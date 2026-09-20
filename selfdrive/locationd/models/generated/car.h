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
void car_err_fun(double *nom_x, double *delta_x, double *out_905618509759065814);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1454872133267434449);
void car_H_mod_fun(double *state, double *out_7905035211705523546);
void car_f_fun(double *state, double dt, double *out_5670425325742993501);
void car_F_fun(double *state, double dt, double *out_4094785554680913164);
void car_h_25(double *state, double *unused, double *out_6142268501048737737);
void car_H_25(double *state, double *unused, double *out_4382054561716031869);
void car_h_24(double *state, double *unused, double *out_5336528544796446006);
void car_H_24(double *state, double *unused, double *out_9128563888682540903);
void car_h_30(double *state, double *unused, double *out_2504818972794715387);
void car_H_30(double *state, double *unused, double *out_8909750891843640067);
void car_h_26(double *state, double *unused, double *out_8383104460353430475);
void car_H_26(double *state, double *unused, double *out_8123557880590088093);
void car_h_27(double *state, double *unused, double *out_5160184407713439625);
void car_H_27(double *state, double *unused, double *out_6686156820659696850);
void car_h_29(double *state, double *unused, double *out_2496854294866130258);
void car_H_29(double *state, double *unused, double *out_8399519547529247883);
void car_h_28(double *state, double *unused, double *out_158511140052593980);
void car_H_28(double *state, double *unused, double *out_6435889275963921632);
void car_h_31(double *state, double *unused, double *out_2622826366728092131);
void car_H_31(double *state, double *unused, double *out_4351408599839071441);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}