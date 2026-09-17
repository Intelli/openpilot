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
void car_err_fun(double *nom_x, double *delta_x, double *out_48334252122072856);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7186072161804593480);
void car_H_mod_fun(double *state, double *out_8687679256710143695);
void car_f_fun(double *state, double dt, double *out_5882685055959693267);
void car_F_fun(double *state, double dt, double *out_2681658964555602350);
void car_h_25(double *state, double *unused, double *out_6651581816798785823);
void car_H_25(double *state, double *unused, double *out_5593660983917747187);
void car_h_24(double *state, double *unused, double *out_1538214036161548291);
void car_H_24(double *state, double *unused, double *out_2791584375066039246);
void car_h_30(double *state, double *unused, double *out_63753890322490660);
void car_H_30(double *state, double *unused, double *out_3075328025410498560);
void car_h_26(double *state, double *unused, double *out_5065427157983336305);
void car_H_26(double *state, double *unused, double *out_9111579770917748205);
void car_h_27(double *state, double *unused, double *out_2029395787342677509);
void car_H_27(double *state, double *unused, double *out_5250091337210923471);
void car_h_29(double *state, double *unused, double *out_8654083029546201666);
void car_H_29(double *state, double *unused, double *out_2565096681096106376);
void car_h_28(double *state, double *unused, double *out_3848889700216037579);
void car_H_28(double *state, double *unused, double *out_7647495698165636950);
void car_h_31(double *state, double *unused, double *out_6494395148447656678);
void car_H_31(double *state, double *unused, double *out_8485371668684396729);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}