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
void err_fun(double *nom_x, double *delta_x, double *out_1129901566109211967) {
   out_1129901566109211967[0] = delta_x[0] + nom_x[0];
   out_1129901566109211967[1] = delta_x[1] + nom_x[1];
   out_1129901566109211967[2] = delta_x[2] + nom_x[2];
   out_1129901566109211967[3] = delta_x[3] + nom_x[3];
   out_1129901566109211967[4] = delta_x[4] + nom_x[4];
   out_1129901566109211967[5] = delta_x[5] + nom_x[5];
   out_1129901566109211967[6] = delta_x[6] + nom_x[6];
   out_1129901566109211967[7] = delta_x[7] + nom_x[7];
   out_1129901566109211967[8] = delta_x[8] + nom_x[8];
   out_1129901566109211967[9] = delta_x[9] + nom_x[9];
   out_1129901566109211967[10] = delta_x[10] + nom_x[10];
   out_1129901566109211967[11] = delta_x[11] + nom_x[11];
   out_1129901566109211967[12] = delta_x[12] + nom_x[12];
   out_1129901566109211967[13] = delta_x[13] + nom_x[13];
   out_1129901566109211967[14] = delta_x[14] + nom_x[14];
   out_1129901566109211967[15] = delta_x[15] + nom_x[15];
   out_1129901566109211967[16] = delta_x[16] + nom_x[16];
   out_1129901566109211967[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5586445504609754685) {
   out_5586445504609754685[0] = -nom_x[0] + true_x[0];
   out_5586445504609754685[1] = -nom_x[1] + true_x[1];
   out_5586445504609754685[2] = -nom_x[2] + true_x[2];
   out_5586445504609754685[3] = -nom_x[3] + true_x[3];
   out_5586445504609754685[4] = -nom_x[4] + true_x[4];
   out_5586445504609754685[5] = -nom_x[5] + true_x[5];
   out_5586445504609754685[6] = -nom_x[6] + true_x[6];
   out_5586445504609754685[7] = -nom_x[7] + true_x[7];
   out_5586445504609754685[8] = -nom_x[8] + true_x[8];
   out_5586445504609754685[9] = -nom_x[9] + true_x[9];
   out_5586445504609754685[10] = -nom_x[10] + true_x[10];
   out_5586445504609754685[11] = -nom_x[11] + true_x[11];
   out_5586445504609754685[12] = -nom_x[12] + true_x[12];
   out_5586445504609754685[13] = -nom_x[13] + true_x[13];
   out_5586445504609754685[14] = -nom_x[14] + true_x[14];
   out_5586445504609754685[15] = -nom_x[15] + true_x[15];
   out_5586445504609754685[16] = -nom_x[16] + true_x[16];
   out_5586445504609754685[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6200665308643472860) {
   out_6200665308643472860[0] = 1.0;
   out_6200665308643472860[1] = 0.0;
   out_6200665308643472860[2] = 0.0;
   out_6200665308643472860[3] = 0.0;
   out_6200665308643472860[4] = 0.0;
   out_6200665308643472860[5] = 0.0;
   out_6200665308643472860[6] = 0.0;
   out_6200665308643472860[7] = 0.0;
   out_6200665308643472860[8] = 0.0;
   out_6200665308643472860[9] = 0.0;
   out_6200665308643472860[10] = 0.0;
   out_6200665308643472860[11] = 0.0;
   out_6200665308643472860[12] = 0.0;
   out_6200665308643472860[13] = 0.0;
   out_6200665308643472860[14] = 0.0;
   out_6200665308643472860[15] = 0.0;
   out_6200665308643472860[16] = 0.0;
   out_6200665308643472860[17] = 0.0;
   out_6200665308643472860[18] = 0.0;
   out_6200665308643472860[19] = 1.0;
   out_6200665308643472860[20] = 0.0;
   out_6200665308643472860[21] = 0.0;
   out_6200665308643472860[22] = 0.0;
   out_6200665308643472860[23] = 0.0;
   out_6200665308643472860[24] = 0.0;
   out_6200665308643472860[25] = 0.0;
   out_6200665308643472860[26] = 0.0;
   out_6200665308643472860[27] = 0.0;
   out_6200665308643472860[28] = 0.0;
   out_6200665308643472860[29] = 0.0;
   out_6200665308643472860[30] = 0.0;
   out_6200665308643472860[31] = 0.0;
   out_6200665308643472860[32] = 0.0;
   out_6200665308643472860[33] = 0.0;
   out_6200665308643472860[34] = 0.0;
   out_6200665308643472860[35] = 0.0;
   out_6200665308643472860[36] = 0.0;
   out_6200665308643472860[37] = 0.0;
   out_6200665308643472860[38] = 1.0;
   out_6200665308643472860[39] = 0.0;
   out_6200665308643472860[40] = 0.0;
   out_6200665308643472860[41] = 0.0;
   out_6200665308643472860[42] = 0.0;
   out_6200665308643472860[43] = 0.0;
   out_6200665308643472860[44] = 0.0;
   out_6200665308643472860[45] = 0.0;
   out_6200665308643472860[46] = 0.0;
   out_6200665308643472860[47] = 0.0;
   out_6200665308643472860[48] = 0.0;
   out_6200665308643472860[49] = 0.0;
   out_6200665308643472860[50] = 0.0;
   out_6200665308643472860[51] = 0.0;
   out_6200665308643472860[52] = 0.0;
   out_6200665308643472860[53] = 0.0;
   out_6200665308643472860[54] = 0.0;
   out_6200665308643472860[55] = 0.0;
   out_6200665308643472860[56] = 0.0;
   out_6200665308643472860[57] = 1.0;
   out_6200665308643472860[58] = 0.0;
   out_6200665308643472860[59] = 0.0;
   out_6200665308643472860[60] = 0.0;
   out_6200665308643472860[61] = 0.0;
   out_6200665308643472860[62] = 0.0;
   out_6200665308643472860[63] = 0.0;
   out_6200665308643472860[64] = 0.0;
   out_6200665308643472860[65] = 0.0;
   out_6200665308643472860[66] = 0.0;
   out_6200665308643472860[67] = 0.0;
   out_6200665308643472860[68] = 0.0;
   out_6200665308643472860[69] = 0.0;
   out_6200665308643472860[70] = 0.0;
   out_6200665308643472860[71] = 0.0;
   out_6200665308643472860[72] = 0.0;
   out_6200665308643472860[73] = 0.0;
   out_6200665308643472860[74] = 0.0;
   out_6200665308643472860[75] = 0.0;
   out_6200665308643472860[76] = 1.0;
   out_6200665308643472860[77] = 0.0;
   out_6200665308643472860[78] = 0.0;
   out_6200665308643472860[79] = 0.0;
   out_6200665308643472860[80] = 0.0;
   out_6200665308643472860[81] = 0.0;
   out_6200665308643472860[82] = 0.0;
   out_6200665308643472860[83] = 0.0;
   out_6200665308643472860[84] = 0.0;
   out_6200665308643472860[85] = 0.0;
   out_6200665308643472860[86] = 0.0;
   out_6200665308643472860[87] = 0.0;
   out_6200665308643472860[88] = 0.0;
   out_6200665308643472860[89] = 0.0;
   out_6200665308643472860[90] = 0.0;
   out_6200665308643472860[91] = 0.0;
   out_6200665308643472860[92] = 0.0;
   out_6200665308643472860[93] = 0.0;
   out_6200665308643472860[94] = 0.0;
   out_6200665308643472860[95] = 1.0;
   out_6200665308643472860[96] = 0.0;
   out_6200665308643472860[97] = 0.0;
   out_6200665308643472860[98] = 0.0;
   out_6200665308643472860[99] = 0.0;
   out_6200665308643472860[100] = 0.0;
   out_6200665308643472860[101] = 0.0;
   out_6200665308643472860[102] = 0.0;
   out_6200665308643472860[103] = 0.0;
   out_6200665308643472860[104] = 0.0;
   out_6200665308643472860[105] = 0.0;
   out_6200665308643472860[106] = 0.0;
   out_6200665308643472860[107] = 0.0;
   out_6200665308643472860[108] = 0.0;
   out_6200665308643472860[109] = 0.0;
   out_6200665308643472860[110] = 0.0;
   out_6200665308643472860[111] = 0.0;
   out_6200665308643472860[112] = 0.0;
   out_6200665308643472860[113] = 0.0;
   out_6200665308643472860[114] = 1.0;
   out_6200665308643472860[115] = 0.0;
   out_6200665308643472860[116] = 0.0;
   out_6200665308643472860[117] = 0.0;
   out_6200665308643472860[118] = 0.0;
   out_6200665308643472860[119] = 0.0;
   out_6200665308643472860[120] = 0.0;
   out_6200665308643472860[121] = 0.0;
   out_6200665308643472860[122] = 0.0;
   out_6200665308643472860[123] = 0.0;
   out_6200665308643472860[124] = 0.0;
   out_6200665308643472860[125] = 0.0;
   out_6200665308643472860[126] = 0.0;
   out_6200665308643472860[127] = 0.0;
   out_6200665308643472860[128] = 0.0;
   out_6200665308643472860[129] = 0.0;
   out_6200665308643472860[130] = 0.0;
   out_6200665308643472860[131] = 0.0;
   out_6200665308643472860[132] = 0.0;
   out_6200665308643472860[133] = 1.0;
   out_6200665308643472860[134] = 0.0;
   out_6200665308643472860[135] = 0.0;
   out_6200665308643472860[136] = 0.0;
   out_6200665308643472860[137] = 0.0;
   out_6200665308643472860[138] = 0.0;
   out_6200665308643472860[139] = 0.0;
   out_6200665308643472860[140] = 0.0;
   out_6200665308643472860[141] = 0.0;
   out_6200665308643472860[142] = 0.0;
   out_6200665308643472860[143] = 0.0;
   out_6200665308643472860[144] = 0.0;
   out_6200665308643472860[145] = 0.0;
   out_6200665308643472860[146] = 0.0;
   out_6200665308643472860[147] = 0.0;
   out_6200665308643472860[148] = 0.0;
   out_6200665308643472860[149] = 0.0;
   out_6200665308643472860[150] = 0.0;
   out_6200665308643472860[151] = 0.0;
   out_6200665308643472860[152] = 1.0;
   out_6200665308643472860[153] = 0.0;
   out_6200665308643472860[154] = 0.0;
   out_6200665308643472860[155] = 0.0;
   out_6200665308643472860[156] = 0.0;
   out_6200665308643472860[157] = 0.0;
   out_6200665308643472860[158] = 0.0;
   out_6200665308643472860[159] = 0.0;
   out_6200665308643472860[160] = 0.0;
   out_6200665308643472860[161] = 0.0;
   out_6200665308643472860[162] = 0.0;
   out_6200665308643472860[163] = 0.0;
   out_6200665308643472860[164] = 0.0;
   out_6200665308643472860[165] = 0.0;
   out_6200665308643472860[166] = 0.0;
   out_6200665308643472860[167] = 0.0;
   out_6200665308643472860[168] = 0.0;
   out_6200665308643472860[169] = 0.0;
   out_6200665308643472860[170] = 0.0;
   out_6200665308643472860[171] = 1.0;
   out_6200665308643472860[172] = 0.0;
   out_6200665308643472860[173] = 0.0;
   out_6200665308643472860[174] = 0.0;
   out_6200665308643472860[175] = 0.0;
   out_6200665308643472860[176] = 0.0;
   out_6200665308643472860[177] = 0.0;
   out_6200665308643472860[178] = 0.0;
   out_6200665308643472860[179] = 0.0;
   out_6200665308643472860[180] = 0.0;
   out_6200665308643472860[181] = 0.0;
   out_6200665308643472860[182] = 0.0;
   out_6200665308643472860[183] = 0.0;
   out_6200665308643472860[184] = 0.0;
   out_6200665308643472860[185] = 0.0;
   out_6200665308643472860[186] = 0.0;
   out_6200665308643472860[187] = 0.0;
   out_6200665308643472860[188] = 0.0;
   out_6200665308643472860[189] = 0.0;
   out_6200665308643472860[190] = 1.0;
   out_6200665308643472860[191] = 0.0;
   out_6200665308643472860[192] = 0.0;
   out_6200665308643472860[193] = 0.0;
   out_6200665308643472860[194] = 0.0;
   out_6200665308643472860[195] = 0.0;
   out_6200665308643472860[196] = 0.0;
   out_6200665308643472860[197] = 0.0;
   out_6200665308643472860[198] = 0.0;
   out_6200665308643472860[199] = 0.0;
   out_6200665308643472860[200] = 0.0;
   out_6200665308643472860[201] = 0.0;
   out_6200665308643472860[202] = 0.0;
   out_6200665308643472860[203] = 0.0;
   out_6200665308643472860[204] = 0.0;
   out_6200665308643472860[205] = 0.0;
   out_6200665308643472860[206] = 0.0;
   out_6200665308643472860[207] = 0.0;
   out_6200665308643472860[208] = 0.0;
   out_6200665308643472860[209] = 1.0;
   out_6200665308643472860[210] = 0.0;
   out_6200665308643472860[211] = 0.0;
   out_6200665308643472860[212] = 0.0;
   out_6200665308643472860[213] = 0.0;
   out_6200665308643472860[214] = 0.0;
   out_6200665308643472860[215] = 0.0;
   out_6200665308643472860[216] = 0.0;
   out_6200665308643472860[217] = 0.0;
   out_6200665308643472860[218] = 0.0;
   out_6200665308643472860[219] = 0.0;
   out_6200665308643472860[220] = 0.0;
   out_6200665308643472860[221] = 0.0;
   out_6200665308643472860[222] = 0.0;
   out_6200665308643472860[223] = 0.0;
   out_6200665308643472860[224] = 0.0;
   out_6200665308643472860[225] = 0.0;
   out_6200665308643472860[226] = 0.0;
   out_6200665308643472860[227] = 0.0;
   out_6200665308643472860[228] = 1.0;
   out_6200665308643472860[229] = 0.0;
   out_6200665308643472860[230] = 0.0;
   out_6200665308643472860[231] = 0.0;
   out_6200665308643472860[232] = 0.0;
   out_6200665308643472860[233] = 0.0;
   out_6200665308643472860[234] = 0.0;
   out_6200665308643472860[235] = 0.0;
   out_6200665308643472860[236] = 0.0;
   out_6200665308643472860[237] = 0.0;
   out_6200665308643472860[238] = 0.0;
   out_6200665308643472860[239] = 0.0;
   out_6200665308643472860[240] = 0.0;
   out_6200665308643472860[241] = 0.0;
   out_6200665308643472860[242] = 0.0;
   out_6200665308643472860[243] = 0.0;
   out_6200665308643472860[244] = 0.0;
   out_6200665308643472860[245] = 0.0;
   out_6200665308643472860[246] = 0.0;
   out_6200665308643472860[247] = 1.0;
   out_6200665308643472860[248] = 0.0;
   out_6200665308643472860[249] = 0.0;
   out_6200665308643472860[250] = 0.0;
   out_6200665308643472860[251] = 0.0;
   out_6200665308643472860[252] = 0.0;
   out_6200665308643472860[253] = 0.0;
   out_6200665308643472860[254] = 0.0;
   out_6200665308643472860[255] = 0.0;
   out_6200665308643472860[256] = 0.0;
   out_6200665308643472860[257] = 0.0;
   out_6200665308643472860[258] = 0.0;
   out_6200665308643472860[259] = 0.0;
   out_6200665308643472860[260] = 0.0;
   out_6200665308643472860[261] = 0.0;
   out_6200665308643472860[262] = 0.0;
   out_6200665308643472860[263] = 0.0;
   out_6200665308643472860[264] = 0.0;
   out_6200665308643472860[265] = 0.0;
   out_6200665308643472860[266] = 1.0;
   out_6200665308643472860[267] = 0.0;
   out_6200665308643472860[268] = 0.0;
   out_6200665308643472860[269] = 0.0;
   out_6200665308643472860[270] = 0.0;
   out_6200665308643472860[271] = 0.0;
   out_6200665308643472860[272] = 0.0;
   out_6200665308643472860[273] = 0.0;
   out_6200665308643472860[274] = 0.0;
   out_6200665308643472860[275] = 0.0;
   out_6200665308643472860[276] = 0.0;
   out_6200665308643472860[277] = 0.0;
   out_6200665308643472860[278] = 0.0;
   out_6200665308643472860[279] = 0.0;
   out_6200665308643472860[280] = 0.0;
   out_6200665308643472860[281] = 0.0;
   out_6200665308643472860[282] = 0.0;
   out_6200665308643472860[283] = 0.0;
   out_6200665308643472860[284] = 0.0;
   out_6200665308643472860[285] = 1.0;
   out_6200665308643472860[286] = 0.0;
   out_6200665308643472860[287] = 0.0;
   out_6200665308643472860[288] = 0.0;
   out_6200665308643472860[289] = 0.0;
   out_6200665308643472860[290] = 0.0;
   out_6200665308643472860[291] = 0.0;
   out_6200665308643472860[292] = 0.0;
   out_6200665308643472860[293] = 0.0;
   out_6200665308643472860[294] = 0.0;
   out_6200665308643472860[295] = 0.0;
   out_6200665308643472860[296] = 0.0;
   out_6200665308643472860[297] = 0.0;
   out_6200665308643472860[298] = 0.0;
   out_6200665308643472860[299] = 0.0;
   out_6200665308643472860[300] = 0.0;
   out_6200665308643472860[301] = 0.0;
   out_6200665308643472860[302] = 0.0;
   out_6200665308643472860[303] = 0.0;
   out_6200665308643472860[304] = 1.0;
   out_6200665308643472860[305] = 0.0;
   out_6200665308643472860[306] = 0.0;
   out_6200665308643472860[307] = 0.0;
   out_6200665308643472860[308] = 0.0;
   out_6200665308643472860[309] = 0.0;
   out_6200665308643472860[310] = 0.0;
   out_6200665308643472860[311] = 0.0;
   out_6200665308643472860[312] = 0.0;
   out_6200665308643472860[313] = 0.0;
   out_6200665308643472860[314] = 0.0;
   out_6200665308643472860[315] = 0.0;
   out_6200665308643472860[316] = 0.0;
   out_6200665308643472860[317] = 0.0;
   out_6200665308643472860[318] = 0.0;
   out_6200665308643472860[319] = 0.0;
   out_6200665308643472860[320] = 0.0;
   out_6200665308643472860[321] = 0.0;
   out_6200665308643472860[322] = 0.0;
   out_6200665308643472860[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8349593971542827612) {
   out_8349593971542827612[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8349593971542827612[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8349593971542827612[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8349593971542827612[3] = dt*state[12] + state[3];
   out_8349593971542827612[4] = dt*state[13] + state[4];
   out_8349593971542827612[5] = dt*state[14] + state[5];
   out_8349593971542827612[6] = state[6];
   out_8349593971542827612[7] = state[7];
   out_8349593971542827612[8] = state[8];
   out_8349593971542827612[9] = state[9];
   out_8349593971542827612[10] = state[10];
   out_8349593971542827612[11] = state[11];
   out_8349593971542827612[12] = state[12];
   out_8349593971542827612[13] = state[13];
   out_8349593971542827612[14] = state[14];
   out_8349593971542827612[15] = state[15];
   out_8349593971542827612[16] = state[16];
   out_8349593971542827612[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2106736445674903187) {
   out_2106736445674903187[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2106736445674903187[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2106736445674903187[2] = 0;
   out_2106736445674903187[3] = 0;
   out_2106736445674903187[4] = 0;
   out_2106736445674903187[5] = 0;
   out_2106736445674903187[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2106736445674903187[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2106736445674903187[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2106736445674903187[9] = 0;
   out_2106736445674903187[10] = 0;
   out_2106736445674903187[11] = 0;
   out_2106736445674903187[12] = 0;
   out_2106736445674903187[13] = 0;
   out_2106736445674903187[14] = 0;
   out_2106736445674903187[15] = 0;
   out_2106736445674903187[16] = 0;
   out_2106736445674903187[17] = 0;
   out_2106736445674903187[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2106736445674903187[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2106736445674903187[20] = 0;
   out_2106736445674903187[21] = 0;
   out_2106736445674903187[22] = 0;
   out_2106736445674903187[23] = 0;
   out_2106736445674903187[24] = 0;
   out_2106736445674903187[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2106736445674903187[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2106736445674903187[27] = 0;
   out_2106736445674903187[28] = 0;
   out_2106736445674903187[29] = 0;
   out_2106736445674903187[30] = 0;
   out_2106736445674903187[31] = 0;
   out_2106736445674903187[32] = 0;
   out_2106736445674903187[33] = 0;
   out_2106736445674903187[34] = 0;
   out_2106736445674903187[35] = 0;
   out_2106736445674903187[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2106736445674903187[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2106736445674903187[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2106736445674903187[39] = 0;
   out_2106736445674903187[40] = 0;
   out_2106736445674903187[41] = 0;
   out_2106736445674903187[42] = 0;
   out_2106736445674903187[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2106736445674903187[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2106736445674903187[45] = 0;
   out_2106736445674903187[46] = 0;
   out_2106736445674903187[47] = 0;
   out_2106736445674903187[48] = 0;
   out_2106736445674903187[49] = 0;
   out_2106736445674903187[50] = 0;
   out_2106736445674903187[51] = 0;
   out_2106736445674903187[52] = 0;
   out_2106736445674903187[53] = 0;
   out_2106736445674903187[54] = 0;
   out_2106736445674903187[55] = 0;
   out_2106736445674903187[56] = 0;
   out_2106736445674903187[57] = 1;
   out_2106736445674903187[58] = 0;
   out_2106736445674903187[59] = 0;
   out_2106736445674903187[60] = 0;
   out_2106736445674903187[61] = 0;
   out_2106736445674903187[62] = 0;
   out_2106736445674903187[63] = 0;
   out_2106736445674903187[64] = 0;
   out_2106736445674903187[65] = 0;
   out_2106736445674903187[66] = dt;
   out_2106736445674903187[67] = 0;
   out_2106736445674903187[68] = 0;
   out_2106736445674903187[69] = 0;
   out_2106736445674903187[70] = 0;
   out_2106736445674903187[71] = 0;
   out_2106736445674903187[72] = 0;
   out_2106736445674903187[73] = 0;
   out_2106736445674903187[74] = 0;
   out_2106736445674903187[75] = 0;
   out_2106736445674903187[76] = 1;
   out_2106736445674903187[77] = 0;
   out_2106736445674903187[78] = 0;
   out_2106736445674903187[79] = 0;
   out_2106736445674903187[80] = 0;
   out_2106736445674903187[81] = 0;
   out_2106736445674903187[82] = 0;
   out_2106736445674903187[83] = 0;
   out_2106736445674903187[84] = 0;
   out_2106736445674903187[85] = dt;
   out_2106736445674903187[86] = 0;
   out_2106736445674903187[87] = 0;
   out_2106736445674903187[88] = 0;
   out_2106736445674903187[89] = 0;
   out_2106736445674903187[90] = 0;
   out_2106736445674903187[91] = 0;
   out_2106736445674903187[92] = 0;
   out_2106736445674903187[93] = 0;
   out_2106736445674903187[94] = 0;
   out_2106736445674903187[95] = 1;
   out_2106736445674903187[96] = 0;
   out_2106736445674903187[97] = 0;
   out_2106736445674903187[98] = 0;
   out_2106736445674903187[99] = 0;
   out_2106736445674903187[100] = 0;
   out_2106736445674903187[101] = 0;
   out_2106736445674903187[102] = 0;
   out_2106736445674903187[103] = 0;
   out_2106736445674903187[104] = dt;
   out_2106736445674903187[105] = 0;
   out_2106736445674903187[106] = 0;
   out_2106736445674903187[107] = 0;
   out_2106736445674903187[108] = 0;
   out_2106736445674903187[109] = 0;
   out_2106736445674903187[110] = 0;
   out_2106736445674903187[111] = 0;
   out_2106736445674903187[112] = 0;
   out_2106736445674903187[113] = 0;
   out_2106736445674903187[114] = 1;
   out_2106736445674903187[115] = 0;
   out_2106736445674903187[116] = 0;
   out_2106736445674903187[117] = 0;
   out_2106736445674903187[118] = 0;
   out_2106736445674903187[119] = 0;
   out_2106736445674903187[120] = 0;
   out_2106736445674903187[121] = 0;
   out_2106736445674903187[122] = 0;
   out_2106736445674903187[123] = 0;
   out_2106736445674903187[124] = 0;
   out_2106736445674903187[125] = 0;
   out_2106736445674903187[126] = 0;
   out_2106736445674903187[127] = 0;
   out_2106736445674903187[128] = 0;
   out_2106736445674903187[129] = 0;
   out_2106736445674903187[130] = 0;
   out_2106736445674903187[131] = 0;
   out_2106736445674903187[132] = 0;
   out_2106736445674903187[133] = 1;
   out_2106736445674903187[134] = 0;
   out_2106736445674903187[135] = 0;
   out_2106736445674903187[136] = 0;
   out_2106736445674903187[137] = 0;
   out_2106736445674903187[138] = 0;
   out_2106736445674903187[139] = 0;
   out_2106736445674903187[140] = 0;
   out_2106736445674903187[141] = 0;
   out_2106736445674903187[142] = 0;
   out_2106736445674903187[143] = 0;
   out_2106736445674903187[144] = 0;
   out_2106736445674903187[145] = 0;
   out_2106736445674903187[146] = 0;
   out_2106736445674903187[147] = 0;
   out_2106736445674903187[148] = 0;
   out_2106736445674903187[149] = 0;
   out_2106736445674903187[150] = 0;
   out_2106736445674903187[151] = 0;
   out_2106736445674903187[152] = 1;
   out_2106736445674903187[153] = 0;
   out_2106736445674903187[154] = 0;
   out_2106736445674903187[155] = 0;
   out_2106736445674903187[156] = 0;
   out_2106736445674903187[157] = 0;
   out_2106736445674903187[158] = 0;
   out_2106736445674903187[159] = 0;
   out_2106736445674903187[160] = 0;
   out_2106736445674903187[161] = 0;
   out_2106736445674903187[162] = 0;
   out_2106736445674903187[163] = 0;
   out_2106736445674903187[164] = 0;
   out_2106736445674903187[165] = 0;
   out_2106736445674903187[166] = 0;
   out_2106736445674903187[167] = 0;
   out_2106736445674903187[168] = 0;
   out_2106736445674903187[169] = 0;
   out_2106736445674903187[170] = 0;
   out_2106736445674903187[171] = 1;
   out_2106736445674903187[172] = 0;
   out_2106736445674903187[173] = 0;
   out_2106736445674903187[174] = 0;
   out_2106736445674903187[175] = 0;
   out_2106736445674903187[176] = 0;
   out_2106736445674903187[177] = 0;
   out_2106736445674903187[178] = 0;
   out_2106736445674903187[179] = 0;
   out_2106736445674903187[180] = 0;
   out_2106736445674903187[181] = 0;
   out_2106736445674903187[182] = 0;
   out_2106736445674903187[183] = 0;
   out_2106736445674903187[184] = 0;
   out_2106736445674903187[185] = 0;
   out_2106736445674903187[186] = 0;
   out_2106736445674903187[187] = 0;
   out_2106736445674903187[188] = 0;
   out_2106736445674903187[189] = 0;
   out_2106736445674903187[190] = 1;
   out_2106736445674903187[191] = 0;
   out_2106736445674903187[192] = 0;
   out_2106736445674903187[193] = 0;
   out_2106736445674903187[194] = 0;
   out_2106736445674903187[195] = 0;
   out_2106736445674903187[196] = 0;
   out_2106736445674903187[197] = 0;
   out_2106736445674903187[198] = 0;
   out_2106736445674903187[199] = 0;
   out_2106736445674903187[200] = 0;
   out_2106736445674903187[201] = 0;
   out_2106736445674903187[202] = 0;
   out_2106736445674903187[203] = 0;
   out_2106736445674903187[204] = 0;
   out_2106736445674903187[205] = 0;
   out_2106736445674903187[206] = 0;
   out_2106736445674903187[207] = 0;
   out_2106736445674903187[208] = 0;
   out_2106736445674903187[209] = 1;
   out_2106736445674903187[210] = 0;
   out_2106736445674903187[211] = 0;
   out_2106736445674903187[212] = 0;
   out_2106736445674903187[213] = 0;
   out_2106736445674903187[214] = 0;
   out_2106736445674903187[215] = 0;
   out_2106736445674903187[216] = 0;
   out_2106736445674903187[217] = 0;
   out_2106736445674903187[218] = 0;
   out_2106736445674903187[219] = 0;
   out_2106736445674903187[220] = 0;
   out_2106736445674903187[221] = 0;
   out_2106736445674903187[222] = 0;
   out_2106736445674903187[223] = 0;
   out_2106736445674903187[224] = 0;
   out_2106736445674903187[225] = 0;
   out_2106736445674903187[226] = 0;
   out_2106736445674903187[227] = 0;
   out_2106736445674903187[228] = 1;
   out_2106736445674903187[229] = 0;
   out_2106736445674903187[230] = 0;
   out_2106736445674903187[231] = 0;
   out_2106736445674903187[232] = 0;
   out_2106736445674903187[233] = 0;
   out_2106736445674903187[234] = 0;
   out_2106736445674903187[235] = 0;
   out_2106736445674903187[236] = 0;
   out_2106736445674903187[237] = 0;
   out_2106736445674903187[238] = 0;
   out_2106736445674903187[239] = 0;
   out_2106736445674903187[240] = 0;
   out_2106736445674903187[241] = 0;
   out_2106736445674903187[242] = 0;
   out_2106736445674903187[243] = 0;
   out_2106736445674903187[244] = 0;
   out_2106736445674903187[245] = 0;
   out_2106736445674903187[246] = 0;
   out_2106736445674903187[247] = 1;
   out_2106736445674903187[248] = 0;
   out_2106736445674903187[249] = 0;
   out_2106736445674903187[250] = 0;
   out_2106736445674903187[251] = 0;
   out_2106736445674903187[252] = 0;
   out_2106736445674903187[253] = 0;
   out_2106736445674903187[254] = 0;
   out_2106736445674903187[255] = 0;
   out_2106736445674903187[256] = 0;
   out_2106736445674903187[257] = 0;
   out_2106736445674903187[258] = 0;
   out_2106736445674903187[259] = 0;
   out_2106736445674903187[260] = 0;
   out_2106736445674903187[261] = 0;
   out_2106736445674903187[262] = 0;
   out_2106736445674903187[263] = 0;
   out_2106736445674903187[264] = 0;
   out_2106736445674903187[265] = 0;
   out_2106736445674903187[266] = 1;
   out_2106736445674903187[267] = 0;
   out_2106736445674903187[268] = 0;
   out_2106736445674903187[269] = 0;
   out_2106736445674903187[270] = 0;
   out_2106736445674903187[271] = 0;
   out_2106736445674903187[272] = 0;
   out_2106736445674903187[273] = 0;
   out_2106736445674903187[274] = 0;
   out_2106736445674903187[275] = 0;
   out_2106736445674903187[276] = 0;
   out_2106736445674903187[277] = 0;
   out_2106736445674903187[278] = 0;
   out_2106736445674903187[279] = 0;
   out_2106736445674903187[280] = 0;
   out_2106736445674903187[281] = 0;
   out_2106736445674903187[282] = 0;
   out_2106736445674903187[283] = 0;
   out_2106736445674903187[284] = 0;
   out_2106736445674903187[285] = 1;
   out_2106736445674903187[286] = 0;
   out_2106736445674903187[287] = 0;
   out_2106736445674903187[288] = 0;
   out_2106736445674903187[289] = 0;
   out_2106736445674903187[290] = 0;
   out_2106736445674903187[291] = 0;
   out_2106736445674903187[292] = 0;
   out_2106736445674903187[293] = 0;
   out_2106736445674903187[294] = 0;
   out_2106736445674903187[295] = 0;
   out_2106736445674903187[296] = 0;
   out_2106736445674903187[297] = 0;
   out_2106736445674903187[298] = 0;
   out_2106736445674903187[299] = 0;
   out_2106736445674903187[300] = 0;
   out_2106736445674903187[301] = 0;
   out_2106736445674903187[302] = 0;
   out_2106736445674903187[303] = 0;
   out_2106736445674903187[304] = 1;
   out_2106736445674903187[305] = 0;
   out_2106736445674903187[306] = 0;
   out_2106736445674903187[307] = 0;
   out_2106736445674903187[308] = 0;
   out_2106736445674903187[309] = 0;
   out_2106736445674903187[310] = 0;
   out_2106736445674903187[311] = 0;
   out_2106736445674903187[312] = 0;
   out_2106736445674903187[313] = 0;
   out_2106736445674903187[314] = 0;
   out_2106736445674903187[315] = 0;
   out_2106736445674903187[316] = 0;
   out_2106736445674903187[317] = 0;
   out_2106736445674903187[318] = 0;
   out_2106736445674903187[319] = 0;
   out_2106736445674903187[320] = 0;
   out_2106736445674903187[321] = 0;
   out_2106736445674903187[322] = 0;
   out_2106736445674903187[323] = 1;
}
void h_4(double *state, double *unused, double *out_5935921283342541016) {
   out_5935921283342541016[0] = state[6] + state[9];
   out_5935921283342541016[1] = state[7] + state[10];
   out_5935921283342541016[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7631451728136762392) {
   out_7631451728136762392[0] = 0;
   out_7631451728136762392[1] = 0;
   out_7631451728136762392[2] = 0;
   out_7631451728136762392[3] = 0;
   out_7631451728136762392[4] = 0;
   out_7631451728136762392[5] = 0;
   out_7631451728136762392[6] = 1;
   out_7631451728136762392[7] = 0;
   out_7631451728136762392[8] = 0;
   out_7631451728136762392[9] = 1;
   out_7631451728136762392[10] = 0;
   out_7631451728136762392[11] = 0;
   out_7631451728136762392[12] = 0;
   out_7631451728136762392[13] = 0;
   out_7631451728136762392[14] = 0;
   out_7631451728136762392[15] = 0;
   out_7631451728136762392[16] = 0;
   out_7631451728136762392[17] = 0;
   out_7631451728136762392[18] = 0;
   out_7631451728136762392[19] = 0;
   out_7631451728136762392[20] = 0;
   out_7631451728136762392[21] = 0;
   out_7631451728136762392[22] = 0;
   out_7631451728136762392[23] = 0;
   out_7631451728136762392[24] = 0;
   out_7631451728136762392[25] = 1;
   out_7631451728136762392[26] = 0;
   out_7631451728136762392[27] = 0;
   out_7631451728136762392[28] = 1;
   out_7631451728136762392[29] = 0;
   out_7631451728136762392[30] = 0;
   out_7631451728136762392[31] = 0;
   out_7631451728136762392[32] = 0;
   out_7631451728136762392[33] = 0;
   out_7631451728136762392[34] = 0;
   out_7631451728136762392[35] = 0;
   out_7631451728136762392[36] = 0;
   out_7631451728136762392[37] = 0;
   out_7631451728136762392[38] = 0;
   out_7631451728136762392[39] = 0;
   out_7631451728136762392[40] = 0;
   out_7631451728136762392[41] = 0;
   out_7631451728136762392[42] = 0;
   out_7631451728136762392[43] = 0;
   out_7631451728136762392[44] = 1;
   out_7631451728136762392[45] = 0;
   out_7631451728136762392[46] = 0;
   out_7631451728136762392[47] = 1;
   out_7631451728136762392[48] = 0;
   out_7631451728136762392[49] = 0;
   out_7631451728136762392[50] = 0;
   out_7631451728136762392[51] = 0;
   out_7631451728136762392[52] = 0;
   out_7631451728136762392[53] = 0;
}
void h_10(double *state, double *unused, double *out_6985262437261806861) {
   out_6985262437261806861[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6985262437261806861[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6985262437261806861[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1981603586596583282) {
   out_1981603586596583282[0] = 0;
   out_1981603586596583282[1] = 9.8100000000000005*cos(state[1]);
   out_1981603586596583282[2] = 0;
   out_1981603586596583282[3] = 0;
   out_1981603586596583282[4] = -state[8];
   out_1981603586596583282[5] = state[7];
   out_1981603586596583282[6] = 0;
   out_1981603586596583282[7] = state[5];
   out_1981603586596583282[8] = -state[4];
   out_1981603586596583282[9] = 0;
   out_1981603586596583282[10] = 0;
   out_1981603586596583282[11] = 0;
   out_1981603586596583282[12] = 1;
   out_1981603586596583282[13] = 0;
   out_1981603586596583282[14] = 0;
   out_1981603586596583282[15] = 1;
   out_1981603586596583282[16] = 0;
   out_1981603586596583282[17] = 0;
   out_1981603586596583282[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1981603586596583282[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1981603586596583282[20] = 0;
   out_1981603586596583282[21] = state[8];
   out_1981603586596583282[22] = 0;
   out_1981603586596583282[23] = -state[6];
   out_1981603586596583282[24] = -state[5];
   out_1981603586596583282[25] = 0;
   out_1981603586596583282[26] = state[3];
   out_1981603586596583282[27] = 0;
   out_1981603586596583282[28] = 0;
   out_1981603586596583282[29] = 0;
   out_1981603586596583282[30] = 0;
   out_1981603586596583282[31] = 1;
   out_1981603586596583282[32] = 0;
   out_1981603586596583282[33] = 0;
   out_1981603586596583282[34] = 1;
   out_1981603586596583282[35] = 0;
   out_1981603586596583282[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1981603586596583282[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1981603586596583282[38] = 0;
   out_1981603586596583282[39] = -state[7];
   out_1981603586596583282[40] = state[6];
   out_1981603586596583282[41] = 0;
   out_1981603586596583282[42] = state[4];
   out_1981603586596583282[43] = -state[3];
   out_1981603586596583282[44] = 0;
   out_1981603586596583282[45] = 0;
   out_1981603586596583282[46] = 0;
   out_1981603586596583282[47] = 0;
   out_1981603586596583282[48] = 0;
   out_1981603586596583282[49] = 0;
   out_1981603586596583282[50] = 1;
   out_1981603586596583282[51] = 0;
   out_1981603586596583282[52] = 0;
   out_1981603586596583282[53] = 1;
}
void h_13(double *state, double *unused, double *out_5585222753052016340) {
   out_5585222753052016340[0] = state[3];
   out_5585222753052016340[1] = state[4];
   out_5585222753052016340[2] = state[5];
}
void H_13(double *state, double *unused, double *out_20820519820061463) {
   out_20820519820061463[0] = 0;
   out_20820519820061463[1] = 0;
   out_20820519820061463[2] = 0;
   out_20820519820061463[3] = 1;
   out_20820519820061463[4] = 0;
   out_20820519820061463[5] = 0;
   out_20820519820061463[6] = 0;
   out_20820519820061463[7] = 0;
   out_20820519820061463[8] = 0;
   out_20820519820061463[9] = 0;
   out_20820519820061463[10] = 0;
   out_20820519820061463[11] = 0;
   out_20820519820061463[12] = 0;
   out_20820519820061463[13] = 0;
   out_20820519820061463[14] = 0;
   out_20820519820061463[15] = 0;
   out_20820519820061463[16] = 0;
   out_20820519820061463[17] = 0;
   out_20820519820061463[18] = 0;
   out_20820519820061463[19] = 0;
   out_20820519820061463[20] = 0;
   out_20820519820061463[21] = 0;
   out_20820519820061463[22] = 1;
   out_20820519820061463[23] = 0;
   out_20820519820061463[24] = 0;
   out_20820519820061463[25] = 0;
   out_20820519820061463[26] = 0;
   out_20820519820061463[27] = 0;
   out_20820519820061463[28] = 0;
   out_20820519820061463[29] = 0;
   out_20820519820061463[30] = 0;
   out_20820519820061463[31] = 0;
   out_20820519820061463[32] = 0;
   out_20820519820061463[33] = 0;
   out_20820519820061463[34] = 0;
   out_20820519820061463[35] = 0;
   out_20820519820061463[36] = 0;
   out_20820519820061463[37] = 0;
   out_20820519820061463[38] = 0;
   out_20820519820061463[39] = 0;
   out_20820519820061463[40] = 0;
   out_20820519820061463[41] = 1;
   out_20820519820061463[42] = 0;
   out_20820519820061463[43] = 0;
   out_20820519820061463[44] = 0;
   out_20820519820061463[45] = 0;
   out_20820519820061463[46] = 0;
   out_20820519820061463[47] = 0;
   out_20820519820061463[48] = 0;
   out_20820519820061463[49] = 0;
   out_20820519820061463[50] = 0;
   out_20820519820061463[51] = 0;
   out_20820519820061463[52] = 0;
   out_20820519820061463[53] = 0;
}
void h_14(double *state, double *unused, double *out_2199267947897191042) {
   out_2199267947897191042[0] = state[6];
   out_2199267947897191042[1] = state[7];
   out_2199267947897191042[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3668210871797277863) {
   out_3668210871797277863[0] = 0;
   out_3668210871797277863[1] = 0;
   out_3668210871797277863[2] = 0;
   out_3668210871797277863[3] = 0;
   out_3668210871797277863[4] = 0;
   out_3668210871797277863[5] = 0;
   out_3668210871797277863[6] = 1;
   out_3668210871797277863[7] = 0;
   out_3668210871797277863[8] = 0;
   out_3668210871797277863[9] = 0;
   out_3668210871797277863[10] = 0;
   out_3668210871797277863[11] = 0;
   out_3668210871797277863[12] = 0;
   out_3668210871797277863[13] = 0;
   out_3668210871797277863[14] = 0;
   out_3668210871797277863[15] = 0;
   out_3668210871797277863[16] = 0;
   out_3668210871797277863[17] = 0;
   out_3668210871797277863[18] = 0;
   out_3668210871797277863[19] = 0;
   out_3668210871797277863[20] = 0;
   out_3668210871797277863[21] = 0;
   out_3668210871797277863[22] = 0;
   out_3668210871797277863[23] = 0;
   out_3668210871797277863[24] = 0;
   out_3668210871797277863[25] = 1;
   out_3668210871797277863[26] = 0;
   out_3668210871797277863[27] = 0;
   out_3668210871797277863[28] = 0;
   out_3668210871797277863[29] = 0;
   out_3668210871797277863[30] = 0;
   out_3668210871797277863[31] = 0;
   out_3668210871797277863[32] = 0;
   out_3668210871797277863[33] = 0;
   out_3668210871797277863[34] = 0;
   out_3668210871797277863[35] = 0;
   out_3668210871797277863[36] = 0;
   out_3668210871797277863[37] = 0;
   out_3668210871797277863[38] = 0;
   out_3668210871797277863[39] = 0;
   out_3668210871797277863[40] = 0;
   out_3668210871797277863[41] = 0;
   out_3668210871797277863[42] = 0;
   out_3668210871797277863[43] = 0;
   out_3668210871797277863[44] = 1;
   out_3668210871797277863[45] = 0;
   out_3668210871797277863[46] = 0;
   out_3668210871797277863[47] = 0;
   out_3668210871797277863[48] = 0;
   out_3668210871797277863[49] = 0;
   out_3668210871797277863[50] = 0;
   out_3668210871797277863[51] = 0;
   out_3668210871797277863[52] = 0;
   out_3668210871797277863[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1129901566109211967) {
  err_fun(nom_x, delta_x, out_1129901566109211967);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5586445504609754685) {
  inv_err_fun(nom_x, true_x, out_5586445504609754685);
}
void pose_H_mod_fun(double *state, double *out_6200665308643472860) {
  H_mod_fun(state, out_6200665308643472860);
}
void pose_f_fun(double *state, double dt, double *out_8349593971542827612) {
  f_fun(state,  dt, out_8349593971542827612);
}
void pose_F_fun(double *state, double dt, double *out_2106736445674903187) {
  F_fun(state,  dt, out_2106736445674903187);
}
void pose_h_4(double *state, double *unused, double *out_5935921283342541016) {
  h_4(state, unused, out_5935921283342541016);
}
void pose_H_4(double *state, double *unused, double *out_7631451728136762392) {
  H_4(state, unused, out_7631451728136762392);
}
void pose_h_10(double *state, double *unused, double *out_6985262437261806861) {
  h_10(state, unused, out_6985262437261806861);
}
void pose_H_10(double *state, double *unused, double *out_1981603586596583282) {
  H_10(state, unused, out_1981603586596583282);
}
void pose_h_13(double *state, double *unused, double *out_5585222753052016340) {
  h_13(state, unused, out_5585222753052016340);
}
void pose_H_13(double *state, double *unused, double *out_20820519820061463) {
  H_13(state, unused, out_20820519820061463);
}
void pose_h_14(double *state, double *unused, double *out_2199267947897191042) {
  h_14(state, unused, out_2199267947897191042);
}
void pose_H_14(double *state, double *unused, double *out_3668210871797277863) {
  H_14(state, unused, out_3668210871797277863);
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
