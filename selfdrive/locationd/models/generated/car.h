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
void car_err_fun(double *nom_x, double *delta_x, double *out_888231951720114761);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5071969062086154653);
void car_H_mod_fun(double *state, double *out_275750450487295748);
void car_f_fun(double *state, double dt, double *out_8193553397271047053);
void car_F_fun(double *state, double dt, double *out_8498803796068946841);
void car_h_25(double *state, double *unused, double *out_333287890152809920);
void car_H_25(double *state, double *unused, double *out_6511660090495415162);
void car_h_24(double *state, double *unused, double *out_7670200299047341739);
void car_H_24(double *state, double *unused, double *out_7356656699279110561);
void car_h_30(double *state, double *unused, double *out_2235669891543854446);
void car_H_30(double *state, double *unused, double *out_5018393641722519699);
void car_h_26(double *state, double *unused, double *out_4915835473802170598);
void car_H_26(double *state, double *unused, double *out_7168514154605727066);
void car_h_27(double *state, double *unused, double *out_1514805784322995420);
void car_H_27(double *state, double *unused, double *out_7193156953522944610);
void car_h_29(double *state, double *unused, double *out_1789999846607501309);
void car_H_29(double *state, double *unused, double *out_4508162297408127515);
void car_h_28(double *state, double *unused, double *out_1089599536485702231);
void car_H_28(double *state, double *unused, double *out_8856182759231893527);
void car_h_31(double *state, double *unused, double *out_2036236090708967058);
void car_H_31(double *state, double *unused, double *out_6542306052372375590);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}