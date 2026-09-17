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
void err_fun(double *nom_x, double *delta_x, double *out_3898235742640831677) {
   out_3898235742640831677[0] = delta_x[0] + nom_x[0];
   out_3898235742640831677[1] = delta_x[1] + nom_x[1];
   out_3898235742640831677[2] = delta_x[2] + nom_x[2];
   out_3898235742640831677[3] = delta_x[3] + nom_x[3];
   out_3898235742640831677[4] = delta_x[4] + nom_x[4];
   out_3898235742640831677[5] = delta_x[5] + nom_x[5];
   out_3898235742640831677[6] = delta_x[6] + nom_x[6];
   out_3898235742640831677[7] = delta_x[7] + nom_x[7];
   out_3898235742640831677[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3493896062924369044) {
   out_3493896062924369044[0] = -nom_x[0] + true_x[0];
   out_3493896062924369044[1] = -nom_x[1] + true_x[1];
   out_3493896062924369044[2] = -nom_x[2] + true_x[2];
   out_3493896062924369044[3] = -nom_x[3] + true_x[3];
   out_3493896062924369044[4] = -nom_x[4] + true_x[4];
   out_3493896062924369044[5] = -nom_x[5] + true_x[5];
   out_3493896062924369044[6] = -nom_x[6] + true_x[6];
   out_3493896062924369044[7] = -nom_x[7] + true_x[7];
   out_3493896062924369044[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6155968468887758897) {
   out_6155968468887758897[0] = 1.0;
   out_6155968468887758897[1] = 0.0;
   out_6155968468887758897[2] = 0.0;
   out_6155968468887758897[3] = 0.0;
   out_6155968468887758897[4] = 0.0;
   out_6155968468887758897[5] = 0.0;
   out_6155968468887758897[6] = 0.0;
   out_6155968468887758897[7] = 0.0;
   out_6155968468887758897[8] = 0.0;
   out_6155968468887758897[9] = 0.0;
   out_6155968468887758897[10] = 1.0;
   out_6155968468887758897[11] = 0.0;
   out_6155968468887758897[12] = 0.0;
   out_6155968468887758897[13] = 0.0;
   out_6155968468887758897[14] = 0.0;
   out_6155968468887758897[15] = 0.0;
   out_6155968468887758897[16] = 0.0;
   out_6155968468887758897[17] = 0.0;
   out_6155968468887758897[18] = 0.0;
   out_6155968468887758897[19] = 0.0;
   out_6155968468887758897[20] = 1.0;
   out_6155968468887758897[21] = 0.0;
   out_6155968468887758897[22] = 0.0;
   out_6155968468887758897[23] = 0.0;
   out_6155968468887758897[24] = 0.0;
   out_6155968468887758897[25] = 0.0;
   out_6155968468887758897[26] = 0.0;
   out_6155968468887758897[27] = 0.0;
   out_6155968468887758897[28] = 0.0;
   out_6155968468887758897[29] = 0.0;
   out_6155968468887758897[30] = 1.0;
   out_6155968468887758897[31] = 0.0;
   out_6155968468887758897[32] = 0.0;
   out_6155968468887758897[33] = 0.0;
   out_6155968468887758897[34] = 0.0;
   out_6155968468887758897[35] = 0.0;
   out_6155968468887758897[36] = 0.0;
   out_6155968468887758897[37] = 0.0;
   out_6155968468887758897[38] = 0.0;
   out_6155968468887758897[39] = 0.0;
   out_6155968468887758897[40] = 1.0;
   out_6155968468887758897[41] = 0.0;
   out_6155968468887758897[42] = 0.0;
   out_6155968468887758897[43] = 0.0;
   out_6155968468887758897[44] = 0.0;
   out_6155968468887758897[45] = 0.0;
   out_6155968468887758897[46] = 0.0;
   out_6155968468887758897[47] = 0.0;
   out_6155968468887758897[48] = 0.0;
   out_6155968468887758897[49] = 0.0;
   out_6155968468887758897[50] = 1.0;
   out_6155968468887758897[51] = 0.0;
   out_6155968468887758897[52] = 0.0;
   out_6155968468887758897[53] = 0.0;
   out_6155968468887758897[54] = 0.0;
   out_6155968468887758897[55] = 0.0;
   out_6155968468887758897[56] = 0.0;
   out_6155968468887758897[57] = 0.0;
   out_6155968468887758897[58] = 0.0;
   out_6155968468887758897[59] = 0.0;
   out_6155968468887758897[60] = 1.0;
   out_6155968468887758897[61] = 0.0;
   out_6155968468887758897[62] = 0.0;
   out_6155968468887758897[63] = 0.0;
   out_6155968468887758897[64] = 0.0;
   out_6155968468887758897[65] = 0.0;
   out_6155968468887758897[66] = 0.0;
   out_6155968468887758897[67] = 0.0;
   out_6155968468887758897[68] = 0.0;
   out_6155968468887758897[69] = 0.0;
   out_6155968468887758897[70] = 1.0;
   out_6155968468887758897[71] = 0.0;
   out_6155968468887758897[72] = 0.0;
   out_6155968468887758897[73] = 0.0;
   out_6155968468887758897[74] = 0.0;
   out_6155968468887758897[75] = 0.0;
   out_6155968468887758897[76] = 0.0;
   out_6155968468887758897[77] = 0.0;
   out_6155968468887758897[78] = 0.0;
   out_6155968468887758897[79] = 0.0;
   out_6155968468887758897[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5924652974824119647) {
   out_5924652974824119647[0] = state[0];
   out_5924652974824119647[1] = state[1];
   out_5924652974824119647[2] = state[2];
   out_5924652974824119647[3] = state[3];
   out_5924652974824119647[4] = state[4];
   out_5924652974824119647[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5924652974824119647[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5924652974824119647[7] = state[7];
   out_5924652974824119647[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7778196774452902734) {
   out_7778196774452902734[0] = 1;
   out_7778196774452902734[1] = 0;
   out_7778196774452902734[2] = 0;
   out_7778196774452902734[3] = 0;
   out_7778196774452902734[4] = 0;
   out_7778196774452902734[5] = 0;
   out_7778196774452902734[6] = 0;
   out_7778196774452902734[7] = 0;
   out_7778196774452902734[8] = 0;
   out_7778196774452902734[9] = 0;
   out_7778196774452902734[10] = 1;
   out_7778196774452902734[11] = 0;
   out_7778196774452902734[12] = 0;
   out_7778196774452902734[13] = 0;
   out_7778196774452902734[14] = 0;
   out_7778196774452902734[15] = 0;
   out_7778196774452902734[16] = 0;
   out_7778196774452902734[17] = 0;
   out_7778196774452902734[18] = 0;
   out_7778196774452902734[19] = 0;
   out_7778196774452902734[20] = 1;
   out_7778196774452902734[21] = 0;
   out_7778196774452902734[22] = 0;
   out_7778196774452902734[23] = 0;
   out_7778196774452902734[24] = 0;
   out_7778196774452902734[25] = 0;
   out_7778196774452902734[26] = 0;
   out_7778196774452902734[27] = 0;
   out_7778196774452902734[28] = 0;
   out_7778196774452902734[29] = 0;
   out_7778196774452902734[30] = 1;
   out_7778196774452902734[31] = 0;
   out_7778196774452902734[32] = 0;
   out_7778196774452902734[33] = 0;
   out_7778196774452902734[34] = 0;
   out_7778196774452902734[35] = 0;
   out_7778196774452902734[36] = 0;
   out_7778196774452902734[37] = 0;
   out_7778196774452902734[38] = 0;
   out_7778196774452902734[39] = 0;
   out_7778196774452902734[40] = 1;
   out_7778196774452902734[41] = 0;
   out_7778196774452902734[42] = 0;
   out_7778196774452902734[43] = 0;
   out_7778196774452902734[44] = 0;
   out_7778196774452902734[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7778196774452902734[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7778196774452902734[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7778196774452902734[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7778196774452902734[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7778196774452902734[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7778196774452902734[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7778196774452902734[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7778196774452902734[53] = -9.8100000000000005*dt;
   out_7778196774452902734[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7778196774452902734[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7778196774452902734[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7778196774452902734[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7778196774452902734[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7778196774452902734[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7778196774452902734[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7778196774452902734[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7778196774452902734[62] = 0;
   out_7778196774452902734[63] = 0;
   out_7778196774452902734[64] = 0;
   out_7778196774452902734[65] = 0;
   out_7778196774452902734[66] = 0;
   out_7778196774452902734[67] = 0;
   out_7778196774452902734[68] = 0;
   out_7778196774452902734[69] = 0;
   out_7778196774452902734[70] = 1;
   out_7778196774452902734[71] = 0;
   out_7778196774452902734[72] = 0;
   out_7778196774452902734[73] = 0;
   out_7778196774452902734[74] = 0;
   out_7778196774452902734[75] = 0;
   out_7778196774452902734[76] = 0;
   out_7778196774452902734[77] = 0;
   out_7778196774452902734[78] = 0;
   out_7778196774452902734[79] = 0;
   out_7778196774452902734[80] = 1;
}
void h_25(double *state, double *unused, double *out_5529134141476677677) {
   out_5529134141476677677[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1252276643703094057) {
   out_1252276643703094057[0] = 0;
   out_1252276643703094057[1] = 0;
   out_1252276643703094057[2] = 0;
   out_1252276643703094057[3] = 0;
   out_1252276643703094057[4] = 0;
   out_1252276643703094057[5] = 0;
   out_1252276643703094057[6] = 1;
   out_1252276643703094057[7] = 0;
   out_1252276643703094057[8] = 0;
}
void h_24(double *state, double *unused, double *out_8362506630194486028) {
   out_8362506630194486028[0] = state[4];
   out_8362506630194486028[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1722734125746432781) {
   out_1722734125746432781[0] = 0;
   out_1722734125746432781[1] = 0;
   out_1722734125746432781[2] = 0;
   out_1722734125746432781[3] = 0;
   out_1722734125746432781[4] = 1;
   out_1722734125746432781[5] = 0;
   out_1722734125746432781[6] = 0;
   out_1722734125746432781[7] = 0;
   out_1722734125746432781[8] = 0;
   out_1722734125746432781[9] = 0;
   out_1722734125746432781[10] = 0;
   out_1722734125746432781[11] = 0;
   out_1722734125746432781[12] = 0;
   out_1722734125746432781[13] = 0;
   out_1722734125746432781[14] = 1;
   out_1722734125746432781[15] = 0;
   out_1722734125746432781[16] = 0;
   out_1722734125746432781[17] = 0;
}
void h_30(double *state, double *unused, double *out_637979898494456626) {
   out_637979898494456626[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5779972973830702255) {
   out_5779972973830702255[0] = 0;
   out_5779972973830702255[1] = 0;
   out_5779972973830702255[2] = 0;
   out_5779972973830702255[3] = 0;
   out_5779972973830702255[4] = 1;
   out_5779972973830702255[5] = 0;
   out_5779972973830702255[6] = 0;
   out_5779972973830702255[7] = 0;
   out_5779972973830702255[8] = 0;
}
void h_26(double *state, double *unused, double *out_5639653166155302271) {
   out_5639653166155302271[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4993779962577150281) {
   out_4993779962577150281[0] = 0;
   out_4993779962577150281[1] = 0;
   out_4993779962577150281[2] = 0;
   out_4993779962577150281[3] = 0;
   out_4993779962577150281[4] = 0;
   out_4993779962577150281[5] = 0;
   out_4993779962577150281[6] = 0;
   out_4993779962577150281[7] = 1;
   out_4993779962577150281[8] = 0;
}
void h_27(double *state, double *unused, double *out_6671158874772700471) {
   out_6671158874772700471[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3556378902646759038) {
   out_3556378902646759038[0] = 0;
   out_3556378902646759038[1] = 0;
   out_3556378902646759038[2] = 0;
   out_3556378902646759038[3] = 1;
   out_3556378902646759038[4] = 0;
   out_3556378902646759038[5] = 0;
   out_3556378902646759038[6] = 0;
   out_3556378902646759038[7] = 0;
   out_3556378902646759038[8] = 0;
}
void h_29(double *state, double *unused, double *out_4278487136318005944) {
   out_4278487136318005944[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5269741629516310071) {
   out_5269741629516310071[0] = 0;
   out_5269741629516310071[1] = 1;
   out_5269741629516310071[2] = 0;
   out_5269741629516310071[3] = 0;
   out_5269741629516310071[4] = 0;
   out_5269741629516310071[5] = 0;
   out_5269741629516310071[6] = 0;
   out_5269741629516310071[7] = 0;
   out_5269741629516310071[8] = 0;
}
void h_28(double *state, double *unused, double *out_1548838237130682557) {
   out_1548838237130682557[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3306111357950983820) {
   out_3306111357950983820[0] = 1;
   out_3306111357950983820[1] = 0;
   out_3306111357950983820[2] = 0;
   out_3306111357950983820[3] = 0;
   out_3306111357950983820[4] = 0;
   out_3306111357950983820[5] = 0;
   out_3306111357950983820[6] = 0;
   out_3306111357950983820[7] = 0;
   out_3306111357950983820[8] = 0;
}
void h_31(double *state, double *unused, double *out_114930689007722180) {
   out_114930689007722180[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1221630681826133629) {
   out_1221630681826133629[0] = 0;
   out_1221630681826133629[1] = 0;
   out_1221630681826133629[2] = 0;
   out_1221630681826133629[3] = 0;
   out_1221630681826133629[4] = 0;
   out_1221630681826133629[5] = 0;
   out_1221630681826133629[6] = 0;
   out_1221630681826133629[7] = 0;
   out_1221630681826133629[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3898235742640831677) {
  err_fun(nom_x, delta_x, out_3898235742640831677);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3493896062924369044) {
  inv_err_fun(nom_x, true_x, out_3493896062924369044);
}
void car_H_mod_fun(double *state, double *out_6155968468887758897) {
  H_mod_fun(state, out_6155968468887758897);
}
void car_f_fun(double *state, double dt, double *out_5924652974824119647) {
  f_fun(state,  dt, out_5924652974824119647);
}
void car_F_fun(double *state, double dt, double *out_7778196774452902734) {
  F_fun(state,  dt, out_7778196774452902734);
}
void car_h_25(double *state, double *unused, double *out_5529134141476677677) {
  h_25(state, unused, out_5529134141476677677);
}
void car_H_25(double *state, double *unused, double *out_1252276643703094057) {
  H_25(state, unused, out_1252276643703094057);
}
void car_h_24(double *state, double *unused, double *out_8362506630194486028) {
  h_24(state, unused, out_8362506630194486028);
}
void car_H_24(double *state, double *unused, double *out_1722734125746432781) {
  H_24(state, unused, out_1722734125746432781);
}
void car_h_30(double *state, double *unused, double *out_637979898494456626) {
  h_30(state, unused, out_637979898494456626);
}
void car_H_30(double *state, double *unused, double *out_5779972973830702255) {
  H_30(state, unused, out_5779972973830702255);
}
void car_h_26(double *state, double *unused, double *out_5639653166155302271) {
  h_26(state, unused, out_5639653166155302271);
}
void car_H_26(double *state, double *unused, double *out_4993779962577150281) {
  H_26(state, unused, out_4993779962577150281);
}
void car_h_27(double *state, double *unused, double *out_6671158874772700471) {
  h_27(state, unused, out_6671158874772700471);
}
void car_H_27(double *state, double *unused, double *out_3556378902646759038) {
  H_27(state, unused, out_3556378902646759038);
}
void car_h_29(double *state, double *unused, double *out_4278487136318005944) {
  h_29(state, unused, out_4278487136318005944);
}
void car_H_29(double *state, double *unused, double *out_5269741629516310071) {
  H_29(state, unused, out_5269741629516310071);
}
void car_h_28(double *state, double *unused, double *out_1548838237130682557) {
  h_28(state, unused, out_1548838237130682557);
}
void car_H_28(double *state, double *unused, double *out_3306111357950983820) {
  H_28(state, unused, out_3306111357950983820);
}
void car_h_31(double *state, double *unused, double *out_114930689007722180) {
  h_31(state, unused, out_114930689007722180);
}
void car_H_31(double *state, double *unused, double *out_1221630681826133629) {
  H_31(state, unused, out_1221630681826133629);
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
