#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5764489290281003311);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1112330292461843791);
void pose_H_mod_fun(double *state, double *out_1113689545321808981);
void pose_f_fun(double *state, double dt, double *out_6623631471554753598);
void pose_F_fun(double *state, double dt, double *out_4351986266867303872);
void pose_h_4(double *state, double *unused, double *out_6906405556919747882);
void pose_H_4(double *state, double *unused, double *out_359528543267096374);
void pose_h_10(double *state, double *unused, double *out_5632699481090685324);
void pose_H_10(double *state, double *unused, double *out_5235527814809035973);
void pose_h_13(double *state, double *unused, double *out_9169818990097730339);
void pose_H_13(double *state, double *unused, double *out_7251102665049604555);
void pose_h_14(double *state, double *unused, double *out_8130628667462245083);
void pose_H_14(double *state, double *unused, double *out_3603712313072388155);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}