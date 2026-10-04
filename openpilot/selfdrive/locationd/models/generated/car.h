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
void car_err_fun(double *nom_x, double *delta_x, double *out_8960374984193016023);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8607819760565032145);
void car_H_mod_fun(double *state, double *out_6865712900868131600);
void car_f_fun(double *state, double dt, double *out_3046687401328038034);
void car_F_fun(double *state, double dt, double *out_8168474853840000782);
void car_h_25(double *state, double *unused, double *out_3704639410232761343);
void car_H_25(double *state, double *unused, double *out_2387842946929182779);
void car_h_24(double *state, double *unused, double *out_5815696604988810764);
void car_H_24(double *state, double *unused, double *out_215193347923683213);
void car_h_30(double *state, double *unused, double *out_3066195816117589593);
void car_H_30(double *state, double *unused, double *out_4906175905436431406);
void car_h_26(double *state, double *unused, double *out_6584238793325964883);
void car_H_26(double *state, double *unused, double *out_1353660371944873445);
void car_h_27(double *state, double *unused, double *out_2761129557331098908);
void car_H_27(double *state, double *unused, double *out_7129769976620374623);
void car_h_29(double *state, double *unused, double *out_6398579085585121258);
void car_H_29(double *state, double *unused, double *out_5416407249750823590);
void car_h_28(double *state, double *unused, double *out_3364445442007576425);
void car_H_28(double *state, double *unused, double *out_334008232681293016);
void car_h_31(double *state, double *unused, double *out_5188269700685231698);
void car_H_31(double *state, double *unused, double *out_1979868474178224921);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}