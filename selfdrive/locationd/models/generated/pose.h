#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_222088853381432014);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5630858664606890930);
void pose_H_mod_fun(double *state, double *out_2006534566727409158);
void pose_f_fun(double *state, double dt, double *out_5095165263511672541);
void pose_F_fun(double *state, double dt, double *out_2477765371920509155);
void pose_h_4(double *state, double *unused, double *out_1444896257330890962);
void pose_H_4(double *state, double *unused, double *out_1765272643116498414);
void pose_h_10(double *state, double *unused, double *out_4705883844394877317);
void pose_H_10(double *state, double *unused, double *out_3449679283445996015);
void pose_h_13(double *state, double *unused, double *out_8700690102558969181);
void pose_H_13(double *state, double *unused, double *out_9070840222276352273);
void pose_h_14(double *state, double *unused, double *out_8343334072151647811);
void pose_H_14(double *state, double *unused, double *out_1317515789178873882);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}