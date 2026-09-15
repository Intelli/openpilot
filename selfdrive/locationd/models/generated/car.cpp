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
void err_fun(double *nom_x, double *delta_x, double *out_4522650774883987719) {
   out_4522650774883987719[0] = delta_x[0] + nom_x[0];
   out_4522650774883987719[1] = delta_x[1] + nom_x[1];
   out_4522650774883987719[2] = delta_x[2] + nom_x[2];
   out_4522650774883987719[3] = delta_x[3] + nom_x[3];
   out_4522650774883987719[4] = delta_x[4] + nom_x[4];
   out_4522650774883987719[5] = delta_x[5] + nom_x[5];
   out_4522650774883987719[6] = delta_x[6] + nom_x[6];
   out_4522650774883987719[7] = delta_x[7] + nom_x[7];
   out_4522650774883987719[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6421097817923825041) {
   out_6421097817923825041[0] = -nom_x[0] + true_x[0];
   out_6421097817923825041[1] = -nom_x[1] + true_x[1];
   out_6421097817923825041[2] = -nom_x[2] + true_x[2];
   out_6421097817923825041[3] = -nom_x[3] + true_x[3];
   out_6421097817923825041[4] = -nom_x[4] + true_x[4];
   out_6421097817923825041[5] = -nom_x[5] + true_x[5];
   out_6421097817923825041[6] = -nom_x[6] + true_x[6];
   out_6421097817923825041[7] = -nom_x[7] + true_x[7];
   out_6421097817923825041[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8354098732435681401) {
   out_8354098732435681401[0] = 1.0;
   out_8354098732435681401[1] = 0.0;
   out_8354098732435681401[2] = 0.0;
   out_8354098732435681401[3] = 0.0;
   out_8354098732435681401[4] = 0.0;
   out_8354098732435681401[5] = 0.0;
   out_8354098732435681401[6] = 0.0;
   out_8354098732435681401[7] = 0.0;
   out_8354098732435681401[8] = 0.0;
   out_8354098732435681401[9] = 0.0;
   out_8354098732435681401[10] = 1.0;
   out_8354098732435681401[11] = 0.0;
   out_8354098732435681401[12] = 0.0;
   out_8354098732435681401[13] = 0.0;
   out_8354098732435681401[14] = 0.0;
   out_8354098732435681401[15] = 0.0;
   out_8354098732435681401[16] = 0.0;
   out_8354098732435681401[17] = 0.0;
   out_8354098732435681401[18] = 0.0;
   out_8354098732435681401[19] = 0.0;
   out_8354098732435681401[20] = 1.0;
   out_8354098732435681401[21] = 0.0;
   out_8354098732435681401[22] = 0.0;
   out_8354098732435681401[23] = 0.0;
   out_8354098732435681401[24] = 0.0;
   out_8354098732435681401[25] = 0.0;
   out_8354098732435681401[26] = 0.0;
   out_8354098732435681401[27] = 0.0;
   out_8354098732435681401[28] = 0.0;
   out_8354098732435681401[29] = 0.0;
   out_8354098732435681401[30] = 1.0;
   out_8354098732435681401[31] = 0.0;
   out_8354098732435681401[32] = 0.0;
   out_8354098732435681401[33] = 0.0;
   out_8354098732435681401[34] = 0.0;
   out_8354098732435681401[35] = 0.0;
   out_8354098732435681401[36] = 0.0;
   out_8354098732435681401[37] = 0.0;
   out_8354098732435681401[38] = 0.0;
   out_8354098732435681401[39] = 0.0;
   out_8354098732435681401[40] = 1.0;
   out_8354098732435681401[41] = 0.0;
   out_8354098732435681401[42] = 0.0;
   out_8354098732435681401[43] = 0.0;
   out_8354098732435681401[44] = 0.0;
   out_8354098732435681401[45] = 0.0;
   out_8354098732435681401[46] = 0.0;
   out_8354098732435681401[47] = 0.0;
   out_8354098732435681401[48] = 0.0;
   out_8354098732435681401[49] = 0.0;
   out_8354098732435681401[50] = 1.0;
   out_8354098732435681401[51] = 0.0;
   out_8354098732435681401[52] = 0.0;
   out_8354098732435681401[53] = 0.0;
   out_8354098732435681401[54] = 0.0;
   out_8354098732435681401[55] = 0.0;
   out_8354098732435681401[56] = 0.0;
   out_8354098732435681401[57] = 0.0;
   out_8354098732435681401[58] = 0.0;
   out_8354098732435681401[59] = 0.0;
   out_8354098732435681401[60] = 1.0;
   out_8354098732435681401[61] = 0.0;
   out_8354098732435681401[62] = 0.0;
   out_8354098732435681401[63] = 0.0;
   out_8354098732435681401[64] = 0.0;
   out_8354098732435681401[65] = 0.0;
   out_8354098732435681401[66] = 0.0;
   out_8354098732435681401[67] = 0.0;
   out_8354098732435681401[68] = 0.0;
   out_8354098732435681401[69] = 0.0;
   out_8354098732435681401[70] = 1.0;
   out_8354098732435681401[71] = 0.0;
   out_8354098732435681401[72] = 0.0;
   out_8354098732435681401[73] = 0.0;
   out_8354098732435681401[74] = 0.0;
   out_8354098732435681401[75] = 0.0;
   out_8354098732435681401[76] = 0.0;
   out_8354098732435681401[77] = 0.0;
   out_8354098732435681401[78] = 0.0;
   out_8354098732435681401[79] = 0.0;
   out_8354098732435681401[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_618802638011462566) {
   out_618802638011462566[0] = state[0];
   out_618802638011462566[1] = state[1];
   out_618802638011462566[2] = state[2];
   out_618802638011462566[3] = state[3];
   out_618802638011462566[4] = state[4];
   out_618802638011462566[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_618802638011462566[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_618802638011462566[7] = state[7];
   out_618802638011462566[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3307921169342290232) {
   out_3307921169342290232[0] = 1;
   out_3307921169342290232[1] = 0;
   out_3307921169342290232[2] = 0;
   out_3307921169342290232[3] = 0;
   out_3307921169342290232[4] = 0;
   out_3307921169342290232[5] = 0;
   out_3307921169342290232[6] = 0;
   out_3307921169342290232[7] = 0;
   out_3307921169342290232[8] = 0;
   out_3307921169342290232[9] = 0;
   out_3307921169342290232[10] = 1;
   out_3307921169342290232[11] = 0;
   out_3307921169342290232[12] = 0;
   out_3307921169342290232[13] = 0;
   out_3307921169342290232[14] = 0;
   out_3307921169342290232[15] = 0;
   out_3307921169342290232[16] = 0;
   out_3307921169342290232[17] = 0;
   out_3307921169342290232[18] = 0;
   out_3307921169342290232[19] = 0;
   out_3307921169342290232[20] = 1;
   out_3307921169342290232[21] = 0;
   out_3307921169342290232[22] = 0;
   out_3307921169342290232[23] = 0;
   out_3307921169342290232[24] = 0;
   out_3307921169342290232[25] = 0;
   out_3307921169342290232[26] = 0;
   out_3307921169342290232[27] = 0;
   out_3307921169342290232[28] = 0;
   out_3307921169342290232[29] = 0;
   out_3307921169342290232[30] = 1;
   out_3307921169342290232[31] = 0;
   out_3307921169342290232[32] = 0;
   out_3307921169342290232[33] = 0;
   out_3307921169342290232[34] = 0;
   out_3307921169342290232[35] = 0;
   out_3307921169342290232[36] = 0;
   out_3307921169342290232[37] = 0;
   out_3307921169342290232[38] = 0;
   out_3307921169342290232[39] = 0;
   out_3307921169342290232[40] = 1;
   out_3307921169342290232[41] = 0;
   out_3307921169342290232[42] = 0;
   out_3307921169342290232[43] = 0;
   out_3307921169342290232[44] = 0;
   out_3307921169342290232[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3307921169342290232[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3307921169342290232[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3307921169342290232[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3307921169342290232[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3307921169342290232[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3307921169342290232[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3307921169342290232[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3307921169342290232[53] = -9.8100000000000005*dt;
   out_3307921169342290232[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3307921169342290232[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3307921169342290232[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3307921169342290232[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3307921169342290232[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3307921169342290232[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3307921169342290232[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3307921169342290232[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3307921169342290232[62] = 0;
   out_3307921169342290232[63] = 0;
   out_3307921169342290232[64] = 0;
   out_3307921169342290232[65] = 0;
   out_3307921169342290232[66] = 0;
   out_3307921169342290232[67] = 0;
   out_3307921169342290232[68] = 0;
   out_3307921169342290232[69] = 0;
   out_3307921169342290232[70] = 1;
   out_3307921169342290232[71] = 0;
   out_3307921169342290232[72] = 0;
   out_3307921169342290232[73] = 0;
   out_3307921169342290232[74] = 0;
   out_3307921169342290232[75] = 0;
   out_3307921169342290232[76] = 0;
   out_3307921169342290232[77] = 0;
   out_3307921169342290232[78] = 0;
   out_3307921169342290232[79] = 0;
   out_3307921169342290232[80] = 1;
}
void h_25(double *state, double *unused, double *out_2859996149114624228) {
   out_2859996149114624228[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3450406907251016561) {
   out_3450406907251016561[0] = 0;
   out_3450406907251016561[1] = 0;
   out_3450406907251016561[2] = 0;
   out_3450406907251016561[3] = 0;
   out_3450406907251016561[4] = 0;
   out_3450406907251016561[5] = 0;
   out_3450406907251016561[6] = 1;
   out_3450406907251016561[7] = 0;
   out_3450406907251016561[8] = 0;
}
void h_24(double *state, double *unused, double *out_164729919387917572) {
   out_164729919387917572[0] = state[4];
   out_164729919387917572[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4396947103623005501) {
   out_4396947103623005501[0] = 0;
   out_4396947103623005501[1] = 0;
   out_4396947103623005501[2] = 0;
   out_4396947103623005501[3] = 0;
   out_4396947103623005501[4] = 1;
   out_4396947103623005501[5] = 0;
   out_4396947103623005501[6] = 0;
   out_4396947103623005501[7] = 0;
   out_4396947103623005501[8] = 0;
   out_4396947103623005501[9] = 0;
   out_4396947103623005501[10] = 0;
   out_4396947103623005501[11] = 0;
   out_4396947103623005501[12] = 0;
   out_4396947103623005501[13] = 0;
   out_4396947103623005501[14] = 1;
   out_4396947103623005501[15] = 0;
   out_4396947103623005501[16] = 0;
   out_4396947103623005501[17] = 0;
}
void h_30(double *state, double *unused, double *out_3053736877556124145) {
   out_3053736877556124145[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7978103237378624759) {
   out_7978103237378624759[0] = 0;
   out_7978103237378624759[1] = 0;
   out_7978103237378624759[2] = 0;
   out_7978103237378624759[3] = 0;
   out_7978103237378624759[4] = 1;
   out_7978103237378624759[5] = 0;
   out_7978103237378624759[6] = 0;
   out_7978103237378624759[7] = 0;
   out_7978103237378624759[8] = 0;
}
void h_26(double *state, double *unused, double *out_3657052762232601662) {
   out_3657052762232601662[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7191910226125072785) {
   out_7191910226125072785[0] = 0;
   out_7191910226125072785[1] = 0;
   out_7191910226125072785[2] = 0;
   out_7191910226125072785[3] = 0;
   out_7191910226125072785[4] = 0;
   out_7191910226125072785[5] = 0;
   out_7191910226125072785[6] = 0;
   out_7191910226125072785[7] = 1;
   out_7191910226125072785[8] = 0;
}
void h_27(double *state, double *unused, double *out_7861669416775469873) {
   out_7861669416775469873[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8293877524530501946) {
   out_8293877524530501946[0] = 0;
   out_8293877524530501946[1] = 0;
   out_8293877524530501946[2] = 0;
   out_8293877524530501946[3] = 1;
   out_8293877524530501946[4] = 0;
   out_8293877524530501946[5] = 0;
   out_8293877524530501946[6] = 0;
   out_8293877524530501946[7] = 0;
   out_8293877524530501946[8] = 0;
}
void h_29(double *state, double *unused, double *out_3997246730457786580) {
   out_3997246730457786580[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7467871893064232575) {
   out_7467871893064232575[0] = 0;
   out_7467871893064232575[1] = 1;
   out_7467871893064232575[2] = 0;
   out_7467871893064232575[3] = 0;
   out_7467871893064232575[4] = 0;
   out_7467871893064232575[5] = 0;
   out_7467871893064232575[6] = 0;
   out_7467871893064232575[7] = 0;
   out_7467871893064232575[8] = 0;
}
void h_28(double *state, double *unused, double *out_858906712982404094) {
   out_858906712982404094[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5504241621498906324) {
   out_5504241621498906324[0] = 1;
   out_5504241621498906324[1] = 0;
   out_5504241621498906324[2] = 0;
   out_5504241621498906324[3] = 0;
   out_5504241621498906324[4] = 0;
   out_5504241621498906324[5] = 0;
   out_5504241621498906324[6] = 0;
   out_5504241621498906324[7] = 0;
   out_5504241621498906324[8] = 0;
}
void h_31(double *state, double *unused, double *out_5310946536877911850) {
   out_5310946536877911850[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7818118328358424261) {
   out_7818118328358424261[0] = 0;
   out_7818118328358424261[1] = 0;
   out_7818118328358424261[2] = 0;
   out_7818118328358424261[3] = 0;
   out_7818118328358424261[4] = 0;
   out_7818118328358424261[5] = 0;
   out_7818118328358424261[6] = 0;
   out_7818118328358424261[7] = 0;
   out_7818118328358424261[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4522650774883987719) {
  err_fun(nom_x, delta_x, out_4522650774883987719);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6421097817923825041) {
  inv_err_fun(nom_x, true_x, out_6421097817923825041);
}
void car_H_mod_fun(double *state, double *out_8354098732435681401) {
  H_mod_fun(state, out_8354098732435681401);
}
void car_f_fun(double *state, double dt, double *out_618802638011462566) {
  f_fun(state,  dt, out_618802638011462566);
}
void car_F_fun(double *state, double dt, double *out_3307921169342290232) {
  F_fun(state,  dt, out_3307921169342290232);
}
void car_h_25(double *state, double *unused, double *out_2859996149114624228) {
  h_25(state, unused, out_2859996149114624228);
}
void car_H_25(double *state, double *unused, double *out_3450406907251016561) {
  H_25(state, unused, out_3450406907251016561);
}
void car_h_24(double *state, double *unused, double *out_164729919387917572) {
  h_24(state, unused, out_164729919387917572);
}
void car_H_24(double *state, double *unused, double *out_4396947103623005501) {
  H_24(state, unused, out_4396947103623005501);
}
void car_h_30(double *state, double *unused, double *out_3053736877556124145) {
  h_30(state, unused, out_3053736877556124145);
}
void car_H_30(double *state, double *unused, double *out_7978103237378624759) {
  H_30(state, unused, out_7978103237378624759);
}
void car_h_26(double *state, double *unused, double *out_3657052762232601662) {
  h_26(state, unused, out_3657052762232601662);
}
void car_H_26(double *state, double *unused, double *out_7191910226125072785) {
  H_26(state, unused, out_7191910226125072785);
}
void car_h_27(double *state, double *unused, double *out_7861669416775469873) {
  h_27(state, unused, out_7861669416775469873);
}
void car_H_27(double *state, double *unused, double *out_8293877524530501946) {
  H_27(state, unused, out_8293877524530501946);
}
void car_h_29(double *state, double *unused, double *out_3997246730457786580) {
  h_29(state, unused, out_3997246730457786580);
}
void car_H_29(double *state, double *unused, double *out_7467871893064232575) {
  H_29(state, unused, out_7467871893064232575);
}
void car_h_28(double *state, double *unused, double *out_858906712982404094) {
  h_28(state, unused, out_858906712982404094);
}
void car_H_28(double *state, double *unused, double *out_5504241621498906324) {
  H_28(state, unused, out_5504241621498906324);
}
void car_h_31(double *state, double *unused, double *out_5310946536877911850) {
  h_31(state, unused, out_5310946536877911850);
}
void car_H_31(double *state, double *unused, double *out_7818118328358424261) {
  H_31(state, unused, out_7818118328358424261);
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
