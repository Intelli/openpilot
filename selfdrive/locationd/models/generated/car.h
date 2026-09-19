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
void car_err_fun(double *nom_x, double *delta_x, double *out_4114648249213916133);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6190245242351307834);
void car_H_mod_fun(double *state, double *out_3909618768201251108);
void car_f_fun(double *state, double dt, double *out_3571540485824102989);
void car_F_fun(double *state, double dt, double *out_6621900683454123459);
void car_h_25(double *state, double *unused, double *out_4179257190693495917);
void car_H_25(double *state, double *unused, double *out_6985761574673146971);
void car_h_24(double *state, double *unused, double *out_3563018922388527814);
void car_H_24(double *state, double *unused, double *out_7456219056716485695);
void car_h_30(double *state, double *unused, double *out_7496651656665704763);
void car_H_30(double *state, double *unused, double *out_7115100521816387041);
void car_h_26(double *state, double *unused, double *out_3947329713250781074);
void car_H_26(double *state, double *unused, double *out_7719479180162348421);
void car_h_27(double *state, double *unused, double *out_5122767043595158352);
void car_H_27(double *state, double *unused, double *out_9156880240092739664);
void car_h_29(double *state, double *unused, double *out_4459865605221372078);
void car_H_29(double *state, double *unused, double *out_6604869177501994857);
void car_h_28(double *state, double *unused, double *out_8159553095039491037);
void car_H_28(double *state, double *unused, double *out_6759475879138026185);
void car_h_31(double *state, double *unused, double *out_3584008066127176524);
void car_H_31(double *state, double *unused, double *out_6955115612796186543);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}