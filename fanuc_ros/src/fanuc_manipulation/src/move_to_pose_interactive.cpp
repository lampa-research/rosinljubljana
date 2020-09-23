#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "move_group_interface_tutorial");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();

    // Initialising and defining the planning group for move_base
    static const std::string PLANNING_GROUP = "fanuc_arm";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    // Raw pointers are frequently used to refer to the planning group for improved performance.
    const robot_state::JointModelGroup *joint_model_group =
        move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

    // Initialisation of Rviz Visual Tools
    moveit_visual_tools::MoveItVisualTools visual_tools("base_link");
    // Clear existing markers
    visual_tools.deleteAllMarkers();
    // Pre-load remote control
    visual_tools.loadRemoteControl();

    Eigen::Isometry3d text_pose = Eigen::Isometry3d::Identity();
    text_pose.translation().z() = 1;
    visual_tools.publishText(text_pose, "MoveGroupInterface Tutorial", rviz_visual_tools::LIME_GREEN, rviz_visual_tools::XLARGE);
    visual_tools.trigger();

    // Defining target pose
    geometry_msgs::Pose target_pose;
    target_pose.position.x = 0.1;
    target_pose.position.y = -0.25;
    target_pose.position.z = 0.35;
    target_pose.orientation.y = sqrt(2) / 2;
    target_pose.orientation.w = sqrt(2) / 2;
    move_group.setPoseTarget(target_pose);
    ROS_INFO_NAMED("move_to_pose", "Setting the target position to x=%g, y=%g, z=%g",
                   target_pose.position.x, target_pose.position.y, target_pose.position.z);
                   
    visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue");

    // Initialising a new plan and planning
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue");

    // Executing the movement
    move_group.move();

    ros::shutdown();
    return 0;
}