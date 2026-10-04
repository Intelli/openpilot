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
void err_fun(double *nom_x, double *delta_x, double *out_5764489290281003311) {
   out_5764489290281003311[0] = delta_x[0] + nom_x[0];
   out_5764489290281003311[1] = delta_x[1] + nom_x[1];
   out_5764489290281003311[2] = delta_x[2] + nom_x[2];
   out_5764489290281003311[3] = delta_x[3] + nom_x[3];
   out_5764489290281003311[4] = delta_x[4] + nom_x[4];
   out_5764489290281003311[5] = delta_x[5] + nom_x[5];
   out_5764489290281003311[6] = delta_x[6] + nom_x[6];
   out_5764489290281003311[7] = delta_x[7] + nom_x[7];
   out_5764489290281003311[8] = delta_x[8] + nom_x[8];
   out_5764489290281003311[9] = delta_x[9] + nom_x[9];
   out_5764489290281003311[10] = delta_x[10] + nom_x[10];
   out_5764489290281003311[11] = delta_x[11] + nom_x[11];
   out_5764489290281003311[12] = delta_x[12] + nom_x[12];
   out_5764489290281003311[13] = delta_x[13] + nom_x[13];
   out_5764489290281003311[14] = delta_x[14] + nom_x[14];
   out_5764489290281003311[15] = delta_x[15] + nom_x[15];
   out_5764489290281003311[16] = delta_x[16] + nom_x[16];
   out_5764489290281003311[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1112330292461843791) {
   out_1112330292461843791[0] = -nom_x[0] + true_x[0];
   out_1112330292461843791[1] = -nom_x[1] + true_x[1];
   out_1112330292461843791[2] = -nom_x[2] + true_x[2];
   out_1112330292461843791[3] = -nom_x[3] + true_x[3];
   out_1112330292461843791[4] = -nom_x[4] + true_x[4];
   out_1112330292461843791[5] = -nom_x[5] + true_x[5];
   out_1112330292461843791[6] = -nom_x[6] + true_x[6];
   out_1112330292461843791[7] = -nom_x[7] + true_x[7];
   out_1112330292461843791[8] = -nom_x[8] + true_x[8];
   out_1112330292461843791[9] = -nom_x[9] + true_x[9];
   out_1112330292461843791[10] = -nom_x[10] + true_x[10];
   out_1112330292461843791[11] = -nom_x[11] + true_x[11];
   out_1112330292461843791[12] = -nom_x[12] + true_x[12];
   out_1112330292461843791[13] = -nom_x[13] + true_x[13];
   out_1112330292461843791[14] = -nom_x[14] + true_x[14];
   out_1112330292461843791[15] = -nom_x[15] + true_x[15];
   out_1112330292461843791[16] = -nom_x[16] + true_x[16];
   out_1112330292461843791[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1113689545321808981) {
   out_1113689545321808981[0] = 1.0;
   out_1113689545321808981[1] = 0.0;
   out_1113689545321808981[2] = 0.0;
   out_1113689545321808981[3] = 0.0;
   out_1113689545321808981[4] = 0.0;
   out_1113689545321808981[5] = 0.0;
   out_1113689545321808981[6] = 0.0;
   out_1113689545321808981[7] = 0.0;
   out_1113689545321808981[8] = 0.0;
   out_1113689545321808981[9] = 0.0;
   out_1113689545321808981[10] = 0.0;
   out_1113689545321808981[11] = 0.0;
   out_1113689545321808981[12] = 0.0;
   out_1113689545321808981[13] = 0.0;
   out_1113689545321808981[14] = 0.0;
   out_1113689545321808981[15] = 0.0;
   out_1113689545321808981[16] = 0.0;
   out_1113689545321808981[17] = 0.0;
   out_1113689545321808981[18] = 0.0;
   out_1113689545321808981[19] = 1.0;
   out_1113689545321808981[20] = 0.0;
   out_1113689545321808981[21] = 0.0;
   out_1113689545321808981[22] = 0.0;
   out_1113689545321808981[23] = 0.0;
   out_1113689545321808981[24] = 0.0;
   out_1113689545321808981[25] = 0.0;
   out_1113689545321808981[26] = 0.0;
   out_1113689545321808981[27] = 0.0;
   out_1113689545321808981[28] = 0.0;
   out_1113689545321808981[29] = 0.0;
   out_1113689545321808981[30] = 0.0;
   out_1113689545321808981[31] = 0.0;
   out_1113689545321808981[32] = 0.0;
   out_1113689545321808981[33] = 0.0;
   out_1113689545321808981[34] = 0.0;
   out_1113689545321808981[35] = 0.0;
   out_1113689545321808981[36] = 0.0;
   out_1113689545321808981[37] = 0.0;
   out_1113689545321808981[38] = 1.0;
   out_1113689545321808981[39] = 0.0;
   out_1113689545321808981[40] = 0.0;
   out_1113689545321808981[41] = 0.0;
   out_1113689545321808981[42] = 0.0;
   out_1113689545321808981[43] = 0.0;
   out_1113689545321808981[44] = 0.0;
   out_1113689545321808981[45] = 0.0;
   out_1113689545321808981[46] = 0.0;
   out_1113689545321808981[47] = 0.0;
   out_1113689545321808981[48] = 0.0;
   out_1113689545321808981[49] = 0.0;
   out_1113689545321808981[50] = 0.0;
   out_1113689545321808981[51] = 0.0;
   out_1113689545321808981[52] = 0.0;
   out_1113689545321808981[53] = 0.0;
   out_1113689545321808981[54] = 0.0;
   out_1113689545321808981[55] = 0.0;
   out_1113689545321808981[56] = 0.0;
   out_1113689545321808981[57] = 1.0;
   out_1113689545321808981[58] = 0.0;
   out_1113689545321808981[59] = 0.0;
   out_1113689545321808981[60] = 0.0;
   out_1113689545321808981[61] = 0.0;
   out_1113689545321808981[62] = 0.0;
   out_1113689545321808981[63] = 0.0;
   out_1113689545321808981[64] = 0.0;
   out_1113689545321808981[65] = 0.0;
   out_1113689545321808981[66] = 0.0;
   out_1113689545321808981[67] = 0.0;
   out_1113689545321808981[68] = 0.0;
   out_1113689545321808981[69] = 0.0;
   out_1113689545321808981[70] = 0.0;
   out_1113689545321808981[71] = 0.0;
   out_1113689545321808981[72] = 0.0;
   out_1113689545321808981[73] = 0.0;
   out_1113689545321808981[74] = 0.0;
   out_1113689545321808981[75] = 0.0;
   out_1113689545321808981[76] = 1.0;
   out_1113689545321808981[77] = 0.0;
   out_1113689545321808981[78] = 0.0;
   out_1113689545321808981[79] = 0.0;
   out_1113689545321808981[80] = 0.0;
   out_1113689545321808981[81] = 0.0;
   out_1113689545321808981[82] = 0.0;
   out_1113689545321808981[83] = 0.0;
   out_1113689545321808981[84] = 0.0;
   out_1113689545321808981[85] = 0.0;
   out_1113689545321808981[86] = 0.0;
   out_1113689545321808981[87] = 0.0;
   out_1113689545321808981[88] = 0.0;
   out_1113689545321808981[89] = 0.0;
   out_1113689545321808981[90] = 0.0;
   out_1113689545321808981[91] = 0.0;
   out_1113689545321808981[92] = 0.0;
   out_1113689545321808981[93] = 0.0;
   out_1113689545321808981[94] = 0.0;
   out_1113689545321808981[95] = 1.0;
   out_1113689545321808981[96] = 0.0;
   out_1113689545321808981[97] = 0.0;
   out_1113689545321808981[98] = 0.0;
   out_1113689545321808981[99] = 0.0;
   out_1113689545321808981[100] = 0.0;
   out_1113689545321808981[101] = 0.0;
   out_1113689545321808981[102] = 0.0;
   out_1113689545321808981[103] = 0.0;
   out_1113689545321808981[104] = 0.0;
   out_1113689545321808981[105] = 0.0;
   out_1113689545321808981[106] = 0.0;
   out_1113689545321808981[107] = 0.0;
   out_1113689545321808981[108] = 0.0;
   out_1113689545321808981[109] = 0.0;
   out_1113689545321808981[110] = 0.0;
   out_1113689545321808981[111] = 0.0;
   out_1113689545321808981[112] = 0.0;
   out_1113689545321808981[113] = 0.0;
   out_1113689545321808981[114] = 1.0;
   out_1113689545321808981[115] = 0.0;
   out_1113689545321808981[116] = 0.0;
   out_1113689545321808981[117] = 0.0;
   out_1113689545321808981[118] = 0.0;
   out_1113689545321808981[119] = 0.0;
   out_1113689545321808981[120] = 0.0;
   out_1113689545321808981[121] = 0.0;
   out_1113689545321808981[122] = 0.0;
   out_1113689545321808981[123] = 0.0;
   out_1113689545321808981[124] = 0.0;
   out_1113689545321808981[125] = 0.0;
   out_1113689545321808981[126] = 0.0;
   out_1113689545321808981[127] = 0.0;
   out_1113689545321808981[128] = 0.0;
   out_1113689545321808981[129] = 0.0;
   out_1113689545321808981[130] = 0.0;
   out_1113689545321808981[131] = 0.0;
   out_1113689545321808981[132] = 0.0;
   out_1113689545321808981[133] = 1.0;
   out_1113689545321808981[134] = 0.0;
   out_1113689545321808981[135] = 0.0;
   out_1113689545321808981[136] = 0.0;
   out_1113689545321808981[137] = 0.0;
   out_1113689545321808981[138] = 0.0;
   out_1113689545321808981[139] = 0.0;
   out_1113689545321808981[140] = 0.0;
   out_1113689545321808981[141] = 0.0;
   out_1113689545321808981[142] = 0.0;
   out_1113689545321808981[143] = 0.0;
   out_1113689545321808981[144] = 0.0;
   out_1113689545321808981[145] = 0.0;
   out_1113689545321808981[146] = 0.0;
   out_1113689545321808981[147] = 0.0;
   out_1113689545321808981[148] = 0.0;
   out_1113689545321808981[149] = 0.0;
   out_1113689545321808981[150] = 0.0;
   out_1113689545321808981[151] = 0.0;
   out_1113689545321808981[152] = 1.0;
   out_1113689545321808981[153] = 0.0;
   out_1113689545321808981[154] = 0.0;
   out_1113689545321808981[155] = 0.0;
   out_1113689545321808981[156] = 0.0;
   out_1113689545321808981[157] = 0.0;
   out_1113689545321808981[158] = 0.0;
   out_1113689545321808981[159] = 0.0;
   out_1113689545321808981[160] = 0.0;
   out_1113689545321808981[161] = 0.0;
   out_1113689545321808981[162] = 0.0;
   out_1113689545321808981[163] = 0.0;
   out_1113689545321808981[164] = 0.0;
   out_1113689545321808981[165] = 0.0;
   out_1113689545321808981[166] = 0.0;
   out_1113689545321808981[167] = 0.0;
   out_1113689545321808981[168] = 0.0;
   out_1113689545321808981[169] = 0.0;
   out_1113689545321808981[170] = 0.0;
   out_1113689545321808981[171] = 1.0;
   out_1113689545321808981[172] = 0.0;
   out_1113689545321808981[173] = 0.0;
   out_1113689545321808981[174] = 0.0;
   out_1113689545321808981[175] = 0.0;
   out_1113689545321808981[176] = 0.0;
   out_1113689545321808981[177] = 0.0;
   out_1113689545321808981[178] = 0.0;
   out_1113689545321808981[179] = 0.0;
   out_1113689545321808981[180] = 0.0;
   out_1113689545321808981[181] = 0.0;
   out_1113689545321808981[182] = 0.0;
   out_1113689545321808981[183] = 0.0;
   out_1113689545321808981[184] = 0.0;
   out_1113689545321808981[185] = 0.0;
   out_1113689545321808981[186] = 0.0;
   out_1113689545321808981[187] = 0.0;
   out_1113689545321808981[188] = 0.0;
   out_1113689545321808981[189] = 0.0;
   out_1113689545321808981[190] = 1.0;
   out_1113689545321808981[191] = 0.0;
   out_1113689545321808981[192] = 0.0;
   out_1113689545321808981[193] = 0.0;
   out_1113689545321808981[194] = 0.0;
   out_1113689545321808981[195] = 0.0;
   out_1113689545321808981[196] = 0.0;
   out_1113689545321808981[197] = 0.0;
   out_1113689545321808981[198] = 0.0;
   out_1113689545321808981[199] = 0.0;
   out_1113689545321808981[200] = 0.0;
   out_1113689545321808981[201] = 0.0;
   out_1113689545321808981[202] = 0.0;
   out_1113689545321808981[203] = 0.0;
   out_1113689545321808981[204] = 0.0;
   out_1113689545321808981[205] = 0.0;
   out_1113689545321808981[206] = 0.0;
   out_1113689545321808981[207] = 0.0;
   out_1113689545321808981[208] = 0.0;
   out_1113689545321808981[209] = 1.0;
   out_1113689545321808981[210] = 0.0;
   out_1113689545321808981[211] = 0.0;
   out_1113689545321808981[212] = 0.0;
   out_1113689545321808981[213] = 0.0;
   out_1113689545321808981[214] = 0.0;
   out_1113689545321808981[215] = 0.0;
   out_1113689545321808981[216] = 0.0;
   out_1113689545321808981[217] = 0.0;
   out_1113689545321808981[218] = 0.0;
   out_1113689545321808981[219] = 0.0;
   out_1113689545321808981[220] = 0.0;
   out_1113689545321808981[221] = 0.0;
   out_1113689545321808981[222] = 0.0;
   out_1113689545321808981[223] = 0.0;
   out_1113689545321808981[224] = 0.0;
   out_1113689545321808981[225] = 0.0;
   out_1113689545321808981[226] = 0.0;
   out_1113689545321808981[227] = 0.0;
   out_1113689545321808981[228] = 1.0;
   out_1113689545321808981[229] = 0.0;
   out_1113689545321808981[230] = 0.0;
   out_1113689545321808981[231] = 0.0;
   out_1113689545321808981[232] = 0.0;
   out_1113689545321808981[233] = 0.0;
   out_1113689545321808981[234] = 0.0;
   out_1113689545321808981[235] = 0.0;
   out_1113689545321808981[236] = 0.0;
   out_1113689545321808981[237] = 0.0;
   out_1113689545321808981[238] = 0.0;
   out_1113689545321808981[239] = 0.0;
   out_1113689545321808981[240] = 0.0;
   out_1113689545321808981[241] = 0.0;
   out_1113689545321808981[242] = 0.0;
   out_1113689545321808981[243] = 0.0;
   out_1113689545321808981[244] = 0.0;
   out_1113689545321808981[245] = 0.0;
   out_1113689545321808981[246] = 0.0;
   out_1113689545321808981[247] = 1.0;
   out_1113689545321808981[248] = 0.0;
   out_1113689545321808981[249] = 0.0;
   out_1113689545321808981[250] = 0.0;
   out_1113689545321808981[251] = 0.0;
   out_1113689545321808981[252] = 0.0;
   out_1113689545321808981[253] = 0.0;
   out_1113689545321808981[254] = 0.0;
   out_1113689545321808981[255] = 0.0;
   out_1113689545321808981[256] = 0.0;
   out_1113689545321808981[257] = 0.0;
   out_1113689545321808981[258] = 0.0;
   out_1113689545321808981[259] = 0.0;
   out_1113689545321808981[260] = 0.0;
   out_1113689545321808981[261] = 0.0;
   out_1113689545321808981[262] = 0.0;
   out_1113689545321808981[263] = 0.0;
   out_1113689545321808981[264] = 0.0;
   out_1113689545321808981[265] = 0.0;
   out_1113689545321808981[266] = 1.0;
   out_1113689545321808981[267] = 0.0;
   out_1113689545321808981[268] = 0.0;
   out_1113689545321808981[269] = 0.0;
   out_1113689545321808981[270] = 0.0;
   out_1113689545321808981[271] = 0.0;
   out_1113689545321808981[272] = 0.0;
   out_1113689545321808981[273] = 0.0;
   out_1113689545321808981[274] = 0.0;
   out_1113689545321808981[275] = 0.0;
   out_1113689545321808981[276] = 0.0;
   out_1113689545321808981[277] = 0.0;
   out_1113689545321808981[278] = 0.0;
   out_1113689545321808981[279] = 0.0;
   out_1113689545321808981[280] = 0.0;
   out_1113689545321808981[281] = 0.0;
   out_1113689545321808981[282] = 0.0;
   out_1113689545321808981[283] = 0.0;
   out_1113689545321808981[284] = 0.0;
   out_1113689545321808981[285] = 1.0;
   out_1113689545321808981[286] = 0.0;
   out_1113689545321808981[287] = 0.0;
   out_1113689545321808981[288] = 0.0;
   out_1113689545321808981[289] = 0.0;
   out_1113689545321808981[290] = 0.0;
   out_1113689545321808981[291] = 0.0;
   out_1113689545321808981[292] = 0.0;
   out_1113689545321808981[293] = 0.0;
   out_1113689545321808981[294] = 0.0;
   out_1113689545321808981[295] = 0.0;
   out_1113689545321808981[296] = 0.0;
   out_1113689545321808981[297] = 0.0;
   out_1113689545321808981[298] = 0.0;
   out_1113689545321808981[299] = 0.0;
   out_1113689545321808981[300] = 0.0;
   out_1113689545321808981[301] = 0.0;
   out_1113689545321808981[302] = 0.0;
   out_1113689545321808981[303] = 0.0;
   out_1113689545321808981[304] = 1.0;
   out_1113689545321808981[305] = 0.0;
   out_1113689545321808981[306] = 0.0;
   out_1113689545321808981[307] = 0.0;
   out_1113689545321808981[308] = 0.0;
   out_1113689545321808981[309] = 0.0;
   out_1113689545321808981[310] = 0.0;
   out_1113689545321808981[311] = 0.0;
   out_1113689545321808981[312] = 0.0;
   out_1113689545321808981[313] = 0.0;
   out_1113689545321808981[314] = 0.0;
   out_1113689545321808981[315] = 0.0;
   out_1113689545321808981[316] = 0.0;
   out_1113689545321808981[317] = 0.0;
   out_1113689545321808981[318] = 0.0;
   out_1113689545321808981[319] = 0.0;
   out_1113689545321808981[320] = 0.0;
   out_1113689545321808981[321] = 0.0;
   out_1113689545321808981[322] = 0.0;
   out_1113689545321808981[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6623631471554753598) {
   out_6623631471554753598[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6623631471554753598[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6623631471554753598[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6623631471554753598[3] = dt*state[12] + state[3];
   out_6623631471554753598[4] = dt*state[13] + state[4];
   out_6623631471554753598[5] = dt*state[14] + state[5];
   out_6623631471554753598[6] = state[6];
   out_6623631471554753598[7] = state[7];
   out_6623631471554753598[8] = state[8];
   out_6623631471554753598[9] = state[9];
   out_6623631471554753598[10] = state[10];
   out_6623631471554753598[11] = state[11];
   out_6623631471554753598[12] = state[12];
   out_6623631471554753598[13] = state[13];
   out_6623631471554753598[14] = state[14];
   out_6623631471554753598[15] = state[15];
   out_6623631471554753598[16] = state[16];
   out_6623631471554753598[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4351986266867303872) {
   out_4351986266867303872[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4351986266867303872[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4351986266867303872[2] = 0;
   out_4351986266867303872[3] = 0;
   out_4351986266867303872[4] = 0;
   out_4351986266867303872[5] = 0;
   out_4351986266867303872[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4351986266867303872[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4351986266867303872[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4351986266867303872[9] = 0;
   out_4351986266867303872[10] = 0;
   out_4351986266867303872[11] = 0;
   out_4351986266867303872[12] = 0;
   out_4351986266867303872[13] = 0;
   out_4351986266867303872[14] = 0;
   out_4351986266867303872[15] = 0;
   out_4351986266867303872[16] = 0;
   out_4351986266867303872[17] = 0;
   out_4351986266867303872[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4351986266867303872[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4351986266867303872[20] = 0;
   out_4351986266867303872[21] = 0;
   out_4351986266867303872[22] = 0;
   out_4351986266867303872[23] = 0;
   out_4351986266867303872[24] = 0;
   out_4351986266867303872[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4351986266867303872[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4351986266867303872[27] = 0;
   out_4351986266867303872[28] = 0;
   out_4351986266867303872[29] = 0;
   out_4351986266867303872[30] = 0;
   out_4351986266867303872[31] = 0;
   out_4351986266867303872[32] = 0;
   out_4351986266867303872[33] = 0;
   out_4351986266867303872[34] = 0;
   out_4351986266867303872[35] = 0;
   out_4351986266867303872[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4351986266867303872[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4351986266867303872[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4351986266867303872[39] = 0;
   out_4351986266867303872[40] = 0;
   out_4351986266867303872[41] = 0;
   out_4351986266867303872[42] = 0;
   out_4351986266867303872[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4351986266867303872[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4351986266867303872[45] = 0;
   out_4351986266867303872[46] = 0;
   out_4351986266867303872[47] = 0;
   out_4351986266867303872[48] = 0;
   out_4351986266867303872[49] = 0;
   out_4351986266867303872[50] = 0;
   out_4351986266867303872[51] = 0;
   out_4351986266867303872[52] = 0;
   out_4351986266867303872[53] = 0;
   out_4351986266867303872[54] = 0;
   out_4351986266867303872[55] = 0;
   out_4351986266867303872[56] = 0;
   out_4351986266867303872[57] = 1;
   out_4351986266867303872[58] = 0;
   out_4351986266867303872[59] = 0;
   out_4351986266867303872[60] = 0;
   out_4351986266867303872[61] = 0;
   out_4351986266867303872[62] = 0;
   out_4351986266867303872[63] = 0;
   out_4351986266867303872[64] = 0;
   out_4351986266867303872[65] = 0;
   out_4351986266867303872[66] = dt;
   out_4351986266867303872[67] = 0;
   out_4351986266867303872[68] = 0;
   out_4351986266867303872[69] = 0;
   out_4351986266867303872[70] = 0;
   out_4351986266867303872[71] = 0;
   out_4351986266867303872[72] = 0;
   out_4351986266867303872[73] = 0;
   out_4351986266867303872[74] = 0;
   out_4351986266867303872[75] = 0;
   out_4351986266867303872[76] = 1;
   out_4351986266867303872[77] = 0;
   out_4351986266867303872[78] = 0;
   out_4351986266867303872[79] = 0;
   out_4351986266867303872[80] = 0;
   out_4351986266867303872[81] = 0;
   out_4351986266867303872[82] = 0;
   out_4351986266867303872[83] = 0;
   out_4351986266867303872[84] = 0;
   out_4351986266867303872[85] = dt;
   out_4351986266867303872[86] = 0;
   out_4351986266867303872[87] = 0;
   out_4351986266867303872[88] = 0;
   out_4351986266867303872[89] = 0;
   out_4351986266867303872[90] = 0;
   out_4351986266867303872[91] = 0;
   out_4351986266867303872[92] = 0;
   out_4351986266867303872[93] = 0;
   out_4351986266867303872[94] = 0;
   out_4351986266867303872[95] = 1;
   out_4351986266867303872[96] = 0;
   out_4351986266867303872[97] = 0;
   out_4351986266867303872[98] = 0;
   out_4351986266867303872[99] = 0;
   out_4351986266867303872[100] = 0;
   out_4351986266867303872[101] = 0;
   out_4351986266867303872[102] = 0;
   out_4351986266867303872[103] = 0;
   out_4351986266867303872[104] = dt;
   out_4351986266867303872[105] = 0;
   out_4351986266867303872[106] = 0;
   out_4351986266867303872[107] = 0;
   out_4351986266867303872[108] = 0;
   out_4351986266867303872[109] = 0;
   out_4351986266867303872[110] = 0;
   out_4351986266867303872[111] = 0;
   out_4351986266867303872[112] = 0;
   out_4351986266867303872[113] = 0;
   out_4351986266867303872[114] = 1;
   out_4351986266867303872[115] = 0;
   out_4351986266867303872[116] = 0;
   out_4351986266867303872[117] = 0;
   out_4351986266867303872[118] = 0;
   out_4351986266867303872[119] = 0;
   out_4351986266867303872[120] = 0;
   out_4351986266867303872[121] = 0;
   out_4351986266867303872[122] = 0;
   out_4351986266867303872[123] = 0;
   out_4351986266867303872[124] = 0;
   out_4351986266867303872[125] = 0;
   out_4351986266867303872[126] = 0;
   out_4351986266867303872[127] = 0;
   out_4351986266867303872[128] = 0;
   out_4351986266867303872[129] = 0;
   out_4351986266867303872[130] = 0;
   out_4351986266867303872[131] = 0;
   out_4351986266867303872[132] = 0;
   out_4351986266867303872[133] = 1;
   out_4351986266867303872[134] = 0;
   out_4351986266867303872[135] = 0;
   out_4351986266867303872[136] = 0;
   out_4351986266867303872[137] = 0;
   out_4351986266867303872[138] = 0;
   out_4351986266867303872[139] = 0;
   out_4351986266867303872[140] = 0;
   out_4351986266867303872[141] = 0;
   out_4351986266867303872[142] = 0;
   out_4351986266867303872[143] = 0;
   out_4351986266867303872[144] = 0;
   out_4351986266867303872[145] = 0;
   out_4351986266867303872[146] = 0;
   out_4351986266867303872[147] = 0;
   out_4351986266867303872[148] = 0;
   out_4351986266867303872[149] = 0;
   out_4351986266867303872[150] = 0;
   out_4351986266867303872[151] = 0;
   out_4351986266867303872[152] = 1;
   out_4351986266867303872[153] = 0;
   out_4351986266867303872[154] = 0;
   out_4351986266867303872[155] = 0;
   out_4351986266867303872[156] = 0;
   out_4351986266867303872[157] = 0;
   out_4351986266867303872[158] = 0;
   out_4351986266867303872[159] = 0;
   out_4351986266867303872[160] = 0;
   out_4351986266867303872[161] = 0;
   out_4351986266867303872[162] = 0;
   out_4351986266867303872[163] = 0;
   out_4351986266867303872[164] = 0;
   out_4351986266867303872[165] = 0;
   out_4351986266867303872[166] = 0;
   out_4351986266867303872[167] = 0;
   out_4351986266867303872[168] = 0;
   out_4351986266867303872[169] = 0;
   out_4351986266867303872[170] = 0;
   out_4351986266867303872[171] = 1;
   out_4351986266867303872[172] = 0;
   out_4351986266867303872[173] = 0;
   out_4351986266867303872[174] = 0;
   out_4351986266867303872[175] = 0;
   out_4351986266867303872[176] = 0;
   out_4351986266867303872[177] = 0;
   out_4351986266867303872[178] = 0;
   out_4351986266867303872[179] = 0;
   out_4351986266867303872[180] = 0;
   out_4351986266867303872[181] = 0;
   out_4351986266867303872[182] = 0;
   out_4351986266867303872[183] = 0;
   out_4351986266867303872[184] = 0;
   out_4351986266867303872[185] = 0;
   out_4351986266867303872[186] = 0;
   out_4351986266867303872[187] = 0;
   out_4351986266867303872[188] = 0;
   out_4351986266867303872[189] = 0;
   out_4351986266867303872[190] = 1;
   out_4351986266867303872[191] = 0;
   out_4351986266867303872[192] = 0;
   out_4351986266867303872[193] = 0;
   out_4351986266867303872[194] = 0;
   out_4351986266867303872[195] = 0;
   out_4351986266867303872[196] = 0;
   out_4351986266867303872[197] = 0;
   out_4351986266867303872[198] = 0;
   out_4351986266867303872[199] = 0;
   out_4351986266867303872[200] = 0;
   out_4351986266867303872[201] = 0;
   out_4351986266867303872[202] = 0;
   out_4351986266867303872[203] = 0;
   out_4351986266867303872[204] = 0;
   out_4351986266867303872[205] = 0;
   out_4351986266867303872[206] = 0;
   out_4351986266867303872[207] = 0;
   out_4351986266867303872[208] = 0;
   out_4351986266867303872[209] = 1;
   out_4351986266867303872[210] = 0;
   out_4351986266867303872[211] = 0;
   out_4351986266867303872[212] = 0;
   out_4351986266867303872[213] = 0;
   out_4351986266867303872[214] = 0;
   out_4351986266867303872[215] = 0;
   out_4351986266867303872[216] = 0;
   out_4351986266867303872[217] = 0;
   out_4351986266867303872[218] = 0;
   out_4351986266867303872[219] = 0;
   out_4351986266867303872[220] = 0;
   out_4351986266867303872[221] = 0;
   out_4351986266867303872[222] = 0;
   out_4351986266867303872[223] = 0;
   out_4351986266867303872[224] = 0;
   out_4351986266867303872[225] = 0;
   out_4351986266867303872[226] = 0;
   out_4351986266867303872[227] = 0;
   out_4351986266867303872[228] = 1;
   out_4351986266867303872[229] = 0;
   out_4351986266867303872[230] = 0;
   out_4351986266867303872[231] = 0;
   out_4351986266867303872[232] = 0;
   out_4351986266867303872[233] = 0;
   out_4351986266867303872[234] = 0;
   out_4351986266867303872[235] = 0;
   out_4351986266867303872[236] = 0;
   out_4351986266867303872[237] = 0;
   out_4351986266867303872[238] = 0;
   out_4351986266867303872[239] = 0;
   out_4351986266867303872[240] = 0;
   out_4351986266867303872[241] = 0;
   out_4351986266867303872[242] = 0;
   out_4351986266867303872[243] = 0;
   out_4351986266867303872[244] = 0;
   out_4351986266867303872[245] = 0;
   out_4351986266867303872[246] = 0;
   out_4351986266867303872[247] = 1;
   out_4351986266867303872[248] = 0;
   out_4351986266867303872[249] = 0;
   out_4351986266867303872[250] = 0;
   out_4351986266867303872[251] = 0;
   out_4351986266867303872[252] = 0;
   out_4351986266867303872[253] = 0;
   out_4351986266867303872[254] = 0;
   out_4351986266867303872[255] = 0;
   out_4351986266867303872[256] = 0;
   out_4351986266867303872[257] = 0;
   out_4351986266867303872[258] = 0;
   out_4351986266867303872[259] = 0;
   out_4351986266867303872[260] = 0;
   out_4351986266867303872[261] = 0;
   out_4351986266867303872[262] = 0;
   out_4351986266867303872[263] = 0;
   out_4351986266867303872[264] = 0;
   out_4351986266867303872[265] = 0;
   out_4351986266867303872[266] = 1;
   out_4351986266867303872[267] = 0;
   out_4351986266867303872[268] = 0;
   out_4351986266867303872[269] = 0;
   out_4351986266867303872[270] = 0;
   out_4351986266867303872[271] = 0;
   out_4351986266867303872[272] = 0;
   out_4351986266867303872[273] = 0;
   out_4351986266867303872[274] = 0;
   out_4351986266867303872[275] = 0;
   out_4351986266867303872[276] = 0;
   out_4351986266867303872[277] = 0;
   out_4351986266867303872[278] = 0;
   out_4351986266867303872[279] = 0;
   out_4351986266867303872[280] = 0;
   out_4351986266867303872[281] = 0;
   out_4351986266867303872[282] = 0;
   out_4351986266867303872[283] = 0;
   out_4351986266867303872[284] = 0;
   out_4351986266867303872[285] = 1;
   out_4351986266867303872[286] = 0;
   out_4351986266867303872[287] = 0;
   out_4351986266867303872[288] = 0;
   out_4351986266867303872[289] = 0;
   out_4351986266867303872[290] = 0;
   out_4351986266867303872[291] = 0;
   out_4351986266867303872[292] = 0;
   out_4351986266867303872[293] = 0;
   out_4351986266867303872[294] = 0;
   out_4351986266867303872[295] = 0;
   out_4351986266867303872[296] = 0;
   out_4351986266867303872[297] = 0;
   out_4351986266867303872[298] = 0;
   out_4351986266867303872[299] = 0;
   out_4351986266867303872[300] = 0;
   out_4351986266867303872[301] = 0;
   out_4351986266867303872[302] = 0;
   out_4351986266867303872[303] = 0;
   out_4351986266867303872[304] = 1;
   out_4351986266867303872[305] = 0;
   out_4351986266867303872[306] = 0;
   out_4351986266867303872[307] = 0;
   out_4351986266867303872[308] = 0;
   out_4351986266867303872[309] = 0;
   out_4351986266867303872[310] = 0;
   out_4351986266867303872[311] = 0;
   out_4351986266867303872[312] = 0;
   out_4351986266867303872[313] = 0;
   out_4351986266867303872[314] = 0;
   out_4351986266867303872[315] = 0;
   out_4351986266867303872[316] = 0;
   out_4351986266867303872[317] = 0;
   out_4351986266867303872[318] = 0;
   out_4351986266867303872[319] = 0;
   out_4351986266867303872[320] = 0;
   out_4351986266867303872[321] = 0;
   out_4351986266867303872[322] = 0;
   out_4351986266867303872[323] = 1;
}
void h_4(double *state, double *unused, double *out_6906405556919747882) {
   out_6906405556919747882[0] = state[6] + state[9];
   out_6906405556919747882[1] = state[7] + state[10];
   out_6906405556919747882[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_359528543267096374) {
   out_359528543267096374[0] = 0;
   out_359528543267096374[1] = 0;
   out_359528543267096374[2] = 0;
   out_359528543267096374[3] = 0;
   out_359528543267096374[4] = 0;
   out_359528543267096374[5] = 0;
   out_359528543267096374[6] = 1;
   out_359528543267096374[7] = 0;
   out_359528543267096374[8] = 0;
   out_359528543267096374[9] = 1;
   out_359528543267096374[10] = 0;
   out_359528543267096374[11] = 0;
   out_359528543267096374[12] = 0;
   out_359528543267096374[13] = 0;
   out_359528543267096374[14] = 0;
   out_359528543267096374[15] = 0;
   out_359528543267096374[16] = 0;
   out_359528543267096374[17] = 0;
   out_359528543267096374[18] = 0;
   out_359528543267096374[19] = 0;
   out_359528543267096374[20] = 0;
   out_359528543267096374[21] = 0;
   out_359528543267096374[22] = 0;
   out_359528543267096374[23] = 0;
   out_359528543267096374[24] = 0;
   out_359528543267096374[25] = 1;
   out_359528543267096374[26] = 0;
   out_359528543267096374[27] = 0;
   out_359528543267096374[28] = 1;
   out_359528543267096374[29] = 0;
   out_359528543267096374[30] = 0;
   out_359528543267096374[31] = 0;
   out_359528543267096374[32] = 0;
   out_359528543267096374[33] = 0;
   out_359528543267096374[34] = 0;
   out_359528543267096374[35] = 0;
   out_359528543267096374[36] = 0;
   out_359528543267096374[37] = 0;
   out_359528543267096374[38] = 0;
   out_359528543267096374[39] = 0;
   out_359528543267096374[40] = 0;
   out_359528543267096374[41] = 0;
   out_359528543267096374[42] = 0;
   out_359528543267096374[43] = 0;
   out_359528543267096374[44] = 1;
   out_359528543267096374[45] = 0;
   out_359528543267096374[46] = 0;
   out_359528543267096374[47] = 1;
   out_359528543267096374[48] = 0;
   out_359528543267096374[49] = 0;
   out_359528543267096374[50] = 0;
   out_359528543267096374[51] = 0;
   out_359528543267096374[52] = 0;
   out_359528543267096374[53] = 0;
}
void h_10(double *state, double *unused, double *out_5632699481090685324) {
   out_5632699481090685324[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5632699481090685324[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5632699481090685324[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5235527814809035973) {
   out_5235527814809035973[0] = 0;
   out_5235527814809035973[1] = 9.8100000000000005*cos(state[1]);
   out_5235527814809035973[2] = 0;
   out_5235527814809035973[3] = 0;
   out_5235527814809035973[4] = -state[8];
   out_5235527814809035973[5] = state[7];
   out_5235527814809035973[6] = 0;
   out_5235527814809035973[7] = state[5];
   out_5235527814809035973[8] = -state[4];
   out_5235527814809035973[9] = 0;
   out_5235527814809035973[10] = 0;
   out_5235527814809035973[11] = 0;
   out_5235527814809035973[12] = 1;
   out_5235527814809035973[13] = 0;
   out_5235527814809035973[14] = 0;
   out_5235527814809035973[15] = 1;
   out_5235527814809035973[16] = 0;
   out_5235527814809035973[17] = 0;
   out_5235527814809035973[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5235527814809035973[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5235527814809035973[20] = 0;
   out_5235527814809035973[21] = state[8];
   out_5235527814809035973[22] = 0;
   out_5235527814809035973[23] = -state[6];
   out_5235527814809035973[24] = -state[5];
   out_5235527814809035973[25] = 0;
   out_5235527814809035973[26] = state[3];
   out_5235527814809035973[27] = 0;
   out_5235527814809035973[28] = 0;
   out_5235527814809035973[29] = 0;
   out_5235527814809035973[30] = 0;
   out_5235527814809035973[31] = 1;
   out_5235527814809035973[32] = 0;
   out_5235527814809035973[33] = 0;
   out_5235527814809035973[34] = 1;
   out_5235527814809035973[35] = 0;
   out_5235527814809035973[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5235527814809035973[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5235527814809035973[38] = 0;
   out_5235527814809035973[39] = -state[7];
   out_5235527814809035973[40] = state[6];
   out_5235527814809035973[41] = 0;
   out_5235527814809035973[42] = state[4];
   out_5235527814809035973[43] = -state[3];
   out_5235527814809035973[44] = 0;
   out_5235527814809035973[45] = 0;
   out_5235527814809035973[46] = 0;
   out_5235527814809035973[47] = 0;
   out_5235527814809035973[48] = 0;
   out_5235527814809035973[49] = 0;
   out_5235527814809035973[50] = 1;
   out_5235527814809035973[51] = 0;
   out_5235527814809035973[52] = 0;
   out_5235527814809035973[53] = 1;
}
void h_13(double *state, double *unused, double *out_9169818990097730339) {
   out_9169818990097730339[0] = state[3];
   out_9169818990097730339[1] = state[4];
   out_9169818990097730339[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7251102665049604555) {
   out_7251102665049604555[0] = 0;
   out_7251102665049604555[1] = 0;
   out_7251102665049604555[2] = 0;
   out_7251102665049604555[3] = 1;
   out_7251102665049604555[4] = 0;
   out_7251102665049604555[5] = 0;
   out_7251102665049604555[6] = 0;
   out_7251102665049604555[7] = 0;
   out_7251102665049604555[8] = 0;
   out_7251102665049604555[9] = 0;
   out_7251102665049604555[10] = 0;
   out_7251102665049604555[11] = 0;
   out_7251102665049604555[12] = 0;
   out_7251102665049604555[13] = 0;
   out_7251102665049604555[14] = 0;
   out_7251102665049604555[15] = 0;
   out_7251102665049604555[16] = 0;
   out_7251102665049604555[17] = 0;
   out_7251102665049604555[18] = 0;
   out_7251102665049604555[19] = 0;
   out_7251102665049604555[20] = 0;
   out_7251102665049604555[21] = 0;
   out_7251102665049604555[22] = 1;
   out_7251102665049604555[23] = 0;
   out_7251102665049604555[24] = 0;
   out_7251102665049604555[25] = 0;
   out_7251102665049604555[26] = 0;
   out_7251102665049604555[27] = 0;
   out_7251102665049604555[28] = 0;
   out_7251102665049604555[29] = 0;
   out_7251102665049604555[30] = 0;
   out_7251102665049604555[31] = 0;
   out_7251102665049604555[32] = 0;
   out_7251102665049604555[33] = 0;
   out_7251102665049604555[34] = 0;
   out_7251102665049604555[35] = 0;
   out_7251102665049604555[36] = 0;
   out_7251102665049604555[37] = 0;
   out_7251102665049604555[38] = 0;
   out_7251102665049604555[39] = 0;
   out_7251102665049604555[40] = 0;
   out_7251102665049604555[41] = 1;
   out_7251102665049604555[42] = 0;
   out_7251102665049604555[43] = 0;
   out_7251102665049604555[44] = 0;
   out_7251102665049604555[45] = 0;
   out_7251102665049604555[46] = 0;
   out_7251102665049604555[47] = 0;
   out_7251102665049604555[48] = 0;
   out_7251102665049604555[49] = 0;
   out_7251102665049604555[50] = 0;
   out_7251102665049604555[51] = 0;
   out_7251102665049604555[52] = 0;
   out_7251102665049604555[53] = 0;
}
void h_14(double *state, double *unused, double *out_8130628667462245083) {
   out_8130628667462245083[0] = state[6];
   out_8130628667462245083[1] = state[7];
   out_8130628667462245083[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3603712313072388155) {
   out_3603712313072388155[0] = 0;
   out_3603712313072388155[1] = 0;
   out_3603712313072388155[2] = 0;
   out_3603712313072388155[3] = 0;
   out_3603712313072388155[4] = 0;
   out_3603712313072388155[5] = 0;
   out_3603712313072388155[6] = 1;
   out_3603712313072388155[7] = 0;
   out_3603712313072388155[8] = 0;
   out_3603712313072388155[9] = 0;
   out_3603712313072388155[10] = 0;
   out_3603712313072388155[11] = 0;
   out_3603712313072388155[12] = 0;
   out_3603712313072388155[13] = 0;
   out_3603712313072388155[14] = 0;
   out_3603712313072388155[15] = 0;
   out_3603712313072388155[16] = 0;
   out_3603712313072388155[17] = 0;
   out_3603712313072388155[18] = 0;
   out_3603712313072388155[19] = 0;
   out_3603712313072388155[20] = 0;
   out_3603712313072388155[21] = 0;
   out_3603712313072388155[22] = 0;
   out_3603712313072388155[23] = 0;
   out_3603712313072388155[24] = 0;
   out_3603712313072388155[25] = 1;
   out_3603712313072388155[26] = 0;
   out_3603712313072388155[27] = 0;
   out_3603712313072388155[28] = 0;
   out_3603712313072388155[29] = 0;
   out_3603712313072388155[30] = 0;
   out_3603712313072388155[31] = 0;
   out_3603712313072388155[32] = 0;
   out_3603712313072388155[33] = 0;
   out_3603712313072388155[34] = 0;
   out_3603712313072388155[35] = 0;
   out_3603712313072388155[36] = 0;
   out_3603712313072388155[37] = 0;
   out_3603712313072388155[38] = 0;
   out_3603712313072388155[39] = 0;
   out_3603712313072388155[40] = 0;
   out_3603712313072388155[41] = 0;
   out_3603712313072388155[42] = 0;
   out_3603712313072388155[43] = 0;
   out_3603712313072388155[44] = 1;
   out_3603712313072388155[45] = 0;
   out_3603712313072388155[46] = 0;
   out_3603712313072388155[47] = 0;
   out_3603712313072388155[48] = 0;
   out_3603712313072388155[49] = 0;
   out_3603712313072388155[50] = 0;
   out_3603712313072388155[51] = 0;
   out_3603712313072388155[52] = 0;
   out_3603712313072388155[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5764489290281003311) {
  err_fun(nom_x, delta_x, out_5764489290281003311);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1112330292461843791) {
  inv_err_fun(nom_x, true_x, out_1112330292461843791);
}
void pose_H_mod_fun(double *state, double *out_1113689545321808981) {
  H_mod_fun(state, out_1113689545321808981);
}
void pose_f_fun(double *state, double dt, double *out_6623631471554753598) {
  f_fun(state,  dt, out_6623631471554753598);
}
void pose_F_fun(double *state, double dt, double *out_4351986266867303872) {
  F_fun(state,  dt, out_4351986266867303872);
}
void pose_h_4(double *state, double *unused, double *out_6906405556919747882) {
  h_4(state, unused, out_6906405556919747882);
}
void pose_H_4(double *state, double *unused, double *out_359528543267096374) {
  H_4(state, unused, out_359528543267096374);
}
void pose_h_10(double *state, double *unused, double *out_5632699481090685324) {
  h_10(state, unused, out_5632699481090685324);
}
void pose_H_10(double *state, double *unused, double *out_5235527814809035973) {
  H_10(state, unused, out_5235527814809035973);
}
void pose_h_13(double *state, double *unused, double *out_9169818990097730339) {
  h_13(state, unused, out_9169818990097730339);
}
void pose_H_13(double *state, double *unused, double *out_7251102665049604555) {
  H_13(state, unused, out_7251102665049604555);
}
void pose_h_14(double *state, double *unused, double *out_8130628667462245083) {
  h_14(state, unused, out_8130628667462245083);
}
void pose_H_14(double *state, double *unused, double *out_3603712313072388155) {
  H_14(state, unused, out_3603712313072388155);
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
