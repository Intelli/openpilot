#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_265137795402476550);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3199037104659900402);
void pose_H_mod_fun(double *state, double *out_3725952604437651116);
void pose_f_fun(double *state, double dt, double *out_8735875083257225398);
void pose_F_fun(double *state, double dt, double *out_2023248126785481392);
void pose_h_4(double *state, double *unused, double *out_5920813341822676961);
void pose_H_4(double *state, double *unused, double *out_7497759814281558688);
void pose_h_10(double *state, double *unused, double *out_232400473007304790);
void pose_H_10(double *state, double *unused, double *out_8496945975479553735);
void pose_h_13(double *state, double *unused, double *out_6031288345573279101);
void pose_H_13(double *state, double *unused, double *out_3338353051111291999);
void pose_h_14(double *state, double *unused, double *out_4049097322198884432);
void pose_H_14(double *state, double *unused, double *out_4414971381986186392);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}