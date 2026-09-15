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
void err_fun(double *nom_x, double *delta_x, double *out_8886897714237588908) {
   out_8886897714237588908[0] = delta_x[0] + nom_x[0];
   out_8886897714237588908[1] = delta_x[1] + nom_x[1];
   out_8886897714237588908[2] = delta_x[2] + nom_x[2];
   out_8886897714237588908[3] = delta_x[3] + nom_x[3];
   out_8886897714237588908[4] = delta_x[4] + nom_x[4];
   out_8886897714237588908[5] = delta_x[5] + nom_x[5];
   out_8886897714237588908[6] = delta_x[6] + nom_x[6];
   out_8886897714237588908[7] = delta_x[7] + nom_x[7];
   out_8886897714237588908[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5733609041839026521) {
   out_5733609041839026521[0] = -nom_x[0] + true_x[0];
   out_5733609041839026521[1] = -nom_x[1] + true_x[1];
   out_5733609041839026521[2] = -nom_x[2] + true_x[2];
   out_5733609041839026521[3] = -nom_x[3] + true_x[3];
   out_5733609041839026521[4] = -nom_x[4] + true_x[4];
   out_5733609041839026521[5] = -nom_x[5] + true_x[5];
   out_5733609041839026521[6] = -nom_x[6] + true_x[6];
   out_5733609041839026521[7] = -nom_x[7] + true_x[7];
   out_5733609041839026521[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3923317096320654469) {
   out_3923317096320654469[0] = 1.0;
   out_3923317096320654469[1] = 0.0;
   out_3923317096320654469[2] = 0.0;
   out_3923317096320654469[3] = 0.0;
   out_3923317096320654469[4] = 0.0;
   out_3923317096320654469[5] = 0.0;
   out_3923317096320654469[6] = 0.0;
   out_3923317096320654469[7] = 0.0;
   out_3923317096320654469[8] = 0.0;
   out_3923317096320654469[9] = 0.0;
   out_3923317096320654469[10] = 1.0;
   out_3923317096320654469[11] = 0.0;
   out_3923317096320654469[12] = 0.0;
   out_3923317096320654469[13] = 0.0;
   out_3923317096320654469[14] = 0.0;
   out_3923317096320654469[15] = 0.0;
   out_3923317096320654469[16] = 0.0;
   out_3923317096320654469[17] = 0.0;
   out_3923317096320654469[18] = 0.0;
   out_3923317096320654469[19] = 0.0;
   out_3923317096320654469[20] = 1.0;
   out_3923317096320654469[21] = 0.0;
   out_3923317096320654469[22] = 0.0;
   out_3923317096320654469[23] = 0.0;
   out_3923317096320654469[24] = 0.0;
   out_3923317096320654469[25] = 0.0;
   out_3923317096320654469[26] = 0.0;
   out_3923317096320654469[27] = 0.0;
   out_3923317096320654469[28] = 0.0;
   out_3923317096320654469[29] = 0.0;
   out_3923317096320654469[30] = 1.0;
   out_3923317096320654469[31] = 0.0;
   out_3923317096320654469[32] = 0.0;
   out_3923317096320654469[33] = 0.0;
   out_3923317096320654469[34] = 0.0;
   out_3923317096320654469[35] = 0.0;
   out_3923317096320654469[36] = 0.0;
   out_3923317096320654469[37] = 0.0;
   out_3923317096320654469[38] = 0.0;
   out_3923317096320654469[39] = 0.0;
   out_3923317096320654469[40] = 1.0;
   out_3923317096320654469[41] = 0.0;
   out_3923317096320654469[42] = 0.0;
   out_3923317096320654469[43] = 0.0;
   out_3923317096320654469[44] = 0.0;
   out_3923317096320654469[45] = 0.0;
   out_3923317096320654469[46] = 0.0;
   out_3923317096320654469[47] = 0.0;
   out_3923317096320654469[48] = 0.0;
   out_3923317096320654469[49] = 0.0;
   out_3923317096320654469[50] = 1.0;
   out_3923317096320654469[51] = 0.0;
   out_3923317096320654469[52] = 0.0;
   out_3923317096320654469[53] = 0.0;
   out_3923317096320654469[54] = 0.0;
   out_3923317096320654469[55] = 0.0;
   out_3923317096320654469[56] = 0.0;
   out_3923317096320654469[57] = 0.0;
   out_3923317096320654469[58] = 0.0;
   out_3923317096320654469[59] = 0.0;
   out_3923317096320654469[60] = 1.0;
   out_3923317096320654469[61] = 0.0;
   out_3923317096320654469[62] = 0.0;
   out_3923317096320654469[63] = 0.0;
   out_3923317096320654469[64] = 0.0;
   out_3923317096320654469[65] = 0.0;
   out_3923317096320654469[66] = 0.0;
   out_3923317096320654469[67] = 0.0;
   out_3923317096320654469[68] = 0.0;
   out_3923317096320654469[69] = 0.0;
   out_3923317096320654469[70] = 1.0;
   out_3923317096320654469[71] = 0.0;
   out_3923317096320654469[72] = 0.0;
   out_3923317096320654469[73] = 0.0;
   out_3923317096320654469[74] = 0.0;
   out_3923317096320654469[75] = 0.0;
   out_3923317096320654469[76] = 0.0;
   out_3923317096320654469[77] = 0.0;
   out_3923317096320654469[78] = 0.0;
   out_3923317096320654469[79] = 0.0;
   out_3923317096320654469[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_669091944002017197) {
   out_669091944002017197[0] = state[0];
   out_669091944002017197[1] = state[1];
   out_669091944002017197[2] = state[2];
   out_669091944002017197[3] = state[3];
   out_669091944002017197[4] = state[4];
   out_669091944002017197[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_669091944002017197[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_669091944002017197[7] = state[7];
   out_669091944002017197[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5797115532516380903) {
   out_5797115532516380903[0] = 1;
   out_5797115532516380903[1] = 0;
   out_5797115532516380903[2] = 0;
   out_5797115532516380903[3] = 0;
   out_5797115532516380903[4] = 0;
   out_5797115532516380903[5] = 0;
   out_5797115532516380903[6] = 0;
   out_5797115532516380903[7] = 0;
   out_5797115532516380903[8] = 0;
   out_5797115532516380903[9] = 0;
   out_5797115532516380903[10] = 1;
   out_5797115532516380903[11] = 0;
   out_5797115532516380903[12] = 0;
   out_5797115532516380903[13] = 0;
   out_5797115532516380903[14] = 0;
   out_5797115532516380903[15] = 0;
   out_5797115532516380903[16] = 0;
   out_5797115532516380903[17] = 0;
   out_5797115532516380903[18] = 0;
   out_5797115532516380903[19] = 0;
   out_5797115532516380903[20] = 1;
   out_5797115532516380903[21] = 0;
   out_5797115532516380903[22] = 0;
   out_5797115532516380903[23] = 0;
   out_5797115532516380903[24] = 0;
   out_5797115532516380903[25] = 0;
   out_5797115532516380903[26] = 0;
   out_5797115532516380903[27] = 0;
   out_5797115532516380903[28] = 0;
   out_5797115532516380903[29] = 0;
   out_5797115532516380903[30] = 1;
   out_5797115532516380903[31] = 0;
   out_5797115532516380903[32] = 0;
   out_5797115532516380903[33] = 0;
   out_5797115532516380903[34] = 0;
   out_5797115532516380903[35] = 0;
   out_5797115532516380903[36] = 0;
   out_5797115532516380903[37] = 0;
   out_5797115532516380903[38] = 0;
   out_5797115532516380903[39] = 0;
   out_5797115532516380903[40] = 1;
   out_5797115532516380903[41] = 0;
   out_5797115532516380903[42] = 0;
   out_5797115532516380903[43] = 0;
   out_5797115532516380903[44] = 0;
   out_5797115532516380903[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5797115532516380903[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5797115532516380903[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5797115532516380903[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5797115532516380903[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5797115532516380903[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5797115532516380903[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5797115532516380903[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5797115532516380903[53] = -9.8100000000000005*dt;
   out_5797115532516380903[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5797115532516380903[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5797115532516380903[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5797115532516380903[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5797115532516380903[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5797115532516380903[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5797115532516380903[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5797115532516380903[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5797115532516380903[62] = 0;
   out_5797115532516380903[63] = 0;
   out_5797115532516380903[64] = 0;
   out_5797115532516380903[65] = 0;
   out_5797115532516380903[66] = 0;
   out_5797115532516380903[67] = 0;
   out_5797115532516380903[68] = 0;
   out_5797115532516380903[69] = 0;
   out_5797115532516380903[70] = 1;
   out_5797115532516380903[71] = 0;
   out_5797115532516380903[72] = 0;
   out_5797115532516380903[73] = 0;
   out_5797115532516380903[74] = 0;
   out_5797115532516380903[75] = 0;
   out_5797115532516380903[76] = 0;
   out_5797115532516380903[77] = 0;
   out_5797115532516380903[78] = 0;
   out_5797115532516380903[79] = 0;
   out_5797115532516380903[80] = 1;
}
void h_25(double *state, double *unused, double *out_5196413492935956300) {
   out_5196413492935956300[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7446297746310146146) {
   out_7446297746310146146[0] = 0;
   out_7446297746310146146[1] = 0;
   out_7446297746310146146[2] = 0;
   out_7446297746310146146[3] = 0;
   out_7446297746310146146[4] = 0;
   out_7446297746310146146[5] = 0;
   out_7446297746310146146[6] = 1;
   out_7446297746310146146[7] = 0;
   out_7446297746310146146[8] = 0;
}
void h_24(double *state, double *unused, double *out_3869112794879626945) {
   out_3869112794879626945[0] = state[4];
   out_3869112794879626945[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3463974594912378248) {
   out_3463974594912378248[0] = 0;
   out_3463974594912378248[1] = 0;
   out_3463974594912378248[2] = 0;
   out_3463974594912378248[3] = 0;
   out_3463974594912378248[4] = 1;
   out_3463974594912378248[5] = 0;
   out_3463974594912378248[6] = 0;
   out_3463974594912378248[7] = 0;
   out_3463974594912378248[8] = 0;
   out_3463974594912378248[9] = 0;
   out_3463974594912378248[10] = 0;
   out_3463974594912378248[11] = 0;
   out_3463974594912378248[12] = 0;
   out_3463974594912378248[13] = 0;
   out_3463974594912378248[14] = 1;
   out_3463974594912378248[15] = 0;
   out_3463974594912378248[16] = 0;
   out_3463974594912378248[17] = 0;
}
void h_30(double *state, double *unused, double *out_6430828419944818181) {
   out_6430828419944818181[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4083755985907788715) {
   out_4083755985907788715[0] = 0;
   out_4083755985907788715[1] = 0;
   out_4083755985907788715[2] = 0;
   out_4083755985907788715[3] = 0;
   out_4083755985907788715[4] = 1;
   out_4083755985907788715[5] = 0;
   out_4083755985907788715[6] = 0;
   out_4083755985907788715[7] = 0;
   out_4083755985907788715[8] = 0;
}
void h_26(double *state, double *unused, double *out_6257930739770995479) {
   out_6257930739770995479[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3704794427436089922) {
   out_3704794427436089922[0] = 0;
   out_3704794427436089922[1] = 0;
   out_3704794427436089922[2] = 0;
   out_3704794427436089922[3] = 0;
   out_3704794427436089922[4] = 0;
   out_3704794427436089922[5] = 0;
   out_3704794427436089922[6] = 0;
   out_3704794427436089922[7] = 1;
   out_3704794427436089922[8] = 0;
}
void h_27(double *state, double *unused, double *out_4844673761129368663) {
   out_4844673761129368663[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6258519297708213626) {
   out_6258519297708213626[0] = 0;
   out_6258519297708213626[1] = 0;
   out_6258519297708213626[2] = 0;
   out_6258519297708213626[3] = 1;
   out_6258519297708213626[4] = 0;
   out_6258519297708213626[5] = 0;
   out_6258519297708213626[6] = 0;
   out_6258519297708213626[7] = 0;
   out_6258519297708213626[8] = 0;
}
void h_29(double *state, double *unused, double *out_2752985765080374306) {
   out_2752985765080374306[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3573524641593396531) {
   out_3573524641593396531[0] = 0;
   out_3573524641593396531[1] = 1;
   out_3573524641593396531[2] = 0;
   out_3573524641593396531[3] = 0;
   out_3573524641593396531[4] = 0;
   out_3573524641593396531[5] = 0;
   out_3573524641593396531[6] = 0;
   out_3573524641593396531[7] = 0;
   out_3573524641593396531[8] = 0;
}
void h_28(double *state, double *unused, double *out_3901163908227706228) {
   out_3901163908227706228[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8655923658662927105) {
   out_8655923658662927105[0] = 1;
   out_8655923658662927105[1] = 0;
   out_8655923658662927105[2] = 0;
   out_8655923658662927105[3] = 0;
   out_8655923658662927105[4] = 0;
   out_8655923658662927105[5] = 0;
   out_8655923658662927105[6] = 0;
   out_8655923658662927105[7] = 0;
   out_8655923658662927105[8] = 0;
}
void h_31(double *state, double *unused, double *out_3794449034785499332) {
   out_3794449034785499332[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7476943708187106574) {
   out_7476943708187106574[0] = 0;
   out_7476943708187106574[1] = 0;
   out_7476943708187106574[2] = 0;
   out_7476943708187106574[3] = 0;
   out_7476943708187106574[4] = 0;
   out_7476943708187106574[5] = 0;
   out_7476943708187106574[6] = 0;
   out_7476943708187106574[7] = 0;
   out_7476943708187106574[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8886897714237588908) {
  err_fun(nom_x, delta_x, out_8886897714237588908);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5733609041839026521) {
  inv_err_fun(nom_x, true_x, out_5733609041839026521);
}
void car_H_mod_fun(double *state, double *out_3923317096320654469) {
  H_mod_fun(state, out_3923317096320654469);
}
void car_f_fun(double *state, double dt, double *out_669091944002017197) {
  f_fun(state,  dt, out_669091944002017197);
}
void car_F_fun(double *state, double dt, double *out_5797115532516380903) {
  F_fun(state,  dt, out_5797115532516380903);
}
void car_h_25(double *state, double *unused, double *out_5196413492935956300) {
  h_25(state, unused, out_5196413492935956300);
}
void car_H_25(double *state, double *unused, double *out_7446297746310146146) {
  H_25(state, unused, out_7446297746310146146);
}
void car_h_24(double *state, double *unused, double *out_3869112794879626945) {
  h_24(state, unused, out_3869112794879626945);
}
void car_H_24(double *state, double *unused, double *out_3463974594912378248) {
  H_24(state, unused, out_3463974594912378248);
}
void car_h_30(double *state, double *unused, double *out_6430828419944818181) {
  h_30(state, unused, out_6430828419944818181);
}
void car_H_30(double *state, double *unused, double *out_4083755985907788715) {
  H_30(state, unused, out_4083755985907788715);
}
void car_h_26(double *state, double *unused, double *out_6257930739770995479) {
  h_26(state, unused, out_6257930739770995479);
}
void car_H_26(double *state, double *unused, double *out_3704794427436089922) {
  H_26(state, unused, out_3704794427436089922);
}
void car_h_27(double *state, double *unused, double *out_4844673761129368663) {
  h_27(state, unused, out_4844673761129368663);
}
void car_H_27(double *state, double *unused, double *out_6258519297708213626) {
  H_27(state, unused, out_6258519297708213626);
}
void car_h_29(double *state, double *unused, double *out_2752985765080374306) {
  h_29(state, unused, out_2752985765080374306);
}
void car_H_29(double *state, double *unused, double *out_3573524641593396531) {
  H_29(state, unused, out_3573524641593396531);
}
void car_h_28(double *state, double *unused, double *out_3901163908227706228) {
  h_28(state, unused, out_3901163908227706228);
}
void car_H_28(double *state, double *unused, double *out_8655923658662927105) {
  H_28(state, unused, out_8655923658662927105);
}
void car_h_31(double *state, double *unused, double *out_3794449034785499332) {
  h_31(state, unused, out_3794449034785499332);
}
void car_H_31(double *state, double *unused, double *out_7476943708187106574) {
  H_31(state, unused, out_7476943708187106574);
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
