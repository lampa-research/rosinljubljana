#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "move_cartesian");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();

    static const std::string PLANNING_GROUP = "fanuc_arm";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    const robot_state::JointModelGroup *joint_model_group =
        move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

    namespace rvt = rviz_visual_tools;
    moveit_visual_tools::MoveItVisualTools visual_tools("base_link");
    visual_tools.deleteAllMarkers();
    visual_tools.loadRemoteControl();

    Eigen::Isometry3d text_pose = Eigen::Isometry3d::Identity();
    text_pose.translation().z() = 0.8;
    visual_tools.publishText(text_pose, "MoveGroupInterface Demo", rvt::WHITE, rvt::XLARGE);
    visual_tools.trigger();

    ROS_INFO_NAMED("move_cartesian", "Planning frame: %s", move_group.getPlanningFrame().c_str());
    ROS_INFO_NAMED("move_cartesian", "Available Planning Groups:");
    std::copy(move_group.getJointModelGroupNames().begin(), move_group.getJointModelGroupNames().end(),
              std::ostream_iterator<std::string>(std::cout, ", "));

    visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");

    //setting waypoints
    std::vector<geometry_msgs::Pose> waypoints;
    robot_state::RobotState start_state(*move_group.getCurrentState());
    geometry_msgs::Pose start_pose;
    start_pose.orientation.y = sqrt(2) / 2;
    start_pose.orientation.w = sqrt(2) / 2;
    start_pose.position.x = 0.3;
    start_pose.position.y = 0.15;
    start_pose.position.z = 0.3;
    waypoints.push_back(start_pose);

    geometry_msgs::Pose target_pose = start_pose;

    target_pose.position.y -= 0.15;
    target_pose.position.z -= 0.15;
    waypoints.push_back(target_pose); // down right

    target_pose.position.y -= 0.15;
    target_pose.position.z += 0.15;
    waypoints.push_back(target_pose); // up right

    target_pose.orientation.y = 0;
    target_pose.orientation.w = 1;
    target_pose.position.y += 0.15;
    target_pose.position.z += 0.15;
    waypoints.push_back(target_pose); // up left

    target_pose.position.y += 0.15;
    target_pose.position.z -= 0.15;
    waypoints.push_back(target_pose); // down left

    //planning
    moveit_msgs::RobotTrajectory trajectory;
    const double jump_threshold = 0.0;
    const double eef_step = 0.01;
    double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
    ROS_INFO_NAMED("move_cartesian", "Visualizing plan through waypoints (%.2f%% acheived)", fraction * 100.0);

    // Visualize the plan in RViz
    visual_tools.deleteAllMarkers();
    visual_tools.publishText(text_pose, "Waypoints", rvt::WHITE, rvt::XLARGE);
    visual_tools.publishPath(waypoints, rvt::MAGENTA, rvt::SMALL);
    for (std::size_t i = 0; i < waypoints.size(); ++i)
        visual_tools.publishAxisLabeled(waypoints[i], "pt" + std::to_string(i), rvt::MEDIUM);
    visual_tools.trigger();
    visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue with path execution");

    //path execution
    move_group.execute(trajectory);
    visual_tools.prompt("Press 'next' to exit the program");

    ros::shutdown();
    return 0;
}