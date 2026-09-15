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
void err_fun(double *nom_x, double *delta_x, double *out_3020435366952319765) {
   out_3020435366952319765[0] = delta_x[0] + nom_x[0];
   out_3020435366952319765[1] = delta_x[1] + nom_x[1];
   out_3020435366952319765[2] = delta_x[2] + nom_x[2];
   out_3020435366952319765[3] = delta_x[3] + nom_x[3];
   out_3020435366952319765[4] = delta_x[4] + nom_x[4];
   out_3020435366952319765[5] = delta_x[5] + nom_x[5];
   out_3020435366952319765[6] = delta_x[6] + nom_x[6];
   out_3020435366952319765[7] = delta_x[7] + nom_x[7];
   out_3020435366952319765[8] = delta_x[8] + nom_x[8];
   out_3020435366952319765[9] = delta_x[9] + nom_x[9];
   out_3020435366952319765[10] = delta_x[10] + nom_x[10];
   out_3020435366952319765[11] = delta_x[11] + nom_x[11];
   out_3020435366952319765[12] = delta_x[12] + nom_x[12];
   out_3020435366952319765[13] = delta_x[13] + nom_x[13];
   out_3020435366952319765[14] = delta_x[14] + nom_x[14];
   out_3020435366952319765[15] = delta_x[15] + nom_x[15];
   out_3020435366952319765[16] = delta_x[16] + nom_x[16];
   out_3020435366952319765[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3417424495517393488) {
   out_3417424495517393488[0] = -nom_x[0] + true_x[0];
   out_3417424495517393488[1] = -nom_x[1] + true_x[1];
   out_3417424495517393488[2] = -nom_x[2] + true_x[2];
   out_3417424495517393488[3] = -nom_x[3] + true_x[3];
   out_3417424495517393488[4] = -nom_x[4] + true_x[4];
   out_3417424495517393488[5] = -nom_x[5] + true_x[5];
   out_3417424495517393488[6] = -nom_x[6] + true_x[6];
   out_3417424495517393488[7] = -nom_x[7] + true_x[7];
   out_3417424495517393488[8] = -nom_x[8] + true_x[8];
   out_3417424495517393488[9] = -nom_x[9] + true_x[9];
   out_3417424495517393488[10] = -nom_x[10] + true_x[10];
   out_3417424495517393488[11] = -nom_x[11] + true_x[11];
   out_3417424495517393488[12] = -nom_x[12] + true_x[12];
   out_3417424495517393488[13] = -nom_x[13] + true_x[13];
   out_3417424495517393488[14] = -nom_x[14] + true_x[14];
   out_3417424495517393488[15] = -nom_x[15] + true_x[15];
   out_3417424495517393488[16] = -nom_x[16] + true_x[16];
   out_3417424495517393488[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2051793842018390757) {
   out_2051793842018390757[0] = 1.0;
   out_2051793842018390757[1] = 0.0;
   out_2051793842018390757[2] = 0.0;
   out_2051793842018390757[3] = 0.0;
   out_2051793842018390757[4] = 0.0;
   out_2051793842018390757[5] = 0.0;
   out_2051793842018390757[6] = 0.0;
   out_2051793842018390757[7] = 0.0;
   out_2051793842018390757[8] = 0.0;
   out_2051793842018390757[9] = 0.0;
   out_2051793842018390757[10] = 0.0;
   out_2051793842018390757[11] = 0.0;
   out_2051793842018390757[12] = 0.0;
   out_2051793842018390757[13] = 0.0;
   out_2051793842018390757[14] = 0.0;
   out_2051793842018390757[15] = 0.0;
   out_2051793842018390757[16] = 0.0;
   out_2051793842018390757[17] = 0.0;
   out_2051793842018390757[18] = 0.0;
   out_2051793842018390757[19] = 1.0;
   out_2051793842018390757[20] = 0.0;
   out_2051793842018390757[21] = 0.0;
   out_2051793842018390757[22] = 0.0;
   out_2051793842018390757[23] = 0.0;
   out_2051793842018390757[24] = 0.0;
   out_2051793842018390757[25] = 0.0;
   out_2051793842018390757[26] = 0.0;
   out_2051793842018390757[27] = 0.0;
   out_2051793842018390757[28] = 0.0;
   out_2051793842018390757[29] = 0.0;
   out_2051793842018390757[30] = 0.0;
   out_2051793842018390757[31] = 0.0;
   out_2051793842018390757[32] = 0.0;
   out_2051793842018390757[33] = 0.0;
   out_2051793842018390757[34] = 0.0;
   out_2051793842018390757[35] = 0.0;
   out_2051793842018390757[36] = 0.0;
   out_2051793842018390757[37] = 0.0;
   out_2051793842018390757[38] = 1.0;
   out_2051793842018390757[39] = 0.0;
   out_2051793842018390757[40] = 0.0;
   out_2051793842018390757[41] = 0.0;
   out_2051793842018390757[42] = 0.0;
   out_2051793842018390757[43] = 0.0;
   out_2051793842018390757[44] = 0.0;
   out_2051793842018390757[45] = 0.0;
   out_2051793842018390757[46] = 0.0;
   out_2051793842018390757[47] = 0.0;
   out_2051793842018390757[48] = 0.0;
   out_2051793842018390757[49] = 0.0;
   out_2051793842018390757[50] = 0.0;
   out_2051793842018390757[51] = 0.0;
   out_2051793842018390757[52] = 0.0;
   out_2051793842018390757[53] = 0.0;
   out_2051793842018390757[54] = 0.0;
   out_2051793842018390757[55] = 0.0;
   out_2051793842018390757[56] = 0.0;
   out_2051793842018390757[57] = 1.0;
   out_2051793842018390757[58] = 0.0;
   out_2051793842018390757[59] = 0.0;
   out_2051793842018390757[60] = 0.0;
   out_2051793842018390757[61] = 0.0;
   out_2051793842018390757[62] = 0.0;
   out_2051793842018390757[63] = 0.0;
   out_2051793842018390757[64] = 0.0;
   out_2051793842018390757[65] = 0.0;
   out_2051793842018390757[66] = 0.0;
   out_2051793842018390757[67] = 0.0;
   out_2051793842018390757[68] = 0.0;
   out_2051793842018390757[69] = 0.0;
   out_2051793842018390757[70] = 0.0;
   out_2051793842018390757[71] = 0.0;
   out_2051793842018390757[72] = 0.0;
   out_2051793842018390757[73] = 0.0;
   out_2051793842018390757[74] = 0.0;
   out_2051793842018390757[75] = 0.0;
   out_2051793842018390757[76] = 1.0;
   out_2051793842018390757[77] = 0.0;
   out_2051793842018390757[78] = 0.0;
   out_2051793842018390757[79] = 0.0;
   out_2051793842018390757[80] = 0.0;
   out_2051793842018390757[81] = 0.0;
   out_2051793842018390757[82] = 0.0;
   out_2051793842018390757[83] = 0.0;
   out_2051793842018390757[84] = 0.0;
   out_2051793842018390757[85] = 0.0;
   out_2051793842018390757[86] = 0.0;
   out_2051793842018390757[87] = 0.0;
   out_2051793842018390757[88] = 0.0;
   out_2051793842018390757[89] = 0.0;
   out_2051793842018390757[90] = 0.0;
   out_2051793842018390757[91] = 0.0;
   out_2051793842018390757[92] = 0.0;
   out_2051793842018390757[93] = 0.0;
   out_2051793842018390757[94] = 0.0;
   out_2051793842018390757[95] = 1.0;
   out_2051793842018390757[96] = 0.0;
   out_2051793842018390757[97] = 0.0;
   out_2051793842018390757[98] = 0.0;
   out_2051793842018390757[99] = 0.0;
   out_2051793842018390757[100] = 0.0;
   out_2051793842018390757[101] = 0.0;
   out_2051793842018390757[102] = 0.0;
   out_2051793842018390757[103] = 0.0;
   out_2051793842018390757[104] = 0.0;
   out_2051793842018390757[105] = 0.0;
   out_2051793842018390757[106] = 0.0;
   out_2051793842018390757[107] = 0.0;
   out_2051793842018390757[108] = 0.0;
   out_2051793842018390757[109] = 0.0;
   out_2051793842018390757[110] = 0.0;
   out_2051793842018390757[111] = 0.0;
   out_2051793842018390757[112] = 0.0;
   out_2051793842018390757[113] = 0.0;
   out_2051793842018390757[114] = 1.0;
   out_2051793842018390757[115] = 0.0;
   out_2051793842018390757[116] = 0.0;
   out_2051793842018390757[117] = 0.0;
   out_2051793842018390757[118] = 0.0;
   out_2051793842018390757[119] = 0.0;
   out_2051793842018390757[120] = 0.0;
   out_2051793842018390757[121] = 0.0;
   out_2051793842018390757[122] = 0.0;
   out_2051793842018390757[123] = 0.0;
   out_2051793842018390757[124] = 0.0;
   out_2051793842018390757[125] = 0.0;
   out_2051793842018390757[126] = 0.0;
   out_2051793842018390757[127] = 0.0;
   out_2051793842018390757[128] = 0.0;
   out_2051793842018390757[129] = 0.0;
   out_2051793842018390757[130] = 0.0;
   out_2051793842018390757[131] = 0.0;
   out_2051793842018390757[132] = 0.0;
   out_2051793842018390757[133] = 1.0;
   out_2051793842018390757[134] = 0.0;
   out_2051793842018390757[135] = 0.0;
   out_2051793842018390757[136] = 0.0;
   out_2051793842018390757[137] = 0.0;
   out_2051793842018390757[138] = 0.0;
   out_2051793842018390757[139] = 0.0;
   out_2051793842018390757[140] = 0.0;
   out_2051793842018390757[141] = 0.0;
   out_2051793842018390757[142] = 0.0;
   out_2051793842018390757[143] = 0.0;
   out_2051793842018390757[144] = 0.0;
   out_2051793842018390757[145] = 0.0;
   out_2051793842018390757[146] = 0.0;
   out_2051793842018390757[147] = 0.0;
   out_2051793842018390757[148] = 0.0;
   out_2051793842018390757[149] = 0.0;
   out_2051793842018390757[150] = 0.0;
   out_2051793842018390757[151] = 0.0;
   out_2051793842018390757[152] = 1.0;
   out_2051793842018390757[153] = 0.0;
   out_2051793842018390757[154] = 0.0;
   out_2051793842018390757[155] = 0.0;
   out_2051793842018390757[156] = 0.0;
   out_2051793842018390757[157] = 0.0;
   out_2051793842018390757[158] = 0.0;
   out_2051793842018390757[159] = 0.0;
   out_2051793842018390757[160] = 0.0;
   out_2051793842018390757[161] = 0.0;
   out_2051793842018390757[162] = 0.0;
   out_2051793842018390757[163] = 0.0;
   out_2051793842018390757[164] = 0.0;
   out_2051793842018390757[165] = 0.0;
   out_2051793842018390757[166] = 0.0;
   out_2051793842018390757[167] = 0.0;
   out_2051793842018390757[168] = 0.0;
   out_2051793842018390757[169] = 0.0;
   out_2051793842018390757[170] = 0.0;
   out_2051793842018390757[171] = 1.0;
   out_2051793842018390757[172] = 0.0;
   out_2051793842018390757[173] = 0.0;
   out_2051793842018390757[174] = 0.0;
   out_2051793842018390757[175] = 0.0;
   out_2051793842018390757[176] = 0.0;
   out_2051793842018390757[177] = 0.0;
   out_2051793842018390757[178] = 0.0;
   out_2051793842018390757[179] = 0.0;
   out_2051793842018390757[180] = 0.0;
   out_2051793842018390757[181] = 0.0;
   out_2051793842018390757[182] = 0.0;
   out_2051793842018390757[183] = 0.0;
   out_2051793842018390757[184] = 0.0;
   out_2051793842018390757[185] = 0.0;
   out_2051793842018390757[186] = 0.0;
   out_2051793842018390757[187] = 0.0;
   out_2051793842018390757[188] = 0.0;
   out_2051793842018390757[189] = 0.0;
   out_2051793842018390757[190] = 1.0;
   out_2051793842018390757[191] = 0.0;
   out_2051793842018390757[192] = 0.0;
   out_2051793842018390757[193] = 0.0;
   out_2051793842018390757[194] = 0.0;
   out_2051793842018390757[195] = 0.0;
   out_2051793842018390757[196] = 0.0;
   out_2051793842018390757[197] = 0.0;
   out_2051793842018390757[198] = 0.0;
   out_2051793842018390757[199] = 0.0;
   out_2051793842018390757[200] = 0.0;
   out_2051793842018390757[201] = 0.0;
   out_2051793842018390757[202] = 0.0;
   out_2051793842018390757[203] = 0.0;
   out_2051793842018390757[204] = 0.0;
   out_2051793842018390757[205] = 0.0;
   out_2051793842018390757[206] = 0.0;
   out_2051793842018390757[207] = 0.0;
   out_2051793842018390757[208] = 0.0;
   out_2051793842018390757[209] = 1.0;
   out_2051793842018390757[210] = 0.0;
   out_2051793842018390757[211] = 0.0;
   out_2051793842018390757[212] = 0.0;
   out_2051793842018390757[213] = 0.0;
   out_2051793842018390757[214] = 0.0;
   out_2051793842018390757[215] = 0.0;
   out_2051793842018390757[216] = 0.0;
   out_2051793842018390757[217] = 0.0;
   out_2051793842018390757[218] = 0.0;
   out_2051793842018390757[219] = 0.0;
   out_2051793842018390757[220] = 0.0;
   out_2051793842018390757[221] = 0.0;
   out_2051793842018390757[222] = 0.0;
   out_2051793842018390757[223] = 0.0;
   out_2051793842018390757[224] = 0.0;
   out_2051793842018390757[225] = 0.0;
   out_2051793842018390757[226] = 0.0;
   out_2051793842018390757[227] = 0.0;
   out_2051793842018390757[228] = 1.0;
   out_2051793842018390757[229] = 0.0;
   out_2051793842018390757[230] = 0.0;
   out_2051793842018390757[231] = 0.0;
   out_2051793842018390757[232] = 0.0;
   out_2051793842018390757[233] = 0.0;
   out_2051793842018390757[234] = 0.0;
   out_2051793842018390757[235] = 0.0;
   out_2051793842018390757[236] = 0.0;
   out_2051793842018390757[237] = 0.0;
   out_2051793842018390757[238] = 0.0;
   out_2051793842018390757[239] = 0.0;
   out_2051793842018390757[240] = 0.0;
   out_2051793842018390757[241] = 0.0;
   out_2051793842018390757[242] = 0.0;
   out_2051793842018390757[243] = 0.0;
   out_2051793842018390757[244] = 0.0;
   out_2051793842018390757[245] = 0.0;
   out_2051793842018390757[246] = 0.0;
   out_2051793842018390757[247] = 1.0;
   out_2051793842018390757[248] = 0.0;
   out_2051793842018390757[249] = 0.0;
   out_2051793842018390757[250] = 0.0;
   out_2051793842018390757[251] = 0.0;
   out_2051793842018390757[252] = 0.0;
   out_2051793842018390757[253] = 0.0;
   out_2051793842018390757[254] = 0.0;
   out_2051793842018390757[255] = 0.0;
   out_2051793842018390757[256] = 0.0;
   out_2051793842018390757[257] = 0.0;
   out_2051793842018390757[258] = 0.0;
   out_2051793842018390757[259] = 0.0;
   out_2051793842018390757[260] = 0.0;
   out_2051793842018390757[261] = 0.0;
   out_2051793842018390757[262] = 0.0;
   out_2051793842018390757[263] = 0.0;
   out_2051793842018390757[264] = 0.0;
   out_2051793842018390757[265] = 0.0;
   out_2051793842018390757[266] = 1.0;
   out_2051793842018390757[267] = 0.0;
   out_2051793842018390757[268] = 0.0;
   out_2051793842018390757[269] = 0.0;
   out_2051793842018390757[270] = 0.0;
   out_2051793842018390757[271] = 0.0;
   out_2051793842018390757[272] = 0.0;
   out_2051793842018390757[273] = 0.0;
   out_2051793842018390757[274] = 0.0;
   out_2051793842018390757[275] = 0.0;
   out_2051793842018390757[276] = 0.0;
   out_2051793842018390757[277] = 0.0;
   out_2051793842018390757[278] = 0.0;
   out_2051793842018390757[279] = 0.0;
   out_2051793842018390757[280] = 0.0;
   out_2051793842018390757[281] = 0.0;
   out_2051793842018390757[282] = 0.0;
   out_2051793842018390757[283] = 0.0;
   out_2051793842018390757[284] = 0.0;
   out_2051793842018390757[285] = 1.0;
   out_2051793842018390757[286] = 0.0;
   out_2051793842018390757[287] = 0.0;
   out_2051793842018390757[288] = 0.0;
   out_2051793842018390757[289] = 0.0;
   out_2051793842018390757[290] = 0.0;
   out_2051793842018390757[291] = 0.0;
   out_2051793842018390757[292] = 0.0;
   out_2051793842018390757[293] = 0.0;
   out_2051793842018390757[294] = 0.0;
   out_2051793842018390757[295] = 0.0;
   out_2051793842018390757[296] = 0.0;
   out_2051793842018390757[297] = 0.0;
   out_2051793842018390757[298] = 0.0;
   out_2051793842018390757[299] = 0.0;
   out_2051793842018390757[300] = 0.0;
   out_2051793842018390757[301] = 0.0;
   out_2051793842018390757[302] = 0.0;
   out_2051793842018390757[303] = 0.0;
   out_2051793842018390757[304] = 1.0;
   out_2051793842018390757[305] = 0.0;
   out_2051793842018390757[306] = 0.0;
   out_2051793842018390757[307] = 0.0;
   out_2051793842018390757[308] = 0.0;
   out_2051793842018390757[309] = 0.0;
   out_2051793842018390757[310] = 0.0;
   out_2051793842018390757[311] = 0.0;
   out_2051793842018390757[312] = 0.0;
   out_2051793842018390757[313] = 0.0;
   out_2051793842018390757[314] = 0.0;
   out_2051793842018390757[315] = 0.0;
   out_2051793842018390757[316] = 0.0;
   out_2051793842018390757[317] = 0.0;
   out_2051793842018390757[318] = 0.0;
   out_2051793842018390757[319] = 0.0;
   out_2051793842018390757[320] = 0.0;
   out_2051793842018390757[321] = 0.0;
   out_2051793842018390757[322] = 0.0;
   out_2051793842018390757[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1030564392189718068) {
   out_1030564392189718068[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1030564392189718068[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1030564392189718068[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1030564392189718068[3] = dt*state[12] + state[3];
   out_1030564392189718068[4] = dt*state[13] + state[4];
   out_1030564392189718068[5] = dt*state[14] + state[5];
   out_1030564392189718068[6] = state[6];
   out_1030564392189718068[7] = state[7];
   out_1030564392189718068[8] = state[8];
   out_1030564392189718068[9] = state[9];
   out_1030564392189718068[10] = state[10];
   out_1030564392189718068[11] = state[11];
   out_1030564392189718068[12] = state[12];
   out_1030564392189718068[13] = state[13];
   out_1030564392189718068[14] = state[14];
   out_1030564392189718068[15] = state[15];
   out_1030564392189718068[16] = state[16];
   out_1030564392189718068[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8175556432247197768) {
   out_8175556432247197768[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8175556432247197768[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8175556432247197768[2] = 0;
   out_8175556432247197768[3] = 0;
   out_8175556432247197768[4] = 0;
   out_8175556432247197768[5] = 0;
   out_8175556432247197768[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8175556432247197768[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8175556432247197768[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8175556432247197768[9] = 0;
   out_8175556432247197768[10] = 0;
   out_8175556432247197768[11] = 0;
   out_8175556432247197768[12] = 0;
   out_8175556432247197768[13] = 0;
   out_8175556432247197768[14] = 0;
   out_8175556432247197768[15] = 0;
   out_8175556432247197768[16] = 0;
   out_8175556432247197768[17] = 0;
   out_8175556432247197768[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8175556432247197768[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8175556432247197768[20] = 0;
   out_8175556432247197768[21] = 0;
   out_8175556432247197768[22] = 0;
   out_8175556432247197768[23] = 0;
   out_8175556432247197768[24] = 0;
   out_8175556432247197768[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8175556432247197768[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8175556432247197768[27] = 0;
   out_8175556432247197768[28] = 0;
   out_8175556432247197768[29] = 0;
   out_8175556432247197768[30] = 0;
   out_8175556432247197768[31] = 0;
   out_8175556432247197768[32] = 0;
   out_8175556432247197768[33] = 0;
   out_8175556432247197768[34] = 0;
   out_8175556432247197768[35] = 0;
   out_8175556432247197768[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8175556432247197768[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8175556432247197768[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8175556432247197768[39] = 0;
   out_8175556432247197768[40] = 0;
   out_8175556432247197768[41] = 0;
   out_8175556432247197768[42] = 0;
   out_8175556432247197768[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8175556432247197768[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8175556432247197768[45] = 0;
   out_8175556432247197768[46] = 0;
   out_8175556432247197768[47] = 0;
   out_8175556432247197768[48] = 0;
   out_8175556432247197768[49] = 0;
   out_8175556432247197768[50] = 0;
   out_8175556432247197768[51] = 0;
   out_8175556432247197768[52] = 0;
   out_8175556432247197768[53] = 0;
   out_8175556432247197768[54] = 0;
   out_8175556432247197768[55] = 0;
   out_8175556432247197768[56] = 0;
   out_8175556432247197768[57] = 1;
   out_8175556432247197768[58] = 0;
   out_8175556432247197768[59] = 0;
   out_8175556432247197768[60] = 0;
   out_8175556432247197768[61] = 0;
   out_8175556432247197768[62] = 0;
   out_8175556432247197768[63] = 0;
   out_8175556432247197768[64] = 0;
   out_8175556432247197768[65] = 0;
   out_8175556432247197768[66] = dt;
   out_8175556432247197768[67] = 0;
   out_8175556432247197768[68] = 0;
   out_8175556432247197768[69] = 0;
   out_8175556432247197768[70] = 0;
   out_8175556432247197768[71] = 0;
   out_8175556432247197768[72] = 0;
   out_8175556432247197768[73] = 0;
   out_8175556432247197768[74] = 0;
   out_8175556432247197768[75] = 0;
   out_8175556432247197768[76] = 1;
   out_8175556432247197768[77] = 0;
   out_8175556432247197768[78] = 0;
   out_8175556432247197768[79] = 0;
   out_8175556432247197768[80] = 0;
   out_8175556432247197768[81] = 0;
   out_8175556432247197768[82] = 0;
   out_8175556432247197768[83] = 0;
   out_8175556432247197768[84] = 0;
   out_8175556432247197768[85] = dt;
   out_8175556432247197768[86] = 0;
   out_8175556432247197768[87] = 0;
   out_8175556432247197768[88] = 0;
   out_8175556432247197768[89] = 0;
   out_8175556432247197768[90] = 0;
   out_8175556432247197768[91] = 0;
   out_8175556432247197768[92] = 0;
   out_8175556432247197768[93] = 0;
   out_8175556432247197768[94] = 0;
   out_8175556432247197768[95] = 1;
   out_8175556432247197768[96] = 0;
   out_8175556432247197768[97] = 0;
   out_8175556432247197768[98] = 0;
   out_8175556432247197768[99] = 0;
   out_8175556432247197768[100] = 0;
   out_8175556432247197768[101] = 0;
   out_8175556432247197768[102] = 0;
   out_8175556432247197768[103] = 0;
   out_8175556432247197768[104] = dt;
   out_8175556432247197768[105] = 0;
   out_8175556432247197768[106] = 0;
   out_8175556432247197768[107] = 0;
   out_8175556432247197768[108] = 0;
   out_8175556432247197768[109] = 0;
   out_8175556432247197768[110] = 0;
   out_8175556432247197768[111] = 0;
   out_8175556432247197768[112] = 0;
   out_8175556432247197768[113] = 0;
   out_8175556432247197768[114] = 1;
   out_8175556432247197768[115] = 0;
   out_8175556432247197768[116] = 0;
   out_8175556432247197768[117] = 0;
   out_8175556432247197768[118] = 0;
   out_8175556432247197768[119] = 0;
   out_8175556432247197768[120] = 0;
   out_8175556432247197768[121] = 0;
   out_8175556432247197768[122] = 0;
   out_8175556432247197768[123] = 0;
   out_8175556432247197768[124] = 0;
   out_8175556432247197768[125] = 0;
   out_8175556432247197768[126] = 0;
   out_8175556432247197768[127] = 0;
   out_8175556432247197768[128] = 0;
   out_8175556432247197768[129] = 0;
   out_8175556432247197768[130] = 0;
   out_8175556432247197768[131] = 0;
   out_8175556432247197768[132] = 0;
   out_8175556432247197768[133] = 1;
   out_8175556432247197768[134] = 0;
   out_8175556432247197768[135] = 0;
   out_8175556432247197768[136] = 0;
   out_8175556432247197768[137] = 0;
   out_8175556432247197768[138] = 0;
   out_8175556432247197768[139] = 0;
   out_8175556432247197768[140] = 0;
   out_8175556432247197768[141] = 0;
   out_8175556432247197768[142] = 0;
   out_8175556432247197768[143] = 0;
   out_8175556432247197768[144] = 0;
   out_8175556432247197768[145] = 0;
   out_8175556432247197768[146] = 0;
   out_8175556432247197768[147] = 0;
   out_8175556432247197768[148] = 0;
   out_8175556432247197768[149] = 0;
   out_8175556432247197768[150] = 0;
   out_8175556432247197768[151] = 0;
   out_8175556432247197768[152] = 1;
   out_8175556432247197768[153] = 0;
   out_8175556432247197768[154] = 0;
   out_8175556432247197768[155] = 0;
   out_8175556432247197768[156] = 0;
   out_8175556432247197768[157] = 0;
   out_8175556432247197768[158] = 0;
   out_8175556432247197768[159] = 0;
   out_8175556432247197768[160] = 0;
   out_8175556432247197768[161] = 0;
   out_8175556432247197768[162] = 0;
   out_8175556432247197768[163] = 0;
   out_8175556432247197768[164] = 0;
   out_8175556432247197768[165] = 0;
   out_8175556432247197768[166] = 0;
   out_8175556432247197768[167] = 0;
   out_8175556432247197768[168] = 0;
   out_8175556432247197768[169] = 0;
   out_8175556432247197768[170] = 0;
   out_8175556432247197768[171] = 1;
   out_8175556432247197768[172] = 0;
   out_8175556432247197768[173] = 0;
   out_8175556432247197768[174] = 0;
   out_8175556432247197768[175] = 0;
   out_8175556432247197768[176] = 0;
   out_8175556432247197768[177] = 0;
   out_8175556432247197768[178] = 0;
   out_8175556432247197768[179] = 0;
   out_8175556432247197768[180] = 0;
   out_8175556432247197768[181] = 0;
   out_8175556432247197768[182] = 0;
   out_8175556432247197768[183] = 0;
   out_8175556432247197768[184] = 0;
   out_8175556432247197768[185] = 0;
   out_8175556432247197768[186] = 0;
   out_8175556432247197768[187] = 0;
   out_8175556432247197768[188] = 0;
   out_8175556432247197768[189] = 0;
   out_8175556432247197768[190] = 1;
   out_8175556432247197768[191] = 0;
   out_8175556432247197768[192] = 0;
   out_8175556432247197768[193] = 0;
   out_8175556432247197768[194] = 0;
   out_8175556432247197768[195] = 0;
   out_8175556432247197768[196] = 0;
   out_8175556432247197768[197] = 0;
   out_8175556432247197768[198] = 0;
   out_8175556432247197768[199] = 0;
   out_8175556432247197768[200] = 0;
   out_8175556432247197768[201] = 0;
   out_8175556432247197768[202] = 0;
   out_8175556432247197768[203] = 0;
   out_8175556432247197768[204] = 0;
   out_8175556432247197768[205] = 0;
   out_8175556432247197768[206] = 0;
   out_8175556432247197768[207] = 0;
   out_8175556432247197768[208] = 0;
   out_8175556432247197768[209] = 1;
   out_8175556432247197768[210] = 0;
   out_8175556432247197768[211] = 0;
   out_8175556432247197768[212] = 0;
   out_8175556432247197768[213] = 0;
   out_8175556432247197768[214] = 0;
   out_8175556432247197768[215] = 0;
   out_8175556432247197768[216] = 0;
   out_8175556432247197768[217] = 0;
   out_8175556432247197768[218] = 0;
   out_8175556432247197768[219] = 0;
   out_8175556432247197768[220] = 0;
   out_8175556432247197768[221] = 0;
   out_8175556432247197768[222] = 0;
   out_8175556432247197768[223] = 0;
   out_8175556432247197768[224] = 0;
   out_8175556432247197768[225] = 0;
   out_8175556432247197768[226] = 0;
   out_8175556432247197768[227] = 0;
   out_8175556432247197768[228] = 1;
   out_8175556432247197768[229] = 0;
   out_8175556432247197768[230] = 0;
   out_8175556432247197768[231] = 0;
   out_8175556432247197768[232] = 0;
   out_8175556432247197768[233] = 0;
   out_8175556432247197768[234] = 0;
   out_8175556432247197768[235] = 0;
   out_8175556432247197768[236] = 0;
   out_8175556432247197768[237] = 0;
   out_8175556432247197768[238] = 0;
   out_8175556432247197768[239] = 0;
   out_8175556432247197768[240] = 0;
   out_8175556432247197768[241] = 0;
   out_8175556432247197768[242] = 0;
   out_8175556432247197768[243] = 0;
   out_8175556432247197768[244] = 0;
   out_8175556432247197768[245] = 0;
   out_8175556432247197768[246] = 0;
   out_8175556432247197768[247] = 1;
   out_8175556432247197768[248] = 0;
   out_8175556432247197768[249] = 0;
   out_8175556432247197768[250] = 0;
   out_8175556432247197768[251] = 0;
   out_8175556432247197768[252] = 0;
   out_8175556432247197768[253] = 0;
   out_8175556432247197768[254] = 0;
   out_8175556432247197768[255] = 0;
   out_8175556432247197768[256] = 0;
   out_8175556432247197768[257] = 0;
   out_8175556432247197768[258] = 0;
   out_8175556432247197768[259] = 0;
   out_8175556432247197768[260] = 0;
   out_8175556432247197768[261] = 0;
   out_8175556432247197768[262] = 0;
   out_8175556432247197768[263] = 0;
   out_8175556432247197768[264] = 0;
   out_8175556432247197768[265] = 0;
   out_8175556432247197768[266] = 1;
   out_8175556432247197768[267] = 0;
   out_8175556432247197768[268] = 0;
   out_8175556432247197768[269] = 0;
   out_8175556432247197768[270] = 0;
   out_8175556432247197768[271] = 0;
   out_8175556432247197768[272] = 0;
   out_8175556432247197768[273] = 0;
   out_8175556432247197768[274] = 0;
   out_8175556432247197768[275] = 0;
   out_8175556432247197768[276] = 0;
   out_8175556432247197768[277] = 0;
   out_8175556432247197768[278] = 0;
   out_8175556432247197768[279] = 0;
   out_8175556432247197768[280] = 0;
   out_8175556432247197768[281] = 0;
   out_8175556432247197768[282] = 0;
   out_8175556432247197768[283] = 0;
   out_8175556432247197768[284] = 0;
   out_8175556432247197768[285] = 1;
   out_8175556432247197768[286] = 0;
   out_8175556432247197768[287] = 0;
   out_8175556432247197768[288] = 0;
   out_8175556432247197768[289] = 0;
   out_8175556432247197768[290] = 0;
   out_8175556432247197768[291] = 0;
   out_8175556432247197768[292] = 0;
   out_8175556432247197768[293] = 0;
   out_8175556432247197768[294] = 0;
   out_8175556432247197768[295] = 0;
   out_8175556432247197768[296] = 0;
   out_8175556432247197768[297] = 0;
   out_8175556432247197768[298] = 0;
   out_8175556432247197768[299] = 0;
   out_8175556432247197768[300] = 0;
   out_8175556432247197768[301] = 0;
   out_8175556432247197768[302] = 0;
   out_8175556432247197768[303] = 0;
   out_8175556432247197768[304] = 1;
   out_8175556432247197768[305] = 0;
   out_8175556432247197768[306] = 0;
   out_8175556432247197768[307] = 0;
   out_8175556432247197768[308] = 0;
   out_8175556432247197768[309] = 0;
   out_8175556432247197768[310] = 0;
   out_8175556432247197768[311] = 0;
   out_8175556432247197768[312] = 0;
   out_8175556432247197768[313] = 0;
   out_8175556432247197768[314] = 0;
   out_8175556432247197768[315] = 0;
   out_8175556432247197768[316] = 0;
   out_8175556432247197768[317] = 0;
   out_8175556432247197768[318] = 0;
   out_8175556432247197768[319] = 0;
   out_8175556432247197768[320] = 0;
   out_8175556432247197768[321] = 0;
   out_8175556432247197768[322] = 0;
   out_8175556432247197768[323] = 1;
}
void h_4(double *state, double *unused, double *out_4843592748572526684) {
   out_4843592748572526684[0] = state[6] + state[9];
   out_4843592748572526684[1] = state[7] + state[10];
   out_4843592748572526684[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6892567824039430585) {
   out_6892567824039430585[0] = 0;
   out_6892567824039430585[1] = 0;
   out_6892567824039430585[2] = 0;
   out_6892567824039430585[3] = 0;
   out_6892567824039430585[4] = 0;
   out_6892567824039430585[5] = 0;
   out_6892567824039430585[6] = 1;
   out_6892567824039430585[7] = 0;
   out_6892567824039430585[8] = 0;
   out_6892567824039430585[9] = 1;
   out_6892567824039430585[10] = 0;
   out_6892567824039430585[11] = 0;
   out_6892567824039430585[12] = 0;
   out_6892567824039430585[13] = 0;
   out_6892567824039430585[14] = 0;
   out_6892567824039430585[15] = 0;
   out_6892567824039430585[16] = 0;
   out_6892567824039430585[17] = 0;
   out_6892567824039430585[18] = 0;
   out_6892567824039430585[19] = 0;
   out_6892567824039430585[20] = 0;
   out_6892567824039430585[21] = 0;
   out_6892567824039430585[22] = 0;
   out_6892567824039430585[23] = 0;
   out_6892567824039430585[24] = 0;
   out_6892567824039430585[25] = 1;
   out_6892567824039430585[26] = 0;
   out_6892567824039430585[27] = 0;
   out_6892567824039430585[28] = 1;
   out_6892567824039430585[29] = 0;
   out_6892567824039430585[30] = 0;
   out_6892567824039430585[31] = 0;
   out_6892567824039430585[32] = 0;
   out_6892567824039430585[33] = 0;
   out_6892567824039430585[34] = 0;
   out_6892567824039430585[35] = 0;
   out_6892567824039430585[36] = 0;
   out_6892567824039430585[37] = 0;
   out_6892567824039430585[38] = 0;
   out_6892567824039430585[39] = 0;
   out_6892567824039430585[40] = 0;
   out_6892567824039430585[41] = 0;
   out_6892567824039430585[42] = 0;
   out_6892567824039430585[43] = 0;
   out_6892567824039430585[44] = 1;
   out_6892567824039430585[45] = 0;
   out_6892567824039430585[46] = 0;
   out_6892567824039430585[47] = 1;
   out_6892567824039430585[48] = 0;
   out_6892567824039430585[49] = 0;
   out_6892567824039430585[50] = 0;
   out_6892567824039430585[51] = 0;
   out_6892567824039430585[52] = 0;
   out_6892567824039430585[53] = 0;
}
void h_10(double *state, double *unused, double *out_3178717001943207923) {
   out_3178717001943207923[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3178717001943207923[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3178717001943207923[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2573295092091137817) {
   out_2573295092091137817[0] = 0;
   out_2573295092091137817[1] = 9.8100000000000005*cos(state[1]);
   out_2573295092091137817[2] = 0;
   out_2573295092091137817[3] = 0;
   out_2573295092091137817[4] = -state[8];
   out_2573295092091137817[5] = state[7];
   out_2573295092091137817[6] = 0;
   out_2573295092091137817[7] = state[5];
   out_2573295092091137817[8] = -state[4];
   out_2573295092091137817[9] = 0;
   out_2573295092091137817[10] = 0;
   out_2573295092091137817[11] = 0;
   out_2573295092091137817[12] = 1;
   out_2573295092091137817[13] = 0;
   out_2573295092091137817[14] = 0;
   out_2573295092091137817[15] = 1;
   out_2573295092091137817[16] = 0;
   out_2573295092091137817[17] = 0;
   out_2573295092091137817[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2573295092091137817[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2573295092091137817[20] = 0;
   out_2573295092091137817[21] = state[8];
   out_2573295092091137817[22] = 0;
   out_2573295092091137817[23] = -state[6];
   out_2573295092091137817[24] = -state[5];
   out_2573295092091137817[25] = 0;
   out_2573295092091137817[26] = state[3];
   out_2573295092091137817[27] = 0;
   out_2573295092091137817[28] = 0;
   out_2573295092091137817[29] = 0;
   out_2573295092091137817[30] = 0;
   out_2573295092091137817[31] = 1;
   out_2573295092091137817[32] = 0;
   out_2573295092091137817[33] = 0;
   out_2573295092091137817[34] = 1;
   out_2573295092091137817[35] = 0;
   out_2573295092091137817[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2573295092091137817[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2573295092091137817[38] = 0;
   out_2573295092091137817[39] = -state[7];
   out_2573295092091137817[40] = state[6];
   out_2573295092091137817[41] = 0;
   out_2573295092091137817[42] = state[4];
   out_2573295092091137817[43] = -state[3];
   out_2573295092091137817[44] = 0;
   out_2573295092091137817[45] = 0;
   out_2573295092091137817[46] = 0;
   out_2573295092091137817[47] = 0;
   out_2573295092091137817[48] = 0;
   out_2573295092091137817[49] = 0;
   out_2573295092091137817[50] = 1;
   out_2573295092091137817[51] = 0;
   out_2573295092091137817[52] = 0;
   out_2573295092091137817[53] = 1;
}
void h_13(double *state, double *unused, double *out_5513627389062910490) {
   out_5513627389062910490[0] = state[3];
   out_5513627389062910490[1] = state[4];
   out_5513627389062910490[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3680293998707097784) {
   out_3680293998707097784[0] = 0;
   out_3680293998707097784[1] = 0;
   out_3680293998707097784[2] = 0;
   out_3680293998707097784[3] = 1;
   out_3680293998707097784[4] = 0;
   out_3680293998707097784[5] = 0;
   out_3680293998707097784[6] = 0;
   out_3680293998707097784[7] = 0;
   out_3680293998707097784[8] = 0;
   out_3680293998707097784[9] = 0;
   out_3680293998707097784[10] = 0;
   out_3680293998707097784[11] = 0;
   out_3680293998707097784[12] = 0;
   out_3680293998707097784[13] = 0;
   out_3680293998707097784[14] = 0;
   out_3680293998707097784[15] = 0;
   out_3680293998707097784[16] = 0;
   out_3680293998707097784[17] = 0;
   out_3680293998707097784[18] = 0;
   out_3680293998707097784[19] = 0;
   out_3680293998707097784[20] = 0;
   out_3680293998707097784[21] = 0;
   out_3680293998707097784[22] = 1;
   out_3680293998707097784[23] = 0;
   out_3680293998707097784[24] = 0;
   out_3680293998707097784[25] = 0;
   out_3680293998707097784[26] = 0;
   out_3680293998707097784[27] = 0;
   out_3680293998707097784[28] = 0;
   out_3680293998707097784[29] = 0;
   out_3680293998707097784[30] = 0;
   out_3680293998707097784[31] = 0;
   out_3680293998707097784[32] = 0;
   out_3680293998707097784[33] = 0;
   out_3680293998707097784[34] = 0;
   out_3680293998707097784[35] = 0;
   out_3680293998707097784[36] = 0;
   out_3680293998707097784[37] = 0;
   out_3680293998707097784[38] = 0;
   out_3680293998707097784[39] = 0;
   out_3680293998707097784[40] = 0;
   out_3680293998707097784[41] = 1;
   out_3680293998707097784[42] = 0;
   out_3680293998707097784[43] = 0;
   out_3680293998707097784[44] = 0;
   out_3680293998707097784[45] = 0;
   out_3680293998707097784[46] = 0;
   out_3680293998707097784[47] = 0;
   out_3680293998707097784[48] = 0;
   out_3680293998707097784[49] = 0;
   out_3680293998707097784[50] = 0;
   out_3680293998707097784[51] = 0;
   out_3680293998707097784[52] = 0;
   out_3680293998707097784[53] = 0;
}
void h_14(double *state, double *unused, double *out_1993056798844969004) {
   out_1993056798844969004[0] = state[6];
   out_1993056798844969004[1] = state[7];
   out_1993056798844969004[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8471387817374748735) {
   out_8471387817374748735[0] = 0;
   out_8471387817374748735[1] = 0;
   out_8471387817374748735[2] = 0;
   out_8471387817374748735[3] = 0;
   out_8471387817374748735[4] = 0;
   out_8471387817374748735[5] = 0;
   out_8471387817374748735[6] = 1;
   out_8471387817374748735[7] = 0;
   out_8471387817374748735[8] = 0;
   out_8471387817374748735[9] = 0;
   out_8471387817374748735[10] = 0;
   out_8471387817374748735[11] = 0;
   out_8471387817374748735[12] = 0;
   out_8471387817374748735[13] = 0;
   out_8471387817374748735[14] = 0;
   out_8471387817374748735[15] = 0;
   out_8471387817374748735[16] = 0;
   out_8471387817374748735[17] = 0;
   out_8471387817374748735[18] = 0;
   out_8471387817374748735[19] = 0;
   out_8471387817374748735[20] = 0;
   out_8471387817374748735[21] = 0;
   out_8471387817374748735[22] = 0;
   out_8471387817374748735[23] = 0;
   out_8471387817374748735[24] = 0;
   out_8471387817374748735[25] = 1;
   out_8471387817374748735[26] = 0;
   out_8471387817374748735[27] = 0;
   out_8471387817374748735[28] = 0;
   out_8471387817374748735[29] = 0;
   out_8471387817374748735[30] = 0;
   out_8471387817374748735[31] = 0;
   out_8471387817374748735[32] = 0;
   out_8471387817374748735[33] = 0;
   out_8471387817374748735[34] = 0;
   out_8471387817374748735[35] = 0;
   out_8471387817374748735[36] = 0;
   out_8471387817374748735[37] = 0;
   out_8471387817374748735[38] = 0;
   out_8471387817374748735[39] = 0;
   out_8471387817374748735[40] = 0;
   out_8471387817374748735[41] = 0;
   out_8471387817374748735[42] = 0;
   out_8471387817374748735[43] = 0;
   out_8471387817374748735[44] = 1;
   out_8471387817374748735[45] = 0;
   out_8471387817374748735[46] = 0;
   out_8471387817374748735[47] = 0;
   out_8471387817374748735[48] = 0;
   out_8471387817374748735[49] = 0;
   out_8471387817374748735[50] = 0;
   out_8471387817374748735[51] = 0;
   out_8471387817374748735[52] = 0;
   out_8471387817374748735[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3020435366952319765) {
  err_fun(nom_x, delta_x, out_3020435366952319765);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3417424495517393488) {
  inv_err_fun(nom_x, true_x, out_3417424495517393488);
}
void pose_H_mod_fun(double *state, double *out_2051793842018390757) {
  H_mod_fun(state, out_2051793842018390757);
}
void pose_f_fun(double *state, double dt, double *out_1030564392189718068) {
  f_fun(state,  dt, out_1030564392189718068);
}
void pose_F_fun(double *state, double dt, double *out_8175556432247197768) {
  F_fun(state,  dt, out_8175556432247197768);
}
void pose_h_4(double *state, double *unused, double *out_4843592748572526684) {
  h_4(state, unused, out_4843592748572526684);
}
void pose_H_4(double *state, double *unused, double *out_6892567824039430585) {
  H_4(state, unused, out_6892567824039430585);
}
void pose_h_10(double *state, double *unused, double *out_3178717001943207923) {
  h_10(state, unused, out_3178717001943207923);
}
void pose_H_10(double *state, double *unused, double *out_2573295092091137817) {
  H_10(state, unused, out_2573295092091137817);
}
void pose_h_13(double *state, double *unused, double *out_5513627389062910490) {
  h_13(state, unused, out_5513627389062910490);
}
void pose_H_13(double *state, double *unused, double *out_3680293998707097784) {
  H_13(state, unused, out_3680293998707097784);
}
void pose_h_14(double *state, double *unused, double *out_1993056798844969004) {
  h_14(state, unused, out_1993056798844969004);
}
void pose_H_14(double *state, double *unused, double *out_8471387817374748735) {
  H_14(state, unused, out_8471387817374748735);
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
