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
void err_fun(double *nom_x, double *delta_x, double *out_1607973439159951126) {
   out_1607973439159951126[0] = delta_x[0] + nom_x[0];
   out_1607973439159951126[1] = delta_x[1] + nom_x[1];
   out_1607973439159951126[2] = delta_x[2] + nom_x[2];
   out_1607973439159951126[3] = delta_x[3] + nom_x[3];
   out_1607973439159951126[4] = delta_x[4] + nom_x[4];
   out_1607973439159951126[5] = delta_x[5] + nom_x[5];
   out_1607973439159951126[6] = delta_x[6] + nom_x[6];
   out_1607973439159951126[7] = delta_x[7] + nom_x[7];
   out_1607973439159951126[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2168352623537558810) {
   out_2168352623537558810[0] = -nom_x[0] + true_x[0];
   out_2168352623537558810[1] = -nom_x[1] + true_x[1];
   out_2168352623537558810[2] = -nom_x[2] + true_x[2];
   out_2168352623537558810[3] = -nom_x[3] + true_x[3];
   out_2168352623537558810[4] = -nom_x[4] + true_x[4];
   out_2168352623537558810[5] = -nom_x[5] + true_x[5];
   out_2168352623537558810[6] = -nom_x[6] + true_x[6];
   out_2168352623537558810[7] = -nom_x[7] + true_x[7];
   out_2168352623537558810[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2583274475517743554) {
   out_2583274475517743554[0] = 1.0;
   out_2583274475517743554[1] = 0.0;
   out_2583274475517743554[2] = 0.0;
   out_2583274475517743554[3] = 0.0;
   out_2583274475517743554[4] = 0.0;
   out_2583274475517743554[5] = 0.0;
   out_2583274475517743554[6] = 0.0;
   out_2583274475517743554[7] = 0.0;
   out_2583274475517743554[8] = 0.0;
   out_2583274475517743554[9] = 0.0;
   out_2583274475517743554[10] = 1.0;
   out_2583274475517743554[11] = 0.0;
   out_2583274475517743554[12] = 0.0;
   out_2583274475517743554[13] = 0.0;
   out_2583274475517743554[14] = 0.0;
   out_2583274475517743554[15] = 0.0;
   out_2583274475517743554[16] = 0.0;
   out_2583274475517743554[17] = 0.0;
   out_2583274475517743554[18] = 0.0;
   out_2583274475517743554[19] = 0.0;
   out_2583274475517743554[20] = 1.0;
   out_2583274475517743554[21] = 0.0;
   out_2583274475517743554[22] = 0.0;
   out_2583274475517743554[23] = 0.0;
   out_2583274475517743554[24] = 0.0;
   out_2583274475517743554[25] = 0.0;
   out_2583274475517743554[26] = 0.0;
   out_2583274475517743554[27] = 0.0;
   out_2583274475517743554[28] = 0.0;
   out_2583274475517743554[29] = 0.0;
   out_2583274475517743554[30] = 1.0;
   out_2583274475517743554[31] = 0.0;
   out_2583274475517743554[32] = 0.0;
   out_2583274475517743554[33] = 0.0;
   out_2583274475517743554[34] = 0.0;
   out_2583274475517743554[35] = 0.0;
   out_2583274475517743554[36] = 0.0;
   out_2583274475517743554[37] = 0.0;
   out_2583274475517743554[38] = 0.0;
   out_2583274475517743554[39] = 0.0;
   out_2583274475517743554[40] = 1.0;
   out_2583274475517743554[41] = 0.0;
   out_2583274475517743554[42] = 0.0;
   out_2583274475517743554[43] = 0.0;
   out_2583274475517743554[44] = 0.0;
   out_2583274475517743554[45] = 0.0;
   out_2583274475517743554[46] = 0.0;
   out_2583274475517743554[47] = 0.0;
   out_2583274475517743554[48] = 0.0;
   out_2583274475517743554[49] = 0.0;
   out_2583274475517743554[50] = 1.0;
   out_2583274475517743554[51] = 0.0;
   out_2583274475517743554[52] = 0.0;
   out_2583274475517743554[53] = 0.0;
   out_2583274475517743554[54] = 0.0;
   out_2583274475517743554[55] = 0.0;
   out_2583274475517743554[56] = 0.0;
   out_2583274475517743554[57] = 0.0;
   out_2583274475517743554[58] = 0.0;
   out_2583274475517743554[59] = 0.0;
   out_2583274475517743554[60] = 1.0;
   out_2583274475517743554[61] = 0.0;
   out_2583274475517743554[62] = 0.0;
   out_2583274475517743554[63] = 0.0;
   out_2583274475517743554[64] = 0.0;
   out_2583274475517743554[65] = 0.0;
   out_2583274475517743554[66] = 0.0;
   out_2583274475517743554[67] = 0.0;
   out_2583274475517743554[68] = 0.0;
   out_2583274475517743554[69] = 0.0;
   out_2583274475517743554[70] = 1.0;
   out_2583274475517743554[71] = 0.0;
   out_2583274475517743554[72] = 0.0;
   out_2583274475517743554[73] = 0.0;
   out_2583274475517743554[74] = 0.0;
   out_2583274475517743554[75] = 0.0;
   out_2583274475517743554[76] = 0.0;
   out_2583274475517743554[77] = 0.0;
   out_2583274475517743554[78] = 0.0;
   out_2583274475517743554[79] = 0.0;
   out_2583274475517743554[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5962891950542322522) {
   out_5962891950542322522[0] = state[0];
   out_5962891950542322522[1] = state[1];
   out_5962891950542322522[2] = state[2];
   out_5962891950542322522[3] = state[3];
   out_5962891950542322522[4] = state[4];
   out_5962891950542322522[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5962891950542322522[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5962891950542322522[7] = state[7];
   out_5962891950542322522[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2636529809798275009) {
   out_2636529809798275009[0] = 1;
   out_2636529809798275009[1] = 0;
   out_2636529809798275009[2] = 0;
   out_2636529809798275009[3] = 0;
   out_2636529809798275009[4] = 0;
   out_2636529809798275009[5] = 0;
   out_2636529809798275009[6] = 0;
   out_2636529809798275009[7] = 0;
   out_2636529809798275009[8] = 0;
   out_2636529809798275009[9] = 0;
   out_2636529809798275009[10] = 1;
   out_2636529809798275009[11] = 0;
   out_2636529809798275009[12] = 0;
   out_2636529809798275009[13] = 0;
   out_2636529809798275009[14] = 0;
   out_2636529809798275009[15] = 0;
   out_2636529809798275009[16] = 0;
   out_2636529809798275009[17] = 0;
   out_2636529809798275009[18] = 0;
   out_2636529809798275009[19] = 0;
   out_2636529809798275009[20] = 1;
   out_2636529809798275009[21] = 0;
   out_2636529809798275009[22] = 0;
   out_2636529809798275009[23] = 0;
   out_2636529809798275009[24] = 0;
   out_2636529809798275009[25] = 0;
   out_2636529809798275009[26] = 0;
   out_2636529809798275009[27] = 0;
   out_2636529809798275009[28] = 0;
   out_2636529809798275009[29] = 0;
   out_2636529809798275009[30] = 1;
   out_2636529809798275009[31] = 0;
   out_2636529809798275009[32] = 0;
   out_2636529809798275009[33] = 0;
   out_2636529809798275009[34] = 0;
   out_2636529809798275009[35] = 0;
   out_2636529809798275009[36] = 0;
   out_2636529809798275009[37] = 0;
   out_2636529809798275009[38] = 0;
   out_2636529809798275009[39] = 0;
   out_2636529809798275009[40] = 1;
   out_2636529809798275009[41] = 0;
   out_2636529809798275009[42] = 0;
   out_2636529809798275009[43] = 0;
   out_2636529809798275009[44] = 0;
   out_2636529809798275009[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2636529809798275009[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2636529809798275009[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2636529809798275009[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2636529809798275009[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2636529809798275009[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2636529809798275009[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2636529809798275009[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2636529809798275009[53] = -9.8100000000000005*dt;
   out_2636529809798275009[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2636529809798275009[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2636529809798275009[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2636529809798275009[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2636529809798275009[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2636529809798275009[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2636529809798275009[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2636529809798275009[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2636529809798275009[62] = 0;
   out_2636529809798275009[63] = 0;
   out_2636529809798275009[64] = 0;
   out_2636529809798275009[65] = 0;
   out_2636529809798275009[66] = 0;
   out_2636529809798275009[67] = 0;
   out_2636529809798275009[68] = 0;
   out_2636529809798275009[69] = 0;
   out_2636529809798275009[70] = 1;
   out_2636529809798275009[71] = 0;
   out_2636529809798275009[72] = 0;
   out_2636529809798275009[73] = 0;
   out_2636529809798275009[74] = 0;
   out_2636529809798275009[75] = 0;
   out_2636529809798275009[76] = 0;
   out_2636529809798275009[77] = 0;
   out_2636529809798275009[78] = 0;
   out_2636529809798275009[79] = 0;
   out_2636529809798275009[80] = 1;
}
void h_25(double *state, double *unused, double *out_1279931555827013363) {
   out_1279931555827013363[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6609913750394493683) {
   out_6609913750394493683[0] = 0;
   out_6609913750394493683[1] = 0;
   out_6609913750394493683[2] = 0;
   out_6609913750394493683[3] = 0;
   out_6609913750394493683[4] = 0;
   out_6609913750394493683[5] = 0;
   out_6609913750394493683[6] = 1;
   out_6609913750394493683[7] = 0;
   out_6609913750394493683[8] = 0;
}
void h_24(double *state, double *unused, double *out_1314306168655061671) {
   out_1314306168655061671[0] = state[4];
   out_1314306168655061671[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8782563349399993249) {
   out_8782563349399993249[0] = 0;
   out_8782563349399993249[1] = 0;
   out_8782563349399993249[2] = 0;
   out_8782563349399993249[3] = 0;
   out_8782563349399993249[4] = 1;
   out_8782563349399993249[5] = 0;
   out_8782563349399993249[6] = 0;
   out_8782563349399993249[7] = 0;
   out_8782563349399993249[8] = 0;
   out_8782563349399993249[9] = 0;
   out_8782563349399993249[10] = 0;
   out_8782563349399993249[11] = 0;
   out_8782563349399993249[12] = 0;
   out_8782563349399993249[13] = 0;
   out_8782563349399993249[14] = 1;
   out_8782563349399993249[15] = 0;
   out_8782563349399993249[16] = 0;
   out_8782563349399993249[17] = 0;
}
void h_30(double *state, double *unused, double *out_1716461369006897797) {
   out_1716461369006897797[0] = state[4];
}
void H_30(double *state, double *unused, double *out_306776591097123072) {
   out_306776591097123072[0] = 0;
   out_306776591097123072[1] = 0;
   out_306776591097123072[2] = 0;
   out_306776591097123072[3] = 0;
   out_306776591097123072[4] = 1;
   out_306776591097123072[5] = 0;
   out_306776591097123072[6] = 0;
   out_306776591097123072[7] = 0;
   out_306776591097123072[8] = 0;
}
void h_26(double *state, double *unused, double *out_5998025210250558305) {
   out_5998025210250558305[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8095327004441001709) {
   out_8095327004441001709[0] = 0;
   out_8095327004441001709[1] = 0;
   out_8095327004441001709[2] = 0;
   out_8095327004441001709[3] = 0;
   out_8095327004441001709[4] = 0;
   out_8095327004441001709[5] = 0;
   out_8095327004441001709[6] = 0;
   out_8095327004441001709[7] = 1;
   out_8095327004441001709[8] = 0;
}
void h_27(double *state, double *unused, double *out_3721741711833832282) {
   out_3721741711833832282[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8914016009338158664) {
   out_8914016009338158664[0] = 0;
   out_8914016009338158664[1] = 0;
   out_8914016009338158664[2] = 0;
   out_8914016009338158664[3] = 1;
   out_8914016009338158664[4] = 0;
   out_8914016009338158664[5] = 0;
   out_8914016009338158664[6] = 0;
   out_8914016009338158664[7] = 0;
   out_8914016009338158664[8] = 0;
}
void h_29(double *state, double *unused, double *out_4041523544986840159) {
   out_4041523544986840159[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3581349447572852872) {
   out_3581349447572852872[0] = 0;
   out_3581349447572852872[1] = 1;
   out_3581349447572852872[2] = 0;
   out_3581349447572852872[3] = 0;
   out_3581349447572852872[4] = 0;
   out_3581349447572852872[5] = 0;
   out_3581349447572852872[6] = 0;
   out_3581349447572852872[7] = 0;
   out_3581349447572852872[8] = 0;
}
void h_28(double *state, double *unused, double *out_8147102627132063815) {
   out_8147102627132063815[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8663748464642383446) {
   out_8663748464642383446[0] = 1;
   out_8663748464642383446[1] = 0;
   out_8663748464642383446[2] = 0;
   out_8663748464642383446[3] = 0;
   out_8663748464642383446[4] = 0;
   out_8663748464642383446[5] = 0;
   out_8663748464642383446[6] = 0;
   out_8663748464642383446[7] = 0;
   out_8663748464642383446[8] = 0;
}
void h_31(double *state, double *unused, double *out_5490903670523337573) {
   out_5490903670523337573[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6579267788517533255) {
   out_6579267788517533255[0] = 0;
   out_6579267788517533255[1] = 0;
   out_6579267788517533255[2] = 0;
   out_6579267788517533255[3] = 0;
   out_6579267788517533255[4] = 0;
   out_6579267788517533255[5] = 0;
   out_6579267788517533255[6] = 0;
   out_6579267788517533255[7] = 0;
   out_6579267788517533255[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_1607973439159951126) {
  err_fun(nom_x, delta_x, out_1607973439159951126);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2168352623537558810) {
  inv_err_fun(nom_x, true_x, out_2168352623537558810);
}
void car_H_mod_fun(double *state, double *out_2583274475517743554) {
  H_mod_fun(state, out_2583274475517743554);
}
void car_f_fun(double *state, double dt, double *out_5962891950542322522) {
  f_fun(state,  dt, out_5962891950542322522);
}
void car_F_fun(double *state, double dt, double *out_2636529809798275009) {
  F_fun(state,  dt, out_2636529809798275009);
}
void car_h_25(double *state, double *unused, double *out_1279931555827013363) {
  h_25(state, unused, out_1279931555827013363);
}
void car_H_25(double *state, double *unused, double *out_6609913750394493683) {
  H_25(state, unused, out_6609913750394493683);
}
void car_h_24(double *state, double *unused, double *out_1314306168655061671) {
  h_24(state, unused, out_1314306168655061671);
}
void car_H_24(double *state, double *unused, double *out_8782563349399993249) {
  H_24(state, unused, out_8782563349399993249);
}
void car_h_30(double *state, double *unused, double *out_1716461369006897797) {
  h_30(state, unused, out_1716461369006897797);
}
void car_H_30(double *state, double *unused, double *out_306776591097123072) {
  H_30(state, unused, out_306776591097123072);
}
void car_h_26(double *state, double *unused, double *out_5998025210250558305) {
  h_26(state, unused, out_5998025210250558305);
}
void car_H_26(double *state, double *unused, double *out_8095327004441001709) {
  H_26(state, unused, out_8095327004441001709);
}
void car_h_27(double *state, double *unused, double *out_3721741711833832282) {
  h_27(state, unused, out_3721741711833832282);
}
void car_H_27(double *state, double *unused, double *out_8914016009338158664) {
  H_27(state, unused, out_8914016009338158664);
}
void car_h_29(double *state, double *unused, double *out_4041523544986840159) {
  h_29(state, unused, out_4041523544986840159);
}
void car_H_29(double *state, double *unused, double *out_3581349447572852872) {
  H_29(state, unused, out_3581349447572852872);
}
void car_h_28(double *state, double *unused, double *out_8147102627132063815) {
  h_28(state, unused, out_8147102627132063815);
}
void car_H_28(double *state, double *unused, double *out_8663748464642383446) {
  H_28(state, unused, out_8663748464642383446);
}
void car_h_31(double *state, double *unused, double *out_5490903670523337573) {
  h_31(state, unused, out_5490903670523337573);
}
void car_H_31(double *state, double *unused, double *out_6579267788517533255) {
  H_31(state, unused, out_6579267788517533255);
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
