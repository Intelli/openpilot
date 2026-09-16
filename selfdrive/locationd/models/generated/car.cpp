#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_8618165811213795631) {
   out_8618165811213795631[0] = delta_x[0] + nom_x[0];
   out_8618165811213795631[1] = delta_x[1] + nom_x[1];
   out_8618165811213795631[2] = delta_x[2] + nom_x[2];
   out_8618165811213795631[3] = delta_x[3] + nom_x[3];
   out_8618165811213795631[4] = delta_x[4] + nom_x[4];
   out_8618165811213795631[5] = delta_x[5] + nom_x[5];
   out_8618165811213795631[6] = delta_x[6] + nom_x[6];
   out_8618165811213795631[7] = delta_x[7] + nom_x[7];
   out_8618165811213795631[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_476504129112473836) {
   out_476504129112473836[0] = -nom_x[0] + true_x[0];
   out_476504129112473836[1] = -nom_x[1] + true_x[1];
   out_476504129112473836[2] = -nom_x[2] + true_x[2];
   out_476504129112473836[3] = -nom_x[3] + true_x[3];
   out_476504129112473836[4] = -nom_x[4] + true_x[4];
   out_476504129112473836[5] = -nom_x[5] + true_x[5];
   out_476504129112473836[6] = -nom_x[6] + true_x[6];
   out_476504129112473836[7] = -nom_x[7] + true_x[7];
   out_476504129112473836[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7392752302911939325) {
   out_7392752302911939325[0] = 1.0;
   out_7392752302911939325[1] = 0.0;
   out_7392752302911939325[2] = 0.0;
   out_7392752302911939325[3] = 0.0;
   out_7392752302911939325[4] = 0.0;
   out_7392752302911939325[5] = 0.0;
   out_7392752302911939325[6] = 0.0;
   out_7392752302911939325[7] = 0.0;
   out_7392752302911939325[8] = 0.0;
   out_7392752302911939325[9] = 0.0;
   out_7392752302911939325[10] = 1.0;
   out_7392752302911939325[11] = 0.0;
   out_7392752302911939325[12] = 0.0;
   out_7392752302911939325[13] = 0.0;
   out_7392752302911939325[14] = 0.0;
   out_7392752302911939325[15] = 0.0;
   out_7392752302911939325[16] = 0.0;
   out_7392752302911939325[17] = 0.0;
   out_7392752302911939325[18] = 0.0;
   out_7392752302911939325[19] = 0.0;
   out_7392752302911939325[20] = 1.0;
   out_7392752302911939325[21] = 0.0;
   out_7392752302911939325[22] = 0.0;
   out_7392752302911939325[23] = 0.0;
   out_7392752302911939325[24] = 0.0;
   out_7392752302911939325[25] = 0.0;
   out_7392752302911939325[26] = 0.0;
   out_7392752302911939325[27] = 0.0;
   out_7392752302911939325[28] = 0.0;
   out_7392752302911939325[29] = 0.0;
   out_7392752302911939325[30] = 1.0;
   out_7392752302911939325[31] = 0.0;
   out_7392752302911939325[32] = 0.0;
   out_7392752302911939325[33] = 0.0;
   out_7392752302911939325[34] = 0.0;
   out_7392752302911939325[35] = 0.0;
   out_7392752302911939325[36] = 0.0;
   out_7392752302911939325[37] = 0.0;
   out_7392752302911939325[38] = 0.0;
   out_7392752302911939325[39] = 0.0;
   out_7392752302911939325[40] = 1.0;
   out_7392752302911939325[41] = 0.0;
   out_7392752302911939325[42] = 0.0;
   out_7392752302911939325[43] = 0.0;
   out_7392752302911939325[44] = 0.0;
   out_7392752302911939325[45] = 0.0;
   out_7392752302911939325[46] = 0.0;
   out_7392752302911939325[47] = 0.0;
   out_7392752302911939325[48] = 0.0;
   out_7392752302911939325[49] = 0.0;
   out_7392752302911939325[50] = 1.0;
   out_7392752302911939325[51] = 0.0;
   out_7392752302911939325[52] = 0.0;
   out_7392752302911939325[53] = 0.0;
   out_7392752302911939325[54] = 0.0;
   out_7392752302911939325[55] = 0.0;
   out_7392752302911939325[56] = 0.0;
   out_7392752302911939325[57] = 0.0;
   out_7392752302911939325[58] = 0.0;
   out_7392752302911939325[59] = 0.0;
   out_7392752302911939325[60] = 1.0;
   out_7392752302911939325[61] = 0.0;
   out_7392752302911939325[62] = 0.0;
   out_7392752302911939325[63] = 0.0;
   out_7392752302911939325[64] = 0.0;
   out_7392752302911939325[65] = 0.0;
   out_7392752302911939325[66] = 0.0;
   out_7392752302911939325[67] = 0.0;
   out_7392752302911939325[68] = 0.0;
   out_7392752302911939325[69] = 0.0;
   out_7392752302911939325[70] = 1.0;
   out_7392752302911939325[71] = 0.0;
   out_7392752302911939325[72] = 0.0;
   out_7392752302911939325[73] = 0.0;
   out_7392752302911939325[74] = 0.0;
   out_7392752302911939325[75] = 0.0;
   out_7392752302911939325[76] = 0.0;
   out_7392752302911939325[77] = 0.0;
   out_7392752302911939325[78] = 0.0;
   out_7392752302911939325[79] = 0.0;
   out_7392752302911939325[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_9221484452100360325) {
   out_9221484452100360325[0] = state[0];
   out_9221484452100360325[1] = state[1];
   out_9221484452100360325[2] = state[2];
   out_9221484452100360325[3] = state[3];
   out_9221484452100360325[4] = state[4];
   out_9221484452100360325[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_9221484452100360325[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_9221484452100360325[7] = state[7];
   out_9221484452100360325[8] = state[8];
}
void F_fun(double *state, double dt, double *out_9146847634012448063) {
   out_9146847634012448063[0] = 1;
   out_9146847634012448063[1] = 0;
   out_9146847634012448063[2] = 0;
   out_9146847634012448063[3] = 0;
   out_9146847634012448063[4] = 0;
   out_9146847634012448063[5] = 0;
   out_9146847634012448063[6] = 0;
   out_9146847634012448063[7] = 0;
   out_9146847634012448063[8] = 0;
   out_9146847634012448063[9] = 0;
   out_9146847634012448063[10] = 1;
   out_9146847634012448063[11] = 0;
   out_9146847634012448063[12] = 0;
   out_9146847634012448063[13] = 0;
   out_9146847634012448063[14] = 0;
   out_9146847634012448063[15] = 0;
   out_9146847634012448063[16] = 0;
   out_9146847634012448063[17] = 0;
   out_9146847634012448063[18] = 0;
   out_9146847634012448063[19] = 0;
   out_9146847634012448063[20] = 1;
   out_9146847634012448063[21] = 0;
   out_9146847634012448063[22] = 0;
   out_9146847634012448063[23] = 0;
   out_9146847634012448063[24] = 0;
   out_9146847634012448063[25] = 0;
   out_9146847634012448063[26] = 0;
   out_9146847634012448063[27] = 0;
   out_9146847634012448063[28] = 0;
   out_9146847634012448063[29] = 0;
   out_9146847634012448063[30] = 1;
   out_9146847634012448063[31] = 0;
   out_9146847634012448063[32] = 0;
   out_9146847634012448063[33] = 0;
   out_9146847634012448063[34] = 0;
   out_9146847634012448063[35] = 0;
   out_9146847634012448063[36] = 0;
   out_9146847634012448063[37] = 0;
   out_9146847634012448063[38] = 0;
   out_9146847634012448063[39] = 0;
   out_9146847634012448063[40] = 1;
   out_9146847634012448063[41] = 0;
   out_9146847634012448063[42] = 0;
   out_9146847634012448063[43] = 0;
   out_9146847634012448063[44] = 0;
   out_9146847634012448063[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_9146847634012448063[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_9146847634012448063[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9146847634012448063[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9146847634012448063[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_9146847634012448063[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_9146847634012448063[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_9146847634012448063[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_9146847634012448063[53] = -9.8100000000000005*dt;
   out_9146847634012448063[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_9146847634012448063[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_9146847634012448063[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9146847634012448063[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9146847634012448063[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_9146847634012448063[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_9146847634012448063[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_9146847634012448063[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9146847634012448063[62] = 0;
   out_9146847634012448063[63] = 0;
   out_9146847634012448063[64] = 0;
   out_9146847634012448063[65] = 0;
   out_9146847634012448063[66] = 0;
   out_9146847634012448063[67] = 0;
   out_9146847634012448063[68] = 0;
   out_9146847634012448063[69] = 0;
   out_9146847634012448063[70] = 1;
   out_9146847634012448063[71] = 0;
   out_9146847634012448063[72] = 0;
   out_9146847634012448063[73] = 0;
   out_9146847634012448063[74] = 0;
   out_9146847634012448063[75] = 0;
   out_9146847634012448063[76] = 0;
   out_9146847634012448063[77] = 0;
   out_9146847634012448063[78] = 0;
   out_9146847634012448063[79] = 0;
   out_9146847634012448063[80] = 1;
}
void h_25(double *state, double *unused, double *out_3254080677535242918) {
   out_3254080677535242918[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1860803544885375054) {
   out_1860803544885375054[0] = 0;
   out_1860803544885375054[1] = 0;
   out_1860803544885375054[2] = 0;
   out_1860803544885375054[3] = 0;
   out_1860803544885375054[4] = 0;
   out_1860803544885375054[5] = 0;
   out_1860803544885375054[6] = 1;
   out_1860803544885375054[7] = 0;
   out_1860803544885375054[8] = 0;
}
void h_24(double *state, double *unused, double *out_1285601474070799560) {
   out_1285601474070799560[0] = state[4];
   out_1285601474070799560[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7357875342754981337) {
   out_7357875342754981337[0] = 0;
   out_7357875342754981337[1] = 0;
   out_7357875342754981337[2] = 0;
   out_7357875342754981337[3] = 0;
   out_7357875342754981337[4] = 1;
   out_7357875342754981337[5] = 0;
   out_7357875342754981337[6] = 0;
   out_7357875342754981337[7] = 0;
   out_7357875342754981337[8] = 0;
   out_7357875342754981337[9] = 0;
   out_7357875342754981337[10] = 0;
   out_7357875342754981337[11] = 0;
   out_7357875342754981337[12] = 0;
   out_7357875342754981337[13] = 0;
   out_7357875342754981337[14] = 1;
   out_7357875342754981337[15] = 0;
   out_7357875342754981337[16] = 0;
   out_7357875342754981337[17] = 0;
}
void h_30(double *state, double *unused, double *out_3855498835148606472) {
   out_3855498835148606472[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1731464597742134984) {
   out_1731464597742134984[0] = 0;
   out_1731464597742134984[1] = 0;
   out_1731464597742134984[2] = 0;
   out_1731464597742134984[3] = 0;
   out_1731464597742134984[4] = 1;
   out_1731464597742134984[5] = 0;
   out_1731464597742134984[6] = 0;
   out_1731464597742134984[7] = 0;
   out_1731464597742134984[8] = 0;
}
void h_26(double *state, double *unused, double *out_8857172102809452117) {
   out_8857172102809452117[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1880699773988681170) {
   out_1880699773988681170[0] = 0;
   out_1880699773988681170[1] = 0;
   out_1880699773988681170[2] = 0;
   out_1880699773988681170[3] = 0;
   out_1880699773988681170[4] = 0;
   out_1880699773988681170[5] = 0;
   out_1880699773988681170[6] = 0;
   out_1880699773988681170[7] = 1;
   out_1880699773988681170[8] = 0;
}
void h_27(double *state, double *unused, double *out_1368105351920865396) {
   out_1368105351920865396[0] = state[3];
}
void H_27(double *state, double *unused, double *out_443298714058289927) {
   out_443298714058289927[0] = 0;
   out_443298714058289927[1] = 0;
   out_443298714058289927[2] = 0;
   out_443298714058289927[3] = 1;
   out_443298714058289927[4] = 0;
   out_443298714058289927[5] = 0;
   out_443298714058289927[6] = 0;
   out_443298714058289927[7] = 0;
   out_443298714058289927[8] = 0;
}
void h_29(double *state, double *unused, double *out_9025144054500435279) {
   out_9025144054500435279[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2156661440927840960) {
   out_2156661440927840960[0] = 0;
   out_2156661440927840960[1] = 1;
   out_2156661440927840960[2] = 0;
   out_2156661440927840960[3] = 0;
   out_2156661440927840960[4] = 0;
   out_2156661440927840960[5] = 0;
   out_2156661440927840960[6] = 0;
   out_2156661440927840960[7] = 0;
   out_2156661440927840960[8] = 0;
}
void h_28(double *state, double *unused, double *out_6369778619581711041) {
   out_6369778619581711041[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7239060457997371534) {
   out_7239060457997371534[0] = 1;
   out_7239060457997371534[1] = 0;
   out_7239060457997371534[2] = 0;
   out_7239060457997371534[3] = 0;
   out_7239060457997371534[4] = 0;
   out_7239060457997371534[5] = 0;
   out_7239060457997371534[6] = 0;
   out_7239060457997371534[7] = 0;
   out_7239060457997371534[8] = 0;
}
void h_31(double *state, double *unused, double *out_4509184579285429523) {
   out_4509184579285429523[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1891449506762335482) {
   out_1891449506762335482[0] = 0;
   out_1891449506762335482[1] = 0;
   out_1891449506762335482[2] = 0;
   out_1891449506762335482[3] = 0;
   out_1891449506762335482[4] = 0;
   out_1891449506762335482[5] = 0;
   out_1891449506762335482[6] = 0;
   out_1891449506762335482[7] = 0;
   out_1891449506762335482[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_8618165811213795631) {
  err_fun(nom_x, delta_x, out_8618165811213795631);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_476504129112473836) {
  inv_err_fun(nom_x, true_x, out_476504129112473836);
}
void car_H_mod_fun(double *state, double *out_7392752302911939325) {
  H_mod_fun(state, out_7392752302911939325);
}
void car_f_fun(double *state, double dt, double *out_9221484452100360325) {
  f_fun(state,  dt, out_9221484452100360325);
}
void car_F_fun(double *state, double dt, double *out_9146847634012448063) {
  F_fun(state,  dt, out_9146847634012448063);
}
void car_h_25(double *state, double *unused, double *out_3254080677535242918) {
  h_25(state, unused, out_3254080677535242918);
}
void car_H_25(double *state, double *unused, double *out_1860803544885375054) {
  H_25(state, unused, out_1860803544885375054);
}
void car_h_24(double *state, double *unused, double *out_1285601474070799560) {
  h_24(state, unused, out_1285601474070799560);
}
void car_H_24(double *state, double *unused, double *out_7357875342754981337) {
  H_24(state, unused, out_7357875342754981337);
}
void car_h_30(double *state, double *unused, double *out_3855498835148606472) {
  h_30(state, unused, out_3855498835148606472);
}
void car_H_30(double *state, double *unused, double *out_1731464597742134984) {
  H_30(state, unused, out_1731464597742134984);
}
void car_h_26(double *state, double *unused, double *out_8857172102809452117) {
  h_26(state, unused, out_8857172102809452117);
}
void car_H_26(double *state, double *unused, double *out_1880699773988681170) {
  H_26(state, unused, out_1880699773988681170);
}
void car_h_27(double *state, double *unused, double *out_1368105351920865396) {
  h_27(state, unused, out_1368105351920865396);
}
void car_H_27(double *state, double *unused, double *out_443298714058289927) {
  H_27(state, unused, out_443298714058289927);
}
void car_h_29(double *state, double *unused, double *out_9025144054500435279) {
  h_29(state, unused, out_9025144054500435279);
}
void car_H_29(double *state, double *unused, double *out_2156661440927840960) {
  H_29(state, unused, out_2156661440927840960);
}
void car_h_28(double *state, double *unused, double *out_6369778619581711041) {
  h_28(state, unused, out_6369778619581711041);
}
void car_H_28(double *state, double *unused, double *out_7239060457997371534) {
  H_28(state, unused, out_7239060457997371534);
}
void car_h_31(double *state, double *unused, double *out_4509184579285429523) {
  h_31(state, unused, out_4509184579285429523);
}
void car_H_31(double *state, double *unused, double *out_1891449506762335482) {
  H_31(state, unused, out_1891449506762335482);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
