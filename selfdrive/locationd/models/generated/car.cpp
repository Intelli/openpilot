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
void err_fun(double *nom_x, double *delta_x, double *out_7534092571675706452) {
   out_7534092571675706452[0] = delta_x[0] + nom_x[0];
   out_7534092571675706452[1] = delta_x[1] + nom_x[1];
   out_7534092571675706452[2] = delta_x[2] + nom_x[2];
   out_7534092571675706452[3] = delta_x[3] + nom_x[3];
   out_7534092571675706452[4] = delta_x[4] + nom_x[4];
   out_7534092571675706452[5] = delta_x[5] + nom_x[5];
   out_7534092571675706452[6] = delta_x[6] + nom_x[6];
   out_7534092571675706452[7] = delta_x[7] + nom_x[7];
   out_7534092571675706452[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4024152262625958442) {
   out_4024152262625958442[0] = -nom_x[0] + true_x[0];
   out_4024152262625958442[1] = -nom_x[1] + true_x[1];
   out_4024152262625958442[2] = -nom_x[2] + true_x[2];
   out_4024152262625958442[3] = -nom_x[3] + true_x[3];
   out_4024152262625958442[4] = -nom_x[4] + true_x[4];
   out_4024152262625958442[5] = -nom_x[5] + true_x[5];
   out_4024152262625958442[6] = -nom_x[6] + true_x[6];
   out_4024152262625958442[7] = -nom_x[7] + true_x[7];
   out_4024152262625958442[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8751041747313336178) {
   out_8751041747313336178[0] = 1.0;
   out_8751041747313336178[1] = 0.0;
   out_8751041747313336178[2] = 0.0;
   out_8751041747313336178[3] = 0.0;
   out_8751041747313336178[4] = 0.0;
   out_8751041747313336178[5] = 0.0;
   out_8751041747313336178[6] = 0.0;
   out_8751041747313336178[7] = 0.0;
   out_8751041747313336178[8] = 0.0;
   out_8751041747313336178[9] = 0.0;
   out_8751041747313336178[10] = 1.0;
   out_8751041747313336178[11] = 0.0;
   out_8751041747313336178[12] = 0.0;
   out_8751041747313336178[13] = 0.0;
   out_8751041747313336178[14] = 0.0;
   out_8751041747313336178[15] = 0.0;
   out_8751041747313336178[16] = 0.0;
   out_8751041747313336178[17] = 0.0;
   out_8751041747313336178[18] = 0.0;
   out_8751041747313336178[19] = 0.0;
   out_8751041747313336178[20] = 1.0;
   out_8751041747313336178[21] = 0.0;
   out_8751041747313336178[22] = 0.0;
   out_8751041747313336178[23] = 0.0;
   out_8751041747313336178[24] = 0.0;
   out_8751041747313336178[25] = 0.0;
   out_8751041747313336178[26] = 0.0;
   out_8751041747313336178[27] = 0.0;
   out_8751041747313336178[28] = 0.0;
   out_8751041747313336178[29] = 0.0;
   out_8751041747313336178[30] = 1.0;
   out_8751041747313336178[31] = 0.0;
   out_8751041747313336178[32] = 0.0;
   out_8751041747313336178[33] = 0.0;
   out_8751041747313336178[34] = 0.0;
   out_8751041747313336178[35] = 0.0;
   out_8751041747313336178[36] = 0.0;
   out_8751041747313336178[37] = 0.0;
   out_8751041747313336178[38] = 0.0;
   out_8751041747313336178[39] = 0.0;
   out_8751041747313336178[40] = 1.0;
   out_8751041747313336178[41] = 0.0;
   out_8751041747313336178[42] = 0.0;
   out_8751041747313336178[43] = 0.0;
   out_8751041747313336178[44] = 0.0;
   out_8751041747313336178[45] = 0.0;
   out_8751041747313336178[46] = 0.0;
   out_8751041747313336178[47] = 0.0;
   out_8751041747313336178[48] = 0.0;
   out_8751041747313336178[49] = 0.0;
   out_8751041747313336178[50] = 1.0;
   out_8751041747313336178[51] = 0.0;
   out_8751041747313336178[52] = 0.0;
   out_8751041747313336178[53] = 0.0;
   out_8751041747313336178[54] = 0.0;
   out_8751041747313336178[55] = 0.0;
   out_8751041747313336178[56] = 0.0;
   out_8751041747313336178[57] = 0.0;
   out_8751041747313336178[58] = 0.0;
   out_8751041747313336178[59] = 0.0;
   out_8751041747313336178[60] = 1.0;
   out_8751041747313336178[61] = 0.0;
   out_8751041747313336178[62] = 0.0;
   out_8751041747313336178[63] = 0.0;
   out_8751041747313336178[64] = 0.0;
   out_8751041747313336178[65] = 0.0;
   out_8751041747313336178[66] = 0.0;
   out_8751041747313336178[67] = 0.0;
   out_8751041747313336178[68] = 0.0;
   out_8751041747313336178[69] = 0.0;
   out_8751041747313336178[70] = 1.0;
   out_8751041747313336178[71] = 0.0;
   out_8751041747313336178[72] = 0.0;
   out_8751041747313336178[73] = 0.0;
   out_8751041747313336178[74] = 0.0;
   out_8751041747313336178[75] = 0.0;
   out_8751041747313336178[76] = 0.0;
   out_8751041747313336178[77] = 0.0;
   out_8751041747313336178[78] = 0.0;
   out_8751041747313336178[79] = 0.0;
   out_8751041747313336178[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1989825484445308883) {
   out_1989825484445308883[0] = state[0];
   out_1989825484445308883[1] = state[1];
   out_1989825484445308883[2] = state[2];
   out_1989825484445308883[3] = state[3];
   out_1989825484445308883[4] = state[4];
   out_1989825484445308883[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1989825484445308883[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1989825484445308883[7] = state[7];
   out_1989825484445308883[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8882937516093608616) {
   out_8882937516093608616[0] = 1;
   out_8882937516093608616[1] = 0;
   out_8882937516093608616[2] = 0;
   out_8882937516093608616[3] = 0;
   out_8882937516093608616[4] = 0;
   out_8882937516093608616[5] = 0;
   out_8882937516093608616[6] = 0;
   out_8882937516093608616[7] = 0;
   out_8882937516093608616[8] = 0;
   out_8882937516093608616[9] = 0;
   out_8882937516093608616[10] = 1;
   out_8882937516093608616[11] = 0;
   out_8882937516093608616[12] = 0;
   out_8882937516093608616[13] = 0;
   out_8882937516093608616[14] = 0;
   out_8882937516093608616[15] = 0;
   out_8882937516093608616[16] = 0;
   out_8882937516093608616[17] = 0;
   out_8882937516093608616[18] = 0;
   out_8882937516093608616[19] = 0;
   out_8882937516093608616[20] = 1;
   out_8882937516093608616[21] = 0;
   out_8882937516093608616[22] = 0;
   out_8882937516093608616[23] = 0;
   out_8882937516093608616[24] = 0;
   out_8882937516093608616[25] = 0;
   out_8882937516093608616[26] = 0;
   out_8882937516093608616[27] = 0;
   out_8882937516093608616[28] = 0;
   out_8882937516093608616[29] = 0;
   out_8882937516093608616[30] = 1;
   out_8882937516093608616[31] = 0;
   out_8882937516093608616[32] = 0;
   out_8882937516093608616[33] = 0;
   out_8882937516093608616[34] = 0;
   out_8882937516093608616[35] = 0;
   out_8882937516093608616[36] = 0;
   out_8882937516093608616[37] = 0;
   out_8882937516093608616[38] = 0;
   out_8882937516093608616[39] = 0;
   out_8882937516093608616[40] = 1;
   out_8882937516093608616[41] = 0;
   out_8882937516093608616[42] = 0;
   out_8882937516093608616[43] = 0;
   out_8882937516093608616[44] = 0;
   out_8882937516093608616[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8882937516093608616[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8882937516093608616[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8882937516093608616[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8882937516093608616[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8882937516093608616[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8882937516093608616[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8882937516093608616[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8882937516093608616[53] = -9.8100000000000005*dt;
   out_8882937516093608616[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8882937516093608616[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8882937516093608616[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8882937516093608616[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8882937516093608616[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8882937516093608616[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8882937516093608616[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8882937516093608616[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8882937516093608616[62] = 0;
   out_8882937516093608616[63] = 0;
   out_8882937516093608616[64] = 0;
   out_8882937516093608616[65] = 0;
   out_8882937516093608616[66] = 0;
   out_8882937516093608616[67] = 0;
   out_8882937516093608616[68] = 0;
   out_8882937516093608616[69] = 0;
   out_8882937516093608616[70] = 1;
   out_8882937516093608616[71] = 0;
   out_8882937516093608616[72] = 0;
   out_8882937516093608616[73] = 0;
   out_8882937516093608616[74] = 0;
   out_8882937516093608616[75] = 0;
   out_8882937516093608616[76] = 0;
   out_8882937516093608616[77] = 0;
   out_8882937516093608616[78] = 0;
   out_8882937516093608616[79] = 0;
   out_8882937516093608616[80] = 1;
}
void h_25(double *state, double *unused, double *out_119245575607229953) {
   out_119245575607229953[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6499843301606348462) {
   out_6499843301606348462[0] = 0;
   out_6499843301606348462[1] = 0;
   out_6499843301606348462[2] = 0;
   out_6499843301606348462[3] = 0;
   out_6499843301606348462[4] = 0;
   out_6499843301606348462[5] = 0;
   out_6499843301606348462[6] = 1;
   out_6499843301606348462[7] = 0;
   out_6499843301606348462[8] = 0;
}
void h_24(double *state, double *unused, double *out_1011930820961359105) {
   out_1011930820961359105[0] = state[4];
   out_1011930820961359105[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6313899731506755166) {
   out_6313899731506755166[0] = 0;
   out_6313899731506755166[1] = 0;
   out_6313899731506755166[2] = 0;
   out_6313899731506755166[3] = 0;
   out_6313899731506755166[4] = 1;
   out_6313899731506755166[5] = 0;
   out_6313899731506755166[6] = 0;
   out_6313899731506755166[7] = 0;
   out_6313899731506755166[8] = 0;
   out_6313899731506755166[9] = 0;
   out_6313899731506755166[10] = 0;
   out_6313899731506755166[11] = 0;
   out_6313899731506755166[12] = 0;
   out_6313899731506755166[13] = 0;
   out_6313899731506755166[14] = 1;
   out_6313899731506755166[15] = 0;
   out_6313899731506755166[16] = 0;
   out_6313899731506755166[17] = 0;
}
void h_30(double *state, double *unused, double *out_5794487451063518420) {
   out_5794487451063518420[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7419204441975594956) {
   out_7419204441975594956[0] = 0;
   out_7419204441975594956[1] = 0;
   out_7419204441975594956[2] = 0;
   out_7419204441975594956[3] = 0;
   out_7419204441975594956[4] = 1;
   out_7419204441975594956[5] = 0;
   out_7419204441975594956[6] = 0;
   out_7419204441975594956[7] = 0;
   out_7419204441975594956[8] = 0;
}
void h_26(double *state, double *unused, double *out_6397803335739995937) {
   out_6397803335739995937[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8205397453229146930) {
   out_8205397453229146930[0] = 0;
   out_8205397453229146930[1] = 0;
   out_8205397453229146930[2] = 0;
   out_8205397453229146930[3] = 0;
   out_8205397453229146930[4] = 0;
   out_8205397453229146930[5] = 0;
   out_8205397453229146930[6] = 0;
   out_8205397453229146930[7] = 1;
   out_8205397453229146930[8] = 0;
}
void h_27(double *state, double *unused, double *out_6279795941806619193) {
   out_6279795941806619193[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5244441130175170045) {
   out_5244441130175170045[0] = 0;
   out_5244441130175170045[1] = 0;
   out_5244441130175170045[2] = 0;
   out_5244441130175170045[3] = 1;
   out_5244441130175170045[4] = 0;
   out_5244441130175170045[5] = 0;
   out_5244441130175170045[6] = 0;
   out_5244441130175170045[7] = 0;
   out_5244441130175170045[8] = 0;
}
void h_29(double *state, double *unused, double *out_3670287450639192431) {
   out_3670287450639192431[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7929435786289987140) {
   out_7929435786289987140[0] = 0;
   out_7929435786289987140[1] = 1;
   out_7929435786289987140[2] = 0;
   out_7929435786289987140[3] = 0;
   out_7929435786289987140[4] = 0;
   out_7929435786289987140[5] = 0;
   out_7929435786289987140[6] = 0;
   out_7929435786289987140[7] = 0;
   out_7929435786289987140[8] = 0;
}
void h_28(double *state, double *unused, double *out_1278122674145773548) {
   out_1278122674145773548[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2847036769220456566) {
   out_2847036769220456566[0] = 1;
   out_2847036769220456566[1] = 0;
   out_2847036769220456566[2] = 0;
   out_2847036769220456566[3] = 0;
   out_2847036769220456566[4] = 0;
   out_2847036769220456566[5] = 0;
   out_2847036769220456566[6] = 0;
   out_2847036769220456566[7] = 0;
   out_2847036769220456566[8] = 0;
}
void h_31(double *state, double *unused, double *out_3518203952646792397) {
   out_3518203952646792397[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7579189350995795454) {
   out_7579189350995795454[0] = 0;
   out_7579189350995795454[1] = 0;
   out_7579189350995795454[2] = 0;
   out_7579189350995795454[3] = 0;
   out_7579189350995795454[4] = 0;
   out_7579189350995795454[5] = 0;
   out_7579189350995795454[6] = 0;
   out_7579189350995795454[7] = 0;
   out_7579189350995795454[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7534092571675706452) {
  err_fun(nom_x, delta_x, out_7534092571675706452);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4024152262625958442) {
  inv_err_fun(nom_x, true_x, out_4024152262625958442);
}
void car_H_mod_fun(double *state, double *out_8751041747313336178) {
  H_mod_fun(state, out_8751041747313336178);
}
void car_f_fun(double *state, double dt, double *out_1989825484445308883) {
  f_fun(state,  dt, out_1989825484445308883);
}
void car_F_fun(double *state, double dt, double *out_8882937516093608616) {
  F_fun(state,  dt, out_8882937516093608616);
}
void car_h_25(double *state, double *unused, double *out_119245575607229953) {
  h_25(state, unused, out_119245575607229953);
}
void car_H_25(double *state, double *unused, double *out_6499843301606348462) {
  H_25(state, unused, out_6499843301606348462);
}
void car_h_24(double *state, double *unused, double *out_1011930820961359105) {
  h_24(state, unused, out_1011930820961359105);
}
void car_H_24(double *state, double *unused, double *out_6313899731506755166) {
  H_24(state, unused, out_6313899731506755166);
}
void car_h_30(double *state, double *unused, double *out_5794487451063518420) {
  h_30(state, unused, out_5794487451063518420);
}
void car_H_30(double *state, double *unused, double *out_7419204441975594956) {
  H_30(state, unused, out_7419204441975594956);
}
void car_h_26(double *state, double *unused, double *out_6397803335739995937) {
  h_26(state, unused, out_6397803335739995937);
}
void car_H_26(double *state, double *unused, double *out_8205397453229146930) {
  H_26(state, unused, out_8205397453229146930);
}
void car_h_27(double *state, double *unused, double *out_6279795941806619193) {
  h_27(state, unused, out_6279795941806619193);
}
void car_H_27(double *state, double *unused, double *out_5244441130175170045) {
  H_27(state, unused, out_5244441130175170045);
}
void car_h_29(double *state, double *unused, double *out_3670287450639192431) {
  h_29(state, unused, out_3670287450639192431);
}
void car_H_29(double *state, double *unused, double *out_7929435786289987140) {
  H_29(state, unused, out_7929435786289987140);
}
void car_h_28(double *state, double *unused, double *out_1278122674145773548) {
  h_28(state, unused, out_1278122674145773548);
}
void car_H_28(double *state, double *unused, double *out_2847036769220456566) {
  H_28(state, unused, out_2847036769220456566);
}
void car_h_31(double *state, double *unused, double *out_3518203952646792397) {
  h_31(state, unused, out_3518203952646792397);
}
void car_H_31(double *state, double *unused, double *out_7579189350995795454) {
  H_31(state, unused, out_7579189350995795454);
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
