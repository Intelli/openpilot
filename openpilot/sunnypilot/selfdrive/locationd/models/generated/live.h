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
void live_H(double *in_vec, double *out_4206635673687684447);
void live_err_fun(double *nom_x, double *delta_x, double *out_2996738844093448965);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_1656788043622297726);
void live_H_mod_fun(double *state, double *out_3605986615940566567);
void live_f_fun(double *state, double dt, double *out_3389205617761735779);
void live_F_fun(double *state, double dt, double *out_3364095401076288303);
void live_h_4(double *state, double *unused, double *out_8522587519876858261);
void live_H_4(double *state, double *unused, double *out_3632952683891194894);
void live_h_9(double *state, double *unused, double *out_3039960679045957117);
void live_H_9(double *state, double *unused, double *out_744091131611115552);
void live_h_10(double *state, double *unused, double *out_1973515044738180906);
void live_H_10(double *state, double *unused, double *out_3495603768961973535);
void live_h_12(double *state, double *unused, double *out_5631191467248715845);
void live_H_12(double *state, double *unused, double *out_3011853658843601227);
void live_h_35(double *state, double *unused, double *out_4476658985134725015);
void live_H_35(double *state, double *unused, double *out_266290626518587518);
void live_h_32(double *state, double *unused, double *out_7564539267483544353);
void live_H_32(double *state, double *unused, double *out_135125841577847049);
void live_h_13(double *state, double *unused, double *out_4510953799549587955);
void live_H_13(double *state, double *unused, double *out_1574385221239692991);
void live_h_14(double *state, double *unused, double *out_3039960679045957117);
void live_H_14(double *state, double *unused, double *out_744091131611115552);
void live_h_33(double *state, double *unused, double *out_1817573706188481740);
void live_H_33(double *state, double *unused, double *out_2884266378120270086);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}