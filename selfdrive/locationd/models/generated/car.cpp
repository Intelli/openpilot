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
void err_fun(double *nom_x, double *delta_x, double *out_592952605244645271) {
   out_592952605244645271[0] = delta_x[0] + nom_x[0];
   out_592952605244645271[1] = delta_x[1] + nom_x[1];
   out_592952605244645271[2] = delta_x[2] + nom_x[2];
   out_592952605244645271[3] = delta_x[3] + nom_x[3];
   out_592952605244645271[4] = delta_x[4] + nom_x[4];
   out_592952605244645271[5] = delta_x[5] + nom_x[5];
   out_592952605244645271[6] = delta_x[6] + nom_x[6];
   out_592952605244645271[7] = delta_x[7] + nom_x[7];
   out_592952605244645271[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6836454440679390003) {
   out_6836454440679390003[0] = -nom_x[0] + true_x[0];
   out_6836454440679390003[1] = -nom_x[1] + true_x[1];
   out_6836454440679390003[2] = -nom_x[2] + true_x[2];
   out_6836454440679390003[3] = -nom_x[3] + true_x[3];
   out_6836454440679390003[4] = -nom_x[4] + true_x[4];
   out_6836454440679390003[5] = -nom_x[5] + true_x[5];
   out_6836454440679390003[6] = -nom_x[6] + true_x[6];
   out_6836454440679390003[7] = -nom_x[7] + true_x[7];
   out_6836454440679390003[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6286510676597888168) {
   out_6286510676597888168[0] = 1.0;
   out_6286510676597888168[1] = 0.0;
   out_6286510676597888168[2] = 0.0;
   out_6286510676597888168[3] = 0.0;
   out_6286510676597888168[4] = 0.0;
   out_6286510676597888168[5] = 0.0;
   out_6286510676597888168[6] = 0.0;
   out_6286510676597888168[7] = 0.0;
   out_6286510676597888168[8] = 0.0;
   out_6286510676597888168[9] = 0.0;
   out_6286510676597888168[10] = 1.0;
   out_6286510676597888168[11] = 0.0;
   out_6286510676597888168[12] = 0.0;
   out_6286510676597888168[13] = 0.0;
   out_6286510676597888168[14] = 0.0;
   out_6286510676597888168[15] = 0.0;
   out_6286510676597888168[16] = 0.0;
   out_6286510676597888168[17] = 0.0;
   out_6286510676597888168[18] = 0.0;
   out_6286510676597888168[19] = 0.0;
   out_6286510676597888168[20] = 1.0;
   out_6286510676597888168[21] = 0.0;
   out_6286510676597888168[22] = 0.0;
   out_6286510676597888168[23] = 0.0;
   out_6286510676597888168[24] = 0.0;
   out_6286510676597888168[25] = 0.0;
   out_6286510676597888168[26] = 0.0;
   out_6286510676597888168[27] = 0.0;
   out_6286510676597888168[28] = 0.0;
   out_6286510676597888168[29] = 0.0;
   out_6286510676597888168[30] = 1.0;
   out_6286510676597888168[31] = 0.0;
   out_6286510676597888168[32] = 0.0;
   out_6286510676597888168[33] = 0.0;
   out_6286510676597888168[34] = 0.0;
   out_6286510676597888168[35] = 0.0;
   out_6286510676597888168[36] = 0.0;
   out_6286510676597888168[37] = 0.0;
   out_6286510676597888168[38] = 0.0;
   out_6286510676597888168[39] = 0.0;
   out_6286510676597888168[40] = 1.0;
   out_6286510676597888168[41] = 0.0;
   out_6286510676597888168[42] = 0.0;
   out_6286510676597888168[43] = 0.0;
   out_6286510676597888168[44] = 0.0;
   out_6286510676597888168[45] = 0.0;
   out_6286510676597888168[46] = 0.0;
   out_6286510676597888168[47] = 0.0;
   out_6286510676597888168[48] = 0.0;
   out_6286510676597888168[49] = 0.0;
   out_6286510676597888168[50] = 1.0;
   out_6286510676597888168[51] = 0.0;
   out_6286510676597888168[52] = 0.0;
   out_6286510676597888168[53] = 0.0;
   out_6286510676597888168[54] = 0.0;
   out_6286510676597888168[55] = 0.0;
   out_6286510676597888168[56] = 0.0;
   out_6286510676597888168[57] = 0.0;
   out_6286510676597888168[58] = 0.0;
   out_6286510676597888168[59] = 0.0;
   out_6286510676597888168[60] = 1.0;
   out_6286510676597888168[61] = 0.0;
   out_6286510676597888168[62] = 0.0;
   out_6286510676597888168[63] = 0.0;
   out_6286510676597888168[64] = 0.0;
   out_6286510676597888168[65] = 0.0;
   out_6286510676597888168[66] = 0.0;
   out_6286510676597888168[67] = 0.0;
   out_6286510676597888168[68] = 0.0;
   out_6286510676597888168[69] = 0.0;
   out_6286510676597888168[70] = 1.0;
   out_6286510676597888168[71] = 0.0;
   out_6286510676597888168[72] = 0.0;
   out_6286510676597888168[73] = 0.0;
   out_6286510676597888168[74] = 0.0;
   out_6286510676597888168[75] = 0.0;
   out_6286510676597888168[76] = 0.0;
   out_6286510676597888168[77] = 0.0;
   out_6286510676597888168[78] = 0.0;
   out_6286510676597888168[79] = 0.0;
   out_6286510676597888168[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5881410695804520477) {
   out_5881410695804520477[0] = state[0];
   out_5881410695804520477[1] = state[1];
   out_5881410695804520477[2] = state[2];
   out_5881410695804520477[3] = state[3];
   out_5881410695804520477[4] = state[4];
   out_5881410695804520477[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5881410695804520477[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5881410695804520477[7] = state[7];
   out_5881410695804520477[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5545553878115808684) {
   out_5545553878115808684[0] = 1;
   out_5545553878115808684[1] = 0;
   out_5545553878115808684[2] = 0;
   out_5545553878115808684[3] = 0;
   out_5545553878115808684[4] = 0;
   out_5545553878115808684[5] = 0;
   out_5545553878115808684[6] = 0;
   out_5545553878115808684[7] = 0;
   out_5545553878115808684[8] = 0;
   out_5545553878115808684[9] = 0;
   out_5545553878115808684[10] = 1;
   out_5545553878115808684[11] = 0;
   out_5545553878115808684[12] = 0;
   out_5545553878115808684[13] = 0;
   out_5545553878115808684[14] = 0;
   out_5545553878115808684[15] = 0;
   out_5545553878115808684[16] = 0;
   out_5545553878115808684[17] = 0;
   out_5545553878115808684[18] = 0;
   out_5545553878115808684[19] = 0;
   out_5545553878115808684[20] = 1;
   out_5545553878115808684[21] = 0;
   out_5545553878115808684[22] = 0;
   out_5545553878115808684[23] = 0;
   out_5545553878115808684[24] = 0;
   out_5545553878115808684[25] = 0;
   out_5545553878115808684[26] = 0;
   out_5545553878115808684[27] = 0;
   out_5545553878115808684[28] = 0;
   out_5545553878115808684[29] = 0;
   out_5545553878115808684[30] = 1;
   out_5545553878115808684[31] = 0;
   out_5545553878115808684[32] = 0;
   out_5545553878115808684[33] = 0;
   out_5545553878115808684[34] = 0;
   out_5545553878115808684[35] = 0;
   out_5545553878115808684[36] = 0;
   out_5545553878115808684[37] = 0;
   out_5545553878115808684[38] = 0;
   out_5545553878115808684[39] = 0;
   out_5545553878115808684[40] = 1;
   out_5545553878115808684[41] = 0;
   out_5545553878115808684[42] = 0;
   out_5545553878115808684[43] = 0;
   out_5545553878115808684[44] = 0;
   out_5545553878115808684[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5545553878115808684[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5545553878115808684[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5545553878115808684[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5545553878115808684[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5545553878115808684[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5545553878115808684[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5545553878115808684[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5545553878115808684[53] = -9.8100000000000005*dt;
   out_5545553878115808684[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5545553878115808684[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5545553878115808684[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5545553878115808684[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5545553878115808684[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5545553878115808684[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5545553878115808684[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5545553878115808684[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5545553878115808684[62] = 0;
   out_5545553878115808684[63] = 0;
   out_5545553878115808684[64] = 0;
   out_5545553878115808684[65] = 0;
   out_5545553878115808684[66] = 0;
   out_5545553878115808684[67] = 0;
   out_5545553878115808684[68] = 0;
   out_5545553878115808684[69] = 0;
   out_5545553878115808684[70] = 1;
   out_5545553878115808684[71] = 0;
   out_5545553878115808684[72] = 0;
   out_5545553878115808684[73] = 0;
   out_5545553878115808684[74] = 0;
   out_5545553878115808684[75] = 0;
   out_5545553878115808684[76] = 0;
   out_5545553878115808684[77] = 0;
   out_5545553878115808684[78] = 0;
   out_5545553878115808684[79] = 0;
   out_5545553878115808684[80] = 1;
}
void h_25(double *state, double *unused, double *out_3412183612969937421) {
   out_3412183612969937421[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5520062914515680919) {
   out_5520062914515680919[0] = 0;
   out_5520062914515680919[1] = 0;
   out_5520062914515680919[2] = 0;
   out_5520062914515680919[3] = 0;
   out_5520062914515680919[4] = 0;
   out_5520062914515680919[5] = 0;
   out_5520062914515680919[6] = 1;
   out_5520062914515680919[7] = 0;
   out_5520062914515680919[8] = 0;
}
void h_24(double *state, double *unused, double *out_4072870949177330157) {
   out_4072870949177330157[0] = state[4];
   out_4072870949177330157[1] = state[5];
}
void H_24(double *state, double *unused, double *out_680969765335480507) {
   out_680969765335480507[0] = 0;
   out_680969765335480507[1] = 0;
   out_680969765335480507[2] = 0;
   out_680969765335480507[3] = 0;
   out_680969765335480507[4] = 1;
   out_680969765335480507[5] = 0;
   out_680969765335480507[6] = 0;
   out_680969765335480507[7] = 0;
   out_680969765335480507[8] = 0;
   out_680969765335480507[9] = 0;
   out_680969765335480507[10] = 0;
   out_680969765335480507[11] = 0;
   out_680969765335480507[12] = 0;
   out_680969765335480507[13] = 0;
   out_680969765335480507[14] = 1;
   out_680969765335480507[15] = 0;
   out_680969765335480507[16] = 0;
   out_680969765335480507[17] = 0;
}
void h_30(double *state, double *unused, double *out_2537864572703668366) {
   out_2537864572703668366[0] = state[4];
}
void H_30(double *state, double *unused, double *out_992366584388072721) {
   out_992366584388072721[0] = 0;
   out_992366584388072721[1] = 0;
   out_992366584388072721[2] = 0;
   out_992366584388072721[3] = 0;
   out_992366584388072721[4] = 1;
   out_992366584388072721[5] = 0;
   out_992366584388072721[6] = 0;
   out_992366584388072721[7] = 0;
   out_992366584388072721[8] = 0;
}
void h_26(double *state, double *unused, double *out_3897492103713038194) {
   out_3897492103713038194[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1778559595641624695) {
   out_1778559595641624695[0] = 0;
   out_1778559595641624695[1] = 0;
   out_1778559595641624695[2] = 0;
   out_1778559595641624695[3] = 0;
   out_1778559595641624695[4] = 0;
   out_1778559595641624695[5] = 0;
   out_1778559595641624695[6] = 0;
   out_1778559595641624695[7] = 1;
   out_1778559595641624695[8] = 0;
}
void h_27(double *state, double *unused, double *out_4015499497646414938) {
   out_4015499497646414938[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3215960655572015938) {
   out_3215960655572015938[0] = 0;
   out_3215960655572015938[1] = 0;
   out_3215960655572015938[2] = 0;
   out_3215960655572015938[3] = 1;
   out_3215960655572015938[4] = 0;
   out_3215960655572015938[5] = 0;
   out_3215960655572015938[6] = 0;
   out_3215960655572015938[7] = 0;
   out_3215960655572015938[8] = 0;
}
void h_29(double *state, double *unused, double *out_82803800632956926) {
   out_82803800632956926[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1502597928702464905) {
   out_1502597928702464905[0] = 0;
   out_1502597928702464905[1] = 1;
   out_1502597928702464905[2] = 0;
   out_1502597928702464905[3] = 0;
   out_1502597928702464905[4] = 0;
   out_1502597928702464905[5] = 0;
   out_1502597928702464905[6] = 0;
   out_1502597928702464905[7] = 0;
   out_1502597928702464905[8] = 0;
}
void h_28(double *state, double *unused, double *out_4997583590981713050) {
   out_4997583590981713050[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3466228200267791156) {
   out_3466228200267791156[0] = 1;
   out_3466228200267791156[1] = 0;
   out_3466228200267791156[2] = 0;
   out_3466228200267791156[3] = 0;
   out_3466228200267791156[4] = 0;
   out_3466228200267791156[5] = 0;
   out_3466228200267791156[6] = 0;
   out_3466228200267791156[7] = 0;
   out_3466228200267791156[8] = 0;
}
void h_31(double *state, double *unused, double *out_7271295203918941754) {
   out_7271295203918941754[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1152351493408273219) {
   out_1152351493408273219[0] = 0;
   out_1152351493408273219[1] = 0;
   out_1152351493408273219[2] = 0;
   out_1152351493408273219[3] = 0;
   out_1152351493408273219[4] = 0;
   out_1152351493408273219[5] = 0;
   out_1152351493408273219[6] = 0;
   out_1152351493408273219[7] = 0;
   out_1152351493408273219[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_592952605244645271) {
  err_fun(nom_x, delta_x, out_592952605244645271);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6836454440679390003) {
  inv_err_fun(nom_x, true_x, out_6836454440679390003);
}
void car_H_mod_fun(double *state, double *out_6286510676597888168) {
  H_mod_fun(state, out_6286510676597888168);
}
void car_f_fun(double *state, double dt, double *out_5881410695804520477) {
  f_fun(state,  dt, out_5881410695804520477);
}
void car_F_fun(double *state, double dt, double *out_5545553878115808684) {
  F_fun(state,  dt, out_5545553878115808684);
}
void car_h_25(double *state, double *unused, double *out_3412183612969937421) {
  h_25(state, unused, out_3412183612969937421);
}
void car_H_25(double *state, double *unused, double *out_5520062914515680919) {
  H_25(state, unused, out_5520062914515680919);
}
void car_h_24(double *state, double *unused, double *out_4072870949177330157) {
  h_24(state, unused, out_4072870949177330157);
}
void car_H_24(double *state, double *unused, double *out_680969765335480507) {
  H_24(state, unused, out_680969765335480507);
}
void car_h_30(double *state, double *unused, double *out_2537864572703668366) {
  h_30(state, unused, out_2537864572703668366);
}
void car_H_30(double *state, double *unused, double *out_992366584388072721) {
  H_30(state, unused, out_992366584388072721);
}
void car_h_26(double *state, double *unused, double *out_3897492103713038194) {
  h_26(state, unused, out_3897492103713038194);
}
void car_H_26(double *state, double *unused, double *out_1778559595641624695) {
  H_26(state, unused, out_1778559595641624695);
}
void car_h_27(double *state, double *unused, double *out_4015499497646414938) {
  h_27(state, unused, out_4015499497646414938);
}
void car_H_27(double *state, double *unused, double *out_3215960655572015938) {
  H_27(state, unused, out_3215960655572015938);
}
void car_h_29(double *state, double *unused, double *out_82803800632956926) {
  h_29(state, unused, out_82803800632956926);
}
void car_H_29(double *state, double *unused, double *out_1502597928702464905) {
  H_29(state, unused, out_1502597928702464905);
}
void car_h_28(double *state, double *unused, double *out_4997583590981713050) {
  h_28(state, unused, out_4997583590981713050);
}
void car_H_28(double *state, double *unused, double *out_3466228200267791156) {
  H_28(state, unused, out_3466228200267791156);
}
void car_h_31(double *state, double *unused, double *out_7271295203918941754) {
  h_31(state, unused, out_7271295203918941754);
}
void car_H_31(double *state, double *unused, double *out_1152351493408273219) {
  H_31(state, unused, out_1152351493408273219);
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
