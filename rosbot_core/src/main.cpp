#include <Robot.h>

#include <WiFi.h>
#include <WiFiDetails.h>

#include <ros.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/BatteryState.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Odometry.h>

const char *ssid = SSID;         /**< Defined in WiFiDetails.h */
const char *password = PASSWORD; /**< Defined in WiFiDetails.h */

ros::NodeHandle nh;

sensor_msgs::BatteryState battery_msg;
ros::Publisher battery_pub("battery", &battery_msg);
sensor_msgs::LaserScan laserscan_msg;
ros::Publisher laserscan_pub("scan", &laserscan_msg);
nav_msgs::Odometry odometry_msg;
ros::Publisher odometry_pub("odom", &odometry_msg);

void twistCb(const geometry_msgs::Twist &msg)
{
    robot.setSpeed(msg.linear.x, msg.angular.z);
}

void leftKpCb(const std_msgs::Float32 &msg)
{
    robot.motor_left.setSpeedKp(msg.data);
}

void leftKiCb(const std_msgs::Float32 &msg)
{
    robot.motor_left.setSpeedKi(msg.data);
}

void leftKdCb(const std_msgs::Float32 &msg)
{
    robot.motor_left.setSpeedKd(msg.data);
}

void rightKpCb(const std_msgs::Float32 &msg)
{
    robot.motor_right.setSpeedKp(msg.data);
}

void rightKiCb(const std_msgs::Float32 &msg)
{
    robot.motor_right.setSpeedKi(msg.data);
}

void rightKdCb(const std_msgs::Float32 &msg)
{
    robot.motor_right.setSpeedKd(msg.data);
}

bool lidar_started = false;

void lidarCb(const std_msgs::Bool &msg)
{
    lidar_started = msg.data;
}

ros::Subscriber<geometry_msgs::Twist> twist_sub("/cmd_vel", &twistCb);
ros::Subscriber<std_msgs::Float32> left_kp_sub("/left_motor/kp", &leftKpCb);
ros::Subscriber<std_msgs::Float32> left_ki_sub("/left_motor/ki", &leftKiCb);
ros::Subscriber<std_msgs::Float32> left_kd_sub("/left_motor/kd", &leftKdCb);
ros::Subscriber<std_msgs::Float32> right_kp_sub("/right_motor/kp", &rightKpCb);
ros::Subscriber<std_msgs::Float32> right_ki_sub("/right_motor/ki", &rightKiCb);
ros::Subscriber<std_msgs::Float32> right_kd_sub("/right_motor/kd", &rightKdCb);
ros::Subscriber<std_msgs::Bool> lidar_sub("/lidar", &lidarCb);

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

    IPAddress server(192, 168, 2, 136);
    const uint16_t serverPort = 11411;
    nh.getHardware()->setConnection(server, serverPort);
    nh.initNode();
    nh.advertise(battery_pub);
    nh.advertise(laserscan_pub);
    nh.advertise(odometry_pub);

    nh.subscribe(twist_sub);
    nh.subscribe(left_kp_sub);
    nh.subscribe(left_ki_sub);
    nh.subscribe(left_kd_sub);
    nh.subscribe(right_kp_sub);
    nh.subscribe(right_ki_sub);
    nh.subscribe(right_kd_sub);
    nh.subscribe(lidar_sub);

    laserscan_msg.ranges_length = 180;
    laserscan_msg.intensities_length = 0;
    laserscan_msg.header.frame_id = "scan";
    laserscan_msg.range_min = 0.08;
    laserscan_msg.range_max = 0.33;
    laserscan_msg.time_increment = 0.010;
    laserscan_msg.scan_time = 0; // laserscan_msg.time_increment * laserscan_msg.ranges_length;
    laserscan_msg.ranges = (float *)malloc(sizeof(float) * 180);

    odometry_msg.header.frame_id = "odom";
    odometry_msg.child_frame_id = "base_link";
    odometry_msg.pose.covariance[0] = 1.0;
    odometry_msg.pose.covariance[7] = 1.0;
    odometry_msg.pose.covariance[35] = 1.0;

    odometry_msg.twist.covariance[0] = 0.01;
    odometry_msg.twist.covariance[35] = 0.10;
}

ulong loop_time = 0;
ulong update_time = 0;
int sweep_dir = 1;

void loop()
{
    robot.spinOnce();

    ulong current_time = millis();

    if (lidar_started && current_time - loop_time > laserscan_msg.time_increment * 1000)
    {
        loop_time = current_time;
        int current_position = robot.lidar.currentPosition();
        float distance = robot.lidar.getDistanceAverage(100);
        robot.lidar.nextPosition(1);
        if (sweep_dir)
        {
            laserscan_msg.ranges[current_position] = distance;
        }
        else
        {
            laserscan_msg.ranges[179 - current_position] = distance;
        }
        if ((sweep_dir == 1 && current_position >= 179) || (sweep_dir == 0 && current_position <= 0))
        {

            if (sweep_dir)
            {
                laserscan_msg.angle_min = -PI / 2.0;
                laserscan_msg.angle_max = PI / 2.0;
                laserscan_msg.angle_increment = PI / 180.0;
            }
            else
            {
                laserscan_msg.angle_min = PI / 2.0;
                laserscan_msg.angle_max = -PI / 2.0;
                laserscan_msg.angle_increment = -PI / 180.0;
            }
            sweep_dir = !sweep_dir;
            laserscan_msg.header.stamp = nh.now();

            laserscan_pub.publish(&laserscan_msg);
        }
    }

    if (current_time - update_time > 100)
    {
        update_time = current_time;

        battery_msg.header.stamp = nh.now();
        battery_msg.voltage = robot.battery.getVoltage();
        battery_pub.publish(&battery_msg);

        odometry_msg.header.stamp = nh.now();
        odometry_msg.pose.pose.position.x = robot.position_x;
        odometry_msg.pose.pose.position.y = robot.position_y;
        odometry_msg.pose.pose.orientation.w = cos(0.5 * robot.orientation_z);
        odometry_msg.pose.pose.orientation.x = 0;
        odometry_msg.pose.pose.orientation.y = 0;
        odometry_msg.pose.pose.orientation.z = sin(0.5 * robot.orientation_z);
        odometry_msg.twist.twist.linear.x = robot.speed_linear;
        odometry_msg.twist.twist.angular.z = robot.speed_angular;
        odometry_pub.publish(&odometry_msg);
    }

    nh.spinOnce();
}