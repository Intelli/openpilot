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
void car_err_fun(double *nom_x, double *delta_x, double *out_6895673119224316411);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5311767461984458348);
void car_H_mod_fun(double *state, double *out_1742728562901466536);
void car_f_fun(double *state, double dt, double *out_6526476796425115344);
void car_F_fun(double *state, double dt, double *out_6139522197160662754);
void car_h_25(double *state, double *unused, double *out_4367531777895338643);
void car_H_25(double *state, double *unused, double *out_793607640872984327);
void car_h_24(double *state, double *unused, double *out_348485520041217042);
void car_H_24(double *state, double *unused, double *out_1264065122916323051);
void car_h_30(double *state, double *unused, double *out_4210345109544209498);
void car_H_30(double *state, double *unused, double *out_922946588016224397);
void car_h_26(double *state, double *unused, double *out_5153854962445871933);
void car_H_26(double *state, double *unused, double *out_4535110959747040551);
void car_h_27(double *state, double *unused, double *out_1330745726451005958);
void car_H_27(double *state, double *unused, double *out_3097709899816649308);
void car_h_29(double *state, double *unused, double *out_5440089499899344978);
void car_H_29(double *state, double *unused, double *out_4811072626686200341);
void car_h_28(double *state, double *unused, double *out_6332418994111851603);
void car_H_28(double *state, double *unused, double *out_2847442355120874090);
void car_h_31(double *state, double *unused, double *out_2220296148580956520);
void car_H_31(double *state, double *unused, double *out_762961678996023899);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}