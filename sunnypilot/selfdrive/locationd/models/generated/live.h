#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_8984514581391162091);
void live_err_fun(double *nom_x, double *delta_x, double *out_6940569659140605087);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_3742606533975212020);
void live_H_mod_fun(double *state, double *out_6419973122373865723);
void live_f_fun(double *state, double dt, double *out_1970565073852462835);
void live_F_fun(double *state, double dt, double *out_3303824337657404013);
void live_h_4(double *state, double *unused, double *out_6241679912291559969);
void live_H_4(double *state, double *unused, double *out_738470078662272562);
void live_h_9(double *state, double *unused, double *out_946535278572243899);
void live_H_9(double *state, double *unused, double *out_6548748856602174908);
void live_h_10(double *state, double *unused, double *out_6738972060598859447);
void live_H_10(double *state, double *unused, double *out_8533635998756131899);
void live_h_12(double *state, double *unused, double *out_6918538293040476422);
void live_H_12(double *state, double *unused, double *out_6928658235020177930);
void live_h_35(double *state, double *unused, double *out_5608265990080007063);
void live_H_35(double *state, double *unused, double *out_2628191978710334814);
void live_h_32(double *state, double *unused, double *out_4575559764843827496);
void live_H_32(double *state, double *unused, double *out_5988864641945942384);
void live_h_13(double *state, double *unused, double *out_745990428519966593);
void live_H_13(double *state, double *unused, double *out_1774997206207026831);
void live_h_14(double *state, double *unused, double *out_946535278572243899);
void live_H_14(double *state, double *unused, double *out_6548748856602174908);
void live_h_33(double *state, double *unused, double *out_6681757322936825613);
void live_H_33(double *state, double *unused, double *out_5778748983349192418);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}