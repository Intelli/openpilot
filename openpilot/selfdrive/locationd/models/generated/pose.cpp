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
void err_fun(double *nom_x, double *delta_x, double *out_4493672777545328076) {
   out_4493672777545328076[0] = delta_x[0] + nom_x[0];
   out_4493672777545328076[1] = delta_x[1] + nom_x[1];
   out_4493672777545328076[2] = delta_x[2] + nom_x[2];
   out_4493672777545328076[3] = delta_x[3] + nom_x[3];
   out_4493672777545328076[4] = delta_x[4] + nom_x[4];
   out_4493672777545328076[5] = delta_x[5] + nom_x[5];
   out_4493672777545328076[6] = delta_x[6] + nom_x[6];
   out_4493672777545328076[7] = delta_x[7] + nom_x[7];
   out_4493672777545328076[8] = delta_x[8] + nom_x[8];
   out_4493672777545328076[9] = delta_x[9] + nom_x[9];
   out_4493672777545328076[10] = delta_x[10] + nom_x[10];
   out_4493672777545328076[11] = delta_x[11] + nom_x[11];
   out_4493672777545328076[12] = delta_x[12] + nom_x[12];
   out_4493672777545328076[13] = delta_x[13] + nom_x[13];
   out_4493672777545328076[14] = delta_x[14] + nom_x[14];
   out_4493672777545328076[15] = delta_x[15] + nom_x[15];
   out_4493672777545328076[16] = delta_x[16] + nom_x[16];
   out_4493672777545328076[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5066533354290862084) {
   out_5066533354290862084[0] = -nom_x[0] + true_x[0];
   out_5066533354290862084[1] = -nom_x[1] + true_x[1];
   out_5066533354290862084[2] = -nom_x[2] + true_x[2];
   out_5066533354290862084[3] = -nom_x[3] + true_x[3];
   out_5066533354290862084[4] = -nom_x[4] + true_x[4];
   out_5066533354290862084[5] = -nom_x[5] + true_x[5];
   out_5066533354290862084[6] = -nom_x[6] + true_x[6];
   out_5066533354290862084[7] = -nom_x[7] + true_x[7];
   out_5066533354290862084[8] = -nom_x[8] + true_x[8];
   out_5066533354290862084[9] = -nom_x[9] + true_x[9];
   out_5066533354290862084[10] = -nom_x[10] + true_x[10];
   out_5066533354290862084[11] = -nom_x[11] + true_x[11];
   out_5066533354290862084[12] = -nom_x[12] + true_x[12];
   out_5066533354290862084[13] = -nom_x[13] + true_x[13];
   out_5066533354290862084[14] = -nom_x[14] + true_x[14];
   out_5066533354290862084[15] = -nom_x[15] + true_x[15];
   out_5066533354290862084[16] = -nom_x[16] + true_x[16];
   out_5066533354290862084[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8162690843869849499) {
   out_8162690843869849499[0] = 1.0;
   out_8162690843869849499[1] = 0.0;
   out_8162690843869849499[2] = 0.0;
   out_8162690843869849499[3] = 0.0;
   out_8162690843869849499[4] = 0.0;
   out_8162690843869849499[5] = 0.0;
   out_8162690843869849499[6] = 0.0;
   out_8162690843869849499[7] = 0.0;
   out_8162690843869849499[8] = 0.0;
   out_8162690843869849499[9] = 0.0;
   out_8162690843869849499[10] = 0.0;
   out_8162690843869849499[11] = 0.0;
   out_8162690843869849499[12] = 0.0;
   out_8162690843869849499[13] = 0.0;
   out_8162690843869849499[14] = 0.0;
   out_8162690843869849499[15] = 0.0;
   out_8162690843869849499[16] = 0.0;
   out_8162690843869849499[17] = 0.0;
   out_8162690843869849499[18] = 0.0;
   out_8162690843869849499[19] = 1.0;
   out_8162690843869849499[20] = 0.0;
   out_8162690843869849499[21] = 0.0;
   out_8162690843869849499[22] = 0.0;
   out_8162690843869849499[23] = 0.0;
   out_8162690843869849499[24] = 0.0;
   out_8162690843869849499[25] = 0.0;
   out_8162690843869849499[26] = 0.0;
   out_8162690843869849499[27] = 0.0;
   out_8162690843869849499[28] = 0.0;
   out_8162690843869849499[29] = 0.0;
   out_8162690843869849499[30] = 0.0;
   out_8162690843869849499[31] = 0.0;
   out_8162690843869849499[32] = 0.0;
   out_8162690843869849499[33] = 0.0;
   out_8162690843869849499[34] = 0.0;
   out_8162690843869849499[35] = 0.0;
   out_8162690843869849499[36] = 0.0;
   out_8162690843869849499[37] = 0.0;
   out_8162690843869849499[38] = 1.0;
   out_8162690843869849499[39] = 0.0;
   out_8162690843869849499[40] = 0.0;
   out_8162690843869849499[41] = 0.0;
   out_8162690843869849499[42] = 0.0;
   out_8162690843869849499[43] = 0.0;
   out_8162690843869849499[44] = 0.0;
   out_8162690843869849499[45] = 0.0;
   out_8162690843869849499[46] = 0.0;
   out_8162690843869849499[47] = 0.0;
   out_8162690843869849499[48] = 0.0;
   out_8162690843869849499[49] = 0.0;
   out_8162690843869849499[50] = 0.0;
   out_8162690843869849499[51] = 0.0;
   out_8162690843869849499[52] = 0.0;
   out_8162690843869849499[53] = 0.0;
   out_8162690843869849499[54] = 0.0;
   out_8162690843869849499[55] = 0.0;
   out_8162690843869849499[56] = 0.0;
   out_8162690843869849499[57] = 1.0;
   out_8162690843869849499[58] = 0.0;
   out_8162690843869849499[59] = 0.0;
   out_8162690843869849499[60] = 0.0;
   out_8162690843869849499[61] = 0.0;
   out_8162690843869849499[62] = 0.0;
   out_8162690843869849499[63] = 0.0;
   out_8162690843869849499[64] = 0.0;
   out_8162690843869849499[65] = 0.0;
   out_8162690843869849499[66] = 0.0;
   out_8162690843869849499[67] = 0.0;
   out_8162690843869849499[68] = 0.0;
   out_8162690843869849499[69] = 0.0;
   out_8162690843869849499[70] = 0.0;
   out_8162690843869849499[71] = 0.0;
   out_8162690843869849499[72] = 0.0;
   out_8162690843869849499[73] = 0.0;
   out_8162690843869849499[74] = 0.0;
   out_8162690843869849499[75] = 0.0;
   out_8162690843869849499[76] = 1.0;
   out_8162690843869849499[77] = 0.0;
   out_8162690843869849499[78] = 0.0;
   out_8162690843869849499[79] = 0.0;
   out_8162690843869849499[80] = 0.0;
   out_8162690843869849499[81] = 0.0;
   out_8162690843869849499[82] = 0.0;
   out_8162690843869849499[83] = 0.0;
   out_8162690843869849499[84] = 0.0;
   out_8162690843869849499[85] = 0.0;
   out_8162690843869849499[86] = 0.0;
   out_8162690843869849499[87] = 0.0;
   out_8162690843869849499[88] = 0.0;
   out_8162690843869849499[89] = 0.0;
   out_8162690843869849499[90] = 0.0;
   out_8162690843869849499[91] = 0.0;
   out_8162690843869849499[92] = 0.0;
   out_8162690843869849499[93] = 0.0;
   out_8162690843869849499[94] = 0.0;
   out_8162690843869849499[95] = 1.0;
   out_8162690843869849499[96] = 0.0;
   out_8162690843869849499[97] = 0.0;
   out_8162690843869849499[98] = 0.0;
   out_8162690843869849499[99] = 0.0;
   out_8162690843869849499[100] = 0.0;
   out_8162690843869849499[101] = 0.0;
   out_8162690843869849499[102] = 0.0;
   out_8162690843869849499[103] = 0.0;
   out_8162690843869849499[104] = 0.0;
   out_8162690843869849499[105] = 0.0;
   out_8162690843869849499[106] = 0.0;
   out_8162690843869849499[107] = 0.0;
   out_8162690843869849499[108] = 0.0;
   out_8162690843869849499[109] = 0.0;
   out_8162690843869849499[110] = 0.0;
   out_8162690843869849499[111] = 0.0;
   out_8162690843869849499[112] = 0.0;
   out_8162690843869849499[113] = 0.0;
   out_8162690843869849499[114] = 1.0;
   out_8162690843869849499[115] = 0.0;
   out_8162690843869849499[116] = 0.0;
   out_8162690843869849499[117] = 0.0;
   out_8162690843869849499[118] = 0.0;
   out_8162690843869849499[119] = 0.0;
   out_8162690843869849499[120] = 0.0;
   out_8162690843869849499[121] = 0.0;
   out_8162690843869849499[122] = 0.0;
   out_8162690843869849499[123] = 0.0;
   out_8162690843869849499[124] = 0.0;
   out_8162690843869849499[125] = 0.0;
   out_8162690843869849499[126] = 0.0;
   out_8162690843869849499[127] = 0.0;
   out_8162690843869849499[128] = 0.0;
   out_8162690843869849499[129] = 0.0;
   out_8162690843869849499[130] = 0.0;
   out_8162690843869849499[131] = 0.0;
   out_8162690843869849499[132] = 0.0;
   out_8162690843869849499[133] = 1.0;
   out_8162690843869849499[134] = 0.0;
   out_8162690843869849499[135] = 0.0;
   out_8162690843869849499[136] = 0.0;
   out_8162690843869849499[137] = 0.0;
   out_8162690843869849499[138] = 0.0;
   out_8162690843869849499[139] = 0.0;
   out_8162690843869849499[140] = 0.0;
   out_8162690843869849499[141] = 0.0;
   out_8162690843869849499[142] = 0.0;
   out_8162690843869849499[143] = 0.0;
   out_8162690843869849499[144] = 0.0;
   out_8162690843869849499[145] = 0.0;
   out_8162690843869849499[146] = 0.0;
   out_8162690843869849499[147] = 0.0;
   out_8162690843869849499[148] = 0.0;
   out_8162690843869849499[149] = 0.0;
   out_8162690843869849499[150] = 0.0;
   out_8162690843869849499[151] = 0.0;
   out_8162690843869849499[152] = 1.0;
   out_8162690843869849499[153] = 0.0;
   out_8162690843869849499[154] = 0.0;
   out_8162690843869849499[155] = 0.0;
   out_8162690843869849499[156] = 0.0;
   out_8162690843869849499[157] = 0.0;
   out_8162690843869849499[158] = 0.0;
   out_8162690843869849499[159] = 0.0;
   out_8162690843869849499[160] = 0.0;
   out_8162690843869849499[161] = 0.0;
   out_8162690843869849499[162] = 0.0;
   out_8162690843869849499[163] = 0.0;
   out_8162690843869849499[164] = 0.0;
   out_8162690843869849499[165] = 0.0;
   out_8162690843869849499[166] = 0.0;
   out_8162690843869849499[167] = 0.0;
   out_8162690843869849499[168] = 0.0;
   out_8162690843869849499[169] = 0.0;
   out_8162690843869849499[170] = 0.0;
   out_8162690843869849499[171] = 1.0;
   out_8162690843869849499[172] = 0.0;
   out_8162690843869849499[173] = 0.0;
   out_8162690843869849499[174] = 0.0;
   out_8162690843869849499[175] = 0.0;
   out_8162690843869849499[176] = 0.0;
   out_8162690843869849499[177] = 0.0;
   out_8162690843869849499[178] = 0.0;
   out_8162690843869849499[179] = 0.0;
   out_8162690843869849499[180] = 0.0;
   out_8162690843869849499[181] = 0.0;
   out_8162690843869849499[182] = 0.0;
   out_8162690843869849499[183] = 0.0;
   out_8162690843869849499[184] = 0.0;
   out_8162690843869849499[185] = 0.0;
   out_8162690843869849499[186] = 0.0;
   out_8162690843869849499[187] = 0.0;
   out_8162690843869849499[188] = 0.0;
   out_8162690843869849499[189] = 0.0;
   out_8162690843869849499[190] = 1.0;
   out_8162690843869849499[191] = 0.0;
   out_8162690843869849499[192] = 0.0;
   out_8162690843869849499[193] = 0.0;
   out_8162690843869849499[194] = 0.0;
   out_8162690843869849499[195] = 0.0;
   out_8162690843869849499[196] = 0.0;
   out_8162690843869849499[197] = 0.0;
   out_8162690843869849499[198] = 0.0;
   out_8162690843869849499[199] = 0.0;
   out_8162690843869849499[200] = 0.0;
   out_8162690843869849499[201] = 0.0;
   out_8162690843869849499[202] = 0.0;
   out_8162690843869849499[203] = 0.0;
   out_8162690843869849499[204] = 0.0;
   out_8162690843869849499[205] = 0.0;
   out_8162690843869849499[206] = 0.0;
   out_8162690843869849499[207] = 0.0;
   out_8162690843869849499[208] = 0.0;
   out_8162690843869849499[209] = 1.0;
   out_8162690843869849499[210] = 0.0;
   out_8162690843869849499[211] = 0.0;
   out_8162690843869849499[212] = 0.0;
   out_8162690843869849499[213] = 0.0;
   out_8162690843869849499[214] = 0.0;
   out_8162690843869849499[215] = 0.0;
   out_8162690843869849499[216] = 0.0;
   out_8162690843869849499[217] = 0.0;
   out_8162690843869849499[218] = 0.0;
   out_8162690843869849499[219] = 0.0;
   out_8162690843869849499[220] = 0.0;
   out_8162690843869849499[221] = 0.0;
   out_8162690843869849499[222] = 0.0;
   out_8162690843869849499[223] = 0.0;
   out_8162690843869849499[224] = 0.0;
   out_8162690843869849499[225] = 0.0;
   out_8162690843869849499[226] = 0.0;
   out_8162690843869849499[227] = 0.0;
   out_8162690843869849499[228] = 1.0;
   out_8162690843869849499[229] = 0.0;
   out_8162690843869849499[230] = 0.0;
   out_8162690843869849499[231] = 0.0;
   out_8162690843869849499[232] = 0.0;
   out_8162690843869849499[233] = 0.0;
   out_8162690843869849499[234] = 0.0;
   out_8162690843869849499[235] = 0.0;
   out_8162690843869849499[236] = 0.0;
   out_8162690843869849499[237] = 0.0;
   out_8162690843869849499[238] = 0.0;
   out_8162690843869849499[239] = 0.0;
   out_8162690843869849499[240] = 0.0;
   out_8162690843869849499[241] = 0.0;
   out_8162690843869849499[242] = 0.0;
   out_8162690843869849499[243] = 0.0;
   out_8162690843869849499[244] = 0.0;
   out_8162690843869849499[245] = 0.0;
   out_8162690843869849499[246] = 0.0;
   out_8162690843869849499[247] = 1.0;
   out_8162690843869849499[248] = 0.0;
   out_8162690843869849499[249] = 0.0;
   out_8162690843869849499[250] = 0.0;
   out_8162690843869849499[251] = 0.0;
   out_8162690843869849499[252] = 0.0;
   out_8162690843869849499[253] = 0.0;
   out_8162690843869849499[254] = 0.0;
   out_8162690843869849499[255] = 0.0;
   out_8162690843869849499[256] = 0.0;
   out_8162690843869849499[257] = 0.0;
   out_8162690843869849499[258] = 0.0;
   out_8162690843869849499[259] = 0.0;
   out_8162690843869849499[260] = 0.0;
   out_8162690843869849499[261] = 0.0;
   out_8162690843869849499[262] = 0.0;
   out_8162690843869849499[263] = 0.0;
   out_8162690843869849499[264] = 0.0;
   out_8162690843869849499[265] = 0.0;
   out_8162690843869849499[266] = 1.0;
   out_8162690843869849499[267] = 0.0;
   out_8162690843869849499[268] = 0.0;
   out_8162690843869849499[269] = 0.0;
   out_8162690843869849499[270] = 0.0;
   out_8162690843869849499[271] = 0.0;
   out_8162690843869849499[272] = 0.0;
   out_8162690843869849499[273] = 0.0;
   out_8162690843869849499[274] = 0.0;
   out_8162690843869849499[275] = 0.0;
   out_8162690843869849499[276] = 0.0;
   out_8162690843869849499[277] = 0.0;
   out_8162690843869849499[278] = 0.0;
   out_8162690843869849499[279] = 0.0;
   out_8162690843869849499[280] = 0.0;
   out_8162690843869849499[281] = 0.0;
   out_8162690843869849499[282] = 0.0;
   out_8162690843869849499[283] = 0.0;
   out_8162690843869849499[284] = 0.0;
   out_8162690843869849499[285] = 1.0;
   out_8162690843869849499[286] = 0.0;
   out_8162690843869849499[287] = 0.0;
   out_8162690843869849499[288] = 0.0;
   out_8162690843869849499[289] = 0.0;
   out_8162690843869849499[290] = 0.0;
   out_8162690843869849499[291] = 0.0;
   out_8162690843869849499[292] = 0.0;
   out_8162690843869849499[293] = 0.0;
   out_8162690843869849499[294] = 0.0;
   out_8162690843869849499[295] = 0.0;
   out_8162690843869849499[296] = 0.0;
   out_8162690843869849499[297] = 0.0;
   out_8162690843869849499[298] = 0.0;
   out_8162690843869849499[299] = 0.0;
   out_8162690843869849499[300] = 0.0;
   out_8162690843869849499[301] = 0.0;
   out_8162690843869849499[302] = 0.0;
   out_8162690843869849499[303] = 0.0;
   out_8162690843869849499[304] = 1.0;
   out_8162690843869849499[305] = 0.0;
   out_8162690843869849499[306] = 0.0;
   out_8162690843869849499[307] = 0.0;
   out_8162690843869849499[308] = 0.0;
   out_8162690843869849499[309] = 0.0;
   out_8162690843869849499[310] = 0.0;
   out_8162690843869849499[311] = 0.0;
   out_8162690843869849499[312] = 0.0;
   out_8162690843869849499[313] = 0.0;
   out_8162690843869849499[314] = 0.0;
   out_8162690843869849499[315] = 0.0;
   out_8162690843869849499[316] = 0.0;
   out_8162690843869849499[317] = 0.0;
   out_8162690843869849499[318] = 0.0;
   out_8162690843869849499[319] = 0.0;
   out_8162690843869849499[320] = 0.0;
   out_8162690843869849499[321] = 0.0;
   out_8162690843869849499[322] = 0.0;
   out_8162690843869849499[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_646878254199369471) {
   out_646878254199369471[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_646878254199369471[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_646878254199369471[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_646878254199369471[3] = dt*state[12] + state[3];
   out_646878254199369471[4] = dt*state[13] + state[4];
   out_646878254199369471[5] = dt*state[14] + state[5];
   out_646878254199369471[6] = state[6];
   out_646878254199369471[7] = state[7];
   out_646878254199369471[8] = state[8];
   out_646878254199369471[9] = state[9];
   out_646878254199369471[10] = state[10];
   out_646878254199369471[11] = state[11];
   out_646878254199369471[12] = state[12];
   out_646878254199369471[13] = state[13];
   out_646878254199369471[14] = state[14];
   out_646878254199369471[15] = state[15];
   out_646878254199369471[16] = state[16];
   out_646878254199369471[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1718881751207348558) {
   out_1718881751207348558[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1718881751207348558[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1718881751207348558[2] = 0;
   out_1718881751207348558[3] = 0;
   out_1718881751207348558[4] = 0;
   out_1718881751207348558[5] = 0;
   out_1718881751207348558[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1718881751207348558[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1718881751207348558[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1718881751207348558[9] = 0;
   out_1718881751207348558[10] = 0;
   out_1718881751207348558[11] = 0;
   out_1718881751207348558[12] = 0;
   out_1718881751207348558[13] = 0;
   out_1718881751207348558[14] = 0;
   out_1718881751207348558[15] = 0;
   out_1718881751207348558[16] = 0;
   out_1718881751207348558[17] = 0;
   out_1718881751207348558[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1718881751207348558[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1718881751207348558[20] = 0;
   out_1718881751207348558[21] = 0;
   out_1718881751207348558[22] = 0;
   out_1718881751207348558[23] = 0;
   out_1718881751207348558[24] = 0;
   out_1718881751207348558[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1718881751207348558[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1718881751207348558[27] = 0;
   out_1718881751207348558[28] = 0;
   out_1718881751207348558[29] = 0;
   out_1718881751207348558[30] = 0;
   out_1718881751207348558[31] = 0;
   out_1718881751207348558[32] = 0;
   out_1718881751207348558[33] = 0;
   out_1718881751207348558[34] = 0;
   out_1718881751207348558[35] = 0;
   out_1718881751207348558[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1718881751207348558[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1718881751207348558[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1718881751207348558[39] = 0;
   out_1718881751207348558[40] = 0;
   out_1718881751207348558[41] = 0;
   out_1718881751207348558[42] = 0;
   out_1718881751207348558[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1718881751207348558[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1718881751207348558[45] = 0;
   out_1718881751207348558[46] = 0;
   out_1718881751207348558[47] = 0;
   out_1718881751207348558[48] = 0;
   out_1718881751207348558[49] = 0;
   out_1718881751207348558[50] = 0;
   out_1718881751207348558[51] = 0;
   out_1718881751207348558[52] = 0;
   out_1718881751207348558[53] = 0;
   out_1718881751207348558[54] = 0;
   out_1718881751207348558[55] = 0;
   out_1718881751207348558[56] = 0;
   out_1718881751207348558[57] = 1;
   out_1718881751207348558[58] = 0;
   out_1718881751207348558[59] = 0;
   out_1718881751207348558[60] = 0;
   out_1718881751207348558[61] = 0;
   out_1718881751207348558[62] = 0;
   out_1718881751207348558[63] = 0;
   out_1718881751207348558[64] = 0;
   out_1718881751207348558[65] = 0;
   out_1718881751207348558[66] = dt;
   out_1718881751207348558[67] = 0;
   out_1718881751207348558[68] = 0;
   out_1718881751207348558[69] = 0;
   out_1718881751207348558[70] = 0;
   out_1718881751207348558[71] = 0;
   out_1718881751207348558[72] = 0;
   out_1718881751207348558[73] = 0;
   out_1718881751207348558[74] = 0;
   out_1718881751207348558[75] = 0;
   out_1718881751207348558[76] = 1;
   out_1718881751207348558[77] = 0;
   out_1718881751207348558[78] = 0;
   out_1718881751207348558[79] = 0;
   out_1718881751207348558[80] = 0;
   out_1718881751207348558[81] = 0;
   out_1718881751207348558[82] = 0;
   out_1718881751207348558[83] = 0;
   out_1718881751207348558[84] = 0;
   out_1718881751207348558[85] = dt;
   out_1718881751207348558[86] = 0;
   out_1718881751207348558[87] = 0;
   out_1718881751207348558[88] = 0;
   out_1718881751207348558[89] = 0;
   out_1718881751207348558[90] = 0;
   out_1718881751207348558[91] = 0;
   out_1718881751207348558[92] = 0;
   out_1718881751207348558[93] = 0;
   out_1718881751207348558[94] = 0;
   out_1718881751207348558[95] = 1;
   out_1718881751207348558[96] = 0;
   out_1718881751207348558[97] = 0;
   out_1718881751207348558[98] = 0;
   out_1718881751207348558[99] = 0;
   out_1718881751207348558[100] = 0;
   out_1718881751207348558[101] = 0;
   out_1718881751207348558[102] = 0;
   out_1718881751207348558[103] = 0;
   out_1718881751207348558[104] = dt;
   out_1718881751207348558[105] = 0;
   out_1718881751207348558[106] = 0;
   out_1718881751207348558[107] = 0;
   out_1718881751207348558[108] = 0;
   out_1718881751207348558[109] = 0;
   out_1718881751207348558[110] = 0;
   out_1718881751207348558[111] = 0;
   out_1718881751207348558[112] = 0;
   out_1718881751207348558[113] = 0;
   out_1718881751207348558[114] = 1;
   out_1718881751207348558[115] = 0;
   out_1718881751207348558[116] = 0;
   out_1718881751207348558[117] = 0;
   out_1718881751207348558[118] = 0;
   out_1718881751207348558[119] = 0;
   out_1718881751207348558[120] = 0;
   out_1718881751207348558[121] = 0;
   out_1718881751207348558[122] = 0;
   out_1718881751207348558[123] = 0;
   out_1718881751207348558[124] = 0;
   out_1718881751207348558[125] = 0;
   out_1718881751207348558[126] = 0;
   out_1718881751207348558[127] = 0;
   out_1718881751207348558[128] = 0;
   out_1718881751207348558[129] = 0;
   out_1718881751207348558[130] = 0;
   out_1718881751207348558[131] = 0;
   out_1718881751207348558[132] = 0;
   out_1718881751207348558[133] = 1;
   out_1718881751207348558[134] = 0;
   out_1718881751207348558[135] = 0;
   out_1718881751207348558[136] = 0;
   out_1718881751207348558[137] = 0;
   out_1718881751207348558[138] = 0;
   out_1718881751207348558[139] = 0;
   out_1718881751207348558[140] = 0;
   out_1718881751207348558[141] = 0;
   out_1718881751207348558[142] = 0;
   out_1718881751207348558[143] = 0;
   out_1718881751207348558[144] = 0;
   out_1718881751207348558[145] = 0;
   out_1718881751207348558[146] = 0;
   out_1718881751207348558[147] = 0;
   out_1718881751207348558[148] = 0;
   out_1718881751207348558[149] = 0;
   out_1718881751207348558[150] = 0;
   out_1718881751207348558[151] = 0;
   out_1718881751207348558[152] = 1;
   out_1718881751207348558[153] = 0;
   out_1718881751207348558[154] = 0;
   out_1718881751207348558[155] = 0;
   out_1718881751207348558[156] = 0;
   out_1718881751207348558[157] = 0;
   out_1718881751207348558[158] = 0;
   out_1718881751207348558[159] = 0;
   out_1718881751207348558[160] = 0;
   out_1718881751207348558[161] = 0;
   out_1718881751207348558[162] = 0;
   out_1718881751207348558[163] = 0;
   out_1718881751207348558[164] = 0;
   out_1718881751207348558[165] = 0;
   out_1718881751207348558[166] = 0;
   out_1718881751207348558[167] = 0;
   out_1718881751207348558[168] = 0;
   out_1718881751207348558[169] = 0;
   out_1718881751207348558[170] = 0;
   out_1718881751207348558[171] = 1;
   out_1718881751207348558[172] = 0;
   out_1718881751207348558[173] = 0;
   out_1718881751207348558[174] = 0;
   out_1718881751207348558[175] = 0;
   out_1718881751207348558[176] = 0;
   out_1718881751207348558[177] = 0;
   out_1718881751207348558[178] = 0;
   out_1718881751207348558[179] = 0;
   out_1718881751207348558[180] = 0;
   out_1718881751207348558[181] = 0;
   out_1718881751207348558[182] = 0;
   out_1718881751207348558[183] = 0;
   out_1718881751207348558[184] = 0;
   out_1718881751207348558[185] = 0;
   out_1718881751207348558[186] = 0;
   out_1718881751207348558[187] = 0;
   out_1718881751207348558[188] = 0;
   out_1718881751207348558[189] = 0;
   out_1718881751207348558[190] = 1;
   out_1718881751207348558[191] = 0;
   out_1718881751207348558[192] = 0;
   out_1718881751207348558[193] = 0;
   out_1718881751207348558[194] = 0;
   out_1718881751207348558[195] = 0;
   out_1718881751207348558[196] = 0;
   out_1718881751207348558[197] = 0;
   out_1718881751207348558[198] = 0;
   out_1718881751207348558[199] = 0;
   out_1718881751207348558[200] = 0;
   out_1718881751207348558[201] = 0;
   out_1718881751207348558[202] = 0;
   out_1718881751207348558[203] = 0;
   out_1718881751207348558[204] = 0;
   out_1718881751207348558[205] = 0;
   out_1718881751207348558[206] = 0;
   out_1718881751207348558[207] = 0;
   out_1718881751207348558[208] = 0;
   out_1718881751207348558[209] = 1;
   out_1718881751207348558[210] = 0;
   out_1718881751207348558[211] = 0;
   out_1718881751207348558[212] = 0;
   out_1718881751207348558[213] = 0;
   out_1718881751207348558[214] = 0;
   out_1718881751207348558[215] = 0;
   out_1718881751207348558[216] = 0;
   out_1718881751207348558[217] = 0;
   out_1718881751207348558[218] = 0;
   out_1718881751207348558[219] = 0;
   out_1718881751207348558[220] = 0;
   out_1718881751207348558[221] = 0;
   out_1718881751207348558[222] = 0;
   out_1718881751207348558[223] = 0;
   out_1718881751207348558[224] = 0;
   out_1718881751207348558[225] = 0;
   out_1718881751207348558[226] = 0;
   out_1718881751207348558[227] = 0;
   out_1718881751207348558[228] = 1;
   out_1718881751207348558[229] = 0;
   out_1718881751207348558[230] = 0;
   out_1718881751207348558[231] = 0;
   out_1718881751207348558[232] = 0;
   out_1718881751207348558[233] = 0;
   out_1718881751207348558[234] = 0;
   out_1718881751207348558[235] = 0;
   out_1718881751207348558[236] = 0;
   out_1718881751207348558[237] = 0;
   out_1718881751207348558[238] = 0;
   out_1718881751207348558[239] = 0;
   out_1718881751207348558[240] = 0;
   out_1718881751207348558[241] = 0;
   out_1718881751207348558[242] = 0;
   out_1718881751207348558[243] = 0;
   out_1718881751207348558[244] = 0;
   out_1718881751207348558[245] = 0;
   out_1718881751207348558[246] = 0;
   out_1718881751207348558[247] = 1;
   out_1718881751207348558[248] = 0;
   out_1718881751207348558[249] = 0;
   out_1718881751207348558[250] = 0;
   out_1718881751207348558[251] = 0;
   out_1718881751207348558[252] = 0;
   out_1718881751207348558[253] = 0;
   out_1718881751207348558[254] = 0;
   out_1718881751207348558[255] = 0;
   out_1718881751207348558[256] = 0;
   out_1718881751207348558[257] = 0;
   out_1718881751207348558[258] = 0;
   out_1718881751207348558[259] = 0;
   out_1718881751207348558[260] = 0;
   out_1718881751207348558[261] = 0;
   out_1718881751207348558[262] = 0;
   out_1718881751207348558[263] = 0;
   out_1718881751207348558[264] = 0;
   out_1718881751207348558[265] = 0;
   out_1718881751207348558[266] = 1;
   out_1718881751207348558[267] = 0;
   out_1718881751207348558[268] = 0;
   out_1718881751207348558[269] = 0;
   out_1718881751207348558[270] = 0;
   out_1718881751207348558[271] = 0;
   out_1718881751207348558[272] = 0;
   out_1718881751207348558[273] = 0;
   out_1718881751207348558[274] = 0;
   out_1718881751207348558[275] = 0;
   out_1718881751207348558[276] = 0;
   out_1718881751207348558[277] = 0;
   out_1718881751207348558[278] = 0;
   out_1718881751207348558[279] = 0;
   out_1718881751207348558[280] = 0;
   out_1718881751207348558[281] = 0;
   out_1718881751207348558[282] = 0;
   out_1718881751207348558[283] = 0;
   out_1718881751207348558[284] = 0;
   out_1718881751207348558[285] = 1;
   out_1718881751207348558[286] = 0;
   out_1718881751207348558[287] = 0;
   out_1718881751207348558[288] = 0;
   out_1718881751207348558[289] = 0;
   out_1718881751207348558[290] = 0;
   out_1718881751207348558[291] = 0;
   out_1718881751207348558[292] = 0;
   out_1718881751207348558[293] = 0;
   out_1718881751207348558[294] = 0;
   out_1718881751207348558[295] = 0;
   out_1718881751207348558[296] = 0;
   out_1718881751207348558[297] = 0;
   out_1718881751207348558[298] = 0;
   out_1718881751207348558[299] = 0;
   out_1718881751207348558[300] = 0;
   out_1718881751207348558[301] = 0;
   out_1718881751207348558[302] = 0;
   out_1718881751207348558[303] = 0;
   out_1718881751207348558[304] = 1;
   out_1718881751207348558[305] = 0;
   out_1718881751207348558[306] = 0;
   out_1718881751207348558[307] = 0;
   out_1718881751207348558[308] = 0;
   out_1718881751207348558[309] = 0;
   out_1718881751207348558[310] = 0;
   out_1718881751207348558[311] = 0;
   out_1718881751207348558[312] = 0;
   out_1718881751207348558[313] = 0;
   out_1718881751207348558[314] = 0;
   out_1718881751207348558[315] = 0;
   out_1718881751207348558[316] = 0;
   out_1718881751207348558[317] = 0;
   out_1718881751207348558[318] = 0;
   out_1718881751207348558[319] = 0;
   out_1718881751207348558[320] = 0;
   out_1718881751207348558[321] = 0;
   out_1718881751207348558[322] = 0;
   out_1718881751207348558[323] = 1;
}
void h_4(double *state, double *unused, double *out_3274903405179125684) {
   out_3274903405179125684[0] = state[6] + state[9];
   out_3274903405179125684[1] = state[7] + state[10];
   out_3274903405179125684[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8916851845924562106) {
   out_8916851845924562106[0] = 0;
   out_8916851845924562106[1] = 0;
   out_8916851845924562106[2] = 0;
   out_8916851845924562106[3] = 0;
   out_8916851845924562106[4] = 0;
   out_8916851845924562106[5] = 0;
   out_8916851845924562106[6] = 1;
   out_8916851845924562106[7] = 0;
   out_8916851845924562106[8] = 0;
   out_8916851845924562106[9] = 1;
   out_8916851845924562106[10] = 0;
   out_8916851845924562106[11] = 0;
   out_8916851845924562106[12] = 0;
   out_8916851845924562106[13] = 0;
   out_8916851845924562106[14] = 0;
   out_8916851845924562106[15] = 0;
   out_8916851845924562106[16] = 0;
   out_8916851845924562106[17] = 0;
   out_8916851845924562106[18] = 0;
   out_8916851845924562106[19] = 0;
   out_8916851845924562106[20] = 0;
   out_8916851845924562106[21] = 0;
   out_8916851845924562106[22] = 0;
   out_8916851845924562106[23] = 0;
   out_8916851845924562106[24] = 0;
   out_8916851845924562106[25] = 1;
   out_8916851845924562106[26] = 0;
   out_8916851845924562106[27] = 0;
   out_8916851845924562106[28] = 1;
   out_8916851845924562106[29] = 0;
   out_8916851845924562106[30] = 0;
   out_8916851845924562106[31] = 0;
   out_8916851845924562106[32] = 0;
   out_8916851845924562106[33] = 0;
   out_8916851845924562106[34] = 0;
   out_8916851845924562106[35] = 0;
   out_8916851845924562106[36] = 0;
   out_8916851845924562106[37] = 0;
   out_8916851845924562106[38] = 0;
   out_8916851845924562106[39] = 0;
   out_8916851845924562106[40] = 0;
   out_8916851845924562106[41] = 0;
   out_8916851845924562106[42] = 0;
   out_8916851845924562106[43] = 0;
   out_8916851845924562106[44] = 1;
   out_8916851845924562106[45] = 0;
   out_8916851845924562106[46] = 0;
   out_8916851845924562106[47] = 1;
   out_8916851845924562106[48] = 0;
   out_8916851845924562106[49] = 0;
   out_8916851845924562106[50] = 0;
   out_8916851845924562106[51] = 0;
   out_8916851845924562106[52] = 0;
   out_8916851845924562106[53] = 0;
}
void h_10(double *state, double *unused, double *out_488427281484310343) {
   out_488427281484310343[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_488427281484310343[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_488427281484310343[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6921454365113393626) {
   out_6921454365113393626[0] = 0;
   out_6921454365113393626[1] = 9.8100000000000005*cos(state[1]);
   out_6921454365113393626[2] = 0;
   out_6921454365113393626[3] = 0;
   out_6921454365113393626[4] = -state[8];
   out_6921454365113393626[5] = state[7];
   out_6921454365113393626[6] = 0;
   out_6921454365113393626[7] = state[5];
   out_6921454365113393626[8] = -state[4];
   out_6921454365113393626[9] = 0;
   out_6921454365113393626[10] = 0;
   out_6921454365113393626[11] = 0;
   out_6921454365113393626[12] = 1;
   out_6921454365113393626[13] = 0;
   out_6921454365113393626[14] = 0;
   out_6921454365113393626[15] = 1;
   out_6921454365113393626[16] = 0;
   out_6921454365113393626[17] = 0;
   out_6921454365113393626[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6921454365113393626[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6921454365113393626[20] = 0;
   out_6921454365113393626[21] = state[8];
   out_6921454365113393626[22] = 0;
   out_6921454365113393626[23] = -state[6];
   out_6921454365113393626[24] = -state[5];
   out_6921454365113393626[25] = 0;
   out_6921454365113393626[26] = state[3];
   out_6921454365113393626[27] = 0;
   out_6921454365113393626[28] = 0;
   out_6921454365113393626[29] = 0;
   out_6921454365113393626[30] = 0;
   out_6921454365113393626[31] = 1;
   out_6921454365113393626[32] = 0;
   out_6921454365113393626[33] = 0;
   out_6921454365113393626[34] = 1;
   out_6921454365113393626[35] = 0;
   out_6921454365113393626[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6921454365113393626[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6921454365113393626[38] = 0;
   out_6921454365113393626[39] = -state[7];
   out_6921454365113393626[40] = state[6];
   out_6921454365113393626[41] = 0;
   out_6921454365113393626[42] = state[4];
   out_6921454365113393626[43] = -state[3];
   out_6921454365113393626[44] = 0;
   out_6921454365113393626[45] = 0;
   out_6921454365113393626[46] = 0;
   out_6921454365113393626[47] = 0;
   out_6921454365113393626[48] = 0;
   out_6921454365113393626[49] = 0;
   out_6921454365113393626[50] = 1;
   out_6921454365113393626[51] = 0;
   out_6921454365113393626[52] = 0;
   out_6921454365113393626[53] = 1;
}
void h_13(double *state, double *unused, double *out_3716360482112169298) {
   out_3716360482112169298[0] = state[3];
   out_3716360482112169298[1] = state[4];
   out_3716360482112169298[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6317618402452656709) {
   out_6317618402452656709[0] = 0;
   out_6317618402452656709[1] = 0;
   out_6317618402452656709[2] = 0;
   out_6317618402452656709[3] = 1;
   out_6317618402452656709[4] = 0;
   out_6317618402452656709[5] = 0;
   out_6317618402452656709[6] = 0;
   out_6317618402452656709[7] = 0;
   out_6317618402452656709[8] = 0;
   out_6317618402452656709[9] = 0;
   out_6317618402452656709[10] = 0;
   out_6317618402452656709[11] = 0;
   out_6317618402452656709[12] = 0;
   out_6317618402452656709[13] = 0;
   out_6317618402452656709[14] = 0;
   out_6317618402452656709[15] = 0;
   out_6317618402452656709[16] = 0;
   out_6317618402452656709[17] = 0;
   out_6317618402452656709[18] = 0;
   out_6317618402452656709[19] = 0;
   out_6317618402452656709[20] = 0;
   out_6317618402452656709[21] = 0;
   out_6317618402452656709[22] = 1;
   out_6317618402452656709[23] = 0;
   out_6317618402452656709[24] = 0;
   out_6317618402452656709[25] = 0;
   out_6317618402452656709[26] = 0;
   out_6317618402452656709[27] = 0;
   out_6317618402452656709[28] = 0;
   out_6317618402452656709[29] = 0;
   out_6317618402452656709[30] = 0;
   out_6317618402452656709[31] = 0;
   out_6317618402452656709[32] = 0;
   out_6317618402452656709[33] = 0;
   out_6317618402452656709[34] = 0;
   out_6317618402452656709[35] = 0;
   out_6317618402452656709[36] = 0;
   out_6317618402452656709[37] = 0;
   out_6317618402452656709[38] = 0;
   out_6317618402452656709[39] = 0;
   out_6317618402452656709[40] = 0;
   out_6317618402452656709[41] = 1;
   out_6317618402452656709[42] = 0;
   out_6317618402452656709[43] = 0;
   out_6317618402452656709[44] = 0;
   out_6317618402452656709[45] = 0;
   out_6317618402452656709[46] = 0;
   out_6317618402452656709[47] = 0;
   out_6317618402452656709[48] = 0;
   out_6317618402452656709[49] = 0;
   out_6317618402452656709[50] = 0;
   out_6317618402452656709[51] = 0;
   out_6317618402452656709[52] = 0;
   out_6317618402452656709[53] = 0;
}
void h_14(double *state, double *unused, double *out_9126146822157534085) {
   out_9126146822157534085[0] = state[6];
   out_9126146822157534085[1] = state[7];
   out_9126146822157534085[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5566651371445504981) {
   out_5566651371445504981[0] = 0;
   out_5566651371445504981[1] = 0;
   out_5566651371445504981[2] = 0;
   out_5566651371445504981[3] = 0;
   out_5566651371445504981[4] = 0;
   out_5566651371445504981[5] = 0;
   out_5566651371445504981[6] = 1;
   out_5566651371445504981[7] = 0;
   out_5566651371445504981[8] = 0;
   out_5566651371445504981[9] = 0;
   out_5566651371445504981[10] = 0;
   out_5566651371445504981[11] = 0;
   out_5566651371445504981[12] = 0;
   out_5566651371445504981[13] = 0;
   out_5566651371445504981[14] = 0;
   out_5566651371445504981[15] = 0;
   out_5566651371445504981[16] = 0;
   out_5566651371445504981[17] = 0;
   out_5566651371445504981[18] = 0;
   out_5566651371445504981[19] = 0;
   out_5566651371445504981[20] = 0;
   out_5566651371445504981[21] = 0;
   out_5566651371445504981[22] = 0;
   out_5566651371445504981[23] = 0;
   out_5566651371445504981[24] = 0;
   out_5566651371445504981[25] = 1;
   out_5566651371445504981[26] = 0;
   out_5566651371445504981[27] = 0;
   out_5566651371445504981[28] = 0;
   out_5566651371445504981[29] = 0;
   out_5566651371445504981[30] = 0;
   out_5566651371445504981[31] = 0;
   out_5566651371445504981[32] = 0;
   out_5566651371445504981[33] = 0;
   out_5566651371445504981[34] = 0;
   out_5566651371445504981[35] = 0;
   out_5566651371445504981[36] = 0;
   out_5566651371445504981[37] = 0;
   out_5566651371445504981[38] = 0;
   out_5566651371445504981[39] = 0;
   out_5566651371445504981[40] = 0;
   out_5566651371445504981[41] = 0;
   out_5566651371445504981[42] = 0;
   out_5566651371445504981[43] = 0;
   out_5566651371445504981[44] = 1;
   out_5566651371445504981[45] = 0;
   out_5566651371445504981[46] = 0;
   out_5566651371445504981[47] = 0;
   out_5566651371445504981[48] = 0;
   out_5566651371445504981[49] = 0;
   out_5566651371445504981[50] = 0;
   out_5566651371445504981[51] = 0;
   out_5566651371445504981[52] = 0;
   out_5566651371445504981[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4493672777545328076) {
  err_fun(nom_x, delta_x, out_4493672777545328076);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5066533354290862084) {
  inv_err_fun(nom_x, true_x, out_5066533354290862084);
}
void pose_H_mod_fun(double *state, double *out_8162690843869849499) {
  H_mod_fun(state, out_8162690843869849499);
}
void pose_f_fun(double *state, double dt, double *out_646878254199369471) {
  f_fun(state,  dt, out_646878254199369471);
}
void pose_F_fun(double *state, double dt, double *out_1718881751207348558) {
  F_fun(state,  dt, out_1718881751207348558);
}
void pose_h_4(double *state, double *unused, double *out_3274903405179125684) {
  h_4(state, unused, out_3274903405179125684);
}
void pose_H_4(double *state, double *unused, double *out_8916851845924562106) {
  H_4(state, unused, out_8916851845924562106);
}
void pose_h_10(double *state, double *unused, double *out_488427281484310343) {
  h_10(state, unused, out_488427281484310343);
}
void pose_H_10(double *state, double *unused, double *out_6921454365113393626) {
  H_10(state, unused, out_6921454365113393626);
}
void pose_h_13(double *state, double *unused, double *out_3716360482112169298) {
  h_13(state, unused, out_3716360482112169298);
}
void pose_H_13(double *state, double *unused, double *out_6317618402452656709) {
  H_13(state, unused, out_6317618402452656709);
}
void pose_h_14(double *state, double *unused, double *out_9126146822157534085) {
  h_14(state, unused, out_9126146822157534085);
}
void pose_H_14(double *state, double *unused, double *out_5566651371445504981) {
  H_14(state, unused, out_5566651371445504981);
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
