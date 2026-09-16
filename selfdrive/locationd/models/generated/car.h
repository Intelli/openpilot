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
void car_err_fun(double *nom_x, double *delta_x, double *out_7186638227715885905);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9217405337689464457);
void car_H_mod_fun(double *state, double *out_6413049500361186115);
void car_f_fun(double *state, double dt, double *out_978474071055538604);
void car_F_fun(double *state, double dt, double *out_5409566246741176518);
void car_h_25(double *state, double *unused, double *out_3060269925431251514);
void car_H_25(double *state, double *unused, double *out_316141133754811499);
void car_h_24(double *state, double *unused, double *out_5581065705820566916);
void car_H_24(double *state, double *unused, double *out_3874066732557134635);
void car_h_30(double *state, double *unused, double *out_6982152288037516471);
void car_H_30(double *state, double *unused, double *out_7232831475246428254);
void car_h_26(double *state, double *unused, double *out_4274242739788829303);
void car_H_26(double *state, double *unused, double *out_3620667103515612100);
void car_h_27(double *state, double *unused, double *out_6097055976875584199);
void car_H_27(double *state, double *unused, double *out_5058068163446003343);
void car_h_29(double *state, double *unused, double *out_5821861914591078310);
void car_H_29(double *state, double *unused, double *out_7743062819560820438);
void car_h_28(double *state, double *unused, double *out_6366764257527825664);
void car_H_28(double *state, double *unused, double *out_2660663802491289864);
void car_h_31(double *state, double *unused, double *out_2602068563272689852);
void car_H_31(double *state, double *unused, double *out_7392816384266628752);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}