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
void car_err_fun(double *nom_x, double *delta_x, double *out_4669638409443648641);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8859452741513286810);
void car_H_mod_fun(double *state, double *out_6131259255263184331);
void car_f_fun(double *state, double dt, double *out_9114301376252007925);
void car_F_fun(double *state, double dt, double *out_3297863687905255883);
void car_h_25(double *state, double *unused, double *out_7473609193578118278);
void car_H_25(double *state, double *unused, double *out_8792436179801002137);
void car_h_24(double *state, double *unused, double *out_3860824270109750960);
void car_H_24(double *state, double *unused, double *out_6619786580795502571);
void car_h_30(double *state, double *unused, double *out_7619129017798773249);
void car_H_30(double *state, double *unused, double *out_7135974935401300852);
void car_h_26(double *state, double *unused, double *out_8562638870700435684);
void car_H_26(double *state, double *unused, double *out_5050932860926945913);
void car_h_27(double *state, double *unused, double *out_5971461612470587693);
void car_H_27(double *state, double *unused, double *out_4912380864217357635);
void car_h_29(double *state, double *unused, double *out_183985583370072436);
void car_H_29(double *state, double *unused, double *out_6625743591086908668);
void car_h_28(double *state, double *unused, double *out_5368145727794110176);
void car_H_28(double *state, double *unused, double *out_6738601465553112374);
void car_h_31(double *state, double *unused, double *out_3836159665324095928);
void car_H_31(double *state, double *unused, double *out_8823082141677962565);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}