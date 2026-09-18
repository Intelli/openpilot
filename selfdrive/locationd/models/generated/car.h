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
void car_err_fun(double *nom_x, double *delta_x, double *out_8674505523865043261);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6250570191206249369);
void car_H_mod_fun(double *state, double *out_742618674605284176);
void car_f_fun(double *state, double dt, double *out_8095007039495488980);
void car_F_fun(double *state, double dt, double *out_7050818561186322839);
void car_h_25(double *state, double *unused, double *out_4702846008704956131);
void car_H_25(double *state, double *unused, double *out_23829087476923073);
void car_h_24(double *state, double *unused, double *out_910324667090234605);
void car_H_24(double *state, double *unused, double *out_6224861767328084499);
void car_h_30(double *state, double *unused, double *out_823211427846066982);
void car_H_30(double *state, double *unused, double *out_4551525417604531271);
void car_h_26(double *state, double *unused, double *out_6668487905725142980);
void car_H_26(double *state, double *unused, double *out_3765332406350979297);
void car_h_27(double *state, double *unused, double *out_3343218477695586303);
void car_H_27(double *state, double *unused, double *out_6726288729404956182);
void car_h_29(double *state, double *unused, double *out_7222252945259916128);
void car_H_29(double *state, double *unused, double *out_4041294073290139087);
void car_h_28(double *state, double *unused, double *out_2399708624793923868);
void car_H_28(double *state, double *unused, double *out_9123693090359669661);
void car_h_31(double *state, double *unused, double *out_6104810466855413099);
void car_H_31(double *state, double *unused, double *out_4391540508584330773);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}