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
void err_fun(double *nom_x, double *delta_x, double *out_8658023881255996922) {
   out_8658023881255996922[0] = delta_x[0] + nom_x[0];
   out_8658023881255996922[1] = delta_x[1] + nom_x[1];
   out_8658023881255996922[2] = delta_x[2] + nom_x[2];
   out_8658023881255996922[3] = delta_x[3] + nom_x[3];
   out_8658023881255996922[4] = delta_x[4] + nom_x[4];
   out_8658023881255996922[5] = delta_x[5] + nom_x[5];
   out_8658023881255996922[6] = delta_x[6] + nom_x[6];
   out_8658023881255996922[7] = delta_x[7] + nom_x[7];
   out_8658023881255996922[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4511098242413357935) {
   out_4511098242413357935[0] = -nom_x[0] + true_x[0];
   out_4511098242413357935[1] = -nom_x[1] + true_x[1];
   out_4511098242413357935[2] = -nom_x[2] + true_x[2];
   out_4511098242413357935[3] = -nom_x[3] + true_x[3];
   out_4511098242413357935[4] = -nom_x[4] + true_x[4];
   out_4511098242413357935[5] = -nom_x[5] + true_x[5];
   out_4511098242413357935[6] = -nom_x[6] + true_x[6];
   out_4511098242413357935[7] = -nom_x[7] + true_x[7];
   out_4511098242413357935[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7419113753789213258) {
   out_7419113753789213258[0] = 1.0;
   out_7419113753789213258[1] = 0.0;
   out_7419113753789213258[2] = 0.0;
   out_7419113753789213258[3] = 0.0;
   out_7419113753789213258[4] = 0.0;
   out_7419113753789213258[5] = 0.0;
   out_7419113753789213258[6] = 0.0;
   out_7419113753789213258[7] = 0.0;
   out_7419113753789213258[8] = 0.0;
   out_7419113753789213258[9] = 0.0;
   out_7419113753789213258[10] = 1.0;
   out_7419113753789213258[11] = 0.0;
   out_7419113753789213258[12] = 0.0;
   out_7419113753789213258[13] = 0.0;
   out_7419113753789213258[14] = 0.0;
   out_7419113753789213258[15] = 0.0;
   out_7419113753789213258[16] = 0.0;
   out_7419113753789213258[17] = 0.0;
   out_7419113753789213258[18] = 0.0;
   out_7419113753789213258[19] = 0.0;
   out_7419113753789213258[20] = 1.0;
   out_7419113753789213258[21] = 0.0;
   out_7419113753789213258[22] = 0.0;
   out_7419113753789213258[23] = 0.0;
   out_7419113753789213258[24] = 0.0;
   out_7419113753789213258[25] = 0.0;
   out_7419113753789213258[26] = 0.0;
   out_7419113753789213258[27] = 0.0;
   out_7419113753789213258[28] = 0.0;
   out_7419113753789213258[29] = 0.0;
   out_7419113753789213258[30] = 1.0;
   out_7419113753789213258[31] = 0.0;
   out_7419113753789213258[32] = 0.0;
   out_7419113753789213258[33] = 0.0;
   out_7419113753789213258[34] = 0.0;
   out_7419113753789213258[35] = 0.0;
   out_7419113753789213258[36] = 0.0;
   out_7419113753789213258[37] = 0.0;
   out_7419113753789213258[38] = 0.0;
   out_7419113753789213258[39] = 0.0;
   out_7419113753789213258[40] = 1.0;
   out_7419113753789213258[41] = 0.0;
   out_7419113753789213258[42] = 0.0;
   out_7419113753789213258[43] = 0.0;
   out_7419113753789213258[44] = 0.0;
   out_7419113753789213258[45] = 0.0;
   out_7419113753789213258[46] = 0.0;
   out_7419113753789213258[47] = 0.0;
   out_7419113753789213258[48] = 0.0;
   out_7419113753789213258[49] = 0.0;
   out_7419113753789213258[50] = 1.0;
   out_7419113753789213258[51] = 0.0;
   out_7419113753789213258[52] = 0.0;
   out_7419113753789213258[53] = 0.0;
   out_7419113753789213258[54] = 0.0;
   out_7419113753789213258[55] = 0.0;
   out_7419113753789213258[56] = 0.0;
   out_7419113753789213258[57] = 0.0;
   out_7419113753789213258[58] = 0.0;
   out_7419113753789213258[59] = 0.0;
   out_7419113753789213258[60] = 1.0;
   out_7419113753789213258[61] = 0.0;
   out_7419113753789213258[62] = 0.0;
   out_7419113753789213258[63] = 0.0;
   out_7419113753789213258[64] = 0.0;
   out_7419113753789213258[65] = 0.0;
   out_7419113753789213258[66] = 0.0;
   out_7419113753789213258[67] = 0.0;
   out_7419113753789213258[68] = 0.0;
   out_7419113753789213258[69] = 0.0;
   out_7419113753789213258[70] = 1.0;
   out_7419113753789213258[71] = 0.0;
   out_7419113753789213258[72] = 0.0;
   out_7419113753789213258[73] = 0.0;
   out_7419113753789213258[74] = 0.0;
   out_7419113753789213258[75] = 0.0;
   out_7419113753789213258[76] = 0.0;
   out_7419113753789213258[77] = 0.0;
   out_7419113753789213258[78] = 0.0;
   out_7419113753789213258[79] = 0.0;
   out_7419113753789213258[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6687108190872076920) {
   out_6687108190872076920[0] = state[0];
   out_6687108190872076920[1] = state[1];
   out_6687108190872076920[2] = state[2];
   out_6687108190872076920[3] = state[3];
   out_6687108190872076920[4] = state[4];
   out_6687108190872076920[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6687108190872076920[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6687108190872076920[7] = state[7];
   out_6687108190872076920[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4340098819845909276) {
   out_4340098819845909276[0] = 1;
   out_4340098819845909276[1] = 0;
   out_4340098819845909276[2] = 0;
   out_4340098819845909276[3] = 0;
   out_4340098819845909276[4] = 0;
   out_4340098819845909276[5] = 0;
   out_4340098819845909276[6] = 0;
   out_4340098819845909276[7] = 0;
   out_4340098819845909276[8] = 0;
   out_4340098819845909276[9] = 0;
   out_4340098819845909276[10] = 1;
   out_4340098819845909276[11] = 0;
   out_4340098819845909276[12] = 0;
   out_4340098819845909276[13] = 0;
   out_4340098819845909276[14] = 0;
   out_4340098819845909276[15] = 0;
   out_4340098819845909276[16] = 0;
   out_4340098819845909276[17] = 0;
   out_4340098819845909276[18] = 0;
   out_4340098819845909276[19] = 0;
   out_4340098819845909276[20] = 1;
   out_4340098819845909276[21] = 0;
   out_4340098819845909276[22] = 0;
   out_4340098819845909276[23] = 0;
   out_4340098819845909276[24] = 0;
   out_4340098819845909276[25] = 0;
   out_4340098819845909276[26] = 0;
   out_4340098819845909276[27] = 0;
   out_4340098819845909276[28] = 0;
   out_4340098819845909276[29] = 0;
   out_4340098819845909276[30] = 1;
   out_4340098819845909276[31] = 0;
   out_4340098819845909276[32] = 0;
   out_4340098819845909276[33] = 0;
   out_4340098819845909276[34] = 0;
   out_4340098819845909276[35] = 0;
   out_4340098819845909276[36] = 0;
   out_4340098819845909276[37] = 0;
   out_4340098819845909276[38] = 0;
   out_4340098819845909276[39] = 0;
   out_4340098819845909276[40] = 1;
   out_4340098819845909276[41] = 0;
   out_4340098819845909276[42] = 0;
   out_4340098819845909276[43] = 0;
   out_4340098819845909276[44] = 0;
   out_4340098819845909276[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4340098819845909276[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4340098819845909276[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4340098819845909276[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4340098819845909276[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4340098819845909276[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4340098819845909276[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4340098819845909276[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4340098819845909276[53] = -9.8100000000000005*dt;
   out_4340098819845909276[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4340098819845909276[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4340098819845909276[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4340098819845909276[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4340098819845909276[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4340098819845909276[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4340098819845909276[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4340098819845909276[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4340098819845909276[62] = 0;
   out_4340098819845909276[63] = 0;
   out_4340098819845909276[64] = 0;
   out_4340098819845909276[65] = 0;
   out_4340098819845909276[66] = 0;
   out_4340098819845909276[67] = 0;
   out_4340098819845909276[68] = 0;
   out_4340098819845909276[69] = 0;
   out_4340098819845909276[70] = 1;
   out_4340098819845909276[71] = 0;
   out_4340098819845909276[72] = 0;
   out_4340098819845909276[73] = 0;
   out_4340098819845909276[74] = 0;
   out_4340098819845909276[75] = 0;
   out_4340098819845909276[76] = 0;
   out_4340098819845909276[77] = 0;
   out_4340098819845909276[78] = 0;
   out_4340098819845909276[79] = 0;
   out_4340098819845909276[80] = 1;
}
void h_25(double *state, double *unused, double *out_2884651234761005866) {
   out_2884651234761005866[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8723452863981184878) {
   out_8723452863981184878[0] = 0;
   out_8723452863981184878[1] = 0;
   out_8723452863981184878[2] = 0;
   out_8723452863981184878[3] = 0;
   out_8723452863981184878[4] = 0;
   out_8723452863981184878[5] = 0;
   out_8723452863981184878[6] = 1;
   out_8723452863981184878[7] = 0;
   out_8723452863981184878[8] = 0;
}
void h_24(double *state, double *unused, double *out_5410236178001565575) {
   out_5410236178001565575[0] = state[4];
   out_5410236178001565575[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6497745080002316316) {
   out_6497745080002316316[0] = 0;
   out_6497745080002316316[1] = 0;
   out_6497745080002316316[2] = 0;
   out_6497745080002316316[3] = 0;
   out_6497745080002316316[4] = 1;
   out_6497745080002316316[5] = 0;
   out_6497745080002316316[6] = 0;
   out_6497745080002316316[7] = 0;
   out_6497745080002316316[8] = 0;
   out_6497745080002316316[9] = 0;
   out_6497745080002316316[10] = 0;
   out_6497745080002316316[11] = 0;
   out_6497745080002316316[12] = 0;
   out_6497745080002316316[13] = 0;
   out_6497745080002316316[14] = 1;
   out_6497745080002316316[15] = 0;
   out_6497745080002316316[16] = 0;
   out_6497745080002316316[17] = 0;
}
void h_30(double *state, double *unused, double *out_3486069392374369420) {
   out_3486069392374369420[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1806762522489568123) {
   out_1806762522489568123[0] = 0;
   out_1806762522489568123[1] = 0;
   out_1806762522489568123[2] = 0;
   out_1806762522489568123[3] = 0;
   out_1806762522489568123[4] = 1;
   out_1806762522489568123[5] = 0;
   out_1806762522489568123[6] = 0;
   out_1806762522489568123[7] = 0;
   out_1806762522489568123[8] = 0;
}
void h_26(double *state, double *unused, double *out_4646686544616951732) {
   out_4646686544616951732[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5981787890854310514) {
   out_5981787890854310514[0] = 0;
   out_5981787890854310514[1] = 0;
   out_5981787890854310514[2] = 0;
   out_5981787890854310514[3] = 0;
   out_5981787890854310514[4] = 0;
   out_5981787890854310514[5] = 0;
   out_5981787890854310514[6] = 0;
   out_5981787890854310514[7] = 1;
   out_5981787890854310514[8] = 0;
}
void h_27(double *state, double *unused, double *out_2117022032899839779) {
   out_2117022032899839779[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3981525834289993034) {
   out_3981525834289993034[0] = 0;
   out_3981525834289993034[1] = 0;
   out_3981525834289993034[2] = 0;
   out_3981525834289993034[3] = 1;
   out_3981525834289993034[4] = 0;
   out_3981525834289993034[5] = 0;
   out_3981525834289993034[6] = 0;
   out_3981525834289993034[7] = 0;
   out_3981525834289993034[8] = 0;
}
void h_29(double *state, double *unused, double *out_8704849959376134942) {
   out_8704849959376134942[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1296531178175175939) {
   out_1296531178175175939[0] = 0;
   out_1296531178175175939[1] = 1;
   out_1296531178175175939[2] = 0;
   out_1296531178175175939[3] = 0;
   out_1296531178175175939[4] = 0;
   out_1296531178175175939[5] = 0;
   out_1296531178175175939[6] = 0;
   out_1296531178175175939[7] = 0;
   out_1296531178175175939[8] = 0;
}
void h_28(double *state, double *unused, double *out_2720337917576317296) {
   out_2720337917576317296[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6378930195244706513) {
   out_6378930195244706513[0] = 1;
   out_6378930195244706513[1] = 0;
   out_6378930195244706513[2] = 0;
   out_6378930195244706513[3] = 0;
   out_6378930195244706513[4] = 0;
   out_6378930195244706513[5] = 0;
   out_6378930195244706513[6] = 0;
   out_6378930195244706513[7] = 0;
   out_6378930195244706513[8] = 0;
}
void h_31(double *state, double *unused, double *out_6522100763015028216) {
   out_6522100763015028216[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8692806902104224450) {
   out_8692806902104224450[0] = 0;
   out_8692806902104224450[1] = 0;
   out_8692806902104224450[2] = 0;
   out_8692806902104224450[3] = 0;
   out_8692806902104224450[4] = 0;
   out_8692806902104224450[5] = 0;
   out_8692806902104224450[6] = 0;
   out_8692806902104224450[7] = 0;
   out_8692806902104224450[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8658023881255996922) {
  err_fun(nom_x, delta_x, out_8658023881255996922);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4511098242413357935) {
  inv_err_fun(nom_x, true_x, out_4511098242413357935);
}
void car_H_mod_fun(double *state, double *out_7419113753789213258) {
  H_mod_fun(state, out_7419113753789213258);
}
void car_f_fun(double *state, double dt, double *out_6687108190872076920) {
  f_fun(state,  dt, out_6687108190872076920);
}
void car_F_fun(double *state, double dt, double *out_4340098819845909276) {
  F_fun(state,  dt, out_4340098819845909276);
}
void car_h_25(double *state, double *unused, double *out_2884651234761005866) {
  h_25(state, unused, out_2884651234761005866);
}
void car_H_25(double *state, double *unused, double *out_8723452863981184878) {
  H_25(state, unused, out_8723452863981184878);
}
void car_h_24(double *state, double *unused, double *out_5410236178001565575) {
  h_24(state, unused, out_5410236178001565575);
}
void car_H_24(double *state, double *unused, double *out_6497745080002316316) {
  H_24(state, unused, out_6497745080002316316);
}
void car_h_30(double *state, double *unused, double *out_3486069392374369420) {
  h_30(state, unused, out_3486069392374369420);
}
void car_H_30(double *state, double *unused, double *out_1806762522489568123) {
  H_30(state, unused, out_1806762522489568123);
}
void car_h_26(double *state, double *unused, double *out_4646686544616951732) {
  h_26(state, unused, out_4646686544616951732);
}
void car_H_26(double *state, double *unused, double *out_5981787890854310514) {
  H_26(state, unused, out_5981787890854310514);
}
void car_h_27(double *state, double *unused, double *out_2117022032899839779) {
  h_27(state, unused, out_2117022032899839779);
}
void car_H_27(double *state, double *unused, double *out_3981525834289993034) {
  H_27(state, unused, out_3981525834289993034);
}
void car_h_29(double *state, double *unused, double *out_8704849959376134942) {
  h_29(state, unused, out_8704849959376134942);
}
void car_H_29(double *state, double *unused, double *out_1296531178175175939) {
  H_29(state, unused, out_1296531178175175939);
}
void car_h_28(double *state, double *unused, double *out_2720337917576317296) {
  h_28(state, unused, out_2720337917576317296);
}
void car_H_28(double *state, double *unused, double *out_6378930195244706513) {
  H_28(state, unused, out_6378930195244706513);
}
void car_h_31(double *state, double *unused, double *out_6522100763015028216) {
  h_31(state, unused, out_6522100763015028216);
}
void car_H_31(double *state, double *unused, double *out_8692806902104224450) {
  H_31(state, unused, out_8692806902104224450);
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
