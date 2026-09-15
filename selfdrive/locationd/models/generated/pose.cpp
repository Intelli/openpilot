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
void err_fun(double *nom_x, double *delta_x, double *out_3776217962159825712) {
   out_3776217962159825712[0] = delta_x[0] + nom_x[0];
   out_3776217962159825712[1] = delta_x[1] + nom_x[1];
   out_3776217962159825712[2] = delta_x[2] + nom_x[2];
   out_3776217962159825712[3] = delta_x[3] + nom_x[3];
   out_3776217962159825712[4] = delta_x[4] + nom_x[4];
   out_3776217962159825712[5] = delta_x[5] + nom_x[5];
   out_3776217962159825712[6] = delta_x[6] + nom_x[6];
   out_3776217962159825712[7] = delta_x[7] + nom_x[7];
   out_3776217962159825712[8] = delta_x[8] + nom_x[8];
   out_3776217962159825712[9] = delta_x[9] + nom_x[9];
   out_3776217962159825712[10] = delta_x[10] + nom_x[10];
   out_3776217962159825712[11] = delta_x[11] + nom_x[11];
   out_3776217962159825712[12] = delta_x[12] + nom_x[12];
   out_3776217962159825712[13] = delta_x[13] + nom_x[13];
   out_3776217962159825712[14] = delta_x[14] + nom_x[14];
   out_3776217962159825712[15] = delta_x[15] + nom_x[15];
   out_3776217962159825712[16] = delta_x[16] + nom_x[16];
   out_3776217962159825712[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_838326120936530935) {
   out_838326120936530935[0] = -nom_x[0] + true_x[0];
   out_838326120936530935[1] = -nom_x[1] + true_x[1];
   out_838326120936530935[2] = -nom_x[2] + true_x[2];
   out_838326120936530935[3] = -nom_x[3] + true_x[3];
   out_838326120936530935[4] = -nom_x[4] + true_x[4];
   out_838326120936530935[5] = -nom_x[5] + true_x[5];
   out_838326120936530935[6] = -nom_x[6] + true_x[6];
   out_838326120936530935[7] = -nom_x[7] + true_x[7];
   out_838326120936530935[8] = -nom_x[8] + true_x[8];
   out_838326120936530935[9] = -nom_x[9] + true_x[9];
   out_838326120936530935[10] = -nom_x[10] + true_x[10];
   out_838326120936530935[11] = -nom_x[11] + true_x[11];
   out_838326120936530935[12] = -nom_x[12] + true_x[12];
   out_838326120936530935[13] = -nom_x[13] + true_x[13];
   out_838326120936530935[14] = -nom_x[14] + true_x[14];
   out_838326120936530935[15] = -nom_x[15] + true_x[15];
   out_838326120936530935[16] = -nom_x[16] + true_x[16];
   out_838326120936530935[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3231377197098151338) {
   out_3231377197098151338[0] = 1.0;
   out_3231377197098151338[1] = 0.0;
   out_3231377197098151338[2] = 0.0;
   out_3231377197098151338[3] = 0.0;
   out_3231377197098151338[4] = 0.0;
   out_3231377197098151338[5] = 0.0;
   out_3231377197098151338[6] = 0.0;
   out_3231377197098151338[7] = 0.0;
   out_3231377197098151338[8] = 0.0;
   out_3231377197098151338[9] = 0.0;
   out_3231377197098151338[10] = 0.0;
   out_3231377197098151338[11] = 0.0;
   out_3231377197098151338[12] = 0.0;
   out_3231377197098151338[13] = 0.0;
   out_3231377197098151338[14] = 0.0;
   out_3231377197098151338[15] = 0.0;
   out_3231377197098151338[16] = 0.0;
   out_3231377197098151338[17] = 0.0;
   out_3231377197098151338[18] = 0.0;
   out_3231377197098151338[19] = 1.0;
   out_3231377197098151338[20] = 0.0;
   out_3231377197098151338[21] = 0.0;
   out_3231377197098151338[22] = 0.0;
   out_3231377197098151338[23] = 0.0;
   out_3231377197098151338[24] = 0.0;
   out_3231377197098151338[25] = 0.0;
   out_3231377197098151338[26] = 0.0;
   out_3231377197098151338[27] = 0.0;
   out_3231377197098151338[28] = 0.0;
   out_3231377197098151338[29] = 0.0;
   out_3231377197098151338[30] = 0.0;
   out_3231377197098151338[31] = 0.0;
   out_3231377197098151338[32] = 0.0;
   out_3231377197098151338[33] = 0.0;
   out_3231377197098151338[34] = 0.0;
   out_3231377197098151338[35] = 0.0;
   out_3231377197098151338[36] = 0.0;
   out_3231377197098151338[37] = 0.0;
   out_3231377197098151338[38] = 1.0;
   out_3231377197098151338[39] = 0.0;
   out_3231377197098151338[40] = 0.0;
   out_3231377197098151338[41] = 0.0;
   out_3231377197098151338[42] = 0.0;
   out_3231377197098151338[43] = 0.0;
   out_3231377197098151338[44] = 0.0;
   out_3231377197098151338[45] = 0.0;
   out_3231377197098151338[46] = 0.0;
   out_3231377197098151338[47] = 0.0;
   out_3231377197098151338[48] = 0.0;
   out_3231377197098151338[49] = 0.0;
   out_3231377197098151338[50] = 0.0;
   out_3231377197098151338[51] = 0.0;
   out_3231377197098151338[52] = 0.0;
   out_3231377197098151338[53] = 0.0;
   out_3231377197098151338[54] = 0.0;
   out_3231377197098151338[55] = 0.0;
   out_3231377197098151338[56] = 0.0;
   out_3231377197098151338[57] = 1.0;
   out_3231377197098151338[58] = 0.0;
   out_3231377197098151338[59] = 0.0;
   out_3231377197098151338[60] = 0.0;
   out_3231377197098151338[61] = 0.0;
   out_3231377197098151338[62] = 0.0;
   out_3231377197098151338[63] = 0.0;
   out_3231377197098151338[64] = 0.0;
   out_3231377197098151338[65] = 0.0;
   out_3231377197098151338[66] = 0.0;
   out_3231377197098151338[67] = 0.0;
   out_3231377197098151338[68] = 0.0;
   out_3231377197098151338[69] = 0.0;
   out_3231377197098151338[70] = 0.0;
   out_3231377197098151338[71] = 0.0;
   out_3231377197098151338[72] = 0.0;
   out_3231377197098151338[73] = 0.0;
   out_3231377197098151338[74] = 0.0;
   out_3231377197098151338[75] = 0.0;
   out_3231377197098151338[76] = 1.0;
   out_3231377197098151338[77] = 0.0;
   out_3231377197098151338[78] = 0.0;
   out_3231377197098151338[79] = 0.0;
   out_3231377197098151338[80] = 0.0;
   out_3231377197098151338[81] = 0.0;
   out_3231377197098151338[82] = 0.0;
   out_3231377197098151338[83] = 0.0;
   out_3231377197098151338[84] = 0.0;
   out_3231377197098151338[85] = 0.0;
   out_3231377197098151338[86] = 0.0;
   out_3231377197098151338[87] = 0.0;
   out_3231377197098151338[88] = 0.0;
   out_3231377197098151338[89] = 0.0;
   out_3231377197098151338[90] = 0.0;
   out_3231377197098151338[91] = 0.0;
   out_3231377197098151338[92] = 0.0;
   out_3231377197098151338[93] = 0.0;
   out_3231377197098151338[94] = 0.0;
   out_3231377197098151338[95] = 1.0;
   out_3231377197098151338[96] = 0.0;
   out_3231377197098151338[97] = 0.0;
   out_3231377197098151338[98] = 0.0;
   out_3231377197098151338[99] = 0.0;
   out_3231377197098151338[100] = 0.0;
   out_3231377197098151338[101] = 0.0;
   out_3231377197098151338[102] = 0.0;
   out_3231377197098151338[103] = 0.0;
   out_3231377197098151338[104] = 0.0;
   out_3231377197098151338[105] = 0.0;
   out_3231377197098151338[106] = 0.0;
   out_3231377197098151338[107] = 0.0;
   out_3231377197098151338[108] = 0.0;
   out_3231377197098151338[109] = 0.0;
   out_3231377197098151338[110] = 0.0;
   out_3231377197098151338[111] = 0.0;
   out_3231377197098151338[112] = 0.0;
   out_3231377197098151338[113] = 0.0;
   out_3231377197098151338[114] = 1.0;
   out_3231377197098151338[115] = 0.0;
   out_3231377197098151338[116] = 0.0;
   out_3231377197098151338[117] = 0.0;
   out_3231377197098151338[118] = 0.0;
   out_3231377197098151338[119] = 0.0;
   out_3231377197098151338[120] = 0.0;
   out_3231377197098151338[121] = 0.0;
   out_3231377197098151338[122] = 0.0;
   out_3231377197098151338[123] = 0.0;
   out_3231377197098151338[124] = 0.0;
   out_3231377197098151338[125] = 0.0;
   out_3231377197098151338[126] = 0.0;
   out_3231377197098151338[127] = 0.0;
   out_3231377197098151338[128] = 0.0;
   out_3231377197098151338[129] = 0.0;
   out_3231377197098151338[130] = 0.0;
   out_3231377197098151338[131] = 0.0;
   out_3231377197098151338[132] = 0.0;
   out_3231377197098151338[133] = 1.0;
   out_3231377197098151338[134] = 0.0;
   out_3231377197098151338[135] = 0.0;
   out_3231377197098151338[136] = 0.0;
   out_3231377197098151338[137] = 0.0;
   out_3231377197098151338[138] = 0.0;
   out_3231377197098151338[139] = 0.0;
   out_3231377197098151338[140] = 0.0;
   out_3231377197098151338[141] = 0.0;
   out_3231377197098151338[142] = 0.0;
   out_3231377197098151338[143] = 0.0;
   out_3231377197098151338[144] = 0.0;
   out_3231377197098151338[145] = 0.0;
   out_3231377197098151338[146] = 0.0;
   out_3231377197098151338[147] = 0.0;
   out_3231377197098151338[148] = 0.0;
   out_3231377197098151338[149] = 0.0;
   out_3231377197098151338[150] = 0.0;
   out_3231377197098151338[151] = 0.0;
   out_3231377197098151338[152] = 1.0;
   out_3231377197098151338[153] = 0.0;
   out_3231377197098151338[154] = 0.0;
   out_3231377197098151338[155] = 0.0;
   out_3231377197098151338[156] = 0.0;
   out_3231377197098151338[157] = 0.0;
   out_3231377197098151338[158] = 0.0;
   out_3231377197098151338[159] = 0.0;
   out_3231377197098151338[160] = 0.0;
   out_3231377197098151338[161] = 0.0;
   out_3231377197098151338[162] = 0.0;
   out_3231377197098151338[163] = 0.0;
   out_3231377197098151338[164] = 0.0;
   out_3231377197098151338[165] = 0.0;
   out_3231377197098151338[166] = 0.0;
   out_3231377197098151338[167] = 0.0;
   out_3231377197098151338[168] = 0.0;
   out_3231377197098151338[169] = 0.0;
   out_3231377197098151338[170] = 0.0;
   out_3231377197098151338[171] = 1.0;
   out_3231377197098151338[172] = 0.0;
   out_3231377197098151338[173] = 0.0;
   out_3231377197098151338[174] = 0.0;
   out_3231377197098151338[175] = 0.0;
   out_3231377197098151338[176] = 0.0;
   out_3231377197098151338[177] = 0.0;
   out_3231377197098151338[178] = 0.0;
   out_3231377197098151338[179] = 0.0;
   out_3231377197098151338[180] = 0.0;
   out_3231377197098151338[181] = 0.0;
   out_3231377197098151338[182] = 0.0;
   out_3231377197098151338[183] = 0.0;
   out_3231377197098151338[184] = 0.0;
   out_3231377197098151338[185] = 0.0;
   out_3231377197098151338[186] = 0.0;
   out_3231377197098151338[187] = 0.0;
   out_3231377197098151338[188] = 0.0;
   out_3231377197098151338[189] = 0.0;
   out_3231377197098151338[190] = 1.0;
   out_3231377197098151338[191] = 0.0;
   out_3231377197098151338[192] = 0.0;
   out_3231377197098151338[193] = 0.0;
   out_3231377197098151338[194] = 0.0;
   out_3231377197098151338[195] = 0.0;
   out_3231377197098151338[196] = 0.0;
   out_3231377197098151338[197] = 0.0;
   out_3231377197098151338[198] = 0.0;
   out_3231377197098151338[199] = 0.0;
   out_3231377197098151338[200] = 0.0;
   out_3231377197098151338[201] = 0.0;
   out_3231377197098151338[202] = 0.0;
   out_3231377197098151338[203] = 0.0;
   out_3231377197098151338[204] = 0.0;
   out_3231377197098151338[205] = 0.0;
   out_3231377197098151338[206] = 0.0;
   out_3231377197098151338[207] = 0.0;
   out_3231377197098151338[208] = 0.0;
   out_3231377197098151338[209] = 1.0;
   out_3231377197098151338[210] = 0.0;
   out_3231377197098151338[211] = 0.0;
   out_3231377197098151338[212] = 0.0;
   out_3231377197098151338[213] = 0.0;
   out_3231377197098151338[214] = 0.0;
   out_3231377197098151338[215] = 0.0;
   out_3231377197098151338[216] = 0.0;
   out_3231377197098151338[217] = 0.0;
   out_3231377197098151338[218] = 0.0;
   out_3231377197098151338[219] = 0.0;
   out_3231377197098151338[220] = 0.0;
   out_3231377197098151338[221] = 0.0;
   out_3231377197098151338[222] = 0.0;
   out_3231377197098151338[223] = 0.0;
   out_3231377197098151338[224] = 0.0;
   out_3231377197098151338[225] = 0.0;
   out_3231377197098151338[226] = 0.0;
   out_3231377197098151338[227] = 0.0;
   out_3231377197098151338[228] = 1.0;
   out_3231377197098151338[229] = 0.0;
   out_3231377197098151338[230] = 0.0;
   out_3231377197098151338[231] = 0.0;
   out_3231377197098151338[232] = 0.0;
   out_3231377197098151338[233] = 0.0;
   out_3231377197098151338[234] = 0.0;
   out_3231377197098151338[235] = 0.0;
   out_3231377197098151338[236] = 0.0;
   out_3231377197098151338[237] = 0.0;
   out_3231377197098151338[238] = 0.0;
   out_3231377197098151338[239] = 0.0;
   out_3231377197098151338[240] = 0.0;
   out_3231377197098151338[241] = 0.0;
   out_3231377197098151338[242] = 0.0;
   out_3231377197098151338[243] = 0.0;
   out_3231377197098151338[244] = 0.0;
   out_3231377197098151338[245] = 0.0;
   out_3231377197098151338[246] = 0.0;
   out_3231377197098151338[247] = 1.0;
   out_3231377197098151338[248] = 0.0;
   out_3231377197098151338[249] = 0.0;
   out_3231377197098151338[250] = 0.0;
   out_3231377197098151338[251] = 0.0;
   out_3231377197098151338[252] = 0.0;
   out_3231377197098151338[253] = 0.0;
   out_3231377197098151338[254] = 0.0;
   out_3231377197098151338[255] = 0.0;
   out_3231377197098151338[256] = 0.0;
   out_3231377197098151338[257] = 0.0;
   out_3231377197098151338[258] = 0.0;
   out_3231377197098151338[259] = 0.0;
   out_3231377197098151338[260] = 0.0;
   out_3231377197098151338[261] = 0.0;
   out_3231377197098151338[262] = 0.0;
   out_3231377197098151338[263] = 0.0;
   out_3231377197098151338[264] = 0.0;
   out_3231377197098151338[265] = 0.0;
   out_3231377197098151338[266] = 1.0;
   out_3231377197098151338[267] = 0.0;
   out_3231377197098151338[268] = 0.0;
   out_3231377197098151338[269] = 0.0;
   out_3231377197098151338[270] = 0.0;
   out_3231377197098151338[271] = 0.0;
   out_3231377197098151338[272] = 0.0;
   out_3231377197098151338[273] = 0.0;
   out_3231377197098151338[274] = 0.0;
   out_3231377197098151338[275] = 0.0;
   out_3231377197098151338[276] = 0.0;
   out_3231377197098151338[277] = 0.0;
   out_3231377197098151338[278] = 0.0;
   out_3231377197098151338[279] = 0.0;
   out_3231377197098151338[280] = 0.0;
   out_3231377197098151338[281] = 0.0;
   out_3231377197098151338[282] = 0.0;
   out_3231377197098151338[283] = 0.0;
   out_3231377197098151338[284] = 0.0;
   out_3231377197098151338[285] = 1.0;
   out_3231377197098151338[286] = 0.0;
   out_3231377197098151338[287] = 0.0;
   out_3231377197098151338[288] = 0.0;
   out_3231377197098151338[289] = 0.0;
   out_3231377197098151338[290] = 0.0;
   out_3231377197098151338[291] = 0.0;
   out_3231377197098151338[292] = 0.0;
   out_3231377197098151338[293] = 0.0;
   out_3231377197098151338[294] = 0.0;
   out_3231377197098151338[295] = 0.0;
   out_3231377197098151338[296] = 0.0;
   out_3231377197098151338[297] = 0.0;
   out_3231377197098151338[298] = 0.0;
   out_3231377197098151338[299] = 0.0;
   out_3231377197098151338[300] = 0.0;
   out_3231377197098151338[301] = 0.0;
   out_3231377197098151338[302] = 0.0;
   out_3231377197098151338[303] = 0.0;
   out_3231377197098151338[304] = 1.0;
   out_3231377197098151338[305] = 0.0;
   out_3231377197098151338[306] = 0.0;
   out_3231377197098151338[307] = 0.0;
   out_3231377197098151338[308] = 0.0;
   out_3231377197098151338[309] = 0.0;
   out_3231377197098151338[310] = 0.0;
   out_3231377197098151338[311] = 0.0;
   out_3231377197098151338[312] = 0.0;
   out_3231377197098151338[313] = 0.0;
   out_3231377197098151338[314] = 0.0;
   out_3231377197098151338[315] = 0.0;
   out_3231377197098151338[316] = 0.0;
   out_3231377197098151338[317] = 0.0;
   out_3231377197098151338[318] = 0.0;
   out_3231377197098151338[319] = 0.0;
   out_3231377197098151338[320] = 0.0;
   out_3231377197098151338[321] = 0.0;
   out_3231377197098151338[322] = 0.0;
   out_3231377197098151338[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4330621084971378974) {
   out_4330621084971378974[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4330621084971378974[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4330621084971378974[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4330621084971378974[3] = dt*state[12] + state[3];
   out_4330621084971378974[4] = dt*state[13] + state[4];
   out_4330621084971378974[5] = dt*state[14] + state[5];
   out_4330621084971378974[6] = state[6];
   out_4330621084971378974[7] = state[7];
   out_4330621084971378974[8] = state[8];
   out_4330621084971378974[9] = state[9];
   out_4330621084971378974[10] = state[10];
   out_4330621084971378974[11] = state[11];
   out_4330621084971378974[12] = state[12];
   out_4330621084971378974[13] = state[13];
   out_4330621084971378974[14] = state[14];
   out_4330621084971378974[15] = state[15];
   out_4330621084971378974[16] = state[16];
   out_4330621084971378974[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2585841718456555900) {
   out_2585841718456555900[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2585841718456555900[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2585841718456555900[2] = 0;
   out_2585841718456555900[3] = 0;
   out_2585841718456555900[4] = 0;
   out_2585841718456555900[5] = 0;
   out_2585841718456555900[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2585841718456555900[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2585841718456555900[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2585841718456555900[9] = 0;
   out_2585841718456555900[10] = 0;
   out_2585841718456555900[11] = 0;
   out_2585841718456555900[12] = 0;
   out_2585841718456555900[13] = 0;
   out_2585841718456555900[14] = 0;
   out_2585841718456555900[15] = 0;
   out_2585841718456555900[16] = 0;
   out_2585841718456555900[17] = 0;
   out_2585841718456555900[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2585841718456555900[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2585841718456555900[20] = 0;
   out_2585841718456555900[21] = 0;
   out_2585841718456555900[22] = 0;
   out_2585841718456555900[23] = 0;
   out_2585841718456555900[24] = 0;
   out_2585841718456555900[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2585841718456555900[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2585841718456555900[27] = 0;
   out_2585841718456555900[28] = 0;
   out_2585841718456555900[29] = 0;
   out_2585841718456555900[30] = 0;
   out_2585841718456555900[31] = 0;
   out_2585841718456555900[32] = 0;
   out_2585841718456555900[33] = 0;
   out_2585841718456555900[34] = 0;
   out_2585841718456555900[35] = 0;
   out_2585841718456555900[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2585841718456555900[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2585841718456555900[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2585841718456555900[39] = 0;
   out_2585841718456555900[40] = 0;
   out_2585841718456555900[41] = 0;
   out_2585841718456555900[42] = 0;
   out_2585841718456555900[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2585841718456555900[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2585841718456555900[45] = 0;
   out_2585841718456555900[46] = 0;
   out_2585841718456555900[47] = 0;
   out_2585841718456555900[48] = 0;
   out_2585841718456555900[49] = 0;
   out_2585841718456555900[50] = 0;
   out_2585841718456555900[51] = 0;
   out_2585841718456555900[52] = 0;
   out_2585841718456555900[53] = 0;
   out_2585841718456555900[54] = 0;
   out_2585841718456555900[55] = 0;
   out_2585841718456555900[56] = 0;
   out_2585841718456555900[57] = 1;
   out_2585841718456555900[58] = 0;
   out_2585841718456555900[59] = 0;
   out_2585841718456555900[60] = 0;
   out_2585841718456555900[61] = 0;
   out_2585841718456555900[62] = 0;
   out_2585841718456555900[63] = 0;
   out_2585841718456555900[64] = 0;
   out_2585841718456555900[65] = 0;
   out_2585841718456555900[66] = dt;
   out_2585841718456555900[67] = 0;
   out_2585841718456555900[68] = 0;
   out_2585841718456555900[69] = 0;
   out_2585841718456555900[70] = 0;
   out_2585841718456555900[71] = 0;
   out_2585841718456555900[72] = 0;
   out_2585841718456555900[73] = 0;
   out_2585841718456555900[74] = 0;
   out_2585841718456555900[75] = 0;
   out_2585841718456555900[76] = 1;
   out_2585841718456555900[77] = 0;
   out_2585841718456555900[78] = 0;
   out_2585841718456555900[79] = 0;
   out_2585841718456555900[80] = 0;
   out_2585841718456555900[81] = 0;
   out_2585841718456555900[82] = 0;
   out_2585841718456555900[83] = 0;
   out_2585841718456555900[84] = 0;
   out_2585841718456555900[85] = dt;
   out_2585841718456555900[86] = 0;
   out_2585841718456555900[87] = 0;
   out_2585841718456555900[88] = 0;
   out_2585841718456555900[89] = 0;
   out_2585841718456555900[90] = 0;
   out_2585841718456555900[91] = 0;
   out_2585841718456555900[92] = 0;
   out_2585841718456555900[93] = 0;
   out_2585841718456555900[94] = 0;
   out_2585841718456555900[95] = 1;
   out_2585841718456555900[96] = 0;
   out_2585841718456555900[97] = 0;
   out_2585841718456555900[98] = 0;
   out_2585841718456555900[99] = 0;
   out_2585841718456555900[100] = 0;
   out_2585841718456555900[101] = 0;
   out_2585841718456555900[102] = 0;
   out_2585841718456555900[103] = 0;
   out_2585841718456555900[104] = dt;
   out_2585841718456555900[105] = 0;
   out_2585841718456555900[106] = 0;
   out_2585841718456555900[107] = 0;
   out_2585841718456555900[108] = 0;
   out_2585841718456555900[109] = 0;
   out_2585841718456555900[110] = 0;
   out_2585841718456555900[111] = 0;
   out_2585841718456555900[112] = 0;
   out_2585841718456555900[113] = 0;
   out_2585841718456555900[114] = 1;
   out_2585841718456555900[115] = 0;
   out_2585841718456555900[116] = 0;
   out_2585841718456555900[117] = 0;
   out_2585841718456555900[118] = 0;
   out_2585841718456555900[119] = 0;
   out_2585841718456555900[120] = 0;
   out_2585841718456555900[121] = 0;
   out_2585841718456555900[122] = 0;
   out_2585841718456555900[123] = 0;
   out_2585841718456555900[124] = 0;
   out_2585841718456555900[125] = 0;
   out_2585841718456555900[126] = 0;
   out_2585841718456555900[127] = 0;
   out_2585841718456555900[128] = 0;
   out_2585841718456555900[129] = 0;
   out_2585841718456555900[130] = 0;
   out_2585841718456555900[131] = 0;
   out_2585841718456555900[132] = 0;
   out_2585841718456555900[133] = 1;
   out_2585841718456555900[134] = 0;
   out_2585841718456555900[135] = 0;
   out_2585841718456555900[136] = 0;
   out_2585841718456555900[137] = 0;
   out_2585841718456555900[138] = 0;
   out_2585841718456555900[139] = 0;
   out_2585841718456555900[140] = 0;
   out_2585841718456555900[141] = 0;
   out_2585841718456555900[142] = 0;
   out_2585841718456555900[143] = 0;
   out_2585841718456555900[144] = 0;
   out_2585841718456555900[145] = 0;
   out_2585841718456555900[146] = 0;
   out_2585841718456555900[147] = 0;
   out_2585841718456555900[148] = 0;
   out_2585841718456555900[149] = 0;
   out_2585841718456555900[150] = 0;
   out_2585841718456555900[151] = 0;
   out_2585841718456555900[152] = 1;
   out_2585841718456555900[153] = 0;
   out_2585841718456555900[154] = 0;
   out_2585841718456555900[155] = 0;
   out_2585841718456555900[156] = 0;
   out_2585841718456555900[157] = 0;
   out_2585841718456555900[158] = 0;
   out_2585841718456555900[159] = 0;
   out_2585841718456555900[160] = 0;
   out_2585841718456555900[161] = 0;
   out_2585841718456555900[162] = 0;
   out_2585841718456555900[163] = 0;
   out_2585841718456555900[164] = 0;
   out_2585841718456555900[165] = 0;
   out_2585841718456555900[166] = 0;
   out_2585841718456555900[167] = 0;
   out_2585841718456555900[168] = 0;
   out_2585841718456555900[169] = 0;
   out_2585841718456555900[170] = 0;
   out_2585841718456555900[171] = 1;
   out_2585841718456555900[172] = 0;
   out_2585841718456555900[173] = 0;
   out_2585841718456555900[174] = 0;
   out_2585841718456555900[175] = 0;
   out_2585841718456555900[176] = 0;
   out_2585841718456555900[177] = 0;
   out_2585841718456555900[178] = 0;
   out_2585841718456555900[179] = 0;
   out_2585841718456555900[180] = 0;
   out_2585841718456555900[181] = 0;
   out_2585841718456555900[182] = 0;
   out_2585841718456555900[183] = 0;
   out_2585841718456555900[184] = 0;
   out_2585841718456555900[185] = 0;
   out_2585841718456555900[186] = 0;
   out_2585841718456555900[187] = 0;
   out_2585841718456555900[188] = 0;
   out_2585841718456555900[189] = 0;
   out_2585841718456555900[190] = 1;
   out_2585841718456555900[191] = 0;
   out_2585841718456555900[192] = 0;
   out_2585841718456555900[193] = 0;
   out_2585841718456555900[194] = 0;
   out_2585841718456555900[195] = 0;
   out_2585841718456555900[196] = 0;
   out_2585841718456555900[197] = 0;
   out_2585841718456555900[198] = 0;
   out_2585841718456555900[199] = 0;
   out_2585841718456555900[200] = 0;
   out_2585841718456555900[201] = 0;
   out_2585841718456555900[202] = 0;
   out_2585841718456555900[203] = 0;
   out_2585841718456555900[204] = 0;
   out_2585841718456555900[205] = 0;
   out_2585841718456555900[206] = 0;
   out_2585841718456555900[207] = 0;
   out_2585841718456555900[208] = 0;
   out_2585841718456555900[209] = 1;
   out_2585841718456555900[210] = 0;
   out_2585841718456555900[211] = 0;
   out_2585841718456555900[212] = 0;
   out_2585841718456555900[213] = 0;
   out_2585841718456555900[214] = 0;
   out_2585841718456555900[215] = 0;
   out_2585841718456555900[216] = 0;
   out_2585841718456555900[217] = 0;
   out_2585841718456555900[218] = 0;
   out_2585841718456555900[219] = 0;
   out_2585841718456555900[220] = 0;
   out_2585841718456555900[221] = 0;
   out_2585841718456555900[222] = 0;
   out_2585841718456555900[223] = 0;
   out_2585841718456555900[224] = 0;
   out_2585841718456555900[225] = 0;
   out_2585841718456555900[226] = 0;
   out_2585841718456555900[227] = 0;
   out_2585841718456555900[228] = 1;
   out_2585841718456555900[229] = 0;
   out_2585841718456555900[230] = 0;
   out_2585841718456555900[231] = 0;
   out_2585841718456555900[232] = 0;
   out_2585841718456555900[233] = 0;
   out_2585841718456555900[234] = 0;
   out_2585841718456555900[235] = 0;
   out_2585841718456555900[236] = 0;
   out_2585841718456555900[237] = 0;
   out_2585841718456555900[238] = 0;
   out_2585841718456555900[239] = 0;
   out_2585841718456555900[240] = 0;
   out_2585841718456555900[241] = 0;
   out_2585841718456555900[242] = 0;
   out_2585841718456555900[243] = 0;
   out_2585841718456555900[244] = 0;
   out_2585841718456555900[245] = 0;
   out_2585841718456555900[246] = 0;
   out_2585841718456555900[247] = 1;
   out_2585841718456555900[248] = 0;
   out_2585841718456555900[249] = 0;
   out_2585841718456555900[250] = 0;
   out_2585841718456555900[251] = 0;
   out_2585841718456555900[252] = 0;
   out_2585841718456555900[253] = 0;
   out_2585841718456555900[254] = 0;
   out_2585841718456555900[255] = 0;
   out_2585841718456555900[256] = 0;
   out_2585841718456555900[257] = 0;
   out_2585841718456555900[258] = 0;
   out_2585841718456555900[259] = 0;
   out_2585841718456555900[260] = 0;
   out_2585841718456555900[261] = 0;
   out_2585841718456555900[262] = 0;
   out_2585841718456555900[263] = 0;
   out_2585841718456555900[264] = 0;
   out_2585841718456555900[265] = 0;
   out_2585841718456555900[266] = 1;
   out_2585841718456555900[267] = 0;
   out_2585841718456555900[268] = 0;
   out_2585841718456555900[269] = 0;
   out_2585841718456555900[270] = 0;
   out_2585841718456555900[271] = 0;
   out_2585841718456555900[272] = 0;
   out_2585841718456555900[273] = 0;
   out_2585841718456555900[274] = 0;
   out_2585841718456555900[275] = 0;
   out_2585841718456555900[276] = 0;
   out_2585841718456555900[277] = 0;
   out_2585841718456555900[278] = 0;
   out_2585841718456555900[279] = 0;
   out_2585841718456555900[280] = 0;
   out_2585841718456555900[281] = 0;
   out_2585841718456555900[282] = 0;
   out_2585841718456555900[283] = 0;
   out_2585841718456555900[284] = 0;
   out_2585841718456555900[285] = 1;
   out_2585841718456555900[286] = 0;
   out_2585841718456555900[287] = 0;
   out_2585841718456555900[288] = 0;
   out_2585841718456555900[289] = 0;
   out_2585841718456555900[290] = 0;
   out_2585841718456555900[291] = 0;
   out_2585841718456555900[292] = 0;
   out_2585841718456555900[293] = 0;
   out_2585841718456555900[294] = 0;
   out_2585841718456555900[295] = 0;
   out_2585841718456555900[296] = 0;
   out_2585841718456555900[297] = 0;
   out_2585841718456555900[298] = 0;
   out_2585841718456555900[299] = 0;
   out_2585841718456555900[300] = 0;
   out_2585841718456555900[301] = 0;
   out_2585841718456555900[302] = 0;
   out_2585841718456555900[303] = 0;
   out_2585841718456555900[304] = 1;
   out_2585841718456555900[305] = 0;
   out_2585841718456555900[306] = 0;
   out_2585841718456555900[307] = 0;
   out_2585841718456555900[308] = 0;
   out_2585841718456555900[309] = 0;
   out_2585841718456555900[310] = 0;
   out_2585841718456555900[311] = 0;
   out_2585841718456555900[312] = 0;
   out_2585841718456555900[313] = 0;
   out_2585841718456555900[314] = 0;
   out_2585841718456555900[315] = 0;
   out_2585841718456555900[316] = 0;
   out_2585841718456555900[317] = 0;
   out_2585841718456555900[318] = 0;
   out_2585841718456555900[319] = 0;
   out_2585841718456555900[320] = 0;
   out_2585841718456555900[321] = 0;
   out_2585841718456555900[322] = 0;
   out_2585841718456555900[323] = 1;
}
void h_4(double *state, double *unused, double *out_7879074859447355491) {
   out_7879074859447355491[0] = state[6] + state[9];
   out_7879074859447355491[1] = state[7] + state[10];
   out_7879074859447355491[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2477216195043438731) {
   out_2477216195043438731[0] = 0;
   out_2477216195043438731[1] = 0;
   out_2477216195043438731[2] = 0;
   out_2477216195043438731[3] = 0;
   out_2477216195043438731[4] = 0;
   out_2477216195043438731[5] = 0;
   out_2477216195043438731[6] = 1;
   out_2477216195043438731[7] = 0;
   out_2477216195043438731[8] = 0;
   out_2477216195043438731[9] = 1;
   out_2477216195043438731[10] = 0;
   out_2477216195043438731[11] = 0;
   out_2477216195043438731[12] = 0;
   out_2477216195043438731[13] = 0;
   out_2477216195043438731[14] = 0;
   out_2477216195043438731[15] = 0;
   out_2477216195043438731[16] = 0;
   out_2477216195043438731[17] = 0;
   out_2477216195043438731[18] = 0;
   out_2477216195043438731[19] = 0;
   out_2477216195043438731[20] = 0;
   out_2477216195043438731[21] = 0;
   out_2477216195043438731[22] = 0;
   out_2477216195043438731[23] = 0;
   out_2477216195043438731[24] = 0;
   out_2477216195043438731[25] = 1;
   out_2477216195043438731[26] = 0;
   out_2477216195043438731[27] = 0;
   out_2477216195043438731[28] = 1;
   out_2477216195043438731[29] = 0;
   out_2477216195043438731[30] = 0;
   out_2477216195043438731[31] = 0;
   out_2477216195043438731[32] = 0;
   out_2477216195043438731[33] = 0;
   out_2477216195043438731[34] = 0;
   out_2477216195043438731[35] = 0;
   out_2477216195043438731[36] = 0;
   out_2477216195043438731[37] = 0;
   out_2477216195043438731[38] = 0;
   out_2477216195043438731[39] = 0;
   out_2477216195043438731[40] = 0;
   out_2477216195043438731[41] = 0;
   out_2477216195043438731[42] = 0;
   out_2477216195043438731[43] = 0;
   out_2477216195043438731[44] = 1;
   out_2477216195043438731[45] = 0;
   out_2477216195043438731[46] = 0;
   out_2477216195043438731[47] = 1;
   out_2477216195043438731[48] = 0;
   out_2477216195043438731[49] = 0;
   out_2477216195043438731[50] = 0;
   out_2477216195043438731[51] = 0;
   out_2477216195043438731[52] = 0;
   out_2477216195043438731[53] = 0;
}
void h_10(double *state, double *unused, double *out_2609678945296250804) {
   out_2609678945296250804[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2609678945296250804[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2609678945296250804[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6604444469350949959) {
   out_6604444469350949959[0] = 0;
   out_6604444469350949959[1] = 9.8100000000000005*cos(state[1]);
   out_6604444469350949959[2] = 0;
   out_6604444469350949959[3] = 0;
   out_6604444469350949959[4] = -state[8];
   out_6604444469350949959[5] = state[7];
   out_6604444469350949959[6] = 0;
   out_6604444469350949959[7] = state[5];
   out_6604444469350949959[8] = -state[4];
   out_6604444469350949959[9] = 0;
   out_6604444469350949959[10] = 0;
   out_6604444469350949959[11] = 0;
   out_6604444469350949959[12] = 1;
   out_6604444469350949959[13] = 0;
   out_6604444469350949959[14] = 0;
   out_6604444469350949959[15] = 1;
   out_6604444469350949959[16] = 0;
   out_6604444469350949959[17] = 0;
   out_6604444469350949959[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6604444469350949959[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6604444469350949959[20] = 0;
   out_6604444469350949959[21] = state[8];
   out_6604444469350949959[22] = 0;
   out_6604444469350949959[23] = -state[6];
   out_6604444469350949959[24] = -state[5];
   out_6604444469350949959[25] = 0;
   out_6604444469350949959[26] = state[3];
   out_6604444469350949959[27] = 0;
   out_6604444469350949959[28] = 0;
   out_6604444469350949959[29] = 0;
   out_6604444469350949959[30] = 0;
   out_6604444469350949959[31] = 1;
   out_6604444469350949959[32] = 0;
   out_6604444469350949959[33] = 0;
   out_6604444469350949959[34] = 1;
   out_6604444469350949959[35] = 0;
   out_6604444469350949959[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6604444469350949959[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6604444469350949959[38] = 0;
   out_6604444469350949959[39] = -state[7];
   out_6604444469350949959[40] = state[6];
   out_6604444469350949959[41] = 0;
   out_6604444469350949959[42] = state[4];
   out_6604444469350949959[43] = -state[3];
   out_6604444469350949959[44] = 0;
   out_6604444469350949959[45] = 0;
   out_6604444469350949959[46] = 0;
   out_6604444469350949959[47] = 0;
   out_6604444469350949959[48] = 0;
   out_6604444469350949959[49] = 0;
   out_6604444469350949959[50] = 1;
   out_6604444469350949959[51] = 0;
   out_6604444469350949959[52] = 0;
   out_6604444469350949959[53] = 1;
}
void h_13(double *state, double *unused, double *out_4854758582756767043) {
   out_4854758582756767043[0] = state[3];
   out_4854758582756767043[1] = state[4];
   out_4854758582756767043[2] = state[5];
}
void H_13(double *state, double *unused, double *out_735057630288894070) {
   out_735057630288894070[0] = 0;
   out_735057630288894070[1] = 0;
   out_735057630288894070[2] = 0;
   out_735057630288894070[3] = 1;
   out_735057630288894070[4] = 0;
   out_735057630288894070[5] = 0;
   out_735057630288894070[6] = 0;
   out_735057630288894070[7] = 0;
   out_735057630288894070[8] = 0;
   out_735057630288894070[9] = 0;
   out_735057630288894070[10] = 0;
   out_735057630288894070[11] = 0;
   out_735057630288894070[12] = 0;
   out_735057630288894070[13] = 0;
   out_735057630288894070[14] = 0;
   out_735057630288894070[15] = 0;
   out_735057630288894070[16] = 0;
   out_735057630288894070[17] = 0;
   out_735057630288894070[18] = 0;
   out_735057630288894070[19] = 0;
   out_735057630288894070[20] = 0;
   out_735057630288894070[21] = 0;
   out_735057630288894070[22] = 1;
   out_735057630288894070[23] = 0;
   out_735057630288894070[24] = 0;
   out_735057630288894070[25] = 0;
   out_735057630288894070[26] = 0;
   out_735057630288894070[27] = 0;
   out_735057630288894070[28] = 0;
   out_735057630288894070[29] = 0;
   out_735057630288894070[30] = 0;
   out_735057630288894070[31] = 0;
   out_735057630288894070[32] = 0;
   out_735057630288894070[33] = 0;
   out_735057630288894070[34] = 0;
   out_735057630288894070[35] = 0;
   out_735057630288894070[36] = 0;
   out_735057630288894070[37] = 0;
   out_735057630288894070[38] = 0;
   out_735057630288894070[39] = 0;
   out_735057630288894070[40] = 0;
   out_735057630288894070[41] = 1;
   out_735057630288894070[42] = 0;
   out_735057630288894070[43] = 0;
   out_735057630288894070[44] = 0;
   out_735057630288894070[45] = 0;
   out_735057630288894070[46] = 0;
   out_735057630288894070[47] = 0;
   out_735057630288894070[48] = 0;
   out_735057630288894070[49] = 0;
   out_735057630288894070[50] = 0;
   out_735057630288894070[51] = 0;
   out_735057630288894070[52] = 0;
   out_735057630288894070[53] = 0;
}
void h_14(double *state, double *unused, double *out_6697923167830866865) {
   out_6697923167830866865[0] = state[6];
   out_6697923167830866865[1] = state[7];
   out_6697923167830866865[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1486024661296045798) {
   out_1486024661296045798[0] = 0;
   out_1486024661296045798[1] = 0;
   out_1486024661296045798[2] = 0;
   out_1486024661296045798[3] = 0;
   out_1486024661296045798[4] = 0;
   out_1486024661296045798[5] = 0;
   out_1486024661296045798[6] = 1;
   out_1486024661296045798[7] = 0;
   out_1486024661296045798[8] = 0;
   out_1486024661296045798[9] = 0;
   out_1486024661296045798[10] = 0;
   out_1486024661296045798[11] = 0;
   out_1486024661296045798[12] = 0;
   out_1486024661296045798[13] = 0;
   out_1486024661296045798[14] = 0;
   out_1486024661296045798[15] = 0;
   out_1486024661296045798[16] = 0;
   out_1486024661296045798[17] = 0;
   out_1486024661296045798[18] = 0;
   out_1486024661296045798[19] = 0;
   out_1486024661296045798[20] = 0;
   out_1486024661296045798[21] = 0;
   out_1486024661296045798[22] = 0;
   out_1486024661296045798[23] = 0;
   out_1486024661296045798[24] = 0;
   out_1486024661296045798[25] = 1;
   out_1486024661296045798[26] = 0;
   out_1486024661296045798[27] = 0;
   out_1486024661296045798[28] = 0;
   out_1486024661296045798[29] = 0;
   out_1486024661296045798[30] = 0;
   out_1486024661296045798[31] = 0;
   out_1486024661296045798[32] = 0;
   out_1486024661296045798[33] = 0;
   out_1486024661296045798[34] = 0;
   out_1486024661296045798[35] = 0;
   out_1486024661296045798[36] = 0;
   out_1486024661296045798[37] = 0;
   out_1486024661296045798[38] = 0;
   out_1486024661296045798[39] = 0;
   out_1486024661296045798[40] = 0;
   out_1486024661296045798[41] = 0;
   out_1486024661296045798[42] = 0;
   out_1486024661296045798[43] = 0;
   out_1486024661296045798[44] = 1;
   out_1486024661296045798[45] = 0;
   out_1486024661296045798[46] = 0;
   out_1486024661296045798[47] = 0;
   out_1486024661296045798[48] = 0;
   out_1486024661296045798[49] = 0;
   out_1486024661296045798[50] = 0;
   out_1486024661296045798[51] = 0;
   out_1486024661296045798[52] = 0;
   out_1486024661296045798[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3776217962159825712) {
  err_fun(nom_x, delta_x, out_3776217962159825712);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_838326120936530935) {
  inv_err_fun(nom_x, true_x, out_838326120936530935);
}
void pose_H_mod_fun(double *state, double *out_3231377197098151338) {
  H_mod_fun(state, out_3231377197098151338);
}
void pose_f_fun(double *state, double dt, double *out_4330621084971378974) {
  f_fun(state,  dt, out_4330621084971378974);
}
void pose_F_fun(double *state, double dt, double *out_2585841718456555900) {
  F_fun(state,  dt, out_2585841718456555900);
}
void pose_h_4(double *state, double *unused, double *out_7879074859447355491) {
  h_4(state, unused, out_7879074859447355491);
}
void pose_H_4(double *state, double *unused, double *out_2477216195043438731) {
  H_4(state, unused, out_2477216195043438731);
}
void pose_h_10(double *state, double *unused, double *out_2609678945296250804) {
  h_10(state, unused, out_2609678945296250804);
}
void pose_H_10(double *state, double *unused, double *out_6604444469350949959) {
  H_10(state, unused, out_6604444469350949959);
}
void pose_h_13(double *state, double *unused, double *out_4854758582756767043) {
  h_13(state, unused, out_4854758582756767043);
}
void pose_H_13(double *state, double *unused, double *out_735057630288894070) {
  H_13(state, unused, out_735057630288894070);
}
void pose_h_14(double *state, double *unused, double *out_6697923167830866865) {
  h_14(state, unused, out_6697923167830866865);
}
void pose_H_14(double *state, double *unused, double *out_1486024661296045798) {
  H_14(state, unused, out_1486024661296045798);
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
