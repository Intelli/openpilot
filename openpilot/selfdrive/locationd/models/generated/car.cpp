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
void err_fun(double *nom_x, double *delta_x, double *out_1348800808687792387) {
   out_1348800808687792387[0] = delta_x[0] + nom_x[0];
   out_1348800808687792387[1] = delta_x[1] + nom_x[1];
   out_1348800808687792387[2] = delta_x[2] + nom_x[2];
   out_1348800808687792387[3] = delta_x[3] + nom_x[3];
   out_1348800808687792387[4] = delta_x[4] + nom_x[4];
   out_1348800808687792387[5] = delta_x[5] + nom_x[5];
   out_1348800808687792387[6] = delta_x[6] + nom_x[6];
   out_1348800808687792387[7] = delta_x[7] + nom_x[7];
   out_1348800808687792387[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1749907634917603761) {
   out_1749907634917603761[0] = -nom_x[0] + true_x[0];
   out_1749907634917603761[1] = -nom_x[1] + true_x[1];
   out_1749907634917603761[2] = -nom_x[2] + true_x[2];
   out_1749907634917603761[3] = -nom_x[3] + true_x[3];
   out_1749907634917603761[4] = -nom_x[4] + true_x[4];
   out_1749907634917603761[5] = -nom_x[5] + true_x[5];
   out_1749907634917603761[6] = -nom_x[6] + true_x[6];
   out_1749907634917603761[7] = -nom_x[7] + true_x[7];
   out_1749907634917603761[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4411937711281551923) {
   out_4411937711281551923[0] = 1.0;
   out_4411937711281551923[1] = 0.0;
   out_4411937711281551923[2] = 0.0;
   out_4411937711281551923[3] = 0.0;
   out_4411937711281551923[4] = 0.0;
   out_4411937711281551923[5] = 0.0;
   out_4411937711281551923[6] = 0.0;
   out_4411937711281551923[7] = 0.0;
   out_4411937711281551923[8] = 0.0;
   out_4411937711281551923[9] = 0.0;
   out_4411937711281551923[10] = 1.0;
   out_4411937711281551923[11] = 0.0;
   out_4411937711281551923[12] = 0.0;
   out_4411937711281551923[13] = 0.0;
   out_4411937711281551923[14] = 0.0;
   out_4411937711281551923[15] = 0.0;
   out_4411937711281551923[16] = 0.0;
   out_4411937711281551923[17] = 0.0;
   out_4411937711281551923[18] = 0.0;
   out_4411937711281551923[19] = 0.0;
   out_4411937711281551923[20] = 1.0;
   out_4411937711281551923[21] = 0.0;
   out_4411937711281551923[22] = 0.0;
   out_4411937711281551923[23] = 0.0;
   out_4411937711281551923[24] = 0.0;
   out_4411937711281551923[25] = 0.0;
   out_4411937711281551923[26] = 0.0;
   out_4411937711281551923[27] = 0.0;
   out_4411937711281551923[28] = 0.0;
   out_4411937711281551923[29] = 0.0;
   out_4411937711281551923[30] = 1.0;
   out_4411937711281551923[31] = 0.0;
   out_4411937711281551923[32] = 0.0;
   out_4411937711281551923[33] = 0.0;
   out_4411937711281551923[34] = 0.0;
   out_4411937711281551923[35] = 0.0;
   out_4411937711281551923[36] = 0.0;
   out_4411937711281551923[37] = 0.0;
   out_4411937711281551923[38] = 0.0;
   out_4411937711281551923[39] = 0.0;
   out_4411937711281551923[40] = 1.0;
   out_4411937711281551923[41] = 0.0;
   out_4411937711281551923[42] = 0.0;
   out_4411937711281551923[43] = 0.0;
   out_4411937711281551923[44] = 0.0;
   out_4411937711281551923[45] = 0.0;
   out_4411937711281551923[46] = 0.0;
   out_4411937711281551923[47] = 0.0;
   out_4411937711281551923[48] = 0.0;
   out_4411937711281551923[49] = 0.0;
   out_4411937711281551923[50] = 1.0;
   out_4411937711281551923[51] = 0.0;
   out_4411937711281551923[52] = 0.0;
   out_4411937711281551923[53] = 0.0;
   out_4411937711281551923[54] = 0.0;
   out_4411937711281551923[55] = 0.0;
   out_4411937711281551923[56] = 0.0;
   out_4411937711281551923[57] = 0.0;
   out_4411937711281551923[58] = 0.0;
   out_4411937711281551923[59] = 0.0;
   out_4411937711281551923[60] = 1.0;
   out_4411937711281551923[61] = 0.0;
   out_4411937711281551923[62] = 0.0;
   out_4411937711281551923[63] = 0.0;
   out_4411937711281551923[64] = 0.0;
   out_4411937711281551923[65] = 0.0;
   out_4411937711281551923[66] = 0.0;
   out_4411937711281551923[67] = 0.0;
   out_4411937711281551923[68] = 0.0;
   out_4411937711281551923[69] = 0.0;
   out_4411937711281551923[70] = 1.0;
   out_4411937711281551923[71] = 0.0;
   out_4411937711281551923[72] = 0.0;
   out_4411937711281551923[73] = 0.0;
   out_4411937711281551923[74] = 0.0;
   out_4411937711281551923[75] = 0.0;
   out_4411937711281551923[76] = 0.0;
   out_4411937711281551923[77] = 0.0;
   out_4411937711281551923[78] = 0.0;
   out_4411937711281551923[79] = 0.0;
   out_4411937711281551923[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6965050437253804893) {
   out_6965050437253804893[0] = state[0];
   out_6965050437253804893[1] = state[1];
   out_6965050437253804893[2] = state[2];
   out_6965050437253804893[3] = state[3];
   out_6965050437253804893[4] = state[4];
   out_6965050437253804893[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6965050437253804893[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6965050437253804893[7] = state[7];
   out_6965050437253804893[8] = state[8];
}
void F_fun(double *state, double dt, double *out_161323463410755275) {
   out_161323463410755275[0] = 1;
   out_161323463410755275[1] = 0;
   out_161323463410755275[2] = 0;
   out_161323463410755275[3] = 0;
   out_161323463410755275[4] = 0;
   out_161323463410755275[5] = 0;
   out_161323463410755275[6] = 0;
   out_161323463410755275[7] = 0;
   out_161323463410755275[8] = 0;
   out_161323463410755275[9] = 0;
   out_161323463410755275[10] = 1;
   out_161323463410755275[11] = 0;
   out_161323463410755275[12] = 0;
   out_161323463410755275[13] = 0;
   out_161323463410755275[14] = 0;
   out_161323463410755275[15] = 0;
   out_161323463410755275[16] = 0;
   out_161323463410755275[17] = 0;
   out_161323463410755275[18] = 0;
   out_161323463410755275[19] = 0;
   out_161323463410755275[20] = 1;
   out_161323463410755275[21] = 0;
   out_161323463410755275[22] = 0;
   out_161323463410755275[23] = 0;
   out_161323463410755275[24] = 0;
   out_161323463410755275[25] = 0;
   out_161323463410755275[26] = 0;
   out_161323463410755275[27] = 0;
   out_161323463410755275[28] = 0;
   out_161323463410755275[29] = 0;
   out_161323463410755275[30] = 1;
   out_161323463410755275[31] = 0;
   out_161323463410755275[32] = 0;
   out_161323463410755275[33] = 0;
   out_161323463410755275[34] = 0;
   out_161323463410755275[35] = 0;
   out_161323463410755275[36] = 0;
   out_161323463410755275[37] = 0;
   out_161323463410755275[38] = 0;
   out_161323463410755275[39] = 0;
   out_161323463410755275[40] = 1;
   out_161323463410755275[41] = 0;
   out_161323463410755275[42] = 0;
   out_161323463410755275[43] = 0;
   out_161323463410755275[44] = 0;
   out_161323463410755275[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_161323463410755275[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_161323463410755275[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_161323463410755275[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_161323463410755275[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_161323463410755275[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_161323463410755275[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_161323463410755275[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_161323463410755275[53] = -9.8100000000000005*dt;
   out_161323463410755275[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_161323463410755275[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_161323463410755275[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_161323463410755275[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_161323463410755275[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_161323463410755275[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_161323463410755275[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_161323463410755275[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_161323463410755275[62] = 0;
   out_161323463410755275[63] = 0;
   out_161323463410755275[64] = 0;
   out_161323463410755275[65] = 0;
   out_161323463410755275[66] = 0;
   out_161323463410755275[67] = 0;
   out_161323463410755275[68] = 0;
   out_161323463410755275[69] = 0;
   out_161323463410755275[70] = 1;
   out_161323463410755275[71] = 0;
   out_161323463410755275[72] = 0;
   out_161323463410755275[73] = 0;
   out_161323463410755275[74] = 0;
   out_161323463410755275[75] = 0;
   out_161323463410755275[76] = 0;
   out_161323463410755275[77] = 0;
   out_161323463410755275[78] = 0;
   out_161323463410755275[79] = 0;
   out_161323463410755275[80] = 1;
}
void h_25(double *state, double *unused, double *out_6578686103484159860) {
   out_6578686103484159860[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7934918361271043600) {
   out_7934918361271043600[0] = 0;
   out_7934918361271043600[1] = 0;
   out_7934918361271043600[2] = 0;
   out_7934918361271043600[3] = 0;
   out_7934918361271043600[4] = 0;
   out_7934918361271043600[5] = 0;
   out_7934918361271043600[6] = 1;
   out_7934918361271043600[7] = 0;
   out_7934918361271043600[8] = 0;
}
void h_24(double *state, double *unused, double *out_1714890755541721598) {
   out_1714890755541721598[0] = state[4];
   out_1714890755541721598[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3936253905846989915) {
   out_3936253905846989915[0] = 0;
   out_3936253905846989915[1] = 0;
   out_3936253905846989915[2] = 0;
   out_3936253905846989915[3] = 0;
   out_3936253905846989915[4] = 1;
   out_3936253905846989915[5] = 0;
   out_3936253905846989915[6] = 0;
   out_3936253905846989915[7] = 0;
   out_3936253905846989915[8] = 0;
   out_3936253905846989915[9] = 0;
   out_3936253905846989915[10] = 0;
   out_3936253905846989915[11] = 0;
   out_3936253905846989915[12] = 0;
   out_3936253905846989915[13] = 0;
   out_3936253905846989915[14] = 1;
   out_3936253905846989915[15] = 0;
   out_3936253905846989915[16] = 0;
   out_3936253905846989915[17] = 0;
}
void h_30(double *state, double *unused, double *out_2975148859307398715) {
   out_2975148859307398715[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3595135370946891261) {
   out_3595135370946891261[0] = 0;
   out_3595135370946891261[1] = 0;
   out_3595135370946891261[2] = 0;
   out_3595135370946891261[3] = 0;
   out_3595135370946891261[4] = 1;
   out_3595135370946891261[5] = 0;
   out_3595135370946891261[6] = 0;
   out_3595135370946891261[7] = 0;
   out_3595135370946891261[8] = 0;
}
void h_26(double *state, double *unused, double *out_61637192136933970) {
   out_61637192136933970[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4193415042396987376) {
   out_4193415042396987376[0] = 0;
   out_4193415042396987376[1] = 0;
   out_4193415042396987376[2] = 0;
   out_4193415042396987376[3] = 0;
   out_4193415042396987376[4] = 0;
   out_4193415042396987376[5] = 0;
   out_4193415042396987376[6] = 0;
   out_4193415042396987376[7] = 1;
   out_4193415042396987376[8] = 0;
}
void h_27(double *state, double *unused, double *out_3974280782675462209) {
   out_3974280782675462209[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5630816102327378619) {
   out_5630816102327378619[0] = 0;
   out_5630816102327378619[1] = 0;
   out_5630816102327378619[2] = 0;
   out_5630816102327378619[3] = 1;
   out_5630816102327378619[4] = 0;
   out_5630816102327378619[5] = 0;
   out_5630816102327378619[6] = 0;
   out_5630816102327378619[7] = 0;
   out_5630816102327378619[8] = 0;
}
void h_29(double *state, double *unused, double *out_8317016095193429278) {
   out_8317016095193429278[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8315810758442195714) {
   out_8315810758442195714[0] = 0;
   out_8315810758442195714[1] = 1;
   out_8315810758442195714[2] = 0;
   out_8315810758442195714[3] = 0;
   out_8315810758442195714[4] = 0;
   out_8315810758442195714[5] = 0;
   out_8315810758442195714[6] = 0;
   out_8315810758442195714[7] = 0;
   out_8315810758442195714[8] = 0;
}
void h_28(double *state, double *unused, double *out_7250128595422918798) {
   out_7250128595422918798[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5881083647023153837) {
   out_5881083647023153837[0] = 1;
   out_5881083647023153837[1] = 0;
   out_5881083647023153837[2] = 0;
   out_5881083647023153837[3] = 0;
   out_5881083647023153837[4] = 0;
   out_5881083647023153837[5] = 0;
   out_5881083647023153837[6] = 0;
   out_5881083647023153837[7] = 0;
   out_5881083647023153837[8] = 0;
}
void h_31(double *state, double *unused, double *out_1302586547269889325) {
   out_1302586547269889325[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7965564323148004028) {
   out_7965564323148004028[0] = 0;
   out_7965564323148004028[1] = 0;
   out_7965564323148004028[2] = 0;
   out_7965564323148004028[3] = 0;
   out_7965564323148004028[4] = 0;
   out_7965564323148004028[5] = 0;
   out_7965564323148004028[6] = 0;
   out_7965564323148004028[7] = 0;
   out_7965564323148004028[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_1348800808687792387) {
  err_fun(nom_x, delta_x, out_1348800808687792387);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1749907634917603761) {
  inv_err_fun(nom_x, true_x, out_1749907634917603761);
}
void car_H_mod_fun(double *state, double *out_4411937711281551923) {
  H_mod_fun(state, out_4411937711281551923);
}
void car_f_fun(double *state, double dt, double *out_6965050437253804893) {
  f_fun(state,  dt, out_6965050437253804893);
}
void car_F_fun(double *state, double dt, double *out_161323463410755275) {
  F_fun(state,  dt, out_161323463410755275);
}
void car_h_25(double *state, double *unused, double *out_6578686103484159860) {
  h_25(state, unused, out_6578686103484159860);
}
void car_H_25(double *state, double *unused, double *out_7934918361271043600) {
  H_25(state, unused, out_7934918361271043600);
}
void car_h_24(double *state, double *unused, double *out_1714890755541721598) {
  h_24(state, unused, out_1714890755541721598);
}
void car_H_24(double *state, double *unused, double *out_3936253905846989915) {
  H_24(state, unused, out_3936253905846989915);
}
void car_h_30(double *state, double *unused, double *out_2975148859307398715) {
  h_30(state, unused, out_2975148859307398715);
}
void car_H_30(double *state, double *unused, double *out_3595135370946891261) {
  H_30(state, unused, out_3595135370946891261);
}
void car_h_26(double *state, double *unused, double *out_61637192136933970) {
  h_26(state, unused, out_61637192136933970);
}
void car_H_26(double *state, double *unused, double *out_4193415042396987376) {
  H_26(state, unused, out_4193415042396987376);
}
void car_h_27(double *state, double *unused, double *out_3974280782675462209) {
  h_27(state, unused, out_3974280782675462209);
}
void car_H_27(double *state, double *unused, double *out_5630816102327378619) {
  H_27(state, unused, out_5630816102327378619);
}
void car_h_29(double *state, double *unused, double *out_8317016095193429278) {
  h_29(state, unused, out_8317016095193429278);
}
void car_H_29(double *state, double *unused, double *out_8315810758442195714) {
  H_29(state, unused, out_8315810758442195714);
}
void car_h_28(double *state, double *unused, double *out_7250128595422918798) {
  h_28(state, unused, out_7250128595422918798);
}
void car_H_28(double *state, double *unused, double *out_5881083647023153837) {
  H_28(state, unused, out_5881083647023153837);
}
void car_h_31(double *state, double *unused, double *out_1302586547269889325) {
  h_31(state, unused, out_1302586547269889325);
}
void car_H_31(double *state, double *unused, double *out_7965564323148004028) {
  H_31(state, unused, out_7965564323148004028);
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
