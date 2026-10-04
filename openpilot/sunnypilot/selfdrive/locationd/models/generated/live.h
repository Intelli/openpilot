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
void live_H(double *in_vec, double *out_4562598538624347341);
void live_err_fun(double *nom_x, double *delta_x, double *out_3453226043256074474);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_8962595521594735347);
void live_H_mod_fun(double *state, double *out_2917453322154412475);
void live_f_fun(double *state, double dt, double *out_8427599082655307051);
void live_F_fun(double *state, double dt, double *out_8185144298360805661);
void live_h_4(double *state, double *unused, double *out_5105207208415084876);
void live_H_4(double *state, double *unused, double *out_4753861728382815566);
void live_h_9(double *state, double *unused, double *out_3158925288946285694);
void live_H_9(double *state, double *unused, double *out_4512672081753224921);
void live_h_10(double *state, double *unused, double *out_7704695621362722595);
void live_H_10(double *state, double *unused, double *out_8015120631741114525);
void live_h_12(double *state, double *unused, double *out_3994499226381862950);
void live_H_12(double *state, double *unused, double *out_4132762703335221899);
void live_h_35(double *state, double *unused, double *out_750674325511485652);
void live_H_35(double *state, double *unused, double *out_1387199671010208190);
void live_h_32(double *state, double *unused, double *out_3307226305935620159);
void live_H_32(double *state, double *unused, double *out_6284213864130623313);
void live_h_13(double *state, double *unused, double *out_1173839242723260278);
void live_H_13(double *state, double *unused, double *out_3712690105474607682);
void live_h_14(double *state, double *unused, double *out_3158925288946285694);
void live_H_14(double *state, double *unused, double *out_4512672081753224921);
void live_h_33(double *state, double *unused, double *out_5302164482247605577);
void live_H_33(double *state, double *unused, double *out_1763357333628649414);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}