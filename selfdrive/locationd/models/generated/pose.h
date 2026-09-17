#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3246138991131647202);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4007822862672909290);
void pose_H_mod_fun(double *state, double *out_8044174148668571060);
void pose_f_fun(double *state, double dt, double *out_509214913504947314);
void pose_F_fun(double *state, double dt, double *out_4927192891870145475);
void pose_h_4(double *state, double *unused, double *out_694167901848750082);
void pose_H_4(double *state, double *unused, double *out_7290013146613858453);
void pose_h_10(double *state, double *unused, double *out_5760027499613918255);
void pose_H_10(double *state, double *unused, double *out_5891931083183346428);
void pose_h_13(double *state, double *unused, double *out_9070928996461222622);
void pose_H_13(double *state, double *unused, double *out_7322975463793169139);
void pose_h_14(double *state, double *unused, double *out_297879652021367590);
void pose_H_14(double *state, double *unused, double *out_8073942494800320867);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}