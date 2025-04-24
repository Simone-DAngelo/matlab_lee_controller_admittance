#ifndef _MW_UORB_BUSSTRUCT_CONVERSION_H_
#define _MW_UORB_BUSSTRUCT_CONVERSION_H_

#include <uORB/topics/act_wrench.h>
#include <uORB/topics/actuator_armed.h>
#include <uORB/topics/admittance.h>
#include <uORB/topics/ang_err.h>
#include <uORB/topics/commander_state.h>
#include <uORB/topics/input_rc.h>
#include <uORB/topics/linear_err.h>
#include <uORB/topics/traj_setpoint.h>
#include <uORB/topics/vehicle_angular_velocity.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/vehicle_local_position.h>

typedef struct act_wrench_s  px4_Bus_act_wrench ;
typedef struct actuator_armed_s  px4_Bus_actuator_armed ;
typedef struct admittance_s  px4_Bus_admittance ;
typedef struct ang_err_s  px4_Bus_ang_err ;
typedef struct commander_state_s  px4_Bus_commander_state ;
typedef struct input_rc_s  px4_Bus_input_rc ;
typedef struct linear_err_s  px4_Bus_linear_err ;
typedef struct traj_setpoint_s  px4_Bus_traj_setpoint ;
typedef struct vehicle_angular_velocity_s  px4_Bus_vehicle_angular_velocity ;
typedef struct vehicle_attitude_s  px4_Bus_vehicle_attitude ;
typedef struct vehicle_local_position_s  px4_Bus_vehicle_local_position ;

#endif
