#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5133309144223277572);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6881212781704972929);
void pose_H_mod_fun(double *state, double *out_6869028127987583637);
void pose_f_fun(double *state, double dt, double *out_8902612319160798640);
void pose_F_fun(double *state, double dt, double *out_1483402946734561261);
void pose_h_4(double *state, double *unused, double *out_7341531725789403251);
void pose_H_4(double *state, double *unused, double *out_8688726853893880498);
void pose_h_10(double *state, double *unused, double *out_7465669924192065255);
void pose_H_10(double *state, double *unused, double *out_3170804055885360208);
void pose_h_13(double *state, double *unused, double *out_1303405934408792496);
void pose_H_13(double *state, double *unused, double *out_5476453028561547697);
void pose_h_14(double *state, double *unused, double *out_8059879594466194155);
void pose_H_14(double *state, double *unused, double *out_6675228787520298822);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}