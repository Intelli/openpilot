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
void car_err_fun(double *nom_x, double *delta_x, double *out_1686743815755470891);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5796375691414819628);
void car_H_mod_fun(double *state, double *out_4674715865062386802);
void car_f_fun(double *state, double dt, double *out_3238688793521924659);
void car_F_fun(double *state, double dt, double *out_8963722065079328777);
void car_h_25(double *state, double *unused, double *out_5916962928910388641);
void car_H_25(double *state, double *unused, double *out_3799407120723383822);
void car_h_24(double *state, double *unused, double *out_9215616507509494571);
void car_H_24(double *state, double *unused, double *out_4639838904905428814);
void car_h_30(double *state, double *unused, double *out_5641768866625882752);
void car_H_30(double *state, double *unused, double *out_1281074162216135195);
void car_h_26(double *state, double *unused, double *out_757272650787966394);
void car_H_26(double *state, double *unused, double *out_494881150962583221);
void car_h_27(double *state, double *unused, double *out_274233057829431806);
void car_H_27(double *state, double *unused, double *out_3455837474016560106);
void car_h_29(double *state, double *unused, double *out_961004455074083);
void car_H_29(double *state, double *unused, double *out_770842817901743011);
void car_h_28(double *state, double *unused, double *out_6257156897135573559);
void car_H_28(double *state, double *unused, double *out_5853241834971273585);
void car_h_31(double *state, double *unused, double *out_3220754355773462541);
void car_H_31(double *state, double *unused, double *out_1121089253195934697);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}