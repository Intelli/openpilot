#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3020435366952319765);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3417424495517393488);
void pose_H_mod_fun(double *state, double *out_2051793842018390757);
void pose_f_fun(double *state, double dt, double *out_1030564392189718068);
void pose_F_fun(double *state, double dt, double *out_8175556432247197768);
void pose_h_4(double *state, double *unused, double *out_4843592748572526684);
void pose_H_4(double *state, double *unused, double *out_6892567824039430585);
void pose_h_10(double *state, double *unused, double *out_3178717001943207923);
void pose_H_10(double *state, double *unused, double *out_2573295092091137817);
void pose_h_13(double *state, double *unused, double *out_5513627389062910490);
void pose_H_13(double *state, double *unused, double *out_3680293998707097784);
void pose_h_14(double *state, double *unused, double *out_1993056798844969004);
void pose_H_14(double *state, double *unused, double *out_8471387817374748735);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}