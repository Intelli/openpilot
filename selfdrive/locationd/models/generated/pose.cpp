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
void err_fun(double *nom_x, double *delta_x, double *out_8269927985032062752) {
   out_8269927985032062752[0] = delta_x[0] + nom_x[0];
   out_8269927985032062752[1] = delta_x[1] + nom_x[1];
   out_8269927985032062752[2] = delta_x[2] + nom_x[2];
   out_8269927985032062752[3] = delta_x[3] + nom_x[3];
   out_8269927985032062752[4] = delta_x[4] + nom_x[4];
   out_8269927985032062752[5] = delta_x[5] + nom_x[5];
   out_8269927985032062752[6] = delta_x[6] + nom_x[6];
   out_8269927985032062752[7] = delta_x[7] + nom_x[7];
   out_8269927985032062752[8] = delta_x[8] + nom_x[8];
   out_8269927985032062752[9] = delta_x[9] + nom_x[9];
   out_8269927985032062752[10] = delta_x[10] + nom_x[10];
   out_8269927985032062752[11] = delta_x[11] + nom_x[11];
   out_8269927985032062752[12] = delta_x[12] + nom_x[12];
   out_8269927985032062752[13] = delta_x[13] + nom_x[13];
   out_8269927985032062752[14] = delta_x[14] + nom_x[14];
   out_8269927985032062752[15] = delta_x[15] + nom_x[15];
   out_8269927985032062752[16] = delta_x[16] + nom_x[16];
   out_8269927985032062752[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7882321665795113097) {
   out_7882321665795113097[0] = -nom_x[0] + true_x[0];
   out_7882321665795113097[1] = -nom_x[1] + true_x[1];
   out_7882321665795113097[2] = -nom_x[2] + true_x[2];
   out_7882321665795113097[3] = -nom_x[3] + true_x[3];
   out_7882321665795113097[4] = -nom_x[4] + true_x[4];
   out_7882321665795113097[5] = -nom_x[5] + true_x[5];
   out_7882321665795113097[6] = -nom_x[6] + true_x[6];
   out_7882321665795113097[7] = -nom_x[7] + true_x[7];
   out_7882321665795113097[8] = -nom_x[8] + true_x[8];
   out_7882321665795113097[9] = -nom_x[9] + true_x[9];
   out_7882321665795113097[10] = -nom_x[10] + true_x[10];
   out_7882321665795113097[11] = -nom_x[11] + true_x[11];
   out_7882321665795113097[12] = -nom_x[12] + true_x[12];
   out_7882321665795113097[13] = -nom_x[13] + true_x[13];
   out_7882321665795113097[14] = -nom_x[14] + true_x[14];
   out_7882321665795113097[15] = -nom_x[15] + true_x[15];
   out_7882321665795113097[16] = -nom_x[16] + true_x[16];
   out_7882321665795113097[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2625199788015220353) {
   out_2625199788015220353[0] = 1.0;
   out_2625199788015220353[1] = 0.0;
   out_2625199788015220353[2] = 0.0;
   out_2625199788015220353[3] = 0.0;
   out_2625199788015220353[4] = 0.0;
   out_2625199788015220353[5] = 0.0;
   out_2625199788015220353[6] = 0.0;
   out_2625199788015220353[7] = 0.0;
   out_2625199788015220353[8] = 0.0;
   out_2625199788015220353[9] = 0.0;
   out_2625199788015220353[10] = 0.0;
   out_2625199788015220353[11] = 0.0;
   out_2625199788015220353[12] = 0.0;
   out_2625199788015220353[13] = 0.0;
   out_2625199788015220353[14] = 0.0;
   out_2625199788015220353[15] = 0.0;
   out_2625199788015220353[16] = 0.0;
   out_2625199788015220353[17] = 0.0;
   out_2625199788015220353[18] = 0.0;
   out_2625199788015220353[19] = 1.0;
   out_2625199788015220353[20] = 0.0;
   out_2625199788015220353[21] = 0.0;
   out_2625199788015220353[22] = 0.0;
   out_2625199788015220353[23] = 0.0;
   out_2625199788015220353[24] = 0.0;
   out_2625199788015220353[25] = 0.0;
   out_2625199788015220353[26] = 0.0;
   out_2625199788015220353[27] = 0.0;
   out_2625199788015220353[28] = 0.0;
   out_2625199788015220353[29] = 0.0;
   out_2625199788015220353[30] = 0.0;
   out_2625199788015220353[31] = 0.0;
   out_2625199788015220353[32] = 0.0;
   out_2625199788015220353[33] = 0.0;
   out_2625199788015220353[34] = 0.0;
   out_2625199788015220353[35] = 0.0;
   out_2625199788015220353[36] = 0.0;
   out_2625199788015220353[37] = 0.0;
   out_2625199788015220353[38] = 1.0;
   out_2625199788015220353[39] = 0.0;
   out_2625199788015220353[40] = 0.0;
   out_2625199788015220353[41] = 0.0;
   out_2625199788015220353[42] = 0.0;
   out_2625199788015220353[43] = 0.0;
   out_2625199788015220353[44] = 0.0;
   out_2625199788015220353[45] = 0.0;
   out_2625199788015220353[46] = 0.0;
   out_2625199788015220353[47] = 0.0;
   out_2625199788015220353[48] = 0.0;
   out_2625199788015220353[49] = 0.0;
   out_2625199788015220353[50] = 0.0;
   out_2625199788015220353[51] = 0.0;
   out_2625199788015220353[52] = 0.0;
   out_2625199788015220353[53] = 0.0;
   out_2625199788015220353[54] = 0.0;
   out_2625199788015220353[55] = 0.0;
   out_2625199788015220353[56] = 0.0;
   out_2625199788015220353[57] = 1.0;
   out_2625199788015220353[58] = 0.0;
   out_2625199788015220353[59] = 0.0;
   out_2625199788015220353[60] = 0.0;
   out_2625199788015220353[61] = 0.0;
   out_2625199788015220353[62] = 0.0;
   out_2625199788015220353[63] = 0.0;
   out_2625199788015220353[64] = 0.0;
   out_2625199788015220353[65] = 0.0;
   out_2625199788015220353[66] = 0.0;
   out_2625199788015220353[67] = 0.0;
   out_2625199788015220353[68] = 0.0;
   out_2625199788015220353[69] = 0.0;
   out_2625199788015220353[70] = 0.0;
   out_2625199788015220353[71] = 0.0;
   out_2625199788015220353[72] = 0.0;
   out_2625199788015220353[73] = 0.0;
   out_2625199788015220353[74] = 0.0;
   out_2625199788015220353[75] = 0.0;
   out_2625199788015220353[76] = 1.0;
   out_2625199788015220353[77] = 0.0;
   out_2625199788015220353[78] = 0.0;
   out_2625199788015220353[79] = 0.0;
   out_2625199788015220353[80] = 0.0;
   out_2625199788015220353[81] = 0.0;
   out_2625199788015220353[82] = 0.0;
   out_2625199788015220353[83] = 0.0;
   out_2625199788015220353[84] = 0.0;
   out_2625199788015220353[85] = 0.0;
   out_2625199788015220353[86] = 0.0;
   out_2625199788015220353[87] = 0.0;
   out_2625199788015220353[88] = 0.0;
   out_2625199788015220353[89] = 0.0;
   out_2625199788015220353[90] = 0.0;
   out_2625199788015220353[91] = 0.0;
   out_2625199788015220353[92] = 0.0;
   out_2625199788015220353[93] = 0.0;
   out_2625199788015220353[94] = 0.0;
   out_2625199788015220353[95] = 1.0;
   out_2625199788015220353[96] = 0.0;
   out_2625199788015220353[97] = 0.0;
   out_2625199788015220353[98] = 0.0;
   out_2625199788015220353[99] = 0.0;
   out_2625199788015220353[100] = 0.0;
   out_2625199788015220353[101] = 0.0;
   out_2625199788015220353[102] = 0.0;
   out_2625199788015220353[103] = 0.0;
   out_2625199788015220353[104] = 0.0;
   out_2625199788015220353[105] = 0.0;
   out_2625199788015220353[106] = 0.0;
   out_2625199788015220353[107] = 0.0;
   out_2625199788015220353[108] = 0.0;
   out_2625199788015220353[109] = 0.0;
   out_2625199788015220353[110] = 0.0;
   out_2625199788015220353[111] = 0.0;
   out_2625199788015220353[112] = 0.0;
   out_2625199788015220353[113] = 0.0;
   out_2625199788015220353[114] = 1.0;
   out_2625199788015220353[115] = 0.0;
   out_2625199788015220353[116] = 0.0;
   out_2625199788015220353[117] = 0.0;
   out_2625199788015220353[118] = 0.0;
   out_2625199788015220353[119] = 0.0;
   out_2625199788015220353[120] = 0.0;
   out_2625199788015220353[121] = 0.0;
   out_2625199788015220353[122] = 0.0;
   out_2625199788015220353[123] = 0.0;
   out_2625199788015220353[124] = 0.0;
   out_2625199788015220353[125] = 0.0;
   out_2625199788015220353[126] = 0.0;
   out_2625199788015220353[127] = 0.0;
   out_2625199788015220353[128] = 0.0;
   out_2625199788015220353[129] = 0.0;
   out_2625199788015220353[130] = 0.0;
   out_2625199788015220353[131] = 0.0;
   out_2625199788015220353[132] = 0.0;
   out_2625199788015220353[133] = 1.0;
   out_2625199788015220353[134] = 0.0;
   out_2625199788015220353[135] = 0.0;
   out_2625199788015220353[136] = 0.0;
   out_2625199788015220353[137] = 0.0;
   out_2625199788015220353[138] = 0.0;
   out_2625199788015220353[139] = 0.0;
   out_2625199788015220353[140] = 0.0;
   out_2625199788015220353[141] = 0.0;
   out_2625199788015220353[142] = 0.0;
   out_2625199788015220353[143] = 0.0;
   out_2625199788015220353[144] = 0.0;
   out_2625199788015220353[145] = 0.0;
   out_2625199788015220353[146] = 0.0;
   out_2625199788015220353[147] = 0.0;
   out_2625199788015220353[148] = 0.0;
   out_2625199788015220353[149] = 0.0;
   out_2625199788015220353[150] = 0.0;
   out_2625199788015220353[151] = 0.0;
   out_2625199788015220353[152] = 1.0;
   out_2625199788015220353[153] = 0.0;
   out_2625199788015220353[154] = 0.0;
   out_2625199788015220353[155] = 0.0;
   out_2625199788015220353[156] = 0.0;
   out_2625199788015220353[157] = 0.0;
   out_2625199788015220353[158] = 0.0;
   out_2625199788015220353[159] = 0.0;
   out_2625199788015220353[160] = 0.0;
   out_2625199788015220353[161] = 0.0;
   out_2625199788015220353[162] = 0.0;
   out_2625199788015220353[163] = 0.0;
   out_2625199788015220353[164] = 0.0;
   out_2625199788015220353[165] = 0.0;
   out_2625199788015220353[166] = 0.0;
   out_2625199788015220353[167] = 0.0;
   out_2625199788015220353[168] = 0.0;
   out_2625199788015220353[169] = 0.0;
   out_2625199788015220353[170] = 0.0;
   out_2625199788015220353[171] = 1.0;
   out_2625199788015220353[172] = 0.0;
   out_2625199788015220353[173] = 0.0;
   out_2625199788015220353[174] = 0.0;
   out_2625199788015220353[175] = 0.0;
   out_2625199788015220353[176] = 0.0;
   out_2625199788015220353[177] = 0.0;
   out_2625199788015220353[178] = 0.0;
   out_2625199788015220353[179] = 0.0;
   out_2625199788015220353[180] = 0.0;
   out_2625199788015220353[181] = 0.0;
   out_2625199788015220353[182] = 0.0;
   out_2625199788015220353[183] = 0.0;
   out_2625199788015220353[184] = 0.0;
   out_2625199788015220353[185] = 0.0;
   out_2625199788015220353[186] = 0.0;
   out_2625199788015220353[187] = 0.0;
   out_2625199788015220353[188] = 0.0;
   out_2625199788015220353[189] = 0.0;
   out_2625199788015220353[190] = 1.0;
   out_2625199788015220353[191] = 0.0;
   out_2625199788015220353[192] = 0.0;
   out_2625199788015220353[193] = 0.0;
   out_2625199788015220353[194] = 0.0;
   out_2625199788015220353[195] = 0.0;
   out_2625199788015220353[196] = 0.0;
   out_2625199788015220353[197] = 0.0;
   out_2625199788015220353[198] = 0.0;
   out_2625199788015220353[199] = 0.0;
   out_2625199788015220353[200] = 0.0;
   out_2625199788015220353[201] = 0.0;
   out_2625199788015220353[202] = 0.0;
   out_2625199788015220353[203] = 0.0;
   out_2625199788015220353[204] = 0.0;
   out_2625199788015220353[205] = 0.0;
   out_2625199788015220353[206] = 0.0;
   out_2625199788015220353[207] = 0.0;
   out_2625199788015220353[208] = 0.0;
   out_2625199788015220353[209] = 1.0;
   out_2625199788015220353[210] = 0.0;
   out_2625199788015220353[211] = 0.0;
   out_2625199788015220353[212] = 0.0;
   out_2625199788015220353[213] = 0.0;
   out_2625199788015220353[214] = 0.0;
   out_2625199788015220353[215] = 0.0;
   out_2625199788015220353[216] = 0.0;
   out_2625199788015220353[217] = 0.0;
   out_2625199788015220353[218] = 0.0;
   out_2625199788015220353[219] = 0.0;
   out_2625199788015220353[220] = 0.0;
   out_2625199788015220353[221] = 0.0;
   out_2625199788015220353[222] = 0.0;
   out_2625199788015220353[223] = 0.0;
   out_2625199788015220353[224] = 0.0;
   out_2625199788015220353[225] = 0.0;
   out_2625199788015220353[226] = 0.0;
   out_2625199788015220353[227] = 0.0;
   out_2625199788015220353[228] = 1.0;
   out_2625199788015220353[229] = 0.0;
   out_2625199788015220353[230] = 0.0;
   out_2625199788015220353[231] = 0.0;
   out_2625199788015220353[232] = 0.0;
   out_2625199788015220353[233] = 0.0;
   out_2625199788015220353[234] = 0.0;
   out_2625199788015220353[235] = 0.0;
   out_2625199788015220353[236] = 0.0;
   out_2625199788015220353[237] = 0.0;
   out_2625199788015220353[238] = 0.0;
   out_2625199788015220353[239] = 0.0;
   out_2625199788015220353[240] = 0.0;
   out_2625199788015220353[241] = 0.0;
   out_2625199788015220353[242] = 0.0;
   out_2625199788015220353[243] = 0.0;
   out_2625199788015220353[244] = 0.0;
   out_2625199788015220353[245] = 0.0;
   out_2625199788015220353[246] = 0.0;
   out_2625199788015220353[247] = 1.0;
   out_2625199788015220353[248] = 0.0;
   out_2625199788015220353[249] = 0.0;
   out_2625199788015220353[250] = 0.0;
   out_2625199788015220353[251] = 0.0;
   out_2625199788015220353[252] = 0.0;
   out_2625199788015220353[253] = 0.0;
   out_2625199788015220353[254] = 0.0;
   out_2625199788015220353[255] = 0.0;
   out_2625199788015220353[256] = 0.0;
   out_2625199788015220353[257] = 0.0;
   out_2625199788015220353[258] = 0.0;
   out_2625199788015220353[259] = 0.0;
   out_2625199788015220353[260] = 0.0;
   out_2625199788015220353[261] = 0.0;
   out_2625199788015220353[262] = 0.0;
   out_2625199788015220353[263] = 0.0;
   out_2625199788015220353[264] = 0.0;
   out_2625199788015220353[265] = 0.0;
   out_2625199788015220353[266] = 1.0;
   out_2625199788015220353[267] = 0.0;
   out_2625199788015220353[268] = 0.0;
   out_2625199788015220353[269] = 0.0;
   out_2625199788015220353[270] = 0.0;
   out_2625199788015220353[271] = 0.0;
   out_2625199788015220353[272] = 0.0;
   out_2625199788015220353[273] = 0.0;
   out_2625199788015220353[274] = 0.0;
   out_2625199788015220353[275] = 0.0;
   out_2625199788015220353[276] = 0.0;
   out_2625199788015220353[277] = 0.0;
   out_2625199788015220353[278] = 0.0;
   out_2625199788015220353[279] = 0.0;
   out_2625199788015220353[280] = 0.0;
   out_2625199788015220353[281] = 0.0;
   out_2625199788015220353[282] = 0.0;
   out_2625199788015220353[283] = 0.0;
   out_2625199788015220353[284] = 0.0;
   out_2625199788015220353[285] = 1.0;
   out_2625199788015220353[286] = 0.0;
   out_2625199788015220353[287] = 0.0;
   out_2625199788015220353[288] = 0.0;
   out_2625199788015220353[289] = 0.0;
   out_2625199788015220353[290] = 0.0;
   out_2625199788015220353[291] = 0.0;
   out_2625199788015220353[292] = 0.0;
   out_2625199788015220353[293] = 0.0;
   out_2625199788015220353[294] = 0.0;
   out_2625199788015220353[295] = 0.0;
   out_2625199788015220353[296] = 0.0;
   out_2625199788015220353[297] = 0.0;
   out_2625199788015220353[298] = 0.0;
   out_2625199788015220353[299] = 0.0;
   out_2625199788015220353[300] = 0.0;
   out_2625199788015220353[301] = 0.0;
   out_2625199788015220353[302] = 0.0;
   out_2625199788015220353[303] = 0.0;
   out_2625199788015220353[304] = 1.0;
   out_2625199788015220353[305] = 0.0;
   out_2625199788015220353[306] = 0.0;
   out_2625199788015220353[307] = 0.0;
   out_2625199788015220353[308] = 0.0;
   out_2625199788015220353[309] = 0.0;
   out_2625199788015220353[310] = 0.0;
   out_2625199788015220353[311] = 0.0;
   out_2625199788015220353[312] = 0.0;
   out_2625199788015220353[313] = 0.0;
   out_2625199788015220353[314] = 0.0;
   out_2625199788015220353[315] = 0.0;
   out_2625199788015220353[316] = 0.0;
   out_2625199788015220353[317] = 0.0;
   out_2625199788015220353[318] = 0.0;
   out_2625199788015220353[319] = 0.0;
   out_2625199788015220353[320] = 0.0;
   out_2625199788015220353[321] = 0.0;
   out_2625199788015220353[322] = 0.0;
   out_2625199788015220353[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2756784837860721128) {
   out_2756784837860721128[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2756784837860721128[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2756784837860721128[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2756784837860721128[3] = dt*state[12] + state[3];
   out_2756784837860721128[4] = dt*state[13] + state[4];
   out_2756784837860721128[5] = dt*state[14] + state[5];
   out_2756784837860721128[6] = state[6];
   out_2756784837860721128[7] = state[7];
   out_2756784837860721128[8] = state[8];
   out_2756784837860721128[9] = state[9];
   out_2756784837860721128[10] = state[10];
   out_2756784837860721128[11] = state[11];
   out_2756784837860721128[12] = state[12];
   out_2756784837860721128[13] = state[13];
   out_2756784837860721128[14] = state[14];
   out_2756784837860721128[15] = state[15];
   out_2756784837860721128[16] = state[16];
   out_2756784837860721128[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7596404610561457994) {
   out_7596404610561457994[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7596404610561457994[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7596404610561457994[2] = 0;
   out_7596404610561457994[3] = 0;
   out_7596404610561457994[4] = 0;
   out_7596404610561457994[5] = 0;
   out_7596404610561457994[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7596404610561457994[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7596404610561457994[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7596404610561457994[9] = 0;
   out_7596404610561457994[10] = 0;
   out_7596404610561457994[11] = 0;
   out_7596404610561457994[12] = 0;
   out_7596404610561457994[13] = 0;
   out_7596404610561457994[14] = 0;
   out_7596404610561457994[15] = 0;
   out_7596404610561457994[16] = 0;
   out_7596404610561457994[17] = 0;
   out_7596404610561457994[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7596404610561457994[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7596404610561457994[20] = 0;
   out_7596404610561457994[21] = 0;
   out_7596404610561457994[22] = 0;
   out_7596404610561457994[23] = 0;
   out_7596404610561457994[24] = 0;
   out_7596404610561457994[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7596404610561457994[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7596404610561457994[27] = 0;
   out_7596404610561457994[28] = 0;
   out_7596404610561457994[29] = 0;
   out_7596404610561457994[30] = 0;
   out_7596404610561457994[31] = 0;
   out_7596404610561457994[32] = 0;
   out_7596404610561457994[33] = 0;
   out_7596404610561457994[34] = 0;
   out_7596404610561457994[35] = 0;
   out_7596404610561457994[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7596404610561457994[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7596404610561457994[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7596404610561457994[39] = 0;
   out_7596404610561457994[40] = 0;
   out_7596404610561457994[41] = 0;
   out_7596404610561457994[42] = 0;
   out_7596404610561457994[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7596404610561457994[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7596404610561457994[45] = 0;
   out_7596404610561457994[46] = 0;
   out_7596404610561457994[47] = 0;
   out_7596404610561457994[48] = 0;
   out_7596404610561457994[49] = 0;
   out_7596404610561457994[50] = 0;
   out_7596404610561457994[51] = 0;
   out_7596404610561457994[52] = 0;
   out_7596404610561457994[53] = 0;
   out_7596404610561457994[54] = 0;
   out_7596404610561457994[55] = 0;
   out_7596404610561457994[56] = 0;
   out_7596404610561457994[57] = 1;
   out_7596404610561457994[58] = 0;
   out_7596404610561457994[59] = 0;
   out_7596404610561457994[60] = 0;
   out_7596404610561457994[61] = 0;
   out_7596404610561457994[62] = 0;
   out_7596404610561457994[63] = 0;
   out_7596404610561457994[64] = 0;
   out_7596404610561457994[65] = 0;
   out_7596404610561457994[66] = dt;
   out_7596404610561457994[67] = 0;
   out_7596404610561457994[68] = 0;
   out_7596404610561457994[69] = 0;
   out_7596404610561457994[70] = 0;
   out_7596404610561457994[71] = 0;
   out_7596404610561457994[72] = 0;
   out_7596404610561457994[73] = 0;
   out_7596404610561457994[74] = 0;
   out_7596404610561457994[75] = 0;
   out_7596404610561457994[76] = 1;
   out_7596404610561457994[77] = 0;
   out_7596404610561457994[78] = 0;
   out_7596404610561457994[79] = 0;
   out_7596404610561457994[80] = 0;
   out_7596404610561457994[81] = 0;
   out_7596404610561457994[82] = 0;
   out_7596404610561457994[83] = 0;
   out_7596404610561457994[84] = 0;
   out_7596404610561457994[85] = dt;
   out_7596404610561457994[86] = 0;
   out_7596404610561457994[87] = 0;
   out_7596404610561457994[88] = 0;
   out_7596404610561457994[89] = 0;
   out_7596404610561457994[90] = 0;
   out_7596404610561457994[91] = 0;
   out_7596404610561457994[92] = 0;
   out_7596404610561457994[93] = 0;
   out_7596404610561457994[94] = 0;
   out_7596404610561457994[95] = 1;
   out_7596404610561457994[96] = 0;
   out_7596404610561457994[97] = 0;
   out_7596404610561457994[98] = 0;
   out_7596404610561457994[99] = 0;
   out_7596404610561457994[100] = 0;
   out_7596404610561457994[101] = 0;
   out_7596404610561457994[102] = 0;
   out_7596404610561457994[103] = 0;
   out_7596404610561457994[104] = dt;
   out_7596404610561457994[105] = 0;
   out_7596404610561457994[106] = 0;
   out_7596404610561457994[107] = 0;
   out_7596404610561457994[108] = 0;
   out_7596404610561457994[109] = 0;
   out_7596404610561457994[110] = 0;
   out_7596404610561457994[111] = 0;
   out_7596404610561457994[112] = 0;
   out_7596404610561457994[113] = 0;
   out_7596404610561457994[114] = 1;
   out_7596404610561457994[115] = 0;
   out_7596404610561457994[116] = 0;
   out_7596404610561457994[117] = 0;
   out_7596404610561457994[118] = 0;
   out_7596404610561457994[119] = 0;
   out_7596404610561457994[120] = 0;
   out_7596404610561457994[121] = 0;
   out_7596404610561457994[122] = 0;
   out_7596404610561457994[123] = 0;
   out_7596404610561457994[124] = 0;
   out_7596404610561457994[125] = 0;
   out_7596404610561457994[126] = 0;
   out_7596404610561457994[127] = 0;
   out_7596404610561457994[128] = 0;
   out_7596404610561457994[129] = 0;
   out_7596404610561457994[130] = 0;
   out_7596404610561457994[131] = 0;
   out_7596404610561457994[132] = 0;
   out_7596404610561457994[133] = 1;
   out_7596404610561457994[134] = 0;
   out_7596404610561457994[135] = 0;
   out_7596404610561457994[136] = 0;
   out_7596404610561457994[137] = 0;
   out_7596404610561457994[138] = 0;
   out_7596404610561457994[139] = 0;
   out_7596404610561457994[140] = 0;
   out_7596404610561457994[141] = 0;
   out_7596404610561457994[142] = 0;
   out_7596404610561457994[143] = 0;
   out_7596404610561457994[144] = 0;
   out_7596404610561457994[145] = 0;
   out_7596404610561457994[146] = 0;
   out_7596404610561457994[147] = 0;
   out_7596404610561457994[148] = 0;
   out_7596404610561457994[149] = 0;
   out_7596404610561457994[150] = 0;
   out_7596404610561457994[151] = 0;
   out_7596404610561457994[152] = 1;
   out_7596404610561457994[153] = 0;
   out_7596404610561457994[154] = 0;
   out_7596404610561457994[155] = 0;
   out_7596404610561457994[156] = 0;
   out_7596404610561457994[157] = 0;
   out_7596404610561457994[158] = 0;
   out_7596404610561457994[159] = 0;
   out_7596404610561457994[160] = 0;
   out_7596404610561457994[161] = 0;
   out_7596404610561457994[162] = 0;
   out_7596404610561457994[163] = 0;
   out_7596404610561457994[164] = 0;
   out_7596404610561457994[165] = 0;
   out_7596404610561457994[166] = 0;
   out_7596404610561457994[167] = 0;
   out_7596404610561457994[168] = 0;
   out_7596404610561457994[169] = 0;
   out_7596404610561457994[170] = 0;
   out_7596404610561457994[171] = 1;
   out_7596404610561457994[172] = 0;
   out_7596404610561457994[173] = 0;
   out_7596404610561457994[174] = 0;
   out_7596404610561457994[175] = 0;
   out_7596404610561457994[176] = 0;
   out_7596404610561457994[177] = 0;
   out_7596404610561457994[178] = 0;
   out_7596404610561457994[179] = 0;
   out_7596404610561457994[180] = 0;
   out_7596404610561457994[181] = 0;
   out_7596404610561457994[182] = 0;
   out_7596404610561457994[183] = 0;
   out_7596404610561457994[184] = 0;
   out_7596404610561457994[185] = 0;
   out_7596404610561457994[186] = 0;
   out_7596404610561457994[187] = 0;
   out_7596404610561457994[188] = 0;
   out_7596404610561457994[189] = 0;
   out_7596404610561457994[190] = 1;
   out_7596404610561457994[191] = 0;
   out_7596404610561457994[192] = 0;
   out_7596404610561457994[193] = 0;
   out_7596404610561457994[194] = 0;
   out_7596404610561457994[195] = 0;
   out_7596404610561457994[196] = 0;
   out_7596404610561457994[197] = 0;
   out_7596404610561457994[198] = 0;
   out_7596404610561457994[199] = 0;
   out_7596404610561457994[200] = 0;
   out_7596404610561457994[201] = 0;
   out_7596404610561457994[202] = 0;
   out_7596404610561457994[203] = 0;
   out_7596404610561457994[204] = 0;
   out_7596404610561457994[205] = 0;
   out_7596404610561457994[206] = 0;
   out_7596404610561457994[207] = 0;
   out_7596404610561457994[208] = 0;
   out_7596404610561457994[209] = 1;
   out_7596404610561457994[210] = 0;
   out_7596404610561457994[211] = 0;
   out_7596404610561457994[212] = 0;
   out_7596404610561457994[213] = 0;
   out_7596404610561457994[214] = 0;
   out_7596404610561457994[215] = 0;
   out_7596404610561457994[216] = 0;
   out_7596404610561457994[217] = 0;
   out_7596404610561457994[218] = 0;
   out_7596404610561457994[219] = 0;
   out_7596404610561457994[220] = 0;
   out_7596404610561457994[221] = 0;
   out_7596404610561457994[222] = 0;
   out_7596404610561457994[223] = 0;
   out_7596404610561457994[224] = 0;
   out_7596404610561457994[225] = 0;
   out_7596404610561457994[226] = 0;
   out_7596404610561457994[227] = 0;
   out_7596404610561457994[228] = 1;
   out_7596404610561457994[229] = 0;
   out_7596404610561457994[230] = 0;
   out_7596404610561457994[231] = 0;
   out_7596404610561457994[232] = 0;
   out_7596404610561457994[233] = 0;
   out_7596404610561457994[234] = 0;
   out_7596404610561457994[235] = 0;
   out_7596404610561457994[236] = 0;
   out_7596404610561457994[237] = 0;
   out_7596404610561457994[238] = 0;
   out_7596404610561457994[239] = 0;
   out_7596404610561457994[240] = 0;
   out_7596404610561457994[241] = 0;
   out_7596404610561457994[242] = 0;
   out_7596404610561457994[243] = 0;
   out_7596404610561457994[244] = 0;
   out_7596404610561457994[245] = 0;
   out_7596404610561457994[246] = 0;
   out_7596404610561457994[247] = 1;
   out_7596404610561457994[248] = 0;
   out_7596404610561457994[249] = 0;
   out_7596404610561457994[250] = 0;
   out_7596404610561457994[251] = 0;
   out_7596404610561457994[252] = 0;
   out_7596404610561457994[253] = 0;
   out_7596404610561457994[254] = 0;
   out_7596404610561457994[255] = 0;
   out_7596404610561457994[256] = 0;
   out_7596404610561457994[257] = 0;
   out_7596404610561457994[258] = 0;
   out_7596404610561457994[259] = 0;
   out_7596404610561457994[260] = 0;
   out_7596404610561457994[261] = 0;
   out_7596404610561457994[262] = 0;
   out_7596404610561457994[263] = 0;
   out_7596404610561457994[264] = 0;
   out_7596404610561457994[265] = 0;
   out_7596404610561457994[266] = 1;
   out_7596404610561457994[267] = 0;
   out_7596404610561457994[268] = 0;
   out_7596404610561457994[269] = 0;
   out_7596404610561457994[270] = 0;
   out_7596404610561457994[271] = 0;
   out_7596404610561457994[272] = 0;
   out_7596404610561457994[273] = 0;
   out_7596404610561457994[274] = 0;
   out_7596404610561457994[275] = 0;
   out_7596404610561457994[276] = 0;
   out_7596404610561457994[277] = 0;
   out_7596404610561457994[278] = 0;
   out_7596404610561457994[279] = 0;
   out_7596404610561457994[280] = 0;
   out_7596404610561457994[281] = 0;
   out_7596404610561457994[282] = 0;
   out_7596404610561457994[283] = 0;
   out_7596404610561457994[284] = 0;
   out_7596404610561457994[285] = 1;
   out_7596404610561457994[286] = 0;
   out_7596404610561457994[287] = 0;
   out_7596404610561457994[288] = 0;
   out_7596404610561457994[289] = 0;
   out_7596404610561457994[290] = 0;
   out_7596404610561457994[291] = 0;
   out_7596404610561457994[292] = 0;
   out_7596404610561457994[293] = 0;
   out_7596404610561457994[294] = 0;
   out_7596404610561457994[295] = 0;
   out_7596404610561457994[296] = 0;
   out_7596404610561457994[297] = 0;
   out_7596404610561457994[298] = 0;
   out_7596404610561457994[299] = 0;
   out_7596404610561457994[300] = 0;
   out_7596404610561457994[301] = 0;
   out_7596404610561457994[302] = 0;
   out_7596404610561457994[303] = 0;
   out_7596404610561457994[304] = 1;
   out_7596404610561457994[305] = 0;
   out_7596404610561457994[306] = 0;
   out_7596404610561457994[307] = 0;
   out_7596404610561457994[308] = 0;
   out_7596404610561457994[309] = 0;
   out_7596404610561457994[310] = 0;
   out_7596404610561457994[311] = 0;
   out_7596404610561457994[312] = 0;
   out_7596404610561457994[313] = 0;
   out_7596404610561457994[314] = 0;
   out_7596404610561457994[315] = 0;
   out_7596404610561457994[316] = 0;
   out_7596404610561457994[317] = 0;
   out_7596404610561457994[318] = 0;
   out_7596404610561457994[319] = 0;
   out_7596404610561457994[320] = 0;
   out_7596404610561457994[321] = 0;
   out_7596404610561457994[322] = 0;
   out_7596404610561457994[323] = 1;
}
void h_4(double *state, double *unused, double *out_5750154137532103835) {
   out_5750154137532103835[0] = state[6] + state[9];
   out_5750154137532103835[1] = state[7] + state[10];
   out_5750154137532103835[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3379360790069932960) {
   out_3379360790069932960[0] = 0;
   out_3379360790069932960[1] = 0;
   out_3379360790069932960[2] = 0;
   out_3379360790069932960[3] = 0;
   out_3379360790069932960[4] = 0;
   out_3379360790069932960[5] = 0;
   out_3379360790069932960[6] = 1;
   out_3379360790069932960[7] = 0;
   out_3379360790069932960[8] = 0;
   out_3379360790069932960[9] = 1;
   out_3379360790069932960[10] = 0;
   out_3379360790069932960[11] = 0;
   out_3379360790069932960[12] = 0;
   out_3379360790069932960[13] = 0;
   out_3379360790069932960[14] = 0;
   out_3379360790069932960[15] = 0;
   out_3379360790069932960[16] = 0;
   out_3379360790069932960[17] = 0;
   out_3379360790069932960[18] = 0;
   out_3379360790069932960[19] = 0;
   out_3379360790069932960[20] = 0;
   out_3379360790069932960[21] = 0;
   out_3379360790069932960[22] = 0;
   out_3379360790069932960[23] = 0;
   out_3379360790069932960[24] = 0;
   out_3379360790069932960[25] = 1;
   out_3379360790069932960[26] = 0;
   out_3379360790069932960[27] = 0;
   out_3379360790069932960[28] = 1;
   out_3379360790069932960[29] = 0;
   out_3379360790069932960[30] = 0;
   out_3379360790069932960[31] = 0;
   out_3379360790069932960[32] = 0;
   out_3379360790069932960[33] = 0;
   out_3379360790069932960[34] = 0;
   out_3379360790069932960[35] = 0;
   out_3379360790069932960[36] = 0;
   out_3379360790069932960[37] = 0;
   out_3379360790069932960[38] = 0;
   out_3379360790069932960[39] = 0;
   out_3379360790069932960[40] = 0;
   out_3379360790069932960[41] = 0;
   out_3379360790069932960[42] = 0;
   out_3379360790069932960[43] = 0;
   out_3379360790069932960[44] = 1;
   out_3379360790069932960[45] = 0;
   out_3379360790069932960[46] = 0;
   out_3379360790069932960[47] = 1;
   out_3379360790069932960[48] = 0;
   out_3379360790069932960[49] = 0;
   out_3379360790069932960[50] = 0;
   out_3379360790069932960[51] = 0;
   out_3379360790069932960[52] = 0;
   out_3379360790069932960[53] = 0;
}
void h_10(double *state, double *unused, double *out_679948980304854494) {
   out_679948980304854494[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_679948980304854494[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_679948980304854494[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1607857339266867784) {
   out_1607857339266867784[0] = 0;
   out_1607857339266867784[1] = 9.8100000000000005*cos(state[1]);
   out_1607857339266867784[2] = 0;
   out_1607857339266867784[3] = 0;
   out_1607857339266867784[4] = -state[8];
   out_1607857339266867784[5] = state[7];
   out_1607857339266867784[6] = 0;
   out_1607857339266867784[7] = state[5];
   out_1607857339266867784[8] = -state[4];
   out_1607857339266867784[9] = 0;
   out_1607857339266867784[10] = 0;
   out_1607857339266867784[11] = 0;
   out_1607857339266867784[12] = 1;
   out_1607857339266867784[13] = 0;
   out_1607857339266867784[14] = 0;
   out_1607857339266867784[15] = 1;
   out_1607857339266867784[16] = 0;
   out_1607857339266867784[17] = 0;
   out_1607857339266867784[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1607857339266867784[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1607857339266867784[20] = 0;
   out_1607857339266867784[21] = state[8];
   out_1607857339266867784[22] = 0;
   out_1607857339266867784[23] = -state[6];
   out_1607857339266867784[24] = -state[5];
   out_1607857339266867784[25] = 0;
   out_1607857339266867784[26] = state[3];
   out_1607857339266867784[27] = 0;
   out_1607857339266867784[28] = 0;
   out_1607857339266867784[29] = 0;
   out_1607857339266867784[30] = 0;
   out_1607857339266867784[31] = 1;
   out_1607857339266867784[32] = 0;
   out_1607857339266867784[33] = 0;
   out_1607857339266867784[34] = 1;
   out_1607857339266867784[35] = 0;
   out_1607857339266867784[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1607857339266867784[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1607857339266867784[38] = 0;
   out_1607857339266867784[39] = -state[7];
   out_1607857339266867784[40] = state[6];
   out_1607857339266867784[41] = 0;
   out_1607857339266867784[42] = state[4];
   out_1607857339266867784[43] = -state[3];
   out_1607857339266867784[44] = 0;
   out_1607857339266867784[45] = 0;
   out_1607857339266867784[46] = 0;
   out_1607857339266867784[47] = 0;
   out_1607857339266867784[48] = 0;
   out_1607857339266867784[49] = 0;
   out_1607857339266867784[50] = 1;
   out_1607857339266867784[51] = 0;
   out_1607857339266867784[52] = 0;
   out_1607857339266867784[53] = 1;
}
void h_13(double *state, double *unused, double *out_312393418504685067) {
   out_312393418504685067[0] = state[3];
   out_312393418504685067[1] = state[4];
   out_312393418504685067[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6591634615402265761) {
   out_6591634615402265761[0] = 0;
   out_6591634615402265761[1] = 0;
   out_6591634615402265761[2] = 0;
   out_6591634615402265761[3] = 1;
   out_6591634615402265761[4] = 0;
   out_6591634615402265761[5] = 0;
   out_6591634615402265761[6] = 0;
   out_6591634615402265761[7] = 0;
   out_6591634615402265761[8] = 0;
   out_6591634615402265761[9] = 0;
   out_6591634615402265761[10] = 0;
   out_6591634615402265761[11] = 0;
   out_6591634615402265761[12] = 0;
   out_6591634615402265761[13] = 0;
   out_6591634615402265761[14] = 0;
   out_6591634615402265761[15] = 0;
   out_6591634615402265761[16] = 0;
   out_6591634615402265761[17] = 0;
   out_6591634615402265761[18] = 0;
   out_6591634615402265761[19] = 0;
   out_6591634615402265761[20] = 0;
   out_6591634615402265761[21] = 0;
   out_6591634615402265761[22] = 1;
   out_6591634615402265761[23] = 0;
   out_6591634615402265761[24] = 0;
   out_6591634615402265761[25] = 0;
   out_6591634615402265761[26] = 0;
   out_6591634615402265761[27] = 0;
   out_6591634615402265761[28] = 0;
   out_6591634615402265761[29] = 0;
   out_6591634615402265761[30] = 0;
   out_6591634615402265761[31] = 0;
   out_6591634615402265761[32] = 0;
   out_6591634615402265761[33] = 0;
   out_6591634615402265761[34] = 0;
   out_6591634615402265761[35] = 0;
   out_6591634615402265761[36] = 0;
   out_6591634615402265761[37] = 0;
   out_6591634615402265761[38] = 0;
   out_6591634615402265761[39] = 0;
   out_6591634615402265761[40] = 0;
   out_6591634615402265761[41] = 1;
   out_6591634615402265761[42] = 0;
   out_6591634615402265761[43] = 0;
   out_6591634615402265761[44] = 0;
   out_6591634615402265761[45] = 0;
   out_6591634615402265761[46] = 0;
   out_6591634615402265761[47] = 0;
   out_6591634615402265761[48] = 0;
   out_6591634615402265761[49] = 0;
   out_6591634615402265761[50] = 0;
   out_6591634615402265761[51] = 0;
   out_6591634615402265761[52] = 0;
   out_6591634615402265761[53] = 0;
}
void h_14(double *state, double *unused, double *out_5563868255163517085) {
   out_5563868255163517085[0] = state[6];
   out_5563868255163517085[1] = state[7];
   out_5563868255163517085[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7342601646409417489) {
   out_7342601646409417489[0] = 0;
   out_7342601646409417489[1] = 0;
   out_7342601646409417489[2] = 0;
   out_7342601646409417489[3] = 0;
   out_7342601646409417489[4] = 0;
   out_7342601646409417489[5] = 0;
   out_7342601646409417489[6] = 1;
   out_7342601646409417489[7] = 0;
   out_7342601646409417489[8] = 0;
   out_7342601646409417489[9] = 0;
   out_7342601646409417489[10] = 0;
   out_7342601646409417489[11] = 0;
   out_7342601646409417489[12] = 0;
   out_7342601646409417489[13] = 0;
   out_7342601646409417489[14] = 0;
   out_7342601646409417489[15] = 0;
   out_7342601646409417489[16] = 0;
   out_7342601646409417489[17] = 0;
   out_7342601646409417489[18] = 0;
   out_7342601646409417489[19] = 0;
   out_7342601646409417489[20] = 0;
   out_7342601646409417489[21] = 0;
   out_7342601646409417489[22] = 0;
   out_7342601646409417489[23] = 0;
   out_7342601646409417489[24] = 0;
   out_7342601646409417489[25] = 1;
   out_7342601646409417489[26] = 0;
   out_7342601646409417489[27] = 0;
   out_7342601646409417489[28] = 0;
   out_7342601646409417489[29] = 0;
   out_7342601646409417489[30] = 0;
   out_7342601646409417489[31] = 0;
   out_7342601646409417489[32] = 0;
   out_7342601646409417489[33] = 0;
   out_7342601646409417489[34] = 0;
   out_7342601646409417489[35] = 0;
   out_7342601646409417489[36] = 0;
   out_7342601646409417489[37] = 0;
   out_7342601646409417489[38] = 0;
   out_7342601646409417489[39] = 0;
   out_7342601646409417489[40] = 0;
   out_7342601646409417489[41] = 0;
   out_7342601646409417489[42] = 0;
   out_7342601646409417489[43] = 0;
   out_7342601646409417489[44] = 1;
   out_7342601646409417489[45] = 0;
   out_7342601646409417489[46] = 0;
   out_7342601646409417489[47] = 0;
   out_7342601646409417489[48] = 0;
   out_7342601646409417489[49] = 0;
   out_7342601646409417489[50] = 0;
   out_7342601646409417489[51] = 0;
   out_7342601646409417489[52] = 0;
   out_7342601646409417489[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8269927985032062752) {
  err_fun(nom_x, delta_x, out_8269927985032062752);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7882321665795113097) {
  inv_err_fun(nom_x, true_x, out_7882321665795113097);
}
void pose_H_mod_fun(double *state, double *out_2625199788015220353) {
  H_mod_fun(state, out_2625199788015220353);
}
void pose_f_fun(double *state, double dt, double *out_2756784837860721128) {
  f_fun(state,  dt, out_2756784837860721128);
}
void pose_F_fun(double *state, double dt, double *out_7596404610561457994) {
  F_fun(state,  dt, out_7596404610561457994);
}
void pose_h_4(double *state, double *unused, double *out_5750154137532103835) {
  h_4(state, unused, out_5750154137532103835);
}
void pose_H_4(double *state, double *unused, double *out_3379360790069932960) {
  H_4(state, unused, out_3379360790069932960);
}
void pose_h_10(double *state, double *unused, double *out_679948980304854494) {
  h_10(state, unused, out_679948980304854494);
}
void pose_H_10(double *state, double *unused, double *out_1607857339266867784) {
  H_10(state, unused, out_1607857339266867784);
}
void pose_h_13(double *state, double *unused, double *out_312393418504685067) {
  h_13(state, unused, out_312393418504685067);
}
void pose_H_13(double *state, double *unused, double *out_6591634615402265761) {
  H_13(state, unused, out_6591634615402265761);
}
void pose_h_14(double *state, double *unused, double *out_5563868255163517085) {
  h_14(state, unused, out_5563868255163517085);
}
void pose_H_14(double *state, double *unused, double *out_7342601646409417489) {
  H_14(state, unused, out_7342601646409417489);
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
