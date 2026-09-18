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
void err_fun(double *nom_x, double *delta_x, double *out_1521868972628687519) {
   out_1521868972628687519[0] = delta_x[0] + nom_x[0];
   out_1521868972628687519[1] = delta_x[1] + nom_x[1];
   out_1521868972628687519[2] = delta_x[2] + nom_x[2];
   out_1521868972628687519[3] = delta_x[3] + nom_x[3];
   out_1521868972628687519[4] = delta_x[4] + nom_x[4];
   out_1521868972628687519[5] = delta_x[5] + nom_x[5];
   out_1521868972628687519[6] = delta_x[6] + nom_x[6];
   out_1521868972628687519[7] = delta_x[7] + nom_x[7];
   out_1521868972628687519[8] = delta_x[8] + nom_x[8];
   out_1521868972628687519[9] = delta_x[9] + nom_x[9];
   out_1521868972628687519[10] = delta_x[10] + nom_x[10];
   out_1521868972628687519[11] = delta_x[11] + nom_x[11];
   out_1521868972628687519[12] = delta_x[12] + nom_x[12];
   out_1521868972628687519[13] = delta_x[13] + nom_x[13];
   out_1521868972628687519[14] = delta_x[14] + nom_x[14];
   out_1521868972628687519[15] = delta_x[15] + nom_x[15];
   out_1521868972628687519[16] = delta_x[16] + nom_x[16];
   out_1521868972628687519[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5973741488758985839) {
   out_5973741488758985839[0] = -nom_x[0] + true_x[0];
   out_5973741488758985839[1] = -nom_x[1] + true_x[1];
   out_5973741488758985839[2] = -nom_x[2] + true_x[2];
   out_5973741488758985839[3] = -nom_x[3] + true_x[3];
   out_5973741488758985839[4] = -nom_x[4] + true_x[4];
   out_5973741488758985839[5] = -nom_x[5] + true_x[5];
   out_5973741488758985839[6] = -nom_x[6] + true_x[6];
   out_5973741488758985839[7] = -nom_x[7] + true_x[7];
   out_5973741488758985839[8] = -nom_x[8] + true_x[8];
   out_5973741488758985839[9] = -nom_x[9] + true_x[9];
   out_5973741488758985839[10] = -nom_x[10] + true_x[10];
   out_5973741488758985839[11] = -nom_x[11] + true_x[11];
   out_5973741488758985839[12] = -nom_x[12] + true_x[12];
   out_5973741488758985839[13] = -nom_x[13] + true_x[13];
   out_5973741488758985839[14] = -nom_x[14] + true_x[14];
   out_5973741488758985839[15] = -nom_x[15] + true_x[15];
   out_5973741488758985839[16] = -nom_x[16] + true_x[16];
   out_5973741488758985839[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3570248239535224383) {
   out_3570248239535224383[0] = 1.0;
   out_3570248239535224383[1] = 0.0;
   out_3570248239535224383[2] = 0.0;
   out_3570248239535224383[3] = 0.0;
   out_3570248239535224383[4] = 0.0;
   out_3570248239535224383[5] = 0.0;
   out_3570248239535224383[6] = 0.0;
   out_3570248239535224383[7] = 0.0;
   out_3570248239535224383[8] = 0.0;
   out_3570248239535224383[9] = 0.0;
   out_3570248239535224383[10] = 0.0;
   out_3570248239535224383[11] = 0.0;
   out_3570248239535224383[12] = 0.0;
   out_3570248239535224383[13] = 0.0;
   out_3570248239535224383[14] = 0.0;
   out_3570248239535224383[15] = 0.0;
   out_3570248239535224383[16] = 0.0;
   out_3570248239535224383[17] = 0.0;
   out_3570248239535224383[18] = 0.0;
   out_3570248239535224383[19] = 1.0;
   out_3570248239535224383[20] = 0.0;
   out_3570248239535224383[21] = 0.0;
   out_3570248239535224383[22] = 0.0;
   out_3570248239535224383[23] = 0.0;
   out_3570248239535224383[24] = 0.0;
   out_3570248239535224383[25] = 0.0;
   out_3570248239535224383[26] = 0.0;
   out_3570248239535224383[27] = 0.0;
   out_3570248239535224383[28] = 0.0;
   out_3570248239535224383[29] = 0.0;
   out_3570248239535224383[30] = 0.0;
   out_3570248239535224383[31] = 0.0;
   out_3570248239535224383[32] = 0.0;
   out_3570248239535224383[33] = 0.0;
   out_3570248239535224383[34] = 0.0;
   out_3570248239535224383[35] = 0.0;
   out_3570248239535224383[36] = 0.0;
   out_3570248239535224383[37] = 0.0;
   out_3570248239535224383[38] = 1.0;
   out_3570248239535224383[39] = 0.0;
   out_3570248239535224383[40] = 0.0;
   out_3570248239535224383[41] = 0.0;
   out_3570248239535224383[42] = 0.0;
   out_3570248239535224383[43] = 0.0;
   out_3570248239535224383[44] = 0.0;
   out_3570248239535224383[45] = 0.0;
   out_3570248239535224383[46] = 0.0;
   out_3570248239535224383[47] = 0.0;
   out_3570248239535224383[48] = 0.0;
   out_3570248239535224383[49] = 0.0;
   out_3570248239535224383[50] = 0.0;
   out_3570248239535224383[51] = 0.0;
   out_3570248239535224383[52] = 0.0;
   out_3570248239535224383[53] = 0.0;
   out_3570248239535224383[54] = 0.0;
   out_3570248239535224383[55] = 0.0;
   out_3570248239535224383[56] = 0.0;
   out_3570248239535224383[57] = 1.0;
   out_3570248239535224383[58] = 0.0;
   out_3570248239535224383[59] = 0.0;
   out_3570248239535224383[60] = 0.0;
   out_3570248239535224383[61] = 0.0;
   out_3570248239535224383[62] = 0.0;
   out_3570248239535224383[63] = 0.0;
   out_3570248239535224383[64] = 0.0;
   out_3570248239535224383[65] = 0.0;
   out_3570248239535224383[66] = 0.0;
   out_3570248239535224383[67] = 0.0;
   out_3570248239535224383[68] = 0.0;
   out_3570248239535224383[69] = 0.0;
   out_3570248239535224383[70] = 0.0;
   out_3570248239535224383[71] = 0.0;
   out_3570248239535224383[72] = 0.0;
   out_3570248239535224383[73] = 0.0;
   out_3570248239535224383[74] = 0.0;
   out_3570248239535224383[75] = 0.0;
   out_3570248239535224383[76] = 1.0;
   out_3570248239535224383[77] = 0.0;
   out_3570248239535224383[78] = 0.0;
   out_3570248239535224383[79] = 0.0;
   out_3570248239535224383[80] = 0.0;
   out_3570248239535224383[81] = 0.0;
   out_3570248239535224383[82] = 0.0;
   out_3570248239535224383[83] = 0.0;
   out_3570248239535224383[84] = 0.0;
   out_3570248239535224383[85] = 0.0;
   out_3570248239535224383[86] = 0.0;
   out_3570248239535224383[87] = 0.0;
   out_3570248239535224383[88] = 0.0;
   out_3570248239535224383[89] = 0.0;
   out_3570248239535224383[90] = 0.0;
   out_3570248239535224383[91] = 0.0;
   out_3570248239535224383[92] = 0.0;
   out_3570248239535224383[93] = 0.0;
   out_3570248239535224383[94] = 0.0;
   out_3570248239535224383[95] = 1.0;
   out_3570248239535224383[96] = 0.0;
   out_3570248239535224383[97] = 0.0;
   out_3570248239535224383[98] = 0.0;
   out_3570248239535224383[99] = 0.0;
   out_3570248239535224383[100] = 0.0;
   out_3570248239535224383[101] = 0.0;
   out_3570248239535224383[102] = 0.0;
   out_3570248239535224383[103] = 0.0;
   out_3570248239535224383[104] = 0.0;
   out_3570248239535224383[105] = 0.0;
   out_3570248239535224383[106] = 0.0;
   out_3570248239535224383[107] = 0.0;
   out_3570248239535224383[108] = 0.0;
   out_3570248239535224383[109] = 0.0;
   out_3570248239535224383[110] = 0.0;
   out_3570248239535224383[111] = 0.0;
   out_3570248239535224383[112] = 0.0;
   out_3570248239535224383[113] = 0.0;
   out_3570248239535224383[114] = 1.0;
   out_3570248239535224383[115] = 0.0;
   out_3570248239535224383[116] = 0.0;
   out_3570248239535224383[117] = 0.0;
   out_3570248239535224383[118] = 0.0;
   out_3570248239535224383[119] = 0.0;
   out_3570248239535224383[120] = 0.0;
   out_3570248239535224383[121] = 0.0;
   out_3570248239535224383[122] = 0.0;
   out_3570248239535224383[123] = 0.0;
   out_3570248239535224383[124] = 0.0;
   out_3570248239535224383[125] = 0.0;
   out_3570248239535224383[126] = 0.0;
   out_3570248239535224383[127] = 0.0;
   out_3570248239535224383[128] = 0.0;
   out_3570248239535224383[129] = 0.0;
   out_3570248239535224383[130] = 0.0;
   out_3570248239535224383[131] = 0.0;
   out_3570248239535224383[132] = 0.0;
   out_3570248239535224383[133] = 1.0;
   out_3570248239535224383[134] = 0.0;
   out_3570248239535224383[135] = 0.0;
   out_3570248239535224383[136] = 0.0;
   out_3570248239535224383[137] = 0.0;
   out_3570248239535224383[138] = 0.0;
   out_3570248239535224383[139] = 0.0;
   out_3570248239535224383[140] = 0.0;
   out_3570248239535224383[141] = 0.0;
   out_3570248239535224383[142] = 0.0;
   out_3570248239535224383[143] = 0.0;
   out_3570248239535224383[144] = 0.0;
   out_3570248239535224383[145] = 0.0;
   out_3570248239535224383[146] = 0.0;
   out_3570248239535224383[147] = 0.0;
   out_3570248239535224383[148] = 0.0;
   out_3570248239535224383[149] = 0.0;
   out_3570248239535224383[150] = 0.0;
   out_3570248239535224383[151] = 0.0;
   out_3570248239535224383[152] = 1.0;
   out_3570248239535224383[153] = 0.0;
   out_3570248239535224383[154] = 0.0;
   out_3570248239535224383[155] = 0.0;
   out_3570248239535224383[156] = 0.0;
   out_3570248239535224383[157] = 0.0;
   out_3570248239535224383[158] = 0.0;
   out_3570248239535224383[159] = 0.0;
   out_3570248239535224383[160] = 0.0;
   out_3570248239535224383[161] = 0.0;
   out_3570248239535224383[162] = 0.0;
   out_3570248239535224383[163] = 0.0;
   out_3570248239535224383[164] = 0.0;
   out_3570248239535224383[165] = 0.0;
   out_3570248239535224383[166] = 0.0;
   out_3570248239535224383[167] = 0.0;
   out_3570248239535224383[168] = 0.0;
   out_3570248239535224383[169] = 0.0;
   out_3570248239535224383[170] = 0.0;
   out_3570248239535224383[171] = 1.0;
   out_3570248239535224383[172] = 0.0;
   out_3570248239535224383[173] = 0.0;
   out_3570248239535224383[174] = 0.0;
   out_3570248239535224383[175] = 0.0;
   out_3570248239535224383[176] = 0.0;
   out_3570248239535224383[177] = 0.0;
   out_3570248239535224383[178] = 0.0;
   out_3570248239535224383[179] = 0.0;
   out_3570248239535224383[180] = 0.0;
   out_3570248239535224383[181] = 0.0;
   out_3570248239535224383[182] = 0.0;
   out_3570248239535224383[183] = 0.0;
   out_3570248239535224383[184] = 0.0;
   out_3570248239535224383[185] = 0.0;
   out_3570248239535224383[186] = 0.0;
   out_3570248239535224383[187] = 0.0;
   out_3570248239535224383[188] = 0.0;
   out_3570248239535224383[189] = 0.0;
   out_3570248239535224383[190] = 1.0;
   out_3570248239535224383[191] = 0.0;
   out_3570248239535224383[192] = 0.0;
   out_3570248239535224383[193] = 0.0;
   out_3570248239535224383[194] = 0.0;
   out_3570248239535224383[195] = 0.0;
   out_3570248239535224383[196] = 0.0;
   out_3570248239535224383[197] = 0.0;
   out_3570248239535224383[198] = 0.0;
   out_3570248239535224383[199] = 0.0;
   out_3570248239535224383[200] = 0.0;
   out_3570248239535224383[201] = 0.0;
   out_3570248239535224383[202] = 0.0;
   out_3570248239535224383[203] = 0.0;
   out_3570248239535224383[204] = 0.0;
   out_3570248239535224383[205] = 0.0;
   out_3570248239535224383[206] = 0.0;
   out_3570248239535224383[207] = 0.0;
   out_3570248239535224383[208] = 0.0;
   out_3570248239535224383[209] = 1.0;
   out_3570248239535224383[210] = 0.0;
   out_3570248239535224383[211] = 0.0;
   out_3570248239535224383[212] = 0.0;
   out_3570248239535224383[213] = 0.0;
   out_3570248239535224383[214] = 0.0;
   out_3570248239535224383[215] = 0.0;
   out_3570248239535224383[216] = 0.0;
   out_3570248239535224383[217] = 0.0;
   out_3570248239535224383[218] = 0.0;
   out_3570248239535224383[219] = 0.0;
   out_3570248239535224383[220] = 0.0;
   out_3570248239535224383[221] = 0.0;
   out_3570248239535224383[222] = 0.0;
   out_3570248239535224383[223] = 0.0;
   out_3570248239535224383[224] = 0.0;
   out_3570248239535224383[225] = 0.0;
   out_3570248239535224383[226] = 0.0;
   out_3570248239535224383[227] = 0.0;
   out_3570248239535224383[228] = 1.0;
   out_3570248239535224383[229] = 0.0;
   out_3570248239535224383[230] = 0.0;
   out_3570248239535224383[231] = 0.0;
   out_3570248239535224383[232] = 0.0;
   out_3570248239535224383[233] = 0.0;
   out_3570248239535224383[234] = 0.0;
   out_3570248239535224383[235] = 0.0;
   out_3570248239535224383[236] = 0.0;
   out_3570248239535224383[237] = 0.0;
   out_3570248239535224383[238] = 0.0;
   out_3570248239535224383[239] = 0.0;
   out_3570248239535224383[240] = 0.0;
   out_3570248239535224383[241] = 0.0;
   out_3570248239535224383[242] = 0.0;
   out_3570248239535224383[243] = 0.0;
   out_3570248239535224383[244] = 0.0;
   out_3570248239535224383[245] = 0.0;
   out_3570248239535224383[246] = 0.0;
   out_3570248239535224383[247] = 1.0;
   out_3570248239535224383[248] = 0.0;
   out_3570248239535224383[249] = 0.0;
   out_3570248239535224383[250] = 0.0;
   out_3570248239535224383[251] = 0.0;
   out_3570248239535224383[252] = 0.0;
   out_3570248239535224383[253] = 0.0;
   out_3570248239535224383[254] = 0.0;
   out_3570248239535224383[255] = 0.0;
   out_3570248239535224383[256] = 0.0;
   out_3570248239535224383[257] = 0.0;
   out_3570248239535224383[258] = 0.0;
   out_3570248239535224383[259] = 0.0;
   out_3570248239535224383[260] = 0.0;
   out_3570248239535224383[261] = 0.0;
   out_3570248239535224383[262] = 0.0;
   out_3570248239535224383[263] = 0.0;
   out_3570248239535224383[264] = 0.0;
   out_3570248239535224383[265] = 0.0;
   out_3570248239535224383[266] = 1.0;
   out_3570248239535224383[267] = 0.0;
   out_3570248239535224383[268] = 0.0;
   out_3570248239535224383[269] = 0.0;
   out_3570248239535224383[270] = 0.0;
   out_3570248239535224383[271] = 0.0;
   out_3570248239535224383[272] = 0.0;
   out_3570248239535224383[273] = 0.0;
   out_3570248239535224383[274] = 0.0;
   out_3570248239535224383[275] = 0.0;
   out_3570248239535224383[276] = 0.0;
   out_3570248239535224383[277] = 0.0;
   out_3570248239535224383[278] = 0.0;
   out_3570248239535224383[279] = 0.0;
   out_3570248239535224383[280] = 0.0;
   out_3570248239535224383[281] = 0.0;
   out_3570248239535224383[282] = 0.0;
   out_3570248239535224383[283] = 0.0;
   out_3570248239535224383[284] = 0.0;
   out_3570248239535224383[285] = 1.0;
   out_3570248239535224383[286] = 0.0;
   out_3570248239535224383[287] = 0.0;
   out_3570248239535224383[288] = 0.0;
   out_3570248239535224383[289] = 0.0;
   out_3570248239535224383[290] = 0.0;
   out_3570248239535224383[291] = 0.0;
   out_3570248239535224383[292] = 0.0;
   out_3570248239535224383[293] = 0.0;
   out_3570248239535224383[294] = 0.0;
   out_3570248239535224383[295] = 0.0;
   out_3570248239535224383[296] = 0.0;
   out_3570248239535224383[297] = 0.0;
   out_3570248239535224383[298] = 0.0;
   out_3570248239535224383[299] = 0.0;
   out_3570248239535224383[300] = 0.0;
   out_3570248239535224383[301] = 0.0;
   out_3570248239535224383[302] = 0.0;
   out_3570248239535224383[303] = 0.0;
   out_3570248239535224383[304] = 1.0;
   out_3570248239535224383[305] = 0.0;
   out_3570248239535224383[306] = 0.0;
   out_3570248239535224383[307] = 0.0;
   out_3570248239535224383[308] = 0.0;
   out_3570248239535224383[309] = 0.0;
   out_3570248239535224383[310] = 0.0;
   out_3570248239535224383[311] = 0.0;
   out_3570248239535224383[312] = 0.0;
   out_3570248239535224383[313] = 0.0;
   out_3570248239535224383[314] = 0.0;
   out_3570248239535224383[315] = 0.0;
   out_3570248239535224383[316] = 0.0;
   out_3570248239535224383[317] = 0.0;
   out_3570248239535224383[318] = 0.0;
   out_3570248239535224383[319] = 0.0;
   out_3570248239535224383[320] = 0.0;
   out_3570248239535224383[321] = 0.0;
   out_3570248239535224383[322] = 0.0;
   out_3570248239535224383[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4424152333430403489) {
   out_4424152333430403489[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4424152333430403489[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4424152333430403489[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4424152333430403489[3] = dt*state[12] + state[3];
   out_4424152333430403489[4] = dt*state[13] + state[4];
   out_4424152333430403489[5] = dt*state[14] + state[5];
   out_4424152333430403489[6] = state[6];
   out_4424152333430403489[7] = state[7];
   out_4424152333430403489[8] = state[8];
   out_4424152333430403489[9] = state[9];
   out_4424152333430403489[10] = state[10];
   out_4424152333430403489[11] = state[11];
   out_4424152333430403489[12] = state[12];
   out_4424152333430403489[13] = state[13];
   out_4424152333430403489[14] = state[14];
   out_4424152333430403489[15] = state[15];
   out_4424152333430403489[16] = state[16];
   out_4424152333430403489[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6803176853977790057) {
   out_6803176853977790057[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6803176853977790057[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6803176853977790057[2] = 0;
   out_6803176853977790057[3] = 0;
   out_6803176853977790057[4] = 0;
   out_6803176853977790057[5] = 0;
   out_6803176853977790057[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6803176853977790057[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6803176853977790057[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6803176853977790057[9] = 0;
   out_6803176853977790057[10] = 0;
   out_6803176853977790057[11] = 0;
   out_6803176853977790057[12] = 0;
   out_6803176853977790057[13] = 0;
   out_6803176853977790057[14] = 0;
   out_6803176853977790057[15] = 0;
   out_6803176853977790057[16] = 0;
   out_6803176853977790057[17] = 0;
   out_6803176853977790057[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6803176853977790057[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6803176853977790057[20] = 0;
   out_6803176853977790057[21] = 0;
   out_6803176853977790057[22] = 0;
   out_6803176853977790057[23] = 0;
   out_6803176853977790057[24] = 0;
   out_6803176853977790057[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6803176853977790057[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6803176853977790057[27] = 0;
   out_6803176853977790057[28] = 0;
   out_6803176853977790057[29] = 0;
   out_6803176853977790057[30] = 0;
   out_6803176853977790057[31] = 0;
   out_6803176853977790057[32] = 0;
   out_6803176853977790057[33] = 0;
   out_6803176853977790057[34] = 0;
   out_6803176853977790057[35] = 0;
   out_6803176853977790057[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6803176853977790057[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6803176853977790057[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6803176853977790057[39] = 0;
   out_6803176853977790057[40] = 0;
   out_6803176853977790057[41] = 0;
   out_6803176853977790057[42] = 0;
   out_6803176853977790057[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6803176853977790057[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6803176853977790057[45] = 0;
   out_6803176853977790057[46] = 0;
   out_6803176853977790057[47] = 0;
   out_6803176853977790057[48] = 0;
   out_6803176853977790057[49] = 0;
   out_6803176853977790057[50] = 0;
   out_6803176853977790057[51] = 0;
   out_6803176853977790057[52] = 0;
   out_6803176853977790057[53] = 0;
   out_6803176853977790057[54] = 0;
   out_6803176853977790057[55] = 0;
   out_6803176853977790057[56] = 0;
   out_6803176853977790057[57] = 1;
   out_6803176853977790057[58] = 0;
   out_6803176853977790057[59] = 0;
   out_6803176853977790057[60] = 0;
   out_6803176853977790057[61] = 0;
   out_6803176853977790057[62] = 0;
   out_6803176853977790057[63] = 0;
   out_6803176853977790057[64] = 0;
   out_6803176853977790057[65] = 0;
   out_6803176853977790057[66] = dt;
   out_6803176853977790057[67] = 0;
   out_6803176853977790057[68] = 0;
   out_6803176853977790057[69] = 0;
   out_6803176853977790057[70] = 0;
   out_6803176853977790057[71] = 0;
   out_6803176853977790057[72] = 0;
   out_6803176853977790057[73] = 0;
   out_6803176853977790057[74] = 0;
   out_6803176853977790057[75] = 0;
   out_6803176853977790057[76] = 1;
   out_6803176853977790057[77] = 0;
   out_6803176853977790057[78] = 0;
   out_6803176853977790057[79] = 0;
   out_6803176853977790057[80] = 0;
   out_6803176853977790057[81] = 0;
   out_6803176853977790057[82] = 0;
   out_6803176853977790057[83] = 0;
   out_6803176853977790057[84] = 0;
   out_6803176853977790057[85] = dt;
   out_6803176853977790057[86] = 0;
   out_6803176853977790057[87] = 0;
   out_6803176853977790057[88] = 0;
   out_6803176853977790057[89] = 0;
   out_6803176853977790057[90] = 0;
   out_6803176853977790057[91] = 0;
   out_6803176853977790057[92] = 0;
   out_6803176853977790057[93] = 0;
   out_6803176853977790057[94] = 0;
   out_6803176853977790057[95] = 1;
   out_6803176853977790057[96] = 0;
   out_6803176853977790057[97] = 0;
   out_6803176853977790057[98] = 0;
   out_6803176853977790057[99] = 0;
   out_6803176853977790057[100] = 0;
   out_6803176853977790057[101] = 0;
   out_6803176853977790057[102] = 0;
   out_6803176853977790057[103] = 0;
   out_6803176853977790057[104] = dt;
   out_6803176853977790057[105] = 0;
   out_6803176853977790057[106] = 0;
   out_6803176853977790057[107] = 0;
   out_6803176853977790057[108] = 0;
   out_6803176853977790057[109] = 0;
   out_6803176853977790057[110] = 0;
   out_6803176853977790057[111] = 0;
   out_6803176853977790057[112] = 0;
   out_6803176853977790057[113] = 0;
   out_6803176853977790057[114] = 1;
   out_6803176853977790057[115] = 0;
   out_6803176853977790057[116] = 0;
   out_6803176853977790057[117] = 0;
   out_6803176853977790057[118] = 0;
   out_6803176853977790057[119] = 0;
   out_6803176853977790057[120] = 0;
   out_6803176853977790057[121] = 0;
   out_6803176853977790057[122] = 0;
   out_6803176853977790057[123] = 0;
   out_6803176853977790057[124] = 0;
   out_6803176853977790057[125] = 0;
   out_6803176853977790057[126] = 0;
   out_6803176853977790057[127] = 0;
   out_6803176853977790057[128] = 0;
   out_6803176853977790057[129] = 0;
   out_6803176853977790057[130] = 0;
   out_6803176853977790057[131] = 0;
   out_6803176853977790057[132] = 0;
   out_6803176853977790057[133] = 1;
   out_6803176853977790057[134] = 0;
   out_6803176853977790057[135] = 0;
   out_6803176853977790057[136] = 0;
   out_6803176853977790057[137] = 0;
   out_6803176853977790057[138] = 0;
   out_6803176853977790057[139] = 0;
   out_6803176853977790057[140] = 0;
   out_6803176853977790057[141] = 0;
   out_6803176853977790057[142] = 0;
   out_6803176853977790057[143] = 0;
   out_6803176853977790057[144] = 0;
   out_6803176853977790057[145] = 0;
   out_6803176853977790057[146] = 0;
   out_6803176853977790057[147] = 0;
   out_6803176853977790057[148] = 0;
   out_6803176853977790057[149] = 0;
   out_6803176853977790057[150] = 0;
   out_6803176853977790057[151] = 0;
   out_6803176853977790057[152] = 1;
   out_6803176853977790057[153] = 0;
   out_6803176853977790057[154] = 0;
   out_6803176853977790057[155] = 0;
   out_6803176853977790057[156] = 0;
   out_6803176853977790057[157] = 0;
   out_6803176853977790057[158] = 0;
   out_6803176853977790057[159] = 0;
   out_6803176853977790057[160] = 0;
   out_6803176853977790057[161] = 0;
   out_6803176853977790057[162] = 0;
   out_6803176853977790057[163] = 0;
   out_6803176853977790057[164] = 0;
   out_6803176853977790057[165] = 0;
   out_6803176853977790057[166] = 0;
   out_6803176853977790057[167] = 0;
   out_6803176853977790057[168] = 0;
   out_6803176853977790057[169] = 0;
   out_6803176853977790057[170] = 0;
   out_6803176853977790057[171] = 1;
   out_6803176853977790057[172] = 0;
   out_6803176853977790057[173] = 0;
   out_6803176853977790057[174] = 0;
   out_6803176853977790057[175] = 0;
   out_6803176853977790057[176] = 0;
   out_6803176853977790057[177] = 0;
   out_6803176853977790057[178] = 0;
   out_6803176853977790057[179] = 0;
   out_6803176853977790057[180] = 0;
   out_6803176853977790057[181] = 0;
   out_6803176853977790057[182] = 0;
   out_6803176853977790057[183] = 0;
   out_6803176853977790057[184] = 0;
   out_6803176853977790057[185] = 0;
   out_6803176853977790057[186] = 0;
   out_6803176853977790057[187] = 0;
   out_6803176853977790057[188] = 0;
   out_6803176853977790057[189] = 0;
   out_6803176853977790057[190] = 1;
   out_6803176853977790057[191] = 0;
   out_6803176853977790057[192] = 0;
   out_6803176853977790057[193] = 0;
   out_6803176853977790057[194] = 0;
   out_6803176853977790057[195] = 0;
   out_6803176853977790057[196] = 0;
   out_6803176853977790057[197] = 0;
   out_6803176853977790057[198] = 0;
   out_6803176853977790057[199] = 0;
   out_6803176853977790057[200] = 0;
   out_6803176853977790057[201] = 0;
   out_6803176853977790057[202] = 0;
   out_6803176853977790057[203] = 0;
   out_6803176853977790057[204] = 0;
   out_6803176853977790057[205] = 0;
   out_6803176853977790057[206] = 0;
   out_6803176853977790057[207] = 0;
   out_6803176853977790057[208] = 0;
   out_6803176853977790057[209] = 1;
   out_6803176853977790057[210] = 0;
   out_6803176853977790057[211] = 0;
   out_6803176853977790057[212] = 0;
   out_6803176853977790057[213] = 0;
   out_6803176853977790057[214] = 0;
   out_6803176853977790057[215] = 0;
   out_6803176853977790057[216] = 0;
   out_6803176853977790057[217] = 0;
   out_6803176853977790057[218] = 0;
   out_6803176853977790057[219] = 0;
   out_6803176853977790057[220] = 0;
   out_6803176853977790057[221] = 0;
   out_6803176853977790057[222] = 0;
   out_6803176853977790057[223] = 0;
   out_6803176853977790057[224] = 0;
   out_6803176853977790057[225] = 0;
   out_6803176853977790057[226] = 0;
   out_6803176853977790057[227] = 0;
   out_6803176853977790057[228] = 1;
   out_6803176853977790057[229] = 0;
   out_6803176853977790057[230] = 0;
   out_6803176853977790057[231] = 0;
   out_6803176853977790057[232] = 0;
   out_6803176853977790057[233] = 0;
   out_6803176853977790057[234] = 0;
   out_6803176853977790057[235] = 0;
   out_6803176853977790057[236] = 0;
   out_6803176853977790057[237] = 0;
   out_6803176853977790057[238] = 0;
   out_6803176853977790057[239] = 0;
   out_6803176853977790057[240] = 0;
   out_6803176853977790057[241] = 0;
   out_6803176853977790057[242] = 0;
   out_6803176853977790057[243] = 0;
   out_6803176853977790057[244] = 0;
   out_6803176853977790057[245] = 0;
   out_6803176853977790057[246] = 0;
   out_6803176853977790057[247] = 1;
   out_6803176853977790057[248] = 0;
   out_6803176853977790057[249] = 0;
   out_6803176853977790057[250] = 0;
   out_6803176853977790057[251] = 0;
   out_6803176853977790057[252] = 0;
   out_6803176853977790057[253] = 0;
   out_6803176853977790057[254] = 0;
   out_6803176853977790057[255] = 0;
   out_6803176853977790057[256] = 0;
   out_6803176853977790057[257] = 0;
   out_6803176853977790057[258] = 0;
   out_6803176853977790057[259] = 0;
   out_6803176853977790057[260] = 0;
   out_6803176853977790057[261] = 0;
   out_6803176853977790057[262] = 0;
   out_6803176853977790057[263] = 0;
   out_6803176853977790057[264] = 0;
   out_6803176853977790057[265] = 0;
   out_6803176853977790057[266] = 1;
   out_6803176853977790057[267] = 0;
   out_6803176853977790057[268] = 0;
   out_6803176853977790057[269] = 0;
   out_6803176853977790057[270] = 0;
   out_6803176853977790057[271] = 0;
   out_6803176853977790057[272] = 0;
   out_6803176853977790057[273] = 0;
   out_6803176853977790057[274] = 0;
   out_6803176853977790057[275] = 0;
   out_6803176853977790057[276] = 0;
   out_6803176853977790057[277] = 0;
   out_6803176853977790057[278] = 0;
   out_6803176853977790057[279] = 0;
   out_6803176853977790057[280] = 0;
   out_6803176853977790057[281] = 0;
   out_6803176853977790057[282] = 0;
   out_6803176853977790057[283] = 0;
   out_6803176853977790057[284] = 0;
   out_6803176853977790057[285] = 1;
   out_6803176853977790057[286] = 0;
   out_6803176853977790057[287] = 0;
   out_6803176853977790057[288] = 0;
   out_6803176853977790057[289] = 0;
   out_6803176853977790057[290] = 0;
   out_6803176853977790057[291] = 0;
   out_6803176853977790057[292] = 0;
   out_6803176853977790057[293] = 0;
   out_6803176853977790057[294] = 0;
   out_6803176853977790057[295] = 0;
   out_6803176853977790057[296] = 0;
   out_6803176853977790057[297] = 0;
   out_6803176853977790057[298] = 0;
   out_6803176853977790057[299] = 0;
   out_6803176853977790057[300] = 0;
   out_6803176853977790057[301] = 0;
   out_6803176853977790057[302] = 0;
   out_6803176853977790057[303] = 0;
   out_6803176853977790057[304] = 1;
   out_6803176853977790057[305] = 0;
   out_6803176853977790057[306] = 0;
   out_6803176853977790057[307] = 0;
   out_6803176853977790057[308] = 0;
   out_6803176853977790057[309] = 0;
   out_6803176853977790057[310] = 0;
   out_6803176853977790057[311] = 0;
   out_6803176853977790057[312] = 0;
   out_6803176853977790057[313] = 0;
   out_6803176853977790057[314] = 0;
   out_6803176853977790057[315] = 0;
   out_6803176853977790057[316] = 0;
   out_6803176853977790057[317] = 0;
   out_6803176853977790057[318] = 0;
   out_6803176853977790057[319] = 0;
   out_6803176853977790057[320] = 0;
   out_6803176853977790057[321] = 0;
   out_6803176853977790057[322] = 0;
   out_6803176853977790057[323] = 1;
}
void h_4(double *state, double *unused, double *out_3836272604617207310) {
   out_3836272604617207310[0] = state[6] + state[9];
   out_3836272604617207310[1] = state[7] + state[10];
   out_3836272604617207310[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8086112231463728530) {
   out_8086112231463728530[0] = 0;
   out_8086112231463728530[1] = 0;
   out_8086112231463728530[2] = 0;
   out_8086112231463728530[3] = 0;
   out_8086112231463728530[4] = 0;
   out_8086112231463728530[5] = 0;
   out_8086112231463728530[6] = 1;
   out_8086112231463728530[7] = 0;
   out_8086112231463728530[8] = 0;
   out_8086112231463728530[9] = 1;
   out_8086112231463728530[10] = 0;
   out_8086112231463728530[11] = 0;
   out_8086112231463728530[12] = 0;
   out_8086112231463728530[13] = 0;
   out_8086112231463728530[14] = 0;
   out_8086112231463728530[15] = 0;
   out_8086112231463728530[16] = 0;
   out_8086112231463728530[17] = 0;
   out_8086112231463728530[18] = 0;
   out_8086112231463728530[19] = 0;
   out_8086112231463728530[20] = 0;
   out_8086112231463728530[21] = 0;
   out_8086112231463728530[22] = 0;
   out_8086112231463728530[23] = 0;
   out_8086112231463728530[24] = 0;
   out_8086112231463728530[25] = 1;
   out_8086112231463728530[26] = 0;
   out_8086112231463728530[27] = 0;
   out_8086112231463728530[28] = 1;
   out_8086112231463728530[29] = 0;
   out_8086112231463728530[30] = 0;
   out_8086112231463728530[31] = 0;
   out_8086112231463728530[32] = 0;
   out_8086112231463728530[33] = 0;
   out_8086112231463728530[34] = 0;
   out_8086112231463728530[35] = 0;
   out_8086112231463728530[36] = 0;
   out_8086112231463728530[37] = 0;
   out_8086112231463728530[38] = 0;
   out_8086112231463728530[39] = 0;
   out_8086112231463728530[40] = 0;
   out_8086112231463728530[41] = 0;
   out_8086112231463728530[42] = 0;
   out_8086112231463728530[43] = 0;
   out_8086112231463728530[44] = 1;
   out_8086112231463728530[45] = 0;
   out_8086112231463728530[46] = 0;
   out_8086112231463728530[47] = 1;
   out_8086112231463728530[48] = 0;
   out_8086112231463728530[49] = 0;
   out_8086112231463728530[50] = 0;
   out_8086112231463728530[51] = 0;
   out_8086112231463728530[52] = 0;
   out_8086112231463728530[53] = 0;
}
void h_10(double *state, double *unused, double *out_5399605113307306233) {
   out_5399605113307306233[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5399605113307306233[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5399605113307306233[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7292319071417432326) {
   out_7292319071417432326[0] = 0;
   out_7292319071417432326[1] = 9.8100000000000005*cos(state[1]);
   out_7292319071417432326[2] = 0;
   out_7292319071417432326[3] = 0;
   out_7292319071417432326[4] = -state[8];
   out_7292319071417432326[5] = state[7];
   out_7292319071417432326[6] = 0;
   out_7292319071417432326[7] = state[5];
   out_7292319071417432326[8] = -state[4];
   out_7292319071417432326[9] = 0;
   out_7292319071417432326[10] = 0;
   out_7292319071417432326[11] = 0;
   out_7292319071417432326[12] = 1;
   out_7292319071417432326[13] = 0;
   out_7292319071417432326[14] = 0;
   out_7292319071417432326[15] = 1;
   out_7292319071417432326[16] = 0;
   out_7292319071417432326[17] = 0;
   out_7292319071417432326[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7292319071417432326[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7292319071417432326[20] = 0;
   out_7292319071417432326[21] = state[8];
   out_7292319071417432326[22] = 0;
   out_7292319071417432326[23] = -state[6];
   out_7292319071417432326[24] = -state[5];
   out_7292319071417432326[25] = 0;
   out_7292319071417432326[26] = state[3];
   out_7292319071417432326[27] = 0;
   out_7292319071417432326[28] = 0;
   out_7292319071417432326[29] = 0;
   out_7292319071417432326[30] = 0;
   out_7292319071417432326[31] = 1;
   out_7292319071417432326[32] = 0;
   out_7292319071417432326[33] = 0;
   out_7292319071417432326[34] = 1;
   out_7292319071417432326[35] = 0;
   out_7292319071417432326[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7292319071417432326[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7292319071417432326[38] = 0;
   out_7292319071417432326[39] = -state[7];
   out_7292319071417432326[40] = state[6];
   out_7292319071417432326[41] = 0;
   out_7292319071417432326[42] = state[4];
   out_7292319071417432326[43] = -state[3];
   out_7292319071417432326[44] = 0;
   out_7292319071417432326[45] = 0;
   out_7292319071417432326[46] = 0;
   out_7292319071417432326[47] = 0;
   out_7292319071417432326[48] = 0;
   out_7292319071417432326[49] = 0;
   out_7292319071417432326[50] = 1;
   out_7292319071417432326[51] = 0;
   out_7292319071417432326[52] = 0;
   out_7292319071417432326[53] = 1;
}
void h_13(double *state, double *unused, double *out_7661639451849470604) {
   out_7661639451849470604[0] = state[3];
   out_7661639451849470604[1] = state[4];
   out_7661639451849470604[2] = state[5];
}
void H_13(double *state, double *unused, double *out_475481023147027601) {
   out_475481023147027601[0] = 0;
   out_475481023147027601[1] = 0;
   out_475481023147027601[2] = 0;
   out_475481023147027601[3] = 1;
   out_475481023147027601[4] = 0;
   out_475481023147027601[5] = 0;
   out_475481023147027601[6] = 0;
   out_475481023147027601[7] = 0;
   out_475481023147027601[8] = 0;
   out_475481023147027601[9] = 0;
   out_475481023147027601[10] = 0;
   out_475481023147027601[11] = 0;
   out_475481023147027601[12] = 0;
   out_475481023147027601[13] = 0;
   out_475481023147027601[14] = 0;
   out_475481023147027601[15] = 0;
   out_475481023147027601[16] = 0;
   out_475481023147027601[17] = 0;
   out_475481023147027601[18] = 0;
   out_475481023147027601[19] = 0;
   out_475481023147027601[20] = 0;
   out_475481023147027601[21] = 0;
   out_475481023147027601[22] = 1;
   out_475481023147027601[23] = 0;
   out_475481023147027601[24] = 0;
   out_475481023147027601[25] = 0;
   out_475481023147027601[26] = 0;
   out_475481023147027601[27] = 0;
   out_475481023147027601[28] = 0;
   out_475481023147027601[29] = 0;
   out_475481023147027601[30] = 0;
   out_475481023147027601[31] = 0;
   out_475481023147027601[32] = 0;
   out_475481023147027601[33] = 0;
   out_475481023147027601[34] = 0;
   out_475481023147027601[35] = 0;
   out_475481023147027601[36] = 0;
   out_475481023147027601[37] = 0;
   out_475481023147027601[38] = 0;
   out_475481023147027601[39] = 0;
   out_475481023147027601[40] = 0;
   out_475481023147027601[41] = 1;
   out_475481023147027601[42] = 0;
   out_475481023147027601[43] = 0;
   out_475481023147027601[44] = 0;
   out_475481023147027601[45] = 0;
   out_475481023147027601[46] = 0;
   out_475481023147027601[47] = 0;
   out_475481023147027601[48] = 0;
   out_475481023147027601[49] = 0;
   out_475481023147027601[50] = 0;
   out_475481023147027601[51] = 0;
   out_475481023147027601[52] = 0;
   out_475481023147027601[53] = 0;
}
void h_14(double *state, double *unused, double *out_8890668722298524322) {
   out_8890668722298524322[0] = state[6];
   out_8890668722298524322[1] = state[7];
   out_8890668722298524322[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4122871375124244001) {
   out_4122871375124244001[0] = 0;
   out_4122871375124244001[1] = 0;
   out_4122871375124244001[2] = 0;
   out_4122871375124244001[3] = 0;
   out_4122871375124244001[4] = 0;
   out_4122871375124244001[5] = 0;
   out_4122871375124244001[6] = 1;
   out_4122871375124244001[7] = 0;
   out_4122871375124244001[8] = 0;
   out_4122871375124244001[9] = 0;
   out_4122871375124244001[10] = 0;
   out_4122871375124244001[11] = 0;
   out_4122871375124244001[12] = 0;
   out_4122871375124244001[13] = 0;
   out_4122871375124244001[14] = 0;
   out_4122871375124244001[15] = 0;
   out_4122871375124244001[16] = 0;
   out_4122871375124244001[17] = 0;
   out_4122871375124244001[18] = 0;
   out_4122871375124244001[19] = 0;
   out_4122871375124244001[20] = 0;
   out_4122871375124244001[21] = 0;
   out_4122871375124244001[22] = 0;
   out_4122871375124244001[23] = 0;
   out_4122871375124244001[24] = 0;
   out_4122871375124244001[25] = 1;
   out_4122871375124244001[26] = 0;
   out_4122871375124244001[27] = 0;
   out_4122871375124244001[28] = 0;
   out_4122871375124244001[29] = 0;
   out_4122871375124244001[30] = 0;
   out_4122871375124244001[31] = 0;
   out_4122871375124244001[32] = 0;
   out_4122871375124244001[33] = 0;
   out_4122871375124244001[34] = 0;
   out_4122871375124244001[35] = 0;
   out_4122871375124244001[36] = 0;
   out_4122871375124244001[37] = 0;
   out_4122871375124244001[38] = 0;
   out_4122871375124244001[39] = 0;
   out_4122871375124244001[40] = 0;
   out_4122871375124244001[41] = 0;
   out_4122871375124244001[42] = 0;
   out_4122871375124244001[43] = 0;
   out_4122871375124244001[44] = 1;
   out_4122871375124244001[45] = 0;
   out_4122871375124244001[46] = 0;
   out_4122871375124244001[47] = 0;
   out_4122871375124244001[48] = 0;
   out_4122871375124244001[49] = 0;
   out_4122871375124244001[50] = 0;
   out_4122871375124244001[51] = 0;
   out_4122871375124244001[52] = 0;
   out_4122871375124244001[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1521868972628687519) {
  err_fun(nom_x, delta_x, out_1521868972628687519);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5973741488758985839) {
  inv_err_fun(nom_x, true_x, out_5973741488758985839);
}
void pose_H_mod_fun(double *state, double *out_3570248239535224383) {
  H_mod_fun(state, out_3570248239535224383);
}
void pose_f_fun(double *state, double dt, double *out_4424152333430403489) {
  f_fun(state,  dt, out_4424152333430403489);
}
void pose_F_fun(double *state, double dt, double *out_6803176853977790057) {
  F_fun(state,  dt, out_6803176853977790057);
}
void pose_h_4(double *state, double *unused, double *out_3836272604617207310) {
  h_4(state, unused, out_3836272604617207310);
}
void pose_H_4(double *state, double *unused, double *out_8086112231463728530) {
  H_4(state, unused, out_8086112231463728530);
}
void pose_h_10(double *state, double *unused, double *out_5399605113307306233) {
  h_10(state, unused, out_5399605113307306233);
}
void pose_H_10(double *state, double *unused, double *out_7292319071417432326) {
  H_10(state, unused, out_7292319071417432326);
}
void pose_h_13(double *state, double *unused, double *out_7661639451849470604) {
  h_13(state, unused, out_7661639451849470604);
}
void pose_H_13(double *state, double *unused, double *out_475481023147027601) {
  H_13(state, unused, out_475481023147027601);
}
void pose_h_14(double *state, double *unused, double *out_8890668722298524322) {
  h_14(state, unused, out_8890668722298524322);
}
void pose_H_14(double *state, double *unused, double *out_4122871375124244001) {
  H_14(state, unused, out_4122871375124244001);
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
