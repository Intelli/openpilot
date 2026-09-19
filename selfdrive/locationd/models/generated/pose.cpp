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
void err_fun(double *nom_x, double *delta_x, double *out_1877090198031843098) {
   out_1877090198031843098[0] = delta_x[0] + nom_x[0];
   out_1877090198031843098[1] = delta_x[1] + nom_x[1];
   out_1877090198031843098[2] = delta_x[2] + nom_x[2];
   out_1877090198031843098[3] = delta_x[3] + nom_x[3];
   out_1877090198031843098[4] = delta_x[4] + nom_x[4];
   out_1877090198031843098[5] = delta_x[5] + nom_x[5];
   out_1877090198031843098[6] = delta_x[6] + nom_x[6];
   out_1877090198031843098[7] = delta_x[7] + nom_x[7];
   out_1877090198031843098[8] = delta_x[8] + nom_x[8];
   out_1877090198031843098[9] = delta_x[9] + nom_x[9];
   out_1877090198031843098[10] = delta_x[10] + nom_x[10];
   out_1877090198031843098[11] = delta_x[11] + nom_x[11];
   out_1877090198031843098[12] = delta_x[12] + nom_x[12];
   out_1877090198031843098[13] = delta_x[13] + nom_x[13];
   out_1877090198031843098[14] = delta_x[14] + nom_x[14];
   out_1877090198031843098[15] = delta_x[15] + nom_x[15];
   out_1877090198031843098[16] = delta_x[16] + nom_x[16];
   out_1877090198031843098[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4765871387657118050) {
   out_4765871387657118050[0] = -nom_x[0] + true_x[0];
   out_4765871387657118050[1] = -nom_x[1] + true_x[1];
   out_4765871387657118050[2] = -nom_x[2] + true_x[2];
   out_4765871387657118050[3] = -nom_x[3] + true_x[3];
   out_4765871387657118050[4] = -nom_x[4] + true_x[4];
   out_4765871387657118050[5] = -nom_x[5] + true_x[5];
   out_4765871387657118050[6] = -nom_x[6] + true_x[6];
   out_4765871387657118050[7] = -nom_x[7] + true_x[7];
   out_4765871387657118050[8] = -nom_x[8] + true_x[8];
   out_4765871387657118050[9] = -nom_x[9] + true_x[9];
   out_4765871387657118050[10] = -nom_x[10] + true_x[10];
   out_4765871387657118050[11] = -nom_x[11] + true_x[11];
   out_4765871387657118050[12] = -nom_x[12] + true_x[12];
   out_4765871387657118050[13] = -nom_x[13] + true_x[13];
   out_4765871387657118050[14] = -nom_x[14] + true_x[14];
   out_4765871387657118050[15] = -nom_x[15] + true_x[15];
   out_4765871387657118050[16] = -nom_x[16] + true_x[16];
   out_4765871387657118050[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3424858624905544886) {
   out_3424858624905544886[0] = 1.0;
   out_3424858624905544886[1] = 0.0;
   out_3424858624905544886[2] = 0.0;
   out_3424858624905544886[3] = 0.0;
   out_3424858624905544886[4] = 0.0;
   out_3424858624905544886[5] = 0.0;
   out_3424858624905544886[6] = 0.0;
   out_3424858624905544886[7] = 0.0;
   out_3424858624905544886[8] = 0.0;
   out_3424858624905544886[9] = 0.0;
   out_3424858624905544886[10] = 0.0;
   out_3424858624905544886[11] = 0.0;
   out_3424858624905544886[12] = 0.0;
   out_3424858624905544886[13] = 0.0;
   out_3424858624905544886[14] = 0.0;
   out_3424858624905544886[15] = 0.0;
   out_3424858624905544886[16] = 0.0;
   out_3424858624905544886[17] = 0.0;
   out_3424858624905544886[18] = 0.0;
   out_3424858624905544886[19] = 1.0;
   out_3424858624905544886[20] = 0.0;
   out_3424858624905544886[21] = 0.0;
   out_3424858624905544886[22] = 0.0;
   out_3424858624905544886[23] = 0.0;
   out_3424858624905544886[24] = 0.0;
   out_3424858624905544886[25] = 0.0;
   out_3424858624905544886[26] = 0.0;
   out_3424858624905544886[27] = 0.0;
   out_3424858624905544886[28] = 0.0;
   out_3424858624905544886[29] = 0.0;
   out_3424858624905544886[30] = 0.0;
   out_3424858624905544886[31] = 0.0;
   out_3424858624905544886[32] = 0.0;
   out_3424858624905544886[33] = 0.0;
   out_3424858624905544886[34] = 0.0;
   out_3424858624905544886[35] = 0.0;
   out_3424858624905544886[36] = 0.0;
   out_3424858624905544886[37] = 0.0;
   out_3424858624905544886[38] = 1.0;
   out_3424858624905544886[39] = 0.0;
   out_3424858624905544886[40] = 0.0;
   out_3424858624905544886[41] = 0.0;
   out_3424858624905544886[42] = 0.0;
   out_3424858624905544886[43] = 0.0;
   out_3424858624905544886[44] = 0.0;
   out_3424858624905544886[45] = 0.0;
   out_3424858624905544886[46] = 0.0;
   out_3424858624905544886[47] = 0.0;
   out_3424858624905544886[48] = 0.0;
   out_3424858624905544886[49] = 0.0;
   out_3424858624905544886[50] = 0.0;
   out_3424858624905544886[51] = 0.0;
   out_3424858624905544886[52] = 0.0;
   out_3424858624905544886[53] = 0.0;
   out_3424858624905544886[54] = 0.0;
   out_3424858624905544886[55] = 0.0;
   out_3424858624905544886[56] = 0.0;
   out_3424858624905544886[57] = 1.0;
   out_3424858624905544886[58] = 0.0;
   out_3424858624905544886[59] = 0.0;
   out_3424858624905544886[60] = 0.0;
   out_3424858624905544886[61] = 0.0;
   out_3424858624905544886[62] = 0.0;
   out_3424858624905544886[63] = 0.0;
   out_3424858624905544886[64] = 0.0;
   out_3424858624905544886[65] = 0.0;
   out_3424858624905544886[66] = 0.0;
   out_3424858624905544886[67] = 0.0;
   out_3424858624905544886[68] = 0.0;
   out_3424858624905544886[69] = 0.0;
   out_3424858624905544886[70] = 0.0;
   out_3424858624905544886[71] = 0.0;
   out_3424858624905544886[72] = 0.0;
   out_3424858624905544886[73] = 0.0;
   out_3424858624905544886[74] = 0.0;
   out_3424858624905544886[75] = 0.0;
   out_3424858624905544886[76] = 1.0;
   out_3424858624905544886[77] = 0.0;
   out_3424858624905544886[78] = 0.0;
   out_3424858624905544886[79] = 0.0;
   out_3424858624905544886[80] = 0.0;
   out_3424858624905544886[81] = 0.0;
   out_3424858624905544886[82] = 0.0;
   out_3424858624905544886[83] = 0.0;
   out_3424858624905544886[84] = 0.0;
   out_3424858624905544886[85] = 0.0;
   out_3424858624905544886[86] = 0.0;
   out_3424858624905544886[87] = 0.0;
   out_3424858624905544886[88] = 0.0;
   out_3424858624905544886[89] = 0.0;
   out_3424858624905544886[90] = 0.0;
   out_3424858624905544886[91] = 0.0;
   out_3424858624905544886[92] = 0.0;
   out_3424858624905544886[93] = 0.0;
   out_3424858624905544886[94] = 0.0;
   out_3424858624905544886[95] = 1.0;
   out_3424858624905544886[96] = 0.0;
   out_3424858624905544886[97] = 0.0;
   out_3424858624905544886[98] = 0.0;
   out_3424858624905544886[99] = 0.0;
   out_3424858624905544886[100] = 0.0;
   out_3424858624905544886[101] = 0.0;
   out_3424858624905544886[102] = 0.0;
   out_3424858624905544886[103] = 0.0;
   out_3424858624905544886[104] = 0.0;
   out_3424858624905544886[105] = 0.0;
   out_3424858624905544886[106] = 0.0;
   out_3424858624905544886[107] = 0.0;
   out_3424858624905544886[108] = 0.0;
   out_3424858624905544886[109] = 0.0;
   out_3424858624905544886[110] = 0.0;
   out_3424858624905544886[111] = 0.0;
   out_3424858624905544886[112] = 0.0;
   out_3424858624905544886[113] = 0.0;
   out_3424858624905544886[114] = 1.0;
   out_3424858624905544886[115] = 0.0;
   out_3424858624905544886[116] = 0.0;
   out_3424858624905544886[117] = 0.0;
   out_3424858624905544886[118] = 0.0;
   out_3424858624905544886[119] = 0.0;
   out_3424858624905544886[120] = 0.0;
   out_3424858624905544886[121] = 0.0;
   out_3424858624905544886[122] = 0.0;
   out_3424858624905544886[123] = 0.0;
   out_3424858624905544886[124] = 0.0;
   out_3424858624905544886[125] = 0.0;
   out_3424858624905544886[126] = 0.0;
   out_3424858624905544886[127] = 0.0;
   out_3424858624905544886[128] = 0.0;
   out_3424858624905544886[129] = 0.0;
   out_3424858624905544886[130] = 0.0;
   out_3424858624905544886[131] = 0.0;
   out_3424858624905544886[132] = 0.0;
   out_3424858624905544886[133] = 1.0;
   out_3424858624905544886[134] = 0.0;
   out_3424858624905544886[135] = 0.0;
   out_3424858624905544886[136] = 0.0;
   out_3424858624905544886[137] = 0.0;
   out_3424858624905544886[138] = 0.0;
   out_3424858624905544886[139] = 0.0;
   out_3424858624905544886[140] = 0.0;
   out_3424858624905544886[141] = 0.0;
   out_3424858624905544886[142] = 0.0;
   out_3424858624905544886[143] = 0.0;
   out_3424858624905544886[144] = 0.0;
   out_3424858624905544886[145] = 0.0;
   out_3424858624905544886[146] = 0.0;
   out_3424858624905544886[147] = 0.0;
   out_3424858624905544886[148] = 0.0;
   out_3424858624905544886[149] = 0.0;
   out_3424858624905544886[150] = 0.0;
   out_3424858624905544886[151] = 0.0;
   out_3424858624905544886[152] = 1.0;
   out_3424858624905544886[153] = 0.0;
   out_3424858624905544886[154] = 0.0;
   out_3424858624905544886[155] = 0.0;
   out_3424858624905544886[156] = 0.0;
   out_3424858624905544886[157] = 0.0;
   out_3424858624905544886[158] = 0.0;
   out_3424858624905544886[159] = 0.0;
   out_3424858624905544886[160] = 0.0;
   out_3424858624905544886[161] = 0.0;
   out_3424858624905544886[162] = 0.0;
   out_3424858624905544886[163] = 0.0;
   out_3424858624905544886[164] = 0.0;
   out_3424858624905544886[165] = 0.0;
   out_3424858624905544886[166] = 0.0;
   out_3424858624905544886[167] = 0.0;
   out_3424858624905544886[168] = 0.0;
   out_3424858624905544886[169] = 0.0;
   out_3424858624905544886[170] = 0.0;
   out_3424858624905544886[171] = 1.0;
   out_3424858624905544886[172] = 0.0;
   out_3424858624905544886[173] = 0.0;
   out_3424858624905544886[174] = 0.0;
   out_3424858624905544886[175] = 0.0;
   out_3424858624905544886[176] = 0.0;
   out_3424858624905544886[177] = 0.0;
   out_3424858624905544886[178] = 0.0;
   out_3424858624905544886[179] = 0.0;
   out_3424858624905544886[180] = 0.0;
   out_3424858624905544886[181] = 0.0;
   out_3424858624905544886[182] = 0.0;
   out_3424858624905544886[183] = 0.0;
   out_3424858624905544886[184] = 0.0;
   out_3424858624905544886[185] = 0.0;
   out_3424858624905544886[186] = 0.0;
   out_3424858624905544886[187] = 0.0;
   out_3424858624905544886[188] = 0.0;
   out_3424858624905544886[189] = 0.0;
   out_3424858624905544886[190] = 1.0;
   out_3424858624905544886[191] = 0.0;
   out_3424858624905544886[192] = 0.0;
   out_3424858624905544886[193] = 0.0;
   out_3424858624905544886[194] = 0.0;
   out_3424858624905544886[195] = 0.0;
   out_3424858624905544886[196] = 0.0;
   out_3424858624905544886[197] = 0.0;
   out_3424858624905544886[198] = 0.0;
   out_3424858624905544886[199] = 0.0;
   out_3424858624905544886[200] = 0.0;
   out_3424858624905544886[201] = 0.0;
   out_3424858624905544886[202] = 0.0;
   out_3424858624905544886[203] = 0.0;
   out_3424858624905544886[204] = 0.0;
   out_3424858624905544886[205] = 0.0;
   out_3424858624905544886[206] = 0.0;
   out_3424858624905544886[207] = 0.0;
   out_3424858624905544886[208] = 0.0;
   out_3424858624905544886[209] = 1.0;
   out_3424858624905544886[210] = 0.0;
   out_3424858624905544886[211] = 0.0;
   out_3424858624905544886[212] = 0.0;
   out_3424858624905544886[213] = 0.0;
   out_3424858624905544886[214] = 0.0;
   out_3424858624905544886[215] = 0.0;
   out_3424858624905544886[216] = 0.0;
   out_3424858624905544886[217] = 0.0;
   out_3424858624905544886[218] = 0.0;
   out_3424858624905544886[219] = 0.0;
   out_3424858624905544886[220] = 0.0;
   out_3424858624905544886[221] = 0.0;
   out_3424858624905544886[222] = 0.0;
   out_3424858624905544886[223] = 0.0;
   out_3424858624905544886[224] = 0.0;
   out_3424858624905544886[225] = 0.0;
   out_3424858624905544886[226] = 0.0;
   out_3424858624905544886[227] = 0.0;
   out_3424858624905544886[228] = 1.0;
   out_3424858624905544886[229] = 0.0;
   out_3424858624905544886[230] = 0.0;
   out_3424858624905544886[231] = 0.0;
   out_3424858624905544886[232] = 0.0;
   out_3424858624905544886[233] = 0.0;
   out_3424858624905544886[234] = 0.0;
   out_3424858624905544886[235] = 0.0;
   out_3424858624905544886[236] = 0.0;
   out_3424858624905544886[237] = 0.0;
   out_3424858624905544886[238] = 0.0;
   out_3424858624905544886[239] = 0.0;
   out_3424858624905544886[240] = 0.0;
   out_3424858624905544886[241] = 0.0;
   out_3424858624905544886[242] = 0.0;
   out_3424858624905544886[243] = 0.0;
   out_3424858624905544886[244] = 0.0;
   out_3424858624905544886[245] = 0.0;
   out_3424858624905544886[246] = 0.0;
   out_3424858624905544886[247] = 1.0;
   out_3424858624905544886[248] = 0.0;
   out_3424858624905544886[249] = 0.0;
   out_3424858624905544886[250] = 0.0;
   out_3424858624905544886[251] = 0.0;
   out_3424858624905544886[252] = 0.0;
   out_3424858624905544886[253] = 0.0;
   out_3424858624905544886[254] = 0.0;
   out_3424858624905544886[255] = 0.0;
   out_3424858624905544886[256] = 0.0;
   out_3424858624905544886[257] = 0.0;
   out_3424858624905544886[258] = 0.0;
   out_3424858624905544886[259] = 0.0;
   out_3424858624905544886[260] = 0.0;
   out_3424858624905544886[261] = 0.0;
   out_3424858624905544886[262] = 0.0;
   out_3424858624905544886[263] = 0.0;
   out_3424858624905544886[264] = 0.0;
   out_3424858624905544886[265] = 0.0;
   out_3424858624905544886[266] = 1.0;
   out_3424858624905544886[267] = 0.0;
   out_3424858624905544886[268] = 0.0;
   out_3424858624905544886[269] = 0.0;
   out_3424858624905544886[270] = 0.0;
   out_3424858624905544886[271] = 0.0;
   out_3424858624905544886[272] = 0.0;
   out_3424858624905544886[273] = 0.0;
   out_3424858624905544886[274] = 0.0;
   out_3424858624905544886[275] = 0.0;
   out_3424858624905544886[276] = 0.0;
   out_3424858624905544886[277] = 0.0;
   out_3424858624905544886[278] = 0.0;
   out_3424858624905544886[279] = 0.0;
   out_3424858624905544886[280] = 0.0;
   out_3424858624905544886[281] = 0.0;
   out_3424858624905544886[282] = 0.0;
   out_3424858624905544886[283] = 0.0;
   out_3424858624905544886[284] = 0.0;
   out_3424858624905544886[285] = 1.0;
   out_3424858624905544886[286] = 0.0;
   out_3424858624905544886[287] = 0.0;
   out_3424858624905544886[288] = 0.0;
   out_3424858624905544886[289] = 0.0;
   out_3424858624905544886[290] = 0.0;
   out_3424858624905544886[291] = 0.0;
   out_3424858624905544886[292] = 0.0;
   out_3424858624905544886[293] = 0.0;
   out_3424858624905544886[294] = 0.0;
   out_3424858624905544886[295] = 0.0;
   out_3424858624905544886[296] = 0.0;
   out_3424858624905544886[297] = 0.0;
   out_3424858624905544886[298] = 0.0;
   out_3424858624905544886[299] = 0.0;
   out_3424858624905544886[300] = 0.0;
   out_3424858624905544886[301] = 0.0;
   out_3424858624905544886[302] = 0.0;
   out_3424858624905544886[303] = 0.0;
   out_3424858624905544886[304] = 1.0;
   out_3424858624905544886[305] = 0.0;
   out_3424858624905544886[306] = 0.0;
   out_3424858624905544886[307] = 0.0;
   out_3424858624905544886[308] = 0.0;
   out_3424858624905544886[309] = 0.0;
   out_3424858624905544886[310] = 0.0;
   out_3424858624905544886[311] = 0.0;
   out_3424858624905544886[312] = 0.0;
   out_3424858624905544886[313] = 0.0;
   out_3424858624905544886[314] = 0.0;
   out_3424858624905544886[315] = 0.0;
   out_3424858624905544886[316] = 0.0;
   out_3424858624905544886[317] = 0.0;
   out_3424858624905544886[318] = 0.0;
   out_3424858624905544886[319] = 0.0;
   out_3424858624905544886[320] = 0.0;
   out_3424858624905544886[321] = 0.0;
   out_3424858624905544886[322] = 0.0;
   out_3424858624905544886[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6956505280641818693) {
   out_6956505280641818693[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6956505280641818693[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6956505280641818693[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6956505280641818693[3] = dt*state[12] + state[3];
   out_6956505280641818693[4] = dt*state[13] + state[4];
   out_6956505280641818693[5] = dt*state[14] + state[5];
   out_6956505280641818693[6] = state[6];
   out_6956505280641818693[7] = state[7];
   out_6956505280641818693[8] = state[8];
   out_6956505280641818693[9] = state[9];
   out_6956505280641818693[10] = state[10];
   out_6956505280641818693[11] = state[11];
   out_6956505280641818693[12] = state[12];
   out_6956505280641818693[13] = state[13];
   out_6956505280641818693[14] = state[14];
   out_6956505280641818693[15] = state[15];
   out_6956505280641818693[16] = state[16];
   out_6956505280641818693[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4753955652213576676) {
   out_4753955652213576676[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4753955652213576676[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4753955652213576676[2] = 0;
   out_4753955652213576676[3] = 0;
   out_4753955652213576676[4] = 0;
   out_4753955652213576676[5] = 0;
   out_4753955652213576676[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4753955652213576676[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4753955652213576676[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4753955652213576676[9] = 0;
   out_4753955652213576676[10] = 0;
   out_4753955652213576676[11] = 0;
   out_4753955652213576676[12] = 0;
   out_4753955652213576676[13] = 0;
   out_4753955652213576676[14] = 0;
   out_4753955652213576676[15] = 0;
   out_4753955652213576676[16] = 0;
   out_4753955652213576676[17] = 0;
   out_4753955652213576676[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4753955652213576676[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4753955652213576676[20] = 0;
   out_4753955652213576676[21] = 0;
   out_4753955652213576676[22] = 0;
   out_4753955652213576676[23] = 0;
   out_4753955652213576676[24] = 0;
   out_4753955652213576676[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4753955652213576676[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4753955652213576676[27] = 0;
   out_4753955652213576676[28] = 0;
   out_4753955652213576676[29] = 0;
   out_4753955652213576676[30] = 0;
   out_4753955652213576676[31] = 0;
   out_4753955652213576676[32] = 0;
   out_4753955652213576676[33] = 0;
   out_4753955652213576676[34] = 0;
   out_4753955652213576676[35] = 0;
   out_4753955652213576676[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4753955652213576676[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4753955652213576676[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4753955652213576676[39] = 0;
   out_4753955652213576676[40] = 0;
   out_4753955652213576676[41] = 0;
   out_4753955652213576676[42] = 0;
   out_4753955652213576676[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4753955652213576676[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4753955652213576676[45] = 0;
   out_4753955652213576676[46] = 0;
   out_4753955652213576676[47] = 0;
   out_4753955652213576676[48] = 0;
   out_4753955652213576676[49] = 0;
   out_4753955652213576676[50] = 0;
   out_4753955652213576676[51] = 0;
   out_4753955652213576676[52] = 0;
   out_4753955652213576676[53] = 0;
   out_4753955652213576676[54] = 0;
   out_4753955652213576676[55] = 0;
   out_4753955652213576676[56] = 0;
   out_4753955652213576676[57] = 1;
   out_4753955652213576676[58] = 0;
   out_4753955652213576676[59] = 0;
   out_4753955652213576676[60] = 0;
   out_4753955652213576676[61] = 0;
   out_4753955652213576676[62] = 0;
   out_4753955652213576676[63] = 0;
   out_4753955652213576676[64] = 0;
   out_4753955652213576676[65] = 0;
   out_4753955652213576676[66] = dt;
   out_4753955652213576676[67] = 0;
   out_4753955652213576676[68] = 0;
   out_4753955652213576676[69] = 0;
   out_4753955652213576676[70] = 0;
   out_4753955652213576676[71] = 0;
   out_4753955652213576676[72] = 0;
   out_4753955652213576676[73] = 0;
   out_4753955652213576676[74] = 0;
   out_4753955652213576676[75] = 0;
   out_4753955652213576676[76] = 1;
   out_4753955652213576676[77] = 0;
   out_4753955652213576676[78] = 0;
   out_4753955652213576676[79] = 0;
   out_4753955652213576676[80] = 0;
   out_4753955652213576676[81] = 0;
   out_4753955652213576676[82] = 0;
   out_4753955652213576676[83] = 0;
   out_4753955652213576676[84] = 0;
   out_4753955652213576676[85] = dt;
   out_4753955652213576676[86] = 0;
   out_4753955652213576676[87] = 0;
   out_4753955652213576676[88] = 0;
   out_4753955652213576676[89] = 0;
   out_4753955652213576676[90] = 0;
   out_4753955652213576676[91] = 0;
   out_4753955652213576676[92] = 0;
   out_4753955652213576676[93] = 0;
   out_4753955652213576676[94] = 0;
   out_4753955652213576676[95] = 1;
   out_4753955652213576676[96] = 0;
   out_4753955652213576676[97] = 0;
   out_4753955652213576676[98] = 0;
   out_4753955652213576676[99] = 0;
   out_4753955652213576676[100] = 0;
   out_4753955652213576676[101] = 0;
   out_4753955652213576676[102] = 0;
   out_4753955652213576676[103] = 0;
   out_4753955652213576676[104] = dt;
   out_4753955652213576676[105] = 0;
   out_4753955652213576676[106] = 0;
   out_4753955652213576676[107] = 0;
   out_4753955652213576676[108] = 0;
   out_4753955652213576676[109] = 0;
   out_4753955652213576676[110] = 0;
   out_4753955652213576676[111] = 0;
   out_4753955652213576676[112] = 0;
   out_4753955652213576676[113] = 0;
   out_4753955652213576676[114] = 1;
   out_4753955652213576676[115] = 0;
   out_4753955652213576676[116] = 0;
   out_4753955652213576676[117] = 0;
   out_4753955652213576676[118] = 0;
   out_4753955652213576676[119] = 0;
   out_4753955652213576676[120] = 0;
   out_4753955652213576676[121] = 0;
   out_4753955652213576676[122] = 0;
   out_4753955652213576676[123] = 0;
   out_4753955652213576676[124] = 0;
   out_4753955652213576676[125] = 0;
   out_4753955652213576676[126] = 0;
   out_4753955652213576676[127] = 0;
   out_4753955652213576676[128] = 0;
   out_4753955652213576676[129] = 0;
   out_4753955652213576676[130] = 0;
   out_4753955652213576676[131] = 0;
   out_4753955652213576676[132] = 0;
   out_4753955652213576676[133] = 1;
   out_4753955652213576676[134] = 0;
   out_4753955652213576676[135] = 0;
   out_4753955652213576676[136] = 0;
   out_4753955652213576676[137] = 0;
   out_4753955652213576676[138] = 0;
   out_4753955652213576676[139] = 0;
   out_4753955652213576676[140] = 0;
   out_4753955652213576676[141] = 0;
   out_4753955652213576676[142] = 0;
   out_4753955652213576676[143] = 0;
   out_4753955652213576676[144] = 0;
   out_4753955652213576676[145] = 0;
   out_4753955652213576676[146] = 0;
   out_4753955652213576676[147] = 0;
   out_4753955652213576676[148] = 0;
   out_4753955652213576676[149] = 0;
   out_4753955652213576676[150] = 0;
   out_4753955652213576676[151] = 0;
   out_4753955652213576676[152] = 1;
   out_4753955652213576676[153] = 0;
   out_4753955652213576676[154] = 0;
   out_4753955652213576676[155] = 0;
   out_4753955652213576676[156] = 0;
   out_4753955652213576676[157] = 0;
   out_4753955652213576676[158] = 0;
   out_4753955652213576676[159] = 0;
   out_4753955652213576676[160] = 0;
   out_4753955652213576676[161] = 0;
   out_4753955652213576676[162] = 0;
   out_4753955652213576676[163] = 0;
   out_4753955652213576676[164] = 0;
   out_4753955652213576676[165] = 0;
   out_4753955652213576676[166] = 0;
   out_4753955652213576676[167] = 0;
   out_4753955652213576676[168] = 0;
   out_4753955652213576676[169] = 0;
   out_4753955652213576676[170] = 0;
   out_4753955652213576676[171] = 1;
   out_4753955652213576676[172] = 0;
   out_4753955652213576676[173] = 0;
   out_4753955652213576676[174] = 0;
   out_4753955652213576676[175] = 0;
   out_4753955652213576676[176] = 0;
   out_4753955652213576676[177] = 0;
   out_4753955652213576676[178] = 0;
   out_4753955652213576676[179] = 0;
   out_4753955652213576676[180] = 0;
   out_4753955652213576676[181] = 0;
   out_4753955652213576676[182] = 0;
   out_4753955652213576676[183] = 0;
   out_4753955652213576676[184] = 0;
   out_4753955652213576676[185] = 0;
   out_4753955652213576676[186] = 0;
   out_4753955652213576676[187] = 0;
   out_4753955652213576676[188] = 0;
   out_4753955652213576676[189] = 0;
   out_4753955652213576676[190] = 1;
   out_4753955652213576676[191] = 0;
   out_4753955652213576676[192] = 0;
   out_4753955652213576676[193] = 0;
   out_4753955652213576676[194] = 0;
   out_4753955652213576676[195] = 0;
   out_4753955652213576676[196] = 0;
   out_4753955652213576676[197] = 0;
   out_4753955652213576676[198] = 0;
   out_4753955652213576676[199] = 0;
   out_4753955652213576676[200] = 0;
   out_4753955652213576676[201] = 0;
   out_4753955652213576676[202] = 0;
   out_4753955652213576676[203] = 0;
   out_4753955652213576676[204] = 0;
   out_4753955652213576676[205] = 0;
   out_4753955652213576676[206] = 0;
   out_4753955652213576676[207] = 0;
   out_4753955652213576676[208] = 0;
   out_4753955652213576676[209] = 1;
   out_4753955652213576676[210] = 0;
   out_4753955652213576676[211] = 0;
   out_4753955652213576676[212] = 0;
   out_4753955652213576676[213] = 0;
   out_4753955652213576676[214] = 0;
   out_4753955652213576676[215] = 0;
   out_4753955652213576676[216] = 0;
   out_4753955652213576676[217] = 0;
   out_4753955652213576676[218] = 0;
   out_4753955652213576676[219] = 0;
   out_4753955652213576676[220] = 0;
   out_4753955652213576676[221] = 0;
   out_4753955652213576676[222] = 0;
   out_4753955652213576676[223] = 0;
   out_4753955652213576676[224] = 0;
   out_4753955652213576676[225] = 0;
   out_4753955652213576676[226] = 0;
   out_4753955652213576676[227] = 0;
   out_4753955652213576676[228] = 1;
   out_4753955652213576676[229] = 0;
   out_4753955652213576676[230] = 0;
   out_4753955652213576676[231] = 0;
   out_4753955652213576676[232] = 0;
   out_4753955652213576676[233] = 0;
   out_4753955652213576676[234] = 0;
   out_4753955652213576676[235] = 0;
   out_4753955652213576676[236] = 0;
   out_4753955652213576676[237] = 0;
   out_4753955652213576676[238] = 0;
   out_4753955652213576676[239] = 0;
   out_4753955652213576676[240] = 0;
   out_4753955652213576676[241] = 0;
   out_4753955652213576676[242] = 0;
   out_4753955652213576676[243] = 0;
   out_4753955652213576676[244] = 0;
   out_4753955652213576676[245] = 0;
   out_4753955652213576676[246] = 0;
   out_4753955652213576676[247] = 1;
   out_4753955652213576676[248] = 0;
   out_4753955652213576676[249] = 0;
   out_4753955652213576676[250] = 0;
   out_4753955652213576676[251] = 0;
   out_4753955652213576676[252] = 0;
   out_4753955652213576676[253] = 0;
   out_4753955652213576676[254] = 0;
   out_4753955652213576676[255] = 0;
   out_4753955652213576676[256] = 0;
   out_4753955652213576676[257] = 0;
   out_4753955652213576676[258] = 0;
   out_4753955652213576676[259] = 0;
   out_4753955652213576676[260] = 0;
   out_4753955652213576676[261] = 0;
   out_4753955652213576676[262] = 0;
   out_4753955652213576676[263] = 0;
   out_4753955652213576676[264] = 0;
   out_4753955652213576676[265] = 0;
   out_4753955652213576676[266] = 1;
   out_4753955652213576676[267] = 0;
   out_4753955652213576676[268] = 0;
   out_4753955652213576676[269] = 0;
   out_4753955652213576676[270] = 0;
   out_4753955652213576676[271] = 0;
   out_4753955652213576676[272] = 0;
   out_4753955652213576676[273] = 0;
   out_4753955652213576676[274] = 0;
   out_4753955652213576676[275] = 0;
   out_4753955652213576676[276] = 0;
   out_4753955652213576676[277] = 0;
   out_4753955652213576676[278] = 0;
   out_4753955652213576676[279] = 0;
   out_4753955652213576676[280] = 0;
   out_4753955652213576676[281] = 0;
   out_4753955652213576676[282] = 0;
   out_4753955652213576676[283] = 0;
   out_4753955652213576676[284] = 0;
   out_4753955652213576676[285] = 1;
   out_4753955652213576676[286] = 0;
   out_4753955652213576676[287] = 0;
   out_4753955652213576676[288] = 0;
   out_4753955652213576676[289] = 0;
   out_4753955652213576676[290] = 0;
   out_4753955652213576676[291] = 0;
   out_4753955652213576676[292] = 0;
   out_4753955652213576676[293] = 0;
   out_4753955652213576676[294] = 0;
   out_4753955652213576676[295] = 0;
   out_4753955652213576676[296] = 0;
   out_4753955652213576676[297] = 0;
   out_4753955652213576676[298] = 0;
   out_4753955652213576676[299] = 0;
   out_4753955652213576676[300] = 0;
   out_4753955652213576676[301] = 0;
   out_4753955652213576676[302] = 0;
   out_4753955652213576676[303] = 0;
   out_4753955652213576676[304] = 1;
   out_4753955652213576676[305] = 0;
   out_4753955652213576676[306] = 0;
   out_4753955652213576676[307] = 0;
   out_4753955652213576676[308] = 0;
   out_4753955652213576676[309] = 0;
   out_4753955652213576676[310] = 0;
   out_4753955652213576676[311] = 0;
   out_4753955652213576676[312] = 0;
   out_4753955652213576676[313] = 0;
   out_4753955652213576676[314] = 0;
   out_4753955652213576676[315] = 0;
   out_4753955652213576676[316] = 0;
   out_4753955652213576676[317] = 0;
   out_4753955652213576676[318] = 0;
   out_4753955652213576676[319] = 0;
   out_4753955652213576676[320] = 0;
   out_4753955652213576676[321] = 0;
   out_4753955652213576676[322] = 0;
   out_4753955652213576676[323] = 1;
}
void h_4(double *state, double *unused, double *out_5605636478763056645) {
   out_5605636478763056645[0] = state[6] + state[9];
   out_5605636478763056645[1] = state[7] + state[10];
   out_5605636478763056645[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4179019626960257493) {
   out_4179019626960257493[0] = 0;
   out_4179019626960257493[1] = 0;
   out_4179019626960257493[2] = 0;
   out_4179019626960257493[3] = 0;
   out_4179019626960257493[4] = 0;
   out_4179019626960257493[5] = 0;
   out_4179019626960257493[6] = 1;
   out_4179019626960257493[7] = 0;
   out_4179019626960257493[8] = 0;
   out_4179019626960257493[9] = 1;
   out_4179019626960257493[10] = 0;
   out_4179019626960257493[11] = 0;
   out_4179019626960257493[12] = 0;
   out_4179019626960257493[13] = 0;
   out_4179019626960257493[14] = 0;
   out_4179019626960257493[15] = 0;
   out_4179019626960257493[16] = 0;
   out_4179019626960257493[17] = 0;
   out_4179019626960257493[18] = 0;
   out_4179019626960257493[19] = 0;
   out_4179019626960257493[20] = 0;
   out_4179019626960257493[21] = 0;
   out_4179019626960257493[22] = 0;
   out_4179019626960257493[23] = 0;
   out_4179019626960257493[24] = 0;
   out_4179019626960257493[25] = 1;
   out_4179019626960257493[26] = 0;
   out_4179019626960257493[27] = 0;
   out_4179019626960257493[28] = 1;
   out_4179019626960257493[29] = 0;
   out_4179019626960257493[30] = 0;
   out_4179019626960257493[31] = 0;
   out_4179019626960257493[32] = 0;
   out_4179019626960257493[33] = 0;
   out_4179019626960257493[34] = 0;
   out_4179019626960257493[35] = 0;
   out_4179019626960257493[36] = 0;
   out_4179019626960257493[37] = 0;
   out_4179019626960257493[38] = 0;
   out_4179019626960257493[39] = 0;
   out_4179019626960257493[40] = 0;
   out_4179019626960257493[41] = 0;
   out_4179019626960257493[42] = 0;
   out_4179019626960257493[43] = 0;
   out_4179019626960257493[44] = 1;
   out_4179019626960257493[45] = 0;
   out_4179019626960257493[46] = 0;
   out_4179019626960257493[47] = 1;
   out_4179019626960257493[48] = 0;
   out_4179019626960257493[49] = 0;
   out_4179019626960257493[50] = 0;
   out_4179019626960257493[51] = 0;
   out_4179019626960257493[52] = 0;
   out_4179019626960257493[53] = 0;
}
void h_10(double *state, double *unused, double *out_3279884597631109591) {
   out_3279884597631109591[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3279884597631109591[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3279884597631109591[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3190556599962023573) {
   out_3190556599962023573[0] = 0;
   out_3190556599962023573[1] = 9.8100000000000005*cos(state[1]);
   out_3190556599962023573[2] = 0;
   out_3190556599962023573[3] = 0;
   out_3190556599962023573[4] = -state[8];
   out_3190556599962023573[5] = state[7];
   out_3190556599962023573[6] = 0;
   out_3190556599962023573[7] = state[5];
   out_3190556599962023573[8] = -state[4];
   out_3190556599962023573[9] = 0;
   out_3190556599962023573[10] = 0;
   out_3190556599962023573[11] = 0;
   out_3190556599962023573[12] = 1;
   out_3190556599962023573[13] = 0;
   out_3190556599962023573[14] = 0;
   out_3190556599962023573[15] = 1;
   out_3190556599962023573[16] = 0;
   out_3190556599962023573[17] = 0;
   out_3190556599962023573[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3190556599962023573[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3190556599962023573[20] = 0;
   out_3190556599962023573[21] = state[8];
   out_3190556599962023573[22] = 0;
   out_3190556599962023573[23] = -state[6];
   out_3190556599962023573[24] = -state[5];
   out_3190556599962023573[25] = 0;
   out_3190556599962023573[26] = state[3];
   out_3190556599962023573[27] = 0;
   out_3190556599962023573[28] = 0;
   out_3190556599962023573[29] = 0;
   out_3190556599962023573[30] = 0;
   out_3190556599962023573[31] = 1;
   out_3190556599962023573[32] = 0;
   out_3190556599962023573[33] = 0;
   out_3190556599962023573[34] = 1;
   out_3190556599962023573[35] = 0;
   out_3190556599962023573[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3190556599962023573[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3190556599962023573[38] = 0;
   out_3190556599962023573[39] = -state[7];
   out_3190556599962023573[40] = state[6];
   out_3190556599962023573[41] = 0;
   out_3190556599962023573[42] = state[4];
   out_3190556599962023573[43] = -state[3];
   out_3190556599962023573[44] = 0;
   out_3190556599962023573[45] = 0;
   out_3190556599962023573[46] = 0;
   out_3190556599962023573[47] = 0;
   out_3190556599962023573[48] = 0;
   out_3190556599962023573[49] = 0;
   out_3190556599962023573[50] = 1;
   out_3190556599962023573[51] = 0;
   out_3190556599962023573[52] = 0;
   out_3190556599962023573[53] = 1;
}
void h_13(double *state, double *unused, double *out_230694173360480530) {
   out_230694173360480530[0] = state[3];
   out_230694173360480530[1] = state[4];
   out_230694173360480530[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6657093238432593194) {
   out_6657093238432593194[0] = 0;
   out_6657093238432593194[1] = 0;
   out_6657093238432593194[2] = 0;
   out_6657093238432593194[3] = 1;
   out_6657093238432593194[4] = 0;
   out_6657093238432593194[5] = 0;
   out_6657093238432593194[6] = 0;
   out_6657093238432593194[7] = 0;
   out_6657093238432593194[8] = 0;
   out_6657093238432593194[9] = 0;
   out_6657093238432593194[10] = 0;
   out_6657093238432593194[11] = 0;
   out_6657093238432593194[12] = 0;
   out_6657093238432593194[13] = 0;
   out_6657093238432593194[14] = 0;
   out_6657093238432593194[15] = 0;
   out_6657093238432593194[16] = 0;
   out_6657093238432593194[17] = 0;
   out_6657093238432593194[18] = 0;
   out_6657093238432593194[19] = 0;
   out_6657093238432593194[20] = 0;
   out_6657093238432593194[21] = 0;
   out_6657093238432593194[22] = 1;
   out_6657093238432593194[23] = 0;
   out_6657093238432593194[24] = 0;
   out_6657093238432593194[25] = 0;
   out_6657093238432593194[26] = 0;
   out_6657093238432593194[27] = 0;
   out_6657093238432593194[28] = 0;
   out_6657093238432593194[29] = 0;
   out_6657093238432593194[30] = 0;
   out_6657093238432593194[31] = 0;
   out_6657093238432593194[32] = 0;
   out_6657093238432593194[33] = 0;
   out_6657093238432593194[34] = 0;
   out_6657093238432593194[35] = 0;
   out_6657093238432593194[36] = 0;
   out_6657093238432593194[37] = 0;
   out_6657093238432593194[38] = 0;
   out_6657093238432593194[39] = 0;
   out_6657093238432593194[40] = 0;
   out_6657093238432593194[41] = 1;
   out_6657093238432593194[42] = 0;
   out_6657093238432593194[43] = 0;
   out_6657093238432593194[44] = 0;
   out_6657093238432593194[45] = 0;
   out_6657093238432593194[46] = 0;
   out_6657093238432593194[47] = 0;
   out_6657093238432593194[48] = 0;
   out_6657093238432593194[49] = 0;
   out_6657093238432593194[50] = 0;
   out_6657093238432593194[51] = 0;
   out_6657093238432593194[52] = 0;
   out_6657093238432593194[53] = 0;
}
void h_14(double *state, double *unused, double *out_1120624520725849136) {
   out_1120624520725849136[0] = state[6];
   out_1120624520725849136[1] = state[7];
   out_1120624520725849136[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8142260483299742022) {
   out_8142260483299742022[0] = 0;
   out_8142260483299742022[1] = 0;
   out_8142260483299742022[2] = 0;
   out_8142260483299742022[3] = 0;
   out_8142260483299742022[4] = 0;
   out_8142260483299742022[5] = 0;
   out_8142260483299742022[6] = 1;
   out_8142260483299742022[7] = 0;
   out_8142260483299742022[8] = 0;
   out_8142260483299742022[9] = 0;
   out_8142260483299742022[10] = 0;
   out_8142260483299742022[11] = 0;
   out_8142260483299742022[12] = 0;
   out_8142260483299742022[13] = 0;
   out_8142260483299742022[14] = 0;
   out_8142260483299742022[15] = 0;
   out_8142260483299742022[16] = 0;
   out_8142260483299742022[17] = 0;
   out_8142260483299742022[18] = 0;
   out_8142260483299742022[19] = 0;
   out_8142260483299742022[20] = 0;
   out_8142260483299742022[21] = 0;
   out_8142260483299742022[22] = 0;
   out_8142260483299742022[23] = 0;
   out_8142260483299742022[24] = 0;
   out_8142260483299742022[25] = 1;
   out_8142260483299742022[26] = 0;
   out_8142260483299742022[27] = 0;
   out_8142260483299742022[28] = 0;
   out_8142260483299742022[29] = 0;
   out_8142260483299742022[30] = 0;
   out_8142260483299742022[31] = 0;
   out_8142260483299742022[32] = 0;
   out_8142260483299742022[33] = 0;
   out_8142260483299742022[34] = 0;
   out_8142260483299742022[35] = 0;
   out_8142260483299742022[36] = 0;
   out_8142260483299742022[37] = 0;
   out_8142260483299742022[38] = 0;
   out_8142260483299742022[39] = 0;
   out_8142260483299742022[40] = 0;
   out_8142260483299742022[41] = 0;
   out_8142260483299742022[42] = 0;
   out_8142260483299742022[43] = 0;
   out_8142260483299742022[44] = 1;
   out_8142260483299742022[45] = 0;
   out_8142260483299742022[46] = 0;
   out_8142260483299742022[47] = 0;
   out_8142260483299742022[48] = 0;
   out_8142260483299742022[49] = 0;
   out_8142260483299742022[50] = 0;
   out_8142260483299742022[51] = 0;
   out_8142260483299742022[52] = 0;
   out_8142260483299742022[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1877090198031843098) {
  err_fun(nom_x, delta_x, out_1877090198031843098);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4765871387657118050) {
  inv_err_fun(nom_x, true_x, out_4765871387657118050);
}
void pose_H_mod_fun(double *state, double *out_3424858624905544886) {
  H_mod_fun(state, out_3424858624905544886);
}
void pose_f_fun(double *state, double dt, double *out_6956505280641818693) {
  f_fun(state,  dt, out_6956505280641818693);
}
void pose_F_fun(double *state, double dt, double *out_4753955652213576676) {
  F_fun(state,  dt, out_4753955652213576676);
}
void pose_h_4(double *state, double *unused, double *out_5605636478763056645) {
  h_4(state, unused, out_5605636478763056645);
}
void pose_H_4(double *state, double *unused, double *out_4179019626960257493) {
  H_4(state, unused, out_4179019626960257493);
}
void pose_h_10(double *state, double *unused, double *out_3279884597631109591) {
  h_10(state, unused, out_3279884597631109591);
}
void pose_H_10(double *state, double *unused, double *out_3190556599962023573) {
  H_10(state, unused, out_3190556599962023573);
}
void pose_h_13(double *state, double *unused, double *out_230694173360480530) {
  h_13(state, unused, out_230694173360480530);
}
void pose_H_13(double *state, double *unused, double *out_6657093238432593194) {
  H_13(state, unused, out_6657093238432593194);
}
void pose_h_14(double *state, double *unused, double *out_1120624520725849136) {
  h_14(state, unused, out_1120624520725849136);
}
void pose_H_14(double *state, double *unused, double *out_8142260483299742022) {
  H_14(state, unused, out_8142260483299742022);
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
