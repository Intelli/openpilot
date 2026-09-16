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
void err_fun(double *nom_x, double *delta_x, double *out_8446512297607145956) {
   out_8446512297607145956[0] = delta_x[0] + nom_x[0];
   out_8446512297607145956[1] = delta_x[1] + nom_x[1];
   out_8446512297607145956[2] = delta_x[2] + nom_x[2];
   out_8446512297607145956[3] = delta_x[3] + nom_x[3];
   out_8446512297607145956[4] = delta_x[4] + nom_x[4];
   out_8446512297607145956[5] = delta_x[5] + nom_x[5];
   out_8446512297607145956[6] = delta_x[6] + nom_x[6];
   out_8446512297607145956[7] = delta_x[7] + nom_x[7];
   out_8446512297607145956[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9057774115653867931) {
   out_9057774115653867931[0] = -nom_x[0] + true_x[0];
   out_9057774115653867931[1] = -nom_x[1] + true_x[1];
   out_9057774115653867931[2] = -nom_x[2] + true_x[2];
   out_9057774115653867931[3] = -nom_x[3] + true_x[3];
   out_9057774115653867931[4] = -nom_x[4] + true_x[4];
   out_9057774115653867931[5] = -nom_x[5] + true_x[5];
   out_9057774115653867931[6] = -nom_x[6] + true_x[6];
   out_9057774115653867931[7] = -nom_x[7] + true_x[7];
   out_9057774115653867931[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3508449618144457651) {
   out_3508449618144457651[0] = 1.0;
   out_3508449618144457651[1] = 0.0;
   out_3508449618144457651[2] = 0.0;
   out_3508449618144457651[3] = 0.0;
   out_3508449618144457651[4] = 0.0;
   out_3508449618144457651[5] = 0.0;
   out_3508449618144457651[6] = 0.0;
   out_3508449618144457651[7] = 0.0;
   out_3508449618144457651[8] = 0.0;
   out_3508449618144457651[9] = 0.0;
   out_3508449618144457651[10] = 1.0;
   out_3508449618144457651[11] = 0.0;
   out_3508449618144457651[12] = 0.0;
   out_3508449618144457651[13] = 0.0;
   out_3508449618144457651[14] = 0.0;
   out_3508449618144457651[15] = 0.0;
   out_3508449618144457651[16] = 0.0;
   out_3508449618144457651[17] = 0.0;
   out_3508449618144457651[18] = 0.0;
   out_3508449618144457651[19] = 0.0;
   out_3508449618144457651[20] = 1.0;
   out_3508449618144457651[21] = 0.0;
   out_3508449618144457651[22] = 0.0;
   out_3508449618144457651[23] = 0.0;
   out_3508449618144457651[24] = 0.0;
   out_3508449618144457651[25] = 0.0;
   out_3508449618144457651[26] = 0.0;
   out_3508449618144457651[27] = 0.0;
   out_3508449618144457651[28] = 0.0;
   out_3508449618144457651[29] = 0.0;
   out_3508449618144457651[30] = 1.0;
   out_3508449618144457651[31] = 0.0;
   out_3508449618144457651[32] = 0.0;
   out_3508449618144457651[33] = 0.0;
   out_3508449618144457651[34] = 0.0;
   out_3508449618144457651[35] = 0.0;
   out_3508449618144457651[36] = 0.0;
   out_3508449618144457651[37] = 0.0;
   out_3508449618144457651[38] = 0.0;
   out_3508449618144457651[39] = 0.0;
   out_3508449618144457651[40] = 1.0;
   out_3508449618144457651[41] = 0.0;
   out_3508449618144457651[42] = 0.0;
   out_3508449618144457651[43] = 0.0;
   out_3508449618144457651[44] = 0.0;
   out_3508449618144457651[45] = 0.0;
   out_3508449618144457651[46] = 0.0;
   out_3508449618144457651[47] = 0.0;
   out_3508449618144457651[48] = 0.0;
   out_3508449618144457651[49] = 0.0;
   out_3508449618144457651[50] = 1.0;
   out_3508449618144457651[51] = 0.0;
   out_3508449618144457651[52] = 0.0;
   out_3508449618144457651[53] = 0.0;
   out_3508449618144457651[54] = 0.0;
   out_3508449618144457651[55] = 0.0;
   out_3508449618144457651[56] = 0.0;
   out_3508449618144457651[57] = 0.0;
   out_3508449618144457651[58] = 0.0;
   out_3508449618144457651[59] = 0.0;
   out_3508449618144457651[60] = 1.0;
   out_3508449618144457651[61] = 0.0;
   out_3508449618144457651[62] = 0.0;
   out_3508449618144457651[63] = 0.0;
   out_3508449618144457651[64] = 0.0;
   out_3508449618144457651[65] = 0.0;
   out_3508449618144457651[66] = 0.0;
   out_3508449618144457651[67] = 0.0;
   out_3508449618144457651[68] = 0.0;
   out_3508449618144457651[69] = 0.0;
   out_3508449618144457651[70] = 1.0;
   out_3508449618144457651[71] = 0.0;
   out_3508449618144457651[72] = 0.0;
   out_3508449618144457651[73] = 0.0;
   out_3508449618144457651[74] = 0.0;
   out_3508449618144457651[75] = 0.0;
   out_3508449618144457651[76] = 0.0;
   out_3508449618144457651[77] = 0.0;
   out_3508449618144457651[78] = 0.0;
   out_3508449618144457651[79] = 0.0;
   out_3508449618144457651[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8242977003035772527) {
   out_8242977003035772527[0] = state[0];
   out_8242977003035772527[1] = state[1];
   out_8242977003035772527[2] = state[2];
   out_8242977003035772527[3] = state[3];
   out_8242977003035772527[4] = state[4];
   out_8242977003035772527[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8242977003035772527[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8242977003035772527[7] = state[7];
   out_8242977003035772527[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5108010767557362242) {
   out_5108010767557362242[0] = 1;
   out_5108010767557362242[1] = 0;
   out_5108010767557362242[2] = 0;
   out_5108010767557362242[3] = 0;
   out_5108010767557362242[4] = 0;
   out_5108010767557362242[5] = 0;
   out_5108010767557362242[6] = 0;
   out_5108010767557362242[7] = 0;
   out_5108010767557362242[8] = 0;
   out_5108010767557362242[9] = 0;
   out_5108010767557362242[10] = 1;
   out_5108010767557362242[11] = 0;
   out_5108010767557362242[12] = 0;
   out_5108010767557362242[13] = 0;
   out_5108010767557362242[14] = 0;
   out_5108010767557362242[15] = 0;
   out_5108010767557362242[16] = 0;
   out_5108010767557362242[17] = 0;
   out_5108010767557362242[18] = 0;
   out_5108010767557362242[19] = 0;
   out_5108010767557362242[20] = 1;
   out_5108010767557362242[21] = 0;
   out_5108010767557362242[22] = 0;
   out_5108010767557362242[23] = 0;
   out_5108010767557362242[24] = 0;
   out_5108010767557362242[25] = 0;
   out_5108010767557362242[26] = 0;
   out_5108010767557362242[27] = 0;
   out_5108010767557362242[28] = 0;
   out_5108010767557362242[29] = 0;
   out_5108010767557362242[30] = 1;
   out_5108010767557362242[31] = 0;
   out_5108010767557362242[32] = 0;
   out_5108010767557362242[33] = 0;
   out_5108010767557362242[34] = 0;
   out_5108010767557362242[35] = 0;
   out_5108010767557362242[36] = 0;
   out_5108010767557362242[37] = 0;
   out_5108010767557362242[38] = 0;
   out_5108010767557362242[39] = 0;
   out_5108010767557362242[40] = 1;
   out_5108010767557362242[41] = 0;
   out_5108010767557362242[42] = 0;
   out_5108010767557362242[43] = 0;
   out_5108010767557362242[44] = 0;
   out_5108010767557362242[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5108010767557362242[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5108010767557362242[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5108010767557362242[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5108010767557362242[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5108010767557362242[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5108010767557362242[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5108010767557362242[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5108010767557362242[53] = -9.8100000000000005*dt;
   out_5108010767557362242[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5108010767557362242[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5108010767557362242[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5108010767557362242[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5108010767557362242[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5108010767557362242[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5108010767557362242[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5108010767557362242[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5108010767557362242[62] = 0;
   out_5108010767557362242[63] = 0;
   out_5108010767557362242[64] = 0;
   out_5108010767557362242[65] = 0;
   out_5108010767557362242[66] = 0;
   out_5108010767557362242[67] = 0;
   out_5108010767557362242[68] = 0;
   out_5108010767557362242[69] = 0;
   out_5108010767557362242[70] = 1;
   out_5108010767557362242[71] = 0;
   out_5108010767557362242[72] = 0;
   out_5108010767557362242[73] = 0;
   out_5108010767557362242[74] = 0;
   out_5108010767557362242[75] = 0;
   out_5108010767557362242[76] = 0;
   out_5108010767557362242[77] = 0;
   out_5108010767557362242[78] = 0;
   out_5108010767557362242[79] = 0;
   out_5108010767557362242[80] = 1;
}
void h_25(double *state, double *unused, double *out_2574374599262144846) {
   out_2574374599262144846[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4013784060344754363) {
   out_4013784060344754363[0] = 0;
   out_4013784060344754363[1] = 0;
   out_4013784060344754363[2] = 0;
   out_4013784060344754363[3] = 0;
   out_4013784060344754363[4] = 0;
   out_4013784060344754363[5] = 0;
   out_4013784060344754363[6] = 1;
   out_4013784060344754363[7] = 0;
   out_4013784060344754363[8] = 0;
}
void h_24(double *state, double *unused, double *out_5096625633322493085) {
   out_5096625633322493085[0] = state[4];
   out_5096625633322493085[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7857388206773279152) {
   out_7857388206773279152[0] = 0;
   out_7857388206773279152[1] = 0;
   out_7857388206773279152[2] = 0;
   out_7857388206773279152[3] = 0;
   out_7857388206773279152[4] = 1;
   out_7857388206773279152[5] = 0;
   out_7857388206773279152[6] = 0;
   out_7857388206773279152[7] = 0;
   out_7857388206773279152[8] = 0;
   out_7857388206773279152[9] = 0;
   out_7857388206773279152[10] = 0;
   out_7857388206773279152[11] = 0;
   out_7857388206773279152[12] = 0;
   out_7857388206773279152[13] = 0;
   out_7857388206773279152[14] = 1;
   out_7857388206773279152[15] = 0;
   out_7857388206773279152[16] = 0;
   out_7857388206773279152[17] = 0;
}
void h_30(double *state, double *unused, double *out_5082664103317425037) {
   out_5082664103317425037[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7516269671873180498) {
   out_7516269671873180498[0] = 0;
   out_7516269671873180498[1] = 0;
   out_7516269671873180498[2] = 0;
   out_7516269671873180498[3] = 0;
   out_7516269671873180498[4] = 1;
   out_7516269671873180498[5] = 0;
   out_7516269671873180498[6] = 0;
   out_7516269671873180498[7] = 0;
   out_7516269671873180498[8] = 0;
}
void h_26(double *state, double *unused, double *out_4479348218640947520) {
   out_4479348218640947520[0] = state[7];
}
void H_26(double *state, double *unused, double *out_272280741470698139) {
   out_272280741470698139[0] = 0;
   out_272280741470698139[1] = 0;
   out_272280741470698139[2] = 0;
   out_272280741470698139[3] = 0;
   out_272280741470698139[4] = 0;
   out_272280741470698139[5] = 0;
   out_272280741470698139[6] = 0;
   out_272280741470698139[7] = 1;
   out_272280741470698139[8] = 0;
}
void h_27(double *state, double *unused, double *out_3742118400338286583) {
   out_3742118400338286583[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8755711090035946207) {
   out_8755711090035946207[0] = 0;
   out_8755711090035946207[1] = 0;
   out_8755711090035946207[2] = 0;
   out_8755711090035946207[3] = 1;
   out_8755711090035946207[4] = 0;
   out_8755711090035946207[5] = 0;
   out_8755711090035946207[6] = 0;
   out_8755711090035946207[7] = 0;
   out_8755711090035946207[8] = 0;
}
void h_29(double *state, double *unused, double *out_6064748196652723149) {
   out_6064748196652723149[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7006038327558788314) {
   out_7006038327558788314[0] = 0;
   out_7006038327558788314[1] = 1;
   out_7006038327558788314[2] = 0;
   out_7006038327558788314[3] = 0;
   out_7006038327558788314[4] = 0;
   out_7006038327558788314[5] = 0;
   out_7006038327558788314[6] = 0;
   out_7006038327558788314[7] = 0;
   out_7006038327558788314[8] = 0;
}
void h_28(double *state, double *unused, double *out_1259554867322559062) {
   out_1259554867322559062[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6358306729081232728) {
   out_6358306729081232728[0] = 1;
   out_6358306729081232728[1] = 0;
   out_6358306729081232728[2] = 0;
   out_6358306729081232728[3] = 0;
   out_6358306729081232728[4] = 0;
   out_6358306729081232728[5] = 0;
   out_6358306729081232728[6] = 0;
   out_6358306729081232728[7] = 0;
   out_6358306729081232728[8] = 0;
}
void h_31(double *state, double *unused, double *out_6436058075690646498) {
   out_6436058075690646498[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4044430022221714791) {
   out_4044430022221714791[0] = 0;
   out_4044430022221714791[1] = 0;
   out_4044430022221714791[2] = 0;
   out_4044430022221714791[3] = 0;
   out_4044430022221714791[4] = 0;
   out_4044430022221714791[5] = 0;
   out_4044430022221714791[6] = 0;
   out_4044430022221714791[7] = 0;
   out_4044430022221714791[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8446512297607145956) {
  err_fun(nom_x, delta_x, out_8446512297607145956);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9057774115653867931) {
  inv_err_fun(nom_x, true_x, out_9057774115653867931);
}
void car_H_mod_fun(double *state, double *out_3508449618144457651) {
  H_mod_fun(state, out_3508449618144457651);
}
void car_f_fun(double *state, double dt, double *out_8242977003035772527) {
  f_fun(state,  dt, out_8242977003035772527);
}
void car_F_fun(double *state, double dt, double *out_5108010767557362242) {
  F_fun(state,  dt, out_5108010767557362242);
}
void car_h_25(double *state, double *unused, double *out_2574374599262144846) {
  h_25(state, unused, out_2574374599262144846);
}
void car_H_25(double *state, double *unused, double *out_4013784060344754363) {
  H_25(state, unused, out_4013784060344754363);
}
void car_h_24(double *state, double *unused, double *out_5096625633322493085) {
  h_24(state, unused, out_5096625633322493085);
}
void car_H_24(double *state, double *unused, double *out_7857388206773279152) {
  H_24(state, unused, out_7857388206773279152);
}
void car_h_30(double *state, double *unused, double *out_5082664103317425037) {
  h_30(state, unused, out_5082664103317425037);
}
void car_H_30(double *state, double *unused, double *out_7516269671873180498) {
  H_30(state, unused, out_7516269671873180498);
}
void car_h_26(double *state, double *unused, double *out_4479348218640947520) {
  h_26(state, unused, out_4479348218640947520);
}
void car_H_26(double *state, double *unused, double *out_272280741470698139) {
  H_26(state, unused, out_272280741470698139);
}
void car_h_27(double *state, double *unused, double *out_3742118400338286583) {
  h_27(state, unused, out_3742118400338286583);
}
void car_H_27(double *state, double *unused, double *out_8755711090035946207) {
  H_27(state, unused, out_8755711090035946207);
}
void car_h_29(double *state, double *unused, double *out_6064748196652723149) {
  h_29(state, unused, out_6064748196652723149);
}
void car_H_29(double *state, double *unused, double *out_7006038327558788314) {
  H_29(state, unused, out_7006038327558788314);
}
void car_h_28(double *state, double *unused, double *out_1259554867322559062) {
  h_28(state, unused, out_1259554867322559062);
}
void car_H_28(double *state, double *unused, double *out_6358306729081232728) {
  H_28(state, unused, out_6358306729081232728);
}
void car_h_31(double *state, double *unused, double *out_6436058075690646498) {
  h_31(state, unused, out_6436058075690646498);
}
void car_H_31(double *state, double *unused, double *out_4044430022221714791) {
  H_31(state, unused, out_4044430022221714791);
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
