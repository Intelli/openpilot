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
void car_err_fun(double *nom_x, double *delta_x, double *out_435362218317324015);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8574647122111739157);
void car_H_mod_fun(double *state, double *out_8740515891481266957);
void car_f_fun(double *state, double dt, double *out_7569887734541362894);
void car_F_fun(double *state, double dt, double *out_8471352899330176325);
void car_h_25(double *state, double *unused, double *out_7212881291178297455);
void car_H_25(double *state, double *unused, double *out_1357001217961298052);
void car_h_24(double *state, double *unused, double *out_1711226362681868661);
void car_H_24(double *state, double *unused, double *out_2625321933436469846);
void car_h_30(double *state, double *unused, double *out_6739311054597629248);
void car_H_30(double *state, double *unused, double *out_8273691559452914807);
void car_h_26(double *state, double *unused, double *out_7342626939274106765);
void car_H_26(double *state, double *unused, double *out_4661527187722098653);
void car_h_27(double *state, double *unused, double *out_4176095239733964770);
void car_H_27(double *state, double *unused, double *out_6098928247652489896);
void car_h_29(double *state, double *unused, double *out_7682820907499291683);
void car_H_29(double *state, double *unused, double *out_8783922903767306991);
void car_h_28(double *state, double *unused, double *out_2826667464059101009);
void car_H_28(double *state, double *unused, double *out_3701523886697776417);
void car_h_31(double *state, double *unused, double *out_4463027556180903225);
void car_H_31(double *state, double *unused, double *out_1387647179838258480);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}