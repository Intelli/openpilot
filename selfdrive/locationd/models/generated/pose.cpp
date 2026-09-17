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
void err_fun(double *nom_x, double *delta_x, double *out_8200257521780243420) {
   out_8200257521780243420[0] = delta_x[0] + nom_x[0];
   out_8200257521780243420[1] = delta_x[1] + nom_x[1];
   out_8200257521780243420[2] = delta_x[2] + nom_x[2];
   out_8200257521780243420[3] = delta_x[3] + nom_x[3];
   out_8200257521780243420[4] = delta_x[4] + nom_x[4];
   out_8200257521780243420[5] = delta_x[5] + nom_x[5];
   out_8200257521780243420[6] = delta_x[6] + nom_x[6];
   out_8200257521780243420[7] = delta_x[7] + nom_x[7];
   out_8200257521780243420[8] = delta_x[8] + nom_x[8];
   out_8200257521780243420[9] = delta_x[9] + nom_x[9];
   out_8200257521780243420[10] = delta_x[10] + nom_x[10];
   out_8200257521780243420[11] = delta_x[11] + nom_x[11];
   out_8200257521780243420[12] = delta_x[12] + nom_x[12];
   out_8200257521780243420[13] = delta_x[13] + nom_x[13];
   out_8200257521780243420[14] = delta_x[14] + nom_x[14];
   out_8200257521780243420[15] = delta_x[15] + nom_x[15];
   out_8200257521780243420[16] = delta_x[16] + nom_x[16];
   out_8200257521780243420[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3514907883279273646) {
   out_3514907883279273646[0] = -nom_x[0] + true_x[0];
   out_3514907883279273646[1] = -nom_x[1] + true_x[1];
   out_3514907883279273646[2] = -nom_x[2] + true_x[2];
   out_3514907883279273646[3] = -nom_x[3] + true_x[3];
   out_3514907883279273646[4] = -nom_x[4] + true_x[4];
   out_3514907883279273646[5] = -nom_x[5] + true_x[5];
   out_3514907883279273646[6] = -nom_x[6] + true_x[6];
   out_3514907883279273646[7] = -nom_x[7] + true_x[7];
   out_3514907883279273646[8] = -nom_x[8] + true_x[8];
   out_3514907883279273646[9] = -nom_x[9] + true_x[9];
   out_3514907883279273646[10] = -nom_x[10] + true_x[10];
   out_3514907883279273646[11] = -nom_x[11] + true_x[11];
   out_3514907883279273646[12] = -nom_x[12] + true_x[12];
   out_3514907883279273646[13] = -nom_x[13] + true_x[13];
   out_3514907883279273646[14] = -nom_x[14] + true_x[14];
   out_3514907883279273646[15] = -nom_x[15] + true_x[15];
   out_3514907883279273646[16] = -nom_x[16] + true_x[16];
   out_3514907883279273646[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3189646925905620491) {
   out_3189646925905620491[0] = 1.0;
   out_3189646925905620491[1] = 0.0;
   out_3189646925905620491[2] = 0.0;
   out_3189646925905620491[3] = 0.0;
   out_3189646925905620491[4] = 0.0;
   out_3189646925905620491[5] = 0.0;
   out_3189646925905620491[6] = 0.0;
   out_3189646925905620491[7] = 0.0;
   out_3189646925905620491[8] = 0.0;
   out_3189646925905620491[9] = 0.0;
   out_3189646925905620491[10] = 0.0;
   out_3189646925905620491[11] = 0.0;
   out_3189646925905620491[12] = 0.0;
   out_3189646925905620491[13] = 0.0;
   out_3189646925905620491[14] = 0.0;
   out_3189646925905620491[15] = 0.0;
   out_3189646925905620491[16] = 0.0;
   out_3189646925905620491[17] = 0.0;
   out_3189646925905620491[18] = 0.0;
   out_3189646925905620491[19] = 1.0;
   out_3189646925905620491[20] = 0.0;
   out_3189646925905620491[21] = 0.0;
   out_3189646925905620491[22] = 0.0;
   out_3189646925905620491[23] = 0.0;
   out_3189646925905620491[24] = 0.0;
   out_3189646925905620491[25] = 0.0;
   out_3189646925905620491[26] = 0.0;
   out_3189646925905620491[27] = 0.0;
   out_3189646925905620491[28] = 0.0;
   out_3189646925905620491[29] = 0.0;
   out_3189646925905620491[30] = 0.0;
   out_3189646925905620491[31] = 0.0;
   out_3189646925905620491[32] = 0.0;
   out_3189646925905620491[33] = 0.0;
   out_3189646925905620491[34] = 0.0;
   out_3189646925905620491[35] = 0.0;
   out_3189646925905620491[36] = 0.0;
   out_3189646925905620491[37] = 0.0;
   out_3189646925905620491[38] = 1.0;
   out_3189646925905620491[39] = 0.0;
   out_3189646925905620491[40] = 0.0;
   out_3189646925905620491[41] = 0.0;
   out_3189646925905620491[42] = 0.0;
   out_3189646925905620491[43] = 0.0;
   out_3189646925905620491[44] = 0.0;
   out_3189646925905620491[45] = 0.0;
   out_3189646925905620491[46] = 0.0;
   out_3189646925905620491[47] = 0.0;
   out_3189646925905620491[48] = 0.0;
   out_3189646925905620491[49] = 0.0;
   out_3189646925905620491[50] = 0.0;
   out_3189646925905620491[51] = 0.0;
   out_3189646925905620491[52] = 0.0;
   out_3189646925905620491[53] = 0.0;
   out_3189646925905620491[54] = 0.0;
   out_3189646925905620491[55] = 0.0;
   out_3189646925905620491[56] = 0.0;
   out_3189646925905620491[57] = 1.0;
   out_3189646925905620491[58] = 0.0;
   out_3189646925905620491[59] = 0.0;
   out_3189646925905620491[60] = 0.0;
   out_3189646925905620491[61] = 0.0;
   out_3189646925905620491[62] = 0.0;
   out_3189646925905620491[63] = 0.0;
   out_3189646925905620491[64] = 0.0;
   out_3189646925905620491[65] = 0.0;
   out_3189646925905620491[66] = 0.0;
   out_3189646925905620491[67] = 0.0;
   out_3189646925905620491[68] = 0.0;
   out_3189646925905620491[69] = 0.0;
   out_3189646925905620491[70] = 0.0;
   out_3189646925905620491[71] = 0.0;
   out_3189646925905620491[72] = 0.0;
   out_3189646925905620491[73] = 0.0;
   out_3189646925905620491[74] = 0.0;
   out_3189646925905620491[75] = 0.0;
   out_3189646925905620491[76] = 1.0;
   out_3189646925905620491[77] = 0.0;
   out_3189646925905620491[78] = 0.0;
   out_3189646925905620491[79] = 0.0;
   out_3189646925905620491[80] = 0.0;
   out_3189646925905620491[81] = 0.0;
   out_3189646925905620491[82] = 0.0;
   out_3189646925905620491[83] = 0.0;
   out_3189646925905620491[84] = 0.0;
   out_3189646925905620491[85] = 0.0;
   out_3189646925905620491[86] = 0.0;
   out_3189646925905620491[87] = 0.0;
   out_3189646925905620491[88] = 0.0;
   out_3189646925905620491[89] = 0.0;
   out_3189646925905620491[90] = 0.0;
   out_3189646925905620491[91] = 0.0;
   out_3189646925905620491[92] = 0.0;
   out_3189646925905620491[93] = 0.0;
   out_3189646925905620491[94] = 0.0;
   out_3189646925905620491[95] = 1.0;
   out_3189646925905620491[96] = 0.0;
   out_3189646925905620491[97] = 0.0;
   out_3189646925905620491[98] = 0.0;
   out_3189646925905620491[99] = 0.0;
   out_3189646925905620491[100] = 0.0;
   out_3189646925905620491[101] = 0.0;
   out_3189646925905620491[102] = 0.0;
   out_3189646925905620491[103] = 0.0;
   out_3189646925905620491[104] = 0.0;
   out_3189646925905620491[105] = 0.0;
   out_3189646925905620491[106] = 0.0;
   out_3189646925905620491[107] = 0.0;
   out_3189646925905620491[108] = 0.0;
   out_3189646925905620491[109] = 0.0;
   out_3189646925905620491[110] = 0.0;
   out_3189646925905620491[111] = 0.0;
   out_3189646925905620491[112] = 0.0;
   out_3189646925905620491[113] = 0.0;
   out_3189646925905620491[114] = 1.0;
   out_3189646925905620491[115] = 0.0;
   out_3189646925905620491[116] = 0.0;
   out_3189646925905620491[117] = 0.0;
   out_3189646925905620491[118] = 0.0;
   out_3189646925905620491[119] = 0.0;
   out_3189646925905620491[120] = 0.0;
   out_3189646925905620491[121] = 0.0;
   out_3189646925905620491[122] = 0.0;
   out_3189646925905620491[123] = 0.0;
   out_3189646925905620491[124] = 0.0;
   out_3189646925905620491[125] = 0.0;
   out_3189646925905620491[126] = 0.0;
   out_3189646925905620491[127] = 0.0;
   out_3189646925905620491[128] = 0.0;
   out_3189646925905620491[129] = 0.0;
   out_3189646925905620491[130] = 0.0;
   out_3189646925905620491[131] = 0.0;
   out_3189646925905620491[132] = 0.0;
   out_3189646925905620491[133] = 1.0;
   out_3189646925905620491[134] = 0.0;
   out_3189646925905620491[135] = 0.0;
   out_3189646925905620491[136] = 0.0;
   out_3189646925905620491[137] = 0.0;
   out_3189646925905620491[138] = 0.0;
   out_3189646925905620491[139] = 0.0;
   out_3189646925905620491[140] = 0.0;
   out_3189646925905620491[141] = 0.0;
   out_3189646925905620491[142] = 0.0;
   out_3189646925905620491[143] = 0.0;
   out_3189646925905620491[144] = 0.0;
   out_3189646925905620491[145] = 0.0;
   out_3189646925905620491[146] = 0.0;
   out_3189646925905620491[147] = 0.0;
   out_3189646925905620491[148] = 0.0;
   out_3189646925905620491[149] = 0.0;
   out_3189646925905620491[150] = 0.0;
   out_3189646925905620491[151] = 0.0;
   out_3189646925905620491[152] = 1.0;
   out_3189646925905620491[153] = 0.0;
   out_3189646925905620491[154] = 0.0;
   out_3189646925905620491[155] = 0.0;
   out_3189646925905620491[156] = 0.0;
   out_3189646925905620491[157] = 0.0;
   out_3189646925905620491[158] = 0.0;
   out_3189646925905620491[159] = 0.0;
   out_3189646925905620491[160] = 0.0;
   out_3189646925905620491[161] = 0.0;
   out_3189646925905620491[162] = 0.0;
   out_3189646925905620491[163] = 0.0;
   out_3189646925905620491[164] = 0.0;
   out_3189646925905620491[165] = 0.0;
   out_3189646925905620491[166] = 0.0;
   out_3189646925905620491[167] = 0.0;
   out_3189646925905620491[168] = 0.0;
   out_3189646925905620491[169] = 0.0;
   out_3189646925905620491[170] = 0.0;
   out_3189646925905620491[171] = 1.0;
   out_3189646925905620491[172] = 0.0;
   out_3189646925905620491[173] = 0.0;
   out_3189646925905620491[174] = 0.0;
   out_3189646925905620491[175] = 0.0;
   out_3189646925905620491[176] = 0.0;
   out_3189646925905620491[177] = 0.0;
   out_3189646925905620491[178] = 0.0;
   out_3189646925905620491[179] = 0.0;
   out_3189646925905620491[180] = 0.0;
   out_3189646925905620491[181] = 0.0;
   out_3189646925905620491[182] = 0.0;
   out_3189646925905620491[183] = 0.0;
   out_3189646925905620491[184] = 0.0;
   out_3189646925905620491[185] = 0.0;
   out_3189646925905620491[186] = 0.0;
   out_3189646925905620491[187] = 0.0;
   out_3189646925905620491[188] = 0.0;
   out_3189646925905620491[189] = 0.0;
   out_3189646925905620491[190] = 1.0;
   out_3189646925905620491[191] = 0.0;
   out_3189646925905620491[192] = 0.0;
   out_3189646925905620491[193] = 0.0;
   out_3189646925905620491[194] = 0.0;
   out_3189646925905620491[195] = 0.0;
   out_3189646925905620491[196] = 0.0;
   out_3189646925905620491[197] = 0.0;
   out_3189646925905620491[198] = 0.0;
   out_3189646925905620491[199] = 0.0;
   out_3189646925905620491[200] = 0.0;
   out_3189646925905620491[201] = 0.0;
   out_3189646925905620491[202] = 0.0;
   out_3189646925905620491[203] = 0.0;
   out_3189646925905620491[204] = 0.0;
   out_3189646925905620491[205] = 0.0;
   out_3189646925905620491[206] = 0.0;
   out_3189646925905620491[207] = 0.0;
   out_3189646925905620491[208] = 0.0;
   out_3189646925905620491[209] = 1.0;
   out_3189646925905620491[210] = 0.0;
   out_3189646925905620491[211] = 0.0;
   out_3189646925905620491[212] = 0.0;
   out_3189646925905620491[213] = 0.0;
   out_3189646925905620491[214] = 0.0;
   out_3189646925905620491[215] = 0.0;
   out_3189646925905620491[216] = 0.0;
   out_3189646925905620491[217] = 0.0;
   out_3189646925905620491[218] = 0.0;
   out_3189646925905620491[219] = 0.0;
   out_3189646925905620491[220] = 0.0;
   out_3189646925905620491[221] = 0.0;
   out_3189646925905620491[222] = 0.0;
   out_3189646925905620491[223] = 0.0;
   out_3189646925905620491[224] = 0.0;
   out_3189646925905620491[225] = 0.0;
   out_3189646925905620491[226] = 0.0;
   out_3189646925905620491[227] = 0.0;
   out_3189646925905620491[228] = 1.0;
   out_3189646925905620491[229] = 0.0;
   out_3189646925905620491[230] = 0.0;
   out_3189646925905620491[231] = 0.0;
   out_3189646925905620491[232] = 0.0;
   out_3189646925905620491[233] = 0.0;
   out_3189646925905620491[234] = 0.0;
   out_3189646925905620491[235] = 0.0;
   out_3189646925905620491[236] = 0.0;
   out_3189646925905620491[237] = 0.0;
   out_3189646925905620491[238] = 0.0;
   out_3189646925905620491[239] = 0.0;
   out_3189646925905620491[240] = 0.0;
   out_3189646925905620491[241] = 0.0;
   out_3189646925905620491[242] = 0.0;
   out_3189646925905620491[243] = 0.0;
   out_3189646925905620491[244] = 0.0;
   out_3189646925905620491[245] = 0.0;
   out_3189646925905620491[246] = 0.0;
   out_3189646925905620491[247] = 1.0;
   out_3189646925905620491[248] = 0.0;
   out_3189646925905620491[249] = 0.0;
   out_3189646925905620491[250] = 0.0;
   out_3189646925905620491[251] = 0.0;
   out_3189646925905620491[252] = 0.0;
   out_3189646925905620491[253] = 0.0;
   out_3189646925905620491[254] = 0.0;
   out_3189646925905620491[255] = 0.0;
   out_3189646925905620491[256] = 0.0;
   out_3189646925905620491[257] = 0.0;
   out_3189646925905620491[258] = 0.0;
   out_3189646925905620491[259] = 0.0;
   out_3189646925905620491[260] = 0.0;
   out_3189646925905620491[261] = 0.0;
   out_3189646925905620491[262] = 0.0;
   out_3189646925905620491[263] = 0.0;
   out_3189646925905620491[264] = 0.0;
   out_3189646925905620491[265] = 0.0;
   out_3189646925905620491[266] = 1.0;
   out_3189646925905620491[267] = 0.0;
   out_3189646925905620491[268] = 0.0;
   out_3189646925905620491[269] = 0.0;
   out_3189646925905620491[270] = 0.0;
   out_3189646925905620491[271] = 0.0;
   out_3189646925905620491[272] = 0.0;
   out_3189646925905620491[273] = 0.0;
   out_3189646925905620491[274] = 0.0;
   out_3189646925905620491[275] = 0.0;
   out_3189646925905620491[276] = 0.0;
   out_3189646925905620491[277] = 0.0;
   out_3189646925905620491[278] = 0.0;
   out_3189646925905620491[279] = 0.0;
   out_3189646925905620491[280] = 0.0;
   out_3189646925905620491[281] = 0.0;
   out_3189646925905620491[282] = 0.0;
   out_3189646925905620491[283] = 0.0;
   out_3189646925905620491[284] = 0.0;
   out_3189646925905620491[285] = 1.0;
   out_3189646925905620491[286] = 0.0;
   out_3189646925905620491[287] = 0.0;
   out_3189646925905620491[288] = 0.0;
   out_3189646925905620491[289] = 0.0;
   out_3189646925905620491[290] = 0.0;
   out_3189646925905620491[291] = 0.0;
   out_3189646925905620491[292] = 0.0;
   out_3189646925905620491[293] = 0.0;
   out_3189646925905620491[294] = 0.0;
   out_3189646925905620491[295] = 0.0;
   out_3189646925905620491[296] = 0.0;
   out_3189646925905620491[297] = 0.0;
   out_3189646925905620491[298] = 0.0;
   out_3189646925905620491[299] = 0.0;
   out_3189646925905620491[300] = 0.0;
   out_3189646925905620491[301] = 0.0;
   out_3189646925905620491[302] = 0.0;
   out_3189646925905620491[303] = 0.0;
   out_3189646925905620491[304] = 1.0;
   out_3189646925905620491[305] = 0.0;
   out_3189646925905620491[306] = 0.0;
   out_3189646925905620491[307] = 0.0;
   out_3189646925905620491[308] = 0.0;
   out_3189646925905620491[309] = 0.0;
   out_3189646925905620491[310] = 0.0;
   out_3189646925905620491[311] = 0.0;
   out_3189646925905620491[312] = 0.0;
   out_3189646925905620491[313] = 0.0;
   out_3189646925905620491[314] = 0.0;
   out_3189646925905620491[315] = 0.0;
   out_3189646925905620491[316] = 0.0;
   out_3189646925905620491[317] = 0.0;
   out_3189646925905620491[318] = 0.0;
   out_3189646925905620491[319] = 0.0;
   out_3189646925905620491[320] = 0.0;
   out_3189646925905620491[321] = 0.0;
   out_3189646925905620491[322] = 0.0;
   out_3189646925905620491[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_252565399931934628) {
   out_252565399931934628[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_252565399931934628[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_252565399931934628[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_252565399931934628[3] = dt*state[12] + state[3];
   out_252565399931934628[4] = dt*state[13] + state[4];
   out_252565399931934628[5] = dt*state[14] + state[5];
   out_252565399931934628[6] = state[6];
   out_252565399931934628[7] = state[7];
   out_252565399931934628[8] = state[8];
   out_252565399931934628[9] = state[9];
   out_252565399931934628[10] = state[10];
   out_252565399931934628[11] = state[11];
   out_252565399931934628[12] = state[12];
   out_252565399931934628[13] = state[13];
   out_252565399931934628[14] = state[14];
   out_252565399931934628[15] = state[15];
   out_252565399931934628[16] = state[16];
   out_252565399931934628[17] = state[17];
}
void F_fun(double *state, double dt, double *out_519143980273656889) {
   out_519143980273656889[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_519143980273656889[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_519143980273656889[2] = 0;
   out_519143980273656889[3] = 0;
   out_519143980273656889[4] = 0;
   out_519143980273656889[5] = 0;
   out_519143980273656889[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_519143980273656889[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_519143980273656889[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_519143980273656889[9] = 0;
   out_519143980273656889[10] = 0;
   out_519143980273656889[11] = 0;
   out_519143980273656889[12] = 0;
   out_519143980273656889[13] = 0;
   out_519143980273656889[14] = 0;
   out_519143980273656889[15] = 0;
   out_519143980273656889[16] = 0;
   out_519143980273656889[17] = 0;
   out_519143980273656889[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_519143980273656889[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_519143980273656889[20] = 0;
   out_519143980273656889[21] = 0;
   out_519143980273656889[22] = 0;
   out_519143980273656889[23] = 0;
   out_519143980273656889[24] = 0;
   out_519143980273656889[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_519143980273656889[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_519143980273656889[27] = 0;
   out_519143980273656889[28] = 0;
   out_519143980273656889[29] = 0;
   out_519143980273656889[30] = 0;
   out_519143980273656889[31] = 0;
   out_519143980273656889[32] = 0;
   out_519143980273656889[33] = 0;
   out_519143980273656889[34] = 0;
   out_519143980273656889[35] = 0;
   out_519143980273656889[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_519143980273656889[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_519143980273656889[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_519143980273656889[39] = 0;
   out_519143980273656889[40] = 0;
   out_519143980273656889[41] = 0;
   out_519143980273656889[42] = 0;
   out_519143980273656889[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_519143980273656889[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_519143980273656889[45] = 0;
   out_519143980273656889[46] = 0;
   out_519143980273656889[47] = 0;
   out_519143980273656889[48] = 0;
   out_519143980273656889[49] = 0;
   out_519143980273656889[50] = 0;
   out_519143980273656889[51] = 0;
   out_519143980273656889[52] = 0;
   out_519143980273656889[53] = 0;
   out_519143980273656889[54] = 0;
   out_519143980273656889[55] = 0;
   out_519143980273656889[56] = 0;
   out_519143980273656889[57] = 1;
   out_519143980273656889[58] = 0;
   out_519143980273656889[59] = 0;
   out_519143980273656889[60] = 0;
   out_519143980273656889[61] = 0;
   out_519143980273656889[62] = 0;
   out_519143980273656889[63] = 0;
   out_519143980273656889[64] = 0;
   out_519143980273656889[65] = 0;
   out_519143980273656889[66] = dt;
   out_519143980273656889[67] = 0;
   out_519143980273656889[68] = 0;
   out_519143980273656889[69] = 0;
   out_519143980273656889[70] = 0;
   out_519143980273656889[71] = 0;
   out_519143980273656889[72] = 0;
   out_519143980273656889[73] = 0;
   out_519143980273656889[74] = 0;
   out_519143980273656889[75] = 0;
   out_519143980273656889[76] = 1;
   out_519143980273656889[77] = 0;
   out_519143980273656889[78] = 0;
   out_519143980273656889[79] = 0;
   out_519143980273656889[80] = 0;
   out_519143980273656889[81] = 0;
   out_519143980273656889[82] = 0;
   out_519143980273656889[83] = 0;
   out_519143980273656889[84] = 0;
   out_519143980273656889[85] = dt;
   out_519143980273656889[86] = 0;
   out_519143980273656889[87] = 0;
   out_519143980273656889[88] = 0;
   out_519143980273656889[89] = 0;
   out_519143980273656889[90] = 0;
   out_519143980273656889[91] = 0;
   out_519143980273656889[92] = 0;
   out_519143980273656889[93] = 0;
   out_519143980273656889[94] = 0;
   out_519143980273656889[95] = 1;
   out_519143980273656889[96] = 0;
   out_519143980273656889[97] = 0;
   out_519143980273656889[98] = 0;
   out_519143980273656889[99] = 0;
   out_519143980273656889[100] = 0;
   out_519143980273656889[101] = 0;
   out_519143980273656889[102] = 0;
   out_519143980273656889[103] = 0;
   out_519143980273656889[104] = dt;
   out_519143980273656889[105] = 0;
   out_519143980273656889[106] = 0;
   out_519143980273656889[107] = 0;
   out_519143980273656889[108] = 0;
   out_519143980273656889[109] = 0;
   out_519143980273656889[110] = 0;
   out_519143980273656889[111] = 0;
   out_519143980273656889[112] = 0;
   out_519143980273656889[113] = 0;
   out_519143980273656889[114] = 1;
   out_519143980273656889[115] = 0;
   out_519143980273656889[116] = 0;
   out_519143980273656889[117] = 0;
   out_519143980273656889[118] = 0;
   out_519143980273656889[119] = 0;
   out_519143980273656889[120] = 0;
   out_519143980273656889[121] = 0;
   out_519143980273656889[122] = 0;
   out_519143980273656889[123] = 0;
   out_519143980273656889[124] = 0;
   out_519143980273656889[125] = 0;
   out_519143980273656889[126] = 0;
   out_519143980273656889[127] = 0;
   out_519143980273656889[128] = 0;
   out_519143980273656889[129] = 0;
   out_519143980273656889[130] = 0;
   out_519143980273656889[131] = 0;
   out_519143980273656889[132] = 0;
   out_519143980273656889[133] = 1;
   out_519143980273656889[134] = 0;
   out_519143980273656889[135] = 0;
   out_519143980273656889[136] = 0;
   out_519143980273656889[137] = 0;
   out_519143980273656889[138] = 0;
   out_519143980273656889[139] = 0;
   out_519143980273656889[140] = 0;
   out_519143980273656889[141] = 0;
   out_519143980273656889[142] = 0;
   out_519143980273656889[143] = 0;
   out_519143980273656889[144] = 0;
   out_519143980273656889[145] = 0;
   out_519143980273656889[146] = 0;
   out_519143980273656889[147] = 0;
   out_519143980273656889[148] = 0;
   out_519143980273656889[149] = 0;
   out_519143980273656889[150] = 0;
   out_519143980273656889[151] = 0;
   out_519143980273656889[152] = 1;
   out_519143980273656889[153] = 0;
   out_519143980273656889[154] = 0;
   out_519143980273656889[155] = 0;
   out_519143980273656889[156] = 0;
   out_519143980273656889[157] = 0;
   out_519143980273656889[158] = 0;
   out_519143980273656889[159] = 0;
   out_519143980273656889[160] = 0;
   out_519143980273656889[161] = 0;
   out_519143980273656889[162] = 0;
   out_519143980273656889[163] = 0;
   out_519143980273656889[164] = 0;
   out_519143980273656889[165] = 0;
   out_519143980273656889[166] = 0;
   out_519143980273656889[167] = 0;
   out_519143980273656889[168] = 0;
   out_519143980273656889[169] = 0;
   out_519143980273656889[170] = 0;
   out_519143980273656889[171] = 1;
   out_519143980273656889[172] = 0;
   out_519143980273656889[173] = 0;
   out_519143980273656889[174] = 0;
   out_519143980273656889[175] = 0;
   out_519143980273656889[176] = 0;
   out_519143980273656889[177] = 0;
   out_519143980273656889[178] = 0;
   out_519143980273656889[179] = 0;
   out_519143980273656889[180] = 0;
   out_519143980273656889[181] = 0;
   out_519143980273656889[182] = 0;
   out_519143980273656889[183] = 0;
   out_519143980273656889[184] = 0;
   out_519143980273656889[185] = 0;
   out_519143980273656889[186] = 0;
   out_519143980273656889[187] = 0;
   out_519143980273656889[188] = 0;
   out_519143980273656889[189] = 0;
   out_519143980273656889[190] = 1;
   out_519143980273656889[191] = 0;
   out_519143980273656889[192] = 0;
   out_519143980273656889[193] = 0;
   out_519143980273656889[194] = 0;
   out_519143980273656889[195] = 0;
   out_519143980273656889[196] = 0;
   out_519143980273656889[197] = 0;
   out_519143980273656889[198] = 0;
   out_519143980273656889[199] = 0;
   out_519143980273656889[200] = 0;
   out_519143980273656889[201] = 0;
   out_519143980273656889[202] = 0;
   out_519143980273656889[203] = 0;
   out_519143980273656889[204] = 0;
   out_519143980273656889[205] = 0;
   out_519143980273656889[206] = 0;
   out_519143980273656889[207] = 0;
   out_519143980273656889[208] = 0;
   out_519143980273656889[209] = 1;
   out_519143980273656889[210] = 0;
   out_519143980273656889[211] = 0;
   out_519143980273656889[212] = 0;
   out_519143980273656889[213] = 0;
   out_519143980273656889[214] = 0;
   out_519143980273656889[215] = 0;
   out_519143980273656889[216] = 0;
   out_519143980273656889[217] = 0;
   out_519143980273656889[218] = 0;
   out_519143980273656889[219] = 0;
   out_519143980273656889[220] = 0;
   out_519143980273656889[221] = 0;
   out_519143980273656889[222] = 0;
   out_519143980273656889[223] = 0;
   out_519143980273656889[224] = 0;
   out_519143980273656889[225] = 0;
   out_519143980273656889[226] = 0;
   out_519143980273656889[227] = 0;
   out_519143980273656889[228] = 1;
   out_519143980273656889[229] = 0;
   out_519143980273656889[230] = 0;
   out_519143980273656889[231] = 0;
   out_519143980273656889[232] = 0;
   out_519143980273656889[233] = 0;
   out_519143980273656889[234] = 0;
   out_519143980273656889[235] = 0;
   out_519143980273656889[236] = 0;
   out_519143980273656889[237] = 0;
   out_519143980273656889[238] = 0;
   out_519143980273656889[239] = 0;
   out_519143980273656889[240] = 0;
   out_519143980273656889[241] = 0;
   out_519143980273656889[242] = 0;
   out_519143980273656889[243] = 0;
   out_519143980273656889[244] = 0;
   out_519143980273656889[245] = 0;
   out_519143980273656889[246] = 0;
   out_519143980273656889[247] = 1;
   out_519143980273656889[248] = 0;
   out_519143980273656889[249] = 0;
   out_519143980273656889[250] = 0;
   out_519143980273656889[251] = 0;
   out_519143980273656889[252] = 0;
   out_519143980273656889[253] = 0;
   out_519143980273656889[254] = 0;
   out_519143980273656889[255] = 0;
   out_519143980273656889[256] = 0;
   out_519143980273656889[257] = 0;
   out_519143980273656889[258] = 0;
   out_519143980273656889[259] = 0;
   out_519143980273656889[260] = 0;
   out_519143980273656889[261] = 0;
   out_519143980273656889[262] = 0;
   out_519143980273656889[263] = 0;
   out_519143980273656889[264] = 0;
   out_519143980273656889[265] = 0;
   out_519143980273656889[266] = 1;
   out_519143980273656889[267] = 0;
   out_519143980273656889[268] = 0;
   out_519143980273656889[269] = 0;
   out_519143980273656889[270] = 0;
   out_519143980273656889[271] = 0;
   out_519143980273656889[272] = 0;
   out_519143980273656889[273] = 0;
   out_519143980273656889[274] = 0;
   out_519143980273656889[275] = 0;
   out_519143980273656889[276] = 0;
   out_519143980273656889[277] = 0;
   out_519143980273656889[278] = 0;
   out_519143980273656889[279] = 0;
   out_519143980273656889[280] = 0;
   out_519143980273656889[281] = 0;
   out_519143980273656889[282] = 0;
   out_519143980273656889[283] = 0;
   out_519143980273656889[284] = 0;
   out_519143980273656889[285] = 1;
   out_519143980273656889[286] = 0;
   out_519143980273656889[287] = 0;
   out_519143980273656889[288] = 0;
   out_519143980273656889[289] = 0;
   out_519143980273656889[290] = 0;
   out_519143980273656889[291] = 0;
   out_519143980273656889[292] = 0;
   out_519143980273656889[293] = 0;
   out_519143980273656889[294] = 0;
   out_519143980273656889[295] = 0;
   out_519143980273656889[296] = 0;
   out_519143980273656889[297] = 0;
   out_519143980273656889[298] = 0;
   out_519143980273656889[299] = 0;
   out_519143980273656889[300] = 0;
   out_519143980273656889[301] = 0;
   out_519143980273656889[302] = 0;
   out_519143980273656889[303] = 0;
   out_519143980273656889[304] = 1;
   out_519143980273656889[305] = 0;
   out_519143980273656889[306] = 0;
   out_519143980273656889[307] = 0;
   out_519143980273656889[308] = 0;
   out_519143980273656889[309] = 0;
   out_519143980273656889[310] = 0;
   out_519143980273656889[311] = 0;
   out_519143980273656889[312] = 0;
   out_519143980273656889[313] = 0;
   out_519143980273656889[314] = 0;
   out_519143980273656889[315] = 0;
   out_519143980273656889[316] = 0;
   out_519143980273656889[317] = 0;
   out_519143980273656889[318] = 0;
   out_519143980273656889[319] = 0;
   out_519143980273656889[320] = 0;
   out_519143980273656889[321] = 0;
   out_519143980273656889[322] = 0;
   out_519143980273656889[323] = 1;
}
void h_4(double *state, double *unused, double *out_2972557042417062016) {
   out_2972557042417062016[0] = state[6] + state[9];
   out_2972557042417062016[1] = state[7] + state[10];
   out_2972557042417062016[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6463869004696569744) {
   out_6463869004696569744[0] = 0;
   out_6463869004696569744[1] = 0;
   out_6463869004696569744[2] = 0;
   out_6463869004696569744[3] = 0;
   out_6463869004696569744[4] = 0;
   out_6463869004696569744[5] = 0;
   out_6463869004696569744[6] = 1;
   out_6463869004696569744[7] = 0;
   out_6463869004696569744[8] = 0;
   out_6463869004696569744[9] = 1;
   out_6463869004696569744[10] = 0;
   out_6463869004696569744[11] = 0;
   out_6463869004696569744[12] = 0;
   out_6463869004696569744[13] = 0;
   out_6463869004696569744[14] = 0;
   out_6463869004696569744[15] = 0;
   out_6463869004696569744[16] = 0;
   out_6463869004696569744[17] = 0;
   out_6463869004696569744[18] = 0;
   out_6463869004696569744[19] = 0;
   out_6463869004696569744[20] = 0;
   out_6463869004696569744[21] = 0;
   out_6463869004696569744[22] = 0;
   out_6463869004696569744[23] = 0;
   out_6463869004696569744[24] = 0;
   out_6463869004696569744[25] = 1;
   out_6463869004696569744[26] = 0;
   out_6463869004696569744[27] = 0;
   out_6463869004696569744[28] = 1;
   out_6463869004696569744[29] = 0;
   out_6463869004696569744[30] = 0;
   out_6463869004696569744[31] = 0;
   out_6463869004696569744[32] = 0;
   out_6463869004696569744[33] = 0;
   out_6463869004696569744[34] = 0;
   out_6463869004696569744[35] = 0;
   out_6463869004696569744[36] = 0;
   out_6463869004696569744[37] = 0;
   out_6463869004696569744[38] = 0;
   out_6463869004696569744[39] = 0;
   out_6463869004696569744[40] = 0;
   out_6463869004696569744[41] = 0;
   out_6463869004696569744[42] = 0;
   out_6463869004696569744[43] = 0;
   out_6463869004696569744[44] = 1;
   out_6463869004696569744[45] = 0;
   out_6463869004696569744[46] = 0;
   out_6463869004696569744[47] = 1;
   out_6463869004696569744[48] = 0;
   out_6463869004696569744[49] = 0;
   out_6463869004696569744[50] = 0;
   out_6463869004696569744[51] = 0;
   out_6463869004696569744[52] = 0;
   out_6463869004696569744[53] = 0;
}
void h_10(double *state, double *unused, double *out_6282181365633460772) {
   out_6282181365633460772[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6282181365633460772[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6282181365633460772[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8114151188329229777) {
   out_8114151188329229777[0] = 0;
   out_8114151188329229777[1] = 9.8100000000000005*cos(state[1]);
   out_8114151188329229777[2] = 0;
   out_8114151188329229777[3] = 0;
   out_8114151188329229777[4] = -state[8];
   out_8114151188329229777[5] = state[7];
   out_8114151188329229777[6] = 0;
   out_8114151188329229777[7] = state[5];
   out_8114151188329229777[8] = -state[4];
   out_8114151188329229777[9] = 0;
   out_8114151188329229777[10] = 0;
   out_8114151188329229777[11] = 0;
   out_8114151188329229777[12] = 1;
   out_8114151188329229777[13] = 0;
   out_8114151188329229777[14] = 0;
   out_8114151188329229777[15] = 1;
   out_8114151188329229777[16] = 0;
   out_8114151188329229777[17] = 0;
   out_8114151188329229777[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8114151188329229777[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8114151188329229777[20] = 0;
   out_8114151188329229777[21] = state[8];
   out_8114151188329229777[22] = 0;
   out_8114151188329229777[23] = -state[6];
   out_8114151188329229777[24] = -state[5];
   out_8114151188329229777[25] = 0;
   out_8114151188329229777[26] = state[3];
   out_8114151188329229777[27] = 0;
   out_8114151188329229777[28] = 0;
   out_8114151188329229777[29] = 0;
   out_8114151188329229777[30] = 0;
   out_8114151188329229777[31] = 1;
   out_8114151188329229777[32] = 0;
   out_8114151188329229777[33] = 0;
   out_8114151188329229777[34] = 1;
   out_8114151188329229777[35] = 0;
   out_8114151188329229777[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8114151188329229777[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8114151188329229777[38] = 0;
   out_8114151188329229777[39] = -state[7];
   out_8114151188329229777[40] = state[6];
   out_8114151188329229777[41] = 0;
   out_8114151188329229777[42] = state[4];
   out_8114151188329229777[43] = -state[3];
   out_8114151188329229777[44] = 0;
   out_8114151188329229777[45] = 0;
   out_8114151188329229777[46] = 0;
   out_8114151188329229777[47] = 0;
   out_8114151188329229777[48] = 0;
   out_8114151188329229777[49] = 0;
   out_8114151188329229777[50] = 1;
   out_8114151188329229777[51] = 0;
   out_8114151188329229777[52] = 0;
   out_8114151188329229777[53] = 1;
}
void h_13(double *state, double *unused, double *out_3807456519538966309) {
   out_3807456519538966309[0] = state[3];
   out_3807456519538966309[1] = state[4];
   out_3807456519538966309[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3251595179364236943) {
   out_3251595179364236943[0] = 0;
   out_3251595179364236943[1] = 0;
   out_3251595179364236943[2] = 0;
   out_3251595179364236943[3] = 1;
   out_3251595179364236943[4] = 0;
   out_3251595179364236943[5] = 0;
   out_3251595179364236943[6] = 0;
   out_3251595179364236943[7] = 0;
   out_3251595179364236943[8] = 0;
   out_3251595179364236943[9] = 0;
   out_3251595179364236943[10] = 0;
   out_3251595179364236943[11] = 0;
   out_3251595179364236943[12] = 0;
   out_3251595179364236943[13] = 0;
   out_3251595179364236943[14] = 0;
   out_3251595179364236943[15] = 0;
   out_3251595179364236943[16] = 0;
   out_3251595179364236943[17] = 0;
   out_3251595179364236943[18] = 0;
   out_3251595179364236943[19] = 0;
   out_3251595179364236943[20] = 0;
   out_3251595179364236943[21] = 0;
   out_3251595179364236943[22] = 1;
   out_3251595179364236943[23] = 0;
   out_3251595179364236943[24] = 0;
   out_3251595179364236943[25] = 0;
   out_3251595179364236943[26] = 0;
   out_3251595179364236943[27] = 0;
   out_3251595179364236943[28] = 0;
   out_3251595179364236943[29] = 0;
   out_3251595179364236943[30] = 0;
   out_3251595179364236943[31] = 0;
   out_3251595179364236943[32] = 0;
   out_3251595179364236943[33] = 0;
   out_3251595179364236943[34] = 0;
   out_3251595179364236943[35] = 0;
   out_3251595179364236943[36] = 0;
   out_3251595179364236943[37] = 0;
   out_3251595179364236943[38] = 0;
   out_3251595179364236943[39] = 0;
   out_3251595179364236943[40] = 0;
   out_3251595179364236943[41] = 1;
   out_3251595179364236943[42] = 0;
   out_3251595179364236943[43] = 0;
   out_3251595179364236943[44] = 0;
   out_3251595179364236943[45] = 0;
   out_3251595179364236943[46] = 0;
   out_3251595179364236943[47] = 0;
   out_3251595179364236943[48] = 0;
   out_3251595179364236943[49] = 0;
   out_3251595179364236943[50] = 0;
   out_3251595179364236943[51] = 0;
   out_3251595179364236943[52] = 0;
   out_3251595179364236943[53] = 0;
}
void h_14(double *state, double *unused, double *out_2724310507005535047) {
   out_2724310507005535047[0] = state[6];
   out_2724310507005535047[1] = state[7];
   out_2724310507005535047[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2500628148357085215) {
   out_2500628148357085215[0] = 0;
   out_2500628148357085215[1] = 0;
   out_2500628148357085215[2] = 0;
   out_2500628148357085215[3] = 0;
   out_2500628148357085215[4] = 0;
   out_2500628148357085215[5] = 0;
   out_2500628148357085215[6] = 1;
   out_2500628148357085215[7] = 0;
   out_2500628148357085215[8] = 0;
   out_2500628148357085215[9] = 0;
   out_2500628148357085215[10] = 0;
   out_2500628148357085215[11] = 0;
   out_2500628148357085215[12] = 0;
   out_2500628148357085215[13] = 0;
   out_2500628148357085215[14] = 0;
   out_2500628148357085215[15] = 0;
   out_2500628148357085215[16] = 0;
   out_2500628148357085215[17] = 0;
   out_2500628148357085215[18] = 0;
   out_2500628148357085215[19] = 0;
   out_2500628148357085215[20] = 0;
   out_2500628148357085215[21] = 0;
   out_2500628148357085215[22] = 0;
   out_2500628148357085215[23] = 0;
   out_2500628148357085215[24] = 0;
   out_2500628148357085215[25] = 1;
   out_2500628148357085215[26] = 0;
   out_2500628148357085215[27] = 0;
   out_2500628148357085215[28] = 0;
   out_2500628148357085215[29] = 0;
   out_2500628148357085215[30] = 0;
   out_2500628148357085215[31] = 0;
   out_2500628148357085215[32] = 0;
   out_2500628148357085215[33] = 0;
   out_2500628148357085215[34] = 0;
   out_2500628148357085215[35] = 0;
   out_2500628148357085215[36] = 0;
   out_2500628148357085215[37] = 0;
   out_2500628148357085215[38] = 0;
   out_2500628148357085215[39] = 0;
   out_2500628148357085215[40] = 0;
   out_2500628148357085215[41] = 0;
   out_2500628148357085215[42] = 0;
   out_2500628148357085215[43] = 0;
   out_2500628148357085215[44] = 1;
   out_2500628148357085215[45] = 0;
   out_2500628148357085215[46] = 0;
   out_2500628148357085215[47] = 0;
   out_2500628148357085215[48] = 0;
   out_2500628148357085215[49] = 0;
   out_2500628148357085215[50] = 0;
   out_2500628148357085215[51] = 0;
   out_2500628148357085215[52] = 0;
   out_2500628148357085215[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8200257521780243420) {
  err_fun(nom_x, delta_x, out_8200257521780243420);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3514907883279273646) {
  inv_err_fun(nom_x, true_x, out_3514907883279273646);
}
void pose_H_mod_fun(double *state, double *out_3189646925905620491) {
  H_mod_fun(state, out_3189646925905620491);
}
void pose_f_fun(double *state, double dt, double *out_252565399931934628) {
  f_fun(state,  dt, out_252565399931934628);
}
void pose_F_fun(double *state, double dt, double *out_519143980273656889) {
  F_fun(state,  dt, out_519143980273656889);
}
void pose_h_4(double *state, double *unused, double *out_2972557042417062016) {
  h_4(state, unused, out_2972557042417062016);
}
void pose_H_4(double *state, double *unused, double *out_6463869004696569744) {
  H_4(state, unused, out_6463869004696569744);
}
void pose_h_10(double *state, double *unused, double *out_6282181365633460772) {
  h_10(state, unused, out_6282181365633460772);
}
void pose_H_10(double *state, double *unused, double *out_8114151188329229777) {
  H_10(state, unused, out_8114151188329229777);
}
void pose_h_13(double *state, double *unused, double *out_3807456519538966309) {
  h_13(state, unused, out_3807456519538966309);
}
void pose_H_13(double *state, double *unused, double *out_3251595179364236943) {
  H_13(state, unused, out_3251595179364236943);
}
void pose_h_14(double *state, double *unused, double *out_2724310507005535047) {
  h_14(state, unused, out_2724310507005535047);
}
void pose_H_14(double *state, double *unused, double *out_2500628148357085215) {
  H_14(state, unused, out_2500628148357085215);
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
