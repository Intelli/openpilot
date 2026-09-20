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
void car_err_fun(double *nom_x, double *delta_x, double *out_1080054032760263743);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_668655428686680811);
void car_H_mod_fun(double *state, double *out_7021396879679134881);
void car_f_fun(double *state, double dt, double *out_5377318552564722043);
void car_F_fun(double *state, double dt, double *out_1196688089252186571);
void car_h_25(double *state, double *unused, double *out_2511128803102887624);
void car_H_25(double *state, double *unused, double *out_6521655368845751895);
void car_h_24(double *state, double *unused, double *out_4108202673726123868);
void car_H_24(double *state, double *unused, double *out_6992112850889090619);
void car_h_30(double *state, double *unused, double *out_5080086584799551990);
void car_H_30(double *state, double *unused, double *out_6650994315988991965);
void car_h_26(double *state, double *unused, double *out_2569258588511782352);
void car_H_26(double *state, double *unused, double *out_8183585385989743497);
void car_h_27(double *state, double *unused, double *out_3861382669613383666);
void car_H_27(double *state, double *unused, double *out_8825757627789416876);
void car_h_29(double *state, double *unused, double *out_4136576731897889555);
void car_H_29(double *state, double *unused, double *out_7907623719050583707);
void car_h_28(double *state, double *unused, double *out_1256977348804686015);
void car_H_28(double *state, double *unused, double *out_8575490083093641658);
void car_h_31(double *state, double *unused, double *out_7295737793888122108);
void car_H_31(double *state, double *unused, double *out_6491009406968791467);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}