#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4883205334769300531);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2778782879349748614);
void pose_H_mod_fun(double *state, double *out_650126789788623456);
void pose_f_fun(double *state, double dt, double *out_8901743997806544277);
void pose_F_fun(double *state, double dt, double *out_187766544558398161);
void pose_h_4(double *state, double *unused, double *out_8738596878988744694);
void pose_H_4(double *state, double *unused, double *out_474008514404795419);
void pose_h_10(double *state, double *unused, double *out_7482317449235390315);
void pose_H_10(double *state, double *unused, double *out_5152479438196498760);
void pose_h_13(double *state, double *unused, double *out_5771768815104758354);
void pose_H_13(double *state, double *unused, double *out_3686282339737128220);
void pose_h_14(double *state, double *unused, double *out_6649299331559184012);
void pose_H_14(double *state, double *unused, double *out_38891987759911820);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}