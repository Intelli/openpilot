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
void err_fun(double *nom_x, double *delta_x, double *out_4256674648376746002) {
   out_4256674648376746002[0] = delta_x[0] + nom_x[0];
   out_4256674648376746002[1] = delta_x[1] + nom_x[1];
   out_4256674648376746002[2] = delta_x[2] + nom_x[2];
   out_4256674648376746002[3] = delta_x[3] + nom_x[3];
   out_4256674648376746002[4] = delta_x[4] + nom_x[4];
   out_4256674648376746002[5] = delta_x[5] + nom_x[5];
   out_4256674648376746002[6] = delta_x[6] + nom_x[6];
   out_4256674648376746002[7] = delta_x[7] + nom_x[7];
   out_4256674648376746002[8] = delta_x[8] + nom_x[8];
   out_4256674648376746002[9] = delta_x[9] + nom_x[9];
   out_4256674648376746002[10] = delta_x[10] + nom_x[10];
   out_4256674648376746002[11] = delta_x[11] + nom_x[11];
   out_4256674648376746002[12] = delta_x[12] + nom_x[12];
   out_4256674648376746002[13] = delta_x[13] + nom_x[13];
   out_4256674648376746002[14] = delta_x[14] + nom_x[14];
   out_4256674648376746002[15] = delta_x[15] + nom_x[15];
   out_4256674648376746002[16] = delta_x[16] + nom_x[16];
   out_4256674648376746002[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6072215117786325780) {
   out_6072215117786325780[0] = -nom_x[0] + true_x[0];
   out_6072215117786325780[1] = -nom_x[1] + true_x[1];
   out_6072215117786325780[2] = -nom_x[2] + true_x[2];
   out_6072215117786325780[3] = -nom_x[3] + true_x[3];
   out_6072215117786325780[4] = -nom_x[4] + true_x[4];
   out_6072215117786325780[5] = -nom_x[5] + true_x[5];
   out_6072215117786325780[6] = -nom_x[6] + true_x[6];
   out_6072215117786325780[7] = -nom_x[7] + true_x[7];
   out_6072215117786325780[8] = -nom_x[8] + true_x[8];
   out_6072215117786325780[9] = -nom_x[9] + true_x[9];
   out_6072215117786325780[10] = -nom_x[10] + true_x[10];
   out_6072215117786325780[11] = -nom_x[11] + true_x[11];
   out_6072215117786325780[12] = -nom_x[12] + true_x[12];
   out_6072215117786325780[13] = -nom_x[13] + true_x[13];
   out_6072215117786325780[14] = -nom_x[14] + true_x[14];
   out_6072215117786325780[15] = -nom_x[15] + true_x[15];
   out_6072215117786325780[16] = -nom_x[16] + true_x[16];
   out_6072215117786325780[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8723676235799255586) {
   out_8723676235799255586[0] = 1.0;
   out_8723676235799255586[1] = 0.0;
   out_8723676235799255586[2] = 0.0;
   out_8723676235799255586[3] = 0.0;
   out_8723676235799255586[4] = 0.0;
   out_8723676235799255586[5] = 0.0;
   out_8723676235799255586[6] = 0.0;
   out_8723676235799255586[7] = 0.0;
   out_8723676235799255586[8] = 0.0;
   out_8723676235799255586[9] = 0.0;
   out_8723676235799255586[10] = 0.0;
   out_8723676235799255586[11] = 0.0;
   out_8723676235799255586[12] = 0.0;
   out_8723676235799255586[13] = 0.0;
   out_8723676235799255586[14] = 0.0;
   out_8723676235799255586[15] = 0.0;
   out_8723676235799255586[16] = 0.0;
   out_8723676235799255586[17] = 0.0;
   out_8723676235799255586[18] = 0.0;
   out_8723676235799255586[19] = 1.0;
   out_8723676235799255586[20] = 0.0;
   out_8723676235799255586[21] = 0.0;
   out_8723676235799255586[22] = 0.0;
   out_8723676235799255586[23] = 0.0;
   out_8723676235799255586[24] = 0.0;
   out_8723676235799255586[25] = 0.0;
   out_8723676235799255586[26] = 0.0;
   out_8723676235799255586[27] = 0.0;
   out_8723676235799255586[28] = 0.0;
   out_8723676235799255586[29] = 0.0;
   out_8723676235799255586[30] = 0.0;
   out_8723676235799255586[31] = 0.0;
   out_8723676235799255586[32] = 0.0;
   out_8723676235799255586[33] = 0.0;
   out_8723676235799255586[34] = 0.0;
   out_8723676235799255586[35] = 0.0;
   out_8723676235799255586[36] = 0.0;
   out_8723676235799255586[37] = 0.0;
   out_8723676235799255586[38] = 1.0;
   out_8723676235799255586[39] = 0.0;
   out_8723676235799255586[40] = 0.0;
   out_8723676235799255586[41] = 0.0;
   out_8723676235799255586[42] = 0.0;
   out_8723676235799255586[43] = 0.0;
   out_8723676235799255586[44] = 0.0;
   out_8723676235799255586[45] = 0.0;
   out_8723676235799255586[46] = 0.0;
   out_8723676235799255586[47] = 0.0;
   out_8723676235799255586[48] = 0.0;
   out_8723676235799255586[49] = 0.0;
   out_8723676235799255586[50] = 0.0;
   out_8723676235799255586[51] = 0.0;
   out_8723676235799255586[52] = 0.0;
   out_8723676235799255586[53] = 0.0;
   out_8723676235799255586[54] = 0.0;
   out_8723676235799255586[55] = 0.0;
   out_8723676235799255586[56] = 0.0;
   out_8723676235799255586[57] = 1.0;
   out_8723676235799255586[58] = 0.0;
   out_8723676235799255586[59] = 0.0;
   out_8723676235799255586[60] = 0.0;
   out_8723676235799255586[61] = 0.0;
   out_8723676235799255586[62] = 0.0;
   out_8723676235799255586[63] = 0.0;
   out_8723676235799255586[64] = 0.0;
   out_8723676235799255586[65] = 0.0;
   out_8723676235799255586[66] = 0.0;
   out_8723676235799255586[67] = 0.0;
   out_8723676235799255586[68] = 0.0;
   out_8723676235799255586[69] = 0.0;
   out_8723676235799255586[70] = 0.0;
   out_8723676235799255586[71] = 0.0;
   out_8723676235799255586[72] = 0.0;
   out_8723676235799255586[73] = 0.0;
   out_8723676235799255586[74] = 0.0;
   out_8723676235799255586[75] = 0.0;
   out_8723676235799255586[76] = 1.0;
   out_8723676235799255586[77] = 0.0;
   out_8723676235799255586[78] = 0.0;
   out_8723676235799255586[79] = 0.0;
   out_8723676235799255586[80] = 0.0;
   out_8723676235799255586[81] = 0.0;
   out_8723676235799255586[82] = 0.0;
   out_8723676235799255586[83] = 0.0;
   out_8723676235799255586[84] = 0.0;
   out_8723676235799255586[85] = 0.0;
   out_8723676235799255586[86] = 0.0;
   out_8723676235799255586[87] = 0.0;
   out_8723676235799255586[88] = 0.0;
   out_8723676235799255586[89] = 0.0;
   out_8723676235799255586[90] = 0.0;
   out_8723676235799255586[91] = 0.0;
   out_8723676235799255586[92] = 0.0;
   out_8723676235799255586[93] = 0.0;
   out_8723676235799255586[94] = 0.0;
   out_8723676235799255586[95] = 1.0;
   out_8723676235799255586[96] = 0.0;
   out_8723676235799255586[97] = 0.0;
   out_8723676235799255586[98] = 0.0;
   out_8723676235799255586[99] = 0.0;
   out_8723676235799255586[100] = 0.0;
   out_8723676235799255586[101] = 0.0;
   out_8723676235799255586[102] = 0.0;
   out_8723676235799255586[103] = 0.0;
   out_8723676235799255586[104] = 0.0;
   out_8723676235799255586[105] = 0.0;
   out_8723676235799255586[106] = 0.0;
   out_8723676235799255586[107] = 0.0;
   out_8723676235799255586[108] = 0.0;
   out_8723676235799255586[109] = 0.0;
   out_8723676235799255586[110] = 0.0;
   out_8723676235799255586[111] = 0.0;
   out_8723676235799255586[112] = 0.0;
   out_8723676235799255586[113] = 0.0;
   out_8723676235799255586[114] = 1.0;
   out_8723676235799255586[115] = 0.0;
   out_8723676235799255586[116] = 0.0;
   out_8723676235799255586[117] = 0.0;
   out_8723676235799255586[118] = 0.0;
   out_8723676235799255586[119] = 0.0;
   out_8723676235799255586[120] = 0.0;
   out_8723676235799255586[121] = 0.0;
   out_8723676235799255586[122] = 0.0;
   out_8723676235799255586[123] = 0.0;
   out_8723676235799255586[124] = 0.0;
   out_8723676235799255586[125] = 0.0;
   out_8723676235799255586[126] = 0.0;
   out_8723676235799255586[127] = 0.0;
   out_8723676235799255586[128] = 0.0;
   out_8723676235799255586[129] = 0.0;
   out_8723676235799255586[130] = 0.0;
   out_8723676235799255586[131] = 0.0;
   out_8723676235799255586[132] = 0.0;
   out_8723676235799255586[133] = 1.0;
   out_8723676235799255586[134] = 0.0;
   out_8723676235799255586[135] = 0.0;
   out_8723676235799255586[136] = 0.0;
   out_8723676235799255586[137] = 0.0;
   out_8723676235799255586[138] = 0.0;
   out_8723676235799255586[139] = 0.0;
   out_8723676235799255586[140] = 0.0;
   out_8723676235799255586[141] = 0.0;
   out_8723676235799255586[142] = 0.0;
   out_8723676235799255586[143] = 0.0;
   out_8723676235799255586[144] = 0.0;
   out_8723676235799255586[145] = 0.0;
   out_8723676235799255586[146] = 0.0;
   out_8723676235799255586[147] = 0.0;
   out_8723676235799255586[148] = 0.0;
   out_8723676235799255586[149] = 0.0;
   out_8723676235799255586[150] = 0.0;
   out_8723676235799255586[151] = 0.0;
   out_8723676235799255586[152] = 1.0;
   out_8723676235799255586[153] = 0.0;
   out_8723676235799255586[154] = 0.0;
   out_8723676235799255586[155] = 0.0;
   out_8723676235799255586[156] = 0.0;
   out_8723676235799255586[157] = 0.0;
   out_8723676235799255586[158] = 0.0;
   out_8723676235799255586[159] = 0.0;
   out_8723676235799255586[160] = 0.0;
   out_8723676235799255586[161] = 0.0;
   out_8723676235799255586[162] = 0.0;
   out_8723676235799255586[163] = 0.0;
   out_8723676235799255586[164] = 0.0;
   out_8723676235799255586[165] = 0.0;
   out_8723676235799255586[166] = 0.0;
   out_8723676235799255586[167] = 0.0;
   out_8723676235799255586[168] = 0.0;
   out_8723676235799255586[169] = 0.0;
   out_8723676235799255586[170] = 0.0;
   out_8723676235799255586[171] = 1.0;
   out_8723676235799255586[172] = 0.0;
   out_8723676235799255586[173] = 0.0;
   out_8723676235799255586[174] = 0.0;
   out_8723676235799255586[175] = 0.0;
   out_8723676235799255586[176] = 0.0;
   out_8723676235799255586[177] = 0.0;
   out_8723676235799255586[178] = 0.0;
   out_8723676235799255586[179] = 0.0;
   out_8723676235799255586[180] = 0.0;
   out_8723676235799255586[181] = 0.0;
   out_8723676235799255586[182] = 0.0;
   out_8723676235799255586[183] = 0.0;
   out_8723676235799255586[184] = 0.0;
   out_8723676235799255586[185] = 0.0;
   out_8723676235799255586[186] = 0.0;
   out_8723676235799255586[187] = 0.0;
   out_8723676235799255586[188] = 0.0;
   out_8723676235799255586[189] = 0.0;
   out_8723676235799255586[190] = 1.0;
   out_8723676235799255586[191] = 0.0;
   out_8723676235799255586[192] = 0.0;
   out_8723676235799255586[193] = 0.0;
   out_8723676235799255586[194] = 0.0;
   out_8723676235799255586[195] = 0.0;
   out_8723676235799255586[196] = 0.0;
   out_8723676235799255586[197] = 0.0;
   out_8723676235799255586[198] = 0.0;
   out_8723676235799255586[199] = 0.0;
   out_8723676235799255586[200] = 0.0;
   out_8723676235799255586[201] = 0.0;
   out_8723676235799255586[202] = 0.0;
   out_8723676235799255586[203] = 0.0;
   out_8723676235799255586[204] = 0.0;
   out_8723676235799255586[205] = 0.0;
   out_8723676235799255586[206] = 0.0;
   out_8723676235799255586[207] = 0.0;
   out_8723676235799255586[208] = 0.0;
   out_8723676235799255586[209] = 1.0;
   out_8723676235799255586[210] = 0.0;
   out_8723676235799255586[211] = 0.0;
   out_8723676235799255586[212] = 0.0;
   out_8723676235799255586[213] = 0.0;
   out_8723676235799255586[214] = 0.0;
   out_8723676235799255586[215] = 0.0;
   out_8723676235799255586[216] = 0.0;
   out_8723676235799255586[217] = 0.0;
   out_8723676235799255586[218] = 0.0;
   out_8723676235799255586[219] = 0.0;
   out_8723676235799255586[220] = 0.0;
   out_8723676235799255586[221] = 0.0;
   out_8723676235799255586[222] = 0.0;
   out_8723676235799255586[223] = 0.0;
   out_8723676235799255586[224] = 0.0;
   out_8723676235799255586[225] = 0.0;
   out_8723676235799255586[226] = 0.0;
   out_8723676235799255586[227] = 0.0;
   out_8723676235799255586[228] = 1.0;
   out_8723676235799255586[229] = 0.0;
   out_8723676235799255586[230] = 0.0;
   out_8723676235799255586[231] = 0.0;
   out_8723676235799255586[232] = 0.0;
   out_8723676235799255586[233] = 0.0;
   out_8723676235799255586[234] = 0.0;
   out_8723676235799255586[235] = 0.0;
   out_8723676235799255586[236] = 0.0;
   out_8723676235799255586[237] = 0.0;
   out_8723676235799255586[238] = 0.0;
   out_8723676235799255586[239] = 0.0;
   out_8723676235799255586[240] = 0.0;
   out_8723676235799255586[241] = 0.0;
   out_8723676235799255586[242] = 0.0;
   out_8723676235799255586[243] = 0.0;
   out_8723676235799255586[244] = 0.0;
   out_8723676235799255586[245] = 0.0;
   out_8723676235799255586[246] = 0.0;
   out_8723676235799255586[247] = 1.0;
   out_8723676235799255586[248] = 0.0;
   out_8723676235799255586[249] = 0.0;
   out_8723676235799255586[250] = 0.0;
   out_8723676235799255586[251] = 0.0;
   out_8723676235799255586[252] = 0.0;
   out_8723676235799255586[253] = 0.0;
   out_8723676235799255586[254] = 0.0;
   out_8723676235799255586[255] = 0.0;
   out_8723676235799255586[256] = 0.0;
   out_8723676235799255586[257] = 0.0;
   out_8723676235799255586[258] = 0.0;
   out_8723676235799255586[259] = 0.0;
   out_8723676235799255586[260] = 0.0;
   out_8723676235799255586[261] = 0.0;
   out_8723676235799255586[262] = 0.0;
   out_8723676235799255586[263] = 0.0;
   out_8723676235799255586[264] = 0.0;
   out_8723676235799255586[265] = 0.0;
   out_8723676235799255586[266] = 1.0;
   out_8723676235799255586[267] = 0.0;
   out_8723676235799255586[268] = 0.0;
   out_8723676235799255586[269] = 0.0;
   out_8723676235799255586[270] = 0.0;
   out_8723676235799255586[271] = 0.0;
   out_8723676235799255586[272] = 0.0;
   out_8723676235799255586[273] = 0.0;
   out_8723676235799255586[274] = 0.0;
   out_8723676235799255586[275] = 0.0;
   out_8723676235799255586[276] = 0.0;
   out_8723676235799255586[277] = 0.0;
   out_8723676235799255586[278] = 0.0;
   out_8723676235799255586[279] = 0.0;
   out_8723676235799255586[280] = 0.0;
   out_8723676235799255586[281] = 0.0;
   out_8723676235799255586[282] = 0.0;
   out_8723676235799255586[283] = 0.0;
   out_8723676235799255586[284] = 0.0;
   out_8723676235799255586[285] = 1.0;
   out_8723676235799255586[286] = 0.0;
   out_8723676235799255586[287] = 0.0;
   out_8723676235799255586[288] = 0.0;
   out_8723676235799255586[289] = 0.0;
   out_8723676235799255586[290] = 0.0;
   out_8723676235799255586[291] = 0.0;
   out_8723676235799255586[292] = 0.0;
   out_8723676235799255586[293] = 0.0;
   out_8723676235799255586[294] = 0.0;
   out_8723676235799255586[295] = 0.0;
   out_8723676235799255586[296] = 0.0;
   out_8723676235799255586[297] = 0.0;
   out_8723676235799255586[298] = 0.0;
   out_8723676235799255586[299] = 0.0;
   out_8723676235799255586[300] = 0.0;
   out_8723676235799255586[301] = 0.0;
   out_8723676235799255586[302] = 0.0;
   out_8723676235799255586[303] = 0.0;
   out_8723676235799255586[304] = 1.0;
   out_8723676235799255586[305] = 0.0;
   out_8723676235799255586[306] = 0.0;
   out_8723676235799255586[307] = 0.0;
   out_8723676235799255586[308] = 0.0;
   out_8723676235799255586[309] = 0.0;
   out_8723676235799255586[310] = 0.0;
   out_8723676235799255586[311] = 0.0;
   out_8723676235799255586[312] = 0.0;
   out_8723676235799255586[313] = 0.0;
   out_8723676235799255586[314] = 0.0;
   out_8723676235799255586[315] = 0.0;
   out_8723676235799255586[316] = 0.0;
   out_8723676235799255586[317] = 0.0;
   out_8723676235799255586[318] = 0.0;
   out_8723676235799255586[319] = 0.0;
   out_8723676235799255586[320] = 0.0;
   out_8723676235799255586[321] = 0.0;
   out_8723676235799255586[322] = 0.0;
   out_8723676235799255586[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8216474693621741347) {
   out_8216474693621741347[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8216474693621741347[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8216474693621741347[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8216474693621741347[3] = dt*state[12] + state[3];
   out_8216474693621741347[4] = dt*state[13] + state[4];
   out_8216474693621741347[5] = dt*state[14] + state[5];
   out_8216474693621741347[6] = state[6];
   out_8216474693621741347[7] = state[7];
   out_8216474693621741347[8] = state[8];
   out_8216474693621741347[9] = state[9];
   out_8216474693621741347[10] = state[10];
   out_8216474693621741347[11] = state[11];
   out_8216474693621741347[12] = state[12];
   out_8216474693621741347[13] = state[13];
   out_8216474693621741347[14] = state[14];
   out_8216474693621741347[15] = state[15];
   out_8216474693621741347[16] = state[16];
   out_8216474693621741347[17] = state[17];
}
void F_fun(double *state, double dt, double *out_9150197466179512248) {
   out_9150197466179512248[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9150197466179512248[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9150197466179512248[2] = 0;
   out_9150197466179512248[3] = 0;
   out_9150197466179512248[4] = 0;
   out_9150197466179512248[5] = 0;
   out_9150197466179512248[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9150197466179512248[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9150197466179512248[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9150197466179512248[9] = 0;
   out_9150197466179512248[10] = 0;
   out_9150197466179512248[11] = 0;
   out_9150197466179512248[12] = 0;
   out_9150197466179512248[13] = 0;
   out_9150197466179512248[14] = 0;
   out_9150197466179512248[15] = 0;
   out_9150197466179512248[16] = 0;
   out_9150197466179512248[17] = 0;
   out_9150197466179512248[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9150197466179512248[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9150197466179512248[20] = 0;
   out_9150197466179512248[21] = 0;
   out_9150197466179512248[22] = 0;
   out_9150197466179512248[23] = 0;
   out_9150197466179512248[24] = 0;
   out_9150197466179512248[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9150197466179512248[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9150197466179512248[27] = 0;
   out_9150197466179512248[28] = 0;
   out_9150197466179512248[29] = 0;
   out_9150197466179512248[30] = 0;
   out_9150197466179512248[31] = 0;
   out_9150197466179512248[32] = 0;
   out_9150197466179512248[33] = 0;
   out_9150197466179512248[34] = 0;
   out_9150197466179512248[35] = 0;
   out_9150197466179512248[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9150197466179512248[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9150197466179512248[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9150197466179512248[39] = 0;
   out_9150197466179512248[40] = 0;
   out_9150197466179512248[41] = 0;
   out_9150197466179512248[42] = 0;
   out_9150197466179512248[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9150197466179512248[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9150197466179512248[45] = 0;
   out_9150197466179512248[46] = 0;
   out_9150197466179512248[47] = 0;
   out_9150197466179512248[48] = 0;
   out_9150197466179512248[49] = 0;
   out_9150197466179512248[50] = 0;
   out_9150197466179512248[51] = 0;
   out_9150197466179512248[52] = 0;
   out_9150197466179512248[53] = 0;
   out_9150197466179512248[54] = 0;
   out_9150197466179512248[55] = 0;
   out_9150197466179512248[56] = 0;
   out_9150197466179512248[57] = 1;
   out_9150197466179512248[58] = 0;
   out_9150197466179512248[59] = 0;
   out_9150197466179512248[60] = 0;
   out_9150197466179512248[61] = 0;
   out_9150197466179512248[62] = 0;
   out_9150197466179512248[63] = 0;
   out_9150197466179512248[64] = 0;
   out_9150197466179512248[65] = 0;
   out_9150197466179512248[66] = dt;
   out_9150197466179512248[67] = 0;
   out_9150197466179512248[68] = 0;
   out_9150197466179512248[69] = 0;
   out_9150197466179512248[70] = 0;
   out_9150197466179512248[71] = 0;
   out_9150197466179512248[72] = 0;
   out_9150197466179512248[73] = 0;
   out_9150197466179512248[74] = 0;
   out_9150197466179512248[75] = 0;
   out_9150197466179512248[76] = 1;
   out_9150197466179512248[77] = 0;
   out_9150197466179512248[78] = 0;
   out_9150197466179512248[79] = 0;
   out_9150197466179512248[80] = 0;
   out_9150197466179512248[81] = 0;
   out_9150197466179512248[82] = 0;
   out_9150197466179512248[83] = 0;
   out_9150197466179512248[84] = 0;
   out_9150197466179512248[85] = dt;
   out_9150197466179512248[86] = 0;
   out_9150197466179512248[87] = 0;
   out_9150197466179512248[88] = 0;
   out_9150197466179512248[89] = 0;
   out_9150197466179512248[90] = 0;
   out_9150197466179512248[91] = 0;
   out_9150197466179512248[92] = 0;
   out_9150197466179512248[93] = 0;
   out_9150197466179512248[94] = 0;
   out_9150197466179512248[95] = 1;
   out_9150197466179512248[96] = 0;
   out_9150197466179512248[97] = 0;
   out_9150197466179512248[98] = 0;
   out_9150197466179512248[99] = 0;
   out_9150197466179512248[100] = 0;
   out_9150197466179512248[101] = 0;
   out_9150197466179512248[102] = 0;
   out_9150197466179512248[103] = 0;
   out_9150197466179512248[104] = dt;
   out_9150197466179512248[105] = 0;
   out_9150197466179512248[106] = 0;
   out_9150197466179512248[107] = 0;
   out_9150197466179512248[108] = 0;
   out_9150197466179512248[109] = 0;
   out_9150197466179512248[110] = 0;
   out_9150197466179512248[111] = 0;
   out_9150197466179512248[112] = 0;
   out_9150197466179512248[113] = 0;
   out_9150197466179512248[114] = 1;
   out_9150197466179512248[115] = 0;
   out_9150197466179512248[116] = 0;
   out_9150197466179512248[117] = 0;
   out_9150197466179512248[118] = 0;
   out_9150197466179512248[119] = 0;
   out_9150197466179512248[120] = 0;
   out_9150197466179512248[121] = 0;
   out_9150197466179512248[122] = 0;
   out_9150197466179512248[123] = 0;
   out_9150197466179512248[124] = 0;
   out_9150197466179512248[125] = 0;
   out_9150197466179512248[126] = 0;
   out_9150197466179512248[127] = 0;
   out_9150197466179512248[128] = 0;
   out_9150197466179512248[129] = 0;
   out_9150197466179512248[130] = 0;
   out_9150197466179512248[131] = 0;
   out_9150197466179512248[132] = 0;
   out_9150197466179512248[133] = 1;
   out_9150197466179512248[134] = 0;
   out_9150197466179512248[135] = 0;
   out_9150197466179512248[136] = 0;
   out_9150197466179512248[137] = 0;
   out_9150197466179512248[138] = 0;
   out_9150197466179512248[139] = 0;
   out_9150197466179512248[140] = 0;
   out_9150197466179512248[141] = 0;
   out_9150197466179512248[142] = 0;
   out_9150197466179512248[143] = 0;
   out_9150197466179512248[144] = 0;
   out_9150197466179512248[145] = 0;
   out_9150197466179512248[146] = 0;
   out_9150197466179512248[147] = 0;
   out_9150197466179512248[148] = 0;
   out_9150197466179512248[149] = 0;
   out_9150197466179512248[150] = 0;
   out_9150197466179512248[151] = 0;
   out_9150197466179512248[152] = 1;
   out_9150197466179512248[153] = 0;
   out_9150197466179512248[154] = 0;
   out_9150197466179512248[155] = 0;
   out_9150197466179512248[156] = 0;
   out_9150197466179512248[157] = 0;
   out_9150197466179512248[158] = 0;
   out_9150197466179512248[159] = 0;
   out_9150197466179512248[160] = 0;
   out_9150197466179512248[161] = 0;
   out_9150197466179512248[162] = 0;
   out_9150197466179512248[163] = 0;
   out_9150197466179512248[164] = 0;
   out_9150197466179512248[165] = 0;
   out_9150197466179512248[166] = 0;
   out_9150197466179512248[167] = 0;
   out_9150197466179512248[168] = 0;
   out_9150197466179512248[169] = 0;
   out_9150197466179512248[170] = 0;
   out_9150197466179512248[171] = 1;
   out_9150197466179512248[172] = 0;
   out_9150197466179512248[173] = 0;
   out_9150197466179512248[174] = 0;
   out_9150197466179512248[175] = 0;
   out_9150197466179512248[176] = 0;
   out_9150197466179512248[177] = 0;
   out_9150197466179512248[178] = 0;
   out_9150197466179512248[179] = 0;
   out_9150197466179512248[180] = 0;
   out_9150197466179512248[181] = 0;
   out_9150197466179512248[182] = 0;
   out_9150197466179512248[183] = 0;
   out_9150197466179512248[184] = 0;
   out_9150197466179512248[185] = 0;
   out_9150197466179512248[186] = 0;
   out_9150197466179512248[187] = 0;
   out_9150197466179512248[188] = 0;
   out_9150197466179512248[189] = 0;
   out_9150197466179512248[190] = 1;
   out_9150197466179512248[191] = 0;
   out_9150197466179512248[192] = 0;
   out_9150197466179512248[193] = 0;
   out_9150197466179512248[194] = 0;
   out_9150197466179512248[195] = 0;
   out_9150197466179512248[196] = 0;
   out_9150197466179512248[197] = 0;
   out_9150197466179512248[198] = 0;
   out_9150197466179512248[199] = 0;
   out_9150197466179512248[200] = 0;
   out_9150197466179512248[201] = 0;
   out_9150197466179512248[202] = 0;
   out_9150197466179512248[203] = 0;
   out_9150197466179512248[204] = 0;
   out_9150197466179512248[205] = 0;
   out_9150197466179512248[206] = 0;
   out_9150197466179512248[207] = 0;
   out_9150197466179512248[208] = 0;
   out_9150197466179512248[209] = 1;
   out_9150197466179512248[210] = 0;
   out_9150197466179512248[211] = 0;
   out_9150197466179512248[212] = 0;
   out_9150197466179512248[213] = 0;
   out_9150197466179512248[214] = 0;
   out_9150197466179512248[215] = 0;
   out_9150197466179512248[216] = 0;
   out_9150197466179512248[217] = 0;
   out_9150197466179512248[218] = 0;
   out_9150197466179512248[219] = 0;
   out_9150197466179512248[220] = 0;
   out_9150197466179512248[221] = 0;
   out_9150197466179512248[222] = 0;
   out_9150197466179512248[223] = 0;
   out_9150197466179512248[224] = 0;
   out_9150197466179512248[225] = 0;
   out_9150197466179512248[226] = 0;
   out_9150197466179512248[227] = 0;
   out_9150197466179512248[228] = 1;
   out_9150197466179512248[229] = 0;
   out_9150197466179512248[230] = 0;
   out_9150197466179512248[231] = 0;
   out_9150197466179512248[232] = 0;
   out_9150197466179512248[233] = 0;
   out_9150197466179512248[234] = 0;
   out_9150197466179512248[235] = 0;
   out_9150197466179512248[236] = 0;
   out_9150197466179512248[237] = 0;
   out_9150197466179512248[238] = 0;
   out_9150197466179512248[239] = 0;
   out_9150197466179512248[240] = 0;
   out_9150197466179512248[241] = 0;
   out_9150197466179512248[242] = 0;
   out_9150197466179512248[243] = 0;
   out_9150197466179512248[244] = 0;
   out_9150197466179512248[245] = 0;
   out_9150197466179512248[246] = 0;
   out_9150197466179512248[247] = 1;
   out_9150197466179512248[248] = 0;
   out_9150197466179512248[249] = 0;
   out_9150197466179512248[250] = 0;
   out_9150197466179512248[251] = 0;
   out_9150197466179512248[252] = 0;
   out_9150197466179512248[253] = 0;
   out_9150197466179512248[254] = 0;
   out_9150197466179512248[255] = 0;
   out_9150197466179512248[256] = 0;
   out_9150197466179512248[257] = 0;
   out_9150197466179512248[258] = 0;
   out_9150197466179512248[259] = 0;
   out_9150197466179512248[260] = 0;
   out_9150197466179512248[261] = 0;
   out_9150197466179512248[262] = 0;
   out_9150197466179512248[263] = 0;
   out_9150197466179512248[264] = 0;
   out_9150197466179512248[265] = 0;
   out_9150197466179512248[266] = 1;
   out_9150197466179512248[267] = 0;
   out_9150197466179512248[268] = 0;
   out_9150197466179512248[269] = 0;
   out_9150197466179512248[270] = 0;
   out_9150197466179512248[271] = 0;
   out_9150197466179512248[272] = 0;
   out_9150197466179512248[273] = 0;
   out_9150197466179512248[274] = 0;
   out_9150197466179512248[275] = 0;
   out_9150197466179512248[276] = 0;
   out_9150197466179512248[277] = 0;
   out_9150197466179512248[278] = 0;
   out_9150197466179512248[279] = 0;
   out_9150197466179512248[280] = 0;
   out_9150197466179512248[281] = 0;
   out_9150197466179512248[282] = 0;
   out_9150197466179512248[283] = 0;
   out_9150197466179512248[284] = 0;
   out_9150197466179512248[285] = 1;
   out_9150197466179512248[286] = 0;
   out_9150197466179512248[287] = 0;
   out_9150197466179512248[288] = 0;
   out_9150197466179512248[289] = 0;
   out_9150197466179512248[290] = 0;
   out_9150197466179512248[291] = 0;
   out_9150197466179512248[292] = 0;
   out_9150197466179512248[293] = 0;
   out_9150197466179512248[294] = 0;
   out_9150197466179512248[295] = 0;
   out_9150197466179512248[296] = 0;
   out_9150197466179512248[297] = 0;
   out_9150197466179512248[298] = 0;
   out_9150197466179512248[299] = 0;
   out_9150197466179512248[300] = 0;
   out_9150197466179512248[301] = 0;
   out_9150197466179512248[302] = 0;
   out_9150197466179512248[303] = 0;
   out_9150197466179512248[304] = 1;
   out_9150197466179512248[305] = 0;
   out_9150197466179512248[306] = 0;
   out_9150197466179512248[307] = 0;
   out_9150197466179512248[308] = 0;
   out_9150197466179512248[309] = 0;
   out_9150197466179512248[310] = 0;
   out_9150197466179512248[311] = 0;
   out_9150197466179512248[312] = 0;
   out_9150197466179512248[313] = 0;
   out_9150197466179512248[314] = 0;
   out_9150197466179512248[315] = 0;
   out_9150197466179512248[316] = 0;
   out_9150197466179512248[317] = 0;
   out_9150197466179512248[318] = 0;
   out_9150197466179512248[319] = 0;
   out_9150197466179512248[320] = 0;
   out_9150197466179512248[321] = 0;
   out_9150197466179512248[322] = 0;
   out_9150197466179512248[323] = 1;
}
void h_4(double *state, double *unused, double *out_6828733239090926752) {
   out_6828733239090926752[0] = state[6] + state[9];
   out_6828733239090926752[1] = state[7] + state[10];
   out_6828733239090926752[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5380831403152443183) {
   out_5380831403152443183[0] = 0;
   out_5380831403152443183[1] = 0;
   out_5380831403152443183[2] = 0;
   out_5380831403152443183[3] = 0;
   out_5380831403152443183[4] = 0;
   out_5380831403152443183[5] = 0;
   out_5380831403152443183[6] = 1;
   out_5380831403152443183[7] = 0;
   out_5380831403152443183[8] = 0;
   out_5380831403152443183[9] = 1;
   out_5380831403152443183[10] = 0;
   out_5380831403152443183[11] = 0;
   out_5380831403152443183[12] = 0;
   out_5380831403152443183[13] = 0;
   out_5380831403152443183[14] = 0;
   out_5380831403152443183[15] = 0;
   out_5380831403152443183[16] = 0;
   out_5380831403152443183[17] = 0;
   out_5380831403152443183[18] = 0;
   out_5380831403152443183[19] = 0;
   out_5380831403152443183[20] = 0;
   out_5380831403152443183[21] = 0;
   out_5380831403152443183[22] = 0;
   out_5380831403152443183[23] = 0;
   out_5380831403152443183[24] = 0;
   out_5380831403152443183[25] = 1;
   out_5380831403152443183[26] = 0;
   out_5380831403152443183[27] = 0;
   out_5380831403152443183[28] = 1;
   out_5380831403152443183[29] = 0;
   out_5380831403152443183[30] = 0;
   out_5380831403152443183[31] = 0;
   out_5380831403152443183[32] = 0;
   out_5380831403152443183[33] = 0;
   out_5380831403152443183[34] = 0;
   out_5380831403152443183[35] = 0;
   out_5380831403152443183[36] = 0;
   out_5380831403152443183[37] = 0;
   out_5380831403152443183[38] = 0;
   out_5380831403152443183[39] = 0;
   out_5380831403152443183[40] = 0;
   out_5380831403152443183[41] = 0;
   out_5380831403152443183[42] = 0;
   out_5380831403152443183[43] = 0;
   out_5380831403152443183[44] = 1;
   out_5380831403152443183[45] = 0;
   out_5380831403152443183[46] = 0;
   out_5380831403152443183[47] = 1;
   out_5380831403152443183[48] = 0;
   out_5380831403152443183[49] = 0;
   out_5380831403152443183[50] = 0;
   out_5380831403152443183[51] = 0;
   out_5380831403152443183[52] = 0;
   out_5380831403152443183[53] = 0;
}
void h_10(double *state, double *unused, double *out_2858686616301996276) {
   out_2858686616301996276[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2858686616301996276[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2858686616301996276[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6143684893144312761) {
   out_6143684893144312761[0] = 0;
   out_6143684893144312761[1] = 9.8100000000000005*cos(state[1]);
   out_6143684893144312761[2] = 0;
   out_6143684893144312761[3] = 0;
   out_6143684893144312761[4] = -state[8];
   out_6143684893144312761[5] = state[7];
   out_6143684893144312761[6] = 0;
   out_6143684893144312761[7] = state[5];
   out_6143684893144312761[8] = -state[4];
   out_6143684893144312761[9] = 0;
   out_6143684893144312761[10] = 0;
   out_6143684893144312761[11] = 0;
   out_6143684893144312761[12] = 1;
   out_6143684893144312761[13] = 0;
   out_6143684893144312761[14] = 0;
   out_6143684893144312761[15] = 1;
   out_6143684893144312761[16] = 0;
   out_6143684893144312761[17] = 0;
   out_6143684893144312761[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6143684893144312761[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6143684893144312761[20] = 0;
   out_6143684893144312761[21] = state[8];
   out_6143684893144312761[22] = 0;
   out_6143684893144312761[23] = -state[6];
   out_6143684893144312761[24] = -state[5];
   out_6143684893144312761[25] = 0;
   out_6143684893144312761[26] = state[3];
   out_6143684893144312761[27] = 0;
   out_6143684893144312761[28] = 0;
   out_6143684893144312761[29] = 0;
   out_6143684893144312761[30] = 0;
   out_6143684893144312761[31] = 1;
   out_6143684893144312761[32] = 0;
   out_6143684893144312761[33] = 0;
   out_6143684893144312761[34] = 1;
   out_6143684893144312761[35] = 0;
   out_6143684893144312761[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6143684893144312761[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6143684893144312761[38] = 0;
   out_6143684893144312761[39] = -state[7];
   out_6143684893144312761[40] = state[6];
   out_6143684893144312761[41] = 0;
   out_6143684893144312761[42] = state[4];
   out_6143684893144312761[43] = -state[3];
   out_6143684893144312761[44] = 0;
   out_6143684893144312761[45] = 0;
   out_6143684893144312761[46] = 0;
   out_6143684893144312761[47] = 0;
   out_6143684893144312761[48] = 0;
   out_6143684893144312761[49] = 0;
   out_6143684893144312761[50] = 1;
   out_6143684893144312761[51] = 0;
   out_6143684893144312761[52] = 0;
   out_6143684893144312761[53] = 1;
}
void h_13(double *state, double *unused, double *out_5884763655197767271) {
   out_5884763655197767271[0] = state[3];
   out_5884763655197767271[1] = state[4];
   out_5884763655197767271[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2168557577820110382) {
   out_2168557577820110382[0] = 0;
   out_2168557577820110382[1] = 0;
   out_2168557577820110382[2] = 0;
   out_2168557577820110382[3] = 1;
   out_2168557577820110382[4] = 0;
   out_2168557577820110382[5] = 0;
   out_2168557577820110382[6] = 0;
   out_2168557577820110382[7] = 0;
   out_2168557577820110382[8] = 0;
   out_2168557577820110382[9] = 0;
   out_2168557577820110382[10] = 0;
   out_2168557577820110382[11] = 0;
   out_2168557577820110382[12] = 0;
   out_2168557577820110382[13] = 0;
   out_2168557577820110382[14] = 0;
   out_2168557577820110382[15] = 0;
   out_2168557577820110382[16] = 0;
   out_2168557577820110382[17] = 0;
   out_2168557577820110382[18] = 0;
   out_2168557577820110382[19] = 0;
   out_2168557577820110382[20] = 0;
   out_2168557577820110382[21] = 0;
   out_2168557577820110382[22] = 1;
   out_2168557577820110382[23] = 0;
   out_2168557577820110382[24] = 0;
   out_2168557577820110382[25] = 0;
   out_2168557577820110382[26] = 0;
   out_2168557577820110382[27] = 0;
   out_2168557577820110382[28] = 0;
   out_2168557577820110382[29] = 0;
   out_2168557577820110382[30] = 0;
   out_2168557577820110382[31] = 0;
   out_2168557577820110382[32] = 0;
   out_2168557577820110382[33] = 0;
   out_2168557577820110382[34] = 0;
   out_2168557577820110382[35] = 0;
   out_2168557577820110382[36] = 0;
   out_2168557577820110382[37] = 0;
   out_2168557577820110382[38] = 0;
   out_2168557577820110382[39] = 0;
   out_2168557577820110382[40] = 0;
   out_2168557577820110382[41] = 1;
   out_2168557577820110382[42] = 0;
   out_2168557577820110382[43] = 0;
   out_2168557577820110382[44] = 0;
   out_2168557577820110382[45] = 0;
   out_2168557577820110382[46] = 0;
   out_2168557577820110382[47] = 0;
   out_2168557577820110382[48] = 0;
   out_2168557577820110382[49] = 0;
   out_2168557577820110382[50] = 0;
   out_2168557577820110382[51] = 0;
   out_2168557577820110382[52] = 0;
   out_2168557577820110382[53] = 0;
}
void h_14(double *state, double *unused, double *out_5945367881582987740) {
   out_5945367881582987740[0] = state[6];
   out_5945367881582987740[1] = state[7];
   out_5945367881582987740[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1417590546812958654) {
   out_1417590546812958654[0] = 0;
   out_1417590546812958654[1] = 0;
   out_1417590546812958654[2] = 0;
   out_1417590546812958654[3] = 0;
   out_1417590546812958654[4] = 0;
   out_1417590546812958654[5] = 0;
   out_1417590546812958654[6] = 1;
   out_1417590546812958654[7] = 0;
   out_1417590546812958654[8] = 0;
   out_1417590546812958654[9] = 0;
   out_1417590546812958654[10] = 0;
   out_1417590546812958654[11] = 0;
   out_1417590546812958654[12] = 0;
   out_1417590546812958654[13] = 0;
   out_1417590546812958654[14] = 0;
   out_1417590546812958654[15] = 0;
   out_1417590546812958654[16] = 0;
   out_1417590546812958654[17] = 0;
   out_1417590546812958654[18] = 0;
   out_1417590546812958654[19] = 0;
   out_1417590546812958654[20] = 0;
   out_1417590546812958654[21] = 0;
   out_1417590546812958654[22] = 0;
   out_1417590546812958654[23] = 0;
   out_1417590546812958654[24] = 0;
   out_1417590546812958654[25] = 1;
   out_1417590546812958654[26] = 0;
   out_1417590546812958654[27] = 0;
   out_1417590546812958654[28] = 0;
   out_1417590546812958654[29] = 0;
   out_1417590546812958654[30] = 0;
   out_1417590546812958654[31] = 0;
   out_1417590546812958654[32] = 0;
   out_1417590546812958654[33] = 0;
   out_1417590546812958654[34] = 0;
   out_1417590546812958654[35] = 0;
   out_1417590546812958654[36] = 0;
   out_1417590546812958654[37] = 0;
   out_1417590546812958654[38] = 0;
   out_1417590546812958654[39] = 0;
   out_1417590546812958654[40] = 0;
   out_1417590546812958654[41] = 0;
   out_1417590546812958654[42] = 0;
   out_1417590546812958654[43] = 0;
   out_1417590546812958654[44] = 1;
   out_1417590546812958654[45] = 0;
   out_1417590546812958654[46] = 0;
   out_1417590546812958654[47] = 0;
   out_1417590546812958654[48] = 0;
   out_1417590546812958654[49] = 0;
   out_1417590546812958654[50] = 0;
   out_1417590546812958654[51] = 0;
   out_1417590546812958654[52] = 0;
   out_1417590546812958654[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4256674648376746002) {
  err_fun(nom_x, delta_x, out_4256674648376746002);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6072215117786325780) {
  inv_err_fun(nom_x, true_x, out_6072215117786325780);
}
void pose_H_mod_fun(double *state, double *out_8723676235799255586) {
  H_mod_fun(state, out_8723676235799255586);
}
void pose_f_fun(double *state, double dt, double *out_8216474693621741347) {
  f_fun(state,  dt, out_8216474693621741347);
}
void pose_F_fun(double *state, double dt, double *out_9150197466179512248) {
  F_fun(state,  dt, out_9150197466179512248);
}
void pose_h_4(double *state, double *unused, double *out_6828733239090926752) {
  h_4(state, unused, out_6828733239090926752);
}
void pose_H_4(double *state, double *unused, double *out_5380831403152443183) {
  H_4(state, unused, out_5380831403152443183);
}
void pose_h_10(double *state, double *unused, double *out_2858686616301996276) {
  h_10(state, unused, out_2858686616301996276);
}
void pose_H_10(double *state, double *unused, double *out_6143684893144312761) {
  H_10(state, unused, out_6143684893144312761);
}
void pose_h_13(double *state, double *unused, double *out_5884763655197767271) {
  h_13(state, unused, out_5884763655197767271);
}
void pose_H_13(double *state, double *unused, double *out_2168557577820110382) {
  H_13(state, unused, out_2168557577820110382);
}
void pose_h_14(double *state, double *unused, double *out_5945367881582987740) {
  h_14(state, unused, out_5945367881582987740);
}
void pose_H_14(double *state, double *unused, double *out_1417590546812958654) {
  H_14(state, unused, out_1417590546812958654);
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
