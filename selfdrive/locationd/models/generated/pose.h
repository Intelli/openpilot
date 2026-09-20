#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6202662645191369);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5065890083902176780);
void pose_H_mod_fun(double *state, double *out_4147804714257678696);
void pose_f_fun(double *state, double dt, double *out_134451283192963896);
void pose_F_fun(double *state, double dt, double *out_7947855407511726470);
void pose_h_4(double *state, double *unused, double *out_7278578289213708861);
void pose_H_4(double *state, double *unused, double *out_5967503440163975557);
void pose_h_10(double *state, double *unused, double *out_7255837942068693372);
void pose_H_10(double *state, double *unused, double *out_2797151911620261444);
void pose_h_13(double *state, double *unused, double *out_4677326677955265500);
void pose_H_13(double *state, double *unused, double *out_8645485170243052035);
void pose_h_14(double *state, double *unused, double *out_8166535974230408665);
void pose_H_14(double *state, double *unused, double *out_9050291872459347853);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}