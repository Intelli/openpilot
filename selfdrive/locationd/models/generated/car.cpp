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
void err_fun(double *nom_x, double *delta_x, double *out_6895673119224316411) {
   out_6895673119224316411[0] = delta_x[0] + nom_x[0];
   out_6895673119224316411[1] = delta_x[1] + nom_x[1];
   out_6895673119224316411[2] = delta_x[2] + nom_x[2];
   out_6895673119224316411[3] = delta_x[3] + nom_x[3];
   out_6895673119224316411[4] = delta_x[4] + nom_x[4];
   out_6895673119224316411[5] = delta_x[5] + nom_x[5];
   out_6895673119224316411[6] = delta_x[6] + nom_x[6];
   out_6895673119224316411[7] = delta_x[7] + nom_x[7];
   out_6895673119224316411[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5311767461984458348) {
   out_5311767461984458348[0] = -nom_x[0] + true_x[0];
   out_5311767461984458348[1] = -nom_x[1] + true_x[1];
   out_5311767461984458348[2] = -nom_x[2] + true_x[2];
   out_5311767461984458348[3] = -nom_x[3] + true_x[3];
   out_5311767461984458348[4] = -nom_x[4] + true_x[4];
   out_5311767461984458348[5] = -nom_x[5] + true_x[5];
   out_5311767461984458348[6] = -nom_x[6] + true_x[6];
   out_5311767461984458348[7] = -nom_x[7] + true_x[7];
   out_5311767461984458348[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1742728562901466536) {
   out_1742728562901466536[0] = 1.0;
   out_1742728562901466536[1] = 0.0;
   out_1742728562901466536[2] = 0.0;
   out_1742728562901466536[3] = 0.0;
   out_1742728562901466536[4] = 0.0;
   out_1742728562901466536[5] = 0.0;
   out_1742728562901466536[6] = 0.0;
   out_1742728562901466536[7] = 0.0;
   out_1742728562901466536[8] = 0.0;
   out_1742728562901466536[9] = 0.0;
   out_1742728562901466536[10] = 1.0;
   out_1742728562901466536[11] = 0.0;
   out_1742728562901466536[12] = 0.0;
   out_1742728562901466536[13] = 0.0;
   out_1742728562901466536[14] = 0.0;
   out_1742728562901466536[15] = 0.0;
   out_1742728562901466536[16] = 0.0;
   out_1742728562901466536[17] = 0.0;
   out_1742728562901466536[18] = 0.0;
   out_1742728562901466536[19] = 0.0;
   out_1742728562901466536[20] = 1.0;
   out_1742728562901466536[21] = 0.0;
   out_1742728562901466536[22] = 0.0;
   out_1742728562901466536[23] = 0.0;
   out_1742728562901466536[24] = 0.0;
   out_1742728562901466536[25] = 0.0;
   out_1742728562901466536[26] = 0.0;
   out_1742728562901466536[27] = 0.0;
   out_1742728562901466536[28] = 0.0;
   out_1742728562901466536[29] = 0.0;
   out_1742728562901466536[30] = 1.0;
   out_1742728562901466536[31] = 0.0;
   out_1742728562901466536[32] = 0.0;
   out_1742728562901466536[33] = 0.0;
   out_1742728562901466536[34] = 0.0;
   out_1742728562901466536[35] = 0.0;
   out_1742728562901466536[36] = 0.0;
   out_1742728562901466536[37] = 0.0;
   out_1742728562901466536[38] = 0.0;
   out_1742728562901466536[39] = 0.0;
   out_1742728562901466536[40] = 1.0;
   out_1742728562901466536[41] = 0.0;
   out_1742728562901466536[42] = 0.0;
   out_1742728562901466536[43] = 0.0;
   out_1742728562901466536[44] = 0.0;
   out_1742728562901466536[45] = 0.0;
   out_1742728562901466536[46] = 0.0;
   out_1742728562901466536[47] = 0.0;
   out_1742728562901466536[48] = 0.0;
   out_1742728562901466536[49] = 0.0;
   out_1742728562901466536[50] = 1.0;
   out_1742728562901466536[51] = 0.0;
   out_1742728562901466536[52] = 0.0;
   out_1742728562901466536[53] = 0.0;
   out_1742728562901466536[54] = 0.0;
   out_1742728562901466536[55] = 0.0;
   out_1742728562901466536[56] = 0.0;
   out_1742728562901466536[57] = 0.0;
   out_1742728562901466536[58] = 0.0;
   out_1742728562901466536[59] = 0.0;
   out_1742728562901466536[60] = 1.0;
   out_1742728562901466536[61] = 0.0;
   out_1742728562901466536[62] = 0.0;
   out_1742728562901466536[63] = 0.0;
   out_1742728562901466536[64] = 0.0;
   out_1742728562901466536[65] = 0.0;
   out_1742728562901466536[66] = 0.0;
   out_1742728562901466536[67] = 0.0;
   out_1742728562901466536[68] = 0.0;
   out_1742728562901466536[69] = 0.0;
   out_1742728562901466536[70] = 1.0;
   out_1742728562901466536[71] = 0.0;
   out_1742728562901466536[72] = 0.0;
   out_1742728562901466536[73] = 0.0;
   out_1742728562901466536[74] = 0.0;
   out_1742728562901466536[75] = 0.0;
   out_1742728562901466536[76] = 0.0;
   out_1742728562901466536[77] = 0.0;
   out_1742728562901466536[78] = 0.0;
   out_1742728562901466536[79] = 0.0;
   out_1742728562901466536[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6526476796425115344) {
   out_6526476796425115344[0] = state[0];
   out_6526476796425115344[1] = state[1];
   out_6526476796425115344[2] = state[2];
   out_6526476796425115344[3] = state[3];
   out_6526476796425115344[4] = state[4];
   out_6526476796425115344[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6526476796425115344[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6526476796425115344[7] = state[7];
   out_6526476796425115344[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6139522197160662754) {
   out_6139522197160662754[0] = 1;
   out_6139522197160662754[1] = 0;
   out_6139522197160662754[2] = 0;
   out_6139522197160662754[3] = 0;
   out_6139522197160662754[4] = 0;
   out_6139522197160662754[5] = 0;
   out_6139522197160662754[6] = 0;
   out_6139522197160662754[7] = 0;
   out_6139522197160662754[8] = 0;
   out_6139522197160662754[9] = 0;
   out_6139522197160662754[10] = 1;
   out_6139522197160662754[11] = 0;
   out_6139522197160662754[12] = 0;
   out_6139522197160662754[13] = 0;
   out_6139522197160662754[14] = 0;
   out_6139522197160662754[15] = 0;
   out_6139522197160662754[16] = 0;
   out_6139522197160662754[17] = 0;
   out_6139522197160662754[18] = 0;
   out_6139522197160662754[19] = 0;
   out_6139522197160662754[20] = 1;
   out_6139522197160662754[21] = 0;
   out_6139522197160662754[22] = 0;
   out_6139522197160662754[23] = 0;
   out_6139522197160662754[24] = 0;
   out_6139522197160662754[25] = 0;
   out_6139522197160662754[26] = 0;
   out_6139522197160662754[27] = 0;
   out_6139522197160662754[28] = 0;
   out_6139522197160662754[29] = 0;
   out_6139522197160662754[30] = 1;
   out_6139522197160662754[31] = 0;
   out_6139522197160662754[32] = 0;
   out_6139522197160662754[33] = 0;
   out_6139522197160662754[34] = 0;
   out_6139522197160662754[35] = 0;
   out_6139522197160662754[36] = 0;
   out_6139522197160662754[37] = 0;
   out_6139522197160662754[38] = 0;
   out_6139522197160662754[39] = 0;
   out_6139522197160662754[40] = 1;
   out_6139522197160662754[41] = 0;
   out_6139522197160662754[42] = 0;
   out_6139522197160662754[43] = 0;
   out_6139522197160662754[44] = 0;
   out_6139522197160662754[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6139522197160662754[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6139522197160662754[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6139522197160662754[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6139522197160662754[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6139522197160662754[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6139522197160662754[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6139522197160662754[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6139522197160662754[53] = -9.8100000000000005*dt;
   out_6139522197160662754[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6139522197160662754[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6139522197160662754[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6139522197160662754[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6139522197160662754[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6139522197160662754[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6139522197160662754[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6139522197160662754[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6139522197160662754[62] = 0;
   out_6139522197160662754[63] = 0;
   out_6139522197160662754[64] = 0;
   out_6139522197160662754[65] = 0;
   out_6139522197160662754[66] = 0;
   out_6139522197160662754[67] = 0;
   out_6139522197160662754[68] = 0;
   out_6139522197160662754[69] = 0;
   out_6139522197160662754[70] = 1;
   out_6139522197160662754[71] = 0;
   out_6139522197160662754[72] = 0;
   out_6139522197160662754[73] = 0;
   out_6139522197160662754[74] = 0;
   out_6139522197160662754[75] = 0;
   out_6139522197160662754[76] = 0;
   out_6139522197160662754[77] = 0;
   out_6139522197160662754[78] = 0;
   out_6139522197160662754[79] = 0;
   out_6139522197160662754[80] = 1;
}
void h_25(double *state, double *unused, double *out_4367531777895338643) {
   out_4367531777895338643[0] = state[6];
}
void H_25(double *state, double *unused, double *out_793607640872984327) {
   out_793607640872984327[0] = 0;
   out_793607640872984327[1] = 0;
   out_793607640872984327[2] = 0;
   out_793607640872984327[3] = 0;
   out_793607640872984327[4] = 0;
   out_793607640872984327[5] = 0;
   out_793607640872984327[6] = 1;
   out_793607640872984327[7] = 0;
   out_793607640872984327[8] = 0;
}
void h_24(double *state, double *unused, double *out_348485520041217042) {
   out_348485520041217042[0] = state[4];
   out_348485520041217042[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1264065122916323051) {
   out_1264065122916323051[0] = 0;
   out_1264065122916323051[1] = 0;
   out_1264065122916323051[2] = 0;
   out_1264065122916323051[3] = 0;
   out_1264065122916323051[4] = 1;
   out_1264065122916323051[5] = 0;
   out_1264065122916323051[6] = 0;
   out_1264065122916323051[7] = 0;
   out_1264065122916323051[8] = 0;
   out_1264065122916323051[9] = 0;
   out_1264065122916323051[10] = 0;
   out_1264065122916323051[11] = 0;
   out_1264065122916323051[12] = 0;
   out_1264065122916323051[13] = 0;
   out_1264065122916323051[14] = 1;
   out_1264065122916323051[15] = 0;
   out_1264065122916323051[16] = 0;
   out_1264065122916323051[17] = 0;
}
void h_30(double *state, double *unused, double *out_4210345109544209498) {
   out_4210345109544209498[0] = state[4];
}
void H_30(double *state, double *unused, double *out_922946588016224397) {
   out_922946588016224397[0] = 0;
   out_922946588016224397[1] = 0;
   out_922946588016224397[2] = 0;
   out_922946588016224397[3] = 0;
   out_922946588016224397[4] = 1;
   out_922946588016224397[5] = 0;
   out_922946588016224397[6] = 0;
   out_922946588016224397[7] = 0;
   out_922946588016224397[8] = 0;
}
void h_26(double *state, double *unused, double *out_5153854962445871933) {
   out_5153854962445871933[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4535110959747040551) {
   out_4535110959747040551[0] = 0;
   out_4535110959747040551[1] = 0;
   out_4535110959747040551[2] = 0;
   out_4535110959747040551[3] = 0;
   out_4535110959747040551[4] = 0;
   out_4535110959747040551[5] = 0;
   out_4535110959747040551[6] = 0;
   out_4535110959747040551[7] = 1;
   out_4535110959747040551[8] = 0;
}
void h_27(double *state, double *unused, double *out_1330745726451005958) {
   out_1330745726451005958[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3097709899816649308) {
   out_3097709899816649308[0] = 0;
   out_3097709899816649308[1] = 0;
   out_3097709899816649308[2] = 0;
   out_3097709899816649308[3] = 1;
   out_3097709899816649308[4] = 0;
   out_3097709899816649308[5] = 0;
   out_3097709899816649308[6] = 0;
   out_3097709899816649308[7] = 0;
   out_3097709899816649308[8] = 0;
}
void h_29(double *state, double *unused, double *out_5440089499899344978) {
   out_5440089499899344978[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4811072626686200341) {
   out_4811072626686200341[0] = 0;
   out_4811072626686200341[1] = 1;
   out_4811072626686200341[2] = 0;
   out_4811072626686200341[3] = 0;
   out_4811072626686200341[4] = 0;
   out_4811072626686200341[5] = 0;
   out_4811072626686200341[6] = 0;
   out_4811072626686200341[7] = 0;
   out_4811072626686200341[8] = 0;
}
void h_28(double *state, double *unused, double *out_6332418994111851603) {
   out_6332418994111851603[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2847442355120874090) {
   out_2847442355120874090[0] = 1;
   out_2847442355120874090[1] = 0;
   out_2847442355120874090[2] = 0;
   out_2847442355120874090[3] = 0;
   out_2847442355120874090[4] = 0;
   out_2847442355120874090[5] = 0;
   out_2847442355120874090[6] = 0;
   out_2847442355120874090[7] = 0;
   out_2847442355120874090[8] = 0;
}
void h_31(double *state, double *unused, double *out_2220296148580956520) {
   out_2220296148580956520[0] = state[8];
}
void H_31(double *state, double *unused, double *out_762961678996023899) {
   out_762961678996023899[0] = 0;
   out_762961678996023899[1] = 0;
   out_762961678996023899[2] = 0;
   out_762961678996023899[3] = 0;
   out_762961678996023899[4] = 0;
   out_762961678996023899[5] = 0;
   out_762961678996023899[6] = 0;
   out_762961678996023899[7] = 0;
   out_762961678996023899[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6895673119224316411) {
  err_fun(nom_x, delta_x, out_6895673119224316411);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5311767461984458348) {
  inv_err_fun(nom_x, true_x, out_5311767461984458348);
}
void car_H_mod_fun(double *state, double *out_1742728562901466536) {
  H_mod_fun(state, out_1742728562901466536);
}
void car_f_fun(double *state, double dt, double *out_6526476796425115344) {
  f_fun(state,  dt, out_6526476796425115344);
}
void car_F_fun(double *state, double dt, double *out_6139522197160662754) {
  F_fun(state,  dt, out_6139522197160662754);
}
void car_h_25(double *state, double *unused, double *out_4367531777895338643) {
  h_25(state, unused, out_4367531777895338643);
}
void car_H_25(double *state, double *unused, double *out_793607640872984327) {
  H_25(state, unused, out_793607640872984327);
}
void car_h_24(double *state, double *unused, double *out_348485520041217042) {
  h_24(state, unused, out_348485520041217042);
}
void car_H_24(double *state, double *unused, double *out_1264065122916323051) {
  H_24(state, unused, out_1264065122916323051);
}
void car_h_30(double *state, double *unused, double *out_4210345109544209498) {
  h_30(state, unused, out_4210345109544209498);
}
void car_H_30(double *state, double *unused, double *out_922946588016224397) {
  H_30(state, unused, out_922946588016224397);
}
void car_h_26(double *state, double *unused, double *out_5153854962445871933) {
  h_26(state, unused, out_5153854962445871933);
}
void car_H_26(double *state, double *unused, double *out_4535110959747040551) {
  H_26(state, unused, out_4535110959747040551);
}
void car_h_27(double *state, double *unused, double *out_1330745726451005958) {
  h_27(state, unused, out_1330745726451005958);
}
void car_H_27(double *state, double *unused, double *out_3097709899816649308) {
  H_27(state, unused, out_3097709899816649308);
}
void car_h_29(double *state, double *unused, double *out_5440089499899344978) {
  h_29(state, unused, out_5440089499899344978);
}
void car_H_29(double *state, double *unused, double *out_4811072626686200341) {
  H_29(state, unused, out_4811072626686200341);
}
void car_h_28(double *state, double *unused, double *out_6332418994111851603) {
  h_28(state, unused, out_6332418994111851603);
}
void car_H_28(double *state, double *unused, double *out_2847442355120874090) {
  H_28(state, unused, out_2847442355120874090);
}
void car_h_31(double *state, double *unused, double *out_2220296148580956520) {
  h_31(state, unused, out_2220296148580956520);
}
void car_H_31(double *state, double *unused, double *out_762961678996023899) {
  H_31(state, unused, out_762961678996023899);
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
