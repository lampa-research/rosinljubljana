#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "move_group_interface_tutorial");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();

    // Initialising and defining the planning group for move_base
    static const std::string PLANNING_GROUP = "manipulator";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    // Raw pointers are frequently used to refer to the planning group for improved performance.
    const moveit::core::JointModelGroup *joint_model_group =
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
    

    // A pointer that references the current robot's state.
    // RobotState is the object that contains all the current position/velocity/acceleration data.
    moveit::core::RobotStatePtr current_state = move_group.getCurrentState();
    // Get the current set of joint values for the group.
    std::vector<double> joint_group_positions;
    current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
    // Modifing one of the joint positions
    joint_group_positions[0] = -0.3; // radians
    joint_group_positions[1] = 0.1;
    // Pass the desired joint positions to move_group as goal for planning
    move_group.setJointValueTarget(joint_group_positions);

    // We lower the allowed maximum velocity and acceleration to 5% of their maximum.
    // The default values are 10% (0.1).
    move_group.setMaxVelocityScalingFactor(0.05);
    move_group.setMaxAccelerationScalingFactor(0.05);

    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue");

    move_group.move();

    ros::shutdown();
    return 0;
}
