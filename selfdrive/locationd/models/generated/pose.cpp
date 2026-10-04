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
void err_fun(double *nom_x, double *delta_x, double *out_4883205334769300531) {
   out_4883205334769300531[0] = delta_x[0] + nom_x[0];
   out_4883205334769300531[1] = delta_x[1] + nom_x[1];
   out_4883205334769300531[2] = delta_x[2] + nom_x[2];
   out_4883205334769300531[3] = delta_x[3] + nom_x[3];
   out_4883205334769300531[4] = delta_x[4] + nom_x[4];
   out_4883205334769300531[5] = delta_x[5] + nom_x[5];
   out_4883205334769300531[6] = delta_x[6] + nom_x[6];
   out_4883205334769300531[7] = delta_x[7] + nom_x[7];
   out_4883205334769300531[8] = delta_x[8] + nom_x[8];
   out_4883205334769300531[9] = delta_x[9] + nom_x[9];
   out_4883205334769300531[10] = delta_x[10] + nom_x[10];
   out_4883205334769300531[11] = delta_x[11] + nom_x[11];
   out_4883205334769300531[12] = delta_x[12] + nom_x[12];
   out_4883205334769300531[13] = delta_x[13] + nom_x[13];
   out_4883205334769300531[14] = delta_x[14] + nom_x[14];
   out_4883205334769300531[15] = delta_x[15] + nom_x[15];
   out_4883205334769300531[16] = delta_x[16] + nom_x[16];
   out_4883205334769300531[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2778782879349748614) {
   out_2778782879349748614[0] = -nom_x[0] + true_x[0];
   out_2778782879349748614[1] = -nom_x[1] + true_x[1];
   out_2778782879349748614[2] = -nom_x[2] + true_x[2];
   out_2778782879349748614[3] = -nom_x[3] + true_x[3];
   out_2778782879349748614[4] = -nom_x[4] + true_x[4];
   out_2778782879349748614[5] = -nom_x[5] + true_x[5];
   out_2778782879349748614[6] = -nom_x[6] + true_x[6];
   out_2778782879349748614[7] = -nom_x[7] + true_x[7];
   out_2778782879349748614[8] = -nom_x[8] + true_x[8];
   out_2778782879349748614[9] = -nom_x[9] + true_x[9];
   out_2778782879349748614[10] = -nom_x[10] + true_x[10];
   out_2778782879349748614[11] = -nom_x[11] + true_x[11];
   out_2778782879349748614[12] = -nom_x[12] + true_x[12];
   out_2778782879349748614[13] = -nom_x[13] + true_x[13];
   out_2778782879349748614[14] = -nom_x[14] + true_x[14];
   out_2778782879349748614[15] = -nom_x[15] + true_x[15];
   out_2778782879349748614[16] = -nom_x[16] + true_x[16];
   out_2778782879349748614[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_650126789788623456) {
   out_650126789788623456[0] = 1.0;
   out_650126789788623456[1] = 0.0;
   out_650126789788623456[2] = 0.0;
   out_650126789788623456[3] = 0.0;
   out_650126789788623456[4] = 0.0;
   out_650126789788623456[5] = 0.0;
   out_650126789788623456[6] = 0.0;
   out_650126789788623456[7] = 0.0;
   out_650126789788623456[8] = 0.0;
   out_650126789788623456[9] = 0.0;
   out_650126789788623456[10] = 0.0;
   out_650126789788623456[11] = 0.0;
   out_650126789788623456[12] = 0.0;
   out_650126789788623456[13] = 0.0;
   out_650126789788623456[14] = 0.0;
   out_650126789788623456[15] = 0.0;
   out_650126789788623456[16] = 0.0;
   out_650126789788623456[17] = 0.0;
   out_650126789788623456[18] = 0.0;
   out_650126789788623456[19] = 1.0;
   out_650126789788623456[20] = 0.0;
   out_650126789788623456[21] = 0.0;
   out_650126789788623456[22] = 0.0;
   out_650126789788623456[23] = 0.0;
   out_650126789788623456[24] = 0.0;
   out_650126789788623456[25] = 0.0;
   out_650126789788623456[26] = 0.0;
   out_650126789788623456[27] = 0.0;
   out_650126789788623456[28] = 0.0;
   out_650126789788623456[29] = 0.0;
   out_650126789788623456[30] = 0.0;
   out_650126789788623456[31] = 0.0;
   out_650126789788623456[32] = 0.0;
   out_650126789788623456[33] = 0.0;
   out_650126789788623456[34] = 0.0;
   out_650126789788623456[35] = 0.0;
   out_650126789788623456[36] = 0.0;
   out_650126789788623456[37] = 0.0;
   out_650126789788623456[38] = 1.0;
   out_650126789788623456[39] = 0.0;
   out_650126789788623456[40] = 0.0;
   out_650126789788623456[41] = 0.0;
   out_650126789788623456[42] = 0.0;
   out_650126789788623456[43] = 0.0;
   out_650126789788623456[44] = 0.0;
   out_650126789788623456[45] = 0.0;
   out_650126789788623456[46] = 0.0;
   out_650126789788623456[47] = 0.0;
   out_650126789788623456[48] = 0.0;
   out_650126789788623456[49] = 0.0;
   out_650126789788623456[50] = 0.0;
   out_650126789788623456[51] = 0.0;
   out_650126789788623456[52] = 0.0;
   out_650126789788623456[53] = 0.0;
   out_650126789788623456[54] = 0.0;
   out_650126789788623456[55] = 0.0;
   out_650126789788623456[56] = 0.0;
   out_650126789788623456[57] = 1.0;
   out_650126789788623456[58] = 0.0;
   out_650126789788623456[59] = 0.0;
   out_650126789788623456[60] = 0.0;
   out_650126789788623456[61] = 0.0;
   out_650126789788623456[62] = 0.0;
   out_650126789788623456[63] = 0.0;
   out_650126789788623456[64] = 0.0;
   out_650126789788623456[65] = 0.0;
   out_650126789788623456[66] = 0.0;
   out_650126789788623456[67] = 0.0;
   out_650126789788623456[68] = 0.0;
   out_650126789788623456[69] = 0.0;
   out_650126789788623456[70] = 0.0;
   out_650126789788623456[71] = 0.0;
   out_650126789788623456[72] = 0.0;
   out_650126789788623456[73] = 0.0;
   out_650126789788623456[74] = 0.0;
   out_650126789788623456[75] = 0.0;
   out_650126789788623456[76] = 1.0;
   out_650126789788623456[77] = 0.0;
   out_650126789788623456[78] = 0.0;
   out_650126789788623456[79] = 0.0;
   out_650126789788623456[80] = 0.0;
   out_650126789788623456[81] = 0.0;
   out_650126789788623456[82] = 0.0;
   out_650126789788623456[83] = 0.0;
   out_650126789788623456[84] = 0.0;
   out_650126789788623456[85] = 0.0;
   out_650126789788623456[86] = 0.0;
   out_650126789788623456[87] = 0.0;
   out_650126789788623456[88] = 0.0;
   out_650126789788623456[89] = 0.0;
   out_650126789788623456[90] = 0.0;
   out_650126789788623456[91] = 0.0;
   out_650126789788623456[92] = 0.0;
   out_650126789788623456[93] = 0.0;
   out_650126789788623456[94] = 0.0;
   out_650126789788623456[95] = 1.0;
   out_650126789788623456[96] = 0.0;
   out_650126789788623456[97] = 0.0;
   out_650126789788623456[98] = 0.0;
   out_650126789788623456[99] = 0.0;
   out_650126789788623456[100] = 0.0;
   out_650126789788623456[101] = 0.0;
   out_650126789788623456[102] = 0.0;
   out_650126789788623456[103] = 0.0;
   out_650126789788623456[104] = 0.0;
   out_650126789788623456[105] = 0.0;
   out_650126789788623456[106] = 0.0;
   out_650126789788623456[107] = 0.0;
   out_650126789788623456[108] = 0.0;
   out_650126789788623456[109] = 0.0;
   out_650126789788623456[110] = 0.0;
   out_650126789788623456[111] = 0.0;
   out_650126789788623456[112] = 0.0;
   out_650126789788623456[113] = 0.0;
   out_650126789788623456[114] = 1.0;
   out_650126789788623456[115] = 0.0;
   out_650126789788623456[116] = 0.0;
   out_650126789788623456[117] = 0.0;
   out_650126789788623456[118] = 0.0;
   out_650126789788623456[119] = 0.0;
   out_650126789788623456[120] = 0.0;
   out_650126789788623456[121] = 0.0;
   out_650126789788623456[122] = 0.0;
   out_650126789788623456[123] = 0.0;
   out_650126789788623456[124] = 0.0;
   out_650126789788623456[125] = 0.0;
   out_650126789788623456[126] = 0.0;
   out_650126789788623456[127] = 0.0;
   out_650126789788623456[128] = 0.0;
   out_650126789788623456[129] = 0.0;
   out_650126789788623456[130] = 0.0;
   out_650126789788623456[131] = 0.0;
   out_650126789788623456[132] = 0.0;
   out_650126789788623456[133] = 1.0;
   out_650126789788623456[134] = 0.0;
   out_650126789788623456[135] = 0.0;
   out_650126789788623456[136] = 0.0;
   out_650126789788623456[137] = 0.0;
   out_650126789788623456[138] = 0.0;
   out_650126789788623456[139] = 0.0;
   out_650126789788623456[140] = 0.0;
   out_650126789788623456[141] = 0.0;
   out_650126789788623456[142] = 0.0;
   out_650126789788623456[143] = 0.0;
   out_650126789788623456[144] = 0.0;
   out_650126789788623456[145] = 0.0;
   out_650126789788623456[146] = 0.0;
   out_650126789788623456[147] = 0.0;
   out_650126789788623456[148] = 0.0;
   out_650126789788623456[149] = 0.0;
   out_650126789788623456[150] = 0.0;
   out_650126789788623456[151] = 0.0;
   out_650126789788623456[152] = 1.0;
   out_650126789788623456[153] = 0.0;
   out_650126789788623456[154] = 0.0;
   out_650126789788623456[155] = 0.0;
   out_650126789788623456[156] = 0.0;
   out_650126789788623456[157] = 0.0;
   out_650126789788623456[158] = 0.0;
   out_650126789788623456[159] = 0.0;
   out_650126789788623456[160] = 0.0;
   out_650126789788623456[161] = 0.0;
   out_650126789788623456[162] = 0.0;
   out_650126789788623456[163] = 0.0;
   out_650126789788623456[164] = 0.0;
   out_650126789788623456[165] = 0.0;
   out_650126789788623456[166] = 0.0;
   out_650126789788623456[167] = 0.0;
   out_650126789788623456[168] = 0.0;
   out_650126789788623456[169] = 0.0;
   out_650126789788623456[170] = 0.0;
   out_650126789788623456[171] = 1.0;
   out_650126789788623456[172] = 0.0;
   out_650126789788623456[173] = 0.0;
   out_650126789788623456[174] = 0.0;
   out_650126789788623456[175] = 0.0;
   out_650126789788623456[176] = 0.0;
   out_650126789788623456[177] = 0.0;
   out_650126789788623456[178] = 0.0;
   out_650126789788623456[179] = 0.0;
   out_650126789788623456[180] = 0.0;
   out_650126789788623456[181] = 0.0;
   out_650126789788623456[182] = 0.0;
   out_650126789788623456[183] = 0.0;
   out_650126789788623456[184] = 0.0;
   out_650126789788623456[185] = 0.0;
   out_650126789788623456[186] = 0.0;
   out_650126789788623456[187] = 0.0;
   out_650126789788623456[188] = 0.0;
   out_650126789788623456[189] = 0.0;
   out_650126789788623456[190] = 1.0;
   out_650126789788623456[191] = 0.0;
   out_650126789788623456[192] = 0.0;
   out_650126789788623456[193] = 0.0;
   out_650126789788623456[194] = 0.0;
   out_650126789788623456[195] = 0.0;
   out_650126789788623456[196] = 0.0;
   out_650126789788623456[197] = 0.0;
   out_650126789788623456[198] = 0.0;
   out_650126789788623456[199] = 0.0;
   out_650126789788623456[200] = 0.0;
   out_650126789788623456[201] = 0.0;
   out_650126789788623456[202] = 0.0;
   out_650126789788623456[203] = 0.0;
   out_650126789788623456[204] = 0.0;
   out_650126789788623456[205] = 0.0;
   out_650126789788623456[206] = 0.0;
   out_650126789788623456[207] = 0.0;
   out_650126789788623456[208] = 0.0;
   out_650126789788623456[209] = 1.0;
   out_650126789788623456[210] = 0.0;
   out_650126789788623456[211] = 0.0;
   out_650126789788623456[212] = 0.0;
   out_650126789788623456[213] = 0.0;
   out_650126789788623456[214] = 0.0;
   out_650126789788623456[215] = 0.0;
   out_650126789788623456[216] = 0.0;
   out_650126789788623456[217] = 0.0;
   out_650126789788623456[218] = 0.0;
   out_650126789788623456[219] = 0.0;
   out_650126789788623456[220] = 0.0;
   out_650126789788623456[221] = 0.0;
   out_650126789788623456[222] = 0.0;
   out_650126789788623456[223] = 0.0;
   out_650126789788623456[224] = 0.0;
   out_650126789788623456[225] = 0.0;
   out_650126789788623456[226] = 0.0;
   out_650126789788623456[227] = 0.0;
   out_650126789788623456[228] = 1.0;
   out_650126789788623456[229] = 0.0;
   out_650126789788623456[230] = 0.0;
   out_650126789788623456[231] = 0.0;
   out_650126789788623456[232] = 0.0;
   out_650126789788623456[233] = 0.0;
   out_650126789788623456[234] = 0.0;
   out_650126789788623456[235] = 0.0;
   out_650126789788623456[236] = 0.0;
   out_650126789788623456[237] = 0.0;
   out_650126789788623456[238] = 0.0;
   out_650126789788623456[239] = 0.0;
   out_650126789788623456[240] = 0.0;
   out_650126789788623456[241] = 0.0;
   out_650126789788623456[242] = 0.0;
   out_650126789788623456[243] = 0.0;
   out_650126789788623456[244] = 0.0;
   out_650126789788623456[245] = 0.0;
   out_650126789788623456[246] = 0.0;
   out_650126789788623456[247] = 1.0;
   out_650126789788623456[248] = 0.0;
   out_650126789788623456[249] = 0.0;
   out_650126789788623456[250] = 0.0;
   out_650126789788623456[251] = 0.0;
   out_650126789788623456[252] = 0.0;
   out_650126789788623456[253] = 0.0;
   out_650126789788623456[254] = 0.0;
   out_650126789788623456[255] = 0.0;
   out_650126789788623456[256] = 0.0;
   out_650126789788623456[257] = 0.0;
   out_650126789788623456[258] = 0.0;
   out_650126789788623456[259] = 0.0;
   out_650126789788623456[260] = 0.0;
   out_650126789788623456[261] = 0.0;
   out_650126789788623456[262] = 0.0;
   out_650126789788623456[263] = 0.0;
   out_650126789788623456[264] = 0.0;
   out_650126789788623456[265] = 0.0;
   out_650126789788623456[266] = 1.0;
   out_650126789788623456[267] = 0.0;
   out_650126789788623456[268] = 0.0;
   out_650126789788623456[269] = 0.0;
   out_650126789788623456[270] = 0.0;
   out_650126789788623456[271] = 0.0;
   out_650126789788623456[272] = 0.0;
   out_650126789788623456[273] = 0.0;
   out_650126789788623456[274] = 0.0;
   out_650126789788623456[275] = 0.0;
   out_650126789788623456[276] = 0.0;
   out_650126789788623456[277] = 0.0;
   out_650126789788623456[278] = 0.0;
   out_650126789788623456[279] = 0.0;
   out_650126789788623456[280] = 0.0;
   out_650126789788623456[281] = 0.0;
   out_650126789788623456[282] = 0.0;
   out_650126789788623456[283] = 0.0;
   out_650126789788623456[284] = 0.0;
   out_650126789788623456[285] = 1.0;
   out_650126789788623456[286] = 0.0;
   out_650126789788623456[287] = 0.0;
   out_650126789788623456[288] = 0.0;
   out_650126789788623456[289] = 0.0;
   out_650126789788623456[290] = 0.0;
   out_650126789788623456[291] = 0.0;
   out_650126789788623456[292] = 0.0;
   out_650126789788623456[293] = 0.0;
   out_650126789788623456[294] = 0.0;
   out_650126789788623456[295] = 0.0;
   out_650126789788623456[296] = 0.0;
   out_650126789788623456[297] = 0.0;
   out_650126789788623456[298] = 0.0;
   out_650126789788623456[299] = 0.0;
   out_650126789788623456[300] = 0.0;
   out_650126789788623456[301] = 0.0;
   out_650126789788623456[302] = 0.0;
   out_650126789788623456[303] = 0.0;
   out_650126789788623456[304] = 1.0;
   out_650126789788623456[305] = 0.0;
   out_650126789788623456[306] = 0.0;
   out_650126789788623456[307] = 0.0;
   out_650126789788623456[308] = 0.0;
   out_650126789788623456[309] = 0.0;
   out_650126789788623456[310] = 0.0;
   out_650126789788623456[311] = 0.0;
   out_650126789788623456[312] = 0.0;
   out_650126789788623456[313] = 0.0;
   out_650126789788623456[314] = 0.0;
   out_650126789788623456[315] = 0.0;
   out_650126789788623456[316] = 0.0;
   out_650126789788623456[317] = 0.0;
   out_650126789788623456[318] = 0.0;
   out_650126789788623456[319] = 0.0;
   out_650126789788623456[320] = 0.0;
   out_650126789788623456[321] = 0.0;
   out_650126789788623456[322] = 0.0;
   out_650126789788623456[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8901743997806544277) {
   out_8901743997806544277[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8901743997806544277[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8901743997806544277[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8901743997806544277[3] = dt*state[12] + state[3];
   out_8901743997806544277[4] = dt*state[13] + state[4];
   out_8901743997806544277[5] = dt*state[14] + state[5];
   out_8901743997806544277[6] = state[6];
   out_8901743997806544277[7] = state[7];
   out_8901743997806544277[8] = state[8];
   out_8901743997806544277[9] = state[9];
   out_8901743997806544277[10] = state[10];
   out_8901743997806544277[11] = state[11];
   out_8901743997806544277[12] = state[12];
   out_8901743997806544277[13] = state[13];
   out_8901743997806544277[14] = state[14];
   out_8901743997806544277[15] = state[15];
   out_8901743997806544277[16] = state[16];
   out_8901743997806544277[17] = state[17];
}
void F_fun(double *state, double dt, double *out_187766544558398161) {
   out_187766544558398161[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_187766544558398161[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_187766544558398161[2] = 0;
   out_187766544558398161[3] = 0;
   out_187766544558398161[4] = 0;
   out_187766544558398161[5] = 0;
   out_187766544558398161[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_187766544558398161[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_187766544558398161[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_187766544558398161[9] = 0;
   out_187766544558398161[10] = 0;
   out_187766544558398161[11] = 0;
   out_187766544558398161[12] = 0;
   out_187766544558398161[13] = 0;
   out_187766544558398161[14] = 0;
   out_187766544558398161[15] = 0;
   out_187766544558398161[16] = 0;
   out_187766544558398161[17] = 0;
   out_187766544558398161[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_187766544558398161[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_187766544558398161[20] = 0;
   out_187766544558398161[21] = 0;
   out_187766544558398161[22] = 0;
   out_187766544558398161[23] = 0;
   out_187766544558398161[24] = 0;
   out_187766544558398161[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_187766544558398161[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_187766544558398161[27] = 0;
   out_187766544558398161[28] = 0;
   out_187766544558398161[29] = 0;
   out_187766544558398161[30] = 0;
   out_187766544558398161[31] = 0;
   out_187766544558398161[32] = 0;
   out_187766544558398161[33] = 0;
   out_187766544558398161[34] = 0;
   out_187766544558398161[35] = 0;
   out_187766544558398161[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_187766544558398161[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_187766544558398161[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_187766544558398161[39] = 0;
   out_187766544558398161[40] = 0;
   out_187766544558398161[41] = 0;
   out_187766544558398161[42] = 0;
   out_187766544558398161[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_187766544558398161[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_187766544558398161[45] = 0;
   out_187766544558398161[46] = 0;
   out_187766544558398161[47] = 0;
   out_187766544558398161[48] = 0;
   out_187766544558398161[49] = 0;
   out_187766544558398161[50] = 0;
   out_187766544558398161[51] = 0;
   out_187766544558398161[52] = 0;
   out_187766544558398161[53] = 0;
   out_187766544558398161[54] = 0;
   out_187766544558398161[55] = 0;
   out_187766544558398161[56] = 0;
   out_187766544558398161[57] = 1;
   out_187766544558398161[58] = 0;
   out_187766544558398161[59] = 0;
   out_187766544558398161[60] = 0;
   out_187766544558398161[61] = 0;
   out_187766544558398161[62] = 0;
   out_187766544558398161[63] = 0;
   out_187766544558398161[64] = 0;
   out_187766544558398161[65] = 0;
   out_187766544558398161[66] = dt;
   out_187766544558398161[67] = 0;
   out_187766544558398161[68] = 0;
   out_187766544558398161[69] = 0;
   out_187766544558398161[70] = 0;
   out_187766544558398161[71] = 0;
   out_187766544558398161[72] = 0;
   out_187766544558398161[73] = 0;
   out_187766544558398161[74] = 0;
   out_187766544558398161[75] = 0;
   out_187766544558398161[76] = 1;
   out_187766544558398161[77] = 0;
   out_187766544558398161[78] = 0;
   out_187766544558398161[79] = 0;
   out_187766544558398161[80] = 0;
   out_187766544558398161[81] = 0;
   out_187766544558398161[82] = 0;
   out_187766544558398161[83] = 0;
   out_187766544558398161[84] = 0;
   out_187766544558398161[85] = dt;
   out_187766544558398161[86] = 0;
   out_187766544558398161[87] = 0;
   out_187766544558398161[88] = 0;
   out_187766544558398161[89] = 0;
   out_187766544558398161[90] = 0;
   out_187766544558398161[91] = 0;
   out_187766544558398161[92] = 0;
   out_187766544558398161[93] = 0;
   out_187766544558398161[94] = 0;
   out_187766544558398161[95] = 1;
   out_187766544558398161[96] = 0;
   out_187766544558398161[97] = 0;
   out_187766544558398161[98] = 0;
   out_187766544558398161[99] = 0;
   out_187766544558398161[100] = 0;
   out_187766544558398161[101] = 0;
   out_187766544558398161[102] = 0;
   out_187766544558398161[103] = 0;
   out_187766544558398161[104] = dt;
   out_187766544558398161[105] = 0;
   out_187766544558398161[106] = 0;
   out_187766544558398161[107] = 0;
   out_187766544558398161[108] = 0;
   out_187766544558398161[109] = 0;
   out_187766544558398161[110] = 0;
   out_187766544558398161[111] = 0;
   out_187766544558398161[112] = 0;
   out_187766544558398161[113] = 0;
   out_187766544558398161[114] = 1;
   out_187766544558398161[115] = 0;
   out_187766544558398161[116] = 0;
   out_187766544558398161[117] = 0;
   out_187766544558398161[118] = 0;
   out_187766544558398161[119] = 0;
   out_187766544558398161[120] = 0;
   out_187766544558398161[121] = 0;
   out_187766544558398161[122] = 0;
   out_187766544558398161[123] = 0;
   out_187766544558398161[124] = 0;
   out_187766544558398161[125] = 0;
   out_187766544558398161[126] = 0;
   out_187766544558398161[127] = 0;
   out_187766544558398161[128] = 0;
   out_187766544558398161[129] = 0;
   out_187766544558398161[130] = 0;
   out_187766544558398161[131] = 0;
   out_187766544558398161[132] = 0;
   out_187766544558398161[133] = 1;
   out_187766544558398161[134] = 0;
   out_187766544558398161[135] = 0;
   out_187766544558398161[136] = 0;
   out_187766544558398161[137] = 0;
   out_187766544558398161[138] = 0;
   out_187766544558398161[139] = 0;
   out_187766544558398161[140] = 0;
   out_187766544558398161[141] = 0;
   out_187766544558398161[142] = 0;
   out_187766544558398161[143] = 0;
   out_187766544558398161[144] = 0;
   out_187766544558398161[145] = 0;
   out_187766544558398161[146] = 0;
   out_187766544558398161[147] = 0;
   out_187766544558398161[148] = 0;
   out_187766544558398161[149] = 0;
   out_187766544558398161[150] = 0;
   out_187766544558398161[151] = 0;
   out_187766544558398161[152] = 1;
   out_187766544558398161[153] = 0;
   out_187766544558398161[154] = 0;
   out_187766544558398161[155] = 0;
   out_187766544558398161[156] = 0;
   out_187766544558398161[157] = 0;
   out_187766544558398161[158] = 0;
   out_187766544558398161[159] = 0;
   out_187766544558398161[160] = 0;
   out_187766544558398161[161] = 0;
   out_187766544558398161[162] = 0;
   out_187766544558398161[163] = 0;
   out_187766544558398161[164] = 0;
   out_187766544558398161[165] = 0;
   out_187766544558398161[166] = 0;
   out_187766544558398161[167] = 0;
   out_187766544558398161[168] = 0;
   out_187766544558398161[169] = 0;
   out_187766544558398161[170] = 0;
   out_187766544558398161[171] = 1;
   out_187766544558398161[172] = 0;
   out_187766544558398161[173] = 0;
   out_187766544558398161[174] = 0;
   out_187766544558398161[175] = 0;
   out_187766544558398161[176] = 0;
   out_187766544558398161[177] = 0;
   out_187766544558398161[178] = 0;
   out_187766544558398161[179] = 0;
   out_187766544558398161[180] = 0;
   out_187766544558398161[181] = 0;
   out_187766544558398161[182] = 0;
   out_187766544558398161[183] = 0;
   out_187766544558398161[184] = 0;
   out_187766544558398161[185] = 0;
   out_187766544558398161[186] = 0;
   out_187766544558398161[187] = 0;
   out_187766544558398161[188] = 0;
   out_187766544558398161[189] = 0;
   out_187766544558398161[190] = 1;
   out_187766544558398161[191] = 0;
   out_187766544558398161[192] = 0;
   out_187766544558398161[193] = 0;
   out_187766544558398161[194] = 0;
   out_187766544558398161[195] = 0;
   out_187766544558398161[196] = 0;
   out_187766544558398161[197] = 0;
   out_187766544558398161[198] = 0;
   out_187766544558398161[199] = 0;
   out_187766544558398161[200] = 0;
   out_187766544558398161[201] = 0;
   out_187766544558398161[202] = 0;
   out_187766544558398161[203] = 0;
   out_187766544558398161[204] = 0;
   out_187766544558398161[205] = 0;
   out_187766544558398161[206] = 0;
   out_187766544558398161[207] = 0;
   out_187766544558398161[208] = 0;
   out_187766544558398161[209] = 1;
   out_187766544558398161[210] = 0;
   out_187766544558398161[211] = 0;
   out_187766544558398161[212] = 0;
   out_187766544558398161[213] = 0;
   out_187766544558398161[214] = 0;
   out_187766544558398161[215] = 0;
   out_187766544558398161[216] = 0;
   out_187766544558398161[217] = 0;
   out_187766544558398161[218] = 0;
   out_187766544558398161[219] = 0;
   out_187766544558398161[220] = 0;
   out_187766544558398161[221] = 0;
   out_187766544558398161[222] = 0;
   out_187766544558398161[223] = 0;
   out_187766544558398161[224] = 0;
   out_187766544558398161[225] = 0;
   out_187766544558398161[226] = 0;
   out_187766544558398161[227] = 0;
   out_187766544558398161[228] = 1;
   out_187766544558398161[229] = 0;
   out_187766544558398161[230] = 0;
   out_187766544558398161[231] = 0;
   out_187766544558398161[232] = 0;
   out_187766544558398161[233] = 0;
   out_187766544558398161[234] = 0;
   out_187766544558398161[235] = 0;
   out_187766544558398161[236] = 0;
   out_187766544558398161[237] = 0;
   out_187766544558398161[238] = 0;
   out_187766544558398161[239] = 0;
   out_187766544558398161[240] = 0;
   out_187766544558398161[241] = 0;
   out_187766544558398161[242] = 0;
   out_187766544558398161[243] = 0;
   out_187766544558398161[244] = 0;
   out_187766544558398161[245] = 0;
   out_187766544558398161[246] = 0;
   out_187766544558398161[247] = 1;
   out_187766544558398161[248] = 0;
   out_187766544558398161[249] = 0;
   out_187766544558398161[250] = 0;
   out_187766544558398161[251] = 0;
   out_187766544558398161[252] = 0;
   out_187766544558398161[253] = 0;
   out_187766544558398161[254] = 0;
   out_187766544558398161[255] = 0;
   out_187766544558398161[256] = 0;
   out_187766544558398161[257] = 0;
   out_187766544558398161[258] = 0;
   out_187766544558398161[259] = 0;
   out_187766544558398161[260] = 0;
   out_187766544558398161[261] = 0;
   out_187766544558398161[262] = 0;
   out_187766544558398161[263] = 0;
   out_187766544558398161[264] = 0;
   out_187766544558398161[265] = 0;
   out_187766544558398161[266] = 1;
   out_187766544558398161[267] = 0;
   out_187766544558398161[268] = 0;
   out_187766544558398161[269] = 0;
   out_187766544558398161[270] = 0;
   out_187766544558398161[271] = 0;
   out_187766544558398161[272] = 0;
   out_187766544558398161[273] = 0;
   out_187766544558398161[274] = 0;
   out_187766544558398161[275] = 0;
   out_187766544558398161[276] = 0;
   out_187766544558398161[277] = 0;
   out_187766544558398161[278] = 0;
   out_187766544558398161[279] = 0;
   out_187766544558398161[280] = 0;
   out_187766544558398161[281] = 0;
   out_187766544558398161[282] = 0;
   out_187766544558398161[283] = 0;
   out_187766544558398161[284] = 0;
   out_187766544558398161[285] = 1;
   out_187766544558398161[286] = 0;
   out_187766544558398161[287] = 0;
   out_187766544558398161[288] = 0;
   out_187766544558398161[289] = 0;
   out_187766544558398161[290] = 0;
   out_187766544558398161[291] = 0;
   out_187766544558398161[292] = 0;
   out_187766544558398161[293] = 0;
   out_187766544558398161[294] = 0;
   out_187766544558398161[295] = 0;
   out_187766544558398161[296] = 0;
   out_187766544558398161[297] = 0;
   out_187766544558398161[298] = 0;
   out_187766544558398161[299] = 0;
   out_187766544558398161[300] = 0;
   out_187766544558398161[301] = 0;
   out_187766544558398161[302] = 0;
   out_187766544558398161[303] = 0;
   out_187766544558398161[304] = 1;
   out_187766544558398161[305] = 0;
   out_187766544558398161[306] = 0;
   out_187766544558398161[307] = 0;
   out_187766544558398161[308] = 0;
   out_187766544558398161[309] = 0;
   out_187766544558398161[310] = 0;
   out_187766544558398161[311] = 0;
   out_187766544558398161[312] = 0;
   out_187766544558398161[313] = 0;
   out_187766544558398161[314] = 0;
   out_187766544558398161[315] = 0;
   out_187766544558398161[316] = 0;
   out_187766544558398161[317] = 0;
   out_187766544558398161[318] = 0;
   out_187766544558398161[319] = 0;
   out_187766544558398161[320] = 0;
   out_187766544558398161[321] = 0;
   out_187766544558398161[322] = 0;
   out_187766544558398161[323] = 1;
}
void h_4(double *state, double *unused, double *out_8738596878988744694) {
   out_8738596878988744694[0] = state[6] + state[9];
   out_8738596878988744694[1] = state[7] + state[10];
   out_8738596878988744694[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_474008514404795419) {
   out_474008514404795419[0] = 0;
   out_474008514404795419[1] = 0;
   out_474008514404795419[2] = 0;
   out_474008514404795419[3] = 0;
   out_474008514404795419[4] = 0;
   out_474008514404795419[5] = 0;
   out_474008514404795419[6] = 1;
   out_474008514404795419[7] = 0;
   out_474008514404795419[8] = 0;
   out_474008514404795419[9] = 1;
   out_474008514404795419[10] = 0;
   out_474008514404795419[11] = 0;
   out_474008514404795419[12] = 0;
   out_474008514404795419[13] = 0;
   out_474008514404795419[14] = 0;
   out_474008514404795419[15] = 0;
   out_474008514404795419[16] = 0;
   out_474008514404795419[17] = 0;
   out_474008514404795419[18] = 0;
   out_474008514404795419[19] = 0;
   out_474008514404795419[20] = 0;
   out_474008514404795419[21] = 0;
   out_474008514404795419[22] = 0;
   out_474008514404795419[23] = 0;
   out_474008514404795419[24] = 0;
   out_474008514404795419[25] = 1;
   out_474008514404795419[26] = 0;
   out_474008514404795419[27] = 0;
   out_474008514404795419[28] = 1;
   out_474008514404795419[29] = 0;
   out_474008514404795419[30] = 0;
   out_474008514404795419[31] = 0;
   out_474008514404795419[32] = 0;
   out_474008514404795419[33] = 0;
   out_474008514404795419[34] = 0;
   out_474008514404795419[35] = 0;
   out_474008514404795419[36] = 0;
   out_474008514404795419[37] = 0;
   out_474008514404795419[38] = 0;
   out_474008514404795419[39] = 0;
   out_474008514404795419[40] = 0;
   out_474008514404795419[41] = 0;
   out_474008514404795419[42] = 0;
   out_474008514404795419[43] = 0;
   out_474008514404795419[44] = 1;
   out_474008514404795419[45] = 0;
   out_474008514404795419[46] = 0;
   out_474008514404795419[47] = 1;
   out_474008514404795419[48] = 0;
   out_474008514404795419[49] = 0;
   out_474008514404795419[50] = 0;
   out_474008514404795419[51] = 0;
   out_474008514404795419[52] = 0;
   out_474008514404795419[53] = 0;
}
void h_10(double *state, double *unused, double *out_7482317449235390315) {
   out_7482317449235390315[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7482317449235390315[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7482317449235390315[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5152479438196498760) {
   out_5152479438196498760[0] = 0;
   out_5152479438196498760[1] = 9.8100000000000005*cos(state[1]);
   out_5152479438196498760[2] = 0;
   out_5152479438196498760[3] = 0;
   out_5152479438196498760[4] = -state[8];
   out_5152479438196498760[5] = state[7];
   out_5152479438196498760[6] = 0;
   out_5152479438196498760[7] = state[5];
   out_5152479438196498760[8] = -state[4];
   out_5152479438196498760[9] = 0;
   out_5152479438196498760[10] = 0;
   out_5152479438196498760[11] = 0;
   out_5152479438196498760[12] = 1;
   out_5152479438196498760[13] = 0;
   out_5152479438196498760[14] = 0;
   out_5152479438196498760[15] = 1;
   out_5152479438196498760[16] = 0;
   out_5152479438196498760[17] = 0;
   out_5152479438196498760[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5152479438196498760[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5152479438196498760[20] = 0;
   out_5152479438196498760[21] = state[8];
   out_5152479438196498760[22] = 0;
   out_5152479438196498760[23] = -state[6];
   out_5152479438196498760[24] = -state[5];
   out_5152479438196498760[25] = 0;
   out_5152479438196498760[26] = state[3];
   out_5152479438196498760[27] = 0;
   out_5152479438196498760[28] = 0;
   out_5152479438196498760[29] = 0;
   out_5152479438196498760[30] = 0;
   out_5152479438196498760[31] = 1;
   out_5152479438196498760[32] = 0;
   out_5152479438196498760[33] = 0;
   out_5152479438196498760[34] = 1;
   out_5152479438196498760[35] = 0;
   out_5152479438196498760[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5152479438196498760[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5152479438196498760[38] = 0;
   out_5152479438196498760[39] = -state[7];
   out_5152479438196498760[40] = state[6];
   out_5152479438196498760[41] = 0;
   out_5152479438196498760[42] = state[4];
   out_5152479438196498760[43] = -state[3];
   out_5152479438196498760[44] = 0;
   out_5152479438196498760[45] = 0;
   out_5152479438196498760[46] = 0;
   out_5152479438196498760[47] = 0;
   out_5152479438196498760[48] = 0;
   out_5152479438196498760[49] = 0;
   out_5152479438196498760[50] = 1;
   out_5152479438196498760[51] = 0;
   out_5152479438196498760[52] = 0;
   out_5152479438196498760[53] = 1;
}
void h_13(double *state, double *unused, double *out_5771768815104758354) {
   out_5771768815104758354[0] = state[3];
   out_5771768815104758354[1] = state[4];
   out_5771768815104758354[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3686282339737128220) {
   out_3686282339737128220[0] = 0;
   out_3686282339737128220[1] = 0;
   out_3686282339737128220[2] = 0;
   out_3686282339737128220[3] = 1;
   out_3686282339737128220[4] = 0;
   out_3686282339737128220[5] = 0;
   out_3686282339737128220[6] = 0;
   out_3686282339737128220[7] = 0;
   out_3686282339737128220[8] = 0;
   out_3686282339737128220[9] = 0;
   out_3686282339737128220[10] = 0;
   out_3686282339737128220[11] = 0;
   out_3686282339737128220[12] = 0;
   out_3686282339737128220[13] = 0;
   out_3686282339737128220[14] = 0;
   out_3686282339737128220[15] = 0;
   out_3686282339737128220[16] = 0;
   out_3686282339737128220[17] = 0;
   out_3686282339737128220[18] = 0;
   out_3686282339737128220[19] = 0;
   out_3686282339737128220[20] = 0;
   out_3686282339737128220[21] = 0;
   out_3686282339737128220[22] = 1;
   out_3686282339737128220[23] = 0;
   out_3686282339737128220[24] = 0;
   out_3686282339737128220[25] = 0;
   out_3686282339737128220[26] = 0;
   out_3686282339737128220[27] = 0;
   out_3686282339737128220[28] = 0;
   out_3686282339737128220[29] = 0;
   out_3686282339737128220[30] = 0;
   out_3686282339737128220[31] = 0;
   out_3686282339737128220[32] = 0;
   out_3686282339737128220[33] = 0;
   out_3686282339737128220[34] = 0;
   out_3686282339737128220[35] = 0;
   out_3686282339737128220[36] = 0;
   out_3686282339737128220[37] = 0;
   out_3686282339737128220[38] = 0;
   out_3686282339737128220[39] = 0;
   out_3686282339737128220[40] = 0;
   out_3686282339737128220[41] = 1;
   out_3686282339737128220[42] = 0;
   out_3686282339737128220[43] = 0;
   out_3686282339737128220[44] = 0;
   out_3686282339737128220[45] = 0;
   out_3686282339737128220[46] = 0;
   out_3686282339737128220[47] = 0;
   out_3686282339737128220[48] = 0;
   out_3686282339737128220[49] = 0;
   out_3686282339737128220[50] = 0;
   out_3686282339737128220[51] = 0;
   out_3686282339737128220[52] = 0;
   out_3686282339737128220[53] = 0;
}
void h_14(double *state, double *unused, double *out_6649299331559184012) {
   out_6649299331559184012[0] = state[6];
   out_6649299331559184012[1] = state[7];
   out_6649299331559184012[2] = state[8];
}
void H_14(double *state, double *unused, double *out_38891987759911820) {
   out_38891987759911820[0] = 0;
   out_38891987759911820[1] = 0;
   out_38891987759911820[2] = 0;
   out_38891987759911820[3] = 0;
   out_38891987759911820[4] = 0;
   out_38891987759911820[5] = 0;
   out_38891987759911820[6] = 1;
   out_38891987759911820[7] = 0;
   out_38891987759911820[8] = 0;
   out_38891987759911820[9] = 0;
   out_38891987759911820[10] = 0;
   out_38891987759911820[11] = 0;
   out_38891987759911820[12] = 0;
   out_38891987759911820[13] = 0;
   out_38891987759911820[14] = 0;
   out_38891987759911820[15] = 0;
   out_38891987759911820[16] = 0;
   out_38891987759911820[17] = 0;
   out_38891987759911820[18] = 0;
   out_38891987759911820[19] = 0;
   out_38891987759911820[20] = 0;
   out_38891987759911820[21] = 0;
   out_38891987759911820[22] = 0;
   out_38891987759911820[23] = 0;
   out_38891987759911820[24] = 0;
   out_38891987759911820[25] = 1;
   out_38891987759911820[26] = 0;
   out_38891987759911820[27] = 0;
   out_38891987759911820[28] = 0;
   out_38891987759911820[29] = 0;
   out_38891987759911820[30] = 0;
   out_38891987759911820[31] = 0;
   out_38891987759911820[32] = 0;
   out_38891987759911820[33] = 0;
   out_38891987759911820[34] = 0;
   out_38891987759911820[35] = 0;
   out_38891987759911820[36] = 0;
   out_38891987759911820[37] = 0;
   out_38891987759911820[38] = 0;
   out_38891987759911820[39] = 0;
   out_38891987759911820[40] = 0;
   out_38891987759911820[41] = 0;
   out_38891987759911820[42] = 0;
   out_38891987759911820[43] = 0;
   out_38891987759911820[44] = 1;
   out_38891987759911820[45] = 0;
   out_38891987759911820[46] = 0;
   out_38891987759911820[47] = 0;
   out_38891987759911820[48] = 0;
   out_38891987759911820[49] = 0;
   out_38891987759911820[50] = 0;
   out_38891987759911820[51] = 0;
   out_38891987759911820[52] = 0;
   out_38891987759911820[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4883205334769300531) {
  err_fun(nom_x, delta_x, out_4883205334769300531);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2778782879349748614) {
  inv_err_fun(nom_x, true_x, out_2778782879349748614);
}
void pose_H_mod_fun(double *state, double *out_650126789788623456) {
  H_mod_fun(state, out_650126789788623456);
}
void pose_f_fun(double *state, double dt, double *out_8901743997806544277) {
  f_fun(state,  dt, out_8901743997806544277);
}
void pose_F_fun(double *state, double dt, double *out_187766544558398161) {
  F_fun(state,  dt, out_187766544558398161);
}
void pose_h_4(double *state, double *unused, double *out_8738596878988744694) {
  h_4(state, unused, out_8738596878988744694);
}
void pose_H_4(double *state, double *unused, double *out_474008514404795419) {
  H_4(state, unused, out_474008514404795419);
}
void pose_h_10(double *state, double *unused, double *out_7482317449235390315) {
  h_10(state, unused, out_7482317449235390315);
}
void pose_H_10(double *state, double *unused, double *out_5152479438196498760) {
  H_10(state, unused, out_5152479438196498760);
}
void pose_h_13(double *state, double *unused, double *out_5771768815104758354) {
  h_13(state, unused, out_5771768815104758354);
}
void pose_H_13(double *state, double *unused, double *out_3686282339737128220) {
  H_13(state, unused, out_3686282339737128220);
}
void pose_h_14(double *state, double *unused, double *out_6649299331559184012) {
  h_14(state, unused, out_6649299331559184012);
}
void pose_H_14(double *state, double *unused, double *out_38891987759911820) {
  H_14(state, unused, out_38891987759911820);
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
