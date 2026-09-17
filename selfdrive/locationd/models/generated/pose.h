#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3324107228628984672);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4562048945435600381);
void pose_H_mod_fun(double *state, double *out_3635685799188405881);
void pose_f_fun(double *state, double dt, double *out_223023666217574094);
void pose_F_fun(double *state, double dt, double *out_6563490807838139396);
void pose_h_4(double *state, double *unused, double *out_2709224699571416582);
void pose_H_4(double *state, double *unused, double *out_2881524797133693274);
void pose_h_10(double *state, double *unused, double *out_528563670856782628);
void pose_H_10(double *state, double *unused, double *out_3212086573286679008);
void pose_h_13(double *state, double *unused, double *out_5134071672757776268);
void pose_H_13(double *state, double *unused, double *out_4729106411183007655);
void pose_h_14(double *state, double *unused, double *out_7319951522008375092);
void pose_H_14(double *state, double *unused, double *out_1081716059205791255);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}