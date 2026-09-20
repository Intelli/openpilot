#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1129901566109211967);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5586445504609754685);
void pose_H_mod_fun(double *state, double *out_6200665308643472860);
void pose_f_fun(double *state, double dt, double *out_8349593971542827612);
void pose_F_fun(double *state, double dt, double *out_2106736445674903187);
void pose_h_4(double *state, double *unused, double *out_5935921283342541016);
void pose_H_4(double *state, double *unused, double *out_7631451728136762392);
void pose_h_10(double *state, double *unused, double *out_6985262437261806861);
void pose_H_10(double *state, double *unused, double *out_1981603586596583282);
void pose_h_13(double *state, double *unused, double *out_5585222753052016340);
void pose_H_13(double *state, double *unused, double *out_20820519820061463);
void pose_h_14(double *state, double *unused, double *out_2199267947897191042);
void pose_H_14(double *state, double *unused, double *out_3668210871797277863);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}