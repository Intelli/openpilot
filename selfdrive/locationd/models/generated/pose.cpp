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
void err_fun(double *nom_x, double *delta_x, double *out_5091660165595542600) {
   out_5091660165595542600[0] = delta_x[0] + nom_x[0];
   out_5091660165595542600[1] = delta_x[1] + nom_x[1];
   out_5091660165595542600[2] = delta_x[2] + nom_x[2];
   out_5091660165595542600[3] = delta_x[3] + nom_x[3];
   out_5091660165595542600[4] = delta_x[4] + nom_x[4];
   out_5091660165595542600[5] = delta_x[5] + nom_x[5];
   out_5091660165595542600[6] = delta_x[6] + nom_x[6];
   out_5091660165595542600[7] = delta_x[7] + nom_x[7];
   out_5091660165595542600[8] = delta_x[8] + nom_x[8];
   out_5091660165595542600[9] = delta_x[9] + nom_x[9];
   out_5091660165595542600[10] = delta_x[10] + nom_x[10];
   out_5091660165595542600[11] = delta_x[11] + nom_x[11];
   out_5091660165595542600[12] = delta_x[12] + nom_x[12];
   out_5091660165595542600[13] = delta_x[13] + nom_x[13];
   out_5091660165595542600[14] = delta_x[14] + nom_x[14];
   out_5091660165595542600[15] = delta_x[15] + nom_x[15];
   out_5091660165595542600[16] = delta_x[16] + nom_x[16];
   out_5091660165595542600[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_828551828041337701) {
   out_828551828041337701[0] = -nom_x[0] + true_x[0];
   out_828551828041337701[1] = -nom_x[1] + true_x[1];
   out_828551828041337701[2] = -nom_x[2] + true_x[2];
   out_828551828041337701[3] = -nom_x[3] + true_x[3];
   out_828551828041337701[4] = -nom_x[4] + true_x[4];
   out_828551828041337701[5] = -nom_x[5] + true_x[5];
   out_828551828041337701[6] = -nom_x[6] + true_x[6];
   out_828551828041337701[7] = -nom_x[7] + true_x[7];
   out_828551828041337701[8] = -nom_x[8] + true_x[8];
   out_828551828041337701[9] = -nom_x[9] + true_x[9];
   out_828551828041337701[10] = -nom_x[10] + true_x[10];
   out_828551828041337701[11] = -nom_x[11] + true_x[11];
   out_828551828041337701[12] = -nom_x[12] + true_x[12];
   out_828551828041337701[13] = -nom_x[13] + true_x[13];
   out_828551828041337701[14] = -nom_x[14] + true_x[14];
   out_828551828041337701[15] = -nom_x[15] + true_x[15];
   out_828551828041337701[16] = -nom_x[16] + true_x[16];
   out_828551828041337701[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3117881215721449640) {
   out_3117881215721449640[0] = 1.0;
   out_3117881215721449640[1] = 0.0;
   out_3117881215721449640[2] = 0.0;
   out_3117881215721449640[3] = 0.0;
   out_3117881215721449640[4] = 0.0;
   out_3117881215721449640[5] = 0.0;
   out_3117881215721449640[6] = 0.0;
   out_3117881215721449640[7] = 0.0;
   out_3117881215721449640[8] = 0.0;
   out_3117881215721449640[9] = 0.0;
   out_3117881215721449640[10] = 0.0;
   out_3117881215721449640[11] = 0.0;
   out_3117881215721449640[12] = 0.0;
   out_3117881215721449640[13] = 0.0;
   out_3117881215721449640[14] = 0.0;
   out_3117881215721449640[15] = 0.0;
   out_3117881215721449640[16] = 0.0;
   out_3117881215721449640[17] = 0.0;
   out_3117881215721449640[18] = 0.0;
   out_3117881215721449640[19] = 1.0;
   out_3117881215721449640[20] = 0.0;
   out_3117881215721449640[21] = 0.0;
   out_3117881215721449640[22] = 0.0;
   out_3117881215721449640[23] = 0.0;
   out_3117881215721449640[24] = 0.0;
   out_3117881215721449640[25] = 0.0;
   out_3117881215721449640[26] = 0.0;
   out_3117881215721449640[27] = 0.0;
   out_3117881215721449640[28] = 0.0;
   out_3117881215721449640[29] = 0.0;
   out_3117881215721449640[30] = 0.0;
   out_3117881215721449640[31] = 0.0;
   out_3117881215721449640[32] = 0.0;
   out_3117881215721449640[33] = 0.0;
   out_3117881215721449640[34] = 0.0;
   out_3117881215721449640[35] = 0.0;
   out_3117881215721449640[36] = 0.0;
   out_3117881215721449640[37] = 0.0;
   out_3117881215721449640[38] = 1.0;
   out_3117881215721449640[39] = 0.0;
   out_3117881215721449640[40] = 0.0;
   out_3117881215721449640[41] = 0.0;
   out_3117881215721449640[42] = 0.0;
   out_3117881215721449640[43] = 0.0;
   out_3117881215721449640[44] = 0.0;
   out_3117881215721449640[45] = 0.0;
   out_3117881215721449640[46] = 0.0;
   out_3117881215721449640[47] = 0.0;
   out_3117881215721449640[48] = 0.0;
   out_3117881215721449640[49] = 0.0;
   out_3117881215721449640[50] = 0.0;
   out_3117881215721449640[51] = 0.0;
   out_3117881215721449640[52] = 0.0;
   out_3117881215721449640[53] = 0.0;
   out_3117881215721449640[54] = 0.0;
   out_3117881215721449640[55] = 0.0;
   out_3117881215721449640[56] = 0.0;
   out_3117881215721449640[57] = 1.0;
   out_3117881215721449640[58] = 0.0;
   out_3117881215721449640[59] = 0.0;
   out_3117881215721449640[60] = 0.0;
   out_3117881215721449640[61] = 0.0;
   out_3117881215721449640[62] = 0.0;
   out_3117881215721449640[63] = 0.0;
   out_3117881215721449640[64] = 0.0;
   out_3117881215721449640[65] = 0.0;
   out_3117881215721449640[66] = 0.0;
   out_3117881215721449640[67] = 0.0;
   out_3117881215721449640[68] = 0.0;
   out_3117881215721449640[69] = 0.0;
   out_3117881215721449640[70] = 0.0;
   out_3117881215721449640[71] = 0.0;
   out_3117881215721449640[72] = 0.0;
   out_3117881215721449640[73] = 0.0;
   out_3117881215721449640[74] = 0.0;
   out_3117881215721449640[75] = 0.0;
   out_3117881215721449640[76] = 1.0;
   out_3117881215721449640[77] = 0.0;
   out_3117881215721449640[78] = 0.0;
   out_3117881215721449640[79] = 0.0;
   out_3117881215721449640[80] = 0.0;
   out_3117881215721449640[81] = 0.0;
   out_3117881215721449640[82] = 0.0;
   out_3117881215721449640[83] = 0.0;
   out_3117881215721449640[84] = 0.0;
   out_3117881215721449640[85] = 0.0;
   out_3117881215721449640[86] = 0.0;
   out_3117881215721449640[87] = 0.0;
   out_3117881215721449640[88] = 0.0;
   out_3117881215721449640[89] = 0.0;
   out_3117881215721449640[90] = 0.0;
   out_3117881215721449640[91] = 0.0;
   out_3117881215721449640[92] = 0.0;
   out_3117881215721449640[93] = 0.0;
   out_3117881215721449640[94] = 0.0;
   out_3117881215721449640[95] = 1.0;
   out_3117881215721449640[96] = 0.0;
   out_3117881215721449640[97] = 0.0;
   out_3117881215721449640[98] = 0.0;
   out_3117881215721449640[99] = 0.0;
   out_3117881215721449640[100] = 0.0;
   out_3117881215721449640[101] = 0.0;
   out_3117881215721449640[102] = 0.0;
   out_3117881215721449640[103] = 0.0;
   out_3117881215721449640[104] = 0.0;
   out_3117881215721449640[105] = 0.0;
   out_3117881215721449640[106] = 0.0;
   out_3117881215721449640[107] = 0.0;
   out_3117881215721449640[108] = 0.0;
   out_3117881215721449640[109] = 0.0;
   out_3117881215721449640[110] = 0.0;
   out_3117881215721449640[111] = 0.0;
   out_3117881215721449640[112] = 0.0;
   out_3117881215721449640[113] = 0.0;
   out_3117881215721449640[114] = 1.0;
   out_3117881215721449640[115] = 0.0;
   out_3117881215721449640[116] = 0.0;
   out_3117881215721449640[117] = 0.0;
   out_3117881215721449640[118] = 0.0;
   out_3117881215721449640[119] = 0.0;
   out_3117881215721449640[120] = 0.0;
   out_3117881215721449640[121] = 0.0;
   out_3117881215721449640[122] = 0.0;
   out_3117881215721449640[123] = 0.0;
   out_3117881215721449640[124] = 0.0;
   out_3117881215721449640[125] = 0.0;
   out_3117881215721449640[126] = 0.0;
   out_3117881215721449640[127] = 0.0;
   out_3117881215721449640[128] = 0.0;
   out_3117881215721449640[129] = 0.0;
   out_3117881215721449640[130] = 0.0;
   out_3117881215721449640[131] = 0.0;
   out_3117881215721449640[132] = 0.0;
   out_3117881215721449640[133] = 1.0;
   out_3117881215721449640[134] = 0.0;
   out_3117881215721449640[135] = 0.0;
   out_3117881215721449640[136] = 0.0;
   out_3117881215721449640[137] = 0.0;
   out_3117881215721449640[138] = 0.0;
   out_3117881215721449640[139] = 0.0;
   out_3117881215721449640[140] = 0.0;
   out_3117881215721449640[141] = 0.0;
   out_3117881215721449640[142] = 0.0;
   out_3117881215721449640[143] = 0.0;
   out_3117881215721449640[144] = 0.0;
   out_3117881215721449640[145] = 0.0;
   out_3117881215721449640[146] = 0.0;
   out_3117881215721449640[147] = 0.0;
   out_3117881215721449640[148] = 0.0;
   out_3117881215721449640[149] = 0.0;
   out_3117881215721449640[150] = 0.0;
   out_3117881215721449640[151] = 0.0;
   out_3117881215721449640[152] = 1.0;
   out_3117881215721449640[153] = 0.0;
   out_3117881215721449640[154] = 0.0;
   out_3117881215721449640[155] = 0.0;
   out_3117881215721449640[156] = 0.0;
   out_3117881215721449640[157] = 0.0;
   out_3117881215721449640[158] = 0.0;
   out_3117881215721449640[159] = 0.0;
   out_3117881215721449640[160] = 0.0;
   out_3117881215721449640[161] = 0.0;
   out_3117881215721449640[162] = 0.0;
   out_3117881215721449640[163] = 0.0;
   out_3117881215721449640[164] = 0.0;
   out_3117881215721449640[165] = 0.0;
   out_3117881215721449640[166] = 0.0;
   out_3117881215721449640[167] = 0.0;
   out_3117881215721449640[168] = 0.0;
   out_3117881215721449640[169] = 0.0;
   out_3117881215721449640[170] = 0.0;
   out_3117881215721449640[171] = 1.0;
   out_3117881215721449640[172] = 0.0;
   out_3117881215721449640[173] = 0.0;
   out_3117881215721449640[174] = 0.0;
   out_3117881215721449640[175] = 0.0;
   out_3117881215721449640[176] = 0.0;
   out_3117881215721449640[177] = 0.0;
   out_3117881215721449640[178] = 0.0;
   out_3117881215721449640[179] = 0.0;
   out_3117881215721449640[180] = 0.0;
   out_3117881215721449640[181] = 0.0;
   out_3117881215721449640[182] = 0.0;
   out_3117881215721449640[183] = 0.0;
   out_3117881215721449640[184] = 0.0;
   out_3117881215721449640[185] = 0.0;
   out_3117881215721449640[186] = 0.0;
   out_3117881215721449640[187] = 0.0;
   out_3117881215721449640[188] = 0.0;
   out_3117881215721449640[189] = 0.0;
   out_3117881215721449640[190] = 1.0;
   out_3117881215721449640[191] = 0.0;
   out_3117881215721449640[192] = 0.0;
   out_3117881215721449640[193] = 0.0;
   out_3117881215721449640[194] = 0.0;
   out_3117881215721449640[195] = 0.0;
   out_3117881215721449640[196] = 0.0;
   out_3117881215721449640[197] = 0.0;
   out_3117881215721449640[198] = 0.0;
   out_3117881215721449640[199] = 0.0;
   out_3117881215721449640[200] = 0.0;
   out_3117881215721449640[201] = 0.0;
   out_3117881215721449640[202] = 0.0;
   out_3117881215721449640[203] = 0.0;
   out_3117881215721449640[204] = 0.0;
   out_3117881215721449640[205] = 0.0;
   out_3117881215721449640[206] = 0.0;
   out_3117881215721449640[207] = 0.0;
   out_3117881215721449640[208] = 0.0;
   out_3117881215721449640[209] = 1.0;
   out_3117881215721449640[210] = 0.0;
   out_3117881215721449640[211] = 0.0;
   out_3117881215721449640[212] = 0.0;
   out_3117881215721449640[213] = 0.0;
   out_3117881215721449640[214] = 0.0;
   out_3117881215721449640[215] = 0.0;
   out_3117881215721449640[216] = 0.0;
   out_3117881215721449640[217] = 0.0;
   out_3117881215721449640[218] = 0.0;
   out_3117881215721449640[219] = 0.0;
   out_3117881215721449640[220] = 0.0;
   out_3117881215721449640[221] = 0.0;
   out_3117881215721449640[222] = 0.0;
   out_3117881215721449640[223] = 0.0;
   out_3117881215721449640[224] = 0.0;
   out_3117881215721449640[225] = 0.0;
   out_3117881215721449640[226] = 0.0;
   out_3117881215721449640[227] = 0.0;
   out_3117881215721449640[228] = 1.0;
   out_3117881215721449640[229] = 0.0;
   out_3117881215721449640[230] = 0.0;
   out_3117881215721449640[231] = 0.0;
   out_3117881215721449640[232] = 0.0;
   out_3117881215721449640[233] = 0.0;
   out_3117881215721449640[234] = 0.0;
   out_3117881215721449640[235] = 0.0;
   out_3117881215721449640[236] = 0.0;
   out_3117881215721449640[237] = 0.0;
   out_3117881215721449640[238] = 0.0;
   out_3117881215721449640[239] = 0.0;
   out_3117881215721449640[240] = 0.0;
   out_3117881215721449640[241] = 0.0;
   out_3117881215721449640[242] = 0.0;
   out_3117881215721449640[243] = 0.0;
   out_3117881215721449640[244] = 0.0;
   out_3117881215721449640[245] = 0.0;
   out_3117881215721449640[246] = 0.0;
   out_3117881215721449640[247] = 1.0;
   out_3117881215721449640[248] = 0.0;
   out_3117881215721449640[249] = 0.0;
   out_3117881215721449640[250] = 0.0;
   out_3117881215721449640[251] = 0.0;
   out_3117881215721449640[252] = 0.0;
   out_3117881215721449640[253] = 0.0;
   out_3117881215721449640[254] = 0.0;
   out_3117881215721449640[255] = 0.0;
   out_3117881215721449640[256] = 0.0;
   out_3117881215721449640[257] = 0.0;
   out_3117881215721449640[258] = 0.0;
   out_3117881215721449640[259] = 0.0;
   out_3117881215721449640[260] = 0.0;
   out_3117881215721449640[261] = 0.0;
   out_3117881215721449640[262] = 0.0;
   out_3117881215721449640[263] = 0.0;
   out_3117881215721449640[264] = 0.0;
   out_3117881215721449640[265] = 0.0;
   out_3117881215721449640[266] = 1.0;
   out_3117881215721449640[267] = 0.0;
   out_3117881215721449640[268] = 0.0;
   out_3117881215721449640[269] = 0.0;
   out_3117881215721449640[270] = 0.0;
   out_3117881215721449640[271] = 0.0;
   out_3117881215721449640[272] = 0.0;
   out_3117881215721449640[273] = 0.0;
   out_3117881215721449640[274] = 0.0;
   out_3117881215721449640[275] = 0.0;
   out_3117881215721449640[276] = 0.0;
   out_3117881215721449640[277] = 0.0;
   out_3117881215721449640[278] = 0.0;
   out_3117881215721449640[279] = 0.0;
   out_3117881215721449640[280] = 0.0;
   out_3117881215721449640[281] = 0.0;
   out_3117881215721449640[282] = 0.0;
   out_3117881215721449640[283] = 0.0;
   out_3117881215721449640[284] = 0.0;
   out_3117881215721449640[285] = 1.0;
   out_3117881215721449640[286] = 0.0;
   out_3117881215721449640[287] = 0.0;
   out_3117881215721449640[288] = 0.0;
   out_3117881215721449640[289] = 0.0;
   out_3117881215721449640[290] = 0.0;
   out_3117881215721449640[291] = 0.0;
   out_3117881215721449640[292] = 0.0;
   out_3117881215721449640[293] = 0.0;
   out_3117881215721449640[294] = 0.0;
   out_3117881215721449640[295] = 0.0;
   out_3117881215721449640[296] = 0.0;
   out_3117881215721449640[297] = 0.0;
   out_3117881215721449640[298] = 0.0;
   out_3117881215721449640[299] = 0.0;
   out_3117881215721449640[300] = 0.0;
   out_3117881215721449640[301] = 0.0;
   out_3117881215721449640[302] = 0.0;
   out_3117881215721449640[303] = 0.0;
   out_3117881215721449640[304] = 1.0;
   out_3117881215721449640[305] = 0.0;
   out_3117881215721449640[306] = 0.0;
   out_3117881215721449640[307] = 0.0;
   out_3117881215721449640[308] = 0.0;
   out_3117881215721449640[309] = 0.0;
   out_3117881215721449640[310] = 0.0;
   out_3117881215721449640[311] = 0.0;
   out_3117881215721449640[312] = 0.0;
   out_3117881215721449640[313] = 0.0;
   out_3117881215721449640[314] = 0.0;
   out_3117881215721449640[315] = 0.0;
   out_3117881215721449640[316] = 0.0;
   out_3117881215721449640[317] = 0.0;
   out_3117881215721449640[318] = 0.0;
   out_3117881215721449640[319] = 0.0;
   out_3117881215721449640[320] = 0.0;
   out_3117881215721449640[321] = 0.0;
   out_3117881215721449640[322] = 0.0;
   out_3117881215721449640[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_700662443455454403) {
   out_700662443455454403[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_700662443455454403[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_700662443455454403[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_700662443455454403[3] = dt*state[12] + state[3];
   out_700662443455454403[4] = dt*state[13] + state[4];
   out_700662443455454403[5] = dt*state[14] + state[5];
   out_700662443455454403[6] = state[6];
   out_700662443455454403[7] = state[7];
   out_700662443455454403[8] = state[8];
   out_700662443455454403[9] = state[9];
   out_700662443455454403[10] = state[10];
   out_700662443455454403[11] = state[11];
   out_700662443455454403[12] = state[12];
   out_700662443455454403[13] = state[13];
   out_700662443455454403[14] = state[14];
   out_700662443455454403[15] = state[15];
   out_700662443455454403[16] = state[16];
   out_700662443455454403[17] = state[17];
}
void F_fun(double *state, double dt, double *out_619818181955587961) {
   out_619818181955587961[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_619818181955587961[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_619818181955587961[2] = 0;
   out_619818181955587961[3] = 0;
   out_619818181955587961[4] = 0;
   out_619818181955587961[5] = 0;
   out_619818181955587961[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_619818181955587961[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_619818181955587961[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_619818181955587961[9] = 0;
   out_619818181955587961[10] = 0;
   out_619818181955587961[11] = 0;
   out_619818181955587961[12] = 0;
   out_619818181955587961[13] = 0;
   out_619818181955587961[14] = 0;
   out_619818181955587961[15] = 0;
   out_619818181955587961[16] = 0;
   out_619818181955587961[17] = 0;
   out_619818181955587961[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_619818181955587961[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_619818181955587961[20] = 0;
   out_619818181955587961[21] = 0;
   out_619818181955587961[22] = 0;
   out_619818181955587961[23] = 0;
   out_619818181955587961[24] = 0;
   out_619818181955587961[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_619818181955587961[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_619818181955587961[27] = 0;
   out_619818181955587961[28] = 0;
   out_619818181955587961[29] = 0;
   out_619818181955587961[30] = 0;
   out_619818181955587961[31] = 0;
   out_619818181955587961[32] = 0;
   out_619818181955587961[33] = 0;
   out_619818181955587961[34] = 0;
   out_619818181955587961[35] = 0;
   out_619818181955587961[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_619818181955587961[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_619818181955587961[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_619818181955587961[39] = 0;
   out_619818181955587961[40] = 0;
   out_619818181955587961[41] = 0;
   out_619818181955587961[42] = 0;
   out_619818181955587961[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_619818181955587961[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_619818181955587961[45] = 0;
   out_619818181955587961[46] = 0;
   out_619818181955587961[47] = 0;
   out_619818181955587961[48] = 0;
   out_619818181955587961[49] = 0;
   out_619818181955587961[50] = 0;
   out_619818181955587961[51] = 0;
   out_619818181955587961[52] = 0;
   out_619818181955587961[53] = 0;
   out_619818181955587961[54] = 0;
   out_619818181955587961[55] = 0;
   out_619818181955587961[56] = 0;
   out_619818181955587961[57] = 1;
   out_619818181955587961[58] = 0;
   out_619818181955587961[59] = 0;
   out_619818181955587961[60] = 0;
   out_619818181955587961[61] = 0;
   out_619818181955587961[62] = 0;
   out_619818181955587961[63] = 0;
   out_619818181955587961[64] = 0;
   out_619818181955587961[65] = 0;
   out_619818181955587961[66] = dt;
   out_619818181955587961[67] = 0;
   out_619818181955587961[68] = 0;
   out_619818181955587961[69] = 0;
   out_619818181955587961[70] = 0;
   out_619818181955587961[71] = 0;
   out_619818181955587961[72] = 0;
   out_619818181955587961[73] = 0;
   out_619818181955587961[74] = 0;
   out_619818181955587961[75] = 0;
   out_619818181955587961[76] = 1;
   out_619818181955587961[77] = 0;
   out_619818181955587961[78] = 0;
   out_619818181955587961[79] = 0;
   out_619818181955587961[80] = 0;
   out_619818181955587961[81] = 0;
   out_619818181955587961[82] = 0;
   out_619818181955587961[83] = 0;
   out_619818181955587961[84] = 0;
   out_619818181955587961[85] = dt;
   out_619818181955587961[86] = 0;
   out_619818181955587961[87] = 0;
   out_619818181955587961[88] = 0;
   out_619818181955587961[89] = 0;
   out_619818181955587961[90] = 0;
   out_619818181955587961[91] = 0;
   out_619818181955587961[92] = 0;
   out_619818181955587961[93] = 0;
   out_619818181955587961[94] = 0;
   out_619818181955587961[95] = 1;
   out_619818181955587961[96] = 0;
   out_619818181955587961[97] = 0;
   out_619818181955587961[98] = 0;
   out_619818181955587961[99] = 0;
   out_619818181955587961[100] = 0;
   out_619818181955587961[101] = 0;
   out_619818181955587961[102] = 0;
   out_619818181955587961[103] = 0;
   out_619818181955587961[104] = dt;
   out_619818181955587961[105] = 0;
   out_619818181955587961[106] = 0;
   out_619818181955587961[107] = 0;
   out_619818181955587961[108] = 0;
   out_619818181955587961[109] = 0;
   out_619818181955587961[110] = 0;
   out_619818181955587961[111] = 0;
   out_619818181955587961[112] = 0;
   out_619818181955587961[113] = 0;
   out_619818181955587961[114] = 1;
   out_619818181955587961[115] = 0;
   out_619818181955587961[116] = 0;
   out_619818181955587961[117] = 0;
   out_619818181955587961[118] = 0;
   out_619818181955587961[119] = 0;
   out_619818181955587961[120] = 0;
   out_619818181955587961[121] = 0;
   out_619818181955587961[122] = 0;
   out_619818181955587961[123] = 0;
   out_619818181955587961[124] = 0;
   out_619818181955587961[125] = 0;
   out_619818181955587961[126] = 0;
   out_619818181955587961[127] = 0;
   out_619818181955587961[128] = 0;
   out_619818181955587961[129] = 0;
   out_619818181955587961[130] = 0;
   out_619818181955587961[131] = 0;
   out_619818181955587961[132] = 0;
   out_619818181955587961[133] = 1;
   out_619818181955587961[134] = 0;
   out_619818181955587961[135] = 0;
   out_619818181955587961[136] = 0;
   out_619818181955587961[137] = 0;
   out_619818181955587961[138] = 0;
   out_619818181955587961[139] = 0;
   out_619818181955587961[140] = 0;
   out_619818181955587961[141] = 0;
   out_619818181955587961[142] = 0;
   out_619818181955587961[143] = 0;
   out_619818181955587961[144] = 0;
   out_619818181955587961[145] = 0;
   out_619818181955587961[146] = 0;
   out_619818181955587961[147] = 0;
   out_619818181955587961[148] = 0;
   out_619818181955587961[149] = 0;
   out_619818181955587961[150] = 0;
   out_619818181955587961[151] = 0;
   out_619818181955587961[152] = 1;
   out_619818181955587961[153] = 0;
   out_619818181955587961[154] = 0;
   out_619818181955587961[155] = 0;
   out_619818181955587961[156] = 0;
   out_619818181955587961[157] = 0;
   out_619818181955587961[158] = 0;
   out_619818181955587961[159] = 0;
   out_619818181955587961[160] = 0;
   out_619818181955587961[161] = 0;
   out_619818181955587961[162] = 0;
   out_619818181955587961[163] = 0;
   out_619818181955587961[164] = 0;
   out_619818181955587961[165] = 0;
   out_619818181955587961[166] = 0;
   out_619818181955587961[167] = 0;
   out_619818181955587961[168] = 0;
   out_619818181955587961[169] = 0;
   out_619818181955587961[170] = 0;
   out_619818181955587961[171] = 1;
   out_619818181955587961[172] = 0;
   out_619818181955587961[173] = 0;
   out_619818181955587961[174] = 0;
   out_619818181955587961[175] = 0;
   out_619818181955587961[176] = 0;
   out_619818181955587961[177] = 0;
   out_619818181955587961[178] = 0;
   out_619818181955587961[179] = 0;
   out_619818181955587961[180] = 0;
   out_619818181955587961[181] = 0;
   out_619818181955587961[182] = 0;
   out_619818181955587961[183] = 0;
   out_619818181955587961[184] = 0;
   out_619818181955587961[185] = 0;
   out_619818181955587961[186] = 0;
   out_619818181955587961[187] = 0;
   out_619818181955587961[188] = 0;
   out_619818181955587961[189] = 0;
   out_619818181955587961[190] = 1;
   out_619818181955587961[191] = 0;
   out_619818181955587961[192] = 0;
   out_619818181955587961[193] = 0;
   out_619818181955587961[194] = 0;
   out_619818181955587961[195] = 0;
   out_619818181955587961[196] = 0;
   out_619818181955587961[197] = 0;
   out_619818181955587961[198] = 0;
   out_619818181955587961[199] = 0;
   out_619818181955587961[200] = 0;
   out_619818181955587961[201] = 0;
   out_619818181955587961[202] = 0;
   out_619818181955587961[203] = 0;
   out_619818181955587961[204] = 0;
   out_619818181955587961[205] = 0;
   out_619818181955587961[206] = 0;
   out_619818181955587961[207] = 0;
   out_619818181955587961[208] = 0;
   out_619818181955587961[209] = 1;
   out_619818181955587961[210] = 0;
   out_619818181955587961[211] = 0;
   out_619818181955587961[212] = 0;
   out_619818181955587961[213] = 0;
   out_619818181955587961[214] = 0;
   out_619818181955587961[215] = 0;
   out_619818181955587961[216] = 0;
   out_619818181955587961[217] = 0;
   out_619818181955587961[218] = 0;
   out_619818181955587961[219] = 0;
   out_619818181955587961[220] = 0;
   out_619818181955587961[221] = 0;
   out_619818181955587961[222] = 0;
   out_619818181955587961[223] = 0;
   out_619818181955587961[224] = 0;
   out_619818181955587961[225] = 0;
   out_619818181955587961[226] = 0;
   out_619818181955587961[227] = 0;
   out_619818181955587961[228] = 1;
   out_619818181955587961[229] = 0;
   out_619818181955587961[230] = 0;
   out_619818181955587961[231] = 0;
   out_619818181955587961[232] = 0;
   out_619818181955587961[233] = 0;
   out_619818181955587961[234] = 0;
   out_619818181955587961[235] = 0;
   out_619818181955587961[236] = 0;
   out_619818181955587961[237] = 0;
   out_619818181955587961[238] = 0;
   out_619818181955587961[239] = 0;
   out_619818181955587961[240] = 0;
   out_619818181955587961[241] = 0;
   out_619818181955587961[242] = 0;
   out_619818181955587961[243] = 0;
   out_619818181955587961[244] = 0;
   out_619818181955587961[245] = 0;
   out_619818181955587961[246] = 0;
   out_619818181955587961[247] = 1;
   out_619818181955587961[248] = 0;
   out_619818181955587961[249] = 0;
   out_619818181955587961[250] = 0;
   out_619818181955587961[251] = 0;
   out_619818181955587961[252] = 0;
   out_619818181955587961[253] = 0;
   out_619818181955587961[254] = 0;
   out_619818181955587961[255] = 0;
   out_619818181955587961[256] = 0;
   out_619818181955587961[257] = 0;
   out_619818181955587961[258] = 0;
   out_619818181955587961[259] = 0;
   out_619818181955587961[260] = 0;
   out_619818181955587961[261] = 0;
   out_619818181955587961[262] = 0;
   out_619818181955587961[263] = 0;
   out_619818181955587961[264] = 0;
   out_619818181955587961[265] = 0;
   out_619818181955587961[266] = 1;
   out_619818181955587961[267] = 0;
   out_619818181955587961[268] = 0;
   out_619818181955587961[269] = 0;
   out_619818181955587961[270] = 0;
   out_619818181955587961[271] = 0;
   out_619818181955587961[272] = 0;
   out_619818181955587961[273] = 0;
   out_619818181955587961[274] = 0;
   out_619818181955587961[275] = 0;
   out_619818181955587961[276] = 0;
   out_619818181955587961[277] = 0;
   out_619818181955587961[278] = 0;
   out_619818181955587961[279] = 0;
   out_619818181955587961[280] = 0;
   out_619818181955587961[281] = 0;
   out_619818181955587961[282] = 0;
   out_619818181955587961[283] = 0;
   out_619818181955587961[284] = 0;
   out_619818181955587961[285] = 1;
   out_619818181955587961[286] = 0;
   out_619818181955587961[287] = 0;
   out_619818181955587961[288] = 0;
   out_619818181955587961[289] = 0;
   out_619818181955587961[290] = 0;
   out_619818181955587961[291] = 0;
   out_619818181955587961[292] = 0;
   out_619818181955587961[293] = 0;
   out_619818181955587961[294] = 0;
   out_619818181955587961[295] = 0;
   out_619818181955587961[296] = 0;
   out_619818181955587961[297] = 0;
   out_619818181955587961[298] = 0;
   out_619818181955587961[299] = 0;
   out_619818181955587961[300] = 0;
   out_619818181955587961[301] = 0;
   out_619818181955587961[302] = 0;
   out_619818181955587961[303] = 0;
   out_619818181955587961[304] = 1;
   out_619818181955587961[305] = 0;
   out_619818181955587961[306] = 0;
   out_619818181955587961[307] = 0;
   out_619818181955587961[308] = 0;
   out_619818181955587961[309] = 0;
   out_619818181955587961[310] = 0;
   out_619818181955587961[311] = 0;
   out_619818181955587961[312] = 0;
   out_619818181955587961[313] = 0;
   out_619818181955587961[314] = 0;
   out_619818181955587961[315] = 0;
   out_619818181955587961[316] = 0;
   out_619818181955587961[317] = 0;
   out_619818181955587961[318] = 0;
   out_619818181955587961[319] = 0;
   out_619818181955587961[320] = 0;
   out_619818181955587961[321] = 0;
   out_619818181955587961[322] = 0;
   out_619818181955587961[323] = 1;
}
void h_4(double *state, double *unused, double *out_7282333748924576152) {
   out_7282333748924576152[0] = state[6] + state[9];
   out_7282333748924576152[1] = state[7] + state[10];
   out_7282333748924576152[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6384501191930280634) {
   out_6384501191930280634[0] = 0;
   out_6384501191930280634[1] = 0;
   out_6384501191930280634[2] = 0;
   out_6384501191930280634[3] = 0;
   out_6384501191930280634[4] = 0;
   out_6384501191930280634[5] = 0;
   out_6384501191930280634[6] = 1;
   out_6384501191930280634[7] = 0;
   out_6384501191930280634[8] = 0;
   out_6384501191930280634[9] = 1;
   out_6384501191930280634[10] = 0;
   out_6384501191930280634[11] = 0;
   out_6384501191930280634[12] = 0;
   out_6384501191930280634[13] = 0;
   out_6384501191930280634[14] = 0;
   out_6384501191930280634[15] = 0;
   out_6384501191930280634[16] = 0;
   out_6384501191930280634[17] = 0;
   out_6384501191930280634[18] = 0;
   out_6384501191930280634[19] = 0;
   out_6384501191930280634[20] = 0;
   out_6384501191930280634[21] = 0;
   out_6384501191930280634[22] = 0;
   out_6384501191930280634[23] = 0;
   out_6384501191930280634[24] = 0;
   out_6384501191930280634[25] = 1;
   out_6384501191930280634[26] = 0;
   out_6384501191930280634[27] = 0;
   out_6384501191930280634[28] = 1;
   out_6384501191930280634[29] = 0;
   out_6384501191930280634[30] = 0;
   out_6384501191930280634[31] = 0;
   out_6384501191930280634[32] = 0;
   out_6384501191930280634[33] = 0;
   out_6384501191930280634[34] = 0;
   out_6384501191930280634[35] = 0;
   out_6384501191930280634[36] = 0;
   out_6384501191930280634[37] = 0;
   out_6384501191930280634[38] = 0;
   out_6384501191930280634[39] = 0;
   out_6384501191930280634[40] = 0;
   out_6384501191930280634[41] = 0;
   out_6384501191930280634[42] = 0;
   out_6384501191930280634[43] = 0;
   out_6384501191930280634[44] = 1;
   out_6384501191930280634[45] = 0;
   out_6384501191930280634[46] = 0;
   out_6384501191930280634[47] = 1;
   out_6384501191930280634[48] = 0;
   out_6384501191930280634[49] = 0;
   out_6384501191930280634[50] = 0;
   out_6384501191930280634[51] = 0;
   out_6384501191930280634[52] = 0;
   out_6384501191930280634[53] = 0;
}
void h_10(double *state, double *unused, double *out_612235433249460658) {
   out_612235433249460658[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_612235433249460658[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_612235433249460658[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3494221895027205679) {
   out_3494221895027205679[0] = 0;
   out_3494221895027205679[1] = 9.8100000000000005*cos(state[1]);
   out_3494221895027205679[2] = 0;
   out_3494221895027205679[3] = 0;
   out_3494221895027205679[4] = -state[8];
   out_3494221895027205679[5] = state[7];
   out_3494221895027205679[6] = 0;
   out_3494221895027205679[7] = state[5];
   out_3494221895027205679[8] = -state[4];
   out_3494221895027205679[9] = 0;
   out_3494221895027205679[10] = 0;
   out_3494221895027205679[11] = 0;
   out_3494221895027205679[12] = 1;
   out_3494221895027205679[13] = 0;
   out_3494221895027205679[14] = 0;
   out_3494221895027205679[15] = 1;
   out_3494221895027205679[16] = 0;
   out_3494221895027205679[17] = 0;
   out_3494221895027205679[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3494221895027205679[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3494221895027205679[20] = 0;
   out_3494221895027205679[21] = state[8];
   out_3494221895027205679[22] = 0;
   out_3494221895027205679[23] = -state[6];
   out_3494221895027205679[24] = -state[5];
   out_3494221895027205679[25] = 0;
   out_3494221895027205679[26] = state[3];
   out_3494221895027205679[27] = 0;
   out_3494221895027205679[28] = 0;
   out_3494221895027205679[29] = 0;
   out_3494221895027205679[30] = 0;
   out_3494221895027205679[31] = 1;
   out_3494221895027205679[32] = 0;
   out_3494221895027205679[33] = 0;
   out_3494221895027205679[34] = 1;
   out_3494221895027205679[35] = 0;
   out_3494221895027205679[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3494221895027205679[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3494221895027205679[38] = 0;
   out_3494221895027205679[39] = -state[7];
   out_3494221895027205679[40] = state[6];
   out_3494221895027205679[41] = 0;
   out_3494221895027205679[42] = state[4];
   out_3494221895027205679[43] = -state[3];
   out_3494221895027205679[44] = 0;
   out_3494221895027205679[45] = 0;
   out_3494221895027205679[46] = 0;
   out_3494221895027205679[47] = 0;
   out_3494221895027205679[48] = 0;
   out_3494221895027205679[49] = 0;
   out_3494221895027205679[50] = 1;
   out_3494221895027205679[51] = 0;
   out_3494221895027205679[52] = 0;
   out_3494221895027205679[53] = 1;
}
void h_13(double *state, double *unused, double *out_2245567861189652579) {
   out_2245567861189652579[0] = state[3];
   out_2245567861189652579[1] = state[4];
   out_2245567861189652579[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8849969056446938181) {
   out_8849969056446938181[0] = 0;
   out_8849969056446938181[1] = 0;
   out_8849969056446938181[2] = 0;
   out_8849969056446938181[3] = 1;
   out_8849969056446938181[4] = 0;
   out_8849969056446938181[5] = 0;
   out_8849969056446938181[6] = 0;
   out_8849969056446938181[7] = 0;
   out_8849969056446938181[8] = 0;
   out_8849969056446938181[9] = 0;
   out_8849969056446938181[10] = 0;
   out_8849969056446938181[11] = 0;
   out_8849969056446938181[12] = 0;
   out_8849969056446938181[13] = 0;
   out_8849969056446938181[14] = 0;
   out_8849969056446938181[15] = 0;
   out_8849969056446938181[16] = 0;
   out_8849969056446938181[17] = 0;
   out_8849969056446938181[18] = 0;
   out_8849969056446938181[19] = 0;
   out_8849969056446938181[20] = 0;
   out_8849969056446938181[21] = 0;
   out_8849969056446938181[22] = 1;
   out_8849969056446938181[23] = 0;
   out_8849969056446938181[24] = 0;
   out_8849969056446938181[25] = 0;
   out_8849969056446938181[26] = 0;
   out_8849969056446938181[27] = 0;
   out_8849969056446938181[28] = 0;
   out_8849969056446938181[29] = 0;
   out_8849969056446938181[30] = 0;
   out_8849969056446938181[31] = 0;
   out_8849969056446938181[32] = 0;
   out_8849969056446938181[33] = 0;
   out_8849969056446938181[34] = 0;
   out_8849969056446938181[35] = 0;
   out_8849969056446938181[36] = 0;
   out_8849969056446938181[37] = 0;
   out_8849969056446938181[38] = 0;
   out_8849969056446938181[39] = 0;
   out_8849969056446938181[40] = 0;
   out_8849969056446938181[41] = 1;
   out_8849969056446938181[42] = 0;
   out_8849969056446938181[43] = 0;
   out_8849969056446938181[44] = 0;
   out_8849969056446938181[45] = 0;
   out_8849969056446938181[46] = 0;
   out_8849969056446938181[47] = 0;
   out_8849969056446938181[48] = 0;
   out_8849969056446938181[49] = 0;
   out_8849969056446938181[50] = 0;
   out_8849969056446938181[51] = 0;
   out_8849969056446938181[52] = 0;
   out_8849969056446938181[53] = 0;
}
void h_14(double *state, double *unused, double *out_7916201911112255990) {
   out_7916201911112255990[0] = state[6];
   out_7916201911112255990[1] = state[7];
   out_7916201911112255990[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8099002025439786453) {
   out_8099002025439786453[0] = 0;
   out_8099002025439786453[1] = 0;
   out_8099002025439786453[2] = 0;
   out_8099002025439786453[3] = 0;
   out_8099002025439786453[4] = 0;
   out_8099002025439786453[5] = 0;
   out_8099002025439786453[6] = 1;
   out_8099002025439786453[7] = 0;
   out_8099002025439786453[8] = 0;
   out_8099002025439786453[9] = 0;
   out_8099002025439786453[10] = 0;
   out_8099002025439786453[11] = 0;
   out_8099002025439786453[12] = 0;
   out_8099002025439786453[13] = 0;
   out_8099002025439786453[14] = 0;
   out_8099002025439786453[15] = 0;
   out_8099002025439786453[16] = 0;
   out_8099002025439786453[17] = 0;
   out_8099002025439786453[18] = 0;
   out_8099002025439786453[19] = 0;
   out_8099002025439786453[20] = 0;
   out_8099002025439786453[21] = 0;
   out_8099002025439786453[22] = 0;
   out_8099002025439786453[23] = 0;
   out_8099002025439786453[24] = 0;
   out_8099002025439786453[25] = 1;
   out_8099002025439786453[26] = 0;
   out_8099002025439786453[27] = 0;
   out_8099002025439786453[28] = 0;
   out_8099002025439786453[29] = 0;
   out_8099002025439786453[30] = 0;
   out_8099002025439786453[31] = 0;
   out_8099002025439786453[32] = 0;
   out_8099002025439786453[33] = 0;
   out_8099002025439786453[34] = 0;
   out_8099002025439786453[35] = 0;
   out_8099002025439786453[36] = 0;
   out_8099002025439786453[37] = 0;
   out_8099002025439786453[38] = 0;
   out_8099002025439786453[39] = 0;
   out_8099002025439786453[40] = 0;
   out_8099002025439786453[41] = 0;
   out_8099002025439786453[42] = 0;
   out_8099002025439786453[43] = 0;
   out_8099002025439786453[44] = 1;
   out_8099002025439786453[45] = 0;
   out_8099002025439786453[46] = 0;
   out_8099002025439786453[47] = 0;
   out_8099002025439786453[48] = 0;
   out_8099002025439786453[49] = 0;
   out_8099002025439786453[50] = 0;
   out_8099002025439786453[51] = 0;
   out_8099002025439786453[52] = 0;
   out_8099002025439786453[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5091660165595542600) {
  err_fun(nom_x, delta_x, out_5091660165595542600);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_828551828041337701) {
  inv_err_fun(nom_x, true_x, out_828551828041337701);
}
void pose_H_mod_fun(double *state, double *out_3117881215721449640) {
  H_mod_fun(state, out_3117881215721449640);
}
void pose_f_fun(double *state, double dt, double *out_700662443455454403) {
  f_fun(state,  dt, out_700662443455454403);
}
void pose_F_fun(double *state, double dt, double *out_619818181955587961) {
  F_fun(state,  dt, out_619818181955587961);
}
void pose_h_4(double *state, double *unused, double *out_7282333748924576152) {
  h_4(state, unused, out_7282333748924576152);
}
void pose_H_4(double *state, double *unused, double *out_6384501191930280634) {
  H_4(state, unused, out_6384501191930280634);
}
void pose_h_10(double *state, double *unused, double *out_612235433249460658) {
  h_10(state, unused, out_612235433249460658);
}
void pose_H_10(double *state, double *unused, double *out_3494221895027205679) {
  H_10(state, unused, out_3494221895027205679);
}
void pose_h_13(double *state, double *unused, double *out_2245567861189652579) {
  h_13(state, unused, out_2245567861189652579);
}
void pose_H_13(double *state, double *unused, double *out_8849969056446938181) {
  H_13(state, unused, out_8849969056446938181);
}
void pose_h_14(double *state, double *unused, double *out_7916201911112255990) {
  h_14(state, unused, out_7916201911112255990);
}
void pose_H_14(double *state, double *unused, double *out_8099002025439786453) {
  H_14(state, unused, out_8099002025439786453);
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
