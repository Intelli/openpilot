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
void err_fun(double *nom_x, double *delta_x, double *out_2543343838934147) {
   out_2543343838934147[0] = delta_x[0] + nom_x[0];
   out_2543343838934147[1] = delta_x[1] + nom_x[1];
   out_2543343838934147[2] = delta_x[2] + nom_x[2];
   out_2543343838934147[3] = delta_x[3] + nom_x[3];
   out_2543343838934147[4] = delta_x[4] + nom_x[4];
   out_2543343838934147[5] = delta_x[5] + nom_x[5];
   out_2543343838934147[6] = delta_x[6] + nom_x[6];
   out_2543343838934147[7] = delta_x[7] + nom_x[7];
   out_2543343838934147[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5525400379837697642) {
   out_5525400379837697642[0] = -nom_x[0] + true_x[0];
   out_5525400379837697642[1] = -nom_x[1] + true_x[1];
   out_5525400379837697642[2] = -nom_x[2] + true_x[2];
   out_5525400379837697642[3] = -nom_x[3] + true_x[3];
   out_5525400379837697642[4] = -nom_x[4] + true_x[4];
   out_5525400379837697642[5] = -nom_x[5] + true_x[5];
   out_5525400379837697642[6] = -nom_x[6] + true_x[6];
   out_5525400379837697642[7] = -nom_x[7] + true_x[7];
   out_5525400379837697642[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5947912966739432546) {
   out_5947912966739432546[0] = 1.0;
   out_5947912966739432546[1] = 0.0;
   out_5947912966739432546[2] = 0.0;
   out_5947912966739432546[3] = 0.0;
   out_5947912966739432546[4] = 0.0;
   out_5947912966739432546[5] = 0.0;
   out_5947912966739432546[6] = 0.0;
   out_5947912966739432546[7] = 0.0;
   out_5947912966739432546[8] = 0.0;
   out_5947912966739432546[9] = 0.0;
   out_5947912966739432546[10] = 1.0;
   out_5947912966739432546[11] = 0.0;
   out_5947912966739432546[12] = 0.0;
   out_5947912966739432546[13] = 0.0;
   out_5947912966739432546[14] = 0.0;
   out_5947912966739432546[15] = 0.0;
   out_5947912966739432546[16] = 0.0;
   out_5947912966739432546[17] = 0.0;
   out_5947912966739432546[18] = 0.0;
   out_5947912966739432546[19] = 0.0;
   out_5947912966739432546[20] = 1.0;
   out_5947912966739432546[21] = 0.0;
   out_5947912966739432546[22] = 0.0;
   out_5947912966739432546[23] = 0.0;
   out_5947912966739432546[24] = 0.0;
   out_5947912966739432546[25] = 0.0;
   out_5947912966739432546[26] = 0.0;
   out_5947912966739432546[27] = 0.0;
   out_5947912966739432546[28] = 0.0;
   out_5947912966739432546[29] = 0.0;
   out_5947912966739432546[30] = 1.0;
   out_5947912966739432546[31] = 0.0;
   out_5947912966739432546[32] = 0.0;
   out_5947912966739432546[33] = 0.0;
   out_5947912966739432546[34] = 0.0;
   out_5947912966739432546[35] = 0.0;
   out_5947912966739432546[36] = 0.0;
   out_5947912966739432546[37] = 0.0;
   out_5947912966739432546[38] = 0.0;
   out_5947912966739432546[39] = 0.0;
   out_5947912966739432546[40] = 1.0;
   out_5947912966739432546[41] = 0.0;
   out_5947912966739432546[42] = 0.0;
   out_5947912966739432546[43] = 0.0;
   out_5947912966739432546[44] = 0.0;
   out_5947912966739432546[45] = 0.0;
   out_5947912966739432546[46] = 0.0;
   out_5947912966739432546[47] = 0.0;
   out_5947912966739432546[48] = 0.0;
   out_5947912966739432546[49] = 0.0;
   out_5947912966739432546[50] = 1.0;
   out_5947912966739432546[51] = 0.0;
   out_5947912966739432546[52] = 0.0;
   out_5947912966739432546[53] = 0.0;
   out_5947912966739432546[54] = 0.0;
   out_5947912966739432546[55] = 0.0;
   out_5947912966739432546[56] = 0.0;
   out_5947912966739432546[57] = 0.0;
   out_5947912966739432546[58] = 0.0;
   out_5947912966739432546[59] = 0.0;
   out_5947912966739432546[60] = 1.0;
   out_5947912966739432546[61] = 0.0;
   out_5947912966739432546[62] = 0.0;
   out_5947912966739432546[63] = 0.0;
   out_5947912966739432546[64] = 0.0;
   out_5947912966739432546[65] = 0.0;
   out_5947912966739432546[66] = 0.0;
   out_5947912966739432546[67] = 0.0;
   out_5947912966739432546[68] = 0.0;
   out_5947912966739432546[69] = 0.0;
   out_5947912966739432546[70] = 1.0;
   out_5947912966739432546[71] = 0.0;
   out_5947912966739432546[72] = 0.0;
   out_5947912966739432546[73] = 0.0;
   out_5947912966739432546[74] = 0.0;
   out_5947912966739432546[75] = 0.0;
   out_5947912966739432546[76] = 0.0;
   out_5947912966739432546[77] = 0.0;
   out_5947912966739432546[78] = 0.0;
   out_5947912966739432546[79] = 0.0;
   out_5947912966739432546[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5736328484507014804) {
   out_5736328484507014804[0] = state[0];
   out_5736328484507014804[1] = state[1];
   out_5736328484507014804[2] = state[2];
   out_5736328484507014804[3] = state[3];
   out_5736328484507014804[4] = state[4];
   out_5736328484507014804[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5736328484507014804[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5736328484507014804[7] = state[7];
   out_5736328484507014804[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2989934352022285926) {
   out_2989934352022285926[0] = 1;
   out_2989934352022285926[1] = 0;
   out_2989934352022285926[2] = 0;
   out_2989934352022285926[3] = 0;
   out_2989934352022285926[4] = 0;
   out_2989934352022285926[5] = 0;
   out_2989934352022285926[6] = 0;
   out_2989934352022285926[7] = 0;
   out_2989934352022285926[8] = 0;
   out_2989934352022285926[9] = 0;
   out_2989934352022285926[10] = 1;
   out_2989934352022285926[11] = 0;
   out_2989934352022285926[12] = 0;
   out_2989934352022285926[13] = 0;
   out_2989934352022285926[14] = 0;
   out_2989934352022285926[15] = 0;
   out_2989934352022285926[16] = 0;
   out_2989934352022285926[17] = 0;
   out_2989934352022285926[18] = 0;
   out_2989934352022285926[19] = 0;
   out_2989934352022285926[20] = 1;
   out_2989934352022285926[21] = 0;
   out_2989934352022285926[22] = 0;
   out_2989934352022285926[23] = 0;
   out_2989934352022285926[24] = 0;
   out_2989934352022285926[25] = 0;
   out_2989934352022285926[26] = 0;
   out_2989934352022285926[27] = 0;
   out_2989934352022285926[28] = 0;
   out_2989934352022285926[29] = 0;
   out_2989934352022285926[30] = 1;
   out_2989934352022285926[31] = 0;
   out_2989934352022285926[32] = 0;
   out_2989934352022285926[33] = 0;
   out_2989934352022285926[34] = 0;
   out_2989934352022285926[35] = 0;
   out_2989934352022285926[36] = 0;
   out_2989934352022285926[37] = 0;
   out_2989934352022285926[38] = 0;
   out_2989934352022285926[39] = 0;
   out_2989934352022285926[40] = 1;
   out_2989934352022285926[41] = 0;
   out_2989934352022285926[42] = 0;
   out_2989934352022285926[43] = 0;
   out_2989934352022285926[44] = 0;
   out_2989934352022285926[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2989934352022285926[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2989934352022285926[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2989934352022285926[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2989934352022285926[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2989934352022285926[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2989934352022285926[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2989934352022285926[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2989934352022285926[53] = -9.8100000000000005*dt;
   out_2989934352022285926[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2989934352022285926[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2989934352022285926[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2989934352022285926[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2989934352022285926[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2989934352022285926[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2989934352022285926[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2989934352022285926[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2989934352022285926[62] = 0;
   out_2989934352022285926[63] = 0;
   out_2989934352022285926[64] = 0;
   out_2989934352022285926[65] = 0;
   out_2989934352022285926[66] = 0;
   out_2989934352022285926[67] = 0;
   out_2989934352022285926[68] = 0;
   out_2989934352022285926[69] = 0;
   out_2989934352022285926[70] = 1;
   out_2989934352022285926[71] = 0;
   out_2989934352022285926[72] = 0;
   out_2989934352022285926[73] = 0;
   out_2989934352022285926[74] = 0;
   out_2989934352022285926[75] = 0;
   out_2989934352022285926[76] = 0;
   out_2989934352022285926[77] = 0;
   out_2989934352022285926[78] = 0;
   out_2989934352022285926[79] = 0;
   out_2989934352022285926[80] = 1;
}
void h_25(double *state, double *unused, double *out_4810667785250124972) {
   out_4810667785250124972[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3245275259172804691) {
   out_3245275259172804691[0] = 0;
   out_3245275259172804691[1] = 0;
   out_3245275259172804691[2] = 0;
   out_3245275259172804691[3] = 0;
   out_3245275259172804691[4] = 0;
   out_3245275259172804691[5] = 0;
   out_3245275259172804691[6] = 1;
   out_3245275259172804691[7] = 0;
   out_3245275259172804691[8] = 0;
}
void h_24(double *state, double *unused, double *out_6117394571812982197) {
   out_6117394571812982197[0] = state[4];
   out_6117394571812982197[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5417924858178304257) {
   out_5417924858178304257[0] = 0;
   out_5417924858178304257[1] = 0;
   out_5417924858178304257[2] = 0;
   out_5417924858178304257[3] = 0;
   out_5417924858178304257[4] = 1;
   out_5417924858178304257[5] = 0;
   out_5417924858178304257[6] = 0;
   out_5417924858178304257[7] = 0;
   out_5417924858178304257[8] = 0;
   out_5417924858178304257[9] = 0;
   out_5417924858178304257[10] = 0;
   out_5417924858178304257[11] = 0;
   out_5417924858178304257[12] = 0;
   out_5417924858178304257[13] = 0;
   out_5417924858178304257[14] = 1;
   out_5417924858178304257[15] = 0;
   out_5417924858178304257[16] = 0;
   out_5417924858178304257[17] = 0;
}
void h_30(double *state, double *unused, double *out_4535473722965619083) {
   out_4535473722965619083[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7772971589300412889) {
   out_7772971589300412889[0] = 0;
   out_7772971589300412889[1] = 0;
   out_7772971589300412889[2] = 0;
   out_7772971589300412889[3] = 0;
   out_7772971589300412889[4] = 1;
   out_7772971589300412889[5] = 0;
   out_7772971589300412889[6] = 0;
   out_7772971589300412889[7] = 0;
   out_7772971589300412889[8] = 0;
}
void h_26(double *state, double *unused, double *out_1931068402156921432) {
   out_1931068402156921432[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6986778578046860915) {
   out_6986778578046860915[0] = 0;
   out_6986778578046860915[1] = 0;
   out_6986778578046860915[2] = 0;
   out_6986778578046860915[3] = 0;
   out_6986778578046860915[4] = 0;
   out_6986778578046860915[5] = 0;
   out_6986778578046860915[6] = 0;
   out_6986778578046860915[7] = 1;
   out_6986778578046860915[8] = 0;
}
void h_27(double *state, double *unused, double *out_3330739680675778012) {
   out_3330739680675778012[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5549377518116469672) {
   out_5549377518116469672[0] = 0;
   out_5549377518116469672[1] = 0;
   out_5549377518116469672[2] = 0;
   out_5549377518116469672[3] = 1;
   out_5549377518116469672[4] = 0;
   out_5549377518116469672[5] = 0;
   out_5549377518116469672[6] = 0;
   out_5549377518116469672[7] = 0;
   out_5549377518116469672[8] = 0;
}
void h_29(double *state, double *unused, double *out_530943795752723640) {
   out_530943795752723640[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7262740244986020705) {
   out_7262740244986020705[0] = 0;
   out_7262740244986020705[1] = 1;
   out_7262740244986020705[2] = 0;
   out_7262740244986020705[3] = 0;
   out_7262740244986020705[4] = 0;
   out_7262740244986020705[5] = 0;
   out_7262740244986020705[6] = 0;
   out_7262740244986020705[7] = 0;
   out_7262740244986020705[8] = 0;
}
void h_28(double *state, double *unused, double *out_5150861753475309890) {
   out_5150861753475309890[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5299109973420694454) {
   out_5299109973420694454[0] = 1;
   out_5299109973420694454[1] = 0;
   out_5299109973420694454[2] = 0;
   out_5299109973420694454[3] = 0;
   out_5299109973420694454[4] = 0;
   out_5299109973420694454[5] = 0;
   out_5299109973420694454[6] = 0;
   out_5299109973420694454[7] = 0;
   out_5299109973420694454[8] = 0;
}
void h_31(double *state, double *unused, double *out_3829209691468416912) {
   out_3829209691468416912[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3214629297295844263) {
   out_3214629297295844263[0] = 0;
   out_3214629297295844263[1] = 0;
   out_3214629297295844263[2] = 0;
   out_3214629297295844263[3] = 0;
   out_3214629297295844263[4] = 0;
   out_3214629297295844263[5] = 0;
   out_3214629297295844263[6] = 0;
   out_3214629297295844263[7] = 0;
   out_3214629297295844263[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2543343838934147) {
  err_fun(nom_x, delta_x, out_2543343838934147);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5525400379837697642) {
  inv_err_fun(nom_x, true_x, out_5525400379837697642);
}
void car_H_mod_fun(double *state, double *out_5947912966739432546) {
  H_mod_fun(state, out_5947912966739432546);
}
void car_f_fun(double *state, double dt, double *out_5736328484507014804) {
  f_fun(state,  dt, out_5736328484507014804);
}
void car_F_fun(double *state, double dt, double *out_2989934352022285926) {
  F_fun(state,  dt, out_2989934352022285926);
}
void car_h_25(double *state, double *unused, double *out_4810667785250124972) {
  h_25(state, unused, out_4810667785250124972);
}
void car_H_25(double *state, double *unused, double *out_3245275259172804691) {
  H_25(state, unused, out_3245275259172804691);
}
void car_h_24(double *state, double *unused, double *out_6117394571812982197) {
  h_24(state, unused, out_6117394571812982197);
}
void car_H_24(double *state, double *unused, double *out_5417924858178304257) {
  H_24(state, unused, out_5417924858178304257);
}
void car_h_30(double *state, double *unused, double *out_4535473722965619083) {
  h_30(state, unused, out_4535473722965619083);
}
void car_H_30(double *state, double *unused, double *out_7772971589300412889) {
  H_30(state, unused, out_7772971589300412889);
}
void car_h_26(double *state, double *unused, double *out_1931068402156921432) {
  h_26(state, unused, out_1931068402156921432);
}
void car_H_26(double *state, double *unused, double *out_6986778578046860915) {
  H_26(state, unused, out_6986778578046860915);
}
void car_h_27(double *state, double *unused, double *out_3330739680675778012) {
  h_27(state, unused, out_3330739680675778012);
}
void car_H_27(double *state, double *unused, double *out_5549377518116469672) {
  H_27(state, unused, out_5549377518116469672);
}
void car_h_29(double *state, double *unused, double *out_530943795752723640) {
  h_29(state, unused, out_530943795752723640);
}
void car_H_29(double *state, double *unused, double *out_7262740244986020705) {
  H_29(state, unused, out_7262740244986020705);
}
void car_h_28(double *state, double *unused, double *out_5150861753475309890) {
  h_28(state, unused, out_5150861753475309890);
}
void car_H_28(double *state, double *unused, double *out_5299109973420694454) {
  H_28(state, unused, out_5299109973420694454);
}
void car_h_31(double *state, double *unused, double *out_3829209691468416912) {
  h_31(state, unused, out_3829209691468416912);
}
void car_H_31(double *state, double *unused, double *out_3214629297295844263) {
  H_31(state, unused, out_3214629297295844263);
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
