#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1246780800306708420);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_322701955714434799);
void pose_H_mod_fun(double *state, double *out_950382144461574038);
void pose_f_fun(double *state, double dt, double *out_5588529265753131833);
void pose_F_fun(double *state, double dt, double *out_2504363338325754815);
void pose_h_4(double *state, double *unused, double *out_7147282312282672959);
void pose_H_4(double *state, double *unused, double *out_4897699662290384683);
void pose_h_10(double *state, double *unused, double *out_9130545523462966991);
void pose_H_10(double *state, double *unused, double *out_6830444104489603573);
void pose_h_13(double *state, double *unused, double *out_6263563644976026350);
void pose_H_13(double *state, double *unused, double *out_1685425836958051882);
void pose_h_14(double *state, double *unused, double *out_5438998319357703596);
void pose_H_14(double *state, double *unused, double *out_934458805950900154);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}