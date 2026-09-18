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
void err_fun(double *nom_x, double *delta_x, double *out_8674505523865043261) {
   out_8674505523865043261[0] = delta_x[0] + nom_x[0];
   out_8674505523865043261[1] = delta_x[1] + nom_x[1];
   out_8674505523865043261[2] = delta_x[2] + nom_x[2];
   out_8674505523865043261[3] = delta_x[3] + nom_x[3];
   out_8674505523865043261[4] = delta_x[4] + nom_x[4];
   out_8674505523865043261[5] = delta_x[5] + nom_x[5];
   out_8674505523865043261[6] = delta_x[6] + nom_x[6];
   out_8674505523865043261[7] = delta_x[7] + nom_x[7];
   out_8674505523865043261[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6250570191206249369) {
   out_6250570191206249369[0] = -nom_x[0] + true_x[0];
   out_6250570191206249369[1] = -nom_x[1] + true_x[1];
   out_6250570191206249369[2] = -nom_x[2] + true_x[2];
   out_6250570191206249369[3] = -nom_x[3] + true_x[3];
   out_6250570191206249369[4] = -nom_x[4] + true_x[4];
   out_6250570191206249369[5] = -nom_x[5] + true_x[5];
   out_6250570191206249369[6] = -nom_x[6] + true_x[6];
   out_6250570191206249369[7] = -nom_x[7] + true_x[7];
   out_6250570191206249369[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_742618674605284176) {
   out_742618674605284176[0] = 1.0;
   out_742618674605284176[1] = 0.0;
   out_742618674605284176[2] = 0.0;
   out_742618674605284176[3] = 0.0;
   out_742618674605284176[4] = 0.0;
   out_742618674605284176[5] = 0.0;
   out_742618674605284176[6] = 0.0;
   out_742618674605284176[7] = 0.0;
   out_742618674605284176[8] = 0.0;
   out_742618674605284176[9] = 0.0;
   out_742618674605284176[10] = 1.0;
   out_742618674605284176[11] = 0.0;
   out_742618674605284176[12] = 0.0;
   out_742618674605284176[13] = 0.0;
   out_742618674605284176[14] = 0.0;
   out_742618674605284176[15] = 0.0;
   out_742618674605284176[16] = 0.0;
   out_742618674605284176[17] = 0.0;
   out_742618674605284176[18] = 0.0;
   out_742618674605284176[19] = 0.0;
   out_742618674605284176[20] = 1.0;
   out_742618674605284176[21] = 0.0;
   out_742618674605284176[22] = 0.0;
   out_742618674605284176[23] = 0.0;
   out_742618674605284176[24] = 0.0;
   out_742618674605284176[25] = 0.0;
   out_742618674605284176[26] = 0.0;
   out_742618674605284176[27] = 0.0;
   out_742618674605284176[28] = 0.0;
   out_742618674605284176[29] = 0.0;
   out_742618674605284176[30] = 1.0;
   out_742618674605284176[31] = 0.0;
   out_742618674605284176[32] = 0.0;
   out_742618674605284176[33] = 0.0;
   out_742618674605284176[34] = 0.0;
   out_742618674605284176[35] = 0.0;
   out_742618674605284176[36] = 0.0;
   out_742618674605284176[37] = 0.0;
   out_742618674605284176[38] = 0.0;
   out_742618674605284176[39] = 0.0;
   out_742618674605284176[40] = 1.0;
   out_742618674605284176[41] = 0.0;
   out_742618674605284176[42] = 0.0;
   out_742618674605284176[43] = 0.0;
   out_742618674605284176[44] = 0.0;
   out_742618674605284176[45] = 0.0;
   out_742618674605284176[46] = 0.0;
   out_742618674605284176[47] = 0.0;
   out_742618674605284176[48] = 0.0;
   out_742618674605284176[49] = 0.0;
   out_742618674605284176[50] = 1.0;
   out_742618674605284176[51] = 0.0;
   out_742618674605284176[52] = 0.0;
   out_742618674605284176[53] = 0.0;
   out_742618674605284176[54] = 0.0;
   out_742618674605284176[55] = 0.0;
   out_742618674605284176[56] = 0.0;
   out_742618674605284176[57] = 0.0;
   out_742618674605284176[58] = 0.0;
   out_742618674605284176[59] = 0.0;
   out_742618674605284176[60] = 1.0;
   out_742618674605284176[61] = 0.0;
   out_742618674605284176[62] = 0.0;
   out_742618674605284176[63] = 0.0;
   out_742618674605284176[64] = 0.0;
   out_742618674605284176[65] = 0.0;
   out_742618674605284176[66] = 0.0;
   out_742618674605284176[67] = 0.0;
   out_742618674605284176[68] = 0.0;
   out_742618674605284176[69] = 0.0;
   out_742618674605284176[70] = 1.0;
   out_742618674605284176[71] = 0.0;
   out_742618674605284176[72] = 0.0;
   out_742618674605284176[73] = 0.0;
   out_742618674605284176[74] = 0.0;
   out_742618674605284176[75] = 0.0;
   out_742618674605284176[76] = 0.0;
   out_742618674605284176[77] = 0.0;
   out_742618674605284176[78] = 0.0;
   out_742618674605284176[79] = 0.0;
   out_742618674605284176[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8095007039495488980) {
   out_8095007039495488980[0] = state[0];
   out_8095007039495488980[1] = state[1];
   out_8095007039495488980[2] = state[2];
   out_8095007039495488980[3] = state[3];
   out_8095007039495488980[4] = state[4];
   out_8095007039495488980[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8095007039495488980[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8095007039495488980[7] = state[7];
   out_8095007039495488980[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7050818561186322839) {
   out_7050818561186322839[0] = 1;
   out_7050818561186322839[1] = 0;
   out_7050818561186322839[2] = 0;
   out_7050818561186322839[3] = 0;
   out_7050818561186322839[4] = 0;
   out_7050818561186322839[5] = 0;
   out_7050818561186322839[6] = 0;
   out_7050818561186322839[7] = 0;
   out_7050818561186322839[8] = 0;
   out_7050818561186322839[9] = 0;
   out_7050818561186322839[10] = 1;
   out_7050818561186322839[11] = 0;
   out_7050818561186322839[12] = 0;
   out_7050818561186322839[13] = 0;
   out_7050818561186322839[14] = 0;
   out_7050818561186322839[15] = 0;
   out_7050818561186322839[16] = 0;
   out_7050818561186322839[17] = 0;
   out_7050818561186322839[18] = 0;
   out_7050818561186322839[19] = 0;
   out_7050818561186322839[20] = 1;
   out_7050818561186322839[21] = 0;
   out_7050818561186322839[22] = 0;
   out_7050818561186322839[23] = 0;
   out_7050818561186322839[24] = 0;
   out_7050818561186322839[25] = 0;
   out_7050818561186322839[26] = 0;
   out_7050818561186322839[27] = 0;
   out_7050818561186322839[28] = 0;
   out_7050818561186322839[29] = 0;
   out_7050818561186322839[30] = 1;
   out_7050818561186322839[31] = 0;
   out_7050818561186322839[32] = 0;
   out_7050818561186322839[33] = 0;
   out_7050818561186322839[34] = 0;
   out_7050818561186322839[35] = 0;
   out_7050818561186322839[36] = 0;
   out_7050818561186322839[37] = 0;
   out_7050818561186322839[38] = 0;
   out_7050818561186322839[39] = 0;
   out_7050818561186322839[40] = 1;
   out_7050818561186322839[41] = 0;
   out_7050818561186322839[42] = 0;
   out_7050818561186322839[43] = 0;
   out_7050818561186322839[44] = 0;
   out_7050818561186322839[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7050818561186322839[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7050818561186322839[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7050818561186322839[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7050818561186322839[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7050818561186322839[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7050818561186322839[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7050818561186322839[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7050818561186322839[53] = -9.8100000000000005*dt;
   out_7050818561186322839[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7050818561186322839[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7050818561186322839[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7050818561186322839[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7050818561186322839[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7050818561186322839[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7050818561186322839[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7050818561186322839[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7050818561186322839[62] = 0;
   out_7050818561186322839[63] = 0;
   out_7050818561186322839[64] = 0;
   out_7050818561186322839[65] = 0;
   out_7050818561186322839[66] = 0;
   out_7050818561186322839[67] = 0;
   out_7050818561186322839[68] = 0;
   out_7050818561186322839[69] = 0;
   out_7050818561186322839[70] = 1;
   out_7050818561186322839[71] = 0;
   out_7050818561186322839[72] = 0;
   out_7050818561186322839[73] = 0;
   out_7050818561186322839[74] = 0;
   out_7050818561186322839[75] = 0;
   out_7050818561186322839[76] = 0;
   out_7050818561186322839[77] = 0;
   out_7050818561186322839[78] = 0;
   out_7050818561186322839[79] = 0;
   out_7050818561186322839[80] = 1;
}
void h_25(double *state, double *unused, double *out_4702846008704956131) {
   out_4702846008704956131[0] = state[6];
}
void H_25(double *state, double *unused, double *out_23829087476923073) {
   out_23829087476923073[0] = 0;
   out_23829087476923073[1] = 0;
   out_23829087476923073[2] = 0;
   out_23829087476923073[3] = 0;
   out_23829087476923073[4] = 0;
   out_23829087476923073[5] = 0;
   out_23829087476923073[6] = 1;
   out_23829087476923073[7] = 0;
   out_23829087476923073[8] = 0;
}
void h_24(double *state, double *unused, double *out_910324667090234605) {
   out_910324667090234605[0] = state[4];
   out_910324667090234605[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6224861767328084499) {
   out_6224861767328084499[0] = 0;
   out_6224861767328084499[1] = 0;
   out_6224861767328084499[2] = 0;
   out_6224861767328084499[3] = 0;
   out_6224861767328084499[4] = 1;
   out_6224861767328084499[5] = 0;
   out_6224861767328084499[6] = 0;
   out_6224861767328084499[7] = 0;
   out_6224861767328084499[8] = 0;
   out_6224861767328084499[9] = 0;
   out_6224861767328084499[10] = 0;
   out_6224861767328084499[11] = 0;
   out_6224861767328084499[12] = 0;
   out_6224861767328084499[13] = 0;
   out_6224861767328084499[14] = 1;
   out_6224861767328084499[15] = 0;
   out_6224861767328084499[16] = 0;
   out_6224861767328084499[17] = 0;
}
void h_30(double *state, double *unused, double *out_823211427846066982) {
   out_823211427846066982[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4551525417604531271) {
   out_4551525417604531271[0] = 0;
   out_4551525417604531271[1] = 0;
   out_4551525417604531271[2] = 0;
   out_4551525417604531271[3] = 0;
   out_4551525417604531271[4] = 1;
   out_4551525417604531271[5] = 0;
   out_4551525417604531271[6] = 0;
   out_4551525417604531271[7] = 0;
   out_4551525417604531271[8] = 0;
}
void h_26(double *state, double *unused, double *out_6668487905725142980) {
   out_6668487905725142980[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3765332406350979297) {
   out_3765332406350979297[0] = 0;
   out_3765332406350979297[1] = 0;
   out_3765332406350979297[2] = 0;
   out_3765332406350979297[3] = 0;
   out_3765332406350979297[4] = 0;
   out_3765332406350979297[5] = 0;
   out_3765332406350979297[6] = 0;
   out_3765332406350979297[7] = 1;
   out_3765332406350979297[8] = 0;
}
void h_27(double *state, double *unused, double *out_3343218477695586303) {
   out_3343218477695586303[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6726288729404956182) {
   out_6726288729404956182[0] = 0;
   out_6726288729404956182[1] = 0;
   out_6726288729404956182[2] = 0;
   out_6726288729404956182[3] = 1;
   out_6726288729404956182[4] = 0;
   out_6726288729404956182[5] = 0;
   out_6726288729404956182[6] = 0;
   out_6726288729404956182[7] = 0;
   out_6726288729404956182[8] = 0;
}
void h_29(double *state, double *unused, double *out_7222252945259916128) {
   out_7222252945259916128[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4041294073290139087) {
   out_4041294073290139087[0] = 0;
   out_4041294073290139087[1] = 1;
   out_4041294073290139087[2] = 0;
   out_4041294073290139087[3] = 0;
   out_4041294073290139087[4] = 0;
   out_4041294073290139087[5] = 0;
   out_4041294073290139087[6] = 0;
   out_4041294073290139087[7] = 0;
   out_4041294073290139087[8] = 0;
}
void h_28(double *state, double *unused, double *out_2399708624793923868) {
   out_2399708624793923868[0] = state[0];
}
void H_28(double *state, double *unused, double *out_9123693090359669661) {
   out_9123693090359669661[0] = 1;
   out_9123693090359669661[1] = 0;
   out_9123693090359669661[2] = 0;
   out_9123693090359669661[3] = 0;
   out_9123693090359669661[4] = 0;
   out_9123693090359669661[5] = 0;
   out_9123693090359669661[6] = 0;
   out_9123693090359669661[7] = 0;
   out_9123693090359669661[8] = 0;
}
void h_31(double *state, double *unused, double *out_6104810466855413099) {
   out_6104810466855413099[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4391540508584330773) {
   out_4391540508584330773[0] = 0;
   out_4391540508584330773[1] = 0;
   out_4391540508584330773[2] = 0;
   out_4391540508584330773[3] = 0;
   out_4391540508584330773[4] = 0;
   out_4391540508584330773[5] = 0;
   out_4391540508584330773[6] = 0;
   out_4391540508584330773[7] = 0;
   out_4391540508584330773[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8674505523865043261) {
  err_fun(nom_x, delta_x, out_8674505523865043261);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6250570191206249369) {
  inv_err_fun(nom_x, true_x, out_6250570191206249369);
}
void car_H_mod_fun(double *state, double *out_742618674605284176) {
  H_mod_fun(state, out_742618674605284176);
}
void car_f_fun(double *state, double dt, double *out_8095007039495488980) {
  f_fun(state,  dt, out_8095007039495488980);
}
void car_F_fun(double *state, double dt, double *out_7050818561186322839) {
  F_fun(state,  dt, out_7050818561186322839);
}
void car_h_25(double *state, double *unused, double *out_4702846008704956131) {
  h_25(state, unused, out_4702846008704956131);
}
void car_H_25(double *state, double *unused, double *out_23829087476923073) {
  H_25(state, unused, out_23829087476923073);
}
void car_h_24(double *state, double *unused, double *out_910324667090234605) {
  h_24(state, unused, out_910324667090234605);
}
void car_H_24(double *state, double *unused, double *out_6224861767328084499) {
  H_24(state, unused, out_6224861767328084499);
}
void car_h_30(double *state, double *unused, double *out_823211427846066982) {
  h_30(state, unused, out_823211427846066982);
}
void car_H_30(double *state, double *unused, double *out_4551525417604531271) {
  H_30(state, unused, out_4551525417604531271);
}
void car_h_26(double *state, double *unused, double *out_6668487905725142980) {
  h_26(state, unused, out_6668487905725142980);
}
void car_H_26(double *state, double *unused, double *out_3765332406350979297) {
  H_26(state, unused, out_3765332406350979297);
}
void car_h_27(double *state, double *unused, double *out_3343218477695586303) {
  h_27(state, unused, out_3343218477695586303);
}
void car_H_27(double *state, double *unused, double *out_6726288729404956182) {
  H_27(state, unused, out_6726288729404956182);
}
void car_h_29(double *state, double *unused, double *out_7222252945259916128) {
  h_29(state, unused, out_7222252945259916128);
}
void car_H_29(double *state, double *unused, double *out_4041294073290139087) {
  H_29(state, unused, out_4041294073290139087);
}
void car_h_28(double *state, double *unused, double *out_2399708624793923868) {
  h_28(state, unused, out_2399708624793923868);
}
void car_H_28(double *state, double *unused, double *out_9123693090359669661) {
  H_28(state, unused, out_9123693090359669661);
}
void car_h_31(double *state, double *unused, double *out_6104810466855413099) {
  h_31(state, unused, out_6104810466855413099);
}
void car_H_31(double *state, double *unused, double *out_4391540508584330773) {
  H_31(state, unused, out_4391540508584330773);
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
