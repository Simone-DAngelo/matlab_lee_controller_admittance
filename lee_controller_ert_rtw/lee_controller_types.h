//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: lee_controller_types.h
//
// Code generated for Simulink model 'lee_controller'.
//
// Model version                  : 1.175
// Simulink Coder version         : 9.6 (R2021b) 14-May-2021
// C/C++ source code generated on : Wed Jun 22 12:14:53 2022
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_lee_controller_types_h_
#define RTW_HEADER_lee_controller_types_h_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include <uORB/topics/actuator_armed.h>
#include <uORB/topics/commander_state.h>
#include <uORB/topics/vehicle_local_position.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/vehicle_angular_velocity.h>
#include <uORB/topics/linear_err.h>
#include <uORB/topics/ang_err.h>
#include <uORB/topics/act_wrench.h>
#include <uORB/topics/admittance.h>
#include <uORB/topics/traj_setpoint.h>
#include <uORB/topics/input_rc.h>

// Model Code Variants
#ifndef struct_px4_internal_block_PWM_lee_co_T
#define struct_px4_internal_block_PWM_lee_co_T

struct px4_internal_block_PWM_lee_co_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  int pwmDevHandler;
  const char * pwmDevObj;
  unsigned int servoCount;
  int channelMask;
  boolean_T isMain;
  uint16_T errorStatus;
  orb_advert_t armAdvertiseObj;
  orb_advert_t actuatorAdvertiseObj;
  boolean_T isArmed;
};

#endif                                // struct_px4_internal_block_PWM_lee_co_T

#ifndef struct_e_px4_internal_block_SampleTi_T
#define struct_e_px4_internal_block_SampleTi_T

struct e_px4_internal_block_SampleTi_T
{
  int32_T __dummy;
};

#endif                                // struct_e_px4_internal_block_SampleTi_T

#ifndef struct_px4_internal_block_Subscriber_T
#define struct_px4_internal_block_Subscriber_T

struct px4_internal_block_Subscriber_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_px4_internal_block_SampleTi_T SampleTimeHandler;
  pollfd_t eventStructObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                // struct_px4_internal_block_Subscriber_T

#ifndef struct_px4_internal_block_Publisher__T
#define struct_px4_internal_block_Publisher__T

struct px4_internal_block_Publisher__T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  orb_advert_t orbAdvertiseObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                // struct_px4_internal_block_Publisher__T

// Custom Type definition for MATLABSystem: '<S42>/Read Parameter9'
#include "MW_Parameter.h"
#ifndef struct_px4_internal_block_ParameterU_T
#define struct_px4_internal_block_ParameterU_T

struct px4_internal_block_ParameterU_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T SampleTime;
  MW_Param_Handle MW_PARAMHANDLE;
};

#endif                                // struct_px4_internal_block_ParameterU_T

// Custom Type definition for MATLABSystem: '<Root>/Serial Receive1'
#include "MW_SVD.h"
#ifndef struct_c_px4_internal_block_Hardware_T
#define struct_c_px4_internal_block_Hardware_T

struct c_px4_internal_block_Hardware_T
{
  int32_T __dummy;
};

#endif                                // struct_c_px4_internal_block_Hardware_T

#ifndef struct_d_px4_internal_block_PX4SCIDr_T
#define struct_d_px4_internal_block_PX4SCIDr_T

struct d_px4_internal_block_PX4SCIDr_T
{
  MW_Handle_Type MW_SCIHANDLE;
};

#endif                                // struct_d_px4_internal_block_PX4SCIDr_T

#ifndef struct_px4_internal_block_PX4SCIRead_T
#define struct_px4_internal_block_PX4SCIRead_T

struct px4_internal_block_PX4SCIRead_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  c_px4_internal_block_Hardware_T Hw;
  d_px4_internal_block_PX4SCIDr_T SCIDriverObj;
  real_T SampleTime;
};

#endif                                // struct_px4_internal_block_PX4SCIRead_T

// Parameters (default storage)
typedef struct P_lee_controller_T_ P_lee_controller_T;

// Forward declaration for rtModel
typedef struct tag_RTM_lee_controller_T RT_MODEL_lee_controller_T;

#endif                                 // RTW_HEADER_lee_controller_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
