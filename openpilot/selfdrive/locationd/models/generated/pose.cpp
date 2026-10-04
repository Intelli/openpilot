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
void err_fun(double *nom_x, double *delta_x, double *out_6405940408767953849) {
   out_6405940408767953849[0] = delta_x[0] + nom_x[0];
   out_6405940408767953849[1] = delta_x[1] + nom_x[1];
   out_6405940408767953849[2] = delta_x[2] + nom_x[2];
   out_6405940408767953849[3] = delta_x[3] + nom_x[3];
   out_6405940408767953849[4] = delta_x[4] + nom_x[4];
   out_6405940408767953849[5] = delta_x[5] + nom_x[5];
   out_6405940408767953849[6] = delta_x[6] + nom_x[6];
   out_6405940408767953849[7] = delta_x[7] + nom_x[7];
   out_6405940408767953849[8] = delta_x[8] + nom_x[8];
   out_6405940408767953849[9] = delta_x[9] + nom_x[9];
   out_6405940408767953849[10] = delta_x[10] + nom_x[10];
   out_6405940408767953849[11] = delta_x[11] + nom_x[11];
   out_6405940408767953849[12] = delta_x[12] + nom_x[12];
   out_6405940408767953849[13] = delta_x[13] + nom_x[13];
   out_6405940408767953849[14] = delta_x[14] + nom_x[14];
   out_6405940408767953849[15] = delta_x[15] + nom_x[15];
   out_6405940408767953849[16] = delta_x[16] + nom_x[16];
   out_6405940408767953849[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8262227002071130515) {
   out_8262227002071130515[0] = -nom_x[0] + true_x[0];
   out_8262227002071130515[1] = -nom_x[1] + true_x[1];
   out_8262227002071130515[2] = -nom_x[2] + true_x[2];
   out_8262227002071130515[3] = -nom_x[3] + true_x[3];
   out_8262227002071130515[4] = -nom_x[4] + true_x[4];
   out_8262227002071130515[5] = -nom_x[5] + true_x[5];
   out_8262227002071130515[6] = -nom_x[6] + true_x[6];
   out_8262227002071130515[7] = -nom_x[7] + true_x[7];
   out_8262227002071130515[8] = -nom_x[8] + true_x[8];
   out_8262227002071130515[9] = -nom_x[9] + true_x[9];
   out_8262227002071130515[10] = -nom_x[10] + true_x[10];
   out_8262227002071130515[11] = -nom_x[11] + true_x[11];
   out_8262227002071130515[12] = -nom_x[12] + true_x[12];
   out_8262227002071130515[13] = -nom_x[13] + true_x[13];
   out_8262227002071130515[14] = -nom_x[14] + true_x[14];
   out_8262227002071130515[15] = -nom_x[15] + true_x[15];
   out_8262227002071130515[16] = -nom_x[16] + true_x[16];
   out_8262227002071130515[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4958429311639991198) {
   out_4958429311639991198[0] = 1.0;
   out_4958429311639991198[1] = 0.0;
   out_4958429311639991198[2] = 0.0;
   out_4958429311639991198[3] = 0.0;
   out_4958429311639991198[4] = 0.0;
   out_4958429311639991198[5] = 0.0;
   out_4958429311639991198[6] = 0.0;
   out_4958429311639991198[7] = 0.0;
   out_4958429311639991198[8] = 0.0;
   out_4958429311639991198[9] = 0.0;
   out_4958429311639991198[10] = 0.0;
   out_4958429311639991198[11] = 0.0;
   out_4958429311639991198[12] = 0.0;
   out_4958429311639991198[13] = 0.0;
   out_4958429311639991198[14] = 0.0;
   out_4958429311639991198[15] = 0.0;
   out_4958429311639991198[16] = 0.0;
   out_4958429311639991198[17] = 0.0;
   out_4958429311639991198[18] = 0.0;
   out_4958429311639991198[19] = 1.0;
   out_4958429311639991198[20] = 0.0;
   out_4958429311639991198[21] = 0.0;
   out_4958429311639991198[22] = 0.0;
   out_4958429311639991198[23] = 0.0;
   out_4958429311639991198[24] = 0.0;
   out_4958429311639991198[25] = 0.0;
   out_4958429311639991198[26] = 0.0;
   out_4958429311639991198[27] = 0.0;
   out_4958429311639991198[28] = 0.0;
   out_4958429311639991198[29] = 0.0;
   out_4958429311639991198[30] = 0.0;
   out_4958429311639991198[31] = 0.0;
   out_4958429311639991198[32] = 0.0;
   out_4958429311639991198[33] = 0.0;
   out_4958429311639991198[34] = 0.0;
   out_4958429311639991198[35] = 0.0;
   out_4958429311639991198[36] = 0.0;
   out_4958429311639991198[37] = 0.0;
   out_4958429311639991198[38] = 1.0;
   out_4958429311639991198[39] = 0.0;
   out_4958429311639991198[40] = 0.0;
   out_4958429311639991198[41] = 0.0;
   out_4958429311639991198[42] = 0.0;
   out_4958429311639991198[43] = 0.0;
   out_4958429311639991198[44] = 0.0;
   out_4958429311639991198[45] = 0.0;
   out_4958429311639991198[46] = 0.0;
   out_4958429311639991198[47] = 0.0;
   out_4958429311639991198[48] = 0.0;
   out_4958429311639991198[49] = 0.0;
   out_4958429311639991198[50] = 0.0;
   out_4958429311639991198[51] = 0.0;
   out_4958429311639991198[52] = 0.0;
   out_4958429311639991198[53] = 0.0;
   out_4958429311639991198[54] = 0.0;
   out_4958429311639991198[55] = 0.0;
   out_4958429311639991198[56] = 0.0;
   out_4958429311639991198[57] = 1.0;
   out_4958429311639991198[58] = 0.0;
   out_4958429311639991198[59] = 0.0;
   out_4958429311639991198[60] = 0.0;
   out_4958429311639991198[61] = 0.0;
   out_4958429311639991198[62] = 0.0;
   out_4958429311639991198[63] = 0.0;
   out_4958429311639991198[64] = 0.0;
   out_4958429311639991198[65] = 0.0;
   out_4958429311639991198[66] = 0.0;
   out_4958429311639991198[67] = 0.0;
   out_4958429311639991198[68] = 0.0;
   out_4958429311639991198[69] = 0.0;
   out_4958429311639991198[70] = 0.0;
   out_4958429311639991198[71] = 0.0;
   out_4958429311639991198[72] = 0.0;
   out_4958429311639991198[73] = 0.0;
   out_4958429311639991198[74] = 0.0;
   out_4958429311639991198[75] = 0.0;
   out_4958429311639991198[76] = 1.0;
   out_4958429311639991198[77] = 0.0;
   out_4958429311639991198[78] = 0.0;
   out_4958429311639991198[79] = 0.0;
   out_4958429311639991198[80] = 0.0;
   out_4958429311639991198[81] = 0.0;
   out_4958429311639991198[82] = 0.0;
   out_4958429311639991198[83] = 0.0;
   out_4958429311639991198[84] = 0.0;
   out_4958429311639991198[85] = 0.0;
   out_4958429311639991198[86] = 0.0;
   out_4958429311639991198[87] = 0.0;
   out_4958429311639991198[88] = 0.0;
   out_4958429311639991198[89] = 0.0;
   out_4958429311639991198[90] = 0.0;
   out_4958429311639991198[91] = 0.0;
   out_4958429311639991198[92] = 0.0;
   out_4958429311639991198[93] = 0.0;
   out_4958429311639991198[94] = 0.0;
   out_4958429311639991198[95] = 1.0;
   out_4958429311639991198[96] = 0.0;
   out_4958429311639991198[97] = 0.0;
   out_4958429311639991198[98] = 0.0;
   out_4958429311639991198[99] = 0.0;
   out_4958429311639991198[100] = 0.0;
   out_4958429311639991198[101] = 0.0;
   out_4958429311639991198[102] = 0.0;
   out_4958429311639991198[103] = 0.0;
   out_4958429311639991198[104] = 0.0;
   out_4958429311639991198[105] = 0.0;
   out_4958429311639991198[106] = 0.0;
   out_4958429311639991198[107] = 0.0;
   out_4958429311639991198[108] = 0.0;
   out_4958429311639991198[109] = 0.0;
   out_4958429311639991198[110] = 0.0;
   out_4958429311639991198[111] = 0.0;
   out_4958429311639991198[112] = 0.0;
   out_4958429311639991198[113] = 0.0;
   out_4958429311639991198[114] = 1.0;
   out_4958429311639991198[115] = 0.0;
   out_4958429311639991198[116] = 0.0;
   out_4958429311639991198[117] = 0.0;
   out_4958429311639991198[118] = 0.0;
   out_4958429311639991198[119] = 0.0;
   out_4958429311639991198[120] = 0.0;
   out_4958429311639991198[121] = 0.0;
   out_4958429311639991198[122] = 0.0;
   out_4958429311639991198[123] = 0.0;
   out_4958429311639991198[124] = 0.0;
   out_4958429311639991198[125] = 0.0;
   out_4958429311639991198[126] = 0.0;
   out_4958429311639991198[127] = 0.0;
   out_4958429311639991198[128] = 0.0;
   out_4958429311639991198[129] = 0.0;
   out_4958429311639991198[130] = 0.0;
   out_4958429311639991198[131] = 0.0;
   out_4958429311639991198[132] = 0.0;
   out_4958429311639991198[133] = 1.0;
   out_4958429311639991198[134] = 0.0;
   out_4958429311639991198[135] = 0.0;
   out_4958429311639991198[136] = 0.0;
   out_4958429311639991198[137] = 0.0;
   out_4958429311639991198[138] = 0.0;
   out_4958429311639991198[139] = 0.0;
   out_4958429311639991198[140] = 0.0;
   out_4958429311639991198[141] = 0.0;
   out_4958429311639991198[142] = 0.0;
   out_4958429311639991198[143] = 0.0;
   out_4958429311639991198[144] = 0.0;
   out_4958429311639991198[145] = 0.0;
   out_4958429311639991198[146] = 0.0;
   out_4958429311639991198[147] = 0.0;
   out_4958429311639991198[148] = 0.0;
   out_4958429311639991198[149] = 0.0;
   out_4958429311639991198[150] = 0.0;
   out_4958429311639991198[151] = 0.0;
   out_4958429311639991198[152] = 1.0;
   out_4958429311639991198[153] = 0.0;
   out_4958429311639991198[154] = 0.0;
   out_4958429311639991198[155] = 0.0;
   out_4958429311639991198[156] = 0.0;
   out_4958429311639991198[157] = 0.0;
   out_4958429311639991198[158] = 0.0;
   out_4958429311639991198[159] = 0.0;
   out_4958429311639991198[160] = 0.0;
   out_4958429311639991198[161] = 0.0;
   out_4958429311639991198[162] = 0.0;
   out_4958429311639991198[163] = 0.0;
   out_4958429311639991198[164] = 0.0;
   out_4958429311639991198[165] = 0.0;
   out_4958429311639991198[166] = 0.0;
   out_4958429311639991198[167] = 0.0;
   out_4958429311639991198[168] = 0.0;
   out_4958429311639991198[169] = 0.0;
   out_4958429311639991198[170] = 0.0;
   out_4958429311639991198[171] = 1.0;
   out_4958429311639991198[172] = 0.0;
   out_4958429311639991198[173] = 0.0;
   out_4958429311639991198[174] = 0.0;
   out_4958429311639991198[175] = 0.0;
   out_4958429311639991198[176] = 0.0;
   out_4958429311639991198[177] = 0.0;
   out_4958429311639991198[178] = 0.0;
   out_4958429311639991198[179] = 0.0;
   out_4958429311639991198[180] = 0.0;
   out_4958429311639991198[181] = 0.0;
   out_4958429311639991198[182] = 0.0;
   out_4958429311639991198[183] = 0.0;
   out_4958429311639991198[184] = 0.0;
   out_4958429311639991198[185] = 0.0;
   out_4958429311639991198[186] = 0.0;
   out_4958429311639991198[187] = 0.0;
   out_4958429311639991198[188] = 0.0;
   out_4958429311639991198[189] = 0.0;
   out_4958429311639991198[190] = 1.0;
   out_4958429311639991198[191] = 0.0;
   out_4958429311639991198[192] = 0.0;
   out_4958429311639991198[193] = 0.0;
   out_4958429311639991198[194] = 0.0;
   out_4958429311639991198[195] = 0.0;
   out_4958429311639991198[196] = 0.0;
   out_4958429311639991198[197] = 0.0;
   out_4958429311639991198[198] = 0.0;
   out_4958429311639991198[199] = 0.0;
   out_4958429311639991198[200] = 0.0;
   out_4958429311639991198[201] = 0.0;
   out_4958429311639991198[202] = 0.0;
   out_4958429311639991198[203] = 0.0;
   out_4958429311639991198[204] = 0.0;
   out_4958429311639991198[205] = 0.0;
   out_4958429311639991198[206] = 0.0;
   out_4958429311639991198[207] = 0.0;
   out_4958429311639991198[208] = 0.0;
   out_4958429311639991198[209] = 1.0;
   out_4958429311639991198[210] = 0.0;
   out_4958429311639991198[211] = 0.0;
   out_4958429311639991198[212] = 0.0;
   out_4958429311639991198[213] = 0.0;
   out_4958429311639991198[214] = 0.0;
   out_4958429311639991198[215] = 0.0;
   out_4958429311639991198[216] = 0.0;
   out_4958429311639991198[217] = 0.0;
   out_4958429311639991198[218] = 0.0;
   out_4958429311639991198[219] = 0.0;
   out_4958429311639991198[220] = 0.0;
   out_4958429311639991198[221] = 0.0;
   out_4958429311639991198[222] = 0.0;
   out_4958429311639991198[223] = 0.0;
   out_4958429311639991198[224] = 0.0;
   out_4958429311639991198[225] = 0.0;
   out_4958429311639991198[226] = 0.0;
   out_4958429311639991198[227] = 0.0;
   out_4958429311639991198[228] = 1.0;
   out_4958429311639991198[229] = 0.0;
   out_4958429311639991198[230] = 0.0;
   out_4958429311639991198[231] = 0.0;
   out_4958429311639991198[232] = 0.0;
   out_4958429311639991198[233] = 0.0;
   out_4958429311639991198[234] = 0.0;
   out_4958429311639991198[235] = 0.0;
   out_4958429311639991198[236] = 0.0;
   out_4958429311639991198[237] = 0.0;
   out_4958429311639991198[238] = 0.0;
   out_4958429311639991198[239] = 0.0;
   out_4958429311639991198[240] = 0.0;
   out_4958429311639991198[241] = 0.0;
   out_4958429311639991198[242] = 0.0;
   out_4958429311639991198[243] = 0.0;
   out_4958429311639991198[244] = 0.0;
   out_4958429311639991198[245] = 0.0;
   out_4958429311639991198[246] = 0.0;
   out_4958429311639991198[247] = 1.0;
   out_4958429311639991198[248] = 0.0;
   out_4958429311639991198[249] = 0.0;
   out_4958429311639991198[250] = 0.0;
   out_4958429311639991198[251] = 0.0;
   out_4958429311639991198[252] = 0.0;
   out_4958429311639991198[253] = 0.0;
   out_4958429311639991198[254] = 0.0;
   out_4958429311639991198[255] = 0.0;
   out_4958429311639991198[256] = 0.0;
   out_4958429311639991198[257] = 0.0;
   out_4958429311639991198[258] = 0.0;
   out_4958429311639991198[259] = 0.0;
   out_4958429311639991198[260] = 0.0;
   out_4958429311639991198[261] = 0.0;
   out_4958429311639991198[262] = 0.0;
   out_4958429311639991198[263] = 0.0;
   out_4958429311639991198[264] = 0.0;
   out_4958429311639991198[265] = 0.0;
   out_4958429311639991198[266] = 1.0;
   out_4958429311639991198[267] = 0.0;
   out_4958429311639991198[268] = 0.0;
   out_4958429311639991198[269] = 0.0;
   out_4958429311639991198[270] = 0.0;
   out_4958429311639991198[271] = 0.0;
   out_4958429311639991198[272] = 0.0;
   out_4958429311639991198[273] = 0.0;
   out_4958429311639991198[274] = 0.0;
   out_4958429311639991198[275] = 0.0;
   out_4958429311639991198[276] = 0.0;
   out_4958429311639991198[277] = 0.0;
   out_4958429311639991198[278] = 0.0;
   out_4958429311639991198[279] = 0.0;
   out_4958429311639991198[280] = 0.0;
   out_4958429311639991198[281] = 0.0;
   out_4958429311639991198[282] = 0.0;
   out_4958429311639991198[283] = 0.0;
   out_4958429311639991198[284] = 0.0;
   out_4958429311639991198[285] = 1.0;
   out_4958429311639991198[286] = 0.0;
   out_4958429311639991198[287] = 0.0;
   out_4958429311639991198[288] = 0.0;
   out_4958429311639991198[289] = 0.0;
   out_4958429311639991198[290] = 0.0;
   out_4958429311639991198[291] = 0.0;
   out_4958429311639991198[292] = 0.0;
   out_4958429311639991198[293] = 0.0;
   out_4958429311639991198[294] = 0.0;
   out_4958429311639991198[295] = 0.0;
   out_4958429311639991198[296] = 0.0;
   out_4958429311639991198[297] = 0.0;
   out_4958429311639991198[298] = 0.0;
   out_4958429311639991198[299] = 0.0;
   out_4958429311639991198[300] = 0.0;
   out_4958429311639991198[301] = 0.0;
   out_4958429311639991198[302] = 0.0;
   out_4958429311639991198[303] = 0.0;
   out_4958429311639991198[304] = 1.0;
   out_4958429311639991198[305] = 0.0;
   out_4958429311639991198[306] = 0.0;
   out_4958429311639991198[307] = 0.0;
   out_4958429311639991198[308] = 0.0;
   out_4958429311639991198[309] = 0.0;
   out_4958429311639991198[310] = 0.0;
   out_4958429311639991198[311] = 0.0;
   out_4958429311639991198[312] = 0.0;
   out_4958429311639991198[313] = 0.0;
   out_4958429311639991198[314] = 0.0;
   out_4958429311639991198[315] = 0.0;
   out_4958429311639991198[316] = 0.0;
   out_4958429311639991198[317] = 0.0;
   out_4958429311639991198[318] = 0.0;
   out_4958429311639991198[319] = 0.0;
   out_4958429311639991198[320] = 0.0;
   out_4958429311639991198[321] = 0.0;
   out_4958429311639991198[322] = 0.0;
   out_4958429311639991198[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6795570829506520409) {
   out_6795570829506520409[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6795570829506520409[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6795570829506520409[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6795570829506520409[3] = dt*state[12] + state[3];
   out_6795570829506520409[4] = dt*state[13] + state[4];
   out_6795570829506520409[5] = dt*state[14] + state[5];
   out_6795570829506520409[6] = state[6];
   out_6795570829506520409[7] = state[7];
   out_6795570829506520409[8] = state[8];
   out_6795570829506520409[9] = state[9];
   out_6795570829506520409[10] = state[10];
   out_6795570829506520409[11] = state[11];
   out_6795570829506520409[12] = state[12];
   out_6795570829506520409[13] = state[13];
   out_6795570829506520409[14] = state[14];
   out_6795570829506520409[15] = state[15];
   out_6795570829506520409[16] = state[16];
   out_6795570829506520409[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6072665348488724658) {
   out_6072665348488724658[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6072665348488724658[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6072665348488724658[2] = 0;
   out_6072665348488724658[3] = 0;
   out_6072665348488724658[4] = 0;
   out_6072665348488724658[5] = 0;
   out_6072665348488724658[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6072665348488724658[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6072665348488724658[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6072665348488724658[9] = 0;
   out_6072665348488724658[10] = 0;
   out_6072665348488724658[11] = 0;
   out_6072665348488724658[12] = 0;
   out_6072665348488724658[13] = 0;
   out_6072665348488724658[14] = 0;
   out_6072665348488724658[15] = 0;
   out_6072665348488724658[16] = 0;
   out_6072665348488724658[17] = 0;
   out_6072665348488724658[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6072665348488724658[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6072665348488724658[20] = 0;
   out_6072665348488724658[21] = 0;
   out_6072665348488724658[22] = 0;
   out_6072665348488724658[23] = 0;
   out_6072665348488724658[24] = 0;
   out_6072665348488724658[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6072665348488724658[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6072665348488724658[27] = 0;
   out_6072665348488724658[28] = 0;
   out_6072665348488724658[29] = 0;
   out_6072665348488724658[30] = 0;
   out_6072665348488724658[31] = 0;
   out_6072665348488724658[32] = 0;
   out_6072665348488724658[33] = 0;
   out_6072665348488724658[34] = 0;
   out_6072665348488724658[35] = 0;
   out_6072665348488724658[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6072665348488724658[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6072665348488724658[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6072665348488724658[39] = 0;
   out_6072665348488724658[40] = 0;
   out_6072665348488724658[41] = 0;
   out_6072665348488724658[42] = 0;
   out_6072665348488724658[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6072665348488724658[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6072665348488724658[45] = 0;
   out_6072665348488724658[46] = 0;
   out_6072665348488724658[47] = 0;
   out_6072665348488724658[48] = 0;
   out_6072665348488724658[49] = 0;
   out_6072665348488724658[50] = 0;
   out_6072665348488724658[51] = 0;
   out_6072665348488724658[52] = 0;
   out_6072665348488724658[53] = 0;
   out_6072665348488724658[54] = 0;
   out_6072665348488724658[55] = 0;
   out_6072665348488724658[56] = 0;
   out_6072665348488724658[57] = 1;
   out_6072665348488724658[58] = 0;
   out_6072665348488724658[59] = 0;
   out_6072665348488724658[60] = 0;
   out_6072665348488724658[61] = 0;
   out_6072665348488724658[62] = 0;
   out_6072665348488724658[63] = 0;
   out_6072665348488724658[64] = 0;
   out_6072665348488724658[65] = 0;
   out_6072665348488724658[66] = dt;
   out_6072665348488724658[67] = 0;
   out_6072665348488724658[68] = 0;
   out_6072665348488724658[69] = 0;
   out_6072665348488724658[70] = 0;
   out_6072665348488724658[71] = 0;
   out_6072665348488724658[72] = 0;
   out_6072665348488724658[73] = 0;
   out_6072665348488724658[74] = 0;
   out_6072665348488724658[75] = 0;
   out_6072665348488724658[76] = 1;
   out_6072665348488724658[77] = 0;
   out_6072665348488724658[78] = 0;
   out_6072665348488724658[79] = 0;
   out_6072665348488724658[80] = 0;
   out_6072665348488724658[81] = 0;
   out_6072665348488724658[82] = 0;
   out_6072665348488724658[83] = 0;
   out_6072665348488724658[84] = 0;
   out_6072665348488724658[85] = dt;
   out_6072665348488724658[86] = 0;
   out_6072665348488724658[87] = 0;
   out_6072665348488724658[88] = 0;
   out_6072665348488724658[89] = 0;
   out_6072665348488724658[90] = 0;
   out_6072665348488724658[91] = 0;
   out_6072665348488724658[92] = 0;
   out_6072665348488724658[93] = 0;
   out_6072665348488724658[94] = 0;
   out_6072665348488724658[95] = 1;
   out_6072665348488724658[96] = 0;
   out_6072665348488724658[97] = 0;
   out_6072665348488724658[98] = 0;
   out_6072665348488724658[99] = 0;
   out_6072665348488724658[100] = 0;
   out_6072665348488724658[101] = 0;
   out_6072665348488724658[102] = 0;
   out_6072665348488724658[103] = 0;
   out_6072665348488724658[104] = dt;
   out_6072665348488724658[105] = 0;
   out_6072665348488724658[106] = 0;
   out_6072665348488724658[107] = 0;
   out_6072665348488724658[108] = 0;
   out_6072665348488724658[109] = 0;
   out_6072665348488724658[110] = 0;
   out_6072665348488724658[111] = 0;
   out_6072665348488724658[112] = 0;
   out_6072665348488724658[113] = 0;
   out_6072665348488724658[114] = 1;
   out_6072665348488724658[115] = 0;
   out_6072665348488724658[116] = 0;
   out_6072665348488724658[117] = 0;
   out_6072665348488724658[118] = 0;
   out_6072665348488724658[119] = 0;
   out_6072665348488724658[120] = 0;
   out_6072665348488724658[121] = 0;
   out_6072665348488724658[122] = 0;
   out_6072665348488724658[123] = 0;
   out_6072665348488724658[124] = 0;
   out_6072665348488724658[125] = 0;
   out_6072665348488724658[126] = 0;
   out_6072665348488724658[127] = 0;
   out_6072665348488724658[128] = 0;
   out_6072665348488724658[129] = 0;
   out_6072665348488724658[130] = 0;
   out_6072665348488724658[131] = 0;
   out_6072665348488724658[132] = 0;
   out_6072665348488724658[133] = 1;
   out_6072665348488724658[134] = 0;
   out_6072665348488724658[135] = 0;
   out_6072665348488724658[136] = 0;
   out_6072665348488724658[137] = 0;
   out_6072665348488724658[138] = 0;
   out_6072665348488724658[139] = 0;
   out_6072665348488724658[140] = 0;
   out_6072665348488724658[141] = 0;
   out_6072665348488724658[142] = 0;
   out_6072665348488724658[143] = 0;
   out_6072665348488724658[144] = 0;
   out_6072665348488724658[145] = 0;
   out_6072665348488724658[146] = 0;
   out_6072665348488724658[147] = 0;
   out_6072665348488724658[148] = 0;
   out_6072665348488724658[149] = 0;
   out_6072665348488724658[150] = 0;
   out_6072665348488724658[151] = 0;
   out_6072665348488724658[152] = 1;
   out_6072665348488724658[153] = 0;
   out_6072665348488724658[154] = 0;
   out_6072665348488724658[155] = 0;
   out_6072665348488724658[156] = 0;
   out_6072665348488724658[157] = 0;
   out_6072665348488724658[158] = 0;
   out_6072665348488724658[159] = 0;
   out_6072665348488724658[160] = 0;
   out_6072665348488724658[161] = 0;
   out_6072665348488724658[162] = 0;
   out_6072665348488724658[163] = 0;
   out_6072665348488724658[164] = 0;
   out_6072665348488724658[165] = 0;
   out_6072665348488724658[166] = 0;
   out_6072665348488724658[167] = 0;
   out_6072665348488724658[168] = 0;
   out_6072665348488724658[169] = 0;
   out_6072665348488724658[170] = 0;
   out_6072665348488724658[171] = 1;
   out_6072665348488724658[172] = 0;
   out_6072665348488724658[173] = 0;
   out_6072665348488724658[174] = 0;
   out_6072665348488724658[175] = 0;
   out_6072665348488724658[176] = 0;
   out_6072665348488724658[177] = 0;
   out_6072665348488724658[178] = 0;
   out_6072665348488724658[179] = 0;
   out_6072665348488724658[180] = 0;
   out_6072665348488724658[181] = 0;
   out_6072665348488724658[182] = 0;
   out_6072665348488724658[183] = 0;
   out_6072665348488724658[184] = 0;
   out_6072665348488724658[185] = 0;
   out_6072665348488724658[186] = 0;
   out_6072665348488724658[187] = 0;
   out_6072665348488724658[188] = 0;
   out_6072665348488724658[189] = 0;
   out_6072665348488724658[190] = 1;
   out_6072665348488724658[191] = 0;
   out_6072665348488724658[192] = 0;
   out_6072665348488724658[193] = 0;
   out_6072665348488724658[194] = 0;
   out_6072665348488724658[195] = 0;
   out_6072665348488724658[196] = 0;
   out_6072665348488724658[197] = 0;
   out_6072665348488724658[198] = 0;
   out_6072665348488724658[199] = 0;
   out_6072665348488724658[200] = 0;
   out_6072665348488724658[201] = 0;
   out_6072665348488724658[202] = 0;
   out_6072665348488724658[203] = 0;
   out_6072665348488724658[204] = 0;
   out_6072665348488724658[205] = 0;
   out_6072665348488724658[206] = 0;
   out_6072665348488724658[207] = 0;
   out_6072665348488724658[208] = 0;
   out_6072665348488724658[209] = 1;
   out_6072665348488724658[210] = 0;
   out_6072665348488724658[211] = 0;
   out_6072665348488724658[212] = 0;
   out_6072665348488724658[213] = 0;
   out_6072665348488724658[214] = 0;
   out_6072665348488724658[215] = 0;
   out_6072665348488724658[216] = 0;
   out_6072665348488724658[217] = 0;
   out_6072665348488724658[218] = 0;
   out_6072665348488724658[219] = 0;
   out_6072665348488724658[220] = 0;
   out_6072665348488724658[221] = 0;
   out_6072665348488724658[222] = 0;
   out_6072665348488724658[223] = 0;
   out_6072665348488724658[224] = 0;
   out_6072665348488724658[225] = 0;
   out_6072665348488724658[226] = 0;
   out_6072665348488724658[227] = 0;
   out_6072665348488724658[228] = 1;
   out_6072665348488724658[229] = 0;
   out_6072665348488724658[230] = 0;
   out_6072665348488724658[231] = 0;
   out_6072665348488724658[232] = 0;
   out_6072665348488724658[233] = 0;
   out_6072665348488724658[234] = 0;
   out_6072665348488724658[235] = 0;
   out_6072665348488724658[236] = 0;
   out_6072665348488724658[237] = 0;
   out_6072665348488724658[238] = 0;
   out_6072665348488724658[239] = 0;
   out_6072665348488724658[240] = 0;
   out_6072665348488724658[241] = 0;
   out_6072665348488724658[242] = 0;
   out_6072665348488724658[243] = 0;
   out_6072665348488724658[244] = 0;
   out_6072665348488724658[245] = 0;
   out_6072665348488724658[246] = 0;
   out_6072665348488724658[247] = 1;
   out_6072665348488724658[248] = 0;
   out_6072665348488724658[249] = 0;
   out_6072665348488724658[250] = 0;
   out_6072665348488724658[251] = 0;
   out_6072665348488724658[252] = 0;
   out_6072665348488724658[253] = 0;
   out_6072665348488724658[254] = 0;
   out_6072665348488724658[255] = 0;
   out_6072665348488724658[256] = 0;
   out_6072665348488724658[257] = 0;
   out_6072665348488724658[258] = 0;
   out_6072665348488724658[259] = 0;
   out_6072665348488724658[260] = 0;
   out_6072665348488724658[261] = 0;
   out_6072665348488724658[262] = 0;
   out_6072665348488724658[263] = 0;
   out_6072665348488724658[264] = 0;
   out_6072665348488724658[265] = 0;
   out_6072665348488724658[266] = 1;
   out_6072665348488724658[267] = 0;
   out_6072665348488724658[268] = 0;
   out_6072665348488724658[269] = 0;
   out_6072665348488724658[270] = 0;
   out_6072665348488724658[271] = 0;
   out_6072665348488724658[272] = 0;
   out_6072665348488724658[273] = 0;
   out_6072665348488724658[274] = 0;
   out_6072665348488724658[275] = 0;
   out_6072665348488724658[276] = 0;
   out_6072665348488724658[277] = 0;
   out_6072665348488724658[278] = 0;
   out_6072665348488724658[279] = 0;
   out_6072665348488724658[280] = 0;
   out_6072665348488724658[281] = 0;
   out_6072665348488724658[282] = 0;
   out_6072665348488724658[283] = 0;
   out_6072665348488724658[284] = 0;
   out_6072665348488724658[285] = 1;
   out_6072665348488724658[286] = 0;
   out_6072665348488724658[287] = 0;
   out_6072665348488724658[288] = 0;
   out_6072665348488724658[289] = 0;
   out_6072665348488724658[290] = 0;
   out_6072665348488724658[291] = 0;
   out_6072665348488724658[292] = 0;
   out_6072665348488724658[293] = 0;
   out_6072665348488724658[294] = 0;
   out_6072665348488724658[295] = 0;
   out_6072665348488724658[296] = 0;
   out_6072665348488724658[297] = 0;
   out_6072665348488724658[298] = 0;
   out_6072665348488724658[299] = 0;
   out_6072665348488724658[300] = 0;
   out_6072665348488724658[301] = 0;
   out_6072665348488724658[302] = 0;
   out_6072665348488724658[303] = 0;
   out_6072665348488724658[304] = 1;
   out_6072665348488724658[305] = 0;
   out_6072665348488724658[306] = 0;
   out_6072665348488724658[307] = 0;
   out_6072665348488724658[308] = 0;
   out_6072665348488724658[309] = 0;
   out_6072665348488724658[310] = 0;
   out_6072665348488724658[311] = 0;
   out_6072665348488724658[312] = 0;
   out_6072665348488724658[313] = 0;
   out_6072665348488724658[314] = 0;
   out_6072665348488724658[315] = 0;
   out_6072665348488724658[316] = 0;
   out_6072665348488724658[317] = 0;
   out_6072665348488724658[318] = 0;
   out_6072665348488724658[319] = 0;
   out_6072665348488724658[320] = 0;
   out_6072665348488724658[321] = 0;
   out_6072665348488724658[322] = 0;
   out_6072665348488724658[323] = 1;
}
void h_4(double *state, double *unused, double *out_5129599059026555347) {
   out_5129599059026555347[0] = state[6] + state[9];
   out_5129599059026555347[1] = state[7] + state[10];
   out_5129599059026555347[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1186622101796083626) {
   out_1186622101796083626[0] = 0;
   out_1186622101796083626[1] = 0;
   out_1186622101796083626[2] = 0;
   out_1186622101796083626[3] = 0;
   out_1186622101796083626[4] = 0;
   out_1186622101796083626[5] = 0;
   out_1186622101796083626[6] = 1;
   out_1186622101796083626[7] = 0;
   out_1186622101796083626[8] = 0;
   out_1186622101796083626[9] = 1;
   out_1186622101796083626[10] = 0;
   out_1186622101796083626[11] = 0;
   out_1186622101796083626[12] = 0;
   out_1186622101796083626[13] = 0;
   out_1186622101796083626[14] = 0;
   out_1186622101796083626[15] = 0;
   out_1186622101796083626[16] = 0;
   out_1186622101796083626[17] = 0;
   out_1186622101796083626[18] = 0;
   out_1186622101796083626[19] = 0;
   out_1186622101796083626[20] = 0;
   out_1186622101796083626[21] = 0;
   out_1186622101796083626[22] = 0;
   out_1186622101796083626[23] = 0;
   out_1186622101796083626[24] = 0;
   out_1186622101796083626[25] = 1;
   out_1186622101796083626[26] = 0;
   out_1186622101796083626[27] = 0;
   out_1186622101796083626[28] = 1;
   out_1186622101796083626[29] = 0;
   out_1186622101796083626[30] = 0;
   out_1186622101796083626[31] = 0;
   out_1186622101796083626[32] = 0;
   out_1186622101796083626[33] = 0;
   out_1186622101796083626[34] = 0;
   out_1186622101796083626[35] = 0;
   out_1186622101796083626[36] = 0;
   out_1186622101796083626[37] = 0;
   out_1186622101796083626[38] = 0;
   out_1186622101796083626[39] = 0;
   out_1186622101796083626[40] = 0;
   out_1186622101796083626[41] = 0;
   out_1186622101796083626[42] = 0;
   out_1186622101796083626[43] = 0;
   out_1186622101796083626[44] = 1;
   out_1186622101796083626[45] = 0;
   out_1186622101796083626[46] = 0;
   out_1186622101796083626[47] = 1;
   out_1186622101796083626[48] = 0;
   out_1186622101796083626[49] = 0;
   out_1186622101796083626[50] = 0;
   out_1186622101796083626[51] = 0;
   out_1186622101796083626[52] = 0;
   out_1186622101796083626[53] = 0;
}
void h_10(double *state, double *unused, double *out_2152379920042166610) {
   out_2152379920042166610[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2152379920042166610[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2152379920042166610[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7082902188437509539) {
   out_7082902188437509539[0] = 0;
   out_7082902188437509539[1] = 9.8100000000000005*cos(state[1]);
   out_7082902188437509539[2] = 0;
   out_7082902188437509539[3] = 0;
   out_7082902188437509539[4] = -state[8];
   out_7082902188437509539[5] = state[7];
   out_7082902188437509539[6] = 0;
   out_7082902188437509539[7] = state[5];
   out_7082902188437509539[8] = -state[4];
   out_7082902188437509539[9] = 0;
   out_7082902188437509539[10] = 0;
   out_7082902188437509539[11] = 0;
   out_7082902188437509539[12] = 1;
   out_7082902188437509539[13] = 0;
   out_7082902188437509539[14] = 0;
   out_7082902188437509539[15] = 1;
   out_7082902188437509539[16] = 0;
   out_7082902188437509539[17] = 0;
   out_7082902188437509539[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7082902188437509539[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7082902188437509539[20] = 0;
   out_7082902188437509539[21] = state[8];
   out_7082902188437509539[22] = 0;
   out_7082902188437509539[23] = -state[6];
   out_7082902188437509539[24] = -state[5];
   out_7082902188437509539[25] = 0;
   out_7082902188437509539[26] = state[3];
   out_7082902188437509539[27] = 0;
   out_7082902188437509539[28] = 0;
   out_7082902188437509539[29] = 0;
   out_7082902188437509539[30] = 0;
   out_7082902188437509539[31] = 1;
   out_7082902188437509539[32] = 0;
   out_7082902188437509539[33] = 0;
   out_7082902188437509539[34] = 1;
   out_7082902188437509539[35] = 0;
   out_7082902188437509539[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7082902188437509539[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7082902188437509539[38] = 0;
   out_7082902188437509539[39] = -state[7];
   out_7082902188437509539[40] = state[6];
   out_7082902188437509539[41] = 0;
   out_7082902188437509539[42] = state[4];
   out_7082902188437509539[43] = -state[3];
   out_7082902188437509539[44] = 0;
   out_7082902188437509539[45] = 0;
   out_7082902188437509539[46] = 0;
   out_7082902188437509539[47] = 0;
   out_7082902188437509539[48] = 0;
   out_7082902188437509539[49] = 0;
   out_7082902188437509539[50] = 1;
   out_7082902188437509539[51] = 0;
   out_7082902188437509539[52] = 0;
   out_7082902188437509539[53] = 1;
}
void h_13(double *state, double *unused, double *out_5324920967497513574) {
   out_5324920967497513574[0] = state[3];
   out_5324920967497513574[1] = state[4];
   out_5324920967497513574[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2025651723536249175) {
   out_2025651723536249175[0] = 0;
   out_2025651723536249175[1] = 0;
   out_2025651723536249175[2] = 0;
   out_2025651723536249175[3] = 1;
   out_2025651723536249175[4] = 0;
   out_2025651723536249175[5] = 0;
   out_2025651723536249175[6] = 0;
   out_2025651723536249175[7] = 0;
   out_2025651723536249175[8] = 0;
   out_2025651723536249175[9] = 0;
   out_2025651723536249175[10] = 0;
   out_2025651723536249175[11] = 0;
   out_2025651723536249175[12] = 0;
   out_2025651723536249175[13] = 0;
   out_2025651723536249175[14] = 0;
   out_2025651723536249175[15] = 0;
   out_2025651723536249175[16] = 0;
   out_2025651723536249175[17] = 0;
   out_2025651723536249175[18] = 0;
   out_2025651723536249175[19] = 0;
   out_2025651723536249175[20] = 0;
   out_2025651723536249175[21] = 0;
   out_2025651723536249175[22] = 1;
   out_2025651723536249175[23] = 0;
   out_2025651723536249175[24] = 0;
   out_2025651723536249175[25] = 0;
   out_2025651723536249175[26] = 0;
   out_2025651723536249175[27] = 0;
   out_2025651723536249175[28] = 0;
   out_2025651723536249175[29] = 0;
   out_2025651723536249175[30] = 0;
   out_2025651723536249175[31] = 0;
   out_2025651723536249175[32] = 0;
   out_2025651723536249175[33] = 0;
   out_2025651723536249175[34] = 0;
   out_2025651723536249175[35] = 0;
   out_2025651723536249175[36] = 0;
   out_2025651723536249175[37] = 0;
   out_2025651723536249175[38] = 0;
   out_2025651723536249175[39] = 0;
   out_2025651723536249175[40] = 0;
   out_2025651723536249175[41] = 1;
   out_2025651723536249175[42] = 0;
   out_2025651723536249175[43] = 0;
   out_2025651723536249175[44] = 0;
   out_2025651723536249175[45] = 0;
   out_2025651723536249175[46] = 0;
   out_2025651723536249175[47] = 0;
   out_2025651723536249175[48] = 0;
   out_2025651723536249175[49] = 0;
   out_2025651723536249175[50] = 0;
   out_2025651723536249175[51] = 0;
   out_2025651723536249175[52] = 0;
   out_2025651723536249175[53] = 0;
}
void h_14(double *state, double *unused, double *out_7200680157934561322) {
   out_7200680157934561322[0] = state[6];
   out_7200680157934561322[1] = state[7];
   out_7200680157934561322[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4269410534091455922) {
   out_4269410534091455922[0] = 0;
   out_4269410534091455922[1] = 0;
   out_4269410534091455922[2] = 0;
   out_4269410534091455922[3] = 0;
   out_4269410534091455922[4] = 0;
   out_4269410534091455922[5] = 0;
   out_4269410534091455922[6] = 1;
   out_4269410534091455922[7] = 0;
   out_4269410534091455922[8] = 0;
   out_4269410534091455922[9] = 0;
   out_4269410534091455922[10] = 0;
   out_4269410534091455922[11] = 0;
   out_4269410534091455922[12] = 0;
   out_4269410534091455922[13] = 0;
   out_4269410534091455922[14] = 0;
   out_4269410534091455922[15] = 0;
   out_4269410534091455922[16] = 0;
   out_4269410534091455922[17] = 0;
   out_4269410534091455922[18] = 0;
   out_4269410534091455922[19] = 0;
   out_4269410534091455922[20] = 0;
   out_4269410534091455922[21] = 0;
   out_4269410534091455922[22] = 0;
   out_4269410534091455922[23] = 0;
   out_4269410534091455922[24] = 0;
   out_4269410534091455922[25] = 1;
   out_4269410534091455922[26] = 0;
   out_4269410534091455922[27] = 0;
   out_4269410534091455922[28] = 0;
   out_4269410534091455922[29] = 0;
   out_4269410534091455922[30] = 0;
   out_4269410534091455922[31] = 0;
   out_4269410534091455922[32] = 0;
   out_4269410534091455922[33] = 0;
   out_4269410534091455922[34] = 0;
   out_4269410534091455922[35] = 0;
   out_4269410534091455922[36] = 0;
   out_4269410534091455922[37] = 0;
   out_4269410534091455922[38] = 0;
   out_4269410534091455922[39] = 0;
   out_4269410534091455922[40] = 0;
   out_4269410534091455922[41] = 0;
   out_4269410534091455922[42] = 0;
   out_4269410534091455922[43] = 0;
   out_4269410534091455922[44] = 1;
   out_4269410534091455922[45] = 0;
   out_4269410534091455922[46] = 0;
   out_4269410534091455922[47] = 0;
   out_4269410534091455922[48] = 0;
   out_4269410534091455922[49] = 0;
   out_4269410534091455922[50] = 0;
   out_4269410534091455922[51] = 0;
   out_4269410534091455922[52] = 0;
   out_4269410534091455922[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6405940408767953849) {
  err_fun(nom_x, delta_x, out_6405940408767953849);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8262227002071130515) {
  inv_err_fun(nom_x, true_x, out_8262227002071130515);
}
void pose_H_mod_fun(double *state, double *out_4958429311639991198) {
  H_mod_fun(state, out_4958429311639991198);
}
void pose_f_fun(double *state, double dt, double *out_6795570829506520409) {
  f_fun(state,  dt, out_6795570829506520409);
}
void pose_F_fun(double *state, double dt, double *out_6072665348488724658) {
  F_fun(state,  dt, out_6072665348488724658);
}
void pose_h_4(double *state, double *unused, double *out_5129599059026555347) {
  h_4(state, unused, out_5129599059026555347);
}
void pose_H_4(double *state, double *unused, double *out_1186622101796083626) {
  H_4(state, unused, out_1186622101796083626);
}
void pose_h_10(double *state, double *unused, double *out_2152379920042166610) {
  h_10(state, unused, out_2152379920042166610);
}
void pose_H_10(double *state, double *unused, double *out_7082902188437509539) {
  H_10(state, unused, out_7082902188437509539);
}
void pose_h_13(double *state, double *unused, double *out_5324920967497513574) {
  h_13(state, unused, out_5324920967497513574);
}
void pose_H_13(double *state, double *unused, double *out_2025651723536249175) {
  H_13(state, unused, out_2025651723536249175);
}
void pose_h_14(double *state, double *unused, double *out_7200680157934561322) {
  h_14(state, unused, out_7200680157934561322);
}
void pose_H_14(double *state, double *unused, double *out_4269410534091455922) {
  H_14(state, unused, out_4269410534091455922);
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
