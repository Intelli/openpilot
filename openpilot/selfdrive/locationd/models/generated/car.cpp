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
void err_fun(double *nom_x, double *delta_x, double *out_3779060101704895999) {
   out_3779060101704895999[0] = delta_x[0] + nom_x[0];
   out_3779060101704895999[1] = delta_x[1] + nom_x[1];
   out_3779060101704895999[2] = delta_x[2] + nom_x[2];
   out_3779060101704895999[3] = delta_x[3] + nom_x[3];
   out_3779060101704895999[4] = delta_x[4] + nom_x[4];
   out_3779060101704895999[5] = delta_x[5] + nom_x[5];
   out_3779060101704895999[6] = delta_x[6] + nom_x[6];
   out_3779060101704895999[7] = delta_x[7] + nom_x[7];
   out_3779060101704895999[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5987549380886467190) {
   out_5987549380886467190[0] = -nom_x[0] + true_x[0];
   out_5987549380886467190[1] = -nom_x[1] + true_x[1];
   out_5987549380886467190[2] = -nom_x[2] + true_x[2];
   out_5987549380886467190[3] = -nom_x[3] + true_x[3];
   out_5987549380886467190[4] = -nom_x[4] + true_x[4];
   out_5987549380886467190[5] = -nom_x[5] + true_x[5];
   out_5987549380886467190[6] = -nom_x[6] + true_x[6];
   out_5987549380886467190[7] = -nom_x[7] + true_x[7];
   out_5987549380886467190[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4566808703681825058) {
   out_4566808703681825058[0] = 1.0;
   out_4566808703681825058[1] = 0.0;
   out_4566808703681825058[2] = 0.0;
   out_4566808703681825058[3] = 0.0;
   out_4566808703681825058[4] = 0.0;
   out_4566808703681825058[5] = 0.0;
   out_4566808703681825058[6] = 0.0;
   out_4566808703681825058[7] = 0.0;
   out_4566808703681825058[8] = 0.0;
   out_4566808703681825058[9] = 0.0;
   out_4566808703681825058[10] = 1.0;
   out_4566808703681825058[11] = 0.0;
   out_4566808703681825058[12] = 0.0;
   out_4566808703681825058[13] = 0.0;
   out_4566808703681825058[14] = 0.0;
   out_4566808703681825058[15] = 0.0;
   out_4566808703681825058[16] = 0.0;
   out_4566808703681825058[17] = 0.0;
   out_4566808703681825058[18] = 0.0;
   out_4566808703681825058[19] = 0.0;
   out_4566808703681825058[20] = 1.0;
   out_4566808703681825058[21] = 0.0;
   out_4566808703681825058[22] = 0.0;
   out_4566808703681825058[23] = 0.0;
   out_4566808703681825058[24] = 0.0;
   out_4566808703681825058[25] = 0.0;
   out_4566808703681825058[26] = 0.0;
   out_4566808703681825058[27] = 0.0;
   out_4566808703681825058[28] = 0.0;
   out_4566808703681825058[29] = 0.0;
   out_4566808703681825058[30] = 1.0;
   out_4566808703681825058[31] = 0.0;
   out_4566808703681825058[32] = 0.0;
   out_4566808703681825058[33] = 0.0;
   out_4566808703681825058[34] = 0.0;
   out_4566808703681825058[35] = 0.0;
   out_4566808703681825058[36] = 0.0;
   out_4566808703681825058[37] = 0.0;
   out_4566808703681825058[38] = 0.0;
   out_4566808703681825058[39] = 0.0;
   out_4566808703681825058[40] = 1.0;
   out_4566808703681825058[41] = 0.0;
   out_4566808703681825058[42] = 0.0;
   out_4566808703681825058[43] = 0.0;
   out_4566808703681825058[44] = 0.0;
   out_4566808703681825058[45] = 0.0;
   out_4566808703681825058[46] = 0.0;
   out_4566808703681825058[47] = 0.0;
   out_4566808703681825058[48] = 0.0;
   out_4566808703681825058[49] = 0.0;
   out_4566808703681825058[50] = 1.0;
   out_4566808703681825058[51] = 0.0;
   out_4566808703681825058[52] = 0.0;
   out_4566808703681825058[53] = 0.0;
   out_4566808703681825058[54] = 0.0;
   out_4566808703681825058[55] = 0.0;
   out_4566808703681825058[56] = 0.0;
   out_4566808703681825058[57] = 0.0;
   out_4566808703681825058[58] = 0.0;
   out_4566808703681825058[59] = 0.0;
   out_4566808703681825058[60] = 1.0;
   out_4566808703681825058[61] = 0.0;
   out_4566808703681825058[62] = 0.0;
   out_4566808703681825058[63] = 0.0;
   out_4566808703681825058[64] = 0.0;
   out_4566808703681825058[65] = 0.0;
   out_4566808703681825058[66] = 0.0;
   out_4566808703681825058[67] = 0.0;
   out_4566808703681825058[68] = 0.0;
   out_4566808703681825058[69] = 0.0;
   out_4566808703681825058[70] = 1.0;
   out_4566808703681825058[71] = 0.0;
   out_4566808703681825058[72] = 0.0;
   out_4566808703681825058[73] = 0.0;
   out_4566808703681825058[74] = 0.0;
   out_4566808703681825058[75] = 0.0;
   out_4566808703681825058[76] = 0.0;
   out_4566808703681825058[77] = 0.0;
   out_4566808703681825058[78] = 0.0;
   out_4566808703681825058[79] = 0.0;
   out_4566808703681825058[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_488073180215631657) {
   out_488073180215631657[0] = state[0];
   out_488073180215631657[1] = state[1];
   out_488073180215631657[2] = state[2];
   out_488073180215631657[3] = state[3];
   out_488073180215631657[4] = state[4];
   out_488073180215631657[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_488073180215631657[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_488073180215631657[7] = state[7];
   out_488073180215631657[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7883446491262668122) {
   out_7883446491262668122[0] = 1;
   out_7883446491262668122[1] = 0;
   out_7883446491262668122[2] = 0;
   out_7883446491262668122[3] = 0;
   out_7883446491262668122[4] = 0;
   out_7883446491262668122[5] = 0;
   out_7883446491262668122[6] = 0;
   out_7883446491262668122[7] = 0;
   out_7883446491262668122[8] = 0;
   out_7883446491262668122[9] = 0;
   out_7883446491262668122[10] = 1;
   out_7883446491262668122[11] = 0;
   out_7883446491262668122[12] = 0;
   out_7883446491262668122[13] = 0;
   out_7883446491262668122[14] = 0;
   out_7883446491262668122[15] = 0;
   out_7883446491262668122[16] = 0;
   out_7883446491262668122[17] = 0;
   out_7883446491262668122[18] = 0;
   out_7883446491262668122[19] = 0;
   out_7883446491262668122[20] = 1;
   out_7883446491262668122[21] = 0;
   out_7883446491262668122[22] = 0;
   out_7883446491262668122[23] = 0;
   out_7883446491262668122[24] = 0;
   out_7883446491262668122[25] = 0;
   out_7883446491262668122[26] = 0;
   out_7883446491262668122[27] = 0;
   out_7883446491262668122[28] = 0;
   out_7883446491262668122[29] = 0;
   out_7883446491262668122[30] = 1;
   out_7883446491262668122[31] = 0;
   out_7883446491262668122[32] = 0;
   out_7883446491262668122[33] = 0;
   out_7883446491262668122[34] = 0;
   out_7883446491262668122[35] = 0;
   out_7883446491262668122[36] = 0;
   out_7883446491262668122[37] = 0;
   out_7883446491262668122[38] = 0;
   out_7883446491262668122[39] = 0;
   out_7883446491262668122[40] = 1;
   out_7883446491262668122[41] = 0;
   out_7883446491262668122[42] = 0;
   out_7883446491262668122[43] = 0;
   out_7883446491262668122[44] = 0;
   out_7883446491262668122[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7883446491262668122[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7883446491262668122[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7883446491262668122[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7883446491262668122[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7883446491262668122[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7883446491262668122[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7883446491262668122[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7883446491262668122[53] = -9.8100000000000005*dt;
   out_7883446491262668122[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7883446491262668122[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7883446491262668122[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7883446491262668122[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7883446491262668122[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7883446491262668122[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7883446491262668122[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7883446491262668122[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7883446491262668122[62] = 0;
   out_7883446491262668122[63] = 0;
   out_7883446491262668122[64] = 0;
   out_7883446491262668122[65] = 0;
   out_7883446491262668122[66] = 0;
   out_7883446491262668122[67] = 0;
   out_7883446491262668122[68] = 0;
   out_7883446491262668122[69] = 0;
   out_7883446491262668122[70] = 1;
   out_7883446491262668122[71] = 0;
   out_7883446491262668122[72] = 0;
   out_7883446491262668122[73] = 0;
   out_7883446491262668122[74] = 0;
   out_7883446491262668122[75] = 0;
   out_7883446491262668122[76] = 0;
   out_7883446491262668122[77] = 0;
   out_7883446491262668122[78] = 0;
   out_7883446491262668122[79] = 0;
   out_7883446491262668122[80] = 1;
}
void h_25(double *state, double *unused, double *out_5144790627375924254) {
   out_5144790627375924254[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5958597337053866753) {
   out_5958597337053866753[0] = 0;
   out_5958597337053866753[1] = 0;
   out_5958597337053866753[2] = 0;
   out_5958597337053866753[3] = 0;
   out_5958597337053866753[4] = 0;
   out_5958597337053866753[5] = 0;
   out_5958597337053866753[6] = 1;
   out_5958597337053866753[7] = 0;
   out_5958597337053866753[8] = 0;
}
void h_24(double *state, double *unused, double *out_2742712512440648123) {
   out_2742712512440648123[0] = state[4];
   out_2742712512440648123[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2400671738251543617) {
   out_2400671738251543617[0] = 0;
   out_2400671738251543617[1] = 0;
   out_2400671738251543617[2] = 0;
   out_2400671738251543617[3] = 0;
   out_2400671738251543617[4] = 1;
   out_2400671738251543617[5] = 0;
   out_2400671738251543617[6] = 0;
   out_2400671738251543617[7] = 0;
   out_2400671738251543617[8] = 0;
   out_2400671738251543617[9] = 0;
   out_2400671738251543617[10] = 0;
   out_2400671738251543617[11] = 0;
   out_2400671738251543617[12] = 0;
   out_2400671738251543617[13] = 0;
   out_2400671738251543617[14] = 1;
   out_2400671738251543617[15] = 0;
   out_2400671738251543617[16] = 0;
   out_2400671738251543617[17] = 0;
}
void h_30(double *state, double *unused, double *out_6595422020004807421) {
   out_6595422020004807421[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3440264378546618126) {
   out_3440264378546618126[0] = 0;
   out_3440264378546618126[1] = 0;
   out_3440264378546618126[2] = 0;
   out_3440264378546618126[3] = 0;
   out_3440264378546618126[4] = 1;
   out_3440264378546618126[5] = 0;
   out_3440264378546618126[6] = 0;
   out_3440264378546618126[7] = 0;
   out_3440264378546618126[8] = 0;
}
void h_26(double *state, double *unused, double *out_6208592182623787360) {
   out_6208592182623787360[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8746643417781628639) {
   out_8746643417781628639[0] = 0;
   out_8746643417781628639[1] = 0;
   out_8746643417781628639[2] = 0;
   out_8746643417781628639[3] = 0;
   out_8746643417781628639[4] = 0;
   out_8746643417781628639[5] = 0;
   out_8746643417781628639[6] = 0;
   out_8746643417781628639[7] = 1;
   out_8746643417781628639[8] = 0;
}
void h_27(double *state, double *unused, double *out_4162706534040626142) {
   out_4162706534040626142[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5615027690347043037) {
   out_5615027690347043037[0] = 0;
   out_5615027690347043037[1] = 0;
   out_5615027690347043037[2] = 0;
   out_5615027690347043037[3] = 1;
   out_5615027690347043037[4] = 0;
   out_5615027690347043037[5] = 0;
   out_5615027690347043037[6] = 0;
   out_5615027690347043037[7] = 0;
   out_5615027690347043037[8] = 0;
}
void h_29(double *state, double *unused, double *out_7682148668361271748) {
   out_7682148668361271748[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2930033034232225942) {
   out_2930033034232225942[0] = 0;
   out_2930033034232225942[1] = 1;
   out_2930033034232225942[2] = 0;
   out_2930033034232225942[3] = 0;
   out_2930033034232225942[4] = 0;
   out_2930033034232225942[5] = 0;
   out_2930033034232225942[6] = 0;
   out_2930033034232225942[7] = 0;
   out_2930033034232225942[8] = 0;
}
void h_28(double *state, double *unused, double *out_9125086531721919374) {
   out_9125086531721919374[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8012432051301756516) {
   out_8012432051301756516[0] = 1;
   out_8012432051301756516[1] = 0;
   out_8012432051301756516[2] = 0;
   out_8012432051301756516[3] = 0;
   out_8012432051301756516[4] = 0;
   out_8012432051301756516[5] = 0;
   out_8012432051301756516[6] = 0;
   out_8012432051301756516[7] = 0;
   out_8012432051301756516[8] = 0;
}
void h_31(double *state, double *unused, double *out_5644914743754057479) {
   out_5644914743754057479[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8120435315548277163) {
   out_8120435315548277163[0] = 0;
   out_8120435315548277163[1] = 0;
   out_8120435315548277163[2] = 0;
   out_8120435315548277163[3] = 0;
   out_8120435315548277163[4] = 0;
   out_8120435315548277163[5] = 0;
   out_8120435315548277163[6] = 0;
   out_8120435315548277163[7] = 0;
   out_8120435315548277163[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3779060101704895999) {
  err_fun(nom_x, delta_x, out_3779060101704895999);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5987549380886467190) {
  inv_err_fun(nom_x, true_x, out_5987549380886467190);
}
void car_H_mod_fun(double *state, double *out_4566808703681825058) {
  H_mod_fun(state, out_4566808703681825058);
}
void car_f_fun(double *state, double dt, double *out_488073180215631657) {
  f_fun(state,  dt, out_488073180215631657);
}
void car_F_fun(double *state, double dt, double *out_7883446491262668122) {
  F_fun(state,  dt, out_7883446491262668122);
}
void car_h_25(double *state, double *unused, double *out_5144790627375924254) {
  h_25(state, unused, out_5144790627375924254);
}
void car_H_25(double *state, double *unused, double *out_5958597337053866753) {
  H_25(state, unused, out_5958597337053866753);
}
void car_h_24(double *state, double *unused, double *out_2742712512440648123) {
  h_24(state, unused, out_2742712512440648123);
}
void car_H_24(double *state, double *unused, double *out_2400671738251543617) {
  H_24(state, unused, out_2400671738251543617);
}
void car_h_30(double *state, double *unused, double *out_6595422020004807421) {
  h_30(state, unused, out_6595422020004807421);
}
void car_H_30(double *state, double *unused, double *out_3440264378546618126) {
  H_30(state, unused, out_3440264378546618126);
}
void car_h_26(double *state, double *unused, double *out_6208592182623787360) {
  h_26(state, unused, out_6208592182623787360);
}
void car_H_26(double *state, double *unused, double *out_8746643417781628639) {
  H_26(state, unused, out_8746643417781628639);
}
void car_h_27(double *state, double *unused, double *out_4162706534040626142) {
  h_27(state, unused, out_4162706534040626142);
}
void car_H_27(double *state, double *unused, double *out_5615027690347043037) {
  H_27(state, unused, out_5615027690347043037);
}
void car_h_29(double *state, double *unused, double *out_7682148668361271748) {
  h_29(state, unused, out_7682148668361271748);
}
void car_H_29(double *state, double *unused, double *out_2930033034232225942) {
  H_29(state, unused, out_2930033034232225942);
}
void car_h_28(double *state, double *unused, double *out_9125086531721919374) {
  h_28(state, unused, out_9125086531721919374);
}
void car_H_28(double *state, double *unused, double *out_8012432051301756516) {
  H_28(state, unused, out_8012432051301756516);
}
void car_h_31(double *state, double *unused, double *out_5644914743754057479) {
  h_31(state, unused, out_5644914743754057479);
}
void car_H_31(double *state, double *unused, double *out_8120435315548277163) {
  H_31(state, unused, out_8120435315548277163);
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
