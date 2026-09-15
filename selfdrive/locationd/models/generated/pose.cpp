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
void err_fun(double *nom_x, double *delta_x, double *out_7318583843401046885) {
   out_7318583843401046885[0] = delta_x[0] + nom_x[0];
   out_7318583843401046885[1] = delta_x[1] + nom_x[1];
   out_7318583843401046885[2] = delta_x[2] + nom_x[2];
   out_7318583843401046885[3] = delta_x[3] + nom_x[3];
   out_7318583843401046885[4] = delta_x[4] + nom_x[4];
   out_7318583843401046885[5] = delta_x[5] + nom_x[5];
   out_7318583843401046885[6] = delta_x[6] + nom_x[6];
   out_7318583843401046885[7] = delta_x[7] + nom_x[7];
   out_7318583843401046885[8] = delta_x[8] + nom_x[8];
   out_7318583843401046885[9] = delta_x[9] + nom_x[9];
   out_7318583843401046885[10] = delta_x[10] + nom_x[10];
   out_7318583843401046885[11] = delta_x[11] + nom_x[11];
   out_7318583843401046885[12] = delta_x[12] + nom_x[12];
   out_7318583843401046885[13] = delta_x[13] + nom_x[13];
   out_7318583843401046885[14] = delta_x[14] + nom_x[14];
   out_7318583843401046885[15] = delta_x[15] + nom_x[15];
   out_7318583843401046885[16] = delta_x[16] + nom_x[16];
   out_7318583843401046885[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8604214068849565205) {
   out_8604214068849565205[0] = -nom_x[0] + true_x[0];
   out_8604214068849565205[1] = -nom_x[1] + true_x[1];
   out_8604214068849565205[2] = -nom_x[2] + true_x[2];
   out_8604214068849565205[3] = -nom_x[3] + true_x[3];
   out_8604214068849565205[4] = -nom_x[4] + true_x[4];
   out_8604214068849565205[5] = -nom_x[5] + true_x[5];
   out_8604214068849565205[6] = -nom_x[6] + true_x[6];
   out_8604214068849565205[7] = -nom_x[7] + true_x[7];
   out_8604214068849565205[8] = -nom_x[8] + true_x[8];
   out_8604214068849565205[9] = -nom_x[9] + true_x[9];
   out_8604214068849565205[10] = -nom_x[10] + true_x[10];
   out_8604214068849565205[11] = -nom_x[11] + true_x[11];
   out_8604214068849565205[12] = -nom_x[12] + true_x[12];
   out_8604214068849565205[13] = -nom_x[13] + true_x[13];
   out_8604214068849565205[14] = -nom_x[14] + true_x[14];
   out_8604214068849565205[15] = -nom_x[15] + true_x[15];
   out_8604214068849565205[16] = -nom_x[16] + true_x[16];
   out_8604214068849565205[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7423581578821108479) {
   out_7423581578821108479[0] = 1.0;
   out_7423581578821108479[1] = 0.0;
   out_7423581578821108479[2] = 0.0;
   out_7423581578821108479[3] = 0.0;
   out_7423581578821108479[4] = 0.0;
   out_7423581578821108479[5] = 0.0;
   out_7423581578821108479[6] = 0.0;
   out_7423581578821108479[7] = 0.0;
   out_7423581578821108479[8] = 0.0;
   out_7423581578821108479[9] = 0.0;
   out_7423581578821108479[10] = 0.0;
   out_7423581578821108479[11] = 0.0;
   out_7423581578821108479[12] = 0.0;
   out_7423581578821108479[13] = 0.0;
   out_7423581578821108479[14] = 0.0;
   out_7423581578821108479[15] = 0.0;
   out_7423581578821108479[16] = 0.0;
   out_7423581578821108479[17] = 0.0;
   out_7423581578821108479[18] = 0.0;
   out_7423581578821108479[19] = 1.0;
   out_7423581578821108479[20] = 0.0;
   out_7423581578821108479[21] = 0.0;
   out_7423581578821108479[22] = 0.0;
   out_7423581578821108479[23] = 0.0;
   out_7423581578821108479[24] = 0.0;
   out_7423581578821108479[25] = 0.0;
   out_7423581578821108479[26] = 0.0;
   out_7423581578821108479[27] = 0.0;
   out_7423581578821108479[28] = 0.0;
   out_7423581578821108479[29] = 0.0;
   out_7423581578821108479[30] = 0.0;
   out_7423581578821108479[31] = 0.0;
   out_7423581578821108479[32] = 0.0;
   out_7423581578821108479[33] = 0.0;
   out_7423581578821108479[34] = 0.0;
   out_7423581578821108479[35] = 0.0;
   out_7423581578821108479[36] = 0.0;
   out_7423581578821108479[37] = 0.0;
   out_7423581578821108479[38] = 1.0;
   out_7423581578821108479[39] = 0.0;
   out_7423581578821108479[40] = 0.0;
   out_7423581578821108479[41] = 0.0;
   out_7423581578821108479[42] = 0.0;
   out_7423581578821108479[43] = 0.0;
   out_7423581578821108479[44] = 0.0;
   out_7423581578821108479[45] = 0.0;
   out_7423581578821108479[46] = 0.0;
   out_7423581578821108479[47] = 0.0;
   out_7423581578821108479[48] = 0.0;
   out_7423581578821108479[49] = 0.0;
   out_7423581578821108479[50] = 0.0;
   out_7423581578821108479[51] = 0.0;
   out_7423581578821108479[52] = 0.0;
   out_7423581578821108479[53] = 0.0;
   out_7423581578821108479[54] = 0.0;
   out_7423581578821108479[55] = 0.0;
   out_7423581578821108479[56] = 0.0;
   out_7423581578821108479[57] = 1.0;
   out_7423581578821108479[58] = 0.0;
   out_7423581578821108479[59] = 0.0;
   out_7423581578821108479[60] = 0.0;
   out_7423581578821108479[61] = 0.0;
   out_7423581578821108479[62] = 0.0;
   out_7423581578821108479[63] = 0.0;
   out_7423581578821108479[64] = 0.0;
   out_7423581578821108479[65] = 0.0;
   out_7423581578821108479[66] = 0.0;
   out_7423581578821108479[67] = 0.0;
   out_7423581578821108479[68] = 0.0;
   out_7423581578821108479[69] = 0.0;
   out_7423581578821108479[70] = 0.0;
   out_7423581578821108479[71] = 0.0;
   out_7423581578821108479[72] = 0.0;
   out_7423581578821108479[73] = 0.0;
   out_7423581578821108479[74] = 0.0;
   out_7423581578821108479[75] = 0.0;
   out_7423581578821108479[76] = 1.0;
   out_7423581578821108479[77] = 0.0;
   out_7423581578821108479[78] = 0.0;
   out_7423581578821108479[79] = 0.0;
   out_7423581578821108479[80] = 0.0;
   out_7423581578821108479[81] = 0.0;
   out_7423581578821108479[82] = 0.0;
   out_7423581578821108479[83] = 0.0;
   out_7423581578821108479[84] = 0.0;
   out_7423581578821108479[85] = 0.0;
   out_7423581578821108479[86] = 0.0;
   out_7423581578821108479[87] = 0.0;
   out_7423581578821108479[88] = 0.0;
   out_7423581578821108479[89] = 0.0;
   out_7423581578821108479[90] = 0.0;
   out_7423581578821108479[91] = 0.0;
   out_7423581578821108479[92] = 0.0;
   out_7423581578821108479[93] = 0.0;
   out_7423581578821108479[94] = 0.0;
   out_7423581578821108479[95] = 1.0;
   out_7423581578821108479[96] = 0.0;
   out_7423581578821108479[97] = 0.0;
   out_7423581578821108479[98] = 0.0;
   out_7423581578821108479[99] = 0.0;
   out_7423581578821108479[100] = 0.0;
   out_7423581578821108479[101] = 0.0;
   out_7423581578821108479[102] = 0.0;
   out_7423581578821108479[103] = 0.0;
   out_7423581578821108479[104] = 0.0;
   out_7423581578821108479[105] = 0.0;
   out_7423581578821108479[106] = 0.0;
   out_7423581578821108479[107] = 0.0;
   out_7423581578821108479[108] = 0.0;
   out_7423581578821108479[109] = 0.0;
   out_7423581578821108479[110] = 0.0;
   out_7423581578821108479[111] = 0.0;
   out_7423581578821108479[112] = 0.0;
   out_7423581578821108479[113] = 0.0;
   out_7423581578821108479[114] = 1.0;
   out_7423581578821108479[115] = 0.0;
   out_7423581578821108479[116] = 0.0;
   out_7423581578821108479[117] = 0.0;
   out_7423581578821108479[118] = 0.0;
   out_7423581578821108479[119] = 0.0;
   out_7423581578821108479[120] = 0.0;
   out_7423581578821108479[121] = 0.0;
   out_7423581578821108479[122] = 0.0;
   out_7423581578821108479[123] = 0.0;
   out_7423581578821108479[124] = 0.0;
   out_7423581578821108479[125] = 0.0;
   out_7423581578821108479[126] = 0.0;
   out_7423581578821108479[127] = 0.0;
   out_7423581578821108479[128] = 0.0;
   out_7423581578821108479[129] = 0.0;
   out_7423581578821108479[130] = 0.0;
   out_7423581578821108479[131] = 0.0;
   out_7423581578821108479[132] = 0.0;
   out_7423581578821108479[133] = 1.0;
   out_7423581578821108479[134] = 0.0;
   out_7423581578821108479[135] = 0.0;
   out_7423581578821108479[136] = 0.0;
   out_7423581578821108479[137] = 0.0;
   out_7423581578821108479[138] = 0.0;
   out_7423581578821108479[139] = 0.0;
   out_7423581578821108479[140] = 0.0;
   out_7423581578821108479[141] = 0.0;
   out_7423581578821108479[142] = 0.0;
   out_7423581578821108479[143] = 0.0;
   out_7423581578821108479[144] = 0.0;
   out_7423581578821108479[145] = 0.0;
   out_7423581578821108479[146] = 0.0;
   out_7423581578821108479[147] = 0.0;
   out_7423581578821108479[148] = 0.0;
   out_7423581578821108479[149] = 0.0;
   out_7423581578821108479[150] = 0.0;
   out_7423581578821108479[151] = 0.0;
   out_7423581578821108479[152] = 1.0;
   out_7423581578821108479[153] = 0.0;
   out_7423581578821108479[154] = 0.0;
   out_7423581578821108479[155] = 0.0;
   out_7423581578821108479[156] = 0.0;
   out_7423581578821108479[157] = 0.0;
   out_7423581578821108479[158] = 0.0;
   out_7423581578821108479[159] = 0.0;
   out_7423581578821108479[160] = 0.0;
   out_7423581578821108479[161] = 0.0;
   out_7423581578821108479[162] = 0.0;
   out_7423581578821108479[163] = 0.0;
   out_7423581578821108479[164] = 0.0;
   out_7423581578821108479[165] = 0.0;
   out_7423581578821108479[166] = 0.0;
   out_7423581578821108479[167] = 0.0;
   out_7423581578821108479[168] = 0.0;
   out_7423581578821108479[169] = 0.0;
   out_7423581578821108479[170] = 0.0;
   out_7423581578821108479[171] = 1.0;
   out_7423581578821108479[172] = 0.0;
   out_7423581578821108479[173] = 0.0;
   out_7423581578821108479[174] = 0.0;
   out_7423581578821108479[175] = 0.0;
   out_7423581578821108479[176] = 0.0;
   out_7423581578821108479[177] = 0.0;
   out_7423581578821108479[178] = 0.0;
   out_7423581578821108479[179] = 0.0;
   out_7423581578821108479[180] = 0.0;
   out_7423581578821108479[181] = 0.0;
   out_7423581578821108479[182] = 0.0;
   out_7423581578821108479[183] = 0.0;
   out_7423581578821108479[184] = 0.0;
   out_7423581578821108479[185] = 0.0;
   out_7423581578821108479[186] = 0.0;
   out_7423581578821108479[187] = 0.0;
   out_7423581578821108479[188] = 0.0;
   out_7423581578821108479[189] = 0.0;
   out_7423581578821108479[190] = 1.0;
   out_7423581578821108479[191] = 0.0;
   out_7423581578821108479[192] = 0.0;
   out_7423581578821108479[193] = 0.0;
   out_7423581578821108479[194] = 0.0;
   out_7423581578821108479[195] = 0.0;
   out_7423581578821108479[196] = 0.0;
   out_7423581578821108479[197] = 0.0;
   out_7423581578821108479[198] = 0.0;
   out_7423581578821108479[199] = 0.0;
   out_7423581578821108479[200] = 0.0;
   out_7423581578821108479[201] = 0.0;
   out_7423581578821108479[202] = 0.0;
   out_7423581578821108479[203] = 0.0;
   out_7423581578821108479[204] = 0.0;
   out_7423581578821108479[205] = 0.0;
   out_7423581578821108479[206] = 0.0;
   out_7423581578821108479[207] = 0.0;
   out_7423581578821108479[208] = 0.0;
   out_7423581578821108479[209] = 1.0;
   out_7423581578821108479[210] = 0.0;
   out_7423581578821108479[211] = 0.0;
   out_7423581578821108479[212] = 0.0;
   out_7423581578821108479[213] = 0.0;
   out_7423581578821108479[214] = 0.0;
   out_7423581578821108479[215] = 0.0;
   out_7423581578821108479[216] = 0.0;
   out_7423581578821108479[217] = 0.0;
   out_7423581578821108479[218] = 0.0;
   out_7423581578821108479[219] = 0.0;
   out_7423581578821108479[220] = 0.0;
   out_7423581578821108479[221] = 0.0;
   out_7423581578821108479[222] = 0.0;
   out_7423581578821108479[223] = 0.0;
   out_7423581578821108479[224] = 0.0;
   out_7423581578821108479[225] = 0.0;
   out_7423581578821108479[226] = 0.0;
   out_7423581578821108479[227] = 0.0;
   out_7423581578821108479[228] = 1.0;
   out_7423581578821108479[229] = 0.0;
   out_7423581578821108479[230] = 0.0;
   out_7423581578821108479[231] = 0.0;
   out_7423581578821108479[232] = 0.0;
   out_7423581578821108479[233] = 0.0;
   out_7423581578821108479[234] = 0.0;
   out_7423581578821108479[235] = 0.0;
   out_7423581578821108479[236] = 0.0;
   out_7423581578821108479[237] = 0.0;
   out_7423581578821108479[238] = 0.0;
   out_7423581578821108479[239] = 0.0;
   out_7423581578821108479[240] = 0.0;
   out_7423581578821108479[241] = 0.0;
   out_7423581578821108479[242] = 0.0;
   out_7423581578821108479[243] = 0.0;
   out_7423581578821108479[244] = 0.0;
   out_7423581578821108479[245] = 0.0;
   out_7423581578821108479[246] = 0.0;
   out_7423581578821108479[247] = 1.0;
   out_7423581578821108479[248] = 0.0;
   out_7423581578821108479[249] = 0.0;
   out_7423581578821108479[250] = 0.0;
   out_7423581578821108479[251] = 0.0;
   out_7423581578821108479[252] = 0.0;
   out_7423581578821108479[253] = 0.0;
   out_7423581578821108479[254] = 0.0;
   out_7423581578821108479[255] = 0.0;
   out_7423581578821108479[256] = 0.0;
   out_7423581578821108479[257] = 0.0;
   out_7423581578821108479[258] = 0.0;
   out_7423581578821108479[259] = 0.0;
   out_7423581578821108479[260] = 0.0;
   out_7423581578821108479[261] = 0.0;
   out_7423581578821108479[262] = 0.0;
   out_7423581578821108479[263] = 0.0;
   out_7423581578821108479[264] = 0.0;
   out_7423581578821108479[265] = 0.0;
   out_7423581578821108479[266] = 1.0;
   out_7423581578821108479[267] = 0.0;
   out_7423581578821108479[268] = 0.0;
   out_7423581578821108479[269] = 0.0;
   out_7423581578821108479[270] = 0.0;
   out_7423581578821108479[271] = 0.0;
   out_7423581578821108479[272] = 0.0;
   out_7423581578821108479[273] = 0.0;
   out_7423581578821108479[274] = 0.0;
   out_7423581578821108479[275] = 0.0;
   out_7423581578821108479[276] = 0.0;
   out_7423581578821108479[277] = 0.0;
   out_7423581578821108479[278] = 0.0;
   out_7423581578821108479[279] = 0.0;
   out_7423581578821108479[280] = 0.0;
   out_7423581578821108479[281] = 0.0;
   out_7423581578821108479[282] = 0.0;
   out_7423581578821108479[283] = 0.0;
   out_7423581578821108479[284] = 0.0;
   out_7423581578821108479[285] = 1.0;
   out_7423581578821108479[286] = 0.0;
   out_7423581578821108479[287] = 0.0;
   out_7423581578821108479[288] = 0.0;
   out_7423581578821108479[289] = 0.0;
   out_7423581578821108479[290] = 0.0;
   out_7423581578821108479[291] = 0.0;
   out_7423581578821108479[292] = 0.0;
   out_7423581578821108479[293] = 0.0;
   out_7423581578821108479[294] = 0.0;
   out_7423581578821108479[295] = 0.0;
   out_7423581578821108479[296] = 0.0;
   out_7423581578821108479[297] = 0.0;
   out_7423581578821108479[298] = 0.0;
   out_7423581578821108479[299] = 0.0;
   out_7423581578821108479[300] = 0.0;
   out_7423581578821108479[301] = 0.0;
   out_7423581578821108479[302] = 0.0;
   out_7423581578821108479[303] = 0.0;
   out_7423581578821108479[304] = 1.0;
   out_7423581578821108479[305] = 0.0;
   out_7423581578821108479[306] = 0.0;
   out_7423581578821108479[307] = 0.0;
   out_7423581578821108479[308] = 0.0;
   out_7423581578821108479[309] = 0.0;
   out_7423581578821108479[310] = 0.0;
   out_7423581578821108479[311] = 0.0;
   out_7423581578821108479[312] = 0.0;
   out_7423581578821108479[313] = 0.0;
   out_7423581578821108479[314] = 0.0;
   out_7423581578821108479[315] = 0.0;
   out_7423581578821108479[316] = 0.0;
   out_7423581578821108479[317] = 0.0;
   out_7423581578821108479[318] = 0.0;
   out_7423581578821108479[319] = 0.0;
   out_7423581578821108479[320] = 0.0;
   out_7423581578821108479[321] = 0.0;
   out_7423581578821108479[322] = 0.0;
   out_7423581578821108479[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6548671648242666617) {
   out_6548671648242666617[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6548671648242666617[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6548671648242666617[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6548671648242666617[3] = dt*state[12] + state[3];
   out_6548671648242666617[4] = dt*state[13] + state[4];
   out_6548671648242666617[5] = dt*state[14] + state[5];
   out_6548671648242666617[6] = state[6];
   out_6548671648242666617[7] = state[7];
   out_6548671648242666617[8] = state[8];
   out_6548671648242666617[9] = state[9];
   out_6548671648242666617[10] = state[10];
   out_6548671648242666617[11] = state[11];
   out_6548671648242666617[12] = state[12];
   out_6548671648242666617[13] = state[13];
   out_6548671648242666617[14] = state[14];
   out_6548671648242666617[15] = state[15];
   out_6548671648242666617[16] = state[16];
   out_6548671648242666617[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8137210036585204187) {
   out_8137210036585204187[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8137210036585204187[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8137210036585204187[2] = 0;
   out_8137210036585204187[3] = 0;
   out_8137210036585204187[4] = 0;
   out_8137210036585204187[5] = 0;
   out_8137210036585204187[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8137210036585204187[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8137210036585204187[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8137210036585204187[9] = 0;
   out_8137210036585204187[10] = 0;
   out_8137210036585204187[11] = 0;
   out_8137210036585204187[12] = 0;
   out_8137210036585204187[13] = 0;
   out_8137210036585204187[14] = 0;
   out_8137210036585204187[15] = 0;
   out_8137210036585204187[16] = 0;
   out_8137210036585204187[17] = 0;
   out_8137210036585204187[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8137210036585204187[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8137210036585204187[20] = 0;
   out_8137210036585204187[21] = 0;
   out_8137210036585204187[22] = 0;
   out_8137210036585204187[23] = 0;
   out_8137210036585204187[24] = 0;
   out_8137210036585204187[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8137210036585204187[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8137210036585204187[27] = 0;
   out_8137210036585204187[28] = 0;
   out_8137210036585204187[29] = 0;
   out_8137210036585204187[30] = 0;
   out_8137210036585204187[31] = 0;
   out_8137210036585204187[32] = 0;
   out_8137210036585204187[33] = 0;
   out_8137210036585204187[34] = 0;
   out_8137210036585204187[35] = 0;
   out_8137210036585204187[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8137210036585204187[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8137210036585204187[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8137210036585204187[39] = 0;
   out_8137210036585204187[40] = 0;
   out_8137210036585204187[41] = 0;
   out_8137210036585204187[42] = 0;
   out_8137210036585204187[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8137210036585204187[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8137210036585204187[45] = 0;
   out_8137210036585204187[46] = 0;
   out_8137210036585204187[47] = 0;
   out_8137210036585204187[48] = 0;
   out_8137210036585204187[49] = 0;
   out_8137210036585204187[50] = 0;
   out_8137210036585204187[51] = 0;
   out_8137210036585204187[52] = 0;
   out_8137210036585204187[53] = 0;
   out_8137210036585204187[54] = 0;
   out_8137210036585204187[55] = 0;
   out_8137210036585204187[56] = 0;
   out_8137210036585204187[57] = 1;
   out_8137210036585204187[58] = 0;
   out_8137210036585204187[59] = 0;
   out_8137210036585204187[60] = 0;
   out_8137210036585204187[61] = 0;
   out_8137210036585204187[62] = 0;
   out_8137210036585204187[63] = 0;
   out_8137210036585204187[64] = 0;
   out_8137210036585204187[65] = 0;
   out_8137210036585204187[66] = dt;
   out_8137210036585204187[67] = 0;
   out_8137210036585204187[68] = 0;
   out_8137210036585204187[69] = 0;
   out_8137210036585204187[70] = 0;
   out_8137210036585204187[71] = 0;
   out_8137210036585204187[72] = 0;
   out_8137210036585204187[73] = 0;
   out_8137210036585204187[74] = 0;
   out_8137210036585204187[75] = 0;
   out_8137210036585204187[76] = 1;
   out_8137210036585204187[77] = 0;
   out_8137210036585204187[78] = 0;
   out_8137210036585204187[79] = 0;
   out_8137210036585204187[80] = 0;
   out_8137210036585204187[81] = 0;
   out_8137210036585204187[82] = 0;
   out_8137210036585204187[83] = 0;
   out_8137210036585204187[84] = 0;
   out_8137210036585204187[85] = dt;
   out_8137210036585204187[86] = 0;
   out_8137210036585204187[87] = 0;
   out_8137210036585204187[88] = 0;
   out_8137210036585204187[89] = 0;
   out_8137210036585204187[90] = 0;
   out_8137210036585204187[91] = 0;
   out_8137210036585204187[92] = 0;
   out_8137210036585204187[93] = 0;
   out_8137210036585204187[94] = 0;
   out_8137210036585204187[95] = 1;
   out_8137210036585204187[96] = 0;
   out_8137210036585204187[97] = 0;
   out_8137210036585204187[98] = 0;
   out_8137210036585204187[99] = 0;
   out_8137210036585204187[100] = 0;
   out_8137210036585204187[101] = 0;
   out_8137210036585204187[102] = 0;
   out_8137210036585204187[103] = 0;
   out_8137210036585204187[104] = dt;
   out_8137210036585204187[105] = 0;
   out_8137210036585204187[106] = 0;
   out_8137210036585204187[107] = 0;
   out_8137210036585204187[108] = 0;
   out_8137210036585204187[109] = 0;
   out_8137210036585204187[110] = 0;
   out_8137210036585204187[111] = 0;
   out_8137210036585204187[112] = 0;
   out_8137210036585204187[113] = 0;
   out_8137210036585204187[114] = 1;
   out_8137210036585204187[115] = 0;
   out_8137210036585204187[116] = 0;
   out_8137210036585204187[117] = 0;
   out_8137210036585204187[118] = 0;
   out_8137210036585204187[119] = 0;
   out_8137210036585204187[120] = 0;
   out_8137210036585204187[121] = 0;
   out_8137210036585204187[122] = 0;
   out_8137210036585204187[123] = 0;
   out_8137210036585204187[124] = 0;
   out_8137210036585204187[125] = 0;
   out_8137210036585204187[126] = 0;
   out_8137210036585204187[127] = 0;
   out_8137210036585204187[128] = 0;
   out_8137210036585204187[129] = 0;
   out_8137210036585204187[130] = 0;
   out_8137210036585204187[131] = 0;
   out_8137210036585204187[132] = 0;
   out_8137210036585204187[133] = 1;
   out_8137210036585204187[134] = 0;
   out_8137210036585204187[135] = 0;
   out_8137210036585204187[136] = 0;
   out_8137210036585204187[137] = 0;
   out_8137210036585204187[138] = 0;
   out_8137210036585204187[139] = 0;
   out_8137210036585204187[140] = 0;
   out_8137210036585204187[141] = 0;
   out_8137210036585204187[142] = 0;
   out_8137210036585204187[143] = 0;
   out_8137210036585204187[144] = 0;
   out_8137210036585204187[145] = 0;
   out_8137210036585204187[146] = 0;
   out_8137210036585204187[147] = 0;
   out_8137210036585204187[148] = 0;
   out_8137210036585204187[149] = 0;
   out_8137210036585204187[150] = 0;
   out_8137210036585204187[151] = 0;
   out_8137210036585204187[152] = 1;
   out_8137210036585204187[153] = 0;
   out_8137210036585204187[154] = 0;
   out_8137210036585204187[155] = 0;
   out_8137210036585204187[156] = 0;
   out_8137210036585204187[157] = 0;
   out_8137210036585204187[158] = 0;
   out_8137210036585204187[159] = 0;
   out_8137210036585204187[160] = 0;
   out_8137210036585204187[161] = 0;
   out_8137210036585204187[162] = 0;
   out_8137210036585204187[163] = 0;
   out_8137210036585204187[164] = 0;
   out_8137210036585204187[165] = 0;
   out_8137210036585204187[166] = 0;
   out_8137210036585204187[167] = 0;
   out_8137210036585204187[168] = 0;
   out_8137210036585204187[169] = 0;
   out_8137210036585204187[170] = 0;
   out_8137210036585204187[171] = 1;
   out_8137210036585204187[172] = 0;
   out_8137210036585204187[173] = 0;
   out_8137210036585204187[174] = 0;
   out_8137210036585204187[175] = 0;
   out_8137210036585204187[176] = 0;
   out_8137210036585204187[177] = 0;
   out_8137210036585204187[178] = 0;
   out_8137210036585204187[179] = 0;
   out_8137210036585204187[180] = 0;
   out_8137210036585204187[181] = 0;
   out_8137210036585204187[182] = 0;
   out_8137210036585204187[183] = 0;
   out_8137210036585204187[184] = 0;
   out_8137210036585204187[185] = 0;
   out_8137210036585204187[186] = 0;
   out_8137210036585204187[187] = 0;
   out_8137210036585204187[188] = 0;
   out_8137210036585204187[189] = 0;
   out_8137210036585204187[190] = 1;
   out_8137210036585204187[191] = 0;
   out_8137210036585204187[192] = 0;
   out_8137210036585204187[193] = 0;
   out_8137210036585204187[194] = 0;
   out_8137210036585204187[195] = 0;
   out_8137210036585204187[196] = 0;
   out_8137210036585204187[197] = 0;
   out_8137210036585204187[198] = 0;
   out_8137210036585204187[199] = 0;
   out_8137210036585204187[200] = 0;
   out_8137210036585204187[201] = 0;
   out_8137210036585204187[202] = 0;
   out_8137210036585204187[203] = 0;
   out_8137210036585204187[204] = 0;
   out_8137210036585204187[205] = 0;
   out_8137210036585204187[206] = 0;
   out_8137210036585204187[207] = 0;
   out_8137210036585204187[208] = 0;
   out_8137210036585204187[209] = 1;
   out_8137210036585204187[210] = 0;
   out_8137210036585204187[211] = 0;
   out_8137210036585204187[212] = 0;
   out_8137210036585204187[213] = 0;
   out_8137210036585204187[214] = 0;
   out_8137210036585204187[215] = 0;
   out_8137210036585204187[216] = 0;
   out_8137210036585204187[217] = 0;
   out_8137210036585204187[218] = 0;
   out_8137210036585204187[219] = 0;
   out_8137210036585204187[220] = 0;
   out_8137210036585204187[221] = 0;
   out_8137210036585204187[222] = 0;
   out_8137210036585204187[223] = 0;
   out_8137210036585204187[224] = 0;
   out_8137210036585204187[225] = 0;
   out_8137210036585204187[226] = 0;
   out_8137210036585204187[227] = 0;
   out_8137210036585204187[228] = 1;
   out_8137210036585204187[229] = 0;
   out_8137210036585204187[230] = 0;
   out_8137210036585204187[231] = 0;
   out_8137210036585204187[232] = 0;
   out_8137210036585204187[233] = 0;
   out_8137210036585204187[234] = 0;
   out_8137210036585204187[235] = 0;
   out_8137210036585204187[236] = 0;
   out_8137210036585204187[237] = 0;
   out_8137210036585204187[238] = 0;
   out_8137210036585204187[239] = 0;
   out_8137210036585204187[240] = 0;
   out_8137210036585204187[241] = 0;
   out_8137210036585204187[242] = 0;
   out_8137210036585204187[243] = 0;
   out_8137210036585204187[244] = 0;
   out_8137210036585204187[245] = 0;
   out_8137210036585204187[246] = 0;
   out_8137210036585204187[247] = 1;
   out_8137210036585204187[248] = 0;
   out_8137210036585204187[249] = 0;
   out_8137210036585204187[250] = 0;
   out_8137210036585204187[251] = 0;
   out_8137210036585204187[252] = 0;
   out_8137210036585204187[253] = 0;
   out_8137210036585204187[254] = 0;
   out_8137210036585204187[255] = 0;
   out_8137210036585204187[256] = 0;
   out_8137210036585204187[257] = 0;
   out_8137210036585204187[258] = 0;
   out_8137210036585204187[259] = 0;
   out_8137210036585204187[260] = 0;
   out_8137210036585204187[261] = 0;
   out_8137210036585204187[262] = 0;
   out_8137210036585204187[263] = 0;
   out_8137210036585204187[264] = 0;
   out_8137210036585204187[265] = 0;
   out_8137210036585204187[266] = 1;
   out_8137210036585204187[267] = 0;
   out_8137210036585204187[268] = 0;
   out_8137210036585204187[269] = 0;
   out_8137210036585204187[270] = 0;
   out_8137210036585204187[271] = 0;
   out_8137210036585204187[272] = 0;
   out_8137210036585204187[273] = 0;
   out_8137210036585204187[274] = 0;
   out_8137210036585204187[275] = 0;
   out_8137210036585204187[276] = 0;
   out_8137210036585204187[277] = 0;
   out_8137210036585204187[278] = 0;
   out_8137210036585204187[279] = 0;
   out_8137210036585204187[280] = 0;
   out_8137210036585204187[281] = 0;
   out_8137210036585204187[282] = 0;
   out_8137210036585204187[283] = 0;
   out_8137210036585204187[284] = 0;
   out_8137210036585204187[285] = 1;
   out_8137210036585204187[286] = 0;
   out_8137210036585204187[287] = 0;
   out_8137210036585204187[288] = 0;
   out_8137210036585204187[289] = 0;
   out_8137210036585204187[290] = 0;
   out_8137210036585204187[291] = 0;
   out_8137210036585204187[292] = 0;
   out_8137210036585204187[293] = 0;
   out_8137210036585204187[294] = 0;
   out_8137210036585204187[295] = 0;
   out_8137210036585204187[296] = 0;
   out_8137210036585204187[297] = 0;
   out_8137210036585204187[298] = 0;
   out_8137210036585204187[299] = 0;
   out_8137210036585204187[300] = 0;
   out_8137210036585204187[301] = 0;
   out_8137210036585204187[302] = 0;
   out_8137210036585204187[303] = 0;
   out_8137210036585204187[304] = 1;
   out_8137210036585204187[305] = 0;
   out_8137210036585204187[306] = 0;
   out_8137210036585204187[307] = 0;
   out_8137210036585204187[308] = 0;
   out_8137210036585204187[309] = 0;
   out_8137210036585204187[310] = 0;
   out_8137210036585204187[311] = 0;
   out_8137210036585204187[312] = 0;
   out_8137210036585204187[313] = 0;
   out_8137210036585204187[314] = 0;
   out_8137210036585204187[315] = 0;
   out_8137210036585204187[316] = 0;
   out_8137210036585204187[317] = 0;
   out_8137210036585204187[318] = 0;
   out_8137210036585204187[319] = 0;
   out_8137210036585204187[320] = 0;
   out_8137210036585204187[321] = 0;
   out_8137210036585204187[322] = 0;
   out_8137210036585204187[323] = 1;
}
void h_4(double *state, double *unused, double *out_8933482968708726010) {
   out_8933482968708726010[0] = state[6] + state[9];
   out_8933482968708726010[1] = state[7] + state[10];
   out_8933482968708726010[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2822857610915218370) {
   out_2822857610915218370[0] = 0;
   out_2822857610915218370[1] = 0;
   out_2822857610915218370[2] = 0;
   out_2822857610915218370[3] = 0;
   out_2822857610915218370[4] = 0;
   out_2822857610915218370[5] = 0;
   out_2822857610915218370[6] = 1;
   out_2822857610915218370[7] = 0;
   out_2822857610915218370[8] = 0;
   out_2822857610915218370[9] = 1;
   out_2822857610915218370[10] = 0;
   out_2822857610915218370[11] = 0;
   out_2822857610915218370[12] = 0;
   out_2822857610915218370[13] = 0;
   out_2822857610915218370[14] = 0;
   out_2822857610915218370[15] = 0;
   out_2822857610915218370[16] = 0;
   out_2822857610915218370[17] = 0;
   out_2822857610915218370[18] = 0;
   out_2822857610915218370[19] = 0;
   out_2822857610915218370[20] = 0;
   out_2822857610915218370[21] = 0;
   out_2822857610915218370[22] = 0;
   out_2822857610915218370[23] = 0;
   out_2822857610915218370[24] = 0;
   out_2822857610915218370[25] = 1;
   out_2822857610915218370[26] = 0;
   out_2822857610915218370[27] = 0;
   out_2822857610915218370[28] = 1;
   out_2822857610915218370[29] = 0;
   out_2822857610915218370[30] = 0;
   out_2822857610915218370[31] = 0;
   out_2822857610915218370[32] = 0;
   out_2822857610915218370[33] = 0;
   out_2822857610915218370[34] = 0;
   out_2822857610915218370[35] = 0;
   out_2822857610915218370[36] = 0;
   out_2822857610915218370[37] = 0;
   out_2822857610915218370[38] = 0;
   out_2822857610915218370[39] = 0;
   out_2822857610915218370[40] = 0;
   out_2822857610915218370[41] = 0;
   out_2822857610915218370[42] = 0;
   out_2822857610915218370[43] = 0;
   out_2822857610915218370[44] = 1;
   out_2822857610915218370[45] = 0;
   out_2822857610915218370[46] = 0;
   out_2822857610915218370[47] = 1;
   out_2822857610915218370[48] = 0;
   out_2822857610915218370[49] = 0;
   out_2822857610915218370[50] = 0;
   out_2822857610915218370[51] = 0;
   out_2822857610915218370[52] = 0;
   out_2822857610915218370[53] = 0;
}
void h_10(double *state, double *unused, double *out_4168852290738747850) {
   out_4168852290738747850[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4168852290738747850[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4168852290738747850[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1054675281937211144) {
   out_1054675281937211144[0] = 0;
   out_1054675281937211144[1] = 9.8100000000000005*cos(state[1]);
   out_1054675281937211144[2] = 0;
   out_1054675281937211144[3] = 0;
   out_1054675281937211144[4] = -state[8];
   out_1054675281937211144[5] = state[7];
   out_1054675281937211144[6] = 0;
   out_1054675281937211144[7] = state[5];
   out_1054675281937211144[8] = -state[4];
   out_1054675281937211144[9] = 0;
   out_1054675281937211144[10] = 0;
   out_1054675281937211144[11] = 0;
   out_1054675281937211144[12] = 1;
   out_1054675281937211144[13] = 0;
   out_1054675281937211144[14] = 0;
   out_1054675281937211144[15] = 1;
   out_1054675281937211144[16] = 0;
   out_1054675281937211144[17] = 0;
   out_1054675281937211144[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1054675281937211144[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1054675281937211144[20] = 0;
   out_1054675281937211144[21] = state[8];
   out_1054675281937211144[22] = 0;
   out_1054675281937211144[23] = -state[6];
   out_1054675281937211144[24] = -state[5];
   out_1054675281937211144[25] = 0;
   out_1054675281937211144[26] = state[3];
   out_1054675281937211144[27] = 0;
   out_1054675281937211144[28] = 0;
   out_1054675281937211144[29] = 0;
   out_1054675281937211144[30] = 0;
   out_1054675281937211144[31] = 1;
   out_1054675281937211144[32] = 0;
   out_1054675281937211144[33] = 0;
   out_1054675281937211144[34] = 1;
   out_1054675281937211144[35] = 0;
   out_1054675281937211144[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1054675281937211144[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1054675281937211144[38] = 0;
   out_1054675281937211144[39] = -state[7];
   out_1054675281937211144[40] = state[6];
   out_1054675281937211144[41] = 0;
   out_1054675281937211144[42] = state[4];
   out_1054675281937211144[43] = -state[3];
   out_1054675281937211144[44] = 0;
   out_1054675281937211144[45] = 0;
   out_1054675281937211144[46] = 0;
   out_1054675281937211144[47] = 0;
   out_1054675281937211144[48] = 0;
   out_1054675281937211144[49] = 0;
   out_1054675281937211144[50] = 1;
   out_1054675281937211144[51] = 0;
   out_1054675281937211144[52] = 0;
   out_1054675281937211144[53] = 1;
}
void h_13(double *state, double *unused, double *out_4043461384186272271) {
   out_4043461384186272271[0] = state[3];
   out_4043461384186272271[1] = state[4];
   out_4043461384186272271[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4787773597401482559) {
   out_4787773597401482559[0] = 0;
   out_4787773597401482559[1] = 0;
   out_4787773597401482559[2] = 0;
   out_4787773597401482559[3] = 1;
   out_4787773597401482559[4] = 0;
   out_4787773597401482559[5] = 0;
   out_4787773597401482559[6] = 0;
   out_4787773597401482559[7] = 0;
   out_4787773597401482559[8] = 0;
   out_4787773597401482559[9] = 0;
   out_4787773597401482559[10] = 0;
   out_4787773597401482559[11] = 0;
   out_4787773597401482559[12] = 0;
   out_4787773597401482559[13] = 0;
   out_4787773597401482559[14] = 0;
   out_4787773597401482559[15] = 0;
   out_4787773597401482559[16] = 0;
   out_4787773597401482559[17] = 0;
   out_4787773597401482559[18] = 0;
   out_4787773597401482559[19] = 0;
   out_4787773597401482559[20] = 0;
   out_4787773597401482559[21] = 0;
   out_4787773597401482559[22] = 1;
   out_4787773597401482559[23] = 0;
   out_4787773597401482559[24] = 0;
   out_4787773597401482559[25] = 0;
   out_4787773597401482559[26] = 0;
   out_4787773597401482559[27] = 0;
   out_4787773597401482559[28] = 0;
   out_4787773597401482559[29] = 0;
   out_4787773597401482559[30] = 0;
   out_4787773597401482559[31] = 0;
   out_4787773597401482559[32] = 0;
   out_4787773597401482559[33] = 0;
   out_4787773597401482559[34] = 0;
   out_4787773597401482559[35] = 0;
   out_4787773597401482559[36] = 0;
   out_4787773597401482559[37] = 0;
   out_4787773597401482559[38] = 0;
   out_4787773597401482559[39] = 0;
   out_4787773597401482559[40] = 0;
   out_4787773597401482559[41] = 1;
   out_4787773597401482559[42] = 0;
   out_4787773597401482559[43] = 0;
   out_4787773597401482559[44] = 0;
   out_4787773597401482559[45] = 0;
   out_4787773597401482559[46] = 0;
   out_4787773597401482559[47] = 0;
   out_4787773597401482559[48] = 0;
   out_4787773597401482559[49] = 0;
   out_4787773597401482559[50] = 0;
   out_4787773597401482559[51] = 0;
   out_4787773597401482559[52] = 0;
   out_4787773597401482559[53] = 0;
}
void h_14(double *state, double *unused, double *out_6969961930413222291) {
   out_6969961930413222291[0] = state[6];
   out_6969961930413222291[1] = state[7];
   out_6969961930413222291[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1140383245424266159) {
   out_1140383245424266159[0] = 0;
   out_1140383245424266159[1] = 0;
   out_1140383245424266159[2] = 0;
   out_1140383245424266159[3] = 0;
   out_1140383245424266159[4] = 0;
   out_1140383245424266159[5] = 0;
   out_1140383245424266159[6] = 1;
   out_1140383245424266159[7] = 0;
   out_1140383245424266159[8] = 0;
   out_1140383245424266159[9] = 0;
   out_1140383245424266159[10] = 0;
   out_1140383245424266159[11] = 0;
   out_1140383245424266159[12] = 0;
   out_1140383245424266159[13] = 0;
   out_1140383245424266159[14] = 0;
   out_1140383245424266159[15] = 0;
   out_1140383245424266159[16] = 0;
   out_1140383245424266159[17] = 0;
   out_1140383245424266159[18] = 0;
   out_1140383245424266159[19] = 0;
   out_1140383245424266159[20] = 0;
   out_1140383245424266159[21] = 0;
   out_1140383245424266159[22] = 0;
   out_1140383245424266159[23] = 0;
   out_1140383245424266159[24] = 0;
   out_1140383245424266159[25] = 1;
   out_1140383245424266159[26] = 0;
   out_1140383245424266159[27] = 0;
   out_1140383245424266159[28] = 0;
   out_1140383245424266159[29] = 0;
   out_1140383245424266159[30] = 0;
   out_1140383245424266159[31] = 0;
   out_1140383245424266159[32] = 0;
   out_1140383245424266159[33] = 0;
   out_1140383245424266159[34] = 0;
   out_1140383245424266159[35] = 0;
   out_1140383245424266159[36] = 0;
   out_1140383245424266159[37] = 0;
   out_1140383245424266159[38] = 0;
   out_1140383245424266159[39] = 0;
   out_1140383245424266159[40] = 0;
   out_1140383245424266159[41] = 0;
   out_1140383245424266159[42] = 0;
   out_1140383245424266159[43] = 0;
   out_1140383245424266159[44] = 1;
   out_1140383245424266159[45] = 0;
   out_1140383245424266159[46] = 0;
   out_1140383245424266159[47] = 0;
   out_1140383245424266159[48] = 0;
   out_1140383245424266159[49] = 0;
   out_1140383245424266159[50] = 0;
   out_1140383245424266159[51] = 0;
   out_1140383245424266159[52] = 0;
   out_1140383245424266159[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7318583843401046885) {
  err_fun(nom_x, delta_x, out_7318583843401046885);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8604214068849565205) {
  inv_err_fun(nom_x, true_x, out_8604214068849565205);
}
void pose_H_mod_fun(double *state, double *out_7423581578821108479) {
  H_mod_fun(state, out_7423581578821108479);
}
void pose_f_fun(double *state, double dt, double *out_6548671648242666617) {
  f_fun(state,  dt, out_6548671648242666617);
}
void pose_F_fun(double *state, double dt, double *out_8137210036585204187) {
  F_fun(state,  dt, out_8137210036585204187);
}
void pose_h_4(double *state, double *unused, double *out_8933482968708726010) {
  h_4(state, unused, out_8933482968708726010);
}
void pose_H_4(double *state, double *unused, double *out_2822857610915218370) {
  H_4(state, unused, out_2822857610915218370);
}
void pose_h_10(double *state, double *unused, double *out_4168852290738747850) {
  h_10(state, unused, out_4168852290738747850);
}
void pose_H_10(double *state, double *unused, double *out_1054675281937211144) {
  H_10(state, unused, out_1054675281937211144);
}
void pose_h_13(double *state, double *unused, double *out_4043461384186272271) {
  h_13(state, unused, out_4043461384186272271);
}
void pose_H_13(double *state, double *unused, double *out_4787773597401482559) {
  H_13(state, unused, out_4787773597401482559);
}
void pose_h_14(double *state, double *unused, double *out_6969961930413222291) {
  h_14(state, unused, out_6969961930413222291);
}
void pose_H_14(double *state, double *unused, double *out_1140383245424266159) {
  H_14(state, unused, out_1140383245424266159);
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
