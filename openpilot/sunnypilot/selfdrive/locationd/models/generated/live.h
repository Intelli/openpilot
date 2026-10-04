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
void live_H(double *in_vec, double *out_7870081904618835558);
void live_err_fun(double *nom_x, double *delta_x, double *out_6334826169765757147);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_8058176845842290288);
void live_H_mod_fun(double *state, double *out_2433983787797720501);
void live_f_fun(double *state, double dt, double *out_1532919942130930475);
void live_F_fun(double *state, double dt, double *out_316506153011050602);
void live_h_4(double *state, double *unused, double *out_4675320498710323826);
void live_H_4(double *state, double *unused, double *out_8851587130889490361);
void live_h_9(double *state, double *unused, double *out_1266451267315044262);
void live_H_9(double *state, double *unused, double *out_8610397484259899716);
void live_h_10(double *state, double *unused, double *out_1285981653526407581);
void live_H_10(double *state, double *unused, double *out_5938988922136390066);
void live_h_12(double *state, double *unused, double *out_644179265923301858);
void live_H_12(double *state, double *unused, double *out_3832130722857528566);
void live_h_35(double *state, double *unused, double *out_3839657971583868981);
void live_H_35(double *state, double *unused, double *out_5484925073516882985);
void live_h_32(double *state, double *unused, double *out_7317278974024184109);
void live_H_32(double *state, double *unused, double *out_6046954496498552275);
void live_h_13(double *state, double *unused, double *out_2818149804466527673);
void live_H_13(double *state, double *unused, double *out_5796361080478786871);
void live_h_14(double *state, double *unused, double *out_1266451267315044262);
void live_H_14(double *state, double *unused, double *out_8610397484259899716);
void live_h_33(double *state, double *unused, double *out_3824926259158853643);
void live_H_33(double *state, double *unused, double *out_2334368068878025381);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}