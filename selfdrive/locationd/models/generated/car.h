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
void car_err_fun(double *nom_x, double *delta_x, double *out_3116950613086029289);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8816218489066620773);
void car_H_mod_fun(double *state, double *out_4584714039641352360);
void car_f_fun(double *state, double dt, double *out_7251150553106896463);
void car_F_fun(double *state, double dt, double *out_2775352329421248203);
void car_h_25(double *state, double *unused, double *out_8133229711243772136);
void car_H_25(double *state, double *unused, double *out_4608474186270884877);
void car_h_24(double *state, double *unused, double *out_2915127492452882109);
void car_H_24(double *state, double *unused, double *out_2045731271837300880);
void car_h_30(double *state, double *unused, double *out_2852955598216891155);
void car_H_30(double *state, double *unused, double *out_9136170516398493075);
void car_h_26(double *state, double *unused, double *out_9108780320175938409);
void car_H_26(double *state, double *unused, double *out_8349977505144941101);
void car_h_27(double *state, double *unused, double *out_2907322495408447189);
void car_H_27(double *state, double *unused, double *out_6912576445214549858);
void car_h_29(double *state, double *unused, double *out_7854628865877736800);
void car_H_29(double *state, double *unused, double *out_8625939172084100891);
void car_h_28(double *state, double *unused, double *out_5511727816217144840);
void car_H_28(double *state, double *unused, double *out_6662308900518774640);
void car_h_31(double *state, double *unused, double *out_6676064834211757130);
void car_H_31(double *state, double *unused, double *out_4577828224393924449);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}