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
void car_err_fun(double *nom_x, double *delta_x, double *out_113716983378204622);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3175147354684049495);
void car_H_mod_fun(double *state, double *out_5065659025262341849);
void car_f_fun(double *state, double dt, double *out_8000933351783123572);
void car_F_fun(double *state, double dt, double *out_409468777326581195);
void car_h_25(double *state, double *unused, double *out_3884977761234258648);
void car_H_25(double *state, double *unused, double *out_5570993467462638561);
void car_h_24(double *state, double *unused, double *out_3737140147320417057);
void car_H_24(double *state, double *unused, double *out_6300178799655394954);
void car_h_30(double *state, double *unused, double *out_4160171823518764537);
void car_H_30(double *state, double *unused, double *out_5959060264755296300);
void car_h_26(double *state, double *unused, double *out_1718113664039950551);
void car_H_26(double *state, double *unused, double *out_1829490148588582337);
void car_h_27(double *state, double *unused, double *out_8886651028895104293);
void car_H_27(double *state, double *unused, double *out_8133823576555721211);
void car_h_29(double *state, double *unused, double *out_1347619720248911154);
void car_H_29(double *state, double *unused, double *out_5448828920440904116);
void car_h_28(double *state, double *unused, double *out_2108122273276517816);
void car_H_28(double *state, double *unused, double *out_7915516136199116926);
void car_h_31(double *state, double *unused, double *out_247528232980236298);
void car_H_31(double *state, double *unused, double *out_5601639429339598989);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}