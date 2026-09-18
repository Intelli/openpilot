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
void car_err_fun(double *nom_x, double *delta_x, double *out_7334514324452905535);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8019483554295330227);
void car_H_mod_fun(double *state, double *out_6421531401304893150);
void car_f_fun(double *state, double dt, double *out_4838091094809053617);
void car_F_fun(double *state, double dt, double *out_5099404173866157435);
void car_h_25(double *state, double *unused, double *out_7774922300368905181);
void car_H_25(double *state, double *unused, double *out_5472410479276410941);
void car_h_24(double *state, double *unused, double *out_3616053314518146228);
void car_H_24(double *state, double *unused, double *out_1914484880474087805);
void car_h_30(double *state, double *unused, double *out_8050116362653411070);
void car_H_30(double *state, double *unused, double *out_8446637264305532477);
void car_h_26(double *state, double *unused, double *out_3048443094992565425);
void car_H_26(double *state, double *unused, double *out_9213913798150467165);
void car_h_27(double *state, double *unused, double *out_772159596575839402);
void car_H_27(double *state, double *unused, double *out_6271873952505107566);
void car_h_29(double *state, double *unused, double *out_4633843073004341054);
void car_H_29(double *state, double *unused, double *out_8956868608619924661);
void car_h_28(double *state, double *unused, double *out_171350256325823033);
void car_H_28(double *state, double *unused, double *out_3874469591550394087);
void car_h_31(double *state, double *unused, double *out_2778882278456123076);
void car_H_31(double *state, double *unused, double *out_8606622173325732975);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}