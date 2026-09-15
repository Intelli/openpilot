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
void car_err_fun(double *nom_x, double *delta_x, double *out_5685634975312251926);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1653700651811135323);
void car_H_mod_fun(double *state, double *out_305387614319530969);
void car_f_fun(double *state, double dt, double *out_6390856393928483226);
void car_F_fun(double *state, double dt, double *out_4160115342344962750);
void car_h_25(double *state, double *unused, double *out_7280288212044461368);
void car_H_25(double *state, double *unused, double *out_3217661024325834179);
void car_h_24(double *state, double *unused, double *out_886623552878830077);
void car_H_24(double *state, double *unused, double *out_340264574476488957);
void car_h_30(double *state, double *unused, double *out_916694233742645507);
void car_H_30(double *state, double *unused, double *out_3699029317165782576);
void car_h_26(double *state, double *unused, double *out_6061584296858293044);
void car_H_26(double *state, double *unused, double *out_86864945434966422);
void car_h_27(double *state, double *unused, double *out_4163693157872024469);
void car_H_27(double *state, double *unused, double *out_1524266005365357665);
void car_h_29(double *state, double *unused, double *out_6401778265083477962);
void car_H_29(double *state, double *unused, double *out_4209260661480174760);
void car_h_28(double *state, double *unused, double *out_9165366425532870114);
void car_H_28(double *state, double *unused, double *out_873138355589355814);
void car_h_31(double *state, double *unused, double *out_7123101543693332223);
void car_H_31(double *state, double *unused, double *out_3859014226185983074);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}