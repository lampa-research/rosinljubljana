#include "Motor.h"

Motor::Motor()
{
}

void Motor::begin(int motor, float gear_ratio, bool reverse_direction, void (*f_A)(void), void (*f_B)(void))
{
    _reverse_direction = reverse_direction;
    if (motor == LEFT)
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
    else if (motor == RIGHT)
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

    // PWM setup
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

    // current measurement setup
    pinMode(_current_pin, OUTPUT);

    // encoder setup
    _encoder_distance_increment = 1.0f / ENCODER_CPR * WHEEL_DIAMETER * PI / GEAR_RATIO;
    pinMode(_encoder_pin_A, INPUT);
    pinMode(_encoder_pin_B, INPUT);
    attachInterrupt(_encoder_pin_A, f_A, CHANGE);
    attachInterrupt(_encoder_pin_B, f_B, CHANGE);
}

void Motor::setVoltage(float u)
{
    _voltage = u;
    _pwm_value = constrain((int)((_voltage * _pwm_value_max) / _supply_voltage), -_pwm_value_max, _pwm_value_max);
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
}

void Motor::setSpeed(float speed_ref)
{
    getSpeed();
    ulong now = micros();
    float dt = _us * (now - _motor_last);
    _motor_last = now;

    if (dt > _motor_timeout)
    {
        _error_integral = 0.0f;
        _error_previous = 0.0f;
    }

    float error = speed_ref - _speed;
    _error_integral = constrain(_error_integral + error * dt, -_error_integral_limit, _error_integral_limit);
    float error_differential = (error - _error_previous) / dt;
    float U = constrain(_kp * error + _ki * _error_integral + _kd * error_differential, -_supply_voltage, _supply_voltage);
    setVoltage(U);
    _error_previous = error;
}

void Motor::setEncoderCountA()
{
    if (digitalRead(_encoder_pin_A) == digitalRead(_encoder_pin_B))
    {
        _encoder_count++;
    }
    else
    {
        _encoder_count--;
    }

    return;
}

void Motor::setEncoderCountB()
{
    if (digitalRead(_encoder_pin_A) != digitalRead(_encoder_pin_B))
    {
        _encoder_count++;
    }
    else
    {
        _encoder_count--;
    }
}

void Motor::setSpeedKp(float kp)
{
    _kp = kp;
}

void Motor::setSpeedKi(float ki)
{
    _ki = ki;
}

void Motor::setSpeedKd(float kd)
{
    _kd = kd;
}

void Motor::setSpeedILimit(float limit)
{
    _error_integral_limit = limit;
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
        _encoder_count_start = micros();
    }
    else if (abs(_encoder_count) > _encoder_count_min)
    {
        float dd = _encoder_distance_increment * _encoder_count;
        _speed = dd / dt;

        _encoder_count = 0;
        _encoder_count_start = micros();
    }
    return _speed;
}

float Motor::getCurrent()
{
    return ((_supply_voltage * analogRead(_current_pin)) / _adc_current_value_max);
}