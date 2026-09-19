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
void err_fun(double *nom_x, double *delta_x, double *out_7293025660765852052) {
   out_7293025660765852052[0] = delta_x[0] + nom_x[0];
   out_7293025660765852052[1] = delta_x[1] + nom_x[1];
   out_7293025660765852052[2] = delta_x[2] + nom_x[2];
   out_7293025660765852052[3] = delta_x[3] + nom_x[3];
   out_7293025660765852052[4] = delta_x[4] + nom_x[4];
   out_7293025660765852052[5] = delta_x[5] + nom_x[5];
   out_7293025660765852052[6] = delta_x[6] + nom_x[6];
   out_7293025660765852052[7] = delta_x[7] + nom_x[7];
   out_7293025660765852052[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3117228366012468934) {
   out_3117228366012468934[0] = -nom_x[0] + true_x[0];
   out_3117228366012468934[1] = -nom_x[1] + true_x[1];
   out_3117228366012468934[2] = -nom_x[2] + true_x[2];
   out_3117228366012468934[3] = -nom_x[3] + true_x[3];
   out_3117228366012468934[4] = -nom_x[4] + true_x[4];
   out_3117228366012468934[5] = -nom_x[5] + true_x[5];
   out_3117228366012468934[6] = -nom_x[6] + true_x[6];
   out_3117228366012468934[7] = -nom_x[7] + true_x[7];
   out_3117228366012468934[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1447426965170589912) {
   out_1447426965170589912[0] = 1.0;
   out_1447426965170589912[1] = 0.0;
   out_1447426965170589912[2] = 0.0;
   out_1447426965170589912[3] = 0.0;
   out_1447426965170589912[4] = 0.0;
   out_1447426965170589912[5] = 0.0;
   out_1447426965170589912[6] = 0.0;
   out_1447426965170589912[7] = 0.0;
   out_1447426965170589912[8] = 0.0;
   out_1447426965170589912[9] = 0.0;
   out_1447426965170589912[10] = 1.0;
   out_1447426965170589912[11] = 0.0;
   out_1447426965170589912[12] = 0.0;
   out_1447426965170589912[13] = 0.0;
   out_1447426965170589912[14] = 0.0;
   out_1447426965170589912[15] = 0.0;
   out_1447426965170589912[16] = 0.0;
   out_1447426965170589912[17] = 0.0;
   out_1447426965170589912[18] = 0.0;
   out_1447426965170589912[19] = 0.0;
   out_1447426965170589912[20] = 1.0;
   out_1447426965170589912[21] = 0.0;
   out_1447426965170589912[22] = 0.0;
   out_1447426965170589912[23] = 0.0;
   out_1447426965170589912[24] = 0.0;
   out_1447426965170589912[25] = 0.0;
   out_1447426965170589912[26] = 0.0;
   out_1447426965170589912[27] = 0.0;
   out_1447426965170589912[28] = 0.0;
   out_1447426965170589912[29] = 0.0;
   out_1447426965170589912[30] = 1.0;
   out_1447426965170589912[31] = 0.0;
   out_1447426965170589912[32] = 0.0;
   out_1447426965170589912[33] = 0.0;
   out_1447426965170589912[34] = 0.0;
   out_1447426965170589912[35] = 0.0;
   out_1447426965170589912[36] = 0.0;
   out_1447426965170589912[37] = 0.0;
   out_1447426965170589912[38] = 0.0;
   out_1447426965170589912[39] = 0.0;
   out_1447426965170589912[40] = 1.0;
   out_1447426965170589912[41] = 0.0;
   out_1447426965170589912[42] = 0.0;
   out_1447426965170589912[43] = 0.0;
   out_1447426965170589912[44] = 0.0;
   out_1447426965170589912[45] = 0.0;
   out_1447426965170589912[46] = 0.0;
   out_1447426965170589912[47] = 0.0;
   out_1447426965170589912[48] = 0.0;
   out_1447426965170589912[49] = 0.0;
   out_1447426965170589912[50] = 1.0;
   out_1447426965170589912[51] = 0.0;
   out_1447426965170589912[52] = 0.0;
   out_1447426965170589912[53] = 0.0;
   out_1447426965170589912[54] = 0.0;
   out_1447426965170589912[55] = 0.0;
   out_1447426965170589912[56] = 0.0;
   out_1447426965170589912[57] = 0.0;
   out_1447426965170589912[58] = 0.0;
   out_1447426965170589912[59] = 0.0;
   out_1447426965170589912[60] = 1.0;
   out_1447426965170589912[61] = 0.0;
   out_1447426965170589912[62] = 0.0;
   out_1447426965170589912[63] = 0.0;
   out_1447426965170589912[64] = 0.0;
   out_1447426965170589912[65] = 0.0;
   out_1447426965170589912[66] = 0.0;
   out_1447426965170589912[67] = 0.0;
   out_1447426965170589912[68] = 0.0;
   out_1447426965170589912[69] = 0.0;
   out_1447426965170589912[70] = 1.0;
   out_1447426965170589912[71] = 0.0;
   out_1447426965170589912[72] = 0.0;
   out_1447426965170589912[73] = 0.0;
   out_1447426965170589912[74] = 0.0;
   out_1447426965170589912[75] = 0.0;
   out_1447426965170589912[76] = 0.0;
   out_1447426965170589912[77] = 0.0;
   out_1447426965170589912[78] = 0.0;
   out_1447426965170589912[79] = 0.0;
   out_1447426965170589912[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3647186790399289701) {
   out_3647186790399289701[0] = state[0];
   out_3647186790399289701[1] = state[1];
   out_3647186790399289701[2] = state[2];
   out_3647186790399289701[3] = state[3];
   out_3647186790399289701[4] = state[4];
   out_3647186790399289701[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3647186790399289701[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3647186790399289701[7] = state[7];
   out_3647186790399289701[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4083868303371300049) {
   out_4083868303371300049[0] = 1;
   out_4083868303371300049[1] = 0;
   out_4083868303371300049[2] = 0;
   out_4083868303371300049[3] = 0;
   out_4083868303371300049[4] = 0;
   out_4083868303371300049[5] = 0;
   out_4083868303371300049[6] = 0;
   out_4083868303371300049[7] = 0;
   out_4083868303371300049[8] = 0;
   out_4083868303371300049[9] = 0;
   out_4083868303371300049[10] = 1;
   out_4083868303371300049[11] = 0;
   out_4083868303371300049[12] = 0;
   out_4083868303371300049[13] = 0;
   out_4083868303371300049[14] = 0;
   out_4083868303371300049[15] = 0;
   out_4083868303371300049[16] = 0;
   out_4083868303371300049[17] = 0;
   out_4083868303371300049[18] = 0;
   out_4083868303371300049[19] = 0;
   out_4083868303371300049[20] = 1;
   out_4083868303371300049[21] = 0;
   out_4083868303371300049[22] = 0;
   out_4083868303371300049[23] = 0;
   out_4083868303371300049[24] = 0;
   out_4083868303371300049[25] = 0;
   out_4083868303371300049[26] = 0;
   out_4083868303371300049[27] = 0;
   out_4083868303371300049[28] = 0;
   out_4083868303371300049[29] = 0;
   out_4083868303371300049[30] = 1;
   out_4083868303371300049[31] = 0;
   out_4083868303371300049[32] = 0;
   out_4083868303371300049[33] = 0;
   out_4083868303371300049[34] = 0;
   out_4083868303371300049[35] = 0;
   out_4083868303371300049[36] = 0;
   out_4083868303371300049[37] = 0;
   out_4083868303371300049[38] = 0;
   out_4083868303371300049[39] = 0;
   out_4083868303371300049[40] = 1;
   out_4083868303371300049[41] = 0;
   out_4083868303371300049[42] = 0;
   out_4083868303371300049[43] = 0;
   out_4083868303371300049[44] = 0;
   out_4083868303371300049[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4083868303371300049[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4083868303371300049[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4083868303371300049[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4083868303371300049[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4083868303371300049[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4083868303371300049[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4083868303371300049[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4083868303371300049[53] = -9.8100000000000005*dt;
   out_4083868303371300049[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4083868303371300049[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4083868303371300049[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4083868303371300049[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4083868303371300049[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4083868303371300049[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4083868303371300049[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4083868303371300049[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4083868303371300049[62] = 0;
   out_4083868303371300049[63] = 0;
   out_4083868303371300049[64] = 0;
   out_4083868303371300049[65] = 0;
   out_4083868303371300049[66] = 0;
   out_4083868303371300049[67] = 0;
   out_4083868303371300049[68] = 0;
   out_4083868303371300049[69] = 0;
   out_4083868303371300049[70] = 1;
   out_4083868303371300049[71] = 0;
   out_4083868303371300049[72] = 0;
   out_4083868303371300049[73] = 0;
   out_4083868303371300049[74] = 0;
   out_4083868303371300049[75] = 0;
   out_4083868303371300049[76] = 0;
   out_4083868303371300049[77] = 0;
   out_4083868303371300049[78] = 0;
   out_4083868303371300049[79] = 0;
   out_4083868303371300049[80] = 1;
}
void h_25(double *state, double *unused, double *out_2804865530302421924) {
   out_2804865530302421924[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6473911067803269893) {
   out_6473911067803269893[0] = 0;
   out_6473911067803269893[1] = 0;
   out_6473911067803269893[2] = 0;
   out_6473911067803269893[3] = 0;
   out_6473911067803269893[4] = 0;
   out_6473911067803269893[5] = 0;
   out_6473911067803269893[6] = 1;
   out_6473911067803269893[7] = 0;
   out_6473911067803269893[8] = 0;
}
void h_24(double *state, double *unused, double *out_3129326117404622252) {
   out_3129326117404622252[0] = state[4];
   out_3129326117404622252[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7886939315841678730) {
   out_7886939315841678730[0] = 0;
   out_7886939315841678730[1] = 0;
   out_7886939315841678730[2] = 0;
   out_7886939315841678730[3] = 0;
   out_7886939315841678730[4] = 1;
   out_7886939315841678730[5] = 0;
   out_7886939315841678730[6] = 0;
   out_7886939315841678730[7] = 0;
   out_7886939315841678730[8] = 0;
   out_7886939315841678730[9] = 0;
   out_7886939315841678730[10] = 0;
   out_7886939315841678730[11] = 0;
   out_7886939315841678730[12] = 0;
   out_7886939315841678730[13] = 0;
   out_7886939315841678730[14] = 1;
   out_7886939315841678730[15] = 0;
   out_7886939315841678730[16] = 0;
   out_7886939315841678730[17] = 0;
}
void h_30(double *state, double *unused, double *out_1447972028461291233) {
   out_1447972028461291233[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1946214737675661695) {
   out_1946214737675661695[0] = 0;
   out_1946214737675661695[1] = 0;
   out_1946214737675661695[2] = 0;
   out_1946214737675661695[3] = 0;
   out_1946214737675661695[4] = 1;
   out_1946214737675661695[5] = 0;
   out_1946214737675661695[6] = 0;
   out_1946214737675661695[7] = 0;
   out_1946214737675661695[8] = 0;
}
void h_26(double *state, double *unused, double *out_6449645296122136878) {
   out_6449645296122136878[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2732407748929213669) {
   out_2732407748929213669[0] = 0;
   out_2732407748929213669[1] = 0;
   out_2732407748929213669[2] = 0;
   out_2732407748929213669[3] = 0;
   out_2732407748929213669[4] = 0;
   out_2732407748929213669[5] = 0;
   out_2732407748929213669[6] = 0;
   out_2732407748929213669[7] = 1;
   out_2732407748929213669[8] = 0;
}
void h_27(double *state, double *unused, double *out_3408181414978899441) {
   out_3408181414978899441[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4169808808859604912) {
   out_4169808808859604912[0] = 0;
   out_4169808808859604912[1] = 0;
   out_4169808808859604912[2] = 0;
   out_4169808808859604912[3] = 1;
   out_4169808808859604912[4] = 0;
   out_4169808808859604912[5] = 0;
   out_4169808808859604912[6] = 0;
   out_4169808808859604912[7] = 0;
   out_4169808808859604912[8] = 0;
}
void h_29(double *state, double *unused, double *out_4484758079905623918) {
   out_4484758079905623918[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2456446081990053879) {
   out_2456446081990053879[0] = 0;
   out_2456446081990053879[1] = 1;
   out_2456446081990053879[2] = 0;
   out_2456446081990053879[3] = 0;
   out_2456446081990053879[4] = 0;
   out_2456446081990053879[5] = 0;
   out_2456446081990053879[6] = 0;
   out_2456446081990053879[7] = 0;
   out_2456446081990053879[8] = 0;
}
void h_28(double *state, double *unused, double *out_2464671562077237006) {
   out_2464671562077237006[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2625952935079476695) {
   out_2625952935079476695[0] = 1;
   out_2625952935079476695[1] = 0;
   out_2625952935079476695[2] = 0;
   out_2625952935079476695[3] = 0;
   out_2625952935079476695[4] = 0;
   out_2625952935079476695[5] = 0;
   out_2625952935079476695[6] = 0;
   out_2625952935079476695[7] = 0;
   out_2625952935079476695[8] = 0;
}
void h_31(double *state, double *unused, double *out_7878613286586457251) {
   out_7878613286586457251[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2106199646695862193) {
   out_2106199646695862193[0] = 0;
   out_2106199646695862193[1] = 0;
   out_2106199646695862193[2] = 0;
   out_2106199646695862193[3] = 0;
   out_2106199646695862193[4] = 0;
   out_2106199646695862193[5] = 0;
   out_2106199646695862193[6] = 0;
   out_2106199646695862193[7] = 0;
   out_2106199646695862193[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7293025660765852052) {
  err_fun(nom_x, delta_x, out_7293025660765852052);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3117228366012468934) {
  inv_err_fun(nom_x, true_x, out_3117228366012468934);
}
void car_H_mod_fun(double *state, double *out_1447426965170589912) {
  H_mod_fun(state, out_1447426965170589912);
}
void car_f_fun(double *state, double dt, double *out_3647186790399289701) {
  f_fun(state,  dt, out_3647186790399289701);
}
void car_F_fun(double *state, double dt, double *out_4083868303371300049) {
  F_fun(state,  dt, out_4083868303371300049);
}
void car_h_25(double *state, double *unused, double *out_2804865530302421924) {
  h_25(state, unused, out_2804865530302421924);
}
void car_H_25(double *state, double *unused, double *out_6473911067803269893) {
  H_25(state, unused, out_6473911067803269893);
}
void car_h_24(double *state, double *unused, double *out_3129326117404622252) {
  h_24(state, unused, out_3129326117404622252);
}
void car_H_24(double *state, double *unused, double *out_7886939315841678730) {
  H_24(state, unused, out_7886939315841678730);
}
void car_h_30(double *state, double *unused, double *out_1447972028461291233) {
  h_30(state, unused, out_1447972028461291233);
}
void car_H_30(double *state, double *unused, double *out_1946214737675661695) {
  H_30(state, unused, out_1946214737675661695);
}
void car_h_26(double *state, double *unused, double *out_6449645296122136878) {
  h_26(state, unused, out_6449645296122136878);
}
void car_H_26(double *state, double *unused, double *out_2732407748929213669) {
  H_26(state, unused, out_2732407748929213669);
}
void car_h_27(double *state, double *unused, double *out_3408181414978899441) {
  h_27(state, unused, out_3408181414978899441);
}
void car_H_27(double *state, double *unused, double *out_4169808808859604912) {
  H_27(state, unused, out_4169808808859604912);
}
void car_h_29(double *state, double *unused, double *out_4484758079905623918) {
  h_29(state, unused, out_4484758079905623918);
}
void car_H_29(double *state, double *unused, double *out_2456446081990053879) {
  H_29(state, unused, out_2456446081990053879);
}
void car_h_28(double *state, double *unused, double *out_2464671562077237006) {
  h_28(state, unused, out_2464671562077237006);
}
void car_H_28(double *state, double *unused, double *out_2625952935079476695) {
  H_28(state, unused, out_2625952935079476695);
}
void car_h_31(double *state, double *unused, double *out_7878613286586457251) {
  h_31(state, unused, out_7878613286586457251);
}
void car_H_31(double *state, double *unused, double *out_2106199646695862193) {
  H_31(state, unused, out_2106199646695862193);
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
