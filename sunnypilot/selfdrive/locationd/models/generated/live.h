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
void live_H(double *in_vec, double *out_4106676231220411782);
void live_err_fun(double *nom_x, double *delta_x, double *out_8798544219538628490);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_3639850515106216413);
void live_H_mod_fun(double *state, double *out_1990826455950661216);
void live_f_fun(double *state, double dt, double *out_1927945319651803687);
void live_F_fun(double *state, double dt, double *out_6859901860120386932);
void live_h_4(double *state, double *unused, double *out_4527308209862999637);
void live_H_4(double *state, double *unused, double *out_7399889148554559418);
void live_h_9(double *state, double *unused, double *out_6606434635025775848);
void live_H_9(double *state, double *unused, double *out_3759635989890544728);
void live_h_10(double *state, double *unused, double *out_7898011716486871827);
void live_H_10(double *state, double *unused, double *out_8830409584232176020);
void live_h_12(double *state, double *unused, double *out_8187161129942171201);
void live_H_12(double *state, double *unused, double *out_1018630771511826422);
void live_h_35(double *state, double *unused, double *out_3537994454635650386);
void live_H_35(double *state, double *unused, double *out_634163579147527997);
void live_h_32(double *state, double *unused, double *out_3326475150974004437);
void live_H_32(double *state, double *unused, double *out_7549028082841644353);
void live_h_13(double *state, double *unused, double *out_639542240863771175);
void live_H_13(double *state, double *unused, double *out_3883136022272514747);
void live_h_14(double *state, double *unused, double *out_6606434635025775848);
void live_H_14(double *state, double *unused, double *out_3759635989890544728);
void live_h_33(double *state, double *unused, double *out_4187548000188405803);
void live_H_33(double *state, double *unused, double *out_2516393425491329607);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}