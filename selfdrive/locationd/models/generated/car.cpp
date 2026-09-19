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
void err_fun(double *nom_x, double *delta_x, double *out_7352776745859294438) {
   out_7352776745859294438[0] = delta_x[0] + nom_x[0];
   out_7352776745859294438[1] = delta_x[1] + nom_x[1];
   out_7352776745859294438[2] = delta_x[2] + nom_x[2];
   out_7352776745859294438[3] = delta_x[3] + nom_x[3];
   out_7352776745859294438[4] = delta_x[4] + nom_x[4];
   out_7352776745859294438[5] = delta_x[5] + nom_x[5];
   out_7352776745859294438[6] = delta_x[6] + nom_x[6];
   out_7352776745859294438[7] = delta_x[7] + nom_x[7];
   out_7352776745859294438[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2797254755301616602) {
   out_2797254755301616602[0] = -nom_x[0] + true_x[0];
   out_2797254755301616602[1] = -nom_x[1] + true_x[1];
   out_2797254755301616602[2] = -nom_x[2] + true_x[2];
   out_2797254755301616602[3] = -nom_x[3] + true_x[3];
   out_2797254755301616602[4] = -nom_x[4] + true_x[4];
   out_2797254755301616602[5] = -nom_x[5] + true_x[5];
   out_2797254755301616602[6] = -nom_x[6] + true_x[6];
   out_2797254755301616602[7] = -nom_x[7] + true_x[7];
   out_2797254755301616602[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5490718872353398943) {
   out_5490718872353398943[0] = 1.0;
   out_5490718872353398943[1] = 0.0;
   out_5490718872353398943[2] = 0.0;
   out_5490718872353398943[3] = 0.0;
   out_5490718872353398943[4] = 0.0;
   out_5490718872353398943[5] = 0.0;
   out_5490718872353398943[6] = 0.0;
   out_5490718872353398943[7] = 0.0;
   out_5490718872353398943[8] = 0.0;
   out_5490718872353398943[9] = 0.0;
   out_5490718872353398943[10] = 1.0;
   out_5490718872353398943[11] = 0.0;
   out_5490718872353398943[12] = 0.0;
   out_5490718872353398943[13] = 0.0;
   out_5490718872353398943[14] = 0.0;
   out_5490718872353398943[15] = 0.0;
   out_5490718872353398943[16] = 0.0;
   out_5490718872353398943[17] = 0.0;
   out_5490718872353398943[18] = 0.0;
   out_5490718872353398943[19] = 0.0;
   out_5490718872353398943[20] = 1.0;
   out_5490718872353398943[21] = 0.0;
   out_5490718872353398943[22] = 0.0;
   out_5490718872353398943[23] = 0.0;
   out_5490718872353398943[24] = 0.0;
   out_5490718872353398943[25] = 0.0;
   out_5490718872353398943[26] = 0.0;
   out_5490718872353398943[27] = 0.0;
   out_5490718872353398943[28] = 0.0;
   out_5490718872353398943[29] = 0.0;
   out_5490718872353398943[30] = 1.0;
   out_5490718872353398943[31] = 0.0;
   out_5490718872353398943[32] = 0.0;
   out_5490718872353398943[33] = 0.0;
   out_5490718872353398943[34] = 0.0;
   out_5490718872353398943[35] = 0.0;
   out_5490718872353398943[36] = 0.0;
   out_5490718872353398943[37] = 0.0;
   out_5490718872353398943[38] = 0.0;
   out_5490718872353398943[39] = 0.0;
   out_5490718872353398943[40] = 1.0;
   out_5490718872353398943[41] = 0.0;
   out_5490718872353398943[42] = 0.0;
   out_5490718872353398943[43] = 0.0;
   out_5490718872353398943[44] = 0.0;
   out_5490718872353398943[45] = 0.0;
   out_5490718872353398943[46] = 0.0;
   out_5490718872353398943[47] = 0.0;
   out_5490718872353398943[48] = 0.0;
   out_5490718872353398943[49] = 0.0;
   out_5490718872353398943[50] = 1.0;
   out_5490718872353398943[51] = 0.0;
   out_5490718872353398943[52] = 0.0;
   out_5490718872353398943[53] = 0.0;
   out_5490718872353398943[54] = 0.0;
   out_5490718872353398943[55] = 0.0;
   out_5490718872353398943[56] = 0.0;
   out_5490718872353398943[57] = 0.0;
   out_5490718872353398943[58] = 0.0;
   out_5490718872353398943[59] = 0.0;
   out_5490718872353398943[60] = 1.0;
   out_5490718872353398943[61] = 0.0;
   out_5490718872353398943[62] = 0.0;
   out_5490718872353398943[63] = 0.0;
   out_5490718872353398943[64] = 0.0;
   out_5490718872353398943[65] = 0.0;
   out_5490718872353398943[66] = 0.0;
   out_5490718872353398943[67] = 0.0;
   out_5490718872353398943[68] = 0.0;
   out_5490718872353398943[69] = 0.0;
   out_5490718872353398943[70] = 1.0;
   out_5490718872353398943[71] = 0.0;
   out_5490718872353398943[72] = 0.0;
   out_5490718872353398943[73] = 0.0;
   out_5490718872353398943[74] = 0.0;
   out_5490718872353398943[75] = 0.0;
   out_5490718872353398943[76] = 0.0;
   out_5490718872353398943[77] = 0.0;
   out_5490718872353398943[78] = 0.0;
   out_5490718872353398943[79] = 0.0;
   out_5490718872353398943[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2803517744059257752) {
   out_2803517744059257752[0] = state[0];
   out_2803517744059257752[1] = state[1];
   out_2803517744059257752[2] = state[2];
   out_2803517744059257752[3] = state[3];
   out_2803517744059257752[4] = state[4];
   out_2803517744059257752[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2803517744059257752[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2803517744059257752[7] = state[7];
   out_2803517744059257752[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1627923674770080030) {
   out_1627923674770080030[0] = 1;
   out_1627923674770080030[1] = 0;
   out_1627923674770080030[2] = 0;
   out_1627923674770080030[3] = 0;
   out_1627923674770080030[4] = 0;
   out_1627923674770080030[5] = 0;
   out_1627923674770080030[6] = 0;
   out_1627923674770080030[7] = 0;
   out_1627923674770080030[8] = 0;
   out_1627923674770080030[9] = 0;
   out_1627923674770080030[10] = 1;
   out_1627923674770080030[11] = 0;
   out_1627923674770080030[12] = 0;
   out_1627923674770080030[13] = 0;
   out_1627923674770080030[14] = 0;
   out_1627923674770080030[15] = 0;
   out_1627923674770080030[16] = 0;
   out_1627923674770080030[17] = 0;
   out_1627923674770080030[18] = 0;
   out_1627923674770080030[19] = 0;
   out_1627923674770080030[20] = 1;
   out_1627923674770080030[21] = 0;
   out_1627923674770080030[22] = 0;
   out_1627923674770080030[23] = 0;
   out_1627923674770080030[24] = 0;
   out_1627923674770080030[25] = 0;
   out_1627923674770080030[26] = 0;
   out_1627923674770080030[27] = 0;
   out_1627923674770080030[28] = 0;
   out_1627923674770080030[29] = 0;
   out_1627923674770080030[30] = 1;
   out_1627923674770080030[31] = 0;
   out_1627923674770080030[32] = 0;
   out_1627923674770080030[33] = 0;
   out_1627923674770080030[34] = 0;
   out_1627923674770080030[35] = 0;
   out_1627923674770080030[36] = 0;
   out_1627923674770080030[37] = 0;
   out_1627923674770080030[38] = 0;
   out_1627923674770080030[39] = 0;
   out_1627923674770080030[40] = 1;
   out_1627923674770080030[41] = 0;
   out_1627923674770080030[42] = 0;
   out_1627923674770080030[43] = 0;
   out_1627923674770080030[44] = 0;
   out_1627923674770080030[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1627923674770080030[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1627923674770080030[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1627923674770080030[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1627923674770080030[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1627923674770080030[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1627923674770080030[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1627923674770080030[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1627923674770080030[53] = -9.8100000000000005*dt;
   out_1627923674770080030[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1627923674770080030[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1627923674770080030[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1627923674770080030[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1627923674770080030[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1627923674770080030[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1627923674770080030[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1627923674770080030[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1627923674770080030[62] = 0;
   out_1627923674770080030[63] = 0;
   out_1627923674770080030[64] = 0;
   out_1627923674770080030[65] = 0;
   out_1627923674770080030[66] = 0;
   out_1627923674770080030[67] = 0;
   out_1627923674770080030[68] = 0;
   out_1627923674770080030[69] = 0;
   out_1627923674770080030[70] = 1;
   out_1627923674770080030[71] = 0;
   out_1627923674770080030[72] = 0;
   out_1627923674770080030[73] = 0;
   out_1627923674770080030[74] = 0;
   out_1627923674770080030[75] = 0;
   out_1627923674770080030[76] = 0;
   out_1627923674770080030[77] = 0;
   out_1627923674770080030[78] = 0;
   out_1627923674770080030[79] = 0;
   out_1627923674770080030[80] = 1;
}
void h_25(double *state, double *unused, double *out_7271936812348157431) {
   out_7271936812348157431[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4615410128014395963) {
   out_4615410128014395963[0] = 0;
   out_4615410128014395963[1] = 0;
   out_4615410128014395963[2] = 0;
   out_4615410128014395963[3] = 0;
   out_4615410128014395963[4] = 0;
   out_4615410128014395963[5] = 0;
   out_4615410128014395963[6] = 1;
   out_4615410128014395963[7] = 0;
   out_4615410128014395963[8] = 0;
}
void h_24(double *state, double *unused, double *out_1124221862302097569) {
   out_1124221862302097569[0] = state[4];
   out_1124221862302097569[1] = state[5];
}
void H_24(double *state, double *unused, double *out_9084824618728646619) {
   out_9084824618728646619[0] = 0;
   out_9084824618728646619[1] = 0;
   out_9084824618728646619[2] = 0;
   out_9084824618728646619[3] = 0;
   out_9084824618728646619[4] = 1;
   out_9084824618728646619[5] = 0;
   out_9084824618728646619[6] = 0;
   out_9084824618728646619[7] = 0;
   out_9084824618728646619[8] = 0;
   out_9084824618728646619[9] = 0;
   out_9084824618728646619[10] = 0;
   out_9084824618728646619[11] = 0;
   out_9084824618728646619[12] = 0;
   out_9084824618728646619[13] = 0;
   out_9084824618728646619[14] = 1;
   out_9084824618728646619[15] = 0;
   out_9084824618728646619[16] = 0;
   out_9084824618728646619[17] = 0;
}
void h_30(double *state, double *unused, double *out_8722568204977040598) {
   out_8722568204977040598[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2097077169507147336) {
   out_2097077169507147336[0] = 0;
   out_2097077169507147336[1] = 0;
   out_2097077169507147336[2] = 0;
   out_2097077169507147336[3] = 0;
   out_2097077169507147336[4] = 1;
   out_2097077169507147336[5] = 0;
   out_2097077169507147336[6] = 0;
   out_2097077169507147336[7] = 0;
   out_2097077169507147336[8] = 0;
}
void h_26(double *state, double *unused, double *out_5685782153532707913) {
   out_5685782153532707913[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8356913446888452187) {
   out_8356913446888452187[0] = 0;
   out_8356913446888452187[1] = 0;
   out_8356913446888452187[2] = 0;
   out_8356913446888452187[3] = 0;
   out_8356913446888452187[4] = 0;
   out_8356913446888452187[5] = 0;
   out_8356913446888452187[6] = 0;
   out_8356913446888452187[7] = 1;
   out_8356913446888452187[8] = 0;
}
void h_27(double *state, double *unused, double *out_5832940025475363622) {
   out_5832940025475363622[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4271840481307572247) {
   out_4271840481307572247[0] = 0;
   out_4271840481307572247[1] = 0;
   out_4271840481307572247[2] = 0;
   out_4271840481307572247[3] = 1;
   out_4271840481307572247[4] = 0;
   out_4271840481307572247[5] = 0;
   out_4271840481307572247[6] = 0;
   out_4271840481307572247[7] = 0;
   out_4271840481307572247[8] = 0;
}
void h_29(double *state, double *unused, double *out_3720894937316194953) {
   out_3720894937316194953[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1586845825192755152) {
   out_1586845825192755152[0] = 0;
   out_1586845825192755152[1] = 1;
   out_1586845825192755152[2] = 0;
   out_1586845825192755152[3] = 0;
   out_1586845825192755152[4] = 0;
   out_1586845825192755152[5] = 0;
   out_1586845825192755152[6] = 0;
   out_1586845825192755152[7] = 0;
   out_1586845825192755152[8] = 0;
}
void h_28(double *state, double *unused, double *out_2796153974031030937) {
   out_2796153974031030937[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6669244842262285726) {
   out_6669244842262285726[0] = 1;
   out_6669244842262285726[1] = 0;
   out_6669244842262285726[2] = 0;
   out_6669244842262285726[3] = 0;
   out_6669244842262285726[4] = 0;
   out_6669244842262285726[5] = 0;
   out_6669244842262285726[6] = 0;
   out_6669244842262285726[7] = 0;
   out_6669244842262285726[8] = 0;
}
void h_31(double *state, double *unused, double *out_7114750143997028286) {
   out_7114750143997028286[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8983121549121803663) {
   out_8983121549121803663[0] = 0;
   out_8983121549121803663[1] = 0;
   out_8983121549121803663[2] = 0;
   out_8983121549121803663[3] = 0;
   out_8983121549121803663[4] = 0;
   out_8983121549121803663[5] = 0;
   out_8983121549121803663[6] = 0;
   out_8983121549121803663[7] = 0;
   out_8983121549121803663[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7352776745859294438) {
  err_fun(nom_x, delta_x, out_7352776745859294438);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2797254755301616602) {
  inv_err_fun(nom_x, true_x, out_2797254755301616602);
}
void car_H_mod_fun(double *state, double *out_5490718872353398943) {
  H_mod_fun(state, out_5490718872353398943);
}
void car_f_fun(double *state, double dt, double *out_2803517744059257752) {
  f_fun(state,  dt, out_2803517744059257752);
}
void car_F_fun(double *state, double dt, double *out_1627923674770080030) {
  F_fun(state,  dt, out_1627923674770080030);
}
void car_h_25(double *state, double *unused, double *out_7271936812348157431) {
  h_25(state, unused, out_7271936812348157431);
}
void car_H_25(double *state, double *unused, double *out_4615410128014395963) {
  H_25(state, unused, out_4615410128014395963);
}
void car_h_24(double *state, double *unused, double *out_1124221862302097569) {
  h_24(state, unused, out_1124221862302097569);
}
void car_H_24(double *state, double *unused, double *out_9084824618728646619) {
  H_24(state, unused, out_9084824618728646619);
}
void car_h_30(double *state, double *unused, double *out_8722568204977040598) {
  h_30(state, unused, out_8722568204977040598);
}
void car_H_30(double *state, double *unused, double *out_2097077169507147336) {
  H_30(state, unused, out_2097077169507147336);
}
void car_h_26(double *state, double *unused, double *out_5685782153532707913) {
  h_26(state, unused, out_5685782153532707913);
}
void car_H_26(double *state, double *unused, double *out_8356913446888452187) {
  H_26(state, unused, out_8356913446888452187);
}
void car_h_27(double *state, double *unused, double *out_5832940025475363622) {
  h_27(state, unused, out_5832940025475363622);
}
void car_H_27(double *state, double *unused, double *out_4271840481307572247) {
  H_27(state, unused, out_4271840481307572247);
}
void car_h_29(double *state, double *unused, double *out_3720894937316194953) {
  h_29(state, unused, out_3720894937316194953);
}
void car_H_29(double *state, double *unused, double *out_1586845825192755152) {
  H_29(state, unused, out_1586845825192755152);
}
void car_h_28(double *state, double *unused, double *out_2796153974031030937) {
  h_28(state, unused, out_2796153974031030937);
}
void car_H_28(double *state, double *unused, double *out_6669244842262285726) {
  H_28(state, unused, out_6669244842262285726);
}
void car_h_31(double *state, double *unused, double *out_7114750143997028286) {
  h_31(state, unused, out_7114750143997028286);
}
void car_H_31(double *state, double *unused, double *out_8983121549121803663) {
  H_31(state, unused, out_8983121549121803663);
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
