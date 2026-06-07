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
void err_fun(double *nom_x, double *delta_x, double *out_5960298151612549262) {
   out_5960298151612549262[0] = delta_x[0] + nom_x[0];
   out_5960298151612549262[1] = delta_x[1] + nom_x[1];
   out_5960298151612549262[2] = delta_x[2] + nom_x[2];
   out_5960298151612549262[3] = delta_x[3] + nom_x[3];
   out_5960298151612549262[4] = delta_x[4] + nom_x[4];
   out_5960298151612549262[5] = delta_x[5] + nom_x[5];
   out_5960298151612549262[6] = delta_x[6] + nom_x[6];
   out_5960298151612549262[7] = delta_x[7] + nom_x[7];
   out_5960298151612549262[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3713988653844672293) {
   out_3713988653844672293[0] = -nom_x[0] + true_x[0];
   out_3713988653844672293[1] = -nom_x[1] + true_x[1];
   out_3713988653844672293[2] = -nom_x[2] + true_x[2];
   out_3713988653844672293[3] = -nom_x[3] + true_x[3];
   out_3713988653844672293[4] = -nom_x[4] + true_x[4];
   out_3713988653844672293[5] = -nom_x[5] + true_x[5];
   out_3713988653844672293[6] = -nom_x[6] + true_x[6];
   out_3713988653844672293[7] = -nom_x[7] + true_x[7];
   out_3713988653844672293[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3260348241577175577) {
   out_3260348241577175577[0] = 1.0;
   out_3260348241577175577[1] = 0.0;
   out_3260348241577175577[2] = 0.0;
   out_3260348241577175577[3] = 0.0;
   out_3260348241577175577[4] = 0.0;
   out_3260348241577175577[5] = 0.0;
   out_3260348241577175577[6] = 0.0;
   out_3260348241577175577[7] = 0.0;
   out_3260348241577175577[8] = 0.0;
   out_3260348241577175577[9] = 0.0;
   out_3260348241577175577[10] = 1.0;
   out_3260348241577175577[11] = 0.0;
   out_3260348241577175577[12] = 0.0;
   out_3260348241577175577[13] = 0.0;
   out_3260348241577175577[14] = 0.0;
   out_3260348241577175577[15] = 0.0;
   out_3260348241577175577[16] = 0.0;
   out_3260348241577175577[17] = 0.0;
   out_3260348241577175577[18] = 0.0;
   out_3260348241577175577[19] = 0.0;
   out_3260348241577175577[20] = 1.0;
   out_3260348241577175577[21] = 0.0;
   out_3260348241577175577[22] = 0.0;
   out_3260348241577175577[23] = 0.0;
   out_3260348241577175577[24] = 0.0;
   out_3260348241577175577[25] = 0.0;
   out_3260348241577175577[26] = 0.0;
   out_3260348241577175577[27] = 0.0;
   out_3260348241577175577[28] = 0.0;
   out_3260348241577175577[29] = 0.0;
   out_3260348241577175577[30] = 1.0;
   out_3260348241577175577[31] = 0.0;
   out_3260348241577175577[32] = 0.0;
   out_3260348241577175577[33] = 0.0;
   out_3260348241577175577[34] = 0.0;
   out_3260348241577175577[35] = 0.0;
   out_3260348241577175577[36] = 0.0;
   out_3260348241577175577[37] = 0.0;
   out_3260348241577175577[38] = 0.0;
   out_3260348241577175577[39] = 0.0;
   out_3260348241577175577[40] = 1.0;
   out_3260348241577175577[41] = 0.0;
   out_3260348241577175577[42] = 0.0;
   out_3260348241577175577[43] = 0.0;
   out_3260348241577175577[44] = 0.0;
   out_3260348241577175577[45] = 0.0;
   out_3260348241577175577[46] = 0.0;
   out_3260348241577175577[47] = 0.0;
   out_3260348241577175577[48] = 0.0;
   out_3260348241577175577[49] = 0.0;
   out_3260348241577175577[50] = 1.0;
   out_3260348241577175577[51] = 0.0;
   out_3260348241577175577[52] = 0.0;
   out_3260348241577175577[53] = 0.0;
   out_3260348241577175577[54] = 0.0;
   out_3260348241577175577[55] = 0.0;
   out_3260348241577175577[56] = 0.0;
   out_3260348241577175577[57] = 0.0;
   out_3260348241577175577[58] = 0.0;
   out_3260348241577175577[59] = 0.0;
   out_3260348241577175577[60] = 1.0;
   out_3260348241577175577[61] = 0.0;
   out_3260348241577175577[62] = 0.0;
   out_3260348241577175577[63] = 0.0;
   out_3260348241577175577[64] = 0.0;
   out_3260348241577175577[65] = 0.0;
   out_3260348241577175577[66] = 0.0;
   out_3260348241577175577[67] = 0.0;
   out_3260348241577175577[68] = 0.0;
   out_3260348241577175577[69] = 0.0;
   out_3260348241577175577[70] = 1.0;
   out_3260348241577175577[71] = 0.0;
   out_3260348241577175577[72] = 0.0;
   out_3260348241577175577[73] = 0.0;
   out_3260348241577175577[74] = 0.0;
   out_3260348241577175577[75] = 0.0;
   out_3260348241577175577[76] = 0.0;
   out_3260348241577175577[77] = 0.0;
   out_3260348241577175577[78] = 0.0;
   out_3260348241577175577[79] = 0.0;
   out_3260348241577175577[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4734299198424188856) {
   out_4734299198424188856[0] = state[0];
   out_4734299198424188856[1] = state[1];
   out_4734299198424188856[2] = state[2];
   out_4734299198424188856[3] = state[3];
   out_4734299198424188856[4] = state[4];
   out_4734299198424188856[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4734299198424188856[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4734299198424188856[7] = state[7];
   out_4734299198424188856[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5631824782310061315) {
   out_5631824782310061315[0] = 1;
   out_5631824782310061315[1] = 0;
   out_5631824782310061315[2] = 0;
   out_5631824782310061315[3] = 0;
   out_5631824782310061315[4] = 0;
   out_5631824782310061315[5] = 0;
   out_5631824782310061315[6] = 0;
   out_5631824782310061315[7] = 0;
   out_5631824782310061315[8] = 0;
   out_5631824782310061315[9] = 0;
   out_5631824782310061315[10] = 1;
   out_5631824782310061315[11] = 0;
   out_5631824782310061315[12] = 0;
   out_5631824782310061315[13] = 0;
   out_5631824782310061315[14] = 0;
   out_5631824782310061315[15] = 0;
   out_5631824782310061315[16] = 0;
   out_5631824782310061315[17] = 0;
   out_5631824782310061315[18] = 0;
   out_5631824782310061315[19] = 0;
   out_5631824782310061315[20] = 1;
   out_5631824782310061315[21] = 0;
   out_5631824782310061315[22] = 0;
   out_5631824782310061315[23] = 0;
   out_5631824782310061315[24] = 0;
   out_5631824782310061315[25] = 0;
   out_5631824782310061315[26] = 0;
   out_5631824782310061315[27] = 0;
   out_5631824782310061315[28] = 0;
   out_5631824782310061315[29] = 0;
   out_5631824782310061315[30] = 1;
   out_5631824782310061315[31] = 0;
   out_5631824782310061315[32] = 0;
   out_5631824782310061315[33] = 0;
   out_5631824782310061315[34] = 0;
   out_5631824782310061315[35] = 0;
   out_5631824782310061315[36] = 0;
   out_5631824782310061315[37] = 0;
   out_5631824782310061315[38] = 0;
   out_5631824782310061315[39] = 0;
   out_5631824782310061315[40] = 1;
   out_5631824782310061315[41] = 0;
   out_5631824782310061315[42] = 0;
   out_5631824782310061315[43] = 0;
   out_5631824782310061315[44] = 0;
   out_5631824782310061315[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5631824782310061315[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5631824782310061315[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5631824782310061315[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5631824782310061315[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5631824782310061315[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5631824782310061315[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5631824782310061315[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5631824782310061315[53] = -9.8100000000000005*dt;
   out_5631824782310061315[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5631824782310061315[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5631824782310061315[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5631824782310061315[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5631824782310061315[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5631824782310061315[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5631824782310061315[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5631824782310061315[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5631824782310061315[62] = 0;
   out_5631824782310061315[63] = 0;
   out_5631824782310061315[64] = 0;
   out_5631824782310061315[65] = 0;
   out_5631824782310061315[66] = 0;
   out_5631824782310061315[67] = 0;
   out_5631824782310061315[68] = 0;
   out_5631824782310061315[69] = 0;
   out_5631824782310061315[70] = 1;
   out_5631824782310061315[71] = 0;
   out_5631824782310061315[72] = 0;
   out_5631824782310061315[73] = 0;
   out_5631824782310061315[74] = 0;
   out_5631824782310061315[75] = 0;
   out_5631824782310061315[76] = 0;
   out_5631824782310061315[77] = 0;
   out_5631824782310061315[78] = 0;
   out_5631824782310061315[79] = 0;
   out_5631824782310061315[80] = 1;
}
void h_25(double *state, double *unused, double *out_4076735487506752080) {
   out_4076735487506752080[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1643343583607489263) {
   out_1643343583607489263[0] = 0;
   out_1643343583607489263[1] = 0;
   out_1643343583607489263[2] = 0;
   out_1643343583607489263[3] = 0;
   out_1643343583607489263[4] = 0;
   out_1643343583607489263[5] = 0;
   out_1643343583607489263[6] = 1;
   out_1643343583607489263[7] = 0;
   out_1643343583607489263[8] = 0;
}
void h_24(double *state, double *unused, double *out_7512610211448591818) {
   out_7512610211448591818[0] = state[4];
   out_7512610211448591818[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4557689096243672163) {
   out_4557689096243672163[0] = 0;
   out_4557689096243672163[1] = 0;
   out_4557689096243672163[2] = 0;
   out_4557689096243672163[3] = 0;
   out_4557689096243672163[4] = 1;
   out_4557689096243672163[5] = 0;
   out_4557689096243672163[6] = 0;
   out_4557689096243672163[7] = 0;
   out_4557689096243672163[8] = 0;
   out_4557689096243672163[9] = 0;
   out_4557689096243672163[10] = 0;
   out_4557689096243672163[11] = 0;
   out_4557689096243672163[12] = 0;
   out_4557689096243672163[13] = 0;
   out_4557689096243672163[14] = 1;
   out_4557689096243672163[15] = 0;
   out_4557689096243672163[16] = 0;
   out_4557689096243672163[17] = 0;
}
void h_30(double *state, double *unused, double *out_6606743329382127095) {
   out_6606743329382127095[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2884352746520118935) {
   out_2884352746520118935[0] = 0;
   out_2884352746520118935[1] = 0;
   out_2884352746520118935[2] = 0;
   out_2884352746520118935[3] = 0;
   out_2884352746520118935[4] = 1;
   out_2884352746520118935[5] = 0;
   out_2884352746520118935[6] = 0;
   out_2884352746520118935[7] = 0;
   out_2884352746520118935[8] = 0;
}
void h_26(double *state, double *unused, double *out_2858031572320583756) {
   out_2858031572320583756[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2098159735266566961) {
   out_2098159735266566961[0] = 0;
   out_2098159735266566961[1] = 0;
   out_2098159735266566961[2] = 0;
   out_2098159735266566961[3] = 0;
   out_2098159735266566961[4] = 0;
   out_2098159735266566961[5] = 0;
   out_2098159735266566961[6] = 0;
   out_2098159735266566961[7] = 1;
   out_2098159735266566961[8] = 0;
}
void h_27(double *state, double *unused, double *out_924937780154093565) {
   out_924937780154093565[0] = state[3];
}
void H_27(double *state, double *unused, double *out_660758675336175718) {
   out_660758675336175718[0] = 0;
   out_660758675336175718[1] = 0;
   out_660758675336175718[2] = 0;
   out_660758675336175718[3] = 1;
   out_660758675336175718[4] = 0;
   out_660758675336175718[5] = 0;
   out_660758675336175718[6] = 0;
   out_660758675336175718[7] = 0;
   out_660758675336175718[8] = 0;
}
void h_29(double *state, double *unused, double *out_6838327476666578876) {
   out_6838327476666578876[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2374121402205726751) {
   out_2374121402205726751[0] = 0;
   out_2374121402205726751[1] = 1;
   out_2374121402205726751[2] = 0;
   out_2374121402205726751[3] = 0;
   out_2374121402205726751[4] = 0;
   out_2374121402205726751[5] = 0;
   out_2374121402205726751[6] = 0;
   out_2374121402205726751[7] = 0;
   out_2374121402205726751[8] = 0;
}
void h_28(double *state, double *unused, double *out_2111848271290239120) {
   out_2111848271290239120[0] = state[0];
}
void H_28(double *state, double *unused, double *out_410491130640400500) {
   out_410491130640400500[0] = 1;
   out_410491130640400500[1] = 0;
   out_410491130640400500[2] = 0;
   out_410491130640400500[3] = 0;
   out_410491130640400500[4] = 0;
   out_410491130640400500[5] = 0;
   out_410491130640400500[6] = 0;
   out_410491130640400500[7] = 0;
   out_410491130640400500[8] = 0;
}
void h_31(double *state, double *unused, double *out_3383823276742136245) {
   out_3383823276742136245[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2724367837499918437) {
   out_2724367837499918437[0] = 0;
   out_2724367837499918437[1] = 0;
   out_2724367837499918437[2] = 0;
   out_2724367837499918437[3] = 0;
   out_2724367837499918437[4] = 0;
   out_2724367837499918437[5] = 0;
   out_2724367837499918437[6] = 0;
   out_2724367837499918437[7] = 0;
   out_2724367837499918437[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5960298151612549262) {
  err_fun(nom_x, delta_x, out_5960298151612549262);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3713988653844672293) {
  inv_err_fun(nom_x, true_x, out_3713988653844672293);
}
void car_H_mod_fun(double *state, double *out_3260348241577175577) {
  H_mod_fun(state, out_3260348241577175577);
}
void car_f_fun(double *state, double dt, double *out_4734299198424188856) {
  f_fun(state,  dt, out_4734299198424188856);
}
void car_F_fun(double *state, double dt, double *out_5631824782310061315) {
  F_fun(state,  dt, out_5631824782310061315);
}
void car_h_25(double *state, double *unused, double *out_4076735487506752080) {
  h_25(state, unused, out_4076735487506752080);
}
void car_H_25(double *state, double *unused, double *out_1643343583607489263) {
  H_25(state, unused, out_1643343583607489263);
}
void car_h_24(double *state, double *unused, double *out_7512610211448591818) {
  h_24(state, unused, out_7512610211448591818);
}
void car_H_24(double *state, double *unused, double *out_4557689096243672163) {
  H_24(state, unused, out_4557689096243672163);
}
void car_h_30(double *state, double *unused, double *out_6606743329382127095) {
  h_30(state, unused, out_6606743329382127095);
}
void car_H_30(double *state, double *unused, double *out_2884352746520118935) {
  H_30(state, unused, out_2884352746520118935);
}
void car_h_26(double *state, double *unused, double *out_2858031572320583756) {
  h_26(state, unused, out_2858031572320583756);
}
void car_H_26(double *state, double *unused, double *out_2098159735266566961) {
  H_26(state, unused, out_2098159735266566961);
}
void car_h_27(double *state, double *unused, double *out_924937780154093565) {
  h_27(state, unused, out_924937780154093565);
}
void car_H_27(double *state, double *unused, double *out_660758675336175718) {
  H_27(state, unused, out_660758675336175718);
}
void car_h_29(double *state, double *unused, double *out_6838327476666578876) {
  h_29(state, unused, out_6838327476666578876);
}
void car_H_29(double *state, double *unused, double *out_2374121402205726751) {
  H_29(state, unused, out_2374121402205726751);
}
void car_h_28(double *state, double *unused, double *out_2111848271290239120) {
  h_28(state, unused, out_2111848271290239120);
}
void car_H_28(double *state, double *unused, double *out_410491130640400500) {
  H_28(state, unused, out_410491130640400500);
}
void car_h_31(double *state, double *unused, double *out_3383823276742136245) {
  h_31(state, unused, out_3383823276742136245);
}
void car_H_31(double *state, double *unused, double *out_2724367837499918437) {
  H_31(state, unused, out_2724367837499918437);
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
