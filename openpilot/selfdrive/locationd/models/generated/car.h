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
void car_err_fun(double *nom_x, double *delta_x, double *out_1348800808687792387);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1749907634917603761);
void car_H_mod_fun(double *state, double *out_4411937711281551923);
void car_f_fun(double *state, double dt, double *out_6965050437253804893);
void car_F_fun(double *state, double dt, double *out_161323463410755275);
void car_h_25(double *state, double *unused, double *out_6578686103484159860);
void car_H_25(double *state, double *unused, double *out_7934918361271043600);
void car_h_24(double *state, double *unused, double *out_1714890755541721598);
void car_H_24(double *state, double *unused, double *out_3936253905846989915);
void car_h_30(double *state, double *unused, double *out_2975148859307398715);
void car_H_30(double *state, double *unused, double *out_3595135370946891261);
void car_h_26(double *state, double *unused, double *out_61637192136933970);
void car_H_26(double *state, double *unused, double *out_4193415042396987376);
void car_h_27(double *state, double *unused, double *out_3974280782675462209);
void car_H_27(double *state, double *unused, double *out_5630816102327378619);
void car_h_29(double *state, double *unused, double *out_8317016095193429278);
void car_H_29(double *state, double *unused, double *out_8315810758442195714);
void car_h_28(double *state, double *unused, double *out_7250128595422918798);
void car_H_28(double *state, double *unused, double *out_5881083647023153837);
void car_h_31(double *state, double *unused, double *out_1302586547269889325);
void car_H_31(double *state, double *unused, double *out_7965564323148004028);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}