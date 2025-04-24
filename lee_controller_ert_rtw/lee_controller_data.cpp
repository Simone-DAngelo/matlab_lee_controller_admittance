//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: lee_controller_data.cpp
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
#include "lee_controller.h"
#include "lee_controller_private.h"

// Block parameters (default storage)
P_lee_controller_T lee_controller_P = {
  // Variable: A_inv
  //  Referenced by:
  //    '<S2>/rpm allocation'
  //    '<S5>/rpm_pos allocation'

  { -0.29137529137529145, -0.29137529137529133, -0.29137529137529145,
    -0.29137529137529139, -1.3735562960111642, 1.3735562960111647,
    1.3735562960111647, -1.3735562960111651, 1.3735562960111651,
    -1.3735562960111647, 1.3735562960111642, -1.3735562960111647,
    1.4204545454545454, 1.4204545454545459, -1.4204545454545454,
    -1.4204545454545459 },

  // Variable: dt
  //  Referenced by:
  //    '<Root>/Serial Receive1'
  //    '<S5>/lee att'
  //    '<S5>/lee pos'
  //    '<S42>/Read Parameter'
  //    '<S42>/Read Parameter1'
  //    '<S42>/Read Parameter10'
  //    '<S42>/Read Parameter11'
  //    '<S42>/Read Parameter12'
  //    '<S42>/Read Parameter13'
  //    '<S42>/Read Parameter14'
  //    '<S42>/Read Parameter15'
  //    '<S42>/Read Parameter16'
  //    '<S42>/Read Parameter17'
  //    '<S42>/Read Parameter18'
  //    '<S42>/Read Parameter19'
  //    '<S42>/Read Parameter2'
  //    '<S42>/Read Parameter20'
  //    '<S42>/Read Parameter21'
  //    '<S42>/Read Parameter22'
  //    '<S42>/Read Parameter23'
  //    '<S42>/Read Parameter24'
  //    '<S42>/Read Parameter25'
  //    '<S42>/Read Parameter26'
  //    '<S42>/Read Parameter27'
  //    '<S42>/Read Parameter28'
  //    '<S42>/Read Parameter29'
  //    '<S42>/Read Parameter3'
  //    '<S42>/Read Parameter30'
  //    '<S42>/Read Parameter31'
  //    '<S42>/Read Parameter32'
  //    '<S42>/Read Parameter33'
  //    '<S42>/Read Parameter34'
  //    '<S42>/Read Parameter35'
  //    '<S42>/Read Parameter36'
  //    '<S42>/Read Parameter37'
  //    '<S42>/Read Parameter38'
  //    '<S42>/Read Parameter39'
  //    '<S42>/Read Parameter4'
  //    '<S42>/Read Parameter40'
  //    '<S42>/Read Parameter41'
  //    '<S42>/Read Parameter42'
  //    '<S42>/Read Parameter43'
  //    '<S42>/Read Parameter5'
  //    '<S42>/Read Parameter6'
  //    '<S42>/Read Parameter7'
  //    '<S42>/Read Parameter8'
  //    '<S42>/Read Parameter9'

  0.004,

  // Variable: ei
  //  Referenced by: '<S5>/lee pos'

  { 0.0, 0.0, 0.0 },

  // Variable: eir
  //  Referenced by: '<S5>/lee att'

  { 0.0, 0.0, 0.0 },

  // Variable: g
  //  Referenced by: '<S5>/lee pos'

  9.81,

  // Variable: pitch_offset
  //  Referenced by: '<S18>/Constant'

  0.028,

  // Variable: roll_offset
  //  Referenced by: '<S17>/Constant'

  0.028,

  // Variable: thrust_offset
  //  Referenced by: '<S16>/Constant'

  0.075,

  // Variable: yaw_offset
  //  Referenced by: '<S19>/Constant'

  0.028,

  // Computed Parameter: Out1_Y0
  //  Referenced by: '<S27>/Out1'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // ref_timestamp
    0.0,                               // ref_lat
    0.0,                               // ref_lon
    0.0F,                              // x
    0.0F,                              // y
    0.0F,                              // z

    {
      0.0F, 0.0F }
    ,                                  // delta_xy
    0.0F,                              // delta_z
    0.0F,                              // vx
    0.0F,                              // vy
    0.0F,                              // vz
    0.0F,                              // z_deriv

    {
      0.0F, 0.0F }
    ,                                  // delta_vxy
    0.0F,                              // delta_vz
    0.0F,                              // ax
    0.0F,                              // ay
    0.0F,                              // az
    0.0F,                              // yaw
    0.0F,                              // ref_alt
    0.0F,                              // dist_bottom
    0.0F,                              // dist_bottom_rate
    0.0F,                              // eph
    0.0F,                              // epv
    0.0F,                              // evh
    0.0F,                              // evv
    0.0F,                              // vxy_max
    0.0F,                              // vz_max
    0.0F,                              // hagl_min
    0.0F,                              // hagl_max
    false,                             // xy_valid
    false,                             // z_valid
    false,                             // v_xy_valid
    false,                             // v_z_valid
    0U,                                // xy_reset_counter
    0U,                                // z_reset_counter
    0U,                                // vxy_reset_counter
    0U,                                // vz_reset_counter
    false,                             // xy_global
    false,                             // z_global
    false,                             // dist_bottom_valid

    {
      0U, 0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value
  //  Referenced by: '<S24>/Constant'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // ref_timestamp
    0.0,                               // ref_lat
    0.0,                               // ref_lon
    0.0F,                              // x
    0.0F,                              // y
    0.0F,                              // z

    {
      0.0F, 0.0F }
    ,                                  // delta_xy
    0.0F,                              // delta_z
    0.0F,                              // vx
    0.0F,                              // vy
    0.0F,                              // vz
    0.0F,                              // z_deriv

    {
      0.0F, 0.0F }
    ,                                  // delta_vxy
    0.0F,                              // delta_vz
    0.0F,                              // ax
    0.0F,                              // ay
    0.0F,                              // az
    0.0F,                              // yaw
    0.0F,                              // ref_alt
    0.0F,                              // dist_bottom
    0.0F,                              // dist_bottom_rate
    0.0F,                              // eph
    0.0F,                              // epv
    0.0F,                              // evh
    0.0F,                              // evv
    0.0F,                              // vxy_max
    0.0F,                              // vz_max
    0.0F,                              // hagl_min
    0.0F,                              // hagl_max
    false,                             // xy_valid
    false,                             // z_valid
    false,                             // v_xy_valid
    false,                             // v_z_valid
    0U,                                // xy_reset_counter
    0U,                                // z_reset_counter
    0U,                                // vxy_reset_counter
    0U,                                // vz_reset_counter
    false,                             // xy_global
    false,                             // z_global
    false,                             // dist_bottom_valid

    {
      0U, 0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Out1_Y0_f
  //  Referenced by: '<S48>/Out1'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_last_signal
    0U,                                // channel_count
    0,                                 // rssi
    0U,                                // rc_lost_frame_count
    0U,                                // rc_total_frame_count
    0U,                                // rc_ppm_frame_length

    {
      0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
    ,                                  // values
    false,                             // rc_failsafe
    false,                             // rc_lost
    0U,                                // input_source

    {
      0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value_d
  //  Referenced by: '<S47>/Constant'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_last_signal
    0U,                                // channel_count
    0,                                 // rssi
    0U,                                // rc_lost_frame_count
    0U,                                // rc_total_frame_count
    0U,                                // rc_ppm_frame_length

    {
      0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
    ,                                  // values
    false,                             // rc_failsafe
    false,                             // rc_lost
    0U,                                // input_source

    {
      0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Out1_Y0_p
  //  Referenced by: '<S46>/Out1'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_sample

    {
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F }
    // setpoints
  },

  // Computed Parameter: Constant_Value_e
  //  Referenced by: '<S43>/Constant'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_sample

    {
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F }
    // setpoints
  },

  // Computed Parameter: Out1_Y0_m
  //  Referenced by: '<S28>/Out1'

  {
    (0ULL),                            // timestamp

    {
      0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // q

    {
      0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // delta_q_reset
    0U,                                // quat_reset_counter

    {
      0U, 0U, 0U, 0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value_i
  //  Referenced by: '<S25>/Constant'

  {
    (0ULL),                            // timestamp

    {
      0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // q

    {
      0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // delta_q_reset
    0U,                                // quat_reset_counter

    {
      0U, 0U, 0U, 0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value_in
  //  Referenced by: '<S32>/Constant'

  {
    (0ULL),                            // timestamp

    {
      0.0F, 0.0F, 0.0F }
    ,                                  // ep

    {
      0.0F, 0.0F, 0.0F }
    // ev
  },

  // Computed Parameter: Out1_Y0_o
  //  Referenced by: '<S29>/Out1'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_sample

    {
      0.0F, 0.0F, 0.0F }
    ,                                  // xyz

    {
      0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value_b
  //  Referenced by: '<S26>/Constant'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_sample

    {
      0.0F, 0.0F, 0.0F }
    ,                                  // xyz

    {
      0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value_n
  //  Referenced by: '<S34>/Constant'

  {
    (0ULL),                            // timestamp
    0.0F,                              // fz

    {
      0.0F, 0.0F, 0.0F }
    // tau
  },

  // Computed Parameter: Out1_Y0_d
  //  Referenced by: '<S53>/Out1'

  {
    (0ULL),                            // timestamp
    0U,                                // armed_time_ms
    false,                             // armed
    false,                             // prearmed
    false,                             // ready_to_arm
    false,                             // lockdown
    false,                             // manual_lockdown
    false,                             // force_failsafe
    false,                             // in_esc_calibration_mode
    false,                             // soft_stop

    {
      0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value_h
  //  Referenced by: '<S51>/Constant'

  {
    (0ULL),                            // timestamp
    0U,                                // armed_time_ms
    false,                             // armed
    false,                             // prearmed
    false,                             // ready_to_arm
    false,                             // lockdown
    false,                             // manual_lockdown
    false,                             // force_failsafe
    false,                             // in_esc_calibration_mode
    false,                             // soft_stop

    {
      0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value_k
  //  Referenced by: '<S6>/Constant'

  {
    (0ULL),                            // timestamp
    0.0F,                              // z
    0.0F,                              // dz
    0.0F,                              // ddz
    0.0F                               // f_ext
  },

  // Computed Parameter: Constant_Value_k4
  //  Referenced by: '<S33>/Constant'

  {
    (0ULL),                            // timestamp
    0.0F,                              // eyaw
    0.0F                               // ew
  },

  // Computed Parameter: Out1_Y0_j
  //  Referenced by: '<S54>/Out1'

  {
    (0ULL),                            // timestamp
    0U,                                // main_state

    {
      0U, 0U, 0U, 0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value_f
  //  Referenced by: '<S52>/Constant'

  {
    (0ULL),                            // timestamp
    0U,                                // main_state

    {
      0U, 0U, 0U, 0U, 0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: rpm_Y0
  //  Referenced by: '<S2>/rpm'

  0.0,

  // Expression: 1
  //  Referenced by: '<S16>/Saturation10'

  1.0,

  // Expression: 0
  //  Referenced by: '<S16>/Saturation10'

  0.0,

  // Expression: 1
  //  Referenced by: '<S19>/Saturation9'

  1.0,

  // Expression: -1
  //  Referenced by: '<S19>/Saturation9'

  -1.0,

  // Expression: 1
  //  Referenced by: '<S17>/Saturation9'

  1.0,

  // Expression: -1
  //  Referenced by: '<S17>/Saturation9'

  -1.0,

  // Expression: 1
  //  Referenced by: '<S18>/Saturation9'

  1.0,

  // Expression: -1
  //  Referenced by: '<S18>/Saturation9'

  -1.0,

  // Expression: 0.0
  //  Referenced by: '<S2>/des_yaw_from_RC'

  0.0,

  // Computed Parameter: rpm_Y0_l
  //  Referenced by: '<S5>/rpm'

  0.0,

  // Computed Parameter: kg_Y0
  //  Referenced by: '<S10>/kg'

  0.0,

  // Expression: 0.001
  //  Referenced by: '<S10>/Gain1'

  0.001,

  // Computed Parameter: DiscreteTimeIntegrator1_gainval
  //  Referenced by: '<Root>/Discrete-Time Integrator1'

  0.004,

  // Expression: 0
  //  Referenced by: '<Root>/Discrete-Time Integrator1'

  0.0,

  // Computed Parameter: DiscreteTimeIntegrator_gainval
  //  Referenced by: '<Root>/Discrete-Time Integrator'

  0.004,

  // Expression: 0
  //  Referenced by: '<Root>/Discrete-Time Integrator'

  0.0,

  // Expression: -9.81
  //  Referenced by: '<Root>/Gain'

  -9.81,

  // Computed Parameter: Gain_Gain_k
  //  Referenced by: '<S10>/Gain'

  16384,

  // Computed Parameter: Saturationpwm_UpperSat
  //  Referenced by: '<S1>/Saturation pwm'

  2000U,

  // Computed Parameter: Saturationpwm_LowerSat
  //  Referenced by: '<S1>/Saturation pwm'

  1000U,

  // Computed Parameter: Saturationpwm1_UpperSat
  //  Referenced by: '<S1>/Saturation pwm1'

  2000U,

  // Computed Parameter: Saturationpwm1_LowerSat
  //  Referenced by: '<S1>/Saturation pwm1'

  1000U
};

//
// File trailer for generated code.
//
// [EOF]
//
