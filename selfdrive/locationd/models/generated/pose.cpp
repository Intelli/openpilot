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
void err_fun(double *nom_x, double *delta_x, double *out_8005578165904155046) {
   out_8005578165904155046[0] = delta_x[0] + nom_x[0];
   out_8005578165904155046[1] = delta_x[1] + nom_x[1];
   out_8005578165904155046[2] = delta_x[2] + nom_x[2];
   out_8005578165904155046[3] = delta_x[3] + nom_x[3];
   out_8005578165904155046[4] = delta_x[4] + nom_x[4];
   out_8005578165904155046[5] = delta_x[5] + nom_x[5];
   out_8005578165904155046[6] = delta_x[6] + nom_x[6];
   out_8005578165904155046[7] = delta_x[7] + nom_x[7];
   out_8005578165904155046[8] = delta_x[8] + nom_x[8];
   out_8005578165904155046[9] = delta_x[9] + nom_x[9];
   out_8005578165904155046[10] = delta_x[10] + nom_x[10];
   out_8005578165904155046[11] = delta_x[11] + nom_x[11];
   out_8005578165904155046[12] = delta_x[12] + nom_x[12];
   out_8005578165904155046[13] = delta_x[13] + nom_x[13];
   out_8005578165904155046[14] = delta_x[14] + nom_x[14];
   out_8005578165904155046[15] = delta_x[15] + nom_x[15];
   out_8005578165904155046[16] = delta_x[16] + nom_x[16];
   out_8005578165904155046[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5771596986871161922) {
   out_5771596986871161922[0] = -nom_x[0] + true_x[0];
   out_5771596986871161922[1] = -nom_x[1] + true_x[1];
   out_5771596986871161922[2] = -nom_x[2] + true_x[2];
   out_5771596986871161922[3] = -nom_x[3] + true_x[3];
   out_5771596986871161922[4] = -nom_x[4] + true_x[4];
   out_5771596986871161922[5] = -nom_x[5] + true_x[5];
   out_5771596986871161922[6] = -nom_x[6] + true_x[6];
   out_5771596986871161922[7] = -nom_x[7] + true_x[7];
   out_5771596986871161922[8] = -nom_x[8] + true_x[8];
   out_5771596986871161922[9] = -nom_x[9] + true_x[9];
   out_5771596986871161922[10] = -nom_x[10] + true_x[10];
   out_5771596986871161922[11] = -nom_x[11] + true_x[11];
   out_5771596986871161922[12] = -nom_x[12] + true_x[12];
   out_5771596986871161922[13] = -nom_x[13] + true_x[13];
   out_5771596986871161922[14] = -nom_x[14] + true_x[14];
   out_5771596986871161922[15] = -nom_x[15] + true_x[15];
   out_5771596986871161922[16] = -nom_x[16] + true_x[16];
   out_5771596986871161922[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3288040166935413696) {
   out_3288040166935413696[0] = 1.0;
   out_3288040166935413696[1] = 0.0;
   out_3288040166935413696[2] = 0.0;
   out_3288040166935413696[3] = 0.0;
   out_3288040166935413696[4] = 0.0;
   out_3288040166935413696[5] = 0.0;
   out_3288040166935413696[6] = 0.0;
   out_3288040166935413696[7] = 0.0;
   out_3288040166935413696[8] = 0.0;
   out_3288040166935413696[9] = 0.0;
   out_3288040166935413696[10] = 0.0;
   out_3288040166935413696[11] = 0.0;
   out_3288040166935413696[12] = 0.0;
   out_3288040166935413696[13] = 0.0;
   out_3288040166935413696[14] = 0.0;
   out_3288040166935413696[15] = 0.0;
   out_3288040166935413696[16] = 0.0;
   out_3288040166935413696[17] = 0.0;
   out_3288040166935413696[18] = 0.0;
   out_3288040166935413696[19] = 1.0;
   out_3288040166935413696[20] = 0.0;
   out_3288040166935413696[21] = 0.0;
   out_3288040166935413696[22] = 0.0;
   out_3288040166935413696[23] = 0.0;
   out_3288040166935413696[24] = 0.0;
   out_3288040166935413696[25] = 0.0;
   out_3288040166935413696[26] = 0.0;
   out_3288040166935413696[27] = 0.0;
   out_3288040166935413696[28] = 0.0;
   out_3288040166935413696[29] = 0.0;
   out_3288040166935413696[30] = 0.0;
   out_3288040166935413696[31] = 0.0;
   out_3288040166935413696[32] = 0.0;
   out_3288040166935413696[33] = 0.0;
   out_3288040166935413696[34] = 0.0;
   out_3288040166935413696[35] = 0.0;
   out_3288040166935413696[36] = 0.0;
   out_3288040166935413696[37] = 0.0;
   out_3288040166935413696[38] = 1.0;
   out_3288040166935413696[39] = 0.0;
   out_3288040166935413696[40] = 0.0;
   out_3288040166935413696[41] = 0.0;
   out_3288040166935413696[42] = 0.0;
   out_3288040166935413696[43] = 0.0;
   out_3288040166935413696[44] = 0.0;
   out_3288040166935413696[45] = 0.0;
   out_3288040166935413696[46] = 0.0;
   out_3288040166935413696[47] = 0.0;
   out_3288040166935413696[48] = 0.0;
   out_3288040166935413696[49] = 0.0;
   out_3288040166935413696[50] = 0.0;
   out_3288040166935413696[51] = 0.0;
   out_3288040166935413696[52] = 0.0;
   out_3288040166935413696[53] = 0.0;
   out_3288040166935413696[54] = 0.0;
   out_3288040166935413696[55] = 0.0;
   out_3288040166935413696[56] = 0.0;
   out_3288040166935413696[57] = 1.0;
   out_3288040166935413696[58] = 0.0;
   out_3288040166935413696[59] = 0.0;
   out_3288040166935413696[60] = 0.0;
   out_3288040166935413696[61] = 0.0;
   out_3288040166935413696[62] = 0.0;
   out_3288040166935413696[63] = 0.0;
   out_3288040166935413696[64] = 0.0;
   out_3288040166935413696[65] = 0.0;
   out_3288040166935413696[66] = 0.0;
   out_3288040166935413696[67] = 0.0;
   out_3288040166935413696[68] = 0.0;
   out_3288040166935413696[69] = 0.0;
   out_3288040166935413696[70] = 0.0;
   out_3288040166935413696[71] = 0.0;
   out_3288040166935413696[72] = 0.0;
   out_3288040166935413696[73] = 0.0;
   out_3288040166935413696[74] = 0.0;
   out_3288040166935413696[75] = 0.0;
   out_3288040166935413696[76] = 1.0;
   out_3288040166935413696[77] = 0.0;
   out_3288040166935413696[78] = 0.0;
   out_3288040166935413696[79] = 0.0;
   out_3288040166935413696[80] = 0.0;
   out_3288040166935413696[81] = 0.0;
   out_3288040166935413696[82] = 0.0;
   out_3288040166935413696[83] = 0.0;
   out_3288040166935413696[84] = 0.0;
   out_3288040166935413696[85] = 0.0;
   out_3288040166935413696[86] = 0.0;
   out_3288040166935413696[87] = 0.0;
   out_3288040166935413696[88] = 0.0;
   out_3288040166935413696[89] = 0.0;
   out_3288040166935413696[90] = 0.0;
   out_3288040166935413696[91] = 0.0;
   out_3288040166935413696[92] = 0.0;
   out_3288040166935413696[93] = 0.0;
   out_3288040166935413696[94] = 0.0;
   out_3288040166935413696[95] = 1.0;
   out_3288040166935413696[96] = 0.0;
   out_3288040166935413696[97] = 0.0;
   out_3288040166935413696[98] = 0.0;
   out_3288040166935413696[99] = 0.0;
   out_3288040166935413696[100] = 0.0;
   out_3288040166935413696[101] = 0.0;
   out_3288040166935413696[102] = 0.0;
   out_3288040166935413696[103] = 0.0;
   out_3288040166935413696[104] = 0.0;
   out_3288040166935413696[105] = 0.0;
   out_3288040166935413696[106] = 0.0;
   out_3288040166935413696[107] = 0.0;
   out_3288040166935413696[108] = 0.0;
   out_3288040166935413696[109] = 0.0;
   out_3288040166935413696[110] = 0.0;
   out_3288040166935413696[111] = 0.0;
   out_3288040166935413696[112] = 0.0;
   out_3288040166935413696[113] = 0.0;
   out_3288040166935413696[114] = 1.0;
   out_3288040166935413696[115] = 0.0;
   out_3288040166935413696[116] = 0.0;
   out_3288040166935413696[117] = 0.0;
   out_3288040166935413696[118] = 0.0;
   out_3288040166935413696[119] = 0.0;
   out_3288040166935413696[120] = 0.0;
   out_3288040166935413696[121] = 0.0;
   out_3288040166935413696[122] = 0.0;
   out_3288040166935413696[123] = 0.0;
   out_3288040166935413696[124] = 0.0;
   out_3288040166935413696[125] = 0.0;
   out_3288040166935413696[126] = 0.0;
   out_3288040166935413696[127] = 0.0;
   out_3288040166935413696[128] = 0.0;
   out_3288040166935413696[129] = 0.0;
   out_3288040166935413696[130] = 0.0;
   out_3288040166935413696[131] = 0.0;
   out_3288040166935413696[132] = 0.0;
   out_3288040166935413696[133] = 1.0;
   out_3288040166935413696[134] = 0.0;
   out_3288040166935413696[135] = 0.0;
   out_3288040166935413696[136] = 0.0;
   out_3288040166935413696[137] = 0.0;
   out_3288040166935413696[138] = 0.0;
   out_3288040166935413696[139] = 0.0;
   out_3288040166935413696[140] = 0.0;
   out_3288040166935413696[141] = 0.0;
   out_3288040166935413696[142] = 0.0;
   out_3288040166935413696[143] = 0.0;
   out_3288040166935413696[144] = 0.0;
   out_3288040166935413696[145] = 0.0;
   out_3288040166935413696[146] = 0.0;
   out_3288040166935413696[147] = 0.0;
   out_3288040166935413696[148] = 0.0;
   out_3288040166935413696[149] = 0.0;
   out_3288040166935413696[150] = 0.0;
   out_3288040166935413696[151] = 0.0;
   out_3288040166935413696[152] = 1.0;
   out_3288040166935413696[153] = 0.0;
   out_3288040166935413696[154] = 0.0;
   out_3288040166935413696[155] = 0.0;
   out_3288040166935413696[156] = 0.0;
   out_3288040166935413696[157] = 0.0;
   out_3288040166935413696[158] = 0.0;
   out_3288040166935413696[159] = 0.0;
   out_3288040166935413696[160] = 0.0;
   out_3288040166935413696[161] = 0.0;
   out_3288040166935413696[162] = 0.0;
   out_3288040166935413696[163] = 0.0;
   out_3288040166935413696[164] = 0.0;
   out_3288040166935413696[165] = 0.0;
   out_3288040166935413696[166] = 0.0;
   out_3288040166935413696[167] = 0.0;
   out_3288040166935413696[168] = 0.0;
   out_3288040166935413696[169] = 0.0;
   out_3288040166935413696[170] = 0.0;
   out_3288040166935413696[171] = 1.0;
   out_3288040166935413696[172] = 0.0;
   out_3288040166935413696[173] = 0.0;
   out_3288040166935413696[174] = 0.0;
   out_3288040166935413696[175] = 0.0;
   out_3288040166935413696[176] = 0.0;
   out_3288040166935413696[177] = 0.0;
   out_3288040166935413696[178] = 0.0;
   out_3288040166935413696[179] = 0.0;
   out_3288040166935413696[180] = 0.0;
   out_3288040166935413696[181] = 0.0;
   out_3288040166935413696[182] = 0.0;
   out_3288040166935413696[183] = 0.0;
   out_3288040166935413696[184] = 0.0;
   out_3288040166935413696[185] = 0.0;
   out_3288040166935413696[186] = 0.0;
   out_3288040166935413696[187] = 0.0;
   out_3288040166935413696[188] = 0.0;
   out_3288040166935413696[189] = 0.0;
   out_3288040166935413696[190] = 1.0;
   out_3288040166935413696[191] = 0.0;
   out_3288040166935413696[192] = 0.0;
   out_3288040166935413696[193] = 0.0;
   out_3288040166935413696[194] = 0.0;
   out_3288040166935413696[195] = 0.0;
   out_3288040166935413696[196] = 0.0;
   out_3288040166935413696[197] = 0.0;
   out_3288040166935413696[198] = 0.0;
   out_3288040166935413696[199] = 0.0;
   out_3288040166935413696[200] = 0.0;
   out_3288040166935413696[201] = 0.0;
   out_3288040166935413696[202] = 0.0;
   out_3288040166935413696[203] = 0.0;
   out_3288040166935413696[204] = 0.0;
   out_3288040166935413696[205] = 0.0;
   out_3288040166935413696[206] = 0.0;
   out_3288040166935413696[207] = 0.0;
   out_3288040166935413696[208] = 0.0;
   out_3288040166935413696[209] = 1.0;
   out_3288040166935413696[210] = 0.0;
   out_3288040166935413696[211] = 0.0;
   out_3288040166935413696[212] = 0.0;
   out_3288040166935413696[213] = 0.0;
   out_3288040166935413696[214] = 0.0;
   out_3288040166935413696[215] = 0.0;
   out_3288040166935413696[216] = 0.0;
   out_3288040166935413696[217] = 0.0;
   out_3288040166935413696[218] = 0.0;
   out_3288040166935413696[219] = 0.0;
   out_3288040166935413696[220] = 0.0;
   out_3288040166935413696[221] = 0.0;
   out_3288040166935413696[222] = 0.0;
   out_3288040166935413696[223] = 0.0;
   out_3288040166935413696[224] = 0.0;
   out_3288040166935413696[225] = 0.0;
   out_3288040166935413696[226] = 0.0;
   out_3288040166935413696[227] = 0.0;
   out_3288040166935413696[228] = 1.0;
   out_3288040166935413696[229] = 0.0;
   out_3288040166935413696[230] = 0.0;
   out_3288040166935413696[231] = 0.0;
   out_3288040166935413696[232] = 0.0;
   out_3288040166935413696[233] = 0.0;
   out_3288040166935413696[234] = 0.0;
   out_3288040166935413696[235] = 0.0;
   out_3288040166935413696[236] = 0.0;
   out_3288040166935413696[237] = 0.0;
   out_3288040166935413696[238] = 0.0;
   out_3288040166935413696[239] = 0.0;
   out_3288040166935413696[240] = 0.0;
   out_3288040166935413696[241] = 0.0;
   out_3288040166935413696[242] = 0.0;
   out_3288040166935413696[243] = 0.0;
   out_3288040166935413696[244] = 0.0;
   out_3288040166935413696[245] = 0.0;
   out_3288040166935413696[246] = 0.0;
   out_3288040166935413696[247] = 1.0;
   out_3288040166935413696[248] = 0.0;
   out_3288040166935413696[249] = 0.0;
   out_3288040166935413696[250] = 0.0;
   out_3288040166935413696[251] = 0.0;
   out_3288040166935413696[252] = 0.0;
   out_3288040166935413696[253] = 0.0;
   out_3288040166935413696[254] = 0.0;
   out_3288040166935413696[255] = 0.0;
   out_3288040166935413696[256] = 0.0;
   out_3288040166935413696[257] = 0.0;
   out_3288040166935413696[258] = 0.0;
   out_3288040166935413696[259] = 0.0;
   out_3288040166935413696[260] = 0.0;
   out_3288040166935413696[261] = 0.0;
   out_3288040166935413696[262] = 0.0;
   out_3288040166935413696[263] = 0.0;
   out_3288040166935413696[264] = 0.0;
   out_3288040166935413696[265] = 0.0;
   out_3288040166935413696[266] = 1.0;
   out_3288040166935413696[267] = 0.0;
   out_3288040166935413696[268] = 0.0;
   out_3288040166935413696[269] = 0.0;
   out_3288040166935413696[270] = 0.0;
   out_3288040166935413696[271] = 0.0;
   out_3288040166935413696[272] = 0.0;
   out_3288040166935413696[273] = 0.0;
   out_3288040166935413696[274] = 0.0;
   out_3288040166935413696[275] = 0.0;
   out_3288040166935413696[276] = 0.0;
   out_3288040166935413696[277] = 0.0;
   out_3288040166935413696[278] = 0.0;
   out_3288040166935413696[279] = 0.0;
   out_3288040166935413696[280] = 0.0;
   out_3288040166935413696[281] = 0.0;
   out_3288040166935413696[282] = 0.0;
   out_3288040166935413696[283] = 0.0;
   out_3288040166935413696[284] = 0.0;
   out_3288040166935413696[285] = 1.0;
   out_3288040166935413696[286] = 0.0;
   out_3288040166935413696[287] = 0.0;
   out_3288040166935413696[288] = 0.0;
   out_3288040166935413696[289] = 0.0;
   out_3288040166935413696[290] = 0.0;
   out_3288040166935413696[291] = 0.0;
   out_3288040166935413696[292] = 0.0;
   out_3288040166935413696[293] = 0.0;
   out_3288040166935413696[294] = 0.0;
   out_3288040166935413696[295] = 0.0;
   out_3288040166935413696[296] = 0.0;
   out_3288040166935413696[297] = 0.0;
   out_3288040166935413696[298] = 0.0;
   out_3288040166935413696[299] = 0.0;
   out_3288040166935413696[300] = 0.0;
   out_3288040166935413696[301] = 0.0;
   out_3288040166935413696[302] = 0.0;
   out_3288040166935413696[303] = 0.0;
   out_3288040166935413696[304] = 1.0;
   out_3288040166935413696[305] = 0.0;
   out_3288040166935413696[306] = 0.0;
   out_3288040166935413696[307] = 0.0;
   out_3288040166935413696[308] = 0.0;
   out_3288040166935413696[309] = 0.0;
   out_3288040166935413696[310] = 0.0;
   out_3288040166935413696[311] = 0.0;
   out_3288040166935413696[312] = 0.0;
   out_3288040166935413696[313] = 0.0;
   out_3288040166935413696[314] = 0.0;
   out_3288040166935413696[315] = 0.0;
   out_3288040166935413696[316] = 0.0;
   out_3288040166935413696[317] = 0.0;
   out_3288040166935413696[318] = 0.0;
   out_3288040166935413696[319] = 0.0;
   out_3288040166935413696[320] = 0.0;
   out_3288040166935413696[321] = 0.0;
   out_3288040166935413696[322] = 0.0;
   out_3288040166935413696[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8548830741413868974) {
   out_8548830741413868974[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8548830741413868974[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8548830741413868974[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8548830741413868974[3] = dt*state[12] + state[3];
   out_8548830741413868974[4] = dt*state[13] + state[4];
   out_8548830741413868974[5] = dt*state[14] + state[5];
   out_8548830741413868974[6] = state[6];
   out_8548830741413868974[7] = state[7];
   out_8548830741413868974[8] = state[8];
   out_8548830741413868974[9] = state[9];
   out_8548830741413868974[10] = state[10];
   out_8548830741413868974[11] = state[11];
   out_8548830741413868974[12] = state[12];
   out_8548830741413868974[13] = state[13];
   out_8548830741413868974[14] = state[14];
   out_8548830741413868974[15] = state[15];
   out_8548830741413868974[16] = state[16];
   out_8548830741413868974[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1843100742578169461) {
   out_1843100742578169461[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1843100742578169461[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1843100742578169461[2] = 0;
   out_1843100742578169461[3] = 0;
   out_1843100742578169461[4] = 0;
   out_1843100742578169461[5] = 0;
   out_1843100742578169461[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1843100742578169461[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1843100742578169461[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1843100742578169461[9] = 0;
   out_1843100742578169461[10] = 0;
   out_1843100742578169461[11] = 0;
   out_1843100742578169461[12] = 0;
   out_1843100742578169461[13] = 0;
   out_1843100742578169461[14] = 0;
   out_1843100742578169461[15] = 0;
   out_1843100742578169461[16] = 0;
   out_1843100742578169461[17] = 0;
   out_1843100742578169461[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1843100742578169461[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1843100742578169461[20] = 0;
   out_1843100742578169461[21] = 0;
   out_1843100742578169461[22] = 0;
   out_1843100742578169461[23] = 0;
   out_1843100742578169461[24] = 0;
   out_1843100742578169461[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1843100742578169461[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1843100742578169461[27] = 0;
   out_1843100742578169461[28] = 0;
   out_1843100742578169461[29] = 0;
   out_1843100742578169461[30] = 0;
   out_1843100742578169461[31] = 0;
   out_1843100742578169461[32] = 0;
   out_1843100742578169461[33] = 0;
   out_1843100742578169461[34] = 0;
   out_1843100742578169461[35] = 0;
   out_1843100742578169461[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1843100742578169461[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1843100742578169461[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1843100742578169461[39] = 0;
   out_1843100742578169461[40] = 0;
   out_1843100742578169461[41] = 0;
   out_1843100742578169461[42] = 0;
   out_1843100742578169461[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1843100742578169461[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1843100742578169461[45] = 0;
   out_1843100742578169461[46] = 0;
   out_1843100742578169461[47] = 0;
   out_1843100742578169461[48] = 0;
   out_1843100742578169461[49] = 0;
   out_1843100742578169461[50] = 0;
   out_1843100742578169461[51] = 0;
   out_1843100742578169461[52] = 0;
   out_1843100742578169461[53] = 0;
   out_1843100742578169461[54] = 0;
   out_1843100742578169461[55] = 0;
   out_1843100742578169461[56] = 0;
   out_1843100742578169461[57] = 1;
   out_1843100742578169461[58] = 0;
   out_1843100742578169461[59] = 0;
   out_1843100742578169461[60] = 0;
   out_1843100742578169461[61] = 0;
   out_1843100742578169461[62] = 0;
   out_1843100742578169461[63] = 0;
   out_1843100742578169461[64] = 0;
   out_1843100742578169461[65] = 0;
   out_1843100742578169461[66] = dt;
   out_1843100742578169461[67] = 0;
   out_1843100742578169461[68] = 0;
   out_1843100742578169461[69] = 0;
   out_1843100742578169461[70] = 0;
   out_1843100742578169461[71] = 0;
   out_1843100742578169461[72] = 0;
   out_1843100742578169461[73] = 0;
   out_1843100742578169461[74] = 0;
   out_1843100742578169461[75] = 0;
   out_1843100742578169461[76] = 1;
   out_1843100742578169461[77] = 0;
   out_1843100742578169461[78] = 0;
   out_1843100742578169461[79] = 0;
   out_1843100742578169461[80] = 0;
   out_1843100742578169461[81] = 0;
   out_1843100742578169461[82] = 0;
   out_1843100742578169461[83] = 0;
   out_1843100742578169461[84] = 0;
   out_1843100742578169461[85] = dt;
   out_1843100742578169461[86] = 0;
   out_1843100742578169461[87] = 0;
   out_1843100742578169461[88] = 0;
   out_1843100742578169461[89] = 0;
   out_1843100742578169461[90] = 0;
   out_1843100742578169461[91] = 0;
   out_1843100742578169461[92] = 0;
   out_1843100742578169461[93] = 0;
   out_1843100742578169461[94] = 0;
   out_1843100742578169461[95] = 1;
   out_1843100742578169461[96] = 0;
   out_1843100742578169461[97] = 0;
   out_1843100742578169461[98] = 0;
   out_1843100742578169461[99] = 0;
   out_1843100742578169461[100] = 0;
   out_1843100742578169461[101] = 0;
   out_1843100742578169461[102] = 0;
   out_1843100742578169461[103] = 0;
   out_1843100742578169461[104] = dt;
   out_1843100742578169461[105] = 0;
   out_1843100742578169461[106] = 0;
   out_1843100742578169461[107] = 0;
   out_1843100742578169461[108] = 0;
   out_1843100742578169461[109] = 0;
   out_1843100742578169461[110] = 0;
   out_1843100742578169461[111] = 0;
   out_1843100742578169461[112] = 0;
   out_1843100742578169461[113] = 0;
   out_1843100742578169461[114] = 1;
   out_1843100742578169461[115] = 0;
   out_1843100742578169461[116] = 0;
   out_1843100742578169461[117] = 0;
   out_1843100742578169461[118] = 0;
   out_1843100742578169461[119] = 0;
   out_1843100742578169461[120] = 0;
   out_1843100742578169461[121] = 0;
   out_1843100742578169461[122] = 0;
   out_1843100742578169461[123] = 0;
   out_1843100742578169461[124] = 0;
   out_1843100742578169461[125] = 0;
   out_1843100742578169461[126] = 0;
   out_1843100742578169461[127] = 0;
   out_1843100742578169461[128] = 0;
   out_1843100742578169461[129] = 0;
   out_1843100742578169461[130] = 0;
   out_1843100742578169461[131] = 0;
   out_1843100742578169461[132] = 0;
   out_1843100742578169461[133] = 1;
   out_1843100742578169461[134] = 0;
   out_1843100742578169461[135] = 0;
   out_1843100742578169461[136] = 0;
   out_1843100742578169461[137] = 0;
   out_1843100742578169461[138] = 0;
   out_1843100742578169461[139] = 0;
   out_1843100742578169461[140] = 0;
   out_1843100742578169461[141] = 0;
   out_1843100742578169461[142] = 0;
   out_1843100742578169461[143] = 0;
   out_1843100742578169461[144] = 0;
   out_1843100742578169461[145] = 0;
   out_1843100742578169461[146] = 0;
   out_1843100742578169461[147] = 0;
   out_1843100742578169461[148] = 0;
   out_1843100742578169461[149] = 0;
   out_1843100742578169461[150] = 0;
   out_1843100742578169461[151] = 0;
   out_1843100742578169461[152] = 1;
   out_1843100742578169461[153] = 0;
   out_1843100742578169461[154] = 0;
   out_1843100742578169461[155] = 0;
   out_1843100742578169461[156] = 0;
   out_1843100742578169461[157] = 0;
   out_1843100742578169461[158] = 0;
   out_1843100742578169461[159] = 0;
   out_1843100742578169461[160] = 0;
   out_1843100742578169461[161] = 0;
   out_1843100742578169461[162] = 0;
   out_1843100742578169461[163] = 0;
   out_1843100742578169461[164] = 0;
   out_1843100742578169461[165] = 0;
   out_1843100742578169461[166] = 0;
   out_1843100742578169461[167] = 0;
   out_1843100742578169461[168] = 0;
   out_1843100742578169461[169] = 0;
   out_1843100742578169461[170] = 0;
   out_1843100742578169461[171] = 1;
   out_1843100742578169461[172] = 0;
   out_1843100742578169461[173] = 0;
   out_1843100742578169461[174] = 0;
   out_1843100742578169461[175] = 0;
   out_1843100742578169461[176] = 0;
   out_1843100742578169461[177] = 0;
   out_1843100742578169461[178] = 0;
   out_1843100742578169461[179] = 0;
   out_1843100742578169461[180] = 0;
   out_1843100742578169461[181] = 0;
   out_1843100742578169461[182] = 0;
   out_1843100742578169461[183] = 0;
   out_1843100742578169461[184] = 0;
   out_1843100742578169461[185] = 0;
   out_1843100742578169461[186] = 0;
   out_1843100742578169461[187] = 0;
   out_1843100742578169461[188] = 0;
   out_1843100742578169461[189] = 0;
   out_1843100742578169461[190] = 1;
   out_1843100742578169461[191] = 0;
   out_1843100742578169461[192] = 0;
   out_1843100742578169461[193] = 0;
   out_1843100742578169461[194] = 0;
   out_1843100742578169461[195] = 0;
   out_1843100742578169461[196] = 0;
   out_1843100742578169461[197] = 0;
   out_1843100742578169461[198] = 0;
   out_1843100742578169461[199] = 0;
   out_1843100742578169461[200] = 0;
   out_1843100742578169461[201] = 0;
   out_1843100742578169461[202] = 0;
   out_1843100742578169461[203] = 0;
   out_1843100742578169461[204] = 0;
   out_1843100742578169461[205] = 0;
   out_1843100742578169461[206] = 0;
   out_1843100742578169461[207] = 0;
   out_1843100742578169461[208] = 0;
   out_1843100742578169461[209] = 1;
   out_1843100742578169461[210] = 0;
   out_1843100742578169461[211] = 0;
   out_1843100742578169461[212] = 0;
   out_1843100742578169461[213] = 0;
   out_1843100742578169461[214] = 0;
   out_1843100742578169461[215] = 0;
   out_1843100742578169461[216] = 0;
   out_1843100742578169461[217] = 0;
   out_1843100742578169461[218] = 0;
   out_1843100742578169461[219] = 0;
   out_1843100742578169461[220] = 0;
   out_1843100742578169461[221] = 0;
   out_1843100742578169461[222] = 0;
   out_1843100742578169461[223] = 0;
   out_1843100742578169461[224] = 0;
   out_1843100742578169461[225] = 0;
   out_1843100742578169461[226] = 0;
   out_1843100742578169461[227] = 0;
   out_1843100742578169461[228] = 1;
   out_1843100742578169461[229] = 0;
   out_1843100742578169461[230] = 0;
   out_1843100742578169461[231] = 0;
   out_1843100742578169461[232] = 0;
   out_1843100742578169461[233] = 0;
   out_1843100742578169461[234] = 0;
   out_1843100742578169461[235] = 0;
   out_1843100742578169461[236] = 0;
   out_1843100742578169461[237] = 0;
   out_1843100742578169461[238] = 0;
   out_1843100742578169461[239] = 0;
   out_1843100742578169461[240] = 0;
   out_1843100742578169461[241] = 0;
   out_1843100742578169461[242] = 0;
   out_1843100742578169461[243] = 0;
   out_1843100742578169461[244] = 0;
   out_1843100742578169461[245] = 0;
   out_1843100742578169461[246] = 0;
   out_1843100742578169461[247] = 1;
   out_1843100742578169461[248] = 0;
   out_1843100742578169461[249] = 0;
   out_1843100742578169461[250] = 0;
   out_1843100742578169461[251] = 0;
   out_1843100742578169461[252] = 0;
   out_1843100742578169461[253] = 0;
   out_1843100742578169461[254] = 0;
   out_1843100742578169461[255] = 0;
   out_1843100742578169461[256] = 0;
   out_1843100742578169461[257] = 0;
   out_1843100742578169461[258] = 0;
   out_1843100742578169461[259] = 0;
   out_1843100742578169461[260] = 0;
   out_1843100742578169461[261] = 0;
   out_1843100742578169461[262] = 0;
   out_1843100742578169461[263] = 0;
   out_1843100742578169461[264] = 0;
   out_1843100742578169461[265] = 0;
   out_1843100742578169461[266] = 1;
   out_1843100742578169461[267] = 0;
   out_1843100742578169461[268] = 0;
   out_1843100742578169461[269] = 0;
   out_1843100742578169461[270] = 0;
   out_1843100742578169461[271] = 0;
   out_1843100742578169461[272] = 0;
   out_1843100742578169461[273] = 0;
   out_1843100742578169461[274] = 0;
   out_1843100742578169461[275] = 0;
   out_1843100742578169461[276] = 0;
   out_1843100742578169461[277] = 0;
   out_1843100742578169461[278] = 0;
   out_1843100742578169461[279] = 0;
   out_1843100742578169461[280] = 0;
   out_1843100742578169461[281] = 0;
   out_1843100742578169461[282] = 0;
   out_1843100742578169461[283] = 0;
   out_1843100742578169461[284] = 0;
   out_1843100742578169461[285] = 1;
   out_1843100742578169461[286] = 0;
   out_1843100742578169461[287] = 0;
   out_1843100742578169461[288] = 0;
   out_1843100742578169461[289] = 0;
   out_1843100742578169461[290] = 0;
   out_1843100742578169461[291] = 0;
   out_1843100742578169461[292] = 0;
   out_1843100742578169461[293] = 0;
   out_1843100742578169461[294] = 0;
   out_1843100742578169461[295] = 0;
   out_1843100742578169461[296] = 0;
   out_1843100742578169461[297] = 0;
   out_1843100742578169461[298] = 0;
   out_1843100742578169461[299] = 0;
   out_1843100742578169461[300] = 0;
   out_1843100742578169461[301] = 0;
   out_1843100742578169461[302] = 0;
   out_1843100742578169461[303] = 0;
   out_1843100742578169461[304] = 1;
   out_1843100742578169461[305] = 0;
   out_1843100742578169461[306] = 0;
   out_1843100742578169461[307] = 0;
   out_1843100742578169461[308] = 0;
   out_1843100742578169461[309] = 0;
   out_1843100742578169461[310] = 0;
   out_1843100742578169461[311] = 0;
   out_1843100742578169461[312] = 0;
   out_1843100742578169461[313] = 0;
   out_1843100742578169461[314] = 0;
   out_1843100742578169461[315] = 0;
   out_1843100742578169461[316] = 0;
   out_1843100742578169461[317] = 0;
   out_1843100742578169461[318] = 0;
   out_1843100742578169461[319] = 0;
   out_1843100742578169461[320] = 0;
   out_1843100742578169461[321] = 0;
   out_1843100742578169461[322] = 0;
   out_1843100742578169461[323] = 1;
}
void h_4(double *state, double *unused, double *out_623102779938789677) {
   out_623102779938789677[0] = state[6] + state[9];
   out_623102779938789677[1] = state[7] + state[10];
   out_623102779938789677[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4912264717037811071) {
   out_4912264717037811071[0] = 0;
   out_4912264717037811071[1] = 0;
   out_4912264717037811071[2] = 0;
   out_4912264717037811071[3] = 0;
   out_4912264717037811071[4] = 0;
   out_4912264717037811071[5] = 0;
   out_4912264717037811071[6] = 1;
   out_4912264717037811071[7] = 0;
   out_4912264717037811071[8] = 0;
   out_4912264717037811071[9] = 1;
   out_4912264717037811071[10] = 0;
   out_4912264717037811071[11] = 0;
   out_4912264717037811071[12] = 0;
   out_4912264717037811071[13] = 0;
   out_4912264717037811071[14] = 0;
   out_4912264717037811071[15] = 0;
   out_4912264717037811071[16] = 0;
   out_4912264717037811071[17] = 0;
   out_4912264717037811071[18] = 0;
   out_4912264717037811071[19] = 0;
   out_4912264717037811071[20] = 0;
   out_4912264717037811071[21] = 0;
   out_4912264717037811071[22] = 0;
   out_4912264717037811071[23] = 0;
   out_4912264717037811071[24] = 0;
   out_4912264717037811071[25] = 1;
   out_4912264717037811071[26] = 0;
   out_4912264717037811071[27] = 0;
   out_4912264717037811071[28] = 1;
   out_4912264717037811071[29] = 0;
   out_4912264717037811071[30] = 0;
   out_4912264717037811071[31] = 0;
   out_4912264717037811071[32] = 0;
   out_4912264717037811071[33] = 0;
   out_4912264717037811071[34] = 0;
   out_4912264717037811071[35] = 0;
   out_4912264717037811071[36] = 0;
   out_4912264717037811071[37] = 0;
   out_4912264717037811071[38] = 0;
   out_4912264717037811071[39] = 0;
   out_4912264717037811071[40] = 0;
   out_4912264717037811071[41] = 0;
   out_4912264717037811071[42] = 0;
   out_4912264717037811071[43] = 0;
   out_4912264717037811071[44] = 1;
   out_4912264717037811071[45] = 0;
   out_4912264717037811071[46] = 0;
   out_4912264717037811071[47] = 1;
   out_4912264717037811071[48] = 0;
   out_4912264717037811071[49] = 0;
   out_4912264717037811071[50] = 0;
   out_4912264717037811071[51] = 0;
   out_4912264717037811071[52] = 0;
   out_4912264717037811071[53] = 0;
}
void h_10(double *state, double *unused, double *out_1249595436022458194) {
   out_1249595436022458194[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1249595436022458194[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1249595436022458194[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2080664605204891446) {
   out_2080664605204891446[0] = 0;
   out_2080664605204891446[1] = 9.8100000000000005*cos(state[1]);
   out_2080664605204891446[2] = 0;
   out_2080664605204891446[3] = 0;
   out_2080664605204891446[4] = -state[8];
   out_2080664605204891446[5] = state[7];
   out_2080664605204891446[6] = 0;
   out_2080664605204891446[7] = state[5];
   out_2080664605204891446[8] = -state[4];
   out_2080664605204891446[9] = 0;
   out_2080664605204891446[10] = 0;
   out_2080664605204891446[11] = 0;
   out_2080664605204891446[12] = 1;
   out_2080664605204891446[13] = 0;
   out_2080664605204891446[14] = 0;
   out_2080664605204891446[15] = 1;
   out_2080664605204891446[16] = 0;
   out_2080664605204891446[17] = 0;
   out_2080664605204891446[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2080664605204891446[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2080664605204891446[20] = 0;
   out_2080664605204891446[21] = state[8];
   out_2080664605204891446[22] = 0;
   out_2080664605204891446[23] = -state[6];
   out_2080664605204891446[24] = -state[5];
   out_2080664605204891446[25] = 0;
   out_2080664605204891446[26] = state[3];
   out_2080664605204891446[27] = 0;
   out_2080664605204891446[28] = 0;
   out_2080664605204891446[29] = 0;
   out_2080664605204891446[30] = 0;
   out_2080664605204891446[31] = 1;
   out_2080664605204891446[32] = 0;
   out_2080664605204891446[33] = 0;
   out_2080664605204891446[34] = 1;
   out_2080664605204891446[35] = 0;
   out_2080664605204891446[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2080664605204891446[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2080664605204891446[38] = 0;
   out_2080664605204891446[39] = -state[7];
   out_2080664605204891446[40] = state[6];
   out_2080664605204891446[41] = 0;
   out_2080664605204891446[42] = state[4];
   out_2080664605204891446[43] = -state[3];
   out_2080664605204891446[44] = 0;
   out_2080664605204891446[45] = 0;
   out_2080664605204891446[46] = 0;
   out_2080664605204891446[47] = 0;
   out_2080664605204891446[48] = 0;
   out_2080664605204891446[49] = 0;
   out_2080664605204891446[50] = 1;
   out_2080664605204891446[51] = 0;
   out_2080664605204891446[52] = 0;
   out_2080664605204891446[53] = 1;
}
void h_13(double *state, double *unused, double *out_67533375617629937) {
   out_67533375617629937[0] = state[3];
   out_67533375617629937[1] = state[4];
   out_67533375617629937[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5923848148355039616) {
   out_5923848148355039616[0] = 0;
   out_5923848148355039616[1] = 0;
   out_5923848148355039616[2] = 0;
   out_5923848148355039616[3] = 1;
   out_5923848148355039616[4] = 0;
   out_5923848148355039616[5] = 0;
   out_5923848148355039616[6] = 0;
   out_5923848148355039616[7] = 0;
   out_5923848148355039616[8] = 0;
   out_5923848148355039616[9] = 0;
   out_5923848148355039616[10] = 0;
   out_5923848148355039616[11] = 0;
   out_5923848148355039616[12] = 0;
   out_5923848148355039616[13] = 0;
   out_5923848148355039616[14] = 0;
   out_5923848148355039616[15] = 0;
   out_5923848148355039616[16] = 0;
   out_5923848148355039616[17] = 0;
   out_5923848148355039616[18] = 0;
   out_5923848148355039616[19] = 0;
   out_5923848148355039616[20] = 0;
   out_5923848148355039616[21] = 0;
   out_5923848148355039616[22] = 1;
   out_5923848148355039616[23] = 0;
   out_5923848148355039616[24] = 0;
   out_5923848148355039616[25] = 0;
   out_5923848148355039616[26] = 0;
   out_5923848148355039616[27] = 0;
   out_5923848148355039616[28] = 0;
   out_5923848148355039616[29] = 0;
   out_5923848148355039616[30] = 0;
   out_5923848148355039616[31] = 0;
   out_5923848148355039616[32] = 0;
   out_5923848148355039616[33] = 0;
   out_5923848148355039616[34] = 0;
   out_5923848148355039616[35] = 0;
   out_5923848148355039616[36] = 0;
   out_5923848148355039616[37] = 0;
   out_5923848148355039616[38] = 0;
   out_5923848148355039616[39] = 0;
   out_5923848148355039616[40] = 0;
   out_5923848148355039616[41] = 1;
   out_5923848148355039616[42] = 0;
   out_5923848148355039616[43] = 0;
   out_5923848148355039616[44] = 0;
   out_5923848148355039616[45] = 0;
   out_5923848148355039616[46] = 0;
   out_5923848148355039616[47] = 0;
   out_5923848148355039616[48] = 0;
   out_5923848148355039616[49] = 0;
   out_5923848148355039616[50] = 0;
   out_5923848148355039616[51] = 0;
   out_5923848148355039616[52] = 0;
   out_5923848148355039616[53] = 0;
}
void h_14(double *state, double *unused, double *out_2407873033235342181) {
   out_2407873033235342181[0] = state[6];
   out_2407873033235342181[1] = state[7];
   out_2407873033235342181[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8875505573377295600) {
   out_8875505573377295600[0] = 0;
   out_8875505573377295600[1] = 0;
   out_8875505573377295600[2] = 0;
   out_8875505573377295600[3] = 0;
   out_8875505573377295600[4] = 0;
   out_8875505573377295600[5] = 0;
   out_8875505573377295600[6] = 1;
   out_8875505573377295600[7] = 0;
   out_8875505573377295600[8] = 0;
   out_8875505573377295600[9] = 0;
   out_8875505573377295600[10] = 0;
   out_8875505573377295600[11] = 0;
   out_8875505573377295600[12] = 0;
   out_8875505573377295600[13] = 0;
   out_8875505573377295600[14] = 0;
   out_8875505573377295600[15] = 0;
   out_8875505573377295600[16] = 0;
   out_8875505573377295600[17] = 0;
   out_8875505573377295600[18] = 0;
   out_8875505573377295600[19] = 0;
   out_8875505573377295600[20] = 0;
   out_8875505573377295600[21] = 0;
   out_8875505573377295600[22] = 0;
   out_8875505573377295600[23] = 0;
   out_8875505573377295600[24] = 0;
   out_8875505573377295600[25] = 1;
   out_8875505573377295600[26] = 0;
   out_8875505573377295600[27] = 0;
   out_8875505573377295600[28] = 0;
   out_8875505573377295600[29] = 0;
   out_8875505573377295600[30] = 0;
   out_8875505573377295600[31] = 0;
   out_8875505573377295600[32] = 0;
   out_8875505573377295600[33] = 0;
   out_8875505573377295600[34] = 0;
   out_8875505573377295600[35] = 0;
   out_8875505573377295600[36] = 0;
   out_8875505573377295600[37] = 0;
   out_8875505573377295600[38] = 0;
   out_8875505573377295600[39] = 0;
   out_8875505573377295600[40] = 0;
   out_8875505573377295600[41] = 0;
   out_8875505573377295600[42] = 0;
   out_8875505573377295600[43] = 0;
   out_8875505573377295600[44] = 1;
   out_8875505573377295600[45] = 0;
   out_8875505573377295600[46] = 0;
   out_8875505573377295600[47] = 0;
   out_8875505573377295600[48] = 0;
   out_8875505573377295600[49] = 0;
   out_8875505573377295600[50] = 0;
   out_8875505573377295600[51] = 0;
   out_8875505573377295600[52] = 0;
   out_8875505573377295600[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8005578165904155046) {
  err_fun(nom_x, delta_x, out_8005578165904155046);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5771596986871161922) {
  inv_err_fun(nom_x, true_x, out_5771596986871161922);
}
void pose_H_mod_fun(double *state, double *out_3288040166935413696) {
  H_mod_fun(state, out_3288040166935413696);
}
void pose_f_fun(double *state, double dt, double *out_8548830741413868974) {
  f_fun(state,  dt, out_8548830741413868974);
}
void pose_F_fun(double *state, double dt, double *out_1843100742578169461) {
  F_fun(state,  dt, out_1843100742578169461);
}
void pose_h_4(double *state, double *unused, double *out_623102779938789677) {
  h_4(state, unused, out_623102779938789677);
}
void pose_H_4(double *state, double *unused, double *out_4912264717037811071) {
  H_4(state, unused, out_4912264717037811071);
}
void pose_h_10(double *state, double *unused, double *out_1249595436022458194) {
  h_10(state, unused, out_1249595436022458194);
}
void pose_H_10(double *state, double *unused, double *out_2080664605204891446) {
  H_10(state, unused, out_2080664605204891446);
}
void pose_h_13(double *state, double *unused, double *out_67533375617629937) {
  h_13(state, unused, out_67533375617629937);
}
void pose_H_13(double *state, double *unused, double *out_5923848148355039616) {
  H_13(state, unused, out_5923848148355039616);
}
void pose_h_14(double *state, double *unused, double *out_2407873033235342181) {
  h_14(state, unused, out_2407873033235342181);
}
void pose_H_14(double *state, double *unused, double *out_8875505573377295600) {
  H_14(state, unused, out_8875505573377295600);
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
