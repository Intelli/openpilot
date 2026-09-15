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
void err_fun(double *nom_x, double *delta_x, double *out_3128060725060609626) {
   out_3128060725060609626[0] = delta_x[0] + nom_x[0];
   out_3128060725060609626[1] = delta_x[1] + nom_x[1];
   out_3128060725060609626[2] = delta_x[2] + nom_x[2];
   out_3128060725060609626[3] = delta_x[3] + nom_x[3];
   out_3128060725060609626[4] = delta_x[4] + nom_x[4];
   out_3128060725060609626[5] = delta_x[5] + nom_x[5];
   out_3128060725060609626[6] = delta_x[6] + nom_x[6];
   out_3128060725060609626[7] = delta_x[7] + nom_x[7];
   out_3128060725060609626[8] = delta_x[8] + nom_x[8];
   out_3128060725060609626[9] = delta_x[9] + nom_x[9];
   out_3128060725060609626[10] = delta_x[10] + nom_x[10];
   out_3128060725060609626[11] = delta_x[11] + nom_x[11];
   out_3128060725060609626[12] = delta_x[12] + nom_x[12];
   out_3128060725060609626[13] = delta_x[13] + nom_x[13];
   out_3128060725060609626[14] = delta_x[14] + nom_x[14];
   out_3128060725060609626[15] = delta_x[15] + nom_x[15];
   out_3128060725060609626[16] = delta_x[16] + nom_x[16];
   out_3128060725060609626[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_962437773882614248) {
   out_962437773882614248[0] = -nom_x[0] + true_x[0];
   out_962437773882614248[1] = -nom_x[1] + true_x[1];
   out_962437773882614248[2] = -nom_x[2] + true_x[2];
   out_962437773882614248[3] = -nom_x[3] + true_x[3];
   out_962437773882614248[4] = -nom_x[4] + true_x[4];
   out_962437773882614248[5] = -nom_x[5] + true_x[5];
   out_962437773882614248[6] = -nom_x[6] + true_x[6];
   out_962437773882614248[7] = -nom_x[7] + true_x[7];
   out_962437773882614248[8] = -nom_x[8] + true_x[8];
   out_962437773882614248[9] = -nom_x[9] + true_x[9];
   out_962437773882614248[10] = -nom_x[10] + true_x[10];
   out_962437773882614248[11] = -nom_x[11] + true_x[11];
   out_962437773882614248[12] = -nom_x[12] + true_x[12];
   out_962437773882614248[13] = -nom_x[13] + true_x[13];
   out_962437773882614248[14] = -nom_x[14] + true_x[14];
   out_962437773882614248[15] = -nom_x[15] + true_x[15];
   out_962437773882614248[16] = -nom_x[16] + true_x[16];
   out_962437773882614248[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1378391307355774028) {
   out_1378391307355774028[0] = 1.0;
   out_1378391307355774028[1] = 0.0;
   out_1378391307355774028[2] = 0.0;
   out_1378391307355774028[3] = 0.0;
   out_1378391307355774028[4] = 0.0;
   out_1378391307355774028[5] = 0.0;
   out_1378391307355774028[6] = 0.0;
   out_1378391307355774028[7] = 0.0;
   out_1378391307355774028[8] = 0.0;
   out_1378391307355774028[9] = 0.0;
   out_1378391307355774028[10] = 0.0;
   out_1378391307355774028[11] = 0.0;
   out_1378391307355774028[12] = 0.0;
   out_1378391307355774028[13] = 0.0;
   out_1378391307355774028[14] = 0.0;
   out_1378391307355774028[15] = 0.0;
   out_1378391307355774028[16] = 0.0;
   out_1378391307355774028[17] = 0.0;
   out_1378391307355774028[18] = 0.0;
   out_1378391307355774028[19] = 1.0;
   out_1378391307355774028[20] = 0.0;
   out_1378391307355774028[21] = 0.0;
   out_1378391307355774028[22] = 0.0;
   out_1378391307355774028[23] = 0.0;
   out_1378391307355774028[24] = 0.0;
   out_1378391307355774028[25] = 0.0;
   out_1378391307355774028[26] = 0.0;
   out_1378391307355774028[27] = 0.0;
   out_1378391307355774028[28] = 0.0;
   out_1378391307355774028[29] = 0.0;
   out_1378391307355774028[30] = 0.0;
   out_1378391307355774028[31] = 0.0;
   out_1378391307355774028[32] = 0.0;
   out_1378391307355774028[33] = 0.0;
   out_1378391307355774028[34] = 0.0;
   out_1378391307355774028[35] = 0.0;
   out_1378391307355774028[36] = 0.0;
   out_1378391307355774028[37] = 0.0;
   out_1378391307355774028[38] = 1.0;
   out_1378391307355774028[39] = 0.0;
   out_1378391307355774028[40] = 0.0;
   out_1378391307355774028[41] = 0.0;
   out_1378391307355774028[42] = 0.0;
   out_1378391307355774028[43] = 0.0;
   out_1378391307355774028[44] = 0.0;
   out_1378391307355774028[45] = 0.0;
   out_1378391307355774028[46] = 0.0;
   out_1378391307355774028[47] = 0.0;
   out_1378391307355774028[48] = 0.0;
   out_1378391307355774028[49] = 0.0;
   out_1378391307355774028[50] = 0.0;
   out_1378391307355774028[51] = 0.0;
   out_1378391307355774028[52] = 0.0;
   out_1378391307355774028[53] = 0.0;
   out_1378391307355774028[54] = 0.0;
   out_1378391307355774028[55] = 0.0;
   out_1378391307355774028[56] = 0.0;
   out_1378391307355774028[57] = 1.0;
   out_1378391307355774028[58] = 0.0;
   out_1378391307355774028[59] = 0.0;
   out_1378391307355774028[60] = 0.0;
   out_1378391307355774028[61] = 0.0;
   out_1378391307355774028[62] = 0.0;
   out_1378391307355774028[63] = 0.0;
   out_1378391307355774028[64] = 0.0;
   out_1378391307355774028[65] = 0.0;
   out_1378391307355774028[66] = 0.0;
   out_1378391307355774028[67] = 0.0;
   out_1378391307355774028[68] = 0.0;
   out_1378391307355774028[69] = 0.0;
   out_1378391307355774028[70] = 0.0;
   out_1378391307355774028[71] = 0.0;
   out_1378391307355774028[72] = 0.0;
   out_1378391307355774028[73] = 0.0;
   out_1378391307355774028[74] = 0.0;
   out_1378391307355774028[75] = 0.0;
   out_1378391307355774028[76] = 1.0;
   out_1378391307355774028[77] = 0.0;
   out_1378391307355774028[78] = 0.0;
   out_1378391307355774028[79] = 0.0;
   out_1378391307355774028[80] = 0.0;
   out_1378391307355774028[81] = 0.0;
   out_1378391307355774028[82] = 0.0;
   out_1378391307355774028[83] = 0.0;
   out_1378391307355774028[84] = 0.0;
   out_1378391307355774028[85] = 0.0;
   out_1378391307355774028[86] = 0.0;
   out_1378391307355774028[87] = 0.0;
   out_1378391307355774028[88] = 0.0;
   out_1378391307355774028[89] = 0.0;
   out_1378391307355774028[90] = 0.0;
   out_1378391307355774028[91] = 0.0;
   out_1378391307355774028[92] = 0.0;
   out_1378391307355774028[93] = 0.0;
   out_1378391307355774028[94] = 0.0;
   out_1378391307355774028[95] = 1.0;
   out_1378391307355774028[96] = 0.0;
   out_1378391307355774028[97] = 0.0;
   out_1378391307355774028[98] = 0.0;
   out_1378391307355774028[99] = 0.0;
   out_1378391307355774028[100] = 0.0;
   out_1378391307355774028[101] = 0.0;
   out_1378391307355774028[102] = 0.0;
   out_1378391307355774028[103] = 0.0;
   out_1378391307355774028[104] = 0.0;
   out_1378391307355774028[105] = 0.0;
   out_1378391307355774028[106] = 0.0;
   out_1378391307355774028[107] = 0.0;
   out_1378391307355774028[108] = 0.0;
   out_1378391307355774028[109] = 0.0;
   out_1378391307355774028[110] = 0.0;
   out_1378391307355774028[111] = 0.0;
   out_1378391307355774028[112] = 0.0;
   out_1378391307355774028[113] = 0.0;
   out_1378391307355774028[114] = 1.0;
   out_1378391307355774028[115] = 0.0;
   out_1378391307355774028[116] = 0.0;
   out_1378391307355774028[117] = 0.0;
   out_1378391307355774028[118] = 0.0;
   out_1378391307355774028[119] = 0.0;
   out_1378391307355774028[120] = 0.0;
   out_1378391307355774028[121] = 0.0;
   out_1378391307355774028[122] = 0.0;
   out_1378391307355774028[123] = 0.0;
   out_1378391307355774028[124] = 0.0;
   out_1378391307355774028[125] = 0.0;
   out_1378391307355774028[126] = 0.0;
   out_1378391307355774028[127] = 0.0;
   out_1378391307355774028[128] = 0.0;
   out_1378391307355774028[129] = 0.0;
   out_1378391307355774028[130] = 0.0;
   out_1378391307355774028[131] = 0.0;
   out_1378391307355774028[132] = 0.0;
   out_1378391307355774028[133] = 1.0;
   out_1378391307355774028[134] = 0.0;
   out_1378391307355774028[135] = 0.0;
   out_1378391307355774028[136] = 0.0;
   out_1378391307355774028[137] = 0.0;
   out_1378391307355774028[138] = 0.0;
   out_1378391307355774028[139] = 0.0;
   out_1378391307355774028[140] = 0.0;
   out_1378391307355774028[141] = 0.0;
   out_1378391307355774028[142] = 0.0;
   out_1378391307355774028[143] = 0.0;
   out_1378391307355774028[144] = 0.0;
   out_1378391307355774028[145] = 0.0;
   out_1378391307355774028[146] = 0.0;
   out_1378391307355774028[147] = 0.0;
   out_1378391307355774028[148] = 0.0;
   out_1378391307355774028[149] = 0.0;
   out_1378391307355774028[150] = 0.0;
   out_1378391307355774028[151] = 0.0;
   out_1378391307355774028[152] = 1.0;
   out_1378391307355774028[153] = 0.0;
   out_1378391307355774028[154] = 0.0;
   out_1378391307355774028[155] = 0.0;
   out_1378391307355774028[156] = 0.0;
   out_1378391307355774028[157] = 0.0;
   out_1378391307355774028[158] = 0.0;
   out_1378391307355774028[159] = 0.0;
   out_1378391307355774028[160] = 0.0;
   out_1378391307355774028[161] = 0.0;
   out_1378391307355774028[162] = 0.0;
   out_1378391307355774028[163] = 0.0;
   out_1378391307355774028[164] = 0.0;
   out_1378391307355774028[165] = 0.0;
   out_1378391307355774028[166] = 0.0;
   out_1378391307355774028[167] = 0.0;
   out_1378391307355774028[168] = 0.0;
   out_1378391307355774028[169] = 0.0;
   out_1378391307355774028[170] = 0.0;
   out_1378391307355774028[171] = 1.0;
   out_1378391307355774028[172] = 0.0;
   out_1378391307355774028[173] = 0.0;
   out_1378391307355774028[174] = 0.0;
   out_1378391307355774028[175] = 0.0;
   out_1378391307355774028[176] = 0.0;
   out_1378391307355774028[177] = 0.0;
   out_1378391307355774028[178] = 0.0;
   out_1378391307355774028[179] = 0.0;
   out_1378391307355774028[180] = 0.0;
   out_1378391307355774028[181] = 0.0;
   out_1378391307355774028[182] = 0.0;
   out_1378391307355774028[183] = 0.0;
   out_1378391307355774028[184] = 0.0;
   out_1378391307355774028[185] = 0.0;
   out_1378391307355774028[186] = 0.0;
   out_1378391307355774028[187] = 0.0;
   out_1378391307355774028[188] = 0.0;
   out_1378391307355774028[189] = 0.0;
   out_1378391307355774028[190] = 1.0;
   out_1378391307355774028[191] = 0.0;
   out_1378391307355774028[192] = 0.0;
   out_1378391307355774028[193] = 0.0;
   out_1378391307355774028[194] = 0.0;
   out_1378391307355774028[195] = 0.0;
   out_1378391307355774028[196] = 0.0;
   out_1378391307355774028[197] = 0.0;
   out_1378391307355774028[198] = 0.0;
   out_1378391307355774028[199] = 0.0;
   out_1378391307355774028[200] = 0.0;
   out_1378391307355774028[201] = 0.0;
   out_1378391307355774028[202] = 0.0;
   out_1378391307355774028[203] = 0.0;
   out_1378391307355774028[204] = 0.0;
   out_1378391307355774028[205] = 0.0;
   out_1378391307355774028[206] = 0.0;
   out_1378391307355774028[207] = 0.0;
   out_1378391307355774028[208] = 0.0;
   out_1378391307355774028[209] = 1.0;
   out_1378391307355774028[210] = 0.0;
   out_1378391307355774028[211] = 0.0;
   out_1378391307355774028[212] = 0.0;
   out_1378391307355774028[213] = 0.0;
   out_1378391307355774028[214] = 0.0;
   out_1378391307355774028[215] = 0.0;
   out_1378391307355774028[216] = 0.0;
   out_1378391307355774028[217] = 0.0;
   out_1378391307355774028[218] = 0.0;
   out_1378391307355774028[219] = 0.0;
   out_1378391307355774028[220] = 0.0;
   out_1378391307355774028[221] = 0.0;
   out_1378391307355774028[222] = 0.0;
   out_1378391307355774028[223] = 0.0;
   out_1378391307355774028[224] = 0.0;
   out_1378391307355774028[225] = 0.0;
   out_1378391307355774028[226] = 0.0;
   out_1378391307355774028[227] = 0.0;
   out_1378391307355774028[228] = 1.0;
   out_1378391307355774028[229] = 0.0;
   out_1378391307355774028[230] = 0.0;
   out_1378391307355774028[231] = 0.0;
   out_1378391307355774028[232] = 0.0;
   out_1378391307355774028[233] = 0.0;
   out_1378391307355774028[234] = 0.0;
   out_1378391307355774028[235] = 0.0;
   out_1378391307355774028[236] = 0.0;
   out_1378391307355774028[237] = 0.0;
   out_1378391307355774028[238] = 0.0;
   out_1378391307355774028[239] = 0.0;
   out_1378391307355774028[240] = 0.0;
   out_1378391307355774028[241] = 0.0;
   out_1378391307355774028[242] = 0.0;
   out_1378391307355774028[243] = 0.0;
   out_1378391307355774028[244] = 0.0;
   out_1378391307355774028[245] = 0.0;
   out_1378391307355774028[246] = 0.0;
   out_1378391307355774028[247] = 1.0;
   out_1378391307355774028[248] = 0.0;
   out_1378391307355774028[249] = 0.0;
   out_1378391307355774028[250] = 0.0;
   out_1378391307355774028[251] = 0.0;
   out_1378391307355774028[252] = 0.0;
   out_1378391307355774028[253] = 0.0;
   out_1378391307355774028[254] = 0.0;
   out_1378391307355774028[255] = 0.0;
   out_1378391307355774028[256] = 0.0;
   out_1378391307355774028[257] = 0.0;
   out_1378391307355774028[258] = 0.0;
   out_1378391307355774028[259] = 0.0;
   out_1378391307355774028[260] = 0.0;
   out_1378391307355774028[261] = 0.0;
   out_1378391307355774028[262] = 0.0;
   out_1378391307355774028[263] = 0.0;
   out_1378391307355774028[264] = 0.0;
   out_1378391307355774028[265] = 0.0;
   out_1378391307355774028[266] = 1.0;
   out_1378391307355774028[267] = 0.0;
   out_1378391307355774028[268] = 0.0;
   out_1378391307355774028[269] = 0.0;
   out_1378391307355774028[270] = 0.0;
   out_1378391307355774028[271] = 0.0;
   out_1378391307355774028[272] = 0.0;
   out_1378391307355774028[273] = 0.0;
   out_1378391307355774028[274] = 0.0;
   out_1378391307355774028[275] = 0.0;
   out_1378391307355774028[276] = 0.0;
   out_1378391307355774028[277] = 0.0;
   out_1378391307355774028[278] = 0.0;
   out_1378391307355774028[279] = 0.0;
   out_1378391307355774028[280] = 0.0;
   out_1378391307355774028[281] = 0.0;
   out_1378391307355774028[282] = 0.0;
   out_1378391307355774028[283] = 0.0;
   out_1378391307355774028[284] = 0.0;
   out_1378391307355774028[285] = 1.0;
   out_1378391307355774028[286] = 0.0;
   out_1378391307355774028[287] = 0.0;
   out_1378391307355774028[288] = 0.0;
   out_1378391307355774028[289] = 0.0;
   out_1378391307355774028[290] = 0.0;
   out_1378391307355774028[291] = 0.0;
   out_1378391307355774028[292] = 0.0;
   out_1378391307355774028[293] = 0.0;
   out_1378391307355774028[294] = 0.0;
   out_1378391307355774028[295] = 0.0;
   out_1378391307355774028[296] = 0.0;
   out_1378391307355774028[297] = 0.0;
   out_1378391307355774028[298] = 0.0;
   out_1378391307355774028[299] = 0.0;
   out_1378391307355774028[300] = 0.0;
   out_1378391307355774028[301] = 0.0;
   out_1378391307355774028[302] = 0.0;
   out_1378391307355774028[303] = 0.0;
   out_1378391307355774028[304] = 1.0;
   out_1378391307355774028[305] = 0.0;
   out_1378391307355774028[306] = 0.0;
   out_1378391307355774028[307] = 0.0;
   out_1378391307355774028[308] = 0.0;
   out_1378391307355774028[309] = 0.0;
   out_1378391307355774028[310] = 0.0;
   out_1378391307355774028[311] = 0.0;
   out_1378391307355774028[312] = 0.0;
   out_1378391307355774028[313] = 0.0;
   out_1378391307355774028[314] = 0.0;
   out_1378391307355774028[315] = 0.0;
   out_1378391307355774028[316] = 0.0;
   out_1378391307355774028[317] = 0.0;
   out_1378391307355774028[318] = 0.0;
   out_1378391307355774028[319] = 0.0;
   out_1378391307355774028[320] = 0.0;
   out_1378391307355774028[321] = 0.0;
   out_1378391307355774028[322] = 0.0;
   out_1378391307355774028[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7600705386146157547) {
   out_7600705386146157547[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7600705386146157547[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7600705386146157547[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7600705386146157547[3] = dt*state[12] + state[3];
   out_7600705386146157547[4] = dt*state[13] + state[4];
   out_7600705386146157547[5] = dt*state[14] + state[5];
   out_7600705386146157547[6] = state[6];
   out_7600705386146157547[7] = state[7];
   out_7600705386146157547[8] = state[8];
   out_7600705386146157547[9] = state[9];
   out_7600705386146157547[10] = state[10];
   out_7600705386146157547[11] = state[11];
   out_7600705386146157547[12] = state[12];
   out_7600705386146157547[13] = state[13];
   out_7600705386146157547[14] = state[14];
   out_7600705386146157547[15] = state[15];
   out_7600705386146157547[16] = state[16];
   out_7600705386146157547[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5012584798577878241) {
   out_5012584798577878241[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5012584798577878241[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5012584798577878241[2] = 0;
   out_5012584798577878241[3] = 0;
   out_5012584798577878241[4] = 0;
   out_5012584798577878241[5] = 0;
   out_5012584798577878241[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5012584798577878241[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5012584798577878241[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5012584798577878241[9] = 0;
   out_5012584798577878241[10] = 0;
   out_5012584798577878241[11] = 0;
   out_5012584798577878241[12] = 0;
   out_5012584798577878241[13] = 0;
   out_5012584798577878241[14] = 0;
   out_5012584798577878241[15] = 0;
   out_5012584798577878241[16] = 0;
   out_5012584798577878241[17] = 0;
   out_5012584798577878241[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5012584798577878241[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5012584798577878241[20] = 0;
   out_5012584798577878241[21] = 0;
   out_5012584798577878241[22] = 0;
   out_5012584798577878241[23] = 0;
   out_5012584798577878241[24] = 0;
   out_5012584798577878241[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5012584798577878241[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5012584798577878241[27] = 0;
   out_5012584798577878241[28] = 0;
   out_5012584798577878241[29] = 0;
   out_5012584798577878241[30] = 0;
   out_5012584798577878241[31] = 0;
   out_5012584798577878241[32] = 0;
   out_5012584798577878241[33] = 0;
   out_5012584798577878241[34] = 0;
   out_5012584798577878241[35] = 0;
   out_5012584798577878241[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5012584798577878241[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5012584798577878241[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5012584798577878241[39] = 0;
   out_5012584798577878241[40] = 0;
   out_5012584798577878241[41] = 0;
   out_5012584798577878241[42] = 0;
   out_5012584798577878241[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5012584798577878241[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5012584798577878241[45] = 0;
   out_5012584798577878241[46] = 0;
   out_5012584798577878241[47] = 0;
   out_5012584798577878241[48] = 0;
   out_5012584798577878241[49] = 0;
   out_5012584798577878241[50] = 0;
   out_5012584798577878241[51] = 0;
   out_5012584798577878241[52] = 0;
   out_5012584798577878241[53] = 0;
   out_5012584798577878241[54] = 0;
   out_5012584798577878241[55] = 0;
   out_5012584798577878241[56] = 0;
   out_5012584798577878241[57] = 1;
   out_5012584798577878241[58] = 0;
   out_5012584798577878241[59] = 0;
   out_5012584798577878241[60] = 0;
   out_5012584798577878241[61] = 0;
   out_5012584798577878241[62] = 0;
   out_5012584798577878241[63] = 0;
   out_5012584798577878241[64] = 0;
   out_5012584798577878241[65] = 0;
   out_5012584798577878241[66] = dt;
   out_5012584798577878241[67] = 0;
   out_5012584798577878241[68] = 0;
   out_5012584798577878241[69] = 0;
   out_5012584798577878241[70] = 0;
   out_5012584798577878241[71] = 0;
   out_5012584798577878241[72] = 0;
   out_5012584798577878241[73] = 0;
   out_5012584798577878241[74] = 0;
   out_5012584798577878241[75] = 0;
   out_5012584798577878241[76] = 1;
   out_5012584798577878241[77] = 0;
   out_5012584798577878241[78] = 0;
   out_5012584798577878241[79] = 0;
   out_5012584798577878241[80] = 0;
   out_5012584798577878241[81] = 0;
   out_5012584798577878241[82] = 0;
   out_5012584798577878241[83] = 0;
   out_5012584798577878241[84] = 0;
   out_5012584798577878241[85] = dt;
   out_5012584798577878241[86] = 0;
   out_5012584798577878241[87] = 0;
   out_5012584798577878241[88] = 0;
   out_5012584798577878241[89] = 0;
   out_5012584798577878241[90] = 0;
   out_5012584798577878241[91] = 0;
   out_5012584798577878241[92] = 0;
   out_5012584798577878241[93] = 0;
   out_5012584798577878241[94] = 0;
   out_5012584798577878241[95] = 1;
   out_5012584798577878241[96] = 0;
   out_5012584798577878241[97] = 0;
   out_5012584798577878241[98] = 0;
   out_5012584798577878241[99] = 0;
   out_5012584798577878241[100] = 0;
   out_5012584798577878241[101] = 0;
   out_5012584798577878241[102] = 0;
   out_5012584798577878241[103] = 0;
   out_5012584798577878241[104] = dt;
   out_5012584798577878241[105] = 0;
   out_5012584798577878241[106] = 0;
   out_5012584798577878241[107] = 0;
   out_5012584798577878241[108] = 0;
   out_5012584798577878241[109] = 0;
   out_5012584798577878241[110] = 0;
   out_5012584798577878241[111] = 0;
   out_5012584798577878241[112] = 0;
   out_5012584798577878241[113] = 0;
   out_5012584798577878241[114] = 1;
   out_5012584798577878241[115] = 0;
   out_5012584798577878241[116] = 0;
   out_5012584798577878241[117] = 0;
   out_5012584798577878241[118] = 0;
   out_5012584798577878241[119] = 0;
   out_5012584798577878241[120] = 0;
   out_5012584798577878241[121] = 0;
   out_5012584798577878241[122] = 0;
   out_5012584798577878241[123] = 0;
   out_5012584798577878241[124] = 0;
   out_5012584798577878241[125] = 0;
   out_5012584798577878241[126] = 0;
   out_5012584798577878241[127] = 0;
   out_5012584798577878241[128] = 0;
   out_5012584798577878241[129] = 0;
   out_5012584798577878241[130] = 0;
   out_5012584798577878241[131] = 0;
   out_5012584798577878241[132] = 0;
   out_5012584798577878241[133] = 1;
   out_5012584798577878241[134] = 0;
   out_5012584798577878241[135] = 0;
   out_5012584798577878241[136] = 0;
   out_5012584798577878241[137] = 0;
   out_5012584798577878241[138] = 0;
   out_5012584798577878241[139] = 0;
   out_5012584798577878241[140] = 0;
   out_5012584798577878241[141] = 0;
   out_5012584798577878241[142] = 0;
   out_5012584798577878241[143] = 0;
   out_5012584798577878241[144] = 0;
   out_5012584798577878241[145] = 0;
   out_5012584798577878241[146] = 0;
   out_5012584798577878241[147] = 0;
   out_5012584798577878241[148] = 0;
   out_5012584798577878241[149] = 0;
   out_5012584798577878241[150] = 0;
   out_5012584798577878241[151] = 0;
   out_5012584798577878241[152] = 1;
   out_5012584798577878241[153] = 0;
   out_5012584798577878241[154] = 0;
   out_5012584798577878241[155] = 0;
   out_5012584798577878241[156] = 0;
   out_5012584798577878241[157] = 0;
   out_5012584798577878241[158] = 0;
   out_5012584798577878241[159] = 0;
   out_5012584798577878241[160] = 0;
   out_5012584798577878241[161] = 0;
   out_5012584798577878241[162] = 0;
   out_5012584798577878241[163] = 0;
   out_5012584798577878241[164] = 0;
   out_5012584798577878241[165] = 0;
   out_5012584798577878241[166] = 0;
   out_5012584798577878241[167] = 0;
   out_5012584798577878241[168] = 0;
   out_5012584798577878241[169] = 0;
   out_5012584798577878241[170] = 0;
   out_5012584798577878241[171] = 1;
   out_5012584798577878241[172] = 0;
   out_5012584798577878241[173] = 0;
   out_5012584798577878241[174] = 0;
   out_5012584798577878241[175] = 0;
   out_5012584798577878241[176] = 0;
   out_5012584798577878241[177] = 0;
   out_5012584798577878241[178] = 0;
   out_5012584798577878241[179] = 0;
   out_5012584798577878241[180] = 0;
   out_5012584798577878241[181] = 0;
   out_5012584798577878241[182] = 0;
   out_5012584798577878241[183] = 0;
   out_5012584798577878241[184] = 0;
   out_5012584798577878241[185] = 0;
   out_5012584798577878241[186] = 0;
   out_5012584798577878241[187] = 0;
   out_5012584798577878241[188] = 0;
   out_5012584798577878241[189] = 0;
   out_5012584798577878241[190] = 1;
   out_5012584798577878241[191] = 0;
   out_5012584798577878241[192] = 0;
   out_5012584798577878241[193] = 0;
   out_5012584798577878241[194] = 0;
   out_5012584798577878241[195] = 0;
   out_5012584798577878241[196] = 0;
   out_5012584798577878241[197] = 0;
   out_5012584798577878241[198] = 0;
   out_5012584798577878241[199] = 0;
   out_5012584798577878241[200] = 0;
   out_5012584798577878241[201] = 0;
   out_5012584798577878241[202] = 0;
   out_5012584798577878241[203] = 0;
   out_5012584798577878241[204] = 0;
   out_5012584798577878241[205] = 0;
   out_5012584798577878241[206] = 0;
   out_5012584798577878241[207] = 0;
   out_5012584798577878241[208] = 0;
   out_5012584798577878241[209] = 1;
   out_5012584798577878241[210] = 0;
   out_5012584798577878241[211] = 0;
   out_5012584798577878241[212] = 0;
   out_5012584798577878241[213] = 0;
   out_5012584798577878241[214] = 0;
   out_5012584798577878241[215] = 0;
   out_5012584798577878241[216] = 0;
   out_5012584798577878241[217] = 0;
   out_5012584798577878241[218] = 0;
   out_5012584798577878241[219] = 0;
   out_5012584798577878241[220] = 0;
   out_5012584798577878241[221] = 0;
   out_5012584798577878241[222] = 0;
   out_5012584798577878241[223] = 0;
   out_5012584798577878241[224] = 0;
   out_5012584798577878241[225] = 0;
   out_5012584798577878241[226] = 0;
   out_5012584798577878241[227] = 0;
   out_5012584798577878241[228] = 1;
   out_5012584798577878241[229] = 0;
   out_5012584798577878241[230] = 0;
   out_5012584798577878241[231] = 0;
   out_5012584798577878241[232] = 0;
   out_5012584798577878241[233] = 0;
   out_5012584798577878241[234] = 0;
   out_5012584798577878241[235] = 0;
   out_5012584798577878241[236] = 0;
   out_5012584798577878241[237] = 0;
   out_5012584798577878241[238] = 0;
   out_5012584798577878241[239] = 0;
   out_5012584798577878241[240] = 0;
   out_5012584798577878241[241] = 0;
   out_5012584798577878241[242] = 0;
   out_5012584798577878241[243] = 0;
   out_5012584798577878241[244] = 0;
   out_5012584798577878241[245] = 0;
   out_5012584798577878241[246] = 0;
   out_5012584798577878241[247] = 1;
   out_5012584798577878241[248] = 0;
   out_5012584798577878241[249] = 0;
   out_5012584798577878241[250] = 0;
   out_5012584798577878241[251] = 0;
   out_5012584798577878241[252] = 0;
   out_5012584798577878241[253] = 0;
   out_5012584798577878241[254] = 0;
   out_5012584798577878241[255] = 0;
   out_5012584798577878241[256] = 0;
   out_5012584798577878241[257] = 0;
   out_5012584798577878241[258] = 0;
   out_5012584798577878241[259] = 0;
   out_5012584798577878241[260] = 0;
   out_5012584798577878241[261] = 0;
   out_5012584798577878241[262] = 0;
   out_5012584798577878241[263] = 0;
   out_5012584798577878241[264] = 0;
   out_5012584798577878241[265] = 0;
   out_5012584798577878241[266] = 1;
   out_5012584798577878241[267] = 0;
   out_5012584798577878241[268] = 0;
   out_5012584798577878241[269] = 0;
   out_5012584798577878241[270] = 0;
   out_5012584798577878241[271] = 0;
   out_5012584798577878241[272] = 0;
   out_5012584798577878241[273] = 0;
   out_5012584798577878241[274] = 0;
   out_5012584798577878241[275] = 0;
   out_5012584798577878241[276] = 0;
   out_5012584798577878241[277] = 0;
   out_5012584798577878241[278] = 0;
   out_5012584798577878241[279] = 0;
   out_5012584798577878241[280] = 0;
   out_5012584798577878241[281] = 0;
   out_5012584798577878241[282] = 0;
   out_5012584798577878241[283] = 0;
   out_5012584798577878241[284] = 0;
   out_5012584798577878241[285] = 1;
   out_5012584798577878241[286] = 0;
   out_5012584798577878241[287] = 0;
   out_5012584798577878241[288] = 0;
   out_5012584798577878241[289] = 0;
   out_5012584798577878241[290] = 0;
   out_5012584798577878241[291] = 0;
   out_5012584798577878241[292] = 0;
   out_5012584798577878241[293] = 0;
   out_5012584798577878241[294] = 0;
   out_5012584798577878241[295] = 0;
   out_5012584798577878241[296] = 0;
   out_5012584798577878241[297] = 0;
   out_5012584798577878241[298] = 0;
   out_5012584798577878241[299] = 0;
   out_5012584798577878241[300] = 0;
   out_5012584798577878241[301] = 0;
   out_5012584798577878241[302] = 0;
   out_5012584798577878241[303] = 0;
   out_5012584798577878241[304] = 1;
   out_5012584798577878241[305] = 0;
   out_5012584798577878241[306] = 0;
   out_5012584798577878241[307] = 0;
   out_5012584798577878241[308] = 0;
   out_5012584798577878241[309] = 0;
   out_5012584798577878241[310] = 0;
   out_5012584798577878241[311] = 0;
   out_5012584798577878241[312] = 0;
   out_5012584798577878241[313] = 0;
   out_5012584798577878241[314] = 0;
   out_5012584798577878241[315] = 0;
   out_5012584798577878241[316] = 0;
   out_5012584798577878241[317] = 0;
   out_5012584798577878241[318] = 0;
   out_5012584798577878241[319] = 0;
   out_5012584798577878241[320] = 0;
   out_5012584798577878241[321] = 0;
   out_5012584798577878241[322] = 0;
   out_5012584798577878241[323] = 1;
}
void h_4(double *state, double *unused, double *out_3012774128462283816) {
   out_3012774128462283816[0] = state[6] + state[9];
   out_3012774128462283816[1] = state[7] + state[10];
   out_3012774128462283816[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8868047882380552821) {
   out_8868047882380552821[0] = 0;
   out_8868047882380552821[1] = 0;
   out_8868047882380552821[2] = 0;
   out_8868047882380552821[3] = 0;
   out_8868047882380552821[4] = 0;
   out_8868047882380552821[5] = 0;
   out_8868047882380552821[6] = 1;
   out_8868047882380552821[7] = 0;
   out_8868047882380552821[8] = 0;
   out_8868047882380552821[9] = 1;
   out_8868047882380552821[10] = 0;
   out_8868047882380552821[11] = 0;
   out_8868047882380552821[12] = 0;
   out_8868047882380552821[13] = 0;
   out_8868047882380552821[14] = 0;
   out_8868047882380552821[15] = 0;
   out_8868047882380552821[16] = 0;
   out_8868047882380552821[17] = 0;
   out_8868047882380552821[18] = 0;
   out_8868047882380552821[19] = 0;
   out_8868047882380552821[20] = 0;
   out_8868047882380552821[21] = 0;
   out_8868047882380552821[22] = 0;
   out_8868047882380552821[23] = 0;
   out_8868047882380552821[24] = 0;
   out_8868047882380552821[25] = 1;
   out_8868047882380552821[26] = 0;
   out_8868047882380552821[27] = 0;
   out_8868047882380552821[28] = 1;
   out_8868047882380552821[29] = 0;
   out_8868047882380552821[30] = 0;
   out_8868047882380552821[31] = 0;
   out_8868047882380552821[32] = 0;
   out_8868047882380552821[33] = 0;
   out_8868047882380552821[34] = 0;
   out_8868047882380552821[35] = 0;
   out_8868047882380552821[36] = 0;
   out_8868047882380552821[37] = 0;
   out_8868047882380552821[38] = 0;
   out_8868047882380552821[39] = 0;
   out_8868047882380552821[40] = 0;
   out_8868047882380552821[41] = 0;
   out_8868047882380552821[42] = 0;
   out_8868047882380552821[43] = 0;
   out_8868047882380552821[44] = 1;
   out_8868047882380552821[45] = 0;
   out_8868047882380552821[46] = 0;
   out_8868047882380552821[47] = 1;
   out_8868047882380552821[48] = 0;
   out_8868047882380552821[49] = 0;
   out_8868047882380552821[50] = 0;
   out_8868047882380552821[51] = 0;
   out_8868047882380552821[52] = 0;
   out_8868047882380552821[53] = 0;
}
void h_10(double *state, double *unused, double *out_5195823745099030305) {
   out_5195823745099030305[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5195823745099030305[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5195823745099030305[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6876873563119817203) {
   out_6876873563119817203[0] = 0;
   out_6876873563119817203[1] = 9.8100000000000005*cos(state[1]);
   out_6876873563119817203[2] = 0;
   out_6876873563119817203[3] = 0;
   out_6876873563119817203[4] = -state[8];
   out_6876873563119817203[5] = state[7];
   out_6876873563119817203[6] = 0;
   out_6876873563119817203[7] = state[5];
   out_6876873563119817203[8] = -state[4];
   out_6876873563119817203[9] = 0;
   out_6876873563119817203[10] = 0;
   out_6876873563119817203[11] = 0;
   out_6876873563119817203[12] = 1;
   out_6876873563119817203[13] = 0;
   out_6876873563119817203[14] = 0;
   out_6876873563119817203[15] = 1;
   out_6876873563119817203[16] = 0;
   out_6876873563119817203[17] = 0;
   out_6876873563119817203[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6876873563119817203[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6876873563119817203[20] = 0;
   out_6876873563119817203[21] = state[8];
   out_6876873563119817203[22] = 0;
   out_6876873563119817203[23] = -state[6];
   out_6876873563119817203[24] = -state[5];
   out_6876873563119817203[25] = 0;
   out_6876873563119817203[26] = state[3];
   out_6876873563119817203[27] = 0;
   out_6876873563119817203[28] = 0;
   out_6876873563119817203[29] = 0;
   out_6876873563119817203[30] = 0;
   out_6876873563119817203[31] = 1;
   out_6876873563119817203[32] = 0;
   out_6876873563119817203[33] = 0;
   out_6876873563119817203[34] = 1;
   out_6876873563119817203[35] = 0;
   out_6876873563119817203[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6876873563119817203[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6876873563119817203[38] = 0;
   out_6876873563119817203[39] = -state[7];
   out_6876873563119817203[40] = state[6];
   out_6876873563119817203[41] = 0;
   out_6876873563119817203[42] = state[4];
   out_6876873563119817203[43] = -state[3];
   out_6876873563119817203[44] = 0;
   out_6876873563119817203[45] = 0;
   out_6876873563119817203[46] = 0;
   out_6876873563119817203[47] = 0;
   out_6876873563119817203[48] = 0;
   out_6876873563119817203[49] = 0;
   out_6876873563119817203[50] = 1;
   out_6876873563119817203[51] = 0;
   out_6876873563119817203[52] = 0;
   out_6876873563119817203[53] = 1;
}
void h_13(double *state, double *unused, double *out_5988520755265918560) {
   out_5988520755265918560[0] = state[3];
   out_5988520755265918560[1] = state[4];
   out_5988520755265918560[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1257416674063851892) {
   out_1257416674063851892[0] = 0;
   out_1257416674063851892[1] = 0;
   out_1257416674063851892[2] = 0;
   out_1257416674063851892[3] = 1;
   out_1257416674063851892[4] = 0;
   out_1257416674063851892[5] = 0;
   out_1257416674063851892[6] = 0;
   out_1257416674063851892[7] = 0;
   out_1257416674063851892[8] = 0;
   out_1257416674063851892[9] = 0;
   out_1257416674063851892[10] = 0;
   out_1257416674063851892[11] = 0;
   out_1257416674063851892[12] = 0;
   out_1257416674063851892[13] = 0;
   out_1257416674063851892[14] = 0;
   out_1257416674063851892[15] = 0;
   out_1257416674063851892[16] = 0;
   out_1257416674063851892[17] = 0;
   out_1257416674063851892[18] = 0;
   out_1257416674063851892[19] = 0;
   out_1257416674063851892[20] = 0;
   out_1257416674063851892[21] = 0;
   out_1257416674063851892[22] = 1;
   out_1257416674063851892[23] = 0;
   out_1257416674063851892[24] = 0;
   out_1257416674063851892[25] = 0;
   out_1257416674063851892[26] = 0;
   out_1257416674063851892[27] = 0;
   out_1257416674063851892[28] = 0;
   out_1257416674063851892[29] = 0;
   out_1257416674063851892[30] = 0;
   out_1257416674063851892[31] = 0;
   out_1257416674063851892[32] = 0;
   out_1257416674063851892[33] = 0;
   out_1257416674063851892[34] = 0;
   out_1257416674063851892[35] = 0;
   out_1257416674063851892[36] = 0;
   out_1257416674063851892[37] = 0;
   out_1257416674063851892[38] = 0;
   out_1257416674063851892[39] = 0;
   out_1257416674063851892[40] = 0;
   out_1257416674063851892[41] = 1;
   out_1257416674063851892[42] = 0;
   out_1257416674063851892[43] = 0;
   out_1257416674063851892[44] = 0;
   out_1257416674063851892[45] = 0;
   out_1257416674063851892[46] = 0;
   out_1257416674063851892[47] = 0;
   out_1257416674063851892[48] = 0;
   out_1257416674063851892[49] = 0;
   out_1257416674063851892[50] = 0;
   out_1257416674063851892[51] = 0;
   out_1257416674063851892[52] = 0;
   out_1257416674063851892[53] = 0;
}
void h_14(double *state, double *unused, double *out_5205424874227035559) {
   out_5205424874227035559[0] = state[6];
   out_5205424874227035559[1] = state[7];
   out_5205424874227035559[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4904807026041068292) {
   out_4904807026041068292[0] = 0;
   out_4904807026041068292[1] = 0;
   out_4904807026041068292[2] = 0;
   out_4904807026041068292[3] = 0;
   out_4904807026041068292[4] = 0;
   out_4904807026041068292[5] = 0;
   out_4904807026041068292[6] = 1;
   out_4904807026041068292[7] = 0;
   out_4904807026041068292[8] = 0;
   out_4904807026041068292[9] = 0;
   out_4904807026041068292[10] = 0;
   out_4904807026041068292[11] = 0;
   out_4904807026041068292[12] = 0;
   out_4904807026041068292[13] = 0;
   out_4904807026041068292[14] = 0;
   out_4904807026041068292[15] = 0;
   out_4904807026041068292[16] = 0;
   out_4904807026041068292[17] = 0;
   out_4904807026041068292[18] = 0;
   out_4904807026041068292[19] = 0;
   out_4904807026041068292[20] = 0;
   out_4904807026041068292[21] = 0;
   out_4904807026041068292[22] = 0;
   out_4904807026041068292[23] = 0;
   out_4904807026041068292[24] = 0;
   out_4904807026041068292[25] = 1;
   out_4904807026041068292[26] = 0;
   out_4904807026041068292[27] = 0;
   out_4904807026041068292[28] = 0;
   out_4904807026041068292[29] = 0;
   out_4904807026041068292[30] = 0;
   out_4904807026041068292[31] = 0;
   out_4904807026041068292[32] = 0;
   out_4904807026041068292[33] = 0;
   out_4904807026041068292[34] = 0;
   out_4904807026041068292[35] = 0;
   out_4904807026041068292[36] = 0;
   out_4904807026041068292[37] = 0;
   out_4904807026041068292[38] = 0;
   out_4904807026041068292[39] = 0;
   out_4904807026041068292[40] = 0;
   out_4904807026041068292[41] = 0;
   out_4904807026041068292[42] = 0;
   out_4904807026041068292[43] = 0;
   out_4904807026041068292[44] = 1;
   out_4904807026041068292[45] = 0;
   out_4904807026041068292[46] = 0;
   out_4904807026041068292[47] = 0;
   out_4904807026041068292[48] = 0;
   out_4904807026041068292[49] = 0;
   out_4904807026041068292[50] = 0;
   out_4904807026041068292[51] = 0;
   out_4904807026041068292[52] = 0;
   out_4904807026041068292[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3128060725060609626) {
  err_fun(nom_x, delta_x, out_3128060725060609626);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_962437773882614248) {
  inv_err_fun(nom_x, true_x, out_962437773882614248);
}
void pose_H_mod_fun(double *state, double *out_1378391307355774028) {
  H_mod_fun(state, out_1378391307355774028);
}
void pose_f_fun(double *state, double dt, double *out_7600705386146157547) {
  f_fun(state,  dt, out_7600705386146157547);
}
void pose_F_fun(double *state, double dt, double *out_5012584798577878241) {
  F_fun(state,  dt, out_5012584798577878241);
}
void pose_h_4(double *state, double *unused, double *out_3012774128462283816) {
  h_4(state, unused, out_3012774128462283816);
}
void pose_H_4(double *state, double *unused, double *out_8868047882380552821) {
  H_4(state, unused, out_8868047882380552821);
}
void pose_h_10(double *state, double *unused, double *out_5195823745099030305) {
  h_10(state, unused, out_5195823745099030305);
}
void pose_H_10(double *state, double *unused, double *out_6876873563119817203) {
  H_10(state, unused, out_6876873563119817203);
}
void pose_h_13(double *state, double *unused, double *out_5988520755265918560) {
  h_13(state, unused, out_5988520755265918560);
}
void pose_H_13(double *state, double *unused, double *out_1257416674063851892) {
  H_13(state, unused, out_1257416674063851892);
}
void pose_h_14(double *state, double *unused, double *out_5205424874227035559) {
  h_14(state, unused, out_5205424874227035559);
}
void pose_H_14(double *state, double *unused, double *out_4904807026041068292) {
  H_14(state, unused, out_4904807026041068292);
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
