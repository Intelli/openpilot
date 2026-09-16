#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7076630439446261590);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2828328233536285037);
void pose_H_mod_fun(double *state, double *out_180736316877999173);
void pose_f_fun(double *state, double dt, double *out_3533683092462162875);
void pose_F_fun(double *state, double dt, double *out_5100092372859724848);
void pose_h_4(double *state, double *unused, double *out_7074427651173269504);
void pose_H_4(double *state, double *unused, double *out_1236248867215554898);
void pose_h_10(double *state, double *unused, double *out_1452877130807937946);
void pose_H_10(double *state, double *unused, double *out_4992083827767139638);
void pose_h_13(double *state, double *unused, double *out_7690389037451804524);
void pose_H_13(double *state, double *unused, double *out_1976024958116777903);
void pose_h_14(double *state, double *unused, double *out_9127280363092827270);
void pose_H_14(double *state, double *unused, double *out_4319037299510927194);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}