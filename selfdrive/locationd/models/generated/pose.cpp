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
void err_fun(double *nom_x, double *delta_x, double *out_1302882686935522561) {
   out_1302882686935522561[0] = delta_x[0] + nom_x[0];
   out_1302882686935522561[1] = delta_x[1] + nom_x[1];
   out_1302882686935522561[2] = delta_x[2] + nom_x[2];
   out_1302882686935522561[3] = delta_x[3] + nom_x[3];
   out_1302882686935522561[4] = delta_x[4] + nom_x[4];
   out_1302882686935522561[5] = delta_x[5] + nom_x[5];
   out_1302882686935522561[6] = delta_x[6] + nom_x[6];
   out_1302882686935522561[7] = delta_x[7] + nom_x[7];
   out_1302882686935522561[8] = delta_x[8] + nom_x[8];
   out_1302882686935522561[9] = delta_x[9] + nom_x[9];
   out_1302882686935522561[10] = delta_x[10] + nom_x[10];
   out_1302882686935522561[11] = delta_x[11] + nom_x[11];
   out_1302882686935522561[12] = delta_x[12] + nom_x[12];
   out_1302882686935522561[13] = delta_x[13] + nom_x[13];
   out_1302882686935522561[14] = delta_x[14] + nom_x[14];
   out_1302882686935522561[15] = delta_x[15] + nom_x[15];
   out_1302882686935522561[16] = delta_x[16] + nom_x[16];
   out_1302882686935522561[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9056716141039600519) {
   out_9056716141039600519[0] = -nom_x[0] + true_x[0];
   out_9056716141039600519[1] = -nom_x[1] + true_x[1];
   out_9056716141039600519[2] = -nom_x[2] + true_x[2];
   out_9056716141039600519[3] = -nom_x[3] + true_x[3];
   out_9056716141039600519[4] = -nom_x[4] + true_x[4];
   out_9056716141039600519[5] = -nom_x[5] + true_x[5];
   out_9056716141039600519[6] = -nom_x[6] + true_x[6];
   out_9056716141039600519[7] = -nom_x[7] + true_x[7];
   out_9056716141039600519[8] = -nom_x[8] + true_x[8];
   out_9056716141039600519[9] = -nom_x[9] + true_x[9];
   out_9056716141039600519[10] = -nom_x[10] + true_x[10];
   out_9056716141039600519[11] = -nom_x[11] + true_x[11];
   out_9056716141039600519[12] = -nom_x[12] + true_x[12];
   out_9056716141039600519[13] = -nom_x[13] + true_x[13];
   out_9056716141039600519[14] = -nom_x[14] + true_x[14];
   out_9056716141039600519[15] = -nom_x[15] + true_x[15];
   out_9056716141039600519[16] = -nom_x[16] + true_x[16];
   out_9056716141039600519[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_55467954928580080) {
   out_55467954928580080[0] = 1.0;
   out_55467954928580080[1] = 0.0;
   out_55467954928580080[2] = 0.0;
   out_55467954928580080[3] = 0.0;
   out_55467954928580080[4] = 0.0;
   out_55467954928580080[5] = 0.0;
   out_55467954928580080[6] = 0.0;
   out_55467954928580080[7] = 0.0;
   out_55467954928580080[8] = 0.0;
   out_55467954928580080[9] = 0.0;
   out_55467954928580080[10] = 0.0;
   out_55467954928580080[11] = 0.0;
   out_55467954928580080[12] = 0.0;
   out_55467954928580080[13] = 0.0;
   out_55467954928580080[14] = 0.0;
   out_55467954928580080[15] = 0.0;
   out_55467954928580080[16] = 0.0;
   out_55467954928580080[17] = 0.0;
   out_55467954928580080[18] = 0.0;
   out_55467954928580080[19] = 1.0;
   out_55467954928580080[20] = 0.0;
   out_55467954928580080[21] = 0.0;
   out_55467954928580080[22] = 0.0;
   out_55467954928580080[23] = 0.0;
   out_55467954928580080[24] = 0.0;
   out_55467954928580080[25] = 0.0;
   out_55467954928580080[26] = 0.0;
   out_55467954928580080[27] = 0.0;
   out_55467954928580080[28] = 0.0;
   out_55467954928580080[29] = 0.0;
   out_55467954928580080[30] = 0.0;
   out_55467954928580080[31] = 0.0;
   out_55467954928580080[32] = 0.0;
   out_55467954928580080[33] = 0.0;
   out_55467954928580080[34] = 0.0;
   out_55467954928580080[35] = 0.0;
   out_55467954928580080[36] = 0.0;
   out_55467954928580080[37] = 0.0;
   out_55467954928580080[38] = 1.0;
   out_55467954928580080[39] = 0.0;
   out_55467954928580080[40] = 0.0;
   out_55467954928580080[41] = 0.0;
   out_55467954928580080[42] = 0.0;
   out_55467954928580080[43] = 0.0;
   out_55467954928580080[44] = 0.0;
   out_55467954928580080[45] = 0.0;
   out_55467954928580080[46] = 0.0;
   out_55467954928580080[47] = 0.0;
   out_55467954928580080[48] = 0.0;
   out_55467954928580080[49] = 0.0;
   out_55467954928580080[50] = 0.0;
   out_55467954928580080[51] = 0.0;
   out_55467954928580080[52] = 0.0;
   out_55467954928580080[53] = 0.0;
   out_55467954928580080[54] = 0.0;
   out_55467954928580080[55] = 0.0;
   out_55467954928580080[56] = 0.0;
   out_55467954928580080[57] = 1.0;
   out_55467954928580080[58] = 0.0;
   out_55467954928580080[59] = 0.0;
   out_55467954928580080[60] = 0.0;
   out_55467954928580080[61] = 0.0;
   out_55467954928580080[62] = 0.0;
   out_55467954928580080[63] = 0.0;
   out_55467954928580080[64] = 0.0;
   out_55467954928580080[65] = 0.0;
   out_55467954928580080[66] = 0.0;
   out_55467954928580080[67] = 0.0;
   out_55467954928580080[68] = 0.0;
   out_55467954928580080[69] = 0.0;
   out_55467954928580080[70] = 0.0;
   out_55467954928580080[71] = 0.0;
   out_55467954928580080[72] = 0.0;
   out_55467954928580080[73] = 0.0;
   out_55467954928580080[74] = 0.0;
   out_55467954928580080[75] = 0.0;
   out_55467954928580080[76] = 1.0;
   out_55467954928580080[77] = 0.0;
   out_55467954928580080[78] = 0.0;
   out_55467954928580080[79] = 0.0;
   out_55467954928580080[80] = 0.0;
   out_55467954928580080[81] = 0.0;
   out_55467954928580080[82] = 0.0;
   out_55467954928580080[83] = 0.0;
   out_55467954928580080[84] = 0.0;
   out_55467954928580080[85] = 0.0;
   out_55467954928580080[86] = 0.0;
   out_55467954928580080[87] = 0.0;
   out_55467954928580080[88] = 0.0;
   out_55467954928580080[89] = 0.0;
   out_55467954928580080[90] = 0.0;
   out_55467954928580080[91] = 0.0;
   out_55467954928580080[92] = 0.0;
   out_55467954928580080[93] = 0.0;
   out_55467954928580080[94] = 0.0;
   out_55467954928580080[95] = 1.0;
   out_55467954928580080[96] = 0.0;
   out_55467954928580080[97] = 0.0;
   out_55467954928580080[98] = 0.0;
   out_55467954928580080[99] = 0.0;
   out_55467954928580080[100] = 0.0;
   out_55467954928580080[101] = 0.0;
   out_55467954928580080[102] = 0.0;
   out_55467954928580080[103] = 0.0;
   out_55467954928580080[104] = 0.0;
   out_55467954928580080[105] = 0.0;
   out_55467954928580080[106] = 0.0;
   out_55467954928580080[107] = 0.0;
   out_55467954928580080[108] = 0.0;
   out_55467954928580080[109] = 0.0;
   out_55467954928580080[110] = 0.0;
   out_55467954928580080[111] = 0.0;
   out_55467954928580080[112] = 0.0;
   out_55467954928580080[113] = 0.0;
   out_55467954928580080[114] = 1.0;
   out_55467954928580080[115] = 0.0;
   out_55467954928580080[116] = 0.0;
   out_55467954928580080[117] = 0.0;
   out_55467954928580080[118] = 0.0;
   out_55467954928580080[119] = 0.0;
   out_55467954928580080[120] = 0.0;
   out_55467954928580080[121] = 0.0;
   out_55467954928580080[122] = 0.0;
   out_55467954928580080[123] = 0.0;
   out_55467954928580080[124] = 0.0;
   out_55467954928580080[125] = 0.0;
   out_55467954928580080[126] = 0.0;
   out_55467954928580080[127] = 0.0;
   out_55467954928580080[128] = 0.0;
   out_55467954928580080[129] = 0.0;
   out_55467954928580080[130] = 0.0;
   out_55467954928580080[131] = 0.0;
   out_55467954928580080[132] = 0.0;
   out_55467954928580080[133] = 1.0;
   out_55467954928580080[134] = 0.0;
   out_55467954928580080[135] = 0.0;
   out_55467954928580080[136] = 0.0;
   out_55467954928580080[137] = 0.0;
   out_55467954928580080[138] = 0.0;
   out_55467954928580080[139] = 0.0;
   out_55467954928580080[140] = 0.0;
   out_55467954928580080[141] = 0.0;
   out_55467954928580080[142] = 0.0;
   out_55467954928580080[143] = 0.0;
   out_55467954928580080[144] = 0.0;
   out_55467954928580080[145] = 0.0;
   out_55467954928580080[146] = 0.0;
   out_55467954928580080[147] = 0.0;
   out_55467954928580080[148] = 0.0;
   out_55467954928580080[149] = 0.0;
   out_55467954928580080[150] = 0.0;
   out_55467954928580080[151] = 0.0;
   out_55467954928580080[152] = 1.0;
   out_55467954928580080[153] = 0.0;
   out_55467954928580080[154] = 0.0;
   out_55467954928580080[155] = 0.0;
   out_55467954928580080[156] = 0.0;
   out_55467954928580080[157] = 0.0;
   out_55467954928580080[158] = 0.0;
   out_55467954928580080[159] = 0.0;
   out_55467954928580080[160] = 0.0;
   out_55467954928580080[161] = 0.0;
   out_55467954928580080[162] = 0.0;
   out_55467954928580080[163] = 0.0;
   out_55467954928580080[164] = 0.0;
   out_55467954928580080[165] = 0.0;
   out_55467954928580080[166] = 0.0;
   out_55467954928580080[167] = 0.0;
   out_55467954928580080[168] = 0.0;
   out_55467954928580080[169] = 0.0;
   out_55467954928580080[170] = 0.0;
   out_55467954928580080[171] = 1.0;
   out_55467954928580080[172] = 0.0;
   out_55467954928580080[173] = 0.0;
   out_55467954928580080[174] = 0.0;
   out_55467954928580080[175] = 0.0;
   out_55467954928580080[176] = 0.0;
   out_55467954928580080[177] = 0.0;
   out_55467954928580080[178] = 0.0;
   out_55467954928580080[179] = 0.0;
   out_55467954928580080[180] = 0.0;
   out_55467954928580080[181] = 0.0;
   out_55467954928580080[182] = 0.0;
   out_55467954928580080[183] = 0.0;
   out_55467954928580080[184] = 0.0;
   out_55467954928580080[185] = 0.0;
   out_55467954928580080[186] = 0.0;
   out_55467954928580080[187] = 0.0;
   out_55467954928580080[188] = 0.0;
   out_55467954928580080[189] = 0.0;
   out_55467954928580080[190] = 1.0;
   out_55467954928580080[191] = 0.0;
   out_55467954928580080[192] = 0.0;
   out_55467954928580080[193] = 0.0;
   out_55467954928580080[194] = 0.0;
   out_55467954928580080[195] = 0.0;
   out_55467954928580080[196] = 0.0;
   out_55467954928580080[197] = 0.0;
   out_55467954928580080[198] = 0.0;
   out_55467954928580080[199] = 0.0;
   out_55467954928580080[200] = 0.0;
   out_55467954928580080[201] = 0.0;
   out_55467954928580080[202] = 0.0;
   out_55467954928580080[203] = 0.0;
   out_55467954928580080[204] = 0.0;
   out_55467954928580080[205] = 0.0;
   out_55467954928580080[206] = 0.0;
   out_55467954928580080[207] = 0.0;
   out_55467954928580080[208] = 0.0;
   out_55467954928580080[209] = 1.0;
   out_55467954928580080[210] = 0.0;
   out_55467954928580080[211] = 0.0;
   out_55467954928580080[212] = 0.0;
   out_55467954928580080[213] = 0.0;
   out_55467954928580080[214] = 0.0;
   out_55467954928580080[215] = 0.0;
   out_55467954928580080[216] = 0.0;
   out_55467954928580080[217] = 0.0;
   out_55467954928580080[218] = 0.0;
   out_55467954928580080[219] = 0.0;
   out_55467954928580080[220] = 0.0;
   out_55467954928580080[221] = 0.0;
   out_55467954928580080[222] = 0.0;
   out_55467954928580080[223] = 0.0;
   out_55467954928580080[224] = 0.0;
   out_55467954928580080[225] = 0.0;
   out_55467954928580080[226] = 0.0;
   out_55467954928580080[227] = 0.0;
   out_55467954928580080[228] = 1.0;
   out_55467954928580080[229] = 0.0;
   out_55467954928580080[230] = 0.0;
   out_55467954928580080[231] = 0.0;
   out_55467954928580080[232] = 0.0;
   out_55467954928580080[233] = 0.0;
   out_55467954928580080[234] = 0.0;
   out_55467954928580080[235] = 0.0;
   out_55467954928580080[236] = 0.0;
   out_55467954928580080[237] = 0.0;
   out_55467954928580080[238] = 0.0;
   out_55467954928580080[239] = 0.0;
   out_55467954928580080[240] = 0.0;
   out_55467954928580080[241] = 0.0;
   out_55467954928580080[242] = 0.0;
   out_55467954928580080[243] = 0.0;
   out_55467954928580080[244] = 0.0;
   out_55467954928580080[245] = 0.0;
   out_55467954928580080[246] = 0.0;
   out_55467954928580080[247] = 1.0;
   out_55467954928580080[248] = 0.0;
   out_55467954928580080[249] = 0.0;
   out_55467954928580080[250] = 0.0;
   out_55467954928580080[251] = 0.0;
   out_55467954928580080[252] = 0.0;
   out_55467954928580080[253] = 0.0;
   out_55467954928580080[254] = 0.0;
   out_55467954928580080[255] = 0.0;
   out_55467954928580080[256] = 0.0;
   out_55467954928580080[257] = 0.0;
   out_55467954928580080[258] = 0.0;
   out_55467954928580080[259] = 0.0;
   out_55467954928580080[260] = 0.0;
   out_55467954928580080[261] = 0.0;
   out_55467954928580080[262] = 0.0;
   out_55467954928580080[263] = 0.0;
   out_55467954928580080[264] = 0.0;
   out_55467954928580080[265] = 0.0;
   out_55467954928580080[266] = 1.0;
   out_55467954928580080[267] = 0.0;
   out_55467954928580080[268] = 0.0;
   out_55467954928580080[269] = 0.0;
   out_55467954928580080[270] = 0.0;
   out_55467954928580080[271] = 0.0;
   out_55467954928580080[272] = 0.0;
   out_55467954928580080[273] = 0.0;
   out_55467954928580080[274] = 0.0;
   out_55467954928580080[275] = 0.0;
   out_55467954928580080[276] = 0.0;
   out_55467954928580080[277] = 0.0;
   out_55467954928580080[278] = 0.0;
   out_55467954928580080[279] = 0.0;
   out_55467954928580080[280] = 0.0;
   out_55467954928580080[281] = 0.0;
   out_55467954928580080[282] = 0.0;
   out_55467954928580080[283] = 0.0;
   out_55467954928580080[284] = 0.0;
   out_55467954928580080[285] = 1.0;
   out_55467954928580080[286] = 0.0;
   out_55467954928580080[287] = 0.0;
   out_55467954928580080[288] = 0.0;
   out_55467954928580080[289] = 0.0;
   out_55467954928580080[290] = 0.0;
   out_55467954928580080[291] = 0.0;
   out_55467954928580080[292] = 0.0;
   out_55467954928580080[293] = 0.0;
   out_55467954928580080[294] = 0.0;
   out_55467954928580080[295] = 0.0;
   out_55467954928580080[296] = 0.0;
   out_55467954928580080[297] = 0.0;
   out_55467954928580080[298] = 0.0;
   out_55467954928580080[299] = 0.0;
   out_55467954928580080[300] = 0.0;
   out_55467954928580080[301] = 0.0;
   out_55467954928580080[302] = 0.0;
   out_55467954928580080[303] = 0.0;
   out_55467954928580080[304] = 1.0;
   out_55467954928580080[305] = 0.0;
   out_55467954928580080[306] = 0.0;
   out_55467954928580080[307] = 0.0;
   out_55467954928580080[308] = 0.0;
   out_55467954928580080[309] = 0.0;
   out_55467954928580080[310] = 0.0;
   out_55467954928580080[311] = 0.0;
   out_55467954928580080[312] = 0.0;
   out_55467954928580080[313] = 0.0;
   out_55467954928580080[314] = 0.0;
   out_55467954928580080[315] = 0.0;
   out_55467954928580080[316] = 0.0;
   out_55467954928580080[317] = 0.0;
   out_55467954928580080[318] = 0.0;
   out_55467954928580080[319] = 0.0;
   out_55467954928580080[320] = 0.0;
   out_55467954928580080[321] = 0.0;
   out_55467954928580080[322] = 0.0;
   out_55467954928580080[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1954087496247120441) {
   out_1954087496247120441[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1954087496247120441[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1954087496247120441[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1954087496247120441[3] = dt*state[12] + state[3];
   out_1954087496247120441[4] = dt*state[13] + state[4];
   out_1954087496247120441[5] = dt*state[14] + state[5];
   out_1954087496247120441[6] = state[6];
   out_1954087496247120441[7] = state[7];
   out_1954087496247120441[8] = state[8];
   out_1954087496247120441[9] = state[9];
   out_1954087496247120441[10] = state[10];
   out_1954087496247120441[11] = state[11];
   out_1954087496247120441[12] = state[12];
   out_1954087496247120441[13] = state[13];
   out_1954087496247120441[14] = state[14];
   out_1954087496247120441[15] = state[15];
   out_1954087496247120441[16] = state[16];
   out_1954087496247120441[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8221376313792984867) {
   out_8221376313792984867[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8221376313792984867[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8221376313792984867[2] = 0;
   out_8221376313792984867[3] = 0;
   out_8221376313792984867[4] = 0;
   out_8221376313792984867[5] = 0;
   out_8221376313792984867[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8221376313792984867[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8221376313792984867[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8221376313792984867[9] = 0;
   out_8221376313792984867[10] = 0;
   out_8221376313792984867[11] = 0;
   out_8221376313792984867[12] = 0;
   out_8221376313792984867[13] = 0;
   out_8221376313792984867[14] = 0;
   out_8221376313792984867[15] = 0;
   out_8221376313792984867[16] = 0;
   out_8221376313792984867[17] = 0;
   out_8221376313792984867[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8221376313792984867[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8221376313792984867[20] = 0;
   out_8221376313792984867[21] = 0;
   out_8221376313792984867[22] = 0;
   out_8221376313792984867[23] = 0;
   out_8221376313792984867[24] = 0;
   out_8221376313792984867[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8221376313792984867[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8221376313792984867[27] = 0;
   out_8221376313792984867[28] = 0;
   out_8221376313792984867[29] = 0;
   out_8221376313792984867[30] = 0;
   out_8221376313792984867[31] = 0;
   out_8221376313792984867[32] = 0;
   out_8221376313792984867[33] = 0;
   out_8221376313792984867[34] = 0;
   out_8221376313792984867[35] = 0;
   out_8221376313792984867[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8221376313792984867[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8221376313792984867[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8221376313792984867[39] = 0;
   out_8221376313792984867[40] = 0;
   out_8221376313792984867[41] = 0;
   out_8221376313792984867[42] = 0;
   out_8221376313792984867[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8221376313792984867[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8221376313792984867[45] = 0;
   out_8221376313792984867[46] = 0;
   out_8221376313792984867[47] = 0;
   out_8221376313792984867[48] = 0;
   out_8221376313792984867[49] = 0;
   out_8221376313792984867[50] = 0;
   out_8221376313792984867[51] = 0;
   out_8221376313792984867[52] = 0;
   out_8221376313792984867[53] = 0;
   out_8221376313792984867[54] = 0;
   out_8221376313792984867[55] = 0;
   out_8221376313792984867[56] = 0;
   out_8221376313792984867[57] = 1;
   out_8221376313792984867[58] = 0;
   out_8221376313792984867[59] = 0;
   out_8221376313792984867[60] = 0;
   out_8221376313792984867[61] = 0;
   out_8221376313792984867[62] = 0;
   out_8221376313792984867[63] = 0;
   out_8221376313792984867[64] = 0;
   out_8221376313792984867[65] = 0;
   out_8221376313792984867[66] = dt;
   out_8221376313792984867[67] = 0;
   out_8221376313792984867[68] = 0;
   out_8221376313792984867[69] = 0;
   out_8221376313792984867[70] = 0;
   out_8221376313792984867[71] = 0;
   out_8221376313792984867[72] = 0;
   out_8221376313792984867[73] = 0;
   out_8221376313792984867[74] = 0;
   out_8221376313792984867[75] = 0;
   out_8221376313792984867[76] = 1;
   out_8221376313792984867[77] = 0;
   out_8221376313792984867[78] = 0;
   out_8221376313792984867[79] = 0;
   out_8221376313792984867[80] = 0;
   out_8221376313792984867[81] = 0;
   out_8221376313792984867[82] = 0;
   out_8221376313792984867[83] = 0;
   out_8221376313792984867[84] = 0;
   out_8221376313792984867[85] = dt;
   out_8221376313792984867[86] = 0;
   out_8221376313792984867[87] = 0;
   out_8221376313792984867[88] = 0;
   out_8221376313792984867[89] = 0;
   out_8221376313792984867[90] = 0;
   out_8221376313792984867[91] = 0;
   out_8221376313792984867[92] = 0;
   out_8221376313792984867[93] = 0;
   out_8221376313792984867[94] = 0;
   out_8221376313792984867[95] = 1;
   out_8221376313792984867[96] = 0;
   out_8221376313792984867[97] = 0;
   out_8221376313792984867[98] = 0;
   out_8221376313792984867[99] = 0;
   out_8221376313792984867[100] = 0;
   out_8221376313792984867[101] = 0;
   out_8221376313792984867[102] = 0;
   out_8221376313792984867[103] = 0;
   out_8221376313792984867[104] = dt;
   out_8221376313792984867[105] = 0;
   out_8221376313792984867[106] = 0;
   out_8221376313792984867[107] = 0;
   out_8221376313792984867[108] = 0;
   out_8221376313792984867[109] = 0;
   out_8221376313792984867[110] = 0;
   out_8221376313792984867[111] = 0;
   out_8221376313792984867[112] = 0;
   out_8221376313792984867[113] = 0;
   out_8221376313792984867[114] = 1;
   out_8221376313792984867[115] = 0;
   out_8221376313792984867[116] = 0;
   out_8221376313792984867[117] = 0;
   out_8221376313792984867[118] = 0;
   out_8221376313792984867[119] = 0;
   out_8221376313792984867[120] = 0;
   out_8221376313792984867[121] = 0;
   out_8221376313792984867[122] = 0;
   out_8221376313792984867[123] = 0;
   out_8221376313792984867[124] = 0;
   out_8221376313792984867[125] = 0;
   out_8221376313792984867[126] = 0;
   out_8221376313792984867[127] = 0;
   out_8221376313792984867[128] = 0;
   out_8221376313792984867[129] = 0;
   out_8221376313792984867[130] = 0;
   out_8221376313792984867[131] = 0;
   out_8221376313792984867[132] = 0;
   out_8221376313792984867[133] = 1;
   out_8221376313792984867[134] = 0;
   out_8221376313792984867[135] = 0;
   out_8221376313792984867[136] = 0;
   out_8221376313792984867[137] = 0;
   out_8221376313792984867[138] = 0;
   out_8221376313792984867[139] = 0;
   out_8221376313792984867[140] = 0;
   out_8221376313792984867[141] = 0;
   out_8221376313792984867[142] = 0;
   out_8221376313792984867[143] = 0;
   out_8221376313792984867[144] = 0;
   out_8221376313792984867[145] = 0;
   out_8221376313792984867[146] = 0;
   out_8221376313792984867[147] = 0;
   out_8221376313792984867[148] = 0;
   out_8221376313792984867[149] = 0;
   out_8221376313792984867[150] = 0;
   out_8221376313792984867[151] = 0;
   out_8221376313792984867[152] = 1;
   out_8221376313792984867[153] = 0;
   out_8221376313792984867[154] = 0;
   out_8221376313792984867[155] = 0;
   out_8221376313792984867[156] = 0;
   out_8221376313792984867[157] = 0;
   out_8221376313792984867[158] = 0;
   out_8221376313792984867[159] = 0;
   out_8221376313792984867[160] = 0;
   out_8221376313792984867[161] = 0;
   out_8221376313792984867[162] = 0;
   out_8221376313792984867[163] = 0;
   out_8221376313792984867[164] = 0;
   out_8221376313792984867[165] = 0;
   out_8221376313792984867[166] = 0;
   out_8221376313792984867[167] = 0;
   out_8221376313792984867[168] = 0;
   out_8221376313792984867[169] = 0;
   out_8221376313792984867[170] = 0;
   out_8221376313792984867[171] = 1;
   out_8221376313792984867[172] = 0;
   out_8221376313792984867[173] = 0;
   out_8221376313792984867[174] = 0;
   out_8221376313792984867[175] = 0;
   out_8221376313792984867[176] = 0;
   out_8221376313792984867[177] = 0;
   out_8221376313792984867[178] = 0;
   out_8221376313792984867[179] = 0;
   out_8221376313792984867[180] = 0;
   out_8221376313792984867[181] = 0;
   out_8221376313792984867[182] = 0;
   out_8221376313792984867[183] = 0;
   out_8221376313792984867[184] = 0;
   out_8221376313792984867[185] = 0;
   out_8221376313792984867[186] = 0;
   out_8221376313792984867[187] = 0;
   out_8221376313792984867[188] = 0;
   out_8221376313792984867[189] = 0;
   out_8221376313792984867[190] = 1;
   out_8221376313792984867[191] = 0;
   out_8221376313792984867[192] = 0;
   out_8221376313792984867[193] = 0;
   out_8221376313792984867[194] = 0;
   out_8221376313792984867[195] = 0;
   out_8221376313792984867[196] = 0;
   out_8221376313792984867[197] = 0;
   out_8221376313792984867[198] = 0;
   out_8221376313792984867[199] = 0;
   out_8221376313792984867[200] = 0;
   out_8221376313792984867[201] = 0;
   out_8221376313792984867[202] = 0;
   out_8221376313792984867[203] = 0;
   out_8221376313792984867[204] = 0;
   out_8221376313792984867[205] = 0;
   out_8221376313792984867[206] = 0;
   out_8221376313792984867[207] = 0;
   out_8221376313792984867[208] = 0;
   out_8221376313792984867[209] = 1;
   out_8221376313792984867[210] = 0;
   out_8221376313792984867[211] = 0;
   out_8221376313792984867[212] = 0;
   out_8221376313792984867[213] = 0;
   out_8221376313792984867[214] = 0;
   out_8221376313792984867[215] = 0;
   out_8221376313792984867[216] = 0;
   out_8221376313792984867[217] = 0;
   out_8221376313792984867[218] = 0;
   out_8221376313792984867[219] = 0;
   out_8221376313792984867[220] = 0;
   out_8221376313792984867[221] = 0;
   out_8221376313792984867[222] = 0;
   out_8221376313792984867[223] = 0;
   out_8221376313792984867[224] = 0;
   out_8221376313792984867[225] = 0;
   out_8221376313792984867[226] = 0;
   out_8221376313792984867[227] = 0;
   out_8221376313792984867[228] = 1;
   out_8221376313792984867[229] = 0;
   out_8221376313792984867[230] = 0;
   out_8221376313792984867[231] = 0;
   out_8221376313792984867[232] = 0;
   out_8221376313792984867[233] = 0;
   out_8221376313792984867[234] = 0;
   out_8221376313792984867[235] = 0;
   out_8221376313792984867[236] = 0;
   out_8221376313792984867[237] = 0;
   out_8221376313792984867[238] = 0;
   out_8221376313792984867[239] = 0;
   out_8221376313792984867[240] = 0;
   out_8221376313792984867[241] = 0;
   out_8221376313792984867[242] = 0;
   out_8221376313792984867[243] = 0;
   out_8221376313792984867[244] = 0;
   out_8221376313792984867[245] = 0;
   out_8221376313792984867[246] = 0;
   out_8221376313792984867[247] = 1;
   out_8221376313792984867[248] = 0;
   out_8221376313792984867[249] = 0;
   out_8221376313792984867[250] = 0;
   out_8221376313792984867[251] = 0;
   out_8221376313792984867[252] = 0;
   out_8221376313792984867[253] = 0;
   out_8221376313792984867[254] = 0;
   out_8221376313792984867[255] = 0;
   out_8221376313792984867[256] = 0;
   out_8221376313792984867[257] = 0;
   out_8221376313792984867[258] = 0;
   out_8221376313792984867[259] = 0;
   out_8221376313792984867[260] = 0;
   out_8221376313792984867[261] = 0;
   out_8221376313792984867[262] = 0;
   out_8221376313792984867[263] = 0;
   out_8221376313792984867[264] = 0;
   out_8221376313792984867[265] = 0;
   out_8221376313792984867[266] = 1;
   out_8221376313792984867[267] = 0;
   out_8221376313792984867[268] = 0;
   out_8221376313792984867[269] = 0;
   out_8221376313792984867[270] = 0;
   out_8221376313792984867[271] = 0;
   out_8221376313792984867[272] = 0;
   out_8221376313792984867[273] = 0;
   out_8221376313792984867[274] = 0;
   out_8221376313792984867[275] = 0;
   out_8221376313792984867[276] = 0;
   out_8221376313792984867[277] = 0;
   out_8221376313792984867[278] = 0;
   out_8221376313792984867[279] = 0;
   out_8221376313792984867[280] = 0;
   out_8221376313792984867[281] = 0;
   out_8221376313792984867[282] = 0;
   out_8221376313792984867[283] = 0;
   out_8221376313792984867[284] = 0;
   out_8221376313792984867[285] = 1;
   out_8221376313792984867[286] = 0;
   out_8221376313792984867[287] = 0;
   out_8221376313792984867[288] = 0;
   out_8221376313792984867[289] = 0;
   out_8221376313792984867[290] = 0;
   out_8221376313792984867[291] = 0;
   out_8221376313792984867[292] = 0;
   out_8221376313792984867[293] = 0;
   out_8221376313792984867[294] = 0;
   out_8221376313792984867[295] = 0;
   out_8221376313792984867[296] = 0;
   out_8221376313792984867[297] = 0;
   out_8221376313792984867[298] = 0;
   out_8221376313792984867[299] = 0;
   out_8221376313792984867[300] = 0;
   out_8221376313792984867[301] = 0;
   out_8221376313792984867[302] = 0;
   out_8221376313792984867[303] = 0;
   out_8221376313792984867[304] = 1;
   out_8221376313792984867[305] = 0;
   out_8221376313792984867[306] = 0;
   out_8221376313792984867[307] = 0;
   out_8221376313792984867[308] = 0;
   out_8221376313792984867[309] = 0;
   out_8221376313792984867[310] = 0;
   out_8221376313792984867[311] = 0;
   out_8221376313792984867[312] = 0;
   out_8221376313792984867[313] = 0;
   out_8221376313792984867[314] = 0;
   out_8221376313792984867[315] = 0;
   out_8221376313792984867[316] = 0;
   out_8221376313792984867[317] = 0;
   out_8221376313792984867[318] = 0;
   out_8221376313792984867[319] = 0;
   out_8221376313792984867[320] = 0;
   out_8221376313792984867[321] = 0;
   out_8221376313792984867[322] = 0;
   out_8221376313792984867[323] = 1;
}
void h_4(double *state, double *unused, double *out_7512970159079020892) {
   out_7512970159079020892[0] = state[6] + state[9];
   out_7512970159079020892[1] = state[7] + state[10];
   out_7512970159079020892[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_698693047126132527) {
   out_698693047126132527[0] = 0;
   out_698693047126132527[1] = 0;
   out_698693047126132527[2] = 0;
   out_698693047126132527[3] = 0;
   out_698693047126132527[4] = 0;
   out_698693047126132527[5] = 0;
   out_698693047126132527[6] = 1;
   out_698693047126132527[7] = 0;
   out_698693047126132527[8] = 0;
   out_698693047126132527[9] = 1;
   out_698693047126132527[10] = 0;
   out_698693047126132527[11] = 0;
   out_698693047126132527[12] = 0;
   out_698693047126132527[13] = 0;
   out_698693047126132527[14] = 0;
   out_698693047126132527[15] = 0;
   out_698693047126132527[16] = 0;
   out_698693047126132527[17] = 0;
   out_698693047126132527[18] = 0;
   out_698693047126132527[19] = 0;
   out_698693047126132527[20] = 0;
   out_698693047126132527[21] = 0;
   out_698693047126132527[22] = 0;
   out_698693047126132527[23] = 0;
   out_698693047126132527[24] = 0;
   out_698693047126132527[25] = 1;
   out_698693047126132527[26] = 0;
   out_698693047126132527[27] = 0;
   out_698693047126132527[28] = 1;
   out_698693047126132527[29] = 0;
   out_698693047126132527[30] = 0;
   out_698693047126132527[31] = 0;
   out_698693047126132527[32] = 0;
   out_698693047126132527[33] = 0;
   out_698693047126132527[34] = 0;
   out_698693047126132527[35] = 0;
   out_698693047126132527[36] = 0;
   out_698693047126132527[37] = 0;
   out_698693047126132527[38] = 0;
   out_698693047126132527[39] = 0;
   out_698693047126132527[40] = 0;
   out_698693047126132527[41] = 0;
   out_698693047126132527[42] = 0;
   out_698693047126132527[43] = 0;
   out_698693047126132527[44] = 1;
   out_698693047126132527[45] = 0;
   out_698693047126132527[46] = 0;
   out_698693047126132527[47] = 1;
   out_698693047126132527[48] = 0;
   out_698693047126132527[49] = 0;
   out_698693047126132527[50] = 0;
   out_698693047126132527[51] = 0;
   out_698693047126132527[52] = 0;
   out_698693047126132527[53] = 0;
}
void h_10(double *state, double *unused, double *out_6422679790916561236) {
   out_6422679790916561236[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6422679790916561236[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6422679790916561236[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4658569367636697608) {
   out_4658569367636697608[0] = 0;
   out_4658569367636697608[1] = 9.8100000000000005*cos(state[1]);
   out_4658569367636697608[2] = 0;
   out_4658569367636697608[3] = 0;
   out_4658569367636697608[4] = -state[8];
   out_4658569367636697608[5] = state[7];
   out_4658569367636697608[6] = 0;
   out_4658569367636697608[7] = state[5];
   out_4658569367636697608[8] = -state[4];
   out_4658569367636697608[9] = 0;
   out_4658569367636697608[10] = 0;
   out_4658569367636697608[11] = 0;
   out_4658569367636697608[12] = 1;
   out_4658569367636697608[13] = 0;
   out_4658569367636697608[14] = 0;
   out_4658569367636697608[15] = 1;
   out_4658569367636697608[16] = 0;
   out_4658569367636697608[17] = 0;
   out_4658569367636697608[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4658569367636697608[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4658569367636697608[20] = 0;
   out_4658569367636697608[21] = state[8];
   out_4658569367636697608[22] = 0;
   out_4658569367636697608[23] = -state[6];
   out_4658569367636697608[24] = -state[5];
   out_4658569367636697608[25] = 0;
   out_4658569367636697608[26] = state[3];
   out_4658569367636697608[27] = 0;
   out_4658569367636697608[28] = 0;
   out_4658569367636697608[29] = 0;
   out_4658569367636697608[30] = 0;
   out_4658569367636697608[31] = 1;
   out_4658569367636697608[32] = 0;
   out_4658569367636697608[33] = 0;
   out_4658569367636697608[34] = 1;
   out_4658569367636697608[35] = 0;
   out_4658569367636697608[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4658569367636697608[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4658569367636697608[38] = 0;
   out_4658569367636697608[39] = -state[7];
   out_4658569367636697608[40] = state[6];
   out_4658569367636697608[41] = 0;
   out_4658569367636697608[42] = state[4];
   out_4658569367636697608[43] = -state[3];
   out_4658569367636697608[44] = 0;
   out_4658569367636697608[45] = 0;
   out_4658569367636697608[46] = 0;
   out_4658569367636697608[47] = 0;
   out_4658569367636697608[48] = 0;
   out_4658569367636697608[49] = 0;
   out_4658569367636697608[50] = 1;
   out_4658569367636697608[51] = 0;
   out_4658569367636697608[52] = 0;
   out_4658569367636697608[53] = 1;
}
void h_13(double *state, double *unused, double *out_7592318235637912656) {
   out_7592318235637912656[0] = state[3];
   out_7592318235637912656[1] = state[4];
   out_7592318235637912656[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3910966872458465328) {
   out_3910966872458465328[0] = 0;
   out_3910966872458465328[1] = 0;
   out_3910966872458465328[2] = 0;
   out_3910966872458465328[3] = 1;
   out_3910966872458465328[4] = 0;
   out_3910966872458465328[5] = 0;
   out_3910966872458465328[6] = 0;
   out_3910966872458465328[7] = 0;
   out_3910966872458465328[8] = 0;
   out_3910966872458465328[9] = 0;
   out_3910966872458465328[10] = 0;
   out_3910966872458465328[11] = 0;
   out_3910966872458465328[12] = 0;
   out_3910966872458465328[13] = 0;
   out_3910966872458465328[14] = 0;
   out_3910966872458465328[15] = 0;
   out_3910966872458465328[16] = 0;
   out_3910966872458465328[17] = 0;
   out_3910966872458465328[18] = 0;
   out_3910966872458465328[19] = 0;
   out_3910966872458465328[20] = 0;
   out_3910966872458465328[21] = 0;
   out_3910966872458465328[22] = 1;
   out_3910966872458465328[23] = 0;
   out_3910966872458465328[24] = 0;
   out_3910966872458465328[25] = 0;
   out_3910966872458465328[26] = 0;
   out_3910966872458465328[27] = 0;
   out_3910966872458465328[28] = 0;
   out_3910966872458465328[29] = 0;
   out_3910966872458465328[30] = 0;
   out_3910966872458465328[31] = 0;
   out_3910966872458465328[32] = 0;
   out_3910966872458465328[33] = 0;
   out_3910966872458465328[34] = 0;
   out_3910966872458465328[35] = 0;
   out_3910966872458465328[36] = 0;
   out_3910966872458465328[37] = 0;
   out_3910966872458465328[38] = 0;
   out_3910966872458465328[39] = 0;
   out_3910966872458465328[40] = 0;
   out_3910966872458465328[41] = 1;
   out_3910966872458465328[42] = 0;
   out_3910966872458465328[43] = 0;
   out_3910966872458465328[44] = 0;
   out_3910966872458465328[45] = 0;
   out_3910966872458465328[46] = 0;
   out_3910966872458465328[47] = 0;
   out_3910966872458465328[48] = 0;
   out_3910966872458465328[49] = 0;
   out_3910966872458465328[50] = 0;
   out_3910966872458465328[51] = 0;
   out_3910966872458465328[52] = 0;
   out_3910966872458465328[53] = 0;
}
void h_14(double *state, double *unused, double *out_2616018567407793546) {
   out_2616018567407793546[0] = state[6];
   out_2616018567407793546[1] = state[7];
   out_2616018567407793546[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4661933903465617056) {
   out_4661933903465617056[0] = 0;
   out_4661933903465617056[1] = 0;
   out_4661933903465617056[2] = 0;
   out_4661933903465617056[3] = 0;
   out_4661933903465617056[4] = 0;
   out_4661933903465617056[5] = 0;
   out_4661933903465617056[6] = 1;
   out_4661933903465617056[7] = 0;
   out_4661933903465617056[8] = 0;
   out_4661933903465617056[9] = 0;
   out_4661933903465617056[10] = 0;
   out_4661933903465617056[11] = 0;
   out_4661933903465617056[12] = 0;
   out_4661933903465617056[13] = 0;
   out_4661933903465617056[14] = 0;
   out_4661933903465617056[15] = 0;
   out_4661933903465617056[16] = 0;
   out_4661933903465617056[17] = 0;
   out_4661933903465617056[18] = 0;
   out_4661933903465617056[19] = 0;
   out_4661933903465617056[20] = 0;
   out_4661933903465617056[21] = 0;
   out_4661933903465617056[22] = 0;
   out_4661933903465617056[23] = 0;
   out_4661933903465617056[24] = 0;
   out_4661933903465617056[25] = 1;
   out_4661933903465617056[26] = 0;
   out_4661933903465617056[27] = 0;
   out_4661933903465617056[28] = 0;
   out_4661933903465617056[29] = 0;
   out_4661933903465617056[30] = 0;
   out_4661933903465617056[31] = 0;
   out_4661933903465617056[32] = 0;
   out_4661933903465617056[33] = 0;
   out_4661933903465617056[34] = 0;
   out_4661933903465617056[35] = 0;
   out_4661933903465617056[36] = 0;
   out_4661933903465617056[37] = 0;
   out_4661933903465617056[38] = 0;
   out_4661933903465617056[39] = 0;
   out_4661933903465617056[40] = 0;
   out_4661933903465617056[41] = 0;
   out_4661933903465617056[42] = 0;
   out_4661933903465617056[43] = 0;
   out_4661933903465617056[44] = 1;
   out_4661933903465617056[45] = 0;
   out_4661933903465617056[46] = 0;
   out_4661933903465617056[47] = 0;
   out_4661933903465617056[48] = 0;
   out_4661933903465617056[49] = 0;
   out_4661933903465617056[50] = 0;
   out_4661933903465617056[51] = 0;
   out_4661933903465617056[52] = 0;
   out_4661933903465617056[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1302882686935522561) {
  err_fun(nom_x, delta_x, out_1302882686935522561);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_9056716141039600519) {
  inv_err_fun(nom_x, true_x, out_9056716141039600519);
}
void pose_H_mod_fun(double *state, double *out_55467954928580080) {
  H_mod_fun(state, out_55467954928580080);
}
void pose_f_fun(double *state, double dt, double *out_1954087496247120441) {
  f_fun(state,  dt, out_1954087496247120441);
}
void pose_F_fun(double *state, double dt, double *out_8221376313792984867) {
  F_fun(state,  dt, out_8221376313792984867);
}
void pose_h_4(double *state, double *unused, double *out_7512970159079020892) {
  h_4(state, unused, out_7512970159079020892);
}
void pose_H_4(double *state, double *unused, double *out_698693047126132527) {
  H_4(state, unused, out_698693047126132527);
}
void pose_h_10(double *state, double *unused, double *out_6422679790916561236) {
  h_10(state, unused, out_6422679790916561236);
}
void pose_H_10(double *state, double *unused, double *out_4658569367636697608) {
  H_10(state, unused, out_4658569367636697608);
}
void pose_h_13(double *state, double *unused, double *out_7592318235637912656) {
  h_13(state, unused, out_7592318235637912656);
}
void pose_H_13(double *state, double *unused, double *out_3910966872458465328) {
  H_13(state, unused, out_3910966872458465328);
}
void pose_h_14(double *state, double *unused, double *out_2616018567407793546) {
  h_14(state, unused, out_2616018567407793546);
}
void pose_H_14(double *state, double *unused, double *out_4661933903465617056) {
  H_14(state, unused, out_4661933903465617056);
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
