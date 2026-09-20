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
void err_fun(double *nom_x, double *delta_x, double *out_3116950613086029289) {
   out_3116950613086029289[0] = delta_x[0] + nom_x[0];
   out_3116950613086029289[1] = delta_x[1] + nom_x[1];
   out_3116950613086029289[2] = delta_x[2] + nom_x[2];
   out_3116950613086029289[3] = delta_x[3] + nom_x[3];
   out_3116950613086029289[4] = delta_x[4] + nom_x[4];
   out_3116950613086029289[5] = delta_x[5] + nom_x[5];
   out_3116950613086029289[6] = delta_x[6] + nom_x[6];
   out_3116950613086029289[7] = delta_x[7] + nom_x[7];
   out_3116950613086029289[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8816218489066620773) {
   out_8816218489066620773[0] = -nom_x[0] + true_x[0];
   out_8816218489066620773[1] = -nom_x[1] + true_x[1];
   out_8816218489066620773[2] = -nom_x[2] + true_x[2];
   out_8816218489066620773[3] = -nom_x[3] + true_x[3];
   out_8816218489066620773[4] = -nom_x[4] + true_x[4];
   out_8816218489066620773[5] = -nom_x[5] + true_x[5];
   out_8816218489066620773[6] = -nom_x[6] + true_x[6];
   out_8816218489066620773[7] = -nom_x[7] + true_x[7];
   out_8816218489066620773[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4584714039641352360) {
   out_4584714039641352360[0] = 1.0;
   out_4584714039641352360[1] = 0.0;
   out_4584714039641352360[2] = 0.0;
   out_4584714039641352360[3] = 0.0;
   out_4584714039641352360[4] = 0.0;
   out_4584714039641352360[5] = 0.0;
   out_4584714039641352360[6] = 0.0;
   out_4584714039641352360[7] = 0.0;
   out_4584714039641352360[8] = 0.0;
   out_4584714039641352360[9] = 0.0;
   out_4584714039641352360[10] = 1.0;
   out_4584714039641352360[11] = 0.0;
   out_4584714039641352360[12] = 0.0;
   out_4584714039641352360[13] = 0.0;
   out_4584714039641352360[14] = 0.0;
   out_4584714039641352360[15] = 0.0;
   out_4584714039641352360[16] = 0.0;
   out_4584714039641352360[17] = 0.0;
   out_4584714039641352360[18] = 0.0;
   out_4584714039641352360[19] = 0.0;
   out_4584714039641352360[20] = 1.0;
   out_4584714039641352360[21] = 0.0;
   out_4584714039641352360[22] = 0.0;
   out_4584714039641352360[23] = 0.0;
   out_4584714039641352360[24] = 0.0;
   out_4584714039641352360[25] = 0.0;
   out_4584714039641352360[26] = 0.0;
   out_4584714039641352360[27] = 0.0;
   out_4584714039641352360[28] = 0.0;
   out_4584714039641352360[29] = 0.0;
   out_4584714039641352360[30] = 1.0;
   out_4584714039641352360[31] = 0.0;
   out_4584714039641352360[32] = 0.0;
   out_4584714039641352360[33] = 0.0;
   out_4584714039641352360[34] = 0.0;
   out_4584714039641352360[35] = 0.0;
   out_4584714039641352360[36] = 0.0;
   out_4584714039641352360[37] = 0.0;
   out_4584714039641352360[38] = 0.0;
   out_4584714039641352360[39] = 0.0;
   out_4584714039641352360[40] = 1.0;
   out_4584714039641352360[41] = 0.0;
   out_4584714039641352360[42] = 0.0;
   out_4584714039641352360[43] = 0.0;
   out_4584714039641352360[44] = 0.0;
   out_4584714039641352360[45] = 0.0;
   out_4584714039641352360[46] = 0.0;
   out_4584714039641352360[47] = 0.0;
   out_4584714039641352360[48] = 0.0;
   out_4584714039641352360[49] = 0.0;
   out_4584714039641352360[50] = 1.0;
   out_4584714039641352360[51] = 0.0;
   out_4584714039641352360[52] = 0.0;
   out_4584714039641352360[53] = 0.0;
   out_4584714039641352360[54] = 0.0;
   out_4584714039641352360[55] = 0.0;
   out_4584714039641352360[56] = 0.0;
   out_4584714039641352360[57] = 0.0;
   out_4584714039641352360[58] = 0.0;
   out_4584714039641352360[59] = 0.0;
   out_4584714039641352360[60] = 1.0;
   out_4584714039641352360[61] = 0.0;
   out_4584714039641352360[62] = 0.0;
   out_4584714039641352360[63] = 0.0;
   out_4584714039641352360[64] = 0.0;
   out_4584714039641352360[65] = 0.0;
   out_4584714039641352360[66] = 0.0;
   out_4584714039641352360[67] = 0.0;
   out_4584714039641352360[68] = 0.0;
   out_4584714039641352360[69] = 0.0;
   out_4584714039641352360[70] = 1.0;
   out_4584714039641352360[71] = 0.0;
   out_4584714039641352360[72] = 0.0;
   out_4584714039641352360[73] = 0.0;
   out_4584714039641352360[74] = 0.0;
   out_4584714039641352360[75] = 0.0;
   out_4584714039641352360[76] = 0.0;
   out_4584714039641352360[77] = 0.0;
   out_4584714039641352360[78] = 0.0;
   out_4584714039641352360[79] = 0.0;
   out_4584714039641352360[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7251150553106896463) {
   out_7251150553106896463[0] = state[0];
   out_7251150553106896463[1] = state[1];
   out_7251150553106896463[2] = state[2];
   out_7251150553106896463[3] = state[3];
   out_7251150553106896463[4] = state[4];
   out_7251150553106896463[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7251150553106896463[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7251150553106896463[7] = state[7];
   out_7251150553106896463[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2775352329421248203) {
   out_2775352329421248203[0] = 1;
   out_2775352329421248203[1] = 0;
   out_2775352329421248203[2] = 0;
   out_2775352329421248203[3] = 0;
   out_2775352329421248203[4] = 0;
   out_2775352329421248203[5] = 0;
   out_2775352329421248203[6] = 0;
   out_2775352329421248203[7] = 0;
   out_2775352329421248203[8] = 0;
   out_2775352329421248203[9] = 0;
   out_2775352329421248203[10] = 1;
   out_2775352329421248203[11] = 0;
   out_2775352329421248203[12] = 0;
   out_2775352329421248203[13] = 0;
   out_2775352329421248203[14] = 0;
   out_2775352329421248203[15] = 0;
   out_2775352329421248203[16] = 0;
   out_2775352329421248203[17] = 0;
   out_2775352329421248203[18] = 0;
   out_2775352329421248203[19] = 0;
   out_2775352329421248203[20] = 1;
   out_2775352329421248203[21] = 0;
   out_2775352329421248203[22] = 0;
   out_2775352329421248203[23] = 0;
   out_2775352329421248203[24] = 0;
   out_2775352329421248203[25] = 0;
   out_2775352329421248203[26] = 0;
   out_2775352329421248203[27] = 0;
   out_2775352329421248203[28] = 0;
   out_2775352329421248203[29] = 0;
   out_2775352329421248203[30] = 1;
   out_2775352329421248203[31] = 0;
   out_2775352329421248203[32] = 0;
   out_2775352329421248203[33] = 0;
   out_2775352329421248203[34] = 0;
   out_2775352329421248203[35] = 0;
   out_2775352329421248203[36] = 0;
   out_2775352329421248203[37] = 0;
   out_2775352329421248203[38] = 0;
   out_2775352329421248203[39] = 0;
   out_2775352329421248203[40] = 1;
   out_2775352329421248203[41] = 0;
   out_2775352329421248203[42] = 0;
   out_2775352329421248203[43] = 0;
   out_2775352329421248203[44] = 0;
   out_2775352329421248203[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2775352329421248203[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2775352329421248203[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2775352329421248203[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2775352329421248203[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2775352329421248203[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2775352329421248203[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2775352329421248203[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2775352329421248203[53] = -9.8100000000000005*dt;
   out_2775352329421248203[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2775352329421248203[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2775352329421248203[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2775352329421248203[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2775352329421248203[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2775352329421248203[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2775352329421248203[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2775352329421248203[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2775352329421248203[62] = 0;
   out_2775352329421248203[63] = 0;
   out_2775352329421248203[64] = 0;
   out_2775352329421248203[65] = 0;
   out_2775352329421248203[66] = 0;
   out_2775352329421248203[67] = 0;
   out_2775352329421248203[68] = 0;
   out_2775352329421248203[69] = 0;
   out_2775352329421248203[70] = 1;
   out_2775352329421248203[71] = 0;
   out_2775352329421248203[72] = 0;
   out_2775352329421248203[73] = 0;
   out_2775352329421248203[74] = 0;
   out_2775352329421248203[75] = 0;
   out_2775352329421248203[76] = 0;
   out_2775352329421248203[77] = 0;
   out_2775352329421248203[78] = 0;
   out_2775352329421248203[79] = 0;
   out_2775352329421248203[80] = 1;
}
void h_25(double *state, double *unused, double *out_8133229711243772136) {
   out_8133229711243772136[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4608474186270884877) {
   out_4608474186270884877[0] = 0;
   out_4608474186270884877[1] = 0;
   out_4608474186270884877[2] = 0;
   out_4608474186270884877[3] = 0;
   out_4608474186270884877[4] = 0;
   out_4608474186270884877[5] = 0;
   out_4608474186270884877[6] = 1;
   out_4608474186270884877[7] = 0;
   out_4608474186270884877[8] = 0;
}
void h_24(double *state, double *unused, double *out_2915127492452882109) {
   out_2915127492452882109[0] = state[4];
   out_2915127492452882109[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2045731271837300880) {
   out_2045731271837300880[0] = 0;
   out_2045731271837300880[1] = 0;
   out_2045731271837300880[2] = 0;
   out_2045731271837300880[3] = 0;
   out_2045731271837300880[4] = 1;
   out_2045731271837300880[5] = 0;
   out_2045731271837300880[6] = 0;
   out_2045731271837300880[7] = 0;
   out_2045731271837300880[8] = 0;
   out_2045731271837300880[9] = 0;
   out_2045731271837300880[10] = 0;
   out_2045731271837300880[11] = 0;
   out_2045731271837300880[12] = 0;
   out_2045731271837300880[13] = 0;
   out_2045731271837300880[14] = 1;
   out_2045731271837300880[15] = 0;
   out_2045731271837300880[16] = 0;
   out_2045731271837300880[17] = 0;
}
void h_30(double *state, double *unused, double *out_2852955598216891155) {
   out_2852955598216891155[0] = state[4];
}
void H_30(double *state, double *unused, double *out_9136170516398493075) {
   out_9136170516398493075[0] = 0;
   out_9136170516398493075[1] = 0;
   out_9136170516398493075[2] = 0;
   out_9136170516398493075[3] = 0;
   out_9136170516398493075[4] = 1;
   out_9136170516398493075[5] = 0;
   out_9136170516398493075[6] = 0;
   out_9136170516398493075[7] = 0;
   out_9136170516398493075[8] = 0;
}
void h_26(double *state, double *unused, double *out_9108780320175938409) {
   out_9108780320175938409[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8349977505144941101) {
   out_8349977505144941101[0] = 0;
   out_8349977505144941101[1] = 0;
   out_8349977505144941101[2] = 0;
   out_8349977505144941101[3] = 0;
   out_8349977505144941101[4] = 0;
   out_8349977505144941101[5] = 0;
   out_8349977505144941101[6] = 0;
   out_8349977505144941101[7] = 1;
   out_8349977505144941101[8] = 0;
}
void h_27(double *state, double *unused, double *out_2907322495408447189) {
   out_2907322495408447189[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6912576445214549858) {
   out_6912576445214549858[0] = 0;
   out_6912576445214549858[1] = 0;
   out_6912576445214549858[2] = 0;
   out_6912576445214549858[3] = 1;
   out_6912576445214549858[4] = 0;
   out_6912576445214549858[5] = 0;
   out_6912576445214549858[6] = 0;
   out_6912576445214549858[7] = 0;
   out_6912576445214549858[8] = 0;
}
void h_29(double *state, double *unused, double *out_7854628865877736800) {
   out_7854628865877736800[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8625939172084100891) {
   out_8625939172084100891[0] = 0;
   out_8625939172084100891[1] = 1;
   out_8625939172084100891[2] = 0;
   out_8625939172084100891[3] = 0;
   out_8625939172084100891[4] = 0;
   out_8625939172084100891[5] = 0;
   out_8625939172084100891[6] = 0;
   out_8625939172084100891[7] = 0;
   out_8625939172084100891[8] = 0;
}
void h_28(double *state, double *unused, double *out_5511727816217144840) {
   out_5511727816217144840[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6662308900518774640) {
   out_6662308900518774640[0] = 1;
   out_6662308900518774640[1] = 0;
   out_6662308900518774640[2] = 0;
   out_6662308900518774640[3] = 0;
   out_6662308900518774640[4] = 0;
   out_6662308900518774640[5] = 0;
   out_6662308900518774640[6] = 0;
   out_6662308900518774640[7] = 0;
   out_6662308900518774640[8] = 0;
}
void h_31(double *state, double *unused, double *out_6676064834211757130) {
   out_6676064834211757130[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4577828224393924449) {
   out_4577828224393924449[0] = 0;
   out_4577828224393924449[1] = 0;
   out_4577828224393924449[2] = 0;
   out_4577828224393924449[3] = 0;
   out_4577828224393924449[4] = 0;
   out_4577828224393924449[5] = 0;
   out_4577828224393924449[6] = 0;
   out_4577828224393924449[7] = 0;
   out_4577828224393924449[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3116950613086029289) {
  err_fun(nom_x, delta_x, out_3116950613086029289);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8816218489066620773) {
  inv_err_fun(nom_x, true_x, out_8816218489066620773);
}
void car_H_mod_fun(double *state, double *out_4584714039641352360) {
  H_mod_fun(state, out_4584714039641352360);
}
void car_f_fun(double *state, double dt, double *out_7251150553106896463) {
  f_fun(state,  dt, out_7251150553106896463);
}
void car_F_fun(double *state, double dt, double *out_2775352329421248203) {
  F_fun(state,  dt, out_2775352329421248203);
}
void car_h_25(double *state, double *unused, double *out_8133229711243772136) {
  h_25(state, unused, out_8133229711243772136);
}
void car_H_25(double *state, double *unused, double *out_4608474186270884877) {
  H_25(state, unused, out_4608474186270884877);
}
void car_h_24(double *state, double *unused, double *out_2915127492452882109) {
  h_24(state, unused, out_2915127492452882109);
}
void car_H_24(double *state, double *unused, double *out_2045731271837300880) {
  H_24(state, unused, out_2045731271837300880);
}
void car_h_30(double *state, double *unused, double *out_2852955598216891155) {
  h_30(state, unused, out_2852955598216891155);
}
void car_H_30(double *state, double *unused, double *out_9136170516398493075) {
  H_30(state, unused, out_9136170516398493075);
}
void car_h_26(double *state, double *unused, double *out_9108780320175938409) {
  h_26(state, unused, out_9108780320175938409);
}
void car_H_26(double *state, double *unused, double *out_8349977505144941101) {
  H_26(state, unused, out_8349977505144941101);
}
void car_h_27(double *state, double *unused, double *out_2907322495408447189) {
  h_27(state, unused, out_2907322495408447189);
}
void car_H_27(double *state, double *unused, double *out_6912576445214549858) {
  H_27(state, unused, out_6912576445214549858);
}
void car_h_29(double *state, double *unused, double *out_7854628865877736800) {
  h_29(state, unused, out_7854628865877736800);
}
void car_H_29(double *state, double *unused, double *out_8625939172084100891) {
  H_29(state, unused, out_8625939172084100891);
}
void car_h_28(double *state, double *unused, double *out_5511727816217144840) {
  h_28(state, unused, out_5511727816217144840);
}
void car_H_28(double *state, double *unused, double *out_6662308900518774640) {
  H_28(state, unused, out_6662308900518774640);
}
void car_h_31(double *state, double *unused, double *out_6676064834211757130) {
  h_31(state, unused, out_6676064834211757130);
}
void car_H_31(double *state, double *unused, double *out_4577828224393924449) {
  H_31(state, unused, out_4577828224393924449);
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
