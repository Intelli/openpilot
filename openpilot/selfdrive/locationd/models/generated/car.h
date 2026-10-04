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
void car_err_fun(double *nom_x, double *delta_x, double *out_8828323615526015434);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3498370127488248858);
void car_H_mod_fun(double *state, double *out_6401776151128821180);
void car_f_fun(double *state, double dt, double *out_146901637752652717);
void car_F_fun(double *state, double dt, double *out_5522538997423658876);
void car_h_25(double *state, double *unused, double *out_8923785172993752075);
void car_H_25(double *state, double *unused, double *out_7141276097396065596);
void car_h_24(double *state, double *unused, double *out_3929820800215180434);
void car_H_24(double *state, double *unused, double *out_4964061673788915623);
void car_h_30(double *state, double *unused, double *out_1238992460570384448);
void car_H_30(double *state, double *unused, double *out_4622943138888816969);
void car_h_26(double *state, double *unused, double *out_2406736261646526185);
void car_H_26(double *state, double *unused, double *out_7563964657439429796);
void car_h_27(double *state, double *unused, double *out_6319379852185054424);
void car_H_27(double *state, double *unused, double *out_6797706450689241880);
void car_h_29(double *state, double *unused, double *out_1573559642699468935);
void car_H_29(double *state, double *unused, double *out_4112711794574424785);
void car_h_28(double *state, double *unused, double *out_3282593800740721739);
void car_H_28(double *state, double *unused, double *out_9195110811643955359);
void car_h_31(double *state, double *unused, double *out_5062101696565250423);
void car_H_31(double *state, double *unused, double *out_6937756555206078320);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}