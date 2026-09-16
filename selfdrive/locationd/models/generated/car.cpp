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
void err_fun(double *nom_x, double *delta_x, double *out_7895276982844131476) {
   out_7895276982844131476[0] = delta_x[0] + nom_x[0];
   out_7895276982844131476[1] = delta_x[1] + nom_x[1];
   out_7895276982844131476[2] = delta_x[2] + nom_x[2];
   out_7895276982844131476[3] = delta_x[3] + nom_x[3];
   out_7895276982844131476[4] = delta_x[4] + nom_x[4];
   out_7895276982844131476[5] = delta_x[5] + nom_x[5];
   out_7895276982844131476[6] = delta_x[6] + nom_x[6];
   out_7895276982844131476[7] = delta_x[7] + nom_x[7];
   out_7895276982844131476[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8311988311363521241) {
   out_8311988311363521241[0] = -nom_x[0] + true_x[0];
   out_8311988311363521241[1] = -nom_x[1] + true_x[1];
   out_8311988311363521241[2] = -nom_x[2] + true_x[2];
   out_8311988311363521241[3] = -nom_x[3] + true_x[3];
   out_8311988311363521241[4] = -nom_x[4] + true_x[4];
   out_8311988311363521241[5] = -nom_x[5] + true_x[5];
   out_8311988311363521241[6] = -nom_x[6] + true_x[6];
   out_8311988311363521241[7] = -nom_x[7] + true_x[7];
   out_8311988311363521241[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6889381883510717831) {
   out_6889381883510717831[0] = 1.0;
   out_6889381883510717831[1] = 0.0;
   out_6889381883510717831[2] = 0.0;
   out_6889381883510717831[3] = 0.0;
   out_6889381883510717831[4] = 0.0;
   out_6889381883510717831[5] = 0.0;
   out_6889381883510717831[6] = 0.0;
   out_6889381883510717831[7] = 0.0;
   out_6889381883510717831[8] = 0.0;
   out_6889381883510717831[9] = 0.0;
   out_6889381883510717831[10] = 1.0;
   out_6889381883510717831[11] = 0.0;
   out_6889381883510717831[12] = 0.0;
   out_6889381883510717831[13] = 0.0;
   out_6889381883510717831[14] = 0.0;
   out_6889381883510717831[15] = 0.0;
   out_6889381883510717831[16] = 0.0;
   out_6889381883510717831[17] = 0.0;
   out_6889381883510717831[18] = 0.0;
   out_6889381883510717831[19] = 0.0;
   out_6889381883510717831[20] = 1.0;
   out_6889381883510717831[21] = 0.0;
   out_6889381883510717831[22] = 0.0;
   out_6889381883510717831[23] = 0.0;
   out_6889381883510717831[24] = 0.0;
   out_6889381883510717831[25] = 0.0;
   out_6889381883510717831[26] = 0.0;
   out_6889381883510717831[27] = 0.0;
   out_6889381883510717831[28] = 0.0;
   out_6889381883510717831[29] = 0.0;
   out_6889381883510717831[30] = 1.0;
   out_6889381883510717831[31] = 0.0;
   out_6889381883510717831[32] = 0.0;
   out_6889381883510717831[33] = 0.0;
   out_6889381883510717831[34] = 0.0;
   out_6889381883510717831[35] = 0.0;
   out_6889381883510717831[36] = 0.0;
   out_6889381883510717831[37] = 0.0;
   out_6889381883510717831[38] = 0.0;
   out_6889381883510717831[39] = 0.0;
   out_6889381883510717831[40] = 1.0;
   out_6889381883510717831[41] = 0.0;
   out_6889381883510717831[42] = 0.0;
   out_6889381883510717831[43] = 0.0;
   out_6889381883510717831[44] = 0.0;
   out_6889381883510717831[45] = 0.0;
   out_6889381883510717831[46] = 0.0;
   out_6889381883510717831[47] = 0.0;
   out_6889381883510717831[48] = 0.0;
   out_6889381883510717831[49] = 0.0;
   out_6889381883510717831[50] = 1.0;
   out_6889381883510717831[51] = 0.0;
   out_6889381883510717831[52] = 0.0;
   out_6889381883510717831[53] = 0.0;
   out_6889381883510717831[54] = 0.0;
   out_6889381883510717831[55] = 0.0;
   out_6889381883510717831[56] = 0.0;
   out_6889381883510717831[57] = 0.0;
   out_6889381883510717831[58] = 0.0;
   out_6889381883510717831[59] = 0.0;
   out_6889381883510717831[60] = 1.0;
   out_6889381883510717831[61] = 0.0;
   out_6889381883510717831[62] = 0.0;
   out_6889381883510717831[63] = 0.0;
   out_6889381883510717831[64] = 0.0;
   out_6889381883510717831[65] = 0.0;
   out_6889381883510717831[66] = 0.0;
   out_6889381883510717831[67] = 0.0;
   out_6889381883510717831[68] = 0.0;
   out_6889381883510717831[69] = 0.0;
   out_6889381883510717831[70] = 1.0;
   out_6889381883510717831[71] = 0.0;
   out_6889381883510717831[72] = 0.0;
   out_6889381883510717831[73] = 0.0;
   out_6889381883510717831[74] = 0.0;
   out_6889381883510717831[75] = 0.0;
   out_6889381883510717831[76] = 0.0;
   out_6889381883510717831[77] = 0.0;
   out_6889381883510717831[78] = 0.0;
   out_6889381883510717831[79] = 0.0;
   out_6889381883510717831[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8017553581414772762) {
   out_8017553581414772762[0] = state[0];
   out_8017553581414772762[1] = state[1];
   out_8017553581414772762[2] = state[2];
   out_8017553581414772762[3] = state[3];
   out_8017553581414772762[4] = state[4];
   out_8017553581414772762[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8017553581414772762[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8017553581414772762[7] = state[7];
   out_8017553581414772762[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8543421153524097422) {
   out_8543421153524097422[0] = 1;
   out_8543421153524097422[1] = 0;
   out_8543421153524097422[2] = 0;
   out_8543421153524097422[3] = 0;
   out_8543421153524097422[4] = 0;
   out_8543421153524097422[5] = 0;
   out_8543421153524097422[6] = 0;
   out_8543421153524097422[7] = 0;
   out_8543421153524097422[8] = 0;
   out_8543421153524097422[9] = 0;
   out_8543421153524097422[10] = 1;
   out_8543421153524097422[11] = 0;
   out_8543421153524097422[12] = 0;
   out_8543421153524097422[13] = 0;
   out_8543421153524097422[14] = 0;
   out_8543421153524097422[15] = 0;
   out_8543421153524097422[16] = 0;
   out_8543421153524097422[17] = 0;
   out_8543421153524097422[18] = 0;
   out_8543421153524097422[19] = 0;
   out_8543421153524097422[20] = 1;
   out_8543421153524097422[21] = 0;
   out_8543421153524097422[22] = 0;
   out_8543421153524097422[23] = 0;
   out_8543421153524097422[24] = 0;
   out_8543421153524097422[25] = 0;
   out_8543421153524097422[26] = 0;
   out_8543421153524097422[27] = 0;
   out_8543421153524097422[28] = 0;
   out_8543421153524097422[29] = 0;
   out_8543421153524097422[30] = 1;
   out_8543421153524097422[31] = 0;
   out_8543421153524097422[32] = 0;
   out_8543421153524097422[33] = 0;
   out_8543421153524097422[34] = 0;
   out_8543421153524097422[35] = 0;
   out_8543421153524097422[36] = 0;
   out_8543421153524097422[37] = 0;
   out_8543421153524097422[38] = 0;
   out_8543421153524097422[39] = 0;
   out_8543421153524097422[40] = 1;
   out_8543421153524097422[41] = 0;
   out_8543421153524097422[42] = 0;
   out_8543421153524097422[43] = 0;
   out_8543421153524097422[44] = 0;
   out_8543421153524097422[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8543421153524097422[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8543421153524097422[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8543421153524097422[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8543421153524097422[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8543421153524097422[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8543421153524097422[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8543421153524097422[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8543421153524097422[53] = -9.8100000000000005*dt;
   out_8543421153524097422[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8543421153524097422[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8543421153524097422[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8543421153524097422[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8543421153524097422[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8543421153524097422[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8543421153524097422[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8543421153524097422[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8543421153524097422[62] = 0;
   out_8543421153524097422[63] = 0;
   out_8543421153524097422[64] = 0;
   out_8543421153524097422[65] = 0;
   out_8543421153524097422[66] = 0;
   out_8543421153524097422[67] = 0;
   out_8543421153524097422[68] = 0;
   out_8543421153524097422[69] = 0;
   out_8543421153524097422[70] = 1;
   out_8543421153524097422[71] = 0;
   out_8543421153524097422[72] = 0;
   out_8543421153524097422[73] = 0;
   out_8543421153524097422[74] = 0;
   out_8543421153524097422[75] = 0;
   out_8543421153524097422[76] = 0;
   out_8543421153524097422[77] = 0;
   out_8543421153524097422[78] = 0;
   out_8543421153524097422[79] = 0;
   out_8543421153524097422[80] = 1;
}
void h_25(double *state, double *unused, double *out_3233264926632776173) {
   out_3233264926632776173[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6653670365014168945) {
   out_6653670365014168945[0] = 0;
   out_6653670365014168945[1] = 0;
   out_6653670365014168945[2] = 0;
   out_6653670365014168945[3] = 0;
   out_6653670365014168945[4] = 0;
   out_6653670365014168945[5] = 0;
   out_6653670365014168945[6] = 1;
   out_6653670365014168945[7] = 0;
   out_6653670365014168945[8] = 0;
}
void h_24(double *state, double *unused, double *out_5475294472382821453) {
   out_5475294472382821453[0] = state[4];
   out_5475294472382821453[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4965853929145064754) {
   out_4965853929145064754[0] = 0;
   out_4965853929145064754[1] = 0;
   out_4965853929145064754[2] = 0;
   out_4965853929145064754[3] = 0;
   out_4965853929145064754[4] = 1;
   out_4965853929145064754[5] = 0;
   out_4965853929145064754[6] = 0;
   out_4965853929145064754[7] = 0;
   out_4965853929145064754[8] = 0;
   out_4965853929145064754[9] = 0;
   out_4965853929145064754[10] = 0;
   out_4965853929145064754[11] = 0;
   out_4965853929145064754[12] = 0;
   out_4965853929145064754[13] = 0;
   out_4965853929145064754[14] = 1;
   out_4965853929145064754[15] = 0;
   out_4965853929145064754[16] = 0;
   out_4965853929145064754[17] = 0;
}
void h_30(double *state, double *unused, double *out_7332206496322726258) {
   out_7332206496322726258[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7265377378567774473) {
   out_7265377378567774473[0] = 0;
   out_7265377378567774473[1] = 0;
   out_7265377378567774473[2] = 0;
   out_7265377378567774473[3] = 0;
   out_7265377378567774473[4] = 1;
   out_7265377378567774473[5] = 0;
   out_7265377378567774473[6] = 0;
   out_7265377378567774473[7] = 0;
   out_7265377378567774473[8] = 0;
}
void h_26(double *state, double *unused, double *out_5512084423523194380) {
   out_5512084423523194380[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8051570389821326447) {
   out_8051570389821326447[0] = 0;
   out_8051570389821326447[1] = 0;
   out_8051570389821326447[2] = 0;
   out_8051570389821326447[3] = 0;
   out_8051570389821326447[4] = 0;
   out_8051570389821326447[5] = 0;
   out_8051570389821326447[6] = 0;
   out_8051570389821326447[7] = 1;
   out_8051570389821326447[8] = 0;
}
void h_27(double *state, double *unused, double *out_1729115071048517059) {
   out_1729115071048517059[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8957772623957833926) {
   out_8957772623957833926[0] = 0;
   out_8957772623957833926[1] = 0;
   out_8957772623957833926[2] = 0;
   out_8957772623957833926[3] = 1;
   out_8957772623957833926[4] = 0;
   out_8957772623957833926[5] = 0;
   out_8957772623957833926[6] = 0;
   out_8957772623957833926[7] = 0;
   out_8957772623957833926[8] = 0;
}
void h_29(double *state, double *unused, double *out_8954363745840362116) {
   out_8954363745840362116[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7775608722882166657) {
   out_7775608722882166657[0] = 0;
   out_7775608722882166657[1] = 1;
   out_7775608722882166657[2] = 0;
   out_7775608722882166657[3] = 0;
   out_7775608722882166657[4] = 0;
   out_7775608722882166657[5] = 0;
   out_7775608722882166657[6] = 0;
   out_7775608722882166657[7] = 0;
   out_7775608722882166657[8] = 0;
}
void h_28(double *state, double *unused, double *out_3419562905784198019) {
   out_3419562905784198019[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8707505079262058708) {
   out_8707505079262058708[0] = 1;
   out_8707505079262058708[1] = 0;
   out_8707505079262058708[2] = 0;
   out_8707505079262058708[3] = 0;
   out_8707505079262058708[4] = 0;
   out_8707505079262058708[5] = 0;
   out_8707505079262058708[6] = 0;
   out_8707505079262058708[7] = 0;
   out_8707505079262058708[8] = 0;
}
void h_31(double *state, double *unused, double *out_5280156946080479537) {
   out_5280156946080479537[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6623024403137208517) {
   out_6623024403137208517[0] = 0;
   out_6623024403137208517[1] = 0;
   out_6623024403137208517[2] = 0;
   out_6623024403137208517[3] = 0;
   out_6623024403137208517[4] = 0;
   out_6623024403137208517[5] = 0;
   out_6623024403137208517[6] = 0;
   out_6623024403137208517[7] = 0;
   out_6623024403137208517[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7895276982844131476) {
  err_fun(nom_x, delta_x, out_7895276982844131476);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8311988311363521241) {
  inv_err_fun(nom_x, true_x, out_8311988311363521241);
}
void car_H_mod_fun(double *state, double *out_6889381883510717831) {
  H_mod_fun(state, out_6889381883510717831);
}
void car_f_fun(double *state, double dt, double *out_8017553581414772762) {
  f_fun(state,  dt, out_8017553581414772762);
}
void car_F_fun(double *state, double dt, double *out_8543421153524097422) {
  F_fun(state,  dt, out_8543421153524097422);
}
void car_h_25(double *state, double *unused, double *out_3233264926632776173) {
  h_25(state, unused, out_3233264926632776173);
}
void car_H_25(double *state, double *unused, double *out_6653670365014168945) {
  H_25(state, unused, out_6653670365014168945);
}
void car_h_24(double *state, double *unused, double *out_5475294472382821453) {
  h_24(state, unused, out_5475294472382821453);
}
void car_H_24(double *state, double *unused, double *out_4965853929145064754) {
  H_24(state, unused, out_4965853929145064754);
}
void car_h_30(double *state, double *unused, double *out_7332206496322726258) {
  h_30(state, unused, out_7332206496322726258);
}
void car_H_30(double *state, double *unused, double *out_7265377378567774473) {
  H_30(state, unused, out_7265377378567774473);
}
void car_h_26(double *state, double *unused, double *out_5512084423523194380) {
  h_26(state, unused, out_5512084423523194380);
}
void car_H_26(double *state, double *unused, double *out_8051570389821326447) {
  H_26(state, unused, out_8051570389821326447);
}
void car_h_27(double *state, double *unused, double *out_1729115071048517059) {
  h_27(state, unused, out_1729115071048517059);
}
void car_H_27(double *state, double *unused, double *out_8957772623957833926) {
  H_27(state, unused, out_8957772623957833926);
}
void car_h_29(double *state, double *unused, double *out_8954363745840362116) {
  h_29(state, unused, out_8954363745840362116);
}
void car_H_29(double *state, double *unused, double *out_7775608722882166657) {
  H_29(state, unused, out_7775608722882166657);
}
void car_h_28(double *state, double *unused, double *out_3419562905784198019) {
  h_28(state, unused, out_3419562905784198019);
}
void car_H_28(double *state, double *unused, double *out_8707505079262058708) {
  H_28(state, unused, out_8707505079262058708);
}
void car_h_31(double *state, double *unused, double *out_5280156946080479537) {
  h_31(state, unused, out_5280156946080479537);
}
void car_H_31(double *state, double *unused, double *out_6623024403137208517) {
  H_31(state, unused, out_6623024403137208517);
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
