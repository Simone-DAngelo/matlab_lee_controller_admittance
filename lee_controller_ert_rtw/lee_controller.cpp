//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: lee_controller.cpp
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

// Block signals (default storage)
B_lee_controller_T lee_controller_B;

// Block states (default storage)
DW_lee_controller_T lee_controller_DW;

// Previous zero-crossings (trigger) states
PrevZCX_lee_controller_T lee_controller_PrevZCX;

// Real-time model
RT_MODEL_lee_controller_T lee_controller_M_ = RT_MODEL_lee_controller_T();
RT_MODEL_lee_controller_T *const lee_controller_M = &lee_controller_M_;

// Forward declaration for local functions
static real_T lee_controller_rt_atan2d_snf(real_T u0, real_T u1);
static boolean_T lee_controller_anyNonFinite(const real_T x[16]);
static real_T lee_controller_rt_hypotd_snf(real_T u0, real_T u1);
static void lee_controller_xzggbal(creal_T A[16], int32_T *ilo, int32_T *ihi,
  int32_T rscale[4]);
static real_T lee_controller_xzlanhs(const creal_T A[16], int32_T ilo, int32_T
  ihi);
static void lee_controller_sqrt(creal_T *x);
static void lee_controller_xzlartg_g(const creal_T f, const creal_T g, real_T
  *cs, creal_T *sn);
static void lee_controller_xzlartg(const creal_T f, const creal_T g, real_T *cs,
  creal_T *sn, creal_T *r);
static void lee_controller_xzhgeqz(creal_T A[16], int32_T ilo, int32_T ihi,
  creal_T Z[16], int32_T *info, creal_T alpha1[4], creal_T beta1[4]);
static void lee_controller_xztgevc(const creal_T A[16], creal_T V[16]);
static void lee_controller_eigStandard(const real_T A[16], creal_T V[16],
  creal_T D[4]);
static real_T lee_controller_xnrm2(int32_T n, const real_T x[16], int32_T ix0);
static void lee_controller_xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[16], int32_T ic0, real_T work[4]);
static void lee_controller_xgehrd(real_T a[16], real_T tau[3]);
static real_T lee_controller_xnrm2_l(int32_T n, const real_T x[3]);
static real_T lee_controller_xzlarfg(int32_T n, real_T *alpha1, real_T x[3]);
static void lee_controller_xdlanv2(real_T *a, real_T *b, real_T *c, real_T *d,
  real_T *rt1r, real_T *rt1i, real_T *rt2r, real_T *rt2i, real_T *cs, real_T *sn);
static void lee_controller_xrot(int32_T n, real_T x[16], int32_T ix0, int32_T
  iy0, real_T c, real_T s);
static void lee_controller_xrot_g(int32_T n, real_T x[16], int32_T ix0, int32_T
  iy0, real_T c, real_T s);
static void lee_controller_xrot_g5(real_T x[16], int32_T ix0, int32_T iy0,
  real_T c, real_T s);
static int32_T lee_controller_eml_dlahqr(real_T h[16], real_T z[16]);
static void lee_controller_schur(const real_T A[16], real_T V[16], real_T T[16]);
static void lee_controll_SystemCore_setup_g(px4_internal_block_PX4SCIRead_T *obj);
static void lee_controller_SystemCore_setup(px4_internal_block_PWM_lee_co_T *obj,
  boolean_T varargin_1, boolean_T varargin_2);

//
// Output and update for atomic system:
//    '<S2>/inv alloc_matrix'
//    '<S5>/inv alloc_matrix'
//
void lee_controller_invalloc_matrix(real_T rtu_kf, real_T rtu_km, real_T
  rtu_l_arm, real_T rty_inv_A[16])
{
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  real_T tmp_2;
  tmp_0 = -1.0 / (4.0 * rtu_kf);
  rty_inv_A[0] = tmp_0;
  tmp = 4.0 * rtu_l_arm * rtu_kf;
  tmp_1 = -1.4142135623730951 / tmp;
  rty_inv_A[4] = tmp_1;
  tmp = 1.4142135623730951 / tmp;
  rty_inv_A[8] = tmp;
  tmp_2 = 1.0 / (4.0 * rtu_km);
  rty_inv_A[12] = tmp_2;
  rty_inv_A[1] = tmp_0;
  rty_inv_A[5] = tmp;
  rty_inv_A[9] = tmp_1;
  rty_inv_A[13] = tmp_2;
  rty_inv_A[2] = tmp_0;
  rty_inv_A[6] = tmp;
  rty_inv_A[10] = tmp;
  tmp = -1.0 / (4.0 * rtu_km);
  rty_inv_A[14] = tmp;
  rty_inv_A[3] = tmp_0;
  rty_inv_A[7] = tmp_1;
  rty_inv_A[11] = tmp_1;
  rty_inv_A[15] = tmp;
}

//
// Output and update for atomic system:
//    '<S2>/rpm allocation'
//    '<S5>/rpm_pos allocation'
//
void lee_controller_rpmallocation(real_T rtu_f, const real_T rtu_M[3], const
  real_T rtu_inv_A[16], real_T rty_rpm[4])
{
  real_T radsec_squared[4];
  real_T b_idx_1;
  real_T b_idx_2;
  real_T b_idx_3;
  b_idx_1 = rtu_M[0];
  b_idx_2 = rtu_M[1];
  b_idx_3 = rtu_M[2];
  for (int32_T i = 0; i < 4; i++) {
    radsec_squared[i] = ((rtu_inv_A[i + 4] * b_idx_1 + rtu_inv_A[i] * -rtu_f) +
                         rtu_inv_A[i + 8] * b_idx_2) + rtu_inv_A[i + 12] *
      b_idx_3;
  }

  if (rtu_f <= 0.05) {
    rty_rpm[0] = 0.0;
    rty_rpm[1] = 0.0;
    rty_rpm[2] = 0.0;
    rty_rpm[3] = 0.0;
  } else {
    if (radsec_squared[0] > 0.0) {
      rty_rpm[0] = sqrt(radsec_squared[0]);
    } else {
      rty_rpm[0] = 0.0;
    }

    rty_rpm[0] *= 9.54;
    if (radsec_squared[1] > 0.0) {
      rty_rpm[1] = sqrt(radsec_squared[1]);
    } else {
      rty_rpm[1] = 0.0;
    }

    rty_rpm[1] *= 9.54;
    if (radsec_squared[2] > 0.0) {
      rty_rpm[2] = sqrt(radsec_squared[2]);
    } else {
      rty_rpm[2] = 0.0;
    }

    rty_rpm[2] *= 9.54;
    if (radsec_squared[3] > 0.0) {
      rty_rpm[3] = sqrt(radsec_squared[3]);
    } else {
      rty_rpm[3] = 0.0;
    }

    rty_rpm[3] *= 9.54;
  }
}

static real_T lee_controller_rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T u1_0;
    if (u0 > 0.0) {
      lee_controller_B.u0 = 1;
    } else {
      lee_controller_B.u0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(static_cast<real_T>(lee_controller_B.u0), static_cast<real_T>(u1_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

// Function for MATLAB Function: '<S2>/att control'
static boolean_T lee_controller_anyNonFinite(const real_T x[16])
{
  boolean_T b_p;
  b_p = true;
  for (lee_controller_B.k_f = 0; lee_controller_B.k_f < 16; lee_controller_B.k_f
       ++) {
    lee_controller_B.x_a = x[lee_controller_B.k_f];
    if (b_p && (rtIsInf(lee_controller_B.x_a) || rtIsNaN(lee_controller_B.x_a)))
    {
      b_p = false;
    }
  }

  return !b_p;
}

static real_T lee_controller_rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T y;
  lee_controller_B.a = fabs(u0);
  y = fabs(u1);
  if (lee_controller_B.a < y) {
    lee_controller_B.a /= y;
    y *= sqrt(lee_controller_B.a * lee_controller_B.a + 1.0);
  } else if (lee_controller_B.a > y) {
    y /= lee_controller_B.a;
    y = sqrt(y * y + 1.0) * lee_controller_B.a;
  } else if (!rtIsNaN(y)) {
    y = lee_controller_B.a * 1.4142135623730951;
  }

  return y;
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xzggbal(creal_T A[16], int32_T *ilo, int32_T *ihi,
  int32_T rscale[4])
{
  int32_T exitg2;
  boolean_T exitg3;
  boolean_T exitg4;
  boolean_T found;
  *ihi = 4;
  rscale[0] = 1;
  rscale[1] = 1;
  rscale[2] = 1;
  rscale[3] = 1;
  *ilo = 1;
  do {
    exitg2 = 0;
    lee_controller_B.i_p = 0;
    lee_controller_B.j_m = 0;
    found = false;
    lee_controller_B.ii = *ihi;
    exitg3 = false;
    while ((!exitg3) && (lee_controller_B.ii > 0)) {
      lee_controller_B.nzcount = 0;
      lee_controller_B.i_p = lee_controller_B.ii;
      lee_controller_B.j_m = *ihi;
      lee_controller_B.jj = 0;
      exitg4 = false;
      while ((!exitg4) && (lee_controller_B.jj <= *ihi - 1)) {
        lee_controller_B.atmp_re_tmp_tmp = ((lee_controller_B.jj << 2) +
          lee_controller_B.ii) - 1;
        if ((A[lee_controller_B.atmp_re_tmp_tmp].re != 0.0) ||
            (A[lee_controller_B.atmp_re_tmp_tmp].im != 0.0) ||
            (lee_controller_B.jj + 1 == lee_controller_B.ii)) {
          if (lee_controller_B.nzcount == 0) {
            lee_controller_B.j_m = lee_controller_B.jj + 1;
            lee_controller_B.nzcount = 1;
            lee_controller_B.jj++;
          } else {
            lee_controller_B.nzcount = 2;
            exitg4 = true;
          }
        } else {
          lee_controller_B.jj++;
        }
      }

      if (lee_controller_B.nzcount < 2) {
        found = true;
        exitg3 = true;
      } else {
        lee_controller_B.ii--;
      }
    }

    if (!found) {
      exitg2 = 2;
    } else {
      if (lee_controller_B.i_p != *ihi) {
        lee_controller_B.atmp_re = A[lee_controller_B.i_p - 1].re;
        lee_controller_B.atmp_im = A[lee_controller_B.i_p - 1].im;
        A[lee_controller_B.i_p - 1] = A[*ihi - 1];
        A[*ihi - 1].re = lee_controller_B.atmp_re;
        A[*ihi - 1].im = lee_controller_B.atmp_im;
        lee_controller_B.atmp_re = A[lee_controller_B.i_p + 3].re;
        lee_controller_B.atmp_im = A[lee_controller_B.i_p + 3].im;
        A[lee_controller_B.i_p + 3] = A[*ihi + 3];
        A[*ihi + 3].re = lee_controller_B.atmp_re;
        A[*ihi + 3].im = lee_controller_B.atmp_im;
        lee_controller_B.atmp_re = A[lee_controller_B.i_p + 7].re;
        lee_controller_B.atmp_im = A[lee_controller_B.i_p + 7].im;
        A[lee_controller_B.i_p + 7] = A[*ihi + 7];
        A[*ihi + 7].re = lee_controller_B.atmp_re;
        A[*ihi + 7].im = lee_controller_B.atmp_im;
        lee_controller_B.atmp_re = A[lee_controller_B.i_p + 11].re;
        lee_controller_B.atmp_im = A[lee_controller_B.i_p + 11].im;
        A[lee_controller_B.i_p + 11] = A[*ihi + 11];
        A[*ihi + 11].re = lee_controller_B.atmp_re;
        A[*ihi + 11].im = lee_controller_B.atmp_im;
      }

      if (lee_controller_B.j_m != *ihi) {
        lee_controller_B.ii = 0;
        while (lee_controller_B.ii <= *ihi - 1) {
          lee_controller_B.i_p = ((lee_controller_B.j_m - 1) << 2) +
            lee_controller_B.ii;
          lee_controller_B.atmp_re = A[lee_controller_B.i_p].re;
          lee_controller_B.atmp_im = A[lee_controller_B.i_p].im;
          lee_controller_B.atmp_re_tmp_tmp = ((*ihi - 1) << 2) +
            lee_controller_B.ii;
          A[lee_controller_B.i_p] = A[lee_controller_B.atmp_re_tmp_tmp];
          A[lee_controller_B.atmp_re_tmp_tmp].re = lee_controller_B.atmp_re;
          A[lee_controller_B.atmp_re_tmp_tmp].im = lee_controller_B.atmp_im;
          lee_controller_B.ii++;
        }
      }

      rscale[*ihi - 1] = lee_controller_B.j_m;
      (*ihi)--;
      if (*ihi == 1) {
        rscale[0] = 1;
        exitg2 = 1;
      }
    }
  } while (exitg2 == 0);

  if (exitg2 == 1) {
  } else {
    int32_T exitg1;
    do {
      exitg1 = 0;
      lee_controller_B.ii = 0;
      lee_controller_B.j_m = 0;
      found = false;
      lee_controller_B.i_p = *ilo;
      exitg3 = false;
      while ((!exitg3) && (lee_controller_B.i_p <= *ihi)) {
        lee_controller_B.nzcount = 0;
        lee_controller_B.ii = *ihi;
        lee_controller_B.j_m = lee_controller_B.i_p;
        lee_controller_B.jj = *ilo;
        exitg4 = false;
        while ((!exitg4) && (lee_controller_B.jj <= *ihi)) {
          lee_controller_B.atmp_re_tmp_tmp = (((lee_controller_B.i_p - 1) << 2)
            + lee_controller_B.jj) - 1;
          if ((A[lee_controller_B.atmp_re_tmp_tmp].re != 0.0) ||
              (A[lee_controller_B.atmp_re_tmp_tmp].im != 0.0) ||
              (lee_controller_B.jj == lee_controller_B.i_p)) {
            if (lee_controller_B.nzcount == 0) {
              lee_controller_B.ii = lee_controller_B.jj;
              lee_controller_B.nzcount = 1;
              lee_controller_B.jj++;
            } else {
              lee_controller_B.nzcount = 2;
              exitg4 = true;
            }
          } else {
            lee_controller_B.jj++;
          }
        }

        if (lee_controller_B.nzcount < 2) {
          found = true;
          exitg3 = true;
        } else {
          lee_controller_B.i_p++;
        }
      }

      if (!found) {
        exitg1 = 1;
      } else {
        if (lee_controller_B.ii != *ilo) {
          lee_controller_B.nzcount = *ilo - 1;
          while (lee_controller_B.nzcount + 1 < 5) {
            lee_controller_B.atmp_re_tmp_tmp = lee_controller_B.nzcount << 2;
            lee_controller_B.i_p = (lee_controller_B.atmp_re_tmp_tmp +
              lee_controller_B.ii) - 1;
            lee_controller_B.atmp_re = A[lee_controller_B.i_p].re;
            lee_controller_B.atmp_im = A[lee_controller_B.i_p].im;
            lee_controller_B.atmp_re_tmp_tmp = (lee_controller_B.atmp_re_tmp_tmp
              + *ilo) - 1;
            A[lee_controller_B.i_p] = A[lee_controller_B.atmp_re_tmp_tmp];
            A[lee_controller_B.atmp_re_tmp_tmp].re = lee_controller_B.atmp_re;
            A[lee_controller_B.atmp_re_tmp_tmp].im = lee_controller_B.atmp_im;
            lee_controller_B.nzcount++;
          }
        }

        if (lee_controller_B.j_m != *ilo) {
          lee_controller_B.ii = 0;
          while (lee_controller_B.ii <= *ihi - 1) {
            lee_controller_B.i_p = ((lee_controller_B.j_m - 1) << 2) +
              lee_controller_B.ii;
            lee_controller_B.atmp_re = A[lee_controller_B.i_p].re;
            lee_controller_B.atmp_im = A[lee_controller_B.i_p].im;
            lee_controller_B.atmp_re_tmp_tmp = ((*ilo - 1) << 2) +
              lee_controller_B.ii;
            A[lee_controller_B.i_p] = A[lee_controller_B.atmp_re_tmp_tmp];
            A[lee_controller_B.atmp_re_tmp_tmp].re = lee_controller_B.atmp_re;
            A[lee_controller_B.atmp_re_tmp_tmp].im = lee_controller_B.atmp_im;
            lee_controller_B.ii++;
          }
        }

        rscale[*ilo - 1] = lee_controller_B.j_m;
        (*ilo)++;
        if (*ilo == *ihi) {
          rscale[*ilo - 1] = *ilo;
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

// Function for MATLAB Function: '<S2>/att control'
static real_T lee_controller_xzlanhs(const creal_T A[16], int32_T ilo, int32_T
  ihi)
{
  real_T f;
  f = 0.0;
  if (ilo <= ihi) {
    lee_controller_B.scale_c = 3.3121686421112381E-170;
    lee_controller_B.ssq = 0.0;
    lee_controller_B.nm1 = ihi - ilo;
    lee_controller_B.j_e = -1;
    while (lee_controller_B.j_e + 1 <= lee_controller_B.nm1) {
      lee_controller_B.colscale = 3.3121686421112381E-170;
      lee_controller_B.colssq = 0.0;
      lee_controller_B.col = ilo + lee_controller_B.j_e;
      if (lee_controller_B.j_e + 2 <= lee_controller_B.nm1) {
        lee_controller_B.j_c = lee_controller_B.j_e + 2;
      } else {
        lee_controller_B.j_c = lee_controller_B.nm1;
      }

      lee_controller_B.j_c += ilo;
      lee_controller_B.row = ilo;
      while (lee_controller_B.row <= lee_controller_B.j_c) {
        lee_controller_B.absxk_tmp = ((lee_controller_B.col << 2) +
          lee_controller_B.row) - 1;
        lee_controller_B.absxk = fabs(A[lee_controller_B.absxk_tmp].re);
        if (lee_controller_B.absxk > lee_controller_B.colscale) {
          lee_controller_B.t = lee_controller_B.colscale /
            lee_controller_B.absxk;
          lee_controller_B.colssq = lee_controller_B.colssq * lee_controller_B.t
            * lee_controller_B.t + 1.0;
          lee_controller_B.colscale = lee_controller_B.absxk;
        } else {
          lee_controller_B.t = lee_controller_B.absxk /
            lee_controller_B.colscale;
          lee_controller_B.colssq += lee_controller_B.t * lee_controller_B.t;
        }

        lee_controller_B.absxk = fabs(A[lee_controller_B.absxk_tmp].im);
        if (lee_controller_B.absxk > lee_controller_B.colscale) {
          lee_controller_B.t = lee_controller_B.colscale /
            lee_controller_B.absxk;
          lee_controller_B.colssq = lee_controller_B.colssq * lee_controller_B.t
            * lee_controller_B.t + 1.0;
          lee_controller_B.colscale = lee_controller_B.absxk;
        } else {
          lee_controller_B.t = lee_controller_B.absxk /
            lee_controller_B.colscale;
          lee_controller_B.colssq += lee_controller_B.t * lee_controller_B.t;
        }

        lee_controller_B.row++;
      }

      if (lee_controller_B.scale_c >= lee_controller_B.colscale) {
        lee_controller_B.colscale /= lee_controller_B.scale_c;
        lee_controller_B.ssq += lee_controller_B.colscale *
          lee_controller_B.colscale * lee_controller_B.colssq;
      } else {
        lee_controller_B.scale_c /= lee_controller_B.colscale;
        lee_controller_B.ssq = lee_controller_B.scale_c *
          lee_controller_B.scale_c * lee_controller_B.ssq +
          lee_controller_B.colssq;
        lee_controller_B.scale_c = lee_controller_B.colscale;
      }

      lee_controller_B.j_e++;
    }

    f = lee_controller_B.scale_c * sqrt(lee_controller_B.ssq);
  }

  return f;
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_sqrt(creal_T *x)
{
  if (x->im == 0.0) {
    if (x->re < 0.0) {
      lee_controller_B.absxr = 0.0;
      lee_controller_B.absxi = sqrt(-x->re);
    } else {
      lee_controller_B.absxr = sqrt(x->re);
      lee_controller_B.absxi = 0.0;
    }
  } else if (x->re == 0.0) {
    if (x->im < 0.0) {
      lee_controller_B.absxr = sqrt(-x->im / 2.0);
      lee_controller_B.absxi = -lee_controller_B.absxr;
    } else {
      lee_controller_B.absxr = sqrt(x->im / 2.0);
      lee_controller_B.absxi = lee_controller_B.absxr;
    }
  } else if (rtIsNaN(x->re)) {
    lee_controller_B.absxr = x->re;
    lee_controller_B.absxi = x->re;
  } else if (rtIsNaN(x->im)) {
    lee_controller_B.absxr = x->im;
    lee_controller_B.absxi = x->im;
  } else if (rtIsInf(x->im)) {
    lee_controller_B.absxr = fabs(x->im);
    lee_controller_B.absxi = x->im;
  } else if (rtIsInf(x->re)) {
    if (x->re < 0.0) {
      lee_controller_B.absxr = 0.0;
      lee_controller_B.absxi = x->im * -x->re;
    } else {
      lee_controller_B.absxr = x->re;
      lee_controller_B.absxi = 0.0;
    }
  } else {
    lee_controller_B.absxr = fabs(x->re);
    lee_controller_B.absxi = fabs(x->im);
    if ((lee_controller_B.absxr > 4.4942328371557893E+307) ||
        (lee_controller_B.absxi > 4.4942328371557893E+307)) {
      lee_controller_B.absxr *= 0.5;
      lee_controller_B.absxi = lee_controller_rt_hypotd_snf
        (lee_controller_B.absxr, lee_controller_B.absxi * 0.5);
      if (lee_controller_B.absxi > lee_controller_B.absxr) {
        lee_controller_B.absxr = sqrt(lee_controller_B.absxr /
          lee_controller_B.absxi + 1.0) * sqrt(lee_controller_B.absxi);
      } else {
        lee_controller_B.absxr = sqrt(lee_controller_B.absxi) *
          1.4142135623730951;
      }
    } else {
      lee_controller_B.absxr = sqrt((lee_controller_rt_hypotd_snf
        (lee_controller_B.absxr, lee_controller_B.absxi) +
        lee_controller_B.absxr) * 0.5);
    }

    if (x->re > 0.0) {
      lee_controller_B.absxi = x->im / lee_controller_B.absxr * 0.5;
    } else {
      if (x->im < 0.0) {
        lee_controller_B.absxi = -lee_controller_B.absxr;
      } else {
        lee_controller_B.absxi = lee_controller_B.absxr;
      }

      lee_controller_B.absxr = x->im / lee_controller_B.absxi * 0.5;
    }
  }

  x->re = lee_controller_B.absxr;
  x->im = lee_controller_B.absxi;
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xzlartg_g(const creal_T f, const creal_T g, real_T
  *cs, creal_T *sn)
{
  boolean_T guard1 = false;
  lee_controller_B.d = fabs(f.re);
  lee_controller_B.scale_o = lee_controller_B.d;
  lee_controller_B.f2s_j = fabs(f.im);
  if (lee_controller_B.f2s_j > lee_controller_B.d) {
    lee_controller_B.scale_o = lee_controller_B.f2s_j;
  }

  lee_controller_B.gs_re_n = fabs(g.re);
  lee_controller_B.gs_im_m = fabs(g.im);
  if (lee_controller_B.gs_im_m > lee_controller_B.gs_re_n) {
    lee_controller_B.gs_re_n = lee_controller_B.gs_im_m;
  }

  if (lee_controller_B.gs_re_n > lee_controller_B.scale_o) {
    lee_controller_B.scale_o = lee_controller_B.gs_re_n;
  }

  lee_controller_B.fs_re_i = f.re;
  lee_controller_B.fs_im_o = f.im;
  lee_controller_B.gs_re_n = g.re;
  lee_controller_B.gs_im_m = g.im;
  guard1 = false;
  if (lee_controller_B.scale_o >= 7.4428285367870146E+137) {
    do {
      lee_controller_B.fs_re_i *= 1.3435752215134178E-138;
      lee_controller_B.fs_im_o *= 1.3435752215134178E-138;
      lee_controller_B.gs_re_n *= 1.3435752215134178E-138;
      lee_controller_B.gs_im_m *= 1.3435752215134178E-138;
      lee_controller_B.scale_o *= 1.3435752215134178E-138;
    } while (!(lee_controller_B.scale_o < 7.4428285367870146E+137));

    guard1 = true;
  } else if (lee_controller_B.scale_o <= 1.3435752215134178E-138) {
    if ((g.re == 0.0) && (g.im == 0.0)) {
      *cs = 1.0;
      sn->re = 0.0;
      sn->im = 0.0;
    } else {
      do {
        lee_controller_B.fs_re_i *= 7.4428285367870146E+137;
        lee_controller_B.fs_im_o *= 7.4428285367870146E+137;
        lee_controller_B.gs_re_n *= 7.4428285367870146E+137;
        lee_controller_B.gs_im_m *= 7.4428285367870146E+137;
        lee_controller_B.scale_o *= 7.4428285367870146E+137;
      } while (!(lee_controller_B.scale_o > 1.3435752215134178E-138));

      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    lee_controller_B.scale_o = lee_controller_B.fs_re_i *
      lee_controller_B.fs_re_i + lee_controller_B.fs_im_o *
      lee_controller_B.fs_im_o;
    lee_controller_B.g2_j = lee_controller_B.gs_re_n * lee_controller_B.gs_re_n
      + lee_controller_B.gs_im_m * lee_controller_B.gs_im_m;
    lee_controller_B.x_n = lee_controller_B.g2_j;
    if (1.0 > lee_controller_B.g2_j) {
      lee_controller_B.x_n = 1.0;
    }

    if (lee_controller_B.scale_o <= lee_controller_B.x_n *
        2.0041683600089728E-292) {
      if ((f.re == 0.0) && (f.im == 0.0)) {
        *cs = 0.0;
        lee_controller_B.d = lee_controller_rt_hypotd_snf
          (lee_controller_B.gs_re_n, lee_controller_B.gs_im_m);
        sn->re = lee_controller_B.gs_re_n / lee_controller_B.d;
        sn->im = -lee_controller_B.gs_im_m / lee_controller_B.d;
      } else {
        lee_controller_B.scale_o = sqrt(lee_controller_B.g2_j);
        *cs = lee_controller_rt_hypotd_snf(lee_controller_B.fs_re_i,
          lee_controller_B.fs_im_o) / lee_controller_B.scale_o;
        if (lee_controller_B.f2s_j > lee_controller_B.d) {
          lee_controller_B.d = lee_controller_B.f2s_j;
        }

        if (lee_controller_B.d > 1.0) {
          lee_controller_B.d = lee_controller_rt_hypotd_snf(f.re, f.im);
          lee_controller_B.fs_re_i = f.re / lee_controller_B.d;
          lee_controller_B.fs_im_o = f.im / lee_controller_B.d;
        } else {
          lee_controller_B.fs_re_i = 7.4428285367870146E+137 * f.re;
          lee_controller_B.f2s_j = 7.4428285367870146E+137 * f.im;
          lee_controller_B.d = lee_controller_rt_hypotd_snf
            (lee_controller_B.fs_re_i, lee_controller_B.f2s_j);
          lee_controller_B.fs_re_i /= lee_controller_B.d;
          lee_controller_B.fs_im_o = lee_controller_B.f2s_j / lee_controller_B.d;
        }

        lee_controller_B.gs_re_n /= lee_controller_B.scale_o;
        lee_controller_B.gs_im_m = -lee_controller_B.gs_im_m /
          lee_controller_B.scale_o;
        sn->re = lee_controller_B.fs_re_i * lee_controller_B.gs_re_n -
          lee_controller_B.fs_im_o * lee_controller_B.gs_im_m;
        sn->im = lee_controller_B.fs_re_i * lee_controller_B.gs_im_m +
          lee_controller_B.fs_im_o * lee_controller_B.gs_re_n;
      }
    } else {
      lee_controller_B.f2s_j = sqrt(lee_controller_B.g2_j /
        lee_controller_B.scale_o + 1.0);
      *cs = 1.0 / lee_controller_B.f2s_j;
      lee_controller_B.d = lee_controller_B.scale_o + lee_controller_B.g2_j;
      lee_controller_B.fs_re_i = lee_controller_B.f2s_j *
        lee_controller_B.fs_re_i / lee_controller_B.d;
      lee_controller_B.fs_im_o = lee_controller_B.f2s_j *
        lee_controller_B.fs_im_o / lee_controller_B.d;
      sn->re = lee_controller_B.fs_re_i * lee_controller_B.gs_re_n -
        lee_controller_B.fs_im_o * -lee_controller_B.gs_im_m;
      sn->im = lee_controller_B.fs_re_i * -lee_controller_B.gs_im_m +
        lee_controller_B.fs_im_o * lee_controller_B.gs_re_n;
    }
  }
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xzlartg(const creal_T f, const creal_T g, real_T *cs,
  creal_T *sn, creal_T *r)
{
  boolean_T guard1 = false;
  lee_controller_B.f2s = fabs(f.re);
  lee_controller_B.scale = lee_controller_B.f2s;
  lee_controller_B.di = fabs(f.im);
  if (lee_controller_B.di > lee_controller_B.f2s) {
    lee_controller_B.scale = lee_controller_B.di;
  }

  lee_controller_B.gs_re = fabs(g.re);
  lee_controller_B.gs_im = fabs(g.im);
  if (lee_controller_B.gs_im > lee_controller_B.gs_re) {
    lee_controller_B.gs_re = lee_controller_B.gs_im;
  }

  if (lee_controller_B.gs_re > lee_controller_B.scale) {
    lee_controller_B.scale = lee_controller_B.gs_re;
  }

  lee_controller_B.fs_re = f.re;
  lee_controller_B.fs_im = f.im;
  lee_controller_B.gs_re = g.re;
  lee_controller_B.gs_im = g.im;
  lee_controller_B.count = -1;
  lee_controller_B.rescaledir = 0;
  guard1 = false;
  if (lee_controller_B.scale >= 7.4428285367870146E+137) {
    do {
      lee_controller_B.count++;
      lee_controller_B.fs_re *= 1.3435752215134178E-138;
      lee_controller_B.fs_im *= 1.3435752215134178E-138;
      lee_controller_B.gs_re *= 1.3435752215134178E-138;
      lee_controller_B.gs_im *= 1.3435752215134178E-138;
      lee_controller_B.scale *= 1.3435752215134178E-138;
    } while (!(lee_controller_B.scale < 7.4428285367870146E+137));

    lee_controller_B.rescaledir = 1;
    guard1 = true;
  } else if (lee_controller_B.scale <= 1.3435752215134178E-138) {
    if ((g.re == 0.0) && (g.im == 0.0)) {
      *cs = 1.0;
      sn->re = 0.0;
      sn->im = 0.0;
      *r = f;
    } else {
      do {
        lee_controller_B.count++;
        lee_controller_B.fs_re *= 7.4428285367870146E+137;
        lee_controller_B.fs_im *= 7.4428285367870146E+137;
        lee_controller_B.gs_re *= 7.4428285367870146E+137;
        lee_controller_B.gs_im *= 7.4428285367870146E+137;
        lee_controller_B.scale *= 7.4428285367870146E+137;
      } while (!(lee_controller_B.scale > 1.3435752215134178E-138));

      lee_controller_B.rescaledir = -1;
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    lee_controller_B.scale = lee_controller_B.fs_re * lee_controller_B.fs_re +
      lee_controller_B.fs_im * lee_controller_B.fs_im;
    lee_controller_B.g2 = lee_controller_B.gs_re * lee_controller_B.gs_re +
      lee_controller_B.gs_im * lee_controller_B.gs_im;
    lee_controller_B.x_l = lee_controller_B.g2;
    if (1.0 > lee_controller_B.g2) {
      lee_controller_B.x_l = 1.0;
    }

    if (lee_controller_B.scale <= lee_controller_B.x_l * 2.0041683600089728E-292)
    {
      if ((f.re == 0.0) && (f.im == 0.0)) {
        *cs = 0.0;
        r->re = lee_controller_rt_hypotd_snf(g.re, g.im);
        r->im = 0.0;
        lee_controller_B.f2s = lee_controller_rt_hypotd_snf
          (lee_controller_B.gs_re, lee_controller_B.gs_im);
        sn->re = lee_controller_B.gs_re / lee_controller_B.f2s;
        sn->im = -lee_controller_B.gs_im / lee_controller_B.f2s;
      } else {
        lee_controller_B.scale = sqrt(lee_controller_B.g2);
        *cs = lee_controller_rt_hypotd_snf(lee_controller_B.fs_re,
          lee_controller_B.fs_im) / lee_controller_B.scale;
        if (lee_controller_B.di > lee_controller_B.f2s) {
          lee_controller_B.f2s = lee_controller_B.di;
        }

        if (lee_controller_B.f2s > 1.0) {
          lee_controller_B.f2s = lee_controller_rt_hypotd_snf(f.re, f.im);
          lee_controller_B.fs_re = f.re / lee_controller_B.f2s;
          lee_controller_B.fs_im = f.im / lee_controller_B.f2s;
        } else {
          lee_controller_B.fs_re = 7.4428285367870146E+137 * f.re;
          lee_controller_B.di = 7.4428285367870146E+137 * f.im;
          lee_controller_B.f2s = lee_controller_rt_hypotd_snf
            (lee_controller_B.fs_re, lee_controller_B.di);
          lee_controller_B.fs_re /= lee_controller_B.f2s;
          lee_controller_B.fs_im = lee_controller_B.di / lee_controller_B.f2s;
        }

        lee_controller_B.gs_re /= lee_controller_B.scale;
        lee_controller_B.gs_im = -lee_controller_B.gs_im /
          lee_controller_B.scale;
        sn->re = lee_controller_B.fs_re * lee_controller_B.gs_re -
          lee_controller_B.fs_im * lee_controller_B.gs_im;
        sn->im = lee_controller_B.fs_re * lee_controller_B.gs_im +
          lee_controller_B.fs_im * lee_controller_B.gs_re;
        r->re = (sn->re * g.re - sn->im * g.im) + *cs * f.re;
        r->im = (sn->re * g.im + sn->im * g.re) + *cs * f.im;
      }
    } else {
      lee_controller_B.f2s = sqrt(lee_controller_B.g2 / lee_controller_B.scale +
        1.0);
      r->re = lee_controller_B.f2s * lee_controller_B.fs_re;
      r->im = lee_controller_B.f2s * lee_controller_B.fs_im;
      *cs = 1.0 / lee_controller_B.f2s;
      lee_controller_B.f2s = lee_controller_B.scale + lee_controller_B.g2;
      lee_controller_B.fs_re = r->re / lee_controller_B.f2s;
      lee_controller_B.f2s = r->im / lee_controller_B.f2s;
      sn->re = lee_controller_B.fs_re * lee_controller_B.gs_re -
        lee_controller_B.f2s * -lee_controller_B.gs_im;
      sn->im = lee_controller_B.fs_re * -lee_controller_B.gs_im +
        lee_controller_B.f2s * lee_controller_B.gs_re;
      if (lee_controller_B.rescaledir > 0) {
        lee_controller_B.rescaledir = 0;
        while (lee_controller_B.rescaledir <= lee_controller_B.count) {
          r->re *= 7.4428285367870146E+137;
          r->im *= 7.4428285367870146E+137;
          lee_controller_B.rescaledir++;
        }
      } else if (lee_controller_B.rescaledir < 0) {
        lee_controller_B.rescaledir = 0;
        while (lee_controller_B.rescaledir <= lee_controller_B.count) {
          r->re *= 1.3435752215134178E-138;
          r->im *= 1.3435752215134178E-138;
          lee_controller_B.rescaledir++;
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xzhgeqz(creal_T A[16], int32_T ilo, int32_T ihi,
  creal_T Z[16], int32_T *info, creal_T alpha1[4], creal_T beta1[4])
{
  boolean_T failed;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *info = 0;
  alpha1[0].re = 0.0;
  alpha1[0].im = 0.0;
  beta1[0].re = 1.0;
  beta1[0].im = 0.0;
  alpha1[1].re = 0.0;
  alpha1[1].im = 0.0;
  beta1[1].re = 1.0;
  beta1[1].im = 0.0;
  alpha1[2].re = 0.0;
  alpha1[2].im = 0.0;
  beta1[2].re = 1.0;
  beta1[2].im = 0.0;
  alpha1[3].re = 0.0;
  alpha1[3].im = 0.0;
  beta1[3].re = 1.0;
  beta1[3].im = 0.0;
  lee_controller_B.eshift_re = 0.0;
  lee_controller_B.eshift_im = 0.0;
  lee_controller_B.ctemp.re = 0.0;
  lee_controller_B.ctemp.im = 0.0;
  lee_controller_B.anorm = lee_controller_xzlanhs(A, ilo, ihi);
  lee_controller_B.b_atol = 2.2250738585072014E-308;
  lee_controller_B.temp = 2.2204460492503131E-16 * lee_controller_B.anorm;
  if (lee_controller_B.temp > 2.2250738585072014E-308) {
    lee_controller_B.b_atol = lee_controller_B.temp;
  }

  lee_controller_B.temp = 2.2250738585072014E-308;
  if (lee_controller_B.anorm > 2.2250738585072014E-308) {
    lee_controller_B.temp = lee_controller_B.anorm;
  }

  lee_controller_B.anorm = 1.0 / lee_controller_B.temp;
  failed = true;
  lee_controller_B.ilast = ihi;
  while (lee_controller_B.ilast + 1 < 5) {
    alpha1[lee_controller_B.ilast] = A[(lee_controller_B.ilast << 2) +
      lee_controller_B.ilast];
    lee_controller_B.ilast++;
  }

  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    boolean_T goto60;
    boolean_T goto70;
    boolean_T goto90;
    lee_controller_B.ifirst = ilo;
    lee_controller_B.istart = ilo;
    lee_controller_B.ilast = ihi - 1;
    lee_controller_B.ilastm1 = ihi - 2;
    lee_controller_B.iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    lee_controller_B.jiter = 0;
    int32_T exitg1;
    do {
      exitg1 = 0;
      if (lee_controller_B.jiter <= ((ihi - ilo) + 1) * 30 - 1) {
        boolean_T exitg2;
        if (lee_controller_B.ilast + 1 == ilo) {
          goto60 = true;
        } else {
          lee_controller_B.jp1 = (lee_controller_B.ilastm1 << 2) +
            lee_controller_B.ilast;
          if (fabs(A[lee_controller_B.jp1].re) + fabs(A[lee_controller_B.jp1].im)
              <= lee_controller_B.b_atol) {
            A[lee_controller_B.jp1].re = 0.0;
            A[lee_controller_B.jp1].im = 0.0;
            goto60 = true;
          } else {
            boolean_T guard3 = false;
            lee_controller_B.j = lee_controller_B.ilastm1;
            guard3 = false;
            exitg2 = false;
            while ((!exitg2) && (lee_controller_B.j + 1 >= ilo)) {
              if (lee_controller_B.j + 1 == ilo) {
                guard3 = true;
                exitg2 = true;
              } else {
                lee_controller_B.jp1 = ((lee_controller_B.j - 1) << 2) +
                  lee_controller_B.j;
                if (fabs(A[lee_controller_B.jp1].re) + fabs
                    (A[lee_controller_B.jp1].im) <= lee_controller_B.b_atol) {
                  A[lee_controller_B.jp1].re = 0.0;
                  A[lee_controller_B.jp1].im = 0.0;
                  guard3 = true;
                  exitg2 = true;
                } else {
                  lee_controller_B.j--;
                  guard3 = false;
                }
              }
            }

            if (guard3) {
              lee_controller_B.ifirst = lee_controller_B.j + 1;
              goto70 = true;
            }
          }
        }

        if ((!goto60) && (!goto70)) {
          alpha1[0].re = (rtNaN);
          alpha1[0].im = 0.0;
          beta1[0].re = (rtNaN);
          beta1[0].im = 0.0;
          alpha1[1].re = (rtNaN);
          alpha1[1].im = 0.0;
          beta1[1].re = (rtNaN);
          beta1[1].im = 0.0;
          alpha1[2].re = (rtNaN);
          alpha1[2].im = 0.0;
          beta1[2].re = (rtNaN);
          beta1[2].im = 0.0;
          alpha1[3].re = (rtNaN);
          alpha1[3].im = 0.0;
          beta1[3].re = (rtNaN);
          beta1[3].im = 0.0;
          for (lee_controller_B.jp1 = 0; lee_controller_B.jp1 < 16;
               lee_controller_B.jp1++) {
            Z[lee_controller_B.jp1].re = (rtNaN);
            Z[lee_controller_B.jp1].im = 0.0;
          }

          *info = 1;
          exitg1 = 1;
        } else if (goto60) {
          goto60 = false;
          alpha1[lee_controller_B.ilast] = A[(lee_controller_B.ilast << 2) +
            lee_controller_B.ilast];
          lee_controller_B.ilast = lee_controller_B.ilastm1;
          lee_controller_B.ilastm1--;
          if (lee_controller_B.ilast + 1 < ilo) {
            failed = false;
            guard2 = true;
            exitg1 = 1;
          } else {
            lee_controller_B.iiter = 0;
            lee_controller_B.eshift_re = 0.0;
            lee_controller_B.eshift_im = 0.0;
            lee_controller_B.jiter++;
          }
        } else {
          if (goto70) {
            goto70 = false;
            lee_controller_B.iiter++;
            if (lee_controller_B.iiter - lee_controller_B.iiter / 10 * 10 != 0)
            {
              lee_controller_B.j = (lee_controller_B.ilastm1 << 2) +
                lee_controller_B.ilastm1;
              lee_controller_B.ar = A[lee_controller_B.j].re *
                lee_controller_B.anorm;
              lee_controller_B.ai = A[lee_controller_B.j].im *
                lee_controller_B.anorm;
              if (lee_controller_B.ai == 0.0) {
                lee_controller_B.shift.re = lee_controller_B.ar / 0.5;
                lee_controller_B.shift.im = 0.0;
              } else if (lee_controller_B.ar == 0.0) {
                lee_controller_B.shift.re = 0.0;
                lee_controller_B.shift.im = lee_controller_B.ai / 0.5;
              } else {
                lee_controller_B.shift.re = lee_controller_B.ar / 0.5;
                lee_controller_B.shift.im = lee_controller_B.ai / 0.5;
              }

              lee_controller_B.j = (lee_controller_B.ilast << 2) +
                lee_controller_B.ilast;
              lee_controller_B.ar = A[lee_controller_B.j].re *
                lee_controller_B.anorm;
              lee_controller_B.ai = A[lee_controller_B.j].im *
                lee_controller_B.anorm;
              if (lee_controller_B.ai == 0.0) {
                lee_controller_B.stemp_re = lee_controller_B.ar / 0.5;
                lee_controller_B.stemp_im = 0.0;
              } else if (lee_controller_B.ar == 0.0) {
                lee_controller_B.stemp_re = 0.0;
                lee_controller_B.stemp_im = lee_controller_B.ai / 0.5;
              } else {
                lee_controller_B.stemp_re = lee_controller_B.ar / 0.5;
                lee_controller_B.stemp_im = lee_controller_B.ai / 0.5;
              }

              lee_controller_B.t1_re = (lee_controller_B.shift.re +
                lee_controller_B.stemp_re) * 0.5;
              lee_controller_B.t1_im = (lee_controller_B.shift.im +
                lee_controller_B.stemp_im) * 0.5;
              lee_controller_B.j = (lee_controller_B.ilast << 2) +
                lee_controller_B.ilastm1;
              lee_controller_B.ar = A[lee_controller_B.j].re *
                lee_controller_B.anorm;
              lee_controller_B.ai = A[lee_controller_B.j].im *
                lee_controller_B.anorm;
              if (lee_controller_B.ai == 0.0) {
                lee_controller_B.temp = lee_controller_B.ar / 0.5;
                lee_controller_B.temp2 = 0.0;
              } else if (lee_controller_B.ar == 0.0) {
                lee_controller_B.temp = 0.0;
                lee_controller_B.temp2 = lee_controller_B.ai / 0.5;
              } else {
                lee_controller_B.temp = lee_controller_B.ar / 0.5;
                lee_controller_B.temp2 = lee_controller_B.ai / 0.5;
              }

              lee_controller_B.j = (lee_controller_B.ilastm1 << 2) +
                lee_controller_B.ilast;
              lee_controller_B.ar = A[lee_controller_B.j].re *
                lee_controller_B.anorm;
              lee_controller_B.ai = A[lee_controller_B.j].im *
                lee_controller_B.anorm;
              if (lee_controller_B.ai == 0.0) {
                lee_controller_B.ar /= 0.5;
                lee_controller_B.ai = 0.0;
              } else if (lee_controller_B.ar == 0.0) {
                lee_controller_B.ar = 0.0;
                lee_controller_B.ai /= 0.5;
              } else {
                lee_controller_B.ar /= 0.5;
                lee_controller_B.ai /= 0.5;
              }

              lee_controller_B.shift_im = lee_controller_B.shift.re *
                lee_controller_B.stemp_im + lee_controller_B.shift.im *
                lee_controller_B.stemp_re;
              lee_controller_B.shift.re = ((lee_controller_B.t1_re *
                lee_controller_B.t1_re - lee_controller_B.t1_im *
                lee_controller_B.t1_im) + (lee_controller_B.temp *
                lee_controller_B.ar - lee_controller_B.temp2 *
                lee_controller_B.ai)) - (lee_controller_B.shift.re *
                lee_controller_B.stemp_re - lee_controller_B.shift.im *
                lee_controller_B.stemp_im);
              lee_controller_B.shift_tmp = lee_controller_B.t1_re *
                lee_controller_B.t1_im;
              lee_controller_B.shift.im = ((lee_controller_B.temp *
                lee_controller_B.ai + lee_controller_B.temp2 *
                lee_controller_B.ar) + (lee_controller_B.shift_tmp +
                lee_controller_B.shift_tmp)) - lee_controller_B.shift_im;
              lee_controller_sqrt(&lee_controller_B.shift);
              if ((lee_controller_B.t1_re - lee_controller_B.stemp_re) *
                  lee_controller_B.shift.re + (lee_controller_B.t1_im -
                   lee_controller_B.stemp_im) * lee_controller_B.shift.im <= 0.0)
              {
                lee_controller_B.shift.re += lee_controller_B.t1_re;
                lee_controller_B.shift.im += lee_controller_B.t1_im;
              } else {
                lee_controller_B.shift.re = lee_controller_B.t1_re -
                  lee_controller_B.shift.re;
                lee_controller_B.shift.im = lee_controller_B.t1_im -
                  lee_controller_B.shift.im;
              }
            } else {
              lee_controller_B.j = (lee_controller_B.ilastm1 << 2) +
                lee_controller_B.ilast;
              lee_controller_B.ar = A[lee_controller_B.j].re *
                lee_controller_B.anorm;
              lee_controller_B.ai = A[lee_controller_B.j].im *
                lee_controller_B.anorm;
              if (lee_controller_B.ai == 0.0) {
                lee_controller_B.temp = lee_controller_B.ar / 0.5;
                lee_controller_B.temp2 = 0.0;
              } else if (lee_controller_B.ar == 0.0) {
                lee_controller_B.temp = 0.0;
                lee_controller_B.temp2 = lee_controller_B.ai / 0.5;
              } else {
                lee_controller_B.temp = lee_controller_B.ar / 0.5;
                lee_controller_B.temp2 = lee_controller_B.ai / 0.5;
              }

              lee_controller_B.eshift_re += lee_controller_B.temp;
              lee_controller_B.eshift_im += lee_controller_B.temp2;
              lee_controller_B.shift.re = lee_controller_B.eshift_re;
              lee_controller_B.shift.im = lee_controller_B.eshift_im;
            }

            lee_controller_B.j = lee_controller_B.ilastm1;
            lee_controller_B.jp1 = lee_controller_B.ilastm1 + 1;
            exitg2 = false;
            while ((!exitg2) && (lee_controller_B.j + 1 >
                                 lee_controller_B.ifirst)) {
              lee_controller_B.istart = lee_controller_B.j + 1;
              lee_controller_B.ctemp_tmp_tmp = lee_controller_B.j << 2;
              lee_controller_B.ctemp_tmp = lee_controller_B.ctemp_tmp_tmp +
                lee_controller_B.j;
              lee_controller_B.ctemp.re = A[lee_controller_B.ctemp_tmp].re *
                lee_controller_B.anorm - lee_controller_B.shift.re * 0.5;
              lee_controller_B.ctemp.im = A[lee_controller_B.ctemp_tmp].im *
                lee_controller_B.anorm - lee_controller_B.shift.im * 0.5;
              lee_controller_B.temp = fabs(lee_controller_B.ctemp.re) + fabs
                (lee_controller_B.ctemp.im);
              lee_controller_B.jp1 += lee_controller_B.ctemp_tmp_tmp;
              lee_controller_B.temp2 = (fabs(A[lee_controller_B.jp1].re) + fabs
                (A[lee_controller_B.jp1].im)) * lee_controller_B.anorm;
              lee_controller_B.stemp_re = lee_controller_B.temp;
              if (lee_controller_B.temp2 > lee_controller_B.temp) {
                lee_controller_B.stemp_re = lee_controller_B.temp2;
              }

              if ((lee_controller_B.stemp_re < 1.0) &&
                  (lee_controller_B.stemp_re != 0.0)) {
                lee_controller_B.temp /= lee_controller_B.stemp_re;
                lee_controller_B.temp2 /= lee_controller_B.stemp_re;
              }

              lee_controller_B.jp1 = ((lee_controller_B.j - 1) << 2) +
                lee_controller_B.j;
              if ((fabs(A[lee_controller_B.jp1].re) + fabs
                   (A[lee_controller_B.jp1].im)) * lee_controller_B.temp2 <=
                  lee_controller_B.temp * lee_controller_B.b_atol) {
                goto90 = true;
                exitg2 = true;
              } else {
                lee_controller_B.jp1 = lee_controller_B.j;
                lee_controller_B.j--;
              }
            }

            if (!goto90) {
              lee_controller_B.istart = lee_controller_B.ifirst;
              lee_controller_B.ctemp_tmp = (((lee_controller_B.ifirst - 1) << 2)
                + lee_controller_B.ifirst) - 1;
              lee_controller_B.ctemp.re = A[lee_controller_B.ctemp_tmp].re *
                lee_controller_B.anorm - lee_controller_B.shift.re * 0.5;
              lee_controller_B.ctemp.im = A[lee_controller_B.ctemp_tmp].im *
                lee_controller_B.anorm - lee_controller_B.shift.im * 0.5;
            }

            goto90 = false;
            lee_controller_B.j = ((lee_controller_B.istart - 1) << 2) +
              lee_controller_B.istart;
            lee_controller_B.ascale.re = A[lee_controller_B.j].re *
              lee_controller_B.anorm;
            lee_controller_B.ascale.im = A[lee_controller_B.j].im *
              lee_controller_B.anorm;
            lee_controller_xzlartg_g(lee_controller_B.ctemp,
              lee_controller_B.ascale, &lee_controller_B.temp,
              &lee_controller_B.shift);
            lee_controller_B.j = lee_controller_B.istart;
            lee_controller_B.jp1 = lee_controller_B.istart - 2;
            while (lee_controller_B.j < lee_controller_B.ilast + 1) {
              if (lee_controller_B.j > lee_controller_B.istart) {
                lee_controller_xzlartg(A[(lee_controller_B.j +
                  (lee_controller_B.jp1 << 2)) - 1], A[lee_controller_B.j +
                  (lee_controller_B.jp1 << 2)], &lee_controller_B.temp,
                  &lee_controller_B.shift, &A[(lee_controller_B.j +
                  (lee_controller_B.jp1 << 2)) - 1]);
                lee_controller_B.jp1 = (lee_controller_B.jp1 << 2) +
                  lee_controller_B.j;
                A[lee_controller_B.jp1].re = 0.0;
                A[lee_controller_B.jp1].im = 0.0;
              }

              lee_controller_B.ctemp_tmp_tmp = lee_controller_B.j - 1;
              while (lee_controller_B.ctemp_tmp_tmp + 1 <= 4) {
                lee_controller_B.jp1 = (lee_controller_B.ctemp_tmp_tmp << 2) +
                  lee_controller_B.j;
                lee_controller_B.ar = A[lee_controller_B.jp1].im;
                lee_controller_B.stemp_re = A[lee_controller_B.jp1].re;
                lee_controller_B.stemp_im = A[lee_controller_B.jp1 - 1].re;
                lee_controller_B.t1_re = A[lee_controller_B.jp1 - 1].im;
                A[lee_controller_B.jp1].re = lee_controller_B.stemp_re *
                  lee_controller_B.temp - (lee_controller_B.stemp_im *
                  lee_controller_B.shift.re + lee_controller_B.t1_re *
                  lee_controller_B.shift.im);
                A[lee_controller_B.jp1].im = A[lee_controller_B.jp1].im *
                  lee_controller_B.temp - (lee_controller_B.shift.re *
                  lee_controller_B.t1_re - lee_controller_B.shift.im *
                  lee_controller_B.stemp_im);
                A[lee_controller_B.jp1 - 1].re = (lee_controller_B.stemp_re *
                  lee_controller_B.shift.re - lee_controller_B.ar *
                  lee_controller_B.shift.im) + lee_controller_B.stemp_im *
                  lee_controller_B.temp;
                A[lee_controller_B.jp1 - 1].im = (lee_controller_B.ar *
                  lee_controller_B.shift.re + lee_controller_B.stemp_re *
                  lee_controller_B.shift.im) + lee_controller_B.t1_re *
                  lee_controller_B.temp;
                lee_controller_B.ctemp_tmp_tmp++;
              }

              lee_controller_B.shift.re = -lee_controller_B.shift.re;
              lee_controller_B.shift.im = -lee_controller_B.shift.im;
              lee_controller_B.ctemp_tmp_tmp = lee_controller_B.j;
              if (lee_controller_B.ilast + 1 < lee_controller_B.j + 2) {
                lee_controller_B.ctemp_tmp_tmp = lee_controller_B.ilast - 1;
              }

              lee_controller_B.ctemp_tmp = 0;
              while (lee_controller_B.ctemp_tmp + 1 <=
                     lee_controller_B.ctemp_tmp_tmp + 2) {
                lee_controller_B.jp1 = ((lee_controller_B.j - 1) << 2) +
                  lee_controller_B.ctemp_tmp;
                lee_controller_B.ar = A[lee_controller_B.jp1].im;
                lee_controller_B.stemp_re = A[lee_controller_B.jp1].re;
                lee_controller_B.stemp_re_tmp_a = (lee_controller_B.j << 2) +
                  lee_controller_B.ctemp_tmp;
                lee_controller_B.stemp_im = A[lee_controller_B.stemp_re_tmp_a].
                  re;
                lee_controller_B.t1_re = A[lee_controller_B.stemp_re_tmp_a].im;
                A[lee_controller_B.jp1].re = lee_controller_B.stemp_re *
                  lee_controller_B.temp - (lee_controller_B.stemp_im *
                  lee_controller_B.shift.re + lee_controller_B.t1_re *
                  lee_controller_B.shift.im);
                A[lee_controller_B.jp1].im = A[lee_controller_B.jp1].im *
                  lee_controller_B.temp - (lee_controller_B.shift.re *
                  lee_controller_B.t1_re - lee_controller_B.shift.im *
                  lee_controller_B.stemp_im);
                A[lee_controller_B.stemp_re_tmp_a].re =
                  (lee_controller_B.stemp_re * lee_controller_B.shift.re -
                   lee_controller_B.ar * lee_controller_B.shift.im) +
                  lee_controller_B.stemp_im * lee_controller_B.temp;
                A[lee_controller_B.stemp_re_tmp_a].im = (lee_controller_B.ar *
                  lee_controller_B.shift.re + lee_controller_B.stemp_re *
                  lee_controller_B.shift.im) + lee_controller_B.t1_re *
                  lee_controller_B.temp;
                lee_controller_B.ctemp_tmp++;
              }

              lee_controller_B.jp1 = (lee_controller_B.j - 1) << 2;
              lee_controller_B.ar = Z[lee_controller_B.jp1].im;
              lee_controller_B.stemp_re = Z[lee_controller_B.jp1].re;
              lee_controller_B.stemp_re_tmp_a = lee_controller_B.j << 2;
              lee_controller_B.stemp_im = Z[lee_controller_B.stemp_re_tmp_a].re;
              lee_controller_B.t1_re = Z[lee_controller_B.stemp_re_tmp_a].im;
              Z[lee_controller_B.jp1].re = lee_controller_B.stemp_re *
                lee_controller_B.temp - (lee_controller_B.stemp_im *
                lee_controller_B.shift.re + lee_controller_B.t1_re *
                lee_controller_B.shift.im);
              Z[lee_controller_B.jp1].im = Z[lee_controller_B.jp1].im *
                lee_controller_B.temp - (lee_controller_B.shift.re *
                lee_controller_B.t1_re - lee_controller_B.shift.im *
                lee_controller_B.stemp_im);
              Z[lee_controller_B.stemp_re_tmp_a].re = (lee_controller_B.stemp_re
                * lee_controller_B.shift.re - lee_controller_B.ar *
                lee_controller_B.shift.im) + lee_controller_B.stemp_im *
                lee_controller_B.temp;
              Z[lee_controller_B.stemp_re_tmp_a].im = (lee_controller_B.ar *
                lee_controller_B.shift.re + lee_controller_B.stemp_re *
                lee_controller_B.shift.im) + lee_controller_B.t1_re *
                lee_controller_B.temp;
              lee_controller_B.ar = Z[lee_controller_B.jp1 + 1].im;
              lee_controller_B.stemp_re = Z[lee_controller_B.jp1 + 1].re;
              lee_controller_B.stemp_im = Z[lee_controller_B.stemp_re_tmp_a + 1]
                .re;
              lee_controller_B.t1_re = Z[lee_controller_B.stemp_re_tmp_a + 1].im;
              Z[lee_controller_B.jp1 + 1].re = lee_controller_B.stemp_re *
                lee_controller_B.temp - (lee_controller_B.stemp_im *
                lee_controller_B.shift.re + lee_controller_B.t1_re *
                lee_controller_B.shift.im);
              Z[lee_controller_B.jp1 + 1].im = Z[lee_controller_B.jp1 + 1].im *
                lee_controller_B.temp - (lee_controller_B.shift.re *
                lee_controller_B.t1_re - lee_controller_B.shift.im *
                lee_controller_B.stemp_im);
              Z[lee_controller_B.stemp_re_tmp_a + 1].re =
                (lee_controller_B.stemp_re * lee_controller_B.shift.re -
                 lee_controller_B.ar * lee_controller_B.shift.im) +
                lee_controller_B.stemp_im * lee_controller_B.temp;
              Z[lee_controller_B.stemp_re_tmp_a + 1].im = (lee_controller_B.ar *
                lee_controller_B.shift.re + lee_controller_B.stemp_re *
                lee_controller_B.shift.im) + lee_controller_B.t1_re *
                lee_controller_B.temp;
              lee_controller_B.ar = Z[lee_controller_B.jp1 + 2].im;
              lee_controller_B.stemp_re = Z[lee_controller_B.jp1 + 2].re;
              lee_controller_B.stemp_im = Z[lee_controller_B.stemp_re_tmp_a + 2]
                .re;
              lee_controller_B.t1_re = Z[lee_controller_B.stemp_re_tmp_a + 2].im;
              Z[lee_controller_B.jp1 + 2].re = lee_controller_B.stemp_re *
                lee_controller_B.temp - (lee_controller_B.stemp_im *
                lee_controller_B.shift.re + lee_controller_B.t1_re *
                lee_controller_B.shift.im);
              Z[lee_controller_B.jp1 + 2].im = Z[lee_controller_B.jp1 + 2].im *
                lee_controller_B.temp - (lee_controller_B.shift.re *
                lee_controller_B.t1_re - lee_controller_B.shift.im *
                lee_controller_B.stemp_im);
              Z[lee_controller_B.stemp_re_tmp_a + 2].re =
                (lee_controller_B.stemp_re * lee_controller_B.shift.re -
                 lee_controller_B.ar * lee_controller_B.shift.im) +
                lee_controller_B.stemp_im * lee_controller_B.temp;
              Z[lee_controller_B.stemp_re_tmp_a + 2].im = (lee_controller_B.ar *
                lee_controller_B.shift.re + lee_controller_B.stemp_re *
                lee_controller_B.shift.im) + lee_controller_B.t1_re *
                lee_controller_B.temp;
              lee_controller_B.ar = Z[lee_controller_B.jp1 + 3].im;
              lee_controller_B.stemp_re = Z[lee_controller_B.jp1 + 3].re;
              lee_controller_B.stemp_im = Z[lee_controller_B.stemp_re_tmp_a + 3]
                .re;
              lee_controller_B.t1_re = Z[lee_controller_B.stemp_re_tmp_a + 3].im;
              Z[lee_controller_B.jp1 + 3].re = lee_controller_B.stemp_re *
                lee_controller_B.temp - (lee_controller_B.stemp_im *
                lee_controller_B.shift.re + lee_controller_B.t1_re *
                lee_controller_B.shift.im);
              Z[lee_controller_B.jp1 + 3].im = Z[lee_controller_B.jp1 + 3].im *
                lee_controller_B.temp - (lee_controller_B.shift.re *
                lee_controller_B.t1_re - lee_controller_B.shift.im *
                lee_controller_B.stemp_im);
              Z[lee_controller_B.stemp_re_tmp_a + 3].re =
                (lee_controller_B.stemp_re * lee_controller_B.shift.re -
                 lee_controller_B.ar * lee_controller_B.shift.im) +
                lee_controller_B.stemp_im * lee_controller_B.temp;
              Z[lee_controller_B.stemp_re_tmp_a + 3].im = (lee_controller_B.ar *
                lee_controller_B.shift.re + lee_controller_B.stemp_re *
                lee_controller_B.shift.im) + lee_controller_B.t1_re *
                lee_controller_B.temp;
              lee_controller_B.jp1 = lee_controller_B.j - 1;
              lee_controller_B.j++;
            }
          }

          lee_controller_B.jiter++;
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }

  if (guard2) {
    if (failed) {
      *info = lee_controller_B.ilast + 1;
      lee_controller_B.ifirst = 0;
      while (lee_controller_B.ifirst <= lee_controller_B.ilast) {
        alpha1[lee_controller_B.ifirst].re = (rtNaN);
        alpha1[lee_controller_B.ifirst].im = 0.0;
        beta1[lee_controller_B.ifirst].re = (rtNaN);
        beta1[lee_controller_B.ifirst].im = 0.0;
        lee_controller_B.ifirst++;
      }

      for (lee_controller_B.jp1 = 0; lee_controller_B.jp1 < 16;
           lee_controller_B.jp1++) {
        Z[lee_controller_B.jp1].re = (rtNaN);
        Z[lee_controller_B.jp1].im = 0.0;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    lee_controller_B.ilast = 0;
    while (lee_controller_B.ilast <= ilo - 2) {
      alpha1[lee_controller_B.ilast] = A[(lee_controller_B.ilast << 2) +
        lee_controller_B.ilast];
      lee_controller_B.ilast++;
    }
  }
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xztgevc(const creal_T A[16], creal_T V[16])
{
  lee_controller_B.rworka[0] = 0.0;
  lee_controller_B.rworka[2] = 0.0;
  lee_controller_B.rworka[3] = 0.0;
  lee_controller_B.anorm_d = fabs(A[0].re) + fabs(A[0].im);
  lee_controller_B.rworka[1] = fabs(A[4].re) + fabs(A[4].im);
  lee_controller_B.ascale_e = (fabs(A[5].re) + fabs(A[5].im)) +
    lee_controller_B.rworka[1];
  if (lee_controller_B.ascale_e > lee_controller_B.anorm_d) {
    lee_controller_B.anorm_d = lee_controller_B.ascale_e;
  }

  lee_controller_B.i_o = 0;
  while (lee_controller_B.i_o <= 1) {
    lee_controller_B.rworka[2] += fabs(A[lee_controller_B.i_o + 8].re) + fabs
      (A[lee_controller_B.i_o + 8].im);
    lee_controller_B.i_o++;
  }

  lee_controller_B.ascale_e = (fabs(A[10].re) + fabs(A[10].im)) +
    lee_controller_B.rworka[2];
  if (lee_controller_B.ascale_e > lee_controller_B.anorm_d) {
    lee_controller_B.anorm_d = lee_controller_B.ascale_e;
  }

  lee_controller_B.i_o = 0;
  while (lee_controller_B.i_o <= 2) {
    lee_controller_B.rworka[3] += fabs(A[lee_controller_B.i_o + 12].re) + fabs
      (A[lee_controller_B.i_o + 12].im);
    lee_controller_B.i_o++;
  }

  lee_controller_B.ascale_e = (fabs(A[15].re) + fabs(A[15].im)) +
    lee_controller_B.rworka[3];
  if (lee_controller_B.ascale_e > lee_controller_B.anorm_d) {
    lee_controller_B.anorm_d = lee_controller_B.ascale_e;
  }

  lee_controller_B.ascale_e = lee_controller_B.anorm_d;
  if (2.2250738585072014E-308 > lee_controller_B.anorm_d) {
    lee_controller_B.ascale_e = 2.2250738585072014E-308;
  }

  lee_controller_B.ascale_e = 1.0 / lee_controller_B.ascale_e;
  for (lee_controller_B.i_o = 3; lee_controller_B.i_o >= 0; lee_controller_B.i_o
       --) {
    boolean_T lscalea;
    boolean_T lscaleb;
    lee_controller_B.b_x_tmp_tmp = lee_controller_B.i_o << 2;
    lee_controller_B.b_x_tmp = lee_controller_B.b_x_tmp_tmp +
      lee_controller_B.i_o;
    lee_controller_B.salpha_re = A[lee_controller_B.b_x_tmp].re;
    lee_controller_B.salpha_im = A[lee_controller_B.b_x_tmp].im;
    lee_controller_B.temp_b = (fabs(lee_controller_B.salpha_re) + fabs
      (lee_controller_B.salpha_im)) * lee_controller_B.ascale_e;
    if (1.0 > lee_controller_B.temp_b) {
      lee_controller_B.temp_b = 1.0;
    }

    lee_controller_B.temp_b = 1.0 / lee_controller_B.temp_b;
    lee_controller_B.salpha_re = lee_controller_B.salpha_re *
      lee_controller_B.temp_b * lee_controller_B.ascale_e;
    lee_controller_B.salpha_im = lee_controller_B.salpha_im *
      lee_controller_B.temp_b * lee_controller_B.ascale_e;
    lee_controller_B.acoeff = lee_controller_B.temp_b *
      lee_controller_B.ascale_e;
    lscalea = ((lee_controller_B.temp_b >= 2.2250738585072014E-308) &&
               (lee_controller_B.acoeff < 4.0083367200179456E-292));
    lee_controller_B.dmin = fabs(lee_controller_B.salpha_re) + fabs
      (lee_controller_B.salpha_im);
    lscaleb = ((lee_controller_B.dmin >= 2.2250738585072014E-308) &&
               (lee_controller_B.dmin < 4.0083367200179456E-292));
    lee_controller_B.scale_j = 1.0;
    if (lscalea) {
      lee_controller_B.scale_j = lee_controller_B.anorm_d;
      if (2.4948003869184E+291 < lee_controller_B.anorm_d) {
        lee_controller_B.scale_j = 2.4948003869184E+291;
      }

      lee_controller_B.scale_j *= 4.0083367200179456E-292 /
        lee_controller_B.temp_b;
    }

    if (lscaleb) {
      lee_controller_B.work2_idx_2_im = 4.0083367200179456E-292 /
        lee_controller_B.dmin;
      if (lee_controller_B.work2_idx_2_im > lee_controller_B.scale_j) {
        lee_controller_B.scale_j = lee_controller_B.work2_idx_2_im;
      }
    }

    if (lscalea || lscaleb) {
      lee_controller_B.work2_idx_2_im = lee_controller_B.acoeff;
      if (1.0 > lee_controller_B.acoeff) {
        lee_controller_B.work2_idx_2_im = 1.0;
      }

      if (lee_controller_B.dmin > lee_controller_B.work2_idx_2_im) {
        lee_controller_B.work2_idx_2_im = lee_controller_B.dmin;
      }

      lee_controller_B.dmin = 1.0 / (2.2250738585072014E-308 *
        lee_controller_B.work2_idx_2_im);
      if (lee_controller_B.dmin < lee_controller_B.scale_j) {
        lee_controller_B.scale_j = lee_controller_B.dmin;
      }

      if (lscalea) {
        lee_controller_B.acoeff = lee_controller_B.scale_j *
          lee_controller_B.temp_b * lee_controller_B.ascale_e;
      } else {
        lee_controller_B.acoeff *= lee_controller_B.scale_j;
      }

      lee_controller_B.salpha_re *= lee_controller_B.scale_j;
      lee_controller_B.salpha_im *= lee_controller_B.scale_j;
    }

    memset(&lee_controller_B.work1[0], 0, sizeof(creal_T) << 2U);
    lee_controller_B.work1[lee_controller_B.i_o].re = 1.0;
    lee_controller_B.work1[lee_controller_B.i_o].im = 0.0;
    lee_controller_B.dmin = 2.2204460492503131E-16 * lee_controller_B.acoeff *
      lee_controller_B.anorm_d;
    lee_controller_B.temp_b = (fabs(lee_controller_B.salpha_re) + fabs
      (lee_controller_B.salpha_im)) * 2.2204460492503131E-16;
    if (lee_controller_B.temp_b > lee_controller_B.dmin) {
      lee_controller_B.dmin = lee_controller_B.temp_b;
    }

    if (2.2250738585072014E-308 > lee_controller_B.dmin) {
      lee_controller_B.dmin = 2.2250738585072014E-308;
    }

    lee_controller_B.b_x_tmp = 0;
    while (lee_controller_B.b_x_tmp <= lee_controller_B.i_o - 1) {
      lee_controller_B.d_re_tmp = lee_controller_B.b_x_tmp_tmp +
        lee_controller_B.b_x_tmp;
      lee_controller_B.work1[lee_controller_B.b_x_tmp].re =
        A[lee_controller_B.d_re_tmp].re * lee_controller_B.acoeff;
      lee_controller_B.work1[lee_controller_B.b_x_tmp].im =
        A[lee_controller_B.d_re_tmp].im * lee_controller_B.acoeff;
      lee_controller_B.b_x_tmp++;
    }

    lee_controller_B.work1[lee_controller_B.i_o].re = 1.0;
    lee_controller_B.work1[lee_controller_B.i_o].im = 0.0;
    lee_controller_B.b_x_tmp = lee_controller_B.i_o - 1;
    while (lee_controller_B.b_x_tmp + 1 > 0) {
      lee_controller_B.work2_idx_0_re_tmp_b = lee_controller_B.b_x_tmp << 2;
      lee_controller_B.d_re_tmp = lee_controller_B.work2_idx_0_re_tmp_b +
        lee_controller_B.b_x_tmp;
      lee_controller_B.work2_idx_3_re = A[lee_controller_B.d_re_tmp].re *
        lee_controller_B.acoeff - lee_controller_B.salpha_re;
      lee_controller_B.scale_j = A[lee_controller_B.d_re_tmp].im *
        lee_controller_B.acoeff - lee_controller_B.salpha_im;
      if (fabs(lee_controller_B.work2_idx_3_re) + fabs(lee_controller_B.scale_j)
          <= lee_controller_B.dmin) {
        lee_controller_B.work2_idx_3_re = lee_controller_B.dmin;
        lee_controller_B.scale_j = 0.0;
      }

      lee_controller_B.work2_idx_2_im = fabs(lee_controller_B.work2_idx_3_re);
      lee_controller_B.e_y = fabs(lee_controller_B.scale_j);
      lee_controller_B.temp_b = lee_controller_B.work2_idx_2_im +
        lee_controller_B.e_y;
      if (lee_controller_B.temp_b < 1.0) {
        lee_controller_B.work2_idx_3_im = fabs
          (lee_controller_B.work1[lee_controller_B.b_x_tmp].re) + fabs
          (lee_controller_B.work1[lee_controller_B.b_x_tmp].im);
        if (lee_controller_B.work2_idx_3_im >= lee_controller_B.temp_b *
            1.1235582092889474E+307) {
          lee_controller_B.temp_b = 1.0 / lee_controller_B.work2_idx_3_im;
          lee_controller_B.d_re_tmp = 0;
          while (lee_controller_B.d_re_tmp <= lee_controller_B.i_o) {
            lee_controller_B.work1[lee_controller_B.d_re_tmp].re *=
              lee_controller_B.temp_b;
            lee_controller_B.work1[lee_controller_B.d_re_tmp].im *=
              lee_controller_B.temp_b;
            lee_controller_B.d_re_tmp++;
          }
        }
      }

      lee_controller_B.temp_b = lee_controller_B.work1[lee_controller_B.b_x_tmp]
        .re;
      lee_controller_B.work2_idx_3_im =
        lee_controller_B.work1[lee_controller_B.b_x_tmp].im;
      if (lee_controller_B.scale_j == 0.0) {
        if (-lee_controller_B.work2_idx_3_im == 0.0) {
          lee_controller_B.work1[lee_controller_B.b_x_tmp].re =
            -lee_controller_B.temp_b / lee_controller_B.work2_idx_3_re;
          lee_controller_B.work1[lee_controller_B.b_x_tmp].im = 0.0;
        } else if (-lee_controller_B.temp_b == 0.0) {
          lee_controller_B.work1[lee_controller_B.b_x_tmp].re = 0.0;
          lee_controller_B.work1[lee_controller_B.b_x_tmp].im =
            -lee_controller_B.work2_idx_3_im / lee_controller_B.work2_idx_3_re;
        } else {
          lee_controller_B.work1[lee_controller_B.b_x_tmp].re =
            -lee_controller_B.temp_b / lee_controller_B.work2_idx_3_re;
          lee_controller_B.work1[lee_controller_B.b_x_tmp].im =
            -lee_controller_B.work2_idx_3_im / lee_controller_B.work2_idx_3_re;
        }
      } else if (lee_controller_B.work2_idx_3_re == 0.0) {
        if (-lee_controller_B.temp_b == 0.0) {
          lee_controller_B.work1[lee_controller_B.b_x_tmp].re =
            -lee_controller_B.work2_idx_3_im / lee_controller_B.scale_j;
          lee_controller_B.work1[lee_controller_B.b_x_tmp].im = 0.0;
        } else if (-lee_controller_B.work2_idx_3_im == 0.0) {
          lee_controller_B.work1[lee_controller_B.b_x_tmp].re = 0.0;
          lee_controller_B.work1[lee_controller_B.b_x_tmp].im =
            -(-lee_controller_B.temp_b / lee_controller_B.scale_j);
        } else {
          lee_controller_B.work1[lee_controller_B.b_x_tmp].re =
            -lee_controller_B.work2_idx_3_im / lee_controller_B.scale_j;
          lee_controller_B.work1[lee_controller_B.b_x_tmp].im =
            -(-lee_controller_B.temp_b / lee_controller_B.scale_j);
        }
      } else if (lee_controller_B.work2_idx_2_im > lee_controller_B.e_y) {
        lee_controller_B.work2_idx_2_im = lee_controller_B.scale_j /
          lee_controller_B.work2_idx_3_re;
        lee_controller_B.scale_j = lee_controller_B.work2_idx_2_im *
          lee_controller_B.scale_j + lee_controller_B.work2_idx_3_re;
        lee_controller_B.work1[lee_controller_B.b_x_tmp].re =
          (lee_controller_B.work2_idx_2_im * -lee_controller_B.work2_idx_3_im +
           -lee_controller_B.temp_b) / lee_controller_B.scale_j;
        lee_controller_B.work1[lee_controller_B.b_x_tmp].im =
          (-lee_controller_B.work2_idx_3_im - lee_controller_B.work2_idx_2_im *
           -lee_controller_B.temp_b) / lee_controller_B.scale_j;
      } else if (lee_controller_B.e_y == lee_controller_B.work2_idx_2_im) {
        lee_controller_B.work2_idx_3_re = lee_controller_B.work2_idx_3_re > 0.0 ?
          0.5 : -0.5;
        lee_controller_B.scale_j = lee_controller_B.scale_j > 0.0 ? 0.5 : -0.5;
        lee_controller_B.work1[lee_controller_B.b_x_tmp].re =
          (-lee_controller_B.temp_b * lee_controller_B.work2_idx_3_re +
           -lee_controller_B.work2_idx_3_im * lee_controller_B.scale_j) /
          lee_controller_B.work2_idx_2_im;
        lee_controller_B.work1[lee_controller_B.b_x_tmp].im =
          (-lee_controller_B.work2_idx_3_im * lee_controller_B.work2_idx_3_re -
           -lee_controller_B.temp_b * lee_controller_B.scale_j) /
          lee_controller_B.work2_idx_2_im;
      } else {
        lee_controller_B.work2_idx_2_im = lee_controller_B.work2_idx_3_re /
          lee_controller_B.scale_j;
        lee_controller_B.scale_j += lee_controller_B.work2_idx_2_im *
          lee_controller_B.work2_idx_3_re;
        lee_controller_B.work1[lee_controller_B.b_x_tmp].re =
          (lee_controller_B.work2_idx_2_im * -lee_controller_B.temp_b +
           -lee_controller_B.work2_idx_3_im) / lee_controller_B.scale_j;
        lee_controller_B.work1[lee_controller_B.b_x_tmp].im =
          (lee_controller_B.work2_idx_2_im * -lee_controller_B.work2_idx_3_im -
           (-lee_controller_B.temp_b)) / lee_controller_B.scale_j;
      }

      if (lee_controller_B.b_x_tmp + 1 > 1) {
        if (fabs(lee_controller_B.work1[lee_controller_B.b_x_tmp].re) + fabs
            (lee_controller_B.work1[lee_controller_B.b_x_tmp].im) > 1.0) {
          lee_controller_B.temp_b = 1.0 / (fabs
            (lee_controller_B.work1[lee_controller_B.b_x_tmp].re) + fabs
            (lee_controller_B.work1[lee_controller_B.b_x_tmp].im));
          if (lee_controller_B.acoeff *
              lee_controller_B.rworka[lee_controller_B.b_x_tmp] >=
              1.1235582092889474E+307 * lee_controller_B.temp_b) {
            lee_controller_B.d_re_tmp = 0;
            while (lee_controller_B.d_re_tmp <= lee_controller_B.i_o) {
              lee_controller_B.work1[lee_controller_B.d_re_tmp].re *=
                lee_controller_B.temp_b;
              lee_controller_B.work1[lee_controller_B.d_re_tmp].im *=
                lee_controller_B.temp_b;
              lee_controller_B.d_re_tmp++;
            }
          }
        }

        lee_controller_B.work2_idx_3_re = lee_controller_B.acoeff *
          lee_controller_B.work1[lee_controller_B.b_x_tmp].re;
        lee_controller_B.scale_j = lee_controller_B.acoeff *
          lee_controller_B.work1[lee_controller_B.b_x_tmp].im;
        lee_controller_B.e_jr = 0;
        while (lee_controller_B.e_jr <= lee_controller_B.b_x_tmp - 1) {
          lee_controller_B.d_re_tmp = lee_controller_B.work2_idx_0_re_tmp_b +
            lee_controller_B.e_jr;
          lee_controller_B.temp_b = A[lee_controller_B.d_re_tmp].im;
          lee_controller_B.work2_idx_3_im = A[lee_controller_B.d_re_tmp].re;
          lee_controller_B.work1[lee_controller_B.e_jr].re +=
            lee_controller_B.work2_idx_3_im * lee_controller_B.work2_idx_3_re -
            lee_controller_B.temp_b * lee_controller_B.scale_j;
          lee_controller_B.work1[lee_controller_B.e_jr].im +=
            lee_controller_B.temp_b * lee_controller_B.work2_idx_3_re +
            lee_controller_B.work2_idx_3_im * lee_controller_B.scale_j;
          lee_controller_B.e_jr++;
        }
      }

      lee_controller_B.b_x_tmp--;
    }

    lee_controller_B.salpha_re = 0.0;
    lee_controller_B.salpha_im = 0.0;
    lee_controller_B.acoeff = 0.0;
    lee_controller_B.dmin = 0.0;
    lee_controller_B.scale_j = 0.0;
    lee_controller_B.work2_idx_2_im = 0.0;
    lee_controller_B.work2_idx_3_re = 0.0;
    lee_controller_B.work2_idx_3_im = 0.0;
    lee_controller_B.b_x_tmp = 0;
    while (lee_controller_B.b_x_tmp <= lee_controller_B.i_o) {
      lee_controller_B.work2_idx_0_re_tmp_b = lee_controller_B.b_x_tmp << 2;
      lee_controller_B.work2_idx_0_re_tmp =
        V[lee_controller_B.work2_idx_0_re_tmp_b].re;
      lee_controller_B.temp_b = lee_controller_B.work1[lee_controller_B.b_x_tmp]
        .im;
      lee_controller_B.work2_idx_0_re_tmp_f =
        V[lee_controller_B.work2_idx_0_re_tmp_b].im;
      lee_controller_B.e_y = lee_controller_B.work1[lee_controller_B.b_x_tmp].re;
      lee_controller_B.salpha_re += lee_controller_B.work2_idx_0_re_tmp *
        lee_controller_B.e_y - lee_controller_B.work2_idx_0_re_tmp_f *
        lee_controller_B.temp_b;
      lee_controller_B.salpha_im += lee_controller_B.work2_idx_0_re_tmp *
        lee_controller_B.temp_b + lee_controller_B.work2_idx_0_re_tmp_f *
        lee_controller_B.e_y;
      lee_controller_B.work2_idx_0_re_tmp =
        V[lee_controller_B.work2_idx_0_re_tmp_b + 1].re;
      lee_controller_B.work2_idx_0_re_tmp_f =
        V[lee_controller_B.work2_idx_0_re_tmp_b + 1].im;
      lee_controller_B.acoeff += lee_controller_B.work2_idx_0_re_tmp *
        lee_controller_B.e_y - lee_controller_B.work2_idx_0_re_tmp_f *
        lee_controller_B.temp_b;
      lee_controller_B.dmin += lee_controller_B.work2_idx_0_re_tmp *
        lee_controller_B.temp_b + lee_controller_B.work2_idx_0_re_tmp_f *
        lee_controller_B.e_y;
      lee_controller_B.work2_idx_0_re_tmp =
        V[lee_controller_B.work2_idx_0_re_tmp_b + 2].re;
      lee_controller_B.work2_idx_0_re_tmp_f =
        V[lee_controller_B.work2_idx_0_re_tmp_b + 2].im;
      lee_controller_B.scale_j += lee_controller_B.work2_idx_0_re_tmp *
        lee_controller_B.e_y - lee_controller_B.work2_idx_0_re_tmp_f *
        lee_controller_B.temp_b;
      lee_controller_B.work2_idx_2_im += lee_controller_B.work2_idx_0_re_tmp *
        lee_controller_B.temp_b + lee_controller_B.work2_idx_0_re_tmp_f *
        lee_controller_B.e_y;
      lee_controller_B.work2_idx_0_re_tmp =
        V[lee_controller_B.work2_idx_0_re_tmp_b + 3].re;
      lee_controller_B.work2_idx_0_re_tmp_f =
        V[lee_controller_B.work2_idx_0_re_tmp_b + 3].im;
      lee_controller_B.work2_idx_3_re += lee_controller_B.work2_idx_0_re_tmp *
        lee_controller_B.e_y - lee_controller_B.work2_idx_0_re_tmp_f *
        lee_controller_B.temp_b;
      lee_controller_B.work2_idx_3_im += lee_controller_B.work2_idx_0_re_tmp *
        lee_controller_B.temp_b + lee_controller_B.work2_idx_0_re_tmp_f *
        lee_controller_B.e_y;
      lee_controller_B.b_x_tmp++;
    }

    lee_controller_B.temp_b = fabs(lee_controller_B.salpha_re) + fabs
      (lee_controller_B.salpha_im);
    lee_controller_B.e_y = fabs(lee_controller_B.acoeff) + fabs
      (lee_controller_B.dmin);
    if (lee_controller_B.e_y > lee_controller_B.temp_b) {
      lee_controller_B.temp_b = lee_controller_B.e_y;
    }

    lee_controller_B.e_y = fabs(lee_controller_B.scale_j) + fabs
      (lee_controller_B.work2_idx_2_im);
    if (lee_controller_B.e_y > lee_controller_B.temp_b) {
      lee_controller_B.temp_b = lee_controller_B.e_y;
    }

    lee_controller_B.e_y = fabs(lee_controller_B.work2_idx_3_re) + fabs
      (lee_controller_B.work2_idx_3_im);
    if (lee_controller_B.e_y > lee_controller_B.temp_b) {
      lee_controller_B.temp_b = lee_controller_B.e_y;
    }

    if (lee_controller_B.temp_b > 2.2250738585072014E-308) {
      lee_controller_B.temp_b = 1.0 / lee_controller_B.temp_b;
      V[lee_controller_B.b_x_tmp_tmp].re = lee_controller_B.temp_b *
        lee_controller_B.salpha_re;
      V[lee_controller_B.b_x_tmp_tmp].im = lee_controller_B.temp_b *
        lee_controller_B.salpha_im;
      lee_controller_B.d_re_tmp = (lee_controller_B.i_o << 2) + 1;
      V[lee_controller_B.d_re_tmp].re = lee_controller_B.temp_b *
        lee_controller_B.acoeff;
      V[lee_controller_B.d_re_tmp].im = lee_controller_B.temp_b *
        lee_controller_B.dmin;
      lee_controller_B.d_re_tmp = (lee_controller_B.i_o << 2) + 2;
      V[lee_controller_B.d_re_tmp].re = lee_controller_B.temp_b *
        lee_controller_B.scale_j;
      V[lee_controller_B.d_re_tmp].im = lee_controller_B.temp_b *
        lee_controller_B.work2_idx_2_im;
      lee_controller_B.d_re_tmp = (lee_controller_B.i_o << 2) + 3;
      V[lee_controller_B.d_re_tmp].re = lee_controller_B.temp_b *
        lee_controller_B.work2_idx_3_re;
      V[lee_controller_B.d_re_tmp].im = lee_controller_B.temp_b *
        lee_controller_B.work2_idx_3_im;
    } else {
      V[lee_controller_B.b_x_tmp_tmp].re = 0.0;
      V[lee_controller_B.b_x_tmp_tmp].im = 0.0;
      V[lee_controller_B.b_x_tmp_tmp + 1].re = 0.0;
      V[lee_controller_B.b_x_tmp_tmp + 1].im = 0.0;
      V[lee_controller_B.b_x_tmp_tmp + 2].re = 0.0;
      V[lee_controller_B.b_x_tmp_tmp + 2].im = 0.0;
      V[lee_controller_B.b_x_tmp_tmp + 3].re = 0.0;
      V[lee_controller_B.b_x_tmp_tmp + 3].im = 0.0;
    }
  }
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_eigStandard(const real_T A[16], creal_T V[16],
  creal_T D[4])
{
  boolean_T exitg1;
  for (lee_controller_B.stemp_re_tmp = 0; lee_controller_B.stemp_re_tmp < 16;
       lee_controller_B.stemp_re_tmp++) {
    lee_controller_B.At[lee_controller_B.stemp_re_tmp].re =
      A[lee_controller_B.stemp_re_tmp];
    lee_controller_B.At[lee_controller_B.stemp_re_tmp].im = 0.0;
  }

  lee_controller_B.anrm = 0.0;
  lee_controller_B.b_k = 0;
  exitg1 = false;
  while ((!exitg1) && (lee_controller_B.b_k < 16)) {
    lee_controller_B.b_absxk = lee_controller_rt_hypotd_snf
      (lee_controller_B.At[lee_controller_B.b_k].re,
       lee_controller_B.At[lee_controller_B.b_k].im);
    if (rtIsNaN(lee_controller_B.b_absxk)) {
      lee_controller_B.anrm = (rtNaN);
      exitg1 = true;
    } else {
      if (lee_controller_B.b_absxk > lee_controller_B.anrm) {
        lee_controller_B.anrm = lee_controller_B.b_absxk;
      }

      lee_controller_B.b_k++;
    }
  }

  if (rtIsInf(lee_controller_B.anrm) || rtIsNaN(lee_controller_B.anrm)) {
    D[0].re = (rtNaN);
    D[0].im = 0.0;
    lee_controller_B.y[0].re = (rtNaN);
    lee_controller_B.y[0].im = 0.0;
    D[1].re = (rtNaN);
    D[1].im = 0.0;
    lee_controller_B.y[1].re = (rtNaN);
    lee_controller_B.y[1].im = 0.0;
    D[2].re = (rtNaN);
    D[2].im = 0.0;
    lee_controller_B.y[2].re = (rtNaN);
    lee_controller_B.y[2].im = 0.0;
    D[3].re = (rtNaN);
    D[3].im = 0.0;
    lee_controller_B.y[3].re = (rtNaN);
    lee_controller_B.y[3].im = 0.0;
    for (lee_controller_B.stemp_re_tmp = 0; lee_controller_B.stemp_re_tmp < 16;
         lee_controller_B.stemp_re_tmp++) {
      V[lee_controller_B.stemp_re_tmp].re = (rtNaN);
      V[lee_controller_B.stemp_re_tmp].im = 0.0;
    }
  } else {
    boolean_T guard1 = false;
    lee_controller_B.ilascl = false;
    lee_controller_B.b_absxk = lee_controller_B.anrm;
    guard1 = false;
    if ((lee_controller_B.anrm > 0.0) && (lee_controller_B.anrm <
         6.7178761075670888E-139)) {
      lee_controller_B.b_absxk = 6.7178761075670888E-139;
      lee_controller_B.ilascl = true;
      guard1 = true;
    } else if (lee_controller_B.anrm > 1.4885657073574029E+138) {
      lee_controller_B.b_absxk = 1.4885657073574029E+138;
      lee_controller_B.ilascl = true;
      guard1 = true;
    }

    if (guard1) {
      lee_controller_B.cfromc = lee_controller_B.anrm;
      lee_controller_B.ctoc = lee_controller_B.b_absxk;
      lee_controller_B.notdone = true;
      while (lee_controller_B.notdone) {
        lee_controller_B.vtemp = lee_controller_B.cfromc *
          2.0041683600089728E-292;
        lee_controller_B.cto1 = lee_controller_B.ctoc / 4.9896007738368E+291;
        if ((lee_controller_B.vtemp > lee_controller_B.ctoc) &&
            (lee_controller_B.ctoc != 0.0)) {
          lee_controller_B.stemp_im_tmp = 2.0041683600089728E-292;
          lee_controller_B.cfromc = lee_controller_B.vtemp;
        } else if (lee_controller_B.cto1 > lee_controller_B.cfromc) {
          lee_controller_B.stemp_im_tmp = 4.9896007738368E+291;
          lee_controller_B.ctoc = lee_controller_B.cto1;
        } else {
          lee_controller_B.stemp_im_tmp = lee_controller_B.ctoc /
            lee_controller_B.cfromc;
          lee_controller_B.notdone = false;
        }

        for (lee_controller_B.stemp_re_tmp = 0; lee_controller_B.stemp_re_tmp <
             16; lee_controller_B.stemp_re_tmp++) {
          lee_controller_B.tmp =
            lee_controller_B.At[lee_controller_B.stemp_re_tmp];
          lee_controller_B.tmp.re *= lee_controller_B.stemp_im_tmp;
          lee_controller_B.tmp.im *= lee_controller_B.stemp_im_tmp;
          lee_controller_B.At[lee_controller_B.stemp_re_tmp] =
            lee_controller_B.tmp;
        }
      }
    }

    lee_controller_xzggbal(lee_controller_B.At, &lee_controller_B.c_i,
      &lee_controller_B.b_k, lee_controller_B.rscale);
    memset(&V[0], 0, sizeof(creal_T) << 4U);
    V[0].re = 1.0;
    V[0].im = 0.0;
    V[5].re = 1.0;
    V[5].im = 0.0;
    V[10].re = 1.0;
    V[10].im = 0.0;
    V[15].re = 1.0;
    V[15].im = 0.0;
    if (lee_controller_B.b_k >= lee_controller_B.c_i + 2) {
      lee_controller_B.jcol = lee_controller_B.c_i - 1;
      while (lee_controller_B.jcol + 1 < lee_controller_B.b_k - 1) {
        lee_controller_B.jrow = lee_controller_B.b_k - 1;
        while (lee_controller_B.jrow + 1 > lee_controller_B.jcol + 2) {
          lee_controller_xzlartg(lee_controller_B.At[(lee_controller_B.jrow +
            (lee_controller_B.jcol << 2)) - 1],
            lee_controller_B.At[lee_controller_B.jrow + (lee_controller_B.jcol <<
            2)], &lee_controller_B.cfromc, &lee_controller_B.tmp,
            &lee_controller_B.At[(lee_controller_B.jrow + (lee_controller_B.jcol
            << 2)) - 1]);
          lee_controller_B.stemp_re_tmp = (lee_controller_B.jcol << 2) +
            lee_controller_B.jrow;
          lee_controller_B.At[lee_controller_B.stemp_re_tmp].re = 0.0;
          lee_controller_B.At[lee_controller_B.stemp_re_tmp].im = 0.0;
          lee_controller_B.b_j = lee_controller_B.jcol + 1;
          while (lee_controller_B.b_j + 1 <= 4) {
            lee_controller_B.stemp_re_tmp = (lee_controller_B.b_j << 2) +
              lee_controller_B.jrow;
            lee_controller_B.ctoc =
              lee_controller_B.At[lee_controller_B.stemp_re_tmp].im;
            lee_controller_B.vtemp =
              lee_controller_B.At[lee_controller_B.stemp_re_tmp].re;
            lee_controller_B.cto1 =
              lee_controller_B.At[lee_controller_B.stemp_re_tmp - 1].re;
            lee_controller_B.stemp_im_tmp =
              lee_controller_B.At[lee_controller_B.stemp_re_tmp - 1].im;
            lee_controller_B.At[lee_controller_B.stemp_re_tmp].re =
              lee_controller_B.vtemp * lee_controller_B.cfromc -
              (lee_controller_B.cto1 * lee_controller_B.tmp.re +
               lee_controller_B.stemp_im_tmp * lee_controller_B.tmp.im);
            lee_controller_B.At[lee_controller_B.stemp_re_tmp].im =
              lee_controller_B.ctoc * lee_controller_B.cfromc -
              (lee_controller_B.stemp_im_tmp * lee_controller_B.tmp.re -
               lee_controller_B.tmp.im * lee_controller_B.cto1);
            lee_controller_B.At[lee_controller_B.stemp_re_tmp - 1].re =
              (lee_controller_B.vtemp * lee_controller_B.tmp.re -
               lee_controller_B.ctoc * lee_controller_B.tmp.im) +
              lee_controller_B.cto1 * lee_controller_B.cfromc;
            lee_controller_B.At[lee_controller_B.stemp_re_tmp - 1].im =
              (lee_controller_B.ctoc * lee_controller_B.tmp.re +
               lee_controller_B.vtemp * lee_controller_B.tmp.im) +
              lee_controller_B.stemp_im_tmp * lee_controller_B.cfromc;
            lee_controller_B.b_j++;
          }

          lee_controller_B.tmp.re = -lee_controller_B.tmp.re;
          lee_controller_B.tmp.im = -lee_controller_B.tmp.im;
          lee_controller_B.b_j = 0;
          while (lee_controller_B.b_j + 1 <= lee_controller_B.b_k) {
            lee_controller_B.stemp_re_tmp = ((lee_controller_B.jrow - 1) << 2) +
              lee_controller_B.b_j;
            lee_controller_B.ctoc =
              lee_controller_B.At[lee_controller_B.stemp_re_tmp].im;
            lee_controller_B.vtemp =
              lee_controller_B.At[lee_controller_B.stemp_re_tmp].re;
            lee_controller_B.stemp_re_tmp_p = (lee_controller_B.jrow << 2) +
              lee_controller_B.b_j;
            lee_controller_B.cto1 =
              lee_controller_B.At[lee_controller_B.stemp_re_tmp_p].re;
            lee_controller_B.stemp_im_tmp =
              lee_controller_B.At[lee_controller_B.stemp_re_tmp_p].im;
            lee_controller_B.At[lee_controller_B.stemp_re_tmp].re =
              lee_controller_B.vtemp * lee_controller_B.cfromc -
              (lee_controller_B.cto1 * lee_controller_B.tmp.re +
               lee_controller_B.stemp_im_tmp * lee_controller_B.tmp.im);
            lee_controller_B.At[lee_controller_B.stemp_re_tmp].im =
              lee_controller_B.ctoc * lee_controller_B.cfromc -
              (lee_controller_B.stemp_im_tmp * lee_controller_B.tmp.re -
               lee_controller_B.tmp.im * lee_controller_B.cto1);
            lee_controller_B.At[lee_controller_B.stemp_re_tmp_p].re =
              (lee_controller_B.vtemp * lee_controller_B.tmp.re -
               lee_controller_B.ctoc * lee_controller_B.tmp.im) +
              lee_controller_B.cto1 * lee_controller_B.cfromc;
            lee_controller_B.At[lee_controller_B.stemp_re_tmp_p].im =
              (lee_controller_B.ctoc * lee_controller_B.tmp.re +
               lee_controller_B.vtemp * lee_controller_B.tmp.im) +
              lee_controller_B.stemp_im_tmp * lee_controller_B.cfromc;
            lee_controller_B.b_j++;
          }

          lee_controller_B.stemp_re_tmp = (lee_controller_B.jrow - 1) << 2;
          lee_controller_B.ctoc = V[lee_controller_B.stemp_re_tmp].im;
          lee_controller_B.vtemp = V[lee_controller_B.stemp_re_tmp].re;
          lee_controller_B.stemp_re_tmp_p = lee_controller_B.jrow << 2;
          lee_controller_B.cto1 = V[lee_controller_B.stemp_re_tmp_p].re;
          lee_controller_B.stemp_im_tmp = V[lee_controller_B.stemp_re_tmp_p].im;
          V[lee_controller_B.stemp_re_tmp].re = lee_controller_B.vtemp *
            lee_controller_B.cfromc - (lee_controller_B.cto1 *
            lee_controller_B.tmp.re + lee_controller_B.stemp_im_tmp *
            lee_controller_B.tmp.im);
          V[lee_controller_B.stemp_re_tmp].im = lee_controller_B.ctoc *
            lee_controller_B.cfromc - (lee_controller_B.stemp_im_tmp *
            lee_controller_B.tmp.re - lee_controller_B.tmp.im *
            lee_controller_B.cto1);
          V[lee_controller_B.stemp_re_tmp_p].re = (lee_controller_B.vtemp *
            lee_controller_B.tmp.re - lee_controller_B.ctoc *
            lee_controller_B.tmp.im) + lee_controller_B.cto1 *
            lee_controller_B.cfromc;
          V[lee_controller_B.stemp_re_tmp_p].im = (lee_controller_B.ctoc *
            lee_controller_B.tmp.re + lee_controller_B.vtemp *
            lee_controller_B.tmp.im) + lee_controller_B.stemp_im_tmp *
            lee_controller_B.cfromc;
          lee_controller_B.ctoc = V[lee_controller_B.stemp_re_tmp + 1].im;
          lee_controller_B.vtemp = V[lee_controller_B.stemp_re_tmp + 1].re;
          lee_controller_B.cto1 = V[lee_controller_B.stemp_re_tmp_p + 1].re;
          lee_controller_B.stemp_im_tmp = V[lee_controller_B.stemp_re_tmp_p + 1]
            .im;
          V[lee_controller_B.stemp_re_tmp + 1].re = lee_controller_B.vtemp *
            lee_controller_B.cfromc - (lee_controller_B.cto1 *
            lee_controller_B.tmp.re + lee_controller_B.stemp_im_tmp *
            lee_controller_B.tmp.im);
          V[lee_controller_B.stemp_re_tmp + 1].im = lee_controller_B.ctoc *
            lee_controller_B.cfromc - (lee_controller_B.stemp_im_tmp *
            lee_controller_B.tmp.re - lee_controller_B.tmp.im *
            lee_controller_B.cto1);
          V[lee_controller_B.stemp_re_tmp_p + 1].re = (lee_controller_B.vtemp *
            lee_controller_B.tmp.re - lee_controller_B.ctoc *
            lee_controller_B.tmp.im) + lee_controller_B.cto1 *
            lee_controller_B.cfromc;
          V[lee_controller_B.stemp_re_tmp_p + 1].im = (lee_controller_B.ctoc *
            lee_controller_B.tmp.re + lee_controller_B.vtemp *
            lee_controller_B.tmp.im) + lee_controller_B.stemp_im_tmp *
            lee_controller_B.cfromc;
          lee_controller_B.ctoc = V[lee_controller_B.stemp_re_tmp + 2].im;
          lee_controller_B.vtemp = V[lee_controller_B.stemp_re_tmp + 2].re;
          lee_controller_B.cto1 = V[lee_controller_B.stemp_re_tmp_p + 2].re;
          lee_controller_B.stemp_im_tmp = V[lee_controller_B.stemp_re_tmp_p + 2]
            .im;
          V[lee_controller_B.stemp_re_tmp + 2].re = lee_controller_B.vtemp *
            lee_controller_B.cfromc - (lee_controller_B.cto1 *
            lee_controller_B.tmp.re + lee_controller_B.stemp_im_tmp *
            lee_controller_B.tmp.im);
          V[lee_controller_B.stemp_re_tmp + 2].im = lee_controller_B.ctoc *
            lee_controller_B.cfromc - (lee_controller_B.stemp_im_tmp *
            lee_controller_B.tmp.re - lee_controller_B.tmp.im *
            lee_controller_B.cto1);
          V[lee_controller_B.stemp_re_tmp_p + 2].re = (lee_controller_B.vtemp *
            lee_controller_B.tmp.re - lee_controller_B.ctoc *
            lee_controller_B.tmp.im) + lee_controller_B.cto1 *
            lee_controller_B.cfromc;
          V[lee_controller_B.stemp_re_tmp_p + 2].im = (lee_controller_B.ctoc *
            lee_controller_B.tmp.re + lee_controller_B.vtemp *
            lee_controller_B.tmp.im) + lee_controller_B.stemp_im_tmp *
            lee_controller_B.cfromc;
          lee_controller_B.ctoc = V[lee_controller_B.stemp_re_tmp + 3].im;
          lee_controller_B.vtemp = V[lee_controller_B.stemp_re_tmp + 3].re;
          lee_controller_B.cto1 = V[lee_controller_B.stemp_re_tmp_p + 3].re;
          lee_controller_B.stemp_im_tmp = V[lee_controller_B.stemp_re_tmp_p + 3]
            .im;
          V[lee_controller_B.stemp_re_tmp + 3].re = lee_controller_B.vtemp *
            lee_controller_B.cfromc - (lee_controller_B.cto1 *
            lee_controller_B.tmp.re + lee_controller_B.stemp_im_tmp *
            lee_controller_B.tmp.im);
          V[lee_controller_B.stemp_re_tmp + 3].im = lee_controller_B.ctoc *
            lee_controller_B.cfromc - (lee_controller_B.stemp_im_tmp *
            lee_controller_B.tmp.re - lee_controller_B.tmp.im *
            lee_controller_B.cto1);
          V[lee_controller_B.stemp_re_tmp_p + 3].re = (lee_controller_B.vtemp *
            lee_controller_B.tmp.re - lee_controller_B.ctoc *
            lee_controller_B.tmp.im) + lee_controller_B.cto1 *
            lee_controller_B.cfromc;
          V[lee_controller_B.stemp_re_tmp_p + 3].im = (lee_controller_B.ctoc *
            lee_controller_B.tmp.re + lee_controller_B.vtemp *
            lee_controller_B.tmp.im) + lee_controller_B.stemp_im_tmp *
            lee_controller_B.cfromc;
          lee_controller_B.jrow--;
        }

        lee_controller_B.jcol++;
      }
    }

    lee_controller_xzhgeqz(lee_controller_B.At, lee_controller_B.c_i,
      lee_controller_B.b_k, V, &lee_controller_B.jcol, D, lee_controller_B.y);
    if (lee_controller_B.jcol == 0) {
      lee_controller_xztgevc(lee_controller_B.At, V);
      if (lee_controller_B.c_i > 1) {
        lee_controller_B.c_i -= 2;
        while (lee_controller_B.c_i + 1 >= 1) {
          lee_controller_B.jcol = lee_controller_B.rscale[lee_controller_B.c_i]
            - 1;
          if (lee_controller_B.c_i + 1 !=
              lee_controller_B.rscale[lee_controller_B.c_i]) {
            lee_controller_B.tmp = V[lee_controller_B.c_i];
            V[lee_controller_B.c_i] = V[lee_controller_B.jcol];
            V[lee_controller_B.jcol] = lee_controller_B.tmp;
            lee_controller_B.tmp = V[lee_controller_B.c_i + 4];
            V[lee_controller_B.c_i + 4] = V[lee_controller_B.jcol + 4];
            V[lee_controller_B.jcol + 4] = lee_controller_B.tmp;
            lee_controller_B.tmp = V[lee_controller_B.c_i + 8];
            V[lee_controller_B.c_i + 8] = V[lee_controller_B.jcol + 8];
            V[lee_controller_B.jcol + 8] = lee_controller_B.tmp;
            lee_controller_B.tmp = V[lee_controller_B.c_i + 12];
            V[lee_controller_B.c_i + 12] = V[lee_controller_B.jcol + 12];
            V[lee_controller_B.jcol + 12] = lee_controller_B.tmp;
          }

          lee_controller_B.c_i--;
        }
      }

      if (lee_controller_B.b_k < 4) {
        while (lee_controller_B.b_k + 1 < 5) {
          lee_controller_B.jcol = lee_controller_B.rscale[lee_controller_B.b_k]
            - 1;
          if (lee_controller_B.b_k + 1 !=
              lee_controller_B.rscale[lee_controller_B.b_k]) {
            lee_controller_B.tmp = V[lee_controller_B.b_k];
            V[lee_controller_B.b_k] = V[lee_controller_B.jcol];
            V[lee_controller_B.jcol] = lee_controller_B.tmp;
            lee_controller_B.tmp = V[lee_controller_B.b_k + 4];
            V[lee_controller_B.b_k + 4] = V[lee_controller_B.jcol + 4];
            V[lee_controller_B.jcol + 4] = lee_controller_B.tmp;
            lee_controller_B.tmp = V[lee_controller_B.b_k + 8];
            V[lee_controller_B.b_k + 8] = V[lee_controller_B.jcol + 8];
            V[lee_controller_B.jcol + 8] = lee_controller_B.tmp;
            lee_controller_B.tmp = V[lee_controller_B.b_k + 12];
            V[lee_controller_B.b_k + 12] = V[lee_controller_B.jcol + 12];
            V[lee_controller_B.jcol + 12] = lee_controller_B.tmp;
          }

          lee_controller_B.b_k++;
        }
      }

      for (lee_controller_B.b_k = 0; lee_controller_B.b_k < 4;
           lee_controller_B.b_k++) {
        lee_controller_B.c_i = lee_controller_B.b_k << 2;
        lee_controller_B.cfromc = V[lee_controller_B.c_i].re;
        lee_controller_B.ctoc = V[lee_controller_B.c_i].im;
        lee_controller_B.vtemp = fabs(lee_controller_B.cfromc) + fabs
          (lee_controller_B.ctoc);
        lee_controller_B.cto1 = fabs(V[lee_controller_B.c_i + 1].re) + fabs
          (V[lee_controller_B.c_i + 1].im);
        if (lee_controller_B.cto1 > lee_controller_B.vtemp) {
          lee_controller_B.vtemp = lee_controller_B.cto1;
        }

        lee_controller_B.cto1 = fabs(V[lee_controller_B.c_i + 2].re) + fabs
          (V[lee_controller_B.c_i + 2].im);
        if (lee_controller_B.cto1 > lee_controller_B.vtemp) {
          lee_controller_B.vtemp = lee_controller_B.cto1;
        }

        lee_controller_B.cto1 = fabs(V[lee_controller_B.c_i + 3].re) + fabs
          (V[lee_controller_B.c_i + 3].im);
        if (lee_controller_B.cto1 > lee_controller_B.vtemp) {
          lee_controller_B.vtemp = lee_controller_B.cto1;
        }

        if (lee_controller_B.vtemp >= 6.7178761075670888E-139) {
          lee_controller_B.vtemp = 1.0 / lee_controller_B.vtemp;
          V[lee_controller_B.c_i].re = lee_controller_B.cfromc *
            lee_controller_B.vtemp;
          V[lee_controller_B.c_i].im = lee_controller_B.ctoc *
            lee_controller_B.vtemp;
          V[lee_controller_B.c_i + 1].re *= lee_controller_B.vtemp;
          V[lee_controller_B.c_i + 1].im *= lee_controller_B.vtemp;
          V[lee_controller_B.c_i + 2].re *= lee_controller_B.vtemp;
          V[lee_controller_B.c_i + 2].im *= lee_controller_B.vtemp;
          V[lee_controller_B.c_i + 3].re *= lee_controller_B.vtemp;
          V[lee_controller_B.c_i + 3].im *= lee_controller_B.vtemp;
        }
      }

      if (lee_controller_B.ilascl) {
        lee_controller_B.ilascl = true;
        while (lee_controller_B.ilascl) {
          lee_controller_B.cfromc = lee_controller_B.b_absxk *
            2.0041683600089728E-292;
          lee_controller_B.ctoc = lee_controller_B.anrm / 4.9896007738368E+291;
          if ((lee_controller_B.cfromc > lee_controller_B.anrm) &&
              (lee_controller_B.anrm != 0.0)) {
            lee_controller_B.vtemp = 2.0041683600089728E-292;
            lee_controller_B.b_absxk = lee_controller_B.cfromc;
          } else if (lee_controller_B.ctoc > lee_controller_B.b_absxk) {
            lee_controller_B.vtemp = 4.9896007738368E+291;
            lee_controller_B.anrm = lee_controller_B.ctoc;
          } else {
            lee_controller_B.vtemp = lee_controller_B.anrm /
              lee_controller_B.b_absxk;
            lee_controller_B.ilascl = false;
          }

          D[0].re *= lee_controller_B.vtemp;
          D[0].im *= lee_controller_B.vtemp;
          D[1].re *= lee_controller_B.vtemp;
          D[1].im *= lee_controller_B.vtemp;
          D[2].re *= lee_controller_B.vtemp;
          D[2].im *= lee_controller_B.vtemp;
          D[3].re *= lee_controller_B.vtemp;
          D[3].im *= lee_controller_B.vtemp;
        }
      }
    }
  }

  lee_controller_B.anrm = 0.0;
  lee_controller_B.b_absxk = 3.3121686421112381E-170;
  lee_controller_B.b_k = 0;
  while (lee_controller_B.b_k + 1 <= 4) {
    lee_controller_B.cfromc = fabs(V[lee_controller_B.b_k].re);
    if (lee_controller_B.cfromc > lee_controller_B.b_absxk) {
      lee_controller_B.ctoc = lee_controller_B.b_absxk / lee_controller_B.cfromc;
      lee_controller_B.anrm = lee_controller_B.anrm * lee_controller_B.ctoc *
        lee_controller_B.ctoc + 1.0;
      lee_controller_B.b_absxk = lee_controller_B.cfromc;
    } else {
      lee_controller_B.ctoc = lee_controller_B.cfromc / lee_controller_B.b_absxk;
      lee_controller_B.anrm += lee_controller_B.ctoc * lee_controller_B.ctoc;
    }

    lee_controller_B.cfromc = fabs(V[lee_controller_B.b_k].im);
    if (lee_controller_B.cfromc > lee_controller_B.b_absxk) {
      lee_controller_B.ctoc = lee_controller_B.b_absxk / lee_controller_B.cfromc;
      lee_controller_B.anrm = lee_controller_B.anrm * lee_controller_B.ctoc *
        lee_controller_B.ctoc + 1.0;
      lee_controller_B.b_absxk = lee_controller_B.cfromc;
    } else {
      lee_controller_B.ctoc = lee_controller_B.cfromc / lee_controller_B.b_absxk;
      lee_controller_B.anrm += lee_controller_B.ctoc * lee_controller_B.ctoc;
    }

    lee_controller_B.b_k++;
  }

  lee_controller_B.anrm = lee_controller_B.b_absxk * sqrt(lee_controller_B.anrm);
  lee_controller_B.b_k = 0;
  while (lee_controller_B.b_k + 1 <= 4) {
    lee_controller_B.b_absxk = V[lee_controller_B.b_k].re;
    lee_controller_B.cfromc = V[lee_controller_B.b_k].im;
    if (lee_controller_B.cfromc == 0.0) {
      V[lee_controller_B.b_k].re = lee_controller_B.b_absxk /
        lee_controller_B.anrm;
      V[lee_controller_B.b_k].im = 0.0;
    } else if (lee_controller_B.b_absxk == 0.0) {
      V[lee_controller_B.b_k].re = 0.0;
      V[lee_controller_B.b_k].im = lee_controller_B.cfromc /
        lee_controller_B.anrm;
    } else {
      V[lee_controller_B.b_k].re = lee_controller_B.b_absxk /
        lee_controller_B.anrm;
      V[lee_controller_B.b_k].im = lee_controller_B.cfromc /
        lee_controller_B.anrm;
    }

    lee_controller_B.b_k++;
  }

  lee_controller_B.anrm = 0.0;
  lee_controller_B.b_absxk = 3.3121686421112381E-170;
  lee_controller_B.b_k = 4;
  while (lee_controller_B.b_k + 1 <= 8) {
    lee_controller_B.cfromc = fabs(V[lee_controller_B.b_k].re);
    if (lee_controller_B.cfromc > lee_controller_B.b_absxk) {
      lee_controller_B.ctoc = lee_controller_B.b_absxk / lee_controller_B.cfromc;
      lee_controller_B.anrm = lee_controller_B.anrm * lee_controller_B.ctoc *
        lee_controller_B.ctoc + 1.0;
      lee_controller_B.b_absxk = lee_controller_B.cfromc;
    } else {
      lee_controller_B.ctoc = lee_controller_B.cfromc / lee_controller_B.b_absxk;
      lee_controller_B.anrm += lee_controller_B.ctoc * lee_controller_B.ctoc;
    }

    lee_controller_B.cfromc = fabs(V[lee_controller_B.b_k].im);
    if (lee_controller_B.cfromc > lee_controller_B.b_absxk) {
      lee_controller_B.ctoc = lee_controller_B.b_absxk / lee_controller_B.cfromc;
      lee_controller_B.anrm = lee_controller_B.anrm * lee_controller_B.ctoc *
        lee_controller_B.ctoc + 1.0;
      lee_controller_B.b_absxk = lee_controller_B.cfromc;
    } else {
      lee_controller_B.ctoc = lee_controller_B.cfromc / lee_controller_B.b_absxk;
      lee_controller_B.anrm += lee_controller_B.ctoc * lee_controller_B.ctoc;
    }

    lee_controller_B.b_k++;
  }

  lee_controller_B.anrm = lee_controller_B.b_absxk * sqrt(lee_controller_B.anrm);
  lee_controller_B.b_k = 4;
  while (lee_controller_B.b_k + 1 <= 8) {
    lee_controller_B.b_absxk = V[lee_controller_B.b_k].re;
    lee_controller_B.cfromc = V[lee_controller_B.b_k].im;
    if (lee_controller_B.cfromc == 0.0) {
      V[lee_controller_B.b_k].re = lee_controller_B.b_absxk /
        lee_controller_B.anrm;
      V[lee_controller_B.b_k].im = 0.0;
    } else if (lee_controller_B.b_absxk == 0.0) {
      V[lee_controller_B.b_k].re = 0.0;
      V[lee_controller_B.b_k].im = lee_controller_B.cfromc /
        lee_controller_B.anrm;
    } else {
      V[lee_controller_B.b_k].re = lee_controller_B.b_absxk /
        lee_controller_B.anrm;
      V[lee_controller_B.b_k].im = lee_controller_B.cfromc /
        lee_controller_B.anrm;
    }

    lee_controller_B.b_k++;
  }

  lee_controller_B.anrm = 0.0;
  lee_controller_B.b_absxk = 3.3121686421112381E-170;
  lee_controller_B.b_k = 8;
  while (lee_controller_B.b_k + 1 <= 12) {
    lee_controller_B.cfromc = fabs(V[lee_controller_B.b_k].re);
    if (lee_controller_B.cfromc > lee_controller_B.b_absxk) {
      lee_controller_B.ctoc = lee_controller_B.b_absxk / lee_controller_B.cfromc;
      lee_controller_B.anrm = lee_controller_B.anrm * lee_controller_B.ctoc *
        lee_controller_B.ctoc + 1.0;
      lee_controller_B.b_absxk = lee_controller_B.cfromc;
    } else {
      lee_controller_B.ctoc = lee_controller_B.cfromc / lee_controller_B.b_absxk;
      lee_controller_B.anrm += lee_controller_B.ctoc * lee_controller_B.ctoc;
    }

    lee_controller_B.cfromc = fabs(V[lee_controller_B.b_k].im);
    if (lee_controller_B.cfromc > lee_controller_B.b_absxk) {
      lee_controller_B.ctoc = lee_controller_B.b_absxk / lee_controller_B.cfromc;
      lee_controller_B.anrm = lee_controller_B.anrm * lee_controller_B.ctoc *
        lee_controller_B.ctoc + 1.0;
      lee_controller_B.b_absxk = lee_controller_B.cfromc;
    } else {
      lee_controller_B.ctoc = lee_controller_B.cfromc / lee_controller_B.b_absxk;
      lee_controller_B.anrm += lee_controller_B.ctoc * lee_controller_B.ctoc;
    }

    lee_controller_B.b_k++;
  }

  lee_controller_B.anrm = lee_controller_B.b_absxk * sqrt(lee_controller_B.anrm);
  lee_controller_B.b_k = 8;
  while (lee_controller_B.b_k + 1 <= 12) {
    lee_controller_B.b_absxk = V[lee_controller_B.b_k].re;
    lee_controller_B.cfromc = V[lee_controller_B.b_k].im;
    if (lee_controller_B.cfromc == 0.0) {
      V[lee_controller_B.b_k].re = lee_controller_B.b_absxk /
        lee_controller_B.anrm;
      V[lee_controller_B.b_k].im = 0.0;
    } else if (lee_controller_B.b_absxk == 0.0) {
      V[lee_controller_B.b_k].re = 0.0;
      V[lee_controller_B.b_k].im = lee_controller_B.cfromc /
        lee_controller_B.anrm;
    } else {
      V[lee_controller_B.b_k].re = lee_controller_B.b_absxk /
        lee_controller_B.anrm;
      V[lee_controller_B.b_k].im = lee_controller_B.cfromc /
        lee_controller_B.anrm;
    }

    lee_controller_B.b_k++;
  }

  lee_controller_B.anrm = 0.0;
  lee_controller_B.b_absxk = 3.3121686421112381E-170;
  lee_controller_B.b_k = 12;
  while (lee_controller_B.b_k + 1 <= 16) {
    lee_controller_B.cfromc = fabs(V[lee_controller_B.b_k].re);
    if (lee_controller_B.cfromc > lee_controller_B.b_absxk) {
      lee_controller_B.ctoc = lee_controller_B.b_absxk / lee_controller_B.cfromc;
      lee_controller_B.anrm = lee_controller_B.anrm * lee_controller_B.ctoc *
        lee_controller_B.ctoc + 1.0;
      lee_controller_B.b_absxk = lee_controller_B.cfromc;
    } else {
      lee_controller_B.ctoc = lee_controller_B.cfromc / lee_controller_B.b_absxk;
      lee_controller_B.anrm += lee_controller_B.ctoc * lee_controller_B.ctoc;
    }

    lee_controller_B.cfromc = fabs(V[lee_controller_B.b_k].im);
    if (lee_controller_B.cfromc > lee_controller_B.b_absxk) {
      lee_controller_B.ctoc = lee_controller_B.b_absxk / lee_controller_B.cfromc;
      lee_controller_B.anrm = lee_controller_B.anrm * lee_controller_B.ctoc *
        lee_controller_B.ctoc + 1.0;
      lee_controller_B.b_absxk = lee_controller_B.cfromc;
    } else {
      lee_controller_B.ctoc = lee_controller_B.cfromc / lee_controller_B.b_absxk;
      lee_controller_B.anrm += lee_controller_B.ctoc * lee_controller_B.ctoc;
    }

    lee_controller_B.b_k++;
  }

  lee_controller_B.anrm = lee_controller_B.b_absxk * sqrt(lee_controller_B.anrm);
  lee_controller_B.b_k = 12;
  while (lee_controller_B.b_k + 1 <= 16) {
    lee_controller_B.b_absxk = V[lee_controller_B.b_k].re;
    lee_controller_B.cfromc = V[lee_controller_B.b_k].im;
    if (lee_controller_B.cfromc == 0.0) {
      V[lee_controller_B.b_k].re = lee_controller_B.b_absxk /
        lee_controller_B.anrm;
      V[lee_controller_B.b_k].im = 0.0;
    } else if (lee_controller_B.b_absxk == 0.0) {
      V[lee_controller_B.b_k].re = 0.0;
      V[lee_controller_B.b_k].im = lee_controller_B.cfromc /
        lee_controller_B.anrm;
    } else {
      V[lee_controller_B.b_k].re = lee_controller_B.b_absxk /
        lee_controller_B.anrm;
      V[lee_controller_B.b_k].im = lee_controller_B.cfromc /
        lee_controller_B.anrm;
    }

    lee_controller_B.b_k++;
  }

  if (lee_controller_B.y[0].im == 0.0) {
    if (D[0].im == 0.0) {
      lee_controller_B.anrm = D[0].re / lee_controller_B.y[0].re;
      lee_controller_B.b_absxk = 0.0;
    } else if (D[0].re == 0.0) {
      lee_controller_B.anrm = 0.0;
      lee_controller_B.b_absxk = D[0].im / lee_controller_B.y[0].re;
    } else {
      lee_controller_B.anrm = D[0].re / lee_controller_B.y[0].re;
      lee_controller_B.b_absxk = D[0].im / lee_controller_B.y[0].re;
    }
  } else if (lee_controller_B.y[0].re == 0.0) {
    if (D[0].re == 0.0) {
      lee_controller_B.anrm = D[0].im / lee_controller_B.y[0].im;
      lee_controller_B.b_absxk = 0.0;
    } else if (D[0].im == 0.0) {
      lee_controller_B.anrm = 0.0;
      lee_controller_B.b_absxk = -(D[0].re / lee_controller_B.y[0].im);
    } else {
      lee_controller_B.anrm = D[0].im / lee_controller_B.y[0].im;
      lee_controller_B.b_absxk = -(D[0].re / lee_controller_B.y[0].im);
    }
  } else {
    lee_controller_B.b_absxk = fabs(lee_controller_B.y[0].re);
    lee_controller_B.anrm = fabs(lee_controller_B.y[0].im);
    if (lee_controller_B.b_absxk > lee_controller_B.anrm) {
      lee_controller_B.b_absxk = lee_controller_B.y[0].im / lee_controller_B.y[0]
        .re;
      lee_controller_B.cfromc = lee_controller_B.b_absxk * lee_controller_B.y[0]
        .im + lee_controller_B.y[0].re;
      lee_controller_B.anrm = (lee_controller_B.b_absxk * D[0].im + D[0].re) /
        lee_controller_B.cfromc;
      lee_controller_B.b_absxk = (D[0].im - lee_controller_B.b_absxk * D[0].re) /
        lee_controller_B.cfromc;
    } else if (lee_controller_B.anrm == lee_controller_B.b_absxk) {
      lee_controller_B.cfromc = lee_controller_B.y[0].re > 0.0 ? 0.5 : -0.5;
      lee_controller_B.ctoc = lee_controller_B.y[0].im > 0.0 ? 0.5 : -0.5;
      lee_controller_B.anrm = (D[0].re * lee_controller_B.cfromc + D[0].im *
        lee_controller_B.ctoc) / lee_controller_B.b_absxk;
      lee_controller_B.b_absxk = (D[0].im * lee_controller_B.cfromc - D[0].re *
        lee_controller_B.ctoc) / lee_controller_B.b_absxk;
    } else {
      lee_controller_B.b_absxk = lee_controller_B.y[0].re / lee_controller_B.y[0]
        .im;
      lee_controller_B.cfromc = lee_controller_B.b_absxk * lee_controller_B.y[0]
        .re + lee_controller_B.y[0].im;
      lee_controller_B.anrm = (lee_controller_B.b_absxk * D[0].re + D[0].im) /
        lee_controller_B.cfromc;
      lee_controller_B.b_absxk = (lee_controller_B.b_absxk * D[0].im - D[0].re) /
        lee_controller_B.cfromc;
    }
  }

  D[0].re = lee_controller_B.anrm;
  D[0].im = lee_controller_B.b_absxk;
  if (lee_controller_B.y[1].im == 0.0) {
    if (D[1].im == 0.0) {
      lee_controller_B.anrm = D[1].re / lee_controller_B.y[1].re;
      lee_controller_B.b_absxk = 0.0;
    } else if (D[1].re == 0.0) {
      lee_controller_B.anrm = 0.0;
      lee_controller_B.b_absxk = D[1].im / lee_controller_B.y[1].re;
    } else {
      lee_controller_B.anrm = D[1].re / lee_controller_B.y[1].re;
      lee_controller_B.b_absxk = D[1].im / lee_controller_B.y[1].re;
    }
  } else if (lee_controller_B.y[1].re == 0.0) {
    if (D[1].re == 0.0) {
      lee_controller_B.anrm = D[1].im / lee_controller_B.y[1].im;
      lee_controller_B.b_absxk = 0.0;
    } else if (D[1].im == 0.0) {
      lee_controller_B.anrm = 0.0;
      lee_controller_B.b_absxk = -(D[1].re / lee_controller_B.y[1].im);
    } else {
      lee_controller_B.anrm = D[1].im / lee_controller_B.y[1].im;
      lee_controller_B.b_absxk = -(D[1].re / lee_controller_B.y[1].im);
    }
  } else {
    lee_controller_B.b_absxk = fabs(lee_controller_B.y[1].re);
    lee_controller_B.anrm = fabs(lee_controller_B.y[1].im);
    if (lee_controller_B.b_absxk > lee_controller_B.anrm) {
      lee_controller_B.b_absxk = lee_controller_B.y[1].im / lee_controller_B.y[1]
        .re;
      lee_controller_B.cfromc = lee_controller_B.b_absxk * lee_controller_B.y[1]
        .im + lee_controller_B.y[1].re;
      lee_controller_B.anrm = (lee_controller_B.b_absxk * D[1].im + D[1].re) /
        lee_controller_B.cfromc;
      lee_controller_B.b_absxk = (D[1].im - lee_controller_B.b_absxk * D[1].re) /
        lee_controller_B.cfromc;
    } else if (lee_controller_B.anrm == lee_controller_B.b_absxk) {
      lee_controller_B.cfromc = lee_controller_B.y[1].re > 0.0 ? 0.5 : -0.5;
      lee_controller_B.ctoc = lee_controller_B.y[1].im > 0.0 ? 0.5 : -0.5;
      lee_controller_B.anrm = (D[1].re * lee_controller_B.cfromc + D[1].im *
        lee_controller_B.ctoc) / lee_controller_B.b_absxk;
      lee_controller_B.b_absxk = (D[1].im * lee_controller_B.cfromc - D[1].re *
        lee_controller_B.ctoc) / lee_controller_B.b_absxk;
    } else {
      lee_controller_B.b_absxk = lee_controller_B.y[1].re / lee_controller_B.y[1]
        .im;
      lee_controller_B.cfromc = lee_controller_B.b_absxk * lee_controller_B.y[1]
        .re + lee_controller_B.y[1].im;
      lee_controller_B.anrm = (lee_controller_B.b_absxk * D[1].re + D[1].im) /
        lee_controller_B.cfromc;
      lee_controller_B.b_absxk = (lee_controller_B.b_absxk * D[1].im - D[1].re) /
        lee_controller_B.cfromc;
    }
  }

  D[1].re = lee_controller_B.anrm;
  D[1].im = lee_controller_B.b_absxk;
  if (lee_controller_B.y[2].im == 0.0) {
    if (D[2].im == 0.0) {
      lee_controller_B.anrm = D[2].re / lee_controller_B.y[2].re;
      lee_controller_B.b_absxk = 0.0;
    } else if (D[2].re == 0.0) {
      lee_controller_B.anrm = 0.0;
      lee_controller_B.b_absxk = D[2].im / lee_controller_B.y[2].re;
    } else {
      lee_controller_B.anrm = D[2].re / lee_controller_B.y[2].re;
      lee_controller_B.b_absxk = D[2].im / lee_controller_B.y[2].re;
    }
  } else if (lee_controller_B.y[2].re == 0.0) {
    if (D[2].re == 0.0) {
      lee_controller_B.anrm = D[2].im / lee_controller_B.y[2].im;
      lee_controller_B.b_absxk = 0.0;
    } else if (D[2].im == 0.0) {
      lee_controller_B.anrm = 0.0;
      lee_controller_B.b_absxk = -(D[2].re / lee_controller_B.y[2].im);
    } else {
      lee_controller_B.anrm = D[2].im / lee_controller_B.y[2].im;
      lee_controller_B.b_absxk = -(D[2].re / lee_controller_B.y[2].im);
    }
  } else {
    lee_controller_B.b_absxk = fabs(lee_controller_B.y[2].re);
    lee_controller_B.anrm = fabs(lee_controller_B.y[2].im);
    if (lee_controller_B.b_absxk > lee_controller_B.anrm) {
      lee_controller_B.b_absxk = lee_controller_B.y[2].im / lee_controller_B.y[2]
        .re;
      lee_controller_B.cfromc = lee_controller_B.b_absxk * lee_controller_B.y[2]
        .im + lee_controller_B.y[2].re;
      lee_controller_B.anrm = (lee_controller_B.b_absxk * D[2].im + D[2].re) /
        lee_controller_B.cfromc;
      lee_controller_B.b_absxk = (D[2].im - lee_controller_B.b_absxk * D[2].re) /
        lee_controller_B.cfromc;
    } else if (lee_controller_B.anrm == lee_controller_B.b_absxk) {
      lee_controller_B.cfromc = lee_controller_B.y[2].re > 0.0 ? 0.5 : -0.5;
      lee_controller_B.ctoc = lee_controller_B.y[2].im > 0.0 ? 0.5 : -0.5;
      lee_controller_B.anrm = (D[2].re * lee_controller_B.cfromc + D[2].im *
        lee_controller_B.ctoc) / lee_controller_B.b_absxk;
      lee_controller_B.b_absxk = (D[2].im * lee_controller_B.cfromc - D[2].re *
        lee_controller_B.ctoc) / lee_controller_B.b_absxk;
    } else {
      lee_controller_B.b_absxk = lee_controller_B.y[2].re / lee_controller_B.y[2]
        .im;
      lee_controller_B.cfromc = lee_controller_B.b_absxk * lee_controller_B.y[2]
        .re + lee_controller_B.y[2].im;
      lee_controller_B.anrm = (lee_controller_B.b_absxk * D[2].re + D[2].im) /
        lee_controller_B.cfromc;
      lee_controller_B.b_absxk = (lee_controller_B.b_absxk * D[2].im - D[2].re) /
        lee_controller_B.cfromc;
    }
  }

  D[2].re = lee_controller_B.anrm;
  D[2].im = lee_controller_B.b_absxk;
  if (lee_controller_B.y[3].im == 0.0) {
    if (D[3].im == 0.0) {
      lee_controller_B.anrm = D[3].re / lee_controller_B.y[3].re;
      lee_controller_B.b_absxk = 0.0;
    } else if (D[3].re == 0.0) {
      lee_controller_B.anrm = 0.0;
      lee_controller_B.b_absxk = D[3].im / lee_controller_B.y[3].re;
    } else {
      lee_controller_B.anrm = D[3].re / lee_controller_B.y[3].re;
      lee_controller_B.b_absxk = D[3].im / lee_controller_B.y[3].re;
    }
  } else if (lee_controller_B.y[3].re == 0.0) {
    if (D[3].re == 0.0) {
      lee_controller_B.anrm = D[3].im / lee_controller_B.y[3].im;
      lee_controller_B.b_absxk = 0.0;
    } else if (D[3].im == 0.0) {
      lee_controller_B.anrm = 0.0;
      lee_controller_B.b_absxk = -(D[3].re / lee_controller_B.y[3].im);
    } else {
      lee_controller_B.anrm = D[3].im / lee_controller_B.y[3].im;
      lee_controller_B.b_absxk = -(D[3].re / lee_controller_B.y[3].im);
    }
  } else {
    lee_controller_B.b_absxk = fabs(lee_controller_B.y[3].re);
    lee_controller_B.anrm = fabs(lee_controller_B.y[3].im);
    if (lee_controller_B.b_absxk > lee_controller_B.anrm) {
      lee_controller_B.b_absxk = lee_controller_B.y[3].im / lee_controller_B.y[3]
        .re;
      lee_controller_B.cfromc = lee_controller_B.b_absxk * lee_controller_B.y[3]
        .im + lee_controller_B.y[3].re;
      lee_controller_B.anrm = (lee_controller_B.b_absxk * D[3].im + D[3].re) /
        lee_controller_B.cfromc;
      lee_controller_B.b_absxk = (D[3].im - lee_controller_B.b_absxk * D[3].re) /
        lee_controller_B.cfromc;
    } else if (lee_controller_B.anrm == lee_controller_B.b_absxk) {
      lee_controller_B.cfromc = lee_controller_B.y[3].re > 0.0 ? 0.5 : -0.5;
      lee_controller_B.ctoc = lee_controller_B.y[3].im > 0.0 ? 0.5 : -0.5;
      lee_controller_B.anrm = (D[3].re * lee_controller_B.cfromc + D[3].im *
        lee_controller_B.ctoc) / lee_controller_B.b_absxk;
      lee_controller_B.b_absxk = (D[3].im * lee_controller_B.cfromc - D[3].re *
        lee_controller_B.ctoc) / lee_controller_B.b_absxk;
    } else {
      lee_controller_B.b_absxk = lee_controller_B.y[3].re / lee_controller_B.y[3]
        .im;
      lee_controller_B.cfromc = lee_controller_B.b_absxk * lee_controller_B.y[3]
        .re + lee_controller_B.y[3].im;
      lee_controller_B.anrm = (lee_controller_B.b_absxk * D[3].re + D[3].im) /
        lee_controller_B.cfromc;
      lee_controller_B.b_absxk = (lee_controller_B.b_absxk * D[3].im - D[3].re) /
        lee_controller_B.cfromc;
    }
  }

  D[3].re = lee_controller_B.anrm;
  D[3].im = lee_controller_B.b_absxk;
}

// Function for MATLAB Function: '<S2>/att control'
static real_T lee_controller_xnrm2(int32_T n, const real_T x[16], int32_T ix0)
{
  real_T y;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      lee_controller_B.scale_ct = 3.3121686421112381E-170;
      lee_controller_B.kend = (ix0 + n) - 1;
      for (int32_T k = ix0; k <= lee_controller_B.kend; k++) {
        lee_controller_B.absxk_p = fabs(x[k - 1]);
        if (lee_controller_B.absxk_p > lee_controller_B.scale_ct) {
          lee_controller_B.t_p = lee_controller_B.scale_ct /
            lee_controller_B.absxk_p;
          y = y * lee_controller_B.t_p * lee_controller_B.t_p + 1.0;
          lee_controller_B.scale_ct = lee_controller_B.absxk_p;
        } else {
          lee_controller_B.t_p = lee_controller_B.absxk_p /
            lee_controller_B.scale_ct;
          y += lee_controller_B.t_p * lee_controller_B.t_p;
        }
      }

      y = lee_controller_B.scale_ct * sqrt(y);
    }
  }

  return y;
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[16], int32_T ic0, real_T work[4])
{
  int32_T jy;
  if (tau != 0.0) {
    boolean_T exitg2;
    lee_controller_B.lastv = m;
    lee_controller_B.lastc_a = iv0 + m;
    while ((lee_controller_B.lastv > 0) && (C[lee_controller_B.lastc_a - 2] ==
            0.0)) {
      lee_controller_B.lastv--;
      lee_controller_B.lastc_a--;
    }

    lee_controller_B.lastc_a = n;
    exitg2 = false;
    while ((!exitg2) && (lee_controller_B.lastc_a > 0)) {
      int32_T exitg1;
      lee_controller_B.coltop = ((lee_controller_B.lastc_a - 1) << 2) + ic0;
      jy = lee_controller_B.coltop;
      do {
        exitg1 = 0;
        if (jy <= (lee_controller_B.coltop + lee_controller_B.lastv) - 1) {
          if (C[jy - 1] != 0.0) {
            exitg1 = 1;
          } else {
            jy++;
          }
        } else {
          lee_controller_B.lastc_a--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }

    lee_controller_B.lastc_a--;
  } else {
    lee_controller_B.lastv = 0;
    lee_controller_B.lastc_a = -1;
  }

  if (lee_controller_B.lastv > 0) {
    if (lee_controller_B.lastc_a + 1 != 0) {
      lee_controller_B.coltop = 0;
      while (lee_controller_B.coltop <= lee_controller_B.lastc_a) {
        work[lee_controller_B.coltop] = 0.0;
        lee_controller_B.coltop++;
      }

      lee_controller_B.coltop = 0;
      jy = (lee_controller_B.lastc_a << 2) + ic0;
      lee_controller_B.iac_e = ic0;
      while (lee_controller_B.iac_e <= jy) {
        lee_controller_B.ix_g = iv0;
        lee_controller_B.c_a = 0.0;
        lee_controller_B.d_f = (lee_controller_B.iac_e + lee_controller_B.lastv)
          - 1;
        lee_controller_B.ia_h = lee_controller_B.iac_e;
        while (lee_controller_B.ia_h <= lee_controller_B.d_f) {
          lee_controller_B.c_a += C[lee_controller_B.ia_h - 1] *
            C[lee_controller_B.ix_g - 1];
          lee_controller_B.ix_g++;
          lee_controller_B.ia_h++;
        }

        work[lee_controller_B.coltop] += lee_controller_B.c_a;
        lee_controller_B.coltop++;
        lee_controller_B.iac_e += 4;
      }
    }

    if (!(-tau == 0.0)) {
      lee_controller_B.coltop = ic0 - 1;
      jy = 0;
      lee_controller_B.iac_e = 0;
      while (lee_controller_B.iac_e <= lee_controller_B.lastc_a) {
        if (work[jy] != 0.0) {
          lee_controller_B.c_a = work[jy] * -tau;
          lee_controller_B.ix_g = iv0;
          lee_controller_B.d_f = lee_controller_B.coltop;
          lee_controller_B.ia_h = lee_controller_B.lastv +
            lee_controller_B.coltop;
          while (lee_controller_B.d_f + 1 <= lee_controller_B.ia_h) {
            C[lee_controller_B.d_f] += C[lee_controller_B.ix_g - 1] *
              lee_controller_B.c_a;
            lee_controller_B.ix_g++;
            lee_controller_B.d_f++;
          }
        }

        jy++;
        lee_controller_B.coltop += 4;
        lee_controller_B.iac_e++;
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xgehrd(real_T a[16], real_T tau[3])
{
  int32_T exitg1;
  boolean_T exitg2;
  lee_controller_B.work_c[0] = 0.0;
  lee_controller_B.work_c[1] = 0.0;
  lee_controller_B.work_c[2] = 0.0;
  lee_controller_B.work_c[3] = 0.0;
  lee_controller_B.alpha1 = a[1];
  tau[0] = 0.0;
  lee_controller_B.xnorm = lee_controller_xnrm2(2, a, 3);
  if (lee_controller_B.xnorm != 0.0) {
    lee_controller_B.xnorm = lee_controller_rt_hypotd_snf(a[1],
      lee_controller_B.xnorm);
    if (a[1] >= 0.0) {
      lee_controller_B.xnorm = -lee_controller_B.xnorm;
    }

    if (fabs(lee_controller_B.xnorm) < 1.0020841800044864E-292) {
      lee_controller_B.knt = -1;
      do {
        lee_controller_B.knt++;
        lee_controller_B.lastc = 3;
        while (lee_controller_B.lastc <= 4) {
          a[lee_controller_B.lastc - 1] *= 9.9792015476736E+291;
          lee_controller_B.lastc++;
        }

        lee_controller_B.xnorm *= 9.9792015476736E+291;
        lee_controller_B.alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(lee_controller_B.xnorm) >= 1.0020841800044864E-292));

      lee_controller_B.xnorm = lee_controller_rt_hypotd_snf
        (lee_controller_B.alpha1, lee_controller_xnrm2(2, a, 3));
      if (lee_controller_B.alpha1 >= 0.0) {
        lee_controller_B.xnorm = -lee_controller_B.xnorm;
      }

      tau[0] = (lee_controller_B.xnorm - lee_controller_B.alpha1) /
        lee_controller_B.xnorm;
      lee_controller_B.alpha1 = 1.0 / (lee_controller_B.alpha1 -
        lee_controller_B.xnorm);
      lee_controller_B.lastc = 3;
      while (lee_controller_B.lastc <= 4) {
        a[lee_controller_B.lastc - 1] *= lee_controller_B.alpha1;
        lee_controller_B.lastc++;
      }

      lee_controller_B.lastc = 0;
      while (lee_controller_B.lastc <= lee_controller_B.knt) {
        lee_controller_B.xnorm *= 1.0020841800044864E-292;
        lee_controller_B.lastc++;
      }

      lee_controller_B.alpha1 = lee_controller_B.xnorm;
    } else {
      tau[0] = (lee_controller_B.xnorm - a[1]) / lee_controller_B.xnorm;
      lee_controller_B.alpha1 = 1.0 / (a[1] - lee_controller_B.xnorm);
      lee_controller_B.knt = 3;
      while (lee_controller_B.knt <= 4) {
        a[lee_controller_B.knt - 1] *= lee_controller_B.alpha1;
        lee_controller_B.knt++;
      }

      lee_controller_B.alpha1 = lee_controller_B.xnorm;
    }
  }

  a[1] = 1.0;
  if (tau[0] != 0.0) {
    lee_controller_B.knt = 2;
    lee_controller_B.lastc = 3;
    while ((lee_controller_B.knt + 1 > 0) && (a[lee_controller_B.lastc] == 0.0))
    {
      lee_controller_B.knt--;
      lee_controller_B.lastc--;
    }

    lee_controller_B.lastc = 4;
    exitg2 = false;
    while ((!exitg2) && (lee_controller_B.lastc > 0)) {
      lee_controller_B.ix = lee_controller_B.lastc + 4;
      do {
        exitg1 = 0;
        if (lee_controller_B.ix <= ((lee_controller_B.knt << 2) +
             lee_controller_B.lastc) + 4) {
          if (a[lee_controller_B.ix - 1] != 0.0) {
            exitg1 = 1;
          } else {
            lee_controller_B.ix += 4;
          }
        } else {
          lee_controller_B.lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lee_controller_B.knt = -1;
    lee_controller_B.lastc = 0;
  }

  if (lee_controller_B.knt + 1 > 0) {
    if (lee_controller_B.lastc != 0) {
      lee_controller_B.ix = 0;
      while (lee_controller_B.ix <= lee_controller_B.lastc - 1) {
        lee_controller_B.work_c[lee_controller_B.ix] = 0.0;
        lee_controller_B.ix++;
      }

      lee_controller_B.ix = 1;
      lee_controller_B.jy = (lee_controller_B.knt << 2) + 5;
      lee_controller_B.iac = 5;
      while (lee_controller_B.iac <= lee_controller_B.jy) {
        lee_controller_B.b_ix = 0;
        lee_controller_B.e = (lee_controller_B.iac + lee_controller_B.lastc) - 1;
        lee_controller_B.ia = lee_controller_B.iac;
        while (lee_controller_B.ia <= lee_controller_B.e) {
          lee_controller_B.work_c[lee_controller_B.b_ix] +=
            a[lee_controller_B.ia - 1] * a[lee_controller_B.ix];
          lee_controller_B.b_ix++;
          lee_controller_B.ia++;
        }

        lee_controller_B.ix++;
        lee_controller_B.iac += 4;
      }
    }

    if (!(-tau[0] == 0.0)) {
      lee_controller_B.ix = 4;
      lee_controller_B.jy = 1;
      lee_controller_B.iac = 0;
      while (lee_controller_B.iac <= lee_controller_B.knt) {
        if (a[lee_controller_B.jy] != 0.0) {
          lee_controller_B.xnorm = a[lee_controller_B.jy] * -tau[0];
          lee_controller_B.b_ix = 0;
          lee_controller_B.e = lee_controller_B.ix;
          lee_controller_B.ia = lee_controller_B.lastc + lee_controller_B.ix;
          while (lee_controller_B.e + 1 <= lee_controller_B.ia) {
            a[lee_controller_B.e] +=
              lee_controller_B.work_c[lee_controller_B.b_ix] *
              lee_controller_B.xnorm;
            lee_controller_B.b_ix++;
            lee_controller_B.e++;
          }
        }

        lee_controller_B.jy++;
        lee_controller_B.ix += 4;
        lee_controller_B.iac++;
      }
    }
  }

  lee_controller_xzlarf(3, 3, 2, tau[0], a, 6, lee_controller_B.work_c);
  a[1] = lee_controller_B.alpha1;
  lee_controller_B.alpha1 = a[6];
  tau[1] = 0.0;
  lee_controller_B.xnorm = lee_controller_xnrm2(1, a, 8);
  if (lee_controller_B.xnorm != 0.0) {
    lee_controller_B.xnorm = lee_controller_rt_hypotd_snf(a[6],
      lee_controller_B.xnorm);
    if (a[6] >= 0.0) {
      lee_controller_B.xnorm = -lee_controller_B.xnorm;
    }

    if (fabs(lee_controller_B.xnorm) < 1.0020841800044864E-292) {
      lee_controller_B.knt = -1;
      do {
        lee_controller_B.knt++;
        a[7] *= 9.9792015476736E+291;
        lee_controller_B.xnorm *= 9.9792015476736E+291;
        lee_controller_B.alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(lee_controller_B.xnorm) >= 1.0020841800044864E-292));

      lee_controller_B.xnorm = lee_controller_rt_hypotd_snf
        (lee_controller_B.alpha1, lee_controller_xnrm2(1, a, 8));
      if (lee_controller_B.alpha1 >= 0.0) {
        lee_controller_B.xnorm = -lee_controller_B.xnorm;
      }

      tau[1] = (lee_controller_B.xnorm - lee_controller_B.alpha1) /
        lee_controller_B.xnorm;
      a[7] *= 1.0 / (lee_controller_B.alpha1 - lee_controller_B.xnorm);
      lee_controller_B.lastc = 0;
      while (lee_controller_B.lastc <= lee_controller_B.knt) {
        lee_controller_B.xnorm *= 1.0020841800044864E-292;
        lee_controller_B.lastc++;
      }

      lee_controller_B.alpha1 = lee_controller_B.xnorm;
    } else {
      tau[1] = (lee_controller_B.xnorm - a[6]) / lee_controller_B.xnorm;
      a[7] *= 1.0 / (a[6] - lee_controller_B.xnorm);
      lee_controller_B.alpha1 = lee_controller_B.xnorm;
    }
  }

  a[6] = 1.0;
  if (tau[1] != 0.0) {
    lee_controller_B.knt = 1;
    lee_controller_B.lastc = 7;
    while ((lee_controller_B.knt + 1 > 0) && (a[lee_controller_B.lastc] == 0.0))
    {
      lee_controller_B.knt--;
      lee_controller_B.lastc--;
    }

    lee_controller_B.lastc = 4;
    exitg2 = false;
    while ((!exitg2) && (lee_controller_B.lastc > 0)) {
      lee_controller_B.ix = lee_controller_B.lastc + 8;
      do {
        exitg1 = 0;
        if (lee_controller_B.ix <= ((lee_controller_B.knt << 2) +
             lee_controller_B.lastc) + 8) {
          if (a[lee_controller_B.ix - 1] != 0.0) {
            exitg1 = 1;
          } else {
            lee_controller_B.ix += 4;
          }
        } else {
          lee_controller_B.lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lee_controller_B.knt = -1;
    lee_controller_B.lastc = 0;
  }

  if (lee_controller_B.knt + 1 > 0) {
    if (lee_controller_B.lastc != 0) {
      lee_controller_B.ix = 0;
      while (lee_controller_B.ix <= lee_controller_B.lastc - 1) {
        lee_controller_B.work_c[lee_controller_B.ix] = 0.0;
        lee_controller_B.ix++;
      }

      lee_controller_B.ix = 6;
      lee_controller_B.jy = (lee_controller_B.knt << 2) + 9;
      lee_controller_B.iac = 9;
      while (lee_controller_B.iac <= lee_controller_B.jy) {
        lee_controller_B.b_ix = 0;
        lee_controller_B.e = (lee_controller_B.iac + lee_controller_B.lastc) - 1;
        lee_controller_B.ia = lee_controller_B.iac;
        while (lee_controller_B.ia <= lee_controller_B.e) {
          lee_controller_B.work_c[lee_controller_B.b_ix] +=
            a[lee_controller_B.ia - 1] * a[lee_controller_B.ix];
          lee_controller_B.b_ix++;
          lee_controller_B.ia++;
        }

        lee_controller_B.ix++;
        lee_controller_B.iac += 4;
      }
    }

    if (!(-tau[1] == 0.0)) {
      lee_controller_B.ix = 8;
      lee_controller_B.jy = 6;
      lee_controller_B.iac = 0;
      while (lee_controller_B.iac <= lee_controller_B.knt) {
        if (a[lee_controller_B.jy] != 0.0) {
          lee_controller_B.xnorm = a[lee_controller_B.jy] * -tau[1];
          lee_controller_B.b_ix = 0;
          lee_controller_B.e = lee_controller_B.ix;
          lee_controller_B.ia = lee_controller_B.lastc + lee_controller_B.ix;
          while (lee_controller_B.e + 1 <= lee_controller_B.ia) {
            a[lee_controller_B.e] +=
              lee_controller_B.work_c[lee_controller_B.b_ix] *
              lee_controller_B.xnorm;
            lee_controller_B.b_ix++;
            lee_controller_B.e++;
          }
        }

        lee_controller_B.jy++;
        lee_controller_B.ix += 4;
        lee_controller_B.iac++;
      }
    }
  }

  lee_controller_xzlarf(2, 2, 7, tau[1], a, 11, lee_controller_B.work_c);
  a[6] = lee_controller_B.alpha1;
  lee_controller_B.alpha1 = a[11];
  tau[2] = 0.0;
  lee_controller_B.xnorm = lee_controller_xnrm2(0, a, 12);
  if (lee_controller_B.xnorm != 0.0) {
    lee_controller_B.xnorm = lee_controller_rt_hypotd_snf(a[11],
      lee_controller_B.xnorm);
    if (a[11] >= 0.0) {
      lee_controller_B.xnorm = -lee_controller_B.xnorm;
    }

    if (fabs(lee_controller_B.xnorm) < 1.0020841800044864E-292) {
      lee_controller_B.knt = -1;
      do {
        lee_controller_B.knt++;
        lee_controller_B.xnorm *= 9.9792015476736E+291;
        lee_controller_B.alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(lee_controller_B.xnorm) >= 1.0020841800044864E-292));

      lee_controller_B.xnorm = lee_controller_rt_hypotd_snf
        (lee_controller_B.alpha1, lee_controller_xnrm2(0, a, 12));
      if (lee_controller_B.alpha1 >= 0.0) {
        lee_controller_B.xnorm = -lee_controller_B.xnorm;
      }

      tau[2] = (lee_controller_B.xnorm - lee_controller_B.alpha1) /
        lee_controller_B.xnorm;
      lee_controller_B.lastc = 0;
      while (lee_controller_B.lastc <= lee_controller_B.knt) {
        lee_controller_B.xnorm *= 1.0020841800044864E-292;
        lee_controller_B.lastc++;
      }

      lee_controller_B.alpha1 = lee_controller_B.xnorm;
    } else {
      tau[2] = (lee_controller_B.xnorm - a[11]) / lee_controller_B.xnorm;
      lee_controller_B.alpha1 = lee_controller_B.xnorm;
    }
  }

  a[11] = 1.0;
  if (tau[2] != 0.0) {
    lee_controller_B.knt = 0;
    lee_controller_B.lastc = 11;
    while ((lee_controller_B.knt + 1 > 0) && (a[lee_controller_B.lastc] == 0.0))
    {
      lee_controller_B.knt--;
      lee_controller_B.lastc--;
    }

    lee_controller_B.lastc = 4;
    exitg2 = false;
    while ((!exitg2) && (lee_controller_B.lastc > 0)) {
      lee_controller_B.ix = lee_controller_B.lastc + 12;
      do {
        exitg1 = 0;
        if (lee_controller_B.ix <= ((lee_controller_B.knt << 2) +
             lee_controller_B.lastc) + 12) {
          if (a[lee_controller_B.ix - 1] != 0.0) {
            exitg1 = 1;
          } else {
            lee_controller_B.ix += 4;
          }
        } else {
          lee_controller_B.lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lee_controller_B.knt = -1;
    lee_controller_B.lastc = 0;
  }

  if (lee_controller_B.knt + 1 > 0) {
    if (lee_controller_B.lastc != 0) {
      lee_controller_B.ix = 0;
      while (lee_controller_B.ix <= lee_controller_B.lastc - 1) {
        lee_controller_B.work_c[lee_controller_B.ix] = 0.0;
        lee_controller_B.ix++;
      }

      lee_controller_B.ix = 11;
      lee_controller_B.jy = (lee_controller_B.knt << 2) + 13;
      lee_controller_B.iac = 13;
      while (lee_controller_B.iac <= lee_controller_B.jy) {
        lee_controller_B.b_ix = 0;
        lee_controller_B.e = (lee_controller_B.iac + lee_controller_B.lastc) - 1;
        lee_controller_B.ia = lee_controller_B.iac;
        while (lee_controller_B.ia <= lee_controller_B.e) {
          lee_controller_B.work_c[lee_controller_B.b_ix] +=
            a[lee_controller_B.ia - 1] * a[lee_controller_B.ix];
          lee_controller_B.b_ix++;
          lee_controller_B.ia++;
        }

        lee_controller_B.ix++;
        lee_controller_B.iac += 4;
      }
    }

    if (!(-tau[2] == 0.0)) {
      lee_controller_B.ix = 12;
      lee_controller_B.jy = 11;
      lee_controller_B.iac = 0;
      while (lee_controller_B.iac <= lee_controller_B.knt) {
        if (a[lee_controller_B.jy] != 0.0) {
          lee_controller_B.xnorm = a[lee_controller_B.jy] * -tau[2];
          lee_controller_B.b_ix = 0;
          lee_controller_B.e = lee_controller_B.ix;
          lee_controller_B.ia = lee_controller_B.lastc + lee_controller_B.ix;
          while (lee_controller_B.e + 1 <= lee_controller_B.ia) {
            a[lee_controller_B.e] +=
              lee_controller_B.work_c[lee_controller_B.b_ix] *
              lee_controller_B.xnorm;
            lee_controller_B.b_ix++;
            lee_controller_B.e++;
          }
        }

        lee_controller_B.jy++;
        lee_controller_B.ix += 4;
        lee_controller_B.iac++;
      }
    }
  }

  lee_controller_xzlarf(1, 1, 12, tau[2], a, 16, lee_controller_B.work_c);
  a[11] = lee_controller_B.alpha1;
}

// Function for MATLAB Function: '<S2>/att control'
static real_T lee_controller_xnrm2_l(int32_T n, const real_T x[3])
{
  real_T y;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[1]);
    } else {
      lee_controller_B.scale_ja = 3.3121686421112381E-170;
      lee_controller_B.k_a = 2;
      while (lee_controller_B.k_a <= n + 1) {
        lee_controller_B.absxk_h = fabs(x[lee_controller_B.k_a - 1]);
        if (lee_controller_B.absxk_h > lee_controller_B.scale_ja) {
          lee_controller_B.t_c = lee_controller_B.scale_ja /
            lee_controller_B.absxk_h;
          y = y * lee_controller_B.t_c * lee_controller_B.t_c + 1.0;
          lee_controller_B.scale_ja = lee_controller_B.absxk_h;
        } else {
          lee_controller_B.t_c = lee_controller_B.absxk_h /
            lee_controller_B.scale_ja;
          y += lee_controller_B.t_c * lee_controller_B.t_c;
        }

        lee_controller_B.k_a++;
      }

      y = lee_controller_B.scale_ja * sqrt(y);
    }
  }

  return y;
}

// Function for MATLAB Function: '<S2>/att control'
static real_T lee_controller_xzlarfg(int32_T n, real_T *alpha1, real_T x[3])
{
  real_T tau;
  tau = 0.0;
  if (n > 0) {
    lee_controller_B.xnorm_m = lee_controller_xnrm2_l(n - 1, x);
    if (lee_controller_B.xnorm_m != 0.0) {
      lee_controller_B.xnorm_m = lee_controller_rt_hypotd_snf(*alpha1,
        lee_controller_B.xnorm_m);
      if (*alpha1 >= 0.0) {
        lee_controller_B.xnorm_m = -lee_controller_B.xnorm_m;
      }

      if (fabs(lee_controller_B.xnorm_m) < 1.0020841800044864E-292) {
        lee_controller_B.knt_a = -1;
        do {
          lee_controller_B.knt_a++;
          lee_controller_B.b_k_d = 1;
          while (lee_controller_B.b_k_d + 1 <= n) {
            x[lee_controller_B.b_k_d] *= 9.9792015476736E+291;
            lee_controller_B.b_k_d++;
          }

          lee_controller_B.xnorm_m *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (!(fabs(lee_controller_B.xnorm_m) >= 1.0020841800044864E-292));

        lee_controller_B.xnorm_m = lee_controller_rt_hypotd_snf(*alpha1,
          lee_controller_xnrm2_l(n - 1, x));
        if (*alpha1 >= 0.0) {
          lee_controller_B.xnorm_m = -lee_controller_B.xnorm_m;
        }

        tau = (lee_controller_B.xnorm_m - *alpha1) / lee_controller_B.xnorm_m;
        lee_controller_B.a_m = 1.0 / (*alpha1 - lee_controller_B.xnorm_m);
        lee_controller_B.b_k_d = 1;
        while (lee_controller_B.b_k_d + 1 <= n) {
          x[lee_controller_B.b_k_d] *= lee_controller_B.a_m;
          lee_controller_B.b_k_d++;
        }

        lee_controller_B.b_k_d = 0;
        while (lee_controller_B.b_k_d <= lee_controller_B.knt_a) {
          lee_controller_B.xnorm_m *= 1.0020841800044864E-292;
          lee_controller_B.b_k_d++;
        }

        *alpha1 = lee_controller_B.xnorm_m;
      } else {
        tau = (lee_controller_B.xnorm_m - *alpha1) / lee_controller_B.xnorm_m;
        lee_controller_B.a_m = 1.0 / (*alpha1 - lee_controller_B.xnorm_m);
        lee_controller_B.knt_a = 1;
        while (lee_controller_B.knt_a + 1 <= n) {
          x[lee_controller_B.knt_a] *= lee_controller_B.a_m;
          lee_controller_B.knt_a++;
        }

        *alpha1 = lee_controller_B.xnorm_m;
      }
    }
  }

  return tau;
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xdlanv2(real_T *a, real_T *b, real_T *c, real_T *d,
  real_T *rt1r, real_T *rt1i, real_T *rt2r, real_T *rt2i, real_T *cs, real_T *sn)
{
  if (*c == 0.0) {
    *cs = 1.0;
    *sn = 0.0;
  } else if (*b == 0.0) {
    *cs = 0.0;
    *sn = 1.0;
    lee_controller_B.bcmax = *d;
    *d = *a;
    *a = lee_controller_B.bcmax;
    *b = -*c;
    *c = 0.0;
  } else {
    lee_controller_B.tau_b = *a - *d;
    if ((lee_controller_B.tau_b == 0.0) && ((*b < 0.0) != (*c < 0.0))) {
      *cs = 1.0;
      *sn = 0.0;
    } else {
      boolean_T tmp;
      lee_controller_B.p = 0.5 * lee_controller_B.tau_b;
      lee_controller_B.bcmis = fabs(*b);
      lee_controller_B.z = fabs(*c);
      tmp = rtIsNaN(lee_controller_B.z);
      if ((lee_controller_B.bcmis >= lee_controller_B.z) || tmp) {
        lee_controller_B.bcmax = lee_controller_B.bcmis;
      } else {
        lee_controller_B.bcmax = lee_controller_B.z;
      }

      if ((lee_controller_B.bcmis <= lee_controller_B.z) || tmp) {
        lee_controller_B.z = lee_controller_B.bcmis;
      }

      if (!(*b < 0.0)) {
        lee_controller_B.b = 1;
      } else {
        lee_controller_B.b = -1;
      }

      if (!(*c < 0.0)) {
        lee_controller_B.c_e = 1;
      } else {
        lee_controller_B.c_e = -1;
      }

      lee_controller_B.bcmis = lee_controller_B.z * static_cast<real_T>
        (lee_controller_B.b) * static_cast<real_T>(lee_controller_B.c_e);
      lee_controller_B.scale_h = fabs(lee_controller_B.p);
      if ((!(lee_controller_B.scale_h >= lee_controller_B.bcmax)) && (!rtIsNaN
           (lee_controller_B.bcmax))) {
        lee_controller_B.scale_h = lee_controller_B.bcmax;
      }

      lee_controller_B.z = lee_controller_B.p / lee_controller_B.scale_h *
        lee_controller_B.p + lee_controller_B.bcmax / lee_controller_B.scale_h *
        lee_controller_B.bcmis;
      if (lee_controller_B.z >= 8.8817841970012523E-16) {
        if (!(lee_controller_B.p < 0.0)) {
          lee_controller_B.tau_b = sqrt(lee_controller_B.scale_h) * sqrt
            (lee_controller_B.z);
        } else {
          lee_controller_B.tau_b = -(sqrt(lee_controller_B.scale_h) * sqrt
            (lee_controller_B.z));
        }

        lee_controller_B.z = lee_controller_B.p + lee_controller_B.tau_b;
        *a = *d + lee_controller_B.z;
        *d -= lee_controller_B.bcmax / lee_controller_B.z *
          lee_controller_B.bcmis;
        lee_controller_B.tau_b = lee_controller_rt_hypotd_snf(*c,
          lee_controller_B.z);
        *cs = lee_controller_B.z / lee_controller_B.tau_b;
        *sn = *c / lee_controller_B.tau_b;
        *b -= *c;
        *c = 0.0;
      } else {
        lee_controller_B.bcmax = *b + *c;
        lee_controller_B.tau_b = lee_controller_rt_hypotd_snf
          (lee_controller_B.bcmax, lee_controller_B.tau_b);
        *cs = sqrt((fabs(lee_controller_B.bcmax) / lee_controller_B.tau_b + 1.0)
                   * 0.5);
        if (!(lee_controller_B.bcmax < 0.0)) {
          lee_controller_B.b = 1;
        } else {
          lee_controller_B.b = -1;
        }

        *sn = -(lee_controller_B.p / (lee_controller_B.tau_b * *cs)) *
          static_cast<real_T>(lee_controller_B.b);
        lee_controller_B.p = *a * *cs + *b * *sn;
        lee_controller_B.tau_b = -*a * *sn + *b * *cs;
        lee_controller_B.bcmax = *c * *cs + *d * *sn;
        lee_controller_B.bcmis = -*c * *sn + *d * *cs;
        *b = lee_controller_B.tau_b * *cs + lee_controller_B.bcmis * *sn;
        *c = -lee_controller_B.p * *sn + lee_controller_B.bcmax * *cs;
        lee_controller_B.bcmax = ((lee_controller_B.p * *cs +
          lee_controller_B.bcmax * *sn) + (-lee_controller_B.tau_b * *sn +
          lee_controller_B.bcmis * *cs)) * 0.5;
        *a = lee_controller_B.bcmax;
        *d = lee_controller_B.bcmax;
        if (*c != 0.0) {
          if (*b != 0.0) {
            if ((*b < 0.0) == (*c < 0.0)) {
              lee_controller_B.z = sqrt(fabs(*b));
              lee_controller_B.bcmis = sqrt(fabs(*c));
              if (!(*c < 0.0)) {
                lee_controller_B.p = lee_controller_B.z * lee_controller_B.bcmis;
              } else {
                lee_controller_B.p = -(lee_controller_B.z *
                  lee_controller_B.bcmis);
              }

              lee_controller_B.tau_b = 1.0 / sqrt(fabs(*b + *c));
              *a = lee_controller_B.bcmax + lee_controller_B.p;
              *d = lee_controller_B.bcmax - lee_controller_B.p;
              *b -= *c;
              *c = 0.0;
              lee_controller_B.p = lee_controller_B.z * lee_controller_B.tau_b;
              lee_controller_B.tau_b *= lee_controller_B.bcmis;
              lee_controller_B.bcmax = *cs * lee_controller_B.p - *sn *
                lee_controller_B.tau_b;
              *sn = *cs * lee_controller_B.tau_b + *sn * lee_controller_B.p;
              *cs = lee_controller_B.bcmax;
            }
          } else {
            *b = -*c;
            *c = 0.0;
            lee_controller_B.bcmax = *cs;
            *cs = -*sn;
            *sn = lee_controller_B.bcmax;
          }
        }
      }
    }
  }

  *rt1r = *a;
  *rt2r = *d;
  if (*c == 0.0) {
    *rt1i = 0.0;
    *rt2i = 0.0;
  } else {
    *rt1i = sqrt(fabs(*b)) * sqrt(fabs(*c));
    *rt2i = -*rt1i;
  }
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xrot(int32_T n, real_T x[16], int32_T ix0, int32_T
  iy0, real_T c, real_T s)
{
  if (n >= 1) {
    lee_controller_B.ix_l = ix0 - 1;
    lee_controller_B.iy_p = iy0 - 1;
    lee_controller_B.k_p = 0;
    while (lee_controller_B.k_p <= n - 1) {
      lee_controller_B.temp_e = c * x[lee_controller_B.ix_l] + s *
        x[lee_controller_B.iy_p];
      x[lee_controller_B.iy_p] = c * x[lee_controller_B.iy_p] - s *
        x[lee_controller_B.ix_l];
      x[lee_controller_B.ix_l] = lee_controller_B.temp_e;
      lee_controller_B.iy_p += 4;
      lee_controller_B.ix_l += 4;
      lee_controller_B.k_p++;
    }
  }
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xrot_g(int32_T n, real_T x[16], int32_T ix0, int32_T
  iy0, real_T c, real_T s)
{
  if (n >= 1) {
    lee_controller_B.ix_o = ix0 - 1;
    lee_controller_B.iy = iy0 - 1;
    lee_controller_B.k_n = 0;
    while (lee_controller_B.k_n <= n - 1) {
      lee_controller_B.temp_a = c * x[lee_controller_B.ix_o] + s *
        x[lee_controller_B.iy];
      x[lee_controller_B.iy] = c * x[lee_controller_B.iy] - s *
        x[lee_controller_B.ix_o];
      x[lee_controller_B.ix_o] = lee_controller_B.temp_a;
      lee_controller_B.iy++;
      lee_controller_B.ix_o++;
      lee_controller_B.k_n++;
    }
  }
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_xrot_g5(real_T x[16], int32_T ix0, int32_T iy0,
  real_T c, real_T s)
{
  lee_controller_B.temp_ax = x[iy0 - 1];
  lee_controller_B.temp_tmp = x[ix0 - 1];
  x[iy0 - 1] = lee_controller_B.temp_ax * c - lee_controller_B.temp_tmp * s;
  x[ix0 - 1] = lee_controller_B.temp_tmp * c + lee_controller_B.temp_ax * s;
  lee_controller_B.temp_ax = x[ix0] * c + x[iy0] * s;
  x[iy0] = x[iy0] * c - x[ix0] * s;
  x[ix0] = lee_controller_B.temp_ax;
  lee_controller_B.temp_ax = x[iy0 + 1];
  lee_controller_B.temp_tmp = x[ix0 + 1];
  x[iy0 + 1] = lee_controller_B.temp_ax * c - lee_controller_B.temp_tmp * s;
  x[ix0 + 1] = lee_controller_B.temp_tmp * c + lee_controller_B.temp_ax * s;
  lee_controller_B.temp_ax = x[iy0 + 2];
  lee_controller_B.temp_tmp = x[ix0 + 2];
  x[iy0 + 2] = lee_controller_B.temp_ax * c - lee_controller_B.temp_tmp * s;
  x[ix0 + 2] = lee_controller_B.temp_tmp * c + lee_controller_B.temp_ax * s;
}

// Function for MATLAB Function: '<S2>/att control'
static int32_T lee_controller_eml_dlahqr(real_T h[16], real_T z[16])
{
  int32_T info;
  boolean_T exitg1;
  info = 0;
  lee_controller_B.v[0] = 0.0;
  lee_controller_B.v[1] = 0.0;
  lee_controller_B.v[2] = 0.0;
  h[2] = 0.0;
  h[3] = 0.0;
  h[7] = 0.0;
  lee_controller_B.i = 3;
  exitg1 = false;
  while ((!exitg1) && (lee_controller_B.i + 1 >= 1)) {
    boolean_T exitg2;
    boolean_T goto150;
    lee_controller_B.L = 1;
    goto150 = false;
    lee_controller_B.its = 0;
    exitg2 = false;
    while ((!exitg2) && (lee_controller_B.its < 301)) {
      boolean_T exitg3;
      lee_controller_B.k = lee_controller_B.i;
      exitg3 = false;
      while ((!exitg3) && (lee_controller_B.k + 1 > lee_controller_B.L)) {
        lee_controller_B.hoffset = ((lee_controller_B.k - 1) << 2) +
          lee_controller_B.k;
        if (fabs(h[lee_controller_B.hoffset]) <= 4.0083367200179456E-292) {
          exitg3 = true;
        } else {
          lee_controller_B.m_tmp = (lee_controller_B.k << 2) +
            lee_controller_B.k;
          lee_controller_B.tst = fabs(h[lee_controller_B.hoffset - 1]) + fabs
            (h[lee_controller_B.m_tmp]);
          if (lee_controller_B.tst == 0.0) {
            if (lee_controller_B.k - 1 >= 1) {
              lee_controller_B.tst = fabs(h[(((lee_controller_B.k - 2) << 2) +
                lee_controller_B.k) - 1]);
            }

            if (lee_controller_B.k + 2 <= 4) {
              lee_controller_B.tst += fabs(h[lee_controller_B.m_tmp + 1]);
            }
          }

          if (fabs(h[lee_controller_B.hoffset]) <= 2.2204460492503131E-16 *
              lee_controller_B.tst) {
            lee_controller_B.htmp1 = fabs(h[lee_controller_B.hoffset]);
            lee_controller_B.tst = fabs(h[lee_controller_B.m_tmp - 1]);
            if (lee_controller_B.htmp1 > lee_controller_B.tst) {
              lee_controller_B.ab = lee_controller_B.htmp1;
              lee_controller_B.ba = lee_controller_B.tst;
            } else {
              lee_controller_B.ab = lee_controller_B.tst;
              lee_controller_B.ba = lee_controller_B.htmp1;
            }

            lee_controller_B.tst = h[lee_controller_B.m_tmp];
            lee_controller_B.htmp1 = fabs(lee_controller_B.tst);
            lee_controller_B.tst = fabs(h[lee_controller_B.hoffset - 1] -
              lee_controller_B.tst);
            if (lee_controller_B.htmp1 > lee_controller_B.tst) {
              lee_controller_B.aa = lee_controller_B.htmp1;
              lee_controller_B.htmp1 = lee_controller_B.tst;
            } else {
              lee_controller_B.aa = lee_controller_B.tst;
            }

            lee_controller_B.tst = lee_controller_B.aa + lee_controller_B.ab;
            lee_controller_B.htmp1 = lee_controller_B.aa / lee_controller_B.tst *
              lee_controller_B.htmp1 * 2.2204460492503131E-16;
            if ((4.0083367200179456E-292 >= lee_controller_B.htmp1) || rtIsNaN
                (lee_controller_B.htmp1)) {
              lee_controller_B.htmp1 = 4.0083367200179456E-292;
            }

            if (lee_controller_B.ab / lee_controller_B.tst * lee_controller_B.ba
                <= lee_controller_B.htmp1) {
              exitg3 = true;
            } else {
              lee_controller_B.k--;
            }
          } else {
            lee_controller_B.k--;
          }
        }
      }

      lee_controller_B.L = lee_controller_B.k + 1;
      if (lee_controller_B.k + 1 > 1) {
        h[lee_controller_B.k + ((lee_controller_B.k - 1) << 2)] = 0.0;
      }

      if (lee_controller_B.k + 1 >= lee_controller_B.i) {
        goto150 = true;
        exitg2 = true;
      } else {
        switch (lee_controller_B.its) {
         case 10:
          lee_controller_B.s_tmp_j = (lee_controller_B.k << 2) +
            lee_controller_B.k;
          lee_controller_B.tst = fabs(h[(((lee_controller_B.k + 1) << 2) +
            lee_controller_B.k) + 2]) + fabs(h[lee_controller_B.s_tmp_j + 1]);
          lee_controller_B.ab = 0.75 * lee_controller_B.tst +
            h[lee_controller_B.s_tmp_j];
          lee_controller_B.h12 = -0.4375 * lee_controller_B.tst;
          lee_controller_B.aa = lee_controller_B.tst;
          lee_controller_B.htmp1 = lee_controller_B.ab;
          break;

         case 20:
          lee_controller_B.tst = fabs(h[(((lee_controller_B.i - 2) << 2) +
            lee_controller_B.i) - 1]) + fabs(h[((lee_controller_B.i - 1) << 2) +
            lee_controller_B.i]);
          lee_controller_B.ab = h[(lee_controller_B.i << 2) + lee_controller_B.i]
            + 0.75 * lee_controller_B.tst;
          lee_controller_B.h12 = -0.4375 * lee_controller_B.tst;
          lee_controller_B.aa = lee_controller_B.tst;
          lee_controller_B.htmp1 = lee_controller_B.ab;
          break;

         default:
          lee_controller_B.m = ((lee_controller_B.i - 1) << 2) +
            lee_controller_B.i;
          lee_controller_B.ab = h[lee_controller_B.m - 1];
          lee_controller_B.aa = h[lee_controller_B.m];
          lee_controller_B.h12 = h[((lee_controller_B.i << 2) +
            lee_controller_B.i) - 1];
          lee_controller_B.htmp1 = h[(lee_controller_B.i << 2) +
            lee_controller_B.i];
          break;
        }

        lee_controller_B.tst = ((fabs(lee_controller_B.ab) + fabs
          (lee_controller_B.h12)) + fabs(lee_controller_B.aa)) + fabs
          (lee_controller_B.htmp1);
        if (lee_controller_B.tst == 0.0) {
          lee_controller_B.ab = 0.0;
          lee_controller_B.htmp1 = 0.0;
          lee_controller_B.ba = 0.0;
          lee_controller_B.aa = 0.0;
        } else {
          lee_controller_B.ab /= lee_controller_B.tst;
          lee_controller_B.htmp1 /= lee_controller_B.tst;
          lee_controller_B.ba = (lee_controller_B.ab + lee_controller_B.htmp1) /
            2.0;
          lee_controller_B.ab = (lee_controller_B.ab - lee_controller_B.ba) *
            (lee_controller_B.htmp1 - lee_controller_B.ba) -
            lee_controller_B.h12 / lee_controller_B.tst * (lee_controller_B.aa /
            lee_controller_B.tst);
          lee_controller_B.aa = sqrt(fabs(lee_controller_B.ab));
          if (lee_controller_B.ab >= 0.0) {
            lee_controller_B.ab = lee_controller_B.ba * lee_controller_B.tst;
            lee_controller_B.ba = lee_controller_B.ab;
            lee_controller_B.htmp1 = lee_controller_B.aa * lee_controller_B.tst;
            lee_controller_B.aa = -lee_controller_B.htmp1;
          } else {
            lee_controller_B.ab = lee_controller_B.ba + lee_controller_B.aa;
            lee_controller_B.ba -= lee_controller_B.aa;
            if (fabs(lee_controller_B.ab - lee_controller_B.htmp1) <= fabs
                (lee_controller_B.ba - lee_controller_B.htmp1)) {
              lee_controller_B.ab *= lee_controller_B.tst;
              lee_controller_B.ba = lee_controller_B.ab;
            } else {
              lee_controller_B.ba *= lee_controller_B.tst;
              lee_controller_B.ab = lee_controller_B.ba;
            }

            lee_controller_B.htmp1 = 0.0;
            lee_controller_B.aa = 0.0;
          }
        }

        lee_controller_B.m = lee_controller_B.i - 1;
        exitg3 = false;
        while ((!exitg3) && (lee_controller_B.m >= lee_controller_B.k + 1)) {
          lee_controller_B.s_tmp_j = ((lee_controller_B.m - 1) << 2) +
            lee_controller_B.m;
          lee_controller_B.h21s = h[lee_controller_B.s_tmp_j];
          lee_controller_B.h12 = h[lee_controller_B.s_tmp_j - 1];
          lee_controller_B.s_tmp = lee_controller_B.h12 - lee_controller_B.ba;
          lee_controller_B.tst = (fabs(lee_controller_B.s_tmp) + fabs
            (lee_controller_B.aa)) + fabs(lee_controller_B.h21s);
          lee_controller_B.h21s /= lee_controller_B.tst;
          lee_controller_B.s_tmp_j = (lee_controller_B.m << 2) +
            lee_controller_B.m;
          lee_controller_B.v[0] = (lee_controller_B.s_tmp / lee_controller_B.tst
            * (lee_controller_B.h12 - lee_controller_B.ab) +
            h[lee_controller_B.s_tmp_j - 1] * lee_controller_B.h21s) -
            lee_controller_B.aa / lee_controller_B.tst * lee_controller_B.htmp1;
          lee_controller_B.s_tmp = h[lee_controller_B.s_tmp_j];
          lee_controller_B.v[1] = (((lee_controller_B.h12 +
            lee_controller_B.s_tmp) - lee_controller_B.ab) - lee_controller_B.ba)
            * lee_controller_B.h21s;
          lee_controller_B.v[2] = h[lee_controller_B.s_tmp_j + 1] *
            lee_controller_B.h21s;
          lee_controller_B.tst = (fabs(lee_controller_B.v[0]) + fabs
            (lee_controller_B.v[1])) + fabs(lee_controller_B.v[2]);
          lee_controller_B.v[0] /= lee_controller_B.tst;
          lee_controller_B.v[1] /= lee_controller_B.tst;
          lee_controller_B.v[2] /= lee_controller_B.tst;
          if (lee_controller_B.k + 1 == lee_controller_B.m) {
            exitg3 = true;
          } else {
            lee_controller_B.hoffset = ((lee_controller_B.m - 2) << 2) +
              lee_controller_B.m;
            if (fabs(h[lee_controller_B.hoffset - 1]) * (fabs
                 (lee_controller_B.v[1]) + fabs(lee_controller_B.v[2])) <=
                ((fabs(h[lee_controller_B.hoffset - 2]) + fabs
                  (lee_controller_B.h12)) + fabs(lee_controller_B.s_tmp)) *
                (2.2204460492503131E-16 * fabs(lee_controller_B.v[0]))) {
              exitg3 = true;
            } else {
              lee_controller_B.m--;
            }
          }
        }

        lee_controller_B.s_tmp_j = lee_controller_B.m;
        while (lee_controller_B.s_tmp_j <= lee_controller_B.i) {
          lee_controller_B.nr = (lee_controller_B.i - lee_controller_B.s_tmp_j)
            + 2;
          if (3 <= lee_controller_B.nr) {
            lee_controller_B.nr = 3;
          }

          if (lee_controller_B.s_tmp_j > lee_controller_B.m) {
            lee_controller_B.hoffset = ((lee_controller_B.s_tmp_j - 2) << 2) +
              lee_controller_B.s_tmp_j;
            lee_controller_B.m_tmp = 0;
            while (lee_controller_B.m_tmp <= lee_controller_B.nr - 1) {
              lee_controller_B.v[lee_controller_B.m_tmp] = h
                [(lee_controller_B.m_tmp + lee_controller_B.hoffset) - 1];
              lee_controller_B.m_tmp++;
            }
          }

          lee_controller_B.ab = lee_controller_B.v[0];
          lee_controller_B.tst = lee_controller_xzlarfg(lee_controller_B.nr,
            &lee_controller_B.ab, lee_controller_B.v);
          lee_controller_B.v[0] = lee_controller_B.ab;
          if (lee_controller_B.s_tmp_j > lee_controller_B.m) {
            h[(lee_controller_B.s_tmp_j + ((lee_controller_B.s_tmp_j - 2) << 2))
              - 1] = lee_controller_B.ab;
            h[lee_controller_B.s_tmp_j + ((lee_controller_B.s_tmp_j - 2) << 2)] =
              0.0;
            if (lee_controller_B.s_tmp_j < lee_controller_B.i) {
              h[(lee_controller_B.s_tmp_j + ((lee_controller_B.s_tmp_j - 2) << 2))
                + 1] = 0.0;
            }
          } else if (lee_controller_B.m > lee_controller_B.k + 1) {
            lee_controller_B.hoffset = (((lee_controller_B.s_tmp_j - 2) << 2) +
              lee_controller_B.s_tmp_j) - 1;
            h[lee_controller_B.hoffset] *= 1.0 - lee_controller_B.tst;
          }

          lee_controller_B.ab = lee_controller_B.v[1];
          lee_controller_B.ba = lee_controller_B.tst * lee_controller_B.v[1];
          switch (lee_controller_B.nr) {
           case 3:
            lee_controller_B.aa = lee_controller_B.v[2];
            lee_controller_B.h12 = lee_controller_B.tst * lee_controller_B.v[2];
            lee_controller_B.hoffset = lee_controller_B.s_tmp_j - 1;
            while (lee_controller_B.hoffset + 1 < 5) {
              lee_controller_B.nr = (lee_controller_B.hoffset << 2) +
                lee_controller_B.s_tmp_j;
              lee_controller_B.htmp1 = (h[lee_controller_B.nr - 1] +
                h[lee_controller_B.nr] * lee_controller_B.ab) +
                h[lee_controller_B.nr + 1] * lee_controller_B.aa;
              h[lee_controller_B.nr - 1] -= lee_controller_B.htmp1 *
                lee_controller_B.tst;
              h[lee_controller_B.nr] -= lee_controller_B.htmp1 *
                lee_controller_B.ba;
              h[lee_controller_B.nr + 1] -= lee_controller_B.htmp1 *
                lee_controller_B.h12;
              lee_controller_B.hoffset++;
            }

            if (lee_controller_B.s_tmp_j + 3 <= lee_controller_B.i + 1) {
              lee_controller_B.m_tmp = lee_controller_B.s_tmp_j + 3;
            } else {
              lee_controller_B.m_tmp = lee_controller_B.i + 1;
            }

            lee_controller_B.c_j = 0;
            while (lee_controller_B.c_j <= lee_controller_B.m_tmp - 1) {
              lee_controller_B.nr = ((lee_controller_B.s_tmp_j - 1) << 2) +
                lee_controller_B.c_j;
              lee_controller_B.hoffset = (lee_controller_B.s_tmp_j << 2) +
                lee_controller_B.c_j;
              lee_controller_B.sum1_tmp = ((lee_controller_B.s_tmp_j + 1) << 2)
                + lee_controller_B.c_j;
              lee_controller_B.htmp1 = (h[lee_controller_B.hoffset] *
                lee_controller_B.ab + h[lee_controller_B.nr]) +
                h[lee_controller_B.sum1_tmp] * lee_controller_B.aa;
              h[lee_controller_B.nr] -= lee_controller_B.htmp1 *
                lee_controller_B.tst;
              h[lee_controller_B.hoffset] -= lee_controller_B.htmp1 *
                lee_controller_B.ba;
              h[lee_controller_B.sum1_tmp] -= lee_controller_B.htmp1 *
                lee_controller_B.h12;
              lee_controller_B.c_j++;
            }

            for (lee_controller_B.m_tmp = 0; lee_controller_B.m_tmp < 4;
                 lee_controller_B.m_tmp++) {
              lee_controller_B.nr = ((lee_controller_B.s_tmp_j - 1) << 2) +
                lee_controller_B.m_tmp;
              lee_controller_B.hoffset = (lee_controller_B.s_tmp_j << 2) +
                lee_controller_B.m_tmp;
              lee_controller_B.sum1_tmp = ((lee_controller_B.s_tmp_j + 1) << 2)
                + lee_controller_B.m_tmp;
              lee_controller_B.htmp1 = (z[lee_controller_B.hoffset] *
                lee_controller_B.ab + z[lee_controller_B.nr]) +
                z[lee_controller_B.sum1_tmp] * lee_controller_B.aa;
              z[lee_controller_B.nr] -= lee_controller_B.htmp1 *
                lee_controller_B.tst;
              z[lee_controller_B.hoffset] -= lee_controller_B.htmp1 *
                lee_controller_B.ba;
              z[lee_controller_B.sum1_tmp] -= lee_controller_B.htmp1 *
                lee_controller_B.h12;
            }
            break;

           case 2:
            lee_controller_B.hoffset = lee_controller_B.s_tmp_j - 1;
            while (lee_controller_B.hoffset + 1 < 5) {
              lee_controller_B.nr = (lee_controller_B.hoffset << 2) +
                lee_controller_B.s_tmp_j;
              lee_controller_B.aa = h[lee_controller_B.nr - 1];
              lee_controller_B.htmp1 = h[lee_controller_B.nr] *
                lee_controller_B.ab + lee_controller_B.aa;
              h[lee_controller_B.nr - 1] = lee_controller_B.aa -
                lee_controller_B.htmp1 * lee_controller_B.tst;
              h[lee_controller_B.nr] -= lee_controller_B.htmp1 *
                lee_controller_B.ba;
              lee_controller_B.hoffset++;
            }

            lee_controller_B.m_tmp = 0;
            while (lee_controller_B.m_tmp <= lee_controller_B.i) {
              lee_controller_B.nr = ((lee_controller_B.s_tmp_j - 1) << 2) +
                lee_controller_B.m_tmp;
              lee_controller_B.hoffset = (lee_controller_B.s_tmp_j << 2) +
                lee_controller_B.m_tmp;
              lee_controller_B.htmp1 = h[lee_controller_B.hoffset] *
                lee_controller_B.ab + h[lee_controller_B.nr];
              h[lee_controller_B.nr] -= lee_controller_B.htmp1 *
                lee_controller_B.tst;
              h[lee_controller_B.hoffset] -= lee_controller_B.htmp1 *
                lee_controller_B.ba;
              lee_controller_B.m_tmp++;
            }

            for (lee_controller_B.m_tmp = 0; lee_controller_B.m_tmp < 4;
                 lee_controller_B.m_tmp++) {
              lee_controller_B.nr = ((lee_controller_B.s_tmp_j - 1) << 2) +
                lee_controller_B.m_tmp;
              lee_controller_B.aa = z[lee_controller_B.nr];
              lee_controller_B.hoffset = (lee_controller_B.s_tmp_j << 2) +
                lee_controller_B.m_tmp;
              lee_controller_B.htmp1 = z[lee_controller_B.hoffset] *
                lee_controller_B.ab + lee_controller_B.aa;
              z[lee_controller_B.nr] = lee_controller_B.aa -
                lee_controller_B.htmp1 * lee_controller_B.tst;
              z[lee_controller_B.hoffset] -= lee_controller_B.htmp1 *
                lee_controller_B.ba;
            }
            break;
          }

          lee_controller_B.s_tmp_j++;
        }

        lee_controller_B.its++;
      }
    }

    if (!goto150) {
      info = lee_controller_B.i + 1;
      exitg1 = true;
    } else {
      if ((lee_controller_B.i + 1 != lee_controller_B.L) && (lee_controller_B.L ==
           lee_controller_B.i)) {
        lee_controller_B.its = (lee_controller_B.i << 2) + lee_controller_B.i;
        lee_controller_B.tst = h[lee_controller_B.its - 1];
        lee_controller_B.k = ((lee_controller_B.i - 1) << 2) +
          lee_controller_B.i;
        lee_controller_B.ab = h[lee_controller_B.k];
        lee_controller_B.ba = h[lee_controller_B.its];
        lee_controller_xdlanv2(&h[(lee_controller_B.i + ((lee_controller_B.i - 1)
          << 2)) - 1], &lee_controller_B.tst, &lee_controller_B.ab,
          &lee_controller_B.ba, &lee_controller_B.htmp1, &lee_controller_B.aa,
          &lee_controller_B.h12, &lee_controller_B.s_tmp, &lee_controller_B.h21s,
          &lee_controller_B.sn);
        h[lee_controller_B.its - 1] = lee_controller_B.tst;
        h[lee_controller_B.k] = lee_controller_B.ab;
        h[lee_controller_B.its] = lee_controller_B.ba;
        if (4 > lee_controller_B.i + 1) {
          lee_controller_xrot(3 - lee_controller_B.i, h, lee_controller_B.i +
                              ((lee_controller_B.i + 1) << 2),
                              (lee_controller_B.i + ((lee_controller_B.i + 1) <<
            2)) + 1, lee_controller_B.h21s, lee_controller_B.sn);
        }

        lee_controller_xrot_g(lee_controller_B.i - 1, h, ((lee_controller_B.i -
          1) << 2) + 1, (lee_controller_B.i << 2) + 1, lee_controller_B.h21s,
                              lee_controller_B.sn);
        lee_controller_xrot_g5(z, ((lee_controller_B.i - 1) << 2) + 1,
          (lee_controller_B.i << 2) + 1, lee_controller_B.h21s,
          lee_controller_B.sn);
      }

      lee_controller_B.i = lee_controller_B.L - 2;
    }
  }

  return info;
}

// Function for MATLAB Function: '<S2>/att control'
static void lee_controller_schur(const real_T A[16], real_T V[16], real_T T[16])
{
  if (lee_controller_anyNonFinite(A)) {
    for (lee_controller_B.b_i = 0; lee_controller_B.b_i < 16;
         lee_controller_B.b_i++) {
      V[lee_controller_B.b_i] = (rtNaN);
    }

    lee_controller_B.b_i = 2;
    while (lee_controller_B.b_i < 5) {
      V[lee_controller_B.b_i - 1] = 0.0;
      lee_controller_B.b_i++;
    }

    lee_controller_B.b_i = 3;
    while (lee_controller_B.b_i < 5) {
      V[lee_controller_B.b_i + 3] = 0.0;
      lee_controller_B.b_i++;
    }

    V[11] = 0.0;
    for (lee_controller_B.b_i = 0; lee_controller_B.b_i < 16;
         lee_controller_B.b_i++) {
      T[lee_controller_B.b_i] = (rtNaN);
    }
  } else {
    memcpy(&T[0], &A[0], sizeof(real_T) << 4U);
    lee_controller_xgehrd(T, lee_controller_B.tau);
    memcpy(&V[0], &T[0], sizeof(real_T) << 4U);
    lee_controller_B.b_i = 0;
    while (lee_controller_B.b_i <= 2) {
      V[lee_controller_B.b_i + 12] = 0.0;
      lee_controller_B.b_i++;
    }

    lee_controller_B.b_i = 0;
    while (lee_controller_B.b_i <= 1) {
      V[lee_controller_B.b_i + 8] = 0.0;
      lee_controller_B.b_i++;
    }

    lee_controller_B.b_i = 1;
    while (lee_controller_B.b_i + 3 <= 4) {
      V[lee_controller_B.b_i + 10] = V[lee_controller_B.b_i + 6];
      lee_controller_B.b_i++;
    }

    V[4] = 0.0;
    lee_controller_B.b_i = 0;
    while (lee_controller_B.b_i + 3 <= 4) {
      V[lee_controller_B.b_i + 6] = V[lee_controller_B.b_i + 2];
      lee_controller_B.b_i++;
    }

    lee_controller_B.work[0] = 0.0;
    V[1] = 0.0;
    lee_controller_B.work[1] = 0.0;
    V[2] = 0.0;
    lee_controller_B.work[2] = 0.0;
    V[3] = 0.0;
    lee_controller_B.work[3] = 0.0;
    V[0] = 1.0;
    V[15] = 1.0 - lee_controller_B.tau[2];
    lee_controller_B.b_i = 0;
    while (lee_controller_B.b_i <= 1) {
      V[14 - lee_controller_B.b_i] = 0.0;
      lee_controller_B.b_i++;
    }

    V[10] = 1.0;
    lee_controller_xzlarf(2, 1, 11, lee_controller_B.tau[1], V, 15,
                          lee_controller_B.work);
    lee_controller_B.b_i = 11;
    while (lee_controller_B.b_i + 1 <= 12) {
      V[lee_controller_B.b_i] *= -lee_controller_B.tau[1];
      lee_controller_B.b_i++;
    }

    V[10] = 1.0 - lee_controller_B.tau[1];
    V[9] = 0.0;
    V[5] = 1.0;
    lee_controller_xzlarf(3, 2, 6, lee_controller_B.tau[0], V, 10,
                          lee_controller_B.work);
    lee_controller_B.b_i = 6;
    while (lee_controller_B.b_i + 1 <= 8) {
      V[lee_controller_B.b_i] *= -lee_controller_B.tau[0];
      lee_controller_B.b_i++;
    }

    V[5] = 1.0 - lee_controller_B.tau[0];
    lee_controller_eml_dlahqr(T, V);
    T[3] = 0.0;
  }
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static void lee_controll_SystemCore_setup_g(px4_internal_block_PX4SCIRead_T *obj)
{
  static const char_T tmp[10] = { '/', 'd', 'e', 'v', '/', 't', 't', 'y', 'S',
    '2' };

  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  lee_controller_B.RxPinLoc = MW_UNDEFINED_VALUE;
  lee_controller_B.TxPinLoc = MW_UNDEFINED_VALUE;
  for (int32_T i = 0; i < 10; i++) {
    lee_controller_B.b_SCIModuleLoc[i] = tmp[i];
  }

  MW_SCI_HardwareFlowControl_Type HardwareFlowControlValue;
  MW_SCI_Parity_Type ParityValue;
  MW_SCI_StopBits_Type StopBitsValue;
  lee_controller_B.b_SCIModuleLoc[10] = '\x00';
  lee_controller_B.SCIModuleVoidPtr = (void*)(&lee_controller_B.b_SCIModuleLoc[0]);
  obj->SCIDriverObj.MW_SCIHANDLE = MW_SCI_Open(lee_controller_B.SCIModuleVoidPtr,
    true, lee_controller_B.RxPinLoc, lee_controller_B.TxPinLoc);
  MW_SCI_SetBaudrate(obj->SCIDriverObj.MW_SCIHANDLE, 9600U);
  StopBitsValue = MW_SCI_STOPBITS_1;
  ParityValue = MW_SCI_PARITY_NONE;
  MW_SCI_SetFrameFormat(obj->SCIDriverObj.MW_SCIHANDLE, 8, ParityValue,
                        StopBitsValue);
  lee_controller_B.RxPinLoc = MW_UNDEFINED_VALUE;
  lee_controller_B.TxPinLoc = MW_UNDEFINED_VALUE;
  HardwareFlowControlValue = MW_SCI_FLOWCONTROL_NONE;
  MW_SCI_ConfigureHardwareFlowControl(obj->SCIDriverObj.MW_SCIHANDLE,
    HardwareFlowControlValue, lee_controller_B.RxPinLoc,
    lee_controller_B.TxPinLoc);
  obj->isSetupComplete = true;
}

static void lee_controller_SystemCore_setup(px4_internal_block_PWM_lee_co_T *obj,
  boolean_T varargin_1, boolean_T varargin_2)
{
  uint16_T status;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->isMain = true;
  obj->pwmDevObj = MW_PWM_OUTPUT_MAIN_DEVICE_PATH;
  status = pwm_open(&obj->pwmDevHandler, obj->pwmDevObj,
                    &obj->actuatorAdvertiseObj, &obj->armAdvertiseObj);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  obj->servoCount = 0;
  status = pwm_getServoCount(&obj->pwmDevHandler, &obj->servoCount);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  if (varargin_1) {
    status = pwm_arm(&obj->pwmDevHandler, &obj->armAdvertiseObj);
    obj->isArmed = true;
  } else {
    status = pwm_disarm(&obj->pwmDevHandler, &obj->armAdvertiseObj);
    obj->isArmed = false;
  }

  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  status = pwm_setPWMRate(&obj->pwmDevHandler, obj->isMain);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  obj->channelMask = 143;
  status = pwm_setChannelMask(&obj->pwmDevHandler, obj->channelMask);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  status = pwm_setFailsafePWM(&obj->pwmDevHandler, obj->servoCount,
    obj->channelMask, obj->isMain);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  status = pwm_setDisarmedPWM(&obj->pwmDevHandler, obj->servoCount,
    obj->channelMask, obj->isMain, &obj->actuatorAdvertiseObj);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  if (obj->isMain) {
    status = pwm_forceFailsafe(&obj->pwmDevHandler, static_cast<int32_T>
      (varargin_2));
    obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
    status = pwm_forceTerminateFailsafe(&obj->pwmDevHandler, 0);
    obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  }

  obj->isSetupComplete = true;
}

// Model step function
void lee_controller_step(void)
{
  static const boolean_T b[128] = { false, false, false, false, false, false,
    false, false, false, true, true, true, true, true, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    true, true, true, true, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false };

  static const int8_T b_0[3] = { 0, 0, 1 };

  boolean_T exitg1;

  // MATLABSystem: '<S25>/SourceBlock' incorporates:
  //   Inport: '<S28>/In1'

  lee_controller_B.carry = uORB_read_step(lee_controller_DW.obj_d.orbMetadataObj,
    &lee_controller_DW.obj_d.eventStructObj, &lee_controller_B.b_varargout_2_k,
    false, 1.0);

  // Outputs for Enabled SubSystem: '<S25>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S28>/Enable'

  if (lee_controller_B.carry) {
    lee_controller_B.In1_h = lee_controller_B.b_varargout_2_k;
  }

  // End of MATLABSystem: '<S25>/SourceBlock'
  // End of Outputs for SubSystem: '<S25>/Enabled Subsystem'

  // Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem1' incorporates:
  //   EnablePort: '<S2>/Enable'

  // MATLAB Function: '<S3>/MATLAB Function' incorporates:
  //   DataTypeConversion: '<S3>/Cast To Double6'
  //   MATLAB Function: '<S2>/att control'

  lee_controller_B.K12 = 1.0 / sqrt(((static_cast<real_T>
    (lee_controller_B.In1_h.q[0]) * lee_controller_B.In1_h.q[0] + static_cast<
    real_T>(lee_controller_B.In1_h.q[1]) * lee_controller_B.In1_h.q[1]) +
    static_cast<real_T>(lee_controller_B.In1_h.q[2]) * lee_controller_B.In1_h.q
    [2]) + static_cast<real_T>(lee_controller_B.In1_h.q[3]) *
    lee_controller_B.In1_h.q[3]);
  lee_controller_B.q_tmp = lee_controller_B.In1_h.q[0] * lee_controller_B.K12;
  lee_controller_B.q_tmp_n = lee_controller_B.In1_h.q[1] * lee_controller_B.K12;
  lee_controller_B.q_tmp_b = lee_controller_B.In1_h.q[2] * lee_controller_B.K12;
  lee_controller_B.K12 *= lee_controller_B.In1_h.q[3];

  // End of Outputs for SubSystem: '<Root>/Enabled Subsystem1'
  lee_controller_B.K13 = lee_controller_B.K12 * lee_controller_B.K12;
  lee_controller_B.K14 = lee_controller_B.q_tmp_b * lee_controller_B.q_tmp_b;
  lee_controller_B.tempR[0] = 1.0 - (lee_controller_B.K14 + lee_controller_B.K13)
    * 2.0;
  lee_controller_B.K23 = lee_controller_B.q_tmp_n * lee_controller_B.q_tmp_b;
  lee_controller_B.K24 = lee_controller_B.q_tmp * lee_controller_B.K12;
  lee_controller_B.tempR[1] = (lee_controller_B.K23 - lee_controller_B.K24) *
    2.0;
  lee_controller_B.K34 = lee_controller_B.q_tmp_n * lee_controller_B.K12;
  lee_controller_B.tempR_tmp = lee_controller_B.q_tmp * lee_controller_B.q_tmp_b;
  lee_controller_B.tempR[2] = (lee_controller_B.K34 + lee_controller_B.tempR_tmp)
    * 2.0;
  lee_controller_B.tempR[3] = (lee_controller_B.K23 + lee_controller_B.K24) *
    2.0;
  lee_controller_B.K23 = lee_controller_B.q_tmp_n * lee_controller_B.q_tmp_n;
  lee_controller_B.tempR[4] = 1.0 - (lee_controller_B.K23 + lee_controller_B.K13)
    * 2.0;
  lee_controller_B.K13 = lee_controller_B.q_tmp_b * lee_controller_B.K12;
  lee_controller_B.K24 = lee_controller_B.q_tmp * lee_controller_B.q_tmp_n;
  lee_controller_B.tempR[5] = (lee_controller_B.K13 - lee_controller_B.K24) *
    2.0;
  lee_controller_B.tempR[6] = (lee_controller_B.K34 - lee_controller_B.tempR_tmp)
    * 2.0;
  lee_controller_B.tempR[7] = (lee_controller_B.K13 + lee_controller_B.K24) *
    2.0;
  lee_controller_B.tempR[8] = 1.0 - (lee_controller_B.K23 + lee_controller_B.K14)
    * 2.0;
  for (lee_controller_B.idx = 0; lee_controller_B.idx < 3; lee_controller_B.idx
       ++) {
    lee_controller_B.pmax = (static_cast<int8_T>(lee_controller_B.idx + 1) - 1) *
      3;
    lee_controller_B.R_mes[static_cast<int8_T>(lee_controller_B.idx + 1) - 1] =
      lee_controller_B.tempR[lee_controller_B.pmax];
    lee_controller_B.R_mes[static_cast<int8_T>(lee_controller_B.idx + 1) + 2] =
      lee_controller_B.tempR[lee_controller_B.pmax + 1];
    lee_controller_B.R_mes[static_cast<int8_T>(lee_controller_B.idx + 1) + 5] =
      lee_controller_B.tempR[lee_controller_B.pmax + 2];
  }

  // End of MATLAB Function: '<S3>/MATLAB Function'

  // MATLABSystem: '<S26>/SourceBlock' incorporates:
  //   Inport: '<S29>/In1'

  lee_controller_B.carry = uORB_read_step
    (lee_controller_DW.obj_l5.orbMetadataObj,
     &lee_controller_DW.obj_l5.eventStructObj, &lee_controller_B.b_varargout_2_b,
     false, 1.0);

  // Outputs for Enabled SubSystem: '<S26>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S29>/Enable'

  if (lee_controller_B.carry) {
    lee_controller_B.In1_f = lee_controller_B.b_varargout_2_b;
  }

  // End of MATLABSystem: '<S26>/SourceBlock'
  // End of Outputs for SubSystem: '<S26>/Enabled Subsystem'

  // DataTypeConversion: '<S3>/Cast To Double7' incorporates:
  //   SignalConversion generated from: '<S21>/ SFunction '

  lee_controller_B.TmpSignalConversionAtSFunct[0] = lee_controller_B.In1_f.xyz[0];
  lee_controller_B.TmpSignalConversionAtSFunct[1] = lee_controller_B.In1_f.xyz[1];
  lee_controller_B.TmpSignalConversionAtSFunct[2] = lee_controller_B.In1_f.xyz[2];

  // MATLABSystem: '<S24>/SourceBlock' incorporates:
  //   Inport: '<S27>/In1'

  lee_controller_B.carry = uORB_read_step
    (lee_controller_DW.obj_awb.orbMetadataObj,
     &lee_controller_DW.obj_awb.eventStructObj, &lee_controller_B.b_varargout_2,
     false, 1.0);

  // Outputs for Enabled SubSystem: '<S24>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S27>/Enable'

  if (lee_controller_B.carry) {
    lee_controller_B.In1 = lee_controller_B.b_varargout_2;
  }

  // End of MATLABSystem: '<S24>/SourceBlock'
  // End of Outputs for SubSystem: '<S24>/Enabled Subsystem'

  // MATLABSystem: '<S43>/SourceBlock' incorporates:
  //   Inport: '<S46>/In1'

  lee_controller_B.carry = uORB_read_step
    (lee_controller_DW.obj_kw.orbMetadataObj,
     &lee_controller_DW.obj_kw.eventStructObj, &lee_controller_B.b_varargout_2_c,
     false, 1.0);

  // Outputs for Enabled SubSystem: '<S43>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S46>/Enable'

  if (lee_controller_B.carry) {
    lee_controller_B.In1_m = lee_controller_B.b_varargout_2_c;
  }

  // End of MATLABSystem: '<S43>/SourceBlock'
  // End of Outputs for SubSystem: '<S43>/Enabled Subsystem'

  // MATLABSystem: '<Root>/Serial Receive1'
  if (lee_controller_DW.obj_cc.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_cc.SampleTime = lee_controller_P.dt;
  }

  MW_SCI_GetDataBytesAvailable
    (lee_controller_DW.obj_cc.SCIDriverObj.MW_SCIHANDLE, false,
     &lee_controller_B.sizeptr, 5);
  if (lee_controller_B.sizeptr >= 2U) {
    MW_SCI_Receive(lee_controller_DW.obj_cc.SCIDriverObj.MW_SCIHANDLE,
                   &lee_controller_B.RxDataLocChar[0], 2U);
    memcpy((void *)&lee_controller_B.RxData[0], (void *)
           &lee_controller_B.RxDataLocChar[0], (uint32_T)((size_t)2 * sizeof
            (int8_T)));
    lee_controller_B.sizeptr = 0U;
  } else {
    lee_controller_B.RxData[0] = 0;
    lee_controller_B.RxData[1] = 0;
    lee_controller_B.sizeptr = 1U;
  }

  // Logic: '<Root>/NOT' incorporates:
  //   MATLABSystem: '<Root>/Serial Receive1'

  lee_controller_B.NOT = (lee_controller_B.sizeptr == 0);

  // Outputs for Triggered SubSystem: '<Root>/Subsystem1' incorporates:
  //   TriggerPort: '<S10>/Trigger'

  if (lee_controller_B.NOT && (lee_controller_PrevZCX.Subsystem1_Trig_ZCE != 1))
  {
    // MATLAB Function: '<S10>/Bit sign' incorporates:
    //   MATLABSystem: '<Root>/Serial Receive1'

    if (lee_controller_B.RxData[1] < 0) {
      if (lee_controller_B.RxData[1] == -128) {
        for (lee_controller_B.idx = 0; lee_controller_B.idx < 8;
             lee_controller_B.idx++) {
          lee_controller_B.sfull[lee_controller_B.idx] = '1';
        }
      } else {
        lee_controller_B.idx = -lee_controller_B.RxData[1];
        for (lee_controller_B.pmax = 0; lee_controller_B.pmax < 8;
             lee_controller_B.pmax++) {
          lee_controller_B.padval = '0';
          if ((1 << (7 - lee_controller_B.pmax) & static_cast<int8_T>
               (lee_controller_B.idx)) != 0) {
            lee_controller_B.padval = '1';
          }

          lee_controller_B.sfull[lee_controller_B.pmax] = '1';
          if (lee_controller_B.padval == '1') {
            lee_controller_B.sfull[lee_controller_B.pmax] = '0';
          }
        }

        lee_controller_B.carry = true;
        for (lee_controller_B.idx = 7; lee_controller_B.idx >= 0;
             lee_controller_B.idx--) {
          lee_controller_B.padval = lee_controller_B.sfull[lee_controller_B.idx];
          if (lee_controller_B.carry) {
            if (lee_controller_B.padval == '1') {
              lee_controller_B.padval = '0';
            } else {
              lee_controller_B.padval = '1';
              lee_controller_B.carry = false;
            }
          }

          lee_controller_B.sfull[lee_controller_B.idx] = lee_controller_B.padval;
        }
      }

      lee_controller_B.idx = 0;
      lee_controller_B.pmax = 0;
      exitg1 = false;
      while ((!exitg1) && (lee_controller_B.pmax < 8)) {
        if (lee_controller_B.sfull[lee_controller_B.pmax] == '0') {
          lee_controller_B.idx = lee_controller_B.pmax + 1;
          exitg1 = true;
        } else {
          lee_controller_B.pmax++;
        }
      }

      if (lee_controller_B.idx == 0) {
        lee_controller_B.pmax = -1;
        lee_controller_B.pmin = 8;
      } else {
        if (4 >= 10 - lee_controller_B.idx) {
          lee_controller_B.idx = 4;
        } else {
          lee_controller_B.idx = 10 - lee_controller_B.idx;
        }

        lee_controller_B.pmax = 31;
        lee_controller_B.pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (lee_controller_B.pmax - lee_controller_B.pmin > 1))
        {
          lee_controller_B.npad = (lee_controller_B.pmin + lee_controller_B.pmax)
            >> 1;
          lee_controller_B.pow2p = 1 << lee_controller_B.npad;
          if (lee_controller_B.pow2p == lee_controller_B.idx) {
            lee_controller_B.pmax = lee_controller_B.npad;
            exitg1 = true;
          } else if (lee_controller_B.pow2p > lee_controller_B.idx) {
            lee_controller_B.pmax = lee_controller_B.npad;
          } else {
            lee_controller_B.pmin = lee_controller_B.npad;
          }
        }

        lee_controller_B.pmin = 1 << lee_controller_B.pmax;
        if (8 <= lee_controller_B.pmin) {
          lee_controller_B.pmin = 8;
        }

        lee_controller_B.pmax = 7 - lee_controller_B.pmin;
      }
    } else {
      for (lee_controller_B.idx = 0; lee_controller_B.idx < 8;
           lee_controller_B.idx++) {
        lee_controller_B.sfull[lee_controller_B.idx] = '0';
        if ((1 << (7 - lee_controller_B.idx) & lee_controller_B.RxData[1]) != 0)
        {
          lee_controller_B.sfull[lee_controller_B.idx] = '1';
        }
      }

      lee_controller_B.idx = 0;
      lee_controller_B.pmax = 0;
      exitg1 = false;
      while ((!exitg1) && (lee_controller_B.pmax < 8)) {
        if (lee_controller_B.sfull[lee_controller_B.pmax] == '1') {
          lee_controller_B.idx = lee_controller_B.pmax + 1;
          exitg1 = true;
        } else {
          lee_controller_B.pmax++;
        }
      }

      if (lee_controller_B.idx == 0) {
        lee_controller_B.idx = 8;
      }

      lee_controller_B.pmax = lee_controller_B.idx - 2;
      lee_controller_B.pmin = 9 - lee_controller_B.idx;
    }

    if (lee_controller_B.pmin < 8) {
      lee_controller_B.npad = 7 - lee_controller_B.pmin;
      if (lee_controller_B.RxData[1] < 0) {
        lee_controller_B.padval = '1';
      } else {
        lee_controller_B.padval = '0';
      }

      lee_controller_B.idx = 0;
      while (lee_controller_B.idx <= 7 - lee_controller_B.pmin) {
        lee_controller_B.x[lee_controller_B.idx] = lee_controller_B.padval;
        lee_controller_B.idx++;
      }
    } else {
      lee_controller_B.npad = -1;
    }

    lee_controller_B.idx = 1;
    while (lee_controller_B.idx - 1 <= lee_controller_B.pmin - 1) {
      lee_controller_B.x[lee_controller_B.npad + lee_controller_B.idx] =
        lee_controller_B.sfull[lee_controller_B.pmax + lee_controller_B.idx];
      lee_controller_B.idx++;
    }

    lee_controller_B.idx = 1;
    while ((lee_controller_B.idx < 8) && b[static_cast<int32_T>
           (lee_controller_B.x[lee_controller_B.idx - 1])]) {
      lee_controller_B.idx++;
    }

    lee_controller_B.pmax = 7;
    while ((lee_controller_B.pmax + 1 > lee_controller_B.idx) && b
           [static_cast<int32_T>(lee_controller_B.x[lee_controller_B.pmax])]) {
      lee_controller_B.pmax--;
    }

    lee_controller_B.p2 = 1ULL;
    lee_controller_B.a_i = 0ULL;
    while ((lee_controller_B.idx < lee_controller_B.pmax + 1) && b
           [static_cast<int32_T>(lee_controller_B.x[lee_controller_B.idx - 1])])
    {
      lee_controller_B.idx++;
    }

    while (lee_controller_B.pmax + 1 >= lee_controller_B.idx) {
      if (lee_controller_B.x[lee_controller_B.pmax] == '1') {
        lee_controller_B.a_i += lee_controller_B.p2;
        lee_controller_B.p2 += lee_controller_B.p2;
      } else if (lee_controller_B.x[lee_controller_B.pmax] == '0') {
        lee_controller_B.p2 += lee_controller_B.p2;
      }

      lee_controller_B.pmax--;
    }

    // Gain: '<S10>/Gain1' incorporates:
    //   DataTypeConversion: '<S10>/Cast To Double'
    //   Gain: '<S10>/Gain'
    //   MATLAB Function: '<S10>/Bit sign'
    //   MATLABSystem: '<Root>/Serial Receive1'
    //   Sum: '<S10>/Sum4'

    lee_controller_B.Gain1 = (static_cast<real_T>(static_cast<int16_T>
      ((lee_controller_P.Gain_Gain_k * lee_controller_B.RxData[0]) >> 6)) +
      static_cast<real_T>(lee_controller_B.a_i)) * lee_controller_P.Gain1_Gain;
  }

  lee_controller_PrevZCX.Subsystem1_Trig_ZCE = lee_controller_B.NOT;

  // End of Outputs for SubSystem: '<Root>/Subsystem1'

  // Gain: '<Root>/Gain'
  lee_controller_B.f_ext = lee_controller_P.Gain_Gain * lee_controller_B.Gain1;

  // MATLABSystem: '<S42>/Read Parameter39'
  if (lee_controller_DW.obj_ma.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_ma.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_ma.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_lt);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_lt = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter38'
  if (lee_controller_DW.obj_lj.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_lj.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_lj.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_o);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_o = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter40'
  if (lee_controller_DW.obj_f.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_f.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_f.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_o2);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_o2 = 0.0F;
  }

  // Product: '<Root>/Divide' incorporates:
  //   DataTypeConversion: '<Root>/Cast To Double'
  //   DataTypeConversion: '<Root>/Cast To Double1'
  //   DataTypeConversion: '<S42>/Cast To Double38'
  //   DataTypeConversion: '<S42>/Cast To Double39'
  //   DataTypeConversion: '<S42>/Cast To Double40'
  //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  //   MATLABSystem: '<S42>/Read Parameter38'
  //   MATLABSystem: '<S42>/Read Parameter39'
  //   MATLABSystem: '<S42>/Read Parameter40'
  //   Product: '<Root>/Product'
  //   Product: '<Root>/Product1'
  //   Sum: '<Root>/Sum'

  lee_controller_B.Divide = ((lee_controller_B.f_ext - static_cast<real_T>(
    static_cast<real32_T>(lee_controller_DW.DiscreteTimeIntegrator_DSTATE)) *
    lee_controller_B.ParamStep_lt) - static_cast<real_T>(static_cast<real32_T>
    (lee_controller_DW.DiscreteTimeIntegrator1_DSTATE)) *
    lee_controller_B.ParamStep_o) / lee_controller_B.ParamStep_o2;

  // MATLABSystem: '<S42>/Read Parameter14'
  if (lee_controller_DW.obj_hh.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_hh.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_hh.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_lt);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_lt = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter15'
  if (lee_controller_DW.obj_pv.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_pv.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_pv.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_o);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_o = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter16'
  if (lee_controller_DW.obj_j.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_j.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_j.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_o2);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_o2 = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter17'
  if (lee_controller_DW.obj_fy.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_fy.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_fy.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_i);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_i = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter18'
  if (lee_controller_DW.obj_n3.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_n3.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_n3.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_f);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_f = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter19'
  if (lee_controller_DW.obj_nu.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_nu.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_nu.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_iz);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_iz = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter20'
  if (lee_controller_DW.obj_hl.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_hl.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_hl.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_ff);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_ff = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter21'
  if (lee_controller_DW.obj_i.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_i.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_i.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_g);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_g = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter22'
  if (lee_controller_DW.obj_k3.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_k3.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_k3.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_co);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_co = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter23'
  if (lee_controller_DW.obj_ni.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_ni.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_ni.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_o3);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_o3 = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter24'
  if (lee_controller_DW.obj_hi.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_hi.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_hi.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_lm);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_lm = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter25'
  if (lee_controller_DW.obj_o1.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_o1.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_o1.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_m);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_m = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter26'
  if (lee_controller_DW.obj_og.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_og.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_og.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_mj);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_mj = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter27'
  if (lee_controller_DW.obj_pq.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_pq.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_pq.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_cn);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_cn = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter28'
  if (lee_controller_DW.obj_ne.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_ne.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_ne.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_fm);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_fm = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter29'
  if (lee_controller_DW.obj_lb.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_lb.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_lb.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_p);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_p = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter30'
  if (lee_controller_DW.obj_pd.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_pd.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_pd.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_e);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_e = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter31'
  if (lee_controller_DW.obj_el.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_el.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_el.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_o4);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_o4 = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter32'
  if (lee_controller_DW.obj_ng.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_ng.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_ng.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_h);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_h = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter33'
  if (lee_controller_DW.obj_e.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_e.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_e.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_l5);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_l5 = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter11'
  if (lee_controller_DW.obj_bh.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_bh.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_bh.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_h2);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_h2 = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter12'
  if (lee_controller_DW.obj_aw.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_aw.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_aw.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_me);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_me = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter13'
  if (lee_controller_DW.obj_js.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_js.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_js.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_mc);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_mc = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter6'
  if (lee_controller_DW.obj_p.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_p.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_p.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_h3);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_h3 = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter37'
  if (lee_controller_DW.obj_mt.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_mt.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_mt.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_cs);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_cs = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter34'
  if (lee_controller_DW.obj_h.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_h.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_h.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_k);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_k = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter35'
  if (lee_controller_DW.obj_k4.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_k4.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_k4.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_pc);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_pc = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter36'
  if (lee_controller_DW.obj_c.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_c.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_c.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_px);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_px = 0.0F;
  }

  // DigitalClock: '<Root>/Digital Clock'
  lee_controller_B.time = ((lee_controller_M->Timing.clockTick0) * 0.004);

  // MATLABSystem: '<S47>/SourceBlock' incorporates:
  //   Inport: '<S48>/In1'

  lee_controller_B.carry = uORB_read_step
    (lee_controller_DW.obj_fp.orbMetadataObj,
     &lee_controller_DW.obj_fp.eventStructObj, &lee_controller_B.b_varargout_2_m,
     false, 5000.0);

  // Outputs for Enabled SubSystem: '<S47>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S48>/Enable'

  if (lee_controller_B.carry) {
    lee_controller_B.In1_c = lee_controller_B.b_varargout_2_m;
  }

  // End of MATLABSystem: '<S47>/SourceBlock'
  // End of Outputs for SubSystem: '<S47>/Enabled Subsystem'

  // MATLABSystem: '<S51>/SourceBlock' incorporates:
  //   Inport: '<S53>/In1'

  lee_controller_B.carry = uORB_read_step
    (lee_controller_DW.obj_oh.orbMetadataObj,
     &lee_controller_DW.obj_oh.eventStructObj, &lee_controller_B.b_varargout_2_f,
     false, 1.0);

  // Outputs for Enabled SubSystem: '<S51>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S53>/Enable'

  if (lee_controller_B.carry) {
    lee_controller_B.In1_ho = lee_controller_B.b_varargout_2_f;
  }

  // End of MATLABSystem: '<S51>/SourceBlock'
  // End of Outputs for SubSystem: '<S51>/Enabled Subsystem'

  // MATLAB Function: '<S12>/MATLAB Function' incorporates:
  //   MATLAB Function: '<S9>/kill sw'

  lee_controller_B.NOT = ((lee_controller_B.In1_c.values[6] <= 1800) &&
    lee_controller_B.In1_ho.armed);

  // MATLABSystem: '<S52>/SourceBlock' incorporates:
  //   Inport: '<S54>/In1'

  lee_controller_B.carry = uORB_read_step
    (lee_controller_DW.obj_mfw.orbMetadataObj,
     &lee_controller_DW.obj_mfw.eventStructObj,
     &lee_controller_B.b_varargout_2_n, false, 1.0);

  // Outputs for Enabled SubSystem: '<S52>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S54>/Enable'

  if (lee_controller_B.carry) {
    lee_controller_B.In1_cj = lee_controller_B.b_varargout_2_n;
  }

  // End of MATLABSystem: '<S52>/SourceBlock'
  // End of Outputs for SubSystem: '<S52>/Enabled Subsystem'

  // MATLAB Function: '<S4>/MATLAB Function'
  lee_controller_B.carry = false;
  lee_controller_B.pos_flag = false;
  switch (lee_controller_B.In1_cj.main_state) {
   case 8:
    lee_controller_B.carry = true;
    break;

   case 2:
    lee_controller_B.pos_flag = true;
    break;
  }

  // End of MATLAB Function: '<S4>/MATLAB Function'

  // Outputs for Enabled SubSystem: '<Root>/LEE_CONTROLLER' incorporates:
  //   EnablePort: '<S5>/Enable'

  // Logic: '<Root>/AND' incorporates:
  //   MATLAB Function: '<S5>/lee att'

  if (lee_controller_B.pos_flag && lee_controller_B.NOT) {
    // MATLAB Function: '<S5>/inv alloc_matrix' incorporates:
    //   DataTypeConversion: '<S42>/Cast To Double34'
    //   DataTypeConversion: '<S42>/Cast To Double35'
    //   DataTypeConversion: '<S42>/Cast To Double36'
    //   MATLABSystem: '<S42>/Read Parameter34'
    //   MATLABSystem: '<S42>/Read Parameter35'
    //   MATLABSystem: '<S42>/Read Parameter36'

    lee_controller_invalloc_matrix(static_cast<real_T>
      (lee_controller_B.ParamStep_k), static_cast<real_T>
      (lee_controller_B.ParamStep_pc), static_cast<real_T>
      (lee_controller_B.ParamStep_px), lee_controller_B.inv_A);

    // MATLAB Function: '<S5>/lee pos' incorporates:
    //   DataTypeConversion: '<Root>/Cast To Double'
    //   DataTypeConversion: '<Root>/Cast To Double1'
    //   DataTypeConversion: '<Root>/Cast To Double2'
    //   DataTypeConversion: '<S3>/Cast To Double4'
    //   DataTypeConversion: '<S3>/Cast To Double5'
    //   DataTypeConversion: '<S42>/Cast To Double14'
    //   DataTypeConversion: '<S42>/Cast To Double15'
    //   DataTypeConversion: '<S42>/Cast To Double16'
    //   DataTypeConversion: '<S42>/Cast To Double37'
    //   DataTypeConversion: '<S42>/Cast To Double6'
    //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
    //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
    //   MATLABSystem: '<S42>/Read Parameter14'
    //   MATLABSystem: '<S42>/Read Parameter15'
    //   MATLABSystem: '<S42>/Read Parameter16'
    //   MATLABSystem: '<S42>/Read Parameter17'
    //   MATLABSystem: '<S42>/Read Parameter18'
    //   MATLABSystem: '<S42>/Read Parameter19'
    //   MATLABSystem: '<S42>/Read Parameter20'
    //   MATLABSystem: '<S42>/Read Parameter21'
    //   MATLABSystem: '<S42>/Read Parameter22'
    //   MATLABSystem: '<S42>/Read Parameter32'
    //   MATLABSystem: '<S42>/Read Parameter37'
    //   MATLABSystem: '<S42>/Read Parameter6'
    //   SignalConversion generated from: '<S40>/ SFunction '
    //   Sum: '<Root>/Sum1'
    //   Sum: '<Root>/Sum2'
    //   Sum: '<Root>/Sum3'

    lee_controller_B.BusAssignment.ep[0] = lee_controller_B.In1.x -
      lee_controller_B.In1_m.setpoints[0];
    lee_controller_B.BusAssignment.ep[1] = lee_controller_B.In1.y -
      lee_controller_B.In1_m.setpoints[1];
    lee_controller_B.BusAssignment.ep[2] = lee_controller_B.In1.z -
      (lee_controller_B.In1_m.setpoints[2] + static_cast<real32_T>
       (lee_controller_DW.DiscreteTimeIntegrator1_DSTATE));
    lee_controller_B.BusAssignment.ev[0] = lee_controller_B.In1.vx -
      lee_controller_B.In1_m.setpoints[3];
    lee_controller_B.BusAssignment.ev[1] = lee_controller_B.In1.vy -
      lee_controller_B.In1_m.setpoints[4];
    lee_controller_B.BusAssignment.ev[2] = lee_controller_B.In1.vz -
      (lee_controller_B.In1_m.setpoints[5] + static_cast<real32_T>
       (lee_controller_DW.DiscreteTimeIntegrator_DSTATE));
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.ParamStep_h3 *
      lee_controller_P.g;
    lee_controller_B.ParamStep[0] = static_cast<real32_T>(-static_cast<real_T>
      (lee_controller_B.ParamStep_lt));
    lee_controller_B.ParamStep[3] = -0.0F;
    lee_controller_B.ParamStep[6] = -0.0F;
    lee_controller_B.ParamStep[1] = -0.0F;
    lee_controller_B.ParamStep[4] = static_cast<real32_T>(-static_cast<real_T>
      (lee_controller_B.ParamStep_o));
    lee_controller_B.ParamStep[7] = -0.0F;
    lee_controller_B.ParamStep[2] = -0.0F;
    lee_controller_B.ParamStep[5] = -0.0F;
    lee_controller_B.ParamStep[8] = static_cast<real32_T>(-static_cast<real_T>
      (lee_controller_B.ParamStep_o2));
    lee_controller_B.ParamStep_c[0] = lee_controller_B.ParamStep_i;
    lee_controller_B.ParamStep_c[3] = 0.0F;
    lee_controller_B.ParamStep_c[6] = 0.0F;
    lee_controller_B.ParamStep_c[1] = 0.0F;
    lee_controller_B.ParamStep_c[4] = lee_controller_B.ParamStep_f;
    lee_controller_B.ParamStep_c[7] = 0.0F;
    lee_controller_B.ParamStep_c[2] = 0.0F;
    lee_controller_B.ParamStep_c[5] = 0.0F;
    lee_controller_B.ParamStep_c[8] = lee_controller_B.ParamStep_iz;
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.ParamStep_o2 = (lee_controller_B.ParamStep_h *
        lee_controller_B.BusAssignment.ep[lee_controller_B.idx] +
        lee_controller_B.BusAssignment.ev[lee_controller_B.idx]) *
        static_cast<real32_T>(lee_controller_P.dt) + static_cast<real32_T>
        (lee_controller_P.ei[lee_controller_B.idx]);
      if (lee_controller_B.ParamStep_o2 > lee_controller_B.ParamStep_cs) {
        lee_controller_B.ParamStep_o2 = lee_controller_B.ParamStep_cs;
      }

      if (lee_controller_B.ParamStep_o2 < -static_cast<real_T>
          (lee_controller_B.ParamStep_cs)) {
        lee_controller_B.ParamStep_o2 = static_cast<real32_T>(-static_cast<
          real_T>(lee_controller_B.ParamStep_cs));
      }

      lee_controller_B.c[lee_controller_B.idx] = b_0[lee_controller_B.idx];
      lee_controller_B.b_ei[lee_controller_B.idx] =
        lee_controller_B.ParamStep_o2;
      lee_controller_B.ParamStep_l[lee_controller_B.idx] =
        (lee_controller_B.ParamStep[lee_controller_B.idx + 3] *
         lee_controller_B.BusAssignment.ep[1] +
         lee_controller_B.ParamStep[lee_controller_B.idx] *
         lee_controller_B.BusAssignment.ep[0]) +
        lee_controller_B.ParamStep[lee_controller_B.idx + 6] *
        lee_controller_B.BusAssignment.ep[2];
      lee_controller_B.ParamStep_d[lee_controller_B.idx] =
        (lee_controller_B.ParamStep_c[lee_controller_B.idx + 3] *
         lee_controller_B.BusAssignment.ev[1] +
         lee_controller_B.ParamStep_c[lee_controller_B.idx] *
         lee_controller_B.BusAssignment.ev[0]) +
        lee_controller_B.ParamStep_c[lee_controller_B.idx + 6] *
        lee_controller_B.BusAssignment.ev[2];
    }

    lee_controller_B.ParamStep[0] = lee_controller_B.ParamStep_ff;
    lee_controller_B.ParamStep[3] = 0.0F;
    lee_controller_B.ParamStep[6] = 0.0F;
    lee_controller_B.ParamStep[1] = 0.0F;
    lee_controller_B.ParamStep[4] = lee_controller_B.ParamStep_g;
    lee_controller_B.ParamStep[7] = 0.0F;
    lee_controller_B.ParamStep[2] = 0.0F;
    lee_controller_B.ParamStep[5] = 0.0F;
    lee_controller_B.ParamStep[8] = lee_controller_B.ParamStep_co;
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.PD[lee_controller_B.idx] =
        ((lee_controller_B.ParamStep_l[lee_controller_B.idx] -
          lee_controller_B.ParamStep_d[lee_controller_B.idx]) -
         ((lee_controller_B.ParamStep[lee_controller_B.idx + 3] *
           lee_controller_B.b_ei[1] +
           lee_controller_B.ParamStep[lee_controller_B.idx] *
           lee_controller_B.b_ei[0]) +
          lee_controller_B.ParamStep[lee_controller_B.idx + 6] *
          lee_controller_B.b_ei[2])) - static_cast<real32_T>
        (lee_controller_B.rtb_q_drone_idx_0 *
         lee_controller_B.c[lee_controller_B.idx]);
    }

    lee_controller_B.ParamStep_o2 = 1.29246971E-26F;
    lee_controller_B.ParamStep_ff = lee_controller_B.ParamStep_h3 *
      lee_controller_B.In1_m.setpoints[6] + lee_controller_B.PD[0];
    lee_controller_B.b_ei[0] = -lee_controller_B.ParamStep_ff;
    lee_controller_B.ParamStep_ff = static_cast<real32_T>(fabs
      (static_cast<real_T>(lee_controller_B.ParamStep_ff)));
    if (lee_controller_B.ParamStep_ff > 1.29246971E-26F) {
      lee_controller_B.ParamStep_i = 1.0F;
      lee_controller_B.ParamStep_o2 = lee_controller_B.ParamStep_ff;
    } else {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_ff /
        1.29246971E-26F;
      lee_controller_B.ParamStep_i = lee_controller_B.ParamStep_g *
        lee_controller_B.ParamStep_g;
    }

    lee_controller_B.ParamStep_ff = lee_controller_B.ParamStep_h3 *
      lee_controller_B.In1_m.setpoints[7] + lee_controller_B.PD[1];
    lee_controller_B.b_ei[1] = -lee_controller_B.ParamStep_ff;
    lee_controller_B.ParamStep_ff = static_cast<real32_T>(fabs
      (static_cast<real_T>(lee_controller_B.ParamStep_ff)));
    if (lee_controller_B.ParamStep_ff > lee_controller_B.ParamStep_o2) {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_o2 /
        lee_controller_B.ParamStep_ff;
      lee_controller_B.ParamStep_i = lee_controller_B.ParamStep_i *
        lee_controller_B.ParamStep_g * lee_controller_B.ParamStep_g + 1.0F;
      lee_controller_B.ParamStep_o2 = lee_controller_B.ParamStep_ff;
    } else {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_ff /
        lee_controller_B.ParamStep_o2;
      lee_controller_B.ParamStep_i += lee_controller_B.ParamStep_g *
        lee_controller_B.ParamStep_g;
    }

    lee_controller_B.ParamStep_ff = (lee_controller_B.In1_m.setpoints[8] +
      static_cast<real32_T>(lee_controller_B.Divide)) *
      lee_controller_B.ParamStep_h3 + lee_controller_B.PD[2];
    lee_controller_B.b_ei[2] = -lee_controller_B.ParamStep_ff;
    lee_controller_B.ParamStep_ff = static_cast<real32_T>(fabs(static_cast<
      real_T>(lee_controller_B.ParamStep_ff)));
    if (lee_controller_B.ParamStep_ff > lee_controller_B.ParamStep_o2) {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_o2 /
        lee_controller_B.ParamStep_ff;
      lee_controller_B.ParamStep_i = lee_controller_B.ParamStep_i *
        lee_controller_B.ParamStep_g * lee_controller_B.ParamStep_g + 1.0F;
      lee_controller_B.ParamStep_o2 = lee_controller_B.ParamStep_ff;
    } else {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_ff /
        lee_controller_B.ParamStep_o2;
      lee_controller_B.ParamStep_i += lee_controller_B.ParamStep_g *
        lee_controller_B.ParamStep_g;
    }

    lee_controller_B.ParamStep_i = lee_controller_B.ParamStep_o2 *
      static_cast<real32_T>(sqrt(static_cast<real_T>
      (lee_controller_B.ParamStep_i)));
    lee_controller_B.ParamStep_h3 = 0.0F;
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.ParamStep_o2 = lee_controller_B.b_ei[lee_controller_B.idx];
      lee_controller_B.b3d[lee_controller_B.idx] = lee_controller_B.ParamStep_o2
        / lee_controller_B.ParamStep_i;
      lee_controller_B.ParamStep_h3 += static_cast<real32_T>
        ((lee_controller_B.R_mes[lee_controller_B.idx + 3] * lee_controller_B.c
          [1] + lee_controller_B.R_mes[lee_controller_B.idx] *
          lee_controller_B.c[0]) + lee_controller_B.R_mes[lee_controller_B.idx +
         6] * lee_controller_B.c[2]) * lee_controller_B.ParamStep_o2;
    }

    // MATLAB Function: '<S5>/MATLAB Function4'
    lee_controller_B.b_ei[0] = 0.0F;
    lee_controller_B.b_ei[1] = 0.0F;
    lee_controller_B.b_ei[2] = lee_controller_B.In1_m.setpoints[10];

    // MATLAB Function: '<S5>/lee att' incorporates:
    //   DataTypeConversion: '<S42>/Cast To Double11'
    //   DataTypeConversion: '<S42>/Cast To Double12'
    //   DataTypeConversion: '<S42>/Cast To Double13'
    //   MATLABSystem: '<S42>/Read Parameter11'
    //   MATLABSystem: '<S42>/Read Parameter12'
    //   MATLABSystem: '<S42>/Read Parameter13'

    lee_controller_B.tempR[0] = lee_controller_B.ParamStep_h2;
    lee_controller_B.tempR[3] = 0.0;
    lee_controller_B.tempR[6] = 0.0;
    lee_controller_B.tempR[1] = 0.0;
    lee_controller_B.tempR[4] = lee_controller_B.ParamStep_me;
    lee_controller_B.tempR[7] = 0.0;
    lee_controller_B.tempR[2] = 0.0;
    lee_controller_B.tempR[5] = 0.0;
    lee_controller_B.tempR[8] = lee_controller_B.ParamStep_mc;
    lee_controller_B.PD[0] = static_cast<real32_T>(cos(static_cast<real_T>
      (lee_controller_B.In1_m.setpoints[9])));
    lee_controller_B.PD[1] = static_cast<real32_T>(sin(static_cast<real_T>
      (lee_controller_B.In1_m.setpoints[9])));
    lee_controller_B.b2d_cross[0] = static_cast<real32_T>(lee_controller_B.b3d[1])
      * 0.0F - static_cast<real32_T>(lee_controller_B.b3d[2]) *
      lee_controller_B.PD[1];
    lee_controller_B.b2d_cross[1] = static_cast<real32_T>(lee_controller_B.b3d[2])
      * lee_controller_B.PD[0] - static_cast<real32_T>(lee_controller_B.b3d[0]) *
      0.0F;
    lee_controller_B.b2d_cross[2] = static_cast<real32_T>(lee_controller_B.b3d[0])
      * lee_controller_B.PD[1] - static_cast<real32_T>(lee_controller_B.b3d[1]) *
      lee_controller_B.PD[0];
    lee_controller_B.ParamStep_o2 = 1.29246971E-26F;
    lee_controller_B.ParamStep_ff = static_cast<real32_T>(fabs
      (static_cast<real_T>(lee_controller_B.b2d_cross[0])));
    if (lee_controller_B.ParamStep_ff > 1.29246971E-26F) {
      lee_controller_B.ParamStep_i = 1.0F;
      lee_controller_B.ParamStep_o2 = lee_controller_B.ParamStep_ff;
    } else {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_ff /
        1.29246971E-26F;
      lee_controller_B.ParamStep_i = lee_controller_B.ParamStep_g *
        lee_controller_B.ParamStep_g;
    }

    lee_controller_B.ParamStep_ff = static_cast<real32_T>(fabs
      (static_cast<real_T>(lee_controller_B.b2d_cross[1])));
    if (lee_controller_B.ParamStep_ff > lee_controller_B.ParamStep_o2) {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_o2 /
        lee_controller_B.ParamStep_ff;
      lee_controller_B.ParamStep_i = lee_controller_B.ParamStep_i *
        lee_controller_B.ParamStep_g * lee_controller_B.ParamStep_g + 1.0F;
      lee_controller_B.ParamStep_o2 = lee_controller_B.ParamStep_ff;
    } else {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_ff /
        lee_controller_B.ParamStep_o2;
      lee_controller_B.ParamStep_i += lee_controller_B.ParamStep_g *
        lee_controller_B.ParamStep_g;
    }

    lee_controller_B.ParamStep_ff = static_cast<real32_T>(fabs
      (static_cast<real_T>(lee_controller_B.b2d_cross[2])));
    if (lee_controller_B.ParamStep_ff > lee_controller_B.ParamStep_o2) {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_o2 /
        lee_controller_B.ParamStep_ff;
      lee_controller_B.ParamStep_i = lee_controller_B.ParamStep_i *
        lee_controller_B.ParamStep_g * lee_controller_B.ParamStep_g + 1.0F;
      lee_controller_B.ParamStep_o2 = lee_controller_B.ParamStep_ff;
    } else {
      lee_controller_B.ParamStep_g = lee_controller_B.ParamStep_ff /
        lee_controller_B.ParamStep_o2;
      lee_controller_B.ParamStep_i += lee_controller_B.ParamStep_g *
        lee_controller_B.ParamStep_g;
    }

    lee_controller_B.ParamStep_i = lee_controller_B.ParamStep_o2 *
      static_cast<real32_T>(sqrt(static_cast<real_T>
      (lee_controller_B.ParamStep_i)));
    lee_controller_B.ParamStep_o2 = lee_controller_B.b2d_cross[0] /
      lee_controller_B.ParamStep_i;
    lee_controller_B.Rd[3] = lee_controller_B.ParamStep_o2;
    lee_controller_B.Rd[6] = static_cast<real32_T>(lee_controller_B.b3d[0]);
    lee_controller_B.b2d_cross[0] = lee_controller_B.ParamStep_o2;

    // MATLAB Function: '<S5>/lee att'
    lee_controller_B.ParamStep_o2 = lee_controller_B.b2d_cross[1] /
      lee_controller_B.ParamStep_i;
    lee_controller_B.Rd[4] = lee_controller_B.ParamStep_o2;
    lee_controller_B.Rd[7] = static_cast<real32_T>(lee_controller_B.b3d[1]);
    lee_controller_B.b2d_cross[1] = lee_controller_B.ParamStep_o2;

    // MATLAB Function: '<S5>/lee att' incorporates:
    //   DataTypeConversion: '<S3>/Cast To Double7'
    //   DataTypeConversion: '<S42>/Cast To Double23'
    //   DataTypeConversion: '<S42>/Cast To Double24'
    //   DataTypeConversion: '<S42>/Cast To Double25'
    //   MATLABSystem: '<S42>/Read Parameter23'
    //   MATLABSystem: '<S42>/Read Parameter24'
    //   MATLABSystem: '<S42>/Read Parameter25'
    //   MATLABSystem: '<S42>/Read Parameter26'
    //   MATLABSystem: '<S42>/Read Parameter27'
    //   MATLABSystem: '<S42>/Read Parameter28'
    //   MATLABSystem: '<S42>/Read Parameter29'
    //   MATLABSystem: '<S42>/Read Parameter30'
    //   MATLABSystem: '<S42>/Read Parameter31'
    //   MATLABSystem: '<S42>/Read Parameter33'
    //   Math: '<S3>/Transpose'
    //   SignalConversion generated from: '<S21>/ SFunction '

    lee_controller_B.ParamStep_o2 = lee_controller_B.b2d_cross[2] /
      lee_controller_B.ParamStep_i;
    lee_controller_B.Rd[5] = lee_controller_B.ParamStep_o2;
    lee_controller_B.Rd[8] = static_cast<real32_T>(lee_controller_B.b3d[2]);
    lee_controller_B.Rd[0] = lee_controller_B.b2d_cross[1] *
      static_cast<real32_T>(lee_controller_B.b3d[2]) -
      lee_controller_B.ParamStep_o2 * static_cast<real32_T>
      (lee_controller_B.b3d[1]);
    lee_controller_B.Rd[1] = lee_controller_B.ParamStep_o2 *
      static_cast<real32_T>(lee_controller_B.b3d[0]) -
      lee_controller_B.b2d_cross[0] * static_cast<real32_T>
      (lee_controller_B.b3d[2]);
    lee_controller_B.Rd[2] = lee_controller_B.b2d_cross[0] *
      static_cast<real32_T>(lee_controller_B.b3d[1]) -
      lee_controller_B.b2d_cross[1] * static_cast<real32_T>
      (lee_controller_B.b3d[0]);
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.catArgs[3 * lee_controller_B.idx] =
        lee_controller_B.R_mes[lee_controller_B.idx];
      lee_controller_B.catArgs[3 * lee_controller_B.idx + 1] =
        lee_controller_B.R_mes[lee_controller_B.idx + 3];
      lee_controller_B.catArgs[3 * lee_controller_B.idx + 2] =
        lee_controller_B.R_mes[lee_controller_B.idx + 6];
    }

    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      for (lee_controller_B.pmax = 0; lee_controller_B.pmax < 3;
           lee_controller_B.pmax++) {
        lee_controller_B.pmin = 3 * lee_controller_B.idx + lee_controller_B.pmax;
        lee_controller_B.R_err_tmp[lee_controller_B.pmin] = 0.0F;
        lee_controller_B.R_err_tmp[lee_controller_B.pmin] +=
          lee_controller_B.Rd[3 * lee_controller_B.idx] * static_cast<real32_T>
          (lee_controller_B.catArgs[lee_controller_B.pmax]);
        lee_controller_B.npad = 3 * lee_controller_B.idx + 1;
        lee_controller_B.R_err_tmp[lee_controller_B.pmin] +=
          static_cast<real32_T>(lee_controller_B.catArgs[lee_controller_B.pmax +
          3]) * lee_controller_B.Rd[lee_controller_B.npad];
        lee_controller_B.pow2p = 3 * lee_controller_B.idx + 2;
        lee_controller_B.R_err_tmp[lee_controller_B.pmin] +=
          static_cast<real32_T>(lee_controller_B.catArgs[lee_controller_B.pmax +
          6]) * lee_controller_B.Rd[lee_controller_B.pow2p];
        lee_controller_B.ParamStep[lee_controller_B.pmin] =
          ((lee_controller_B.Rd[3 * lee_controller_B.pmax + 1] *
            static_cast<real32_T>(lee_controller_B.R_mes[lee_controller_B.npad])
            + lee_controller_B.Rd[3 * lee_controller_B.pmax] *
            static_cast<real32_T>(lee_controller_B.R_mes[3 *
             lee_controller_B.idx])) + lee_controller_B.Rd[3 *
           lee_controller_B.pmax + 2] * static_cast<real32_T>
           (lee_controller_B.R_mes[lee_controller_B.pow2p])) -
          lee_controller_B.R_err_tmp[lee_controller_B.pmin];
      }
    }

    for (lee_controller_B.idx = 0; lee_controller_B.idx < 9;
         lee_controller_B.idx++) {
      lee_controller_B.R_err[lee_controller_B.idx] = 0.5F *
        lee_controller_B.ParamStep[lee_controller_B.idx];
    }

    lee_controller_B.PD[0] = lee_controller_B.R_err[5];
    lee_controller_B.PD[1] = lee_controller_B.R_err[6];
    lee_controller_B.PD[2] = lee_controller_B.R_err[1];
    lee_controller_B.ParamStep[0] = static_cast<real32_T>(-static_cast<real_T>
      (lee_controller_B.ParamStep_o3));
    lee_controller_B.ParamStep[3] = -0.0F;
    lee_controller_B.ParamStep[6] = -0.0F;
    lee_controller_B.ParamStep[1] = -0.0F;
    lee_controller_B.ParamStep[4] = static_cast<real32_T>(-static_cast<real_T>
      (lee_controller_B.ParamStep_lm));
    lee_controller_B.ParamStep[7] = -0.0F;
    lee_controller_B.ParamStep[2] = -0.0F;
    lee_controller_B.ParamStep[5] = -0.0F;
    lee_controller_B.ParamStep[8] = static_cast<real32_T>(-static_cast<real_T>
      (lee_controller_B.ParamStep_m));
    lee_controller_B.ParamStep_c[0] = lee_controller_B.ParamStep_mj;
    lee_controller_B.ParamStep_c[3] = 0.0F;
    lee_controller_B.ParamStep_c[6] = 0.0F;
    lee_controller_B.ParamStep_c[1] = 0.0F;
    lee_controller_B.ParamStep_c[4] = lee_controller_B.ParamStep_cn;
    lee_controller_B.ParamStep_c[7] = 0.0F;
    lee_controller_B.ParamStep_c[2] = 0.0F;
    lee_controller_B.ParamStep_c[5] = 0.0F;
    lee_controller_B.ParamStep_c[8] = lee_controller_B.ParamStep_fm;
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.b2d_cross[lee_controller_B.idx] = static_cast<real32_T>
        (lee_controller_B.TmpSignalConversionAtSFunct[lee_controller_B.idx]) -
        ((lee_controller_B.R_err_tmp[lee_controller_B.idx + 3] * 0.0F +
          lee_controller_B.R_err_tmp[lee_controller_B.idx] * 0.0F) +
         lee_controller_B.R_err_tmp[lee_controller_B.idx + 6] *
         lee_controller_B.b_ei[2]);
      lee_controller_B.c[lee_controller_B.idx] =
        (lee_controller_B.tempR[lee_controller_B.idx + 3] *
         lee_controller_B.TmpSignalConversionAtSFunct[1] +
         lee_controller_B.tempR[lee_controller_B.idx] *
         lee_controller_B.TmpSignalConversionAtSFunct[0]) +
        lee_controller_B.tempR[lee_controller_B.idx + 6] *
        lee_controller_B.TmpSignalConversionAtSFunct[2];
      lee_controller_B.ParamStep_l[lee_controller_B.idx] =
        (lee_controller_B.ParamStep[lee_controller_B.idx + 3] *
         lee_controller_B.PD[1] +
         lee_controller_B.ParamStep[lee_controller_B.idx] * lee_controller_B.PD
         [0]) + lee_controller_B.ParamStep[lee_controller_B.idx + 6] *
        lee_controller_B.PD[2];
    }

    lee_controller_B.ParamStep[0] = lee_controller_B.ParamStep_p;
    lee_controller_B.ParamStep[3] = 0.0F;
    lee_controller_B.ParamStep[6] = 0.0F;
    lee_controller_B.ParamStep[1] = 0.0F;
    lee_controller_B.ParamStep[4] = lee_controller_B.ParamStep_e;
    lee_controller_B.ParamStep[7] = 0.0F;
    lee_controller_B.ParamStep[2] = 0.0F;
    lee_controller_B.ParamStep[5] = 0.0F;
    lee_controller_B.ParamStep[8] = lee_controller_B.ParamStep_o4;
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.fv[lee_controller_B.idx] = (lee_controller_B.ParamStep_l5
        * lee_controller_B.PD[lee_controller_B.idx] +
        lee_controller_B.b2d_cross[lee_controller_B.idx]) * static_cast<real32_T>
        (lee_controller_P.dt) + static_cast<real32_T>
        (lee_controller_P.eir[lee_controller_B.idx]);
      lee_controller_B.ParamStep_d[lee_controller_B.idx] =
        (lee_controller_B.ParamStep_c[lee_controller_B.idx + 3] *
         lee_controller_B.b2d_cross[1] +
         lee_controller_B.ParamStep_c[lee_controller_B.idx] *
         lee_controller_B.b2d_cross[0]) +
        lee_controller_B.ParamStep_c[lee_controller_B.idx + 6] *
        lee_controller_B.b2d_cross[2];
    }

    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.PD[lee_controller_B.idx] =
        (lee_controller_B.ParamStep_l[lee_controller_B.idx] -
         lee_controller_B.ParamStep_d[lee_controller_B.idx]) -
        ((lee_controller_B.ParamStep[lee_controller_B.idx + 3] *
          lee_controller_B.fv[1] +
          lee_controller_B.ParamStep[lee_controller_B.idx] *
          lee_controller_B.fv[0]) +
         lee_controller_B.ParamStep[lee_controller_B.idx + 6] *
         lee_controller_B.fv[2]);
    }

    lee_controller_B.ParamStep_l[0] = static_cast<real32_T>
      (lee_controller_B.In1_f.xyz[1] * lee_controller_B.c[2] -
       lee_controller_B.c[1] * lee_controller_B.In1_f.xyz[2]);
    lee_controller_B.ParamStep_l[1] = static_cast<real32_T>(lee_controller_B.c[0]
      * lee_controller_B.In1_f.xyz[2] - lee_controller_B.In1_f.xyz[0] *
      lee_controller_B.c[2]);
    lee_controller_B.ParamStep_l[2] = static_cast<real32_T>
      (lee_controller_B.In1_f.xyz[0] * lee_controller_B.c[1] -
       lee_controller_B.c[0] * lee_controller_B.In1_f.xyz[1]);
    lee_controller_B.R_mes[0] = 0.0;
    lee_controller_B.R_mes[3] = -static_cast<real_T>(lee_controller_B.In1_f.xyz
      [2]);
    lee_controller_B.R_mes[6] = lee_controller_B.In1_f.xyz[1];
    lee_controller_B.R_mes[1] = lee_controller_B.In1_f.xyz[2];
    lee_controller_B.R_mes[4] = 0.0;
    lee_controller_B.R_mes[7] = -static_cast<real_T>(lee_controller_B.In1_f.xyz
      [0]);
    lee_controller_B.R_mes[2] = -static_cast<real_T>(lee_controller_B.In1_f.xyz
      [1]);
    lee_controller_B.R_mes[5] = lee_controller_B.In1_f.xyz[0];
    lee_controller_B.R_mes[8] = 0.0;

    // MATLAB Function: '<S5>/MATLAB Function4'
    lee_controller_B.fv[0] = 0.0F;
    lee_controller_B.fv[1] = 0.0F;
    lee_controller_B.fv[2] = lee_controller_B.In1_m.setpoints[11];

    // MATLAB Function: '<S5>/lee att'
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      for (lee_controller_B.pmax = 0; lee_controller_B.pmax < 3;
           lee_controller_B.pmax++) {
        lee_controller_B.ParamStep[lee_controller_B.idx + 3 *
          lee_controller_B.pmax] = static_cast<real32_T>
          ((lee_controller_B.catArgs[3 * lee_controller_B.pmax + 1] *
            lee_controller_B.R_mes[lee_controller_B.idx + 3] +
            lee_controller_B.catArgs[3 * lee_controller_B.pmax] *
            lee_controller_B.R_mes[lee_controller_B.idx]) +
           lee_controller_B.catArgs[3 * lee_controller_B.pmax + 2] *
           lee_controller_B.R_mes[lee_controller_B.idx + 6]);
      }

      lee_controller_B.ParamStep_d[lee_controller_B.idx] = 0.0F;
      lee_controller_B.R_err_tmp_d[lee_controller_B.idx] = 0.0F;
      for (lee_controller_B.pmax = 0; lee_controller_B.pmax < 3;
           lee_controller_B.pmax++) {
        lee_controller_B.pmin = 3 * lee_controller_B.pmax + lee_controller_B.idx;
        lee_controller_B.ParamStep_c[lee_controller_B.pmin] = 0.0F;
        lee_controller_B.ParamStep_c[lee_controller_B.pmin] +=
          lee_controller_B.Rd[3 * lee_controller_B.pmax] *
          lee_controller_B.ParamStep[lee_controller_B.idx];
        lee_controller_B.ParamStep_c[lee_controller_B.pmin] +=
          lee_controller_B.Rd[3 * lee_controller_B.pmax + 1] *
          lee_controller_B.ParamStep[lee_controller_B.idx + 3];
        lee_controller_B.ParamStep_c[lee_controller_B.pmin] +=
          lee_controller_B.Rd[3 * lee_controller_B.pmax + 2] *
          lee_controller_B.ParamStep[lee_controller_B.idx + 6];
        lee_controller_B.ParamStep_d[lee_controller_B.idx] +=
          lee_controller_B.ParamStep_c[lee_controller_B.pmin] *
          lee_controller_B.b_ei[lee_controller_B.pmax];
        lee_controller_B.R_err_tmp_d[lee_controller_B.idx] +=
          lee_controller_B.R_err_tmp[lee_controller_B.pmin] *
          lee_controller_B.fv[lee_controller_B.pmax];
      }

      lee_controller_B.fv1[lee_controller_B.idx] =
        lee_controller_B.ParamStep_d[lee_controller_B.idx] -
        lee_controller_B.R_err_tmp_d[lee_controller_B.idx];
    }

    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.b3d[lee_controller_B.idx] =
        (lee_controller_B.PD[lee_controller_B.idx] +
         lee_controller_B.ParamStep_l[lee_controller_B.idx]) -
        ((static_cast<real32_T>(lee_controller_B.tempR[lee_controller_B.idx + 3])
          * lee_controller_B.fv1[1] + static_cast<real32_T>
          (lee_controller_B.tempR[lee_controller_B.idx]) * lee_controller_B.fv1
          [0]) + static_cast<real32_T>
         (lee_controller_B.tempR[lee_controller_B.idx + 6]) *
         lee_controller_B.fv1[2]);
    }

    // MATLAB Function: '<S5>/rpm_pos allocation' incorporates:
    //   MATLAB Function: '<S5>/lee pos'

    lee_controller_rpmallocation(static_cast<real_T>
      (lee_controller_B.ParamStep_h3), lee_controller_B.b3d,
      lee_controller_B.inv_A, lee_controller_B.rpm);

    // DataTypeConversion: '<S5>/Cast To Single9' incorporates:
    //   DataTypeConversion: '<S5>/Cast To Single7'
    //   DataTypeConversion: '<S5>/Cast To Single8'

    lee_controller_B.rtb_q_drone_idx_0 = floor(lee_controller_B.time);
    if (rtIsNaN(lee_controller_B.rtb_q_drone_idx_0) || rtIsInf
        (lee_controller_B.rtb_q_drone_idx_0)) {
      lee_controller_B.K13 = 0.0;
    } else {
      lee_controller_B.K13 = fmod(lee_controller_B.rtb_q_drone_idx_0,
        1.8446744073709552E+19);
    }

    // BusAssignment: '<S5>/Bus Assignment' incorporates:
    //   DataTypeConversion: '<S5>/Cast To Single9'

    lee_controller_B.BusAssignment.timestamp = lee_controller_B.K13 < 0.0 ?
      static_cast<uint64_T>(-static_cast<int64_T>(static_cast<uint64_T>
      (-lee_controller_B.K13))) : static_cast<uint64_T>(lee_controller_B.K13);

    // MATLABSystem: '<S35>/SinkBlock' incorporates:
    //   BusAssignment: '<S5>/Bus Assignment'

    uORB_write_step(lee_controller_DW.obj_cg.orbMetadataObj,
                    &lee_controller_DW.obj_cg.orbAdvertiseObj,
                    &lee_controller_B.BusAssignment);

    // DataTypeConversion: '<S5>/Cast To Single7'
    if (rtIsNaN(lee_controller_B.rtb_q_drone_idx_0) || rtIsInf
        (lee_controller_B.rtb_q_drone_idx_0)) {
      lee_controller_B.K13 = 0.0;
    } else {
      lee_controller_B.K13 = fmod(lee_controller_B.rtb_q_drone_idx_0,
        1.8446744073709552E+19);
    }

    // BusAssignment: '<S5>/Bus Assignment2' incorporates:
    //   DataTypeConversion: '<S5>/Cast To Single6'
    //   DataTypeConversion: '<S5>/Cast To Single7'
    //   MATLAB Function: '<S5>/lee pos'
    //   Math: '<S5>/Transpose2'

    lee_controller_B.BusAssignment2.timestamp = lee_controller_B.K13 < 0.0 ?
      static_cast<uint64_T>(-static_cast<int64_T>(static_cast<uint64_T>
      (-lee_controller_B.K13))) : static_cast<uint64_T>(lee_controller_B.K13);
    lee_controller_B.BusAssignment2.fz = lee_controller_B.ParamStep_h3;
    lee_controller_B.BusAssignment2.tau[0] = static_cast<real32_T>
      (lee_controller_B.b3d[0]);
    lee_controller_B.BusAssignment2.tau[1] = static_cast<real32_T>
      (lee_controller_B.b3d[1]);
    lee_controller_B.BusAssignment2.tau[2] = static_cast<real32_T>
      (lee_controller_B.b3d[2]);

    // MATLABSystem: '<S37>/SinkBlock' incorporates:
    //   BusAssignment: '<S5>/Bus Assignment2'

    uORB_write_step(lee_controller_DW.obj_cs.orbMetadataObj,
                    &lee_controller_DW.obj_cs.orbAdvertiseObj,
                    &lee_controller_B.BusAssignment2);

    // DataTypeConversion: '<S5>/Cast To Single8'
    if (rtIsNaN(lee_controller_B.rtb_q_drone_idx_0) || rtIsInf
        (lee_controller_B.rtb_q_drone_idx_0)) {
      lee_controller_B.K13 = 0.0;
    } else {
      lee_controller_B.K13 = fmod(lee_controller_B.rtb_q_drone_idx_0,
        1.8446744073709552E+19);
    }

    // BusAssignment: '<S5>/Bus Assignment1' incorporates:
    //   DataTypeConversion: '<S5>/Cast To Single8'
    //   MATLAB Function: '<S5>/lee att'

    lee_controller_B.BusAssignment1.timestamp = lee_controller_B.K13 < 0.0 ?
      static_cast<uint64_T>(-static_cast<int64_T>(static_cast<uint64_T>
      (-lee_controller_B.K13))) : static_cast<uint64_T>(lee_controller_B.K13);
    lee_controller_B.BusAssignment1.eyaw = lee_controller_B.R_err[1];
    lee_controller_B.BusAssignment1.ew = lee_controller_B.b2d_cross[2];

    // MATLABSystem: '<S36>/SinkBlock' incorporates:
    //   BusAssignment: '<S5>/Bus Assignment1'

    uORB_write_step(lee_controller_DW.obj_lu.orbMetadataObj,
                    &lee_controller_DW.obj_lu.orbAdvertiseObj,
                    &lee_controller_B.BusAssignment1);
  }

  // End of Logic: '<Root>/AND'
  // End of Outputs for SubSystem: '<Root>/LEE_CONTROLLER'

  // MATLABSystem: '<S42>/Read Parameter7'
  if (lee_controller_DW.obj_m.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_m.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_m.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_lt);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_lt = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter8'
  if (lee_controller_DW.obj_b.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_b.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_b.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_o);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_o = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter10'
  if (lee_controller_DW.obj_cm.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_cm.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_cm.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_o2);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_o2 = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter9'
  if (lee_controller_DW.obj.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_i);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_i = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter'
  if (lee_controller_DW.obj_mf.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_mf.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_mf.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_f);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_f = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter1'
  if (lee_controller_DW.obj_kp.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_kp.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_kp.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_iz);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_iz = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter2'
  if (lee_controller_DW.obj_ef.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_ef.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_ef.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_ff);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_ff = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter3'
  if (lee_controller_DW.obj_ph.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_ph.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_ph.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_g);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_g = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter4'
  if (lee_controller_DW.obj_k.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_k.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_k.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_co);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_co = 0.0F;
  }

  // MATLABSystem: '<S42>/Read Parameter5'
  if (lee_controller_DW.obj_a.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_a.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  lee_controller_B.b_varargout_2_i = MW_Param_Step
    (lee_controller_DW.obj_a.MW_PARAMHANDLE, lee_controller_B.ParamDataType,
     &lee_controller_B.ParamStep_o3);
  if (lee_controller_B.b_varargout_2_i) {
    lee_controller_B.ParamStep_o3 = 0.0F;
  }

  // Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem1' incorporates:
  //   EnablePort: '<S2>/Enable'

  // Logic: '<Root>/AND1'
  if (lee_controller_B.carry && lee_controller_B.NOT) {
    // MATLAB Function: '<S2>/inv alloc_matrix' incorporates:
    //   DataTypeConversion: '<S42>/Cast To Double34'
    //   DataTypeConversion: '<S42>/Cast To Double35'
    //   DataTypeConversion: '<S42>/Cast To Double36'
    //   MATLABSystem: '<S42>/Read Parameter34'
    //   MATLABSystem: '<S42>/Read Parameter35'
    //   MATLABSystem: '<S42>/Read Parameter36'

    lee_controller_invalloc_matrix(static_cast<real_T>
      (lee_controller_B.ParamStep_k), static_cast<real_T>
      (lee_controller_B.ParamStep_pc), static_cast<real_T>
      (lee_controller_B.ParamStep_px), lee_controller_B.inv_A);

    // Fcn: '<S19>/Fcn2' incorporates:
    //   DataTypeConversion: '<S19>/Data Type Conversion'
    //   DataTypeConversion: '<S9>/Cast To Double3'

    lee_controller_B.ParamStep_lm = (static_cast<real32_T>
      (lee_controller_B.In1_c.values[3]) - 1500.0F) / 500.0F;

    // Fcn: '<S17>/Fcn2' incorporates:
    //   DataTypeConversion: '<S17>/Data Type Conversion'
    //   DataTypeConversion: '<S9>/Cast To Double'

    lee_controller_B.ParamStep_m = (static_cast<real32_T>
      (lee_controller_B.In1_c.values[0]) - 1500.0F) / 500.0F;

    // Signum: '<S17>/Sign'
    if (lee_controller_B.ParamStep_m < 0.0F) {
      lee_controller_B.ParamStep_mj = -1.0F;
    } else if (lee_controller_B.ParamStep_m > 0.0F) {
      lee_controller_B.ParamStep_mj = 1.0F;
    } else {
      lee_controller_B.ParamStep_mj = 0.0F;
    }

    // End of Signum: '<S17>/Sign'

    // Sum: '<S17>/Sum' incorporates:
    //   Constant: '<S17>/Constant'
    //   Product: '<S17>/Product'

    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.ParamStep_m -
      lee_controller_B.ParamStep_mj * lee_controller_P.roll_offset;

    // Fcn: '<S18>/Fcn2' incorporates:
    //   DataTypeConversion: '<S18>/Data Type Conversion'
    //   DataTypeConversion: '<S9>/Cast To Double1'

    lee_controller_B.ParamStep_m = (static_cast<real32_T>
      (lee_controller_B.In1_c.values[1]) - 1500.0F) / 500.0F;

    // MATLAB Function: '<S2>/att control' incorporates:
    //   DataTypeConversion: '<S42>/Cast To Double'
    //   DataTypeConversion: '<S42>/Cast To Double1'
    //   DataTypeConversion: '<S42>/Cast To Double2'
    //   MATLABSystem: '<S42>/Read Parameter'
    //   MATLABSystem: '<S42>/Read Parameter1'
    //   MATLABSystem: '<S42>/Read Parameter2'

    memset(&lee_controller_B.R_mes[0], 0, 9U * sizeof(real_T));
    lee_controller_B.R_mes[0] = lee_controller_B.ParamStep_f;
    lee_controller_B.R_mes[4] = lee_controller_B.ParamStep_iz;
    lee_controller_B.R_mes[8] = lee_controller_B.ParamStep_ff;
    lee_controller_B.K13 = lee_controller_B.K12 * lee_controller_B.K12;
    lee_controller_B.K14 = lee_controller_B.q_tmp_b * lee_controller_B.q_tmp_b;
    lee_controller_B.tempR[0] = 1.0 - (lee_controller_B.K14 +
      lee_controller_B.K13) * 2.0;
    lee_controller_B.K23 = lee_controller_B.q_tmp_n * lee_controller_B.q_tmp_b;
    lee_controller_B.K24 = lee_controller_B.q_tmp * lee_controller_B.K12;
    lee_controller_B.tempR[1] = (lee_controller_B.K23 - lee_controller_B.K24) *
      2.0;
    lee_controller_B.K34 = lee_controller_B.q_tmp_n * lee_controller_B.K12;
    lee_controller_B.tempR_tmp = lee_controller_B.q_tmp *
      lee_controller_B.q_tmp_b;
    lee_controller_B.tempR[2] = (lee_controller_B.K34 +
      lee_controller_B.tempR_tmp) * 2.0;
    lee_controller_B.tempR[3] = (lee_controller_B.K23 + lee_controller_B.K24) *
      2.0;
    lee_controller_B.K23 = lee_controller_B.q_tmp_n * lee_controller_B.q_tmp_n;
    lee_controller_B.tempR[4] = 1.0 - (lee_controller_B.K23 +
      lee_controller_B.K13) * 2.0;
    lee_controller_B.K13 = lee_controller_B.q_tmp_b * lee_controller_B.K12;
    lee_controller_B.K24 = lee_controller_B.q_tmp * lee_controller_B.q_tmp_n;
    lee_controller_B.tempR[5] = (lee_controller_B.K13 - lee_controller_B.K24) *
      2.0;
    lee_controller_B.tempR[6] = (lee_controller_B.K34 -
      lee_controller_B.tempR_tmp) * 2.0;
    lee_controller_B.tempR[7] = (lee_controller_B.K13 + lee_controller_B.K24) *
      2.0;
    lee_controller_B.tempR[8] = 1.0 - (lee_controller_B.K23 +
      lee_controller_B.K14) * 2.0;
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.pmax = (static_cast<int8_T>(lee_controller_B.idx + 1) - 1)
        * 3;
      lee_controller_B.R_drone[static_cast<int8_T>(lee_controller_B.idx + 1) - 1]
        = lee_controller_B.tempR[lee_controller_B.pmax];
      lee_controller_B.R_drone[static_cast<int8_T>(lee_controller_B.idx + 1) + 2]
        = lee_controller_B.tempR[lee_controller_B.pmax + 1];
      lee_controller_B.R_drone[static_cast<int8_T>(lee_controller_B.idx + 1) + 5]
        = lee_controller_B.tempR[lee_controller_B.pmax + 2];
    }

    lee_controller_B.K13 = lee_controller_rt_atan2d_snf
      (lee_controller_B.R_drone[1], lee_controller_B.R_drone[0]);
    lee_controller_B.K12 = sin(lee_controller_B.K13);
    lee_controller_B.K13 = cos(lee_controller_B.K13);
    lee_controller_B.tempR[0] = lee_controller_B.K13;
    lee_controller_B.tempR[1] = -lee_controller_B.K12;
    lee_controller_B.tempR[2] = 0.0;
    lee_controller_B.tempR[3] = lee_controller_B.K12;
    lee_controller_B.tempR[4] = lee_controller_B.K13;
    lee_controller_B.tempR[5] = 0.0;
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.tempR[lee_controller_B.idx + 6] =
        b_0[lee_controller_B.idx];
      for (lee_controller_B.pmax = 0; lee_controller_B.pmax < 3;
           lee_controller_B.pmax++) {
        lee_controller_B.pmin = 3 * lee_controller_B.pmax + lee_controller_B.idx;
        lee_controller_B.catArgs[lee_controller_B.pmin] = 0.0;
        lee_controller_B.catArgs[lee_controller_B.pmin] +=
          lee_controller_B.R_drone[3 * lee_controller_B.pmax] *
          lee_controller_B.tempR[lee_controller_B.idx];
        lee_controller_B.catArgs[lee_controller_B.pmin] +=
          lee_controller_B.R_drone[3 * lee_controller_B.pmax + 1] *
          lee_controller_B.tempR[lee_controller_B.idx + 3];
        lee_controller_B.catArgs[lee_controller_B.pmin] +=
          lee_controller_B.R_drone[3 * lee_controller_B.pmax + 2] *
          lee_controller_B.tempR[lee_controller_B.idx + 6];
      }
    }

    lee_controller_B.K12 = lee_controller_B.catArgs[1] +
      lee_controller_B.catArgs[3];
    lee_controller_B.K13 = lee_controller_B.catArgs[2] +
      lee_controller_B.catArgs[6];
    lee_controller_B.K14 = lee_controller_B.catArgs[5] -
      lee_controller_B.catArgs[7];
    lee_controller_B.K23 = lee_controller_B.catArgs[5] +
      lee_controller_B.catArgs[7];
    lee_controller_B.K24 = lee_controller_B.catArgs[6] -
      lee_controller_B.catArgs[2];
    lee_controller_B.K34 = lee_controller_B.catArgs[1] -
      lee_controller_B.catArgs[3];
    lee_controller_B.A[0] = ((lee_controller_B.catArgs[0] -
      lee_controller_B.catArgs[4]) - lee_controller_B.catArgs[8]) / 3.0;
    lee_controller_B.A[4] = lee_controller_B.K12 / 3.0;
    lee_controller_B.A[8] = lee_controller_B.K13 / 3.0;
    lee_controller_B.A[12] = lee_controller_B.K14 / 3.0;
    lee_controller_B.A[1] = lee_controller_B.K12 / 3.0;
    lee_controller_B.A[5] = ((lee_controller_B.catArgs[4] -
      lee_controller_B.catArgs[0]) - lee_controller_B.catArgs[8]) / 3.0;
    lee_controller_B.A[9] = lee_controller_B.K23 / 3.0;
    lee_controller_B.A[13] = lee_controller_B.K24 / 3.0;
    lee_controller_B.A[2] = lee_controller_B.K13 / 3.0;
    lee_controller_B.A[6] = lee_controller_B.K23 / 3.0;
    lee_controller_B.A[10] = ((lee_controller_B.catArgs[8] -
      lee_controller_B.catArgs[0]) - lee_controller_B.catArgs[4]) / 3.0;
    lee_controller_B.A[14] = lee_controller_B.K34 / 3.0;
    lee_controller_B.A[3] = lee_controller_B.K14 / 3.0;
    lee_controller_B.A[7] = lee_controller_B.K24 / 3.0;
    lee_controller_B.A[11] = lee_controller_B.K34 / 3.0;
    lee_controller_B.A[15] = ((lee_controller_B.catArgs[0] +
      lee_controller_B.catArgs[4]) + lee_controller_B.catArgs[8]) / 3.0;
    if (lee_controller_anyNonFinite(lee_controller_B.A)) {
      for (lee_controller_B.idx = 0; lee_controller_B.idx < 16;
           lee_controller_B.idx++) {
        lee_controller_B.V[lee_controller_B.idx].re = (rtNaN);
        lee_controller_B.V[lee_controller_B.idx].im = 0.0;
      }

      lee_controller_B.D[0].re = (rtNaN);
      lee_controller_B.D[1].re = (rtNaN);
      lee_controller_B.D[2].re = (rtNaN);
      lee_controller_B.D[3].re = (rtNaN);
    } else {
      int32_T exitg2;
      lee_controller_B.b_varargout_2_i = true;
      lee_controller_B.pmax = 0;
      exitg1 = false;
      while ((!exitg1) && (lee_controller_B.pmax < 4)) {
        lee_controller_B.idx = 0;
        do {
          exitg2 = 0;
          if (lee_controller_B.idx <= lee_controller_B.pmax) {
            if (!(lee_controller_B.A[(lee_controller_B.pmax << 2) +
                  lee_controller_B.idx] == lee_controller_B.A
                  [(lee_controller_B.idx << 2) + lee_controller_B.pmax])) {
              lee_controller_B.b_varargout_2_i = false;
              exitg2 = 1;
            } else {
              lee_controller_B.idx++;
            }
          } else {
            lee_controller_B.pmax++;
            exitg2 = 2;
          }
        } while (exitg2 == 0);

        if (exitg2 == 1) {
          exitg1 = true;
        }
      }

      if (lee_controller_B.b_varargout_2_i) {
        lee_controller_schur(lee_controller_B.A, lee_controller_B.U,
                             lee_controller_B.T);
        for (lee_controller_B.idx = 0; lee_controller_B.idx < 16;
             lee_controller_B.idx++) {
          lee_controller_B.V[lee_controller_B.idx].re =
            lee_controller_B.U[lee_controller_B.idx];
          lee_controller_B.V[lee_controller_B.idx].im = 0.0;
        }

        lee_controller_B.D[0].re = lee_controller_B.T[0];
        lee_controller_B.D[1].re = lee_controller_B.T[5];
        lee_controller_B.D[2].re = lee_controller_B.T[10];
        lee_controller_B.D[3].re = lee_controller_B.T[15];
      } else {
        lee_controller_B.b_varargout_2_i = true;
        lee_controller_B.idx = 0;
        exitg1 = false;
        while ((!exitg1) && (lee_controller_B.idx < 4)) {
          lee_controller_B.pmax = 0;
          do {
            exitg2 = 0;
            if (lee_controller_B.pmax <= lee_controller_B.idx) {
              if (!(lee_controller_B.A[(lee_controller_B.idx << 2) +
                    lee_controller_B.pmax] == -lee_controller_B.A
                    [(lee_controller_B.pmax << 2) + lee_controller_B.idx])) {
                lee_controller_B.b_varargout_2_i = false;
                exitg2 = 1;
              } else {
                lee_controller_B.pmax++;
              }
            } else {
              lee_controller_B.idx++;
              exitg2 = 2;
            }
          } while (exitg2 == 0);

          if (exitg2 == 1) {
            exitg1 = true;
          }
        }

        if (lee_controller_B.b_varargout_2_i) {
          lee_controller_schur(lee_controller_B.A, lee_controller_B.U,
                               lee_controller_B.T);
          lee_controller_B.idx = 1;
          do {
            exitg2 = 0;
            if (lee_controller_B.idx <= 4) {
              boolean_T guard1 = false;
              guard1 = false;
              if (lee_controller_B.idx != 4) {
                lee_controller_B.K13 = lee_controller_B.T[((lee_controller_B.idx
                  - 1) << 2) + lee_controller_B.idx];
                if (lee_controller_B.K13 != 0.0) {
                  lee_controller_B.K12 = fabs(lee_controller_B.K13);
                  lee_controller_B.D[lee_controller_B.idx - 1].re = 0.0;
                  lee_controller_B.D[lee_controller_B.idx - 1].im =
                    lee_controller_B.K12;
                  lee_controller_B.D[lee_controller_B.idx].re = 0.0;
                  lee_controller_B.D[lee_controller_B.idx].im =
                    -lee_controller_B.K12;
                  lee_controller_B.idx += 2;
                } else {
                  guard1 = true;
                }
              } else {
                guard1 = true;
              }

              if (guard1) {
                lee_controller_B.D[lee_controller_B.idx - 1].re = 0.0;
                lee_controller_B.D[lee_controller_B.idx - 1].im = 0.0;
                lee_controller_B.idx++;
              }
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);

          for (lee_controller_B.idx = 0; lee_controller_B.idx < 16;
               lee_controller_B.idx++) {
            lee_controller_B.V[lee_controller_B.idx].re =
              lee_controller_B.U[lee_controller_B.idx];
            lee_controller_B.V[lee_controller_B.idx].im = 0.0;
          }

          lee_controller_B.pmax = 1;
          do {
            exitg2 = 0;
            if (lee_controller_B.pmax <= 4) {
              if (lee_controller_B.pmax != 4) {
                lee_controller_B.idx = (lee_controller_B.pmax - 1) << 2;
                lee_controller_B.K13 = lee_controller_B.T[lee_controller_B.idx +
                  lee_controller_B.pmax];
                if (lee_controller_B.K13 != 0.0) {
                  if (lee_controller_B.K13 < 0.0) {
                    lee_controller_B.pmin = 1;
                  } else {
                    lee_controller_B.pmin = -1;
                  }

                  lee_controller_B.q_tmp =
                    lee_controller_B.V[lee_controller_B.idx].re;
                  lee_controller_B.npad = lee_controller_B.pmax << 2;
                  lee_controller_B.K13 =
                    lee_controller_B.V[lee_controller_B.npad].re *
                    static_cast<real_T>(lee_controller_B.pmin);
                  if (lee_controller_B.K13 == 0.0) {
                    lee_controller_B.V[lee_controller_B.idx].re =
                      lee_controller_B.q_tmp / 1.4142135623730951;
                    lee_controller_B.V[lee_controller_B.idx].im = 0.0;
                  } else if (lee_controller_B.q_tmp == 0.0) {
                    lee_controller_B.V[lee_controller_B.idx].re = 0.0;
                    lee_controller_B.V[lee_controller_B.idx].im =
                      lee_controller_B.K13 / 1.4142135623730951;
                  } else {
                    lee_controller_B.V[lee_controller_B.idx].re =
                      lee_controller_B.q_tmp / 1.4142135623730951;
                    lee_controller_B.V[lee_controller_B.idx].im =
                      lee_controller_B.K13 / 1.4142135623730951;
                  }

                  lee_controller_B.V[lee_controller_B.npad].re =
                    lee_controller_B.V[lee_controller_B.idx].re;
                  lee_controller_B.V[lee_controller_B.npad].im =
                    -lee_controller_B.V[lee_controller_B.idx].im;
                  lee_controller_B.q_tmp =
                    lee_controller_B.V[lee_controller_B.idx + 1].re;
                  lee_controller_B.K13 =
                    lee_controller_B.V[lee_controller_B.npad + 1].re *
                    static_cast<real_T>(lee_controller_B.pmin);
                  if (lee_controller_B.K13 == 0.0) {
                    lee_controller_B.V[lee_controller_B.idx + 1].re =
                      lee_controller_B.q_tmp / 1.4142135623730951;
                    lee_controller_B.V[lee_controller_B.idx + 1].im = 0.0;
                  } else if (lee_controller_B.q_tmp == 0.0) {
                    lee_controller_B.V[lee_controller_B.idx + 1].re = 0.0;
                    lee_controller_B.V[lee_controller_B.idx + 1].im =
                      lee_controller_B.K13 / 1.4142135623730951;
                  } else {
                    lee_controller_B.V[lee_controller_B.idx + 1].re =
                      lee_controller_B.q_tmp / 1.4142135623730951;
                    lee_controller_B.V[lee_controller_B.idx + 1].im =
                      lee_controller_B.K13 / 1.4142135623730951;
                  }

                  lee_controller_B.V[lee_controller_B.npad + 1].re =
                    lee_controller_B.V[lee_controller_B.idx + 1].re;
                  lee_controller_B.V[lee_controller_B.npad + 1].im =
                    -lee_controller_B.V[lee_controller_B.idx + 1].im;
                  lee_controller_B.q_tmp =
                    lee_controller_B.V[lee_controller_B.idx + 2].re;
                  lee_controller_B.K13 =
                    lee_controller_B.V[lee_controller_B.npad + 2].re *
                    static_cast<real_T>(lee_controller_B.pmin);
                  if (lee_controller_B.K13 == 0.0) {
                    lee_controller_B.V[lee_controller_B.idx + 2].re =
                      lee_controller_B.q_tmp / 1.4142135623730951;
                    lee_controller_B.V[lee_controller_B.idx + 2].im = 0.0;
                  } else if (lee_controller_B.q_tmp == 0.0) {
                    lee_controller_B.V[lee_controller_B.idx + 2].re = 0.0;
                    lee_controller_B.V[lee_controller_B.idx + 2].im =
                      lee_controller_B.K13 / 1.4142135623730951;
                  } else {
                    lee_controller_B.V[lee_controller_B.idx + 2].re =
                      lee_controller_B.q_tmp / 1.4142135623730951;
                    lee_controller_B.V[lee_controller_B.idx + 2].im =
                      lee_controller_B.K13 / 1.4142135623730951;
                  }

                  lee_controller_B.V[lee_controller_B.npad + 2].re =
                    lee_controller_B.V[lee_controller_B.idx + 2].re;
                  lee_controller_B.V[lee_controller_B.npad + 2].im =
                    -lee_controller_B.V[lee_controller_B.idx + 2].im;
                  lee_controller_B.q_tmp =
                    lee_controller_B.V[lee_controller_B.idx + 3].re;
                  lee_controller_B.K13 =
                    lee_controller_B.V[lee_controller_B.npad + 3].re *
                    static_cast<real_T>(lee_controller_B.pmin);
                  if (lee_controller_B.K13 == 0.0) {
                    lee_controller_B.V[lee_controller_B.idx + 3].re =
                      lee_controller_B.q_tmp / 1.4142135623730951;
                    lee_controller_B.V[lee_controller_B.idx + 3].im = 0.0;
                  } else if (lee_controller_B.q_tmp == 0.0) {
                    lee_controller_B.V[lee_controller_B.idx + 3].re = 0.0;
                    lee_controller_B.V[lee_controller_B.idx + 3].im =
                      lee_controller_B.K13 / 1.4142135623730951;
                  } else {
                    lee_controller_B.V[lee_controller_B.idx + 3].re =
                      lee_controller_B.q_tmp / 1.4142135623730951;
                    lee_controller_B.V[lee_controller_B.idx + 3].im =
                      lee_controller_B.K13 / 1.4142135623730951;
                  }

                  lee_controller_B.V[lee_controller_B.npad + 3].re =
                    lee_controller_B.V[lee_controller_B.idx + 3].re;
                  lee_controller_B.V[lee_controller_B.npad + 3].im =
                    -lee_controller_B.V[lee_controller_B.idx + 3].im;
                  lee_controller_B.pmax += 2;
                } else {
                  lee_controller_B.pmax++;
                }
              } else {
                lee_controller_B.pmax++;
              }
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);
        } else {
          lee_controller_eigStandard(lee_controller_B.A, lee_controller_B.V,
            lee_controller_B.D);
        }
      }
    }

    lee_controller_B.q[0] = lee_controller_B.D[0].re;
    lee_controller_B.q[1] = lee_controller_B.D[1].re;
    lee_controller_B.q[2] = lee_controller_B.D[2].re;
    lee_controller_B.q[3] = lee_controller_B.D[3].re;
    if (!rtIsNaN(lee_controller_B.D[0].re)) {
      lee_controller_B.idx = 1;
    } else {
      lee_controller_B.idx = 0;
      lee_controller_B.pmax = 2;
      exitg1 = false;
      while ((!exitg1) && (lee_controller_B.pmax < 5)) {
        if (!rtIsNaN(lee_controller_B.q[lee_controller_B.pmax - 1])) {
          lee_controller_B.idx = lee_controller_B.pmax;
          exitg1 = true;
        } else {
          lee_controller_B.pmax++;
        }
      }
    }

    if (lee_controller_B.idx == 0) {
      lee_controller_B.pmax = 0;
    } else {
      lee_controller_B.K12 = lee_controller_B.q[lee_controller_B.idx - 1];
      lee_controller_B.pmax = lee_controller_B.idx - 1;
      while (lee_controller_B.idx + 1 <= 4) {
        if (lee_controller_B.K12 < lee_controller_B.q[lee_controller_B.idx]) {
          lee_controller_B.K12 = lee_controller_B.q[lee_controller_B.idx];
          lee_controller_B.pmax = lee_controller_B.idx;
        }

        lee_controller_B.idx++;
      }
    }

    lee_controller_B.idx = lee_controller_B.pmax << 2;
    lee_controller_B.q[0] = lee_controller_B.V[lee_controller_B.idx + 3].re;
    lee_controller_B.q[1] = lee_controller_B.V[lee_controller_B.idx].re;
    lee_controller_B.q[2] = lee_controller_B.V[lee_controller_B.idx + 1].re;
    lee_controller_B.q[3] = lee_controller_B.V[lee_controller_B.idx + 2].re;
    if (lee_controller_B.q[0] < 0.0) {
      lee_controller_B.q[0] = -lee_controller_B.q[0];
      lee_controller_B.q[1] = -lee_controller_B.q[1];
      lee_controller_B.q[2] = -lee_controller_B.q[2];
      lee_controller_B.q[3] = -lee_controller_B.q[3];
    }

    // Saturate: '<S17>/Saturation9'
    if (lee_controller_B.rtb_q_drone_idx_0 >
        lee_controller_P.Saturation9_UpperSat_h) {
      lee_controller_B.rtb_q_drone_idx_0 =
        lee_controller_P.Saturation9_UpperSat_h;
    } else if (lee_controller_B.rtb_q_drone_idx_0 <
               lee_controller_P.Saturation9_LowerSat_h) {
      lee_controller_B.rtb_q_drone_idx_0 =
        lee_controller_P.Saturation9_LowerSat_h;
    }

    // End of Saturate: '<S17>/Saturation9'

    // MATLAB Function: '<S2>/att control' incorporates:
    //   DataTypeConversion: '<S42>/Cast To Double7'
    //   MATLABSystem: '<S42>/Read Parameter7'
    //   Product: '<S2>/Product'

    lee_controller_B.b3d[0] = lee_controller_B.ParamStep_lt *
      lee_controller_B.rtb_q_drone_idx_0 / 2.0;

    // Signum: '<S18>/Sign'
    if (lee_controller_B.ParamStep_m < 0.0F) {
      lee_controller_B.ParamStep_mj = -1.0F;
    } else if (lee_controller_B.ParamStep_m > 0.0F) {
      lee_controller_B.ParamStep_mj = 1.0F;
    } else {
      lee_controller_B.ParamStep_mj = 0.0F;
    }

    // End of Signum: '<S18>/Sign'

    // Sum: '<S18>/Sum' incorporates:
    //   Constant: '<S18>/Constant'
    //   Product: '<S18>/Product'

    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.ParamStep_m -
      lee_controller_B.ParamStep_mj * lee_controller_P.pitch_offset;

    // Saturate: '<S18>/Saturation9'
    if (lee_controller_B.rtb_q_drone_idx_0 >
        lee_controller_P.Saturation9_UpperSat_e) {
      lee_controller_B.rtb_q_drone_idx_0 =
        lee_controller_P.Saturation9_UpperSat_e;
    } else if (lee_controller_B.rtb_q_drone_idx_0 <
               lee_controller_P.Saturation9_LowerSat_f) {
      lee_controller_B.rtb_q_drone_idx_0 =
        lee_controller_P.Saturation9_LowerSat_f;
    }

    // End of Saturate: '<S18>/Saturation9'

    // MATLAB Function: '<S2>/att control' incorporates:
    //   Constant: '<S2>/des_yaw_from_RC'
    //   DataTypeConversion: '<S42>/Cast To Double8'
    //   MATLABSystem: '<S42>/Read Parameter8'
    //   Product: '<S2>/Product1'

    lee_controller_B.b3d[1] = lee_controller_B.ParamStep_o *
      lee_controller_B.rtb_q_drone_idx_0 / 2.0;
    lee_controller_B.b3d[2] = lee_controller_P.des_yaw_from_RC_Value / 2.0;
    lee_controller_B.K12 = cos(lee_controller_B.b3d[0]);
    lee_controller_B.K34 = sin(lee_controller_B.b3d[0]);
    lee_controller_B.tempR_tmp = cos(lee_controller_B.b3d[1]);
    lee_controller_B.q_tmp = sin(lee_controller_B.b3d[1]);
    lee_controller_B.K13 = cos(lee_controller_B.b3d[2]);
    lee_controller_B.K14 = sin(lee_controller_B.b3d[2]);
    lee_controller_B.K23 = lee_controller_B.K12 * lee_controller_B.tempR_tmp;
    lee_controller_B.K24 = lee_controller_B.K34 * lee_controller_B.q_tmp;
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.K23 *
      lee_controller_B.K13 - lee_controller_B.K24 * lee_controller_B.K14;
    lee_controller_B.q_tmp *= lee_controller_B.K12;
    lee_controller_B.K12 = lee_controller_B.K34 * lee_controller_B.tempR_tmp *
      lee_controller_B.K13 + lee_controller_B.q_tmp * lee_controller_B.K14;
    lee_controller_B.K34 = -lee_controller_B.K34 * lee_controller_B.tempR_tmp *
      lee_controller_B.K14 + lee_controller_B.q_tmp * lee_controller_B.K13;
    lee_controller_B.K24 = lee_controller_B.K23 * lee_controller_B.K14 +
      lee_controller_B.K24 * lee_controller_B.K13;
    lee_controller_B.K23 = ((lee_controller_B.K12 * lee_controller_B.q[1] +
      lee_controller_B.K34 * lee_controller_B.q[2]) + lee_controller_B.K24 *
      lee_controller_B.q[3]) + lee_controller_B.rtb_q_drone_idx_0 *
      lee_controller_B.q[0];
    lee_controller_B.K13 = (lee_controller_B.q[0] * lee_controller_B.K12 -
      lee_controller_B.rtb_q_drone_idx_0 * lee_controller_B.q[1]) +
      (lee_controller_B.K34 * -lee_controller_B.q[3] - -lee_controller_B.q[2] *
       lee_controller_B.K24);
    lee_controller_B.K14 = (lee_controller_B.q[0] * lee_controller_B.K34 -
      lee_controller_B.rtb_q_drone_idx_0 * lee_controller_B.q[2]) +
      (-lee_controller_B.q[1] * lee_controller_B.K24 - lee_controller_B.K12 *
       -lee_controller_B.q[3]);
    lee_controller_B.rtb_q_drone_idx_0 = (lee_controller_B.q[0] *
      lee_controller_B.K24 - lee_controller_B.rtb_q_drone_idx_0 *
      lee_controller_B.q[3]) + (lee_controller_B.K12 * -lee_controller_B.q[2] -
      -lee_controller_B.q[1] * lee_controller_B.K34);
    if (lee_controller_B.K23 < 0.0) {
      lee_controller_B.K12 = -1.0;
    } else if (lee_controller_B.K23 > 0.0) {
      lee_controller_B.K12 = 1.0;
    } else if (lee_controller_B.K23 == 0.0) {
      lee_controller_B.K12 = 0.0;
    } else {
      lee_controller_B.K12 = (rtNaN);
    }

    // MATLAB Function: '<S2>/rate control' incorporates:
    //   DataTypeConversion: '<S42>/Cast To Double11'
    //   DataTypeConversion: '<S42>/Cast To Double12'
    //   DataTypeConversion: '<S42>/Cast To Double13'
    //   DataTypeConversion: '<S42>/Cast To Double3'
    //   DataTypeConversion: '<S42>/Cast To Double4'
    //   DataTypeConversion: '<S42>/Cast To Double5'
    //   MATLAB Function: '<S2>/att control'
    //   MATLABSystem: '<S42>/Read Parameter11'
    //   MATLABSystem: '<S42>/Read Parameter12'
    //   MATLABSystem: '<S42>/Read Parameter13'
    //   MATLABSystem: '<S42>/Read Parameter3'
    //   MATLABSystem: '<S42>/Read Parameter4'
    //   MATLABSystem: '<S42>/Read Parameter5'
    //   Math: '<S3>/Transpose'
    //   SignalConversion generated from: '<S21>/ SFunction '

    memset(&lee_controller_B.tempR[0], 0, 9U * sizeof(real_T));
    lee_controller_B.tempR[0] = lee_controller_B.ParamStep_h2;
    lee_controller_B.tempR[4] = lee_controller_B.ParamStep_me;
    lee_controller_B.tempR[8] = lee_controller_B.ParamStep_mc;
    lee_controller_B.c[0] = lee_controller_B.ParamStep_g;
    lee_controller_B.c[1] = lee_controller_B.ParamStep_co;
    lee_controller_B.c[2] = lee_controller_B.ParamStep_o3;
    memset(&lee_controller_B.catArgs[0], 0, 9U * sizeof(real_T));
    for (lee_controller_B.pmax = 0; lee_controller_B.pmax < 3;
         lee_controller_B.pmax++) {
      lee_controller_B.catArgs[lee_controller_B.pmax + 3 * lee_controller_B.pmax]
        = lee_controller_B.c[lee_controller_B.pmax];
      lee_controller_B.c[lee_controller_B.pmax] =
        (lee_controller_B.tempR[lee_controller_B.pmax + 3] *
         lee_controller_B.TmpSignalConversionAtSFunct[1] +
         lee_controller_B.tempR[lee_controller_B.pmax] *
         lee_controller_B.TmpSignalConversionAtSFunct[0]) +
        lee_controller_B.tempR[lee_controller_B.pmax + 6] *
        lee_controller_B.TmpSignalConversionAtSFunct[2];
      lee_controller_B.b3d[lee_controller_B.pmax] =
        (lee_controller_B.R_mes[lee_controller_B.pmax + 3] *
         lee_controller_B.K12 * lee_controller_B.K14 +
         lee_controller_B.R_mes[lee_controller_B.pmax] * lee_controller_B.K12 *
         lee_controller_B.K13) + lee_controller_B.R_mes[lee_controller_B.pmax +
        6] * lee_controller_B.K12 * lee_controller_B.rtb_q_drone_idx_0;
    }

    // Signum: '<S19>/Sign'
    if (lee_controller_B.ParamStep_lm < 0.0F) {
      lee_controller_B.ParamStep_o3 = -1.0F;
    } else if (lee_controller_B.ParamStep_lm > 0.0F) {
      lee_controller_B.ParamStep_o3 = 1.0F;
    } else {
      lee_controller_B.ParamStep_o3 = 0.0F;
    }

    // Sum: '<S19>/Sum' incorporates:
    //   Constant: '<S19>/Constant'
    //   Product: '<S19>/Product'
    //   Signum: '<S19>/Sign'

    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.ParamStep_lm -
      static_cast<real_T>(static_cast<int32_T>(lee_controller_B.ParamStep_o3)) *
      lee_controller_P.yaw_offset;

    // SignalConversion generated from: '<S21>/ SFunction ' incorporates:
    //   DataTypeConversion: '<S3>/Cast To Double7'
    //   MATLAB Function: '<S2>/rate control'

    lee_controller_B.K12 = lee_controller_B.b3d[0] - lee_controller_B.In1_f.xyz
      [0];
    lee_controller_B.K13 = lee_controller_B.b3d[1] - lee_controller_B.In1_f.xyz
      [1];

    // Saturate: '<S19>/Saturation9'
    if (lee_controller_B.rtb_q_drone_idx_0 >
        lee_controller_P.Saturation9_UpperSat) {
      lee_controller_B.rtb_q_drone_idx_0 = lee_controller_P.Saturation9_UpperSat;
    } else if (lee_controller_B.rtb_q_drone_idx_0 <
               lee_controller_P.Saturation9_LowerSat) {
      lee_controller_B.rtb_q_drone_idx_0 = lee_controller_P.Saturation9_LowerSat;
    }

    // End of Saturate: '<S19>/Saturation9'

    // SignalConversion generated from: '<S21>/ SFunction ' incorporates:
    //   DataTypeConversion: '<S3>/Cast To Double7'
    //   DataTypeConversion: '<S42>/Cast To Double9'
    //   MATLAB Function: '<S2>/rate control'
    //   MATLABSystem: '<S42>/Read Parameter9'
    //   Math: '<S3>/Transpose'
    //   Product: '<S2>/Product3'

    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.ParamStep_i *
      lee_controller_B.rtb_q_drone_idx_0 - lee_controller_B.In1_f.xyz[2];

    // MATLAB Function: '<S2>/rate control' incorporates:
    //   DataTypeConversion: '<S3>/Cast To Double7'

    lee_controller_B.TmpSignalConversionAtSFunct[0] =
      lee_controller_B.In1_f.xyz[1] * lee_controller_B.c[2] -
      lee_controller_B.c[1] * lee_controller_B.In1_f.xyz[2];
    lee_controller_B.TmpSignalConversionAtSFunct[1] = lee_controller_B.c[0] *
      lee_controller_B.In1_f.xyz[2] - lee_controller_B.In1_f.xyz[0] *
      lee_controller_B.c[2];
    lee_controller_B.TmpSignalConversionAtSFunct[2] =
      lee_controller_B.In1_f.xyz[0] * lee_controller_B.c[1] -
      lee_controller_B.c[0] * lee_controller_B.In1_f.xyz[1];
    for (lee_controller_B.idx = 0; lee_controller_B.idx < 3;
         lee_controller_B.idx++) {
      lee_controller_B.b3d[lee_controller_B.idx] =
        ((lee_controller_B.catArgs[lee_controller_B.idx + 3] *
          lee_controller_B.K13 + lee_controller_B.catArgs[lee_controller_B.idx] *
          lee_controller_B.K12) + lee_controller_B.catArgs[lee_controller_B.idx
         + 6] * lee_controller_B.rtb_q_drone_idx_0) +
        lee_controller_B.TmpSignalConversionAtSFunct[lee_controller_B.idx];
    }

    // Sum: '<S16>/Sum' incorporates:
    //   Constant: '<S16>/Constant'
    //   DataTypeConversion: '<S16>/Data Type Conversion3'
    //   DataTypeConversion: '<S9>/Cast To Double2'
    //   Fcn: '<S16>/Fcn6'

    lee_controller_B.rtb_q_drone_idx_0 = (static_cast<real32_T>
      (lee_controller_B.In1_c.values[2]) - 1000.0F) / 1000.0F -
      lee_controller_P.thrust_offset;

    // Saturate: '<S16>/Saturation10'
    if (lee_controller_B.rtb_q_drone_idx_0 >
        lee_controller_P.Saturation10_UpperSat) {
      lee_controller_B.rtb_q_drone_idx_0 =
        lee_controller_P.Saturation10_UpperSat;
    } else if (lee_controller_B.rtb_q_drone_idx_0 <
               lee_controller_P.Saturation10_LowerSat) {
      lee_controller_B.rtb_q_drone_idx_0 =
        lee_controller_P.Saturation10_LowerSat;
    }

    // End of Saturate: '<S16>/Saturation10'

    // MATLAB Function: '<S2>/rpm allocation' incorporates:
    //   DataTypeConversion: '<S42>/Cast To Double10'
    //   MATLABSystem: '<S42>/Read Parameter10'
    //   Product: '<S2>/Product2'

    lee_controller_rpmallocation(lee_controller_B.ParamStep_o2 *
      lee_controller_B.rtb_q_drone_idx_0, lee_controller_B.b3d,
      lee_controller_B.inv_A, lee_controller_B.rpm_j);
  }

  // End of Logic: '<Root>/AND1'
  // End of Outputs for SubSystem: '<Root>/Enabled Subsystem1'

  // MATLAB Function: '<Root>/mode sw'
  if (lee_controller_B.pos_flag) {
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.rpm[0];
  } else if (lee_controller_B.carry) {
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.rpm_j[0];
  } else {
    lee_controller_B.rtb_q_drone_idx_0 = 0.0;
  }

  // MATLAB Function: '<S1>/MATLAB Function4'
  lee_controller_B.K13 = rt_roundd_snf(lee_controller_B.rtb_q_drone_idx_0 *
    2000.0 / 8800.0 * 100.0 + 1000.0);
  if (lee_controller_B.K13 < 65536.0) {
    if (lee_controller_B.K13 >= 0.0) {
      lee_controller_B.status = static_cast<uint16_T>(lee_controller_B.K13);
    } else {
      lee_controller_B.status = 0U;
    }
  } else {
    lee_controller_B.status = MAX_uint16_T;
  }

  // MATLAB Function: '<Root>/mode sw'
  if (lee_controller_B.pos_flag) {
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.rpm[1];
  } else if (lee_controller_B.carry) {
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.rpm_j[1];
  } else {
    lee_controller_B.rtb_q_drone_idx_0 = 0.0;
  }

  // MATLAB Function: '<S1>/MATLAB Function4'
  lee_controller_B.K13 = rt_roundd_snf(lee_controller_B.rtb_q_drone_idx_0 *
    2000.0 / 8800.0 * 100.0 + 1000.0);
  if (lee_controller_B.K13 < 65536.0) {
    if (lee_controller_B.K13 >= 0.0) {
      lee_controller_B.u2 = static_cast<uint16_T>(lee_controller_B.K13);
    } else {
      lee_controller_B.u2 = 0U;
    }
  } else {
    lee_controller_B.u2 = MAX_uint16_T;
  }

  // MATLAB Function: '<Root>/mode sw'
  if (lee_controller_B.pos_flag) {
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.rpm[2];
  } else if (lee_controller_B.carry) {
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.rpm_j[2];
  } else {
    lee_controller_B.rtb_q_drone_idx_0 = 0.0;
  }

  // MATLAB Function: '<S1>/MATLAB Function4'
  lee_controller_B.K13 = rt_roundd_snf(lee_controller_B.rtb_q_drone_idx_0 *
    2000.0 / 8800.0 * 100.0 + 1000.0);
  if (lee_controller_B.K13 < 65536.0) {
    if (lee_controller_B.K13 >= 0.0) {
      lee_controller_B.u1 = static_cast<uint16_T>(lee_controller_B.K13);
    } else {
      lee_controller_B.u1 = 0U;
    }
  } else {
    lee_controller_B.u1 = MAX_uint16_T;
  }

  // MATLAB Function: '<Root>/mode sw'
  if (lee_controller_B.pos_flag) {
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.rpm[3];
  } else if (lee_controller_B.carry) {
    lee_controller_B.rtb_q_drone_idx_0 = lee_controller_B.rpm_j[3];
  } else {
    lee_controller_B.rtb_q_drone_idx_0 = 0.0;
  }

  // MATLAB Function: '<S1>/MATLAB Function4'
  lee_controller_B.K13 = rt_roundd_snf(lee_controller_B.rtb_q_drone_idx_0 *
    2000.0 / 8800.0 * 100.0 + 1000.0);
  if (lee_controller_B.K13 < 65536.0) {
    if (lee_controller_B.K13 >= 0.0) {
      lee_controller_B.u = static_cast<uint16_T>(lee_controller_B.K13);
    } else {
      lee_controller_B.u = 0U;
    }
  } else {
    lee_controller_B.u = MAX_uint16_T;
  }

  // MATLABSystem: '<S1>/PX4 PWM Output'
  for (lee_controller_B.idx = 0; lee_controller_B.idx < 8; lee_controller_B.idx
       ++) {
    lee_controller_B.pwmValue[lee_controller_B.idx] = 0U;
  }

  // Saturate: '<S1>/Saturation pwm'
  if (lee_controller_B.status > lee_controller_P.Saturationpwm_UpperSat) {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[0] = lee_controller_P.Saturationpwm_UpperSat;
  } else if (lee_controller_B.status < lee_controller_P.Saturationpwm_LowerSat)
  {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[0] = lee_controller_P.Saturationpwm_LowerSat;
  } else {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[0] = lee_controller_B.status;
  }

  if (lee_controller_B.u2 > lee_controller_P.Saturationpwm_UpperSat) {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[1] = lee_controller_P.Saturationpwm_UpperSat;
  } else if (lee_controller_B.u2 < lee_controller_P.Saturationpwm_LowerSat) {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[1] = lee_controller_P.Saturationpwm_LowerSat;
  } else {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[1] = lee_controller_B.u2;
  }

  if (lee_controller_B.u1 > lee_controller_P.Saturationpwm_UpperSat) {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[2] = lee_controller_P.Saturationpwm_UpperSat;
  } else if (lee_controller_B.u1 < lee_controller_P.Saturationpwm_LowerSat) {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[2] = lee_controller_P.Saturationpwm_LowerSat;
  } else {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[2] = lee_controller_B.u1;
  }

  if (lee_controller_B.u > lee_controller_P.Saturationpwm_UpperSat) {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[3] = lee_controller_P.Saturationpwm_UpperSat;
  } else if (lee_controller_B.u < lee_controller_P.Saturationpwm_LowerSat) {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[3] = lee_controller_P.Saturationpwm_LowerSat;
  } else {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[3] = lee_controller_B.u;
  }

  // End of Saturate: '<S1>/Saturation pwm'

  // MATLAB Function: '<S1>/MATLAB Function1'
  if (lee_controller_B.In1_c.values[5] >= 1620) {
    lee_controller_B.idx = 1;
  } else if ((lee_controller_B.In1_c.values[5] < 1620) &&
             (lee_controller_B.In1_c.values[5] > 1420)) {
    lee_controller_B.idx = 0;
  } else {
    lee_controller_B.idx = -1;
  }

  // Saturate: '<S1>/Saturation pwm1' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'

  lee_controller_B.status = static_cast<uint16_T>(lee_controller_B.idx * 50 +
    1520);
  if (lee_controller_B.status > lee_controller_P.Saturationpwm1_UpperSat) {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[7] = lee_controller_P.Saturationpwm1_UpperSat;
  } else if (lee_controller_B.status < lee_controller_P.Saturationpwm1_LowerSat)
  {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[7] = lee_controller_P.Saturationpwm1_LowerSat;
  } else {
    // MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_B.pwmValue[7] = lee_controller_B.status;
  }

  // End of Saturate: '<S1>/Saturation pwm1'

  // MATLABSystem: '<S1>/PX4 PWM Output' incorporates:
  //   Logic: '<S1>/NOT'

  if (lee_controller_B.NOT) {
    if (!lee_controller_DW.obj_co.isArmed) {
      lee_controller_DW.obj_co.isArmed = true;
      lee_controller_B.status = pwm_arm(&lee_controller_DW.obj_co.pwmDevHandler,
        &lee_controller_DW.obj_co.armAdvertiseObj);
      lee_controller_DW.obj_co.errorStatus = static_cast<uint16_T>
        (lee_controller_DW.obj_co.errorStatus | lee_controller_B.status);
    }

    lee_controller_B.status = pwm_setServo
      (&lee_controller_DW.obj_co.pwmDevHandler,
       lee_controller_DW.obj_co.servoCount, lee_controller_DW.obj_co.channelMask,
       &lee_controller_B.pwmValue[0], lee_controller_DW.obj_co.isMain,
       &lee_controller_DW.obj_co.actuatorAdvertiseObj);
    lee_controller_DW.obj_co.errorStatus = static_cast<uint16_T>
      (lee_controller_DW.obj_co.errorStatus | lee_controller_B.status);
  } else {
    lee_controller_B.status = pwm_disarm(&lee_controller_DW.obj_co.pwmDevHandler,
      &lee_controller_DW.obj_co.armAdvertiseObj);
    lee_controller_DW.obj_co.errorStatus = static_cast<uint16_T>
      (lee_controller_DW.obj_co.errorStatus | lee_controller_B.status);
    lee_controller_DW.obj_co.isArmed = false;
    lee_controller_B.status = pwm_resetServo
      (&lee_controller_DW.obj_co.pwmDevHandler,
       lee_controller_DW.obj_co.servoCount, lee_controller_DW.obj_co.channelMask,
       lee_controller_DW.obj_co.isMain,
       &lee_controller_DW.obj_co.actuatorAdvertiseObj);
    lee_controller_DW.obj_co.errorStatus = static_cast<uint16_T>
      (lee_controller_DW.obj_co.errorStatus | lee_controller_B.status);
  }

  if (lee_controller_DW.obj_co.isMain) {
    lee_controller_B.status = pwm_forceFailsafe
      (&lee_controller_DW.obj_co.pwmDevHandler, !lee_controller_B.NOT);
    lee_controller_DW.obj_co.errorStatus = static_cast<uint16_T>
      (lee_controller_DW.obj_co.errorStatus | lee_controller_B.status);
  }

  // DataTypeConversion: '<Root>/Cast To Single1'
  lee_controller_B.K13 = floor(lee_controller_B.time);
  if (rtIsNaN(lee_controller_B.K13) || rtIsInf(lee_controller_B.K13)) {
    lee_controller_B.K13 = 0.0;
  } else {
    lee_controller_B.K13 = fmod(lee_controller_B.K13, 1.8446744073709552E+19);
  }

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   DataTypeConversion: '<Root>/Cast To Double'
  //   DataTypeConversion: '<Root>/Cast To Double1'
  //   DataTypeConversion: '<Root>/Cast To Double2'
  //   DataTypeConversion: '<Root>/Cast To Single1'
  //   DataTypeConversion: '<Root>/Cast To Single6'
  //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'

  lee_controller_B.BusAssignment_k.timestamp = lee_controller_B.K13 < 0.0 ?
    static_cast<uint64_T>(-static_cast<int64_T>(static_cast<uint64_T>
    (-lee_controller_B.K13))) : static_cast<uint64_T>(lee_controller_B.K13);
  lee_controller_B.BusAssignment_k.z = static_cast<real32_T>
    (lee_controller_DW.DiscreteTimeIntegrator1_DSTATE);
  lee_controller_B.BusAssignment_k.dz = static_cast<real32_T>
    (lee_controller_DW.DiscreteTimeIntegrator_DSTATE);
  lee_controller_B.BusAssignment_k.ddz = static_cast<real32_T>
    (lee_controller_B.Divide);
  lee_controller_B.BusAssignment_k.f_ext = static_cast<real32_T>
    (lee_controller_B.f_ext);

  // MATLABSystem: '<S7>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment'

  uORB_write_step(lee_controller_DW.obj_bv.orbMetadataObj,
                  &lee_controller_DW.obj_bv.orbAdvertiseObj,
                  &lee_controller_B.BusAssignment_k);

  // MATLABSystem: '<S42>/Read Parameter41'
  if (lee_controller_DW.obj_o.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_o.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  MW_Param_Step(lee_controller_DW.obj_o.MW_PARAMHANDLE,
                lee_controller_B.ParamDataType, &lee_controller_B.ParamStep_lt);

  // End of MATLABSystem: '<S42>/Read Parameter41'

  // MATLABSystem: '<S42>/Read Parameter42'
  if (lee_controller_DW.obj_l.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_l.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  MW_Param_Step(lee_controller_DW.obj_l.MW_PARAMHANDLE,
                lee_controller_B.ParamDataType, &lee_controller_B.ParamStep_lt);

  // End of MATLABSystem: '<S42>/Read Parameter42'

  // MATLABSystem: '<S42>/Read Parameter43'
  if (lee_controller_DW.obj_n.SampleTime != lee_controller_P.dt) {
    lee_controller_DW.obj_n.SampleTime = lee_controller_P.dt;
  }

  lee_controller_B.ParamDataType = MW_SINGLE;
  MW_Param_Step(lee_controller_DW.obj_n.MW_PARAMHANDLE,
                lee_controller_B.ParamDataType, &lee_controller_B.ParamStep_lt);

  // End of MATLABSystem: '<S42>/Read Parameter43'

  // Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator1' incorporates:
  //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator'

  lee_controller_DW.DiscreteTimeIntegrator1_DSTATE +=
    lee_controller_P.DiscreteTimeIntegrator1_gainval *
    lee_controller_DW.DiscreteTimeIntegrator_DSTATE;

  // Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  lee_controller_DW.DiscreteTimeIntegrator_DSTATE +=
    lee_controller_P.DiscreteTimeIntegrator_gainval * lee_controller_B.Divide;

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.004, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  lee_controller_M->Timing.clockTick0++;
}

// Model initialize function
void lee_controller_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    px4_internal_block_ParameterU_T *obj;
    int32_T i;
    char_T ParameterNameStr_1[7];
    char_T ParameterNameStr_2[6];
    char_T ParameterNameStr[5];
    char_T ParameterNameStr_0[4];
    boolean_T rtb_arm;
    static const char_T tmp[12] = { 'L', 'E', 'E', '_', 'K', 'P', '_', 'X', '_',
      'P', 'O', 'S' };

    static const char_T tmp_0[12] = { 'L', 'E', 'E', '_', 'K', 'P', '_', 'Y',
      '_', 'P', 'O', 'S' };

    static const char_T tmp_1[12] = { 'L', 'E', 'E', '_', 'K', 'P', '_', 'Z',
      '_', 'P', 'O', 'S' };

    static const char_T tmp_2[12] = { 'L', 'E', 'E', '_', 'K', 'D', '_', 'X',
      '_', 'P', 'O', 'S' };

    static const char_T tmp_3[12] = { 'L', 'E', 'E', '_', 'K', 'D', '_', 'Y',
      '_', 'P', 'O', 'S' };

    static const char_T tmp_4[12] = { 'L', 'E', 'E', '_', 'K', 'D', '_', 'Z',
      '_', 'P', 'O', 'S' };

    static const char_T tmp_5[12] = { 'L', 'E', 'E', '_', 'K', 'I', '_', 'X',
      '_', 'P', 'O', 'S' };

    static const char_T tmp_6[12] = { 'L', 'E', 'E', '_', 'K', 'I', '_', 'Y',
      '_', 'P', 'O', 'S' };

    static const char_T tmp_7[12] = { 'L', 'E', 'E', '_', 'K', 'I', '_', 'Z',
      '_', 'P', 'O', 'S' };

    static const char_T tmp_8[11] = { 'L', 'E', 'E', '_', 'K', 'P', '_', 'X',
      '_', 'O', 'R' };

    static const char_T tmp_9[11] = { 'L', 'E', 'E', '_', 'K', 'P', '_', 'Y',
      '_', 'O', 'R' };

    static const char_T tmp_a[11] = { 'L', 'E', 'E', '_', 'K', 'P', '_', 'Z',
      '_', 'O', 'R' };

    static const char_T tmp_b[11] = { 'L', 'E', 'E', '_', 'K', 'D', '_', 'X',
      '_', 'O', 'R' };

    static const char_T tmp_c[11] = { 'L', 'E', 'E', '_', 'K', 'D', '_', 'Y',
      '_', 'O', 'R' };

    static const char_T tmp_d[11] = { 'L', 'E', 'E', '_', 'K', 'D', '_', 'Z',
      '_', 'O', 'R' };

    static const char_T tmp_e[11] = { 'L', 'E', 'E', '_', 'K', 'I', '_', 'X',
      '_', 'O', 'R' };

    static const char_T tmp_f[11] = { 'L', 'E', 'E', '_', 'K', 'I', '_', 'Y',
      '_', 'O', 'R' };

    static const char_T tmp_g[11] = { 'L', 'E', 'E', '_', 'K', 'I', '_', 'Z',
      '_', 'O', 'R' };

    static const char_T tmp_h[6] = { 'L', 'E', 'E', '_', 'C', '1' };

    static const char_T tmp_i[6] = { 'L', 'E', 'E', '_', 'C', '2' };

    static const char_T tmp_j[8] = { 'L', 'E', 'E', '_', 'J', '_', 'X', 'X' };

    static const char_T tmp_k[8] = { 'L', 'E', 'E', '_', 'J', '_', 'Y', 'Y' };

    static const char_T tmp_l[8] = { 'L', 'E', 'E', '_', 'J', '_', 'Z', 'Z' };

    static const char_T tmp_m[8] = { 'L', 'E', 'E', '_', 'M', 'A', 'S', 'S' };

    static const char_T tmp_n[15] = { 'L', 'E', 'E', '_', 'S', 'A', 'T', '_',
      'I', 'N', 'T', '_', 'A', 'C', 'T' };

    static const char_T tmp_o[6] = { 'L', 'E', 'E', '_', 'K', 'F' };

    static const char_T tmp_p[6] = { 'L', 'E', 'E', '_', 'K', 'M' };

    static const char_T tmp_q[9] = { 'L', 'E', 'E', '_', 'L', '_', 'A', 'R', 'M'
    };

    static const char_T tmp_r[12] = { 'L', 'E', 'E', '_', 'R', 'O', 'L', 'L',
      '_', 'M', 'A', 'X' };

    static const char_T tmp_s[13] = { 'L', 'E', 'E', '_', 'P', 'I', 'T', 'C',
      'H', '_', 'M', 'A', 'X' };

    static const char_T tmp_t[14] = { 'L', 'E', 'E', '_', 'T', 'H', 'R', 'U',
      'S', 'T', '_', 'M', 'A', 'X' };

    static const char_T tmp_u[16] = { 'L', 'E', 'E', '_', 'Y', 'A', 'W', '_',
      'R', 'A', 'T', 'E', '_', 'M', 'A', 'X' };

    static const char_T tmp_v[12] = { 'L', 'E', 'E', '_', 'K', 'P', '_', 'X',
      '_', 'A', 'T', 'T' };

    static const char_T tmp_w[12] = { 'L', 'E', 'E', '_', 'K', 'P', '_', 'Y',
      '_', 'A', 'T', 'T' };

    static const char_T tmp_x[12] = { 'L', 'E', 'E', '_', 'K', 'P', '_', 'Z',
      '_', 'A', 'T', 'T' };

    static const char_T tmp_y[12] = { 'L', 'E', 'E', '_', 'K', 'D', '_', 'X',
      '_', 'A', 'T', 'T' };

    static const char_T tmp_z[12] = { 'L', 'E', 'E', '_', 'K', 'D', '_', 'Y',
      '_', 'A', 'T', 'T' };

    static const char_T tmp_10[12] = { 'L', 'E', 'E', '_', 'K', 'D', '_', 'Z',
      '_', 'A', 'T', 'T' };

    static const char_T tmp_11[5] = { 'N', 'E', 'D', '_', 'Z' };

    static const char_T tmp_12[6] = { 'N', 'E', 'D', '_', 'D', 'Z' };

    static const char_T tmp_13[7] = { 'N', 'E', 'D', '_', 'D', 'D', 'Z' };

    lee_controller_PrevZCX.Subsystem1_Trig_ZCE = POS_ZCSIG;

    // InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator1' 
    lee_controller_DW.DiscreteTimeIntegrator1_DSTATE =
      lee_controller_P.DiscreteTimeIntegrator1_IC;

    // InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' 
    lee_controller_DW.DiscreteTimeIntegrator_DSTATE =
      lee_controller_P.DiscreteTimeIntegrator_IC;

    // SystemInitialize for Enabled SubSystem: '<S25>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S28>/Out1' incorporates:
    //   Inport: '<S28>/In1'

    lee_controller_B.In1_h = lee_controller_P.Out1_Y0_m;

    // End of SystemInitialize for SubSystem: '<S25>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<S26>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S29>/Out1' incorporates:
    //   Inport: '<S29>/In1'

    lee_controller_B.In1_f = lee_controller_P.Out1_Y0_o;

    // End of SystemInitialize for SubSystem: '<S26>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<S24>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S27>/Out1' incorporates:
    //   Inport: '<S27>/In1'

    lee_controller_B.In1 = lee_controller_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S24>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<S43>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S46>/Out1' incorporates:
    //   Inport: '<S46>/In1'

    lee_controller_B.In1_m = lee_controller_P.Out1_Y0_p;

    // End of SystemInitialize for SubSystem: '<S43>/Enabled Subsystem'

    // SystemInitialize for Triggered SubSystem: '<Root>/Subsystem1'
    // SystemInitialize for Gain: '<S10>/Gain1' incorporates:
    //   Outport: '<S10>/kg'

    lee_controller_B.Gain1 = lee_controller_P.kg_Y0;

    // End of SystemInitialize for SubSystem: '<Root>/Subsystem1'

    // SystemInitialize for Enabled SubSystem: '<S47>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S48>/Out1' incorporates:
    //   Inport: '<S48>/In1'

    lee_controller_B.In1_c = lee_controller_P.Out1_Y0_f;

    // End of SystemInitialize for SubSystem: '<S47>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<S51>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S53>/Out1' incorporates:
    //   Inport: '<S53>/In1'

    lee_controller_B.In1_ho = lee_controller_P.Out1_Y0_d;

    // End of SystemInitialize for SubSystem: '<S51>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<S52>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S54>/Out1' incorporates:
    //   Inport: '<S54>/In1'

    lee_controller_B.In1_cj = lee_controller_P.Out1_Y0_j;

    // End of SystemInitialize for SubSystem: '<S52>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<Root>/LEE_CONTROLLER'
    // Start for MATLABSystem: '<S35>/SinkBlock' incorporates:
    //   BusAssignment: '<S5>/Bus Assignment'

    lee_controller_DW.obj_cg.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_cg.isSetupComplete = false;
    lee_controller_DW.obj_cg.isInitialized = 1;
    lee_controller_DW.obj_cg.orbMetadataObj = ORB_ID(linear_err);
    uORB_write_initialize(lee_controller_DW.obj_cg.orbMetadataObj,
                          &lee_controller_DW.obj_cg.orbAdvertiseObj,
                          &lee_controller_B.BusAssignment_p, 1);
    lee_controller_DW.obj_cg.isSetupComplete = true;

    // Start for MATLABSystem: '<S37>/SinkBlock' incorporates:
    //   BusAssignment: '<S5>/Bus Assignment2'

    lee_controller_DW.obj_cs.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_cs.isSetupComplete = false;
    lee_controller_DW.obj_cs.isInitialized = 1;
    lee_controller_DW.obj_cs.orbMetadataObj = ORB_ID(act_wrench);
    uORB_write_initialize(lee_controller_DW.obj_cs.orbMetadataObj,
                          &lee_controller_DW.obj_cs.orbAdvertiseObj,
                          &lee_controller_B.BusAssignment2_g, 1);
    lee_controller_DW.obj_cs.isSetupComplete = true;

    // Start for MATLABSystem: '<S36>/SinkBlock' incorporates:
    //   BusAssignment: '<S5>/Bus Assignment1'

    lee_controller_DW.obj_lu.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_lu.isSetupComplete = false;
    lee_controller_DW.obj_lu.isInitialized = 1;
    lee_controller_DW.obj_lu.orbMetadataObj = ORB_ID(ang_err);
    uORB_write_initialize(lee_controller_DW.obj_lu.orbMetadataObj,
                          &lee_controller_DW.obj_lu.orbAdvertiseObj,
                          &lee_controller_B.BusAssignment1_p, 1);
    lee_controller_DW.obj_lu.isSetupComplete = true;

    // SystemInitialize for Outport: '<S5>/rpm'
    lee_controller_B.rpm[0] = lee_controller_P.rpm_Y0_l;

    // End of SystemInitialize for SubSystem: '<Root>/LEE_CONTROLLER'

    // SystemInitialize for Enabled SubSystem: '<Root>/Enabled Subsystem1'
    // SystemInitialize for Outport: '<S2>/rpm'
    lee_controller_B.rpm_j[0] = lee_controller_P.rpm_Y0;

    // End of SystemInitialize for SubSystem: '<Root>/Enabled Subsystem1'

    // SystemInitialize for Enabled SubSystem: '<Root>/LEE_CONTROLLER'
    // SystemInitialize for Outport: '<S5>/rpm'
    lee_controller_B.rpm[1] = lee_controller_P.rpm_Y0_l;

    // End of SystemInitialize for SubSystem: '<Root>/LEE_CONTROLLER'

    // SystemInitialize for Enabled SubSystem: '<Root>/Enabled Subsystem1'
    // SystemInitialize for Outport: '<S2>/rpm'
    lee_controller_B.rpm_j[1] = lee_controller_P.rpm_Y0;

    // End of SystemInitialize for SubSystem: '<Root>/Enabled Subsystem1'

    // SystemInitialize for Enabled SubSystem: '<Root>/LEE_CONTROLLER'
    // SystemInitialize for Outport: '<S5>/rpm'
    lee_controller_B.rpm[2] = lee_controller_P.rpm_Y0_l;

    // End of SystemInitialize for SubSystem: '<Root>/LEE_CONTROLLER'

    // SystemInitialize for Enabled SubSystem: '<Root>/Enabled Subsystem1'
    // SystemInitialize for Outport: '<S2>/rpm'
    lee_controller_B.rpm_j[2] = lee_controller_P.rpm_Y0;

    // End of SystemInitialize for SubSystem: '<Root>/Enabled Subsystem1'

    // SystemInitialize for Enabled SubSystem: '<Root>/LEE_CONTROLLER'
    // SystemInitialize for Outport: '<S5>/rpm'
    lee_controller_B.rpm[3] = lee_controller_P.rpm_Y0_l;

    // End of SystemInitialize for SubSystem: '<Root>/LEE_CONTROLLER'

    // SystemInitialize for Enabled SubSystem: '<Root>/Enabled Subsystem1'
    // SystemInitialize for Outport: '<S2>/rpm'
    lee_controller_B.rpm_j[3] = lee_controller_P.rpm_Y0;

    // End of SystemInitialize for SubSystem: '<Root>/Enabled Subsystem1'

    // Start for MATLABSystem: '<S25>/SourceBlock'
    lee_controller_DW.obj_d.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_d.isSetupComplete = false;
    lee_controller_DW.obj_d.isInitialized = 1;
    lee_controller_DW.obj_d.orbMetadataObj = ORB_ID(vehicle_attitude);
    uORB_read_initialize(lee_controller_DW.obj_d.orbMetadataObj,
                         &lee_controller_DW.obj_d.eventStructObj);
    lee_controller_DW.obj_d.isSetupComplete = true;

    // Start for MATLABSystem: '<S26>/SourceBlock'
    lee_controller_DW.obj_l5.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_l5.isSetupComplete = false;
    lee_controller_DW.obj_l5.isInitialized = 1;
    lee_controller_DW.obj_l5.orbMetadataObj = ORB_ID(vehicle_angular_velocity);
    uORB_read_initialize(lee_controller_DW.obj_l5.orbMetadataObj,
                         &lee_controller_DW.obj_l5.eventStructObj);
    lee_controller_DW.obj_l5.isSetupComplete = true;

    // Start for MATLABSystem: '<S24>/SourceBlock'
    lee_controller_DW.obj_awb.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_awb.isSetupComplete = false;
    lee_controller_DW.obj_awb.isInitialized = 1;
    lee_controller_DW.obj_awb.orbMetadataObj = ORB_ID(vehicle_local_position);
    uORB_read_initialize(lee_controller_DW.obj_awb.orbMetadataObj,
                         &lee_controller_DW.obj_awb.eventStructObj);
    lee_controller_DW.obj_awb.isSetupComplete = true;

    // Start for MATLABSystem: '<S43>/SourceBlock'
    lee_controller_DW.obj_kw.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_kw.isSetupComplete = false;
    lee_controller_DW.obj_kw.isInitialized = 1;
    lee_controller_DW.obj_kw.orbMetadataObj = ORB_ID(traj_setpoint);
    uORB_read_initialize(lee_controller_DW.obj_kw.orbMetadataObj,
                         &lee_controller_DW.obj_kw.eventStructObj);
    lee_controller_DW.obj_kw.isSetupComplete = true;

    // Start for MATLABSystem: '<Root>/Serial Receive1'
    lee_controller_DW.obj_cc.isInitialized = 0;
    lee_controller_DW.obj_cc.SCIDriverObj.MW_SCIHANDLE = NULL;
    lee_controller_DW.obj_cc.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_cc.SampleTime = lee_controller_P.dt;
    lee_controll_SystemCore_setup_g(&lee_controller_DW.obj_cc);

    // Start for MATLABSystem: '<S42>/Read Parameter39'
    lee_controller_DW.obj_ma.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_ma.isInitialized = 0;
    lee_controller_DW.obj_ma.SampleTime = -1.0;
    lee_controller_DW.obj_ma.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_ma.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_ma;
    lee_controller_DW.obj_ma.isSetupComplete = false;
    lee_controller_DW.obj_ma.isInitialized = 1;
    ParameterNameStr[0] = 'K';
    ParameterNameStr[1] = 'D';
    ParameterNameStr[2] = '_';
    ParameterNameStr[3] = 'A';
    ParameterNameStr[4] = '\x00';
    if (lee_controller_DW.obj_ma.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_ma.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr[0], true,
      lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_ma.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter39'

    // Start for MATLABSystem: '<S42>/Read Parameter38'
    lee_controller_DW.obj_lj.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_lj.isInitialized = 0;
    lee_controller_DW.obj_lj.SampleTime = -1.0;
    lee_controller_DW.obj_lj.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_lj.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_lj;
    lee_controller_DW.obj_lj.isSetupComplete = false;
    lee_controller_DW.obj_lj.isInitialized = 1;
    ParameterNameStr[0] = 'K';
    ParameterNameStr[1] = 'P';
    ParameterNameStr[2] = '_';
    ParameterNameStr[3] = 'A';
    ParameterNameStr[4] = '\x00';
    if (lee_controller_DW.obj_lj.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_lj.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr[0], true,
      lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_lj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter38'

    // Start for MATLABSystem: '<S42>/Read Parameter40'
    lee_controller_DW.obj_f.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_f.isInitialized = 0;
    lee_controller_DW.obj_f.SampleTime = -1.0;
    lee_controller_DW.obj_f.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_f.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_f;
    lee_controller_DW.obj_f.isSetupComplete = false;
    lee_controller_DW.obj_f.isInitialized = 1;
    ParameterNameStr_0[0] = 'M';
    ParameterNameStr_0[1] = '_';
    ParameterNameStr_0[2] = 'A';
    ParameterNameStr_0[3] = '\x00';
    if (lee_controller_DW.obj_f.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_f.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr_0[0], true,
      lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_f.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter40'

    // Start for MATLABSystem: '<S42>/Read Parameter14'
    lee_controller_DW.obj_hh.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_hh.isInitialized = 0;
    lee_controller_DW.obj_hh.SampleTime = -1.0;
    lee_controller_DW.obj_hh.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_hh.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_hh;
    lee_controller_DW.obj_hh.isSetupComplete = false;
    lee_controller_DW.obj_hh.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_hh.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_hh.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_hh.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter14'

    // Start for MATLABSystem: '<S42>/Read Parameter15'
    lee_controller_DW.obj_pv.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_pv.isInitialized = 0;
    lee_controller_DW.obj_pv.SampleTime = -1.0;
    lee_controller_DW.obj_pv.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_pv.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_pv;
    lee_controller_DW.obj_pv.isSetupComplete = false;
    lee_controller_DW.obj_pv.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_0[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_pv.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_pv.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_pv.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter15'

    // Start for MATLABSystem: '<S42>/Read Parameter16'
    lee_controller_DW.obj_j.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_j.isInitialized = 0;
    lee_controller_DW.obj_j.SampleTime = -1.0;
    lee_controller_DW.obj_j.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_j.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_j;
    lee_controller_DW.obj_j.isSetupComplete = false;
    lee_controller_DW.obj_j.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_1[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_j.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_j.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_j.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter16'

    // Start for MATLABSystem: '<S42>/Read Parameter17'
    lee_controller_DW.obj_fy.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_fy.isInitialized = 0;
    lee_controller_DW.obj_fy.SampleTime = -1.0;
    lee_controller_DW.obj_fy.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_fy.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_fy;
    lee_controller_DW.obj_fy.isSetupComplete = false;
    lee_controller_DW.obj_fy.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_2[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_fy.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_fy.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_fy.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter17'

    // Start for MATLABSystem: '<S42>/Read Parameter18'
    lee_controller_DW.obj_n3.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_n3.isInitialized = 0;
    lee_controller_DW.obj_n3.SampleTime = -1.0;
    lee_controller_DW.obj_n3.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_n3.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_n3;
    lee_controller_DW.obj_n3.isSetupComplete = false;
    lee_controller_DW.obj_n3.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_3[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_n3.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_n3.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_n3.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter18'

    // Start for MATLABSystem: '<S42>/Read Parameter19'
    lee_controller_DW.obj_nu.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_nu.isInitialized = 0;
    lee_controller_DW.obj_nu.SampleTime = -1.0;
    lee_controller_DW.obj_nu.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_nu.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_nu;
    lee_controller_DW.obj_nu.isSetupComplete = false;
    lee_controller_DW.obj_nu.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_4[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_nu.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_nu.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_nu.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter19'

    // Start for MATLABSystem: '<S42>/Read Parameter20'
    lee_controller_DW.obj_hl.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_hl.isInitialized = 0;
    lee_controller_DW.obj_hl.SampleTime = -1.0;
    lee_controller_DW.obj_hl.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_hl.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_hl;
    lee_controller_DW.obj_hl.isSetupComplete = false;
    lee_controller_DW.obj_hl.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_5[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_hl.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_hl.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_hl.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter20'

    // Start for MATLABSystem: '<S42>/Read Parameter21'
    lee_controller_DW.obj_i.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_i.isInitialized = 0;
    lee_controller_DW.obj_i.SampleTime = -1.0;
    lee_controller_DW.obj_i.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_i.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_i;
    lee_controller_DW.obj_i.isSetupComplete = false;
    lee_controller_DW.obj_i.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_6[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_i.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_i.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_i.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter21'

    // Start for MATLABSystem: '<S42>/Read Parameter22'
    lee_controller_DW.obj_k3.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_k3.isInitialized = 0;
    lee_controller_DW.obj_k3.SampleTime = -1.0;
    lee_controller_DW.obj_k3.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_k3.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_k3;
    lee_controller_DW.obj_k3.isSetupComplete = false;
    lee_controller_DW.obj_k3.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_7[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_k3.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_k3.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_k3.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter22'

    // Start for MATLABSystem: '<S42>/Read Parameter23'
    lee_controller_DW.obj_ni.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_ni.isInitialized = 0;
    lee_controller_DW.obj_ni.SampleTime = -1.0;
    lee_controller_DW.obj_ni.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_ni.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_ni;
    lee_controller_DW.obj_ni.isSetupComplete = false;
    lee_controller_DW.obj_ni.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      lee_controller_B.ParameterNameStr_g[i] = tmp_8[i];
    }

    lee_controller_B.ParameterNameStr_g[11] = '\x00';
    if (lee_controller_DW.obj_ni.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_ni.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_g[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_ni.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter23'

    // Start for MATLABSystem: '<S42>/Read Parameter24'
    lee_controller_DW.obj_hi.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_hi.isInitialized = 0;
    lee_controller_DW.obj_hi.SampleTime = -1.0;
    lee_controller_DW.obj_hi.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_hi.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_hi;
    lee_controller_DW.obj_hi.isSetupComplete = false;
    lee_controller_DW.obj_hi.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      lee_controller_B.ParameterNameStr_g[i] = tmp_9[i];
    }

    lee_controller_B.ParameterNameStr_g[11] = '\x00';
    if (lee_controller_DW.obj_hi.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_hi.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_g[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_hi.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter24'

    // Start for MATLABSystem: '<S42>/Read Parameter25'
    lee_controller_DW.obj_o1.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_o1.isInitialized = 0;
    lee_controller_DW.obj_o1.SampleTime = -1.0;
    lee_controller_DW.obj_o1.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_o1.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_o1;
    lee_controller_DW.obj_o1.isSetupComplete = false;
    lee_controller_DW.obj_o1.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      lee_controller_B.ParameterNameStr_g[i] = tmp_a[i];
    }

    lee_controller_B.ParameterNameStr_g[11] = '\x00';
    if (lee_controller_DW.obj_o1.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_o1.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_g[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_o1.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter25'

    // Start for MATLABSystem: '<S42>/Read Parameter26'
    lee_controller_DW.obj_og.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_og.isInitialized = 0;
    lee_controller_DW.obj_og.SampleTime = -1.0;
    lee_controller_DW.obj_og.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_og.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_og;
    lee_controller_DW.obj_og.isSetupComplete = false;
    lee_controller_DW.obj_og.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      lee_controller_B.ParameterNameStr_g[i] = tmp_b[i];
    }

    lee_controller_B.ParameterNameStr_g[11] = '\x00';
    if (lee_controller_DW.obj_og.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_og.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_g[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_og.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter26'

    // Start for MATLABSystem: '<S42>/Read Parameter27'
    lee_controller_DW.obj_pq.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_pq.isInitialized = 0;
    lee_controller_DW.obj_pq.SampleTime = -1.0;
    lee_controller_DW.obj_pq.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_pq.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_pq;
    lee_controller_DW.obj_pq.isSetupComplete = false;
    lee_controller_DW.obj_pq.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      lee_controller_B.ParameterNameStr_g[i] = tmp_c[i];
    }

    lee_controller_B.ParameterNameStr_g[11] = '\x00';
    if (lee_controller_DW.obj_pq.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_pq.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_g[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_pq.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter27'

    // Start for MATLABSystem: '<S42>/Read Parameter28'
    lee_controller_DW.obj_ne.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_ne.isInitialized = 0;
    lee_controller_DW.obj_ne.SampleTime = -1.0;
    lee_controller_DW.obj_ne.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_ne.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_ne;
    lee_controller_DW.obj_ne.isSetupComplete = false;
    lee_controller_DW.obj_ne.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      lee_controller_B.ParameterNameStr_g[i] = tmp_d[i];
    }

    lee_controller_B.ParameterNameStr_g[11] = '\x00';
    if (lee_controller_DW.obj_ne.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_ne.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_g[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_ne.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter28'

    // Start for MATLABSystem: '<S42>/Read Parameter29'
    lee_controller_DW.obj_lb.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_lb.isInitialized = 0;
    lee_controller_DW.obj_lb.SampleTime = -1.0;
    lee_controller_DW.obj_lb.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_lb.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_lb;
    lee_controller_DW.obj_lb.isSetupComplete = false;
    lee_controller_DW.obj_lb.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      lee_controller_B.ParameterNameStr_g[i] = tmp_e[i];
    }

    lee_controller_B.ParameterNameStr_g[11] = '\x00';
    if (lee_controller_DW.obj_lb.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_lb.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_g[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_lb.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter29'

    // Start for MATLABSystem: '<S42>/Read Parameter30'
    lee_controller_DW.obj_pd.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_pd.isInitialized = 0;
    lee_controller_DW.obj_pd.SampleTime = -1.0;
    lee_controller_DW.obj_pd.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_pd.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_pd;
    lee_controller_DW.obj_pd.isSetupComplete = false;
    lee_controller_DW.obj_pd.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      lee_controller_B.ParameterNameStr_g[i] = tmp_f[i];
    }

    lee_controller_B.ParameterNameStr_g[11] = '\x00';
    if (lee_controller_DW.obj_pd.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_pd.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_g[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_pd.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter30'

    // Start for MATLABSystem: '<S42>/Read Parameter31'
    lee_controller_DW.obj_el.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_el.isInitialized = 0;
    lee_controller_DW.obj_el.SampleTime = -1.0;
    lee_controller_DW.obj_el.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_el.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_el;
    lee_controller_DW.obj_el.isSetupComplete = false;
    lee_controller_DW.obj_el.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      lee_controller_B.ParameterNameStr_g[i] = tmp_g[i];
    }

    lee_controller_B.ParameterNameStr_g[11] = '\x00';
    if (lee_controller_DW.obj_el.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_el.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_g[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_el.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter31'

    // Start for MATLABSystem: '<S42>/Read Parameter32'
    lee_controller_DW.obj_ng.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_ng.isInitialized = 0;
    lee_controller_DW.obj_ng.SampleTime = -1.0;
    lee_controller_DW.obj_ng.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_ng.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_ng;
    lee_controller_DW.obj_ng.isSetupComplete = false;
    lee_controller_DW.obj_ng.isInitialized = 1;
    for (i = 0; i < 6; i++) {
      ParameterNameStr_1[i] = tmp_h[i];
    }

    ParameterNameStr_1[6] = '\x00';
    if (lee_controller_DW.obj_ng.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_ng.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr_1[0], true,
      lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_ng.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter32'

    // Start for MATLABSystem: '<S42>/Read Parameter33'
    lee_controller_DW.obj_e.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_e.isInitialized = 0;
    lee_controller_DW.obj_e.SampleTime = -1.0;
    lee_controller_DW.obj_e.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_e.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_e;
    lee_controller_DW.obj_e.isSetupComplete = false;
    lee_controller_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 6; i++) {
      ParameterNameStr_1[i] = tmp_i[i];
    }

    ParameterNameStr_1[6] = '\x00';
    if (lee_controller_DW.obj_e.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_e.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr_1[0], true,
      lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_e.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter33'

    // Start for MATLABSystem: '<S42>/Read Parameter11'
    lee_controller_DW.obj_bh.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_bh.isInitialized = 0;
    lee_controller_DW.obj_bh.SampleTime = -1.0;
    lee_controller_DW.obj_bh.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_bh.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_bh;
    lee_controller_DW.obj_bh.isSetupComplete = false;
    lee_controller_DW.obj_bh.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      lee_controller_B.ParameterNameStr_o[i] = tmp_j[i];
    }

    lee_controller_B.ParameterNameStr_o[8] = '\x00';
    if (lee_controller_DW.obj_bh.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_bh.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_o[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_bh.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter11'

    // Start for MATLABSystem: '<S42>/Read Parameter12'
    lee_controller_DW.obj_aw.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_aw.isInitialized = 0;
    lee_controller_DW.obj_aw.SampleTime = -1.0;
    lee_controller_DW.obj_aw.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_aw.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_aw;
    lee_controller_DW.obj_aw.isSetupComplete = false;
    lee_controller_DW.obj_aw.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      lee_controller_B.ParameterNameStr_o[i] = tmp_k[i];
    }

    lee_controller_B.ParameterNameStr_o[8] = '\x00';
    if (lee_controller_DW.obj_aw.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_aw.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_o[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_aw.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter12'

    // Start for MATLABSystem: '<S42>/Read Parameter13'
    lee_controller_DW.obj_js.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_js.isInitialized = 0;
    lee_controller_DW.obj_js.SampleTime = -1.0;
    lee_controller_DW.obj_js.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_js.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_js;
    lee_controller_DW.obj_js.isSetupComplete = false;
    lee_controller_DW.obj_js.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      lee_controller_B.ParameterNameStr_o[i] = tmp_l[i];
    }

    lee_controller_B.ParameterNameStr_o[8] = '\x00';
    if (lee_controller_DW.obj_js.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_js.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_o[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_js.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter13'

    // Start for MATLABSystem: '<S42>/Read Parameter6'
    lee_controller_DW.obj_p.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_p.isInitialized = 0;
    lee_controller_DW.obj_p.SampleTime = -1.0;
    lee_controller_DW.obj_p.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_p.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_p;
    lee_controller_DW.obj_p.isSetupComplete = false;
    lee_controller_DW.obj_p.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      lee_controller_B.ParameterNameStr_o[i] = tmp_m[i];
    }

    lee_controller_B.ParameterNameStr_o[8] = '\x00';
    if (lee_controller_DW.obj_p.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_p.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_o[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_p.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter6'

    // Start for MATLABSystem: '<S42>/Read Parameter37'
    lee_controller_DW.obj_mt.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_mt.isInitialized = 0;
    lee_controller_DW.obj_mt.SampleTime = -1.0;
    lee_controller_DW.obj_mt.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_mt.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_mt;
    lee_controller_DW.obj_mt.isSetupComplete = false;
    lee_controller_DW.obj_mt.isInitialized = 1;
    for (i = 0; i < 15; i++) {
      lee_controller_B.ParameterNameStr_m[i] = tmp_n[i];
    }

    lee_controller_B.ParameterNameStr_m[15] = '\x00';
    if (lee_controller_DW.obj_mt.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_mt.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_m[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_mt.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter37'

    // Start for MATLABSystem: '<S42>/Read Parameter34'
    lee_controller_DW.obj_h.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_h.isInitialized = 0;
    lee_controller_DW.obj_h.SampleTime = -1.0;
    lee_controller_DW.obj_h.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_h.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_h;
    lee_controller_DW.obj_h.isSetupComplete = false;
    lee_controller_DW.obj_h.isInitialized = 1;
    for (i = 0; i < 6; i++) {
      ParameterNameStr_1[i] = tmp_o[i];
    }

    ParameterNameStr_1[6] = '\x00';
    if (lee_controller_DW.obj_h.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_h.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr_1[0], true,
      lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_h.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter34'

    // Start for MATLABSystem: '<S42>/Read Parameter35'
    lee_controller_DW.obj_k4.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_k4.isInitialized = 0;
    lee_controller_DW.obj_k4.SampleTime = -1.0;
    lee_controller_DW.obj_k4.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_k4.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_k4;
    lee_controller_DW.obj_k4.isSetupComplete = false;
    lee_controller_DW.obj_k4.isInitialized = 1;
    for (i = 0; i < 6; i++) {
      ParameterNameStr_1[i] = tmp_p[i];
    }

    ParameterNameStr_1[6] = '\x00';
    if (lee_controller_DW.obj_k4.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_k4.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr_1[0], true,
      lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_k4.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter35'

    // Start for MATLABSystem: '<S42>/Read Parameter36'
    lee_controller_DW.obj_c.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_c.isInitialized = 0;
    lee_controller_DW.obj_c.SampleTime = -1.0;
    lee_controller_DW.obj_c.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_c.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_c;
    lee_controller_DW.obj_c.isSetupComplete = false;
    lee_controller_DW.obj_c.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      lee_controller_B.ParameterNameStr_lx[i] = tmp_q[i];
    }

    lee_controller_B.ParameterNameStr_lx[9] = '\x00';
    if (lee_controller_DW.obj_c.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_c.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_lx[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_c.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter36'

    // Start for MATLABSystem: '<S47>/SourceBlock'
    lee_controller_DW.obj_fp.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_fp.isSetupComplete = false;
    lee_controller_DW.obj_fp.isInitialized = 1;
    lee_controller_DW.obj_fp.orbMetadataObj = ORB_ID(input_rc);
    uORB_read_initialize(lee_controller_DW.obj_fp.orbMetadataObj,
                         &lee_controller_DW.obj_fp.eventStructObj);
    lee_controller_DW.obj_fp.isSetupComplete = true;

    // Start for MATLABSystem: '<S51>/SourceBlock'
    lee_controller_DW.obj_oh.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_oh.isSetupComplete = false;
    lee_controller_DW.obj_oh.isInitialized = 1;
    lee_controller_DW.obj_oh.orbMetadataObj = ORB_ID(actuator_armed);
    uORB_read_initialize(lee_controller_DW.obj_oh.orbMetadataObj,
                         &lee_controller_DW.obj_oh.eventStructObj);
    lee_controller_DW.obj_oh.isSetupComplete = true;

    // Start for MATLABSystem: '<S52>/SourceBlock'
    lee_controller_DW.obj_mfw.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_mfw.isSetupComplete = false;
    lee_controller_DW.obj_mfw.isInitialized = 1;
    lee_controller_DW.obj_mfw.orbMetadataObj = ORB_ID(commander_state);
    uORB_read_initialize(lee_controller_DW.obj_mfw.orbMetadataObj,
                         &lee_controller_DW.obj_mfw.eventStructObj);
    lee_controller_DW.obj_mfw.isSetupComplete = true;

    // Start for MATLABSystem: '<S42>/Read Parameter7'
    lee_controller_DW.obj_m.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_m.isInitialized = 0;
    lee_controller_DW.obj_m.SampleTime = -1.0;
    lee_controller_DW.obj_m.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_m.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_m;
    lee_controller_DW.obj_m.isSetupComplete = false;
    lee_controller_DW.obj_m.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_r[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_m.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_m.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_m.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter7'

    // Start for MATLABSystem: '<S42>/Read Parameter8'
    lee_controller_DW.obj_b.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_b.isInitialized = 0;
    lee_controller_DW.obj_b.SampleTime = -1.0;
    lee_controller_DW.obj_b.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_b.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_b;
    lee_controller_DW.obj_b.isSetupComplete = false;
    lee_controller_DW.obj_b.isInitialized = 1;
    for (i = 0; i < 13; i++) {
      lee_controller_B.ParameterNameStr_j[i] = tmp_s[i];
    }

    lee_controller_B.ParameterNameStr_j[13] = '\x00';
    if (lee_controller_DW.obj_b.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_b.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_j[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_b.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter8'

    // Start for MATLABSystem: '<S42>/Read Parameter10'
    lee_controller_DW.obj_cm.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_cm.isInitialized = 0;
    lee_controller_DW.obj_cm.SampleTime = -1.0;
    lee_controller_DW.obj_cm.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_cm.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_cm;
    lee_controller_DW.obj_cm.isSetupComplete = false;
    lee_controller_DW.obj_cm.isInitialized = 1;
    for (i = 0; i < 14; i++) {
      lee_controller_B.ParameterNameStr_l[i] = tmp_t[i];
    }

    lee_controller_B.ParameterNameStr_l[14] = '\x00';
    if (lee_controller_DW.obj_cm.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_cm.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_l[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_cm.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter10'

    // Start for MATLABSystem: '<S42>/Read Parameter9'
    lee_controller_DW.obj.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj.isInitialized = 0;
    lee_controller_DW.obj.SampleTime = -1.0;
    lee_controller_DW.obj.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj;
    lee_controller_DW.obj.isSetupComplete = false;
    lee_controller_DW.obj.isInitialized = 1;
    for (i = 0; i < 16; i++) {
      lee_controller_B.ParameterNameStr[i] = tmp_u[i];
    }

    lee_controller_B.ParameterNameStr[16] = '\x00';
    if (lee_controller_DW.obj.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter9'

    // Start for MATLABSystem: '<S42>/Read Parameter'
    lee_controller_DW.obj_mf.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_mf.isInitialized = 0;
    lee_controller_DW.obj_mf.SampleTime = -1.0;
    lee_controller_DW.obj_mf.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_mf.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_mf;
    lee_controller_DW.obj_mf.isSetupComplete = false;
    lee_controller_DW.obj_mf.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_v[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_mf.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_mf.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_mf.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter'

    // Start for MATLABSystem: '<S42>/Read Parameter1'
    lee_controller_DW.obj_kp.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_kp.isInitialized = 0;
    lee_controller_DW.obj_kp.SampleTime = -1.0;
    lee_controller_DW.obj_kp.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_kp.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_kp;
    lee_controller_DW.obj_kp.isSetupComplete = false;
    lee_controller_DW.obj_kp.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_w[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_kp.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_kp.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_kp.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter1'

    // Start for MATLABSystem: '<S42>/Read Parameter2'
    lee_controller_DW.obj_ef.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_ef.isInitialized = 0;
    lee_controller_DW.obj_ef.SampleTime = -1.0;
    lee_controller_DW.obj_ef.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_ef.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_ef;
    lee_controller_DW.obj_ef.isSetupComplete = false;
    lee_controller_DW.obj_ef.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_x[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_ef.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_ef.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_ef.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter2'

    // Start for MATLABSystem: '<S42>/Read Parameter3'
    lee_controller_DW.obj_ph.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_ph.isInitialized = 0;
    lee_controller_DW.obj_ph.SampleTime = -1.0;
    lee_controller_DW.obj_ph.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_ph.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_ph;
    lee_controller_DW.obj_ph.isSetupComplete = false;
    lee_controller_DW.obj_ph.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_y[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_ph.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_ph.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_ph.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter3'

    // Start for MATLABSystem: '<S42>/Read Parameter4'
    lee_controller_DW.obj_k.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_k.isInitialized = 0;
    lee_controller_DW.obj_k.SampleTime = -1.0;
    lee_controller_DW.obj_k.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_k.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_k;
    lee_controller_DW.obj_k.isSetupComplete = false;
    lee_controller_DW.obj_k.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_z[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_k.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_k.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_k.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter4'

    // Start for MATLABSystem: '<S42>/Read Parameter5'
    lee_controller_DW.obj_a.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_a.isInitialized = 0;
    lee_controller_DW.obj_a.SampleTime = -1.0;
    lee_controller_DW.obj_a.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_a.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_a;
    lee_controller_DW.obj_a.isSetupComplete = false;
    lee_controller_DW.obj_a.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      lee_controller_B.ParameterNameStr_d[i] = tmp_10[i];
    }

    lee_controller_B.ParameterNameStr_d[12] = '\x00';
    if (lee_controller_DW.obj_a.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_a.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_d[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_a.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter5'

    // Start for MATLABSystem: '<S1>/PX4 PWM Output'
    lee_controller_DW.obj_co.errorStatus = 0U;
    lee_controller_DW.obj_co.isInitialized = 0;
    lee_controller_DW.obj_co.matlabCodegenIsDeleted = false;
    lee_controller_SystemCore_setup(&lee_controller_DW.obj_co, rtb_arm, rtb_arm);

    // Start for MATLABSystem: '<S7>/SinkBlock' incorporates:
    //   BusAssignment: '<Root>/Bus Assignment'

    lee_controller_DW.obj_bv.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_bv.isSetupComplete = false;
    lee_controller_DW.obj_bv.isInitialized = 1;
    lee_controller_DW.obj_bv.orbMetadataObj = ORB_ID(admittance);
    uORB_write_initialize(lee_controller_DW.obj_bv.orbMetadataObj,
                          &lee_controller_DW.obj_bv.orbAdvertiseObj,
                          &lee_controller_B.BusAssignment_k_g, 1);
    lee_controller_DW.obj_bv.isSetupComplete = true;

    // Start for MATLABSystem: '<S42>/Read Parameter41'
    lee_controller_DW.obj_o.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_o.isInitialized = 0;
    lee_controller_DW.obj_o.SampleTime = -1.0;
    lee_controller_DW.obj_o.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_o.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_o;
    lee_controller_DW.obj_o.isSetupComplete = false;
    lee_controller_DW.obj_o.isInitialized = 1;
    for (i = 0; i < 5; i++) {
      ParameterNameStr_2[i] = tmp_11[i];
    }

    ParameterNameStr_2[5] = '\x00';
    if (lee_controller_DW.obj_o.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_o.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr_2[0], true,
      lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_o.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter41'

    // Start for MATLABSystem: '<S42>/Read Parameter42'
    lee_controller_DW.obj_l.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_l.isInitialized = 0;
    lee_controller_DW.obj_l.SampleTime = -1.0;
    lee_controller_DW.obj_l.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_l.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_l;
    lee_controller_DW.obj_l.isSetupComplete = false;
    lee_controller_DW.obj_l.isInitialized = 1;
    for (i = 0; i < 6; i++) {
      ParameterNameStr_1[i] = tmp_12[i];
    }

    ParameterNameStr_1[6] = '\x00';
    if (lee_controller_DW.obj_l.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_l.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr_1[0], true,
      lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_l.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter42'

    // Start for MATLABSystem: '<S42>/Read Parameter43'
    lee_controller_DW.obj_n.matlabCodegenIsDeleted = true;
    lee_controller_DW.obj_n.isInitialized = 0;
    lee_controller_DW.obj_n.SampleTime = -1.0;
    lee_controller_DW.obj_n.matlabCodegenIsDeleted = false;
    lee_controller_DW.obj_n.SampleTime = lee_controller_P.dt;
    obj = &lee_controller_DW.obj_n;
    lee_controller_DW.obj_n.isSetupComplete = false;
    lee_controller_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 7; i++) {
      lee_controller_B.ParameterNameStr_b[i] = tmp_13[i];
    }

    lee_controller_B.ParameterNameStr_b[7] = '\x00';
    if (lee_controller_DW.obj_n.SampleTime == -1.0) {
      lee_controller_B.sts = 0.2;
    } else {
      lee_controller_B.sts = lee_controller_DW.obj_n.SampleTime;
    }

    obj->MW_PARAMHANDLE = MW_Init_Param(&lee_controller_B.ParameterNameStr_b[0],
      true, lee_controller_B.sts * 1000.0);
    lee_controller_DW.obj_n.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S42>/Read Parameter43'
  }
}

// Model terminate function
void lee_controller_terminate(void)
{
  // Terminate for MATLABSystem: '<S25>/SourceBlock'
  if (!lee_controller_DW.obj_d.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_d.isInitialized == 1) &&
        lee_controller_DW.obj_d.isSetupComplete) {
      uORB_read_terminate(&lee_controller_DW.obj_d.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S25>/SourceBlock'

  // Terminate for MATLABSystem: '<S26>/SourceBlock'
  if (!lee_controller_DW.obj_l5.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_l5.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_l5.isInitialized == 1) &&
        lee_controller_DW.obj_l5.isSetupComplete) {
      uORB_read_terminate(&lee_controller_DW.obj_l5.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S26>/SourceBlock'

  // Terminate for MATLABSystem: '<S24>/SourceBlock'
  if (!lee_controller_DW.obj_awb.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_awb.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_awb.isInitialized == 1) &&
        lee_controller_DW.obj_awb.isSetupComplete) {
      uORB_read_terminate(&lee_controller_DW.obj_awb.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S24>/SourceBlock'

  // Terminate for MATLABSystem: '<S43>/SourceBlock'
  if (!lee_controller_DW.obj_kw.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_kw.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_kw.isInitialized == 1) &&
        lee_controller_DW.obj_kw.isSetupComplete) {
      uORB_read_terminate(&lee_controller_DW.obj_kw.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S43>/SourceBlock'

  // Terminate for MATLABSystem: '<Root>/Serial Receive1'
  if (!lee_controller_DW.obj_cc.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_cc.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_cc.isInitialized == 1) &&
        lee_controller_DW.obj_cc.isSetupComplete) {
      MW_SCI_Close(lee_controller_DW.obj_cc.SCIDriverObj.MW_SCIHANDLE);
    }
  }

  // End of Terminate for MATLABSystem: '<Root>/Serial Receive1'

  // Terminate for MATLABSystem: '<S42>/Read Parameter39'
  if (!lee_controller_DW.obj_ma.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_ma.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter39'

  // Terminate for MATLABSystem: '<S42>/Read Parameter38'
  if (!lee_controller_DW.obj_lj.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_lj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter38'

  // Terminate for MATLABSystem: '<S42>/Read Parameter40'
  if (!lee_controller_DW.obj_f.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_f.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter40'

  // Terminate for MATLABSystem: '<S42>/Read Parameter14'
  if (!lee_controller_DW.obj_hh.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_hh.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter14'

  // Terminate for MATLABSystem: '<S42>/Read Parameter15'
  if (!lee_controller_DW.obj_pv.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_pv.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter15'

  // Terminate for MATLABSystem: '<S42>/Read Parameter16'
  if (!lee_controller_DW.obj_j.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_j.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter16'

  // Terminate for MATLABSystem: '<S42>/Read Parameter17'
  if (!lee_controller_DW.obj_fy.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_fy.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter17'

  // Terminate for MATLABSystem: '<S42>/Read Parameter18'
  if (!lee_controller_DW.obj_n3.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_n3.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter18'

  // Terminate for MATLABSystem: '<S42>/Read Parameter19'
  if (!lee_controller_DW.obj_nu.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_nu.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter19'

  // Terminate for MATLABSystem: '<S42>/Read Parameter20'
  if (!lee_controller_DW.obj_hl.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_hl.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter20'

  // Terminate for MATLABSystem: '<S42>/Read Parameter21'
  if (!lee_controller_DW.obj_i.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_i.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter21'

  // Terminate for MATLABSystem: '<S42>/Read Parameter22'
  if (!lee_controller_DW.obj_k3.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_k3.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter22'

  // Terminate for MATLABSystem: '<S42>/Read Parameter23'
  if (!lee_controller_DW.obj_ni.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_ni.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter23'

  // Terminate for MATLABSystem: '<S42>/Read Parameter24'
  if (!lee_controller_DW.obj_hi.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_hi.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter24'

  // Terminate for MATLABSystem: '<S42>/Read Parameter25'
  if (!lee_controller_DW.obj_o1.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_o1.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter25'

  // Terminate for MATLABSystem: '<S42>/Read Parameter26'
  if (!lee_controller_DW.obj_og.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_og.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter26'

  // Terminate for MATLABSystem: '<S42>/Read Parameter27'
  if (!lee_controller_DW.obj_pq.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_pq.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter27'

  // Terminate for MATLABSystem: '<S42>/Read Parameter28'
  if (!lee_controller_DW.obj_ne.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_ne.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter28'

  // Terminate for MATLABSystem: '<S42>/Read Parameter29'
  if (!lee_controller_DW.obj_lb.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_lb.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter29'

  // Terminate for MATLABSystem: '<S42>/Read Parameter30'
  if (!lee_controller_DW.obj_pd.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_pd.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter30'

  // Terminate for MATLABSystem: '<S42>/Read Parameter31'
  if (!lee_controller_DW.obj_el.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_el.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter31'

  // Terminate for MATLABSystem: '<S42>/Read Parameter32'
  if (!lee_controller_DW.obj_ng.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_ng.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter32'

  // Terminate for MATLABSystem: '<S42>/Read Parameter33'
  if (!lee_controller_DW.obj_e.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter33'

  // Terminate for MATLABSystem: '<S42>/Read Parameter11'
  if (!lee_controller_DW.obj_bh.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_bh.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter11'

  // Terminate for MATLABSystem: '<S42>/Read Parameter12'
  if (!lee_controller_DW.obj_aw.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_aw.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter12'

  // Terminate for MATLABSystem: '<S42>/Read Parameter13'
  if (!lee_controller_DW.obj_js.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_js.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter13'

  // Terminate for MATLABSystem: '<S42>/Read Parameter6'
  if (!lee_controller_DW.obj_p.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_p.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter6'

  // Terminate for MATLABSystem: '<S42>/Read Parameter37'
  if (!lee_controller_DW.obj_mt.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_mt.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter37'

  // Terminate for MATLABSystem: '<S42>/Read Parameter34'
  if (!lee_controller_DW.obj_h.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_h.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter34'

  // Terminate for MATLABSystem: '<S42>/Read Parameter35'
  if (!lee_controller_DW.obj_k4.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_k4.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter35'

  // Terminate for MATLABSystem: '<S42>/Read Parameter36'
  if (!lee_controller_DW.obj_c.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_c.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter36'

  // Terminate for MATLABSystem: '<S47>/SourceBlock'
  if (!lee_controller_DW.obj_fp.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_fp.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_fp.isInitialized == 1) &&
        lee_controller_DW.obj_fp.isSetupComplete) {
      uORB_read_terminate(&lee_controller_DW.obj_fp.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S47>/SourceBlock'

  // Terminate for MATLABSystem: '<S51>/SourceBlock'
  if (!lee_controller_DW.obj_oh.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_oh.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_oh.isInitialized == 1) &&
        lee_controller_DW.obj_oh.isSetupComplete) {
      uORB_read_terminate(&lee_controller_DW.obj_oh.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S51>/SourceBlock'

  // Terminate for MATLABSystem: '<S52>/SourceBlock'
  if (!lee_controller_DW.obj_mfw.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_mfw.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_mfw.isInitialized == 1) &&
        lee_controller_DW.obj_mfw.isSetupComplete) {
      uORB_read_terminate(&lee_controller_DW.obj_mfw.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S52>/SourceBlock'

  // Terminate for Enabled SubSystem: '<Root>/LEE_CONTROLLER'
  // Terminate for MATLABSystem: '<S35>/SinkBlock'
  if (!lee_controller_DW.obj_cg.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_cg.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_cg.isInitialized == 1) &&
        lee_controller_DW.obj_cg.isSetupComplete) {
      uORB_write_terminate(&lee_controller_DW.obj_cg.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S35>/SinkBlock'

  // Terminate for MATLABSystem: '<S37>/SinkBlock'
  if (!lee_controller_DW.obj_cs.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_cs.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_cs.isInitialized == 1) &&
        lee_controller_DW.obj_cs.isSetupComplete) {
      uORB_write_terminate(&lee_controller_DW.obj_cs.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S37>/SinkBlock'

  // Terminate for MATLABSystem: '<S36>/SinkBlock'
  if (!lee_controller_DW.obj_lu.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_lu.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_lu.isInitialized == 1) &&
        lee_controller_DW.obj_lu.isSetupComplete) {
      uORB_write_terminate(&lee_controller_DW.obj_lu.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S36>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/LEE_CONTROLLER'

  // Terminate for MATLABSystem: '<S42>/Read Parameter7'
  if (!lee_controller_DW.obj_m.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_m.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter7'

  // Terminate for MATLABSystem: '<S42>/Read Parameter8'
  if (!lee_controller_DW.obj_b.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_b.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter8'

  // Terminate for MATLABSystem: '<S42>/Read Parameter10'
  if (!lee_controller_DW.obj_cm.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_cm.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter10'

  // Terminate for MATLABSystem: '<S42>/Read Parameter9'
  if (!lee_controller_DW.obj.matlabCodegenIsDeleted) {
    lee_controller_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter9'

  // Terminate for MATLABSystem: '<S42>/Read Parameter'
  if (!lee_controller_DW.obj_mf.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_mf.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter'

  // Terminate for MATLABSystem: '<S42>/Read Parameter1'
  if (!lee_controller_DW.obj_kp.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_kp.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter1'

  // Terminate for MATLABSystem: '<S42>/Read Parameter2'
  if (!lee_controller_DW.obj_ef.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_ef.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter2'

  // Terminate for MATLABSystem: '<S42>/Read Parameter3'
  if (!lee_controller_DW.obj_ph.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_ph.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter3'

  // Terminate for MATLABSystem: '<S42>/Read Parameter4'
  if (!lee_controller_DW.obj_k.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_k.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter4'

  // Terminate for MATLABSystem: '<S42>/Read Parameter5'
  if (!lee_controller_DW.obj_a.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_a.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter5'

  // Terminate for MATLABSystem: '<S1>/PX4 PWM Output'
  if (!lee_controller_DW.obj_co.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_co.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_co.isInitialized == 1) &&
        lee_controller_DW.obj_co.isSetupComplete) {
      uint16_T status;
      status = pwm_disarm(&lee_controller_DW.obj_co.pwmDevHandler,
                          &lee_controller_DW.obj_co.armAdvertiseObj);
      lee_controller_DW.obj_co.errorStatus = static_cast<uint16_T>
        (lee_controller_DW.obj_co.errorStatus | status);
      status = pwm_resetServo(&lee_controller_DW.obj_co.pwmDevHandler,
        lee_controller_DW.obj_co.servoCount,
        lee_controller_DW.obj_co.channelMask, lee_controller_DW.obj_co.isMain,
        &lee_controller_DW.obj_co.actuatorAdvertiseObj);
      lee_controller_DW.obj_co.errorStatus = static_cast<uint16_T>
        (lee_controller_DW.obj_co.errorStatus | status);
      status = pwm_close(&lee_controller_DW.obj_co.pwmDevHandler,
                         &lee_controller_DW.obj_co.actuatorAdvertiseObj,
                         &lee_controller_DW.obj_co.armAdvertiseObj);
      lee_controller_DW.obj_co.errorStatus = static_cast<uint16_T>
        (lee_controller_DW.obj_co.errorStatus | status);
    }
  }

  // End of Terminate for MATLABSystem: '<S1>/PX4 PWM Output'

  // Terminate for MATLABSystem: '<S7>/SinkBlock'
  if (!lee_controller_DW.obj_bv.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_bv.matlabCodegenIsDeleted = true;
    if ((lee_controller_DW.obj_bv.isInitialized == 1) &&
        lee_controller_DW.obj_bv.isSetupComplete) {
      uORB_write_terminate(&lee_controller_DW.obj_bv.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S7>/SinkBlock'

  // Terminate for MATLABSystem: '<S42>/Read Parameter41'
  if (!lee_controller_DW.obj_o.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_o.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter41'

  // Terminate for MATLABSystem: '<S42>/Read Parameter42'
  if (!lee_controller_DW.obj_l.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_l.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter42'

  // Terminate for MATLABSystem: '<S42>/Read Parameter43'
  if (!lee_controller_DW.obj_n.matlabCodegenIsDeleted) {
    lee_controller_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S42>/Read Parameter43'
}

//
// File trailer for generated code.
//
// [EOF]
//
