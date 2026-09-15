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
void car_err_fun(double *nom_x, double *delta_x, double *out_1227793143144495277);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_377220753251568338);
void car_H_mod_fun(double *state, double *out_4965179062603390678);
void car_f_fun(double *state, double dt, double *out_5021644498978266308);
void car_F_fun(double *state, double dt, double *out_4137309702793038373);
void car_h_25(double *state, double *unused, double *out_5010515879516742558);
void car_H_25(double *state, double *unused, double *out_61487237418725838);
void car_h_24(double *state, double *unused, double *out_2332165883187586177);
void car_H_24(double *state, double *unused, double *out_6262519917269887264);
void car_h_30(double *state, double *unused, double *out_7792163363708409201);
void car_H_30(double *state, double *unused, double *out_6855203104072890917);
void car_h_26(double *state, double *unused, double *out_1393121846294560055);
void car_H_26(double *state, double *unused, double *out_3802990556292782062);
void car_h_27(double *state, double *unused, double *out_2424627554911958255);
void car_H_27(double *state, double *unused, double *out_4680439792272466006);
void car_h_29(double *state, double *unused, double *out_2149433492627452366);
void car_H_29(double *state, double *unused, double *out_2967077065402914973);
void car_h_28(double *state, double *unused, double *out_4009194011233731880);
void car_H_28(double *state, double *unused, double *out_2115321951666615601);
void car_h_31(double *state, double *unused, double *out_1070359858690936092);
void car_H_31(double *state, double *unused, double *out_30841275541765410);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}