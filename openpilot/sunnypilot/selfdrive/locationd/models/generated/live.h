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
void live_H(double *in_vec, double *out_4804737763829635979);
void live_err_fun(double *nom_x, double *delta_x, double *out_4473331695791129559);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_92097654233209623);
void live_H_mod_fun(double *state, double *out_4655480727105486234);
void live_f_fun(double *state, double dt, double *out_9112177356581956333);
void live_F_fun(double *state, double dt, double *out_7518876851550340641);
void live_h_4(double *state, double *unused, double *out_3828722671037477727);
void live_H_4(double *state, double *unused, double *out_291391154670860649);
void live_h_9(double *state, double *unused, double *out_4893909245178932598);
void live_H_9(double *state, double *unused, double *out_3865776581683916834);
void live_h_10(double *state, double *unused, double *out_8105500715036822121);
void live_H_10(double *state, double *unused, double *out_1869374218469703606);
void live_h_12(double *state, double *unused, double *out_413006695460515797);
void live_H_12(double *state, double *unused, double *out_912490179718454316);
void live_h_35(double *state, double *unused, double *out_3483902817321414833);
void live_H_35(double *state, double *unused, double *out_3658053212043468025);
void live_h_32(double *state, double *unused, double *out_5507274868859097590);
void live_H_32(double *state, double *unused, double *out_7205897552030626754);
void live_h_13(double *state, double *unused, double *out_6844552832565306328);
void live_H_13(double *state, double *unused, double *out_8859865575493772568);
void live_h_14(double *state, double *unused, double *out_4893909245178932598);
void live_H_14(double *state, double *unused, double *out_3865776581683916834);
void live_h_33(double *state, double *unused, double *out_875604746051228925);
void live_H_33(double *state, double *unused, double *out_6808610216682325629);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}