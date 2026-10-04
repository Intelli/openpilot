#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4256674648376746002);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6072215117786325780);
void pose_H_mod_fun(double *state, double *out_8723676235799255586);
void pose_f_fun(double *state, double dt, double *out_8216474693621741347);
void pose_F_fun(double *state, double dt, double *out_9150197466179512248);
void pose_h_4(double *state, double *unused, double *out_6828733239090926752);
void pose_H_4(double *state, double *unused, double *out_5380831403152443183);
void pose_h_10(double *state, double *unused, double *out_2858686616301996276);
void pose_H_10(double *state, double *unused, double *out_6143684893144312761);
void pose_h_13(double *state, double *unused, double *out_5884763655197767271);
void pose_H_13(double *state, double *unused, double *out_2168557577820110382);
void pose_h_14(double *state, double *unused, double *out_5945367881582987740);
void pose_H_14(double *state, double *unused, double *out_1417590546812958654);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}