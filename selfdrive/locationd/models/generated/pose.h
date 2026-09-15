#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8269927985032062752);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7882321665795113097);
void pose_H_mod_fun(double *state, double *out_2625199788015220353);
void pose_f_fun(double *state, double dt, double *out_2756784837860721128);
void pose_F_fun(double *state, double dt, double *out_7596404610561457994);
void pose_h_4(double *state, double *unused, double *out_5750154137532103835);
void pose_H_4(double *state, double *unused, double *out_3379360790069932960);
void pose_h_10(double *state, double *unused, double *out_679948980304854494);
void pose_H_10(double *state, double *unused, double *out_1607857339266867784);
void pose_h_13(double *state, double *unused, double *out_312393418504685067);
void pose_H_13(double *state, double *unused, double *out_6591634615402265761);
void pose_h_14(double *state, double *unused, double *out_5563868255163517085);
void pose_H_14(double *state, double *unused, double *out_7342601646409417489);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}