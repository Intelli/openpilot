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
void car_err_fun(double *nom_x, double *delta_x, double *out_8118814337675434360);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2446487967258621015);
void car_H_mod_fun(double *state, double *out_4385027558944011010);
void car_f_fun(double *state, double dt, double *out_6609873402410428986);
void car_F_fun(double *state, double dt, double *out_6492042525862959454);
void car_h_25(double *state, double *unused, double *out_1305345852000088236);
void car_H_25(double *state, double *unused, double *out_518664266240653830);
void car_h_24(double *state, double *unused, double *out_1085442299742350701);
void car_H_24(double *state, double *unused, double *out_2695878689847803803);
void car_h_30(double *state, double *unused, double *out_2556337624428413416);
void car_H_30(double *state, double *unused, double *out_3036997224747902457);
void car_h_26(double *state, double *unused, double *out_2669569591406911531);
void car_H_26(double *state, double *unused, double *out_3222839052633402394);
void car_h_27(double *state, double *unused, double *out_323261758664790124);
void car_H_27(double *state, double *unused, double *out_6183795375687379279);
void car_h_29(double *state, double *unused, double *out_7558010892089259061);
void car_H_29(double *state, double *unused, double *out_3498800719572562184);
void car_h_28(double *state, double *unused, double *out_5285641756346083356);
void car_H_28(double *state, double *unused, double *out_1535170448007235933);
void car_h_31(double *state, double *unused, double *out_3874303633696752602);
void car_H_31(double *state, double *unused, double *out_3849047154866753870);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}