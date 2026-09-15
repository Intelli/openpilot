#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4724133448419912693);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6531814374965429464);
void pose_H_mod_fun(double *state, double *out_4336476144052946499);
void pose_f_fun(double *state, double dt, double *out_5802866657257443587);
void pose_F_fun(double *state, double dt, double *out_4553776162496472303);
void pose_h_4(double *state, double *unused, double *out_3898746135561568286);
void pose_H_4(double *state, double *unused, double *out_6156174869959243360);
void pose_h_10(double *state, double *unused, double *out_5696118002194808494);
void pose_H_10(double *state, double *unused, double *out_2562922199780515749);
void pose_h_13(double *state, double *unused, double *out_5143493122680971933);
void pose_H_13(double *state, double *unused, double *out_1454456338357457569);
void pose_h_14(double *state, double *unused, double *out_1192181091089126491);
void pose_H_14(double *state, double *unused, double *out_2192934013619758831);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}