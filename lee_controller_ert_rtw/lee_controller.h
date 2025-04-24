//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: lee_controller.h
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
#ifndef RTW_HEADER_lee_controller_h_
#define RTW_HEADER_lee_controller_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#include <poll.h>
#include <uORB/uORB.h>
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "MW_PX4_PWM.h"
#include "MW_uORB_Read.h"
#include "MW_uORB_Write.h"
#include "MW_Parameter.h"
#include "MW_ParameterRead.h"
#include "MW_PX4_SCI.h"
#include "MW_SCI.h"
#include "lee_controller_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Block signals (default storage)
struct B_lee_controller_T {
  creal_T V[16];
  creal_T At[16];
  px4_Bus_vehicle_local_position In1;  // '<S27>/In1'
  px4_Bus_vehicle_local_position b_varargout_2;
  real_T A[16];
  real_T T[16];
  real_T U[16];
  real_T inv_A[16];                    // '<S5>/inv alloc_matrix'
  px4_Bus_input_rc In1_c;              // '<S48>/In1'
  px4_Bus_input_rc b_varargout_2_m;
  real_T R_drone[9];
  real_T tempR[9];
  real_T catArgs[9];
  real_T R_mes[9];                     // '<S3>/MATLAB Function'
  px4_Bus_traj_setpoint In1_m;         // '<S46>/In1'
  px4_Bus_traj_setpoint b_varargout_2_c;
  creal_T D[4];
  creal_T y[4];
  creal_T work1[4];
  px4_Bus_vehicle_attitude In1_h;      // '<S28>/In1'
  px4_Bus_vehicle_attitude b_varargout_2_k;
  real32_T Rd[9];
  real32_T R_err[9];
  real32_T R_err_tmp[9];
  real32_T ParamStep[9];
  real32_T ParamStep_c[9];
  px4_Bus_vehicle_angular_velocity In1_f;// '<S29>/In1'
  px4_Bus_vehicle_angular_velocity b_varargout_2_b;
  px4_Bus_linear_err BusAssignment;    // '<S5>/Bus Assignment'
  px4_Bus_linear_err BusAssignment_p;  // '<S5>/Bus Assignment'
  real_T rpm[4];                       // '<S5>/rpm_pos allocation'
  real_T rpm_j[4];                     // '<S2>/rpm allocation'
  real_T q[4];
  real_T work[4];
  real_T rworka[4];
  real_T work_c[4];
  px4_Bus_actuator_armed In1_ho;       // '<S53>/In1'
  px4_Bus_actuator_armed b_varargout_2_f;
  px4_Bus_act_wrench BusAssignment2;   // '<S5>/Bus Assignment2'
  px4_Bus_act_wrench BusAssignment2_g; // '<S5>/Bus Assignment2'
  px4_Bus_admittance BusAssignment_k;  // '<Root>/Bus Assignment'
  px4_Bus_admittance BusAssignment_k_g;// '<Root>/Bus Assignment'
  real_T c[3];
  real_T TmpSignalConversionAtSFunct[3];// '<S2>/rate control'
  real_T b3d[3];                       // '<S5>/lee pos'
  real_T tau[3];
  real_T v[3];
  char_T ParameterNameStr[17];
  uint16_T pwmValue[8];
  char_T ParameterNameStr_m[16];
  px4_Bus_commander_state In1_cj;      // '<S54>/In1'
  px4_Bus_commander_state b_varargout_2_n;
  px4_Bus_ang_err BusAssignment1;      // '<S5>/Bus Assignment1'
  px4_Bus_ang_err BusAssignment1_p;    // '<S5>/Bus Assignment1'
  creal_T tmp;
  creal_T ctemp;
  creal_T shift;
  creal_T ascale;
  int32_T rscale[4];
  char_T ParameterNameStr_l[15];
  char_T ParameterNameStr_j[14];
  char_T ParameterNameStr_d[13];
  char_T ParameterNameStr_g[12];
  real32_T PD[3];
  real32_T b_ei[3];
  real32_T b2d_cross[3];
  real32_T ParamStep_l[3];
  real32_T ParamStep_d[3];
  real32_T fv[3];
  real32_T R_err_tmp_d[3];
  real32_T fv1[3];
  char_T b_SCIModuleLoc[11];
  char_T ParameterNameStr_lx[10];
  char_T ParameterNameStr_o[9];
  char_T x[8];
  char_T sfull[8];
  MW_PARAM_DATA_TYPE ParamDataType;
  char_T ParameterNameStr_b[8];
  uint32_T RxPinLoc;
  uint32_T TxPinLoc;
  void* SCIModuleVoidPtr;
  real_T Gain1;                        // '<S10>/Gain1'
  real_T K12;
  real_T K13;
  real_T K14;
  real_T K23;
  real_T K24;
  real_T K34;
  real_T f_ext;                        // '<Root>/Gain'
  real_T Divide;                       // '<Root>/Divide'
  real_T time;                         // '<Root>/Digital Clock'
  real_T rtb_q_drone_idx_0;
  real_T tempR_tmp;
  real_T q_tmp;
  real_T q_tmp_n;
  real_T q_tmp_b;
  real_T anrm;
  real_T vtemp;
  real_T b_absxk;
  real_T cfromc;
  real_T ctoc;
  real_T cto1;
  real_T stemp_im_tmp;
  real_T anorm;
  real_T b_atol;
  real_T temp;
  real_T temp2;
  real_T ar;
  real_T ai;
  real_T stemp_re;
  real_T stemp_im;
  real_T t1_re;
  real_T t1_im;
  real_T shift_im;
  real_T eshift_re;
  real_T eshift_im;
  real_T shift_tmp;
  real_T g2;
  real_T f2s;
  real_T di;
  real_T scale;
  real_T x_l;
  real_T fs_re;
  real_T fs_im;
  real_T gs_re;
  real_T gs_im;
  real_T a;
  real_T tst;
  real_T htmp1;
  real_T ab;
  real_T ba;
  real_T aa;
  real_T h12;
  real_T h21s;
  real_T sn;
  real_T s_tmp;
  real_T p;
  real_T bcmax;
  real_T bcmis;
  real_T scale_h;
  real_T z;
  real_T tau_b;
  real_T sts;
  real_T anorm_d;
  real_T ascale_e;
  real_T temp_b;
  real_T acoeff;
  real_T scale_j;
  real_T dmin;
  real_T e_y;
  real_T salpha_re;
  real_T salpha_im;
  real_T work2_idx_2_im;
  real_T work2_idx_3_re;
  real_T work2_idx_3_im;
  real_T work2_idx_0_re_tmp;
  real_T work2_idx_0_re_tmp_f;
  real_T alpha1;
  real_T xnorm;
  real_T c_a;
  real_T g2_j;
  real_T d;
  real_T f2s_j;
  real_T scale_o;
  real_T x_n;
  real_T fs_re_i;
  real_T fs_im_o;
  real_T gs_re_n;
  real_T gs_im_m;
  real_T scale_c;
  real_T ssq;
  real_T colscale;
  real_T colssq;
  real_T absxk;
  real_T t;
  real_T xnorm_m;
  real_T a_m;
  real_T scale_ja;
  real_T absxk_h;
  real_T t_c;
  real_T atmp_re;
  real_T atmp_im;
  real_T scale_ct;
  real_T absxk_p;
  real_T t_p;
  real_T temp_a;
  real_T temp_e;
  real_T absxr;
  real_T absxi;
  real_T temp_ax;
  real_T temp_tmp;
  real_T x_a;
  uint64_T p2;
  uint64_T a_i;
  real32_T ParamStep_lt;
  real32_T ParamStep_o;
  real32_T ParamStep_o2;
  real32_T ParamStep_i;
  real32_T ParamStep_f;
  real32_T ParamStep_iz;
  real32_T ParamStep_ff;
  real32_T ParamStep_g;
  real32_T ParamStep_co;
  real32_T ParamStep_o3;
  real32_T ParamStep_lm;
  real32_T ParamStep_m;
  real32_T ParamStep_mj;
  real32_T ParamStep_cn;
  real32_T ParamStep_fm;
  real32_T ParamStep_p;
  real32_T ParamStep_e;
  real32_T ParamStep_o4;
  real32_T ParamStep_h;
  real32_T ParamStep_l5;
  real32_T ParamStep_h2;
  real32_T ParamStep_me;
  real32_T ParamStep_mc;
  real32_T ParamStep_h3;
  real32_T ParamStep_cs;
  real32_T ParamStep_k;
  real32_T ParamStep_pc;
  real32_T ParamStep_px;
  int32_T npad;
  int32_T idx;
  int32_T pmax;
  int32_T pmin;
  int32_T pow2p;
  int32_T b_k;
  int32_T jrow;
  int32_T jcol;
  int32_T b_j;
  int32_T c_i;
  int32_T stemp_re_tmp;
  int32_T stemp_re_tmp_p;
  int32_T j;
  int32_T ifirst;
  int32_T istart;
  int32_T ilast;
  int32_T ilastm1;
  int32_T iiter;
  int32_T jp1;
  int32_T jiter;
  int32_T ctemp_tmp;
  int32_T ctemp_tmp_tmp;
  int32_T stemp_re_tmp_a;
  int32_T rescaledir;
  int32_T count;
  int32_T b_i;
  int32_T i;
  int32_T L;
  int32_T k;
  int32_T m;
  int32_T nr;
  int32_T hoffset;
  int32_T its;
  int32_T c_j;
  int32_T s_tmp_j;
  int32_T sum1_tmp;
  int32_T m_tmp;
  int32_T b;
  int32_T c_e;
  int32_T i_o;
  int32_T e_jr;
  int32_T b_x_tmp;
  int32_T b_x_tmp_tmp;
  int32_T d_re_tmp;
  int32_T work2_idx_0_re_tmp_b;
  int32_T knt;
  int32_T lastc;
  int32_T ix;
  int32_T iac;
  int32_T e;
  int32_T ia;
  int32_T jy;
  int32_T b_ix;
  int32_T lastv;
  int32_T lastc_a;
  int32_T ix_g;
  int32_T iac_e;
  int32_T d_f;
  int32_T ia_h;
  int32_T coltop;
  int32_T nm1;
  int32_T col;
  int32_T j_e;
  int32_T row;
  int32_T j_c;
  int32_T absxk_tmp;
  int32_T knt_a;
  int32_T b_k_d;
  int32_T k_a;
  int32_T i_p;
  int32_T j_m;
  int32_T ii;
  int32_T nzcount;
  int32_T jj;
  int32_T atmp_re_tmp_tmp;
  int32_T kend;
  int32_T ix_o;
  int32_T iy;
  int32_T k_n;
  int32_T ix_l;
  int32_T iy_p;
  int32_T k_p;
  int32_T k_f;
  int32_T u0;
  uint8_T RxDataLocChar[2];
  uint16_T status;
  uint16_T u;
  uint16_T u1;
  uint16_T u2;
  int8_T RxData[2];
  char_T padval;
  uint8_T sizeptr;
  boolean_T carry;
  boolean_T b_varargout_2_i;
  boolean_T NOT;                       // '<Root>/NOT'
  boolean_T pos_flag;                  // '<S4>/MATLAB Function'
  boolean_T ilascl;
  boolean_T notdone;
};

// Block states (default storage) for system '<Root>'
struct DW_lee_controller_T {
  px4_internal_block_ParameterU_T obj; // '<S42>/Read Parameter9'
  px4_internal_block_ParameterU_T obj_b;// '<S42>/Read Parameter8'
  px4_internal_block_ParameterU_T obj_m;// '<S42>/Read Parameter7'
  px4_internal_block_ParameterU_T obj_p;// '<S42>/Read Parameter6'
  px4_internal_block_ParameterU_T obj_a;// '<S42>/Read Parameter5'
  px4_internal_block_ParameterU_T obj_n;// '<S42>/Read Parameter43'
  px4_internal_block_ParameterU_T obj_l;// '<S42>/Read Parameter42'
  px4_internal_block_ParameterU_T obj_o;// '<S42>/Read Parameter41'
  px4_internal_block_ParameterU_T obj_f;// '<S42>/Read Parameter40'
  px4_internal_block_ParameterU_T obj_k;// '<S42>/Read Parameter4'
  px4_internal_block_ParameterU_T obj_ma;// '<S42>/Read Parameter39'
  px4_internal_block_ParameterU_T obj_lj;// '<S42>/Read Parameter38'
  px4_internal_block_ParameterU_T obj_mt;// '<S42>/Read Parameter37'
  px4_internal_block_ParameterU_T obj_c;// '<S42>/Read Parameter36'
  px4_internal_block_ParameterU_T obj_k4;// '<S42>/Read Parameter35'
  px4_internal_block_ParameterU_T obj_h;// '<S42>/Read Parameter34'
  px4_internal_block_ParameterU_T obj_e;// '<S42>/Read Parameter33'
  px4_internal_block_ParameterU_T obj_ng;// '<S42>/Read Parameter32'
  px4_internal_block_ParameterU_T obj_el;// '<S42>/Read Parameter31'
  px4_internal_block_ParameterU_T obj_pd;// '<S42>/Read Parameter30'
  px4_internal_block_ParameterU_T obj_ph;// '<S42>/Read Parameter3'
  px4_internal_block_ParameterU_T obj_lb;// '<S42>/Read Parameter29'
  px4_internal_block_ParameterU_T obj_ne;// '<S42>/Read Parameter28'
  px4_internal_block_ParameterU_T obj_pq;// '<S42>/Read Parameter27'
  px4_internal_block_ParameterU_T obj_og;// '<S42>/Read Parameter26'
  px4_internal_block_ParameterU_T obj_o1;// '<S42>/Read Parameter25'
  px4_internal_block_ParameterU_T obj_hi;// '<S42>/Read Parameter24'
  px4_internal_block_ParameterU_T obj_ni;// '<S42>/Read Parameter23'
  px4_internal_block_ParameterU_T obj_k3;// '<S42>/Read Parameter22'
  px4_internal_block_ParameterU_T obj_i;// '<S42>/Read Parameter21'
  px4_internal_block_ParameterU_T obj_hl;// '<S42>/Read Parameter20'
  px4_internal_block_ParameterU_T obj_ef;// '<S42>/Read Parameter2'
  px4_internal_block_ParameterU_T obj_nu;// '<S42>/Read Parameter19'
  px4_internal_block_ParameterU_T obj_n3;// '<S42>/Read Parameter18'
  px4_internal_block_ParameterU_T obj_fy;// '<S42>/Read Parameter17'
  px4_internal_block_ParameterU_T obj_j;// '<S42>/Read Parameter16'
  px4_internal_block_ParameterU_T obj_pv;// '<S42>/Read Parameter15'
  px4_internal_block_ParameterU_T obj_hh;// '<S42>/Read Parameter14'
  px4_internal_block_ParameterU_T obj_js;// '<S42>/Read Parameter13'
  px4_internal_block_ParameterU_T obj_aw;// '<S42>/Read Parameter12'
  px4_internal_block_ParameterU_T obj_bh;// '<S42>/Read Parameter11'
  px4_internal_block_ParameterU_T obj_cm;// '<S42>/Read Parameter10'
  px4_internal_block_ParameterU_T obj_kp;// '<S42>/Read Parameter1'
  px4_internal_block_ParameterU_T obj_mf;// '<S42>/Read Parameter'
  px4_internal_block_PX4SCIRead_T obj_cc;// '<Root>/Serial Receive1'
  px4_internal_block_PWM_lee_co_T obj_co;// '<S1>/PX4 PWM Output'
  px4_internal_block_Subscriber_T obj_mfw;// '<S52>/SourceBlock'
  px4_internal_block_Subscriber_T obj_oh;// '<S51>/SourceBlock'
  px4_internal_block_Subscriber_T obj_fp;// '<S47>/SourceBlock'
  px4_internal_block_Subscriber_T obj_kw;// '<S43>/SourceBlock'
  px4_internal_block_Subscriber_T obj_l5;// '<S26>/SourceBlock'
  px4_internal_block_Subscriber_T obj_d;// '<S25>/SourceBlock'
  px4_internal_block_Subscriber_T obj_awb;// '<S24>/SourceBlock'
  px4_internal_block_Publisher__T obj_bv;// '<S7>/SinkBlock'
  px4_internal_block_Publisher__T obj_cs;// '<S37>/SinkBlock'
  px4_internal_block_Publisher__T obj_lu;// '<S36>/SinkBlock'
  px4_internal_block_Publisher__T obj_cg;// '<S35>/SinkBlock'
  real_T DiscreteTimeIntegrator1_DSTATE;// '<Root>/Discrete-Time Integrator1'
  real_T DiscreteTimeIntegrator_DSTATE;// '<Root>/Discrete-Time Integrator'
};

// Zero-crossing (trigger) state
struct PrevZCX_lee_controller_T {
  ZCSigState Subsystem1_Trig_ZCE;      // '<Root>/Subsystem1'
};

// Parameters (default storage)
struct P_lee_controller_T_ {
  real_T A_inv[16];                    // Variable: A_inv
                                          //  Referenced by:
                                          //    '<S2>/rpm allocation'
                                          //    '<S5>/rpm_pos allocation'

  real_T dt;                           // Variable: dt
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

  real_T ei[3];                        // Variable: ei
                                          //  Referenced by: '<S5>/lee pos'

  real_T eir[3];                       // Variable: eir
                                          //  Referenced by: '<S5>/lee att'

  real_T g;                            // Variable: g
                                          //  Referenced by: '<S5>/lee pos'

  real_T pitch_offset;                 // Variable: pitch_offset
                                          //  Referenced by: '<S18>/Constant'

  real_T roll_offset;                  // Variable: roll_offset
                                          //  Referenced by: '<S17>/Constant'

  real_T thrust_offset;                // Variable: thrust_offset
                                          //  Referenced by: '<S16>/Constant'

  real_T yaw_offset;                   // Variable: yaw_offset
                                          //  Referenced by: '<S19>/Constant'

  px4_Bus_vehicle_local_position Out1_Y0;// Computed Parameter: Out1_Y0
                                            //  Referenced by: '<S27>/Out1'

  px4_Bus_vehicle_local_position Constant_Value;// Computed Parameter: Constant_Value
                                                   //  Referenced by: '<S24>/Constant'

  px4_Bus_input_rc Out1_Y0_f;          // Computed Parameter: Out1_Y0_f
                                          //  Referenced by: '<S48>/Out1'

  px4_Bus_input_rc Constant_Value_d;   // Computed Parameter: Constant_Value_d
                                          //  Referenced by: '<S47>/Constant'

  px4_Bus_traj_setpoint Out1_Y0_p;     // Computed Parameter: Out1_Y0_p
                                          //  Referenced by: '<S46>/Out1'

  px4_Bus_traj_setpoint Constant_Value_e;// Computed Parameter: Constant_Value_e
                                            //  Referenced by: '<S43>/Constant'

  px4_Bus_vehicle_attitude Out1_Y0_m;  // Computed Parameter: Out1_Y0_m
                                          //  Referenced by: '<S28>/Out1'

  px4_Bus_vehicle_attitude Constant_Value_i;// Computed Parameter: Constant_Value_i
                                               //  Referenced by: '<S25>/Constant'

  px4_Bus_linear_err Constant_Value_in;// Computed Parameter: Constant_Value_in
                                          //  Referenced by: '<S32>/Constant'

  px4_Bus_vehicle_angular_velocity Out1_Y0_o;// Computed Parameter: Out1_Y0_o
                                                //  Referenced by: '<S29>/Out1'

  px4_Bus_vehicle_angular_velocity Constant_Value_b;// Computed Parameter: Constant_Value_b
                                                       //  Referenced by: '<S26>/Constant'

  px4_Bus_act_wrench Constant_Value_n; // Computed Parameter: Constant_Value_n
                                          //  Referenced by: '<S34>/Constant'

  px4_Bus_actuator_armed Out1_Y0_d;    // Computed Parameter: Out1_Y0_d
                                          //  Referenced by: '<S53>/Out1'

  px4_Bus_actuator_armed Constant_Value_h;// Computed Parameter: Constant_Value_h
                                             //  Referenced by: '<S51>/Constant'

  px4_Bus_admittance Constant_Value_k; // Computed Parameter: Constant_Value_k
                                          //  Referenced by: '<S6>/Constant'

  px4_Bus_ang_err Constant_Value_k4;   // Computed Parameter: Constant_Value_k4
                                          //  Referenced by: '<S33>/Constant'

  px4_Bus_commander_state Out1_Y0_j;   // Computed Parameter: Out1_Y0_j
                                          //  Referenced by: '<S54>/Out1'

  px4_Bus_commander_state Constant_Value_f;// Computed Parameter: Constant_Value_f
                                              //  Referenced by: '<S52>/Constant'

  real_T rpm_Y0;                       // Computed Parameter: rpm_Y0
                                          //  Referenced by: '<S2>/rpm'

  real_T Saturation10_UpperSat;        // Expression: 1
                                          //  Referenced by: '<S16>/Saturation10'

  real_T Saturation10_LowerSat;        // Expression: 0
                                          //  Referenced by: '<S16>/Saturation10'

  real_T Saturation9_UpperSat;         // Expression: 1
                                          //  Referenced by: '<S19>/Saturation9'

  real_T Saturation9_LowerSat;         // Expression: -1
                                          //  Referenced by: '<S19>/Saturation9'

  real_T Saturation9_UpperSat_h;       // Expression: 1
                                          //  Referenced by: '<S17>/Saturation9'

  real_T Saturation9_LowerSat_h;       // Expression: -1
                                          //  Referenced by: '<S17>/Saturation9'

  real_T Saturation9_UpperSat_e;       // Expression: 1
                                          //  Referenced by: '<S18>/Saturation9'

  real_T Saturation9_LowerSat_f;       // Expression: -1
                                          //  Referenced by: '<S18>/Saturation9'

  real_T des_yaw_from_RC_Value;        // Expression: 0.0
                                          //  Referenced by: '<S2>/des_yaw_from_RC'

  real_T rpm_Y0_l;                     // Computed Parameter: rpm_Y0_l
                                          //  Referenced by: '<S5>/rpm'

  real_T kg_Y0;                        // Computed Parameter: kg_Y0
                                          //  Referenced by: '<S10>/kg'

  real_T Gain1_Gain;                   // Expression: 0.001
                                          //  Referenced by: '<S10>/Gain1'

  real_T DiscreteTimeIntegrator1_gainval;
                          // Computed Parameter: DiscreteTimeIntegrator1_gainval
                             //  Referenced by: '<Root>/Discrete-Time Integrator1'

  real_T DiscreteTimeIntegrator1_IC;   // Expression: 0
                                          //  Referenced by: '<Root>/Discrete-Time Integrator1'

  real_T DiscreteTimeIntegrator_gainval;
                           // Computed Parameter: DiscreteTimeIntegrator_gainval
                              //  Referenced by: '<Root>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator_IC;    // Expression: 0
                                          //  Referenced by: '<Root>/Discrete-Time Integrator'

  real_T Gain_Gain;                    // Expression: -9.81
                                          //  Referenced by: '<Root>/Gain'

  int16_T Gain_Gain_k;                 // Computed Parameter: Gain_Gain_k
                                          //  Referenced by: '<S10>/Gain'

  uint16_T Saturationpwm_UpperSat; // Computed Parameter: Saturationpwm_UpperSat
                                      //  Referenced by: '<S1>/Saturation pwm'

  uint16_T Saturationpwm_LowerSat; // Computed Parameter: Saturationpwm_LowerSat
                                      //  Referenced by: '<S1>/Saturation pwm'

  uint16_T Saturationpwm1_UpperSat;
                                  // Computed Parameter: Saturationpwm1_UpperSat
                                     //  Referenced by: '<S1>/Saturation pwm1'

  uint16_T Saturationpwm1_LowerSat;
                                  // Computed Parameter: Saturationpwm1_LowerSat
                                     //  Referenced by: '<S1>/Saturation pwm1'

};

// Real-time Model Data Structure
struct tag_RTM_lee_controller_T {
  const char_T * volatile errorStatus;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
  } Timing;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_lee_controller_T lee_controller_P;

#ifdef __cplusplus

}
#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern struct B_lee_controller_T lee_controller_B;

#ifdef __cplusplus

}
#endif

// Block states (default storage)
extern struct DW_lee_controller_T lee_controller_DW;

// Zero-crossing (trigger) state
extern PrevZCX_lee_controller_T lee_controller_PrevZCX;

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void lee_controller_initialize(void);
  extern void lee_controller_step(void);
  extern void lee_controller_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_lee_controller_T *const lee_controller_M;

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S2>/Scope8' : Unused code path elimination
//  Block '<S16>/Scope' : Unused code path elimination
//  Block '<S17>/Scope' : Unused code path elimination
//  Block '<S18>/Scope' : Unused code path elimination
//  Block '<S19>/Scope' : Unused code path elimination
//  Block '<S24>/NOT' : Unused code path elimination
//  Block '<S25>/NOT' : Unused code path elimination
//  Block '<S26>/NOT' : Unused code path elimination
//  Block '<S42>/Cast To Double41' : Unused code path elimination
//  Block '<S42>/Cast To Double42' : Unused code path elimination
//  Block '<S42>/Cast To Double43' : Unused code path elimination
//  Block '<S42>/Display' : Unused code path elimination
//  Block '<S42>/Display1' : Unused code path elimination
//  Block '<S42>/Display10' : Unused code path elimination
//  Block '<S42>/Display11' : Unused code path elimination
//  Block '<S42>/Display12' : Unused code path elimination
//  Block '<S42>/Display13' : Unused code path elimination
//  Block '<S42>/Display14' : Unused code path elimination
//  Block '<S42>/Display15' : Unused code path elimination
//  Block '<S42>/Display16' : Unused code path elimination
//  Block '<S42>/Display17' : Unused code path elimination
//  Block '<S42>/Display18' : Unused code path elimination
//  Block '<S42>/Display19' : Unused code path elimination
//  Block '<S42>/Display2' : Unused code path elimination
//  Block '<S42>/Display20' : Unused code path elimination
//  Block '<S42>/Display21' : Unused code path elimination
//  Block '<S42>/Display22' : Unused code path elimination
//  Block '<S42>/Display23' : Unused code path elimination
//  Block '<S42>/Display24' : Unused code path elimination
//  Block '<S42>/Display25' : Unused code path elimination
//  Block '<S42>/Display26' : Unused code path elimination
//  Block '<S42>/Display27' : Unused code path elimination
//  Block '<S42>/Display28' : Unused code path elimination
//  Block '<S42>/Display29' : Unused code path elimination
//  Block '<S42>/Display3' : Unused code path elimination
//  Block '<S42>/Display30' : Unused code path elimination
//  Block '<S42>/Display31' : Unused code path elimination
//  Block '<S42>/Display32' : Unused code path elimination
//  Block '<S42>/Display33' : Unused code path elimination
//  Block '<S42>/Display34' : Unused code path elimination
//  Block '<S42>/Display35' : Unused code path elimination
//  Block '<S42>/Display36' : Unused code path elimination
//  Block '<S42>/Display37' : Unused code path elimination
//  Block '<S42>/Display38' : Unused code path elimination
//  Block '<S42>/Display39' : Unused code path elimination
//  Block '<S42>/Display4' : Unused code path elimination
//  Block '<S42>/Display40' : Unused code path elimination
//  Block '<S42>/Display41' : Unused code path elimination
//  Block '<S42>/Display42' : Unused code path elimination
//  Block '<S42>/Display43' : Unused code path elimination
//  Block '<S42>/Display5' : Unused code path elimination
//  Block '<S42>/Display6' : Unused code path elimination
//  Block '<S42>/Display7' : Unused code path elimination
//  Block '<S42>/Display8' : Unused code path elimination
//  Block '<S42>/Display9' : Unused code path elimination
//  Block '<Root>/Scope' : Unused code path elimination
//  Block '<S43>/NOT' : Unused code path elimination
//  Block '<S44>/Bitwise Operator' : Unused code path elimination
//  Block '<S44>/Data Type Conversion' : Unused code path elimination
//  Block '<S44>/Data Type Conversion1' : Unused code path elimination
//  Block '<S44>/Data Type Conversion2' : Unused code path elimination
//  Block '<S44>/Gain' : Unused code path elimination
//  Block '<S44>/Gain1' : Unused code path elimination
//  Block '<S47>/NOT' : Unused code path elimination
//  Block '<S9>/Scope3' : Unused code path elimination
//  Block '<S10>/Scope' : Unused code path elimination
//  Block '<S10>/Scope1' : Unused code path elimination
//  Block '<S51>/NOT' : Unused code path elimination
//  Block '<S52>/NOT' : Unused code path elimination
//  Block '<Root>/Cast To Single3' : Eliminate redundant data type conversion
//  Block '<Root>/Cast To Single4' : Eliminate redundant data type conversion
//  Block '<Root>/Cast To Single5' : Eliminate redundant data type conversion
//  Block '<S2>/Cast To Double' : Eliminate redundant data type conversion
//  Block '<S2>/Cast To Double1' : Eliminate redundant data type conversion
//  Block '<S2>/Cast To Double2' : Eliminate redundant data type conversion
//  Block '<S2>/Cast To Double3' : Eliminate redundant data type conversion
//  Block '<S5>/Cast To Single1' : Eliminate redundant data type conversion
//  Block '<S5>/Cast To Single2' : Eliminate redundant data type conversion
//  Block '<S5>/Cast To Single3' : Eliminate redundant data type conversion
//  Block '<S5>/Cast To Single4' : Eliminate redundant data type conversion


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'lee_controller'
//  '<S1>'   : 'lee_controller/Drone_pwm_converter'
//  '<S2>'   : 'lee_controller/Enabled Subsystem1'
//  '<S3>'   : 'lee_controller/Feedback'
//  '<S4>'   : 'lee_controller/Flight_modes_switch'
//  '<S5>'   : 'lee_controller/LEE_CONTROLLER'
//  '<S6>'   : 'lee_controller/PX4 uORB Message'
//  '<S7>'   : 'lee_controller/PX4 uORB Write'
//  '<S8>'   : 'lee_controller/Read Params from QGround'
//  '<S9>'   : 'lee_controller/Setpoints'
//  '<S10>'  : 'lee_controller/Subsystem1'
//  '<S11>'  : 'lee_controller/mode sw'
//  '<S12>'  : 'lee_controller/uORB_reads'
//  '<S13>'  : 'lee_controller/Drone_pwm_converter/MATLAB Function1'
//  '<S14>'  : 'lee_controller/Drone_pwm_converter/MATLAB Function4'
//  '<S15>'  : 'lee_controller/Enabled Subsystem1/att control'
//  '<S16>'  : 'lee_controller/Enabled Subsystem1/convert_thrust'
//  '<S17>'  : 'lee_controller/Enabled Subsystem1/convert_to_1_-1'
//  '<S18>'  : 'lee_controller/Enabled Subsystem1/convert_to_1_-2'
//  '<S19>'  : 'lee_controller/Enabled Subsystem1/convert_to_1_-3'
//  '<S20>'  : 'lee_controller/Enabled Subsystem1/inv alloc_matrix'
//  '<S21>'  : 'lee_controller/Enabled Subsystem1/rate control'
//  '<S22>'  : 'lee_controller/Enabled Subsystem1/rpm allocation'
//  '<S23>'  : 'lee_controller/Feedback/MATLAB Function'
//  '<S24>'  : 'lee_controller/Feedback/PX4 uORB Read1'
//  '<S25>'  : 'lee_controller/Feedback/PX4 uORB Read2'
//  '<S26>'  : 'lee_controller/Feedback/PX4 uORB Read3'
//  '<S27>'  : 'lee_controller/Feedback/PX4 uORB Read1/Enabled Subsystem'
//  '<S28>'  : 'lee_controller/Feedback/PX4 uORB Read2/Enabled Subsystem'
//  '<S29>'  : 'lee_controller/Feedback/PX4 uORB Read3/Enabled Subsystem'
//  '<S30>'  : 'lee_controller/Flight_modes_switch/MATLAB Function'
//  '<S31>'  : 'lee_controller/LEE_CONTROLLER/MATLAB Function4'
//  '<S32>'  : 'lee_controller/LEE_CONTROLLER/PX4 uORB Message'
//  '<S33>'  : 'lee_controller/LEE_CONTROLLER/PX4 uORB Message1'
//  '<S34>'  : 'lee_controller/LEE_CONTROLLER/PX4 uORB Message2'
//  '<S35>'  : 'lee_controller/LEE_CONTROLLER/PX4 uORB Write'
//  '<S36>'  : 'lee_controller/LEE_CONTROLLER/PX4 uORB Write1'
//  '<S37>'  : 'lee_controller/LEE_CONTROLLER/PX4 uORB Write2'
//  '<S38>'  : 'lee_controller/LEE_CONTROLLER/inv alloc_matrix'
//  '<S39>'  : 'lee_controller/LEE_CONTROLLER/lee att'
//  '<S40>'  : 'lee_controller/LEE_CONTROLLER/lee pos'
//  '<S41>'  : 'lee_controller/LEE_CONTROLLER/rpm_pos allocation'
//  '<S42>'  : 'lee_controller/Read Params from QGround/Read_Parameters'
//  '<S43>'  : 'lee_controller/Setpoints/PX4 uORB Read1'
//  '<S44>'  : 'lee_controller/Setpoints/Radio Control Transmitter'
//  '<S45>'  : 'lee_controller/Setpoints/kill sw'
//  '<S46>'  : 'lee_controller/Setpoints/PX4 uORB Read1/Enabled Subsystem'
//  '<S47>'  : 'lee_controller/Setpoints/Radio Control Transmitter/PX4 uORB Read'
//  '<S48>'  : 'lee_controller/Setpoints/Radio Control Transmitter/PX4 uORB Read/Enabled Subsystem'
//  '<S49>'  : 'lee_controller/Subsystem1/Bit sign'
//  '<S50>'  : 'lee_controller/uORB_reads/MATLAB Function'
//  '<S51>'  : 'lee_controller/uORB_reads/PX4 uORB Read'
//  '<S52>'  : 'lee_controller/uORB_reads/PX4 uORB Read3'
//  '<S53>'  : 'lee_controller/uORB_reads/PX4 uORB Read/Enabled Subsystem'
//  '<S54>'  : 'lee_controller/uORB_reads/PX4 uORB Read3/Enabled Subsystem'

#endif                                 // RTW_HEADER_lee_controller_h_

//
// File trailer for generated code.
//
// [EOF]
//
