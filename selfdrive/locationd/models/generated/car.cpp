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
void err_fun(double *nom_x, double *delta_x, double *out_6220786048043098858) {
   out_6220786048043098858[0] = delta_x[0] + nom_x[0];
   out_6220786048043098858[1] = delta_x[1] + nom_x[1];
   out_6220786048043098858[2] = delta_x[2] + nom_x[2];
   out_6220786048043098858[3] = delta_x[3] + nom_x[3];
   out_6220786048043098858[4] = delta_x[4] + nom_x[4];
   out_6220786048043098858[5] = delta_x[5] + nom_x[5];
   out_6220786048043098858[6] = delta_x[6] + nom_x[6];
   out_6220786048043098858[7] = delta_x[7] + nom_x[7];
   out_6220786048043098858[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8365457917697439847) {
   out_8365457917697439847[0] = -nom_x[0] + true_x[0];
   out_8365457917697439847[1] = -nom_x[1] + true_x[1];
   out_8365457917697439847[2] = -nom_x[2] + true_x[2];
   out_8365457917697439847[3] = -nom_x[3] + true_x[3];
   out_8365457917697439847[4] = -nom_x[4] + true_x[4];
   out_8365457917697439847[5] = -nom_x[5] + true_x[5];
   out_8365457917697439847[6] = -nom_x[6] + true_x[6];
   out_8365457917697439847[7] = -nom_x[7] + true_x[7];
   out_8365457917697439847[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7240996753969743287) {
   out_7240996753969743287[0] = 1.0;
   out_7240996753969743287[1] = 0.0;
   out_7240996753969743287[2] = 0.0;
   out_7240996753969743287[3] = 0.0;
   out_7240996753969743287[4] = 0.0;
   out_7240996753969743287[5] = 0.0;
   out_7240996753969743287[6] = 0.0;
   out_7240996753969743287[7] = 0.0;
   out_7240996753969743287[8] = 0.0;
   out_7240996753969743287[9] = 0.0;
   out_7240996753969743287[10] = 1.0;
   out_7240996753969743287[11] = 0.0;
   out_7240996753969743287[12] = 0.0;
   out_7240996753969743287[13] = 0.0;
   out_7240996753969743287[14] = 0.0;
   out_7240996753969743287[15] = 0.0;
   out_7240996753969743287[16] = 0.0;
   out_7240996753969743287[17] = 0.0;
   out_7240996753969743287[18] = 0.0;
   out_7240996753969743287[19] = 0.0;
   out_7240996753969743287[20] = 1.0;
   out_7240996753969743287[21] = 0.0;
   out_7240996753969743287[22] = 0.0;
   out_7240996753969743287[23] = 0.0;
   out_7240996753969743287[24] = 0.0;
   out_7240996753969743287[25] = 0.0;
   out_7240996753969743287[26] = 0.0;
   out_7240996753969743287[27] = 0.0;
   out_7240996753969743287[28] = 0.0;
   out_7240996753969743287[29] = 0.0;
   out_7240996753969743287[30] = 1.0;
   out_7240996753969743287[31] = 0.0;
   out_7240996753969743287[32] = 0.0;
   out_7240996753969743287[33] = 0.0;
   out_7240996753969743287[34] = 0.0;
   out_7240996753969743287[35] = 0.0;
   out_7240996753969743287[36] = 0.0;
   out_7240996753969743287[37] = 0.0;
   out_7240996753969743287[38] = 0.0;
   out_7240996753969743287[39] = 0.0;
   out_7240996753969743287[40] = 1.0;
   out_7240996753969743287[41] = 0.0;
   out_7240996753969743287[42] = 0.0;
   out_7240996753969743287[43] = 0.0;
   out_7240996753969743287[44] = 0.0;
   out_7240996753969743287[45] = 0.0;
   out_7240996753969743287[46] = 0.0;
   out_7240996753969743287[47] = 0.0;
   out_7240996753969743287[48] = 0.0;
   out_7240996753969743287[49] = 0.0;
   out_7240996753969743287[50] = 1.0;
   out_7240996753969743287[51] = 0.0;
   out_7240996753969743287[52] = 0.0;
   out_7240996753969743287[53] = 0.0;
   out_7240996753969743287[54] = 0.0;
   out_7240996753969743287[55] = 0.0;
   out_7240996753969743287[56] = 0.0;
   out_7240996753969743287[57] = 0.0;
   out_7240996753969743287[58] = 0.0;
   out_7240996753969743287[59] = 0.0;
   out_7240996753969743287[60] = 1.0;
   out_7240996753969743287[61] = 0.0;
   out_7240996753969743287[62] = 0.0;
   out_7240996753969743287[63] = 0.0;
   out_7240996753969743287[64] = 0.0;
   out_7240996753969743287[65] = 0.0;
   out_7240996753969743287[66] = 0.0;
   out_7240996753969743287[67] = 0.0;
   out_7240996753969743287[68] = 0.0;
   out_7240996753969743287[69] = 0.0;
   out_7240996753969743287[70] = 1.0;
   out_7240996753969743287[71] = 0.0;
   out_7240996753969743287[72] = 0.0;
   out_7240996753969743287[73] = 0.0;
   out_7240996753969743287[74] = 0.0;
   out_7240996753969743287[75] = 0.0;
   out_7240996753969743287[76] = 0.0;
   out_7240996753969743287[77] = 0.0;
   out_7240996753969743287[78] = 0.0;
   out_7240996753969743287[79] = 0.0;
   out_7240996753969743287[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5407440773771914068) {
   out_5407440773771914068[0] = state[0];
   out_5407440773771914068[1] = state[1];
   out_5407440773771914068[2] = state[2];
   out_5407440773771914068[3] = state[3];
   out_5407440773771914068[4] = state[4];
   out_5407440773771914068[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5407440773771914068[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5407440773771914068[7] = state[7];
   out_5407440773771914068[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1968632945652242383) {
   out_1968632945652242383[0] = 1;
   out_1968632945652242383[1] = 0;
   out_1968632945652242383[2] = 0;
   out_1968632945652242383[3] = 0;
   out_1968632945652242383[4] = 0;
   out_1968632945652242383[5] = 0;
   out_1968632945652242383[6] = 0;
   out_1968632945652242383[7] = 0;
   out_1968632945652242383[8] = 0;
   out_1968632945652242383[9] = 0;
   out_1968632945652242383[10] = 1;
   out_1968632945652242383[11] = 0;
   out_1968632945652242383[12] = 0;
   out_1968632945652242383[13] = 0;
   out_1968632945652242383[14] = 0;
   out_1968632945652242383[15] = 0;
   out_1968632945652242383[16] = 0;
   out_1968632945652242383[17] = 0;
   out_1968632945652242383[18] = 0;
   out_1968632945652242383[19] = 0;
   out_1968632945652242383[20] = 1;
   out_1968632945652242383[21] = 0;
   out_1968632945652242383[22] = 0;
   out_1968632945652242383[23] = 0;
   out_1968632945652242383[24] = 0;
   out_1968632945652242383[25] = 0;
   out_1968632945652242383[26] = 0;
   out_1968632945652242383[27] = 0;
   out_1968632945652242383[28] = 0;
   out_1968632945652242383[29] = 0;
   out_1968632945652242383[30] = 1;
   out_1968632945652242383[31] = 0;
   out_1968632945652242383[32] = 0;
   out_1968632945652242383[33] = 0;
   out_1968632945652242383[34] = 0;
   out_1968632945652242383[35] = 0;
   out_1968632945652242383[36] = 0;
   out_1968632945652242383[37] = 0;
   out_1968632945652242383[38] = 0;
   out_1968632945652242383[39] = 0;
   out_1968632945652242383[40] = 1;
   out_1968632945652242383[41] = 0;
   out_1968632945652242383[42] = 0;
   out_1968632945652242383[43] = 0;
   out_1968632945652242383[44] = 0;
   out_1968632945652242383[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1968632945652242383[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1968632945652242383[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1968632945652242383[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1968632945652242383[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1968632945652242383[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1968632945652242383[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1968632945652242383[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1968632945652242383[53] = -9.8100000000000005*dt;
   out_1968632945652242383[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1968632945652242383[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1968632945652242383[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1968632945652242383[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1968632945652242383[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1968632945652242383[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1968632945652242383[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1968632945652242383[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1968632945652242383[62] = 0;
   out_1968632945652242383[63] = 0;
   out_1968632945652242383[64] = 0;
   out_1968632945652242383[65] = 0;
   out_1968632945652242383[66] = 0;
   out_1968632945652242383[67] = 0;
   out_1968632945652242383[68] = 0;
   out_1968632945652242383[69] = 0;
   out_1968632945652242383[70] = 1;
   out_1968632945652242383[71] = 0;
   out_1968632945652242383[72] = 0;
   out_1968632945652242383[73] = 0;
   out_1968632945652242383[74] = 0;
   out_1968632945652242383[75] = 0;
   out_1968632945652242383[76] = 0;
   out_1968632945652242383[77] = 0;
   out_1968632945652242383[78] = 0;
   out_1968632945652242383[79] = 0;
   out_1968632945652242383[80] = 1;
}
void h_25(double *state, double *unused, double *out_1914678424628455374) {
   out_1914678424628455374[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8545335864161714907) {
   out_8545335864161714907[0] = 0;
   out_8545335864161714907[1] = 0;
   out_8545335864161714907[2] = 0;
   out_8545335864161714907[3] = 0;
   out_8545335864161714907[4] = 0;
   out_8545335864161714907[5] = 0;
   out_8545335864161714907[6] = 1;
   out_8545335864161714907[7] = 0;
   out_8545335864161714907[8] = 0;
}
void h_24(double *state, double *unused, double *out_1769762204930244922) {
   out_1769762204930244922[0] = state[4];
   out_1769762204930244922[1] = state[5];
}
void H_24(double *state, double *unused, double *out_160090505177928474) {
   out_160090505177928474[0] = 0;
   out_160090505177928474[1] = 0;
   out_160090505177928474[2] = 0;
   out_160090505177928474[3] = 0;
   out_160090505177928474[4] = 1;
   out_160090505177928474[5] = 0;
   out_160090505177928474[6] = 0;
   out_160090505177928474[7] = 0;
   out_160090505177928474[8] = 0;
   out_160090505177928474[9] = 0;
   out_160090505177928474[10] = 0;
   out_160090505177928474[11] = 0;
   out_160090505177928474[12] = 0;
   out_160090505177928474[13] = 0;
   out_160090505177928474[14] = 1;
   out_160090505177928474[15] = 0;
   out_160090505177928474[16] = 0;
   out_160090505177928474[17] = 0;
}
void h_30(double *state, double *unused, double *out_8650792998327047057) {
   out_8650792998327047057[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8674674811304954977) {
   out_8674674811304954977[0] = 0;
   out_8674674811304954977[1] = 0;
   out_8674674811304954977[2] = 0;
   out_8674674811304954977[3] = 0;
   out_8674674811304954977[4] = 1;
   out_8674674811304954977[5] = 0;
   out_8674674811304954977[6] = 0;
   out_8674674811304954977[7] = 0;
   out_8674674811304954977[8] = 0;
}
void h_26(double *state, double *unused, double *out_3357616287989103000) {
   out_3357616287989103000[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6159904890673780485) {
   out_6159904890673780485[0] = 0;
   out_6159904890673780485[1] = 0;
   out_6159904890673780485[2] = 0;
   out_6159904890673780485[3] = 0;
   out_6159904890673780485[4] = 0;
   out_6159904890673780485[5] = 0;
   out_6159904890673780485[6] = 0;
   out_6159904890673780485[7] = 1;
   out_6159904890673780485[8] = 0;
}
void h_27(double *state, double *unused, double *out_7140585640463780321) {
   out_7140585640463780321[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7597305950604171728) {
   out_7597305950604171728[0] = 0;
   out_7597305950604171728[1] = 0;
   out_7597305950604171728[2] = 0;
   out_7597305950604171728[3] = 1;
   out_7597305950604171728[4] = 0;
   out_7597305950604171728[5] = 0;
   out_7597305950604171728[6] = 0;
   out_7597305950604171728[7] = 0;
   out_7597305950604171728[8] = 0;
}
void h_29(double *state, double *unused, double *out_5021036999341260248) {
   out_5021036999341260248[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5883943223734620695) {
   out_5883943223734620695[0] = 0;
   out_5883943223734620695[1] = 1;
   out_5883943223734620695[2] = 0;
   out_5883943223734620695[3] = 0;
   out_5883943223734620695[4] = 0;
   out_5883943223734620695[5] = 0;
   out_5883943223734620695[6] = 0;
   out_5883943223734620695[7] = 0;
   out_5883943223734620695[8] = 0;
}
void h_28(double *state, double *unused, double *out_7743901525140257838) {
   out_7743901525140257838[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7847573495299946946) {
   out_7847573495299946946[0] = 1;
   out_7847573495299946946[1] = 0;
   out_7847573495299946946[2] = 0;
   out_7847573495299946946[3] = 0;
   out_7847573495299946946[4] = 0;
   out_7847573495299946946[5] = 0;
   out_7847573495299946946[6] = 0;
   out_7847573495299946946[7] = 0;
   out_7847573495299946946[8] = 0;
}
void h_31(double *state, double *unused, double *out_1722771103625566976) {
   out_1722771103625566976[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8514689902284754479) {
   out_8514689902284754479[0] = 0;
   out_8514689902284754479[1] = 0;
   out_8514689902284754479[2] = 0;
   out_8514689902284754479[3] = 0;
   out_8514689902284754479[4] = 0;
   out_8514689902284754479[5] = 0;
   out_8514689902284754479[6] = 0;
   out_8514689902284754479[7] = 0;
   out_8514689902284754479[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6220786048043098858) {
  err_fun(nom_x, delta_x, out_6220786048043098858);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8365457917697439847) {
  inv_err_fun(nom_x, true_x, out_8365457917697439847);
}
void car_H_mod_fun(double *state, double *out_7240996753969743287) {
  H_mod_fun(state, out_7240996753969743287);
}
void car_f_fun(double *state, double dt, double *out_5407440773771914068) {
  f_fun(state,  dt, out_5407440773771914068);
}
void car_F_fun(double *state, double dt, double *out_1968632945652242383) {
  F_fun(state,  dt, out_1968632945652242383);
}
void car_h_25(double *state, double *unused, double *out_1914678424628455374) {
  h_25(state, unused, out_1914678424628455374);
}
void car_H_25(double *state, double *unused, double *out_8545335864161714907) {
  H_25(state, unused, out_8545335864161714907);
}
void car_h_24(double *state, double *unused, double *out_1769762204930244922) {
  h_24(state, unused, out_1769762204930244922);
}
void car_H_24(double *state, double *unused, double *out_160090505177928474) {
  H_24(state, unused, out_160090505177928474);
}
void car_h_30(double *state, double *unused, double *out_8650792998327047057) {
  h_30(state, unused, out_8650792998327047057);
}
void car_H_30(double *state, double *unused, double *out_8674674811304954977) {
  H_30(state, unused, out_8674674811304954977);
}
void car_h_26(double *state, double *unused, double *out_3357616287989103000) {
  h_26(state, unused, out_3357616287989103000);
}
void car_H_26(double *state, double *unused, double *out_6159904890673780485) {
  H_26(state, unused, out_6159904890673780485);
}
void car_h_27(double *state, double *unused, double *out_7140585640463780321) {
  h_27(state, unused, out_7140585640463780321);
}
void car_H_27(double *state, double *unused, double *out_7597305950604171728) {
  H_27(state, unused, out_7597305950604171728);
}
void car_h_29(double *state, double *unused, double *out_5021036999341260248) {
  h_29(state, unused, out_5021036999341260248);
}
void car_H_29(double *state, double *unused, double *out_5883943223734620695) {
  H_29(state, unused, out_5883943223734620695);
}
void car_h_28(double *state, double *unused, double *out_7743901525140257838) {
  h_28(state, unused, out_7743901525140257838);
}
void car_H_28(double *state, double *unused, double *out_7847573495299946946) {
  H_28(state, unused, out_7847573495299946946);
}
void car_h_31(double *state, double *unused, double *out_1722771103625566976) {
  h_31(state, unused, out_1722771103625566976);
}
void car_H_31(double *state, double *unused, double *out_8514689902284754479) {
  H_31(state, unused, out_8514689902284754479);
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
