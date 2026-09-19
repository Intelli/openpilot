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
void err_fun(double *nom_x, double *delta_x, double *out_435362218317324015) {
   out_435362218317324015[0] = delta_x[0] + nom_x[0];
   out_435362218317324015[1] = delta_x[1] + nom_x[1];
   out_435362218317324015[2] = delta_x[2] + nom_x[2];
   out_435362218317324015[3] = delta_x[3] + nom_x[3];
   out_435362218317324015[4] = delta_x[4] + nom_x[4];
   out_435362218317324015[5] = delta_x[5] + nom_x[5];
   out_435362218317324015[6] = delta_x[6] + nom_x[6];
   out_435362218317324015[7] = delta_x[7] + nom_x[7];
   out_435362218317324015[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8574647122111739157) {
   out_8574647122111739157[0] = -nom_x[0] + true_x[0];
   out_8574647122111739157[1] = -nom_x[1] + true_x[1];
   out_8574647122111739157[2] = -nom_x[2] + true_x[2];
   out_8574647122111739157[3] = -nom_x[3] + true_x[3];
   out_8574647122111739157[4] = -nom_x[4] + true_x[4];
   out_8574647122111739157[5] = -nom_x[5] + true_x[5];
   out_8574647122111739157[6] = -nom_x[6] + true_x[6];
   out_8574647122111739157[7] = -nom_x[7] + true_x[7];
   out_8574647122111739157[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8740515891481266957) {
   out_8740515891481266957[0] = 1.0;
   out_8740515891481266957[1] = 0.0;
   out_8740515891481266957[2] = 0.0;
   out_8740515891481266957[3] = 0.0;
   out_8740515891481266957[4] = 0.0;
   out_8740515891481266957[5] = 0.0;
   out_8740515891481266957[6] = 0.0;
   out_8740515891481266957[7] = 0.0;
   out_8740515891481266957[8] = 0.0;
   out_8740515891481266957[9] = 0.0;
   out_8740515891481266957[10] = 1.0;
   out_8740515891481266957[11] = 0.0;
   out_8740515891481266957[12] = 0.0;
   out_8740515891481266957[13] = 0.0;
   out_8740515891481266957[14] = 0.0;
   out_8740515891481266957[15] = 0.0;
   out_8740515891481266957[16] = 0.0;
   out_8740515891481266957[17] = 0.0;
   out_8740515891481266957[18] = 0.0;
   out_8740515891481266957[19] = 0.0;
   out_8740515891481266957[20] = 1.0;
   out_8740515891481266957[21] = 0.0;
   out_8740515891481266957[22] = 0.0;
   out_8740515891481266957[23] = 0.0;
   out_8740515891481266957[24] = 0.0;
   out_8740515891481266957[25] = 0.0;
   out_8740515891481266957[26] = 0.0;
   out_8740515891481266957[27] = 0.0;
   out_8740515891481266957[28] = 0.0;
   out_8740515891481266957[29] = 0.0;
   out_8740515891481266957[30] = 1.0;
   out_8740515891481266957[31] = 0.0;
   out_8740515891481266957[32] = 0.0;
   out_8740515891481266957[33] = 0.0;
   out_8740515891481266957[34] = 0.0;
   out_8740515891481266957[35] = 0.0;
   out_8740515891481266957[36] = 0.0;
   out_8740515891481266957[37] = 0.0;
   out_8740515891481266957[38] = 0.0;
   out_8740515891481266957[39] = 0.0;
   out_8740515891481266957[40] = 1.0;
   out_8740515891481266957[41] = 0.0;
   out_8740515891481266957[42] = 0.0;
   out_8740515891481266957[43] = 0.0;
   out_8740515891481266957[44] = 0.0;
   out_8740515891481266957[45] = 0.0;
   out_8740515891481266957[46] = 0.0;
   out_8740515891481266957[47] = 0.0;
   out_8740515891481266957[48] = 0.0;
   out_8740515891481266957[49] = 0.0;
   out_8740515891481266957[50] = 1.0;
   out_8740515891481266957[51] = 0.0;
   out_8740515891481266957[52] = 0.0;
   out_8740515891481266957[53] = 0.0;
   out_8740515891481266957[54] = 0.0;
   out_8740515891481266957[55] = 0.0;
   out_8740515891481266957[56] = 0.0;
   out_8740515891481266957[57] = 0.0;
   out_8740515891481266957[58] = 0.0;
   out_8740515891481266957[59] = 0.0;
   out_8740515891481266957[60] = 1.0;
   out_8740515891481266957[61] = 0.0;
   out_8740515891481266957[62] = 0.0;
   out_8740515891481266957[63] = 0.0;
   out_8740515891481266957[64] = 0.0;
   out_8740515891481266957[65] = 0.0;
   out_8740515891481266957[66] = 0.0;
   out_8740515891481266957[67] = 0.0;
   out_8740515891481266957[68] = 0.0;
   out_8740515891481266957[69] = 0.0;
   out_8740515891481266957[70] = 1.0;
   out_8740515891481266957[71] = 0.0;
   out_8740515891481266957[72] = 0.0;
   out_8740515891481266957[73] = 0.0;
   out_8740515891481266957[74] = 0.0;
   out_8740515891481266957[75] = 0.0;
   out_8740515891481266957[76] = 0.0;
   out_8740515891481266957[77] = 0.0;
   out_8740515891481266957[78] = 0.0;
   out_8740515891481266957[79] = 0.0;
   out_8740515891481266957[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7569887734541362894) {
   out_7569887734541362894[0] = state[0];
   out_7569887734541362894[1] = state[1];
   out_7569887734541362894[2] = state[2];
   out_7569887734541362894[3] = state[3];
   out_7569887734541362894[4] = state[4];
   out_7569887734541362894[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7569887734541362894[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7569887734541362894[7] = state[7];
   out_7569887734541362894[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8471352899330176325) {
   out_8471352899330176325[0] = 1;
   out_8471352899330176325[1] = 0;
   out_8471352899330176325[2] = 0;
   out_8471352899330176325[3] = 0;
   out_8471352899330176325[4] = 0;
   out_8471352899330176325[5] = 0;
   out_8471352899330176325[6] = 0;
   out_8471352899330176325[7] = 0;
   out_8471352899330176325[8] = 0;
   out_8471352899330176325[9] = 0;
   out_8471352899330176325[10] = 1;
   out_8471352899330176325[11] = 0;
   out_8471352899330176325[12] = 0;
   out_8471352899330176325[13] = 0;
   out_8471352899330176325[14] = 0;
   out_8471352899330176325[15] = 0;
   out_8471352899330176325[16] = 0;
   out_8471352899330176325[17] = 0;
   out_8471352899330176325[18] = 0;
   out_8471352899330176325[19] = 0;
   out_8471352899330176325[20] = 1;
   out_8471352899330176325[21] = 0;
   out_8471352899330176325[22] = 0;
   out_8471352899330176325[23] = 0;
   out_8471352899330176325[24] = 0;
   out_8471352899330176325[25] = 0;
   out_8471352899330176325[26] = 0;
   out_8471352899330176325[27] = 0;
   out_8471352899330176325[28] = 0;
   out_8471352899330176325[29] = 0;
   out_8471352899330176325[30] = 1;
   out_8471352899330176325[31] = 0;
   out_8471352899330176325[32] = 0;
   out_8471352899330176325[33] = 0;
   out_8471352899330176325[34] = 0;
   out_8471352899330176325[35] = 0;
   out_8471352899330176325[36] = 0;
   out_8471352899330176325[37] = 0;
   out_8471352899330176325[38] = 0;
   out_8471352899330176325[39] = 0;
   out_8471352899330176325[40] = 1;
   out_8471352899330176325[41] = 0;
   out_8471352899330176325[42] = 0;
   out_8471352899330176325[43] = 0;
   out_8471352899330176325[44] = 0;
   out_8471352899330176325[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8471352899330176325[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8471352899330176325[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8471352899330176325[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8471352899330176325[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8471352899330176325[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8471352899330176325[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8471352899330176325[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8471352899330176325[53] = -9.8100000000000005*dt;
   out_8471352899330176325[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8471352899330176325[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8471352899330176325[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8471352899330176325[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8471352899330176325[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8471352899330176325[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8471352899330176325[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8471352899330176325[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8471352899330176325[62] = 0;
   out_8471352899330176325[63] = 0;
   out_8471352899330176325[64] = 0;
   out_8471352899330176325[65] = 0;
   out_8471352899330176325[66] = 0;
   out_8471352899330176325[67] = 0;
   out_8471352899330176325[68] = 0;
   out_8471352899330176325[69] = 0;
   out_8471352899330176325[70] = 1;
   out_8471352899330176325[71] = 0;
   out_8471352899330176325[72] = 0;
   out_8471352899330176325[73] = 0;
   out_8471352899330176325[74] = 0;
   out_8471352899330176325[75] = 0;
   out_8471352899330176325[76] = 0;
   out_8471352899330176325[77] = 0;
   out_8471352899330176325[78] = 0;
   out_8471352899330176325[79] = 0;
   out_8471352899330176325[80] = 1;
}
void h_25(double *state, double *unused, double *out_7212881291178297455) {
   out_7212881291178297455[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1357001217961298052) {
   out_1357001217961298052[0] = 0;
   out_1357001217961298052[1] = 0;
   out_1357001217961298052[2] = 0;
   out_1357001217961298052[3] = 0;
   out_1357001217961298052[4] = 0;
   out_1357001217961298052[5] = 0;
   out_1357001217961298052[6] = 1;
   out_1357001217961298052[7] = 0;
   out_1357001217961298052[8] = 0;
}
void h_24(double *state, double *unused, double *out_1711226362681868661) {
   out_1711226362681868661[0] = state[4];
   out_1711226362681868661[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2625321933436469846) {
   out_2625321933436469846[0] = 0;
   out_2625321933436469846[1] = 0;
   out_2625321933436469846[2] = 0;
   out_2625321933436469846[3] = 0;
   out_2625321933436469846[4] = 1;
   out_2625321933436469846[5] = 0;
   out_2625321933436469846[6] = 0;
   out_2625321933436469846[7] = 0;
   out_2625321933436469846[8] = 0;
   out_2625321933436469846[9] = 0;
   out_2625321933436469846[10] = 0;
   out_2625321933436469846[11] = 0;
   out_2625321933436469846[12] = 0;
   out_2625321933436469846[13] = 0;
   out_2625321933436469846[14] = 1;
   out_2625321933436469846[15] = 0;
   out_2625321933436469846[16] = 0;
   out_2625321933436469846[17] = 0;
}
void h_30(double *state, double *unused, double *out_6739311054597629248) {
   out_6739311054597629248[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8273691559452914807) {
   out_8273691559452914807[0] = 0;
   out_8273691559452914807[1] = 0;
   out_8273691559452914807[2] = 0;
   out_8273691559452914807[3] = 0;
   out_8273691559452914807[4] = 1;
   out_8273691559452914807[5] = 0;
   out_8273691559452914807[6] = 0;
   out_8273691559452914807[7] = 0;
   out_8273691559452914807[8] = 0;
}
void h_26(double *state, double *unused, double *out_7342626939274106765) {
   out_7342626939274106765[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4661527187722098653) {
   out_4661527187722098653[0] = 0;
   out_4661527187722098653[1] = 0;
   out_4661527187722098653[2] = 0;
   out_4661527187722098653[3] = 0;
   out_4661527187722098653[4] = 0;
   out_4661527187722098653[5] = 0;
   out_4661527187722098653[6] = 0;
   out_4661527187722098653[7] = 1;
   out_4661527187722098653[8] = 0;
}
void h_27(double *state, double *unused, double *out_4176095239733964770) {
   out_4176095239733964770[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6098928247652489896) {
   out_6098928247652489896[0] = 0;
   out_6098928247652489896[1] = 0;
   out_6098928247652489896[2] = 0;
   out_6098928247652489896[3] = 1;
   out_6098928247652489896[4] = 0;
   out_6098928247652489896[5] = 0;
   out_6098928247652489896[6] = 0;
   out_6098928247652489896[7] = 0;
   out_6098928247652489896[8] = 0;
}
void h_29(double *state, double *unused, double *out_7682820907499291683) {
   out_7682820907499291683[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8783922903767306991) {
   out_8783922903767306991[0] = 0;
   out_8783922903767306991[1] = 1;
   out_8783922903767306991[2] = 0;
   out_8783922903767306991[3] = 0;
   out_8783922903767306991[4] = 0;
   out_8783922903767306991[5] = 0;
   out_8783922903767306991[6] = 0;
   out_8783922903767306991[7] = 0;
   out_8783922903767306991[8] = 0;
}
void h_28(double *state, double *unused, double *out_2826667464059101009) {
   out_2826667464059101009[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3701523886697776417) {
   out_3701523886697776417[0] = 1;
   out_3701523886697776417[1] = 0;
   out_3701523886697776417[2] = 0;
   out_3701523886697776417[3] = 0;
   out_3701523886697776417[4] = 0;
   out_3701523886697776417[5] = 0;
   out_3701523886697776417[6] = 0;
   out_3701523886697776417[7] = 0;
   out_3701523886697776417[8] = 0;
}
void h_31(double *state, double *unused, double *out_4463027556180903225) {
   out_4463027556180903225[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1387647179838258480) {
   out_1387647179838258480[0] = 0;
   out_1387647179838258480[1] = 0;
   out_1387647179838258480[2] = 0;
   out_1387647179838258480[3] = 0;
   out_1387647179838258480[4] = 0;
   out_1387647179838258480[5] = 0;
   out_1387647179838258480[6] = 0;
   out_1387647179838258480[7] = 0;
   out_1387647179838258480[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_435362218317324015) {
  err_fun(nom_x, delta_x, out_435362218317324015);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8574647122111739157) {
  inv_err_fun(nom_x, true_x, out_8574647122111739157);
}
void car_H_mod_fun(double *state, double *out_8740515891481266957) {
  H_mod_fun(state, out_8740515891481266957);
}
void car_f_fun(double *state, double dt, double *out_7569887734541362894) {
  f_fun(state,  dt, out_7569887734541362894);
}
void car_F_fun(double *state, double dt, double *out_8471352899330176325) {
  F_fun(state,  dt, out_8471352899330176325);
}
void car_h_25(double *state, double *unused, double *out_7212881291178297455) {
  h_25(state, unused, out_7212881291178297455);
}
void car_H_25(double *state, double *unused, double *out_1357001217961298052) {
  H_25(state, unused, out_1357001217961298052);
}
void car_h_24(double *state, double *unused, double *out_1711226362681868661) {
  h_24(state, unused, out_1711226362681868661);
}
void car_H_24(double *state, double *unused, double *out_2625321933436469846) {
  H_24(state, unused, out_2625321933436469846);
}
void car_h_30(double *state, double *unused, double *out_6739311054597629248) {
  h_30(state, unused, out_6739311054597629248);
}
void car_H_30(double *state, double *unused, double *out_8273691559452914807) {
  H_30(state, unused, out_8273691559452914807);
}
void car_h_26(double *state, double *unused, double *out_7342626939274106765) {
  h_26(state, unused, out_7342626939274106765);
}
void car_H_26(double *state, double *unused, double *out_4661527187722098653) {
  H_26(state, unused, out_4661527187722098653);
}
void car_h_27(double *state, double *unused, double *out_4176095239733964770) {
  h_27(state, unused, out_4176095239733964770);
}
void car_H_27(double *state, double *unused, double *out_6098928247652489896) {
  H_27(state, unused, out_6098928247652489896);
}
void car_h_29(double *state, double *unused, double *out_7682820907499291683) {
  h_29(state, unused, out_7682820907499291683);
}
void car_H_29(double *state, double *unused, double *out_8783922903767306991) {
  H_29(state, unused, out_8783922903767306991);
}
void car_h_28(double *state, double *unused, double *out_2826667464059101009) {
  h_28(state, unused, out_2826667464059101009);
}
void car_H_28(double *state, double *unused, double *out_3701523886697776417) {
  H_28(state, unused, out_3701523886697776417);
}
void car_h_31(double *state, double *unused, double *out_4463027556180903225) {
  h_31(state, unused, out_4463027556180903225);
}
void car_H_31(double *state, double *unused, double *out_1387647179838258480) {
  H_31(state, unused, out_1387647179838258480);
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
