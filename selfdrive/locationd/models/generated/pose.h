#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3776217962159825712);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_838326120936530935);
void pose_H_mod_fun(double *state, double *out_3231377197098151338);
void pose_f_fun(double *state, double dt, double *out_4330621084971378974);
void pose_F_fun(double *state, double dt, double *out_2585841718456555900);
void pose_h_4(double *state, double *unused, double *out_7879074859447355491);
void pose_H_4(double *state, double *unused, double *out_2477216195043438731);
void pose_h_10(double *state, double *unused, double *out_2609678945296250804);
void pose_H_10(double *state, double *unused, double *out_6604444469350949959);
void pose_h_13(double *state, double *unused, double *out_4854758582756767043);
void pose_H_13(double *state, double *unused, double *out_735057630288894070);
void pose_h_14(double *state, double *unused, double *out_6697923167830866865);
void pose_H_14(double *state, double *unused, double *out_1486024661296045798);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}