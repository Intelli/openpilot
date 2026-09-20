#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4788240677246511833);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5975192517926128029);
void pose_H_mod_fun(double *state, double *out_1132541603520551659);
void pose_f_fun(double *state, double dt, double *out_4710851946960034212);
void pose_F_fun(double *state, double dt, double *out_8035530764887172818);
void pose_h_4(double *state, double *unused, double *out_5758439189671492522);
void pose_H_4(double *state, double *unused, double *out_5653546144624826768);
void pose_h_10(double *state, double *unused, double *out_4438741120644189837);
void pose_H_10(double *state, double *unused, double *out_4815704039696511932);
void pose_h_13(double *state, double *unused, double *out_1473597949739903729);
void pose_H_13(double *state, double *unused, double *out_1957085063691874161);
void pose_h_14(double *state, double *unused, double *out_3842475002178970014);
void pose_H_14(double *state, double *unused, double *out_8736334576920199064);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}