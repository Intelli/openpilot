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
void car_err_fun(double *nom_x, double *delta_x, double *out_2875077231426279529);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7764517582708413116);
void car_H_mod_fun(double *state, double *out_1362034626282984391);
void car_f_fun(double *state, double dt, double *out_4861076963360172947);
void car_F_fun(double *state, double dt, double *out_344082542095483460);
void car_h_25(double *state, double *unused, double *out_6349540795286409135);
void car_H_25(double *state, double *unused, double *out_6265726451467649231);
void car_h_24(double *state, double *unused, double *out_2089055603068722673);
void car_H_24(double *state, double *unused, double *out_7953542887336753422);
void car_h_30(double *state, double *unused, double *out_6192354126935279990);
void car_H_30(double *state, double *unused, double *out_8784059409974897858);
void car_h_26(double *state, double *unused, double *out_1190680859274434345);
void car_H_26(double *state, double *unused, double *out_2524223132593593007);
void car_h_27(double *state, double *unused, double *out_7174002555159601650);
void car_H_27(double *state, double *unused, double *out_7439090592550710541);
void car_h_29(double *state, double *unused, double *out_4501906292199599030);
void car_H_29(double *state, double *unused, double *out_9152453319420261574);
void car_h_28(double *state, double *unused, double *out_5016916796590902712);
void car_H_28(double *state, double *unused, double *out_4211891737219759468);
void car_h_31(double *state, double *unused, double *out_4412410565999774854);
void car_H_31(double *state, double *unused, double *out_6296372413344609659);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}