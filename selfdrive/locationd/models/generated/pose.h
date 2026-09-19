#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3009149682027724813);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6241253285121461636);
void pose_H_mod_fun(double *state, double *out_3247087395785811549);
void pose_f_fun(double *state, double dt, double *out_8180428593278352040);
void pose_F_fun(double *state, double dt, double *out_7556302766395134047);
void pose_h_4(double *state, double *unused, double *out_8616831018009531357);
void pose_H_4(double *state, double *unused, double *out_603353465574763679);
void pose_h_10(double *state, double *unused, double *out_4956865148383568303);
void pose_H_10(double *state, double *unused, double *out_6422333739801875195);
void pose_h_13(double *state, double *unused, double *out_8713729594127404972);
void pose_H_13(double *state, double *unused, double *out_8213984673891464608);
void pose_h_14(double *state, double *unused, double *out_1912344082414302298);
void pose_H_14(double *state, double *unused, double *out_4566594321914248208);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}