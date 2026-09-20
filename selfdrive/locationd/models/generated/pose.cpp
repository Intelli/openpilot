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
void err_fun(double *nom_x, double *delta_x, double *out_4630147527928263386) {
   out_4630147527928263386[0] = delta_x[0] + nom_x[0];
   out_4630147527928263386[1] = delta_x[1] + nom_x[1];
   out_4630147527928263386[2] = delta_x[2] + nom_x[2];
   out_4630147527928263386[3] = delta_x[3] + nom_x[3];
   out_4630147527928263386[4] = delta_x[4] + nom_x[4];
   out_4630147527928263386[5] = delta_x[5] + nom_x[5];
   out_4630147527928263386[6] = delta_x[6] + nom_x[6];
   out_4630147527928263386[7] = delta_x[7] + nom_x[7];
   out_4630147527928263386[8] = delta_x[8] + nom_x[8];
   out_4630147527928263386[9] = delta_x[9] + nom_x[9];
   out_4630147527928263386[10] = delta_x[10] + nom_x[10];
   out_4630147527928263386[11] = delta_x[11] + nom_x[11];
   out_4630147527928263386[12] = delta_x[12] + nom_x[12];
   out_4630147527928263386[13] = delta_x[13] + nom_x[13];
   out_4630147527928263386[14] = delta_x[14] + nom_x[14];
   out_4630147527928263386[15] = delta_x[15] + nom_x[15];
   out_4630147527928263386[16] = delta_x[16] + nom_x[16];
   out_4630147527928263386[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7264677227800699737) {
   out_7264677227800699737[0] = -nom_x[0] + true_x[0];
   out_7264677227800699737[1] = -nom_x[1] + true_x[1];
   out_7264677227800699737[2] = -nom_x[2] + true_x[2];
   out_7264677227800699737[3] = -nom_x[3] + true_x[3];
   out_7264677227800699737[4] = -nom_x[4] + true_x[4];
   out_7264677227800699737[5] = -nom_x[5] + true_x[5];
   out_7264677227800699737[6] = -nom_x[6] + true_x[6];
   out_7264677227800699737[7] = -nom_x[7] + true_x[7];
   out_7264677227800699737[8] = -nom_x[8] + true_x[8];
   out_7264677227800699737[9] = -nom_x[9] + true_x[9];
   out_7264677227800699737[10] = -nom_x[10] + true_x[10];
   out_7264677227800699737[11] = -nom_x[11] + true_x[11];
   out_7264677227800699737[12] = -nom_x[12] + true_x[12];
   out_7264677227800699737[13] = -nom_x[13] + true_x[13];
   out_7264677227800699737[14] = -nom_x[14] + true_x[14];
   out_7264677227800699737[15] = -nom_x[15] + true_x[15];
   out_7264677227800699737[16] = -nom_x[16] + true_x[16];
   out_7264677227800699737[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5498312016839624203) {
   out_5498312016839624203[0] = 1.0;
   out_5498312016839624203[1] = 0.0;
   out_5498312016839624203[2] = 0.0;
   out_5498312016839624203[3] = 0.0;
   out_5498312016839624203[4] = 0.0;
   out_5498312016839624203[5] = 0.0;
   out_5498312016839624203[6] = 0.0;
   out_5498312016839624203[7] = 0.0;
   out_5498312016839624203[8] = 0.0;
   out_5498312016839624203[9] = 0.0;
   out_5498312016839624203[10] = 0.0;
   out_5498312016839624203[11] = 0.0;
   out_5498312016839624203[12] = 0.0;
   out_5498312016839624203[13] = 0.0;
   out_5498312016839624203[14] = 0.0;
   out_5498312016839624203[15] = 0.0;
   out_5498312016839624203[16] = 0.0;
   out_5498312016839624203[17] = 0.0;
   out_5498312016839624203[18] = 0.0;
   out_5498312016839624203[19] = 1.0;
   out_5498312016839624203[20] = 0.0;
   out_5498312016839624203[21] = 0.0;
   out_5498312016839624203[22] = 0.0;
   out_5498312016839624203[23] = 0.0;
   out_5498312016839624203[24] = 0.0;
   out_5498312016839624203[25] = 0.0;
   out_5498312016839624203[26] = 0.0;
   out_5498312016839624203[27] = 0.0;
   out_5498312016839624203[28] = 0.0;
   out_5498312016839624203[29] = 0.0;
   out_5498312016839624203[30] = 0.0;
   out_5498312016839624203[31] = 0.0;
   out_5498312016839624203[32] = 0.0;
   out_5498312016839624203[33] = 0.0;
   out_5498312016839624203[34] = 0.0;
   out_5498312016839624203[35] = 0.0;
   out_5498312016839624203[36] = 0.0;
   out_5498312016839624203[37] = 0.0;
   out_5498312016839624203[38] = 1.0;
   out_5498312016839624203[39] = 0.0;
   out_5498312016839624203[40] = 0.0;
   out_5498312016839624203[41] = 0.0;
   out_5498312016839624203[42] = 0.0;
   out_5498312016839624203[43] = 0.0;
   out_5498312016839624203[44] = 0.0;
   out_5498312016839624203[45] = 0.0;
   out_5498312016839624203[46] = 0.0;
   out_5498312016839624203[47] = 0.0;
   out_5498312016839624203[48] = 0.0;
   out_5498312016839624203[49] = 0.0;
   out_5498312016839624203[50] = 0.0;
   out_5498312016839624203[51] = 0.0;
   out_5498312016839624203[52] = 0.0;
   out_5498312016839624203[53] = 0.0;
   out_5498312016839624203[54] = 0.0;
   out_5498312016839624203[55] = 0.0;
   out_5498312016839624203[56] = 0.0;
   out_5498312016839624203[57] = 1.0;
   out_5498312016839624203[58] = 0.0;
   out_5498312016839624203[59] = 0.0;
   out_5498312016839624203[60] = 0.0;
   out_5498312016839624203[61] = 0.0;
   out_5498312016839624203[62] = 0.0;
   out_5498312016839624203[63] = 0.0;
   out_5498312016839624203[64] = 0.0;
   out_5498312016839624203[65] = 0.0;
   out_5498312016839624203[66] = 0.0;
   out_5498312016839624203[67] = 0.0;
   out_5498312016839624203[68] = 0.0;
   out_5498312016839624203[69] = 0.0;
   out_5498312016839624203[70] = 0.0;
   out_5498312016839624203[71] = 0.0;
   out_5498312016839624203[72] = 0.0;
   out_5498312016839624203[73] = 0.0;
   out_5498312016839624203[74] = 0.0;
   out_5498312016839624203[75] = 0.0;
   out_5498312016839624203[76] = 1.0;
   out_5498312016839624203[77] = 0.0;
   out_5498312016839624203[78] = 0.0;
   out_5498312016839624203[79] = 0.0;
   out_5498312016839624203[80] = 0.0;
   out_5498312016839624203[81] = 0.0;
   out_5498312016839624203[82] = 0.0;
   out_5498312016839624203[83] = 0.0;
   out_5498312016839624203[84] = 0.0;
   out_5498312016839624203[85] = 0.0;
   out_5498312016839624203[86] = 0.0;
   out_5498312016839624203[87] = 0.0;
   out_5498312016839624203[88] = 0.0;
   out_5498312016839624203[89] = 0.0;
   out_5498312016839624203[90] = 0.0;
   out_5498312016839624203[91] = 0.0;
   out_5498312016839624203[92] = 0.0;
   out_5498312016839624203[93] = 0.0;
   out_5498312016839624203[94] = 0.0;
   out_5498312016839624203[95] = 1.0;
   out_5498312016839624203[96] = 0.0;
   out_5498312016839624203[97] = 0.0;
   out_5498312016839624203[98] = 0.0;
   out_5498312016839624203[99] = 0.0;
   out_5498312016839624203[100] = 0.0;
   out_5498312016839624203[101] = 0.0;
   out_5498312016839624203[102] = 0.0;
   out_5498312016839624203[103] = 0.0;
   out_5498312016839624203[104] = 0.0;
   out_5498312016839624203[105] = 0.0;
   out_5498312016839624203[106] = 0.0;
   out_5498312016839624203[107] = 0.0;
   out_5498312016839624203[108] = 0.0;
   out_5498312016839624203[109] = 0.0;
   out_5498312016839624203[110] = 0.0;
   out_5498312016839624203[111] = 0.0;
   out_5498312016839624203[112] = 0.0;
   out_5498312016839624203[113] = 0.0;
   out_5498312016839624203[114] = 1.0;
   out_5498312016839624203[115] = 0.0;
   out_5498312016839624203[116] = 0.0;
   out_5498312016839624203[117] = 0.0;
   out_5498312016839624203[118] = 0.0;
   out_5498312016839624203[119] = 0.0;
   out_5498312016839624203[120] = 0.0;
   out_5498312016839624203[121] = 0.0;
   out_5498312016839624203[122] = 0.0;
   out_5498312016839624203[123] = 0.0;
   out_5498312016839624203[124] = 0.0;
   out_5498312016839624203[125] = 0.0;
   out_5498312016839624203[126] = 0.0;
   out_5498312016839624203[127] = 0.0;
   out_5498312016839624203[128] = 0.0;
   out_5498312016839624203[129] = 0.0;
   out_5498312016839624203[130] = 0.0;
   out_5498312016839624203[131] = 0.0;
   out_5498312016839624203[132] = 0.0;
   out_5498312016839624203[133] = 1.0;
   out_5498312016839624203[134] = 0.0;
   out_5498312016839624203[135] = 0.0;
   out_5498312016839624203[136] = 0.0;
   out_5498312016839624203[137] = 0.0;
   out_5498312016839624203[138] = 0.0;
   out_5498312016839624203[139] = 0.0;
   out_5498312016839624203[140] = 0.0;
   out_5498312016839624203[141] = 0.0;
   out_5498312016839624203[142] = 0.0;
   out_5498312016839624203[143] = 0.0;
   out_5498312016839624203[144] = 0.0;
   out_5498312016839624203[145] = 0.0;
   out_5498312016839624203[146] = 0.0;
   out_5498312016839624203[147] = 0.0;
   out_5498312016839624203[148] = 0.0;
   out_5498312016839624203[149] = 0.0;
   out_5498312016839624203[150] = 0.0;
   out_5498312016839624203[151] = 0.0;
   out_5498312016839624203[152] = 1.0;
   out_5498312016839624203[153] = 0.0;
   out_5498312016839624203[154] = 0.0;
   out_5498312016839624203[155] = 0.0;
   out_5498312016839624203[156] = 0.0;
   out_5498312016839624203[157] = 0.0;
   out_5498312016839624203[158] = 0.0;
   out_5498312016839624203[159] = 0.0;
   out_5498312016839624203[160] = 0.0;
   out_5498312016839624203[161] = 0.0;
   out_5498312016839624203[162] = 0.0;
   out_5498312016839624203[163] = 0.0;
   out_5498312016839624203[164] = 0.0;
   out_5498312016839624203[165] = 0.0;
   out_5498312016839624203[166] = 0.0;
   out_5498312016839624203[167] = 0.0;
   out_5498312016839624203[168] = 0.0;
   out_5498312016839624203[169] = 0.0;
   out_5498312016839624203[170] = 0.0;
   out_5498312016839624203[171] = 1.0;
   out_5498312016839624203[172] = 0.0;
   out_5498312016839624203[173] = 0.0;
   out_5498312016839624203[174] = 0.0;
   out_5498312016839624203[175] = 0.0;
   out_5498312016839624203[176] = 0.0;
   out_5498312016839624203[177] = 0.0;
   out_5498312016839624203[178] = 0.0;
   out_5498312016839624203[179] = 0.0;
   out_5498312016839624203[180] = 0.0;
   out_5498312016839624203[181] = 0.0;
   out_5498312016839624203[182] = 0.0;
   out_5498312016839624203[183] = 0.0;
   out_5498312016839624203[184] = 0.0;
   out_5498312016839624203[185] = 0.0;
   out_5498312016839624203[186] = 0.0;
   out_5498312016839624203[187] = 0.0;
   out_5498312016839624203[188] = 0.0;
   out_5498312016839624203[189] = 0.0;
   out_5498312016839624203[190] = 1.0;
   out_5498312016839624203[191] = 0.0;
   out_5498312016839624203[192] = 0.0;
   out_5498312016839624203[193] = 0.0;
   out_5498312016839624203[194] = 0.0;
   out_5498312016839624203[195] = 0.0;
   out_5498312016839624203[196] = 0.0;
   out_5498312016839624203[197] = 0.0;
   out_5498312016839624203[198] = 0.0;
   out_5498312016839624203[199] = 0.0;
   out_5498312016839624203[200] = 0.0;
   out_5498312016839624203[201] = 0.0;
   out_5498312016839624203[202] = 0.0;
   out_5498312016839624203[203] = 0.0;
   out_5498312016839624203[204] = 0.0;
   out_5498312016839624203[205] = 0.0;
   out_5498312016839624203[206] = 0.0;
   out_5498312016839624203[207] = 0.0;
   out_5498312016839624203[208] = 0.0;
   out_5498312016839624203[209] = 1.0;
   out_5498312016839624203[210] = 0.0;
   out_5498312016839624203[211] = 0.0;
   out_5498312016839624203[212] = 0.0;
   out_5498312016839624203[213] = 0.0;
   out_5498312016839624203[214] = 0.0;
   out_5498312016839624203[215] = 0.0;
   out_5498312016839624203[216] = 0.0;
   out_5498312016839624203[217] = 0.0;
   out_5498312016839624203[218] = 0.0;
   out_5498312016839624203[219] = 0.0;
   out_5498312016839624203[220] = 0.0;
   out_5498312016839624203[221] = 0.0;
   out_5498312016839624203[222] = 0.0;
   out_5498312016839624203[223] = 0.0;
   out_5498312016839624203[224] = 0.0;
   out_5498312016839624203[225] = 0.0;
   out_5498312016839624203[226] = 0.0;
   out_5498312016839624203[227] = 0.0;
   out_5498312016839624203[228] = 1.0;
   out_5498312016839624203[229] = 0.0;
   out_5498312016839624203[230] = 0.0;
   out_5498312016839624203[231] = 0.0;
   out_5498312016839624203[232] = 0.0;
   out_5498312016839624203[233] = 0.0;
   out_5498312016839624203[234] = 0.0;
   out_5498312016839624203[235] = 0.0;
   out_5498312016839624203[236] = 0.0;
   out_5498312016839624203[237] = 0.0;
   out_5498312016839624203[238] = 0.0;
   out_5498312016839624203[239] = 0.0;
   out_5498312016839624203[240] = 0.0;
   out_5498312016839624203[241] = 0.0;
   out_5498312016839624203[242] = 0.0;
   out_5498312016839624203[243] = 0.0;
   out_5498312016839624203[244] = 0.0;
   out_5498312016839624203[245] = 0.0;
   out_5498312016839624203[246] = 0.0;
   out_5498312016839624203[247] = 1.0;
   out_5498312016839624203[248] = 0.0;
   out_5498312016839624203[249] = 0.0;
   out_5498312016839624203[250] = 0.0;
   out_5498312016839624203[251] = 0.0;
   out_5498312016839624203[252] = 0.0;
   out_5498312016839624203[253] = 0.0;
   out_5498312016839624203[254] = 0.0;
   out_5498312016839624203[255] = 0.0;
   out_5498312016839624203[256] = 0.0;
   out_5498312016839624203[257] = 0.0;
   out_5498312016839624203[258] = 0.0;
   out_5498312016839624203[259] = 0.0;
   out_5498312016839624203[260] = 0.0;
   out_5498312016839624203[261] = 0.0;
   out_5498312016839624203[262] = 0.0;
   out_5498312016839624203[263] = 0.0;
   out_5498312016839624203[264] = 0.0;
   out_5498312016839624203[265] = 0.0;
   out_5498312016839624203[266] = 1.0;
   out_5498312016839624203[267] = 0.0;
   out_5498312016839624203[268] = 0.0;
   out_5498312016839624203[269] = 0.0;
   out_5498312016839624203[270] = 0.0;
   out_5498312016839624203[271] = 0.0;
   out_5498312016839624203[272] = 0.0;
   out_5498312016839624203[273] = 0.0;
   out_5498312016839624203[274] = 0.0;
   out_5498312016839624203[275] = 0.0;
   out_5498312016839624203[276] = 0.0;
   out_5498312016839624203[277] = 0.0;
   out_5498312016839624203[278] = 0.0;
   out_5498312016839624203[279] = 0.0;
   out_5498312016839624203[280] = 0.0;
   out_5498312016839624203[281] = 0.0;
   out_5498312016839624203[282] = 0.0;
   out_5498312016839624203[283] = 0.0;
   out_5498312016839624203[284] = 0.0;
   out_5498312016839624203[285] = 1.0;
   out_5498312016839624203[286] = 0.0;
   out_5498312016839624203[287] = 0.0;
   out_5498312016839624203[288] = 0.0;
   out_5498312016839624203[289] = 0.0;
   out_5498312016839624203[290] = 0.0;
   out_5498312016839624203[291] = 0.0;
   out_5498312016839624203[292] = 0.0;
   out_5498312016839624203[293] = 0.0;
   out_5498312016839624203[294] = 0.0;
   out_5498312016839624203[295] = 0.0;
   out_5498312016839624203[296] = 0.0;
   out_5498312016839624203[297] = 0.0;
   out_5498312016839624203[298] = 0.0;
   out_5498312016839624203[299] = 0.0;
   out_5498312016839624203[300] = 0.0;
   out_5498312016839624203[301] = 0.0;
   out_5498312016839624203[302] = 0.0;
   out_5498312016839624203[303] = 0.0;
   out_5498312016839624203[304] = 1.0;
   out_5498312016839624203[305] = 0.0;
   out_5498312016839624203[306] = 0.0;
   out_5498312016839624203[307] = 0.0;
   out_5498312016839624203[308] = 0.0;
   out_5498312016839624203[309] = 0.0;
   out_5498312016839624203[310] = 0.0;
   out_5498312016839624203[311] = 0.0;
   out_5498312016839624203[312] = 0.0;
   out_5498312016839624203[313] = 0.0;
   out_5498312016839624203[314] = 0.0;
   out_5498312016839624203[315] = 0.0;
   out_5498312016839624203[316] = 0.0;
   out_5498312016839624203[317] = 0.0;
   out_5498312016839624203[318] = 0.0;
   out_5498312016839624203[319] = 0.0;
   out_5498312016839624203[320] = 0.0;
   out_5498312016839624203[321] = 0.0;
   out_5498312016839624203[322] = 0.0;
   out_5498312016839624203[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8948155690063379520) {
   out_8948155690063379520[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8948155690063379520[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8948155690063379520[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8948155690063379520[3] = dt*state[12] + state[3];
   out_8948155690063379520[4] = dt*state[13] + state[4];
   out_8948155690063379520[5] = dt*state[14] + state[5];
   out_8948155690063379520[6] = state[6];
   out_8948155690063379520[7] = state[7];
   out_8948155690063379520[8] = state[8];
   out_8948155690063379520[9] = state[9];
   out_8948155690063379520[10] = state[10];
   out_8948155690063379520[11] = state[11];
   out_8948155690063379520[12] = state[12];
   out_8948155690063379520[13] = state[13];
   out_8948155690063379520[14] = state[14];
   out_8948155690063379520[15] = state[15];
   out_8948155690063379520[16] = state[16];
   out_8948155690063379520[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4354584664413358096) {
   out_4354584664413358096[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4354584664413358096[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4354584664413358096[2] = 0;
   out_4354584664413358096[3] = 0;
   out_4354584664413358096[4] = 0;
   out_4354584664413358096[5] = 0;
   out_4354584664413358096[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4354584664413358096[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4354584664413358096[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4354584664413358096[9] = 0;
   out_4354584664413358096[10] = 0;
   out_4354584664413358096[11] = 0;
   out_4354584664413358096[12] = 0;
   out_4354584664413358096[13] = 0;
   out_4354584664413358096[14] = 0;
   out_4354584664413358096[15] = 0;
   out_4354584664413358096[16] = 0;
   out_4354584664413358096[17] = 0;
   out_4354584664413358096[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4354584664413358096[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4354584664413358096[20] = 0;
   out_4354584664413358096[21] = 0;
   out_4354584664413358096[22] = 0;
   out_4354584664413358096[23] = 0;
   out_4354584664413358096[24] = 0;
   out_4354584664413358096[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4354584664413358096[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4354584664413358096[27] = 0;
   out_4354584664413358096[28] = 0;
   out_4354584664413358096[29] = 0;
   out_4354584664413358096[30] = 0;
   out_4354584664413358096[31] = 0;
   out_4354584664413358096[32] = 0;
   out_4354584664413358096[33] = 0;
   out_4354584664413358096[34] = 0;
   out_4354584664413358096[35] = 0;
   out_4354584664413358096[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4354584664413358096[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4354584664413358096[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4354584664413358096[39] = 0;
   out_4354584664413358096[40] = 0;
   out_4354584664413358096[41] = 0;
   out_4354584664413358096[42] = 0;
   out_4354584664413358096[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4354584664413358096[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4354584664413358096[45] = 0;
   out_4354584664413358096[46] = 0;
   out_4354584664413358096[47] = 0;
   out_4354584664413358096[48] = 0;
   out_4354584664413358096[49] = 0;
   out_4354584664413358096[50] = 0;
   out_4354584664413358096[51] = 0;
   out_4354584664413358096[52] = 0;
   out_4354584664413358096[53] = 0;
   out_4354584664413358096[54] = 0;
   out_4354584664413358096[55] = 0;
   out_4354584664413358096[56] = 0;
   out_4354584664413358096[57] = 1;
   out_4354584664413358096[58] = 0;
   out_4354584664413358096[59] = 0;
   out_4354584664413358096[60] = 0;
   out_4354584664413358096[61] = 0;
   out_4354584664413358096[62] = 0;
   out_4354584664413358096[63] = 0;
   out_4354584664413358096[64] = 0;
   out_4354584664413358096[65] = 0;
   out_4354584664413358096[66] = dt;
   out_4354584664413358096[67] = 0;
   out_4354584664413358096[68] = 0;
   out_4354584664413358096[69] = 0;
   out_4354584664413358096[70] = 0;
   out_4354584664413358096[71] = 0;
   out_4354584664413358096[72] = 0;
   out_4354584664413358096[73] = 0;
   out_4354584664413358096[74] = 0;
   out_4354584664413358096[75] = 0;
   out_4354584664413358096[76] = 1;
   out_4354584664413358096[77] = 0;
   out_4354584664413358096[78] = 0;
   out_4354584664413358096[79] = 0;
   out_4354584664413358096[80] = 0;
   out_4354584664413358096[81] = 0;
   out_4354584664413358096[82] = 0;
   out_4354584664413358096[83] = 0;
   out_4354584664413358096[84] = 0;
   out_4354584664413358096[85] = dt;
   out_4354584664413358096[86] = 0;
   out_4354584664413358096[87] = 0;
   out_4354584664413358096[88] = 0;
   out_4354584664413358096[89] = 0;
   out_4354584664413358096[90] = 0;
   out_4354584664413358096[91] = 0;
   out_4354584664413358096[92] = 0;
   out_4354584664413358096[93] = 0;
   out_4354584664413358096[94] = 0;
   out_4354584664413358096[95] = 1;
   out_4354584664413358096[96] = 0;
   out_4354584664413358096[97] = 0;
   out_4354584664413358096[98] = 0;
   out_4354584664413358096[99] = 0;
   out_4354584664413358096[100] = 0;
   out_4354584664413358096[101] = 0;
   out_4354584664413358096[102] = 0;
   out_4354584664413358096[103] = 0;
   out_4354584664413358096[104] = dt;
   out_4354584664413358096[105] = 0;
   out_4354584664413358096[106] = 0;
   out_4354584664413358096[107] = 0;
   out_4354584664413358096[108] = 0;
   out_4354584664413358096[109] = 0;
   out_4354584664413358096[110] = 0;
   out_4354584664413358096[111] = 0;
   out_4354584664413358096[112] = 0;
   out_4354584664413358096[113] = 0;
   out_4354584664413358096[114] = 1;
   out_4354584664413358096[115] = 0;
   out_4354584664413358096[116] = 0;
   out_4354584664413358096[117] = 0;
   out_4354584664413358096[118] = 0;
   out_4354584664413358096[119] = 0;
   out_4354584664413358096[120] = 0;
   out_4354584664413358096[121] = 0;
   out_4354584664413358096[122] = 0;
   out_4354584664413358096[123] = 0;
   out_4354584664413358096[124] = 0;
   out_4354584664413358096[125] = 0;
   out_4354584664413358096[126] = 0;
   out_4354584664413358096[127] = 0;
   out_4354584664413358096[128] = 0;
   out_4354584664413358096[129] = 0;
   out_4354584664413358096[130] = 0;
   out_4354584664413358096[131] = 0;
   out_4354584664413358096[132] = 0;
   out_4354584664413358096[133] = 1;
   out_4354584664413358096[134] = 0;
   out_4354584664413358096[135] = 0;
   out_4354584664413358096[136] = 0;
   out_4354584664413358096[137] = 0;
   out_4354584664413358096[138] = 0;
   out_4354584664413358096[139] = 0;
   out_4354584664413358096[140] = 0;
   out_4354584664413358096[141] = 0;
   out_4354584664413358096[142] = 0;
   out_4354584664413358096[143] = 0;
   out_4354584664413358096[144] = 0;
   out_4354584664413358096[145] = 0;
   out_4354584664413358096[146] = 0;
   out_4354584664413358096[147] = 0;
   out_4354584664413358096[148] = 0;
   out_4354584664413358096[149] = 0;
   out_4354584664413358096[150] = 0;
   out_4354584664413358096[151] = 0;
   out_4354584664413358096[152] = 1;
   out_4354584664413358096[153] = 0;
   out_4354584664413358096[154] = 0;
   out_4354584664413358096[155] = 0;
   out_4354584664413358096[156] = 0;
   out_4354584664413358096[157] = 0;
   out_4354584664413358096[158] = 0;
   out_4354584664413358096[159] = 0;
   out_4354584664413358096[160] = 0;
   out_4354584664413358096[161] = 0;
   out_4354584664413358096[162] = 0;
   out_4354584664413358096[163] = 0;
   out_4354584664413358096[164] = 0;
   out_4354584664413358096[165] = 0;
   out_4354584664413358096[166] = 0;
   out_4354584664413358096[167] = 0;
   out_4354584664413358096[168] = 0;
   out_4354584664413358096[169] = 0;
   out_4354584664413358096[170] = 0;
   out_4354584664413358096[171] = 1;
   out_4354584664413358096[172] = 0;
   out_4354584664413358096[173] = 0;
   out_4354584664413358096[174] = 0;
   out_4354584664413358096[175] = 0;
   out_4354584664413358096[176] = 0;
   out_4354584664413358096[177] = 0;
   out_4354584664413358096[178] = 0;
   out_4354584664413358096[179] = 0;
   out_4354584664413358096[180] = 0;
   out_4354584664413358096[181] = 0;
   out_4354584664413358096[182] = 0;
   out_4354584664413358096[183] = 0;
   out_4354584664413358096[184] = 0;
   out_4354584664413358096[185] = 0;
   out_4354584664413358096[186] = 0;
   out_4354584664413358096[187] = 0;
   out_4354584664413358096[188] = 0;
   out_4354584664413358096[189] = 0;
   out_4354584664413358096[190] = 1;
   out_4354584664413358096[191] = 0;
   out_4354584664413358096[192] = 0;
   out_4354584664413358096[193] = 0;
   out_4354584664413358096[194] = 0;
   out_4354584664413358096[195] = 0;
   out_4354584664413358096[196] = 0;
   out_4354584664413358096[197] = 0;
   out_4354584664413358096[198] = 0;
   out_4354584664413358096[199] = 0;
   out_4354584664413358096[200] = 0;
   out_4354584664413358096[201] = 0;
   out_4354584664413358096[202] = 0;
   out_4354584664413358096[203] = 0;
   out_4354584664413358096[204] = 0;
   out_4354584664413358096[205] = 0;
   out_4354584664413358096[206] = 0;
   out_4354584664413358096[207] = 0;
   out_4354584664413358096[208] = 0;
   out_4354584664413358096[209] = 1;
   out_4354584664413358096[210] = 0;
   out_4354584664413358096[211] = 0;
   out_4354584664413358096[212] = 0;
   out_4354584664413358096[213] = 0;
   out_4354584664413358096[214] = 0;
   out_4354584664413358096[215] = 0;
   out_4354584664413358096[216] = 0;
   out_4354584664413358096[217] = 0;
   out_4354584664413358096[218] = 0;
   out_4354584664413358096[219] = 0;
   out_4354584664413358096[220] = 0;
   out_4354584664413358096[221] = 0;
   out_4354584664413358096[222] = 0;
   out_4354584664413358096[223] = 0;
   out_4354584664413358096[224] = 0;
   out_4354584664413358096[225] = 0;
   out_4354584664413358096[226] = 0;
   out_4354584664413358096[227] = 0;
   out_4354584664413358096[228] = 1;
   out_4354584664413358096[229] = 0;
   out_4354584664413358096[230] = 0;
   out_4354584664413358096[231] = 0;
   out_4354584664413358096[232] = 0;
   out_4354584664413358096[233] = 0;
   out_4354584664413358096[234] = 0;
   out_4354584664413358096[235] = 0;
   out_4354584664413358096[236] = 0;
   out_4354584664413358096[237] = 0;
   out_4354584664413358096[238] = 0;
   out_4354584664413358096[239] = 0;
   out_4354584664413358096[240] = 0;
   out_4354584664413358096[241] = 0;
   out_4354584664413358096[242] = 0;
   out_4354584664413358096[243] = 0;
   out_4354584664413358096[244] = 0;
   out_4354584664413358096[245] = 0;
   out_4354584664413358096[246] = 0;
   out_4354584664413358096[247] = 1;
   out_4354584664413358096[248] = 0;
   out_4354584664413358096[249] = 0;
   out_4354584664413358096[250] = 0;
   out_4354584664413358096[251] = 0;
   out_4354584664413358096[252] = 0;
   out_4354584664413358096[253] = 0;
   out_4354584664413358096[254] = 0;
   out_4354584664413358096[255] = 0;
   out_4354584664413358096[256] = 0;
   out_4354584664413358096[257] = 0;
   out_4354584664413358096[258] = 0;
   out_4354584664413358096[259] = 0;
   out_4354584664413358096[260] = 0;
   out_4354584664413358096[261] = 0;
   out_4354584664413358096[262] = 0;
   out_4354584664413358096[263] = 0;
   out_4354584664413358096[264] = 0;
   out_4354584664413358096[265] = 0;
   out_4354584664413358096[266] = 1;
   out_4354584664413358096[267] = 0;
   out_4354584664413358096[268] = 0;
   out_4354584664413358096[269] = 0;
   out_4354584664413358096[270] = 0;
   out_4354584664413358096[271] = 0;
   out_4354584664413358096[272] = 0;
   out_4354584664413358096[273] = 0;
   out_4354584664413358096[274] = 0;
   out_4354584664413358096[275] = 0;
   out_4354584664413358096[276] = 0;
   out_4354584664413358096[277] = 0;
   out_4354584664413358096[278] = 0;
   out_4354584664413358096[279] = 0;
   out_4354584664413358096[280] = 0;
   out_4354584664413358096[281] = 0;
   out_4354584664413358096[282] = 0;
   out_4354584664413358096[283] = 0;
   out_4354584664413358096[284] = 0;
   out_4354584664413358096[285] = 1;
   out_4354584664413358096[286] = 0;
   out_4354584664413358096[287] = 0;
   out_4354584664413358096[288] = 0;
   out_4354584664413358096[289] = 0;
   out_4354584664413358096[290] = 0;
   out_4354584664413358096[291] = 0;
   out_4354584664413358096[292] = 0;
   out_4354584664413358096[293] = 0;
   out_4354584664413358096[294] = 0;
   out_4354584664413358096[295] = 0;
   out_4354584664413358096[296] = 0;
   out_4354584664413358096[297] = 0;
   out_4354584664413358096[298] = 0;
   out_4354584664413358096[299] = 0;
   out_4354584664413358096[300] = 0;
   out_4354584664413358096[301] = 0;
   out_4354584664413358096[302] = 0;
   out_4354584664413358096[303] = 0;
   out_4354584664413358096[304] = 1;
   out_4354584664413358096[305] = 0;
   out_4354584664413358096[306] = 0;
   out_4354584664413358096[307] = 0;
   out_4354584664413358096[308] = 0;
   out_4354584664413358096[309] = 0;
   out_4354584664413358096[310] = 0;
   out_4354584664413358096[311] = 0;
   out_4354584664413358096[312] = 0;
   out_4354584664413358096[313] = 0;
   out_4354584664413358096[314] = 0;
   out_4354584664413358096[315] = 0;
   out_4354584664413358096[316] = 0;
   out_4354584664413358096[317] = 0;
   out_4354584664413358096[318] = 0;
   out_4354584664413358096[319] = 0;
   out_4354584664413358096[320] = 0;
   out_4354584664413358096[321] = 0;
   out_4354584664413358096[322] = 0;
   out_4354584664413358096[323] = 1;
}
void h_4(double *state, double *unused, double *out_3294895423612452149) {
   out_3294895423612452149[0] = state[6] + state[9];
   out_3294895423612452149[1] = state[7] + state[10];
   out_3294895423612452149[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2155467184192811800) {
   out_2155467184192811800[0] = 0;
   out_2155467184192811800[1] = 0;
   out_2155467184192811800[2] = 0;
   out_2155467184192811800[3] = 0;
   out_2155467184192811800[4] = 0;
   out_2155467184192811800[5] = 0;
   out_2155467184192811800[6] = 1;
   out_2155467184192811800[7] = 0;
   out_2155467184192811800[8] = 0;
   out_2155467184192811800[9] = 1;
   out_2155467184192811800[10] = 0;
   out_2155467184192811800[11] = 0;
   out_2155467184192811800[12] = 0;
   out_2155467184192811800[13] = 0;
   out_2155467184192811800[14] = 0;
   out_2155467184192811800[15] = 0;
   out_2155467184192811800[16] = 0;
   out_2155467184192811800[17] = 0;
   out_2155467184192811800[18] = 0;
   out_2155467184192811800[19] = 0;
   out_2155467184192811800[20] = 0;
   out_2155467184192811800[21] = 0;
   out_2155467184192811800[22] = 0;
   out_2155467184192811800[23] = 0;
   out_2155467184192811800[24] = 0;
   out_2155467184192811800[25] = 1;
   out_2155467184192811800[26] = 0;
   out_2155467184192811800[27] = 0;
   out_2155467184192811800[28] = 1;
   out_2155467184192811800[29] = 0;
   out_2155467184192811800[30] = 0;
   out_2155467184192811800[31] = 0;
   out_2155467184192811800[32] = 0;
   out_2155467184192811800[33] = 0;
   out_2155467184192811800[34] = 0;
   out_2155467184192811800[35] = 0;
   out_2155467184192811800[36] = 0;
   out_2155467184192811800[37] = 0;
   out_2155467184192811800[38] = 0;
   out_2155467184192811800[39] = 0;
   out_2155467184192811800[40] = 0;
   out_2155467184192811800[41] = 0;
   out_2155467184192811800[42] = 0;
   out_2155467184192811800[43] = 0;
   out_2155467184192811800[44] = 1;
   out_2155467184192811800[45] = 0;
   out_2155467184192811800[46] = 0;
   out_2155467184192811800[47] = 1;
   out_2155467184192811800[48] = 0;
   out_2155467184192811800[49] = 0;
   out_2155467184192811800[50] = 0;
   out_2155467184192811800[51] = 0;
   out_2155467184192811800[52] = 0;
   out_2155467184192811800[53] = 0;
}
void h_10(double *state, double *unused, double *out_189283368100710860) {
   out_189283368100710860[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_189283368100710860[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_189283368100710860[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3614963382677852821) {
   out_3614963382677852821[0] = 0;
   out_3614963382677852821[1] = 9.8100000000000005*cos(state[1]);
   out_3614963382677852821[2] = 0;
   out_3614963382677852821[3] = 0;
   out_3614963382677852821[4] = -state[8];
   out_3614963382677852821[5] = state[7];
   out_3614963382677852821[6] = 0;
   out_3614963382677852821[7] = state[5];
   out_3614963382677852821[8] = -state[4];
   out_3614963382677852821[9] = 0;
   out_3614963382677852821[10] = 0;
   out_3614963382677852821[11] = 0;
   out_3614963382677852821[12] = 1;
   out_3614963382677852821[13] = 0;
   out_3614963382677852821[14] = 0;
   out_3614963382677852821[15] = 1;
   out_3614963382677852821[16] = 0;
   out_3614963382677852821[17] = 0;
   out_3614963382677852821[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3614963382677852821[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3614963382677852821[20] = 0;
   out_3614963382677852821[21] = state[8];
   out_3614963382677852821[22] = 0;
   out_3614963382677852821[23] = -state[6];
   out_3614963382677852821[24] = -state[5];
   out_3614963382677852821[25] = 0;
   out_3614963382677852821[26] = state[3];
   out_3614963382677852821[27] = 0;
   out_3614963382677852821[28] = 0;
   out_3614963382677852821[29] = 0;
   out_3614963382677852821[30] = 0;
   out_3614963382677852821[31] = 1;
   out_3614963382677852821[32] = 0;
   out_3614963382677852821[33] = 0;
   out_3614963382677852821[34] = 1;
   out_3614963382677852821[35] = 0;
   out_3614963382677852821[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3614963382677852821[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3614963382677852821[38] = 0;
   out_3614963382677852821[39] = -state[7];
   out_3614963382677852821[40] = state[6];
   out_3614963382677852821[41] = 0;
   out_3614963382677852821[42] = state[4];
   out_3614963382677852821[43] = -state[3];
   out_3614963382677852821[44] = 0;
   out_3614963382677852821[45] = 0;
   out_3614963382677852821[46] = 0;
   out_3614963382677852821[47] = 0;
   out_3614963382677852821[48] = 0;
   out_3614963382677852821[49] = 0;
   out_3614963382677852821[50] = 1;
   out_3614963382677852821[51] = 0;
   out_3614963382677852821[52] = 0;
   out_3614963382677852821[53] = 1;
}
void h_13(double *state, double *unused, double *out_2399824474141319282) {
   out_2399824474141319282[0] = state[3];
   out_2399824474141319282[1] = state[4];
   out_2399824474141319282[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1056806641139521001) {
   out_1056806641139521001[0] = 0;
   out_1056806641139521001[1] = 0;
   out_1056806641139521001[2] = 0;
   out_1056806641139521001[3] = 1;
   out_1056806641139521001[4] = 0;
   out_1056806641139521001[5] = 0;
   out_1056806641139521001[6] = 0;
   out_1056806641139521001[7] = 0;
   out_1056806641139521001[8] = 0;
   out_1056806641139521001[9] = 0;
   out_1056806641139521001[10] = 0;
   out_1056806641139521001[11] = 0;
   out_1056806641139521001[12] = 0;
   out_1056806641139521001[13] = 0;
   out_1056806641139521001[14] = 0;
   out_1056806641139521001[15] = 0;
   out_1056806641139521001[16] = 0;
   out_1056806641139521001[17] = 0;
   out_1056806641139521001[18] = 0;
   out_1056806641139521001[19] = 0;
   out_1056806641139521001[20] = 0;
   out_1056806641139521001[21] = 0;
   out_1056806641139521001[22] = 1;
   out_1056806641139521001[23] = 0;
   out_1056806641139521001[24] = 0;
   out_1056806641139521001[25] = 0;
   out_1056806641139521001[26] = 0;
   out_1056806641139521001[27] = 0;
   out_1056806641139521001[28] = 0;
   out_1056806641139521001[29] = 0;
   out_1056806641139521001[30] = 0;
   out_1056806641139521001[31] = 0;
   out_1056806641139521001[32] = 0;
   out_1056806641139521001[33] = 0;
   out_1056806641139521001[34] = 0;
   out_1056806641139521001[35] = 0;
   out_1056806641139521001[36] = 0;
   out_1056806641139521001[37] = 0;
   out_1056806641139521001[38] = 0;
   out_1056806641139521001[39] = 0;
   out_1056806641139521001[40] = 0;
   out_1056806641139521001[41] = 1;
   out_1056806641139521001[42] = 0;
   out_1056806641139521001[43] = 0;
   out_1056806641139521001[44] = 0;
   out_1056806641139521001[45] = 0;
   out_1056806641139521001[46] = 0;
   out_1056806641139521001[47] = 0;
   out_1056806641139521001[48] = 0;
   out_1056806641139521001[49] = 0;
   out_1056806641139521001[50] = 0;
   out_1056806641139521001[51] = 0;
   out_1056806641139521001[52] = 0;
   out_1056806641139521001[53] = 0;
}
void h_14(double *state, double *unused, double *out_102831174585947121) {
   out_102831174585947121[0] = state[6];
   out_102831174585947121[1] = state[7];
   out_102831174585947121[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8810131074236999392) {
   out_8810131074236999392[0] = 0;
   out_8810131074236999392[1] = 0;
   out_8810131074236999392[2] = 0;
   out_8810131074236999392[3] = 0;
   out_8810131074236999392[4] = 0;
   out_8810131074236999392[5] = 0;
   out_8810131074236999392[6] = 1;
   out_8810131074236999392[7] = 0;
   out_8810131074236999392[8] = 0;
   out_8810131074236999392[9] = 0;
   out_8810131074236999392[10] = 0;
   out_8810131074236999392[11] = 0;
   out_8810131074236999392[12] = 0;
   out_8810131074236999392[13] = 0;
   out_8810131074236999392[14] = 0;
   out_8810131074236999392[15] = 0;
   out_8810131074236999392[16] = 0;
   out_8810131074236999392[17] = 0;
   out_8810131074236999392[18] = 0;
   out_8810131074236999392[19] = 0;
   out_8810131074236999392[20] = 0;
   out_8810131074236999392[21] = 0;
   out_8810131074236999392[22] = 0;
   out_8810131074236999392[23] = 0;
   out_8810131074236999392[24] = 0;
   out_8810131074236999392[25] = 1;
   out_8810131074236999392[26] = 0;
   out_8810131074236999392[27] = 0;
   out_8810131074236999392[28] = 0;
   out_8810131074236999392[29] = 0;
   out_8810131074236999392[30] = 0;
   out_8810131074236999392[31] = 0;
   out_8810131074236999392[32] = 0;
   out_8810131074236999392[33] = 0;
   out_8810131074236999392[34] = 0;
   out_8810131074236999392[35] = 0;
   out_8810131074236999392[36] = 0;
   out_8810131074236999392[37] = 0;
   out_8810131074236999392[38] = 0;
   out_8810131074236999392[39] = 0;
   out_8810131074236999392[40] = 0;
   out_8810131074236999392[41] = 0;
   out_8810131074236999392[42] = 0;
   out_8810131074236999392[43] = 0;
   out_8810131074236999392[44] = 1;
   out_8810131074236999392[45] = 0;
   out_8810131074236999392[46] = 0;
   out_8810131074236999392[47] = 0;
   out_8810131074236999392[48] = 0;
   out_8810131074236999392[49] = 0;
   out_8810131074236999392[50] = 0;
   out_8810131074236999392[51] = 0;
   out_8810131074236999392[52] = 0;
   out_8810131074236999392[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4630147527928263386) {
  err_fun(nom_x, delta_x, out_4630147527928263386);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7264677227800699737) {
  inv_err_fun(nom_x, true_x, out_7264677227800699737);
}
void pose_H_mod_fun(double *state, double *out_5498312016839624203) {
  H_mod_fun(state, out_5498312016839624203);
}
void pose_f_fun(double *state, double dt, double *out_8948155690063379520) {
  f_fun(state,  dt, out_8948155690063379520);
}
void pose_F_fun(double *state, double dt, double *out_4354584664413358096) {
  F_fun(state,  dt, out_4354584664413358096);
}
void pose_h_4(double *state, double *unused, double *out_3294895423612452149) {
  h_4(state, unused, out_3294895423612452149);
}
void pose_H_4(double *state, double *unused, double *out_2155467184192811800) {
  H_4(state, unused, out_2155467184192811800);
}
void pose_h_10(double *state, double *unused, double *out_189283368100710860) {
  h_10(state, unused, out_189283368100710860);
}
void pose_H_10(double *state, double *unused, double *out_3614963382677852821) {
  H_10(state, unused, out_3614963382677852821);
}
void pose_h_13(double *state, double *unused, double *out_2399824474141319282) {
  h_13(state, unused, out_2399824474141319282);
}
void pose_H_13(double *state, double *unused, double *out_1056806641139521001) {
  H_13(state, unused, out_1056806641139521001);
}
void pose_h_14(double *state, double *unused, double *out_102831174585947121) {
  h_14(state, unused, out_102831174585947121);
}
void pose_H_14(double *state, double *unused, double *out_8810131074236999392) {
  H_14(state, unused, out_8810131074236999392);
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
