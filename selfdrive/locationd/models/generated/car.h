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
void car_err_fun(double *nom_x, double *delta_x, double *out_4724135031167294247);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2223837273842813027);
void car_H_mod_fun(double *state, double *out_1736865348108088772);
void car_f_fun(double *state, double dt, double *out_7457021128043083908);
void car_F_fun(double *state, double dt, double *out_1755097740802618951);
void car_h_25(double *state, double *unused, double *out_6272135937118882243);
void car_H_25(double *state, double *unused, double *out_861556603769085792);
void car_h_24(double *state, double *unused, double *out_2155945064809607249);
void car_H_24(double *state, double *unused, double *out_2696368995033237344);
void car_h_30(double *state, double *unused, double *out_6547329999403388132);
void car_H_30(double *state, double *unused, double *out_1656776354738162835);
void car_h_26(double *state, double *unused, double *out_1545656731742542487);
void car_H_26(double *state, double *unused, double *out_2442969365991714809);
void car_h_27(double *state, double *unused, double *out_4581688102383201283);
void car_H_27(double *state, double *unused, double *out_517986957062262076);
void car_h_29(double *state, double *unused, double *out_6256684203225206649);
void car_H_29(double *state, double *unused, double *out_2167007699052555019);
void car_h_28(double *state, double *unused, double *out_1674136619575845971);
void car_H_28(double *state, double *unused, double *out_2915391318016975555);
void car_h_31(double *state, double *unused, double *out_4281668641706146014);
void car_H_31(double *state, double *unused, double *out_1816761263758363333);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}