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
void err_fun(double *nom_x, double *delta_x, double *out_1903961773272735640) {
   out_1903961773272735640[0] = delta_x[0] + nom_x[0];
   out_1903961773272735640[1] = delta_x[1] + nom_x[1];
   out_1903961773272735640[2] = delta_x[2] + nom_x[2];
   out_1903961773272735640[3] = delta_x[3] + nom_x[3];
   out_1903961773272735640[4] = delta_x[4] + nom_x[4];
   out_1903961773272735640[5] = delta_x[5] + nom_x[5];
   out_1903961773272735640[6] = delta_x[6] + nom_x[6];
   out_1903961773272735640[7] = delta_x[7] + nom_x[7];
   out_1903961773272735640[8] = delta_x[8] + nom_x[8];
   out_1903961773272735640[9] = delta_x[9] + nom_x[9];
   out_1903961773272735640[10] = delta_x[10] + nom_x[10];
   out_1903961773272735640[11] = delta_x[11] + nom_x[11];
   out_1903961773272735640[12] = delta_x[12] + nom_x[12];
   out_1903961773272735640[13] = delta_x[13] + nom_x[13];
   out_1903961773272735640[14] = delta_x[14] + nom_x[14];
   out_1903961773272735640[15] = delta_x[15] + nom_x[15];
   out_1903961773272735640[16] = delta_x[16] + nom_x[16];
   out_1903961773272735640[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_573088353517031631) {
   out_573088353517031631[0] = -nom_x[0] + true_x[0];
   out_573088353517031631[1] = -nom_x[1] + true_x[1];
   out_573088353517031631[2] = -nom_x[2] + true_x[2];
   out_573088353517031631[3] = -nom_x[3] + true_x[3];
   out_573088353517031631[4] = -nom_x[4] + true_x[4];
   out_573088353517031631[5] = -nom_x[5] + true_x[5];
   out_573088353517031631[6] = -nom_x[6] + true_x[6];
   out_573088353517031631[7] = -nom_x[7] + true_x[7];
   out_573088353517031631[8] = -nom_x[8] + true_x[8];
   out_573088353517031631[9] = -nom_x[9] + true_x[9];
   out_573088353517031631[10] = -nom_x[10] + true_x[10];
   out_573088353517031631[11] = -nom_x[11] + true_x[11];
   out_573088353517031631[12] = -nom_x[12] + true_x[12];
   out_573088353517031631[13] = -nom_x[13] + true_x[13];
   out_573088353517031631[14] = -nom_x[14] + true_x[14];
   out_573088353517031631[15] = -nom_x[15] + true_x[15];
   out_573088353517031631[16] = -nom_x[16] + true_x[16];
   out_573088353517031631[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8399228583696910237) {
   out_8399228583696910237[0] = 1.0;
   out_8399228583696910237[1] = 0.0;
   out_8399228583696910237[2] = 0.0;
   out_8399228583696910237[3] = 0.0;
   out_8399228583696910237[4] = 0.0;
   out_8399228583696910237[5] = 0.0;
   out_8399228583696910237[6] = 0.0;
   out_8399228583696910237[7] = 0.0;
   out_8399228583696910237[8] = 0.0;
   out_8399228583696910237[9] = 0.0;
   out_8399228583696910237[10] = 0.0;
   out_8399228583696910237[11] = 0.0;
   out_8399228583696910237[12] = 0.0;
   out_8399228583696910237[13] = 0.0;
   out_8399228583696910237[14] = 0.0;
   out_8399228583696910237[15] = 0.0;
   out_8399228583696910237[16] = 0.0;
   out_8399228583696910237[17] = 0.0;
   out_8399228583696910237[18] = 0.0;
   out_8399228583696910237[19] = 1.0;
   out_8399228583696910237[20] = 0.0;
   out_8399228583696910237[21] = 0.0;
   out_8399228583696910237[22] = 0.0;
   out_8399228583696910237[23] = 0.0;
   out_8399228583696910237[24] = 0.0;
   out_8399228583696910237[25] = 0.0;
   out_8399228583696910237[26] = 0.0;
   out_8399228583696910237[27] = 0.0;
   out_8399228583696910237[28] = 0.0;
   out_8399228583696910237[29] = 0.0;
   out_8399228583696910237[30] = 0.0;
   out_8399228583696910237[31] = 0.0;
   out_8399228583696910237[32] = 0.0;
   out_8399228583696910237[33] = 0.0;
   out_8399228583696910237[34] = 0.0;
   out_8399228583696910237[35] = 0.0;
   out_8399228583696910237[36] = 0.0;
   out_8399228583696910237[37] = 0.0;
   out_8399228583696910237[38] = 1.0;
   out_8399228583696910237[39] = 0.0;
   out_8399228583696910237[40] = 0.0;
   out_8399228583696910237[41] = 0.0;
   out_8399228583696910237[42] = 0.0;
   out_8399228583696910237[43] = 0.0;
   out_8399228583696910237[44] = 0.0;
   out_8399228583696910237[45] = 0.0;
   out_8399228583696910237[46] = 0.0;
   out_8399228583696910237[47] = 0.0;
   out_8399228583696910237[48] = 0.0;
   out_8399228583696910237[49] = 0.0;
   out_8399228583696910237[50] = 0.0;
   out_8399228583696910237[51] = 0.0;
   out_8399228583696910237[52] = 0.0;
   out_8399228583696910237[53] = 0.0;
   out_8399228583696910237[54] = 0.0;
   out_8399228583696910237[55] = 0.0;
   out_8399228583696910237[56] = 0.0;
   out_8399228583696910237[57] = 1.0;
   out_8399228583696910237[58] = 0.0;
   out_8399228583696910237[59] = 0.0;
   out_8399228583696910237[60] = 0.0;
   out_8399228583696910237[61] = 0.0;
   out_8399228583696910237[62] = 0.0;
   out_8399228583696910237[63] = 0.0;
   out_8399228583696910237[64] = 0.0;
   out_8399228583696910237[65] = 0.0;
   out_8399228583696910237[66] = 0.0;
   out_8399228583696910237[67] = 0.0;
   out_8399228583696910237[68] = 0.0;
   out_8399228583696910237[69] = 0.0;
   out_8399228583696910237[70] = 0.0;
   out_8399228583696910237[71] = 0.0;
   out_8399228583696910237[72] = 0.0;
   out_8399228583696910237[73] = 0.0;
   out_8399228583696910237[74] = 0.0;
   out_8399228583696910237[75] = 0.0;
   out_8399228583696910237[76] = 1.0;
   out_8399228583696910237[77] = 0.0;
   out_8399228583696910237[78] = 0.0;
   out_8399228583696910237[79] = 0.0;
   out_8399228583696910237[80] = 0.0;
   out_8399228583696910237[81] = 0.0;
   out_8399228583696910237[82] = 0.0;
   out_8399228583696910237[83] = 0.0;
   out_8399228583696910237[84] = 0.0;
   out_8399228583696910237[85] = 0.0;
   out_8399228583696910237[86] = 0.0;
   out_8399228583696910237[87] = 0.0;
   out_8399228583696910237[88] = 0.0;
   out_8399228583696910237[89] = 0.0;
   out_8399228583696910237[90] = 0.0;
   out_8399228583696910237[91] = 0.0;
   out_8399228583696910237[92] = 0.0;
   out_8399228583696910237[93] = 0.0;
   out_8399228583696910237[94] = 0.0;
   out_8399228583696910237[95] = 1.0;
   out_8399228583696910237[96] = 0.0;
   out_8399228583696910237[97] = 0.0;
   out_8399228583696910237[98] = 0.0;
   out_8399228583696910237[99] = 0.0;
   out_8399228583696910237[100] = 0.0;
   out_8399228583696910237[101] = 0.0;
   out_8399228583696910237[102] = 0.0;
   out_8399228583696910237[103] = 0.0;
   out_8399228583696910237[104] = 0.0;
   out_8399228583696910237[105] = 0.0;
   out_8399228583696910237[106] = 0.0;
   out_8399228583696910237[107] = 0.0;
   out_8399228583696910237[108] = 0.0;
   out_8399228583696910237[109] = 0.0;
   out_8399228583696910237[110] = 0.0;
   out_8399228583696910237[111] = 0.0;
   out_8399228583696910237[112] = 0.0;
   out_8399228583696910237[113] = 0.0;
   out_8399228583696910237[114] = 1.0;
   out_8399228583696910237[115] = 0.0;
   out_8399228583696910237[116] = 0.0;
   out_8399228583696910237[117] = 0.0;
   out_8399228583696910237[118] = 0.0;
   out_8399228583696910237[119] = 0.0;
   out_8399228583696910237[120] = 0.0;
   out_8399228583696910237[121] = 0.0;
   out_8399228583696910237[122] = 0.0;
   out_8399228583696910237[123] = 0.0;
   out_8399228583696910237[124] = 0.0;
   out_8399228583696910237[125] = 0.0;
   out_8399228583696910237[126] = 0.0;
   out_8399228583696910237[127] = 0.0;
   out_8399228583696910237[128] = 0.0;
   out_8399228583696910237[129] = 0.0;
   out_8399228583696910237[130] = 0.0;
   out_8399228583696910237[131] = 0.0;
   out_8399228583696910237[132] = 0.0;
   out_8399228583696910237[133] = 1.0;
   out_8399228583696910237[134] = 0.0;
   out_8399228583696910237[135] = 0.0;
   out_8399228583696910237[136] = 0.0;
   out_8399228583696910237[137] = 0.0;
   out_8399228583696910237[138] = 0.0;
   out_8399228583696910237[139] = 0.0;
   out_8399228583696910237[140] = 0.0;
   out_8399228583696910237[141] = 0.0;
   out_8399228583696910237[142] = 0.0;
   out_8399228583696910237[143] = 0.0;
   out_8399228583696910237[144] = 0.0;
   out_8399228583696910237[145] = 0.0;
   out_8399228583696910237[146] = 0.0;
   out_8399228583696910237[147] = 0.0;
   out_8399228583696910237[148] = 0.0;
   out_8399228583696910237[149] = 0.0;
   out_8399228583696910237[150] = 0.0;
   out_8399228583696910237[151] = 0.0;
   out_8399228583696910237[152] = 1.0;
   out_8399228583696910237[153] = 0.0;
   out_8399228583696910237[154] = 0.0;
   out_8399228583696910237[155] = 0.0;
   out_8399228583696910237[156] = 0.0;
   out_8399228583696910237[157] = 0.0;
   out_8399228583696910237[158] = 0.0;
   out_8399228583696910237[159] = 0.0;
   out_8399228583696910237[160] = 0.0;
   out_8399228583696910237[161] = 0.0;
   out_8399228583696910237[162] = 0.0;
   out_8399228583696910237[163] = 0.0;
   out_8399228583696910237[164] = 0.0;
   out_8399228583696910237[165] = 0.0;
   out_8399228583696910237[166] = 0.0;
   out_8399228583696910237[167] = 0.0;
   out_8399228583696910237[168] = 0.0;
   out_8399228583696910237[169] = 0.0;
   out_8399228583696910237[170] = 0.0;
   out_8399228583696910237[171] = 1.0;
   out_8399228583696910237[172] = 0.0;
   out_8399228583696910237[173] = 0.0;
   out_8399228583696910237[174] = 0.0;
   out_8399228583696910237[175] = 0.0;
   out_8399228583696910237[176] = 0.0;
   out_8399228583696910237[177] = 0.0;
   out_8399228583696910237[178] = 0.0;
   out_8399228583696910237[179] = 0.0;
   out_8399228583696910237[180] = 0.0;
   out_8399228583696910237[181] = 0.0;
   out_8399228583696910237[182] = 0.0;
   out_8399228583696910237[183] = 0.0;
   out_8399228583696910237[184] = 0.0;
   out_8399228583696910237[185] = 0.0;
   out_8399228583696910237[186] = 0.0;
   out_8399228583696910237[187] = 0.0;
   out_8399228583696910237[188] = 0.0;
   out_8399228583696910237[189] = 0.0;
   out_8399228583696910237[190] = 1.0;
   out_8399228583696910237[191] = 0.0;
   out_8399228583696910237[192] = 0.0;
   out_8399228583696910237[193] = 0.0;
   out_8399228583696910237[194] = 0.0;
   out_8399228583696910237[195] = 0.0;
   out_8399228583696910237[196] = 0.0;
   out_8399228583696910237[197] = 0.0;
   out_8399228583696910237[198] = 0.0;
   out_8399228583696910237[199] = 0.0;
   out_8399228583696910237[200] = 0.0;
   out_8399228583696910237[201] = 0.0;
   out_8399228583696910237[202] = 0.0;
   out_8399228583696910237[203] = 0.0;
   out_8399228583696910237[204] = 0.0;
   out_8399228583696910237[205] = 0.0;
   out_8399228583696910237[206] = 0.0;
   out_8399228583696910237[207] = 0.0;
   out_8399228583696910237[208] = 0.0;
   out_8399228583696910237[209] = 1.0;
   out_8399228583696910237[210] = 0.0;
   out_8399228583696910237[211] = 0.0;
   out_8399228583696910237[212] = 0.0;
   out_8399228583696910237[213] = 0.0;
   out_8399228583696910237[214] = 0.0;
   out_8399228583696910237[215] = 0.0;
   out_8399228583696910237[216] = 0.0;
   out_8399228583696910237[217] = 0.0;
   out_8399228583696910237[218] = 0.0;
   out_8399228583696910237[219] = 0.0;
   out_8399228583696910237[220] = 0.0;
   out_8399228583696910237[221] = 0.0;
   out_8399228583696910237[222] = 0.0;
   out_8399228583696910237[223] = 0.0;
   out_8399228583696910237[224] = 0.0;
   out_8399228583696910237[225] = 0.0;
   out_8399228583696910237[226] = 0.0;
   out_8399228583696910237[227] = 0.0;
   out_8399228583696910237[228] = 1.0;
   out_8399228583696910237[229] = 0.0;
   out_8399228583696910237[230] = 0.0;
   out_8399228583696910237[231] = 0.0;
   out_8399228583696910237[232] = 0.0;
   out_8399228583696910237[233] = 0.0;
   out_8399228583696910237[234] = 0.0;
   out_8399228583696910237[235] = 0.0;
   out_8399228583696910237[236] = 0.0;
   out_8399228583696910237[237] = 0.0;
   out_8399228583696910237[238] = 0.0;
   out_8399228583696910237[239] = 0.0;
   out_8399228583696910237[240] = 0.0;
   out_8399228583696910237[241] = 0.0;
   out_8399228583696910237[242] = 0.0;
   out_8399228583696910237[243] = 0.0;
   out_8399228583696910237[244] = 0.0;
   out_8399228583696910237[245] = 0.0;
   out_8399228583696910237[246] = 0.0;
   out_8399228583696910237[247] = 1.0;
   out_8399228583696910237[248] = 0.0;
   out_8399228583696910237[249] = 0.0;
   out_8399228583696910237[250] = 0.0;
   out_8399228583696910237[251] = 0.0;
   out_8399228583696910237[252] = 0.0;
   out_8399228583696910237[253] = 0.0;
   out_8399228583696910237[254] = 0.0;
   out_8399228583696910237[255] = 0.0;
   out_8399228583696910237[256] = 0.0;
   out_8399228583696910237[257] = 0.0;
   out_8399228583696910237[258] = 0.0;
   out_8399228583696910237[259] = 0.0;
   out_8399228583696910237[260] = 0.0;
   out_8399228583696910237[261] = 0.0;
   out_8399228583696910237[262] = 0.0;
   out_8399228583696910237[263] = 0.0;
   out_8399228583696910237[264] = 0.0;
   out_8399228583696910237[265] = 0.0;
   out_8399228583696910237[266] = 1.0;
   out_8399228583696910237[267] = 0.0;
   out_8399228583696910237[268] = 0.0;
   out_8399228583696910237[269] = 0.0;
   out_8399228583696910237[270] = 0.0;
   out_8399228583696910237[271] = 0.0;
   out_8399228583696910237[272] = 0.0;
   out_8399228583696910237[273] = 0.0;
   out_8399228583696910237[274] = 0.0;
   out_8399228583696910237[275] = 0.0;
   out_8399228583696910237[276] = 0.0;
   out_8399228583696910237[277] = 0.0;
   out_8399228583696910237[278] = 0.0;
   out_8399228583696910237[279] = 0.0;
   out_8399228583696910237[280] = 0.0;
   out_8399228583696910237[281] = 0.0;
   out_8399228583696910237[282] = 0.0;
   out_8399228583696910237[283] = 0.0;
   out_8399228583696910237[284] = 0.0;
   out_8399228583696910237[285] = 1.0;
   out_8399228583696910237[286] = 0.0;
   out_8399228583696910237[287] = 0.0;
   out_8399228583696910237[288] = 0.0;
   out_8399228583696910237[289] = 0.0;
   out_8399228583696910237[290] = 0.0;
   out_8399228583696910237[291] = 0.0;
   out_8399228583696910237[292] = 0.0;
   out_8399228583696910237[293] = 0.0;
   out_8399228583696910237[294] = 0.0;
   out_8399228583696910237[295] = 0.0;
   out_8399228583696910237[296] = 0.0;
   out_8399228583696910237[297] = 0.0;
   out_8399228583696910237[298] = 0.0;
   out_8399228583696910237[299] = 0.0;
   out_8399228583696910237[300] = 0.0;
   out_8399228583696910237[301] = 0.0;
   out_8399228583696910237[302] = 0.0;
   out_8399228583696910237[303] = 0.0;
   out_8399228583696910237[304] = 1.0;
   out_8399228583696910237[305] = 0.0;
   out_8399228583696910237[306] = 0.0;
   out_8399228583696910237[307] = 0.0;
   out_8399228583696910237[308] = 0.0;
   out_8399228583696910237[309] = 0.0;
   out_8399228583696910237[310] = 0.0;
   out_8399228583696910237[311] = 0.0;
   out_8399228583696910237[312] = 0.0;
   out_8399228583696910237[313] = 0.0;
   out_8399228583696910237[314] = 0.0;
   out_8399228583696910237[315] = 0.0;
   out_8399228583696910237[316] = 0.0;
   out_8399228583696910237[317] = 0.0;
   out_8399228583696910237[318] = 0.0;
   out_8399228583696910237[319] = 0.0;
   out_8399228583696910237[320] = 0.0;
   out_8399228583696910237[321] = 0.0;
   out_8399228583696910237[322] = 0.0;
   out_8399228583696910237[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7642272888362122250) {
   out_7642272888362122250[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7642272888362122250[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7642272888362122250[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7642272888362122250[3] = dt*state[12] + state[3];
   out_7642272888362122250[4] = dt*state[13] + state[4];
   out_7642272888362122250[5] = dt*state[14] + state[5];
   out_7642272888362122250[6] = state[6];
   out_7642272888362122250[7] = state[7];
   out_7642272888362122250[8] = state[8];
   out_7642272888362122250[9] = state[9];
   out_7642272888362122250[10] = state[10];
   out_7642272888362122250[11] = state[11];
   out_7642272888362122250[12] = state[12];
   out_7642272888362122250[13] = state[13];
   out_7642272888362122250[14] = state[14];
   out_7642272888362122250[15] = state[15];
   out_7642272888362122250[16] = state[16];
   out_7642272888362122250[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2644346224160988756) {
   out_2644346224160988756[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2644346224160988756[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2644346224160988756[2] = 0;
   out_2644346224160988756[3] = 0;
   out_2644346224160988756[4] = 0;
   out_2644346224160988756[5] = 0;
   out_2644346224160988756[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2644346224160988756[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2644346224160988756[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2644346224160988756[9] = 0;
   out_2644346224160988756[10] = 0;
   out_2644346224160988756[11] = 0;
   out_2644346224160988756[12] = 0;
   out_2644346224160988756[13] = 0;
   out_2644346224160988756[14] = 0;
   out_2644346224160988756[15] = 0;
   out_2644346224160988756[16] = 0;
   out_2644346224160988756[17] = 0;
   out_2644346224160988756[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2644346224160988756[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2644346224160988756[20] = 0;
   out_2644346224160988756[21] = 0;
   out_2644346224160988756[22] = 0;
   out_2644346224160988756[23] = 0;
   out_2644346224160988756[24] = 0;
   out_2644346224160988756[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2644346224160988756[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2644346224160988756[27] = 0;
   out_2644346224160988756[28] = 0;
   out_2644346224160988756[29] = 0;
   out_2644346224160988756[30] = 0;
   out_2644346224160988756[31] = 0;
   out_2644346224160988756[32] = 0;
   out_2644346224160988756[33] = 0;
   out_2644346224160988756[34] = 0;
   out_2644346224160988756[35] = 0;
   out_2644346224160988756[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2644346224160988756[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2644346224160988756[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2644346224160988756[39] = 0;
   out_2644346224160988756[40] = 0;
   out_2644346224160988756[41] = 0;
   out_2644346224160988756[42] = 0;
   out_2644346224160988756[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2644346224160988756[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2644346224160988756[45] = 0;
   out_2644346224160988756[46] = 0;
   out_2644346224160988756[47] = 0;
   out_2644346224160988756[48] = 0;
   out_2644346224160988756[49] = 0;
   out_2644346224160988756[50] = 0;
   out_2644346224160988756[51] = 0;
   out_2644346224160988756[52] = 0;
   out_2644346224160988756[53] = 0;
   out_2644346224160988756[54] = 0;
   out_2644346224160988756[55] = 0;
   out_2644346224160988756[56] = 0;
   out_2644346224160988756[57] = 1;
   out_2644346224160988756[58] = 0;
   out_2644346224160988756[59] = 0;
   out_2644346224160988756[60] = 0;
   out_2644346224160988756[61] = 0;
   out_2644346224160988756[62] = 0;
   out_2644346224160988756[63] = 0;
   out_2644346224160988756[64] = 0;
   out_2644346224160988756[65] = 0;
   out_2644346224160988756[66] = dt;
   out_2644346224160988756[67] = 0;
   out_2644346224160988756[68] = 0;
   out_2644346224160988756[69] = 0;
   out_2644346224160988756[70] = 0;
   out_2644346224160988756[71] = 0;
   out_2644346224160988756[72] = 0;
   out_2644346224160988756[73] = 0;
   out_2644346224160988756[74] = 0;
   out_2644346224160988756[75] = 0;
   out_2644346224160988756[76] = 1;
   out_2644346224160988756[77] = 0;
   out_2644346224160988756[78] = 0;
   out_2644346224160988756[79] = 0;
   out_2644346224160988756[80] = 0;
   out_2644346224160988756[81] = 0;
   out_2644346224160988756[82] = 0;
   out_2644346224160988756[83] = 0;
   out_2644346224160988756[84] = 0;
   out_2644346224160988756[85] = dt;
   out_2644346224160988756[86] = 0;
   out_2644346224160988756[87] = 0;
   out_2644346224160988756[88] = 0;
   out_2644346224160988756[89] = 0;
   out_2644346224160988756[90] = 0;
   out_2644346224160988756[91] = 0;
   out_2644346224160988756[92] = 0;
   out_2644346224160988756[93] = 0;
   out_2644346224160988756[94] = 0;
   out_2644346224160988756[95] = 1;
   out_2644346224160988756[96] = 0;
   out_2644346224160988756[97] = 0;
   out_2644346224160988756[98] = 0;
   out_2644346224160988756[99] = 0;
   out_2644346224160988756[100] = 0;
   out_2644346224160988756[101] = 0;
   out_2644346224160988756[102] = 0;
   out_2644346224160988756[103] = 0;
   out_2644346224160988756[104] = dt;
   out_2644346224160988756[105] = 0;
   out_2644346224160988756[106] = 0;
   out_2644346224160988756[107] = 0;
   out_2644346224160988756[108] = 0;
   out_2644346224160988756[109] = 0;
   out_2644346224160988756[110] = 0;
   out_2644346224160988756[111] = 0;
   out_2644346224160988756[112] = 0;
   out_2644346224160988756[113] = 0;
   out_2644346224160988756[114] = 1;
   out_2644346224160988756[115] = 0;
   out_2644346224160988756[116] = 0;
   out_2644346224160988756[117] = 0;
   out_2644346224160988756[118] = 0;
   out_2644346224160988756[119] = 0;
   out_2644346224160988756[120] = 0;
   out_2644346224160988756[121] = 0;
   out_2644346224160988756[122] = 0;
   out_2644346224160988756[123] = 0;
   out_2644346224160988756[124] = 0;
   out_2644346224160988756[125] = 0;
   out_2644346224160988756[126] = 0;
   out_2644346224160988756[127] = 0;
   out_2644346224160988756[128] = 0;
   out_2644346224160988756[129] = 0;
   out_2644346224160988756[130] = 0;
   out_2644346224160988756[131] = 0;
   out_2644346224160988756[132] = 0;
   out_2644346224160988756[133] = 1;
   out_2644346224160988756[134] = 0;
   out_2644346224160988756[135] = 0;
   out_2644346224160988756[136] = 0;
   out_2644346224160988756[137] = 0;
   out_2644346224160988756[138] = 0;
   out_2644346224160988756[139] = 0;
   out_2644346224160988756[140] = 0;
   out_2644346224160988756[141] = 0;
   out_2644346224160988756[142] = 0;
   out_2644346224160988756[143] = 0;
   out_2644346224160988756[144] = 0;
   out_2644346224160988756[145] = 0;
   out_2644346224160988756[146] = 0;
   out_2644346224160988756[147] = 0;
   out_2644346224160988756[148] = 0;
   out_2644346224160988756[149] = 0;
   out_2644346224160988756[150] = 0;
   out_2644346224160988756[151] = 0;
   out_2644346224160988756[152] = 1;
   out_2644346224160988756[153] = 0;
   out_2644346224160988756[154] = 0;
   out_2644346224160988756[155] = 0;
   out_2644346224160988756[156] = 0;
   out_2644346224160988756[157] = 0;
   out_2644346224160988756[158] = 0;
   out_2644346224160988756[159] = 0;
   out_2644346224160988756[160] = 0;
   out_2644346224160988756[161] = 0;
   out_2644346224160988756[162] = 0;
   out_2644346224160988756[163] = 0;
   out_2644346224160988756[164] = 0;
   out_2644346224160988756[165] = 0;
   out_2644346224160988756[166] = 0;
   out_2644346224160988756[167] = 0;
   out_2644346224160988756[168] = 0;
   out_2644346224160988756[169] = 0;
   out_2644346224160988756[170] = 0;
   out_2644346224160988756[171] = 1;
   out_2644346224160988756[172] = 0;
   out_2644346224160988756[173] = 0;
   out_2644346224160988756[174] = 0;
   out_2644346224160988756[175] = 0;
   out_2644346224160988756[176] = 0;
   out_2644346224160988756[177] = 0;
   out_2644346224160988756[178] = 0;
   out_2644346224160988756[179] = 0;
   out_2644346224160988756[180] = 0;
   out_2644346224160988756[181] = 0;
   out_2644346224160988756[182] = 0;
   out_2644346224160988756[183] = 0;
   out_2644346224160988756[184] = 0;
   out_2644346224160988756[185] = 0;
   out_2644346224160988756[186] = 0;
   out_2644346224160988756[187] = 0;
   out_2644346224160988756[188] = 0;
   out_2644346224160988756[189] = 0;
   out_2644346224160988756[190] = 1;
   out_2644346224160988756[191] = 0;
   out_2644346224160988756[192] = 0;
   out_2644346224160988756[193] = 0;
   out_2644346224160988756[194] = 0;
   out_2644346224160988756[195] = 0;
   out_2644346224160988756[196] = 0;
   out_2644346224160988756[197] = 0;
   out_2644346224160988756[198] = 0;
   out_2644346224160988756[199] = 0;
   out_2644346224160988756[200] = 0;
   out_2644346224160988756[201] = 0;
   out_2644346224160988756[202] = 0;
   out_2644346224160988756[203] = 0;
   out_2644346224160988756[204] = 0;
   out_2644346224160988756[205] = 0;
   out_2644346224160988756[206] = 0;
   out_2644346224160988756[207] = 0;
   out_2644346224160988756[208] = 0;
   out_2644346224160988756[209] = 1;
   out_2644346224160988756[210] = 0;
   out_2644346224160988756[211] = 0;
   out_2644346224160988756[212] = 0;
   out_2644346224160988756[213] = 0;
   out_2644346224160988756[214] = 0;
   out_2644346224160988756[215] = 0;
   out_2644346224160988756[216] = 0;
   out_2644346224160988756[217] = 0;
   out_2644346224160988756[218] = 0;
   out_2644346224160988756[219] = 0;
   out_2644346224160988756[220] = 0;
   out_2644346224160988756[221] = 0;
   out_2644346224160988756[222] = 0;
   out_2644346224160988756[223] = 0;
   out_2644346224160988756[224] = 0;
   out_2644346224160988756[225] = 0;
   out_2644346224160988756[226] = 0;
   out_2644346224160988756[227] = 0;
   out_2644346224160988756[228] = 1;
   out_2644346224160988756[229] = 0;
   out_2644346224160988756[230] = 0;
   out_2644346224160988756[231] = 0;
   out_2644346224160988756[232] = 0;
   out_2644346224160988756[233] = 0;
   out_2644346224160988756[234] = 0;
   out_2644346224160988756[235] = 0;
   out_2644346224160988756[236] = 0;
   out_2644346224160988756[237] = 0;
   out_2644346224160988756[238] = 0;
   out_2644346224160988756[239] = 0;
   out_2644346224160988756[240] = 0;
   out_2644346224160988756[241] = 0;
   out_2644346224160988756[242] = 0;
   out_2644346224160988756[243] = 0;
   out_2644346224160988756[244] = 0;
   out_2644346224160988756[245] = 0;
   out_2644346224160988756[246] = 0;
   out_2644346224160988756[247] = 1;
   out_2644346224160988756[248] = 0;
   out_2644346224160988756[249] = 0;
   out_2644346224160988756[250] = 0;
   out_2644346224160988756[251] = 0;
   out_2644346224160988756[252] = 0;
   out_2644346224160988756[253] = 0;
   out_2644346224160988756[254] = 0;
   out_2644346224160988756[255] = 0;
   out_2644346224160988756[256] = 0;
   out_2644346224160988756[257] = 0;
   out_2644346224160988756[258] = 0;
   out_2644346224160988756[259] = 0;
   out_2644346224160988756[260] = 0;
   out_2644346224160988756[261] = 0;
   out_2644346224160988756[262] = 0;
   out_2644346224160988756[263] = 0;
   out_2644346224160988756[264] = 0;
   out_2644346224160988756[265] = 0;
   out_2644346224160988756[266] = 1;
   out_2644346224160988756[267] = 0;
   out_2644346224160988756[268] = 0;
   out_2644346224160988756[269] = 0;
   out_2644346224160988756[270] = 0;
   out_2644346224160988756[271] = 0;
   out_2644346224160988756[272] = 0;
   out_2644346224160988756[273] = 0;
   out_2644346224160988756[274] = 0;
   out_2644346224160988756[275] = 0;
   out_2644346224160988756[276] = 0;
   out_2644346224160988756[277] = 0;
   out_2644346224160988756[278] = 0;
   out_2644346224160988756[279] = 0;
   out_2644346224160988756[280] = 0;
   out_2644346224160988756[281] = 0;
   out_2644346224160988756[282] = 0;
   out_2644346224160988756[283] = 0;
   out_2644346224160988756[284] = 0;
   out_2644346224160988756[285] = 1;
   out_2644346224160988756[286] = 0;
   out_2644346224160988756[287] = 0;
   out_2644346224160988756[288] = 0;
   out_2644346224160988756[289] = 0;
   out_2644346224160988756[290] = 0;
   out_2644346224160988756[291] = 0;
   out_2644346224160988756[292] = 0;
   out_2644346224160988756[293] = 0;
   out_2644346224160988756[294] = 0;
   out_2644346224160988756[295] = 0;
   out_2644346224160988756[296] = 0;
   out_2644346224160988756[297] = 0;
   out_2644346224160988756[298] = 0;
   out_2644346224160988756[299] = 0;
   out_2644346224160988756[300] = 0;
   out_2644346224160988756[301] = 0;
   out_2644346224160988756[302] = 0;
   out_2644346224160988756[303] = 0;
   out_2644346224160988756[304] = 1;
   out_2644346224160988756[305] = 0;
   out_2644346224160988756[306] = 0;
   out_2644346224160988756[307] = 0;
   out_2644346224160988756[308] = 0;
   out_2644346224160988756[309] = 0;
   out_2644346224160988756[310] = 0;
   out_2644346224160988756[311] = 0;
   out_2644346224160988756[312] = 0;
   out_2644346224160988756[313] = 0;
   out_2644346224160988756[314] = 0;
   out_2644346224160988756[315] = 0;
   out_2644346224160988756[316] = 0;
   out_2644346224160988756[317] = 0;
   out_2644346224160988756[318] = 0;
   out_2644346224160988756[319] = 0;
   out_2644346224160988756[320] = 0;
   out_2644346224160988756[321] = 0;
   out_2644346224160988756[322] = 0;
   out_2644346224160988756[323] = 1;
}
void h_4(double *state, double *unused, double *out_866291291104227919) {
   out_866291291104227919[0] = state[6] + state[9];
   out_866291291104227919[1] = state[7] + state[10];
   out_866291291104227919[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1103153823954820037) {
   out_1103153823954820037[0] = 0;
   out_1103153823954820037[1] = 0;
   out_1103153823954820037[2] = 0;
   out_1103153823954820037[3] = 0;
   out_1103153823954820037[4] = 0;
   out_1103153823954820037[5] = 0;
   out_1103153823954820037[6] = 1;
   out_1103153823954820037[7] = 0;
   out_1103153823954820037[8] = 0;
   out_1103153823954820037[9] = 1;
   out_1103153823954820037[10] = 0;
   out_1103153823954820037[11] = 0;
   out_1103153823954820037[12] = 0;
   out_1103153823954820037[13] = 0;
   out_1103153823954820037[14] = 0;
   out_1103153823954820037[15] = 0;
   out_1103153823954820037[16] = 0;
   out_1103153823954820037[17] = 0;
   out_1103153823954820037[18] = 0;
   out_1103153823954820037[19] = 0;
   out_1103153823954820037[20] = 0;
   out_1103153823954820037[21] = 0;
   out_1103153823954820037[22] = 0;
   out_1103153823954820037[23] = 0;
   out_1103153823954820037[24] = 0;
   out_1103153823954820037[25] = 1;
   out_1103153823954820037[26] = 0;
   out_1103153823954820037[27] = 0;
   out_1103153823954820037[28] = 1;
   out_1103153823954820037[29] = 0;
   out_1103153823954820037[30] = 0;
   out_1103153823954820037[31] = 0;
   out_1103153823954820037[32] = 0;
   out_1103153823954820037[33] = 0;
   out_1103153823954820037[34] = 0;
   out_1103153823954820037[35] = 0;
   out_1103153823954820037[36] = 0;
   out_1103153823954820037[37] = 0;
   out_1103153823954820037[38] = 0;
   out_1103153823954820037[39] = 0;
   out_1103153823954820037[40] = 0;
   out_1103153823954820037[41] = 0;
   out_1103153823954820037[42] = 0;
   out_1103153823954820037[43] = 0;
   out_1103153823954820037[44] = 1;
   out_1103153823954820037[45] = 0;
   out_1103153823954820037[46] = 0;
   out_1103153823954820037[47] = 1;
   out_1103153823954820037[48] = 0;
   out_1103153823954820037[49] = 0;
   out_1103153823954820037[50] = 0;
   out_1103153823954820037[51] = 0;
   out_1103153823954820037[52] = 0;
   out_1103153823954820037[53] = 0;
}
void h_10(double *state, double *unused, double *out_5833399118122366963) {
   out_5833399118122366963[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5833399118122366963[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5833399118122366963[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6949267687029300227) {
   out_6949267687029300227[0] = 0;
   out_6949267687029300227[1] = 9.8100000000000005*cos(state[1]);
   out_6949267687029300227[2] = 0;
   out_6949267687029300227[3] = 0;
   out_6949267687029300227[4] = -state[8];
   out_6949267687029300227[5] = state[7];
   out_6949267687029300227[6] = 0;
   out_6949267687029300227[7] = state[5];
   out_6949267687029300227[8] = -state[4];
   out_6949267687029300227[9] = 0;
   out_6949267687029300227[10] = 0;
   out_6949267687029300227[11] = 0;
   out_6949267687029300227[12] = 1;
   out_6949267687029300227[13] = 0;
   out_6949267687029300227[14] = 0;
   out_6949267687029300227[15] = 1;
   out_6949267687029300227[16] = 0;
   out_6949267687029300227[17] = 0;
   out_6949267687029300227[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6949267687029300227[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6949267687029300227[20] = 0;
   out_6949267687029300227[21] = state[8];
   out_6949267687029300227[22] = 0;
   out_6949267687029300227[23] = -state[6];
   out_6949267687029300227[24] = -state[5];
   out_6949267687029300227[25] = 0;
   out_6949267687029300227[26] = state[3];
   out_6949267687029300227[27] = 0;
   out_6949267687029300227[28] = 0;
   out_6949267687029300227[29] = 0;
   out_6949267687029300227[30] = 0;
   out_6949267687029300227[31] = 1;
   out_6949267687029300227[32] = 0;
   out_6949267687029300227[33] = 0;
   out_6949267687029300227[34] = 1;
   out_6949267687029300227[35] = 0;
   out_6949267687029300227[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6949267687029300227[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6949267687029300227[38] = 0;
   out_6949267687029300227[39] = -state[7];
   out_6949267687029300227[40] = state[6];
   out_6949267687029300227[41] = 0;
   out_6949267687029300227[42] = state[4];
   out_6949267687029300227[43] = -state[3];
   out_6949267687029300227[44] = 0;
   out_6949267687029300227[45] = 0;
   out_6949267687029300227[46] = 0;
   out_6949267687029300227[47] = 0;
   out_6949267687029300227[48] = 0;
   out_6949267687029300227[49] = 0;
   out_6949267687029300227[50] = 1;
   out_6949267687029300227[51] = 0;
   out_6949267687029300227[52] = 0;
   out_6949267687029300227[53] = 1;
}
void h_13(double *state, double *unused, double *out_255680044725993896) {
   out_255680044725993896[0] = state[3];
   out_255680044725993896[1] = state[4];
   out_255680044725993896[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4315427649287152838) {
   out_4315427649287152838[0] = 0;
   out_4315427649287152838[1] = 0;
   out_4315427649287152838[2] = 0;
   out_4315427649287152838[3] = 1;
   out_4315427649287152838[4] = 0;
   out_4315427649287152838[5] = 0;
   out_4315427649287152838[6] = 0;
   out_4315427649287152838[7] = 0;
   out_4315427649287152838[8] = 0;
   out_4315427649287152838[9] = 0;
   out_4315427649287152838[10] = 0;
   out_4315427649287152838[11] = 0;
   out_4315427649287152838[12] = 0;
   out_4315427649287152838[13] = 0;
   out_4315427649287152838[14] = 0;
   out_4315427649287152838[15] = 0;
   out_4315427649287152838[16] = 0;
   out_4315427649287152838[17] = 0;
   out_4315427649287152838[18] = 0;
   out_4315427649287152838[19] = 0;
   out_4315427649287152838[20] = 0;
   out_4315427649287152838[21] = 0;
   out_4315427649287152838[22] = 1;
   out_4315427649287152838[23] = 0;
   out_4315427649287152838[24] = 0;
   out_4315427649287152838[25] = 0;
   out_4315427649287152838[26] = 0;
   out_4315427649287152838[27] = 0;
   out_4315427649287152838[28] = 0;
   out_4315427649287152838[29] = 0;
   out_4315427649287152838[30] = 0;
   out_4315427649287152838[31] = 0;
   out_4315427649287152838[32] = 0;
   out_4315427649287152838[33] = 0;
   out_4315427649287152838[34] = 0;
   out_4315427649287152838[35] = 0;
   out_4315427649287152838[36] = 0;
   out_4315427649287152838[37] = 0;
   out_4315427649287152838[38] = 0;
   out_4315427649287152838[39] = 0;
   out_4315427649287152838[40] = 0;
   out_4315427649287152838[41] = 1;
   out_4315427649287152838[42] = 0;
   out_4315427649287152838[43] = 0;
   out_4315427649287152838[44] = 0;
   out_4315427649287152838[45] = 0;
   out_4315427649287152838[46] = 0;
   out_4315427649287152838[47] = 0;
   out_4315427649287152838[48] = 0;
   out_4315427649287152838[49] = 0;
   out_4315427649287152838[50] = 0;
   out_4315427649287152838[51] = 0;
   out_4315427649287152838[52] = 0;
   out_4315427649287152838[53] = 0;
}
void h_14(double *state, double *unused, double *out_18401598981597761) {
   out_18401598981597761[0] = state[6];
   out_18401598981597761[1] = state[7];
   out_18401598981597761[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1979634608340552259) {
   out_1979634608340552259[0] = 0;
   out_1979634608340552259[1] = 0;
   out_1979634608340552259[2] = 0;
   out_1979634608340552259[3] = 0;
   out_1979634608340552259[4] = 0;
   out_1979634608340552259[5] = 0;
   out_1979634608340552259[6] = 1;
   out_1979634608340552259[7] = 0;
   out_1979634608340552259[8] = 0;
   out_1979634608340552259[9] = 0;
   out_1979634608340552259[10] = 0;
   out_1979634608340552259[11] = 0;
   out_1979634608340552259[12] = 0;
   out_1979634608340552259[13] = 0;
   out_1979634608340552259[14] = 0;
   out_1979634608340552259[15] = 0;
   out_1979634608340552259[16] = 0;
   out_1979634608340552259[17] = 0;
   out_1979634608340552259[18] = 0;
   out_1979634608340552259[19] = 0;
   out_1979634608340552259[20] = 0;
   out_1979634608340552259[21] = 0;
   out_1979634608340552259[22] = 0;
   out_1979634608340552259[23] = 0;
   out_1979634608340552259[24] = 0;
   out_1979634608340552259[25] = 1;
   out_1979634608340552259[26] = 0;
   out_1979634608340552259[27] = 0;
   out_1979634608340552259[28] = 0;
   out_1979634608340552259[29] = 0;
   out_1979634608340552259[30] = 0;
   out_1979634608340552259[31] = 0;
   out_1979634608340552259[32] = 0;
   out_1979634608340552259[33] = 0;
   out_1979634608340552259[34] = 0;
   out_1979634608340552259[35] = 0;
   out_1979634608340552259[36] = 0;
   out_1979634608340552259[37] = 0;
   out_1979634608340552259[38] = 0;
   out_1979634608340552259[39] = 0;
   out_1979634608340552259[40] = 0;
   out_1979634608340552259[41] = 0;
   out_1979634608340552259[42] = 0;
   out_1979634608340552259[43] = 0;
   out_1979634608340552259[44] = 1;
   out_1979634608340552259[45] = 0;
   out_1979634608340552259[46] = 0;
   out_1979634608340552259[47] = 0;
   out_1979634608340552259[48] = 0;
   out_1979634608340552259[49] = 0;
   out_1979634608340552259[50] = 0;
   out_1979634608340552259[51] = 0;
   out_1979634608340552259[52] = 0;
   out_1979634608340552259[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1903961773272735640) {
  err_fun(nom_x, delta_x, out_1903961773272735640);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_573088353517031631) {
  inv_err_fun(nom_x, true_x, out_573088353517031631);
}
void pose_H_mod_fun(double *state, double *out_8399228583696910237) {
  H_mod_fun(state, out_8399228583696910237);
}
void pose_f_fun(double *state, double dt, double *out_7642272888362122250) {
  f_fun(state,  dt, out_7642272888362122250);
}
void pose_F_fun(double *state, double dt, double *out_2644346224160988756) {
  F_fun(state,  dt, out_2644346224160988756);
}
void pose_h_4(double *state, double *unused, double *out_866291291104227919) {
  h_4(state, unused, out_866291291104227919);
}
void pose_H_4(double *state, double *unused, double *out_1103153823954820037) {
  H_4(state, unused, out_1103153823954820037);
}
void pose_h_10(double *state, double *unused, double *out_5833399118122366963) {
  h_10(state, unused, out_5833399118122366963);
}
void pose_H_10(double *state, double *unused, double *out_6949267687029300227) {
  H_10(state, unused, out_6949267687029300227);
}
void pose_h_13(double *state, double *unused, double *out_255680044725993896) {
  h_13(state, unused, out_255680044725993896);
}
void pose_H_13(double *state, double *unused, double *out_4315427649287152838) {
  H_13(state, unused, out_4315427649287152838);
}
void pose_h_14(double *state, double *unused, double *out_18401598981597761) {
  h_14(state, unused, out_18401598981597761);
}
void pose_H_14(double *state, double *unused, double *out_1979634608340552259) {
  H_14(state, unused, out_1979634608340552259);
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
