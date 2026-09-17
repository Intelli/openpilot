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
void car_err_fun(double *nom_x, double *delta_x, double *out_8658023881255996922);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4511098242413357935);
void car_H_mod_fun(double *state, double *out_7419113753789213258);
void car_f_fun(double *state, double dt, double *out_6687108190872076920);
void car_F_fun(double *state, double dt, double *out_4340098819845909276);
void car_h_25(double *state, double *unused, double *out_2884651234761005866);
void car_H_25(double *state, double *unused, double *out_8723452863981184878);
void car_h_24(double *state, double *unused, double *out_5410236178001565575);
void car_H_24(double *state, double *unused, double *out_6497745080002316316);
void car_h_30(double *state, double *unused, double *out_3486069392374369420);
void car_H_30(double *state, double *unused, double *out_1806762522489568123);
void car_h_26(double *state, double *unused, double *out_4646686544616951732);
void car_H_26(double *state, double *unused, double *out_5981787890854310514);
void car_h_27(double *state, double *unused, double *out_2117022032899839779);
void car_H_27(double *state, double *unused, double *out_3981525834289993034);
void car_h_29(double *state, double *unused, double *out_8704849959376134942);
void car_H_29(double *state, double *unused, double *out_1296531178175175939);
void car_h_28(double *state, double *unused, double *out_2720337917576317296);
void car_H_28(double *state, double *unused, double *out_6378930195244706513);
void car_h_31(double *state, double *unused, double *out_6522100763015028216);
void car_H_31(double *state, double *unused, double *out_8692806902104224450);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}