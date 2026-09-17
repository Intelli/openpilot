#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5899152602515428793);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1853168426912981794);
void pose_H_mod_fun(double *state, double *out_4126833233538436701);
void pose_f_fun(double *state, double dt, double *out_4790836135548827488);
void pose_F_fun(double *state, double dt, double *out_8482055114076347653);
void pose_h_4(double *state, double *unused, double *out_1502834332527763816);
void pose_H_4(double *state, double *unused, double *out_4880994235593149308);
void pose_h_10(double *state, double *unused, double *out_6109171037953532925);
void pose_H_10(double *state, double *unused, double *out_7194656996829539727);
void pose_h_13(double *state, double *unused, double *out_5799887535713035202);
void pose_H_13(double *state, double *unused, double *out_8093268060925482109);
void pose_h_14(double *state, double *unused, double *out_2127057284884247461);
void pose_H_14(double *state, double *unused, double *out_8844235091932633837);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}