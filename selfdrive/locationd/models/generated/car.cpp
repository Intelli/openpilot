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
void err_fun(double *nom_x, double *delta_x, double *out_2989898474462123217) {
   out_2989898474462123217[0] = delta_x[0] + nom_x[0];
   out_2989898474462123217[1] = delta_x[1] + nom_x[1];
   out_2989898474462123217[2] = delta_x[2] + nom_x[2];
   out_2989898474462123217[3] = delta_x[3] + nom_x[3];
   out_2989898474462123217[4] = delta_x[4] + nom_x[4];
   out_2989898474462123217[5] = delta_x[5] + nom_x[5];
   out_2989898474462123217[6] = delta_x[6] + nom_x[6];
   out_2989898474462123217[7] = delta_x[7] + nom_x[7];
   out_2989898474462123217[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7725514447092014153) {
   out_7725514447092014153[0] = -nom_x[0] + true_x[0];
   out_7725514447092014153[1] = -nom_x[1] + true_x[1];
   out_7725514447092014153[2] = -nom_x[2] + true_x[2];
   out_7725514447092014153[3] = -nom_x[3] + true_x[3];
   out_7725514447092014153[4] = -nom_x[4] + true_x[4];
   out_7725514447092014153[5] = -nom_x[5] + true_x[5];
   out_7725514447092014153[6] = -nom_x[6] + true_x[6];
   out_7725514447092014153[7] = -nom_x[7] + true_x[7];
   out_7725514447092014153[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_779695979657555196) {
   out_779695979657555196[0] = 1.0;
   out_779695979657555196[1] = 0.0;
   out_779695979657555196[2] = 0.0;
   out_779695979657555196[3] = 0.0;
   out_779695979657555196[4] = 0.0;
   out_779695979657555196[5] = 0.0;
   out_779695979657555196[6] = 0.0;
   out_779695979657555196[7] = 0.0;
   out_779695979657555196[8] = 0.0;
   out_779695979657555196[9] = 0.0;
   out_779695979657555196[10] = 1.0;
   out_779695979657555196[11] = 0.0;
   out_779695979657555196[12] = 0.0;
   out_779695979657555196[13] = 0.0;
   out_779695979657555196[14] = 0.0;
   out_779695979657555196[15] = 0.0;
   out_779695979657555196[16] = 0.0;
   out_779695979657555196[17] = 0.0;
   out_779695979657555196[18] = 0.0;
   out_779695979657555196[19] = 0.0;
   out_779695979657555196[20] = 1.0;
   out_779695979657555196[21] = 0.0;
   out_779695979657555196[22] = 0.0;
   out_779695979657555196[23] = 0.0;
   out_779695979657555196[24] = 0.0;
   out_779695979657555196[25] = 0.0;
   out_779695979657555196[26] = 0.0;
   out_779695979657555196[27] = 0.0;
   out_779695979657555196[28] = 0.0;
   out_779695979657555196[29] = 0.0;
   out_779695979657555196[30] = 1.0;
   out_779695979657555196[31] = 0.0;
   out_779695979657555196[32] = 0.0;
   out_779695979657555196[33] = 0.0;
   out_779695979657555196[34] = 0.0;
   out_779695979657555196[35] = 0.0;
   out_779695979657555196[36] = 0.0;
   out_779695979657555196[37] = 0.0;
   out_779695979657555196[38] = 0.0;
   out_779695979657555196[39] = 0.0;
   out_779695979657555196[40] = 1.0;
   out_779695979657555196[41] = 0.0;
   out_779695979657555196[42] = 0.0;
   out_779695979657555196[43] = 0.0;
   out_779695979657555196[44] = 0.0;
   out_779695979657555196[45] = 0.0;
   out_779695979657555196[46] = 0.0;
   out_779695979657555196[47] = 0.0;
   out_779695979657555196[48] = 0.0;
   out_779695979657555196[49] = 0.0;
   out_779695979657555196[50] = 1.0;
   out_779695979657555196[51] = 0.0;
   out_779695979657555196[52] = 0.0;
   out_779695979657555196[53] = 0.0;
   out_779695979657555196[54] = 0.0;
   out_779695979657555196[55] = 0.0;
   out_779695979657555196[56] = 0.0;
   out_779695979657555196[57] = 0.0;
   out_779695979657555196[58] = 0.0;
   out_779695979657555196[59] = 0.0;
   out_779695979657555196[60] = 1.0;
   out_779695979657555196[61] = 0.0;
   out_779695979657555196[62] = 0.0;
   out_779695979657555196[63] = 0.0;
   out_779695979657555196[64] = 0.0;
   out_779695979657555196[65] = 0.0;
   out_779695979657555196[66] = 0.0;
   out_779695979657555196[67] = 0.0;
   out_779695979657555196[68] = 0.0;
   out_779695979657555196[69] = 0.0;
   out_779695979657555196[70] = 1.0;
   out_779695979657555196[71] = 0.0;
   out_779695979657555196[72] = 0.0;
   out_779695979657555196[73] = 0.0;
   out_779695979657555196[74] = 0.0;
   out_779695979657555196[75] = 0.0;
   out_779695979657555196[76] = 0.0;
   out_779695979657555196[77] = 0.0;
   out_779695979657555196[78] = 0.0;
   out_779695979657555196[79] = 0.0;
   out_779695979657555196[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3948637387392336290) {
   out_3948637387392336290[0] = state[0];
   out_3948637387392336290[1] = state[1];
   out_3948637387392336290[2] = state[2];
   out_3948637387392336290[3] = state[3];
   out_3948637387392336290[4] = state[4];
   out_3948637387392336290[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3948637387392336290[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3948637387392336290[7] = state[7];
   out_3948637387392336290[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6167405682750118523) {
   out_6167405682750118523[0] = 1;
   out_6167405682750118523[1] = 0;
   out_6167405682750118523[2] = 0;
   out_6167405682750118523[3] = 0;
   out_6167405682750118523[4] = 0;
   out_6167405682750118523[5] = 0;
   out_6167405682750118523[6] = 0;
   out_6167405682750118523[7] = 0;
   out_6167405682750118523[8] = 0;
   out_6167405682750118523[9] = 0;
   out_6167405682750118523[10] = 1;
   out_6167405682750118523[11] = 0;
   out_6167405682750118523[12] = 0;
   out_6167405682750118523[13] = 0;
   out_6167405682750118523[14] = 0;
   out_6167405682750118523[15] = 0;
   out_6167405682750118523[16] = 0;
   out_6167405682750118523[17] = 0;
   out_6167405682750118523[18] = 0;
   out_6167405682750118523[19] = 0;
   out_6167405682750118523[20] = 1;
   out_6167405682750118523[21] = 0;
   out_6167405682750118523[22] = 0;
   out_6167405682750118523[23] = 0;
   out_6167405682750118523[24] = 0;
   out_6167405682750118523[25] = 0;
   out_6167405682750118523[26] = 0;
   out_6167405682750118523[27] = 0;
   out_6167405682750118523[28] = 0;
   out_6167405682750118523[29] = 0;
   out_6167405682750118523[30] = 1;
   out_6167405682750118523[31] = 0;
   out_6167405682750118523[32] = 0;
   out_6167405682750118523[33] = 0;
   out_6167405682750118523[34] = 0;
   out_6167405682750118523[35] = 0;
   out_6167405682750118523[36] = 0;
   out_6167405682750118523[37] = 0;
   out_6167405682750118523[38] = 0;
   out_6167405682750118523[39] = 0;
   out_6167405682750118523[40] = 1;
   out_6167405682750118523[41] = 0;
   out_6167405682750118523[42] = 0;
   out_6167405682750118523[43] = 0;
   out_6167405682750118523[44] = 0;
   out_6167405682750118523[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6167405682750118523[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6167405682750118523[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6167405682750118523[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6167405682750118523[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6167405682750118523[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6167405682750118523[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6167405682750118523[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6167405682750118523[53] = -9.8100000000000005*dt;
   out_6167405682750118523[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6167405682750118523[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6167405682750118523[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6167405682750118523[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6167405682750118523[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6167405682750118523[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6167405682750118523[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6167405682750118523[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6167405682750118523[62] = 0;
   out_6167405682750118523[63] = 0;
   out_6167405682750118523[64] = 0;
   out_6167405682750118523[65] = 0;
   out_6167405682750118523[66] = 0;
   out_6167405682750118523[67] = 0;
   out_6167405682750118523[68] = 0;
   out_6167405682750118523[69] = 0;
   out_6167405682750118523[70] = 1;
   out_6167405682750118523[71] = 0;
   out_6167405682750118523[72] = 0;
   out_6167405682750118523[73] = 0;
   out_6167405682750118523[74] = 0;
   out_6167405682750118523[75] = 0;
   out_6167405682750118523[76] = 0;
   out_6167405682750118523[77] = 0;
   out_6167405682750118523[78] = 0;
   out_6167405682750118523[79] = 0;
   out_6167405682750118523[80] = 1;
}
void h_25(double *state, double *unused, double *out_2762237331341649667) {
   out_2762237331341649667[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7015605619665674610) {
   out_7015605619665674610[0] = 0;
   out_7015605619665674610[1] = 0;
   out_7015605619665674610[2] = 0;
   out_7015605619665674610[3] = 0;
   out_7015605619665674610[4] = 0;
   out_7015605619665674610[5] = 0;
   out_7015605619665674610[6] = 1;
   out_7015605619665674610[7] = 0;
   out_7015605619665674610[8] = 0;
}
void h_24(double *state, double *unused, double *out_1423861544418694677) {
   out_1423861544418694677[0] = state[4];
   out_1423861544418694677[1] = state[5];
}
void H_24(double *state, double *unused, double *out_814572939814513184) {
   out_814572939814513184[0] = 0;
   out_814572939814513184[1] = 0;
   out_814572939814513184[2] = 0;
   out_814572939814513184[3] = 0;
   out_814572939814513184[4] = 1;
   out_814572939814513184[5] = 0;
   out_814572939814513184[6] = 0;
   out_814572939814513184[7] = 0;
   out_814572939814513184[8] = 0;
   out_814572939814513184[9] = 0;
   out_814572939814513184[10] = 0;
   out_814572939814513184[11] = 0;
   out_814572939814513184[12] = 0;
   out_814572939814513184[13] = 0;
   out_814572939814513184[14] = 1;
   out_814572939814513184[15] = 0;
   out_814572939814513184[16] = 0;
   out_814572939814513184[17] = 0;
}
void h_30(double *state, double *unused, double *out_3393209864499010462) {
   out_3393209864499010462[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4514448112552260251) {
   out_4514448112552260251[0] = 0;
   out_4514448112552260251[1] = 0;
   out_4514448112552260251[2] = 0;
   out_4514448112552260251[3] = 0;
   out_4514448112552260251[4] = 1;
   out_4514448112552260251[5] = 0;
   out_4514448112552260251[6] = 0;
   out_4514448112552260251[7] = 0;
   out_4514448112552260251[8] = 0;
}
void h_26(double *state, double *unused, double *out_8735077100385041025) {
   out_8735077100385041025[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3274102300791618386) {
   out_3274102300791618386[0] = 0;
   out_3274102300791618386[1] = 0;
   out_3274102300791618386[2] = 0;
   out_3274102300791618386[3] = 0;
   out_3274102300791618386[4] = 0;
   out_3274102300791618386[5] = 0;
   out_3274102300791618386[6] = 0;
   out_3274102300791618386[7] = 1;
   out_3274102300791618386[8] = 0;
}
void h_27(double *state, double *unused, double *out_513610481405806922) {
   out_513610481405806922[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4711503360722009629) {
   out_4711503360722009629[0] = 0;
   out_4711503360722009629[1] = 0;
   out_4711503360722009629[2] = 0;
   out_4711503360722009629[3] = 1;
   out_4711503360722009629[4] = 0;
   out_4711503360722009629[5] = 0;
   out_4711503360722009629[6] = 0;
   out_4711503360722009629[7] = 0;
   out_4711503360722009629[8] = 0;
}
void h_29(double *state, double *unused, double *out_8394883132159856107) {
   out_8394883132159856107[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7396498016836826724) {
   out_7396498016836826724[0] = 0;
   out_7396498016836826724[1] = 1;
   out_7396498016836826724[2] = 0;
   out_7396498016836826724[3] = 0;
   out_7396498016836826724[4] = 0;
   out_7396498016836826724[5] = 0;
   out_7396498016836826724[6] = 0;
   out_7396498016836826724[7] = 0;
   out_7396498016836826724[8] = 0;
}
void h_28(double *state, double *unused, double *out_5515283749066652567) {
   out_5515283749066652567[0] = state[0];
}
void H_28(double *state, double *unused, double *out_9086615785307398641) {
   out_9086615785307398641[0] = 1;
   out_9086615785307398641[1] = 0;
   out_9086615785307398641[2] = 0;
   out_9086615785307398641[3] = 0;
   out_9086615785307398641[4] = 0;
   out_9086615785307398641[5] = 0;
   out_9086615785307398641[6] = 0;
   out_9086615785307398641[7] = 0;
   out_9086615785307398641[8] = 0;
}
void h_31(double *state, double *unused, double *out_3037431393626155556) {
   out_3037431393626155556[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7046251581542635038) {
   out_7046251581542635038[0] = 0;
   out_7046251581542635038[1] = 0;
   out_7046251581542635038[2] = 0;
   out_7046251581542635038[3] = 0;
   out_7046251581542635038[4] = 0;
   out_7046251581542635038[5] = 0;
   out_7046251581542635038[6] = 0;
   out_7046251581542635038[7] = 0;
   out_7046251581542635038[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2989898474462123217) {
  err_fun(nom_x, delta_x, out_2989898474462123217);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7725514447092014153) {
  inv_err_fun(nom_x, true_x, out_7725514447092014153);
}
void car_H_mod_fun(double *state, double *out_779695979657555196) {
  H_mod_fun(state, out_779695979657555196);
}
void car_f_fun(double *state, double dt, double *out_3948637387392336290) {
  f_fun(state,  dt, out_3948637387392336290);
}
void car_F_fun(double *state, double dt, double *out_6167405682750118523) {
  F_fun(state,  dt, out_6167405682750118523);
}
void car_h_25(double *state, double *unused, double *out_2762237331341649667) {
  h_25(state, unused, out_2762237331341649667);
}
void car_H_25(double *state, double *unused, double *out_7015605619665674610) {
  H_25(state, unused, out_7015605619665674610);
}
void car_h_24(double *state, double *unused, double *out_1423861544418694677) {
  h_24(state, unused, out_1423861544418694677);
}
void car_H_24(double *state, double *unused, double *out_814572939814513184) {
  H_24(state, unused, out_814572939814513184);
}
void car_h_30(double *state, double *unused, double *out_3393209864499010462) {
  h_30(state, unused, out_3393209864499010462);
}
void car_H_30(double *state, double *unused, double *out_4514448112552260251) {
  H_30(state, unused, out_4514448112552260251);
}
void car_h_26(double *state, double *unused, double *out_8735077100385041025) {
  h_26(state, unused, out_8735077100385041025);
}
void car_H_26(double *state, double *unused, double *out_3274102300791618386) {
  H_26(state, unused, out_3274102300791618386);
}
void car_h_27(double *state, double *unused, double *out_513610481405806922) {
  h_27(state, unused, out_513610481405806922);
}
void car_H_27(double *state, double *unused, double *out_4711503360722009629) {
  H_27(state, unused, out_4711503360722009629);
}
void car_h_29(double *state, double *unused, double *out_8394883132159856107) {
  h_29(state, unused, out_8394883132159856107);
}
void car_H_29(double *state, double *unused, double *out_7396498016836826724) {
  H_29(state, unused, out_7396498016836826724);
}
void car_h_28(double *state, double *unused, double *out_5515283749066652567) {
  h_28(state, unused, out_5515283749066652567);
}
void car_H_28(double *state, double *unused, double *out_9086615785307398641) {
  H_28(state, unused, out_9086615785307398641);
}
void car_h_31(double *state, double *unused, double *out_3037431393626155556) {
  h_31(state, unused, out_3037431393626155556);
}
void car_H_31(double *state, double *unused, double *out_7046251581542635038) {
  H_31(state, unused, out_7046251581542635038);
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
