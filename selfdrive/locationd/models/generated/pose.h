#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1877090198031843098);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4765871387657118050);
void pose_H_mod_fun(double *state, double *out_3424858624905544886);
void pose_f_fun(double *state, double dt, double *out_6956505280641818693);
void pose_F_fun(double *state, double dt, double *out_4753955652213576676);
void pose_h_4(double *state, double *unused, double *out_5605636478763056645);
void pose_H_4(double *state, double *unused, double *out_4179019626960257493);
void pose_h_10(double *state, double *unused, double *out_3279884597631109591);
void pose_H_10(double *state, double *unused, double *out_3190556599962023573);
void pose_h_13(double *state, double *unused, double *out_230694173360480530);
void pose_H_13(double *state, double *unused, double *out_6657093238432593194);
void pose_h_14(double *state, double *unused, double *out_1120624520725849136);
void pose_H_14(double *state, double *unused, double *out_8142260483299742022);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}