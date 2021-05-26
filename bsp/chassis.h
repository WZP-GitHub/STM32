#ifndef __CHASSIS_H
#define __CHASSIS_H
#include "struct_typedef.h"
#include "pid.h"
#include "remote_control.h"
#include "CAN_receive.h"
#define MOTOR_DISTANCE_TO_CENTER 0.2f
void chassis_vector_to_mecanum_wheel_speed(fp32 vx_set, fp32 vy_set, fp32 wz_set, fp32 wheel_speed[4]);
void chassis_control_loop(void);
#endif
