#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8794951023692473693);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_147609790886506349);
void pose_H_mod_fun(double *state, double *out_4713269657164746226);
void pose_f_fun(double *state, double dt, double *out_8307718287749749495);
void pose_F_fun(double *state, double dt, double *out_2796913824456762059);
void pose_h_4(double *state, double *unused, double *out_9193516370136012539);
void pose_H_4(double *state, double *unused, double *out_3657757106827190501);
void pose_h_10(double *state, double *unused, double *out_5330616401180944027);
void pose_H_10(double *state, double *unused, double *out_1395272858445918149);
void pose_h_13(double *state, double *unused, double *out_8491663337253319846);
void pose_H_13(double *state, double *unused, double *out_6870030932159523302);
void pose_h_14(double *state, double *unused, double *out_730939643929042312);
void pose_H_14(double *state, double *unused, double *out_574968674531818205);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}