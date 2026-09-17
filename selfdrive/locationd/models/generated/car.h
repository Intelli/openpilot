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
void car_err_fun(double *nom_x, double *delta_x, double *out_1312431228385794227);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1436856768403750846);
void car_H_mod_fun(double *state, double *out_7131425478870869743);
void car_f_fun(double *state, double dt, double *out_998549237639831428);
void car_F_fun(double *state, double dt, double *out_8057735163102707176);
void car_h_25(double *state, double *unused, double *out_3026651365419480074);
void car_H_25(double *state, double *unused, double *out_2227733653686204903);
void car_h_24(double *state, double *unused, double *out_638459334598805920);
void car_H_24(double *state, double *unused, double *out_8354954155847887100);
void car_h_30(double *state, double *unused, double *out_1646900079849393943);
void car_H_30(double *state, double *unused, double *out_290599304821043724);
void car_h_26(double *state, double *unused, double *out_3504367418824073069);
void car_H_26(double *state, double *unused, double *out_5969236972560261127);
void car_h_27(double *state, double *unused, double *out_318741817170792906);
void car_H_27(double *state, double *unused, double *out_1884164006979381187);
void car_h_29(double *state, double *unused, double *out_2250215964525871460);
void car_H_29(double *state, double *unused, double *out_800830649135435908);
void car_h_28(double *state, double *unused, double *out_284574067505684611);
void car_H_28(double *state, double *unused, double *out_4281568367934094666);
void car_h_31(double *state, double *unused, double *out_9182098561260140203);
void car_H_31(double *state, double *unused, double *out_6595445074793612603);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}