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
void err_fun(double *nom_x, double *delta_x, double *out_4669638409443648641) {
   out_4669638409443648641[0] = delta_x[0] + nom_x[0];
   out_4669638409443648641[1] = delta_x[1] + nom_x[1];
   out_4669638409443648641[2] = delta_x[2] + nom_x[2];
   out_4669638409443648641[3] = delta_x[3] + nom_x[3];
   out_4669638409443648641[4] = delta_x[4] + nom_x[4];
   out_4669638409443648641[5] = delta_x[5] + nom_x[5];
   out_4669638409443648641[6] = delta_x[6] + nom_x[6];
   out_4669638409443648641[7] = delta_x[7] + nom_x[7];
   out_4669638409443648641[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8859452741513286810) {
   out_8859452741513286810[0] = -nom_x[0] + true_x[0];
   out_8859452741513286810[1] = -nom_x[1] + true_x[1];
   out_8859452741513286810[2] = -nom_x[2] + true_x[2];
   out_8859452741513286810[3] = -nom_x[3] + true_x[3];
   out_8859452741513286810[4] = -nom_x[4] + true_x[4];
   out_8859452741513286810[5] = -nom_x[5] + true_x[5];
   out_8859452741513286810[6] = -nom_x[6] + true_x[6];
   out_8859452741513286810[7] = -nom_x[7] + true_x[7];
   out_8859452741513286810[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6131259255263184331) {
   out_6131259255263184331[0] = 1.0;
   out_6131259255263184331[1] = 0.0;
   out_6131259255263184331[2] = 0.0;
   out_6131259255263184331[3] = 0.0;
   out_6131259255263184331[4] = 0.0;
   out_6131259255263184331[5] = 0.0;
   out_6131259255263184331[6] = 0.0;
   out_6131259255263184331[7] = 0.0;
   out_6131259255263184331[8] = 0.0;
   out_6131259255263184331[9] = 0.0;
   out_6131259255263184331[10] = 1.0;
   out_6131259255263184331[11] = 0.0;
   out_6131259255263184331[12] = 0.0;
   out_6131259255263184331[13] = 0.0;
   out_6131259255263184331[14] = 0.0;
   out_6131259255263184331[15] = 0.0;
   out_6131259255263184331[16] = 0.0;
   out_6131259255263184331[17] = 0.0;
   out_6131259255263184331[18] = 0.0;
   out_6131259255263184331[19] = 0.0;
   out_6131259255263184331[20] = 1.0;
   out_6131259255263184331[21] = 0.0;
   out_6131259255263184331[22] = 0.0;
   out_6131259255263184331[23] = 0.0;
   out_6131259255263184331[24] = 0.0;
   out_6131259255263184331[25] = 0.0;
   out_6131259255263184331[26] = 0.0;
   out_6131259255263184331[27] = 0.0;
   out_6131259255263184331[28] = 0.0;
   out_6131259255263184331[29] = 0.0;
   out_6131259255263184331[30] = 1.0;
   out_6131259255263184331[31] = 0.0;
   out_6131259255263184331[32] = 0.0;
   out_6131259255263184331[33] = 0.0;
   out_6131259255263184331[34] = 0.0;
   out_6131259255263184331[35] = 0.0;
   out_6131259255263184331[36] = 0.0;
   out_6131259255263184331[37] = 0.0;
   out_6131259255263184331[38] = 0.0;
   out_6131259255263184331[39] = 0.0;
   out_6131259255263184331[40] = 1.0;
   out_6131259255263184331[41] = 0.0;
   out_6131259255263184331[42] = 0.0;
   out_6131259255263184331[43] = 0.0;
   out_6131259255263184331[44] = 0.0;
   out_6131259255263184331[45] = 0.0;
   out_6131259255263184331[46] = 0.0;
   out_6131259255263184331[47] = 0.0;
   out_6131259255263184331[48] = 0.0;
   out_6131259255263184331[49] = 0.0;
   out_6131259255263184331[50] = 1.0;
   out_6131259255263184331[51] = 0.0;
   out_6131259255263184331[52] = 0.0;
   out_6131259255263184331[53] = 0.0;
   out_6131259255263184331[54] = 0.0;
   out_6131259255263184331[55] = 0.0;
   out_6131259255263184331[56] = 0.0;
   out_6131259255263184331[57] = 0.0;
   out_6131259255263184331[58] = 0.0;
   out_6131259255263184331[59] = 0.0;
   out_6131259255263184331[60] = 1.0;
   out_6131259255263184331[61] = 0.0;
   out_6131259255263184331[62] = 0.0;
   out_6131259255263184331[63] = 0.0;
   out_6131259255263184331[64] = 0.0;
   out_6131259255263184331[65] = 0.0;
   out_6131259255263184331[66] = 0.0;
   out_6131259255263184331[67] = 0.0;
   out_6131259255263184331[68] = 0.0;
   out_6131259255263184331[69] = 0.0;
   out_6131259255263184331[70] = 1.0;
   out_6131259255263184331[71] = 0.0;
   out_6131259255263184331[72] = 0.0;
   out_6131259255263184331[73] = 0.0;
   out_6131259255263184331[74] = 0.0;
   out_6131259255263184331[75] = 0.0;
   out_6131259255263184331[76] = 0.0;
   out_6131259255263184331[77] = 0.0;
   out_6131259255263184331[78] = 0.0;
   out_6131259255263184331[79] = 0.0;
   out_6131259255263184331[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_9114301376252007925) {
   out_9114301376252007925[0] = state[0];
   out_9114301376252007925[1] = state[1];
   out_9114301376252007925[2] = state[2];
   out_9114301376252007925[3] = state[3];
   out_9114301376252007925[4] = state[4];
   out_9114301376252007925[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_9114301376252007925[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_9114301376252007925[7] = state[7];
   out_9114301376252007925[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3297863687905255883) {
   out_3297863687905255883[0] = 1;
   out_3297863687905255883[1] = 0;
   out_3297863687905255883[2] = 0;
   out_3297863687905255883[3] = 0;
   out_3297863687905255883[4] = 0;
   out_3297863687905255883[5] = 0;
   out_3297863687905255883[6] = 0;
   out_3297863687905255883[7] = 0;
   out_3297863687905255883[8] = 0;
   out_3297863687905255883[9] = 0;
   out_3297863687905255883[10] = 1;
   out_3297863687905255883[11] = 0;
   out_3297863687905255883[12] = 0;
   out_3297863687905255883[13] = 0;
   out_3297863687905255883[14] = 0;
   out_3297863687905255883[15] = 0;
   out_3297863687905255883[16] = 0;
   out_3297863687905255883[17] = 0;
   out_3297863687905255883[18] = 0;
   out_3297863687905255883[19] = 0;
   out_3297863687905255883[20] = 1;
   out_3297863687905255883[21] = 0;
   out_3297863687905255883[22] = 0;
   out_3297863687905255883[23] = 0;
   out_3297863687905255883[24] = 0;
   out_3297863687905255883[25] = 0;
   out_3297863687905255883[26] = 0;
   out_3297863687905255883[27] = 0;
   out_3297863687905255883[28] = 0;
   out_3297863687905255883[29] = 0;
   out_3297863687905255883[30] = 1;
   out_3297863687905255883[31] = 0;
   out_3297863687905255883[32] = 0;
   out_3297863687905255883[33] = 0;
   out_3297863687905255883[34] = 0;
   out_3297863687905255883[35] = 0;
   out_3297863687905255883[36] = 0;
   out_3297863687905255883[37] = 0;
   out_3297863687905255883[38] = 0;
   out_3297863687905255883[39] = 0;
   out_3297863687905255883[40] = 1;
   out_3297863687905255883[41] = 0;
   out_3297863687905255883[42] = 0;
   out_3297863687905255883[43] = 0;
   out_3297863687905255883[44] = 0;
   out_3297863687905255883[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3297863687905255883[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3297863687905255883[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3297863687905255883[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3297863687905255883[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3297863687905255883[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3297863687905255883[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3297863687905255883[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3297863687905255883[53] = -9.8100000000000005*dt;
   out_3297863687905255883[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3297863687905255883[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3297863687905255883[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3297863687905255883[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3297863687905255883[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3297863687905255883[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3297863687905255883[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3297863687905255883[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3297863687905255883[62] = 0;
   out_3297863687905255883[63] = 0;
   out_3297863687905255883[64] = 0;
   out_3297863687905255883[65] = 0;
   out_3297863687905255883[66] = 0;
   out_3297863687905255883[67] = 0;
   out_3297863687905255883[68] = 0;
   out_3297863687905255883[69] = 0;
   out_3297863687905255883[70] = 1;
   out_3297863687905255883[71] = 0;
   out_3297863687905255883[72] = 0;
   out_3297863687905255883[73] = 0;
   out_3297863687905255883[74] = 0;
   out_3297863687905255883[75] = 0;
   out_3297863687905255883[76] = 0;
   out_3297863687905255883[77] = 0;
   out_3297863687905255883[78] = 0;
   out_3297863687905255883[79] = 0;
   out_3297863687905255883[80] = 1;
}
void h_25(double *state, double *unused, double *out_7473609193578118278) {
   out_7473609193578118278[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8792436179801002137) {
   out_8792436179801002137[0] = 0;
   out_8792436179801002137[1] = 0;
   out_8792436179801002137[2] = 0;
   out_8792436179801002137[3] = 0;
   out_8792436179801002137[4] = 0;
   out_8792436179801002137[5] = 0;
   out_8792436179801002137[6] = 1;
   out_8792436179801002137[7] = 0;
   out_8792436179801002137[8] = 0;
}
void h_24(double *state, double *unused, double *out_3860824270109750960) {
   out_3860824270109750960[0] = state[4];
   out_3860824270109750960[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6619786580795502571) {
   out_6619786580795502571[0] = 0;
   out_6619786580795502571[1] = 0;
   out_6619786580795502571[2] = 0;
   out_6619786580795502571[3] = 0;
   out_6619786580795502571[4] = 1;
   out_6619786580795502571[5] = 0;
   out_6619786580795502571[6] = 0;
   out_6619786580795502571[7] = 0;
   out_6619786580795502571[8] = 0;
   out_6619786580795502571[9] = 0;
   out_6619786580795502571[10] = 0;
   out_6619786580795502571[11] = 0;
   out_6619786580795502571[12] = 0;
   out_6619786580795502571[13] = 0;
   out_6619786580795502571[14] = 1;
   out_6619786580795502571[15] = 0;
   out_6619786580795502571[16] = 0;
   out_6619786580795502571[17] = 0;
}
void h_30(double *state, double *unused, double *out_7619129017798773249) {
   out_7619129017798773249[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7135974935401300852) {
   out_7135974935401300852[0] = 0;
   out_7135974935401300852[1] = 0;
   out_7135974935401300852[2] = 0;
   out_7135974935401300852[3] = 0;
   out_7135974935401300852[4] = 1;
   out_7135974935401300852[5] = 0;
   out_7135974935401300852[6] = 0;
   out_7135974935401300852[7] = 0;
   out_7135974935401300852[8] = 0;
}
void h_26(double *state, double *unused, double *out_8562638870700435684) {
   out_8562638870700435684[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5050932860926945913) {
   out_5050932860926945913[0] = 0;
   out_5050932860926945913[1] = 0;
   out_5050932860926945913[2] = 0;
   out_5050932860926945913[3] = 0;
   out_5050932860926945913[4] = 0;
   out_5050932860926945913[5] = 0;
   out_5050932860926945913[6] = 0;
   out_5050932860926945913[7] = 1;
   out_5050932860926945913[8] = 0;
}
void h_27(double *state, double *unused, double *out_5971461612470587693) {
   out_5971461612470587693[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4912380864217357635) {
   out_4912380864217357635[0] = 0;
   out_4912380864217357635[1] = 0;
   out_4912380864217357635[2] = 0;
   out_4912380864217357635[3] = 1;
   out_4912380864217357635[4] = 0;
   out_4912380864217357635[5] = 0;
   out_4912380864217357635[6] = 0;
   out_4912380864217357635[7] = 0;
   out_4912380864217357635[8] = 0;
}
void h_29(double *state, double *unused, double *out_183985583370072436) {
   out_183985583370072436[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6625743591086908668) {
   out_6625743591086908668[0] = 0;
   out_6625743591086908668[1] = 1;
   out_6625743591086908668[2] = 0;
   out_6625743591086908668[3] = 0;
   out_6625743591086908668[4] = 0;
   out_6625743591086908668[5] = 0;
   out_6625743591086908668[6] = 0;
   out_6625743591086908668[7] = 0;
   out_6625743591086908668[8] = 0;
}
void h_28(double *state, double *unused, double *out_5368145727794110176) {
   out_5368145727794110176[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6738601465553112374) {
   out_6738601465553112374[0] = 1;
   out_6738601465553112374[1] = 0;
   out_6738601465553112374[2] = 0;
   out_6738601465553112374[3] = 0;
   out_6738601465553112374[4] = 0;
   out_6738601465553112374[5] = 0;
   out_6738601465553112374[6] = 0;
   out_6738601465553112374[7] = 0;
   out_6738601465553112374[8] = 0;
}
void h_31(double *state, double *unused, double *out_3836159665324095928) {
   out_3836159665324095928[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8823082141677962565) {
   out_8823082141677962565[0] = 0;
   out_8823082141677962565[1] = 0;
   out_8823082141677962565[2] = 0;
   out_8823082141677962565[3] = 0;
   out_8823082141677962565[4] = 0;
   out_8823082141677962565[5] = 0;
   out_8823082141677962565[6] = 0;
   out_8823082141677962565[7] = 0;
   out_8823082141677962565[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4669638409443648641) {
  err_fun(nom_x, delta_x, out_4669638409443648641);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8859452741513286810) {
  inv_err_fun(nom_x, true_x, out_8859452741513286810);
}
void car_H_mod_fun(double *state, double *out_6131259255263184331) {
  H_mod_fun(state, out_6131259255263184331);
}
void car_f_fun(double *state, double dt, double *out_9114301376252007925) {
  f_fun(state,  dt, out_9114301376252007925);
}
void car_F_fun(double *state, double dt, double *out_3297863687905255883) {
  F_fun(state,  dt, out_3297863687905255883);
}
void car_h_25(double *state, double *unused, double *out_7473609193578118278) {
  h_25(state, unused, out_7473609193578118278);
}
void car_H_25(double *state, double *unused, double *out_8792436179801002137) {
  H_25(state, unused, out_8792436179801002137);
}
void car_h_24(double *state, double *unused, double *out_3860824270109750960) {
  h_24(state, unused, out_3860824270109750960);
}
void car_H_24(double *state, double *unused, double *out_6619786580795502571) {
  H_24(state, unused, out_6619786580795502571);
}
void car_h_30(double *state, double *unused, double *out_7619129017798773249) {
  h_30(state, unused, out_7619129017798773249);
}
void car_H_30(double *state, double *unused, double *out_7135974935401300852) {
  H_30(state, unused, out_7135974935401300852);
}
void car_h_26(double *state, double *unused, double *out_8562638870700435684) {
  h_26(state, unused, out_8562638870700435684);
}
void car_H_26(double *state, double *unused, double *out_5050932860926945913) {
  H_26(state, unused, out_5050932860926945913);
}
void car_h_27(double *state, double *unused, double *out_5971461612470587693) {
  h_27(state, unused, out_5971461612470587693);
}
void car_H_27(double *state, double *unused, double *out_4912380864217357635) {
  H_27(state, unused, out_4912380864217357635);
}
void car_h_29(double *state, double *unused, double *out_183985583370072436) {
  h_29(state, unused, out_183985583370072436);
}
void car_H_29(double *state, double *unused, double *out_6625743591086908668) {
  H_29(state, unused, out_6625743591086908668);
}
void car_h_28(double *state, double *unused, double *out_5368145727794110176) {
  h_28(state, unused, out_5368145727794110176);
}
void car_H_28(double *state, double *unused, double *out_6738601465553112374) {
  H_28(state, unused, out_6738601465553112374);
}
void car_h_31(double *state, double *unused, double *out_3836159665324095928) {
  h_31(state, unused, out_3836159665324095928);
}
void car_H_31(double *state, double *unused, double *out_8823082141677962565) {
  H_31(state, unused, out_8823082141677962565);
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
