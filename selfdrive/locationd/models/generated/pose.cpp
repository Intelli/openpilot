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
void err_fun(double *nom_x, double *delta_x, double *out_5899152602515428793) {
   out_5899152602515428793[0] = delta_x[0] + nom_x[0];
   out_5899152602515428793[1] = delta_x[1] + nom_x[1];
   out_5899152602515428793[2] = delta_x[2] + nom_x[2];
   out_5899152602515428793[3] = delta_x[3] + nom_x[3];
   out_5899152602515428793[4] = delta_x[4] + nom_x[4];
   out_5899152602515428793[5] = delta_x[5] + nom_x[5];
   out_5899152602515428793[6] = delta_x[6] + nom_x[6];
   out_5899152602515428793[7] = delta_x[7] + nom_x[7];
   out_5899152602515428793[8] = delta_x[8] + nom_x[8];
   out_5899152602515428793[9] = delta_x[9] + nom_x[9];
   out_5899152602515428793[10] = delta_x[10] + nom_x[10];
   out_5899152602515428793[11] = delta_x[11] + nom_x[11];
   out_5899152602515428793[12] = delta_x[12] + nom_x[12];
   out_5899152602515428793[13] = delta_x[13] + nom_x[13];
   out_5899152602515428793[14] = delta_x[14] + nom_x[14];
   out_5899152602515428793[15] = delta_x[15] + nom_x[15];
   out_5899152602515428793[16] = delta_x[16] + nom_x[16];
   out_5899152602515428793[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1853168426912981794) {
   out_1853168426912981794[0] = -nom_x[0] + true_x[0];
   out_1853168426912981794[1] = -nom_x[1] + true_x[1];
   out_1853168426912981794[2] = -nom_x[2] + true_x[2];
   out_1853168426912981794[3] = -nom_x[3] + true_x[3];
   out_1853168426912981794[4] = -nom_x[4] + true_x[4];
   out_1853168426912981794[5] = -nom_x[5] + true_x[5];
   out_1853168426912981794[6] = -nom_x[6] + true_x[6];
   out_1853168426912981794[7] = -nom_x[7] + true_x[7];
   out_1853168426912981794[8] = -nom_x[8] + true_x[8];
   out_1853168426912981794[9] = -nom_x[9] + true_x[9];
   out_1853168426912981794[10] = -nom_x[10] + true_x[10];
   out_1853168426912981794[11] = -nom_x[11] + true_x[11];
   out_1853168426912981794[12] = -nom_x[12] + true_x[12];
   out_1853168426912981794[13] = -nom_x[13] + true_x[13];
   out_1853168426912981794[14] = -nom_x[14] + true_x[14];
   out_1853168426912981794[15] = -nom_x[15] + true_x[15];
   out_1853168426912981794[16] = -nom_x[16] + true_x[16];
   out_1853168426912981794[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4126833233538436701) {
   out_4126833233538436701[0] = 1.0;
   out_4126833233538436701[1] = 0.0;
   out_4126833233538436701[2] = 0.0;
   out_4126833233538436701[3] = 0.0;
   out_4126833233538436701[4] = 0.0;
   out_4126833233538436701[5] = 0.0;
   out_4126833233538436701[6] = 0.0;
   out_4126833233538436701[7] = 0.0;
   out_4126833233538436701[8] = 0.0;
   out_4126833233538436701[9] = 0.0;
   out_4126833233538436701[10] = 0.0;
   out_4126833233538436701[11] = 0.0;
   out_4126833233538436701[12] = 0.0;
   out_4126833233538436701[13] = 0.0;
   out_4126833233538436701[14] = 0.0;
   out_4126833233538436701[15] = 0.0;
   out_4126833233538436701[16] = 0.0;
   out_4126833233538436701[17] = 0.0;
   out_4126833233538436701[18] = 0.0;
   out_4126833233538436701[19] = 1.0;
   out_4126833233538436701[20] = 0.0;
   out_4126833233538436701[21] = 0.0;
   out_4126833233538436701[22] = 0.0;
   out_4126833233538436701[23] = 0.0;
   out_4126833233538436701[24] = 0.0;
   out_4126833233538436701[25] = 0.0;
   out_4126833233538436701[26] = 0.0;
   out_4126833233538436701[27] = 0.0;
   out_4126833233538436701[28] = 0.0;
   out_4126833233538436701[29] = 0.0;
   out_4126833233538436701[30] = 0.0;
   out_4126833233538436701[31] = 0.0;
   out_4126833233538436701[32] = 0.0;
   out_4126833233538436701[33] = 0.0;
   out_4126833233538436701[34] = 0.0;
   out_4126833233538436701[35] = 0.0;
   out_4126833233538436701[36] = 0.0;
   out_4126833233538436701[37] = 0.0;
   out_4126833233538436701[38] = 1.0;
   out_4126833233538436701[39] = 0.0;
   out_4126833233538436701[40] = 0.0;
   out_4126833233538436701[41] = 0.0;
   out_4126833233538436701[42] = 0.0;
   out_4126833233538436701[43] = 0.0;
   out_4126833233538436701[44] = 0.0;
   out_4126833233538436701[45] = 0.0;
   out_4126833233538436701[46] = 0.0;
   out_4126833233538436701[47] = 0.0;
   out_4126833233538436701[48] = 0.0;
   out_4126833233538436701[49] = 0.0;
   out_4126833233538436701[50] = 0.0;
   out_4126833233538436701[51] = 0.0;
   out_4126833233538436701[52] = 0.0;
   out_4126833233538436701[53] = 0.0;
   out_4126833233538436701[54] = 0.0;
   out_4126833233538436701[55] = 0.0;
   out_4126833233538436701[56] = 0.0;
   out_4126833233538436701[57] = 1.0;
   out_4126833233538436701[58] = 0.0;
   out_4126833233538436701[59] = 0.0;
   out_4126833233538436701[60] = 0.0;
   out_4126833233538436701[61] = 0.0;
   out_4126833233538436701[62] = 0.0;
   out_4126833233538436701[63] = 0.0;
   out_4126833233538436701[64] = 0.0;
   out_4126833233538436701[65] = 0.0;
   out_4126833233538436701[66] = 0.0;
   out_4126833233538436701[67] = 0.0;
   out_4126833233538436701[68] = 0.0;
   out_4126833233538436701[69] = 0.0;
   out_4126833233538436701[70] = 0.0;
   out_4126833233538436701[71] = 0.0;
   out_4126833233538436701[72] = 0.0;
   out_4126833233538436701[73] = 0.0;
   out_4126833233538436701[74] = 0.0;
   out_4126833233538436701[75] = 0.0;
   out_4126833233538436701[76] = 1.0;
   out_4126833233538436701[77] = 0.0;
   out_4126833233538436701[78] = 0.0;
   out_4126833233538436701[79] = 0.0;
   out_4126833233538436701[80] = 0.0;
   out_4126833233538436701[81] = 0.0;
   out_4126833233538436701[82] = 0.0;
   out_4126833233538436701[83] = 0.0;
   out_4126833233538436701[84] = 0.0;
   out_4126833233538436701[85] = 0.0;
   out_4126833233538436701[86] = 0.0;
   out_4126833233538436701[87] = 0.0;
   out_4126833233538436701[88] = 0.0;
   out_4126833233538436701[89] = 0.0;
   out_4126833233538436701[90] = 0.0;
   out_4126833233538436701[91] = 0.0;
   out_4126833233538436701[92] = 0.0;
   out_4126833233538436701[93] = 0.0;
   out_4126833233538436701[94] = 0.0;
   out_4126833233538436701[95] = 1.0;
   out_4126833233538436701[96] = 0.0;
   out_4126833233538436701[97] = 0.0;
   out_4126833233538436701[98] = 0.0;
   out_4126833233538436701[99] = 0.0;
   out_4126833233538436701[100] = 0.0;
   out_4126833233538436701[101] = 0.0;
   out_4126833233538436701[102] = 0.0;
   out_4126833233538436701[103] = 0.0;
   out_4126833233538436701[104] = 0.0;
   out_4126833233538436701[105] = 0.0;
   out_4126833233538436701[106] = 0.0;
   out_4126833233538436701[107] = 0.0;
   out_4126833233538436701[108] = 0.0;
   out_4126833233538436701[109] = 0.0;
   out_4126833233538436701[110] = 0.0;
   out_4126833233538436701[111] = 0.0;
   out_4126833233538436701[112] = 0.0;
   out_4126833233538436701[113] = 0.0;
   out_4126833233538436701[114] = 1.0;
   out_4126833233538436701[115] = 0.0;
   out_4126833233538436701[116] = 0.0;
   out_4126833233538436701[117] = 0.0;
   out_4126833233538436701[118] = 0.0;
   out_4126833233538436701[119] = 0.0;
   out_4126833233538436701[120] = 0.0;
   out_4126833233538436701[121] = 0.0;
   out_4126833233538436701[122] = 0.0;
   out_4126833233538436701[123] = 0.0;
   out_4126833233538436701[124] = 0.0;
   out_4126833233538436701[125] = 0.0;
   out_4126833233538436701[126] = 0.0;
   out_4126833233538436701[127] = 0.0;
   out_4126833233538436701[128] = 0.0;
   out_4126833233538436701[129] = 0.0;
   out_4126833233538436701[130] = 0.0;
   out_4126833233538436701[131] = 0.0;
   out_4126833233538436701[132] = 0.0;
   out_4126833233538436701[133] = 1.0;
   out_4126833233538436701[134] = 0.0;
   out_4126833233538436701[135] = 0.0;
   out_4126833233538436701[136] = 0.0;
   out_4126833233538436701[137] = 0.0;
   out_4126833233538436701[138] = 0.0;
   out_4126833233538436701[139] = 0.0;
   out_4126833233538436701[140] = 0.0;
   out_4126833233538436701[141] = 0.0;
   out_4126833233538436701[142] = 0.0;
   out_4126833233538436701[143] = 0.0;
   out_4126833233538436701[144] = 0.0;
   out_4126833233538436701[145] = 0.0;
   out_4126833233538436701[146] = 0.0;
   out_4126833233538436701[147] = 0.0;
   out_4126833233538436701[148] = 0.0;
   out_4126833233538436701[149] = 0.0;
   out_4126833233538436701[150] = 0.0;
   out_4126833233538436701[151] = 0.0;
   out_4126833233538436701[152] = 1.0;
   out_4126833233538436701[153] = 0.0;
   out_4126833233538436701[154] = 0.0;
   out_4126833233538436701[155] = 0.0;
   out_4126833233538436701[156] = 0.0;
   out_4126833233538436701[157] = 0.0;
   out_4126833233538436701[158] = 0.0;
   out_4126833233538436701[159] = 0.0;
   out_4126833233538436701[160] = 0.0;
   out_4126833233538436701[161] = 0.0;
   out_4126833233538436701[162] = 0.0;
   out_4126833233538436701[163] = 0.0;
   out_4126833233538436701[164] = 0.0;
   out_4126833233538436701[165] = 0.0;
   out_4126833233538436701[166] = 0.0;
   out_4126833233538436701[167] = 0.0;
   out_4126833233538436701[168] = 0.0;
   out_4126833233538436701[169] = 0.0;
   out_4126833233538436701[170] = 0.0;
   out_4126833233538436701[171] = 1.0;
   out_4126833233538436701[172] = 0.0;
   out_4126833233538436701[173] = 0.0;
   out_4126833233538436701[174] = 0.0;
   out_4126833233538436701[175] = 0.0;
   out_4126833233538436701[176] = 0.0;
   out_4126833233538436701[177] = 0.0;
   out_4126833233538436701[178] = 0.0;
   out_4126833233538436701[179] = 0.0;
   out_4126833233538436701[180] = 0.0;
   out_4126833233538436701[181] = 0.0;
   out_4126833233538436701[182] = 0.0;
   out_4126833233538436701[183] = 0.0;
   out_4126833233538436701[184] = 0.0;
   out_4126833233538436701[185] = 0.0;
   out_4126833233538436701[186] = 0.0;
   out_4126833233538436701[187] = 0.0;
   out_4126833233538436701[188] = 0.0;
   out_4126833233538436701[189] = 0.0;
   out_4126833233538436701[190] = 1.0;
   out_4126833233538436701[191] = 0.0;
   out_4126833233538436701[192] = 0.0;
   out_4126833233538436701[193] = 0.0;
   out_4126833233538436701[194] = 0.0;
   out_4126833233538436701[195] = 0.0;
   out_4126833233538436701[196] = 0.0;
   out_4126833233538436701[197] = 0.0;
   out_4126833233538436701[198] = 0.0;
   out_4126833233538436701[199] = 0.0;
   out_4126833233538436701[200] = 0.0;
   out_4126833233538436701[201] = 0.0;
   out_4126833233538436701[202] = 0.0;
   out_4126833233538436701[203] = 0.0;
   out_4126833233538436701[204] = 0.0;
   out_4126833233538436701[205] = 0.0;
   out_4126833233538436701[206] = 0.0;
   out_4126833233538436701[207] = 0.0;
   out_4126833233538436701[208] = 0.0;
   out_4126833233538436701[209] = 1.0;
   out_4126833233538436701[210] = 0.0;
   out_4126833233538436701[211] = 0.0;
   out_4126833233538436701[212] = 0.0;
   out_4126833233538436701[213] = 0.0;
   out_4126833233538436701[214] = 0.0;
   out_4126833233538436701[215] = 0.0;
   out_4126833233538436701[216] = 0.0;
   out_4126833233538436701[217] = 0.0;
   out_4126833233538436701[218] = 0.0;
   out_4126833233538436701[219] = 0.0;
   out_4126833233538436701[220] = 0.0;
   out_4126833233538436701[221] = 0.0;
   out_4126833233538436701[222] = 0.0;
   out_4126833233538436701[223] = 0.0;
   out_4126833233538436701[224] = 0.0;
   out_4126833233538436701[225] = 0.0;
   out_4126833233538436701[226] = 0.0;
   out_4126833233538436701[227] = 0.0;
   out_4126833233538436701[228] = 1.0;
   out_4126833233538436701[229] = 0.0;
   out_4126833233538436701[230] = 0.0;
   out_4126833233538436701[231] = 0.0;
   out_4126833233538436701[232] = 0.0;
   out_4126833233538436701[233] = 0.0;
   out_4126833233538436701[234] = 0.0;
   out_4126833233538436701[235] = 0.0;
   out_4126833233538436701[236] = 0.0;
   out_4126833233538436701[237] = 0.0;
   out_4126833233538436701[238] = 0.0;
   out_4126833233538436701[239] = 0.0;
   out_4126833233538436701[240] = 0.0;
   out_4126833233538436701[241] = 0.0;
   out_4126833233538436701[242] = 0.0;
   out_4126833233538436701[243] = 0.0;
   out_4126833233538436701[244] = 0.0;
   out_4126833233538436701[245] = 0.0;
   out_4126833233538436701[246] = 0.0;
   out_4126833233538436701[247] = 1.0;
   out_4126833233538436701[248] = 0.0;
   out_4126833233538436701[249] = 0.0;
   out_4126833233538436701[250] = 0.0;
   out_4126833233538436701[251] = 0.0;
   out_4126833233538436701[252] = 0.0;
   out_4126833233538436701[253] = 0.0;
   out_4126833233538436701[254] = 0.0;
   out_4126833233538436701[255] = 0.0;
   out_4126833233538436701[256] = 0.0;
   out_4126833233538436701[257] = 0.0;
   out_4126833233538436701[258] = 0.0;
   out_4126833233538436701[259] = 0.0;
   out_4126833233538436701[260] = 0.0;
   out_4126833233538436701[261] = 0.0;
   out_4126833233538436701[262] = 0.0;
   out_4126833233538436701[263] = 0.0;
   out_4126833233538436701[264] = 0.0;
   out_4126833233538436701[265] = 0.0;
   out_4126833233538436701[266] = 1.0;
   out_4126833233538436701[267] = 0.0;
   out_4126833233538436701[268] = 0.0;
   out_4126833233538436701[269] = 0.0;
   out_4126833233538436701[270] = 0.0;
   out_4126833233538436701[271] = 0.0;
   out_4126833233538436701[272] = 0.0;
   out_4126833233538436701[273] = 0.0;
   out_4126833233538436701[274] = 0.0;
   out_4126833233538436701[275] = 0.0;
   out_4126833233538436701[276] = 0.0;
   out_4126833233538436701[277] = 0.0;
   out_4126833233538436701[278] = 0.0;
   out_4126833233538436701[279] = 0.0;
   out_4126833233538436701[280] = 0.0;
   out_4126833233538436701[281] = 0.0;
   out_4126833233538436701[282] = 0.0;
   out_4126833233538436701[283] = 0.0;
   out_4126833233538436701[284] = 0.0;
   out_4126833233538436701[285] = 1.0;
   out_4126833233538436701[286] = 0.0;
   out_4126833233538436701[287] = 0.0;
   out_4126833233538436701[288] = 0.0;
   out_4126833233538436701[289] = 0.0;
   out_4126833233538436701[290] = 0.0;
   out_4126833233538436701[291] = 0.0;
   out_4126833233538436701[292] = 0.0;
   out_4126833233538436701[293] = 0.0;
   out_4126833233538436701[294] = 0.0;
   out_4126833233538436701[295] = 0.0;
   out_4126833233538436701[296] = 0.0;
   out_4126833233538436701[297] = 0.0;
   out_4126833233538436701[298] = 0.0;
   out_4126833233538436701[299] = 0.0;
   out_4126833233538436701[300] = 0.0;
   out_4126833233538436701[301] = 0.0;
   out_4126833233538436701[302] = 0.0;
   out_4126833233538436701[303] = 0.0;
   out_4126833233538436701[304] = 1.0;
   out_4126833233538436701[305] = 0.0;
   out_4126833233538436701[306] = 0.0;
   out_4126833233538436701[307] = 0.0;
   out_4126833233538436701[308] = 0.0;
   out_4126833233538436701[309] = 0.0;
   out_4126833233538436701[310] = 0.0;
   out_4126833233538436701[311] = 0.0;
   out_4126833233538436701[312] = 0.0;
   out_4126833233538436701[313] = 0.0;
   out_4126833233538436701[314] = 0.0;
   out_4126833233538436701[315] = 0.0;
   out_4126833233538436701[316] = 0.0;
   out_4126833233538436701[317] = 0.0;
   out_4126833233538436701[318] = 0.0;
   out_4126833233538436701[319] = 0.0;
   out_4126833233538436701[320] = 0.0;
   out_4126833233538436701[321] = 0.0;
   out_4126833233538436701[322] = 0.0;
   out_4126833233538436701[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4790836135548827488) {
   out_4790836135548827488[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4790836135548827488[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4790836135548827488[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4790836135548827488[3] = dt*state[12] + state[3];
   out_4790836135548827488[4] = dt*state[13] + state[4];
   out_4790836135548827488[5] = dt*state[14] + state[5];
   out_4790836135548827488[6] = state[6];
   out_4790836135548827488[7] = state[7];
   out_4790836135548827488[8] = state[8];
   out_4790836135548827488[9] = state[9];
   out_4790836135548827488[10] = state[10];
   out_4790836135548827488[11] = state[11];
   out_4790836135548827488[12] = state[12];
   out_4790836135548827488[13] = state[13];
   out_4790836135548827488[14] = state[14];
   out_4790836135548827488[15] = state[15];
   out_4790836135548827488[16] = state[16];
   out_4790836135548827488[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8482055114076347653) {
   out_8482055114076347653[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8482055114076347653[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8482055114076347653[2] = 0;
   out_8482055114076347653[3] = 0;
   out_8482055114076347653[4] = 0;
   out_8482055114076347653[5] = 0;
   out_8482055114076347653[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8482055114076347653[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8482055114076347653[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8482055114076347653[9] = 0;
   out_8482055114076347653[10] = 0;
   out_8482055114076347653[11] = 0;
   out_8482055114076347653[12] = 0;
   out_8482055114076347653[13] = 0;
   out_8482055114076347653[14] = 0;
   out_8482055114076347653[15] = 0;
   out_8482055114076347653[16] = 0;
   out_8482055114076347653[17] = 0;
   out_8482055114076347653[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8482055114076347653[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8482055114076347653[20] = 0;
   out_8482055114076347653[21] = 0;
   out_8482055114076347653[22] = 0;
   out_8482055114076347653[23] = 0;
   out_8482055114076347653[24] = 0;
   out_8482055114076347653[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8482055114076347653[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8482055114076347653[27] = 0;
   out_8482055114076347653[28] = 0;
   out_8482055114076347653[29] = 0;
   out_8482055114076347653[30] = 0;
   out_8482055114076347653[31] = 0;
   out_8482055114076347653[32] = 0;
   out_8482055114076347653[33] = 0;
   out_8482055114076347653[34] = 0;
   out_8482055114076347653[35] = 0;
   out_8482055114076347653[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8482055114076347653[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8482055114076347653[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8482055114076347653[39] = 0;
   out_8482055114076347653[40] = 0;
   out_8482055114076347653[41] = 0;
   out_8482055114076347653[42] = 0;
   out_8482055114076347653[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8482055114076347653[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8482055114076347653[45] = 0;
   out_8482055114076347653[46] = 0;
   out_8482055114076347653[47] = 0;
   out_8482055114076347653[48] = 0;
   out_8482055114076347653[49] = 0;
   out_8482055114076347653[50] = 0;
   out_8482055114076347653[51] = 0;
   out_8482055114076347653[52] = 0;
   out_8482055114076347653[53] = 0;
   out_8482055114076347653[54] = 0;
   out_8482055114076347653[55] = 0;
   out_8482055114076347653[56] = 0;
   out_8482055114076347653[57] = 1;
   out_8482055114076347653[58] = 0;
   out_8482055114076347653[59] = 0;
   out_8482055114076347653[60] = 0;
   out_8482055114076347653[61] = 0;
   out_8482055114076347653[62] = 0;
   out_8482055114076347653[63] = 0;
   out_8482055114076347653[64] = 0;
   out_8482055114076347653[65] = 0;
   out_8482055114076347653[66] = dt;
   out_8482055114076347653[67] = 0;
   out_8482055114076347653[68] = 0;
   out_8482055114076347653[69] = 0;
   out_8482055114076347653[70] = 0;
   out_8482055114076347653[71] = 0;
   out_8482055114076347653[72] = 0;
   out_8482055114076347653[73] = 0;
   out_8482055114076347653[74] = 0;
   out_8482055114076347653[75] = 0;
   out_8482055114076347653[76] = 1;
   out_8482055114076347653[77] = 0;
   out_8482055114076347653[78] = 0;
   out_8482055114076347653[79] = 0;
   out_8482055114076347653[80] = 0;
   out_8482055114076347653[81] = 0;
   out_8482055114076347653[82] = 0;
   out_8482055114076347653[83] = 0;
   out_8482055114076347653[84] = 0;
   out_8482055114076347653[85] = dt;
   out_8482055114076347653[86] = 0;
   out_8482055114076347653[87] = 0;
   out_8482055114076347653[88] = 0;
   out_8482055114076347653[89] = 0;
   out_8482055114076347653[90] = 0;
   out_8482055114076347653[91] = 0;
   out_8482055114076347653[92] = 0;
   out_8482055114076347653[93] = 0;
   out_8482055114076347653[94] = 0;
   out_8482055114076347653[95] = 1;
   out_8482055114076347653[96] = 0;
   out_8482055114076347653[97] = 0;
   out_8482055114076347653[98] = 0;
   out_8482055114076347653[99] = 0;
   out_8482055114076347653[100] = 0;
   out_8482055114076347653[101] = 0;
   out_8482055114076347653[102] = 0;
   out_8482055114076347653[103] = 0;
   out_8482055114076347653[104] = dt;
   out_8482055114076347653[105] = 0;
   out_8482055114076347653[106] = 0;
   out_8482055114076347653[107] = 0;
   out_8482055114076347653[108] = 0;
   out_8482055114076347653[109] = 0;
   out_8482055114076347653[110] = 0;
   out_8482055114076347653[111] = 0;
   out_8482055114076347653[112] = 0;
   out_8482055114076347653[113] = 0;
   out_8482055114076347653[114] = 1;
   out_8482055114076347653[115] = 0;
   out_8482055114076347653[116] = 0;
   out_8482055114076347653[117] = 0;
   out_8482055114076347653[118] = 0;
   out_8482055114076347653[119] = 0;
   out_8482055114076347653[120] = 0;
   out_8482055114076347653[121] = 0;
   out_8482055114076347653[122] = 0;
   out_8482055114076347653[123] = 0;
   out_8482055114076347653[124] = 0;
   out_8482055114076347653[125] = 0;
   out_8482055114076347653[126] = 0;
   out_8482055114076347653[127] = 0;
   out_8482055114076347653[128] = 0;
   out_8482055114076347653[129] = 0;
   out_8482055114076347653[130] = 0;
   out_8482055114076347653[131] = 0;
   out_8482055114076347653[132] = 0;
   out_8482055114076347653[133] = 1;
   out_8482055114076347653[134] = 0;
   out_8482055114076347653[135] = 0;
   out_8482055114076347653[136] = 0;
   out_8482055114076347653[137] = 0;
   out_8482055114076347653[138] = 0;
   out_8482055114076347653[139] = 0;
   out_8482055114076347653[140] = 0;
   out_8482055114076347653[141] = 0;
   out_8482055114076347653[142] = 0;
   out_8482055114076347653[143] = 0;
   out_8482055114076347653[144] = 0;
   out_8482055114076347653[145] = 0;
   out_8482055114076347653[146] = 0;
   out_8482055114076347653[147] = 0;
   out_8482055114076347653[148] = 0;
   out_8482055114076347653[149] = 0;
   out_8482055114076347653[150] = 0;
   out_8482055114076347653[151] = 0;
   out_8482055114076347653[152] = 1;
   out_8482055114076347653[153] = 0;
   out_8482055114076347653[154] = 0;
   out_8482055114076347653[155] = 0;
   out_8482055114076347653[156] = 0;
   out_8482055114076347653[157] = 0;
   out_8482055114076347653[158] = 0;
   out_8482055114076347653[159] = 0;
   out_8482055114076347653[160] = 0;
   out_8482055114076347653[161] = 0;
   out_8482055114076347653[162] = 0;
   out_8482055114076347653[163] = 0;
   out_8482055114076347653[164] = 0;
   out_8482055114076347653[165] = 0;
   out_8482055114076347653[166] = 0;
   out_8482055114076347653[167] = 0;
   out_8482055114076347653[168] = 0;
   out_8482055114076347653[169] = 0;
   out_8482055114076347653[170] = 0;
   out_8482055114076347653[171] = 1;
   out_8482055114076347653[172] = 0;
   out_8482055114076347653[173] = 0;
   out_8482055114076347653[174] = 0;
   out_8482055114076347653[175] = 0;
   out_8482055114076347653[176] = 0;
   out_8482055114076347653[177] = 0;
   out_8482055114076347653[178] = 0;
   out_8482055114076347653[179] = 0;
   out_8482055114076347653[180] = 0;
   out_8482055114076347653[181] = 0;
   out_8482055114076347653[182] = 0;
   out_8482055114076347653[183] = 0;
   out_8482055114076347653[184] = 0;
   out_8482055114076347653[185] = 0;
   out_8482055114076347653[186] = 0;
   out_8482055114076347653[187] = 0;
   out_8482055114076347653[188] = 0;
   out_8482055114076347653[189] = 0;
   out_8482055114076347653[190] = 1;
   out_8482055114076347653[191] = 0;
   out_8482055114076347653[192] = 0;
   out_8482055114076347653[193] = 0;
   out_8482055114076347653[194] = 0;
   out_8482055114076347653[195] = 0;
   out_8482055114076347653[196] = 0;
   out_8482055114076347653[197] = 0;
   out_8482055114076347653[198] = 0;
   out_8482055114076347653[199] = 0;
   out_8482055114076347653[200] = 0;
   out_8482055114076347653[201] = 0;
   out_8482055114076347653[202] = 0;
   out_8482055114076347653[203] = 0;
   out_8482055114076347653[204] = 0;
   out_8482055114076347653[205] = 0;
   out_8482055114076347653[206] = 0;
   out_8482055114076347653[207] = 0;
   out_8482055114076347653[208] = 0;
   out_8482055114076347653[209] = 1;
   out_8482055114076347653[210] = 0;
   out_8482055114076347653[211] = 0;
   out_8482055114076347653[212] = 0;
   out_8482055114076347653[213] = 0;
   out_8482055114076347653[214] = 0;
   out_8482055114076347653[215] = 0;
   out_8482055114076347653[216] = 0;
   out_8482055114076347653[217] = 0;
   out_8482055114076347653[218] = 0;
   out_8482055114076347653[219] = 0;
   out_8482055114076347653[220] = 0;
   out_8482055114076347653[221] = 0;
   out_8482055114076347653[222] = 0;
   out_8482055114076347653[223] = 0;
   out_8482055114076347653[224] = 0;
   out_8482055114076347653[225] = 0;
   out_8482055114076347653[226] = 0;
   out_8482055114076347653[227] = 0;
   out_8482055114076347653[228] = 1;
   out_8482055114076347653[229] = 0;
   out_8482055114076347653[230] = 0;
   out_8482055114076347653[231] = 0;
   out_8482055114076347653[232] = 0;
   out_8482055114076347653[233] = 0;
   out_8482055114076347653[234] = 0;
   out_8482055114076347653[235] = 0;
   out_8482055114076347653[236] = 0;
   out_8482055114076347653[237] = 0;
   out_8482055114076347653[238] = 0;
   out_8482055114076347653[239] = 0;
   out_8482055114076347653[240] = 0;
   out_8482055114076347653[241] = 0;
   out_8482055114076347653[242] = 0;
   out_8482055114076347653[243] = 0;
   out_8482055114076347653[244] = 0;
   out_8482055114076347653[245] = 0;
   out_8482055114076347653[246] = 0;
   out_8482055114076347653[247] = 1;
   out_8482055114076347653[248] = 0;
   out_8482055114076347653[249] = 0;
   out_8482055114076347653[250] = 0;
   out_8482055114076347653[251] = 0;
   out_8482055114076347653[252] = 0;
   out_8482055114076347653[253] = 0;
   out_8482055114076347653[254] = 0;
   out_8482055114076347653[255] = 0;
   out_8482055114076347653[256] = 0;
   out_8482055114076347653[257] = 0;
   out_8482055114076347653[258] = 0;
   out_8482055114076347653[259] = 0;
   out_8482055114076347653[260] = 0;
   out_8482055114076347653[261] = 0;
   out_8482055114076347653[262] = 0;
   out_8482055114076347653[263] = 0;
   out_8482055114076347653[264] = 0;
   out_8482055114076347653[265] = 0;
   out_8482055114076347653[266] = 1;
   out_8482055114076347653[267] = 0;
   out_8482055114076347653[268] = 0;
   out_8482055114076347653[269] = 0;
   out_8482055114076347653[270] = 0;
   out_8482055114076347653[271] = 0;
   out_8482055114076347653[272] = 0;
   out_8482055114076347653[273] = 0;
   out_8482055114076347653[274] = 0;
   out_8482055114076347653[275] = 0;
   out_8482055114076347653[276] = 0;
   out_8482055114076347653[277] = 0;
   out_8482055114076347653[278] = 0;
   out_8482055114076347653[279] = 0;
   out_8482055114076347653[280] = 0;
   out_8482055114076347653[281] = 0;
   out_8482055114076347653[282] = 0;
   out_8482055114076347653[283] = 0;
   out_8482055114076347653[284] = 0;
   out_8482055114076347653[285] = 1;
   out_8482055114076347653[286] = 0;
   out_8482055114076347653[287] = 0;
   out_8482055114076347653[288] = 0;
   out_8482055114076347653[289] = 0;
   out_8482055114076347653[290] = 0;
   out_8482055114076347653[291] = 0;
   out_8482055114076347653[292] = 0;
   out_8482055114076347653[293] = 0;
   out_8482055114076347653[294] = 0;
   out_8482055114076347653[295] = 0;
   out_8482055114076347653[296] = 0;
   out_8482055114076347653[297] = 0;
   out_8482055114076347653[298] = 0;
   out_8482055114076347653[299] = 0;
   out_8482055114076347653[300] = 0;
   out_8482055114076347653[301] = 0;
   out_8482055114076347653[302] = 0;
   out_8482055114076347653[303] = 0;
   out_8482055114076347653[304] = 1;
   out_8482055114076347653[305] = 0;
   out_8482055114076347653[306] = 0;
   out_8482055114076347653[307] = 0;
   out_8482055114076347653[308] = 0;
   out_8482055114076347653[309] = 0;
   out_8482055114076347653[310] = 0;
   out_8482055114076347653[311] = 0;
   out_8482055114076347653[312] = 0;
   out_8482055114076347653[313] = 0;
   out_8482055114076347653[314] = 0;
   out_8482055114076347653[315] = 0;
   out_8482055114076347653[316] = 0;
   out_8482055114076347653[317] = 0;
   out_8482055114076347653[318] = 0;
   out_8482055114076347653[319] = 0;
   out_8482055114076347653[320] = 0;
   out_8482055114076347653[321] = 0;
   out_8482055114076347653[322] = 0;
   out_8482055114076347653[323] = 1;
}
void h_4(double *state, double *unused, double *out_1502834332527763816) {
   out_1502834332527763816[0] = state[6] + state[9];
   out_1502834332527763816[1] = state[7] + state[10];
   out_1502834332527763816[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4880994235593149308) {
   out_4880994235593149308[0] = 0;
   out_4880994235593149308[1] = 0;
   out_4880994235593149308[2] = 0;
   out_4880994235593149308[3] = 0;
   out_4880994235593149308[4] = 0;
   out_4880994235593149308[5] = 0;
   out_4880994235593149308[6] = 1;
   out_4880994235593149308[7] = 0;
   out_4880994235593149308[8] = 0;
   out_4880994235593149308[9] = 1;
   out_4880994235593149308[10] = 0;
   out_4880994235593149308[11] = 0;
   out_4880994235593149308[12] = 0;
   out_4880994235593149308[13] = 0;
   out_4880994235593149308[14] = 0;
   out_4880994235593149308[15] = 0;
   out_4880994235593149308[16] = 0;
   out_4880994235593149308[17] = 0;
   out_4880994235593149308[18] = 0;
   out_4880994235593149308[19] = 0;
   out_4880994235593149308[20] = 0;
   out_4880994235593149308[21] = 0;
   out_4880994235593149308[22] = 0;
   out_4880994235593149308[23] = 0;
   out_4880994235593149308[24] = 0;
   out_4880994235593149308[25] = 1;
   out_4880994235593149308[26] = 0;
   out_4880994235593149308[27] = 0;
   out_4880994235593149308[28] = 1;
   out_4880994235593149308[29] = 0;
   out_4880994235593149308[30] = 0;
   out_4880994235593149308[31] = 0;
   out_4880994235593149308[32] = 0;
   out_4880994235593149308[33] = 0;
   out_4880994235593149308[34] = 0;
   out_4880994235593149308[35] = 0;
   out_4880994235593149308[36] = 0;
   out_4880994235593149308[37] = 0;
   out_4880994235593149308[38] = 0;
   out_4880994235593149308[39] = 0;
   out_4880994235593149308[40] = 0;
   out_4880994235593149308[41] = 0;
   out_4880994235593149308[42] = 0;
   out_4880994235593149308[43] = 0;
   out_4880994235593149308[44] = 1;
   out_4880994235593149308[45] = 0;
   out_4880994235593149308[46] = 0;
   out_4880994235593149308[47] = 1;
   out_4880994235593149308[48] = 0;
   out_4880994235593149308[49] = 0;
   out_4880994235593149308[50] = 0;
   out_4880994235593149308[51] = 0;
   out_4880994235593149308[52] = 0;
   out_4880994235593149308[53] = 0;
}
void h_10(double *state, double *unused, double *out_6109171037953532925) {
   out_6109171037953532925[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6109171037953532925[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6109171037953532925[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7194656996829539727) {
   out_7194656996829539727[0] = 0;
   out_7194656996829539727[1] = 9.8100000000000005*cos(state[1]);
   out_7194656996829539727[2] = 0;
   out_7194656996829539727[3] = 0;
   out_7194656996829539727[4] = -state[8];
   out_7194656996829539727[5] = state[7];
   out_7194656996829539727[6] = 0;
   out_7194656996829539727[7] = state[5];
   out_7194656996829539727[8] = -state[4];
   out_7194656996829539727[9] = 0;
   out_7194656996829539727[10] = 0;
   out_7194656996829539727[11] = 0;
   out_7194656996829539727[12] = 1;
   out_7194656996829539727[13] = 0;
   out_7194656996829539727[14] = 0;
   out_7194656996829539727[15] = 1;
   out_7194656996829539727[16] = 0;
   out_7194656996829539727[17] = 0;
   out_7194656996829539727[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7194656996829539727[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7194656996829539727[20] = 0;
   out_7194656996829539727[21] = state[8];
   out_7194656996829539727[22] = 0;
   out_7194656996829539727[23] = -state[6];
   out_7194656996829539727[24] = -state[5];
   out_7194656996829539727[25] = 0;
   out_7194656996829539727[26] = state[3];
   out_7194656996829539727[27] = 0;
   out_7194656996829539727[28] = 0;
   out_7194656996829539727[29] = 0;
   out_7194656996829539727[30] = 0;
   out_7194656996829539727[31] = 1;
   out_7194656996829539727[32] = 0;
   out_7194656996829539727[33] = 0;
   out_7194656996829539727[34] = 1;
   out_7194656996829539727[35] = 0;
   out_7194656996829539727[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7194656996829539727[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7194656996829539727[38] = 0;
   out_7194656996829539727[39] = -state[7];
   out_7194656996829539727[40] = state[6];
   out_7194656996829539727[41] = 0;
   out_7194656996829539727[42] = state[4];
   out_7194656996829539727[43] = -state[3];
   out_7194656996829539727[44] = 0;
   out_7194656996829539727[45] = 0;
   out_7194656996829539727[46] = 0;
   out_7194656996829539727[47] = 0;
   out_7194656996829539727[48] = 0;
   out_7194656996829539727[49] = 0;
   out_7194656996829539727[50] = 1;
   out_7194656996829539727[51] = 0;
   out_7194656996829539727[52] = 0;
   out_7194656996829539727[53] = 1;
}
void h_13(double *state, double *unused, double *out_5799887535713035202) {
   out_5799887535713035202[0] = state[3];
   out_5799887535713035202[1] = state[4];
   out_5799887535713035202[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8093268060925482109) {
   out_8093268060925482109[0] = 0;
   out_8093268060925482109[1] = 0;
   out_8093268060925482109[2] = 0;
   out_8093268060925482109[3] = 1;
   out_8093268060925482109[4] = 0;
   out_8093268060925482109[5] = 0;
   out_8093268060925482109[6] = 0;
   out_8093268060925482109[7] = 0;
   out_8093268060925482109[8] = 0;
   out_8093268060925482109[9] = 0;
   out_8093268060925482109[10] = 0;
   out_8093268060925482109[11] = 0;
   out_8093268060925482109[12] = 0;
   out_8093268060925482109[13] = 0;
   out_8093268060925482109[14] = 0;
   out_8093268060925482109[15] = 0;
   out_8093268060925482109[16] = 0;
   out_8093268060925482109[17] = 0;
   out_8093268060925482109[18] = 0;
   out_8093268060925482109[19] = 0;
   out_8093268060925482109[20] = 0;
   out_8093268060925482109[21] = 0;
   out_8093268060925482109[22] = 1;
   out_8093268060925482109[23] = 0;
   out_8093268060925482109[24] = 0;
   out_8093268060925482109[25] = 0;
   out_8093268060925482109[26] = 0;
   out_8093268060925482109[27] = 0;
   out_8093268060925482109[28] = 0;
   out_8093268060925482109[29] = 0;
   out_8093268060925482109[30] = 0;
   out_8093268060925482109[31] = 0;
   out_8093268060925482109[32] = 0;
   out_8093268060925482109[33] = 0;
   out_8093268060925482109[34] = 0;
   out_8093268060925482109[35] = 0;
   out_8093268060925482109[36] = 0;
   out_8093268060925482109[37] = 0;
   out_8093268060925482109[38] = 0;
   out_8093268060925482109[39] = 0;
   out_8093268060925482109[40] = 0;
   out_8093268060925482109[41] = 1;
   out_8093268060925482109[42] = 0;
   out_8093268060925482109[43] = 0;
   out_8093268060925482109[44] = 0;
   out_8093268060925482109[45] = 0;
   out_8093268060925482109[46] = 0;
   out_8093268060925482109[47] = 0;
   out_8093268060925482109[48] = 0;
   out_8093268060925482109[49] = 0;
   out_8093268060925482109[50] = 0;
   out_8093268060925482109[51] = 0;
   out_8093268060925482109[52] = 0;
   out_8093268060925482109[53] = 0;
}
void h_14(double *state, double *unused, double *out_2127057284884247461) {
   out_2127057284884247461[0] = state[6];
   out_2127057284884247461[1] = state[7];
   out_2127057284884247461[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8844235091932633837) {
   out_8844235091932633837[0] = 0;
   out_8844235091932633837[1] = 0;
   out_8844235091932633837[2] = 0;
   out_8844235091932633837[3] = 0;
   out_8844235091932633837[4] = 0;
   out_8844235091932633837[5] = 0;
   out_8844235091932633837[6] = 1;
   out_8844235091932633837[7] = 0;
   out_8844235091932633837[8] = 0;
   out_8844235091932633837[9] = 0;
   out_8844235091932633837[10] = 0;
   out_8844235091932633837[11] = 0;
   out_8844235091932633837[12] = 0;
   out_8844235091932633837[13] = 0;
   out_8844235091932633837[14] = 0;
   out_8844235091932633837[15] = 0;
   out_8844235091932633837[16] = 0;
   out_8844235091932633837[17] = 0;
   out_8844235091932633837[18] = 0;
   out_8844235091932633837[19] = 0;
   out_8844235091932633837[20] = 0;
   out_8844235091932633837[21] = 0;
   out_8844235091932633837[22] = 0;
   out_8844235091932633837[23] = 0;
   out_8844235091932633837[24] = 0;
   out_8844235091932633837[25] = 1;
   out_8844235091932633837[26] = 0;
   out_8844235091932633837[27] = 0;
   out_8844235091932633837[28] = 0;
   out_8844235091932633837[29] = 0;
   out_8844235091932633837[30] = 0;
   out_8844235091932633837[31] = 0;
   out_8844235091932633837[32] = 0;
   out_8844235091932633837[33] = 0;
   out_8844235091932633837[34] = 0;
   out_8844235091932633837[35] = 0;
   out_8844235091932633837[36] = 0;
   out_8844235091932633837[37] = 0;
   out_8844235091932633837[38] = 0;
   out_8844235091932633837[39] = 0;
   out_8844235091932633837[40] = 0;
   out_8844235091932633837[41] = 0;
   out_8844235091932633837[42] = 0;
   out_8844235091932633837[43] = 0;
   out_8844235091932633837[44] = 1;
   out_8844235091932633837[45] = 0;
   out_8844235091932633837[46] = 0;
   out_8844235091932633837[47] = 0;
   out_8844235091932633837[48] = 0;
   out_8844235091932633837[49] = 0;
   out_8844235091932633837[50] = 0;
   out_8844235091932633837[51] = 0;
   out_8844235091932633837[52] = 0;
   out_8844235091932633837[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5899152602515428793) {
  err_fun(nom_x, delta_x, out_5899152602515428793);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1853168426912981794) {
  inv_err_fun(nom_x, true_x, out_1853168426912981794);
}
void pose_H_mod_fun(double *state, double *out_4126833233538436701) {
  H_mod_fun(state, out_4126833233538436701);
}
void pose_f_fun(double *state, double dt, double *out_4790836135548827488) {
  f_fun(state,  dt, out_4790836135548827488);
}
void pose_F_fun(double *state, double dt, double *out_8482055114076347653) {
  F_fun(state,  dt, out_8482055114076347653);
}
void pose_h_4(double *state, double *unused, double *out_1502834332527763816) {
  h_4(state, unused, out_1502834332527763816);
}
void pose_H_4(double *state, double *unused, double *out_4880994235593149308) {
  H_4(state, unused, out_4880994235593149308);
}
void pose_h_10(double *state, double *unused, double *out_6109171037953532925) {
  h_10(state, unused, out_6109171037953532925);
}
void pose_H_10(double *state, double *unused, double *out_7194656996829539727) {
  H_10(state, unused, out_7194656996829539727);
}
void pose_h_13(double *state, double *unused, double *out_5799887535713035202) {
  h_13(state, unused, out_5799887535713035202);
}
void pose_H_13(double *state, double *unused, double *out_8093268060925482109) {
  H_13(state, unused, out_8093268060925482109);
}
void pose_h_14(double *state, double *unused, double *out_2127057284884247461) {
  h_14(state, unused, out_2127057284884247461);
}
void pose_H_14(double *state, double *unused, double *out_8844235091932633837) {
  H_14(state, unused, out_8844235091932633837);
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
