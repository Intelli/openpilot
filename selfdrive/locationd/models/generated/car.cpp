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
void err_fun(double *nom_x, double *delta_x, double *out_3439473612777542328) {
   out_3439473612777542328[0] = delta_x[0] + nom_x[0];
   out_3439473612777542328[1] = delta_x[1] + nom_x[1];
   out_3439473612777542328[2] = delta_x[2] + nom_x[2];
   out_3439473612777542328[3] = delta_x[3] + nom_x[3];
   out_3439473612777542328[4] = delta_x[4] + nom_x[4];
   out_3439473612777542328[5] = delta_x[5] + nom_x[5];
   out_3439473612777542328[6] = delta_x[6] + nom_x[6];
   out_3439473612777542328[7] = delta_x[7] + nom_x[7];
   out_3439473612777542328[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3047310167658356067) {
   out_3047310167658356067[0] = -nom_x[0] + true_x[0];
   out_3047310167658356067[1] = -nom_x[1] + true_x[1];
   out_3047310167658356067[2] = -nom_x[2] + true_x[2];
   out_3047310167658356067[3] = -nom_x[3] + true_x[3];
   out_3047310167658356067[4] = -nom_x[4] + true_x[4];
   out_3047310167658356067[5] = -nom_x[5] + true_x[5];
   out_3047310167658356067[6] = -nom_x[6] + true_x[6];
   out_3047310167658356067[7] = -nom_x[7] + true_x[7];
   out_3047310167658356067[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3426229254954236394) {
   out_3426229254954236394[0] = 1.0;
   out_3426229254954236394[1] = 0.0;
   out_3426229254954236394[2] = 0.0;
   out_3426229254954236394[3] = 0.0;
   out_3426229254954236394[4] = 0.0;
   out_3426229254954236394[5] = 0.0;
   out_3426229254954236394[6] = 0.0;
   out_3426229254954236394[7] = 0.0;
   out_3426229254954236394[8] = 0.0;
   out_3426229254954236394[9] = 0.0;
   out_3426229254954236394[10] = 1.0;
   out_3426229254954236394[11] = 0.0;
   out_3426229254954236394[12] = 0.0;
   out_3426229254954236394[13] = 0.0;
   out_3426229254954236394[14] = 0.0;
   out_3426229254954236394[15] = 0.0;
   out_3426229254954236394[16] = 0.0;
   out_3426229254954236394[17] = 0.0;
   out_3426229254954236394[18] = 0.0;
   out_3426229254954236394[19] = 0.0;
   out_3426229254954236394[20] = 1.0;
   out_3426229254954236394[21] = 0.0;
   out_3426229254954236394[22] = 0.0;
   out_3426229254954236394[23] = 0.0;
   out_3426229254954236394[24] = 0.0;
   out_3426229254954236394[25] = 0.0;
   out_3426229254954236394[26] = 0.0;
   out_3426229254954236394[27] = 0.0;
   out_3426229254954236394[28] = 0.0;
   out_3426229254954236394[29] = 0.0;
   out_3426229254954236394[30] = 1.0;
   out_3426229254954236394[31] = 0.0;
   out_3426229254954236394[32] = 0.0;
   out_3426229254954236394[33] = 0.0;
   out_3426229254954236394[34] = 0.0;
   out_3426229254954236394[35] = 0.0;
   out_3426229254954236394[36] = 0.0;
   out_3426229254954236394[37] = 0.0;
   out_3426229254954236394[38] = 0.0;
   out_3426229254954236394[39] = 0.0;
   out_3426229254954236394[40] = 1.0;
   out_3426229254954236394[41] = 0.0;
   out_3426229254954236394[42] = 0.0;
   out_3426229254954236394[43] = 0.0;
   out_3426229254954236394[44] = 0.0;
   out_3426229254954236394[45] = 0.0;
   out_3426229254954236394[46] = 0.0;
   out_3426229254954236394[47] = 0.0;
   out_3426229254954236394[48] = 0.0;
   out_3426229254954236394[49] = 0.0;
   out_3426229254954236394[50] = 1.0;
   out_3426229254954236394[51] = 0.0;
   out_3426229254954236394[52] = 0.0;
   out_3426229254954236394[53] = 0.0;
   out_3426229254954236394[54] = 0.0;
   out_3426229254954236394[55] = 0.0;
   out_3426229254954236394[56] = 0.0;
   out_3426229254954236394[57] = 0.0;
   out_3426229254954236394[58] = 0.0;
   out_3426229254954236394[59] = 0.0;
   out_3426229254954236394[60] = 1.0;
   out_3426229254954236394[61] = 0.0;
   out_3426229254954236394[62] = 0.0;
   out_3426229254954236394[63] = 0.0;
   out_3426229254954236394[64] = 0.0;
   out_3426229254954236394[65] = 0.0;
   out_3426229254954236394[66] = 0.0;
   out_3426229254954236394[67] = 0.0;
   out_3426229254954236394[68] = 0.0;
   out_3426229254954236394[69] = 0.0;
   out_3426229254954236394[70] = 1.0;
   out_3426229254954236394[71] = 0.0;
   out_3426229254954236394[72] = 0.0;
   out_3426229254954236394[73] = 0.0;
   out_3426229254954236394[74] = 0.0;
   out_3426229254954236394[75] = 0.0;
   out_3426229254954236394[76] = 0.0;
   out_3426229254954236394[77] = 0.0;
   out_3426229254954236394[78] = 0.0;
   out_3426229254954236394[79] = 0.0;
   out_3426229254954236394[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1603579069930264214) {
   out_1603579069930264214[0] = state[0];
   out_1603579069930264214[1] = state[1];
   out_1603579069930264214[2] = state[2];
   out_1603579069930264214[3] = state[3];
   out_1603579069930264214[4] = state[4];
   out_1603579069930264214[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1603579069930264214[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1603579069930264214[7] = state[7];
   out_1603579069930264214[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4328042070139184712) {
   out_4328042070139184712[0] = 1;
   out_4328042070139184712[1] = 0;
   out_4328042070139184712[2] = 0;
   out_4328042070139184712[3] = 0;
   out_4328042070139184712[4] = 0;
   out_4328042070139184712[5] = 0;
   out_4328042070139184712[6] = 0;
   out_4328042070139184712[7] = 0;
   out_4328042070139184712[8] = 0;
   out_4328042070139184712[9] = 0;
   out_4328042070139184712[10] = 1;
   out_4328042070139184712[11] = 0;
   out_4328042070139184712[12] = 0;
   out_4328042070139184712[13] = 0;
   out_4328042070139184712[14] = 0;
   out_4328042070139184712[15] = 0;
   out_4328042070139184712[16] = 0;
   out_4328042070139184712[17] = 0;
   out_4328042070139184712[18] = 0;
   out_4328042070139184712[19] = 0;
   out_4328042070139184712[20] = 1;
   out_4328042070139184712[21] = 0;
   out_4328042070139184712[22] = 0;
   out_4328042070139184712[23] = 0;
   out_4328042070139184712[24] = 0;
   out_4328042070139184712[25] = 0;
   out_4328042070139184712[26] = 0;
   out_4328042070139184712[27] = 0;
   out_4328042070139184712[28] = 0;
   out_4328042070139184712[29] = 0;
   out_4328042070139184712[30] = 1;
   out_4328042070139184712[31] = 0;
   out_4328042070139184712[32] = 0;
   out_4328042070139184712[33] = 0;
   out_4328042070139184712[34] = 0;
   out_4328042070139184712[35] = 0;
   out_4328042070139184712[36] = 0;
   out_4328042070139184712[37] = 0;
   out_4328042070139184712[38] = 0;
   out_4328042070139184712[39] = 0;
   out_4328042070139184712[40] = 1;
   out_4328042070139184712[41] = 0;
   out_4328042070139184712[42] = 0;
   out_4328042070139184712[43] = 0;
   out_4328042070139184712[44] = 0;
   out_4328042070139184712[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4328042070139184712[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4328042070139184712[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4328042070139184712[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4328042070139184712[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4328042070139184712[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4328042070139184712[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4328042070139184712[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4328042070139184712[53] = -9.8100000000000005*dt;
   out_4328042070139184712[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4328042070139184712[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4328042070139184712[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4328042070139184712[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4328042070139184712[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4328042070139184712[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4328042070139184712[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4328042070139184712[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4328042070139184712[62] = 0;
   out_4328042070139184712[63] = 0;
   out_4328042070139184712[64] = 0;
   out_4328042070139184712[65] = 0;
   out_4328042070139184712[66] = 0;
   out_4328042070139184712[67] = 0;
   out_4328042070139184712[68] = 0;
   out_4328042070139184712[69] = 0;
   out_4328042070139184712[70] = 1;
   out_4328042070139184712[71] = 0;
   out_4328042070139184712[72] = 0;
   out_4328042070139184712[73] = 0;
   out_4328042070139184712[74] = 0;
   out_4328042070139184712[75] = 0;
   out_4328042070139184712[76] = 0;
   out_4328042070139184712[77] = 0;
   out_4328042070139184712[78] = 0;
   out_4328042070139184712[79] = 0;
   out_4328042070139184712[80] = 1;
}
void h_25(double *state, double *unused, double *out_1106143716500973221) {
   out_1106143716500973221[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1279070317676855982) {
   out_1279070317676855982[0] = 0;
   out_1279070317676855982[1] = 0;
   out_1279070317676855982[2] = 0;
   out_1279070317676855982[3] = 0;
   out_1279070317676855982[4] = 0;
   out_1279070317676855982[5] = 0;
   out_1279070317676855982[6] = 1;
   out_1279070317676855982[7] = 0;
   out_1279070317676855982[8] = 0;
}
void h_24(double *state, double *unused, double *out_2858376262202982067) {
   out_2858376262202982067[0] = state[4];
   out_2858376262202982067[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7939608569963500409) {
   out_7939608569963500409[0] = 0;
   out_7939608569963500409[1] = 0;
   out_7939608569963500409[2] = 0;
   out_7939608569963500409[3] = 0;
   out_7939608569963500409[4] = 1;
   out_7939608569963500409[5] = 0;
   out_7939608569963500409[6] = 0;
   out_7939608569963500409[7] = 0;
   out_7939608569963500409[8] = 0;
   out_7939608569963500409[9] = 0;
   out_7939608569963500409[10] = 0;
   out_7939608569963500409[11] = 0;
   out_7939608569963500409[12] = 0;
   out_7939608569963500409[13] = 0;
   out_7939608569963500409[14] = 1;
   out_7939608569963500409[15] = 0;
   out_7939608569963500409[16] = 0;
   out_7939608569963500409[17] = 0;
}
void h_30(double *state, double *unused, double *out_4743593244754995571) {
   out_4743593244754995571[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3248626012450752216) {
   out_3248626012450752216[0] = 0;
   out_3248626012450752216[1] = 0;
   out_3248626012450752216[2] = 0;
   out_3248626012450752216[3] = 0;
   out_3248626012450752216[4] = 1;
   out_3248626012450752216[5] = 0;
   out_3248626012450752216[6] = 0;
   out_3248626012450752216[7] = 0;
   out_3248626012450752216[8] = 0;
}
void h_26(double *state, double *unused, double *out_8159866534404065587) {
   out_8159866534404065587[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2462433001197200242) {
   out_2462433001197200242[0] = 0;
   out_2462433001197200242[1] = 0;
   out_2462433001197200242[2] = 0;
   out_2462433001197200242[3] = 0;
   out_2462433001197200242[4] = 0;
   out_2462433001197200242[5] = 0;
   out_2462433001197200242[6] = 0;
   out_2462433001197200242[7] = 1;
   out_2462433001197200242[8] = 0;
}
void h_27(double *state, double *unused, double *out_61600084575168516) {
   out_61600084575168516[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5423389324251177127) {
   out_5423389324251177127[0] = 0;
   out_5423389324251177127[1] = 0;
   out_5423389324251177127[2] = 0;
   out_5423389324251177127[3] = 1;
   out_5423389324251177127[4] = 0;
   out_5423389324251177127[5] = 0;
   out_5423389324251177127[6] = 0;
   out_5423389324251177127[7] = 0;
   out_5423389324251177127[8] = 0;
}
void h_29(double *state, double *unused, double *out_1655448272658853575) {
   out_1655448272658853575[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2738394668136360032) {
   out_2738394668136360032[0] = 0;
   out_2738394668136360032[1] = 1;
   out_2738394668136360032[2] = 0;
   out_2738394668136360032[3] = 0;
   out_2738394668136360032[4] = 0;
   out_2738394668136360032[5] = 0;
   out_2738394668136360032[6] = 0;
   out_2738394668136360032[7] = 0;
   out_2738394668136360032[8] = 0;
}
void h_28(double *state, double *unused, double *out_2874152187845021899) {
   out_2874152187845021899[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7820793685205890606) {
   out_7820793685205890606[0] = 1;
   out_7820793685205890606[1] = 0;
   out_7820793685205890606[2] = 0;
   out_7820793685205890606[3] = 0;
   out_7820793685205890606[4] = 0;
   out_7820793685205890606[5] = 0;
   out_7820793685205890606[6] = 0;
   out_7820793685205890606[7] = 0;
   out_7820793685205890606[8] = 0;
}
void h_31(double *state, double *unused, double *out_1707561874114336775) {
   out_1707561874114336775[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3088641103430551718) {
   out_3088641103430551718[0] = 0;
   out_3088641103430551718[1] = 0;
   out_3088641103430551718[2] = 0;
   out_3088641103430551718[3] = 0;
   out_3088641103430551718[4] = 0;
   out_3088641103430551718[5] = 0;
   out_3088641103430551718[6] = 0;
   out_3088641103430551718[7] = 0;
   out_3088641103430551718[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3439473612777542328) {
  err_fun(nom_x, delta_x, out_3439473612777542328);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3047310167658356067) {
  inv_err_fun(nom_x, true_x, out_3047310167658356067);
}
void car_H_mod_fun(double *state, double *out_3426229254954236394) {
  H_mod_fun(state, out_3426229254954236394);
}
void car_f_fun(double *state, double dt, double *out_1603579069930264214) {
  f_fun(state,  dt, out_1603579069930264214);
}
void car_F_fun(double *state, double dt, double *out_4328042070139184712) {
  F_fun(state,  dt, out_4328042070139184712);
}
void car_h_25(double *state, double *unused, double *out_1106143716500973221) {
  h_25(state, unused, out_1106143716500973221);
}
void car_H_25(double *state, double *unused, double *out_1279070317676855982) {
  H_25(state, unused, out_1279070317676855982);
}
void car_h_24(double *state, double *unused, double *out_2858376262202982067) {
  h_24(state, unused, out_2858376262202982067);
}
void car_H_24(double *state, double *unused, double *out_7939608569963500409) {
  H_24(state, unused, out_7939608569963500409);
}
void car_h_30(double *state, double *unused, double *out_4743593244754995571) {
  h_30(state, unused, out_4743593244754995571);
}
void car_H_30(double *state, double *unused, double *out_3248626012450752216) {
  H_30(state, unused, out_3248626012450752216);
}
void car_h_26(double *state, double *unused, double *out_8159866534404065587) {
  h_26(state, unused, out_8159866534404065587);
}
void car_H_26(double *state, double *unused, double *out_2462433001197200242) {
  H_26(state, unused, out_2462433001197200242);
}
void car_h_27(double *state, double *unused, double *out_61600084575168516) {
  h_27(state, unused, out_61600084575168516);
}
void car_H_27(double *state, double *unused, double *out_5423389324251177127) {
  H_27(state, unused, out_5423389324251177127);
}
void car_h_29(double *state, double *unused, double *out_1655448272658853575) {
  h_29(state, unused, out_1655448272658853575);
}
void car_H_29(double *state, double *unused, double *out_2738394668136360032) {
  H_29(state, unused, out_2738394668136360032);
}
void car_h_28(double *state, double *unused, double *out_2874152187845021899) {
  h_28(state, unused, out_2874152187845021899);
}
void car_H_28(double *state, double *unused, double *out_7820793685205890606) {
  H_28(state, unused, out_7820793685205890606);
}
void car_h_31(double *state, double *unused, double *out_1707561874114336775) {
  h_31(state, unused, out_1707561874114336775);
}
void car_H_31(double *state, double *unused, double *out_3088641103430551718) {
  H_31(state, unused, out_3088641103430551718);
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
