#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include <string>


std::string responsestring;
std::string successstring = "1";
int main(int argc, char **argv)
{
    ros::init(argc, argv, "gripper_rapid_tester_node");
    ros::NodeHandle n;

    ros::ServiceClient client = n.serviceClient<std_srvs::SetBool>("/gripper_srv");
    
    std_srvs::SetBool srv;
    srv.request.data = true; // to close gripper
    
      

    ros::Rate rate(1./5.); // hz
  while (ros::ok())
  {
    if (client.call(srv))
    {
    ROS_INFO("%s", srv.response.success ? "call successed" : "call failed");
    ROS_INFO("Response: %s", srv.response.message.c_str());
    }
    else
    {
    ROS_ERROR("Failed to call service gripper_srv");
    return 1;
    }

    srv.request.data = !srv.request.data; // inverting gripper state

    ros::spinOnce();
    rate.sleep();
  }


}