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
void err_fun(double *nom_x, double *delta_x, double *out_222088853381432014) {
   out_222088853381432014[0] = delta_x[0] + nom_x[0];
   out_222088853381432014[1] = delta_x[1] + nom_x[1];
   out_222088853381432014[2] = delta_x[2] + nom_x[2];
   out_222088853381432014[3] = delta_x[3] + nom_x[3];
   out_222088853381432014[4] = delta_x[4] + nom_x[4];
   out_222088853381432014[5] = delta_x[5] + nom_x[5];
   out_222088853381432014[6] = delta_x[6] + nom_x[6];
   out_222088853381432014[7] = delta_x[7] + nom_x[7];
   out_222088853381432014[8] = delta_x[8] + nom_x[8];
   out_222088853381432014[9] = delta_x[9] + nom_x[9];
   out_222088853381432014[10] = delta_x[10] + nom_x[10];
   out_222088853381432014[11] = delta_x[11] + nom_x[11];
   out_222088853381432014[12] = delta_x[12] + nom_x[12];
   out_222088853381432014[13] = delta_x[13] + nom_x[13];
   out_222088853381432014[14] = delta_x[14] + nom_x[14];
   out_222088853381432014[15] = delta_x[15] + nom_x[15];
   out_222088853381432014[16] = delta_x[16] + nom_x[16];
   out_222088853381432014[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5630858664606890930) {
   out_5630858664606890930[0] = -nom_x[0] + true_x[0];
   out_5630858664606890930[1] = -nom_x[1] + true_x[1];
   out_5630858664606890930[2] = -nom_x[2] + true_x[2];
   out_5630858664606890930[3] = -nom_x[3] + true_x[3];
   out_5630858664606890930[4] = -nom_x[4] + true_x[4];
   out_5630858664606890930[5] = -nom_x[5] + true_x[5];
   out_5630858664606890930[6] = -nom_x[6] + true_x[6];
   out_5630858664606890930[7] = -nom_x[7] + true_x[7];
   out_5630858664606890930[8] = -nom_x[8] + true_x[8];
   out_5630858664606890930[9] = -nom_x[9] + true_x[9];
   out_5630858664606890930[10] = -nom_x[10] + true_x[10];
   out_5630858664606890930[11] = -nom_x[11] + true_x[11];
   out_5630858664606890930[12] = -nom_x[12] + true_x[12];
   out_5630858664606890930[13] = -nom_x[13] + true_x[13];
   out_5630858664606890930[14] = -nom_x[14] + true_x[14];
   out_5630858664606890930[15] = -nom_x[15] + true_x[15];
   out_5630858664606890930[16] = -nom_x[16] + true_x[16];
   out_5630858664606890930[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2006534566727409158) {
   out_2006534566727409158[0] = 1.0;
   out_2006534566727409158[1] = 0.0;
   out_2006534566727409158[2] = 0.0;
   out_2006534566727409158[3] = 0.0;
   out_2006534566727409158[4] = 0.0;
   out_2006534566727409158[5] = 0.0;
   out_2006534566727409158[6] = 0.0;
   out_2006534566727409158[7] = 0.0;
   out_2006534566727409158[8] = 0.0;
   out_2006534566727409158[9] = 0.0;
   out_2006534566727409158[10] = 0.0;
   out_2006534566727409158[11] = 0.0;
   out_2006534566727409158[12] = 0.0;
   out_2006534566727409158[13] = 0.0;
   out_2006534566727409158[14] = 0.0;
   out_2006534566727409158[15] = 0.0;
   out_2006534566727409158[16] = 0.0;
   out_2006534566727409158[17] = 0.0;
   out_2006534566727409158[18] = 0.0;
   out_2006534566727409158[19] = 1.0;
   out_2006534566727409158[20] = 0.0;
   out_2006534566727409158[21] = 0.0;
   out_2006534566727409158[22] = 0.0;
   out_2006534566727409158[23] = 0.0;
   out_2006534566727409158[24] = 0.0;
   out_2006534566727409158[25] = 0.0;
   out_2006534566727409158[26] = 0.0;
   out_2006534566727409158[27] = 0.0;
   out_2006534566727409158[28] = 0.0;
   out_2006534566727409158[29] = 0.0;
   out_2006534566727409158[30] = 0.0;
   out_2006534566727409158[31] = 0.0;
   out_2006534566727409158[32] = 0.0;
   out_2006534566727409158[33] = 0.0;
   out_2006534566727409158[34] = 0.0;
   out_2006534566727409158[35] = 0.0;
   out_2006534566727409158[36] = 0.0;
   out_2006534566727409158[37] = 0.0;
   out_2006534566727409158[38] = 1.0;
   out_2006534566727409158[39] = 0.0;
   out_2006534566727409158[40] = 0.0;
   out_2006534566727409158[41] = 0.0;
   out_2006534566727409158[42] = 0.0;
   out_2006534566727409158[43] = 0.0;
   out_2006534566727409158[44] = 0.0;
   out_2006534566727409158[45] = 0.0;
   out_2006534566727409158[46] = 0.0;
   out_2006534566727409158[47] = 0.0;
   out_2006534566727409158[48] = 0.0;
   out_2006534566727409158[49] = 0.0;
   out_2006534566727409158[50] = 0.0;
   out_2006534566727409158[51] = 0.0;
   out_2006534566727409158[52] = 0.0;
   out_2006534566727409158[53] = 0.0;
   out_2006534566727409158[54] = 0.0;
   out_2006534566727409158[55] = 0.0;
   out_2006534566727409158[56] = 0.0;
   out_2006534566727409158[57] = 1.0;
   out_2006534566727409158[58] = 0.0;
   out_2006534566727409158[59] = 0.0;
   out_2006534566727409158[60] = 0.0;
   out_2006534566727409158[61] = 0.0;
   out_2006534566727409158[62] = 0.0;
   out_2006534566727409158[63] = 0.0;
   out_2006534566727409158[64] = 0.0;
   out_2006534566727409158[65] = 0.0;
   out_2006534566727409158[66] = 0.0;
   out_2006534566727409158[67] = 0.0;
   out_2006534566727409158[68] = 0.0;
   out_2006534566727409158[69] = 0.0;
   out_2006534566727409158[70] = 0.0;
   out_2006534566727409158[71] = 0.0;
   out_2006534566727409158[72] = 0.0;
   out_2006534566727409158[73] = 0.0;
   out_2006534566727409158[74] = 0.0;
   out_2006534566727409158[75] = 0.0;
   out_2006534566727409158[76] = 1.0;
   out_2006534566727409158[77] = 0.0;
   out_2006534566727409158[78] = 0.0;
   out_2006534566727409158[79] = 0.0;
   out_2006534566727409158[80] = 0.0;
   out_2006534566727409158[81] = 0.0;
   out_2006534566727409158[82] = 0.0;
   out_2006534566727409158[83] = 0.0;
   out_2006534566727409158[84] = 0.0;
   out_2006534566727409158[85] = 0.0;
   out_2006534566727409158[86] = 0.0;
   out_2006534566727409158[87] = 0.0;
   out_2006534566727409158[88] = 0.0;
   out_2006534566727409158[89] = 0.0;
   out_2006534566727409158[90] = 0.0;
   out_2006534566727409158[91] = 0.0;
   out_2006534566727409158[92] = 0.0;
   out_2006534566727409158[93] = 0.0;
   out_2006534566727409158[94] = 0.0;
   out_2006534566727409158[95] = 1.0;
   out_2006534566727409158[96] = 0.0;
   out_2006534566727409158[97] = 0.0;
   out_2006534566727409158[98] = 0.0;
   out_2006534566727409158[99] = 0.0;
   out_2006534566727409158[100] = 0.0;
   out_2006534566727409158[101] = 0.0;
   out_2006534566727409158[102] = 0.0;
   out_2006534566727409158[103] = 0.0;
   out_2006534566727409158[104] = 0.0;
   out_2006534566727409158[105] = 0.0;
   out_2006534566727409158[106] = 0.0;
   out_2006534566727409158[107] = 0.0;
   out_2006534566727409158[108] = 0.0;
   out_2006534566727409158[109] = 0.0;
   out_2006534566727409158[110] = 0.0;
   out_2006534566727409158[111] = 0.0;
   out_2006534566727409158[112] = 0.0;
   out_2006534566727409158[113] = 0.0;
   out_2006534566727409158[114] = 1.0;
   out_2006534566727409158[115] = 0.0;
   out_2006534566727409158[116] = 0.0;
   out_2006534566727409158[117] = 0.0;
   out_2006534566727409158[118] = 0.0;
   out_2006534566727409158[119] = 0.0;
   out_2006534566727409158[120] = 0.0;
   out_2006534566727409158[121] = 0.0;
   out_2006534566727409158[122] = 0.0;
   out_2006534566727409158[123] = 0.0;
   out_2006534566727409158[124] = 0.0;
   out_2006534566727409158[125] = 0.0;
   out_2006534566727409158[126] = 0.0;
   out_2006534566727409158[127] = 0.0;
   out_2006534566727409158[128] = 0.0;
   out_2006534566727409158[129] = 0.0;
   out_2006534566727409158[130] = 0.0;
   out_2006534566727409158[131] = 0.0;
   out_2006534566727409158[132] = 0.0;
   out_2006534566727409158[133] = 1.0;
   out_2006534566727409158[134] = 0.0;
   out_2006534566727409158[135] = 0.0;
   out_2006534566727409158[136] = 0.0;
   out_2006534566727409158[137] = 0.0;
   out_2006534566727409158[138] = 0.0;
   out_2006534566727409158[139] = 0.0;
   out_2006534566727409158[140] = 0.0;
   out_2006534566727409158[141] = 0.0;
   out_2006534566727409158[142] = 0.0;
   out_2006534566727409158[143] = 0.0;
   out_2006534566727409158[144] = 0.0;
   out_2006534566727409158[145] = 0.0;
   out_2006534566727409158[146] = 0.0;
   out_2006534566727409158[147] = 0.0;
   out_2006534566727409158[148] = 0.0;
   out_2006534566727409158[149] = 0.0;
   out_2006534566727409158[150] = 0.0;
   out_2006534566727409158[151] = 0.0;
   out_2006534566727409158[152] = 1.0;
   out_2006534566727409158[153] = 0.0;
   out_2006534566727409158[154] = 0.0;
   out_2006534566727409158[155] = 0.0;
   out_2006534566727409158[156] = 0.0;
   out_2006534566727409158[157] = 0.0;
   out_2006534566727409158[158] = 0.0;
   out_2006534566727409158[159] = 0.0;
   out_2006534566727409158[160] = 0.0;
   out_2006534566727409158[161] = 0.0;
   out_2006534566727409158[162] = 0.0;
   out_2006534566727409158[163] = 0.0;
   out_2006534566727409158[164] = 0.0;
   out_2006534566727409158[165] = 0.0;
   out_2006534566727409158[166] = 0.0;
   out_2006534566727409158[167] = 0.0;
   out_2006534566727409158[168] = 0.0;
   out_2006534566727409158[169] = 0.0;
   out_2006534566727409158[170] = 0.0;
   out_2006534566727409158[171] = 1.0;
   out_2006534566727409158[172] = 0.0;
   out_2006534566727409158[173] = 0.0;
   out_2006534566727409158[174] = 0.0;
   out_2006534566727409158[175] = 0.0;
   out_2006534566727409158[176] = 0.0;
   out_2006534566727409158[177] = 0.0;
   out_2006534566727409158[178] = 0.0;
   out_2006534566727409158[179] = 0.0;
   out_2006534566727409158[180] = 0.0;
   out_2006534566727409158[181] = 0.0;
   out_2006534566727409158[182] = 0.0;
   out_2006534566727409158[183] = 0.0;
   out_2006534566727409158[184] = 0.0;
   out_2006534566727409158[185] = 0.0;
   out_2006534566727409158[186] = 0.0;
   out_2006534566727409158[187] = 0.0;
   out_2006534566727409158[188] = 0.0;
   out_2006534566727409158[189] = 0.0;
   out_2006534566727409158[190] = 1.0;
   out_2006534566727409158[191] = 0.0;
   out_2006534566727409158[192] = 0.0;
   out_2006534566727409158[193] = 0.0;
   out_2006534566727409158[194] = 0.0;
   out_2006534566727409158[195] = 0.0;
   out_2006534566727409158[196] = 0.0;
   out_2006534566727409158[197] = 0.0;
   out_2006534566727409158[198] = 0.0;
   out_2006534566727409158[199] = 0.0;
   out_2006534566727409158[200] = 0.0;
   out_2006534566727409158[201] = 0.0;
   out_2006534566727409158[202] = 0.0;
   out_2006534566727409158[203] = 0.0;
   out_2006534566727409158[204] = 0.0;
   out_2006534566727409158[205] = 0.0;
   out_2006534566727409158[206] = 0.0;
   out_2006534566727409158[207] = 0.0;
   out_2006534566727409158[208] = 0.0;
   out_2006534566727409158[209] = 1.0;
   out_2006534566727409158[210] = 0.0;
   out_2006534566727409158[211] = 0.0;
   out_2006534566727409158[212] = 0.0;
   out_2006534566727409158[213] = 0.0;
   out_2006534566727409158[214] = 0.0;
   out_2006534566727409158[215] = 0.0;
   out_2006534566727409158[216] = 0.0;
   out_2006534566727409158[217] = 0.0;
   out_2006534566727409158[218] = 0.0;
   out_2006534566727409158[219] = 0.0;
   out_2006534566727409158[220] = 0.0;
   out_2006534566727409158[221] = 0.0;
   out_2006534566727409158[222] = 0.0;
   out_2006534566727409158[223] = 0.0;
   out_2006534566727409158[224] = 0.0;
   out_2006534566727409158[225] = 0.0;
   out_2006534566727409158[226] = 0.0;
   out_2006534566727409158[227] = 0.0;
   out_2006534566727409158[228] = 1.0;
   out_2006534566727409158[229] = 0.0;
   out_2006534566727409158[230] = 0.0;
   out_2006534566727409158[231] = 0.0;
   out_2006534566727409158[232] = 0.0;
   out_2006534566727409158[233] = 0.0;
   out_2006534566727409158[234] = 0.0;
   out_2006534566727409158[235] = 0.0;
   out_2006534566727409158[236] = 0.0;
   out_2006534566727409158[237] = 0.0;
   out_2006534566727409158[238] = 0.0;
   out_2006534566727409158[239] = 0.0;
   out_2006534566727409158[240] = 0.0;
   out_2006534566727409158[241] = 0.0;
   out_2006534566727409158[242] = 0.0;
   out_2006534566727409158[243] = 0.0;
   out_2006534566727409158[244] = 0.0;
   out_2006534566727409158[245] = 0.0;
   out_2006534566727409158[246] = 0.0;
   out_2006534566727409158[247] = 1.0;
   out_2006534566727409158[248] = 0.0;
   out_2006534566727409158[249] = 0.0;
   out_2006534566727409158[250] = 0.0;
   out_2006534566727409158[251] = 0.0;
   out_2006534566727409158[252] = 0.0;
   out_2006534566727409158[253] = 0.0;
   out_2006534566727409158[254] = 0.0;
   out_2006534566727409158[255] = 0.0;
   out_2006534566727409158[256] = 0.0;
   out_2006534566727409158[257] = 0.0;
   out_2006534566727409158[258] = 0.0;
   out_2006534566727409158[259] = 0.0;
   out_2006534566727409158[260] = 0.0;
   out_2006534566727409158[261] = 0.0;
   out_2006534566727409158[262] = 0.0;
   out_2006534566727409158[263] = 0.0;
   out_2006534566727409158[264] = 0.0;
   out_2006534566727409158[265] = 0.0;
   out_2006534566727409158[266] = 1.0;
   out_2006534566727409158[267] = 0.0;
   out_2006534566727409158[268] = 0.0;
   out_2006534566727409158[269] = 0.0;
   out_2006534566727409158[270] = 0.0;
   out_2006534566727409158[271] = 0.0;
   out_2006534566727409158[272] = 0.0;
   out_2006534566727409158[273] = 0.0;
   out_2006534566727409158[274] = 0.0;
   out_2006534566727409158[275] = 0.0;
   out_2006534566727409158[276] = 0.0;
   out_2006534566727409158[277] = 0.0;
   out_2006534566727409158[278] = 0.0;
   out_2006534566727409158[279] = 0.0;
   out_2006534566727409158[280] = 0.0;
   out_2006534566727409158[281] = 0.0;
   out_2006534566727409158[282] = 0.0;
   out_2006534566727409158[283] = 0.0;
   out_2006534566727409158[284] = 0.0;
   out_2006534566727409158[285] = 1.0;
   out_2006534566727409158[286] = 0.0;
   out_2006534566727409158[287] = 0.0;
   out_2006534566727409158[288] = 0.0;
   out_2006534566727409158[289] = 0.0;
   out_2006534566727409158[290] = 0.0;
   out_2006534566727409158[291] = 0.0;
   out_2006534566727409158[292] = 0.0;
   out_2006534566727409158[293] = 0.0;
   out_2006534566727409158[294] = 0.0;
   out_2006534566727409158[295] = 0.0;
   out_2006534566727409158[296] = 0.0;
   out_2006534566727409158[297] = 0.0;
   out_2006534566727409158[298] = 0.0;
   out_2006534566727409158[299] = 0.0;
   out_2006534566727409158[300] = 0.0;
   out_2006534566727409158[301] = 0.0;
   out_2006534566727409158[302] = 0.0;
   out_2006534566727409158[303] = 0.0;
   out_2006534566727409158[304] = 1.0;
   out_2006534566727409158[305] = 0.0;
   out_2006534566727409158[306] = 0.0;
   out_2006534566727409158[307] = 0.0;
   out_2006534566727409158[308] = 0.0;
   out_2006534566727409158[309] = 0.0;
   out_2006534566727409158[310] = 0.0;
   out_2006534566727409158[311] = 0.0;
   out_2006534566727409158[312] = 0.0;
   out_2006534566727409158[313] = 0.0;
   out_2006534566727409158[314] = 0.0;
   out_2006534566727409158[315] = 0.0;
   out_2006534566727409158[316] = 0.0;
   out_2006534566727409158[317] = 0.0;
   out_2006534566727409158[318] = 0.0;
   out_2006534566727409158[319] = 0.0;
   out_2006534566727409158[320] = 0.0;
   out_2006534566727409158[321] = 0.0;
   out_2006534566727409158[322] = 0.0;
   out_2006534566727409158[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5095165263511672541) {
   out_5095165263511672541[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5095165263511672541[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5095165263511672541[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5095165263511672541[3] = dt*state[12] + state[3];
   out_5095165263511672541[4] = dt*state[13] + state[4];
   out_5095165263511672541[5] = dt*state[14] + state[5];
   out_5095165263511672541[6] = state[6];
   out_5095165263511672541[7] = state[7];
   out_5095165263511672541[8] = state[8];
   out_5095165263511672541[9] = state[9];
   out_5095165263511672541[10] = state[10];
   out_5095165263511672541[11] = state[11];
   out_5095165263511672541[12] = state[12];
   out_5095165263511672541[13] = state[13];
   out_5095165263511672541[14] = state[14];
   out_5095165263511672541[15] = state[15];
   out_5095165263511672541[16] = state[16];
   out_5095165263511672541[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2477765371920509155) {
   out_2477765371920509155[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2477765371920509155[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2477765371920509155[2] = 0;
   out_2477765371920509155[3] = 0;
   out_2477765371920509155[4] = 0;
   out_2477765371920509155[5] = 0;
   out_2477765371920509155[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2477765371920509155[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2477765371920509155[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2477765371920509155[9] = 0;
   out_2477765371920509155[10] = 0;
   out_2477765371920509155[11] = 0;
   out_2477765371920509155[12] = 0;
   out_2477765371920509155[13] = 0;
   out_2477765371920509155[14] = 0;
   out_2477765371920509155[15] = 0;
   out_2477765371920509155[16] = 0;
   out_2477765371920509155[17] = 0;
   out_2477765371920509155[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2477765371920509155[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2477765371920509155[20] = 0;
   out_2477765371920509155[21] = 0;
   out_2477765371920509155[22] = 0;
   out_2477765371920509155[23] = 0;
   out_2477765371920509155[24] = 0;
   out_2477765371920509155[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2477765371920509155[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2477765371920509155[27] = 0;
   out_2477765371920509155[28] = 0;
   out_2477765371920509155[29] = 0;
   out_2477765371920509155[30] = 0;
   out_2477765371920509155[31] = 0;
   out_2477765371920509155[32] = 0;
   out_2477765371920509155[33] = 0;
   out_2477765371920509155[34] = 0;
   out_2477765371920509155[35] = 0;
   out_2477765371920509155[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2477765371920509155[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2477765371920509155[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2477765371920509155[39] = 0;
   out_2477765371920509155[40] = 0;
   out_2477765371920509155[41] = 0;
   out_2477765371920509155[42] = 0;
   out_2477765371920509155[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2477765371920509155[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2477765371920509155[45] = 0;
   out_2477765371920509155[46] = 0;
   out_2477765371920509155[47] = 0;
   out_2477765371920509155[48] = 0;
   out_2477765371920509155[49] = 0;
   out_2477765371920509155[50] = 0;
   out_2477765371920509155[51] = 0;
   out_2477765371920509155[52] = 0;
   out_2477765371920509155[53] = 0;
   out_2477765371920509155[54] = 0;
   out_2477765371920509155[55] = 0;
   out_2477765371920509155[56] = 0;
   out_2477765371920509155[57] = 1;
   out_2477765371920509155[58] = 0;
   out_2477765371920509155[59] = 0;
   out_2477765371920509155[60] = 0;
   out_2477765371920509155[61] = 0;
   out_2477765371920509155[62] = 0;
   out_2477765371920509155[63] = 0;
   out_2477765371920509155[64] = 0;
   out_2477765371920509155[65] = 0;
   out_2477765371920509155[66] = dt;
   out_2477765371920509155[67] = 0;
   out_2477765371920509155[68] = 0;
   out_2477765371920509155[69] = 0;
   out_2477765371920509155[70] = 0;
   out_2477765371920509155[71] = 0;
   out_2477765371920509155[72] = 0;
   out_2477765371920509155[73] = 0;
   out_2477765371920509155[74] = 0;
   out_2477765371920509155[75] = 0;
   out_2477765371920509155[76] = 1;
   out_2477765371920509155[77] = 0;
   out_2477765371920509155[78] = 0;
   out_2477765371920509155[79] = 0;
   out_2477765371920509155[80] = 0;
   out_2477765371920509155[81] = 0;
   out_2477765371920509155[82] = 0;
   out_2477765371920509155[83] = 0;
   out_2477765371920509155[84] = 0;
   out_2477765371920509155[85] = dt;
   out_2477765371920509155[86] = 0;
   out_2477765371920509155[87] = 0;
   out_2477765371920509155[88] = 0;
   out_2477765371920509155[89] = 0;
   out_2477765371920509155[90] = 0;
   out_2477765371920509155[91] = 0;
   out_2477765371920509155[92] = 0;
   out_2477765371920509155[93] = 0;
   out_2477765371920509155[94] = 0;
   out_2477765371920509155[95] = 1;
   out_2477765371920509155[96] = 0;
   out_2477765371920509155[97] = 0;
   out_2477765371920509155[98] = 0;
   out_2477765371920509155[99] = 0;
   out_2477765371920509155[100] = 0;
   out_2477765371920509155[101] = 0;
   out_2477765371920509155[102] = 0;
   out_2477765371920509155[103] = 0;
   out_2477765371920509155[104] = dt;
   out_2477765371920509155[105] = 0;
   out_2477765371920509155[106] = 0;
   out_2477765371920509155[107] = 0;
   out_2477765371920509155[108] = 0;
   out_2477765371920509155[109] = 0;
   out_2477765371920509155[110] = 0;
   out_2477765371920509155[111] = 0;
   out_2477765371920509155[112] = 0;
   out_2477765371920509155[113] = 0;
   out_2477765371920509155[114] = 1;
   out_2477765371920509155[115] = 0;
   out_2477765371920509155[116] = 0;
   out_2477765371920509155[117] = 0;
   out_2477765371920509155[118] = 0;
   out_2477765371920509155[119] = 0;
   out_2477765371920509155[120] = 0;
   out_2477765371920509155[121] = 0;
   out_2477765371920509155[122] = 0;
   out_2477765371920509155[123] = 0;
   out_2477765371920509155[124] = 0;
   out_2477765371920509155[125] = 0;
   out_2477765371920509155[126] = 0;
   out_2477765371920509155[127] = 0;
   out_2477765371920509155[128] = 0;
   out_2477765371920509155[129] = 0;
   out_2477765371920509155[130] = 0;
   out_2477765371920509155[131] = 0;
   out_2477765371920509155[132] = 0;
   out_2477765371920509155[133] = 1;
   out_2477765371920509155[134] = 0;
   out_2477765371920509155[135] = 0;
   out_2477765371920509155[136] = 0;
   out_2477765371920509155[137] = 0;
   out_2477765371920509155[138] = 0;
   out_2477765371920509155[139] = 0;
   out_2477765371920509155[140] = 0;
   out_2477765371920509155[141] = 0;
   out_2477765371920509155[142] = 0;
   out_2477765371920509155[143] = 0;
   out_2477765371920509155[144] = 0;
   out_2477765371920509155[145] = 0;
   out_2477765371920509155[146] = 0;
   out_2477765371920509155[147] = 0;
   out_2477765371920509155[148] = 0;
   out_2477765371920509155[149] = 0;
   out_2477765371920509155[150] = 0;
   out_2477765371920509155[151] = 0;
   out_2477765371920509155[152] = 1;
   out_2477765371920509155[153] = 0;
   out_2477765371920509155[154] = 0;
   out_2477765371920509155[155] = 0;
   out_2477765371920509155[156] = 0;
   out_2477765371920509155[157] = 0;
   out_2477765371920509155[158] = 0;
   out_2477765371920509155[159] = 0;
   out_2477765371920509155[160] = 0;
   out_2477765371920509155[161] = 0;
   out_2477765371920509155[162] = 0;
   out_2477765371920509155[163] = 0;
   out_2477765371920509155[164] = 0;
   out_2477765371920509155[165] = 0;
   out_2477765371920509155[166] = 0;
   out_2477765371920509155[167] = 0;
   out_2477765371920509155[168] = 0;
   out_2477765371920509155[169] = 0;
   out_2477765371920509155[170] = 0;
   out_2477765371920509155[171] = 1;
   out_2477765371920509155[172] = 0;
   out_2477765371920509155[173] = 0;
   out_2477765371920509155[174] = 0;
   out_2477765371920509155[175] = 0;
   out_2477765371920509155[176] = 0;
   out_2477765371920509155[177] = 0;
   out_2477765371920509155[178] = 0;
   out_2477765371920509155[179] = 0;
   out_2477765371920509155[180] = 0;
   out_2477765371920509155[181] = 0;
   out_2477765371920509155[182] = 0;
   out_2477765371920509155[183] = 0;
   out_2477765371920509155[184] = 0;
   out_2477765371920509155[185] = 0;
   out_2477765371920509155[186] = 0;
   out_2477765371920509155[187] = 0;
   out_2477765371920509155[188] = 0;
   out_2477765371920509155[189] = 0;
   out_2477765371920509155[190] = 1;
   out_2477765371920509155[191] = 0;
   out_2477765371920509155[192] = 0;
   out_2477765371920509155[193] = 0;
   out_2477765371920509155[194] = 0;
   out_2477765371920509155[195] = 0;
   out_2477765371920509155[196] = 0;
   out_2477765371920509155[197] = 0;
   out_2477765371920509155[198] = 0;
   out_2477765371920509155[199] = 0;
   out_2477765371920509155[200] = 0;
   out_2477765371920509155[201] = 0;
   out_2477765371920509155[202] = 0;
   out_2477765371920509155[203] = 0;
   out_2477765371920509155[204] = 0;
   out_2477765371920509155[205] = 0;
   out_2477765371920509155[206] = 0;
   out_2477765371920509155[207] = 0;
   out_2477765371920509155[208] = 0;
   out_2477765371920509155[209] = 1;
   out_2477765371920509155[210] = 0;
   out_2477765371920509155[211] = 0;
   out_2477765371920509155[212] = 0;
   out_2477765371920509155[213] = 0;
   out_2477765371920509155[214] = 0;
   out_2477765371920509155[215] = 0;
   out_2477765371920509155[216] = 0;
   out_2477765371920509155[217] = 0;
   out_2477765371920509155[218] = 0;
   out_2477765371920509155[219] = 0;
   out_2477765371920509155[220] = 0;
   out_2477765371920509155[221] = 0;
   out_2477765371920509155[222] = 0;
   out_2477765371920509155[223] = 0;
   out_2477765371920509155[224] = 0;
   out_2477765371920509155[225] = 0;
   out_2477765371920509155[226] = 0;
   out_2477765371920509155[227] = 0;
   out_2477765371920509155[228] = 1;
   out_2477765371920509155[229] = 0;
   out_2477765371920509155[230] = 0;
   out_2477765371920509155[231] = 0;
   out_2477765371920509155[232] = 0;
   out_2477765371920509155[233] = 0;
   out_2477765371920509155[234] = 0;
   out_2477765371920509155[235] = 0;
   out_2477765371920509155[236] = 0;
   out_2477765371920509155[237] = 0;
   out_2477765371920509155[238] = 0;
   out_2477765371920509155[239] = 0;
   out_2477765371920509155[240] = 0;
   out_2477765371920509155[241] = 0;
   out_2477765371920509155[242] = 0;
   out_2477765371920509155[243] = 0;
   out_2477765371920509155[244] = 0;
   out_2477765371920509155[245] = 0;
   out_2477765371920509155[246] = 0;
   out_2477765371920509155[247] = 1;
   out_2477765371920509155[248] = 0;
   out_2477765371920509155[249] = 0;
   out_2477765371920509155[250] = 0;
   out_2477765371920509155[251] = 0;
   out_2477765371920509155[252] = 0;
   out_2477765371920509155[253] = 0;
   out_2477765371920509155[254] = 0;
   out_2477765371920509155[255] = 0;
   out_2477765371920509155[256] = 0;
   out_2477765371920509155[257] = 0;
   out_2477765371920509155[258] = 0;
   out_2477765371920509155[259] = 0;
   out_2477765371920509155[260] = 0;
   out_2477765371920509155[261] = 0;
   out_2477765371920509155[262] = 0;
   out_2477765371920509155[263] = 0;
   out_2477765371920509155[264] = 0;
   out_2477765371920509155[265] = 0;
   out_2477765371920509155[266] = 1;
   out_2477765371920509155[267] = 0;
   out_2477765371920509155[268] = 0;
   out_2477765371920509155[269] = 0;
   out_2477765371920509155[270] = 0;
   out_2477765371920509155[271] = 0;
   out_2477765371920509155[272] = 0;
   out_2477765371920509155[273] = 0;
   out_2477765371920509155[274] = 0;
   out_2477765371920509155[275] = 0;
   out_2477765371920509155[276] = 0;
   out_2477765371920509155[277] = 0;
   out_2477765371920509155[278] = 0;
   out_2477765371920509155[279] = 0;
   out_2477765371920509155[280] = 0;
   out_2477765371920509155[281] = 0;
   out_2477765371920509155[282] = 0;
   out_2477765371920509155[283] = 0;
   out_2477765371920509155[284] = 0;
   out_2477765371920509155[285] = 1;
   out_2477765371920509155[286] = 0;
   out_2477765371920509155[287] = 0;
   out_2477765371920509155[288] = 0;
   out_2477765371920509155[289] = 0;
   out_2477765371920509155[290] = 0;
   out_2477765371920509155[291] = 0;
   out_2477765371920509155[292] = 0;
   out_2477765371920509155[293] = 0;
   out_2477765371920509155[294] = 0;
   out_2477765371920509155[295] = 0;
   out_2477765371920509155[296] = 0;
   out_2477765371920509155[297] = 0;
   out_2477765371920509155[298] = 0;
   out_2477765371920509155[299] = 0;
   out_2477765371920509155[300] = 0;
   out_2477765371920509155[301] = 0;
   out_2477765371920509155[302] = 0;
   out_2477765371920509155[303] = 0;
   out_2477765371920509155[304] = 1;
   out_2477765371920509155[305] = 0;
   out_2477765371920509155[306] = 0;
   out_2477765371920509155[307] = 0;
   out_2477765371920509155[308] = 0;
   out_2477765371920509155[309] = 0;
   out_2477765371920509155[310] = 0;
   out_2477765371920509155[311] = 0;
   out_2477765371920509155[312] = 0;
   out_2477765371920509155[313] = 0;
   out_2477765371920509155[314] = 0;
   out_2477765371920509155[315] = 0;
   out_2477765371920509155[316] = 0;
   out_2477765371920509155[317] = 0;
   out_2477765371920509155[318] = 0;
   out_2477765371920509155[319] = 0;
   out_2477765371920509155[320] = 0;
   out_2477765371920509155[321] = 0;
   out_2477765371920509155[322] = 0;
   out_2477765371920509155[323] = 1;
}
void h_4(double *state, double *unused, double *out_1444896257330890962) {
   out_1444896257330890962[0] = state[6] + state[9];
   out_1444896257330890962[1] = state[7] + state[10];
   out_1444896257330890962[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1765272643116498414) {
   out_1765272643116498414[0] = 0;
   out_1765272643116498414[1] = 0;
   out_1765272643116498414[2] = 0;
   out_1765272643116498414[3] = 0;
   out_1765272643116498414[4] = 0;
   out_1765272643116498414[5] = 0;
   out_1765272643116498414[6] = 1;
   out_1765272643116498414[7] = 0;
   out_1765272643116498414[8] = 0;
   out_1765272643116498414[9] = 1;
   out_1765272643116498414[10] = 0;
   out_1765272643116498414[11] = 0;
   out_1765272643116498414[12] = 0;
   out_1765272643116498414[13] = 0;
   out_1765272643116498414[14] = 0;
   out_1765272643116498414[15] = 0;
   out_1765272643116498414[16] = 0;
   out_1765272643116498414[17] = 0;
   out_1765272643116498414[18] = 0;
   out_1765272643116498414[19] = 0;
   out_1765272643116498414[20] = 0;
   out_1765272643116498414[21] = 0;
   out_1765272643116498414[22] = 0;
   out_1765272643116498414[23] = 0;
   out_1765272643116498414[24] = 0;
   out_1765272643116498414[25] = 1;
   out_1765272643116498414[26] = 0;
   out_1765272643116498414[27] = 0;
   out_1765272643116498414[28] = 1;
   out_1765272643116498414[29] = 0;
   out_1765272643116498414[30] = 0;
   out_1765272643116498414[31] = 0;
   out_1765272643116498414[32] = 0;
   out_1765272643116498414[33] = 0;
   out_1765272643116498414[34] = 0;
   out_1765272643116498414[35] = 0;
   out_1765272643116498414[36] = 0;
   out_1765272643116498414[37] = 0;
   out_1765272643116498414[38] = 0;
   out_1765272643116498414[39] = 0;
   out_1765272643116498414[40] = 0;
   out_1765272643116498414[41] = 0;
   out_1765272643116498414[42] = 0;
   out_1765272643116498414[43] = 0;
   out_1765272643116498414[44] = 1;
   out_1765272643116498414[45] = 0;
   out_1765272643116498414[46] = 0;
   out_1765272643116498414[47] = 1;
   out_1765272643116498414[48] = 0;
   out_1765272643116498414[49] = 0;
   out_1765272643116498414[50] = 0;
   out_1765272643116498414[51] = 0;
   out_1765272643116498414[52] = 0;
   out_1765272643116498414[53] = 0;
}
void h_10(double *state, double *unused, double *out_4705883844394877317) {
   out_4705883844394877317[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4705883844394877317[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4705883844394877317[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3449679283445996015) {
   out_3449679283445996015[0] = 0;
   out_3449679283445996015[1] = 9.8100000000000005*cos(state[1]);
   out_3449679283445996015[2] = 0;
   out_3449679283445996015[3] = 0;
   out_3449679283445996015[4] = -state[8];
   out_3449679283445996015[5] = state[7];
   out_3449679283445996015[6] = 0;
   out_3449679283445996015[7] = state[5];
   out_3449679283445996015[8] = -state[4];
   out_3449679283445996015[9] = 0;
   out_3449679283445996015[10] = 0;
   out_3449679283445996015[11] = 0;
   out_3449679283445996015[12] = 1;
   out_3449679283445996015[13] = 0;
   out_3449679283445996015[14] = 0;
   out_3449679283445996015[15] = 1;
   out_3449679283445996015[16] = 0;
   out_3449679283445996015[17] = 0;
   out_3449679283445996015[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3449679283445996015[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3449679283445996015[20] = 0;
   out_3449679283445996015[21] = state[8];
   out_3449679283445996015[22] = 0;
   out_3449679283445996015[23] = -state[6];
   out_3449679283445996015[24] = -state[5];
   out_3449679283445996015[25] = 0;
   out_3449679283445996015[26] = state[3];
   out_3449679283445996015[27] = 0;
   out_3449679283445996015[28] = 0;
   out_3449679283445996015[29] = 0;
   out_3449679283445996015[30] = 0;
   out_3449679283445996015[31] = 1;
   out_3449679283445996015[32] = 0;
   out_3449679283445996015[33] = 0;
   out_3449679283445996015[34] = 1;
   out_3449679283445996015[35] = 0;
   out_3449679283445996015[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3449679283445996015[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3449679283445996015[38] = 0;
   out_3449679283445996015[39] = -state[7];
   out_3449679283445996015[40] = state[6];
   out_3449679283445996015[41] = 0;
   out_3449679283445996015[42] = state[4];
   out_3449679283445996015[43] = -state[3];
   out_3449679283445996015[44] = 0;
   out_3449679283445996015[45] = 0;
   out_3449679283445996015[46] = 0;
   out_3449679283445996015[47] = 0;
   out_3449679283445996015[48] = 0;
   out_3449679283445996015[49] = 0;
   out_3449679283445996015[50] = 1;
   out_3449679283445996015[51] = 0;
   out_3449679283445996015[52] = 0;
   out_3449679283445996015[53] = 1;
}
void h_13(double *state, double *unused, double *out_8700690102558969181) {
   out_8700690102558969181[0] = state[3];
   out_8700690102558969181[1] = state[4];
   out_8700690102558969181[2] = state[5];
}
void H_13(double *state, double *unused, double *out_9070840222276352273) {
   out_9070840222276352273[0] = 0;
   out_9070840222276352273[1] = 0;
   out_9070840222276352273[2] = 0;
   out_9070840222276352273[3] = 1;
   out_9070840222276352273[4] = 0;
   out_9070840222276352273[5] = 0;
   out_9070840222276352273[6] = 0;
   out_9070840222276352273[7] = 0;
   out_9070840222276352273[8] = 0;
   out_9070840222276352273[9] = 0;
   out_9070840222276352273[10] = 0;
   out_9070840222276352273[11] = 0;
   out_9070840222276352273[12] = 0;
   out_9070840222276352273[13] = 0;
   out_9070840222276352273[14] = 0;
   out_9070840222276352273[15] = 0;
   out_9070840222276352273[16] = 0;
   out_9070840222276352273[17] = 0;
   out_9070840222276352273[18] = 0;
   out_9070840222276352273[19] = 0;
   out_9070840222276352273[20] = 0;
   out_9070840222276352273[21] = 0;
   out_9070840222276352273[22] = 1;
   out_9070840222276352273[23] = 0;
   out_9070840222276352273[24] = 0;
   out_9070840222276352273[25] = 0;
   out_9070840222276352273[26] = 0;
   out_9070840222276352273[27] = 0;
   out_9070840222276352273[28] = 0;
   out_9070840222276352273[29] = 0;
   out_9070840222276352273[30] = 0;
   out_9070840222276352273[31] = 0;
   out_9070840222276352273[32] = 0;
   out_9070840222276352273[33] = 0;
   out_9070840222276352273[34] = 0;
   out_9070840222276352273[35] = 0;
   out_9070840222276352273[36] = 0;
   out_9070840222276352273[37] = 0;
   out_9070840222276352273[38] = 0;
   out_9070840222276352273[39] = 0;
   out_9070840222276352273[40] = 0;
   out_9070840222276352273[41] = 1;
   out_9070840222276352273[42] = 0;
   out_9070840222276352273[43] = 0;
   out_9070840222276352273[44] = 0;
   out_9070840222276352273[45] = 0;
   out_9070840222276352273[46] = 0;
   out_9070840222276352273[47] = 0;
   out_9070840222276352273[48] = 0;
   out_9070840222276352273[49] = 0;
   out_9070840222276352273[50] = 0;
   out_9070840222276352273[51] = 0;
   out_9070840222276352273[52] = 0;
   out_9070840222276352273[53] = 0;
}
void h_14(double *state, double *unused, double *out_8343334072151647811) {
   out_8343334072151647811[0] = state[6];
   out_8343334072151647811[1] = state[7];
   out_8343334072151647811[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1317515789178873882) {
   out_1317515789178873882[0] = 0;
   out_1317515789178873882[1] = 0;
   out_1317515789178873882[2] = 0;
   out_1317515789178873882[3] = 0;
   out_1317515789178873882[4] = 0;
   out_1317515789178873882[5] = 0;
   out_1317515789178873882[6] = 1;
   out_1317515789178873882[7] = 0;
   out_1317515789178873882[8] = 0;
   out_1317515789178873882[9] = 0;
   out_1317515789178873882[10] = 0;
   out_1317515789178873882[11] = 0;
   out_1317515789178873882[12] = 0;
   out_1317515789178873882[13] = 0;
   out_1317515789178873882[14] = 0;
   out_1317515789178873882[15] = 0;
   out_1317515789178873882[16] = 0;
   out_1317515789178873882[17] = 0;
   out_1317515789178873882[18] = 0;
   out_1317515789178873882[19] = 0;
   out_1317515789178873882[20] = 0;
   out_1317515789178873882[21] = 0;
   out_1317515789178873882[22] = 0;
   out_1317515789178873882[23] = 0;
   out_1317515789178873882[24] = 0;
   out_1317515789178873882[25] = 1;
   out_1317515789178873882[26] = 0;
   out_1317515789178873882[27] = 0;
   out_1317515789178873882[28] = 0;
   out_1317515789178873882[29] = 0;
   out_1317515789178873882[30] = 0;
   out_1317515789178873882[31] = 0;
   out_1317515789178873882[32] = 0;
   out_1317515789178873882[33] = 0;
   out_1317515789178873882[34] = 0;
   out_1317515789178873882[35] = 0;
   out_1317515789178873882[36] = 0;
   out_1317515789178873882[37] = 0;
   out_1317515789178873882[38] = 0;
   out_1317515789178873882[39] = 0;
   out_1317515789178873882[40] = 0;
   out_1317515789178873882[41] = 0;
   out_1317515789178873882[42] = 0;
   out_1317515789178873882[43] = 0;
   out_1317515789178873882[44] = 1;
   out_1317515789178873882[45] = 0;
   out_1317515789178873882[46] = 0;
   out_1317515789178873882[47] = 0;
   out_1317515789178873882[48] = 0;
   out_1317515789178873882[49] = 0;
   out_1317515789178873882[50] = 0;
   out_1317515789178873882[51] = 0;
   out_1317515789178873882[52] = 0;
   out_1317515789178873882[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_222088853381432014) {
  err_fun(nom_x, delta_x, out_222088853381432014);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5630858664606890930) {
  inv_err_fun(nom_x, true_x, out_5630858664606890930);
}
void pose_H_mod_fun(double *state, double *out_2006534566727409158) {
  H_mod_fun(state, out_2006534566727409158);
}
void pose_f_fun(double *state, double dt, double *out_5095165263511672541) {
  f_fun(state,  dt, out_5095165263511672541);
}
void pose_F_fun(double *state, double dt, double *out_2477765371920509155) {
  F_fun(state,  dt, out_2477765371920509155);
}
void pose_h_4(double *state, double *unused, double *out_1444896257330890962) {
  h_4(state, unused, out_1444896257330890962);
}
void pose_H_4(double *state, double *unused, double *out_1765272643116498414) {
  H_4(state, unused, out_1765272643116498414);
}
void pose_h_10(double *state, double *unused, double *out_4705883844394877317) {
  h_10(state, unused, out_4705883844394877317);
}
void pose_H_10(double *state, double *unused, double *out_3449679283445996015) {
  H_10(state, unused, out_3449679283445996015);
}
void pose_h_13(double *state, double *unused, double *out_8700690102558969181) {
  h_13(state, unused, out_8700690102558969181);
}
void pose_H_13(double *state, double *unused, double *out_9070840222276352273) {
  H_13(state, unused, out_9070840222276352273);
}
void pose_h_14(double *state, double *unused, double *out_8343334072151647811) {
  h_14(state, unused, out_8343334072151647811);
}
void pose_H_14(double *state, double *unused, double *out_1317515789178873882) {
  H_14(state, unused, out_1317515789178873882);
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
