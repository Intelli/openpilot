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
void car_err_fun(double *nom_x, double *delta_x, double *out_2236917899360960475);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2708070960366344927);
void car_H_mod_fun(double *state, double *out_6800576499473052122);
void car_f_fun(double *state, double dt, double *out_6732064645415141134);
void car_F_fun(double *state, double dt, double *out_561713757681768772);
void car_h_25(double *state, double *unused, double *out_1362906194470842416);
void car_H_25(double *state, double *unused, double *out_8123186924247007817);
void car_h_24(double *state, double *unused, double *out_8482783219785419481);
void car_H_24(double *state, double *unused, double *out_4565261325444684681);
void car_h_30(double *state, double *unused, double *out_1520092862821971561);
void car_H_30(double *state, double *unused, double *out_8252525871390247887);
void car_h_26(double *state, double *unused, double *out_1292459240447881822);
void car_H_26(double *state, double *unused, double *out_6582053830588487575);
void car_h_27(double *state, double *unused, double *out_759590309794364899);
void car_H_27(double *state, double *unused, double *out_8019454890518878818);
void car_h_29(double *state, double *unused, double *out_3481580404838874084);
void car_H_29(double *state, double *unused, double *out_7742294527075855703);
void car_h_28(double *state, double *unused, double *out_8705184591908345952);
void car_H_28(double *state, double *unused, double *out_5778664255510529452);
void car_h_31(double *state, double *unused, double *out_6097652569778045909);
void car_H_31(double *state, double *unused, double *out_8092540962370047389);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}