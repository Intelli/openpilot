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
void err_fun(double *nom_x, double *delta_x, double *out_5685634975312251926) {
   out_5685634975312251926[0] = delta_x[0] + nom_x[0];
   out_5685634975312251926[1] = delta_x[1] + nom_x[1];
   out_5685634975312251926[2] = delta_x[2] + nom_x[2];
   out_5685634975312251926[3] = delta_x[3] + nom_x[3];
   out_5685634975312251926[4] = delta_x[4] + nom_x[4];
   out_5685634975312251926[5] = delta_x[5] + nom_x[5];
   out_5685634975312251926[6] = delta_x[6] + nom_x[6];
   out_5685634975312251926[7] = delta_x[7] + nom_x[7];
   out_5685634975312251926[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1653700651811135323) {
   out_1653700651811135323[0] = -nom_x[0] + true_x[0];
   out_1653700651811135323[1] = -nom_x[1] + true_x[1];
   out_1653700651811135323[2] = -nom_x[2] + true_x[2];
   out_1653700651811135323[3] = -nom_x[3] + true_x[3];
   out_1653700651811135323[4] = -nom_x[4] + true_x[4];
   out_1653700651811135323[5] = -nom_x[5] + true_x[5];
   out_1653700651811135323[6] = -nom_x[6] + true_x[6];
   out_1653700651811135323[7] = -nom_x[7] + true_x[7];
   out_1653700651811135323[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_305387614319530969) {
   out_305387614319530969[0] = 1.0;
   out_305387614319530969[1] = 0.0;
   out_305387614319530969[2] = 0.0;
   out_305387614319530969[3] = 0.0;
   out_305387614319530969[4] = 0.0;
   out_305387614319530969[5] = 0.0;
   out_305387614319530969[6] = 0.0;
   out_305387614319530969[7] = 0.0;
   out_305387614319530969[8] = 0.0;
   out_305387614319530969[9] = 0.0;
   out_305387614319530969[10] = 1.0;
   out_305387614319530969[11] = 0.0;
   out_305387614319530969[12] = 0.0;
   out_305387614319530969[13] = 0.0;
   out_305387614319530969[14] = 0.0;
   out_305387614319530969[15] = 0.0;
   out_305387614319530969[16] = 0.0;
   out_305387614319530969[17] = 0.0;
   out_305387614319530969[18] = 0.0;
   out_305387614319530969[19] = 0.0;
   out_305387614319530969[20] = 1.0;
   out_305387614319530969[21] = 0.0;
   out_305387614319530969[22] = 0.0;
   out_305387614319530969[23] = 0.0;
   out_305387614319530969[24] = 0.0;
   out_305387614319530969[25] = 0.0;
   out_305387614319530969[26] = 0.0;
   out_305387614319530969[27] = 0.0;
   out_305387614319530969[28] = 0.0;
   out_305387614319530969[29] = 0.0;
   out_305387614319530969[30] = 1.0;
   out_305387614319530969[31] = 0.0;
   out_305387614319530969[32] = 0.0;
   out_305387614319530969[33] = 0.0;
   out_305387614319530969[34] = 0.0;
   out_305387614319530969[35] = 0.0;
   out_305387614319530969[36] = 0.0;
   out_305387614319530969[37] = 0.0;
   out_305387614319530969[38] = 0.0;
   out_305387614319530969[39] = 0.0;
   out_305387614319530969[40] = 1.0;
   out_305387614319530969[41] = 0.0;
   out_305387614319530969[42] = 0.0;
   out_305387614319530969[43] = 0.0;
   out_305387614319530969[44] = 0.0;
   out_305387614319530969[45] = 0.0;
   out_305387614319530969[46] = 0.0;
   out_305387614319530969[47] = 0.0;
   out_305387614319530969[48] = 0.0;
   out_305387614319530969[49] = 0.0;
   out_305387614319530969[50] = 1.0;
   out_305387614319530969[51] = 0.0;
   out_305387614319530969[52] = 0.0;
   out_305387614319530969[53] = 0.0;
   out_305387614319530969[54] = 0.0;
   out_305387614319530969[55] = 0.0;
   out_305387614319530969[56] = 0.0;
   out_305387614319530969[57] = 0.0;
   out_305387614319530969[58] = 0.0;
   out_305387614319530969[59] = 0.0;
   out_305387614319530969[60] = 1.0;
   out_305387614319530969[61] = 0.0;
   out_305387614319530969[62] = 0.0;
   out_305387614319530969[63] = 0.0;
   out_305387614319530969[64] = 0.0;
   out_305387614319530969[65] = 0.0;
   out_305387614319530969[66] = 0.0;
   out_305387614319530969[67] = 0.0;
   out_305387614319530969[68] = 0.0;
   out_305387614319530969[69] = 0.0;
   out_305387614319530969[70] = 1.0;
   out_305387614319530969[71] = 0.0;
   out_305387614319530969[72] = 0.0;
   out_305387614319530969[73] = 0.0;
   out_305387614319530969[74] = 0.0;
   out_305387614319530969[75] = 0.0;
   out_305387614319530969[76] = 0.0;
   out_305387614319530969[77] = 0.0;
   out_305387614319530969[78] = 0.0;
   out_305387614319530969[79] = 0.0;
   out_305387614319530969[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6390856393928483226) {
   out_6390856393928483226[0] = state[0];
   out_6390856393928483226[1] = state[1];
   out_6390856393928483226[2] = state[2];
   out_6390856393928483226[3] = state[3];
   out_6390856393928483226[4] = state[4];
   out_6390856393928483226[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6390856393928483226[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6390856393928483226[7] = state[7];
   out_6390856393928483226[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4160115342344962750) {
   out_4160115342344962750[0] = 1;
   out_4160115342344962750[1] = 0;
   out_4160115342344962750[2] = 0;
   out_4160115342344962750[3] = 0;
   out_4160115342344962750[4] = 0;
   out_4160115342344962750[5] = 0;
   out_4160115342344962750[6] = 0;
   out_4160115342344962750[7] = 0;
   out_4160115342344962750[8] = 0;
   out_4160115342344962750[9] = 0;
   out_4160115342344962750[10] = 1;
   out_4160115342344962750[11] = 0;
   out_4160115342344962750[12] = 0;
   out_4160115342344962750[13] = 0;
   out_4160115342344962750[14] = 0;
   out_4160115342344962750[15] = 0;
   out_4160115342344962750[16] = 0;
   out_4160115342344962750[17] = 0;
   out_4160115342344962750[18] = 0;
   out_4160115342344962750[19] = 0;
   out_4160115342344962750[20] = 1;
   out_4160115342344962750[21] = 0;
   out_4160115342344962750[22] = 0;
   out_4160115342344962750[23] = 0;
   out_4160115342344962750[24] = 0;
   out_4160115342344962750[25] = 0;
   out_4160115342344962750[26] = 0;
   out_4160115342344962750[27] = 0;
   out_4160115342344962750[28] = 0;
   out_4160115342344962750[29] = 0;
   out_4160115342344962750[30] = 1;
   out_4160115342344962750[31] = 0;
   out_4160115342344962750[32] = 0;
   out_4160115342344962750[33] = 0;
   out_4160115342344962750[34] = 0;
   out_4160115342344962750[35] = 0;
   out_4160115342344962750[36] = 0;
   out_4160115342344962750[37] = 0;
   out_4160115342344962750[38] = 0;
   out_4160115342344962750[39] = 0;
   out_4160115342344962750[40] = 1;
   out_4160115342344962750[41] = 0;
   out_4160115342344962750[42] = 0;
   out_4160115342344962750[43] = 0;
   out_4160115342344962750[44] = 0;
   out_4160115342344962750[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4160115342344962750[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4160115342344962750[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4160115342344962750[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4160115342344962750[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4160115342344962750[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4160115342344962750[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4160115342344962750[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4160115342344962750[53] = -9.8100000000000005*dt;
   out_4160115342344962750[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4160115342344962750[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4160115342344962750[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4160115342344962750[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4160115342344962750[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4160115342344962750[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4160115342344962750[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4160115342344962750[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4160115342344962750[62] = 0;
   out_4160115342344962750[63] = 0;
   out_4160115342344962750[64] = 0;
   out_4160115342344962750[65] = 0;
   out_4160115342344962750[66] = 0;
   out_4160115342344962750[67] = 0;
   out_4160115342344962750[68] = 0;
   out_4160115342344962750[69] = 0;
   out_4160115342344962750[70] = 1;
   out_4160115342344962750[71] = 0;
   out_4160115342344962750[72] = 0;
   out_4160115342344962750[73] = 0;
   out_4160115342344962750[74] = 0;
   out_4160115342344962750[75] = 0;
   out_4160115342344962750[76] = 0;
   out_4160115342344962750[77] = 0;
   out_4160115342344962750[78] = 0;
   out_4160115342344962750[79] = 0;
   out_4160115342344962750[80] = 1;
}
void h_25(double *state, double *unused, double *out_7280288212044461368) {
   out_7280288212044461368[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3217661024325834179) {
   out_3217661024325834179[0] = 0;
   out_3217661024325834179[1] = 0;
   out_3217661024325834179[2] = 0;
   out_3217661024325834179[3] = 0;
   out_3217661024325834179[4] = 0;
   out_3217661024325834179[5] = 0;
   out_3217661024325834179[6] = 1;
   out_3217661024325834179[7] = 0;
   out_3217661024325834179[8] = 0;
}
void h_24(double *state, double *unused, double *out_886623552878830077) {
   out_886623552878830077[0] = state[4];
   out_886623552878830077[1] = state[5];
}
void H_24(double *state, double *unused, double *out_340264574476488957) {
   out_340264574476488957[0] = 0;
   out_340264574476488957[1] = 0;
   out_340264574476488957[2] = 0;
   out_340264574476488957[3] = 0;
   out_340264574476488957[4] = 1;
   out_340264574476488957[5] = 0;
   out_340264574476488957[6] = 0;
   out_340264574476488957[7] = 0;
   out_340264574476488957[8] = 0;
   out_340264574476488957[9] = 0;
   out_340264574476488957[10] = 0;
   out_340264574476488957[11] = 0;
   out_340264574476488957[12] = 0;
   out_340264574476488957[13] = 0;
   out_340264574476488957[14] = 1;
   out_340264574476488957[15] = 0;
   out_340264574476488957[16] = 0;
   out_340264574476488957[17] = 0;
}
void h_30(double *state, double *unused, double *out_916694233742645507) {
   out_916694233742645507[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3699029317165782576) {
   out_3699029317165782576[0] = 0;
   out_3699029317165782576[1] = 0;
   out_3699029317165782576[2] = 0;
   out_3699029317165782576[3] = 0;
   out_3699029317165782576[4] = 1;
   out_3699029317165782576[5] = 0;
   out_3699029317165782576[6] = 0;
   out_3699029317165782576[7] = 0;
   out_3699029317165782576[8] = 0;
}
void h_26(double *state, double *unused, double *out_6061584296858293044) {
   out_6061584296858293044[0] = state[7];
}
void H_26(double *state, double *unused, double *out_86864945434966422) {
   out_86864945434966422[0] = 0;
   out_86864945434966422[1] = 0;
   out_86864945434966422[2] = 0;
   out_86864945434966422[3] = 0;
   out_86864945434966422[4] = 0;
   out_86864945434966422[5] = 0;
   out_86864945434966422[6] = 0;
   out_86864945434966422[7] = 1;
   out_86864945434966422[8] = 0;
}
void h_27(double *state, double *unused, double *out_4163693157872024469) {
   out_4163693157872024469[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1524266005365357665) {
   out_1524266005365357665[0] = 0;
   out_1524266005365357665[1] = 0;
   out_1524266005365357665[2] = 0;
   out_1524266005365357665[3] = 1;
   out_1524266005365357665[4] = 0;
   out_1524266005365357665[5] = 0;
   out_1524266005365357665[6] = 0;
   out_1524266005365357665[7] = 0;
   out_1524266005365357665[8] = 0;
}
void h_29(double *state, double *unused, double *out_6401778265083477962) {
   out_6401778265083477962[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4209260661480174760) {
   out_4209260661480174760[0] = 0;
   out_4209260661480174760[1] = 1;
   out_4209260661480174760[2] = 0;
   out_4209260661480174760[3] = 0;
   out_4209260661480174760[4] = 0;
   out_4209260661480174760[5] = 0;
   out_4209260661480174760[6] = 0;
   out_4209260661480174760[7] = 0;
   out_4209260661480174760[8] = 0;
}
void h_28(double *state, double *unused, double *out_9165366425532870114) {
   out_9165366425532870114[0] = state[0];
}
void H_28(double *state, double *unused, double *out_873138355589355814) {
   out_873138355589355814[0] = 1;
   out_873138355589355814[1] = 0;
   out_873138355589355814[2] = 0;
   out_873138355589355814[3] = 0;
   out_873138355589355814[4] = 0;
   out_873138355589355814[5] = 0;
   out_873138355589355814[6] = 0;
   out_873138355589355814[7] = 0;
   out_873138355589355814[8] = 0;
}
void h_31(double *state, double *unused, double *out_7123101543693332223) {
   out_7123101543693332223[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3859014226185983074) {
   out_3859014226185983074[0] = 0;
   out_3859014226185983074[1] = 0;
   out_3859014226185983074[2] = 0;
   out_3859014226185983074[3] = 0;
   out_3859014226185983074[4] = 0;
   out_3859014226185983074[5] = 0;
   out_3859014226185983074[6] = 0;
   out_3859014226185983074[7] = 0;
   out_3859014226185983074[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5685634975312251926) {
  err_fun(nom_x, delta_x, out_5685634975312251926);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1653700651811135323) {
  inv_err_fun(nom_x, true_x, out_1653700651811135323);
}
void car_H_mod_fun(double *state, double *out_305387614319530969) {
  H_mod_fun(state, out_305387614319530969);
}
void car_f_fun(double *state, double dt, double *out_6390856393928483226) {
  f_fun(state,  dt, out_6390856393928483226);
}
void car_F_fun(double *state, double dt, double *out_4160115342344962750) {
  F_fun(state,  dt, out_4160115342344962750);
}
void car_h_25(double *state, double *unused, double *out_7280288212044461368) {
  h_25(state, unused, out_7280288212044461368);
}
void car_H_25(double *state, double *unused, double *out_3217661024325834179) {
  H_25(state, unused, out_3217661024325834179);
}
void car_h_24(double *state, double *unused, double *out_886623552878830077) {
  h_24(state, unused, out_886623552878830077);
}
void car_H_24(double *state, double *unused, double *out_340264574476488957) {
  H_24(state, unused, out_340264574476488957);
}
void car_h_30(double *state, double *unused, double *out_916694233742645507) {
  h_30(state, unused, out_916694233742645507);
}
void car_H_30(double *state, double *unused, double *out_3699029317165782576) {
  H_30(state, unused, out_3699029317165782576);
}
void car_h_26(double *state, double *unused, double *out_6061584296858293044) {
  h_26(state, unused, out_6061584296858293044);
}
void car_H_26(double *state, double *unused, double *out_86864945434966422) {
  H_26(state, unused, out_86864945434966422);
}
void car_h_27(double *state, double *unused, double *out_4163693157872024469) {
  h_27(state, unused, out_4163693157872024469);
}
void car_H_27(double *state, double *unused, double *out_1524266005365357665) {
  H_27(state, unused, out_1524266005365357665);
}
void car_h_29(double *state, double *unused, double *out_6401778265083477962) {
  h_29(state, unused, out_6401778265083477962);
}
void car_H_29(double *state, double *unused, double *out_4209260661480174760) {
  H_29(state, unused, out_4209260661480174760);
}
void car_h_28(double *state, double *unused, double *out_9165366425532870114) {
  h_28(state, unused, out_9165366425532870114);
}
void car_H_28(double *state, double *unused, double *out_873138355589355814) {
  H_28(state, unused, out_873138355589355814);
}
void car_h_31(double *state, double *unused, double *out_7123101543693332223) {
  h_31(state, unused, out_7123101543693332223);
}
void car_H_31(double *state, double *unused, double *out_3859014226185983074) {
  H_31(state, unused, out_3859014226185983074);
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
