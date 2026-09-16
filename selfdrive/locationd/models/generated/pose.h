#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1903961773272735640);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_573088353517031631);
void pose_H_mod_fun(double *state, double *out_8399228583696910237);
void pose_f_fun(double *state, double dt, double *out_7642272888362122250);
void pose_F_fun(double *state, double dt, double *out_2644346224160988756);
void pose_h_4(double *state, double *unused, double *out_866291291104227919);
void pose_H_4(double *state, double *unused, double *out_1103153823954820037);
void pose_h_10(double *state, double *unused, double *out_5833399118122366963);
void pose_H_10(double *state, double *unused, double *out_6949267687029300227);
void pose_h_13(double *state, double *unused, double *out_255680044725993896);
void pose_H_13(double *state, double *unused, double *out_4315427649287152838);
void pose_h_14(double *state, double *unused, double *out_18401598981597761);
void pose_H_14(double *state, double *unused, double *out_1979634608340552259);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}