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
void err_fun(double *nom_x, double *delta_x, double *out_9016928863822956392) {
   out_9016928863822956392[0] = delta_x[0] + nom_x[0];
   out_9016928863822956392[1] = delta_x[1] + nom_x[1];
   out_9016928863822956392[2] = delta_x[2] + nom_x[2];
   out_9016928863822956392[3] = delta_x[3] + nom_x[3];
   out_9016928863822956392[4] = delta_x[4] + nom_x[4];
   out_9016928863822956392[5] = delta_x[5] + nom_x[5];
   out_9016928863822956392[6] = delta_x[6] + nom_x[6];
   out_9016928863822956392[7] = delta_x[7] + nom_x[7];
   out_9016928863822956392[8] = delta_x[8] + nom_x[8];
   out_9016928863822956392[9] = delta_x[9] + nom_x[9];
   out_9016928863822956392[10] = delta_x[10] + nom_x[10];
   out_9016928863822956392[11] = delta_x[11] + nom_x[11];
   out_9016928863822956392[12] = delta_x[12] + nom_x[12];
   out_9016928863822956392[13] = delta_x[13] + nom_x[13];
   out_9016928863822956392[14] = delta_x[14] + nom_x[14];
   out_9016928863822956392[15] = delta_x[15] + nom_x[15];
   out_9016928863822956392[16] = delta_x[16] + nom_x[16];
   out_9016928863822956392[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4151582763741233475) {
   out_4151582763741233475[0] = -nom_x[0] + true_x[0];
   out_4151582763741233475[1] = -nom_x[1] + true_x[1];
   out_4151582763741233475[2] = -nom_x[2] + true_x[2];
   out_4151582763741233475[3] = -nom_x[3] + true_x[3];
   out_4151582763741233475[4] = -nom_x[4] + true_x[4];
   out_4151582763741233475[5] = -nom_x[5] + true_x[5];
   out_4151582763741233475[6] = -nom_x[6] + true_x[6];
   out_4151582763741233475[7] = -nom_x[7] + true_x[7];
   out_4151582763741233475[8] = -nom_x[8] + true_x[8];
   out_4151582763741233475[9] = -nom_x[9] + true_x[9];
   out_4151582763741233475[10] = -nom_x[10] + true_x[10];
   out_4151582763741233475[11] = -nom_x[11] + true_x[11];
   out_4151582763741233475[12] = -nom_x[12] + true_x[12];
   out_4151582763741233475[13] = -nom_x[13] + true_x[13];
   out_4151582763741233475[14] = -nom_x[14] + true_x[14];
   out_4151582763741233475[15] = -nom_x[15] + true_x[15];
   out_4151582763741233475[16] = -nom_x[16] + true_x[16];
   out_4151582763741233475[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4338917552998734116) {
   out_4338917552998734116[0] = 1.0;
   out_4338917552998734116[1] = 0.0;
   out_4338917552998734116[2] = 0.0;
   out_4338917552998734116[3] = 0.0;
   out_4338917552998734116[4] = 0.0;
   out_4338917552998734116[5] = 0.0;
   out_4338917552998734116[6] = 0.0;
   out_4338917552998734116[7] = 0.0;
   out_4338917552998734116[8] = 0.0;
   out_4338917552998734116[9] = 0.0;
   out_4338917552998734116[10] = 0.0;
   out_4338917552998734116[11] = 0.0;
   out_4338917552998734116[12] = 0.0;
   out_4338917552998734116[13] = 0.0;
   out_4338917552998734116[14] = 0.0;
   out_4338917552998734116[15] = 0.0;
   out_4338917552998734116[16] = 0.0;
   out_4338917552998734116[17] = 0.0;
   out_4338917552998734116[18] = 0.0;
   out_4338917552998734116[19] = 1.0;
   out_4338917552998734116[20] = 0.0;
   out_4338917552998734116[21] = 0.0;
   out_4338917552998734116[22] = 0.0;
   out_4338917552998734116[23] = 0.0;
   out_4338917552998734116[24] = 0.0;
   out_4338917552998734116[25] = 0.0;
   out_4338917552998734116[26] = 0.0;
   out_4338917552998734116[27] = 0.0;
   out_4338917552998734116[28] = 0.0;
   out_4338917552998734116[29] = 0.0;
   out_4338917552998734116[30] = 0.0;
   out_4338917552998734116[31] = 0.0;
   out_4338917552998734116[32] = 0.0;
   out_4338917552998734116[33] = 0.0;
   out_4338917552998734116[34] = 0.0;
   out_4338917552998734116[35] = 0.0;
   out_4338917552998734116[36] = 0.0;
   out_4338917552998734116[37] = 0.0;
   out_4338917552998734116[38] = 1.0;
   out_4338917552998734116[39] = 0.0;
   out_4338917552998734116[40] = 0.0;
   out_4338917552998734116[41] = 0.0;
   out_4338917552998734116[42] = 0.0;
   out_4338917552998734116[43] = 0.0;
   out_4338917552998734116[44] = 0.0;
   out_4338917552998734116[45] = 0.0;
   out_4338917552998734116[46] = 0.0;
   out_4338917552998734116[47] = 0.0;
   out_4338917552998734116[48] = 0.0;
   out_4338917552998734116[49] = 0.0;
   out_4338917552998734116[50] = 0.0;
   out_4338917552998734116[51] = 0.0;
   out_4338917552998734116[52] = 0.0;
   out_4338917552998734116[53] = 0.0;
   out_4338917552998734116[54] = 0.0;
   out_4338917552998734116[55] = 0.0;
   out_4338917552998734116[56] = 0.0;
   out_4338917552998734116[57] = 1.0;
   out_4338917552998734116[58] = 0.0;
   out_4338917552998734116[59] = 0.0;
   out_4338917552998734116[60] = 0.0;
   out_4338917552998734116[61] = 0.0;
   out_4338917552998734116[62] = 0.0;
   out_4338917552998734116[63] = 0.0;
   out_4338917552998734116[64] = 0.0;
   out_4338917552998734116[65] = 0.0;
   out_4338917552998734116[66] = 0.0;
   out_4338917552998734116[67] = 0.0;
   out_4338917552998734116[68] = 0.0;
   out_4338917552998734116[69] = 0.0;
   out_4338917552998734116[70] = 0.0;
   out_4338917552998734116[71] = 0.0;
   out_4338917552998734116[72] = 0.0;
   out_4338917552998734116[73] = 0.0;
   out_4338917552998734116[74] = 0.0;
   out_4338917552998734116[75] = 0.0;
   out_4338917552998734116[76] = 1.0;
   out_4338917552998734116[77] = 0.0;
   out_4338917552998734116[78] = 0.0;
   out_4338917552998734116[79] = 0.0;
   out_4338917552998734116[80] = 0.0;
   out_4338917552998734116[81] = 0.0;
   out_4338917552998734116[82] = 0.0;
   out_4338917552998734116[83] = 0.0;
   out_4338917552998734116[84] = 0.0;
   out_4338917552998734116[85] = 0.0;
   out_4338917552998734116[86] = 0.0;
   out_4338917552998734116[87] = 0.0;
   out_4338917552998734116[88] = 0.0;
   out_4338917552998734116[89] = 0.0;
   out_4338917552998734116[90] = 0.0;
   out_4338917552998734116[91] = 0.0;
   out_4338917552998734116[92] = 0.0;
   out_4338917552998734116[93] = 0.0;
   out_4338917552998734116[94] = 0.0;
   out_4338917552998734116[95] = 1.0;
   out_4338917552998734116[96] = 0.0;
   out_4338917552998734116[97] = 0.0;
   out_4338917552998734116[98] = 0.0;
   out_4338917552998734116[99] = 0.0;
   out_4338917552998734116[100] = 0.0;
   out_4338917552998734116[101] = 0.0;
   out_4338917552998734116[102] = 0.0;
   out_4338917552998734116[103] = 0.0;
   out_4338917552998734116[104] = 0.0;
   out_4338917552998734116[105] = 0.0;
   out_4338917552998734116[106] = 0.0;
   out_4338917552998734116[107] = 0.0;
   out_4338917552998734116[108] = 0.0;
   out_4338917552998734116[109] = 0.0;
   out_4338917552998734116[110] = 0.0;
   out_4338917552998734116[111] = 0.0;
   out_4338917552998734116[112] = 0.0;
   out_4338917552998734116[113] = 0.0;
   out_4338917552998734116[114] = 1.0;
   out_4338917552998734116[115] = 0.0;
   out_4338917552998734116[116] = 0.0;
   out_4338917552998734116[117] = 0.0;
   out_4338917552998734116[118] = 0.0;
   out_4338917552998734116[119] = 0.0;
   out_4338917552998734116[120] = 0.0;
   out_4338917552998734116[121] = 0.0;
   out_4338917552998734116[122] = 0.0;
   out_4338917552998734116[123] = 0.0;
   out_4338917552998734116[124] = 0.0;
   out_4338917552998734116[125] = 0.0;
   out_4338917552998734116[126] = 0.0;
   out_4338917552998734116[127] = 0.0;
   out_4338917552998734116[128] = 0.0;
   out_4338917552998734116[129] = 0.0;
   out_4338917552998734116[130] = 0.0;
   out_4338917552998734116[131] = 0.0;
   out_4338917552998734116[132] = 0.0;
   out_4338917552998734116[133] = 1.0;
   out_4338917552998734116[134] = 0.0;
   out_4338917552998734116[135] = 0.0;
   out_4338917552998734116[136] = 0.0;
   out_4338917552998734116[137] = 0.0;
   out_4338917552998734116[138] = 0.0;
   out_4338917552998734116[139] = 0.0;
   out_4338917552998734116[140] = 0.0;
   out_4338917552998734116[141] = 0.0;
   out_4338917552998734116[142] = 0.0;
   out_4338917552998734116[143] = 0.0;
   out_4338917552998734116[144] = 0.0;
   out_4338917552998734116[145] = 0.0;
   out_4338917552998734116[146] = 0.0;
   out_4338917552998734116[147] = 0.0;
   out_4338917552998734116[148] = 0.0;
   out_4338917552998734116[149] = 0.0;
   out_4338917552998734116[150] = 0.0;
   out_4338917552998734116[151] = 0.0;
   out_4338917552998734116[152] = 1.0;
   out_4338917552998734116[153] = 0.0;
   out_4338917552998734116[154] = 0.0;
   out_4338917552998734116[155] = 0.0;
   out_4338917552998734116[156] = 0.0;
   out_4338917552998734116[157] = 0.0;
   out_4338917552998734116[158] = 0.0;
   out_4338917552998734116[159] = 0.0;
   out_4338917552998734116[160] = 0.0;
   out_4338917552998734116[161] = 0.0;
   out_4338917552998734116[162] = 0.0;
   out_4338917552998734116[163] = 0.0;
   out_4338917552998734116[164] = 0.0;
   out_4338917552998734116[165] = 0.0;
   out_4338917552998734116[166] = 0.0;
   out_4338917552998734116[167] = 0.0;
   out_4338917552998734116[168] = 0.0;
   out_4338917552998734116[169] = 0.0;
   out_4338917552998734116[170] = 0.0;
   out_4338917552998734116[171] = 1.0;
   out_4338917552998734116[172] = 0.0;
   out_4338917552998734116[173] = 0.0;
   out_4338917552998734116[174] = 0.0;
   out_4338917552998734116[175] = 0.0;
   out_4338917552998734116[176] = 0.0;
   out_4338917552998734116[177] = 0.0;
   out_4338917552998734116[178] = 0.0;
   out_4338917552998734116[179] = 0.0;
   out_4338917552998734116[180] = 0.0;
   out_4338917552998734116[181] = 0.0;
   out_4338917552998734116[182] = 0.0;
   out_4338917552998734116[183] = 0.0;
   out_4338917552998734116[184] = 0.0;
   out_4338917552998734116[185] = 0.0;
   out_4338917552998734116[186] = 0.0;
   out_4338917552998734116[187] = 0.0;
   out_4338917552998734116[188] = 0.0;
   out_4338917552998734116[189] = 0.0;
   out_4338917552998734116[190] = 1.0;
   out_4338917552998734116[191] = 0.0;
   out_4338917552998734116[192] = 0.0;
   out_4338917552998734116[193] = 0.0;
   out_4338917552998734116[194] = 0.0;
   out_4338917552998734116[195] = 0.0;
   out_4338917552998734116[196] = 0.0;
   out_4338917552998734116[197] = 0.0;
   out_4338917552998734116[198] = 0.0;
   out_4338917552998734116[199] = 0.0;
   out_4338917552998734116[200] = 0.0;
   out_4338917552998734116[201] = 0.0;
   out_4338917552998734116[202] = 0.0;
   out_4338917552998734116[203] = 0.0;
   out_4338917552998734116[204] = 0.0;
   out_4338917552998734116[205] = 0.0;
   out_4338917552998734116[206] = 0.0;
   out_4338917552998734116[207] = 0.0;
   out_4338917552998734116[208] = 0.0;
   out_4338917552998734116[209] = 1.0;
   out_4338917552998734116[210] = 0.0;
   out_4338917552998734116[211] = 0.0;
   out_4338917552998734116[212] = 0.0;
   out_4338917552998734116[213] = 0.0;
   out_4338917552998734116[214] = 0.0;
   out_4338917552998734116[215] = 0.0;
   out_4338917552998734116[216] = 0.0;
   out_4338917552998734116[217] = 0.0;
   out_4338917552998734116[218] = 0.0;
   out_4338917552998734116[219] = 0.0;
   out_4338917552998734116[220] = 0.0;
   out_4338917552998734116[221] = 0.0;
   out_4338917552998734116[222] = 0.0;
   out_4338917552998734116[223] = 0.0;
   out_4338917552998734116[224] = 0.0;
   out_4338917552998734116[225] = 0.0;
   out_4338917552998734116[226] = 0.0;
   out_4338917552998734116[227] = 0.0;
   out_4338917552998734116[228] = 1.0;
   out_4338917552998734116[229] = 0.0;
   out_4338917552998734116[230] = 0.0;
   out_4338917552998734116[231] = 0.0;
   out_4338917552998734116[232] = 0.0;
   out_4338917552998734116[233] = 0.0;
   out_4338917552998734116[234] = 0.0;
   out_4338917552998734116[235] = 0.0;
   out_4338917552998734116[236] = 0.0;
   out_4338917552998734116[237] = 0.0;
   out_4338917552998734116[238] = 0.0;
   out_4338917552998734116[239] = 0.0;
   out_4338917552998734116[240] = 0.0;
   out_4338917552998734116[241] = 0.0;
   out_4338917552998734116[242] = 0.0;
   out_4338917552998734116[243] = 0.0;
   out_4338917552998734116[244] = 0.0;
   out_4338917552998734116[245] = 0.0;
   out_4338917552998734116[246] = 0.0;
   out_4338917552998734116[247] = 1.0;
   out_4338917552998734116[248] = 0.0;
   out_4338917552998734116[249] = 0.0;
   out_4338917552998734116[250] = 0.0;
   out_4338917552998734116[251] = 0.0;
   out_4338917552998734116[252] = 0.0;
   out_4338917552998734116[253] = 0.0;
   out_4338917552998734116[254] = 0.0;
   out_4338917552998734116[255] = 0.0;
   out_4338917552998734116[256] = 0.0;
   out_4338917552998734116[257] = 0.0;
   out_4338917552998734116[258] = 0.0;
   out_4338917552998734116[259] = 0.0;
   out_4338917552998734116[260] = 0.0;
   out_4338917552998734116[261] = 0.0;
   out_4338917552998734116[262] = 0.0;
   out_4338917552998734116[263] = 0.0;
   out_4338917552998734116[264] = 0.0;
   out_4338917552998734116[265] = 0.0;
   out_4338917552998734116[266] = 1.0;
   out_4338917552998734116[267] = 0.0;
   out_4338917552998734116[268] = 0.0;
   out_4338917552998734116[269] = 0.0;
   out_4338917552998734116[270] = 0.0;
   out_4338917552998734116[271] = 0.0;
   out_4338917552998734116[272] = 0.0;
   out_4338917552998734116[273] = 0.0;
   out_4338917552998734116[274] = 0.0;
   out_4338917552998734116[275] = 0.0;
   out_4338917552998734116[276] = 0.0;
   out_4338917552998734116[277] = 0.0;
   out_4338917552998734116[278] = 0.0;
   out_4338917552998734116[279] = 0.0;
   out_4338917552998734116[280] = 0.0;
   out_4338917552998734116[281] = 0.0;
   out_4338917552998734116[282] = 0.0;
   out_4338917552998734116[283] = 0.0;
   out_4338917552998734116[284] = 0.0;
   out_4338917552998734116[285] = 1.0;
   out_4338917552998734116[286] = 0.0;
   out_4338917552998734116[287] = 0.0;
   out_4338917552998734116[288] = 0.0;
   out_4338917552998734116[289] = 0.0;
   out_4338917552998734116[290] = 0.0;
   out_4338917552998734116[291] = 0.0;
   out_4338917552998734116[292] = 0.0;
   out_4338917552998734116[293] = 0.0;
   out_4338917552998734116[294] = 0.0;
   out_4338917552998734116[295] = 0.0;
   out_4338917552998734116[296] = 0.0;
   out_4338917552998734116[297] = 0.0;
   out_4338917552998734116[298] = 0.0;
   out_4338917552998734116[299] = 0.0;
   out_4338917552998734116[300] = 0.0;
   out_4338917552998734116[301] = 0.0;
   out_4338917552998734116[302] = 0.0;
   out_4338917552998734116[303] = 0.0;
   out_4338917552998734116[304] = 1.0;
   out_4338917552998734116[305] = 0.0;
   out_4338917552998734116[306] = 0.0;
   out_4338917552998734116[307] = 0.0;
   out_4338917552998734116[308] = 0.0;
   out_4338917552998734116[309] = 0.0;
   out_4338917552998734116[310] = 0.0;
   out_4338917552998734116[311] = 0.0;
   out_4338917552998734116[312] = 0.0;
   out_4338917552998734116[313] = 0.0;
   out_4338917552998734116[314] = 0.0;
   out_4338917552998734116[315] = 0.0;
   out_4338917552998734116[316] = 0.0;
   out_4338917552998734116[317] = 0.0;
   out_4338917552998734116[318] = 0.0;
   out_4338917552998734116[319] = 0.0;
   out_4338917552998734116[320] = 0.0;
   out_4338917552998734116[321] = 0.0;
   out_4338917552998734116[322] = 0.0;
   out_4338917552998734116[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5686895573409391632) {
   out_5686895573409391632[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5686895573409391632[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5686895573409391632[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5686895573409391632[3] = dt*state[12] + state[3];
   out_5686895573409391632[4] = dt*state[13] + state[4];
   out_5686895573409391632[5] = dt*state[14] + state[5];
   out_5686895573409391632[6] = state[6];
   out_5686895573409391632[7] = state[7];
   out_5686895573409391632[8] = state[8];
   out_5686895573409391632[9] = state[9];
   out_5686895573409391632[10] = state[10];
   out_5686895573409391632[11] = state[11];
   out_5686895573409391632[12] = state[12];
   out_5686895573409391632[13] = state[13];
   out_5686895573409391632[14] = state[14];
   out_5686895573409391632[15] = state[15];
   out_5686895573409391632[16] = state[16];
   out_5686895573409391632[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4802469097723825273) {
   out_4802469097723825273[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4802469097723825273[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4802469097723825273[2] = 0;
   out_4802469097723825273[3] = 0;
   out_4802469097723825273[4] = 0;
   out_4802469097723825273[5] = 0;
   out_4802469097723825273[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4802469097723825273[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4802469097723825273[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4802469097723825273[9] = 0;
   out_4802469097723825273[10] = 0;
   out_4802469097723825273[11] = 0;
   out_4802469097723825273[12] = 0;
   out_4802469097723825273[13] = 0;
   out_4802469097723825273[14] = 0;
   out_4802469097723825273[15] = 0;
   out_4802469097723825273[16] = 0;
   out_4802469097723825273[17] = 0;
   out_4802469097723825273[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4802469097723825273[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4802469097723825273[20] = 0;
   out_4802469097723825273[21] = 0;
   out_4802469097723825273[22] = 0;
   out_4802469097723825273[23] = 0;
   out_4802469097723825273[24] = 0;
   out_4802469097723825273[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4802469097723825273[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4802469097723825273[27] = 0;
   out_4802469097723825273[28] = 0;
   out_4802469097723825273[29] = 0;
   out_4802469097723825273[30] = 0;
   out_4802469097723825273[31] = 0;
   out_4802469097723825273[32] = 0;
   out_4802469097723825273[33] = 0;
   out_4802469097723825273[34] = 0;
   out_4802469097723825273[35] = 0;
   out_4802469097723825273[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4802469097723825273[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4802469097723825273[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4802469097723825273[39] = 0;
   out_4802469097723825273[40] = 0;
   out_4802469097723825273[41] = 0;
   out_4802469097723825273[42] = 0;
   out_4802469097723825273[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4802469097723825273[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4802469097723825273[45] = 0;
   out_4802469097723825273[46] = 0;
   out_4802469097723825273[47] = 0;
   out_4802469097723825273[48] = 0;
   out_4802469097723825273[49] = 0;
   out_4802469097723825273[50] = 0;
   out_4802469097723825273[51] = 0;
   out_4802469097723825273[52] = 0;
   out_4802469097723825273[53] = 0;
   out_4802469097723825273[54] = 0;
   out_4802469097723825273[55] = 0;
   out_4802469097723825273[56] = 0;
   out_4802469097723825273[57] = 1;
   out_4802469097723825273[58] = 0;
   out_4802469097723825273[59] = 0;
   out_4802469097723825273[60] = 0;
   out_4802469097723825273[61] = 0;
   out_4802469097723825273[62] = 0;
   out_4802469097723825273[63] = 0;
   out_4802469097723825273[64] = 0;
   out_4802469097723825273[65] = 0;
   out_4802469097723825273[66] = dt;
   out_4802469097723825273[67] = 0;
   out_4802469097723825273[68] = 0;
   out_4802469097723825273[69] = 0;
   out_4802469097723825273[70] = 0;
   out_4802469097723825273[71] = 0;
   out_4802469097723825273[72] = 0;
   out_4802469097723825273[73] = 0;
   out_4802469097723825273[74] = 0;
   out_4802469097723825273[75] = 0;
   out_4802469097723825273[76] = 1;
   out_4802469097723825273[77] = 0;
   out_4802469097723825273[78] = 0;
   out_4802469097723825273[79] = 0;
   out_4802469097723825273[80] = 0;
   out_4802469097723825273[81] = 0;
   out_4802469097723825273[82] = 0;
   out_4802469097723825273[83] = 0;
   out_4802469097723825273[84] = 0;
   out_4802469097723825273[85] = dt;
   out_4802469097723825273[86] = 0;
   out_4802469097723825273[87] = 0;
   out_4802469097723825273[88] = 0;
   out_4802469097723825273[89] = 0;
   out_4802469097723825273[90] = 0;
   out_4802469097723825273[91] = 0;
   out_4802469097723825273[92] = 0;
   out_4802469097723825273[93] = 0;
   out_4802469097723825273[94] = 0;
   out_4802469097723825273[95] = 1;
   out_4802469097723825273[96] = 0;
   out_4802469097723825273[97] = 0;
   out_4802469097723825273[98] = 0;
   out_4802469097723825273[99] = 0;
   out_4802469097723825273[100] = 0;
   out_4802469097723825273[101] = 0;
   out_4802469097723825273[102] = 0;
   out_4802469097723825273[103] = 0;
   out_4802469097723825273[104] = dt;
   out_4802469097723825273[105] = 0;
   out_4802469097723825273[106] = 0;
   out_4802469097723825273[107] = 0;
   out_4802469097723825273[108] = 0;
   out_4802469097723825273[109] = 0;
   out_4802469097723825273[110] = 0;
   out_4802469097723825273[111] = 0;
   out_4802469097723825273[112] = 0;
   out_4802469097723825273[113] = 0;
   out_4802469097723825273[114] = 1;
   out_4802469097723825273[115] = 0;
   out_4802469097723825273[116] = 0;
   out_4802469097723825273[117] = 0;
   out_4802469097723825273[118] = 0;
   out_4802469097723825273[119] = 0;
   out_4802469097723825273[120] = 0;
   out_4802469097723825273[121] = 0;
   out_4802469097723825273[122] = 0;
   out_4802469097723825273[123] = 0;
   out_4802469097723825273[124] = 0;
   out_4802469097723825273[125] = 0;
   out_4802469097723825273[126] = 0;
   out_4802469097723825273[127] = 0;
   out_4802469097723825273[128] = 0;
   out_4802469097723825273[129] = 0;
   out_4802469097723825273[130] = 0;
   out_4802469097723825273[131] = 0;
   out_4802469097723825273[132] = 0;
   out_4802469097723825273[133] = 1;
   out_4802469097723825273[134] = 0;
   out_4802469097723825273[135] = 0;
   out_4802469097723825273[136] = 0;
   out_4802469097723825273[137] = 0;
   out_4802469097723825273[138] = 0;
   out_4802469097723825273[139] = 0;
   out_4802469097723825273[140] = 0;
   out_4802469097723825273[141] = 0;
   out_4802469097723825273[142] = 0;
   out_4802469097723825273[143] = 0;
   out_4802469097723825273[144] = 0;
   out_4802469097723825273[145] = 0;
   out_4802469097723825273[146] = 0;
   out_4802469097723825273[147] = 0;
   out_4802469097723825273[148] = 0;
   out_4802469097723825273[149] = 0;
   out_4802469097723825273[150] = 0;
   out_4802469097723825273[151] = 0;
   out_4802469097723825273[152] = 1;
   out_4802469097723825273[153] = 0;
   out_4802469097723825273[154] = 0;
   out_4802469097723825273[155] = 0;
   out_4802469097723825273[156] = 0;
   out_4802469097723825273[157] = 0;
   out_4802469097723825273[158] = 0;
   out_4802469097723825273[159] = 0;
   out_4802469097723825273[160] = 0;
   out_4802469097723825273[161] = 0;
   out_4802469097723825273[162] = 0;
   out_4802469097723825273[163] = 0;
   out_4802469097723825273[164] = 0;
   out_4802469097723825273[165] = 0;
   out_4802469097723825273[166] = 0;
   out_4802469097723825273[167] = 0;
   out_4802469097723825273[168] = 0;
   out_4802469097723825273[169] = 0;
   out_4802469097723825273[170] = 0;
   out_4802469097723825273[171] = 1;
   out_4802469097723825273[172] = 0;
   out_4802469097723825273[173] = 0;
   out_4802469097723825273[174] = 0;
   out_4802469097723825273[175] = 0;
   out_4802469097723825273[176] = 0;
   out_4802469097723825273[177] = 0;
   out_4802469097723825273[178] = 0;
   out_4802469097723825273[179] = 0;
   out_4802469097723825273[180] = 0;
   out_4802469097723825273[181] = 0;
   out_4802469097723825273[182] = 0;
   out_4802469097723825273[183] = 0;
   out_4802469097723825273[184] = 0;
   out_4802469097723825273[185] = 0;
   out_4802469097723825273[186] = 0;
   out_4802469097723825273[187] = 0;
   out_4802469097723825273[188] = 0;
   out_4802469097723825273[189] = 0;
   out_4802469097723825273[190] = 1;
   out_4802469097723825273[191] = 0;
   out_4802469097723825273[192] = 0;
   out_4802469097723825273[193] = 0;
   out_4802469097723825273[194] = 0;
   out_4802469097723825273[195] = 0;
   out_4802469097723825273[196] = 0;
   out_4802469097723825273[197] = 0;
   out_4802469097723825273[198] = 0;
   out_4802469097723825273[199] = 0;
   out_4802469097723825273[200] = 0;
   out_4802469097723825273[201] = 0;
   out_4802469097723825273[202] = 0;
   out_4802469097723825273[203] = 0;
   out_4802469097723825273[204] = 0;
   out_4802469097723825273[205] = 0;
   out_4802469097723825273[206] = 0;
   out_4802469097723825273[207] = 0;
   out_4802469097723825273[208] = 0;
   out_4802469097723825273[209] = 1;
   out_4802469097723825273[210] = 0;
   out_4802469097723825273[211] = 0;
   out_4802469097723825273[212] = 0;
   out_4802469097723825273[213] = 0;
   out_4802469097723825273[214] = 0;
   out_4802469097723825273[215] = 0;
   out_4802469097723825273[216] = 0;
   out_4802469097723825273[217] = 0;
   out_4802469097723825273[218] = 0;
   out_4802469097723825273[219] = 0;
   out_4802469097723825273[220] = 0;
   out_4802469097723825273[221] = 0;
   out_4802469097723825273[222] = 0;
   out_4802469097723825273[223] = 0;
   out_4802469097723825273[224] = 0;
   out_4802469097723825273[225] = 0;
   out_4802469097723825273[226] = 0;
   out_4802469097723825273[227] = 0;
   out_4802469097723825273[228] = 1;
   out_4802469097723825273[229] = 0;
   out_4802469097723825273[230] = 0;
   out_4802469097723825273[231] = 0;
   out_4802469097723825273[232] = 0;
   out_4802469097723825273[233] = 0;
   out_4802469097723825273[234] = 0;
   out_4802469097723825273[235] = 0;
   out_4802469097723825273[236] = 0;
   out_4802469097723825273[237] = 0;
   out_4802469097723825273[238] = 0;
   out_4802469097723825273[239] = 0;
   out_4802469097723825273[240] = 0;
   out_4802469097723825273[241] = 0;
   out_4802469097723825273[242] = 0;
   out_4802469097723825273[243] = 0;
   out_4802469097723825273[244] = 0;
   out_4802469097723825273[245] = 0;
   out_4802469097723825273[246] = 0;
   out_4802469097723825273[247] = 1;
   out_4802469097723825273[248] = 0;
   out_4802469097723825273[249] = 0;
   out_4802469097723825273[250] = 0;
   out_4802469097723825273[251] = 0;
   out_4802469097723825273[252] = 0;
   out_4802469097723825273[253] = 0;
   out_4802469097723825273[254] = 0;
   out_4802469097723825273[255] = 0;
   out_4802469097723825273[256] = 0;
   out_4802469097723825273[257] = 0;
   out_4802469097723825273[258] = 0;
   out_4802469097723825273[259] = 0;
   out_4802469097723825273[260] = 0;
   out_4802469097723825273[261] = 0;
   out_4802469097723825273[262] = 0;
   out_4802469097723825273[263] = 0;
   out_4802469097723825273[264] = 0;
   out_4802469097723825273[265] = 0;
   out_4802469097723825273[266] = 1;
   out_4802469097723825273[267] = 0;
   out_4802469097723825273[268] = 0;
   out_4802469097723825273[269] = 0;
   out_4802469097723825273[270] = 0;
   out_4802469097723825273[271] = 0;
   out_4802469097723825273[272] = 0;
   out_4802469097723825273[273] = 0;
   out_4802469097723825273[274] = 0;
   out_4802469097723825273[275] = 0;
   out_4802469097723825273[276] = 0;
   out_4802469097723825273[277] = 0;
   out_4802469097723825273[278] = 0;
   out_4802469097723825273[279] = 0;
   out_4802469097723825273[280] = 0;
   out_4802469097723825273[281] = 0;
   out_4802469097723825273[282] = 0;
   out_4802469097723825273[283] = 0;
   out_4802469097723825273[284] = 0;
   out_4802469097723825273[285] = 1;
   out_4802469097723825273[286] = 0;
   out_4802469097723825273[287] = 0;
   out_4802469097723825273[288] = 0;
   out_4802469097723825273[289] = 0;
   out_4802469097723825273[290] = 0;
   out_4802469097723825273[291] = 0;
   out_4802469097723825273[292] = 0;
   out_4802469097723825273[293] = 0;
   out_4802469097723825273[294] = 0;
   out_4802469097723825273[295] = 0;
   out_4802469097723825273[296] = 0;
   out_4802469097723825273[297] = 0;
   out_4802469097723825273[298] = 0;
   out_4802469097723825273[299] = 0;
   out_4802469097723825273[300] = 0;
   out_4802469097723825273[301] = 0;
   out_4802469097723825273[302] = 0;
   out_4802469097723825273[303] = 0;
   out_4802469097723825273[304] = 1;
   out_4802469097723825273[305] = 0;
   out_4802469097723825273[306] = 0;
   out_4802469097723825273[307] = 0;
   out_4802469097723825273[308] = 0;
   out_4802469097723825273[309] = 0;
   out_4802469097723825273[310] = 0;
   out_4802469097723825273[311] = 0;
   out_4802469097723825273[312] = 0;
   out_4802469097723825273[313] = 0;
   out_4802469097723825273[314] = 0;
   out_4802469097723825273[315] = 0;
   out_4802469097723825273[316] = 0;
   out_4802469097723825273[317] = 0;
   out_4802469097723825273[318] = 0;
   out_4802469097723825273[319] = 0;
   out_4802469097723825273[320] = 0;
   out_4802469097723825273[321] = 0;
   out_4802469097723825273[322] = 0;
   out_4802469097723825273[323] = 1;
}
void h_4(double *state, double *unused, double *out_7554104894661564763) {
   out_7554104894661564763[0] = state[6] + state[9];
   out_7554104894661564763[1] = state[7] + state[10];
   out_7554104894661564763[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8955308135671736765) {
   out_8955308135671736765[0] = 0;
   out_8955308135671736765[1] = 0;
   out_8955308135671736765[2] = 0;
   out_8955308135671736765[3] = 0;
   out_8955308135671736765[4] = 0;
   out_8955308135671736765[5] = 0;
   out_8955308135671736765[6] = 1;
   out_8955308135671736765[7] = 0;
   out_8955308135671736765[8] = 0;
   out_8955308135671736765[9] = 1;
   out_8955308135671736765[10] = 0;
   out_8955308135671736765[11] = 0;
   out_8955308135671736765[12] = 0;
   out_8955308135671736765[13] = 0;
   out_8955308135671736765[14] = 0;
   out_8955308135671736765[15] = 0;
   out_8955308135671736765[16] = 0;
   out_8955308135671736765[17] = 0;
   out_8955308135671736765[18] = 0;
   out_8955308135671736765[19] = 0;
   out_8955308135671736765[20] = 0;
   out_8955308135671736765[21] = 0;
   out_8955308135671736765[22] = 0;
   out_8955308135671736765[23] = 0;
   out_8955308135671736765[24] = 0;
   out_8955308135671736765[25] = 1;
   out_8955308135671736765[26] = 0;
   out_8955308135671736765[27] = 0;
   out_8955308135671736765[28] = 1;
   out_8955308135671736765[29] = 0;
   out_8955308135671736765[30] = 0;
   out_8955308135671736765[31] = 0;
   out_8955308135671736765[32] = 0;
   out_8955308135671736765[33] = 0;
   out_8955308135671736765[34] = 0;
   out_8955308135671736765[35] = 0;
   out_8955308135671736765[36] = 0;
   out_8955308135671736765[37] = 0;
   out_8955308135671736765[38] = 0;
   out_8955308135671736765[39] = 0;
   out_8955308135671736765[40] = 0;
   out_8955308135671736765[41] = 0;
   out_8955308135671736765[42] = 0;
   out_8955308135671736765[43] = 0;
   out_8955308135671736765[44] = 1;
   out_8955308135671736765[45] = 0;
   out_8955308135671736765[46] = 0;
   out_8955308135671736765[47] = 1;
   out_8955308135671736765[48] = 0;
   out_8955308135671736765[49] = 0;
   out_8955308135671736765[50] = 0;
   out_8955308135671736765[51] = 0;
   out_8955308135671736765[52] = 0;
   out_8955308135671736765[53] = 0;
}
void h_10(double *state, double *unused, double *out_6873089334257555130) {
   out_6873089334257555130[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6873089334257555130[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6873089334257555130[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3021799401528491989) {
   out_3021799401528491989[0] = 0;
   out_3021799401528491989[1] = 9.8100000000000005*cos(state[1]);
   out_3021799401528491989[2] = 0;
   out_3021799401528491989[3] = 0;
   out_3021799401528491989[4] = -state[8];
   out_3021799401528491989[5] = state[7];
   out_3021799401528491989[6] = 0;
   out_3021799401528491989[7] = state[5];
   out_3021799401528491989[8] = -state[4];
   out_3021799401528491989[9] = 0;
   out_3021799401528491989[10] = 0;
   out_3021799401528491989[11] = 0;
   out_3021799401528491989[12] = 1;
   out_3021799401528491989[13] = 0;
   out_3021799401528491989[14] = 0;
   out_3021799401528491989[15] = 1;
   out_3021799401528491989[16] = 0;
   out_3021799401528491989[17] = 0;
   out_3021799401528491989[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3021799401528491989[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3021799401528491989[20] = 0;
   out_3021799401528491989[21] = state[8];
   out_3021799401528491989[22] = 0;
   out_3021799401528491989[23] = -state[6];
   out_3021799401528491989[24] = -state[5];
   out_3021799401528491989[25] = 0;
   out_3021799401528491989[26] = state[3];
   out_3021799401528491989[27] = 0;
   out_3021799401528491989[28] = 0;
   out_3021799401528491989[29] = 0;
   out_3021799401528491989[30] = 0;
   out_3021799401528491989[31] = 1;
   out_3021799401528491989[32] = 0;
   out_3021799401528491989[33] = 0;
   out_3021799401528491989[34] = 1;
   out_3021799401528491989[35] = 0;
   out_3021799401528491989[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3021799401528491989[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3021799401528491989[38] = 0;
   out_3021799401528491989[39] = -state[7];
   out_3021799401528491989[40] = state[6];
   out_3021799401528491989[41] = 0;
   out_3021799401528491989[42] = state[4];
   out_3021799401528491989[43] = -state[3];
   out_3021799401528491989[44] = 0;
   out_3021799401528491989[45] = 0;
   out_3021799401528491989[46] = 0;
   out_3021799401528491989[47] = 0;
   out_3021799401528491989[48] = 0;
   out_3021799401528491989[49] = 0;
   out_3021799401528491989[50] = 1;
   out_3021799401528491989[51] = 0;
   out_3021799401528491989[52] = 0;
   out_3021799401528491989[53] = 1;
}
void h_13(double *state, double *unused, double *out_4311220329493223705) {
   out_4311220329493223705[0] = state[3];
   out_4311220329493223705[1] = state[4];
   out_4311220329493223705[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5743034310339403964) {
   out_5743034310339403964[0] = 0;
   out_5743034310339403964[1] = 0;
   out_5743034310339403964[2] = 0;
   out_5743034310339403964[3] = 1;
   out_5743034310339403964[4] = 0;
   out_5743034310339403964[5] = 0;
   out_5743034310339403964[6] = 0;
   out_5743034310339403964[7] = 0;
   out_5743034310339403964[8] = 0;
   out_5743034310339403964[9] = 0;
   out_5743034310339403964[10] = 0;
   out_5743034310339403964[11] = 0;
   out_5743034310339403964[12] = 0;
   out_5743034310339403964[13] = 0;
   out_5743034310339403964[14] = 0;
   out_5743034310339403964[15] = 0;
   out_5743034310339403964[16] = 0;
   out_5743034310339403964[17] = 0;
   out_5743034310339403964[18] = 0;
   out_5743034310339403964[19] = 0;
   out_5743034310339403964[20] = 0;
   out_5743034310339403964[21] = 0;
   out_5743034310339403964[22] = 1;
   out_5743034310339403964[23] = 0;
   out_5743034310339403964[24] = 0;
   out_5743034310339403964[25] = 0;
   out_5743034310339403964[26] = 0;
   out_5743034310339403964[27] = 0;
   out_5743034310339403964[28] = 0;
   out_5743034310339403964[29] = 0;
   out_5743034310339403964[30] = 0;
   out_5743034310339403964[31] = 0;
   out_5743034310339403964[32] = 0;
   out_5743034310339403964[33] = 0;
   out_5743034310339403964[34] = 0;
   out_5743034310339403964[35] = 0;
   out_5743034310339403964[36] = 0;
   out_5743034310339403964[37] = 0;
   out_5743034310339403964[38] = 0;
   out_5743034310339403964[39] = 0;
   out_5743034310339403964[40] = 0;
   out_5743034310339403964[41] = 1;
   out_5743034310339403964[42] = 0;
   out_5743034310339403964[43] = 0;
   out_5743034310339403964[44] = 0;
   out_5743034310339403964[45] = 0;
   out_5743034310339403964[46] = 0;
   out_5743034310339403964[47] = 0;
   out_5743034310339403964[48] = 0;
   out_5743034310339403964[49] = 0;
   out_5743034310339403964[50] = 0;
   out_5743034310339403964[51] = 0;
   out_5743034310339403964[52] = 0;
   out_5743034310339403964[53] = 0;
}
void h_14(double *state, double *unused, double *out_8792741387017571645) {
   out_8792741387017571645[0] = state[6];
   out_8792741387017571645[1] = state[7];
   out_8792741387017571645[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4992067279332252236) {
   out_4992067279332252236[0] = 0;
   out_4992067279332252236[1] = 0;
   out_4992067279332252236[2] = 0;
   out_4992067279332252236[3] = 0;
   out_4992067279332252236[4] = 0;
   out_4992067279332252236[5] = 0;
   out_4992067279332252236[6] = 1;
   out_4992067279332252236[7] = 0;
   out_4992067279332252236[8] = 0;
   out_4992067279332252236[9] = 0;
   out_4992067279332252236[10] = 0;
   out_4992067279332252236[11] = 0;
   out_4992067279332252236[12] = 0;
   out_4992067279332252236[13] = 0;
   out_4992067279332252236[14] = 0;
   out_4992067279332252236[15] = 0;
   out_4992067279332252236[16] = 0;
   out_4992067279332252236[17] = 0;
   out_4992067279332252236[18] = 0;
   out_4992067279332252236[19] = 0;
   out_4992067279332252236[20] = 0;
   out_4992067279332252236[21] = 0;
   out_4992067279332252236[22] = 0;
   out_4992067279332252236[23] = 0;
   out_4992067279332252236[24] = 0;
   out_4992067279332252236[25] = 1;
   out_4992067279332252236[26] = 0;
   out_4992067279332252236[27] = 0;
   out_4992067279332252236[28] = 0;
   out_4992067279332252236[29] = 0;
   out_4992067279332252236[30] = 0;
   out_4992067279332252236[31] = 0;
   out_4992067279332252236[32] = 0;
   out_4992067279332252236[33] = 0;
   out_4992067279332252236[34] = 0;
   out_4992067279332252236[35] = 0;
   out_4992067279332252236[36] = 0;
   out_4992067279332252236[37] = 0;
   out_4992067279332252236[38] = 0;
   out_4992067279332252236[39] = 0;
   out_4992067279332252236[40] = 0;
   out_4992067279332252236[41] = 0;
   out_4992067279332252236[42] = 0;
   out_4992067279332252236[43] = 0;
   out_4992067279332252236[44] = 1;
   out_4992067279332252236[45] = 0;
   out_4992067279332252236[46] = 0;
   out_4992067279332252236[47] = 0;
   out_4992067279332252236[48] = 0;
   out_4992067279332252236[49] = 0;
   out_4992067279332252236[50] = 0;
   out_4992067279332252236[51] = 0;
   out_4992067279332252236[52] = 0;
   out_4992067279332252236[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_9016928863822956392) {
  err_fun(nom_x, delta_x, out_9016928863822956392);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4151582763741233475) {
  inv_err_fun(nom_x, true_x, out_4151582763741233475);
}
void pose_H_mod_fun(double *state, double *out_4338917552998734116) {
  H_mod_fun(state, out_4338917552998734116);
}
void pose_f_fun(double *state, double dt, double *out_5686895573409391632) {
  f_fun(state,  dt, out_5686895573409391632);
}
void pose_F_fun(double *state, double dt, double *out_4802469097723825273) {
  F_fun(state,  dt, out_4802469097723825273);
}
void pose_h_4(double *state, double *unused, double *out_7554104894661564763) {
  h_4(state, unused, out_7554104894661564763);
}
void pose_H_4(double *state, double *unused, double *out_8955308135671736765) {
  H_4(state, unused, out_8955308135671736765);
}
void pose_h_10(double *state, double *unused, double *out_6873089334257555130) {
  h_10(state, unused, out_6873089334257555130);
}
void pose_H_10(double *state, double *unused, double *out_3021799401528491989) {
  H_10(state, unused, out_3021799401528491989);
}
void pose_h_13(double *state, double *unused, double *out_4311220329493223705) {
  h_13(state, unused, out_4311220329493223705);
}
void pose_H_13(double *state, double *unused, double *out_5743034310339403964) {
  H_13(state, unused, out_5743034310339403964);
}
void pose_h_14(double *state, double *unused, double *out_8792741387017571645) {
  h_14(state, unused, out_8792741387017571645);
}
void pose_H_14(double *state, double *unused, double *out_4992067279332252236) {
  H_14(state, unused, out_4992067279332252236);
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
