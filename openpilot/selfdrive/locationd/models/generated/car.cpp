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
void err_fun(double *nom_x, double *delta_x, double *out_8118814337675434360) {
   out_8118814337675434360[0] = delta_x[0] + nom_x[0];
   out_8118814337675434360[1] = delta_x[1] + nom_x[1];
   out_8118814337675434360[2] = delta_x[2] + nom_x[2];
   out_8118814337675434360[3] = delta_x[3] + nom_x[3];
   out_8118814337675434360[4] = delta_x[4] + nom_x[4];
   out_8118814337675434360[5] = delta_x[5] + nom_x[5];
   out_8118814337675434360[6] = delta_x[6] + nom_x[6];
   out_8118814337675434360[7] = delta_x[7] + nom_x[7];
   out_8118814337675434360[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2446487967258621015) {
   out_2446487967258621015[0] = -nom_x[0] + true_x[0];
   out_2446487967258621015[1] = -nom_x[1] + true_x[1];
   out_2446487967258621015[2] = -nom_x[2] + true_x[2];
   out_2446487967258621015[3] = -nom_x[3] + true_x[3];
   out_2446487967258621015[4] = -nom_x[4] + true_x[4];
   out_2446487967258621015[5] = -nom_x[5] + true_x[5];
   out_2446487967258621015[6] = -nom_x[6] + true_x[6];
   out_2446487967258621015[7] = -nom_x[7] + true_x[7];
   out_2446487967258621015[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4385027558944011010) {
   out_4385027558944011010[0] = 1.0;
   out_4385027558944011010[1] = 0.0;
   out_4385027558944011010[2] = 0.0;
   out_4385027558944011010[3] = 0.0;
   out_4385027558944011010[4] = 0.0;
   out_4385027558944011010[5] = 0.0;
   out_4385027558944011010[6] = 0.0;
   out_4385027558944011010[7] = 0.0;
   out_4385027558944011010[8] = 0.0;
   out_4385027558944011010[9] = 0.0;
   out_4385027558944011010[10] = 1.0;
   out_4385027558944011010[11] = 0.0;
   out_4385027558944011010[12] = 0.0;
   out_4385027558944011010[13] = 0.0;
   out_4385027558944011010[14] = 0.0;
   out_4385027558944011010[15] = 0.0;
   out_4385027558944011010[16] = 0.0;
   out_4385027558944011010[17] = 0.0;
   out_4385027558944011010[18] = 0.0;
   out_4385027558944011010[19] = 0.0;
   out_4385027558944011010[20] = 1.0;
   out_4385027558944011010[21] = 0.0;
   out_4385027558944011010[22] = 0.0;
   out_4385027558944011010[23] = 0.0;
   out_4385027558944011010[24] = 0.0;
   out_4385027558944011010[25] = 0.0;
   out_4385027558944011010[26] = 0.0;
   out_4385027558944011010[27] = 0.0;
   out_4385027558944011010[28] = 0.0;
   out_4385027558944011010[29] = 0.0;
   out_4385027558944011010[30] = 1.0;
   out_4385027558944011010[31] = 0.0;
   out_4385027558944011010[32] = 0.0;
   out_4385027558944011010[33] = 0.0;
   out_4385027558944011010[34] = 0.0;
   out_4385027558944011010[35] = 0.0;
   out_4385027558944011010[36] = 0.0;
   out_4385027558944011010[37] = 0.0;
   out_4385027558944011010[38] = 0.0;
   out_4385027558944011010[39] = 0.0;
   out_4385027558944011010[40] = 1.0;
   out_4385027558944011010[41] = 0.0;
   out_4385027558944011010[42] = 0.0;
   out_4385027558944011010[43] = 0.0;
   out_4385027558944011010[44] = 0.0;
   out_4385027558944011010[45] = 0.0;
   out_4385027558944011010[46] = 0.0;
   out_4385027558944011010[47] = 0.0;
   out_4385027558944011010[48] = 0.0;
   out_4385027558944011010[49] = 0.0;
   out_4385027558944011010[50] = 1.0;
   out_4385027558944011010[51] = 0.0;
   out_4385027558944011010[52] = 0.0;
   out_4385027558944011010[53] = 0.0;
   out_4385027558944011010[54] = 0.0;
   out_4385027558944011010[55] = 0.0;
   out_4385027558944011010[56] = 0.0;
   out_4385027558944011010[57] = 0.0;
   out_4385027558944011010[58] = 0.0;
   out_4385027558944011010[59] = 0.0;
   out_4385027558944011010[60] = 1.0;
   out_4385027558944011010[61] = 0.0;
   out_4385027558944011010[62] = 0.0;
   out_4385027558944011010[63] = 0.0;
   out_4385027558944011010[64] = 0.0;
   out_4385027558944011010[65] = 0.0;
   out_4385027558944011010[66] = 0.0;
   out_4385027558944011010[67] = 0.0;
   out_4385027558944011010[68] = 0.0;
   out_4385027558944011010[69] = 0.0;
   out_4385027558944011010[70] = 1.0;
   out_4385027558944011010[71] = 0.0;
   out_4385027558944011010[72] = 0.0;
   out_4385027558944011010[73] = 0.0;
   out_4385027558944011010[74] = 0.0;
   out_4385027558944011010[75] = 0.0;
   out_4385027558944011010[76] = 0.0;
   out_4385027558944011010[77] = 0.0;
   out_4385027558944011010[78] = 0.0;
   out_4385027558944011010[79] = 0.0;
   out_4385027558944011010[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6609873402410428986) {
   out_6609873402410428986[0] = state[0];
   out_6609873402410428986[1] = state[1];
   out_6609873402410428986[2] = state[2];
   out_6609873402410428986[3] = state[3];
   out_6609873402410428986[4] = state[4];
   out_6609873402410428986[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6609873402410428986[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6609873402410428986[7] = state[7];
   out_6609873402410428986[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6492042525862959454) {
   out_6492042525862959454[0] = 1;
   out_6492042525862959454[1] = 0;
   out_6492042525862959454[2] = 0;
   out_6492042525862959454[3] = 0;
   out_6492042525862959454[4] = 0;
   out_6492042525862959454[5] = 0;
   out_6492042525862959454[6] = 0;
   out_6492042525862959454[7] = 0;
   out_6492042525862959454[8] = 0;
   out_6492042525862959454[9] = 0;
   out_6492042525862959454[10] = 1;
   out_6492042525862959454[11] = 0;
   out_6492042525862959454[12] = 0;
   out_6492042525862959454[13] = 0;
   out_6492042525862959454[14] = 0;
   out_6492042525862959454[15] = 0;
   out_6492042525862959454[16] = 0;
   out_6492042525862959454[17] = 0;
   out_6492042525862959454[18] = 0;
   out_6492042525862959454[19] = 0;
   out_6492042525862959454[20] = 1;
   out_6492042525862959454[21] = 0;
   out_6492042525862959454[22] = 0;
   out_6492042525862959454[23] = 0;
   out_6492042525862959454[24] = 0;
   out_6492042525862959454[25] = 0;
   out_6492042525862959454[26] = 0;
   out_6492042525862959454[27] = 0;
   out_6492042525862959454[28] = 0;
   out_6492042525862959454[29] = 0;
   out_6492042525862959454[30] = 1;
   out_6492042525862959454[31] = 0;
   out_6492042525862959454[32] = 0;
   out_6492042525862959454[33] = 0;
   out_6492042525862959454[34] = 0;
   out_6492042525862959454[35] = 0;
   out_6492042525862959454[36] = 0;
   out_6492042525862959454[37] = 0;
   out_6492042525862959454[38] = 0;
   out_6492042525862959454[39] = 0;
   out_6492042525862959454[40] = 1;
   out_6492042525862959454[41] = 0;
   out_6492042525862959454[42] = 0;
   out_6492042525862959454[43] = 0;
   out_6492042525862959454[44] = 0;
   out_6492042525862959454[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6492042525862959454[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6492042525862959454[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6492042525862959454[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6492042525862959454[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6492042525862959454[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6492042525862959454[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6492042525862959454[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6492042525862959454[53] = -9.8100000000000005*dt;
   out_6492042525862959454[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6492042525862959454[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6492042525862959454[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6492042525862959454[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6492042525862959454[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6492042525862959454[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6492042525862959454[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6492042525862959454[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6492042525862959454[62] = 0;
   out_6492042525862959454[63] = 0;
   out_6492042525862959454[64] = 0;
   out_6492042525862959454[65] = 0;
   out_6492042525862959454[66] = 0;
   out_6492042525862959454[67] = 0;
   out_6492042525862959454[68] = 0;
   out_6492042525862959454[69] = 0;
   out_6492042525862959454[70] = 1;
   out_6492042525862959454[71] = 0;
   out_6492042525862959454[72] = 0;
   out_6492042525862959454[73] = 0;
   out_6492042525862959454[74] = 0;
   out_6492042525862959454[75] = 0;
   out_6492042525862959454[76] = 0;
   out_6492042525862959454[77] = 0;
   out_6492042525862959454[78] = 0;
   out_6492042525862959454[79] = 0;
   out_6492042525862959454[80] = 1;
}
void h_25(double *state, double *unused, double *out_1305345852000088236) {
   out_1305345852000088236[0] = state[6];
}
void H_25(double *state, double *unused, double *out_518664266240653830) {
   out_518664266240653830[0] = 0;
   out_518664266240653830[1] = 0;
   out_518664266240653830[2] = 0;
   out_518664266240653830[3] = 0;
   out_518664266240653830[4] = 0;
   out_518664266240653830[5] = 0;
   out_518664266240653830[6] = 1;
   out_518664266240653830[7] = 0;
   out_518664266240653830[8] = 0;
}
void h_24(double *state, double *unused, double *out_1085442299742350701) {
   out_1085442299742350701[0] = state[4];
   out_1085442299742350701[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2695878689847803803) {
   out_2695878689847803803[0] = 0;
   out_2695878689847803803[1] = 0;
   out_2695878689847803803[2] = 0;
   out_2695878689847803803[3] = 0;
   out_2695878689847803803[4] = 1;
   out_2695878689847803803[5] = 0;
   out_2695878689847803803[6] = 0;
   out_2695878689847803803[7] = 0;
   out_2695878689847803803[8] = 0;
   out_2695878689847803803[9] = 0;
   out_2695878689847803803[10] = 0;
   out_2695878689847803803[11] = 0;
   out_2695878689847803803[12] = 0;
   out_2695878689847803803[13] = 0;
   out_2695878689847803803[14] = 1;
   out_2695878689847803803[15] = 0;
   out_2695878689847803803[16] = 0;
   out_2695878689847803803[17] = 0;
}
void h_30(double *state, double *unused, double *out_2556337624428413416) {
   out_2556337624428413416[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3036997224747902457) {
   out_3036997224747902457[0] = 0;
   out_3036997224747902457[1] = 0;
   out_3036997224747902457[2] = 0;
   out_3036997224747902457[3] = 0;
   out_3036997224747902457[4] = 1;
   out_3036997224747902457[5] = 0;
   out_3036997224747902457[6] = 0;
   out_3036997224747902457[7] = 0;
   out_3036997224747902457[8] = 0;
}
void h_26(double *state, double *unused, double *out_2669569591406911531) {
   out_2669569591406911531[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3222839052633402394) {
   out_3222839052633402394[0] = 0;
   out_3222839052633402394[1] = 0;
   out_3222839052633402394[2] = 0;
   out_3222839052633402394[3] = 0;
   out_3222839052633402394[4] = 0;
   out_3222839052633402394[5] = 0;
   out_3222839052633402394[6] = 0;
   out_3222839052633402394[7] = 1;
   out_3222839052633402394[8] = 0;
}
void h_27(double *state, double *unused, double *out_323261758664790124) {
   out_323261758664790124[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6183795375687379279) {
   out_6183795375687379279[0] = 0;
   out_6183795375687379279[1] = 0;
   out_6183795375687379279[2] = 0;
   out_6183795375687379279[3] = 1;
   out_6183795375687379279[4] = 0;
   out_6183795375687379279[5] = 0;
   out_6183795375687379279[6] = 0;
   out_6183795375687379279[7] = 0;
   out_6183795375687379279[8] = 0;
}
void h_29(double *state, double *unused, double *out_7558010892089259061) {
   out_7558010892089259061[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3498800719572562184) {
   out_3498800719572562184[0] = 0;
   out_3498800719572562184[1] = 1;
   out_3498800719572562184[2] = 0;
   out_3498800719572562184[3] = 0;
   out_3498800719572562184[4] = 0;
   out_3498800719572562184[5] = 0;
   out_3498800719572562184[6] = 0;
   out_3498800719572562184[7] = 0;
   out_3498800719572562184[8] = 0;
}
void h_28(double *state, double *unused, double *out_5285641756346083356) {
   out_5285641756346083356[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1535170448007235933) {
   out_1535170448007235933[0] = 1;
   out_1535170448007235933[1] = 0;
   out_1535170448007235933[2] = 0;
   out_1535170448007235933[3] = 0;
   out_1535170448007235933[4] = 0;
   out_1535170448007235933[5] = 0;
   out_1535170448007235933[6] = 0;
   out_1535170448007235933[7] = 0;
   out_1535170448007235933[8] = 0;
}
void h_31(double *state, double *unused, double *out_3874303633696752602) {
   out_3874303633696752602[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3849047154866753870) {
   out_3849047154866753870[0] = 0;
   out_3849047154866753870[1] = 0;
   out_3849047154866753870[2] = 0;
   out_3849047154866753870[3] = 0;
   out_3849047154866753870[4] = 0;
   out_3849047154866753870[5] = 0;
   out_3849047154866753870[6] = 0;
   out_3849047154866753870[7] = 0;
   out_3849047154866753870[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8118814337675434360) {
  err_fun(nom_x, delta_x, out_8118814337675434360);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2446487967258621015) {
  inv_err_fun(nom_x, true_x, out_2446487967258621015);
}
void car_H_mod_fun(double *state, double *out_4385027558944011010) {
  H_mod_fun(state, out_4385027558944011010);
}
void car_f_fun(double *state, double dt, double *out_6609873402410428986) {
  f_fun(state,  dt, out_6609873402410428986);
}
void car_F_fun(double *state, double dt, double *out_6492042525862959454) {
  F_fun(state,  dt, out_6492042525862959454);
}
void car_h_25(double *state, double *unused, double *out_1305345852000088236) {
  h_25(state, unused, out_1305345852000088236);
}
void car_H_25(double *state, double *unused, double *out_518664266240653830) {
  H_25(state, unused, out_518664266240653830);
}
void car_h_24(double *state, double *unused, double *out_1085442299742350701) {
  h_24(state, unused, out_1085442299742350701);
}
void car_H_24(double *state, double *unused, double *out_2695878689847803803) {
  H_24(state, unused, out_2695878689847803803);
}
void car_h_30(double *state, double *unused, double *out_2556337624428413416) {
  h_30(state, unused, out_2556337624428413416);
}
void car_H_30(double *state, double *unused, double *out_3036997224747902457) {
  H_30(state, unused, out_3036997224747902457);
}
void car_h_26(double *state, double *unused, double *out_2669569591406911531) {
  h_26(state, unused, out_2669569591406911531);
}
void car_H_26(double *state, double *unused, double *out_3222839052633402394) {
  H_26(state, unused, out_3222839052633402394);
}
void car_h_27(double *state, double *unused, double *out_323261758664790124) {
  h_27(state, unused, out_323261758664790124);
}
void car_H_27(double *state, double *unused, double *out_6183795375687379279) {
  H_27(state, unused, out_6183795375687379279);
}
void car_h_29(double *state, double *unused, double *out_7558010892089259061) {
  h_29(state, unused, out_7558010892089259061);
}
void car_H_29(double *state, double *unused, double *out_3498800719572562184) {
  H_29(state, unused, out_3498800719572562184);
}
void car_h_28(double *state, double *unused, double *out_5285641756346083356) {
  h_28(state, unused, out_5285641756346083356);
}
void car_H_28(double *state, double *unused, double *out_1535170448007235933) {
  H_28(state, unused, out_1535170448007235933);
}
void car_h_31(double *state, double *unused, double *out_3874303633696752602) {
  h_31(state, unused, out_3874303633696752602);
}
void car_H_31(double *state, double *unused, double *out_3849047154866753870) {
  H_31(state, unused, out_3849047154866753870);
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
