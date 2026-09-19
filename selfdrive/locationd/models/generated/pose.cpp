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
void err_fun(double *nom_x, double *delta_x, double *out_7239197641731070156) {
   out_7239197641731070156[0] = delta_x[0] + nom_x[0];
   out_7239197641731070156[1] = delta_x[1] + nom_x[1];
   out_7239197641731070156[2] = delta_x[2] + nom_x[2];
   out_7239197641731070156[3] = delta_x[3] + nom_x[3];
   out_7239197641731070156[4] = delta_x[4] + nom_x[4];
   out_7239197641731070156[5] = delta_x[5] + nom_x[5];
   out_7239197641731070156[6] = delta_x[6] + nom_x[6];
   out_7239197641731070156[7] = delta_x[7] + nom_x[7];
   out_7239197641731070156[8] = delta_x[8] + nom_x[8];
   out_7239197641731070156[9] = delta_x[9] + nom_x[9];
   out_7239197641731070156[10] = delta_x[10] + nom_x[10];
   out_7239197641731070156[11] = delta_x[11] + nom_x[11];
   out_7239197641731070156[12] = delta_x[12] + nom_x[12];
   out_7239197641731070156[13] = delta_x[13] + nom_x[13];
   out_7239197641731070156[14] = delta_x[14] + nom_x[14];
   out_7239197641731070156[15] = delta_x[15] + nom_x[15];
   out_7239197641731070156[16] = delta_x[16] + nom_x[16];
   out_7239197641731070156[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_217209870609913891) {
   out_217209870609913891[0] = -nom_x[0] + true_x[0];
   out_217209870609913891[1] = -nom_x[1] + true_x[1];
   out_217209870609913891[2] = -nom_x[2] + true_x[2];
   out_217209870609913891[3] = -nom_x[3] + true_x[3];
   out_217209870609913891[4] = -nom_x[4] + true_x[4];
   out_217209870609913891[5] = -nom_x[5] + true_x[5];
   out_217209870609913891[6] = -nom_x[6] + true_x[6];
   out_217209870609913891[7] = -nom_x[7] + true_x[7];
   out_217209870609913891[8] = -nom_x[8] + true_x[8];
   out_217209870609913891[9] = -nom_x[9] + true_x[9];
   out_217209870609913891[10] = -nom_x[10] + true_x[10];
   out_217209870609913891[11] = -nom_x[11] + true_x[11];
   out_217209870609913891[12] = -nom_x[12] + true_x[12];
   out_217209870609913891[13] = -nom_x[13] + true_x[13];
   out_217209870609913891[14] = -nom_x[14] + true_x[14];
   out_217209870609913891[15] = -nom_x[15] + true_x[15];
   out_217209870609913891[16] = -nom_x[16] + true_x[16];
   out_217209870609913891[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8844683690844308926) {
   out_8844683690844308926[0] = 1.0;
   out_8844683690844308926[1] = 0.0;
   out_8844683690844308926[2] = 0.0;
   out_8844683690844308926[3] = 0.0;
   out_8844683690844308926[4] = 0.0;
   out_8844683690844308926[5] = 0.0;
   out_8844683690844308926[6] = 0.0;
   out_8844683690844308926[7] = 0.0;
   out_8844683690844308926[8] = 0.0;
   out_8844683690844308926[9] = 0.0;
   out_8844683690844308926[10] = 0.0;
   out_8844683690844308926[11] = 0.0;
   out_8844683690844308926[12] = 0.0;
   out_8844683690844308926[13] = 0.0;
   out_8844683690844308926[14] = 0.0;
   out_8844683690844308926[15] = 0.0;
   out_8844683690844308926[16] = 0.0;
   out_8844683690844308926[17] = 0.0;
   out_8844683690844308926[18] = 0.0;
   out_8844683690844308926[19] = 1.0;
   out_8844683690844308926[20] = 0.0;
   out_8844683690844308926[21] = 0.0;
   out_8844683690844308926[22] = 0.0;
   out_8844683690844308926[23] = 0.0;
   out_8844683690844308926[24] = 0.0;
   out_8844683690844308926[25] = 0.0;
   out_8844683690844308926[26] = 0.0;
   out_8844683690844308926[27] = 0.0;
   out_8844683690844308926[28] = 0.0;
   out_8844683690844308926[29] = 0.0;
   out_8844683690844308926[30] = 0.0;
   out_8844683690844308926[31] = 0.0;
   out_8844683690844308926[32] = 0.0;
   out_8844683690844308926[33] = 0.0;
   out_8844683690844308926[34] = 0.0;
   out_8844683690844308926[35] = 0.0;
   out_8844683690844308926[36] = 0.0;
   out_8844683690844308926[37] = 0.0;
   out_8844683690844308926[38] = 1.0;
   out_8844683690844308926[39] = 0.0;
   out_8844683690844308926[40] = 0.0;
   out_8844683690844308926[41] = 0.0;
   out_8844683690844308926[42] = 0.0;
   out_8844683690844308926[43] = 0.0;
   out_8844683690844308926[44] = 0.0;
   out_8844683690844308926[45] = 0.0;
   out_8844683690844308926[46] = 0.0;
   out_8844683690844308926[47] = 0.0;
   out_8844683690844308926[48] = 0.0;
   out_8844683690844308926[49] = 0.0;
   out_8844683690844308926[50] = 0.0;
   out_8844683690844308926[51] = 0.0;
   out_8844683690844308926[52] = 0.0;
   out_8844683690844308926[53] = 0.0;
   out_8844683690844308926[54] = 0.0;
   out_8844683690844308926[55] = 0.0;
   out_8844683690844308926[56] = 0.0;
   out_8844683690844308926[57] = 1.0;
   out_8844683690844308926[58] = 0.0;
   out_8844683690844308926[59] = 0.0;
   out_8844683690844308926[60] = 0.0;
   out_8844683690844308926[61] = 0.0;
   out_8844683690844308926[62] = 0.0;
   out_8844683690844308926[63] = 0.0;
   out_8844683690844308926[64] = 0.0;
   out_8844683690844308926[65] = 0.0;
   out_8844683690844308926[66] = 0.0;
   out_8844683690844308926[67] = 0.0;
   out_8844683690844308926[68] = 0.0;
   out_8844683690844308926[69] = 0.0;
   out_8844683690844308926[70] = 0.0;
   out_8844683690844308926[71] = 0.0;
   out_8844683690844308926[72] = 0.0;
   out_8844683690844308926[73] = 0.0;
   out_8844683690844308926[74] = 0.0;
   out_8844683690844308926[75] = 0.0;
   out_8844683690844308926[76] = 1.0;
   out_8844683690844308926[77] = 0.0;
   out_8844683690844308926[78] = 0.0;
   out_8844683690844308926[79] = 0.0;
   out_8844683690844308926[80] = 0.0;
   out_8844683690844308926[81] = 0.0;
   out_8844683690844308926[82] = 0.0;
   out_8844683690844308926[83] = 0.0;
   out_8844683690844308926[84] = 0.0;
   out_8844683690844308926[85] = 0.0;
   out_8844683690844308926[86] = 0.0;
   out_8844683690844308926[87] = 0.0;
   out_8844683690844308926[88] = 0.0;
   out_8844683690844308926[89] = 0.0;
   out_8844683690844308926[90] = 0.0;
   out_8844683690844308926[91] = 0.0;
   out_8844683690844308926[92] = 0.0;
   out_8844683690844308926[93] = 0.0;
   out_8844683690844308926[94] = 0.0;
   out_8844683690844308926[95] = 1.0;
   out_8844683690844308926[96] = 0.0;
   out_8844683690844308926[97] = 0.0;
   out_8844683690844308926[98] = 0.0;
   out_8844683690844308926[99] = 0.0;
   out_8844683690844308926[100] = 0.0;
   out_8844683690844308926[101] = 0.0;
   out_8844683690844308926[102] = 0.0;
   out_8844683690844308926[103] = 0.0;
   out_8844683690844308926[104] = 0.0;
   out_8844683690844308926[105] = 0.0;
   out_8844683690844308926[106] = 0.0;
   out_8844683690844308926[107] = 0.0;
   out_8844683690844308926[108] = 0.0;
   out_8844683690844308926[109] = 0.0;
   out_8844683690844308926[110] = 0.0;
   out_8844683690844308926[111] = 0.0;
   out_8844683690844308926[112] = 0.0;
   out_8844683690844308926[113] = 0.0;
   out_8844683690844308926[114] = 1.0;
   out_8844683690844308926[115] = 0.0;
   out_8844683690844308926[116] = 0.0;
   out_8844683690844308926[117] = 0.0;
   out_8844683690844308926[118] = 0.0;
   out_8844683690844308926[119] = 0.0;
   out_8844683690844308926[120] = 0.0;
   out_8844683690844308926[121] = 0.0;
   out_8844683690844308926[122] = 0.0;
   out_8844683690844308926[123] = 0.0;
   out_8844683690844308926[124] = 0.0;
   out_8844683690844308926[125] = 0.0;
   out_8844683690844308926[126] = 0.0;
   out_8844683690844308926[127] = 0.0;
   out_8844683690844308926[128] = 0.0;
   out_8844683690844308926[129] = 0.0;
   out_8844683690844308926[130] = 0.0;
   out_8844683690844308926[131] = 0.0;
   out_8844683690844308926[132] = 0.0;
   out_8844683690844308926[133] = 1.0;
   out_8844683690844308926[134] = 0.0;
   out_8844683690844308926[135] = 0.0;
   out_8844683690844308926[136] = 0.0;
   out_8844683690844308926[137] = 0.0;
   out_8844683690844308926[138] = 0.0;
   out_8844683690844308926[139] = 0.0;
   out_8844683690844308926[140] = 0.0;
   out_8844683690844308926[141] = 0.0;
   out_8844683690844308926[142] = 0.0;
   out_8844683690844308926[143] = 0.0;
   out_8844683690844308926[144] = 0.0;
   out_8844683690844308926[145] = 0.0;
   out_8844683690844308926[146] = 0.0;
   out_8844683690844308926[147] = 0.0;
   out_8844683690844308926[148] = 0.0;
   out_8844683690844308926[149] = 0.0;
   out_8844683690844308926[150] = 0.0;
   out_8844683690844308926[151] = 0.0;
   out_8844683690844308926[152] = 1.0;
   out_8844683690844308926[153] = 0.0;
   out_8844683690844308926[154] = 0.0;
   out_8844683690844308926[155] = 0.0;
   out_8844683690844308926[156] = 0.0;
   out_8844683690844308926[157] = 0.0;
   out_8844683690844308926[158] = 0.0;
   out_8844683690844308926[159] = 0.0;
   out_8844683690844308926[160] = 0.0;
   out_8844683690844308926[161] = 0.0;
   out_8844683690844308926[162] = 0.0;
   out_8844683690844308926[163] = 0.0;
   out_8844683690844308926[164] = 0.0;
   out_8844683690844308926[165] = 0.0;
   out_8844683690844308926[166] = 0.0;
   out_8844683690844308926[167] = 0.0;
   out_8844683690844308926[168] = 0.0;
   out_8844683690844308926[169] = 0.0;
   out_8844683690844308926[170] = 0.0;
   out_8844683690844308926[171] = 1.0;
   out_8844683690844308926[172] = 0.0;
   out_8844683690844308926[173] = 0.0;
   out_8844683690844308926[174] = 0.0;
   out_8844683690844308926[175] = 0.0;
   out_8844683690844308926[176] = 0.0;
   out_8844683690844308926[177] = 0.0;
   out_8844683690844308926[178] = 0.0;
   out_8844683690844308926[179] = 0.0;
   out_8844683690844308926[180] = 0.0;
   out_8844683690844308926[181] = 0.0;
   out_8844683690844308926[182] = 0.0;
   out_8844683690844308926[183] = 0.0;
   out_8844683690844308926[184] = 0.0;
   out_8844683690844308926[185] = 0.0;
   out_8844683690844308926[186] = 0.0;
   out_8844683690844308926[187] = 0.0;
   out_8844683690844308926[188] = 0.0;
   out_8844683690844308926[189] = 0.0;
   out_8844683690844308926[190] = 1.0;
   out_8844683690844308926[191] = 0.0;
   out_8844683690844308926[192] = 0.0;
   out_8844683690844308926[193] = 0.0;
   out_8844683690844308926[194] = 0.0;
   out_8844683690844308926[195] = 0.0;
   out_8844683690844308926[196] = 0.0;
   out_8844683690844308926[197] = 0.0;
   out_8844683690844308926[198] = 0.0;
   out_8844683690844308926[199] = 0.0;
   out_8844683690844308926[200] = 0.0;
   out_8844683690844308926[201] = 0.0;
   out_8844683690844308926[202] = 0.0;
   out_8844683690844308926[203] = 0.0;
   out_8844683690844308926[204] = 0.0;
   out_8844683690844308926[205] = 0.0;
   out_8844683690844308926[206] = 0.0;
   out_8844683690844308926[207] = 0.0;
   out_8844683690844308926[208] = 0.0;
   out_8844683690844308926[209] = 1.0;
   out_8844683690844308926[210] = 0.0;
   out_8844683690844308926[211] = 0.0;
   out_8844683690844308926[212] = 0.0;
   out_8844683690844308926[213] = 0.0;
   out_8844683690844308926[214] = 0.0;
   out_8844683690844308926[215] = 0.0;
   out_8844683690844308926[216] = 0.0;
   out_8844683690844308926[217] = 0.0;
   out_8844683690844308926[218] = 0.0;
   out_8844683690844308926[219] = 0.0;
   out_8844683690844308926[220] = 0.0;
   out_8844683690844308926[221] = 0.0;
   out_8844683690844308926[222] = 0.0;
   out_8844683690844308926[223] = 0.0;
   out_8844683690844308926[224] = 0.0;
   out_8844683690844308926[225] = 0.0;
   out_8844683690844308926[226] = 0.0;
   out_8844683690844308926[227] = 0.0;
   out_8844683690844308926[228] = 1.0;
   out_8844683690844308926[229] = 0.0;
   out_8844683690844308926[230] = 0.0;
   out_8844683690844308926[231] = 0.0;
   out_8844683690844308926[232] = 0.0;
   out_8844683690844308926[233] = 0.0;
   out_8844683690844308926[234] = 0.0;
   out_8844683690844308926[235] = 0.0;
   out_8844683690844308926[236] = 0.0;
   out_8844683690844308926[237] = 0.0;
   out_8844683690844308926[238] = 0.0;
   out_8844683690844308926[239] = 0.0;
   out_8844683690844308926[240] = 0.0;
   out_8844683690844308926[241] = 0.0;
   out_8844683690844308926[242] = 0.0;
   out_8844683690844308926[243] = 0.0;
   out_8844683690844308926[244] = 0.0;
   out_8844683690844308926[245] = 0.0;
   out_8844683690844308926[246] = 0.0;
   out_8844683690844308926[247] = 1.0;
   out_8844683690844308926[248] = 0.0;
   out_8844683690844308926[249] = 0.0;
   out_8844683690844308926[250] = 0.0;
   out_8844683690844308926[251] = 0.0;
   out_8844683690844308926[252] = 0.0;
   out_8844683690844308926[253] = 0.0;
   out_8844683690844308926[254] = 0.0;
   out_8844683690844308926[255] = 0.0;
   out_8844683690844308926[256] = 0.0;
   out_8844683690844308926[257] = 0.0;
   out_8844683690844308926[258] = 0.0;
   out_8844683690844308926[259] = 0.0;
   out_8844683690844308926[260] = 0.0;
   out_8844683690844308926[261] = 0.0;
   out_8844683690844308926[262] = 0.0;
   out_8844683690844308926[263] = 0.0;
   out_8844683690844308926[264] = 0.0;
   out_8844683690844308926[265] = 0.0;
   out_8844683690844308926[266] = 1.0;
   out_8844683690844308926[267] = 0.0;
   out_8844683690844308926[268] = 0.0;
   out_8844683690844308926[269] = 0.0;
   out_8844683690844308926[270] = 0.0;
   out_8844683690844308926[271] = 0.0;
   out_8844683690844308926[272] = 0.0;
   out_8844683690844308926[273] = 0.0;
   out_8844683690844308926[274] = 0.0;
   out_8844683690844308926[275] = 0.0;
   out_8844683690844308926[276] = 0.0;
   out_8844683690844308926[277] = 0.0;
   out_8844683690844308926[278] = 0.0;
   out_8844683690844308926[279] = 0.0;
   out_8844683690844308926[280] = 0.0;
   out_8844683690844308926[281] = 0.0;
   out_8844683690844308926[282] = 0.0;
   out_8844683690844308926[283] = 0.0;
   out_8844683690844308926[284] = 0.0;
   out_8844683690844308926[285] = 1.0;
   out_8844683690844308926[286] = 0.0;
   out_8844683690844308926[287] = 0.0;
   out_8844683690844308926[288] = 0.0;
   out_8844683690844308926[289] = 0.0;
   out_8844683690844308926[290] = 0.0;
   out_8844683690844308926[291] = 0.0;
   out_8844683690844308926[292] = 0.0;
   out_8844683690844308926[293] = 0.0;
   out_8844683690844308926[294] = 0.0;
   out_8844683690844308926[295] = 0.0;
   out_8844683690844308926[296] = 0.0;
   out_8844683690844308926[297] = 0.0;
   out_8844683690844308926[298] = 0.0;
   out_8844683690844308926[299] = 0.0;
   out_8844683690844308926[300] = 0.0;
   out_8844683690844308926[301] = 0.0;
   out_8844683690844308926[302] = 0.0;
   out_8844683690844308926[303] = 0.0;
   out_8844683690844308926[304] = 1.0;
   out_8844683690844308926[305] = 0.0;
   out_8844683690844308926[306] = 0.0;
   out_8844683690844308926[307] = 0.0;
   out_8844683690844308926[308] = 0.0;
   out_8844683690844308926[309] = 0.0;
   out_8844683690844308926[310] = 0.0;
   out_8844683690844308926[311] = 0.0;
   out_8844683690844308926[312] = 0.0;
   out_8844683690844308926[313] = 0.0;
   out_8844683690844308926[314] = 0.0;
   out_8844683690844308926[315] = 0.0;
   out_8844683690844308926[316] = 0.0;
   out_8844683690844308926[317] = 0.0;
   out_8844683690844308926[318] = 0.0;
   out_8844683690844308926[319] = 0.0;
   out_8844683690844308926[320] = 0.0;
   out_8844683690844308926[321] = 0.0;
   out_8844683690844308926[322] = 0.0;
   out_8844683690844308926[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_371859905987646833) {
   out_371859905987646833[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_371859905987646833[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_371859905987646833[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_371859905987646833[3] = dt*state[12] + state[3];
   out_371859905987646833[4] = dt*state[13] + state[4];
   out_371859905987646833[5] = dt*state[14] + state[5];
   out_371859905987646833[6] = state[6];
   out_371859905987646833[7] = state[7];
   out_371859905987646833[8] = state[8];
   out_371859905987646833[9] = state[9];
   out_371859905987646833[10] = state[10];
   out_371859905987646833[11] = state[11];
   out_371859905987646833[12] = state[12];
   out_371859905987646833[13] = state[13];
   out_371859905987646833[14] = state[14];
   out_371859905987646833[15] = state[15];
   out_371859905987646833[16] = state[16];
   out_371859905987646833[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5262243657608806363) {
   out_5262243657608806363[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5262243657608806363[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5262243657608806363[2] = 0;
   out_5262243657608806363[3] = 0;
   out_5262243657608806363[4] = 0;
   out_5262243657608806363[5] = 0;
   out_5262243657608806363[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5262243657608806363[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5262243657608806363[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5262243657608806363[9] = 0;
   out_5262243657608806363[10] = 0;
   out_5262243657608806363[11] = 0;
   out_5262243657608806363[12] = 0;
   out_5262243657608806363[13] = 0;
   out_5262243657608806363[14] = 0;
   out_5262243657608806363[15] = 0;
   out_5262243657608806363[16] = 0;
   out_5262243657608806363[17] = 0;
   out_5262243657608806363[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5262243657608806363[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5262243657608806363[20] = 0;
   out_5262243657608806363[21] = 0;
   out_5262243657608806363[22] = 0;
   out_5262243657608806363[23] = 0;
   out_5262243657608806363[24] = 0;
   out_5262243657608806363[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5262243657608806363[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5262243657608806363[27] = 0;
   out_5262243657608806363[28] = 0;
   out_5262243657608806363[29] = 0;
   out_5262243657608806363[30] = 0;
   out_5262243657608806363[31] = 0;
   out_5262243657608806363[32] = 0;
   out_5262243657608806363[33] = 0;
   out_5262243657608806363[34] = 0;
   out_5262243657608806363[35] = 0;
   out_5262243657608806363[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5262243657608806363[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5262243657608806363[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5262243657608806363[39] = 0;
   out_5262243657608806363[40] = 0;
   out_5262243657608806363[41] = 0;
   out_5262243657608806363[42] = 0;
   out_5262243657608806363[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5262243657608806363[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5262243657608806363[45] = 0;
   out_5262243657608806363[46] = 0;
   out_5262243657608806363[47] = 0;
   out_5262243657608806363[48] = 0;
   out_5262243657608806363[49] = 0;
   out_5262243657608806363[50] = 0;
   out_5262243657608806363[51] = 0;
   out_5262243657608806363[52] = 0;
   out_5262243657608806363[53] = 0;
   out_5262243657608806363[54] = 0;
   out_5262243657608806363[55] = 0;
   out_5262243657608806363[56] = 0;
   out_5262243657608806363[57] = 1;
   out_5262243657608806363[58] = 0;
   out_5262243657608806363[59] = 0;
   out_5262243657608806363[60] = 0;
   out_5262243657608806363[61] = 0;
   out_5262243657608806363[62] = 0;
   out_5262243657608806363[63] = 0;
   out_5262243657608806363[64] = 0;
   out_5262243657608806363[65] = 0;
   out_5262243657608806363[66] = dt;
   out_5262243657608806363[67] = 0;
   out_5262243657608806363[68] = 0;
   out_5262243657608806363[69] = 0;
   out_5262243657608806363[70] = 0;
   out_5262243657608806363[71] = 0;
   out_5262243657608806363[72] = 0;
   out_5262243657608806363[73] = 0;
   out_5262243657608806363[74] = 0;
   out_5262243657608806363[75] = 0;
   out_5262243657608806363[76] = 1;
   out_5262243657608806363[77] = 0;
   out_5262243657608806363[78] = 0;
   out_5262243657608806363[79] = 0;
   out_5262243657608806363[80] = 0;
   out_5262243657608806363[81] = 0;
   out_5262243657608806363[82] = 0;
   out_5262243657608806363[83] = 0;
   out_5262243657608806363[84] = 0;
   out_5262243657608806363[85] = dt;
   out_5262243657608806363[86] = 0;
   out_5262243657608806363[87] = 0;
   out_5262243657608806363[88] = 0;
   out_5262243657608806363[89] = 0;
   out_5262243657608806363[90] = 0;
   out_5262243657608806363[91] = 0;
   out_5262243657608806363[92] = 0;
   out_5262243657608806363[93] = 0;
   out_5262243657608806363[94] = 0;
   out_5262243657608806363[95] = 1;
   out_5262243657608806363[96] = 0;
   out_5262243657608806363[97] = 0;
   out_5262243657608806363[98] = 0;
   out_5262243657608806363[99] = 0;
   out_5262243657608806363[100] = 0;
   out_5262243657608806363[101] = 0;
   out_5262243657608806363[102] = 0;
   out_5262243657608806363[103] = 0;
   out_5262243657608806363[104] = dt;
   out_5262243657608806363[105] = 0;
   out_5262243657608806363[106] = 0;
   out_5262243657608806363[107] = 0;
   out_5262243657608806363[108] = 0;
   out_5262243657608806363[109] = 0;
   out_5262243657608806363[110] = 0;
   out_5262243657608806363[111] = 0;
   out_5262243657608806363[112] = 0;
   out_5262243657608806363[113] = 0;
   out_5262243657608806363[114] = 1;
   out_5262243657608806363[115] = 0;
   out_5262243657608806363[116] = 0;
   out_5262243657608806363[117] = 0;
   out_5262243657608806363[118] = 0;
   out_5262243657608806363[119] = 0;
   out_5262243657608806363[120] = 0;
   out_5262243657608806363[121] = 0;
   out_5262243657608806363[122] = 0;
   out_5262243657608806363[123] = 0;
   out_5262243657608806363[124] = 0;
   out_5262243657608806363[125] = 0;
   out_5262243657608806363[126] = 0;
   out_5262243657608806363[127] = 0;
   out_5262243657608806363[128] = 0;
   out_5262243657608806363[129] = 0;
   out_5262243657608806363[130] = 0;
   out_5262243657608806363[131] = 0;
   out_5262243657608806363[132] = 0;
   out_5262243657608806363[133] = 1;
   out_5262243657608806363[134] = 0;
   out_5262243657608806363[135] = 0;
   out_5262243657608806363[136] = 0;
   out_5262243657608806363[137] = 0;
   out_5262243657608806363[138] = 0;
   out_5262243657608806363[139] = 0;
   out_5262243657608806363[140] = 0;
   out_5262243657608806363[141] = 0;
   out_5262243657608806363[142] = 0;
   out_5262243657608806363[143] = 0;
   out_5262243657608806363[144] = 0;
   out_5262243657608806363[145] = 0;
   out_5262243657608806363[146] = 0;
   out_5262243657608806363[147] = 0;
   out_5262243657608806363[148] = 0;
   out_5262243657608806363[149] = 0;
   out_5262243657608806363[150] = 0;
   out_5262243657608806363[151] = 0;
   out_5262243657608806363[152] = 1;
   out_5262243657608806363[153] = 0;
   out_5262243657608806363[154] = 0;
   out_5262243657608806363[155] = 0;
   out_5262243657608806363[156] = 0;
   out_5262243657608806363[157] = 0;
   out_5262243657608806363[158] = 0;
   out_5262243657608806363[159] = 0;
   out_5262243657608806363[160] = 0;
   out_5262243657608806363[161] = 0;
   out_5262243657608806363[162] = 0;
   out_5262243657608806363[163] = 0;
   out_5262243657608806363[164] = 0;
   out_5262243657608806363[165] = 0;
   out_5262243657608806363[166] = 0;
   out_5262243657608806363[167] = 0;
   out_5262243657608806363[168] = 0;
   out_5262243657608806363[169] = 0;
   out_5262243657608806363[170] = 0;
   out_5262243657608806363[171] = 1;
   out_5262243657608806363[172] = 0;
   out_5262243657608806363[173] = 0;
   out_5262243657608806363[174] = 0;
   out_5262243657608806363[175] = 0;
   out_5262243657608806363[176] = 0;
   out_5262243657608806363[177] = 0;
   out_5262243657608806363[178] = 0;
   out_5262243657608806363[179] = 0;
   out_5262243657608806363[180] = 0;
   out_5262243657608806363[181] = 0;
   out_5262243657608806363[182] = 0;
   out_5262243657608806363[183] = 0;
   out_5262243657608806363[184] = 0;
   out_5262243657608806363[185] = 0;
   out_5262243657608806363[186] = 0;
   out_5262243657608806363[187] = 0;
   out_5262243657608806363[188] = 0;
   out_5262243657608806363[189] = 0;
   out_5262243657608806363[190] = 1;
   out_5262243657608806363[191] = 0;
   out_5262243657608806363[192] = 0;
   out_5262243657608806363[193] = 0;
   out_5262243657608806363[194] = 0;
   out_5262243657608806363[195] = 0;
   out_5262243657608806363[196] = 0;
   out_5262243657608806363[197] = 0;
   out_5262243657608806363[198] = 0;
   out_5262243657608806363[199] = 0;
   out_5262243657608806363[200] = 0;
   out_5262243657608806363[201] = 0;
   out_5262243657608806363[202] = 0;
   out_5262243657608806363[203] = 0;
   out_5262243657608806363[204] = 0;
   out_5262243657608806363[205] = 0;
   out_5262243657608806363[206] = 0;
   out_5262243657608806363[207] = 0;
   out_5262243657608806363[208] = 0;
   out_5262243657608806363[209] = 1;
   out_5262243657608806363[210] = 0;
   out_5262243657608806363[211] = 0;
   out_5262243657608806363[212] = 0;
   out_5262243657608806363[213] = 0;
   out_5262243657608806363[214] = 0;
   out_5262243657608806363[215] = 0;
   out_5262243657608806363[216] = 0;
   out_5262243657608806363[217] = 0;
   out_5262243657608806363[218] = 0;
   out_5262243657608806363[219] = 0;
   out_5262243657608806363[220] = 0;
   out_5262243657608806363[221] = 0;
   out_5262243657608806363[222] = 0;
   out_5262243657608806363[223] = 0;
   out_5262243657608806363[224] = 0;
   out_5262243657608806363[225] = 0;
   out_5262243657608806363[226] = 0;
   out_5262243657608806363[227] = 0;
   out_5262243657608806363[228] = 1;
   out_5262243657608806363[229] = 0;
   out_5262243657608806363[230] = 0;
   out_5262243657608806363[231] = 0;
   out_5262243657608806363[232] = 0;
   out_5262243657608806363[233] = 0;
   out_5262243657608806363[234] = 0;
   out_5262243657608806363[235] = 0;
   out_5262243657608806363[236] = 0;
   out_5262243657608806363[237] = 0;
   out_5262243657608806363[238] = 0;
   out_5262243657608806363[239] = 0;
   out_5262243657608806363[240] = 0;
   out_5262243657608806363[241] = 0;
   out_5262243657608806363[242] = 0;
   out_5262243657608806363[243] = 0;
   out_5262243657608806363[244] = 0;
   out_5262243657608806363[245] = 0;
   out_5262243657608806363[246] = 0;
   out_5262243657608806363[247] = 1;
   out_5262243657608806363[248] = 0;
   out_5262243657608806363[249] = 0;
   out_5262243657608806363[250] = 0;
   out_5262243657608806363[251] = 0;
   out_5262243657608806363[252] = 0;
   out_5262243657608806363[253] = 0;
   out_5262243657608806363[254] = 0;
   out_5262243657608806363[255] = 0;
   out_5262243657608806363[256] = 0;
   out_5262243657608806363[257] = 0;
   out_5262243657608806363[258] = 0;
   out_5262243657608806363[259] = 0;
   out_5262243657608806363[260] = 0;
   out_5262243657608806363[261] = 0;
   out_5262243657608806363[262] = 0;
   out_5262243657608806363[263] = 0;
   out_5262243657608806363[264] = 0;
   out_5262243657608806363[265] = 0;
   out_5262243657608806363[266] = 1;
   out_5262243657608806363[267] = 0;
   out_5262243657608806363[268] = 0;
   out_5262243657608806363[269] = 0;
   out_5262243657608806363[270] = 0;
   out_5262243657608806363[271] = 0;
   out_5262243657608806363[272] = 0;
   out_5262243657608806363[273] = 0;
   out_5262243657608806363[274] = 0;
   out_5262243657608806363[275] = 0;
   out_5262243657608806363[276] = 0;
   out_5262243657608806363[277] = 0;
   out_5262243657608806363[278] = 0;
   out_5262243657608806363[279] = 0;
   out_5262243657608806363[280] = 0;
   out_5262243657608806363[281] = 0;
   out_5262243657608806363[282] = 0;
   out_5262243657608806363[283] = 0;
   out_5262243657608806363[284] = 0;
   out_5262243657608806363[285] = 1;
   out_5262243657608806363[286] = 0;
   out_5262243657608806363[287] = 0;
   out_5262243657608806363[288] = 0;
   out_5262243657608806363[289] = 0;
   out_5262243657608806363[290] = 0;
   out_5262243657608806363[291] = 0;
   out_5262243657608806363[292] = 0;
   out_5262243657608806363[293] = 0;
   out_5262243657608806363[294] = 0;
   out_5262243657608806363[295] = 0;
   out_5262243657608806363[296] = 0;
   out_5262243657608806363[297] = 0;
   out_5262243657608806363[298] = 0;
   out_5262243657608806363[299] = 0;
   out_5262243657608806363[300] = 0;
   out_5262243657608806363[301] = 0;
   out_5262243657608806363[302] = 0;
   out_5262243657608806363[303] = 0;
   out_5262243657608806363[304] = 1;
   out_5262243657608806363[305] = 0;
   out_5262243657608806363[306] = 0;
   out_5262243657608806363[307] = 0;
   out_5262243657608806363[308] = 0;
   out_5262243657608806363[309] = 0;
   out_5262243657608806363[310] = 0;
   out_5262243657608806363[311] = 0;
   out_5262243657608806363[312] = 0;
   out_5262243657608806363[313] = 0;
   out_5262243657608806363[314] = 0;
   out_5262243657608806363[315] = 0;
   out_5262243657608806363[316] = 0;
   out_5262243657608806363[317] = 0;
   out_5262243657608806363[318] = 0;
   out_5262243657608806363[319] = 0;
   out_5262243657608806363[320] = 0;
   out_5262243657608806363[321] = 0;
   out_5262243657608806363[322] = 0;
   out_5262243657608806363[323] = 1;
}
void h_4(double *state, double *unused, double *out_3538877410533377824) {
   out_3538877410533377824[0] = state[6] + state[9];
   out_3538877410533377824[1] = state[7] + state[10];
   out_3538877410533377824[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5830253173021335118) {
   out_5830253173021335118[0] = 0;
   out_5830253173021335118[1] = 0;
   out_5830253173021335118[2] = 0;
   out_5830253173021335118[3] = 0;
   out_5830253173021335118[4] = 0;
   out_5830253173021335118[5] = 0;
   out_5830253173021335118[6] = 1;
   out_5830253173021335118[7] = 0;
   out_5830253173021335118[8] = 0;
   out_5830253173021335118[9] = 1;
   out_5830253173021335118[10] = 0;
   out_5830253173021335118[11] = 0;
   out_5830253173021335118[12] = 0;
   out_5830253173021335118[13] = 0;
   out_5830253173021335118[14] = 0;
   out_5830253173021335118[15] = 0;
   out_5830253173021335118[16] = 0;
   out_5830253173021335118[17] = 0;
   out_5830253173021335118[18] = 0;
   out_5830253173021335118[19] = 0;
   out_5830253173021335118[20] = 0;
   out_5830253173021335118[21] = 0;
   out_5830253173021335118[22] = 0;
   out_5830253173021335118[23] = 0;
   out_5830253173021335118[24] = 0;
   out_5830253173021335118[25] = 1;
   out_5830253173021335118[26] = 0;
   out_5830253173021335118[27] = 0;
   out_5830253173021335118[28] = 1;
   out_5830253173021335118[29] = 0;
   out_5830253173021335118[30] = 0;
   out_5830253173021335118[31] = 0;
   out_5830253173021335118[32] = 0;
   out_5830253173021335118[33] = 0;
   out_5830253173021335118[34] = 0;
   out_5830253173021335118[35] = 0;
   out_5830253173021335118[36] = 0;
   out_5830253173021335118[37] = 0;
   out_5830253173021335118[38] = 0;
   out_5830253173021335118[39] = 0;
   out_5830253173021335118[40] = 0;
   out_5830253173021335118[41] = 0;
   out_5830253173021335118[42] = 0;
   out_5830253173021335118[43] = 0;
   out_5830253173021335118[44] = 1;
   out_5830253173021335118[45] = 0;
   out_5830253173021335118[46] = 0;
   out_5830253173021335118[47] = 1;
   out_5830253173021335118[48] = 0;
   out_5830253173021335118[49] = 0;
   out_5830253173021335118[50] = 0;
   out_5830253173021335118[51] = 0;
   out_5830253173021335118[52] = 0;
   out_5830253173021335118[53] = 0;
}
void h_10(double *state, double *unused, double *out_2136400816105186670) {
   out_2136400816105186670[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2136400816105186670[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2136400816105186670[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7987660615244689739) {
   out_7987660615244689739[0] = 0;
   out_7987660615244689739[1] = 9.8100000000000005*cos(state[1]);
   out_7987660615244689739[2] = 0;
   out_7987660615244689739[3] = 0;
   out_7987660615244689739[4] = -state[8];
   out_7987660615244689739[5] = state[7];
   out_7987660615244689739[6] = 0;
   out_7987660615244689739[7] = state[5];
   out_7987660615244689739[8] = -state[4];
   out_7987660615244689739[9] = 0;
   out_7987660615244689739[10] = 0;
   out_7987660615244689739[11] = 0;
   out_7987660615244689739[12] = 1;
   out_7987660615244689739[13] = 0;
   out_7987660615244689739[14] = 0;
   out_7987660615244689739[15] = 1;
   out_7987660615244689739[16] = 0;
   out_7987660615244689739[17] = 0;
   out_7987660615244689739[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7987660615244689739[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7987660615244689739[20] = 0;
   out_7987660615244689739[21] = state[8];
   out_7987660615244689739[22] = 0;
   out_7987660615244689739[23] = -state[6];
   out_7987660615244689739[24] = -state[5];
   out_7987660615244689739[25] = 0;
   out_7987660615244689739[26] = state[3];
   out_7987660615244689739[27] = 0;
   out_7987660615244689739[28] = 0;
   out_7987660615244689739[29] = 0;
   out_7987660615244689739[30] = 0;
   out_7987660615244689739[31] = 1;
   out_7987660615244689739[32] = 0;
   out_7987660615244689739[33] = 0;
   out_7987660615244689739[34] = 1;
   out_7987660615244689739[35] = 0;
   out_7987660615244689739[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7987660615244689739[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7987660615244689739[38] = 0;
   out_7987660615244689739[39] = -state[7];
   out_7987660615244689739[40] = state[6];
   out_7987660615244689739[41] = 0;
   out_7987660615244689739[42] = state[4];
   out_7987660615244689739[43] = -state[3];
   out_7987660615244689739[44] = 0;
   out_7987660615244689739[45] = 0;
   out_7987660615244689739[46] = 0;
   out_7987660615244689739[47] = 0;
   out_7987660615244689739[48] = 0;
   out_7987660615244689739[49] = 0;
   out_7987660615244689739[50] = 1;
   out_7987660615244689739[51] = 0;
   out_7987660615244689739[52] = 0;
   out_7987660615244689739[53] = 1;
}
void h_13(double *state, double *unused, double *out_7049441698464861794) {
   out_7049441698464861794[0] = state[3];
   out_7049441698464861794[1] = state[4];
   out_7049441698464861794[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5265651253339491014) {
   out_5265651253339491014[0] = 0;
   out_5265651253339491014[1] = 0;
   out_5265651253339491014[2] = 0;
   out_5265651253339491014[3] = 1;
   out_5265651253339491014[4] = 0;
   out_5265651253339491014[5] = 0;
   out_5265651253339491014[6] = 0;
   out_5265651253339491014[7] = 0;
   out_5265651253339491014[8] = 0;
   out_5265651253339491014[9] = 0;
   out_5265651253339491014[10] = 0;
   out_5265651253339491014[11] = 0;
   out_5265651253339491014[12] = 0;
   out_5265651253339491014[13] = 0;
   out_5265651253339491014[14] = 0;
   out_5265651253339491014[15] = 0;
   out_5265651253339491014[16] = 0;
   out_5265651253339491014[17] = 0;
   out_5265651253339491014[18] = 0;
   out_5265651253339491014[19] = 0;
   out_5265651253339491014[20] = 0;
   out_5265651253339491014[21] = 0;
   out_5265651253339491014[22] = 1;
   out_5265651253339491014[23] = 0;
   out_5265651253339491014[24] = 0;
   out_5265651253339491014[25] = 0;
   out_5265651253339491014[26] = 0;
   out_5265651253339491014[27] = 0;
   out_5265651253339491014[28] = 0;
   out_5265651253339491014[29] = 0;
   out_5265651253339491014[30] = 0;
   out_5265651253339491014[31] = 0;
   out_5265651253339491014[32] = 0;
   out_5265651253339491014[33] = 0;
   out_5265651253339491014[34] = 0;
   out_5265651253339491014[35] = 0;
   out_5265651253339491014[36] = 0;
   out_5265651253339491014[37] = 0;
   out_5265651253339491014[38] = 0;
   out_5265651253339491014[39] = 0;
   out_5265651253339491014[40] = 0;
   out_5265651253339491014[41] = 1;
   out_5265651253339491014[42] = 0;
   out_5265651253339491014[43] = 0;
   out_5265651253339491014[44] = 0;
   out_5265651253339491014[45] = 0;
   out_5265651253339491014[46] = 0;
   out_5265651253339491014[47] = 0;
   out_5265651253339491014[48] = 0;
   out_5265651253339491014[49] = 0;
   out_5265651253339491014[50] = 0;
   out_5265651253339491014[51] = 0;
   out_5265651253339491014[52] = 0;
   out_5265651253339491014[53] = 0;
}
void h_14(double *state, double *unused, double *out_1548028699133749812) {
   out_1548028699133749812[0] = state[6];
   out_1548028699133749812[1] = state[7];
   out_1548028699133749812[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8913041605316707414) {
   out_8913041605316707414[0] = 0;
   out_8913041605316707414[1] = 0;
   out_8913041605316707414[2] = 0;
   out_8913041605316707414[3] = 0;
   out_8913041605316707414[4] = 0;
   out_8913041605316707414[5] = 0;
   out_8913041605316707414[6] = 1;
   out_8913041605316707414[7] = 0;
   out_8913041605316707414[8] = 0;
   out_8913041605316707414[9] = 0;
   out_8913041605316707414[10] = 0;
   out_8913041605316707414[11] = 0;
   out_8913041605316707414[12] = 0;
   out_8913041605316707414[13] = 0;
   out_8913041605316707414[14] = 0;
   out_8913041605316707414[15] = 0;
   out_8913041605316707414[16] = 0;
   out_8913041605316707414[17] = 0;
   out_8913041605316707414[18] = 0;
   out_8913041605316707414[19] = 0;
   out_8913041605316707414[20] = 0;
   out_8913041605316707414[21] = 0;
   out_8913041605316707414[22] = 0;
   out_8913041605316707414[23] = 0;
   out_8913041605316707414[24] = 0;
   out_8913041605316707414[25] = 1;
   out_8913041605316707414[26] = 0;
   out_8913041605316707414[27] = 0;
   out_8913041605316707414[28] = 0;
   out_8913041605316707414[29] = 0;
   out_8913041605316707414[30] = 0;
   out_8913041605316707414[31] = 0;
   out_8913041605316707414[32] = 0;
   out_8913041605316707414[33] = 0;
   out_8913041605316707414[34] = 0;
   out_8913041605316707414[35] = 0;
   out_8913041605316707414[36] = 0;
   out_8913041605316707414[37] = 0;
   out_8913041605316707414[38] = 0;
   out_8913041605316707414[39] = 0;
   out_8913041605316707414[40] = 0;
   out_8913041605316707414[41] = 0;
   out_8913041605316707414[42] = 0;
   out_8913041605316707414[43] = 0;
   out_8913041605316707414[44] = 1;
   out_8913041605316707414[45] = 0;
   out_8913041605316707414[46] = 0;
   out_8913041605316707414[47] = 0;
   out_8913041605316707414[48] = 0;
   out_8913041605316707414[49] = 0;
   out_8913041605316707414[50] = 0;
   out_8913041605316707414[51] = 0;
   out_8913041605316707414[52] = 0;
   out_8913041605316707414[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7239197641731070156) {
  err_fun(nom_x, delta_x, out_7239197641731070156);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_217209870609913891) {
  inv_err_fun(nom_x, true_x, out_217209870609913891);
}
void pose_H_mod_fun(double *state, double *out_8844683690844308926) {
  H_mod_fun(state, out_8844683690844308926);
}
void pose_f_fun(double *state, double dt, double *out_371859905987646833) {
  f_fun(state,  dt, out_371859905987646833);
}
void pose_F_fun(double *state, double dt, double *out_5262243657608806363) {
  F_fun(state,  dt, out_5262243657608806363);
}
void pose_h_4(double *state, double *unused, double *out_3538877410533377824) {
  h_4(state, unused, out_3538877410533377824);
}
void pose_H_4(double *state, double *unused, double *out_5830253173021335118) {
  H_4(state, unused, out_5830253173021335118);
}
void pose_h_10(double *state, double *unused, double *out_2136400816105186670) {
  h_10(state, unused, out_2136400816105186670);
}
void pose_H_10(double *state, double *unused, double *out_7987660615244689739) {
  H_10(state, unused, out_7987660615244689739);
}
void pose_h_13(double *state, double *unused, double *out_7049441698464861794) {
  h_13(state, unused, out_7049441698464861794);
}
void pose_H_13(double *state, double *unused, double *out_5265651253339491014) {
  H_13(state, unused, out_5265651253339491014);
}
void pose_h_14(double *state, double *unused, double *out_1548028699133749812) {
  h_14(state, unused, out_1548028699133749812);
}
void pose_H_14(double *state, double *unused, double *out_8913041605316707414) {
  H_14(state, unused, out_8913041605316707414);
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
