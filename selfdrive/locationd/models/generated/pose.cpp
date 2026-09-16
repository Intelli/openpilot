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
void err_fun(double *nom_x, double *delta_x, double *out_2325015377156513737) {
   out_2325015377156513737[0] = delta_x[0] + nom_x[0];
   out_2325015377156513737[1] = delta_x[1] + nom_x[1];
   out_2325015377156513737[2] = delta_x[2] + nom_x[2];
   out_2325015377156513737[3] = delta_x[3] + nom_x[3];
   out_2325015377156513737[4] = delta_x[4] + nom_x[4];
   out_2325015377156513737[5] = delta_x[5] + nom_x[5];
   out_2325015377156513737[6] = delta_x[6] + nom_x[6];
   out_2325015377156513737[7] = delta_x[7] + nom_x[7];
   out_2325015377156513737[8] = delta_x[8] + nom_x[8];
   out_2325015377156513737[9] = delta_x[9] + nom_x[9];
   out_2325015377156513737[10] = delta_x[10] + nom_x[10];
   out_2325015377156513737[11] = delta_x[11] + nom_x[11];
   out_2325015377156513737[12] = delta_x[12] + nom_x[12];
   out_2325015377156513737[13] = delta_x[13] + nom_x[13];
   out_2325015377156513737[14] = delta_x[14] + nom_x[14];
   out_2325015377156513737[15] = delta_x[15] + nom_x[15];
   out_2325015377156513737[16] = delta_x[16] + nom_x[16];
   out_2325015377156513737[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6324847366348989757) {
   out_6324847366348989757[0] = -nom_x[0] + true_x[0];
   out_6324847366348989757[1] = -nom_x[1] + true_x[1];
   out_6324847366348989757[2] = -nom_x[2] + true_x[2];
   out_6324847366348989757[3] = -nom_x[3] + true_x[3];
   out_6324847366348989757[4] = -nom_x[4] + true_x[4];
   out_6324847366348989757[5] = -nom_x[5] + true_x[5];
   out_6324847366348989757[6] = -nom_x[6] + true_x[6];
   out_6324847366348989757[7] = -nom_x[7] + true_x[7];
   out_6324847366348989757[8] = -nom_x[8] + true_x[8];
   out_6324847366348989757[9] = -nom_x[9] + true_x[9];
   out_6324847366348989757[10] = -nom_x[10] + true_x[10];
   out_6324847366348989757[11] = -nom_x[11] + true_x[11];
   out_6324847366348989757[12] = -nom_x[12] + true_x[12];
   out_6324847366348989757[13] = -nom_x[13] + true_x[13];
   out_6324847366348989757[14] = -nom_x[14] + true_x[14];
   out_6324847366348989757[15] = -nom_x[15] + true_x[15];
   out_6324847366348989757[16] = -nom_x[16] + true_x[16];
   out_6324847366348989757[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8008080077202602510) {
   out_8008080077202602510[0] = 1.0;
   out_8008080077202602510[1] = 0.0;
   out_8008080077202602510[2] = 0.0;
   out_8008080077202602510[3] = 0.0;
   out_8008080077202602510[4] = 0.0;
   out_8008080077202602510[5] = 0.0;
   out_8008080077202602510[6] = 0.0;
   out_8008080077202602510[7] = 0.0;
   out_8008080077202602510[8] = 0.0;
   out_8008080077202602510[9] = 0.0;
   out_8008080077202602510[10] = 0.0;
   out_8008080077202602510[11] = 0.0;
   out_8008080077202602510[12] = 0.0;
   out_8008080077202602510[13] = 0.0;
   out_8008080077202602510[14] = 0.0;
   out_8008080077202602510[15] = 0.0;
   out_8008080077202602510[16] = 0.0;
   out_8008080077202602510[17] = 0.0;
   out_8008080077202602510[18] = 0.0;
   out_8008080077202602510[19] = 1.0;
   out_8008080077202602510[20] = 0.0;
   out_8008080077202602510[21] = 0.0;
   out_8008080077202602510[22] = 0.0;
   out_8008080077202602510[23] = 0.0;
   out_8008080077202602510[24] = 0.0;
   out_8008080077202602510[25] = 0.0;
   out_8008080077202602510[26] = 0.0;
   out_8008080077202602510[27] = 0.0;
   out_8008080077202602510[28] = 0.0;
   out_8008080077202602510[29] = 0.0;
   out_8008080077202602510[30] = 0.0;
   out_8008080077202602510[31] = 0.0;
   out_8008080077202602510[32] = 0.0;
   out_8008080077202602510[33] = 0.0;
   out_8008080077202602510[34] = 0.0;
   out_8008080077202602510[35] = 0.0;
   out_8008080077202602510[36] = 0.0;
   out_8008080077202602510[37] = 0.0;
   out_8008080077202602510[38] = 1.0;
   out_8008080077202602510[39] = 0.0;
   out_8008080077202602510[40] = 0.0;
   out_8008080077202602510[41] = 0.0;
   out_8008080077202602510[42] = 0.0;
   out_8008080077202602510[43] = 0.0;
   out_8008080077202602510[44] = 0.0;
   out_8008080077202602510[45] = 0.0;
   out_8008080077202602510[46] = 0.0;
   out_8008080077202602510[47] = 0.0;
   out_8008080077202602510[48] = 0.0;
   out_8008080077202602510[49] = 0.0;
   out_8008080077202602510[50] = 0.0;
   out_8008080077202602510[51] = 0.0;
   out_8008080077202602510[52] = 0.0;
   out_8008080077202602510[53] = 0.0;
   out_8008080077202602510[54] = 0.0;
   out_8008080077202602510[55] = 0.0;
   out_8008080077202602510[56] = 0.0;
   out_8008080077202602510[57] = 1.0;
   out_8008080077202602510[58] = 0.0;
   out_8008080077202602510[59] = 0.0;
   out_8008080077202602510[60] = 0.0;
   out_8008080077202602510[61] = 0.0;
   out_8008080077202602510[62] = 0.0;
   out_8008080077202602510[63] = 0.0;
   out_8008080077202602510[64] = 0.0;
   out_8008080077202602510[65] = 0.0;
   out_8008080077202602510[66] = 0.0;
   out_8008080077202602510[67] = 0.0;
   out_8008080077202602510[68] = 0.0;
   out_8008080077202602510[69] = 0.0;
   out_8008080077202602510[70] = 0.0;
   out_8008080077202602510[71] = 0.0;
   out_8008080077202602510[72] = 0.0;
   out_8008080077202602510[73] = 0.0;
   out_8008080077202602510[74] = 0.0;
   out_8008080077202602510[75] = 0.0;
   out_8008080077202602510[76] = 1.0;
   out_8008080077202602510[77] = 0.0;
   out_8008080077202602510[78] = 0.0;
   out_8008080077202602510[79] = 0.0;
   out_8008080077202602510[80] = 0.0;
   out_8008080077202602510[81] = 0.0;
   out_8008080077202602510[82] = 0.0;
   out_8008080077202602510[83] = 0.0;
   out_8008080077202602510[84] = 0.0;
   out_8008080077202602510[85] = 0.0;
   out_8008080077202602510[86] = 0.0;
   out_8008080077202602510[87] = 0.0;
   out_8008080077202602510[88] = 0.0;
   out_8008080077202602510[89] = 0.0;
   out_8008080077202602510[90] = 0.0;
   out_8008080077202602510[91] = 0.0;
   out_8008080077202602510[92] = 0.0;
   out_8008080077202602510[93] = 0.0;
   out_8008080077202602510[94] = 0.0;
   out_8008080077202602510[95] = 1.0;
   out_8008080077202602510[96] = 0.0;
   out_8008080077202602510[97] = 0.0;
   out_8008080077202602510[98] = 0.0;
   out_8008080077202602510[99] = 0.0;
   out_8008080077202602510[100] = 0.0;
   out_8008080077202602510[101] = 0.0;
   out_8008080077202602510[102] = 0.0;
   out_8008080077202602510[103] = 0.0;
   out_8008080077202602510[104] = 0.0;
   out_8008080077202602510[105] = 0.0;
   out_8008080077202602510[106] = 0.0;
   out_8008080077202602510[107] = 0.0;
   out_8008080077202602510[108] = 0.0;
   out_8008080077202602510[109] = 0.0;
   out_8008080077202602510[110] = 0.0;
   out_8008080077202602510[111] = 0.0;
   out_8008080077202602510[112] = 0.0;
   out_8008080077202602510[113] = 0.0;
   out_8008080077202602510[114] = 1.0;
   out_8008080077202602510[115] = 0.0;
   out_8008080077202602510[116] = 0.0;
   out_8008080077202602510[117] = 0.0;
   out_8008080077202602510[118] = 0.0;
   out_8008080077202602510[119] = 0.0;
   out_8008080077202602510[120] = 0.0;
   out_8008080077202602510[121] = 0.0;
   out_8008080077202602510[122] = 0.0;
   out_8008080077202602510[123] = 0.0;
   out_8008080077202602510[124] = 0.0;
   out_8008080077202602510[125] = 0.0;
   out_8008080077202602510[126] = 0.0;
   out_8008080077202602510[127] = 0.0;
   out_8008080077202602510[128] = 0.0;
   out_8008080077202602510[129] = 0.0;
   out_8008080077202602510[130] = 0.0;
   out_8008080077202602510[131] = 0.0;
   out_8008080077202602510[132] = 0.0;
   out_8008080077202602510[133] = 1.0;
   out_8008080077202602510[134] = 0.0;
   out_8008080077202602510[135] = 0.0;
   out_8008080077202602510[136] = 0.0;
   out_8008080077202602510[137] = 0.0;
   out_8008080077202602510[138] = 0.0;
   out_8008080077202602510[139] = 0.0;
   out_8008080077202602510[140] = 0.0;
   out_8008080077202602510[141] = 0.0;
   out_8008080077202602510[142] = 0.0;
   out_8008080077202602510[143] = 0.0;
   out_8008080077202602510[144] = 0.0;
   out_8008080077202602510[145] = 0.0;
   out_8008080077202602510[146] = 0.0;
   out_8008080077202602510[147] = 0.0;
   out_8008080077202602510[148] = 0.0;
   out_8008080077202602510[149] = 0.0;
   out_8008080077202602510[150] = 0.0;
   out_8008080077202602510[151] = 0.0;
   out_8008080077202602510[152] = 1.0;
   out_8008080077202602510[153] = 0.0;
   out_8008080077202602510[154] = 0.0;
   out_8008080077202602510[155] = 0.0;
   out_8008080077202602510[156] = 0.0;
   out_8008080077202602510[157] = 0.0;
   out_8008080077202602510[158] = 0.0;
   out_8008080077202602510[159] = 0.0;
   out_8008080077202602510[160] = 0.0;
   out_8008080077202602510[161] = 0.0;
   out_8008080077202602510[162] = 0.0;
   out_8008080077202602510[163] = 0.0;
   out_8008080077202602510[164] = 0.0;
   out_8008080077202602510[165] = 0.0;
   out_8008080077202602510[166] = 0.0;
   out_8008080077202602510[167] = 0.0;
   out_8008080077202602510[168] = 0.0;
   out_8008080077202602510[169] = 0.0;
   out_8008080077202602510[170] = 0.0;
   out_8008080077202602510[171] = 1.0;
   out_8008080077202602510[172] = 0.0;
   out_8008080077202602510[173] = 0.0;
   out_8008080077202602510[174] = 0.0;
   out_8008080077202602510[175] = 0.0;
   out_8008080077202602510[176] = 0.0;
   out_8008080077202602510[177] = 0.0;
   out_8008080077202602510[178] = 0.0;
   out_8008080077202602510[179] = 0.0;
   out_8008080077202602510[180] = 0.0;
   out_8008080077202602510[181] = 0.0;
   out_8008080077202602510[182] = 0.0;
   out_8008080077202602510[183] = 0.0;
   out_8008080077202602510[184] = 0.0;
   out_8008080077202602510[185] = 0.0;
   out_8008080077202602510[186] = 0.0;
   out_8008080077202602510[187] = 0.0;
   out_8008080077202602510[188] = 0.0;
   out_8008080077202602510[189] = 0.0;
   out_8008080077202602510[190] = 1.0;
   out_8008080077202602510[191] = 0.0;
   out_8008080077202602510[192] = 0.0;
   out_8008080077202602510[193] = 0.0;
   out_8008080077202602510[194] = 0.0;
   out_8008080077202602510[195] = 0.0;
   out_8008080077202602510[196] = 0.0;
   out_8008080077202602510[197] = 0.0;
   out_8008080077202602510[198] = 0.0;
   out_8008080077202602510[199] = 0.0;
   out_8008080077202602510[200] = 0.0;
   out_8008080077202602510[201] = 0.0;
   out_8008080077202602510[202] = 0.0;
   out_8008080077202602510[203] = 0.0;
   out_8008080077202602510[204] = 0.0;
   out_8008080077202602510[205] = 0.0;
   out_8008080077202602510[206] = 0.0;
   out_8008080077202602510[207] = 0.0;
   out_8008080077202602510[208] = 0.0;
   out_8008080077202602510[209] = 1.0;
   out_8008080077202602510[210] = 0.0;
   out_8008080077202602510[211] = 0.0;
   out_8008080077202602510[212] = 0.0;
   out_8008080077202602510[213] = 0.0;
   out_8008080077202602510[214] = 0.0;
   out_8008080077202602510[215] = 0.0;
   out_8008080077202602510[216] = 0.0;
   out_8008080077202602510[217] = 0.0;
   out_8008080077202602510[218] = 0.0;
   out_8008080077202602510[219] = 0.0;
   out_8008080077202602510[220] = 0.0;
   out_8008080077202602510[221] = 0.0;
   out_8008080077202602510[222] = 0.0;
   out_8008080077202602510[223] = 0.0;
   out_8008080077202602510[224] = 0.0;
   out_8008080077202602510[225] = 0.0;
   out_8008080077202602510[226] = 0.0;
   out_8008080077202602510[227] = 0.0;
   out_8008080077202602510[228] = 1.0;
   out_8008080077202602510[229] = 0.0;
   out_8008080077202602510[230] = 0.0;
   out_8008080077202602510[231] = 0.0;
   out_8008080077202602510[232] = 0.0;
   out_8008080077202602510[233] = 0.0;
   out_8008080077202602510[234] = 0.0;
   out_8008080077202602510[235] = 0.0;
   out_8008080077202602510[236] = 0.0;
   out_8008080077202602510[237] = 0.0;
   out_8008080077202602510[238] = 0.0;
   out_8008080077202602510[239] = 0.0;
   out_8008080077202602510[240] = 0.0;
   out_8008080077202602510[241] = 0.0;
   out_8008080077202602510[242] = 0.0;
   out_8008080077202602510[243] = 0.0;
   out_8008080077202602510[244] = 0.0;
   out_8008080077202602510[245] = 0.0;
   out_8008080077202602510[246] = 0.0;
   out_8008080077202602510[247] = 1.0;
   out_8008080077202602510[248] = 0.0;
   out_8008080077202602510[249] = 0.0;
   out_8008080077202602510[250] = 0.0;
   out_8008080077202602510[251] = 0.0;
   out_8008080077202602510[252] = 0.0;
   out_8008080077202602510[253] = 0.0;
   out_8008080077202602510[254] = 0.0;
   out_8008080077202602510[255] = 0.0;
   out_8008080077202602510[256] = 0.0;
   out_8008080077202602510[257] = 0.0;
   out_8008080077202602510[258] = 0.0;
   out_8008080077202602510[259] = 0.0;
   out_8008080077202602510[260] = 0.0;
   out_8008080077202602510[261] = 0.0;
   out_8008080077202602510[262] = 0.0;
   out_8008080077202602510[263] = 0.0;
   out_8008080077202602510[264] = 0.0;
   out_8008080077202602510[265] = 0.0;
   out_8008080077202602510[266] = 1.0;
   out_8008080077202602510[267] = 0.0;
   out_8008080077202602510[268] = 0.0;
   out_8008080077202602510[269] = 0.0;
   out_8008080077202602510[270] = 0.0;
   out_8008080077202602510[271] = 0.0;
   out_8008080077202602510[272] = 0.0;
   out_8008080077202602510[273] = 0.0;
   out_8008080077202602510[274] = 0.0;
   out_8008080077202602510[275] = 0.0;
   out_8008080077202602510[276] = 0.0;
   out_8008080077202602510[277] = 0.0;
   out_8008080077202602510[278] = 0.0;
   out_8008080077202602510[279] = 0.0;
   out_8008080077202602510[280] = 0.0;
   out_8008080077202602510[281] = 0.0;
   out_8008080077202602510[282] = 0.0;
   out_8008080077202602510[283] = 0.0;
   out_8008080077202602510[284] = 0.0;
   out_8008080077202602510[285] = 1.0;
   out_8008080077202602510[286] = 0.0;
   out_8008080077202602510[287] = 0.0;
   out_8008080077202602510[288] = 0.0;
   out_8008080077202602510[289] = 0.0;
   out_8008080077202602510[290] = 0.0;
   out_8008080077202602510[291] = 0.0;
   out_8008080077202602510[292] = 0.0;
   out_8008080077202602510[293] = 0.0;
   out_8008080077202602510[294] = 0.0;
   out_8008080077202602510[295] = 0.0;
   out_8008080077202602510[296] = 0.0;
   out_8008080077202602510[297] = 0.0;
   out_8008080077202602510[298] = 0.0;
   out_8008080077202602510[299] = 0.0;
   out_8008080077202602510[300] = 0.0;
   out_8008080077202602510[301] = 0.0;
   out_8008080077202602510[302] = 0.0;
   out_8008080077202602510[303] = 0.0;
   out_8008080077202602510[304] = 1.0;
   out_8008080077202602510[305] = 0.0;
   out_8008080077202602510[306] = 0.0;
   out_8008080077202602510[307] = 0.0;
   out_8008080077202602510[308] = 0.0;
   out_8008080077202602510[309] = 0.0;
   out_8008080077202602510[310] = 0.0;
   out_8008080077202602510[311] = 0.0;
   out_8008080077202602510[312] = 0.0;
   out_8008080077202602510[313] = 0.0;
   out_8008080077202602510[314] = 0.0;
   out_8008080077202602510[315] = 0.0;
   out_8008080077202602510[316] = 0.0;
   out_8008080077202602510[317] = 0.0;
   out_8008080077202602510[318] = 0.0;
   out_8008080077202602510[319] = 0.0;
   out_8008080077202602510[320] = 0.0;
   out_8008080077202602510[321] = 0.0;
   out_8008080077202602510[322] = 0.0;
   out_8008080077202602510[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_300170642878345281) {
   out_300170642878345281[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_300170642878345281[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_300170642878345281[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_300170642878345281[3] = dt*state[12] + state[3];
   out_300170642878345281[4] = dt*state[13] + state[4];
   out_300170642878345281[5] = dt*state[14] + state[5];
   out_300170642878345281[6] = state[6];
   out_300170642878345281[7] = state[7];
   out_300170642878345281[8] = state[8];
   out_300170642878345281[9] = state[9];
   out_300170642878345281[10] = state[10];
   out_300170642878345281[11] = state[11];
   out_300170642878345281[12] = state[12];
   out_300170642878345281[13] = state[13];
   out_300170642878345281[14] = state[14];
   out_300170642878345281[15] = state[15];
   out_300170642878345281[16] = state[16];
   out_300170642878345281[17] = state[17];
}
void F_fun(double *state, double dt, double *out_581435981594179307) {
   out_581435981594179307[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_581435981594179307[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_581435981594179307[2] = 0;
   out_581435981594179307[3] = 0;
   out_581435981594179307[4] = 0;
   out_581435981594179307[5] = 0;
   out_581435981594179307[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_581435981594179307[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_581435981594179307[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_581435981594179307[9] = 0;
   out_581435981594179307[10] = 0;
   out_581435981594179307[11] = 0;
   out_581435981594179307[12] = 0;
   out_581435981594179307[13] = 0;
   out_581435981594179307[14] = 0;
   out_581435981594179307[15] = 0;
   out_581435981594179307[16] = 0;
   out_581435981594179307[17] = 0;
   out_581435981594179307[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_581435981594179307[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_581435981594179307[20] = 0;
   out_581435981594179307[21] = 0;
   out_581435981594179307[22] = 0;
   out_581435981594179307[23] = 0;
   out_581435981594179307[24] = 0;
   out_581435981594179307[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_581435981594179307[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_581435981594179307[27] = 0;
   out_581435981594179307[28] = 0;
   out_581435981594179307[29] = 0;
   out_581435981594179307[30] = 0;
   out_581435981594179307[31] = 0;
   out_581435981594179307[32] = 0;
   out_581435981594179307[33] = 0;
   out_581435981594179307[34] = 0;
   out_581435981594179307[35] = 0;
   out_581435981594179307[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_581435981594179307[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_581435981594179307[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_581435981594179307[39] = 0;
   out_581435981594179307[40] = 0;
   out_581435981594179307[41] = 0;
   out_581435981594179307[42] = 0;
   out_581435981594179307[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_581435981594179307[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_581435981594179307[45] = 0;
   out_581435981594179307[46] = 0;
   out_581435981594179307[47] = 0;
   out_581435981594179307[48] = 0;
   out_581435981594179307[49] = 0;
   out_581435981594179307[50] = 0;
   out_581435981594179307[51] = 0;
   out_581435981594179307[52] = 0;
   out_581435981594179307[53] = 0;
   out_581435981594179307[54] = 0;
   out_581435981594179307[55] = 0;
   out_581435981594179307[56] = 0;
   out_581435981594179307[57] = 1;
   out_581435981594179307[58] = 0;
   out_581435981594179307[59] = 0;
   out_581435981594179307[60] = 0;
   out_581435981594179307[61] = 0;
   out_581435981594179307[62] = 0;
   out_581435981594179307[63] = 0;
   out_581435981594179307[64] = 0;
   out_581435981594179307[65] = 0;
   out_581435981594179307[66] = dt;
   out_581435981594179307[67] = 0;
   out_581435981594179307[68] = 0;
   out_581435981594179307[69] = 0;
   out_581435981594179307[70] = 0;
   out_581435981594179307[71] = 0;
   out_581435981594179307[72] = 0;
   out_581435981594179307[73] = 0;
   out_581435981594179307[74] = 0;
   out_581435981594179307[75] = 0;
   out_581435981594179307[76] = 1;
   out_581435981594179307[77] = 0;
   out_581435981594179307[78] = 0;
   out_581435981594179307[79] = 0;
   out_581435981594179307[80] = 0;
   out_581435981594179307[81] = 0;
   out_581435981594179307[82] = 0;
   out_581435981594179307[83] = 0;
   out_581435981594179307[84] = 0;
   out_581435981594179307[85] = dt;
   out_581435981594179307[86] = 0;
   out_581435981594179307[87] = 0;
   out_581435981594179307[88] = 0;
   out_581435981594179307[89] = 0;
   out_581435981594179307[90] = 0;
   out_581435981594179307[91] = 0;
   out_581435981594179307[92] = 0;
   out_581435981594179307[93] = 0;
   out_581435981594179307[94] = 0;
   out_581435981594179307[95] = 1;
   out_581435981594179307[96] = 0;
   out_581435981594179307[97] = 0;
   out_581435981594179307[98] = 0;
   out_581435981594179307[99] = 0;
   out_581435981594179307[100] = 0;
   out_581435981594179307[101] = 0;
   out_581435981594179307[102] = 0;
   out_581435981594179307[103] = 0;
   out_581435981594179307[104] = dt;
   out_581435981594179307[105] = 0;
   out_581435981594179307[106] = 0;
   out_581435981594179307[107] = 0;
   out_581435981594179307[108] = 0;
   out_581435981594179307[109] = 0;
   out_581435981594179307[110] = 0;
   out_581435981594179307[111] = 0;
   out_581435981594179307[112] = 0;
   out_581435981594179307[113] = 0;
   out_581435981594179307[114] = 1;
   out_581435981594179307[115] = 0;
   out_581435981594179307[116] = 0;
   out_581435981594179307[117] = 0;
   out_581435981594179307[118] = 0;
   out_581435981594179307[119] = 0;
   out_581435981594179307[120] = 0;
   out_581435981594179307[121] = 0;
   out_581435981594179307[122] = 0;
   out_581435981594179307[123] = 0;
   out_581435981594179307[124] = 0;
   out_581435981594179307[125] = 0;
   out_581435981594179307[126] = 0;
   out_581435981594179307[127] = 0;
   out_581435981594179307[128] = 0;
   out_581435981594179307[129] = 0;
   out_581435981594179307[130] = 0;
   out_581435981594179307[131] = 0;
   out_581435981594179307[132] = 0;
   out_581435981594179307[133] = 1;
   out_581435981594179307[134] = 0;
   out_581435981594179307[135] = 0;
   out_581435981594179307[136] = 0;
   out_581435981594179307[137] = 0;
   out_581435981594179307[138] = 0;
   out_581435981594179307[139] = 0;
   out_581435981594179307[140] = 0;
   out_581435981594179307[141] = 0;
   out_581435981594179307[142] = 0;
   out_581435981594179307[143] = 0;
   out_581435981594179307[144] = 0;
   out_581435981594179307[145] = 0;
   out_581435981594179307[146] = 0;
   out_581435981594179307[147] = 0;
   out_581435981594179307[148] = 0;
   out_581435981594179307[149] = 0;
   out_581435981594179307[150] = 0;
   out_581435981594179307[151] = 0;
   out_581435981594179307[152] = 1;
   out_581435981594179307[153] = 0;
   out_581435981594179307[154] = 0;
   out_581435981594179307[155] = 0;
   out_581435981594179307[156] = 0;
   out_581435981594179307[157] = 0;
   out_581435981594179307[158] = 0;
   out_581435981594179307[159] = 0;
   out_581435981594179307[160] = 0;
   out_581435981594179307[161] = 0;
   out_581435981594179307[162] = 0;
   out_581435981594179307[163] = 0;
   out_581435981594179307[164] = 0;
   out_581435981594179307[165] = 0;
   out_581435981594179307[166] = 0;
   out_581435981594179307[167] = 0;
   out_581435981594179307[168] = 0;
   out_581435981594179307[169] = 0;
   out_581435981594179307[170] = 0;
   out_581435981594179307[171] = 1;
   out_581435981594179307[172] = 0;
   out_581435981594179307[173] = 0;
   out_581435981594179307[174] = 0;
   out_581435981594179307[175] = 0;
   out_581435981594179307[176] = 0;
   out_581435981594179307[177] = 0;
   out_581435981594179307[178] = 0;
   out_581435981594179307[179] = 0;
   out_581435981594179307[180] = 0;
   out_581435981594179307[181] = 0;
   out_581435981594179307[182] = 0;
   out_581435981594179307[183] = 0;
   out_581435981594179307[184] = 0;
   out_581435981594179307[185] = 0;
   out_581435981594179307[186] = 0;
   out_581435981594179307[187] = 0;
   out_581435981594179307[188] = 0;
   out_581435981594179307[189] = 0;
   out_581435981594179307[190] = 1;
   out_581435981594179307[191] = 0;
   out_581435981594179307[192] = 0;
   out_581435981594179307[193] = 0;
   out_581435981594179307[194] = 0;
   out_581435981594179307[195] = 0;
   out_581435981594179307[196] = 0;
   out_581435981594179307[197] = 0;
   out_581435981594179307[198] = 0;
   out_581435981594179307[199] = 0;
   out_581435981594179307[200] = 0;
   out_581435981594179307[201] = 0;
   out_581435981594179307[202] = 0;
   out_581435981594179307[203] = 0;
   out_581435981594179307[204] = 0;
   out_581435981594179307[205] = 0;
   out_581435981594179307[206] = 0;
   out_581435981594179307[207] = 0;
   out_581435981594179307[208] = 0;
   out_581435981594179307[209] = 1;
   out_581435981594179307[210] = 0;
   out_581435981594179307[211] = 0;
   out_581435981594179307[212] = 0;
   out_581435981594179307[213] = 0;
   out_581435981594179307[214] = 0;
   out_581435981594179307[215] = 0;
   out_581435981594179307[216] = 0;
   out_581435981594179307[217] = 0;
   out_581435981594179307[218] = 0;
   out_581435981594179307[219] = 0;
   out_581435981594179307[220] = 0;
   out_581435981594179307[221] = 0;
   out_581435981594179307[222] = 0;
   out_581435981594179307[223] = 0;
   out_581435981594179307[224] = 0;
   out_581435981594179307[225] = 0;
   out_581435981594179307[226] = 0;
   out_581435981594179307[227] = 0;
   out_581435981594179307[228] = 1;
   out_581435981594179307[229] = 0;
   out_581435981594179307[230] = 0;
   out_581435981594179307[231] = 0;
   out_581435981594179307[232] = 0;
   out_581435981594179307[233] = 0;
   out_581435981594179307[234] = 0;
   out_581435981594179307[235] = 0;
   out_581435981594179307[236] = 0;
   out_581435981594179307[237] = 0;
   out_581435981594179307[238] = 0;
   out_581435981594179307[239] = 0;
   out_581435981594179307[240] = 0;
   out_581435981594179307[241] = 0;
   out_581435981594179307[242] = 0;
   out_581435981594179307[243] = 0;
   out_581435981594179307[244] = 0;
   out_581435981594179307[245] = 0;
   out_581435981594179307[246] = 0;
   out_581435981594179307[247] = 1;
   out_581435981594179307[248] = 0;
   out_581435981594179307[249] = 0;
   out_581435981594179307[250] = 0;
   out_581435981594179307[251] = 0;
   out_581435981594179307[252] = 0;
   out_581435981594179307[253] = 0;
   out_581435981594179307[254] = 0;
   out_581435981594179307[255] = 0;
   out_581435981594179307[256] = 0;
   out_581435981594179307[257] = 0;
   out_581435981594179307[258] = 0;
   out_581435981594179307[259] = 0;
   out_581435981594179307[260] = 0;
   out_581435981594179307[261] = 0;
   out_581435981594179307[262] = 0;
   out_581435981594179307[263] = 0;
   out_581435981594179307[264] = 0;
   out_581435981594179307[265] = 0;
   out_581435981594179307[266] = 1;
   out_581435981594179307[267] = 0;
   out_581435981594179307[268] = 0;
   out_581435981594179307[269] = 0;
   out_581435981594179307[270] = 0;
   out_581435981594179307[271] = 0;
   out_581435981594179307[272] = 0;
   out_581435981594179307[273] = 0;
   out_581435981594179307[274] = 0;
   out_581435981594179307[275] = 0;
   out_581435981594179307[276] = 0;
   out_581435981594179307[277] = 0;
   out_581435981594179307[278] = 0;
   out_581435981594179307[279] = 0;
   out_581435981594179307[280] = 0;
   out_581435981594179307[281] = 0;
   out_581435981594179307[282] = 0;
   out_581435981594179307[283] = 0;
   out_581435981594179307[284] = 0;
   out_581435981594179307[285] = 1;
   out_581435981594179307[286] = 0;
   out_581435981594179307[287] = 0;
   out_581435981594179307[288] = 0;
   out_581435981594179307[289] = 0;
   out_581435981594179307[290] = 0;
   out_581435981594179307[291] = 0;
   out_581435981594179307[292] = 0;
   out_581435981594179307[293] = 0;
   out_581435981594179307[294] = 0;
   out_581435981594179307[295] = 0;
   out_581435981594179307[296] = 0;
   out_581435981594179307[297] = 0;
   out_581435981594179307[298] = 0;
   out_581435981594179307[299] = 0;
   out_581435981594179307[300] = 0;
   out_581435981594179307[301] = 0;
   out_581435981594179307[302] = 0;
   out_581435981594179307[303] = 0;
   out_581435981594179307[304] = 1;
   out_581435981594179307[305] = 0;
   out_581435981594179307[306] = 0;
   out_581435981594179307[307] = 0;
   out_581435981594179307[308] = 0;
   out_581435981594179307[309] = 0;
   out_581435981594179307[310] = 0;
   out_581435981594179307[311] = 0;
   out_581435981594179307[312] = 0;
   out_581435981594179307[313] = 0;
   out_581435981594179307[314] = 0;
   out_581435981594179307[315] = 0;
   out_581435981594179307[316] = 0;
   out_581435981594179307[317] = 0;
   out_581435981594179307[318] = 0;
   out_581435981594179307[319] = 0;
   out_581435981594179307[320] = 0;
   out_581435981594179307[321] = 0;
   out_581435981594179307[322] = 0;
   out_581435981594179307[323] = 1;
}
void h_4(double *state, double *unused, double *out_1860856687374340932) {
   out_1860856687374340932[0] = state[6] + state[9];
   out_1860856687374340932[1] = state[7] + state[10];
   out_1860856687374340932[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2855561692163521775) {
   out_2855561692163521775[0] = 0;
   out_2855561692163521775[1] = 0;
   out_2855561692163521775[2] = 0;
   out_2855561692163521775[3] = 0;
   out_2855561692163521775[4] = 0;
   out_2855561692163521775[5] = 0;
   out_2855561692163521775[6] = 1;
   out_2855561692163521775[7] = 0;
   out_2855561692163521775[8] = 0;
   out_2855561692163521775[9] = 1;
   out_2855561692163521775[10] = 0;
   out_2855561692163521775[11] = 0;
   out_2855561692163521775[12] = 0;
   out_2855561692163521775[13] = 0;
   out_2855561692163521775[14] = 0;
   out_2855561692163521775[15] = 0;
   out_2855561692163521775[16] = 0;
   out_2855561692163521775[17] = 0;
   out_2855561692163521775[18] = 0;
   out_2855561692163521775[19] = 0;
   out_2855561692163521775[20] = 0;
   out_2855561692163521775[21] = 0;
   out_2855561692163521775[22] = 0;
   out_2855561692163521775[23] = 0;
   out_2855561692163521775[24] = 0;
   out_2855561692163521775[25] = 1;
   out_2855561692163521775[26] = 0;
   out_2855561692163521775[27] = 0;
   out_2855561692163521775[28] = 1;
   out_2855561692163521775[29] = 0;
   out_2855561692163521775[30] = 0;
   out_2855561692163521775[31] = 0;
   out_2855561692163521775[32] = 0;
   out_2855561692163521775[33] = 0;
   out_2855561692163521775[34] = 0;
   out_2855561692163521775[35] = 0;
   out_2855561692163521775[36] = 0;
   out_2855561692163521775[37] = 0;
   out_2855561692163521775[38] = 0;
   out_2855561692163521775[39] = 0;
   out_2855561692163521775[40] = 0;
   out_2855561692163521775[41] = 0;
   out_2855561692163521775[42] = 0;
   out_2855561692163521775[43] = 0;
   out_2855561692163521775[44] = 1;
   out_2855561692163521775[45] = 0;
   out_2855561692163521775[46] = 0;
   out_2855561692163521775[47] = 1;
   out_2855561692163521775[48] = 0;
   out_2855561692163521775[49] = 0;
   out_2855561692163521775[50] = 0;
   out_2855561692163521775[51] = 0;
   out_2855561692163521775[52] = 0;
   out_2855561692163521775[53] = 0;
}
void h_10(double *state, double *unused, double *out_8529954627682698254) {
   out_8529954627682698254[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8529954627682698254[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8529954627682698254[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7619851342069224566) {
   out_7619851342069224566[0] = 0;
   out_7619851342069224566[1] = 9.8100000000000005*cos(state[1]);
   out_7619851342069224566[2] = 0;
   out_7619851342069224566[3] = 0;
   out_7619851342069224566[4] = -state[8];
   out_7619851342069224566[5] = state[7];
   out_7619851342069224566[6] = 0;
   out_7619851342069224566[7] = state[5];
   out_7619851342069224566[8] = -state[4];
   out_7619851342069224566[9] = 0;
   out_7619851342069224566[10] = 0;
   out_7619851342069224566[11] = 0;
   out_7619851342069224566[12] = 1;
   out_7619851342069224566[13] = 0;
   out_7619851342069224566[14] = 0;
   out_7619851342069224566[15] = 1;
   out_7619851342069224566[16] = 0;
   out_7619851342069224566[17] = 0;
   out_7619851342069224566[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7619851342069224566[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7619851342069224566[20] = 0;
   out_7619851342069224566[21] = state[8];
   out_7619851342069224566[22] = 0;
   out_7619851342069224566[23] = -state[6];
   out_7619851342069224566[24] = -state[5];
   out_7619851342069224566[25] = 0;
   out_7619851342069224566[26] = state[3];
   out_7619851342069224566[27] = 0;
   out_7619851342069224566[28] = 0;
   out_7619851342069224566[29] = 0;
   out_7619851342069224566[30] = 0;
   out_7619851342069224566[31] = 1;
   out_7619851342069224566[32] = 0;
   out_7619851342069224566[33] = 0;
   out_7619851342069224566[34] = 1;
   out_7619851342069224566[35] = 0;
   out_7619851342069224566[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7619851342069224566[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7619851342069224566[38] = 0;
   out_7619851342069224566[39] = -state[7];
   out_7619851342069224566[40] = state[6];
   out_7619851342069224566[41] = 0;
   out_7619851342069224566[42] = state[4];
   out_7619851342069224566[43] = -state[3];
   out_7619851342069224566[44] = 0;
   out_7619851342069224566[45] = 0;
   out_7619851342069224566[46] = 0;
   out_7619851342069224566[47] = 0;
   out_7619851342069224566[48] = 0;
   out_7619851342069224566[49] = 0;
   out_7619851342069224566[50] = 1;
   out_7619851342069224566[51] = 0;
   out_7619851342069224566[52] = 0;
   out_7619851342069224566[53] = 1;
}
void h_13(double *state, double *unused, double *out_8848881485524591493) {
   out_8848881485524591493[0] = state[3];
   out_8848881485524591493[1] = state[4];
   out_8848881485524591493[2] = state[5];
}
void H_13(double *state, double *unused, double *out_356712133168811026) {
   out_356712133168811026[0] = 0;
   out_356712133168811026[1] = 0;
   out_356712133168811026[2] = 0;
   out_356712133168811026[3] = 1;
   out_356712133168811026[4] = 0;
   out_356712133168811026[5] = 0;
   out_356712133168811026[6] = 0;
   out_356712133168811026[7] = 0;
   out_356712133168811026[8] = 0;
   out_356712133168811026[9] = 0;
   out_356712133168811026[10] = 0;
   out_356712133168811026[11] = 0;
   out_356712133168811026[12] = 0;
   out_356712133168811026[13] = 0;
   out_356712133168811026[14] = 0;
   out_356712133168811026[15] = 0;
   out_356712133168811026[16] = 0;
   out_356712133168811026[17] = 0;
   out_356712133168811026[18] = 0;
   out_356712133168811026[19] = 0;
   out_356712133168811026[20] = 0;
   out_356712133168811026[21] = 0;
   out_356712133168811026[22] = 1;
   out_356712133168811026[23] = 0;
   out_356712133168811026[24] = 0;
   out_356712133168811026[25] = 0;
   out_356712133168811026[26] = 0;
   out_356712133168811026[27] = 0;
   out_356712133168811026[28] = 0;
   out_356712133168811026[29] = 0;
   out_356712133168811026[30] = 0;
   out_356712133168811026[31] = 0;
   out_356712133168811026[32] = 0;
   out_356712133168811026[33] = 0;
   out_356712133168811026[34] = 0;
   out_356712133168811026[35] = 0;
   out_356712133168811026[36] = 0;
   out_356712133168811026[37] = 0;
   out_356712133168811026[38] = 0;
   out_356712133168811026[39] = 0;
   out_356712133168811026[40] = 0;
   out_356712133168811026[41] = 1;
   out_356712133168811026[42] = 0;
   out_356712133168811026[43] = 0;
   out_356712133168811026[44] = 0;
   out_356712133168811026[45] = 0;
   out_356712133168811026[46] = 0;
   out_356712133168811026[47] = 0;
   out_356712133168811026[48] = 0;
   out_356712133168811026[49] = 0;
   out_356712133168811026[50] = 0;
   out_356712133168811026[51] = 0;
   out_356712133168811026[52] = 0;
   out_356712133168811026[53] = 0;
}
void h_14(double *state, double *unused, double *out_6213919889321867101) {
   out_6213919889321867101[0] = state[6];
   out_6213919889321867101[1] = state[7];
   out_6213919889321867101[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3290678218808405374) {
   out_3290678218808405374[0] = 0;
   out_3290678218808405374[1] = 0;
   out_3290678218808405374[2] = 0;
   out_3290678218808405374[3] = 0;
   out_3290678218808405374[4] = 0;
   out_3290678218808405374[5] = 0;
   out_3290678218808405374[6] = 1;
   out_3290678218808405374[7] = 0;
   out_3290678218808405374[8] = 0;
   out_3290678218808405374[9] = 0;
   out_3290678218808405374[10] = 0;
   out_3290678218808405374[11] = 0;
   out_3290678218808405374[12] = 0;
   out_3290678218808405374[13] = 0;
   out_3290678218808405374[14] = 0;
   out_3290678218808405374[15] = 0;
   out_3290678218808405374[16] = 0;
   out_3290678218808405374[17] = 0;
   out_3290678218808405374[18] = 0;
   out_3290678218808405374[19] = 0;
   out_3290678218808405374[20] = 0;
   out_3290678218808405374[21] = 0;
   out_3290678218808405374[22] = 0;
   out_3290678218808405374[23] = 0;
   out_3290678218808405374[24] = 0;
   out_3290678218808405374[25] = 1;
   out_3290678218808405374[26] = 0;
   out_3290678218808405374[27] = 0;
   out_3290678218808405374[28] = 0;
   out_3290678218808405374[29] = 0;
   out_3290678218808405374[30] = 0;
   out_3290678218808405374[31] = 0;
   out_3290678218808405374[32] = 0;
   out_3290678218808405374[33] = 0;
   out_3290678218808405374[34] = 0;
   out_3290678218808405374[35] = 0;
   out_3290678218808405374[36] = 0;
   out_3290678218808405374[37] = 0;
   out_3290678218808405374[38] = 0;
   out_3290678218808405374[39] = 0;
   out_3290678218808405374[40] = 0;
   out_3290678218808405374[41] = 0;
   out_3290678218808405374[42] = 0;
   out_3290678218808405374[43] = 0;
   out_3290678218808405374[44] = 1;
   out_3290678218808405374[45] = 0;
   out_3290678218808405374[46] = 0;
   out_3290678218808405374[47] = 0;
   out_3290678218808405374[48] = 0;
   out_3290678218808405374[49] = 0;
   out_3290678218808405374[50] = 0;
   out_3290678218808405374[51] = 0;
   out_3290678218808405374[52] = 0;
   out_3290678218808405374[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2325015377156513737) {
  err_fun(nom_x, delta_x, out_2325015377156513737);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6324847366348989757) {
  inv_err_fun(nom_x, true_x, out_6324847366348989757);
}
void pose_H_mod_fun(double *state, double *out_8008080077202602510) {
  H_mod_fun(state, out_8008080077202602510);
}
void pose_f_fun(double *state, double dt, double *out_300170642878345281) {
  f_fun(state,  dt, out_300170642878345281);
}
void pose_F_fun(double *state, double dt, double *out_581435981594179307) {
  F_fun(state,  dt, out_581435981594179307);
}
void pose_h_4(double *state, double *unused, double *out_1860856687374340932) {
  h_4(state, unused, out_1860856687374340932);
}
void pose_H_4(double *state, double *unused, double *out_2855561692163521775) {
  H_4(state, unused, out_2855561692163521775);
}
void pose_h_10(double *state, double *unused, double *out_8529954627682698254) {
  h_10(state, unused, out_8529954627682698254);
}
void pose_H_10(double *state, double *unused, double *out_7619851342069224566) {
  H_10(state, unused, out_7619851342069224566);
}
void pose_h_13(double *state, double *unused, double *out_8848881485524591493) {
  h_13(state, unused, out_8848881485524591493);
}
void pose_H_13(double *state, double *unused, double *out_356712133168811026) {
  H_13(state, unused, out_356712133168811026);
}
void pose_h_14(double *state, double *unused, double *out_6213919889321867101) {
  h_14(state, unused, out_6213919889321867101);
}
void pose_H_14(double *state, double *unused, double *out_3290678218808405374) {
  H_14(state, unused, out_3290678218808405374);
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
