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
void err_fun(double *nom_x, double *delta_x, double *out_5991537263051443263) {
   out_5991537263051443263[0] = delta_x[0] + nom_x[0];
   out_5991537263051443263[1] = delta_x[1] + nom_x[1];
   out_5991537263051443263[2] = delta_x[2] + nom_x[2];
   out_5991537263051443263[3] = delta_x[3] + nom_x[3];
   out_5991537263051443263[4] = delta_x[4] + nom_x[4];
   out_5991537263051443263[5] = delta_x[5] + nom_x[5];
   out_5991537263051443263[6] = delta_x[6] + nom_x[6];
   out_5991537263051443263[7] = delta_x[7] + nom_x[7];
   out_5991537263051443263[8] = delta_x[8] + nom_x[8];
   out_5991537263051443263[9] = delta_x[9] + nom_x[9];
   out_5991537263051443263[10] = delta_x[10] + nom_x[10];
   out_5991537263051443263[11] = delta_x[11] + nom_x[11];
   out_5991537263051443263[12] = delta_x[12] + nom_x[12];
   out_5991537263051443263[13] = delta_x[13] + nom_x[13];
   out_5991537263051443263[14] = delta_x[14] + nom_x[14];
   out_5991537263051443263[15] = delta_x[15] + nom_x[15];
   out_5991537263051443263[16] = delta_x[16] + nom_x[16];
   out_5991537263051443263[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2628315792951768716) {
   out_2628315792951768716[0] = -nom_x[0] + true_x[0];
   out_2628315792951768716[1] = -nom_x[1] + true_x[1];
   out_2628315792951768716[2] = -nom_x[2] + true_x[2];
   out_2628315792951768716[3] = -nom_x[3] + true_x[3];
   out_2628315792951768716[4] = -nom_x[4] + true_x[4];
   out_2628315792951768716[5] = -nom_x[5] + true_x[5];
   out_2628315792951768716[6] = -nom_x[6] + true_x[6];
   out_2628315792951768716[7] = -nom_x[7] + true_x[7];
   out_2628315792951768716[8] = -nom_x[8] + true_x[8];
   out_2628315792951768716[9] = -nom_x[9] + true_x[9];
   out_2628315792951768716[10] = -nom_x[10] + true_x[10];
   out_2628315792951768716[11] = -nom_x[11] + true_x[11];
   out_2628315792951768716[12] = -nom_x[12] + true_x[12];
   out_2628315792951768716[13] = -nom_x[13] + true_x[13];
   out_2628315792951768716[14] = -nom_x[14] + true_x[14];
   out_2628315792951768716[15] = -nom_x[15] + true_x[15];
   out_2628315792951768716[16] = -nom_x[16] + true_x[16];
   out_2628315792951768716[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4425582544225868447) {
   out_4425582544225868447[0] = 1.0;
   out_4425582544225868447[1] = 0.0;
   out_4425582544225868447[2] = 0.0;
   out_4425582544225868447[3] = 0.0;
   out_4425582544225868447[4] = 0.0;
   out_4425582544225868447[5] = 0.0;
   out_4425582544225868447[6] = 0.0;
   out_4425582544225868447[7] = 0.0;
   out_4425582544225868447[8] = 0.0;
   out_4425582544225868447[9] = 0.0;
   out_4425582544225868447[10] = 0.0;
   out_4425582544225868447[11] = 0.0;
   out_4425582544225868447[12] = 0.0;
   out_4425582544225868447[13] = 0.0;
   out_4425582544225868447[14] = 0.0;
   out_4425582544225868447[15] = 0.0;
   out_4425582544225868447[16] = 0.0;
   out_4425582544225868447[17] = 0.0;
   out_4425582544225868447[18] = 0.0;
   out_4425582544225868447[19] = 1.0;
   out_4425582544225868447[20] = 0.0;
   out_4425582544225868447[21] = 0.0;
   out_4425582544225868447[22] = 0.0;
   out_4425582544225868447[23] = 0.0;
   out_4425582544225868447[24] = 0.0;
   out_4425582544225868447[25] = 0.0;
   out_4425582544225868447[26] = 0.0;
   out_4425582544225868447[27] = 0.0;
   out_4425582544225868447[28] = 0.0;
   out_4425582544225868447[29] = 0.0;
   out_4425582544225868447[30] = 0.0;
   out_4425582544225868447[31] = 0.0;
   out_4425582544225868447[32] = 0.0;
   out_4425582544225868447[33] = 0.0;
   out_4425582544225868447[34] = 0.0;
   out_4425582544225868447[35] = 0.0;
   out_4425582544225868447[36] = 0.0;
   out_4425582544225868447[37] = 0.0;
   out_4425582544225868447[38] = 1.0;
   out_4425582544225868447[39] = 0.0;
   out_4425582544225868447[40] = 0.0;
   out_4425582544225868447[41] = 0.0;
   out_4425582544225868447[42] = 0.0;
   out_4425582544225868447[43] = 0.0;
   out_4425582544225868447[44] = 0.0;
   out_4425582544225868447[45] = 0.0;
   out_4425582544225868447[46] = 0.0;
   out_4425582544225868447[47] = 0.0;
   out_4425582544225868447[48] = 0.0;
   out_4425582544225868447[49] = 0.0;
   out_4425582544225868447[50] = 0.0;
   out_4425582544225868447[51] = 0.0;
   out_4425582544225868447[52] = 0.0;
   out_4425582544225868447[53] = 0.0;
   out_4425582544225868447[54] = 0.0;
   out_4425582544225868447[55] = 0.0;
   out_4425582544225868447[56] = 0.0;
   out_4425582544225868447[57] = 1.0;
   out_4425582544225868447[58] = 0.0;
   out_4425582544225868447[59] = 0.0;
   out_4425582544225868447[60] = 0.0;
   out_4425582544225868447[61] = 0.0;
   out_4425582544225868447[62] = 0.0;
   out_4425582544225868447[63] = 0.0;
   out_4425582544225868447[64] = 0.0;
   out_4425582544225868447[65] = 0.0;
   out_4425582544225868447[66] = 0.0;
   out_4425582544225868447[67] = 0.0;
   out_4425582544225868447[68] = 0.0;
   out_4425582544225868447[69] = 0.0;
   out_4425582544225868447[70] = 0.0;
   out_4425582544225868447[71] = 0.0;
   out_4425582544225868447[72] = 0.0;
   out_4425582544225868447[73] = 0.0;
   out_4425582544225868447[74] = 0.0;
   out_4425582544225868447[75] = 0.0;
   out_4425582544225868447[76] = 1.0;
   out_4425582544225868447[77] = 0.0;
   out_4425582544225868447[78] = 0.0;
   out_4425582544225868447[79] = 0.0;
   out_4425582544225868447[80] = 0.0;
   out_4425582544225868447[81] = 0.0;
   out_4425582544225868447[82] = 0.0;
   out_4425582544225868447[83] = 0.0;
   out_4425582544225868447[84] = 0.0;
   out_4425582544225868447[85] = 0.0;
   out_4425582544225868447[86] = 0.0;
   out_4425582544225868447[87] = 0.0;
   out_4425582544225868447[88] = 0.0;
   out_4425582544225868447[89] = 0.0;
   out_4425582544225868447[90] = 0.0;
   out_4425582544225868447[91] = 0.0;
   out_4425582544225868447[92] = 0.0;
   out_4425582544225868447[93] = 0.0;
   out_4425582544225868447[94] = 0.0;
   out_4425582544225868447[95] = 1.0;
   out_4425582544225868447[96] = 0.0;
   out_4425582544225868447[97] = 0.0;
   out_4425582544225868447[98] = 0.0;
   out_4425582544225868447[99] = 0.0;
   out_4425582544225868447[100] = 0.0;
   out_4425582544225868447[101] = 0.0;
   out_4425582544225868447[102] = 0.0;
   out_4425582544225868447[103] = 0.0;
   out_4425582544225868447[104] = 0.0;
   out_4425582544225868447[105] = 0.0;
   out_4425582544225868447[106] = 0.0;
   out_4425582544225868447[107] = 0.0;
   out_4425582544225868447[108] = 0.0;
   out_4425582544225868447[109] = 0.0;
   out_4425582544225868447[110] = 0.0;
   out_4425582544225868447[111] = 0.0;
   out_4425582544225868447[112] = 0.0;
   out_4425582544225868447[113] = 0.0;
   out_4425582544225868447[114] = 1.0;
   out_4425582544225868447[115] = 0.0;
   out_4425582544225868447[116] = 0.0;
   out_4425582544225868447[117] = 0.0;
   out_4425582544225868447[118] = 0.0;
   out_4425582544225868447[119] = 0.0;
   out_4425582544225868447[120] = 0.0;
   out_4425582544225868447[121] = 0.0;
   out_4425582544225868447[122] = 0.0;
   out_4425582544225868447[123] = 0.0;
   out_4425582544225868447[124] = 0.0;
   out_4425582544225868447[125] = 0.0;
   out_4425582544225868447[126] = 0.0;
   out_4425582544225868447[127] = 0.0;
   out_4425582544225868447[128] = 0.0;
   out_4425582544225868447[129] = 0.0;
   out_4425582544225868447[130] = 0.0;
   out_4425582544225868447[131] = 0.0;
   out_4425582544225868447[132] = 0.0;
   out_4425582544225868447[133] = 1.0;
   out_4425582544225868447[134] = 0.0;
   out_4425582544225868447[135] = 0.0;
   out_4425582544225868447[136] = 0.0;
   out_4425582544225868447[137] = 0.0;
   out_4425582544225868447[138] = 0.0;
   out_4425582544225868447[139] = 0.0;
   out_4425582544225868447[140] = 0.0;
   out_4425582544225868447[141] = 0.0;
   out_4425582544225868447[142] = 0.0;
   out_4425582544225868447[143] = 0.0;
   out_4425582544225868447[144] = 0.0;
   out_4425582544225868447[145] = 0.0;
   out_4425582544225868447[146] = 0.0;
   out_4425582544225868447[147] = 0.0;
   out_4425582544225868447[148] = 0.0;
   out_4425582544225868447[149] = 0.0;
   out_4425582544225868447[150] = 0.0;
   out_4425582544225868447[151] = 0.0;
   out_4425582544225868447[152] = 1.0;
   out_4425582544225868447[153] = 0.0;
   out_4425582544225868447[154] = 0.0;
   out_4425582544225868447[155] = 0.0;
   out_4425582544225868447[156] = 0.0;
   out_4425582544225868447[157] = 0.0;
   out_4425582544225868447[158] = 0.0;
   out_4425582544225868447[159] = 0.0;
   out_4425582544225868447[160] = 0.0;
   out_4425582544225868447[161] = 0.0;
   out_4425582544225868447[162] = 0.0;
   out_4425582544225868447[163] = 0.0;
   out_4425582544225868447[164] = 0.0;
   out_4425582544225868447[165] = 0.0;
   out_4425582544225868447[166] = 0.0;
   out_4425582544225868447[167] = 0.0;
   out_4425582544225868447[168] = 0.0;
   out_4425582544225868447[169] = 0.0;
   out_4425582544225868447[170] = 0.0;
   out_4425582544225868447[171] = 1.0;
   out_4425582544225868447[172] = 0.0;
   out_4425582544225868447[173] = 0.0;
   out_4425582544225868447[174] = 0.0;
   out_4425582544225868447[175] = 0.0;
   out_4425582544225868447[176] = 0.0;
   out_4425582544225868447[177] = 0.0;
   out_4425582544225868447[178] = 0.0;
   out_4425582544225868447[179] = 0.0;
   out_4425582544225868447[180] = 0.0;
   out_4425582544225868447[181] = 0.0;
   out_4425582544225868447[182] = 0.0;
   out_4425582544225868447[183] = 0.0;
   out_4425582544225868447[184] = 0.0;
   out_4425582544225868447[185] = 0.0;
   out_4425582544225868447[186] = 0.0;
   out_4425582544225868447[187] = 0.0;
   out_4425582544225868447[188] = 0.0;
   out_4425582544225868447[189] = 0.0;
   out_4425582544225868447[190] = 1.0;
   out_4425582544225868447[191] = 0.0;
   out_4425582544225868447[192] = 0.0;
   out_4425582544225868447[193] = 0.0;
   out_4425582544225868447[194] = 0.0;
   out_4425582544225868447[195] = 0.0;
   out_4425582544225868447[196] = 0.0;
   out_4425582544225868447[197] = 0.0;
   out_4425582544225868447[198] = 0.0;
   out_4425582544225868447[199] = 0.0;
   out_4425582544225868447[200] = 0.0;
   out_4425582544225868447[201] = 0.0;
   out_4425582544225868447[202] = 0.0;
   out_4425582544225868447[203] = 0.0;
   out_4425582544225868447[204] = 0.0;
   out_4425582544225868447[205] = 0.0;
   out_4425582544225868447[206] = 0.0;
   out_4425582544225868447[207] = 0.0;
   out_4425582544225868447[208] = 0.0;
   out_4425582544225868447[209] = 1.0;
   out_4425582544225868447[210] = 0.0;
   out_4425582544225868447[211] = 0.0;
   out_4425582544225868447[212] = 0.0;
   out_4425582544225868447[213] = 0.0;
   out_4425582544225868447[214] = 0.0;
   out_4425582544225868447[215] = 0.0;
   out_4425582544225868447[216] = 0.0;
   out_4425582544225868447[217] = 0.0;
   out_4425582544225868447[218] = 0.0;
   out_4425582544225868447[219] = 0.0;
   out_4425582544225868447[220] = 0.0;
   out_4425582544225868447[221] = 0.0;
   out_4425582544225868447[222] = 0.0;
   out_4425582544225868447[223] = 0.0;
   out_4425582544225868447[224] = 0.0;
   out_4425582544225868447[225] = 0.0;
   out_4425582544225868447[226] = 0.0;
   out_4425582544225868447[227] = 0.0;
   out_4425582544225868447[228] = 1.0;
   out_4425582544225868447[229] = 0.0;
   out_4425582544225868447[230] = 0.0;
   out_4425582544225868447[231] = 0.0;
   out_4425582544225868447[232] = 0.0;
   out_4425582544225868447[233] = 0.0;
   out_4425582544225868447[234] = 0.0;
   out_4425582544225868447[235] = 0.0;
   out_4425582544225868447[236] = 0.0;
   out_4425582544225868447[237] = 0.0;
   out_4425582544225868447[238] = 0.0;
   out_4425582544225868447[239] = 0.0;
   out_4425582544225868447[240] = 0.0;
   out_4425582544225868447[241] = 0.0;
   out_4425582544225868447[242] = 0.0;
   out_4425582544225868447[243] = 0.0;
   out_4425582544225868447[244] = 0.0;
   out_4425582544225868447[245] = 0.0;
   out_4425582544225868447[246] = 0.0;
   out_4425582544225868447[247] = 1.0;
   out_4425582544225868447[248] = 0.0;
   out_4425582544225868447[249] = 0.0;
   out_4425582544225868447[250] = 0.0;
   out_4425582544225868447[251] = 0.0;
   out_4425582544225868447[252] = 0.0;
   out_4425582544225868447[253] = 0.0;
   out_4425582544225868447[254] = 0.0;
   out_4425582544225868447[255] = 0.0;
   out_4425582544225868447[256] = 0.0;
   out_4425582544225868447[257] = 0.0;
   out_4425582544225868447[258] = 0.0;
   out_4425582544225868447[259] = 0.0;
   out_4425582544225868447[260] = 0.0;
   out_4425582544225868447[261] = 0.0;
   out_4425582544225868447[262] = 0.0;
   out_4425582544225868447[263] = 0.0;
   out_4425582544225868447[264] = 0.0;
   out_4425582544225868447[265] = 0.0;
   out_4425582544225868447[266] = 1.0;
   out_4425582544225868447[267] = 0.0;
   out_4425582544225868447[268] = 0.0;
   out_4425582544225868447[269] = 0.0;
   out_4425582544225868447[270] = 0.0;
   out_4425582544225868447[271] = 0.0;
   out_4425582544225868447[272] = 0.0;
   out_4425582544225868447[273] = 0.0;
   out_4425582544225868447[274] = 0.0;
   out_4425582544225868447[275] = 0.0;
   out_4425582544225868447[276] = 0.0;
   out_4425582544225868447[277] = 0.0;
   out_4425582544225868447[278] = 0.0;
   out_4425582544225868447[279] = 0.0;
   out_4425582544225868447[280] = 0.0;
   out_4425582544225868447[281] = 0.0;
   out_4425582544225868447[282] = 0.0;
   out_4425582544225868447[283] = 0.0;
   out_4425582544225868447[284] = 0.0;
   out_4425582544225868447[285] = 1.0;
   out_4425582544225868447[286] = 0.0;
   out_4425582544225868447[287] = 0.0;
   out_4425582544225868447[288] = 0.0;
   out_4425582544225868447[289] = 0.0;
   out_4425582544225868447[290] = 0.0;
   out_4425582544225868447[291] = 0.0;
   out_4425582544225868447[292] = 0.0;
   out_4425582544225868447[293] = 0.0;
   out_4425582544225868447[294] = 0.0;
   out_4425582544225868447[295] = 0.0;
   out_4425582544225868447[296] = 0.0;
   out_4425582544225868447[297] = 0.0;
   out_4425582544225868447[298] = 0.0;
   out_4425582544225868447[299] = 0.0;
   out_4425582544225868447[300] = 0.0;
   out_4425582544225868447[301] = 0.0;
   out_4425582544225868447[302] = 0.0;
   out_4425582544225868447[303] = 0.0;
   out_4425582544225868447[304] = 1.0;
   out_4425582544225868447[305] = 0.0;
   out_4425582544225868447[306] = 0.0;
   out_4425582544225868447[307] = 0.0;
   out_4425582544225868447[308] = 0.0;
   out_4425582544225868447[309] = 0.0;
   out_4425582544225868447[310] = 0.0;
   out_4425582544225868447[311] = 0.0;
   out_4425582544225868447[312] = 0.0;
   out_4425582544225868447[313] = 0.0;
   out_4425582544225868447[314] = 0.0;
   out_4425582544225868447[315] = 0.0;
   out_4425582544225868447[316] = 0.0;
   out_4425582544225868447[317] = 0.0;
   out_4425582544225868447[318] = 0.0;
   out_4425582544225868447[319] = 0.0;
   out_4425582544225868447[320] = 0.0;
   out_4425582544225868447[321] = 0.0;
   out_4425582544225868447[322] = 0.0;
   out_4425582544225868447[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_61910386899534067) {
   out_61910386899534067[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_61910386899534067[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_61910386899534067[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_61910386899534067[3] = dt*state[12] + state[3];
   out_61910386899534067[4] = dt*state[13] + state[4];
   out_61910386899534067[5] = dt*state[14] + state[5];
   out_61910386899534067[6] = state[6];
   out_61910386899534067[7] = state[7];
   out_61910386899534067[8] = state[8];
   out_61910386899534067[9] = state[9];
   out_61910386899534067[10] = state[10];
   out_61910386899534067[11] = state[11];
   out_61910386899534067[12] = state[12];
   out_61910386899534067[13] = state[13];
   out_61910386899534067[14] = state[14];
   out_61910386899534067[15] = state[15];
   out_61910386899534067[16] = state[16];
   out_61910386899534067[17] = state[17];
}
void F_fun(double *state, double dt, double *out_915104698457213198) {
   out_915104698457213198[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_915104698457213198[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_915104698457213198[2] = 0;
   out_915104698457213198[3] = 0;
   out_915104698457213198[4] = 0;
   out_915104698457213198[5] = 0;
   out_915104698457213198[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_915104698457213198[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_915104698457213198[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_915104698457213198[9] = 0;
   out_915104698457213198[10] = 0;
   out_915104698457213198[11] = 0;
   out_915104698457213198[12] = 0;
   out_915104698457213198[13] = 0;
   out_915104698457213198[14] = 0;
   out_915104698457213198[15] = 0;
   out_915104698457213198[16] = 0;
   out_915104698457213198[17] = 0;
   out_915104698457213198[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_915104698457213198[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_915104698457213198[20] = 0;
   out_915104698457213198[21] = 0;
   out_915104698457213198[22] = 0;
   out_915104698457213198[23] = 0;
   out_915104698457213198[24] = 0;
   out_915104698457213198[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_915104698457213198[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_915104698457213198[27] = 0;
   out_915104698457213198[28] = 0;
   out_915104698457213198[29] = 0;
   out_915104698457213198[30] = 0;
   out_915104698457213198[31] = 0;
   out_915104698457213198[32] = 0;
   out_915104698457213198[33] = 0;
   out_915104698457213198[34] = 0;
   out_915104698457213198[35] = 0;
   out_915104698457213198[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_915104698457213198[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_915104698457213198[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_915104698457213198[39] = 0;
   out_915104698457213198[40] = 0;
   out_915104698457213198[41] = 0;
   out_915104698457213198[42] = 0;
   out_915104698457213198[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_915104698457213198[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_915104698457213198[45] = 0;
   out_915104698457213198[46] = 0;
   out_915104698457213198[47] = 0;
   out_915104698457213198[48] = 0;
   out_915104698457213198[49] = 0;
   out_915104698457213198[50] = 0;
   out_915104698457213198[51] = 0;
   out_915104698457213198[52] = 0;
   out_915104698457213198[53] = 0;
   out_915104698457213198[54] = 0;
   out_915104698457213198[55] = 0;
   out_915104698457213198[56] = 0;
   out_915104698457213198[57] = 1;
   out_915104698457213198[58] = 0;
   out_915104698457213198[59] = 0;
   out_915104698457213198[60] = 0;
   out_915104698457213198[61] = 0;
   out_915104698457213198[62] = 0;
   out_915104698457213198[63] = 0;
   out_915104698457213198[64] = 0;
   out_915104698457213198[65] = 0;
   out_915104698457213198[66] = dt;
   out_915104698457213198[67] = 0;
   out_915104698457213198[68] = 0;
   out_915104698457213198[69] = 0;
   out_915104698457213198[70] = 0;
   out_915104698457213198[71] = 0;
   out_915104698457213198[72] = 0;
   out_915104698457213198[73] = 0;
   out_915104698457213198[74] = 0;
   out_915104698457213198[75] = 0;
   out_915104698457213198[76] = 1;
   out_915104698457213198[77] = 0;
   out_915104698457213198[78] = 0;
   out_915104698457213198[79] = 0;
   out_915104698457213198[80] = 0;
   out_915104698457213198[81] = 0;
   out_915104698457213198[82] = 0;
   out_915104698457213198[83] = 0;
   out_915104698457213198[84] = 0;
   out_915104698457213198[85] = dt;
   out_915104698457213198[86] = 0;
   out_915104698457213198[87] = 0;
   out_915104698457213198[88] = 0;
   out_915104698457213198[89] = 0;
   out_915104698457213198[90] = 0;
   out_915104698457213198[91] = 0;
   out_915104698457213198[92] = 0;
   out_915104698457213198[93] = 0;
   out_915104698457213198[94] = 0;
   out_915104698457213198[95] = 1;
   out_915104698457213198[96] = 0;
   out_915104698457213198[97] = 0;
   out_915104698457213198[98] = 0;
   out_915104698457213198[99] = 0;
   out_915104698457213198[100] = 0;
   out_915104698457213198[101] = 0;
   out_915104698457213198[102] = 0;
   out_915104698457213198[103] = 0;
   out_915104698457213198[104] = dt;
   out_915104698457213198[105] = 0;
   out_915104698457213198[106] = 0;
   out_915104698457213198[107] = 0;
   out_915104698457213198[108] = 0;
   out_915104698457213198[109] = 0;
   out_915104698457213198[110] = 0;
   out_915104698457213198[111] = 0;
   out_915104698457213198[112] = 0;
   out_915104698457213198[113] = 0;
   out_915104698457213198[114] = 1;
   out_915104698457213198[115] = 0;
   out_915104698457213198[116] = 0;
   out_915104698457213198[117] = 0;
   out_915104698457213198[118] = 0;
   out_915104698457213198[119] = 0;
   out_915104698457213198[120] = 0;
   out_915104698457213198[121] = 0;
   out_915104698457213198[122] = 0;
   out_915104698457213198[123] = 0;
   out_915104698457213198[124] = 0;
   out_915104698457213198[125] = 0;
   out_915104698457213198[126] = 0;
   out_915104698457213198[127] = 0;
   out_915104698457213198[128] = 0;
   out_915104698457213198[129] = 0;
   out_915104698457213198[130] = 0;
   out_915104698457213198[131] = 0;
   out_915104698457213198[132] = 0;
   out_915104698457213198[133] = 1;
   out_915104698457213198[134] = 0;
   out_915104698457213198[135] = 0;
   out_915104698457213198[136] = 0;
   out_915104698457213198[137] = 0;
   out_915104698457213198[138] = 0;
   out_915104698457213198[139] = 0;
   out_915104698457213198[140] = 0;
   out_915104698457213198[141] = 0;
   out_915104698457213198[142] = 0;
   out_915104698457213198[143] = 0;
   out_915104698457213198[144] = 0;
   out_915104698457213198[145] = 0;
   out_915104698457213198[146] = 0;
   out_915104698457213198[147] = 0;
   out_915104698457213198[148] = 0;
   out_915104698457213198[149] = 0;
   out_915104698457213198[150] = 0;
   out_915104698457213198[151] = 0;
   out_915104698457213198[152] = 1;
   out_915104698457213198[153] = 0;
   out_915104698457213198[154] = 0;
   out_915104698457213198[155] = 0;
   out_915104698457213198[156] = 0;
   out_915104698457213198[157] = 0;
   out_915104698457213198[158] = 0;
   out_915104698457213198[159] = 0;
   out_915104698457213198[160] = 0;
   out_915104698457213198[161] = 0;
   out_915104698457213198[162] = 0;
   out_915104698457213198[163] = 0;
   out_915104698457213198[164] = 0;
   out_915104698457213198[165] = 0;
   out_915104698457213198[166] = 0;
   out_915104698457213198[167] = 0;
   out_915104698457213198[168] = 0;
   out_915104698457213198[169] = 0;
   out_915104698457213198[170] = 0;
   out_915104698457213198[171] = 1;
   out_915104698457213198[172] = 0;
   out_915104698457213198[173] = 0;
   out_915104698457213198[174] = 0;
   out_915104698457213198[175] = 0;
   out_915104698457213198[176] = 0;
   out_915104698457213198[177] = 0;
   out_915104698457213198[178] = 0;
   out_915104698457213198[179] = 0;
   out_915104698457213198[180] = 0;
   out_915104698457213198[181] = 0;
   out_915104698457213198[182] = 0;
   out_915104698457213198[183] = 0;
   out_915104698457213198[184] = 0;
   out_915104698457213198[185] = 0;
   out_915104698457213198[186] = 0;
   out_915104698457213198[187] = 0;
   out_915104698457213198[188] = 0;
   out_915104698457213198[189] = 0;
   out_915104698457213198[190] = 1;
   out_915104698457213198[191] = 0;
   out_915104698457213198[192] = 0;
   out_915104698457213198[193] = 0;
   out_915104698457213198[194] = 0;
   out_915104698457213198[195] = 0;
   out_915104698457213198[196] = 0;
   out_915104698457213198[197] = 0;
   out_915104698457213198[198] = 0;
   out_915104698457213198[199] = 0;
   out_915104698457213198[200] = 0;
   out_915104698457213198[201] = 0;
   out_915104698457213198[202] = 0;
   out_915104698457213198[203] = 0;
   out_915104698457213198[204] = 0;
   out_915104698457213198[205] = 0;
   out_915104698457213198[206] = 0;
   out_915104698457213198[207] = 0;
   out_915104698457213198[208] = 0;
   out_915104698457213198[209] = 1;
   out_915104698457213198[210] = 0;
   out_915104698457213198[211] = 0;
   out_915104698457213198[212] = 0;
   out_915104698457213198[213] = 0;
   out_915104698457213198[214] = 0;
   out_915104698457213198[215] = 0;
   out_915104698457213198[216] = 0;
   out_915104698457213198[217] = 0;
   out_915104698457213198[218] = 0;
   out_915104698457213198[219] = 0;
   out_915104698457213198[220] = 0;
   out_915104698457213198[221] = 0;
   out_915104698457213198[222] = 0;
   out_915104698457213198[223] = 0;
   out_915104698457213198[224] = 0;
   out_915104698457213198[225] = 0;
   out_915104698457213198[226] = 0;
   out_915104698457213198[227] = 0;
   out_915104698457213198[228] = 1;
   out_915104698457213198[229] = 0;
   out_915104698457213198[230] = 0;
   out_915104698457213198[231] = 0;
   out_915104698457213198[232] = 0;
   out_915104698457213198[233] = 0;
   out_915104698457213198[234] = 0;
   out_915104698457213198[235] = 0;
   out_915104698457213198[236] = 0;
   out_915104698457213198[237] = 0;
   out_915104698457213198[238] = 0;
   out_915104698457213198[239] = 0;
   out_915104698457213198[240] = 0;
   out_915104698457213198[241] = 0;
   out_915104698457213198[242] = 0;
   out_915104698457213198[243] = 0;
   out_915104698457213198[244] = 0;
   out_915104698457213198[245] = 0;
   out_915104698457213198[246] = 0;
   out_915104698457213198[247] = 1;
   out_915104698457213198[248] = 0;
   out_915104698457213198[249] = 0;
   out_915104698457213198[250] = 0;
   out_915104698457213198[251] = 0;
   out_915104698457213198[252] = 0;
   out_915104698457213198[253] = 0;
   out_915104698457213198[254] = 0;
   out_915104698457213198[255] = 0;
   out_915104698457213198[256] = 0;
   out_915104698457213198[257] = 0;
   out_915104698457213198[258] = 0;
   out_915104698457213198[259] = 0;
   out_915104698457213198[260] = 0;
   out_915104698457213198[261] = 0;
   out_915104698457213198[262] = 0;
   out_915104698457213198[263] = 0;
   out_915104698457213198[264] = 0;
   out_915104698457213198[265] = 0;
   out_915104698457213198[266] = 1;
   out_915104698457213198[267] = 0;
   out_915104698457213198[268] = 0;
   out_915104698457213198[269] = 0;
   out_915104698457213198[270] = 0;
   out_915104698457213198[271] = 0;
   out_915104698457213198[272] = 0;
   out_915104698457213198[273] = 0;
   out_915104698457213198[274] = 0;
   out_915104698457213198[275] = 0;
   out_915104698457213198[276] = 0;
   out_915104698457213198[277] = 0;
   out_915104698457213198[278] = 0;
   out_915104698457213198[279] = 0;
   out_915104698457213198[280] = 0;
   out_915104698457213198[281] = 0;
   out_915104698457213198[282] = 0;
   out_915104698457213198[283] = 0;
   out_915104698457213198[284] = 0;
   out_915104698457213198[285] = 1;
   out_915104698457213198[286] = 0;
   out_915104698457213198[287] = 0;
   out_915104698457213198[288] = 0;
   out_915104698457213198[289] = 0;
   out_915104698457213198[290] = 0;
   out_915104698457213198[291] = 0;
   out_915104698457213198[292] = 0;
   out_915104698457213198[293] = 0;
   out_915104698457213198[294] = 0;
   out_915104698457213198[295] = 0;
   out_915104698457213198[296] = 0;
   out_915104698457213198[297] = 0;
   out_915104698457213198[298] = 0;
   out_915104698457213198[299] = 0;
   out_915104698457213198[300] = 0;
   out_915104698457213198[301] = 0;
   out_915104698457213198[302] = 0;
   out_915104698457213198[303] = 0;
   out_915104698457213198[304] = 1;
   out_915104698457213198[305] = 0;
   out_915104698457213198[306] = 0;
   out_915104698457213198[307] = 0;
   out_915104698457213198[308] = 0;
   out_915104698457213198[309] = 0;
   out_915104698457213198[310] = 0;
   out_915104698457213198[311] = 0;
   out_915104698457213198[312] = 0;
   out_915104698457213198[313] = 0;
   out_915104698457213198[314] = 0;
   out_915104698457213198[315] = 0;
   out_915104698457213198[316] = 0;
   out_915104698457213198[317] = 0;
   out_915104698457213198[318] = 0;
   out_915104698457213198[319] = 0;
   out_915104698457213198[320] = 0;
   out_915104698457213198[321] = 0;
   out_915104698457213198[322] = 0;
   out_915104698457213198[323] = 1;
}
void h_4(double *state, double *unused, double *out_4848764096163798698) {
   out_4848764096163798698[0] = state[6] + state[9];
   out_4848764096163798698[1] = state[7] + state[10];
   out_4848764096163798698[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5179743546280581054) {
   out_5179743546280581054[0] = 0;
   out_5179743546280581054[1] = 0;
   out_5179743546280581054[2] = 0;
   out_5179743546280581054[3] = 0;
   out_5179743546280581054[4] = 0;
   out_5179743546280581054[5] = 0;
   out_5179743546280581054[6] = 1;
   out_5179743546280581054[7] = 0;
   out_5179743546280581054[8] = 0;
   out_5179743546280581054[9] = 1;
   out_5179743546280581054[10] = 0;
   out_5179743546280581054[11] = 0;
   out_5179743546280581054[12] = 0;
   out_5179743546280581054[13] = 0;
   out_5179743546280581054[14] = 0;
   out_5179743546280581054[15] = 0;
   out_5179743546280581054[16] = 0;
   out_5179743546280581054[17] = 0;
   out_5179743546280581054[18] = 0;
   out_5179743546280581054[19] = 0;
   out_5179743546280581054[20] = 0;
   out_5179743546280581054[21] = 0;
   out_5179743546280581054[22] = 0;
   out_5179743546280581054[23] = 0;
   out_5179743546280581054[24] = 0;
   out_5179743546280581054[25] = 1;
   out_5179743546280581054[26] = 0;
   out_5179743546280581054[27] = 0;
   out_5179743546280581054[28] = 1;
   out_5179743546280581054[29] = 0;
   out_5179743546280581054[30] = 0;
   out_5179743546280581054[31] = 0;
   out_5179743546280581054[32] = 0;
   out_5179743546280581054[33] = 0;
   out_5179743546280581054[34] = 0;
   out_5179743546280581054[35] = 0;
   out_5179743546280581054[36] = 0;
   out_5179743546280581054[37] = 0;
   out_5179743546280581054[38] = 0;
   out_5179743546280581054[39] = 0;
   out_5179743546280581054[40] = 0;
   out_5179743546280581054[41] = 0;
   out_5179743546280581054[42] = 0;
   out_5179743546280581054[43] = 0;
   out_5179743546280581054[44] = 1;
   out_5179743546280581054[45] = 0;
   out_5179743546280581054[46] = 0;
   out_5179743546280581054[47] = 1;
   out_5179743546280581054[48] = 0;
   out_5179743546280581054[49] = 0;
   out_5179743546280581054[50] = 0;
   out_5179743546280581054[51] = 0;
   out_5179743546280581054[52] = 0;
   out_5179743546280581054[53] = 0;
}
void h_10(double *state, double *unused, double *out_6403830294478679987) {
   out_6403830294478679987[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6403830294478679987[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6403830294478679987[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1159038497426952620) {
   out_1159038497426952620[0] = 0;
   out_1159038497426952620[1] = 9.8100000000000005*cos(state[1]);
   out_1159038497426952620[2] = 0;
   out_1159038497426952620[3] = 0;
   out_1159038497426952620[4] = -state[8];
   out_1159038497426952620[5] = state[7];
   out_1159038497426952620[6] = 0;
   out_1159038497426952620[7] = state[5];
   out_1159038497426952620[8] = -state[4];
   out_1159038497426952620[9] = 0;
   out_1159038497426952620[10] = 0;
   out_1159038497426952620[11] = 0;
   out_1159038497426952620[12] = 1;
   out_1159038497426952620[13] = 0;
   out_1159038497426952620[14] = 0;
   out_1159038497426952620[15] = 1;
   out_1159038497426952620[16] = 0;
   out_1159038497426952620[17] = 0;
   out_1159038497426952620[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1159038497426952620[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1159038497426952620[20] = 0;
   out_1159038497426952620[21] = state[8];
   out_1159038497426952620[22] = 0;
   out_1159038497426952620[23] = -state[6];
   out_1159038497426952620[24] = -state[5];
   out_1159038497426952620[25] = 0;
   out_1159038497426952620[26] = state[3];
   out_1159038497426952620[27] = 0;
   out_1159038497426952620[28] = 0;
   out_1159038497426952620[29] = 0;
   out_1159038497426952620[30] = 0;
   out_1159038497426952620[31] = 1;
   out_1159038497426952620[32] = 0;
   out_1159038497426952620[33] = 0;
   out_1159038497426952620[34] = 1;
   out_1159038497426952620[35] = 0;
   out_1159038497426952620[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1159038497426952620[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1159038497426952620[38] = 0;
   out_1159038497426952620[39] = -state[7];
   out_1159038497426952620[40] = state[6];
   out_1159038497426952620[41] = 0;
   out_1159038497426952620[42] = state[4];
   out_1159038497426952620[43] = -state[3];
   out_1159038497426952620[44] = 0;
   out_1159038497426952620[45] = 0;
   out_1159038497426952620[46] = 0;
   out_1159038497426952620[47] = 0;
   out_1159038497426952620[48] = 0;
   out_1159038497426952620[49] = 0;
   out_1159038497426952620[50] = 1;
   out_1159038497426952620[51] = 0;
   out_1159038497426952620[52] = 0;
   out_1159038497426952620[53] = 1;
}
void h_13(double *state, double *unused, double *out_8750933078138370929) {
   out_8750933078138370929[0] = state[3];
   out_8750933078138370929[1] = state[4];
   out_8750933078138370929[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5656369319112269633) {
   out_5656369319112269633[0] = 0;
   out_5656369319112269633[1] = 0;
   out_5656369319112269633[2] = 0;
   out_5656369319112269633[3] = 1;
   out_5656369319112269633[4] = 0;
   out_5656369319112269633[5] = 0;
   out_5656369319112269633[6] = 0;
   out_5656369319112269633[7] = 0;
   out_5656369319112269633[8] = 0;
   out_5656369319112269633[9] = 0;
   out_5656369319112269633[10] = 0;
   out_5656369319112269633[11] = 0;
   out_5656369319112269633[12] = 0;
   out_5656369319112269633[13] = 0;
   out_5656369319112269633[14] = 0;
   out_5656369319112269633[15] = 0;
   out_5656369319112269633[16] = 0;
   out_5656369319112269633[17] = 0;
   out_5656369319112269633[18] = 0;
   out_5656369319112269633[19] = 0;
   out_5656369319112269633[20] = 0;
   out_5656369319112269633[21] = 0;
   out_5656369319112269633[22] = 1;
   out_5656369319112269633[23] = 0;
   out_5656369319112269633[24] = 0;
   out_5656369319112269633[25] = 0;
   out_5656369319112269633[26] = 0;
   out_5656369319112269633[27] = 0;
   out_5656369319112269633[28] = 0;
   out_5656369319112269633[29] = 0;
   out_5656369319112269633[30] = 0;
   out_5656369319112269633[31] = 0;
   out_5656369319112269633[32] = 0;
   out_5656369319112269633[33] = 0;
   out_5656369319112269633[34] = 0;
   out_5656369319112269633[35] = 0;
   out_5656369319112269633[36] = 0;
   out_5656369319112269633[37] = 0;
   out_5656369319112269633[38] = 0;
   out_5656369319112269633[39] = 0;
   out_5656369319112269633[40] = 0;
   out_5656369319112269633[41] = 1;
   out_5656369319112269633[42] = 0;
   out_5656369319112269633[43] = 0;
   out_5656369319112269633[44] = 0;
   out_5656369319112269633[45] = 0;
   out_5656369319112269633[46] = 0;
   out_5656369319112269633[47] = 0;
   out_5656369319112269633[48] = 0;
   out_5656369319112269633[49] = 0;
   out_5656369319112269633[50] = 0;
   out_5656369319112269633[51] = 0;
   out_5656369319112269633[52] = 0;
   out_5656369319112269633[53] = 0;
}
void h_14(double *state, double *unused, double *out_7722972172433229947) {
   out_7722972172433229947[0] = state[6];
   out_7722972172433229947[1] = state[7];
   out_7722972172433229947[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2096955113985208758) {
   out_2096955113985208758[0] = 0;
   out_2096955113985208758[1] = 0;
   out_2096955113985208758[2] = 0;
   out_2096955113985208758[3] = 0;
   out_2096955113985208758[4] = 0;
   out_2096955113985208758[5] = 0;
   out_2096955113985208758[6] = 1;
   out_2096955113985208758[7] = 0;
   out_2096955113985208758[8] = 0;
   out_2096955113985208758[9] = 0;
   out_2096955113985208758[10] = 0;
   out_2096955113985208758[11] = 0;
   out_2096955113985208758[12] = 0;
   out_2096955113985208758[13] = 0;
   out_2096955113985208758[14] = 0;
   out_2096955113985208758[15] = 0;
   out_2096955113985208758[16] = 0;
   out_2096955113985208758[17] = 0;
   out_2096955113985208758[18] = 0;
   out_2096955113985208758[19] = 0;
   out_2096955113985208758[20] = 0;
   out_2096955113985208758[21] = 0;
   out_2096955113985208758[22] = 0;
   out_2096955113985208758[23] = 0;
   out_2096955113985208758[24] = 0;
   out_2096955113985208758[25] = 1;
   out_2096955113985208758[26] = 0;
   out_2096955113985208758[27] = 0;
   out_2096955113985208758[28] = 0;
   out_2096955113985208758[29] = 0;
   out_2096955113985208758[30] = 0;
   out_2096955113985208758[31] = 0;
   out_2096955113985208758[32] = 0;
   out_2096955113985208758[33] = 0;
   out_2096955113985208758[34] = 0;
   out_2096955113985208758[35] = 0;
   out_2096955113985208758[36] = 0;
   out_2096955113985208758[37] = 0;
   out_2096955113985208758[38] = 0;
   out_2096955113985208758[39] = 0;
   out_2096955113985208758[40] = 0;
   out_2096955113985208758[41] = 0;
   out_2096955113985208758[42] = 0;
   out_2096955113985208758[43] = 0;
   out_2096955113985208758[44] = 1;
   out_2096955113985208758[45] = 0;
   out_2096955113985208758[46] = 0;
   out_2096955113985208758[47] = 0;
   out_2096955113985208758[48] = 0;
   out_2096955113985208758[49] = 0;
   out_2096955113985208758[50] = 0;
   out_2096955113985208758[51] = 0;
   out_2096955113985208758[52] = 0;
   out_2096955113985208758[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5991537263051443263) {
  err_fun(nom_x, delta_x, out_5991537263051443263);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2628315792951768716) {
  inv_err_fun(nom_x, true_x, out_2628315792951768716);
}
void pose_H_mod_fun(double *state, double *out_4425582544225868447) {
  H_mod_fun(state, out_4425582544225868447);
}
void pose_f_fun(double *state, double dt, double *out_61910386899534067) {
  f_fun(state,  dt, out_61910386899534067);
}
void pose_F_fun(double *state, double dt, double *out_915104698457213198) {
  F_fun(state,  dt, out_915104698457213198);
}
void pose_h_4(double *state, double *unused, double *out_4848764096163798698) {
  h_4(state, unused, out_4848764096163798698);
}
void pose_H_4(double *state, double *unused, double *out_5179743546280581054) {
  H_4(state, unused, out_5179743546280581054);
}
void pose_h_10(double *state, double *unused, double *out_6403830294478679987) {
  h_10(state, unused, out_6403830294478679987);
}
void pose_H_10(double *state, double *unused, double *out_1159038497426952620) {
  H_10(state, unused, out_1159038497426952620);
}
void pose_h_13(double *state, double *unused, double *out_8750933078138370929) {
  h_13(state, unused, out_8750933078138370929);
}
void pose_H_13(double *state, double *unused, double *out_5656369319112269633) {
  H_13(state, unused, out_5656369319112269633);
}
void pose_h_14(double *state, double *unused, double *out_7722972172433229947) {
  h_14(state, unused, out_7722972172433229947);
}
void pose_H_14(double *state, double *unused, double *out_2096955113985208758) {
  H_14(state, unused, out_2096955113985208758);
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
