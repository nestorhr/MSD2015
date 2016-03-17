/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Demo1_sfun.h"
#include "c2_Demo1.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Demo1_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[11] = { "ports", "ids", "dist", "id",
  "nargin", "nargout", "r1", "r2", "r3", "r4", "s" };

/* Function Declarations */
static void initialize_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance);
static void initialize_params_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance);
static void enable_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance);
static void disable_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_Demo1(SFc2_Demo1InstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_Demo1(SFc2_Demo1InstanceStruct
  *chartInstance);
static void set_sim_state_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance);
static void sf_gateway_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance);
static void mdl_start_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance);
static void initSimStructsc2_Demo1(SFc2_Demo1InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_b_r4, const char_T *c2_identifier);
static real_T c2_b_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y[2]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_d_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y[6]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u);
static boolean_T c2_e_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_isempty, const char_T *c2_identifier);
static boolean_T c2_f_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_g_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_GetMC, const char_T *c2_identifier, real_T c2_y[4]);
static void c2_h_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4]);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_i_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_j_emlrt_marshallIn(SFc2_Demo1InstanceStruct
  *chartInstance, const mxArray *c2_b_s, const char_T *c2_identifier);
static const mxArray *c2_k_emlrt_marshallIn(SFc2_Demo1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static uint8_T c2_l_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_Demo1, const char_T *c2_identifier);
static uint8_T c2_m_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_Demo1InstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_Demo1InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_s = NULL;
  chartInstance->c2_s_not_empty = false;
  chartInstance->c2_is_active_c2_Demo1 = 0U;
}

static void initialize_params_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_Demo1(SFc2_Demo1InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_Demo1(SFc2_Demo1InstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T c2_c_hoistedGlobal;
  real_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real_T c2_d_hoistedGlobal;
  real_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  const mxArray *c2_e_u;
  const mxArray *c2_f_y = NULL;
  uint8_T c2_e_hoistedGlobal;
  uint8_T c2_f_u;
  const mxArray *c2_g_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(6, 1), false);
  c2_hoistedGlobal = *chartInstance->c2_r1;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = *chartInstance->c2_r2;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_c_hoistedGlobal = *chartInstance->c2_r3;
  c2_c_u = c2_c_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_d_hoistedGlobal = *chartInstance->c2_r4;
  c2_d_u = c2_d_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_e_u = sf_mex_dup(chartInstance->c2_s);
  c2_f_y = NULL;
  if (!chartInstance->c2_s_not_empty) {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_f_y, sf_mex_duplicatearraysafe(&c2_e_u), false);
  }

  sf_mex_destroy(&c2_e_u);
  sf_mex_setcell(c2_y, 4, c2_f_y);
  c2_e_hoistedGlobal = chartInstance->c2_is_active_c2_Demo1;
  c2_f_u = c2_e_hoistedGlobal;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 5, c2_g_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  *chartInstance->c2_r1 = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 0)), "r1");
  *chartInstance->c2_r2 = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 1)), "r2");
  *chartInstance->c2_r3 = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 2)), "r3");
  *chartInstance->c2_r4 = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 3)), "r4");
  sf_mex_assign(&chartInstance->c2_s, c2_j_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 4)), "s"), true);
  chartInstance->c2_is_active_c2_Demo1 = c2_l_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 5)), "is_active_c2_Demo1");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_Demo1(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c2_s);
}

static void sf_gateway_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_id;
  uint32_T c2_debug_family_var_map[11];
  const mxArray *c2_ports = NULL;
  char_T c2_ids[6];
  real_T c2_dist[4];
  char_T c2_c_id[2];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 4.0;
  real_T c2_b_r1;
  real_T c2_b_r2;
  real_T c2_b_r3;
  real_T c2_b_r4;
  int32_T c2_i0;
  static char_T c2_cv0[5] = { 'C', 'O', 'M', '3', '3' };

  char_T c2_u[5];
  const mxArray *c2_y = NULL;
  int32_T c2_i1;
  static char_T c2_cv1[8] = { 'B', 'a', 'u', 'd', 'R', 'a', 't', 'e' };

  char_T c2_b_u[8];
  const mxArray *c2_b_y = NULL;
  real_T c2_c_u;
  const mxArray *c2_c_y = NULL;
  int32_T c2_i2;
  static char_T c2_cv2[6] = { 'P', 'a', 'r', 'i', 't', 'y' };

  char_T c2_d_u[6];
  const mxArray *c2_d_y = NULL;
  int32_T c2_i3;
  static char_T c2_cv3[4] = { 'N', 'o', 'n', 'e' };

  char_T c2_e_u[4];
  const mxArray *c2_e_y = NULL;
  int32_T c2_i4;
  static char_T c2_cv4[6] = { 'm', 'm', 'm', 'c', 'r', 'a' };

  int32_T c2_d_id;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  char_T c2_f_u[2];
  const mxArray *c2_f_y = NULL;
  real_T c2_dv0[4];
  int32_T c2_i8;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_id, 0U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_id;
  c2_b_id = c2_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 11U, 12U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_ports, 0U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_ids, 1U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dist, 2U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_c_id, MAX_uint32_T,
    c2_c_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 4U, c2_b_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 5U, c2_b_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_id, 3U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_r1, 6U, c2_b_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_r2, 7U, c2_b_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_r3, 8U, c2_b_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_r4, 9U, c2_b_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&chartInstance->c2_s, 10U, c2_sf_marshallOut);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_b_r1 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_b_r2 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_b_r3 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_b_r4 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 17);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_s_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
    sf_mex_assign(&c2_ports, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
      "instrfind", 1U, 0U), false);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
    if (CV_EML_IF(0, 1, 1, CV_EML_MCDC(0, 1, 0, !CV_EML_COND(0, 1, 0,
           c2_e_emlrt_marshallIn(chartInstance, sf_mex_call_debug
            (sfGlobalDebugInstanceStruct, "isempty", 1U, 1U, 14, sf_mex_dup
             (c2_ports)), "isempty"))))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "fclose", 0U, 1U, 14,
                        sf_mex_dup(c2_ports));
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "delete", 0U, 1U, 14,
                        sf_mex_dup(c2_ports));
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
    for (c2_i0 = 0; c2_i0 < 5; c2_i0++) {
      c2_u[c2_i0] = c2_cv0[c2_i0];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 5),
                  false);
    for (c2_i1 = 0; c2_i1 < 8; c2_i1++) {
      c2_b_u[c2_i1] = c2_cv1[c2_i1];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 8),
                  false);
    c2_c_u = 9600.0;
    c2_c_y = NULL;
    sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), false);
    for (c2_i2 = 0; c2_i2 < 6; c2_i2++) {
      c2_d_u[c2_i2] = c2_cv2[c2_i2];
    }

    c2_d_y = NULL;
    sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_d_u, 10, 0U, 1U, 0U, 2, 1, 6),
                  false);
    for (c2_i3 = 0; c2_i3 < 4; c2_i3++) {
      c2_e_u[c2_i3] = c2_cv3[c2_i3];
    }

    c2_e_y = NULL;
    sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 10, 0U, 1U, 0U, 2, 1, 4),
                  false);
    sf_mex_assign(&chartInstance->c2_s, sf_mex_call_debug
                  (sfGlobalDebugInstanceStruct, "serial", 1U, 5U, 14, c2_y, 14,
                   c2_b_y, 14, c2_c_y, 14, c2_d_y, 14, c2_e_y), true);
    chartInstance->c2_s_not_empty = true;
    chartInstance->c2_s_not_empty = !c2_e_emlrt_marshallIn(chartInstance,
      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "isempty", 1U, 1U, 14,
                        sf_mex_dup(chartInstance->c2_s)), "isempty");
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "fopen", 0U, 1U, 14,
                      sf_mex_dup(chartInstance->c2_s));
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "fscanf", 0U, 1U, 14,
                      sf_mex_dup(chartInstance->c2_s));
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  for (c2_i4 = 0; c2_i4 < 6; c2_i4++) {
    c2_ids[c2_i4] = c2_cv4[c2_i4];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
  c2_d_id = _SFD_EML_ARRAY_BOUNDS_CHECK("ids", (int32_T)_SFD_INTEGER_CHECK("id",
    c2_b_id), 1, 3, 1, 0) - 1;
  for (c2_i5 = 0; c2_i5 < 2; c2_i5++) {
    c2_c_id[c2_i5] = c2_ids[c2_d_id + 3 * c2_i5];
  }

  _SFD_SYMBOL_SWITCH(3U, 3U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
  for (c2_i6 = 0; c2_i6 < 4; c2_i6++) {
    c2_dist[c2_i6] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
  for (c2_i7 = 0; c2_i7 < 2; c2_i7++) {
    c2_f_u[c2_i7] = c2_c_id[c2_i7];
  }

  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_f_u, 10, 0U, 1U, 0U, 2, 1, 2),
                false);
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_call_debug
                        (sfGlobalDebugInstanceStruct, "GetMC", 1U, 2U, 14,
    sf_mex_dup(chartInstance->c2_s), 14, c2_f_y), "GetMC", c2_dv0);
  for (c2_i8 = 0; c2_i8 < 4; c2_i8++) {
    c2_dist[c2_i8] = c2_dv0[c2_i8];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
  c2_b_r1 = c2_dist[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 37);
  c2_b_r2 = c2_dist[1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
  c2_b_r3 = c2_dist[2];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
  c2_b_r4 = c2_dist[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -39);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c2_ports);
  *chartInstance->c2_r1 = c2_b_r1;
  *chartInstance->c2_r2 = c2_b_r2;
  *chartInstance->c2_r3 = c2_b_r3;
  *chartInstance->c2_r4 = c2_b_r4;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Demo1MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_r1, 1U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_r2, 2U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_r3, 3U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_r4, 4U);
}

static void mdl_start_c2_Demo1(SFc2_Demo1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc2_Demo1(SFc2_Demo1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  const mxArray *c2_u;
  const mxArray *c2_y = NULL;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = sf_mex_dup(*(const mxArray **)c2_inData);
  c2_y = NULL;
  if (!chartInstance->c2_s_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_u), false);
  }

  sf_mex_destroy(&c2_u);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_b_r4, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_r4), &c2_thisId);
  sf_mex_destroy(&c2_b_r4);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_r4;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_b_r4 = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_r4), &c2_thisId);
  sf_mex_destroy(&c2_b_r4);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i9;
  char_T c2_b_inData[2];
  int32_T c2_i10;
  char_T c2_u[2];
  const mxArray *c2_y = NULL;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i9 = 0; c2_i9 < 2; c2_i9++) {
    c2_b_inData[c2_i9] = (*(char_T (*)[2])c2_inData)[c2_i9];
  }

  for (c2_i10 = 0; c2_i10 < 2; c2_i10++) {
    c2_u[c2_i10] = c2_b_inData[c2_i10];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 2), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y[2])
{
  char_T c2_cv5[2];
  int32_T c2_i11;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_cv5, 1, 10, 0U, 1, 0U, 2, 1, 2);
  for (c2_i11 = 0; c2_i11 < 2; c2_i11++) {
    c2_y[c2_i11] = c2_cv5[c2_i11];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_id;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  char_T c2_y[2];
  int32_T c2_i12;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_b_id = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_id), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_id);
  for (c2_i12 = 0; c2_i12 < 2; c2_i12++) {
    (*(char_T (*)[2])c2_outData)[c2_i12] = c2_y[c2_i12];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i13;
  real_T c2_b_inData[4];
  int32_T c2_i14;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i13 = 0; c2_i13 < 4; c2_i13++) {
    c2_b_inData[c2_i13] = (*(real_T (*)[4])c2_inData)[c2_i13];
  }

  for (c2_i14 = 0; c2_i14 < 4; c2_i14++) {
    c2_u[c2_i14] = c2_b_inData[c2_i14];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 4), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_GetMC;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i15;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_GetMC = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_GetMC), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_GetMC);
  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    (*(real_T (*)[4])c2_outData)[c2_i15] = c2_y[c2_i15];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i16;
  int32_T c2_i17;
  int32_T c2_i18;
  char_T c2_b_inData[6];
  int32_T c2_i19;
  int32_T c2_i20;
  int32_T c2_i21;
  char_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i16 = 0;
  for (c2_i17 = 0; c2_i17 < 2; c2_i17++) {
    for (c2_i18 = 0; c2_i18 < 3; c2_i18++) {
      c2_b_inData[c2_i18 + c2_i16] = (*(char_T (*)[6])c2_inData)[c2_i18 + c2_i16];
    }

    c2_i16 += 3;
  }

  c2_i19 = 0;
  for (c2_i20 = 0; c2_i20 < 2; c2_i20++) {
    for (c2_i21 = 0; c2_i21 < 3; c2_i21++) {
      c2_u[c2_i21 + c2_i19] = c2_b_inData[c2_i21 + c2_i19];
    }

    c2_i19 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 3, 2), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y[6])
{
  char_T c2_cv6[6];
  int32_T c2_i22;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_cv6, 1, 10, 0U, 1, 0U, 2, 3, 2);
  for (c2_i22 = 0; c2_i22 < 6; c2_i22++) {
    c2_y[c2_i22] = c2_cv6[c2_i22];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_ids;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  char_T c2_y[6];
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_i25;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_ids = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_ids), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_ids);
  c2_i23 = 0;
  for (c2_i24 = 0; c2_i24 < 2; c2_i24++) {
    for (c2_i25 = 0; c2_i25 < 3; c2_i25++) {
      (*(char_T (*)[6])c2_outData)[c2_i25 + c2_i23] = c2_y[c2_i25 + c2_i23];
    }

    c2_i23 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  const mxArray *c2_u;
  const mxArray *c2_y = NULL;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = sf_mex_dup(*(const mxArray **)c2_inData);
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_u), false);
  sf_mex_destroy(&c2_u);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

const mxArray *sf_c2_Demo1_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 2, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fclose"), "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mxArray"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/iofun/fclose.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fopen"), "name", "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mxArray"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/iofun/fopen.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_u)), false);
  return c2_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 7, 0U, 0U, 0U, 0), false);
  return c2_y;
}

static boolean_T c2_e_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_isempty, const char_T *c2_identifier)
{
  boolean_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_isempty), &c2_thisId);
  sf_mex_destroy(&c2_isempty);
  return c2_y;
}

static boolean_T c2_f_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  boolean_T c2_y;
  boolean_T c2_b0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_b0, 1, 11, 0U, 0, 0U, 0);
  c2_y = c2_b0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_g_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_GetMC, const char_T *c2_identifier, real_T c2_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_GetMC), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_GetMC);
}

static void c2_h_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4])
{
  real_T c2_dv1[4];
  int32_T c2_i26;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv1, 1, 0, 0U, 1, 0U, 2, 1, 4);
  for (c2_i26 = 0; c2_i26 < 4; c2_i26++) {
    c2_y[c2_i26] = c2_dv1[c2_i26];
  }

  sf_mex_destroy(&c2_u);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_i_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i27;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i27, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i27;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_Demo1InstanceStruct *chartInstance;
  chartInstance = (SFc2_Demo1InstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_j_emlrt_marshallIn(SFc2_Demo1InstanceStruct
  *chartInstance, const mxArray *c2_b_s, const char_T *c2_identifier)
{
  const mxArray *c2_y = NULL;
  emlrtMsgIdentifier c2_thisId;
  c2_y = NULL;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  sf_mex_assign(&c2_y, c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_s),
    &c2_thisId), false);
  sf_mex_destroy(&c2_b_s);
  return c2_y;
}

static const mxArray *c2_k_emlrt_marshallIn(SFc2_Demo1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  const mxArray *c2_y;
  (void)c2_parentId;
  c2_y = NULL;
  c2_y = NULL;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_s_not_empty = false;
  } else {
    chartInstance->c2_s_not_empty = true;
    sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_u), false);
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static uint8_T c2_l_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_Demo1, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_is_active_c2_Demo1),
    &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_Demo1);
  return c2_y;
}

static uint8_T c2_m_emlrt_marshallIn(SFc2_Demo1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_Demo1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_Demo1InstanceStruct *chartInstance)
{
  chartInstance->c2_id = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    0);
  chartInstance->c2_r1 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_r2 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_r3 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_r4 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_Demo1_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2943032785U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3624533290U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2285265809U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(184434897U);
}

mxArray* sf_c2_Demo1_get_post_codegen_info(void);
mxArray *sf_c2_Demo1_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("jpBjpK1RPQ42wHwPJ4mtQG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_Demo1_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_Demo1_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_Demo1_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_Demo1_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_Demo1_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_Demo1(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[5],T\"r1\",},{M[1],M[6],T\"r2\",},{M[1],M[7],T\"r3\",},{M[1],M[8],T\"r4\",},{M[4],M[0],T\"s\",S'l','i','p'{{M1x2[398 399],M[0],}}},{M[8],M[0],T\"is_active_c2_Demo1\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_Demo1_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_Demo1InstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_Demo1InstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Demo1MachineNumber_,
           2,
           1,
           1,
           0,
           5,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_Demo1MachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_Demo1MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _Demo1MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"id");
          _SFD_SET_DATA_PROPS(1,2,0,1,"r1");
          _SFD_SET_DATA_PROPS(2,2,0,1,"r2");
          _SFD_SET_DATA_PROPS(3,2,0,1,"r3");
          _SFD_SET_DATA_PROPS(4,2,0,1,"r4");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,0,0,1,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1123);
        _SFD_CV_INIT_EML_IF(0,1,0,591,604,-1,941);
        _SFD_CV_INIT_EML_IF(0,1,1,640,658,-1,724);

        {
          static int condStart[] = { 644 };

          static int condEnd[] = { 658 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,643,658,1,0,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c2_id);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c2_r1);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c2_r2);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c2_r3);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c2_r4);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _Demo1MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "kQVoFhGg9BYPOBUwsFaQUD";
}

static void sf_opaque_initialize_c2_Demo1(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_Demo1InstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c2_Demo1((SFc2_Demo1InstanceStruct*) chartInstanceVar);
  initialize_c2_Demo1((SFc2_Demo1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_Demo1(void *chartInstanceVar)
{
  enable_c2_Demo1((SFc2_Demo1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_Demo1(void *chartInstanceVar)
{
  disable_c2_Demo1((SFc2_Demo1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_Demo1(void *chartInstanceVar)
{
  sf_gateway_c2_Demo1((SFc2_Demo1InstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_Demo1(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c2_Demo1((SFc2_Demo1InstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_Demo1(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c2_Demo1((SFc2_Demo1InstanceStruct*)chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c2_Demo1(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_Demo1InstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Demo1_optimization_info();
    }

    finalize_c2_Demo1((SFc2_Demo1InstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_Demo1((SFc2_Demo1InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_Demo1(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c2_Demo1((SFc2_Demo1InstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_Demo1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Demo1_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1563556750U));
  ssSetChecksum1(S,(3061661845U));
  ssSetChecksum2(S,(3229442284U));
  ssSetChecksum3(S,(3342554554U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_Demo1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_Demo1(SimStruct *S)
{
  SFc2_Demo1InstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_Demo1InstanceStruct *)utMalloc(sizeof
    (SFc2_Demo1InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_Demo1InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_Demo1;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_Demo1;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_Demo1;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_Demo1;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_Demo1;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_Demo1;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_Demo1;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_Demo1;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_Demo1;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_Demo1;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_Demo1;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_Demo1_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_Demo1(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_Demo1(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_Demo1(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_Demo1_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
