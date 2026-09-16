#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3332094354178799206);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6787681857429762222);
void pose_H_mod_fun(double *state, double *out_699928149424030002);
void pose_f_fun(double *state, double dt, double *out_1867137519926473675);
void pose_F_fun(double *state, double dt, double *out_9116919347276229378);
void pose_h_4(double *state, double *unused, double *out_6089064433593564706);
void pose_H_4(double *state, double *unused, double *out_4452590235615050733);
void pose_h_10(double *state, double *unused, double *out_2469906940172367738);
void pose_H_10(double *state, double *unused, double *out_2054220961747582832);
void pose_h_13(double *state, double *unused, double *out_1980844008070145866);
void pose_H_13(double *state, double *unused, double *out_618834772312526709);
void pose_h_14(double *state, double *unused, double *out_1213929799491886433);
void pose_H_14(double *state, double *unused, double *out_1369801803319678437);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}