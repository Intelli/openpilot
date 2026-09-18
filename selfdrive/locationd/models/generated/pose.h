#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5991537263051443263);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2628315792951768716);
void pose_H_mod_fun(double *state, double *out_4425582544225868447);
void pose_f_fun(double *state, double dt, double *out_61910386899534067);
void pose_F_fun(double *state, double dt, double *out_915104698457213198);
void pose_h_4(double *state, double *unused, double *out_4848764096163798698);
void pose_H_4(double *state, double *unused, double *out_5179743546280581054);
void pose_h_10(double *state, double *unused, double *out_6403830294478679987);
void pose_H_10(double *state, double *unused, double *out_1159038497426952620);
void pose_h_13(double *state, double *unused, double *out_8750933078138370929);
void pose_H_13(double *state, double *unused, double *out_5656369319112269633);
void pose_h_14(double *state, double *unused, double *out_7722972172433229947);
void pose_H_14(double *state, double *unused, double *out_2096955113985208758);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}