#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_3898235742640831677);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3493896062924369044);
void car_H_mod_fun(double *state, double *out_6155968468887758897);
void car_f_fun(double *state, double dt, double *out_5924652974824119647);
void car_F_fun(double *state, double dt, double *out_7778196774452902734);
void car_h_25(double *state, double *unused, double *out_5529134141476677677);
void car_H_25(double *state, double *unused, double *out_1252276643703094057);
void car_h_24(double *state, double *unused, double *out_8362506630194486028);
void car_H_24(double *state, double *unused, double *out_1722734125746432781);
void car_h_30(double *state, double *unused, double *out_637979898494456626);
void car_H_30(double *state, double *unused, double *out_5779972973830702255);
void car_h_26(double *state, double *unused, double *out_5639653166155302271);
void car_H_26(double *state, double *unused, double *out_4993779962577150281);
void car_h_27(double *state, double *unused, double *out_6671158874772700471);
void car_H_27(double *state, double *unused, double *out_3556378902646759038);
void car_h_29(double *state, double *unused, double *out_4278487136318005944);
void car_H_29(double *state, double *unused, double *out_5269741629516310071);
void car_h_28(double *state, double *unused, double *out_1548838237130682557);
void car_H_28(double *state, double *unused, double *out_3306111357950983820);
void car_h_31(double *state, double *unused, double *out_114930689007722180);
void car_H_31(double *state, double *unused, double *out_1221630681826133629);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}