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
void err_fun(double *nom_x, double *delta_x, double *out_8828323615526015434) {
   out_8828323615526015434[0] = delta_x[0] + nom_x[0];
   out_8828323615526015434[1] = delta_x[1] + nom_x[1];
   out_8828323615526015434[2] = delta_x[2] + nom_x[2];
   out_8828323615526015434[3] = delta_x[3] + nom_x[3];
   out_8828323615526015434[4] = delta_x[4] + nom_x[4];
   out_8828323615526015434[5] = delta_x[5] + nom_x[5];
   out_8828323615526015434[6] = delta_x[6] + nom_x[6];
   out_8828323615526015434[7] = delta_x[7] + nom_x[7];
   out_8828323615526015434[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3498370127488248858) {
   out_3498370127488248858[0] = -nom_x[0] + true_x[0];
   out_3498370127488248858[1] = -nom_x[1] + true_x[1];
   out_3498370127488248858[2] = -nom_x[2] + true_x[2];
   out_3498370127488248858[3] = -nom_x[3] + true_x[3];
   out_3498370127488248858[4] = -nom_x[4] + true_x[4];
   out_3498370127488248858[5] = -nom_x[5] + true_x[5];
   out_3498370127488248858[6] = -nom_x[6] + true_x[6];
   out_3498370127488248858[7] = -nom_x[7] + true_x[7];
   out_3498370127488248858[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6401776151128821180) {
   out_6401776151128821180[0] = 1.0;
   out_6401776151128821180[1] = 0.0;
   out_6401776151128821180[2] = 0.0;
   out_6401776151128821180[3] = 0.0;
   out_6401776151128821180[4] = 0.0;
   out_6401776151128821180[5] = 0.0;
   out_6401776151128821180[6] = 0.0;
   out_6401776151128821180[7] = 0.0;
   out_6401776151128821180[8] = 0.0;
   out_6401776151128821180[9] = 0.0;
   out_6401776151128821180[10] = 1.0;
   out_6401776151128821180[11] = 0.0;
   out_6401776151128821180[12] = 0.0;
   out_6401776151128821180[13] = 0.0;
   out_6401776151128821180[14] = 0.0;
   out_6401776151128821180[15] = 0.0;
   out_6401776151128821180[16] = 0.0;
   out_6401776151128821180[17] = 0.0;
   out_6401776151128821180[18] = 0.0;
   out_6401776151128821180[19] = 0.0;
   out_6401776151128821180[20] = 1.0;
   out_6401776151128821180[21] = 0.0;
   out_6401776151128821180[22] = 0.0;
   out_6401776151128821180[23] = 0.0;
   out_6401776151128821180[24] = 0.0;
   out_6401776151128821180[25] = 0.0;
   out_6401776151128821180[26] = 0.0;
   out_6401776151128821180[27] = 0.0;
   out_6401776151128821180[28] = 0.0;
   out_6401776151128821180[29] = 0.0;
   out_6401776151128821180[30] = 1.0;
   out_6401776151128821180[31] = 0.0;
   out_6401776151128821180[32] = 0.0;
   out_6401776151128821180[33] = 0.0;
   out_6401776151128821180[34] = 0.0;
   out_6401776151128821180[35] = 0.0;
   out_6401776151128821180[36] = 0.0;
   out_6401776151128821180[37] = 0.0;
   out_6401776151128821180[38] = 0.0;
   out_6401776151128821180[39] = 0.0;
   out_6401776151128821180[40] = 1.0;
   out_6401776151128821180[41] = 0.0;
   out_6401776151128821180[42] = 0.0;
   out_6401776151128821180[43] = 0.0;
   out_6401776151128821180[44] = 0.0;
   out_6401776151128821180[45] = 0.0;
   out_6401776151128821180[46] = 0.0;
   out_6401776151128821180[47] = 0.0;
   out_6401776151128821180[48] = 0.0;
   out_6401776151128821180[49] = 0.0;
   out_6401776151128821180[50] = 1.0;
   out_6401776151128821180[51] = 0.0;
   out_6401776151128821180[52] = 0.0;
   out_6401776151128821180[53] = 0.0;
   out_6401776151128821180[54] = 0.0;
   out_6401776151128821180[55] = 0.0;
   out_6401776151128821180[56] = 0.0;
   out_6401776151128821180[57] = 0.0;
   out_6401776151128821180[58] = 0.0;
   out_6401776151128821180[59] = 0.0;
   out_6401776151128821180[60] = 1.0;
   out_6401776151128821180[61] = 0.0;
   out_6401776151128821180[62] = 0.0;
   out_6401776151128821180[63] = 0.0;
   out_6401776151128821180[64] = 0.0;
   out_6401776151128821180[65] = 0.0;
   out_6401776151128821180[66] = 0.0;
   out_6401776151128821180[67] = 0.0;
   out_6401776151128821180[68] = 0.0;
   out_6401776151128821180[69] = 0.0;
   out_6401776151128821180[70] = 1.0;
   out_6401776151128821180[71] = 0.0;
   out_6401776151128821180[72] = 0.0;
   out_6401776151128821180[73] = 0.0;
   out_6401776151128821180[74] = 0.0;
   out_6401776151128821180[75] = 0.0;
   out_6401776151128821180[76] = 0.0;
   out_6401776151128821180[77] = 0.0;
   out_6401776151128821180[78] = 0.0;
   out_6401776151128821180[79] = 0.0;
   out_6401776151128821180[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_146901637752652717) {
   out_146901637752652717[0] = state[0];
   out_146901637752652717[1] = state[1];
   out_146901637752652717[2] = state[2];
   out_146901637752652717[3] = state[3];
   out_146901637752652717[4] = state[4];
   out_146901637752652717[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_146901637752652717[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_146901637752652717[7] = state[7];
   out_146901637752652717[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5522538997423658876) {
   out_5522538997423658876[0] = 1;
   out_5522538997423658876[1] = 0;
   out_5522538997423658876[2] = 0;
   out_5522538997423658876[3] = 0;
   out_5522538997423658876[4] = 0;
   out_5522538997423658876[5] = 0;
   out_5522538997423658876[6] = 0;
   out_5522538997423658876[7] = 0;
   out_5522538997423658876[8] = 0;
   out_5522538997423658876[9] = 0;
   out_5522538997423658876[10] = 1;
   out_5522538997423658876[11] = 0;
   out_5522538997423658876[12] = 0;
   out_5522538997423658876[13] = 0;
   out_5522538997423658876[14] = 0;
   out_5522538997423658876[15] = 0;
   out_5522538997423658876[16] = 0;
   out_5522538997423658876[17] = 0;
   out_5522538997423658876[18] = 0;
   out_5522538997423658876[19] = 0;
   out_5522538997423658876[20] = 1;
   out_5522538997423658876[21] = 0;
   out_5522538997423658876[22] = 0;
   out_5522538997423658876[23] = 0;
   out_5522538997423658876[24] = 0;
   out_5522538997423658876[25] = 0;
   out_5522538997423658876[26] = 0;
   out_5522538997423658876[27] = 0;
   out_5522538997423658876[28] = 0;
   out_5522538997423658876[29] = 0;
   out_5522538997423658876[30] = 1;
   out_5522538997423658876[31] = 0;
   out_5522538997423658876[32] = 0;
   out_5522538997423658876[33] = 0;
   out_5522538997423658876[34] = 0;
   out_5522538997423658876[35] = 0;
   out_5522538997423658876[36] = 0;
   out_5522538997423658876[37] = 0;
   out_5522538997423658876[38] = 0;
   out_5522538997423658876[39] = 0;
   out_5522538997423658876[40] = 1;
   out_5522538997423658876[41] = 0;
   out_5522538997423658876[42] = 0;
   out_5522538997423658876[43] = 0;
   out_5522538997423658876[44] = 0;
   out_5522538997423658876[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5522538997423658876[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5522538997423658876[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5522538997423658876[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5522538997423658876[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5522538997423658876[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5522538997423658876[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5522538997423658876[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5522538997423658876[53] = -9.8100000000000005*dt;
   out_5522538997423658876[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5522538997423658876[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5522538997423658876[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5522538997423658876[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5522538997423658876[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5522538997423658876[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5522538997423658876[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5522538997423658876[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5522538997423658876[62] = 0;
   out_5522538997423658876[63] = 0;
   out_5522538997423658876[64] = 0;
   out_5522538997423658876[65] = 0;
   out_5522538997423658876[66] = 0;
   out_5522538997423658876[67] = 0;
   out_5522538997423658876[68] = 0;
   out_5522538997423658876[69] = 0;
   out_5522538997423658876[70] = 1;
   out_5522538997423658876[71] = 0;
   out_5522538997423658876[72] = 0;
   out_5522538997423658876[73] = 0;
   out_5522538997423658876[74] = 0;
   out_5522538997423658876[75] = 0;
   out_5522538997423658876[76] = 0;
   out_5522538997423658876[77] = 0;
   out_5522538997423658876[78] = 0;
   out_5522538997423658876[79] = 0;
   out_5522538997423658876[80] = 1;
}
void h_25(double *state, double *unused, double *out_8923785172993752075) {
   out_8923785172993752075[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7141276097396065596) {
   out_7141276097396065596[0] = 0;
   out_7141276097396065596[1] = 0;
   out_7141276097396065596[2] = 0;
   out_7141276097396065596[3] = 0;
   out_7141276097396065596[4] = 0;
   out_7141276097396065596[5] = 0;
   out_7141276097396065596[6] = 1;
   out_7141276097396065596[7] = 0;
   out_7141276097396065596[8] = 0;
}
void h_24(double *state, double *unused, double *out_3929820800215180434) {
   out_3929820800215180434[0] = state[4];
   out_3929820800215180434[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4964061673788915623) {
   out_4964061673788915623[0] = 0;
   out_4964061673788915623[1] = 0;
   out_4964061673788915623[2] = 0;
   out_4964061673788915623[3] = 0;
   out_4964061673788915623[4] = 1;
   out_4964061673788915623[5] = 0;
   out_4964061673788915623[6] = 0;
   out_4964061673788915623[7] = 0;
   out_4964061673788915623[8] = 0;
   out_4964061673788915623[9] = 0;
   out_4964061673788915623[10] = 0;
   out_4964061673788915623[11] = 0;
   out_4964061673788915623[12] = 0;
   out_4964061673788915623[13] = 0;
   out_4964061673788915623[14] = 1;
   out_4964061673788915623[15] = 0;
   out_4964061673788915623[16] = 0;
   out_4964061673788915623[17] = 0;
}
void h_30(double *state, double *unused, double *out_1238992460570384448) {
   out_1238992460570384448[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4622943138888816969) {
   out_4622943138888816969[0] = 0;
   out_4622943138888816969[1] = 0;
   out_4622943138888816969[2] = 0;
   out_4622943138888816969[3] = 0;
   out_4622943138888816969[4] = 1;
   out_4622943138888816969[5] = 0;
   out_4622943138888816969[6] = 0;
   out_4622943138888816969[7] = 0;
   out_4622943138888816969[8] = 0;
}
void h_26(double *state, double *unused, double *out_2406736261646526185) {
   out_2406736261646526185[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7563964657439429796) {
   out_7563964657439429796[0] = 0;
   out_7563964657439429796[1] = 0;
   out_7563964657439429796[2] = 0;
   out_7563964657439429796[3] = 0;
   out_7563964657439429796[4] = 0;
   out_7563964657439429796[5] = 0;
   out_7563964657439429796[6] = 0;
   out_7563964657439429796[7] = 1;
   out_7563964657439429796[8] = 0;
}
void h_27(double *state, double *unused, double *out_6319379852185054424) {
   out_6319379852185054424[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6797706450689241880) {
   out_6797706450689241880[0] = 0;
   out_6797706450689241880[1] = 0;
   out_6797706450689241880[2] = 0;
   out_6797706450689241880[3] = 1;
   out_6797706450689241880[4] = 0;
   out_6797706450689241880[5] = 0;
   out_6797706450689241880[6] = 0;
   out_6797706450689241880[7] = 0;
   out_6797706450689241880[8] = 0;
}
void h_29(double *state, double *unused, double *out_1573559642699468935) {
   out_1573559642699468935[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4112711794574424785) {
   out_4112711794574424785[0] = 0;
   out_4112711794574424785[1] = 1;
   out_4112711794574424785[2] = 0;
   out_4112711794574424785[3] = 0;
   out_4112711794574424785[4] = 0;
   out_4112711794574424785[5] = 0;
   out_4112711794574424785[6] = 0;
   out_4112711794574424785[7] = 0;
   out_4112711794574424785[8] = 0;
}
void h_28(double *state, double *unused, double *out_3282593800740721739) {
   out_3282593800740721739[0] = state[0];
}
void H_28(double *state, double *unused, double *out_9195110811643955359) {
   out_9195110811643955359[0] = 1;
   out_9195110811643955359[1] = 0;
   out_9195110811643955359[2] = 0;
   out_9195110811643955359[3] = 0;
   out_9195110811643955359[4] = 0;
   out_9195110811643955359[5] = 0;
   out_9195110811643955359[6] = 0;
   out_9195110811643955359[7] = 0;
   out_9195110811643955359[8] = 0;
}
void h_31(double *state, double *unused, double *out_5062101696565250423) {
   out_5062101696565250423[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6937756555206078320) {
   out_6937756555206078320[0] = 0;
   out_6937756555206078320[1] = 0;
   out_6937756555206078320[2] = 0;
   out_6937756555206078320[3] = 0;
   out_6937756555206078320[4] = 0;
   out_6937756555206078320[5] = 0;
   out_6937756555206078320[6] = 0;
   out_6937756555206078320[7] = 0;
   out_6937756555206078320[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8828323615526015434) {
  err_fun(nom_x, delta_x, out_8828323615526015434);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3498370127488248858) {
  inv_err_fun(nom_x, true_x, out_3498370127488248858);
}
void car_H_mod_fun(double *state, double *out_6401776151128821180) {
  H_mod_fun(state, out_6401776151128821180);
}
void car_f_fun(double *state, double dt, double *out_146901637752652717) {
  f_fun(state,  dt, out_146901637752652717);
}
void car_F_fun(double *state, double dt, double *out_5522538997423658876) {
  F_fun(state,  dt, out_5522538997423658876);
}
void car_h_25(double *state, double *unused, double *out_8923785172993752075) {
  h_25(state, unused, out_8923785172993752075);
}
void car_H_25(double *state, double *unused, double *out_7141276097396065596) {
  H_25(state, unused, out_7141276097396065596);
}
void car_h_24(double *state, double *unused, double *out_3929820800215180434) {
  h_24(state, unused, out_3929820800215180434);
}
void car_H_24(double *state, double *unused, double *out_4964061673788915623) {
  H_24(state, unused, out_4964061673788915623);
}
void car_h_30(double *state, double *unused, double *out_1238992460570384448) {
  h_30(state, unused, out_1238992460570384448);
}
void car_H_30(double *state, double *unused, double *out_4622943138888816969) {
  H_30(state, unused, out_4622943138888816969);
}
void car_h_26(double *state, double *unused, double *out_2406736261646526185) {
  h_26(state, unused, out_2406736261646526185);
}
void car_H_26(double *state, double *unused, double *out_7563964657439429796) {
  H_26(state, unused, out_7563964657439429796);
}
void car_h_27(double *state, double *unused, double *out_6319379852185054424) {
  h_27(state, unused, out_6319379852185054424);
}
void car_H_27(double *state, double *unused, double *out_6797706450689241880) {
  H_27(state, unused, out_6797706450689241880);
}
void car_h_29(double *state, double *unused, double *out_1573559642699468935) {
  h_29(state, unused, out_1573559642699468935);
}
void car_H_29(double *state, double *unused, double *out_4112711794574424785) {
  H_29(state, unused, out_4112711794574424785);
}
void car_h_28(double *state, double *unused, double *out_3282593800740721739) {
  h_28(state, unused, out_3282593800740721739);
}
void car_H_28(double *state, double *unused, double *out_9195110811643955359) {
  H_28(state, unused, out_9195110811643955359);
}
void car_h_31(double *state, double *unused, double *out_5062101696565250423) {
  h_31(state, unused, out_5062101696565250423);
}
void car_H_31(double *state, double *unused, double *out_6937756555206078320) {
  H_31(state, unused, out_6937756555206078320);
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
