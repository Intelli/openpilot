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
void err_fun(double *nom_x, double *delta_x, double *out_5999999625262296722) {
   out_5999999625262296722[0] = delta_x[0] + nom_x[0];
   out_5999999625262296722[1] = delta_x[1] + nom_x[1];
   out_5999999625262296722[2] = delta_x[2] + nom_x[2];
   out_5999999625262296722[3] = delta_x[3] + nom_x[3];
   out_5999999625262296722[4] = delta_x[4] + nom_x[4];
   out_5999999625262296722[5] = delta_x[5] + nom_x[5];
   out_5999999625262296722[6] = delta_x[6] + nom_x[6];
   out_5999999625262296722[7] = delta_x[7] + nom_x[7];
   out_5999999625262296722[8] = delta_x[8] + nom_x[8];
   out_5999999625262296722[9] = delta_x[9] + nom_x[9];
   out_5999999625262296722[10] = delta_x[10] + nom_x[10];
   out_5999999625262296722[11] = delta_x[11] + nom_x[11];
   out_5999999625262296722[12] = delta_x[12] + nom_x[12];
   out_5999999625262296722[13] = delta_x[13] + nom_x[13];
   out_5999999625262296722[14] = delta_x[14] + nom_x[14];
   out_5999999625262296722[15] = delta_x[15] + nom_x[15];
   out_5999999625262296722[16] = delta_x[16] + nom_x[16];
   out_5999999625262296722[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_608932248278116384) {
   out_608932248278116384[0] = -nom_x[0] + true_x[0];
   out_608932248278116384[1] = -nom_x[1] + true_x[1];
   out_608932248278116384[2] = -nom_x[2] + true_x[2];
   out_608932248278116384[3] = -nom_x[3] + true_x[3];
   out_608932248278116384[4] = -nom_x[4] + true_x[4];
   out_608932248278116384[5] = -nom_x[5] + true_x[5];
   out_608932248278116384[6] = -nom_x[6] + true_x[6];
   out_608932248278116384[7] = -nom_x[7] + true_x[7];
   out_608932248278116384[8] = -nom_x[8] + true_x[8];
   out_608932248278116384[9] = -nom_x[9] + true_x[9];
   out_608932248278116384[10] = -nom_x[10] + true_x[10];
   out_608932248278116384[11] = -nom_x[11] + true_x[11];
   out_608932248278116384[12] = -nom_x[12] + true_x[12];
   out_608932248278116384[13] = -nom_x[13] + true_x[13];
   out_608932248278116384[14] = -nom_x[14] + true_x[14];
   out_608932248278116384[15] = -nom_x[15] + true_x[15];
   out_608932248278116384[16] = -nom_x[16] + true_x[16];
   out_608932248278116384[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5835985313550633106) {
   out_5835985313550633106[0] = 1.0;
   out_5835985313550633106[1] = 0.0;
   out_5835985313550633106[2] = 0.0;
   out_5835985313550633106[3] = 0.0;
   out_5835985313550633106[4] = 0.0;
   out_5835985313550633106[5] = 0.0;
   out_5835985313550633106[6] = 0.0;
   out_5835985313550633106[7] = 0.0;
   out_5835985313550633106[8] = 0.0;
   out_5835985313550633106[9] = 0.0;
   out_5835985313550633106[10] = 0.0;
   out_5835985313550633106[11] = 0.0;
   out_5835985313550633106[12] = 0.0;
   out_5835985313550633106[13] = 0.0;
   out_5835985313550633106[14] = 0.0;
   out_5835985313550633106[15] = 0.0;
   out_5835985313550633106[16] = 0.0;
   out_5835985313550633106[17] = 0.0;
   out_5835985313550633106[18] = 0.0;
   out_5835985313550633106[19] = 1.0;
   out_5835985313550633106[20] = 0.0;
   out_5835985313550633106[21] = 0.0;
   out_5835985313550633106[22] = 0.0;
   out_5835985313550633106[23] = 0.0;
   out_5835985313550633106[24] = 0.0;
   out_5835985313550633106[25] = 0.0;
   out_5835985313550633106[26] = 0.0;
   out_5835985313550633106[27] = 0.0;
   out_5835985313550633106[28] = 0.0;
   out_5835985313550633106[29] = 0.0;
   out_5835985313550633106[30] = 0.0;
   out_5835985313550633106[31] = 0.0;
   out_5835985313550633106[32] = 0.0;
   out_5835985313550633106[33] = 0.0;
   out_5835985313550633106[34] = 0.0;
   out_5835985313550633106[35] = 0.0;
   out_5835985313550633106[36] = 0.0;
   out_5835985313550633106[37] = 0.0;
   out_5835985313550633106[38] = 1.0;
   out_5835985313550633106[39] = 0.0;
   out_5835985313550633106[40] = 0.0;
   out_5835985313550633106[41] = 0.0;
   out_5835985313550633106[42] = 0.0;
   out_5835985313550633106[43] = 0.0;
   out_5835985313550633106[44] = 0.0;
   out_5835985313550633106[45] = 0.0;
   out_5835985313550633106[46] = 0.0;
   out_5835985313550633106[47] = 0.0;
   out_5835985313550633106[48] = 0.0;
   out_5835985313550633106[49] = 0.0;
   out_5835985313550633106[50] = 0.0;
   out_5835985313550633106[51] = 0.0;
   out_5835985313550633106[52] = 0.0;
   out_5835985313550633106[53] = 0.0;
   out_5835985313550633106[54] = 0.0;
   out_5835985313550633106[55] = 0.0;
   out_5835985313550633106[56] = 0.0;
   out_5835985313550633106[57] = 1.0;
   out_5835985313550633106[58] = 0.0;
   out_5835985313550633106[59] = 0.0;
   out_5835985313550633106[60] = 0.0;
   out_5835985313550633106[61] = 0.0;
   out_5835985313550633106[62] = 0.0;
   out_5835985313550633106[63] = 0.0;
   out_5835985313550633106[64] = 0.0;
   out_5835985313550633106[65] = 0.0;
   out_5835985313550633106[66] = 0.0;
   out_5835985313550633106[67] = 0.0;
   out_5835985313550633106[68] = 0.0;
   out_5835985313550633106[69] = 0.0;
   out_5835985313550633106[70] = 0.0;
   out_5835985313550633106[71] = 0.0;
   out_5835985313550633106[72] = 0.0;
   out_5835985313550633106[73] = 0.0;
   out_5835985313550633106[74] = 0.0;
   out_5835985313550633106[75] = 0.0;
   out_5835985313550633106[76] = 1.0;
   out_5835985313550633106[77] = 0.0;
   out_5835985313550633106[78] = 0.0;
   out_5835985313550633106[79] = 0.0;
   out_5835985313550633106[80] = 0.0;
   out_5835985313550633106[81] = 0.0;
   out_5835985313550633106[82] = 0.0;
   out_5835985313550633106[83] = 0.0;
   out_5835985313550633106[84] = 0.0;
   out_5835985313550633106[85] = 0.0;
   out_5835985313550633106[86] = 0.0;
   out_5835985313550633106[87] = 0.0;
   out_5835985313550633106[88] = 0.0;
   out_5835985313550633106[89] = 0.0;
   out_5835985313550633106[90] = 0.0;
   out_5835985313550633106[91] = 0.0;
   out_5835985313550633106[92] = 0.0;
   out_5835985313550633106[93] = 0.0;
   out_5835985313550633106[94] = 0.0;
   out_5835985313550633106[95] = 1.0;
   out_5835985313550633106[96] = 0.0;
   out_5835985313550633106[97] = 0.0;
   out_5835985313550633106[98] = 0.0;
   out_5835985313550633106[99] = 0.0;
   out_5835985313550633106[100] = 0.0;
   out_5835985313550633106[101] = 0.0;
   out_5835985313550633106[102] = 0.0;
   out_5835985313550633106[103] = 0.0;
   out_5835985313550633106[104] = 0.0;
   out_5835985313550633106[105] = 0.0;
   out_5835985313550633106[106] = 0.0;
   out_5835985313550633106[107] = 0.0;
   out_5835985313550633106[108] = 0.0;
   out_5835985313550633106[109] = 0.0;
   out_5835985313550633106[110] = 0.0;
   out_5835985313550633106[111] = 0.0;
   out_5835985313550633106[112] = 0.0;
   out_5835985313550633106[113] = 0.0;
   out_5835985313550633106[114] = 1.0;
   out_5835985313550633106[115] = 0.0;
   out_5835985313550633106[116] = 0.0;
   out_5835985313550633106[117] = 0.0;
   out_5835985313550633106[118] = 0.0;
   out_5835985313550633106[119] = 0.0;
   out_5835985313550633106[120] = 0.0;
   out_5835985313550633106[121] = 0.0;
   out_5835985313550633106[122] = 0.0;
   out_5835985313550633106[123] = 0.0;
   out_5835985313550633106[124] = 0.0;
   out_5835985313550633106[125] = 0.0;
   out_5835985313550633106[126] = 0.0;
   out_5835985313550633106[127] = 0.0;
   out_5835985313550633106[128] = 0.0;
   out_5835985313550633106[129] = 0.0;
   out_5835985313550633106[130] = 0.0;
   out_5835985313550633106[131] = 0.0;
   out_5835985313550633106[132] = 0.0;
   out_5835985313550633106[133] = 1.0;
   out_5835985313550633106[134] = 0.0;
   out_5835985313550633106[135] = 0.0;
   out_5835985313550633106[136] = 0.0;
   out_5835985313550633106[137] = 0.0;
   out_5835985313550633106[138] = 0.0;
   out_5835985313550633106[139] = 0.0;
   out_5835985313550633106[140] = 0.0;
   out_5835985313550633106[141] = 0.0;
   out_5835985313550633106[142] = 0.0;
   out_5835985313550633106[143] = 0.0;
   out_5835985313550633106[144] = 0.0;
   out_5835985313550633106[145] = 0.0;
   out_5835985313550633106[146] = 0.0;
   out_5835985313550633106[147] = 0.0;
   out_5835985313550633106[148] = 0.0;
   out_5835985313550633106[149] = 0.0;
   out_5835985313550633106[150] = 0.0;
   out_5835985313550633106[151] = 0.0;
   out_5835985313550633106[152] = 1.0;
   out_5835985313550633106[153] = 0.0;
   out_5835985313550633106[154] = 0.0;
   out_5835985313550633106[155] = 0.0;
   out_5835985313550633106[156] = 0.0;
   out_5835985313550633106[157] = 0.0;
   out_5835985313550633106[158] = 0.0;
   out_5835985313550633106[159] = 0.0;
   out_5835985313550633106[160] = 0.0;
   out_5835985313550633106[161] = 0.0;
   out_5835985313550633106[162] = 0.0;
   out_5835985313550633106[163] = 0.0;
   out_5835985313550633106[164] = 0.0;
   out_5835985313550633106[165] = 0.0;
   out_5835985313550633106[166] = 0.0;
   out_5835985313550633106[167] = 0.0;
   out_5835985313550633106[168] = 0.0;
   out_5835985313550633106[169] = 0.0;
   out_5835985313550633106[170] = 0.0;
   out_5835985313550633106[171] = 1.0;
   out_5835985313550633106[172] = 0.0;
   out_5835985313550633106[173] = 0.0;
   out_5835985313550633106[174] = 0.0;
   out_5835985313550633106[175] = 0.0;
   out_5835985313550633106[176] = 0.0;
   out_5835985313550633106[177] = 0.0;
   out_5835985313550633106[178] = 0.0;
   out_5835985313550633106[179] = 0.0;
   out_5835985313550633106[180] = 0.0;
   out_5835985313550633106[181] = 0.0;
   out_5835985313550633106[182] = 0.0;
   out_5835985313550633106[183] = 0.0;
   out_5835985313550633106[184] = 0.0;
   out_5835985313550633106[185] = 0.0;
   out_5835985313550633106[186] = 0.0;
   out_5835985313550633106[187] = 0.0;
   out_5835985313550633106[188] = 0.0;
   out_5835985313550633106[189] = 0.0;
   out_5835985313550633106[190] = 1.0;
   out_5835985313550633106[191] = 0.0;
   out_5835985313550633106[192] = 0.0;
   out_5835985313550633106[193] = 0.0;
   out_5835985313550633106[194] = 0.0;
   out_5835985313550633106[195] = 0.0;
   out_5835985313550633106[196] = 0.0;
   out_5835985313550633106[197] = 0.0;
   out_5835985313550633106[198] = 0.0;
   out_5835985313550633106[199] = 0.0;
   out_5835985313550633106[200] = 0.0;
   out_5835985313550633106[201] = 0.0;
   out_5835985313550633106[202] = 0.0;
   out_5835985313550633106[203] = 0.0;
   out_5835985313550633106[204] = 0.0;
   out_5835985313550633106[205] = 0.0;
   out_5835985313550633106[206] = 0.0;
   out_5835985313550633106[207] = 0.0;
   out_5835985313550633106[208] = 0.0;
   out_5835985313550633106[209] = 1.0;
   out_5835985313550633106[210] = 0.0;
   out_5835985313550633106[211] = 0.0;
   out_5835985313550633106[212] = 0.0;
   out_5835985313550633106[213] = 0.0;
   out_5835985313550633106[214] = 0.0;
   out_5835985313550633106[215] = 0.0;
   out_5835985313550633106[216] = 0.0;
   out_5835985313550633106[217] = 0.0;
   out_5835985313550633106[218] = 0.0;
   out_5835985313550633106[219] = 0.0;
   out_5835985313550633106[220] = 0.0;
   out_5835985313550633106[221] = 0.0;
   out_5835985313550633106[222] = 0.0;
   out_5835985313550633106[223] = 0.0;
   out_5835985313550633106[224] = 0.0;
   out_5835985313550633106[225] = 0.0;
   out_5835985313550633106[226] = 0.0;
   out_5835985313550633106[227] = 0.0;
   out_5835985313550633106[228] = 1.0;
   out_5835985313550633106[229] = 0.0;
   out_5835985313550633106[230] = 0.0;
   out_5835985313550633106[231] = 0.0;
   out_5835985313550633106[232] = 0.0;
   out_5835985313550633106[233] = 0.0;
   out_5835985313550633106[234] = 0.0;
   out_5835985313550633106[235] = 0.0;
   out_5835985313550633106[236] = 0.0;
   out_5835985313550633106[237] = 0.0;
   out_5835985313550633106[238] = 0.0;
   out_5835985313550633106[239] = 0.0;
   out_5835985313550633106[240] = 0.0;
   out_5835985313550633106[241] = 0.0;
   out_5835985313550633106[242] = 0.0;
   out_5835985313550633106[243] = 0.0;
   out_5835985313550633106[244] = 0.0;
   out_5835985313550633106[245] = 0.0;
   out_5835985313550633106[246] = 0.0;
   out_5835985313550633106[247] = 1.0;
   out_5835985313550633106[248] = 0.0;
   out_5835985313550633106[249] = 0.0;
   out_5835985313550633106[250] = 0.0;
   out_5835985313550633106[251] = 0.0;
   out_5835985313550633106[252] = 0.0;
   out_5835985313550633106[253] = 0.0;
   out_5835985313550633106[254] = 0.0;
   out_5835985313550633106[255] = 0.0;
   out_5835985313550633106[256] = 0.0;
   out_5835985313550633106[257] = 0.0;
   out_5835985313550633106[258] = 0.0;
   out_5835985313550633106[259] = 0.0;
   out_5835985313550633106[260] = 0.0;
   out_5835985313550633106[261] = 0.0;
   out_5835985313550633106[262] = 0.0;
   out_5835985313550633106[263] = 0.0;
   out_5835985313550633106[264] = 0.0;
   out_5835985313550633106[265] = 0.0;
   out_5835985313550633106[266] = 1.0;
   out_5835985313550633106[267] = 0.0;
   out_5835985313550633106[268] = 0.0;
   out_5835985313550633106[269] = 0.0;
   out_5835985313550633106[270] = 0.0;
   out_5835985313550633106[271] = 0.0;
   out_5835985313550633106[272] = 0.0;
   out_5835985313550633106[273] = 0.0;
   out_5835985313550633106[274] = 0.0;
   out_5835985313550633106[275] = 0.0;
   out_5835985313550633106[276] = 0.0;
   out_5835985313550633106[277] = 0.0;
   out_5835985313550633106[278] = 0.0;
   out_5835985313550633106[279] = 0.0;
   out_5835985313550633106[280] = 0.0;
   out_5835985313550633106[281] = 0.0;
   out_5835985313550633106[282] = 0.0;
   out_5835985313550633106[283] = 0.0;
   out_5835985313550633106[284] = 0.0;
   out_5835985313550633106[285] = 1.0;
   out_5835985313550633106[286] = 0.0;
   out_5835985313550633106[287] = 0.0;
   out_5835985313550633106[288] = 0.0;
   out_5835985313550633106[289] = 0.0;
   out_5835985313550633106[290] = 0.0;
   out_5835985313550633106[291] = 0.0;
   out_5835985313550633106[292] = 0.0;
   out_5835985313550633106[293] = 0.0;
   out_5835985313550633106[294] = 0.0;
   out_5835985313550633106[295] = 0.0;
   out_5835985313550633106[296] = 0.0;
   out_5835985313550633106[297] = 0.0;
   out_5835985313550633106[298] = 0.0;
   out_5835985313550633106[299] = 0.0;
   out_5835985313550633106[300] = 0.0;
   out_5835985313550633106[301] = 0.0;
   out_5835985313550633106[302] = 0.0;
   out_5835985313550633106[303] = 0.0;
   out_5835985313550633106[304] = 1.0;
   out_5835985313550633106[305] = 0.0;
   out_5835985313550633106[306] = 0.0;
   out_5835985313550633106[307] = 0.0;
   out_5835985313550633106[308] = 0.0;
   out_5835985313550633106[309] = 0.0;
   out_5835985313550633106[310] = 0.0;
   out_5835985313550633106[311] = 0.0;
   out_5835985313550633106[312] = 0.0;
   out_5835985313550633106[313] = 0.0;
   out_5835985313550633106[314] = 0.0;
   out_5835985313550633106[315] = 0.0;
   out_5835985313550633106[316] = 0.0;
   out_5835985313550633106[317] = 0.0;
   out_5835985313550633106[318] = 0.0;
   out_5835985313550633106[319] = 0.0;
   out_5835985313550633106[320] = 0.0;
   out_5835985313550633106[321] = 0.0;
   out_5835985313550633106[322] = 0.0;
   out_5835985313550633106[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5863158505292019107) {
   out_5863158505292019107[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5863158505292019107[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5863158505292019107[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5863158505292019107[3] = dt*state[12] + state[3];
   out_5863158505292019107[4] = dt*state[13] + state[4];
   out_5863158505292019107[5] = dt*state[14] + state[5];
   out_5863158505292019107[6] = state[6];
   out_5863158505292019107[7] = state[7];
   out_5863158505292019107[8] = state[8];
   out_5863158505292019107[9] = state[9];
   out_5863158505292019107[10] = state[10];
   out_5863158505292019107[11] = state[11];
   out_5863158505292019107[12] = state[12];
   out_5863158505292019107[13] = state[13];
   out_5863158505292019107[14] = state[14];
   out_5863158505292019107[15] = state[15];
   out_5863158505292019107[16] = state[16];
   out_5863158505292019107[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1611471319636251524) {
   out_1611471319636251524[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1611471319636251524[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1611471319636251524[2] = 0;
   out_1611471319636251524[3] = 0;
   out_1611471319636251524[4] = 0;
   out_1611471319636251524[5] = 0;
   out_1611471319636251524[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1611471319636251524[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1611471319636251524[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1611471319636251524[9] = 0;
   out_1611471319636251524[10] = 0;
   out_1611471319636251524[11] = 0;
   out_1611471319636251524[12] = 0;
   out_1611471319636251524[13] = 0;
   out_1611471319636251524[14] = 0;
   out_1611471319636251524[15] = 0;
   out_1611471319636251524[16] = 0;
   out_1611471319636251524[17] = 0;
   out_1611471319636251524[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1611471319636251524[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1611471319636251524[20] = 0;
   out_1611471319636251524[21] = 0;
   out_1611471319636251524[22] = 0;
   out_1611471319636251524[23] = 0;
   out_1611471319636251524[24] = 0;
   out_1611471319636251524[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1611471319636251524[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1611471319636251524[27] = 0;
   out_1611471319636251524[28] = 0;
   out_1611471319636251524[29] = 0;
   out_1611471319636251524[30] = 0;
   out_1611471319636251524[31] = 0;
   out_1611471319636251524[32] = 0;
   out_1611471319636251524[33] = 0;
   out_1611471319636251524[34] = 0;
   out_1611471319636251524[35] = 0;
   out_1611471319636251524[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1611471319636251524[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1611471319636251524[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1611471319636251524[39] = 0;
   out_1611471319636251524[40] = 0;
   out_1611471319636251524[41] = 0;
   out_1611471319636251524[42] = 0;
   out_1611471319636251524[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1611471319636251524[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1611471319636251524[45] = 0;
   out_1611471319636251524[46] = 0;
   out_1611471319636251524[47] = 0;
   out_1611471319636251524[48] = 0;
   out_1611471319636251524[49] = 0;
   out_1611471319636251524[50] = 0;
   out_1611471319636251524[51] = 0;
   out_1611471319636251524[52] = 0;
   out_1611471319636251524[53] = 0;
   out_1611471319636251524[54] = 0;
   out_1611471319636251524[55] = 0;
   out_1611471319636251524[56] = 0;
   out_1611471319636251524[57] = 1;
   out_1611471319636251524[58] = 0;
   out_1611471319636251524[59] = 0;
   out_1611471319636251524[60] = 0;
   out_1611471319636251524[61] = 0;
   out_1611471319636251524[62] = 0;
   out_1611471319636251524[63] = 0;
   out_1611471319636251524[64] = 0;
   out_1611471319636251524[65] = 0;
   out_1611471319636251524[66] = dt;
   out_1611471319636251524[67] = 0;
   out_1611471319636251524[68] = 0;
   out_1611471319636251524[69] = 0;
   out_1611471319636251524[70] = 0;
   out_1611471319636251524[71] = 0;
   out_1611471319636251524[72] = 0;
   out_1611471319636251524[73] = 0;
   out_1611471319636251524[74] = 0;
   out_1611471319636251524[75] = 0;
   out_1611471319636251524[76] = 1;
   out_1611471319636251524[77] = 0;
   out_1611471319636251524[78] = 0;
   out_1611471319636251524[79] = 0;
   out_1611471319636251524[80] = 0;
   out_1611471319636251524[81] = 0;
   out_1611471319636251524[82] = 0;
   out_1611471319636251524[83] = 0;
   out_1611471319636251524[84] = 0;
   out_1611471319636251524[85] = dt;
   out_1611471319636251524[86] = 0;
   out_1611471319636251524[87] = 0;
   out_1611471319636251524[88] = 0;
   out_1611471319636251524[89] = 0;
   out_1611471319636251524[90] = 0;
   out_1611471319636251524[91] = 0;
   out_1611471319636251524[92] = 0;
   out_1611471319636251524[93] = 0;
   out_1611471319636251524[94] = 0;
   out_1611471319636251524[95] = 1;
   out_1611471319636251524[96] = 0;
   out_1611471319636251524[97] = 0;
   out_1611471319636251524[98] = 0;
   out_1611471319636251524[99] = 0;
   out_1611471319636251524[100] = 0;
   out_1611471319636251524[101] = 0;
   out_1611471319636251524[102] = 0;
   out_1611471319636251524[103] = 0;
   out_1611471319636251524[104] = dt;
   out_1611471319636251524[105] = 0;
   out_1611471319636251524[106] = 0;
   out_1611471319636251524[107] = 0;
   out_1611471319636251524[108] = 0;
   out_1611471319636251524[109] = 0;
   out_1611471319636251524[110] = 0;
   out_1611471319636251524[111] = 0;
   out_1611471319636251524[112] = 0;
   out_1611471319636251524[113] = 0;
   out_1611471319636251524[114] = 1;
   out_1611471319636251524[115] = 0;
   out_1611471319636251524[116] = 0;
   out_1611471319636251524[117] = 0;
   out_1611471319636251524[118] = 0;
   out_1611471319636251524[119] = 0;
   out_1611471319636251524[120] = 0;
   out_1611471319636251524[121] = 0;
   out_1611471319636251524[122] = 0;
   out_1611471319636251524[123] = 0;
   out_1611471319636251524[124] = 0;
   out_1611471319636251524[125] = 0;
   out_1611471319636251524[126] = 0;
   out_1611471319636251524[127] = 0;
   out_1611471319636251524[128] = 0;
   out_1611471319636251524[129] = 0;
   out_1611471319636251524[130] = 0;
   out_1611471319636251524[131] = 0;
   out_1611471319636251524[132] = 0;
   out_1611471319636251524[133] = 1;
   out_1611471319636251524[134] = 0;
   out_1611471319636251524[135] = 0;
   out_1611471319636251524[136] = 0;
   out_1611471319636251524[137] = 0;
   out_1611471319636251524[138] = 0;
   out_1611471319636251524[139] = 0;
   out_1611471319636251524[140] = 0;
   out_1611471319636251524[141] = 0;
   out_1611471319636251524[142] = 0;
   out_1611471319636251524[143] = 0;
   out_1611471319636251524[144] = 0;
   out_1611471319636251524[145] = 0;
   out_1611471319636251524[146] = 0;
   out_1611471319636251524[147] = 0;
   out_1611471319636251524[148] = 0;
   out_1611471319636251524[149] = 0;
   out_1611471319636251524[150] = 0;
   out_1611471319636251524[151] = 0;
   out_1611471319636251524[152] = 1;
   out_1611471319636251524[153] = 0;
   out_1611471319636251524[154] = 0;
   out_1611471319636251524[155] = 0;
   out_1611471319636251524[156] = 0;
   out_1611471319636251524[157] = 0;
   out_1611471319636251524[158] = 0;
   out_1611471319636251524[159] = 0;
   out_1611471319636251524[160] = 0;
   out_1611471319636251524[161] = 0;
   out_1611471319636251524[162] = 0;
   out_1611471319636251524[163] = 0;
   out_1611471319636251524[164] = 0;
   out_1611471319636251524[165] = 0;
   out_1611471319636251524[166] = 0;
   out_1611471319636251524[167] = 0;
   out_1611471319636251524[168] = 0;
   out_1611471319636251524[169] = 0;
   out_1611471319636251524[170] = 0;
   out_1611471319636251524[171] = 1;
   out_1611471319636251524[172] = 0;
   out_1611471319636251524[173] = 0;
   out_1611471319636251524[174] = 0;
   out_1611471319636251524[175] = 0;
   out_1611471319636251524[176] = 0;
   out_1611471319636251524[177] = 0;
   out_1611471319636251524[178] = 0;
   out_1611471319636251524[179] = 0;
   out_1611471319636251524[180] = 0;
   out_1611471319636251524[181] = 0;
   out_1611471319636251524[182] = 0;
   out_1611471319636251524[183] = 0;
   out_1611471319636251524[184] = 0;
   out_1611471319636251524[185] = 0;
   out_1611471319636251524[186] = 0;
   out_1611471319636251524[187] = 0;
   out_1611471319636251524[188] = 0;
   out_1611471319636251524[189] = 0;
   out_1611471319636251524[190] = 1;
   out_1611471319636251524[191] = 0;
   out_1611471319636251524[192] = 0;
   out_1611471319636251524[193] = 0;
   out_1611471319636251524[194] = 0;
   out_1611471319636251524[195] = 0;
   out_1611471319636251524[196] = 0;
   out_1611471319636251524[197] = 0;
   out_1611471319636251524[198] = 0;
   out_1611471319636251524[199] = 0;
   out_1611471319636251524[200] = 0;
   out_1611471319636251524[201] = 0;
   out_1611471319636251524[202] = 0;
   out_1611471319636251524[203] = 0;
   out_1611471319636251524[204] = 0;
   out_1611471319636251524[205] = 0;
   out_1611471319636251524[206] = 0;
   out_1611471319636251524[207] = 0;
   out_1611471319636251524[208] = 0;
   out_1611471319636251524[209] = 1;
   out_1611471319636251524[210] = 0;
   out_1611471319636251524[211] = 0;
   out_1611471319636251524[212] = 0;
   out_1611471319636251524[213] = 0;
   out_1611471319636251524[214] = 0;
   out_1611471319636251524[215] = 0;
   out_1611471319636251524[216] = 0;
   out_1611471319636251524[217] = 0;
   out_1611471319636251524[218] = 0;
   out_1611471319636251524[219] = 0;
   out_1611471319636251524[220] = 0;
   out_1611471319636251524[221] = 0;
   out_1611471319636251524[222] = 0;
   out_1611471319636251524[223] = 0;
   out_1611471319636251524[224] = 0;
   out_1611471319636251524[225] = 0;
   out_1611471319636251524[226] = 0;
   out_1611471319636251524[227] = 0;
   out_1611471319636251524[228] = 1;
   out_1611471319636251524[229] = 0;
   out_1611471319636251524[230] = 0;
   out_1611471319636251524[231] = 0;
   out_1611471319636251524[232] = 0;
   out_1611471319636251524[233] = 0;
   out_1611471319636251524[234] = 0;
   out_1611471319636251524[235] = 0;
   out_1611471319636251524[236] = 0;
   out_1611471319636251524[237] = 0;
   out_1611471319636251524[238] = 0;
   out_1611471319636251524[239] = 0;
   out_1611471319636251524[240] = 0;
   out_1611471319636251524[241] = 0;
   out_1611471319636251524[242] = 0;
   out_1611471319636251524[243] = 0;
   out_1611471319636251524[244] = 0;
   out_1611471319636251524[245] = 0;
   out_1611471319636251524[246] = 0;
   out_1611471319636251524[247] = 1;
   out_1611471319636251524[248] = 0;
   out_1611471319636251524[249] = 0;
   out_1611471319636251524[250] = 0;
   out_1611471319636251524[251] = 0;
   out_1611471319636251524[252] = 0;
   out_1611471319636251524[253] = 0;
   out_1611471319636251524[254] = 0;
   out_1611471319636251524[255] = 0;
   out_1611471319636251524[256] = 0;
   out_1611471319636251524[257] = 0;
   out_1611471319636251524[258] = 0;
   out_1611471319636251524[259] = 0;
   out_1611471319636251524[260] = 0;
   out_1611471319636251524[261] = 0;
   out_1611471319636251524[262] = 0;
   out_1611471319636251524[263] = 0;
   out_1611471319636251524[264] = 0;
   out_1611471319636251524[265] = 0;
   out_1611471319636251524[266] = 1;
   out_1611471319636251524[267] = 0;
   out_1611471319636251524[268] = 0;
   out_1611471319636251524[269] = 0;
   out_1611471319636251524[270] = 0;
   out_1611471319636251524[271] = 0;
   out_1611471319636251524[272] = 0;
   out_1611471319636251524[273] = 0;
   out_1611471319636251524[274] = 0;
   out_1611471319636251524[275] = 0;
   out_1611471319636251524[276] = 0;
   out_1611471319636251524[277] = 0;
   out_1611471319636251524[278] = 0;
   out_1611471319636251524[279] = 0;
   out_1611471319636251524[280] = 0;
   out_1611471319636251524[281] = 0;
   out_1611471319636251524[282] = 0;
   out_1611471319636251524[283] = 0;
   out_1611471319636251524[284] = 0;
   out_1611471319636251524[285] = 1;
   out_1611471319636251524[286] = 0;
   out_1611471319636251524[287] = 0;
   out_1611471319636251524[288] = 0;
   out_1611471319636251524[289] = 0;
   out_1611471319636251524[290] = 0;
   out_1611471319636251524[291] = 0;
   out_1611471319636251524[292] = 0;
   out_1611471319636251524[293] = 0;
   out_1611471319636251524[294] = 0;
   out_1611471319636251524[295] = 0;
   out_1611471319636251524[296] = 0;
   out_1611471319636251524[297] = 0;
   out_1611471319636251524[298] = 0;
   out_1611471319636251524[299] = 0;
   out_1611471319636251524[300] = 0;
   out_1611471319636251524[301] = 0;
   out_1611471319636251524[302] = 0;
   out_1611471319636251524[303] = 0;
   out_1611471319636251524[304] = 1;
   out_1611471319636251524[305] = 0;
   out_1611471319636251524[306] = 0;
   out_1611471319636251524[307] = 0;
   out_1611471319636251524[308] = 0;
   out_1611471319636251524[309] = 0;
   out_1611471319636251524[310] = 0;
   out_1611471319636251524[311] = 0;
   out_1611471319636251524[312] = 0;
   out_1611471319636251524[313] = 0;
   out_1611471319636251524[314] = 0;
   out_1611471319636251524[315] = 0;
   out_1611471319636251524[316] = 0;
   out_1611471319636251524[317] = 0;
   out_1611471319636251524[318] = 0;
   out_1611471319636251524[319] = 0;
   out_1611471319636251524[320] = 0;
   out_1611471319636251524[321] = 0;
   out_1611471319636251524[322] = 0;
   out_1611471319636251524[323] = 1;
}
void h_4(double *state, double *unused, double *out_1124236774130910347) {
   out_1124236774130910347[0] = state[6] + state[9];
   out_1124236774130910347[1] = state[7] + state[10];
   out_1124236774130910347[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2064178103706725534) {
   out_2064178103706725534[0] = 0;
   out_2064178103706725534[1] = 0;
   out_2064178103706725534[2] = 0;
   out_2064178103706725534[3] = 0;
   out_2064178103706725534[4] = 0;
   out_2064178103706725534[5] = 0;
   out_2064178103706725534[6] = 1;
   out_2064178103706725534[7] = 0;
   out_2064178103706725534[8] = 0;
   out_2064178103706725534[9] = 1;
   out_2064178103706725534[10] = 0;
   out_2064178103706725534[11] = 0;
   out_2064178103706725534[12] = 0;
   out_2064178103706725534[13] = 0;
   out_2064178103706725534[14] = 0;
   out_2064178103706725534[15] = 0;
   out_2064178103706725534[16] = 0;
   out_2064178103706725534[17] = 0;
   out_2064178103706725534[18] = 0;
   out_2064178103706725534[19] = 0;
   out_2064178103706725534[20] = 0;
   out_2064178103706725534[21] = 0;
   out_2064178103706725534[22] = 0;
   out_2064178103706725534[23] = 0;
   out_2064178103706725534[24] = 0;
   out_2064178103706725534[25] = 1;
   out_2064178103706725534[26] = 0;
   out_2064178103706725534[27] = 0;
   out_2064178103706725534[28] = 1;
   out_2064178103706725534[29] = 0;
   out_2064178103706725534[30] = 0;
   out_2064178103706725534[31] = 0;
   out_2064178103706725534[32] = 0;
   out_2064178103706725534[33] = 0;
   out_2064178103706725534[34] = 0;
   out_2064178103706725534[35] = 0;
   out_2064178103706725534[36] = 0;
   out_2064178103706725534[37] = 0;
   out_2064178103706725534[38] = 0;
   out_2064178103706725534[39] = 0;
   out_2064178103706725534[40] = 0;
   out_2064178103706725534[41] = 0;
   out_2064178103706725534[42] = 0;
   out_2064178103706725534[43] = 0;
   out_2064178103706725534[44] = 1;
   out_2064178103706725534[45] = 0;
   out_2064178103706725534[46] = 0;
   out_2064178103706725534[47] = 1;
   out_2064178103706725534[48] = 0;
   out_2064178103706725534[49] = 0;
   out_2064178103706725534[50] = 0;
   out_2064178103706725534[51] = 0;
   out_2064178103706725534[52] = 0;
   out_2064178103706725534[53] = 0;
}
void h_10(double *state, double *unused, double *out_1155728135803400153) {
   out_1155728135803400153[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1155728135803400153[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1155728135803400153[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8226063157301123461) {
   out_8226063157301123461[0] = 0;
   out_8226063157301123461[1] = 9.8100000000000005*cos(state[1]);
   out_8226063157301123461[2] = 0;
   out_8226063157301123461[3] = 0;
   out_8226063157301123461[4] = -state[8];
   out_8226063157301123461[5] = state[7];
   out_8226063157301123461[6] = 0;
   out_8226063157301123461[7] = state[5];
   out_8226063157301123461[8] = -state[4];
   out_8226063157301123461[9] = 0;
   out_8226063157301123461[10] = 0;
   out_8226063157301123461[11] = 0;
   out_8226063157301123461[12] = 1;
   out_8226063157301123461[13] = 0;
   out_8226063157301123461[14] = 0;
   out_8226063157301123461[15] = 1;
   out_8226063157301123461[16] = 0;
   out_8226063157301123461[17] = 0;
   out_8226063157301123461[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8226063157301123461[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8226063157301123461[20] = 0;
   out_8226063157301123461[21] = state[8];
   out_8226063157301123461[22] = 0;
   out_8226063157301123461[23] = -state[6];
   out_8226063157301123461[24] = -state[5];
   out_8226063157301123461[25] = 0;
   out_8226063157301123461[26] = state[3];
   out_8226063157301123461[27] = 0;
   out_8226063157301123461[28] = 0;
   out_8226063157301123461[29] = 0;
   out_8226063157301123461[30] = 0;
   out_8226063157301123461[31] = 1;
   out_8226063157301123461[32] = 0;
   out_8226063157301123461[33] = 0;
   out_8226063157301123461[34] = 1;
   out_8226063157301123461[35] = 0;
   out_8226063157301123461[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8226063157301123461[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8226063157301123461[38] = 0;
   out_8226063157301123461[39] = -state[7];
   out_8226063157301123461[40] = state[6];
   out_8226063157301123461[41] = 0;
   out_8226063157301123461[42] = state[4];
   out_8226063157301123461[43] = -state[3];
   out_8226063157301123461[44] = 0;
   out_8226063157301123461[45] = 0;
   out_8226063157301123461[46] = 0;
   out_8226063157301123461[47] = 0;
   out_8226063157301123461[48] = 0;
   out_8226063157301123461[49] = 0;
   out_8226063157301123461[50] = 1;
   out_8226063157301123461[51] = 0;
   out_8226063157301123461[52] = 0;
   out_8226063157301123461[53] = 1;
}
void h_13(double *state, double *unused, double *out_4927127245414031844) {
   out_4927127245414031844[0] = state[3];
   out_4927127245414031844[1] = state[4];
   out_4927127245414031844[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1499576184024881430) {
   out_1499576184024881430[0] = 0;
   out_1499576184024881430[1] = 0;
   out_1499576184024881430[2] = 0;
   out_1499576184024881430[3] = 1;
   out_1499576184024881430[4] = 0;
   out_1499576184024881430[5] = 0;
   out_1499576184024881430[6] = 0;
   out_1499576184024881430[7] = 0;
   out_1499576184024881430[8] = 0;
   out_1499576184024881430[9] = 0;
   out_1499576184024881430[10] = 0;
   out_1499576184024881430[11] = 0;
   out_1499576184024881430[12] = 0;
   out_1499576184024881430[13] = 0;
   out_1499576184024881430[14] = 0;
   out_1499576184024881430[15] = 0;
   out_1499576184024881430[16] = 0;
   out_1499576184024881430[17] = 0;
   out_1499576184024881430[18] = 0;
   out_1499576184024881430[19] = 0;
   out_1499576184024881430[20] = 0;
   out_1499576184024881430[21] = 0;
   out_1499576184024881430[22] = 1;
   out_1499576184024881430[23] = 0;
   out_1499576184024881430[24] = 0;
   out_1499576184024881430[25] = 0;
   out_1499576184024881430[26] = 0;
   out_1499576184024881430[27] = 0;
   out_1499576184024881430[28] = 0;
   out_1499576184024881430[29] = 0;
   out_1499576184024881430[30] = 0;
   out_1499576184024881430[31] = 0;
   out_1499576184024881430[32] = 0;
   out_1499576184024881430[33] = 0;
   out_1499576184024881430[34] = 0;
   out_1499576184024881430[35] = 0;
   out_1499576184024881430[36] = 0;
   out_1499576184024881430[37] = 0;
   out_1499576184024881430[38] = 0;
   out_1499576184024881430[39] = 0;
   out_1499576184024881430[40] = 0;
   out_1499576184024881430[41] = 1;
   out_1499576184024881430[42] = 0;
   out_1499576184024881430[43] = 0;
   out_1499576184024881430[44] = 0;
   out_1499576184024881430[45] = 0;
   out_1499576184024881430[46] = 0;
   out_1499576184024881430[47] = 0;
   out_1499576184024881430[48] = 0;
   out_1499576184024881430[49] = 0;
   out_1499576184024881430[50] = 0;
   out_1499576184024881430[51] = 0;
   out_1499576184024881430[52] = 0;
   out_1499576184024881430[53] = 0;
}
void h_14(double *state, double *unused, double *out_7188704726752566078) {
   out_7188704726752566078[0] = state[6];
   out_7188704726752566078[1] = state[7];
   out_7188704726752566078[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5146966536002097830) {
   out_5146966536002097830[0] = 0;
   out_5146966536002097830[1] = 0;
   out_5146966536002097830[2] = 0;
   out_5146966536002097830[3] = 0;
   out_5146966536002097830[4] = 0;
   out_5146966536002097830[5] = 0;
   out_5146966536002097830[6] = 1;
   out_5146966536002097830[7] = 0;
   out_5146966536002097830[8] = 0;
   out_5146966536002097830[9] = 0;
   out_5146966536002097830[10] = 0;
   out_5146966536002097830[11] = 0;
   out_5146966536002097830[12] = 0;
   out_5146966536002097830[13] = 0;
   out_5146966536002097830[14] = 0;
   out_5146966536002097830[15] = 0;
   out_5146966536002097830[16] = 0;
   out_5146966536002097830[17] = 0;
   out_5146966536002097830[18] = 0;
   out_5146966536002097830[19] = 0;
   out_5146966536002097830[20] = 0;
   out_5146966536002097830[21] = 0;
   out_5146966536002097830[22] = 0;
   out_5146966536002097830[23] = 0;
   out_5146966536002097830[24] = 0;
   out_5146966536002097830[25] = 1;
   out_5146966536002097830[26] = 0;
   out_5146966536002097830[27] = 0;
   out_5146966536002097830[28] = 0;
   out_5146966536002097830[29] = 0;
   out_5146966536002097830[30] = 0;
   out_5146966536002097830[31] = 0;
   out_5146966536002097830[32] = 0;
   out_5146966536002097830[33] = 0;
   out_5146966536002097830[34] = 0;
   out_5146966536002097830[35] = 0;
   out_5146966536002097830[36] = 0;
   out_5146966536002097830[37] = 0;
   out_5146966536002097830[38] = 0;
   out_5146966536002097830[39] = 0;
   out_5146966536002097830[40] = 0;
   out_5146966536002097830[41] = 0;
   out_5146966536002097830[42] = 0;
   out_5146966536002097830[43] = 0;
   out_5146966536002097830[44] = 1;
   out_5146966536002097830[45] = 0;
   out_5146966536002097830[46] = 0;
   out_5146966536002097830[47] = 0;
   out_5146966536002097830[48] = 0;
   out_5146966536002097830[49] = 0;
   out_5146966536002097830[50] = 0;
   out_5146966536002097830[51] = 0;
   out_5146966536002097830[52] = 0;
   out_5146966536002097830[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5999999625262296722) {
  err_fun(nom_x, delta_x, out_5999999625262296722);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_608932248278116384) {
  inv_err_fun(nom_x, true_x, out_608932248278116384);
}
void pose_H_mod_fun(double *state, double *out_5835985313550633106) {
  H_mod_fun(state, out_5835985313550633106);
}
void pose_f_fun(double *state, double dt, double *out_5863158505292019107) {
  f_fun(state,  dt, out_5863158505292019107);
}
void pose_F_fun(double *state, double dt, double *out_1611471319636251524) {
  F_fun(state,  dt, out_1611471319636251524);
}
void pose_h_4(double *state, double *unused, double *out_1124236774130910347) {
  h_4(state, unused, out_1124236774130910347);
}
void pose_H_4(double *state, double *unused, double *out_2064178103706725534) {
  H_4(state, unused, out_2064178103706725534);
}
void pose_h_10(double *state, double *unused, double *out_1155728135803400153) {
  h_10(state, unused, out_1155728135803400153);
}
void pose_H_10(double *state, double *unused, double *out_8226063157301123461) {
  H_10(state, unused, out_8226063157301123461);
}
void pose_h_13(double *state, double *unused, double *out_4927127245414031844) {
  h_13(state, unused, out_4927127245414031844);
}
void pose_H_13(double *state, double *unused, double *out_1499576184024881430) {
  H_13(state, unused, out_1499576184024881430);
}
void pose_h_14(double *state, double *unused, double *out_7188704726752566078) {
  h_14(state, unused, out_7188704726752566078);
}
void pose_H_14(double *state, double *unused, double *out_5146966536002097830) {
  H_14(state, unused, out_5146966536002097830);
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
