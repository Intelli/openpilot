#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_9016928863822956392);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4151582763741233475);
void pose_H_mod_fun(double *state, double *out_4338917552998734116);
void pose_f_fun(double *state, double dt, double *out_5686895573409391632);
void pose_F_fun(double *state, double dt, double *out_4802469097723825273);
void pose_h_4(double *state, double *unused, double *out_7554104894661564763);
void pose_H_4(double *state, double *unused, double *out_8955308135671736765);
void pose_h_10(double *state, double *unused, double *out_6873089334257555130);
void pose_H_10(double *state, double *unused, double *out_3021799401528491989);
void pose_h_13(double *state, double *unused, double *out_4311220329493223705);
void pose_H_13(double *state, double *unused, double *out_5743034310339403964);
void pose_h_14(double *state, double *unused, double *out_8792741387017571645);
void pose_H_14(double *state, double *unused, double *out_4992067279332252236);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}