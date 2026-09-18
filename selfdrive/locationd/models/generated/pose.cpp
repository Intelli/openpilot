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
void err_fun(double *nom_x, double *delta_x, double *out_3942668725891730719) {
   out_3942668725891730719[0] = delta_x[0] + nom_x[0];
   out_3942668725891730719[1] = delta_x[1] + nom_x[1];
   out_3942668725891730719[2] = delta_x[2] + nom_x[2];
   out_3942668725891730719[3] = delta_x[3] + nom_x[3];
   out_3942668725891730719[4] = delta_x[4] + nom_x[4];
   out_3942668725891730719[5] = delta_x[5] + nom_x[5];
   out_3942668725891730719[6] = delta_x[6] + nom_x[6];
   out_3942668725891730719[7] = delta_x[7] + nom_x[7];
   out_3942668725891730719[8] = delta_x[8] + nom_x[8];
   out_3942668725891730719[9] = delta_x[9] + nom_x[9];
   out_3942668725891730719[10] = delta_x[10] + nom_x[10];
   out_3942668725891730719[11] = delta_x[11] + nom_x[11];
   out_3942668725891730719[12] = delta_x[12] + nom_x[12];
   out_3942668725891730719[13] = delta_x[13] + nom_x[13];
   out_3942668725891730719[14] = delta_x[14] + nom_x[14];
   out_3942668725891730719[15] = delta_x[15] + nom_x[15];
   out_3942668725891730719[16] = delta_x[16] + nom_x[16];
   out_3942668725891730719[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1991070876907521357) {
   out_1991070876907521357[0] = -nom_x[0] + true_x[0];
   out_1991070876907521357[1] = -nom_x[1] + true_x[1];
   out_1991070876907521357[2] = -nom_x[2] + true_x[2];
   out_1991070876907521357[3] = -nom_x[3] + true_x[3];
   out_1991070876907521357[4] = -nom_x[4] + true_x[4];
   out_1991070876907521357[5] = -nom_x[5] + true_x[5];
   out_1991070876907521357[6] = -nom_x[6] + true_x[6];
   out_1991070876907521357[7] = -nom_x[7] + true_x[7];
   out_1991070876907521357[8] = -nom_x[8] + true_x[8];
   out_1991070876907521357[9] = -nom_x[9] + true_x[9];
   out_1991070876907521357[10] = -nom_x[10] + true_x[10];
   out_1991070876907521357[11] = -nom_x[11] + true_x[11];
   out_1991070876907521357[12] = -nom_x[12] + true_x[12];
   out_1991070876907521357[13] = -nom_x[13] + true_x[13];
   out_1991070876907521357[14] = -nom_x[14] + true_x[14];
   out_1991070876907521357[15] = -nom_x[15] + true_x[15];
   out_1991070876907521357[16] = -nom_x[16] + true_x[16];
   out_1991070876907521357[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6816734002753500757) {
   out_6816734002753500757[0] = 1.0;
   out_6816734002753500757[1] = 0.0;
   out_6816734002753500757[2] = 0.0;
   out_6816734002753500757[3] = 0.0;
   out_6816734002753500757[4] = 0.0;
   out_6816734002753500757[5] = 0.0;
   out_6816734002753500757[6] = 0.0;
   out_6816734002753500757[7] = 0.0;
   out_6816734002753500757[8] = 0.0;
   out_6816734002753500757[9] = 0.0;
   out_6816734002753500757[10] = 0.0;
   out_6816734002753500757[11] = 0.0;
   out_6816734002753500757[12] = 0.0;
   out_6816734002753500757[13] = 0.0;
   out_6816734002753500757[14] = 0.0;
   out_6816734002753500757[15] = 0.0;
   out_6816734002753500757[16] = 0.0;
   out_6816734002753500757[17] = 0.0;
   out_6816734002753500757[18] = 0.0;
   out_6816734002753500757[19] = 1.0;
   out_6816734002753500757[20] = 0.0;
   out_6816734002753500757[21] = 0.0;
   out_6816734002753500757[22] = 0.0;
   out_6816734002753500757[23] = 0.0;
   out_6816734002753500757[24] = 0.0;
   out_6816734002753500757[25] = 0.0;
   out_6816734002753500757[26] = 0.0;
   out_6816734002753500757[27] = 0.0;
   out_6816734002753500757[28] = 0.0;
   out_6816734002753500757[29] = 0.0;
   out_6816734002753500757[30] = 0.0;
   out_6816734002753500757[31] = 0.0;
   out_6816734002753500757[32] = 0.0;
   out_6816734002753500757[33] = 0.0;
   out_6816734002753500757[34] = 0.0;
   out_6816734002753500757[35] = 0.0;
   out_6816734002753500757[36] = 0.0;
   out_6816734002753500757[37] = 0.0;
   out_6816734002753500757[38] = 1.0;
   out_6816734002753500757[39] = 0.0;
   out_6816734002753500757[40] = 0.0;
   out_6816734002753500757[41] = 0.0;
   out_6816734002753500757[42] = 0.0;
   out_6816734002753500757[43] = 0.0;
   out_6816734002753500757[44] = 0.0;
   out_6816734002753500757[45] = 0.0;
   out_6816734002753500757[46] = 0.0;
   out_6816734002753500757[47] = 0.0;
   out_6816734002753500757[48] = 0.0;
   out_6816734002753500757[49] = 0.0;
   out_6816734002753500757[50] = 0.0;
   out_6816734002753500757[51] = 0.0;
   out_6816734002753500757[52] = 0.0;
   out_6816734002753500757[53] = 0.0;
   out_6816734002753500757[54] = 0.0;
   out_6816734002753500757[55] = 0.0;
   out_6816734002753500757[56] = 0.0;
   out_6816734002753500757[57] = 1.0;
   out_6816734002753500757[58] = 0.0;
   out_6816734002753500757[59] = 0.0;
   out_6816734002753500757[60] = 0.0;
   out_6816734002753500757[61] = 0.0;
   out_6816734002753500757[62] = 0.0;
   out_6816734002753500757[63] = 0.0;
   out_6816734002753500757[64] = 0.0;
   out_6816734002753500757[65] = 0.0;
   out_6816734002753500757[66] = 0.0;
   out_6816734002753500757[67] = 0.0;
   out_6816734002753500757[68] = 0.0;
   out_6816734002753500757[69] = 0.0;
   out_6816734002753500757[70] = 0.0;
   out_6816734002753500757[71] = 0.0;
   out_6816734002753500757[72] = 0.0;
   out_6816734002753500757[73] = 0.0;
   out_6816734002753500757[74] = 0.0;
   out_6816734002753500757[75] = 0.0;
   out_6816734002753500757[76] = 1.0;
   out_6816734002753500757[77] = 0.0;
   out_6816734002753500757[78] = 0.0;
   out_6816734002753500757[79] = 0.0;
   out_6816734002753500757[80] = 0.0;
   out_6816734002753500757[81] = 0.0;
   out_6816734002753500757[82] = 0.0;
   out_6816734002753500757[83] = 0.0;
   out_6816734002753500757[84] = 0.0;
   out_6816734002753500757[85] = 0.0;
   out_6816734002753500757[86] = 0.0;
   out_6816734002753500757[87] = 0.0;
   out_6816734002753500757[88] = 0.0;
   out_6816734002753500757[89] = 0.0;
   out_6816734002753500757[90] = 0.0;
   out_6816734002753500757[91] = 0.0;
   out_6816734002753500757[92] = 0.0;
   out_6816734002753500757[93] = 0.0;
   out_6816734002753500757[94] = 0.0;
   out_6816734002753500757[95] = 1.0;
   out_6816734002753500757[96] = 0.0;
   out_6816734002753500757[97] = 0.0;
   out_6816734002753500757[98] = 0.0;
   out_6816734002753500757[99] = 0.0;
   out_6816734002753500757[100] = 0.0;
   out_6816734002753500757[101] = 0.0;
   out_6816734002753500757[102] = 0.0;
   out_6816734002753500757[103] = 0.0;
   out_6816734002753500757[104] = 0.0;
   out_6816734002753500757[105] = 0.0;
   out_6816734002753500757[106] = 0.0;
   out_6816734002753500757[107] = 0.0;
   out_6816734002753500757[108] = 0.0;
   out_6816734002753500757[109] = 0.0;
   out_6816734002753500757[110] = 0.0;
   out_6816734002753500757[111] = 0.0;
   out_6816734002753500757[112] = 0.0;
   out_6816734002753500757[113] = 0.0;
   out_6816734002753500757[114] = 1.0;
   out_6816734002753500757[115] = 0.0;
   out_6816734002753500757[116] = 0.0;
   out_6816734002753500757[117] = 0.0;
   out_6816734002753500757[118] = 0.0;
   out_6816734002753500757[119] = 0.0;
   out_6816734002753500757[120] = 0.0;
   out_6816734002753500757[121] = 0.0;
   out_6816734002753500757[122] = 0.0;
   out_6816734002753500757[123] = 0.0;
   out_6816734002753500757[124] = 0.0;
   out_6816734002753500757[125] = 0.0;
   out_6816734002753500757[126] = 0.0;
   out_6816734002753500757[127] = 0.0;
   out_6816734002753500757[128] = 0.0;
   out_6816734002753500757[129] = 0.0;
   out_6816734002753500757[130] = 0.0;
   out_6816734002753500757[131] = 0.0;
   out_6816734002753500757[132] = 0.0;
   out_6816734002753500757[133] = 1.0;
   out_6816734002753500757[134] = 0.0;
   out_6816734002753500757[135] = 0.0;
   out_6816734002753500757[136] = 0.0;
   out_6816734002753500757[137] = 0.0;
   out_6816734002753500757[138] = 0.0;
   out_6816734002753500757[139] = 0.0;
   out_6816734002753500757[140] = 0.0;
   out_6816734002753500757[141] = 0.0;
   out_6816734002753500757[142] = 0.0;
   out_6816734002753500757[143] = 0.0;
   out_6816734002753500757[144] = 0.0;
   out_6816734002753500757[145] = 0.0;
   out_6816734002753500757[146] = 0.0;
   out_6816734002753500757[147] = 0.0;
   out_6816734002753500757[148] = 0.0;
   out_6816734002753500757[149] = 0.0;
   out_6816734002753500757[150] = 0.0;
   out_6816734002753500757[151] = 0.0;
   out_6816734002753500757[152] = 1.0;
   out_6816734002753500757[153] = 0.0;
   out_6816734002753500757[154] = 0.0;
   out_6816734002753500757[155] = 0.0;
   out_6816734002753500757[156] = 0.0;
   out_6816734002753500757[157] = 0.0;
   out_6816734002753500757[158] = 0.0;
   out_6816734002753500757[159] = 0.0;
   out_6816734002753500757[160] = 0.0;
   out_6816734002753500757[161] = 0.0;
   out_6816734002753500757[162] = 0.0;
   out_6816734002753500757[163] = 0.0;
   out_6816734002753500757[164] = 0.0;
   out_6816734002753500757[165] = 0.0;
   out_6816734002753500757[166] = 0.0;
   out_6816734002753500757[167] = 0.0;
   out_6816734002753500757[168] = 0.0;
   out_6816734002753500757[169] = 0.0;
   out_6816734002753500757[170] = 0.0;
   out_6816734002753500757[171] = 1.0;
   out_6816734002753500757[172] = 0.0;
   out_6816734002753500757[173] = 0.0;
   out_6816734002753500757[174] = 0.0;
   out_6816734002753500757[175] = 0.0;
   out_6816734002753500757[176] = 0.0;
   out_6816734002753500757[177] = 0.0;
   out_6816734002753500757[178] = 0.0;
   out_6816734002753500757[179] = 0.0;
   out_6816734002753500757[180] = 0.0;
   out_6816734002753500757[181] = 0.0;
   out_6816734002753500757[182] = 0.0;
   out_6816734002753500757[183] = 0.0;
   out_6816734002753500757[184] = 0.0;
   out_6816734002753500757[185] = 0.0;
   out_6816734002753500757[186] = 0.0;
   out_6816734002753500757[187] = 0.0;
   out_6816734002753500757[188] = 0.0;
   out_6816734002753500757[189] = 0.0;
   out_6816734002753500757[190] = 1.0;
   out_6816734002753500757[191] = 0.0;
   out_6816734002753500757[192] = 0.0;
   out_6816734002753500757[193] = 0.0;
   out_6816734002753500757[194] = 0.0;
   out_6816734002753500757[195] = 0.0;
   out_6816734002753500757[196] = 0.0;
   out_6816734002753500757[197] = 0.0;
   out_6816734002753500757[198] = 0.0;
   out_6816734002753500757[199] = 0.0;
   out_6816734002753500757[200] = 0.0;
   out_6816734002753500757[201] = 0.0;
   out_6816734002753500757[202] = 0.0;
   out_6816734002753500757[203] = 0.0;
   out_6816734002753500757[204] = 0.0;
   out_6816734002753500757[205] = 0.0;
   out_6816734002753500757[206] = 0.0;
   out_6816734002753500757[207] = 0.0;
   out_6816734002753500757[208] = 0.0;
   out_6816734002753500757[209] = 1.0;
   out_6816734002753500757[210] = 0.0;
   out_6816734002753500757[211] = 0.0;
   out_6816734002753500757[212] = 0.0;
   out_6816734002753500757[213] = 0.0;
   out_6816734002753500757[214] = 0.0;
   out_6816734002753500757[215] = 0.0;
   out_6816734002753500757[216] = 0.0;
   out_6816734002753500757[217] = 0.0;
   out_6816734002753500757[218] = 0.0;
   out_6816734002753500757[219] = 0.0;
   out_6816734002753500757[220] = 0.0;
   out_6816734002753500757[221] = 0.0;
   out_6816734002753500757[222] = 0.0;
   out_6816734002753500757[223] = 0.0;
   out_6816734002753500757[224] = 0.0;
   out_6816734002753500757[225] = 0.0;
   out_6816734002753500757[226] = 0.0;
   out_6816734002753500757[227] = 0.0;
   out_6816734002753500757[228] = 1.0;
   out_6816734002753500757[229] = 0.0;
   out_6816734002753500757[230] = 0.0;
   out_6816734002753500757[231] = 0.0;
   out_6816734002753500757[232] = 0.0;
   out_6816734002753500757[233] = 0.0;
   out_6816734002753500757[234] = 0.0;
   out_6816734002753500757[235] = 0.0;
   out_6816734002753500757[236] = 0.0;
   out_6816734002753500757[237] = 0.0;
   out_6816734002753500757[238] = 0.0;
   out_6816734002753500757[239] = 0.0;
   out_6816734002753500757[240] = 0.0;
   out_6816734002753500757[241] = 0.0;
   out_6816734002753500757[242] = 0.0;
   out_6816734002753500757[243] = 0.0;
   out_6816734002753500757[244] = 0.0;
   out_6816734002753500757[245] = 0.0;
   out_6816734002753500757[246] = 0.0;
   out_6816734002753500757[247] = 1.0;
   out_6816734002753500757[248] = 0.0;
   out_6816734002753500757[249] = 0.0;
   out_6816734002753500757[250] = 0.0;
   out_6816734002753500757[251] = 0.0;
   out_6816734002753500757[252] = 0.0;
   out_6816734002753500757[253] = 0.0;
   out_6816734002753500757[254] = 0.0;
   out_6816734002753500757[255] = 0.0;
   out_6816734002753500757[256] = 0.0;
   out_6816734002753500757[257] = 0.0;
   out_6816734002753500757[258] = 0.0;
   out_6816734002753500757[259] = 0.0;
   out_6816734002753500757[260] = 0.0;
   out_6816734002753500757[261] = 0.0;
   out_6816734002753500757[262] = 0.0;
   out_6816734002753500757[263] = 0.0;
   out_6816734002753500757[264] = 0.0;
   out_6816734002753500757[265] = 0.0;
   out_6816734002753500757[266] = 1.0;
   out_6816734002753500757[267] = 0.0;
   out_6816734002753500757[268] = 0.0;
   out_6816734002753500757[269] = 0.0;
   out_6816734002753500757[270] = 0.0;
   out_6816734002753500757[271] = 0.0;
   out_6816734002753500757[272] = 0.0;
   out_6816734002753500757[273] = 0.0;
   out_6816734002753500757[274] = 0.0;
   out_6816734002753500757[275] = 0.0;
   out_6816734002753500757[276] = 0.0;
   out_6816734002753500757[277] = 0.0;
   out_6816734002753500757[278] = 0.0;
   out_6816734002753500757[279] = 0.0;
   out_6816734002753500757[280] = 0.0;
   out_6816734002753500757[281] = 0.0;
   out_6816734002753500757[282] = 0.0;
   out_6816734002753500757[283] = 0.0;
   out_6816734002753500757[284] = 0.0;
   out_6816734002753500757[285] = 1.0;
   out_6816734002753500757[286] = 0.0;
   out_6816734002753500757[287] = 0.0;
   out_6816734002753500757[288] = 0.0;
   out_6816734002753500757[289] = 0.0;
   out_6816734002753500757[290] = 0.0;
   out_6816734002753500757[291] = 0.0;
   out_6816734002753500757[292] = 0.0;
   out_6816734002753500757[293] = 0.0;
   out_6816734002753500757[294] = 0.0;
   out_6816734002753500757[295] = 0.0;
   out_6816734002753500757[296] = 0.0;
   out_6816734002753500757[297] = 0.0;
   out_6816734002753500757[298] = 0.0;
   out_6816734002753500757[299] = 0.0;
   out_6816734002753500757[300] = 0.0;
   out_6816734002753500757[301] = 0.0;
   out_6816734002753500757[302] = 0.0;
   out_6816734002753500757[303] = 0.0;
   out_6816734002753500757[304] = 1.0;
   out_6816734002753500757[305] = 0.0;
   out_6816734002753500757[306] = 0.0;
   out_6816734002753500757[307] = 0.0;
   out_6816734002753500757[308] = 0.0;
   out_6816734002753500757[309] = 0.0;
   out_6816734002753500757[310] = 0.0;
   out_6816734002753500757[311] = 0.0;
   out_6816734002753500757[312] = 0.0;
   out_6816734002753500757[313] = 0.0;
   out_6816734002753500757[314] = 0.0;
   out_6816734002753500757[315] = 0.0;
   out_6816734002753500757[316] = 0.0;
   out_6816734002753500757[317] = 0.0;
   out_6816734002753500757[318] = 0.0;
   out_6816734002753500757[319] = 0.0;
   out_6816734002753500757[320] = 0.0;
   out_6816734002753500757[321] = 0.0;
   out_6816734002753500757[322] = 0.0;
   out_6816734002753500757[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8854473194143657966) {
   out_8854473194143657966[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8854473194143657966[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8854473194143657966[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8854473194143657966[3] = dt*state[12] + state[3];
   out_8854473194143657966[4] = dt*state[13] + state[4];
   out_8854473194143657966[5] = dt*state[14] + state[5];
   out_8854473194143657966[6] = state[6];
   out_8854473194143657966[7] = state[7];
   out_8854473194143657966[8] = state[8];
   out_8854473194143657966[9] = state[9];
   out_8854473194143657966[10] = state[10];
   out_8854473194143657966[11] = state[11];
   out_8854473194143657966[12] = state[12];
   out_8854473194143657966[13] = state[13];
   out_8854473194143657966[14] = state[14];
   out_8854473194143657966[15] = state[15];
   out_8854473194143657966[16] = state[16];
   out_8854473194143657966[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4169004597503113381) {
   out_4169004597503113381[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4169004597503113381[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4169004597503113381[2] = 0;
   out_4169004597503113381[3] = 0;
   out_4169004597503113381[4] = 0;
   out_4169004597503113381[5] = 0;
   out_4169004597503113381[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4169004597503113381[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4169004597503113381[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4169004597503113381[9] = 0;
   out_4169004597503113381[10] = 0;
   out_4169004597503113381[11] = 0;
   out_4169004597503113381[12] = 0;
   out_4169004597503113381[13] = 0;
   out_4169004597503113381[14] = 0;
   out_4169004597503113381[15] = 0;
   out_4169004597503113381[16] = 0;
   out_4169004597503113381[17] = 0;
   out_4169004597503113381[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4169004597503113381[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4169004597503113381[20] = 0;
   out_4169004597503113381[21] = 0;
   out_4169004597503113381[22] = 0;
   out_4169004597503113381[23] = 0;
   out_4169004597503113381[24] = 0;
   out_4169004597503113381[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4169004597503113381[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4169004597503113381[27] = 0;
   out_4169004597503113381[28] = 0;
   out_4169004597503113381[29] = 0;
   out_4169004597503113381[30] = 0;
   out_4169004597503113381[31] = 0;
   out_4169004597503113381[32] = 0;
   out_4169004597503113381[33] = 0;
   out_4169004597503113381[34] = 0;
   out_4169004597503113381[35] = 0;
   out_4169004597503113381[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4169004597503113381[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4169004597503113381[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4169004597503113381[39] = 0;
   out_4169004597503113381[40] = 0;
   out_4169004597503113381[41] = 0;
   out_4169004597503113381[42] = 0;
   out_4169004597503113381[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4169004597503113381[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4169004597503113381[45] = 0;
   out_4169004597503113381[46] = 0;
   out_4169004597503113381[47] = 0;
   out_4169004597503113381[48] = 0;
   out_4169004597503113381[49] = 0;
   out_4169004597503113381[50] = 0;
   out_4169004597503113381[51] = 0;
   out_4169004597503113381[52] = 0;
   out_4169004597503113381[53] = 0;
   out_4169004597503113381[54] = 0;
   out_4169004597503113381[55] = 0;
   out_4169004597503113381[56] = 0;
   out_4169004597503113381[57] = 1;
   out_4169004597503113381[58] = 0;
   out_4169004597503113381[59] = 0;
   out_4169004597503113381[60] = 0;
   out_4169004597503113381[61] = 0;
   out_4169004597503113381[62] = 0;
   out_4169004597503113381[63] = 0;
   out_4169004597503113381[64] = 0;
   out_4169004597503113381[65] = 0;
   out_4169004597503113381[66] = dt;
   out_4169004597503113381[67] = 0;
   out_4169004597503113381[68] = 0;
   out_4169004597503113381[69] = 0;
   out_4169004597503113381[70] = 0;
   out_4169004597503113381[71] = 0;
   out_4169004597503113381[72] = 0;
   out_4169004597503113381[73] = 0;
   out_4169004597503113381[74] = 0;
   out_4169004597503113381[75] = 0;
   out_4169004597503113381[76] = 1;
   out_4169004597503113381[77] = 0;
   out_4169004597503113381[78] = 0;
   out_4169004597503113381[79] = 0;
   out_4169004597503113381[80] = 0;
   out_4169004597503113381[81] = 0;
   out_4169004597503113381[82] = 0;
   out_4169004597503113381[83] = 0;
   out_4169004597503113381[84] = 0;
   out_4169004597503113381[85] = dt;
   out_4169004597503113381[86] = 0;
   out_4169004597503113381[87] = 0;
   out_4169004597503113381[88] = 0;
   out_4169004597503113381[89] = 0;
   out_4169004597503113381[90] = 0;
   out_4169004597503113381[91] = 0;
   out_4169004597503113381[92] = 0;
   out_4169004597503113381[93] = 0;
   out_4169004597503113381[94] = 0;
   out_4169004597503113381[95] = 1;
   out_4169004597503113381[96] = 0;
   out_4169004597503113381[97] = 0;
   out_4169004597503113381[98] = 0;
   out_4169004597503113381[99] = 0;
   out_4169004597503113381[100] = 0;
   out_4169004597503113381[101] = 0;
   out_4169004597503113381[102] = 0;
   out_4169004597503113381[103] = 0;
   out_4169004597503113381[104] = dt;
   out_4169004597503113381[105] = 0;
   out_4169004597503113381[106] = 0;
   out_4169004597503113381[107] = 0;
   out_4169004597503113381[108] = 0;
   out_4169004597503113381[109] = 0;
   out_4169004597503113381[110] = 0;
   out_4169004597503113381[111] = 0;
   out_4169004597503113381[112] = 0;
   out_4169004597503113381[113] = 0;
   out_4169004597503113381[114] = 1;
   out_4169004597503113381[115] = 0;
   out_4169004597503113381[116] = 0;
   out_4169004597503113381[117] = 0;
   out_4169004597503113381[118] = 0;
   out_4169004597503113381[119] = 0;
   out_4169004597503113381[120] = 0;
   out_4169004597503113381[121] = 0;
   out_4169004597503113381[122] = 0;
   out_4169004597503113381[123] = 0;
   out_4169004597503113381[124] = 0;
   out_4169004597503113381[125] = 0;
   out_4169004597503113381[126] = 0;
   out_4169004597503113381[127] = 0;
   out_4169004597503113381[128] = 0;
   out_4169004597503113381[129] = 0;
   out_4169004597503113381[130] = 0;
   out_4169004597503113381[131] = 0;
   out_4169004597503113381[132] = 0;
   out_4169004597503113381[133] = 1;
   out_4169004597503113381[134] = 0;
   out_4169004597503113381[135] = 0;
   out_4169004597503113381[136] = 0;
   out_4169004597503113381[137] = 0;
   out_4169004597503113381[138] = 0;
   out_4169004597503113381[139] = 0;
   out_4169004597503113381[140] = 0;
   out_4169004597503113381[141] = 0;
   out_4169004597503113381[142] = 0;
   out_4169004597503113381[143] = 0;
   out_4169004597503113381[144] = 0;
   out_4169004597503113381[145] = 0;
   out_4169004597503113381[146] = 0;
   out_4169004597503113381[147] = 0;
   out_4169004597503113381[148] = 0;
   out_4169004597503113381[149] = 0;
   out_4169004597503113381[150] = 0;
   out_4169004597503113381[151] = 0;
   out_4169004597503113381[152] = 1;
   out_4169004597503113381[153] = 0;
   out_4169004597503113381[154] = 0;
   out_4169004597503113381[155] = 0;
   out_4169004597503113381[156] = 0;
   out_4169004597503113381[157] = 0;
   out_4169004597503113381[158] = 0;
   out_4169004597503113381[159] = 0;
   out_4169004597503113381[160] = 0;
   out_4169004597503113381[161] = 0;
   out_4169004597503113381[162] = 0;
   out_4169004597503113381[163] = 0;
   out_4169004597503113381[164] = 0;
   out_4169004597503113381[165] = 0;
   out_4169004597503113381[166] = 0;
   out_4169004597503113381[167] = 0;
   out_4169004597503113381[168] = 0;
   out_4169004597503113381[169] = 0;
   out_4169004597503113381[170] = 0;
   out_4169004597503113381[171] = 1;
   out_4169004597503113381[172] = 0;
   out_4169004597503113381[173] = 0;
   out_4169004597503113381[174] = 0;
   out_4169004597503113381[175] = 0;
   out_4169004597503113381[176] = 0;
   out_4169004597503113381[177] = 0;
   out_4169004597503113381[178] = 0;
   out_4169004597503113381[179] = 0;
   out_4169004597503113381[180] = 0;
   out_4169004597503113381[181] = 0;
   out_4169004597503113381[182] = 0;
   out_4169004597503113381[183] = 0;
   out_4169004597503113381[184] = 0;
   out_4169004597503113381[185] = 0;
   out_4169004597503113381[186] = 0;
   out_4169004597503113381[187] = 0;
   out_4169004597503113381[188] = 0;
   out_4169004597503113381[189] = 0;
   out_4169004597503113381[190] = 1;
   out_4169004597503113381[191] = 0;
   out_4169004597503113381[192] = 0;
   out_4169004597503113381[193] = 0;
   out_4169004597503113381[194] = 0;
   out_4169004597503113381[195] = 0;
   out_4169004597503113381[196] = 0;
   out_4169004597503113381[197] = 0;
   out_4169004597503113381[198] = 0;
   out_4169004597503113381[199] = 0;
   out_4169004597503113381[200] = 0;
   out_4169004597503113381[201] = 0;
   out_4169004597503113381[202] = 0;
   out_4169004597503113381[203] = 0;
   out_4169004597503113381[204] = 0;
   out_4169004597503113381[205] = 0;
   out_4169004597503113381[206] = 0;
   out_4169004597503113381[207] = 0;
   out_4169004597503113381[208] = 0;
   out_4169004597503113381[209] = 1;
   out_4169004597503113381[210] = 0;
   out_4169004597503113381[211] = 0;
   out_4169004597503113381[212] = 0;
   out_4169004597503113381[213] = 0;
   out_4169004597503113381[214] = 0;
   out_4169004597503113381[215] = 0;
   out_4169004597503113381[216] = 0;
   out_4169004597503113381[217] = 0;
   out_4169004597503113381[218] = 0;
   out_4169004597503113381[219] = 0;
   out_4169004597503113381[220] = 0;
   out_4169004597503113381[221] = 0;
   out_4169004597503113381[222] = 0;
   out_4169004597503113381[223] = 0;
   out_4169004597503113381[224] = 0;
   out_4169004597503113381[225] = 0;
   out_4169004597503113381[226] = 0;
   out_4169004597503113381[227] = 0;
   out_4169004597503113381[228] = 1;
   out_4169004597503113381[229] = 0;
   out_4169004597503113381[230] = 0;
   out_4169004597503113381[231] = 0;
   out_4169004597503113381[232] = 0;
   out_4169004597503113381[233] = 0;
   out_4169004597503113381[234] = 0;
   out_4169004597503113381[235] = 0;
   out_4169004597503113381[236] = 0;
   out_4169004597503113381[237] = 0;
   out_4169004597503113381[238] = 0;
   out_4169004597503113381[239] = 0;
   out_4169004597503113381[240] = 0;
   out_4169004597503113381[241] = 0;
   out_4169004597503113381[242] = 0;
   out_4169004597503113381[243] = 0;
   out_4169004597503113381[244] = 0;
   out_4169004597503113381[245] = 0;
   out_4169004597503113381[246] = 0;
   out_4169004597503113381[247] = 1;
   out_4169004597503113381[248] = 0;
   out_4169004597503113381[249] = 0;
   out_4169004597503113381[250] = 0;
   out_4169004597503113381[251] = 0;
   out_4169004597503113381[252] = 0;
   out_4169004597503113381[253] = 0;
   out_4169004597503113381[254] = 0;
   out_4169004597503113381[255] = 0;
   out_4169004597503113381[256] = 0;
   out_4169004597503113381[257] = 0;
   out_4169004597503113381[258] = 0;
   out_4169004597503113381[259] = 0;
   out_4169004597503113381[260] = 0;
   out_4169004597503113381[261] = 0;
   out_4169004597503113381[262] = 0;
   out_4169004597503113381[263] = 0;
   out_4169004597503113381[264] = 0;
   out_4169004597503113381[265] = 0;
   out_4169004597503113381[266] = 1;
   out_4169004597503113381[267] = 0;
   out_4169004597503113381[268] = 0;
   out_4169004597503113381[269] = 0;
   out_4169004597503113381[270] = 0;
   out_4169004597503113381[271] = 0;
   out_4169004597503113381[272] = 0;
   out_4169004597503113381[273] = 0;
   out_4169004597503113381[274] = 0;
   out_4169004597503113381[275] = 0;
   out_4169004597503113381[276] = 0;
   out_4169004597503113381[277] = 0;
   out_4169004597503113381[278] = 0;
   out_4169004597503113381[279] = 0;
   out_4169004597503113381[280] = 0;
   out_4169004597503113381[281] = 0;
   out_4169004597503113381[282] = 0;
   out_4169004597503113381[283] = 0;
   out_4169004597503113381[284] = 0;
   out_4169004597503113381[285] = 1;
   out_4169004597503113381[286] = 0;
   out_4169004597503113381[287] = 0;
   out_4169004597503113381[288] = 0;
   out_4169004597503113381[289] = 0;
   out_4169004597503113381[290] = 0;
   out_4169004597503113381[291] = 0;
   out_4169004597503113381[292] = 0;
   out_4169004597503113381[293] = 0;
   out_4169004597503113381[294] = 0;
   out_4169004597503113381[295] = 0;
   out_4169004597503113381[296] = 0;
   out_4169004597503113381[297] = 0;
   out_4169004597503113381[298] = 0;
   out_4169004597503113381[299] = 0;
   out_4169004597503113381[300] = 0;
   out_4169004597503113381[301] = 0;
   out_4169004597503113381[302] = 0;
   out_4169004597503113381[303] = 0;
   out_4169004597503113381[304] = 1;
   out_4169004597503113381[305] = 0;
   out_4169004597503113381[306] = 0;
   out_4169004597503113381[307] = 0;
   out_4169004597503113381[308] = 0;
   out_4169004597503113381[309] = 0;
   out_4169004597503113381[310] = 0;
   out_4169004597503113381[311] = 0;
   out_4169004597503113381[312] = 0;
   out_4169004597503113381[313] = 0;
   out_4169004597503113381[314] = 0;
   out_4169004597503113381[315] = 0;
   out_4169004597503113381[316] = 0;
   out_4169004597503113381[317] = 0;
   out_4169004597503113381[318] = 0;
   out_4169004597503113381[319] = 0;
   out_4169004597503113381[320] = 0;
   out_4169004597503113381[321] = 0;
   out_4169004597503113381[322] = 0;
   out_4169004597503113381[323] = 1;
}
void h_4(double *state, double *unused, double *out_8446778466240330255) {
   out_8446778466240330255[0] = state[6] + state[9];
   out_8446778466240330255[1] = state[7] + state[10];
   out_8446778466240330255[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3044926792909593185) {
   out_3044926792909593185[0] = 0;
   out_3044926792909593185[1] = 0;
   out_3044926792909593185[2] = 0;
   out_3044926792909593185[3] = 0;
   out_3044926792909593185[4] = 0;
   out_3044926792909593185[5] = 0;
   out_3044926792909593185[6] = 1;
   out_3044926792909593185[7] = 0;
   out_3044926792909593185[8] = 0;
   out_3044926792909593185[9] = 1;
   out_3044926792909593185[10] = 0;
   out_3044926792909593185[11] = 0;
   out_3044926792909593185[12] = 0;
   out_3044926792909593185[13] = 0;
   out_3044926792909593185[14] = 0;
   out_3044926792909593185[15] = 0;
   out_3044926792909593185[16] = 0;
   out_3044926792909593185[17] = 0;
   out_3044926792909593185[18] = 0;
   out_3044926792909593185[19] = 0;
   out_3044926792909593185[20] = 0;
   out_3044926792909593185[21] = 0;
   out_3044926792909593185[22] = 0;
   out_3044926792909593185[23] = 0;
   out_3044926792909593185[24] = 0;
   out_3044926792909593185[25] = 1;
   out_3044926792909593185[26] = 0;
   out_3044926792909593185[27] = 0;
   out_3044926792909593185[28] = 1;
   out_3044926792909593185[29] = 0;
   out_3044926792909593185[30] = 0;
   out_3044926792909593185[31] = 0;
   out_3044926792909593185[32] = 0;
   out_3044926792909593185[33] = 0;
   out_3044926792909593185[34] = 0;
   out_3044926792909593185[35] = 0;
   out_3044926792909593185[36] = 0;
   out_3044926792909593185[37] = 0;
   out_3044926792909593185[38] = 0;
   out_3044926792909593185[39] = 0;
   out_3044926792909593185[40] = 0;
   out_3044926792909593185[41] = 0;
   out_3044926792909593185[42] = 0;
   out_3044926792909593185[43] = 0;
   out_3044926792909593185[44] = 1;
   out_3044926792909593185[45] = 0;
   out_3044926792909593185[46] = 0;
   out_3044926792909593185[47] = 1;
   out_3044926792909593185[48] = 0;
   out_3044926792909593185[49] = 0;
   out_3044926792909593185[50] = 0;
   out_3044926792909593185[51] = 0;
   out_3044926792909593185[52] = 0;
   out_3044926792909593185[53] = 0;
}
void h_10(double *state, double *unused, double *out_7710800854864143014) {
   out_7710800854864143014[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7710800854864143014[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7710800854864143014[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4471861486161314633) {
   out_4471861486161314633[0] = 0;
   out_4471861486161314633[1] = 9.8100000000000005*cos(state[1]);
   out_4471861486161314633[2] = 0;
   out_4471861486161314633[3] = 0;
   out_4471861486161314633[4] = -state[8];
   out_4471861486161314633[5] = state[7];
   out_4471861486161314633[6] = 0;
   out_4471861486161314633[7] = state[5];
   out_4471861486161314633[8] = -state[4];
   out_4471861486161314633[9] = 0;
   out_4471861486161314633[10] = 0;
   out_4471861486161314633[11] = 0;
   out_4471861486161314633[12] = 1;
   out_4471861486161314633[13] = 0;
   out_4471861486161314633[14] = 0;
   out_4471861486161314633[15] = 1;
   out_4471861486161314633[16] = 0;
   out_4471861486161314633[17] = 0;
   out_4471861486161314633[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4471861486161314633[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4471861486161314633[20] = 0;
   out_4471861486161314633[21] = state[8];
   out_4471861486161314633[22] = 0;
   out_4471861486161314633[23] = -state[6];
   out_4471861486161314633[24] = -state[5];
   out_4471861486161314633[25] = 0;
   out_4471861486161314633[26] = state[3];
   out_4471861486161314633[27] = 0;
   out_4471861486161314633[28] = 0;
   out_4471861486161314633[29] = 0;
   out_4471861486161314633[30] = 0;
   out_4471861486161314633[31] = 1;
   out_4471861486161314633[32] = 0;
   out_4471861486161314633[33] = 0;
   out_4471861486161314633[34] = 1;
   out_4471861486161314633[35] = 0;
   out_4471861486161314633[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4471861486161314633[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4471861486161314633[38] = 0;
   out_4471861486161314633[39] = -state[7];
   out_4471861486161314633[40] = state[6];
   out_4471861486161314633[41] = 0;
   out_4471861486161314633[42] = state[4];
   out_4471861486161314633[43] = -state[3];
   out_4471861486161314633[44] = 0;
   out_4471861486161314633[45] = 0;
   out_4471861486161314633[46] = 0;
   out_4471861486161314633[47] = 0;
   out_4471861486161314633[48] = 0;
   out_4471861486161314633[49] = 0;
   out_4471861486161314633[50] = 1;
   out_4471861486161314633[51] = 0;
   out_4471861486161314633[52] = 0;
   out_4471861486161314633[53] = 1;
}
void h_13(double *state, double *unused, double *out_7052128610875229889) {
   out_7052128610875229889[0] = state[3];
   out_7052128610875229889[1] = state[4];
   out_7052128610875229889[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4565704415407107744) {
   out_4565704415407107744[0] = 0;
   out_4565704415407107744[1] = 0;
   out_4565704415407107744[2] = 0;
   out_4565704415407107744[3] = 1;
   out_4565704415407107744[4] = 0;
   out_4565704415407107744[5] = 0;
   out_4565704415407107744[6] = 0;
   out_4565704415407107744[7] = 0;
   out_4565704415407107744[8] = 0;
   out_4565704415407107744[9] = 0;
   out_4565704415407107744[10] = 0;
   out_4565704415407107744[11] = 0;
   out_4565704415407107744[12] = 0;
   out_4565704415407107744[13] = 0;
   out_4565704415407107744[14] = 0;
   out_4565704415407107744[15] = 0;
   out_4565704415407107744[16] = 0;
   out_4565704415407107744[17] = 0;
   out_4565704415407107744[18] = 0;
   out_4565704415407107744[19] = 0;
   out_4565704415407107744[20] = 0;
   out_4565704415407107744[21] = 0;
   out_4565704415407107744[22] = 1;
   out_4565704415407107744[23] = 0;
   out_4565704415407107744[24] = 0;
   out_4565704415407107744[25] = 0;
   out_4565704415407107744[26] = 0;
   out_4565704415407107744[27] = 0;
   out_4565704415407107744[28] = 0;
   out_4565704415407107744[29] = 0;
   out_4565704415407107744[30] = 0;
   out_4565704415407107744[31] = 0;
   out_4565704415407107744[32] = 0;
   out_4565704415407107744[33] = 0;
   out_4565704415407107744[34] = 0;
   out_4565704415407107744[35] = 0;
   out_4565704415407107744[36] = 0;
   out_4565704415407107744[37] = 0;
   out_4565704415407107744[38] = 0;
   out_4565704415407107744[39] = 0;
   out_4565704415407107744[40] = 0;
   out_4565704415407107744[41] = 1;
   out_4565704415407107744[42] = 0;
   out_4565704415407107744[43] = 0;
   out_4565704415407107744[44] = 0;
   out_4565704415407107744[45] = 0;
   out_4565704415407107744[46] = 0;
   out_4565704415407107744[47] = 0;
   out_4565704415407107744[48] = 0;
   out_4565704415407107744[49] = 0;
   out_4565704415407107744[50] = 0;
   out_4565704415407107744[51] = 0;
   out_4565704415407107744[52] = 0;
   out_4565704415407107744[53] = 0;
}
void h_14(double *state, double *unused, double *out_6863744574475710969) {
   out_6863744574475710969[0] = state[6];
   out_6863744574475710969[1] = state[7];
   out_6863744574475710969[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6127715225204965481) {
   out_6127715225204965481[0] = 0;
   out_6127715225204965481[1] = 0;
   out_6127715225204965481[2] = 0;
   out_6127715225204965481[3] = 0;
   out_6127715225204965481[4] = 0;
   out_6127715225204965481[5] = 0;
   out_6127715225204965481[6] = 1;
   out_6127715225204965481[7] = 0;
   out_6127715225204965481[8] = 0;
   out_6127715225204965481[9] = 0;
   out_6127715225204965481[10] = 0;
   out_6127715225204965481[11] = 0;
   out_6127715225204965481[12] = 0;
   out_6127715225204965481[13] = 0;
   out_6127715225204965481[14] = 0;
   out_6127715225204965481[15] = 0;
   out_6127715225204965481[16] = 0;
   out_6127715225204965481[17] = 0;
   out_6127715225204965481[18] = 0;
   out_6127715225204965481[19] = 0;
   out_6127715225204965481[20] = 0;
   out_6127715225204965481[21] = 0;
   out_6127715225204965481[22] = 0;
   out_6127715225204965481[23] = 0;
   out_6127715225204965481[24] = 0;
   out_6127715225204965481[25] = 1;
   out_6127715225204965481[26] = 0;
   out_6127715225204965481[27] = 0;
   out_6127715225204965481[28] = 0;
   out_6127715225204965481[29] = 0;
   out_6127715225204965481[30] = 0;
   out_6127715225204965481[31] = 0;
   out_6127715225204965481[32] = 0;
   out_6127715225204965481[33] = 0;
   out_6127715225204965481[34] = 0;
   out_6127715225204965481[35] = 0;
   out_6127715225204965481[36] = 0;
   out_6127715225204965481[37] = 0;
   out_6127715225204965481[38] = 0;
   out_6127715225204965481[39] = 0;
   out_6127715225204965481[40] = 0;
   out_6127715225204965481[41] = 0;
   out_6127715225204965481[42] = 0;
   out_6127715225204965481[43] = 0;
   out_6127715225204965481[44] = 1;
   out_6127715225204965481[45] = 0;
   out_6127715225204965481[46] = 0;
   out_6127715225204965481[47] = 0;
   out_6127715225204965481[48] = 0;
   out_6127715225204965481[49] = 0;
   out_6127715225204965481[50] = 0;
   out_6127715225204965481[51] = 0;
   out_6127715225204965481[52] = 0;
   out_6127715225204965481[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3942668725891730719) {
  err_fun(nom_x, delta_x, out_3942668725891730719);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1991070876907521357) {
  inv_err_fun(nom_x, true_x, out_1991070876907521357);
}
void pose_H_mod_fun(double *state, double *out_6816734002753500757) {
  H_mod_fun(state, out_6816734002753500757);
}
void pose_f_fun(double *state, double dt, double *out_8854473194143657966) {
  f_fun(state,  dt, out_8854473194143657966);
}
void pose_F_fun(double *state, double dt, double *out_4169004597503113381) {
  F_fun(state,  dt, out_4169004597503113381);
}
void pose_h_4(double *state, double *unused, double *out_8446778466240330255) {
  h_4(state, unused, out_8446778466240330255);
}
void pose_H_4(double *state, double *unused, double *out_3044926792909593185) {
  H_4(state, unused, out_3044926792909593185);
}
void pose_h_10(double *state, double *unused, double *out_7710800854864143014) {
  h_10(state, unused, out_7710800854864143014);
}
void pose_H_10(double *state, double *unused, double *out_4471861486161314633) {
  H_10(state, unused, out_4471861486161314633);
}
void pose_h_13(double *state, double *unused, double *out_7052128610875229889) {
  h_13(state, unused, out_7052128610875229889);
}
void pose_H_13(double *state, double *unused, double *out_4565704415407107744) {
  H_13(state, unused, out_4565704415407107744);
}
void pose_h_14(double *state, double *unused, double *out_6863744574475710969) {
  h_14(state, unused, out_6863744574475710969);
}
void pose_H_14(double *state, double *unused, double *out_6127715225204965481) {
  H_14(state, unused, out_6127715225204965481);
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
