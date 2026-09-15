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
void car_err_fun(double *nom_x, double *delta_x, double *out_6220786048043098858);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8365457917697439847);
void car_H_mod_fun(double *state, double *out_7240996753969743287);
void car_f_fun(double *state, double dt, double *out_5407440773771914068);
void car_F_fun(double *state, double dt, double *out_1968632945652242383);
void car_h_25(double *state, double *unused, double *out_1914678424628455374);
void car_H_25(double *state, double *unused, double *out_8545335864161714907);
void car_h_24(double *state, double *unused, double *out_1769762204930244922);
void car_H_24(double *state, double *unused, double *out_160090505177928474);
void car_h_30(double *state, double *unused, double *out_8650792998327047057);
void car_H_30(double *state, double *unused, double *out_8674674811304954977);
void car_h_26(double *state, double *unused, double *out_3357616287989103000);
void car_H_26(double *state, double *unused, double *out_6159904890673780485);
void car_h_27(double *state, double *unused, double *out_7140585640463780321);
void car_H_27(double *state, double *unused, double *out_7597305950604171728);
void car_h_29(double *state, double *unused, double *out_5021036999341260248);
void car_H_29(double *state, double *unused, double *out_5883943223734620695);
void car_h_28(double *state, double *unused, double *out_7743901525140257838);
void car_H_28(double *state, double *unused, double *out_7847573495299946946);
void car_h_31(double *state, double *unused, double *out_1722771103625566976);
void car_H_31(double *state, double *unused, double *out_8514689902284754479);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}