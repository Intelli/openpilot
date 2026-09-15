#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8005578165904155046);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5771596986871161922);
void pose_H_mod_fun(double *state, double *out_3288040166935413696);
void pose_f_fun(double *state, double dt, double *out_8548830741413868974);
void pose_F_fun(double *state, double dt, double *out_1843100742578169461);
void pose_h_4(double *state, double *unused, double *out_623102779938789677);
void pose_H_4(double *state, double *unused, double *out_4912264717037811071);
void pose_h_10(double *state, double *unused, double *out_1249595436022458194);
void pose_H_10(double *state, double *unused, double *out_2080664605204891446);
void pose_h_13(double *state, double *unused, double *out_67533375617629937);
void pose_H_13(double *state, double *unused, double *out_5923848148355039616);
void pose_h_14(double *state, double *unused, double *out_2407873033235342181);
void pose_H_14(double *state, double *unused, double *out_8875505573377295600);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}