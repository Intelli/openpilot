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
void err_fun(double *nom_x, double *delta_x, double *out_5160239029106514666) {
   out_5160239029106514666[0] = delta_x[0] + nom_x[0];
   out_5160239029106514666[1] = delta_x[1] + nom_x[1];
   out_5160239029106514666[2] = delta_x[2] + nom_x[2];
   out_5160239029106514666[3] = delta_x[3] + nom_x[3];
   out_5160239029106514666[4] = delta_x[4] + nom_x[4];
   out_5160239029106514666[5] = delta_x[5] + nom_x[5];
   out_5160239029106514666[6] = delta_x[6] + nom_x[6];
   out_5160239029106514666[7] = delta_x[7] + nom_x[7];
   out_5160239029106514666[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6431411527563361110) {
   out_6431411527563361110[0] = -nom_x[0] + true_x[0];
   out_6431411527563361110[1] = -nom_x[1] + true_x[1];
   out_6431411527563361110[2] = -nom_x[2] + true_x[2];
   out_6431411527563361110[3] = -nom_x[3] + true_x[3];
   out_6431411527563361110[4] = -nom_x[4] + true_x[4];
   out_6431411527563361110[5] = -nom_x[5] + true_x[5];
   out_6431411527563361110[6] = -nom_x[6] + true_x[6];
   out_6431411527563361110[7] = -nom_x[7] + true_x[7];
   out_6431411527563361110[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6736064714843669271) {
   out_6736064714843669271[0] = 1.0;
   out_6736064714843669271[1] = 0.0;
   out_6736064714843669271[2] = 0.0;
   out_6736064714843669271[3] = 0.0;
   out_6736064714843669271[4] = 0.0;
   out_6736064714843669271[5] = 0.0;
   out_6736064714843669271[6] = 0.0;
   out_6736064714843669271[7] = 0.0;
   out_6736064714843669271[8] = 0.0;
   out_6736064714843669271[9] = 0.0;
   out_6736064714843669271[10] = 1.0;
   out_6736064714843669271[11] = 0.0;
   out_6736064714843669271[12] = 0.0;
   out_6736064714843669271[13] = 0.0;
   out_6736064714843669271[14] = 0.0;
   out_6736064714843669271[15] = 0.0;
   out_6736064714843669271[16] = 0.0;
   out_6736064714843669271[17] = 0.0;
   out_6736064714843669271[18] = 0.0;
   out_6736064714843669271[19] = 0.0;
   out_6736064714843669271[20] = 1.0;
   out_6736064714843669271[21] = 0.0;
   out_6736064714843669271[22] = 0.0;
   out_6736064714843669271[23] = 0.0;
   out_6736064714843669271[24] = 0.0;
   out_6736064714843669271[25] = 0.0;
   out_6736064714843669271[26] = 0.0;
   out_6736064714843669271[27] = 0.0;
   out_6736064714843669271[28] = 0.0;
   out_6736064714843669271[29] = 0.0;
   out_6736064714843669271[30] = 1.0;
   out_6736064714843669271[31] = 0.0;
   out_6736064714843669271[32] = 0.0;
   out_6736064714843669271[33] = 0.0;
   out_6736064714843669271[34] = 0.0;
   out_6736064714843669271[35] = 0.0;
   out_6736064714843669271[36] = 0.0;
   out_6736064714843669271[37] = 0.0;
   out_6736064714843669271[38] = 0.0;
   out_6736064714843669271[39] = 0.0;
   out_6736064714843669271[40] = 1.0;
   out_6736064714843669271[41] = 0.0;
   out_6736064714843669271[42] = 0.0;
   out_6736064714843669271[43] = 0.0;
   out_6736064714843669271[44] = 0.0;
   out_6736064714843669271[45] = 0.0;
   out_6736064714843669271[46] = 0.0;
   out_6736064714843669271[47] = 0.0;
   out_6736064714843669271[48] = 0.0;
   out_6736064714843669271[49] = 0.0;
   out_6736064714843669271[50] = 1.0;
   out_6736064714843669271[51] = 0.0;
   out_6736064714843669271[52] = 0.0;
   out_6736064714843669271[53] = 0.0;
   out_6736064714843669271[54] = 0.0;
   out_6736064714843669271[55] = 0.0;
   out_6736064714843669271[56] = 0.0;
   out_6736064714843669271[57] = 0.0;
   out_6736064714843669271[58] = 0.0;
   out_6736064714843669271[59] = 0.0;
   out_6736064714843669271[60] = 1.0;
   out_6736064714843669271[61] = 0.0;
   out_6736064714843669271[62] = 0.0;
   out_6736064714843669271[63] = 0.0;
   out_6736064714843669271[64] = 0.0;
   out_6736064714843669271[65] = 0.0;
   out_6736064714843669271[66] = 0.0;
   out_6736064714843669271[67] = 0.0;
   out_6736064714843669271[68] = 0.0;
   out_6736064714843669271[69] = 0.0;
   out_6736064714843669271[70] = 1.0;
   out_6736064714843669271[71] = 0.0;
   out_6736064714843669271[72] = 0.0;
   out_6736064714843669271[73] = 0.0;
   out_6736064714843669271[74] = 0.0;
   out_6736064714843669271[75] = 0.0;
   out_6736064714843669271[76] = 0.0;
   out_6736064714843669271[77] = 0.0;
   out_6736064714843669271[78] = 0.0;
   out_6736064714843669271[79] = 0.0;
   out_6736064714843669271[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4896158582496107655) {
   out_4896158582496107655[0] = state[0];
   out_4896158582496107655[1] = state[1];
   out_4896158582496107655[2] = state[2];
   out_4896158582496107655[3] = state[3];
   out_4896158582496107655[4] = state[4];
   out_4896158582496107655[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4896158582496107655[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4896158582496107655[7] = state[7];
   out_4896158582496107655[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8349825476572880262) {
   out_8349825476572880262[0] = 1;
   out_8349825476572880262[1] = 0;
   out_8349825476572880262[2] = 0;
   out_8349825476572880262[3] = 0;
   out_8349825476572880262[4] = 0;
   out_8349825476572880262[5] = 0;
   out_8349825476572880262[6] = 0;
   out_8349825476572880262[7] = 0;
   out_8349825476572880262[8] = 0;
   out_8349825476572880262[9] = 0;
   out_8349825476572880262[10] = 1;
   out_8349825476572880262[11] = 0;
   out_8349825476572880262[12] = 0;
   out_8349825476572880262[13] = 0;
   out_8349825476572880262[14] = 0;
   out_8349825476572880262[15] = 0;
   out_8349825476572880262[16] = 0;
   out_8349825476572880262[17] = 0;
   out_8349825476572880262[18] = 0;
   out_8349825476572880262[19] = 0;
   out_8349825476572880262[20] = 1;
   out_8349825476572880262[21] = 0;
   out_8349825476572880262[22] = 0;
   out_8349825476572880262[23] = 0;
   out_8349825476572880262[24] = 0;
   out_8349825476572880262[25] = 0;
   out_8349825476572880262[26] = 0;
   out_8349825476572880262[27] = 0;
   out_8349825476572880262[28] = 0;
   out_8349825476572880262[29] = 0;
   out_8349825476572880262[30] = 1;
   out_8349825476572880262[31] = 0;
   out_8349825476572880262[32] = 0;
   out_8349825476572880262[33] = 0;
   out_8349825476572880262[34] = 0;
   out_8349825476572880262[35] = 0;
   out_8349825476572880262[36] = 0;
   out_8349825476572880262[37] = 0;
   out_8349825476572880262[38] = 0;
   out_8349825476572880262[39] = 0;
   out_8349825476572880262[40] = 1;
   out_8349825476572880262[41] = 0;
   out_8349825476572880262[42] = 0;
   out_8349825476572880262[43] = 0;
   out_8349825476572880262[44] = 0;
   out_8349825476572880262[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8349825476572880262[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8349825476572880262[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8349825476572880262[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8349825476572880262[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8349825476572880262[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8349825476572880262[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8349825476572880262[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8349825476572880262[53] = -9.8100000000000005*dt;
   out_8349825476572880262[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8349825476572880262[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8349825476572880262[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8349825476572880262[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8349825476572880262[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8349825476572880262[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8349825476572880262[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8349825476572880262[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8349825476572880262[62] = 0;
   out_8349825476572880262[63] = 0;
   out_8349825476572880262[64] = 0;
   out_8349825476572880262[65] = 0;
   out_8349825476572880262[66] = 0;
   out_8349825476572880262[67] = 0;
   out_8349825476572880262[68] = 0;
   out_8349825476572880262[69] = 0;
   out_8349825476572880262[70] = 1;
   out_8349825476572880262[71] = 0;
   out_8349825476572880262[72] = 0;
   out_8349825476572880262[73] = 0;
   out_8349825476572880262[74] = 0;
   out_8349825476572880262[75] = 0;
   out_8349825476572880262[76] = 0;
   out_8349825476572880262[77] = 0;
   out_8349825476572880262[78] = 0;
   out_8349825476572880262[79] = 0;
   out_8349825476572880262[80] = 1;
}
void h_25(double *state, double *unused, double *out_5540085199088834649) {
   out_5540085199088834649[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1185273318130190534) {
   out_1185273318130190534[0] = 0;
   out_1185273318130190534[1] = 0;
   out_1185273318130190534[2] = 0;
   out_1185273318130190534[3] = 0;
   out_1185273318130190534[4] = 0;
   out_1185273318130190534[5] = 0;
   out_1185273318130190534[6] = 1;
   out_1185273318130190534[7] = 0;
   out_1185273318130190534[8] = 0;
}
void h_24(double *state, double *unused, double *out_2307312474763862199) {
   out_2307312474763862199[0] = state[4];
   out_2307312474763862199[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4743198916932513670) {
   out_4743198916932513670[0] = 0;
   out_4743198916932513670[1] = 0;
   out_4743198916932513670[2] = 0;
   out_4743198916932513670[3] = 0;
   out_4743198916932513670[4] = 1;
   out_4743198916932513670[5] = 0;
   out_4743198916932513670[6] = 0;
   out_4743198916932513670[7] = 0;
   out_4743198916932513670[8] = 0;
   out_4743198916932513670[9] = 0;
   out_4743198916932513670[10] = 0;
   out_4743198916932513670[11] = 0;
   out_4743198916932513670[12] = 0;
   out_4743198916932513670[13] = 0;
   out_4743198916932513670[14] = 1;
   out_4743198916932513670[15] = 0;
   out_4743198916932513670[16] = 0;
   out_4743198916932513670[17] = 0;
}
void h_30(double *state, double *unused, double *out_7498149660614075363) {
   out_7498149660614075363[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3342423011997417664) {
   out_3342423011997417664[0] = 0;
   out_3342423011997417664[1] = 0;
   out_3342423011997417664[2] = 0;
   out_3342423011997417664[3] = 0;
   out_3342423011997417664[4] = 1;
   out_3342423011997417664[5] = 0;
   out_3342423011997417664[6] = 0;
   out_3342423011997417664[7] = 0;
   out_3342423011997417664[8] = 0;
}
void h_26(double *state, double *unused, double *out_63006226185374550) {
   out_63006226185374550[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2556230000743865690) {
   out_2556230000743865690[0] = 0;
   out_2556230000743865690[1] = 0;
   out_2556230000743865690[2] = 0;
   out_2556230000743865690[3] = 0;
   out_2556230000743865690[4] = 0;
   out_2556230000743865690[5] = 0;
   out_2556230000743865690[6] = 0;
   out_2556230000743865690[7] = 1;
   out_2556230000743865690[8] = 0;
}
void h_27(double *state, double *unused, double *out_678394256695065357) {
   out_678394256695065357[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5517186323797842575) {
   out_5517186323797842575[0] = 0;
   out_5517186323797842575[1] = 0;
   out_5517186323797842575[2] = 0;
   out_5517186323797842575[3] = 1;
   out_5517186323797842575[4] = 0;
   out_5517186323797842575[5] = 0;
   out_5517186323797842575[6] = 0;
   out_5517186323797842575[7] = 0;
   out_5517186323797842575[8] = 0;
}
void h_29(double *state, double *unused, double *out_8441659513515737798) {
   out_8441659513515737798[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2832191667683025480) {
   out_2832191667683025480[0] = 0;
   out_2832191667683025480[1] = 1;
   out_2832191667683025480[2] = 0;
   out_2832191667683025480[3] = 0;
   out_2832191667683025480[4] = 0;
   out_2832191667683025480[5] = 0;
   out_2832191667683025480[6] = 0;
   out_2832191667683025480[7] = 0;
   out_2832191667683025480[8] = 0;
}
void h_28(double *state, double *unused, double *out_3715180308139398042) {
   out_3715180308139398042[0] = state[0];
}
void H_28(double *state, double *unused, double *out_868561396117699229) {
   out_868561396117699229[0] = 1;
   out_868561396117699229[1] = 0;
   out_868561396117699229[2] = 0;
   out_868561396117699229[3] = 0;
   out_868561396117699229[4] = 0;
   out_868561396117699229[5] = 0;
   out_868561396117699229[6] = 0;
   out_868561396117699229[7] = 0;
   out_868561396117699229[8] = 0;
}
void h_31(double *state, double *unused, double *out_5489125084978808062) {
   out_5489125084978808062[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3182438102977217166) {
   out_3182438102977217166[0] = 0;
   out_3182438102977217166[1] = 0;
   out_3182438102977217166[2] = 0;
   out_3182438102977217166[3] = 0;
   out_3182438102977217166[4] = 0;
   out_3182438102977217166[5] = 0;
   out_3182438102977217166[6] = 0;
   out_3182438102977217166[7] = 0;
   out_3182438102977217166[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5160239029106514666) {
  err_fun(nom_x, delta_x, out_5160239029106514666);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6431411527563361110) {
  inv_err_fun(nom_x, true_x, out_6431411527563361110);
}
void car_H_mod_fun(double *state, double *out_6736064714843669271) {
  H_mod_fun(state, out_6736064714843669271);
}
void car_f_fun(double *state, double dt, double *out_4896158582496107655) {
  f_fun(state,  dt, out_4896158582496107655);
}
void car_F_fun(double *state, double dt, double *out_8349825476572880262) {
  F_fun(state,  dt, out_8349825476572880262);
}
void car_h_25(double *state, double *unused, double *out_5540085199088834649) {
  h_25(state, unused, out_5540085199088834649);
}
void car_H_25(double *state, double *unused, double *out_1185273318130190534) {
  H_25(state, unused, out_1185273318130190534);
}
void car_h_24(double *state, double *unused, double *out_2307312474763862199) {
  h_24(state, unused, out_2307312474763862199);
}
void car_H_24(double *state, double *unused, double *out_4743198916932513670) {
  H_24(state, unused, out_4743198916932513670);
}
void car_h_30(double *state, double *unused, double *out_7498149660614075363) {
  h_30(state, unused, out_7498149660614075363);
}
void car_H_30(double *state, double *unused, double *out_3342423011997417664) {
  H_30(state, unused, out_3342423011997417664);
}
void car_h_26(double *state, double *unused, double *out_63006226185374550) {
  h_26(state, unused, out_63006226185374550);
}
void car_H_26(double *state, double *unused, double *out_2556230000743865690) {
  H_26(state, unused, out_2556230000743865690);
}
void car_h_27(double *state, double *unused, double *out_678394256695065357) {
  h_27(state, unused, out_678394256695065357);
}
void car_H_27(double *state, double *unused, double *out_5517186323797842575) {
  H_27(state, unused, out_5517186323797842575);
}
void car_h_29(double *state, double *unused, double *out_8441659513515737798) {
  h_29(state, unused, out_8441659513515737798);
}
void car_H_29(double *state, double *unused, double *out_2832191667683025480) {
  H_29(state, unused, out_2832191667683025480);
}
void car_h_28(double *state, double *unused, double *out_3715180308139398042) {
  h_28(state, unused, out_3715180308139398042);
}
void car_H_28(double *state, double *unused, double *out_868561396117699229) {
  H_28(state, unused, out_868561396117699229);
}
void car_h_31(double *state, double *unused, double *out_5489125084978808062) {
  h_31(state, unused, out_5489125084978808062);
}
void car_H_31(double *state, double *unused, double *out_3182438102977217166) {
  H_31(state, unused, out_3182438102977217166);
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
