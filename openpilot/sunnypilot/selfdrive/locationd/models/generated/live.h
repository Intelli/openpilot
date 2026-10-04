#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_8210793990414788398);
void live_err_fun(double *nom_x, double *delta_x, double *out_417811736739863641);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_6625227950584699734);
void live_H_mod_fun(double *state, double *out_4537104792097713627);
void live_f_fun(double *state, double dt, double *out_5832882657935881448);
void live_F_fun(double *state, double dt, double *out_5658816536673986885);
void live_h_4(double *state, double *unused, double *out_1642604332153076098);
void live_H_4(double *state, double *unused, double *out_3321249479197129353);
void live_h_9(double *state, double *unused, double *out_9187919071079287615);
void live_H_9(double *state, double *unused, double *out_3080059832567538708);
void live_h_10(double *state, double *unused, double *out_114157758198215907);
void live_H_10(double *state, double *unused, double *out_6067106692939063389);
void live_h_12(double *state, double *unused, double *out_5887409486457765444);
void live_H_12(double *state, double *unused, double *out_1698206928834832442);
void live_h_35(double *state, double *unused, double *out_4241882921055957840);
void live_H_35(double *state, double *unused, double *out_45412578175478023);
void live_h_32(double *state, double *unused, double *out_1087709522140710339);
void live_H_32(double *state, double *unused, double *out_8645456220170278404);
void live_h_13(double *state, double *unused, double *out_7214866789994028350);
void live_H_13(double *state, double *unused, double *out_6404486945223462255);
void live_h_14(double *state, double *unused, double *out_9187919071079287615);
void live_H_14(double *state, double *unused, double *out_3080059832567538708);
void live_h_33(double *state, double *unused, double *out_2007642600244726303);
void live_H_33(double *state, double *unused, double *out_3195969582814335627);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}