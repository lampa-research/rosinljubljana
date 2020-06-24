#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ENCODER_CPR 12
#define MOTOR_GEAR_RATIO 100.37004662
#define ROBOT_WHEELBASE 0.0825
#define WHEEL_DIAMETER 0.0325

#define ENCODER_DISTANCE_INCREMENT (1.0f / ENCODER_CPR * WHEEL_DIAMETER * PI / MOTOR_GEAR_RATIO)
#define WHEEL_ARC_LENGTH (PI * WHEEL_DIAMETER / MOTOR_GEAR_RATIO / ENCODER_CPR)
#define ROBOT_ROTATION_INCREMENT (WHEEL_ARC_LENGTH / ROBOT_WHEELBASE)
#define ROBOT_TRANSLATION_INCREMENT (tan(ROBOT_ROTATION_INCREMENT / 2) * ROBOT_WHEELBASE)

// _increment_robot_rotation_angle_left = -motor_left.increment_wheel_arc_length / ROBOT_WHEELBASE;
// _increment_robot_rotation_angle_right = motor_right.increment_wheel_arc_length / ROBOT_WHEELBASE;
// _increment_robot_translation_distance_left = tan(-_increment_robot_rotation_angle_left / 2) * ROBOT_WHEELBASE;
// _increment_robot_translation_distance_right = tan(_increment_robot_rotation_angle_right / 2) * ROBOT_WHEELBASE;

#endif