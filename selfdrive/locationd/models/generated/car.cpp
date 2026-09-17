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
void err_fun(double *nom_x, double *delta_x, double *out_269603389839755742) {
   out_269603389839755742[0] = delta_x[0] + nom_x[0];
   out_269603389839755742[1] = delta_x[1] + nom_x[1];
   out_269603389839755742[2] = delta_x[2] + nom_x[2];
   out_269603389839755742[3] = delta_x[3] + nom_x[3];
   out_269603389839755742[4] = delta_x[4] + nom_x[4];
   out_269603389839755742[5] = delta_x[5] + nom_x[5];
   out_269603389839755742[6] = delta_x[6] + nom_x[6];
   out_269603389839755742[7] = delta_x[7] + nom_x[7];
   out_269603389839755742[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_592438703867529051) {
   out_592438703867529051[0] = -nom_x[0] + true_x[0];
   out_592438703867529051[1] = -nom_x[1] + true_x[1];
   out_592438703867529051[2] = -nom_x[2] + true_x[2];
   out_592438703867529051[3] = -nom_x[3] + true_x[3];
   out_592438703867529051[4] = -nom_x[4] + true_x[4];
   out_592438703867529051[5] = -nom_x[5] + true_x[5];
   out_592438703867529051[6] = -nom_x[6] + true_x[6];
   out_592438703867529051[7] = -nom_x[7] + true_x[7];
   out_592438703867529051[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2647141062540633245) {
   out_2647141062540633245[0] = 1.0;
   out_2647141062540633245[1] = 0.0;
   out_2647141062540633245[2] = 0.0;
   out_2647141062540633245[3] = 0.0;
   out_2647141062540633245[4] = 0.0;
   out_2647141062540633245[5] = 0.0;
   out_2647141062540633245[6] = 0.0;
   out_2647141062540633245[7] = 0.0;
   out_2647141062540633245[8] = 0.0;
   out_2647141062540633245[9] = 0.0;
   out_2647141062540633245[10] = 1.0;
   out_2647141062540633245[11] = 0.0;
   out_2647141062540633245[12] = 0.0;
   out_2647141062540633245[13] = 0.0;
   out_2647141062540633245[14] = 0.0;
   out_2647141062540633245[15] = 0.0;
   out_2647141062540633245[16] = 0.0;
   out_2647141062540633245[17] = 0.0;
   out_2647141062540633245[18] = 0.0;
   out_2647141062540633245[19] = 0.0;
   out_2647141062540633245[20] = 1.0;
   out_2647141062540633245[21] = 0.0;
   out_2647141062540633245[22] = 0.0;
   out_2647141062540633245[23] = 0.0;
   out_2647141062540633245[24] = 0.0;
   out_2647141062540633245[25] = 0.0;
   out_2647141062540633245[26] = 0.0;
   out_2647141062540633245[27] = 0.0;
   out_2647141062540633245[28] = 0.0;
   out_2647141062540633245[29] = 0.0;
   out_2647141062540633245[30] = 1.0;
   out_2647141062540633245[31] = 0.0;
   out_2647141062540633245[32] = 0.0;
   out_2647141062540633245[33] = 0.0;
   out_2647141062540633245[34] = 0.0;
   out_2647141062540633245[35] = 0.0;
   out_2647141062540633245[36] = 0.0;
   out_2647141062540633245[37] = 0.0;
   out_2647141062540633245[38] = 0.0;
   out_2647141062540633245[39] = 0.0;
   out_2647141062540633245[40] = 1.0;
   out_2647141062540633245[41] = 0.0;
   out_2647141062540633245[42] = 0.0;
   out_2647141062540633245[43] = 0.0;
   out_2647141062540633245[44] = 0.0;
   out_2647141062540633245[45] = 0.0;
   out_2647141062540633245[46] = 0.0;
   out_2647141062540633245[47] = 0.0;
   out_2647141062540633245[48] = 0.0;
   out_2647141062540633245[49] = 0.0;
   out_2647141062540633245[50] = 1.0;
   out_2647141062540633245[51] = 0.0;
   out_2647141062540633245[52] = 0.0;
   out_2647141062540633245[53] = 0.0;
   out_2647141062540633245[54] = 0.0;
   out_2647141062540633245[55] = 0.0;
   out_2647141062540633245[56] = 0.0;
   out_2647141062540633245[57] = 0.0;
   out_2647141062540633245[58] = 0.0;
   out_2647141062540633245[59] = 0.0;
   out_2647141062540633245[60] = 1.0;
   out_2647141062540633245[61] = 0.0;
   out_2647141062540633245[62] = 0.0;
   out_2647141062540633245[63] = 0.0;
   out_2647141062540633245[64] = 0.0;
   out_2647141062540633245[65] = 0.0;
   out_2647141062540633245[66] = 0.0;
   out_2647141062540633245[67] = 0.0;
   out_2647141062540633245[68] = 0.0;
   out_2647141062540633245[69] = 0.0;
   out_2647141062540633245[70] = 1.0;
   out_2647141062540633245[71] = 0.0;
   out_2647141062540633245[72] = 0.0;
   out_2647141062540633245[73] = 0.0;
   out_2647141062540633245[74] = 0.0;
   out_2647141062540633245[75] = 0.0;
   out_2647141062540633245[76] = 0.0;
   out_2647141062540633245[77] = 0.0;
   out_2647141062540633245[78] = 0.0;
   out_2647141062540633245[79] = 0.0;
   out_2647141062540633245[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6099382505660640035) {
   out_6099382505660640035[0] = state[0];
   out_6099382505660640035[1] = state[1];
   out_6099382505660640035[2] = state[2];
   out_6099382505660640035[3] = state[3];
   out_6099382505660640035[4] = state[4];
   out_6099382505660640035[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6099382505660640035[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6099382505660640035[7] = state[7];
   out_6099382505660640035[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6313816615875393456) {
   out_6313816615875393456[0] = 1;
   out_6313816615875393456[1] = 0;
   out_6313816615875393456[2] = 0;
   out_6313816615875393456[3] = 0;
   out_6313816615875393456[4] = 0;
   out_6313816615875393456[5] = 0;
   out_6313816615875393456[6] = 0;
   out_6313816615875393456[7] = 0;
   out_6313816615875393456[8] = 0;
   out_6313816615875393456[9] = 0;
   out_6313816615875393456[10] = 1;
   out_6313816615875393456[11] = 0;
   out_6313816615875393456[12] = 0;
   out_6313816615875393456[13] = 0;
   out_6313816615875393456[14] = 0;
   out_6313816615875393456[15] = 0;
   out_6313816615875393456[16] = 0;
   out_6313816615875393456[17] = 0;
   out_6313816615875393456[18] = 0;
   out_6313816615875393456[19] = 0;
   out_6313816615875393456[20] = 1;
   out_6313816615875393456[21] = 0;
   out_6313816615875393456[22] = 0;
   out_6313816615875393456[23] = 0;
   out_6313816615875393456[24] = 0;
   out_6313816615875393456[25] = 0;
   out_6313816615875393456[26] = 0;
   out_6313816615875393456[27] = 0;
   out_6313816615875393456[28] = 0;
   out_6313816615875393456[29] = 0;
   out_6313816615875393456[30] = 1;
   out_6313816615875393456[31] = 0;
   out_6313816615875393456[32] = 0;
   out_6313816615875393456[33] = 0;
   out_6313816615875393456[34] = 0;
   out_6313816615875393456[35] = 0;
   out_6313816615875393456[36] = 0;
   out_6313816615875393456[37] = 0;
   out_6313816615875393456[38] = 0;
   out_6313816615875393456[39] = 0;
   out_6313816615875393456[40] = 1;
   out_6313816615875393456[41] = 0;
   out_6313816615875393456[42] = 0;
   out_6313816615875393456[43] = 0;
   out_6313816615875393456[44] = 0;
   out_6313816615875393456[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6313816615875393456[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6313816615875393456[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6313816615875393456[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6313816615875393456[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6313816615875393456[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6313816615875393456[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6313816615875393456[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6313816615875393456[53] = -9.8100000000000005*dt;
   out_6313816615875393456[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6313816615875393456[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6313816615875393456[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6313816615875393456[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6313816615875393456[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6313816615875393456[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6313816615875393456[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6313816615875393456[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6313816615875393456[62] = 0;
   out_6313816615875393456[63] = 0;
   out_6313816615875393456[64] = 0;
   out_6313816615875393456[65] = 0;
   out_6313816615875393456[66] = 0;
   out_6313816615875393456[67] = 0;
   out_6313816615875393456[68] = 0;
   out_6313816615875393456[69] = 0;
   out_6313816615875393456[70] = 1;
   out_6313816615875393456[71] = 0;
   out_6313816615875393456[72] = 0;
   out_6313816615875393456[73] = 0;
   out_6313816615875393456[74] = 0;
   out_6313816615875393456[75] = 0;
   out_6313816615875393456[76] = 0;
   out_6313816615875393456[77] = 0;
   out_6313816615875393456[78] = 0;
   out_6313816615875393456[79] = 0;
   out_6313816615875393456[80] = 1;
}
void h_25(double *state, double *unused, double *out_5356303473462709754) {
   out_5356303473462709754[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3849881897349396706) {
   out_3849881897349396706[0] = 0;
   out_3849881897349396706[1] = 0;
   out_3849881897349396706[2] = 0;
   out_3849881897349396706[3] = 0;
   out_3849881897349396706[4] = 0;
   out_3849881897349396706[5] = 0;
   out_3849881897349396706[6] = 1;
   out_3849881897349396706[7] = 0;
   out_3849881897349396706[8] = 0;
}
void h_24(double *state, double *unused, double *out_1055368816343579033) {
   out_1055368816343579033[0] = state[4];
   out_1055368816343579033[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8718696762377103558) {
   out_8718696762377103558[0] = 0;
   out_8718696762377103558[1] = 0;
   out_8718696762377103558[2] = 0;
   out_8718696762377103558[3] = 0;
   out_8718696762377103558[4] = 1;
   out_8718696762377103558[5] = 0;
   out_8718696762377103558[6] = 0;
   out_8718696762377103558[7] = 0;
   out_8718696762377103558[8] = 0;
   out_8718696762377103558[9] = 0;
   out_8718696762377103558[10] = 0;
   out_8718696762377103558[11] = 0;
   out_8718696762377103558[12] = 0;
   out_8718696762377103558[13] = 0;
   out_8718696762377103558[14] = 1;
   out_8718696762377103558[15] = 0;
   out_8718696762377103558[16] = 0;
   out_8718696762377103558[17] = 0;
}
void h_30(double *state, double *unused, double *out_1414531752887641182) {
   out_1414531752887641182[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8377578227477004904) {
   out_8377578227477004904[0] = 0;
   out_8377578227477004904[1] = 0;
   out_8377578227477004904[2] = 0;
   out_8377578227477004904[3] = 0;
   out_8377578227477004904[4] = 1;
   out_8377578227477004904[5] = 0;
   out_8377578227477004904[6] = 0;
   out_8377578227477004904[7] = 0;
   out_8377578227477004904[8] = 0;
}
void h_26(double *state, double *unused, double *out_6416205020548486827) {
   out_6416205020548486827[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7591385216223452930) {
   out_7591385216223452930[0] = 0;
   out_7591385216223452930[1] = 0;
   out_7591385216223452930[2] = 0;
   out_7591385216223452930[3] = 0;
   out_7591385216223452930[4] = 0;
   out_7591385216223452930[5] = 0;
   out_7591385216223452930[6] = 0;
   out_7591385216223452930[7] = 1;
   out_7591385216223452930[8] = 0;
}
void h_27(double *state, double *unused, double *out_7672649654478288824) {
   out_7672649654478288824[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6153984156293061687) {
   out_6153984156293061687[0] = 0;
   out_6153984156293061687[1] = 0;
   out_6153984156293061687[2] = 0;
   out_6153984156293061687[3] = 1;
   out_6153984156293061687[4] = 0;
   out_6153984156293061687[5] = 0;
   out_6153984156293061687[6] = 0;
   out_6153984156293061687[7] = 0;
   out_6153984156293061687[8] = 0;
}
void h_29(double *state, double *unused, double *out_811215868211163665) {
   out_811215868211163665[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7867346883162612720) {
   out_7867346883162612720[0] = 0;
   out_7867346883162612720[1] = 1;
   out_7867346883162612720[2] = 0;
   out_7867346883162612720[3] = 0;
   out_7867346883162612720[4] = 0;
   out_7867346883162612720[5] = 0;
   out_7867346883162612720[6] = 0;
   out_7867346883162612720[7] = 0;
   out_7867346883162612720[8] = 0;
}
void h_28(double *state, double *unused, double *out_5016109505237524836) {
   out_5016109505237524836[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5496998173477408322) {
   out_5496998173477408322[0] = 1;
   out_5496998173477408322[1] = 0;
   out_5496998173477408322[2] = 0;
   out_5496998173477408322[3] = 0;
   out_5496998173477408322[4] = 0;
   out_5496998173477408322[5] = 0;
   out_5496998173477408322[6] = 0;
   out_5496998173477408322[7] = 0;
   out_5496998173477408322[8] = 0;
}
void h_31(double *state, double *unused, double *out_5327175343426169421) {
   out_5327175343426169421[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8217593318456804406) {
   out_8217593318456804406[0] = 0;
   out_8217593318456804406[1] = 0;
   out_8217593318456804406[2] = 0;
   out_8217593318456804406[3] = 0;
   out_8217593318456804406[4] = 0;
   out_8217593318456804406[5] = 0;
   out_8217593318456804406[6] = 0;
   out_8217593318456804406[7] = 0;
   out_8217593318456804406[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_269603389839755742) {
  err_fun(nom_x, delta_x, out_269603389839755742);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_592438703867529051) {
  inv_err_fun(nom_x, true_x, out_592438703867529051);
}
void car_H_mod_fun(double *state, double *out_2647141062540633245) {
  H_mod_fun(state, out_2647141062540633245);
}
void car_f_fun(double *state, double dt, double *out_6099382505660640035) {
  f_fun(state,  dt, out_6099382505660640035);
}
void car_F_fun(double *state, double dt, double *out_6313816615875393456) {
  F_fun(state,  dt, out_6313816615875393456);
}
void car_h_25(double *state, double *unused, double *out_5356303473462709754) {
  h_25(state, unused, out_5356303473462709754);
}
void car_H_25(double *state, double *unused, double *out_3849881897349396706) {
  H_25(state, unused, out_3849881897349396706);
}
void car_h_24(double *state, double *unused, double *out_1055368816343579033) {
  h_24(state, unused, out_1055368816343579033);
}
void car_H_24(double *state, double *unused, double *out_8718696762377103558) {
  H_24(state, unused, out_8718696762377103558);
}
void car_h_30(double *state, double *unused, double *out_1414531752887641182) {
  h_30(state, unused, out_1414531752887641182);
}
void car_H_30(double *state, double *unused, double *out_8377578227477004904) {
  H_30(state, unused, out_8377578227477004904);
}
void car_h_26(double *state, double *unused, double *out_6416205020548486827) {
  h_26(state, unused, out_6416205020548486827);
}
void car_H_26(double *state, double *unused, double *out_7591385216223452930) {
  H_26(state, unused, out_7591385216223452930);
}
void car_h_27(double *state, double *unused, double *out_7672649654478288824) {
  h_27(state, unused, out_7672649654478288824);
}
void car_H_27(double *state, double *unused, double *out_6153984156293061687) {
  H_27(state, unused, out_6153984156293061687);
}
void car_h_29(double *state, double *unused, double *out_811215868211163665) {
  h_29(state, unused, out_811215868211163665);
}
void car_H_29(double *state, double *unused, double *out_7867346883162612720) {
  H_29(state, unused, out_7867346883162612720);
}
void car_h_28(double *state, double *unused, double *out_5016109505237524836) {
  h_28(state, unused, out_5016109505237524836);
}
void car_H_28(double *state, double *unused, double *out_5496998173477408322) {
  H_28(state, unused, out_5496998173477408322);
}
void car_h_31(double *state, double *unused, double *out_5327175343426169421) {
  h_31(state, unused, out_5327175343426169421);
}
void car_H_31(double *state, double *unused, double *out_8217593318456804406) {
  H_31(state, unused, out_8217593318456804406);
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
