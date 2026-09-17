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
void err_fun(double *nom_x, double *delta_x, double *out_48334252122072856) {
   out_48334252122072856[0] = delta_x[0] + nom_x[0];
   out_48334252122072856[1] = delta_x[1] + nom_x[1];
   out_48334252122072856[2] = delta_x[2] + nom_x[2];
   out_48334252122072856[3] = delta_x[3] + nom_x[3];
   out_48334252122072856[4] = delta_x[4] + nom_x[4];
   out_48334252122072856[5] = delta_x[5] + nom_x[5];
   out_48334252122072856[6] = delta_x[6] + nom_x[6];
   out_48334252122072856[7] = delta_x[7] + nom_x[7];
   out_48334252122072856[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7186072161804593480) {
   out_7186072161804593480[0] = -nom_x[0] + true_x[0];
   out_7186072161804593480[1] = -nom_x[1] + true_x[1];
   out_7186072161804593480[2] = -nom_x[2] + true_x[2];
   out_7186072161804593480[3] = -nom_x[3] + true_x[3];
   out_7186072161804593480[4] = -nom_x[4] + true_x[4];
   out_7186072161804593480[5] = -nom_x[5] + true_x[5];
   out_7186072161804593480[6] = -nom_x[6] + true_x[6];
   out_7186072161804593480[7] = -nom_x[7] + true_x[7];
   out_7186072161804593480[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8687679256710143695) {
   out_8687679256710143695[0] = 1.0;
   out_8687679256710143695[1] = 0.0;
   out_8687679256710143695[2] = 0.0;
   out_8687679256710143695[3] = 0.0;
   out_8687679256710143695[4] = 0.0;
   out_8687679256710143695[5] = 0.0;
   out_8687679256710143695[6] = 0.0;
   out_8687679256710143695[7] = 0.0;
   out_8687679256710143695[8] = 0.0;
   out_8687679256710143695[9] = 0.0;
   out_8687679256710143695[10] = 1.0;
   out_8687679256710143695[11] = 0.0;
   out_8687679256710143695[12] = 0.0;
   out_8687679256710143695[13] = 0.0;
   out_8687679256710143695[14] = 0.0;
   out_8687679256710143695[15] = 0.0;
   out_8687679256710143695[16] = 0.0;
   out_8687679256710143695[17] = 0.0;
   out_8687679256710143695[18] = 0.0;
   out_8687679256710143695[19] = 0.0;
   out_8687679256710143695[20] = 1.0;
   out_8687679256710143695[21] = 0.0;
   out_8687679256710143695[22] = 0.0;
   out_8687679256710143695[23] = 0.0;
   out_8687679256710143695[24] = 0.0;
   out_8687679256710143695[25] = 0.0;
   out_8687679256710143695[26] = 0.0;
   out_8687679256710143695[27] = 0.0;
   out_8687679256710143695[28] = 0.0;
   out_8687679256710143695[29] = 0.0;
   out_8687679256710143695[30] = 1.0;
   out_8687679256710143695[31] = 0.0;
   out_8687679256710143695[32] = 0.0;
   out_8687679256710143695[33] = 0.0;
   out_8687679256710143695[34] = 0.0;
   out_8687679256710143695[35] = 0.0;
   out_8687679256710143695[36] = 0.0;
   out_8687679256710143695[37] = 0.0;
   out_8687679256710143695[38] = 0.0;
   out_8687679256710143695[39] = 0.0;
   out_8687679256710143695[40] = 1.0;
   out_8687679256710143695[41] = 0.0;
   out_8687679256710143695[42] = 0.0;
   out_8687679256710143695[43] = 0.0;
   out_8687679256710143695[44] = 0.0;
   out_8687679256710143695[45] = 0.0;
   out_8687679256710143695[46] = 0.0;
   out_8687679256710143695[47] = 0.0;
   out_8687679256710143695[48] = 0.0;
   out_8687679256710143695[49] = 0.0;
   out_8687679256710143695[50] = 1.0;
   out_8687679256710143695[51] = 0.0;
   out_8687679256710143695[52] = 0.0;
   out_8687679256710143695[53] = 0.0;
   out_8687679256710143695[54] = 0.0;
   out_8687679256710143695[55] = 0.0;
   out_8687679256710143695[56] = 0.0;
   out_8687679256710143695[57] = 0.0;
   out_8687679256710143695[58] = 0.0;
   out_8687679256710143695[59] = 0.0;
   out_8687679256710143695[60] = 1.0;
   out_8687679256710143695[61] = 0.0;
   out_8687679256710143695[62] = 0.0;
   out_8687679256710143695[63] = 0.0;
   out_8687679256710143695[64] = 0.0;
   out_8687679256710143695[65] = 0.0;
   out_8687679256710143695[66] = 0.0;
   out_8687679256710143695[67] = 0.0;
   out_8687679256710143695[68] = 0.0;
   out_8687679256710143695[69] = 0.0;
   out_8687679256710143695[70] = 1.0;
   out_8687679256710143695[71] = 0.0;
   out_8687679256710143695[72] = 0.0;
   out_8687679256710143695[73] = 0.0;
   out_8687679256710143695[74] = 0.0;
   out_8687679256710143695[75] = 0.0;
   out_8687679256710143695[76] = 0.0;
   out_8687679256710143695[77] = 0.0;
   out_8687679256710143695[78] = 0.0;
   out_8687679256710143695[79] = 0.0;
   out_8687679256710143695[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5882685055959693267) {
   out_5882685055959693267[0] = state[0];
   out_5882685055959693267[1] = state[1];
   out_5882685055959693267[2] = state[2];
   out_5882685055959693267[3] = state[3];
   out_5882685055959693267[4] = state[4];
   out_5882685055959693267[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5882685055959693267[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5882685055959693267[7] = state[7];
   out_5882685055959693267[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2681658964555602350) {
   out_2681658964555602350[0] = 1;
   out_2681658964555602350[1] = 0;
   out_2681658964555602350[2] = 0;
   out_2681658964555602350[3] = 0;
   out_2681658964555602350[4] = 0;
   out_2681658964555602350[5] = 0;
   out_2681658964555602350[6] = 0;
   out_2681658964555602350[7] = 0;
   out_2681658964555602350[8] = 0;
   out_2681658964555602350[9] = 0;
   out_2681658964555602350[10] = 1;
   out_2681658964555602350[11] = 0;
   out_2681658964555602350[12] = 0;
   out_2681658964555602350[13] = 0;
   out_2681658964555602350[14] = 0;
   out_2681658964555602350[15] = 0;
   out_2681658964555602350[16] = 0;
   out_2681658964555602350[17] = 0;
   out_2681658964555602350[18] = 0;
   out_2681658964555602350[19] = 0;
   out_2681658964555602350[20] = 1;
   out_2681658964555602350[21] = 0;
   out_2681658964555602350[22] = 0;
   out_2681658964555602350[23] = 0;
   out_2681658964555602350[24] = 0;
   out_2681658964555602350[25] = 0;
   out_2681658964555602350[26] = 0;
   out_2681658964555602350[27] = 0;
   out_2681658964555602350[28] = 0;
   out_2681658964555602350[29] = 0;
   out_2681658964555602350[30] = 1;
   out_2681658964555602350[31] = 0;
   out_2681658964555602350[32] = 0;
   out_2681658964555602350[33] = 0;
   out_2681658964555602350[34] = 0;
   out_2681658964555602350[35] = 0;
   out_2681658964555602350[36] = 0;
   out_2681658964555602350[37] = 0;
   out_2681658964555602350[38] = 0;
   out_2681658964555602350[39] = 0;
   out_2681658964555602350[40] = 1;
   out_2681658964555602350[41] = 0;
   out_2681658964555602350[42] = 0;
   out_2681658964555602350[43] = 0;
   out_2681658964555602350[44] = 0;
   out_2681658964555602350[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2681658964555602350[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2681658964555602350[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2681658964555602350[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2681658964555602350[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2681658964555602350[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2681658964555602350[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2681658964555602350[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2681658964555602350[53] = -9.8100000000000005*dt;
   out_2681658964555602350[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2681658964555602350[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2681658964555602350[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2681658964555602350[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2681658964555602350[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2681658964555602350[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2681658964555602350[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2681658964555602350[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2681658964555602350[62] = 0;
   out_2681658964555602350[63] = 0;
   out_2681658964555602350[64] = 0;
   out_2681658964555602350[65] = 0;
   out_2681658964555602350[66] = 0;
   out_2681658964555602350[67] = 0;
   out_2681658964555602350[68] = 0;
   out_2681658964555602350[69] = 0;
   out_2681658964555602350[70] = 1;
   out_2681658964555602350[71] = 0;
   out_2681658964555602350[72] = 0;
   out_2681658964555602350[73] = 0;
   out_2681658964555602350[74] = 0;
   out_2681658964555602350[75] = 0;
   out_2681658964555602350[76] = 0;
   out_2681658964555602350[77] = 0;
   out_2681658964555602350[78] = 0;
   out_2681658964555602350[79] = 0;
   out_2681658964555602350[80] = 1;
}
void h_25(double *state, double *unused, double *out_6651581816798785823) {
   out_6651581816798785823[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5593660983917747187) {
   out_5593660983917747187[0] = 0;
   out_5593660983917747187[1] = 0;
   out_5593660983917747187[2] = 0;
   out_5593660983917747187[3] = 0;
   out_5593660983917747187[4] = 0;
   out_5593660983917747187[5] = 0;
   out_5593660983917747187[6] = 1;
   out_5593660983917747187[7] = 0;
   out_5593660983917747187[8] = 0;
}
void h_24(double *state, double *unused, double *out_1538214036161548291) {
   out_1538214036161548291[0] = state[4];
   out_1538214036161548291[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2791584375066039246) {
   out_2791584375066039246[0] = 0;
   out_2791584375066039246[1] = 0;
   out_2791584375066039246[2] = 0;
   out_2791584375066039246[3] = 0;
   out_2791584375066039246[4] = 1;
   out_2791584375066039246[5] = 0;
   out_2791584375066039246[6] = 0;
   out_2791584375066039246[7] = 0;
   out_2791584375066039246[8] = 0;
   out_2791584375066039246[9] = 0;
   out_2791584375066039246[10] = 0;
   out_2791584375066039246[11] = 0;
   out_2791584375066039246[12] = 0;
   out_2791584375066039246[13] = 0;
   out_2791584375066039246[14] = 1;
   out_2791584375066039246[15] = 0;
   out_2791584375066039246[16] = 0;
   out_2791584375066039246[17] = 0;
}
void h_30(double *state, double *unused, double *out_63753890322490660) {
   out_63753890322490660[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3075328025410498560) {
   out_3075328025410498560[0] = 0;
   out_3075328025410498560[1] = 0;
   out_3075328025410498560[2] = 0;
   out_3075328025410498560[3] = 0;
   out_3075328025410498560[4] = 1;
   out_3075328025410498560[5] = 0;
   out_3075328025410498560[6] = 0;
   out_3075328025410498560[7] = 0;
   out_3075328025410498560[8] = 0;
}
void h_26(double *state, double *unused, double *out_5065427157983336305) {
   out_5065427157983336305[0] = state[7];
}
void H_26(double *state, double *unused, double *out_9111579770917748205) {
   out_9111579770917748205[0] = 0;
   out_9111579770917748205[1] = 0;
   out_9111579770917748205[2] = 0;
   out_9111579770917748205[3] = 0;
   out_9111579770917748205[4] = 0;
   out_9111579770917748205[5] = 0;
   out_9111579770917748205[6] = 0;
   out_9111579770917748205[7] = 1;
   out_9111579770917748205[8] = 0;
}
void h_27(double *state, double *unused, double *out_2029395787342677509) {
   out_2029395787342677509[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5250091337210923471) {
   out_5250091337210923471[0] = 0;
   out_5250091337210923471[1] = 0;
   out_5250091337210923471[2] = 0;
   out_5250091337210923471[3] = 1;
   out_5250091337210923471[4] = 0;
   out_5250091337210923471[5] = 0;
   out_5250091337210923471[6] = 0;
   out_5250091337210923471[7] = 0;
   out_5250091337210923471[8] = 0;
}
void h_29(double *state, double *unused, double *out_8654083029546201666) {
   out_8654083029546201666[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2565096681096106376) {
   out_2565096681096106376[0] = 0;
   out_2565096681096106376[1] = 1;
   out_2565096681096106376[2] = 0;
   out_2565096681096106376[3] = 0;
   out_2565096681096106376[4] = 0;
   out_2565096681096106376[5] = 0;
   out_2565096681096106376[6] = 0;
   out_2565096681096106376[7] = 0;
   out_2565096681096106376[8] = 0;
}
void h_28(double *state, double *unused, double *out_3848889700216037579) {
   out_3848889700216037579[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7647495698165636950) {
   out_7647495698165636950[0] = 1;
   out_7647495698165636950[1] = 0;
   out_7647495698165636950[2] = 0;
   out_7647495698165636950[3] = 0;
   out_7647495698165636950[4] = 0;
   out_7647495698165636950[5] = 0;
   out_7647495698165636950[6] = 0;
   out_7647495698165636950[7] = 0;
   out_7647495698165636950[8] = 0;
}
void h_31(double *state, double *unused, double *out_6494395148447656678) {
   out_6494395148447656678[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8485371668684396729) {
   out_8485371668684396729[0] = 0;
   out_8485371668684396729[1] = 0;
   out_8485371668684396729[2] = 0;
   out_8485371668684396729[3] = 0;
   out_8485371668684396729[4] = 0;
   out_8485371668684396729[5] = 0;
   out_8485371668684396729[6] = 0;
   out_8485371668684396729[7] = 0;
   out_8485371668684396729[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_48334252122072856) {
  err_fun(nom_x, delta_x, out_48334252122072856);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7186072161804593480) {
  inv_err_fun(nom_x, true_x, out_7186072161804593480);
}
void car_H_mod_fun(double *state, double *out_8687679256710143695) {
  H_mod_fun(state, out_8687679256710143695);
}
void car_f_fun(double *state, double dt, double *out_5882685055959693267) {
  f_fun(state,  dt, out_5882685055959693267);
}
void car_F_fun(double *state, double dt, double *out_2681658964555602350) {
  F_fun(state,  dt, out_2681658964555602350);
}
void car_h_25(double *state, double *unused, double *out_6651581816798785823) {
  h_25(state, unused, out_6651581816798785823);
}
void car_H_25(double *state, double *unused, double *out_5593660983917747187) {
  H_25(state, unused, out_5593660983917747187);
}
void car_h_24(double *state, double *unused, double *out_1538214036161548291) {
  h_24(state, unused, out_1538214036161548291);
}
void car_H_24(double *state, double *unused, double *out_2791584375066039246) {
  H_24(state, unused, out_2791584375066039246);
}
void car_h_30(double *state, double *unused, double *out_63753890322490660) {
  h_30(state, unused, out_63753890322490660);
}
void car_H_30(double *state, double *unused, double *out_3075328025410498560) {
  H_30(state, unused, out_3075328025410498560);
}
void car_h_26(double *state, double *unused, double *out_5065427157983336305) {
  h_26(state, unused, out_5065427157983336305);
}
void car_H_26(double *state, double *unused, double *out_9111579770917748205) {
  H_26(state, unused, out_9111579770917748205);
}
void car_h_27(double *state, double *unused, double *out_2029395787342677509) {
  h_27(state, unused, out_2029395787342677509);
}
void car_H_27(double *state, double *unused, double *out_5250091337210923471) {
  H_27(state, unused, out_5250091337210923471);
}
void car_h_29(double *state, double *unused, double *out_8654083029546201666) {
  h_29(state, unused, out_8654083029546201666);
}
void car_H_29(double *state, double *unused, double *out_2565096681096106376) {
  H_29(state, unused, out_2565096681096106376);
}
void car_h_28(double *state, double *unused, double *out_3848889700216037579) {
  h_28(state, unused, out_3848889700216037579);
}
void car_H_28(double *state, double *unused, double *out_7647495698165636950) {
  H_28(state, unused, out_7647495698165636950);
}
void car_h_31(double *state, double *unused, double *out_6494395148447656678) {
  h_31(state, unused, out_6494395148447656678);
}
void car_H_31(double *state, double *unused, double *out_8485371668684396729) {
  H_31(state, unused, out_8485371668684396729);
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
