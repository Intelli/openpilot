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
void err_fun(double *nom_x, double *delta_x, double *out_2875077231426279529) {
   out_2875077231426279529[0] = delta_x[0] + nom_x[0];
   out_2875077231426279529[1] = delta_x[1] + nom_x[1];
   out_2875077231426279529[2] = delta_x[2] + nom_x[2];
   out_2875077231426279529[3] = delta_x[3] + nom_x[3];
   out_2875077231426279529[4] = delta_x[4] + nom_x[4];
   out_2875077231426279529[5] = delta_x[5] + nom_x[5];
   out_2875077231426279529[6] = delta_x[6] + nom_x[6];
   out_2875077231426279529[7] = delta_x[7] + nom_x[7];
   out_2875077231426279529[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7764517582708413116) {
   out_7764517582708413116[0] = -nom_x[0] + true_x[0];
   out_7764517582708413116[1] = -nom_x[1] + true_x[1];
   out_7764517582708413116[2] = -nom_x[2] + true_x[2];
   out_7764517582708413116[3] = -nom_x[3] + true_x[3];
   out_7764517582708413116[4] = -nom_x[4] + true_x[4];
   out_7764517582708413116[5] = -nom_x[5] + true_x[5];
   out_7764517582708413116[6] = -nom_x[6] + true_x[6];
   out_7764517582708413116[7] = -nom_x[7] + true_x[7];
   out_7764517582708413116[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1362034626282984391) {
   out_1362034626282984391[0] = 1.0;
   out_1362034626282984391[1] = 0.0;
   out_1362034626282984391[2] = 0.0;
   out_1362034626282984391[3] = 0.0;
   out_1362034626282984391[4] = 0.0;
   out_1362034626282984391[5] = 0.0;
   out_1362034626282984391[6] = 0.0;
   out_1362034626282984391[7] = 0.0;
   out_1362034626282984391[8] = 0.0;
   out_1362034626282984391[9] = 0.0;
   out_1362034626282984391[10] = 1.0;
   out_1362034626282984391[11] = 0.0;
   out_1362034626282984391[12] = 0.0;
   out_1362034626282984391[13] = 0.0;
   out_1362034626282984391[14] = 0.0;
   out_1362034626282984391[15] = 0.0;
   out_1362034626282984391[16] = 0.0;
   out_1362034626282984391[17] = 0.0;
   out_1362034626282984391[18] = 0.0;
   out_1362034626282984391[19] = 0.0;
   out_1362034626282984391[20] = 1.0;
   out_1362034626282984391[21] = 0.0;
   out_1362034626282984391[22] = 0.0;
   out_1362034626282984391[23] = 0.0;
   out_1362034626282984391[24] = 0.0;
   out_1362034626282984391[25] = 0.0;
   out_1362034626282984391[26] = 0.0;
   out_1362034626282984391[27] = 0.0;
   out_1362034626282984391[28] = 0.0;
   out_1362034626282984391[29] = 0.0;
   out_1362034626282984391[30] = 1.0;
   out_1362034626282984391[31] = 0.0;
   out_1362034626282984391[32] = 0.0;
   out_1362034626282984391[33] = 0.0;
   out_1362034626282984391[34] = 0.0;
   out_1362034626282984391[35] = 0.0;
   out_1362034626282984391[36] = 0.0;
   out_1362034626282984391[37] = 0.0;
   out_1362034626282984391[38] = 0.0;
   out_1362034626282984391[39] = 0.0;
   out_1362034626282984391[40] = 1.0;
   out_1362034626282984391[41] = 0.0;
   out_1362034626282984391[42] = 0.0;
   out_1362034626282984391[43] = 0.0;
   out_1362034626282984391[44] = 0.0;
   out_1362034626282984391[45] = 0.0;
   out_1362034626282984391[46] = 0.0;
   out_1362034626282984391[47] = 0.0;
   out_1362034626282984391[48] = 0.0;
   out_1362034626282984391[49] = 0.0;
   out_1362034626282984391[50] = 1.0;
   out_1362034626282984391[51] = 0.0;
   out_1362034626282984391[52] = 0.0;
   out_1362034626282984391[53] = 0.0;
   out_1362034626282984391[54] = 0.0;
   out_1362034626282984391[55] = 0.0;
   out_1362034626282984391[56] = 0.0;
   out_1362034626282984391[57] = 0.0;
   out_1362034626282984391[58] = 0.0;
   out_1362034626282984391[59] = 0.0;
   out_1362034626282984391[60] = 1.0;
   out_1362034626282984391[61] = 0.0;
   out_1362034626282984391[62] = 0.0;
   out_1362034626282984391[63] = 0.0;
   out_1362034626282984391[64] = 0.0;
   out_1362034626282984391[65] = 0.0;
   out_1362034626282984391[66] = 0.0;
   out_1362034626282984391[67] = 0.0;
   out_1362034626282984391[68] = 0.0;
   out_1362034626282984391[69] = 0.0;
   out_1362034626282984391[70] = 1.0;
   out_1362034626282984391[71] = 0.0;
   out_1362034626282984391[72] = 0.0;
   out_1362034626282984391[73] = 0.0;
   out_1362034626282984391[74] = 0.0;
   out_1362034626282984391[75] = 0.0;
   out_1362034626282984391[76] = 0.0;
   out_1362034626282984391[77] = 0.0;
   out_1362034626282984391[78] = 0.0;
   out_1362034626282984391[79] = 0.0;
   out_1362034626282984391[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4861076963360172947) {
   out_4861076963360172947[0] = state[0];
   out_4861076963360172947[1] = state[1];
   out_4861076963360172947[2] = state[2];
   out_4861076963360172947[3] = state[3];
   out_4861076963360172947[4] = state[4];
   out_4861076963360172947[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4861076963360172947[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4861076963360172947[7] = state[7];
   out_4861076963360172947[8] = state[8];
}
void F_fun(double *state, double dt, double *out_344082542095483460) {
   out_344082542095483460[0] = 1;
   out_344082542095483460[1] = 0;
   out_344082542095483460[2] = 0;
   out_344082542095483460[3] = 0;
   out_344082542095483460[4] = 0;
   out_344082542095483460[5] = 0;
   out_344082542095483460[6] = 0;
   out_344082542095483460[7] = 0;
   out_344082542095483460[8] = 0;
   out_344082542095483460[9] = 0;
   out_344082542095483460[10] = 1;
   out_344082542095483460[11] = 0;
   out_344082542095483460[12] = 0;
   out_344082542095483460[13] = 0;
   out_344082542095483460[14] = 0;
   out_344082542095483460[15] = 0;
   out_344082542095483460[16] = 0;
   out_344082542095483460[17] = 0;
   out_344082542095483460[18] = 0;
   out_344082542095483460[19] = 0;
   out_344082542095483460[20] = 1;
   out_344082542095483460[21] = 0;
   out_344082542095483460[22] = 0;
   out_344082542095483460[23] = 0;
   out_344082542095483460[24] = 0;
   out_344082542095483460[25] = 0;
   out_344082542095483460[26] = 0;
   out_344082542095483460[27] = 0;
   out_344082542095483460[28] = 0;
   out_344082542095483460[29] = 0;
   out_344082542095483460[30] = 1;
   out_344082542095483460[31] = 0;
   out_344082542095483460[32] = 0;
   out_344082542095483460[33] = 0;
   out_344082542095483460[34] = 0;
   out_344082542095483460[35] = 0;
   out_344082542095483460[36] = 0;
   out_344082542095483460[37] = 0;
   out_344082542095483460[38] = 0;
   out_344082542095483460[39] = 0;
   out_344082542095483460[40] = 1;
   out_344082542095483460[41] = 0;
   out_344082542095483460[42] = 0;
   out_344082542095483460[43] = 0;
   out_344082542095483460[44] = 0;
   out_344082542095483460[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_344082542095483460[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_344082542095483460[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_344082542095483460[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_344082542095483460[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_344082542095483460[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_344082542095483460[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_344082542095483460[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_344082542095483460[53] = -9.8100000000000005*dt;
   out_344082542095483460[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_344082542095483460[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_344082542095483460[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_344082542095483460[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_344082542095483460[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_344082542095483460[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_344082542095483460[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_344082542095483460[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_344082542095483460[62] = 0;
   out_344082542095483460[63] = 0;
   out_344082542095483460[64] = 0;
   out_344082542095483460[65] = 0;
   out_344082542095483460[66] = 0;
   out_344082542095483460[67] = 0;
   out_344082542095483460[68] = 0;
   out_344082542095483460[69] = 0;
   out_344082542095483460[70] = 1;
   out_344082542095483460[71] = 0;
   out_344082542095483460[72] = 0;
   out_344082542095483460[73] = 0;
   out_344082542095483460[74] = 0;
   out_344082542095483460[75] = 0;
   out_344082542095483460[76] = 0;
   out_344082542095483460[77] = 0;
   out_344082542095483460[78] = 0;
   out_344082542095483460[79] = 0;
   out_344082542095483460[80] = 1;
}
void h_25(double *state, double *unused, double *out_6349540795286409135) {
   out_6349540795286409135[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6265726451467649231) {
   out_6265726451467649231[0] = 0;
   out_6265726451467649231[1] = 0;
   out_6265726451467649231[2] = 0;
   out_6265726451467649231[3] = 0;
   out_6265726451467649231[4] = 0;
   out_6265726451467649231[5] = 0;
   out_6265726451467649231[6] = 1;
   out_6265726451467649231[7] = 0;
   out_6265726451467649231[8] = 0;
}
void h_24(double *state, double *unused, double *out_2089055603068722673) {
   out_2089055603068722673[0] = state[4];
   out_2089055603068722673[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7953542887336753422) {
   out_7953542887336753422[0] = 0;
   out_7953542887336753422[1] = 0;
   out_7953542887336753422[2] = 0;
   out_7953542887336753422[3] = 0;
   out_7953542887336753422[4] = 1;
   out_7953542887336753422[5] = 0;
   out_7953542887336753422[6] = 0;
   out_7953542887336753422[7] = 0;
   out_7953542887336753422[8] = 0;
   out_7953542887336753422[9] = 0;
   out_7953542887336753422[10] = 0;
   out_7953542887336753422[11] = 0;
   out_7953542887336753422[12] = 0;
   out_7953542887336753422[13] = 0;
   out_7953542887336753422[14] = 1;
   out_7953542887336753422[15] = 0;
   out_7953542887336753422[16] = 0;
   out_7953542887336753422[17] = 0;
}
void h_30(double *state, double *unused, double *out_6192354126935279990) {
   out_6192354126935279990[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8784059409974897858) {
   out_8784059409974897858[0] = 0;
   out_8784059409974897858[1] = 0;
   out_8784059409974897858[2] = 0;
   out_8784059409974897858[3] = 0;
   out_8784059409974897858[4] = 1;
   out_8784059409974897858[5] = 0;
   out_8784059409974897858[6] = 0;
   out_8784059409974897858[7] = 0;
   out_8784059409974897858[8] = 0;
}
void h_26(double *state, double *unused, double *out_1190680859274434345) {
   out_1190680859274434345[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2524223132593593007) {
   out_2524223132593593007[0] = 0;
   out_2524223132593593007[1] = 0;
   out_2524223132593593007[2] = 0;
   out_2524223132593593007[3] = 0;
   out_2524223132593593007[4] = 0;
   out_2524223132593593007[5] = 0;
   out_2524223132593593007[6] = 0;
   out_2524223132593593007[7] = 1;
   out_2524223132593593007[8] = 0;
}
void h_27(double *state, double *unused, double *out_7174002555159601650) {
   out_7174002555159601650[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7439090592550710541) {
   out_7439090592550710541[0] = 0;
   out_7439090592550710541[1] = 0;
   out_7439090592550710541[2] = 0;
   out_7439090592550710541[3] = 1;
   out_7439090592550710541[4] = 0;
   out_7439090592550710541[5] = 0;
   out_7439090592550710541[6] = 0;
   out_7439090592550710541[7] = 0;
   out_7439090592550710541[8] = 0;
}
void h_29(double *state, double *unused, double *out_4501906292199599030) {
   out_4501906292199599030[0] = state[1];
}
void H_29(double *state, double *unused, double *out_9152453319420261574) {
   out_9152453319420261574[0] = 0;
   out_9152453319420261574[1] = 1;
   out_9152453319420261574[2] = 0;
   out_9152453319420261574[3] = 0;
   out_9152453319420261574[4] = 0;
   out_9152453319420261574[5] = 0;
   out_9152453319420261574[6] = 0;
   out_9152453319420261574[7] = 0;
   out_9152453319420261574[8] = 0;
}
void h_28(double *state, double *unused, double *out_5016916796590902712) {
   out_5016916796590902712[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4211891737219759468) {
   out_4211891737219759468[0] = 1;
   out_4211891737219759468[1] = 0;
   out_4211891737219759468[2] = 0;
   out_4211891737219759468[3] = 0;
   out_4211891737219759468[4] = 0;
   out_4211891737219759468[5] = 0;
   out_4211891737219759468[6] = 0;
   out_4211891737219759468[7] = 0;
   out_4211891737219759468[8] = 0;
}
void h_31(double *state, double *unused, double *out_4412410565999774854) {
   out_4412410565999774854[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6296372413344609659) {
   out_6296372413344609659[0] = 0;
   out_6296372413344609659[1] = 0;
   out_6296372413344609659[2] = 0;
   out_6296372413344609659[3] = 0;
   out_6296372413344609659[4] = 0;
   out_6296372413344609659[5] = 0;
   out_6296372413344609659[6] = 0;
   out_6296372413344609659[7] = 0;
   out_6296372413344609659[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2875077231426279529) {
  err_fun(nom_x, delta_x, out_2875077231426279529);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7764517582708413116) {
  inv_err_fun(nom_x, true_x, out_7764517582708413116);
}
void car_H_mod_fun(double *state, double *out_1362034626282984391) {
  H_mod_fun(state, out_1362034626282984391);
}
void car_f_fun(double *state, double dt, double *out_4861076963360172947) {
  f_fun(state,  dt, out_4861076963360172947);
}
void car_F_fun(double *state, double dt, double *out_344082542095483460) {
  F_fun(state,  dt, out_344082542095483460);
}
void car_h_25(double *state, double *unused, double *out_6349540795286409135) {
  h_25(state, unused, out_6349540795286409135);
}
void car_H_25(double *state, double *unused, double *out_6265726451467649231) {
  H_25(state, unused, out_6265726451467649231);
}
void car_h_24(double *state, double *unused, double *out_2089055603068722673) {
  h_24(state, unused, out_2089055603068722673);
}
void car_H_24(double *state, double *unused, double *out_7953542887336753422) {
  H_24(state, unused, out_7953542887336753422);
}
void car_h_30(double *state, double *unused, double *out_6192354126935279990) {
  h_30(state, unused, out_6192354126935279990);
}
void car_H_30(double *state, double *unused, double *out_8784059409974897858) {
  H_30(state, unused, out_8784059409974897858);
}
void car_h_26(double *state, double *unused, double *out_1190680859274434345) {
  h_26(state, unused, out_1190680859274434345);
}
void car_H_26(double *state, double *unused, double *out_2524223132593593007) {
  H_26(state, unused, out_2524223132593593007);
}
void car_h_27(double *state, double *unused, double *out_7174002555159601650) {
  h_27(state, unused, out_7174002555159601650);
}
void car_H_27(double *state, double *unused, double *out_7439090592550710541) {
  H_27(state, unused, out_7439090592550710541);
}
void car_h_29(double *state, double *unused, double *out_4501906292199599030) {
  h_29(state, unused, out_4501906292199599030);
}
void car_H_29(double *state, double *unused, double *out_9152453319420261574) {
  H_29(state, unused, out_9152453319420261574);
}
void car_h_28(double *state, double *unused, double *out_5016916796590902712) {
  h_28(state, unused, out_5016916796590902712);
}
void car_H_28(double *state, double *unused, double *out_4211891737219759468) {
  H_28(state, unused, out_4211891737219759468);
}
void car_h_31(double *state, double *unused, double *out_4412410565999774854) {
  h_31(state, unused, out_4412410565999774854);
}
void car_H_31(double *state, double *unused, double *out_6296372413344609659) {
  H_31(state, unused, out_6296372413344609659);
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
