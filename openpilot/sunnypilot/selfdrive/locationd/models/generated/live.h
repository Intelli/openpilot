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
void live_H(double *in_vec, double *out_2582016779842555919);
void live_err_fun(double *nom_x, double *delta_x, double *out_8051606083940632368);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_3218006689515805213);
void live_H_mod_fun(double *state, double *out_6326419125419769433);
void live_f_fun(double *state, double dt, double *out_6518109257649848762);
void live_F_fun(double *state, double dt, double *out_6799741306415315042);
void live_h_4(double *state, double *unused, double *out_1990305592483740549);
void live_H_4(double *state, double *unused, double *out_5587904301212687159);
void live_h_9(double *state, double *unused, double *out_7083436011394676187);
void live_H_9(double *state, double *unused, double *out_1699314634051760311);
void live_h_10(double *state, double *unused, double *out_3293139685756091351);
void live_H_10(double *state, double *unused, double *out_8898080828769490400);
void live_h_12(double *state, double *unused, double *out_6018786823362259383);
void live_H_12(double *state, double *unused, double *out_6477581395454131461);
void live_h_35(double *state, double *unused, double *out_1864971253144397367);
void live_H_35(double *state, double *unused, double *out_2177115139144288345);
void live_h_32(double *state, double *unused, double *out_1903308315975440781);
void live_H_32(double *state, double *unused, double *out_3866081753550979385);
void live_h_13(double *state, double *unused, double *out_6208980428892528476);
void live_H_13(double *state, double *unused, double *out_1844175838319099911);
void live_h_14(double *state, double *unused, double *out_7083436011394676187);
void live_H_14(double *state, double *unused, double *out_1699314634051760311);
void live_h_33(double *state, double *unused, double *out_4411801792000451158);
void live_H_33(double *state, double *unused, double *out_7975344049433634646);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}