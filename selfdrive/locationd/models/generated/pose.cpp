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
void err_fun(double *nom_x, double *delta_x, double *out_5133309144223277572) {
   out_5133309144223277572[0] = delta_x[0] + nom_x[0];
   out_5133309144223277572[1] = delta_x[1] + nom_x[1];
   out_5133309144223277572[2] = delta_x[2] + nom_x[2];
   out_5133309144223277572[3] = delta_x[3] + nom_x[3];
   out_5133309144223277572[4] = delta_x[4] + nom_x[4];
   out_5133309144223277572[5] = delta_x[5] + nom_x[5];
   out_5133309144223277572[6] = delta_x[6] + nom_x[6];
   out_5133309144223277572[7] = delta_x[7] + nom_x[7];
   out_5133309144223277572[8] = delta_x[8] + nom_x[8];
   out_5133309144223277572[9] = delta_x[9] + nom_x[9];
   out_5133309144223277572[10] = delta_x[10] + nom_x[10];
   out_5133309144223277572[11] = delta_x[11] + nom_x[11];
   out_5133309144223277572[12] = delta_x[12] + nom_x[12];
   out_5133309144223277572[13] = delta_x[13] + nom_x[13];
   out_5133309144223277572[14] = delta_x[14] + nom_x[14];
   out_5133309144223277572[15] = delta_x[15] + nom_x[15];
   out_5133309144223277572[16] = delta_x[16] + nom_x[16];
   out_5133309144223277572[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6881212781704972929) {
   out_6881212781704972929[0] = -nom_x[0] + true_x[0];
   out_6881212781704972929[1] = -nom_x[1] + true_x[1];
   out_6881212781704972929[2] = -nom_x[2] + true_x[2];
   out_6881212781704972929[3] = -nom_x[3] + true_x[3];
   out_6881212781704972929[4] = -nom_x[4] + true_x[4];
   out_6881212781704972929[5] = -nom_x[5] + true_x[5];
   out_6881212781704972929[6] = -nom_x[6] + true_x[6];
   out_6881212781704972929[7] = -nom_x[7] + true_x[7];
   out_6881212781704972929[8] = -nom_x[8] + true_x[8];
   out_6881212781704972929[9] = -nom_x[9] + true_x[9];
   out_6881212781704972929[10] = -nom_x[10] + true_x[10];
   out_6881212781704972929[11] = -nom_x[11] + true_x[11];
   out_6881212781704972929[12] = -nom_x[12] + true_x[12];
   out_6881212781704972929[13] = -nom_x[13] + true_x[13];
   out_6881212781704972929[14] = -nom_x[14] + true_x[14];
   out_6881212781704972929[15] = -nom_x[15] + true_x[15];
   out_6881212781704972929[16] = -nom_x[16] + true_x[16];
   out_6881212781704972929[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6869028127987583637) {
   out_6869028127987583637[0] = 1.0;
   out_6869028127987583637[1] = 0.0;
   out_6869028127987583637[2] = 0.0;
   out_6869028127987583637[3] = 0.0;
   out_6869028127987583637[4] = 0.0;
   out_6869028127987583637[5] = 0.0;
   out_6869028127987583637[6] = 0.0;
   out_6869028127987583637[7] = 0.0;
   out_6869028127987583637[8] = 0.0;
   out_6869028127987583637[9] = 0.0;
   out_6869028127987583637[10] = 0.0;
   out_6869028127987583637[11] = 0.0;
   out_6869028127987583637[12] = 0.0;
   out_6869028127987583637[13] = 0.0;
   out_6869028127987583637[14] = 0.0;
   out_6869028127987583637[15] = 0.0;
   out_6869028127987583637[16] = 0.0;
   out_6869028127987583637[17] = 0.0;
   out_6869028127987583637[18] = 0.0;
   out_6869028127987583637[19] = 1.0;
   out_6869028127987583637[20] = 0.0;
   out_6869028127987583637[21] = 0.0;
   out_6869028127987583637[22] = 0.0;
   out_6869028127987583637[23] = 0.0;
   out_6869028127987583637[24] = 0.0;
   out_6869028127987583637[25] = 0.0;
   out_6869028127987583637[26] = 0.0;
   out_6869028127987583637[27] = 0.0;
   out_6869028127987583637[28] = 0.0;
   out_6869028127987583637[29] = 0.0;
   out_6869028127987583637[30] = 0.0;
   out_6869028127987583637[31] = 0.0;
   out_6869028127987583637[32] = 0.0;
   out_6869028127987583637[33] = 0.0;
   out_6869028127987583637[34] = 0.0;
   out_6869028127987583637[35] = 0.0;
   out_6869028127987583637[36] = 0.0;
   out_6869028127987583637[37] = 0.0;
   out_6869028127987583637[38] = 1.0;
   out_6869028127987583637[39] = 0.0;
   out_6869028127987583637[40] = 0.0;
   out_6869028127987583637[41] = 0.0;
   out_6869028127987583637[42] = 0.0;
   out_6869028127987583637[43] = 0.0;
   out_6869028127987583637[44] = 0.0;
   out_6869028127987583637[45] = 0.0;
   out_6869028127987583637[46] = 0.0;
   out_6869028127987583637[47] = 0.0;
   out_6869028127987583637[48] = 0.0;
   out_6869028127987583637[49] = 0.0;
   out_6869028127987583637[50] = 0.0;
   out_6869028127987583637[51] = 0.0;
   out_6869028127987583637[52] = 0.0;
   out_6869028127987583637[53] = 0.0;
   out_6869028127987583637[54] = 0.0;
   out_6869028127987583637[55] = 0.0;
   out_6869028127987583637[56] = 0.0;
   out_6869028127987583637[57] = 1.0;
   out_6869028127987583637[58] = 0.0;
   out_6869028127987583637[59] = 0.0;
   out_6869028127987583637[60] = 0.0;
   out_6869028127987583637[61] = 0.0;
   out_6869028127987583637[62] = 0.0;
   out_6869028127987583637[63] = 0.0;
   out_6869028127987583637[64] = 0.0;
   out_6869028127987583637[65] = 0.0;
   out_6869028127987583637[66] = 0.0;
   out_6869028127987583637[67] = 0.0;
   out_6869028127987583637[68] = 0.0;
   out_6869028127987583637[69] = 0.0;
   out_6869028127987583637[70] = 0.0;
   out_6869028127987583637[71] = 0.0;
   out_6869028127987583637[72] = 0.0;
   out_6869028127987583637[73] = 0.0;
   out_6869028127987583637[74] = 0.0;
   out_6869028127987583637[75] = 0.0;
   out_6869028127987583637[76] = 1.0;
   out_6869028127987583637[77] = 0.0;
   out_6869028127987583637[78] = 0.0;
   out_6869028127987583637[79] = 0.0;
   out_6869028127987583637[80] = 0.0;
   out_6869028127987583637[81] = 0.0;
   out_6869028127987583637[82] = 0.0;
   out_6869028127987583637[83] = 0.0;
   out_6869028127987583637[84] = 0.0;
   out_6869028127987583637[85] = 0.0;
   out_6869028127987583637[86] = 0.0;
   out_6869028127987583637[87] = 0.0;
   out_6869028127987583637[88] = 0.0;
   out_6869028127987583637[89] = 0.0;
   out_6869028127987583637[90] = 0.0;
   out_6869028127987583637[91] = 0.0;
   out_6869028127987583637[92] = 0.0;
   out_6869028127987583637[93] = 0.0;
   out_6869028127987583637[94] = 0.0;
   out_6869028127987583637[95] = 1.0;
   out_6869028127987583637[96] = 0.0;
   out_6869028127987583637[97] = 0.0;
   out_6869028127987583637[98] = 0.0;
   out_6869028127987583637[99] = 0.0;
   out_6869028127987583637[100] = 0.0;
   out_6869028127987583637[101] = 0.0;
   out_6869028127987583637[102] = 0.0;
   out_6869028127987583637[103] = 0.0;
   out_6869028127987583637[104] = 0.0;
   out_6869028127987583637[105] = 0.0;
   out_6869028127987583637[106] = 0.0;
   out_6869028127987583637[107] = 0.0;
   out_6869028127987583637[108] = 0.0;
   out_6869028127987583637[109] = 0.0;
   out_6869028127987583637[110] = 0.0;
   out_6869028127987583637[111] = 0.0;
   out_6869028127987583637[112] = 0.0;
   out_6869028127987583637[113] = 0.0;
   out_6869028127987583637[114] = 1.0;
   out_6869028127987583637[115] = 0.0;
   out_6869028127987583637[116] = 0.0;
   out_6869028127987583637[117] = 0.0;
   out_6869028127987583637[118] = 0.0;
   out_6869028127987583637[119] = 0.0;
   out_6869028127987583637[120] = 0.0;
   out_6869028127987583637[121] = 0.0;
   out_6869028127987583637[122] = 0.0;
   out_6869028127987583637[123] = 0.0;
   out_6869028127987583637[124] = 0.0;
   out_6869028127987583637[125] = 0.0;
   out_6869028127987583637[126] = 0.0;
   out_6869028127987583637[127] = 0.0;
   out_6869028127987583637[128] = 0.0;
   out_6869028127987583637[129] = 0.0;
   out_6869028127987583637[130] = 0.0;
   out_6869028127987583637[131] = 0.0;
   out_6869028127987583637[132] = 0.0;
   out_6869028127987583637[133] = 1.0;
   out_6869028127987583637[134] = 0.0;
   out_6869028127987583637[135] = 0.0;
   out_6869028127987583637[136] = 0.0;
   out_6869028127987583637[137] = 0.0;
   out_6869028127987583637[138] = 0.0;
   out_6869028127987583637[139] = 0.0;
   out_6869028127987583637[140] = 0.0;
   out_6869028127987583637[141] = 0.0;
   out_6869028127987583637[142] = 0.0;
   out_6869028127987583637[143] = 0.0;
   out_6869028127987583637[144] = 0.0;
   out_6869028127987583637[145] = 0.0;
   out_6869028127987583637[146] = 0.0;
   out_6869028127987583637[147] = 0.0;
   out_6869028127987583637[148] = 0.0;
   out_6869028127987583637[149] = 0.0;
   out_6869028127987583637[150] = 0.0;
   out_6869028127987583637[151] = 0.0;
   out_6869028127987583637[152] = 1.0;
   out_6869028127987583637[153] = 0.0;
   out_6869028127987583637[154] = 0.0;
   out_6869028127987583637[155] = 0.0;
   out_6869028127987583637[156] = 0.0;
   out_6869028127987583637[157] = 0.0;
   out_6869028127987583637[158] = 0.0;
   out_6869028127987583637[159] = 0.0;
   out_6869028127987583637[160] = 0.0;
   out_6869028127987583637[161] = 0.0;
   out_6869028127987583637[162] = 0.0;
   out_6869028127987583637[163] = 0.0;
   out_6869028127987583637[164] = 0.0;
   out_6869028127987583637[165] = 0.0;
   out_6869028127987583637[166] = 0.0;
   out_6869028127987583637[167] = 0.0;
   out_6869028127987583637[168] = 0.0;
   out_6869028127987583637[169] = 0.0;
   out_6869028127987583637[170] = 0.0;
   out_6869028127987583637[171] = 1.0;
   out_6869028127987583637[172] = 0.0;
   out_6869028127987583637[173] = 0.0;
   out_6869028127987583637[174] = 0.0;
   out_6869028127987583637[175] = 0.0;
   out_6869028127987583637[176] = 0.0;
   out_6869028127987583637[177] = 0.0;
   out_6869028127987583637[178] = 0.0;
   out_6869028127987583637[179] = 0.0;
   out_6869028127987583637[180] = 0.0;
   out_6869028127987583637[181] = 0.0;
   out_6869028127987583637[182] = 0.0;
   out_6869028127987583637[183] = 0.0;
   out_6869028127987583637[184] = 0.0;
   out_6869028127987583637[185] = 0.0;
   out_6869028127987583637[186] = 0.0;
   out_6869028127987583637[187] = 0.0;
   out_6869028127987583637[188] = 0.0;
   out_6869028127987583637[189] = 0.0;
   out_6869028127987583637[190] = 1.0;
   out_6869028127987583637[191] = 0.0;
   out_6869028127987583637[192] = 0.0;
   out_6869028127987583637[193] = 0.0;
   out_6869028127987583637[194] = 0.0;
   out_6869028127987583637[195] = 0.0;
   out_6869028127987583637[196] = 0.0;
   out_6869028127987583637[197] = 0.0;
   out_6869028127987583637[198] = 0.0;
   out_6869028127987583637[199] = 0.0;
   out_6869028127987583637[200] = 0.0;
   out_6869028127987583637[201] = 0.0;
   out_6869028127987583637[202] = 0.0;
   out_6869028127987583637[203] = 0.0;
   out_6869028127987583637[204] = 0.0;
   out_6869028127987583637[205] = 0.0;
   out_6869028127987583637[206] = 0.0;
   out_6869028127987583637[207] = 0.0;
   out_6869028127987583637[208] = 0.0;
   out_6869028127987583637[209] = 1.0;
   out_6869028127987583637[210] = 0.0;
   out_6869028127987583637[211] = 0.0;
   out_6869028127987583637[212] = 0.0;
   out_6869028127987583637[213] = 0.0;
   out_6869028127987583637[214] = 0.0;
   out_6869028127987583637[215] = 0.0;
   out_6869028127987583637[216] = 0.0;
   out_6869028127987583637[217] = 0.0;
   out_6869028127987583637[218] = 0.0;
   out_6869028127987583637[219] = 0.0;
   out_6869028127987583637[220] = 0.0;
   out_6869028127987583637[221] = 0.0;
   out_6869028127987583637[222] = 0.0;
   out_6869028127987583637[223] = 0.0;
   out_6869028127987583637[224] = 0.0;
   out_6869028127987583637[225] = 0.0;
   out_6869028127987583637[226] = 0.0;
   out_6869028127987583637[227] = 0.0;
   out_6869028127987583637[228] = 1.0;
   out_6869028127987583637[229] = 0.0;
   out_6869028127987583637[230] = 0.0;
   out_6869028127987583637[231] = 0.0;
   out_6869028127987583637[232] = 0.0;
   out_6869028127987583637[233] = 0.0;
   out_6869028127987583637[234] = 0.0;
   out_6869028127987583637[235] = 0.0;
   out_6869028127987583637[236] = 0.0;
   out_6869028127987583637[237] = 0.0;
   out_6869028127987583637[238] = 0.0;
   out_6869028127987583637[239] = 0.0;
   out_6869028127987583637[240] = 0.0;
   out_6869028127987583637[241] = 0.0;
   out_6869028127987583637[242] = 0.0;
   out_6869028127987583637[243] = 0.0;
   out_6869028127987583637[244] = 0.0;
   out_6869028127987583637[245] = 0.0;
   out_6869028127987583637[246] = 0.0;
   out_6869028127987583637[247] = 1.0;
   out_6869028127987583637[248] = 0.0;
   out_6869028127987583637[249] = 0.0;
   out_6869028127987583637[250] = 0.0;
   out_6869028127987583637[251] = 0.0;
   out_6869028127987583637[252] = 0.0;
   out_6869028127987583637[253] = 0.0;
   out_6869028127987583637[254] = 0.0;
   out_6869028127987583637[255] = 0.0;
   out_6869028127987583637[256] = 0.0;
   out_6869028127987583637[257] = 0.0;
   out_6869028127987583637[258] = 0.0;
   out_6869028127987583637[259] = 0.0;
   out_6869028127987583637[260] = 0.0;
   out_6869028127987583637[261] = 0.0;
   out_6869028127987583637[262] = 0.0;
   out_6869028127987583637[263] = 0.0;
   out_6869028127987583637[264] = 0.0;
   out_6869028127987583637[265] = 0.0;
   out_6869028127987583637[266] = 1.0;
   out_6869028127987583637[267] = 0.0;
   out_6869028127987583637[268] = 0.0;
   out_6869028127987583637[269] = 0.0;
   out_6869028127987583637[270] = 0.0;
   out_6869028127987583637[271] = 0.0;
   out_6869028127987583637[272] = 0.0;
   out_6869028127987583637[273] = 0.0;
   out_6869028127987583637[274] = 0.0;
   out_6869028127987583637[275] = 0.0;
   out_6869028127987583637[276] = 0.0;
   out_6869028127987583637[277] = 0.0;
   out_6869028127987583637[278] = 0.0;
   out_6869028127987583637[279] = 0.0;
   out_6869028127987583637[280] = 0.0;
   out_6869028127987583637[281] = 0.0;
   out_6869028127987583637[282] = 0.0;
   out_6869028127987583637[283] = 0.0;
   out_6869028127987583637[284] = 0.0;
   out_6869028127987583637[285] = 1.0;
   out_6869028127987583637[286] = 0.0;
   out_6869028127987583637[287] = 0.0;
   out_6869028127987583637[288] = 0.0;
   out_6869028127987583637[289] = 0.0;
   out_6869028127987583637[290] = 0.0;
   out_6869028127987583637[291] = 0.0;
   out_6869028127987583637[292] = 0.0;
   out_6869028127987583637[293] = 0.0;
   out_6869028127987583637[294] = 0.0;
   out_6869028127987583637[295] = 0.0;
   out_6869028127987583637[296] = 0.0;
   out_6869028127987583637[297] = 0.0;
   out_6869028127987583637[298] = 0.0;
   out_6869028127987583637[299] = 0.0;
   out_6869028127987583637[300] = 0.0;
   out_6869028127987583637[301] = 0.0;
   out_6869028127987583637[302] = 0.0;
   out_6869028127987583637[303] = 0.0;
   out_6869028127987583637[304] = 1.0;
   out_6869028127987583637[305] = 0.0;
   out_6869028127987583637[306] = 0.0;
   out_6869028127987583637[307] = 0.0;
   out_6869028127987583637[308] = 0.0;
   out_6869028127987583637[309] = 0.0;
   out_6869028127987583637[310] = 0.0;
   out_6869028127987583637[311] = 0.0;
   out_6869028127987583637[312] = 0.0;
   out_6869028127987583637[313] = 0.0;
   out_6869028127987583637[314] = 0.0;
   out_6869028127987583637[315] = 0.0;
   out_6869028127987583637[316] = 0.0;
   out_6869028127987583637[317] = 0.0;
   out_6869028127987583637[318] = 0.0;
   out_6869028127987583637[319] = 0.0;
   out_6869028127987583637[320] = 0.0;
   out_6869028127987583637[321] = 0.0;
   out_6869028127987583637[322] = 0.0;
   out_6869028127987583637[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8902612319160798640) {
   out_8902612319160798640[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8902612319160798640[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8902612319160798640[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8902612319160798640[3] = dt*state[12] + state[3];
   out_8902612319160798640[4] = dt*state[13] + state[4];
   out_8902612319160798640[5] = dt*state[14] + state[5];
   out_8902612319160798640[6] = state[6];
   out_8902612319160798640[7] = state[7];
   out_8902612319160798640[8] = state[8];
   out_8902612319160798640[9] = state[9];
   out_8902612319160798640[10] = state[10];
   out_8902612319160798640[11] = state[11];
   out_8902612319160798640[12] = state[12];
   out_8902612319160798640[13] = state[13];
   out_8902612319160798640[14] = state[14];
   out_8902612319160798640[15] = state[15];
   out_8902612319160798640[16] = state[16];
   out_8902612319160798640[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1483402946734561261) {
   out_1483402946734561261[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1483402946734561261[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1483402946734561261[2] = 0;
   out_1483402946734561261[3] = 0;
   out_1483402946734561261[4] = 0;
   out_1483402946734561261[5] = 0;
   out_1483402946734561261[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1483402946734561261[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1483402946734561261[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1483402946734561261[9] = 0;
   out_1483402946734561261[10] = 0;
   out_1483402946734561261[11] = 0;
   out_1483402946734561261[12] = 0;
   out_1483402946734561261[13] = 0;
   out_1483402946734561261[14] = 0;
   out_1483402946734561261[15] = 0;
   out_1483402946734561261[16] = 0;
   out_1483402946734561261[17] = 0;
   out_1483402946734561261[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1483402946734561261[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1483402946734561261[20] = 0;
   out_1483402946734561261[21] = 0;
   out_1483402946734561261[22] = 0;
   out_1483402946734561261[23] = 0;
   out_1483402946734561261[24] = 0;
   out_1483402946734561261[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1483402946734561261[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1483402946734561261[27] = 0;
   out_1483402946734561261[28] = 0;
   out_1483402946734561261[29] = 0;
   out_1483402946734561261[30] = 0;
   out_1483402946734561261[31] = 0;
   out_1483402946734561261[32] = 0;
   out_1483402946734561261[33] = 0;
   out_1483402946734561261[34] = 0;
   out_1483402946734561261[35] = 0;
   out_1483402946734561261[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1483402946734561261[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1483402946734561261[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1483402946734561261[39] = 0;
   out_1483402946734561261[40] = 0;
   out_1483402946734561261[41] = 0;
   out_1483402946734561261[42] = 0;
   out_1483402946734561261[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1483402946734561261[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1483402946734561261[45] = 0;
   out_1483402946734561261[46] = 0;
   out_1483402946734561261[47] = 0;
   out_1483402946734561261[48] = 0;
   out_1483402946734561261[49] = 0;
   out_1483402946734561261[50] = 0;
   out_1483402946734561261[51] = 0;
   out_1483402946734561261[52] = 0;
   out_1483402946734561261[53] = 0;
   out_1483402946734561261[54] = 0;
   out_1483402946734561261[55] = 0;
   out_1483402946734561261[56] = 0;
   out_1483402946734561261[57] = 1;
   out_1483402946734561261[58] = 0;
   out_1483402946734561261[59] = 0;
   out_1483402946734561261[60] = 0;
   out_1483402946734561261[61] = 0;
   out_1483402946734561261[62] = 0;
   out_1483402946734561261[63] = 0;
   out_1483402946734561261[64] = 0;
   out_1483402946734561261[65] = 0;
   out_1483402946734561261[66] = dt;
   out_1483402946734561261[67] = 0;
   out_1483402946734561261[68] = 0;
   out_1483402946734561261[69] = 0;
   out_1483402946734561261[70] = 0;
   out_1483402946734561261[71] = 0;
   out_1483402946734561261[72] = 0;
   out_1483402946734561261[73] = 0;
   out_1483402946734561261[74] = 0;
   out_1483402946734561261[75] = 0;
   out_1483402946734561261[76] = 1;
   out_1483402946734561261[77] = 0;
   out_1483402946734561261[78] = 0;
   out_1483402946734561261[79] = 0;
   out_1483402946734561261[80] = 0;
   out_1483402946734561261[81] = 0;
   out_1483402946734561261[82] = 0;
   out_1483402946734561261[83] = 0;
   out_1483402946734561261[84] = 0;
   out_1483402946734561261[85] = dt;
   out_1483402946734561261[86] = 0;
   out_1483402946734561261[87] = 0;
   out_1483402946734561261[88] = 0;
   out_1483402946734561261[89] = 0;
   out_1483402946734561261[90] = 0;
   out_1483402946734561261[91] = 0;
   out_1483402946734561261[92] = 0;
   out_1483402946734561261[93] = 0;
   out_1483402946734561261[94] = 0;
   out_1483402946734561261[95] = 1;
   out_1483402946734561261[96] = 0;
   out_1483402946734561261[97] = 0;
   out_1483402946734561261[98] = 0;
   out_1483402946734561261[99] = 0;
   out_1483402946734561261[100] = 0;
   out_1483402946734561261[101] = 0;
   out_1483402946734561261[102] = 0;
   out_1483402946734561261[103] = 0;
   out_1483402946734561261[104] = dt;
   out_1483402946734561261[105] = 0;
   out_1483402946734561261[106] = 0;
   out_1483402946734561261[107] = 0;
   out_1483402946734561261[108] = 0;
   out_1483402946734561261[109] = 0;
   out_1483402946734561261[110] = 0;
   out_1483402946734561261[111] = 0;
   out_1483402946734561261[112] = 0;
   out_1483402946734561261[113] = 0;
   out_1483402946734561261[114] = 1;
   out_1483402946734561261[115] = 0;
   out_1483402946734561261[116] = 0;
   out_1483402946734561261[117] = 0;
   out_1483402946734561261[118] = 0;
   out_1483402946734561261[119] = 0;
   out_1483402946734561261[120] = 0;
   out_1483402946734561261[121] = 0;
   out_1483402946734561261[122] = 0;
   out_1483402946734561261[123] = 0;
   out_1483402946734561261[124] = 0;
   out_1483402946734561261[125] = 0;
   out_1483402946734561261[126] = 0;
   out_1483402946734561261[127] = 0;
   out_1483402946734561261[128] = 0;
   out_1483402946734561261[129] = 0;
   out_1483402946734561261[130] = 0;
   out_1483402946734561261[131] = 0;
   out_1483402946734561261[132] = 0;
   out_1483402946734561261[133] = 1;
   out_1483402946734561261[134] = 0;
   out_1483402946734561261[135] = 0;
   out_1483402946734561261[136] = 0;
   out_1483402946734561261[137] = 0;
   out_1483402946734561261[138] = 0;
   out_1483402946734561261[139] = 0;
   out_1483402946734561261[140] = 0;
   out_1483402946734561261[141] = 0;
   out_1483402946734561261[142] = 0;
   out_1483402946734561261[143] = 0;
   out_1483402946734561261[144] = 0;
   out_1483402946734561261[145] = 0;
   out_1483402946734561261[146] = 0;
   out_1483402946734561261[147] = 0;
   out_1483402946734561261[148] = 0;
   out_1483402946734561261[149] = 0;
   out_1483402946734561261[150] = 0;
   out_1483402946734561261[151] = 0;
   out_1483402946734561261[152] = 1;
   out_1483402946734561261[153] = 0;
   out_1483402946734561261[154] = 0;
   out_1483402946734561261[155] = 0;
   out_1483402946734561261[156] = 0;
   out_1483402946734561261[157] = 0;
   out_1483402946734561261[158] = 0;
   out_1483402946734561261[159] = 0;
   out_1483402946734561261[160] = 0;
   out_1483402946734561261[161] = 0;
   out_1483402946734561261[162] = 0;
   out_1483402946734561261[163] = 0;
   out_1483402946734561261[164] = 0;
   out_1483402946734561261[165] = 0;
   out_1483402946734561261[166] = 0;
   out_1483402946734561261[167] = 0;
   out_1483402946734561261[168] = 0;
   out_1483402946734561261[169] = 0;
   out_1483402946734561261[170] = 0;
   out_1483402946734561261[171] = 1;
   out_1483402946734561261[172] = 0;
   out_1483402946734561261[173] = 0;
   out_1483402946734561261[174] = 0;
   out_1483402946734561261[175] = 0;
   out_1483402946734561261[176] = 0;
   out_1483402946734561261[177] = 0;
   out_1483402946734561261[178] = 0;
   out_1483402946734561261[179] = 0;
   out_1483402946734561261[180] = 0;
   out_1483402946734561261[181] = 0;
   out_1483402946734561261[182] = 0;
   out_1483402946734561261[183] = 0;
   out_1483402946734561261[184] = 0;
   out_1483402946734561261[185] = 0;
   out_1483402946734561261[186] = 0;
   out_1483402946734561261[187] = 0;
   out_1483402946734561261[188] = 0;
   out_1483402946734561261[189] = 0;
   out_1483402946734561261[190] = 1;
   out_1483402946734561261[191] = 0;
   out_1483402946734561261[192] = 0;
   out_1483402946734561261[193] = 0;
   out_1483402946734561261[194] = 0;
   out_1483402946734561261[195] = 0;
   out_1483402946734561261[196] = 0;
   out_1483402946734561261[197] = 0;
   out_1483402946734561261[198] = 0;
   out_1483402946734561261[199] = 0;
   out_1483402946734561261[200] = 0;
   out_1483402946734561261[201] = 0;
   out_1483402946734561261[202] = 0;
   out_1483402946734561261[203] = 0;
   out_1483402946734561261[204] = 0;
   out_1483402946734561261[205] = 0;
   out_1483402946734561261[206] = 0;
   out_1483402946734561261[207] = 0;
   out_1483402946734561261[208] = 0;
   out_1483402946734561261[209] = 1;
   out_1483402946734561261[210] = 0;
   out_1483402946734561261[211] = 0;
   out_1483402946734561261[212] = 0;
   out_1483402946734561261[213] = 0;
   out_1483402946734561261[214] = 0;
   out_1483402946734561261[215] = 0;
   out_1483402946734561261[216] = 0;
   out_1483402946734561261[217] = 0;
   out_1483402946734561261[218] = 0;
   out_1483402946734561261[219] = 0;
   out_1483402946734561261[220] = 0;
   out_1483402946734561261[221] = 0;
   out_1483402946734561261[222] = 0;
   out_1483402946734561261[223] = 0;
   out_1483402946734561261[224] = 0;
   out_1483402946734561261[225] = 0;
   out_1483402946734561261[226] = 0;
   out_1483402946734561261[227] = 0;
   out_1483402946734561261[228] = 1;
   out_1483402946734561261[229] = 0;
   out_1483402946734561261[230] = 0;
   out_1483402946734561261[231] = 0;
   out_1483402946734561261[232] = 0;
   out_1483402946734561261[233] = 0;
   out_1483402946734561261[234] = 0;
   out_1483402946734561261[235] = 0;
   out_1483402946734561261[236] = 0;
   out_1483402946734561261[237] = 0;
   out_1483402946734561261[238] = 0;
   out_1483402946734561261[239] = 0;
   out_1483402946734561261[240] = 0;
   out_1483402946734561261[241] = 0;
   out_1483402946734561261[242] = 0;
   out_1483402946734561261[243] = 0;
   out_1483402946734561261[244] = 0;
   out_1483402946734561261[245] = 0;
   out_1483402946734561261[246] = 0;
   out_1483402946734561261[247] = 1;
   out_1483402946734561261[248] = 0;
   out_1483402946734561261[249] = 0;
   out_1483402946734561261[250] = 0;
   out_1483402946734561261[251] = 0;
   out_1483402946734561261[252] = 0;
   out_1483402946734561261[253] = 0;
   out_1483402946734561261[254] = 0;
   out_1483402946734561261[255] = 0;
   out_1483402946734561261[256] = 0;
   out_1483402946734561261[257] = 0;
   out_1483402946734561261[258] = 0;
   out_1483402946734561261[259] = 0;
   out_1483402946734561261[260] = 0;
   out_1483402946734561261[261] = 0;
   out_1483402946734561261[262] = 0;
   out_1483402946734561261[263] = 0;
   out_1483402946734561261[264] = 0;
   out_1483402946734561261[265] = 0;
   out_1483402946734561261[266] = 1;
   out_1483402946734561261[267] = 0;
   out_1483402946734561261[268] = 0;
   out_1483402946734561261[269] = 0;
   out_1483402946734561261[270] = 0;
   out_1483402946734561261[271] = 0;
   out_1483402946734561261[272] = 0;
   out_1483402946734561261[273] = 0;
   out_1483402946734561261[274] = 0;
   out_1483402946734561261[275] = 0;
   out_1483402946734561261[276] = 0;
   out_1483402946734561261[277] = 0;
   out_1483402946734561261[278] = 0;
   out_1483402946734561261[279] = 0;
   out_1483402946734561261[280] = 0;
   out_1483402946734561261[281] = 0;
   out_1483402946734561261[282] = 0;
   out_1483402946734561261[283] = 0;
   out_1483402946734561261[284] = 0;
   out_1483402946734561261[285] = 1;
   out_1483402946734561261[286] = 0;
   out_1483402946734561261[287] = 0;
   out_1483402946734561261[288] = 0;
   out_1483402946734561261[289] = 0;
   out_1483402946734561261[290] = 0;
   out_1483402946734561261[291] = 0;
   out_1483402946734561261[292] = 0;
   out_1483402946734561261[293] = 0;
   out_1483402946734561261[294] = 0;
   out_1483402946734561261[295] = 0;
   out_1483402946734561261[296] = 0;
   out_1483402946734561261[297] = 0;
   out_1483402946734561261[298] = 0;
   out_1483402946734561261[299] = 0;
   out_1483402946734561261[300] = 0;
   out_1483402946734561261[301] = 0;
   out_1483402946734561261[302] = 0;
   out_1483402946734561261[303] = 0;
   out_1483402946734561261[304] = 1;
   out_1483402946734561261[305] = 0;
   out_1483402946734561261[306] = 0;
   out_1483402946734561261[307] = 0;
   out_1483402946734561261[308] = 0;
   out_1483402946734561261[309] = 0;
   out_1483402946734561261[310] = 0;
   out_1483402946734561261[311] = 0;
   out_1483402946734561261[312] = 0;
   out_1483402946734561261[313] = 0;
   out_1483402946734561261[314] = 0;
   out_1483402946734561261[315] = 0;
   out_1483402946734561261[316] = 0;
   out_1483402946734561261[317] = 0;
   out_1483402946734561261[318] = 0;
   out_1483402946734561261[319] = 0;
   out_1483402946734561261[320] = 0;
   out_1483402946734561261[321] = 0;
   out_1483402946734561261[322] = 0;
   out_1483402946734561261[323] = 1;
}
void h_4(double *state, double *unused, double *out_7341531725789403251) {
   out_7341531725789403251[0] = state[6] + state[9];
   out_7341531725789403251[1] = state[7] + state[10];
   out_7341531725789403251[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8688726853893880498) {
   out_8688726853893880498[0] = 0;
   out_8688726853893880498[1] = 0;
   out_8688726853893880498[2] = 0;
   out_8688726853893880498[3] = 0;
   out_8688726853893880498[4] = 0;
   out_8688726853893880498[5] = 0;
   out_8688726853893880498[6] = 1;
   out_8688726853893880498[7] = 0;
   out_8688726853893880498[8] = 0;
   out_8688726853893880498[9] = 1;
   out_8688726853893880498[10] = 0;
   out_8688726853893880498[11] = 0;
   out_8688726853893880498[12] = 0;
   out_8688726853893880498[13] = 0;
   out_8688726853893880498[14] = 0;
   out_8688726853893880498[15] = 0;
   out_8688726853893880498[16] = 0;
   out_8688726853893880498[17] = 0;
   out_8688726853893880498[18] = 0;
   out_8688726853893880498[19] = 0;
   out_8688726853893880498[20] = 0;
   out_8688726853893880498[21] = 0;
   out_8688726853893880498[22] = 0;
   out_8688726853893880498[23] = 0;
   out_8688726853893880498[24] = 0;
   out_8688726853893880498[25] = 1;
   out_8688726853893880498[26] = 0;
   out_8688726853893880498[27] = 0;
   out_8688726853893880498[28] = 1;
   out_8688726853893880498[29] = 0;
   out_8688726853893880498[30] = 0;
   out_8688726853893880498[31] = 0;
   out_8688726853893880498[32] = 0;
   out_8688726853893880498[33] = 0;
   out_8688726853893880498[34] = 0;
   out_8688726853893880498[35] = 0;
   out_8688726853893880498[36] = 0;
   out_8688726853893880498[37] = 0;
   out_8688726853893880498[38] = 0;
   out_8688726853893880498[39] = 0;
   out_8688726853893880498[40] = 0;
   out_8688726853893880498[41] = 0;
   out_8688726853893880498[42] = 0;
   out_8688726853893880498[43] = 0;
   out_8688726853893880498[44] = 1;
   out_8688726853893880498[45] = 0;
   out_8688726853893880498[46] = 0;
   out_8688726853893880498[47] = 1;
   out_8688726853893880498[48] = 0;
   out_8688726853893880498[49] = 0;
   out_8688726853893880498[50] = 0;
   out_8688726853893880498[51] = 0;
   out_8688726853893880498[52] = 0;
   out_8688726853893880498[53] = 0;
}
void h_10(double *state, double *unused, double *out_7465669924192065255) {
   out_7465669924192065255[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7465669924192065255[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7465669924192065255[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3170804055885360208) {
   out_3170804055885360208[0] = 0;
   out_3170804055885360208[1] = 9.8100000000000005*cos(state[1]);
   out_3170804055885360208[2] = 0;
   out_3170804055885360208[3] = 0;
   out_3170804055885360208[4] = -state[8];
   out_3170804055885360208[5] = state[7];
   out_3170804055885360208[6] = 0;
   out_3170804055885360208[7] = state[5];
   out_3170804055885360208[8] = -state[4];
   out_3170804055885360208[9] = 0;
   out_3170804055885360208[10] = 0;
   out_3170804055885360208[11] = 0;
   out_3170804055885360208[12] = 1;
   out_3170804055885360208[13] = 0;
   out_3170804055885360208[14] = 0;
   out_3170804055885360208[15] = 1;
   out_3170804055885360208[16] = 0;
   out_3170804055885360208[17] = 0;
   out_3170804055885360208[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3170804055885360208[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3170804055885360208[20] = 0;
   out_3170804055885360208[21] = state[8];
   out_3170804055885360208[22] = 0;
   out_3170804055885360208[23] = -state[6];
   out_3170804055885360208[24] = -state[5];
   out_3170804055885360208[25] = 0;
   out_3170804055885360208[26] = state[3];
   out_3170804055885360208[27] = 0;
   out_3170804055885360208[28] = 0;
   out_3170804055885360208[29] = 0;
   out_3170804055885360208[30] = 0;
   out_3170804055885360208[31] = 1;
   out_3170804055885360208[32] = 0;
   out_3170804055885360208[33] = 0;
   out_3170804055885360208[34] = 1;
   out_3170804055885360208[35] = 0;
   out_3170804055885360208[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3170804055885360208[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3170804055885360208[38] = 0;
   out_3170804055885360208[39] = -state[7];
   out_3170804055885360208[40] = state[6];
   out_3170804055885360208[41] = 0;
   out_3170804055885360208[42] = state[4];
   out_3170804055885360208[43] = -state[3];
   out_3170804055885360208[44] = 0;
   out_3170804055885360208[45] = 0;
   out_3170804055885360208[46] = 0;
   out_3170804055885360208[47] = 0;
   out_3170804055885360208[48] = 0;
   out_3170804055885360208[49] = 0;
   out_3170804055885360208[50] = 1;
   out_3170804055885360208[51] = 0;
   out_3170804055885360208[52] = 0;
   out_3170804055885360208[53] = 1;
}
void h_13(double *state, double *unused, double *out_1303405934408792496) {
   out_1303405934408792496[0] = state[3];
   out_1303405934408792496[1] = state[4];
   out_1303405934408792496[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5476453028561547697) {
   out_5476453028561547697[0] = 0;
   out_5476453028561547697[1] = 0;
   out_5476453028561547697[2] = 0;
   out_5476453028561547697[3] = 1;
   out_5476453028561547697[4] = 0;
   out_5476453028561547697[5] = 0;
   out_5476453028561547697[6] = 0;
   out_5476453028561547697[7] = 0;
   out_5476453028561547697[8] = 0;
   out_5476453028561547697[9] = 0;
   out_5476453028561547697[10] = 0;
   out_5476453028561547697[11] = 0;
   out_5476453028561547697[12] = 0;
   out_5476453028561547697[13] = 0;
   out_5476453028561547697[14] = 0;
   out_5476453028561547697[15] = 0;
   out_5476453028561547697[16] = 0;
   out_5476453028561547697[17] = 0;
   out_5476453028561547697[18] = 0;
   out_5476453028561547697[19] = 0;
   out_5476453028561547697[20] = 0;
   out_5476453028561547697[21] = 0;
   out_5476453028561547697[22] = 1;
   out_5476453028561547697[23] = 0;
   out_5476453028561547697[24] = 0;
   out_5476453028561547697[25] = 0;
   out_5476453028561547697[26] = 0;
   out_5476453028561547697[27] = 0;
   out_5476453028561547697[28] = 0;
   out_5476453028561547697[29] = 0;
   out_5476453028561547697[30] = 0;
   out_5476453028561547697[31] = 0;
   out_5476453028561547697[32] = 0;
   out_5476453028561547697[33] = 0;
   out_5476453028561547697[34] = 0;
   out_5476453028561547697[35] = 0;
   out_5476453028561547697[36] = 0;
   out_5476453028561547697[37] = 0;
   out_5476453028561547697[38] = 0;
   out_5476453028561547697[39] = 0;
   out_5476453028561547697[40] = 0;
   out_5476453028561547697[41] = 1;
   out_5476453028561547697[42] = 0;
   out_5476453028561547697[43] = 0;
   out_5476453028561547697[44] = 0;
   out_5476453028561547697[45] = 0;
   out_5476453028561547697[46] = 0;
   out_5476453028561547697[47] = 0;
   out_5476453028561547697[48] = 0;
   out_5476453028561547697[49] = 0;
   out_5476453028561547697[50] = 0;
   out_5476453028561547697[51] = 0;
   out_5476453028561547697[52] = 0;
   out_5476453028561547697[53] = 0;
}
void h_14(double *state, double *unused, double *out_8059879594466194155) {
   out_8059879594466194155[0] = state[6];
   out_8059879594466194155[1] = state[7];
   out_8059879594466194155[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6675228787520298822) {
   out_6675228787520298822[0] = 0;
   out_6675228787520298822[1] = 0;
   out_6675228787520298822[2] = 0;
   out_6675228787520298822[3] = 0;
   out_6675228787520298822[4] = 0;
   out_6675228787520298822[5] = 0;
   out_6675228787520298822[6] = 1;
   out_6675228787520298822[7] = 0;
   out_6675228787520298822[8] = 0;
   out_6675228787520298822[9] = 0;
   out_6675228787520298822[10] = 0;
   out_6675228787520298822[11] = 0;
   out_6675228787520298822[12] = 0;
   out_6675228787520298822[13] = 0;
   out_6675228787520298822[14] = 0;
   out_6675228787520298822[15] = 0;
   out_6675228787520298822[16] = 0;
   out_6675228787520298822[17] = 0;
   out_6675228787520298822[18] = 0;
   out_6675228787520298822[19] = 0;
   out_6675228787520298822[20] = 0;
   out_6675228787520298822[21] = 0;
   out_6675228787520298822[22] = 0;
   out_6675228787520298822[23] = 0;
   out_6675228787520298822[24] = 0;
   out_6675228787520298822[25] = 1;
   out_6675228787520298822[26] = 0;
   out_6675228787520298822[27] = 0;
   out_6675228787520298822[28] = 0;
   out_6675228787520298822[29] = 0;
   out_6675228787520298822[30] = 0;
   out_6675228787520298822[31] = 0;
   out_6675228787520298822[32] = 0;
   out_6675228787520298822[33] = 0;
   out_6675228787520298822[34] = 0;
   out_6675228787520298822[35] = 0;
   out_6675228787520298822[36] = 0;
   out_6675228787520298822[37] = 0;
   out_6675228787520298822[38] = 0;
   out_6675228787520298822[39] = 0;
   out_6675228787520298822[40] = 0;
   out_6675228787520298822[41] = 0;
   out_6675228787520298822[42] = 0;
   out_6675228787520298822[43] = 0;
   out_6675228787520298822[44] = 1;
   out_6675228787520298822[45] = 0;
   out_6675228787520298822[46] = 0;
   out_6675228787520298822[47] = 0;
   out_6675228787520298822[48] = 0;
   out_6675228787520298822[49] = 0;
   out_6675228787520298822[50] = 0;
   out_6675228787520298822[51] = 0;
   out_6675228787520298822[52] = 0;
   out_6675228787520298822[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5133309144223277572) {
  err_fun(nom_x, delta_x, out_5133309144223277572);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6881212781704972929) {
  inv_err_fun(nom_x, true_x, out_6881212781704972929);
}
void pose_H_mod_fun(double *state, double *out_6869028127987583637) {
  H_mod_fun(state, out_6869028127987583637);
}
void pose_f_fun(double *state, double dt, double *out_8902612319160798640) {
  f_fun(state,  dt, out_8902612319160798640);
}
void pose_F_fun(double *state, double dt, double *out_1483402946734561261) {
  F_fun(state,  dt, out_1483402946734561261);
}
void pose_h_4(double *state, double *unused, double *out_7341531725789403251) {
  h_4(state, unused, out_7341531725789403251);
}
void pose_H_4(double *state, double *unused, double *out_8688726853893880498) {
  H_4(state, unused, out_8688726853893880498);
}
void pose_h_10(double *state, double *unused, double *out_7465669924192065255) {
  h_10(state, unused, out_7465669924192065255);
}
void pose_H_10(double *state, double *unused, double *out_3170804055885360208) {
  H_10(state, unused, out_3170804055885360208);
}
void pose_h_13(double *state, double *unused, double *out_1303405934408792496) {
  h_13(state, unused, out_1303405934408792496);
}
void pose_H_13(double *state, double *unused, double *out_5476453028561547697) {
  H_13(state, unused, out_5476453028561547697);
}
void pose_h_14(double *state, double *unused, double *out_8059879594466194155) {
  h_14(state, unused, out_8059879594466194155);
}
void pose_H_14(double *state, double *unused, double *out_6675228787520298822) {
  H_14(state, unused, out_6675228787520298822);
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
