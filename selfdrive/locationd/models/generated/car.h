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
void car_err_fun(double *nom_x, double *delta_x, double *out_1436388919194520933);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1865692594489150733);
void car_H_mod_fun(double *state, double *out_2018588707815567135);
void car_f_fun(double *state, double dt, double *out_4398355278429487138);
void car_F_fun(double *state, double dt, double *out_1417418255089739393);
void car_h_25(double *state, double *unused, double *out_3948781947240439381);
void car_H_25(double *state, double *unused, double *out_7174599518096670102);
void car_h_24(double *state, double *unused, double *out_7923150373677837021);
void car_H_24(double *state, double *unused, double *out_9099494956607381948);
void car_h_30(double *state, double *unused, double *out_87098470811937729);
void car_H_30(double *state, double *unused, double *out_257909176605053347);
void car_h_26(double *state, double *unused, double *out_4709284500268046043);
void car_H_26(double *state, double *unused, double *out_7530641236738825290);
void car_h_27(double *state, double *unused, double *out_5372776159007469578);
void car_H_27(double *state, double *unused, double *out_2432672488405478258);
void car_h_29(double *state, double *unused, double *out_4914574796848907916);
void car_H_29(double *state, double *unused, double *out_4146035215275029291);
void car_h_28(double *state, double *unused, double *out_5976092043683947095);
void car_H_28(double *state, double *unused, double *out_9218309841364991751);
void car_h_31(double *state, double *unused, double *out_8134368148167296374);
void car_H_31(double *state, double *unused, double *out_7143953556219709674);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}