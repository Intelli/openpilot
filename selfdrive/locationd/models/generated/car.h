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
void car_err_fun(double *nom_x, double *delta_x, double *out_3563114425621724245);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7606356790606784638);
void car_H_mod_fun(double *state, double *out_815759021034898572);
void car_f_fun(double *state, double dt, double *out_4397317462301668753);
void car_F_fun(double *state, double dt, double *out_7256568882913831170);
void car_h_25(double *state, double *unused, double *out_1332281256568723173);
void car_H_25(double *state, double *unused, double *out_4338739671024390249);
void car_h_24(double *state, double *unused, double *out_162131755279869977);
void car_H_24(double *state, double *unused, double *out_6564447455003258811);
void car_h_30(double *state, double *unused, double *out_2305168271685299177);
void car_H_30(double *state, double *unused, double *out_7191314061193544612);
void car_h_26(double *state, double *unused, double *out_1323084178350001065);
void car_H_26(double *state, double *unused, double *out_597236352150334025);
void car_h_27(double *state, double *unused, double *out_3669392011092122472);
void car_H_27(double *state, double *unused, double *out_9080666700715582093);
void car_h_29(double *state, double *unused, double *out_4093873245728549969);
void car_H_29(double *state, double *unused, double *out_6681082716879152428);
void car_h_28(double *state, double *unused, double *out_8735809529810465195);
void car_H_28(double *state, double *unused, double *out_6683262339760868614);
void car_h_31(double *state, double *unused, double *out_1607475318853229062);
void car_H_31(double *state, double *unused, double *out_4369385632901350677);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}