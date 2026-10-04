#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4493672777545328076);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5066533354290862084);
void pose_H_mod_fun(double *state, double *out_8162690843869849499);
void pose_f_fun(double *state, double dt, double *out_646878254199369471);
void pose_F_fun(double *state, double dt, double *out_1718881751207348558);
void pose_h_4(double *state, double *unused, double *out_3274903405179125684);
void pose_H_4(double *state, double *unused, double *out_8916851845924562106);
void pose_h_10(double *state, double *unused, double *out_488427281484310343);
void pose_H_10(double *state, double *unused, double *out_6921454365113393626);
void pose_h_13(double *state, double *unused, double *out_3716360482112169298);
void pose_H_13(double *state, double *unused, double *out_6317618402452656709);
void pose_h_14(double *state, double *unused, double *out_9126146822157534085);
void pose_H_14(double *state, double *unused, double *out_5566651371445504981);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}