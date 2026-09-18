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
void car_err_fun(double *nom_x, double *delta_x, double *out_592952605244645271);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6836454440679390003);
void car_H_mod_fun(double *state, double *out_6286510676597888168);
void car_f_fun(double *state, double dt, double *out_5881410695804520477);
void car_F_fun(double *state, double dt, double *out_5545553878115808684);
void car_h_25(double *state, double *unused, double *out_3412183612969937421);
void car_H_25(double *state, double *unused, double *out_5520062914515680919);
void car_h_24(double *state, double *unused, double *out_4072870949177330157);
void car_H_24(double *state, double *unused, double *out_680969765335480507);
void car_h_30(double *state, double *unused, double *out_2537864572703668366);
void car_H_30(double *state, double *unused, double *out_992366584388072721);
void car_h_26(double *state, double *unused, double *out_3897492103713038194);
void car_H_26(double *state, double *unused, double *out_1778559595641624695);
void car_h_27(double *state, double *unused, double *out_4015499497646414938);
void car_H_27(double *state, double *unused, double *out_3215960655572015938);
void car_h_29(double *state, double *unused, double *out_82803800632956926);
void car_H_29(double *state, double *unused, double *out_1502597928702464905);
void car_h_28(double *state, double *unused, double *out_4997583590981713050);
void car_H_28(double *state, double *unused, double *out_3466228200267791156);
void car_h_31(double *state, double *unused, double *out_7271295203918941754);
void car_H_31(double *state, double *unused, double *out_1152351493408273219);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}