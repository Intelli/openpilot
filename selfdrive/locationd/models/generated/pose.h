#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6965396131273747251);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7732022762673456989);
void pose_H_mod_fun(double *state, double *out_387031049435319729);
void pose_f_fun(double *state, double dt, double *out_4790244506834107583);
void pose_F_fun(double *state, double dt, double *out_4347921339132117367);
void pose_h_4(double *state, double *unused, double *out_8125039053526857015);
void pose_H_4(double *state, double *unused, double *out_1141192051490032336);
void pose_h_10(double *state, double *unused, double *out_1313374945329114385);
void pose_H_10(double *state, double *unused, double *out_3646778444555579065);
void pose_h_13(double *state, double *unused, double *out_488303792701597214);
void pose_H_13(double *state, double *unused, double *out_4353465876822365137);
void pose_h_14(double *state, double *unused, double *out_8265272713495484247);
void pose_H_14(double *state, double *unused, double *out_1941596380805339960);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}