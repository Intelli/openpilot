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
void car_err_fun(double *nom_x, double *delta_x, double *out_7534092571675706452);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4024152262625958442);
void car_H_mod_fun(double *state, double *out_8751041747313336178);
void car_f_fun(double *state, double dt, double *out_1989825484445308883);
void car_F_fun(double *state, double dt, double *out_8882937516093608616);
void car_h_25(double *state, double *unused, double *out_119245575607229953);
void car_H_25(double *state, double *unused, double *out_6499843301606348462);
void car_h_24(double *state, double *unused, double *out_1011930820961359105);
void car_H_24(double *state, double *unused, double *out_6313899731506755166);
void car_h_30(double *state, double *unused, double *out_5794487451063518420);
void car_H_30(double *state, double *unused, double *out_7419204441975594956);
void car_h_26(double *state, double *unused, double *out_6397803335739995937);
void car_H_26(double *state, double *unused, double *out_8205397453229146930);
void car_h_27(double *state, double *unused, double *out_6279795941806619193);
void car_H_27(double *state, double *unused, double *out_5244441130175170045);
void car_h_29(double *state, double *unused, double *out_3670287450639192431);
void car_H_29(double *state, double *unused, double *out_7929435786289987140);
void car_h_28(double *state, double *unused, double *out_1278122674145773548);
void car_H_28(double *state, double *unused, double *out_2847036769220456566);
void car_h_31(double *state, double *unused, double *out_3518203952646792397);
void car_H_31(double *state, double *unused, double *out_7579189350995795454);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}