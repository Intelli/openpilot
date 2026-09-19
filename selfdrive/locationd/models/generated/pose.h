#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2757450705506867855);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2371677109582741398);
void pose_H_mod_fun(double *state, double *out_7009258506666885735);
void pose_f_fun(double *state, double dt, double *out_3443385267993362178);
void pose_F_fun(double *state, double dt, double *out_3344416469963573399);
void pose_h_4(double *state, double *unused, double *out_5247280839960053081);
void pose_H_4(double *state, double *unused, double *out_4508962887351945075);
void pose_h_10(double *state, double *unused, double *out_9164942161681221546);
void pose_H_10(double *state, double *unused, double *out_7905481608622117688);
void pose_h_13(double *state, double *unused, double *out_4129298553195873659);
void pose_H_13(double *state, double *unused, double *out_1296689062019612274);
void pose_h_14(double *state, double *unused, double *out_3157172185554168331);
void pose_H_14(double *state, double *unused, double *out_7591751319647317371);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}