#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8350573898937785017);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5918399502432517462);
void pose_H_mod_fun(double *state, double *out_5408019346738954690);
void pose_f_fun(double *state, double dt, double *out_3102010915359179201);
void pose_F_fun(double *state, double dt, double *out_5989389069242696689);
void pose_h_4(double *state, double *unused, double *out_7406421415907820239);
void pose_H_4(double *state, double *unused, double *out_6162180348793667297);
void pose_h_10(double *state, double *unused, double *out_3211171476200369044);
void pose_H_10(double *state, double *unused, double *out_281169815792164733);
void pose_h_13(double *state, double *unused, double *out_573980117357148738);
void pose_H_13(double *state, double *unused, double *out_9072289899583551518);
void pose_h_14(double *state, double *unused, double *out_662186785725404223);
void pose_H_14(double *state, double *unused, double *out_8321322868576399790);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}