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
void err_fun(double *nom_x, double *delta_x, double *out_3246138991131647202) {
   out_3246138991131647202[0] = delta_x[0] + nom_x[0];
   out_3246138991131647202[1] = delta_x[1] + nom_x[1];
   out_3246138991131647202[2] = delta_x[2] + nom_x[2];
   out_3246138991131647202[3] = delta_x[3] + nom_x[3];
   out_3246138991131647202[4] = delta_x[4] + nom_x[4];
   out_3246138991131647202[5] = delta_x[5] + nom_x[5];
   out_3246138991131647202[6] = delta_x[6] + nom_x[6];
   out_3246138991131647202[7] = delta_x[7] + nom_x[7];
   out_3246138991131647202[8] = delta_x[8] + nom_x[8];
   out_3246138991131647202[9] = delta_x[9] + nom_x[9];
   out_3246138991131647202[10] = delta_x[10] + nom_x[10];
   out_3246138991131647202[11] = delta_x[11] + nom_x[11];
   out_3246138991131647202[12] = delta_x[12] + nom_x[12];
   out_3246138991131647202[13] = delta_x[13] + nom_x[13];
   out_3246138991131647202[14] = delta_x[14] + nom_x[14];
   out_3246138991131647202[15] = delta_x[15] + nom_x[15];
   out_3246138991131647202[16] = delta_x[16] + nom_x[16];
   out_3246138991131647202[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4007822862672909290) {
   out_4007822862672909290[0] = -nom_x[0] + true_x[0];
   out_4007822862672909290[1] = -nom_x[1] + true_x[1];
   out_4007822862672909290[2] = -nom_x[2] + true_x[2];
   out_4007822862672909290[3] = -nom_x[3] + true_x[3];
   out_4007822862672909290[4] = -nom_x[4] + true_x[4];
   out_4007822862672909290[5] = -nom_x[5] + true_x[5];
   out_4007822862672909290[6] = -nom_x[6] + true_x[6];
   out_4007822862672909290[7] = -nom_x[7] + true_x[7];
   out_4007822862672909290[8] = -nom_x[8] + true_x[8];
   out_4007822862672909290[9] = -nom_x[9] + true_x[9];
   out_4007822862672909290[10] = -nom_x[10] + true_x[10];
   out_4007822862672909290[11] = -nom_x[11] + true_x[11];
   out_4007822862672909290[12] = -nom_x[12] + true_x[12];
   out_4007822862672909290[13] = -nom_x[13] + true_x[13];
   out_4007822862672909290[14] = -nom_x[14] + true_x[14];
   out_4007822862672909290[15] = -nom_x[15] + true_x[15];
   out_4007822862672909290[16] = -nom_x[16] + true_x[16];
   out_4007822862672909290[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8044174148668571060) {
   out_8044174148668571060[0] = 1.0;
   out_8044174148668571060[1] = 0.0;
   out_8044174148668571060[2] = 0.0;
   out_8044174148668571060[3] = 0.0;
   out_8044174148668571060[4] = 0.0;
   out_8044174148668571060[5] = 0.0;
   out_8044174148668571060[6] = 0.0;
   out_8044174148668571060[7] = 0.0;
   out_8044174148668571060[8] = 0.0;
   out_8044174148668571060[9] = 0.0;
   out_8044174148668571060[10] = 0.0;
   out_8044174148668571060[11] = 0.0;
   out_8044174148668571060[12] = 0.0;
   out_8044174148668571060[13] = 0.0;
   out_8044174148668571060[14] = 0.0;
   out_8044174148668571060[15] = 0.0;
   out_8044174148668571060[16] = 0.0;
   out_8044174148668571060[17] = 0.0;
   out_8044174148668571060[18] = 0.0;
   out_8044174148668571060[19] = 1.0;
   out_8044174148668571060[20] = 0.0;
   out_8044174148668571060[21] = 0.0;
   out_8044174148668571060[22] = 0.0;
   out_8044174148668571060[23] = 0.0;
   out_8044174148668571060[24] = 0.0;
   out_8044174148668571060[25] = 0.0;
   out_8044174148668571060[26] = 0.0;
   out_8044174148668571060[27] = 0.0;
   out_8044174148668571060[28] = 0.0;
   out_8044174148668571060[29] = 0.0;
   out_8044174148668571060[30] = 0.0;
   out_8044174148668571060[31] = 0.0;
   out_8044174148668571060[32] = 0.0;
   out_8044174148668571060[33] = 0.0;
   out_8044174148668571060[34] = 0.0;
   out_8044174148668571060[35] = 0.0;
   out_8044174148668571060[36] = 0.0;
   out_8044174148668571060[37] = 0.0;
   out_8044174148668571060[38] = 1.0;
   out_8044174148668571060[39] = 0.0;
   out_8044174148668571060[40] = 0.0;
   out_8044174148668571060[41] = 0.0;
   out_8044174148668571060[42] = 0.0;
   out_8044174148668571060[43] = 0.0;
   out_8044174148668571060[44] = 0.0;
   out_8044174148668571060[45] = 0.0;
   out_8044174148668571060[46] = 0.0;
   out_8044174148668571060[47] = 0.0;
   out_8044174148668571060[48] = 0.0;
   out_8044174148668571060[49] = 0.0;
   out_8044174148668571060[50] = 0.0;
   out_8044174148668571060[51] = 0.0;
   out_8044174148668571060[52] = 0.0;
   out_8044174148668571060[53] = 0.0;
   out_8044174148668571060[54] = 0.0;
   out_8044174148668571060[55] = 0.0;
   out_8044174148668571060[56] = 0.0;
   out_8044174148668571060[57] = 1.0;
   out_8044174148668571060[58] = 0.0;
   out_8044174148668571060[59] = 0.0;
   out_8044174148668571060[60] = 0.0;
   out_8044174148668571060[61] = 0.0;
   out_8044174148668571060[62] = 0.0;
   out_8044174148668571060[63] = 0.0;
   out_8044174148668571060[64] = 0.0;
   out_8044174148668571060[65] = 0.0;
   out_8044174148668571060[66] = 0.0;
   out_8044174148668571060[67] = 0.0;
   out_8044174148668571060[68] = 0.0;
   out_8044174148668571060[69] = 0.0;
   out_8044174148668571060[70] = 0.0;
   out_8044174148668571060[71] = 0.0;
   out_8044174148668571060[72] = 0.0;
   out_8044174148668571060[73] = 0.0;
   out_8044174148668571060[74] = 0.0;
   out_8044174148668571060[75] = 0.0;
   out_8044174148668571060[76] = 1.0;
   out_8044174148668571060[77] = 0.0;
   out_8044174148668571060[78] = 0.0;
   out_8044174148668571060[79] = 0.0;
   out_8044174148668571060[80] = 0.0;
   out_8044174148668571060[81] = 0.0;
   out_8044174148668571060[82] = 0.0;
   out_8044174148668571060[83] = 0.0;
   out_8044174148668571060[84] = 0.0;
   out_8044174148668571060[85] = 0.0;
   out_8044174148668571060[86] = 0.0;
   out_8044174148668571060[87] = 0.0;
   out_8044174148668571060[88] = 0.0;
   out_8044174148668571060[89] = 0.0;
   out_8044174148668571060[90] = 0.0;
   out_8044174148668571060[91] = 0.0;
   out_8044174148668571060[92] = 0.0;
   out_8044174148668571060[93] = 0.0;
   out_8044174148668571060[94] = 0.0;
   out_8044174148668571060[95] = 1.0;
   out_8044174148668571060[96] = 0.0;
   out_8044174148668571060[97] = 0.0;
   out_8044174148668571060[98] = 0.0;
   out_8044174148668571060[99] = 0.0;
   out_8044174148668571060[100] = 0.0;
   out_8044174148668571060[101] = 0.0;
   out_8044174148668571060[102] = 0.0;
   out_8044174148668571060[103] = 0.0;
   out_8044174148668571060[104] = 0.0;
   out_8044174148668571060[105] = 0.0;
   out_8044174148668571060[106] = 0.0;
   out_8044174148668571060[107] = 0.0;
   out_8044174148668571060[108] = 0.0;
   out_8044174148668571060[109] = 0.0;
   out_8044174148668571060[110] = 0.0;
   out_8044174148668571060[111] = 0.0;
   out_8044174148668571060[112] = 0.0;
   out_8044174148668571060[113] = 0.0;
   out_8044174148668571060[114] = 1.0;
   out_8044174148668571060[115] = 0.0;
   out_8044174148668571060[116] = 0.0;
   out_8044174148668571060[117] = 0.0;
   out_8044174148668571060[118] = 0.0;
   out_8044174148668571060[119] = 0.0;
   out_8044174148668571060[120] = 0.0;
   out_8044174148668571060[121] = 0.0;
   out_8044174148668571060[122] = 0.0;
   out_8044174148668571060[123] = 0.0;
   out_8044174148668571060[124] = 0.0;
   out_8044174148668571060[125] = 0.0;
   out_8044174148668571060[126] = 0.0;
   out_8044174148668571060[127] = 0.0;
   out_8044174148668571060[128] = 0.0;
   out_8044174148668571060[129] = 0.0;
   out_8044174148668571060[130] = 0.0;
   out_8044174148668571060[131] = 0.0;
   out_8044174148668571060[132] = 0.0;
   out_8044174148668571060[133] = 1.0;
   out_8044174148668571060[134] = 0.0;
   out_8044174148668571060[135] = 0.0;
   out_8044174148668571060[136] = 0.0;
   out_8044174148668571060[137] = 0.0;
   out_8044174148668571060[138] = 0.0;
   out_8044174148668571060[139] = 0.0;
   out_8044174148668571060[140] = 0.0;
   out_8044174148668571060[141] = 0.0;
   out_8044174148668571060[142] = 0.0;
   out_8044174148668571060[143] = 0.0;
   out_8044174148668571060[144] = 0.0;
   out_8044174148668571060[145] = 0.0;
   out_8044174148668571060[146] = 0.0;
   out_8044174148668571060[147] = 0.0;
   out_8044174148668571060[148] = 0.0;
   out_8044174148668571060[149] = 0.0;
   out_8044174148668571060[150] = 0.0;
   out_8044174148668571060[151] = 0.0;
   out_8044174148668571060[152] = 1.0;
   out_8044174148668571060[153] = 0.0;
   out_8044174148668571060[154] = 0.0;
   out_8044174148668571060[155] = 0.0;
   out_8044174148668571060[156] = 0.0;
   out_8044174148668571060[157] = 0.0;
   out_8044174148668571060[158] = 0.0;
   out_8044174148668571060[159] = 0.0;
   out_8044174148668571060[160] = 0.0;
   out_8044174148668571060[161] = 0.0;
   out_8044174148668571060[162] = 0.0;
   out_8044174148668571060[163] = 0.0;
   out_8044174148668571060[164] = 0.0;
   out_8044174148668571060[165] = 0.0;
   out_8044174148668571060[166] = 0.0;
   out_8044174148668571060[167] = 0.0;
   out_8044174148668571060[168] = 0.0;
   out_8044174148668571060[169] = 0.0;
   out_8044174148668571060[170] = 0.0;
   out_8044174148668571060[171] = 1.0;
   out_8044174148668571060[172] = 0.0;
   out_8044174148668571060[173] = 0.0;
   out_8044174148668571060[174] = 0.0;
   out_8044174148668571060[175] = 0.0;
   out_8044174148668571060[176] = 0.0;
   out_8044174148668571060[177] = 0.0;
   out_8044174148668571060[178] = 0.0;
   out_8044174148668571060[179] = 0.0;
   out_8044174148668571060[180] = 0.0;
   out_8044174148668571060[181] = 0.0;
   out_8044174148668571060[182] = 0.0;
   out_8044174148668571060[183] = 0.0;
   out_8044174148668571060[184] = 0.0;
   out_8044174148668571060[185] = 0.0;
   out_8044174148668571060[186] = 0.0;
   out_8044174148668571060[187] = 0.0;
   out_8044174148668571060[188] = 0.0;
   out_8044174148668571060[189] = 0.0;
   out_8044174148668571060[190] = 1.0;
   out_8044174148668571060[191] = 0.0;
   out_8044174148668571060[192] = 0.0;
   out_8044174148668571060[193] = 0.0;
   out_8044174148668571060[194] = 0.0;
   out_8044174148668571060[195] = 0.0;
   out_8044174148668571060[196] = 0.0;
   out_8044174148668571060[197] = 0.0;
   out_8044174148668571060[198] = 0.0;
   out_8044174148668571060[199] = 0.0;
   out_8044174148668571060[200] = 0.0;
   out_8044174148668571060[201] = 0.0;
   out_8044174148668571060[202] = 0.0;
   out_8044174148668571060[203] = 0.0;
   out_8044174148668571060[204] = 0.0;
   out_8044174148668571060[205] = 0.0;
   out_8044174148668571060[206] = 0.0;
   out_8044174148668571060[207] = 0.0;
   out_8044174148668571060[208] = 0.0;
   out_8044174148668571060[209] = 1.0;
   out_8044174148668571060[210] = 0.0;
   out_8044174148668571060[211] = 0.0;
   out_8044174148668571060[212] = 0.0;
   out_8044174148668571060[213] = 0.0;
   out_8044174148668571060[214] = 0.0;
   out_8044174148668571060[215] = 0.0;
   out_8044174148668571060[216] = 0.0;
   out_8044174148668571060[217] = 0.0;
   out_8044174148668571060[218] = 0.0;
   out_8044174148668571060[219] = 0.0;
   out_8044174148668571060[220] = 0.0;
   out_8044174148668571060[221] = 0.0;
   out_8044174148668571060[222] = 0.0;
   out_8044174148668571060[223] = 0.0;
   out_8044174148668571060[224] = 0.0;
   out_8044174148668571060[225] = 0.0;
   out_8044174148668571060[226] = 0.0;
   out_8044174148668571060[227] = 0.0;
   out_8044174148668571060[228] = 1.0;
   out_8044174148668571060[229] = 0.0;
   out_8044174148668571060[230] = 0.0;
   out_8044174148668571060[231] = 0.0;
   out_8044174148668571060[232] = 0.0;
   out_8044174148668571060[233] = 0.0;
   out_8044174148668571060[234] = 0.0;
   out_8044174148668571060[235] = 0.0;
   out_8044174148668571060[236] = 0.0;
   out_8044174148668571060[237] = 0.0;
   out_8044174148668571060[238] = 0.0;
   out_8044174148668571060[239] = 0.0;
   out_8044174148668571060[240] = 0.0;
   out_8044174148668571060[241] = 0.0;
   out_8044174148668571060[242] = 0.0;
   out_8044174148668571060[243] = 0.0;
   out_8044174148668571060[244] = 0.0;
   out_8044174148668571060[245] = 0.0;
   out_8044174148668571060[246] = 0.0;
   out_8044174148668571060[247] = 1.0;
   out_8044174148668571060[248] = 0.0;
   out_8044174148668571060[249] = 0.0;
   out_8044174148668571060[250] = 0.0;
   out_8044174148668571060[251] = 0.0;
   out_8044174148668571060[252] = 0.0;
   out_8044174148668571060[253] = 0.0;
   out_8044174148668571060[254] = 0.0;
   out_8044174148668571060[255] = 0.0;
   out_8044174148668571060[256] = 0.0;
   out_8044174148668571060[257] = 0.0;
   out_8044174148668571060[258] = 0.0;
   out_8044174148668571060[259] = 0.0;
   out_8044174148668571060[260] = 0.0;
   out_8044174148668571060[261] = 0.0;
   out_8044174148668571060[262] = 0.0;
   out_8044174148668571060[263] = 0.0;
   out_8044174148668571060[264] = 0.0;
   out_8044174148668571060[265] = 0.0;
   out_8044174148668571060[266] = 1.0;
   out_8044174148668571060[267] = 0.0;
   out_8044174148668571060[268] = 0.0;
   out_8044174148668571060[269] = 0.0;
   out_8044174148668571060[270] = 0.0;
   out_8044174148668571060[271] = 0.0;
   out_8044174148668571060[272] = 0.0;
   out_8044174148668571060[273] = 0.0;
   out_8044174148668571060[274] = 0.0;
   out_8044174148668571060[275] = 0.0;
   out_8044174148668571060[276] = 0.0;
   out_8044174148668571060[277] = 0.0;
   out_8044174148668571060[278] = 0.0;
   out_8044174148668571060[279] = 0.0;
   out_8044174148668571060[280] = 0.0;
   out_8044174148668571060[281] = 0.0;
   out_8044174148668571060[282] = 0.0;
   out_8044174148668571060[283] = 0.0;
   out_8044174148668571060[284] = 0.0;
   out_8044174148668571060[285] = 1.0;
   out_8044174148668571060[286] = 0.0;
   out_8044174148668571060[287] = 0.0;
   out_8044174148668571060[288] = 0.0;
   out_8044174148668571060[289] = 0.0;
   out_8044174148668571060[290] = 0.0;
   out_8044174148668571060[291] = 0.0;
   out_8044174148668571060[292] = 0.0;
   out_8044174148668571060[293] = 0.0;
   out_8044174148668571060[294] = 0.0;
   out_8044174148668571060[295] = 0.0;
   out_8044174148668571060[296] = 0.0;
   out_8044174148668571060[297] = 0.0;
   out_8044174148668571060[298] = 0.0;
   out_8044174148668571060[299] = 0.0;
   out_8044174148668571060[300] = 0.0;
   out_8044174148668571060[301] = 0.0;
   out_8044174148668571060[302] = 0.0;
   out_8044174148668571060[303] = 0.0;
   out_8044174148668571060[304] = 1.0;
   out_8044174148668571060[305] = 0.0;
   out_8044174148668571060[306] = 0.0;
   out_8044174148668571060[307] = 0.0;
   out_8044174148668571060[308] = 0.0;
   out_8044174148668571060[309] = 0.0;
   out_8044174148668571060[310] = 0.0;
   out_8044174148668571060[311] = 0.0;
   out_8044174148668571060[312] = 0.0;
   out_8044174148668571060[313] = 0.0;
   out_8044174148668571060[314] = 0.0;
   out_8044174148668571060[315] = 0.0;
   out_8044174148668571060[316] = 0.0;
   out_8044174148668571060[317] = 0.0;
   out_8044174148668571060[318] = 0.0;
   out_8044174148668571060[319] = 0.0;
   out_8044174148668571060[320] = 0.0;
   out_8044174148668571060[321] = 0.0;
   out_8044174148668571060[322] = 0.0;
   out_8044174148668571060[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_509214913504947314) {
   out_509214913504947314[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_509214913504947314[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_509214913504947314[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_509214913504947314[3] = dt*state[12] + state[3];
   out_509214913504947314[4] = dt*state[13] + state[4];
   out_509214913504947314[5] = dt*state[14] + state[5];
   out_509214913504947314[6] = state[6];
   out_509214913504947314[7] = state[7];
   out_509214913504947314[8] = state[8];
   out_509214913504947314[9] = state[9];
   out_509214913504947314[10] = state[10];
   out_509214913504947314[11] = state[11];
   out_509214913504947314[12] = state[12];
   out_509214913504947314[13] = state[13];
   out_509214913504947314[14] = state[14];
   out_509214913504947314[15] = state[15];
   out_509214913504947314[16] = state[16];
   out_509214913504947314[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4927192891870145475) {
   out_4927192891870145475[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4927192891870145475[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4927192891870145475[2] = 0;
   out_4927192891870145475[3] = 0;
   out_4927192891870145475[4] = 0;
   out_4927192891870145475[5] = 0;
   out_4927192891870145475[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4927192891870145475[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4927192891870145475[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4927192891870145475[9] = 0;
   out_4927192891870145475[10] = 0;
   out_4927192891870145475[11] = 0;
   out_4927192891870145475[12] = 0;
   out_4927192891870145475[13] = 0;
   out_4927192891870145475[14] = 0;
   out_4927192891870145475[15] = 0;
   out_4927192891870145475[16] = 0;
   out_4927192891870145475[17] = 0;
   out_4927192891870145475[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4927192891870145475[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4927192891870145475[20] = 0;
   out_4927192891870145475[21] = 0;
   out_4927192891870145475[22] = 0;
   out_4927192891870145475[23] = 0;
   out_4927192891870145475[24] = 0;
   out_4927192891870145475[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4927192891870145475[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4927192891870145475[27] = 0;
   out_4927192891870145475[28] = 0;
   out_4927192891870145475[29] = 0;
   out_4927192891870145475[30] = 0;
   out_4927192891870145475[31] = 0;
   out_4927192891870145475[32] = 0;
   out_4927192891870145475[33] = 0;
   out_4927192891870145475[34] = 0;
   out_4927192891870145475[35] = 0;
   out_4927192891870145475[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4927192891870145475[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4927192891870145475[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4927192891870145475[39] = 0;
   out_4927192891870145475[40] = 0;
   out_4927192891870145475[41] = 0;
   out_4927192891870145475[42] = 0;
   out_4927192891870145475[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4927192891870145475[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4927192891870145475[45] = 0;
   out_4927192891870145475[46] = 0;
   out_4927192891870145475[47] = 0;
   out_4927192891870145475[48] = 0;
   out_4927192891870145475[49] = 0;
   out_4927192891870145475[50] = 0;
   out_4927192891870145475[51] = 0;
   out_4927192891870145475[52] = 0;
   out_4927192891870145475[53] = 0;
   out_4927192891870145475[54] = 0;
   out_4927192891870145475[55] = 0;
   out_4927192891870145475[56] = 0;
   out_4927192891870145475[57] = 1;
   out_4927192891870145475[58] = 0;
   out_4927192891870145475[59] = 0;
   out_4927192891870145475[60] = 0;
   out_4927192891870145475[61] = 0;
   out_4927192891870145475[62] = 0;
   out_4927192891870145475[63] = 0;
   out_4927192891870145475[64] = 0;
   out_4927192891870145475[65] = 0;
   out_4927192891870145475[66] = dt;
   out_4927192891870145475[67] = 0;
   out_4927192891870145475[68] = 0;
   out_4927192891870145475[69] = 0;
   out_4927192891870145475[70] = 0;
   out_4927192891870145475[71] = 0;
   out_4927192891870145475[72] = 0;
   out_4927192891870145475[73] = 0;
   out_4927192891870145475[74] = 0;
   out_4927192891870145475[75] = 0;
   out_4927192891870145475[76] = 1;
   out_4927192891870145475[77] = 0;
   out_4927192891870145475[78] = 0;
   out_4927192891870145475[79] = 0;
   out_4927192891870145475[80] = 0;
   out_4927192891870145475[81] = 0;
   out_4927192891870145475[82] = 0;
   out_4927192891870145475[83] = 0;
   out_4927192891870145475[84] = 0;
   out_4927192891870145475[85] = dt;
   out_4927192891870145475[86] = 0;
   out_4927192891870145475[87] = 0;
   out_4927192891870145475[88] = 0;
   out_4927192891870145475[89] = 0;
   out_4927192891870145475[90] = 0;
   out_4927192891870145475[91] = 0;
   out_4927192891870145475[92] = 0;
   out_4927192891870145475[93] = 0;
   out_4927192891870145475[94] = 0;
   out_4927192891870145475[95] = 1;
   out_4927192891870145475[96] = 0;
   out_4927192891870145475[97] = 0;
   out_4927192891870145475[98] = 0;
   out_4927192891870145475[99] = 0;
   out_4927192891870145475[100] = 0;
   out_4927192891870145475[101] = 0;
   out_4927192891870145475[102] = 0;
   out_4927192891870145475[103] = 0;
   out_4927192891870145475[104] = dt;
   out_4927192891870145475[105] = 0;
   out_4927192891870145475[106] = 0;
   out_4927192891870145475[107] = 0;
   out_4927192891870145475[108] = 0;
   out_4927192891870145475[109] = 0;
   out_4927192891870145475[110] = 0;
   out_4927192891870145475[111] = 0;
   out_4927192891870145475[112] = 0;
   out_4927192891870145475[113] = 0;
   out_4927192891870145475[114] = 1;
   out_4927192891870145475[115] = 0;
   out_4927192891870145475[116] = 0;
   out_4927192891870145475[117] = 0;
   out_4927192891870145475[118] = 0;
   out_4927192891870145475[119] = 0;
   out_4927192891870145475[120] = 0;
   out_4927192891870145475[121] = 0;
   out_4927192891870145475[122] = 0;
   out_4927192891870145475[123] = 0;
   out_4927192891870145475[124] = 0;
   out_4927192891870145475[125] = 0;
   out_4927192891870145475[126] = 0;
   out_4927192891870145475[127] = 0;
   out_4927192891870145475[128] = 0;
   out_4927192891870145475[129] = 0;
   out_4927192891870145475[130] = 0;
   out_4927192891870145475[131] = 0;
   out_4927192891870145475[132] = 0;
   out_4927192891870145475[133] = 1;
   out_4927192891870145475[134] = 0;
   out_4927192891870145475[135] = 0;
   out_4927192891870145475[136] = 0;
   out_4927192891870145475[137] = 0;
   out_4927192891870145475[138] = 0;
   out_4927192891870145475[139] = 0;
   out_4927192891870145475[140] = 0;
   out_4927192891870145475[141] = 0;
   out_4927192891870145475[142] = 0;
   out_4927192891870145475[143] = 0;
   out_4927192891870145475[144] = 0;
   out_4927192891870145475[145] = 0;
   out_4927192891870145475[146] = 0;
   out_4927192891870145475[147] = 0;
   out_4927192891870145475[148] = 0;
   out_4927192891870145475[149] = 0;
   out_4927192891870145475[150] = 0;
   out_4927192891870145475[151] = 0;
   out_4927192891870145475[152] = 1;
   out_4927192891870145475[153] = 0;
   out_4927192891870145475[154] = 0;
   out_4927192891870145475[155] = 0;
   out_4927192891870145475[156] = 0;
   out_4927192891870145475[157] = 0;
   out_4927192891870145475[158] = 0;
   out_4927192891870145475[159] = 0;
   out_4927192891870145475[160] = 0;
   out_4927192891870145475[161] = 0;
   out_4927192891870145475[162] = 0;
   out_4927192891870145475[163] = 0;
   out_4927192891870145475[164] = 0;
   out_4927192891870145475[165] = 0;
   out_4927192891870145475[166] = 0;
   out_4927192891870145475[167] = 0;
   out_4927192891870145475[168] = 0;
   out_4927192891870145475[169] = 0;
   out_4927192891870145475[170] = 0;
   out_4927192891870145475[171] = 1;
   out_4927192891870145475[172] = 0;
   out_4927192891870145475[173] = 0;
   out_4927192891870145475[174] = 0;
   out_4927192891870145475[175] = 0;
   out_4927192891870145475[176] = 0;
   out_4927192891870145475[177] = 0;
   out_4927192891870145475[178] = 0;
   out_4927192891870145475[179] = 0;
   out_4927192891870145475[180] = 0;
   out_4927192891870145475[181] = 0;
   out_4927192891870145475[182] = 0;
   out_4927192891870145475[183] = 0;
   out_4927192891870145475[184] = 0;
   out_4927192891870145475[185] = 0;
   out_4927192891870145475[186] = 0;
   out_4927192891870145475[187] = 0;
   out_4927192891870145475[188] = 0;
   out_4927192891870145475[189] = 0;
   out_4927192891870145475[190] = 1;
   out_4927192891870145475[191] = 0;
   out_4927192891870145475[192] = 0;
   out_4927192891870145475[193] = 0;
   out_4927192891870145475[194] = 0;
   out_4927192891870145475[195] = 0;
   out_4927192891870145475[196] = 0;
   out_4927192891870145475[197] = 0;
   out_4927192891870145475[198] = 0;
   out_4927192891870145475[199] = 0;
   out_4927192891870145475[200] = 0;
   out_4927192891870145475[201] = 0;
   out_4927192891870145475[202] = 0;
   out_4927192891870145475[203] = 0;
   out_4927192891870145475[204] = 0;
   out_4927192891870145475[205] = 0;
   out_4927192891870145475[206] = 0;
   out_4927192891870145475[207] = 0;
   out_4927192891870145475[208] = 0;
   out_4927192891870145475[209] = 1;
   out_4927192891870145475[210] = 0;
   out_4927192891870145475[211] = 0;
   out_4927192891870145475[212] = 0;
   out_4927192891870145475[213] = 0;
   out_4927192891870145475[214] = 0;
   out_4927192891870145475[215] = 0;
   out_4927192891870145475[216] = 0;
   out_4927192891870145475[217] = 0;
   out_4927192891870145475[218] = 0;
   out_4927192891870145475[219] = 0;
   out_4927192891870145475[220] = 0;
   out_4927192891870145475[221] = 0;
   out_4927192891870145475[222] = 0;
   out_4927192891870145475[223] = 0;
   out_4927192891870145475[224] = 0;
   out_4927192891870145475[225] = 0;
   out_4927192891870145475[226] = 0;
   out_4927192891870145475[227] = 0;
   out_4927192891870145475[228] = 1;
   out_4927192891870145475[229] = 0;
   out_4927192891870145475[230] = 0;
   out_4927192891870145475[231] = 0;
   out_4927192891870145475[232] = 0;
   out_4927192891870145475[233] = 0;
   out_4927192891870145475[234] = 0;
   out_4927192891870145475[235] = 0;
   out_4927192891870145475[236] = 0;
   out_4927192891870145475[237] = 0;
   out_4927192891870145475[238] = 0;
   out_4927192891870145475[239] = 0;
   out_4927192891870145475[240] = 0;
   out_4927192891870145475[241] = 0;
   out_4927192891870145475[242] = 0;
   out_4927192891870145475[243] = 0;
   out_4927192891870145475[244] = 0;
   out_4927192891870145475[245] = 0;
   out_4927192891870145475[246] = 0;
   out_4927192891870145475[247] = 1;
   out_4927192891870145475[248] = 0;
   out_4927192891870145475[249] = 0;
   out_4927192891870145475[250] = 0;
   out_4927192891870145475[251] = 0;
   out_4927192891870145475[252] = 0;
   out_4927192891870145475[253] = 0;
   out_4927192891870145475[254] = 0;
   out_4927192891870145475[255] = 0;
   out_4927192891870145475[256] = 0;
   out_4927192891870145475[257] = 0;
   out_4927192891870145475[258] = 0;
   out_4927192891870145475[259] = 0;
   out_4927192891870145475[260] = 0;
   out_4927192891870145475[261] = 0;
   out_4927192891870145475[262] = 0;
   out_4927192891870145475[263] = 0;
   out_4927192891870145475[264] = 0;
   out_4927192891870145475[265] = 0;
   out_4927192891870145475[266] = 1;
   out_4927192891870145475[267] = 0;
   out_4927192891870145475[268] = 0;
   out_4927192891870145475[269] = 0;
   out_4927192891870145475[270] = 0;
   out_4927192891870145475[271] = 0;
   out_4927192891870145475[272] = 0;
   out_4927192891870145475[273] = 0;
   out_4927192891870145475[274] = 0;
   out_4927192891870145475[275] = 0;
   out_4927192891870145475[276] = 0;
   out_4927192891870145475[277] = 0;
   out_4927192891870145475[278] = 0;
   out_4927192891870145475[279] = 0;
   out_4927192891870145475[280] = 0;
   out_4927192891870145475[281] = 0;
   out_4927192891870145475[282] = 0;
   out_4927192891870145475[283] = 0;
   out_4927192891870145475[284] = 0;
   out_4927192891870145475[285] = 1;
   out_4927192891870145475[286] = 0;
   out_4927192891870145475[287] = 0;
   out_4927192891870145475[288] = 0;
   out_4927192891870145475[289] = 0;
   out_4927192891870145475[290] = 0;
   out_4927192891870145475[291] = 0;
   out_4927192891870145475[292] = 0;
   out_4927192891870145475[293] = 0;
   out_4927192891870145475[294] = 0;
   out_4927192891870145475[295] = 0;
   out_4927192891870145475[296] = 0;
   out_4927192891870145475[297] = 0;
   out_4927192891870145475[298] = 0;
   out_4927192891870145475[299] = 0;
   out_4927192891870145475[300] = 0;
   out_4927192891870145475[301] = 0;
   out_4927192891870145475[302] = 0;
   out_4927192891870145475[303] = 0;
   out_4927192891870145475[304] = 1;
   out_4927192891870145475[305] = 0;
   out_4927192891870145475[306] = 0;
   out_4927192891870145475[307] = 0;
   out_4927192891870145475[308] = 0;
   out_4927192891870145475[309] = 0;
   out_4927192891870145475[310] = 0;
   out_4927192891870145475[311] = 0;
   out_4927192891870145475[312] = 0;
   out_4927192891870145475[313] = 0;
   out_4927192891870145475[314] = 0;
   out_4927192891870145475[315] = 0;
   out_4927192891870145475[316] = 0;
   out_4927192891870145475[317] = 0;
   out_4927192891870145475[318] = 0;
   out_4927192891870145475[319] = 0;
   out_4927192891870145475[320] = 0;
   out_4927192891870145475[321] = 0;
   out_4927192891870145475[322] = 0;
   out_4927192891870145475[323] = 1;
}
void h_4(double *state, double *unused, double *out_694167901848750082) {
   out_694167901848750082[0] = state[6] + state[9];
   out_694167901848750082[1] = state[7] + state[10];
   out_694167901848750082[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7290013146613858453) {
   out_7290013146613858453[0] = 0;
   out_7290013146613858453[1] = 0;
   out_7290013146613858453[2] = 0;
   out_7290013146613858453[3] = 0;
   out_7290013146613858453[4] = 0;
   out_7290013146613858453[5] = 0;
   out_7290013146613858453[6] = 1;
   out_7290013146613858453[7] = 0;
   out_7290013146613858453[8] = 0;
   out_7290013146613858453[9] = 1;
   out_7290013146613858453[10] = 0;
   out_7290013146613858453[11] = 0;
   out_7290013146613858453[12] = 0;
   out_7290013146613858453[13] = 0;
   out_7290013146613858453[14] = 0;
   out_7290013146613858453[15] = 0;
   out_7290013146613858453[16] = 0;
   out_7290013146613858453[17] = 0;
   out_7290013146613858453[18] = 0;
   out_7290013146613858453[19] = 0;
   out_7290013146613858453[20] = 0;
   out_7290013146613858453[21] = 0;
   out_7290013146613858453[22] = 0;
   out_7290013146613858453[23] = 0;
   out_7290013146613858453[24] = 0;
   out_7290013146613858453[25] = 1;
   out_7290013146613858453[26] = 0;
   out_7290013146613858453[27] = 0;
   out_7290013146613858453[28] = 1;
   out_7290013146613858453[29] = 0;
   out_7290013146613858453[30] = 0;
   out_7290013146613858453[31] = 0;
   out_7290013146613858453[32] = 0;
   out_7290013146613858453[33] = 0;
   out_7290013146613858453[34] = 0;
   out_7290013146613858453[35] = 0;
   out_7290013146613858453[36] = 0;
   out_7290013146613858453[37] = 0;
   out_7290013146613858453[38] = 0;
   out_7290013146613858453[39] = 0;
   out_7290013146613858453[40] = 0;
   out_7290013146613858453[41] = 0;
   out_7290013146613858453[42] = 0;
   out_7290013146613858453[43] = 0;
   out_7290013146613858453[44] = 1;
   out_7290013146613858453[45] = 0;
   out_7290013146613858453[46] = 0;
   out_7290013146613858453[47] = 1;
   out_7290013146613858453[48] = 0;
   out_7290013146613858453[49] = 0;
   out_7290013146613858453[50] = 0;
   out_7290013146613858453[51] = 0;
   out_7290013146613858453[52] = 0;
   out_7290013146613858453[53] = 0;
}
void h_10(double *state, double *unused, double *out_5760027499613918255) {
   out_5760027499613918255[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5760027499613918255[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5760027499613918255[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5891931083183346428) {
   out_5891931083183346428[0] = 0;
   out_5891931083183346428[1] = 9.8100000000000005*cos(state[1]);
   out_5891931083183346428[2] = 0;
   out_5891931083183346428[3] = 0;
   out_5891931083183346428[4] = -state[8];
   out_5891931083183346428[5] = state[7];
   out_5891931083183346428[6] = 0;
   out_5891931083183346428[7] = state[5];
   out_5891931083183346428[8] = -state[4];
   out_5891931083183346428[9] = 0;
   out_5891931083183346428[10] = 0;
   out_5891931083183346428[11] = 0;
   out_5891931083183346428[12] = 1;
   out_5891931083183346428[13] = 0;
   out_5891931083183346428[14] = 0;
   out_5891931083183346428[15] = 1;
   out_5891931083183346428[16] = 0;
   out_5891931083183346428[17] = 0;
   out_5891931083183346428[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5891931083183346428[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5891931083183346428[20] = 0;
   out_5891931083183346428[21] = state[8];
   out_5891931083183346428[22] = 0;
   out_5891931083183346428[23] = -state[6];
   out_5891931083183346428[24] = -state[5];
   out_5891931083183346428[25] = 0;
   out_5891931083183346428[26] = state[3];
   out_5891931083183346428[27] = 0;
   out_5891931083183346428[28] = 0;
   out_5891931083183346428[29] = 0;
   out_5891931083183346428[30] = 0;
   out_5891931083183346428[31] = 1;
   out_5891931083183346428[32] = 0;
   out_5891931083183346428[33] = 0;
   out_5891931083183346428[34] = 1;
   out_5891931083183346428[35] = 0;
   out_5891931083183346428[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5891931083183346428[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5891931083183346428[38] = 0;
   out_5891931083183346428[39] = -state[7];
   out_5891931083183346428[40] = state[6];
   out_5891931083183346428[41] = 0;
   out_5891931083183346428[42] = state[4];
   out_5891931083183346428[43] = -state[3];
   out_5891931083183346428[44] = 0;
   out_5891931083183346428[45] = 0;
   out_5891931083183346428[46] = 0;
   out_5891931083183346428[47] = 0;
   out_5891931083183346428[48] = 0;
   out_5891931083183346428[49] = 0;
   out_5891931083183346428[50] = 1;
   out_5891931083183346428[51] = 0;
   out_5891931083183346428[52] = 0;
   out_5891931083183346428[53] = 1;
}
void h_13(double *state, double *unused, double *out_9070928996461222622) {
   out_9070928996461222622[0] = state[3];
   out_9070928996461222622[1] = state[4];
   out_9070928996461222622[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7322975463793169139) {
   out_7322975463793169139[0] = 0;
   out_7322975463793169139[1] = 0;
   out_7322975463793169139[2] = 0;
   out_7322975463793169139[3] = 1;
   out_7322975463793169139[4] = 0;
   out_7322975463793169139[5] = 0;
   out_7322975463793169139[6] = 0;
   out_7322975463793169139[7] = 0;
   out_7322975463793169139[8] = 0;
   out_7322975463793169139[9] = 0;
   out_7322975463793169139[10] = 0;
   out_7322975463793169139[11] = 0;
   out_7322975463793169139[12] = 0;
   out_7322975463793169139[13] = 0;
   out_7322975463793169139[14] = 0;
   out_7322975463793169139[15] = 0;
   out_7322975463793169139[16] = 0;
   out_7322975463793169139[17] = 0;
   out_7322975463793169139[18] = 0;
   out_7322975463793169139[19] = 0;
   out_7322975463793169139[20] = 0;
   out_7322975463793169139[21] = 0;
   out_7322975463793169139[22] = 1;
   out_7322975463793169139[23] = 0;
   out_7322975463793169139[24] = 0;
   out_7322975463793169139[25] = 0;
   out_7322975463793169139[26] = 0;
   out_7322975463793169139[27] = 0;
   out_7322975463793169139[28] = 0;
   out_7322975463793169139[29] = 0;
   out_7322975463793169139[30] = 0;
   out_7322975463793169139[31] = 0;
   out_7322975463793169139[32] = 0;
   out_7322975463793169139[33] = 0;
   out_7322975463793169139[34] = 0;
   out_7322975463793169139[35] = 0;
   out_7322975463793169139[36] = 0;
   out_7322975463793169139[37] = 0;
   out_7322975463793169139[38] = 0;
   out_7322975463793169139[39] = 0;
   out_7322975463793169139[40] = 0;
   out_7322975463793169139[41] = 1;
   out_7322975463793169139[42] = 0;
   out_7322975463793169139[43] = 0;
   out_7322975463793169139[44] = 0;
   out_7322975463793169139[45] = 0;
   out_7322975463793169139[46] = 0;
   out_7322975463793169139[47] = 0;
   out_7322975463793169139[48] = 0;
   out_7322975463793169139[49] = 0;
   out_7322975463793169139[50] = 0;
   out_7322975463793169139[51] = 0;
   out_7322975463793169139[52] = 0;
   out_7322975463793169139[53] = 0;
}
void h_14(double *state, double *unused, double *out_297879652021367590) {
   out_297879652021367590[0] = state[6];
   out_297879652021367590[1] = state[7];
   out_297879652021367590[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8073942494800320867) {
   out_8073942494800320867[0] = 0;
   out_8073942494800320867[1] = 0;
   out_8073942494800320867[2] = 0;
   out_8073942494800320867[3] = 0;
   out_8073942494800320867[4] = 0;
   out_8073942494800320867[5] = 0;
   out_8073942494800320867[6] = 1;
   out_8073942494800320867[7] = 0;
   out_8073942494800320867[8] = 0;
   out_8073942494800320867[9] = 0;
   out_8073942494800320867[10] = 0;
   out_8073942494800320867[11] = 0;
   out_8073942494800320867[12] = 0;
   out_8073942494800320867[13] = 0;
   out_8073942494800320867[14] = 0;
   out_8073942494800320867[15] = 0;
   out_8073942494800320867[16] = 0;
   out_8073942494800320867[17] = 0;
   out_8073942494800320867[18] = 0;
   out_8073942494800320867[19] = 0;
   out_8073942494800320867[20] = 0;
   out_8073942494800320867[21] = 0;
   out_8073942494800320867[22] = 0;
   out_8073942494800320867[23] = 0;
   out_8073942494800320867[24] = 0;
   out_8073942494800320867[25] = 1;
   out_8073942494800320867[26] = 0;
   out_8073942494800320867[27] = 0;
   out_8073942494800320867[28] = 0;
   out_8073942494800320867[29] = 0;
   out_8073942494800320867[30] = 0;
   out_8073942494800320867[31] = 0;
   out_8073942494800320867[32] = 0;
   out_8073942494800320867[33] = 0;
   out_8073942494800320867[34] = 0;
   out_8073942494800320867[35] = 0;
   out_8073942494800320867[36] = 0;
   out_8073942494800320867[37] = 0;
   out_8073942494800320867[38] = 0;
   out_8073942494800320867[39] = 0;
   out_8073942494800320867[40] = 0;
   out_8073942494800320867[41] = 0;
   out_8073942494800320867[42] = 0;
   out_8073942494800320867[43] = 0;
   out_8073942494800320867[44] = 1;
   out_8073942494800320867[45] = 0;
   out_8073942494800320867[46] = 0;
   out_8073942494800320867[47] = 0;
   out_8073942494800320867[48] = 0;
   out_8073942494800320867[49] = 0;
   out_8073942494800320867[50] = 0;
   out_8073942494800320867[51] = 0;
   out_8073942494800320867[52] = 0;
   out_8073942494800320867[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3246138991131647202) {
  err_fun(nom_x, delta_x, out_3246138991131647202);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4007822862672909290) {
  inv_err_fun(nom_x, true_x, out_4007822862672909290);
}
void pose_H_mod_fun(double *state, double *out_8044174148668571060) {
  H_mod_fun(state, out_8044174148668571060);
}
void pose_f_fun(double *state, double dt, double *out_509214913504947314) {
  f_fun(state,  dt, out_509214913504947314);
}
void pose_F_fun(double *state, double dt, double *out_4927192891870145475) {
  F_fun(state,  dt, out_4927192891870145475);
}
void pose_h_4(double *state, double *unused, double *out_694167901848750082) {
  h_4(state, unused, out_694167901848750082);
}
void pose_H_4(double *state, double *unused, double *out_7290013146613858453) {
  H_4(state, unused, out_7290013146613858453);
}
void pose_h_10(double *state, double *unused, double *out_5760027499613918255) {
  h_10(state, unused, out_5760027499613918255);
}
void pose_H_10(double *state, double *unused, double *out_5891931083183346428) {
  H_10(state, unused, out_5891931083183346428);
}
void pose_h_13(double *state, double *unused, double *out_9070928996461222622) {
  h_13(state, unused, out_9070928996461222622);
}
void pose_H_13(double *state, double *unused, double *out_7322975463793169139) {
  H_13(state, unused, out_7322975463793169139);
}
void pose_h_14(double *state, double *unused, double *out_297879652021367590) {
  h_14(state, unused, out_297879652021367590);
}
void pose_H_14(double *state, double *unused, double *out_8073942494800320867) {
  H_14(state, unused, out_8073942494800320867);
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
