#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7239197641731070156);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_217209870609913891);
void pose_H_mod_fun(double *state, double *out_8844683690844308926);
void pose_f_fun(double *state, double dt, double *out_371859905987646833);
void pose_F_fun(double *state, double dt, double *out_5262243657608806363);
void pose_h_4(double *state, double *unused, double *out_3538877410533377824);
void pose_H_4(double *state, double *unused, double *out_5830253173021335118);
void pose_h_10(double *state, double *unused, double *out_2136400816105186670);
void pose_H_10(double *state, double *unused, double *out_7987660615244689739);
void pose_h_13(double *state, double *unused, double *out_7049441698464861794);
void pose_H_13(double *state, double *unused, double *out_5265651253339491014);
void pose_h_14(double *state, double *unused, double *out_1548028699133749812);
void pose_H_14(double *state, double *unused, double *out_8913041605316707414);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}