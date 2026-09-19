#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_265137795402476550) {
   out_265137795402476550[0] = delta_x[0] + nom_x[0];
   out_265137795402476550[1] = delta_x[1] + nom_x[1];
   out_265137795402476550[2] = delta_x[2] + nom_x[2];
   out_265137795402476550[3] = delta_x[3] + nom_x[3];
   out_265137795402476550[4] = delta_x[4] + nom_x[4];
   out_265137795402476550[5] = delta_x[5] + nom_x[5];
   out_265137795402476550[6] = delta_x[6] + nom_x[6];
   out_265137795402476550[7] = delta_x[7] + nom_x[7];
   out_265137795402476550[8] = delta_x[8] + nom_x[8];
   out_265137795402476550[9] = delta_x[9] + nom_x[9];
   out_265137795402476550[10] = delta_x[10] + nom_x[10];
   out_265137795402476550[11] = delta_x[11] + nom_x[11];
   out_265137795402476550[12] = delta_x[12] + nom_x[12];
   out_265137795402476550[13] = delta_x[13] + nom_x[13];
   out_265137795402476550[14] = delta_x[14] + nom_x[14];
   out_265137795402476550[15] = delta_x[15] + nom_x[15];
   out_265137795402476550[16] = delta_x[16] + nom_x[16];
   out_265137795402476550[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3199037104659900402) {
   out_3199037104659900402[0] = -nom_x[0] + true_x[0];
   out_3199037104659900402[1] = -nom_x[1] + true_x[1];
   out_3199037104659900402[2] = -nom_x[2] + true_x[2];
   out_3199037104659900402[3] = -nom_x[3] + true_x[3];
   out_3199037104659900402[4] = -nom_x[4] + true_x[4];
   out_3199037104659900402[5] = -nom_x[5] + true_x[5];
   out_3199037104659900402[6] = -nom_x[6] + true_x[6];
   out_3199037104659900402[7] = -nom_x[7] + true_x[7];
   out_3199037104659900402[8] = -nom_x[8] + true_x[8];
   out_3199037104659900402[9] = -nom_x[9] + true_x[9];
   out_3199037104659900402[10] = -nom_x[10] + true_x[10];
   out_3199037104659900402[11] = -nom_x[11] + true_x[11];
   out_3199037104659900402[12] = -nom_x[12] + true_x[12];
   out_3199037104659900402[13] = -nom_x[13] + true_x[13];
   out_3199037104659900402[14] = -nom_x[14] + true_x[14];
   out_3199037104659900402[15] = -nom_x[15] + true_x[15];
   out_3199037104659900402[16] = -nom_x[16] + true_x[16];
   out_3199037104659900402[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3725952604437651116) {
   out_3725952604437651116[0] = 1.0;
   out_3725952604437651116[1] = 0.0;
   out_3725952604437651116[2] = 0.0;
   out_3725952604437651116[3] = 0.0;
   out_3725952604437651116[4] = 0.0;
   out_3725952604437651116[5] = 0.0;
   out_3725952604437651116[6] = 0.0;
   out_3725952604437651116[7] = 0.0;
   out_3725952604437651116[8] = 0.0;
   out_3725952604437651116[9] = 0.0;
   out_3725952604437651116[10] = 0.0;
   out_3725952604437651116[11] = 0.0;
   out_3725952604437651116[12] = 0.0;
   out_3725952604437651116[13] = 0.0;
   out_3725952604437651116[14] = 0.0;
   out_3725952604437651116[15] = 0.0;
   out_3725952604437651116[16] = 0.0;
   out_3725952604437651116[17] = 0.0;
   out_3725952604437651116[18] = 0.0;
   out_3725952604437651116[19] = 1.0;
   out_3725952604437651116[20] = 0.0;
   out_3725952604437651116[21] = 0.0;
   out_3725952604437651116[22] = 0.0;
   out_3725952604437651116[23] = 0.0;
   out_3725952604437651116[24] = 0.0;
   out_3725952604437651116[25] = 0.0;
   out_3725952604437651116[26] = 0.0;
   out_3725952604437651116[27] = 0.0;
   out_3725952604437651116[28] = 0.0;
   out_3725952604437651116[29] = 0.0;
   out_3725952604437651116[30] = 0.0;
   out_3725952604437651116[31] = 0.0;
   out_3725952604437651116[32] = 0.0;
   out_3725952604437651116[33] = 0.0;
   out_3725952604437651116[34] = 0.0;
   out_3725952604437651116[35] = 0.0;
   out_3725952604437651116[36] = 0.0;
   out_3725952604437651116[37] = 0.0;
   out_3725952604437651116[38] = 1.0;
   out_3725952604437651116[39] = 0.0;
   out_3725952604437651116[40] = 0.0;
   out_3725952604437651116[41] = 0.0;
   out_3725952604437651116[42] = 0.0;
   out_3725952604437651116[43] = 0.0;
   out_3725952604437651116[44] = 0.0;
   out_3725952604437651116[45] = 0.0;
   out_3725952604437651116[46] = 0.0;
   out_3725952604437651116[47] = 0.0;
   out_3725952604437651116[48] = 0.0;
   out_3725952604437651116[49] = 0.0;
   out_3725952604437651116[50] = 0.0;
   out_3725952604437651116[51] = 0.0;
   out_3725952604437651116[52] = 0.0;
   out_3725952604437651116[53] = 0.0;
   out_3725952604437651116[54] = 0.0;
   out_3725952604437651116[55] = 0.0;
   out_3725952604437651116[56] = 0.0;
   out_3725952604437651116[57] = 1.0;
   out_3725952604437651116[58] = 0.0;
   out_3725952604437651116[59] = 0.0;
   out_3725952604437651116[60] = 0.0;
   out_3725952604437651116[61] = 0.0;
   out_3725952604437651116[62] = 0.0;
   out_3725952604437651116[63] = 0.0;
   out_3725952604437651116[64] = 0.0;
   out_3725952604437651116[65] = 0.0;
   out_3725952604437651116[66] = 0.0;
   out_3725952604437651116[67] = 0.0;
   out_3725952604437651116[68] = 0.0;
   out_3725952604437651116[69] = 0.0;
   out_3725952604437651116[70] = 0.0;
   out_3725952604437651116[71] = 0.0;
   out_3725952604437651116[72] = 0.0;
   out_3725952604437651116[73] = 0.0;
   out_3725952604437651116[74] = 0.0;
   out_3725952604437651116[75] = 0.0;
   out_3725952604437651116[76] = 1.0;
   out_3725952604437651116[77] = 0.0;
   out_3725952604437651116[78] = 0.0;
   out_3725952604437651116[79] = 0.0;
   out_3725952604437651116[80] = 0.0;
   out_3725952604437651116[81] = 0.0;
   out_3725952604437651116[82] = 0.0;
   out_3725952604437651116[83] = 0.0;
   out_3725952604437651116[84] = 0.0;
   out_3725952604437651116[85] = 0.0;
   out_3725952604437651116[86] = 0.0;
   out_3725952604437651116[87] = 0.0;
   out_3725952604437651116[88] = 0.0;
   out_3725952604437651116[89] = 0.0;
   out_3725952604437651116[90] = 0.0;
   out_3725952604437651116[91] = 0.0;
   out_3725952604437651116[92] = 0.0;
   out_3725952604437651116[93] = 0.0;
   out_3725952604437651116[94] = 0.0;
   out_3725952604437651116[95] = 1.0;
   out_3725952604437651116[96] = 0.0;
   out_3725952604437651116[97] = 0.0;
   out_3725952604437651116[98] = 0.0;
   out_3725952604437651116[99] = 0.0;
   out_3725952604437651116[100] = 0.0;
   out_3725952604437651116[101] = 0.0;
   out_3725952604437651116[102] = 0.0;
   out_3725952604437651116[103] = 0.0;
   out_3725952604437651116[104] = 0.0;
   out_3725952604437651116[105] = 0.0;
   out_3725952604437651116[106] = 0.0;
   out_3725952604437651116[107] = 0.0;
   out_3725952604437651116[108] = 0.0;
   out_3725952604437651116[109] = 0.0;
   out_3725952604437651116[110] = 0.0;
   out_3725952604437651116[111] = 0.0;
   out_3725952604437651116[112] = 0.0;
   out_3725952604437651116[113] = 0.0;
   out_3725952604437651116[114] = 1.0;
   out_3725952604437651116[115] = 0.0;
   out_3725952604437651116[116] = 0.0;
   out_3725952604437651116[117] = 0.0;
   out_3725952604437651116[118] = 0.0;
   out_3725952604437651116[119] = 0.0;
   out_3725952604437651116[120] = 0.0;
   out_3725952604437651116[121] = 0.0;
   out_3725952604437651116[122] = 0.0;
   out_3725952604437651116[123] = 0.0;
   out_3725952604437651116[124] = 0.0;
   out_3725952604437651116[125] = 0.0;
   out_3725952604437651116[126] = 0.0;
   out_3725952604437651116[127] = 0.0;
   out_3725952604437651116[128] = 0.0;
   out_3725952604437651116[129] = 0.0;
   out_3725952604437651116[130] = 0.0;
   out_3725952604437651116[131] = 0.0;
   out_3725952604437651116[132] = 0.0;
   out_3725952604437651116[133] = 1.0;
   out_3725952604437651116[134] = 0.0;
   out_3725952604437651116[135] = 0.0;
   out_3725952604437651116[136] = 0.0;
   out_3725952604437651116[137] = 0.0;
   out_3725952604437651116[138] = 0.0;
   out_3725952604437651116[139] = 0.0;
   out_3725952604437651116[140] = 0.0;
   out_3725952604437651116[141] = 0.0;
   out_3725952604437651116[142] = 0.0;
   out_3725952604437651116[143] = 0.0;
   out_3725952604437651116[144] = 0.0;
   out_3725952604437651116[145] = 0.0;
   out_3725952604437651116[146] = 0.0;
   out_3725952604437651116[147] = 0.0;
   out_3725952604437651116[148] = 0.0;
   out_3725952604437651116[149] = 0.0;
   out_3725952604437651116[150] = 0.0;
   out_3725952604437651116[151] = 0.0;
   out_3725952604437651116[152] = 1.0;
   out_3725952604437651116[153] = 0.0;
   out_3725952604437651116[154] = 0.0;
   out_3725952604437651116[155] = 0.0;
   out_3725952604437651116[156] = 0.0;
   out_3725952604437651116[157] = 0.0;
   out_3725952604437651116[158] = 0.0;
   out_3725952604437651116[159] = 0.0;
   out_3725952604437651116[160] = 0.0;
   out_3725952604437651116[161] = 0.0;
   out_3725952604437651116[162] = 0.0;
   out_3725952604437651116[163] = 0.0;
   out_3725952604437651116[164] = 0.0;
   out_3725952604437651116[165] = 0.0;
   out_3725952604437651116[166] = 0.0;
   out_3725952604437651116[167] = 0.0;
   out_3725952604437651116[168] = 0.0;
   out_3725952604437651116[169] = 0.0;
   out_3725952604437651116[170] = 0.0;
   out_3725952604437651116[171] = 1.0;
   out_3725952604437651116[172] = 0.0;
   out_3725952604437651116[173] = 0.0;
   out_3725952604437651116[174] = 0.0;
   out_3725952604437651116[175] = 0.0;
   out_3725952604437651116[176] = 0.0;
   out_3725952604437651116[177] = 0.0;
   out_3725952604437651116[178] = 0.0;
   out_3725952604437651116[179] = 0.0;
   out_3725952604437651116[180] = 0.0;
   out_3725952604437651116[181] = 0.0;
   out_3725952604437651116[182] = 0.0;
   out_3725952604437651116[183] = 0.0;
   out_3725952604437651116[184] = 0.0;
   out_3725952604437651116[185] = 0.0;
   out_3725952604437651116[186] = 0.0;
   out_3725952604437651116[187] = 0.0;
   out_3725952604437651116[188] = 0.0;
   out_3725952604437651116[189] = 0.0;
   out_3725952604437651116[190] = 1.0;
   out_3725952604437651116[191] = 0.0;
   out_3725952604437651116[192] = 0.0;
   out_3725952604437651116[193] = 0.0;
   out_3725952604437651116[194] = 0.0;
   out_3725952604437651116[195] = 0.0;
   out_3725952604437651116[196] = 0.0;
   out_3725952604437651116[197] = 0.0;
   out_3725952604437651116[198] = 0.0;
   out_3725952604437651116[199] = 0.0;
   out_3725952604437651116[200] = 0.0;
   out_3725952604437651116[201] = 0.0;
   out_3725952604437651116[202] = 0.0;
   out_3725952604437651116[203] = 0.0;
   out_3725952604437651116[204] = 0.0;
   out_3725952604437651116[205] = 0.0;
   out_3725952604437651116[206] = 0.0;
   out_3725952604437651116[207] = 0.0;
   out_3725952604437651116[208] = 0.0;
   out_3725952604437651116[209] = 1.0;
   out_3725952604437651116[210] = 0.0;
   out_3725952604437651116[211] = 0.0;
   out_3725952604437651116[212] = 0.0;
   out_3725952604437651116[213] = 0.0;
   out_3725952604437651116[214] = 0.0;
   out_3725952604437651116[215] = 0.0;
   out_3725952604437651116[216] = 0.0;
   out_3725952604437651116[217] = 0.0;
   out_3725952604437651116[218] = 0.0;
   out_3725952604437651116[219] = 0.0;
   out_3725952604437651116[220] = 0.0;
   out_3725952604437651116[221] = 0.0;
   out_3725952604437651116[222] = 0.0;
   out_3725952604437651116[223] = 0.0;
   out_3725952604437651116[224] = 0.0;
   out_3725952604437651116[225] = 0.0;
   out_3725952604437651116[226] = 0.0;
   out_3725952604437651116[227] = 0.0;
   out_3725952604437651116[228] = 1.0;
   out_3725952604437651116[229] = 0.0;
   out_3725952604437651116[230] = 0.0;
   out_3725952604437651116[231] = 0.0;
   out_3725952604437651116[232] = 0.0;
   out_3725952604437651116[233] = 0.0;
   out_3725952604437651116[234] = 0.0;
   out_3725952604437651116[235] = 0.0;
   out_3725952604437651116[236] = 0.0;
   out_3725952604437651116[237] = 0.0;
   out_3725952604437651116[238] = 0.0;
   out_3725952604437651116[239] = 0.0;
   out_3725952604437651116[240] = 0.0;
   out_3725952604437651116[241] = 0.0;
   out_3725952604437651116[242] = 0.0;
   out_3725952604437651116[243] = 0.0;
   out_3725952604437651116[244] = 0.0;
   out_3725952604437651116[245] = 0.0;
   out_3725952604437651116[246] = 0.0;
   out_3725952604437651116[247] = 1.0;
   out_3725952604437651116[248] = 0.0;
   out_3725952604437651116[249] = 0.0;
   out_3725952604437651116[250] = 0.0;
   out_3725952604437651116[251] = 0.0;
   out_3725952604437651116[252] = 0.0;
   out_3725952604437651116[253] = 0.0;
   out_3725952604437651116[254] = 0.0;
   out_3725952604437651116[255] = 0.0;
   out_3725952604437651116[256] = 0.0;
   out_3725952604437651116[257] = 0.0;
   out_3725952604437651116[258] = 0.0;
   out_3725952604437651116[259] = 0.0;
   out_3725952604437651116[260] = 0.0;
   out_3725952604437651116[261] = 0.0;
   out_3725952604437651116[262] = 0.0;
   out_3725952604437651116[263] = 0.0;
   out_3725952604437651116[264] = 0.0;
   out_3725952604437651116[265] = 0.0;
   out_3725952604437651116[266] = 1.0;
   out_3725952604437651116[267] = 0.0;
   out_3725952604437651116[268] = 0.0;
   out_3725952604437651116[269] = 0.0;
   out_3725952604437651116[270] = 0.0;
   out_3725952604437651116[271] = 0.0;
   out_3725952604437651116[272] = 0.0;
   out_3725952604437651116[273] = 0.0;
   out_3725952604437651116[274] = 0.0;
   out_3725952604437651116[275] = 0.0;
   out_3725952604437651116[276] = 0.0;
   out_3725952604437651116[277] = 0.0;
   out_3725952604437651116[278] = 0.0;
   out_3725952604437651116[279] = 0.0;
   out_3725952604437651116[280] = 0.0;
   out_3725952604437651116[281] = 0.0;
   out_3725952604437651116[282] = 0.0;
   out_3725952604437651116[283] = 0.0;
   out_3725952604437651116[284] = 0.0;
   out_3725952604437651116[285] = 1.0;
   out_3725952604437651116[286] = 0.0;
   out_3725952604437651116[287] = 0.0;
   out_3725952604437651116[288] = 0.0;
   out_3725952604437651116[289] = 0.0;
   out_3725952604437651116[290] = 0.0;
   out_3725952604437651116[291] = 0.0;
   out_3725952604437651116[292] = 0.0;
   out_3725952604437651116[293] = 0.0;
   out_3725952604437651116[294] = 0.0;
   out_3725952604437651116[295] = 0.0;
   out_3725952604437651116[296] = 0.0;
   out_3725952604437651116[297] = 0.0;
   out_3725952604437651116[298] = 0.0;
   out_3725952604437651116[299] = 0.0;
   out_3725952604437651116[300] = 0.0;
   out_3725952604437651116[301] = 0.0;
   out_3725952604437651116[302] = 0.0;
   out_3725952604437651116[303] = 0.0;
   out_3725952604437651116[304] = 1.0;
   out_3725952604437651116[305] = 0.0;
   out_3725952604437651116[306] = 0.0;
   out_3725952604437651116[307] = 0.0;
   out_3725952604437651116[308] = 0.0;
   out_3725952604437651116[309] = 0.0;
   out_3725952604437651116[310] = 0.0;
   out_3725952604437651116[311] = 0.0;
   out_3725952604437651116[312] = 0.0;
   out_3725952604437651116[313] = 0.0;
   out_3725952604437651116[314] = 0.0;
   out_3725952604437651116[315] = 0.0;
   out_3725952604437651116[316] = 0.0;
   out_3725952604437651116[317] = 0.0;
   out_3725952604437651116[318] = 0.0;
   out_3725952604437651116[319] = 0.0;
   out_3725952604437651116[320] = 0.0;
   out_3725952604437651116[321] = 0.0;
   out_3725952604437651116[322] = 0.0;
   out_3725952604437651116[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8735875083257225398) {
   out_8735875083257225398[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8735875083257225398[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8735875083257225398[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8735875083257225398[3] = dt*state[12] + state[3];
   out_8735875083257225398[4] = dt*state[13] + state[4];
   out_8735875083257225398[5] = dt*state[14] + state[5];
   out_8735875083257225398[6] = state[6];
   out_8735875083257225398[7] = state[7];
   out_8735875083257225398[8] = state[8];
   out_8735875083257225398[9] = state[9];
   out_8735875083257225398[10] = state[10];
   out_8735875083257225398[11] = state[11];
   out_8735875083257225398[12] = state[12];
   out_8735875083257225398[13] = state[13];
   out_8735875083257225398[14] = state[14];
   out_8735875083257225398[15] = state[15];
   out_8735875083257225398[16] = state[16];
   out_8735875083257225398[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2023248126785481392) {
   out_2023248126785481392[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2023248126785481392[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2023248126785481392[2] = 0;
   out_2023248126785481392[3] = 0;
   out_2023248126785481392[4] = 0;
   out_2023248126785481392[5] = 0;
   out_2023248126785481392[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2023248126785481392[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2023248126785481392[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2023248126785481392[9] = 0;
   out_2023248126785481392[10] = 0;
   out_2023248126785481392[11] = 0;
   out_2023248126785481392[12] = 0;
   out_2023248126785481392[13] = 0;
   out_2023248126785481392[14] = 0;
   out_2023248126785481392[15] = 0;
   out_2023248126785481392[16] = 0;
   out_2023248126785481392[17] = 0;
   out_2023248126785481392[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2023248126785481392[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2023248126785481392[20] = 0;
   out_2023248126785481392[21] = 0;
   out_2023248126785481392[22] = 0;
   out_2023248126785481392[23] = 0;
   out_2023248126785481392[24] = 0;
   out_2023248126785481392[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2023248126785481392[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2023248126785481392[27] = 0;
   out_2023248126785481392[28] = 0;
   out_2023248126785481392[29] = 0;
   out_2023248126785481392[30] = 0;
   out_2023248126785481392[31] = 0;
   out_2023248126785481392[32] = 0;
   out_2023248126785481392[33] = 0;
   out_2023248126785481392[34] = 0;
   out_2023248126785481392[35] = 0;
   out_2023248126785481392[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2023248126785481392[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2023248126785481392[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2023248126785481392[39] = 0;
   out_2023248126785481392[40] = 0;
   out_2023248126785481392[41] = 0;
   out_2023248126785481392[42] = 0;
   out_2023248126785481392[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2023248126785481392[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2023248126785481392[45] = 0;
   out_2023248126785481392[46] = 0;
   out_2023248126785481392[47] = 0;
   out_2023248126785481392[48] = 0;
   out_2023248126785481392[49] = 0;
   out_2023248126785481392[50] = 0;
   out_2023248126785481392[51] = 0;
   out_2023248126785481392[52] = 0;
   out_2023248126785481392[53] = 0;
   out_2023248126785481392[54] = 0;
   out_2023248126785481392[55] = 0;
   out_2023248126785481392[56] = 0;
   out_2023248126785481392[57] = 1;
   out_2023248126785481392[58] = 0;
   out_2023248126785481392[59] = 0;
   out_2023248126785481392[60] = 0;
   out_2023248126785481392[61] = 0;
   out_2023248126785481392[62] = 0;
   out_2023248126785481392[63] = 0;
   out_2023248126785481392[64] = 0;
   out_2023248126785481392[65] = 0;
   out_2023248126785481392[66] = dt;
   out_2023248126785481392[67] = 0;
   out_2023248126785481392[68] = 0;
   out_2023248126785481392[69] = 0;
   out_2023248126785481392[70] = 0;
   out_2023248126785481392[71] = 0;
   out_2023248126785481392[72] = 0;
   out_2023248126785481392[73] = 0;
   out_2023248126785481392[74] = 0;
   out_2023248126785481392[75] = 0;
   out_2023248126785481392[76] = 1;
   out_2023248126785481392[77] = 0;
   out_2023248126785481392[78] = 0;
   out_2023248126785481392[79] = 0;
   out_2023248126785481392[80] = 0;
   out_2023248126785481392[81] = 0;
   out_2023248126785481392[82] = 0;
   out_2023248126785481392[83] = 0;
   out_2023248126785481392[84] = 0;
   out_2023248126785481392[85] = dt;
   out_2023248126785481392[86] = 0;
   out_2023248126785481392[87] = 0;
   out_2023248126785481392[88] = 0;
   out_2023248126785481392[89] = 0;
   out_2023248126785481392[90] = 0;
   out_2023248126785481392[91] = 0;
   out_2023248126785481392[92] = 0;
   out_2023248126785481392[93] = 0;
   out_2023248126785481392[94] = 0;
   out_2023248126785481392[95] = 1;
   out_2023248126785481392[96] = 0;
   out_2023248126785481392[97] = 0;
   out_2023248126785481392[98] = 0;
   out_2023248126785481392[99] = 0;
   out_2023248126785481392[100] = 0;
   out_2023248126785481392[101] = 0;
   out_2023248126785481392[102] = 0;
   out_2023248126785481392[103] = 0;
   out_2023248126785481392[104] = dt;
   out_2023248126785481392[105] = 0;
   out_2023248126785481392[106] = 0;
   out_2023248126785481392[107] = 0;
   out_2023248126785481392[108] = 0;
   out_2023248126785481392[109] = 0;
   out_2023248126785481392[110] = 0;
   out_2023248126785481392[111] = 0;
   out_2023248126785481392[112] = 0;
   out_2023248126785481392[113] = 0;
   out_2023248126785481392[114] = 1;
   out_2023248126785481392[115] = 0;
   out_2023248126785481392[116] = 0;
   out_2023248126785481392[117] = 0;
   out_2023248126785481392[118] = 0;
   out_2023248126785481392[119] = 0;
   out_2023248126785481392[120] = 0;
   out_2023248126785481392[121] = 0;
   out_2023248126785481392[122] = 0;
   out_2023248126785481392[123] = 0;
   out_2023248126785481392[124] = 0;
   out_2023248126785481392[125] = 0;
   out_2023248126785481392[126] = 0;
   out_2023248126785481392[127] = 0;
   out_2023248126785481392[128] = 0;
   out_2023248126785481392[129] = 0;
   out_2023248126785481392[130] = 0;
   out_2023248126785481392[131] = 0;
   out_2023248126785481392[132] = 0;
   out_2023248126785481392[133] = 1;
   out_2023248126785481392[134] = 0;
   out_2023248126785481392[135] = 0;
   out_2023248126785481392[136] = 0;
   out_2023248126785481392[137] = 0;
   out_2023248126785481392[138] = 0;
   out_2023248126785481392[139] = 0;
   out_2023248126785481392[140] = 0;
   out_2023248126785481392[141] = 0;
   out_2023248126785481392[142] = 0;
   out_2023248126785481392[143] = 0;
   out_2023248126785481392[144] = 0;
   out_2023248126785481392[145] = 0;
   out_2023248126785481392[146] = 0;
   out_2023248126785481392[147] = 0;
   out_2023248126785481392[148] = 0;
   out_2023248126785481392[149] = 0;
   out_2023248126785481392[150] = 0;
   out_2023248126785481392[151] = 0;
   out_2023248126785481392[152] = 1;
   out_2023248126785481392[153] = 0;
   out_2023248126785481392[154] = 0;
   out_2023248126785481392[155] = 0;
   out_2023248126785481392[156] = 0;
   out_2023248126785481392[157] = 0;
   out_2023248126785481392[158] = 0;
   out_2023248126785481392[159] = 0;
   out_2023248126785481392[160] = 0;
   out_2023248126785481392[161] = 0;
   out_2023248126785481392[162] = 0;
   out_2023248126785481392[163] = 0;
   out_2023248126785481392[164] = 0;
   out_2023248126785481392[165] = 0;
   out_2023248126785481392[166] = 0;
   out_2023248126785481392[167] = 0;
   out_2023248126785481392[168] = 0;
   out_2023248126785481392[169] = 0;
   out_2023248126785481392[170] = 0;
   out_2023248126785481392[171] = 1;
   out_2023248126785481392[172] = 0;
   out_2023248126785481392[173] = 0;
   out_2023248126785481392[174] = 0;
   out_2023248126785481392[175] = 0;
   out_2023248126785481392[176] = 0;
   out_2023248126785481392[177] = 0;
   out_2023248126785481392[178] = 0;
   out_2023248126785481392[179] = 0;
   out_2023248126785481392[180] = 0;
   out_2023248126785481392[181] = 0;
   out_2023248126785481392[182] = 0;
   out_2023248126785481392[183] = 0;
   out_2023248126785481392[184] = 0;
   out_2023248126785481392[185] = 0;
   out_2023248126785481392[186] = 0;
   out_2023248126785481392[187] = 0;
   out_2023248126785481392[188] = 0;
   out_2023248126785481392[189] = 0;
   out_2023248126785481392[190] = 1;
   out_2023248126785481392[191] = 0;
   out_2023248126785481392[192] = 0;
   out_2023248126785481392[193] = 0;
   out_2023248126785481392[194] = 0;
   out_2023248126785481392[195] = 0;
   out_2023248126785481392[196] = 0;
   out_2023248126785481392[197] = 0;
   out_2023248126785481392[198] = 0;
   out_2023248126785481392[199] = 0;
   out_2023248126785481392[200] = 0;
   out_2023248126785481392[201] = 0;
   out_2023248126785481392[202] = 0;
   out_2023248126785481392[203] = 0;
   out_2023248126785481392[204] = 0;
   out_2023248126785481392[205] = 0;
   out_2023248126785481392[206] = 0;
   out_2023248126785481392[207] = 0;
   out_2023248126785481392[208] = 0;
   out_2023248126785481392[209] = 1;
   out_2023248126785481392[210] = 0;
   out_2023248126785481392[211] = 0;
   out_2023248126785481392[212] = 0;
   out_2023248126785481392[213] = 0;
   out_2023248126785481392[214] = 0;
   out_2023248126785481392[215] = 0;
   out_2023248126785481392[216] = 0;
   out_2023248126785481392[217] = 0;
   out_2023248126785481392[218] = 0;
   out_2023248126785481392[219] = 0;
   out_2023248126785481392[220] = 0;
   out_2023248126785481392[221] = 0;
   out_2023248126785481392[222] = 0;
   out_2023248126785481392[223] = 0;
   out_2023248126785481392[224] = 0;
   out_2023248126785481392[225] = 0;
   out_2023248126785481392[226] = 0;
   out_2023248126785481392[227] = 0;
   out_2023248126785481392[228] = 1;
   out_2023248126785481392[229] = 0;
   out_2023248126785481392[230] = 0;
   out_2023248126785481392[231] = 0;
   out_2023248126785481392[232] = 0;
   out_2023248126785481392[233] = 0;
   out_2023248126785481392[234] = 0;
   out_2023248126785481392[235] = 0;
   out_2023248126785481392[236] = 0;
   out_2023248126785481392[237] = 0;
   out_2023248126785481392[238] = 0;
   out_2023248126785481392[239] = 0;
   out_2023248126785481392[240] = 0;
   out_2023248126785481392[241] = 0;
   out_2023248126785481392[242] = 0;
   out_2023248126785481392[243] = 0;
   out_2023248126785481392[244] = 0;
   out_2023248126785481392[245] = 0;
   out_2023248126785481392[246] = 0;
   out_2023248126785481392[247] = 1;
   out_2023248126785481392[248] = 0;
   out_2023248126785481392[249] = 0;
   out_2023248126785481392[250] = 0;
   out_2023248126785481392[251] = 0;
   out_2023248126785481392[252] = 0;
   out_2023248126785481392[253] = 0;
   out_2023248126785481392[254] = 0;
   out_2023248126785481392[255] = 0;
   out_2023248126785481392[256] = 0;
   out_2023248126785481392[257] = 0;
   out_2023248126785481392[258] = 0;
   out_2023248126785481392[259] = 0;
   out_2023248126785481392[260] = 0;
   out_2023248126785481392[261] = 0;
   out_2023248126785481392[262] = 0;
   out_2023248126785481392[263] = 0;
   out_2023248126785481392[264] = 0;
   out_2023248126785481392[265] = 0;
   out_2023248126785481392[266] = 1;
   out_2023248126785481392[267] = 0;
   out_2023248126785481392[268] = 0;
   out_2023248126785481392[269] = 0;
   out_2023248126785481392[270] = 0;
   out_2023248126785481392[271] = 0;
   out_2023248126785481392[272] = 0;
   out_2023248126785481392[273] = 0;
   out_2023248126785481392[274] = 0;
   out_2023248126785481392[275] = 0;
   out_2023248126785481392[276] = 0;
   out_2023248126785481392[277] = 0;
   out_2023248126785481392[278] = 0;
   out_2023248126785481392[279] = 0;
   out_2023248126785481392[280] = 0;
   out_2023248126785481392[281] = 0;
   out_2023248126785481392[282] = 0;
   out_2023248126785481392[283] = 0;
   out_2023248126785481392[284] = 0;
   out_2023248126785481392[285] = 1;
   out_2023248126785481392[286] = 0;
   out_2023248126785481392[287] = 0;
   out_2023248126785481392[288] = 0;
   out_2023248126785481392[289] = 0;
   out_2023248126785481392[290] = 0;
   out_2023248126785481392[291] = 0;
   out_2023248126785481392[292] = 0;
   out_2023248126785481392[293] = 0;
   out_2023248126785481392[294] = 0;
   out_2023248126785481392[295] = 0;
   out_2023248126785481392[296] = 0;
   out_2023248126785481392[297] = 0;
   out_2023248126785481392[298] = 0;
   out_2023248126785481392[299] = 0;
   out_2023248126785481392[300] = 0;
   out_2023248126785481392[301] = 0;
   out_2023248126785481392[302] = 0;
   out_2023248126785481392[303] = 0;
   out_2023248126785481392[304] = 1;
   out_2023248126785481392[305] = 0;
   out_2023248126785481392[306] = 0;
   out_2023248126785481392[307] = 0;
   out_2023248126785481392[308] = 0;
   out_2023248126785481392[309] = 0;
   out_2023248126785481392[310] = 0;
   out_2023248126785481392[311] = 0;
   out_2023248126785481392[312] = 0;
   out_2023248126785481392[313] = 0;
   out_2023248126785481392[314] = 0;
   out_2023248126785481392[315] = 0;
   out_2023248126785481392[316] = 0;
   out_2023248126785481392[317] = 0;
   out_2023248126785481392[318] = 0;
   out_2023248126785481392[319] = 0;
   out_2023248126785481392[320] = 0;
   out_2023248126785481392[321] = 0;
   out_2023248126785481392[322] = 0;
   out_2023248126785481392[323] = 1;
}
void h_4(double *state, double *unused, double *out_5920813341822676961) {
   out_5920813341822676961[0] = state[6] + state[9];
   out_5920813341822676961[1] = state[7] + state[10];
   out_5920813341822676961[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7497759814281558688) {
   out_7497759814281558688[0] = 0;
   out_7497759814281558688[1] = 0;
   out_7497759814281558688[2] = 0;
   out_7497759814281558688[3] = 0;
   out_7497759814281558688[4] = 0;
   out_7497759814281558688[5] = 0;
   out_7497759814281558688[6] = 1;
   out_7497759814281558688[7] = 0;
   out_7497759814281558688[8] = 0;
   out_7497759814281558688[9] = 1;
   out_7497759814281558688[10] = 0;
   out_7497759814281558688[11] = 0;
   out_7497759814281558688[12] = 0;
   out_7497759814281558688[13] = 0;
   out_7497759814281558688[14] = 0;
   out_7497759814281558688[15] = 0;
   out_7497759814281558688[16] = 0;
   out_7497759814281558688[17] = 0;
   out_7497759814281558688[18] = 0;
   out_7497759814281558688[19] = 0;
   out_7497759814281558688[20] = 0;
   out_7497759814281558688[21] = 0;
   out_7497759814281558688[22] = 0;
   out_7497759814281558688[23] = 0;
   out_7497759814281558688[24] = 0;
   out_7497759814281558688[25] = 1;
   out_7497759814281558688[26] = 0;
   out_7497759814281558688[27] = 0;
   out_7497759814281558688[28] = 1;
   out_7497759814281558688[29] = 0;
   out_7497759814281558688[30] = 0;
   out_7497759814281558688[31] = 0;
   out_7497759814281558688[32] = 0;
   out_7497759814281558688[33] = 0;
   out_7497759814281558688[34] = 0;
   out_7497759814281558688[35] = 0;
   out_7497759814281558688[36] = 0;
   out_7497759814281558688[37] = 0;
   out_7497759814281558688[38] = 0;
   out_7497759814281558688[39] = 0;
   out_7497759814281558688[40] = 0;
   out_7497759814281558688[41] = 0;
   out_7497759814281558688[42] = 0;
   out_7497759814281558688[43] = 0;
   out_7497759814281558688[44] = 1;
   out_7497759814281558688[45] = 0;
   out_7497759814281558688[46] = 0;
   out_7497759814281558688[47] = 1;
   out_7497759814281558688[48] = 0;
   out_7497759814281558688[49] = 0;
   out_7497759814281558688[50] = 0;
   out_7497759814281558688[51] = 0;
   out_7497759814281558688[52] = 0;
   out_7497759814281558688[53] = 0;
}
void h_10(double *state, double *unused, double *out_232400473007304790) {
   out_232400473007304790[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_232400473007304790[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_232400473007304790[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8496945975479553735) {
   out_8496945975479553735[0] = 0;
   out_8496945975479553735[1] = 9.8100000000000005*cos(state[1]);
   out_8496945975479553735[2] = 0;
   out_8496945975479553735[3] = 0;
   out_8496945975479553735[4] = -state[8];
   out_8496945975479553735[5] = state[7];
   out_8496945975479553735[6] = 0;
   out_8496945975479553735[7] = state[5];
   out_8496945975479553735[8] = -state[4];
   out_8496945975479553735[9] = 0;
   out_8496945975479553735[10] = 0;
   out_8496945975479553735[11] = 0;
   out_8496945975479553735[12] = 1;
   out_8496945975479553735[13] = 0;
   out_8496945975479553735[14] = 0;
   out_8496945975479553735[15] = 1;
   out_8496945975479553735[16] = 0;
   out_8496945975479553735[17] = 0;
   out_8496945975479553735[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8496945975479553735[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8496945975479553735[20] = 0;
   out_8496945975479553735[21] = state[8];
   out_8496945975479553735[22] = 0;
   out_8496945975479553735[23] = -state[6];
   out_8496945975479553735[24] = -state[5];
   out_8496945975479553735[25] = 0;
   out_8496945975479553735[26] = state[3];
   out_8496945975479553735[27] = 0;
   out_8496945975479553735[28] = 0;
   out_8496945975479553735[29] = 0;
   out_8496945975479553735[30] = 0;
   out_8496945975479553735[31] = 1;
   out_8496945975479553735[32] = 0;
   out_8496945975479553735[33] = 0;
   out_8496945975479553735[34] = 1;
   out_8496945975479553735[35] = 0;
   out_8496945975479553735[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8496945975479553735[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8496945975479553735[38] = 0;
   out_8496945975479553735[39] = -state[7];
   out_8496945975479553735[40] = state[6];
   out_8496945975479553735[41] = 0;
   out_8496945975479553735[42] = state[4];
   out_8496945975479553735[43] = -state[3];
   out_8496945975479553735[44] = 0;
   out_8496945975479553735[45] = 0;
   out_8496945975479553735[46] = 0;
   out_8496945975479553735[47] = 0;
   out_8496945975479553735[48] = 0;
   out_8496945975479553735[49] = 0;
   out_8496945975479553735[50] = 1;
   out_8496945975479553735[51] = 0;
   out_8496945975479553735[52] = 0;
   out_8496945975479553735[53] = 1;
}
void h_13(double *state, double *unused, double *out_6031288345573279101) {
   out_6031288345573279101[0] = state[3];
   out_6031288345573279101[1] = state[4];
   out_6031288345573279101[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3338353051111291999) {
   out_3338353051111291999[0] = 0;
   out_3338353051111291999[1] = 0;
   out_3338353051111291999[2] = 0;
   out_3338353051111291999[3] = 1;
   out_3338353051111291999[4] = 0;
   out_3338353051111291999[5] = 0;
   out_3338353051111291999[6] = 0;
   out_3338353051111291999[7] = 0;
   out_3338353051111291999[8] = 0;
   out_3338353051111291999[9] = 0;
   out_3338353051111291999[10] = 0;
   out_3338353051111291999[11] = 0;
   out_3338353051111291999[12] = 0;
   out_3338353051111291999[13] = 0;
   out_3338353051111291999[14] = 0;
   out_3338353051111291999[15] = 0;
   out_3338353051111291999[16] = 0;
   out_3338353051111291999[17] = 0;
   out_3338353051111291999[18] = 0;
   out_3338353051111291999[19] = 0;
   out_3338353051111291999[20] = 0;
   out_3338353051111291999[21] = 0;
   out_3338353051111291999[22] = 1;
   out_3338353051111291999[23] = 0;
   out_3338353051111291999[24] = 0;
   out_3338353051111291999[25] = 0;
   out_3338353051111291999[26] = 0;
   out_3338353051111291999[27] = 0;
   out_3338353051111291999[28] = 0;
   out_3338353051111291999[29] = 0;
   out_3338353051111291999[30] = 0;
   out_3338353051111291999[31] = 0;
   out_3338353051111291999[32] = 0;
   out_3338353051111291999[33] = 0;
   out_3338353051111291999[34] = 0;
   out_3338353051111291999[35] = 0;
   out_3338353051111291999[36] = 0;
   out_3338353051111291999[37] = 0;
   out_3338353051111291999[38] = 0;
   out_3338353051111291999[39] = 0;
   out_3338353051111291999[40] = 0;
   out_3338353051111291999[41] = 1;
   out_3338353051111291999[42] = 0;
   out_3338353051111291999[43] = 0;
   out_3338353051111291999[44] = 0;
   out_3338353051111291999[45] = 0;
   out_3338353051111291999[46] = 0;
   out_3338353051111291999[47] = 0;
   out_3338353051111291999[48] = 0;
   out_3338353051111291999[49] = 0;
   out_3338353051111291999[50] = 0;
   out_3338353051111291999[51] = 0;
   out_3338353051111291999[52] = 0;
   out_3338353051111291999[53] = 0;
}
void h_14(double *state, double *unused, double *out_4049097322198884432) {
   out_4049097322198884432[0] = state[6];
   out_4049097322198884432[1] = state[7];
   out_4049097322198884432[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4414971381986186392) {
   out_4414971381986186392[0] = 0;
   out_4414971381986186392[1] = 0;
   out_4414971381986186392[2] = 0;
   out_4414971381986186392[3] = 0;
   out_4414971381986186392[4] = 0;
   out_4414971381986186392[5] = 0;
   out_4414971381986186392[6] = 1;
   out_4414971381986186392[7] = 0;
   out_4414971381986186392[8] = 0;
   out_4414971381986186392[9] = 0;
   out_4414971381986186392[10] = 0;
   out_4414971381986186392[11] = 0;
   out_4414971381986186392[12] = 0;
   out_4414971381986186392[13] = 0;
   out_4414971381986186392[14] = 0;
   out_4414971381986186392[15] = 0;
   out_4414971381986186392[16] = 0;
   out_4414971381986186392[17] = 0;
   out_4414971381986186392[18] = 0;
   out_4414971381986186392[19] = 0;
   out_4414971381986186392[20] = 0;
   out_4414971381986186392[21] = 0;
   out_4414971381986186392[22] = 0;
   out_4414971381986186392[23] = 0;
   out_4414971381986186392[24] = 0;
   out_4414971381986186392[25] = 1;
   out_4414971381986186392[26] = 0;
   out_4414971381986186392[27] = 0;
   out_4414971381986186392[28] = 0;
   out_4414971381986186392[29] = 0;
   out_4414971381986186392[30] = 0;
   out_4414971381986186392[31] = 0;
   out_4414971381986186392[32] = 0;
   out_4414971381986186392[33] = 0;
   out_4414971381986186392[34] = 0;
   out_4414971381986186392[35] = 0;
   out_4414971381986186392[36] = 0;
   out_4414971381986186392[37] = 0;
   out_4414971381986186392[38] = 0;
   out_4414971381986186392[39] = 0;
   out_4414971381986186392[40] = 0;
   out_4414971381986186392[41] = 0;
   out_4414971381986186392[42] = 0;
   out_4414971381986186392[43] = 0;
   out_4414971381986186392[44] = 1;
   out_4414971381986186392[45] = 0;
   out_4414971381986186392[46] = 0;
   out_4414971381986186392[47] = 0;
   out_4414971381986186392[48] = 0;
   out_4414971381986186392[49] = 0;
   out_4414971381986186392[50] = 0;
   out_4414971381986186392[51] = 0;
   out_4414971381986186392[52] = 0;
   out_4414971381986186392[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_265137795402476550) {
  err_fun(nom_x, delta_x, out_265137795402476550);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3199037104659900402) {
  inv_err_fun(nom_x, true_x, out_3199037104659900402);
}
void pose_H_mod_fun(double *state, double *out_3725952604437651116) {
  H_mod_fun(state, out_3725952604437651116);
}
void pose_f_fun(double *state, double dt, double *out_8735875083257225398) {
  f_fun(state,  dt, out_8735875083257225398);
}
void pose_F_fun(double *state, double dt, double *out_2023248126785481392) {
  F_fun(state,  dt, out_2023248126785481392);
}
void pose_h_4(double *state, double *unused, double *out_5920813341822676961) {
  h_4(state, unused, out_5920813341822676961);
}
void pose_H_4(double *state, double *unused, double *out_7497759814281558688) {
  H_4(state, unused, out_7497759814281558688);
}
void pose_h_10(double *state, double *unused, double *out_232400473007304790) {
  h_10(state, unused, out_232400473007304790);
}
void pose_H_10(double *state, double *unused, double *out_8496945975479553735) {
  H_10(state, unused, out_8496945975479553735);
}
void pose_h_13(double *state, double *unused, double *out_6031288345573279101) {
  h_13(state, unused, out_6031288345573279101);
}
void pose_H_13(double *state, double *unused, double *out_3338353051111291999) {
  H_13(state, unused, out_3338353051111291999);
}
void pose_h_14(double *state, double *unused, double *out_4049097322198884432) {
  h_14(state, unused, out_4049097322198884432);
}
void pose_H_14(double *state, double *unused, double *out_4414971381986186392) {
  H_14(state, unused, out_4414971381986186392);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
