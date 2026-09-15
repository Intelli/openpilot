#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8015077839077896466);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_120875525776824592);
void pose_H_mod_fun(double *state, double *out_6916249509140048441);
void pose_f_fun(double *state, double dt, double *out_4090535296156790500);
void pose_F_fun(double *state, double dt, double *out_3730744472462246424);
void pose_h_4(double *state, double *unused, double *out_5341722606028163908);
void pose_H_4(double *state, double *unused, double *out_5096550783233751580);
void pose_h_10(double *state, double *unused, double *out_9209642980587727009);
void pose_H_10(double *state, double *unused, double *out_2564039051245540813);
void pose_h_13(double *state, double *unused, double *out_7516940390179027057);
void pose_H_13(double *state, double *unused, double *out_8308824608566084381);
void pose_h_14(double *state, double *unused, double *out_4591991634188895423);
void pose_H_14(double *state, double *unused, double *out_9059791639573236109);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}