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
void err_fun(double *nom_x, double *delta_x, double *out_4505651181940075839) {
   out_4505651181940075839[0] = delta_x[0] + nom_x[0];
   out_4505651181940075839[1] = delta_x[1] + nom_x[1];
   out_4505651181940075839[2] = delta_x[2] + nom_x[2];
   out_4505651181940075839[3] = delta_x[3] + nom_x[3];
   out_4505651181940075839[4] = delta_x[4] + nom_x[4];
   out_4505651181940075839[5] = delta_x[5] + nom_x[5];
   out_4505651181940075839[6] = delta_x[6] + nom_x[6];
   out_4505651181940075839[7] = delta_x[7] + nom_x[7];
   out_4505651181940075839[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1646596662830797608) {
   out_1646596662830797608[0] = -nom_x[0] + true_x[0];
   out_1646596662830797608[1] = -nom_x[1] + true_x[1];
   out_1646596662830797608[2] = -nom_x[2] + true_x[2];
   out_1646596662830797608[3] = -nom_x[3] + true_x[3];
   out_1646596662830797608[4] = -nom_x[4] + true_x[4];
   out_1646596662830797608[5] = -nom_x[5] + true_x[5];
   out_1646596662830797608[6] = -nom_x[6] + true_x[6];
   out_1646596662830797608[7] = -nom_x[7] + true_x[7];
   out_1646596662830797608[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5501956759725950600) {
   out_5501956759725950600[0] = 1.0;
   out_5501956759725950600[1] = 0.0;
   out_5501956759725950600[2] = 0.0;
   out_5501956759725950600[3] = 0.0;
   out_5501956759725950600[4] = 0.0;
   out_5501956759725950600[5] = 0.0;
   out_5501956759725950600[6] = 0.0;
   out_5501956759725950600[7] = 0.0;
   out_5501956759725950600[8] = 0.0;
   out_5501956759725950600[9] = 0.0;
   out_5501956759725950600[10] = 1.0;
   out_5501956759725950600[11] = 0.0;
   out_5501956759725950600[12] = 0.0;
   out_5501956759725950600[13] = 0.0;
   out_5501956759725950600[14] = 0.0;
   out_5501956759725950600[15] = 0.0;
   out_5501956759725950600[16] = 0.0;
   out_5501956759725950600[17] = 0.0;
   out_5501956759725950600[18] = 0.0;
   out_5501956759725950600[19] = 0.0;
   out_5501956759725950600[20] = 1.0;
   out_5501956759725950600[21] = 0.0;
   out_5501956759725950600[22] = 0.0;
   out_5501956759725950600[23] = 0.0;
   out_5501956759725950600[24] = 0.0;
   out_5501956759725950600[25] = 0.0;
   out_5501956759725950600[26] = 0.0;
   out_5501956759725950600[27] = 0.0;
   out_5501956759725950600[28] = 0.0;
   out_5501956759725950600[29] = 0.0;
   out_5501956759725950600[30] = 1.0;
   out_5501956759725950600[31] = 0.0;
   out_5501956759725950600[32] = 0.0;
   out_5501956759725950600[33] = 0.0;
   out_5501956759725950600[34] = 0.0;
   out_5501956759725950600[35] = 0.0;
   out_5501956759725950600[36] = 0.0;
   out_5501956759725950600[37] = 0.0;
   out_5501956759725950600[38] = 0.0;
   out_5501956759725950600[39] = 0.0;
   out_5501956759725950600[40] = 1.0;
   out_5501956759725950600[41] = 0.0;
   out_5501956759725950600[42] = 0.0;
   out_5501956759725950600[43] = 0.0;
   out_5501956759725950600[44] = 0.0;
   out_5501956759725950600[45] = 0.0;
   out_5501956759725950600[46] = 0.0;
   out_5501956759725950600[47] = 0.0;
   out_5501956759725950600[48] = 0.0;
   out_5501956759725950600[49] = 0.0;
   out_5501956759725950600[50] = 1.0;
   out_5501956759725950600[51] = 0.0;
   out_5501956759725950600[52] = 0.0;
   out_5501956759725950600[53] = 0.0;
   out_5501956759725950600[54] = 0.0;
   out_5501956759725950600[55] = 0.0;
   out_5501956759725950600[56] = 0.0;
   out_5501956759725950600[57] = 0.0;
   out_5501956759725950600[58] = 0.0;
   out_5501956759725950600[59] = 0.0;
   out_5501956759725950600[60] = 1.0;
   out_5501956759725950600[61] = 0.0;
   out_5501956759725950600[62] = 0.0;
   out_5501956759725950600[63] = 0.0;
   out_5501956759725950600[64] = 0.0;
   out_5501956759725950600[65] = 0.0;
   out_5501956759725950600[66] = 0.0;
   out_5501956759725950600[67] = 0.0;
   out_5501956759725950600[68] = 0.0;
   out_5501956759725950600[69] = 0.0;
   out_5501956759725950600[70] = 1.0;
   out_5501956759725950600[71] = 0.0;
   out_5501956759725950600[72] = 0.0;
   out_5501956759725950600[73] = 0.0;
   out_5501956759725950600[74] = 0.0;
   out_5501956759725950600[75] = 0.0;
   out_5501956759725950600[76] = 0.0;
   out_5501956759725950600[77] = 0.0;
   out_5501956759725950600[78] = 0.0;
   out_5501956759725950600[79] = 0.0;
   out_5501956759725950600[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4174408190255373619) {
   out_4174408190255373619[0] = state[0];
   out_4174408190255373619[1] = state[1];
   out_4174408190255373619[2] = state[2];
   out_4174408190255373619[3] = state[3];
   out_4174408190255373619[4] = state[4];
   out_4174408190255373619[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4174408190255373619[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4174408190255373619[7] = state[7];
   out_4174408190255373619[8] = state[8];
}
void F_fun(double *state, double dt, double *out_584677443248040024) {
   out_584677443248040024[0] = 1;
   out_584677443248040024[1] = 0;
   out_584677443248040024[2] = 0;
   out_584677443248040024[3] = 0;
   out_584677443248040024[4] = 0;
   out_584677443248040024[5] = 0;
   out_584677443248040024[6] = 0;
   out_584677443248040024[7] = 0;
   out_584677443248040024[8] = 0;
   out_584677443248040024[9] = 0;
   out_584677443248040024[10] = 1;
   out_584677443248040024[11] = 0;
   out_584677443248040024[12] = 0;
   out_584677443248040024[13] = 0;
   out_584677443248040024[14] = 0;
   out_584677443248040024[15] = 0;
   out_584677443248040024[16] = 0;
   out_584677443248040024[17] = 0;
   out_584677443248040024[18] = 0;
   out_584677443248040024[19] = 0;
   out_584677443248040024[20] = 1;
   out_584677443248040024[21] = 0;
   out_584677443248040024[22] = 0;
   out_584677443248040024[23] = 0;
   out_584677443248040024[24] = 0;
   out_584677443248040024[25] = 0;
   out_584677443248040024[26] = 0;
   out_584677443248040024[27] = 0;
   out_584677443248040024[28] = 0;
   out_584677443248040024[29] = 0;
   out_584677443248040024[30] = 1;
   out_584677443248040024[31] = 0;
   out_584677443248040024[32] = 0;
   out_584677443248040024[33] = 0;
   out_584677443248040024[34] = 0;
   out_584677443248040024[35] = 0;
   out_584677443248040024[36] = 0;
   out_584677443248040024[37] = 0;
   out_584677443248040024[38] = 0;
   out_584677443248040024[39] = 0;
   out_584677443248040024[40] = 1;
   out_584677443248040024[41] = 0;
   out_584677443248040024[42] = 0;
   out_584677443248040024[43] = 0;
   out_584677443248040024[44] = 0;
   out_584677443248040024[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_584677443248040024[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_584677443248040024[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_584677443248040024[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_584677443248040024[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_584677443248040024[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_584677443248040024[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_584677443248040024[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_584677443248040024[53] = -9.8100000000000005*dt;
   out_584677443248040024[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_584677443248040024[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_584677443248040024[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_584677443248040024[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_584677443248040024[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_584677443248040024[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_584677443248040024[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_584677443248040024[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_584677443248040024[62] = 0;
   out_584677443248040024[63] = 0;
   out_584677443248040024[64] = 0;
   out_584677443248040024[65] = 0;
   out_584677443248040024[66] = 0;
   out_584677443248040024[67] = 0;
   out_584677443248040024[68] = 0;
   out_584677443248040024[69] = 0;
   out_584677443248040024[70] = 1;
   out_584677443248040024[71] = 0;
   out_584677443248040024[72] = 0;
   out_584677443248040024[73] = 0;
   out_584677443248040024[74] = 0;
   out_584677443248040024[75] = 0;
   out_584677443248040024[76] = 0;
   out_584677443248040024[77] = 0;
   out_584677443248040024[78] = 0;
   out_584677443248040024[79] = 0;
   out_584677443248040024[80] = 1;
}
void h_25(double *state, double *unused, double *out_1009943400890808144) {
   out_1009943400890808144[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1978976109736458923) {
   out_1978976109736458923[0] = 0;
   out_1978976109736458923[1] = 0;
   out_1978976109736458923[2] = 0;
   out_1978976109736458923[3] = 0;
   out_1978976109736458923[4] = 0;
   out_1978976109736458923[5] = 0;
   out_1978976109736458923[6] = 1;
   out_1978976109736458923[7] = 0;
   out_1978976109736458923[8] = 0;
}
void h_24(double *state, double *unused, double *out_390532478353196657) {
   out_390532478353196657[0] = state[4];
   out_390532478353196657[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1578949489065864213) {
   out_1578949489065864213[0] = 0;
   out_1578949489065864213[1] = 0;
   out_1578949489065864213[2] = 0;
   out_1578949489065864213[3] = 0;
   out_1578949489065864213[4] = 1;
   out_1578949489065864213[5] = 0;
   out_1578949489065864213[6] = 0;
   out_1578949489065864213[7] = 0;
   out_1578949489065864213[8] = 0;
   out_1578949489065864213[9] = 0;
   out_1578949489065864213[10] = 0;
   out_1578949489065864213[11] = 0;
   out_1578949489065864213[12] = 0;
   out_1578949489065864213[13] = 0;
   out_1578949489065864213[14] = 1;
   out_1578949489065864213[15] = 0;
   out_1578949489065864213[16] = 0;
   out_1578949489065864213[17] = 0;
}
void h_30(double *state, double *unused, double *out_7597771327367103307) {
   out_7597771327367103307[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4937714231755157832) {
   out_4937714231755157832[0] = 0;
   out_4937714231755157832[1] = 0;
   out_4937714231755157832[2] = 0;
   out_4937714231755157832[3] = 0;
   out_4937714231755157832[4] = 1;
   out_4937714231755157832[5] = 0;
   out_4937714231755157832[6] = 0;
   out_4937714231755157832[7] = 0;
   out_4937714231755157832[8] = 0;
}
void h_26(double *state, double *unused, double *out_4449931228928599163) {
   out_4449931228928599163[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5720479428610515147) {
   out_5720479428610515147[0] = 0;
   out_5720479428610515147[1] = 0;
   out_5720479428610515147[2] = 0;
   out_5720479428610515147[3] = 0;
   out_5720479428610515147[4] = 0;
   out_5720479428610515147[5] = 0;
   out_5720479428610515147[6] = 0;
   out_5720479428610515147[7] = 1;
   out_5720479428610515147[8] = 0;
}
void h_27(double *state, double *unused, double *out_1178344241810182114) {
   out_1178344241810182114[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4283078368680123904) {
   out_4283078368680123904[0] = 0;
   out_4283078368680123904[1] = 0;
   out_4283078368680123904[2] = 0;
   out_4283078368680123904[3] = 1;
   out_4283078368680123904[4] = 0;
   out_4283078368680123904[5] = 0;
   out_4283078368680123904[6] = 0;
   out_4283078368680123904[7] = 0;
   out_4283078368680123904[8] = 0;
}
void h_29(double *state, double *unused, double *out_2131135826473755983) {
   out_2131135826473755983[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1598083712565306809) {
   out_1598083712565306809[0] = 0;
   out_1598083712565306809[1] = 1;
   out_1598083712565306809[2] = 0;
   out_1598083712565306809[3] = 0;
   out_1598083712565306809[4] = 0;
   out_1598083712565306809[5] = 0;
   out_1598083712565306809[6] = 0;
   out_1598083712565306809[7] = 0;
   out_1598083712565306809[8] = 0;
}
void h_28(double *state, double *unused, double *out_6936329155803920070) {
   out_6936329155803920070[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4032810823984348686) {
   out_4032810823984348686[0] = 1;
   out_4032810823984348686[1] = 0;
   out_4032810823984348686[2] = 0;
   out_4032810823984348686[3] = 0;
   out_4032810823984348686[4] = 0;
   out_4032810823984348686[5] = 0;
   out_4032810823984348686[6] = 0;
   out_4032810823984348686[7] = 0;
   out_4032810823984348686[8] = 0;
}
void h_31(double *state, double *unused, double *out_2828025537148972505) {
   out_2828025537148972505[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1948330147859498495) {
   out_1948330147859498495[0] = 0;
   out_1948330147859498495[1] = 0;
   out_1948330147859498495[2] = 0;
   out_1948330147859498495[3] = 0;
   out_1948330147859498495[4] = 0;
   out_1948330147859498495[5] = 0;
   out_1948330147859498495[6] = 0;
   out_1948330147859498495[7] = 0;
   out_1948330147859498495[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4505651181940075839) {
  err_fun(nom_x, delta_x, out_4505651181940075839);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1646596662830797608) {
  inv_err_fun(nom_x, true_x, out_1646596662830797608);
}
void car_H_mod_fun(double *state, double *out_5501956759725950600) {
  H_mod_fun(state, out_5501956759725950600);
}
void car_f_fun(double *state, double dt, double *out_4174408190255373619) {
  f_fun(state,  dt, out_4174408190255373619);
}
void car_F_fun(double *state, double dt, double *out_584677443248040024) {
  F_fun(state,  dt, out_584677443248040024);
}
void car_h_25(double *state, double *unused, double *out_1009943400890808144) {
  h_25(state, unused, out_1009943400890808144);
}
void car_H_25(double *state, double *unused, double *out_1978976109736458923) {
  H_25(state, unused, out_1978976109736458923);
}
void car_h_24(double *state, double *unused, double *out_390532478353196657) {
  h_24(state, unused, out_390532478353196657);
}
void car_H_24(double *state, double *unused, double *out_1578949489065864213) {
  H_24(state, unused, out_1578949489065864213);
}
void car_h_30(double *state, double *unused, double *out_7597771327367103307) {
  h_30(state, unused, out_7597771327367103307);
}
void car_H_30(double *state, double *unused, double *out_4937714231755157832) {
  H_30(state, unused, out_4937714231755157832);
}
void car_h_26(double *state, double *unused, double *out_4449931228928599163) {
  h_26(state, unused, out_4449931228928599163);
}
void car_H_26(double *state, double *unused, double *out_5720479428610515147) {
  H_26(state, unused, out_5720479428610515147);
}
void car_h_27(double *state, double *unused, double *out_1178344241810182114) {
  h_27(state, unused, out_1178344241810182114);
}
void car_H_27(double *state, double *unused, double *out_4283078368680123904) {
  H_27(state, unused, out_4283078368680123904);
}
void car_h_29(double *state, double *unused, double *out_2131135826473755983) {
  h_29(state, unused, out_2131135826473755983);
}
void car_H_29(double *state, double *unused, double *out_1598083712565306809) {
  H_29(state, unused, out_1598083712565306809);
}
void car_h_28(double *state, double *unused, double *out_6936329155803920070) {
  h_28(state, unused, out_6936329155803920070);
}
void car_H_28(double *state, double *unused, double *out_4032810823984348686) {
  H_28(state, unused, out_4032810823984348686);
}
void car_h_31(double *state, double *unused, double *out_2828025537148972505) {
  h_31(state, unused, out_2828025537148972505);
}
void car_H_31(double *state, double *unused, double *out_1948330147859498495) {
  H_31(state, unused, out_1948330147859498495);
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
