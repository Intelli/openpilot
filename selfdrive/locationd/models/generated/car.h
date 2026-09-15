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
void car_err_fun(double *nom_x, double *delta_x, double *out_445019409688598964);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4351151372455830383);
void car_H_mod_fun(double *state, double *out_482292932446809381);
void car_f_fun(double *state, double dt, double *out_3036930739161912371);
void car_F_fun(double *state, double dt, double *out_4607213455717215037);
void car_h_25(double *state, double *unused, double *out_335506616585222898);
void car_H_25(double *state, double *unused, double *out_4005341571092174529);
void car_h_24(double *state, double *unused, double *out_3915395329659002282);
void car_H_24(double *state, double *unused, double *out_447415972289851393);
void car_h_30(double *state, double *unused, double *out_4338044828683651119);
void car_H_30(double *state, double *unused, double *out_1487008612584925902);
void car_h_26(double *state, double *unused, double *out_1764474607049543271);
void car_H_26(double *state, double *unused, double *out_700815601331373928);
void car_h_27(double *state, double *unused, double *out_4666166651075622747);
void car_H_27(double *state, double *unused, double *out_736585458599017315);
void car_h_29(double *state, double *unused, double *out_4941360713360128636);
void car_H_29(double *state, double *unused, double *out_976777268270533718);
void car_h_28(double *state, double *unused, double *out_8778904154973083224);
void car_H_28(double *state, double *unused, double *out_6059176285340064292);
void car_h_31(double *state, double *unused, double *out_1115124776043660269);
void car_H_31(double *state, double *unused, double *out_3071333679419642724);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}