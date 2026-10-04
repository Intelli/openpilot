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
void live_H(double *in_vec, double *out_7030349046328016536);
void live_err_fun(double *nom_x, double *delta_x, double *out_1858310598967300904);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_8790134798765675821);
void live_H_mod_fun(double *state, double *out_8928128772882965191);
void live_f_fun(double *state, double dt, double *out_3941485355868554113);
void live_F_fun(double *state, double dt, double *out_3977057823515082469);
void live_h_4(double *state, double *unused, double *out_2738214305468595925);
void live_H_4(double *state, double *unused, double *out_1637156565452069253);
void live_h_9(double *state, double *unused, double *out_280940033002323536);
void live_H_9(double *state, double *unused, double *out_8924375500716516723);
void live_h_10(double *state, double *unused, double *out_8194075064688507140);
void live_H_10(double *state, double *unused, double *out_6384022673832351745);
void live_h_12(double *state, double *unused, double *out_7499272242628491220);
void live_H_12(double *state, double *unused, double *out_6656612973484031048);
void live_h_35(double *state, double *unused, double *out_569470800795752603);
void live_H_35(double *state, double *unused, double *out_9044568067900506859);
void live_h_32(double *state, double *unused, double *out_3992670189700262586);
void live_H_32(double *state, double *unused, double *out_785119385152767559);
void live_h_13(double *state, double *unused, double *out_3704621429129933521);
void live_H_13(double *state, double *unused, double *out_8015795064950764628);
void live_h_14(double *state, double *unused, double *out_280940033002323536);
void live_H_14(double *state, double *unused, double *out_8924375500716516723);
void live_h_33(double *state, double *unused, double *out_8415419969140816671);
void live_H_33(double *state, double *unused, double *out_5894011063261649255);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}