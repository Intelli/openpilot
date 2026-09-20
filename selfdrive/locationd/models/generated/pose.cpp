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
void err_fun(double *nom_x, double *delta_x, double *out_4788240677246511833) {
   out_4788240677246511833[0] = delta_x[0] + nom_x[0];
   out_4788240677246511833[1] = delta_x[1] + nom_x[1];
   out_4788240677246511833[2] = delta_x[2] + nom_x[2];
   out_4788240677246511833[3] = delta_x[3] + nom_x[3];
   out_4788240677246511833[4] = delta_x[4] + nom_x[4];
   out_4788240677246511833[5] = delta_x[5] + nom_x[5];
   out_4788240677246511833[6] = delta_x[6] + nom_x[6];
   out_4788240677246511833[7] = delta_x[7] + nom_x[7];
   out_4788240677246511833[8] = delta_x[8] + nom_x[8];
   out_4788240677246511833[9] = delta_x[9] + nom_x[9];
   out_4788240677246511833[10] = delta_x[10] + nom_x[10];
   out_4788240677246511833[11] = delta_x[11] + nom_x[11];
   out_4788240677246511833[12] = delta_x[12] + nom_x[12];
   out_4788240677246511833[13] = delta_x[13] + nom_x[13];
   out_4788240677246511833[14] = delta_x[14] + nom_x[14];
   out_4788240677246511833[15] = delta_x[15] + nom_x[15];
   out_4788240677246511833[16] = delta_x[16] + nom_x[16];
   out_4788240677246511833[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5975192517926128029) {
   out_5975192517926128029[0] = -nom_x[0] + true_x[0];
   out_5975192517926128029[1] = -nom_x[1] + true_x[1];
   out_5975192517926128029[2] = -nom_x[2] + true_x[2];
   out_5975192517926128029[3] = -nom_x[3] + true_x[3];
   out_5975192517926128029[4] = -nom_x[4] + true_x[4];
   out_5975192517926128029[5] = -nom_x[5] + true_x[5];
   out_5975192517926128029[6] = -nom_x[6] + true_x[6];
   out_5975192517926128029[7] = -nom_x[7] + true_x[7];
   out_5975192517926128029[8] = -nom_x[8] + true_x[8];
   out_5975192517926128029[9] = -nom_x[9] + true_x[9];
   out_5975192517926128029[10] = -nom_x[10] + true_x[10];
   out_5975192517926128029[11] = -nom_x[11] + true_x[11];
   out_5975192517926128029[12] = -nom_x[12] + true_x[12];
   out_5975192517926128029[13] = -nom_x[13] + true_x[13];
   out_5975192517926128029[14] = -nom_x[14] + true_x[14];
   out_5975192517926128029[15] = -nom_x[15] + true_x[15];
   out_5975192517926128029[16] = -nom_x[16] + true_x[16];
   out_5975192517926128029[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1132541603520551659) {
   out_1132541603520551659[0] = 1.0;
   out_1132541603520551659[1] = 0.0;
   out_1132541603520551659[2] = 0.0;
   out_1132541603520551659[3] = 0.0;
   out_1132541603520551659[4] = 0.0;
   out_1132541603520551659[5] = 0.0;
   out_1132541603520551659[6] = 0.0;
   out_1132541603520551659[7] = 0.0;
   out_1132541603520551659[8] = 0.0;
   out_1132541603520551659[9] = 0.0;
   out_1132541603520551659[10] = 0.0;
   out_1132541603520551659[11] = 0.0;
   out_1132541603520551659[12] = 0.0;
   out_1132541603520551659[13] = 0.0;
   out_1132541603520551659[14] = 0.0;
   out_1132541603520551659[15] = 0.0;
   out_1132541603520551659[16] = 0.0;
   out_1132541603520551659[17] = 0.0;
   out_1132541603520551659[18] = 0.0;
   out_1132541603520551659[19] = 1.0;
   out_1132541603520551659[20] = 0.0;
   out_1132541603520551659[21] = 0.0;
   out_1132541603520551659[22] = 0.0;
   out_1132541603520551659[23] = 0.0;
   out_1132541603520551659[24] = 0.0;
   out_1132541603520551659[25] = 0.0;
   out_1132541603520551659[26] = 0.0;
   out_1132541603520551659[27] = 0.0;
   out_1132541603520551659[28] = 0.0;
   out_1132541603520551659[29] = 0.0;
   out_1132541603520551659[30] = 0.0;
   out_1132541603520551659[31] = 0.0;
   out_1132541603520551659[32] = 0.0;
   out_1132541603520551659[33] = 0.0;
   out_1132541603520551659[34] = 0.0;
   out_1132541603520551659[35] = 0.0;
   out_1132541603520551659[36] = 0.0;
   out_1132541603520551659[37] = 0.0;
   out_1132541603520551659[38] = 1.0;
   out_1132541603520551659[39] = 0.0;
   out_1132541603520551659[40] = 0.0;
   out_1132541603520551659[41] = 0.0;
   out_1132541603520551659[42] = 0.0;
   out_1132541603520551659[43] = 0.0;
   out_1132541603520551659[44] = 0.0;
   out_1132541603520551659[45] = 0.0;
   out_1132541603520551659[46] = 0.0;
   out_1132541603520551659[47] = 0.0;
   out_1132541603520551659[48] = 0.0;
   out_1132541603520551659[49] = 0.0;
   out_1132541603520551659[50] = 0.0;
   out_1132541603520551659[51] = 0.0;
   out_1132541603520551659[52] = 0.0;
   out_1132541603520551659[53] = 0.0;
   out_1132541603520551659[54] = 0.0;
   out_1132541603520551659[55] = 0.0;
   out_1132541603520551659[56] = 0.0;
   out_1132541603520551659[57] = 1.0;
   out_1132541603520551659[58] = 0.0;
   out_1132541603520551659[59] = 0.0;
   out_1132541603520551659[60] = 0.0;
   out_1132541603520551659[61] = 0.0;
   out_1132541603520551659[62] = 0.0;
   out_1132541603520551659[63] = 0.0;
   out_1132541603520551659[64] = 0.0;
   out_1132541603520551659[65] = 0.0;
   out_1132541603520551659[66] = 0.0;
   out_1132541603520551659[67] = 0.0;
   out_1132541603520551659[68] = 0.0;
   out_1132541603520551659[69] = 0.0;
   out_1132541603520551659[70] = 0.0;
   out_1132541603520551659[71] = 0.0;
   out_1132541603520551659[72] = 0.0;
   out_1132541603520551659[73] = 0.0;
   out_1132541603520551659[74] = 0.0;
   out_1132541603520551659[75] = 0.0;
   out_1132541603520551659[76] = 1.0;
   out_1132541603520551659[77] = 0.0;
   out_1132541603520551659[78] = 0.0;
   out_1132541603520551659[79] = 0.0;
   out_1132541603520551659[80] = 0.0;
   out_1132541603520551659[81] = 0.0;
   out_1132541603520551659[82] = 0.0;
   out_1132541603520551659[83] = 0.0;
   out_1132541603520551659[84] = 0.0;
   out_1132541603520551659[85] = 0.0;
   out_1132541603520551659[86] = 0.0;
   out_1132541603520551659[87] = 0.0;
   out_1132541603520551659[88] = 0.0;
   out_1132541603520551659[89] = 0.0;
   out_1132541603520551659[90] = 0.0;
   out_1132541603520551659[91] = 0.0;
   out_1132541603520551659[92] = 0.0;
   out_1132541603520551659[93] = 0.0;
   out_1132541603520551659[94] = 0.0;
   out_1132541603520551659[95] = 1.0;
   out_1132541603520551659[96] = 0.0;
   out_1132541603520551659[97] = 0.0;
   out_1132541603520551659[98] = 0.0;
   out_1132541603520551659[99] = 0.0;
   out_1132541603520551659[100] = 0.0;
   out_1132541603520551659[101] = 0.0;
   out_1132541603520551659[102] = 0.0;
   out_1132541603520551659[103] = 0.0;
   out_1132541603520551659[104] = 0.0;
   out_1132541603520551659[105] = 0.0;
   out_1132541603520551659[106] = 0.0;
   out_1132541603520551659[107] = 0.0;
   out_1132541603520551659[108] = 0.0;
   out_1132541603520551659[109] = 0.0;
   out_1132541603520551659[110] = 0.0;
   out_1132541603520551659[111] = 0.0;
   out_1132541603520551659[112] = 0.0;
   out_1132541603520551659[113] = 0.0;
   out_1132541603520551659[114] = 1.0;
   out_1132541603520551659[115] = 0.0;
   out_1132541603520551659[116] = 0.0;
   out_1132541603520551659[117] = 0.0;
   out_1132541603520551659[118] = 0.0;
   out_1132541603520551659[119] = 0.0;
   out_1132541603520551659[120] = 0.0;
   out_1132541603520551659[121] = 0.0;
   out_1132541603520551659[122] = 0.0;
   out_1132541603520551659[123] = 0.0;
   out_1132541603520551659[124] = 0.0;
   out_1132541603520551659[125] = 0.0;
   out_1132541603520551659[126] = 0.0;
   out_1132541603520551659[127] = 0.0;
   out_1132541603520551659[128] = 0.0;
   out_1132541603520551659[129] = 0.0;
   out_1132541603520551659[130] = 0.0;
   out_1132541603520551659[131] = 0.0;
   out_1132541603520551659[132] = 0.0;
   out_1132541603520551659[133] = 1.0;
   out_1132541603520551659[134] = 0.0;
   out_1132541603520551659[135] = 0.0;
   out_1132541603520551659[136] = 0.0;
   out_1132541603520551659[137] = 0.0;
   out_1132541603520551659[138] = 0.0;
   out_1132541603520551659[139] = 0.0;
   out_1132541603520551659[140] = 0.0;
   out_1132541603520551659[141] = 0.0;
   out_1132541603520551659[142] = 0.0;
   out_1132541603520551659[143] = 0.0;
   out_1132541603520551659[144] = 0.0;
   out_1132541603520551659[145] = 0.0;
   out_1132541603520551659[146] = 0.0;
   out_1132541603520551659[147] = 0.0;
   out_1132541603520551659[148] = 0.0;
   out_1132541603520551659[149] = 0.0;
   out_1132541603520551659[150] = 0.0;
   out_1132541603520551659[151] = 0.0;
   out_1132541603520551659[152] = 1.0;
   out_1132541603520551659[153] = 0.0;
   out_1132541603520551659[154] = 0.0;
   out_1132541603520551659[155] = 0.0;
   out_1132541603520551659[156] = 0.0;
   out_1132541603520551659[157] = 0.0;
   out_1132541603520551659[158] = 0.0;
   out_1132541603520551659[159] = 0.0;
   out_1132541603520551659[160] = 0.0;
   out_1132541603520551659[161] = 0.0;
   out_1132541603520551659[162] = 0.0;
   out_1132541603520551659[163] = 0.0;
   out_1132541603520551659[164] = 0.0;
   out_1132541603520551659[165] = 0.0;
   out_1132541603520551659[166] = 0.0;
   out_1132541603520551659[167] = 0.0;
   out_1132541603520551659[168] = 0.0;
   out_1132541603520551659[169] = 0.0;
   out_1132541603520551659[170] = 0.0;
   out_1132541603520551659[171] = 1.0;
   out_1132541603520551659[172] = 0.0;
   out_1132541603520551659[173] = 0.0;
   out_1132541603520551659[174] = 0.0;
   out_1132541603520551659[175] = 0.0;
   out_1132541603520551659[176] = 0.0;
   out_1132541603520551659[177] = 0.0;
   out_1132541603520551659[178] = 0.0;
   out_1132541603520551659[179] = 0.0;
   out_1132541603520551659[180] = 0.0;
   out_1132541603520551659[181] = 0.0;
   out_1132541603520551659[182] = 0.0;
   out_1132541603520551659[183] = 0.0;
   out_1132541603520551659[184] = 0.0;
   out_1132541603520551659[185] = 0.0;
   out_1132541603520551659[186] = 0.0;
   out_1132541603520551659[187] = 0.0;
   out_1132541603520551659[188] = 0.0;
   out_1132541603520551659[189] = 0.0;
   out_1132541603520551659[190] = 1.0;
   out_1132541603520551659[191] = 0.0;
   out_1132541603520551659[192] = 0.0;
   out_1132541603520551659[193] = 0.0;
   out_1132541603520551659[194] = 0.0;
   out_1132541603520551659[195] = 0.0;
   out_1132541603520551659[196] = 0.0;
   out_1132541603520551659[197] = 0.0;
   out_1132541603520551659[198] = 0.0;
   out_1132541603520551659[199] = 0.0;
   out_1132541603520551659[200] = 0.0;
   out_1132541603520551659[201] = 0.0;
   out_1132541603520551659[202] = 0.0;
   out_1132541603520551659[203] = 0.0;
   out_1132541603520551659[204] = 0.0;
   out_1132541603520551659[205] = 0.0;
   out_1132541603520551659[206] = 0.0;
   out_1132541603520551659[207] = 0.0;
   out_1132541603520551659[208] = 0.0;
   out_1132541603520551659[209] = 1.0;
   out_1132541603520551659[210] = 0.0;
   out_1132541603520551659[211] = 0.0;
   out_1132541603520551659[212] = 0.0;
   out_1132541603520551659[213] = 0.0;
   out_1132541603520551659[214] = 0.0;
   out_1132541603520551659[215] = 0.0;
   out_1132541603520551659[216] = 0.0;
   out_1132541603520551659[217] = 0.0;
   out_1132541603520551659[218] = 0.0;
   out_1132541603520551659[219] = 0.0;
   out_1132541603520551659[220] = 0.0;
   out_1132541603520551659[221] = 0.0;
   out_1132541603520551659[222] = 0.0;
   out_1132541603520551659[223] = 0.0;
   out_1132541603520551659[224] = 0.0;
   out_1132541603520551659[225] = 0.0;
   out_1132541603520551659[226] = 0.0;
   out_1132541603520551659[227] = 0.0;
   out_1132541603520551659[228] = 1.0;
   out_1132541603520551659[229] = 0.0;
   out_1132541603520551659[230] = 0.0;
   out_1132541603520551659[231] = 0.0;
   out_1132541603520551659[232] = 0.0;
   out_1132541603520551659[233] = 0.0;
   out_1132541603520551659[234] = 0.0;
   out_1132541603520551659[235] = 0.0;
   out_1132541603520551659[236] = 0.0;
   out_1132541603520551659[237] = 0.0;
   out_1132541603520551659[238] = 0.0;
   out_1132541603520551659[239] = 0.0;
   out_1132541603520551659[240] = 0.0;
   out_1132541603520551659[241] = 0.0;
   out_1132541603520551659[242] = 0.0;
   out_1132541603520551659[243] = 0.0;
   out_1132541603520551659[244] = 0.0;
   out_1132541603520551659[245] = 0.0;
   out_1132541603520551659[246] = 0.0;
   out_1132541603520551659[247] = 1.0;
   out_1132541603520551659[248] = 0.0;
   out_1132541603520551659[249] = 0.0;
   out_1132541603520551659[250] = 0.0;
   out_1132541603520551659[251] = 0.0;
   out_1132541603520551659[252] = 0.0;
   out_1132541603520551659[253] = 0.0;
   out_1132541603520551659[254] = 0.0;
   out_1132541603520551659[255] = 0.0;
   out_1132541603520551659[256] = 0.0;
   out_1132541603520551659[257] = 0.0;
   out_1132541603520551659[258] = 0.0;
   out_1132541603520551659[259] = 0.0;
   out_1132541603520551659[260] = 0.0;
   out_1132541603520551659[261] = 0.0;
   out_1132541603520551659[262] = 0.0;
   out_1132541603520551659[263] = 0.0;
   out_1132541603520551659[264] = 0.0;
   out_1132541603520551659[265] = 0.0;
   out_1132541603520551659[266] = 1.0;
   out_1132541603520551659[267] = 0.0;
   out_1132541603520551659[268] = 0.0;
   out_1132541603520551659[269] = 0.0;
   out_1132541603520551659[270] = 0.0;
   out_1132541603520551659[271] = 0.0;
   out_1132541603520551659[272] = 0.0;
   out_1132541603520551659[273] = 0.0;
   out_1132541603520551659[274] = 0.0;
   out_1132541603520551659[275] = 0.0;
   out_1132541603520551659[276] = 0.0;
   out_1132541603520551659[277] = 0.0;
   out_1132541603520551659[278] = 0.0;
   out_1132541603520551659[279] = 0.0;
   out_1132541603520551659[280] = 0.0;
   out_1132541603520551659[281] = 0.0;
   out_1132541603520551659[282] = 0.0;
   out_1132541603520551659[283] = 0.0;
   out_1132541603520551659[284] = 0.0;
   out_1132541603520551659[285] = 1.0;
   out_1132541603520551659[286] = 0.0;
   out_1132541603520551659[287] = 0.0;
   out_1132541603520551659[288] = 0.0;
   out_1132541603520551659[289] = 0.0;
   out_1132541603520551659[290] = 0.0;
   out_1132541603520551659[291] = 0.0;
   out_1132541603520551659[292] = 0.0;
   out_1132541603520551659[293] = 0.0;
   out_1132541603520551659[294] = 0.0;
   out_1132541603520551659[295] = 0.0;
   out_1132541603520551659[296] = 0.0;
   out_1132541603520551659[297] = 0.0;
   out_1132541603520551659[298] = 0.0;
   out_1132541603520551659[299] = 0.0;
   out_1132541603520551659[300] = 0.0;
   out_1132541603520551659[301] = 0.0;
   out_1132541603520551659[302] = 0.0;
   out_1132541603520551659[303] = 0.0;
   out_1132541603520551659[304] = 1.0;
   out_1132541603520551659[305] = 0.0;
   out_1132541603520551659[306] = 0.0;
   out_1132541603520551659[307] = 0.0;
   out_1132541603520551659[308] = 0.0;
   out_1132541603520551659[309] = 0.0;
   out_1132541603520551659[310] = 0.0;
   out_1132541603520551659[311] = 0.0;
   out_1132541603520551659[312] = 0.0;
   out_1132541603520551659[313] = 0.0;
   out_1132541603520551659[314] = 0.0;
   out_1132541603520551659[315] = 0.0;
   out_1132541603520551659[316] = 0.0;
   out_1132541603520551659[317] = 0.0;
   out_1132541603520551659[318] = 0.0;
   out_1132541603520551659[319] = 0.0;
   out_1132541603520551659[320] = 0.0;
   out_1132541603520551659[321] = 0.0;
   out_1132541603520551659[322] = 0.0;
   out_1132541603520551659[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4710851946960034212) {
   out_4710851946960034212[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4710851946960034212[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4710851946960034212[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4710851946960034212[3] = dt*state[12] + state[3];
   out_4710851946960034212[4] = dt*state[13] + state[4];
   out_4710851946960034212[5] = dt*state[14] + state[5];
   out_4710851946960034212[6] = state[6];
   out_4710851946960034212[7] = state[7];
   out_4710851946960034212[8] = state[8];
   out_4710851946960034212[9] = state[9];
   out_4710851946960034212[10] = state[10];
   out_4710851946960034212[11] = state[11];
   out_4710851946960034212[12] = state[12];
   out_4710851946960034212[13] = state[13];
   out_4710851946960034212[14] = state[14];
   out_4710851946960034212[15] = state[15];
   out_4710851946960034212[16] = state[16];
   out_4710851946960034212[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8035530764887172818) {
   out_8035530764887172818[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8035530764887172818[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8035530764887172818[2] = 0;
   out_8035530764887172818[3] = 0;
   out_8035530764887172818[4] = 0;
   out_8035530764887172818[5] = 0;
   out_8035530764887172818[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8035530764887172818[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8035530764887172818[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8035530764887172818[9] = 0;
   out_8035530764887172818[10] = 0;
   out_8035530764887172818[11] = 0;
   out_8035530764887172818[12] = 0;
   out_8035530764887172818[13] = 0;
   out_8035530764887172818[14] = 0;
   out_8035530764887172818[15] = 0;
   out_8035530764887172818[16] = 0;
   out_8035530764887172818[17] = 0;
   out_8035530764887172818[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8035530764887172818[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8035530764887172818[20] = 0;
   out_8035530764887172818[21] = 0;
   out_8035530764887172818[22] = 0;
   out_8035530764887172818[23] = 0;
   out_8035530764887172818[24] = 0;
   out_8035530764887172818[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8035530764887172818[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8035530764887172818[27] = 0;
   out_8035530764887172818[28] = 0;
   out_8035530764887172818[29] = 0;
   out_8035530764887172818[30] = 0;
   out_8035530764887172818[31] = 0;
   out_8035530764887172818[32] = 0;
   out_8035530764887172818[33] = 0;
   out_8035530764887172818[34] = 0;
   out_8035530764887172818[35] = 0;
   out_8035530764887172818[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8035530764887172818[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8035530764887172818[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8035530764887172818[39] = 0;
   out_8035530764887172818[40] = 0;
   out_8035530764887172818[41] = 0;
   out_8035530764887172818[42] = 0;
   out_8035530764887172818[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8035530764887172818[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8035530764887172818[45] = 0;
   out_8035530764887172818[46] = 0;
   out_8035530764887172818[47] = 0;
   out_8035530764887172818[48] = 0;
   out_8035530764887172818[49] = 0;
   out_8035530764887172818[50] = 0;
   out_8035530764887172818[51] = 0;
   out_8035530764887172818[52] = 0;
   out_8035530764887172818[53] = 0;
   out_8035530764887172818[54] = 0;
   out_8035530764887172818[55] = 0;
   out_8035530764887172818[56] = 0;
   out_8035530764887172818[57] = 1;
   out_8035530764887172818[58] = 0;
   out_8035530764887172818[59] = 0;
   out_8035530764887172818[60] = 0;
   out_8035530764887172818[61] = 0;
   out_8035530764887172818[62] = 0;
   out_8035530764887172818[63] = 0;
   out_8035530764887172818[64] = 0;
   out_8035530764887172818[65] = 0;
   out_8035530764887172818[66] = dt;
   out_8035530764887172818[67] = 0;
   out_8035530764887172818[68] = 0;
   out_8035530764887172818[69] = 0;
   out_8035530764887172818[70] = 0;
   out_8035530764887172818[71] = 0;
   out_8035530764887172818[72] = 0;
   out_8035530764887172818[73] = 0;
   out_8035530764887172818[74] = 0;
   out_8035530764887172818[75] = 0;
   out_8035530764887172818[76] = 1;
   out_8035530764887172818[77] = 0;
   out_8035530764887172818[78] = 0;
   out_8035530764887172818[79] = 0;
   out_8035530764887172818[80] = 0;
   out_8035530764887172818[81] = 0;
   out_8035530764887172818[82] = 0;
   out_8035530764887172818[83] = 0;
   out_8035530764887172818[84] = 0;
   out_8035530764887172818[85] = dt;
   out_8035530764887172818[86] = 0;
   out_8035530764887172818[87] = 0;
   out_8035530764887172818[88] = 0;
   out_8035530764887172818[89] = 0;
   out_8035530764887172818[90] = 0;
   out_8035530764887172818[91] = 0;
   out_8035530764887172818[92] = 0;
   out_8035530764887172818[93] = 0;
   out_8035530764887172818[94] = 0;
   out_8035530764887172818[95] = 1;
   out_8035530764887172818[96] = 0;
   out_8035530764887172818[97] = 0;
   out_8035530764887172818[98] = 0;
   out_8035530764887172818[99] = 0;
   out_8035530764887172818[100] = 0;
   out_8035530764887172818[101] = 0;
   out_8035530764887172818[102] = 0;
   out_8035530764887172818[103] = 0;
   out_8035530764887172818[104] = dt;
   out_8035530764887172818[105] = 0;
   out_8035530764887172818[106] = 0;
   out_8035530764887172818[107] = 0;
   out_8035530764887172818[108] = 0;
   out_8035530764887172818[109] = 0;
   out_8035530764887172818[110] = 0;
   out_8035530764887172818[111] = 0;
   out_8035530764887172818[112] = 0;
   out_8035530764887172818[113] = 0;
   out_8035530764887172818[114] = 1;
   out_8035530764887172818[115] = 0;
   out_8035530764887172818[116] = 0;
   out_8035530764887172818[117] = 0;
   out_8035530764887172818[118] = 0;
   out_8035530764887172818[119] = 0;
   out_8035530764887172818[120] = 0;
   out_8035530764887172818[121] = 0;
   out_8035530764887172818[122] = 0;
   out_8035530764887172818[123] = 0;
   out_8035530764887172818[124] = 0;
   out_8035530764887172818[125] = 0;
   out_8035530764887172818[126] = 0;
   out_8035530764887172818[127] = 0;
   out_8035530764887172818[128] = 0;
   out_8035530764887172818[129] = 0;
   out_8035530764887172818[130] = 0;
   out_8035530764887172818[131] = 0;
   out_8035530764887172818[132] = 0;
   out_8035530764887172818[133] = 1;
   out_8035530764887172818[134] = 0;
   out_8035530764887172818[135] = 0;
   out_8035530764887172818[136] = 0;
   out_8035530764887172818[137] = 0;
   out_8035530764887172818[138] = 0;
   out_8035530764887172818[139] = 0;
   out_8035530764887172818[140] = 0;
   out_8035530764887172818[141] = 0;
   out_8035530764887172818[142] = 0;
   out_8035530764887172818[143] = 0;
   out_8035530764887172818[144] = 0;
   out_8035530764887172818[145] = 0;
   out_8035530764887172818[146] = 0;
   out_8035530764887172818[147] = 0;
   out_8035530764887172818[148] = 0;
   out_8035530764887172818[149] = 0;
   out_8035530764887172818[150] = 0;
   out_8035530764887172818[151] = 0;
   out_8035530764887172818[152] = 1;
   out_8035530764887172818[153] = 0;
   out_8035530764887172818[154] = 0;
   out_8035530764887172818[155] = 0;
   out_8035530764887172818[156] = 0;
   out_8035530764887172818[157] = 0;
   out_8035530764887172818[158] = 0;
   out_8035530764887172818[159] = 0;
   out_8035530764887172818[160] = 0;
   out_8035530764887172818[161] = 0;
   out_8035530764887172818[162] = 0;
   out_8035530764887172818[163] = 0;
   out_8035530764887172818[164] = 0;
   out_8035530764887172818[165] = 0;
   out_8035530764887172818[166] = 0;
   out_8035530764887172818[167] = 0;
   out_8035530764887172818[168] = 0;
   out_8035530764887172818[169] = 0;
   out_8035530764887172818[170] = 0;
   out_8035530764887172818[171] = 1;
   out_8035530764887172818[172] = 0;
   out_8035530764887172818[173] = 0;
   out_8035530764887172818[174] = 0;
   out_8035530764887172818[175] = 0;
   out_8035530764887172818[176] = 0;
   out_8035530764887172818[177] = 0;
   out_8035530764887172818[178] = 0;
   out_8035530764887172818[179] = 0;
   out_8035530764887172818[180] = 0;
   out_8035530764887172818[181] = 0;
   out_8035530764887172818[182] = 0;
   out_8035530764887172818[183] = 0;
   out_8035530764887172818[184] = 0;
   out_8035530764887172818[185] = 0;
   out_8035530764887172818[186] = 0;
   out_8035530764887172818[187] = 0;
   out_8035530764887172818[188] = 0;
   out_8035530764887172818[189] = 0;
   out_8035530764887172818[190] = 1;
   out_8035530764887172818[191] = 0;
   out_8035530764887172818[192] = 0;
   out_8035530764887172818[193] = 0;
   out_8035530764887172818[194] = 0;
   out_8035530764887172818[195] = 0;
   out_8035530764887172818[196] = 0;
   out_8035530764887172818[197] = 0;
   out_8035530764887172818[198] = 0;
   out_8035530764887172818[199] = 0;
   out_8035530764887172818[200] = 0;
   out_8035530764887172818[201] = 0;
   out_8035530764887172818[202] = 0;
   out_8035530764887172818[203] = 0;
   out_8035530764887172818[204] = 0;
   out_8035530764887172818[205] = 0;
   out_8035530764887172818[206] = 0;
   out_8035530764887172818[207] = 0;
   out_8035530764887172818[208] = 0;
   out_8035530764887172818[209] = 1;
   out_8035530764887172818[210] = 0;
   out_8035530764887172818[211] = 0;
   out_8035530764887172818[212] = 0;
   out_8035530764887172818[213] = 0;
   out_8035530764887172818[214] = 0;
   out_8035530764887172818[215] = 0;
   out_8035530764887172818[216] = 0;
   out_8035530764887172818[217] = 0;
   out_8035530764887172818[218] = 0;
   out_8035530764887172818[219] = 0;
   out_8035530764887172818[220] = 0;
   out_8035530764887172818[221] = 0;
   out_8035530764887172818[222] = 0;
   out_8035530764887172818[223] = 0;
   out_8035530764887172818[224] = 0;
   out_8035530764887172818[225] = 0;
   out_8035530764887172818[226] = 0;
   out_8035530764887172818[227] = 0;
   out_8035530764887172818[228] = 1;
   out_8035530764887172818[229] = 0;
   out_8035530764887172818[230] = 0;
   out_8035530764887172818[231] = 0;
   out_8035530764887172818[232] = 0;
   out_8035530764887172818[233] = 0;
   out_8035530764887172818[234] = 0;
   out_8035530764887172818[235] = 0;
   out_8035530764887172818[236] = 0;
   out_8035530764887172818[237] = 0;
   out_8035530764887172818[238] = 0;
   out_8035530764887172818[239] = 0;
   out_8035530764887172818[240] = 0;
   out_8035530764887172818[241] = 0;
   out_8035530764887172818[242] = 0;
   out_8035530764887172818[243] = 0;
   out_8035530764887172818[244] = 0;
   out_8035530764887172818[245] = 0;
   out_8035530764887172818[246] = 0;
   out_8035530764887172818[247] = 1;
   out_8035530764887172818[248] = 0;
   out_8035530764887172818[249] = 0;
   out_8035530764887172818[250] = 0;
   out_8035530764887172818[251] = 0;
   out_8035530764887172818[252] = 0;
   out_8035530764887172818[253] = 0;
   out_8035530764887172818[254] = 0;
   out_8035530764887172818[255] = 0;
   out_8035530764887172818[256] = 0;
   out_8035530764887172818[257] = 0;
   out_8035530764887172818[258] = 0;
   out_8035530764887172818[259] = 0;
   out_8035530764887172818[260] = 0;
   out_8035530764887172818[261] = 0;
   out_8035530764887172818[262] = 0;
   out_8035530764887172818[263] = 0;
   out_8035530764887172818[264] = 0;
   out_8035530764887172818[265] = 0;
   out_8035530764887172818[266] = 1;
   out_8035530764887172818[267] = 0;
   out_8035530764887172818[268] = 0;
   out_8035530764887172818[269] = 0;
   out_8035530764887172818[270] = 0;
   out_8035530764887172818[271] = 0;
   out_8035530764887172818[272] = 0;
   out_8035530764887172818[273] = 0;
   out_8035530764887172818[274] = 0;
   out_8035530764887172818[275] = 0;
   out_8035530764887172818[276] = 0;
   out_8035530764887172818[277] = 0;
   out_8035530764887172818[278] = 0;
   out_8035530764887172818[279] = 0;
   out_8035530764887172818[280] = 0;
   out_8035530764887172818[281] = 0;
   out_8035530764887172818[282] = 0;
   out_8035530764887172818[283] = 0;
   out_8035530764887172818[284] = 0;
   out_8035530764887172818[285] = 1;
   out_8035530764887172818[286] = 0;
   out_8035530764887172818[287] = 0;
   out_8035530764887172818[288] = 0;
   out_8035530764887172818[289] = 0;
   out_8035530764887172818[290] = 0;
   out_8035530764887172818[291] = 0;
   out_8035530764887172818[292] = 0;
   out_8035530764887172818[293] = 0;
   out_8035530764887172818[294] = 0;
   out_8035530764887172818[295] = 0;
   out_8035530764887172818[296] = 0;
   out_8035530764887172818[297] = 0;
   out_8035530764887172818[298] = 0;
   out_8035530764887172818[299] = 0;
   out_8035530764887172818[300] = 0;
   out_8035530764887172818[301] = 0;
   out_8035530764887172818[302] = 0;
   out_8035530764887172818[303] = 0;
   out_8035530764887172818[304] = 1;
   out_8035530764887172818[305] = 0;
   out_8035530764887172818[306] = 0;
   out_8035530764887172818[307] = 0;
   out_8035530764887172818[308] = 0;
   out_8035530764887172818[309] = 0;
   out_8035530764887172818[310] = 0;
   out_8035530764887172818[311] = 0;
   out_8035530764887172818[312] = 0;
   out_8035530764887172818[313] = 0;
   out_8035530764887172818[314] = 0;
   out_8035530764887172818[315] = 0;
   out_8035530764887172818[316] = 0;
   out_8035530764887172818[317] = 0;
   out_8035530764887172818[318] = 0;
   out_8035530764887172818[319] = 0;
   out_8035530764887172818[320] = 0;
   out_8035530764887172818[321] = 0;
   out_8035530764887172818[322] = 0;
   out_8035530764887172818[323] = 1;
}
void h_4(double *state, double *unused, double *out_5758439189671492522) {
   out_5758439189671492522[0] = state[6] + state[9];
   out_5758439189671492522[1] = state[7] + state[10];
   out_5758439189671492522[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5653546144624826768) {
   out_5653546144624826768[0] = 0;
   out_5653546144624826768[1] = 0;
   out_5653546144624826768[2] = 0;
   out_5653546144624826768[3] = 0;
   out_5653546144624826768[4] = 0;
   out_5653546144624826768[5] = 0;
   out_5653546144624826768[6] = 1;
   out_5653546144624826768[7] = 0;
   out_5653546144624826768[8] = 0;
   out_5653546144624826768[9] = 1;
   out_5653546144624826768[10] = 0;
   out_5653546144624826768[11] = 0;
   out_5653546144624826768[12] = 0;
   out_5653546144624826768[13] = 0;
   out_5653546144624826768[14] = 0;
   out_5653546144624826768[15] = 0;
   out_5653546144624826768[16] = 0;
   out_5653546144624826768[17] = 0;
   out_5653546144624826768[18] = 0;
   out_5653546144624826768[19] = 0;
   out_5653546144624826768[20] = 0;
   out_5653546144624826768[21] = 0;
   out_5653546144624826768[22] = 0;
   out_5653546144624826768[23] = 0;
   out_5653546144624826768[24] = 0;
   out_5653546144624826768[25] = 1;
   out_5653546144624826768[26] = 0;
   out_5653546144624826768[27] = 0;
   out_5653546144624826768[28] = 1;
   out_5653546144624826768[29] = 0;
   out_5653546144624826768[30] = 0;
   out_5653546144624826768[31] = 0;
   out_5653546144624826768[32] = 0;
   out_5653546144624826768[33] = 0;
   out_5653546144624826768[34] = 0;
   out_5653546144624826768[35] = 0;
   out_5653546144624826768[36] = 0;
   out_5653546144624826768[37] = 0;
   out_5653546144624826768[38] = 0;
   out_5653546144624826768[39] = 0;
   out_5653546144624826768[40] = 0;
   out_5653546144624826768[41] = 0;
   out_5653546144624826768[42] = 0;
   out_5653546144624826768[43] = 0;
   out_5653546144624826768[44] = 1;
   out_5653546144624826768[45] = 0;
   out_5653546144624826768[46] = 0;
   out_5653546144624826768[47] = 1;
   out_5653546144624826768[48] = 0;
   out_5653546144624826768[49] = 0;
   out_5653546144624826768[50] = 0;
   out_5653546144624826768[51] = 0;
   out_5653546144624826768[52] = 0;
   out_5653546144624826768[53] = 0;
}
void h_10(double *state, double *unused, double *out_4438741120644189837) {
   out_4438741120644189837[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4438741120644189837[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4438741120644189837[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4815704039696511932) {
   out_4815704039696511932[0] = 0;
   out_4815704039696511932[1] = 9.8100000000000005*cos(state[1]);
   out_4815704039696511932[2] = 0;
   out_4815704039696511932[3] = 0;
   out_4815704039696511932[4] = -state[8];
   out_4815704039696511932[5] = state[7];
   out_4815704039696511932[6] = 0;
   out_4815704039696511932[7] = state[5];
   out_4815704039696511932[8] = -state[4];
   out_4815704039696511932[9] = 0;
   out_4815704039696511932[10] = 0;
   out_4815704039696511932[11] = 0;
   out_4815704039696511932[12] = 1;
   out_4815704039696511932[13] = 0;
   out_4815704039696511932[14] = 0;
   out_4815704039696511932[15] = 1;
   out_4815704039696511932[16] = 0;
   out_4815704039696511932[17] = 0;
   out_4815704039696511932[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4815704039696511932[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4815704039696511932[20] = 0;
   out_4815704039696511932[21] = state[8];
   out_4815704039696511932[22] = 0;
   out_4815704039696511932[23] = -state[6];
   out_4815704039696511932[24] = -state[5];
   out_4815704039696511932[25] = 0;
   out_4815704039696511932[26] = state[3];
   out_4815704039696511932[27] = 0;
   out_4815704039696511932[28] = 0;
   out_4815704039696511932[29] = 0;
   out_4815704039696511932[30] = 0;
   out_4815704039696511932[31] = 1;
   out_4815704039696511932[32] = 0;
   out_4815704039696511932[33] = 0;
   out_4815704039696511932[34] = 1;
   out_4815704039696511932[35] = 0;
   out_4815704039696511932[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4815704039696511932[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4815704039696511932[38] = 0;
   out_4815704039696511932[39] = -state[7];
   out_4815704039696511932[40] = state[6];
   out_4815704039696511932[41] = 0;
   out_4815704039696511932[42] = state[4];
   out_4815704039696511932[43] = -state[3];
   out_4815704039696511932[44] = 0;
   out_4815704039696511932[45] = 0;
   out_4815704039696511932[46] = 0;
   out_4815704039696511932[47] = 0;
   out_4815704039696511932[48] = 0;
   out_4815704039696511932[49] = 0;
   out_4815704039696511932[50] = 1;
   out_4815704039696511932[51] = 0;
   out_4815704039696511932[52] = 0;
   out_4815704039696511932[53] = 1;
}
void h_13(double *state, double *unused, double *out_1473597949739903729) {
   out_1473597949739903729[0] = state[3];
   out_1473597949739903729[1] = state[4];
   out_1473597949739903729[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1957085063691874161) {
   out_1957085063691874161[0] = 0;
   out_1957085063691874161[1] = 0;
   out_1957085063691874161[2] = 0;
   out_1957085063691874161[3] = 1;
   out_1957085063691874161[4] = 0;
   out_1957085063691874161[5] = 0;
   out_1957085063691874161[6] = 0;
   out_1957085063691874161[7] = 0;
   out_1957085063691874161[8] = 0;
   out_1957085063691874161[9] = 0;
   out_1957085063691874161[10] = 0;
   out_1957085063691874161[11] = 0;
   out_1957085063691874161[12] = 0;
   out_1957085063691874161[13] = 0;
   out_1957085063691874161[14] = 0;
   out_1957085063691874161[15] = 0;
   out_1957085063691874161[16] = 0;
   out_1957085063691874161[17] = 0;
   out_1957085063691874161[18] = 0;
   out_1957085063691874161[19] = 0;
   out_1957085063691874161[20] = 0;
   out_1957085063691874161[21] = 0;
   out_1957085063691874161[22] = 1;
   out_1957085063691874161[23] = 0;
   out_1957085063691874161[24] = 0;
   out_1957085063691874161[25] = 0;
   out_1957085063691874161[26] = 0;
   out_1957085063691874161[27] = 0;
   out_1957085063691874161[28] = 0;
   out_1957085063691874161[29] = 0;
   out_1957085063691874161[30] = 0;
   out_1957085063691874161[31] = 0;
   out_1957085063691874161[32] = 0;
   out_1957085063691874161[33] = 0;
   out_1957085063691874161[34] = 0;
   out_1957085063691874161[35] = 0;
   out_1957085063691874161[36] = 0;
   out_1957085063691874161[37] = 0;
   out_1957085063691874161[38] = 0;
   out_1957085063691874161[39] = 0;
   out_1957085063691874161[40] = 0;
   out_1957085063691874161[41] = 1;
   out_1957085063691874161[42] = 0;
   out_1957085063691874161[43] = 0;
   out_1957085063691874161[44] = 0;
   out_1957085063691874161[45] = 0;
   out_1957085063691874161[46] = 0;
   out_1957085063691874161[47] = 0;
   out_1957085063691874161[48] = 0;
   out_1957085063691874161[49] = 0;
   out_1957085063691874161[50] = 0;
   out_1957085063691874161[51] = 0;
   out_1957085063691874161[52] = 0;
   out_1957085063691874161[53] = 0;
}
void h_14(double *state, double *unused, double *out_3842475002178970014) {
   out_3842475002178970014[0] = state[6];
   out_3842475002178970014[1] = state[7];
   out_3842475002178970014[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8736334576920199064) {
   out_8736334576920199064[0] = 0;
   out_8736334576920199064[1] = 0;
   out_8736334576920199064[2] = 0;
   out_8736334576920199064[3] = 0;
   out_8736334576920199064[4] = 0;
   out_8736334576920199064[5] = 0;
   out_8736334576920199064[6] = 1;
   out_8736334576920199064[7] = 0;
   out_8736334576920199064[8] = 0;
   out_8736334576920199064[9] = 0;
   out_8736334576920199064[10] = 0;
   out_8736334576920199064[11] = 0;
   out_8736334576920199064[12] = 0;
   out_8736334576920199064[13] = 0;
   out_8736334576920199064[14] = 0;
   out_8736334576920199064[15] = 0;
   out_8736334576920199064[16] = 0;
   out_8736334576920199064[17] = 0;
   out_8736334576920199064[18] = 0;
   out_8736334576920199064[19] = 0;
   out_8736334576920199064[20] = 0;
   out_8736334576920199064[21] = 0;
   out_8736334576920199064[22] = 0;
   out_8736334576920199064[23] = 0;
   out_8736334576920199064[24] = 0;
   out_8736334576920199064[25] = 1;
   out_8736334576920199064[26] = 0;
   out_8736334576920199064[27] = 0;
   out_8736334576920199064[28] = 0;
   out_8736334576920199064[29] = 0;
   out_8736334576920199064[30] = 0;
   out_8736334576920199064[31] = 0;
   out_8736334576920199064[32] = 0;
   out_8736334576920199064[33] = 0;
   out_8736334576920199064[34] = 0;
   out_8736334576920199064[35] = 0;
   out_8736334576920199064[36] = 0;
   out_8736334576920199064[37] = 0;
   out_8736334576920199064[38] = 0;
   out_8736334576920199064[39] = 0;
   out_8736334576920199064[40] = 0;
   out_8736334576920199064[41] = 0;
   out_8736334576920199064[42] = 0;
   out_8736334576920199064[43] = 0;
   out_8736334576920199064[44] = 1;
   out_8736334576920199064[45] = 0;
   out_8736334576920199064[46] = 0;
   out_8736334576920199064[47] = 0;
   out_8736334576920199064[48] = 0;
   out_8736334576920199064[49] = 0;
   out_8736334576920199064[50] = 0;
   out_8736334576920199064[51] = 0;
   out_8736334576920199064[52] = 0;
   out_8736334576920199064[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4788240677246511833) {
  err_fun(nom_x, delta_x, out_4788240677246511833);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5975192517926128029) {
  inv_err_fun(nom_x, true_x, out_5975192517926128029);
}
void pose_H_mod_fun(double *state, double *out_1132541603520551659) {
  H_mod_fun(state, out_1132541603520551659);
}
void pose_f_fun(double *state, double dt, double *out_4710851946960034212) {
  f_fun(state,  dt, out_4710851946960034212);
}
void pose_F_fun(double *state, double dt, double *out_8035530764887172818) {
  F_fun(state,  dt, out_8035530764887172818);
}
void pose_h_4(double *state, double *unused, double *out_5758439189671492522) {
  h_4(state, unused, out_5758439189671492522);
}
void pose_H_4(double *state, double *unused, double *out_5653546144624826768) {
  H_4(state, unused, out_5653546144624826768);
}
void pose_h_10(double *state, double *unused, double *out_4438741120644189837) {
  h_10(state, unused, out_4438741120644189837);
}
void pose_H_10(double *state, double *unused, double *out_4815704039696511932) {
  H_10(state, unused, out_4815704039696511932);
}
void pose_h_13(double *state, double *unused, double *out_1473597949739903729) {
  h_13(state, unused, out_1473597949739903729);
}
void pose_H_13(double *state, double *unused, double *out_1957085063691874161) {
  H_13(state, unused, out_1957085063691874161);
}
void pose_h_14(double *state, double *unused, double *out_3842475002178970014) {
  h_14(state, unused, out_3842475002178970014);
}
void pose_H_14(double *state, double *unused, double *out_8736334576920199064) {
  H_14(state, unused, out_8736334576920199064);
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
