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
void err_fun(double *nom_x, double *delta_x, double *out_8015077839077896466) {
   out_8015077839077896466[0] = delta_x[0] + nom_x[0];
   out_8015077839077896466[1] = delta_x[1] + nom_x[1];
   out_8015077839077896466[2] = delta_x[2] + nom_x[2];
   out_8015077839077896466[3] = delta_x[3] + nom_x[3];
   out_8015077839077896466[4] = delta_x[4] + nom_x[4];
   out_8015077839077896466[5] = delta_x[5] + nom_x[5];
   out_8015077839077896466[6] = delta_x[6] + nom_x[6];
   out_8015077839077896466[7] = delta_x[7] + nom_x[7];
   out_8015077839077896466[8] = delta_x[8] + nom_x[8];
   out_8015077839077896466[9] = delta_x[9] + nom_x[9];
   out_8015077839077896466[10] = delta_x[10] + nom_x[10];
   out_8015077839077896466[11] = delta_x[11] + nom_x[11];
   out_8015077839077896466[12] = delta_x[12] + nom_x[12];
   out_8015077839077896466[13] = delta_x[13] + nom_x[13];
   out_8015077839077896466[14] = delta_x[14] + nom_x[14];
   out_8015077839077896466[15] = delta_x[15] + nom_x[15];
   out_8015077839077896466[16] = delta_x[16] + nom_x[16];
   out_8015077839077896466[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_120875525776824592) {
   out_120875525776824592[0] = -nom_x[0] + true_x[0];
   out_120875525776824592[1] = -nom_x[1] + true_x[1];
   out_120875525776824592[2] = -nom_x[2] + true_x[2];
   out_120875525776824592[3] = -nom_x[3] + true_x[3];
   out_120875525776824592[4] = -nom_x[4] + true_x[4];
   out_120875525776824592[5] = -nom_x[5] + true_x[5];
   out_120875525776824592[6] = -nom_x[6] + true_x[6];
   out_120875525776824592[7] = -nom_x[7] + true_x[7];
   out_120875525776824592[8] = -nom_x[8] + true_x[8];
   out_120875525776824592[9] = -nom_x[9] + true_x[9];
   out_120875525776824592[10] = -nom_x[10] + true_x[10];
   out_120875525776824592[11] = -nom_x[11] + true_x[11];
   out_120875525776824592[12] = -nom_x[12] + true_x[12];
   out_120875525776824592[13] = -nom_x[13] + true_x[13];
   out_120875525776824592[14] = -nom_x[14] + true_x[14];
   out_120875525776824592[15] = -nom_x[15] + true_x[15];
   out_120875525776824592[16] = -nom_x[16] + true_x[16];
   out_120875525776824592[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6916249509140048441) {
   out_6916249509140048441[0] = 1.0;
   out_6916249509140048441[1] = 0.0;
   out_6916249509140048441[2] = 0.0;
   out_6916249509140048441[3] = 0.0;
   out_6916249509140048441[4] = 0.0;
   out_6916249509140048441[5] = 0.0;
   out_6916249509140048441[6] = 0.0;
   out_6916249509140048441[7] = 0.0;
   out_6916249509140048441[8] = 0.0;
   out_6916249509140048441[9] = 0.0;
   out_6916249509140048441[10] = 0.0;
   out_6916249509140048441[11] = 0.0;
   out_6916249509140048441[12] = 0.0;
   out_6916249509140048441[13] = 0.0;
   out_6916249509140048441[14] = 0.0;
   out_6916249509140048441[15] = 0.0;
   out_6916249509140048441[16] = 0.0;
   out_6916249509140048441[17] = 0.0;
   out_6916249509140048441[18] = 0.0;
   out_6916249509140048441[19] = 1.0;
   out_6916249509140048441[20] = 0.0;
   out_6916249509140048441[21] = 0.0;
   out_6916249509140048441[22] = 0.0;
   out_6916249509140048441[23] = 0.0;
   out_6916249509140048441[24] = 0.0;
   out_6916249509140048441[25] = 0.0;
   out_6916249509140048441[26] = 0.0;
   out_6916249509140048441[27] = 0.0;
   out_6916249509140048441[28] = 0.0;
   out_6916249509140048441[29] = 0.0;
   out_6916249509140048441[30] = 0.0;
   out_6916249509140048441[31] = 0.0;
   out_6916249509140048441[32] = 0.0;
   out_6916249509140048441[33] = 0.0;
   out_6916249509140048441[34] = 0.0;
   out_6916249509140048441[35] = 0.0;
   out_6916249509140048441[36] = 0.0;
   out_6916249509140048441[37] = 0.0;
   out_6916249509140048441[38] = 1.0;
   out_6916249509140048441[39] = 0.0;
   out_6916249509140048441[40] = 0.0;
   out_6916249509140048441[41] = 0.0;
   out_6916249509140048441[42] = 0.0;
   out_6916249509140048441[43] = 0.0;
   out_6916249509140048441[44] = 0.0;
   out_6916249509140048441[45] = 0.0;
   out_6916249509140048441[46] = 0.0;
   out_6916249509140048441[47] = 0.0;
   out_6916249509140048441[48] = 0.0;
   out_6916249509140048441[49] = 0.0;
   out_6916249509140048441[50] = 0.0;
   out_6916249509140048441[51] = 0.0;
   out_6916249509140048441[52] = 0.0;
   out_6916249509140048441[53] = 0.0;
   out_6916249509140048441[54] = 0.0;
   out_6916249509140048441[55] = 0.0;
   out_6916249509140048441[56] = 0.0;
   out_6916249509140048441[57] = 1.0;
   out_6916249509140048441[58] = 0.0;
   out_6916249509140048441[59] = 0.0;
   out_6916249509140048441[60] = 0.0;
   out_6916249509140048441[61] = 0.0;
   out_6916249509140048441[62] = 0.0;
   out_6916249509140048441[63] = 0.0;
   out_6916249509140048441[64] = 0.0;
   out_6916249509140048441[65] = 0.0;
   out_6916249509140048441[66] = 0.0;
   out_6916249509140048441[67] = 0.0;
   out_6916249509140048441[68] = 0.0;
   out_6916249509140048441[69] = 0.0;
   out_6916249509140048441[70] = 0.0;
   out_6916249509140048441[71] = 0.0;
   out_6916249509140048441[72] = 0.0;
   out_6916249509140048441[73] = 0.0;
   out_6916249509140048441[74] = 0.0;
   out_6916249509140048441[75] = 0.0;
   out_6916249509140048441[76] = 1.0;
   out_6916249509140048441[77] = 0.0;
   out_6916249509140048441[78] = 0.0;
   out_6916249509140048441[79] = 0.0;
   out_6916249509140048441[80] = 0.0;
   out_6916249509140048441[81] = 0.0;
   out_6916249509140048441[82] = 0.0;
   out_6916249509140048441[83] = 0.0;
   out_6916249509140048441[84] = 0.0;
   out_6916249509140048441[85] = 0.0;
   out_6916249509140048441[86] = 0.0;
   out_6916249509140048441[87] = 0.0;
   out_6916249509140048441[88] = 0.0;
   out_6916249509140048441[89] = 0.0;
   out_6916249509140048441[90] = 0.0;
   out_6916249509140048441[91] = 0.0;
   out_6916249509140048441[92] = 0.0;
   out_6916249509140048441[93] = 0.0;
   out_6916249509140048441[94] = 0.0;
   out_6916249509140048441[95] = 1.0;
   out_6916249509140048441[96] = 0.0;
   out_6916249509140048441[97] = 0.0;
   out_6916249509140048441[98] = 0.0;
   out_6916249509140048441[99] = 0.0;
   out_6916249509140048441[100] = 0.0;
   out_6916249509140048441[101] = 0.0;
   out_6916249509140048441[102] = 0.0;
   out_6916249509140048441[103] = 0.0;
   out_6916249509140048441[104] = 0.0;
   out_6916249509140048441[105] = 0.0;
   out_6916249509140048441[106] = 0.0;
   out_6916249509140048441[107] = 0.0;
   out_6916249509140048441[108] = 0.0;
   out_6916249509140048441[109] = 0.0;
   out_6916249509140048441[110] = 0.0;
   out_6916249509140048441[111] = 0.0;
   out_6916249509140048441[112] = 0.0;
   out_6916249509140048441[113] = 0.0;
   out_6916249509140048441[114] = 1.0;
   out_6916249509140048441[115] = 0.0;
   out_6916249509140048441[116] = 0.0;
   out_6916249509140048441[117] = 0.0;
   out_6916249509140048441[118] = 0.0;
   out_6916249509140048441[119] = 0.0;
   out_6916249509140048441[120] = 0.0;
   out_6916249509140048441[121] = 0.0;
   out_6916249509140048441[122] = 0.0;
   out_6916249509140048441[123] = 0.0;
   out_6916249509140048441[124] = 0.0;
   out_6916249509140048441[125] = 0.0;
   out_6916249509140048441[126] = 0.0;
   out_6916249509140048441[127] = 0.0;
   out_6916249509140048441[128] = 0.0;
   out_6916249509140048441[129] = 0.0;
   out_6916249509140048441[130] = 0.0;
   out_6916249509140048441[131] = 0.0;
   out_6916249509140048441[132] = 0.0;
   out_6916249509140048441[133] = 1.0;
   out_6916249509140048441[134] = 0.0;
   out_6916249509140048441[135] = 0.0;
   out_6916249509140048441[136] = 0.0;
   out_6916249509140048441[137] = 0.0;
   out_6916249509140048441[138] = 0.0;
   out_6916249509140048441[139] = 0.0;
   out_6916249509140048441[140] = 0.0;
   out_6916249509140048441[141] = 0.0;
   out_6916249509140048441[142] = 0.0;
   out_6916249509140048441[143] = 0.0;
   out_6916249509140048441[144] = 0.0;
   out_6916249509140048441[145] = 0.0;
   out_6916249509140048441[146] = 0.0;
   out_6916249509140048441[147] = 0.0;
   out_6916249509140048441[148] = 0.0;
   out_6916249509140048441[149] = 0.0;
   out_6916249509140048441[150] = 0.0;
   out_6916249509140048441[151] = 0.0;
   out_6916249509140048441[152] = 1.0;
   out_6916249509140048441[153] = 0.0;
   out_6916249509140048441[154] = 0.0;
   out_6916249509140048441[155] = 0.0;
   out_6916249509140048441[156] = 0.0;
   out_6916249509140048441[157] = 0.0;
   out_6916249509140048441[158] = 0.0;
   out_6916249509140048441[159] = 0.0;
   out_6916249509140048441[160] = 0.0;
   out_6916249509140048441[161] = 0.0;
   out_6916249509140048441[162] = 0.0;
   out_6916249509140048441[163] = 0.0;
   out_6916249509140048441[164] = 0.0;
   out_6916249509140048441[165] = 0.0;
   out_6916249509140048441[166] = 0.0;
   out_6916249509140048441[167] = 0.0;
   out_6916249509140048441[168] = 0.0;
   out_6916249509140048441[169] = 0.0;
   out_6916249509140048441[170] = 0.0;
   out_6916249509140048441[171] = 1.0;
   out_6916249509140048441[172] = 0.0;
   out_6916249509140048441[173] = 0.0;
   out_6916249509140048441[174] = 0.0;
   out_6916249509140048441[175] = 0.0;
   out_6916249509140048441[176] = 0.0;
   out_6916249509140048441[177] = 0.0;
   out_6916249509140048441[178] = 0.0;
   out_6916249509140048441[179] = 0.0;
   out_6916249509140048441[180] = 0.0;
   out_6916249509140048441[181] = 0.0;
   out_6916249509140048441[182] = 0.0;
   out_6916249509140048441[183] = 0.0;
   out_6916249509140048441[184] = 0.0;
   out_6916249509140048441[185] = 0.0;
   out_6916249509140048441[186] = 0.0;
   out_6916249509140048441[187] = 0.0;
   out_6916249509140048441[188] = 0.0;
   out_6916249509140048441[189] = 0.0;
   out_6916249509140048441[190] = 1.0;
   out_6916249509140048441[191] = 0.0;
   out_6916249509140048441[192] = 0.0;
   out_6916249509140048441[193] = 0.0;
   out_6916249509140048441[194] = 0.0;
   out_6916249509140048441[195] = 0.0;
   out_6916249509140048441[196] = 0.0;
   out_6916249509140048441[197] = 0.0;
   out_6916249509140048441[198] = 0.0;
   out_6916249509140048441[199] = 0.0;
   out_6916249509140048441[200] = 0.0;
   out_6916249509140048441[201] = 0.0;
   out_6916249509140048441[202] = 0.0;
   out_6916249509140048441[203] = 0.0;
   out_6916249509140048441[204] = 0.0;
   out_6916249509140048441[205] = 0.0;
   out_6916249509140048441[206] = 0.0;
   out_6916249509140048441[207] = 0.0;
   out_6916249509140048441[208] = 0.0;
   out_6916249509140048441[209] = 1.0;
   out_6916249509140048441[210] = 0.0;
   out_6916249509140048441[211] = 0.0;
   out_6916249509140048441[212] = 0.0;
   out_6916249509140048441[213] = 0.0;
   out_6916249509140048441[214] = 0.0;
   out_6916249509140048441[215] = 0.0;
   out_6916249509140048441[216] = 0.0;
   out_6916249509140048441[217] = 0.0;
   out_6916249509140048441[218] = 0.0;
   out_6916249509140048441[219] = 0.0;
   out_6916249509140048441[220] = 0.0;
   out_6916249509140048441[221] = 0.0;
   out_6916249509140048441[222] = 0.0;
   out_6916249509140048441[223] = 0.0;
   out_6916249509140048441[224] = 0.0;
   out_6916249509140048441[225] = 0.0;
   out_6916249509140048441[226] = 0.0;
   out_6916249509140048441[227] = 0.0;
   out_6916249509140048441[228] = 1.0;
   out_6916249509140048441[229] = 0.0;
   out_6916249509140048441[230] = 0.0;
   out_6916249509140048441[231] = 0.0;
   out_6916249509140048441[232] = 0.0;
   out_6916249509140048441[233] = 0.0;
   out_6916249509140048441[234] = 0.0;
   out_6916249509140048441[235] = 0.0;
   out_6916249509140048441[236] = 0.0;
   out_6916249509140048441[237] = 0.0;
   out_6916249509140048441[238] = 0.0;
   out_6916249509140048441[239] = 0.0;
   out_6916249509140048441[240] = 0.0;
   out_6916249509140048441[241] = 0.0;
   out_6916249509140048441[242] = 0.0;
   out_6916249509140048441[243] = 0.0;
   out_6916249509140048441[244] = 0.0;
   out_6916249509140048441[245] = 0.0;
   out_6916249509140048441[246] = 0.0;
   out_6916249509140048441[247] = 1.0;
   out_6916249509140048441[248] = 0.0;
   out_6916249509140048441[249] = 0.0;
   out_6916249509140048441[250] = 0.0;
   out_6916249509140048441[251] = 0.0;
   out_6916249509140048441[252] = 0.0;
   out_6916249509140048441[253] = 0.0;
   out_6916249509140048441[254] = 0.0;
   out_6916249509140048441[255] = 0.0;
   out_6916249509140048441[256] = 0.0;
   out_6916249509140048441[257] = 0.0;
   out_6916249509140048441[258] = 0.0;
   out_6916249509140048441[259] = 0.0;
   out_6916249509140048441[260] = 0.0;
   out_6916249509140048441[261] = 0.0;
   out_6916249509140048441[262] = 0.0;
   out_6916249509140048441[263] = 0.0;
   out_6916249509140048441[264] = 0.0;
   out_6916249509140048441[265] = 0.0;
   out_6916249509140048441[266] = 1.0;
   out_6916249509140048441[267] = 0.0;
   out_6916249509140048441[268] = 0.0;
   out_6916249509140048441[269] = 0.0;
   out_6916249509140048441[270] = 0.0;
   out_6916249509140048441[271] = 0.0;
   out_6916249509140048441[272] = 0.0;
   out_6916249509140048441[273] = 0.0;
   out_6916249509140048441[274] = 0.0;
   out_6916249509140048441[275] = 0.0;
   out_6916249509140048441[276] = 0.0;
   out_6916249509140048441[277] = 0.0;
   out_6916249509140048441[278] = 0.0;
   out_6916249509140048441[279] = 0.0;
   out_6916249509140048441[280] = 0.0;
   out_6916249509140048441[281] = 0.0;
   out_6916249509140048441[282] = 0.0;
   out_6916249509140048441[283] = 0.0;
   out_6916249509140048441[284] = 0.0;
   out_6916249509140048441[285] = 1.0;
   out_6916249509140048441[286] = 0.0;
   out_6916249509140048441[287] = 0.0;
   out_6916249509140048441[288] = 0.0;
   out_6916249509140048441[289] = 0.0;
   out_6916249509140048441[290] = 0.0;
   out_6916249509140048441[291] = 0.0;
   out_6916249509140048441[292] = 0.0;
   out_6916249509140048441[293] = 0.0;
   out_6916249509140048441[294] = 0.0;
   out_6916249509140048441[295] = 0.0;
   out_6916249509140048441[296] = 0.0;
   out_6916249509140048441[297] = 0.0;
   out_6916249509140048441[298] = 0.0;
   out_6916249509140048441[299] = 0.0;
   out_6916249509140048441[300] = 0.0;
   out_6916249509140048441[301] = 0.0;
   out_6916249509140048441[302] = 0.0;
   out_6916249509140048441[303] = 0.0;
   out_6916249509140048441[304] = 1.0;
   out_6916249509140048441[305] = 0.0;
   out_6916249509140048441[306] = 0.0;
   out_6916249509140048441[307] = 0.0;
   out_6916249509140048441[308] = 0.0;
   out_6916249509140048441[309] = 0.0;
   out_6916249509140048441[310] = 0.0;
   out_6916249509140048441[311] = 0.0;
   out_6916249509140048441[312] = 0.0;
   out_6916249509140048441[313] = 0.0;
   out_6916249509140048441[314] = 0.0;
   out_6916249509140048441[315] = 0.0;
   out_6916249509140048441[316] = 0.0;
   out_6916249509140048441[317] = 0.0;
   out_6916249509140048441[318] = 0.0;
   out_6916249509140048441[319] = 0.0;
   out_6916249509140048441[320] = 0.0;
   out_6916249509140048441[321] = 0.0;
   out_6916249509140048441[322] = 0.0;
   out_6916249509140048441[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4090535296156790500) {
   out_4090535296156790500[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4090535296156790500[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4090535296156790500[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4090535296156790500[3] = dt*state[12] + state[3];
   out_4090535296156790500[4] = dt*state[13] + state[4];
   out_4090535296156790500[5] = dt*state[14] + state[5];
   out_4090535296156790500[6] = state[6];
   out_4090535296156790500[7] = state[7];
   out_4090535296156790500[8] = state[8];
   out_4090535296156790500[9] = state[9];
   out_4090535296156790500[10] = state[10];
   out_4090535296156790500[11] = state[11];
   out_4090535296156790500[12] = state[12];
   out_4090535296156790500[13] = state[13];
   out_4090535296156790500[14] = state[14];
   out_4090535296156790500[15] = state[15];
   out_4090535296156790500[16] = state[16];
   out_4090535296156790500[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3730744472462246424) {
   out_3730744472462246424[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3730744472462246424[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3730744472462246424[2] = 0;
   out_3730744472462246424[3] = 0;
   out_3730744472462246424[4] = 0;
   out_3730744472462246424[5] = 0;
   out_3730744472462246424[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3730744472462246424[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3730744472462246424[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3730744472462246424[9] = 0;
   out_3730744472462246424[10] = 0;
   out_3730744472462246424[11] = 0;
   out_3730744472462246424[12] = 0;
   out_3730744472462246424[13] = 0;
   out_3730744472462246424[14] = 0;
   out_3730744472462246424[15] = 0;
   out_3730744472462246424[16] = 0;
   out_3730744472462246424[17] = 0;
   out_3730744472462246424[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3730744472462246424[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3730744472462246424[20] = 0;
   out_3730744472462246424[21] = 0;
   out_3730744472462246424[22] = 0;
   out_3730744472462246424[23] = 0;
   out_3730744472462246424[24] = 0;
   out_3730744472462246424[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3730744472462246424[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3730744472462246424[27] = 0;
   out_3730744472462246424[28] = 0;
   out_3730744472462246424[29] = 0;
   out_3730744472462246424[30] = 0;
   out_3730744472462246424[31] = 0;
   out_3730744472462246424[32] = 0;
   out_3730744472462246424[33] = 0;
   out_3730744472462246424[34] = 0;
   out_3730744472462246424[35] = 0;
   out_3730744472462246424[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3730744472462246424[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3730744472462246424[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3730744472462246424[39] = 0;
   out_3730744472462246424[40] = 0;
   out_3730744472462246424[41] = 0;
   out_3730744472462246424[42] = 0;
   out_3730744472462246424[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3730744472462246424[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3730744472462246424[45] = 0;
   out_3730744472462246424[46] = 0;
   out_3730744472462246424[47] = 0;
   out_3730744472462246424[48] = 0;
   out_3730744472462246424[49] = 0;
   out_3730744472462246424[50] = 0;
   out_3730744472462246424[51] = 0;
   out_3730744472462246424[52] = 0;
   out_3730744472462246424[53] = 0;
   out_3730744472462246424[54] = 0;
   out_3730744472462246424[55] = 0;
   out_3730744472462246424[56] = 0;
   out_3730744472462246424[57] = 1;
   out_3730744472462246424[58] = 0;
   out_3730744472462246424[59] = 0;
   out_3730744472462246424[60] = 0;
   out_3730744472462246424[61] = 0;
   out_3730744472462246424[62] = 0;
   out_3730744472462246424[63] = 0;
   out_3730744472462246424[64] = 0;
   out_3730744472462246424[65] = 0;
   out_3730744472462246424[66] = dt;
   out_3730744472462246424[67] = 0;
   out_3730744472462246424[68] = 0;
   out_3730744472462246424[69] = 0;
   out_3730744472462246424[70] = 0;
   out_3730744472462246424[71] = 0;
   out_3730744472462246424[72] = 0;
   out_3730744472462246424[73] = 0;
   out_3730744472462246424[74] = 0;
   out_3730744472462246424[75] = 0;
   out_3730744472462246424[76] = 1;
   out_3730744472462246424[77] = 0;
   out_3730744472462246424[78] = 0;
   out_3730744472462246424[79] = 0;
   out_3730744472462246424[80] = 0;
   out_3730744472462246424[81] = 0;
   out_3730744472462246424[82] = 0;
   out_3730744472462246424[83] = 0;
   out_3730744472462246424[84] = 0;
   out_3730744472462246424[85] = dt;
   out_3730744472462246424[86] = 0;
   out_3730744472462246424[87] = 0;
   out_3730744472462246424[88] = 0;
   out_3730744472462246424[89] = 0;
   out_3730744472462246424[90] = 0;
   out_3730744472462246424[91] = 0;
   out_3730744472462246424[92] = 0;
   out_3730744472462246424[93] = 0;
   out_3730744472462246424[94] = 0;
   out_3730744472462246424[95] = 1;
   out_3730744472462246424[96] = 0;
   out_3730744472462246424[97] = 0;
   out_3730744472462246424[98] = 0;
   out_3730744472462246424[99] = 0;
   out_3730744472462246424[100] = 0;
   out_3730744472462246424[101] = 0;
   out_3730744472462246424[102] = 0;
   out_3730744472462246424[103] = 0;
   out_3730744472462246424[104] = dt;
   out_3730744472462246424[105] = 0;
   out_3730744472462246424[106] = 0;
   out_3730744472462246424[107] = 0;
   out_3730744472462246424[108] = 0;
   out_3730744472462246424[109] = 0;
   out_3730744472462246424[110] = 0;
   out_3730744472462246424[111] = 0;
   out_3730744472462246424[112] = 0;
   out_3730744472462246424[113] = 0;
   out_3730744472462246424[114] = 1;
   out_3730744472462246424[115] = 0;
   out_3730744472462246424[116] = 0;
   out_3730744472462246424[117] = 0;
   out_3730744472462246424[118] = 0;
   out_3730744472462246424[119] = 0;
   out_3730744472462246424[120] = 0;
   out_3730744472462246424[121] = 0;
   out_3730744472462246424[122] = 0;
   out_3730744472462246424[123] = 0;
   out_3730744472462246424[124] = 0;
   out_3730744472462246424[125] = 0;
   out_3730744472462246424[126] = 0;
   out_3730744472462246424[127] = 0;
   out_3730744472462246424[128] = 0;
   out_3730744472462246424[129] = 0;
   out_3730744472462246424[130] = 0;
   out_3730744472462246424[131] = 0;
   out_3730744472462246424[132] = 0;
   out_3730744472462246424[133] = 1;
   out_3730744472462246424[134] = 0;
   out_3730744472462246424[135] = 0;
   out_3730744472462246424[136] = 0;
   out_3730744472462246424[137] = 0;
   out_3730744472462246424[138] = 0;
   out_3730744472462246424[139] = 0;
   out_3730744472462246424[140] = 0;
   out_3730744472462246424[141] = 0;
   out_3730744472462246424[142] = 0;
   out_3730744472462246424[143] = 0;
   out_3730744472462246424[144] = 0;
   out_3730744472462246424[145] = 0;
   out_3730744472462246424[146] = 0;
   out_3730744472462246424[147] = 0;
   out_3730744472462246424[148] = 0;
   out_3730744472462246424[149] = 0;
   out_3730744472462246424[150] = 0;
   out_3730744472462246424[151] = 0;
   out_3730744472462246424[152] = 1;
   out_3730744472462246424[153] = 0;
   out_3730744472462246424[154] = 0;
   out_3730744472462246424[155] = 0;
   out_3730744472462246424[156] = 0;
   out_3730744472462246424[157] = 0;
   out_3730744472462246424[158] = 0;
   out_3730744472462246424[159] = 0;
   out_3730744472462246424[160] = 0;
   out_3730744472462246424[161] = 0;
   out_3730744472462246424[162] = 0;
   out_3730744472462246424[163] = 0;
   out_3730744472462246424[164] = 0;
   out_3730744472462246424[165] = 0;
   out_3730744472462246424[166] = 0;
   out_3730744472462246424[167] = 0;
   out_3730744472462246424[168] = 0;
   out_3730744472462246424[169] = 0;
   out_3730744472462246424[170] = 0;
   out_3730744472462246424[171] = 1;
   out_3730744472462246424[172] = 0;
   out_3730744472462246424[173] = 0;
   out_3730744472462246424[174] = 0;
   out_3730744472462246424[175] = 0;
   out_3730744472462246424[176] = 0;
   out_3730744472462246424[177] = 0;
   out_3730744472462246424[178] = 0;
   out_3730744472462246424[179] = 0;
   out_3730744472462246424[180] = 0;
   out_3730744472462246424[181] = 0;
   out_3730744472462246424[182] = 0;
   out_3730744472462246424[183] = 0;
   out_3730744472462246424[184] = 0;
   out_3730744472462246424[185] = 0;
   out_3730744472462246424[186] = 0;
   out_3730744472462246424[187] = 0;
   out_3730744472462246424[188] = 0;
   out_3730744472462246424[189] = 0;
   out_3730744472462246424[190] = 1;
   out_3730744472462246424[191] = 0;
   out_3730744472462246424[192] = 0;
   out_3730744472462246424[193] = 0;
   out_3730744472462246424[194] = 0;
   out_3730744472462246424[195] = 0;
   out_3730744472462246424[196] = 0;
   out_3730744472462246424[197] = 0;
   out_3730744472462246424[198] = 0;
   out_3730744472462246424[199] = 0;
   out_3730744472462246424[200] = 0;
   out_3730744472462246424[201] = 0;
   out_3730744472462246424[202] = 0;
   out_3730744472462246424[203] = 0;
   out_3730744472462246424[204] = 0;
   out_3730744472462246424[205] = 0;
   out_3730744472462246424[206] = 0;
   out_3730744472462246424[207] = 0;
   out_3730744472462246424[208] = 0;
   out_3730744472462246424[209] = 1;
   out_3730744472462246424[210] = 0;
   out_3730744472462246424[211] = 0;
   out_3730744472462246424[212] = 0;
   out_3730744472462246424[213] = 0;
   out_3730744472462246424[214] = 0;
   out_3730744472462246424[215] = 0;
   out_3730744472462246424[216] = 0;
   out_3730744472462246424[217] = 0;
   out_3730744472462246424[218] = 0;
   out_3730744472462246424[219] = 0;
   out_3730744472462246424[220] = 0;
   out_3730744472462246424[221] = 0;
   out_3730744472462246424[222] = 0;
   out_3730744472462246424[223] = 0;
   out_3730744472462246424[224] = 0;
   out_3730744472462246424[225] = 0;
   out_3730744472462246424[226] = 0;
   out_3730744472462246424[227] = 0;
   out_3730744472462246424[228] = 1;
   out_3730744472462246424[229] = 0;
   out_3730744472462246424[230] = 0;
   out_3730744472462246424[231] = 0;
   out_3730744472462246424[232] = 0;
   out_3730744472462246424[233] = 0;
   out_3730744472462246424[234] = 0;
   out_3730744472462246424[235] = 0;
   out_3730744472462246424[236] = 0;
   out_3730744472462246424[237] = 0;
   out_3730744472462246424[238] = 0;
   out_3730744472462246424[239] = 0;
   out_3730744472462246424[240] = 0;
   out_3730744472462246424[241] = 0;
   out_3730744472462246424[242] = 0;
   out_3730744472462246424[243] = 0;
   out_3730744472462246424[244] = 0;
   out_3730744472462246424[245] = 0;
   out_3730744472462246424[246] = 0;
   out_3730744472462246424[247] = 1;
   out_3730744472462246424[248] = 0;
   out_3730744472462246424[249] = 0;
   out_3730744472462246424[250] = 0;
   out_3730744472462246424[251] = 0;
   out_3730744472462246424[252] = 0;
   out_3730744472462246424[253] = 0;
   out_3730744472462246424[254] = 0;
   out_3730744472462246424[255] = 0;
   out_3730744472462246424[256] = 0;
   out_3730744472462246424[257] = 0;
   out_3730744472462246424[258] = 0;
   out_3730744472462246424[259] = 0;
   out_3730744472462246424[260] = 0;
   out_3730744472462246424[261] = 0;
   out_3730744472462246424[262] = 0;
   out_3730744472462246424[263] = 0;
   out_3730744472462246424[264] = 0;
   out_3730744472462246424[265] = 0;
   out_3730744472462246424[266] = 1;
   out_3730744472462246424[267] = 0;
   out_3730744472462246424[268] = 0;
   out_3730744472462246424[269] = 0;
   out_3730744472462246424[270] = 0;
   out_3730744472462246424[271] = 0;
   out_3730744472462246424[272] = 0;
   out_3730744472462246424[273] = 0;
   out_3730744472462246424[274] = 0;
   out_3730744472462246424[275] = 0;
   out_3730744472462246424[276] = 0;
   out_3730744472462246424[277] = 0;
   out_3730744472462246424[278] = 0;
   out_3730744472462246424[279] = 0;
   out_3730744472462246424[280] = 0;
   out_3730744472462246424[281] = 0;
   out_3730744472462246424[282] = 0;
   out_3730744472462246424[283] = 0;
   out_3730744472462246424[284] = 0;
   out_3730744472462246424[285] = 1;
   out_3730744472462246424[286] = 0;
   out_3730744472462246424[287] = 0;
   out_3730744472462246424[288] = 0;
   out_3730744472462246424[289] = 0;
   out_3730744472462246424[290] = 0;
   out_3730744472462246424[291] = 0;
   out_3730744472462246424[292] = 0;
   out_3730744472462246424[293] = 0;
   out_3730744472462246424[294] = 0;
   out_3730744472462246424[295] = 0;
   out_3730744472462246424[296] = 0;
   out_3730744472462246424[297] = 0;
   out_3730744472462246424[298] = 0;
   out_3730744472462246424[299] = 0;
   out_3730744472462246424[300] = 0;
   out_3730744472462246424[301] = 0;
   out_3730744472462246424[302] = 0;
   out_3730744472462246424[303] = 0;
   out_3730744472462246424[304] = 1;
   out_3730744472462246424[305] = 0;
   out_3730744472462246424[306] = 0;
   out_3730744472462246424[307] = 0;
   out_3730744472462246424[308] = 0;
   out_3730744472462246424[309] = 0;
   out_3730744472462246424[310] = 0;
   out_3730744472462246424[311] = 0;
   out_3730744472462246424[312] = 0;
   out_3730744472462246424[313] = 0;
   out_3730744472462246424[314] = 0;
   out_3730744472462246424[315] = 0;
   out_3730744472462246424[316] = 0;
   out_3730744472462246424[317] = 0;
   out_3730744472462246424[318] = 0;
   out_3730744472462246424[319] = 0;
   out_3730744472462246424[320] = 0;
   out_3730744472462246424[321] = 0;
   out_3730744472462246424[322] = 0;
   out_3730744472462246424[323] = 1;
}
void h_4(double *state, double *unused, double *out_5341722606028163908) {
   out_5341722606028163908[0] = state[6] + state[9];
   out_5341722606028163908[1] = state[7] + state[10];
   out_5341722606028163908[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5096550783233751580) {
   out_5096550783233751580[0] = 0;
   out_5096550783233751580[1] = 0;
   out_5096550783233751580[2] = 0;
   out_5096550783233751580[3] = 0;
   out_5096550783233751580[4] = 0;
   out_5096550783233751580[5] = 0;
   out_5096550783233751580[6] = 1;
   out_5096550783233751580[7] = 0;
   out_5096550783233751580[8] = 0;
   out_5096550783233751580[9] = 1;
   out_5096550783233751580[10] = 0;
   out_5096550783233751580[11] = 0;
   out_5096550783233751580[12] = 0;
   out_5096550783233751580[13] = 0;
   out_5096550783233751580[14] = 0;
   out_5096550783233751580[15] = 0;
   out_5096550783233751580[16] = 0;
   out_5096550783233751580[17] = 0;
   out_5096550783233751580[18] = 0;
   out_5096550783233751580[19] = 0;
   out_5096550783233751580[20] = 0;
   out_5096550783233751580[21] = 0;
   out_5096550783233751580[22] = 0;
   out_5096550783233751580[23] = 0;
   out_5096550783233751580[24] = 0;
   out_5096550783233751580[25] = 1;
   out_5096550783233751580[26] = 0;
   out_5096550783233751580[27] = 0;
   out_5096550783233751580[28] = 1;
   out_5096550783233751580[29] = 0;
   out_5096550783233751580[30] = 0;
   out_5096550783233751580[31] = 0;
   out_5096550783233751580[32] = 0;
   out_5096550783233751580[33] = 0;
   out_5096550783233751580[34] = 0;
   out_5096550783233751580[35] = 0;
   out_5096550783233751580[36] = 0;
   out_5096550783233751580[37] = 0;
   out_5096550783233751580[38] = 0;
   out_5096550783233751580[39] = 0;
   out_5096550783233751580[40] = 0;
   out_5096550783233751580[41] = 0;
   out_5096550783233751580[42] = 0;
   out_5096550783233751580[43] = 0;
   out_5096550783233751580[44] = 1;
   out_5096550783233751580[45] = 0;
   out_5096550783233751580[46] = 0;
   out_5096550783233751580[47] = 1;
   out_5096550783233751580[48] = 0;
   out_5096550783233751580[49] = 0;
   out_5096550783233751580[50] = 0;
   out_5096550783233751580[51] = 0;
   out_5096550783233751580[52] = 0;
   out_5096550783233751580[53] = 0;
}
void h_10(double *state, double *unused, double *out_9209642980587727009) {
   out_9209642980587727009[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_9209642980587727009[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_9209642980587727009[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2564039051245540813) {
   out_2564039051245540813[0] = 0;
   out_2564039051245540813[1] = 9.8100000000000005*cos(state[1]);
   out_2564039051245540813[2] = 0;
   out_2564039051245540813[3] = 0;
   out_2564039051245540813[4] = -state[8];
   out_2564039051245540813[5] = state[7];
   out_2564039051245540813[6] = 0;
   out_2564039051245540813[7] = state[5];
   out_2564039051245540813[8] = -state[4];
   out_2564039051245540813[9] = 0;
   out_2564039051245540813[10] = 0;
   out_2564039051245540813[11] = 0;
   out_2564039051245540813[12] = 1;
   out_2564039051245540813[13] = 0;
   out_2564039051245540813[14] = 0;
   out_2564039051245540813[15] = 1;
   out_2564039051245540813[16] = 0;
   out_2564039051245540813[17] = 0;
   out_2564039051245540813[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2564039051245540813[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2564039051245540813[20] = 0;
   out_2564039051245540813[21] = state[8];
   out_2564039051245540813[22] = 0;
   out_2564039051245540813[23] = -state[6];
   out_2564039051245540813[24] = -state[5];
   out_2564039051245540813[25] = 0;
   out_2564039051245540813[26] = state[3];
   out_2564039051245540813[27] = 0;
   out_2564039051245540813[28] = 0;
   out_2564039051245540813[29] = 0;
   out_2564039051245540813[30] = 0;
   out_2564039051245540813[31] = 1;
   out_2564039051245540813[32] = 0;
   out_2564039051245540813[33] = 0;
   out_2564039051245540813[34] = 1;
   out_2564039051245540813[35] = 0;
   out_2564039051245540813[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2564039051245540813[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2564039051245540813[38] = 0;
   out_2564039051245540813[39] = -state[7];
   out_2564039051245540813[40] = state[6];
   out_2564039051245540813[41] = 0;
   out_2564039051245540813[42] = state[4];
   out_2564039051245540813[43] = -state[3];
   out_2564039051245540813[44] = 0;
   out_2564039051245540813[45] = 0;
   out_2564039051245540813[46] = 0;
   out_2564039051245540813[47] = 0;
   out_2564039051245540813[48] = 0;
   out_2564039051245540813[49] = 0;
   out_2564039051245540813[50] = 1;
   out_2564039051245540813[51] = 0;
   out_2564039051245540813[52] = 0;
   out_2564039051245540813[53] = 1;
}
void h_13(double *state, double *unused, double *out_7516940390179027057) {
   out_7516940390179027057[0] = state[3];
   out_7516940390179027057[1] = state[4];
   out_7516940390179027057[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8308824608566084381) {
   out_8308824608566084381[0] = 0;
   out_8308824608566084381[1] = 0;
   out_8308824608566084381[2] = 0;
   out_8308824608566084381[3] = 1;
   out_8308824608566084381[4] = 0;
   out_8308824608566084381[5] = 0;
   out_8308824608566084381[6] = 0;
   out_8308824608566084381[7] = 0;
   out_8308824608566084381[8] = 0;
   out_8308824608566084381[9] = 0;
   out_8308824608566084381[10] = 0;
   out_8308824608566084381[11] = 0;
   out_8308824608566084381[12] = 0;
   out_8308824608566084381[13] = 0;
   out_8308824608566084381[14] = 0;
   out_8308824608566084381[15] = 0;
   out_8308824608566084381[16] = 0;
   out_8308824608566084381[17] = 0;
   out_8308824608566084381[18] = 0;
   out_8308824608566084381[19] = 0;
   out_8308824608566084381[20] = 0;
   out_8308824608566084381[21] = 0;
   out_8308824608566084381[22] = 1;
   out_8308824608566084381[23] = 0;
   out_8308824608566084381[24] = 0;
   out_8308824608566084381[25] = 0;
   out_8308824608566084381[26] = 0;
   out_8308824608566084381[27] = 0;
   out_8308824608566084381[28] = 0;
   out_8308824608566084381[29] = 0;
   out_8308824608566084381[30] = 0;
   out_8308824608566084381[31] = 0;
   out_8308824608566084381[32] = 0;
   out_8308824608566084381[33] = 0;
   out_8308824608566084381[34] = 0;
   out_8308824608566084381[35] = 0;
   out_8308824608566084381[36] = 0;
   out_8308824608566084381[37] = 0;
   out_8308824608566084381[38] = 0;
   out_8308824608566084381[39] = 0;
   out_8308824608566084381[40] = 0;
   out_8308824608566084381[41] = 1;
   out_8308824608566084381[42] = 0;
   out_8308824608566084381[43] = 0;
   out_8308824608566084381[44] = 0;
   out_8308824608566084381[45] = 0;
   out_8308824608566084381[46] = 0;
   out_8308824608566084381[47] = 0;
   out_8308824608566084381[48] = 0;
   out_8308824608566084381[49] = 0;
   out_8308824608566084381[50] = 0;
   out_8308824608566084381[51] = 0;
   out_8308824608566084381[52] = 0;
   out_8308824608566084381[53] = 0;
}
void h_14(double *state, double *unused, double *out_4591991634188895423) {
   out_4591991634188895423[0] = state[6];
   out_4591991634188895423[1] = state[7];
   out_4591991634188895423[2] = state[8];
}
void H_14(double *state, double *unused, double *out_9059791639573236109) {
   out_9059791639573236109[0] = 0;
   out_9059791639573236109[1] = 0;
   out_9059791639573236109[2] = 0;
   out_9059791639573236109[3] = 0;
   out_9059791639573236109[4] = 0;
   out_9059791639573236109[5] = 0;
   out_9059791639573236109[6] = 1;
   out_9059791639573236109[7] = 0;
   out_9059791639573236109[8] = 0;
   out_9059791639573236109[9] = 0;
   out_9059791639573236109[10] = 0;
   out_9059791639573236109[11] = 0;
   out_9059791639573236109[12] = 0;
   out_9059791639573236109[13] = 0;
   out_9059791639573236109[14] = 0;
   out_9059791639573236109[15] = 0;
   out_9059791639573236109[16] = 0;
   out_9059791639573236109[17] = 0;
   out_9059791639573236109[18] = 0;
   out_9059791639573236109[19] = 0;
   out_9059791639573236109[20] = 0;
   out_9059791639573236109[21] = 0;
   out_9059791639573236109[22] = 0;
   out_9059791639573236109[23] = 0;
   out_9059791639573236109[24] = 0;
   out_9059791639573236109[25] = 1;
   out_9059791639573236109[26] = 0;
   out_9059791639573236109[27] = 0;
   out_9059791639573236109[28] = 0;
   out_9059791639573236109[29] = 0;
   out_9059791639573236109[30] = 0;
   out_9059791639573236109[31] = 0;
   out_9059791639573236109[32] = 0;
   out_9059791639573236109[33] = 0;
   out_9059791639573236109[34] = 0;
   out_9059791639573236109[35] = 0;
   out_9059791639573236109[36] = 0;
   out_9059791639573236109[37] = 0;
   out_9059791639573236109[38] = 0;
   out_9059791639573236109[39] = 0;
   out_9059791639573236109[40] = 0;
   out_9059791639573236109[41] = 0;
   out_9059791639573236109[42] = 0;
   out_9059791639573236109[43] = 0;
   out_9059791639573236109[44] = 1;
   out_9059791639573236109[45] = 0;
   out_9059791639573236109[46] = 0;
   out_9059791639573236109[47] = 0;
   out_9059791639573236109[48] = 0;
   out_9059791639573236109[49] = 0;
   out_9059791639573236109[50] = 0;
   out_9059791639573236109[51] = 0;
   out_9059791639573236109[52] = 0;
   out_9059791639573236109[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8015077839077896466) {
  err_fun(nom_x, delta_x, out_8015077839077896466);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_120875525776824592) {
  inv_err_fun(nom_x, true_x, out_120875525776824592);
}
void pose_H_mod_fun(double *state, double *out_6916249509140048441) {
  H_mod_fun(state, out_6916249509140048441);
}
void pose_f_fun(double *state, double dt, double *out_4090535296156790500) {
  f_fun(state,  dt, out_4090535296156790500);
}
void pose_F_fun(double *state, double dt, double *out_3730744472462246424) {
  F_fun(state,  dt, out_3730744472462246424);
}
void pose_h_4(double *state, double *unused, double *out_5341722606028163908) {
  h_4(state, unused, out_5341722606028163908);
}
void pose_H_4(double *state, double *unused, double *out_5096550783233751580) {
  H_4(state, unused, out_5096550783233751580);
}
void pose_h_10(double *state, double *unused, double *out_9209642980587727009) {
  h_10(state, unused, out_9209642980587727009);
}
void pose_H_10(double *state, double *unused, double *out_2564039051245540813) {
  H_10(state, unused, out_2564039051245540813);
}
void pose_h_13(double *state, double *unused, double *out_7516940390179027057) {
  h_13(state, unused, out_7516940390179027057);
}
void pose_H_13(double *state, double *unused, double *out_8308824608566084381) {
  H_13(state, unused, out_8308824608566084381);
}
void pose_h_14(double *state, double *unused, double *out_4591991634188895423) {
  h_14(state, unused, out_4591991634188895423);
}
void pose_H_14(double *state, double *unused, double *out_9059791639573236109) {
  H_14(state, unused, out_9059791639573236109);
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
