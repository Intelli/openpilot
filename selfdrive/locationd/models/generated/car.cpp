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
void err_fun(double *nom_x, double *delta_x, double *out_1080054032760263743) {
   out_1080054032760263743[0] = delta_x[0] + nom_x[0];
   out_1080054032760263743[1] = delta_x[1] + nom_x[1];
   out_1080054032760263743[2] = delta_x[2] + nom_x[2];
   out_1080054032760263743[3] = delta_x[3] + nom_x[3];
   out_1080054032760263743[4] = delta_x[4] + nom_x[4];
   out_1080054032760263743[5] = delta_x[5] + nom_x[5];
   out_1080054032760263743[6] = delta_x[6] + nom_x[6];
   out_1080054032760263743[7] = delta_x[7] + nom_x[7];
   out_1080054032760263743[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_668655428686680811) {
   out_668655428686680811[0] = -nom_x[0] + true_x[0];
   out_668655428686680811[1] = -nom_x[1] + true_x[1];
   out_668655428686680811[2] = -nom_x[2] + true_x[2];
   out_668655428686680811[3] = -nom_x[3] + true_x[3];
   out_668655428686680811[4] = -nom_x[4] + true_x[4];
   out_668655428686680811[5] = -nom_x[5] + true_x[5];
   out_668655428686680811[6] = -nom_x[6] + true_x[6];
   out_668655428686680811[7] = -nom_x[7] + true_x[7];
   out_668655428686680811[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7021396879679134881) {
   out_7021396879679134881[0] = 1.0;
   out_7021396879679134881[1] = 0.0;
   out_7021396879679134881[2] = 0.0;
   out_7021396879679134881[3] = 0.0;
   out_7021396879679134881[4] = 0.0;
   out_7021396879679134881[5] = 0.0;
   out_7021396879679134881[6] = 0.0;
   out_7021396879679134881[7] = 0.0;
   out_7021396879679134881[8] = 0.0;
   out_7021396879679134881[9] = 0.0;
   out_7021396879679134881[10] = 1.0;
   out_7021396879679134881[11] = 0.0;
   out_7021396879679134881[12] = 0.0;
   out_7021396879679134881[13] = 0.0;
   out_7021396879679134881[14] = 0.0;
   out_7021396879679134881[15] = 0.0;
   out_7021396879679134881[16] = 0.0;
   out_7021396879679134881[17] = 0.0;
   out_7021396879679134881[18] = 0.0;
   out_7021396879679134881[19] = 0.0;
   out_7021396879679134881[20] = 1.0;
   out_7021396879679134881[21] = 0.0;
   out_7021396879679134881[22] = 0.0;
   out_7021396879679134881[23] = 0.0;
   out_7021396879679134881[24] = 0.0;
   out_7021396879679134881[25] = 0.0;
   out_7021396879679134881[26] = 0.0;
   out_7021396879679134881[27] = 0.0;
   out_7021396879679134881[28] = 0.0;
   out_7021396879679134881[29] = 0.0;
   out_7021396879679134881[30] = 1.0;
   out_7021396879679134881[31] = 0.0;
   out_7021396879679134881[32] = 0.0;
   out_7021396879679134881[33] = 0.0;
   out_7021396879679134881[34] = 0.0;
   out_7021396879679134881[35] = 0.0;
   out_7021396879679134881[36] = 0.0;
   out_7021396879679134881[37] = 0.0;
   out_7021396879679134881[38] = 0.0;
   out_7021396879679134881[39] = 0.0;
   out_7021396879679134881[40] = 1.0;
   out_7021396879679134881[41] = 0.0;
   out_7021396879679134881[42] = 0.0;
   out_7021396879679134881[43] = 0.0;
   out_7021396879679134881[44] = 0.0;
   out_7021396879679134881[45] = 0.0;
   out_7021396879679134881[46] = 0.0;
   out_7021396879679134881[47] = 0.0;
   out_7021396879679134881[48] = 0.0;
   out_7021396879679134881[49] = 0.0;
   out_7021396879679134881[50] = 1.0;
   out_7021396879679134881[51] = 0.0;
   out_7021396879679134881[52] = 0.0;
   out_7021396879679134881[53] = 0.0;
   out_7021396879679134881[54] = 0.0;
   out_7021396879679134881[55] = 0.0;
   out_7021396879679134881[56] = 0.0;
   out_7021396879679134881[57] = 0.0;
   out_7021396879679134881[58] = 0.0;
   out_7021396879679134881[59] = 0.0;
   out_7021396879679134881[60] = 1.0;
   out_7021396879679134881[61] = 0.0;
   out_7021396879679134881[62] = 0.0;
   out_7021396879679134881[63] = 0.0;
   out_7021396879679134881[64] = 0.0;
   out_7021396879679134881[65] = 0.0;
   out_7021396879679134881[66] = 0.0;
   out_7021396879679134881[67] = 0.0;
   out_7021396879679134881[68] = 0.0;
   out_7021396879679134881[69] = 0.0;
   out_7021396879679134881[70] = 1.0;
   out_7021396879679134881[71] = 0.0;
   out_7021396879679134881[72] = 0.0;
   out_7021396879679134881[73] = 0.0;
   out_7021396879679134881[74] = 0.0;
   out_7021396879679134881[75] = 0.0;
   out_7021396879679134881[76] = 0.0;
   out_7021396879679134881[77] = 0.0;
   out_7021396879679134881[78] = 0.0;
   out_7021396879679134881[79] = 0.0;
   out_7021396879679134881[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5377318552564722043) {
   out_5377318552564722043[0] = state[0];
   out_5377318552564722043[1] = state[1];
   out_5377318552564722043[2] = state[2];
   out_5377318552564722043[3] = state[3];
   out_5377318552564722043[4] = state[4];
   out_5377318552564722043[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5377318552564722043[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5377318552564722043[7] = state[7];
   out_5377318552564722043[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1196688089252186571) {
   out_1196688089252186571[0] = 1;
   out_1196688089252186571[1] = 0;
   out_1196688089252186571[2] = 0;
   out_1196688089252186571[3] = 0;
   out_1196688089252186571[4] = 0;
   out_1196688089252186571[5] = 0;
   out_1196688089252186571[6] = 0;
   out_1196688089252186571[7] = 0;
   out_1196688089252186571[8] = 0;
   out_1196688089252186571[9] = 0;
   out_1196688089252186571[10] = 1;
   out_1196688089252186571[11] = 0;
   out_1196688089252186571[12] = 0;
   out_1196688089252186571[13] = 0;
   out_1196688089252186571[14] = 0;
   out_1196688089252186571[15] = 0;
   out_1196688089252186571[16] = 0;
   out_1196688089252186571[17] = 0;
   out_1196688089252186571[18] = 0;
   out_1196688089252186571[19] = 0;
   out_1196688089252186571[20] = 1;
   out_1196688089252186571[21] = 0;
   out_1196688089252186571[22] = 0;
   out_1196688089252186571[23] = 0;
   out_1196688089252186571[24] = 0;
   out_1196688089252186571[25] = 0;
   out_1196688089252186571[26] = 0;
   out_1196688089252186571[27] = 0;
   out_1196688089252186571[28] = 0;
   out_1196688089252186571[29] = 0;
   out_1196688089252186571[30] = 1;
   out_1196688089252186571[31] = 0;
   out_1196688089252186571[32] = 0;
   out_1196688089252186571[33] = 0;
   out_1196688089252186571[34] = 0;
   out_1196688089252186571[35] = 0;
   out_1196688089252186571[36] = 0;
   out_1196688089252186571[37] = 0;
   out_1196688089252186571[38] = 0;
   out_1196688089252186571[39] = 0;
   out_1196688089252186571[40] = 1;
   out_1196688089252186571[41] = 0;
   out_1196688089252186571[42] = 0;
   out_1196688089252186571[43] = 0;
   out_1196688089252186571[44] = 0;
   out_1196688089252186571[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1196688089252186571[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1196688089252186571[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1196688089252186571[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1196688089252186571[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1196688089252186571[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1196688089252186571[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1196688089252186571[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1196688089252186571[53] = -9.8100000000000005*dt;
   out_1196688089252186571[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1196688089252186571[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1196688089252186571[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1196688089252186571[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1196688089252186571[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1196688089252186571[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1196688089252186571[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1196688089252186571[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1196688089252186571[62] = 0;
   out_1196688089252186571[63] = 0;
   out_1196688089252186571[64] = 0;
   out_1196688089252186571[65] = 0;
   out_1196688089252186571[66] = 0;
   out_1196688089252186571[67] = 0;
   out_1196688089252186571[68] = 0;
   out_1196688089252186571[69] = 0;
   out_1196688089252186571[70] = 1;
   out_1196688089252186571[71] = 0;
   out_1196688089252186571[72] = 0;
   out_1196688089252186571[73] = 0;
   out_1196688089252186571[74] = 0;
   out_1196688089252186571[75] = 0;
   out_1196688089252186571[76] = 0;
   out_1196688089252186571[77] = 0;
   out_1196688089252186571[78] = 0;
   out_1196688089252186571[79] = 0;
   out_1196688089252186571[80] = 1;
}
void h_25(double *state, double *unused, double *out_2511128803102887624) {
   out_2511128803102887624[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6521655368845751895) {
   out_6521655368845751895[0] = 0;
   out_6521655368845751895[1] = 0;
   out_6521655368845751895[2] = 0;
   out_6521655368845751895[3] = 0;
   out_6521655368845751895[4] = 0;
   out_6521655368845751895[5] = 0;
   out_6521655368845751895[6] = 1;
   out_6521655368845751895[7] = 0;
   out_6521655368845751895[8] = 0;
}
void h_24(double *state, double *unused, double *out_4108202673726123868) {
   out_4108202673726123868[0] = state[4];
   out_4108202673726123868[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6992112850889090619) {
   out_6992112850889090619[0] = 0;
   out_6992112850889090619[1] = 0;
   out_6992112850889090619[2] = 0;
   out_6992112850889090619[3] = 0;
   out_6992112850889090619[4] = 1;
   out_6992112850889090619[5] = 0;
   out_6992112850889090619[6] = 0;
   out_6992112850889090619[7] = 0;
   out_6992112850889090619[8] = 0;
   out_6992112850889090619[9] = 0;
   out_6992112850889090619[10] = 0;
   out_6992112850889090619[11] = 0;
   out_6992112850889090619[12] = 0;
   out_6992112850889090619[13] = 0;
   out_6992112850889090619[14] = 1;
   out_6992112850889090619[15] = 0;
   out_6992112850889090619[16] = 0;
   out_6992112850889090619[17] = 0;
}
void h_30(double *state, double *unused, double *out_5080086584799551990) {
   out_5080086584799551990[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6650994315988991965) {
   out_6650994315988991965[0] = 0;
   out_6650994315988991965[1] = 0;
   out_6650994315988991965[2] = 0;
   out_6650994315988991965[3] = 0;
   out_6650994315988991965[4] = 1;
   out_6650994315988991965[5] = 0;
   out_6650994315988991965[6] = 0;
   out_6650994315988991965[7] = 0;
   out_6650994315988991965[8] = 0;
}
void h_26(double *state, double *unused, double *out_2569258588511782352) {
   out_2569258588511782352[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8183585385989743497) {
   out_8183585385989743497[0] = 0;
   out_8183585385989743497[1] = 0;
   out_8183585385989743497[2] = 0;
   out_8183585385989743497[3] = 0;
   out_8183585385989743497[4] = 0;
   out_8183585385989743497[5] = 0;
   out_8183585385989743497[6] = 0;
   out_8183585385989743497[7] = 1;
   out_8183585385989743497[8] = 0;
}
void h_27(double *state, double *unused, double *out_3861382669613383666) {
   out_3861382669613383666[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8825757627789416876) {
   out_8825757627789416876[0] = 0;
   out_8825757627789416876[1] = 0;
   out_8825757627789416876[2] = 0;
   out_8825757627789416876[3] = 1;
   out_8825757627789416876[4] = 0;
   out_8825757627789416876[5] = 0;
   out_8825757627789416876[6] = 0;
   out_8825757627789416876[7] = 0;
   out_8825757627789416876[8] = 0;
}
void h_29(double *state, double *unused, double *out_4136576731897889555) {
   out_4136576731897889555[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7907623719050583707) {
   out_7907623719050583707[0] = 0;
   out_7907623719050583707[1] = 1;
   out_7907623719050583707[2] = 0;
   out_7907623719050583707[3] = 0;
   out_7907623719050583707[4] = 0;
   out_7907623719050583707[5] = 0;
   out_7907623719050583707[6] = 0;
   out_7907623719050583707[7] = 0;
   out_7907623719050583707[8] = 0;
}
void h_28(double *state, double *unused, double *out_1256977348804686015) {
   out_1256977348804686015[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8575490083093641658) {
   out_8575490083093641658[0] = 1;
   out_8575490083093641658[1] = 0;
   out_8575490083093641658[2] = 0;
   out_8575490083093641658[3] = 0;
   out_8575490083093641658[4] = 0;
   out_8575490083093641658[5] = 0;
   out_8575490083093641658[6] = 0;
   out_8575490083093641658[7] = 0;
   out_8575490083093641658[8] = 0;
}
void h_31(double *state, double *unused, double *out_7295737793888122108) {
   out_7295737793888122108[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6491009406968791467) {
   out_6491009406968791467[0] = 0;
   out_6491009406968791467[1] = 0;
   out_6491009406968791467[2] = 0;
   out_6491009406968791467[3] = 0;
   out_6491009406968791467[4] = 0;
   out_6491009406968791467[5] = 0;
   out_6491009406968791467[6] = 0;
   out_6491009406968791467[7] = 0;
   out_6491009406968791467[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_1080054032760263743) {
  err_fun(nom_x, delta_x, out_1080054032760263743);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_668655428686680811) {
  inv_err_fun(nom_x, true_x, out_668655428686680811);
}
void car_H_mod_fun(double *state, double *out_7021396879679134881) {
  H_mod_fun(state, out_7021396879679134881);
}
void car_f_fun(double *state, double dt, double *out_5377318552564722043) {
  f_fun(state,  dt, out_5377318552564722043);
}
void car_F_fun(double *state, double dt, double *out_1196688089252186571) {
  F_fun(state,  dt, out_1196688089252186571);
}
void car_h_25(double *state, double *unused, double *out_2511128803102887624) {
  h_25(state, unused, out_2511128803102887624);
}
void car_H_25(double *state, double *unused, double *out_6521655368845751895) {
  H_25(state, unused, out_6521655368845751895);
}
void car_h_24(double *state, double *unused, double *out_4108202673726123868) {
  h_24(state, unused, out_4108202673726123868);
}
void car_H_24(double *state, double *unused, double *out_6992112850889090619) {
  H_24(state, unused, out_6992112850889090619);
}
void car_h_30(double *state, double *unused, double *out_5080086584799551990) {
  h_30(state, unused, out_5080086584799551990);
}
void car_H_30(double *state, double *unused, double *out_6650994315988991965) {
  H_30(state, unused, out_6650994315988991965);
}
void car_h_26(double *state, double *unused, double *out_2569258588511782352) {
  h_26(state, unused, out_2569258588511782352);
}
void car_H_26(double *state, double *unused, double *out_8183585385989743497) {
  H_26(state, unused, out_8183585385989743497);
}
void car_h_27(double *state, double *unused, double *out_3861382669613383666) {
  h_27(state, unused, out_3861382669613383666);
}
void car_H_27(double *state, double *unused, double *out_8825757627789416876) {
  H_27(state, unused, out_8825757627789416876);
}
void car_h_29(double *state, double *unused, double *out_4136576731897889555) {
  h_29(state, unused, out_4136576731897889555);
}
void car_H_29(double *state, double *unused, double *out_7907623719050583707) {
  H_29(state, unused, out_7907623719050583707);
}
void car_h_28(double *state, double *unused, double *out_1256977348804686015) {
  h_28(state, unused, out_1256977348804686015);
}
void car_H_28(double *state, double *unused, double *out_8575490083093641658) {
  H_28(state, unused, out_8575490083093641658);
}
void car_h_31(double *state, double *unused, double *out_7295737793888122108) {
  h_31(state, unused, out_7295737793888122108);
}
void car_H_31(double *state, double *unused, double *out_6491009406968791467) {
  H_31(state, unused, out_6491009406968791467);
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
