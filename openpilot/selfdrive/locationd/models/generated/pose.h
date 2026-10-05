#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2561165156665466750);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1962872074544000331);
void pose_H_mod_fun(double *state, double *out_279889982478867027);
void pose_f_fun(double *state, double dt, double *out_3993756686932435860);
void pose_F_fun(double *state, double dt, double *out_8805999151920846348);
void pose_h_4(double *state, double *unused, double *out_704160499582318412);
void pose_H_4(double *state, double *unused, double *out_6011978304101277191);
void pose_h_10(double *state, double *unused, double *out_3225747117198463437);
void pose_H_10(double *state, double *unused, double *out_134585223641373339);
void pose_h_13(double *state, double *unused, double *out_638625316845772836);
void pose_H_13(double *state, double *unused, double *out_1598652904215423738);
void pose_h_14(double *state, double *unused, double *out_3735192849560274451);
void pose_H_14(double *state, double *unused, double *out_2048737447761792662);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}