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
void err_fun(double *nom_x, double *delta_x, double *out_2844503766928312028) {
   out_2844503766928312028[0] = delta_x[0] + nom_x[0];
   out_2844503766928312028[1] = delta_x[1] + nom_x[1];
   out_2844503766928312028[2] = delta_x[2] + nom_x[2];
   out_2844503766928312028[3] = delta_x[3] + nom_x[3];
   out_2844503766928312028[4] = delta_x[4] + nom_x[4];
   out_2844503766928312028[5] = delta_x[5] + nom_x[5];
   out_2844503766928312028[6] = delta_x[6] + nom_x[6];
   out_2844503766928312028[7] = delta_x[7] + nom_x[7];
   out_2844503766928312028[8] = delta_x[8] + nom_x[8];
   out_2844503766928312028[9] = delta_x[9] + nom_x[9];
   out_2844503766928312028[10] = delta_x[10] + nom_x[10];
   out_2844503766928312028[11] = delta_x[11] + nom_x[11];
   out_2844503766928312028[12] = delta_x[12] + nom_x[12];
   out_2844503766928312028[13] = delta_x[13] + nom_x[13];
   out_2844503766928312028[14] = delta_x[14] + nom_x[14];
   out_2844503766928312028[15] = delta_x[15] + nom_x[15];
   out_2844503766928312028[16] = delta_x[16] + nom_x[16];
   out_2844503766928312028[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_188944154440250924) {
   out_188944154440250924[0] = -nom_x[0] + true_x[0];
   out_188944154440250924[1] = -nom_x[1] + true_x[1];
   out_188944154440250924[2] = -nom_x[2] + true_x[2];
   out_188944154440250924[3] = -nom_x[3] + true_x[3];
   out_188944154440250924[4] = -nom_x[4] + true_x[4];
   out_188944154440250924[5] = -nom_x[5] + true_x[5];
   out_188944154440250924[6] = -nom_x[6] + true_x[6];
   out_188944154440250924[7] = -nom_x[7] + true_x[7];
   out_188944154440250924[8] = -nom_x[8] + true_x[8];
   out_188944154440250924[9] = -nom_x[9] + true_x[9];
   out_188944154440250924[10] = -nom_x[10] + true_x[10];
   out_188944154440250924[11] = -nom_x[11] + true_x[11];
   out_188944154440250924[12] = -nom_x[12] + true_x[12];
   out_188944154440250924[13] = -nom_x[13] + true_x[13];
   out_188944154440250924[14] = -nom_x[14] + true_x[14];
   out_188944154440250924[15] = -nom_x[15] + true_x[15];
   out_188944154440250924[16] = -nom_x[16] + true_x[16];
   out_188944154440250924[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7217718077783114524) {
   out_7217718077783114524[0] = 1.0;
   out_7217718077783114524[1] = 0.0;
   out_7217718077783114524[2] = 0.0;
   out_7217718077783114524[3] = 0.0;
   out_7217718077783114524[4] = 0.0;
   out_7217718077783114524[5] = 0.0;
   out_7217718077783114524[6] = 0.0;
   out_7217718077783114524[7] = 0.0;
   out_7217718077783114524[8] = 0.0;
   out_7217718077783114524[9] = 0.0;
   out_7217718077783114524[10] = 0.0;
   out_7217718077783114524[11] = 0.0;
   out_7217718077783114524[12] = 0.0;
   out_7217718077783114524[13] = 0.0;
   out_7217718077783114524[14] = 0.0;
   out_7217718077783114524[15] = 0.0;
   out_7217718077783114524[16] = 0.0;
   out_7217718077783114524[17] = 0.0;
   out_7217718077783114524[18] = 0.0;
   out_7217718077783114524[19] = 1.0;
   out_7217718077783114524[20] = 0.0;
   out_7217718077783114524[21] = 0.0;
   out_7217718077783114524[22] = 0.0;
   out_7217718077783114524[23] = 0.0;
   out_7217718077783114524[24] = 0.0;
   out_7217718077783114524[25] = 0.0;
   out_7217718077783114524[26] = 0.0;
   out_7217718077783114524[27] = 0.0;
   out_7217718077783114524[28] = 0.0;
   out_7217718077783114524[29] = 0.0;
   out_7217718077783114524[30] = 0.0;
   out_7217718077783114524[31] = 0.0;
   out_7217718077783114524[32] = 0.0;
   out_7217718077783114524[33] = 0.0;
   out_7217718077783114524[34] = 0.0;
   out_7217718077783114524[35] = 0.0;
   out_7217718077783114524[36] = 0.0;
   out_7217718077783114524[37] = 0.0;
   out_7217718077783114524[38] = 1.0;
   out_7217718077783114524[39] = 0.0;
   out_7217718077783114524[40] = 0.0;
   out_7217718077783114524[41] = 0.0;
   out_7217718077783114524[42] = 0.0;
   out_7217718077783114524[43] = 0.0;
   out_7217718077783114524[44] = 0.0;
   out_7217718077783114524[45] = 0.0;
   out_7217718077783114524[46] = 0.0;
   out_7217718077783114524[47] = 0.0;
   out_7217718077783114524[48] = 0.0;
   out_7217718077783114524[49] = 0.0;
   out_7217718077783114524[50] = 0.0;
   out_7217718077783114524[51] = 0.0;
   out_7217718077783114524[52] = 0.0;
   out_7217718077783114524[53] = 0.0;
   out_7217718077783114524[54] = 0.0;
   out_7217718077783114524[55] = 0.0;
   out_7217718077783114524[56] = 0.0;
   out_7217718077783114524[57] = 1.0;
   out_7217718077783114524[58] = 0.0;
   out_7217718077783114524[59] = 0.0;
   out_7217718077783114524[60] = 0.0;
   out_7217718077783114524[61] = 0.0;
   out_7217718077783114524[62] = 0.0;
   out_7217718077783114524[63] = 0.0;
   out_7217718077783114524[64] = 0.0;
   out_7217718077783114524[65] = 0.0;
   out_7217718077783114524[66] = 0.0;
   out_7217718077783114524[67] = 0.0;
   out_7217718077783114524[68] = 0.0;
   out_7217718077783114524[69] = 0.0;
   out_7217718077783114524[70] = 0.0;
   out_7217718077783114524[71] = 0.0;
   out_7217718077783114524[72] = 0.0;
   out_7217718077783114524[73] = 0.0;
   out_7217718077783114524[74] = 0.0;
   out_7217718077783114524[75] = 0.0;
   out_7217718077783114524[76] = 1.0;
   out_7217718077783114524[77] = 0.0;
   out_7217718077783114524[78] = 0.0;
   out_7217718077783114524[79] = 0.0;
   out_7217718077783114524[80] = 0.0;
   out_7217718077783114524[81] = 0.0;
   out_7217718077783114524[82] = 0.0;
   out_7217718077783114524[83] = 0.0;
   out_7217718077783114524[84] = 0.0;
   out_7217718077783114524[85] = 0.0;
   out_7217718077783114524[86] = 0.0;
   out_7217718077783114524[87] = 0.0;
   out_7217718077783114524[88] = 0.0;
   out_7217718077783114524[89] = 0.0;
   out_7217718077783114524[90] = 0.0;
   out_7217718077783114524[91] = 0.0;
   out_7217718077783114524[92] = 0.0;
   out_7217718077783114524[93] = 0.0;
   out_7217718077783114524[94] = 0.0;
   out_7217718077783114524[95] = 1.0;
   out_7217718077783114524[96] = 0.0;
   out_7217718077783114524[97] = 0.0;
   out_7217718077783114524[98] = 0.0;
   out_7217718077783114524[99] = 0.0;
   out_7217718077783114524[100] = 0.0;
   out_7217718077783114524[101] = 0.0;
   out_7217718077783114524[102] = 0.0;
   out_7217718077783114524[103] = 0.0;
   out_7217718077783114524[104] = 0.0;
   out_7217718077783114524[105] = 0.0;
   out_7217718077783114524[106] = 0.0;
   out_7217718077783114524[107] = 0.0;
   out_7217718077783114524[108] = 0.0;
   out_7217718077783114524[109] = 0.0;
   out_7217718077783114524[110] = 0.0;
   out_7217718077783114524[111] = 0.0;
   out_7217718077783114524[112] = 0.0;
   out_7217718077783114524[113] = 0.0;
   out_7217718077783114524[114] = 1.0;
   out_7217718077783114524[115] = 0.0;
   out_7217718077783114524[116] = 0.0;
   out_7217718077783114524[117] = 0.0;
   out_7217718077783114524[118] = 0.0;
   out_7217718077783114524[119] = 0.0;
   out_7217718077783114524[120] = 0.0;
   out_7217718077783114524[121] = 0.0;
   out_7217718077783114524[122] = 0.0;
   out_7217718077783114524[123] = 0.0;
   out_7217718077783114524[124] = 0.0;
   out_7217718077783114524[125] = 0.0;
   out_7217718077783114524[126] = 0.0;
   out_7217718077783114524[127] = 0.0;
   out_7217718077783114524[128] = 0.0;
   out_7217718077783114524[129] = 0.0;
   out_7217718077783114524[130] = 0.0;
   out_7217718077783114524[131] = 0.0;
   out_7217718077783114524[132] = 0.0;
   out_7217718077783114524[133] = 1.0;
   out_7217718077783114524[134] = 0.0;
   out_7217718077783114524[135] = 0.0;
   out_7217718077783114524[136] = 0.0;
   out_7217718077783114524[137] = 0.0;
   out_7217718077783114524[138] = 0.0;
   out_7217718077783114524[139] = 0.0;
   out_7217718077783114524[140] = 0.0;
   out_7217718077783114524[141] = 0.0;
   out_7217718077783114524[142] = 0.0;
   out_7217718077783114524[143] = 0.0;
   out_7217718077783114524[144] = 0.0;
   out_7217718077783114524[145] = 0.0;
   out_7217718077783114524[146] = 0.0;
   out_7217718077783114524[147] = 0.0;
   out_7217718077783114524[148] = 0.0;
   out_7217718077783114524[149] = 0.0;
   out_7217718077783114524[150] = 0.0;
   out_7217718077783114524[151] = 0.0;
   out_7217718077783114524[152] = 1.0;
   out_7217718077783114524[153] = 0.0;
   out_7217718077783114524[154] = 0.0;
   out_7217718077783114524[155] = 0.0;
   out_7217718077783114524[156] = 0.0;
   out_7217718077783114524[157] = 0.0;
   out_7217718077783114524[158] = 0.0;
   out_7217718077783114524[159] = 0.0;
   out_7217718077783114524[160] = 0.0;
   out_7217718077783114524[161] = 0.0;
   out_7217718077783114524[162] = 0.0;
   out_7217718077783114524[163] = 0.0;
   out_7217718077783114524[164] = 0.0;
   out_7217718077783114524[165] = 0.0;
   out_7217718077783114524[166] = 0.0;
   out_7217718077783114524[167] = 0.0;
   out_7217718077783114524[168] = 0.0;
   out_7217718077783114524[169] = 0.0;
   out_7217718077783114524[170] = 0.0;
   out_7217718077783114524[171] = 1.0;
   out_7217718077783114524[172] = 0.0;
   out_7217718077783114524[173] = 0.0;
   out_7217718077783114524[174] = 0.0;
   out_7217718077783114524[175] = 0.0;
   out_7217718077783114524[176] = 0.0;
   out_7217718077783114524[177] = 0.0;
   out_7217718077783114524[178] = 0.0;
   out_7217718077783114524[179] = 0.0;
   out_7217718077783114524[180] = 0.0;
   out_7217718077783114524[181] = 0.0;
   out_7217718077783114524[182] = 0.0;
   out_7217718077783114524[183] = 0.0;
   out_7217718077783114524[184] = 0.0;
   out_7217718077783114524[185] = 0.0;
   out_7217718077783114524[186] = 0.0;
   out_7217718077783114524[187] = 0.0;
   out_7217718077783114524[188] = 0.0;
   out_7217718077783114524[189] = 0.0;
   out_7217718077783114524[190] = 1.0;
   out_7217718077783114524[191] = 0.0;
   out_7217718077783114524[192] = 0.0;
   out_7217718077783114524[193] = 0.0;
   out_7217718077783114524[194] = 0.0;
   out_7217718077783114524[195] = 0.0;
   out_7217718077783114524[196] = 0.0;
   out_7217718077783114524[197] = 0.0;
   out_7217718077783114524[198] = 0.0;
   out_7217718077783114524[199] = 0.0;
   out_7217718077783114524[200] = 0.0;
   out_7217718077783114524[201] = 0.0;
   out_7217718077783114524[202] = 0.0;
   out_7217718077783114524[203] = 0.0;
   out_7217718077783114524[204] = 0.0;
   out_7217718077783114524[205] = 0.0;
   out_7217718077783114524[206] = 0.0;
   out_7217718077783114524[207] = 0.0;
   out_7217718077783114524[208] = 0.0;
   out_7217718077783114524[209] = 1.0;
   out_7217718077783114524[210] = 0.0;
   out_7217718077783114524[211] = 0.0;
   out_7217718077783114524[212] = 0.0;
   out_7217718077783114524[213] = 0.0;
   out_7217718077783114524[214] = 0.0;
   out_7217718077783114524[215] = 0.0;
   out_7217718077783114524[216] = 0.0;
   out_7217718077783114524[217] = 0.0;
   out_7217718077783114524[218] = 0.0;
   out_7217718077783114524[219] = 0.0;
   out_7217718077783114524[220] = 0.0;
   out_7217718077783114524[221] = 0.0;
   out_7217718077783114524[222] = 0.0;
   out_7217718077783114524[223] = 0.0;
   out_7217718077783114524[224] = 0.0;
   out_7217718077783114524[225] = 0.0;
   out_7217718077783114524[226] = 0.0;
   out_7217718077783114524[227] = 0.0;
   out_7217718077783114524[228] = 1.0;
   out_7217718077783114524[229] = 0.0;
   out_7217718077783114524[230] = 0.0;
   out_7217718077783114524[231] = 0.0;
   out_7217718077783114524[232] = 0.0;
   out_7217718077783114524[233] = 0.0;
   out_7217718077783114524[234] = 0.0;
   out_7217718077783114524[235] = 0.0;
   out_7217718077783114524[236] = 0.0;
   out_7217718077783114524[237] = 0.0;
   out_7217718077783114524[238] = 0.0;
   out_7217718077783114524[239] = 0.0;
   out_7217718077783114524[240] = 0.0;
   out_7217718077783114524[241] = 0.0;
   out_7217718077783114524[242] = 0.0;
   out_7217718077783114524[243] = 0.0;
   out_7217718077783114524[244] = 0.0;
   out_7217718077783114524[245] = 0.0;
   out_7217718077783114524[246] = 0.0;
   out_7217718077783114524[247] = 1.0;
   out_7217718077783114524[248] = 0.0;
   out_7217718077783114524[249] = 0.0;
   out_7217718077783114524[250] = 0.0;
   out_7217718077783114524[251] = 0.0;
   out_7217718077783114524[252] = 0.0;
   out_7217718077783114524[253] = 0.0;
   out_7217718077783114524[254] = 0.0;
   out_7217718077783114524[255] = 0.0;
   out_7217718077783114524[256] = 0.0;
   out_7217718077783114524[257] = 0.0;
   out_7217718077783114524[258] = 0.0;
   out_7217718077783114524[259] = 0.0;
   out_7217718077783114524[260] = 0.0;
   out_7217718077783114524[261] = 0.0;
   out_7217718077783114524[262] = 0.0;
   out_7217718077783114524[263] = 0.0;
   out_7217718077783114524[264] = 0.0;
   out_7217718077783114524[265] = 0.0;
   out_7217718077783114524[266] = 1.0;
   out_7217718077783114524[267] = 0.0;
   out_7217718077783114524[268] = 0.0;
   out_7217718077783114524[269] = 0.0;
   out_7217718077783114524[270] = 0.0;
   out_7217718077783114524[271] = 0.0;
   out_7217718077783114524[272] = 0.0;
   out_7217718077783114524[273] = 0.0;
   out_7217718077783114524[274] = 0.0;
   out_7217718077783114524[275] = 0.0;
   out_7217718077783114524[276] = 0.0;
   out_7217718077783114524[277] = 0.0;
   out_7217718077783114524[278] = 0.0;
   out_7217718077783114524[279] = 0.0;
   out_7217718077783114524[280] = 0.0;
   out_7217718077783114524[281] = 0.0;
   out_7217718077783114524[282] = 0.0;
   out_7217718077783114524[283] = 0.0;
   out_7217718077783114524[284] = 0.0;
   out_7217718077783114524[285] = 1.0;
   out_7217718077783114524[286] = 0.0;
   out_7217718077783114524[287] = 0.0;
   out_7217718077783114524[288] = 0.0;
   out_7217718077783114524[289] = 0.0;
   out_7217718077783114524[290] = 0.0;
   out_7217718077783114524[291] = 0.0;
   out_7217718077783114524[292] = 0.0;
   out_7217718077783114524[293] = 0.0;
   out_7217718077783114524[294] = 0.0;
   out_7217718077783114524[295] = 0.0;
   out_7217718077783114524[296] = 0.0;
   out_7217718077783114524[297] = 0.0;
   out_7217718077783114524[298] = 0.0;
   out_7217718077783114524[299] = 0.0;
   out_7217718077783114524[300] = 0.0;
   out_7217718077783114524[301] = 0.0;
   out_7217718077783114524[302] = 0.0;
   out_7217718077783114524[303] = 0.0;
   out_7217718077783114524[304] = 1.0;
   out_7217718077783114524[305] = 0.0;
   out_7217718077783114524[306] = 0.0;
   out_7217718077783114524[307] = 0.0;
   out_7217718077783114524[308] = 0.0;
   out_7217718077783114524[309] = 0.0;
   out_7217718077783114524[310] = 0.0;
   out_7217718077783114524[311] = 0.0;
   out_7217718077783114524[312] = 0.0;
   out_7217718077783114524[313] = 0.0;
   out_7217718077783114524[314] = 0.0;
   out_7217718077783114524[315] = 0.0;
   out_7217718077783114524[316] = 0.0;
   out_7217718077783114524[317] = 0.0;
   out_7217718077783114524[318] = 0.0;
   out_7217718077783114524[319] = 0.0;
   out_7217718077783114524[320] = 0.0;
   out_7217718077783114524[321] = 0.0;
   out_7217718077783114524[322] = 0.0;
   out_7217718077783114524[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6254706918453181358) {
   out_6254706918453181358[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6254706918453181358[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6254706918453181358[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6254706918453181358[3] = dt*state[12] + state[3];
   out_6254706918453181358[4] = dt*state[13] + state[4];
   out_6254706918453181358[5] = dt*state[14] + state[5];
   out_6254706918453181358[6] = state[6];
   out_6254706918453181358[7] = state[7];
   out_6254706918453181358[8] = state[8];
   out_6254706918453181358[9] = state[9];
   out_6254706918453181358[10] = state[10];
   out_6254706918453181358[11] = state[11];
   out_6254706918453181358[12] = state[12];
   out_6254706918453181358[13] = state[13];
   out_6254706918453181358[14] = state[14];
   out_6254706918453181358[15] = state[15];
   out_6254706918453181358[16] = state[16];
   out_6254706918453181358[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5818928030751659740) {
   out_5818928030751659740[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5818928030751659740[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5818928030751659740[2] = 0;
   out_5818928030751659740[3] = 0;
   out_5818928030751659740[4] = 0;
   out_5818928030751659740[5] = 0;
   out_5818928030751659740[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5818928030751659740[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5818928030751659740[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5818928030751659740[9] = 0;
   out_5818928030751659740[10] = 0;
   out_5818928030751659740[11] = 0;
   out_5818928030751659740[12] = 0;
   out_5818928030751659740[13] = 0;
   out_5818928030751659740[14] = 0;
   out_5818928030751659740[15] = 0;
   out_5818928030751659740[16] = 0;
   out_5818928030751659740[17] = 0;
   out_5818928030751659740[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5818928030751659740[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5818928030751659740[20] = 0;
   out_5818928030751659740[21] = 0;
   out_5818928030751659740[22] = 0;
   out_5818928030751659740[23] = 0;
   out_5818928030751659740[24] = 0;
   out_5818928030751659740[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5818928030751659740[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5818928030751659740[27] = 0;
   out_5818928030751659740[28] = 0;
   out_5818928030751659740[29] = 0;
   out_5818928030751659740[30] = 0;
   out_5818928030751659740[31] = 0;
   out_5818928030751659740[32] = 0;
   out_5818928030751659740[33] = 0;
   out_5818928030751659740[34] = 0;
   out_5818928030751659740[35] = 0;
   out_5818928030751659740[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5818928030751659740[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5818928030751659740[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5818928030751659740[39] = 0;
   out_5818928030751659740[40] = 0;
   out_5818928030751659740[41] = 0;
   out_5818928030751659740[42] = 0;
   out_5818928030751659740[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5818928030751659740[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5818928030751659740[45] = 0;
   out_5818928030751659740[46] = 0;
   out_5818928030751659740[47] = 0;
   out_5818928030751659740[48] = 0;
   out_5818928030751659740[49] = 0;
   out_5818928030751659740[50] = 0;
   out_5818928030751659740[51] = 0;
   out_5818928030751659740[52] = 0;
   out_5818928030751659740[53] = 0;
   out_5818928030751659740[54] = 0;
   out_5818928030751659740[55] = 0;
   out_5818928030751659740[56] = 0;
   out_5818928030751659740[57] = 1;
   out_5818928030751659740[58] = 0;
   out_5818928030751659740[59] = 0;
   out_5818928030751659740[60] = 0;
   out_5818928030751659740[61] = 0;
   out_5818928030751659740[62] = 0;
   out_5818928030751659740[63] = 0;
   out_5818928030751659740[64] = 0;
   out_5818928030751659740[65] = 0;
   out_5818928030751659740[66] = dt;
   out_5818928030751659740[67] = 0;
   out_5818928030751659740[68] = 0;
   out_5818928030751659740[69] = 0;
   out_5818928030751659740[70] = 0;
   out_5818928030751659740[71] = 0;
   out_5818928030751659740[72] = 0;
   out_5818928030751659740[73] = 0;
   out_5818928030751659740[74] = 0;
   out_5818928030751659740[75] = 0;
   out_5818928030751659740[76] = 1;
   out_5818928030751659740[77] = 0;
   out_5818928030751659740[78] = 0;
   out_5818928030751659740[79] = 0;
   out_5818928030751659740[80] = 0;
   out_5818928030751659740[81] = 0;
   out_5818928030751659740[82] = 0;
   out_5818928030751659740[83] = 0;
   out_5818928030751659740[84] = 0;
   out_5818928030751659740[85] = dt;
   out_5818928030751659740[86] = 0;
   out_5818928030751659740[87] = 0;
   out_5818928030751659740[88] = 0;
   out_5818928030751659740[89] = 0;
   out_5818928030751659740[90] = 0;
   out_5818928030751659740[91] = 0;
   out_5818928030751659740[92] = 0;
   out_5818928030751659740[93] = 0;
   out_5818928030751659740[94] = 0;
   out_5818928030751659740[95] = 1;
   out_5818928030751659740[96] = 0;
   out_5818928030751659740[97] = 0;
   out_5818928030751659740[98] = 0;
   out_5818928030751659740[99] = 0;
   out_5818928030751659740[100] = 0;
   out_5818928030751659740[101] = 0;
   out_5818928030751659740[102] = 0;
   out_5818928030751659740[103] = 0;
   out_5818928030751659740[104] = dt;
   out_5818928030751659740[105] = 0;
   out_5818928030751659740[106] = 0;
   out_5818928030751659740[107] = 0;
   out_5818928030751659740[108] = 0;
   out_5818928030751659740[109] = 0;
   out_5818928030751659740[110] = 0;
   out_5818928030751659740[111] = 0;
   out_5818928030751659740[112] = 0;
   out_5818928030751659740[113] = 0;
   out_5818928030751659740[114] = 1;
   out_5818928030751659740[115] = 0;
   out_5818928030751659740[116] = 0;
   out_5818928030751659740[117] = 0;
   out_5818928030751659740[118] = 0;
   out_5818928030751659740[119] = 0;
   out_5818928030751659740[120] = 0;
   out_5818928030751659740[121] = 0;
   out_5818928030751659740[122] = 0;
   out_5818928030751659740[123] = 0;
   out_5818928030751659740[124] = 0;
   out_5818928030751659740[125] = 0;
   out_5818928030751659740[126] = 0;
   out_5818928030751659740[127] = 0;
   out_5818928030751659740[128] = 0;
   out_5818928030751659740[129] = 0;
   out_5818928030751659740[130] = 0;
   out_5818928030751659740[131] = 0;
   out_5818928030751659740[132] = 0;
   out_5818928030751659740[133] = 1;
   out_5818928030751659740[134] = 0;
   out_5818928030751659740[135] = 0;
   out_5818928030751659740[136] = 0;
   out_5818928030751659740[137] = 0;
   out_5818928030751659740[138] = 0;
   out_5818928030751659740[139] = 0;
   out_5818928030751659740[140] = 0;
   out_5818928030751659740[141] = 0;
   out_5818928030751659740[142] = 0;
   out_5818928030751659740[143] = 0;
   out_5818928030751659740[144] = 0;
   out_5818928030751659740[145] = 0;
   out_5818928030751659740[146] = 0;
   out_5818928030751659740[147] = 0;
   out_5818928030751659740[148] = 0;
   out_5818928030751659740[149] = 0;
   out_5818928030751659740[150] = 0;
   out_5818928030751659740[151] = 0;
   out_5818928030751659740[152] = 1;
   out_5818928030751659740[153] = 0;
   out_5818928030751659740[154] = 0;
   out_5818928030751659740[155] = 0;
   out_5818928030751659740[156] = 0;
   out_5818928030751659740[157] = 0;
   out_5818928030751659740[158] = 0;
   out_5818928030751659740[159] = 0;
   out_5818928030751659740[160] = 0;
   out_5818928030751659740[161] = 0;
   out_5818928030751659740[162] = 0;
   out_5818928030751659740[163] = 0;
   out_5818928030751659740[164] = 0;
   out_5818928030751659740[165] = 0;
   out_5818928030751659740[166] = 0;
   out_5818928030751659740[167] = 0;
   out_5818928030751659740[168] = 0;
   out_5818928030751659740[169] = 0;
   out_5818928030751659740[170] = 0;
   out_5818928030751659740[171] = 1;
   out_5818928030751659740[172] = 0;
   out_5818928030751659740[173] = 0;
   out_5818928030751659740[174] = 0;
   out_5818928030751659740[175] = 0;
   out_5818928030751659740[176] = 0;
   out_5818928030751659740[177] = 0;
   out_5818928030751659740[178] = 0;
   out_5818928030751659740[179] = 0;
   out_5818928030751659740[180] = 0;
   out_5818928030751659740[181] = 0;
   out_5818928030751659740[182] = 0;
   out_5818928030751659740[183] = 0;
   out_5818928030751659740[184] = 0;
   out_5818928030751659740[185] = 0;
   out_5818928030751659740[186] = 0;
   out_5818928030751659740[187] = 0;
   out_5818928030751659740[188] = 0;
   out_5818928030751659740[189] = 0;
   out_5818928030751659740[190] = 1;
   out_5818928030751659740[191] = 0;
   out_5818928030751659740[192] = 0;
   out_5818928030751659740[193] = 0;
   out_5818928030751659740[194] = 0;
   out_5818928030751659740[195] = 0;
   out_5818928030751659740[196] = 0;
   out_5818928030751659740[197] = 0;
   out_5818928030751659740[198] = 0;
   out_5818928030751659740[199] = 0;
   out_5818928030751659740[200] = 0;
   out_5818928030751659740[201] = 0;
   out_5818928030751659740[202] = 0;
   out_5818928030751659740[203] = 0;
   out_5818928030751659740[204] = 0;
   out_5818928030751659740[205] = 0;
   out_5818928030751659740[206] = 0;
   out_5818928030751659740[207] = 0;
   out_5818928030751659740[208] = 0;
   out_5818928030751659740[209] = 1;
   out_5818928030751659740[210] = 0;
   out_5818928030751659740[211] = 0;
   out_5818928030751659740[212] = 0;
   out_5818928030751659740[213] = 0;
   out_5818928030751659740[214] = 0;
   out_5818928030751659740[215] = 0;
   out_5818928030751659740[216] = 0;
   out_5818928030751659740[217] = 0;
   out_5818928030751659740[218] = 0;
   out_5818928030751659740[219] = 0;
   out_5818928030751659740[220] = 0;
   out_5818928030751659740[221] = 0;
   out_5818928030751659740[222] = 0;
   out_5818928030751659740[223] = 0;
   out_5818928030751659740[224] = 0;
   out_5818928030751659740[225] = 0;
   out_5818928030751659740[226] = 0;
   out_5818928030751659740[227] = 0;
   out_5818928030751659740[228] = 1;
   out_5818928030751659740[229] = 0;
   out_5818928030751659740[230] = 0;
   out_5818928030751659740[231] = 0;
   out_5818928030751659740[232] = 0;
   out_5818928030751659740[233] = 0;
   out_5818928030751659740[234] = 0;
   out_5818928030751659740[235] = 0;
   out_5818928030751659740[236] = 0;
   out_5818928030751659740[237] = 0;
   out_5818928030751659740[238] = 0;
   out_5818928030751659740[239] = 0;
   out_5818928030751659740[240] = 0;
   out_5818928030751659740[241] = 0;
   out_5818928030751659740[242] = 0;
   out_5818928030751659740[243] = 0;
   out_5818928030751659740[244] = 0;
   out_5818928030751659740[245] = 0;
   out_5818928030751659740[246] = 0;
   out_5818928030751659740[247] = 1;
   out_5818928030751659740[248] = 0;
   out_5818928030751659740[249] = 0;
   out_5818928030751659740[250] = 0;
   out_5818928030751659740[251] = 0;
   out_5818928030751659740[252] = 0;
   out_5818928030751659740[253] = 0;
   out_5818928030751659740[254] = 0;
   out_5818928030751659740[255] = 0;
   out_5818928030751659740[256] = 0;
   out_5818928030751659740[257] = 0;
   out_5818928030751659740[258] = 0;
   out_5818928030751659740[259] = 0;
   out_5818928030751659740[260] = 0;
   out_5818928030751659740[261] = 0;
   out_5818928030751659740[262] = 0;
   out_5818928030751659740[263] = 0;
   out_5818928030751659740[264] = 0;
   out_5818928030751659740[265] = 0;
   out_5818928030751659740[266] = 1;
   out_5818928030751659740[267] = 0;
   out_5818928030751659740[268] = 0;
   out_5818928030751659740[269] = 0;
   out_5818928030751659740[270] = 0;
   out_5818928030751659740[271] = 0;
   out_5818928030751659740[272] = 0;
   out_5818928030751659740[273] = 0;
   out_5818928030751659740[274] = 0;
   out_5818928030751659740[275] = 0;
   out_5818928030751659740[276] = 0;
   out_5818928030751659740[277] = 0;
   out_5818928030751659740[278] = 0;
   out_5818928030751659740[279] = 0;
   out_5818928030751659740[280] = 0;
   out_5818928030751659740[281] = 0;
   out_5818928030751659740[282] = 0;
   out_5818928030751659740[283] = 0;
   out_5818928030751659740[284] = 0;
   out_5818928030751659740[285] = 1;
   out_5818928030751659740[286] = 0;
   out_5818928030751659740[287] = 0;
   out_5818928030751659740[288] = 0;
   out_5818928030751659740[289] = 0;
   out_5818928030751659740[290] = 0;
   out_5818928030751659740[291] = 0;
   out_5818928030751659740[292] = 0;
   out_5818928030751659740[293] = 0;
   out_5818928030751659740[294] = 0;
   out_5818928030751659740[295] = 0;
   out_5818928030751659740[296] = 0;
   out_5818928030751659740[297] = 0;
   out_5818928030751659740[298] = 0;
   out_5818928030751659740[299] = 0;
   out_5818928030751659740[300] = 0;
   out_5818928030751659740[301] = 0;
   out_5818928030751659740[302] = 0;
   out_5818928030751659740[303] = 0;
   out_5818928030751659740[304] = 1;
   out_5818928030751659740[305] = 0;
   out_5818928030751659740[306] = 0;
   out_5818928030751659740[307] = 0;
   out_5818928030751659740[308] = 0;
   out_5818928030751659740[309] = 0;
   out_5818928030751659740[310] = 0;
   out_5818928030751659740[311] = 0;
   out_5818928030751659740[312] = 0;
   out_5818928030751659740[313] = 0;
   out_5818928030751659740[314] = 0;
   out_5818928030751659740[315] = 0;
   out_5818928030751659740[316] = 0;
   out_5818928030751659740[317] = 0;
   out_5818928030751659740[318] = 0;
   out_5818928030751659740[319] = 0;
   out_5818928030751659740[320] = 0;
   out_5818928030751659740[321] = 0;
   out_5818928030751659740[322] = 0;
   out_5818928030751659740[323] = 1;
}
void h_4(double *state, double *unused, double *out_3846056568958226266) {
   out_3846056568958226266[0] = state[6] + state[9];
   out_3846056568958226266[1] = state[7] + state[10];
   out_3846056568958226266[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8772672876909563643) {
   out_8772672876909563643[0] = 0;
   out_8772672876909563643[1] = 0;
   out_8772672876909563643[2] = 0;
   out_8772672876909563643[3] = 0;
   out_8772672876909563643[4] = 0;
   out_8772672876909563643[5] = 0;
   out_8772672876909563643[6] = 1;
   out_8772672876909563643[7] = 0;
   out_8772672876909563643[8] = 0;
   out_8772672876909563643[9] = 1;
   out_8772672876909563643[10] = 0;
   out_8772672876909563643[11] = 0;
   out_8772672876909563643[12] = 0;
   out_8772672876909563643[13] = 0;
   out_8772672876909563643[14] = 0;
   out_8772672876909563643[15] = 0;
   out_8772672876909563643[16] = 0;
   out_8772672876909563643[17] = 0;
   out_8772672876909563643[18] = 0;
   out_8772672876909563643[19] = 0;
   out_8772672876909563643[20] = 0;
   out_8772672876909563643[21] = 0;
   out_8772672876909563643[22] = 0;
   out_8772672876909563643[23] = 0;
   out_8772672876909563643[24] = 0;
   out_8772672876909563643[25] = 1;
   out_8772672876909563643[26] = 0;
   out_8772672876909563643[27] = 0;
   out_8772672876909563643[28] = 1;
   out_8772672876909563643[29] = 0;
   out_8772672876909563643[30] = 0;
   out_8772672876909563643[31] = 0;
   out_8772672876909563643[32] = 0;
   out_8772672876909563643[33] = 0;
   out_8772672876909563643[34] = 0;
   out_8772672876909563643[35] = 0;
   out_8772672876909563643[36] = 0;
   out_8772672876909563643[37] = 0;
   out_8772672876909563643[38] = 0;
   out_8772672876909563643[39] = 0;
   out_8772672876909563643[40] = 0;
   out_8772672876909563643[41] = 0;
   out_8772672876909563643[42] = 0;
   out_8772672876909563643[43] = 0;
   out_8772672876909563643[44] = 1;
   out_8772672876909563643[45] = 0;
   out_8772672876909563643[46] = 0;
   out_8772672876909563643[47] = 1;
   out_8772672876909563643[48] = 0;
   out_8772672876909563643[49] = 0;
   out_8772672876909563643[50] = 0;
   out_8772672876909563643[51] = 0;
   out_8772672876909563643[52] = 0;
   out_8772672876909563643[53] = 0;
}
void h_10(double *state, double *unused, double *out_3022049088022343856) {
   out_3022049088022343856[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3022049088022343856[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3022049088022343856[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4820309526576605798) {
   out_4820309526576605798[0] = 0;
   out_4820309526576605798[1] = 9.8100000000000005*cos(state[1]);
   out_4820309526576605798[2] = 0;
   out_4820309526576605798[3] = 0;
   out_4820309526576605798[4] = -state[8];
   out_4820309526576605798[5] = state[7];
   out_4820309526576605798[6] = 0;
   out_4820309526576605798[7] = state[5];
   out_4820309526576605798[8] = -state[4];
   out_4820309526576605798[9] = 0;
   out_4820309526576605798[10] = 0;
   out_4820309526576605798[11] = 0;
   out_4820309526576605798[12] = 1;
   out_4820309526576605798[13] = 0;
   out_4820309526576605798[14] = 0;
   out_4820309526576605798[15] = 1;
   out_4820309526576605798[16] = 0;
   out_4820309526576605798[17] = 0;
   out_4820309526576605798[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4820309526576605798[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4820309526576605798[20] = 0;
   out_4820309526576605798[21] = state[8];
   out_4820309526576605798[22] = 0;
   out_4820309526576605798[23] = -state[6];
   out_4820309526576605798[24] = -state[5];
   out_4820309526576605798[25] = 0;
   out_4820309526576605798[26] = state[3];
   out_4820309526576605798[27] = 0;
   out_4820309526576605798[28] = 0;
   out_4820309526576605798[29] = 0;
   out_4820309526576605798[30] = 0;
   out_4820309526576605798[31] = 1;
   out_4820309526576605798[32] = 0;
   out_4820309526576605798[33] = 0;
   out_4820309526576605798[34] = 1;
   out_4820309526576605798[35] = 0;
   out_4820309526576605798[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4820309526576605798[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4820309526576605798[38] = 0;
   out_4820309526576605798[39] = -state[7];
   out_4820309526576605798[40] = state[6];
   out_4820309526576605798[41] = 0;
   out_4820309526576605798[42] = state[4];
   out_4820309526576605798[43] = -state[3];
   out_4820309526576605798[44] = 0;
   out_4820309526576605798[45] = 0;
   out_4820309526576605798[46] = 0;
   out_4820309526576605798[47] = 0;
   out_4820309526576605798[48] = 0;
   out_4820309526576605798[49] = 0;
   out_4820309526576605798[50] = 1;
   out_4820309526576605798[51] = 0;
   out_4820309526576605798[52] = 0;
   out_4820309526576605798[53] = 1;
}
void h_13(double *state, double *unused, double *out_4676021508495622785) {
   out_4676021508495622785[0] = state[3];
   out_4676021508495622785[1] = state[4];
   out_4676021508495622785[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5560399051577230842) {
   out_5560399051577230842[0] = 0;
   out_5560399051577230842[1] = 0;
   out_5560399051577230842[2] = 0;
   out_5560399051577230842[3] = 1;
   out_5560399051577230842[4] = 0;
   out_5560399051577230842[5] = 0;
   out_5560399051577230842[6] = 0;
   out_5560399051577230842[7] = 0;
   out_5560399051577230842[8] = 0;
   out_5560399051577230842[9] = 0;
   out_5560399051577230842[10] = 0;
   out_5560399051577230842[11] = 0;
   out_5560399051577230842[12] = 0;
   out_5560399051577230842[13] = 0;
   out_5560399051577230842[14] = 0;
   out_5560399051577230842[15] = 0;
   out_5560399051577230842[16] = 0;
   out_5560399051577230842[17] = 0;
   out_5560399051577230842[18] = 0;
   out_5560399051577230842[19] = 0;
   out_5560399051577230842[20] = 0;
   out_5560399051577230842[21] = 0;
   out_5560399051577230842[22] = 1;
   out_5560399051577230842[23] = 0;
   out_5560399051577230842[24] = 0;
   out_5560399051577230842[25] = 0;
   out_5560399051577230842[26] = 0;
   out_5560399051577230842[27] = 0;
   out_5560399051577230842[28] = 0;
   out_5560399051577230842[29] = 0;
   out_5560399051577230842[30] = 0;
   out_5560399051577230842[31] = 0;
   out_5560399051577230842[32] = 0;
   out_5560399051577230842[33] = 0;
   out_5560399051577230842[34] = 0;
   out_5560399051577230842[35] = 0;
   out_5560399051577230842[36] = 0;
   out_5560399051577230842[37] = 0;
   out_5560399051577230842[38] = 0;
   out_5560399051577230842[39] = 0;
   out_5560399051577230842[40] = 0;
   out_5560399051577230842[41] = 1;
   out_5560399051577230842[42] = 0;
   out_5560399051577230842[43] = 0;
   out_5560399051577230842[44] = 0;
   out_5560399051577230842[45] = 0;
   out_5560399051577230842[46] = 0;
   out_5560399051577230842[47] = 0;
   out_5560399051577230842[48] = 0;
   out_5560399051577230842[49] = 0;
   out_5560399051577230842[50] = 0;
   out_5560399051577230842[51] = 0;
   out_5560399051577230842[52] = 0;
   out_5560399051577230842[53] = 0;
}
void h_14(double *state, double *unused, double *out_7231214306405891091) {
   out_7231214306405891091[0] = state[6];
   out_7231214306405891091[1] = state[7];
   out_7231214306405891091[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4809432020570079114) {
   out_4809432020570079114[0] = 0;
   out_4809432020570079114[1] = 0;
   out_4809432020570079114[2] = 0;
   out_4809432020570079114[3] = 0;
   out_4809432020570079114[4] = 0;
   out_4809432020570079114[5] = 0;
   out_4809432020570079114[6] = 1;
   out_4809432020570079114[7] = 0;
   out_4809432020570079114[8] = 0;
   out_4809432020570079114[9] = 0;
   out_4809432020570079114[10] = 0;
   out_4809432020570079114[11] = 0;
   out_4809432020570079114[12] = 0;
   out_4809432020570079114[13] = 0;
   out_4809432020570079114[14] = 0;
   out_4809432020570079114[15] = 0;
   out_4809432020570079114[16] = 0;
   out_4809432020570079114[17] = 0;
   out_4809432020570079114[18] = 0;
   out_4809432020570079114[19] = 0;
   out_4809432020570079114[20] = 0;
   out_4809432020570079114[21] = 0;
   out_4809432020570079114[22] = 0;
   out_4809432020570079114[23] = 0;
   out_4809432020570079114[24] = 0;
   out_4809432020570079114[25] = 1;
   out_4809432020570079114[26] = 0;
   out_4809432020570079114[27] = 0;
   out_4809432020570079114[28] = 0;
   out_4809432020570079114[29] = 0;
   out_4809432020570079114[30] = 0;
   out_4809432020570079114[31] = 0;
   out_4809432020570079114[32] = 0;
   out_4809432020570079114[33] = 0;
   out_4809432020570079114[34] = 0;
   out_4809432020570079114[35] = 0;
   out_4809432020570079114[36] = 0;
   out_4809432020570079114[37] = 0;
   out_4809432020570079114[38] = 0;
   out_4809432020570079114[39] = 0;
   out_4809432020570079114[40] = 0;
   out_4809432020570079114[41] = 0;
   out_4809432020570079114[42] = 0;
   out_4809432020570079114[43] = 0;
   out_4809432020570079114[44] = 1;
   out_4809432020570079114[45] = 0;
   out_4809432020570079114[46] = 0;
   out_4809432020570079114[47] = 0;
   out_4809432020570079114[48] = 0;
   out_4809432020570079114[49] = 0;
   out_4809432020570079114[50] = 0;
   out_4809432020570079114[51] = 0;
   out_4809432020570079114[52] = 0;
   out_4809432020570079114[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2844503766928312028) {
  err_fun(nom_x, delta_x, out_2844503766928312028);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_188944154440250924) {
  inv_err_fun(nom_x, true_x, out_188944154440250924);
}
void pose_H_mod_fun(double *state, double *out_7217718077783114524) {
  H_mod_fun(state, out_7217718077783114524);
}
void pose_f_fun(double *state, double dt, double *out_6254706918453181358) {
  f_fun(state,  dt, out_6254706918453181358);
}
void pose_F_fun(double *state, double dt, double *out_5818928030751659740) {
  F_fun(state,  dt, out_5818928030751659740);
}
void pose_h_4(double *state, double *unused, double *out_3846056568958226266) {
  h_4(state, unused, out_3846056568958226266);
}
void pose_H_4(double *state, double *unused, double *out_8772672876909563643) {
  H_4(state, unused, out_8772672876909563643);
}
void pose_h_10(double *state, double *unused, double *out_3022049088022343856) {
  h_10(state, unused, out_3022049088022343856);
}
void pose_H_10(double *state, double *unused, double *out_4820309526576605798) {
  H_10(state, unused, out_4820309526576605798);
}
void pose_h_13(double *state, double *unused, double *out_4676021508495622785) {
  h_13(state, unused, out_4676021508495622785);
}
void pose_H_13(double *state, double *unused, double *out_5560399051577230842) {
  H_13(state, unused, out_5560399051577230842);
}
void pose_h_14(double *state, double *unused, double *out_7231214306405891091) {
  h_14(state, unused, out_7231214306405891091);
}
void pose_H_14(double *state, double *unused, double *out_4809432020570079114) {
  H_14(state, unused, out_4809432020570079114);
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
