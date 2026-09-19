#include <math.h>
#include "acados_solver_ev9_path.h"
#include "acados/utils/types.h"

// Version 4 bounds SQP work; MAXITER still returns initialized states/controls.
int ev9_path_abi_version(void) { return EV9_PATH_N == 30 ? 4 : 0; }

void *ev9_path_create(void) {
  ev9_path_solver_capsule *capsule = ev9_path_acados_create_capsule();
  if (!capsule) return NULL;
  if (ev9_path_acados_create(capsule)) {
    ev9_path_acados_free_capsule(capsule);
    return NULL;
  }
  return capsule;
}

void ev9_path_destroy(void *pointer) {
  if (!pointer) return;
  ev9_path_acados_free(pointer);
  ev9_path_acados_free_capsule(pointer);
}

// Each node: reference x/y/yaw/k; limits lateral-low/high, yaw-deviation, k-upper, |dk/ds|, preserve-pose, k-lower.
int ev9_path_solve(void *pointer, double length, const double *reference, const double *limits,
                   const double *initial, double *states, double *rates) {
  ev9_path_solver_capsule *capsule = pointer;
  ocp_nlp_config *config = ev9_path_acados_get_nlp_config(capsule);
  ocp_nlp_dims *dims = ev9_path_acados_get_nlp_dims(capsule);
  ocp_nlp_in *input = ev9_path_acados_get_nlp_in(capsule);
  ocp_nlp_out *output = ev9_path_acados_get_nlp_out(capsule);
  ev9_path_acados_reset(capsule, 1);
  for (int i = 0; i <= EV9_PATH_N; i++) {
    const double *r = reference + 4*i;
    const double *b = limits + 7*i;
    double p[4] = {length, r[0], r[1], r[2]};
    double seed[4] = {r[0], r[1], r[2], fmax(b[6], fmin(b[3], r[3]))};
    double target[6] = {r[0], r[1], r[2], r[3], 0., 1.};
    ev9_path_acados_update_params(capsule, i, p, 4);
    ocp_nlp_out_set(config, dims, output, i, "x", seed);
    ocp_nlp_cost_model_set(config, dims, input, i, "yref", target);
    ocp_nlp_constraints_model_set(config, dims, input, i, "lh", (void *)(b));
    ocp_nlp_constraints_model_set(config, dims, input, i, "uh", (void *)(b+1));
    if (i == 0) {
      ocp_nlp_constraints_model_set(config, dims, input, i, "lbx", (void *)initial);
      ocp_nlp_constraints_model_set(config, dims, input, i, "ubx", (void *)initial);
    } else {
      // A forecast may end inside the turn. Its last pose is a cost target,
      // subject to the same path, heading and physical limits as other nodes.
      // Hard terminal pose matching can contradict the 140-degree capability.
      double low[4] = {-1e6, -1e6, r[2]-b[2], b[6]}, high[4] = {1e6, 1e6, r[2]+b[2], b[3]};
      if (b[5]) {
        for (int j = 0; j < 3; j++) low[j] = high[j] = r[j];
      }
      ocp_nlp_constraints_model_set(config, dims, input, i, "lbx", low);
      ocp_nlp_constraints_model_set(config, dims, input, i, "ubx", high);
    }
    if (i < EV9_PATH_N) {
      double zero[2] = {0., 1.}, low[2] = {-b[4], .7}, high[2] = {b[4], 1.3};
      ocp_nlp_out_set(config, dims, output, i, "u", &zero);
      ocp_nlp_constraints_model_set(config, dims, input, i, "lbu", &low);
      ocp_nlp_constraints_model_set(config, dims, input, i, "ubu", &high);
    }
  }
  int status = ev9_path_acados_solve(capsule);
  if (status != ACADOS_SUCCESS && status != ACADOS_MAXITER) return status;
  for (int i = 0; i <= EV9_PATH_N; i++) {
    ocp_nlp_out_get(config, dims, output, i, "x", states + 4*i);
    if (i < EV9_PATH_N) ocp_nlp_out_get(config, dims, output, i, "u", rates+2*i);
  }
  return status;
}
