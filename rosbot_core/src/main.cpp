#include <Robot.h>

#include <WiFi.h>

#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <ros.h>
#include <sensor_msgs/BatteryState.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Header.h>

ros::NodeHandle nh;
sensor_msgs::BatteryState battery_msg;
ros::Publisher battery_pub("battery", &battery_msg);
sensor_msgs::LaserScan laserscan_msg;
ros::Publisher laserscan_pub("scan", &laserscan_msg);
nav_msgs::Odometry odometry_msg;
ros::Publisher odometry_pub("odom", &odometry_msg);
sensor_msgs::Imu imu_msg;
ros::Publisher imu_pub("imu", &imu_msg);

void twistCb(const geometry_msgs::Twist &msg)
{
    robot.setSpeed(msg.linear.x, msg.angular.z);
}
ros::Subscriber<geometry_msgs::Twist> twist_sub("/cmd_vel", &twistCb);

void lidarCb(const std_msgs::Bool &msg)
{
    robot.setLidarStarted(msg.data);
}
ros::Subscriber<std_msgs::Bool> lidar_sub("/lidar", &lidarCb);

void setup()
{
    robot.setup.init();
    robot.setup.loop();
    if (robot.eeprom.getMOTOR_PID_CUSTOM("left"))
    {
        robot.motor_left.setSpeedPIDGains(robot.eeprom.getMOTOR_P("left"), robot.eeprom.getMOTOR_I("left"), robot.eeprom.getMOTOR_D("left"));
    }
    if (robot.eeprom.getMOTOR_PID_CUSTOM("right"))
    {
        robot.motor_left.setSpeedPIDGains(robot.eeprom.getMOTOR_P("right"), robot.eeprom.getMOTOR_I("right"), robot.eeprom.getMOTOR_D("right"));
    }
    robot.setLidarBacklash(robot.eeprom.getLIDAR_Backlash());
    robot.setLidarAngle(robot.eeprom.getLIDAR_Angle());

    WiFi.begin(robot.eeprom.getSSID().c_str(), robot.eeprom.getPASS().c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.print("Connected to the WiFi network. IP: ");
    Serial.println(WiFi.localIP());

    int ros_ip[4] ={ 0, 0, 0, 0 };
    int i = 0;
    String s = robot.eeprom.getROSMaster();
    char delimiter = '.';
    size_t pos = 0;
    String token;
    while ((pos = s.indexOf(delimiter)) != std::string::npos)
    {
        token = s.substring(0, pos);
        ros_ip[i++] = token.toInt();
        s = s.substring(pos + 1);
    }
    ros_ip[i] = s.toInt();
    IPAddress server(ros_ip[0], ros_ip[1], ros_ip[2], ros_ip[3]);
    const uint16_t serverPort = 11411;
    nh.getHardware()->setConnection(server, serverPort);
    nh.initNode();
    nh.advertise(battery_pub);
    nh.advertise(laserscan_pub);
    nh.advertise(odometry_pub);
    nh.advertise(imu_pub);

    nh.subscribe(twist_sub);
    nh.subscribe(lidar_sub);

    laserscan_msg.ranges_length = robot.getLidarAngle() + 1;
    laserscan_msg.intensities_length = 0;
    laserscan_msg.header.frame_id = "lidar_link";
    laserscan_msg.range_min = 0.08;
    laserscan_msg.range_max = 1.00;
    laserscan_msg.time_increment = 0.010;
    laserscan_msg.scan_time = 0; // laserscan_msg.time_increment * laserscan_msg.ranges_length;
    laserscan_msg.ranges = (float *)malloc(sizeof(float) * (robot.getLidarAngle() + 1));

    odometry_msg.header.frame_id = "odom";
    odometry_msg.child_frame_id = "base_link";
    odometry_msg.pose.covariance[0] = 0.01;
    odometry_msg.pose.covariance[7] = 0.01;
    odometry_msg.pose.covariance[35] = 0.01;
    odometry_msg.twist.covariance[0] = 0.01;
    odometry_msg.twist.covariance[35] = 0.01;

    imu_msg.header.frame_id = "imu_link";
    imu_msg.linear_acceleration_covariance[0] = 0.1;
    imu_msg.linear_acceleration_covariance[4] = 0.1;
    imu_msg.linear_acceleration_covariance[8] = 0.1;
    imu_msg.angular_velocity_covariance[0] = 0.1;
    imu_msg.angular_velocity_covariance[4] = 0.1;
    imu_msg.angular_velocity_covariance[8] = 0.1;
}

ulong lidar_loop_time = 0;
ulong update_time = 0;
bool robot_moved = false;

void loop()
{
    robot.spinOnce();
    ulong current_time = millis();
    if (robot.isMoving())
    {
        robot_moved = true;
    }

    if (robot.lidarStarted() && current_time - lidar_loop_time > laserscan_msg.time_increment * 1000)
    {
        lidar_loop_time = current_time;
        int current_position = robot.lidar.currentPosition(robot.getLidarAngle()) - 90 + robot.getLidarAngle() / 2;
        float distance = robot.lidar.getDistanceAverage(32);
        robot.lidar.nextPosition(robot.getLidarAngle(), 1);
        if (robot.lidar.getSweepDirection() == 1)
        {
            laserscan_msg.ranges[current_position] = distance;
        }
        else
        {
            laserscan_msg.ranges[robot.getLidarAngle() - 1 - current_position] = distance;
        }
        if ((robot.lidar.getSweepDirection() == 1 && current_position >= robot.getLidarAngle() - 1) || (robot.lidar.getSweepDirection() == 0 && current_position <= 0))
        {

            if (robot.lidar.getSweepDirection() == 1)
            {
                laserscan_msg.angle_min = -PI * (float)robot.getLidarAngle() / 360.0 - robot.getLidarBacklash();
                laserscan_msg.angle_max = PI * (float)robot.getLidarAngle() / 360.0 - robot.getLidarBacklash();
                laserscan_msg.angle_increment = PI / 180.0;
            }
            else
            {
                laserscan_msg.angle_min = PI * (float)robot.getLidarAngle() / 360.0 + robot.getLidarBacklash();
                laserscan_msg.angle_max = -PI * (float)robot.getLidarAngle() / 360.0 + robot.getLidarBacklash();
                laserscan_msg.angle_increment = -PI / 180.0;
            }
            robot.lidar.setSweepDirection(!robot.lidar.getSweepDirection());
            if (!robot_moved)
            {
                laserscan_msg.header.stamp = nh.now();
                laserscan_pub.publish(&laserscan_msg);
            }
            else if (robot_moved && !robot.isMoving())
            {
                robot_moved = false;
            }
        }
    }

    if (current_time - update_time > 100)
    {
        update_time = current_time;

        battery_msg.header.stamp = nh.now();
        battery_msg.voltage = robot.battery.getVoltage();
        battery_pub.publish(&battery_msg);

        odometry_msg.header.stamp = nh.now();
        odometry_msg.pose.pose.position.x = robot.getPositionX();
        odometry_msg.pose.pose.position.y = robot.getPositionY();
        odometry_msg.pose.pose.position.z = 0.016;
        odometry_msg.pose.pose.orientation.w = cos(0.5 * robot.getRotation());
        odometry_msg.pose.pose.orientation.x = 0;
        odometry_msg.pose.pose.orientation.y = 0;
        odometry_msg.pose.pose.orientation.z = sin(0.5 * robot.getRotation());
        odometry_msg.twist.twist.linear.x = robot.getSpeedLinear();
        odometry_msg.twist.twist.angular.z = robot.getSpeedAngular();
        odometry_pub.publish(&odometry_msg);

        imu_msg.header.stamp = nh.now();
        imu_msg.angular_velocity.x = robot.imu.getGyroY() * PI / 180.0;
        imu_msg.angular_velocity.y = -robot.imu.getGyroX() * PI / 180.0;
        imu_msg.angular_velocity.z = robot.imu.getGyroZ() * PI / 180.0;
        imu_msg.linear_acceleration.x = -robot.imu.getAccY() * 9.81;
        imu_msg.linear_acceleration.y = robot.imu.getAccX() * 9.81;
        imu_msg.linear_acceleration.z = robot.imu.getAccZ() * 9.81;
        imu_pub.publish(&imu_msg);
    }

    nh.spinOnce();
}