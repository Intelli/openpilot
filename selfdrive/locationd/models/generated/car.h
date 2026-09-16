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
void car_err_fun(double *nom_x, double *delta_x, double *out_7895276982844131476);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8311988311363521241);
void car_H_mod_fun(double *state, double *out_6889381883510717831);
void car_f_fun(double *state, double dt, double *out_8017553581414772762);
void car_F_fun(double *state, double dt, double *out_8543421153524097422);
void car_h_25(double *state, double *unused, double *out_3233264926632776173);
void car_H_25(double *state, double *unused, double *out_6653670365014168945);
void car_h_24(double *state, double *unused, double *out_5475294472382821453);
void car_H_24(double *state, double *unused, double *out_4965853929145064754);
void car_h_30(double *state, double *unused, double *out_7332206496322726258);
void car_H_30(double *state, double *unused, double *out_7265377378567774473);
void car_h_26(double *state, double *unused, double *out_5512084423523194380);
void car_H_26(double *state, double *unused, double *out_8051570389821326447);
void car_h_27(double *state, double *unused, double *out_1729115071048517059);
void car_H_27(double *state, double *unused, double *out_8957772623957833926);
void car_h_29(double *state, double *unused, double *out_8954363745840362116);
void car_H_29(double *state, double *unused, double *out_7775608722882166657);
void car_h_28(double *state, double *unused, double *out_3419562905784198019);
void car_H_28(double *state, double *unused, double *out_8707505079262058708);
void car_h_31(double *state, double *unused, double *out_5280156946080479537);
void car_H_31(double *state, double *unused, double *out_6623024403137208517);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}