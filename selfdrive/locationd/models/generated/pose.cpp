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
void err_fun(double *nom_x, double *delta_x, double *out_3965258856132538103) {
   out_3965258856132538103[0] = delta_x[0] + nom_x[0];
   out_3965258856132538103[1] = delta_x[1] + nom_x[1];
   out_3965258856132538103[2] = delta_x[2] + nom_x[2];
   out_3965258856132538103[3] = delta_x[3] + nom_x[3];
   out_3965258856132538103[4] = delta_x[4] + nom_x[4];
   out_3965258856132538103[5] = delta_x[5] + nom_x[5];
   out_3965258856132538103[6] = delta_x[6] + nom_x[6];
   out_3965258856132538103[7] = delta_x[7] + nom_x[7];
   out_3965258856132538103[8] = delta_x[8] + nom_x[8];
   out_3965258856132538103[9] = delta_x[9] + nom_x[9];
   out_3965258856132538103[10] = delta_x[10] + nom_x[10];
   out_3965258856132538103[11] = delta_x[11] + nom_x[11];
   out_3965258856132538103[12] = delta_x[12] + nom_x[12];
   out_3965258856132538103[13] = delta_x[13] + nom_x[13];
   out_3965258856132538103[14] = delta_x[14] + nom_x[14];
   out_3965258856132538103[15] = delta_x[15] + nom_x[15];
   out_3965258856132538103[16] = delta_x[16] + nom_x[16];
   out_3965258856132538103[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5412015007655879645) {
   out_5412015007655879645[0] = -nom_x[0] + true_x[0];
   out_5412015007655879645[1] = -nom_x[1] + true_x[1];
   out_5412015007655879645[2] = -nom_x[2] + true_x[2];
   out_5412015007655879645[3] = -nom_x[3] + true_x[3];
   out_5412015007655879645[4] = -nom_x[4] + true_x[4];
   out_5412015007655879645[5] = -nom_x[5] + true_x[5];
   out_5412015007655879645[6] = -nom_x[6] + true_x[6];
   out_5412015007655879645[7] = -nom_x[7] + true_x[7];
   out_5412015007655879645[8] = -nom_x[8] + true_x[8];
   out_5412015007655879645[9] = -nom_x[9] + true_x[9];
   out_5412015007655879645[10] = -nom_x[10] + true_x[10];
   out_5412015007655879645[11] = -nom_x[11] + true_x[11];
   out_5412015007655879645[12] = -nom_x[12] + true_x[12];
   out_5412015007655879645[13] = -nom_x[13] + true_x[13];
   out_5412015007655879645[14] = -nom_x[14] + true_x[14];
   out_5412015007655879645[15] = -nom_x[15] + true_x[15];
   out_5412015007655879645[16] = -nom_x[16] + true_x[16];
   out_5412015007655879645[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4522806033046979489) {
   out_4522806033046979489[0] = 1.0;
   out_4522806033046979489[1] = 0.0;
   out_4522806033046979489[2] = 0.0;
   out_4522806033046979489[3] = 0.0;
   out_4522806033046979489[4] = 0.0;
   out_4522806033046979489[5] = 0.0;
   out_4522806033046979489[6] = 0.0;
   out_4522806033046979489[7] = 0.0;
   out_4522806033046979489[8] = 0.0;
   out_4522806033046979489[9] = 0.0;
   out_4522806033046979489[10] = 0.0;
   out_4522806033046979489[11] = 0.0;
   out_4522806033046979489[12] = 0.0;
   out_4522806033046979489[13] = 0.0;
   out_4522806033046979489[14] = 0.0;
   out_4522806033046979489[15] = 0.0;
   out_4522806033046979489[16] = 0.0;
   out_4522806033046979489[17] = 0.0;
   out_4522806033046979489[18] = 0.0;
   out_4522806033046979489[19] = 1.0;
   out_4522806033046979489[20] = 0.0;
   out_4522806033046979489[21] = 0.0;
   out_4522806033046979489[22] = 0.0;
   out_4522806033046979489[23] = 0.0;
   out_4522806033046979489[24] = 0.0;
   out_4522806033046979489[25] = 0.0;
   out_4522806033046979489[26] = 0.0;
   out_4522806033046979489[27] = 0.0;
   out_4522806033046979489[28] = 0.0;
   out_4522806033046979489[29] = 0.0;
   out_4522806033046979489[30] = 0.0;
   out_4522806033046979489[31] = 0.0;
   out_4522806033046979489[32] = 0.0;
   out_4522806033046979489[33] = 0.0;
   out_4522806033046979489[34] = 0.0;
   out_4522806033046979489[35] = 0.0;
   out_4522806033046979489[36] = 0.0;
   out_4522806033046979489[37] = 0.0;
   out_4522806033046979489[38] = 1.0;
   out_4522806033046979489[39] = 0.0;
   out_4522806033046979489[40] = 0.0;
   out_4522806033046979489[41] = 0.0;
   out_4522806033046979489[42] = 0.0;
   out_4522806033046979489[43] = 0.0;
   out_4522806033046979489[44] = 0.0;
   out_4522806033046979489[45] = 0.0;
   out_4522806033046979489[46] = 0.0;
   out_4522806033046979489[47] = 0.0;
   out_4522806033046979489[48] = 0.0;
   out_4522806033046979489[49] = 0.0;
   out_4522806033046979489[50] = 0.0;
   out_4522806033046979489[51] = 0.0;
   out_4522806033046979489[52] = 0.0;
   out_4522806033046979489[53] = 0.0;
   out_4522806033046979489[54] = 0.0;
   out_4522806033046979489[55] = 0.0;
   out_4522806033046979489[56] = 0.0;
   out_4522806033046979489[57] = 1.0;
   out_4522806033046979489[58] = 0.0;
   out_4522806033046979489[59] = 0.0;
   out_4522806033046979489[60] = 0.0;
   out_4522806033046979489[61] = 0.0;
   out_4522806033046979489[62] = 0.0;
   out_4522806033046979489[63] = 0.0;
   out_4522806033046979489[64] = 0.0;
   out_4522806033046979489[65] = 0.0;
   out_4522806033046979489[66] = 0.0;
   out_4522806033046979489[67] = 0.0;
   out_4522806033046979489[68] = 0.0;
   out_4522806033046979489[69] = 0.0;
   out_4522806033046979489[70] = 0.0;
   out_4522806033046979489[71] = 0.0;
   out_4522806033046979489[72] = 0.0;
   out_4522806033046979489[73] = 0.0;
   out_4522806033046979489[74] = 0.0;
   out_4522806033046979489[75] = 0.0;
   out_4522806033046979489[76] = 1.0;
   out_4522806033046979489[77] = 0.0;
   out_4522806033046979489[78] = 0.0;
   out_4522806033046979489[79] = 0.0;
   out_4522806033046979489[80] = 0.0;
   out_4522806033046979489[81] = 0.0;
   out_4522806033046979489[82] = 0.0;
   out_4522806033046979489[83] = 0.0;
   out_4522806033046979489[84] = 0.0;
   out_4522806033046979489[85] = 0.0;
   out_4522806033046979489[86] = 0.0;
   out_4522806033046979489[87] = 0.0;
   out_4522806033046979489[88] = 0.0;
   out_4522806033046979489[89] = 0.0;
   out_4522806033046979489[90] = 0.0;
   out_4522806033046979489[91] = 0.0;
   out_4522806033046979489[92] = 0.0;
   out_4522806033046979489[93] = 0.0;
   out_4522806033046979489[94] = 0.0;
   out_4522806033046979489[95] = 1.0;
   out_4522806033046979489[96] = 0.0;
   out_4522806033046979489[97] = 0.0;
   out_4522806033046979489[98] = 0.0;
   out_4522806033046979489[99] = 0.0;
   out_4522806033046979489[100] = 0.0;
   out_4522806033046979489[101] = 0.0;
   out_4522806033046979489[102] = 0.0;
   out_4522806033046979489[103] = 0.0;
   out_4522806033046979489[104] = 0.0;
   out_4522806033046979489[105] = 0.0;
   out_4522806033046979489[106] = 0.0;
   out_4522806033046979489[107] = 0.0;
   out_4522806033046979489[108] = 0.0;
   out_4522806033046979489[109] = 0.0;
   out_4522806033046979489[110] = 0.0;
   out_4522806033046979489[111] = 0.0;
   out_4522806033046979489[112] = 0.0;
   out_4522806033046979489[113] = 0.0;
   out_4522806033046979489[114] = 1.0;
   out_4522806033046979489[115] = 0.0;
   out_4522806033046979489[116] = 0.0;
   out_4522806033046979489[117] = 0.0;
   out_4522806033046979489[118] = 0.0;
   out_4522806033046979489[119] = 0.0;
   out_4522806033046979489[120] = 0.0;
   out_4522806033046979489[121] = 0.0;
   out_4522806033046979489[122] = 0.0;
   out_4522806033046979489[123] = 0.0;
   out_4522806033046979489[124] = 0.0;
   out_4522806033046979489[125] = 0.0;
   out_4522806033046979489[126] = 0.0;
   out_4522806033046979489[127] = 0.0;
   out_4522806033046979489[128] = 0.0;
   out_4522806033046979489[129] = 0.0;
   out_4522806033046979489[130] = 0.0;
   out_4522806033046979489[131] = 0.0;
   out_4522806033046979489[132] = 0.0;
   out_4522806033046979489[133] = 1.0;
   out_4522806033046979489[134] = 0.0;
   out_4522806033046979489[135] = 0.0;
   out_4522806033046979489[136] = 0.0;
   out_4522806033046979489[137] = 0.0;
   out_4522806033046979489[138] = 0.0;
   out_4522806033046979489[139] = 0.0;
   out_4522806033046979489[140] = 0.0;
   out_4522806033046979489[141] = 0.0;
   out_4522806033046979489[142] = 0.0;
   out_4522806033046979489[143] = 0.0;
   out_4522806033046979489[144] = 0.0;
   out_4522806033046979489[145] = 0.0;
   out_4522806033046979489[146] = 0.0;
   out_4522806033046979489[147] = 0.0;
   out_4522806033046979489[148] = 0.0;
   out_4522806033046979489[149] = 0.0;
   out_4522806033046979489[150] = 0.0;
   out_4522806033046979489[151] = 0.0;
   out_4522806033046979489[152] = 1.0;
   out_4522806033046979489[153] = 0.0;
   out_4522806033046979489[154] = 0.0;
   out_4522806033046979489[155] = 0.0;
   out_4522806033046979489[156] = 0.0;
   out_4522806033046979489[157] = 0.0;
   out_4522806033046979489[158] = 0.0;
   out_4522806033046979489[159] = 0.0;
   out_4522806033046979489[160] = 0.0;
   out_4522806033046979489[161] = 0.0;
   out_4522806033046979489[162] = 0.0;
   out_4522806033046979489[163] = 0.0;
   out_4522806033046979489[164] = 0.0;
   out_4522806033046979489[165] = 0.0;
   out_4522806033046979489[166] = 0.0;
   out_4522806033046979489[167] = 0.0;
   out_4522806033046979489[168] = 0.0;
   out_4522806033046979489[169] = 0.0;
   out_4522806033046979489[170] = 0.0;
   out_4522806033046979489[171] = 1.0;
   out_4522806033046979489[172] = 0.0;
   out_4522806033046979489[173] = 0.0;
   out_4522806033046979489[174] = 0.0;
   out_4522806033046979489[175] = 0.0;
   out_4522806033046979489[176] = 0.0;
   out_4522806033046979489[177] = 0.0;
   out_4522806033046979489[178] = 0.0;
   out_4522806033046979489[179] = 0.0;
   out_4522806033046979489[180] = 0.0;
   out_4522806033046979489[181] = 0.0;
   out_4522806033046979489[182] = 0.0;
   out_4522806033046979489[183] = 0.0;
   out_4522806033046979489[184] = 0.0;
   out_4522806033046979489[185] = 0.0;
   out_4522806033046979489[186] = 0.0;
   out_4522806033046979489[187] = 0.0;
   out_4522806033046979489[188] = 0.0;
   out_4522806033046979489[189] = 0.0;
   out_4522806033046979489[190] = 1.0;
   out_4522806033046979489[191] = 0.0;
   out_4522806033046979489[192] = 0.0;
   out_4522806033046979489[193] = 0.0;
   out_4522806033046979489[194] = 0.0;
   out_4522806033046979489[195] = 0.0;
   out_4522806033046979489[196] = 0.0;
   out_4522806033046979489[197] = 0.0;
   out_4522806033046979489[198] = 0.0;
   out_4522806033046979489[199] = 0.0;
   out_4522806033046979489[200] = 0.0;
   out_4522806033046979489[201] = 0.0;
   out_4522806033046979489[202] = 0.0;
   out_4522806033046979489[203] = 0.0;
   out_4522806033046979489[204] = 0.0;
   out_4522806033046979489[205] = 0.0;
   out_4522806033046979489[206] = 0.0;
   out_4522806033046979489[207] = 0.0;
   out_4522806033046979489[208] = 0.0;
   out_4522806033046979489[209] = 1.0;
   out_4522806033046979489[210] = 0.0;
   out_4522806033046979489[211] = 0.0;
   out_4522806033046979489[212] = 0.0;
   out_4522806033046979489[213] = 0.0;
   out_4522806033046979489[214] = 0.0;
   out_4522806033046979489[215] = 0.0;
   out_4522806033046979489[216] = 0.0;
   out_4522806033046979489[217] = 0.0;
   out_4522806033046979489[218] = 0.0;
   out_4522806033046979489[219] = 0.0;
   out_4522806033046979489[220] = 0.0;
   out_4522806033046979489[221] = 0.0;
   out_4522806033046979489[222] = 0.0;
   out_4522806033046979489[223] = 0.0;
   out_4522806033046979489[224] = 0.0;
   out_4522806033046979489[225] = 0.0;
   out_4522806033046979489[226] = 0.0;
   out_4522806033046979489[227] = 0.0;
   out_4522806033046979489[228] = 1.0;
   out_4522806033046979489[229] = 0.0;
   out_4522806033046979489[230] = 0.0;
   out_4522806033046979489[231] = 0.0;
   out_4522806033046979489[232] = 0.0;
   out_4522806033046979489[233] = 0.0;
   out_4522806033046979489[234] = 0.0;
   out_4522806033046979489[235] = 0.0;
   out_4522806033046979489[236] = 0.0;
   out_4522806033046979489[237] = 0.0;
   out_4522806033046979489[238] = 0.0;
   out_4522806033046979489[239] = 0.0;
   out_4522806033046979489[240] = 0.0;
   out_4522806033046979489[241] = 0.0;
   out_4522806033046979489[242] = 0.0;
   out_4522806033046979489[243] = 0.0;
   out_4522806033046979489[244] = 0.0;
   out_4522806033046979489[245] = 0.0;
   out_4522806033046979489[246] = 0.0;
   out_4522806033046979489[247] = 1.0;
   out_4522806033046979489[248] = 0.0;
   out_4522806033046979489[249] = 0.0;
   out_4522806033046979489[250] = 0.0;
   out_4522806033046979489[251] = 0.0;
   out_4522806033046979489[252] = 0.0;
   out_4522806033046979489[253] = 0.0;
   out_4522806033046979489[254] = 0.0;
   out_4522806033046979489[255] = 0.0;
   out_4522806033046979489[256] = 0.0;
   out_4522806033046979489[257] = 0.0;
   out_4522806033046979489[258] = 0.0;
   out_4522806033046979489[259] = 0.0;
   out_4522806033046979489[260] = 0.0;
   out_4522806033046979489[261] = 0.0;
   out_4522806033046979489[262] = 0.0;
   out_4522806033046979489[263] = 0.0;
   out_4522806033046979489[264] = 0.0;
   out_4522806033046979489[265] = 0.0;
   out_4522806033046979489[266] = 1.0;
   out_4522806033046979489[267] = 0.0;
   out_4522806033046979489[268] = 0.0;
   out_4522806033046979489[269] = 0.0;
   out_4522806033046979489[270] = 0.0;
   out_4522806033046979489[271] = 0.0;
   out_4522806033046979489[272] = 0.0;
   out_4522806033046979489[273] = 0.0;
   out_4522806033046979489[274] = 0.0;
   out_4522806033046979489[275] = 0.0;
   out_4522806033046979489[276] = 0.0;
   out_4522806033046979489[277] = 0.0;
   out_4522806033046979489[278] = 0.0;
   out_4522806033046979489[279] = 0.0;
   out_4522806033046979489[280] = 0.0;
   out_4522806033046979489[281] = 0.0;
   out_4522806033046979489[282] = 0.0;
   out_4522806033046979489[283] = 0.0;
   out_4522806033046979489[284] = 0.0;
   out_4522806033046979489[285] = 1.0;
   out_4522806033046979489[286] = 0.0;
   out_4522806033046979489[287] = 0.0;
   out_4522806033046979489[288] = 0.0;
   out_4522806033046979489[289] = 0.0;
   out_4522806033046979489[290] = 0.0;
   out_4522806033046979489[291] = 0.0;
   out_4522806033046979489[292] = 0.0;
   out_4522806033046979489[293] = 0.0;
   out_4522806033046979489[294] = 0.0;
   out_4522806033046979489[295] = 0.0;
   out_4522806033046979489[296] = 0.0;
   out_4522806033046979489[297] = 0.0;
   out_4522806033046979489[298] = 0.0;
   out_4522806033046979489[299] = 0.0;
   out_4522806033046979489[300] = 0.0;
   out_4522806033046979489[301] = 0.0;
   out_4522806033046979489[302] = 0.0;
   out_4522806033046979489[303] = 0.0;
   out_4522806033046979489[304] = 1.0;
   out_4522806033046979489[305] = 0.0;
   out_4522806033046979489[306] = 0.0;
   out_4522806033046979489[307] = 0.0;
   out_4522806033046979489[308] = 0.0;
   out_4522806033046979489[309] = 0.0;
   out_4522806033046979489[310] = 0.0;
   out_4522806033046979489[311] = 0.0;
   out_4522806033046979489[312] = 0.0;
   out_4522806033046979489[313] = 0.0;
   out_4522806033046979489[314] = 0.0;
   out_4522806033046979489[315] = 0.0;
   out_4522806033046979489[316] = 0.0;
   out_4522806033046979489[317] = 0.0;
   out_4522806033046979489[318] = 0.0;
   out_4522806033046979489[319] = 0.0;
   out_4522806033046979489[320] = 0.0;
   out_4522806033046979489[321] = 0.0;
   out_4522806033046979489[322] = 0.0;
   out_4522806033046979489[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4549035263779007924) {
   out_4549035263779007924[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4549035263779007924[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4549035263779007924[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4549035263779007924[3] = dt*state[12] + state[3];
   out_4549035263779007924[4] = dt*state[13] + state[4];
   out_4549035263779007924[5] = dt*state[14] + state[5];
   out_4549035263779007924[6] = state[6];
   out_4549035263779007924[7] = state[7];
   out_4549035263779007924[8] = state[8];
   out_4549035263779007924[9] = state[9];
   out_4549035263779007924[10] = state[10];
   out_4549035263779007924[11] = state[11];
   out_4549035263779007924[12] = state[12];
   out_4549035263779007924[13] = state[13];
   out_4549035263779007924[14] = state[14];
   out_4549035263779007924[15] = state[15];
   out_4549035263779007924[16] = state[16];
   out_4549035263779007924[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8864985683110121579) {
   out_8864985683110121579[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8864985683110121579[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8864985683110121579[2] = 0;
   out_8864985683110121579[3] = 0;
   out_8864985683110121579[4] = 0;
   out_8864985683110121579[5] = 0;
   out_8864985683110121579[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8864985683110121579[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8864985683110121579[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8864985683110121579[9] = 0;
   out_8864985683110121579[10] = 0;
   out_8864985683110121579[11] = 0;
   out_8864985683110121579[12] = 0;
   out_8864985683110121579[13] = 0;
   out_8864985683110121579[14] = 0;
   out_8864985683110121579[15] = 0;
   out_8864985683110121579[16] = 0;
   out_8864985683110121579[17] = 0;
   out_8864985683110121579[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8864985683110121579[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8864985683110121579[20] = 0;
   out_8864985683110121579[21] = 0;
   out_8864985683110121579[22] = 0;
   out_8864985683110121579[23] = 0;
   out_8864985683110121579[24] = 0;
   out_8864985683110121579[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8864985683110121579[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8864985683110121579[27] = 0;
   out_8864985683110121579[28] = 0;
   out_8864985683110121579[29] = 0;
   out_8864985683110121579[30] = 0;
   out_8864985683110121579[31] = 0;
   out_8864985683110121579[32] = 0;
   out_8864985683110121579[33] = 0;
   out_8864985683110121579[34] = 0;
   out_8864985683110121579[35] = 0;
   out_8864985683110121579[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8864985683110121579[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8864985683110121579[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8864985683110121579[39] = 0;
   out_8864985683110121579[40] = 0;
   out_8864985683110121579[41] = 0;
   out_8864985683110121579[42] = 0;
   out_8864985683110121579[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8864985683110121579[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8864985683110121579[45] = 0;
   out_8864985683110121579[46] = 0;
   out_8864985683110121579[47] = 0;
   out_8864985683110121579[48] = 0;
   out_8864985683110121579[49] = 0;
   out_8864985683110121579[50] = 0;
   out_8864985683110121579[51] = 0;
   out_8864985683110121579[52] = 0;
   out_8864985683110121579[53] = 0;
   out_8864985683110121579[54] = 0;
   out_8864985683110121579[55] = 0;
   out_8864985683110121579[56] = 0;
   out_8864985683110121579[57] = 1;
   out_8864985683110121579[58] = 0;
   out_8864985683110121579[59] = 0;
   out_8864985683110121579[60] = 0;
   out_8864985683110121579[61] = 0;
   out_8864985683110121579[62] = 0;
   out_8864985683110121579[63] = 0;
   out_8864985683110121579[64] = 0;
   out_8864985683110121579[65] = 0;
   out_8864985683110121579[66] = dt;
   out_8864985683110121579[67] = 0;
   out_8864985683110121579[68] = 0;
   out_8864985683110121579[69] = 0;
   out_8864985683110121579[70] = 0;
   out_8864985683110121579[71] = 0;
   out_8864985683110121579[72] = 0;
   out_8864985683110121579[73] = 0;
   out_8864985683110121579[74] = 0;
   out_8864985683110121579[75] = 0;
   out_8864985683110121579[76] = 1;
   out_8864985683110121579[77] = 0;
   out_8864985683110121579[78] = 0;
   out_8864985683110121579[79] = 0;
   out_8864985683110121579[80] = 0;
   out_8864985683110121579[81] = 0;
   out_8864985683110121579[82] = 0;
   out_8864985683110121579[83] = 0;
   out_8864985683110121579[84] = 0;
   out_8864985683110121579[85] = dt;
   out_8864985683110121579[86] = 0;
   out_8864985683110121579[87] = 0;
   out_8864985683110121579[88] = 0;
   out_8864985683110121579[89] = 0;
   out_8864985683110121579[90] = 0;
   out_8864985683110121579[91] = 0;
   out_8864985683110121579[92] = 0;
   out_8864985683110121579[93] = 0;
   out_8864985683110121579[94] = 0;
   out_8864985683110121579[95] = 1;
   out_8864985683110121579[96] = 0;
   out_8864985683110121579[97] = 0;
   out_8864985683110121579[98] = 0;
   out_8864985683110121579[99] = 0;
   out_8864985683110121579[100] = 0;
   out_8864985683110121579[101] = 0;
   out_8864985683110121579[102] = 0;
   out_8864985683110121579[103] = 0;
   out_8864985683110121579[104] = dt;
   out_8864985683110121579[105] = 0;
   out_8864985683110121579[106] = 0;
   out_8864985683110121579[107] = 0;
   out_8864985683110121579[108] = 0;
   out_8864985683110121579[109] = 0;
   out_8864985683110121579[110] = 0;
   out_8864985683110121579[111] = 0;
   out_8864985683110121579[112] = 0;
   out_8864985683110121579[113] = 0;
   out_8864985683110121579[114] = 1;
   out_8864985683110121579[115] = 0;
   out_8864985683110121579[116] = 0;
   out_8864985683110121579[117] = 0;
   out_8864985683110121579[118] = 0;
   out_8864985683110121579[119] = 0;
   out_8864985683110121579[120] = 0;
   out_8864985683110121579[121] = 0;
   out_8864985683110121579[122] = 0;
   out_8864985683110121579[123] = 0;
   out_8864985683110121579[124] = 0;
   out_8864985683110121579[125] = 0;
   out_8864985683110121579[126] = 0;
   out_8864985683110121579[127] = 0;
   out_8864985683110121579[128] = 0;
   out_8864985683110121579[129] = 0;
   out_8864985683110121579[130] = 0;
   out_8864985683110121579[131] = 0;
   out_8864985683110121579[132] = 0;
   out_8864985683110121579[133] = 1;
   out_8864985683110121579[134] = 0;
   out_8864985683110121579[135] = 0;
   out_8864985683110121579[136] = 0;
   out_8864985683110121579[137] = 0;
   out_8864985683110121579[138] = 0;
   out_8864985683110121579[139] = 0;
   out_8864985683110121579[140] = 0;
   out_8864985683110121579[141] = 0;
   out_8864985683110121579[142] = 0;
   out_8864985683110121579[143] = 0;
   out_8864985683110121579[144] = 0;
   out_8864985683110121579[145] = 0;
   out_8864985683110121579[146] = 0;
   out_8864985683110121579[147] = 0;
   out_8864985683110121579[148] = 0;
   out_8864985683110121579[149] = 0;
   out_8864985683110121579[150] = 0;
   out_8864985683110121579[151] = 0;
   out_8864985683110121579[152] = 1;
   out_8864985683110121579[153] = 0;
   out_8864985683110121579[154] = 0;
   out_8864985683110121579[155] = 0;
   out_8864985683110121579[156] = 0;
   out_8864985683110121579[157] = 0;
   out_8864985683110121579[158] = 0;
   out_8864985683110121579[159] = 0;
   out_8864985683110121579[160] = 0;
   out_8864985683110121579[161] = 0;
   out_8864985683110121579[162] = 0;
   out_8864985683110121579[163] = 0;
   out_8864985683110121579[164] = 0;
   out_8864985683110121579[165] = 0;
   out_8864985683110121579[166] = 0;
   out_8864985683110121579[167] = 0;
   out_8864985683110121579[168] = 0;
   out_8864985683110121579[169] = 0;
   out_8864985683110121579[170] = 0;
   out_8864985683110121579[171] = 1;
   out_8864985683110121579[172] = 0;
   out_8864985683110121579[173] = 0;
   out_8864985683110121579[174] = 0;
   out_8864985683110121579[175] = 0;
   out_8864985683110121579[176] = 0;
   out_8864985683110121579[177] = 0;
   out_8864985683110121579[178] = 0;
   out_8864985683110121579[179] = 0;
   out_8864985683110121579[180] = 0;
   out_8864985683110121579[181] = 0;
   out_8864985683110121579[182] = 0;
   out_8864985683110121579[183] = 0;
   out_8864985683110121579[184] = 0;
   out_8864985683110121579[185] = 0;
   out_8864985683110121579[186] = 0;
   out_8864985683110121579[187] = 0;
   out_8864985683110121579[188] = 0;
   out_8864985683110121579[189] = 0;
   out_8864985683110121579[190] = 1;
   out_8864985683110121579[191] = 0;
   out_8864985683110121579[192] = 0;
   out_8864985683110121579[193] = 0;
   out_8864985683110121579[194] = 0;
   out_8864985683110121579[195] = 0;
   out_8864985683110121579[196] = 0;
   out_8864985683110121579[197] = 0;
   out_8864985683110121579[198] = 0;
   out_8864985683110121579[199] = 0;
   out_8864985683110121579[200] = 0;
   out_8864985683110121579[201] = 0;
   out_8864985683110121579[202] = 0;
   out_8864985683110121579[203] = 0;
   out_8864985683110121579[204] = 0;
   out_8864985683110121579[205] = 0;
   out_8864985683110121579[206] = 0;
   out_8864985683110121579[207] = 0;
   out_8864985683110121579[208] = 0;
   out_8864985683110121579[209] = 1;
   out_8864985683110121579[210] = 0;
   out_8864985683110121579[211] = 0;
   out_8864985683110121579[212] = 0;
   out_8864985683110121579[213] = 0;
   out_8864985683110121579[214] = 0;
   out_8864985683110121579[215] = 0;
   out_8864985683110121579[216] = 0;
   out_8864985683110121579[217] = 0;
   out_8864985683110121579[218] = 0;
   out_8864985683110121579[219] = 0;
   out_8864985683110121579[220] = 0;
   out_8864985683110121579[221] = 0;
   out_8864985683110121579[222] = 0;
   out_8864985683110121579[223] = 0;
   out_8864985683110121579[224] = 0;
   out_8864985683110121579[225] = 0;
   out_8864985683110121579[226] = 0;
   out_8864985683110121579[227] = 0;
   out_8864985683110121579[228] = 1;
   out_8864985683110121579[229] = 0;
   out_8864985683110121579[230] = 0;
   out_8864985683110121579[231] = 0;
   out_8864985683110121579[232] = 0;
   out_8864985683110121579[233] = 0;
   out_8864985683110121579[234] = 0;
   out_8864985683110121579[235] = 0;
   out_8864985683110121579[236] = 0;
   out_8864985683110121579[237] = 0;
   out_8864985683110121579[238] = 0;
   out_8864985683110121579[239] = 0;
   out_8864985683110121579[240] = 0;
   out_8864985683110121579[241] = 0;
   out_8864985683110121579[242] = 0;
   out_8864985683110121579[243] = 0;
   out_8864985683110121579[244] = 0;
   out_8864985683110121579[245] = 0;
   out_8864985683110121579[246] = 0;
   out_8864985683110121579[247] = 1;
   out_8864985683110121579[248] = 0;
   out_8864985683110121579[249] = 0;
   out_8864985683110121579[250] = 0;
   out_8864985683110121579[251] = 0;
   out_8864985683110121579[252] = 0;
   out_8864985683110121579[253] = 0;
   out_8864985683110121579[254] = 0;
   out_8864985683110121579[255] = 0;
   out_8864985683110121579[256] = 0;
   out_8864985683110121579[257] = 0;
   out_8864985683110121579[258] = 0;
   out_8864985683110121579[259] = 0;
   out_8864985683110121579[260] = 0;
   out_8864985683110121579[261] = 0;
   out_8864985683110121579[262] = 0;
   out_8864985683110121579[263] = 0;
   out_8864985683110121579[264] = 0;
   out_8864985683110121579[265] = 0;
   out_8864985683110121579[266] = 1;
   out_8864985683110121579[267] = 0;
   out_8864985683110121579[268] = 0;
   out_8864985683110121579[269] = 0;
   out_8864985683110121579[270] = 0;
   out_8864985683110121579[271] = 0;
   out_8864985683110121579[272] = 0;
   out_8864985683110121579[273] = 0;
   out_8864985683110121579[274] = 0;
   out_8864985683110121579[275] = 0;
   out_8864985683110121579[276] = 0;
   out_8864985683110121579[277] = 0;
   out_8864985683110121579[278] = 0;
   out_8864985683110121579[279] = 0;
   out_8864985683110121579[280] = 0;
   out_8864985683110121579[281] = 0;
   out_8864985683110121579[282] = 0;
   out_8864985683110121579[283] = 0;
   out_8864985683110121579[284] = 0;
   out_8864985683110121579[285] = 1;
   out_8864985683110121579[286] = 0;
   out_8864985683110121579[287] = 0;
   out_8864985683110121579[288] = 0;
   out_8864985683110121579[289] = 0;
   out_8864985683110121579[290] = 0;
   out_8864985683110121579[291] = 0;
   out_8864985683110121579[292] = 0;
   out_8864985683110121579[293] = 0;
   out_8864985683110121579[294] = 0;
   out_8864985683110121579[295] = 0;
   out_8864985683110121579[296] = 0;
   out_8864985683110121579[297] = 0;
   out_8864985683110121579[298] = 0;
   out_8864985683110121579[299] = 0;
   out_8864985683110121579[300] = 0;
   out_8864985683110121579[301] = 0;
   out_8864985683110121579[302] = 0;
   out_8864985683110121579[303] = 0;
   out_8864985683110121579[304] = 1;
   out_8864985683110121579[305] = 0;
   out_8864985683110121579[306] = 0;
   out_8864985683110121579[307] = 0;
   out_8864985683110121579[308] = 0;
   out_8864985683110121579[309] = 0;
   out_8864985683110121579[310] = 0;
   out_8864985683110121579[311] = 0;
   out_8864985683110121579[312] = 0;
   out_8864985683110121579[313] = 0;
   out_8864985683110121579[314] = 0;
   out_8864985683110121579[315] = 0;
   out_8864985683110121579[316] = 0;
   out_8864985683110121579[317] = 0;
   out_8864985683110121579[318] = 0;
   out_8864985683110121579[319] = 0;
   out_8864985683110121579[320] = 0;
   out_8864985683110121579[321] = 0;
   out_8864985683110121579[322] = 0;
   out_8864985683110121579[323] = 1;
}
void h_4(double *state, double *unused, double *out_3762734515711563779) {
   out_3762734515711563779[0] = state[6] + state[9];
   out_3762734515711563779[1] = state[7] + state[10];
   out_3762734515711563779[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_672365171686404261) {
   out_672365171686404261[0] = 0;
   out_672365171686404261[1] = 0;
   out_672365171686404261[2] = 0;
   out_672365171686404261[3] = 0;
   out_672365171686404261[4] = 0;
   out_672365171686404261[5] = 0;
   out_672365171686404261[6] = 1;
   out_672365171686404261[7] = 0;
   out_672365171686404261[8] = 0;
   out_672365171686404261[9] = 1;
   out_672365171686404261[10] = 0;
   out_672365171686404261[11] = 0;
   out_672365171686404261[12] = 0;
   out_672365171686404261[13] = 0;
   out_672365171686404261[14] = 0;
   out_672365171686404261[15] = 0;
   out_672365171686404261[16] = 0;
   out_672365171686404261[17] = 0;
   out_672365171686404261[18] = 0;
   out_672365171686404261[19] = 0;
   out_672365171686404261[20] = 0;
   out_672365171686404261[21] = 0;
   out_672365171686404261[22] = 0;
   out_672365171686404261[23] = 0;
   out_672365171686404261[24] = 0;
   out_672365171686404261[25] = 1;
   out_672365171686404261[26] = 0;
   out_672365171686404261[27] = 0;
   out_672365171686404261[28] = 1;
   out_672365171686404261[29] = 0;
   out_672365171686404261[30] = 0;
   out_672365171686404261[31] = 0;
   out_672365171686404261[32] = 0;
   out_672365171686404261[33] = 0;
   out_672365171686404261[34] = 0;
   out_672365171686404261[35] = 0;
   out_672365171686404261[36] = 0;
   out_672365171686404261[37] = 0;
   out_672365171686404261[38] = 0;
   out_672365171686404261[39] = 0;
   out_672365171686404261[40] = 0;
   out_672365171686404261[41] = 0;
   out_672365171686404261[42] = 0;
   out_672365171686404261[43] = 0;
   out_672365171686404261[44] = 1;
   out_672365171686404261[45] = 0;
   out_672365171686404261[46] = 0;
   out_672365171686404261[47] = 1;
   out_672365171686404261[48] = 0;
   out_672365171686404261[49] = 0;
   out_672365171686404261[50] = 0;
   out_672365171686404261[51] = 0;
   out_672365171686404261[52] = 0;
   out_672365171686404261[53] = 0;
}
void h_10(double *state, double *unused, double *out_3744239542214290894) {
   out_3744239542214290894[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3744239542214290894[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3744239542214290894[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_704080362957931033) {
   out_704080362957931033[0] = 0;
   out_704080362957931033[1] = 9.8100000000000005*cos(state[1]);
   out_704080362957931033[2] = 0;
   out_704080362957931033[3] = 0;
   out_704080362957931033[4] = -state[8];
   out_704080362957931033[5] = state[7];
   out_704080362957931033[6] = 0;
   out_704080362957931033[7] = state[5];
   out_704080362957931033[8] = -state[4];
   out_704080362957931033[9] = 0;
   out_704080362957931033[10] = 0;
   out_704080362957931033[11] = 0;
   out_704080362957931033[12] = 1;
   out_704080362957931033[13] = 0;
   out_704080362957931033[14] = 0;
   out_704080362957931033[15] = 1;
   out_704080362957931033[16] = 0;
   out_704080362957931033[17] = 0;
   out_704080362957931033[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_704080362957931033[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_704080362957931033[20] = 0;
   out_704080362957931033[21] = state[8];
   out_704080362957931033[22] = 0;
   out_704080362957931033[23] = -state[6];
   out_704080362957931033[24] = -state[5];
   out_704080362957931033[25] = 0;
   out_704080362957931033[26] = state[3];
   out_704080362957931033[27] = 0;
   out_704080362957931033[28] = 0;
   out_704080362957931033[29] = 0;
   out_704080362957931033[30] = 0;
   out_704080362957931033[31] = 1;
   out_704080362957931033[32] = 0;
   out_704080362957931033[33] = 0;
   out_704080362957931033[34] = 1;
   out_704080362957931033[35] = 0;
   out_704080362957931033[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_704080362957931033[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_704080362957931033[38] = 0;
   out_704080362957931033[39] = -state[7];
   out_704080362957931033[40] = state[6];
   out_704080362957931033[41] = 0;
   out_704080362957931033[42] = state[4];
   out_704080362957931033[43] = -state[3];
   out_704080362957931033[44] = 0;
   out_704080362957931033[45] = 0;
   out_704080362957931033[46] = 0;
   out_704080362957931033[47] = 0;
   out_704080362957931033[48] = 0;
   out_704080362957931033[49] = 0;
   out_704080362957931033[50] = 1;
   out_704080362957931033[51] = 0;
   out_704080362957931033[52] = 0;
   out_704080362957931033[53] = 1;
}
void h_13(double *state, double *unused, double *out_6770705826550858406) {
   out_6770705826550858406[0] = state[3];
   out_6770705826550858406[1] = state[4];
   out_6770705826550858406[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2539908653645928540) {
   out_2539908653645928540[0] = 0;
   out_2539908653645928540[1] = 0;
   out_2539908653645928540[2] = 0;
   out_2539908653645928540[3] = 1;
   out_2539908653645928540[4] = 0;
   out_2539908653645928540[5] = 0;
   out_2539908653645928540[6] = 0;
   out_2539908653645928540[7] = 0;
   out_2539908653645928540[8] = 0;
   out_2539908653645928540[9] = 0;
   out_2539908653645928540[10] = 0;
   out_2539908653645928540[11] = 0;
   out_2539908653645928540[12] = 0;
   out_2539908653645928540[13] = 0;
   out_2539908653645928540[14] = 0;
   out_2539908653645928540[15] = 0;
   out_2539908653645928540[16] = 0;
   out_2539908653645928540[17] = 0;
   out_2539908653645928540[18] = 0;
   out_2539908653645928540[19] = 0;
   out_2539908653645928540[20] = 0;
   out_2539908653645928540[21] = 0;
   out_2539908653645928540[22] = 1;
   out_2539908653645928540[23] = 0;
   out_2539908653645928540[24] = 0;
   out_2539908653645928540[25] = 0;
   out_2539908653645928540[26] = 0;
   out_2539908653645928540[27] = 0;
   out_2539908653645928540[28] = 0;
   out_2539908653645928540[29] = 0;
   out_2539908653645928540[30] = 0;
   out_2539908653645928540[31] = 0;
   out_2539908653645928540[32] = 0;
   out_2539908653645928540[33] = 0;
   out_2539908653645928540[34] = 0;
   out_2539908653645928540[35] = 0;
   out_2539908653645928540[36] = 0;
   out_2539908653645928540[37] = 0;
   out_2539908653645928540[38] = 0;
   out_2539908653645928540[39] = 0;
   out_2539908653645928540[40] = 0;
   out_2539908653645928540[41] = 1;
   out_2539908653645928540[42] = 0;
   out_2539908653645928540[43] = 0;
   out_2539908653645928540[44] = 0;
   out_2539908653645928540[45] = 0;
   out_2539908653645928540[46] = 0;
   out_2539908653645928540[47] = 0;
   out_2539908653645928540[48] = 0;
   out_2539908653645928540[49] = 0;
   out_2539908653645928540[50] = 0;
   out_2539908653645928540[51] = 0;
   out_2539908653645928540[52] = 0;
   out_2539908653645928540[53] = 0;
}
void h_14(double *state, double *unused, double *out_3527789304040821044) {
   out_3527789304040821044[0] = state[6];
   out_3527789304040821044[1] = state[7];
   out_3527789304040821044[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3290875684653080268) {
   out_3290875684653080268[0] = 0;
   out_3290875684653080268[1] = 0;
   out_3290875684653080268[2] = 0;
   out_3290875684653080268[3] = 0;
   out_3290875684653080268[4] = 0;
   out_3290875684653080268[5] = 0;
   out_3290875684653080268[6] = 1;
   out_3290875684653080268[7] = 0;
   out_3290875684653080268[8] = 0;
   out_3290875684653080268[9] = 0;
   out_3290875684653080268[10] = 0;
   out_3290875684653080268[11] = 0;
   out_3290875684653080268[12] = 0;
   out_3290875684653080268[13] = 0;
   out_3290875684653080268[14] = 0;
   out_3290875684653080268[15] = 0;
   out_3290875684653080268[16] = 0;
   out_3290875684653080268[17] = 0;
   out_3290875684653080268[18] = 0;
   out_3290875684653080268[19] = 0;
   out_3290875684653080268[20] = 0;
   out_3290875684653080268[21] = 0;
   out_3290875684653080268[22] = 0;
   out_3290875684653080268[23] = 0;
   out_3290875684653080268[24] = 0;
   out_3290875684653080268[25] = 1;
   out_3290875684653080268[26] = 0;
   out_3290875684653080268[27] = 0;
   out_3290875684653080268[28] = 0;
   out_3290875684653080268[29] = 0;
   out_3290875684653080268[30] = 0;
   out_3290875684653080268[31] = 0;
   out_3290875684653080268[32] = 0;
   out_3290875684653080268[33] = 0;
   out_3290875684653080268[34] = 0;
   out_3290875684653080268[35] = 0;
   out_3290875684653080268[36] = 0;
   out_3290875684653080268[37] = 0;
   out_3290875684653080268[38] = 0;
   out_3290875684653080268[39] = 0;
   out_3290875684653080268[40] = 0;
   out_3290875684653080268[41] = 0;
   out_3290875684653080268[42] = 0;
   out_3290875684653080268[43] = 0;
   out_3290875684653080268[44] = 1;
   out_3290875684653080268[45] = 0;
   out_3290875684653080268[46] = 0;
   out_3290875684653080268[47] = 0;
   out_3290875684653080268[48] = 0;
   out_3290875684653080268[49] = 0;
   out_3290875684653080268[50] = 0;
   out_3290875684653080268[51] = 0;
   out_3290875684653080268[52] = 0;
   out_3290875684653080268[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3965258856132538103) {
  err_fun(nom_x, delta_x, out_3965258856132538103);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5412015007655879645) {
  inv_err_fun(nom_x, true_x, out_5412015007655879645);
}
void pose_H_mod_fun(double *state, double *out_4522806033046979489) {
  H_mod_fun(state, out_4522806033046979489);
}
void pose_f_fun(double *state, double dt, double *out_4549035263779007924) {
  f_fun(state,  dt, out_4549035263779007924);
}
void pose_F_fun(double *state, double dt, double *out_8864985683110121579) {
  F_fun(state,  dt, out_8864985683110121579);
}
void pose_h_4(double *state, double *unused, double *out_3762734515711563779) {
  h_4(state, unused, out_3762734515711563779);
}
void pose_H_4(double *state, double *unused, double *out_672365171686404261) {
  H_4(state, unused, out_672365171686404261);
}
void pose_h_10(double *state, double *unused, double *out_3744239542214290894) {
  h_10(state, unused, out_3744239542214290894);
}
void pose_H_10(double *state, double *unused, double *out_704080362957931033) {
  H_10(state, unused, out_704080362957931033);
}
void pose_h_13(double *state, double *unused, double *out_6770705826550858406) {
  h_13(state, unused, out_6770705826550858406);
}
void pose_H_13(double *state, double *unused, double *out_2539908653645928540) {
  H_13(state, unused, out_2539908653645928540);
}
void pose_h_14(double *state, double *unused, double *out_3527789304040821044) {
  h_14(state, unused, out_3527789304040821044);
}
void pose_H_14(double *state, double *unused, double *out_3290875684653080268) {
  H_14(state, unused, out_3290875684653080268);
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
