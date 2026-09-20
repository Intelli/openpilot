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
void car_err_fun(double *nom_x, double *delta_x, double *out_16839997209750613);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_997850346281991640);
void car_H_mod_fun(double *state, double *out_793862516828139793);
void car_f_fun(double *state, double dt, double *out_7985598016111714437);
void car_F_fun(double *state, double dt, double *out_2618723996397977550);
void car_h_25(double *state, double *unused, double *out_2300452709025625959);
void car_H_25(double *state, double *unused, double *out_288528074627843081);
void car_h_24(double *state, double *unused, double *out_6637232346528830745);
void car_H_24(double *state, double *unused, double *out_556468534155852318);
void car_h_30(double *state, double *unused, double *out_6162136185454127611);
void car_H_30(double *state, double *unused, double *out_6628162266863773674);
void car_h_26(double *state, double *unused, double *out_3302638716248583240);
void car_H_26(double *state, double *unused, double *out_4030031393501899305);
void car_h_27(double *state, double *unused, double *out_7125747952243449215);
void car_H_27(double *state, double *unused, double *out_4453398955063348763);
void car_h_29(double *state, double *unused, double *out_7282934620594578360);
void car_H_29(double *state, double *unused, double *out_7138393611178165858);
void car_h_28(double *state, double *unused, double *out_8284210070021769716);
void car_H_28(double *state, double *unused, double *out_2055994594108635284);
void car_h_31(double *state, double *unused, double *out_268505072671038407);
void car_H_31(double *state, double *unused, double *out_257882112750882653);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}