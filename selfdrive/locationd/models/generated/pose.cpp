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
void err_fun(double *nom_x, double *delta_x, double *out_6308403071375908873) {
   out_6308403071375908873[0] = delta_x[0] + nom_x[0];
   out_6308403071375908873[1] = delta_x[1] + nom_x[1];
   out_6308403071375908873[2] = delta_x[2] + nom_x[2];
   out_6308403071375908873[3] = delta_x[3] + nom_x[3];
   out_6308403071375908873[4] = delta_x[4] + nom_x[4];
   out_6308403071375908873[5] = delta_x[5] + nom_x[5];
   out_6308403071375908873[6] = delta_x[6] + nom_x[6];
   out_6308403071375908873[7] = delta_x[7] + nom_x[7];
   out_6308403071375908873[8] = delta_x[8] + nom_x[8];
   out_6308403071375908873[9] = delta_x[9] + nom_x[9];
   out_6308403071375908873[10] = delta_x[10] + nom_x[10];
   out_6308403071375908873[11] = delta_x[11] + nom_x[11];
   out_6308403071375908873[12] = delta_x[12] + nom_x[12];
   out_6308403071375908873[13] = delta_x[13] + nom_x[13];
   out_6308403071375908873[14] = delta_x[14] + nom_x[14];
   out_6308403071375908873[15] = delta_x[15] + nom_x[15];
   out_6308403071375908873[16] = delta_x[16] + nom_x[16];
   out_6308403071375908873[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5050968420956665665) {
   out_5050968420956665665[0] = -nom_x[0] + true_x[0];
   out_5050968420956665665[1] = -nom_x[1] + true_x[1];
   out_5050968420956665665[2] = -nom_x[2] + true_x[2];
   out_5050968420956665665[3] = -nom_x[3] + true_x[3];
   out_5050968420956665665[4] = -nom_x[4] + true_x[4];
   out_5050968420956665665[5] = -nom_x[5] + true_x[5];
   out_5050968420956665665[6] = -nom_x[6] + true_x[6];
   out_5050968420956665665[7] = -nom_x[7] + true_x[7];
   out_5050968420956665665[8] = -nom_x[8] + true_x[8];
   out_5050968420956665665[9] = -nom_x[9] + true_x[9];
   out_5050968420956665665[10] = -nom_x[10] + true_x[10];
   out_5050968420956665665[11] = -nom_x[11] + true_x[11];
   out_5050968420956665665[12] = -nom_x[12] + true_x[12];
   out_5050968420956665665[13] = -nom_x[13] + true_x[13];
   out_5050968420956665665[14] = -nom_x[14] + true_x[14];
   out_5050968420956665665[15] = -nom_x[15] + true_x[15];
   out_5050968420956665665[16] = -nom_x[16] + true_x[16];
   out_5050968420956665665[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7135066242214707114) {
   out_7135066242214707114[0] = 1.0;
   out_7135066242214707114[1] = 0.0;
   out_7135066242214707114[2] = 0.0;
   out_7135066242214707114[3] = 0.0;
   out_7135066242214707114[4] = 0.0;
   out_7135066242214707114[5] = 0.0;
   out_7135066242214707114[6] = 0.0;
   out_7135066242214707114[7] = 0.0;
   out_7135066242214707114[8] = 0.0;
   out_7135066242214707114[9] = 0.0;
   out_7135066242214707114[10] = 0.0;
   out_7135066242214707114[11] = 0.0;
   out_7135066242214707114[12] = 0.0;
   out_7135066242214707114[13] = 0.0;
   out_7135066242214707114[14] = 0.0;
   out_7135066242214707114[15] = 0.0;
   out_7135066242214707114[16] = 0.0;
   out_7135066242214707114[17] = 0.0;
   out_7135066242214707114[18] = 0.0;
   out_7135066242214707114[19] = 1.0;
   out_7135066242214707114[20] = 0.0;
   out_7135066242214707114[21] = 0.0;
   out_7135066242214707114[22] = 0.0;
   out_7135066242214707114[23] = 0.0;
   out_7135066242214707114[24] = 0.0;
   out_7135066242214707114[25] = 0.0;
   out_7135066242214707114[26] = 0.0;
   out_7135066242214707114[27] = 0.0;
   out_7135066242214707114[28] = 0.0;
   out_7135066242214707114[29] = 0.0;
   out_7135066242214707114[30] = 0.0;
   out_7135066242214707114[31] = 0.0;
   out_7135066242214707114[32] = 0.0;
   out_7135066242214707114[33] = 0.0;
   out_7135066242214707114[34] = 0.0;
   out_7135066242214707114[35] = 0.0;
   out_7135066242214707114[36] = 0.0;
   out_7135066242214707114[37] = 0.0;
   out_7135066242214707114[38] = 1.0;
   out_7135066242214707114[39] = 0.0;
   out_7135066242214707114[40] = 0.0;
   out_7135066242214707114[41] = 0.0;
   out_7135066242214707114[42] = 0.0;
   out_7135066242214707114[43] = 0.0;
   out_7135066242214707114[44] = 0.0;
   out_7135066242214707114[45] = 0.0;
   out_7135066242214707114[46] = 0.0;
   out_7135066242214707114[47] = 0.0;
   out_7135066242214707114[48] = 0.0;
   out_7135066242214707114[49] = 0.0;
   out_7135066242214707114[50] = 0.0;
   out_7135066242214707114[51] = 0.0;
   out_7135066242214707114[52] = 0.0;
   out_7135066242214707114[53] = 0.0;
   out_7135066242214707114[54] = 0.0;
   out_7135066242214707114[55] = 0.0;
   out_7135066242214707114[56] = 0.0;
   out_7135066242214707114[57] = 1.0;
   out_7135066242214707114[58] = 0.0;
   out_7135066242214707114[59] = 0.0;
   out_7135066242214707114[60] = 0.0;
   out_7135066242214707114[61] = 0.0;
   out_7135066242214707114[62] = 0.0;
   out_7135066242214707114[63] = 0.0;
   out_7135066242214707114[64] = 0.0;
   out_7135066242214707114[65] = 0.0;
   out_7135066242214707114[66] = 0.0;
   out_7135066242214707114[67] = 0.0;
   out_7135066242214707114[68] = 0.0;
   out_7135066242214707114[69] = 0.0;
   out_7135066242214707114[70] = 0.0;
   out_7135066242214707114[71] = 0.0;
   out_7135066242214707114[72] = 0.0;
   out_7135066242214707114[73] = 0.0;
   out_7135066242214707114[74] = 0.0;
   out_7135066242214707114[75] = 0.0;
   out_7135066242214707114[76] = 1.0;
   out_7135066242214707114[77] = 0.0;
   out_7135066242214707114[78] = 0.0;
   out_7135066242214707114[79] = 0.0;
   out_7135066242214707114[80] = 0.0;
   out_7135066242214707114[81] = 0.0;
   out_7135066242214707114[82] = 0.0;
   out_7135066242214707114[83] = 0.0;
   out_7135066242214707114[84] = 0.0;
   out_7135066242214707114[85] = 0.0;
   out_7135066242214707114[86] = 0.0;
   out_7135066242214707114[87] = 0.0;
   out_7135066242214707114[88] = 0.0;
   out_7135066242214707114[89] = 0.0;
   out_7135066242214707114[90] = 0.0;
   out_7135066242214707114[91] = 0.0;
   out_7135066242214707114[92] = 0.0;
   out_7135066242214707114[93] = 0.0;
   out_7135066242214707114[94] = 0.0;
   out_7135066242214707114[95] = 1.0;
   out_7135066242214707114[96] = 0.0;
   out_7135066242214707114[97] = 0.0;
   out_7135066242214707114[98] = 0.0;
   out_7135066242214707114[99] = 0.0;
   out_7135066242214707114[100] = 0.0;
   out_7135066242214707114[101] = 0.0;
   out_7135066242214707114[102] = 0.0;
   out_7135066242214707114[103] = 0.0;
   out_7135066242214707114[104] = 0.0;
   out_7135066242214707114[105] = 0.0;
   out_7135066242214707114[106] = 0.0;
   out_7135066242214707114[107] = 0.0;
   out_7135066242214707114[108] = 0.0;
   out_7135066242214707114[109] = 0.0;
   out_7135066242214707114[110] = 0.0;
   out_7135066242214707114[111] = 0.0;
   out_7135066242214707114[112] = 0.0;
   out_7135066242214707114[113] = 0.0;
   out_7135066242214707114[114] = 1.0;
   out_7135066242214707114[115] = 0.0;
   out_7135066242214707114[116] = 0.0;
   out_7135066242214707114[117] = 0.0;
   out_7135066242214707114[118] = 0.0;
   out_7135066242214707114[119] = 0.0;
   out_7135066242214707114[120] = 0.0;
   out_7135066242214707114[121] = 0.0;
   out_7135066242214707114[122] = 0.0;
   out_7135066242214707114[123] = 0.0;
   out_7135066242214707114[124] = 0.0;
   out_7135066242214707114[125] = 0.0;
   out_7135066242214707114[126] = 0.0;
   out_7135066242214707114[127] = 0.0;
   out_7135066242214707114[128] = 0.0;
   out_7135066242214707114[129] = 0.0;
   out_7135066242214707114[130] = 0.0;
   out_7135066242214707114[131] = 0.0;
   out_7135066242214707114[132] = 0.0;
   out_7135066242214707114[133] = 1.0;
   out_7135066242214707114[134] = 0.0;
   out_7135066242214707114[135] = 0.0;
   out_7135066242214707114[136] = 0.0;
   out_7135066242214707114[137] = 0.0;
   out_7135066242214707114[138] = 0.0;
   out_7135066242214707114[139] = 0.0;
   out_7135066242214707114[140] = 0.0;
   out_7135066242214707114[141] = 0.0;
   out_7135066242214707114[142] = 0.0;
   out_7135066242214707114[143] = 0.0;
   out_7135066242214707114[144] = 0.0;
   out_7135066242214707114[145] = 0.0;
   out_7135066242214707114[146] = 0.0;
   out_7135066242214707114[147] = 0.0;
   out_7135066242214707114[148] = 0.0;
   out_7135066242214707114[149] = 0.0;
   out_7135066242214707114[150] = 0.0;
   out_7135066242214707114[151] = 0.0;
   out_7135066242214707114[152] = 1.0;
   out_7135066242214707114[153] = 0.0;
   out_7135066242214707114[154] = 0.0;
   out_7135066242214707114[155] = 0.0;
   out_7135066242214707114[156] = 0.0;
   out_7135066242214707114[157] = 0.0;
   out_7135066242214707114[158] = 0.0;
   out_7135066242214707114[159] = 0.0;
   out_7135066242214707114[160] = 0.0;
   out_7135066242214707114[161] = 0.0;
   out_7135066242214707114[162] = 0.0;
   out_7135066242214707114[163] = 0.0;
   out_7135066242214707114[164] = 0.0;
   out_7135066242214707114[165] = 0.0;
   out_7135066242214707114[166] = 0.0;
   out_7135066242214707114[167] = 0.0;
   out_7135066242214707114[168] = 0.0;
   out_7135066242214707114[169] = 0.0;
   out_7135066242214707114[170] = 0.0;
   out_7135066242214707114[171] = 1.0;
   out_7135066242214707114[172] = 0.0;
   out_7135066242214707114[173] = 0.0;
   out_7135066242214707114[174] = 0.0;
   out_7135066242214707114[175] = 0.0;
   out_7135066242214707114[176] = 0.0;
   out_7135066242214707114[177] = 0.0;
   out_7135066242214707114[178] = 0.0;
   out_7135066242214707114[179] = 0.0;
   out_7135066242214707114[180] = 0.0;
   out_7135066242214707114[181] = 0.0;
   out_7135066242214707114[182] = 0.0;
   out_7135066242214707114[183] = 0.0;
   out_7135066242214707114[184] = 0.0;
   out_7135066242214707114[185] = 0.0;
   out_7135066242214707114[186] = 0.0;
   out_7135066242214707114[187] = 0.0;
   out_7135066242214707114[188] = 0.0;
   out_7135066242214707114[189] = 0.0;
   out_7135066242214707114[190] = 1.0;
   out_7135066242214707114[191] = 0.0;
   out_7135066242214707114[192] = 0.0;
   out_7135066242214707114[193] = 0.0;
   out_7135066242214707114[194] = 0.0;
   out_7135066242214707114[195] = 0.0;
   out_7135066242214707114[196] = 0.0;
   out_7135066242214707114[197] = 0.0;
   out_7135066242214707114[198] = 0.0;
   out_7135066242214707114[199] = 0.0;
   out_7135066242214707114[200] = 0.0;
   out_7135066242214707114[201] = 0.0;
   out_7135066242214707114[202] = 0.0;
   out_7135066242214707114[203] = 0.0;
   out_7135066242214707114[204] = 0.0;
   out_7135066242214707114[205] = 0.0;
   out_7135066242214707114[206] = 0.0;
   out_7135066242214707114[207] = 0.0;
   out_7135066242214707114[208] = 0.0;
   out_7135066242214707114[209] = 1.0;
   out_7135066242214707114[210] = 0.0;
   out_7135066242214707114[211] = 0.0;
   out_7135066242214707114[212] = 0.0;
   out_7135066242214707114[213] = 0.0;
   out_7135066242214707114[214] = 0.0;
   out_7135066242214707114[215] = 0.0;
   out_7135066242214707114[216] = 0.0;
   out_7135066242214707114[217] = 0.0;
   out_7135066242214707114[218] = 0.0;
   out_7135066242214707114[219] = 0.0;
   out_7135066242214707114[220] = 0.0;
   out_7135066242214707114[221] = 0.0;
   out_7135066242214707114[222] = 0.0;
   out_7135066242214707114[223] = 0.0;
   out_7135066242214707114[224] = 0.0;
   out_7135066242214707114[225] = 0.0;
   out_7135066242214707114[226] = 0.0;
   out_7135066242214707114[227] = 0.0;
   out_7135066242214707114[228] = 1.0;
   out_7135066242214707114[229] = 0.0;
   out_7135066242214707114[230] = 0.0;
   out_7135066242214707114[231] = 0.0;
   out_7135066242214707114[232] = 0.0;
   out_7135066242214707114[233] = 0.0;
   out_7135066242214707114[234] = 0.0;
   out_7135066242214707114[235] = 0.0;
   out_7135066242214707114[236] = 0.0;
   out_7135066242214707114[237] = 0.0;
   out_7135066242214707114[238] = 0.0;
   out_7135066242214707114[239] = 0.0;
   out_7135066242214707114[240] = 0.0;
   out_7135066242214707114[241] = 0.0;
   out_7135066242214707114[242] = 0.0;
   out_7135066242214707114[243] = 0.0;
   out_7135066242214707114[244] = 0.0;
   out_7135066242214707114[245] = 0.0;
   out_7135066242214707114[246] = 0.0;
   out_7135066242214707114[247] = 1.0;
   out_7135066242214707114[248] = 0.0;
   out_7135066242214707114[249] = 0.0;
   out_7135066242214707114[250] = 0.0;
   out_7135066242214707114[251] = 0.0;
   out_7135066242214707114[252] = 0.0;
   out_7135066242214707114[253] = 0.0;
   out_7135066242214707114[254] = 0.0;
   out_7135066242214707114[255] = 0.0;
   out_7135066242214707114[256] = 0.0;
   out_7135066242214707114[257] = 0.0;
   out_7135066242214707114[258] = 0.0;
   out_7135066242214707114[259] = 0.0;
   out_7135066242214707114[260] = 0.0;
   out_7135066242214707114[261] = 0.0;
   out_7135066242214707114[262] = 0.0;
   out_7135066242214707114[263] = 0.0;
   out_7135066242214707114[264] = 0.0;
   out_7135066242214707114[265] = 0.0;
   out_7135066242214707114[266] = 1.0;
   out_7135066242214707114[267] = 0.0;
   out_7135066242214707114[268] = 0.0;
   out_7135066242214707114[269] = 0.0;
   out_7135066242214707114[270] = 0.0;
   out_7135066242214707114[271] = 0.0;
   out_7135066242214707114[272] = 0.0;
   out_7135066242214707114[273] = 0.0;
   out_7135066242214707114[274] = 0.0;
   out_7135066242214707114[275] = 0.0;
   out_7135066242214707114[276] = 0.0;
   out_7135066242214707114[277] = 0.0;
   out_7135066242214707114[278] = 0.0;
   out_7135066242214707114[279] = 0.0;
   out_7135066242214707114[280] = 0.0;
   out_7135066242214707114[281] = 0.0;
   out_7135066242214707114[282] = 0.0;
   out_7135066242214707114[283] = 0.0;
   out_7135066242214707114[284] = 0.0;
   out_7135066242214707114[285] = 1.0;
   out_7135066242214707114[286] = 0.0;
   out_7135066242214707114[287] = 0.0;
   out_7135066242214707114[288] = 0.0;
   out_7135066242214707114[289] = 0.0;
   out_7135066242214707114[290] = 0.0;
   out_7135066242214707114[291] = 0.0;
   out_7135066242214707114[292] = 0.0;
   out_7135066242214707114[293] = 0.0;
   out_7135066242214707114[294] = 0.0;
   out_7135066242214707114[295] = 0.0;
   out_7135066242214707114[296] = 0.0;
   out_7135066242214707114[297] = 0.0;
   out_7135066242214707114[298] = 0.0;
   out_7135066242214707114[299] = 0.0;
   out_7135066242214707114[300] = 0.0;
   out_7135066242214707114[301] = 0.0;
   out_7135066242214707114[302] = 0.0;
   out_7135066242214707114[303] = 0.0;
   out_7135066242214707114[304] = 1.0;
   out_7135066242214707114[305] = 0.0;
   out_7135066242214707114[306] = 0.0;
   out_7135066242214707114[307] = 0.0;
   out_7135066242214707114[308] = 0.0;
   out_7135066242214707114[309] = 0.0;
   out_7135066242214707114[310] = 0.0;
   out_7135066242214707114[311] = 0.0;
   out_7135066242214707114[312] = 0.0;
   out_7135066242214707114[313] = 0.0;
   out_7135066242214707114[314] = 0.0;
   out_7135066242214707114[315] = 0.0;
   out_7135066242214707114[316] = 0.0;
   out_7135066242214707114[317] = 0.0;
   out_7135066242214707114[318] = 0.0;
   out_7135066242214707114[319] = 0.0;
   out_7135066242214707114[320] = 0.0;
   out_7135066242214707114[321] = 0.0;
   out_7135066242214707114[322] = 0.0;
   out_7135066242214707114[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1066594021391050582) {
   out_1066594021391050582[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1066594021391050582[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1066594021391050582[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1066594021391050582[3] = dt*state[12] + state[3];
   out_1066594021391050582[4] = dt*state[13] + state[4];
   out_1066594021391050582[5] = dt*state[14] + state[5];
   out_1066594021391050582[6] = state[6];
   out_1066594021391050582[7] = state[7];
   out_1066594021391050582[8] = state[8];
   out_1066594021391050582[9] = state[9];
   out_1066594021391050582[10] = state[10];
   out_1066594021391050582[11] = state[11];
   out_1066594021391050582[12] = state[12];
   out_1066594021391050582[13] = state[13];
   out_1066594021391050582[14] = state[14];
   out_1066594021391050582[15] = state[15];
   out_1066594021391050582[16] = state[16];
   out_1066594021391050582[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4090974996683569946) {
   out_4090974996683569946[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4090974996683569946[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4090974996683569946[2] = 0;
   out_4090974996683569946[3] = 0;
   out_4090974996683569946[4] = 0;
   out_4090974996683569946[5] = 0;
   out_4090974996683569946[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4090974996683569946[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4090974996683569946[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4090974996683569946[9] = 0;
   out_4090974996683569946[10] = 0;
   out_4090974996683569946[11] = 0;
   out_4090974996683569946[12] = 0;
   out_4090974996683569946[13] = 0;
   out_4090974996683569946[14] = 0;
   out_4090974996683569946[15] = 0;
   out_4090974996683569946[16] = 0;
   out_4090974996683569946[17] = 0;
   out_4090974996683569946[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4090974996683569946[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4090974996683569946[20] = 0;
   out_4090974996683569946[21] = 0;
   out_4090974996683569946[22] = 0;
   out_4090974996683569946[23] = 0;
   out_4090974996683569946[24] = 0;
   out_4090974996683569946[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4090974996683569946[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4090974996683569946[27] = 0;
   out_4090974996683569946[28] = 0;
   out_4090974996683569946[29] = 0;
   out_4090974996683569946[30] = 0;
   out_4090974996683569946[31] = 0;
   out_4090974996683569946[32] = 0;
   out_4090974996683569946[33] = 0;
   out_4090974996683569946[34] = 0;
   out_4090974996683569946[35] = 0;
   out_4090974996683569946[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4090974996683569946[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4090974996683569946[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4090974996683569946[39] = 0;
   out_4090974996683569946[40] = 0;
   out_4090974996683569946[41] = 0;
   out_4090974996683569946[42] = 0;
   out_4090974996683569946[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4090974996683569946[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4090974996683569946[45] = 0;
   out_4090974996683569946[46] = 0;
   out_4090974996683569946[47] = 0;
   out_4090974996683569946[48] = 0;
   out_4090974996683569946[49] = 0;
   out_4090974996683569946[50] = 0;
   out_4090974996683569946[51] = 0;
   out_4090974996683569946[52] = 0;
   out_4090974996683569946[53] = 0;
   out_4090974996683569946[54] = 0;
   out_4090974996683569946[55] = 0;
   out_4090974996683569946[56] = 0;
   out_4090974996683569946[57] = 1;
   out_4090974996683569946[58] = 0;
   out_4090974996683569946[59] = 0;
   out_4090974996683569946[60] = 0;
   out_4090974996683569946[61] = 0;
   out_4090974996683569946[62] = 0;
   out_4090974996683569946[63] = 0;
   out_4090974996683569946[64] = 0;
   out_4090974996683569946[65] = 0;
   out_4090974996683569946[66] = dt;
   out_4090974996683569946[67] = 0;
   out_4090974996683569946[68] = 0;
   out_4090974996683569946[69] = 0;
   out_4090974996683569946[70] = 0;
   out_4090974996683569946[71] = 0;
   out_4090974996683569946[72] = 0;
   out_4090974996683569946[73] = 0;
   out_4090974996683569946[74] = 0;
   out_4090974996683569946[75] = 0;
   out_4090974996683569946[76] = 1;
   out_4090974996683569946[77] = 0;
   out_4090974996683569946[78] = 0;
   out_4090974996683569946[79] = 0;
   out_4090974996683569946[80] = 0;
   out_4090974996683569946[81] = 0;
   out_4090974996683569946[82] = 0;
   out_4090974996683569946[83] = 0;
   out_4090974996683569946[84] = 0;
   out_4090974996683569946[85] = dt;
   out_4090974996683569946[86] = 0;
   out_4090974996683569946[87] = 0;
   out_4090974996683569946[88] = 0;
   out_4090974996683569946[89] = 0;
   out_4090974996683569946[90] = 0;
   out_4090974996683569946[91] = 0;
   out_4090974996683569946[92] = 0;
   out_4090974996683569946[93] = 0;
   out_4090974996683569946[94] = 0;
   out_4090974996683569946[95] = 1;
   out_4090974996683569946[96] = 0;
   out_4090974996683569946[97] = 0;
   out_4090974996683569946[98] = 0;
   out_4090974996683569946[99] = 0;
   out_4090974996683569946[100] = 0;
   out_4090974996683569946[101] = 0;
   out_4090974996683569946[102] = 0;
   out_4090974996683569946[103] = 0;
   out_4090974996683569946[104] = dt;
   out_4090974996683569946[105] = 0;
   out_4090974996683569946[106] = 0;
   out_4090974996683569946[107] = 0;
   out_4090974996683569946[108] = 0;
   out_4090974996683569946[109] = 0;
   out_4090974996683569946[110] = 0;
   out_4090974996683569946[111] = 0;
   out_4090974996683569946[112] = 0;
   out_4090974996683569946[113] = 0;
   out_4090974996683569946[114] = 1;
   out_4090974996683569946[115] = 0;
   out_4090974996683569946[116] = 0;
   out_4090974996683569946[117] = 0;
   out_4090974996683569946[118] = 0;
   out_4090974996683569946[119] = 0;
   out_4090974996683569946[120] = 0;
   out_4090974996683569946[121] = 0;
   out_4090974996683569946[122] = 0;
   out_4090974996683569946[123] = 0;
   out_4090974996683569946[124] = 0;
   out_4090974996683569946[125] = 0;
   out_4090974996683569946[126] = 0;
   out_4090974996683569946[127] = 0;
   out_4090974996683569946[128] = 0;
   out_4090974996683569946[129] = 0;
   out_4090974996683569946[130] = 0;
   out_4090974996683569946[131] = 0;
   out_4090974996683569946[132] = 0;
   out_4090974996683569946[133] = 1;
   out_4090974996683569946[134] = 0;
   out_4090974996683569946[135] = 0;
   out_4090974996683569946[136] = 0;
   out_4090974996683569946[137] = 0;
   out_4090974996683569946[138] = 0;
   out_4090974996683569946[139] = 0;
   out_4090974996683569946[140] = 0;
   out_4090974996683569946[141] = 0;
   out_4090974996683569946[142] = 0;
   out_4090974996683569946[143] = 0;
   out_4090974996683569946[144] = 0;
   out_4090974996683569946[145] = 0;
   out_4090974996683569946[146] = 0;
   out_4090974996683569946[147] = 0;
   out_4090974996683569946[148] = 0;
   out_4090974996683569946[149] = 0;
   out_4090974996683569946[150] = 0;
   out_4090974996683569946[151] = 0;
   out_4090974996683569946[152] = 1;
   out_4090974996683569946[153] = 0;
   out_4090974996683569946[154] = 0;
   out_4090974996683569946[155] = 0;
   out_4090974996683569946[156] = 0;
   out_4090974996683569946[157] = 0;
   out_4090974996683569946[158] = 0;
   out_4090974996683569946[159] = 0;
   out_4090974996683569946[160] = 0;
   out_4090974996683569946[161] = 0;
   out_4090974996683569946[162] = 0;
   out_4090974996683569946[163] = 0;
   out_4090974996683569946[164] = 0;
   out_4090974996683569946[165] = 0;
   out_4090974996683569946[166] = 0;
   out_4090974996683569946[167] = 0;
   out_4090974996683569946[168] = 0;
   out_4090974996683569946[169] = 0;
   out_4090974996683569946[170] = 0;
   out_4090974996683569946[171] = 1;
   out_4090974996683569946[172] = 0;
   out_4090974996683569946[173] = 0;
   out_4090974996683569946[174] = 0;
   out_4090974996683569946[175] = 0;
   out_4090974996683569946[176] = 0;
   out_4090974996683569946[177] = 0;
   out_4090974996683569946[178] = 0;
   out_4090974996683569946[179] = 0;
   out_4090974996683569946[180] = 0;
   out_4090974996683569946[181] = 0;
   out_4090974996683569946[182] = 0;
   out_4090974996683569946[183] = 0;
   out_4090974996683569946[184] = 0;
   out_4090974996683569946[185] = 0;
   out_4090974996683569946[186] = 0;
   out_4090974996683569946[187] = 0;
   out_4090974996683569946[188] = 0;
   out_4090974996683569946[189] = 0;
   out_4090974996683569946[190] = 1;
   out_4090974996683569946[191] = 0;
   out_4090974996683569946[192] = 0;
   out_4090974996683569946[193] = 0;
   out_4090974996683569946[194] = 0;
   out_4090974996683569946[195] = 0;
   out_4090974996683569946[196] = 0;
   out_4090974996683569946[197] = 0;
   out_4090974996683569946[198] = 0;
   out_4090974996683569946[199] = 0;
   out_4090974996683569946[200] = 0;
   out_4090974996683569946[201] = 0;
   out_4090974996683569946[202] = 0;
   out_4090974996683569946[203] = 0;
   out_4090974996683569946[204] = 0;
   out_4090974996683569946[205] = 0;
   out_4090974996683569946[206] = 0;
   out_4090974996683569946[207] = 0;
   out_4090974996683569946[208] = 0;
   out_4090974996683569946[209] = 1;
   out_4090974996683569946[210] = 0;
   out_4090974996683569946[211] = 0;
   out_4090974996683569946[212] = 0;
   out_4090974996683569946[213] = 0;
   out_4090974996683569946[214] = 0;
   out_4090974996683569946[215] = 0;
   out_4090974996683569946[216] = 0;
   out_4090974996683569946[217] = 0;
   out_4090974996683569946[218] = 0;
   out_4090974996683569946[219] = 0;
   out_4090974996683569946[220] = 0;
   out_4090974996683569946[221] = 0;
   out_4090974996683569946[222] = 0;
   out_4090974996683569946[223] = 0;
   out_4090974996683569946[224] = 0;
   out_4090974996683569946[225] = 0;
   out_4090974996683569946[226] = 0;
   out_4090974996683569946[227] = 0;
   out_4090974996683569946[228] = 1;
   out_4090974996683569946[229] = 0;
   out_4090974996683569946[230] = 0;
   out_4090974996683569946[231] = 0;
   out_4090974996683569946[232] = 0;
   out_4090974996683569946[233] = 0;
   out_4090974996683569946[234] = 0;
   out_4090974996683569946[235] = 0;
   out_4090974996683569946[236] = 0;
   out_4090974996683569946[237] = 0;
   out_4090974996683569946[238] = 0;
   out_4090974996683569946[239] = 0;
   out_4090974996683569946[240] = 0;
   out_4090974996683569946[241] = 0;
   out_4090974996683569946[242] = 0;
   out_4090974996683569946[243] = 0;
   out_4090974996683569946[244] = 0;
   out_4090974996683569946[245] = 0;
   out_4090974996683569946[246] = 0;
   out_4090974996683569946[247] = 1;
   out_4090974996683569946[248] = 0;
   out_4090974996683569946[249] = 0;
   out_4090974996683569946[250] = 0;
   out_4090974996683569946[251] = 0;
   out_4090974996683569946[252] = 0;
   out_4090974996683569946[253] = 0;
   out_4090974996683569946[254] = 0;
   out_4090974996683569946[255] = 0;
   out_4090974996683569946[256] = 0;
   out_4090974996683569946[257] = 0;
   out_4090974996683569946[258] = 0;
   out_4090974996683569946[259] = 0;
   out_4090974996683569946[260] = 0;
   out_4090974996683569946[261] = 0;
   out_4090974996683569946[262] = 0;
   out_4090974996683569946[263] = 0;
   out_4090974996683569946[264] = 0;
   out_4090974996683569946[265] = 0;
   out_4090974996683569946[266] = 1;
   out_4090974996683569946[267] = 0;
   out_4090974996683569946[268] = 0;
   out_4090974996683569946[269] = 0;
   out_4090974996683569946[270] = 0;
   out_4090974996683569946[271] = 0;
   out_4090974996683569946[272] = 0;
   out_4090974996683569946[273] = 0;
   out_4090974996683569946[274] = 0;
   out_4090974996683569946[275] = 0;
   out_4090974996683569946[276] = 0;
   out_4090974996683569946[277] = 0;
   out_4090974996683569946[278] = 0;
   out_4090974996683569946[279] = 0;
   out_4090974996683569946[280] = 0;
   out_4090974996683569946[281] = 0;
   out_4090974996683569946[282] = 0;
   out_4090974996683569946[283] = 0;
   out_4090974996683569946[284] = 0;
   out_4090974996683569946[285] = 1;
   out_4090974996683569946[286] = 0;
   out_4090974996683569946[287] = 0;
   out_4090974996683569946[288] = 0;
   out_4090974996683569946[289] = 0;
   out_4090974996683569946[290] = 0;
   out_4090974996683569946[291] = 0;
   out_4090974996683569946[292] = 0;
   out_4090974996683569946[293] = 0;
   out_4090974996683569946[294] = 0;
   out_4090974996683569946[295] = 0;
   out_4090974996683569946[296] = 0;
   out_4090974996683569946[297] = 0;
   out_4090974996683569946[298] = 0;
   out_4090974996683569946[299] = 0;
   out_4090974996683569946[300] = 0;
   out_4090974996683569946[301] = 0;
   out_4090974996683569946[302] = 0;
   out_4090974996683569946[303] = 0;
   out_4090974996683569946[304] = 1;
   out_4090974996683569946[305] = 0;
   out_4090974996683569946[306] = 0;
   out_4090974996683569946[307] = 0;
   out_4090974996683569946[308] = 0;
   out_4090974996683569946[309] = 0;
   out_4090974996683569946[310] = 0;
   out_4090974996683569946[311] = 0;
   out_4090974996683569946[312] = 0;
   out_4090974996683569946[313] = 0;
   out_4090974996683569946[314] = 0;
   out_4090974996683569946[315] = 0;
   out_4090974996683569946[316] = 0;
   out_4090974996683569946[317] = 0;
   out_4090974996683569946[318] = 0;
   out_4090974996683569946[319] = 0;
   out_4090974996683569946[320] = 0;
   out_4090974996683569946[321] = 0;
   out_4090974996683569946[322] = 0;
   out_4090974996683569946[323] = 1;
}
void h_4(double *state, double *unused, double *out_5017787030143132829) {
   out_5017787030143132829[0] = state[6] + state[9];
   out_5017787030143132829[1] = state[7] + state[10];
   out_5017787030143132829[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6159159446455763767) {
   out_6159159446455763767[0] = 0;
   out_6159159446455763767[1] = 0;
   out_6159159446455763767[2] = 0;
   out_6159159446455763767[3] = 0;
   out_6159159446455763767[4] = 0;
   out_6159159446455763767[5] = 0;
   out_6159159446455763767[6] = 1;
   out_6159159446455763767[7] = 0;
   out_6159159446455763767[8] = 0;
   out_6159159446455763767[9] = 1;
   out_6159159446455763767[10] = 0;
   out_6159159446455763767[11] = 0;
   out_6159159446455763767[12] = 0;
   out_6159159446455763767[13] = 0;
   out_6159159446455763767[14] = 0;
   out_6159159446455763767[15] = 0;
   out_6159159446455763767[16] = 0;
   out_6159159446455763767[17] = 0;
   out_6159159446455763767[18] = 0;
   out_6159159446455763767[19] = 0;
   out_6159159446455763767[20] = 0;
   out_6159159446455763767[21] = 0;
   out_6159159446455763767[22] = 0;
   out_6159159446455763767[23] = 0;
   out_6159159446455763767[24] = 0;
   out_6159159446455763767[25] = 1;
   out_6159159446455763767[26] = 0;
   out_6159159446455763767[27] = 0;
   out_6159159446455763767[28] = 1;
   out_6159159446455763767[29] = 0;
   out_6159159446455763767[30] = 0;
   out_6159159446455763767[31] = 0;
   out_6159159446455763767[32] = 0;
   out_6159159446455763767[33] = 0;
   out_6159159446455763767[34] = 0;
   out_6159159446455763767[35] = 0;
   out_6159159446455763767[36] = 0;
   out_6159159446455763767[37] = 0;
   out_6159159446455763767[38] = 0;
   out_6159159446455763767[39] = 0;
   out_6159159446455763767[40] = 0;
   out_6159159446455763767[41] = 0;
   out_6159159446455763767[42] = 0;
   out_6159159446455763767[43] = 0;
   out_6159159446455763767[44] = 1;
   out_6159159446455763767[45] = 0;
   out_6159159446455763767[46] = 0;
   out_6159159446455763767[47] = 1;
   out_6159159446455763767[48] = 0;
   out_6159159446455763767[49] = 0;
   out_6159159446455763767[50] = 0;
   out_6159159446455763767[51] = 0;
   out_6159159446455763767[52] = 0;
   out_6159159446455763767[53] = 0;
}
void h_10(double *state, double *unused, double *out_3262846990399651616) {
   out_3262846990399651616[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3262846990399651616[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3262846990399651616[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7436549945486840862) {
   out_7436549945486840862[0] = 0;
   out_7436549945486840862[1] = 9.8100000000000005*cos(state[1]);
   out_7436549945486840862[2] = 0;
   out_7436549945486840862[3] = 0;
   out_7436549945486840862[4] = -state[8];
   out_7436549945486840862[5] = state[7];
   out_7436549945486840862[6] = 0;
   out_7436549945486840862[7] = state[5];
   out_7436549945486840862[8] = -state[4];
   out_7436549945486840862[9] = 0;
   out_7436549945486840862[10] = 0;
   out_7436549945486840862[11] = 0;
   out_7436549945486840862[12] = 1;
   out_7436549945486840862[13] = 0;
   out_7436549945486840862[14] = 0;
   out_7436549945486840862[15] = 1;
   out_7436549945486840862[16] = 0;
   out_7436549945486840862[17] = 0;
   out_7436549945486840862[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7436549945486840862[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7436549945486840862[20] = 0;
   out_7436549945486840862[21] = state[8];
   out_7436549945486840862[22] = 0;
   out_7436549945486840862[23] = -state[6];
   out_7436549945486840862[24] = -state[5];
   out_7436549945486840862[25] = 0;
   out_7436549945486840862[26] = state[3];
   out_7436549945486840862[27] = 0;
   out_7436549945486840862[28] = 0;
   out_7436549945486840862[29] = 0;
   out_7436549945486840862[30] = 0;
   out_7436549945486840862[31] = 1;
   out_7436549945486840862[32] = 0;
   out_7436549945486840862[33] = 0;
   out_7436549945486840862[34] = 1;
   out_7436549945486840862[35] = 0;
   out_7436549945486840862[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7436549945486840862[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7436549945486840862[38] = 0;
   out_7436549945486840862[39] = -state[7];
   out_7436549945486840862[40] = state[6];
   out_7436549945486840862[41] = 0;
   out_7436549945486840862[42] = state[4];
   out_7436549945486840862[43] = -state[3];
   out_7436549945486840862[44] = 0;
   out_7436549945486840862[45] = 0;
   out_7436549945486840862[46] = 0;
   out_7436549945486840862[47] = 0;
   out_7436549945486840862[48] = 0;
   out_7436549945486840862[49] = 0;
   out_7436549945486840862[50] = 1;
   out_7436549945486840862[51] = 0;
   out_7436549945486840862[52] = 0;
   out_7436549945486840862[53] = 1;
}
void h_13(double *state, double *unused, double *out_8458063766517386356) {
   out_8458063766517386356[0] = state[3];
   out_8458063766517386356[1] = state[4];
   out_8458063766517386356[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2946885621123430966) {
   out_2946885621123430966[0] = 0;
   out_2946885621123430966[1] = 0;
   out_2946885621123430966[2] = 0;
   out_2946885621123430966[3] = 1;
   out_2946885621123430966[4] = 0;
   out_2946885621123430966[5] = 0;
   out_2946885621123430966[6] = 0;
   out_2946885621123430966[7] = 0;
   out_2946885621123430966[8] = 0;
   out_2946885621123430966[9] = 0;
   out_2946885621123430966[10] = 0;
   out_2946885621123430966[11] = 0;
   out_2946885621123430966[12] = 0;
   out_2946885621123430966[13] = 0;
   out_2946885621123430966[14] = 0;
   out_2946885621123430966[15] = 0;
   out_2946885621123430966[16] = 0;
   out_2946885621123430966[17] = 0;
   out_2946885621123430966[18] = 0;
   out_2946885621123430966[19] = 0;
   out_2946885621123430966[20] = 0;
   out_2946885621123430966[21] = 0;
   out_2946885621123430966[22] = 1;
   out_2946885621123430966[23] = 0;
   out_2946885621123430966[24] = 0;
   out_2946885621123430966[25] = 0;
   out_2946885621123430966[26] = 0;
   out_2946885621123430966[27] = 0;
   out_2946885621123430966[28] = 0;
   out_2946885621123430966[29] = 0;
   out_2946885621123430966[30] = 0;
   out_2946885621123430966[31] = 0;
   out_2946885621123430966[32] = 0;
   out_2946885621123430966[33] = 0;
   out_2946885621123430966[34] = 0;
   out_2946885621123430966[35] = 0;
   out_2946885621123430966[36] = 0;
   out_2946885621123430966[37] = 0;
   out_2946885621123430966[38] = 0;
   out_2946885621123430966[39] = 0;
   out_2946885621123430966[40] = 0;
   out_2946885621123430966[41] = 1;
   out_2946885621123430966[42] = 0;
   out_2946885621123430966[43] = 0;
   out_2946885621123430966[44] = 0;
   out_2946885621123430966[45] = 0;
   out_2946885621123430966[46] = 0;
   out_2946885621123430966[47] = 0;
   out_2946885621123430966[48] = 0;
   out_2946885621123430966[49] = 0;
   out_2946885621123430966[50] = 0;
   out_2946885621123430966[51] = 0;
   out_2946885621123430966[52] = 0;
   out_2946885621123430966[53] = 0;
}
void h_14(double *state, double *unused, double *out_1921628300665528083) {
   out_1921628300665528083[0] = state[6];
   out_1921628300665528083[1] = state[7];
   out_1921628300665528083[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2195918590116279238) {
   out_2195918590116279238[0] = 0;
   out_2195918590116279238[1] = 0;
   out_2195918590116279238[2] = 0;
   out_2195918590116279238[3] = 0;
   out_2195918590116279238[4] = 0;
   out_2195918590116279238[5] = 0;
   out_2195918590116279238[6] = 1;
   out_2195918590116279238[7] = 0;
   out_2195918590116279238[8] = 0;
   out_2195918590116279238[9] = 0;
   out_2195918590116279238[10] = 0;
   out_2195918590116279238[11] = 0;
   out_2195918590116279238[12] = 0;
   out_2195918590116279238[13] = 0;
   out_2195918590116279238[14] = 0;
   out_2195918590116279238[15] = 0;
   out_2195918590116279238[16] = 0;
   out_2195918590116279238[17] = 0;
   out_2195918590116279238[18] = 0;
   out_2195918590116279238[19] = 0;
   out_2195918590116279238[20] = 0;
   out_2195918590116279238[21] = 0;
   out_2195918590116279238[22] = 0;
   out_2195918590116279238[23] = 0;
   out_2195918590116279238[24] = 0;
   out_2195918590116279238[25] = 1;
   out_2195918590116279238[26] = 0;
   out_2195918590116279238[27] = 0;
   out_2195918590116279238[28] = 0;
   out_2195918590116279238[29] = 0;
   out_2195918590116279238[30] = 0;
   out_2195918590116279238[31] = 0;
   out_2195918590116279238[32] = 0;
   out_2195918590116279238[33] = 0;
   out_2195918590116279238[34] = 0;
   out_2195918590116279238[35] = 0;
   out_2195918590116279238[36] = 0;
   out_2195918590116279238[37] = 0;
   out_2195918590116279238[38] = 0;
   out_2195918590116279238[39] = 0;
   out_2195918590116279238[40] = 0;
   out_2195918590116279238[41] = 0;
   out_2195918590116279238[42] = 0;
   out_2195918590116279238[43] = 0;
   out_2195918590116279238[44] = 1;
   out_2195918590116279238[45] = 0;
   out_2195918590116279238[46] = 0;
   out_2195918590116279238[47] = 0;
   out_2195918590116279238[48] = 0;
   out_2195918590116279238[49] = 0;
   out_2195918590116279238[50] = 0;
   out_2195918590116279238[51] = 0;
   out_2195918590116279238[52] = 0;
   out_2195918590116279238[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6308403071375908873) {
  err_fun(nom_x, delta_x, out_6308403071375908873);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5050968420956665665) {
  inv_err_fun(nom_x, true_x, out_5050968420956665665);
}
void pose_H_mod_fun(double *state, double *out_7135066242214707114) {
  H_mod_fun(state, out_7135066242214707114);
}
void pose_f_fun(double *state, double dt, double *out_1066594021391050582) {
  f_fun(state,  dt, out_1066594021391050582);
}
void pose_F_fun(double *state, double dt, double *out_4090974996683569946) {
  F_fun(state,  dt, out_4090974996683569946);
}
void pose_h_4(double *state, double *unused, double *out_5017787030143132829) {
  h_4(state, unused, out_5017787030143132829);
}
void pose_H_4(double *state, double *unused, double *out_6159159446455763767) {
  H_4(state, unused, out_6159159446455763767);
}
void pose_h_10(double *state, double *unused, double *out_3262846990399651616) {
  h_10(state, unused, out_3262846990399651616);
}
void pose_H_10(double *state, double *unused, double *out_7436549945486840862) {
  H_10(state, unused, out_7436549945486840862);
}
void pose_h_13(double *state, double *unused, double *out_8458063766517386356) {
  h_13(state, unused, out_8458063766517386356);
}
void pose_H_13(double *state, double *unused, double *out_2946885621123430966) {
  H_13(state, unused, out_2946885621123430966);
}
void pose_h_14(double *state, double *unused, double *out_1921628300665528083) {
  h_14(state, unused, out_1921628300665528083);
}
void pose_H_14(double *state, double *unused, double *out_2195918590116279238) {
  H_14(state, unused, out_2195918590116279238);
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
