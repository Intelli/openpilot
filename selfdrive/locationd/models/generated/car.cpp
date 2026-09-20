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
void err_fun(double *nom_x, double *delta_x, double *out_905618509759065814) {
   out_905618509759065814[0] = delta_x[0] + nom_x[0];
   out_905618509759065814[1] = delta_x[1] + nom_x[1];
   out_905618509759065814[2] = delta_x[2] + nom_x[2];
   out_905618509759065814[3] = delta_x[3] + nom_x[3];
   out_905618509759065814[4] = delta_x[4] + nom_x[4];
   out_905618509759065814[5] = delta_x[5] + nom_x[5];
   out_905618509759065814[6] = delta_x[6] + nom_x[6];
   out_905618509759065814[7] = delta_x[7] + nom_x[7];
   out_905618509759065814[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1454872133267434449) {
   out_1454872133267434449[0] = -nom_x[0] + true_x[0];
   out_1454872133267434449[1] = -nom_x[1] + true_x[1];
   out_1454872133267434449[2] = -nom_x[2] + true_x[2];
   out_1454872133267434449[3] = -nom_x[3] + true_x[3];
   out_1454872133267434449[4] = -nom_x[4] + true_x[4];
   out_1454872133267434449[5] = -nom_x[5] + true_x[5];
   out_1454872133267434449[6] = -nom_x[6] + true_x[6];
   out_1454872133267434449[7] = -nom_x[7] + true_x[7];
   out_1454872133267434449[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7905035211705523546) {
   out_7905035211705523546[0] = 1.0;
   out_7905035211705523546[1] = 0.0;
   out_7905035211705523546[2] = 0.0;
   out_7905035211705523546[3] = 0.0;
   out_7905035211705523546[4] = 0.0;
   out_7905035211705523546[5] = 0.0;
   out_7905035211705523546[6] = 0.0;
   out_7905035211705523546[7] = 0.0;
   out_7905035211705523546[8] = 0.0;
   out_7905035211705523546[9] = 0.0;
   out_7905035211705523546[10] = 1.0;
   out_7905035211705523546[11] = 0.0;
   out_7905035211705523546[12] = 0.0;
   out_7905035211705523546[13] = 0.0;
   out_7905035211705523546[14] = 0.0;
   out_7905035211705523546[15] = 0.0;
   out_7905035211705523546[16] = 0.0;
   out_7905035211705523546[17] = 0.0;
   out_7905035211705523546[18] = 0.0;
   out_7905035211705523546[19] = 0.0;
   out_7905035211705523546[20] = 1.0;
   out_7905035211705523546[21] = 0.0;
   out_7905035211705523546[22] = 0.0;
   out_7905035211705523546[23] = 0.0;
   out_7905035211705523546[24] = 0.0;
   out_7905035211705523546[25] = 0.0;
   out_7905035211705523546[26] = 0.0;
   out_7905035211705523546[27] = 0.0;
   out_7905035211705523546[28] = 0.0;
   out_7905035211705523546[29] = 0.0;
   out_7905035211705523546[30] = 1.0;
   out_7905035211705523546[31] = 0.0;
   out_7905035211705523546[32] = 0.0;
   out_7905035211705523546[33] = 0.0;
   out_7905035211705523546[34] = 0.0;
   out_7905035211705523546[35] = 0.0;
   out_7905035211705523546[36] = 0.0;
   out_7905035211705523546[37] = 0.0;
   out_7905035211705523546[38] = 0.0;
   out_7905035211705523546[39] = 0.0;
   out_7905035211705523546[40] = 1.0;
   out_7905035211705523546[41] = 0.0;
   out_7905035211705523546[42] = 0.0;
   out_7905035211705523546[43] = 0.0;
   out_7905035211705523546[44] = 0.0;
   out_7905035211705523546[45] = 0.0;
   out_7905035211705523546[46] = 0.0;
   out_7905035211705523546[47] = 0.0;
   out_7905035211705523546[48] = 0.0;
   out_7905035211705523546[49] = 0.0;
   out_7905035211705523546[50] = 1.0;
   out_7905035211705523546[51] = 0.0;
   out_7905035211705523546[52] = 0.0;
   out_7905035211705523546[53] = 0.0;
   out_7905035211705523546[54] = 0.0;
   out_7905035211705523546[55] = 0.0;
   out_7905035211705523546[56] = 0.0;
   out_7905035211705523546[57] = 0.0;
   out_7905035211705523546[58] = 0.0;
   out_7905035211705523546[59] = 0.0;
   out_7905035211705523546[60] = 1.0;
   out_7905035211705523546[61] = 0.0;
   out_7905035211705523546[62] = 0.0;
   out_7905035211705523546[63] = 0.0;
   out_7905035211705523546[64] = 0.0;
   out_7905035211705523546[65] = 0.0;
   out_7905035211705523546[66] = 0.0;
   out_7905035211705523546[67] = 0.0;
   out_7905035211705523546[68] = 0.0;
   out_7905035211705523546[69] = 0.0;
   out_7905035211705523546[70] = 1.0;
   out_7905035211705523546[71] = 0.0;
   out_7905035211705523546[72] = 0.0;
   out_7905035211705523546[73] = 0.0;
   out_7905035211705523546[74] = 0.0;
   out_7905035211705523546[75] = 0.0;
   out_7905035211705523546[76] = 0.0;
   out_7905035211705523546[77] = 0.0;
   out_7905035211705523546[78] = 0.0;
   out_7905035211705523546[79] = 0.0;
   out_7905035211705523546[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5670425325742993501) {
   out_5670425325742993501[0] = state[0];
   out_5670425325742993501[1] = state[1];
   out_5670425325742993501[2] = state[2];
   out_5670425325742993501[3] = state[3];
   out_5670425325742993501[4] = state[4];
   out_5670425325742993501[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5670425325742993501[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5670425325742993501[7] = state[7];
   out_5670425325742993501[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4094785554680913164) {
   out_4094785554680913164[0] = 1;
   out_4094785554680913164[1] = 0;
   out_4094785554680913164[2] = 0;
   out_4094785554680913164[3] = 0;
   out_4094785554680913164[4] = 0;
   out_4094785554680913164[5] = 0;
   out_4094785554680913164[6] = 0;
   out_4094785554680913164[7] = 0;
   out_4094785554680913164[8] = 0;
   out_4094785554680913164[9] = 0;
   out_4094785554680913164[10] = 1;
   out_4094785554680913164[11] = 0;
   out_4094785554680913164[12] = 0;
   out_4094785554680913164[13] = 0;
   out_4094785554680913164[14] = 0;
   out_4094785554680913164[15] = 0;
   out_4094785554680913164[16] = 0;
   out_4094785554680913164[17] = 0;
   out_4094785554680913164[18] = 0;
   out_4094785554680913164[19] = 0;
   out_4094785554680913164[20] = 1;
   out_4094785554680913164[21] = 0;
   out_4094785554680913164[22] = 0;
   out_4094785554680913164[23] = 0;
   out_4094785554680913164[24] = 0;
   out_4094785554680913164[25] = 0;
   out_4094785554680913164[26] = 0;
   out_4094785554680913164[27] = 0;
   out_4094785554680913164[28] = 0;
   out_4094785554680913164[29] = 0;
   out_4094785554680913164[30] = 1;
   out_4094785554680913164[31] = 0;
   out_4094785554680913164[32] = 0;
   out_4094785554680913164[33] = 0;
   out_4094785554680913164[34] = 0;
   out_4094785554680913164[35] = 0;
   out_4094785554680913164[36] = 0;
   out_4094785554680913164[37] = 0;
   out_4094785554680913164[38] = 0;
   out_4094785554680913164[39] = 0;
   out_4094785554680913164[40] = 1;
   out_4094785554680913164[41] = 0;
   out_4094785554680913164[42] = 0;
   out_4094785554680913164[43] = 0;
   out_4094785554680913164[44] = 0;
   out_4094785554680913164[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4094785554680913164[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4094785554680913164[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4094785554680913164[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4094785554680913164[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4094785554680913164[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4094785554680913164[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4094785554680913164[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4094785554680913164[53] = -9.8100000000000005*dt;
   out_4094785554680913164[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4094785554680913164[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4094785554680913164[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4094785554680913164[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4094785554680913164[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4094785554680913164[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4094785554680913164[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4094785554680913164[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4094785554680913164[62] = 0;
   out_4094785554680913164[63] = 0;
   out_4094785554680913164[64] = 0;
   out_4094785554680913164[65] = 0;
   out_4094785554680913164[66] = 0;
   out_4094785554680913164[67] = 0;
   out_4094785554680913164[68] = 0;
   out_4094785554680913164[69] = 0;
   out_4094785554680913164[70] = 1;
   out_4094785554680913164[71] = 0;
   out_4094785554680913164[72] = 0;
   out_4094785554680913164[73] = 0;
   out_4094785554680913164[74] = 0;
   out_4094785554680913164[75] = 0;
   out_4094785554680913164[76] = 0;
   out_4094785554680913164[77] = 0;
   out_4094785554680913164[78] = 0;
   out_4094785554680913164[79] = 0;
   out_4094785554680913164[80] = 1;
}
void h_25(double *state, double *unused, double *out_6142268501048737737) {
   out_6142268501048737737[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4382054561716031869) {
   out_4382054561716031869[0] = 0;
   out_4382054561716031869[1] = 0;
   out_4382054561716031869[2] = 0;
   out_4382054561716031869[3] = 0;
   out_4382054561716031869[4] = 0;
   out_4382054561716031869[5] = 0;
   out_4382054561716031869[6] = 1;
   out_4382054561716031869[7] = 0;
   out_4382054561716031869[8] = 0;
}
void h_24(double *state, double *unused, double *out_5336528544796446006) {
   out_5336528544796446006[0] = state[4];
   out_5336528544796446006[1] = state[5];
}
void H_24(double *state, double *unused, double *out_9128563888682540903) {
   out_9128563888682540903[0] = 0;
   out_9128563888682540903[1] = 0;
   out_9128563888682540903[2] = 0;
   out_9128563888682540903[3] = 0;
   out_9128563888682540903[4] = 1;
   out_9128563888682540903[5] = 0;
   out_9128563888682540903[6] = 0;
   out_9128563888682540903[7] = 0;
   out_9128563888682540903[8] = 0;
   out_9128563888682540903[9] = 0;
   out_9128563888682540903[10] = 0;
   out_9128563888682540903[11] = 0;
   out_9128563888682540903[12] = 0;
   out_9128563888682540903[13] = 0;
   out_9128563888682540903[14] = 1;
   out_9128563888682540903[15] = 0;
   out_9128563888682540903[16] = 0;
   out_9128563888682540903[17] = 0;
}
void h_30(double *state, double *unused, double *out_2504818972794715387) {
   out_2504818972794715387[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8909750891843640067) {
   out_8909750891843640067[0] = 0;
   out_8909750891843640067[1] = 0;
   out_8909750891843640067[2] = 0;
   out_8909750891843640067[3] = 0;
   out_8909750891843640067[4] = 1;
   out_8909750891843640067[5] = 0;
   out_8909750891843640067[6] = 0;
   out_8909750891843640067[7] = 0;
   out_8909750891843640067[8] = 0;
}
void h_26(double *state, double *unused, double *out_8383104460353430475) {
   out_8383104460353430475[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8123557880590088093) {
   out_8123557880590088093[0] = 0;
   out_8123557880590088093[1] = 0;
   out_8123557880590088093[2] = 0;
   out_8123557880590088093[3] = 0;
   out_8123557880590088093[4] = 0;
   out_8123557880590088093[5] = 0;
   out_8123557880590088093[6] = 0;
   out_8123557880590088093[7] = 1;
   out_8123557880590088093[8] = 0;
}
void h_27(double *state, double *unused, double *out_5160184407713439625) {
   out_5160184407713439625[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6686156820659696850) {
   out_6686156820659696850[0] = 0;
   out_6686156820659696850[1] = 0;
   out_6686156820659696850[2] = 0;
   out_6686156820659696850[3] = 1;
   out_6686156820659696850[4] = 0;
   out_6686156820659696850[5] = 0;
   out_6686156820659696850[6] = 0;
   out_6686156820659696850[7] = 0;
   out_6686156820659696850[8] = 0;
}
void h_29(double *state, double *unused, double *out_2496854294866130258) {
   out_2496854294866130258[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8399519547529247883) {
   out_8399519547529247883[0] = 0;
   out_8399519547529247883[1] = 1;
   out_8399519547529247883[2] = 0;
   out_8399519547529247883[3] = 0;
   out_8399519547529247883[4] = 0;
   out_8399519547529247883[5] = 0;
   out_8399519547529247883[6] = 0;
   out_8399519547529247883[7] = 0;
   out_8399519547529247883[8] = 0;
}
void h_28(double *state, double *unused, double *out_158511140052593980) {
   out_158511140052593980[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6435889275963921632) {
   out_6435889275963921632[0] = 1;
   out_6435889275963921632[1] = 0;
   out_6435889275963921632[2] = 0;
   out_6435889275963921632[3] = 0;
   out_6435889275963921632[4] = 0;
   out_6435889275963921632[5] = 0;
   out_6435889275963921632[6] = 0;
   out_6435889275963921632[7] = 0;
   out_6435889275963921632[8] = 0;
}
void h_31(double *state, double *unused, double *out_2622826366728092131) {
   out_2622826366728092131[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4351408599839071441) {
   out_4351408599839071441[0] = 0;
   out_4351408599839071441[1] = 0;
   out_4351408599839071441[2] = 0;
   out_4351408599839071441[3] = 0;
   out_4351408599839071441[4] = 0;
   out_4351408599839071441[5] = 0;
   out_4351408599839071441[6] = 0;
   out_4351408599839071441[7] = 0;
   out_4351408599839071441[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_905618509759065814) {
  err_fun(nom_x, delta_x, out_905618509759065814);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1454872133267434449) {
  inv_err_fun(nom_x, true_x, out_1454872133267434449);
}
void car_H_mod_fun(double *state, double *out_7905035211705523546) {
  H_mod_fun(state, out_7905035211705523546);
}
void car_f_fun(double *state, double dt, double *out_5670425325742993501) {
  f_fun(state,  dt, out_5670425325742993501);
}
void car_F_fun(double *state, double dt, double *out_4094785554680913164) {
  F_fun(state,  dt, out_4094785554680913164);
}
void car_h_25(double *state, double *unused, double *out_6142268501048737737) {
  h_25(state, unused, out_6142268501048737737);
}
void car_H_25(double *state, double *unused, double *out_4382054561716031869) {
  H_25(state, unused, out_4382054561716031869);
}
void car_h_24(double *state, double *unused, double *out_5336528544796446006) {
  h_24(state, unused, out_5336528544796446006);
}
void car_H_24(double *state, double *unused, double *out_9128563888682540903) {
  H_24(state, unused, out_9128563888682540903);
}
void car_h_30(double *state, double *unused, double *out_2504818972794715387) {
  h_30(state, unused, out_2504818972794715387);
}
void car_H_30(double *state, double *unused, double *out_8909750891843640067) {
  H_30(state, unused, out_8909750891843640067);
}
void car_h_26(double *state, double *unused, double *out_8383104460353430475) {
  h_26(state, unused, out_8383104460353430475);
}
void car_H_26(double *state, double *unused, double *out_8123557880590088093) {
  H_26(state, unused, out_8123557880590088093);
}
void car_h_27(double *state, double *unused, double *out_5160184407713439625) {
  h_27(state, unused, out_5160184407713439625);
}
void car_H_27(double *state, double *unused, double *out_6686156820659696850) {
  H_27(state, unused, out_6686156820659696850);
}
void car_h_29(double *state, double *unused, double *out_2496854294866130258) {
  h_29(state, unused, out_2496854294866130258);
}
void car_H_29(double *state, double *unused, double *out_8399519547529247883) {
  H_29(state, unused, out_8399519547529247883);
}
void car_h_28(double *state, double *unused, double *out_158511140052593980) {
  h_28(state, unused, out_158511140052593980);
}
void car_H_28(double *state, double *unused, double *out_6435889275963921632) {
  H_28(state, unused, out_6435889275963921632);
}
void car_h_31(double *state, double *unused, double *out_2622826366728092131) {
  h_31(state, unused, out_2622826366728092131);
}
void car_H_31(double *state, double *unused, double *out_4351408599839071441) {
  H_31(state, unused, out_4351408599839071441);
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
