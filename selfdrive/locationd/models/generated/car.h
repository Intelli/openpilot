#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_7352776745859294438);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2797254755301616602);
void car_H_mod_fun(double *state, double *out_5490718872353398943);
void car_f_fun(double *state, double dt, double *out_2803517744059257752);
void car_F_fun(double *state, double dt, double *out_1627923674770080030);
void car_h_25(double *state, double *unused, double *out_7271936812348157431);
void car_H_25(double *state, double *unused, double *out_4615410128014395963);
void car_h_24(double *state, double *unused, double *out_1124221862302097569);
void car_H_24(double *state, double *unused, double *out_9084824618728646619);
void car_h_30(double *state, double *unused, double *out_8722568204977040598);
void car_H_30(double *state, double *unused, double *out_2097077169507147336);
void car_h_26(double *state, double *unused, double *out_5685782153532707913);
void car_H_26(double *state, double *unused, double *out_8356913446888452187);
void car_h_27(double *state, double *unused, double *out_5832940025475363622);
void car_H_27(double *state, double *unused, double *out_4271840481307572247);
void car_h_29(double *state, double *unused, double *out_3720894937316194953);
void car_H_29(double *state, double *unused, double *out_1586845825192755152);
void car_h_28(double *state, double *unused, double *out_2796153974031030937);
void car_H_28(double *state, double *unused, double *out_6669244842262285726);
void car_h_31(double *state, double *unused, double *out_7114750143997028286);
void car_H_31(double *state, double *unused, double *out_8983121549121803663);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}