#include <Robot.h>

float ax_ms2, ay_ms2, az_ms2;
float gx_rads, gy_rads, gz_rads;

void setup()
{
    //robot.imu.Calibrrate();

}

void loop()
{
    robot.imu.getMotion6(&ax_ms2, &ay_ms2, &az_ms2, &gx_rads, &gy_rads, &gz_rads);
    
    Serial.print("a/g:\t");
    Serial.print(ax_ms2); Serial.print("\t");
    Serial.print(ay_ms2); Serial.print("\t");
    Serial.print(az_ms2); Serial.print("\t");
    Serial.print(gx_rads); Serial.print("\t");
    Serial.print(gy_rads); Serial.print("\t");
    Serial.print(gz_rads); Serial.print("\t");
    Serial.print(robot.imu.getTemperature()); Serial.println("degC");

    delay(500);

}