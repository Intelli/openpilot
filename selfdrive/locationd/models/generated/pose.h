#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5972218924990510792);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2514414057014520529);
void pose_H_mod_fun(double *state, double *out_4028083170396016980);
void pose_f_fun(double *state, double dt, double *out_5391513649361153377);
void pose_F_fun(double *state, double dt, double *out_3183755745481268939);
void pose_h_4(double *state, double *unused, double *out_4392711394053593010);
void pose_H_4(double *state, double *unused, double *out_6484436289412890429);
void pose_h_10(double *state, double *unused, double *out_8376071089077647070);
void pose_H_10(double *state, double *unused, double *out_7681394100323810490);
void pose_h_13(double *state, double *unused, double *out_3671495376644037122);
void pose_H_13(double *state, double *unused, double *out_8750033958964328386);
void pose_h_14(double *state, double *unused, double *out_2407733700991607130);
void pose_H_14(double *state, double *unused, double *out_7999066927957176658);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}