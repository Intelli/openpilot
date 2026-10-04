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
void car_err_fun(double *nom_x, double *delta_x, double *out_2543343838934147);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5525400379837697642);
void car_H_mod_fun(double *state, double *out_5947912966739432546);
void car_f_fun(double *state, double dt, double *out_5736328484507014804);
void car_F_fun(double *state, double dt, double *out_2989934352022285926);
void car_h_25(double *state, double *unused, double *out_4810667785250124972);
void car_H_25(double *state, double *unused, double *out_3245275259172804691);
void car_h_24(double *state, double *unused, double *out_6117394571812982197);
void car_H_24(double *state, double *unused, double *out_5417924858178304257);
void car_h_30(double *state, double *unused, double *out_4535473722965619083);
void car_H_30(double *state, double *unused, double *out_7772971589300412889);
void car_h_26(double *state, double *unused, double *out_1931068402156921432);
void car_H_26(double *state, double *unused, double *out_6986778578046860915);
void car_h_27(double *state, double *unused, double *out_3330739680675778012);
void car_H_27(double *state, double *unused, double *out_5549377518116469672);
void car_h_29(double *state, double *unused, double *out_530943795752723640);
void car_H_29(double *state, double *unused, double *out_7262740244986020705);
void car_h_28(double *state, double *unused, double *out_5150861753475309890);
void car_H_28(double *state, double *unused, double *out_5299109973420694454);
void car_h_31(double *state, double *unused, double *out_3829209691468416912);
void car_H_31(double *state, double *unused, double *out_3214629297295844263);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}