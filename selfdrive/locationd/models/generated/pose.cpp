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
void err_fun(double *nom_x, double *delta_x, double *out_2182538694400222550) {
   out_2182538694400222550[0] = delta_x[0] + nom_x[0];
   out_2182538694400222550[1] = delta_x[1] + nom_x[1];
   out_2182538694400222550[2] = delta_x[2] + nom_x[2];
   out_2182538694400222550[3] = delta_x[3] + nom_x[3];
   out_2182538694400222550[4] = delta_x[4] + nom_x[4];
   out_2182538694400222550[5] = delta_x[5] + nom_x[5];
   out_2182538694400222550[6] = delta_x[6] + nom_x[6];
   out_2182538694400222550[7] = delta_x[7] + nom_x[7];
   out_2182538694400222550[8] = delta_x[8] + nom_x[8];
   out_2182538694400222550[9] = delta_x[9] + nom_x[9];
   out_2182538694400222550[10] = delta_x[10] + nom_x[10];
   out_2182538694400222550[11] = delta_x[11] + nom_x[11];
   out_2182538694400222550[12] = delta_x[12] + nom_x[12];
   out_2182538694400222550[13] = delta_x[13] + nom_x[13];
   out_2182538694400222550[14] = delta_x[14] + nom_x[14];
   out_2182538694400222550[15] = delta_x[15] + nom_x[15];
   out_2182538694400222550[16] = delta_x[16] + nom_x[16];
   out_2182538694400222550[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3636770726618230824) {
   out_3636770726618230824[0] = -nom_x[0] + true_x[0];
   out_3636770726618230824[1] = -nom_x[1] + true_x[1];
   out_3636770726618230824[2] = -nom_x[2] + true_x[2];
   out_3636770726618230824[3] = -nom_x[3] + true_x[3];
   out_3636770726618230824[4] = -nom_x[4] + true_x[4];
   out_3636770726618230824[5] = -nom_x[5] + true_x[5];
   out_3636770726618230824[6] = -nom_x[6] + true_x[6];
   out_3636770726618230824[7] = -nom_x[7] + true_x[7];
   out_3636770726618230824[8] = -nom_x[8] + true_x[8];
   out_3636770726618230824[9] = -nom_x[9] + true_x[9];
   out_3636770726618230824[10] = -nom_x[10] + true_x[10];
   out_3636770726618230824[11] = -nom_x[11] + true_x[11];
   out_3636770726618230824[12] = -nom_x[12] + true_x[12];
   out_3636770726618230824[13] = -nom_x[13] + true_x[13];
   out_3636770726618230824[14] = -nom_x[14] + true_x[14];
   out_3636770726618230824[15] = -nom_x[15] + true_x[15];
   out_3636770726618230824[16] = -nom_x[16] + true_x[16];
   out_3636770726618230824[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5732313931484354230) {
   out_5732313931484354230[0] = 1.0;
   out_5732313931484354230[1] = 0.0;
   out_5732313931484354230[2] = 0.0;
   out_5732313931484354230[3] = 0.0;
   out_5732313931484354230[4] = 0.0;
   out_5732313931484354230[5] = 0.0;
   out_5732313931484354230[6] = 0.0;
   out_5732313931484354230[7] = 0.0;
   out_5732313931484354230[8] = 0.0;
   out_5732313931484354230[9] = 0.0;
   out_5732313931484354230[10] = 0.0;
   out_5732313931484354230[11] = 0.0;
   out_5732313931484354230[12] = 0.0;
   out_5732313931484354230[13] = 0.0;
   out_5732313931484354230[14] = 0.0;
   out_5732313931484354230[15] = 0.0;
   out_5732313931484354230[16] = 0.0;
   out_5732313931484354230[17] = 0.0;
   out_5732313931484354230[18] = 0.0;
   out_5732313931484354230[19] = 1.0;
   out_5732313931484354230[20] = 0.0;
   out_5732313931484354230[21] = 0.0;
   out_5732313931484354230[22] = 0.0;
   out_5732313931484354230[23] = 0.0;
   out_5732313931484354230[24] = 0.0;
   out_5732313931484354230[25] = 0.0;
   out_5732313931484354230[26] = 0.0;
   out_5732313931484354230[27] = 0.0;
   out_5732313931484354230[28] = 0.0;
   out_5732313931484354230[29] = 0.0;
   out_5732313931484354230[30] = 0.0;
   out_5732313931484354230[31] = 0.0;
   out_5732313931484354230[32] = 0.0;
   out_5732313931484354230[33] = 0.0;
   out_5732313931484354230[34] = 0.0;
   out_5732313931484354230[35] = 0.0;
   out_5732313931484354230[36] = 0.0;
   out_5732313931484354230[37] = 0.0;
   out_5732313931484354230[38] = 1.0;
   out_5732313931484354230[39] = 0.0;
   out_5732313931484354230[40] = 0.0;
   out_5732313931484354230[41] = 0.0;
   out_5732313931484354230[42] = 0.0;
   out_5732313931484354230[43] = 0.0;
   out_5732313931484354230[44] = 0.0;
   out_5732313931484354230[45] = 0.0;
   out_5732313931484354230[46] = 0.0;
   out_5732313931484354230[47] = 0.0;
   out_5732313931484354230[48] = 0.0;
   out_5732313931484354230[49] = 0.0;
   out_5732313931484354230[50] = 0.0;
   out_5732313931484354230[51] = 0.0;
   out_5732313931484354230[52] = 0.0;
   out_5732313931484354230[53] = 0.0;
   out_5732313931484354230[54] = 0.0;
   out_5732313931484354230[55] = 0.0;
   out_5732313931484354230[56] = 0.0;
   out_5732313931484354230[57] = 1.0;
   out_5732313931484354230[58] = 0.0;
   out_5732313931484354230[59] = 0.0;
   out_5732313931484354230[60] = 0.0;
   out_5732313931484354230[61] = 0.0;
   out_5732313931484354230[62] = 0.0;
   out_5732313931484354230[63] = 0.0;
   out_5732313931484354230[64] = 0.0;
   out_5732313931484354230[65] = 0.0;
   out_5732313931484354230[66] = 0.0;
   out_5732313931484354230[67] = 0.0;
   out_5732313931484354230[68] = 0.0;
   out_5732313931484354230[69] = 0.0;
   out_5732313931484354230[70] = 0.0;
   out_5732313931484354230[71] = 0.0;
   out_5732313931484354230[72] = 0.0;
   out_5732313931484354230[73] = 0.0;
   out_5732313931484354230[74] = 0.0;
   out_5732313931484354230[75] = 0.0;
   out_5732313931484354230[76] = 1.0;
   out_5732313931484354230[77] = 0.0;
   out_5732313931484354230[78] = 0.0;
   out_5732313931484354230[79] = 0.0;
   out_5732313931484354230[80] = 0.0;
   out_5732313931484354230[81] = 0.0;
   out_5732313931484354230[82] = 0.0;
   out_5732313931484354230[83] = 0.0;
   out_5732313931484354230[84] = 0.0;
   out_5732313931484354230[85] = 0.0;
   out_5732313931484354230[86] = 0.0;
   out_5732313931484354230[87] = 0.0;
   out_5732313931484354230[88] = 0.0;
   out_5732313931484354230[89] = 0.0;
   out_5732313931484354230[90] = 0.0;
   out_5732313931484354230[91] = 0.0;
   out_5732313931484354230[92] = 0.0;
   out_5732313931484354230[93] = 0.0;
   out_5732313931484354230[94] = 0.0;
   out_5732313931484354230[95] = 1.0;
   out_5732313931484354230[96] = 0.0;
   out_5732313931484354230[97] = 0.0;
   out_5732313931484354230[98] = 0.0;
   out_5732313931484354230[99] = 0.0;
   out_5732313931484354230[100] = 0.0;
   out_5732313931484354230[101] = 0.0;
   out_5732313931484354230[102] = 0.0;
   out_5732313931484354230[103] = 0.0;
   out_5732313931484354230[104] = 0.0;
   out_5732313931484354230[105] = 0.0;
   out_5732313931484354230[106] = 0.0;
   out_5732313931484354230[107] = 0.0;
   out_5732313931484354230[108] = 0.0;
   out_5732313931484354230[109] = 0.0;
   out_5732313931484354230[110] = 0.0;
   out_5732313931484354230[111] = 0.0;
   out_5732313931484354230[112] = 0.0;
   out_5732313931484354230[113] = 0.0;
   out_5732313931484354230[114] = 1.0;
   out_5732313931484354230[115] = 0.0;
   out_5732313931484354230[116] = 0.0;
   out_5732313931484354230[117] = 0.0;
   out_5732313931484354230[118] = 0.0;
   out_5732313931484354230[119] = 0.0;
   out_5732313931484354230[120] = 0.0;
   out_5732313931484354230[121] = 0.0;
   out_5732313931484354230[122] = 0.0;
   out_5732313931484354230[123] = 0.0;
   out_5732313931484354230[124] = 0.0;
   out_5732313931484354230[125] = 0.0;
   out_5732313931484354230[126] = 0.0;
   out_5732313931484354230[127] = 0.0;
   out_5732313931484354230[128] = 0.0;
   out_5732313931484354230[129] = 0.0;
   out_5732313931484354230[130] = 0.0;
   out_5732313931484354230[131] = 0.0;
   out_5732313931484354230[132] = 0.0;
   out_5732313931484354230[133] = 1.0;
   out_5732313931484354230[134] = 0.0;
   out_5732313931484354230[135] = 0.0;
   out_5732313931484354230[136] = 0.0;
   out_5732313931484354230[137] = 0.0;
   out_5732313931484354230[138] = 0.0;
   out_5732313931484354230[139] = 0.0;
   out_5732313931484354230[140] = 0.0;
   out_5732313931484354230[141] = 0.0;
   out_5732313931484354230[142] = 0.0;
   out_5732313931484354230[143] = 0.0;
   out_5732313931484354230[144] = 0.0;
   out_5732313931484354230[145] = 0.0;
   out_5732313931484354230[146] = 0.0;
   out_5732313931484354230[147] = 0.0;
   out_5732313931484354230[148] = 0.0;
   out_5732313931484354230[149] = 0.0;
   out_5732313931484354230[150] = 0.0;
   out_5732313931484354230[151] = 0.0;
   out_5732313931484354230[152] = 1.0;
   out_5732313931484354230[153] = 0.0;
   out_5732313931484354230[154] = 0.0;
   out_5732313931484354230[155] = 0.0;
   out_5732313931484354230[156] = 0.0;
   out_5732313931484354230[157] = 0.0;
   out_5732313931484354230[158] = 0.0;
   out_5732313931484354230[159] = 0.0;
   out_5732313931484354230[160] = 0.0;
   out_5732313931484354230[161] = 0.0;
   out_5732313931484354230[162] = 0.0;
   out_5732313931484354230[163] = 0.0;
   out_5732313931484354230[164] = 0.0;
   out_5732313931484354230[165] = 0.0;
   out_5732313931484354230[166] = 0.0;
   out_5732313931484354230[167] = 0.0;
   out_5732313931484354230[168] = 0.0;
   out_5732313931484354230[169] = 0.0;
   out_5732313931484354230[170] = 0.0;
   out_5732313931484354230[171] = 1.0;
   out_5732313931484354230[172] = 0.0;
   out_5732313931484354230[173] = 0.0;
   out_5732313931484354230[174] = 0.0;
   out_5732313931484354230[175] = 0.0;
   out_5732313931484354230[176] = 0.0;
   out_5732313931484354230[177] = 0.0;
   out_5732313931484354230[178] = 0.0;
   out_5732313931484354230[179] = 0.0;
   out_5732313931484354230[180] = 0.0;
   out_5732313931484354230[181] = 0.0;
   out_5732313931484354230[182] = 0.0;
   out_5732313931484354230[183] = 0.0;
   out_5732313931484354230[184] = 0.0;
   out_5732313931484354230[185] = 0.0;
   out_5732313931484354230[186] = 0.0;
   out_5732313931484354230[187] = 0.0;
   out_5732313931484354230[188] = 0.0;
   out_5732313931484354230[189] = 0.0;
   out_5732313931484354230[190] = 1.0;
   out_5732313931484354230[191] = 0.0;
   out_5732313931484354230[192] = 0.0;
   out_5732313931484354230[193] = 0.0;
   out_5732313931484354230[194] = 0.0;
   out_5732313931484354230[195] = 0.0;
   out_5732313931484354230[196] = 0.0;
   out_5732313931484354230[197] = 0.0;
   out_5732313931484354230[198] = 0.0;
   out_5732313931484354230[199] = 0.0;
   out_5732313931484354230[200] = 0.0;
   out_5732313931484354230[201] = 0.0;
   out_5732313931484354230[202] = 0.0;
   out_5732313931484354230[203] = 0.0;
   out_5732313931484354230[204] = 0.0;
   out_5732313931484354230[205] = 0.0;
   out_5732313931484354230[206] = 0.0;
   out_5732313931484354230[207] = 0.0;
   out_5732313931484354230[208] = 0.0;
   out_5732313931484354230[209] = 1.0;
   out_5732313931484354230[210] = 0.0;
   out_5732313931484354230[211] = 0.0;
   out_5732313931484354230[212] = 0.0;
   out_5732313931484354230[213] = 0.0;
   out_5732313931484354230[214] = 0.0;
   out_5732313931484354230[215] = 0.0;
   out_5732313931484354230[216] = 0.0;
   out_5732313931484354230[217] = 0.0;
   out_5732313931484354230[218] = 0.0;
   out_5732313931484354230[219] = 0.0;
   out_5732313931484354230[220] = 0.0;
   out_5732313931484354230[221] = 0.0;
   out_5732313931484354230[222] = 0.0;
   out_5732313931484354230[223] = 0.0;
   out_5732313931484354230[224] = 0.0;
   out_5732313931484354230[225] = 0.0;
   out_5732313931484354230[226] = 0.0;
   out_5732313931484354230[227] = 0.0;
   out_5732313931484354230[228] = 1.0;
   out_5732313931484354230[229] = 0.0;
   out_5732313931484354230[230] = 0.0;
   out_5732313931484354230[231] = 0.0;
   out_5732313931484354230[232] = 0.0;
   out_5732313931484354230[233] = 0.0;
   out_5732313931484354230[234] = 0.0;
   out_5732313931484354230[235] = 0.0;
   out_5732313931484354230[236] = 0.0;
   out_5732313931484354230[237] = 0.0;
   out_5732313931484354230[238] = 0.0;
   out_5732313931484354230[239] = 0.0;
   out_5732313931484354230[240] = 0.0;
   out_5732313931484354230[241] = 0.0;
   out_5732313931484354230[242] = 0.0;
   out_5732313931484354230[243] = 0.0;
   out_5732313931484354230[244] = 0.0;
   out_5732313931484354230[245] = 0.0;
   out_5732313931484354230[246] = 0.0;
   out_5732313931484354230[247] = 1.0;
   out_5732313931484354230[248] = 0.0;
   out_5732313931484354230[249] = 0.0;
   out_5732313931484354230[250] = 0.0;
   out_5732313931484354230[251] = 0.0;
   out_5732313931484354230[252] = 0.0;
   out_5732313931484354230[253] = 0.0;
   out_5732313931484354230[254] = 0.0;
   out_5732313931484354230[255] = 0.0;
   out_5732313931484354230[256] = 0.0;
   out_5732313931484354230[257] = 0.0;
   out_5732313931484354230[258] = 0.0;
   out_5732313931484354230[259] = 0.0;
   out_5732313931484354230[260] = 0.0;
   out_5732313931484354230[261] = 0.0;
   out_5732313931484354230[262] = 0.0;
   out_5732313931484354230[263] = 0.0;
   out_5732313931484354230[264] = 0.0;
   out_5732313931484354230[265] = 0.0;
   out_5732313931484354230[266] = 1.0;
   out_5732313931484354230[267] = 0.0;
   out_5732313931484354230[268] = 0.0;
   out_5732313931484354230[269] = 0.0;
   out_5732313931484354230[270] = 0.0;
   out_5732313931484354230[271] = 0.0;
   out_5732313931484354230[272] = 0.0;
   out_5732313931484354230[273] = 0.0;
   out_5732313931484354230[274] = 0.0;
   out_5732313931484354230[275] = 0.0;
   out_5732313931484354230[276] = 0.0;
   out_5732313931484354230[277] = 0.0;
   out_5732313931484354230[278] = 0.0;
   out_5732313931484354230[279] = 0.0;
   out_5732313931484354230[280] = 0.0;
   out_5732313931484354230[281] = 0.0;
   out_5732313931484354230[282] = 0.0;
   out_5732313931484354230[283] = 0.0;
   out_5732313931484354230[284] = 0.0;
   out_5732313931484354230[285] = 1.0;
   out_5732313931484354230[286] = 0.0;
   out_5732313931484354230[287] = 0.0;
   out_5732313931484354230[288] = 0.0;
   out_5732313931484354230[289] = 0.0;
   out_5732313931484354230[290] = 0.0;
   out_5732313931484354230[291] = 0.0;
   out_5732313931484354230[292] = 0.0;
   out_5732313931484354230[293] = 0.0;
   out_5732313931484354230[294] = 0.0;
   out_5732313931484354230[295] = 0.0;
   out_5732313931484354230[296] = 0.0;
   out_5732313931484354230[297] = 0.0;
   out_5732313931484354230[298] = 0.0;
   out_5732313931484354230[299] = 0.0;
   out_5732313931484354230[300] = 0.0;
   out_5732313931484354230[301] = 0.0;
   out_5732313931484354230[302] = 0.0;
   out_5732313931484354230[303] = 0.0;
   out_5732313931484354230[304] = 1.0;
   out_5732313931484354230[305] = 0.0;
   out_5732313931484354230[306] = 0.0;
   out_5732313931484354230[307] = 0.0;
   out_5732313931484354230[308] = 0.0;
   out_5732313931484354230[309] = 0.0;
   out_5732313931484354230[310] = 0.0;
   out_5732313931484354230[311] = 0.0;
   out_5732313931484354230[312] = 0.0;
   out_5732313931484354230[313] = 0.0;
   out_5732313931484354230[314] = 0.0;
   out_5732313931484354230[315] = 0.0;
   out_5732313931484354230[316] = 0.0;
   out_5732313931484354230[317] = 0.0;
   out_5732313931484354230[318] = 0.0;
   out_5732313931484354230[319] = 0.0;
   out_5732313931484354230[320] = 0.0;
   out_5732313931484354230[321] = 0.0;
   out_5732313931484354230[322] = 0.0;
   out_5732313931484354230[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8124696220925940808) {
   out_8124696220925940808[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8124696220925940808[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8124696220925940808[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8124696220925940808[3] = dt*state[12] + state[3];
   out_8124696220925940808[4] = dt*state[13] + state[4];
   out_8124696220925940808[5] = dt*state[14] + state[5];
   out_8124696220925940808[6] = state[6];
   out_8124696220925940808[7] = state[7];
   out_8124696220925940808[8] = state[8];
   out_8124696220925940808[9] = state[9];
   out_8124696220925940808[10] = state[10];
   out_8124696220925940808[11] = state[11];
   out_8124696220925940808[12] = state[12];
   out_8124696220925940808[13] = state[13];
   out_8124696220925940808[14] = state[14];
   out_8124696220925940808[15] = state[15];
   out_8124696220925940808[16] = state[16];
   out_8124696220925940808[17] = state[17];
}
void F_fun(double *state, double dt, double *out_282840327706957589) {
   out_282840327706957589[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_282840327706957589[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_282840327706957589[2] = 0;
   out_282840327706957589[3] = 0;
   out_282840327706957589[4] = 0;
   out_282840327706957589[5] = 0;
   out_282840327706957589[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_282840327706957589[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_282840327706957589[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_282840327706957589[9] = 0;
   out_282840327706957589[10] = 0;
   out_282840327706957589[11] = 0;
   out_282840327706957589[12] = 0;
   out_282840327706957589[13] = 0;
   out_282840327706957589[14] = 0;
   out_282840327706957589[15] = 0;
   out_282840327706957589[16] = 0;
   out_282840327706957589[17] = 0;
   out_282840327706957589[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_282840327706957589[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_282840327706957589[20] = 0;
   out_282840327706957589[21] = 0;
   out_282840327706957589[22] = 0;
   out_282840327706957589[23] = 0;
   out_282840327706957589[24] = 0;
   out_282840327706957589[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_282840327706957589[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_282840327706957589[27] = 0;
   out_282840327706957589[28] = 0;
   out_282840327706957589[29] = 0;
   out_282840327706957589[30] = 0;
   out_282840327706957589[31] = 0;
   out_282840327706957589[32] = 0;
   out_282840327706957589[33] = 0;
   out_282840327706957589[34] = 0;
   out_282840327706957589[35] = 0;
   out_282840327706957589[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_282840327706957589[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_282840327706957589[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_282840327706957589[39] = 0;
   out_282840327706957589[40] = 0;
   out_282840327706957589[41] = 0;
   out_282840327706957589[42] = 0;
   out_282840327706957589[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_282840327706957589[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_282840327706957589[45] = 0;
   out_282840327706957589[46] = 0;
   out_282840327706957589[47] = 0;
   out_282840327706957589[48] = 0;
   out_282840327706957589[49] = 0;
   out_282840327706957589[50] = 0;
   out_282840327706957589[51] = 0;
   out_282840327706957589[52] = 0;
   out_282840327706957589[53] = 0;
   out_282840327706957589[54] = 0;
   out_282840327706957589[55] = 0;
   out_282840327706957589[56] = 0;
   out_282840327706957589[57] = 1;
   out_282840327706957589[58] = 0;
   out_282840327706957589[59] = 0;
   out_282840327706957589[60] = 0;
   out_282840327706957589[61] = 0;
   out_282840327706957589[62] = 0;
   out_282840327706957589[63] = 0;
   out_282840327706957589[64] = 0;
   out_282840327706957589[65] = 0;
   out_282840327706957589[66] = dt;
   out_282840327706957589[67] = 0;
   out_282840327706957589[68] = 0;
   out_282840327706957589[69] = 0;
   out_282840327706957589[70] = 0;
   out_282840327706957589[71] = 0;
   out_282840327706957589[72] = 0;
   out_282840327706957589[73] = 0;
   out_282840327706957589[74] = 0;
   out_282840327706957589[75] = 0;
   out_282840327706957589[76] = 1;
   out_282840327706957589[77] = 0;
   out_282840327706957589[78] = 0;
   out_282840327706957589[79] = 0;
   out_282840327706957589[80] = 0;
   out_282840327706957589[81] = 0;
   out_282840327706957589[82] = 0;
   out_282840327706957589[83] = 0;
   out_282840327706957589[84] = 0;
   out_282840327706957589[85] = dt;
   out_282840327706957589[86] = 0;
   out_282840327706957589[87] = 0;
   out_282840327706957589[88] = 0;
   out_282840327706957589[89] = 0;
   out_282840327706957589[90] = 0;
   out_282840327706957589[91] = 0;
   out_282840327706957589[92] = 0;
   out_282840327706957589[93] = 0;
   out_282840327706957589[94] = 0;
   out_282840327706957589[95] = 1;
   out_282840327706957589[96] = 0;
   out_282840327706957589[97] = 0;
   out_282840327706957589[98] = 0;
   out_282840327706957589[99] = 0;
   out_282840327706957589[100] = 0;
   out_282840327706957589[101] = 0;
   out_282840327706957589[102] = 0;
   out_282840327706957589[103] = 0;
   out_282840327706957589[104] = dt;
   out_282840327706957589[105] = 0;
   out_282840327706957589[106] = 0;
   out_282840327706957589[107] = 0;
   out_282840327706957589[108] = 0;
   out_282840327706957589[109] = 0;
   out_282840327706957589[110] = 0;
   out_282840327706957589[111] = 0;
   out_282840327706957589[112] = 0;
   out_282840327706957589[113] = 0;
   out_282840327706957589[114] = 1;
   out_282840327706957589[115] = 0;
   out_282840327706957589[116] = 0;
   out_282840327706957589[117] = 0;
   out_282840327706957589[118] = 0;
   out_282840327706957589[119] = 0;
   out_282840327706957589[120] = 0;
   out_282840327706957589[121] = 0;
   out_282840327706957589[122] = 0;
   out_282840327706957589[123] = 0;
   out_282840327706957589[124] = 0;
   out_282840327706957589[125] = 0;
   out_282840327706957589[126] = 0;
   out_282840327706957589[127] = 0;
   out_282840327706957589[128] = 0;
   out_282840327706957589[129] = 0;
   out_282840327706957589[130] = 0;
   out_282840327706957589[131] = 0;
   out_282840327706957589[132] = 0;
   out_282840327706957589[133] = 1;
   out_282840327706957589[134] = 0;
   out_282840327706957589[135] = 0;
   out_282840327706957589[136] = 0;
   out_282840327706957589[137] = 0;
   out_282840327706957589[138] = 0;
   out_282840327706957589[139] = 0;
   out_282840327706957589[140] = 0;
   out_282840327706957589[141] = 0;
   out_282840327706957589[142] = 0;
   out_282840327706957589[143] = 0;
   out_282840327706957589[144] = 0;
   out_282840327706957589[145] = 0;
   out_282840327706957589[146] = 0;
   out_282840327706957589[147] = 0;
   out_282840327706957589[148] = 0;
   out_282840327706957589[149] = 0;
   out_282840327706957589[150] = 0;
   out_282840327706957589[151] = 0;
   out_282840327706957589[152] = 1;
   out_282840327706957589[153] = 0;
   out_282840327706957589[154] = 0;
   out_282840327706957589[155] = 0;
   out_282840327706957589[156] = 0;
   out_282840327706957589[157] = 0;
   out_282840327706957589[158] = 0;
   out_282840327706957589[159] = 0;
   out_282840327706957589[160] = 0;
   out_282840327706957589[161] = 0;
   out_282840327706957589[162] = 0;
   out_282840327706957589[163] = 0;
   out_282840327706957589[164] = 0;
   out_282840327706957589[165] = 0;
   out_282840327706957589[166] = 0;
   out_282840327706957589[167] = 0;
   out_282840327706957589[168] = 0;
   out_282840327706957589[169] = 0;
   out_282840327706957589[170] = 0;
   out_282840327706957589[171] = 1;
   out_282840327706957589[172] = 0;
   out_282840327706957589[173] = 0;
   out_282840327706957589[174] = 0;
   out_282840327706957589[175] = 0;
   out_282840327706957589[176] = 0;
   out_282840327706957589[177] = 0;
   out_282840327706957589[178] = 0;
   out_282840327706957589[179] = 0;
   out_282840327706957589[180] = 0;
   out_282840327706957589[181] = 0;
   out_282840327706957589[182] = 0;
   out_282840327706957589[183] = 0;
   out_282840327706957589[184] = 0;
   out_282840327706957589[185] = 0;
   out_282840327706957589[186] = 0;
   out_282840327706957589[187] = 0;
   out_282840327706957589[188] = 0;
   out_282840327706957589[189] = 0;
   out_282840327706957589[190] = 1;
   out_282840327706957589[191] = 0;
   out_282840327706957589[192] = 0;
   out_282840327706957589[193] = 0;
   out_282840327706957589[194] = 0;
   out_282840327706957589[195] = 0;
   out_282840327706957589[196] = 0;
   out_282840327706957589[197] = 0;
   out_282840327706957589[198] = 0;
   out_282840327706957589[199] = 0;
   out_282840327706957589[200] = 0;
   out_282840327706957589[201] = 0;
   out_282840327706957589[202] = 0;
   out_282840327706957589[203] = 0;
   out_282840327706957589[204] = 0;
   out_282840327706957589[205] = 0;
   out_282840327706957589[206] = 0;
   out_282840327706957589[207] = 0;
   out_282840327706957589[208] = 0;
   out_282840327706957589[209] = 1;
   out_282840327706957589[210] = 0;
   out_282840327706957589[211] = 0;
   out_282840327706957589[212] = 0;
   out_282840327706957589[213] = 0;
   out_282840327706957589[214] = 0;
   out_282840327706957589[215] = 0;
   out_282840327706957589[216] = 0;
   out_282840327706957589[217] = 0;
   out_282840327706957589[218] = 0;
   out_282840327706957589[219] = 0;
   out_282840327706957589[220] = 0;
   out_282840327706957589[221] = 0;
   out_282840327706957589[222] = 0;
   out_282840327706957589[223] = 0;
   out_282840327706957589[224] = 0;
   out_282840327706957589[225] = 0;
   out_282840327706957589[226] = 0;
   out_282840327706957589[227] = 0;
   out_282840327706957589[228] = 1;
   out_282840327706957589[229] = 0;
   out_282840327706957589[230] = 0;
   out_282840327706957589[231] = 0;
   out_282840327706957589[232] = 0;
   out_282840327706957589[233] = 0;
   out_282840327706957589[234] = 0;
   out_282840327706957589[235] = 0;
   out_282840327706957589[236] = 0;
   out_282840327706957589[237] = 0;
   out_282840327706957589[238] = 0;
   out_282840327706957589[239] = 0;
   out_282840327706957589[240] = 0;
   out_282840327706957589[241] = 0;
   out_282840327706957589[242] = 0;
   out_282840327706957589[243] = 0;
   out_282840327706957589[244] = 0;
   out_282840327706957589[245] = 0;
   out_282840327706957589[246] = 0;
   out_282840327706957589[247] = 1;
   out_282840327706957589[248] = 0;
   out_282840327706957589[249] = 0;
   out_282840327706957589[250] = 0;
   out_282840327706957589[251] = 0;
   out_282840327706957589[252] = 0;
   out_282840327706957589[253] = 0;
   out_282840327706957589[254] = 0;
   out_282840327706957589[255] = 0;
   out_282840327706957589[256] = 0;
   out_282840327706957589[257] = 0;
   out_282840327706957589[258] = 0;
   out_282840327706957589[259] = 0;
   out_282840327706957589[260] = 0;
   out_282840327706957589[261] = 0;
   out_282840327706957589[262] = 0;
   out_282840327706957589[263] = 0;
   out_282840327706957589[264] = 0;
   out_282840327706957589[265] = 0;
   out_282840327706957589[266] = 1;
   out_282840327706957589[267] = 0;
   out_282840327706957589[268] = 0;
   out_282840327706957589[269] = 0;
   out_282840327706957589[270] = 0;
   out_282840327706957589[271] = 0;
   out_282840327706957589[272] = 0;
   out_282840327706957589[273] = 0;
   out_282840327706957589[274] = 0;
   out_282840327706957589[275] = 0;
   out_282840327706957589[276] = 0;
   out_282840327706957589[277] = 0;
   out_282840327706957589[278] = 0;
   out_282840327706957589[279] = 0;
   out_282840327706957589[280] = 0;
   out_282840327706957589[281] = 0;
   out_282840327706957589[282] = 0;
   out_282840327706957589[283] = 0;
   out_282840327706957589[284] = 0;
   out_282840327706957589[285] = 1;
   out_282840327706957589[286] = 0;
   out_282840327706957589[287] = 0;
   out_282840327706957589[288] = 0;
   out_282840327706957589[289] = 0;
   out_282840327706957589[290] = 0;
   out_282840327706957589[291] = 0;
   out_282840327706957589[292] = 0;
   out_282840327706957589[293] = 0;
   out_282840327706957589[294] = 0;
   out_282840327706957589[295] = 0;
   out_282840327706957589[296] = 0;
   out_282840327706957589[297] = 0;
   out_282840327706957589[298] = 0;
   out_282840327706957589[299] = 0;
   out_282840327706957589[300] = 0;
   out_282840327706957589[301] = 0;
   out_282840327706957589[302] = 0;
   out_282840327706957589[303] = 0;
   out_282840327706957589[304] = 1;
   out_282840327706957589[305] = 0;
   out_282840327706957589[306] = 0;
   out_282840327706957589[307] = 0;
   out_282840327706957589[308] = 0;
   out_282840327706957589[309] = 0;
   out_282840327706957589[310] = 0;
   out_282840327706957589[311] = 0;
   out_282840327706957589[312] = 0;
   out_282840327706957589[313] = 0;
   out_282840327706957589[314] = 0;
   out_282840327706957589[315] = 0;
   out_282840327706957589[316] = 0;
   out_282840327706957589[317] = 0;
   out_282840327706957589[318] = 0;
   out_282840327706957589[319] = 0;
   out_282840327706957589[320] = 0;
   out_282840327706957589[321] = 0;
   out_282840327706957589[322] = 0;
   out_282840327706957589[323] = 1;
}
void h_4(double *state, double *unused, double *out_5925821027563078418) {
   out_5925821027563078418[0] = state[6] + state[9];
   out_5925821027563078418[1] = state[7] + state[10];
   out_5925821027563078418[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6930261413367252334) {
   out_6930261413367252334[0] = 0;
   out_6930261413367252334[1] = 0;
   out_6930261413367252334[2] = 0;
   out_6930261413367252334[3] = 0;
   out_6930261413367252334[4] = 0;
   out_6930261413367252334[5] = 0;
   out_6930261413367252334[6] = 1;
   out_6930261413367252334[7] = 0;
   out_6930261413367252334[8] = 0;
   out_6930261413367252334[9] = 1;
   out_6930261413367252334[10] = 0;
   out_6930261413367252334[11] = 0;
   out_6930261413367252334[12] = 0;
   out_6930261413367252334[13] = 0;
   out_6930261413367252334[14] = 0;
   out_6930261413367252334[15] = 0;
   out_6930261413367252334[16] = 0;
   out_6930261413367252334[17] = 0;
   out_6930261413367252334[18] = 0;
   out_6930261413367252334[19] = 0;
   out_6930261413367252334[20] = 0;
   out_6930261413367252334[21] = 0;
   out_6930261413367252334[22] = 0;
   out_6930261413367252334[23] = 0;
   out_6930261413367252334[24] = 0;
   out_6930261413367252334[25] = 1;
   out_6930261413367252334[26] = 0;
   out_6930261413367252334[27] = 0;
   out_6930261413367252334[28] = 1;
   out_6930261413367252334[29] = 0;
   out_6930261413367252334[30] = 0;
   out_6930261413367252334[31] = 0;
   out_6930261413367252334[32] = 0;
   out_6930261413367252334[33] = 0;
   out_6930261413367252334[34] = 0;
   out_6930261413367252334[35] = 0;
   out_6930261413367252334[36] = 0;
   out_6930261413367252334[37] = 0;
   out_6930261413367252334[38] = 0;
   out_6930261413367252334[39] = 0;
   out_6930261413367252334[40] = 0;
   out_6930261413367252334[41] = 0;
   out_6930261413367252334[42] = 0;
   out_6930261413367252334[43] = 0;
   out_6930261413367252334[44] = 1;
   out_6930261413367252334[45] = 0;
   out_6930261413367252334[46] = 0;
   out_6930261413367252334[47] = 1;
   out_6930261413367252334[48] = 0;
   out_6930261413367252334[49] = 0;
   out_6930261413367252334[50] = 0;
   out_6930261413367252334[51] = 0;
   out_6930261413367252334[52] = 0;
   out_6930261413367252334[53] = 0;
}
void h_10(double *state, double *unused, double *out_7088557639870104909) {
   out_7088557639870104909[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7088557639870104909[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7088557639870104909[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8659962992607815749) {
   out_8659962992607815749[0] = 0;
   out_8659962992607815749[1] = 9.8100000000000005*cos(state[1]);
   out_8659962992607815749[2] = 0;
   out_8659962992607815749[3] = 0;
   out_8659962992607815749[4] = -state[8];
   out_8659962992607815749[5] = state[7];
   out_8659962992607815749[6] = 0;
   out_8659962992607815749[7] = state[5];
   out_8659962992607815749[8] = -state[4];
   out_8659962992607815749[9] = 0;
   out_8659962992607815749[10] = 0;
   out_8659962992607815749[11] = 0;
   out_8659962992607815749[12] = 1;
   out_8659962992607815749[13] = 0;
   out_8659962992607815749[14] = 0;
   out_8659962992607815749[15] = 1;
   out_8659962992607815749[16] = 0;
   out_8659962992607815749[17] = 0;
   out_8659962992607815749[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8659962992607815749[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8659962992607815749[20] = 0;
   out_8659962992607815749[21] = state[8];
   out_8659962992607815749[22] = 0;
   out_8659962992607815749[23] = -state[6];
   out_8659962992607815749[24] = -state[5];
   out_8659962992607815749[25] = 0;
   out_8659962992607815749[26] = state[3];
   out_8659962992607815749[27] = 0;
   out_8659962992607815749[28] = 0;
   out_8659962992607815749[29] = 0;
   out_8659962992607815749[30] = 0;
   out_8659962992607815749[31] = 1;
   out_8659962992607815749[32] = 0;
   out_8659962992607815749[33] = 0;
   out_8659962992607815749[34] = 1;
   out_8659962992607815749[35] = 0;
   out_8659962992607815749[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8659962992607815749[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8659962992607815749[38] = 0;
   out_8659962992607815749[39] = -state[7];
   out_8659962992607815749[40] = state[6];
   out_8659962992607815749[41] = 0;
   out_8659962992607815749[42] = state[4];
   out_8659962992607815749[43] = -state[3];
   out_8659962992607815749[44] = 0;
   out_8659962992607815749[45] = 0;
   out_8659962992607815749[46] = 0;
   out_8659962992607815749[47] = 0;
   out_8659962992607815749[48] = 0;
   out_8659962992607815749[49] = 0;
   out_8659962992607815749[50] = 1;
   out_8659962992607815749[51] = 0;
   out_8659962992607815749[52] = 0;
   out_8659962992607815749[53] = 1;
}
void h_13(double *state, double *unused, double *out_5685915155655708417) {
   out_5685915155655708417[0] = state[3];
   out_5685915155655708417[1] = state[4];
   out_5685915155655708417[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8304208835009966481) {
   out_8304208835009966481[0] = 0;
   out_8304208835009966481[1] = 0;
   out_8304208835009966481[2] = 0;
   out_8304208835009966481[3] = 1;
   out_8304208835009966481[4] = 0;
   out_8304208835009966481[5] = 0;
   out_8304208835009966481[6] = 0;
   out_8304208835009966481[7] = 0;
   out_8304208835009966481[8] = 0;
   out_8304208835009966481[9] = 0;
   out_8304208835009966481[10] = 0;
   out_8304208835009966481[11] = 0;
   out_8304208835009966481[12] = 0;
   out_8304208835009966481[13] = 0;
   out_8304208835009966481[14] = 0;
   out_8304208835009966481[15] = 0;
   out_8304208835009966481[16] = 0;
   out_8304208835009966481[17] = 0;
   out_8304208835009966481[18] = 0;
   out_8304208835009966481[19] = 0;
   out_8304208835009966481[20] = 0;
   out_8304208835009966481[21] = 0;
   out_8304208835009966481[22] = 1;
   out_8304208835009966481[23] = 0;
   out_8304208835009966481[24] = 0;
   out_8304208835009966481[25] = 0;
   out_8304208835009966481[26] = 0;
   out_8304208835009966481[27] = 0;
   out_8304208835009966481[28] = 0;
   out_8304208835009966481[29] = 0;
   out_8304208835009966481[30] = 0;
   out_8304208835009966481[31] = 0;
   out_8304208835009966481[32] = 0;
   out_8304208835009966481[33] = 0;
   out_8304208835009966481[34] = 0;
   out_8304208835009966481[35] = 0;
   out_8304208835009966481[36] = 0;
   out_8304208835009966481[37] = 0;
   out_8304208835009966481[38] = 0;
   out_8304208835009966481[39] = 0;
   out_8304208835009966481[40] = 0;
   out_8304208835009966481[41] = 1;
   out_8304208835009966481[42] = 0;
   out_8304208835009966481[43] = 0;
   out_8304208835009966481[44] = 0;
   out_8304208835009966481[45] = 0;
   out_8304208835009966481[46] = 0;
   out_8304208835009966481[47] = 0;
   out_8304208835009966481[48] = 0;
   out_8304208835009966481[49] = 0;
   out_8304208835009966481[50] = 0;
   out_8304208835009966481[51] = 0;
   out_8304208835009966481[52] = 0;
   out_8304208835009966481[53] = 0;
}
void h_14(double *state, double *unused, double *out_211775679460280009) {
   out_211775679460280009[0] = state[6];
   out_211775679460280009[1] = state[7];
   out_211775679460280009[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3847472981071880038) {
   out_3847472981071880038[0] = 0;
   out_3847472981071880038[1] = 0;
   out_3847472981071880038[2] = 0;
   out_3847472981071880038[3] = 0;
   out_3847472981071880038[4] = 0;
   out_3847472981071880038[5] = 0;
   out_3847472981071880038[6] = 1;
   out_3847472981071880038[7] = 0;
   out_3847472981071880038[8] = 0;
   out_3847472981071880038[9] = 0;
   out_3847472981071880038[10] = 0;
   out_3847472981071880038[11] = 0;
   out_3847472981071880038[12] = 0;
   out_3847472981071880038[13] = 0;
   out_3847472981071880038[14] = 0;
   out_3847472981071880038[15] = 0;
   out_3847472981071880038[16] = 0;
   out_3847472981071880038[17] = 0;
   out_3847472981071880038[18] = 0;
   out_3847472981071880038[19] = 0;
   out_3847472981071880038[20] = 0;
   out_3847472981071880038[21] = 0;
   out_3847472981071880038[22] = 0;
   out_3847472981071880038[23] = 0;
   out_3847472981071880038[24] = 0;
   out_3847472981071880038[25] = 1;
   out_3847472981071880038[26] = 0;
   out_3847472981071880038[27] = 0;
   out_3847472981071880038[28] = 0;
   out_3847472981071880038[29] = 0;
   out_3847472981071880038[30] = 0;
   out_3847472981071880038[31] = 0;
   out_3847472981071880038[32] = 0;
   out_3847472981071880038[33] = 0;
   out_3847472981071880038[34] = 0;
   out_3847472981071880038[35] = 0;
   out_3847472981071880038[36] = 0;
   out_3847472981071880038[37] = 0;
   out_3847472981071880038[38] = 0;
   out_3847472981071880038[39] = 0;
   out_3847472981071880038[40] = 0;
   out_3847472981071880038[41] = 0;
   out_3847472981071880038[42] = 0;
   out_3847472981071880038[43] = 0;
   out_3847472981071880038[44] = 1;
   out_3847472981071880038[45] = 0;
   out_3847472981071880038[46] = 0;
   out_3847472981071880038[47] = 0;
   out_3847472981071880038[48] = 0;
   out_3847472981071880038[49] = 0;
   out_3847472981071880038[50] = 0;
   out_3847472981071880038[51] = 0;
   out_3847472981071880038[52] = 0;
   out_3847472981071880038[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2182538694400222550) {
  err_fun(nom_x, delta_x, out_2182538694400222550);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3636770726618230824) {
  inv_err_fun(nom_x, true_x, out_3636770726618230824);
}
void pose_H_mod_fun(double *state, double *out_5732313931484354230) {
  H_mod_fun(state, out_5732313931484354230);
}
void pose_f_fun(double *state, double dt, double *out_8124696220925940808) {
  f_fun(state,  dt, out_8124696220925940808);
}
void pose_F_fun(double *state, double dt, double *out_282840327706957589) {
  F_fun(state,  dt, out_282840327706957589);
}
void pose_h_4(double *state, double *unused, double *out_5925821027563078418) {
  h_4(state, unused, out_5925821027563078418);
}
void pose_H_4(double *state, double *unused, double *out_6930261413367252334) {
  H_4(state, unused, out_6930261413367252334);
}
void pose_h_10(double *state, double *unused, double *out_7088557639870104909) {
  h_10(state, unused, out_7088557639870104909);
}
void pose_H_10(double *state, double *unused, double *out_8659962992607815749) {
  H_10(state, unused, out_8659962992607815749);
}
void pose_h_13(double *state, double *unused, double *out_5685915155655708417) {
  h_13(state, unused, out_5685915155655708417);
}
void pose_H_13(double *state, double *unused, double *out_8304208835009966481) {
  H_13(state, unused, out_8304208835009966481);
}
void pose_h_14(double *state, double *unused, double *out_211775679460280009) {
  h_14(state, unused, out_211775679460280009);
}
void pose_H_14(double *state, double *unused, double *out_3847472981071880038) {
  H_14(state, unused, out_3847472981071880038);
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
