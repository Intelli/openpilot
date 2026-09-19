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
void car_err_fun(double *nom_x, double *delta_x, double *out_1685137447773454281);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7632548252191174279);
void car_H_mod_fun(double *state, double *out_528146882961143348);
void car_f_fun(double *state, double dt, double *out_508312864269159076);
void car_F_fun(double *state, double dt, double *out_1840474173639359999);
void car_h_25(double *state, double *unused, double *out_4145230403640242229);
void car_H_25(double *state, double *unused, double *out_8725408964836171031);
void car_h_24(double *state, double *unused, double *out_8922953874602113358);
void car_H_24(double *state, double *unused, double *out_3909949477850603620);
void car_h_30(double *state, double *unused, double *out_3870036341355736340);
void car_H_30(double *state, double *unused, double *out_4197712634708562833);
void car_h_26(double *state, double *unused, double *out_2112887497950405413);
void car_H_26(double *state, double *unused, double *out_4983905645962114807);
void car_h_27(double *state, double *unused, double *out_5895856850425082734);
void car_H_27(double *state, double *unused, double *out_6421306705892506050);
void car_h_29(double *state, double *unused, double *out_3804168854376088377);
void car_H_29(double *state, double *unused, double *out_4707943979022955017);
void car_h_28(double *state, double *unused, double *out_503184666988766412);
void car_H_28(double *state, double *unused, double *out_6671574250588281268);
void car_h_31(double *state, double *unused, double *out_2743265945489785261);
void car_H_31(double *state, double *unused, double *out_8756054926713131459);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}