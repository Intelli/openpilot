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
void err_fun(double *nom_x, double *delta_x, double *out_5677531195299710099) {
   out_5677531195299710099[0] = delta_x[0] + nom_x[0];
   out_5677531195299710099[1] = delta_x[1] + nom_x[1];
   out_5677531195299710099[2] = delta_x[2] + nom_x[2];
   out_5677531195299710099[3] = delta_x[3] + nom_x[3];
   out_5677531195299710099[4] = delta_x[4] + nom_x[4];
   out_5677531195299710099[5] = delta_x[5] + nom_x[5];
   out_5677531195299710099[6] = delta_x[6] + nom_x[6];
   out_5677531195299710099[7] = delta_x[7] + nom_x[7];
   out_5677531195299710099[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3240212805769737864) {
   out_3240212805769737864[0] = -nom_x[0] + true_x[0];
   out_3240212805769737864[1] = -nom_x[1] + true_x[1];
   out_3240212805769737864[2] = -nom_x[2] + true_x[2];
   out_3240212805769737864[3] = -nom_x[3] + true_x[3];
   out_3240212805769737864[4] = -nom_x[4] + true_x[4];
   out_3240212805769737864[5] = -nom_x[5] + true_x[5];
   out_3240212805769737864[6] = -nom_x[6] + true_x[6];
   out_3240212805769737864[7] = -nom_x[7] + true_x[7];
   out_3240212805769737864[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_201453769190803420) {
   out_201453769190803420[0] = 1.0;
   out_201453769190803420[1] = 0.0;
   out_201453769190803420[2] = 0.0;
   out_201453769190803420[3] = 0.0;
   out_201453769190803420[4] = 0.0;
   out_201453769190803420[5] = 0.0;
   out_201453769190803420[6] = 0.0;
   out_201453769190803420[7] = 0.0;
   out_201453769190803420[8] = 0.0;
   out_201453769190803420[9] = 0.0;
   out_201453769190803420[10] = 1.0;
   out_201453769190803420[11] = 0.0;
   out_201453769190803420[12] = 0.0;
   out_201453769190803420[13] = 0.0;
   out_201453769190803420[14] = 0.0;
   out_201453769190803420[15] = 0.0;
   out_201453769190803420[16] = 0.0;
   out_201453769190803420[17] = 0.0;
   out_201453769190803420[18] = 0.0;
   out_201453769190803420[19] = 0.0;
   out_201453769190803420[20] = 1.0;
   out_201453769190803420[21] = 0.0;
   out_201453769190803420[22] = 0.0;
   out_201453769190803420[23] = 0.0;
   out_201453769190803420[24] = 0.0;
   out_201453769190803420[25] = 0.0;
   out_201453769190803420[26] = 0.0;
   out_201453769190803420[27] = 0.0;
   out_201453769190803420[28] = 0.0;
   out_201453769190803420[29] = 0.0;
   out_201453769190803420[30] = 1.0;
   out_201453769190803420[31] = 0.0;
   out_201453769190803420[32] = 0.0;
   out_201453769190803420[33] = 0.0;
   out_201453769190803420[34] = 0.0;
   out_201453769190803420[35] = 0.0;
   out_201453769190803420[36] = 0.0;
   out_201453769190803420[37] = 0.0;
   out_201453769190803420[38] = 0.0;
   out_201453769190803420[39] = 0.0;
   out_201453769190803420[40] = 1.0;
   out_201453769190803420[41] = 0.0;
   out_201453769190803420[42] = 0.0;
   out_201453769190803420[43] = 0.0;
   out_201453769190803420[44] = 0.0;
   out_201453769190803420[45] = 0.0;
   out_201453769190803420[46] = 0.0;
   out_201453769190803420[47] = 0.0;
   out_201453769190803420[48] = 0.0;
   out_201453769190803420[49] = 0.0;
   out_201453769190803420[50] = 1.0;
   out_201453769190803420[51] = 0.0;
   out_201453769190803420[52] = 0.0;
   out_201453769190803420[53] = 0.0;
   out_201453769190803420[54] = 0.0;
   out_201453769190803420[55] = 0.0;
   out_201453769190803420[56] = 0.0;
   out_201453769190803420[57] = 0.0;
   out_201453769190803420[58] = 0.0;
   out_201453769190803420[59] = 0.0;
   out_201453769190803420[60] = 1.0;
   out_201453769190803420[61] = 0.0;
   out_201453769190803420[62] = 0.0;
   out_201453769190803420[63] = 0.0;
   out_201453769190803420[64] = 0.0;
   out_201453769190803420[65] = 0.0;
   out_201453769190803420[66] = 0.0;
   out_201453769190803420[67] = 0.0;
   out_201453769190803420[68] = 0.0;
   out_201453769190803420[69] = 0.0;
   out_201453769190803420[70] = 1.0;
   out_201453769190803420[71] = 0.0;
   out_201453769190803420[72] = 0.0;
   out_201453769190803420[73] = 0.0;
   out_201453769190803420[74] = 0.0;
   out_201453769190803420[75] = 0.0;
   out_201453769190803420[76] = 0.0;
   out_201453769190803420[77] = 0.0;
   out_201453769190803420[78] = 0.0;
   out_201453769190803420[79] = 0.0;
   out_201453769190803420[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8096296852446877645) {
   out_8096296852446877645[0] = state[0];
   out_8096296852446877645[1] = state[1];
   out_8096296852446877645[2] = state[2];
   out_8096296852446877645[3] = state[3];
   out_8096296852446877645[4] = state[4];
   out_8096296852446877645[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8096296852446877645[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8096296852446877645[7] = state[7];
   out_8096296852446877645[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3086345955946777782) {
   out_3086345955946777782[0] = 1;
   out_3086345955946777782[1] = 0;
   out_3086345955946777782[2] = 0;
   out_3086345955946777782[3] = 0;
   out_3086345955946777782[4] = 0;
   out_3086345955946777782[5] = 0;
   out_3086345955946777782[6] = 0;
   out_3086345955946777782[7] = 0;
   out_3086345955946777782[8] = 0;
   out_3086345955946777782[9] = 0;
   out_3086345955946777782[10] = 1;
   out_3086345955946777782[11] = 0;
   out_3086345955946777782[12] = 0;
   out_3086345955946777782[13] = 0;
   out_3086345955946777782[14] = 0;
   out_3086345955946777782[15] = 0;
   out_3086345955946777782[16] = 0;
   out_3086345955946777782[17] = 0;
   out_3086345955946777782[18] = 0;
   out_3086345955946777782[19] = 0;
   out_3086345955946777782[20] = 1;
   out_3086345955946777782[21] = 0;
   out_3086345955946777782[22] = 0;
   out_3086345955946777782[23] = 0;
   out_3086345955946777782[24] = 0;
   out_3086345955946777782[25] = 0;
   out_3086345955946777782[26] = 0;
   out_3086345955946777782[27] = 0;
   out_3086345955946777782[28] = 0;
   out_3086345955946777782[29] = 0;
   out_3086345955946777782[30] = 1;
   out_3086345955946777782[31] = 0;
   out_3086345955946777782[32] = 0;
   out_3086345955946777782[33] = 0;
   out_3086345955946777782[34] = 0;
   out_3086345955946777782[35] = 0;
   out_3086345955946777782[36] = 0;
   out_3086345955946777782[37] = 0;
   out_3086345955946777782[38] = 0;
   out_3086345955946777782[39] = 0;
   out_3086345955946777782[40] = 1;
   out_3086345955946777782[41] = 0;
   out_3086345955946777782[42] = 0;
   out_3086345955946777782[43] = 0;
   out_3086345955946777782[44] = 0;
   out_3086345955946777782[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3086345955946777782[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3086345955946777782[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3086345955946777782[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3086345955946777782[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3086345955946777782[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3086345955946777782[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3086345955946777782[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3086345955946777782[53] = -9.8100000000000005*dt;
   out_3086345955946777782[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3086345955946777782[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3086345955946777782[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3086345955946777782[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3086345955946777782[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3086345955946777782[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3086345955946777782[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3086345955946777782[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3086345955946777782[62] = 0;
   out_3086345955946777782[63] = 0;
   out_3086345955946777782[64] = 0;
   out_3086345955946777782[65] = 0;
   out_3086345955946777782[66] = 0;
   out_3086345955946777782[67] = 0;
   out_3086345955946777782[68] = 0;
   out_3086345955946777782[69] = 0;
   out_3086345955946777782[70] = 1;
   out_3086345955946777782[71] = 0;
   out_3086345955946777782[72] = 0;
   out_3086345955946777782[73] = 0;
   out_3086345955946777782[74] = 0;
   out_3086345955946777782[75] = 0;
   out_3086345955946777782[76] = 0;
   out_3086345955946777782[77] = 0;
   out_3086345955946777782[78] = 0;
   out_3086345955946777782[79] = 0;
   out_3086345955946777782[80] = 1;
}
void h_25(double *state, double *unused, double *out_5322718312140181517) {
   out_5322718312140181517[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1102885341001168200) {
   out_1102885341001168200[0] = 0;
   out_1102885341001168200[1] = 0;
   out_1102885341001168200[2] = 0;
   out_1102885341001168200[3] = 0;
   out_1102885341001168200[4] = 0;
   out_1102885341001168200[5] = 0;
   out_1102885341001168200[6] = 1;
   out_1102885341001168200[7] = 0;
   out_1102885341001168200[8] = 0;
}
void h_24(double *state, double *unused, double *out_5561456258811847026) {
   out_5561456258811847026[0] = state[4];
   out_5561456258811847026[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7282360017982618233) {
   out_7282360017982618233[0] = 0;
   out_7282360017982618233[1] = 0;
   out_7282360017982618233[2] = 0;
   out_7282360017982618233[3] = 0;
   out_7282360017982618233[4] = 1;
   out_7282360017982618233[5] = 0;
   out_7282360017982618233[6] = 0;
   out_7282360017982618233[7] = 0;
   out_7282360017982618233[8] = 0;
   out_7282360017982618233[9] = 0;
   out_7282360017982618233[10] = 0;
   out_7282360017982618233[11] = 0;
   out_7282360017982618233[12] = 0;
   out_7282360017982618233[13] = 0;
   out_7282360017982618233[14] = 1;
   out_7282360017982618233[15] = 0;
   out_7282360017982618233[16] = 0;
   out_7282360017982618233[17] = 0;
}
void h_30(double *state, double *unused, double *out_3173942369123558475) {
   out_3173942369123558475[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5813805000490448555) {
   out_5813805000490448555[0] = 0;
   out_5813805000490448555[1] = 0;
   out_5813805000490448555[2] = 0;
   out_5813805000490448555[3] = 0;
   out_5813805000490448555[4] = 1;
   out_5813805000490448555[5] = 0;
   out_5813805000490448555[6] = 0;
   out_5813805000490448555[7] = 0;
   out_5813805000490448555[8] = 0;
}
void h_26(double *state, double *unused, double *out_6449790181871015064) {
   out_6449790181871015064[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4844388659875224424) {
   out_4844388659875224424[0] = 0;
   out_4844388659875224424[1] = 0;
   out_4844388659875224424[2] = 0;
   out_4844388659875224424[3] = 0;
   out_4844388659875224424[4] = 0;
   out_4844388659875224424[5] = 0;
   out_4844388659875224424[6] = 0;
   out_4844388659875224424[7] = 1;
   out_4844388659875224424[8] = 0;
}
void h_27(double *state, double *unused, double *out_4379208459238519082) {
   out_4379208459238519082[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3639041688690023644) {
   out_3639041688690023644[0] = 0;
   out_3639041688690023644[1] = 0;
   out_3639041688690023644[2] = 0;
   out_3639041688690023644[3] = 1;
   out_3639041688690023644[4] = 0;
   out_3639041688690023644[5] = 0;
   out_3639041688690023644[6] = 0;
   out_3639041688690023644[7] = 0;
   out_3639041688690023644[8] = 0;
}
void h_29(double *state, double *unused, double *out_8016657987492541432) {
   out_8016657987492541432[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1925678961820472611) {
   out_1925678961820472611[0] = 0;
   out_1925678961820472611[1] = 1;
   out_1925678961820472611[2] = 0;
   out_1925678961820472611[3] = 0;
   out_1925678961820472611[4] = 0;
   out_1925678961820472611[5] = 0;
   out_1925678961820472611[6] = 0;
   out_1925678961820472611[7] = 0;
   out_1925678961820472611[8] = 0;
}
void h_28(double *state, double *unused, double *out_738701221414969764) {
   out_738701221414969764[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3156720055249057963) {
   out_3156720055249057963[0] = 1;
   out_3156720055249057963[1] = 0;
   out_3156720055249057963[2] = 0;
   out_3156720055249057963[3] = 0;
   out_3156720055249057963[4] = 0;
   out_3156720055249057963[5] = 0;
   out_3156720055249057963[6] = 0;
   out_3156720055249057963[7] = 0;
   out_3156720055249057963[8] = 0;
}
void h_31(double *state, double *unused, double *out_897658870706832452) {
   out_897658870706832452[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1072239379124207772) {
   out_1072239379124207772[0] = 0;
   out_1072239379124207772[1] = 0;
   out_1072239379124207772[2] = 0;
   out_1072239379124207772[3] = 0;
   out_1072239379124207772[4] = 0;
   out_1072239379124207772[5] = 0;
   out_1072239379124207772[6] = 0;
   out_1072239379124207772[7] = 0;
   out_1072239379124207772[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5677531195299710099) {
  err_fun(nom_x, delta_x, out_5677531195299710099);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3240212805769737864) {
  inv_err_fun(nom_x, true_x, out_3240212805769737864);
}
void car_H_mod_fun(double *state, double *out_201453769190803420) {
  H_mod_fun(state, out_201453769190803420);
}
void car_f_fun(double *state, double dt, double *out_8096296852446877645) {
  f_fun(state,  dt, out_8096296852446877645);
}
void car_F_fun(double *state, double dt, double *out_3086345955946777782) {
  F_fun(state,  dt, out_3086345955946777782);
}
void car_h_25(double *state, double *unused, double *out_5322718312140181517) {
  h_25(state, unused, out_5322718312140181517);
}
void car_H_25(double *state, double *unused, double *out_1102885341001168200) {
  H_25(state, unused, out_1102885341001168200);
}
void car_h_24(double *state, double *unused, double *out_5561456258811847026) {
  h_24(state, unused, out_5561456258811847026);
}
void car_H_24(double *state, double *unused, double *out_7282360017982618233) {
  H_24(state, unused, out_7282360017982618233);
}
void car_h_30(double *state, double *unused, double *out_3173942369123558475) {
  h_30(state, unused, out_3173942369123558475);
}
void car_H_30(double *state, double *unused, double *out_5813805000490448555) {
  H_30(state, unused, out_5813805000490448555);
}
void car_h_26(double *state, double *unused, double *out_6449790181871015064) {
  h_26(state, unused, out_6449790181871015064);
}
void car_H_26(double *state, double *unused, double *out_4844388659875224424) {
  H_26(state, unused, out_4844388659875224424);
}
void car_h_27(double *state, double *unused, double *out_4379208459238519082) {
  h_27(state, unused, out_4379208459238519082);
}
void car_H_27(double *state, double *unused, double *out_3639041688690023644) {
  H_27(state, unused, out_3639041688690023644);
}
void car_h_29(double *state, double *unused, double *out_8016657987492541432) {
  h_29(state, unused, out_8016657987492541432);
}
void car_H_29(double *state, double *unused, double *out_1925678961820472611) {
  H_29(state, unused, out_1925678961820472611);
}
void car_h_28(double *state, double *unused, double *out_738701221414969764) {
  h_28(state, unused, out_738701221414969764);
}
void car_H_28(double *state, double *unused, double *out_3156720055249057963) {
  H_28(state, unused, out_3156720055249057963);
}
void car_h_31(double *state, double *unused, double *out_897658870706832452) {
  h_31(state, unused, out_897658870706832452);
}
void car_H_31(double *state, double *unused, double *out_1072239379124207772) {
  H_31(state, unused, out_1072239379124207772);
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
