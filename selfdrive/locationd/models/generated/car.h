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
void car_err_fun(double *nom_x, double *delta_x, double *out_8446512297607145956);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9057774115653867931);
void car_H_mod_fun(double *state, double *out_3508449618144457651);
void car_f_fun(double *state, double dt, double *out_8242977003035772527);
void car_F_fun(double *state, double dt, double *out_5108010767557362242);
void car_h_25(double *state, double *unused, double *out_2574374599262144846);
void car_H_25(double *state, double *unused, double *out_4013784060344754363);
void car_h_24(double *state, double *unused, double *out_5096625633322493085);
void car_H_24(double *state, double *unused, double *out_7857388206773279152);
void car_h_30(double *state, double *unused, double *out_5082664103317425037);
void car_H_30(double *state, double *unused, double *out_7516269671873180498);
void car_h_26(double *state, double *unused, double *out_4479348218640947520);
void car_H_26(double *state, double *unused, double *out_272280741470698139);
void car_h_27(double *state, double *unused, double *out_3742118400338286583);
void car_H_27(double *state, double *unused, double *out_8755711090035946207);
void car_h_29(double *state, double *unused, double *out_6064748196652723149);
void car_H_29(double *state, double *unused, double *out_7006038327558788314);
void car_h_28(double *state, double *unused, double *out_1259554867322559062);
void car_H_28(double *state, double *unused, double *out_6358306729081232728);
void car_h_31(double *state, double *unused, double *out_6436058075690646498);
void car_H_31(double *state, double *unused, double *out_4044430022221714791);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}