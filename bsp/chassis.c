#include "chassis.h"
void chassis_vector_to_mecanum_wheel_speed(fp32 vx_set,fp32 vy_set,fp32 wz_set, fp32 wheel_speed[4])
{
    wheel_speed[0] = -vx_set + vy_set + MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[1] = vx_set + vy_set + MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[2] = vx_set - vy_set + MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[3] = -vx_set - vy_set + MOTOR_DISTANCE_TO_CENTER * wz_set;
}

void chassis_control_loop(void)
{
	fp32 wheel_speed[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    uint8_t i = 0;
	chassis_vector_to_mecanum_wheel_speed((float)((get_remote_control_point()->rc.ch[1])*24),(float)((get_remote_control_point()->rc.ch[0])*24),(float)((get_remote_control_point()->rc.ch[2])*24),wheel_speed);
	for (i = 0; i < 4; i++)
    {
        pid_calc(&pid_spd[i], get_chassis_motor_measure_point(i)->speed_rpm, wheel_speed[i]);
    }
  CAN_cmd_chassis(pid_spd[0].pos_out,pid_spd[1].pos_out,pid_spd[2].pos_out,pid_spd[3].pos_out);
}
