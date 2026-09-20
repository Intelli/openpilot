#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5091660165595542600);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_828551828041337701);
void pose_H_mod_fun(double *state, double *out_3117881215721449640);
void pose_f_fun(double *state, double dt, double *out_700662443455454403);
void pose_F_fun(double *state, double dt, double *out_619818181955587961);
void pose_h_4(double *state, double *unused, double *out_7282333748924576152);
void pose_H_4(double *state, double *unused, double *out_6384501191930280634);
void pose_h_10(double *state, double *unused, double *out_612235433249460658);
void pose_H_10(double *state, double *unused, double *out_3494221895027205679);
void pose_h_13(double *state, double *unused, double *out_2245567861189652579);
void pose_H_13(double *state, double *unused, double *out_8849969056446938181);
void pose_h_14(double *state, double *unused, double *out_7916201911112255990);
void pose_H_14(double *state, double *unused, double *out_8099002025439786453);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}