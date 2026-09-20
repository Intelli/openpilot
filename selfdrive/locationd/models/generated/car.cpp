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
void err_fun(double *nom_x, double *delta_x, double *out_4230123520330551295) {
   out_4230123520330551295[0] = delta_x[0] + nom_x[0];
   out_4230123520330551295[1] = delta_x[1] + nom_x[1];
   out_4230123520330551295[2] = delta_x[2] + nom_x[2];
   out_4230123520330551295[3] = delta_x[3] + nom_x[3];
   out_4230123520330551295[4] = delta_x[4] + nom_x[4];
   out_4230123520330551295[5] = delta_x[5] + nom_x[5];
   out_4230123520330551295[6] = delta_x[6] + nom_x[6];
   out_4230123520330551295[7] = delta_x[7] + nom_x[7];
   out_4230123520330551295[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3558665329655221205) {
   out_3558665329655221205[0] = -nom_x[0] + true_x[0];
   out_3558665329655221205[1] = -nom_x[1] + true_x[1];
   out_3558665329655221205[2] = -nom_x[2] + true_x[2];
   out_3558665329655221205[3] = -nom_x[3] + true_x[3];
   out_3558665329655221205[4] = -nom_x[4] + true_x[4];
   out_3558665329655221205[5] = -nom_x[5] + true_x[5];
   out_3558665329655221205[6] = -nom_x[6] + true_x[6];
   out_3558665329655221205[7] = -nom_x[7] + true_x[7];
   out_3558665329655221205[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_553175090804179771) {
   out_553175090804179771[0] = 1.0;
   out_553175090804179771[1] = 0.0;
   out_553175090804179771[2] = 0.0;
   out_553175090804179771[3] = 0.0;
   out_553175090804179771[4] = 0.0;
   out_553175090804179771[5] = 0.0;
   out_553175090804179771[6] = 0.0;
   out_553175090804179771[7] = 0.0;
   out_553175090804179771[8] = 0.0;
   out_553175090804179771[9] = 0.0;
   out_553175090804179771[10] = 1.0;
   out_553175090804179771[11] = 0.0;
   out_553175090804179771[12] = 0.0;
   out_553175090804179771[13] = 0.0;
   out_553175090804179771[14] = 0.0;
   out_553175090804179771[15] = 0.0;
   out_553175090804179771[16] = 0.0;
   out_553175090804179771[17] = 0.0;
   out_553175090804179771[18] = 0.0;
   out_553175090804179771[19] = 0.0;
   out_553175090804179771[20] = 1.0;
   out_553175090804179771[21] = 0.0;
   out_553175090804179771[22] = 0.0;
   out_553175090804179771[23] = 0.0;
   out_553175090804179771[24] = 0.0;
   out_553175090804179771[25] = 0.0;
   out_553175090804179771[26] = 0.0;
   out_553175090804179771[27] = 0.0;
   out_553175090804179771[28] = 0.0;
   out_553175090804179771[29] = 0.0;
   out_553175090804179771[30] = 1.0;
   out_553175090804179771[31] = 0.0;
   out_553175090804179771[32] = 0.0;
   out_553175090804179771[33] = 0.0;
   out_553175090804179771[34] = 0.0;
   out_553175090804179771[35] = 0.0;
   out_553175090804179771[36] = 0.0;
   out_553175090804179771[37] = 0.0;
   out_553175090804179771[38] = 0.0;
   out_553175090804179771[39] = 0.0;
   out_553175090804179771[40] = 1.0;
   out_553175090804179771[41] = 0.0;
   out_553175090804179771[42] = 0.0;
   out_553175090804179771[43] = 0.0;
   out_553175090804179771[44] = 0.0;
   out_553175090804179771[45] = 0.0;
   out_553175090804179771[46] = 0.0;
   out_553175090804179771[47] = 0.0;
   out_553175090804179771[48] = 0.0;
   out_553175090804179771[49] = 0.0;
   out_553175090804179771[50] = 1.0;
   out_553175090804179771[51] = 0.0;
   out_553175090804179771[52] = 0.0;
   out_553175090804179771[53] = 0.0;
   out_553175090804179771[54] = 0.0;
   out_553175090804179771[55] = 0.0;
   out_553175090804179771[56] = 0.0;
   out_553175090804179771[57] = 0.0;
   out_553175090804179771[58] = 0.0;
   out_553175090804179771[59] = 0.0;
   out_553175090804179771[60] = 1.0;
   out_553175090804179771[61] = 0.0;
   out_553175090804179771[62] = 0.0;
   out_553175090804179771[63] = 0.0;
   out_553175090804179771[64] = 0.0;
   out_553175090804179771[65] = 0.0;
   out_553175090804179771[66] = 0.0;
   out_553175090804179771[67] = 0.0;
   out_553175090804179771[68] = 0.0;
   out_553175090804179771[69] = 0.0;
   out_553175090804179771[70] = 1.0;
   out_553175090804179771[71] = 0.0;
   out_553175090804179771[72] = 0.0;
   out_553175090804179771[73] = 0.0;
   out_553175090804179771[74] = 0.0;
   out_553175090804179771[75] = 0.0;
   out_553175090804179771[76] = 0.0;
   out_553175090804179771[77] = 0.0;
   out_553175090804179771[78] = 0.0;
   out_553175090804179771[79] = 0.0;
   out_553175090804179771[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4521756381782259895) {
   out_4521756381782259895[0] = state[0];
   out_4521756381782259895[1] = state[1];
   out_4521756381782259895[2] = state[2];
   out_4521756381782259895[3] = state[3];
   out_4521756381782259895[4] = state[4];
   out_4521756381782259895[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4521756381782259895[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4521756381782259895[7] = state[7];
   out_4521756381782259895[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2346473426156925819) {
   out_2346473426156925819[0] = 1;
   out_2346473426156925819[1] = 0;
   out_2346473426156925819[2] = 0;
   out_2346473426156925819[3] = 0;
   out_2346473426156925819[4] = 0;
   out_2346473426156925819[5] = 0;
   out_2346473426156925819[6] = 0;
   out_2346473426156925819[7] = 0;
   out_2346473426156925819[8] = 0;
   out_2346473426156925819[9] = 0;
   out_2346473426156925819[10] = 1;
   out_2346473426156925819[11] = 0;
   out_2346473426156925819[12] = 0;
   out_2346473426156925819[13] = 0;
   out_2346473426156925819[14] = 0;
   out_2346473426156925819[15] = 0;
   out_2346473426156925819[16] = 0;
   out_2346473426156925819[17] = 0;
   out_2346473426156925819[18] = 0;
   out_2346473426156925819[19] = 0;
   out_2346473426156925819[20] = 1;
   out_2346473426156925819[21] = 0;
   out_2346473426156925819[22] = 0;
   out_2346473426156925819[23] = 0;
   out_2346473426156925819[24] = 0;
   out_2346473426156925819[25] = 0;
   out_2346473426156925819[26] = 0;
   out_2346473426156925819[27] = 0;
   out_2346473426156925819[28] = 0;
   out_2346473426156925819[29] = 0;
   out_2346473426156925819[30] = 1;
   out_2346473426156925819[31] = 0;
   out_2346473426156925819[32] = 0;
   out_2346473426156925819[33] = 0;
   out_2346473426156925819[34] = 0;
   out_2346473426156925819[35] = 0;
   out_2346473426156925819[36] = 0;
   out_2346473426156925819[37] = 0;
   out_2346473426156925819[38] = 0;
   out_2346473426156925819[39] = 0;
   out_2346473426156925819[40] = 1;
   out_2346473426156925819[41] = 0;
   out_2346473426156925819[42] = 0;
   out_2346473426156925819[43] = 0;
   out_2346473426156925819[44] = 0;
   out_2346473426156925819[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2346473426156925819[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2346473426156925819[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2346473426156925819[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2346473426156925819[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2346473426156925819[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2346473426156925819[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2346473426156925819[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2346473426156925819[53] = -9.8100000000000005*dt;
   out_2346473426156925819[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2346473426156925819[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2346473426156925819[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2346473426156925819[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2346473426156925819[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2346473426156925819[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2346473426156925819[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2346473426156925819[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2346473426156925819[62] = 0;
   out_2346473426156925819[63] = 0;
   out_2346473426156925819[64] = 0;
   out_2346473426156925819[65] = 0;
   out_2346473426156925819[66] = 0;
   out_2346473426156925819[67] = 0;
   out_2346473426156925819[68] = 0;
   out_2346473426156925819[69] = 0;
   out_2346473426156925819[70] = 1;
   out_2346473426156925819[71] = 0;
   out_2346473426156925819[72] = 0;
   out_2346473426156925819[73] = 0;
   out_2346473426156925819[74] = 0;
   out_2346473426156925819[75] = 0;
   out_2346473426156925819[76] = 0;
   out_2346473426156925819[77] = 0;
   out_2346473426156925819[78] = 0;
   out_2346473426156925819[79] = 0;
   out_2346473426156925819[80] = 1;
}
void h_25(double *state, double *unused, double *out_4511589462972267238) {
   out_4511589462972267238[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4918975567879080240) {
   out_4918975567879080240[0] = 0;
   out_4918975567879080240[1] = 0;
   out_4918975567879080240[2] = 0;
   out_4918975567879080240[3] = 0;
   out_4918975567879080240[4] = 0;
   out_4918975567879080240[5] = 0;
   out_4918975567879080240[6] = 1;
   out_4918975567879080240[7] = 0;
   out_4918975567879080240[8] = 0;
}
void h_24(double *state, double *unused, double *out_7653285293992697712) {
   out_7653285293992697712[0] = state[4];
   out_7653285293992697712[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8476901166681403376) {
   out_8476901166681403376[0] = 0;
   out_8476901166681403376[1] = 0;
   out_8476901166681403376[2] = 0;
   out_8476901166681403376[3] = 0;
   out_8476901166681403376[4] = 1;
   out_8476901166681403376[5] = 0;
   out_8476901166681403376[6] = 0;
   out_8476901166681403376[7] = 0;
   out_8476901166681403376[8] = 0;
   out_8476901166681403376[9] = 0;
   out_8476901166681403376[10] = 0;
   out_8476901166681403376[11] = 0;
   out_8476901166681403376[12] = 0;
   out_8476901166681403376[13] = 0;
   out_8476901166681403376[14] = 1;
   out_8476901166681403376[15] = 0;
   out_8476901166681403376[16] = 0;
   out_8476901166681403376[17] = 0;
}
void h_30(double *state, double *unused, double *out_3251675793848405203) {
   out_3251675793848405203[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6611078164338854621) {
   out_6611078164338854621[0] = 0;
   out_6611078164338854621[1] = 0;
   out_6611078164338854621[2] = 0;
   out_6611078164338854621[3] = 0;
   out_6611078164338854621[4] = 1;
   out_6611078164338854621[5] = 0;
   out_6611078164338854621[6] = 0;
   out_6611078164338854621[7] = 0;
   out_6611078164338854621[8] = 0;
}
void h_26(double *state, double *unused, double *out_4183467640580295610) {
   out_4183467640580295610[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5575829631989392144) {
   out_5575829631989392144[0] = 0;
   out_5575829631989392144[1] = 0;
   out_5575829631989392144[2] = 0;
   out_5575829631989392144[3] = 0;
   out_5575829631989392144[4] = 0;
   out_5575829631989392144[5] = 0;
   out_5575829631989392144[6] = 0;
   out_5575829631989392144[7] = 1;
   out_5575829631989392144[8] = 0;
}
void h_27(double *state, double *unused, double *out_1887452054441581908) {
   out_1887452054441581908[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8785841476139279532) {
   out_8785841476139279532[0] = 0;
   out_8785841476139279532[1] = 0;
   out_8785841476139279532[2] = 0;
   out_8785841476139279532[3] = 1;
   out_8785841476139279532[4] = 0;
   out_8785841476139279532[5] = 0;
   out_8785841476139279532[6] = 0;
   out_8785841476139279532[7] = 0;
   out_8785841476139279532[8] = 0;
}
void h_29(double *state, double *unused, double *out_1749997473812440442) {
   out_1749997473812440442[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6100846820024462437) {
   out_6100846820024462437[0] = 0;
   out_6100846820024462437[1] = 1;
   out_6100846820024462437[2] = 0;
   out_6100846820024462437[3] = 0;
   out_6100846820024462437[4] = 0;
   out_6100846820024462437[5] = 0;
   out_6100846820024462437[6] = 0;
   out_6100846820024462437[7] = 0;
   out_6100846820024462437[8] = 0;
}
void h_28(double *state, double *unused, double *out_7577322847261128943) {
   out_7577322847261128943[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7263498236615558605) {
   out_7263498236615558605[0] = 1;
   out_7263498236615558605[1] = 0;
   out_7263498236615558605[2] = 0;
   out_7263498236615558605[3] = 0;
   out_7263498236615558605[4] = 0;
   out_7263498236615558605[5] = 0;
   out_7263498236615558605[6] = 0;
   out_7263498236615558605[7] = 0;
   out_7263498236615558605[8] = 0;
}
void h_31(double *state, double *unused, double *out_7164319384386933442) {
   out_7164319384386933442[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4949621529756040668) {
   out_4949621529756040668[0] = 0;
   out_4949621529756040668[1] = 0;
   out_4949621529756040668[2] = 0;
   out_4949621529756040668[3] = 0;
   out_4949621529756040668[4] = 0;
   out_4949621529756040668[5] = 0;
   out_4949621529756040668[6] = 0;
   out_4949621529756040668[7] = 0;
   out_4949621529756040668[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4230123520330551295) {
  err_fun(nom_x, delta_x, out_4230123520330551295);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3558665329655221205) {
  inv_err_fun(nom_x, true_x, out_3558665329655221205);
}
void car_H_mod_fun(double *state, double *out_553175090804179771) {
  H_mod_fun(state, out_553175090804179771);
}
void car_f_fun(double *state, double dt, double *out_4521756381782259895) {
  f_fun(state,  dt, out_4521756381782259895);
}
void car_F_fun(double *state, double dt, double *out_2346473426156925819) {
  F_fun(state,  dt, out_2346473426156925819);
}
void car_h_25(double *state, double *unused, double *out_4511589462972267238) {
  h_25(state, unused, out_4511589462972267238);
}
void car_H_25(double *state, double *unused, double *out_4918975567879080240) {
  H_25(state, unused, out_4918975567879080240);
}
void car_h_24(double *state, double *unused, double *out_7653285293992697712) {
  h_24(state, unused, out_7653285293992697712);
}
void car_H_24(double *state, double *unused, double *out_8476901166681403376) {
  H_24(state, unused, out_8476901166681403376);
}
void car_h_30(double *state, double *unused, double *out_3251675793848405203) {
  h_30(state, unused, out_3251675793848405203);
}
void car_H_30(double *state, double *unused, double *out_6611078164338854621) {
  H_30(state, unused, out_6611078164338854621);
}
void car_h_26(double *state, double *unused, double *out_4183467640580295610) {
  h_26(state, unused, out_4183467640580295610);
}
void car_H_26(double *state, double *unused, double *out_5575829631989392144) {
  H_26(state, unused, out_5575829631989392144);
}
void car_h_27(double *state, double *unused, double *out_1887452054441581908) {
  h_27(state, unused, out_1887452054441581908);
}
void car_H_27(double *state, double *unused, double *out_8785841476139279532) {
  H_27(state, unused, out_8785841476139279532);
}
void car_h_29(double *state, double *unused, double *out_1749997473812440442) {
  h_29(state, unused, out_1749997473812440442);
}
void car_H_29(double *state, double *unused, double *out_6100846820024462437) {
  H_29(state, unused, out_6100846820024462437);
}
void car_h_28(double *state, double *unused, double *out_7577322847261128943) {
  h_28(state, unused, out_7577322847261128943);
}
void car_H_28(double *state, double *unused, double *out_7263498236615558605) {
  H_28(state, unused, out_7263498236615558605);
}
void car_h_31(double *state, double *unused, double *out_7164319384386933442) {
  h_31(state, unused, out_7164319384386933442);
}
void car_H_31(double *state, double *unused, double *out_4949621529756040668) {
  H_31(state, unused, out_4949621529756040668);
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
