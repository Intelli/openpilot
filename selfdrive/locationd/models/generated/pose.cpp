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
void err_fun(double *nom_x, double *delta_x, double *out_3324107228628984672) {
   out_3324107228628984672[0] = delta_x[0] + nom_x[0];
   out_3324107228628984672[1] = delta_x[1] + nom_x[1];
   out_3324107228628984672[2] = delta_x[2] + nom_x[2];
   out_3324107228628984672[3] = delta_x[3] + nom_x[3];
   out_3324107228628984672[4] = delta_x[4] + nom_x[4];
   out_3324107228628984672[5] = delta_x[5] + nom_x[5];
   out_3324107228628984672[6] = delta_x[6] + nom_x[6];
   out_3324107228628984672[7] = delta_x[7] + nom_x[7];
   out_3324107228628984672[8] = delta_x[8] + nom_x[8];
   out_3324107228628984672[9] = delta_x[9] + nom_x[9];
   out_3324107228628984672[10] = delta_x[10] + nom_x[10];
   out_3324107228628984672[11] = delta_x[11] + nom_x[11];
   out_3324107228628984672[12] = delta_x[12] + nom_x[12];
   out_3324107228628984672[13] = delta_x[13] + nom_x[13];
   out_3324107228628984672[14] = delta_x[14] + nom_x[14];
   out_3324107228628984672[15] = delta_x[15] + nom_x[15];
   out_3324107228628984672[16] = delta_x[16] + nom_x[16];
   out_3324107228628984672[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4562048945435600381) {
   out_4562048945435600381[0] = -nom_x[0] + true_x[0];
   out_4562048945435600381[1] = -nom_x[1] + true_x[1];
   out_4562048945435600381[2] = -nom_x[2] + true_x[2];
   out_4562048945435600381[3] = -nom_x[3] + true_x[3];
   out_4562048945435600381[4] = -nom_x[4] + true_x[4];
   out_4562048945435600381[5] = -nom_x[5] + true_x[5];
   out_4562048945435600381[6] = -nom_x[6] + true_x[6];
   out_4562048945435600381[7] = -nom_x[7] + true_x[7];
   out_4562048945435600381[8] = -nom_x[8] + true_x[8];
   out_4562048945435600381[9] = -nom_x[9] + true_x[9];
   out_4562048945435600381[10] = -nom_x[10] + true_x[10];
   out_4562048945435600381[11] = -nom_x[11] + true_x[11];
   out_4562048945435600381[12] = -nom_x[12] + true_x[12];
   out_4562048945435600381[13] = -nom_x[13] + true_x[13];
   out_4562048945435600381[14] = -nom_x[14] + true_x[14];
   out_4562048945435600381[15] = -nom_x[15] + true_x[15];
   out_4562048945435600381[16] = -nom_x[16] + true_x[16];
   out_4562048945435600381[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3635685799188405881) {
   out_3635685799188405881[0] = 1.0;
   out_3635685799188405881[1] = 0.0;
   out_3635685799188405881[2] = 0.0;
   out_3635685799188405881[3] = 0.0;
   out_3635685799188405881[4] = 0.0;
   out_3635685799188405881[5] = 0.0;
   out_3635685799188405881[6] = 0.0;
   out_3635685799188405881[7] = 0.0;
   out_3635685799188405881[8] = 0.0;
   out_3635685799188405881[9] = 0.0;
   out_3635685799188405881[10] = 0.0;
   out_3635685799188405881[11] = 0.0;
   out_3635685799188405881[12] = 0.0;
   out_3635685799188405881[13] = 0.0;
   out_3635685799188405881[14] = 0.0;
   out_3635685799188405881[15] = 0.0;
   out_3635685799188405881[16] = 0.0;
   out_3635685799188405881[17] = 0.0;
   out_3635685799188405881[18] = 0.0;
   out_3635685799188405881[19] = 1.0;
   out_3635685799188405881[20] = 0.0;
   out_3635685799188405881[21] = 0.0;
   out_3635685799188405881[22] = 0.0;
   out_3635685799188405881[23] = 0.0;
   out_3635685799188405881[24] = 0.0;
   out_3635685799188405881[25] = 0.0;
   out_3635685799188405881[26] = 0.0;
   out_3635685799188405881[27] = 0.0;
   out_3635685799188405881[28] = 0.0;
   out_3635685799188405881[29] = 0.0;
   out_3635685799188405881[30] = 0.0;
   out_3635685799188405881[31] = 0.0;
   out_3635685799188405881[32] = 0.0;
   out_3635685799188405881[33] = 0.0;
   out_3635685799188405881[34] = 0.0;
   out_3635685799188405881[35] = 0.0;
   out_3635685799188405881[36] = 0.0;
   out_3635685799188405881[37] = 0.0;
   out_3635685799188405881[38] = 1.0;
   out_3635685799188405881[39] = 0.0;
   out_3635685799188405881[40] = 0.0;
   out_3635685799188405881[41] = 0.0;
   out_3635685799188405881[42] = 0.0;
   out_3635685799188405881[43] = 0.0;
   out_3635685799188405881[44] = 0.0;
   out_3635685799188405881[45] = 0.0;
   out_3635685799188405881[46] = 0.0;
   out_3635685799188405881[47] = 0.0;
   out_3635685799188405881[48] = 0.0;
   out_3635685799188405881[49] = 0.0;
   out_3635685799188405881[50] = 0.0;
   out_3635685799188405881[51] = 0.0;
   out_3635685799188405881[52] = 0.0;
   out_3635685799188405881[53] = 0.0;
   out_3635685799188405881[54] = 0.0;
   out_3635685799188405881[55] = 0.0;
   out_3635685799188405881[56] = 0.0;
   out_3635685799188405881[57] = 1.0;
   out_3635685799188405881[58] = 0.0;
   out_3635685799188405881[59] = 0.0;
   out_3635685799188405881[60] = 0.0;
   out_3635685799188405881[61] = 0.0;
   out_3635685799188405881[62] = 0.0;
   out_3635685799188405881[63] = 0.0;
   out_3635685799188405881[64] = 0.0;
   out_3635685799188405881[65] = 0.0;
   out_3635685799188405881[66] = 0.0;
   out_3635685799188405881[67] = 0.0;
   out_3635685799188405881[68] = 0.0;
   out_3635685799188405881[69] = 0.0;
   out_3635685799188405881[70] = 0.0;
   out_3635685799188405881[71] = 0.0;
   out_3635685799188405881[72] = 0.0;
   out_3635685799188405881[73] = 0.0;
   out_3635685799188405881[74] = 0.0;
   out_3635685799188405881[75] = 0.0;
   out_3635685799188405881[76] = 1.0;
   out_3635685799188405881[77] = 0.0;
   out_3635685799188405881[78] = 0.0;
   out_3635685799188405881[79] = 0.0;
   out_3635685799188405881[80] = 0.0;
   out_3635685799188405881[81] = 0.0;
   out_3635685799188405881[82] = 0.0;
   out_3635685799188405881[83] = 0.0;
   out_3635685799188405881[84] = 0.0;
   out_3635685799188405881[85] = 0.0;
   out_3635685799188405881[86] = 0.0;
   out_3635685799188405881[87] = 0.0;
   out_3635685799188405881[88] = 0.0;
   out_3635685799188405881[89] = 0.0;
   out_3635685799188405881[90] = 0.0;
   out_3635685799188405881[91] = 0.0;
   out_3635685799188405881[92] = 0.0;
   out_3635685799188405881[93] = 0.0;
   out_3635685799188405881[94] = 0.0;
   out_3635685799188405881[95] = 1.0;
   out_3635685799188405881[96] = 0.0;
   out_3635685799188405881[97] = 0.0;
   out_3635685799188405881[98] = 0.0;
   out_3635685799188405881[99] = 0.0;
   out_3635685799188405881[100] = 0.0;
   out_3635685799188405881[101] = 0.0;
   out_3635685799188405881[102] = 0.0;
   out_3635685799188405881[103] = 0.0;
   out_3635685799188405881[104] = 0.0;
   out_3635685799188405881[105] = 0.0;
   out_3635685799188405881[106] = 0.0;
   out_3635685799188405881[107] = 0.0;
   out_3635685799188405881[108] = 0.0;
   out_3635685799188405881[109] = 0.0;
   out_3635685799188405881[110] = 0.0;
   out_3635685799188405881[111] = 0.0;
   out_3635685799188405881[112] = 0.0;
   out_3635685799188405881[113] = 0.0;
   out_3635685799188405881[114] = 1.0;
   out_3635685799188405881[115] = 0.0;
   out_3635685799188405881[116] = 0.0;
   out_3635685799188405881[117] = 0.0;
   out_3635685799188405881[118] = 0.0;
   out_3635685799188405881[119] = 0.0;
   out_3635685799188405881[120] = 0.0;
   out_3635685799188405881[121] = 0.0;
   out_3635685799188405881[122] = 0.0;
   out_3635685799188405881[123] = 0.0;
   out_3635685799188405881[124] = 0.0;
   out_3635685799188405881[125] = 0.0;
   out_3635685799188405881[126] = 0.0;
   out_3635685799188405881[127] = 0.0;
   out_3635685799188405881[128] = 0.0;
   out_3635685799188405881[129] = 0.0;
   out_3635685799188405881[130] = 0.0;
   out_3635685799188405881[131] = 0.0;
   out_3635685799188405881[132] = 0.0;
   out_3635685799188405881[133] = 1.0;
   out_3635685799188405881[134] = 0.0;
   out_3635685799188405881[135] = 0.0;
   out_3635685799188405881[136] = 0.0;
   out_3635685799188405881[137] = 0.0;
   out_3635685799188405881[138] = 0.0;
   out_3635685799188405881[139] = 0.0;
   out_3635685799188405881[140] = 0.0;
   out_3635685799188405881[141] = 0.0;
   out_3635685799188405881[142] = 0.0;
   out_3635685799188405881[143] = 0.0;
   out_3635685799188405881[144] = 0.0;
   out_3635685799188405881[145] = 0.0;
   out_3635685799188405881[146] = 0.0;
   out_3635685799188405881[147] = 0.0;
   out_3635685799188405881[148] = 0.0;
   out_3635685799188405881[149] = 0.0;
   out_3635685799188405881[150] = 0.0;
   out_3635685799188405881[151] = 0.0;
   out_3635685799188405881[152] = 1.0;
   out_3635685799188405881[153] = 0.0;
   out_3635685799188405881[154] = 0.0;
   out_3635685799188405881[155] = 0.0;
   out_3635685799188405881[156] = 0.0;
   out_3635685799188405881[157] = 0.0;
   out_3635685799188405881[158] = 0.0;
   out_3635685799188405881[159] = 0.0;
   out_3635685799188405881[160] = 0.0;
   out_3635685799188405881[161] = 0.0;
   out_3635685799188405881[162] = 0.0;
   out_3635685799188405881[163] = 0.0;
   out_3635685799188405881[164] = 0.0;
   out_3635685799188405881[165] = 0.0;
   out_3635685799188405881[166] = 0.0;
   out_3635685799188405881[167] = 0.0;
   out_3635685799188405881[168] = 0.0;
   out_3635685799188405881[169] = 0.0;
   out_3635685799188405881[170] = 0.0;
   out_3635685799188405881[171] = 1.0;
   out_3635685799188405881[172] = 0.0;
   out_3635685799188405881[173] = 0.0;
   out_3635685799188405881[174] = 0.0;
   out_3635685799188405881[175] = 0.0;
   out_3635685799188405881[176] = 0.0;
   out_3635685799188405881[177] = 0.0;
   out_3635685799188405881[178] = 0.0;
   out_3635685799188405881[179] = 0.0;
   out_3635685799188405881[180] = 0.0;
   out_3635685799188405881[181] = 0.0;
   out_3635685799188405881[182] = 0.0;
   out_3635685799188405881[183] = 0.0;
   out_3635685799188405881[184] = 0.0;
   out_3635685799188405881[185] = 0.0;
   out_3635685799188405881[186] = 0.0;
   out_3635685799188405881[187] = 0.0;
   out_3635685799188405881[188] = 0.0;
   out_3635685799188405881[189] = 0.0;
   out_3635685799188405881[190] = 1.0;
   out_3635685799188405881[191] = 0.0;
   out_3635685799188405881[192] = 0.0;
   out_3635685799188405881[193] = 0.0;
   out_3635685799188405881[194] = 0.0;
   out_3635685799188405881[195] = 0.0;
   out_3635685799188405881[196] = 0.0;
   out_3635685799188405881[197] = 0.0;
   out_3635685799188405881[198] = 0.0;
   out_3635685799188405881[199] = 0.0;
   out_3635685799188405881[200] = 0.0;
   out_3635685799188405881[201] = 0.0;
   out_3635685799188405881[202] = 0.0;
   out_3635685799188405881[203] = 0.0;
   out_3635685799188405881[204] = 0.0;
   out_3635685799188405881[205] = 0.0;
   out_3635685799188405881[206] = 0.0;
   out_3635685799188405881[207] = 0.0;
   out_3635685799188405881[208] = 0.0;
   out_3635685799188405881[209] = 1.0;
   out_3635685799188405881[210] = 0.0;
   out_3635685799188405881[211] = 0.0;
   out_3635685799188405881[212] = 0.0;
   out_3635685799188405881[213] = 0.0;
   out_3635685799188405881[214] = 0.0;
   out_3635685799188405881[215] = 0.0;
   out_3635685799188405881[216] = 0.0;
   out_3635685799188405881[217] = 0.0;
   out_3635685799188405881[218] = 0.0;
   out_3635685799188405881[219] = 0.0;
   out_3635685799188405881[220] = 0.0;
   out_3635685799188405881[221] = 0.0;
   out_3635685799188405881[222] = 0.0;
   out_3635685799188405881[223] = 0.0;
   out_3635685799188405881[224] = 0.0;
   out_3635685799188405881[225] = 0.0;
   out_3635685799188405881[226] = 0.0;
   out_3635685799188405881[227] = 0.0;
   out_3635685799188405881[228] = 1.0;
   out_3635685799188405881[229] = 0.0;
   out_3635685799188405881[230] = 0.0;
   out_3635685799188405881[231] = 0.0;
   out_3635685799188405881[232] = 0.0;
   out_3635685799188405881[233] = 0.0;
   out_3635685799188405881[234] = 0.0;
   out_3635685799188405881[235] = 0.0;
   out_3635685799188405881[236] = 0.0;
   out_3635685799188405881[237] = 0.0;
   out_3635685799188405881[238] = 0.0;
   out_3635685799188405881[239] = 0.0;
   out_3635685799188405881[240] = 0.0;
   out_3635685799188405881[241] = 0.0;
   out_3635685799188405881[242] = 0.0;
   out_3635685799188405881[243] = 0.0;
   out_3635685799188405881[244] = 0.0;
   out_3635685799188405881[245] = 0.0;
   out_3635685799188405881[246] = 0.0;
   out_3635685799188405881[247] = 1.0;
   out_3635685799188405881[248] = 0.0;
   out_3635685799188405881[249] = 0.0;
   out_3635685799188405881[250] = 0.0;
   out_3635685799188405881[251] = 0.0;
   out_3635685799188405881[252] = 0.0;
   out_3635685799188405881[253] = 0.0;
   out_3635685799188405881[254] = 0.0;
   out_3635685799188405881[255] = 0.0;
   out_3635685799188405881[256] = 0.0;
   out_3635685799188405881[257] = 0.0;
   out_3635685799188405881[258] = 0.0;
   out_3635685799188405881[259] = 0.0;
   out_3635685799188405881[260] = 0.0;
   out_3635685799188405881[261] = 0.0;
   out_3635685799188405881[262] = 0.0;
   out_3635685799188405881[263] = 0.0;
   out_3635685799188405881[264] = 0.0;
   out_3635685799188405881[265] = 0.0;
   out_3635685799188405881[266] = 1.0;
   out_3635685799188405881[267] = 0.0;
   out_3635685799188405881[268] = 0.0;
   out_3635685799188405881[269] = 0.0;
   out_3635685799188405881[270] = 0.0;
   out_3635685799188405881[271] = 0.0;
   out_3635685799188405881[272] = 0.0;
   out_3635685799188405881[273] = 0.0;
   out_3635685799188405881[274] = 0.0;
   out_3635685799188405881[275] = 0.0;
   out_3635685799188405881[276] = 0.0;
   out_3635685799188405881[277] = 0.0;
   out_3635685799188405881[278] = 0.0;
   out_3635685799188405881[279] = 0.0;
   out_3635685799188405881[280] = 0.0;
   out_3635685799188405881[281] = 0.0;
   out_3635685799188405881[282] = 0.0;
   out_3635685799188405881[283] = 0.0;
   out_3635685799188405881[284] = 0.0;
   out_3635685799188405881[285] = 1.0;
   out_3635685799188405881[286] = 0.0;
   out_3635685799188405881[287] = 0.0;
   out_3635685799188405881[288] = 0.0;
   out_3635685799188405881[289] = 0.0;
   out_3635685799188405881[290] = 0.0;
   out_3635685799188405881[291] = 0.0;
   out_3635685799188405881[292] = 0.0;
   out_3635685799188405881[293] = 0.0;
   out_3635685799188405881[294] = 0.0;
   out_3635685799188405881[295] = 0.0;
   out_3635685799188405881[296] = 0.0;
   out_3635685799188405881[297] = 0.0;
   out_3635685799188405881[298] = 0.0;
   out_3635685799188405881[299] = 0.0;
   out_3635685799188405881[300] = 0.0;
   out_3635685799188405881[301] = 0.0;
   out_3635685799188405881[302] = 0.0;
   out_3635685799188405881[303] = 0.0;
   out_3635685799188405881[304] = 1.0;
   out_3635685799188405881[305] = 0.0;
   out_3635685799188405881[306] = 0.0;
   out_3635685799188405881[307] = 0.0;
   out_3635685799188405881[308] = 0.0;
   out_3635685799188405881[309] = 0.0;
   out_3635685799188405881[310] = 0.0;
   out_3635685799188405881[311] = 0.0;
   out_3635685799188405881[312] = 0.0;
   out_3635685799188405881[313] = 0.0;
   out_3635685799188405881[314] = 0.0;
   out_3635685799188405881[315] = 0.0;
   out_3635685799188405881[316] = 0.0;
   out_3635685799188405881[317] = 0.0;
   out_3635685799188405881[318] = 0.0;
   out_3635685799188405881[319] = 0.0;
   out_3635685799188405881[320] = 0.0;
   out_3635685799188405881[321] = 0.0;
   out_3635685799188405881[322] = 0.0;
   out_3635685799188405881[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_223023666217574094) {
   out_223023666217574094[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_223023666217574094[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_223023666217574094[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_223023666217574094[3] = dt*state[12] + state[3];
   out_223023666217574094[4] = dt*state[13] + state[4];
   out_223023666217574094[5] = dt*state[14] + state[5];
   out_223023666217574094[6] = state[6];
   out_223023666217574094[7] = state[7];
   out_223023666217574094[8] = state[8];
   out_223023666217574094[9] = state[9];
   out_223023666217574094[10] = state[10];
   out_223023666217574094[11] = state[11];
   out_223023666217574094[12] = state[12];
   out_223023666217574094[13] = state[13];
   out_223023666217574094[14] = state[14];
   out_223023666217574094[15] = state[15];
   out_223023666217574094[16] = state[16];
   out_223023666217574094[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6563490807838139396) {
   out_6563490807838139396[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6563490807838139396[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6563490807838139396[2] = 0;
   out_6563490807838139396[3] = 0;
   out_6563490807838139396[4] = 0;
   out_6563490807838139396[5] = 0;
   out_6563490807838139396[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6563490807838139396[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6563490807838139396[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6563490807838139396[9] = 0;
   out_6563490807838139396[10] = 0;
   out_6563490807838139396[11] = 0;
   out_6563490807838139396[12] = 0;
   out_6563490807838139396[13] = 0;
   out_6563490807838139396[14] = 0;
   out_6563490807838139396[15] = 0;
   out_6563490807838139396[16] = 0;
   out_6563490807838139396[17] = 0;
   out_6563490807838139396[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6563490807838139396[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6563490807838139396[20] = 0;
   out_6563490807838139396[21] = 0;
   out_6563490807838139396[22] = 0;
   out_6563490807838139396[23] = 0;
   out_6563490807838139396[24] = 0;
   out_6563490807838139396[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6563490807838139396[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6563490807838139396[27] = 0;
   out_6563490807838139396[28] = 0;
   out_6563490807838139396[29] = 0;
   out_6563490807838139396[30] = 0;
   out_6563490807838139396[31] = 0;
   out_6563490807838139396[32] = 0;
   out_6563490807838139396[33] = 0;
   out_6563490807838139396[34] = 0;
   out_6563490807838139396[35] = 0;
   out_6563490807838139396[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6563490807838139396[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6563490807838139396[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6563490807838139396[39] = 0;
   out_6563490807838139396[40] = 0;
   out_6563490807838139396[41] = 0;
   out_6563490807838139396[42] = 0;
   out_6563490807838139396[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6563490807838139396[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6563490807838139396[45] = 0;
   out_6563490807838139396[46] = 0;
   out_6563490807838139396[47] = 0;
   out_6563490807838139396[48] = 0;
   out_6563490807838139396[49] = 0;
   out_6563490807838139396[50] = 0;
   out_6563490807838139396[51] = 0;
   out_6563490807838139396[52] = 0;
   out_6563490807838139396[53] = 0;
   out_6563490807838139396[54] = 0;
   out_6563490807838139396[55] = 0;
   out_6563490807838139396[56] = 0;
   out_6563490807838139396[57] = 1;
   out_6563490807838139396[58] = 0;
   out_6563490807838139396[59] = 0;
   out_6563490807838139396[60] = 0;
   out_6563490807838139396[61] = 0;
   out_6563490807838139396[62] = 0;
   out_6563490807838139396[63] = 0;
   out_6563490807838139396[64] = 0;
   out_6563490807838139396[65] = 0;
   out_6563490807838139396[66] = dt;
   out_6563490807838139396[67] = 0;
   out_6563490807838139396[68] = 0;
   out_6563490807838139396[69] = 0;
   out_6563490807838139396[70] = 0;
   out_6563490807838139396[71] = 0;
   out_6563490807838139396[72] = 0;
   out_6563490807838139396[73] = 0;
   out_6563490807838139396[74] = 0;
   out_6563490807838139396[75] = 0;
   out_6563490807838139396[76] = 1;
   out_6563490807838139396[77] = 0;
   out_6563490807838139396[78] = 0;
   out_6563490807838139396[79] = 0;
   out_6563490807838139396[80] = 0;
   out_6563490807838139396[81] = 0;
   out_6563490807838139396[82] = 0;
   out_6563490807838139396[83] = 0;
   out_6563490807838139396[84] = 0;
   out_6563490807838139396[85] = dt;
   out_6563490807838139396[86] = 0;
   out_6563490807838139396[87] = 0;
   out_6563490807838139396[88] = 0;
   out_6563490807838139396[89] = 0;
   out_6563490807838139396[90] = 0;
   out_6563490807838139396[91] = 0;
   out_6563490807838139396[92] = 0;
   out_6563490807838139396[93] = 0;
   out_6563490807838139396[94] = 0;
   out_6563490807838139396[95] = 1;
   out_6563490807838139396[96] = 0;
   out_6563490807838139396[97] = 0;
   out_6563490807838139396[98] = 0;
   out_6563490807838139396[99] = 0;
   out_6563490807838139396[100] = 0;
   out_6563490807838139396[101] = 0;
   out_6563490807838139396[102] = 0;
   out_6563490807838139396[103] = 0;
   out_6563490807838139396[104] = dt;
   out_6563490807838139396[105] = 0;
   out_6563490807838139396[106] = 0;
   out_6563490807838139396[107] = 0;
   out_6563490807838139396[108] = 0;
   out_6563490807838139396[109] = 0;
   out_6563490807838139396[110] = 0;
   out_6563490807838139396[111] = 0;
   out_6563490807838139396[112] = 0;
   out_6563490807838139396[113] = 0;
   out_6563490807838139396[114] = 1;
   out_6563490807838139396[115] = 0;
   out_6563490807838139396[116] = 0;
   out_6563490807838139396[117] = 0;
   out_6563490807838139396[118] = 0;
   out_6563490807838139396[119] = 0;
   out_6563490807838139396[120] = 0;
   out_6563490807838139396[121] = 0;
   out_6563490807838139396[122] = 0;
   out_6563490807838139396[123] = 0;
   out_6563490807838139396[124] = 0;
   out_6563490807838139396[125] = 0;
   out_6563490807838139396[126] = 0;
   out_6563490807838139396[127] = 0;
   out_6563490807838139396[128] = 0;
   out_6563490807838139396[129] = 0;
   out_6563490807838139396[130] = 0;
   out_6563490807838139396[131] = 0;
   out_6563490807838139396[132] = 0;
   out_6563490807838139396[133] = 1;
   out_6563490807838139396[134] = 0;
   out_6563490807838139396[135] = 0;
   out_6563490807838139396[136] = 0;
   out_6563490807838139396[137] = 0;
   out_6563490807838139396[138] = 0;
   out_6563490807838139396[139] = 0;
   out_6563490807838139396[140] = 0;
   out_6563490807838139396[141] = 0;
   out_6563490807838139396[142] = 0;
   out_6563490807838139396[143] = 0;
   out_6563490807838139396[144] = 0;
   out_6563490807838139396[145] = 0;
   out_6563490807838139396[146] = 0;
   out_6563490807838139396[147] = 0;
   out_6563490807838139396[148] = 0;
   out_6563490807838139396[149] = 0;
   out_6563490807838139396[150] = 0;
   out_6563490807838139396[151] = 0;
   out_6563490807838139396[152] = 1;
   out_6563490807838139396[153] = 0;
   out_6563490807838139396[154] = 0;
   out_6563490807838139396[155] = 0;
   out_6563490807838139396[156] = 0;
   out_6563490807838139396[157] = 0;
   out_6563490807838139396[158] = 0;
   out_6563490807838139396[159] = 0;
   out_6563490807838139396[160] = 0;
   out_6563490807838139396[161] = 0;
   out_6563490807838139396[162] = 0;
   out_6563490807838139396[163] = 0;
   out_6563490807838139396[164] = 0;
   out_6563490807838139396[165] = 0;
   out_6563490807838139396[166] = 0;
   out_6563490807838139396[167] = 0;
   out_6563490807838139396[168] = 0;
   out_6563490807838139396[169] = 0;
   out_6563490807838139396[170] = 0;
   out_6563490807838139396[171] = 1;
   out_6563490807838139396[172] = 0;
   out_6563490807838139396[173] = 0;
   out_6563490807838139396[174] = 0;
   out_6563490807838139396[175] = 0;
   out_6563490807838139396[176] = 0;
   out_6563490807838139396[177] = 0;
   out_6563490807838139396[178] = 0;
   out_6563490807838139396[179] = 0;
   out_6563490807838139396[180] = 0;
   out_6563490807838139396[181] = 0;
   out_6563490807838139396[182] = 0;
   out_6563490807838139396[183] = 0;
   out_6563490807838139396[184] = 0;
   out_6563490807838139396[185] = 0;
   out_6563490807838139396[186] = 0;
   out_6563490807838139396[187] = 0;
   out_6563490807838139396[188] = 0;
   out_6563490807838139396[189] = 0;
   out_6563490807838139396[190] = 1;
   out_6563490807838139396[191] = 0;
   out_6563490807838139396[192] = 0;
   out_6563490807838139396[193] = 0;
   out_6563490807838139396[194] = 0;
   out_6563490807838139396[195] = 0;
   out_6563490807838139396[196] = 0;
   out_6563490807838139396[197] = 0;
   out_6563490807838139396[198] = 0;
   out_6563490807838139396[199] = 0;
   out_6563490807838139396[200] = 0;
   out_6563490807838139396[201] = 0;
   out_6563490807838139396[202] = 0;
   out_6563490807838139396[203] = 0;
   out_6563490807838139396[204] = 0;
   out_6563490807838139396[205] = 0;
   out_6563490807838139396[206] = 0;
   out_6563490807838139396[207] = 0;
   out_6563490807838139396[208] = 0;
   out_6563490807838139396[209] = 1;
   out_6563490807838139396[210] = 0;
   out_6563490807838139396[211] = 0;
   out_6563490807838139396[212] = 0;
   out_6563490807838139396[213] = 0;
   out_6563490807838139396[214] = 0;
   out_6563490807838139396[215] = 0;
   out_6563490807838139396[216] = 0;
   out_6563490807838139396[217] = 0;
   out_6563490807838139396[218] = 0;
   out_6563490807838139396[219] = 0;
   out_6563490807838139396[220] = 0;
   out_6563490807838139396[221] = 0;
   out_6563490807838139396[222] = 0;
   out_6563490807838139396[223] = 0;
   out_6563490807838139396[224] = 0;
   out_6563490807838139396[225] = 0;
   out_6563490807838139396[226] = 0;
   out_6563490807838139396[227] = 0;
   out_6563490807838139396[228] = 1;
   out_6563490807838139396[229] = 0;
   out_6563490807838139396[230] = 0;
   out_6563490807838139396[231] = 0;
   out_6563490807838139396[232] = 0;
   out_6563490807838139396[233] = 0;
   out_6563490807838139396[234] = 0;
   out_6563490807838139396[235] = 0;
   out_6563490807838139396[236] = 0;
   out_6563490807838139396[237] = 0;
   out_6563490807838139396[238] = 0;
   out_6563490807838139396[239] = 0;
   out_6563490807838139396[240] = 0;
   out_6563490807838139396[241] = 0;
   out_6563490807838139396[242] = 0;
   out_6563490807838139396[243] = 0;
   out_6563490807838139396[244] = 0;
   out_6563490807838139396[245] = 0;
   out_6563490807838139396[246] = 0;
   out_6563490807838139396[247] = 1;
   out_6563490807838139396[248] = 0;
   out_6563490807838139396[249] = 0;
   out_6563490807838139396[250] = 0;
   out_6563490807838139396[251] = 0;
   out_6563490807838139396[252] = 0;
   out_6563490807838139396[253] = 0;
   out_6563490807838139396[254] = 0;
   out_6563490807838139396[255] = 0;
   out_6563490807838139396[256] = 0;
   out_6563490807838139396[257] = 0;
   out_6563490807838139396[258] = 0;
   out_6563490807838139396[259] = 0;
   out_6563490807838139396[260] = 0;
   out_6563490807838139396[261] = 0;
   out_6563490807838139396[262] = 0;
   out_6563490807838139396[263] = 0;
   out_6563490807838139396[264] = 0;
   out_6563490807838139396[265] = 0;
   out_6563490807838139396[266] = 1;
   out_6563490807838139396[267] = 0;
   out_6563490807838139396[268] = 0;
   out_6563490807838139396[269] = 0;
   out_6563490807838139396[270] = 0;
   out_6563490807838139396[271] = 0;
   out_6563490807838139396[272] = 0;
   out_6563490807838139396[273] = 0;
   out_6563490807838139396[274] = 0;
   out_6563490807838139396[275] = 0;
   out_6563490807838139396[276] = 0;
   out_6563490807838139396[277] = 0;
   out_6563490807838139396[278] = 0;
   out_6563490807838139396[279] = 0;
   out_6563490807838139396[280] = 0;
   out_6563490807838139396[281] = 0;
   out_6563490807838139396[282] = 0;
   out_6563490807838139396[283] = 0;
   out_6563490807838139396[284] = 0;
   out_6563490807838139396[285] = 1;
   out_6563490807838139396[286] = 0;
   out_6563490807838139396[287] = 0;
   out_6563490807838139396[288] = 0;
   out_6563490807838139396[289] = 0;
   out_6563490807838139396[290] = 0;
   out_6563490807838139396[291] = 0;
   out_6563490807838139396[292] = 0;
   out_6563490807838139396[293] = 0;
   out_6563490807838139396[294] = 0;
   out_6563490807838139396[295] = 0;
   out_6563490807838139396[296] = 0;
   out_6563490807838139396[297] = 0;
   out_6563490807838139396[298] = 0;
   out_6563490807838139396[299] = 0;
   out_6563490807838139396[300] = 0;
   out_6563490807838139396[301] = 0;
   out_6563490807838139396[302] = 0;
   out_6563490807838139396[303] = 0;
   out_6563490807838139396[304] = 1;
   out_6563490807838139396[305] = 0;
   out_6563490807838139396[306] = 0;
   out_6563490807838139396[307] = 0;
   out_6563490807838139396[308] = 0;
   out_6563490807838139396[309] = 0;
   out_6563490807838139396[310] = 0;
   out_6563490807838139396[311] = 0;
   out_6563490807838139396[312] = 0;
   out_6563490807838139396[313] = 0;
   out_6563490807838139396[314] = 0;
   out_6563490807838139396[315] = 0;
   out_6563490807838139396[316] = 0;
   out_6563490807838139396[317] = 0;
   out_6563490807838139396[318] = 0;
   out_6563490807838139396[319] = 0;
   out_6563490807838139396[320] = 0;
   out_6563490807838139396[321] = 0;
   out_6563490807838139396[322] = 0;
   out_6563490807838139396[323] = 1;
}
void h_4(double *state, double *unused, double *out_2709224699571416582) {
   out_2709224699571416582[0] = state[6] + state[9];
   out_2709224699571416582[1] = state[7] + state[10];
   out_2709224699571416582[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2881524797133693274) {
   out_2881524797133693274[0] = 0;
   out_2881524797133693274[1] = 0;
   out_2881524797133693274[2] = 0;
   out_2881524797133693274[3] = 0;
   out_2881524797133693274[4] = 0;
   out_2881524797133693274[5] = 0;
   out_2881524797133693274[6] = 1;
   out_2881524797133693274[7] = 0;
   out_2881524797133693274[8] = 0;
   out_2881524797133693274[9] = 1;
   out_2881524797133693274[10] = 0;
   out_2881524797133693274[11] = 0;
   out_2881524797133693274[12] = 0;
   out_2881524797133693274[13] = 0;
   out_2881524797133693274[14] = 0;
   out_2881524797133693274[15] = 0;
   out_2881524797133693274[16] = 0;
   out_2881524797133693274[17] = 0;
   out_2881524797133693274[18] = 0;
   out_2881524797133693274[19] = 0;
   out_2881524797133693274[20] = 0;
   out_2881524797133693274[21] = 0;
   out_2881524797133693274[22] = 0;
   out_2881524797133693274[23] = 0;
   out_2881524797133693274[24] = 0;
   out_2881524797133693274[25] = 1;
   out_2881524797133693274[26] = 0;
   out_2881524797133693274[27] = 0;
   out_2881524797133693274[28] = 1;
   out_2881524797133693274[29] = 0;
   out_2881524797133693274[30] = 0;
   out_2881524797133693274[31] = 0;
   out_2881524797133693274[32] = 0;
   out_2881524797133693274[33] = 0;
   out_2881524797133693274[34] = 0;
   out_2881524797133693274[35] = 0;
   out_2881524797133693274[36] = 0;
   out_2881524797133693274[37] = 0;
   out_2881524797133693274[38] = 0;
   out_2881524797133693274[39] = 0;
   out_2881524797133693274[40] = 0;
   out_2881524797133693274[41] = 0;
   out_2881524797133693274[42] = 0;
   out_2881524797133693274[43] = 0;
   out_2881524797133693274[44] = 1;
   out_2881524797133693274[45] = 0;
   out_2881524797133693274[46] = 0;
   out_2881524797133693274[47] = 1;
   out_2881524797133693274[48] = 0;
   out_2881524797133693274[49] = 0;
   out_2881524797133693274[50] = 0;
   out_2881524797133693274[51] = 0;
   out_2881524797133693274[52] = 0;
   out_2881524797133693274[53] = 0;
}
void h_10(double *state, double *unused, double *out_528563670856782628) {
   out_528563670856782628[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_528563670856782628[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_528563670856782628[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3212086573286679008) {
   out_3212086573286679008[0] = 0;
   out_3212086573286679008[1] = 9.8100000000000005*cos(state[1]);
   out_3212086573286679008[2] = 0;
   out_3212086573286679008[3] = 0;
   out_3212086573286679008[4] = -state[8];
   out_3212086573286679008[5] = state[7];
   out_3212086573286679008[6] = 0;
   out_3212086573286679008[7] = state[5];
   out_3212086573286679008[8] = -state[4];
   out_3212086573286679008[9] = 0;
   out_3212086573286679008[10] = 0;
   out_3212086573286679008[11] = 0;
   out_3212086573286679008[12] = 1;
   out_3212086573286679008[13] = 0;
   out_3212086573286679008[14] = 0;
   out_3212086573286679008[15] = 1;
   out_3212086573286679008[16] = 0;
   out_3212086573286679008[17] = 0;
   out_3212086573286679008[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3212086573286679008[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3212086573286679008[20] = 0;
   out_3212086573286679008[21] = state[8];
   out_3212086573286679008[22] = 0;
   out_3212086573286679008[23] = -state[6];
   out_3212086573286679008[24] = -state[5];
   out_3212086573286679008[25] = 0;
   out_3212086573286679008[26] = state[3];
   out_3212086573286679008[27] = 0;
   out_3212086573286679008[28] = 0;
   out_3212086573286679008[29] = 0;
   out_3212086573286679008[30] = 0;
   out_3212086573286679008[31] = 1;
   out_3212086573286679008[32] = 0;
   out_3212086573286679008[33] = 0;
   out_3212086573286679008[34] = 1;
   out_3212086573286679008[35] = 0;
   out_3212086573286679008[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3212086573286679008[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3212086573286679008[38] = 0;
   out_3212086573286679008[39] = -state[7];
   out_3212086573286679008[40] = state[6];
   out_3212086573286679008[41] = 0;
   out_3212086573286679008[42] = state[4];
   out_3212086573286679008[43] = -state[3];
   out_3212086573286679008[44] = 0;
   out_3212086573286679008[45] = 0;
   out_3212086573286679008[46] = 0;
   out_3212086573286679008[47] = 0;
   out_3212086573286679008[48] = 0;
   out_3212086573286679008[49] = 0;
   out_3212086573286679008[50] = 1;
   out_3212086573286679008[51] = 0;
   out_3212086573286679008[52] = 0;
   out_3212086573286679008[53] = 1;
}
void h_13(double *state, double *unused, double *out_5134071672757776268) {
   out_5134071672757776268[0] = state[3];
   out_5134071672757776268[1] = state[4];
   out_5134071672757776268[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4729106411183007655) {
   out_4729106411183007655[0] = 0;
   out_4729106411183007655[1] = 0;
   out_4729106411183007655[2] = 0;
   out_4729106411183007655[3] = 1;
   out_4729106411183007655[4] = 0;
   out_4729106411183007655[5] = 0;
   out_4729106411183007655[6] = 0;
   out_4729106411183007655[7] = 0;
   out_4729106411183007655[8] = 0;
   out_4729106411183007655[9] = 0;
   out_4729106411183007655[10] = 0;
   out_4729106411183007655[11] = 0;
   out_4729106411183007655[12] = 0;
   out_4729106411183007655[13] = 0;
   out_4729106411183007655[14] = 0;
   out_4729106411183007655[15] = 0;
   out_4729106411183007655[16] = 0;
   out_4729106411183007655[17] = 0;
   out_4729106411183007655[18] = 0;
   out_4729106411183007655[19] = 0;
   out_4729106411183007655[20] = 0;
   out_4729106411183007655[21] = 0;
   out_4729106411183007655[22] = 1;
   out_4729106411183007655[23] = 0;
   out_4729106411183007655[24] = 0;
   out_4729106411183007655[25] = 0;
   out_4729106411183007655[26] = 0;
   out_4729106411183007655[27] = 0;
   out_4729106411183007655[28] = 0;
   out_4729106411183007655[29] = 0;
   out_4729106411183007655[30] = 0;
   out_4729106411183007655[31] = 0;
   out_4729106411183007655[32] = 0;
   out_4729106411183007655[33] = 0;
   out_4729106411183007655[34] = 0;
   out_4729106411183007655[35] = 0;
   out_4729106411183007655[36] = 0;
   out_4729106411183007655[37] = 0;
   out_4729106411183007655[38] = 0;
   out_4729106411183007655[39] = 0;
   out_4729106411183007655[40] = 0;
   out_4729106411183007655[41] = 1;
   out_4729106411183007655[42] = 0;
   out_4729106411183007655[43] = 0;
   out_4729106411183007655[44] = 0;
   out_4729106411183007655[45] = 0;
   out_4729106411183007655[46] = 0;
   out_4729106411183007655[47] = 0;
   out_4729106411183007655[48] = 0;
   out_4729106411183007655[49] = 0;
   out_4729106411183007655[50] = 0;
   out_4729106411183007655[51] = 0;
   out_4729106411183007655[52] = 0;
   out_4729106411183007655[53] = 0;
}
void h_14(double *state, double *unused, double *out_7319951522008375092) {
   out_7319951522008375092[0] = state[6];
   out_7319951522008375092[1] = state[7];
   out_7319951522008375092[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1081716059205791255) {
   out_1081716059205791255[0] = 0;
   out_1081716059205791255[1] = 0;
   out_1081716059205791255[2] = 0;
   out_1081716059205791255[3] = 0;
   out_1081716059205791255[4] = 0;
   out_1081716059205791255[5] = 0;
   out_1081716059205791255[6] = 1;
   out_1081716059205791255[7] = 0;
   out_1081716059205791255[8] = 0;
   out_1081716059205791255[9] = 0;
   out_1081716059205791255[10] = 0;
   out_1081716059205791255[11] = 0;
   out_1081716059205791255[12] = 0;
   out_1081716059205791255[13] = 0;
   out_1081716059205791255[14] = 0;
   out_1081716059205791255[15] = 0;
   out_1081716059205791255[16] = 0;
   out_1081716059205791255[17] = 0;
   out_1081716059205791255[18] = 0;
   out_1081716059205791255[19] = 0;
   out_1081716059205791255[20] = 0;
   out_1081716059205791255[21] = 0;
   out_1081716059205791255[22] = 0;
   out_1081716059205791255[23] = 0;
   out_1081716059205791255[24] = 0;
   out_1081716059205791255[25] = 1;
   out_1081716059205791255[26] = 0;
   out_1081716059205791255[27] = 0;
   out_1081716059205791255[28] = 0;
   out_1081716059205791255[29] = 0;
   out_1081716059205791255[30] = 0;
   out_1081716059205791255[31] = 0;
   out_1081716059205791255[32] = 0;
   out_1081716059205791255[33] = 0;
   out_1081716059205791255[34] = 0;
   out_1081716059205791255[35] = 0;
   out_1081716059205791255[36] = 0;
   out_1081716059205791255[37] = 0;
   out_1081716059205791255[38] = 0;
   out_1081716059205791255[39] = 0;
   out_1081716059205791255[40] = 0;
   out_1081716059205791255[41] = 0;
   out_1081716059205791255[42] = 0;
   out_1081716059205791255[43] = 0;
   out_1081716059205791255[44] = 1;
   out_1081716059205791255[45] = 0;
   out_1081716059205791255[46] = 0;
   out_1081716059205791255[47] = 0;
   out_1081716059205791255[48] = 0;
   out_1081716059205791255[49] = 0;
   out_1081716059205791255[50] = 0;
   out_1081716059205791255[51] = 0;
   out_1081716059205791255[52] = 0;
   out_1081716059205791255[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3324107228628984672) {
  err_fun(nom_x, delta_x, out_3324107228628984672);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4562048945435600381) {
  inv_err_fun(nom_x, true_x, out_4562048945435600381);
}
void pose_H_mod_fun(double *state, double *out_3635685799188405881) {
  H_mod_fun(state, out_3635685799188405881);
}
void pose_f_fun(double *state, double dt, double *out_223023666217574094) {
  f_fun(state,  dt, out_223023666217574094);
}
void pose_F_fun(double *state, double dt, double *out_6563490807838139396) {
  F_fun(state,  dt, out_6563490807838139396);
}
void pose_h_4(double *state, double *unused, double *out_2709224699571416582) {
  h_4(state, unused, out_2709224699571416582);
}
void pose_H_4(double *state, double *unused, double *out_2881524797133693274) {
  H_4(state, unused, out_2881524797133693274);
}
void pose_h_10(double *state, double *unused, double *out_528563670856782628) {
  h_10(state, unused, out_528563670856782628);
}
void pose_H_10(double *state, double *unused, double *out_3212086573286679008) {
  H_10(state, unused, out_3212086573286679008);
}
void pose_h_13(double *state, double *unused, double *out_5134071672757776268) {
  h_13(state, unused, out_5134071672757776268);
}
void pose_H_13(double *state, double *unused, double *out_4729106411183007655) {
  H_13(state, unused, out_4729106411183007655);
}
void pose_h_14(double *state, double *unused, double *out_7319951522008375092) {
  h_14(state, unused, out_7319951522008375092);
}
void pose_H_14(double *state, double *unused, double *out_1081716059205791255) {
  H_14(state, unused, out_1081716059205791255);
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
