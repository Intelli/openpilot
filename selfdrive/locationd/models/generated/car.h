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
void car_err_fun(double *nom_x, double *delta_x, double *out_2868059773781515085);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_914043083376862951);
void car_H_mod_fun(double *state, double *out_1520386229881842552);
void car_f_fun(double *state, double dt, double *out_6740959738038231183);
void car_F_fun(double *state, double dt, double *out_3261921498188250037);
void car_h_25(double *state, double *unused, double *out_6799552646789288449);
void car_H_25(double *state, double *unused, double *out_571265307853360343);
void car_h_24(double *state, double *unused, double *out_1135785712041919118);
void car_H_24(double *state, double *unused, double *out_8656799878215834882);
void car_h_30(double *state, double *unused, double *out_4443975469934277197);
void car_H_30(double *state, double *unused, double *out_5098961637980968541);
void car_h_26(double *state, double *unused, double *out_7064643843270902489);
void car_H_26(double *state, double *unused, double *out_4312768626727416567);
void car_h_27(double *state, double *unused, double *out_1156822775708331614);
void car_H_27(double *state, double *unused, double *out_2875367566797025324);
void car_h_29(double *state, double *unused, double *out_2334553285684309280);
void car_H_29(double *state, double *unused, double *out_4588730293666576357);
void car_h_28(double *state, double *unused, double *out_2391925919692030476);
void car_H_28(double *state, double *unused, double *out_8775614762973444685);
void car_h_31(double *state, double *unused, double *out_7074746709073794338);
void car_H_31(double *state, double *unused, double *out_540619345976399915);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}