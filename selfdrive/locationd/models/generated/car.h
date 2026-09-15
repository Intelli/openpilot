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
void car_err_fun(double *nom_x, double *delta_x, double *out_8886897714237588908);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5733609041839026521);
void car_H_mod_fun(double *state, double *out_3923317096320654469);
void car_f_fun(double *state, double dt, double *out_669091944002017197);
void car_F_fun(double *state, double dt, double *out_5797115532516380903);
void car_h_25(double *state, double *unused, double *out_5196413492935956300);
void car_H_25(double *state, double *unused, double *out_7446297746310146146);
void car_h_24(double *state, double *unused, double *out_3869112794879626945);
void car_H_24(double *state, double *unused, double *out_3463974594912378248);
void car_h_30(double *state, double *unused, double *out_6430828419944818181);
void car_H_30(double *state, double *unused, double *out_4083755985907788715);
void car_h_26(double *state, double *unused, double *out_6257930739770995479);
void car_H_26(double *state, double *unused, double *out_3704794427436089922);
void car_h_27(double *state, double *unused, double *out_4844673761129368663);
void car_H_27(double *state, double *unused, double *out_6258519297708213626);
void car_h_29(double *state, double *unused, double *out_2752985765080374306);
void car_H_29(double *state, double *unused, double *out_3573524641593396531);
void car_h_28(double *state, double *unused, double *out_3901163908227706228);
void car_H_28(double *state, double *unused, double *out_8655923658662927105);
void car_h_31(double *state, double *unused, double *out_3794449034785499332);
void car_H_31(double *state, double *unused, double *out_7476943708187106574);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}