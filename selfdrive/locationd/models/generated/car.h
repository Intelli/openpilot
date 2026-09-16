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
void car_err_fun(double *nom_x, double *delta_x, double *out_8618165811213795631);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_476504129112473836);
void car_H_mod_fun(double *state, double *out_7392752302911939325);
void car_f_fun(double *state, double dt, double *out_9221484452100360325);
void car_F_fun(double *state, double dt, double *out_9146847634012448063);
void car_h_25(double *state, double *unused, double *out_3254080677535242918);
void car_H_25(double *state, double *unused, double *out_1860803544885375054);
void car_h_24(double *state, double *unused, double *out_1285601474070799560);
void car_H_24(double *state, double *unused, double *out_7357875342754981337);
void car_h_30(double *state, double *unused, double *out_3855498835148606472);
void car_H_30(double *state, double *unused, double *out_1731464597742134984);
void car_h_26(double *state, double *unused, double *out_8857172102809452117);
void car_H_26(double *state, double *unused, double *out_1880699773988681170);
void car_h_27(double *state, double *unused, double *out_1368105351920865396);
void car_H_27(double *state, double *unused, double *out_443298714058289927);
void car_h_29(double *state, double *unused, double *out_9025144054500435279);
void car_H_29(double *state, double *unused, double *out_2156661440927840960);
void car_h_28(double *state, double *unused, double *out_6369778619581711041);
void car_H_28(double *state, double *unused, double *out_7239060457997371534);
void car_h_31(double *state, double *unused, double *out_4509184579285429523);
void car_H_31(double *state, double *unused, double *out_1891449506762335482);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}