
cmake_minimum_required(VERSION 3.0.2)
project(gripper_controller)

add_compile_options(-std=c++11)
set(CURL_LIBRARY "-lcurl") 


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  std_srvs
)

find_package(CURL REQUIRED)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES gripper_controller
   CATKIN_DEPENDS roscpp rospy std_msgs std_srvs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${CURL_INCLUDE_DIR}
)

# **************************************** #
add_executable(${PROJECT_NAME}_node 
  src/gripper_node.cpp
)
target_link_libraries(${PROJECT_NAME}_node 
  ${catkin_LIBRARIES} 
  ${CURL_LIBRARIES}
)

# **************************************** #
add_executable(${PROJECT_NAME}_test 
  src/gripper_test.cpp
)
target_link_libraries(${PROJECT_NAME}_test 
  ${catkin_LIBRARIES} 
)