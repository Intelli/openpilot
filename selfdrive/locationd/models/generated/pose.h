#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4630147527928263386);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7264677227800699737);
void pose_H_mod_fun(double *state, double *out_5498312016839624203);
void pose_f_fun(double *state, double dt, double *out_8948155690063379520);
void pose_F_fun(double *state, double dt, double *out_4354584664413358096);
void pose_h_4(double *state, double *unused, double *out_3294895423612452149);
void pose_H_4(double *state, double *unused, double *out_2155467184192811800);
void pose_h_10(double *state, double *unused, double *out_189283368100710860);
void pose_H_10(double *state, double *unused, double *out_3614963382677852821);
void pose_h_13(double *state, double *unused, double *out_2399824474141319282);
void pose_H_13(double *state, double *unused, double *out_1056806641139521001);
void pose_h_14(double *state, double *unused, double *out_102831174585947121);
void pose_H_14(double *state, double *unused, double *out_8810131074236999392);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}