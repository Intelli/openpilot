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
void err_fun(double *nom_x, double *delta_x, double *out_113716983378204622) {
   out_113716983378204622[0] = delta_x[0] + nom_x[0];
   out_113716983378204622[1] = delta_x[1] + nom_x[1];
   out_113716983378204622[2] = delta_x[2] + nom_x[2];
   out_113716983378204622[3] = delta_x[3] + nom_x[3];
   out_113716983378204622[4] = delta_x[4] + nom_x[4];
   out_113716983378204622[5] = delta_x[5] + nom_x[5];
   out_113716983378204622[6] = delta_x[6] + nom_x[6];
   out_113716983378204622[7] = delta_x[7] + nom_x[7];
   out_113716983378204622[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3175147354684049495) {
   out_3175147354684049495[0] = -nom_x[0] + true_x[0];
   out_3175147354684049495[1] = -nom_x[1] + true_x[1];
   out_3175147354684049495[2] = -nom_x[2] + true_x[2];
   out_3175147354684049495[3] = -nom_x[3] + true_x[3];
   out_3175147354684049495[4] = -nom_x[4] + true_x[4];
   out_3175147354684049495[5] = -nom_x[5] + true_x[5];
   out_3175147354684049495[6] = -nom_x[6] + true_x[6];
   out_3175147354684049495[7] = -nom_x[7] + true_x[7];
   out_3175147354684049495[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5065659025262341849) {
   out_5065659025262341849[0] = 1.0;
   out_5065659025262341849[1] = 0.0;
   out_5065659025262341849[2] = 0.0;
   out_5065659025262341849[3] = 0.0;
   out_5065659025262341849[4] = 0.0;
   out_5065659025262341849[5] = 0.0;
   out_5065659025262341849[6] = 0.0;
   out_5065659025262341849[7] = 0.0;
   out_5065659025262341849[8] = 0.0;
   out_5065659025262341849[9] = 0.0;
   out_5065659025262341849[10] = 1.0;
   out_5065659025262341849[11] = 0.0;
   out_5065659025262341849[12] = 0.0;
   out_5065659025262341849[13] = 0.0;
   out_5065659025262341849[14] = 0.0;
   out_5065659025262341849[15] = 0.0;
   out_5065659025262341849[16] = 0.0;
   out_5065659025262341849[17] = 0.0;
   out_5065659025262341849[18] = 0.0;
   out_5065659025262341849[19] = 0.0;
   out_5065659025262341849[20] = 1.0;
   out_5065659025262341849[21] = 0.0;
   out_5065659025262341849[22] = 0.0;
   out_5065659025262341849[23] = 0.0;
   out_5065659025262341849[24] = 0.0;
   out_5065659025262341849[25] = 0.0;
   out_5065659025262341849[26] = 0.0;
   out_5065659025262341849[27] = 0.0;
   out_5065659025262341849[28] = 0.0;
   out_5065659025262341849[29] = 0.0;
   out_5065659025262341849[30] = 1.0;
   out_5065659025262341849[31] = 0.0;
   out_5065659025262341849[32] = 0.0;
   out_5065659025262341849[33] = 0.0;
   out_5065659025262341849[34] = 0.0;
   out_5065659025262341849[35] = 0.0;
   out_5065659025262341849[36] = 0.0;
   out_5065659025262341849[37] = 0.0;
   out_5065659025262341849[38] = 0.0;
   out_5065659025262341849[39] = 0.0;
   out_5065659025262341849[40] = 1.0;
   out_5065659025262341849[41] = 0.0;
   out_5065659025262341849[42] = 0.0;
   out_5065659025262341849[43] = 0.0;
   out_5065659025262341849[44] = 0.0;
   out_5065659025262341849[45] = 0.0;
   out_5065659025262341849[46] = 0.0;
   out_5065659025262341849[47] = 0.0;
   out_5065659025262341849[48] = 0.0;
   out_5065659025262341849[49] = 0.0;
   out_5065659025262341849[50] = 1.0;
   out_5065659025262341849[51] = 0.0;
   out_5065659025262341849[52] = 0.0;
   out_5065659025262341849[53] = 0.0;
   out_5065659025262341849[54] = 0.0;
   out_5065659025262341849[55] = 0.0;
   out_5065659025262341849[56] = 0.0;
   out_5065659025262341849[57] = 0.0;
   out_5065659025262341849[58] = 0.0;
   out_5065659025262341849[59] = 0.0;
   out_5065659025262341849[60] = 1.0;
   out_5065659025262341849[61] = 0.0;
   out_5065659025262341849[62] = 0.0;
   out_5065659025262341849[63] = 0.0;
   out_5065659025262341849[64] = 0.0;
   out_5065659025262341849[65] = 0.0;
   out_5065659025262341849[66] = 0.0;
   out_5065659025262341849[67] = 0.0;
   out_5065659025262341849[68] = 0.0;
   out_5065659025262341849[69] = 0.0;
   out_5065659025262341849[70] = 1.0;
   out_5065659025262341849[71] = 0.0;
   out_5065659025262341849[72] = 0.0;
   out_5065659025262341849[73] = 0.0;
   out_5065659025262341849[74] = 0.0;
   out_5065659025262341849[75] = 0.0;
   out_5065659025262341849[76] = 0.0;
   out_5065659025262341849[77] = 0.0;
   out_5065659025262341849[78] = 0.0;
   out_5065659025262341849[79] = 0.0;
   out_5065659025262341849[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8000933351783123572) {
   out_8000933351783123572[0] = state[0];
   out_8000933351783123572[1] = state[1];
   out_8000933351783123572[2] = state[2];
   out_8000933351783123572[3] = state[3];
   out_8000933351783123572[4] = state[4];
   out_8000933351783123572[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8000933351783123572[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8000933351783123572[7] = state[7];
   out_8000933351783123572[8] = state[8];
}
void F_fun(double *state, double dt, double *out_409468777326581195) {
   out_409468777326581195[0] = 1;
   out_409468777326581195[1] = 0;
   out_409468777326581195[2] = 0;
   out_409468777326581195[3] = 0;
   out_409468777326581195[4] = 0;
   out_409468777326581195[5] = 0;
   out_409468777326581195[6] = 0;
   out_409468777326581195[7] = 0;
   out_409468777326581195[8] = 0;
   out_409468777326581195[9] = 0;
   out_409468777326581195[10] = 1;
   out_409468777326581195[11] = 0;
   out_409468777326581195[12] = 0;
   out_409468777326581195[13] = 0;
   out_409468777326581195[14] = 0;
   out_409468777326581195[15] = 0;
   out_409468777326581195[16] = 0;
   out_409468777326581195[17] = 0;
   out_409468777326581195[18] = 0;
   out_409468777326581195[19] = 0;
   out_409468777326581195[20] = 1;
   out_409468777326581195[21] = 0;
   out_409468777326581195[22] = 0;
   out_409468777326581195[23] = 0;
   out_409468777326581195[24] = 0;
   out_409468777326581195[25] = 0;
   out_409468777326581195[26] = 0;
   out_409468777326581195[27] = 0;
   out_409468777326581195[28] = 0;
   out_409468777326581195[29] = 0;
   out_409468777326581195[30] = 1;
   out_409468777326581195[31] = 0;
   out_409468777326581195[32] = 0;
   out_409468777326581195[33] = 0;
   out_409468777326581195[34] = 0;
   out_409468777326581195[35] = 0;
   out_409468777326581195[36] = 0;
   out_409468777326581195[37] = 0;
   out_409468777326581195[38] = 0;
   out_409468777326581195[39] = 0;
   out_409468777326581195[40] = 1;
   out_409468777326581195[41] = 0;
   out_409468777326581195[42] = 0;
   out_409468777326581195[43] = 0;
   out_409468777326581195[44] = 0;
   out_409468777326581195[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_409468777326581195[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_409468777326581195[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_409468777326581195[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_409468777326581195[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_409468777326581195[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_409468777326581195[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_409468777326581195[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_409468777326581195[53] = -9.8100000000000005*dt;
   out_409468777326581195[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_409468777326581195[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_409468777326581195[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_409468777326581195[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_409468777326581195[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_409468777326581195[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_409468777326581195[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_409468777326581195[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_409468777326581195[62] = 0;
   out_409468777326581195[63] = 0;
   out_409468777326581195[64] = 0;
   out_409468777326581195[65] = 0;
   out_409468777326581195[66] = 0;
   out_409468777326581195[67] = 0;
   out_409468777326581195[68] = 0;
   out_409468777326581195[69] = 0;
   out_409468777326581195[70] = 1;
   out_409468777326581195[71] = 0;
   out_409468777326581195[72] = 0;
   out_409468777326581195[73] = 0;
   out_409468777326581195[74] = 0;
   out_409468777326581195[75] = 0;
   out_409468777326581195[76] = 0;
   out_409468777326581195[77] = 0;
   out_409468777326581195[78] = 0;
   out_409468777326581195[79] = 0;
   out_409468777326581195[80] = 1;
}
void h_25(double *state, double *unused, double *out_3884977761234258648) {
   out_3884977761234258648[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5570993467462638561) {
   out_5570993467462638561[0] = 0;
   out_5570993467462638561[1] = 0;
   out_5570993467462638561[2] = 0;
   out_5570993467462638561[3] = 0;
   out_5570993467462638561[4] = 0;
   out_5570993467462638561[5] = 0;
   out_5570993467462638561[6] = 1;
   out_5570993467462638561[7] = 0;
   out_5570993467462638561[8] = 0;
}
void h_24(double *state, double *unused, double *out_3737140147320417057) {
   out_3737140147320417057[0] = state[4];
   out_3737140147320417057[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6300178799655394954) {
   out_6300178799655394954[0] = 0;
   out_6300178799655394954[1] = 0;
   out_6300178799655394954[2] = 0;
   out_6300178799655394954[3] = 0;
   out_6300178799655394954[4] = 1;
   out_6300178799655394954[5] = 0;
   out_6300178799655394954[6] = 0;
   out_6300178799655394954[7] = 0;
   out_6300178799655394954[8] = 0;
   out_6300178799655394954[9] = 0;
   out_6300178799655394954[10] = 0;
   out_6300178799655394954[11] = 0;
   out_6300178799655394954[12] = 0;
   out_6300178799655394954[13] = 0;
   out_6300178799655394954[14] = 1;
   out_6300178799655394954[15] = 0;
   out_6300178799655394954[16] = 0;
   out_6300178799655394954[17] = 0;
}
void h_30(double *state, double *unused, double *out_4160171823518764537) {
   out_4160171823518764537[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5959060264755296300) {
   out_5959060264755296300[0] = 0;
   out_5959060264755296300[1] = 0;
   out_5959060264755296300[2] = 0;
   out_5959060264755296300[3] = 0;
   out_5959060264755296300[4] = 1;
   out_5959060264755296300[5] = 0;
   out_5959060264755296300[6] = 0;
   out_5959060264755296300[7] = 0;
   out_5959060264755296300[8] = 0;
}
void h_26(double *state, double *unused, double *out_1718113664039950551) {
   out_1718113664039950551[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1829490148588582337) {
   out_1829490148588582337[0] = 0;
   out_1829490148588582337[1] = 0;
   out_1829490148588582337[2] = 0;
   out_1829490148588582337[3] = 0;
   out_1829490148588582337[4] = 0;
   out_1829490148588582337[5] = 0;
   out_1829490148588582337[6] = 0;
   out_1829490148588582337[7] = 1;
   out_1829490148588582337[8] = 0;
}
void h_27(double *state, double *unused, double *out_8886651028895104293) {
   out_8886651028895104293[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8133823576555721211) {
   out_8133823576555721211[0] = 0;
   out_8133823576555721211[1] = 0;
   out_8133823576555721211[2] = 0;
   out_8133823576555721211[3] = 1;
   out_8133823576555721211[4] = 0;
   out_8133823576555721211[5] = 0;
   out_8133823576555721211[6] = 0;
   out_8133823576555721211[7] = 0;
   out_8133823576555721211[8] = 0;
}
void h_29(double *state, double *unused, double *out_1347619720248911154) {
   out_1347619720248911154[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5448828920440904116) {
   out_5448828920440904116[0] = 0;
   out_5448828920440904116[1] = 1;
   out_5448828920440904116[2] = 0;
   out_5448828920440904116[3] = 0;
   out_5448828920440904116[4] = 0;
   out_5448828920440904116[5] = 0;
   out_5448828920440904116[6] = 0;
   out_5448828920440904116[7] = 0;
   out_5448828920440904116[8] = 0;
}
void h_28(double *state, double *unused, double *out_2108122273276517816) {
   out_2108122273276517816[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7915516136199116926) {
   out_7915516136199116926[0] = 1;
   out_7915516136199116926[1] = 0;
   out_7915516136199116926[2] = 0;
   out_7915516136199116926[3] = 0;
   out_7915516136199116926[4] = 0;
   out_7915516136199116926[5] = 0;
   out_7915516136199116926[6] = 0;
   out_7915516136199116926[7] = 0;
   out_7915516136199116926[8] = 0;
}
void h_31(double *state, double *unused, double *out_247528232980236298) {
   out_247528232980236298[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5601639429339598989) {
   out_5601639429339598989[0] = 0;
   out_5601639429339598989[1] = 0;
   out_5601639429339598989[2] = 0;
   out_5601639429339598989[3] = 0;
   out_5601639429339598989[4] = 0;
   out_5601639429339598989[5] = 0;
   out_5601639429339598989[6] = 0;
   out_5601639429339598989[7] = 0;
   out_5601639429339598989[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_113716983378204622) {
  err_fun(nom_x, delta_x, out_113716983378204622);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3175147354684049495) {
  inv_err_fun(nom_x, true_x, out_3175147354684049495);
}
void car_H_mod_fun(double *state, double *out_5065659025262341849) {
  H_mod_fun(state, out_5065659025262341849);
}
void car_f_fun(double *state, double dt, double *out_8000933351783123572) {
  f_fun(state,  dt, out_8000933351783123572);
}
void car_F_fun(double *state, double dt, double *out_409468777326581195) {
  F_fun(state,  dt, out_409468777326581195);
}
void car_h_25(double *state, double *unused, double *out_3884977761234258648) {
  h_25(state, unused, out_3884977761234258648);
}
void car_H_25(double *state, double *unused, double *out_5570993467462638561) {
  H_25(state, unused, out_5570993467462638561);
}
void car_h_24(double *state, double *unused, double *out_3737140147320417057) {
  h_24(state, unused, out_3737140147320417057);
}
void car_H_24(double *state, double *unused, double *out_6300178799655394954) {
  H_24(state, unused, out_6300178799655394954);
}
void car_h_30(double *state, double *unused, double *out_4160171823518764537) {
  h_30(state, unused, out_4160171823518764537);
}
void car_H_30(double *state, double *unused, double *out_5959060264755296300) {
  H_30(state, unused, out_5959060264755296300);
}
void car_h_26(double *state, double *unused, double *out_1718113664039950551) {
  h_26(state, unused, out_1718113664039950551);
}
void car_H_26(double *state, double *unused, double *out_1829490148588582337) {
  H_26(state, unused, out_1829490148588582337);
}
void car_h_27(double *state, double *unused, double *out_8886651028895104293) {
  h_27(state, unused, out_8886651028895104293);
}
void car_H_27(double *state, double *unused, double *out_8133823576555721211) {
  H_27(state, unused, out_8133823576555721211);
}
void car_h_29(double *state, double *unused, double *out_1347619720248911154) {
  h_29(state, unused, out_1347619720248911154);
}
void car_H_29(double *state, double *unused, double *out_5448828920440904116) {
  H_29(state, unused, out_5448828920440904116);
}
void car_h_28(double *state, double *unused, double *out_2108122273276517816) {
  h_28(state, unused, out_2108122273276517816);
}
void car_H_28(double *state, double *unused, double *out_7915516136199116926) {
  H_28(state, unused, out_7915516136199116926);
}
void car_h_31(double *state, double *unused, double *out_247528232980236298) {
  h_31(state, unused, out_247528232980236298);
}
void car_H_31(double *state, double *unused, double *out_5601639429339598989) {
  H_31(state, unused, out_5601639429339598989);
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
