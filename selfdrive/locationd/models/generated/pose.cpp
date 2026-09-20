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
void err_fun(double *nom_x, double *delta_x, double *out_6202662645191369) {
   out_6202662645191369[0] = delta_x[0] + nom_x[0];
   out_6202662645191369[1] = delta_x[1] + nom_x[1];
   out_6202662645191369[2] = delta_x[2] + nom_x[2];
   out_6202662645191369[3] = delta_x[3] + nom_x[3];
   out_6202662645191369[4] = delta_x[4] + nom_x[4];
   out_6202662645191369[5] = delta_x[5] + nom_x[5];
   out_6202662645191369[6] = delta_x[6] + nom_x[6];
   out_6202662645191369[7] = delta_x[7] + nom_x[7];
   out_6202662645191369[8] = delta_x[8] + nom_x[8];
   out_6202662645191369[9] = delta_x[9] + nom_x[9];
   out_6202662645191369[10] = delta_x[10] + nom_x[10];
   out_6202662645191369[11] = delta_x[11] + nom_x[11];
   out_6202662645191369[12] = delta_x[12] + nom_x[12];
   out_6202662645191369[13] = delta_x[13] + nom_x[13];
   out_6202662645191369[14] = delta_x[14] + nom_x[14];
   out_6202662645191369[15] = delta_x[15] + nom_x[15];
   out_6202662645191369[16] = delta_x[16] + nom_x[16];
   out_6202662645191369[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5065890083902176780) {
   out_5065890083902176780[0] = -nom_x[0] + true_x[0];
   out_5065890083902176780[1] = -nom_x[1] + true_x[1];
   out_5065890083902176780[2] = -nom_x[2] + true_x[2];
   out_5065890083902176780[3] = -nom_x[3] + true_x[3];
   out_5065890083902176780[4] = -nom_x[4] + true_x[4];
   out_5065890083902176780[5] = -nom_x[5] + true_x[5];
   out_5065890083902176780[6] = -nom_x[6] + true_x[6];
   out_5065890083902176780[7] = -nom_x[7] + true_x[7];
   out_5065890083902176780[8] = -nom_x[8] + true_x[8];
   out_5065890083902176780[9] = -nom_x[9] + true_x[9];
   out_5065890083902176780[10] = -nom_x[10] + true_x[10];
   out_5065890083902176780[11] = -nom_x[11] + true_x[11];
   out_5065890083902176780[12] = -nom_x[12] + true_x[12];
   out_5065890083902176780[13] = -nom_x[13] + true_x[13];
   out_5065890083902176780[14] = -nom_x[14] + true_x[14];
   out_5065890083902176780[15] = -nom_x[15] + true_x[15];
   out_5065890083902176780[16] = -nom_x[16] + true_x[16];
   out_5065890083902176780[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4147804714257678696) {
   out_4147804714257678696[0] = 1.0;
   out_4147804714257678696[1] = 0.0;
   out_4147804714257678696[2] = 0.0;
   out_4147804714257678696[3] = 0.0;
   out_4147804714257678696[4] = 0.0;
   out_4147804714257678696[5] = 0.0;
   out_4147804714257678696[6] = 0.0;
   out_4147804714257678696[7] = 0.0;
   out_4147804714257678696[8] = 0.0;
   out_4147804714257678696[9] = 0.0;
   out_4147804714257678696[10] = 0.0;
   out_4147804714257678696[11] = 0.0;
   out_4147804714257678696[12] = 0.0;
   out_4147804714257678696[13] = 0.0;
   out_4147804714257678696[14] = 0.0;
   out_4147804714257678696[15] = 0.0;
   out_4147804714257678696[16] = 0.0;
   out_4147804714257678696[17] = 0.0;
   out_4147804714257678696[18] = 0.0;
   out_4147804714257678696[19] = 1.0;
   out_4147804714257678696[20] = 0.0;
   out_4147804714257678696[21] = 0.0;
   out_4147804714257678696[22] = 0.0;
   out_4147804714257678696[23] = 0.0;
   out_4147804714257678696[24] = 0.0;
   out_4147804714257678696[25] = 0.0;
   out_4147804714257678696[26] = 0.0;
   out_4147804714257678696[27] = 0.0;
   out_4147804714257678696[28] = 0.0;
   out_4147804714257678696[29] = 0.0;
   out_4147804714257678696[30] = 0.0;
   out_4147804714257678696[31] = 0.0;
   out_4147804714257678696[32] = 0.0;
   out_4147804714257678696[33] = 0.0;
   out_4147804714257678696[34] = 0.0;
   out_4147804714257678696[35] = 0.0;
   out_4147804714257678696[36] = 0.0;
   out_4147804714257678696[37] = 0.0;
   out_4147804714257678696[38] = 1.0;
   out_4147804714257678696[39] = 0.0;
   out_4147804714257678696[40] = 0.0;
   out_4147804714257678696[41] = 0.0;
   out_4147804714257678696[42] = 0.0;
   out_4147804714257678696[43] = 0.0;
   out_4147804714257678696[44] = 0.0;
   out_4147804714257678696[45] = 0.0;
   out_4147804714257678696[46] = 0.0;
   out_4147804714257678696[47] = 0.0;
   out_4147804714257678696[48] = 0.0;
   out_4147804714257678696[49] = 0.0;
   out_4147804714257678696[50] = 0.0;
   out_4147804714257678696[51] = 0.0;
   out_4147804714257678696[52] = 0.0;
   out_4147804714257678696[53] = 0.0;
   out_4147804714257678696[54] = 0.0;
   out_4147804714257678696[55] = 0.0;
   out_4147804714257678696[56] = 0.0;
   out_4147804714257678696[57] = 1.0;
   out_4147804714257678696[58] = 0.0;
   out_4147804714257678696[59] = 0.0;
   out_4147804714257678696[60] = 0.0;
   out_4147804714257678696[61] = 0.0;
   out_4147804714257678696[62] = 0.0;
   out_4147804714257678696[63] = 0.0;
   out_4147804714257678696[64] = 0.0;
   out_4147804714257678696[65] = 0.0;
   out_4147804714257678696[66] = 0.0;
   out_4147804714257678696[67] = 0.0;
   out_4147804714257678696[68] = 0.0;
   out_4147804714257678696[69] = 0.0;
   out_4147804714257678696[70] = 0.0;
   out_4147804714257678696[71] = 0.0;
   out_4147804714257678696[72] = 0.0;
   out_4147804714257678696[73] = 0.0;
   out_4147804714257678696[74] = 0.0;
   out_4147804714257678696[75] = 0.0;
   out_4147804714257678696[76] = 1.0;
   out_4147804714257678696[77] = 0.0;
   out_4147804714257678696[78] = 0.0;
   out_4147804714257678696[79] = 0.0;
   out_4147804714257678696[80] = 0.0;
   out_4147804714257678696[81] = 0.0;
   out_4147804714257678696[82] = 0.0;
   out_4147804714257678696[83] = 0.0;
   out_4147804714257678696[84] = 0.0;
   out_4147804714257678696[85] = 0.0;
   out_4147804714257678696[86] = 0.0;
   out_4147804714257678696[87] = 0.0;
   out_4147804714257678696[88] = 0.0;
   out_4147804714257678696[89] = 0.0;
   out_4147804714257678696[90] = 0.0;
   out_4147804714257678696[91] = 0.0;
   out_4147804714257678696[92] = 0.0;
   out_4147804714257678696[93] = 0.0;
   out_4147804714257678696[94] = 0.0;
   out_4147804714257678696[95] = 1.0;
   out_4147804714257678696[96] = 0.0;
   out_4147804714257678696[97] = 0.0;
   out_4147804714257678696[98] = 0.0;
   out_4147804714257678696[99] = 0.0;
   out_4147804714257678696[100] = 0.0;
   out_4147804714257678696[101] = 0.0;
   out_4147804714257678696[102] = 0.0;
   out_4147804714257678696[103] = 0.0;
   out_4147804714257678696[104] = 0.0;
   out_4147804714257678696[105] = 0.0;
   out_4147804714257678696[106] = 0.0;
   out_4147804714257678696[107] = 0.0;
   out_4147804714257678696[108] = 0.0;
   out_4147804714257678696[109] = 0.0;
   out_4147804714257678696[110] = 0.0;
   out_4147804714257678696[111] = 0.0;
   out_4147804714257678696[112] = 0.0;
   out_4147804714257678696[113] = 0.0;
   out_4147804714257678696[114] = 1.0;
   out_4147804714257678696[115] = 0.0;
   out_4147804714257678696[116] = 0.0;
   out_4147804714257678696[117] = 0.0;
   out_4147804714257678696[118] = 0.0;
   out_4147804714257678696[119] = 0.0;
   out_4147804714257678696[120] = 0.0;
   out_4147804714257678696[121] = 0.0;
   out_4147804714257678696[122] = 0.0;
   out_4147804714257678696[123] = 0.0;
   out_4147804714257678696[124] = 0.0;
   out_4147804714257678696[125] = 0.0;
   out_4147804714257678696[126] = 0.0;
   out_4147804714257678696[127] = 0.0;
   out_4147804714257678696[128] = 0.0;
   out_4147804714257678696[129] = 0.0;
   out_4147804714257678696[130] = 0.0;
   out_4147804714257678696[131] = 0.0;
   out_4147804714257678696[132] = 0.0;
   out_4147804714257678696[133] = 1.0;
   out_4147804714257678696[134] = 0.0;
   out_4147804714257678696[135] = 0.0;
   out_4147804714257678696[136] = 0.0;
   out_4147804714257678696[137] = 0.0;
   out_4147804714257678696[138] = 0.0;
   out_4147804714257678696[139] = 0.0;
   out_4147804714257678696[140] = 0.0;
   out_4147804714257678696[141] = 0.0;
   out_4147804714257678696[142] = 0.0;
   out_4147804714257678696[143] = 0.0;
   out_4147804714257678696[144] = 0.0;
   out_4147804714257678696[145] = 0.0;
   out_4147804714257678696[146] = 0.0;
   out_4147804714257678696[147] = 0.0;
   out_4147804714257678696[148] = 0.0;
   out_4147804714257678696[149] = 0.0;
   out_4147804714257678696[150] = 0.0;
   out_4147804714257678696[151] = 0.0;
   out_4147804714257678696[152] = 1.0;
   out_4147804714257678696[153] = 0.0;
   out_4147804714257678696[154] = 0.0;
   out_4147804714257678696[155] = 0.0;
   out_4147804714257678696[156] = 0.0;
   out_4147804714257678696[157] = 0.0;
   out_4147804714257678696[158] = 0.0;
   out_4147804714257678696[159] = 0.0;
   out_4147804714257678696[160] = 0.0;
   out_4147804714257678696[161] = 0.0;
   out_4147804714257678696[162] = 0.0;
   out_4147804714257678696[163] = 0.0;
   out_4147804714257678696[164] = 0.0;
   out_4147804714257678696[165] = 0.0;
   out_4147804714257678696[166] = 0.0;
   out_4147804714257678696[167] = 0.0;
   out_4147804714257678696[168] = 0.0;
   out_4147804714257678696[169] = 0.0;
   out_4147804714257678696[170] = 0.0;
   out_4147804714257678696[171] = 1.0;
   out_4147804714257678696[172] = 0.0;
   out_4147804714257678696[173] = 0.0;
   out_4147804714257678696[174] = 0.0;
   out_4147804714257678696[175] = 0.0;
   out_4147804714257678696[176] = 0.0;
   out_4147804714257678696[177] = 0.0;
   out_4147804714257678696[178] = 0.0;
   out_4147804714257678696[179] = 0.0;
   out_4147804714257678696[180] = 0.0;
   out_4147804714257678696[181] = 0.0;
   out_4147804714257678696[182] = 0.0;
   out_4147804714257678696[183] = 0.0;
   out_4147804714257678696[184] = 0.0;
   out_4147804714257678696[185] = 0.0;
   out_4147804714257678696[186] = 0.0;
   out_4147804714257678696[187] = 0.0;
   out_4147804714257678696[188] = 0.0;
   out_4147804714257678696[189] = 0.0;
   out_4147804714257678696[190] = 1.0;
   out_4147804714257678696[191] = 0.0;
   out_4147804714257678696[192] = 0.0;
   out_4147804714257678696[193] = 0.0;
   out_4147804714257678696[194] = 0.0;
   out_4147804714257678696[195] = 0.0;
   out_4147804714257678696[196] = 0.0;
   out_4147804714257678696[197] = 0.0;
   out_4147804714257678696[198] = 0.0;
   out_4147804714257678696[199] = 0.0;
   out_4147804714257678696[200] = 0.0;
   out_4147804714257678696[201] = 0.0;
   out_4147804714257678696[202] = 0.0;
   out_4147804714257678696[203] = 0.0;
   out_4147804714257678696[204] = 0.0;
   out_4147804714257678696[205] = 0.0;
   out_4147804714257678696[206] = 0.0;
   out_4147804714257678696[207] = 0.0;
   out_4147804714257678696[208] = 0.0;
   out_4147804714257678696[209] = 1.0;
   out_4147804714257678696[210] = 0.0;
   out_4147804714257678696[211] = 0.0;
   out_4147804714257678696[212] = 0.0;
   out_4147804714257678696[213] = 0.0;
   out_4147804714257678696[214] = 0.0;
   out_4147804714257678696[215] = 0.0;
   out_4147804714257678696[216] = 0.0;
   out_4147804714257678696[217] = 0.0;
   out_4147804714257678696[218] = 0.0;
   out_4147804714257678696[219] = 0.0;
   out_4147804714257678696[220] = 0.0;
   out_4147804714257678696[221] = 0.0;
   out_4147804714257678696[222] = 0.0;
   out_4147804714257678696[223] = 0.0;
   out_4147804714257678696[224] = 0.0;
   out_4147804714257678696[225] = 0.0;
   out_4147804714257678696[226] = 0.0;
   out_4147804714257678696[227] = 0.0;
   out_4147804714257678696[228] = 1.0;
   out_4147804714257678696[229] = 0.0;
   out_4147804714257678696[230] = 0.0;
   out_4147804714257678696[231] = 0.0;
   out_4147804714257678696[232] = 0.0;
   out_4147804714257678696[233] = 0.0;
   out_4147804714257678696[234] = 0.0;
   out_4147804714257678696[235] = 0.0;
   out_4147804714257678696[236] = 0.0;
   out_4147804714257678696[237] = 0.0;
   out_4147804714257678696[238] = 0.0;
   out_4147804714257678696[239] = 0.0;
   out_4147804714257678696[240] = 0.0;
   out_4147804714257678696[241] = 0.0;
   out_4147804714257678696[242] = 0.0;
   out_4147804714257678696[243] = 0.0;
   out_4147804714257678696[244] = 0.0;
   out_4147804714257678696[245] = 0.0;
   out_4147804714257678696[246] = 0.0;
   out_4147804714257678696[247] = 1.0;
   out_4147804714257678696[248] = 0.0;
   out_4147804714257678696[249] = 0.0;
   out_4147804714257678696[250] = 0.0;
   out_4147804714257678696[251] = 0.0;
   out_4147804714257678696[252] = 0.0;
   out_4147804714257678696[253] = 0.0;
   out_4147804714257678696[254] = 0.0;
   out_4147804714257678696[255] = 0.0;
   out_4147804714257678696[256] = 0.0;
   out_4147804714257678696[257] = 0.0;
   out_4147804714257678696[258] = 0.0;
   out_4147804714257678696[259] = 0.0;
   out_4147804714257678696[260] = 0.0;
   out_4147804714257678696[261] = 0.0;
   out_4147804714257678696[262] = 0.0;
   out_4147804714257678696[263] = 0.0;
   out_4147804714257678696[264] = 0.0;
   out_4147804714257678696[265] = 0.0;
   out_4147804714257678696[266] = 1.0;
   out_4147804714257678696[267] = 0.0;
   out_4147804714257678696[268] = 0.0;
   out_4147804714257678696[269] = 0.0;
   out_4147804714257678696[270] = 0.0;
   out_4147804714257678696[271] = 0.0;
   out_4147804714257678696[272] = 0.0;
   out_4147804714257678696[273] = 0.0;
   out_4147804714257678696[274] = 0.0;
   out_4147804714257678696[275] = 0.0;
   out_4147804714257678696[276] = 0.0;
   out_4147804714257678696[277] = 0.0;
   out_4147804714257678696[278] = 0.0;
   out_4147804714257678696[279] = 0.0;
   out_4147804714257678696[280] = 0.0;
   out_4147804714257678696[281] = 0.0;
   out_4147804714257678696[282] = 0.0;
   out_4147804714257678696[283] = 0.0;
   out_4147804714257678696[284] = 0.0;
   out_4147804714257678696[285] = 1.0;
   out_4147804714257678696[286] = 0.0;
   out_4147804714257678696[287] = 0.0;
   out_4147804714257678696[288] = 0.0;
   out_4147804714257678696[289] = 0.0;
   out_4147804714257678696[290] = 0.0;
   out_4147804714257678696[291] = 0.0;
   out_4147804714257678696[292] = 0.0;
   out_4147804714257678696[293] = 0.0;
   out_4147804714257678696[294] = 0.0;
   out_4147804714257678696[295] = 0.0;
   out_4147804714257678696[296] = 0.0;
   out_4147804714257678696[297] = 0.0;
   out_4147804714257678696[298] = 0.0;
   out_4147804714257678696[299] = 0.0;
   out_4147804714257678696[300] = 0.0;
   out_4147804714257678696[301] = 0.0;
   out_4147804714257678696[302] = 0.0;
   out_4147804714257678696[303] = 0.0;
   out_4147804714257678696[304] = 1.0;
   out_4147804714257678696[305] = 0.0;
   out_4147804714257678696[306] = 0.0;
   out_4147804714257678696[307] = 0.0;
   out_4147804714257678696[308] = 0.0;
   out_4147804714257678696[309] = 0.0;
   out_4147804714257678696[310] = 0.0;
   out_4147804714257678696[311] = 0.0;
   out_4147804714257678696[312] = 0.0;
   out_4147804714257678696[313] = 0.0;
   out_4147804714257678696[314] = 0.0;
   out_4147804714257678696[315] = 0.0;
   out_4147804714257678696[316] = 0.0;
   out_4147804714257678696[317] = 0.0;
   out_4147804714257678696[318] = 0.0;
   out_4147804714257678696[319] = 0.0;
   out_4147804714257678696[320] = 0.0;
   out_4147804714257678696[321] = 0.0;
   out_4147804714257678696[322] = 0.0;
   out_4147804714257678696[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_134451283192963896) {
   out_134451283192963896[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_134451283192963896[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_134451283192963896[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_134451283192963896[3] = dt*state[12] + state[3];
   out_134451283192963896[4] = dt*state[13] + state[4];
   out_134451283192963896[5] = dt*state[14] + state[5];
   out_134451283192963896[6] = state[6];
   out_134451283192963896[7] = state[7];
   out_134451283192963896[8] = state[8];
   out_134451283192963896[9] = state[9];
   out_134451283192963896[10] = state[10];
   out_134451283192963896[11] = state[11];
   out_134451283192963896[12] = state[12];
   out_134451283192963896[13] = state[13];
   out_134451283192963896[14] = state[14];
   out_134451283192963896[15] = state[15];
   out_134451283192963896[16] = state[16];
   out_134451283192963896[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7947855407511726470) {
   out_7947855407511726470[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7947855407511726470[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7947855407511726470[2] = 0;
   out_7947855407511726470[3] = 0;
   out_7947855407511726470[4] = 0;
   out_7947855407511726470[5] = 0;
   out_7947855407511726470[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7947855407511726470[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7947855407511726470[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7947855407511726470[9] = 0;
   out_7947855407511726470[10] = 0;
   out_7947855407511726470[11] = 0;
   out_7947855407511726470[12] = 0;
   out_7947855407511726470[13] = 0;
   out_7947855407511726470[14] = 0;
   out_7947855407511726470[15] = 0;
   out_7947855407511726470[16] = 0;
   out_7947855407511726470[17] = 0;
   out_7947855407511726470[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7947855407511726470[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7947855407511726470[20] = 0;
   out_7947855407511726470[21] = 0;
   out_7947855407511726470[22] = 0;
   out_7947855407511726470[23] = 0;
   out_7947855407511726470[24] = 0;
   out_7947855407511726470[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7947855407511726470[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7947855407511726470[27] = 0;
   out_7947855407511726470[28] = 0;
   out_7947855407511726470[29] = 0;
   out_7947855407511726470[30] = 0;
   out_7947855407511726470[31] = 0;
   out_7947855407511726470[32] = 0;
   out_7947855407511726470[33] = 0;
   out_7947855407511726470[34] = 0;
   out_7947855407511726470[35] = 0;
   out_7947855407511726470[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7947855407511726470[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7947855407511726470[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7947855407511726470[39] = 0;
   out_7947855407511726470[40] = 0;
   out_7947855407511726470[41] = 0;
   out_7947855407511726470[42] = 0;
   out_7947855407511726470[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7947855407511726470[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7947855407511726470[45] = 0;
   out_7947855407511726470[46] = 0;
   out_7947855407511726470[47] = 0;
   out_7947855407511726470[48] = 0;
   out_7947855407511726470[49] = 0;
   out_7947855407511726470[50] = 0;
   out_7947855407511726470[51] = 0;
   out_7947855407511726470[52] = 0;
   out_7947855407511726470[53] = 0;
   out_7947855407511726470[54] = 0;
   out_7947855407511726470[55] = 0;
   out_7947855407511726470[56] = 0;
   out_7947855407511726470[57] = 1;
   out_7947855407511726470[58] = 0;
   out_7947855407511726470[59] = 0;
   out_7947855407511726470[60] = 0;
   out_7947855407511726470[61] = 0;
   out_7947855407511726470[62] = 0;
   out_7947855407511726470[63] = 0;
   out_7947855407511726470[64] = 0;
   out_7947855407511726470[65] = 0;
   out_7947855407511726470[66] = dt;
   out_7947855407511726470[67] = 0;
   out_7947855407511726470[68] = 0;
   out_7947855407511726470[69] = 0;
   out_7947855407511726470[70] = 0;
   out_7947855407511726470[71] = 0;
   out_7947855407511726470[72] = 0;
   out_7947855407511726470[73] = 0;
   out_7947855407511726470[74] = 0;
   out_7947855407511726470[75] = 0;
   out_7947855407511726470[76] = 1;
   out_7947855407511726470[77] = 0;
   out_7947855407511726470[78] = 0;
   out_7947855407511726470[79] = 0;
   out_7947855407511726470[80] = 0;
   out_7947855407511726470[81] = 0;
   out_7947855407511726470[82] = 0;
   out_7947855407511726470[83] = 0;
   out_7947855407511726470[84] = 0;
   out_7947855407511726470[85] = dt;
   out_7947855407511726470[86] = 0;
   out_7947855407511726470[87] = 0;
   out_7947855407511726470[88] = 0;
   out_7947855407511726470[89] = 0;
   out_7947855407511726470[90] = 0;
   out_7947855407511726470[91] = 0;
   out_7947855407511726470[92] = 0;
   out_7947855407511726470[93] = 0;
   out_7947855407511726470[94] = 0;
   out_7947855407511726470[95] = 1;
   out_7947855407511726470[96] = 0;
   out_7947855407511726470[97] = 0;
   out_7947855407511726470[98] = 0;
   out_7947855407511726470[99] = 0;
   out_7947855407511726470[100] = 0;
   out_7947855407511726470[101] = 0;
   out_7947855407511726470[102] = 0;
   out_7947855407511726470[103] = 0;
   out_7947855407511726470[104] = dt;
   out_7947855407511726470[105] = 0;
   out_7947855407511726470[106] = 0;
   out_7947855407511726470[107] = 0;
   out_7947855407511726470[108] = 0;
   out_7947855407511726470[109] = 0;
   out_7947855407511726470[110] = 0;
   out_7947855407511726470[111] = 0;
   out_7947855407511726470[112] = 0;
   out_7947855407511726470[113] = 0;
   out_7947855407511726470[114] = 1;
   out_7947855407511726470[115] = 0;
   out_7947855407511726470[116] = 0;
   out_7947855407511726470[117] = 0;
   out_7947855407511726470[118] = 0;
   out_7947855407511726470[119] = 0;
   out_7947855407511726470[120] = 0;
   out_7947855407511726470[121] = 0;
   out_7947855407511726470[122] = 0;
   out_7947855407511726470[123] = 0;
   out_7947855407511726470[124] = 0;
   out_7947855407511726470[125] = 0;
   out_7947855407511726470[126] = 0;
   out_7947855407511726470[127] = 0;
   out_7947855407511726470[128] = 0;
   out_7947855407511726470[129] = 0;
   out_7947855407511726470[130] = 0;
   out_7947855407511726470[131] = 0;
   out_7947855407511726470[132] = 0;
   out_7947855407511726470[133] = 1;
   out_7947855407511726470[134] = 0;
   out_7947855407511726470[135] = 0;
   out_7947855407511726470[136] = 0;
   out_7947855407511726470[137] = 0;
   out_7947855407511726470[138] = 0;
   out_7947855407511726470[139] = 0;
   out_7947855407511726470[140] = 0;
   out_7947855407511726470[141] = 0;
   out_7947855407511726470[142] = 0;
   out_7947855407511726470[143] = 0;
   out_7947855407511726470[144] = 0;
   out_7947855407511726470[145] = 0;
   out_7947855407511726470[146] = 0;
   out_7947855407511726470[147] = 0;
   out_7947855407511726470[148] = 0;
   out_7947855407511726470[149] = 0;
   out_7947855407511726470[150] = 0;
   out_7947855407511726470[151] = 0;
   out_7947855407511726470[152] = 1;
   out_7947855407511726470[153] = 0;
   out_7947855407511726470[154] = 0;
   out_7947855407511726470[155] = 0;
   out_7947855407511726470[156] = 0;
   out_7947855407511726470[157] = 0;
   out_7947855407511726470[158] = 0;
   out_7947855407511726470[159] = 0;
   out_7947855407511726470[160] = 0;
   out_7947855407511726470[161] = 0;
   out_7947855407511726470[162] = 0;
   out_7947855407511726470[163] = 0;
   out_7947855407511726470[164] = 0;
   out_7947855407511726470[165] = 0;
   out_7947855407511726470[166] = 0;
   out_7947855407511726470[167] = 0;
   out_7947855407511726470[168] = 0;
   out_7947855407511726470[169] = 0;
   out_7947855407511726470[170] = 0;
   out_7947855407511726470[171] = 1;
   out_7947855407511726470[172] = 0;
   out_7947855407511726470[173] = 0;
   out_7947855407511726470[174] = 0;
   out_7947855407511726470[175] = 0;
   out_7947855407511726470[176] = 0;
   out_7947855407511726470[177] = 0;
   out_7947855407511726470[178] = 0;
   out_7947855407511726470[179] = 0;
   out_7947855407511726470[180] = 0;
   out_7947855407511726470[181] = 0;
   out_7947855407511726470[182] = 0;
   out_7947855407511726470[183] = 0;
   out_7947855407511726470[184] = 0;
   out_7947855407511726470[185] = 0;
   out_7947855407511726470[186] = 0;
   out_7947855407511726470[187] = 0;
   out_7947855407511726470[188] = 0;
   out_7947855407511726470[189] = 0;
   out_7947855407511726470[190] = 1;
   out_7947855407511726470[191] = 0;
   out_7947855407511726470[192] = 0;
   out_7947855407511726470[193] = 0;
   out_7947855407511726470[194] = 0;
   out_7947855407511726470[195] = 0;
   out_7947855407511726470[196] = 0;
   out_7947855407511726470[197] = 0;
   out_7947855407511726470[198] = 0;
   out_7947855407511726470[199] = 0;
   out_7947855407511726470[200] = 0;
   out_7947855407511726470[201] = 0;
   out_7947855407511726470[202] = 0;
   out_7947855407511726470[203] = 0;
   out_7947855407511726470[204] = 0;
   out_7947855407511726470[205] = 0;
   out_7947855407511726470[206] = 0;
   out_7947855407511726470[207] = 0;
   out_7947855407511726470[208] = 0;
   out_7947855407511726470[209] = 1;
   out_7947855407511726470[210] = 0;
   out_7947855407511726470[211] = 0;
   out_7947855407511726470[212] = 0;
   out_7947855407511726470[213] = 0;
   out_7947855407511726470[214] = 0;
   out_7947855407511726470[215] = 0;
   out_7947855407511726470[216] = 0;
   out_7947855407511726470[217] = 0;
   out_7947855407511726470[218] = 0;
   out_7947855407511726470[219] = 0;
   out_7947855407511726470[220] = 0;
   out_7947855407511726470[221] = 0;
   out_7947855407511726470[222] = 0;
   out_7947855407511726470[223] = 0;
   out_7947855407511726470[224] = 0;
   out_7947855407511726470[225] = 0;
   out_7947855407511726470[226] = 0;
   out_7947855407511726470[227] = 0;
   out_7947855407511726470[228] = 1;
   out_7947855407511726470[229] = 0;
   out_7947855407511726470[230] = 0;
   out_7947855407511726470[231] = 0;
   out_7947855407511726470[232] = 0;
   out_7947855407511726470[233] = 0;
   out_7947855407511726470[234] = 0;
   out_7947855407511726470[235] = 0;
   out_7947855407511726470[236] = 0;
   out_7947855407511726470[237] = 0;
   out_7947855407511726470[238] = 0;
   out_7947855407511726470[239] = 0;
   out_7947855407511726470[240] = 0;
   out_7947855407511726470[241] = 0;
   out_7947855407511726470[242] = 0;
   out_7947855407511726470[243] = 0;
   out_7947855407511726470[244] = 0;
   out_7947855407511726470[245] = 0;
   out_7947855407511726470[246] = 0;
   out_7947855407511726470[247] = 1;
   out_7947855407511726470[248] = 0;
   out_7947855407511726470[249] = 0;
   out_7947855407511726470[250] = 0;
   out_7947855407511726470[251] = 0;
   out_7947855407511726470[252] = 0;
   out_7947855407511726470[253] = 0;
   out_7947855407511726470[254] = 0;
   out_7947855407511726470[255] = 0;
   out_7947855407511726470[256] = 0;
   out_7947855407511726470[257] = 0;
   out_7947855407511726470[258] = 0;
   out_7947855407511726470[259] = 0;
   out_7947855407511726470[260] = 0;
   out_7947855407511726470[261] = 0;
   out_7947855407511726470[262] = 0;
   out_7947855407511726470[263] = 0;
   out_7947855407511726470[264] = 0;
   out_7947855407511726470[265] = 0;
   out_7947855407511726470[266] = 1;
   out_7947855407511726470[267] = 0;
   out_7947855407511726470[268] = 0;
   out_7947855407511726470[269] = 0;
   out_7947855407511726470[270] = 0;
   out_7947855407511726470[271] = 0;
   out_7947855407511726470[272] = 0;
   out_7947855407511726470[273] = 0;
   out_7947855407511726470[274] = 0;
   out_7947855407511726470[275] = 0;
   out_7947855407511726470[276] = 0;
   out_7947855407511726470[277] = 0;
   out_7947855407511726470[278] = 0;
   out_7947855407511726470[279] = 0;
   out_7947855407511726470[280] = 0;
   out_7947855407511726470[281] = 0;
   out_7947855407511726470[282] = 0;
   out_7947855407511726470[283] = 0;
   out_7947855407511726470[284] = 0;
   out_7947855407511726470[285] = 1;
   out_7947855407511726470[286] = 0;
   out_7947855407511726470[287] = 0;
   out_7947855407511726470[288] = 0;
   out_7947855407511726470[289] = 0;
   out_7947855407511726470[290] = 0;
   out_7947855407511726470[291] = 0;
   out_7947855407511726470[292] = 0;
   out_7947855407511726470[293] = 0;
   out_7947855407511726470[294] = 0;
   out_7947855407511726470[295] = 0;
   out_7947855407511726470[296] = 0;
   out_7947855407511726470[297] = 0;
   out_7947855407511726470[298] = 0;
   out_7947855407511726470[299] = 0;
   out_7947855407511726470[300] = 0;
   out_7947855407511726470[301] = 0;
   out_7947855407511726470[302] = 0;
   out_7947855407511726470[303] = 0;
   out_7947855407511726470[304] = 1;
   out_7947855407511726470[305] = 0;
   out_7947855407511726470[306] = 0;
   out_7947855407511726470[307] = 0;
   out_7947855407511726470[308] = 0;
   out_7947855407511726470[309] = 0;
   out_7947855407511726470[310] = 0;
   out_7947855407511726470[311] = 0;
   out_7947855407511726470[312] = 0;
   out_7947855407511726470[313] = 0;
   out_7947855407511726470[314] = 0;
   out_7947855407511726470[315] = 0;
   out_7947855407511726470[316] = 0;
   out_7947855407511726470[317] = 0;
   out_7947855407511726470[318] = 0;
   out_7947855407511726470[319] = 0;
   out_7947855407511726470[320] = 0;
   out_7947855407511726470[321] = 0;
   out_7947855407511726470[322] = 0;
   out_7947855407511726470[323] = 1;
}
void h_4(double *state, double *unused, double *out_7278578289213708861) {
   out_7278578289213708861[0] = state[6] + state[9];
   out_7278578289213708861[1] = state[7] + state[10];
   out_7278578289213708861[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5967503440163975557) {
   out_5967503440163975557[0] = 0;
   out_5967503440163975557[1] = 0;
   out_5967503440163975557[2] = 0;
   out_5967503440163975557[3] = 0;
   out_5967503440163975557[4] = 0;
   out_5967503440163975557[5] = 0;
   out_5967503440163975557[6] = 1;
   out_5967503440163975557[7] = 0;
   out_5967503440163975557[8] = 0;
   out_5967503440163975557[9] = 1;
   out_5967503440163975557[10] = 0;
   out_5967503440163975557[11] = 0;
   out_5967503440163975557[12] = 0;
   out_5967503440163975557[13] = 0;
   out_5967503440163975557[14] = 0;
   out_5967503440163975557[15] = 0;
   out_5967503440163975557[16] = 0;
   out_5967503440163975557[17] = 0;
   out_5967503440163975557[18] = 0;
   out_5967503440163975557[19] = 0;
   out_5967503440163975557[20] = 0;
   out_5967503440163975557[21] = 0;
   out_5967503440163975557[22] = 0;
   out_5967503440163975557[23] = 0;
   out_5967503440163975557[24] = 0;
   out_5967503440163975557[25] = 1;
   out_5967503440163975557[26] = 0;
   out_5967503440163975557[27] = 0;
   out_5967503440163975557[28] = 1;
   out_5967503440163975557[29] = 0;
   out_5967503440163975557[30] = 0;
   out_5967503440163975557[31] = 0;
   out_5967503440163975557[32] = 0;
   out_5967503440163975557[33] = 0;
   out_5967503440163975557[34] = 0;
   out_5967503440163975557[35] = 0;
   out_5967503440163975557[36] = 0;
   out_5967503440163975557[37] = 0;
   out_5967503440163975557[38] = 0;
   out_5967503440163975557[39] = 0;
   out_5967503440163975557[40] = 0;
   out_5967503440163975557[41] = 0;
   out_5967503440163975557[42] = 0;
   out_5967503440163975557[43] = 0;
   out_5967503440163975557[44] = 1;
   out_5967503440163975557[45] = 0;
   out_5967503440163975557[46] = 0;
   out_5967503440163975557[47] = 1;
   out_5967503440163975557[48] = 0;
   out_5967503440163975557[49] = 0;
   out_5967503440163975557[50] = 0;
   out_5967503440163975557[51] = 0;
   out_5967503440163975557[52] = 0;
   out_5967503440163975557[53] = 0;
}
void h_10(double *state, double *unused, double *out_7255837942068693372) {
   out_7255837942068693372[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7255837942068693372[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7255837942068693372[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2797151911620261444) {
   out_2797151911620261444[0] = 0;
   out_2797151911620261444[1] = 9.8100000000000005*cos(state[1]);
   out_2797151911620261444[2] = 0;
   out_2797151911620261444[3] = 0;
   out_2797151911620261444[4] = -state[8];
   out_2797151911620261444[5] = state[7];
   out_2797151911620261444[6] = 0;
   out_2797151911620261444[7] = state[5];
   out_2797151911620261444[8] = -state[4];
   out_2797151911620261444[9] = 0;
   out_2797151911620261444[10] = 0;
   out_2797151911620261444[11] = 0;
   out_2797151911620261444[12] = 1;
   out_2797151911620261444[13] = 0;
   out_2797151911620261444[14] = 0;
   out_2797151911620261444[15] = 1;
   out_2797151911620261444[16] = 0;
   out_2797151911620261444[17] = 0;
   out_2797151911620261444[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2797151911620261444[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2797151911620261444[20] = 0;
   out_2797151911620261444[21] = state[8];
   out_2797151911620261444[22] = 0;
   out_2797151911620261444[23] = -state[6];
   out_2797151911620261444[24] = -state[5];
   out_2797151911620261444[25] = 0;
   out_2797151911620261444[26] = state[3];
   out_2797151911620261444[27] = 0;
   out_2797151911620261444[28] = 0;
   out_2797151911620261444[29] = 0;
   out_2797151911620261444[30] = 0;
   out_2797151911620261444[31] = 1;
   out_2797151911620261444[32] = 0;
   out_2797151911620261444[33] = 0;
   out_2797151911620261444[34] = 1;
   out_2797151911620261444[35] = 0;
   out_2797151911620261444[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2797151911620261444[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2797151911620261444[38] = 0;
   out_2797151911620261444[39] = -state[7];
   out_2797151911620261444[40] = state[6];
   out_2797151911620261444[41] = 0;
   out_2797151911620261444[42] = state[4];
   out_2797151911620261444[43] = -state[3];
   out_2797151911620261444[44] = 0;
   out_2797151911620261444[45] = 0;
   out_2797151911620261444[46] = 0;
   out_2797151911620261444[47] = 0;
   out_2797151911620261444[48] = 0;
   out_2797151911620261444[49] = 0;
   out_2797151911620261444[50] = 1;
   out_2797151911620261444[51] = 0;
   out_2797151911620261444[52] = 0;
   out_2797151911620261444[53] = 1;
}
void h_13(double *state, double *unused, double *out_4677326677955265500) {
   out_4677326677955265500[0] = state[3];
   out_4677326677955265500[1] = state[4];
   out_4677326677955265500[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8645485170243052035) {
   out_8645485170243052035[0] = 0;
   out_8645485170243052035[1] = 0;
   out_8645485170243052035[2] = 0;
   out_8645485170243052035[3] = 1;
   out_8645485170243052035[4] = 0;
   out_8645485170243052035[5] = 0;
   out_8645485170243052035[6] = 0;
   out_8645485170243052035[7] = 0;
   out_8645485170243052035[8] = 0;
   out_8645485170243052035[9] = 0;
   out_8645485170243052035[10] = 0;
   out_8645485170243052035[11] = 0;
   out_8645485170243052035[12] = 0;
   out_8645485170243052035[13] = 0;
   out_8645485170243052035[14] = 0;
   out_8645485170243052035[15] = 0;
   out_8645485170243052035[16] = 0;
   out_8645485170243052035[17] = 0;
   out_8645485170243052035[18] = 0;
   out_8645485170243052035[19] = 0;
   out_8645485170243052035[20] = 0;
   out_8645485170243052035[21] = 0;
   out_8645485170243052035[22] = 1;
   out_8645485170243052035[23] = 0;
   out_8645485170243052035[24] = 0;
   out_8645485170243052035[25] = 0;
   out_8645485170243052035[26] = 0;
   out_8645485170243052035[27] = 0;
   out_8645485170243052035[28] = 0;
   out_8645485170243052035[29] = 0;
   out_8645485170243052035[30] = 0;
   out_8645485170243052035[31] = 0;
   out_8645485170243052035[32] = 0;
   out_8645485170243052035[33] = 0;
   out_8645485170243052035[34] = 0;
   out_8645485170243052035[35] = 0;
   out_8645485170243052035[36] = 0;
   out_8645485170243052035[37] = 0;
   out_8645485170243052035[38] = 0;
   out_8645485170243052035[39] = 0;
   out_8645485170243052035[40] = 0;
   out_8645485170243052035[41] = 1;
   out_8645485170243052035[42] = 0;
   out_8645485170243052035[43] = 0;
   out_8645485170243052035[44] = 0;
   out_8645485170243052035[45] = 0;
   out_8645485170243052035[46] = 0;
   out_8645485170243052035[47] = 0;
   out_8645485170243052035[48] = 0;
   out_8645485170243052035[49] = 0;
   out_8645485170243052035[50] = 0;
   out_8645485170243052035[51] = 0;
   out_8645485170243052035[52] = 0;
   out_8645485170243052035[53] = 0;
}
void h_14(double *state, double *unused, double *out_8166535974230408665) {
   out_8166535974230408665[0] = state[6];
   out_8166535974230408665[1] = state[7];
   out_8166535974230408665[2] = state[8];
}
void H_14(double *state, double *unused, double *out_9050291872459347853) {
   out_9050291872459347853[0] = 0;
   out_9050291872459347853[1] = 0;
   out_9050291872459347853[2] = 0;
   out_9050291872459347853[3] = 0;
   out_9050291872459347853[4] = 0;
   out_9050291872459347853[5] = 0;
   out_9050291872459347853[6] = 1;
   out_9050291872459347853[7] = 0;
   out_9050291872459347853[8] = 0;
   out_9050291872459347853[9] = 0;
   out_9050291872459347853[10] = 0;
   out_9050291872459347853[11] = 0;
   out_9050291872459347853[12] = 0;
   out_9050291872459347853[13] = 0;
   out_9050291872459347853[14] = 0;
   out_9050291872459347853[15] = 0;
   out_9050291872459347853[16] = 0;
   out_9050291872459347853[17] = 0;
   out_9050291872459347853[18] = 0;
   out_9050291872459347853[19] = 0;
   out_9050291872459347853[20] = 0;
   out_9050291872459347853[21] = 0;
   out_9050291872459347853[22] = 0;
   out_9050291872459347853[23] = 0;
   out_9050291872459347853[24] = 0;
   out_9050291872459347853[25] = 1;
   out_9050291872459347853[26] = 0;
   out_9050291872459347853[27] = 0;
   out_9050291872459347853[28] = 0;
   out_9050291872459347853[29] = 0;
   out_9050291872459347853[30] = 0;
   out_9050291872459347853[31] = 0;
   out_9050291872459347853[32] = 0;
   out_9050291872459347853[33] = 0;
   out_9050291872459347853[34] = 0;
   out_9050291872459347853[35] = 0;
   out_9050291872459347853[36] = 0;
   out_9050291872459347853[37] = 0;
   out_9050291872459347853[38] = 0;
   out_9050291872459347853[39] = 0;
   out_9050291872459347853[40] = 0;
   out_9050291872459347853[41] = 0;
   out_9050291872459347853[42] = 0;
   out_9050291872459347853[43] = 0;
   out_9050291872459347853[44] = 1;
   out_9050291872459347853[45] = 0;
   out_9050291872459347853[46] = 0;
   out_9050291872459347853[47] = 0;
   out_9050291872459347853[48] = 0;
   out_9050291872459347853[49] = 0;
   out_9050291872459347853[50] = 0;
   out_9050291872459347853[51] = 0;
   out_9050291872459347853[52] = 0;
   out_9050291872459347853[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6202662645191369) {
  err_fun(nom_x, delta_x, out_6202662645191369);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5065890083902176780) {
  inv_err_fun(nom_x, true_x, out_5065890083902176780);
}
void pose_H_mod_fun(double *state, double *out_4147804714257678696) {
  H_mod_fun(state, out_4147804714257678696);
}
void pose_f_fun(double *state, double dt, double *out_134451283192963896) {
  f_fun(state,  dt, out_134451283192963896);
}
void pose_F_fun(double *state, double dt, double *out_7947855407511726470) {
  F_fun(state,  dt, out_7947855407511726470);
}
void pose_h_4(double *state, double *unused, double *out_7278578289213708861) {
  h_4(state, unused, out_7278578289213708861);
}
void pose_H_4(double *state, double *unused, double *out_5967503440163975557) {
  H_4(state, unused, out_5967503440163975557);
}
void pose_h_10(double *state, double *unused, double *out_7255837942068693372) {
  h_10(state, unused, out_7255837942068693372);
}
void pose_H_10(double *state, double *unused, double *out_2797151911620261444) {
  H_10(state, unused, out_2797151911620261444);
}
void pose_h_13(double *state, double *unused, double *out_4677326677955265500) {
  h_13(state, unused, out_4677326677955265500);
}
void pose_H_13(double *state, double *unused, double *out_8645485170243052035) {
  H_13(state, unused, out_8645485170243052035);
}
void pose_h_14(double *state, double *unused, double *out_8166535974230408665) {
  h_14(state, unused, out_8166535974230408665);
}
void pose_H_14(double *state, double *unused, double *out_9050291872459347853) {
  H_14(state, unused, out_9050291872459347853);
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
