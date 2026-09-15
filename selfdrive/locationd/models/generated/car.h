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
void car_err_fun(double *nom_x, double *delta_x, double *out_3439473612777542328);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3047310167658356067);
void car_H_mod_fun(double *state, double *out_3426229254954236394);
void car_f_fun(double *state, double dt, double *out_1603579069930264214);
void car_F_fun(double *state, double dt, double *out_4328042070139184712);
void car_h_25(double *state, double *unused, double *out_1106143716500973221);
void car_H_25(double *state, double *unused, double *out_1279070317676855982);
void car_h_24(double *state, double *unused, double *out_2858376262202982067);
void car_H_24(double *state, double *unused, double *out_7939608569963500409);
void car_h_30(double *state, double *unused, double *out_4743593244754995571);
void car_H_30(double *state, double *unused, double *out_3248626012450752216);
void car_h_26(double *state, double *unused, double *out_8159866534404065587);
void car_H_26(double *state, double *unused, double *out_2462433001197200242);
void car_h_27(double *state, double *unused, double *out_61600084575168516);
void car_H_27(double *state, double *unused, double *out_5423389324251177127);
void car_h_29(double *state, double *unused, double *out_1655448272658853575);
void car_H_29(double *state, double *unused, double *out_2738394668136360032);
void car_h_28(double *state, double *unused, double *out_2874152187845021899);
void car_H_28(double *state, double *unused, double *out_7820793685205890606);
void car_h_31(double *state, double *unused, double *out_1707561874114336775);
void car_H_31(double *state, double *unused, double *out_3088641103430551718);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}