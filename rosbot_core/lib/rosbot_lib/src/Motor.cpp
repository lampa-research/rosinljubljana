#include "Motor.h"
Motor::Motor() {}

void Motor::init(int motor, bool reverse_direction, void (*f_A)(void), void (*f_B)(void))
{
    _motor = motor;
    _reverse_direction = reverse_direction;

    if (_motor == LEFT)
    {
        _channel_A = MOTOR_PWM_0;
        _channel_B = MOTOR_PWM_1;
        _current_pin = IL;
        _encoder_pin_A = ENCLA;
        _encoder_pin_B = ENCLB;
        if (!_reverse_direction)
        {
            _motor_A_pin = INL1;
            _motor_B_pin = INL2;
        }
        else
        {
            _motor_A_pin = INL2;
            _motor_B_pin = INL1;
        }
    }
    else if (_motor == RIGHT)
    {
        _channel_A = MOTOR_PWM_2;
        _channel_B = MOTOR_PWM_3;
        _current_pin = IR;
        _encoder_pin_B = ENCRA;
        _encoder_pin_A = ENCRB;
        if (!_reverse_direction)
        {
            _motor_A_pin = INR1;
            _motor_B_pin = INR2;
        }
        else
        {
            _motor_A_pin = INR2;
            _motor_B_pin = INR1;
        }
    }

    //setup pwm
    pinMode(_motor_A_pin, OUTPUT);
    pinMode(_motor_B_pin, OUTPUT);
    ledcSetup(_channel_A, _pwm_freq, _pwm_resolution);
    ledcSetup(_channel_B, _pwm_freq, _pwm_resolution);
    ledcAttachPin(_motor_A_pin, _channel_A);
    ledcAttachPin(_motor_B_pin, _channel_B);
    ledcWriteTone(_channel_A, _pwm_freq);
    ledcWriteTone(_channel_B, _pwm_freq);
    ledcWrite(_channel_A, 0);
    ledcWrite(_channel_B, 0);
    //setup current
    pinMode(_current_pin, OUTPUT);
    //encoder
    pinMode(_encoder_pin_A, INPUT);
    pinMode(_encoder_pin_B, INPUT);
    attachInterrupt(_encoder_pin_A, f_A, CHANGE);
    attachInterrupt(_encoder_pin_B, f_B, CHANGE);
}

void Motor::spinOnce()
{
    getSpeed();

    ulong now = micros();
    float dt = _us * (now - _motor_last);
    _motor_last = now;

    if (dt > _motor_timeout)
    {
        _error_integral = 0.0f;
        _error_previous = 0.0f;
        return;
    }

    float error = _speed_ref - _speed;
    _error_integral = _error_integral + error * dt;

    if (_error_integral > _error_integral_limit)
    {
        _error_integral = _error_integral_limit;
    }
    else if (_error_integral < -_error_integral_limit)
    {
        _error_integral = -_error_integral_limit;
    }

    float errorDifferential = (error - _error_previous) / dt;

    float U = _kp * error + _ki * _error_integral + _kd * errorDifferential;

    if (U > _supply_voltage)
    {
        U = _supply_voltage;
    }
    setVoltage(U);

    _error_previous = error;

    return;
}

// Set ---

void Motor::setVoltage(float u)
{
    _voltage = u;
    _pwm_value = (int)((_voltage * _pwm_value_max) / _supply_voltage);

    if (_pwm_value > _pwm_value_max)
    {
        _pwm_value = _pwm_value_max;
    }
    else if (_pwm_value < -_pwm_value_max)
    {
        _pwm_value = -_pwm_value_max;
    }

    if (_pwm_value >= 0)
    {
        ledcWrite(_channel_A, 0);
        ledcWrite(_channel_B, _pwm_value);
    }
    else
    {
        ledcWrite(_channel_A, -_pwm_value);
        ledcWrite(_channel_B, 0);
    }

    return;
}

void Motor::setSpeed(float speed_ref)
{
    _speed_ref = speed_ref;
}

void Motor::setEncoderCountA()
{
    if (digitalRead(_encoder_pin_A) == HIGH && digitalRead(_encoder_pin_B) == LOW)
    {
        _encoder_count--;
        _encoder_count_position--;
    }
    else if (digitalRead(_encoder_pin_A) == LOW && digitalRead(_encoder_pin_B) == HIGH)
    {
        _encoder_count--;
        _encoder_count_position--;
    }
    else if (digitalRead(_encoder_pin_A) == HIGH && digitalRead(_encoder_pin_B) == HIGH)
    {
        _encoder_count++;
        _encoder_count_position++;
    }
    else if (digitalRead(_encoder_pin_A) == LOW && digitalRead(_encoder_pin_B) == LOW)
    {
        _encoder_count++;
        _encoder_count_position++;
    }

    return;
}

void Motor::setEncoderCountB()
{
    if (digitalRead(_encoder_pin_A) == HIGH && digitalRead(_encoder_pin_B) == LOW)
    {
        _encoder_count++;
        _encoder_count_position++;
    }
    else if (digitalRead(_encoder_pin_A) == LOW && digitalRead(_encoder_pin_B) == HIGH)
    {
        _encoder_count++;
        _encoder_count_position++;
    }
    else if (digitalRead(_encoder_pin_A) == HIGH && digitalRead(_encoder_pin_B) == HIGH)
    {
        _encoder_count--;
        _encoder_count_position--;
    }
    else if (digitalRead(_encoder_pin_A) == LOW && digitalRead(_encoder_pin_B) == LOW)
    {
        _encoder_count--;
        _encoder_count_position--;
    }

    return;
}

void Motor::setSpeedPIDGains(float kp, float ki, float kd)
{
    _kp = kp;
    _ki = ki;
    _kd = kd;

    return;
}

void Motor::setSpeedILimit(float limit)
{
    _error_integral_limit = limit;

    return;
}

// Get ---
int Motor::getEncoderCountPosition()
{
    int x = _encoder_count_position;
    _encoder_count_position = 0;
    return x;
}

float Motor::getVoltage()
{
    return _voltage;
}

float Motor::getSpeed()
{
    ulong now = micros();
    float dt = _us * (now - _encoder_count_start);

    if (dt > _encoder_timeout)
    {
        _speed = 0.0f;
        _encoder_count = 0;
        _encoder_count_start = now;
    }
    else if (abs(_encoder_count) > _encoder_count_min)
    {
        float dd = ENCODER_DISTANCE_INCREMENT * _encoder_count;
        _speed = dd / dt;

        _encoder_count = 0;
        _encoder_count_start = now;
    }
    else
    {
        //wait for higher ecoder count
    }

    return _speed;
}

float Motor::getCurrent()
{
    return ((_supply_voltage * analogRead(_current_pin)) / _adc_current_value_max);
}