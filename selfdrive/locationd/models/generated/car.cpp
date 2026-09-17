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
void err_fun(double *nom_x, double *delta_x, double *out_888231951720114761) {
   out_888231951720114761[0] = delta_x[0] + nom_x[0];
   out_888231951720114761[1] = delta_x[1] + nom_x[1];
   out_888231951720114761[2] = delta_x[2] + nom_x[2];
   out_888231951720114761[3] = delta_x[3] + nom_x[3];
   out_888231951720114761[4] = delta_x[4] + nom_x[4];
   out_888231951720114761[5] = delta_x[5] + nom_x[5];
   out_888231951720114761[6] = delta_x[6] + nom_x[6];
   out_888231951720114761[7] = delta_x[7] + nom_x[7];
   out_888231951720114761[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5071969062086154653) {
   out_5071969062086154653[0] = -nom_x[0] + true_x[0];
   out_5071969062086154653[1] = -nom_x[1] + true_x[1];
   out_5071969062086154653[2] = -nom_x[2] + true_x[2];
   out_5071969062086154653[3] = -nom_x[3] + true_x[3];
   out_5071969062086154653[4] = -nom_x[4] + true_x[4];
   out_5071969062086154653[5] = -nom_x[5] + true_x[5];
   out_5071969062086154653[6] = -nom_x[6] + true_x[6];
   out_5071969062086154653[7] = -nom_x[7] + true_x[7];
   out_5071969062086154653[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_275750450487295748) {
   out_275750450487295748[0] = 1.0;
   out_275750450487295748[1] = 0.0;
   out_275750450487295748[2] = 0.0;
   out_275750450487295748[3] = 0.0;
   out_275750450487295748[4] = 0.0;
   out_275750450487295748[5] = 0.0;
   out_275750450487295748[6] = 0.0;
   out_275750450487295748[7] = 0.0;
   out_275750450487295748[8] = 0.0;
   out_275750450487295748[9] = 0.0;
   out_275750450487295748[10] = 1.0;
   out_275750450487295748[11] = 0.0;
   out_275750450487295748[12] = 0.0;
   out_275750450487295748[13] = 0.0;
   out_275750450487295748[14] = 0.0;
   out_275750450487295748[15] = 0.0;
   out_275750450487295748[16] = 0.0;
   out_275750450487295748[17] = 0.0;
   out_275750450487295748[18] = 0.0;
   out_275750450487295748[19] = 0.0;
   out_275750450487295748[20] = 1.0;
   out_275750450487295748[21] = 0.0;
   out_275750450487295748[22] = 0.0;
   out_275750450487295748[23] = 0.0;
   out_275750450487295748[24] = 0.0;
   out_275750450487295748[25] = 0.0;
   out_275750450487295748[26] = 0.0;
   out_275750450487295748[27] = 0.0;
   out_275750450487295748[28] = 0.0;
   out_275750450487295748[29] = 0.0;
   out_275750450487295748[30] = 1.0;
   out_275750450487295748[31] = 0.0;
   out_275750450487295748[32] = 0.0;
   out_275750450487295748[33] = 0.0;
   out_275750450487295748[34] = 0.0;
   out_275750450487295748[35] = 0.0;
   out_275750450487295748[36] = 0.0;
   out_275750450487295748[37] = 0.0;
   out_275750450487295748[38] = 0.0;
   out_275750450487295748[39] = 0.0;
   out_275750450487295748[40] = 1.0;
   out_275750450487295748[41] = 0.0;
   out_275750450487295748[42] = 0.0;
   out_275750450487295748[43] = 0.0;
   out_275750450487295748[44] = 0.0;
   out_275750450487295748[45] = 0.0;
   out_275750450487295748[46] = 0.0;
   out_275750450487295748[47] = 0.0;
   out_275750450487295748[48] = 0.0;
   out_275750450487295748[49] = 0.0;
   out_275750450487295748[50] = 1.0;
   out_275750450487295748[51] = 0.0;
   out_275750450487295748[52] = 0.0;
   out_275750450487295748[53] = 0.0;
   out_275750450487295748[54] = 0.0;
   out_275750450487295748[55] = 0.0;
   out_275750450487295748[56] = 0.0;
   out_275750450487295748[57] = 0.0;
   out_275750450487295748[58] = 0.0;
   out_275750450487295748[59] = 0.0;
   out_275750450487295748[60] = 1.0;
   out_275750450487295748[61] = 0.0;
   out_275750450487295748[62] = 0.0;
   out_275750450487295748[63] = 0.0;
   out_275750450487295748[64] = 0.0;
   out_275750450487295748[65] = 0.0;
   out_275750450487295748[66] = 0.0;
   out_275750450487295748[67] = 0.0;
   out_275750450487295748[68] = 0.0;
   out_275750450487295748[69] = 0.0;
   out_275750450487295748[70] = 1.0;
   out_275750450487295748[71] = 0.0;
   out_275750450487295748[72] = 0.0;
   out_275750450487295748[73] = 0.0;
   out_275750450487295748[74] = 0.0;
   out_275750450487295748[75] = 0.0;
   out_275750450487295748[76] = 0.0;
   out_275750450487295748[77] = 0.0;
   out_275750450487295748[78] = 0.0;
   out_275750450487295748[79] = 0.0;
   out_275750450487295748[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8193553397271047053) {
   out_8193553397271047053[0] = state[0];
   out_8193553397271047053[1] = state[1];
   out_8193553397271047053[2] = state[2];
   out_8193553397271047053[3] = state[3];
   out_8193553397271047053[4] = state[4];
   out_8193553397271047053[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8193553397271047053[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8193553397271047053[7] = state[7];
   out_8193553397271047053[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8498803796068946841) {
   out_8498803796068946841[0] = 1;
   out_8498803796068946841[1] = 0;
   out_8498803796068946841[2] = 0;
   out_8498803796068946841[3] = 0;
   out_8498803796068946841[4] = 0;
   out_8498803796068946841[5] = 0;
   out_8498803796068946841[6] = 0;
   out_8498803796068946841[7] = 0;
   out_8498803796068946841[8] = 0;
   out_8498803796068946841[9] = 0;
   out_8498803796068946841[10] = 1;
   out_8498803796068946841[11] = 0;
   out_8498803796068946841[12] = 0;
   out_8498803796068946841[13] = 0;
   out_8498803796068946841[14] = 0;
   out_8498803796068946841[15] = 0;
   out_8498803796068946841[16] = 0;
   out_8498803796068946841[17] = 0;
   out_8498803796068946841[18] = 0;
   out_8498803796068946841[19] = 0;
   out_8498803796068946841[20] = 1;
   out_8498803796068946841[21] = 0;
   out_8498803796068946841[22] = 0;
   out_8498803796068946841[23] = 0;
   out_8498803796068946841[24] = 0;
   out_8498803796068946841[25] = 0;
   out_8498803796068946841[26] = 0;
   out_8498803796068946841[27] = 0;
   out_8498803796068946841[28] = 0;
   out_8498803796068946841[29] = 0;
   out_8498803796068946841[30] = 1;
   out_8498803796068946841[31] = 0;
   out_8498803796068946841[32] = 0;
   out_8498803796068946841[33] = 0;
   out_8498803796068946841[34] = 0;
   out_8498803796068946841[35] = 0;
   out_8498803796068946841[36] = 0;
   out_8498803796068946841[37] = 0;
   out_8498803796068946841[38] = 0;
   out_8498803796068946841[39] = 0;
   out_8498803796068946841[40] = 1;
   out_8498803796068946841[41] = 0;
   out_8498803796068946841[42] = 0;
   out_8498803796068946841[43] = 0;
   out_8498803796068946841[44] = 0;
   out_8498803796068946841[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8498803796068946841[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8498803796068946841[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8498803796068946841[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8498803796068946841[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8498803796068946841[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8498803796068946841[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8498803796068946841[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8498803796068946841[53] = -9.8100000000000005*dt;
   out_8498803796068946841[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8498803796068946841[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8498803796068946841[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8498803796068946841[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8498803796068946841[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8498803796068946841[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8498803796068946841[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8498803796068946841[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8498803796068946841[62] = 0;
   out_8498803796068946841[63] = 0;
   out_8498803796068946841[64] = 0;
   out_8498803796068946841[65] = 0;
   out_8498803796068946841[66] = 0;
   out_8498803796068946841[67] = 0;
   out_8498803796068946841[68] = 0;
   out_8498803796068946841[69] = 0;
   out_8498803796068946841[70] = 1;
   out_8498803796068946841[71] = 0;
   out_8498803796068946841[72] = 0;
   out_8498803796068946841[73] = 0;
   out_8498803796068946841[74] = 0;
   out_8498803796068946841[75] = 0;
   out_8498803796068946841[76] = 0;
   out_8498803796068946841[77] = 0;
   out_8498803796068946841[78] = 0;
   out_8498803796068946841[79] = 0;
   out_8498803796068946841[80] = 1;
}
void h_25(double *state, double *unused, double *out_333287890152809920) {
   out_333287890152809920[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6511660090495415162) {
   out_6511660090495415162[0] = 0;
   out_6511660090495415162[1] = 0;
   out_6511660090495415162[2] = 0;
   out_6511660090495415162[3] = 0;
   out_6511660090495415162[4] = 0;
   out_6511660090495415162[5] = 0;
   out_6511660090495415162[6] = 1;
   out_6511660090495415162[7] = 0;
   out_6511660090495415162[8] = 0;
}
void h_24(double *state, double *unused, double *out_7670200299047341739) {
   out_7670200299047341739[0] = state[4];
   out_7670200299047341739[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7356656699279110561) {
   out_7356656699279110561[0] = 0;
   out_7356656699279110561[1] = 0;
   out_7356656699279110561[2] = 0;
   out_7356656699279110561[3] = 0;
   out_7356656699279110561[4] = 1;
   out_7356656699279110561[5] = 0;
   out_7356656699279110561[6] = 0;
   out_7356656699279110561[7] = 0;
   out_7356656699279110561[8] = 0;
   out_7356656699279110561[9] = 0;
   out_7356656699279110561[10] = 0;
   out_7356656699279110561[11] = 0;
   out_7356656699279110561[12] = 0;
   out_7356656699279110561[13] = 0;
   out_7356656699279110561[14] = 1;
   out_7356656699279110561[15] = 0;
   out_7356656699279110561[16] = 0;
   out_7356656699279110561[17] = 0;
}
void h_30(double *state, double *unused, double *out_2235669891543854446) {
   out_2235669891543854446[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5018393641722519699) {
   out_5018393641722519699[0] = 0;
   out_5018393641722519699[1] = 0;
   out_5018393641722519699[2] = 0;
   out_5018393641722519699[3] = 0;
   out_5018393641722519699[4] = 1;
   out_5018393641722519699[5] = 0;
   out_5018393641722519699[6] = 0;
   out_5018393641722519699[7] = 0;
   out_5018393641722519699[8] = 0;
}
void h_26(double *state, double *unused, double *out_4915835473802170598) {
   out_4915835473802170598[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7168514154605727066) {
   out_7168514154605727066[0] = 0;
   out_7168514154605727066[1] = 0;
   out_7168514154605727066[2] = 0;
   out_7168514154605727066[3] = 0;
   out_7168514154605727066[4] = 0;
   out_7168514154605727066[5] = 0;
   out_7168514154605727066[6] = 0;
   out_7168514154605727066[7] = 1;
   out_7168514154605727066[8] = 0;
}
void h_27(double *state, double *unused, double *out_1514805784322995420) {
   out_1514805784322995420[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7193156953522944610) {
   out_7193156953522944610[0] = 0;
   out_7193156953522944610[1] = 0;
   out_7193156953522944610[2] = 0;
   out_7193156953522944610[3] = 1;
   out_7193156953522944610[4] = 0;
   out_7193156953522944610[5] = 0;
   out_7193156953522944610[6] = 0;
   out_7193156953522944610[7] = 0;
   out_7193156953522944610[8] = 0;
}
void h_29(double *state, double *unused, double *out_1789999846607501309) {
   out_1789999846607501309[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4508162297408127515) {
   out_4508162297408127515[0] = 0;
   out_4508162297408127515[1] = 1;
   out_4508162297408127515[2] = 0;
   out_4508162297408127515[3] = 0;
   out_4508162297408127515[4] = 0;
   out_4508162297408127515[5] = 0;
   out_4508162297408127515[6] = 0;
   out_4508162297408127515[7] = 0;
   out_4508162297408127515[8] = 0;
}
void h_28(double *state, double *unused, double *out_1089599536485702231) {
   out_1089599536485702231[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8856182759231893527) {
   out_8856182759231893527[0] = 1;
   out_8856182759231893527[1] = 0;
   out_8856182759231893527[2] = 0;
   out_8856182759231893527[3] = 0;
   out_8856182759231893527[4] = 0;
   out_8856182759231893527[5] = 0;
   out_8856182759231893527[6] = 0;
   out_8856182759231893527[7] = 0;
   out_8856182759231893527[8] = 0;
}
void h_31(double *state, double *unused, double *out_2036236090708967058) {
   out_2036236090708967058[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6542306052372375590) {
   out_6542306052372375590[0] = 0;
   out_6542306052372375590[1] = 0;
   out_6542306052372375590[2] = 0;
   out_6542306052372375590[3] = 0;
   out_6542306052372375590[4] = 0;
   out_6542306052372375590[5] = 0;
   out_6542306052372375590[6] = 0;
   out_6542306052372375590[7] = 0;
   out_6542306052372375590[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_888231951720114761) {
  err_fun(nom_x, delta_x, out_888231951720114761);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5071969062086154653) {
  inv_err_fun(nom_x, true_x, out_5071969062086154653);
}
void car_H_mod_fun(double *state, double *out_275750450487295748) {
  H_mod_fun(state, out_275750450487295748);
}
void car_f_fun(double *state, double dt, double *out_8193553397271047053) {
  f_fun(state,  dt, out_8193553397271047053);
}
void car_F_fun(double *state, double dt, double *out_8498803796068946841) {
  F_fun(state,  dt, out_8498803796068946841);
}
void car_h_25(double *state, double *unused, double *out_333287890152809920) {
  h_25(state, unused, out_333287890152809920);
}
void car_H_25(double *state, double *unused, double *out_6511660090495415162) {
  H_25(state, unused, out_6511660090495415162);
}
void car_h_24(double *state, double *unused, double *out_7670200299047341739) {
  h_24(state, unused, out_7670200299047341739);
}
void car_H_24(double *state, double *unused, double *out_7356656699279110561) {
  H_24(state, unused, out_7356656699279110561);
}
void car_h_30(double *state, double *unused, double *out_2235669891543854446) {
  h_30(state, unused, out_2235669891543854446);
}
void car_H_30(double *state, double *unused, double *out_5018393641722519699) {
  H_30(state, unused, out_5018393641722519699);
}
void car_h_26(double *state, double *unused, double *out_4915835473802170598) {
  h_26(state, unused, out_4915835473802170598);
}
void car_H_26(double *state, double *unused, double *out_7168514154605727066) {
  H_26(state, unused, out_7168514154605727066);
}
void car_h_27(double *state, double *unused, double *out_1514805784322995420) {
  h_27(state, unused, out_1514805784322995420);
}
void car_H_27(double *state, double *unused, double *out_7193156953522944610) {
  H_27(state, unused, out_7193156953522944610);
}
void car_h_29(double *state, double *unused, double *out_1789999846607501309) {
  h_29(state, unused, out_1789999846607501309);
}
void car_H_29(double *state, double *unused, double *out_4508162297408127515) {
  H_29(state, unused, out_4508162297408127515);
}
void car_h_28(double *state, double *unused, double *out_1089599536485702231) {
  h_28(state, unused, out_1089599536485702231);
}
void car_H_28(double *state, double *unused, double *out_8856182759231893527) {
  H_28(state, unused, out_8856182759231893527);
}
void car_h_31(double *state, double *unused, double *out_2036236090708967058) {
  h_31(state, unused, out_2036236090708967058);
}
void car_H_31(double *state, double *unused, double *out_6542306052372375590) {
  H_31(state, unused, out_6542306052372375590);
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
