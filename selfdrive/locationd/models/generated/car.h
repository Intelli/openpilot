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
void car_err_fun(double *nom_x, double *delta_x, double *out_2579147921043217820);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4595464121730668566);
void car_H_mod_fun(double *state, double *out_4312954293014229808);
void car_f_fun(double *state, double dt, double *out_3633989389734511779);
void car_F_fun(double *state, double dt, double *out_3520723824960767419);
void car_h_25(double *state, double *unused, double *out_4250949531156864346);
void car_H_25(double *state, double *unused, double *out_6460113230291610220);
void car_h_24(double *state, double *unused, double *out_5654665218976778104);
void car_H_24(double *state, double *unused, double *out_2767951955777585005);
void car_h_30(double *state, double *unused, double *out_8881186493863702063);
void car_H_30(double *state, double *unused, double *out_7458934513290333198);
void car_h_26(double *state, double *unused, double *out_3922827708764892718);
void car_H_26(double *state, double *unused, double *out_8245127524543885172);
void car_h_27(double *state, double *unused, double *out_8093275106819492880);
void car_H_27(double *state, double *unused, double *out_8764215489235275201);
void car_h_29(double *state, double *unused, double *out_3582633740539707800);
void car_H_29(double *state, double *unused, double *out_7969165857604725382);
void car_h_28(double *state, double *unused, double *out_1947812147245832083);
void car_H_28(double *state, double *unused, double *out_2886766840535194808);
void car_h_31(double *state, double *unused, double *out_5331683117659666084);
void car_H_31(double *state, double *unused, double *out_7618919422310533696);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}