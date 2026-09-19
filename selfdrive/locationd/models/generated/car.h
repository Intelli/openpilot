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
void car_err_fun(double *nom_x, double *delta_x, double *out_7293025660765852052);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3117228366012468934);
void car_H_mod_fun(double *state, double *out_1447426965170589912);
void car_f_fun(double *state, double dt, double *out_3647186790399289701);
void car_F_fun(double *state, double dt, double *out_4083868303371300049);
void car_h_25(double *state, double *unused, double *out_2804865530302421924);
void car_H_25(double *state, double *unused, double *out_6473911067803269893);
void car_h_24(double *state, double *unused, double *out_3129326117404622252);
void car_H_24(double *state, double *unused, double *out_7886939315841678730);
void car_h_30(double *state, double *unused, double *out_1447972028461291233);
void car_H_30(double *state, double *unused, double *out_1946214737675661695);
void car_h_26(double *state, double *unused, double *out_6449645296122136878);
void car_H_26(double *state, double *unused, double *out_2732407748929213669);
void car_h_27(double *state, double *unused, double *out_3408181414978899441);
void car_H_27(double *state, double *unused, double *out_4169808808859604912);
void car_h_29(double *state, double *unused, double *out_4484758079905623918);
void car_H_29(double *state, double *unused, double *out_2456446081990053879);
void car_h_28(double *state, double *unused, double *out_2464671562077237006);
void car_H_28(double *state, double *unused, double *out_2625952935079476695);
void car_h_31(double *state, double *unused, double *out_7878613286586457251);
void car_H_31(double *state, double *unused, double *out_2106199646695862193);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}