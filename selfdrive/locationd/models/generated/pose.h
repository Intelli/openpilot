#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3128060725060609626);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_962437773882614248);
void pose_H_mod_fun(double *state, double *out_1378391307355774028);
void pose_f_fun(double *state, double dt, double *out_7600705386146157547);
void pose_F_fun(double *state, double dt, double *out_5012584798577878241);
void pose_h_4(double *state, double *unused, double *out_3012774128462283816);
void pose_H_4(double *state, double *unused, double *out_8868047882380552821);
void pose_h_10(double *state, double *unused, double *out_5195823745099030305);
void pose_H_10(double *state, double *unused, double *out_6876873563119817203);
void pose_h_13(double *state, double *unused, double *out_5988520755265918560);
void pose_H_13(double *state, double *unused, double *out_1257416674063851892);
void pose_h_14(double *state, double *unused, double *out_5205424874227035559);
void pose_H_14(double *state, double *unused, double *out_4904807026041068292);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}