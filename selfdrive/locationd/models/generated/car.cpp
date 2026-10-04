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
void err_fun(double *nom_x, double *delta_x, double *out_2236917899360960475) {
   out_2236917899360960475[0] = delta_x[0] + nom_x[0];
   out_2236917899360960475[1] = delta_x[1] + nom_x[1];
   out_2236917899360960475[2] = delta_x[2] + nom_x[2];
   out_2236917899360960475[3] = delta_x[3] + nom_x[3];
   out_2236917899360960475[4] = delta_x[4] + nom_x[4];
   out_2236917899360960475[5] = delta_x[5] + nom_x[5];
   out_2236917899360960475[6] = delta_x[6] + nom_x[6];
   out_2236917899360960475[7] = delta_x[7] + nom_x[7];
   out_2236917899360960475[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2708070960366344927) {
   out_2708070960366344927[0] = -nom_x[0] + true_x[0];
   out_2708070960366344927[1] = -nom_x[1] + true_x[1];
   out_2708070960366344927[2] = -nom_x[2] + true_x[2];
   out_2708070960366344927[3] = -nom_x[3] + true_x[3];
   out_2708070960366344927[4] = -nom_x[4] + true_x[4];
   out_2708070960366344927[5] = -nom_x[5] + true_x[5];
   out_2708070960366344927[6] = -nom_x[6] + true_x[6];
   out_2708070960366344927[7] = -nom_x[7] + true_x[7];
   out_2708070960366344927[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6800576499473052122) {
   out_6800576499473052122[0] = 1.0;
   out_6800576499473052122[1] = 0.0;
   out_6800576499473052122[2] = 0.0;
   out_6800576499473052122[3] = 0.0;
   out_6800576499473052122[4] = 0.0;
   out_6800576499473052122[5] = 0.0;
   out_6800576499473052122[6] = 0.0;
   out_6800576499473052122[7] = 0.0;
   out_6800576499473052122[8] = 0.0;
   out_6800576499473052122[9] = 0.0;
   out_6800576499473052122[10] = 1.0;
   out_6800576499473052122[11] = 0.0;
   out_6800576499473052122[12] = 0.0;
   out_6800576499473052122[13] = 0.0;
   out_6800576499473052122[14] = 0.0;
   out_6800576499473052122[15] = 0.0;
   out_6800576499473052122[16] = 0.0;
   out_6800576499473052122[17] = 0.0;
   out_6800576499473052122[18] = 0.0;
   out_6800576499473052122[19] = 0.0;
   out_6800576499473052122[20] = 1.0;
   out_6800576499473052122[21] = 0.0;
   out_6800576499473052122[22] = 0.0;
   out_6800576499473052122[23] = 0.0;
   out_6800576499473052122[24] = 0.0;
   out_6800576499473052122[25] = 0.0;
   out_6800576499473052122[26] = 0.0;
   out_6800576499473052122[27] = 0.0;
   out_6800576499473052122[28] = 0.0;
   out_6800576499473052122[29] = 0.0;
   out_6800576499473052122[30] = 1.0;
   out_6800576499473052122[31] = 0.0;
   out_6800576499473052122[32] = 0.0;
   out_6800576499473052122[33] = 0.0;
   out_6800576499473052122[34] = 0.0;
   out_6800576499473052122[35] = 0.0;
   out_6800576499473052122[36] = 0.0;
   out_6800576499473052122[37] = 0.0;
   out_6800576499473052122[38] = 0.0;
   out_6800576499473052122[39] = 0.0;
   out_6800576499473052122[40] = 1.0;
   out_6800576499473052122[41] = 0.0;
   out_6800576499473052122[42] = 0.0;
   out_6800576499473052122[43] = 0.0;
   out_6800576499473052122[44] = 0.0;
   out_6800576499473052122[45] = 0.0;
   out_6800576499473052122[46] = 0.0;
   out_6800576499473052122[47] = 0.0;
   out_6800576499473052122[48] = 0.0;
   out_6800576499473052122[49] = 0.0;
   out_6800576499473052122[50] = 1.0;
   out_6800576499473052122[51] = 0.0;
   out_6800576499473052122[52] = 0.0;
   out_6800576499473052122[53] = 0.0;
   out_6800576499473052122[54] = 0.0;
   out_6800576499473052122[55] = 0.0;
   out_6800576499473052122[56] = 0.0;
   out_6800576499473052122[57] = 0.0;
   out_6800576499473052122[58] = 0.0;
   out_6800576499473052122[59] = 0.0;
   out_6800576499473052122[60] = 1.0;
   out_6800576499473052122[61] = 0.0;
   out_6800576499473052122[62] = 0.0;
   out_6800576499473052122[63] = 0.0;
   out_6800576499473052122[64] = 0.0;
   out_6800576499473052122[65] = 0.0;
   out_6800576499473052122[66] = 0.0;
   out_6800576499473052122[67] = 0.0;
   out_6800576499473052122[68] = 0.0;
   out_6800576499473052122[69] = 0.0;
   out_6800576499473052122[70] = 1.0;
   out_6800576499473052122[71] = 0.0;
   out_6800576499473052122[72] = 0.0;
   out_6800576499473052122[73] = 0.0;
   out_6800576499473052122[74] = 0.0;
   out_6800576499473052122[75] = 0.0;
   out_6800576499473052122[76] = 0.0;
   out_6800576499473052122[77] = 0.0;
   out_6800576499473052122[78] = 0.0;
   out_6800576499473052122[79] = 0.0;
   out_6800576499473052122[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6732064645415141134) {
   out_6732064645415141134[0] = state[0];
   out_6732064645415141134[1] = state[1];
   out_6732064645415141134[2] = state[2];
   out_6732064645415141134[3] = state[3];
   out_6732064645415141134[4] = state[4];
   out_6732064645415141134[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6732064645415141134[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6732064645415141134[7] = state[7];
   out_6732064645415141134[8] = state[8];
}
void F_fun(double *state, double dt, double *out_561713757681768772) {
   out_561713757681768772[0] = 1;
   out_561713757681768772[1] = 0;
   out_561713757681768772[2] = 0;
   out_561713757681768772[3] = 0;
   out_561713757681768772[4] = 0;
   out_561713757681768772[5] = 0;
   out_561713757681768772[6] = 0;
   out_561713757681768772[7] = 0;
   out_561713757681768772[8] = 0;
   out_561713757681768772[9] = 0;
   out_561713757681768772[10] = 1;
   out_561713757681768772[11] = 0;
   out_561713757681768772[12] = 0;
   out_561713757681768772[13] = 0;
   out_561713757681768772[14] = 0;
   out_561713757681768772[15] = 0;
   out_561713757681768772[16] = 0;
   out_561713757681768772[17] = 0;
   out_561713757681768772[18] = 0;
   out_561713757681768772[19] = 0;
   out_561713757681768772[20] = 1;
   out_561713757681768772[21] = 0;
   out_561713757681768772[22] = 0;
   out_561713757681768772[23] = 0;
   out_561713757681768772[24] = 0;
   out_561713757681768772[25] = 0;
   out_561713757681768772[26] = 0;
   out_561713757681768772[27] = 0;
   out_561713757681768772[28] = 0;
   out_561713757681768772[29] = 0;
   out_561713757681768772[30] = 1;
   out_561713757681768772[31] = 0;
   out_561713757681768772[32] = 0;
   out_561713757681768772[33] = 0;
   out_561713757681768772[34] = 0;
   out_561713757681768772[35] = 0;
   out_561713757681768772[36] = 0;
   out_561713757681768772[37] = 0;
   out_561713757681768772[38] = 0;
   out_561713757681768772[39] = 0;
   out_561713757681768772[40] = 1;
   out_561713757681768772[41] = 0;
   out_561713757681768772[42] = 0;
   out_561713757681768772[43] = 0;
   out_561713757681768772[44] = 0;
   out_561713757681768772[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_561713757681768772[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_561713757681768772[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_561713757681768772[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_561713757681768772[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_561713757681768772[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_561713757681768772[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_561713757681768772[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_561713757681768772[53] = -9.8100000000000005*dt;
   out_561713757681768772[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_561713757681768772[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_561713757681768772[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_561713757681768772[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_561713757681768772[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_561713757681768772[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_561713757681768772[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_561713757681768772[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_561713757681768772[62] = 0;
   out_561713757681768772[63] = 0;
   out_561713757681768772[64] = 0;
   out_561713757681768772[65] = 0;
   out_561713757681768772[66] = 0;
   out_561713757681768772[67] = 0;
   out_561713757681768772[68] = 0;
   out_561713757681768772[69] = 0;
   out_561713757681768772[70] = 1;
   out_561713757681768772[71] = 0;
   out_561713757681768772[72] = 0;
   out_561713757681768772[73] = 0;
   out_561713757681768772[74] = 0;
   out_561713757681768772[75] = 0;
   out_561713757681768772[76] = 0;
   out_561713757681768772[77] = 0;
   out_561713757681768772[78] = 0;
   out_561713757681768772[79] = 0;
   out_561713757681768772[80] = 1;
}
void h_25(double *state, double *unused, double *out_1362906194470842416) {
   out_1362906194470842416[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8123186924247007817) {
   out_8123186924247007817[0] = 0;
   out_8123186924247007817[1] = 0;
   out_8123186924247007817[2] = 0;
   out_8123186924247007817[3] = 0;
   out_8123186924247007817[4] = 0;
   out_8123186924247007817[5] = 0;
   out_8123186924247007817[6] = 1;
   out_8123186924247007817[7] = 0;
   out_8123186924247007817[8] = 0;
}
void h_24(double *state, double *unused, double *out_8482783219785419481) {
   out_8482783219785419481[0] = state[4];
   out_8482783219785419481[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4565261325444684681) {
   out_4565261325444684681[0] = 0;
   out_4565261325444684681[1] = 0;
   out_4565261325444684681[2] = 0;
   out_4565261325444684681[3] = 0;
   out_4565261325444684681[4] = 1;
   out_4565261325444684681[5] = 0;
   out_4565261325444684681[6] = 0;
   out_4565261325444684681[7] = 0;
   out_4565261325444684681[8] = 0;
   out_4565261325444684681[9] = 0;
   out_4565261325444684681[10] = 0;
   out_4565261325444684681[11] = 0;
   out_4565261325444684681[12] = 0;
   out_4565261325444684681[13] = 0;
   out_4565261325444684681[14] = 1;
   out_4565261325444684681[15] = 0;
   out_4565261325444684681[16] = 0;
   out_4565261325444684681[17] = 0;
}
void h_30(double *state, double *unused, double *out_1520092862821971561) {
   out_1520092862821971561[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8252525871390247887) {
   out_8252525871390247887[0] = 0;
   out_8252525871390247887[1] = 0;
   out_8252525871390247887[2] = 0;
   out_8252525871390247887[3] = 0;
   out_8252525871390247887[4] = 1;
   out_8252525871390247887[5] = 0;
   out_8252525871390247887[6] = 0;
   out_8252525871390247887[7] = 0;
   out_8252525871390247887[8] = 0;
}
void h_26(double *state, double *unused, double *out_1292459240447881822) {
   out_1292459240447881822[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6582053830588487575) {
   out_6582053830588487575[0] = 0;
   out_6582053830588487575[1] = 0;
   out_6582053830588487575[2] = 0;
   out_6582053830588487575[3] = 0;
   out_6582053830588487575[4] = 0;
   out_6582053830588487575[5] = 0;
   out_6582053830588487575[6] = 0;
   out_6582053830588487575[7] = 1;
   out_6582053830588487575[8] = 0;
}
void h_27(double *state, double *unused, double *out_759590309794364899) {
   out_759590309794364899[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8019454890518878818) {
   out_8019454890518878818[0] = 0;
   out_8019454890518878818[1] = 0;
   out_8019454890518878818[2] = 0;
   out_8019454890518878818[3] = 1;
   out_8019454890518878818[4] = 0;
   out_8019454890518878818[5] = 0;
   out_8019454890518878818[6] = 0;
   out_8019454890518878818[7] = 0;
   out_8019454890518878818[8] = 0;
}
void h_29(double *state, double *unused, double *out_3481580404838874084) {
   out_3481580404838874084[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7742294527075855703) {
   out_7742294527075855703[0] = 0;
   out_7742294527075855703[1] = 1;
   out_7742294527075855703[2] = 0;
   out_7742294527075855703[3] = 0;
   out_7742294527075855703[4] = 0;
   out_7742294527075855703[5] = 0;
   out_7742294527075855703[6] = 0;
   out_7742294527075855703[7] = 0;
   out_7742294527075855703[8] = 0;
}
void h_28(double *state, double *unused, double *out_8705184591908345952) {
   out_8705184591908345952[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5778664255510529452) {
   out_5778664255510529452[0] = 1;
   out_5778664255510529452[1] = 0;
   out_5778664255510529452[2] = 0;
   out_5778664255510529452[3] = 0;
   out_5778664255510529452[4] = 0;
   out_5778664255510529452[5] = 0;
   out_5778664255510529452[6] = 0;
   out_5778664255510529452[7] = 0;
   out_5778664255510529452[8] = 0;
}
void h_31(double *state, double *unused, double *out_6097652569778045909) {
   out_6097652569778045909[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8092540962370047389) {
   out_8092540962370047389[0] = 0;
   out_8092540962370047389[1] = 0;
   out_8092540962370047389[2] = 0;
   out_8092540962370047389[3] = 0;
   out_8092540962370047389[4] = 0;
   out_8092540962370047389[5] = 0;
   out_8092540962370047389[6] = 0;
   out_8092540962370047389[7] = 0;
   out_8092540962370047389[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2236917899360960475) {
  err_fun(nom_x, delta_x, out_2236917899360960475);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2708070960366344927) {
  inv_err_fun(nom_x, true_x, out_2708070960366344927);
}
void car_H_mod_fun(double *state, double *out_6800576499473052122) {
  H_mod_fun(state, out_6800576499473052122);
}
void car_f_fun(double *state, double dt, double *out_6732064645415141134) {
  f_fun(state,  dt, out_6732064645415141134);
}
void car_F_fun(double *state, double dt, double *out_561713757681768772) {
  F_fun(state,  dt, out_561713757681768772);
}
void car_h_25(double *state, double *unused, double *out_1362906194470842416) {
  h_25(state, unused, out_1362906194470842416);
}
void car_H_25(double *state, double *unused, double *out_8123186924247007817) {
  H_25(state, unused, out_8123186924247007817);
}
void car_h_24(double *state, double *unused, double *out_8482783219785419481) {
  h_24(state, unused, out_8482783219785419481);
}
void car_H_24(double *state, double *unused, double *out_4565261325444684681) {
  H_24(state, unused, out_4565261325444684681);
}
void car_h_30(double *state, double *unused, double *out_1520092862821971561) {
  h_30(state, unused, out_1520092862821971561);
}
void car_H_30(double *state, double *unused, double *out_8252525871390247887) {
  H_30(state, unused, out_8252525871390247887);
}
void car_h_26(double *state, double *unused, double *out_1292459240447881822) {
  h_26(state, unused, out_1292459240447881822);
}
void car_H_26(double *state, double *unused, double *out_6582053830588487575) {
  H_26(state, unused, out_6582053830588487575);
}
void car_h_27(double *state, double *unused, double *out_759590309794364899) {
  h_27(state, unused, out_759590309794364899);
}
void car_H_27(double *state, double *unused, double *out_8019454890518878818) {
  H_27(state, unused, out_8019454890518878818);
}
void car_h_29(double *state, double *unused, double *out_3481580404838874084) {
  h_29(state, unused, out_3481580404838874084);
}
void car_H_29(double *state, double *unused, double *out_7742294527075855703) {
  H_29(state, unused, out_7742294527075855703);
}
void car_h_28(double *state, double *unused, double *out_8705184591908345952) {
  h_28(state, unused, out_8705184591908345952);
}
void car_H_28(double *state, double *unused, double *out_5778664255510529452) {
  H_28(state, unused, out_5778664255510529452);
}
void car_h_31(double *state, double *unused, double *out_6097652569778045909) {
  h_31(state, unused, out_6097652569778045909);
}
void car_H_31(double *state, double *unused, double *out_8092540962370047389) {
  H_31(state, unused, out_8092540962370047389);
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
