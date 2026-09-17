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
void err_fun(double *nom_x, double *delta_x, double *out_8619877196673941904) {
   out_8619877196673941904[0] = delta_x[0] + nom_x[0];
   out_8619877196673941904[1] = delta_x[1] + nom_x[1];
   out_8619877196673941904[2] = delta_x[2] + nom_x[2];
   out_8619877196673941904[3] = delta_x[3] + nom_x[3];
   out_8619877196673941904[4] = delta_x[4] + nom_x[4];
   out_8619877196673941904[5] = delta_x[5] + nom_x[5];
   out_8619877196673941904[6] = delta_x[6] + nom_x[6];
   out_8619877196673941904[7] = delta_x[7] + nom_x[7];
   out_8619877196673941904[8] = delta_x[8] + nom_x[8];
   out_8619877196673941904[9] = delta_x[9] + nom_x[9];
   out_8619877196673941904[10] = delta_x[10] + nom_x[10];
   out_8619877196673941904[11] = delta_x[11] + nom_x[11];
   out_8619877196673941904[12] = delta_x[12] + nom_x[12];
   out_8619877196673941904[13] = delta_x[13] + nom_x[13];
   out_8619877196673941904[14] = delta_x[14] + nom_x[14];
   out_8619877196673941904[15] = delta_x[15] + nom_x[15];
   out_8619877196673941904[16] = delta_x[16] + nom_x[16];
   out_8619877196673941904[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5079236499620164768) {
   out_5079236499620164768[0] = -nom_x[0] + true_x[0];
   out_5079236499620164768[1] = -nom_x[1] + true_x[1];
   out_5079236499620164768[2] = -nom_x[2] + true_x[2];
   out_5079236499620164768[3] = -nom_x[3] + true_x[3];
   out_5079236499620164768[4] = -nom_x[4] + true_x[4];
   out_5079236499620164768[5] = -nom_x[5] + true_x[5];
   out_5079236499620164768[6] = -nom_x[6] + true_x[6];
   out_5079236499620164768[7] = -nom_x[7] + true_x[7];
   out_5079236499620164768[8] = -nom_x[8] + true_x[8];
   out_5079236499620164768[9] = -nom_x[9] + true_x[9];
   out_5079236499620164768[10] = -nom_x[10] + true_x[10];
   out_5079236499620164768[11] = -nom_x[11] + true_x[11];
   out_5079236499620164768[12] = -nom_x[12] + true_x[12];
   out_5079236499620164768[13] = -nom_x[13] + true_x[13];
   out_5079236499620164768[14] = -nom_x[14] + true_x[14];
   out_5079236499620164768[15] = -nom_x[15] + true_x[15];
   out_5079236499620164768[16] = -nom_x[16] + true_x[16];
   out_5079236499620164768[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3834855492212920326) {
   out_3834855492212920326[0] = 1.0;
   out_3834855492212920326[1] = 0.0;
   out_3834855492212920326[2] = 0.0;
   out_3834855492212920326[3] = 0.0;
   out_3834855492212920326[4] = 0.0;
   out_3834855492212920326[5] = 0.0;
   out_3834855492212920326[6] = 0.0;
   out_3834855492212920326[7] = 0.0;
   out_3834855492212920326[8] = 0.0;
   out_3834855492212920326[9] = 0.0;
   out_3834855492212920326[10] = 0.0;
   out_3834855492212920326[11] = 0.0;
   out_3834855492212920326[12] = 0.0;
   out_3834855492212920326[13] = 0.0;
   out_3834855492212920326[14] = 0.0;
   out_3834855492212920326[15] = 0.0;
   out_3834855492212920326[16] = 0.0;
   out_3834855492212920326[17] = 0.0;
   out_3834855492212920326[18] = 0.0;
   out_3834855492212920326[19] = 1.0;
   out_3834855492212920326[20] = 0.0;
   out_3834855492212920326[21] = 0.0;
   out_3834855492212920326[22] = 0.0;
   out_3834855492212920326[23] = 0.0;
   out_3834855492212920326[24] = 0.0;
   out_3834855492212920326[25] = 0.0;
   out_3834855492212920326[26] = 0.0;
   out_3834855492212920326[27] = 0.0;
   out_3834855492212920326[28] = 0.0;
   out_3834855492212920326[29] = 0.0;
   out_3834855492212920326[30] = 0.0;
   out_3834855492212920326[31] = 0.0;
   out_3834855492212920326[32] = 0.0;
   out_3834855492212920326[33] = 0.0;
   out_3834855492212920326[34] = 0.0;
   out_3834855492212920326[35] = 0.0;
   out_3834855492212920326[36] = 0.0;
   out_3834855492212920326[37] = 0.0;
   out_3834855492212920326[38] = 1.0;
   out_3834855492212920326[39] = 0.0;
   out_3834855492212920326[40] = 0.0;
   out_3834855492212920326[41] = 0.0;
   out_3834855492212920326[42] = 0.0;
   out_3834855492212920326[43] = 0.0;
   out_3834855492212920326[44] = 0.0;
   out_3834855492212920326[45] = 0.0;
   out_3834855492212920326[46] = 0.0;
   out_3834855492212920326[47] = 0.0;
   out_3834855492212920326[48] = 0.0;
   out_3834855492212920326[49] = 0.0;
   out_3834855492212920326[50] = 0.0;
   out_3834855492212920326[51] = 0.0;
   out_3834855492212920326[52] = 0.0;
   out_3834855492212920326[53] = 0.0;
   out_3834855492212920326[54] = 0.0;
   out_3834855492212920326[55] = 0.0;
   out_3834855492212920326[56] = 0.0;
   out_3834855492212920326[57] = 1.0;
   out_3834855492212920326[58] = 0.0;
   out_3834855492212920326[59] = 0.0;
   out_3834855492212920326[60] = 0.0;
   out_3834855492212920326[61] = 0.0;
   out_3834855492212920326[62] = 0.0;
   out_3834855492212920326[63] = 0.0;
   out_3834855492212920326[64] = 0.0;
   out_3834855492212920326[65] = 0.0;
   out_3834855492212920326[66] = 0.0;
   out_3834855492212920326[67] = 0.0;
   out_3834855492212920326[68] = 0.0;
   out_3834855492212920326[69] = 0.0;
   out_3834855492212920326[70] = 0.0;
   out_3834855492212920326[71] = 0.0;
   out_3834855492212920326[72] = 0.0;
   out_3834855492212920326[73] = 0.0;
   out_3834855492212920326[74] = 0.0;
   out_3834855492212920326[75] = 0.0;
   out_3834855492212920326[76] = 1.0;
   out_3834855492212920326[77] = 0.0;
   out_3834855492212920326[78] = 0.0;
   out_3834855492212920326[79] = 0.0;
   out_3834855492212920326[80] = 0.0;
   out_3834855492212920326[81] = 0.0;
   out_3834855492212920326[82] = 0.0;
   out_3834855492212920326[83] = 0.0;
   out_3834855492212920326[84] = 0.0;
   out_3834855492212920326[85] = 0.0;
   out_3834855492212920326[86] = 0.0;
   out_3834855492212920326[87] = 0.0;
   out_3834855492212920326[88] = 0.0;
   out_3834855492212920326[89] = 0.0;
   out_3834855492212920326[90] = 0.0;
   out_3834855492212920326[91] = 0.0;
   out_3834855492212920326[92] = 0.0;
   out_3834855492212920326[93] = 0.0;
   out_3834855492212920326[94] = 0.0;
   out_3834855492212920326[95] = 1.0;
   out_3834855492212920326[96] = 0.0;
   out_3834855492212920326[97] = 0.0;
   out_3834855492212920326[98] = 0.0;
   out_3834855492212920326[99] = 0.0;
   out_3834855492212920326[100] = 0.0;
   out_3834855492212920326[101] = 0.0;
   out_3834855492212920326[102] = 0.0;
   out_3834855492212920326[103] = 0.0;
   out_3834855492212920326[104] = 0.0;
   out_3834855492212920326[105] = 0.0;
   out_3834855492212920326[106] = 0.0;
   out_3834855492212920326[107] = 0.0;
   out_3834855492212920326[108] = 0.0;
   out_3834855492212920326[109] = 0.0;
   out_3834855492212920326[110] = 0.0;
   out_3834855492212920326[111] = 0.0;
   out_3834855492212920326[112] = 0.0;
   out_3834855492212920326[113] = 0.0;
   out_3834855492212920326[114] = 1.0;
   out_3834855492212920326[115] = 0.0;
   out_3834855492212920326[116] = 0.0;
   out_3834855492212920326[117] = 0.0;
   out_3834855492212920326[118] = 0.0;
   out_3834855492212920326[119] = 0.0;
   out_3834855492212920326[120] = 0.0;
   out_3834855492212920326[121] = 0.0;
   out_3834855492212920326[122] = 0.0;
   out_3834855492212920326[123] = 0.0;
   out_3834855492212920326[124] = 0.0;
   out_3834855492212920326[125] = 0.0;
   out_3834855492212920326[126] = 0.0;
   out_3834855492212920326[127] = 0.0;
   out_3834855492212920326[128] = 0.0;
   out_3834855492212920326[129] = 0.0;
   out_3834855492212920326[130] = 0.0;
   out_3834855492212920326[131] = 0.0;
   out_3834855492212920326[132] = 0.0;
   out_3834855492212920326[133] = 1.0;
   out_3834855492212920326[134] = 0.0;
   out_3834855492212920326[135] = 0.0;
   out_3834855492212920326[136] = 0.0;
   out_3834855492212920326[137] = 0.0;
   out_3834855492212920326[138] = 0.0;
   out_3834855492212920326[139] = 0.0;
   out_3834855492212920326[140] = 0.0;
   out_3834855492212920326[141] = 0.0;
   out_3834855492212920326[142] = 0.0;
   out_3834855492212920326[143] = 0.0;
   out_3834855492212920326[144] = 0.0;
   out_3834855492212920326[145] = 0.0;
   out_3834855492212920326[146] = 0.0;
   out_3834855492212920326[147] = 0.0;
   out_3834855492212920326[148] = 0.0;
   out_3834855492212920326[149] = 0.0;
   out_3834855492212920326[150] = 0.0;
   out_3834855492212920326[151] = 0.0;
   out_3834855492212920326[152] = 1.0;
   out_3834855492212920326[153] = 0.0;
   out_3834855492212920326[154] = 0.0;
   out_3834855492212920326[155] = 0.0;
   out_3834855492212920326[156] = 0.0;
   out_3834855492212920326[157] = 0.0;
   out_3834855492212920326[158] = 0.0;
   out_3834855492212920326[159] = 0.0;
   out_3834855492212920326[160] = 0.0;
   out_3834855492212920326[161] = 0.0;
   out_3834855492212920326[162] = 0.0;
   out_3834855492212920326[163] = 0.0;
   out_3834855492212920326[164] = 0.0;
   out_3834855492212920326[165] = 0.0;
   out_3834855492212920326[166] = 0.0;
   out_3834855492212920326[167] = 0.0;
   out_3834855492212920326[168] = 0.0;
   out_3834855492212920326[169] = 0.0;
   out_3834855492212920326[170] = 0.0;
   out_3834855492212920326[171] = 1.0;
   out_3834855492212920326[172] = 0.0;
   out_3834855492212920326[173] = 0.0;
   out_3834855492212920326[174] = 0.0;
   out_3834855492212920326[175] = 0.0;
   out_3834855492212920326[176] = 0.0;
   out_3834855492212920326[177] = 0.0;
   out_3834855492212920326[178] = 0.0;
   out_3834855492212920326[179] = 0.0;
   out_3834855492212920326[180] = 0.0;
   out_3834855492212920326[181] = 0.0;
   out_3834855492212920326[182] = 0.0;
   out_3834855492212920326[183] = 0.0;
   out_3834855492212920326[184] = 0.0;
   out_3834855492212920326[185] = 0.0;
   out_3834855492212920326[186] = 0.0;
   out_3834855492212920326[187] = 0.0;
   out_3834855492212920326[188] = 0.0;
   out_3834855492212920326[189] = 0.0;
   out_3834855492212920326[190] = 1.0;
   out_3834855492212920326[191] = 0.0;
   out_3834855492212920326[192] = 0.0;
   out_3834855492212920326[193] = 0.0;
   out_3834855492212920326[194] = 0.0;
   out_3834855492212920326[195] = 0.0;
   out_3834855492212920326[196] = 0.0;
   out_3834855492212920326[197] = 0.0;
   out_3834855492212920326[198] = 0.0;
   out_3834855492212920326[199] = 0.0;
   out_3834855492212920326[200] = 0.0;
   out_3834855492212920326[201] = 0.0;
   out_3834855492212920326[202] = 0.0;
   out_3834855492212920326[203] = 0.0;
   out_3834855492212920326[204] = 0.0;
   out_3834855492212920326[205] = 0.0;
   out_3834855492212920326[206] = 0.0;
   out_3834855492212920326[207] = 0.0;
   out_3834855492212920326[208] = 0.0;
   out_3834855492212920326[209] = 1.0;
   out_3834855492212920326[210] = 0.0;
   out_3834855492212920326[211] = 0.0;
   out_3834855492212920326[212] = 0.0;
   out_3834855492212920326[213] = 0.0;
   out_3834855492212920326[214] = 0.0;
   out_3834855492212920326[215] = 0.0;
   out_3834855492212920326[216] = 0.0;
   out_3834855492212920326[217] = 0.0;
   out_3834855492212920326[218] = 0.0;
   out_3834855492212920326[219] = 0.0;
   out_3834855492212920326[220] = 0.0;
   out_3834855492212920326[221] = 0.0;
   out_3834855492212920326[222] = 0.0;
   out_3834855492212920326[223] = 0.0;
   out_3834855492212920326[224] = 0.0;
   out_3834855492212920326[225] = 0.0;
   out_3834855492212920326[226] = 0.0;
   out_3834855492212920326[227] = 0.0;
   out_3834855492212920326[228] = 1.0;
   out_3834855492212920326[229] = 0.0;
   out_3834855492212920326[230] = 0.0;
   out_3834855492212920326[231] = 0.0;
   out_3834855492212920326[232] = 0.0;
   out_3834855492212920326[233] = 0.0;
   out_3834855492212920326[234] = 0.0;
   out_3834855492212920326[235] = 0.0;
   out_3834855492212920326[236] = 0.0;
   out_3834855492212920326[237] = 0.0;
   out_3834855492212920326[238] = 0.0;
   out_3834855492212920326[239] = 0.0;
   out_3834855492212920326[240] = 0.0;
   out_3834855492212920326[241] = 0.0;
   out_3834855492212920326[242] = 0.0;
   out_3834855492212920326[243] = 0.0;
   out_3834855492212920326[244] = 0.0;
   out_3834855492212920326[245] = 0.0;
   out_3834855492212920326[246] = 0.0;
   out_3834855492212920326[247] = 1.0;
   out_3834855492212920326[248] = 0.0;
   out_3834855492212920326[249] = 0.0;
   out_3834855492212920326[250] = 0.0;
   out_3834855492212920326[251] = 0.0;
   out_3834855492212920326[252] = 0.0;
   out_3834855492212920326[253] = 0.0;
   out_3834855492212920326[254] = 0.0;
   out_3834855492212920326[255] = 0.0;
   out_3834855492212920326[256] = 0.0;
   out_3834855492212920326[257] = 0.0;
   out_3834855492212920326[258] = 0.0;
   out_3834855492212920326[259] = 0.0;
   out_3834855492212920326[260] = 0.0;
   out_3834855492212920326[261] = 0.0;
   out_3834855492212920326[262] = 0.0;
   out_3834855492212920326[263] = 0.0;
   out_3834855492212920326[264] = 0.0;
   out_3834855492212920326[265] = 0.0;
   out_3834855492212920326[266] = 1.0;
   out_3834855492212920326[267] = 0.0;
   out_3834855492212920326[268] = 0.0;
   out_3834855492212920326[269] = 0.0;
   out_3834855492212920326[270] = 0.0;
   out_3834855492212920326[271] = 0.0;
   out_3834855492212920326[272] = 0.0;
   out_3834855492212920326[273] = 0.0;
   out_3834855492212920326[274] = 0.0;
   out_3834855492212920326[275] = 0.0;
   out_3834855492212920326[276] = 0.0;
   out_3834855492212920326[277] = 0.0;
   out_3834855492212920326[278] = 0.0;
   out_3834855492212920326[279] = 0.0;
   out_3834855492212920326[280] = 0.0;
   out_3834855492212920326[281] = 0.0;
   out_3834855492212920326[282] = 0.0;
   out_3834855492212920326[283] = 0.0;
   out_3834855492212920326[284] = 0.0;
   out_3834855492212920326[285] = 1.0;
   out_3834855492212920326[286] = 0.0;
   out_3834855492212920326[287] = 0.0;
   out_3834855492212920326[288] = 0.0;
   out_3834855492212920326[289] = 0.0;
   out_3834855492212920326[290] = 0.0;
   out_3834855492212920326[291] = 0.0;
   out_3834855492212920326[292] = 0.0;
   out_3834855492212920326[293] = 0.0;
   out_3834855492212920326[294] = 0.0;
   out_3834855492212920326[295] = 0.0;
   out_3834855492212920326[296] = 0.0;
   out_3834855492212920326[297] = 0.0;
   out_3834855492212920326[298] = 0.0;
   out_3834855492212920326[299] = 0.0;
   out_3834855492212920326[300] = 0.0;
   out_3834855492212920326[301] = 0.0;
   out_3834855492212920326[302] = 0.0;
   out_3834855492212920326[303] = 0.0;
   out_3834855492212920326[304] = 1.0;
   out_3834855492212920326[305] = 0.0;
   out_3834855492212920326[306] = 0.0;
   out_3834855492212920326[307] = 0.0;
   out_3834855492212920326[308] = 0.0;
   out_3834855492212920326[309] = 0.0;
   out_3834855492212920326[310] = 0.0;
   out_3834855492212920326[311] = 0.0;
   out_3834855492212920326[312] = 0.0;
   out_3834855492212920326[313] = 0.0;
   out_3834855492212920326[314] = 0.0;
   out_3834855492212920326[315] = 0.0;
   out_3834855492212920326[316] = 0.0;
   out_3834855492212920326[317] = 0.0;
   out_3834855492212920326[318] = 0.0;
   out_3834855492212920326[319] = 0.0;
   out_3834855492212920326[320] = 0.0;
   out_3834855492212920326[321] = 0.0;
   out_3834855492212920326[322] = 0.0;
   out_3834855492212920326[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_271549942577683268) {
   out_271549942577683268[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_271549942577683268[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_271549942577683268[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_271549942577683268[3] = dt*state[12] + state[3];
   out_271549942577683268[4] = dt*state[13] + state[4];
   out_271549942577683268[5] = dt*state[14] + state[5];
   out_271549942577683268[6] = state[6];
   out_271549942577683268[7] = state[7];
   out_271549942577683268[8] = state[8];
   out_271549942577683268[9] = state[9];
   out_271549942577683268[10] = state[10];
   out_271549942577683268[11] = state[11];
   out_271549942577683268[12] = state[12];
   out_271549942577683268[13] = state[13];
   out_271549942577683268[14] = state[14];
   out_271549942577683268[15] = state[15];
   out_271549942577683268[16] = state[16];
   out_271549942577683268[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8758390952692881982) {
   out_8758390952692881982[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8758390952692881982[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8758390952692881982[2] = 0;
   out_8758390952692881982[3] = 0;
   out_8758390952692881982[4] = 0;
   out_8758390952692881982[5] = 0;
   out_8758390952692881982[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8758390952692881982[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8758390952692881982[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8758390952692881982[9] = 0;
   out_8758390952692881982[10] = 0;
   out_8758390952692881982[11] = 0;
   out_8758390952692881982[12] = 0;
   out_8758390952692881982[13] = 0;
   out_8758390952692881982[14] = 0;
   out_8758390952692881982[15] = 0;
   out_8758390952692881982[16] = 0;
   out_8758390952692881982[17] = 0;
   out_8758390952692881982[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8758390952692881982[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8758390952692881982[20] = 0;
   out_8758390952692881982[21] = 0;
   out_8758390952692881982[22] = 0;
   out_8758390952692881982[23] = 0;
   out_8758390952692881982[24] = 0;
   out_8758390952692881982[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8758390952692881982[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8758390952692881982[27] = 0;
   out_8758390952692881982[28] = 0;
   out_8758390952692881982[29] = 0;
   out_8758390952692881982[30] = 0;
   out_8758390952692881982[31] = 0;
   out_8758390952692881982[32] = 0;
   out_8758390952692881982[33] = 0;
   out_8758390952692881982[34] = 0;
   out_8758390952692881982[35] = 0;
   out_8758390952692881982[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8758390952692881982[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8758390952692881982[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8758390952692881982[39] = 0;
   out_8758390952692881982[40] = 0;
   out_8758390952692881982[41] = 0;
   out_8758390952692881982[42] = 0;
   out_8758390952692881982[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8758390952692881982[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8758390952692881982[45] = 0;
   out_8758390952692881982[46] = 0;
   out_8758390952692881982[47] = 0;
   out_8758390952692881982[48] = 0;
   out_8758390952692881982[49] = 0;
   out_8758390952692881982[50] = 0;
   out_8758390952692881982[51] = 0;
   out_8758390952692881982[52] = 0;
   out_8758390952692881982[53] = 0;
   out_8758390952692881982[54] = 0;
   out_8758390952692881982[55] = 0;
   out_8758390952692881982[56] = 0;
   out_8758390952692881982[57] = 1;
   out_8758390952692881982[58] = 0;
   out_8758390952692881982[59] = 0;
   out_8758390952692881982[60] = 0;
   out_8758390952692881982[61] = 0;
   out_8758390952692881982[62] = 0;
   out_8758390952692881982[63] = 0;
   out_8758390952692881982[64] = 0;
   out_8758390952692881982[65] = 0;
   out_8758390952692881982[66] = dt;
   out_8758390952692881982[67] = 0;
   out_8758390952692881982[68] = 0;
   out_8758390952692881982[69] = 0;
   out_8758390952692881982[70] = 0;
   out_8758390952692881982[71] = 0;
   out_8758390952692881982[72] = 0;
   out_8758390952692881982[73] = 0;
   out_8758390952692881982[74] = 0;
   out_8758390952692881982[75] = 0;
   out_8758390952692881982[76] = 1;
   out_8758390952692881982[77] = 0;
   out_8758390952692881982[78] = 0;
   out_8758390952692881982[79] = 0;
   out_8758390952692881982[80] = 0;
   out_8758390952692881982[81] = 0;
   out_8758390952692881982[82] = 0;
   out_8758390952692881982[83] = 0;
   out_8758390952692881982[84] = 0;
   out_8758390952692881982[85] = dt;
   out_8758390952692881982[86] = 0;
   out_8758390952692881982[87] = 0;
   out_8758390952692881982[88] = 0;
   out_8758390952692881982[89] = 0;
   out_8758390952692881982[90] = 0;
   out_8758390952692881982[91] = 0;
   out_8758390952692881982[92] = 0;
   out_8758390952692881982[93] = 0;
   out_8758390952692881982[94] = 0;
   out_8758390952692881982[95] = 1;
   out_8758390952692881982[96] = 0;
   out_8758390952692881982[97] = 0;
   out_8758390952692881982[98] = 0;
   out_8758390952692881982[99] = 0;
   out_8758390952692881982[100] = 0;
   out_8758390952692881982[101] = 0;
   out_8758390952692881982[102] = 0;
   out_8758390952692881982[103] = 0;
   out_8758390952692881982[104] = dt;
   out_8758390952692881982[105] = 0;
   out_8758390952692881982[106] = 0;
   out_8758390952692881982[107] = 0;
   out_8758390952692881982[108] = 0;
   out_8758390952692881982[109] = 0;
   out_8758390952692881982[110] = 0;
   out_8758390952692881982[111] = 0;
   out_8758390952692881982[112] = 0;
   out_8758390952692881982[113] = 0;
   out_8758390952692881982[114] = 1;
   out_8758390952692881982[115] = 0;
   out_8758390952692881982[116] = 0;
   out_8758390952692881982[117] = 0;
   out_8758390952692881982[118] = 0;
   out_8758390952692881982[119] = 0;
   out_8758390952692881982[120] = 0;
   out_8758390952692881982[121] = 0;
   out_8758390952692881982[122] = 0;
   out_8758390952692881982[123] = 0;
   out_8758390952692881982[124] = 0;
   out_8758390952692881982[125] = 0;
   out_8758390952692881982[126] = 0;
   out_8758390952692881982[127] = 0;
   out_8758390952692881982[128] = 0;
   out_8758390952692881982[129] = 0;
   out_8758390952692881982[130] = 0;
   out_8758390952692881982[131] = 0;
   out_8758390952692881982[132] = 0;
   out_8758390952692881982[133] = 1;
   out_8758390952692881982[134] = 0;
   out_8758390952692881982[135] = 0;
   out_8758390952692881982[136] = 0;
   out_8758390952692881982[137] = 0;
   out_8758390952692881982[138] = 0;
   out_8758390952692881982[139] = 0;
   out_8758390952692881982[140] = 0;
   out_8758390952692881982[141] = 0;
   out_8758390952692881982[142] = 0;
   out_8758390952692881982[143] = 0;
   out_8758390952692881982[144] = 0;
   out_8758390952692881982[145] = 0;
   out_8758390952692881982[146] = 0;
   out_8758390952692881982[147] = 0;
   out_8758390952692881982[148] = 0;
   out_8758390952692881982[149] = 0;
   out_8758390952692881982[150] = 0;
   out_8758390952692881982[151] = 0;
   out_8758390952692881982[152] = 1;
   out_8758390952692881982[153] = 0;
   out_8758390952692881982[154] = 0;
   out_8758390952692881982[155] = 0;
   out_8758390952692881982[156] = 0;
   out_8758390952692881982[157] = 0;
   out_8758390952692881982[158] = 0;
   out_8758390952692881982[159] = 0;
   out_8758390952692881982[160] = 0;
   out_8758390952692881982[161] = 0;
   out_8758390952692881982[162] = 0;
   out_8758390952692881982[163] = 0;
   out_8758390952692881982[164] = 0;
   out_8758390952692881982[165] = 0;
   out_8758390952692881982[166] = 0;
   out_8758390952692881982[167] = 0;
   out_8758390952692881982[168] = 0;
   out_8758390952692881982[169] = 0;
   out_8758390952692881982[170] = 0;
   out_8758390952692881982[171] = 1;
   out_8758390952692881982[172] = 0;
   out_8758390952692881982[173] = 0;
   out_8758390952692881982[174] = 0;
   out_8758390952692881982[175] = 0;
   out_8758390952692881982[176] = 0;
   out_8758390952692881982[177] = 0;
   out_8758390952692881982[178] = 0;
   out_8758390952692881982[179] = 0;
   out_8758390952692881982[180] = 0;
   out_8758390952692881982[181] = 0;
   out_8758390952692881982[182] = 0;
   out_8758390952692881982[183] = 0;
   out_8758390952692881982[184] = 0;
   out_8758390952692881982[185] = 0;
   out_8758390952692881982[186] = 0;
   out_8758390952692881982[187] = 0;
   out_8758390952692881982[188] = 0;
   out_8758390952692881982[189] = 0;
   out_8758390952692881982[190] = 1;
   out_8758390952692881982[191] = 0;
   out_8758390952692881982[192] = 0;
   out_8758390952692881982[193] = 0;
   out_8758390952692881982[194] = 0;
   out_8758390952692881982[195] = 0;
   out_8758390952692881982[196] = 0;
   out_8758390952692881982[197] = 0;
   out_8758390952692881982[198] = 0;
   out_8758390952692881982[199] = 0;
   out_8758390952692881982[200] = 0;
   out_8758390952692881982[201] = 0;
   out_8758390952692881982[202] = 0;
   out_8758390952692881982[203] = 0;
   out_8758390952692881982[204] = 0;
   out_8758390952692881982[205] = 0;
   out_8758390952692881982[206] = 0;
   out_8758390952692881982[207] = 0;
   out_8758390952692881982[208] = 0;
   out_8758390952692881982[209] = 1;
   out_8758390952692881982[210] = 0;
   out_8758390952692881982[211] = 0;
   out_8758390952692881982[212] = 0;
   out_8758390952692881982[213] = 0;
   out_8758390952692881982[214] = 0;
   out_8758390952692881982[215] = 0;
   out_8758390952692881982[216] = 0;
   out_8758390952692881982[217] = 0;
   out_8758390952692881982[218] = 0;
   out_8758390952692881982[219] = 0;
   out_8758390952692881982[220] = 0;
   out_8758390952692881982[221] = 0;
   out_8758390952692881982[222] = 0;
   out_8758390952692881982[223] = 0;
   out_8758390952692881982[224] = 0;
   out_8758390952692881982[225] = 0;
   out_8758390952692881982[226] = 0;
   out_8758390952692881982[227] = 0;
   out_8758390952692881982[228] = 1;
   out_8758390952692881982[229] = 0;
   out_8758390952692881982[230] = 0;
   out_8758390952692881982[231] = 0;
   out_8758390952692881982[232] = 0;
   out_8758390952692881982[233] = 0;
   out_8758390952692881982[234] = 0;
   out_8758390952692881982[235] = 0;
   out_8758390952692881982[236] = 0;
   out_8758390952692881982[237] = 0;
   out_8758390952692881982[238] = 0;
   out_8758390952692881982[239] = 0;
   out_8758390952692881982[240] = 0;
   out_8758390952692881982[241] = 0;
   out_8758390952692881982[242] = 0;
   out_8758390952692881982[243] = 0;
   out_8758390952692881982[244] = 0;
   out_8758390952692881982[245] = 0;
   out_8758390952692881982[246] = 0;
   out_8758390952692881982[247] = 1;
   out_8758390952692881982[248] = 0;
   out_8758390952692881982[249] = 0;
   out_8758390952692881982[250] = 0;
   out_8758390952692881982[251] = 0;
   out_8758390952692881982[252] = 0;
   out_8758390952692881982[253] = 0;
   out_8758390952692881982[254] = 0;
   out_8758390952692881982[255] = 0;
   out_8758390952692881982[256] = 0;
   out_8758390952692881982[257] = 0;
   out_8758390952692881982[258] = 0;
   out_8758390952692881982[259] = 0;
   out_8758390952692881982[260] = 0;
   out_8758390952692881982[261] = 0;
   out_8758390952692881982[262] = 0;
   out_8758390952692881982[263] = 0;
   out_8758390952692881982[264] = 0;
   out_8758390952692881982[265] = 0;
   out_8758390952692881982[266] = 1;
   out_8758390952692881982[267] = 0;
   out_8758390952692881982[268] = 0;
   out_8758390952692881982[269] = 0;
   out_8758390952692881982[270] = 0;
   out_8758390952692881982[271] = 0;
   out_8758390952692881982[272] = 0;
   out_8758390952692881982[273] = 0;
   out_8758390952692881982[274] = 0;
   out_8758390952692881982[275] = 0;
   out_8758390952692881982[276] = 0;
   out_8758390952692881982[277] = 0;
   out_8758390952692881982[278] = 0;
   out_8758390952692881982[279] = 0;
   out_8758390952692881982[280] = 0;
   out_8758390952692881982[281] = 0;
   out_8758390952692881982[282] = 0;
   out_8758390952692881982[283] = 0;
   out_8758390952692881982[284] = 0;
   out_8758390952692881982[285] = 1;
   out_8758390952692881982[286] = 0;
   out_8758390952692881982[287] = 0;
   out_8758390952692881982[288] = 0;
   out_8758390952692881982[289] = 0;
   out_8758390952692881982[290] = 0;
   out_8758390952692881982[291] = 0;
   out_8758390952692881982[292] = 0;
   out_8758390952692881982[293] = 0;
   out_8758390952692881982[294] = 0;
   out_8758390952692881982[295] = 0;
   out_8758390952692881982[296] = 0;
   out_8758390952692881982[297] = 0;
   out_8758390952692881982[298] = 0;
   out_8758390952692881982[299] = 0;
   out_8758390952692881982[300] = 0;
   out_8758390952692881982[301] = 0;
   out_8758390952692881982[302] = 0;
   out_8758390952692881982[303] = 0;
   out_8758390952692881982[304] = 1;
   out_8758390952692881982[305] = 0;
   out_8758390952692881982[306] = 0;
   out_8758390952692881982[307] = 0;
   out_8758390952692881982[308] = 0;
   out_8758390952692881982[309] = 0;
   out_8758390952692881982[310] = 0;
   out_8758390952692881982[311] = 0;
   out_8758390952692881982[312] = 0;
   out_8758390952692881982[313] = 0;
   out_8758390952692881982[314] = 0;
   out_8758390952692881982[315] = 0;
   out_8758390952692881982[316] = 0;
   out_8758390952692881982[317] = 0;
   out_8758390952692881982[318] = 0;
   out_8758390952692881982[319] = 0;
   out_8758390952692881982[320] = 0;
   out_8758390952692881982[321] = 0;
   out_8758390952692881982[322] = 0;
   out_8758390952692881982[323] = 1;
}
void h_4(double *state, double *unused, double *out_4085392694727598368) {
   out_4085392694727598368[0] = state[6] + state[9];
   out_4085392694727598368[1] = state[7] + state[10];
   out_4085392694727598368[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3080694490158207719) {
   out_3080694490158207719[0] = 0;
   out_3080694490158207719[1] = 0;
   out_3080694490158207719[2] = 0;
   out_3080694490158207719[3] = 0;
   out_3080694490158207719[4] = 0;
   out_3080694490158207719[5] = 0;
   out_3080694490158207719[6] = 1;
   out_3080694490158207719[7] = 0;
   out_3080694490158207719[8] = 0;
   out_3080694490158207719[9] = 1;
   out_3080694490158207719[10] = 0;
   out_3080694490158207719[11] = 0;
   out_3080694490158207719[12] = 0;
   out_3080694490158207719[13] = 0;
   out_3080694490158207719[14] = 0;
   out_3080694490158207719[15] = 0;
   out_3080694490158207719[16] = 0;
   out_3080694490158207719[17] = 0;
   out_3080694490158207719[18] = 0;
   out_3080694490158207719[19] = 0;
   out_3080694490158207719[20] = 0;
   out_3080694490158207719[21] = 0;
   out_3080694490158207719[22] = 0;
   out_3080694490158207719[23] = 0;
   out_3080694490158207719[24] = 0;
   out_3080694490158207719[25] = 1;
   out_3080694490158207719[26] = 0;
   out_3080694490158207719[27] = 0;
   out_3080694490158207719[28] = 1;
   out_3080694490158207719[29] = 0;
   out_3080694490158207719[30] = 0;
   out_3080694490158207719[31] = 0;
   out_3080694490158207719[32] = 0;
   out_3080694490158207719[33] = 0;
   out_3080694490158207719[34] = 0;
   out_3080694490158207719[35] = 0;
   out_3080694490158207719[36] = 0;
   out_3080694490158207719[37] = 0;
   out_3080694490158207719[38] = 0;
   out_3080694490158207719[39] = 0;
   out_3080694490158207719[40] = 0;
   out_3080694490158207719[41] = 0;
   out_3080694490158207719[42] = 0;
   out_3080694490158207719[43] = 0;
   out_3080694490158207719[44] = 1;
   out_3080694490158207719[45] = 0;
   out_3080694490158207719[46] = 0;
   out_3080694490158207719[47] = 1;
   out_3080694490158207719[48] = 0;
   out_3080694490158207719[49] = 0;
   out_3080694490158207719[50] = 0;
   out_3080694490158207719[51] = 0;
   out_3080694490158207719[52] = 0;
   out_3080694490158207719[53] = 0;
}
void h_10(double *state, double *unused, double *out_8653843584460147373) {
   out_8653843584460147373[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8653843584460147373[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8653843584460147373[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1350506859556886668) {
   out_1350506859556886668[0] = 0;
   out_1350506859556886668[1] = 9.8100000000000005*cos(state[1]);
   out_1350506859556886668[2] = 0;
   out_1350506859556886668[3] = 0;
   out_1350506859556886668[4] = -state[8];
   out_1350506859556886668[5] = state[7];
   out_1350506859556886668[6] = 0;
   out_1350506859556886668[7] = state[5];
   out_1350506859556886668[8] = -state[4];
   out_1350506859556886668[9] = 0;
   out_1350506859556886668[10] = 0;
   out_1350506859556886668[11] = 0;
   out_1350506859556886668[12] = 1;
   out_1350506859556886668[13] = 0;
   out_1350506859556886668[14] = 0;
   out_1350506859556886668[15] = 1;
   out_1350506859556886668[16] = 0;
   out_1350506859556886668[17] = 0;
   out_1350506859556886668[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1350506859556886668[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1350506859556886668[20] = 0;
   out_1350506859556886668[21] = state[8];
   out_1350506859556886668[22] = 0;
   out_1350506859556886668[23] = -state[6];
   out_1350506859556886668[24] = -state[5];
   out_1350506859556886668[25] = 0;
   out_1350506859556886668[26] = state[3];
   out_1350506859556886668[27] = 0;
   out_1350506859556886668[28] = 0;
   out_1350506859556886668[29] = 0;
   out_1350506859556886668[30] = 0;
   out_1350506859556886668[31] = 1;
   out_1350506859556886668[32] = 0;
   out_1350506859556886668[33] = 0;
   out_1350506859556886668[34] = 1;
   out_1350506859556886668[35] = 0;
   out_1350506859556886668[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1350506859556886668[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1350506859556886668[38] = 0;
   out_1350506859556886668[39] = -state[7];
   out_1350506859556886668[40] = state[6];
   out_1350506859556886668[41] = 0;
   out_1350506859556886668[42] = state[4];
   out_1350506859556886668[43] = -state[3];
   out_1350506859556886668[44] = 0;
   out_1350506859556886668[45] = 0;
   out_1350506859556886668[46] = 0;
   out_1350506859556886668[47] = 0;
   out_1350506859556886668[48] = 0;
   out_1350506859556886668[49] = 0;
   out_1350506859556886668[50] = 1;
   out_1350506859556886668[51] = 0;
   out_1350506859556886668[52] = 0;
   out_1350506859556886668[53] = 1;
}
void h_13(double *state, double *unused, double *out_6805598292797670581) {
   out_6805598292797670581[0] = state[3];
   out_6805598292797670581[1] = state[4];
   out_6805598292797670581[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4529936718158493210) {
   out_4529936718158493210[0] = 0;
   out_4529936718158493210[1] = 0;
   out_4529936718158493210[2] = 0;
   out_4529936718158493210[3] = 1;
   out_4529936718158493210[4] = 0;
   out_4529936718158493210[5] = 0;
   out_4529936718158493210[6] = 0;
   out_4529936718158493210[7] = 0;
   out_4529936718158493210[8] = 0;
   out_4529936718158493210[9] = 0;
   out_4529936718158493210[10] = 0;
   out_4529936718158493210[11] = 0;
   out_4529936718158493210[12] = 0;
   out_4529936718158493210[13] = 0;
   out_4529936718158493210[14] = 0;
   out_4529936718158493210[15] = 0;
   out_4529936718158493210[16] = 0;
   out_4529936718158493210[17] = 0;
   out_4529936718158493210[18] = 0;
   out_4529936718158493210[19] = 0;
   out_4529936718158493210[20] = 0;
   out_4529936718158493210[21] = 0;
   out_4529936718158493210[22] = 1;
   out_4529936718158493210[23] = 0;
   out_4529936718158493210[24] = 0;
   out_4529936718158493210[25] = 0;
   out_4529936718158493210[26] = 0;
   out_4529936718158493210[27] = 0;
   out_4529936718158493210[28] = 0;
   out_4529936718158493210[29] = 0;
   out_4529936718158493210[30] = 0;
   out_4529936718158493210[31] = 0;
   out_4529936718158493210[32] = 0;
   out_4529936718158493210[33] = 0;
   out_4529936718158493210[34] = 0;
   out_4529936718158493210[35] = 0;
   out_4529936718158493210[36] = 0;
   out_4529936718158493210[37] = 0;
   out_4529936718158493210[38] = 0;
   out_4529936718158493210[39] = 0;
   out_4529936718158493210[40] = 0;
   out_4529936718158493210[41] = 1;
   out_4529936718158493210[42] = 0;
   out_4529936718158493210[43] = 0;
   out_4529936718158493210[44] = 0;
   out_4529936718158493210[45] = 0;
   out_4529936718158493210[46] = 0;
   out_4529936718158493210[47] = 0;
   out_4529936718158493210[48] = 0;
   out_4529936718158493210[49] = 0;
   out_4529936718158493210[50] = 0;
   out_4529936718158493210[51] = 0;
   out_4529936718158493210[52] = 0;
   out_4529936718158493210[53] = 0;
}
void h_14(double *state, double *unused, double *out_7201729596421949005) {
   out_7201729596421949005[0] = state[6];
   out_7201729596421949005[1] = state[7];
   out_7201729596421949005[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6163482922453580015) {
   out_6163482922453580015[0] = 0;
   out_6163482922453580015[1] = 0;
   out_6163482922453580015[2] = 0;
   out_6163482922453580015[3] = 0;
   out_6163482922453580015[4] = 0;
   out_6163482922453580015[5] = 0;
   out_6163482922453580015[6] = 1;
   out_6163482922453580015[7] = 0;
   out_6163482922453580015[8] = 0;
   out_6163482922453580015[9] = 0;
   out_6163482922453580015[10] = 0;
   out_6163482922453580015[11] = 0;
   out_6163482922453580015[12] = 0;
   out_6163482922453580015[13] = 0;
   out_6163482922453580015[14] = 0;
   out_6163482922453580015[15] = 0;
   out_6163482922453580015[16] = 0;
   out_6163482922453580015[17] = 0;
   out_6163482922453580015[18] = 0;
   out_6163482922453580015[19] = 0;
   out_6163482922453580015[20] = 0;
   out_6163482922453580015[21] = 0;
   out_6163482922453580015[22] = 0;
   out_6163482922453580015[23] = 0;
   out_6163482922453580015[24] = 0;
   out_6163482922453580015[25] = 1;
   out_6163482922453580015[26] = 0;
   out_6163482922453580015[27] = 0;
   out_6163482922453580015[28] = 0;
   out_6163482922453580015[29] = 0;
   out_6163482922453580015[30] = 0;
   out_6163482922453580015[31] = 0;
   out_6163482922453580015[32] = 0;
   out_6163482922453580015[33] = 0;
   out_6163482922453580015[34] = 0;
   out_6163482922453580015[35] = 0;
   out_6163482922453580015[36] = 0;
   out_6163482922453580015[37] = 0;
   out_6163482922453580015[38] = 0;
   out_6163482922453580015[39] = 0;
   out_6163482922453580015[40] = 0;
   out_6163482922453580015[41] = 0;
   out_6163482922453580015[42] = 0;
   out_6163482922453580015[43] = 0;
   out_6163482922453580015[44] = 1;
   out_6163482922453580015[45] = 0;
   out_6163482922453580015[46] = 0;
   out_6163482922453580015[47] = 0;
   out_6163482922453580015[48] = 0;
   out_6163482922453580015[49] = 0;
   out_6163482922453580015[50] = 0;
   out_6163482922453580015[51] = 0;
   out_6163482922453580015[52] = 0;
   out_6163482922453580015[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8619877196673941904) {
  err_fun(nom_x, delta_x, out_8619877196673941904);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5079236499620164768) {
  inv_err_fun(nom_x, true_x, out_5079236499620164768);
}
void pose_H_mod_fun(double *state, double *out_3834855492212920326) {
  H_mod_fun(state, out_3834855492212920326);
}
void pose_f_fun(double *state, double dt, double *out_271549942577683268) {
  f_fun(state,  dt, out_271549942577683268);
}
void pose_F_fun(double *state, double dt, double *out_8758390952692881982) {
  F_fun(state,  dt, out_8758390952692881982);
}
void pose_h_4(double *state, double *unused, double *out_4085392694727598368) {
  h_4(state, unused, out_4085392694727598368);
}
void pose_H_4(double *state, double *unused, double *out_3080694490158207719) {
  H_4(state, unused, out_3080694490158207719);
}
void pose_h_10(double *state, double *unused, double *out_8653843584460147373) {
  h_10(state, unused, out_8653843584460147373);
}
void pose_H_10(double *state, double *unused, double *out_1350506859556886668) {
  H_10(state, unused, out_1350506859556886668);
}
void pose_h_13(double *state, double *unused, double *out_6805598292797670581) {
  h_13(state, unused, out_6805598292797670581);
}
void pose_H_13(double *state, double *unused, double *out_4529936718158493210) {
  H_13(state, unused, out_4529936718158493210);
}
void pose_h_14(double *state, double *unused, double *out_7201729596421949005) {
  h_14(state, unused, out_7201729596421949005);
}
void pose_H_14(double *state, double *unused, double *out_6163482922453580015) {
  H_14(state, unused, out_6163482922453580015);
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
