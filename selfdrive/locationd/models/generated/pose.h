#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1302882686935522561);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_9056716141039600519);
void pose_H_mod_fun(double *state, double *out_55467954928580080);
void pose_f_fun(double *state, double dt, double *out_1954087496247120441);
void pose_F_fun(double *state, double dt, double *out_8221376313792984867);
void pose_h_4(double *state, double *unused, double *out_7512970159079020892);
void pose_H_4(double *state, double *unused, double *out_698693047126132527);
void pose_h_10(double *state, double *unused, double *out_6422679790916561236);
void pose_H_10(double *state, double *unused, double *out_4658569367636697608);
void pose_h_13(double *state, double *unused, double *out_7592318235637912656);
void pose_H_13(double *state, double *unused, double *out_3910966872458465328);
void pose_h_14(double *state, double *unused, double *out_2616018567407793546);
void pose_H_14(double *state, double *unused, double *out_4661933903465617056);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}