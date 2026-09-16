#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3965258856132538103);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5412015007655879645);
void pose_H_mod_fun(double *state, double *out_4522806033046979489);
void pose_f_fun(double *state, double dt, double *out_4549035263779007924);
void pose_F_fun(double *state, double dt, double *out_8864985683110121579);
void pose_h_4(double *state, double *unused, double *out_3762734515711563779);
void pose_H_4(double *state, double *unused, double *out_672365171686404261);
void pose_h_10(double *state, double *unused, double *out_3744239542214290894);
void pose_H_10(double *state, double *unused, double *out_704080362957931033);
void pose_h_13(double *state, double *unused, double *out_6770705826550858406);
void pose_H_13(double *state, double *unused, double *out_2539908653645928540);
void pose_h_14(double *state, double *unused, double *out_3527789304040821044);
void pose_H_14(double *state, double *unused, double *out_3290875684653080268);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}