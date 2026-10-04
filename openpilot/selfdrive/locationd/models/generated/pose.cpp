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
void err_fun(double *nom_x, double *delta_x, double *out_1826050002567019116) {
   out_1826050002567019116[0] = delta_x[0] + nom_x[0];
   out_1826050002567019116[1] = delta_x[1] + nom_x[1];
   out_1826050002567019116[2] = delta_x[2] + nom_x[2];
   out_1826050002567019116[3] = delta_x[3] + nom_x[3];
   out_1826050002567019116[4] = delta_x[4] + nom_x[4];
   out_1826050002567019116[5] = delta_x[5] + nom_x[5];
   out_1826050002567019116[6] = delta_x[6] + nom_x[6];
   out_1826050002567019116[7] = delta_x[7] + nom_x[7];
   out_1826050002567019116[8] = delta_x[8] + nom_x[8];
   out_1826050002567019116[9] = delta_x[9] + nom_x[9];
   out_1826050002567019116[10] = delta_x[10] + nom_x[10];
   out_1826050002567019116[11] = delta_x[11] + nom_x[11];
   out_1826050002567019116[12] = delta_x[12] + nom_x[12];
   out_1826050002567019116[13] = delta_x[13] + nom_x[13];
   out_1826050002567019116[14] = delta_x[14] + nom_x[14];
   out_1826050002567019116[15] = delta_x[15] + nom_x[15];
   out_1826050002567019116[16] = delta_x[16] + nom_x[16];
   out_1826050002567019116[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4637537663232425696) {
   out_4637537663232425696[0] = -nom_x[0] + true_x[0];
   out_4637537663232425696[1] = -nom_x[1] + true_x[1];
   out_4637537663232425696[2] = -nom_x[2] + true_x[2];
   out_4637537663232425696[3] = -nom_x[3] + true_x[3];
   out_4637537663232425696[4] = -nom_x[4] + true_x[4];
   out_4637537663232425696[5] = -nom_x[5] + true_x[5];
   out_4637537663232425696[6] = -nom_x[6] + true_x[6];
   out_4637537663232425696[7] = -nom_x[7] + true_x[7];
   out_4637537663232425696[8] = -nom_x[8] + true_x[8];
   out_4637537663232425696[9] = -nom_x[9] + true_x[9];
   out_4637537663232425696[10] = -nom_x[10] + true_x[10];
   out_4637537663232425696[11] = -nom_x[11] + true_x[11];
   out_4637537663232425696[12] = -nom_x[12] + true_x[12];
   out_4637537663232425696[13] = -nom_x[13] + true_x[13];
   out_4637537663232425696[14] = -nom_x[14] + true_x[14];
   out_4637537663232425696[15] = -nom_x[15] + true_x[15];
   out_4637537663232425696[16] = -nom_x[16] + true_x[16];
   out_4637537663232425696[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5823096309702897011) {
   out_5823096309702897011[0] = 1.0;
   out_5823096309702897011[1] = 0.0;
   out_5823096309702897011[2] = 0.0;
   out_5823096309702897011[3] = 0.0;
   out_5823096309702897011[4] = 0.0;
   out_5823096309702897011[5] = 0.0;
   out_5823096309702897011[6] = 0.0;
   out_5823096309702897011[7] = 0.0;
   out_5823096309702897011[8] = 0.0;
   out_5823096309702897011[9] = 0.0;
   out_5823096309702897011[10] = 0.0;
   out_5823096309702897011[11] = 0.0;
   out_5823096309702897011[12] = 0.0;
   out_5823096309702897011[13] = 0.0;
   out_5823096309702897011[14] = 0.0;
   out_5823096309702897011[15] = 0.0;
   out_5823096309702897011[16] = 0.0;
   out_5823096309702897011[17] = 0.0;
   out_5823096309702897011[18] = 0.0;
   out_5823096309702897011[19] = 1.0;
   out_5823096309702897011[20] = 0.0;
   out_5823096309702897011[21] = 0.0;
   out_5823096309702897011[22] = 0.0;
   out_5823096309702897011[23] = 0.0;
   out_5823096309702897011[24] = 0.0;
   out_5823096309702897011[25] = 0.0;
   out_5823096309702897011[26] = 0.0;
   out_5823096309702897011[27] = 0.0;
   out_5823096309702897011[28] = 0.0;
   out_5823096309702897011[29] = 0.0;
   out_5823096309702897011[30] = 0.0;
   out_5823096309702897011[31] = 0.0;
   out_5823096309702897011[32] = 0.0;
   out_5823096309702897011[33] = 0.0;
   out_5823096309702897011[34] = 0.0;
   out_5823096309702897011[35] = 0.0;
   out_5823096309702897011[36] = 0.0;
   out_5823096309702897011[37] = 0.0;
   out_5823096309702897011[38] = 1.0;
   out_5823096309702897011[39] = 0.0;
   out_5823096309702897011[40] = 0.0;
   out_5823096309702897011[41] = 0.0;
   out_5823096309702897011[42] = 0.0;
   out_5823096309702897011[43] = 0.0;
   out_5823096309702897011[44] = 0.0;
   out_5823096309702897011[45] = 0.0;
   out_5823096309702897011[46] = 0.0;
   out_5823096309702897011[47] = 0.0;
   out_5823096309702897011[48] = 0.0;
   out_5823096309702897011[49] = 0.0;
   out_5823096309702897011[50] = 0.0;
   out_5823096309702897011[51] = 0.0;
   out_5823096309702897011[52] = 0.0;
   out_5823096309702897011[53] = 0.0;
   out_5823096309702897011[54] = 0.0;
   out_5823096309702897011[55] = 0.0;
   out_5823096309702897011[56] = 0.0;
   out_5823096309702897011[57] = 1.0;
   out_5823096309702897011[58] = 0.0;
   out_5823096309702897011[59] = 0.0;
   out_5823096309702897011[60] = 0.0;
   out_5823096309702897011[61] = 0.0;
   out_5823096309702897011[62] = 0.0;
   out_5823096309702897011[63] = 0.0;
   out_5823096309702897011[64] = 0.0;
   out_5823096309702897011[65] = 0.0;
   out_5823096309702897011[66] = 0.0;
   out_5823096309702897011[67] = 0.0;
   out_5823096309702897011[68] = 0.0;
   out_5823096309702897011[69] = 0.0;
   out_5823096309702897011[70] = 0.0;
   out_5823096309702897011[71] = 0.0;
   out_5823096309702897011[72] = 0.0;
   out_5823096309702897011[73] = 0.0;
   out_5823096309702897011[74] = 0.0;
   out_5823096309702897011[75] = 0.0;
   out_5823096309702897011[76] = 1.0;
   out_5823096309702897011[77] = 0.0;
   out_5823096309702897011[78] = 0.0;
   out_5823096309702897011[79] = 0.0;
   out_5823096309702897011[80] = 0.0;
   out_5823096309702897011[81] = 0.0;
   out_5823096309702897011[82] = 0.0;
   out_5823096309702897011[83] = 0.0;
   out_5823096309702897011[84] = 0.0;
   out_5823096309702897011[85] = 0.0;
   out_5823096309702897011[86] = 0.0;
   out_5823096309702897011[87] = 0.0;
   out_5823096309702897011[88] = 0.0;
   out_5823096309702897011[89] = 0.0;
   out_5823096309702897011[90] = 0.0;
   out_5823096309702897011[91] = 0.0;
   out_5823096309702897011[92] = 0.0;
   out_5823096309702897011[93] = 0.0;
   out_5823096309702897011[94] = 0.0;
   out_5823096309702897011[95] = 1.0;
   out_5823096309702897011[96] = 0.0;
   out_5823096309702897011[97] = 0.0;
   out_5823096309702897011[98] = 0.0;
   out_5823096309702897011[99] = 0.0;
   out_5823096309702897011[100] = 0.0;
   out_5823096309702897011[101] = 0.0;
   out_5823096309702897011[102] = 0.0;
   out_5823096309702897011[103] = 0.0;
   out_5823096309702897011[104] = 0.0;
   out_5823096309702897011[105] = 0.0;
   out_5823096309702897011[106] = 0.0;
   out_5823096309702897011[107] = 0.0;
   out_5823096309702897011[108] = 0.0;
   out_5823096309702897011[109] = 0.0;
   out_5823096309702897011[110] = 0.0;
   out_5823096309702897011[111] = 0.0;
   out_5823096309702897011[112] = 0.0;
   out_5823096309702897011[113] = 0.0;
   out_5823096309702897011[114] = 1.0;
   out_5823096309702897011[115] = 0.0;
   out_5823096309702897011[116] = 0.0;
   out_5823096309702897011[117] = 0.0;
   out_5823096309702897011[118] = 0.0;
   out_5823096309702897011[119] = 0.0;
   out_5823096309702897011[120] = 0.0;
   out_5823096309702897011[121] = 0.0;
   out_5823096309702897011[122] = 0.0;
   out_5823096309702897011[123] = 0.0;
   out_5823096309702897011[124] = 0.0;
   out_5823096309702897011[125] = 0.0;
   out_5823096309702897011[126] = 0.0;
   out_5823096309702897011[127] = 0.0;
   out_5823096309702897011[128] = 0.0;
   out_5823096309702897011[129] = 0.0;
   out_5823096309702897011[130] = 0.0;
   out_5823096309702897011[131] = 0.0;
   out_5823096309702897011[132] = 0.0;
   out_5823096309702897011[133] = 1.0;
   out_5823096309702897011[134] = 0.0;
   out_5823096309702897011[135] = 0.0;
   out_5823096309702897011[136] = 0.0;
   out_5823096309702897011[137] = 0.0;
   out_5823096309702897011[138] = 0.0;
   out_5823096309702897011[139] = 0.0;
   out_5823096309702897011[140] = 0.0;
   out_5823096309702897011[141] = 0.0;
   out_5823096309702897011[142] = 0.0;
   out_5823096309702897011[143] = 0.0;
   out_5823096309702897011[144] = 0.0;
   out_5823096309702897011[145] = 0.0;
   out_5823096309702897011[146] = 0.0;
   out_5823096309702897011[147] = 0.0;
   out_5823096309702897011[148] = 0.0;
   out_5823096309702897011[149] = 0.0;
   out_5823096309702897011[150] = 0.0;
   out_5823096309702897011[151] = 0.0;
   out_5823096309702897011[152] = 1.0;
   out_5823096309702897011[153] = 0.0;
   out_5823096309702897011[154] = 0.0;
   out_5823096309702897011[155] = 0.0;
   out_5823096309702897011[156] = 0.0;
   out_5823096309702897011[157] = 0.0;
   out_5823096309702897011[158] = 0.0;
   out_5823096309702897011[159] = 0.0;
   out_5823096309702897011[160] = 0.0;
   out_5823096309702897011[161] = 0.0;
   out_5823096309702897011[162] = 0.0;
   out_5823096309702897011[163] = 0.0;
   out_5823096309702897011[164] = 0.0;
   out_5823096309702897011[165] = 0.0;
   out_5823096309702897011[166] = 0.0;
   out_5823096309702897011[167] = 0.0;
   out_5823096309702897011[168] = 0.0;
   out_5823096309702897011[169] = 0.0;
   out_5823096309702897011[170] = 0.0;
   out_5823096309702897011[171] = 1.0;
   out_5823096309702897011[172] = 0.0;
   out_5823096309702897011[173] = 0.0;
   out_5823096309702897011[174] = 0.0;
   out_5823096309702897011[175] = 0.0;
   out_5823096309702897011[176] = 0.0;
   out_5823096309702897011[177] = 0.0;
   out_5823096309702897011[178] = 0.0;
   out_5823096309702897011[179] = 0.0;
   out_5823096309702897011[180] = 0.0;
   out_5823096309702897011[181] = 0.0;
   out_5823096309702897011[182] = 0.0;
   out_5823096309702897011[183] = 0.0;
   out_5823096309702897011[184] = 0.0;
   out_5823096309702897011[185] = 0.0;
   out_5823096309702897011[186] = 0.0;
   out_5823096309702897011[187] = 0.0;
   out_5823096309702897011[188] = 0.0;
   out_5823096309702897011[189] = 0.0;
   out_5823096309702897011[190] = 1.0;
   out_5823096309702897011[191] = 0.0;
   out_5823096309702897011[192] = 0.0;
   out_5823096309702897011[193] = 0.0;
   out_5823096309702897011[194] = 0.0;
   out_5823096309702897011[195] = 0.0;
   out_5823096309702897011[196] = 0.0;
   out_5823096309702897011[197] = 0.0;
   out_5823096309702897011[198] = 0.0;
   out_5823096309702897011[199] = 0.0;
   out_5823096309702897011[200] = 0.0;
   out_5823096309702897011[201] = 0.0;
   out_5823096309702897011[202] = 0.0;
   out_5823096309702897011[203] = 0.0;
   out_5823096309702897011[204] = 0.0;
   out_5823096309702897011[205] = 0.0;
   out_5823096309702897011[206] = 0.0;
   out_5823096309702897011[207] = 0.0;
   out_5823096309702897011[208] = 0.0;
   out_5823096309702897011[209] = 1.0;
   out_5823096309702897011[210] = 0.0;
   out_5823096309702897011[211] = 0.0;
   out_5823096309702897011[212] = 0.0;
   out_5823096309702897011[213] = 0.0;
   out_5823096309702897011[214] = 0.0;
   out_5823096309702897011[215] = 0.0;
   out_5823096309702897011[216] = 0.0;
   out_5823096309702897011[217] = 0.0;
   out_5823096309702897011[218] = 0.0;
   out_5823096309702897011[219] = 0.0;
   out_5823096309702897011[220] = 0.0;
   out_5823096309702897011[221] = 0.0;
   out_5823096309702897011[222] = 0.0;
   out_5823096309702897011[223] = 0.0;
   out_5823096309702897011[224] = 0.0;
   out_5823096309702897011[225] = 0.0;
   out_5823096309702897011[226] = 0.0;
   out_5823096309702897011[227] = 0.0;
   out_5823096309702897011[228] = 1.0;
   out_5823096309702897011[229] = 0.0;
   out_5823096309702897011[230] = 0.0;
   out_5823096309702897011[231] = 0.0;
   out_5823096309702897011[232] = 0.0;
   out_5823096309702897011[233] = 0.0;
   out_5823096309702897011[234] = 0.0;
   out_5823096309702897011[235] = 0.0;
   out_5823096309702897011[236] = 0.0;
   out_5823096309702897011[237] = 0.0;
   out_5823096309702897011[238] = 0.0;
   out_5823096309702897011[239] = 0.0;
   out_5823096309702897011[240] = 0.0;
   out_5823096309702897011[241] = 0.0;
   out_5823096309702897011[242] = 0.0;
   out_5823096309702897011[243] = 0.0;
   out_5823096309702897011[244] = 0.0;
   out_5823096309702897011[245] = 0.0;
   out_5823096309702897011[246] = 0.0;
   out_5823096309702897011[247] = 1.0;
   out_5823096309702897011[248] = 0.0;
   out_5823096309702897011[249] = 0.0;
   out_5823096309702897011[250] = 0.0;
   out_5823096309702897011[251] = 0.0;
   out_5823096309702897011[252] = 0.0;
   out_5823096309702897011[253] = 0.0;
   out_5823096309702897011[254] = 0.0;
   out_5823096309702897011[255] = 0.0;
   out_5823096309702897011[256] = 0.0;
   out_5823096309702897011[257] = 0.0;
   out_5823096309702897011[258] = 0.0;
   out_5823096309702897011[259] = 0.0;
   out_5823096309702897011[260] = 0.0;
   out_5823096309702897011[261] = 0.0;
   out_5823096309702897011[262] = 0.0;
   out_5823096309702897011[263] = 0.0;
   out_5823096309702897011[264] = 0.0;
   out_5823096309702897011[265] = 0.0;
   out_5823096309702897011[266] = 1.0;
   out_5823096309702897011[267] = 0.0;
   out_5823096309702897011[268] = 0.0;
   out_5823096309702897011[269] = 0.0;
   out_5823096309702897011[270] = 0.0;
   out_5823096309702897011[271] = 0.0;
   out_5823096309702897011[272] = 0.0;
   out_5823096309702897011[273] = 0.0;
   out_5823096309702897011[274] = 0.0;
   out_5823096309702897011[275] = 0.0;
   out_5823096309702897011[276] = 0.0;
   out_5823096309702897011[277] = 0.0;
   out_5823096309702897011[278] = 0.0;
   out_5823096309702897011[279] = 0.0;
   out_5823096309702897011[280] = 0.0;
   out_5823096309702897011[281] = 0.0;
   out_5823096309702897011[282] = 0.0;
   out_5823096309702897011[283] = 0.0;
   out_5823096309702897011[284] = 0.0;
   out_5823096309702897011[285] = 1.0;
   out_5823096309702897011[286] = 0.0;
   out_5823096309702897011[287] = 0.0;
   out_5823096309702897011[288] = 0.0;
   out_5823096309702897011[289] = 0.0;
   out_5823096309702897011[290] = 0.0;
   out_5823096309702897011[291] = 0.0;
   out_5823096309702897011[292] = 0.0;
   out_5823096309702897011[293] = 0.0;
   out_5823096309702897011[294] = 0.0;
   out_5823096309702897011[295] = 0.0;
   out_5823096309702897011[296] = 0.0;
   out_5823096309702897011[297] = 0.0;
   out_5823096309702897011[298] = 0.0;
   out_5823096309702897011[299] = 0.0;
   out_5823096309702897011[300] = 0.0;
   out_5823096309702897011[301] = 0.0;
   out_5823096309702897011[302] = 0.0;
   out_5823096309702897011[303] = 0.0;
   out_5823096309702897011[304] = 1.0;
   out_5823096309702897011[305] = 0.0;
   out_5823096309702897011[306] = 0.0;
   out_5823096309702897011[307] = 0.0;
   out_5823096309702897011[308] = 0.0;
   out_5823096309702897011[309] = 0.0;
   out_5823096309702897011[310] = 0.0;
   out_5823096309702897011[311] = 0.0;
   out_5823096309702897011[312] = 0.0;
   out_5823096309702897011[313] = 0.0;
   out_5823096309702897011[314] = 0.0;
   out_5823096309702897011[315] = 0.0;
   out_5823096309702897011[316] = 0.0;
   out_5823096309702897011[317] = 0.0;
   out_5823096309702897011[318] = 0.0;
   out_5823096309702897011[319] = 0.0;
   out_5823096309702897011[320] = 0.0;
   out_5823096309702897011[321] = 0.0;
   out_5823096309702897011[322] = 0.0;
   out_5823096309702897011[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4447474560046678856) {
   out_4447474560046678856[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4447474560046678856[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4447474560046678856[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4447474560046678856[3] = dt*state[12] + state[3];
   out_4447474560046678856[4] = dt*state[13] + state[4];
   out_4447474560046678856[5] = dt*state[14] + state[5];
   out_4447474560046678856[6] = state[6];
   out_4447474560046678856[7] = state[7];
   out_4447474560046678856[8] = state[8];
   out_4447474560046678856[9] = state[9];
   out_4447474560046678856[10] = state[10];
   out_4447474560046678856[11] = state[11];
   out_4447474560046678856[12] = state[12];
   out_4447474560046678856[13] = state[13];
   out_4447474560046678856[14] = state[14];
   out_4447474560046678856[15] = state[15];
   out_4447474560046678856[16] = state[16];
   out_4447474560046678856[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1876724253576652183) {
   out_1876724253576652183[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1876724253576652183[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1876724253576652183[2] = 0;
   out_1876724253576652183[3] = 0;
   out_1876724253576652183[4] = 0;
   out_1876724253576652183[5] = 0;
   out_1876724253576652183[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1876724253576652183[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1876724253576652183[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1876724253576652183[9] = 0;
   out_1876724253576652183[10] = 0;
   out_1876724253576652183[11] = 0;
   out_1876724253576652183[12] = 0;
   out_1876724253576652183[13] = 0;
   out_1876724253576652183[14] = 0;
   out_1876724253576652183[15] = 0;
   out_1876724253576652183[16] = 0;
   out_1876724253576652183[17] = 0;
   out_1876724253576652183[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1876724253576652183[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1876724253576652183[20] = 0;
   out_1876724253576652183[21] = 0;
   out_1876724253576652183[22] = 0;
   out_1876724253576652183[23] = 0;
   out_1876724253576652183[24] = 0;
   out_1876724253576652183[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1876724253576652183[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1876724253576652183[27] = 0;
   out_1876724253576652183[28] = 0;
   out_1876724253576652183[29] = 0;
   out_1876724253576652183[30] = 0;
   out_1876724253576652183[31] = 0;
   out_1876724253576652183[32] = 0;
   out_1876724253576652183[33] = 0;
   out_1876724253576652183[34] = 0;
   out_1876724253576652183[35] = 0;
   out_1876724253576652183[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1876724253576652183[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1876724253576652183[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1876724253576652183[39] = 0;
   out_1876724253576652183[40] = 0;
   out_1876724253576652183[41] = 0;
   out_1876724253576652183[42] = 0;
   out_1876724253576652183[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1876724253576652183[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1876724253576652183[45] = 0;
   out_1876724253576652183[46] = 0;
   out_1876724253576652183[47] = 0;
   out_1876724253576652183[48] = 0;
   out_1876724253576652183[49] = 0;
   out_1876724253576652183[50] = 0;
   out_1876724253576652183[51] = 0;
   out_1876724253576652183[52] = 0;
   out_1876724253576652183[53] = 0;
   out_1876724253576652183[54] = 0;
   out_1876724253576652183[55] = 0;
   out_1876724253576652183[56] = 0;
   out_1876724253576652183[57] = 1;
   out_1876724253576652183[58] = 0;
   out_1876724253576652183[59] = 0;
   out_1876724253576652183[60] = 0;
   out_1876724253576652183[61] = 0;
   out_1876724253576652183[62] = 0;
   out_1876724253576652183[63] = 0;
   out_1876724253576652183[64] = 0;
   out_1876724253576652183[65] = 0;
   out_1876724253576652183[66] = dt;
   out_1876724253576652183[67] = 0;
   out_1876724253576652183[68] = 0;
   out_1876724253576652183[69] = 0;
   out_1876724253576652183[70] = 0;
   out_1876724253576652183[71] = 0;
   out_1876724253576652183[72] = 0;
   out_1876724253576652183[73] = 0;
   out_1876724253576652183[74] = 0;
   out_1876724253576652183[75] = 0;
   out_1876724253576652183[76] = 1;
   out_1876724253576652183[77] = 0;
   out_1876724253576652183[78] = 0;
   out_1876724253576652183[79] = 0;
   out_1876724253576652183[80] = 0;
   out_1876724253576652183[81] = 0;
   out_1876724253576652183[82] = 0;
   out_1876724253576652183[83] = 0;
   out_1876724253576652183[84] = 0;
   out_1876724253576652183[85] = dt;
   out_1876724253576652183[86] = 0;
   out_1876724253576652183[87] = 0;
   out_1876724253576652183[88] = 0;
   out_1876724253576652183[89] = 0;
   out_1876724253576652183[90] = 0;
   out_1876724253576652183[91] = 0;
   out_1876724253576652183[92] = 0;
   out_1876724253576652183[93] = 0;
   out_1876724253576652183[94] = 0;
   out_1876724253576652183[95] = 1;
   out_1876724253576652183[96] = 0;
   out_1876724253576652183[97] = 0;
   out_1876724253576652183[98] = 0;
   out_1876724253576652183[99] = 0;
   out_1876724253576652183[100] = 0;
   out_1876724253576652183[101] = 0;
   out_1876724253576652183[102] = 0;
   out_1876724253576652183[103] = 0;
   out_1876724253576652183[104] = dt;
   out_1876724253576652183[105] = 0;
   out_1876724253576652183[106] = 0;
   out_1876724253576652183[107] = 0;
   out_1876724253576652183[108] = 0;
   out_1876724253576652183[109] = 0;
   out_1876724253576652183[110] = 0;
   out_1876724253576652183[111] = 0;
   out_1876724253576652183[112] = 0;
   out_1876724253576652183[113] = 0;
   out_1876724253576652183[114] = 1;
   out_1876724253576652183[115] = 0;
   out_1876724253576652183[116] = 0;
   out_1876724253576652183[117] = 0;
   out_1876724253576652183[118] = 0;
   out_1876724253576652183[119] = 0;
   out_1876724253576652183[120] = 0;
   out_1876724253576652183[121] = 0;
   out_1876724253576652183[122] = 0;
   out_1876724253576652183[123] = 0;
   out_1876724253576652183[124] = 0;
   out_1876724253576652183[125] = 0;
   out_1876724253576652183[126] = 0;
   out_1876724253576652183[127] = 0;
   out_1876724253576652183[128] = 0;
   out_1876724253576652183[129] = 0;
   out_1876724253576652183[130] = 0;
   out_1876724253576652183[131] = 0;
   out_1876724253576652183[132] = 0;
   out_1876724253576652183[133] = 1;
   out_1876724253576652183[134] = 0;
   out_1876724253576652183[135] = 0;
   out_1876724253576652183[136] = 0;
   out_1876724253576652183[137] = 0;
   out_1876724253576652183[138] = 0;
   out_1876724253576652183[139] = 0;
   out_1876724253576652183[140] = 0;
   out_1876724253576652183[141] = 0;
   out_1876724253576652183[142] = 0;
   out_1876724253576652183[143] = 0;
   out_1876724253576652183[144] = 0;
   out_1876724253576652183[145] = 0;
   out_1876724253576652183[146] = 0;
   out_1876724253576652183[147] = 0;
   out_1876724253576652183[148] = 0;
   out_1876724253576652183[149] = 0;
   out_1876724253576652183[150] = 0;
   out_1876724253576652183[151] = 0;
   out_1876724253576652183[152] = 1;
   out_1876724253576652183[153] = 0;
   out_1876724253576652183[154] = 0;
   out_1876724253576652183[155] = 0;
   out_1876724253576652183[156] = 0;
   out_1876724253576652183[157] = 0;
   out_1876724253576652183[158] = 0;
   out_1876724253576652183[159] = 0;
   out_1876724253576652183[160] = 0;
   out_1876724253576652183[161] = 0;
   out_1876724253576652183[162] = 0;
   out_1876724253576652183[163] = 0;
   out_1876724253576652183[164] = 0;
   out_1876724253576652183[165] = 0;
   out_1876724253576652183[166] = 0;
   out_1876724253576652183[167] = 0;
   out_1876724253576652183[168] = 0;
   out_1876724253576652183[169] = 0;
   out_1876724253576652183[170] = 0;
   out_1876724253576652183[171] = 1;
   out_1876724253576652183[172] = 0;
   out_1876724253576652183[173] = 0;
   out_1876724253576652183[174] = 0;
   out_1876724253576652183[175] = 0;
   out_1876724253576652183[176] = 0;
   out_1876724253576652183[177] = 0;
   out_1876724253576652183[178] = 0;
   out_1876724253576652183[179] = 0;
   out_1876724253576652183[180] = 0;
   out_1876724253576652183[181] = 0;
   out_1876724253576652183[182] = 0;
   out_1876724253576652183[183] = 0;
   out_1876724253576652183[184] = 0;
   out_1876724253576652183[185] = 0;
   out_1876724253576652183[186] = 0;
   out_1876724253576652183[187] = 0;
   out_1876724253576652183[188] = 0;
   out_1876724253576652183[189] = 0;
   out_1876724253576652183[190] = 1;
   out_1876724253576652183[191] = 0;
   out_1876724253576652183[192] = 0;
   out_1876724253576652183[193] = 0;
   out_1876724253576652183[194] = 0;
   out_1876724253576652183[195] = 0;
   out_1876724253576652183[196] = 0;
   out_1876724253576652183[197] = 0;
   out_1876724253576652183[198] = 0;
   out_1876724253576652183[199] = 0;
   out_1876724253576652183[200] = 0;
   out_1876724253576652183[201] = 0;
   out_1876724253576652183[202] = 0;
   out_1876724253576652183[203] = 0;
   out_1876724253576652183[204] = 0;
   out_1876724253576652183[205] = 0;
   out_1876724253576652183[206] = 0;
   out_1876724253576652183[207] = 0;
   out_1876724253576652183[208] = 0;
   out_1876724253576652183[209] = 1;
   out_1876724253576652183[210] = 0;
   out_1876724253576652183[211] = 0;
   out_1876724253576652183[212] = 0;
   out_1876724253576652183[213] = 0;
   out_1876724253576652183[214] = 0;
   out_1876724253576652183[215] = 0;
   out_1876724253576652183[216] = 0;
   out_1876724253576652183[217] = 0;
   out_1876724253576652183[218] = 0;
   out_1876724253576652183[219] = 0;
   out_1876724253576652183[220] = 0;
   out_1876724253576652183[221] = 0;
   out_1876724253576652183[222] = 0;
   out_1876724253576652183[223] = 0;
   out_1876724253576652183[224] = 0;
   out_1876724253576652183[225] = 0;
   out_1876724253576652183[226] = 0;
   out_1876724253576652183[227] = 0;
   out_1876724253576652183[228] = 1;
   out_1876724253576652183[229] = 0;
   out_1876724253576652183[230] = 0;
   out_1876724253576652183[231] = 0;
   out_1876724253576652183[232] = 0;
   out_1876724253576652183[233] = 0;
   out_1876724253576652183[234] = 0;
   out_1876724253576652183[235] = 0;
   out_1876724253576652183[236] = 0;
   out_1876724253576652183[237] = 0;
   out_1876724253576652183[238] = 0;
   out_1876724253576652183[239] = 0;
   out_1876724253576652183[240] = 0;
   out_1876724253576652183[241] = 0;
   out_1876724253576652183[242] = 0;
   out_1876724253576652183[243] = 0;
   out_1876724253576652183[244] = 0;
   out_1876724253576652183[245] = 0;
   out_1876724253576652183[246] = 0;
   out_1876724253576652183[247] = 1;
   out_1876724253576652183[248] = 0;
   out_1876724253576652183[249] = 0;
   out_1876724253576652183[250] = 0;
   out_1876724253576652183[251] = 0;
   out_1876724253576652183[252] = 0;
   out_1876724253576652183[253] = 0;
   out_1876724253576652183[254] = 0;
   out_1876724253576652183[255] = 0;
   out_1876724253576652183[256] = 0;
   out_1876724253576652183[257] = 0;
   out_1876724253576652183[258] = 0;
   out_1876724253576652183[259] = 0;
   out_1876724253576652183[260] = 0;
   out_1876724253576652183[261] = 0;
   out_1876724253576652183[262] = 0;
   out_1876724253576652183[263] = 0;
   out_1876724253576652183[264] = 0;
   out_1876724253576652183[265] = 0;
   out_1876724253576652183[266] = 1;
   out_1876724253576652183[267] = 0;
   out_1876724253576652183[268] = 0;
   out_1876724253576652183[269] = 0;
   out_1876724253576652183[270] = 0;
   out_1876724253576652183[271] = 0;
   out_1876724253576652183[272] = 0;
   out_1876724253576652183[273] = 0;
   out_1876724253576652183[274] = 0;
   out_1876724253576652183[275] = 0;
   out_1876724253576652183[276] = 0;
   out_1876724253576652183[277] = 0;
   out_1876724253576652183[278] = 0;
   out_1876724253576652183[279] = 0;
   out_1876724253576652183[280] = 0;
   out_1876724253576652183[281] = 0;
   out_1876724253576652183[282] = 0;
   out_1876724253576652183[283] = 0;
   out_1876724253576652183[284] = 0;
   out_1876724253576652183[285] = 1;
   out_1876724253576652183[286] = 0;
   out_1876724253576652183[287] = 0;
   out_1876724253576652183[288] = 0;
   out_1876724253576652183[289] = 0;
   out_1876724253576652183[290] = 0;
   out_1876724253576652183[291] = 0;
   out_1876724253576652183[292] = 0;
   out_1876724253576652183[293] = 0;
   out_1876724253576652183[294] = 0;
   out_1876724253576652183[295] = 0;
   out_1876724253576652183[296] = 0;
   out_1876724253576652183[297] = 0;
   out_1876724253576652183[298] = 0;
   out_1876724253576652183[299] = 0;
   out_1876724253576652183[300] = 0;
   out_1876724253576652183[301] = 0;
   out_1876724253576652183[302] = 0;
   out_1876724253576652183[303] = 0;
   out_1876724253576652183[304] = 1;
   out_1876724253576652183[305] = 0;
   out_1876724253576652183[306] = 0;
   out_1876724253576652183[307] = 0;
   out_1876724253576652183[308] = 0;
   out_1876724253576652183[309] = 0;
   out_1876724253576652183[310] = 0;
   out_1876724253576652183[311] = 0;
   out_1876724253576652183[312] = 0;
   out_1876724253576652183[313] = 0;
   out_1876724253576652183[314] = 0;
   out_1876724253576652183[315] = 0;
   out_1876724253576652183[316] = 0;
   out_1876724253576652183[317] = 0;
   out_1876724253576652183[318] = 0;
   out_1876724253576652183[319] = 0;
   out_1876724253576652183[320] = 0;
   out_1876724253576652183[321] = 0;
   out_1876724253576652183[322] = 0;
   out_1876724253576652183[323] = 1;
}
void h_4(double *state, double *unused, double *out_5870638379975225029) {
   out_5870638379975225029[0] = state[6] + state[9];
   out_5870638379975225029[1] = state[7] + state[10];
   out_5870638379975225029[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3121265356354924331) {
   out_3121265356354924331[0] = 0;
   out_3121265356354924331[1] = 0;
   out_3121265356354924331[2] = 0;
   out_3121265356354924331[3] = 0;
   out_3121265356354924331[4] = 0;
   out_3121265356354924331[5] = 0;
   out_3121265356354924331[6] = 1;
   out_3121265356354924331[7] = 0;
   out_3121265356354924331[8] = 0;
   out_3121265356354924331[9] = 1;
   out_3121265356354924331[10] = 0;
   out_3121265356354924331[11] = 0;
   out_3121265356354924331[12] = 0;
   out_3121265356354924331[13] = 0;
   out_3121265356354924331[14] = 0;
   out_3121265356354924331[15] = 0;
   out_3121265356354924331[16] = 0;
   out_3121265356354924331[17] = 0;
   out_3121265356354924331[18] = 0;
   out_3121265356354924331[19] = 0;
   out_3121265356354924331[20] = 0;
   out_3121265356354924331[21] = 0;
   out_3121265356354924331[22] = 0;
   out_3121265356354924331[23] = 0;
   out_3121265356354924331[24] = 0;
   out_3121265356354924331[25] = 1;
   out_3121265356354924331[26] = 0;
   out_3121265356354924331[27] = 0;
   out_3121265356354924331[28] = 1;
   out_3121265356354924331[29] = 0;
   out_3121265356354924331[30] = 0;
   out_3121265356354924331[31] = 0;
   out_3121265356354924331[32] = 0;
   out_3121265356354924331[33] = 0;
   out_3121265356354924331[34] = 0;
   out_3121265356354924331[35] = 0;
   out_3121265356354924331[36] = 0;
   out_3121265356354924331[37] = 0;
   out_3121265356354924331[38] = 0;
   out_3121265356354924331[39] = 0;
   out_3121265356354924331[40] = 0;
   out_3121265356354924331[41] = 0;
   out_3121265356354924331[42] = 0;
   out_3121265356354924331[43] = 0;
   out_3121265356354924331[44] = 1;
   out_3121265356354924331[45] = 0;
   out_3121265356354924331[46] = 0;
   out_3121265356354924331[47] = 1;
   out_3121265356354924331[48] = 0;
   out_3121265356354924331[49] = 0;
   out_3121265356354924331[50] = 0;
   out_3121265356354924331[51] = 0;
   out_3121265356354924331[52] = 0;
   out_3121265356354924331[53] = 0;
}
void h_10(double *state, double *unused, double *out_8351966239607778150) {
   out_8351966239607778150[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8351966239607778150[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8351966239607778150[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5853760429658336434) {
   out_5853760429658336434[0] = 0;
   out_5853760429658336434[1] = 9.8100000000000005*cos(state[1]);
   out_5853760429658336434[2] = 0;
   out_5853760429658336434[3] = 0;
   out_5853760429658336434[4] = -state[8];
   out_5853760429658336434[5] = state[7];
   out_5853760429658336434[6] = 0;
   out_5853760429658336434[7] = state[5];
   out_5853760429658336434[8] = -state[4];
   out_5853760429658336434[9] = 0;
   out_5853760429658336434[10] = 0;
   out_5853760429658336434[11] = 0;
   out_5853760429658336434[12] = 1;
   out_5853760429658336434[13] = 0;
   out_5853760429658336434[14] = 0;
   out_5853760429658336434[15] = 1;
   out_5853760429658336434[16] = 0;
   out_5853760429658336434[17] = 0;
   out_5853760429658336434[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5853760429658336434[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5853760429658336434[20] = 0;
   out_5853760429658336434[21] = state[8];
   out_5853760429658336434[22] = 0;
   out_5853760429658336434[23] = -state[6];
   out_5853760429658336434[24] = -state[5];
   out_5853760429658336434[25] = 0;
   out_5853760429658336434[26] = state[3];
   out_5853760429658336434[27] = 0;
   out_5853760429658336434[28] = 0;
   out_5853760429658336434[29] = 0;
   out_5853760429658336434[30] = 0;
   out_5853760429658336434[31] = 1;
   out_5853760429658336434[32] = 0;
   out_5853760429658336434[33] = 0;
   out_5853760429658336434[34] = 1;
   out_5853760429658336434[35] = 0;
   out_5853760429658336434[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5853760429658336434[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5853760429658336434[38] = 0;
   out_5853760429658336434[39] = -state[7];
   out_5853760429658336434[40] = state[6];
   out_5853760429658336434[41] = 0;
   out_5853760429658336434[42] = state[4];
   out_5853760429658336434[43] = -state[3];
   out_5853760429658336434[44] = 0;
   out_5853760429658336434[45] = 0;
   out_5853760429658336434[46] = 0;
   out_5853760429658336434[47] = 0;
   out_5853760429658336434[48] = 0;
   out_5853760429658336434[49] = 0;
   out_5853760429658336434[50] = 1;
   out_5853760429658336434[51] = 0;
   out_5853760429658336434[52] = 0;
   out_5853760429658336434[53] = 1;
}
void h_13(double *state, double *unused, double *out_1331349399792691795) {
   out_1331349399792691795[0] = state[3];
   out_1331349399792691795[1] = state[4];
   out_1331349399792691795[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6955020819657448355) {
   out_6955020819657448355[0] = 0;
   out_6955020819657448355[1] = 0;
   out_6955020819657448355[2] = 0;
   out_6955020819657448355[3] = 1;
   out_6955020819657448355[4] = 0;
   out_6955020819657448355[5] = 0;
   out_6955020819657448355[6] = 0;
   out_6955020819657448355[7] = 0;
   out_6955020819657448355[8] = 0;
   out_6955020819657448355[9] = 0;
   out_6955020819657448355[10] = 0;
   out_6955020819657448355[11] = 0;
   out_6955020819657448355[12] = 0;
   out_6955020819657448355[13] = 0;
   out_6955020819657448355[14] = 0;
   out_6955020819657448355[15] = 0;
   out_6955020819657448355[16] = 0;
   out_6955020819657448355[17] = 0;
   out_6955020819657448355[18] = 0;
   out_6955020819657448355[19] = 0;
   out_6955020819657448355[20] = 0;
   out_6955020819657448355[21] = 0;
   out_6955020819657448355[22] = 1;
   out_6955020819657448355[23] = 0;
   out_6955020819657448355[24] = 0;
   out_6955020819657448355[25] = 0;
   out_6955020819657448355[26] = 0;
   out_6955020819657448355[27] = 0;
   out_6955020819657448355[28] = 0;
   out_6955020819657448355[29] = 0;
   out_6955020819657448355[30] = 0;
   out_6955020819657448355[31] = 0;
   out_6955020819657448355[32] = 0;
   out_6955020819657448355[33] = 0;
   out_6955020819657448355[34] = 0;
   out_6955020819657448355[35] = 0;
   out_6955020819657448355[36] = 0;
   out_6955020819657448355[37] = 0;
   out_6955020819657448355[38] = 0;
   out_6955020819657448355[39] = 0;
   out_6955020819657448355[40] = 0;
   out_6955020819657448355[41] = 1;
   out_6955020819657448355[42] = 0;
   out_6955020819657448355[43] = 0;
   out_6955020819657448355[44] = 0;
   out_6955020819657448355[45] = 0;
   out_6955020819657448355[46] = 0;
   out_6955020819657448355[47] = 0;
   out_6955020819657448355[48] = 0;
   out_6955020819657448355[49] = 0;
   out_6955020819657448355[50] = 0;
   out_6955020819657448355[51] = 0;
   out_6955020819657448355[52] = 0;
   out_6955020819657448355[53] = 0;
}
void h_14(double *state, double *unused, double *out_1044143545257583313) {
   out_1044143545257583313[0] = state[6];
   out_1044143545257583313[1] = state[7];
   out_1044143545257583313[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6204053788650296627) {
   out_6204053788650296627[0] = 0;
   out_6204053788650296627[1] = 0;
   out_6204053788650296627[2] = 0;
   out_6204053788650296627[3] = 0;
   out_6204053788650296627[4] = 0;
   out_6204053788650296627[5] = 0;
   out_6204053788650296627[6] = 1;
   out_6204053788650296627[7] = 0;
   out_6204053788650296627[8] = 0;
   out_6204053788650296627[9] = 0;
   out_6204053788650296627[10] = 0;
   out_6204053788650296627[11] = 0;
   out_6204053788650296627[12] = 0;
   out_6204053788650296627[13] = 0;
   out_6204053788650296627[14] = 0;
   out_6204053788650296627[15] = 0;
   out_6204053788650296627[16] = 0;
   out_6204053788650296627[17] = 0;
   out_6204053788650296627[18] = 0;
   out_6204053788650296627[19] = 0;
   out_6204053788650296627[20] = 0;
   out_6204053788650296627[21] = 0;
   out_6204053788650296627[22] = 0;
   out_6204053788650296627[23] = 0;
   out_6204053788650296627[24] = 0;
   out_6204053788650296627[25] = 1;
   out_6204053788650296627[26] = 0;
   out_6204053788650296627[27] = 0;
   out_6204053788650296627[28] = 0;
   out_6204053788650296627[29] = 0;
   out_6204053788650296627[30] = 0;
   out_6204053788650296627[31] = 0;
   out_6204053788650296627[32] = 0;
   out_6204053788650296627[33] = 0;
   out_6204053788650296627[34] = 0;
   out_6204053788650296627[35] = 0;
   out_6204053788650296627[36] = 0;
   out_6204053788650296627[37] = 0;
   out_6204053788650296627[38] = 0;
   out_6204053788650296627[39] = 0;
   out_6204053788650296627[40] = 0;
   out_6204053788650296627[41] = 0;
   out_6204053788650296627[42] = 0;
   out_6204053788650296627[43] = 0;
   out_6204053788650296627[44] = 1;
   out_6204053788650296627[45] = 0;
   out_6204053788650296627[46] = 0;
   out_6204053788650296627[47] = 0;
   out_6204053788650296627[48] = 0;
   out_6204053788650296627[49] = 0;
   out_6204053788650296627[50] = 0;
   out_6204053788650296627[51] = 0;
   out_6204053788650296627[52] = 0;
   out_6204053788650296627[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1826050002567019116) {
  err_fun(nom_x, delta_x, out_1826050002567019116);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4637537663232425696) {
  inv_err_fun(nom_x, true_x, out_4637537663232425696);
}
void pose_H_mod_fun(double *state, double *out_5823096309702897011) {
  H_mod_fun(state, out_5823096309702897011);
}
void pose_f_fun(double *state, double dt, double *out_4447474560046678856) {
  f_fun(state,  dt, out_4447474560046678856);
}
void pose_F_fun(double *state, double dt, double *out_1876724253576652183) {
  F_fun(state,  dt, out_1876724253576652183);
}
void pose_h_4(double *state, double *unused, double *out_5870638379975225029) {
  h_4(state, unused, out_5870638379975225029);
}
void pose_H_4(double *state, double *unused, double *out_3121265356354924331) {
  H_4(state, unused, out_3121265356354924331);
}
void pose_h_10(double *state, double *unused, double *out_8351966239607778150) {
  h_10(state, unused, out_8351966239607778150);
}
void pose_H_10(double *state, double *unused, double *out_5853760429658336434) {
  H_10(state, unused, out_5853760429658336434);
}
void pose_h_13(double *state, double *unused, double *out_1331349399792691795) {
  h_13(state, unused, out_1331349399792691795);
}
void pose_H_13(double *state, double *unused, double *out_6955020819657448355) {
  H_13(state, unused, out_6955020819657448355);
}
void pose_h_14(double *state, double *unused, double *out_1044143545257583313) {
  h_14(state, unused, out_1044143545257583313);
}
void pose_H_14(double *state, double *unused, double *out_6204053788650296627) {
  H_14(state, unused, out_6204053788650296627);
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
