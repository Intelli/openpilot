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
void err_fun(double *nom_x, double *delta_x, double *out_2579147921043217820) {
   out_2579147921043217820[0] = delta_x[0] + nom_x[0];
   out_2579147921043217820[1] = delta_x[1] + nom_x[1];
   out_2579147921043217820[2] = delta_x[2] + nom_x[2];
   out_2579147921043217820[3] = delta_x[3] + nom_x[3];
   out_2579147921043217820[4] = delta_x[4] + nom_x[4];
   out_2579147921043217820[5] = delta_x[5] + nom_x[5];
   out_2579147921043217820[6] = delta_x[6] + nom_x[6];
   out_2579147921043217820[7] = delta_x[7] + nom_x[7];
   out_2579147921043217820[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4595464121730668566) {
   out_4595464121730668566[0] = -nom_x[0] + true_x[0];
   out_4595464121730668566[1] = -nom_x[1] + true_x[1];
   out_4595464121730668566[2] = -nom_x[2] + true_x[2];
   out_4595464121730668566[3] = -nom_x[3] + true_x[3];
   out_4595464121730668566[4] = -nom_x[4] + true_x[4];
   out_4595464121730668566[5] = -nom_x[5] + true_x[5];
   out_4595464121730668566[6] = -nom_x[6] + true_x[6];
   out_4595464121730668566[7] = -nom_x[7] + true_x[7];
   out_4595464121730668566[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4312954293014229808) {
   out_4312954293014229808[0] = 1.0;
   out_4312954293014229808[1] = 0.0;
   out_4312954293014229808[2] = 0.0;
   out_4312954293014229808[3] = 0.0;
   out_4312954293014229808[4] = 0.0;
   out_4312954293014229808[5] = 0.0;
   out_4312954293014229808[6] = 0.0;
   out_4312954293014229808[7] = 0.0;
   out_4312954293014229808[8] = 0.0;
   out_4312954293014229808[9] = 0.0;
   out_4312954293014229808[10] = 1.0;
   out_4312954293014229808[11] = 0.0;
   out_4312954293014229808[12] = 0.0;
   out_4312954293014229808[13] = 0.0;
   out_4312954293014229808[14] = 0.0;
   out_4312954293014229808[15] = 0.0;
   out_4312954293014229808[16] = 0.0;
   out_4312954293014229808[17] = 0.0;
   out_4312954293014229808[18] = 0.0;
   out_4312954293014229808[19] = 0.0;
   out_4312954293014229808[20] = 1.0;
   out_4312954293014229808[21] = 0.0;
   out_4312954293014229808[22] = 0.0;
   out_4312954293014229808[23] = 0.0;
   out_4312954293014229808[24] = 0.0;
   out_4312954293014229808[25] = 0.0;
   out_4312954293014229808[26] = 0.0;
   out_4312954293014229808[27] = 0.0;
   out_4312954293014229808[28] = 0.0;
   out_4312954293014229808[29] = 0.0;
   out_4312954293014229808[30] = 1.0;
   out_4312954293014229808[31] = 0.0;
   out_4312954293014229808[32] = 0.0;
   out_4312954293014229808[33] = 0.0;
   out_4312954293014229808[34] = 0.0;
   out_4312954293014229808[35] = 0.0;
   out_4312954293014229808[36] = 0.0;
   out_4312954293014229808[37] = 0.0;
   out_4312954293014229808[38] = 0.0;
   out_4312954293014229808[39] = 0.0;
   out_4312954293014229808[40] = 1.0;
   out_4312954293014229808[41] = 0.0;
   out_4312954293014229808[42] = 0.0;
   out_4312954293014229808[43] = 0.0;
   out_4312954293014229808[44] = 0.0;
   out_4312954293014229808[45] = 0.0;
   out_4312954293014229808[46] = 0.0;
   out_4312954293014229808[47] = 0.0;
   out_4312954293014229808[48] = 0.0;
   out_4312954293014229808[49] = 0.0;
   out_4312954293014229808[50] = 1.0;
   out_4312954293014229808[51] = 0.0;
   out_4312954293014229808[52] = 0.0;
   out_4312954293014229808[53] = 0.0;
   out_4312954293014229808[54] = 0.0;
   out_4312954293014229808[55] = 0.0;
   out_4312954293014229808[56] = 0.0;
   out_4312954293014229808[57] = 0.0;
   out_4312954293014229808[58] = 0.0;
   out_4312954293014229808[59] = 0.0;
   out_4312954293014229808[60] = 1.0;
   out_4312954293014229808[61] = 0.0;
   out_4312954293014229808[62] = 0.0;
   out_4312954293014229808[63] = 0.0;
   out_4312954293014229808[64] = 0.0;
   out_4312954293014229808[65] = 0.0;
   out_4312954293014229808[66] = 0.0;
   out_4312954293014229808[67] = 0.0;
   out_4312954293014229808[68] = 0.0;
   out_4312954293014229808[69] = 0.0;
   out_4312954293014229808[70] = 1.0;
   out_4312954293014229808[71] = 0.0;
   out_4312954293014229808[72] = 0.0;
   out_4312954293014229808[73] = 0.0;
   out_4312954293014229808[74] = 0.0;
   out_4312954293014229808[75] = 0.0;
   out_4312954293014229808[76] = 0.0;
   out_4312954293014229808[77] = 0.0;
   out_4312954293014229808[78] = 0.0;
   out_4312954293014229808[79] = 0.0;
   out_4312954293014229808[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3633989389734511779) {
   out_3633989389734511779[0] = state[0];
   out_3633989389734511779[1] = state[1];
   out_3633989389734511779[2] = state[2];
   out_3633989389734511779[3] = state[3];
   out_3633989389734511779[4] = state[4];
   out_3633989389734511779[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3633989389734511779[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3633989389734511779[7] = state[7];
   out_3633989389734511779[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3520723824960767419) {
   out_3520723824960767419[0] = 1;
   out_3520723824960767419[1] = 0;
   out_3520723824960767419[2] = 0;
   out_3520723824960767419[3] = 0;
   out_3520723824960767419[4] = 0;
   out_3520723824960767419[5] = 0;
   out_3520723824960767419[6] = 0;
   out_3520723824960767419[7] = 0;
   out_3520723824960767419[8] = 0;
   out_3520723824960767419[9] = 0;
   out_3520723824960767419[10] = 1;
   out_3520723824960767419[11] = 0;
   out_3520723824960767419[12] = 0;
   out_3520723824960767419[13] = 0;
   out_3520723824960767419[14] = 0;
   out_3520723824960767419[15] = 0;
   out_3520723824960767419[16] = 0;
   out_3520723824960767419[17] = 0;
   out_3520723824960767419[18] = 0;
   out_3520723824960767419[19] = 0;
   out_3520723824960767419[20] = 1;
   out_3520723824960767419[21] = 0;
   out_3520723824960767419[22] = 0;
   out_3520723824960767419[23] = 0;
   out_3520723824960767419[24] = 0;
   out_3520723824960767419[25] = 0;
   out_3520723824960767419[26] = 0;
   out_3520723824960767419[27] = 0;
   out_3520723824960767419[28] = 0;
   out_3520723824960767419[29] = 0;
   out_3520723824960767419[30] = 1;
   out_3520723824960767419[31] = 0;
   out_3520723824960767419[32] = 0;
   out_3520723824960767419[33] = 0;
   out_3520723824960767419[34] = 0;
   out_3520723824960767419[35] = 0;
   out_3520723824960767419[36] = 0;
   out_3520723824960767419[37] = 0;
   out_3520723824960767419[38] = 0;
   out_3520723824960767419[39] = 0;
   out_3520723824960767419[40] = 1;
   out_3520723824960767419[41] = 0;
   out_3520723824960767419[42] = 0;
   out_3520723824960767419[43] = 0;
   out_3520723824960767419[44] = 0;
   out_3520723824960767419[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3520723824960767419[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3520723824960767419[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3520723824960767419[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3520723824960767419[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3520723824960767419[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3520723824960767419[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3520723824960767419[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3520723824960767419[53] = -9.8100000000000005*dt;
   out_3520723824960767419[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3520723824960767419[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3520723824960767419[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3520723824960767419[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3520723824960767419[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3520723824960767419[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3520723824960767419[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3520723824960767419[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3520723824960767419[62] = 0;
   out_3520723824960767419[63] = 0;
   out_3520723824960767419[64] = 0;
   out_3520723824960767419[65] = 0;
   out_3520723824960767419[66] = 0;
   out_3520723824960767419[67] = 0;
   out_3520723824960767419[68] = 0;
   out_3520723824960767419[69] = 0;
   out_3520723824960767419[70] = 1;
   out_3520723824960767419[71] = 0;
   out_3520723824960767419[72] = 0;
   out_3520723824960767419[73] = 0;
   out_3520723824960767419[74] = 0;
   out_3520723824960767419[75] = 0;
   out_3520723824960767419[76] = 0;
   out_3520723824960767419[77] = 0;
   out_3520723824960767419[78] = 0;
   out_3520723824960767419[79] = 0;
   out_3520723824960767419[80] = 1;
}
void h_25(double *state, double *unused, double *out_4250949531156864346) {
   out_4250949531156864346[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6460113230291610220) {
   out_6460113230291610220[0] = 0;
   out_6460113230291610220[1] = 0;
   out_6460113230291610220[2] = 0;
   out_6460113230291610220[3] = 0;
   out_6460113230291610220[4] = 0;
   out_6460113230291610220[5] = 0;
   out_6460113230291610220[6] = 1;
   out_6460113230291610220[7] = 0;
   out_6460113230291610220[8] = 0;
}
void h_24(double *state, double *unused, double *out_5654665218976778104) {
   out_5654665218976778104[0] = state[4];
   out_5654665218976778104[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2767951955777585005) {
   out_2767951955777585005[0] = 0;
   out_2767951955777585005[1] = 0;
   out_2767951955777585005[2] = 0;
   out_2767951955777585005[3] = 0;
   out_2767951955777585005[4] = 1;
   out_2767951955777585005[5] = 0;
   out_2767951955777585005[6] = 0;
   out_2767951955777585005[7] = 0;
   out_2767951955777585005[8] = 0;
   out_2767951955777585005[9] = 0;
   out_2767951955777585005[10] = 0;
   out_2767951955777585005[11] = 0;
   out_2767951955777585005[12] = 0;
   out_2767951955777585005[13] = 0;
   out_2767951955777585005[14] = 1;
   out_2767951955777585005[15] = 0;
   out_2767951955777585005[16] = 0;
   out_2767951955777585005[17] = 0;
}
void h_30(double *state, double *unused, double *out_8881186493863702063) {
   out_8881186493863702063[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7458934513290333198) {
   out_7458934513290333198[0] = 0;
   out_7458934513290333198[1] = 0;
   out_7458934513290333198[2] = 0;
   out_7458934513290333198[3] = 0;
   out_7458934513290333198[4] = 1;
   out_7458934513290333198[5] = 0;
   out_7458934513290333198[6] = 0;
   out_7458934513290333198[7] = 0;
   out_7458934513290333198[8] = 0;
}
void h_26(double *state, double *unused, double *out_3922827708764892718) {
   out_3922827708764892718[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8245127524543885172) {
   out_8245127524543885172[0] = 0;
   out_8245127524543885172[1] = 0;
   out_8245127524543885172[2] = 0;
   out_8245127524543885172[3] = 0;
   out_8245127524543885172[4] = 0;
   out_8245127524543885172[5] = 0;
   out_8245127524543885172[6] = 0;
   out_8245127524543885172[7] = 1;
   out_8245127524543885172[8] = 0;
}
void h_27(double *state, double *unused, double *out_8093275106819492880) {
   out_8093275106819492880[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8764215489235275201) {
   out_8764215489235275201[0] = 0;
   out_8764215489235275201[1] = 0;
   out_8764215489235275201[2] = 0;
   out_8764215489235275201[3] = 1;
   out_8764215489235275201[4] = 0;
   out_8764215489235275201[5] = 0;
   out_8764215489235275201[6] = 0;
   out_8764215489235275201[7] = 0;
   out_8764215489235275201[8] = 0;
}
void h_29(double *state, double *unused, double *out_3582633740539707800) {
   out_3582633740539707800[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7969165857604725382) {
   out_7969165857604725382[0] = 0;
   out_7969165857604725382[1] = 1;
   out_7969165857604725382[2] = 0;
   out_7969165857604725382[3] = 0;
   out_7969165857604725382[4] = 0;
   out_7969165857604725382[5] = 0;
   out_7969165857604725382[6] = 0;
   out_7969165857604725382[7] = 0;
   out_7969165857604725382[8] = 0;
}
void h_28(double *state, double *unused, double *out_1947812147245832083) {
   out_1947812147245832083[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2886766840535194808) {
   out_2886766840535194808[0] = 1;
   out_2886766840535194808[1] = 0;
   out_2886766840535194808[2] = 0;
   out_2886766840535194808[3] = 0;
   out_2886766840535194808[4] = 0;
   out_2886766840535194808[5] = 0;
   out_2886766840535194808[6] = 0;
   out_2886766840535194808[7] = 0;
   out_2886766840535194808[8] = 0;
}
void h_31(double *state, double *unused, double *out_5331683117659666084) {
   out_5331683117659666084[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7618919422310533696) {
   out_7618919422310533696[0] = 0;
   out_7618919422310533696[1] = 0;
   out_7618919422310533696[2] = 0;
   out_7618919422310533696[3] = 0;
   out_7618919422310533696[4] = 0;
   out_7618919422310533696[5] = 0;
   out_7618919422310533696[6] = 0;
   out_7618919422310533696[7] = 0;
   out_7618919422310533696[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2579147921043217820) {
  err_fun(nom_x, delta_x, out_2579147921043217820);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4595464121730668566) {
  inv_err_fun(nom_x, true_x, out_4595464121730668566);
}
void car_H_mod_fun(double *state, double *out_4312954293014229808) {
  H_mod_fun(state, out_4312954293014229808);
}
void car_f_fun(double *state, double dt, double *out_3633989389734511779) {
  f_fun(state,  dt, out_3633989389734511779);
}
void car_F_fun(double *state, double dt, double *out_3520723824960767419) {
  F_fun(state,  dt, out_3520723824960767419);
}
void car_h_25(double *state, double *unused, double *out_4250949531156864346) {
  h_25(state, unused, out_4250949531156864346);
}
void car_H_25(double *state, double *unused, double *out_6460113230291610220) {
  H_25(state, unused, out_6460113230291610220);
}
void car_h_24(double *state, double *unused, double *out_5654665218976778104) {
  h_24(state, unused, out_5654665218976778104);
}
void car_H_24(double *state, double *unused, double *out_2767951955777585005) {
  H_24(state, unused, out_2767951955777585005);
}
void car_h_30(double *state, double *unused, double *out_8881186493863702063) {
  h_30(state, unused, out_8881186493863702063);
}
void car_H_30(double *state, double *unused, double *out_7458934513290333198) {
  H_30(state, unused, out_7458934513290333198);
}
void car_h_26(double *state, double *unused, double *out_3922827708764892718) {
  h_26(state, unused, out_3922827708764892718);
}
void car_H_26(double *state, double *unused, double *out_8245127524543885172) {
  H_26(state, unused, out_8245127524543885172);
}
void car_h_27(double *state, double *unused, double *out_8093275106819492880) {
  h_27(state, unused, out_8093275106819492880);
}
void car_H_27(double *state, double *unused, double *out_8764215489235275201) {
  H_27(state, unused, out_8764215489235275201);
}
void car_h_29(double *state, double *unused, double *out_3582633740539707800) {
  h_29(state, unused, out_3582633740539707800);
}
void car_H_29(double *state, double *unused, double *out_7969165857604725382) {
  H_29(state, unused, out_7969165857604725382);
}
void car_h_28(double *state, double *unused, double *out_1947812147245832083) {
  h_28(state, unused, out_1947812147245832083);
}
void car_H_28(double *state, double *unused, double *out_2886766840535194808) {
  H_28(state, unused, out_2886766840535194808);
}
void car_h_31(double *state, double *unused, double *out_5331683117659666084) {
  h_31(state, unused, out_5331683117659666084);
}
void car_H_31(double *state, double *unused, double *out_7618919422310533696) {
  H_31(state, unused, out_7618919422310533696);
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
