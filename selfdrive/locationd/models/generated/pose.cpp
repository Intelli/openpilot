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
void err_fun(double *nom_x, double *delta_x, double *out_2757450705506867855) {
   out_2757450705506867855[0] = delta_x[0] + nom_x[0];
   out_2757450705506867855[1] = delta_x[1] + nom_x[1];
   out_2757450705506867855[2] = delta_x[2] + nom_x[2];
   out_2757450705506867855[3] = delta_x[3] + nom_x[3];
   out_2757450705506867855[4] = delta_x[4] + nom_x[4];
   out_2757450705506867855[5] = delta_x[5] + nom_x[5];
   out_2757450705506867855[6] = delta_x[6] + nom_x[6];
   out_2757450705506867855[7] = delta_x[7] + nom_x[7];
   out_2757450705506867855[8] = delta_x[8] + nom_x[8];
   out_2757450705506867855[9] = delta_x[9] + nom_x[9];
   out_2757450705506867855[10] = delta_x[10] + nom_x[10];
   out_2757450705506867855[11] = delta_x[11] + nom_x[11];
   out_2757450705506867855[12] = delta_x[12] + nom_x[12];
   out_2757450705506867855[13] = delta_x[13] + nom_x[13];
   out_2757450705506867855[14] = delta_x[14] + nom_x[14];
   out_2757450705506867855[15] = delta_x[15] + nom_x[15];
   out_2757450705506867855[16] = delta_x[16] + nom_x[16];
   out_2757450705506867855[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2371677109582741398) {
   out_2371677109582741398[0] = -nom_x[0] + true_x[0];
   out_2371677109582741398[1] = -nom_x[1] + true_x[1];
   out_2371677109582741398[2] = -nom_x[2] + true_x[2];
   out_2371677109582741398[3] = -nom_x[3] + true_x[3];
   out_2371677109582741398[4] = -nom_x[4] + true_x[4];
   out_2371677109582741398[5] = -nom_x[5] + true_x[5];
   out_2371677109582741398[6] = -nom_x[6] + true_x[6];
   out_2371677109582741398[7] = -nom_x[7] + true_x[7];
   out_2371677109582741398[8] = -nom_x[8] + true_x[8];
   out_2371677109582741398[9] = -nom_x[9] + true_x[9];
   out_2371677109582741398[10] = -nom_x[10] + true_x[10];
   out_2371677109582741398[11] = -nom_x[11] + true_x[11];
   out_2371677109582741398[12] = -nom_x[12] + true_x[12];
   out_2371677109582741398[13] = -nom_x[13] + true_x[13];
   out_2371677109582741398[14] = -nom_x[14] + true_x[14];
   out_2371677109582741398[15] = -nom_x[15] + true_x[15];
   out_2371677109582741398[16] = -nom_x[16] + true_x[16];
   out_2371677109582741398[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7009258506666885735) {
   out_7009258506666885735[0] = 1.0;
   out_7009258506666885735[1] = 0.0;
   out_7009258506666885735[2] = 0.0;
   out_7009258506666885735[3] = 0.0;
   out_7009258506666885735[4] = 0.0;
   out_7009258506666885735[5] = 0.0;
   out_7009258506666885735[6] = 0.0;
   out_7009258506666885735[7] = 0.0;
   out_7009258506666885735[8] = 0.0;
   out_7009258506666885735[9] = 0.0;
   out_7009258506666885735[10] = 0.0;
   out_7009258506666885735[11] = 0.0;
   out_7009258506666885735[12] = 0.0;
   out_7009258506666885735[13] = 0.0;
   out_7009258506666885735[14] = 0.0;
   out_7009258506666885735[15] = 0.0;
   out_7009258506666885735[16] = 0.0;
   out_7009258506666885735[17] = 0.0;
   out_7009258506666885735[18] = 0.0;
   out_7009258506666885735[19] = 1.0;
   out_7009258506666885735[20] = 0.0;
   out_7009258506666885735[21] = 0.0;
   out_7009258506666885735[22] = 0.0;
   out_7009258506666885735[23] = 0.0;
   out_7009258506666885735[24] = 0.0;
   out_7009258506666885735[25] = 0.0;
   out_7009258506666885735[26] = 0.0;
   out_7009258506666885735[27] = 0.0;
   out_7009258506666885735[28] = 0.0;
   out_7009258506666885735[29] = 0.0;
   out_7009258506666885735[30] = 0.0;
   out_7009258506666885735[31] = 0.0;
   out_7009258506666885735[32] = 0.0;
   out_7009258506666885735[33] = 0.0;
   out_7009258506666885735[34] = 0.0;
   out_7009258506666885735[35] = 0.0;
   out_7009258506666885735[36] = 0.0;
   out_7009258506666885735[37] = 0.0;
   out_7009258506666885735[38] = 1.0;
   out_7009258506666885735[39] = 0.0;
   out_7009258506666885735[40] = 0.0;
   out_7009258506666885735[41] = 0.0;
   out_7009258506666885735[42] = 0.0;
   out_7009258506666885735[43] = 0.0;
   out_7009258506666885735[44] = 0.0;
   out_7009258506666885735[45] = 0.0;
   out_7009258506666885735[46] = 0.0;
   out_7009258506666885735[47] = 0.0;
   out_7009258506666885735[48] = 0.0;
   out_7009258506666885735[49] = 0.0;
   out_7009258506666885735[50] = 0.0;
   out_7009258506666885735[51] = 0.0;
   out_7009258506666885735[52] = 0.0;
   out_7009258506666885735[53] = 0.0;
   out_7009258506666885735[54] = 0.0;
   out_7009258506666885735[55] = 0.0;
   out_7009258506666885735[56] = 0.0;
   out_7009258506666885735[57] = 1.0;
   out_7009258506666885735[58] = 0.0;
   out_7009258506666885735[59] = 0.0;
   out_7009258506666885735[60] = 0.0;
   out_7009258506666885735[61] = 0.0;
   out_7009258506666885735[62] = 0.0;
   out_7009258506666885735[63] = 0.0;
   out_7009258506666885735[64] = 0.0;
   out_7009258506666885735[65] = 0.0;
   out_7009258506666885735[66] = 0.0;
   out_7009258506666885735[67] = 0.0;
   out_7009258506666885735[68] = 0.0;
   out_7009258506666885735[69] = 0.0;
   out_7009258506666885735[70] = 0.0;
   out_7009258506666885735[71] = 0.0;
   out_7009258506666885735[72] = 0.0;
   out_7009258506666885735[73] = 0.0;
   out_7009258506666885735[74] = 0.0;
   out_7009258506666885735[75] = 0.0;
   out_7009258506666885735[76] = 1.0;
   out_7009258506666885735[77] = 0.0;
   out_7009258506666885735[78] = 0.0;
   out_7009258506666885735[79] = 0.0;
   out_7009258506666885735[80] = 0.0;
   out_7009258506666885735[81] = 0.0;
   out_7009258506666885735[82] = 0.0;
   out_7009258506666885735[83] = 0.0;
   out_7009258506666885735[84] = 0.0;
   out_7009258506666885735[85] = 0.0;
   out_7009258506666885735[86] = 0.0;
   out_7009258506666885735[87] = 0.0;
   out_7009258506666885735[88] = 0.0;
   out_7009258506666885735[89] = 0.0;
   out_7009258506666885735[90] = 0.0;
   out_7009258506666885735[91] = 0.0;
   out_7009258506666885735[92] = 0.0;
   out_7009258506666885735[93] = 0.0;
   out_7009258506666885735[94] = 0.0;
   out_7009258506666885735[95] = 1.0;
   out_7009258506666885735[96] = 0.0;
   out_7009258506666885735[97] = 0.0;
   out_7009258506666885735[98] = 0.0;
   out_7009258506666885735[99] = 0.0;
   out_7009258506666885735[100] = 0.0;
   out_7009258506666885735[101] = 0.0;
   out_7009258506666885735[102] = 0.0;
   out_7009258506666885735[103] = 0.0;
   out_7009258506666885735[104] = 0.0;
   out_7009258506666885735[105] = 0.0;
   out_7009258506666885735[106] = 0.0;
   out_7009258506666885735[107] = 0.0;
   out_7009258506666885735[108] = 0.0;
   out_7009258506666885735[109] = 0.0;
   out_7009258506666885735[110] = 0.0;
   out_7009258506666885735[111] = 0.0;
   out_7009258506666885735[112] = 0.0;
   out_7009258506666885735[113] = 0.0;
   out_7009258506666885735[114] = 1.0;
   out_7009258506666885735[115] = 0.0;
   out_7009258506666885735[116] = 0.0;
   out_7009258506666885735[117] = 0.0;
   out_7009258506666885735[118] = 0.0;
   out_7009258506666885735[119] = 0.0;
   out_7009258506666885735[120] = 0.0;
   out_7009258506666885735[121] = 0.0;
   out_7009258506666885735[122] = 0.0;
   out_7009258506666885735[123] = 0.0;
   out_7009258506666885735[124] = 0.0;
   out_7009258506666885735[125] = 0.0;
   out_7009258506666885735[126] = 0.0;
   out_7009258506666885735[127] = 0.0;
   out_7009258506666885735[128] = 0.0;
   out_7009258506666885735[129] = 0.0;
   out_7009258506666885735[130] = 0.0;
   out_7009258506666885735[131] = 0.0;
   out_7009258506666885735[132] = 0.0;
   out_7009258506666885735[133] = 1.0;
   out_7009258506666885735[134] = 0.0;
   out_7009258506666885735[135] = 0.0;
   out_7009258506666885735[136] = 0.0;
   out_7009258506666885735[137] = 0.0;
   out_7009258506666885735[138] = 0.0;
   out_7009258506666885735[139] = 0.0;
   out_7009258506666885735[140] = 0.0;
   out_7009258506666885735[141] = 0.0;
   out_7009258506666885735[142] = 0.0;
   out_7009258506666885735[143] = 0.0;
   out_7009258506666885735[144] = 0.0;
   out_7009258506666885735[145] = 0.0;
   out_7009258506666885735[146] = 0.0;
   out_7009258506666885735[147] = 0.0;
   out_7009258506666885735[148] = 0.0;
   out_7009258506666885735[149] = 0.0;
   out_7009258506666885735[150] = 0.0;
   out_7009258506666885735[151] = 0.0;
   out_7009258506666885735[152] = 1.0;
   out_7009258506666885735[153] = 0.0;
   out_7009258506666885735[154] = 0.0;
   out_7009258506666885735[155] = 0.0;
   out_7009258506666885735[156] = 0.0;
   out_7009258506666885735[157] = 0.0;
   out_7009258506666885735[158] = 0.0;
   out_7009258506666885735[159] = 0.0;
   out_7009258506666885735[160] = 0.0;
   out_7009258506666885735[161] = 0.0;
   out_7009258506666885735[162] = 0.0;
   out_7009258506666885735[163] = 0.0;
   out_7009258506666885735[164] = 0.0;
   out_7009258506666885735[165] = 0.0;
   out_7009258506666885735[166] = 0.0;
   out_7009258506666885735[167] = 0.0;
   out_7009258506666885735[168] = 0.0;
   out_7009258506666885735[169] = 0.0;
   out_7009258506666885735[170] = 0.0;
   out_7009258506666885735[171] = 1.0;
   out_7009258506666885735[172] = 0.0;
   out_7009258506666885735[173] = 0.0;
   out_7009258506666885735[174] = 0.0;
   out_7009258506666885735[175] = 0.0;
   out_7009258506666885735[176] = 0.0;
   out_7009258506666885735[177] = 0.0;
   out_7009258506666885735[178] = 0.0;
   out_7009258506666885735[179] = 0.0;
   out_7009258506666885735[180] = 0.0;
   out_7009258506666885735[181] = 0.0;
   out_7009258506666885735[182] = 0.0;
   out_7009258506666885735[183] = 0.0;
   out_7009258506666885735[184] = 0.0;
   out_7009258506666885735[185] = 0.0;
   out_7009258506666885735[186] = 0.0;
   out_7009258506666885735[187] = 0.0;
   out_7009258506666885735[188] = 0.0;
   out_7009258506666885735[189] = 0.0;
   out_7009258506666885735[190] = 1.0;
   out_7009258506666885735[191] = 0.0;
   out_7009258506666885735[192] = 0.0;
   out_7009258506666885735[193] = 0.0;
   out_7009258506666885735[194] = 0.0;
   out_7009258506666885735[195] = 0.0;
   out_7009258506666885735[196] = 0.0;
   out_7009258506666885735[197] = 0.0;
   out_7009258506666885735[198] = 0.0;
   out_7009258506666885735[199] = 0.0;
   out_7009258506666885735[200] = 0.0;
   out_7009258506666885735[201] = 0.0;
   out_7009258506666885735[202] = 0.0;
   out_7009258506666885735[203] = 0.0;
   out_7009258506666885735[204] = 0.0;
   out_7009258506666885735[205] = 0.0;
   out_7009258506666885735[206] = 0.0;
   out_7009258506666885735[207] = 0.0;
   out_7009258506666885735[208] = 0.0;
   out_7009258506666885735[209] = 1.0;
   out_7009258506666885735[210] = 0.0;
   out_7009258506666885735[211] = 0.0;
   out_7009258506666885735[212] = 0.0;
   out_7009258506666885735[213] = 0.0;
   out_7009258506666885735[214] = 0.0;
   out_7009258506666885735[215] = 0.0;
   out_7009258506666885735[216] = 0.0;
   out_7009258506666885735[217] = 0.0;
   out_7009258506666885735[218] = 0.0;
   out_7009258506666885735[219] = 0.0;
   out_7009258506666885735[220] = 0.0;
   out_7009258506666885735[221] = 0.0;
   out_7009258506666885735[222] = 0.0;
   out_7009258506666885735[223] = 0.0;
   out_7009258506666885735[224] = 0.0;
   out_7009258506666885735[225] = 0.0;
   out_7009258506666885735[226] = 0.0;
   out_7009258506666885735[227] = 0.0;
   out_7009258506666885735[228] = 1.0;
   out_7009258506666885735[229] = 0.0;
   out_7009258506666885735[230] = 0.0;
   out_7009258506666885735[231] = 0.0;
   out_7009258506666885735[232] = 0.0;
   out_7009258506666885735[233] = 0.0;
   out_7009258506666885735[234] = 0.0;
   out_7009258506666885735[235] = 0.0;
   out_7009258506666885735[236] = 0.0;
   out_7009258506666885735[237] = 0.0;
   out_7009258506666885735[238] = 0.0;
   out_7009258506666885735[239] = 0.0;
   out_7009258506666885735[240] = 0.0;
   out_7009258506666885735[241] = 0.0;
   out_7009258506666885735[242] = 0.0;
   out_7009258506666885735[243] = 0.0;
   out_7009258506666885735[244] = 0.0;
   out_7009258506666885735[245] = 0.0;
   out_7009258506666885735[246] = 0.0;
   out_7009258506666885735[247] = 1.0;
   out_7009258506666885735[248] = 0.0;
   out_7009258506666885735[249] = 0.0;
   out_7009258506666885735[250] = 0.0;
   out_7009258506666885735[251] = 0.0;
   out_7009258506666885735[252] = 0.0;
   out_7009258506666885735[253] = 0.0;
   out_7009258506666885735[254] = 0.0;
   out_7009258506666885735[255] = 0.0;
   out_7009258506666885735[256] = 0.0;
   out_7009258506666885735[257] = 0.0;
   out_7009258506666885735[258] = 0.0;
   out_7009258506666885735[259] = 0.0;
   out_7009258506666885735[260] = 0.0;
   out_7009258506666885735[261] = 0.0;
   out_7009258506666885735[262] = 0.0;
   out_7009258506666885735[263] = 0.0;
   out_7009258506666885735[264] = 0.0;
   out_7009258506666885735[265] = 0.0;
   out_7009258506666885735[266] = 1.0;
   out_7009258506666885735[267] = 0.0;
   out_7009258506666885735[268] = 0.0;
   out_7009258506666885735[269] = 0.0;
   out_7009258506666885735[270] = 0.0;
   out_7009258506666885735[271] = 0.0;
   out_7009258506666885735[272] = 0.0;
   out_7009258506666885735[273] = 0.0;
   out_7009258506666885735[274] = 0.0;
   out_7009258506666885735[275] = 0.0;
   out_7009258506666885735[276] = 0.0;
   out_7009258506666885735[277] = 0.0;
   out_7009258506666885735[278] = 0.0;
   out_7009258506666885735[279] = 0.0;
   out_7009258506666885735[280] = 0.0;
   out_7009258506666885735[281] = 0.0;
   out_7009258506666885735[282] = 0.0;
   out_7009258506666885735[283] = 0.0;
   out_7009258506666885735[284] = 0.0;
   out_7009258506666885735[285] = 1.0;
   out_7009258506666885735[286] = 0.0;
   out_7009258506666885735[287] = 0.0;
   out_7009258506666885735[288] = 0.0;
   out_7009258506666885735[289] = 0.0;
   out_7009258506666885735[290] = 0.0;
   out_7009258506666885735[291] = 0.0;
   out_7009258506666885735[292] = 0.0;
   out_7009258506666885735[293] = 0.0;
   out_7009258506666885735[294] = 0.0;
   out_7009258506666885735[295] = 0.0;
   out_7009258506666885735[296] = 0.0;
   out_7009258506666885735[297] = 0.0;
   out_7009258506666885735[298] = 0.0;
   out_7009258506666885735[299] = 0.0;
   out_7009258506666885735[300] = 0.0;
   out_7009258506666885735[301] = 0.0;
   out_7009258506666885735[302] = 0.0;
   out_7009258506666885735[303] = 0.0;
   out_7009258506666885735[304] = 1.0;
   out_7009258506666885735[305] = 0.0;
   out_7009258506666885735[306] = 0.0;
   out_7009258506666885735[307] = 0.0;
   out_7009258506666885735[308] = 0.0;
   out_7009258506666885735[309] = 0.0;
   out_7009258506666885735[310] = 0.0;
   out_7009258506666885735[311] = 0.0;
   out_7009258506666885735[312] = 0.0;
   out_7009258506666885735[313] = 0.0;
   out_7009258506666885735[314] = 0.0;
   out_7009258506666885735[315] = 0.0;
   out_7009258506666885735[316] = 0.0;
   out_7009258506666885735[317] = 0.0;
   out_7009258506666885735[318] = 0.0;
   out_7009258506666885735[319] = 0.0;
   out_7009258506666885735[320] = 0.0;
   out_7009258506666885735[321] = 0.0;
   out_7009258506666885735[322] = 0.0;
   out_7009258506666885735[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3443385267993362178) {
   out_3443385267993362178[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3443385267993362178[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3443385267993362178[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3443385267993362178[3] = dt*state[12] + state[3];
   out_3443385267993362178[4] = dt*state[13] + state[4];
   out_3443385267993362178[5] = dt*state[14] + state[5];
   out_3443385267993362178[6] = state[6];
   out_3443385267993362178[7] = state[7];
   out_3443385267993362178[8] = state[8];
   out_3443385267993362178[9] = state[9];
   out_3443385267993362178[10] = state[10];
   out_3443385267993362178[11] = state[11];
   out_3443385267993362178[12] = state[12];
   out_3443385267993362178[13] = state[13];
   out_3443385267993362178[14] = state[14];
   out_3443385267993362178[15] = state[15];
   out_3443385267993362178[16] = state[16];
   out_3443385267993362178[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3344416469963573399) {
   out_3344416469963573399[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3344416469963573399[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3344416469963573399[2] = 0;
   out_3344416469963573399[3] = 0;
   out_3344416469963573399[4] = 0;
   out_3344416469963573399[5] = 0;
   out_3344416469963573399[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3344416469963573399[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3344416469963573399[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3344416469963573399[9] = 0;
   out_3344416469963573399[10] = 0;
   out_3344416469963573399[11] = 0;
   out_3344416469963573399[12] = 0;
   out_3344416469963573399[13] = 0;
   out_3344416469963573399[14] = 0;
   out_3344416469963573399[15] = 0;
   out_3344416469963573399[16] = 0;
   out_3344416469963573399[17] = 0;
   out_3344416469963573399[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3344416469963573399[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3344416469963573399[20] = 0;
   out_3344416469963573399[21] = 0;
   out_3344416469963573399[22] = 0;
   out_3344416469963573399[23] = 0;
   out_3344416469963573399[24] = 0;
   out_3344416469963573399[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3344416469963573399[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3344416469963573399[27] = 0;
   out_3344416469963573399[28] = 0;
   out_3344416469963573399[29] = 0;
   out_3344416469963573399[30] = 0;
   out_3344416469963573399[31] = 0;
   out_3344416469963573399[32] = 0;
   out_3344416469963573399[33] = 0;
   out_3344416469963573399[34] = 0;
   out_3344416469963573399[35] = 0;
   out_3344416469963573399[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3344416469963573399[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3344416469963573399[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3344416469963573399[39] = 0;
   out_3344416469963573399[40] = 0;
   out_3344416469963573399[41] = 0;
   out_3344416469963573399[42] = 0;
   out_3344416469963573399[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3344416469963573399[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3344416469963573399[45] = 0;
   out_3344416469963573399[46] = 0;
   out_3344416469963573399[47] = 0;
   out_3344416469963573399[48] = 0;
   out_3344416469963573399[49] = 0;
   out_3344416469963573399[50] = 0;
   out_3344416469963573399[51] = 0;
   out_3344416469963573399[52] = 0;
   out_3344416469963573399[53] = 0;
   out_3344416469963573399[54] = 0;
   out_3344416469963573399[55] = 0;
   out_3344416469963573399[56] = 0;
   out_3344416469963573399[57] = 1;
   out_3344416469963573399[58] = 0;
   out_3344416469963573399[59] = 0;
   out_3344416469963573399[60] = 0;
   out_3344416469963573399[61] = 0;
   out_3344416469963573399[62] = 0;
   out_3344416469963573399[63] = 0;
   out_3344416469963573399[64] = 0;
   out_3344416469963573399[65] = 0;
   out_3344416469963573399[66] = dt;
   out_3344416469963573399[67] = 0;
   out_3344416469963573399[68] = 0;
   out_3344416469963573399[69] = 0;
   out_3344416469963573399[70] = 0;
   out_3344416469963573399[71] = 0;
   out_3344416469963573399[72] = 0;
   out_3344416469963573399[73] = 0;
   out_3344416469963573399[74] = 0;
   out_3344416469963573399[75] = 0;
   out_3344416469963573399[76] = 1;
   out_3344416469963573399[77] = 0;
   out_3344416469963573399[78] = 0;
   out_3344416469963573399[79] = 0;
   out_3344416469963573399[80] = 0;
   out_3344416469963573399[81] = 0;
   out_3344416469963573399[82] = 0;
   out_3344416469963573399[83] = 0;
   out_3344416469963573399[84] = 0;
   out_3344416469963573399[85] = dt;
   out_3344416469963573399[86] = 0;
   out_3344416469963573399[87] = 0;
   out_3344416469963573399[88] = 0;
   out_3344416469963573399[89] = 0;
   out_3344416469963573399[90] = 0;
   out_3344416469963573399[91] = 0;
   out_3344416469963573399[92] = 0;
   out_3344416469963573399[93] = 0;
   out_3344416469963573399[94] = 0;
   out_3344416469963573399[95] = 1;
   out_3344416469963573399[96] = 0;
   out_3344416469963573399[97] = 0;
   out_3344416469963573399[98] = 0;
   out_3344416469963573399[99] = 0;
   out_3344416469963573399[100] = 0;
   out_3344416469963573399[101] = 0;
   out_3344416469963573399[102] = 0;
   out_3344416469963573399[103] = 0;
   out_3344416469963573399[104] = dt;
   out_3344416469963573399[105] = 0;
   out_3344416469963573399[106] = 0;
   out_3344416469963573399[107] = 0;
   out_3344416469963573399[108] = 0;
   out_3344416469963573399[109] = 0;
   out_3344416469963573399[110] = 0;
   out_3344416469963573399[111] = 0;
   out_3344416469963573399[112] = 0;
   out_3344416469963573399[113] = 0;
   out_3344416469963573399[114] = 1;
   out_3344416469963573399[115] = 0;
   out_3344416469963573399[116] = 0;
   out_3344416469963573399[117] = 0;
   out_3344416469963573399[118] = 0;
   out_3344416469963573399[119] = 0;
   out_3344416469963573399[120] = 0;
   out_3344416469963573399[121] = 0;
   out_3344416469963573399[122] = 0;
   out_3344416469963573399[123] = 0;
   out_3344416469963573399[124] = 0;
   out_3344416469963573399[125] = 0;
   out_3344416469963573399[126] = 0;
   out_3344416469963573399[127] = 0;
   out_3344416469963573399[128] = 0;
   out_3344416469963573399[129] = 0;
   out_3344416469963573399[130] = 0;
   out_3344416469963573399[131] = 0;
   out_3344416469963573399[132] = 0;
   out_3344416469963573399[133] = 1;
   out_3344416469963573399[134] = 0;
   out_3344416469963573399[135] = 0;
   out_3344416469963573399[136] = 0;
   out_3344416469963573399[137] = 0;
   out_3344416469963573399[138] = 0;
   out_3344416469963573399[139] = 0;
   out_3344416469963573399[140] = 0;
   out_3344416469963573399[141] = 0;
   out_3344416469963573399[142] = 0;
   out_3344416469963573399[143] = 0;
   out_3344416469963573399[144] = 0;
   out_3344416469963573399[145] = 0;
   out_3344416469963573399[146] = 0;
   out_3344416469963573399[147] = 0;
   out_3344416469963573399[148] = 0;
   out_3344416469963573399[149] = 0;
   out_3344416469963573399[150] = 0;
   out_3344416469963573399[151] = 0;
   out_3344416469963573399[152] = 1;
   out_3344416469963573399[153] = 0;
   out_3344416469963573399[154] = 0;
   out_3344416469963573399[155] = 0;
   out_3344416469963573399[156] = 0;
   out_3344416469963573399[157] = 0;
   out_3344416469963573399[158] = 0;
   out_3344416469963573399[159] = 0;
   out_3344416469963573399[160] = 0;
   out_3344416469963573399[161] = 0;
   out_3344416469963573399[162] = 0;
   out_3344416469963573399[163] = 0;
   out_3344416469963573399[164] = 0;
   out_3344416469963573399[165] = 0;
   out_3344416469963573399[166] = 0;
   out_3344416469963573399[167] = 0;
   out_3344416469963573399[168] = 0;
   out_3344416469963573399[169] = 0;
   out_3344416469963573399[170] = 0;
   out_3344416469963573399[171] = 1;
   out_3344416469963573399[172] = 0;
   out_3344416469963573399[173] = 0;
   out_3344416469963573399[174] = 0;
   out_3344416469963573399[175] = 0;
   out_3344416469963573399[176] = 0;
   out_3344416469963573399[177] = 0;
   out_3344416469963573399[178] = 0;
   out_3344416469963573399[179] = 0;
   out_3344416469963573399[180] = 0;
   out_3344416469963573399[181] = 0;
   out_3344416469963573399[182] = 0;
   out_3344416469963573399[183] = 0;
   out_3344416469963573399[184] = 0;
   out_3344416469963573399[185] = 0;
   out_3344416469963573399[186] = 0;
   out_3344416469963573399[187] = 0;
   out_3344416469963573399[188] = 0;
   out_3344416469963573399[189] = 0;
   out_3344416469963573399[190] = 1;
   out_3344416469963573399[191] = 0;
   out_3344416469963573399[192] = 0;
   out_3344416469963573399[193] = 0;
   out_3344416469963573399[194] = 0;
   out_3344416469963573399[195] = 0;
   out_3344416469963573399[196] = 0;
   out_3344416469963573399[197] = 0;
   out_3344416469963573399[198] = 0;
   out_3344416469963573399[199] = 0;
   out_3344416469963573399[200] = 0;
   out_3344416469963573399[201] = 0;
   out_3344416469963573399[202] = 0;
   out_3344416469963573399[203] = 0;
   out_3344416469963573399[204] = 0;
   out_3344416469963573399[205] = 0;
   out_3344416469963573399[206] = 0;
   out_3344416469963573399[207] = 0;
   out_3344416469963573399[208] = 0;
   out_3344416469963573399[209] = 1;
   out_3344416469963573399[210] = 0;
   out_3344416469963573399[211] = 0;
   out_3344416469963573399[212] = 0;
   out_3344416469963573399[213] = 0;
   out_3344416469963573399[214] = 0;
   out_3344416469963573399[215] = 0;
   out_3344416469963573399[216] = 0;
   out_3344416469963573399[217] = 0;
   out_3344416469963573399[218] = 0;
   out_3344416469963573399[219] = 0;
   out_3344416469963573399[220] = 0;
   out_3344416469963573399[221] = 0;
   out_3344416469963573399[222] = 0;
   out_3344416469963573399[223] = 0;
   out_3344416469963573399[224] = 0;
   out_3344416469963573399[225] = 0;
   out_3344416469963573399[226] = 0;
   out_3344416469963573399[227] = 0;
   out_3344416469963573399[228] = 1;
   out_3344416469963573399[229] = 0;
   out_3344416469963573399[230] = 0;
   out_3344416469963573399[231] = 0;
   out_3344416469963573399[232] = 0;
   out_3344416469963573399[233] = 0;
   out_3344416469963573399[234] = 0;
   out_3344416469963573399[235] = 0;
   out_3344416469963573399[236] = 0;
   out_3344416469963573399[237] = 0;
   out_3344416469963573399[238] = 0;
   out_3344416469963573399[239] = 0;
   out_3344416469963573399[240] = 0;
   out_3344416469963573399[241] = 0;
   out_3344416469963573399[242] = 0;
   out_3344416469963573399[243] = 0;
   out_3344416469963573399[244] = 0;
   out_3344416469963573399[245] = 0;
   out_3344416469963573399[246] = 0;
   out_3344416469963573399[247] = 1;
   out_3344416469963573399[248] = 0;
   out_3344416469963573399[249] = 0;
   out_3344416469963573399[250] = 0;
   out_3344416469963573399[251] = 0;
   out_3344416469963573399[252] = 0;
   out_3344416469963573399[253] = 0;
   out_3344416469963573399[254] = 0;
   out_3344416469963573399[255] = 0;
   out_3344416469963573399[256] = 0;
   out_3344416469963573399[257] = 0;
   out_3344416469963573399[258] = 0;
   out_3344416469963573399[259] = 0;
   out_3344416469963573399[260] = 0;
   out_3344416469963573399[261] = 0;
   out_3344416469963573399[262] = 0;
   out_3344416469963573399[263] = 0;
   out_3344416469963573399[264] = 0;
   out_3344416469963573399[265] = 0;
   out_3344416469963573399[266] = 1;
   out_3344416469963573399[267] = 0;
   out_3344416469963573399[268] = 0;
   out_3344416469963573399[269] = 0;
   out_3344416469963573399[270] = 0;
   out_3344416469963573399[271] = 0;
   out_3344416469963573399[272] = 0;
   out_3344416469963573399[273] = 0;
   out_3344416469963573399[274] = 0;
   out_3344416469963573399[275] = 0;
   out_3344416469963573399[276] = 0;
   out_3344416469963573399[277] = 0;
   out_3344416469963573399[278] = 0;
   out_3344416469963573399[279] = 0;
   out_3344416469963573399[280] = 0;
   out_3344416469963573399[281] = 0;
   out_3344416469963573399[282] = 0;
   out_3344416469963573399[283] = 0;
   out_3344416469963573399[284] = 0;
   out_3344416469963573399[285] = 1;
   out_3344416469963573399[286] = 0;
   out_3344416469963573399[287] = 0;
   out_3344416469963573399[288] = 0;
   out_3344416469963573399[289] = 0;
   out_3344416469963573399[290] = 0;
   out_3344416469963573399[291] = 0;
   out_3344416469963573399[292] = 0;
   out_3344416469963573399[293] = 0;
   out_3344416469963573399[294] = 0;
   out_3344416469963573399[295] = 0;
   out_3344416469963573399[296] = 0;
   out_3344416469963573399[297] = 0;
   out_3344416469963573399[298] = 0;
   out_3344416469963573399[299] = 0;
   out_3344416469963573399[300] = 0;
   out_3344416469963573399[301] = 0;
   out_3344416469963573399[302] = 0;
   out_3344416469963573399[303] = 0;
   out_3344416469963573399[304] = 1;
   out_3344416469963573399[305] = 0;
   out_3344416469963573399[306] = 0;
   out_3344416469963573399[307] = 0;
   out_3344416469963573399[308] = 0;
   out_3344416469963573399[309] = 0;
   out_3344416469963573399[310] = 0;
   out_3344416469963573399[311] = 0;
   out_3344416469963573399[312] = 0;
   out_3344416469963573399[313] = 0;
   out_3344416469963573399[314] = 0;
   out_3344416469963573399[315] = 0;
   out_3344416469963573399[316] = 0;
   out_3344416469963573399[317] = 0;
   out_3344416469963573399[318] = 0;
   out_3344416469963573399[319] = 0;
   out_3344416469963573399[320] = 0;
   out_3344416469963573399[321] = 0;
   out_3344416469963573399[322] = 0;
   out_3344416469963573399[323] = 1;
}
void h_4(double *state, double *unused, double *out_5247280839960053081) {
   out_5247280839960053081[0] = state[6] + state[9];
   out_5247280839960053081[1] = state[7] + state[10];
   out_5247280839960053081[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4508962887351945075) {
   out_4508962887351945075[0] = 0;
   out_4508962887351945075[1] = 0;
   out_4508962887351945075[2] = 0;
   out_4508962887351945075[3] = 0;
   out_4508962887351945075[4] = 0;
   out_4508962887351945075[5] = 0;
   out_4508962887351945075[6] = 1;
   out_4508962887351945075[7] = 0;
   out_4508962887351945075[8] = 0;
   out_4508962887351945075[9] = 1;
   out_4508962887351945075[10] = 0;
   out_4508962887351945075[11] = 0;
   out_4508962887351945075[12] = 0;
   out_4508962887351945075[13] = 0;
   out_4508962887351945075[14] = 0;
   out_4508962887351945075[15] = 0;
   out_4508962887351945075[16] = 0;
   out_4508962887351945075[17] = 0;
   out_4508962887351945075[18] = 0;
   out_4508962887351945075[19] = 0;
   out_4508962887351945075[20] = 0;
   out_4508962887351945075[21] = 0;
   out_4508962887351945075[22] = 0;
   out_4508962887351945075[23] = 0;
   out_4508962887351945075[24] = 0;
   out_4508962887351945075[25] = 1;
   out_4508962887351945075[26] = 0;
   out_4508962887351945075[27] = 0;
   out_4508962887351945075[28] = 1;
   out_4508962887351945075[29] = 0;
   out_4508962887351945075[30] = 0;
   out_4508962887351945075[31] = 0;
   out_4508962887351945075[32] = 0;
   out_4508962887351945075[33] = 0;
   out_4508962887351945075[34] = 0;
   out_4508962887351945075[35] = 0;
   out_4508962887351945075[36] = 0;
   out_4508962887351945075[37] = 0;
   out_4508962887351945075[38] = 0;
   out_4508962887351945075[39] = 0;
   out_4508962887351945075[40] = 0;
   out_4508962887351945075[41] = 0;
   out_4508962887351945075[42] = 0;
   out_4508962887351945075[43] = 0;
   out_4508962887351945075[44] = 1;
   out_4508962887351945075[45] = 0;
   out_4508962887351945075[46] = 0;
   out_4508962887351945075[47] = 1;
   out_4508962887351945075[48] = 0;
   out_4508962887351945075[49] = 0;
   out_4508962887351945075[50] = 0;
   out_4508962887351945075[51] = 0;
   out_4508962887351945075[52] = 0;
   out_4508962887351945075[53] = 0;
}
void h_10(double *state, double *unused, double *out_9164942161681221546) {
   out_9164942161681221546[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_9164942161681221546[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_9164942161681221546[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7905481608622117688) {
   out_7905481608622117688[0] = 0;
   out_7905481608622117688[1] = 9.8100000000000005*cos(state[1]);
   out_7905481608622117688[2] = 0;
   out_7905481608622117688[3] = 0;
   out_7905481608622117688[4] = -state[8];
   out_7905481608622117688[5] = state[7];
   out_7905481608622117688[6] = 0;
   out_7905481608622117688[7] = state[5];
   out_7905481608622117688[8] = -state[4];
   out_7905481608622117688[9] = 0;
   out_7905481608622117688[10] = 0;
   out_7905481608622117688[11] = 0;
   out_7905481608622117688[12] = 1;
   out_7905481608622117688[13] = 0;
   out_7905481608622117688[14] = 0;
   out_7905481608622117688[15] = 1;
   out_7905481608622117688[16] = 0;
   out_7905481608622117688[17] = 0;
   out_7905481608622117688[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7905481608622117688[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7905481608622117688[20] = 0;
   out_7905481608622117688[21] = state[8];
   out_7905481608622117688[22] = 0;
   out_7905481608622117688[23] = -state[6];
   out_7905481608622117688[24] = -state[5];
   out_7905481608622117688[25] = 0;
   out_7905481608622117688[26] = state[3];
   out_7905481608622117688[27] = 0;
   out_7905481608622117688[28] = 0;
   out_7905481608622117688[29] = 0;
   out_7905481608622117688[30] = 0;
   out_7905481608622117688[31] = 1;
   out_7905481608622117688[32] = 0;
   out_7905481608622117688[33] = 0;
   out_7905481608622117688[34] = 1;
   out_7905481608622117688[35] = 0;
   out_7905481608622117688[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7905481608622117688[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7905481608622117688[38] = 0;
   out_7905481608622117688[39] = -state[7];
   out_7905481608622117688[40] = state[6];
   out_7905481608622117688[41] = 0;
   out_7905481608622117688[42] = state[4];
   out_7905481608622117688[43] = -state[3];
   out_7905481608622117688[44] = 0;
   out_7905481608622117688[45] = 0;
   out_7905481608622117688[46] = 0;
   out_7905481608622117688[47] = 0;
   out_7905481608622117688[48] = 0;
   out_7905481608622117688[49] = 0;
   out_7905481608622117688[50] = 1;
   out_7905481608622117688[51] = 0;
   out_7905481608622117688[52] = 0;
   out_7905481608622117688[53] = 1;
}
void h_13(double *state, double *unused, double *out_4129298553195873659) {
   out_4129298553195873659[0] = state[3];
   out_4129298553195873659[1] = state[4];
   out_4129298553195873659[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1296689062019612274) {
   out_1296689062019612274[0] = 0;
   out_1296689062019612274[1] = 0;
   out_1296689062019612274[2] = 0;
   out_1296689062019612274[3] = 1;
   out_1296689062019612274[4] = 0;
   out_1296689062019612274[5] = 0;
   out_1296689062019612274[6] = 0;
   out_1296689062019612274[7] = 0;
   out_1296689062019612274[8] = 0;
   out_1296689062019612274[9] = 0;
   out_1296689062019612274[10] = 0;
   out_1296689062019612274[11] = 0;
   out_1296689062019612274[12] = 0;
   out_1296689062019612274[13] = 0;
   out_1296689062019612274[14] = 0;
   out_1296689062019612274[15] = 0;
   out_1296689062019612274[16] = 0;
   out_1296689062019612274[17] = 0;
   out_1296689062019612274[18] = 0;
   out_1296689062019612274[19] = 0;
   out_1296689062019612274[20] = 0;
   out_1296689062019612274[21] = 0;
   out_1296689062019612274[22] = 1;
   out_1296689062019612274[23] = 0;
   out_1296689062019612274[24] = 0;
   out_1296689062019612274[25] = 0;
   out_1296689062019612274[26] = 0;
   out_1296689062019612274[27] = 0;
   out_1296689062019612274[28] = 0;
   out_1296689062019612274[29] = 0;
   out_1296689062019612274[30] = 0;
   out_1296689062019612274[31] = 0;
   out_1296689062019612274[32] = 0;
   out_1296689062019612274[33] = 0;
   out_1296689062019612274[34] = 0;
   out_1296689062019612274[35] = 0;
   out_1296689062019612274[36] = 0;
   out_1296689062019612274[37] = 0;
   out_1296689062019612274[38] = 0;
   out_1296689062019612274[39] = 0;
   out_1296689062019612274[40] = 0;
   out_1296689062019612274[41] = 1;
   out_1296689062019612274[42] = 0;
   out_1296689062019612274[43] = 0;
   out_1296689062019612274[44] = 0;
   out_1296689062019612274[45] = 0;
   out_1296689062019612274[46] = 0;
   out_1296689062019612274[47] = 0;
   out_1296689062019612274[48] = 0;
   out_1296689062019612274[49] = 0;
   out_1296689062019612274[50] = 0;
   out_1296689062019612274[51] = 0;
   out_1296689062019612274[52] = 0;
   out_1296689062019612274[53] = 0;
}
void h_14(double *state, double *unused, double *out_3157172185554168331) {
   out_3157172185554168331[0] = state[6];
   out_3157172185554168331[1] = state[7];
   out_3157172185554168331[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7591751319647317371) {
   out_7591751319647317371[0] = 0;
   out_7591751319647317371[1] = 0;
   out_7591751319647317371[2] = 0;
   out_7591751319647317371[3] = 0;
   out_7591751319647317371[4] = 0;
   out_7591751319647317371[5] = 0;
   out_7591751319647317371[6] = 1;
   out_7591751319647317371[7] = 0;
   out_7591751319647317371[8] = 0;
   out_7591751319647317371[9] = 0;
   out_7591751319647317371[10] = 0;
   out_7591751319647317371[11] = 0;
   out_7591751319647317371[12] = 0;
   out_7591751319647317371[13] = 0;
   out_7591751319647317371[14] = 0;
   out_7591751319647317371[15] = 0;
   out_7591751319647317371[16] = 0;
   out_7591751319647317371[17] = 0;
   out_7591751319647317371[18] = 0;
   out_7591751319647317371[19] = 0;
   out_7591751319647317371[20] = 0;
   out_7591751319647317371[21] = 0;
   out_7591751319647317371[22] = 0;
   out_7591751319647317371[23] = 0;
   out_7591751319647317371[24] = 0;
   out_7591751319647317371[25] = 1;
   out_7591751319647317371[26] = 0;
   out_7591751319647317371[27] = 0;
   out_7591751319647317371[28] = 0;
   out_7591751319647317371[29] = 0;
   out_7591751319647317371[30] = 0;
   out_7591751319647317371[31] = 0;
   out_7591751319647317371[32] = 0;
   out_7591751319647317371[33] = 0;
   out_7591751319647317371[34] = 0;
   out_7591751319647317371[35] = 0;
   out_7591751319647317371[36] = 0;
   out_7591751319647317371[37] = 0;
   out_7591751319647317371[38] = 0;
   out_7591751319647317371[39] = 0;
   out_7591751319647317371[40] = 0;
   out_7591751319647317371[41] = 0;
   out_7591751319647317371[42] = 0;
   out_7591751319647317371[43] = 0;
   out_7591751319647317371[44] = 1;
   out_7591751319647317371[45] = 0;
   out_7591751319647317371[46] = 0;
   out_7591751319647317371[47] = 0;
   out_7591751319647317371[48] = 0;
   out_7591751319647317371[49] = 0;
   out_7591751319647317371[50] = 0;
   out_7591751319647317371[51] = 0;
   out_7591751319647317371[52] = 0;
   out_7591751319647317371[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2757450705506867855) {
  err_fun(nom_x, delta_x, out_2757450705506867855);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2371677109582741398) {
  inv_err_fun(nom_x, true_x, out_2371677109582741398);
}
void pose_H_mod_fun(double *state, double *out_7009258506666885735) {
  H_mod_fun(state, out_7009258506666885735);
}
void pose_f_fun(double *state, double dt, double *out_3443385267993362178) {
  f_fun(state,  dt, out_3443385267993362178);
}
void pose_F_fun(double *state, double dt, double *out_3344416469963573399) {
  F_fun(state,  dt, out_3344416469963573399);
}
void pose_h_4(double *state, double *unused, double *out_5247280839960053081) {
  h_4(state, unused, out_5247280839960053081);
}
void pose_H_4(double *state, double *unused, double *out_4508962887351945075) {
  H_4(state, unused, out_4508962887351945075);
}
void pose_h_10(double *state, double *unused, double *out_9164942161681221546) {
  h_10(state, unused, out_9164942161681221546);
}
void pose_H_10(double *state, double *unused, double *out_7905481608622117688) {
  H_10(state, unused, out_7905481608622117688);
}
void pose_h_13(double *state, double *unused, double *out_4129298553195873659) {
  h_13(state, unused, out_4129298553195873659);
}
void pose_H_13(double *state, double *unused, double *out_1296689062019612274) {
  H_13(state, unused, out_1296689062019612274);
}
void pose_h_14(double *state, double *unused, double *out_3157172185554168331) {
  h_14(state, unused, out_3157172185554168331);
}
void pose_H_14(double *state, double *unused, double *out_7591751319647317371) {
  H_14(state, unused, out_7591751319647317371);
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
