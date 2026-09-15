#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2182538694400222550);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3636770726618230824);
void pose_H_mod_fun(double *state, double *out_5732313931484354230);
void pose_f_fun(double *state, double dt, double *out_8124696220925940808);
void pose_F_fun(double *state, double dt, double *out_282840327706957589);
void pose_h_4(double *state, double *unused, double *out_5925821027563078418);
void pose_H_4(double *state, double *unused, double *out_6930261413367252334);
void pose_h_10(double *state, double *unused, double *out_7088557639870104909);
void pose_H_10(double *state, double *unused, double *out_8659962992607815749);
void pose_h_13(double *state, double *unused, double *out_5685915155655708417);
void pose_H_13(double *state, double *unused, double *out_8304208835009966481);
void pose_h_14(double *state, double *unused, double *out_211775679460280009);
void pose_H_14(double *state, double *unused, double *out_3847472981071880038);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}