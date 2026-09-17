#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5999999625262296722);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_608932248278116384);
void pose_H_mod_fun(double *state, double *out_5835985313550633106);
void pose_f_fun(double *state, double dt, double *out_5863158505292019107);
void pose_F_fun(double *state, double dt, double *out_1611471319636251524);
void pose_h_4(double *state, double *unused, double *out_1124236774130910347);
void pose_H_4(double *state, double *unused, double *out_2064178103706725534);
void pose_h_10(double *state, double *unused, double *out_1155728135803400153);
void pose_H_10(double *state, double *unused, double *out_8226063157301123461);
void pose_h_13(double *state, double *unused, double *out_4927127245414031844);
void pose_H_13(double *state, double *unused, double *out_1499576184024881430);
void pose_h_14(double *state, double *unused, double *out_7188704726752566078);
void pose_H_14(double *state, double *unused, double *out_5146966536002097830);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}