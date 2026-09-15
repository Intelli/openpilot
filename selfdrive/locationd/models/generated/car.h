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
void car_err_fun(double *nom_x, double *delta_x, double *out_4522650774883987719);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6421097817923825041);
void car_H_mod_fun(double *state, double *out_8354098732435681401);
void car_f_fun(double *state, double dt, double *out_618802638011462566);
void car_F_fun(double *state, double dt, double *out_3307921169342290232);
void car_h_25(double *state, double *unused, double *out_2859996149114624228);
void car_H_25(double *state, double *unused, double *out_3450406907251016561);
void car_h_24(double *state, double *unused, double *out_164729919387917572);
void car_H_24(double *state, double *unused, double *out_4396947103623005501);
void car_h_30(double *state, double *unused, double *out_3053736877556124145);
void car_H_30(double *state, double *unused, double *out_7978103237378624759);
void car_h_26(double *state, double *unused, double *out_3657052762232601662);
void car_H_26(double *state, double *unused, double *out_7191910226125072785);
void car_h_27(double *state, double *unused, double *out_7861669416775469873);
void car_H_27(double *state, double *unused, double *out_8293877524530501946);
void car_h_29(double *state, double *unused, double *out_3997246730457786580);
void car_H_29(double *state, double *unused, double *out_7467871893064232575);
void car_h_28(double *state, double *unused, double *out_858906712982404094);
void car_H_28(double *state, double *unused, double *out_5504241621498906324);
void car_h_31(double *state, double *unused, double *out_5310946536877911850);
void car_H_31(double *state, double *unused, double *out_7818118328358424261);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}