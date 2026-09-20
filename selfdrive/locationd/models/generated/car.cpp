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
void err_fun(double *nom_x, double *delta_x, double *out_16839997209750613) {
   out_16839997209750613[0] = delta_x[0] + nom_x[0];
   out_16839997209750613[1] = delta_x[1] + nom_x[1];
   out_16839997209750613[2] = delta_x[2] + nom_x[2];
   out_16839997209750613[3] = delta_x[3] + nom_x[3];
   out_16839997209750613[4] = delta_x[4] + nom_x[4];
   out_16839997209750613[5] = delta_x[5] + nom_x[5];
   out_16839997209750613[6] = delta_x[6] + nom_x[6];
   out_16839997209750613[7] = delta_x[7] + nom_x[7];
   out_16839997209750613[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_997850346281991640) {
   out_997850346281991640[0] = -nom_x[0] + true_x[0];
   out_997850346281991640[1] = -nom_x[1] + true_x[1];
   out_997850346281991640[2] = -nom_x[2] + true_x[2];
   out_997850346281991640[3] = -nom_x[3] + true_x[3];
   out_997850346281991640[4] = -nom_x[4] + true_x[4];
   out_997850346281991640[5] = -nom_x[5] + true_x[5];
   out_997850346281991640[6] = -nom_x[6] + true_x[6];
   out_997850346281991640[7] = -nom_x[7] + true_x[7];
   out_997850346281991640[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_793862516828139793) {
   out_793862516828139793[0] = 1.0;
   out_793862516828139793[1] = 0.0;
   out_793862516828139793[2] = 0.0;
   out_793862516828139793[3] = 0.0;
   out_793862516828139793[4] = 0.0;
   out_793862516828139793[5] = 0.0;
   out_793862516828139793[6] = 0.0;
   out_793862516828139793[7] = 0.0;
   out_793862516828139793[8] = 0.0;
   out_793862516828139793[9] = 0.0;
   out_793862516828139793[10] = 1.0;
   out_793862516828139793[11] = 0.0;
   out_793862516828139793[12] = 0.0;
   out_793862516828139793[13] = 0.0;
   out_793862516828139793[14] = 0.0;
   out_793862516828139793[15] = 0.0;
   out_793862516828139793[16] = 0.0;
   out_793862516828139793[17] = 0.0;
   out_793862516828139793[18] = 0.0;
   out_793862516828139793[19] = 0.0;
   out_793862516828139793[20] = 1.0;
   out_793862516828139793[21] = 0.0;
   out_793862516828139793[22] = 0.0;
   out_793862516828139793[23] = 0.0;
   out_793862516828139793[24] = 0.0;
   out_793862516828139793[25] = 0.0;
   out_793862516828139793[26] = 0.0;
   out_793862516828139793[27] = 0.0;
   out_793862516828139793[28] = 0.0;
   out_793862516828139793[29] = 0.0;
   out_793862516828139793[30] = 1.0;
   out_793862516828139793[31] = 0.0;
   out_793862516828139793[32] = 0.0;
   out_793862516828139793[33] = 0.0;
   out_793862516828139793[34] = 0.0;
   out_793862516828139793[35] = 0.0;
   out_793862516828139793[36] = 0.0;
   out_793862516828139793[37] = 0.0;
   out_793862516828139793[38] = 0.0;
   out_793862516828139793[39] = 0.0;
   out_793862516828139793[40] = 1.0;
   out_793862516828139793[41] = 0.0;
   out_793862516828139793[42] = 0.0;
   out_793862516828139793[43] = 0.0;
   out_793862516828139793[44] = 0.0;
   out_793862516828139793[45] = 0.0;
   out_793862516828139793[46] = 0.0;
   out_793862516828139793[47] = 0.0;
   out_793862516828139793[48] = 0.0;
   out_793862516828139793[49] = 0.0;
   out_793862516828139793[50] = 1.0;
   out_793862516828139793[51] = 0.0;
   out_793862516828139793[52] = 0.0;
   out_793862516828139793[53] = 0.0;
   out_793862516828139793[54] = 0.0;
   out_793862516828139793[55] = 0.0;
   out_793862516828139793[56] = 0.0;
   out_793862516828139793[57] = 0.0;
   out_793862516828139793[58] = 0.0;
   out_793862516828139793[59] = 0.0;
   out_793862516828139793[60] = 1.0;
   out_793862516828139793[61] = 0.0;
   out_793862516828139793[62] = 0.0;
   out_793862516828139793[63] = 0.0;
   out_793862516828139793[64] = 0.0;
   out_793862516828139793[65] = 0.0;
   out_793862516828139793[66] = 0.0;
   out_793862516828139793[67] = 0.0;
   out_793862516828139793[68] = 0.0;
   out_793862516828139793[69] = 0.0;
   out_793862516828139793[70] = 1.0;
   out_793862516828139793[71] = 0.0;
   out_793862516828139793[72] = 0.0;
   out_793862516828139793[73] = 0.0;
   out_793862516828139793[74] = 0.0;
   out_793862516828139793[75] = 0.0;
   out_793862516828139793[76] = 0.0;
   out_793862516828139793[77] = 0.0;
   out_793862516828139793[78] = 0.0;
   out_793862516828139793[79] = 0.0;
   out_793862516828139793[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7985598016111714437) {
   out_7985598016111714437[0] = state[0];
   out_7985598016111714437[1] = state[1];
   out_7985598016111714437[2] = state[2];
   out_7985598016111714437[3] = state[3];
   out_7985598016111714437[4] = state[4];
   out_7985598016111714437[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7985598016111714437[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7985598016111714437[7] = state[7];
   out_7985598016111714437[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2618723996397977550) {
   out_2618723996397977550[0] = 1;
   out_2618723996397977550[1] = 0;
   out_2618723996397977550[2] = 0;
   out_2618723996397977550[3] = 0;
   out_2618723996397977550[4] = 0;
   out_2618723996397977550[5] = 0;
   out_2618723996397977550[6] = 0;
   out_2618723996397977550[7] = 0;
   out_2618723996397977550[8] = 0;
   out_2618723996397977550[9] = 0;
   out_2618723996397977550[10] = 1;
   out_2618723996397977550[11] = 0;
   out_2618723996397977550[12] = 0;
   out_2618723996397977550[13] = 0;
   out_2618723996397977550[14] = 0;
   out_2618723996397977550[15] = 0;
   out_2618723996397977550[16] = 0;
   out_2618723996397977550[17] = 0;
   out_2618723996397977550[18] = 0;
   out_2618723996397977550[19] = 0;
   out_2618723996397977550[20] = 1;
   out_2618723996397977550[21] = 0;
   out_2618723996397977550[22] = 0;
   out_2618723996397977550[23] = 0;
   out_2618723996397977550[24] = 0;
   out_2618723996397977550[25] = 0;
   out_2618723996397977550[26] = 0;
   out_2618723996397977550[27] = 0;
   out_2618723996397977550[28] = 0;
   out_2618723996397977550[29] = 0;
   out_2618723996397977550[30] = 1;
   out_2618723996397977550[31] = 0;
   out_2618723996397977550[32] = 0;
   out_2618723996397977550[33] = 0;
   out_2618723996397977550[34] = 0;
   out_2618723996397977550[35] = 0;
   out_2618723996397977550[36] = 0;
   out_2618723996397977550[37] = 0;
   out_2618723996397977550[38] = 0;
   out_2618723996397977550[39] = 0;
   out_2618723996397977550[40] = 1;
   out_2618723996397977550[41] = 0;
   out_2618723996397977550[42] = 0;
   out_2618723996397977550[43] = 0;
   out_2618723996397977550[44] = 0;
   out_2618723996397977550[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2618723996397977550[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2618723996397977550[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2618723996397977550[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2618723996397977550[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2618723996397977550[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2618723996397977550[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2618723996397977550[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2618723996397977550[53] = -9.8100000000000005*dt;
   out_2618723996397977550[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2618723996397977550[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2618723996397977550[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2618723996397977550[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2618723996397977550[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2618723996397977550[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2618723996397977550[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2618723996397977550[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2618723996397977550[62] = 0;
   out_2618723996397977550[63] = 0;
   out_2618723996397977550[64] = 0;
   out_2618723996397977550[65] = 0;
   out_2618723996397977550[66] = 0;
   out_2618723996397977550[67] = 0;
   out_2618723996397977550[68] = 0;
   out_2618723996397977550[69] = 0;
   out_2618723996397977550[70] = 1;
   out_2618723996397977550[71] = 0;
   out_2618723996397977550[72] = 0;
   out_2618723996397977550[73] = 0;
   out_2618723996397977550[74] = 0;
   out_2618723996397977550[75] = 0;
   out_2618723996397977550[76] = 0;
   out_2618723996397977550[77] = 0;
   out_2618723996397977550[78] = 0;
   out_2618723996397977550[79] = 0;
   out_2618723996397977550[80] = 1;
}
void h_25(double *state, double *unused, double *out_2300452709025625959) {
   out_2300452709025625959[0] = state[6];
}
void H_25(double *state, double *unused, double *out_288528074627843081) {
   out_288528074627843081[0] = 0;
   out_288528074627843081[1] = 0;
   out_288528074627843081[2] = 0;
   out_288528074627843081[3] = 0;
   out_288528074627843081[4] = 0;
   out_288528074627843081[5] = 0;
   out_288528074627843081[6] = 1;
   out_288528074627843081[7] = 0;
   out_288528074627843081[8] = 0;
}
void h_24(double *state, double *unused, double *out_6637232346528830745) {
   out_6637232346528830745[0] = state[4];
   out_6637232346528830745[1] = state[5];
}
void H_24(double *state, double *unused, double *out_556468534155852318) {
   out_556468534155852318[0] = 0;
   out_556468534155852318[1] = 0;
   out_556468534155852318[2] = 0;
   out_556468534155852318[3] = 0;
   out_556468534155852318[4] = 1;
   out_556468534155852318[5] = 0;
   out_556468534155852318[6] = 0;
   out_556468534155852318[7] = 0;
   out_556468534155852318[8] = 0;
   out_556468534155852318[9] = 0;
   out_556468534155852318[10] = 0;
   out_556468534155852318[11] = 0;
   out_556468534155852318[12] = 0;
   out_556468534155852318[13] = 0;
   out_556468534155852318[14] = 1;
   out_556468534155852318[15] = 0;
   out_556468534155852318[16] = 0;
   out_556468534155852318[17] = 0;
}
void h_30(double *state, double *unused, double *out_6162136185454127611) {
   out_6162136185454127611[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6628162266863773674) {
   out_6628162266863773674[0] = 0;
   out_6628162266863773674[1] = 0;
   out_6628162266863773674[2] = 0;
   out_6628162266863773674[3] = 0;
   out_6628162266863773674[4] = 1;
   out_6628162266863773674[5] = 0;
   out_6628162266863773674[6] = 0;
   out_6628162266863773674[7] = 0;
   out_6628162266863773674[8] = 0;
}
void h_26(double *state, double *unused, double *out_3302638716248583240) {
   out_3302638716248583240[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4030031393501899305) {
   out_4030031393501899305[0] = 0;
   out_4030031393501899305[1] = 0;
   out_4030031393501899305[2] = 0;
   out_4030031393501899305[3] = 0;
   out_4030031393501899305[4] = 0;
   out_4030031393501899305[5] = 0;
   out_4030031393501899305[6] = 0;
   out_4030031393501899305[7] = 1;
   out_4030031393501899305[8] = 0;
}
void h_27(double *state, double *unused, double *out_7125747952243449215) {
   out_7125747952243449215[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4453398955063348763) {
   out_4453398955063348763[0] = 0;
   out_4453398955063348763[1] = 0;
   out_4453398955063348763[2] = 0;
   out_4453398955063348763[3] = 1;
   out_4453398955063348763[4] = 0;
   out_4453398955063348763[5] = 0;
   out_4453398955063348763[6] = 0;
   out_4453398955063348763[7] = 0;
   out_4453398955063348763[8] = 0;
}
void h_29(double *state, double *unused, double *out_7282934620594578360) {
   out_7282934620594578360[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7138393611178165858) {
   out_7138393611178165858[0] = 0;
   out_7138393611178165858[1] = 1;
   out_7138393611178165858[2] = 0;
   out_7138393611178165858[3] = 0;
   out_7138393611178165858[4] = 0;
   out_7138393611178165858[5] = 0;
   out_7138393611178165858[6] = 0;
   out_7138393611178165858[7] = 0;
   out_7138393611178165858[8] = 0;
}
void h_28(double *state, double *unused, double *out_8284210070021769716) {
   out_8284210070021769716[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2055994594108635284) {
   out_2055994594108635284[0] = 1;
   out_2055994594108635284[1] = 0;
   out_2055994594108635284[2] = 0;
   out_2055994594108635284[3] = 0;
   out_2055994594108635284[4] = 0;
   out_2055994594108635284[5] = 0;
   out_2055994594108635284[6] = 0;
   out_2055994594108635284[7] = 0;
   out_2055994594108635284[8] = 0;
}
void h_31(double *state, double *unused, double *out_268505072671038407) {
   out_268505072671038407[0] = state[8];
}
void H_31(double *state, double *unused, double *out_257882112750882653) {
   out_257882112750882653[0] = 0;
   out_257882112750882653[1] = 0;
   out_257882112750882653[2] = 0;
   out_257882112750882653[3] = 0;
   out_257882112750882653[4] = 0;
   out_257882112750882653[5] = 0;
   out_257882112750882653[6] = 0;
   out_257882112750882653[7] = 0;
   out_257882112750882653[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_16839997209750613) {
  err_fun(nom_x, delta_x, out_16839997209750613);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_997850346281991640) {
  inv_err_fun(nom_x, true_x, out_997850346281991640);
}
void car_H_mod_fun(double *state, double *out_793862516828139793) {
  H_mod_fun(state, out_793862516828139793);
}
void car_f_fun(double *state, double dt, double *out_7985598016111714437) {
  f_fun(state,  dt, out_7985598016111714437);
}
void car_F_fun(double *state, double dt, double *out_2618723996397977550) {
  F_fun(state,  dt, out_2618723996397977550);
}
void car_h_25(double *state, double *unused, double *out_2300452709025625959) {
  h_25(state, unused, out_2300452709025625959);
}
void car_H_25(double *state, double *unused, double *out_288528074627843081) {
  H_25(state, unused, out_288528074627843081);
}
void car_h_24(double *state, double *unused, double *out_6637232346528830745) {
  h_24(state, unused, out_6637232346528830745);
}
void car_H_24(double *state, double *unused, double *out_556468534155852318) {
  H_24(state, unused, out_556468534155852318);
}
void car_h_30(double *state, double *unused, double *out_6162136185454127611) {
  h_30(state, unused, out_6162136185454127611);
}
void car_H_30(double *state, double *unused, double *out_6628162266863773674) {
  H_30(state, unused, out_6628162266863773674);
}
void car_h_26(double *state, double *unused, double *out_3302638716248583240) {
  h_26(state, unused, out_3302638716248583240);
}
void car_H_26(double *state, double *unused, double *out_4030031393501899305) {
  H_26(state, unused, out_4030031393501899305);
}
void car_h_27(double *state, double *unused, double *out_7125747952243449215) {
  h_27(state, unused, out_7125747952243449215);
}
void car_H_27(double *state, double *unused, double *out_4453398955063348763) {
  H_27(state, unused, out_4453398955063348763);
}
void car_h_29(double *state, double *unused, double *out_7282934620594578360) {
  h_29(state, unused, out_7282934620594578360);
}
void car_H_29(double *state, double *unused, double *out_7138393611178165858) {
  H_29(state, unused, out_7138393611178165858);
}
void car_h_28(double *state, double *unused, double *out_8284210070021769716) {
  h_28(state, unused, out_8284210070021769716);
}
void car_H_28(double *state, double *unused, double *out_2055994594108635284) {
  H_28(state, unused, out_2055994594108635284);
}
void car_h_31(double *state, double *unused, double *out_268505072671038407) {
  h_31(state, unused, out_268505072671038407);
}
void car_H_31(double *state, double *unused, double *out_257882112750882653) {
  H_31(state, unused, out_257882112750882653);
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
