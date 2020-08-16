#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_srvs/SetBool.h>

ros::Publisher f1_pub;
ros::Publisher f2_pub;

bool gripper(std_srvs::SetBool::Request &req,
             std_srvs::SetBool::Response &res)
{
    std_msgs::Float64 msg;
    if (req.data)
    {
        msg.data = 0.01;
        f1_pub.publish(msg);
        f2_pub.publish(msg);
    }
    else
    {
        msg.data = 0.00;
        f1_pub.publish(msg);
        f2_pub.publish(msg);
    }
    res.success = true;
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "schunk_gripper");
    ros::NodeHandle n;

    f1_pub = n.advertise<std_msgs::Float64>("finger_joint1_controller/command", 1000);
    f2_pub = n.advertise<std_msgs::Float64>("finger_joint2_controller/command", 1000);
    ros::ServiceServer service = n.advertiseService("gripper_closed", gripper);
    ros::spin();

    return 0;
}
