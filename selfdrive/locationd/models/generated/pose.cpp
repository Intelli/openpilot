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
void err_fun(double *nom_x, double *delta_x, double *out_4781408360620996115) {
   out_4781408360620996115[0] = delta_x[0] + nom_x[0];
   out_4781408360620996115[1] = delta_x[1] + nom_x[1];
   out_4781408360620996115[2] = delta_x[2] + nom_x[2];
   out_4781408360620996115[3] = delta_x[3] + nom_x[3];
   out_4781408360620996115[4] = delta_x[4] + nom_x[4];
   out_4781408360620996115[5] = delta_x[5] + nom_x[5];
   out_4781408360620996115[6] = delta_x[6] + nom_x[6];
   out_4781408360620996115[7] = delta_x[7] + nom_x[7];
   out_4781408360620996115[8] = delta_x[8] + nom_x[8];
   out_4781408360620996115[9] = delta_x[9] + nom_x[9];
   out_4781408360620996115[10] = delta_x[10] + nom_x[10];
   out_4781408360620996115[11] = delta_x[11] + nom_x[11];
   out_4781408360620996115[12] = delta_x[12] + nom_x[12];
   out_4781408360620996115[13] = delta_x[13] + nom_x[13];
   out_4781408360620996115[14] = delta_x[14] + nom_x[14];
   out_4781408360620996115[15] = delta_x[15] + nom_x[15];
   out_4781408360620996115[16] = delta_x[16] + nom_x[16];
   out_4781408360620996115[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8699824419183456650) {
   out_8699824419183456650[0] = -nom_x[0] + true_x[0];
   out_8699824419183456650[1] = -nom_x[1] + true_x[1];
   out_8699824419183456650[2] = -nom_x[2] + true_x[2];
   out_8699824419183456650[3] = -nom_x[3] + true_x[3];
   out_8699824419183456650[4] = -nom_x[4] + true_x[4];
   out_8699824419183456650[5] = -nom_x[5] + true_x[5];
   out_8699824419183456650[6] = -nom_x[6] + true_x[6];
   out_8699824419183456650[7] = -nom_x[7] + true_x[7];
   out_8699824419183456650[8] = -nom_x[8] + true_x[8];
   out_8699824419183456650[9] = -nom_x[9] + true_x[9];
   out_8699824419183456650[10] = -nom_x[10] + true_x[10];
   out_8699824419183456650[11] = -nom_x[11] + true_x[11];
   out_8699824419183456650[12] = -nom_x[12] + true_x[12];
   out_8699824419183456650[13] = -nom_x[13] + true_x[13];
   out_8699824419183456650[14] = -nom_x[14] + true_x[14];
   out_8699824419183456650[15] = -nom_x[15] + true_x[15];
   out_8699824419183456650[16] = -nom_x[16] + true_x[16];
   out_8699824419183456650[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4078091713371530257) {
   out_4078091713371530257[0] = 1.0;
   out_4078091713371530257[1] = 0.0;
   out_4078091713371530257[2] = 0.0;
   out_4078091713371530257[3] = 0.0;
   out_4078091713371530257[4] = 0.0;
   out_4078091713371530257[5] = 0.0;
   out_4078091713371530257[6] = 0.0;
   out_4078091713371530257[7] = 0.0;
   out_4078091713371530257[8] = 0.0;
   out_4078091713371530257[9] = 0.0;
   out_4078091713371530257[10] = 0.0;
   out_4078091713371530257[11] = 0.0;
   out_4078091713371530257[12] = 0.0;
   out_4078091713371530257[13] = 0.0;
   out_4078091713371530257[14] = 0.0;
   out_4078091713371530257[15] = 0.0;
   out_4078091713371530257[16] = 0.0;
   out_4078091713371530257[17] = 0.0;
   out_4078091713371530257[18] = 0.0;
   out_4078091713371530257[19] = 1.0;
   out_4078091713371530257[20] = 0.0;
   out_4078091713371530257[21] = 0.0;
   out_4078091713371530257[22] = 0.0;
   out_4078091713371530257[23] = 0.0;
   out_4078091713371530257[24] = 0.0;
   out_4078091713371530257[25] = 0.0;
   out_4078091713371530257[26] = 0.0;
   out_4078091713371530257[27] = 0.0;
   out_4078091713371530257[28] = 0.0;
   out_4078091713371530257[29] = 0.0;
   out_4078091713371530257[30] = 0.0;
   out_4078091713371530257[31] = 0.0;
   out_4078091713371530257[32] = 0.0;
   out_4078091713371530257[33] = 0.0;
   out_4078091713371530257[34] = 0.0;
   out_4078091713371530257[35] = 0.0;
   out_4078091713371530257[36] = 0.0;
   out_4078091713371530257[37] = 0.0;
   out_4078091713371530257[38] = 1.0;
   out_4078091713371530257[39] = 0.0;
   out_4078091713371530257[40] = 0.0;
   out_4078091713371530257[41] = 0.0;
   out_4078091713371530257[42] = 0.0;
   out_4078091713371530257[43] = 0.0;
   out_4078091713371530257[44] = 0.0;
   out_4078091713371530257[45] = 0.0;
   out_4078091713371530257[46] = 0.0;
   out_4078091713371530257[47] = 0.0;
   out_4078091713371530257[48] = 0.0;
   out_4078091713371530257[49] = 0.0;
   out_4078091713371530257[50] = 0.0;
   out_4078091713371530257[51] = 0.0;
   out_4078091713371530257[52] = 0.0;
   out_4078091713371530257[53] = 0.0;
   out_4078091713371530257[54] = 0.0;
   out_4078091713371530257[55] = 0.0;
   out_4078091713371530257[56] = 0.0;
   out_4078091713371530257[57] = 1.0;
   out_4078091713371530257[58] = 0.0;
   out_4078091713371530257[59] = 0.0;
   out_4078091713371530257[60] = 0.0;
   out_4078091713371530257[61] = 0.0;
   out_4078091713371530257[62] = 0.0;
   out_4078091713371530257[63] = 0.0;
   out_4078091713371530257[64] = 0.0;
   out_4078091713371530257[65] = 0.0;
   out_4078091713371530257[66] = 0.0;
   out_4078091713371530257[67] = 0.0;
   out_4078091713371530257[68] = 0.0;
   out_4078091713371530257[69] = 0.0;
   out_4078091713371530257[70] = 0.0;
   out_4078091713371530257[71] = 0.0;
   out_4078091713371530257[72] = 0.0;
   out_4078091713371530257[73] = 0.0;
   out_4078091713371530257[74] = 0.0;
   out_4078091713371530257[75] = 0.0;
   out_4078091713371530257[76] = 1.0;
   out_4078091713371530257[77] = 0.0;
   out_4078091713371530257[78] = 0.0;
   out_4078091713371530257[79] = 0.0;
   out_4078091713371530257[80] = 0.0;
   out_4078091713371530257[81] = 0.0;
   out_4078091713371530257[82] = 0.0;
   out_4078091713371530257[83] = 0.0;
   out_4078091713371530257[84] = 0.0;
   out_4078091713371530257[85] = 0.0;
   out_4078091713371530257[86] = 0.0;
   out_4078091713371530257[87] = 0.0;
   out_4078091713371530257[88] = 0.0;
   out_4078091713371530257[89] = 0.0;
   out_4078091713371530257[90] = 0.0;
   out_4078091713371530257[91] = 0.0;
   out_4078091713371530257[92] = 0.0;
   out_4078091713371530257[93] = 0.0;
   out_4078091713371530257[94] = 0.0;
   out_4078091713371530257[95] = 1.0;
   out_4078091713371530257[96] = 0.0;
   out_4078091713371530257[97] = 0.0;
   out_4078091713371530257[98] = 0.0;
   out_4078091713371530257[99] = 0.0;
   out_4078091713371530257[100] = 0.0;
   out_4078091713371530257[101] = 0.0;
   out_4078091713371530257[102] = 0.0;
   out_4078091713371530257[103] = 0.0;
   out_4078091713371530257[104] = 0.0;
   out_4078091713371530257[105] = 0.0;
   out_4078091713371530257[106] = 0.0;
   out_4078091713371530257[107] = 0.0;
   out_4078091713371530257[108] = 0.0;
   out_4078091713371530257[109] = 0.0;
   out_4078091713371530257[110] = 0.0;
   out_4078091713371530257[111] = 0.0;
   out_4078091713371530257[112] = 0.0;
   out_4078091713371530257[113] = 0.0;
   out_4078091713371530257[114] = 1.0;
   out_4078091713371530257[115] = 0.0;
   out_4078091713371530257[116] = 0.0;
   out_4078091713371530257[117] = 0.0;
   out_4078091713371530257[118] = 0.0;
   out_4078091713371530257[119] = 0.0;
   out_4078091713371530257[120] = 0.0;
   out_4078091713371530257[121] = 0.0;
   out_4078091713371530257[122] = 0.0;
   out_4078091713371530257[123] = 0.0;
   out_4078091713371530257[124] = 0.0;
   out_4078091713371530257[125] = 0.0;
   out_4078091713371530257[126] = 0.0;
   out_4078091713371530257[127] = 0.0;
   out_4078091713371530257[128] = 0.0;
   out_4078091713371530257[129] = 0.0;
   out_4078091713371530257[130] = 0.0;
   out_4078091713371530257[131] = 0.0;
   out_4078091713371530257[132] = 0.0;
   out_4078091713371530257[133] = 1.0;
   out_4078091713371530257[134] = 0.0;
   out_4078091713371530257[135] = 0.0;
   out_4078091713371530257[136] = 0.0;
   out_4078091713371530257[137] = 0.0;
   out_4078091713371530257[138] = 0.0;
   out_4078091713371530257[139] = 0.0;
   out_4078091713371530257[140] = 0.0;
   out_4078091713371530257[141] = 0.0;
   out_4078091713371530257[142] = 0.0;
   out_4078091713371530257[143] = 0.0;
   out_4078091713371530257[144] = 0.0;
   out_4078091713371530257[145] = 0.0;
   out_4078091713371530257[146] = 0.0;
   out_4078091713371530257[147] = 0.0;
   out_4078091713371530257[148] = 0.0;
   out_4078091713371530257[149] = 0.0;
   out_4078091713371530257[150] = 0.0;
   out_4078091713371530257[151] = 0.0;
   out_4078091713371530257[152] = 1.0;
   out_4078091713371530257[153] = 0.0;
   out_4078091713371530257[154] = 0.0;
   out_4078091713371530257[155] = 0.0;
   out_4078091713371530257[156] = 0.0;
   out_4078091713371530257[157] = 0.0;
   out_4078091713371530257[158] = 0.0;
   out_4078091713371530257[159] = 0.0;
   out_4078091713371530257[160] = 0.0;
   out_4078091713371530257[161] = 0.0;
   out_4078091713371530257[162] = 0.0;
   out_4078091713371530257[163] = 0.0;
   out_4078091713371530257[164] = 0.0;
   out_4078091713371530257[165] = 0.0;
   out_4078091713371530257[166] = 0.0;
   out_4078091713371530257[167] = 0.0;
   out_4078091713371530257[168] = 0.0;
   out_4078091713371530257[169] = 0.0;
   out_4078091713371530257[170] = 0.0;
   out_4078091713371530257[171] = 1.0;
   out_4078091713371530257[172] = 0.0;
   out_4078091713371530257[173] = 0.0;
   out_4078091713371530257[174] = 0.0;
   out_4078091713371530257[175] = 0.0;
   out_4078091713371530257[176] = 0.0;
   out_4078091713371530257[177] = 0.0;
   out_4078091713371530257[178] = 0.0;
   out_4078091713371530257[179] = 0.0;
   out_4078091713371530257[180] = 0.0;
   out_4078091713371530257[181] = 0.0;
   out_4078091713371530257[182] = 0.0;
   out_4078091713371530257[183] = 0.0;
   out_4078091713371530257[184] = 0.0;
   out_4078091713371530257[185] = 0.0;
   out_4078091713371530257[186] = 0.0;
   out_4078091713371530257[187] = 0.0;
   out_4078091713371530257[188] = 0.0;
   out_4078091713371530257[189] = 0.0;
   out_4078091713371530257[190] = 1.0;
   out_4078091713371530257[191] = 0.0;
   out_4078091713371530257[192] = 0.0;
   out_4078091713371530257[193] = 0.0;
   out_4078091713371530257[194] = 0.0;
   out_4078091713371530257[195] = 0.0;
   out_4078091713371530257[196] = 0.0;
   out_4078091713371530257[197] = 0.0;
   out_4078091713371530257[198] = 0.0;
   out_4078091713371530257[199] = 0.0;
   out_4078091713371530257[200] = 0.0;
   out_4078091713371530257[201] = 0.0;
   out_4078091713371530257[202] = 0.0;
   out_4078091713371530257[203] = 0.0;
   out_4078091713371530257[204] = 0.0;
   out_4078091713371530257[205] = 0.0;
   out_4078091713371530257[206] = 0.0;
   out_4078091713371530257[207] = 0.0;
   out_4078091713371530257[208] = 0.0;
   out_4078091713371530257[209] = 1.0;
   out_4078091713371530257[210] = 0.0;
   out_4078091713371530257[211] = 0.0;
   out_4078091713371530257[212] = 0.0;
   out_4078091713371530257[213] = 0.0;
   out_4078091713371530257[214] = 0.0;
   out_4078091713371530257[215] = 0.0;
   out_4078091713371530257[216] = 0.0;
   out_4078091713371530257[217] = 0.0;
   out_4078091713371530257[218] = 0.0;
   out_4078091713371530257[219] = 0.0;
   out_4078091713371530257[220] = 0.0;
   out_4078091713371530257[221] = 0.0;
   out_4078091713371530257[222] = 0.0;
   out_4078091713371530257[223] = 0.0;
   out_4078091713371530257[224] = 0.0;
   out_4078091713371530257[225] = 0.0;
   out_4078091713371530257[226] = 0.0;
   out_4078091713371530257[227] = 0.0;
   out_4078091713371530257[228] = 1.0;
   out_4078091713371530257[229] = 0.0;
   out_4078091713371530257[230] = 0.0;
   out_4078091713371530257[231] = 0.0;
   out_4078091713371530257[232] = 0.0;
   out_4078091713371530257[233] = 0.0;
   out_4078091713371530257[234] = 0.0;
   out_4078091713371530257[235] = 0.0;
   out_4078091713371530257[236] = 0.0;
   out_4078091713371530257[237] = 0.0;
   out_4078091713371530257[238] = 0.0;
   out_4078091713371530257[239] = 0.0;
   out_4078091713371530257[240] = 0.0;
   out_4078091713371530257[241] = 0.0;
   out_4078091713371530257[242] = 0.0;
   out_4078091713371530257[243] = 0.0;
   out_4078091713371530257[244] = 0.0;
   out_4078091713371530257[245] = 0.0;
   out_4078091713371530257[246] = 0.0;
   out_4078091713371530257[247] = 1.0;
   out_4078091713371530257[248] = 0.0;
   out_4078091713371530257[249] = 0.0;
   out_4078091713371530257[250] = 0.0;
   out_4078091713371530257[251] = 0.0;
   out_4078091713371530257[252] = 0.0;
   out_4078091713371530257[253] = 0.0;
   out_4078091713371530257[254] = 0.0;
   out_4078091713371530257[255] = 0.0;
   out_4078091713371530257[256] = 0.0;
   out_4078091713371530257[257] = 0.0;
   out_4078091713371530257[258] = 0.0;
   out_4078091713371530257[259] = 0.0;
   out_4078091713371530257[260] = 0.0;
   out_4078091713371530257[261] = 0.0;
   out_4078091713371530257[262] = 0.0;
   out_4078091713371530257[263] = 0.0;
   out_4078091713371530257[264] = 0.0;
   out_4078091713371530257[265] = 0.0;
   out_4078091713371530257[266] = 1.0;
   out_4078091713371530257[267] = 0.0;
   out_4078091713371530257[268] = 0.0;
   out_4078091713371530257[269] = 0.0;
   out_4078091713371530257[270] = 0.0;
   out_4078091713371530257[271] = 0.0;
   out_4078091713371530257[272] = 0.0;
   out_4078091713371530257[273] = 0.0;
   out_4078091713371530257[274] = 0.0;
   out_4078091713371530257[275] = 0.0;
   out_4078091713371530257[276] = 0.0;
   out_4078091713371530257[277] = 0.0;
   out_4078091713371530257[278] = 0.0;
   out_4078091713371530257[279] = 0.0;
   out_4078091713371530257[280] = 0.0;
   out_4078091713371530257[281] = 0.0;
   out_4078091713371530257[282] = 0.0;
   out_4078091713371530257[283] = 0.0;
   out_4078091713371530257[284] = 0.0;
   out_4078091713371530257[285] = 1.0;
   out_4078091713371530257[286] = 0.0;
   out_4078091713371530257[287] = 0.0;
   out_4078091713371530257[288] = 0.0;
   out_4078091713371530257[289] = 0.0;
   out_4078091713371530257[290] = 0.0;
   out_4078091713371530257[291] = 0.0;
   out_4078091713371530257[292] = 0.0;
   out_4078091713371530257[293] = 0.0;
   out_4078091713371530257[294] = 0.0;
   out_4078091713371530257[295] = 0.0;
   out_4078091713371530257[296] = 0.0;
   out_4078091713371530257[297] = 0.0;
   out_4078091713371530257[298] = 0.0;
   out_4078091713371530257[299] = 0.0;
   out_4078091713371530257[300] = 0.0;
   out_4078091713371530257[301] = 0.0;
   out_4078091713371530257[302] = 0.0;
   out_4078091713371530257[303] = 0.0;
   out_4078091713371530257[304] = 1.0;
   out_4078091713371530257[305] = 0.0;
   out_4078091713371530257[306] = 0.0;
   out_4078091713371530257[307] = 0.0;
   out_4078091713371530257[308] = 0.0;
   out_4078091713371530257[309] = 0.0;
   out_4078091713371530257[310] = 0.0;
   out_4078091713371530257[311] = 0.0;
   out_4078091713371530257[312] = 0.0;
   out_4078091713371530257[313] = 0.0;
   out_4078091713371530257[314] = 0.0;
   out_4078091713371530257[315] = 0.0;
   out_4078091713371530257[316] = 0.0;
   out_4078091713371530257[317] = 0.0;
   out_4078091713371530257[318] = 0.0;
   out_4078091713371530257[319] = 0.0;
   out_4078091713371530257[320] = 0.0;
   out_4078091713371530257[321] = 0.0;
   out_4078091713371530257[322] = 0.0;
   out_4078091713371530257[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3654134625857924620) {
   out_3654134625857924620[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3654134625857924620[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3654134625857924620[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3654134625857924620[3] = dt*state[12] + state[3];
   out_3654134625857924620[4] = dt*state[13] + state[4];
   out_3654134625857924620[5] = dt*state[14] + state[5];
   out_3654134625857924620[6] = state[6];
   out_3654134625857924620[7] = state[7];
   out_3654134625857924620[8] = state[8];
   out_3654134625857924620[9] = state[9];
   out_3654134625857924620[10] = state[10];
   out_3654134625857924620[11] = state[11];
   out_3654134625857924620[12] = state[12];
   out_3654134625857924620[13] = state[13];
   out_3654134625857924620[14] = state[14];
   out_3654134625857924620[15] = state[15];
   out_3654134625857924620[16] = state[16];
   out_3654134625857924620[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4922789249915948413) {
   out_4922789249915948413[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4922789249915948413[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4922789249915948413[2] = 0;
   out_4922789249915948413[3] = 0;
   out_4922789249915948413[4] = 0;
   out_4922789249915948413[5] = 0;
   out_4922789249915948413[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4922789249915948413[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4922789249915948413[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4922789249915948413[9] = 0;
   out_4922789249915948413[10] = 0;
   out_4922789249915948413[11] = 0;
   out_4922789249915948413[12] = 0;
   out_4922789249915948413[13] = 0;
   out_4922789249915948413[14] = 0;
   out_4922789249915948413[15] = 0;
   out_4922789249915948413[16] = 0;
   out_4922789249915948413[17] = 0;
   out_4922789249915948413[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4922789249915948413[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4922789249915948413[20] = 0;
   out_4922789249915948413[21] = 0;
   out_4922789249915948413[22] = 0;
   out_4922789249915948413[23] = 0;
   out_4922789249915948413[24] = 0;
   out_4922789249915948413[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4922789249915948413[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4922789249915948413[27] = 0;
   out_4922789249915948413[28] = 0;
   out_4922789249915948413[29] = 0;
   out_4922789249915948413[30] = 0;
   out_4922789249915948413[31] = 0;
   out_4922789249915948413[32] = 0;
   out_4922789249915948413[33] = 0;
   out_4922789249915948413[34] = 0;
   out_4922789249915948413[35] = 0;
   out_4922789249915948413[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4922789249915948413[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4922789249915948413[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4922789249915948413[39] = 0;
   out_4922789249915948413[40] = 0;
   out_4922789249915948413[41] = 0;
   out_4922789249915948413[42] = 0;
   out_4922789249915948413[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4922789249915948413[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4922789249915948413[45] = 0;
   out_4922789249915948413[46] = 0;
   out_4922789249915948413[47] = 0;
   out_4922789249915948413[48] = 0;
   out_4922789249915948413[49] = 0;
   out_4922789249915948413[50] = 0;
   out_4922789249915948413[51] = 0;
   out_4922789249915948413[52] = 0;
   out_4922789249915948413[53] = 0;
   out_4922789249915948413[54] = 0;
   out_4922789249915948413[55] = 0;
   out_4922789249915948413[56] = 0;
   out_4922789249915948413[57] = 1;
   out_4922789249915948413[58] = 0;
   out_4922789249915948413[59] = 0;
   out_4922789249915948413[60] = 0;
   out_4922789249915948413[61] = 0;
   out_4922789249915948413[62] = 0;
   out_4922789249915948413[63] = 0;
   out_4922789249915948413[64] = 0;
   out_4922789249915948413[65] = 0;
   out_4922789249915948413[66] = dt;
   out_4922789249915948413[67] = 0;
   out_4922789249915948413[68] = 0;
   out_4922789249915948413[69] = 0;
   out_4922789249915948413[70] = 0;
   out_4922789249915948413[71] = 0;
   out_4922789249915948413[72] = 0;
   out_4922789249915948413[73] = 0;
   out_4922789249915948413[74] = 0;
   out_4922789249915948413[75] = 0;
   out_4922789249915948413[76] = 1;
   out_4922789249915948413[77] = 0;
   out_4922789249915948413[78] = 0;
   out_4922789249915948413[79] = 0;
   out_4922789249915948413[80] = 0;
   out_4922789249915948413[81] = 0;
   out_4922789249915948413[82] = 0;
   out_4922789249915948413[83] = 0;
   out_4922789249915948413[84] = 0;
   out_4922789249915948413[85] = dt;
   out_4922789249915948413[86] = 0;
   out_4922789249915948413[87] = 0;
   out_4922789249915948413[88] = 0;
   out_4922789249915948413[89] = 0;
   out_4922789249915948413[90] = 0;
   out_4922789249915948413[91] = 0;
   out_4922789249915948413[92] = 0;
   out_4922789249915948413[93] = 0;
   out_4922789249915948413[94] = 0;
   out_4922789249915948413[95] = 1;
   out_4922789249915948413[96] = 0;
   out_4922789249915948413[97] = 0;
   out_4922789249915948413[98] = 0;
   out_4922789249915948413[99] = 0;
   out_4922789249915948413[100] = 0;
   out_4922789249915948413[101] = 0;
   out_4922789249915948413[102] = 0;
   out_4922789249915948413[103] = 0;
   out_4922789249915948413[104] = dt;
   out_4922789249915948413[105] = 0;
   out_4922789249915948413[106] = 0;
   out_4922789249915948413[107] = 0;
   out_4922789249915948413[108] = 0;
   out_4922789249915948413[109] = 0;
   out_4922789249915948413[110] = 0;
   out_4922789249915948413[111] = 0;
   out_4922789249915948413[112] = 0;
   out_4922789249915948413[113] = 0;
   out_4922789249915948413[114] = 1;
   out_4922789249915948413[115] = 0;
   out_4922789249915948413[116] = 0;
   out_4922789249915948413[117] = 0;
   out_4922789249915948413[118] = 0;
   out_4922789249915948413[119] = 0;
   out_4922789249915948413[120] = 0;
   out_4922789249915948413[121] = 0;
   out_4922789249915948413[122] = 0;
   out_4922789249915948413[123] = 0;
   out_4922789249915948413[124] = 0;
   out_4922789249915948413[125] = 0;
   out_4922789249915948413[126] = 0;
   out_4922789249915948413[127] = 0;
   out_4922789249915948413[128] = 0;
   out_4922789249915948413[129] = 0;
   out_4922789249915948413[130] = 0;
   out_4922789249915948413[131] = 0;
   out_4922789249915948413[132] = 0;
   out_4922789249915948413[133] = 1;
   out_4922789249915948413[134] = 0;
   out_4922789249915948413[135] = 0;
   out_4922789249915948413[136] = 0;
   out_4922789249915948413[137] = 0;
   out_4922789249915948413[138] = 0;
   out_4922789249915948413[139] = 0;
   out_4922789249915948413[140] = 0;
   out_4922789249915948413[141] = 0;
   out_4922789249915948413[142] = 0;
   out_4922789249915948413[143] = 0;
   out_4922789249915948413[144] = 0;
   out_4922789249915948413[145] = 0;
   out_4922789249915948413[146] = 0;
   out_4922789249915948413[147] = 0;
   out_4922789249915948413[148] = 0;
   out_4922789249915948413[149] = 0;
   out_4922789249915948413[150] = 0;
   out_4922789249915948413[151] = 0;
   out_4922789249915948413[152] = 1;
   out_4922789249915948413[153] = 0;
   out_4922789249915948413[154] = 0;
   out_4922789249915948413[155] = 0;
   out_4922789249915948413[156] = 0;
   out_4922789249915948413[157] = 0;
   out_4922789249915948413[158] = 0;
   out_4922789249915948413[159] = 0;
   out_4922789249915948413[160] = 0;
   out_4922789249915948413[161] = 0;
   out_4922789249915948413[162] = 0;
   out_4922789249915948413[163] = 0;
   out_4922789249915948413[164] = 0;
   out_4922789249915948413[165] = 0;
   out_4922789249915948413[166] = 0;
   out_4922789249915948413[167] = 0;
   out_4922789249915948413[168] = 0;
   out_4922789249915948413[169] = 0;
   out_4922789249915948413[170] = 0;
   out_4922789249915948413[171] = 1;
   out_4922789249915948413[172] = 0;
   out_4922789249915948413[173] = 0;
   out_4922789249915948413[174] = 0;
   out_4922789249915948413[175] = 0;
   out_4922789249915948413[176] = 0;
   out_4922789249915948413[177] = 0;
   out_4922789249915948413[178] = 0;
   out_4922789249915948413[179] = 0;
   out_4922789249915948413[180] = 0;
   out_4922789249915948413[181] = 0;
   out_4922789249915948413[182] = 0;
   out_4922789249915948413[183] = 0;
   out_4922789249915948413[184] = 0;
   out_4922789249915948413[185] = 0;
   out_4922789249915948413[186] = 0;
   out_4922789249915948413[187] = 0;
   out_4922789249915948413[188] = 0;
   out_4922789249915948413[189] = 0;
   out_4922789249915948413[190] = 1;
   out_4922789249915948413[191] = 0;
   out_4922789249915948413[192] = 0;
   out_4922789249915948413[193] = 0;
   out_4922789249915948413[194] = 0;
   out_4922789249915948413[195] = 0;
   out_4922789249915948413[196] = 0;
   out_4922789249915948413[197] = 0;
   out_4922789249915948413[198] = 0;
   out_4922789249915948413[199] = 0;
   out_4922789249915948413[200] = 0;
   out_4922789249915948413[201] = 0;
   out_4922789249915948413[202] = 0;
   out_4922789249915948413[203] = 0;
   out_4922789249915948413[204] = 0;
   out_4922789249915948413[205] = 0;
   out_4922789249915948413[206] = 0;
   out_4922789249915948413[207] = 0;
   out_4922789249915948413[208] = 0;
   out_4922789249915948413[209] = 1;
   out_4922789249915948413[210] = 0;
   out_4922789249915948413[211] = 0;
   out_4922789249915948413[212] = 0;
   out_4922789249915948413[213] = 0;
   out_4922789249915948413[214] = 0;
   out_4922789249915948413[215] = 0;
   out_4922789249915948413[216] = 0;
   out_4922789249915948413[217] = 0;
   out_4922789249915948413[218] = 0;
   out_4922789249915948413[219] = 0;
   out_4922789249915948413[220] = 0;
   out_4922789249915948413[221] = 0;
   out_4922789249915948413[222] = 0;
   out_4922789249915948413[223] = 0;
   out_4922789249915948413[224] = 0;
   out_4922789249915948413[225] = 0;
   out_4922789249915948413[226] = 0;
   out_4922789249915948413[227] = 0;
   out_4922789249915948413[228] = 1;
   out_4922789249915948413[229] = 0;
   out_4922789249915948413[230] = 0;
   out_4922789249915948413[231] = 0;
   out_4922789249915948413[232] = 0;
   out_4922789249915948413[233] = 0;
   out_4922789249915948413[234] = 0;
   out_4922789249915948413[235] = 0;
   out_4922789249915948413[236] = 0;
   out_4922789249915948413[237] = 0;
   out_4922789249915948413[238] = 0;
   out_4922789249915948413[239] = 0;
   out_4922789249915948413[240] = 0;
   out_4922789249915948413[241] = 0;
   out_4922789249915948413[242] = 0;
   out_4922789249915948413[243] = 0;
   out_4922789249915948413[244] = 0;
   out_4922789249915948413[245] = 0;
   out_4922789249915948413[246] = 0;
   out_4922789249915948413[247] = 1;
   out_4922789249915948413[248] = 0;
   out_4922789249915948413[249] = 0;
   out_4922789249915948413[250] = 0;
   out_4922789249915948413[251] = 0;
   out_4922789249915948413[252] = 0;
   out_4922789249915948413[253] = 0;
   out_4922789249915948413[254] = 0;
   out_4922789249915948413[255] = 0;
   out_4922789249915948413[256] = 0;
   out_4922789249915948413[257] = 0;
   out_4922789249915948413[258] = 0;
   out_4922789249915948413[259] = 0;
   out_4922789249915948413[260] = 0;
   out_4922789249915948413[261] = 0;
   out_4922789249915948413[262] = 0;
   out_4922789249915948413[263] = 0;
   out_4922789249915948413[264] = 0;
   out_4922789249915948413[265] = 0;
   out_4922789249915948413[266] = 1;
   out_4922789249915948413[267] = 0;
   out_4922789249915948413[268] = 0;
   out_4922789249915948413[269] = 0;
   out_4922789249915948413[270] = 0;
   out_4922789249915948413[271] = 0;
   out_4922789249915948413[272] = 0;
   out_4922789249915948413[273] = 0;
   out_4922789249915948413[274] = 0;
   out_4922789249915948413[275] = 0;
   out_4922789249915948413[276] = 0;
   out_4922789249915948413[277] = 0;
   out_4922789249915948413[278] = 0;
   out_4922789249915948413[279] = 0;
   out_4922789249915948413[280] = 0;
   out_4922789249915948413[281] = 0;
   out_4922789249915948413[282] = 0;
   out_4922789249915948413[283] = 0;
   out_4922789249915948413[284] = 0;
   out_4922789249915948413[285] = 1;
   out_4922789249915948413[286] = 0;
   out_4922789249915948413[287] = 0;
   out_4922789249915948413[288] = 0;
   out_4922789249915948413[289] = 0;
   out_4922789249915948413[290] = 0;
   out_4922789249915948413[291] = 0;
   out_4922789249915948413[292] = 0;
   out_4922789249915948413[293] = 0;
   out_4922789249915948413[294] = 0;
   out_4922789249915948413[295] = 0;
   out_4922789249915948413[296] = 0;
   out_4922789249915948413[297] = 0;
   out_4922789249915948413[298] = 0;
   out_4922789249915948413[299] = 0;
   out_4922789249915948413[300] = 0;
   out_4922789249915948413[301] = 0;
   out_4922789249915948413[302] = 0;
   out_4922789249915948413[303] = 0;
   out_4922789249915948413[304] = 1;
   out_4922789249915948413[305] = 0;
   out_4922789249915948413[306] = 0;
   out_4922789249915948413[307] = 0;
   out_4922789249915948413[308] = 0;
   out_4922789249915948413[309] = 0;
   out_4922789249915948413[310] = 0;
   out_4922789249915948413[311] = 0;
   out_4922789249915948413[312] = 0;
   out_4922789249915948413[313] = 0;
   out_4922789249915948413[314] = 0;
   out_4922789249915948413[315] = 0;
   out_4922789249915948413[316] = 0;
   out_4922789249915948413[317] = 0;
   out_4922789249915948413[318] = 0;
   out_4922789249915948413[319] = 0;
   out_4922789249915948413[320] = 0;
   out_4922789249915948413[321] = 0;
   out_4922789249915948413[322] = 0;
   out_4922789249915948413[323] = 1;
}
void h_4(double *state, double *unused, double *out_1614563645168656522) {
   out_1614563645168656522[0] = state[6] + state[9];
   out_1614563645168656522[1] = state[7] + state[10];
   out_1614563645168656522[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4866269952686291085) {
   out_4866269952686291085[0] = 0;
   out_4866269952686291085[1] = 0;
   out_4866269952686291085[2] = 0;
   out_4866269952686291085[3] = 0;
   out_4866269952686291085[4] = 0;
   out_4866269952686291085[5] = 0;
   out_4866269952686291085[6] = 1;
   out_4866269952686291085[7] = 0;
   out_4866269952686291085[8] = 0;
   out_4866269952686291085[9] = 1;
   out_4866269952686291085[10] = 0;
   out_4866269952686291085[11] = 0;
   out_4866269952686291085[12] = 0;
   out_4866269952686291085[13] = 0;
   out_4866269952686291085[14] = 0;
   out_4866269952686291085[15] = 0;
   out_4866269952686291085[16] = 0;
   out_4866269952686291085[17] = 0;
   out_4866269952686291085[18] = 0;
   out_4866269952686291085[19] = 0;
   out_4866269952686291085[20] = 0;
   out_4866269952686291085[21] = 0;
   out_4866269952686291085[22] = 0;
   out_4866269952686291085[23] = 0;
   out_4866269952686291085[24] = 0;
   out_4866269952686291085[25] = 1;
   out_4866269952686291085[26] = 0;
   out_4866269952686291085[27] = 0;
   out_4866269952686291085[28] = 1;
   out_4866269952686291085[29] = 0;
   out_4866269952686291085[30] = 0;
   out_4866269952686291085[31] = 0;
   out_4866269952686291085[32] = 0;
   out_4866269952686291085[33] = 0;
   out_4866269952686291085[34] = 0;
   out_4866269952686291085[35] = 0;
   out_4866269952686291085[36] = 0;
   out_4866269952686291085[37] = 0;
   out_4866269952686291085[38] = 0;
   out_4866269952686291085[39] = 0;
   out_4866269952686291085[40] = 0;
   out_4866269952686291085[41] = 0;
   out_4866269952686291085[42] = 0;
   out_4866269952686291085[43] = 0;
   out_4866269952686291085[44] = 1;
   out_4866269952686291085[45] = 0;
   out_4866269952686291085[46] = 0;
   out_4866269952686291085[47] = 1;
   out_4866269952686291085[48] = 0;
   out_4866269952686291085[49] = 0;
   out_4866269952686291085[50] = 0;
   out_4866269952686291085[51] = 0;
   out_4866269952686291085[52] = 0;
   out_4866269952686291085[53] = 0;
}
void h_10(double *state, double *unused, double *out_6213117493135598820) {
   out_6213117493135598820[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6213117493135598820[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6213117493135598820[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5311772579141249863) {
   out_5311772579141249863[0] = 0;
   out_5311772579141249863[1] = 9.8100000000000005*cos(state[1]);
   out_5311772579141249863[2] = 0;
   out_5311772579141249863[3] = 0;
   out_5311772579141249863[4] = -state[8];
   out_5311772579141249863[5] = state[7];
   out_5311772579141249863[6] = 0;
   out_5311772579141249863[7] = state[5];
   out_5311772579141249863[8] = -state[4];
   out_5311772579141249863[9] = 0;
   out_5311772579141249863[10] = 0;
   out_5311772579141249863[11] = 0;
   out_5311772579141249863[12] = 1;
   out_5311772579141249863[13] = 0;
   out_5311772579141249863[14] = 0;
   out_5311772579141249863[15] = 1;
   out_5311772579141249863[16] = 0;
   out_5311772579141249863[17] = 0;
   out_5311772579141249863[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5311772579141249863[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5311772579141249863[20] = 0;
   out_5311772579141249863[21] = state[8];
   out_5311772579141249863[22] = 0;
   out_5311772579141249863[23] = -state[6];
   out_5311772579141249863[24] = -state[5];
   out_5311772579141249863[25] = 0;
   out_5311772579141249863[26] = state[3];
   out_5311772579141249863[27] = 0;
   out_5311772579141249863[28] = 0;
   out_5311772579141249863[29] = 0;
   out_5311772579141249863[30] = 0;
   out_5311772579141249863[31] = 1;
   out_5311772579141249863[32] = 0;
   out_5311772579141249863[33] = 0;
   out_5311772579141249863[34] = 1;
   out_5311772579141249863[35] = 0;
   out_5311772579141249863[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5311772579141249863[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5311772579141249863[38] = 0;
   out_5311772579141249863[39] = -state[7];
   out_5311772579141249863[40] = state[6];
   out_5311772579141249863[41] = 0;
   out_5311772579141249863[42] = state[4];
   out_5311772579141249863[43] = -state[3];
   out_5311772579141249863[44] = 0;
   out_5311772579141249863[45] = 0;
   out_5311772579141249863[46] = 0;
   out_5311772579141249863[47] = 0;
   out_5311772579141249863[48] = 0;
   out_5311772579141249863[49] = 0;
   out_5311772579141249863[50] = 1;
   out_5311772579141249863[51] = 0;
   out_5311772579141249863[52] = 0;
   out_5311772579141249863[53] = 1;
}
void h_13(double *state, double *unused, double *out_11034046619496304) {
   out_11034046619496304[0] = state[3];
   out_11034046619496304[1] = state[4];
   out_11034046619496304[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1653996127353958284) {
   out_1653996127353958284[0] = 0;
   out_1653996127353958284[1] = 0;
   out_1653996127353958284[2] = 0;
   out_1653996127353958284[3] = 1;
   out_1653996127353958284[4] = 0;
   out_1653996127353958284[5] = 0;
   out_1653996127353958284[6] = 0;
   out_1653996127353958284[7] = 0;
   out_1653996127353958284[8] = 0;
   out_1653996127353958284[9] = 0;
   out_1653996127353958284[10] = 0;
   out_1653996127353958284[11] = 0;
   out_1653996127353958284[12] = 0;
   out_1653996127353958284[13] = 0;
   out_1653996127353958284[14] = 0;
   out_1653996127353958284[15] = 0;
   out_1653996127353958284[16] = 0;
   out_1653996127353958284[17] = 0;
   out_1653996127353958284[18] = 0;
   out_1653996127353958284[19] = 0;
   out_1653996127353958284[20] = 0;
   out_1653996127353958284[21] = 0;
   out_1653996127353958284[22] = 1;
   out_1653996127353958284[23] = 0;
   out_1653996127353958284[24] = 0;
   out_1653996127353958284[25] = 0;
   out_1653996127353958284[26] = 0;
   out_1653996127353958284[27] = 0;
   out_1653996127353958284[28] = 0;
   out_1653996127353958284[29] = 0;
   out_1653996127353958284[30] = 0;
   out_1653996127353958284[31] = 0;
   out_1653996127353958284[32] = 0;
   out_1653996127353958284[33] = 0;
   out_1653996127353958284[34] = 0;
   out_1653996127353958284[35] = 0;
   out_1653996127353958284[36] = 0;
   out_1653996127353958284[37] = 0;
   out_1653996127353958284[38] = 0;
   out_1653996127353958284[39] = 0;
   out_1653996127353958284[40] = 0;
   out_1653996127353958284[41] = 1;
   out_1653996127353958284[42] = 0;
   out_1653996127353958284[43] = 0;
   out_1653996127353958284[44] = 0;
   out_1653996127353958284[45] = 0;
   out_1653996127353958284[46] = 0;
   out_1653996127353958284[47] = 0;
   out_1653996127353958284[48] = 0;
   out_1653996127353958284[49] = 0;
   out_1653996127353958284[50] = 0;
   out_1653996127353958284[51] = 0;
   out_1653996127353958284[52] = 0;
   out_1653996127353958284[53] = 0;
}
void h_14(double *state, double *unused, double *out_8590572313452717671) {
   out_8590572313452717671[0] = state[6];
   out_8590572313452717671[1] = state[7];
   out_8590572313452717671[2] = state[8];
}
void H_14(double *state, double *unused, double *out_903029096346806556) {
   out_903029096346806556[0] = 0;
   out_903029096346806556[1] = 0;
   out_903029096346806556[2] = 0;
   out_903029096346806556[3] = 0;
   out_903029096346806556[4] = 0;
   out_903029096346806556[5] = 0;
   out_903029096346806556[6] = 1;
   out_903029096346806556[7] = 0;
   out_903029096346806556[8] = 0;
   out_903029096346806556[9] = 0;
   out_903029096346806556[10] = 0;
   out_903029096346806556[11] = 0;
   out_903029096346806556[12] = 0;
   out_903029096346806556[13] = 0;
   out_903029096346806556[14] = 0;
   out_903029096346806556[15] = 0;
   out_903029096346806556[16] = 0;
   out_903029096346806556[17] = 0;
   out_903029096346806556[18] = 0;
   out_903029096346806556[19] = 0;
   out_903029096346806556[20] = 0;
   out_903029096346806556[21] = 0;
   out_903029096346806556[22] = 0;
   out_903029096346806556[23] = 0;
   out_903029096346806556[24] = 0;
   out_903029096346806556[25] = 1;
   out_903029096346806556[26] = 0;
   out_903029096346806556[27] = 0;
   out_903029096346806556[28] = 0;
   out_903029096346806556[29] = 0;
   out_903029096346806556[30] = 0;
   out_903029096346806556[31] = 0;
   out_903029096346806556[32] = 0;
   out_903029096346806556[33] = 0;
   out_903029096346806556[34] = 0;
   out_903029096346806556[35] = 0;
   out_903029096346806556[36] = 0;
   out_903029096346806556[37] = 0;
   out_903029096346806556[38] = 0;
   out_903029096346806556[39] = 0;
   out_903029096346806556[40] = 0;
   out_903029096346806556[41] = 0;
   out_903029096346806556[42] = 0;
   out_903029096346806556[43] = 0;
   out_903029096346806556[44] = 1;
   out_903029096346806556[45] = 0;
   out_903029096346806556[46] = 0;
   out_903029096346806556[47] = 0;
   out_903029096346806556[48] = 0;
   out_903029096346806556[49] = 0;
   out_903029096346806556[50] = 0;
   out_903029096346806556[51] = 0;
   out_903029096346806556[52] = 0;
   out_903029096346806556[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4781408360620996115) {
  err_fun(nom_x, delta_x, out_4781408360620996115);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8699824419183456650) {
  inv_err_fun(nom_x, true_x, out_8699824419183456650);
}
void pose_H_mod_fun(double *state, double *out_4078091713371530257) {
  H_mod_fun(state, out_4078091713371530257);
}
void pose_f_fun(double *state, double dt, double *out_3654134625857924620) {
  f_fun(state,  dt, out_3654134625857924620);
}
void pose_F_fun(double *state, double dt, double *out_4922789249915948413) {
  F_fun(state,  dt, out_4922789249915948413);
}
void pose_h_4(double *state, double *unused, double *out_1614563645168656522) {
  h_4(state, unused, out_1614563645168656522);
}
void pose_H_4(double *state, double *unused, double *out_4866269952686291085) {
  H_4(state, unused, out_4866269952686291085);
}
void pose_h_10(double *state, double *unused, double *out_6213117493135598820) {
  h_10(state, unused, out_6213117493135598820);
}
void pose_H_10(double *state, double *unused, double *out_5311772579141249863) {
  H_10(state, unused, out_5311772579141249863);
}
void pose_h_13(double *state, double *unused, double *out_11034046619496304) {
  h_13(state, unused, out_11034046619496304);
}
void pose_H_13(double *state, double *unused, double *out_1653996127353958284) {
  H_13(state, unused, out_1653996127353958284);
}
void pose_h_14(double *state, double *unused, double *out_8590572313452717671) {
  h_14(state, unused, out_8590572313452717671);
}
void pose_H_14(double *state, double *unused, double *out_903029096346806556) {
  H_14(state, unused, out_903029096346806556);
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
