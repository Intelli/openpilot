#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7318583843401046885);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8604214068849565205);
void pose_H_mod_fun(double *state, double *out_7423581578821108479);
void pose_f_fun(double *state, double dt, double *out_6548671648242666617);
void pose_F_fun(double *state, double dt, double *out_8137210036585204187);
void pose_h_4(double *state, double *unused, double *out_8933482968708726010);
void pose_H_4(double *state, double *unused, double *out_2822857610915218370);
void pose_h_10(double *state, double *unused, double *out_4168852290738747850);
void pose_H_10(double *state, double *unused, double *out_1054675281937211144);
void pose_h_13(double *state, double *unused, double *out_4043461384186272271);
void pose_H_13(double *state, double *unused, double *out_4787773597401482559);
void pose_h_14(double *state, double *unused, double *out_6969961930413222291);
void pose_H_14(double *state, double *unused, double *out_1140383245424266159);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}