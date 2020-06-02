#include <Robot.h>

#include <WiFi.h>
#include <WiFiDetails.h>

#include <ros.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/BatteryState.h>

const char *ssid = SSID; /**< Defined in WiFiDetails.h */
const char *password = PASSWORD; /**< Defined in WiFiDetails.h */

ros::NodeHandle nh;
sensor_msgs::BatteryState battery_msg;
ros::Publisher battery_pub("battery", &battery_msg);

void setup()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.print("Connected to the WiFi network. IP: ");
    Serial.println(WiFi.localIP());

    IPAddress server(192, 168, 2, 147);
    const uint16_t serverPort = 11411;
    nh.getHardware()->setConnection(server, serverPort);
    nh.initNode();
    nh.advertise(battery_pub);
}

void loop()
{
    ros::Time now;
    now = now.fromNSec(millis());
    battery_msg.header.stamp = now;
    battery_msg.voltage = robot.battery.getVoltage();
    battery_pub.publish(&battery_msg);
    nh.spinOnce();
    delay(100);
}