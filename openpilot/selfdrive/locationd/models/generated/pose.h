#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1826050002567019116);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4637537663232425696);
void pose_H_mod_fun(double *state, double *out_5823096309702897011);
void pose_f_fun(double *state, double dt, double *out_4447474560046678856);
void pose_F_fun(double *state, double dt, double *out_1876724253576652183);
void pose_h_4(double *state, double *unused, double *out_5870638379975225029);
void pose_H_4(double *state, double *unused, double *out_3121265356354924331);
void pose_h_10(double *state, double *unused, double *out_8351966239607778150);
void pose_H_10(double *state, double *unused, double *out_5853760429658336434);
void pose_h_13(double *state, double *unused, double *out_1331349399792691795);
void pose_H_13(double *state, double *unused, double *out_6955020819657448355);
void pose_h_14(double *state, double *unused, double *out_1044143545257583313);
void pose_H_14(double *state, double *unused, double *out_6204053788650296627);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}