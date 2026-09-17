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
void car_err_fun(double *nom_x, double *delta_x, double *out_4505651181940075839);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1646596662830797608);
void car_H_mod_fun(double *state, double *out_5501956759725950600);
void car_f_fun(double *state, double dt, double *out_4174408190255373619);
void car_F_fun(double *state, double dt, double *out_584677443248040024);
void car_h_25(double *state, double *unused, double *out_1009943400890808144);
void car_H_25(double *state, double *unused, double *out_1978976109736458923);
void car_h_24(double *state, double *unused, double *out_390532478353196657);
void car_H_24(double *state, double *unused, double *out_1578949489065864213);
void car_h_30(double *state, double *unused, double *out_7597771327367103307);
void car_H_30(double *state, double *unused, double *out_4937714231755157832);
void car_h_26(double *state, double *unused, double *out_4449931228928599163);
void car_H_26(double *state, double *unused, double *out_5720479428610515147);
void car_h_27(double *state, double *unused, double *out_1178344241810182114);
void car_H_27(double *state, double *unused, double *out_4283078368680123904);
void car_h_29(double *state, double *unused, double *out_2131135826473755983);
void car_H_29(double *state, double *unused, double *out_1598083712565306809);
void car_h_28(double *state, double *unused, double *out_6936329155803920070);
void car_H_28(double *state, double *unused, double *out_4032810823984348686);
void car_h_31(double *state, double *unused, double *out_2828025537148972505);
void car_H_31(double *state, double *unused, double *out_1948330147859498495);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}