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
void err_fun(double *nom_x, double *delta_x, double *out_3332094354178799206) {
   out_3332094354178799206[0] = delta_x[0] + nom_x[0];
   out_3332094354178799206[1] = delta_x[1] + nom_x[1];
   out_3332094354178799206[2] = delta_x[2] + nom_x[2];
   out_3332094354178799206[3] = delta_x[3] + nom_x[3];
   out_3332094354178799206[4] = delta_x[4] + nom_x[4];
   out_3332094354178799206[5] = delta_x[5] + nom_x[5];
   out_3332094354178799206[6] = delta_x[6] + nom_x[6];
   out_3332094354178799206[7] = delta_x[7] + nom_x[7];
   out_3332094354178799206[8] = delta_x[8] + nom_x[8];
   out_3332094354178799206[9] = delta_x[9] + nom_x[9];
   out_3332094354178799206[10] = delta_x[10] + nom_x[10];
   out_3332094354178799206[11] = delta_x[11] + nom_x[11];
   out_3332094354178799206[12] = delta_x[12] + nom_x[12];
   out_3332094354178799206[13] = delta_x[13] + nom_x[13];
   out_3332094354178799206[14] = delta_x[14] + nom_x[14];
   out_3332094354178799206[15] = delta_x[15] + nom_x[15];
   out_3332094354178799206[16] = delta_x[16] + nom_x[16];
   out_3332094354178799206[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6787681857429762222) {
   out_6787681857429762222[0] = -nom_x[0] + true_x[0];
   out_6787681857429762222[1] = -nom_x[1] + true_x[1];
   out_6787681857429762222[2] = -nom_x[2] + true_x[2];
   out_6787681857429762222[3] = -nom_x[3] + true_x[3];
   out_6787681857429762222[4] = -nom_x[4] + true_x[4];
   out_6787681857429762222[5] = -nom_x[5] + true_x[5];
   out_6787681857429762222[6] = -nom_x[6] + true_x[6];
   out_6787681857429762222[7] = -nom_x[7] + true_x[7];
   out_6787681857429762222[8] = -nom_x[8] + true_x[8];
   out_6787681857429762222[9] = -nom_x[9] + true_x[9];
   out_6787681857429762222[10] = -nom_x[10] + true_x[10];
   out_6787681857429762222[11] = -nom_x[11] + true_x[11];
   out_6787681857429762222[12] = -nom_x[12] + true_x[12];
   out_6787681857429762222[13] = -nom_x[13] + true_x[13];
   out_6787681857429762222[14] = -nom_x[14] + true_x[14];
   out_6787681857429762222[15] = -nom_x[15] + true_x[15];
   out_6787681857429762222[16] = -nom_x[16] + true_x[16];
   out_6787681857429762222[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_699928149424030002) {
   out_699928149424030002[0] = 1.0;
   out_699928149424030002[1] = 0.0;
   out_699928149424030002[2] = 0.0;
   out_699928149424030002[3] = 0.0;
   out_699928149424030002[4] = 0.0;
   out_699928149424030002[5] = 0.0;
   out_699928149424030002[6] = 0.0;
   out_699928149424030002[7] = 0.0;
   out_699928149424030002[8] = 0.0;
   out_699928149424030002[9] = 0.0;
   out_699928149424030002[10] = 0.0;
   out_699928149424030002[11] = 0.0;
   out_699928149424030002[12] = 0.0;
   out_699928149424030002[13] = 0.0;
   out_699928149424030002[14] = 0.0;
   out_699928149424030002[15] = 0.0;
   out_699928149424030002[16] = 0.0;
   out_699928149424030002[17] = 0.0;
   out_699928149424030002[18] = 0.0;
   out_699928149424030002[19] = 1.0;
   out_699928149424030002[20] = 0.0;
   out_699928149424030002[21] = 0.0;
   out_699928149424030002[22] = 0.0;
   out_699928149424030002[23] = 0.0;
   out_699928149424030002[24] = 0.0;
   out_699928149424030002[25] = 0.0;
   out_699928149424030002[26] = 0.0;
   out_699928149424030002[27] = 0.0;
   out_699928149424030002[28] = 0.0;
   out_699928149424030002[29] = 0.0;
   out_699928149424030002[30] = 0.0;
   out_699928149424030002[31] = 0.0;
   out_699928149424030002[32] = 0.0;
   out_699928149424030002[33] = 0.0;
   out_699928149424030002[34] = 0.0;
   out_699928149424030002[35] = 0.0;
   out_699928149424030002[36] = 0.0;
   out_699928149424030002[37] = 0.0;
   out_699928149424030002[38] = 1.0;
   out_699928149424030002[39] = 0.0;
   out_699928149424030002[40] = 0.0;
   out_699928149424030002[41] = 0.0;
   out_699928149424030002[42] = 0.0;
   out_699928149424030002[43] = 0.0;
   out_699928149424030002[44] = 0.0;
   out_699928149424030002[45] = 0.0;
   out_699928149424030002[46] = 0.0;
   out_699928149424030002[47] = 0.0;
   out_699928149424030002[48] = 0.0;
   out_699928149424030002[49] = 0.0;
   out_699928149424030002[50] = 0.0;
   out_699928149424030002[51] = 0.0;
   out_699928149424030002[52] = 0.0;
   out_699928149424030002[53] = 0.0;
   out_699928149424030002[54] = 0.0;
   out_699928149424030002[55] = 0.0;
   out_699928149424030002[56] = 0.0;
   out_699928149424030002[57] = 1.0;
   out_699928149424030002[58] = 0.0;
   out_699928149424030002[59] = 0.0;
   out_699928149424030002[60] = 0.0;
   out_699928149424030002[61] = 0.0;
   out_699928149424030002[62] = 0.0;
   out_699928149424030002[63] = 0.0;
   out_699928149424030002[64] = 0.0;
   out_699928149424030002[65] = 0.0;
   out_699928149424030002[66] = 0.0;
   out_699928149424030002[67] = 0.0;
   out_699928149424030002[68] = 0.0;
   out_699928149424030002[69] = 0.0;
   out_699928149424030002[70] = 0.0;
   out_699928149424030002[71] = 0.0;
   out_699928149424030002[72] = 0.0;
   out_699928149424030002[73] = 0.0;
   out_699928149424030002[74] = 0.0;
   out_699928149424030002[75] = 0.0;
   out_699928149424030002[76] = 1.0;
   out_699928149424030002[77] = 0.0;
   out_699928149424030002[78] = 0.0;
   out_699928149424030002[79] = 0.0;
   out_699928149424030002[80] = 0.0;
   out_699928149424030002[81] = 0.0;
   out_699928149424030002[82] = 0.0;
   out_699928149424030002[83] = 0.0;
   out_699928149424030002[84] = 0.0;
   out_699928149424030002[85] = 0.0;
   out_699928149424030002[86] = 0.0;
   out_699928149424030002[87] = 0.0;
   out_699928149424030002[88] = 0.0;
   out_699928149424030002[89] = 0.0;
   out_699928149424030002[90] = 0.0;
   out_699928149424030002[91] = 0.0;
   out_699928149424030002[92] = 0.0;
   out_699928149424030002[93] = 0.0;
   out_699928149424030002[94] = 0.0;
   out_699928149424030002[95] = 1.0;
   out_699928149424030002[96] = 0.0;
   out_699928149424030002[97] = 0.0;
   out_699928149424030002[98] = 0.0;
   out_699928149424030002[99] = 0.0;
   out_699928149424030002[100] = 0.0;
   out_699928149424030002[101] = 0.0;
   out_699928149424030002[102] = 0.0;
   out_699928149424030002[103] = 0.0;
   out_699928149424030002[104] = 0.0;
   out_699928149424030002[105] = 0.0;
   out_699928149424030002[106] = 0.0;
   out_699928149424030002[107] = 0.0;
   out_699928149424030002[108] = 0.0;
   out_699928149424030002[109] = 0.0;
   out_699928149424030002[110] = 0.0;
   out_699928149424030002[111] = 0.0;
   out_699928149424030002[112] = 0.0;
   out_699928149424030002[113] = 0.0;
   out_699928149424030002[114] = 1.0;
   out_699928149424030002[115] = 0.0;
   out_699928149424030002[116] = 0.0;
   out_699928149424030002[117] = 0.0;
   out_699928149424030002[118] = 0.0;
   out_699928149424030002[119] = 0.0;
   out_699928149424030002[120] = 0.0;
   out_699928149424030002[121] = 0.0;
   out_699928149424030002[122] = 0.0;
   out_699928149424030002[123] = 0.0;
   out_699928149424030002[124] = 0.0;
   out_699928149424030002[125] = 0.0;
   out_699928149424030002[126] = 0.0;
   out_699928149424030002[127] = 0.0;
   out_699928149424030002[128] = 0.0;
   out_699928149424030002[129] = 0.0;
   out_699928149424030002[130] = 0.0;
   out_699928149424030002[131] = 0.0;
   out_699928149424030002[132] = 0.0;
   out_699928149424030002[133] = 1.0;
   out_699928149424030002[134] = 0.0;
   out_699928149424030002[135] = 0.0;
   out_699928149424030002[136] = 0.0;
   out_699928149424030002[137] = 0.0;
   out_699928149424030002[138] = 0.0;
   out_699928149424030002[139] = 0.0;
   out_699928149424030002[140] = 0.0;
   out_699928149424030002[141] = 0.0;
   out_699928149424030002[142] = 0.0;
   out_699928149424030002[143] = 0.0;
   out_699928149424030002[144] = 0.0;
   out_699928149424030002[145] = 0.0;
   out_699928149424030002[146] = 0.0;
   out_699928149424030002[147] = 0.0;
   out_699928149424030002[148] = 0.0;
   out_699928149424030002[149] = 0.0;
   out_699928149424030002[150] = 0.0;
   out_699928149424030002[151] = 0.0;
   out_699928149424030002[152] = 1.0;
   out_699928149424030002[153] = 0.0;
   out_699928149424030002[154] = 0.0;
   out_699928149424030002[155] = 0.0;
   out_699928149424030002[156] = 0.0;
   out_699928149424030002[157] = 0.0;
   out_699928149424030002[158] = 0.0;
   out_699928149424030002[159] = 0.0;
   out_699928149424030002[160] = 0.0;
   out_699928149424030002[161] = 0.0;
   out_699928149424030002[162] = 0.0;
   out_699928149424030002[163] = 0.0;
   out_699928149424030002[164] = 0.0;
   out_699928149424030002[165] = 0.0;
   out_699928149424030002[166] = 0.0;
   out_699928149424030002[167] = 0.0;
   out_699928149424030002[168] = 0.0;
   out_699928149424030002[169] = 0.0;
   out_699928149424030002[170] = 0.0;
   out_699928149424030002[171] = 1.0;
   out_699928149424030002[172] = 0.0;
   out_699928149424030002[173] = 0.0;
   out_699928149424030002[174] = 0.0;
   out_699928149424030002[175] = 0.0;
   out_699928149424030002[176] = 0.0;
   out_699928149424030002[177] = 0.0;
   out_699928149424030002[178] = 0.0;
   out_699928149424030002[179] = 0.0;
   out_699928149424030002[180] = 0.0;
   out_699928149424030002[181] = 0.0;
   out_699928149424030002[182] = 0.0;
   out_699928149424030002[183] = 0.0;
   out_699928149424030002[184] = 0.0;
   out_699928149424030002[185] = 0.0;
   out_699928149424030002[186] = 0.0;
   out_699928149424030002[187] = 0.0;
   out_699928149424030002[188] = 0.0;
   out_699928149424030002[189] = 0.0;
   out_699928149424030002[190] = 1.0;
   out_699928149424030002[191] = 0.0;
   out_699928149424030002[192] = 0.0;
   out_699928149424030002[193] = 0.0;
   out_699928149424030002[194] = 0.0;
   out_699928149424030002[195] = 0.0;
   out_699928149424030002[196] = 0.0;
   out_699928149424030002[197] = 0.0;
   out_699928149424030002[198] = 0.0;
   out_699928149424030002[199] = 0.0;
   out_699928149424030002[200] = 0.0;
   out_699928149424030002[201] = 0.0;
   out_699928149424030002[202] = 0.0;
   out_699928149424030002[203] = 0.0;
   out_699928149424030002[204] = 0.0;
   out_699928149424030002[205] = 0.0;
   out_699928149424030002[206] = 0.0;
   out_699928149424030002[207] = 0.0;
   out_699928149424030002[208] = 0.0;
   out_699928149424030002[209] = 1.0;
   out_699928149424030002[210] = 0.0;
   out_699928149424030002[211] = 0.0;
   out_699928149424030002[212] = 0.0;
   out_699928149424030002[213] = 0.0;
   out_699928149424030002[214] = 0.0;
   out_699928149424030002[215] = 0.0;
   out_699928149424030002[216] = 0.0;
   out_699928149424030002[217] = 0.0;
   out_699928149424030002[218] = 0.0;
   out_699928149424030002[219] = 0.0;
   out_699928149424030002[220] = 0.0;
   out_699928149424030002[221] = 0.0;
   out_699928149424030002[222] = 0.0;
   out_699928149424030002[223] = 0.0;
   out_699928149424030002[224] = 0.0;
   out_699928149424030002[225] = 0.0;
   out_699928149424030002[226] = 0.0;
   out_699928149424030002[227] = 0.0;
   out_699928149424030002[228] = 1.0;
   out_699928149424030002[229] = 0.0;
   out_699928149424030002[230] = 0.0;
   out_699928149424030002[231] = 0.0;
   out_699928149424030002[232] = 0.0;
   out_699928149424030002[233] = 0.0;
   out_699928149424030002[234] = 0.0;
   out_699928149424030002[235] = 0.0;
   out_699928149424030002[236] = 0.0;
   out_699928149424030002[237] = 0.0;
   out_699928149424030002[238] = 0.0;
   out_699928149424030002[239] = 0.0;
   out_699928149424030002[240] = 0.0;
   out_699928149424030002[241] = 0.0;
   out_699928149424030002[242] = 0.0;
   out_699928149424030002[243] = 0.0;
   out_699928149424030002[244] = 0.0;
   out_699928149424030002[245] = 0.0;
   out_699928149424030002[246] = 0.0;
   out_699928149424030002[247] = 1.0;
   out_699928149424030002[248] = 0.0;
   out_699928149424030002[249] = 0.0;
   out_699928149424030002[250] = 0.0;
   out_699928149424030002[251] = 0.0;
   out_699928149424030002[252] = 0.0;
   out_699928149424030002[253] = 0.0;
   out_699928149424030002[254] = 0.0;
   out_699928149424030002[255] = 0.0;
   out_699928149424030002[256] = 0.0;
   out_699928149424030002[257] = 0.0;
   out_699928149424030002[258] = 0.0;
   out_699928149424030002[259] = 0.0;
   out_699928149424030002[260] = 0.0;
   out_699928149424030002[261] = 0.0;
   out_699928149424030002[262] = 0.0;
   out_699928149424030002[263] = 0.0;
   out_699928149424030002[264] = 0.0;
   out_699928149424030002[265] = 0.0;
   out_699928149424030002[266] = 1.0;
   out_699928149424030002[267] = 0.0;
   out_699928149424030002[268] = 0.0;
   out_699928149424030002[269] = 0.0;
   out_699928149424030002[270] = 0.0;
   out_699928149424030002[271] = 0.0;
   out_699928149424030002[272] = 0.0;
   out_699928149424030002[273] = 0.0;
   out_699928149424030002[274] = 0.0;
   out_699928149424030002[275] = 0.0;
   out_699928149424030002[276] = 0.0;
   out_699928149424030002[277] = 0.0;
   out_699928149424030002[278] = 0.0;
   out_699928149424030002[279] = 0.0;
   out_699928149424030002[280] = 0.0;
   out_699928149424030002[281] = 0.0;
   out_699928149424030002[282] = 0.0;
   out_699928149424030002[283] = 0.0;
   out_699928149424030002[284] = 0.0;
   out_699928149424030002[285] = 1.0;
   out_699928149424030002[286] = 0.0;
   out_699928149424030002[287] = 0.0;
   out_699928149424030002[288] = 0.0;
   out_699928149424030002[289] = 0.0;
   out_699928149424030002[290] = 0.0;
   out_699928149424030002[291] = 0.0;
   out_699928149424030002[292] = 0.0;
   out_699928149424030002[293] = 0.0;
   out_699928149424030002[294] = 0.0;
   out_699928149424030002[295] = 0.0;
   out_699928149424030002[296] = 0.0;
   out_699928149424030002[297] = 0.0;
   out_699928149424030002[298] = 0.0;
   out_699928149424030002[299] = 0.0;
   out_699928149424030002[300] = 0.0;
   out_699928149424030002[301] = 0.0;
   out_699928149424030002[302] = 0.0;
   out_699928149424030002[303] = 0.0;
   out_699928149424030002[304] = 1.0;
   out_699928149424030002[305] = 0.0;
   out_699928149424030002[306] = 0.0;
   out_699928149424030002[307] = 0.0;
   out_699928149424030002[308] = 0.0;
   out_699928149424030002[309] = 0.0;
   out_699928149424030002[310] = 0.0;
   out_699928149424030002[311] = 0.0;
   out_699928149424030002[312] = 0.0;
   out_699928149424030002[313] = 0.0;
   out_699928149424030002[314] = 0.0;
   out_699928149424030002[315] = 0.0;
   out_699928149424030002[316] = 0.0;
   out_699928149424030002[317] = 0.0;
   out_699928149424030002[318] = 0.0;
   out_699928149424030002[319] = 0.0;
   out_699928149424030002[320] = 0.0;
   out_699928149424030002[321] = 0.0;
   out_699928149424030002[322] = 0.0;
   out_699928149424030002[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1867137519926473675) {
   out_1867137519926473675[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1867137519926473675[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1867137519926473675[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1867137519926473675[3] = dt*state[12] + state[3];
   out_1867137519926473675[4] = dt*state[13] + state[4];
   out_1867137519926473675[5] = dt*state[14] + state[5];
   out_1867137519926473675[6] = state[6];
   out_1867137519926473675[7] = state[7];
   out_1867137519926473675[8] = state[8];
   out_1867137519926473675[9] = state[9];
   out_1867137519926473675[10] = state[10];
   out_1867137519926473675[11] = state[11];
   out_1867137519926473675[12] = state[12];
   out_1867137519926473675[13] = state[13];
   out_1867137519926473675[14] = state[14];
   out_1867137519926473675[15] = state[15];
   out_1867137519926473675[16] = state[16];
   out_1867137519926473675[17] = state[17];
}
void F_fun(double *state, double dt, double *out_9116919347276229378) {
   out_9116919347276229378[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9116919347276229378[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9116919347276229378[2] = 0;
   out_9116919347276229378[3] = 0;
   out_9116919347276229378[4] = 0;
   out_9116919347276229378[5] = 0;
   out_9116919347276229378[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9116919347276229378[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9116919347276229378[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9116919347276229378[9] = 0;
   out_9116919347276229378[10] = 0;
   out_9116919347276229378[11] = 0;
   out_9116919347276229378[12] = 0;
   out_9116919347276229378[13] = 0;
   out_9116919347276229378[14] = 0;
   out_9116919347276229378[15] = 0;
   out_9116919347276229378[16] = 0;
   out_9116919347276229378[17] = 0;
   out_9116919347276229378[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9116919347276229378[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9116919347276229378[20] = 0;
   out_9116919347276229378[21] = 0;
   out_9116919347276229378[22] = 0;
   out_9116919347276229378[23] = 0;
   out_9116919347276229378[24] = 0;
   out_9116919347276229378[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9116919347276229378[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9116919347276229378[27] = 0;
   out_9116919347276229378[28] = 0;
   out_9116919347276229378[29] = 0;
   out_9116919347276229378[30] = 0;
   out_9116919347276229378[31] = 0;
   out_9116919347276229378[32] = 0;
   out_9116919347276229378[33] = 0;
   out_9116919347276229378[34] = 0;
   out_9116919347276229378[35] = 0;
   out_9116919347276229378[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9116919347276229378[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9116919347276229378[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9116919347276229378[39] = 0;
   out_9116919347276229378[40] = 0;
   out_9116919347276229378[41] = 0;
   out_9116919347276229378[42] = 0;
   out_9116919347276229378[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9116919347276229378[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9116919347276229378[45] = 0;
   out_9116919347276229378[46] = 0;
   out_9116919347276229378[47] = 0;
   out_9116919347276229378[48] = 0;
   out_9116919347276229378[49] = 0;
   out_9116919347276229378[50] = 0;
   out_9116919347276229378[51] = 0;
   out_9116919347276229378[52] = 0;
   out_9116919347276229378[53] = 0;
   out_9116919347276229378[54] = 0;
   out_9116919347276229378[55] = 0;
   out_9116919347276229378[56] = 0;
   out_9116919347276229378[57] = 1;
   out_9116919347276229378[58] = 0;
   out_9116919347276229378[59] = 0;
   out_9116919347276229378[60] = 0;
   out_9116919347276229378[61] = 0;
   out_9116919347276229378[62] = 0;
   out_9116919347276229378[63] = 0;
   out_9116919347276229378[64] = 0;
   out_9116919347276229378[65] = 0;
   out_9116919347276229378[66] = dt;
   out_9116919347276229378[67] = 0;
   out_9116919347276229378[68] = 0;
   out_9116919347276229378[69] = 0;
   out_9116919347276229378[70] = 0;
   out_9116919347276229378[71] = 0;
   out_9116919347276229378[72] = 0;
   out_9116919347276229378[73] = 0;
   out_9116919347276229378[74] = 0;
   out_9116919347276229378[75] = 0;
   out_9116919347276229378[76] = 1;
   out_9116919347276229378[77] = 0;
   out_9116919347276229378[78] = 0;
   out_9116919347276229378[79] = 0;
   out_9116919347276229378[80] = 0;
   out_9116919347276229378[81] = 0;
   out_9116919347276229378[82] = 0;
   out_9116919347276229378[83] = 0;
   out_9116919347276229378[84] = 0;
   out_9116919347276229378[85] = dt;
   out_9116919347276229378[86] = 0;
   out_9116919347276229378[87] = 0;
   out_9116919347276229378[88] = 0;
   out_9116919347276229378[89] = 0;
   out_9116919347276229378[90] = 0;
   out_9116919347276229378[91] = 0;
   out_9116919347276229378[92] = 0;
   out_9116919347276229378[93] = 0;
   out_9116919347276229378[94] = 0;
   out_9116919347276229378[95] = 1;
   out_9116919347276229378[96] = 0;
   out_9116919347276229378[97] = 0;
   out_9116919347276229378[98] = 0;
   out_9116919347276229378[99] = 0;
   out_9116919347276229378[100] = 0;
   out_9116919347276229378[101] = 0;
   out_9116919347276229378[102] = 0;
   out_9116919347276229378[103] = 0;
   out_9116919347276229378[104] = dt;
   out_9116919347276229378[105] = 0;
   out_9116919347276229378[106] = 0;
   out_9116919347276229378[107] = 0;
   out_9116919347276229378[108] = 0;
   out_9116919347276229378[109] = 0;
   out_9116919347276229378[110] = 0;
   out_9116919347276229378[111] = 0;
   out_9116919347276229378[112] = 0;
   out_9116919347276229378[113] = 0;
   out_9116919347276229378[114] = 1;
   out_9116919347276229378[115] = 0;
   out_9116919347276229378[116] = 0;
   out_9116919347276229378[117] = 0;
   out_9116919347276229378[118] = 0;
   out_9116919347276229378[119] = 0;
   out_9116919347276229378[120] = 0;
   out_9116919347276229378[121] = 0;
   out_9116919347276229378[122] = 0;
   out_9116919347276229378[123] = 0;
   out_9116919347276229378[124] = 0;
   out_9116919347276229378[125] = 0;
   out_9116919347276229378[126] = 0;
   out_9116919347276229378[127] = 0;
   out_9116919347276229378[128] = 0;
   out_9116919347276229378[129] = 0;
   out_9116919347276229378[130] = 0;
   out_9116919347276229378[131] = 0;
   out_9116919347276229378[132] = 0;
   out_9116919347276229378[133] = 1;
   out_9116919347276229378[134] = 0;
   out_9116919347276229378[135] = 0;
   out_9116919347276229378[136] = 0;
   out_9116919347276229378[137] = 0;
   out_9116919347276229378[138] = 0;
   out_9116919347276229378[139] = 0;
   out_9116919347276229378[140] = 0;
   out_9116919347276229378[141] = 0;
   out_9116919347276229378[142] = 0;
   out_9116919347276229378[143] = 0;
   out_9116919347276229378[144] = 0;
   out_9116919347276229378[145] = 0;
   out_9116919347276229378[146] = 0;
   out_9116919347276229378[147] = 0;
   out_9116919347276229378[148] = 0;
   out_9116919347276229378[149] = 0;
   out_9116919347276229378[150] = 0;
   out_9116919347276229378[151] = 0;
   out_9116919347276229378[152] = 1;
   out_9116919347276229378[153] = 0;
   out_9116919347276229378[154] = 0;
   out_9116919347276229378[155] = 0;
   out_9116919347276229378[156] = 0;
   out_9116919347276229378[157] = 0;
   out_9116919347276229378[158] = 0;
   out_9116919347276229378[159] = 0;
   out_9116919347276229378[160] = 0;
   out_9116919347276229378[161] = 0;
   out_9116919347276229378[162] = 0;
   out_9116919347276229378[163] = 0;
   out_9116919347276229378[164] = 0;
   out_9116919347276229378[165] = 0;
   out_9116919347276229378[166] = 0;
   out_9116919347276229378[167] = 0;
   out_9116919347276229378[168] = 0;
   out_9116919347276229378[169] = 0;
   out_9116919347276229378[170] = 0;
   out_9116919347276229378[171] = 1;
   out_9116919347276229378[172] = 0;
   out_9116919347276229378[173] = 0;
   out_9116919347276229378[174] = 0;
   out_9116919347276229378[175] = 0;
   out_9116919347276229378[176] = 0;
   out_9116919347276229378[177] = 0;
   out_9116919347276229378[178] = 0;
   out_9116919347276229378[179] = 0;
   out_9116919347276229378[180] = 0;
   out_9116919347276229378[181] = 0;
   out_9116919347276229378[182] = 0;
   out_9116919347276229378[183] = 0;
   out_9116919347276229378[184] = 0;
   out_9116919347276229378[185] = 0;
   out_9116919347276229378[186] = 0;
   out_9116919347276229378[187] = 0;
   out_9116919347276229378[188] = 0;
   out_9116919347276229378[189] = 0;
   out_9116919347276229378[190] = 1;
   out_9116919347276229378[191] = 0;
   out_9116919347276229378[192] = 0;
   out_9116919347276229378[193] = 0;
   out_9116919347276229378[194] = 0;
   out_9116919347276229378[195] = 0;
   out_9116919347276229378[196] = 0;
   out_9116919347276229378[197] = 0;
   out_9116919347276229378[198] = 0;
   out_9116919347276229378[199] = 0;
   out_9116919347276229378[200] = 0;
   out_9116919347276229378[201] = 0;
   out_9116919347276229378[202] = 0;
   out_9116919347276229378[203] = 0;
   out_9116919347276229378[204] = 0;
   out_9116919347276229378[205] = 0;
   out_9116919347276229378[206] = 0;
   out_9116919347276229378[207] = 0;
   out_9116919347276229378[208] = 0;
   out_9116919347276229378[209] = 1;
   out_9116919347276229378[210] = 0;
   out_9116919347276229378[211] = 0;
   out_9116919347276229378[212] = 0;
   out_9116919347276229378[213] = 0;
   out_9116919347276229378[214] = 0;
   out_9116919347276229378[215] = 0;
   out_9116919347276229378[216] = 0;
   out_9116919347276229378[217] = 0;
   out_9116919347276229378[218] = 0;
   out_9116919347276229378[219] = 0;
   out_9116919347276229378[220] = 0;
   out_9116919347276229378[221] = 0;
   out_9116919347276229378[222] = 0;
   out_9116919347276229378[223] = 0;
   out_9116919347276229378[224] = 0;
   out_9116919347276229378[225] = 0;
   out_9116919347276229378[226] = 0;
   out_9116919347276229378[227] = 0;
   out_9116919347276229378[228] = 1;
   out_9116919347276229378[229] = 0;
   out_9116919347276229378[230] = 0;
   out_9116919347276229378[231] = 0;
   out_9116919347276229378[232] = 0;
   out_9116919347276229378[233] = 0;
   out_9116919347276229378[234] = 0;
   out_9116919347276229378[235] = 0;
   out_9116919347276229378[236] = 0;
   out_9116919347276229378[237] = 0;
   out_9116919347276229378[238] = 0;
   out_9116919347276229378[239] = 0;
   out_9116919347276229378[240] = 0;
   out_9116919347276229378[241] = 0;
   out_9116919347276229378[242] = 0;
   out_9116919347276229378[243] = 0;
   out_9116919347276229378[244] = 0;
   out_9116919347276229378[245] = 0;
   out_9116919347276229378[246] = 0;
   out_9116919347276229378[247] = 1;
   out_9116919347276229378[248] = 0;
   out_9116919347276229378[249] = 0;
   out_9116919347276229378[250] = 0;
   out_9116919347276229378[251] = 0;
   out_9116919347276229378[252] = 0;
   out_9116919347276229378[253] = 0;
   out_9116919347276229378[254] = 0;
   out_9116919347276229378[255] = 0;
   out_9116919347276229378[256] = 0;
   out_9116919347276229378[257] = 0;
   out_9116919347276229378[258] = 0;
   out_9116919347276229378[259] = 0;
   out_9116919347276229378[260] = 0;
   out_9116919347276229378[261] = 0;
   out_9116919347276229378[262] = 0;
   out_9116919347276229378[263] = 0;
   out_9116919347276229378[264] = 0;
   out_9116919347276229378[265] = 0;
   out_9116919347276229378[266] = 1;
   out_9116919347276229378[267] = 0;
   out_9116919347276229378[268] = 0;
   out_9116919347276229378[269] = 0;
   out_9116919347276229378[270] = 0;
   out_9116919347276229378[271] = 0;
   out_9116919347276229378[272] = 0;
   out_9116919347276229378[273] = 0;
   out_9116919347276229378[274] = 0;
   out_9116919347276229378[275] = 0;
   out_9116919347276229378[276] = 0;
   out_9116919347276229378[277] = 0;
   out_9116919347276229378[278] = 0;
   out_9116919347276229378[279] = 0;
   out_9116919347276229378[280] = 0;
   out_9116919347276229378[281] = 0;
   out_9116919347276229378[282] = 0;
   out_9116919347276229378[283] = 0;
   out_9116919347276229378[284] = 0;
   out_9116919347276229378[285] = 1;
   out_9116919347276229378[286] = 0;
   out_9116919347276229378[287] = 0;
   out_9116919347276229378[288] = 0;
   out_9116919347276229378[289] = 0;
   out_9116919347276229378[290] = 0;
   out_9116919347276229378[291] = 0;
   out_9116919347276229378[292] = 0;
   out_9116919347276229378[293] = 0;
   out_9116919347276229378[294] = 0;
   out_9116919347276229378[295] = 0;
   out_9116919347276229378[296] = 0;
   out_9116919347276229378[297] = 0;
   out_9116919347276229378[298] = 0;
   out_9116919347276229378[299] = 0;
   out_9116919347276229378[300] = 0;
   out_9116919347276229378[301] = 0;
   out_9116919347276229378[302] = 0;
   out_9116919347276229378[303] = 0;
   out_9116919347276229378[304] = 1;
   out_9116919347276229378[305] = 0;
   out_9116919347276229378[306] = 0;
   out_9116919347276229378[307] = 0;
   out_9116919347276229378[308] = 0;
   out_9116919347276229378[309] = 0;
   out_9116919347276229378[310] = 0;
   out_9116919347276229378[311] = 0;
   out_9116919347276229378[312] = 0;
   out_9116919347276229378[313] = 0;
   out_9116919347276229378[314] = 0;
   out_9116919347276229378[315] = 0;
   out_9116919347276229378[316] = 0;
   out_9116919347276229378[317] = 0;
   out_9116919347276229378[318] = 0;
   out_9116919347276229378[319] = 0;
   out_9116919347276229378[320] = 0;
   out_9116919347276229378[321] = 0;
   out_9116919347276229378[322] = 0;
   out_9116919347276229378[323] = 1;
}
void h_4(double *state, double *unused, double *out_6089064433593564706) {
   out_6089064433593564706[0] = state[6] + state[9];
   out_6089064433593564706[1] = state[7] + state[10];
   out_6089064433593564706[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4452590235615050733) {
   out_4452590235615050733[0] = 0;
   out_4452590235615050733[1] = 0;
   out_4452590235615050733[2] = 0;
   out_4452590235615050733[3] = 0;
   out_4452590235615050733[4] = 0;
   out_4452590235615050733[5] = 0;
   out_4452590235615050733[6] = 1;
   out_4452590235615050733[7] = 0;
   out_4452590235615050733[8] = 0;
   out_4452590235615050733[9] = 1;
   out_4452590235615050733[10] = 0;
   out_4452590235615050733[11] = 0;
   out_4452590235615050733[12] = 0;
   out_4452590235615050733[13] = 0;
   out_4452590235615050733[14] = 0;
   out_4452590235615050733[15] = 0;
   out_4452590235615050733[16] = 0;
   out_4452590235615050733[17] = 0;
   out_4452590235615050733[18] = 0;
   out_4452590235615050733[19] = 0;
   out_4452590235615050733[20] = 0;
   out_4452590235615050733[21] = 0;
   out_4452590235615050733[22] = 0;
   out_4452590235615050733[23] = 0;
   out_4452590235615050733[24] = 0;
   out_4452590235615050733[25] = 1;
   out_4452590235615050733[26] = 0;
   out_4452590235615050733[27] = 0;
   out_4452590235615050733[28] = 1;
   out_4452590235615050733[29] = 0;
   out_4452590235615050733[30] = 0;
   out_4452590235615050733[31] = 0;
   out_4452590235615050733[32] = 0;
   out_4452590235615050733[33] = 0;
   out_4452590235615050733[34] = 0;
   out_4452590235615050733[35] = 0;
   out_4452590235615050733[36] = 0;
   out_4452590235615050733[37] = 0;
   out_4452590235615050733[38] = 0;
   out_4452590235615050733[39] = 0;
   out_4452590235615050733[40] = 0;
   out_4452590235615050733[41] = 0;
   out_4452590235615050733[42] = 0;
   out_4452590235615050733[43] = 0;
   out_4452590235615050733[44] = 1;
   out_4452590235615050733[45] = 0;
   out_4452590235615050733[46] = 0;
   out_4452590235615050733[47] = 1;
   out_4452590235615050733[48] = 0;
   out_4452590235615050733[49] = 0;
   out_4452590235615050733[50] = 0;
   out_4452590235615050733[51] = 0;
   out_4452590235615050733[52] = 0;
   out_4452590235615050733[53] = 0;
}
void h_10(double *state, double *unused, double *out_2469906940172367738) {
   out_2469906940172367738[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2469906940172367738[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2469906940172367738[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2054220961747582832) {
   out_2054220961747582832[0] = 0;
   out_2054220961747582832[1] = 9.8100000000000005*cos(state[1]);
   out_2054220961747582832[2] = 0;
   out_2054220961747582832[3] = 0;
   out_2054220961747582832[4] = -state[8];
   out_2054220961747582832[5] = state[7];
   out_2054220961747582832[6] = 0;
   out_2054220961747582832[7] = state[5];
   out_2054220961747582832[8] = -state[4];
   out_2054220961747582832[9] = 0;
   out_2054220961747582832[10] = 0;
   out_2054220961747582832[11] = 0;
   out_2054220961747582832[12] = 1;
   out_2054220961747582832[13] = 0;
   out_2054220961747582832[14] = 0;
   out_2054220961747582832[15] = 1;
   out_2054220961747582832[16] = 0;
   out_2054220961747582832[17] = 0;
   out_2054220961747582832[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2054220961747582832[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2054220961747582832[20] = 0;
   out_2054220961747582832[21] = state[8];
   out_2054220961747582832[22] = 0;
   out_2054220961747582832[23] = -state[6];
   out_2054220961747582832[24] = -state[5];
   out_2054220961747582832[25] = 0;
   out_2054220961747582832[26] = state[3];
   out_2054220961747582832[27] = 0;
   out_2054220961747582832[28] = 0;
   out_2054220961747582832[29] = 0;
   out_2054220961747582832[30] = 0;
   out_2054220961747582832[31] = 1;
   out_2054220961747582832[32] = 0;
   out_2054220961747582832[33] = 0;
   out_2054220961747582832[34] = 1;
   out_2054220961747582832[35] = 0;
   out_2054220961747582832[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2054220961747582832[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2054220961747582832[38] = 0;
   out_2054220961747582832[39] = -state[7];
   out_2054220961747582832[40] = state[6];
   out_2054220961747582832[41] = 0;
   out_2054220961747582832[42] = state[4];
   out_2054220961747582832[43] = -state[3];
   out_2054220961747582832[44] = 0;
   out_2054220961747582832[45] = 0;
   out_2054220961747582832[46] = 0;
   out_2054220961747582832[47] = 0;
   out_2054220961747582832[48] = 0;
   out_2054220961747582832[49] = 0;
   out_2054220961747582832[50] = 1;
   out_2054220961747582832[51] = 0;
   out_2054220961747582832[52] = 0;
   out_2054220961747582832[53] = 1;
}
void h_13(double *state, double *unused, double *out_1980844008070145866) {
   out_1980844008070145866[0] = state[3];
   out_1980844008070145866[1] = state[4];
   out_1980844008070145866[2] = state[5];
}
void H_13(double *state, double *unused, double *out_618834772312526709) {
   out_618834772312526709[0] = 0;
   out_618834772312526709[1] = 0;
   out_618834772312526709[2] = 0;
   out_618834772312526709[3] = 1;
   out_618834772312526709[4] = 0;
   out_618834772312526709[5] = 0;
   out_618834772312526709[6] = 0;
   out_618834772312526709[7] = 0;
   out_618834772312526709[8] = 0;
   out_618834772312526709[9] = 0;
   out_618834772312526709[10] = 0;
   out_618834772312526709[11] = 0;
   out_618834772312526709[12] = 0;
   out_618834772312526709[13] = 0;
   out_618834772312526709[14] = 0;
   out_618834772312526709[15] = 0;
   out_618834772312526709[16] = 0;
   out_618834772312526709[17] = 0;
   out_618834772312526709[18] = 0;
   out_618834772312526709[19] = 0;
   out_618834772312526709[20] = 0;
   out_618834772312526709[21] = 0;
   out_618834772312526709[22] = 1;
   out_618834772312526709[23] = 0;
   out_618834772312526709[24] = 0;
   out_618834772312526709[25] = 0;
   out_618834772312526709[26] = 0;
   out_618834772312526709[27] = 0;
   out_618834772312526709[28] = 0;
   out_618834772312526709[29] = 0;
   out_618834772312526709[30] = 0;
   out_618834772312526709[31] = 0;
   out_618834772312526709[32] = 0;
   out_618834772312526709[33] = 0;
   out_618834772312526709[34] = 0;
   out_618834772312526709[35] = 0;
   out_618834772312526709[36] = 0;
   out_618834772312526709[37] = 0;
   out_618834772312526709[38] = 0;
   out_618834772312526709[39] = 0;
   out_618834772312526709[40] = 0;
   out_618834772312526709[41] = 1;
   out_618834772312526709[42] = 0;
   out_618834772312526709[43] = 0;
   out_618834772312526709[44] = 0;
   out_618834772312526709[45] = 0;
   out_618834772312526709[46] = 0;
   out_618834772312526709[47] = 0;
   out_618834772312526709[48] = 0;
   out_618834772312526709[49] = 0;
   out_618834772312526709[50] = 0;
   out_618834772312526709[51] = 0;
   out_618834772312526709[52] = 0;
   out_618834772312526709[53] = 0;
}
void h_14(double *state, double *unused, double *out_1213929799491886433) {
   out_1213929799491886433[0] = state[6];
   out_1213929799491886433[1] = state[7];
   out_1213929799491886433[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1369801803319678437) {
   out_1369801803319678437[0] = 0;
   out_1369801803319678437[1] = 0;
   out_1369801803319678437[2] = 0;
   out_1369801803319678437[3] = 0;
   out_1369801803319678437[4] = 0;
   out_1369801803319678437[5] = 0;
   out_1369801803319678437[6] = 1;
   out_1369801803319678437[7] = 0;
   out_1369801803319678437[8] = 0;
   out_1369801803319678437[9] = 0;
   out_1369801803319678437[10] = 0;
   out_1369801803319678437[11] = 0;
   out_1369801803319678437[12] = 0;
   out_1369801803319678437[13] = 0;
   out_1369801803319678437[14] = 0;
   out_1369801803319678437[15] = 0;
   out_1369801803319678437[16] = 0;
   out_1369801803319678437[17] = 0;
   out_1369801803319678437[18] = 0;
   out_1369801803319678437[19] = 0;
   out_1369801803319678437[20] = 0;
   out_1369801803319678437[21] = 0;
   out_1369801803319678437[22] = 0;
   out_1369801803319678437[23] = 0;
   out_1369801803319678437[24] = 0;
   out_1369801803319678437[25] = 1;
   out_1369801803319678437[26] = 0;
   out_1369801803319678437[27] = 0;
   out_1369801803319678437[28] = 0;
   out_1369801803319678437[29] = 0;
   out_1369801803319678437[30] = 0;
   out_1369801803319678437[31] = 0;
   out_1369801803319678437[32] = 0;
   out_1369801803319678437[33] = 0;
   out_1369801803319678437[34] = 0;
   out_1369801803319678437[35] = 0;
   out_1369801803319678437[36] = 0;
   out_1369801803319678437[37] = 0;
   out_1369801803319678437[38] = 0;
   out_1369801803319678437[39] = 0;
   out_1369801803319678437[40] = 0;
   out_1369801803319678437[41] = 0;
   out_1369801803319678437[42] = 0;
   out_1369801803319678437[43] = 0;
   out_1369801803319678437[44] = 1;
   out_1369801803319678437[45] = 0;
   out_1369801803319678437[46] = 0;
   out_1369801803319678437[47] = 0;
   out_1369801803319678437[48] = 0;
   out_1369801803319678437[49] = 0;
   out_1369801803319678437[50] = 0;
   out_1369801803319678437[51] = 0;
   out_1369801803319678437[52] = 0;
   out_1369801803319678437[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3332094354178799206) {
  err_fun(nom_x, delta_x, out_3332094354178799206);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6787681857429762222) {
  inv_err_fun(nom_x, true_x, out_6787681857429762222);
}
void pose_H_mod_fun(double *state, double *out_699928149424030002) {
  H_mod_fun(state, out_699928149424030002);
}
void pose_f_fun(double *state, double dt, double *out_1867137519926473675) {
  f_fun(state,  dt, out_1867137519926473675);
}
void pose_F_fun(double *state, double dt, double *out_9116919347276229378) {
  F_fun(state,  dt, out_9116919347276229378);
}
void pose_h_4(double *state, double *unused, double *out_6089064433593564706) {
  h_4(state, unused, out_6089064433593564706);
}
void pose_H_4(double *state, double *unused, double *out_4452590235615050733) {
  H_4(state, unused, out_4452590235615050733);
}
void pose_h_10(double *state, double *unused, double *out_2469906940172367738) {
  h_10(state, unused, out_2469906940172367738);
}
void pose_H_10(double *state, double *unused, double *out_2054220961747582832) {
  H_10(state, unused, out_2054220961747582832);
}
void pose_h_13(double *state, double *unused, double *out_1980844008070145866) {
  h_13(state, unused, out_1980844008070145866);
}
void pose_H_13(double *state, double *unused, double *out_618834772312526709) {
  H_13(state, unused, out_618834772312526709);
}
void pose_h_14(double *state, double *unused, double *out_1213929799491886433) {
  h_14(state, unused, out_1213929799491886433);
}
void pose_H_14(double *state, double *unused, double *out_1369801803319678437) {
  H_14(state, unused, out_1369801803319678437);
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
