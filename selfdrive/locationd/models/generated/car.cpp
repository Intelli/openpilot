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
void err_fun(double *nom_x, double *delta_x, double *out_3563114425621724245) {
   out_3563114425621724245[0] = delta_x[0] + nom_x[0];
   out_3563114425621724245[1] = delta_x[1] + nom_x[1];
   out_3563114425621724245[2] = delta_x[2] + nom_x[2];
   out_3563114425621724245[3] = delta_x[3] + nom_x[3];
   out_3563114425621724245[4] = delta_x[4] + nom_x[4];
   out_3563114425621724245[5] = delta_x[5] + nom_x[5];
   out_3563114425621724245[6] = delta_x[6] + nom_x[6];
   out_3563114425621724245[7] = delta_x[7] + nom_x[7];
   out_3563114425621724245[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7606356790606784638) {
   out_7606356790606784638[0] = -nom_x[0] + true_x[0];
   out_7606356790606784638[1] = -nom_x[1] + true_x[1];
   out_7606356790606784638[2] = -nom_x[2] + true_x[2];
   out_7606356790606784638[3] = -nom_x[3] + true_x[3];
   out_7606356790606784638[4] = -nom_x[4] + true_x[4];
   out_7606356790606784638[5] = -nom_x[5] + true_x[5];
   out_7606356790606784638[6] = -nom_x[6] + true_x[6];
   out_7606356790606784638[7] = -nom_x[7] + true_x[7];
   out_7606356790606784638[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_815759021034898572) {
   out_815759021034898572[0] = 1.0;
   out_815759021034898572[1] = 0.0;
   out_815759021034898572[2] = 0.0;
   out_815759021034898572[3] = 0.0;
   out_815759021034898572[4] = 0.0;
   out_815759021034898572[5] = 0.0;
   out_815759021034898572[6] = 0.0;
   out_815759021034898572[7] = 0.0;
   out_815759021034898572[8] = 0.0;
   out_815759021034898572[9] = 0.0;
   out_815759021034898572[10] = 1.0;
   out_815759021034898572[11] = 0.0;
   out_815759021034898572[12] = 0.0;
   out_815759021034898572[13] = 0.0;
   out_815759021034898572[14] = 0.0;
   out_815759021034898572[15] = 0.0;
   out_815759021034898572[16] = 0.0;
   out_815759021034898572[17] = 0.0;
   out_815759021034898572[18] = 0.0;
   out_815759021034898572[19] = 0.0;
   out_815759021034898572[20] = 1.0;
   out_815759021034898572[21] = 0.0;
   out_815759021034898572[22] = 0.0;
   out_815759021034898572[23] = 0.0;
   out_815759021034898572[24] = 0.0;
   out_815759021034898572[25] = 0.0;
   out_815759021034898572[26] = 0.0;
   out_815759021034898572[27] = 0.0;
   out_815759021034898572[28] = 0.0;
   out_815759021034898572[29] = 0.0;
   out_815759021034898572[30] = 1.0;
   out_815759021034898572[31] = 0.0;
   out_815759021034898572[32] = 0.0;
   out_815759021034898572[33] = 0.0;
   out_815759021034898572[34] = 0.0;
   out_815759021034898572[35] = 0.0;
   out_815759021034898572[36] = 0.0;
   out_815759021034898572[37] = 0.0;
   out_815759021034898572[38] = 0.0;
   out_815759021034898572[39] = 0.0;
   out_815759021034898572[40] = 1.0;
   out_815759021034898572[41] = 0.0;
   out_815759021034898572[42] = 0.0;
   out_815759021034898572[43] = 0.0;
   out_815759021034898572[44] = 0.0;
   out_815759021034898572[45] = 0.0;
   out_815759021034898572[46] = 0.0;
   out_815759021034898572[47] = 0.0;
   out_815759021034898572[48] = 0.0;
   out_815759021034898572[49] = 0.0;
   out_815759021034898572[50] = 1.0;
   out_815759021034898572[51] = 0.0;
   out_815759021034898572[52] = 0.0;
   out_815759021034898572[53] = 0.0;
   out_815759021034898572[54] = 0.0;
   out_815759021034898572[55] = 0.0;
   out_815759021034898572[56] = 0.0;
   out_815759021034898572[57] = 0.0;
   out_815759021034898572[58] = 0.0;
   out_815759021034898572[59] = 0.0;
   out_815759021034898572[60] = 1.0;
   out_815759021034898572[61] = 0.0;
   out_815759021034898572[62] = 0.0;
   out_815759021034898572[63] = 0.0;
   out_815759021034898572[64] = 0.0;
   out_815759021034898572[65] = 0.0;
   out_815759021034898572[66] = 0.0;
   out_815759021034898572[67] = 0.0;
   out_815759021034898572[68] = 0.0;
   out_815759021034898572[69] = 0.0;
   out_815759021034898572[70] = 1.0;
   out_815759021034898572[71] = 0.0;
   out_815759021034898572[72] = 0.0;
   out_815759021034898572[73] = 0.0;
   out_815759021034898572[74] = 0.0;
   out_815759021034898572[75] = 0.0;
   out_815759021034898572[76] = 0.0;
   out_815759021034898572[77] = 0.0;
   out_815759021034898572[78] = 0.0;
   out_815759021034898572[79] = 0.0;
   out_815759021034898572[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4397317462301668753) {
   out_4397317462301668753[0] = state[0];
   out_4397317462301668753[1] = state[1];
   out_4397317462301668753[2] = state[2];
   out_4397317462301668753[3] = state[3];
   out_4397317462301668753[4] = state[4];
   out_4397317462301668753[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4397317462301668753[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4397317462301668753[7] = state[7];
   out_4397317462301668753[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7256568882913831170) {
   out_7256568882913831170[0] = 1;
   out_7256568882913831170[1] = 0;
   out_7256568882913831170[2] = 0;
   out_7256568882913831170[3] = 0;
   out_7256568882913831170[4] = 0;
   out_7256568882913831170[5] = 0;
   out_7256568882913831170[6] = 0;
   out_7256568882913831170[7] = 0;
   out_7256568882913831170[8] = 0;
   out_7256568882913831170[9] = 0;
   out_7256568882913831170[10] = 1;
   out_7256568882913831170[11] = 0;
   out_7256568882913831170[12] = 0;
   out_7256568882913831170[13] = 0;
   out_7256568882913831170[14] = 0;
   out_7256568882913831170[15] = 0;
   out_7256568882913831170[16] = 0;
   out_7256568882913831170[17] = 0;
   out_7256568882913831170[18] = 0;
   out_7256568882913831170[19] = 0;
   out_7256568882913831170[20] = 1;
   out_7256568882913831170[21] = 0;
   out_7256568882913831170[22] = 0;
   out_7256568882913831170[23] = 0;
   out_7256568882913831170[24] = 0;
   out_7256568882913831170[25] = 0;
   out_7256568882913831170[26] = 0;
   out_7256568882913831170[27] = 0;
   out_7256568882913831170[28] = 0;
   out_7256568882913831170[29] = 0;
   out_7256568882913831170[30] = 1;
   out_7256568882913831170[31] = 0;
   out_7256568882913831170[32] = 0;
   out_7256568882913831170[33] = 0;
   out_7256568882913831170[34] = 0;
   out_7256568882913831170[35] = 0;
   out_7256568882913831170[36] = 0;
   out_7256568882913831170[37] = 0;
   out_7256568882913831170[38] = 0;
   out_7256568882913831170[39] = 0;
   out_7256568882913831170[40] = 1;
   out_7256568882913831170[41] = 0;
   out_7256568882913831170[42] = 0;
   out_7256568882913831170[43] = 0;
   out_7256568882913831170[44] = 0;
   out_7256568882913831170[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7256568882913831170[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7256568882913831170[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7256568882913831170[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7256568882913831170[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7256568882913831170[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7256568882913831170[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7256568882913831170[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7256568882913831170[53] = -9.8100000000000005*dt;
   out_7256568882913831170[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7256568882913831170[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7256568882913831170[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7256568882913831170[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7256568882913831170[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7256568882913831170[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7256568882913831170[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7256568882913831170[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7256568882913831170[62] = 0;
   out_7256568882913831170[63] = 0;
   out_7256568882913831170[64] = 0;
   out_7256568882913831170[65] = 0;
   out_7256568882913831170[66] = 0;
   out_7256568882913831170[67] = 0;
   out_7256568882913831170[68] = 0;
   out_7256568882913831170[69] = 0;
   out_7256568882913831170[70] = 1;
   out_7256568882913831170[71] = 0;
   out_7256568882913831170[72] = 0;
   out_7256568882913831170[73] = 0;
   out_7256568882913831170[74] = 0;
   out_7256568882913831170[75] = 0;
   out_7256568882913831170[76] = 0;
   out_7256568882913831170[77] = 0;
   out_7256568882913831170[78] = 0;
   out_7256568882913831170[79] = 0;
   out_7256568882913831170[80] = 1;
}
void h_25(double *state, double *unused, double *out_1332281256568723173) {
   out_1332281256568723173[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4338739671024390249) {
   out_4338739671024390249[0] = 0;
   out_4338739671024390249[1] = 0;
   out_4338739671024390249[2] = 0;
   out_4338739671024390249[3] = 0;
   out_4338739671024390249[4] = 0;
   out_4338739671024390249[5] = 0;
   out_4338739671024390249[6] = 1;
   out_4338739671024390249[7] = 0;
   out_4338739671024390249[8] = 0;
}
void h_24(double *state, double *unused, double *out_162131755279869977) {
   out_162131755279869977[0] = state[4];
   out_162131755279869977[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6564447455003258811) {
   out_6564447455003258811[0] = 0;
   out_6564447455003258811[1] = 0;
   out_6564447455003258811[2] = 0;
   out_6564447455003258811[3] = 0;
   out_6564447455003258811[4] = 1;
   out_6564447455003258811[5] = 0;
   out_6564447455003258811[6] = 0;
   out_6564447455003258811[7] = 0;
   out_6564447455003258811[8] = 0;
   out_6564447455003258811[9] = 0;
   out_6564447455003258811[10] = 0;
   out_6564447455003258811[11] = 0;
   out_6564447455003258811[12] = 0;
   out_6564447455003258811[13] = 0;
   out_6564447455003258811[14] = 1;
   out_6564447455003258811[15] = 0;
   out_6564447455003258811[16] = 0;
   out_6564447455003258811[17] = 0;
}
void h_30(double *state, double *unused, double *out_2305168271685299177) {
   out_2305168271685299177[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7191314061193544612) {
   out_7191314061193544612[0] = 0;
   out_7191314061193544612[1] = 0;
   out_7191314061193544612[2] = 0;
   out_7191314061193544612[3] = 0;
   out_7191314061193544612[4] = 1;
   out_7191314061193544612[5] = 0;
   out_7191314061193544612[6] = 0;
   out_7191314061193544612[7] = 0;
   out_7191314061193544612[8] = 0;
}
void h_26(double *state, double *unused, double *out_1323084178350001065) {
   out_1323084178350001065[0] = state[7];
}
void H_26(double *state, double *unused, double *out_597236352150334025) {
   out_597236352150334025[0] = 0;
   out_597236352150334025[1] = 0;
   out_597236352150334025[2] = 0;
   out_597236352150334025[3] = 0;
   out_597236352150334025[4] = 0;
   out_597236352150334025[5] = 0;
   out_597236352150334025[6] = 0;
   out_597236352150334025[7] = 1;
   out_597236352150334025[8] = 0;
}
void h_27(double *state, double *unused, double *out_3669392011092122472) {
   out_3669392011092122472[0] = state[3];
}
void H_27(double *state, double *unused, double *out_9080666700715582093) {
   out_9080666700715582093[0] = 0;
   out_9080666700715582093[1] = 0;
   out_9080666700715582093[2] = 0;
   out_9080666700715582093[3] = 1;
   out_9080666700715582093[4] = 0;
   out_9080666700715582093[5] = 0;
   out_9080666700715582093[6] = 0;
   out_9080666700715582093[7] = 0;
   out_9080666700715582093[8] = 0;
}
void h_29(double *state, double *unused, double *out_4093873245728549969) {
   out_4093873245728549969[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6681082716879152428) {
   out_6681082716879152428[0] = 0;
   out_6681082716879152428[1] = 1;
   out_6681082716879152428[2] = 0;
   out_6681082716879152428[3] = 0;
   out_6681082716879152428[4] = 0;
   out_6681082716879152428[5] = 0;
   out_6681082716879152428[6] = 0;
   out_6681082716879152428[7] = 0;
   out_6681082716879152428[8] = 0;
}
void h_28(double *state, double *unused, double *out_8735809529810465195) {
   out_8735809529810465195[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6683262339760868614) {
   out_6683262339760868614[0] = 1;
   out_6683262339760868614[1] = 0;
   out_6683262339760868614[2] = 0;
   out_6683262339760868614[3] = 0;
   out_6683262339760868614[4] = 0;
   out_6683262339760868614[5] = 0;
   out_6683262339760868614[6] = 0;
   out_6683262339760868614[7] = 0;
   out_6683262339760868614[8] = 0;
}
void h_31(double *state, double *unused, double *out_1607475318853229062) {
   out_1607475318853229062[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4369385632901350677) {
   out_4369385632901350677[0] = 0;
   out_4369385632901350677[1] = 0;
   out_4369385632901350677[2] = 0;
   out_4369385632901350677[3] = 0;
   out_4369385632901350677[4] = 0;
   out_4369385632901350677[5] = 0;
   out_4369385632901350677[6] = 0;
   out_4369385632901350677[7] = 0;
   out_4369385632901350677[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3563114425621724245) {
  err_fun(nom_x, delta_x, out_3563114425621724245);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7606356790606784638) {
  inv_err_fun(nom_x, true_x, out_7606356790606784638);
}
void car_H_mod_fun(double *state, double *out_815759021034898572) {
  H_mod_fun(state, out_815759021034898572);
}
void car_f_fun(double *state, double dt, double *out_4397317462301668753) {
  f_fun(state,  dt, out_4397317462301668753);
}
void car_F_fun(double *state, double dt, double *out_7256568882913831170) {
  F_fun(state,  dt, out_7256568882913831170);
}
void car_h_25(double *state, double *unused, double *out_1332281256568723173) {
  h_25(state, unused, out_1332281256568723173);
}
void car_H_25(double *state, double *unused, double *out_4338739671024390249) {
  H_25(state, unused, out_4338739671024390249);
}
void car_h_24(double *state, double *unused, double *out_162131755279869977) {
  h_24(state, unused, out_162131755279869977);
}
void car_H_24(double *state, double *unused, double *out_6564447455003258811) {
  H_24(state, unused, out_6564447455003258811);
}
void car_h_30(double *state, double *unused, double *out_2305168271685299177) {
  h_30(state, unused, out_2305168271685299177);
}
void car_H_30(double *state, double *unused, double *out_7191314061193544612) {
  H_30(state, unused, out_7191314061193544612);
}
void car_h_26(double *state, double *unused, double *out_1323084178350001065) {
  h_26(state, unused, out_1323084178350001065);
}
void car_H_26(double *state, double *unused, double *out_597236352150334025) {
  H_26(state, unused, out_597236352150334025);
}
void car_h_27(double *state, double *unused, double *out_3669392011092122472) {
  h_27(state, unused, out_3669392011092122472);
}
void car_H_27(double *state, double *unused, double *out_9080666700715582093) {
  H_27(state, unused, out_9080666700715582093);
}
void car_h_29(double *state, double *unused, double *out_4093873245728549969) {
  h_29(state, unused, out_4093873245728549969);
}
void car_H_29(double *state, double *unused, double *out_6681082716879152428) {
  H_29(state, unused, out_6681082716879152428);
}
void car_h_28(double *state, double *unused, double *out_8735809529810465195) {
  h_28(state, unused, out_8735809529810465195);
}
void car_H_28(double *state, double *unused, double *out_6683262339760868614) {
  H_28(state, unused, out_6683262339760868614);
}
void car_h_31(double *state, double *unused, double *out_1607475318853229062) {
  h_31(state, unused, out_1607475318853229062);
}
void car_H_31(double *state, double *unused, double *out_4369385632901350677) {
  H_31(state, unused, out_4369385632901350677);
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
