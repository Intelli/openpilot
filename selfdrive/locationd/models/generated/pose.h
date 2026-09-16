#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2844503766928312028);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_188944154440250924);
void pose_H_mod_fun(double *state, double *out_7217718077783114524);
void pose_f_fun(double *state, double dt, double *out_6254706918453181358);
void pose_F_fun(double *state, double dt, double *out_5818928030751659740);
void pose_h_4(double *state, double *unused, double *out_3846056568958226266);
void pose_H_4(double *state, double *unused, double *out_8772672876909563643);
void pose_h_10(double *state, double *unused, double *out_3022049088022343856);
void pose_H_10(double *state, double *unused, double *out_4820309526576605798);
void pose_h_13(double *state, double *unused, double *out_4676021508495622785);
void pose_H_13(double *state, double *unused, double *out_5560399051577230842);
void pose_h_14(double *state, double *unused, double *out_7231214306405891091);
void pose_H_14(double *state, double *unused, double *out_4809432020570079114);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}