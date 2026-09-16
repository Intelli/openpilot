#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2325015377156513737);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6324847366348989757);
void pose_H_mod_fun(double *state, double *out_8008080077202602510);
void pose_f_fun(double *state, double dt, double *out_300170642878345281);
void pose_F_fun(double *state, double dt, double *out_581435981594179307);
void pose_h_4(double *state, double *unused, double *out_1860856687374340932);
void pose_H_4(double *state, double *unused, double *out_2855561692163521775);
void pose_h_10(double *state, double *unused, double *out_8529954627682698254);
void pose_H_10(double *state, double *unused, double *out_7619851342069224566);
void pose_h_13(double *state, double *unused, double *out_8848881485524591493);
void pose_H_13(double *state, double *unused, double *out_356712133168811026);
void pose_h_14(double *state, double *unused, double *out_6213919889321867101);
void pose_H_14(double *state, double *unused, double *out_3290678218808405374);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}