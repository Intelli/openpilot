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
void car_err_fun(double *nom_x, double *delta_x, double *out_5453433098127179484);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7256852226573224649);
void car_H_mod_fun(double *state, double *out_1133376989991124274);
void car_f_fun(double *state, double dt, double *out_6769417562591752525);
void car_F_fun(double *state, double dt, double *out_71820053026216018);
void car_h_25(double *state, double *unused, double *out_9068388865430187051);
void car_H_25(double *state, double *unused, double *out_2389603659998367403);
void car_h_24(double *state, double *unused, double *out_7302798642790729474);
void car_H_24(double *state, double *unused, double *out_5947529258800690539);
void car_h_30(double *state, double *unused, double *out_8911202197079057906);
void car_H_30(double *state, double *unused, double *out_4907936618505616030);
void car_h_26(double *state, double *unused, double *out_6722989773360640327);
void car_H_26(double *state, double *unused, double *out_1351899658875688821);
void car_h_27(double *state, double *unused, double *out_4106008867748893819);
void car_H_27(double *state, double *unused, double *out_7131530689689559247);
void car_h_29(double *state, double *unused, double *out_6306796876270360255);
void car_H_29(double *state, double *unused, double *out_5418167962820008214);
void car_h_28(double *state, double *unused, double *out_5088092961084191931);
void car_H_28(double *state, double *unused, double *out_335768945750477640);
void car_h_31(double *state, double *unused, double *out_1170858462196457715);
void car_H_31(double *state, double *unused, double *out_1978107761109040297);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}