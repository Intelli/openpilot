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
void err_fun(double *nom_x, double *delta_x, double *out_1227793143144495277) {
   out_1227793143144495277[0] = delta_x[0] + nom_x[0];
   out_1227793143144495277[1] = delta_x[1] + nom_x[1];
   out_1227793143144495277[2] = delta_x[2] + nom_x[2];
   out_1227793143144495277[3] = delta_x[3] + nom_x[3];
   out_1227793143144495277[4] = delta_x[4] + nom_x[4];
   out_1227793143144495277[5] = delta_x[5] + nom_x[5];
   out_1227793143144495277[6] = delta_x[6] + nom_x[6];
   out_1227793143144495277[7] = delta_x[7] + nom_x[7];
   out_1227793143144495277[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_377220753251568338) {
   out_377220753251568338[0] = -nom_x[0] + true_x[0];
   out_377220753251568338[1] = -nom_x[1] + true_x[1];
   out_377220753251568338[2] = -nom_x[2] + true_x[2];
   out_377220753251568338[3] = -nom_x[3] + true_x[3];
   out_377220753251568338[4] = -nom_x[4] + true_x[4];
   out_377220753251568338[5] = -nom_x[5] + true_x[5];
   out_377220753251568338[6] = -nom_x[6] + true_x[6];
   out_377220753251568338[7] = -nom_x[7] + true_x[7];
   out_377220753251568338[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4965179062603390678) {
   out_4965179062603390678[0] = 1.0;
   out_4965179062603390678[1] = 0.0;
   out_4965179062603390678[2] = 0.0;
   out_4965179062603390678[3] = 0.0;
   out_4965179062603390678[4] = 0.0;
   out_4965179062603390678[5] = 0.0;
   out_4965179062603390678[6] = 0.0;
   out_4965179062603390678[7] = 0.0;
   out_4965179062603390678[8] = 0.0;
   out_4965179062603390678[9] = 0.0;
   out_4965179062603390678[10] = 1.0;
   out_4965179062603390678[11] = 0.0;
   out_4965179062603390678[12] = 0.0;
   out_4965179062603390678[13] = 0.0;
   out_4965179062603390678[14] = 0.0;
   out_4965179062603390678[15] = 0.0;
   out_4965179062603390678[16] = 0.0;
   out_4965179062603390678[17] = 0.0;
   out_4965179062603390678[18] = 0.0;
   out_4965179062603390678[19] = 0.0;
   out_4965179062603390678[20] = 1.0;
   out_4965179062603390678[21] = 0.0;
   out_4965179062603390678[22] = 0.0;
   out_4965179062603390678[23] = 0.0;
   out_4965179062603390678[24] = 0.0;
   out_4965179062603390678[25] = 0.0;
   out_4965179062603390678[26] = 0.0;
   out_4965179062603390678[27] = 0.0;
   out_4965179062603390678[28] = 0.0;
   out_4965179062603390678[29] = 0.0;
   out_4965179062603390678[30] = 1.0;
   out_4965179062603390678[31] = 0.0;
   out_4965179062603390678[32] = 0.0;
   out_4965179062603390678[33] = 0.0;
   out_4965179062603390678[34] = 0.0;
   out_4965179062603390678[35] = 0.0;
   out_4965179062603390678[36] = 0.0;
   out_4965179062603390678[37] = 0.0;
   out_4965179062603390678[38] = 0.0;
   out_4965179062603390678[39] = 0.0;
   out_4965179062603390678[40] = 1.0;
   out_4965179062603390678[41] = 0.0;
   out_4965179062603390678[42] = 0.0;
   out_4965179062603390678[43] = 0.0;
   out_4965179062603390678[44] = 0.0;
   out_4965179062603390678[45] = 0.0;
   out_4965179062603390678[46] = 0.0;
   out_4965179062603390678[47] = 0.0;
   out_4965179062603390678[48] = 0.0;
   out_4965179062603390678[49] = 0.0;
   out_4965179062603390678[50] = 1.0;
   out_4965179062603390678[51] = 0.0;
   out_4965179062603390678[52] = 0.0;
   out_4965179062603390678[53] = 0.0;
   out_4965179062603390678[54] = 0.0;
   out_4965179062603390678[55] = 0.0;
   out_4965179062603390678[56] = 0.0;
   out_4965179062603390678[57] = 0.0;
   out_4965179062603390678[58] = 0.0;
   out_4965179062603390678[59] = 0.0;
   out_4965179062603390678[60] = 1.0;
   out_4965179062603390678[61] = 0.0;
   out_4965179062603390678[62] = 0.0;
   out_4965179062603390678[63] = 0.0;
   out_4965179062603390678[64] = 0.0;
   out_4965179062603390678[65] = 0.0;
   out_4965179062603390678[66] = 0.0;
   out_4965179062603390678[67] = 0.0;
   out_4965179062603390678[68] = 0.0;
   out_4965179062603390678[69] = 0.0;
   out_4965179062603390678[70] = 1.0;
   out_4965179062603390678[71] = 0.0;
   out_4965179062603390678[72] = 0.0;
   out_4965179062603390678[73] = 0.0;
   out_4965179062603390678[74] = 0.0;
   out_4965179062603390678[75] = 0.0;
   out_4965179062603390678[76] = 0.0;
   out_4965179062603390678[77] = 0.0;
   out_4965179062603390678[78] = 0.0;
   out_4965179062603390678[79] = 0.0;
   out_4965179062603390678[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5021644498978266308) {
   out_5021644498978266308[0] = state[0];
   out_5021644498978266308[1] = state[1];
   out_5021644498978266308[2] = state[2];
   out_5021644498978266308[3] = state[3];
   out_5021644498978266308[4] = state[4];
   out_5021644498978266308[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5021644498978266308[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5021644498978266308[7] = state[7];
   out_5021644498978266308[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4137309702793038373) {
   out_4137309702793038373[0] = 1;
   out_4137309702793038373[1] = 0;
   out_4137309702793038373[2] = 0;
   out_4137309702793038373[3] = 0;
   out_4137309702793038373[4] = 0;
   out_4137309702793038373[5] = 0;
   out_4137309702793038373[6] = 0;
   out_4137309702793038373[7] = 0;
   out_4137309702793038373[8] = 0;
   out_4137309702793038373[9] = 0;
   out_4137309702793038373[10] = 1;
   out_4137309702793038373[11] = 0;
   out_4137309702793038373[12] = 0;
   out_4137309702793038373[13] = 0;
   out_4137309702793038373[14] = 0;
   out_4137309702793038373[15] = 0;
   out_4137309702793038373[16] = 0;
   out_4137309702793038373[17] = 0;
   out_4137309702793038373[18] = 0;
   out_4137309702793038373[19] = 0;
   out_4137309702793038373[20] = 1;
   out_4137309702793038373[21] = 0;
   out_4137309702793038373[22] = 0;
   out_4137309702793038373[23] = 0;
   out_4137309702793038373[24] = 0;
   out_4137309702793038373[25] = 0;
   out_4137309702793038373[26] = 0;
   out_4137309702793038373[27] = 0;
   out_4137309702793038373[28] = 0;
   out_4137309702793038373[29] = 0;
   out_4137309702793038373[30] = 1;
   out_4137309702793038373[31] = 0;
   out_4137309702793038373[32] = 0;
   out_4137309702793038373[33] = 0;
   out_4137309702793038373[34] = 0;
   out_4137309702793038373[35] = 0;
   out_4137309702793038373[36] = 0;
   out_4137309702793038373[37] = 0;
   out_4137309702793038373[38] = 0;
   out_4137309702793038373[39] = 0;
   out_4137309702793038373[40] = 1;
   out_4137309702793038373[41] = 0;
   out_4137309702793038373[42] = 0;
   out_4137309702793038373[43] = 0;
   out_4137309702793038373[44] = 0;
   out_4137309702793038373[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4137309702793038373[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4137309702793038373[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4137309702793038373[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4137309702793038373[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4137309702793038373[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4137309702793038373[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4137309702793038373[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4137309702793038373[53] = -9.8100000000000005*dt;
   out_4137309702793038373[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4137309702793038373[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4137309702793038373[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4137309702793038373[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4137309702793038373[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4137309702793038373[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4137309702793038373[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4137309702793038373[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4137309702793038373[62] = 0;
   out_4137309702793038373[63] = 0;
   out_4137309702793038373[64] = 0;
   out_4137309702793038373[65] = 0;
   out_4137309702793038373[66] = 0;
   out_4137309702793038373[67] = 0;
   out_4137309702793038373[68] = 0;
   out_4137309702793038373[69] = 0;
   out_4137309702793038373[70] = 1;
   out_4137309702793038373[71] = 0;
   out_4137309702793038373[72] = 0;
   out_4137309702793038373[73] = 0;
   out_4137309702793038373[74] = 0;
   out_4137309702793038373[75] = 0;
   out_4137309702793038373[76] = 0;
   out_4137309702793038373[77] = 0;
   out_4137309702793038373[78] = 0;
   out_4137309702793038373[79] = 0;
   out_4137309702793038373[80] = 1;
}
void h_25(double *state, double *unused, double *out_5010515879516742558) {
   out_5010515879516742558[0] = state[6];
}
void H_25(double *state, double *unused, double *out_61487237418725838) {
   out_61487237418725838[0] = 0;
   out_61487237418725838[1] = 0;
   out_61487237418725838[2] = 0;
   out_61487237418725838[3] = 0;
   out_61487237418725838[4] = 0;
   out_61487237418725838[5] = 0;
   out_61487237418725838[6] = 1;
   out_61487237418725838[7] = 0;
   out_61487237418725838[8] = 0;
}
void h_24(double *state, double *unused, double *out_2332165883187586177) {
   out_2332165883187586177[0] = state[4];
   out_2332165883187586177[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6262519917269887264) {
   out_6262519917269887264[0] = 0;
   out_6262519917269887264[1] = 0;
   out_6262519917269887264[2] = 0;
   out_6262519917269887264[3] = 0;
   out_6262519917269887264[4] = 1;
   out_6262519917269887264[5] = 0;
   out_6262519917269887264[6] = 0;
   out_6262519917269887264[7] = 0;
   out_6262519917269887264[8] = 0;
   out_6262519917269887264[9] = 0;
   out_6262519917269887264[10] = 0;
   out_6262519917269887264[11] = 0;
   out_6262519917269887264[12] = 0;
   out_6262519917269887264[13] = 0;
   out_6262519917269887264[14] = 1;
   out_6262519917269887264[15] = 0;
   out_6262519917269887264[16] = 0;
   out_6262519917269887264[17] = 0;
}
void h_30(double *state, double *unused, double *out_7792163363708409201) {
   out_7792163363708409201[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6855203104072890917) {
   out_6855203104072890917[0] = 0;
   out_6855203104072890917[1] = 0;
   out_6855203104072890917[2] = 0;
   out_6855203104072890917[3] = 0;
   out_6855203104072890917[4] = 1;
   out_6855203104072890917[5] = 0;
   out_6855203104072890917[6] = 0;
   out_6855203104072890917[7] = 0;
   out_6855203104072890917[8] = 0;
}
void h_26(double *state, double *unused, double *out_1393121846294560055) {
   out_1393121846294560055[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3802990556292782062) {
   out_3802990556292782062[0] = 0;
   out_3802990556292782062[1] = 0;
   out_3802990556292782062[2] = 0;
   out_3802990556292782062[3] = 0;
   out_3802990556292782062[4] = 0;
   out_3802990556292782062[5] = 0;
   out_3802990556292782062[6] = 0;
   out_3802990556292782062[7] = 1;
   out_3802990556292782062[8] = 0;
}
void h_27(double *state, double *unused, double *out_2424627554911958255) {
   out_2424627554911958255[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4680439792272466006) {
   out_4680439792272466006[0] = 0;
   out_4680439792272466006[1] = 0;
   out_4680439792272466006[2] = 0;
   out_4680439792272466006[3] = 1;
   out_4680439792272466006[4] = 0;
   out_4680439792272466006[5] = 0;
   out_4680439792272466006[6] = 0;
   out_4680439792272466006[7] = 0;
   out_4680439792272466006[8] = 0;
}
void h_29(double *state, double *unused, double *out_2149433492627452366) {
   out_2149433492627452366[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2967077065402914973) {
   out_2967077065402914973[0] = 0;
   out_2967077065402914973[1] = 1;
   out_2967077065402914973[2] = 0;
   out_2967077065402914973[3] = 0;
   out_2967077065402914973[4] = 0;
   out_2967077065402914973[5] = 0;
   out_2967077065402914973[6] = 0;
   out_2967077065402914973[7] = 0;
   out_2967077065402914973[8] = 0;
}
void h_28(double *state, double *unused, double *out_4009194011233731880) {
   out_4009194011233731880[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2115321951666615601) {
   out_2115321951666615601[0] = 1;
   out_2115321951666615601[1] = 0;
   out_2115321951666615601[2] = 0;
   out_2115321951666615601[3] = 0;
   out_2115321951666615601[4] = 0;
   out_2115321951666615601[5] = 0;
   out_2115321951666615601[6] = 0;
   out_2115321951666615601[7] = 0;
   out_2115321951666615601[8] = 0;
}
void h_31(double *state, double *unused, double *out_1070359858690936092) {
   out_1070359858690936092[0] = state[8];
}
void H_31(double *state, double *unused, double *out_30841275541765410) {
   out_30841275541765410[0] = 0;
   out_30841275541765410[1] = 0;
   out_30841275541765410[2] = 0;
   out_30841275541765410[3] = 0;
   out_30841275541765410[4] = 0;
   out_30841275541765410[5] = 0;
   out_30841275541765410[6] = 0;
   out_30841275541765410[7] = 0;
   out_30841275541765410[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_1227793143144495277) {
  err_fun(nom_x, delta_x, out_1227793143144495277);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_377220753251568338) {
  inv_err_fun(nom_x, true_x, out_377220753251568338);
}
void car_H_mod_fun(double *state, double *out_4965179062603390678) {
  H_mod_fun(state, out_4965179062603390678);
}
void car_f_fun(double *state, double dt, double *out_5021644498978266308) {
  f_fun(state,  dt, out_5021644498978266308);
}
void car_F_fun(double *state, double dt, double *out_4137309702793038373) {
  F_fun(state,  dt, out_4137309702793038373);
}
void car_h_25(double *state, double *unused, double *out_5010515879516742558) {
  h_25(state, unused, out_5010515879516742558);
}
void car_H_25(double *state, double *unused, double *out_61487237418725838) {
  H_25(state, unused, out_61487237418725838);
}
void car_h_24(double *state, double *unused, double *out_2332165883187586177) {
  h_24(state, unused, out_2332165883187586177);
}
void car_H_24(double *state, double *unused, double *out_6262519917269887264) {
  H_24(state, unused, out_6262519917269887264);
}
void car_h_30(double *state, double *unused, double *out_7792163363708409201) {
  h_30(state, unused, out_7792163363708409201);
}
void car_H_30(double *state, double *unused, double *out_6855203104072890917) {
  H_30(state, unused, out_6855203104072890917);
}
void car_h_26(double *state, double *unused, double *out_1393121846294560055) {
  h_26(state, unused, out_1393121846294560055);
}
void car_H_26(double *state, double *unused, double *out_3802990556292782062) {
  H_26(state, unused, out_3802990556292782062);
}
void car_h_27(double *state, double *unused, double *out_2424627554911958255) {
  h_27(state, unused, out_2424627554911958255);
}
void car_H_27(double *state, double *unused, double *out_4680439792272466006) {
  H_27(state, unused, out_4680439792272466006);
}
void car_h_29(double *state, double *unused, double *out_2149433492627452366) {
  h_29(state, unused, out_2149433492627452366);
}
void car_H_29(double *state, double *unused, double *out_2967077065402914973) {
  H_29(state, unused, out_2967077065402914973);
}
void car_h_28(double *state, double *unused, double *out_4009194011233731880) {
  h_28(state, unused, out_4009194011233731880);
}
void car_H_28(double *state, double *unused, double *out_2115321951666615601) {
  H_28(state, unused, out_2115321951666615601);
}
void car_h_31(double *state, double *unused, double *out_1070359858690936092) {
  h_31(state, unused, out_1070359858690936092);
}
void car_H_31(double *state, double *unused, double *out_30841275541765410) {
  H_31(state, unused, out_30841275541765410);
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
