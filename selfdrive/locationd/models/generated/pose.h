#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8200257521780243420);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3514907883279273646);
void pose_H_mod_fun(double *state, double *out_3189646925905620491);
void pose_f_fun(double *state, double dt, double *out_252565399931934628);
void pose_F_fun(double *state, double dt, double *out_519143980273656889);
void pose_h_4(double *state, double *unused, double *out_2972557042417062016);
void pose_H_4(double *state, double *unused, double *out_6463869004696569744);
void pose_h_10(double *state, double *unused, double *out_6282181365633460772);
void pose_H_10(double *state, double *unused, double *out_8114151188329229777);
void pose_h_13(double *state, double *unused, double *out_3807456519538966309);
void pose_H_13(double *state, double *unused, double *out_3251595179364236943);
void pose_h_14(double *state, double *unused, double *out_2724310507005535047);
void pose_H_14(double *state, double *unused, double *out_2500628148357085215);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}