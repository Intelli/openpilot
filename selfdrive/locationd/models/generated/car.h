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
void car_err_fun(double *nom_x, double *delta_x, double *out_8862914790525016689);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_204580419444730517);
void car_H_mod_fun(double *state, double *out_8750329420800131115);
void car_f_fun(double *state, double dt, double *out_5966360353628800727);
void car_F_fun(double *state, double dt, double *out_1075513601505327266);
void car_h_25(double *state, double *unused, double *out_3594241908522391142);
void car_H_25(double *state, double *unused, double *out_6785069540063298953);
void car_h_24(double *state, double *unused, double *out_3431526355112374706);
void car_H_24(double *state, double *unused, double *out_5575500714792780344);
void car_h_30(double *state, double *unused, double *out_43207619731631208);
void car_H_30(double *state, double *unused, double *out_6655730592920058883);
void car_h_26(double *state, double *unused, double *out_8320721113898730898);
void car_H_26(double *state, double *unused, double *out_3043566221189242729);
void car_h_27(double *state, double *unused, double *out_6631027959966723827);
void car_H_27(double *state, double *unused, double *out_4480967281119633972);
void car_h_29(double *state, double *unused, double *out_6355833897682217938);
void car_H_29(double *state, double *unused, double *out_7165961937234451067);
void car_h_28(double *state, double *unused, double *out_6473848877856797226);
void car_H_28(double *state, double *unused, double *out_2083562920164920493);
void car_h_31(double *state, double *unused, double *out_3866316855726497183);
void car_H_31(double *state, double *unused, double *out_6815715501940259381);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}