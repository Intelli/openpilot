#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8619877196673941904);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5079236499620164768);
void pose_H_mod_fun(double *state, double *out_3834855492212920326);
void pose_f_fun(double *state, double dt, double *out_271549942577683268);
void pose_F_fun(double *state, double dt, double *out_8758390952692881982);
void pose_h_4(double *state, double *unused, double *out_4085392694727598368);
void pose_H_4(double *state, double *unused, double *out_3080694490158207719);
void pose_h_10(double *state, double *unused, double *out_8653843584460147373);
void pose_H_10(double *state, double *unused, double *out_1350506859556886668);
void pose_h_13(double *state, double *unused, double *out_6805598292797670581);
void pose_H_13(double *state, double *unused, double *out_4529936718158493210);
void pose_h_14(double *state, double *unused, double *out_7201729596421949005);
void pose_H_14(double *state, double *unused, double *out_6163482922453580015);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}