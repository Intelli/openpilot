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
void car_err_fun(double *nom_x, double *delta_x, double *out_5677531195299710099);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3240212805769737864);
void car_H_mod_fun(double *state, double *out_201453769190803420);
void car_f_fun(double *state, double dt, double *out_8096296852446877645);
void car_F_fun(double *state, double dt, double *out_3086345955946777782);
void car_h_25(double *state, double *unused, double *out_5322718312140181517);
void car_H_25(double *state, double *unused, double *out_1102885341001168200);
void car_h_24(double *state, double *unused, double *out_5561456258811847026);
void car_H_24(double *state, double *unused, double *out_7282360017982618233);
void car_h_30(double *state, double *unused, double *out_3173942369123558475);
void car_H_30(double *state, double *unused, double *out_5813805000490448555);
void car_h_26(double *state, double *unused, double *out_6449790181871015064);
void car_H_26(double *state, double *unused, double *out_4844388659875224424);
void car_h_27(double *state, double *unused, double *out_4379208459238519082);
void car_H_27(double *state, double *unused, double *out_3639041688690023644);
void car_h_29(double *state, double *unused, double *out_8016657987492541432);
void car_H_29(double *state, double *unused, double *out_1925678961820472611);
void car_h_28(double *state, double *unused, double *out_738701221414969764);
void car_H_28(double *state, double *unused, double *out_3156720055249057963);
void car_h_31(double *state, double *unused, double *out_897658870706832452);
void car_H_31(double *state, double *unused, double *out_1072239379124207772);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}