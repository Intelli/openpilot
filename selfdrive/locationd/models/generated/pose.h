#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8838830420648207010);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2885477467670563304);
void pose_H_mod_fun(double *state, double *out_7096528025583759202);
void pose_f_fun(double *state, double dt, double *out_8038070982033161577);
void pose_F_fun(double *state, double dt, double *out_794702288486851768);
void pose_h_4(double *state, double *unused, double *out_5361717666727753051);
void pose_H_4(double *state, double *unused, double *out_8075993969334843161);
void pose_h_10(double *state, double *unused, double *out_391166273927914197);
void pose_H_10(double *state, double *unused, double *out_2614348763027175247);
void pose_h_13(double *state, double *unused, double *out_6109132341939542181);
void pose_H_13(double *state, double *unused, double *out_7158476279042375654);
void pose_h_14(double *state, double *unused, double *out_6365736750673459896);
void pose_H_14(double *state, double *unused, double *out_6407509248035223926);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}