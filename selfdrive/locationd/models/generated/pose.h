#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1521868972628687519);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5973741488758985839);
void pose_H_mod_fun(double *state, double *out_3570248239535224383);
void pose_f_fun(double *state, double dt, double *out_4424152333430403489);
void pose_F_fun(double *state, double dt, double *out_6803176853977790057);
void pose_h_4(double *state, double *unused, double *out_3836272604617207310);
void pose_H_4(double *state, double *unused, double *out_8086112231463728530);
void pose_h_10(double *state, double *unused, double *out_5399605113307306233);
void pose_H_10(double *state, double *unused, double *out_7292319071417432326);
void pose_h_13(double *state, double *unused, double *out_7661639451849470604);
void pose_H_13(double *state, double *unused, double *out_475481023147027601);
void pose_h_14(double *state, double *unused, double *out_8890668722298524322);
void pose_H_14(double *state, double *unused, double *out_4122871375124244001);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}