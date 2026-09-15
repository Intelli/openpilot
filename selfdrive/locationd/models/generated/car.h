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
void car_err_fun(double *nom_x, double *delta_x, double *out_2989898474462123217);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7725514447092014153);
void car_H_mod_fun(double *state, double *out_779695979657555196);
void car_f_fun(double *state, double dt, double *out_3948637387392336290);
void car_F_fun(double *state, double dt, double *out_6167405682750118523);
void car_h_25(double *state, double *unused, double *out_2762237331341649667);
void car_H_25(double *state, double *unused, double *out_7015605619665674610);
void car_h_24(double *state, double *unused, double *out_1423861544418694677);
void car_H_24(double *state, double *unused, double *out_814572939814513184);
void car_h_30(double *state, double *unused, double *out_3393209864499010462);
void car_H_30(double *state, double *unused, double *out_4514448112552260251);
void car_h_26(double *state, double *unused, double *out_8735077100385041025);
void car_H_26(double *state, double *unused, double *out_3274102300791618386);
void car_h_27(double *state, double *unused, double *out_513610481405806922);
void car_H_27(double *state, double *unused, double *out_4711503360722009629);
void car_h_29(double *state, double *unused, double *out_8394883132159856107);
void car_H_29(double *state, double *unused, double *out_7396498016836826724);
void car_h_28(double *state, double *unused, double *out_5515283749066652567);
void car_H_28(double *state, double *unused, double *out_9086615785307398641);
void car_h_31(double *state, double *unused, double *out_3037431393626155556);
void car_H_31(double *state, double *unused, double *out_7046251581542635038);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}