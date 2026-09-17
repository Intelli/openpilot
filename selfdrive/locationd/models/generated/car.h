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
void car_err_fun(double *nom_x, double *delta_x, double *out_269603389839755742);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_592438703867529051);
void car_H_mod_fun(double *state, double *out_2647141062540633245);
void car_f_fun(double *state, double dt, double *out_6099382505660640035);
void car_F_fun(double *state, double dt, double *out_6313816615875393456);
void car_h_25(double *state, double *unused, double *out_5356303473462709754);
void car_H_25(double *state, double *unused, double *out_3849881897349396706);
void car_h_24(double *state, double *unused, double *out_1055368816343579033);
void car_H_24(double *state, double *unused, double *out_8718696762377103558);
void car_h_30(double *state, double *unused, double *out_1414531752887641182);
void car_H_30(double *state, double *unused, double *out_8377578227477004904);
void car_h_26(double *state, double *unused, double *out_6416205020548486827);
void car_H_26(double *state, double *unused, double *out_7591385216223452930);
void car_h_27(double *state, double *unused, double *out_7672649654478288824);
void car_H_27(double *state, double *unused, double *out_6153984156293061687);
void car_h_29(double *state, double *unused, double *out_811215868211163665);
void car_H_29(double *state, double *unused, double *out_7867346883162612720);
void car_h_28(double *state, double *unused, double *out_5016109505237524836);
void car_H_28(double *state, double *unused, double *out_5496998173477408322);
void car_h_31(double *state, double *unused, double *out_5327175343426169421);
void car_H_31(double *state, double *unused, double *out_8217593318456804406);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}