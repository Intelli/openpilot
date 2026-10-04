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
void err_fun(double *nom_x, double *delta_x, double *out_8960374984193016023) {
   out_8960374984193016023[0] = delta_x[0] + nom_x[0];
   out_8960374984193016023[1] = delta_x[1] + nom_x[1];
   out_8960374984193016023[2] = delta_x[2] + nom_x[2];
   out_8960374984193016023[3] = delta_x[3] + nom_x[3];
   out_8960374984193016023[4] = delta_x[4] + nom_x[4];
   out_8960374984193016023[5] = delta_x[5] + nom_x[5];
   out_8960374984193016023[6] = delta_x[6] + nom_x[6];
   out_8960374984193016023[7] = delta_x[7] + nom_x[7];
   out_8960374984193016023[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8607819760565032145) {
   out_8607819760565032145[0] = -nom_x[0] + true_x[0];
   out_8607819760565032145[1] = -nom_x[1] + true_x[1];
   out_8607819760565032145[2] = -nom_x[2] + true_x[2];
   out_8607819760565032145[3] = -nom_x[3] + true_x[3];
   out_8607819760565032145[4] = -nom_x[4] + true_x[4];
   out_8607819760565032145[5] = -nom_x[5] + true_x[5];
   out_8607819760565032145[6] = -nom_x[6] + true_x[6];
   out_8607819760565032145[7] = -nom_x[7] + true_x[7];
   out_8607819760565032145[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6865712900868131600) {
   out_6865712900868131600[0] = 1.0;
   out_6865712900868131600[1] = 0.0;
   out_6865712900868131600[2] = 0.0;
   out_6865712900868131600[3] = 0.0;
   out_6865712900868131600[4] = 0.0;
   out_6865712900868131600[5] = 0.0;
   out_6865712900868131600[6] = 0.0;
   out_6865712900868131600[7] = 0.0;
   out_6865712900868131600[8] = 0.0;
   out_6865712900868131600[9] = 0.0;
   out_6865712900868131600[10] = 1.0;
   out_6865712900868131600[11] = 0.0;
   out_6865712900868131600[12] = 0.0;
   out_6865712900868131600[13] = 0.0;
   out_6865712900868131600[14] = 0.0;
   out_6865712900868131600[15] = 0.0;
   out_6865712900868131600[16] = 0.0;
   out_6865712900868131600[17] = 0.0;
   out_6865712900868131600[18] = 0.0;
   out_6865712900868131600[19] = 0.0;
   out_6865712900868131600[20] = 1.0;
   out_6865712900868131600[21] = 0.0;
   out_6865712900868131600[22] = 0.0;
   out_6865712900868131600[23] = 0.0;
   out_6865712900868131600[24] = 0.0;
   out_6865712900868131600[25] = 0.0;
   out_6865712900868131600[26] = 0.0;
   out_6865712900868131600[27] = 0.0;
   out_6865712900868131600[28] = 0.0;
   out_6865712900868131600[29] = 0.0;
   out_6865712900868131600[30] = 1.0;
   out_6865712900868131600[31] = 0.0;
   out_6865712900868131600[32] = 0.0;
   out_6865712900868131600[33] = 0.0;
   out_6865712900868131600[34] = 0.0;
   out_6865712900868131600[35] = 0.0;
   out_6865712900868131600[36] = 0.0;
   out_6865712900868131600[37] = 0.0;
   out_6865712900868131600[38] = 0.0;
   out_6865712900868131600[39] = 0.0;
   out_6865712900868131600[40] = 1.0;
   out_6865712900868131600[41] = 0.0;
   out_6865712900868131600[42] = 0.0;
   out_6865712900868131600[43] = 0.0;
   out_6865712900868131600[44] = 0.0;
   out_6865712900868131600[45] = 0.0;
   out_6865712900868131600[46] = 0.0;
   out_6865712900868131600[47] = 0.0;
   out_6865712900868131600[48] = 0.0;
   out_6865712900868131600[49] = 0.0;
   out_6865712900868131600[50] = 1.0;
   out_6865712900868131600[51] = 0.0;
   out_6865712900868131600[52] = 0.0;
   out_6865712900868131600[53] = 0.0;
   out_6865712900868131600[54] = 0.0;
   out_6865712900868131600[55] = 0.0;
   out_6865712900868131600[56] = 0.0;
   out_6865712900868131600[57] = 0.0;
   out_6865712900868131600[58] = 0.0;
   out_6865712900868131600[59] = 0.0;
   out_6865712900868131600[60] = 1.0;
   out_6865712900868131600[61] = 0.0;
   out_6865712900868131600[62] = 0.0;
   out_6865712900868131600[63] = 0.0;
   out_6865712900868131600[64] = 0.0;
   out_6865712900868131600[65] = 0.0;
   out_6865712900868131600[66] = 0.0;
   out_6865712900868131600[67] = 0.0;
   out_6865712900868131600[68] = 0.0;
   out_6865712900868131600[69] = 0.0;
   out_6865712900868131600[70] = 1.0;
   out_6865712900868131600[71] = 0.0;
   out_6865712900868131600[72] = 0.0;
   out_6865712900868131600[73] = 0.0;
   out_6865712900868131600[74] = 0.0;
   out_6865712900868131600[75] = 0.0;
   out_6865712900868131600[76] = 0.0;
   out_6865712900868131600[77] = 0.0;
   out_6865712900868131600[78] = 0.0;
   out_6865712900868131600[79] = 0.0;
   out_6865712900868131600[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3046687401328038034) {
   out_3046687401328038034[0] = state[0];
   out_3046687401328038034[1] = state[1];
   out_3046687401328038034[2] = state[2];
   out_3046687401328038034[3] = state[3];
   out_3046687401328038034[4] = state[4];
   out_3046687401328038034[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3046687401328038034[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3046687401328038034[7] = state[7];
   out_3046687401328038034[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8168474853840000782) {
   out_8168474853840000782[0] = 1;
   out_8168474853840000782[1] = 0;
   out_8168474853840000782[2] = 0;
   out_8168474853840000782[3] = 0;
   out_8168474853840000782[4] = 0;
   out_8168474853840000782[5] = 0;
   out_8168474853840000782[6] = 0;
   out_8168474853840000782[7] = 0;
   out_8168474853840000782[8] = 0;
   out_8168474853840000782[9] = 0;
   out_8168474853840000782[10] = 1;
   out_8168474853840000782[11] = 0;
   out_8168474853840000782[12] = 0;
   out_8168474853840000782[13] = 0;
   out_8168474853840000782[14] = 0;
   out_8168474853840000782[15] = 0;
   out_8168474853840000782[16] = 0;
   out_8168474853840000782[17] = 0;
   out_8168474853840000782[18] = 0;
   out_8168474853840000782[19] = 0;
   out_8168474853840000782[20] = 1;
   out_8168474853840000782[21] = 0;
   out_8168474853840000782[22] = 0;
   out_8168474853840000782[23] = 0;
   out_8168474853840000782[24] = 0;
   out_8168474853840000782[25] = 0;
   out_8168474853840000782[26] = 0;
   out_8168474853840000782[27] = 0;
   out_8168474853840000782[28] = 0;
   out_8168474853840000782[29] = 0;
   out_8168474853840000782[30] = 1;
   out_8168474853840000782[31] = 0;
   out_8168474853840000782[32] = 0;
   out_8168474853840000782[33] = 0;
   out_8168474853840000782[34] = 0;
   out_8168474853840000782[35] = 0;
   out_8168474853840000782[36] = 0;
   out_8168474853840000782[37] = 0;
   out_8168474853840000782[38] = 0;
   out_8168474853840000782[39] = 0;
   out_8168474853840000782[40] = 1;
   out_8168474853840000782[41] = 0;
   out_8168474853840000782[42] = 0;
   out_8168474853840000782[43] = 0;
   out_8168474853840000782[44] = 0;
   out_8168474853840000782[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8168474853840000782[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8168474853840000782[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8168474853840000782[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8168474853840000782[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8168474853840000782[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8168474853840000782[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8168474853840000782[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8168474853840000782[53] = -9.8100000000000005*dt;
   out_8168474853840000782[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8168474853840000782[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8168474853840000782[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8168474853840000782[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8168474853840000782[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8168474853840000782[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8168474853840000782[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8168474853840000782[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8168474853840000782[62] = 0;
   out_8168474853840000782[63] = 0;
   out_8168474853840000782[64] = 0;
   out_8168474853840000782[65] = 0;
   out_8168474853840000782[66] = 0;
   out_8168474853840000782[67] = 0;
   out_8168474853840000782[68] = 0;
   out_8168474853840000782[69] = 0;
   out_8168474853840000782[70] = 1;
   out_8168474853840000782[71] = 0;
   out_8168474853840000782[72] = 0;
   out_8168474853840000782[73] = 0;
   out_8168474853840000782[74] = 0;
   out_8168474853840000782[75] = 0;
   out_8168474853840000782[76] = 0;
   out_8168474853840000782[77] = 0;
   out_8168474853840000782[78] = 0;
   out_8168474853840000782[79] = 0;
   out_8168474853840000782[80] = 1;
}
void h_25(double *state, double *unused, double *out_3704639410232761343) {
   out_3704639410232761343[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2387842946929182779) {
   out_2387842946929182779[0] = 0;
   out_2387842946929182779[1] = 0;
   out_2387842946929182779[2] = 0;
   out_2387842946929182779[3] = 0;
   out_2387842946929182779[4] = 0;
   out_2387842946929182779[5] = 0;
   out_2387842946929182779[6] = 1;
   out_2387842946929182779[7] = 0;
   out_2387842946929182779[8] = 0;
}
void h_24(double *state, double *unused, double *out_5815696604988810764) {
   out_5815696604988810764[0] = state[4];
   out_5815696604988810764[1] = state[5];
}
void H_24(double *state, double *unused, double *out_215193347923683213) {
   out_215193347923683213[0] = 0;
   out_215193347923683213[1] = 0;
   out_215193347923683213[2] = 0;
   out_215193347923683213[3] = 0;
   out_215193347923683213[4] = 1;
   out_215193347923683213[5] = 0;
   out_215193347923683213[6] = 0;
   out_215193347923683213[7] = 0;
   out_215193347923683213[8] = 0;
   out_215193347923683213[9] = 0;
   out_215193347923683213[10] = 0;
   out_215193347923683213[11] = 0;
   out_215193347923683213[12] = 0;
   out_215193347923683213[13] = 0;
   out_215193347923683213[14] = 1;
   out_215193347923683213[15] = 0;
   out_215193347923683213[16] = 0;
   out_215193347923683213[17] = 0;
}
void h_30(double *state, double *unused, double *out_3066195816117589593) {
   out_3066195816117589593[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4906175905436431406) {
   out_4906175905436431406[0] = 0;
   out_4906175905436431406[1] = 0;
   out_4906175905436431406[2] = 0;
   out_4906175905436431406[3] = 0;
   out_4906175905436431406[4] = 1;
   out_4906175905436431406[5] = 0;
   out_4906175905436431406[6] = 0;
   out_4906175905436431406[7] = 0;
   out_4906175905436431406[8] = 0;
}
void h_26(double *state, double *unused, double *out_6584238793325964883) {
   out_6584238793325964883[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1353660371944873445) {
   out_1353660371944873445[0] = 0;
   out_1353660371944873445[1] = 0;
   out_1353660371944873445[2] = 0;
   out_1353660371944873445[3] = 0;
   out_1353660371944873445[4] = 0;
   out_1353660371944873445[5] = 0;
   out_1353660371944873445[6] = 0;
   out_1353660371944873445[7] = 1;
   out_1353660371944873445[8] = 0;
}
void h_27(double *state, double *unused, double *out_2761129557331098908) {
   out_2761129557331098908[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7129769976620374623) {
   out_7129769976620374623[0] = 0;
   out_7129769976620374623[1] = 0;
   out_7129769976620374623[2] = 0;
   out_7129769976620374623[3] = 1;
   out_7129769976620374623[4] = 0;
   out_7129769976620374623[5] = 0;
   out_7129769976620374623[6] = 0;
   out_7129769976620374623[7] = 0;
   out_7129769976620374623[8] = 0;
}
void h_29(double *state, double *unused, double *out_6398579085585121258) {
   out_6398579085585121258[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5416407249750823590) {
   out_5416407249750823590[0] = 0;
   out_5416407249750823590[1] = 1;
   out_5416407249750823590[2] = 0;
   out_5416407249750823590[3] = 0;
   out_5416407249750823590[4] = 0;
   out_5416407249750823590[5] = 0;
   out_5416407249750823590[6] = 0;
   out_5416407249750823590[7] = 0;
   out_5416407249750823590[8] = 0;
}
void h_28(double *state, double *unused, double *out_3364445442007576425) {
   out_3364445442007576425[0] = state[0];
}
void H_28(double *state, double *unused, double *out_334008232681293016) {
   out_334008232681293016[0] = 1;
   out_334008232681293016[1] = 0;
   out_334008232681293016[2] = 0;
   out_334008232681293016[3] = 0;
   out_334008232681293016[4] = 0;
   out_334008232681293016[5] = 0;
   out_334008232681293016[6] = 0;
   out_334008232681293016[7] = 0;
   out_334008232681293016[8] = 0;
}
void h_31(double *state, double *unused, double *out_5188269700685231698) {
   out_5188269700685231698[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1979868474178224921) {
   out_1979868474178224921[0] = 0;
   out_1979868474178224921[1] = 0;
   out_1979868474178224921[2] = 0;
   out_1979868474178224921[3] = 0;
   out_1979868474178224921[4] = 0;
   out_1979868474178224921[5] = 0;
   out_1979868474178224921[6] = 0;
   out_1979868474178224921[7] = 0;
   out_1979868474178224921[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8960374984193016023) {
  err_fun(nom_x, delta_x, out_8960374984193016023);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8607819760565032145) {
  inv_err_fun(nom_x, true_x, out_8607819760565032145);
}
void car_H_mod_fun(double *state, double *out_6865712900868131600) {
  H_mod_fun(state, out_6865712900868131600);
}
void car_f_fun(double *state, double dt, double *out_3046687401328038034) {
  f_fun(state,  dt, out_3046687401328038034);
}
void car_F_fun(double *state, double dt, double *out_8168474853840000782) {
  F_fun(state,  dt, out_8168474853840000782);
}
void car_h_25(double *state, double *unused, double *out_3704639410232761343) {
  h_25(state, unused, out_3704639410232761343);
}
void car_H_25(double *state, double *unused, double *out_2387842946929182779) {
  H_25(state, unused, out_2387842946929182779);
}
void car_h_24(double *state, double *unused, double *out_5815696604988810764) {
  h_24(state, unused, out_5815696604988810764);
}
void car_H_24(double *state, double *unused, double *out_215193347923683213) {
  H_24(state, unused, out_215193347923683213);
}
void car_h_30(double *state, double *unused, double *out_3066195816117589593) {
  h_30(state, unused, out_3066195816117589593);
}
void car_H_30(double *state, double *unused, double *out_4906175905436431406) {
  H_30(state, unused, out_4906175905436431406);
}
void car_h_26(double *state, double *unused, double *out_6584238793325964883) {
  h_26(state, unused, out_6584238793325964883);
}
void car_H_26(double *state, double *unused, double *out_1353660371944873445) {
  H_26(state, unused, out_1353660371944873445);
}
void car_h_27(double *state, double *unused, double *out_2761129557331098908) {
  h_27(state, unused, out_2761129557331098908);
}
void car_H_27(double *state, double *unused, double *out_7129769976620374623) {
  H_27(state, unused, out_7129769976620374623);
}
void car_h_29(double *state, double *unused, double *out_6398579085585121258) {
  h_29(state, unused, out_6398579085585121258);
}
void car_H_29(double *state, double *unused, double *out_5416407249750823590) {
  H_29(state, unused, out_5416407249750823590);
}
void car_h_28(double *state, double *unused, double *out_3364445442007576425) {
  h_28(state, unused, out_3364445442007576425);
}
void car_H_28(double *state, double *unused, double *out_334008232681293016) {
  H_28(state, unused, out_334008232681293016);
}
void car_h_31(double *state, double *unused, double *out_5188269700685231698) {
  h_31(state, unused, out_5188269700685231698);
}
void car_H_31(double *state, double *unused, double *out_1979868474178224921) {
  H_31(state, unused, out_1979868474178224921);
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
