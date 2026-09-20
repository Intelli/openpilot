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
void err_fun(double *nom_x, double *delta_x, double *out_8838830420648207010) {
   out_8838830420648207010[0] = delta_x[0] + nom_x[0];
   out_8838830420648207010[1] = delta_x[1] + nom_x[1];
   out_8838830420648207010[2] = delta_x[2] + nom_x[2];
   out_8838830420648207010[3] = delta_x[3] + nom_x[3];
   out_8838830420648207010[4] = delta_x[4] + nom_x[4];
   out_8838830420648207010[5] = delta_x[5] + nom_x[5];
   out_8838830420648207010[6] = delta_x[6] + nom_x[6];
   out_8838830420648207010[7] = delta_x[7] + nom_x[7];
   out_8838830420648207010[8] = delta_x[8] + nom_x[8];
   out_8838830420648207010[9] = delta_x[9] + nom_x[9];
   out_8838830420648207010[10] = delta_x[10] + nom_x[10];
   out_8838830420648207010[11] = delta_x[11] + nom_x[11];
   out_8838830420648207010[12] = delta_x[12] + nom_x[12];
   out_8838830420648207010[13] = delta_x[13] + nom_x[13];
   out_8838830420648207010[14] = delta_x[14] + nom_x[14];
   out_8838830420648207010[15] = delta_x[15] + nom_x[15];
   out_8838830420648207010[16] = delta_x[16] + nom_x[16];
   out_8838830420648207010[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2885477467670563304) {
   out_2885477467670563304[0] = -nom_x[0] + true_x[0];
   out_2885477467670563304[1] = -nom_x[1] + true_x[1];
   out_2885477467670563304[2] = -nom_x[2] + true_x[2];
   out_2885477467670563304[3] = -nom_x[3] + true_x[3];
   out_2885477467670563304[4] = -nom_x[4] + true_x[4];
   out_2885477467670563304[5] = -nom_x[5] + true_x[5];
   out_2885477467670563304[6] = -nom_x[6] + true_x[6];
   out_2885477467670563304[7] = -nom_x[7] + true_x[7];
   out_2885477467670563304[8] = -nom_x[8] + true_x[8];
   out_2885477467670563304[9] = -nom_x[9] + true_x[9];
   out_2885477467670563304[10] = -nom_x[10] + true_x[10];
   out_2885477467670563304[11] = -nom_x[11] + true_x[11];
   out_2885477467670563304[12] = -nom_x[12] + true_x[12];
   out_2885477467670563304[13] = -nom_x[13] + true_x[13];
   out_2885477467670563304[14] = -nom_x[14] + true_x[14];
   out_2885477467670563304[15] = -nom_x[15] + true_x[15];
   out_2885477467670563304[16] = -nom_x[16] + true_x[16];
   out_2885477467670563304[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7096528025583759202) {
   out_7096528025583759202[0] = 1.0;
   out_7096528025583759202[1] = 0.0;
   out_7096528025583759202[2] = 0.0;
   out_7096528025583759202[3] = 0.0;
   out_7096528025583759202[4] = 0.0;
   out_7096528025583759202[5] = 0.0;
   out_7096528025583759202[6] = 0.0;
   out_7096528025583759202[7] = 0.0;
   out_7096528025583759202[8] = 0.0;
   out_7096528025583759202[9] = 0.0;
   out_7096528025583759202[10] = 0.0;
   out_7096528025583759202[11] = 0.0;
   out_7096528025583759202[12] = 0.0;
   out_7096528025583759202[13] = 0.0;
   out_7096528025583759202[14] = 0.0;
   out_7096528025583759202[15] = 0.0;
   out_7096528025583759202[16] = 0.0;
   out_7096528025583759202[17] = 0.0;
   out_7096528025583759202[18] = 0.0;
   out_7096528025583759202[19] = 1.0;
   out_7096528025583759202[20] = 0.0;
   out_7096528025583759202[21] = 0.0;
   out_7096528025583759202[22] = 0.0;
   out_7096528025583759202[23] = 0.0;
   out_7096528025583759202[24] = 0.0;
   out_7096528025583759202[25] = 0.0;
   out_7096528025583759202[26] = 0.0;
   out_7096528025583759202[27] = 0.0;
   out_7096528025583759202[28] = 0.0;
   out_7096528025583759202[29] = 0.0;
   out_7096528025583759202[30] = 0.0;
   out_7096528025583759202[31] = 0.0;
   out_7096528025583759202[32] = 0.0;
   out_7096528025583759202[33] = 0.0;
   out_7096528025583759202[34] = 0.0;
   out_7096528025583759202[35] = 0.0;
   out_7096528025583759202[36] = 0.0;
   out_7096528025583759202[37] = 0.0;
   out_7096528025583759202[38] = 1.0;
   out_7096528025583759202[39] = 0.0;
   out_7096528025583759202[40] = 0.0;
   out_7096528025583759202[41] = 0.0;
   out_7096528025583759202[42] = 0.0;
   out_7096528025583759202[43] = 0.0;
   out_7096528025583759202[44] = 0.0;
   out_7096528025583759202[45] = 0.0;
   out_7096528025583759202[46] = 0.0;
   out_7096528025583759202[47] = 0.0;
   out_7096528025583759202[48] = 0.0;
   out_7096528025583759202[49] = 0.0;
   out_7096528025583759202[50] = 0.0;
   out_7096528025583759202[51] = 0.0;
   out_7096528025583759202[52] = 0.0;
   out_7096528025583759202[53] = 0.0;
   out_7096528025583759202[54] = 0.0;
   out_7096528025583759202[55] = 0.0;
   out_7096528025583759202[56] = 0.0;
   out_7096528025583759202[57] = 1.0;
   out_7096528025583759202[58] = 0.0;
   out_7096528025583759202[59] = 0.0;
   out_7096528025583759202[60] = 0.0;
   out_7096528025583759202[61] = 0.0;
   out_7096528025583759202[62] = 0.0;
   out_7096528025583759202[63] = 0.0;
   out_7096528025583759202[64] = 0.0;
   out_7096528025583759202[65] = 0.0;
   out_7096528025583759202[66] = 0.0;
   out_7096528025583759202[67] = 0.0;
   out_7096528025583759202[68] = 0.0;
   out_7096528025583759202[69] = 0.0;
   out_7096528025583759202[70] = 0.0;
   out_7096528025583759202[71] = 0.0;
   out_7096528025583759202[72] = 0.0;
   out_7096528025583759202[73] = 0.0;
   out_7096528025583759202[74] = 0.0;
   out_7096528025583759202[75] = 0.0;
   out_7096528025583759202[76] = 1.0;
   out_7096528025583759202[77] = 0.0;
   out_7096528025583759202[78] = 0.0;
   out_7096528025583759202[79] = 0.0;
   out_7096528025583759202[80] = 0.0;
   out_7096528025583759202[81] = 0.0;
   out_7096528025583759202[82] = 0.0;
   out_7096528025583759202[83] = 0.0;
   out_7096528025583759202[84] = 0.0;
   out_7096528025583759202[85] = 0.0;
   out_7096528025583759202[86] = 0.0;
   out_7096528025583759202[87] = 0.0;
   out_7096528025583759202[88] = 0.0;
   out_7096528025583759202[89] = 0.0;
   out_7096528025583759202[90] = 0.0;
   out_7096528025583759202[91] = 0.0;
   out_7096528025583759202[92] = 0.0;
   out_7096528025583759202[93] = 0.0;
   out_7096528025583759202[94] = 0.0;
   out_7096528025583759202[95] = 1.0;
   out_7096528025583759202[96] = 0.0;
   out_7096528025583759202[97] = 0.0;
   out_7096528025583759202[98] = 0.0;
   out_7096528025583759202[99] = 0.0;
   out_7096528025583759202[100] = 0.0;
   out_7096528025583759202[101] = 0.0;
   out_7096528025583759202[102] = 0.0;
   out_7096528025583759202[103] = 0.0;
   out_7096528025583759202[104] = 0.0;
   out_7096528025583759202[105] = 0.0;
   out_7096528025583759202[106] = 0.0;
   out_7096528025583759202[107] = 0.0;
   out_7096528025583759202[108] = 0.0;
   out_7096528025583759202[109] = 0.0;
   out_7096528025583759202[110] = 0.0;
   out_7096528025583759202[111] = 0.0;
   out_7096528025583759202[112] = 0.0;
   out_7096528025583759202[113] = 0.0;
   out_7096528025583759202[114] = 1.0;
   out_7096528025583759202[115] = 0.0;
   out_7096528025583759202[116] = 0.0;
   out_7096528025583759202[117] = 0.0;
   out_7096528025583759202[118] = 0.0;
   out_7096528025583759202[119] = 0.0;
   out_7096528025583759202[120] = 0.0;
   out_7096528025583759202[121] = 0.0;
   out_7096528025583759202[122] = 0.0;
   out_7096528025583759202[123] = 0.0;
   out_7096528025583759202[124] = 0.0;
   out_7096528025583759202[125] = 0.0;
   out_7096528025583759202[126] = 0.0;
   out_7096528025583759202[127] = 0.0;
   out_7096528025583759202[128] = 0.0;
   out_7096528025583759202[129] = 0.0;
   out_7096528025583759202[130] = 0.0;
   out_7096528025583759202[131] = 0.0;
   out_7096528025583759202[132] = 0.0;
   out_7096528025583759202[133] = 1.0;
   out_7096528025583759202[134] = 0.0;
   out_7096528025583759202[135] = 0.0;
   out_7096528025583759202[136] = 0.0;
   out_7096528025583759202[137] = 0.0;
   out_7096528025583759202[138] = 0.0;
   out_7096528025583759202[139] = 0.0;
   out_7096528025583759202[140] = 0.0;
   out_7096528025583759202[141] = 0.0;
   out_7096528025583759202[142] = 0.0;
   out_7096528025583759202[143] = 0.0;
   out_7096528025583759202[144] = 0.0;
   out_7096528025583759202[145] = 0.0;
   out_7096528025583759202[146] = 0.0;
   out_7096528025583759202[147] = 0.0;
   out_7096528025583759202[148] = 0.0;
   out_7096528025583759202[149] = 0.0;
   out_7096528025583759202[150] = 0.0;
   out_7096528025583759202[151] = 0.0;
   out_7096528025583759202[152] = 1.0;
   out_7096528025583759202[153] = 0.0;
   out_7096528025583759202[154] = 0.0;
   out_7096528025583759202[155] = 0.0;
   out_7096528025583759202[156] = 0.0;
   out_7096528025583759202[157] = 0.0;
   out_7096528025583759202[158] = 0.0;
   out_7096528025583759202[159] = 0.0;
   out_7096528025583759202[160] = 0.0;
   out_7096528025583759202[161] = 0.0;
   out_7096528025583759202[162] = 0.0;
   out_7096528025583759202[163] = 0.0;
   out_7096528025583759202[164] = 0.0;
   out_7096528025583759202[165] = 0.0;
   out_7096528025583759202[166] = 0.0;
   out_7096528025583759202[167] = 0.0;
   out_7096528025583759202[168] = 0.0;
   out_7096528025583759202[169] = 0.0;
   out_7096528025583759202[170] = 0.0;
   out_7096528025583759202[171] = 1.0;
   out_7096528025583759202[172] = 0.0;
   out_7096528025583759202[173] = 0.0;
   out_7096528025583759202[174] = 0.0;
   out_7096528025583759202[175] = 0.0;
   out_7096528025583759202[176] = 0.0;
   out_7096528025583759202[177] = 0.0;
   out_7096528025583759202[178] = 0.0;
   out_7096528025583759202[179] = 0.0;
   out_7096528025583759202[180] = 0.0;
   out_7096528025583759202[181] = 0.0;
   out_7096528025583759202[182] = 0.0;
   out_7096528025583759202[183] = 0.0;
   out_7096528025583759202[184] = 0.0;
   out_7096528025583759202[185] = 0.0;
   out_7096528025583759202[186] = 0.0;
   out_7096528025583759202[187] = 0.0;
   out_7096528025583759202[188] = 0.0;
   out_7096528025583759202[189] = 0.0;
   out_7096528025583759202[190] = 1.0;
   out_7096528025583759202[191] = 0.0;
   out_7096528025583759202[192] = 0.0;
   out_7096528025583759202[193] = 0.0;
   out_7096528025583759202[194] = 0.0;
   out_7096528025583759202[195] = 0.0;
   out_7096528025583759202[196] = 0.0;
   out_7096528025583759202[197] = 0.0;
   out_7096528025583759202[198] = 0.0;
   out_7096528025583759202[199] = 0.0;
   out_7096528025583759202[200] = 0.0;
   out_7096528025583759202[201] = 0.0;
   out_7096528025583759202[202] = 0.0;
   out_7096528025583759202[203] = 0.0;
   out_7096528025583759202[204] = 0.0;
   out_7096528025583759202[205] = 0.0;
   out_7096528025583759202[206] = 0.0;
   out_7096528025583759202[207] = 0.0;
   out_7096528025583759202[208] = 0.0;
   out_7096528025583759202[209] = 1.0;
   out_7096528025583759202[210] = 0.0;
   out_7096528025583759202[211] = 0.0;
   out_7096528025583759202[212] = 0.0;
   out_7096528025583759202[213] = 0.0;
   out_7096528025583759202[214] = 0.0;
   out_7096528025583759202[215] = 0.0;
   out_7096528025583759202[216] = 0.0;
   out_7096528025583759202[217] = 0.0;
   out_7096528025583759202[218] = 0.0;
   out_7096528025583759202[219] = 0.0;
   out_7096528025583759202[220] = 0.0;
   out_7096528025583759202[221] = 0.0;
   out_7096528025583759202[222] = 0.0;
   out_7096528025583759202[223] = 0.0;
   out_7096528025583759202[224] = 0.0;
   out_7096528025583759202[225] = 0.0;
   out_7096528025583759202[226] = 0.0;
   out_7096528025583759202[227] = 0.0;
   out_7096528025583759202[228] = 1.0;
   out_7096528025583759202[229] = 0.0;
   out_7096528025583759202[230] = 0.0;
   out_7096528025583759202[231] = 0.0;
   out_7096528025583759202[232] = 0.0;
   out_7096528025583759202[233] = 0.0;
   out_7096528025583759202[234] = 0.0;
   out_7096528025583759202[235] = 0.0;
   out_7096528025583759202[236] = 0.0;
   out_7096528025583759202[237] = 0.0;
   out_7096528025583759202[238] = 0.0;
   out_7096528025583759202[239] = 0.0;
   out_7096528025583759202[240] = 0.0;
   out_7096528025583759202[241] = 0.0;
   out_7096528025583759202[242] = 0.0;
   out_7096528025583759202[243] = 0.0;
   out_7096528025583759202[244] = 0.0;
   out_7096528025583759202[245] = 0.0;
   out_7096528025583759202[246] = 0.0;
   out_7096528025583759202[247] = 1.0;
   out_7096528025583759202[248] = 0.0;
   out_7096528025583759202[249] = 0.0;
   out_7096528025583759202[250] = 0.0;
   out_7096528025583759202[251] = 0.0;
   out_7096528025583759202[252] = 0.0;
   out_7096528025583759202[253] = 0.0;
   out_7096528025583759202[254] = 0.0;
   out_7096528025583759202[255] = 0.0;
   out_7096528025583759202[256] = 0.0;
   out_7096528025583759202[257] = 0.0;
   out_7096528025583759202[258] = 0.0;
   out_7096528025583759202[259] = 0.0;
   out_7096528025583759202[260] = 0.0;
   out_7096528025583759202[261] = 0.0;
   out_7096528025583759202[262] = 0.0;
   out_7096528025583759202[263] = 0.0;
   out_7096528025583759202[264] = 0.0;
   out_7096528025583759202[265] = 0.0;
   out_7096528025583759202[266] = 1.0;
   out_7096528025583759202[267] = 0.0;
   out_7096528025583759202[268] = 0.0;
   out_7096528025583759202[269] = 0.0;
   out_7096528025583759202[270] = 0.0;
   out_7096528025583759202[271] = 0.0;
   out_7096528025583759202[272] = 0.0;
   out_7096528025583759202[273] = 0.0;
   out_7096528025583759202[274] = 0.0;
   out_7096528025583759202[275] = 0.0;
   out_7096528025583759202[276] = 0.0;
   out_7096528025583759202[277] = 0.0;
   out_7096528025583759202[278] = 0.0;
   out_7096528025583759202[279] = 0.0;
   out_7096528025583759202[280] = 0.0;
   out_7096528025583759202[281] = 0.0;
   out_7096528025583759202[282] = 0.0;
   out_7096528025583759202[283] = 0.0;
   out_7096528025583759202[284] = 0.0;
   out_7096528025583759202[285] = 1.0;
   out_7096528025583759202[286] = 0.0;
   out_7096528025583759202[287] = 0.0;
   out_7096528025583759202[288] = 0.0;
   out_7096528025583759202[289] = 0.0;
   out_7096528025583759202[290] = 0.0;
   out_7096528025583759202[291] = 0.0;
   out_7096528025583759202[292] = 0.0;
   out_7096528025583759202[293] = 0.0;
   out_7096528025583759202[294] = 0.0;
   out_7096528025583759202[295] = 0.0;
   out_7096528025583759202[296] = 0.0;
   out_7096528025583759202[297] = 0.0;
   out_7096528025583759202[298] = 0.0;
   out_7096528025583759202[299] = 0.0;
   out_7096528025583759202[300] = 0.0;
   out_7096528025583759202[301] = 0.0;
   out_7096528025583759202[302] = 0.0;
   out_7096528025583759202[303] = 0.0;
   out_7096528025583759202[304] = 1.0;
   out_7096528025583759202[305] = 0.0;
   out_7096528025583759202[306] = 0.0;
   out_7096528025583759202[307] = 0.0;
   out_7096528025583759202[308] = 0.0;
   out_7096528025583759202[309] = 0.0;
   out_7096528025583759202[310] = 0.0;
   out_7096528025583759202[311] = 0.0;
   out_7096528025583759202[312] = 0.0;
   out_7096528025583759202[313] = 0.0;
   out_7096528025583759202[314] = 0.0;
   out_7096528025583759202[315] = 0.0;
   out_7096528025583759202[316] = 0.0;
   out_7096528025583759202[317] = 0.0;
   out_7096528025583759202[318] = 0.0;
   out_7096528025583759202[319] = 0.0;
   out_7096528025583759202[320] = 0.0;
   out_7096528025583759202[321] = 0.0;
   out_7096528025583759202[322] = 0.0;
   out_7096528025583759202[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8038070982033161577) {
   out_8038070982033161577[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8038070982033161577[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8038070982033161577[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8038070982033161577[3] = dt*state[12] + state[3];
   out_8038070982033161577[4] = dt*state[13] + state[4];
   out_8038070982033161577[5] = dt*state[14] + state[5];
   out_8038070982033161577[6] = state[6];
   out_8038070982033161577[7] = state[7];
   out_8038070982033161577[8] = state[8];
   out_8038070982033161577[9] = state[9];
   out_8038070982033161577[10] = state[10];
   out_8038070982033161577[11] = state[11];
   out_8038070982033161577[12] = state[12];
   out_8038070982033161577[13] = state[13];
   out_8038070982033161577[14] = state[14];
   out_8038070982033161577[15] = state[15];
   out_8038070982033161577[16] = state[16];
   out_8038070982033161577[17] = state[17];
}
void F_fun(double *state, double dt, double *out_794702288486851768) {
   out_794702288486851768[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_794702288486851768[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_794702288486851768[2] = 0;
   out_794702288486851768[3] = 0;
   out_794702288486851768[4] = 0;
   out_794702288486851768[5] = 0;
   out_794702288486851768[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_794702288486851768[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_794702288486851768[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_794702288486851768[9] = 0;
   out_794702288486851768[10] = 0;
   out_794702288486851768[11] = 0;
   out_794702288486851768[12] = 0;
   out_794702288486851768[13] = 0;
   out_794702288486851768[14] = 0;
   out_794702288486851768[15] = 0;
   out_794702288486851768[16] = 0;
   out_794702288486851768[17] = 0;
   out_794702288486851768[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_794702288486851768[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_794702288486851768[20] = 0;
   out_794702288486851768[21] = 0;
   out_794702288486851768[22] = 0;
   out_794702288486851768[23] = 0;
   out_794702288486851768[24] = 0;
   out_794702288486851768[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_794702288486851768[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_794702288486851768[27] = 0;
   out_794702288486851768[28] = 0;
   out_794702288486851768[29] = 0;
   out_794702288486851768[30] = 0;
   out_794702288486851768[31] = 0;
   out_794702288486851768[32] = 0;
   out_794702288486851768[33] = 0;
   out_794702288486851768[34] = 0;
   out_794702288486851768[35] = 0;
   out_794702288486851768[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_794702288486851768[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_794702288486851768[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_794702288486851768[39] = 0;
   out_794702288486851768[40] = 0;
   out_794702288486851768[41] = 0;
   out_794702288486851768[42] = 0;
   out_794702288486851768[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_794702288486851768[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_794702288486851768[45] = 0;
   out_794702288486851768[46] = 0;
   out_794702288486851768[47] = 0;
   out_794702288486851768[48] = 0;
   out_794702288486851768[49] = 0;
   out_794702288486851768[50] = 0;
   out_794702288486851768[51] = 0;
   out_794702288486851768[52] = 0;
   out_794702288486851768[53] = 0;
   out_794702288486851768[54] = 0;
   out_794702288486851768[55] = 0;
   out_794702288486851768[56] = 0;
   out_794702288486851768[57] = 1;
   out_794702288486851768[58] = 0;
   out_794702288486851768[59] = 0;
   out_794702288486851768[60] = 0;
   out_794702288486851768[61] = 0;
   out_794702288486851768[62] = 0;
   out_794702288486851768[63] = 0;
   out_794702288486851768[64] = 0;
   out_794702288486851768[65] = 0;
   out_794702288486851768[66] = dt;
   out_794702288486851768[67] = 0;
   out_794702288486851768[68] = 0;
   out_794702288486851768[69] = 0;
   out_794702288486851768[70] = 0;
   out_794702288486851768[71] = 0;
   out_794702288486851768[72] = 0;
   out_794702288486851768[73] = 0;
   out_794702288486851768[74] = 0;
   out_794702288486851768[75] = 0;
   out_794702288486851768[76] = 1;
   out_794702288486851768[77] = 0;
   out_794702288486851768[78] = 0;
   out_794702288486851768[79] = 0;
   out_794702288486851768[80] = 0;
   out_794702288486851768[81] = 0;
   out_794702288486851768[82] = 0;
   out_794702288486851768[83] = 0;
   out_794702288486851768[84] = 0;
   out_794702288486851768[85] = dt;
   out_794702288486851768[86] = 0;
   out_794702288486851768[87] = 0;
   out_794702288486851768[88] = 0;
   out_794702288486851768[89] = 0;
   out_794702288486851768[90] = 0;
   out_794702288486851768[91] = 0;
   out_794702288486851768[92] = 0;
   out_794702288486851768[93] = 0;
   out_794702288486851768[94] = 0;
   out_794702288486851768[95] = 1;
   out_794702288486851768[96] = 0;
   out_794702288486851768[97] = 0;
   out_794702288486851768[98] = 0;
   out_794702288486851768[99] = 0;
   out_794702288486851768[100] = 0;
   out_794702288486851768[101] = 0;
   out_794702288486851768[102] = 0;
   out_794702288486851768[103] = 0;
   out_794702288486851768[104] = dt;
   out_794702288486851768[105] = 0;
   out_794702288486851768[106] = 0;
   out_794702288486851768[107] = 0;
   out_794702288486851768[108] = 0;
   out_794702288486851768[109] = 0;
   out_794702288486851768[110] = 0;
   out_794702288486851768[111] = 0;
   out_794702288486851768[112] = 0;
   out_794702288486851768[113] = 0;
   out_794702288486851768[114] = 1;
   out_794702288486851768[115] = 0;
   out_794702288486851768[116] = 0;
   out_794702288486851768[117] = 0;
   out_794702288486851768[118] = 0;
   out_794702288486851768[119] = 0;
   out_794702288486851768[120] = 0;
   out_794702288486851768[121] = 0;
   out_794702288486851768[122] = 0;
   out_794702288486851768[123] = 0;
   out_794702288486851768[124] = 0;
   out_794702288486851768[125] = 0;
   out_794702288486851768[126] = 0;
   out_794702288486851768[127] = 0;
   out_794702288486851768[128] = 0;
   out_794702288486851768[129] = 0;
   out_794702288486851768[130] = 0;
   out_794702288486851768[131] = 0;
   out_794702288486851768[132] = 0;
   out_794702288486851768[133] = 1;
   out_794702288486851768[134] = 0;
   out_794702288486851768[135] = 0;
   out_794702288486851768[136] = 0;
   out_794702288486851768[137] = 0;
   out_794702288486851768[138] = 0;
   out_794702288486851768[139] = 0;
   out_794702288486851768[140] = 0;
   out_794702288486851768[141] = 0;
   out_794702288486851768[142] = 0;
   out_794702288486851768[143] = 0;
   out_794702288486851768[144] = 0;
   out_794702288486851768[145] = 0;
   out_794702288486851768[146] = 0;
   out_794702288486851768[147] = 0;
   out_794702288486851768[148] = 0;
   out_794702288486851768[149] = 0;
   out_794702288486851768[150] = 0;
   out_794702288486851768[151] = 0;
   out_794702288486851768[152] = 1;
   out_794702288486851768[153] = 0;
   out_794702288486851768[154] = 0;
   out_794702288486851768[155] = 0;
   out_794702288486851768[156] = 0;
   out_794702288486851768[157] = 0;
   out_794702288486851768[158] = 0;
   out_794702288486851768[159] = 0;
   out_794702288486851768[160] = 0;
   out_794702288486851768[161] = 0;
   out_794702288486851768[162] = 0;
   out_794702288486851768[163] = 0;
   out_794702288486851768[164] = 0;
   out_794702288486851768[165] = 0;
   out_794702288486851768[166] = 0;
   out_794702288486851768[167] = 0;
   out_794702288486851768[168] = 0;
   out_794702288486851768[169] = 0;
   out_794702288486851768[170] = 0;
   out_794702288486851768[171] = 1;
   out_794702288486851768[172] = 0;
   out_794702288486851768[173] = 0;
   out_794702288486851768[174] = 0;
   out_794702288486851768[175] = 0;
   out_794702288486851768[176] = 0;
   out_794702288486851768[177] = 0;
   out_794702288486851768[178] = 0;
   out_794702288486851768[179] = 0;
   out_794702288486851768[180] = 0;
   out_794702288486851768[181] = 0;
   out_794702288486851768[182] = 0;
   out_794702288486851768[183] = 0;
   out_794702288486851768[184] = 0;
   out_794702288486851768[185] = 0;
   out_794702288486851768[186] = 0;
   out_794702288486851768[187] = 0;
   out_794702288486851768[188] = 0;
   out_794702288486851768[189] = 0;
   out_794702288486851768[190] = 1;
   out_794702288486851768[191] = 0;
   out_794702288486851768[192] = 0;
   out_794702288486851768[193] = 0;
   out_794702288486851768[194] = 0;
   out_794702288486851768[195] = 0;
   out_794702288486851768[196] = 0;
   out_794702288486851768[197] = 0;
   out_794702288486851768[198] = 0;
   out_794702288486851768[199] = 0;
   out_794702288486851768[200] = 0;
   out_794702288486851768[201] = 0;
   out_794702288486851768[202] = 0;
   out_794702288486851768[203] = 0;
   out_794702288486851768[204] = 0;
   out_794702288486851768[205] = 0;
   out_794702288486851768[206] = 0;
   out_794702288486851768[207] = 0;
   out_794702288486851768[208] = 0;
   out_794702288486851768[209] = 1;
   out_794702288486851768[210] = 0;
   out_794702288486851768[211] = 0;
   out_794702288486851768[212] = 0;
   out_794702288486851768[213] = 0;
   out_794702288486851768[214] = 0;
   out_794702288486851768[215] = 0;
   out_794702288486851768[216] = 0;
   out_794702288486851768[217] = 0;
   out_794702288486851768[218] = 0;
   out_794702288486851768[219] = 0;
   out_794702288486851768[220] = 0;
   out_794702288486851768[221] = 0;
   out_794702288486851768[222] = 0;
   out_794702288486851768[223] = 0;
   out_794702288486851768[224] = 0;
   out_794702288486851768[225] = 0;
   out_794702288486851768[226] = 0;
   out_794702288486851768[227] = 0;
   out_794702288486851768[228] = 1;
   out_794702288486851768[229] = 0;
   out_794702288486851768[230] = 0;
   out_794702288486851768[231] = 0;
   out_794702288486851768[232] = 0;
   out_794702288486851768[233] = 0;
   out_794702288486851768[234] = 0;
   out_794702288486851768[235] = 0;
   out_794702288486851768[236] = 0;
   out_794702288486851768[237] = 0;
   out_794702288486851768[238] = 0;
   out_794702288486851768[239] = 0;
   out_794702288486851768[240] = 0;
   out_794702288486851768[241] = 0;
   out_794702288486851768[242] = 0;
   out_794702288486851768[243] = 0;
   out_794702288486851768[244] = 0;
   out_794702288486851768[245] = 0;
   out_794702288486851768[246] = 0;
   out_794702288486851768[247] = 1;
   out_794702288486851768[248] = 0;
   out_794702288486851768[249] = 0;
   out_794702288486851768[250] = 0;
   out_794702288486851768[251] = 0;
   out_794702288486851768[252] = 0;
   out_794702288486851768[253] = 0;
   out_794702288486851768[254] = 0;
   out_794702288486851768[255] = 0;
   out_794702288486851768[256] = 0;
   out_794702288486851768[257] = 0;
   out_794702288486851768[258] = 0;
   out_794702288486851768[259] = 0;
   out_794702288486851768[260] = 0;
   out_794702288486851768[261] = 0;
   out_794702288486851768[262] = 0;
   out_794702288486851768[263] = 0;
   out_794702288486851768[264] = 0;
   out_794702288486851768[265] = 0;
   out_794702288486851768[266] = 1;
   out_794702288486851768[267] = 0;
   out_794702288486851768[268] = 0;
   out_794702288486851768[269] = 0;
   out_794702288486851768[270] = 0;
   out_794702288486851768[271] = 0;
   out_794702288486851768[272] = 0;
   out_794702288486851768[273] = 0;
   out_794702288486851768[274] = 0;
   out_794702288486851768[275] = 0;
   out_794702288486851768[276] = 0;
   out_794702288486851768[277] = 0;
   out_794702288486851768[278] = 0;
   out_794702288486851768[279] = 0;
   out_794702288486851768[280] = 0;
   out_794702288486851768[281] = 0;
   out_794702288486851768[282] = 0;
   out_794702288486851768[283] = 0;
   out_794702288486851768[284] = 0;
   out_794702288486851768[285] = 1;
   out_794702288486851768[286] = 0;
   out_794702288486851768[287] = 0;
   out_794702288486851768[288] = 0;
   out_794702288486851768[289] = 0;
   out_794702288486851768[290] = 0;
   out_794702288486851768[291] = 0;
   out_794702288486851768[292] = 0;
   out_794702288486851768[293] = 0;
   out_794702288486851768[294] = 0;
   out_794702288486851768[295] = 0;
   out_794702288486851768[296] = 0;
   out_794702288486851768[297] = 0;
   out_794702288486851768[298] = 0;
   out_794702288486851768[299] = 0;
   out_794702288486851768[300] = 0;
   out_794702288486851768[301] = 0;
   out_794702288486851768[302] = 0;
   out_794702288486851768[303] = 0;
   out_794702288486851768[304] = 1;
   out_794702288486851768[305] = 0;
   out_794702288486851768[306] = 0;
   out_794702288486851768[307] = 0;
   out_794702288486851768[308] = 0;
   out_794702288486851768[309] = 0;
   out_794702288486851768[310] = 0;
   out_794702288486851768[311] = 0;
   out_794702288486851768[312] = 0;
   out_794702288486851768[313] = 0;
   out_794702288486851768[314] = 0;
   out_794702288486851768[315] = 0;
   out_794702288486851768[316] = 0;
   out_794702288486851768[317] = 0;
   out_794702288486851768[318] = 0;
   out_794702288486851768[319] = 0;
   out_794702288486851768[320] = 0;
   out_794702288486851768[321] = 0;
   out_794702288486851768[322] = 0;
   out_794702288486851768[323] = 1;
}
void h_4(double *state, double *unused, double *out_5361717666727753051) {
   out_5361717666727753051[0] = state[6] + state[9];
   out_5361717666727753051[1] = state[7] + state[10];
   out_5361717666727753051[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8075993969334843161) {
   out_8075993969334843161[0] = 0;
   out_8075993969334843161[1] = 0;
   out_8075993969334843161[2] = 0;
   out_8075993969334843161[3] = 0;
   out_8075993969334843161[4] = 0;
   out_8075993969334843161[5] = 0;
   out_8075993969334843161[6] = 1;
   out_8075993969334843161[7] = 0;
   out_8075993969334843161[8] = 0;
   out_8075993969334843161[9] = 1;
   out_8075993969334843161[10] = 0;
   out_8075993969334843161[11] = 0;
   out_8075993969334843161[12] = 0;
   out_8075993969334843161[13] = 0;
   out_8075993969334843161[14] = 0;
   out_8075993969334843161[15] = 0;
   out_8075993969334843161[16] = 0;
   out_8075993969334843161[17] = 0;
   out_8075993969334843161[18] = 0;
   out_8075993969334843161[19] = 0;
   out_8075993969334843161[20] = 0;
   out_8075993969334843161[21] = 0;
   out_8075993969334843161[22] = 0;
   out_8075993969334843161[23] = 0;
   out_8075993969334843161[24] = 0;
   out_8075993969334843161[25] = 1;
   out_8075993969334843161[26] = 0;
   out_8075993969334843161[27] = 0;
   out_8075993969334843161[28] = 1;
   out_8075993969334843161[29] = 0;
   out_8075993969334843161[30] = 0;
   out_8075993969334843161[31] = 0;
   out_8075993969334843161[32] = 0;
   out_8075993969334843161[33] = 0;
   out_8075993969334843161[34] = 0;
   out_8075993969334843161[35] = 0;
   out_8075993969334843161[36] = 0;
   out_8075993969334843161[37] = 0;
   out_8075993969334843161[38] = 0;
   out_8075993969334843161[39] = 0;
   out_8075993969334843161[40] = 0;
   out_8075993969334843161[41] = 0;
   out_8075993969334843161[42] = 0;
   out_8075993969334843161[43] = 0;
   out_8075993969334843161[44] = 1;
   out_8075993969334843161[45] = 0;
   out_8075993969334843161[46] = 0;
   out_8075993969334843161[47] = 1;
   out_8075993969334843161[48] = 0;
   out_8075993969334843161[49] = 0;
   out_8075993969334843161[50] = 0;
   out_8075993969334843161[51] = 0;
   out_8075993969334843161[52] = 0;
   out_8075993969334843161[53] = 0;
}
void h_10(double *state, double *unused, double *out_391166273927914197) {
   out_391166273927914197[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_391166273927914197[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_391166273927914197[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2614348763027175247) {
   out_2614348763027175247[0] = 0;
   out_2614348763027175247[1] = 9.8100000000000005*cos(state[1]);
   out_2614348763027175247[2] = 0;
   out_2614348763027175247[3] = 0;
   out_2614348763027175247[4] = -state[8];
   out_2614348763027175247[5] = state[7];
   out_2614348763027175247[6] = 0;
   out_2614348763027175247[7] = state[5];
   out_2614348763027175247[8] = -state[4];
   out_2614348763027175247[9] = 0;
   out_2614348763027175247[10] = 0;
   out_2614348763027175247[11] = 0;
   out_2614348763027175247[12] = 1;
   out_2614348763027175247[13] = 0;
   out_2614348763027175247[14] = 0;
   out_2614348763027175247[15] = 1;
   out_2614348763027175247[16] = 0;
   out_2614348763027175247[17] = 0;
   out_2614348763027175247[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2614348763027175247[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2614348763027175247[20] = 0;
   out_2614348763027175247[21] = state[8];
   out_2614348763027175247[22] = 0;
   out_2614348763027175247[23] = -state[6];
   out_2614348763027175247[24] = -state[5];
   out_2614348763027175247[25] = 0;
   out_2614348763027175247[26] = state[3];
   out_2614348763027175247[27] = 0;
   out_2614348763027175247[28] = 0;
   out_2614348763027175247[29] = 0;
   out_2614348763027175247[30] = 0;
   out_2614348763027175247[31] = 1;
   out_2614348763027175247[32] = 0;
   out_2614348763027175247[33] = 0;
   out_2614348763027175247[34] = 1;
   out_2614348763027175247[35] = 0;
   out_2614348763027175247[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2614348763027175247[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2614348763027175247[38] = 0;
   out_2614348763027175247[39] = -state[7];
   out_2614348763027175247[40] = state[6];
   out_2614348763027175247[41] = 0;
   out_2614348763027175247[42] = state[4];
   out_2614348763027175247[43] = -state[3];
   out_2614348763027175247[44] = 0;
   out_2614348763027175247[45] = 0;
   out_2614348763027175247[46] = 0;
   out_2614348763027175247[47] = 0;
   out_2614348763027175247[48] = 0;
   out_2614348763027175247[49] = 0;
   out_2614348763027175247[50] = 1;
   out_2614348763027175247[51] = 0;
   out_2614348763027175247[52] = 0;
   out_2614348763027175247[53] = 1;
}
void h_13(double *state, double *unused, double *out_6109132341939542181) {
   out_6109132341939542181[0] = state[3];
   out_6109132341939542181[1] = state[4];
   out_6109132341939542181[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7158476279042375654) {
   out_7158476279042375654[0] = 0;
   out_7158476279042375654[1] = 0;
   out_7158476279042375654[2] = 0;
   out_7158476279042375654[3] = 1;
   out_7158476279042375654[4] = 0;
   out_7158476279042375654[5] = 0;
   out_7158476279042375654[6] = 0;
   out_7158476279042375654[7] = 0;
   out_7158476279042375654[8] = 0;
   out_7158476279042375654[9] = 0;
   out_7158476279042375654[10] = 0;
   out_7158476279042375654[11] = 0;
   out_7158476279042375654[12] = 0;
   out_7158476279042375654[13] = 0;
   out_7158476279042375654[14] = 0;
   out_7158476279042375654[15] = 0;
   out_7158476279042375654[16] = 0;
   out_7158476279042375654[17] = 0;
   out_7158476279042375654[18] = 0;
   out_7158476279042375654[19] = 0;
   out_7158476279042375654[20] = 0;
   out_7158476279042375654[21] = 0;
   out_7158476279042375654[22] = 1;
   out_7158476279042375654[23] = 0;
   out_7158476279042375654[24] = 0;
   out_7158476279042375654[25] = 0;
   out_7158476279042375654[26] = 0;
   out_7158476279042375654[27] = 0;
   out_7158476279042375654[28] = 0;
   out_7158476279042375654[29] = 0;
   out_7158476279042375654[30] = 0;
   out_7158476279042375654[31] = 0;
   out_7158476279042375654[32] = 0;
   out_7158476279042375654[33] = 0;
   out_7158476279042375654[34] = 0;
   out_7158476279042375654[35] = 0;
   out_7158476279042375654[36] = 0;
   out_7158476279042375654[37] = 0;
   out_7158476279042375654[38] = 0;
   out_7158476279042375654[39] = 0;
   out_7158476279042375654[40] = 0;
   out_7158476279042375654[41] = 1;
   out_7158476279042375654[42] = 0;
   out_7158476279042375654[43] = 0;
   out_7158476279042375654[44] = 0;
   out_7158476279042375654[45] = 0;
   out_7158476279042375654[46] = 0;
   out_7158476279042375654[47] = 0;
   out_7158476279042375654[48] = 0;
   out_7158476279042375654[49] = 0;
   out_7158476279042375654[50] = 0;
   out_7158476279042375654[51] = 0;
   out_7158476279042375654[52] = 0;
   out_7158476279042375654[53] = 0;
}
void h_14(double *state, double *unused, double *out_6365736750673459896) {
   out_6365736750673459896[0] = state[6];
   out_6365736750673459896[1] = state[7];
   out_6365736750673459896[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6407509248035223926) {
   out_6407509248035223926[0] = 0;
   out_6407509248035223926[1] = 0;
   out_6407509248035223926[2] = 0;
   out_6407509248035223926[3] = 0;
   out_6407509248035223926[4] = 0;
   out_6407509248035223926[5] = 0;
   out_6407509248035223926[6] = 1;
   out_6407509248035223926[7] = 0;
   out_6407509248035223926[8] = 0;
   out_6407509248035223926[9] = 0;
   out_6407509248035223926[10] = 0;
   out_6407509248035223926[11] = 0;
   out_6407509248035223926[12] = 0;
   out_6407509248035223926[13] = 0;
   out_6407509248035223926[14] = 0;
   out_6407509248035223926[15] = 0;
   out_6407509248035223926[16] = 0;
   out_6407509248035223926[17] = 0;
   out_6407509248035223926[18] = 0;
   out_6407509248035223926[19] = 0;
   out_6407509248035223926[20] = 0;
   out_6407509248035223926[21] = 0;
   out_6407509248035223926[22] = 0;
   out_6407509248035223926[23] = 0;
   out_6407509248035223926[24] = 0;
   out_6407509248035223926[25] = 1;
   out_6407509248035223926[26] = 0;
   out_6407509248035223926[27] = 0;
   out_6407509248035223926[28] = 0;
   out_6407509248035223926[29] = 0;
   out_6407509248035223926[30] = 0;
   out_6407509248035223926[31] = 0;
   out_6407509248035223926[32] = 0;
   out_6407509248035223926[33] = 0;
   out_6407509248035223926[34] = 0;
   out_6407509248035223926[35] = 0;
   out_6407509248035223926[36] = 0;
   out_6407509248035223926[37] = 0;
   out_6407509248035223926[38] = 0;
   out_6407509248035223926[39] = 0;
   out_6407509248035223926[40] = 0;
   out_6407509248035223926[41] = 0;
   out_6407509248035223926[42] = 0;
   out_6407509248035223926[43] = 0;
   out_6407509248035223926[44] = 1;
   out_6407509248035223926[45] = 0;
   out_6407509248035223926[46] = 0;
   out_6407509248035223926[47] = 0;
   out_6407509248035223926[48] = 0;
   out_6407509248035223926[49] = 0;
   out_6407509248035223926[50] = 0;
   out_6407509248035223926[51] = 0;
   out_6407509248035223926[52] = 0;
   out_6407509248035223926[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8838830420648207010) {
  err_fun(nom_x, delta_x, out_8838830420648207010);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2885477467670563304) {
  inv_err_fun(nom_x, true_x, out_2885477467670563304);
}
void pose_H_mod_fun(double *state, double *out_7096528025583759202) {
  H_mod_fun(state, out_7096528025583759202);
}
void pose_f_fun(double *state, double dt, double *out_8038070982033161577) {
  f_fun(state,  dt, out_8038070982033161577);
}
void pose_F_fun(double *state, double dt, double *out_794702288486851768) {
  F_fun(state,  dt, out_794702288486851768);
}
void pose_h_4(double *state, double *unused, double *out_5361717666727753051) {
  h_4(state, unused, out_5361717666727753051);
}
void pose_H_4(double *state, double *unused, double *out_8075993969334843161) {
  H_4(state, unused, out_8075993969334843161);
}
void pose_h_10(double *state, double *unused, double *out_391166273927914197) {
  h_10(state, unused, out_391166273927914197);
}
void pose_H_10(double *state, double *unused, double *out_2614348763027175247) {
  H_10(state, unused, out_2614348763027175247);
}
void pose_h_13(double *state, double *unused, double *out_6109132341939542181) {
  h_13(state, unused, out_6109132341939542181);
}
void pose_H_13(double *state, double *unused, double *out_7158476279042375654) {
  H_13(state, unused, out_7158476279042375654);
}
void pose_h_14(double *state, double *unused, double *out_6365736750673459896) {
  h_14(state, unused, out_6365736750673459896);
}
void pose_H_14(double *state, double *unused, double *out_6407509248035223926) {
  H_14(state, unused, out_6407509248035223926);
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
