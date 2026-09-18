#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3942668725891730719);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1991070876907521357);
void pose_H_mod_fun(double *state, double *out_6816734002753500757);
void pose_f_fun(double *state, double dt, double *out_8854473194143657966);
void pose_F_fun(double *state, double dt, double *out_4169004597503113381);
void pose_h_4(double *state, double *unused, double *out_8446778466240330255);
void pose_H_4(double *state, double *unused, double *out_3044926792909593185);
void pose_h_10(double *state, double *unused, double *out_7710800854864143014);
void pose_H_10(double *state, double *unused, double *out_4471861486161314633);
void pose_h_13(double *state, double *unused, double *out_7052128610875229889);
void pose_H_13(double *state, double *unused, double *out_4565704415407107744);
void pose_h_14(double *state, double *unused, double *out_6863744574475710969);
void pose_H_14(double *state, double *unused, double *out_6127715225204965481);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}