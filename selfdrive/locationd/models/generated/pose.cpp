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
void err_fun(double *nom_x, double *delta_x, double *out_8794951023692473693) {
   out_8794951023692473693[0] = delta_x[0] + nom_x[0];
   out_8794951023692473693[1] = delta_x[1] + nom_x[1];
   out_8794951023692473693[2] = delta_x[2] + nom_x[2];
   out_8794951023692473693[3] = delta_x[3] + nom_x[3];
   out_8794951023692473693[4] = delta_x[4] + nom_x[4];
   out_8794951023692473693[5] = delta_x[5] + nom_x[5];
   out_8794951023692473693[6] = delta_x[6] + nom_x[6];
   out_8794951023692473693[7] = delta_x[7] + nom_x[7];
   out_8794951023692473693[8] = delta_x[8] + nom_x[8];
   out_8794951023692473693[9] = delta_x[9] + nom_x[9];
   out_8794951023692473693[10] = delta_x[10] + nom_x[10];
   out_8794951023692473693[11] = delta_x[11] + nom_x[11];
   out_8794951023692473693[12] = delta_x[12] + nom_x[12];
   out_8794951023692473693[13] = delta_x[13] + nom_x[13];
   out_8794951023692473693[14] = delta_x[14] + nom_x[14];
   out_8794951023692473693[15] = delta_x[15] + nom_x[15];
   out_8794951023692473693[16] = delta_x[16] + nom_x[16];
   out_8794951023692473693[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_147609790886506349) {
   out_147609790886506349[0] = -nom_x[0] + true_x[0];
   out_147609790886506349[1] = -nom_x[1] + true_x[1];
   out_147609790886506349[2] = -nom_x[2] + true_x[2];
   out_147609790886506349[3] = -nom_x[3] + true_x[3];
   out_147609790886506349[4] = -nom_x[4] + true_x[4];
   out_147609790886506349[5] = -nom_x[5] + true_x[5];
   out_147609790886506349[6] = -nom_x[6] + true_x[6];
   out_147609790886506349[7] = -nom_x[7] + true_x[7];
   out_147609790886506349[8] = -nom_x[8] + true_x[8];
   out_147609790886506349[9] = -nom_x[9] + true_x[9];
   out_147609790886506349[10] = -nom_x[10] + true_x[10];
   out_147609790886506349[11] = -nom_x[11] + true_x[11];
   out_147609790886506349[12] = -nom_x[12] + true_x[12];
   out_147609790886506349[13] = -nom_x[13] + true_x[13];
   out_147609790886506349[14] = -nom_x[14] + true_x[14];
   out_147609790886506349[15] = -nom_x[15] + true_x[15];
   out_147609790886506349[16] = -nom_x[16] + true_x[16];
   out_147609790886506349[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4713269657164746226) {
   out_4713269657164746226[0] = 1.0;
   out_4713269657164746226[1] = 0.0;
   out_4713269657164746226[2] = 0.0;
   out_4713269657164746226[3] = 0.0;
   out_4713269657164746226[4] = 0.0;
   out_4713269657164746226[5] = 0.0;
   out_4713269657164746226[6] = 0.0;
   out_4713269657164746226[7] = 0.0;
   out_4713269657164746226[8] = 0.0;
   out_4713269657164746226[9] = 0.0;
   out_4713269657164746226[10] = 0.0;
   out_4713269657164746226[11] = 0.0;
   out_4713269657164746226[12] = 0.0;
   out_4713269657164746226[13] = 0.0;
   out_4713269657164746226[14] = 0.0;
   out_4713269657164746226[15] = 0.0;
   out_4713269657164746226[16] = 0.0;
   out_4713269657164746226[17] = 0.0;
   out_4713269657164746226[18] = 0.0;
   out_4713269657164746226[19] = 1.0;
   out_4713269657164746226[20] = 0.0;
   out_4713269657164746226[21] = 0.0;
   out_4713269657164746226[22] = 0.0;
   out_4713269657164746226[23] = 0.0;
   out_4713269657164746226[24] = 0.0;
   out_4713269657164746226[25] = 0.0;
   out_4713269657164746226[26] = 0.0;
   out_4713269657164746226[27] = 0.0;
   out_4713269657164746226[28] = 0.0;
   out_4713269657164746226[29] = 0.0;
   out_4713269657164746226[30] = 0.0;
   out_4713269657164746226[31] = 0.0;
   out_4713269657164746226[32] = 0.0;
   out_4713269657164746226[33] = 0.0;
   out_4713269657164746226[34] = 0.0;
   out_4713269657164746226[35] = 0.0;
   out_4713269657164746226[36] = 0.0;
   out_4713269657164746226[37] = 0.0;
   out_4713269657164746226[38] = 1.0;
   out_4713269657164746226[39] = 0.0;
   out_4713269657164746226[40] = 0.0;
   out_4713269657164746226[41] = 0.0;
   out_4713269657164746226[42] = 0.0;
   out_4713269657164746226[43] = 0.0;
   out_4713269657164746226[44] = 0.0;
   out_4713269657164746226[45] = 0.0;
   out_4713269657164746226[46] = 0.0;
   out_4713269657164746226[47] = 0.0;
   out_4713269657164746226[48] = 0.0;
   out_4713269657164746226[49] = 0.0;
   out_4713269657164746226[50] = 0.0;
   out_4713269657164746226[51] = 0.0;
   out_4713269657164746226[52] = 0.0;
   out_4713269657164746226[53] = 0.0;
   out_4713269657164746226[54] = 0.0;
   out_4713269657164746226[55] = 0.0;
   out_4713269657164746226[56] = 0.0;
   out_4713269657164746226[57] = 1.0;
   out_4713269657164746226[58] = 0.0;
   out_4713269657164746226[59] = 0.0;
   out_4713269657164746226[60] = 0.0;
   out_4713269657164746226[61] = 0.0;
   out_4713269657164746226[62] = 0.0;
   out_4713269657164746226[63] = 0.0;
   out_4713269657164746226[64] = 0.0;
   out_4713269657164746226[65] = 0.0;
   out_4713269657164746226[66] = 0.0;
   out_4713269657164746226[67] = 0.0;
   out_4713269657164746226[68] = 0.0;
   out_4713269657164746226[69] = 0.0;
   out_4713269657164746226[70] = 0.0;
   out_4713269657164746226[71] = 0.0;
   out_4713269657164746226[72] = 0.0;
   out_4713269657164746226[73] = 0.0;
   out_4713269657164746226[74] = 0.0;
   out_4713269657164746226[75] = 0.0;
   out_4713269657164746226[76] = 1.0;
   out_4713269657164746226[77] = 0.0;
   out_4713269657164746226[78] = 0.0;
   out_4713269657164746226[79] = 0.0;
   out_4713269657164746226[80] = 0.0;
   out_4713269657164746226[81] = 0.0;
   out_4713269657164746226[82] = 0.0;
   out_4713269657164746226[83] = 0.0;
   out_4713269657164746226[84] = 0.0;
   out_4713269657164746226[85] = 0.0;
   out_4713269657164746226[86] = 0.0;
   out_4713269657164746226[87] = 0.0;
   out_4713269657164746226[88] = 0.0;
   out_4713269657164746226[89] = 0.0;
   out_4713269657164746226[90] = 0.0;
   out_4713269657164746226[91] = 0.0;
   out_4713269657164746226[92] = 0.0;
   out_4713269657164746226[93] = 0.0;
   out_4713269657164746226[94] = 0.0;
   out_4713269657164746226[95] = 1.0;
   out_4713269657164746226[96] = 0.0;
   out_4713269657164746226[97] = 0.0;
   out_4713269657164746226[98] = 0.0;
   out_4713269657164746226[99] = 0.0;
   out_4713269657164746226[100] = 0.0;
   out_4713269657164746226[101] = 0.0;
   out_4713269657164746226[102] = 0.0;
   out_4713269657164746226[103] = 0.0;
   out_4713269657164746226[104] = 0.0;
   out_4713269657164746226[105] = 0.0;
   out_4713269657164746226[106] = 0.0;
   out_4713269657164746226[107] = 0.0;
   out_4713269657164746226[108] = 0.0;
   out_4713269657164746226[109] = 0.0;
   out_4713269657164746226[110] = 0.0;
   out_4713269657164746226[111] = 0.0;
   out_4713269657164746226[112] = 0.0;
   out_4713269657164746226[113] = 0.0;
   out_4713269657164746226[114] = 1.0;
   out_4713269657164746226[115] = 0.0;
   out_4713269657164746226[116] = 0.0;
   out_4713269657164746226[117] = 0.0;
   out_4713269657164746226[118] = 0.0;
   out_4713269657164746226[119] = 0.0;
   out_4713269657164746226[120] = 0.0;
   out_4713269657164746226[121] = 0.0;
   out_4713269657164746226[122] = 0.0;
   out_4713269657164746226[123] = 0.0;
   out_4713269657164746226[124] = 0.0;
   out_4713269657164746226[125] = 0.0;
   out_4713269657164746226[126] = 0.0;
   out_4713269657164746226[127] = 0.0;
   out_4713269657164746226[128] = 0.0;
   out_4713269657164746226[129] = 0.0;
   out_4713269657164746226[130] = 0.0;
   out_4713269657164746226[131] = 0.0;
   out_4713269657164746226[132] = 0.0;
   out_4713269657164746226[133] = 1.0;
   out_4713269657164746226[134] = 0.0;
   out_4713269657164746226[135] = 0.0;
   out_4713269657164746226[136] = 0.0;
   out_4713269657164746226[137] = 0.0;
   out_4713269657164746226[138] = 0.0;
   out_4713269657164746226[139] = 0.0;
   out_4713269657164746226[140] = 0.0;
   out_4713269657164746226[141] = 0.0;
   out_4713269657164746226[142] = 0.0;
   out_4713269657164746226[143] = 0.0;
   out_4713269657164746226[144] = 0.0;
   out_4713269657164746226[145] = 0.0;
   out_4713269657164746226[146] = 0.0;
   out_4713269657164746226[147] = 0.0;
   out_4713269657164746226[148] = 0.0;
   out_4713269657164746226[149] = 0.0;
   out_4713269657164746226[150] = 0.0;
   out_4713269657164746226[151] = 0.0;
   out_4713269657164746226[152] = 1.0;
   out_4713269657164746226[153] = 0.0;
   out_4713269657164746226[154] = 0.0;
   out_4713269657164746226[155] = 0.0;
   out_4713269657164746226[156] = 0.0;
   out_4713269657164746226[157] = 0.0;
   out_4713269657164746226[158] = 0.0;
   out_4713269657164746226[159] = 0.0;
   out_4713269657164746226[160] = 0.0;
   out_4713269657164746226[161] = 0.0;
   out_4713269657164746226[162] = 0.0;
   out_4713269657164746226[163] = 0.0;
   out_4713269657164746226[164] = 0.0;
   out_4713269657164746226[165] = 0.0;
   out_4713269657164746226[166] = 0.0;
   out_4713269657164746226[167] = 0.0;
   out_4713269657164746226[168] = 0.0;
   out_4713269657164746226[169] = 0.0;
   out_4713269657164746226[170] = 0.0;
   out_4713269657164746226[171] = 1.0;
   out_4713269657164746226[172] = 0.0;
   out_4713269657164746226[173] = 0.0;
   out_4713269657164746226[174] = 0.0;
   out_4713269657164746226[175] = 0.0;
   out_4713269657164746226[176] = 0.0;
   out_4713269657164746226[177] = 0.0;
   out_4713269657164746226[178] = 0.0;
   out_4713269657164746226[179] = 0.0;
   out_4713269657164746226[180] = 0.0;
   out_4713269657164746226[181] = 0.0;
   out_4713269657164746226[182] = 0.0;
   out_4713269657164746226[183] = 0.0;
   out_4713269657164746226[184] = 0.0;
   out_4713269657164746226[185] = 0.0;
   out_4713269657164746226[186] = 0.0;
   out_4713269657164746226[187] = 0.0;
   out_4713269657164746226[188] = 0.0;
   out_4713269657164746226[189] = 0.0;
   out_4713269657164746226[190] = 1.0;
   out_4713269657164746226[191] = 0.0;
   out_4713269657164746226[192] = 0.0;
   out_4713269657164746226[193] = 0.0;
   out_4713269657164746226[194] = 0.0;
   out_4713269657164746226[195] = 0.0;
   out_4713269657164746226[196] = 0.0;
   out_4713269657164746226[197] = 0.0;
   out_4713269657164746226[198] = 0.0;
   out_4713269657164746226[199] = 0.0;
   out_4713269657164746226[200] = 0.0;
   out_4713269657164746226[201] = 0.0;
   out_4713269657164746226[202] = 0.0;
   out_4713269657164746226[203] = 0.0;
   out_4713269657164746226[204] = 0.0;
   out_4713269657164746226[205] = 0.0;
   out_4713269657164746226[206] = 0.0;
   out_4713269657164746226[207] = 0.0;
   out_4713269657164746226[208] = 0.0;
   out_4713269657164746226[209] = 1.0;
   out_4713269657164746226[210] = 0.0;
   out_4713269657164746226[211] = 0.0;
   out_4713269657164746226[212] = 0.0;
   out_4713269657164746226[213] = 0.0;
   out_4713269657164746226[214] = 0.0;
   out_4713269657164746226[215] = 0.0;
   out_4713269657164746226[216] = 0.0;
   out_4713269657164746226[217] = 0.0;
   out_4713269657164746226[218] = 0.0;
   out_4713269657164746226[219] = 0.0;
   out_4713269657164746226[220] = 0.0;
   out_4713269657164746226[221] = 0.0;
   out_4713269657164746226[222] = 0.0;
   out_4713269657164746226[223] = 0.0;
   out_4713269657164746226[224] = 0.0;
   out_4713269657164746226[225] = 0.0;
   out_4713269657164746226[226] = 0.0;
   out_4713269657164746226[227] = 0.0;
   out_4713269657164746226[228] = 1.0;
   out_4713269657164746226[229] = 0.0;
   out_4713269657164746226[230] = 0.0;
   out_4713269657164746226[231] = 0.0;
   out_4713269657164746226[232] = 0.0;
   out_4713269657164746226[233] = 0.0;
   out_4713269657164746226[234] = 0.0;
   out_4713269657164746226[235] = 0.0;
   out_4713269657164746226[236] = 0.0;
   out_4713269657164746226[237] = 0.0;
   out_4713269657164746226[238] = 0.0;
   out_4713269657164746226[239] = 0.0;
   out_4713269657164746226[240] = 0.0;
   out_4713269657164746226[241] = 0.0;
   out_4713269657164746226[242] = 0.0;
   out_4713269657164746226[243] = 0.0;
   out_4713269657164746226[244] = 0.0;
   out_4713269657164746226[245] = 0.0;
   out_4713269657164746226[246] = 0.0;
   out_4713269657164746226[247] = 1.0;
   out_4713269657164746226[248] = 0.0;
   out_4713269657164746226[249] = 0.0;
   out_4713269657164746226[250] = 0.0;
   out_4713269657164746226[251] = 0.0;
   out_4713269657164746226[252] = 0.0;
   out_4713269657164746226[253] = 0.0;
   out_4713269657164746226[254] = 0.0;
   out_4713269657164746226[255] = 0.0;
   out_4713269657164746226[256] = 0.0;
   out_4713269657164746226[257] = 0.0;
   out_4713269657164746226[258] = 0.0;
   out_4713269657164746226[259] = 0.0;
   out_4713269657164746226[260] = 0.0;
   out_4713269657164746226[261] = 0.0;
   out_4713269657164746226[262] = 0.0;
   out_4713269657164746226[263] = 0.0;
   out_4713269657164746226[264] = 0.0;
   out_4713269657164746226[265] = 0.0;
   out_4713269657164746226[266] = 1.0;
   out_4713269657164746226[267] = 0.0;
   out_4713269657164746226[268] = 0.0;
   out_4713269657164746226[269] = 0.0;
   out_4713269657164746226[270] = 0.0;
   out_4713269657164746226[271] = 0.0;
   out_4713269657164746226[272] = 0.0;
   out_4713269657164746226[273] = 0.0;
   out_4713269657164746226[274] = 0.0;
   out_4713269657164746226[275] = 0.0;
   out_4713269657164746226[276] = 0.0;
   out_4713269657164746226[277] = 0.0;
   out_4713269657164746226[278] = 0.0;
   out_4713269657164746226[279] = 0.0;
   out_4713269657164746226[280] = 0.0;
   out_4713269657164746226[281] = 0.0;
   out_4713269657164746226[282] = 0.0;
   out_4713269657164746226[283] = 0.0;
   out_4713269657164746226[284] = 0.0;
   out_4713269657164746226[285] = 1.0;
   out_4713269657164746226[286] = 0.0;
   out_4713269657164746226[287] = 0.0;
   out_4713269657164746226[288] = 0.0;
   out_4713269657164746226[289] = 0.0;
   out_4713269657164746226[290] = 0.0;
   out_4713269657164746226[291] = 0.0;
   out_4713269657164746226[292] = 0.0;
   out_4713269657164746226[293] = 0.0;
   out_4713269657164746226[294] = 0.0;
   out_4713269657164746226[295] = 0.0;
   out_4713269657164746226[296] = 0.0;
   out_4713269657164746226[297] = 0.0;
   out_4713269657164746226[298] = 0.0;
   out_4713269657164746226[299] = 0.0;
   out_4713269657164746226[300] = 0.0;
   out_4713269657164746226[301] = 0.0;
   out_4713269657164746226[302] = 0.0;
   out_4713269657164746226[303] = 0.0;
   out_4713269657164746226[304] = 1.0;
   out_4713269657164746226[305] = 0.0;
   out_4713269657164746226[306] = 0.0;
   out_4713269657164746226[307] = 0.0;
   out_4713269657164746226[308] = 0.0;
   out_4713269657164746226[309] = 0.0;
   out_4713269657164746226[310] = 0.0;
   out_4713269657164746226[311] = 0.0;
   out_4713269657164746226[312] = 0.0;
   out_4713269657164746226[313] = 0.0;
   out_4713269657164746226[314] = 0.0;
   out_4713269657164746226[315] = 0.0;
   out_4713269657164746226[316] = 0.0;
   out_4713269657164746226[317] = 0.0;
   out_4713269657164746226[318] = 0.0;
   out_4713269657164746226[319] = 0.0;
   out_4713269657164746226[320] = 0.0;
   out_4713269657164746226[321] = 0.0;
   out_4713269657164746226[322] = 0.0;
   out_4713269657164746226[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8307718287749749495) {
   out_8307718287749749495[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8307718287749749495[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8307718287749749495[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8307718287749749495[3] = dt*state[12] + state[3];
   out_8307718287749749495[4] = dt*state[13] + state[4];
   out_8307718287749749495[5] = dt*state[14] + state[5];
   out_8307718287749749495[6] = state[6];
   out_8307718287749749495[7] = state[7];
   out_8307718287749749495[8] = state[8];
   out_8307718287749749495[9] = state[9];
   out_8307718287749749495[10] = state[10];
   out_8307718287749749495[11] = state[11];
   out_8307718287749749495[12] = state[12];
   out_8307718287749749495[13] = state[13];
   out_8307718287749749495[14] = state[14];
   out_8307718287749749495[15] = state[15];
   out_8307718287749749495[16] = state[16];
   out_8307718287749749495[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2796913824456762059) {
   out_2796913824456762059[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2796913824456762059[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2796913824456762059[2] = 0;
   out_2796913824456762059[3] = 0;
   out_2796913824456762059[4] = 0;
   out_2796913824456762059[5] = 0;
   out_2796913824456762059[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2796913824456762059[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2796913824456762059[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2796913824456762059[9] = 0;
   out_2796913824456762059[10] = 0;
   out_2796913824456762059[11] = 0;
   out_2796913824456762059[12] = 0;
   out_2796913824456762059[13] = 0;
   out_2796913824456762059[14] = 0;
   out_2796913824456762059[15] = 0;
   out_2796913824456762059[16] = 0;
   out_2796913824456762059[17] = 0;
   out_2796913824456762059[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2796913824456762059[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2796913824456762059[20] = 0;
   out_2796913824456762059[21] = 0;
   out_2796913824456762059[22] = 0;
   out_2796913824456762059[23] = 0;
   out_2796913824456762059[24] = 0;
   out_2796913824456762059[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2796913824456762059[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2796913824456762059[27] = 0;
   out_2796913824456762059[28] = 0;
   out_2796913824456762059[29] = 0;
   out_2796913824456762059[30] = 0;
   out_2796913824456762059[31] = 0;
   out_2796913824456762059[32] = 0;
   out_2796913824456762059[33] = 0;
   out_2796913824456762059[34] = 0;
   out_2796913824456762059[35] = 0;
   out_2796913824456762059[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2796913824456762059[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2796913824456762059[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2796913824456762059[39] = 0;
   out_2796913824456762059[40] = 0;
   out_2796913824456762059[41] = 0;
   out_2796913824456762059[42] = 0;
   out_2796913824456762059[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2796913824456762059[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2796913824456762059[45] = 0;
   out_2796913824456762059[46] = 0;
   out_2796913824456762059[47] = 0;
   out_2796913824456762059[48] = 0;
   out_2796913824456762059[49] = 0;
   out_2796913824456762059[50] = 0;
   out_2796913824456762059[51] = 0;
   out_2796913824456762059[52] = 0;
   out_2796913824456762059[53] = 0;
   out_2796913824456762059[54] = 0;
   out_2796913824456762059[55] = 0;
   out_2796913824456762059[56] = 0;
   out_2796913824456762059[57] = 1;
   out_2796913824456762059[58] = 0;
   out_2796913824456762059[59] = 0;
   out_2796913824456762059[60] = 0;
   out_2796913824456762059[61] = 0;
   out_2796913824456762059[62] = 0;
   out_2796913824456762059[63] = 0;
   out_2796913824456762059[64] = 0;
   out_2796913824456762059[65] = 0;
   out_2796913824456762059[66] = dt;
   out_2796913824456762059[67] = 0;
   out_2796913824456762059[68] = 0;
   out_2796913824456762059[69] = 0;
   out_2796913824456762059[70] = 0;
   out_2796913824456762059[71] = 0;
   out_2796913824456762059[72] = 0;
   out_2796913824456762059[73] = 0;
   out_2796913824456762059[74] = 0;
   out_2796913824456762059[75] = 0;
   out_2796913824456762059[76] = 1;
   out_2796913824456762059[77] = 0;
   out_2796913824456762059[78] = 0;
   out_2796913824456762059[79] = 0;
   out_2796913824456762059[80] = 0;
   out_2796913824456762059[81] = 0;
   out_2796913824456762059[82] = 0;
   out_2796913824456762059[83] = 0;
   out_2796913824456762059[84] = 0;
   out_2796913824456762059[85] = dt;
   out_2796913824456762059[86] = 0;
   out_2796913824456762059[87] = 0;
   out_2796913824456762059[88] = 0;
   out_2796913824456762059[89] = 0;
   out_2796913824456762059[90] = 0;
   out_2796913824456762059[91] = 0;
   out_2796913824456762059[92] = 0;
   out_2796913824456762059[93] = 0;
   out_2796913824456762059[94] = 0;
   out_2796913824456762059[95] = 1;
   out_2796913824456762059[96] = 0;
   out_2796913824456762059[97] = 0;
   out_2796913824456762059[98] = 0;
   out_2796913824456762059[99] = 0;
   out_2796913824456762059[100] = 0;
   out_2796913824456762059[101] = 0;
   out_2796913824456762059[102] = 0;
   out_2796913824456762059[103] = 0;
   out_2796913824456762059[104] = dt;
   out_2796913824456762059[105] = 0;
   out_2796913824456762059[106] = 0;
   out_2796913824456762059[107] = 0;
   out_2796913824456762059[108] = 0;
   out_2796913824456762059[109] = 0;
   out_2796913824456762059[110] = 0;
   out_2796913824456762059[111] = 0;
   out_2796913824456762059[112] = 0;
   out_2796913824456762059[113] = 0;
   out_2796913824456762059[114] = 1;
   out_2796913824456762059[115] = 0;
   out_2796913824456762059[116] = 0;
   out_2796913824456762059[117] = 0;
   out_2796913824456762059[118] = 0;
   out_2796913824456762059[119] = 0;
   out_2796913824456762059[120] = 0;
   out_2796913824456762059[121] = 0;
   out_2796913824456762059[122] = 0;
   out_2796913824456762059[123] = 0;
   out_2796913824456762059[124] = 0;
   out_2796913824456762059[125] = 0;
   out_2796913824456762059[126] = 0;
   out_2796913824456762059[127] = 0;
   out_2796913824456762059[128] = 0;
   out_2796913824456762059[129] = 0;
   out_2796913824456762059[130] = 0;
   out_2796913824456762059[131] = 0;
   out_2796913824456762059[132] = 0;
   out_2796913824456762059[133] = 1;
   out_2796913824456762059[134] = 0;
   out_2796913824456762059[135] = 0;
   out_2796913824456762059[136] = 0;
   out_2796913824456762059[137] = 0;
   out_2796913824456762059[138] = 0;
   out_2796913824456762059[139] = 0;
   out_2796913824456762059[140] = 0;
   out_2796913824456762059[141] = 0;
   out_2796913824456762059[142] = 0;
   out_2796913824456762059[143] = 0;
   out_2796913824456762059[144] = 0;
   out_2796913824456762059[145] = 0;
   out_2796913824456762059[146] = 0;
   out_2796913824456762059[147] = 0;
   out_2796913824456762059[148] = 0;
   out_2796913824456762059[149] = 0;
   out_2796913824456762059[150] = 0;
   out_2796913824456762059[151] = 0;
   out_2796913824456762059[152] = 1;
   out_2796913824456762059[153] = 0;
   out_2796913824456762059[154] = 0;
   out_2796913824456762059[155] = 0;
   out_2796913824456762059[156] = 0;
   out_2796913824456762059[157] = 0;
   out_2796913824456762059[158] = 0;
   out_2796913824456762059[159] = 0;
   out_2796913824456762059[160] = 0;
   out_2796913824456762059[161] = 0;
   out_2796913824456762059[162] = 0;
   out_2796913824456762059[163] = 0;
   out_2796913824456762059[164] = 0;
   out_2796913824456762059[165] = 0;
   out_2796913824456762059[166] = 0;
   out_2796913824456762059[167] = 0;
   out_2796913824456762059[168] = 0;
   out_2796913824456762059[169] = 0;
   out_2796913824456762059[170] = 0;
   out_2796913824456762059[171] = 1;
   out_2796913824456762059[172] = 0;
   out_2796913824456762059[173] = 0;
   out_2796913824456762059[174] = 0;
   out_2796913824456762059[175] = 0;
   out_2796913824456762059[176] = 0;
   out_2796913824456762059[177] = 0;
   out_2796913824456762059[178] = 0;
   out_2796913824456762059[179] = 0;
   out_2796913824456762059[180] = 0;
   out_2796913824456762059[181] = 0;
   out_2796913824456762059[182] = 0;
   out_2796913824456762059[183] = 0;
   out_2796913824456762059[184] = 0;
   out_2796913824456762059[185] = 0;
   out_2796913824456762059[186] = 0;
   out_2796913824456762059[187] = 0;
   out_2796913824456762059[188] = 0;
   out_2796913824456762059[189] = 0;
   out_2796913824456762059[190] = 1;
   out_2796913824456762059[191] = 0;
   out_2796913824456762059[192] = 0;
   out_2796913824456762059[193] = 0;
   out_2796913824456762059[194] = 0;
   out_2796913824456762059[195] = 0;
   out_2796913824456762059[196] = 0;
   out_2796913824456762059[197] = 0;
   out_2796913824456762059[198] = 0;
   out_2796913824456762059[199] = 0;
   out_2796913824456762059[200] = 0;
   out_2796913824456762059[201] = 0;
   out_2796913824456762059[202] = 0;
   out_2796913824456762059[203] = 0;
   out_2796913824456762059[204] = 0;
   out_2796913824456762059[205] = 0;
   out_2796913824456762059[206] = 0;
   out_2796913824456762059[207] = 0;
   out_2796913824456762059[208] = 0;
   out_2796913824456762059[209] = 1;
   out_2796913824456762059[210] = 0;
   out_2796913824456762059[211] = 0;
   out_2796913824456762059[212] = 0;
   out_2796913824456762059[213] = 0;
   out_2796913824456762059[214] = 0;
   out_2796913824456762059[215] = 0;
   out_2796913824456762059[216] = 0;
   out_2796913824456762059[217] = 0;
   out_2796913824456762059[218] = 0;
   out_2796913824456762059[219] = 0;
   out_2796913824456762059[220] = 0;
   out_2796913824456762059[221] = 0;
   out_2796913824456762059[222] = 0;
   out_2796913824456762059[223] = 0;
   out_2796913824456762059[224] = 0;
   out_2796913824456762059[225] = 0;
   out_2796913824456762059[226] = 0;
   out_2796913824456762059[227] = 0;
   out_2796913824456762059[228] = 1;
   out_2796913824456762059[229] = 0;
   out_2796913824456762059[230] = 0;
   out_2796913824456762059[231] = 0;
   out_2796913824456762059[232] = 0;
   out_2796913824456762059[233] = 0;
   out_2796913824456762059[234] = 0;
   out_2796913824456762059[235] = 0;
   out_2796913824456762059[236] = 0;
   out_2796913824456762059[237] = 0;
   out_2796913824456762059[238] = 0;
   out_2796913824456762059[239] = 0;
   out_2796913824456762059[240] = 0;
   out_2796913824456762059[241] = 0;
   out_2796913824456762059[242] = 0;
   out_2796913824456762059[243] = 0;
   out_2796913824456762059[244] = 0;
   out_2796913824456762059[245] = 0;
   out_2796913824456762059[246] = 0;
   out_2796913824456762059[247] = 1;
   out_2796913824456762059[248] = 0;
   out_2796913824456762059[249] = 0;
   out_2796913824456762059[250] = 0;
   out_2796913824456762059[251] = 0;
   out_2796913824456762059[252] = 0;
   out_2796913824456762059[253] = 0;
   out_2796913824456762059[254] = 0;
   out_2796913824456762059[255] = 0;
   out_2796913824456762059[256] = 0;
   out_2796913824456762059[257] = 0;
   out_2796913824456762059[258] = 0;
   out_2796913824456762059[259] = 0;
   out_2796913824456762059[260] = 0;
   out_2796913824456762059[261] = 0;
   out_2796913824456762059[262] = 0;
   out_2796913824456762059[263] = 0;
   out_2796913824456762059[264] = 0;
   out_2796913824456762059[265] = 0;
   out_2796913824456762059[266] = 1;
   out_2796913824456762059[267] = 0;
   out_2796913824456762059[268] = 0;
   out_2796913824456762059[269] = 0;
   out_2796913824456762059[270] = 0;
   out_2796913824456762059[271] = 0;
   out_2796913824456762059[272] = 0;
   out_2796913824456762059[273] = 0;
   out_2796913824456762059[274] = 0;
   out_2796913824456762059[275] = 0;
   out_2796913824456762059[276] = 0;
   out_2796913824456762059[277] = 0;
   out_2796913824456762059[278] = 0;
   out_2796913824456762059[279] = 0;
   out_2796913824456762059[280] = 0;
   out_2796913824456762059[281] = 0;
   out_2796913824456762059[282] = 0;
   out_2796913824456762059[283] = 0;
   out_2796913824456762059[284] = 0;
   out_2796913824456762059[285] = 1;
   out_2796913824456762059[286] = 0;
   out_2796913824456762059[287] = 0;
   out_2796913824456762059[288] = 0;
   out_2796913824456762059[289] = 0;
   out_2796913824456762059[290] = 0;
   out_2796913824456762059[291] = 0;
   out_2796913824456762059[292] = 0;
   out_2796913824456762059[293] = 0;
   out_2796913824456762059[294] = 0;
   out_2796913824456762059[295] = 0;
   out_2796913824456762059[296] = 0;
   out_2796913824456762059[297] = 0;
   out_2796913824456762059[298] = 0;
   out_2796913824456762059[299] = 0;
   out_2796913824456762059[300] = 0;
   out_2796913824456762059[301] = 0;
   out_2796913824456762059[302] = 0;
   out_2796913824456762059[303] = 0;
   out_2796913824456762059[304] = 1;
   out_2796913824456762059[305] = 0;
   out_2796913824456762059[306] = 0;
   out_2796913824456762059[307] = 0;
   out_2796913824456762059[308] = 0;
   out_2796913824456762059[309] = 0;
   out_2796913824456762059[310] = 0;
   out_2796913824456762059[311] = 0;
   out_2796913824456762059[312] = 0;
   out_2796913824456762059[313] = 0;
   out_2796913824456762059[314] = 0;
   out_2796913824456762059[315] = 0;
   out_2796913824456762059[316] = 0;
   out_2796913824456762059[317] = 0;
   out_2796913824456762059[318] = 0;
   out_2796913824456762059[319] = 0;
   out_2796913824456762059[320] = 0;
   out_2796913824456762059[321] = 0;
   out_2796913824456762059[322] = 0;
   out_2796913824456762059[323] = 1;
}
void h_4(double *state, double *unused, double *out_9193516370136012539) {
   out_9193516370136012539[0] = state[6] + state[9];
   out_9193516370136012539[1] = state[7] + state[10];
   out_9193516370136012539[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3657757106827190501) {
   out_3657757106827190501[0] = 0;
   out_3657757106827190501[1] = 0;
   out_3657757106827190501[2] = 0;
   out_3657757106827190501[3] = 0;
   out_3657757106827190501[4] = 0;
   out_3657757106827190501[5] = 0;
   out_3657757106827190501[6] = 1;
   out_3657757106827190501[7] = 0;
   out_3657757106827190501[8] = 0;
   out_3657757106827190501[9] = 1;
   out_3657757106827190501[10] = 0;
   out_3657757106827190501[11] = 0;
   out_3657757106827190501[12] = 0;
   out_3657757106827190501[13] = 0;
   out_3657757106827190501[14] = 0;
   out_3657757106827190501[15] = 0;
   out_3657757106827190501[16] = 0;
   out_3657757106827190501[17] = 0;
   out_3657757106827190501[18] = 0;
   out_3657757106827190501[19] = 0;
   out_3657757106827190501[20] = 0;
   out_3657757106827190501[21] = 0;
   out_3657757106827190501[22] = 0;
   out_3657757106827190501[23] = 0;
   out_3657757106827190501[24] = 0;
   out_3657757106827190501[25] = 1;
   out_3657757106827190501[26] = 0;
   out_3657757106827190501[27] = 0;
   out_3657757106827190501[28] = 1;
   out_3657757106827190501[29] = 0;
   out_3657757106827190501[30] = 0;
   out_3657757106827190501[31] = 0;
   out_3657757106827190501[32] = 0;
   out_3657757106827190501[33] = 0;
   out_3657757106827190501[34] = 0;
   out_3657757106827190501[35] = 0;
   out_3657757106827190501[36] = 0;
   out_3657757106827190501[37] = 0;
   out_3657757106827190501[38] = 0;
   out_3657757106827190501[39] = 0;
   out_3657757106827190501[40] = 0;
   out_3657757106827190501[41] = 0;
   out_3657757106827190501[42] = 0;
   out_3657757106827190501[43] = 0;
   out_3657757106827190501[44] = 1;
   out_3657757106827190501[45] = 0;
   out_3657757106827190501[46] = 0;
   out_3657757106827190501[47] = 1;
   out_3657757106827190501[48] = 0;
   out_3657757106827190501[49] = 0;
   out_3657757106827190501[50] = 0;
   out_3657757106827190501[51] = 0;
   out_3657757106827190501[52] = 0;
   out_3657757106827190501[53] = 0;
}
void h_10(double *state, double *unused, double *out_5330616401180944027) {
   out_5330616401180944027[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5330616401180944027[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5330616401180944027[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1395272858445918149) {
   out_1395272858445918149[0] = 0;
   out_1395272858445918149[1] = 9.8100000000000005*cos(state[1]);
   out_1395272858445918149[2] = 0;
   out_1395272858445918149[3] = 0;
   out_1395272858445918149[4] = -state[8];
   out_1395272858445918149[5] = state[7];
   out_1395272858445918149[6] = 0;
   out_1395272858445918149[7] = state[5];
   out_1395272858445918149[8] = -state[4];
   out_1395272858445918149[9] = 0;
   out_1395272858445918149[10] = 0;
   out_1395272858445918149[11] = 0;
   out_1395272858445918149[12] = 1;
   out_1395272858445918149[13] = 0;
   out_1395272858445918149[14] = 0;
   out_1395272858445918149[15] = 1;
   out_1395272858445918149[16] = 0;
   out_1395272858445918149[17] = 0;
   out_1395272858445918149[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1395272858445918149[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1395272858445918149[20] = 0;
   out_1395272858445918149[21] = state[8];
   out_1395272858445918149[22] = 0;
   out_1395272858445918149[23] = -state[6];
   out_1395272858445918149[24] = -state[5];
   out_1395272858445918149[25] = 0;
   out_1395272858445918149[26] = state[3];
   out_1395272858445918149[27] = 0;
   out_1395272858445918149[28] = 0;
   out_1395272858445918149[29] = 0;
   out_1395272858445918149[30] = 0;
   out_1395272858445918149[31] = 1;
   out_1395272858445918149[32] = 0;
   out_1395272858445918149[33] = 0;
   out_1395272858445918149[34] = 1;
   out_1395272858445918149[35] = 0;
   out_1395272858445918149[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1395272858445918149[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1395272858445918149[38] = 0;
   out_1395272858445918149[39] = -state[7];
   out_1395272858445918149[40] = state[6];
   out_1395272858445918149[41] = 0;
   out_1395272858445918149[42] = state[4];
   out_1395272858445918149[43] = -state[3];
   out_1395272858445918149[44] = 0;
   out_1395272858445918149[45] = 0;
   out_1395272858445918149[46] = 0;
   out_1395272858445918149[47] = 0;
   out_1395272858445918149[48] = 0;
   out_1395272858445918149[49] = 0;
   out_1395272858445918149[50] = 1;
   out_1395272858445918149[51] = 0;
   out_1395272858445918149[52] = 0;
   out_1395272858445918149[53] = 1;
}
void h_13(double *state, double *unused, double *out_8491663337253319846) {
   out_8491663337253319846[0] = state[3];
   out_8491663337253319846[1] = state[4];
   out_8491663337253319846[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6870030932159523302) {
   out_6870030932159523302[0] = 0;
   out_6870030932159523302[1] = 0;
   out_6870030932159523302[2] = 0;
   out_6870030932159523302[3] = 1;
   out_6870030932159523302[4] = 0;
   out_6870030932159523302[5] = 0;
   out_6870030932159523302[6] = 0;
   out_6870030932159523302[7] = 0;
   out_6870030932159523302[8] = 0;
   out_6870030932159523302[9] = 0;
   out_6870030932159523302[10] = 0;
   out_6870030932159523302[11] = 0;
   out_6870030932159523302[12] = 0;
   out_6870030932159523302[13] = 0;
   out_6870030932159523302[14] = 0;
   out_6870030932159523302[15] = 0;
   out_6870030932159523302[16] = 0;
   out_6870030932159523302[17] = 0;
   out_6870030932159523302[18] = 0;
   out_6870030932159523302[19] = 0;
   out_6870030932159523302[20] = 0;
   out_6870030932159523302[21] = 0;
   out_6870030932159523302[22] = 1;
   out_6870030932159523302[23] = 0;
   out_6870030932159523302[24] = 0;
   out_6870030932159523302[25] = 0;
   out_6870030932159523302[26] = 0;
   out_6870030932159523302[27] = 0;
   out_6870030932159523302[28] = 0;
   out_6870030932159523302[29] = 0;
   out_6870030932159523302[30] = 0;
   out_6870030932159523302[31] = 0;
   out_6870030932159523302[32] = 0;
   out_6870030932159523302[33] = 0;
   out_6870030932159523302[34] = 0;
   out_6870030932159523302[35] = 0;
   out_6870030932159523302[36] = 0;
   out_6870030932159523302[37] = 0;
   out_6870030932159523302[38] = 0;
   out_6870030932159523302[39] = 0;
   out_6870030932159523302[40] = 0;
   out_6870030932159523302[41] = 1;
   out_6870030932159523302[42] = 0;
   out_6870030932159523302[43] = 0;
   out_6870030932159523302[44] = 0;
   out_6870030932159523302[45] = 0;
   out_6870030932159523302[46] = 0;
   out_6870030932159523302[47] = 0;
   out_6870030932159523302[48] = 0;
   out_6870030932159523302[49] = 0;
   out_6870030932159523302[50] = 0;
   out_6870030932159523302[51] = 0;
   out_6870030932159523302[52] = 0;
   out_6870030932159523302[53] = 0;
}
void h_14(double *state, double *unused, double *out_730939643929042312) {
   out_730939643929042312[0] = state[6];
   out_730939643929042312[1] = state[7];
   out_730939643929042312[2] = state[8];
}
void H_14(double *state, double *unused, double *out_574968674531818205) {
   out_574968674531818205[0] = 0;
   out_574968674531818205[1] = 0;
   out_574968674531818205[2] = 0;
   out_574968674531818205[3] = 0;
   out_574968674531818205[4] = 0;
   out_574968674531818205[5] = 0;
   out_574968674531818205[6] = 1;
   out_574968674531818205[7] = 0;
   out_574968674531818205[8] = 0;
   out_574968674531818205[9] = 0;
   out_574968674531818205[10] = 0;
   out_574968674531818205[11] = 0;
   out_574968674531818205[12] = 0;
   out_574968674531818205[13] = 0;
   out_574968674531818205[14] = 0;
   out_574968674531818205[15] = 0;
   out_574968674531818205[16] = 0;
   out_574968674531818205[17] = 0;
   out_574968674531818205[18] = 0;
   out_574968674531818205[19] = 0;
   out_574968674531818205[20] = 0;
   out_574968674531818205[21] = 0;
   out_574968674531818205[22] = 0;
   out_574968674531818205[23] = 0;
   out_574968674531818205[24] = 0;
   out_574968674531818205[25] = 1;
   out_574968674531818205[26] = 0;
   out_574968674531818205[27] = 0;
   out_574968674531818205[28] = 0;
   out_574968674531818205[29] = 0;
   out_574968674531818205[30] = 0;
   out_574968674531818205[31] = 0;
   out_574968674531818205[32] = 0;
   out_574968674531818205[33] = 0;
   out_574968674531818205[34] = 0;
   out_574968674531818205[35] = 0;
   out_574968674531818205[36] = 0;
   out_574968674531818205[37] = 0;
   out_574968674531818205[38] = 0;
   out_574968674531818205[39] = 0;
   out_574968674531818205[40] = 0;
   out_574968674531818205[41] = 0;
   out_574968674531818205[42] = 0;
   out_574968674531818205[43] = 0;
   out_574968674531818205[44] = 1;
   out_574968674531818205[45] = 0;
   out_574968674531818205[46] = 0;
   out_574968674531818205[47] = 0;
   out_574968674531818205[48] = 0;
   out_574968674531818205[49] = 0;
   out_574968674531818205[50] = 0;
   out_574968674531818205[51] = 0;
   out_574968674531818205[52] = 0;
   out_574968674531818205[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8794951023692473693) {
  err_fun(nom_x, delta_x, out_8794951023692473693);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_147609790886506349) {
  inv_err_fun(nom_x, true_x, out_147609790886506349);
}
void pose_H_mod_fun(double *state, double *out_4713269657164746226) {
  H_mod_fun(state, out_4713269657164746226);
}
void pose_f_fun(double *state, double dt, double *out_8307718287749749495) {
  f_fun(state,  dt, out_8307718287749749495);
}
void pose_F_fun(double *state, double dt, double *out_2796913824456762059) {
  F_fun(state,  dt, out_2796913824456762059);
}
void pose_h_4(double *state, double *unused, double *out_9193516370136012539) {
  h_4(state, unused, out_9193516370136012539);
}
void pose_H_4(double *state, double *unused, double *out_3657757106827190501) {
  H_4(state, unused, out_3657757106827190501);
}
void pose_h_10(double *state, double *unused, double *out_5330616401180944027) {
  h_10(state, unused, out_5330616401180944027);
}
void pose_H_10(double *state, double *unused, double *out_1395272858445918149) {
  H_10(state, unused, out_1395272858445918149);
}
void pose_h_13(double *state, double *unused, double *out_8491663337253319846) {
  h_13(state, unused, out_8491663337253319846);
}
void pose_H_13(double *state, double *unused, double *out_6870030932159523302) {
  H_13(state, unused, out_6870030932159523302);
}
void pose_h_14(double *state, double *unused, double *out_730939643929042312) {
  h_14(state, unused, out_730939643929042312);
}
void pose_H_14(double *state, double *unused, double *out_574968674531818205) {
  H_14(state, unused, out_574968674531818205);
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
