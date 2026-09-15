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
void err_fun(double *nom_x, double *delta_x, double *out_5972218924990510792) {
   out_5972218924990510792[0] = delta_x[0] + nom_x[0];
   out_5972218924990510792[1] = delta_x[1] + nom_x[1];
   out_5972218924990510792[2] = delta_x[2] + nom_x[2];
   out_5972218924990510792[3] = delta_x[3] + nom_x[3];
   out_5972218924990510792[4] = delta_x[4] + nom_x[4];
   out_5972218924990510792[5] = delta_x[5] + nom_x[5];
   out_5972218924990510792[6] = delta_x[6] + nom_x[6];
   out_5972218924990510792[7] = delta_x[7] + nom_x[7];
   out_5972218924990510792[8] = delta_x[8] + nom_x[8];
   out_5972218924990510792[9] = delta_x[9] + nom_x[9];
   out_5972218924990510792[10] = delta_x[10] + nom_x[10];
   out_5972218924990510792[11] = delta_x[11] + nom_x[11];
   out_5972218924990510792[12] = delta_x[12] + nom_x[12];
   out_5972218924990510792[13] = delta_x[13] + nom_x[13];
   out_5972218924990510792[14] = delta_x[14] + nom_x[14];
   out_5972218924990510792[15] = delta_x[15] + nom_x[15];
   out_5972218924990510792[16] = delta_x[16] + nom_x[16];
   out_5972218924990510792[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2514414057014520529) {
   out_2514414057014520529[0] = -nom_x[0] + true_x[0];
   out_2514414057014520529[1] = -nom_x[1] + true_x[1];
   out_2514414057014520529[2] = -nom_x[2] + true_x[2];
   out_2514414057014520529[3] = -nom_x[3] + true_x[3];
   out_2514414057014520529[4] = -nom_x[4] + true_x[4];
   out_2514414057014520529[5] = -nom_x[5] + true_x[5];
   out_2514414057014520529[6] = -nom_x[6] + true_x[6];
   out_2514414057014520529[7] = -nom_x[7] + true_x[7];
   out_2514414057014520529[8] = -nom_x[8] + true_x[8];
   out_2514414057014520529[9] = -nom_x[9] + true_x[9];
   out_2514414057014520529[10] = -nom_x[10] + true_x[10];
   out_2514414057014520529[11] = -nom_x[11] + true_x[11];
   out_2514414057014520529[12] = -nom_x[12] + true_x[12];
   out_2514414057014520529[13] = -nom_x[13] + true_x[13];
   out_2514414057014520529[14] = -nom_x[14] + true_x[14];
   out_2514414057014520529[15] = -nom_x[15] + true_x[15];
   out_2514414057014520529[16] = -nom_x[16] + true_x[16];
   out_2514414057014520529[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4028083170396016980) {
   out_4028083170396016980[0] = 1.0;
   out_4028083170396016980[1] = 0.0;
   out_4028083170396016980[2] = 0.0;
   out_4028083170396016980[3] = 0.0;
   out_4028083170396016980[4] = 0.0;
   out_4028083170396016980[5] = 0.0;
   out_4028083170396016980[6] = 0.0;
   out_4028083170396016980[7] = 0.0;
   out_4028083170396016980[8] = 0.0;
   out_4028083170396016980[9] = 0.0;
   out_4028083170396016980[10] = 0.0;
   out_4028083170396016980[11] = 0.0;
   out_4028083170396016980[12] = 0.0;
   out_4028083170396016980[13] = 0.0;
   out_4028083170396016980[14] = 0.0;
   out_4028083170396016980[15] = 0.0;
   out_4028083170396016980[16] = 0.0;
   out_4028083170396016980[17] = 0.0;
   out_4028083170396016980[18] = 0.0;
   out_4028083170396016980[19] = 1.0;
   out_4028083170396016980[20] = 0.0;
   out_4028083170396016980[21] = 0.0;
   out_4028083170396016980[22] = 0.0;
   out_4028083170396016980[23] = 0.0;
   out_4028083170396016980[24] = 0.0;
   out_4028083170396016980[25] = 0.0;
   out_4028083170396016980[26] = 0.0;
   out_4028083170396016980[27] = 0.0;
   out_4028083170396016980[28] = 0.0;
   out_4028083170396016980[29] = 0.0;
   out_4028083170396016980[30] = 0.0;
   out_4028083170396016980[31] = 0.0;
   out_4028083170396016980[32] = 0.0;
   out_4028083170396016980[33] = 0.0;
   out_4028083170396016980[34] = 0.0;
   out_4028083170396016980[35] = 0.0;
   out_4028083170396016980[36] = 0.0;
   out_4028083170396016980[37] = 0.0;
   out_4028083170396016980[38] = 1.0;
   out_4028083170396016980[39] = 0.0;
   out_4028083170396016980[40] = 0.0;
   out_4028083170396016980[41] = 0.0;
   out_4028083170396016980[42] = 0.0;
   out_4028083170396016980[43] = 0.0;
   out_4028083170396016980[44] = 0.0;
   out_4028083170396016980[45] = 0.0;
   out_4028083170396016980[46] = 0.0;
   out_4028083170396016980[47] = 0.0;
   out_4028083170396016980[48] = 0.0;
   out_4028083170396016980[49] = 0.0;
   out_4028083170396016980[50] = 0.0;
   out_4028083170396016980[51] = 0.0;
   out_4028083170396016980[52] = 0.0;
   out_4028083170396016980[53] = 0.0;
   out_4028083170396016980[54] = 0.0;
   out_4028083170396016980[55] = 0.0;
   out_4028083170396016980[56] = 0.0;
   out_4028083170396016980[57] = 1.0;
   out_4028083170396016980[58] = 0.0;
   out_4028083170396016980[59] = 0.0;
   out_4028083170396016980[60] = 0.0;
   out_4028083170396016980[61] = 0.0;
   out_4028083170396016980[62] = 0.0;
   out_4028083170396016980[63] = 0.0;
   out_4028083170396016980[64] = 0.0;
   out_4028083170396016980[65] = 0.0;
   out_4028083170396016980[66] = 0.0;
   out_4028083170396016980[67] = 0.0;
   out_4028083170396016980[68] = 0.0;
   out_4028083170396016980[69] = 0.0;
   out_4028083170396016980[70] = 0.0;
   out_4028083170396016980[71] = 0.0;
   out_4028083170396016980[72] = 0.0;
   out_4028083170396016980[73] = 0.0;
   out_4028083170396016980[74] = 0.0;
   out_4028083170396016980[75] = 0.0;
   out_4028083170396016980[76] = 1.0;
   out_4028083170396016980[77] = 0.0;
   out_4028083170396016980[78] = 0.0;
   out_4028083170396016980[79] = 0.0;
   out_4028083170396016980[80] = 0.0;
   out_4028083170396016980[81] = 0.0;
   out_4028083170396016980[82] = 0.0;
   out_4028083170396016980[83] = 0.0;
   out_4028083170396016980[84] = 0.0;
   out_4028083170396016980[85] = 0.0;
   out_4028083170396016980[86] = 0.0;
   out_4028083170396016980[87] = 0.0;
   out_4028083170396016980[88] = 0.0;
   out_4028083170396016980[89] = 0.0;
   out_4028083170396016980[90] = 0.0;
   out_4028083170396016980[91] = 0.0;
   out_4028083170396016980[92] = 0.0;
   out_4028083170396016980[93] = 0.0;
   out_4028083170396016980[94] = 0.0;
   out_4028083170396016980[95] = 1.0;
   out_4028083170396016980[96] = 0.0;
   out_4028083170396016980[97] = 0.0;
   out_4028083170396016980[98] = 0.0;
   out_4028083170396016980[99] = 0.0;
   out_4028083170396016980[100] = 0.0;
   out_4028083170396016980[101] = 0.0;
   out_4028083170396016980[102] = 0.0;
   out_4028083170396016980[103] = 0.0;
   out_4028083170396016980[104] = 0.0;
   out_4028083170396016980[105] = 0.0;
   out_4028083170396016980[106] = 0.0;
   out_4028083170396016980[107] = 0.0;
   out_4028083170396016980[108] = 0.0;
   out_4028083170396016980[109] = 0.0;
   out_4028083170396016980[110] = 0.0;
   out_4028083170396016980[111] = 0.0;
   out_4028083170396016980[112] = 0.0;
   out_4028083170396016980[113] = 0.0;
   out_4028083170396016980[114] = 1.0;
   out_4028083170396016980[115] = 0.0;
   out_4028083170396016980[116] = 0.0;
   out_4028083170396016980[117] = 0.0;
   out_4028083170396016980[118] = 0.0;
   out_4028083170396016980[119] = 0.0;
   out_4028083170396016980[120] = 0.0;
   out_4028083170396016980[121] = 0.0;
   out_4028083170396016980[122] = 0.0;
   out_4028083170396016980[123] = 0.0;
   out_4028083170396016980[124] = 0.0;
   out_4028083170396016980[125] = 0.0;
   out_4028083170396016980[126] = 0.0;
   out_4028083170396016980[127] = 0.0;
   out_4028083170396016980[128] = 0.0;
   out_4028083170396016980[129] = 0.0;
   out_4028083170396016980[130] = 0.0;
   out_4028083170396016980[131] = 0.0;
   out_4028083170396016980[132] = 0.0;
   out_4028083170396016980[133] = 1.0;
   out_4028083170396016980[134] = 0.0;
   out_4028083170396016980[135] = 0.0;
   out_4028083170396016980[136] = 0.0;
   out_4028083170396016980[137] = 0.0;
   out_4028083170396016980[138] = 0.0;
   out_4028083170396016980[139] = 0.0;
   out_4028083170396016980[140] = 0.0;
   out_4028083170396016980[141] = 0.0;
   out_4028083170396016980[142] = 0.0;
   out_4028083170396016980[143] = 0.0;
   out_4028083170396016980[144] = 0.0;
   out_4028083170396016980[145] = 0.0;
   out_4028083170396016980[146] = 0.0;
   out_4028083170396016980[147] = 0.0;
   out_4028083170396016980[148] = 0.0;
   out_4028083170396016980[149] = 0.0;
   out_4028083170396016980[150] = 0.0;
   out_4028083170396016980[151] = 0.0;
   out_4028083170396016980[152] = 1.0;
   out_4028083170396016980[153] = 0.0;
   out_4028083170396016980[154] = 0.0;
   out_4028083170396016980[155] = 0.0;
   out_4028083170396016980[156] = 0.0;
   out_4028083170396016980[157] = 0.0;
   out_4028083170396016980[158] = 0.0;
   out_4028083170396016980[159] = 0.0;
   out_4028083170396016980[160] = 0.0;
   out_4028083170396016980[161] = 0.0;
   out_4028083170396016980[162] = 0.0;
   out_4028083170396016980[163] = 0.0;
   out_4028083170396016980[164] = 0.0;
   out_4028083170396016980[165] = 0.0;
   out_4028083170396016980[166] = 0.0;
   out_4028083170396016980[167] = 0.0;
   out_4028083170396016980[168] = 0.0;
   out_4028083170396016980[169] = 0.0;
   out_4028083170396016980[170] = 0.0;
   out_4028083170396016980[171] = 1.0;
   out_4028083170396016980[172] = 0.0;
   out_4028083170396016980[173] = 0.0;
   out_4028083170396016980[174] = 0.0;
   out_4028083170396016980[175] = 0.0;
   out_4028083170396016980[176] = 0.0;
   out_4028083170396016980[177] = 0.0;
   out_4028083170396016980[178] = 0.0;
   out_4028083170396016980[179] = 0.0;
   out_4028083170396016980[180] = 0.0;
   out_4028083170396016980[181] = 0.0;
   out_4028083170396016980[182] = 0.0;
   out_4028083170396016980[183] = 0.0;
   out_4028083170396016980[184] = 0.0;
   out_4028083170396016980[185] = 0.0;
   out_4028083170396016980[186] = 0.0;
   out_4028083170396016980[187] = 0.0;
   out_4028083170396016980[188] = 0.0;
   out_4028083170396016980[189] = 0.0;
   out_4028083170396016980[190] = 1.0;
   out_4028083170396016980[191] = 0.0;
   out_4028083170396016980[192] = 0.0;
   out_4028083170396016980[193] = 0.0;
   out_4028083170396016980[194] = 0.0;
   out_4028083170396016980[195] = 0.0;
   out_4028083170396016980[196] = 0.0;
   out_4028083170396016980[197] = 0.0;
   out_4028083170396016980[198] = 0.0;
   out_4028083170396016980[199] = 0.0;
   out_4028083170396016980[200] = 0.0;
   out_4028083170396016980[201] = 0.0;
   out_4028083170396016980[202] = 0.0;
   out_4028083170396016980[203] = 0.0;
   out_4028083170396016980[204] = 0.0;
   out_4028083170396016980[205] = 0.0;
   out_4028083170396016980[206] = 0.0;
   out_4028083170396016980[207] = 0.0;
   out_4028083170396016980[208] = 0.0;
   out_4028083170396016980[209] = 1.0;
   out_4028083170396016980[210] = 0.0;
   out_4028083170396016980[211] = 0.0;
   out_4028083170396016980[212] = 0.0;
   out_4028083170396016980[213] = 0.0;
   out_4028083170396016980[214] = 0.0;
   out_4028083170396016980[215] = 0.0;
   out_4028083170396016980[216] = 0.0;
   out_4028083170396016980[217] = 0.0;
   out_4028083170396016980[218] = 0.0;
   out_4028083170396016980[219] = 0.0;
   out_4028083170396016980[220] = 0.0;
   out_4028083170396016980[221] = 0.0;
   out_4028083170396016980[222] = 0.0;
   out_4028083170396016980[223] = 0.0;
   out_4028083170396016980[224] = 0.0;
   out_4028083170396016980[225] = 0.0;
   out_4028083170396016980[226] = 0.0;
   out_4028083170396016980[227] = 0.0;
   out_4028083170396016980[228] = 1.0;
   out_4028083170396016980[229] = 0.0;
   out_4028083170396016980[230] = 0.0;
   out_4028083170396016980[231] = 0.0;
   out_4028083170396016980[232] = 0.0;
   out_4028083170396016980[233] = 0.0;
   out_4028083170396016980[234] = 0.0;
   out_4028083170396016980[235] = 0.0;
   out_4028083170396016980[236] = 0.0;
   out_4028083170396016980[237] = 0.0;
   out_4028083170396016980[238] = 0.0;
   out_4028083170396016980[239] = 0.0;
   out_4028083170396016980[240] = 0.0;
   out_4028083170396016980[241] = 0.0;
   out_4028083170396016980[242] = 0.0;
   out_4028083170396016980[243] = 0.0;
   out_4028083170396016980[244] = 0.0;
   out_4028083170396016980[245] = 0.0;
   out_4028083170396016980[246] = 0.0;
   out_4028083170396016980[247] = 1.0;
   out_4028083170396016980[248] = 0.0;
   out_4028083170396016980[249] = 0.0;
   out_4028083170396016980[250] = 0.0;
   out_4028083170396016980[251] = 0.0;
   out_4028083170396016980[252] = 0.0;
   out_4028083170396016980[253] = 0.0;
   out_4028083170396016980[254] = 0.0;
   out_4028083170396016980[255] = 0.0;
   out_4028083170396016980[256] = 0.0;
   out_4028083170396016980[257] = 0.0;
   out_4028083170396016980[258] = 0.0;
   out_4028083170396016980[259] = 0.0;
   out_4028083170396016980[260] = 0.0;
   out_4028083170396016980[261] = 0.0;
   out_4028083170396016980[262] = 0.0;
   out_4028083170396016980[263] = 0.0;
   out_4028083170396016980[264] = 0.0;
   out_4028083170396016980[265] = 0.0;
   out_4028083170396016980[266] = 1.0;
   out_4028083170396016980[267] = 0.0;
   out_4028083170396016980[268] = 0.0;
   out_4028083170396016980[269] = 0.0;
   out_4028083170396016980[270] = 0.0;
   out_4028083170396016980[271] = 0.0;
   out_4028083170396016980[272] = 0.0;
   out_4028083170396016980[273] = 0.0;
   out_4028083170396016980[274] = 0.0;
   out_4028083170396016980[275] = 0.0;
   out_4028083170396016980[276] = 0.0;
   out_4028083170396016980[277] = 0.0;
   out_4028083170396016980[278] = 0.0;
   out_4028083170396016980[279] = 0.0;
   out_4028083170396016980[280] = 0.0;
   out_4028083170396016980[281] = 0.0;
   out_4028083170396016980[282] = 0.0;
   out_4028083170396016980[283] = 0.0;
   out_4028083170396016980[284] = 0.0;
   out_4028083170396016980[285] = 1.0;
   out_4028083170396016980[286] = 0.0;
   out_4028083170396016980[287] = 0.0;
   out_4028083170396016980[288] = 0.0;
   out_4028083170396016980[289] = 0.0;
   out_4028083170396016980[290] = 0.0;
   out_4028083170396016980[291] = 0.0;
   out_4028083170396016980[292] = 0.0;
   out_4028083170396016980[293] = 0.0;
   out_4028083170396016980[294] = 0.0;
   out_4028083170396016980[295] = 0.0;
   out_4028083170396016980[296] = 0.0;
   out_4028083170396016980[297] = 0.0;
   out_4028083170396016980[298] = 0.0;
   out_4028083170396016980[299] = 0.0;
   out_4028083170396016980[300] = 0.0;
   out_4028083170396016980[301] = 0.0;
   out_4028083170396016980[302] = 0.0;
   out_4028083170396016980[303] = 0.0;
   out_4028083170396016980[304] = 1.0;
   out_4028083170396016980[305] = 0.0;
   out_4028083170396016980[306] = 0.0;
   out_4028083170396016980[307] = 0.0;
   out_4028083170396016980[308] = 0.0;
   out_4028083170396016980[309] = 0.0;
   out_4028083170396016980[310] = 0.0;
   out_4028083170396016980[311] = 0.0;
   out_4028083170396016980[312] = 0.0;
   out_4028083170396016980[313] = 0.0;
   out_4028083170396016980[314] = 0.0;
   out_4028083170396016980[315] = 0.0;
   out_4028083170396016980[316] = 0.0;
   out_4028083170396016980[317] = 0.0;
   out_4028083170396016980[318] = 0.0;
   out_4028083170396016980[319] = 0.0;
   out_4028083170396016980[320] = 0.0;
   out_4028083170396016980[321] = 0.0;
   out_4028083170396016980[322] = 0.0;
   out_4028083170396016980[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5391513649361153377) {
   out_5391513649361153377[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5391513649361153377[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5391513649361153377[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5391513649361153377[3] = dt*state[12] + state[3];
   out_5391513649361153377[4] = dt*state[13] + state[4];
   out_5391513649361153377[5] = dt*state[14] + state[5];
   out_5391513649361153377[6] = state[6];
   out_5391513649361153377[7] = state[7];
   out_5391513649361153377[8] = state[8];
   out_5391513649361153377[9] = state[9];
   out_5391513649361153377[10] = state[10];
   out_5391513649361153377[11] = state[11];
   out_5391513649361153377[12] = state[12];
   out_5391513649361153377[13] = state[13];
   out_5391513649361153377[14] = state[14];
   out_5391513649361153377[15] = state[15];
   out_5391513649361153377[16] = state[16];
   out_5391513649361153377[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3183755745481268939) {
   out_3183755745481268939[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3183755745481268939[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3183755745481268939[2] = 0;
   out_3183755745481268939[3] = 0;
   out_3183755745481268939[4] = 0;
   out_3183755745481268939[5] = 0;
   out_3183755745481268939[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3183755745481268939[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3183755745481268939[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3183755745481268939[9] = 0;
   out_3183755745481268939[10] = 0;
   out_3183755745481268939[11] = 0;
   out_3183755745481268939[12] = 0;
   out_3183755745481268939[13] = 0;
   out_3183755745481268939[14] = 0;
   out_3183755745481268939[15] = 0;
   out_3183755745481268939[16] = 0;
   out_3183755745481268939[17] = 0;
   out_3183755745481268939[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3183755745481268939[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3183755745481268939[20] = 0;
   out_3183755745481268939[21] = 0;
   out_3183755745481268939[22] = 0;
   out_3183755745481268939[23] = 0;
   out_3183755745481268939[24] = 0;
   out_3183755745481268939[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3183755745481268939[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3183755745481268939[27] = 0;
   out_3183755745481268939[28] = 0;
   out_3183755745481268939[29] = 0;
   out_3183755745481268939[30] = 0;
   out_3183755745481268939[31] = 0;
   out_3183755745481268939[32] = 0;
   out_3183755745481268939[33] = 0;
   out_3183755745481268939[34] = 0;
   out_3183755745481268939[35] = 0;
   out_3183755745481268939[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3183755745481268939[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3183755745481268939[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3183755745481268939[39] = 0;
   out_3183755745481268939[40] = 0;
   out_3183755745481268939[41] = 0;
   out_3183755745481268939[42] = 0;
   out_3183755745481268939[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3183755745481268939[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3183755745481268939[45] = 0;
   out_3183755745481268939[46] = 0;
   out_3183755745481268939[47] = 0;
   out_3183755745481268939[48] = 0;
   out_3183755745481268939[49] = 0;
   out_3183755745481268939[50] = 0;
   out_3183755745481268939[51] = 0;
   out_3183755745481268939[52] = 0;
   out_3183755745481268939[53] = 0;
   out_3183755745481268939[54] = 0;
   out_3183755745481268939[55] = 0;
   out_3183755745481268939[56] = 0;
   out_3183755745481268939[57] = 1;
   out_3183755745481268939[58] = 0;
   out_3183755745481268939[59] = 0;
   out_3183755745481268939[60] = 0;
   out_3183755745481268939[61] = 0;
   out_3183755745481268939[62] = 0;
   out_3183755745481268939[63] = 0;
   out_3183755745481268939[64] = 0;
   out_3183755745481268939[65] = 0;
   out_3183755745481268939[66] = dt;
   out_3183755745481268939[67] = 0;
   out_3183755745481268939[68] = 0;
   out_3183755745481268939[69] = 0;
   out_3183755745481268939[70] = 0;
   out_3183755745481268939[71] = 0;
   out_3183755745481268939[72] = 0;
   out_3183755745481268939[73] = 0;
   out_3183755745481268939[74] = 0;
   out_3183755745481268939[75] = 0;
   out_3183755745481268939[76] = 1;
   out_3183755745481268939[77] = 0;
   out_3183755745481268939[78] = 0;
   out_3183755745481268939[79] = 0;
   out_3183755745481268939[80] = 0;
   out_3183755745481268939[81] = 0;
   out_3183755745481268939[82] = 0;
   out_3183755745481268939[83] = 0;
   out_3183755745481268939[84] = 0;
   out_3183755745481268939[85] = dt;
   out_3183755745481268939[86] = 0;
   out_3183755745481268939[87] = 0;
   out_3183755745481268939[88] = 0;
   out_3183755745481268939[89] = 0;
   out_3183755745481268939[90] = 0;
   out_3183755745481268939[91] = 0;
   out_3183755745481268939[92] = 0;
   out_3183755745481268939[93] = 0;
   out_3183755745481268939[94] = 0;
   out_3183755745481268939[95] = 1;
   out_3183755745481268939[96] = 0;
   out_3183755745481268939[97] = 0;
   out_3183755745481268939[98] = 0;
   out_3183755745481268939[99] = 0;
   out_3183755745481268939[100] = 0;
   out_3183755745481268939[101] = 0;
   out_3183755745481268939[102] = 0;
   out_3183755745481268939[103] = 0;
   out_3183755745481268939[104] = dt;
   out_3183755745481268939[105] = 0;
   out_3183755745481268939[106] = 0;
   out_3183755745481268939[107] = 0;
   out_3183755745481268939[108] = 0;
   out_3183755745481268939[109] = 0;
   out_3183755745481268939[110] = 0;
   out_3183755745481268939[111] = 0;
   out_3183755745481268939[112] = 0;
   out_3183755745481268939[113] = 0;
   out_3183755745481268939[114] = 1;
   out_3183755745481268939[115] = 0;
   out_3183755745481268939[116] = 0;
   out_3183755745481268939[117] = 0;
   out_3183755745481268939[118] = 0;
   out_3183755745481268939[119] = 0;
   out_3183755745481268939[120] = 0;
   out_3183755745481268939[121] = 0;
   out_3183755745481268939[122] = 0;
   out_3183755745481268939[123] = 0;
   out_3183755745481268939[124] = 0;
   out_3183755745481268939[125] = 0;
   out_3183755745481268939[126] = 0;
   out_3183755745481268939[127] = 0;
   out_3183755745481268939[128] = 0;
   out_3183755745481268939[129] = 0;
   out_3183755745481268939[130] = 0;
   out_3183755745481268939[131] = 0;
   out_3183755745481268939[132] = 0;
   out_3183755745481268939[133] = 1;
   out_3183755745481268939[134] = 0;
   out_3183755745481268939[135] = 0;
   out_3183755745481268939[136] = 0;
   out_3183755745481268939[137] = 0;
   out_3183755745481268939[138] = 0;
   out_3183755745481268939[139] = 0;
   out_3183755745481268939[140] = 0;
   out_3183755745481268939[141] = 0;
   out_3183755745481268939[142] = 0;
   out_3183755745481268939[143] = 0;
   out_3183755745481268939[144] = 0;
   out_3183755745481268939[145] = 0;
   out_3183755745481268939[146] = 0;
   out_3183755745481268939[147] = 0;
   out_3183755745481268939[148] = 0;
   out_3183755745481268939[149] = 0;
   out_3183755745481268939[150] = 0;
   out_3183755745481268939[151] = 0;
   out_3183755745481268939[152] = 1;
   out_3183755745481268939[153] = 0;
   out_3183755745481268939[154] = 0;
   out_3183755745481268939[155] = 0;
   out_3183755745481268939[156] = 0;
   out_3183755745481268939[157] = 0;
   out_3183755745481268939[158] = 0;
   out_3183755745481268939[159] = 0;
   out_3183755745481268939[160] = 0;
   out_3183755745481268939[161] = 0;
   out_3183755745481268939[162] = 0;
   out_3183755745481268939[163] = 0;
   out_3183755745481268939[164] = 0;
   out_3183755745481268939[165] = 0;
   out_3183755745481268939[166] = 0;
   out_3183755745481268939[167] = 0;
   out_3183755745481268939[168] = 0;
   out_3183755745481268939[169] = 0;
   out_3183755745481268939[170] = 0;
   out_3183755745481268939[171] = 1;
   out_3183755745481268939[172] = 0;
   out_3183755745481268939[173] = 0;
   out_3183755745481268939[174] = 0;
   out_3183755745481268939[175] = 0;
   out_3183755745481268939[176] = 0;
   out_3183755745481268939[177] = 0;
   out_3183755745481268939[178] = 0;
   out_3183755745481268939[179] = 0;
   out_3183755745481268939[180] = 0;
   out_3183755745481268939[181] = 0;
   out_3183755745481268939[182] = 0;
   out_3183755745481268939[183] = 0;
   out_3183755745481268939[184] = 0;
   out_3183755745481268939[185] = 0;
   out_3183755745481268939[186] = 0;
   out_3183755745481268939[187] = 0;
   out_3183755745481268939[188] = 0;
   out_3183755745481268939[189] = 0;
   out_3183755745481268939[190] = 1;
   out_3183755745481268939[191] = 0;
   out_3183755745481268939[192] = 0;
   out_3183755745481268939[193] = 0;
   out_3183755745481268939[194] = 0;
   out_3183755745481268939[195] = 0;
   out_3183755745481268939[196] = 0;
   out_3183755745481268939[197] = 0;
   out_3183755745481268939[198] = 0;
   out_3183755745481268939[199] = 0;
   out_3183755745481268939[200] = 0;
   out_3183755745481268939[201] = 0;
   out_3183755745481268939[202] = 0;
   out_3183755745481268939[203] = 0;
   out_3183755745481268939[204] = 0;
   out_3183755745481268939[205] = 0;
   out_3183755745481268939[206] = 0;
   out_3183755745481268939[207] = 0;
   out_3183755745481268939[208] = 0;
   out_3183755745481268939[209] = 1;
   out_3183755745481268939[210] = 0;
   out_3183755745481268939[211] = 0;
   out_3183755745481268939[212] = 0;
   out_3183755745481268939[213] = 0;
   out_3183755745481268939[214] = 0;
   out_3183755745481268939[215] = 0;
   out_3183755745481268939[216] = 0;
   out_3183755745481268939[217] = 0;
   out_3183755745481268939[218] = 0;
   out_3183755745481268939[219] = 0;
   out_3183755745481268939[220] = 0;
   out_3183755745481268939[221] = 0;
   out_3183755745481268939[222] = 0;
   out_3183755745481268939[223] = 0;
   out_3183755745481268939[224] = 0;
   out_3183755745481268939[225] = 0;
   out_3183755745481268939[226] = 0;
   out_3183755745481268939[227] = 0;
   out_3183755745481268939[228] = 1;
   out_3183755745481268939[229] = 0;
   out_3183755745481268939[230] = 0;
   out_3183755745481268939[231] = 0;
   out_3183755745481268939[232] = 0;
   out_3183755745481268939[233] = 0;
   out_3183755745481268939[234] = 0;
   out_3183755745481268939[235] = 0;
   out_3183755745481268939[236] = 0;
   out_3183755745481268939[237] = 0;
   out_3183755745481268939[238] = 0;
   out_3183755745481268939[239] = 0;
   out_3183755745481268939[240] = 0;
   out_3183755745481268939[241] = 0;
   out_3183755745481268939[242] = 0;
   out_3183755745481268939[243] = 0;
   out_3183755745481268939[244] = 0;
   out_3183755745481268939[245] = 0;
   out_3183755745481268939[246] = 0;
   out_3183755745481268939[247] = 1;
   out_3183755745481268939[248] = 0;
   out_3183755745481268939[249] = 0;
   out_3183755745481268939[250] = 0;
   out_3183755745481268939[251] = 0;
   out_3183755745481268939[252] = 0;
   out_3183755745481268939[253] = 0;
   out_3183755745481268939[254] = 0;
   out_3183755745481268939[255] = 0;
   out_3183755745481268939[256] = 0;
   out_3183755745481268939[257] = 0;
   out_3183755745481268939[258] = 0;
   out_3183755745481268939[259] = 0;
   out_3183755745481268939[260] = 0;
   out_3183755745481268939[261] = 0;
   out_3183755745481268939[262] = 0;
   out_3183755745481268939[263] = 0;
   out_3183755745481268939[264] = 0;
   out_3183755745481268939[265] = 0;
   out_3183755745481268939[266] = 1;
   out_3183755745481268939[267] = 0;
   out_3183755745481268939[268] = 0;
   out_3183755745481268939[269] = 0;
   out_3183755745481268939[270] = 0;
   out_3183755745481268939[271] = 0;
   out_3183755745481268939[272] = 0;
   out_3183755745481268939[273] = 0;
   out_3183755745481268939[274] = 0;
   out_3183755745481268939[275] = 0;
   out_3183755745481268939[276] = 0;
   out_3183755745481268939[277] = 0;
   out_3183755745481268939[278] = 0;
   out_3183755745481268939[279] = 0;
   out_3183755745481268939[280] = 0;
   out_3183755745481268939[281] = 0;
   out_3183755745481268939[282] = 0;
   out_3183755745481268939[283] = 0;
   out_3183755745481268939[284] = 0;
   out_3183755745481268939[285] = 1;
   out_3183755745481268939[286] = 0;
   out_3183755745481268939[287] = 0;
   out_3183755745481268939[288] = 0;
   out_3183755745481268939[289] = 0;
   out_3183755745481268939[290] = 0;
   out_3183755745481268939[291] = 0;
   out_3183755745481268939[292] = 0;
   out_3183755745481268939[293] = 0;
   out_3183755745481268939[294] = 0;
   out_3183755745481268939[295] = 0;
   out_3183755745481268939[296] = 0;
   out_3183755745481268939[297] = 0;
   out_3183755745481268939[298] = 0;
   out_3183755745481268939[299] = 0;
   out_3183755745481268939[300] = 0;
   out_3183755745481268939[301] = 0;
   out_3183755745481268939[302] = 0;
   out_3183755745481268939[303] = 0;
   out_3183755745481268939[304] = 1;
   out_3183755745481268939[305] = 0;
   out_3183755745481268939[306] = 0;
   out_3183755745481268939[307] = 0;
   out_3183755745481268939[308] = 0;
   out_3183755745481268939[309] = 0;
   out_3183755745481268939[310] = 0;
   out_3183755745481268939[311] = 0;
   out_3183755745481268939[312] = 0;
   out_3183755745481268939[313] = 0;
   out_3183755745481268939[314] = 0;
   out_3183755745481268939[315] = 0;
   out_3183755745481268939[316] = 0;
   out_3183755745481268939[317] = 0;
   out_3183755745481268939[318] = 0;
   out_3183755745481268939[319] = 0;
   out_3183755745481268939[320] = 0;
   out_3183755745481268939[321] = 0;
   out_3183755745481268939[322] = 0;
   out_3183755745481268939[323] = 1;
}
void h_4(double *state, double *unused, double *out_4392711394053593010) {
   out_4392711394053593010[0] = state[6] + state[9];
   out_4392711394053593010[1] = state[7] + state[10];
   out_4392711394053593010[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6484436289412890429) {
   out_6484436289412890429[0] = 0;
   out_6484436289412890429[1] = 0;
   out_6484436289412890429[2] = 0;
   out_6484436289412890429[3] = 0;
   out_6484436289412890429[4] = 0;
   out_6484436289412890429[5] = 0;
   out_6484436289412890429[6] = 1;
   out_6484436289412890429[7] = 0;
   out_6484436289412890429[8] = 0;
   out_6484436289412890429[9] = 1;
   out_6484436289412890429[10] = 0;
   out_6484436289412890429[11] = 0;
   out_6484436289412890429[12] = 0;
   out_6484436289412890429[13] = 0;
   out_6484436289412890429[14] = 0;
   out_6484436289412890429[15] = 0;
   out_6484436289412890429[16] = 0;
   out_6484436289412890429[17] = 0;
   out_6484436289412890429[18] = 0;
   out_6484436289412890429[19] = 0;
   out_6484436289412890429[20] = 0;
   out_6484436289412890429[21] = 0;
   out_6484436289412890429[22] = 0;
   out_6484436289412890429[23] = 0;
   out_6484436289412890429[24] = 0;
   out_6484436289412890429[25] = 1;
   out_6484436289412890429[26] = 0;
   out_6484436289412890429[27] = 0;
   out_6484436289412890429[28] = 1;
   out_6484436289412890429[29] = 0;
   out_6484436289412890429[30] = 0;
   out_6484436289412890429[31] = 0;
   out_6484436289412890429[32] = 0;
   out_6484436289412890429[33] = 0;
   out_6484436289412890429[34] = 0;
   out_6484436289412890429[35] = 0;
   out_6484436289412890429[36] = 0;
   out_6484436289412890429[37] = 0;
   out_6484436289412890429[38] = 0;
   out_6484436289412890429[39] = 0;
   out_6484436289412890429[40] = 0;
   out_6484436289412890429[41] = 0;
   out_6484436289412890429[42] = 0;
   out_6484436289412890429[43] = 0;
   out_6484436289412890429[44] = 1;
   out_6484436289412890429[45] = 0;
   out_6484436289412890429[46] = 0;
   out_6484436289412890429[47] = 1;
   out_6484436289412890429[48] = 0;
   out_6484436289412890429[49] = 0;
   out_6484436289412890429[50] = 0;
   out_6484436289412890429[51] = 0;
   out_6484436289412890429[52] = 0;
   out_6484436289412890429[53] = 0;
}
void h_10(double *state, double *unused, double *out_8376071089077647070) {
   out_8376071089077647070[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8376071089077647070[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8376071089077647070[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7681394100323810490) {
   out_7681394100323810490[0] = 0;
   out_7681394100323810490[1] = 9.8100000000000005*cos(state[1]);
   out_7681394100323810490[2] = 0;
   out_7681394100323810490[3] = 0;
   out_7681394100323810490[4] = -state[8];
   out_7681394100323810490[5] = state[7];
   out_7681394100323810490[6] = 0;
   out_7681394100323810490[7] = state[5];
   out_7681394100323810490[8] = -state[4];
   out_7681394100323810490[9] = 0;
   out_7681394100323810490[10] = 0;
   out_7681394100323810490[11] = 0;
   out_7681394100323810490[12] = 1;
   out_7681394100323810490[13] = 0;
   out_7681394100323810490[14] = 0;
   out_7681394100323810490[15] = 1;
   out_7681394100323810490[16] = 0;
   out_7681394100323810490[17] = 0;
   out_7681394100323810490[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7681394100323810490[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7681394100323810490[20] = 0;
   out_7681394100323810490[21] = state[8];
   out_7681394100323810490[22] = 0;
   out_7681394100323810490[23] = -state[6];
   out_7681394100323810490[24] = -state[5];
   out_7681394100323810490[25] = 0;
   out_7681394100323810490[26] = state[3];
   out_7681394100323810490[27] = 0;
   out_7681394100323810490[28] = 0;
   out_7681394100323810490[29] = 0;
   out_7681394100323810490[30] = 0;
   out_7681394100323810490[31] = 1;
   out_7681394100323810490[32] = 0;
   out_7681394100323810490[33] = 0;
   out_7681394100323810490[34] = 1;
   out_7681394100323810490[35] = 0;
   out_7681394100323810490[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7681394100323810490[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7681394100323810490[38] = 0;
   out_7681394100323810490[39] = -state[7];
   out_7681394100323810490[40] = state[6];
   out_7681394100323810490[41] = 0;
   out_7681394100323810490[42] = state[4];
   out_7681394100323810490[43] = -state[3];
   out_7681394100323810490[44] = 0;
   out_7681394100323810490[45] = 0;
   out_7681394100323810490[46] = 0;
   out_7681394100323810490[47] = 0;
   out_7681394100323810490[48] = 0;
   out_7681394100323810490[49] = 0;
   out_7681394100323810490[50] = 1;
   out_7681394100323810490[51] = 0;
   out_7681394100323810490[52] = 0;
   out_7681394100323810490[53] = 1;
}
void h_13(double *state, double *unused, double *out_3671495376644037122) {
   out_3671495376644037122[0] = state[3];
   out_3671495376644037122[1] = state[4];
   out_3671495376644037122[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8750033958964328386) {
   out_8750033958964328386[0] = 0;
   out_8750033958964328386[1] = 0;
   out_8750033958964328386[2] = 0;
   out_8750033958964328386[3] = 1;
   out_8750033958964328386[4] = 0;
   out_8750033958964328386[5] = 0;
   out_8750033958964328386[6] = 0;
   out_8750033958964328386[7] = 0;
   out_8750033958964328386[8] = 0;
   out_8750033958964328386[9] = 0;
   out_8750033958964328386[10] = 0;
   out_8750033958964328386[11] = 0;
   out_8750033958964328386[12] = 0;
   out_8750033958964328386[13] = 0;
   out_8750033958964328386[14] = 0;
   out_8750033958964328386[15] = 0;
   out_8750033958964328386[16] = 0;
   out_8750033958964328386[17] = 0;
   out_8750033958964328386[18] = 0;
   out_8750033958964328386[19] = 0;
   out_8750033958964328386[20] = 0;
   out_8750033958964328386[21] = 0;
   out_8750033958964328386[22] = 1;
   out_8750033958964328386[23] = 0;
   out_8750033958964328386[24] = 0;
   out_8750033958964328386[25] = 0;
   out_8750033958964328386[26] = 0;
   out_8750033958964328386[27] = 0;
   out_8750033958964328386[28] = 0;
   out_8750033958964328386[29] = 0;
   out_8750033958964328386[30] = 0;
   out_8750033958964328386[31] = 0;
   out_8750033958964328386[32] = 0;
   out_8750033958964328386[33] = 0;
   out_8750033958964328386[34] = 0;
   out_8750033958964328386[35] = 0;
   out_8750033958964328386[36] = 0;
   out_8750033958964328386[37] = 0;
   out_8750033958964328386[38] = 0;
   out_8750033958964328386[39] = 0;
   out_8750033958964328386[40] = 0;
   out_8750033958964328386[41] = 1;
   out_8750033958964328386[42] = 0;
   out_8750033958964328386[43] = 0;
   out_8750033958964328386[44] = 0;
   out_8750033958964328386[45] = 0;
   out_8750033958964328386[46] = 0;
   out_8750033958964328386[47] = 0;
   out_8750033958964328386[48] = 0;
   out_8750033958964328386[49] = 0;
   out_8750033958964328386[50] = 0;
   out_8750033958964328386[51] = 0;
   out_8750033958964328386[52] = 0;
   out_8750033958964328386[53] = 0;
}
void h_14(double *state, double *unused, double *out_2407733700991607130) {
   out_2407733700991607130[0] = state[6];
   out_2407733700991607130[1] = state[7];
   out_2407733700991607130[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7999066927957176658) {
   out_7999066927957176658[0] = 0;
   out_7999066927957176658[1] = 0;
   out_7999066927957176658[2] = 0;
   out_7999066927957176658[3] = 0;
   out_7999066927957176658[4] = 0;
   out_7999066927957176658[5] = 0;
   out_7999066927957176658[6] = 1;
   out_7999066927957176658[7] = 0;
   out_7999066927957176658[8] = 0;
   out_7999066927957176658[9] = 0;
   out_7999066927957176658[10] = 0;
   out_7999066927957176658[11] = 0;
   out_7999066927957176658[12] = 0;
   out_7999066927957176658[13] = 0;
   out_7999066927957176658[14] = 0;
   out_7999066927957176658[15] = 0;
   out_7999066927957176658[16] = 0;
   out_7999066927957176658[17] = 0;
   out_7999066927957176658[18] = 0;
   out_7999066927957176658[19] = 0;
   out_7999066927957176658[20] = 0;
   out_7999066927957176658[21] = 0;
   out_7999066927957176658[22] = 0;
   out_7999066927957176658[23] = 0;
   out_7999066927957176658[24] = 0;
   out_7999066927957176658[25] = 1;
   out_7999066927957176658[26] = 0;
   out_7999066927957176658[27] = 0;
   out_7999066927957176658[28] = 0;
   out_7999066927957176658[29] = 0;
   out_7999066927957176658[30] = 0;
   out_7999066927957176658[31] = 0;
   out_7999066927957176658[32] = 0;
   out_7999066927957176658[33] = 0;
   out_7999066927957176658[34] = 0;
   out_7999066927957176658[35] = 0;
   out_7999066927957176658[36] = 0;
   out_7999066927957176658[37] = 0;
   out_7999066927957176658[38] = 0;
   out_7999066927957176658[39] = 0;
   out_7999066927957176658[40] = 0;
   out_7999066927957176658[41] = 0;
   out_7999066927957176658[42] = 0;
   out_7999066927957176658[43] = 0;
   out_7999066927957176658[44] = 1;
   out_7999066927957176658[45] = 0;
   out_7999066927957176658[46] = 0;
   out_7999066927957176658[47] = 0;
   out_7999066927957176658[48] = 0;
   out_7999066927957176658[49] = 0;
   out_7999066927957176658[50] = 0;
   out_7999066927957176658[51] = 0;
   out_7999066927957176658[52] = 0;
   out_7999066927957176658[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5972218924990510792) {
  err_fun(nom_x, delta_x, out_5972218924990510792);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2514414057014520529) {
  inv_err_fun(nom_x, true_x, out_2514414057014520529);
}
void pose_H_mod_fun(double *state, double *out_4028083170396016980) {
  H_mod_fun(state, out_4028083170396016980);
}
void pose_f_fun(double *state, double dt, double *out_5391513649361153377) {
  f_fun(state,  dt, out_5391513649361153377);
}
void pose_F_fun(double *state, double dt, double *out_3183755745481268939) {
  F_fun(state,  dt, out_3183755745481268939);
}
void pose_h_4(double *state, double *unused, double *out_4392711394053593010) {
  h_4(state, unused, out_4392711394053593010);
}
void pose_H_4(double *state, double *unused, double *out_6484436289412890429) {
  H_4(state, unused, out_6484436289412890429);
}
void pose_h_10(double *state, double *unused, double *out_8376071089077647070) {
  h_10(state, unused, out_8376071089077647070);
}
void pose_H_10(double *state, double *unused, double *out_7681394100323810490) {
  H_10(state, unused, out_7681394100323810490);
}
void pose_h_13(double *state, double *unused, double *out_3671495376644037122) {
  h_13(state, unused, out_3671495376644037122);
}
void pose_H_13(double *state, double *unused, double *out_8750033958964328386) {
  H_13(state, unused, out_8750033958964328386);
}
void pose_h_14(double *state, double *unused, double *out_2407733700991607130) {
  h_14(state, unused, out_2407733700991607130);
}
void pose_H_14(double *state, double *unused, double *out_7999066927957176658) {
  H_14(state, unused, out_7999066927957176658);
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
