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
void err_fun(double *nom_x, double *delta_x, double *out_445019409688598964) {
   out_445019409688598964[0] = delta_x[0] + nom_x[0];
   out_445019409688598964[1] = delta_x[1] + nom_x[1];
   out_445019409688598964[2] = delta_x[2] + nom_x[2];
   out_445019409688598964[3] = delta_x[3] + nom_x[3];
   out_445019409688598964[4] = delta_x[4] + nom_x[4];
   out_445019409688598964[5] = delta_x[5] + nom_x[5];
   out_445019409688598964[6] = delta_x[6] + nom_x[6];
   out_445019409688598964[7] = delta_x[7] + nom_x[7];
   out_445019409688598964[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4351151372455830383) {
   out_4351151372455830383[0] = -nom_x[0] + true_x[0];
   out_4351151372455830383[1] = -nom_x[1] + true_x[1];
   out_4351151372455830383[2] = -nom_x[2] + true_x[2];
   out_4351151372455830383[3] = -nom_x[3] + true_x[3];
   out_4351151372455830383[4] = -nom_x[4] + true_x[4];
   out_4351151372455830383[5] = -nom_x[5] + true_x[5];
   out_4351151372455830383[6] = -nom_x[6] + true_x[6];
   out_4351151372455830383[7] = -nom_x[7] + true_x[7];
   out_4351151372455830383[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_482292932446809381) {
   out_482292932446809381[0] = 1.0;
   out_482292932446809381[1] = 0.0;
   out_482292932446809381[2] = 0.0;
   out_482292932446809381[3] = 0.0;
   out_482292932446809381[4] = 0.0;
   out_482292932446809381[5] = 0.0;
   out_482292932446809381[6] = 0.0;
   out_482292932446809381[7] = 0.0;
   out_482292932446809381[8] = 0.0;
   out_482292932446809381[9] = 0.0;
   out_482292932446809381[10] = 1.0;
   out_482292932446809381[11] = 0.0;
   out_482292932446809381[12] = 0.0;
   out_482292932446809381[13] = 0.0;
   out_482292932446809381[14] = 0.0;
   out_482292932446809381[15] = 0.0;
   out_482292932446809381[16] = 0.0;
   out_482292932446809381[17] = 0.0;
   out_482292932446809381[18] = 0.0;
   out_482292932446809381[19] = 0.0;
   out_482292932446809381[20] = 1.0;
   out_482292932446809381[21] = 0.0;
   out_482292932446809381[22] = 0.0;
   out_482292932446809381[23] = 0.0;
   out_482292932446809381[24] = 0.0;
   out_482292932446809381[25] = 0.0;
   out_482292932446809381[26] = 0.0;
   out_482292932446809381[27] = 0.0;
   out_482292932446809381[28] = 0.0;
   out_482292932446809381[29] = 0.0;
   out_482292932446809381[30] = 1.0;
   out_482292932446809381[31] = 0.0;
   out_482292932446809381[32] = 0.0;
   out_482292932446809381[33] = 0.0;
   out_482292932446809381[34] = 0.0;
   out_482292932446809381[35] = 0.0;
   out_482292932446809381[36] = 0.0;
   out_482292932446809381[37] = 0.0;
   out_482292932446809381[38] = 0.0;
   out_482292932446809381[39] = 0.0;
   out_482292932446809381[40] = 1.0;
   out_482292932446809381[41] = 0.0;
   out_482292932446809381[42] = 0.0;
   out_482292932446809381[43] = 0.0;
   out_482292932446809381[44] = 0.0;
   out_482292932446809381[45] = 0.0;
   out_482292932446809381[46] = 0.0;
   out_482292932446809381[47] = 0.0;
   out_482292932446809381[48] = 0.0;
   out_482292932446809381[49] = 0.0;
   out_482292932446809381[50] = 1.0;
   out_482292932446809381[51] = 0.0;
   out_482292932446809381[52] = 0.0;
   out_482292932446809381[53] = 0.0;
   out_482292932446809381[54] = 0.0;
   out_482292932446809381[55] = 0.0;
   out_482292932446809381[56] = 0.0;
   out_482292932446809381[57] = 0.0;
   out_482292932446809381[58] = 0.0;
   out_482292932446809381[59] = 0.0;
   out_482292932446809381[60] = 1.0;
   out_482292932446809381[61] = 0.0;
   out_482292932446809381[62] = 0.0;
   out_482292932446809381[63] = 0.0;
   out_482292932446809381[64] = 0.0;
   out_482292932446809381[65] = 0.0;
   out_482292932446809381[66] = 0.0;
   out_482292932446809381[67] = 0.0;
   out_482292932446809381[68] = 0.0;
   out_482292932446809381[69] = 0.0;
   out_482292932446809381[70] = 1.0;
   out_482292932446809381[71] = 0.0;
   out_482292932446809381[72] = 0.0;
   out_482292932446809381[73] = 0.0;
   out_482292932446809381[74] = 0.0;
   out_482292932446809381[75] = 0.0;
   out_482292932446809381[76] = 0.0;
   out_482292932446809381[77] = 0.0;
   out_482292932446809381[78] = 0.0;
   out_482292932446809381[79] = 0.0;
   out_482292932446809381[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3036930739161912371) {
   out_3036930739161912371[0] = state[0];
   out_3036930739161912371[1] = state[1];
   out_3036930739161912371[2] = state[2];
   out_3036930739161912371[3] = state[3];
   out_3036930739161912371[4] = state[4];
   out_3036930739161912371[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3036930739161912371[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3036930739161912371[7] = state[7];
   out_3036930739161912371[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4607213455717215037) {
   out_4607213455717215037[0] = 1;
   out_4607213455717215037[1] = 0;
   out_4607213455717215037[2] = 0;
   out_4607213455717215037[3] = 0;
   out_4607213455717215037[4] = 0;
   out_4607213455717215037[5] = 0;
   out_4607213455717215037[6] = 0;
   out_4607213455717215037[7] = 0;
   out_4607213455717215037[8] = 0;
   out_4607213455717215037[9] = 0;
   out_4607213455717215037[10] = 1;
   out_4607213455717215037[11] = 0;
   out_4607213455717215037[12] = 0;
   out_4607213455717215037[13] = 0;
   out_4607213455717215037[14] = 0;
   out_4607213455717215037[15] = 0;
   out_4607213455717215037[16] = 0;
   out_4607213455717215037[17] = 0;
   out_4607213455717215037[18] = 0;
   out_4607213455717215037[19] = 0;
   out_4607213455717215037[20] = 1;
   out_4607213455717215037[21] = 0;
   out_4607213455717215037[22] = 0;
   out_4607213455717215037[23] = 0;
   out_4607213455717215037[24] = 0;
   out_4607213455717215037[25] = 0;
   out_4607213455717215037[26] = 0;
   out_4607213455717215037[27] = 0;
   out_4607213455717215037[28] = 0;
   out_4607213455717215037[29] = 0;
   out_4607213455717215037[30] = 1;
   out_4607213455717215037[31] = 0;
   out_4607213455717215037[32] = 0;
   out_4607213455717215037[33] = 0;
   out_4607213455717215037[34] = 0;
   out_4607213455717215037[35] = 0;
   out_4607213455717215037[36] = 0;
   out_4607213455717215037[37] = 0;
   out_4607213455717215037[38] = 0;
   out_4607213455717215037[39] = 0;
   out_4607213455717215037[40] = 1;
   out_4607213455717215037[41] = 0;
   out_4607213455717215037[42] = 0;
   out_4607213455717215037[43] = 0;
   out_4607213455717215037[44] = 0;
   out_4607213455717215037[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4607213455717215037[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4607213455717215037[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4607213455717215037[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4607213455717215037[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4607213455717215037[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4607213455717215037[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4607213455717215037[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4607213455717215037[53] = -9.8100000000000005*dt;
   out_4607213455717215037[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4607213455717215037[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4607213455717215037[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4607213455717215037[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4607213455717215037[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4607213455717215037[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4607213455717215037[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4607213455717215037[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4607213455717215037[62] = 0;
   out_4607213455717215037[63] = 0;
   out_4607213455717215037[64] = 0;
   out_4607213455717215037[65] = 0;
   out_4607213455717215037[66] = 0;
   out_4607213455717215037[67] = 0;
   out_4607213455717215037[68] = 0;
   out_4607213455717215037[69] = 0;
   out_4607213455717215037[70] = 1;
   out_4607213455717215037[71] = 0;
   out_4607213455717215037[72] = 0;
   out_4607213455717215037[73] = 0;
   out_4607213455717215037[74] = 0;
   out_4607213455717215037[75] = 0;
   out_4607213455717215037[76] = 0;
   out_4607213455717215037[77] = 0;
   out_4607213455717215037[78] = 0;
   out_4607213455717215037[79] = 0;
   out_4607213455717215037[80] = 1;
}
void h_25(double *state, double *unused, double *out_335506616585222898) {
   out_335506616585222898[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4005341571092174529) {
   out_4005341571092174529[0] = 0;
   out_4005341571092174529[1] = 0;
   out_4005341571092174529[2] = 0;
   out_4005341571092174529[3] = 0;
   out_4005341571092174529[4] = 0;
   out_4005341571092174529[5] = 0;
   out_4005341571092174529[6] = 1;
   out_4005341571092174529[7] = 0;
   out_4005341571092174529[8] = 0;
}
void h_24(double *state, double *unused, double *out_3915395329659002282) {
   out_3915395329659002282[0] = state[4];
   out_3915395329659002282[1] = state[5];
}
void H_24(double *state, double *unused, double *out_447415972289851393) {
   out_447415972289851393[0] = 0;
   out_447415972289851393[1] = 0;
   out_447415972289851393[2] = 0;
   out_447415972289851393[3] = 0;
   out_447415972289851393[4] = 1;
   out_447415972289851393[5] = 0;
   out_447415972289851393[6] = 0;
   out_447415972289851393[7] = 0;
   out_447415972289851393[8] = 0;
   out_447415972289851393[9] = 0;
   out_447415972289851393[10] = 0;
   out_447415972289851393[11] = 0;
   out_447415972289851393[12] = 0;
   out_447415972289851393[13] = 0;
   out_447415972289851393[14] = 1;
   out_447415972289851393[15] = 0;
   out_447415972289851393[16] = 0;
   out_447415972289851393[17] = 0;
}
void h_30(double *state, double *unused, double *out_4338044828683651119) {
   out_4338044828683651119[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1487008612584925902) {
   out_1487008612584925902[0] = 0;
   out_1487008612584925902[1] = 0;
   out_1487008612584925902[2] = 0;
   out_1487008612584925902[3] = 0;
   out_1487008612584925902[4] = 1;
   out_1487008612584925902[5] = 0;
   out_1487008612584925902[6] = 0;
   out_1487008612584925902[7] = 0;
   out_1487008612584925902[8] = 0;
}
void h_26(double *state, double *unused, double *out_1764474607049543271) {
   out_1764474607049543271[0] = state[7];
}
void H_26(double *state, double *unused, double *out_700815601331373928) {
   out_700815601331373928[0] = 0;
   out_700815601331373928[1] = 0;
   out_700815601331373928[2] = 0;
   out_700815601331373928[3] = 0;
   out_700815601331373928[4] = 0;
   out_700815601331373928[5] = 0;
   out_700815601331373928[6] = 0;
   out_700815601331373928[7] = 1;
   out_700815601331373928[8] = 0;
}
void h_27(double *state, double *unused, double *out_4666166651075622747) {
   out_4666166651075622747[0] = state[3];
}
void H_27(double *state, double *unused, double *out_736585458599017315) {
   out_736585458599017315[0] = 0;
   out_736585458599017315[1] = 0;
   out_736585458599017315[2] = 0;
   out_736585458599017315[3] = 1;
   out_736585458599017315[4] = 0;
   out_736585458599017315[5] = 0;
   out_736585458599017315[6] = 0;
   out_736585458599017315[7] = 0;
   out_736585458599017315[8] = 0;
}
void h_29(double *state, double *unused, double *out_4941360713360128636) {
   out_4941360713360128636[0] = state[1];
}
void H_29(double *state, double *unused, double *out_976777268270533718) {
   out_976777268270533718[0] = 0;
   out_976777268270533718[1] = 1;
   out_976777268270533718[2] = 0;
   out_976777268270533718[3] = 0;
   out_976777268270533718[4] = 0;
   out_976777268270533718[5] = 0;
   out_976777268270533718[6] = 0;
   out_976777268270533718[7] = 0;
   out_976777268270533718[8] = 0;
}
void h_28(double *state, double *unused, double *out_8778904154973083224) {
   out_8778904154973083224[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6059176285340064292) {
   out_6059176285340064292[0] = 1;
   out_6059176285340064292[1] = 0;
   out_6059176285340064292[2] = 0;
   out_6059176285340064292[3] = 0;
   out_6059176285340064292[4] = 0;
   out_6059176285340064292[5] = 0;
   out_6059176285340064292[6] = 0;
   out_6059176285340064292[7] = 0;
   out_6059176285340064292[8] = 0;
}
void h_31(double *state, double *unused, double *out_1115124776043660269) {
   out_1115124776043660269[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3071333679419642724) {
   out_3071333679419642724[0] = 0;
   out_3071333679419642724[1] = 0;
   out_3071333679419642724[2] = 0;
   out_3071333679419642724[3] = 0;
   out_3071333679419642724[4] = 0;
   out_3071333679419642724[5] = 0;
   out_3071333679419642724[6] = 0;
   out_3071333679419642724[7] = 0;
   out_3071333679419642724[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_445019409688598964) {
  err_fun(nom_x, delta_x, out_445019409688598964);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4351151372455830383) {
  inv_err_fun(nom_x, true_x, out_4351151372455830383);
}
void car_H_mod_fun(double *state, double *out_482292932446809381) {
  H_mod_fun(state, out_482292932446809381);
}
void car_f_fun(double *state, double dt, double *out_3036930739161912371) {
  f_fun(state,  dt, out_3036930739161912371);
}
void car_F_fun(double *state, double dt, double *out_4607213455717215037) {
  F_fun(state,  dt, out_4607213455717215037);
}
void car_h_25(double *state, double *unused, double *out_335506616585222898) {
  h_25(state, unused, out_335506616585222898);
}
void car_H_25(double *state, double *unused, double *out_4005341571092174529) {
  H_25(state, unused, out_4005341571092174529);
}
void car_h_24(double *state, double *unused, double *out_3915395329659002282) {
  h_24(state, unused, out_3915395329659002282);
}
void car_H_24(double *state, double *unused, double *out_447415972289851393) {
  H_24(state, unused, out_447415972289851393);
}
void car_h_30(double *state, double *unused, double *out_4338044828683651119) {
  h_30(state, unused, out_4338044828683651119);
}
void car_H_30(double *state, double *unused, double *out_1487008612584925902) {
  H_30(state, unused, out_1487008612584925902);
}
void car_h_26(double *state, double *unused, double *out_1764474607049543271) {
  h_26(state, unused, out_1764474607049543271);
}
void car_H_26(double *state, double *unused, double *out_700815601331373928) {
  H_26(state, unused, out_700815601331373928);
}
void car_h_27(double *state, double *unused, double *out_4666166651075622747) {
  h_27(state, unused, out_4666166651075622747);
}
void car_H_27(double *state, double *unused, double *out_736585458599017315) {
  H_27(state, unused, out_736585458599017315);
}
void car_h_29(double *state, double *unused, double *out_4941360713360128636) {
  h_29(state, unused, out_4941360713360128636);
}
void car_H_29(double *state, double *unused, double *out_976777268270533718) {
  H_29(state, unused, out_976777268270533718);
}
void car_h_28(double *state, double *unused, double *out_8778904154973083224) {
  h_28(state, unused, out_8778904154973083224);
}
void car_H_28(double *state, double *unused, double *out_6059176285340064292) {
  H_28(state, unused, out_6059176285340064292);
}
void car_h_31(double *state, double *unused, double *out_1115124776043660269) {
  h_31(state, unused, out_1115124776043660269);
}
void car_H_31(double *state, double *unused, double *out_3071333679419642724) {
  H_31(state, unused, out_3071333679419642724);
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
