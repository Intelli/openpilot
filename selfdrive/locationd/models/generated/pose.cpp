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
void err_fun(double *nom_x, double *delta_x, double *out_1246780800306708420) {
   out_1246780800306708420[0] = delta_x[0] + nom_x[0];
   out_1246780800306708420[1] = delta_x[1] + nom_x[1];
   out_1246780800306708420[2] = delta_x[2] + nom_x[2];
   out_1246780800306708420[3] = delta_x[3] + nom_x[3];
   out_1246780800306708420[4] = delta_x[4] + nom_x[4];
   out_1246780800306708420[5] = delta_x[5] + nom_x[5];
   out_1246780800306708420[6] = delta_x[6] + nom_x[6];
   out_1246780800306708420[7] = delta_x[7] + nom_x[7];
   out_1246780800306708420[8] = delta_x[8] + nom_x[8];
   out_1246780800306708420[9] = delta_x[9] + nom_x[9];
   out_1246780800306708420[10] = delta_x[10] + nom_x[10];
   out_1246780800306708420[11] = delta_x[11] + nom_x[11];
   out_1246780800306708420[12] = delta_x[12] + nom_x[12];
   out_1246780800306708420[13] = delta_x[13] + nom_x[13];
   out_1246780800306708420[14] = delta_x[14] + nom_x[14];
   out_1246780800306708420[15] = delta_x[15] + nom_x[15];
   out_1246780800306708420[16] = delta_x[16] + nom_x[16];
   out_1246780800306708420[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_322701955714434799) {
   out_322701955714434799[0] = -nom_x[0] + true_x[0];
   out_322701955714434799[1] = -nom_x[1] + true_x[1];
   out_322701955714434799[2] = -nom_x[2] + true_x[2];
   out_322701955714434799[3] = -nom_x[3] + true_x[3];
   out_322701955714434799[4] = -nom_x[4] + true_x[4];
   out_322701955714434799[5] = -nom_x[5] + true_x[5];
   out_322701955714434799[6] = -nom_x[6] + true_x[6];
   out_322701955714434799[7] = -nom_x[7] + true_x[7];
   out_322701955714434799[8] = -nom_x[8] + true_x[8];
   out_322701955714434799[9] = -nom_x[9] + true_x[9];
   out_322701955714434799[10] = -nom_x[10] + true_x[10];
   out_322701955714434799[11] = -nom_x[11] + true_x[11];
   out_322701955714434799[12] = -nom_x[12] + true_x[12];
   out_322701955714434799[13] = -nom_x[13] + true_x[13];
   out_322701955714434799[14] = -nom_x[14] + true_x[14];
   out_322701955714434799[15] = -nom_x[15] + true_x[15];
   out_322701955714434799[16] = -nom_x[16] + true_x[16];
   out_322701955714434799[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_950382144461574038) {
   out_950382144461574038[0] = 1.0;
   out_950382144461574038[1] = 0.0;
   out_950382144461574038[2] = 0.0;
   out_950382144461574038[3] = 0.0;
   out_950382144461574038[4] = 0.0;
   out_950382144461574038[5] = 0.0;
   out_950382144461574038[6] = 0.0;
   out_950382144461574038[7] = 0.0;
   out_950382144461574038[8] = 0.0;
   out_950382144461574038[9] = 0.0;
   out_950382144461574038[10] = 0.0;
   out_950382144461574038[11] = 0.0;
   out_950382144461574038[12] = 0.0;
   out_950382144461574038[13] = 0.0;
   out_950382144461574038[14] = 0.0;
   out_950382144461574038[15] = 0.0;
   out_950382144461574038[16] = 0.0;
   out_950382144461574038[17] = 0.0;
   out_950382144461574038[18] = 0.0;
   out_950382144461574038[19] = 1.0;
   out_950382144461574038[20] = 0.0;
   out_950382144461574038[21] = 0.0;
   out_950382144461574038[22] = 0.0;
   out_950382144461574038[23] = 0.0;
   out_950382144461574038[24] = 0.0;
   out_950382144461574038[25] = 0.0;
   out_950382144461574038[26] = 0.0;
   out_950382144461574038[27] = 0.0;
   out_950382144461574038[28] = 0.0;
   out_950382144461574038[29] = 0.0;
   out_950382144461574038[30] = 0.0;
   out_950382144461574038[31] = 0.0;
   out_950382144461574038[32] = 0.0;
   out_950382144461574038[33] = 0.0;
   out_950382144461574038[34] = 0.0;
   out_950382144461574038[35] = 0.0;
   out_950382144461574038[36] = 0.0;
   out_950382144461574038[37] = 0.0;
   out_950382144461574038[38] = 1.0;
   out_950382144461574038[39] = 0.0;
   out_950382144461574038[40] = 0.0;
   out_950382144461574038[41] = 0.0;
   out_950382144461574038[42] = 0.0;
   out_950382144461574038[43] = 0.0;
   out_950382144461574038[44] = 0.0;
   out_950382144461574038[45] = 0.0;
   out_950382144461574038[46] = 0.0;
   out_950382144461574038[47] = 0.0;
   out_950382144461574038[48] = 0.0;
   out_950382144461574038[49] = 0.0;
   out_950382144461574038[50] = 0.0;
   out_950382144461574038[51] = 0.0;
   out_950382144461574038[52] = 0.0;
   out_950382144461574038[53] = 0.0;
   out_950382144461574038[54] = 0.0;
   out_950382144461574038[55] = 0.0;
   out_950382144461574038[56] = 0.0;
   out_950382144461574038[57] = 1.0;
   out_950382144461574038[58] = 0.0;
   out_950382144461574038[59] = 0.0;
   out_950382144461574038[60] = 0.0;
   out_950382144461574038[61] = 0.0;
   out_950382144461574038[62] = 0.0;
   out_950382144461574038[63] = 0.0;
   out_950382144461574038[64] = 0.0;
   out_950382144461574038[65] = 0.0;
   out_950382144461574038[66] = 0.0;
   out_950382144461574038[67] = 0.0;
   out_950382144461574038[68] = 0.0;
   out_950382144461574038[69] = 0.0;
   out_950382144461574038[70] = 0.0;
   out_950382144461574038[71] = 0.0;
   out_950382144461574038[72] = 0.0;
   out_950382144461574038[73] = 0.0;
   out_950382144461574038[74] = 0.0;
   out_950382144461574038[75] = 0.0;
   out_950382144461574038[76] = 1.0;
   out_950382144461574038[77] = 0.0;
   out_950382144461574038[78] = 0.0;
   out_950382144461574038[79] = 0.0;
   out_950382144461574038[80] = 0.0;
   out_950382144461574038[81] = 0.0;
   out_950382144461574038[82] = 0.0;
   out_950382144461574038[83] = 0.0;
   out_950382144461574038[84] = 0.0;
   out_950382144461574038[85] = 0.0;
   out_950382144461574038[86] = 0.0;
   out_950382144461574038[87] = 0.0;
   out_950382144461574038[88] = 0.0;
   out_950382144461574038[89] = 0.0;
   out_950382144461574038[90] = 0.0;
   out_950382144461574038[91] = 0.0;
   out_950382144461574038[92] = 0.0;
   out_950382144461574038[93] = 0.0;
   out_950382144461574038[94] = 0.0;
   out_950382144461574038[95] = 1.0;
   out_950382144461574038[96] = 0.0;
   out_950382144461574038[97] = 0.0;
   out_950382144461574038[98] = 0.0;
   out_950382144461574038[99] = 0.0;
   out_950382144461574038[100] = 0.0;
   out_950382144461574038[101] = 0.0;
   out_950382144461574038[102] = 0.0;
   out_950382144461574038[103] = 0.0;
   out_950382144461574038[104] = 0.0;
   out_950382144461574038[105] = 0.0;
   out_950382144461574038[106] = 0.0;
   out_950382144461574038[107] = 0.0;
   out_950382144461574038[108] = 0.0;
   out_950382144461574038[109] = 0.0;
   out_950382144461574038[110] = 0.0;
   out_950382144461574038[111] = 0.0;
   out_950382144461574038[112] = 0.0;
   out_950382144461574038[113] = 0.0;
   out_950382144461574038[114] = 1.0;
   out_950382144461574038[115] = 0.0;
   out_950382144461574038[116] = 0.0;
   out_950382144461574038[117] = 0.0;
   out_950382144461574038[118] = 0.0;
   out_950382144461574038[119] = 0.0;
   out_950382144461574038[120] = 0.0;
   out_950382144461574038[121] = 0.0;
   out_950382144461574038[122] = 0.0;
   out_950382144461574038[123] = 0.0;
   out_950382144461574038[124] = 0.0;
   out_950382144461574038[125] = 0.0;
   out_950382144461574038[126] = 0.0;
   out_950382144461574038[127] = 0.0;
   out_950382144461574038[128] = 0.0;
   out_950382144461574038[129] = 0.0;
   out_950382144461574038[130] = 0.0;
   out_950382144461574038[131] = 0.0;
   out_950382144461574038[132] = 0.0;
   out_950382144461574038[133] = 1.0;
   out_950382144461574038[134] = 0.0;
   out_950382144461574038[135] = 0.0;
   out_950382144461574038[136] = 0.0;
   out_950382144461574038[137] = 0.0;
   out_950382144461574038[138] = 0.0;
   out_950382144461574038[139] = 0.0;
   out_950382144461574038[140] = 0.0;
   out_950382144461574038[141] = 0.0;
   out_950382144461574038[142] = 0.0;
   out_950382144461574038[143] = 0.0;
   out_950382144461574038[144] = 0.0;
   out_950382144461574038[145] = 0.0;
   out_950382144461574038[146] = 0.0;
   out_950382144461574038[147] = 0.0;
   out_950382144461574038[148] = 0.0;
   out_950382144461574038[149] = 0.0;
   out_950382144461574038[150] = 0.0;
   out_950382144461574038[151] = 0.0;
   out_950382144461574038[152] = 1.0;
   out_950382144461574038[153] = 0.0;
   out_950382144461574038[154] = 0.0;
   out_950382144461574038[155] = 0.0;
   out_950382144461574038[156] = 0.0;
   out_950382144461574038[157] = 0.0;
   out_950382144461574038[158] = 0.0;
   out_950382144461574038[159] = 0.0;
   out_950382144461574038[160] = 0.0;
   out_950382144461574038[161] = 0.0;
   out_950382144461574038[162] = 0.0;
   out_950382144461574038[163] = 0.0;
   out_950382144461574038[164] = 0.0;
   out_950382144461574038[165] = 0.0;
   out_950382144461574038[166] = 0.0;
   out_950382144461574038[167] = 0.0;
   out_950382144461574038[168] = 0.0;
   out_950382144461574038[169] = 0.0;
   out_950382144461574038[170] = 0.0;
   out_950382144461574038[171] = 1.0;
   out_950382144461574038[172] = 0.0;
   out_950382144461574038[173] = 0.0;
   out_950382144461574038[174] = 0.0;
   out_950382144461574038[175] = 0.0;
   out_950382144461574038[176] = 0.0;
   out_950382144461574038[177] = 0.0;
   out_950382144461574038[178] = 0.0;
   out_950382144461574038[179] = 0.0;
   out_950382144461574038[180] = 0.0;
   out_950382144461574038[181] = 0.0;
   out_950382144461574038[182] = 0.0;
   out_950382144461574038[183] = 0.0;
   out_950382144461574038[184] = 0.0;
   out_950382144461574038[185] = 0.0;
   out_950382144461574038[186] = 0.0;
   out_950382144461574038[187] = 0.0;
   out_950382144461574038[188] = 0.0;
   out_950382144461574038[189] = 0.0;
   out_950382144461574038[190] = 1.0;
   out_950382144461574038[191] = 0.0;
   out_950382144461574038[192] = 0.0;
   out_950382144461574038[193] = 0.0;
   out_950382144461574038[194] = 0.0;
   out_950382144461574038[195] = 0.0;
   out_950382144461574038[196] = 0.0;
   out_950382144461574038[197] = 0.0;
   out_950382144461574038[198] = 0.0;
   out_950382144461574038[199] = 0.0;
   out_950382144461574038[200] = 0.0;
   out_950382144461574038[201] = 0.0;
   out_950382144461574038[202] = 0.0;
   out_950382144461574038[203] = 0.0;
   out_950382144461574038[204] = 0.0;
   out_950382144461574038[205] = 0.0;
   out_950382144461574038[206] = 0.0;
   out_950382144461574038[207] = 0.0;
   out_950382144461574038[208] = 0.0;
   out_950382144461574038[209] = 1.0;
   out_950382144461574038[210] = 0.0;
   out_950382144461574038[211] = 0.0;
   out_950382144461574038[212] = 0.0;
   out_950382144461574038[213] = 0.0;
   out_950382144461574038[214] = 0.0;
   out_950382144461574038[215] = 0.0;
   out_950382144461574038[216] = 0.0;
   out_950382144461574038[217] = 0.0;
   out_950382144461574038[218] = 0.0;
   out_950382144461574038[219] = 0.0;
   out_950382144461574038[220] = 0.0;
   out_950382144461574038[221] = 0.0;
   out_950382144461574038[222] = 0.0;
   out_950382144461574038[223] = 0.0;
   out_950382144461574038[224] = 0.0;
   out_950382144461574038[225] = 0.0;
   out_950382144461574038[226] = 0.0;
   out_950382144461574038[227] = 0.0;
   out_950382144461574038[228] = 1.0;
   out_950382144461574038[229] = 0.0;
   out_950382144461574038[230] = 0.0;
   out_950382144461574038[231] = 0.0;
   out_950382144461574038[232] = 0.0;
   out_950382144461574038[233] = 0.0;
   out_950382144461574038[234] = 0.0;
   out_950382144461574038[235] = 0.0;
   out_950382144461574038[236] = 0.0;
   out_950382144461574038[237] = 0.0;
   out_950382144461574038[238] = 0.0;
   out_950382144461574038[239] = 0.0;
   out_950382144461574038[240] = 0.0;
   out_950382144461574038[241] = 0.0;
   out_950382144461574038[242] = 0.0;
   out_950382144461574038[243] = 0.0;
   out_950382144461574038[244] = 0.0;
   out_950382144461574038[245] = 0.0;
   out_950382144461574038[246] = 0.0;
   out_950382144461574038[247] = 1.0;
   out_950382144461574038[248] = 0.0;
   out_950382144461574038[249] = 0.0;
   out_950382144461574038[250] = 0.0;
   out_950382144461574038[251] = 0.0;
   out_950382144461574038[252] = 0.0;
   out_950382144461574038[253] = 0.0;
   out_950382144461574038[254] = 0.0;
   out_950382144461574038[255] = 0.0;
   out_950382144461574038[256] = 0.0;
   out_950382144461574038[257] = 0.0;
   out_950382144461574038[258] = 0.0;
   out_950382144461574038[259] = 0.0;
   out_950382144461574038[260] = 0.0;
   out_950382144461574038[261] = 0.0;
   out_950382144461574038[262] = 0.0;
   out_950382144461574038[263] = 0.0;
   out_950382144461574038[264] = 0.0;
   out_950382144461574038[265] = 0.0;
   out_950382144461574038[266] = 1.0;
   out_950382144461574038[267] = 0.0;
   out_950382144461574038[268] = 0.0;
   out_950382144461574038[269] = 0.0;
   out_950382144461574038[270] = 0.0;
   out_950382144461574038[271] = 0.0;
   out_950382144461574038[272] = 0.0;
   out_950382144461574038[273] = 0.0;
   out_950382144461574038[274] = 0.0;
   out_950382144461574038[275] = 0.0;
   out_950382144461574038[276] = 0.0;
   out_950382144461574038[277] = 0.0;
   out_950382144461574038[278] = 0.0;
   out_950382144461574038[279] = 0.0;
   out_950382144461574038[280] = 0.0;
   out_950382144461574038[281] = 0.0;
   out_950382144461574038[282] = 0.0;
   out_950382144461574038[283] = 0.0;
   out_950382144461574038[284] = 0.0;
   out_950382144461574038[285] = 1.0;
   out_950382144461574038[286] = 0.0;
   out_950382144461574038[287] = 0.0;
   out_950382144461574038[288] = 0.0;
   out_950382144461574038[289] = 0.0;
   out_950382144461574038[290] = 0.0;
   out_950382144461574038[291] = 0.0;
   out_950382144461574038[292] = 0.0;
   out_950382144461574038[293] = 0.0;
   out_950382144461574038[294] = 0.0;
   out_950382144461574038[295] = 0.0;
   out_950382144461574038[296] = 0.0;
   out_950382144461574038[297] = 0.0;
   out_950382144461574038[298] = 0.0;
   out_950382144461574038[299] = 0.0;
   out_950382144461574038[300] = 0.0;
   out_950382144461574038[301] = 0.0;
   out_950382144461574038[302] = 0.0;
   out_950382144461574038[303] = 0.0;
   out_950382144461574038[304] = 1.0;
   out_950382144461574038[305] = 0.0;
   out_950382144461574038[306] = 0.0;
   out_950382144461574038[307] = 0.0;
   out_950382144461574038[308] = 0.0;
   out_950382144461574038[309] = 0.0;
   out_950382144461574038[310] = 0.0;
   out_950382144461574038[311] = 0.0;
   out_950382144461574038[312] = 0.0;
   out_950382144461574038[313] = 0.0;
   out_950382144461574038[314] = 0.0;
   out_950382144461574038[315] = 0.0;
   out_950382144461574038[316] = 0.0;
   out_950382144461574038[317] = 0.0;
   out_950382144461574038[318] = 0.0;
   out_950382144461574038[319] = 0.0;
   out_950382144461574038[320] = 0.0;
   out_950382144461574038[321] = 0.0;
   out_950382144461574038[322] = 0.0;
   out_950382144461574038[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5588529265753131833) {
   out_5588529265753131833[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5588529265753131833[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5588529265753131833[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5588529265753131833[3] = dt*state[12] + state[3];
   out_5588529265753131833[4] = dt*state[13] + state[4];
   out_5588529265753131833[5] = dt*state[14] + state[5];
   out_5588529265753131833[6] = state[6];
   out_5588529265753131833[7] = state[7];
   out_5588529265753131833[8] = state[8];
   out_5588529265753131833[9] = state[9];
   out_5588529265753131833[10] = state[10];
   out_5588529265753131833[11] = state[11];
   out_5588529265753131833[12] = state[12];
   out_5588529265753131833[13] = state[13];
   out_5588529265753131833[14] = state[14];
   out_5588529265753131833[15] = state[15];
   out_5588529265753131833[16] = state[16];
   out_5588529265753131833[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2504363338325754815) {
   out_2504363338325754815[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504363338325754815[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504363338325754815[2] = 0;
   out_2504363338325754815[3] = 0;
   out_2504363338325754815[4] = 0;
   out_2504363338325754815[5] = 0;
   out_2504363338325754815[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504363338325754815[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504363338325754815[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504363338325754815[9] = 0;
   out_2504363338325754815[10] = 0;
   out_2504363338325754815[11] = 0;
   out_2504363338325754815[12] = 0;
   out_2504363338325754815[13] = 0;
   out_2504363338325754815[14] = 0;
   out_2504363338325754815[15] = 0;
   out_2504363338325754815[16] = 0;
   out_2504363338325754815[17] = 0;
   out_2504363338325754815[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2504363338325754815[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2504363338325754815[20] = 0;
   out_2504363338325754815[21] = 0;
   out_2504363338325754815[22] = 0;
   out_2504363338325754815[23] = 0;
   out_2504363338325754815[24] = 0;
   out_2504363338325754815[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2504363338325754815[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2504363338325754815[27] = 0;
   out_2504363338325754815[28] = 0;
   out_2504363338325754815[29] = 0;
   out_2504363338325754815[30] = 0;
   out_2504363338325754815[31] = 0;
   out_2504363338325754815[32] = 0;
   out_2504363338325754815[33] = 0;
   out_2504363338325754815[34] = 0;
   out_2504363338325754815[35] = 0;
   out_2504363338325754815[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504363338325754815[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504363338325754815[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504363338325754815[39] = 0;
   out_2504363338325754815[40] = 0;
   out_2504363338325754815[41] = 0;
   out_2504363338325754815[42] = 0;
   out_2504363338325754815[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504363338325754815[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504363338325754815[45] = 0;
   out_2504363338325754815[46] = 0;
   out_2504363338325754815[47] = 0;
   out_2504363338325754815[48] = 0;
   out_2504363338325754815[49] = 0;
   out_2504363338325754815[50] = 0;
   out_2504363338325754815[51] = 0;
   out_2504363338325754815[52] = 0;
   out_2504363338325754815[53] = 0;
   out_2504363338325754815[54] = 0;
   out_2504363338325754815[55] = 0;
   out_2504363338325754815[56] = 0;
   out_2504363338325754815[57] = 1;
   out_2504363338325754815[58] = 0;
   out_2504363338325754815[59] = 0;
   out_2504363338325754815[60] = 0;
   out_2504363338325754815[61] = 0;
   out_2504363338325754815[62] = 0;
   out_2504363338325754815[63] = 0;
   out_2504363338325754815[64] = 0;
   out_2504363338325754815[65] = 0;
   out_2504363338325754815[66] = dt;
   out_2504363338325754815[67] = 0;
   out_2504363338325754815[68] = 0;
   out_2504363338325754815[69] = 0;
   out_2504363338325754815[70] = 0;
   out_2504363338325754815[71] = 0;
   out_2504363338325754815[72] = 0;
   out_2504363338325754815[73] = 0;
   out_2504363338325754815[74] = 0;
   out_2504363338325754815[75] = 0;
   out_2504363338325754815[76] = 1;
   out_2504363338325754815[77] = 0;
   out_2504363338325754815[78] = 0;
   out_2504363338325754815[79] = 0;
   out_2504363338325754815[80] = 0;
   out_2504363338325754815[81] = 0;
   out_2504363338325754815[82] = 0;
   out_2504363338325754815[83] = 0;
   out_2504363338325754815[84] = 0;
   out_2504363338325754815[85] = dt;
   out_2504363338325754815[86] = 0;
   out_2504363338325754815[87] = 0;
   out_2504363338325754815[88] = 0;
   out_2504363338325754815[89] = 0;
   out_2504363338325754815[90] = 0;
   out_2504363338325754815[91] = 0;
   out_2504363338325754815[92] = 0;
   out_2504363338325754815[93] = 0;
   out_2504363338325754815[94] = 0;
   out_2504363338325754815[95] = 1;
   out_2504363338325754815[96] = 0;
   out_2504363338325754815[97] = 0;
   out_2504363338325754815[98] = 0;
   out_2504363338325754815[99] = 0;
   out_2504363338325754815[100] = 0;
   out_2504363338325754815[101] = 0;
   out_2504363338325754815[102] = 0;
   out_2504363338325754815[103] = 0;
   out_2504363338325754815[104] = dt;
   out_2504363338325754815[105] = 0;
   out_2504363338325754815[106] = 0;
   out_2504363338325754815[107] = 0;
   out_2504363338325754815[108] = 0;
   out_2504363338325754815[109] = 0;
   out_2504363338325754815[110] = 0;
   out_2504363338325754815[111] = 0;
   out_2504363338325754815[112] = 0;
   out_2504363338325754815[113] = 0;
   out_2504363338325754815[114] = 1;
   out_2504363338325754815[115] = 0;
   out_2504363338325754815[116] = 0;
   out_2504363338325754815[117] = 0;
   out_2504363338325754815[118] = 0;
   out_2504363338325754815[119] = 0;
   out_2504363338325754815[120] = 0;
   out_2504363338325754815[121] = 0;
   out_2504363338325754815[122] = 0;
   out_2504363338325754815[123] = 0;
   out_2504363338325754815[124] = 0;
   out_2504363338325754815[125] = 0;
   out_2504363338325754815[126] = 0;
   out_2504363338325754815[127] = 0;
   out_2504363338325754815[128] = 0;
   out_2504363338325754815[129] = 0;
   out_2504363338325754815[130] = 0;
   out_2504363338325754815[131] = 0;
   out_2504363338325754815[132] = 0;
   out_2504363338325754815[133] = 1;
   out_2504363338325754815[134] = 0;
   out_2504363338325754815[135] = 0;
   out_2504363338325754815[136] = 0;
   out_2504363338325754815[137] = 0;
   out_2504363338325754815[138] = 0;
   out_2504363338325754815[139] = 0;
   out_2504363338325754815[140] = 0;
   out_2504363338325754815[141] = 0;
   out_2504363338325754815[142] = 0;
   out_2504363338325754815[143] = 0;
   out_2504363338325754815[144] = 0;
   out_2504363338325754815[145] = 0;
   out_2504363338325754815[146] = 0;
   out_2504363338325754815[147] = 0;
   out_2504363338325754815[148] = 0;
   out_2504363338325754815[149] = 0;
   out_2504363338325754815[150] = 0;
   out_2504363338325754815[151] = 0;
   out_2504363338325754815[152] = 1;
   out_2504363338325754815[153] = 0;
   out_2504363338325754815[154] = 0;
   out_2504363338325754815[155] = 0;
   out_2504363338325754815[156] = 0;
   out_2504363338325754815[157] = 0;
   out_2504363338325754815[158] = 0;
   out_2504363338325754815[159] = 0;
   out_2504363338325754815[160] = 0;
   out_2504363338325754815[161] = 0;
   out_2504363338325754815[162] = 0;
   out_2504363338325754815[163] = 0;
   out_2504363338325754815[164] = 0;
   out_2504363338325754815[165] = 0;
   out_2504363338325754815[166] = 0;
   out_2504363338325754815[167] = 0;
   out_2504363338325754815[168] = 0;
   out_2504363338325754815[169] = 0;
   out_2504363338325754815[170] = 0;
   out_2504363338325754815[171] = 1;
   out_2504363338325754815[172] = 0;
   out_2504363338325754815[173] = 0;
   out_2504363338325754815[174] = 0;
   out_2504363338325754815[175] = 0;
   out_2504363338325754815[176] = 0;
   out_2504363338325754815[177] = 0;
   out_2504363338325754815[178] = 0;
   out_2504363338325754815[179] = 0;
   out_2504363338325754815[180] = 0;
   out_2504363338325754815[181] = 0;
   out_2504363338325754815[182] = 0;
   out_2504363338325754815[183] = 0;
   out_2504363338325754815[184] = 0;
   out_2504363338325754815[185] = 0;
   out_2504363338325754815[186] = 0;
   out_2504363338325754815[187] = 0;
   out_2504363338325754815[188] = 0;
   out_2504363338325754815[189] = 0;
   out_2504363338325754815[190] = 1;
   out_2504363338325754815[191] = 0;
   out_2504363338325754815[192] = 0;
   out_2504363338325754815[193] = 0;
   out_2504363338325754815[194] = 0;
   out_2504363338325754815[195] = 0;
   out_2504363338325754815[196] = 0;
   out_2504363338325754815[197] = 0;
   out_2504363338325754815[198] = 0;
   out_2504363338325754815[199] = 0;
   out_2504363338325754815[200] = 0;
   out_2504363338325754815[201] = 0;
   out_2504363338325754815[202] = 0;
   out_2504363338325754815[203] = 0;
   out_2504363338325754815[204] = 0;
   out_2504363338325754815[205] = 0;
   out_2504363338325754815[206] = 0;
   out_2504363338325754815[207] = 0;
   out_2504363338325754815[208] = 0;
   out_2504363338325754815[209] = 1;
   out_2504363338325754815[210] = 0;
   out_2504363338325754815[211] = 0;
   out_2504363338325754815[212] = 0;
   out_2504363338325754815[213] = 0;
   out_2504363338325754815[214] = 0;
   out_2504363338325754815[215] = 0;
   out_2504363338325754815[216] = 0;
   out_2504363338325754815[217] = 0;
   out_2504363338325754815[218] = 0;
   out_2504363338325754815[219] = 0;
   out_2504363338325754815[220] = 0;
   out_2504363338325754815[221] = 0;
   out_2504363338325754815[222] = 0;
   out_2504363338325754815[223] = 0;
   out_2504363338325754815[224] = 0;
   out_2504363338325754815[225] = 0;
   out_2504363338325754815[226] = 0;
   out_2504363338325754815[227] = 0;
   out_2504363338325754815[228] = 1;
   out_2504363338325754815[229] = 0;
   out_2504363338325754815[230] = 0;
   out_2504363338325754815[231] = 0;
   out_2504363338325754815[232] = 0;
   out_2504363338325754815[233] = 0;
   out_2504363338325754815[234] = 0;
   out_2504363338325754815[235] = 0;
   out_2504363338325754815[236] = 0;
   out_2504363338325754815[237] = 0;
   out_2504363338325754815[238] = 0;
   out_2504363338325754815[239] = 0;
   out_2504363338325754815[240] = 0;
   out_2504363338325754815[241] = 0;
   out_2504363338325754815[242] = 0;
   out_2504363338325754815[243] = 0;
   out_2504363338325754815[244] = 0;
   out_2504363338325754815[245] = 0;
   out_2504363338325754815[246] = 0;
   out_2504363338325754815[247] = 1;
   out_2504363338325754815[248] = 0;
   out_2504363338325754815[249] = 0;
   out_2504363338325754815[250] = 0;
   out_2504363338325754815[251] = 0;
   out_2504363338325754815[252] = 0;
   out_2504363338325754815[253] = 0;
   out_2504363338325754815[254] = 0;
   out_2504363338325754815[255] = 0;
   out_2504363338325754815[256] = 0;
   out_2504363338325754815[257] = 0;
   out_2504363338325754815[258] = 0;
   out_2504363338325754815[259] = 0;
   out_2504363338325754815[260] = 0;
   out_2504363338325754815[261] = 0;
   out_2504363338325754815[262] = 0;
   out_2504363338325754815[263] = 0;
   out_2504363338325754815[264] = 0;
   out_2504363338325754815[265] = 0;
   out_2504363338325754815[266] = 1;
   out_2504363338325754815[267] = 0;
   out_2504363338325754815[268] = 0;
   out_2504363338325754815[269] = 0;
   out_2504363338325754815[270] = 0;
   out_2504363338325754815[271] = 0;
   out_2504363338325754815[272] = 0;
   out_2504363338325754815[273] = 0;
   out_2504363338325754815[274] = 0;
   out_2504363338325754815[275] = 0;
   out_2504363338325754815[276] = 0;
   out_2504363338325754815[277] = 0;
   out_2504363338325754815[278] = 0;
   out_2504363338325754815[279] = 0;
   out_2504363338325754815[280] = 0;
   out_2504363338325754815[281] = 0;
   out_2504363338325754815[282] = 0;
   out_2504363338325754815[283] = 0;
   out_2504363338325754815[284] = 0;
   out_2504363338325754815[285] = 1;
   out_2504363338325754815[286] = 0;
   out_2504363338325754815[287] = 0;
   out_2504363338325754815[288] = 0;
   out_2504363338325754815[289] = 0;
   out_2504363338325754815[290] = 0;
   out_2504363338325754815[291] = 0;
   out_2504363338325754815[292] = 0;
   out_2504363338325754815[293] = 0;
   out_2504363338325754815[294] = 0;
   out_2504363338325754815[295] = 0;
   out_2504363338325754815[296] = 0;
   out_2504363338325754815[297] = 0;
   out_2504363338325754815[298] = 0;
   out_2504363338325754815[299] = 0;
   out_2504363338325754815[300] = 0;
   out_2504363338325754815[301] = 0;
   out_2504363338325754815[302] = 0;
   out_2504363338325754815[303] = 0;
   out_2504363338325754815[304] = 1;
   out_2504363338325754815[305] = 0;
   out_2504363338325754815[306] = 0;
   out_2504363338325754815[307] = 0;
   out_2504363338325754815[308] = 0;
   out_2504363338325754815[309] = 0;
   out_2504363338325754815[310] = 0;
   out_2504363338325754815[311] = 0;
   out_2504363338325754815[312] = 0;
   out_2504363338325754815[313] = 0;
   out_2504363338325754815[314] = 0;
   out_2504363338325754815[315] = 0;
   out_2504363338325754815[316] = 0;
   out_2504363338325754815[317] = 0;
   out_2504363338325754815[318] = 0;
   out_2504363338325754815[319] = 0;
   out_2504363338325754815[320] = 0;
   out_2504363338325754815[321] = 0;
   out_2504363338325754815[322] = 0;
   out_2504363338325754815[323] = 1;
}
void h_4(double *state, double *unused, double *out_7147282312282672959) {
   out_7147282312282672959[0] = state[6] + state[9];
   out_7147282312282672959[1] = state[7] + state[10];
   out_7147282312282672959[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4897699662290384683) {
   out_4897699662290384683[0] = 0;
   out_4897699662290384683[1] = 0;
   out_4897699662290384683[2] = 0;
   out_4897699662290384683[3] = 0;
   out_4897699662290384683[4] = 0;
   out_4897699662290384683[5] = 0;
   out_4897699662290384683[6] = 1;
   out_4897699662290384683[7] = 0;
   out_4897699662290384683[8] = 0;
   out_4897699662290384683[9] = 1;
   out_4897699662290384683[10] = 0;
   out_4897699662290384683[11] = 0;
   out_4897699662290384683[12] = 0;
   out_4897699662290384683[13] = 0;
   out_4897699662290384683[14] = 0;
   out_4897699662290384683[15] = 0;
   out_4897699662290384683[16] = 0;
   out_4897699662290384683[17] = 0;
   out_4897699662290384683[18] = 0;
   out_4897699662290384683[19] = 0;
   out_4897699662290384683[20] = 0;
   out_4897699662290384683[21] = 0;
   out_4897699662290384683[22] = 0;
   out_4897699662290384683[23] = 0;
   out_4897699662290384683[24] = 0;
   out_4897699662290384683[25] = 1;
   out_4897699662290384683[26] = 0;
   out_4897699662290384683[27] = 0;
   out_4897699662290384683[28] = 1;
   out_4897699662290384683[29] = 0;
   out_4897699662290384683[30] = 0;
   out_4897699662290384683[31] = 0;
   out_4897699662290384683[32] = 0;
   out_4897699662290384683[33] = 0;
   out_4897699662290384683[34] = 0;
   out_4897699662290384683[35] = 0;
   out_4897699662290384683[36] = 0;
   out_4897699662290384683[37] = 0;
   out_4897699662290384683[38] = 0;
   out_4897699662290384683[39] = 0;
   out_4897699662290384683[40] = 0;
   out_4897699662290384683[41] = 0;
   out_4897699662290384683[42] = 0;
   out_4897699662290384683[43] = 0;
   out_4897699662290384683[44] = 1;
   out_4897699662290384683[45] = 0;
   out_4897699662290384683[46] = 0;
   out_4897699662290384683[47] = 1;
   out_4897699662290384683[48] = 0;
   out_4897699662290384683[49] = 0;
   out_4897699662290384683[50] = 0;
   out_4897699662290384683[51] = 0;
   out_4897699662290384683[52] = 0;
   out_4897699662290384683[53] = 0;
}
void h_10(double *state, double *unused, double *out_9130545523462966991) {
   out_9130545523462966991[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_9130545523462966991[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_9130545523462966991[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6830444104489603573) {
   out_6830444104489603573[0] = 0;
   out_6830444104489603573[1] = 9.8100000000000005*cos(state[1]);
   out_6830444104489603573[2] = 0;
   out_6830444104489603573[3] = 0;
   out_6830444104489603573[4] = -state[8];
   out_6830444104489603573[5] = state[7];
   out_6830444104489603573[6] = 0;
   out_6830444104489603573[7] = state[5];
   out_6830444104489603573[8] = -state[4];
   out_6830444104489603573[9] = 0;
   out_6830444104489603573[10] = 0;
   out_6830444104489603573[11] = 0;
   out_6830444104489603573[12] = 1;
   out_6830444104489603573[13] = 0;
   out_6830444104489603573[14] = 0;
   out_6830444104489603573[15] = 1;
   out_6830444104489603573[16] = 0;
   out_6830444104489603573[17] = 0;
   out_6830444104489603573[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6830444104489603573[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6830444104489603573[20] = 0;
   out_6830444104489603573[21] = state[8];
   out_6830444104489603573[22] = 0;
   out_6830444104489603573[23] = -state[6];
   out_6830444104489603573[24] = -state[5];
   out_6830444104489603573[25] = 0;
   out_6830444104489603573[26] = state[3];
   out_6830444104489603573[27] = 0;
   out_6830444104489603573[28] = 0;
   out_6830444104489603573[29] = 0;
   out_6830444104489603573[30] = 0;
   out_6830444104489603573[31] = 1;
   out_6830444104489603573[32] = 0;
   out_6830444104489603573[33] = 0;
   out_6830444104489603573[34] = 1;
   out_6830444104489603573[35] = 0;
   out_6830444104489603573[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6830444104489603573[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6830444104489603573[38] = 0;
   out_6830444104489603573[39] = -state[7];
   out_6830444104489603573[40] = state[6];
   out_6830444104489603573[41] = 0;
   out_6830444104489603573[42] = state[4];
   out_6830444104489603573[43] = -state[3];
   out_6830444104489603573[44] = 0;
   out_6830444104489603573[45] = 0;
   out_6830444104489603573[46] = 0;
   out_6830444104489603573[47] = 0;
   out_6830444104489603573[48] = 0;
   out_6830444104489603573[49] = 0;
   out_6830444104489603573[50] = 1;
   out_6830444104489603573[51] = 0;
   out_6830444104489603573[52] = 0;
   out_6830444104489603573[53] = 1;
}
void h_13(double *state, double *unused, double *out_6263563644976026350) {
   out_6263563644976026350[0] = state[3];
   out_6263563644976026350[1] = state[4];
   out_6263563644976026350[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1685425836958051882) {
   out_1685425836958051882[0] = 0;
   out_1685425836958051882[1] = 0;
   out_1685425836958051882[2] = 0;
   out_1685425836958051882[3] = 1;
   out_1685425836958051882[4] = 0;
   out_1685425836958051882[5] = 0;
   out_1685425836958051882[6] = 0;
   out_1685425836958051882[7] = 0;
   out_1685425836958051882[8] = 0;
   out_1685425836958051882[9] = 0;
   out_1685425836958051882[10] = 0;
   out_1685425836958051882[11] = 0;
   out_1685425836958051882[12] = 0;
   out_1685425836958051882[13] = 0;
   out_1685425836958051882[14] = 0;
   out_1685425836958051882[15] = 0;
   out_1685425836958051882[16] = 0;
   out_1685425836958051882[17] = 0;
   out_1685425836958051882[18] = 0;
   out_1685425836958051882[19] = 0;
   out_1685425836958051882[20] = 0;
   out_1685425836958051882[21] = 0;
   out_1685425836958051882[22] = 1;
   out_1685425836958051882[23] = 0;
   out_1685425836958051882[24] = 0;
   out_1685425836958051882[25] = 0;
   out_1685425836958051882[26] = 0;
   out_1685425836958051882[27] = 0;
   out_1685425836958051882[28] = 0;
   out_1685425836958051882[29] = 0;
   out_1685425836958051882[30] = 0;
   out_1685425836958051882[31] = 0;
   out_1685425836958051882[32] = 0;
   out_1685425836958051882[33] = 0;
   out_1685425836958051882[34] = 0;
   out_1685425836958051882[35] = 0;
   out_1685425836958051882[36] = 0;
   out_1685425836958051882[37] = 0;
   out_1685425836958051882[38] = 0;
   out_1685425836958051882[39] = 0;
   out_1685425836958051882[40] = 0;
   out_1685425836958051882[41] = 1;
   out_1685425836958051882[42] = 0;
   out_1685425836958051882[43] = 0;
   out_1685425836958051882[44] = 0;
   out_1685425836958051882[45] = 0;
   out_1685425836958051882[46] = 0;
   out_1685425836958051882[47] = 0;
   out_1685425836958051882[48] = 0;
   out_1685425836958051882[49] = 0;
   out_1685425836958051882[50] = 0;
   out_1685425836958051882[51] = 0;
   out_1685425836958051882[52] = 0;
   out_1685425836958051882[53] = 0;
}
void h_14(double *state, double *unused, double *out_5438998319357703596) {
   out_5438998319357703596[0] = state[6];
   out_5438998319357703596[1] = state[7];
   out_5438998319357703596[2] = state[8];
}
void H_14(double *state, double *unused, double *out_934458805950900154) {
   out_934458805950900154[0] = 0;
   out_934458805950900154[1] = 0;
   out_934458805950900154[2] = 0;
   out_934458805950900154[3] = 0;
   out_934458805950900154[4] = 0;
   out_934458805950900154[5] = 0;
   out_934458805950900154[6] = 1;
   out_934458805950900154[7] = 0;
   out_934458805950900154[8] = 0;
   out_934458805950900154[9] = 0;
   out_934458805950900154[10] = 0;
   out_934458805950900154[11] = 0;
   out_934458805950900154[12] = 0;
   out_934458805950900154[13] = 0;
   out_934458805950900154[14] = 0;
   out_934458805950900154[15] = 0;
   out_934458805950900154[16] = 0;
   out_934458805950900154[17] = 0;
   out_934458805950900154[18] = 0;
   out_934458805950900154[19] = 0;
   out_934458805950900154[20] = 0;
   out_934458805950900154[21] = 0;
   out_934458805950900154[22] = 0;
   out_934458805950900154[23] = 0;
   out_934458805950900154[24] = 0;
   out_934458805950900154[25] = 1;
   out_934458805950900154[26] = 0;
   out_934458805950900154[27] = 0;
   out_934458805950900154[28] = 0;
   out_934458805950900154[29] = 0;
   out_934458805950900154[30] = 0;
   out_934458805950900154[31] = 0;
   out_934458805950900154[32] = 0;
   out_934458805950900154[33] = 0;
   out_934458805950900154[34] = 0;
   out_934458805950900154[35] = 0;
   out_934458805950900154[36] = 0;
   out_934458805950900154[37] = 0;
   out_934458805950900154[38] = 0;
   out_934458805950900154[39] = 0;
   out_934458805950900154[40] = 0;
   out_934458805950900154[41] = 0;
   out_934458805950900154[42] = 0;
   out_934458805950900154[43] = 0;
   out_934458805950900154[44] = 1;
   out_934458805950900154[45] = 0;
   out_934458805950900154[46] = 0;
   out_934458805950900154[47] = 0;
   out_934458805950900154[48] = 0;
   out_934458805950900154[49] = 0;
   out_934458805950900154[50] = 0;
   out_934458805950900154[51] = 0;
   out_934458805950900154[52] = 0;
   out_934458805950900154[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1246780800306708420) {
  err_fun(nom_x, delta_x, out_1246780800306708420);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_322701955714434799) {
  inv_err_fun(nom_x, true_x, out_322701955714434799);
}
void pose_H_mod_fun(double *state, double *out_950382144461574038) {
  H_mod_fun(state, out_950382144461574038);
}
void pose_f_fun(double *state, double dt, double *out_5588529265753131833) {
  f_fun(state,  dt, out_5588529265753131833);
}
void pose_F_fun(double *state, double dt, double *out_2504363338325754815) {
  F_fun(state,  dt, out_2504363338325754815);
}
void pose_h_4(double *state, double *unused, double *out_7147282312282672959) {
  h_4(state, unused, out_7147282312282672959);
}
void pose_H_4(double *state, double *unused, double *out_4897699662290384683) {
  H_4(state, unused, out_4897699662290384683);
}
void pose_h_10(double *state, double *unused, double *out_9130545523462966991) {
  h_10(state, unused, out_9130545523462966991);
}
void pose_H_10(double *state, double *unused, double *out_6830444104489603573) {
  H_10(state, unused, out_6830444104489603573);
}
void pose_h_13(double *state, double *unused, double *out_6263563644976026350) {
  h_13(state, unused, out_6263563644976026350);
}
void pose_H_13(double *state, double *unused, double *out_1685425836958051882) {
  H_13(state, unused, out_1685425836958051882);
}
void pose_h_14(double *state, double *unused, double *out_5438998319357703596) {
  h_14(state, unused, out_5438998319357703596);
}
void pose_H_14(double *state, double *unused, double *out_934458805950900154) {
  H_14(state, unused, out_934458805950900154);
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
