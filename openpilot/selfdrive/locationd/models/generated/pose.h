#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3124141466551087525);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2496827843304733878);
void pose_H_mod_fun(double *state, double *out_8432171404531004476);
void pose_f_fun(double *state, double dt, double *out_5003705705076485198);
void pose_F_fun(double *state, double dt, double *out_228980895344950613);
void pose_h_4(double *state, double *unused, double *out_5085675732535578637);
void pose_H_4(double *state, double *unused, double *out_306024827551984662);
void pose_h_10(double *state, double *unused, double *out_4336648869499679786);
void pose_H_10(double *state, double *unused, double *out_1911216833332166041);
void pose_h_13(double *state, double *unused, double *out_6880935629319661407);
void pose_H_13(double *state, double *unused, double *out_3518298652884317463);
void pose_h_14(double *state, double *unused, double *out_2812231938192808748);
void pose_H_14(double *state, double *unused, double *out_4269265683891469191);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}