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
void err_fun(double *nom_x, double *delta_x, double *out_1813739608873815140) {
   out_1813739608873815140[0] = delta_x[0] + nom_x[0];
   out_1813739608873815140[1] = delta_x[1] + nom_x[1];
   out_1813739608873815140[2] = delta_x[2] + nom_x[2];
   out_1813739608873815140[3] = delta_x[3] + nom_x[3];
   out_1813739608873815140[4] = delta_x[4] + nom_x[4];
   out_1813739608873815140[5] = delta_x[5] + nom_x[5];
   out_1813739608873815140[6] = delta_x[6] + nom_x[6];
   out_1813739608873815140[7] = delta_x[7] + nom_x[7];
   out_1813739608873815140[8] = delta_x[8] + nom_x[8];
   out_1813739608873815140[9] = delta_x[9] + nom_x[9];
   out_1813739608873815140[10] = delta_x[10] + nom_x[10];
   out_1813739608873815140[11] = delta_x[11] + nom_x[11];
   out_1813739608873815140[12] = delta_x[12] + nom_x[12];
   out_1813739608873815140[13] = delta_x[13] + nom_x[13];
   out_1813739608873815140[14] = delta_x[14] + nom_x[14];
   out_1813739608873815140[15] = delta_x[15] + nom_x[15];
   out_1813739608873815140[16] = delta_x[16] + nom_x[16];
   out_1813739608873815140[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8036368585793301884) {
   out_8036368585793301884[0] = -nom_x[0] + true_x[0];
   out_8036368585793301884[1] = -nom_x[1] + true_x[1];
   out_8036368585793301884[2] = -nom_x[2] + true_x[2];
   out_8036368585793301884[3] = -nom_x[3] + true_x[3];
   out_8036368585793301884[4] = -nom_x[4] + true_x[4];
   out_8036368585793301884[5] = -nom_x[5] + true_x[5];
   out_8036368585793301884[6] = -nom_x[6] + true_x[6];
   out_8036368585793301884[7] = -nom_x[7] + true_x[7];
   out_8036368585793301884[8] = -nom_x[8] + true_x[8];
   out_8036368585793301884[9] = -nom_x[9] + true_x[9];
   out_8036368585793301884[10] = -nom_x[10] + true_x[10];
   out_8036368585793301884[11] = -nom_x[11] + true_x[11];
   out_8036368585793301884[12] = -nom_x[12] + true_x[12];
   out_8036368585793301884[13] = -nom_x[13] + true_x[13];
   out_8036368585793301884[14] = -nom_x[14] + true_x[14];
   out_8036368585793301884[15] = -nom_x[15] + true_x[15];
   out_8036368585793301884[16] = -nom_x[16] + true_x[16];
   out_8036368585793301884[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3792066886079858939) {
   out_3792066886079858939[0] = 1.0;
   out_3792066886079858939[1] = 0.0;
   out_3792066886079858939[2] = 0.0;
   out_3792066886079858939[3] = 0.0;
   out_3792066886079858939[4] = 0.0;
   out_3792066886079858939[5] = 0.0;
   out_3792066886079858939[6] = 0.0;
   out_3792066886079858939[7] = 0.0;
   out_3792066886079858939[8] = 0.0;
   out_3792066886079858939[9] = 0.0;
   out_3792066886079858939[10] = 0.0;
   out_3792066886079858939[11] = 0.0;
   out_3792066886079858939[12] = 0.0;
   out_3792066886079858939[13] = 0.0;
   out_3792066886079858939[14] = 0.0;
   out_3792066886079858939[15] = 0.0;
   out_3792066886079858939[16] = 0.0;
   out_3792066886079858939[17] = 0.0;
   out_3792066886079858939[18] = 0.0;
   out_3792066886079858939[19] = 1.0;
   out_3792066886079858939[20] = 0.0;
   out_3792066886079858939[21] = 0.0;
   out_3792066886079858939[22] = 0.0;
   out_3792066886079858939[23] = 0.0;
   out_3792066886079858939[24] = 0.0;
   out_3792066886079858939[25] = 0.0;
   out_3792066886079858939[26] = 0.0;
   out_3792066886079858939[27] = 0.0;
   out_3792066886079858939[28] = 0.0;
   out_3792066886079858939[29] = 0.0;
   out_3792066886079858939[30] = 0.0;
   out_3792066886079858939[31] = 0.0;
   out_3792066886079858939[32] = 0.0;
   out_3792066886079858939[33] = 0.0;
   out_3792066886079858939[34] = 0.0;
   out_3792066886079858939[35] = 0.0;
   out_3792066886079858939[36] = 0.0;
   out_3792066886079858939[37] = 0.0;
   out_3792066886079858939[38] = 1.0;
   out_3792066886079858939[39] = 0.0;
   out_3792066886079858939[40] = 0.0;
   out_3792066886079858939[41] = 0.0;
   out_3792066886079858939[42] = 0.0;
   out_3792066886079858939[43] = 0.0;
   out_3792066886079858939[44] = 0.0;
   out_3792066886079858939[45] = 0.0;
   out_3792066886079858939[46] = 0.0;
   out_3792066886079858939[47] = 0.0;
   out_3792066886079858939[48] = 0.0;
   out_3792066886079858939[49] = 0.0;
   out_3792066886079858939[50] = 0.0;
   out_3792066886079858939[51] = 0.0;
   out_3792066886079858939[52] = 0.0;
   out_3792066886079858939[53] = 0.0;
   out_3792066886079858939[54] = 0.0;
   out_3792066886079858939[55] = 0.0;
   out_3792066886079858939[56] = 0.0;
   out_3792066886079858939[57] = 1.0;
   out_3792066886079858939[58] = 0.0;
   out_3792066886079858939[59] = 0.0;
   out_3792066886079858939[60] = 0.0;
   out_3792066886079858939[61] = 0.0;
   out_3792066886079858939[62] = 0.0;
   out_3792066886079858939[63] = 0.0;
   out_3792066886079858939[64] = 0.0;
   out_3792066886079858939[65] = 0.0;
   out_3792066886079858939[66] = 0.0;
   out_3792066886079858939[67] = 0.0;
   out_3792066886079858939[68] = 0.0;
   out_3792066886079858939[69] = 0.0;
   out_3792066886079858939[70] = 0.0;
   out_3792066886079858939[71] = 0.0;
   out_3792066886079858939[72] = 0.0;
   out_3792066886079858939[73] = 0.0;
   out_3792066886079858939[74] = 0.0;
   out_3792066886079858939[75] = 0.0;
   out_3792066886079858939[76] = 1.0;
   out_3792066886079858939[77] = 0.0;
   out_3792066886079858939[78] = 0.0;
   out_3792066886079858939[79] = 0.0;
   out_3792066886079858939[80] = 0.0;
   out_3792066886079858939[81] = 0.0;
   out_3792066886079858939[82] = 0.0;
   out_3792066886079858939[83] = 0.0;
   out_3792066886079858939[84] = 0.0;
   out_3792066886079858939[85] = 0.0;
   out_3792066886079858939[86] = 0.0;
   out_3792066886079858939[87] = 0.0;
   out_3792066886079858939[88] = 0.0;
   out_3792066886079858939[89] = 0.0;
   out_3792066886079858939[90] = 0.0;
   out_3792066886079858939[91] = 0.0;
   out_3792066886079858939[92] = 0.0;
   out_3792066886079858939[93] = 0.0;
   out_3792066886079858939[94] = 0.0;
   out_3792066886079858939[95] = 1.0;
   out_3792066886079858939[96] = 0.0;
   out_3792066886079858939[97] = 0.0;
   out_3792066886079858939[98] = 0.0;
   out_3792066886079858939[99] = 0.0;
   out_3792066886079858939[100] = 0.0;
   out_3792066886079858939[101] = 0.0;
   out_3792066886079858939[102] = 0.0;
   out_3792066886079858939[103] = 0.0;
   out_3792066886079858939[104] = 0.0;
   out_3792066886079858939[105] = 0.0;
   out_3792066886079858939[106] = 0.0;
   out_3792066886079858939[107] = 0.0;
   out_3792066886079858939[108] = 0.0;
   out_3792066886079858939[109] = 0.0;
   out_3792066886079858939[110] = 0.0;
   out_3792066886079858939[111] = 0.0;
   out_3792066886079858939[112] = 0.0;
   out_3792066886079858939[113] = 0.0;
   out_3792066886079858939[114] = 1.0;
   out_3792066886079858939[115] = 0.0;
   out_3792066886079858939[116] = 0.0;
   out_3792066886079858939[117] = 0.0;
   out_3792066886079858939[118] = 0.0;
   out_3792066886079858939[119] = 0.0;
   out_3792066886079858939[120] = 0.0;
   out_3792066886079858939[121] = 0.0;
   out_3792066886079858939[122] = 0.0;
   out_3792066886079858939[123] = 0.0;
   out_3792066886079858939[124] = 0.0;
   out_3792066886079858939[125] = 0.0;
   out_3792066886079858939[126] = 0.0;
   out_3792066886079858939[127] = 0.0;
   out_3792066886079858939[128] = 0.0;
   out_3792066886079858939[129] = 0.0;
   out_3792066886079858939[130] = 0.0;
   out_3792066886079858939[131] = 0.0;
   out_3792066886079858939[132] = 0.0;
   out_3792066886079858939[133] = 1.0;
   out_3792066886079858939[134] = 0.0;
   out_3792066886079858939[135] = 0.0;
   out_3792066886079858939[136] = 0.0;
   out_3792066886079858939[137] = 0.0;
   out_3792066886079858939[138] = 0.0;
   out_3792066886079858939[139] = 0.0;
   out_3792066886079858939[140] = 0.0;
   out_3792066886079858939[141] = 0.0;
   out_3792066886079858939[142] = 0.0;
   out_3792066886079858939[143] = 0.0;
   out_3792066886079858939[144] = 0.0;
   out_3792066886079858939[145] = 0.0;
   out_3792066886079858939[146] = 0.0;
   out_3792066886079858939[147] = 0.0;
   out_3792066886079858939[148] = 0.0;
   out_3792066886079858939[149] = 0.0;
   out_3792066886079858939[150] = 0.0;
   out_3792066886079858939[151] = 0.0;
   out_3792066886079858939[152] = 1.0;
   out_3792066886079858939[153] = 0.0;
   out_3792066886079858939[154] = 0.0;
   out_3792066886079858939[155] = 0.0;
   out_3792066886079858939[156] = 0.0;
   out_3792066886079858939[157] = 0.0;
   out_3792066886079858939[158] = 0.0;
   out_3792066886079858939[159] = 0.0;
   out_3792066886079858939[160] = 0.0;
   out_3792066886079858939[161] = 0.0;
   out_3792066886079858939[162] = 0.0;
   out_3792066886079858939[163] = 0.0;
   out_3792066886079858939[164] = 0.0;
   out_3792066886079858939[165] = 0.0;
   out_3792066886079858939[166] = 0.0;
   out_3792066886079858939[167] = 0.0;
   out_3792066886079858939[168] = 0.0;
   out_3792066886079858939[169] = 0.0;
   out_3792066886079858939[170] = 0.0;
   out_3792066886079858939[171] = 1.0;
   out_3792066886079858939[172] = 0.0;
   out_3792066886079858939[173] = 0.0;
   out_3792066886079858939[174] = 0.0;
   out_3792066886079858939[175] = 0.0;
   out_3792066886079858939[176] = 0.0;
   out_3792066886079858939[177] = 0.0;
   out_3792066886079858939[178] = 0.0;
   out_3792066886079858939[179] = 0.0;
   out_3792066886079858939[180] = 0.0;
   out_3792066886079858939[181] = 0.0;
   out_3792066886079858939[182] = 0.0;
   out_3792066886079858939[183] = 0.0;
   out_3792066886079858939[184] = 0.0;
   out_3792066886079858939[185] = 0.0;
   out_3792066886079858939[186] = 0.0;
   out_3792066886079858939[187] = 0.0;
   out_3792066886079858939[188] = 0.0;
   out_3792066886079858939[189] = 0.0;
   out_3792066886079858939[190] = 1.0;
   out_3792066886079858939[191] = 0.0;
   out_3792066886079858939[192] = 0.0;
   out_3792066886079858939[193] = 0.0;
   out_3792066886079858939[194] = 0.0;
   out_3792066886079858939[195] = 0.0;
   out_3792066886079858939[196] = 0.0;
   out_3792066886079858939[197] = 0.0;
   out_3792066886079858939[198] = 0.0;
   out_3792066886079858939[199] = 0.0;
   out_3792066886079858939[200] = 0.0;
   out_3792066886079858939[201] = 0.0;
   out_3792066886079858939[202] = 0.0;
   out_3792066886079858939[203] = 0.0;
   out_3792066886079858939[204] = 0.0;
   out_3792066886079858939[205] = 0.0;
   out_3792066886079858939[206] = 0.0;
   out_3792066886079858939[207] = 0.0;
   out_3792066886079858939[208] = 0.0;
   out_3792066886079858939[209] = 1.0;
   out_3792066886079858939[210] = 0.0;
   out_3792066886079858939[211] = 0.0;
   out_3792066886079858939[212] = 0.0;
   out_3792066886079858939[213] = 0.0;
   out_3792066886079858939[214] = 0.0;
   out_3792066886079858939[215] = 0.0;
   out_3792066886079858939[216] = 0.0;
   out_3792066886079858939[217] = 0.0;
   out_3792066886079858939[218] = 0.0;
   out_3792066886079858939[219] = 0.0;
   out_3792066886079858939[220] = 0.0;
   out_3792066886079858939[221] = 0.0;
   out_3792066886079858939[222] = 0.0;
   out_3792066886079858939[223] = 0.0;
   out_3792066886079858939[224] = 0.0;
   out_3792066886079858939[225] = 0.0;
   out_3792066886079858939[226] = 0.0;
   out_3792066886079858939[227] = 0.0;
   out_3792066886079858939[228] = 1.0;
   out_3792066886079858939[229] = 0.0;
   out_3792066886079858939[230] = 0.0;
   out_3792066886079858939[231] = 0.0;
   out_3792066886079858939[232] = 0.0;
   out_3792066886079858939[233] = 0.0;
   out_3792066886079858939[234] = 0.0;
   out_3792066886079858939[235] = 0.0;
   out_3792066886079858939[236] = 0.0;
   out_3792066886079858939[237] = 0.0;
   out_3792066886079858939[238] = 0.0;
   out_3792066886079858939[239] = 0.0;
   out_3792066886079858939[240] = 0.0;
   out_3792066886079858939[241] = 0.0;
   out_3792066886079858939[242] = 0.0;
   out_3792066886079858939[243] = 0.0;
   out_3792066886079858939[244] = 0.0;
   out_3792066886079858939[245] = 0.0;
   out_3792066886079858939[246] = 0.0;
   out_3792066886079858939[247] = 1.0;
   out_3792066886079858939[248] = 0.0;
   out_3792066886079858939[249] = 0.0;
   out_3792066886079858939[250] = 0.0;
   out_3792066886079858939[251] = 0.0;
   out_3792066886079858939[252] = 0.0;
   out_3792066886079858939[253] = 0.0;
   out_3792066886079858939[254] = 0.0;
   out_3792066886079858939[255] = 0.0;
   out_3792066886079858939[256] = 0.0;
   out_3792066886079858939[257] = 0.0;
   out_3792066886079858939[258] = 0.0;
   out_3792066886079858939[259] = 0.0;
   out_3792066886079858939[260] = 0.0;
   out_3792066886079858939[261] = 0.0;
   out_3792066886079858939[262] = 0.0;
   out_3792066886079858939[263] = 0.0;
   out_3792066886079858939[264] = 0.0;
   out_3792066886079858939[265] = 0.0;
   out_3792066886079858939[266] = 1.0;
   out_3792066886079858939[267] = 0.0;
   out_3792066886079858939[268] = 0.0;
   out_3792066886079858939[269] = 0.0;
   out_3792066886079858939[270] = 0.0;
   out_3792066886079858939[271] = 0.0;
   out_3792066886079858939[272] = 0.0;
   out_3792066886079858939[273] = 0.0;
   out_3792066886079858939[274] = 0.0;
   out_3792066886079858939[275] = 0.0;
   out_3792066886079858939[276] = 0.0;
   out_3792066886079858939[277] = 0.0;
   out_3792066886079858939[278] = 0.0;
   out_3792066886079858939[279] = 0.0;
   out_3792066886079858939[280] = 0.0;
   out_3792066886079858939[281] = 0.0;
   out_3792066886079858939[282] = 0.0;
   out_3792066886079858939[283] = 0.0;
   out_3792066886079858939[284] = 0.0;
   out_3792066886079858939[285] = 1.0;
   out_3792066886079858939[286] = 0.0;
   out_3792066886079858939[287] = 0.0;
   out_3792066886079858939[288] = 0.0;
   out_3792066886079858939[289] = 0.0;
   out_3792066886079858939[290] = 0.0;
   out_3792066886079858939[291] = 0.0;
   out_3792066886079858939[292] = 0.0;
   out_3792066886079858939[293] = 0.0;
   out_3792066886079858939[294] = 0.0;
   out_3792066886079858939[295] = 0.0;
   out_3792066886079858939[296] = 0.0;
   out_3792066886079858939[297] = 0.0;
   out_3792066886079858939[298] = 0.0;
   out_3792066886079858939[299] = 0.0;
   out_3792066886079858939[300] = 0.0;
   out_3792066886079858939[301] = 0.0;
   out_3792066886079858939[302] = 0.0;
   out_3792066886079858939[303] = 0.0;
   out_3792066886079858939[304] = 1.0;
   out_3792066886079858939[305] = 0.0;
   out_3792066886079858939[306] = 0.0;
   out_3792066886079858939[307] = 0.0;
   out_3792066886079858939[308] = 0.0;
   out_3792066886079858939[309] = 0.0;
   out_3792066886079858939[310] = 0.0;
   out_3792066886079858939[311] = 0.0;
   out_3792066886079858939[312] = 0.0;
   out_3792066886079858939[313] = 0.0;
   out_3792066886079858939[314] = 0.0;
   out_3792066886079858939[315] = 0.0;
   out_3792066886079858939[316] = 0.0;
   out_3792066886079858939[317] = 0.0;
   out_3792066886079858939[318] = 0.0;
   out_3792066886079858939[319] = 0.0;
   out_3792066886079858939[320] = 0.0;
   out_3792066886079858939[321] = 0.0;
   out_3792066886079858939[322] = 0.0;
   out_3792066886079858939[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8697136999633362847) {
   out_8697136999633362847[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8697136999633362847[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8697136999633362847[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8697136999633362847[3] = dt*state[12] + state[3];
   out_8697136999633362847[4] = dt*state[13] + state[4];
   out_8697136999633362847[5] = dt*state[14] + state[5];
   out_8697136999633362847[6] = state[6];
   out_8697136999633362847[7] = state[7];
   out_8697136999633362847[8] = state[8];
   out_8697136999633362847[9] = state[9];
   out_8697136999633362847[10] = state[10];
   out_8697136999633362847[11] = state[11];
   out_8697136999633362847[12] = state[12];
   out_8697136999633362847[13] = state[13];
   out_8697136999633362847[14] = state[14];
   out_8697136999633362847[15] = state[15];
   out_8697136999633362847[16] = state[16];
   out_8697136999633362847[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3871028545822381301) {
   out_3871028545822381301[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3871028545822381301[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3871028545822381301[2] = 0;
   out_3871028545822381301[3] = 0;
   out_3871028545822381301[4] = 0;
   out_3871028545822381301[5] = 0;
   out_3871028545822381301[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3871028545822381301[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3871028545822381301[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3871028545822381301[9] = 0;
   out_3871028545822381301[10] = 0;
   out_3871028545822381301[11] = 0;
   out_3871028545822381301[12] = 0;
   out_3871028545822381301[13] = 0;
   out_3871028545822381301[14] = 0;
   out_3871028545822381301[15] = 0;
   out_3871028545822381301[16] = 0;
   out_3871028545822381301[17] = 0;
   out_3871028545822381301[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3871028545822381301[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3871028545822381301[20] = 0;
   out_3871028545822381301[21] = 0;
   out_3871028545822381301[22] = 0;
   out_3871028545822381301[23] = 0;
   out_3871028545822381301[24] = 0;
   out_3871028545822381301[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3871028545822381301[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3871028545822381301[27] = 0;
   out_3871028545822381301[28] = 0;
   out_3871028545822381301[29] = 0;
   out_3871028545822381301[30] = 0;
   out_3871028545822381301[31] = 0;
   out_3871028545822381301[32] = 0;
   out_3871028545822381301[33] = 0;
   out_3871028545822381301[34] = 0;
   out_3871028545822381301[35] = 0;
   out_3871028545822381301[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3871028545822381301[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3871028545822381301[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3871028545822381301[39] = 0;
   out_3871028545822381301[40] = 0;
   out_3871028545822381301[41] = 0;
   out_3871028545822381301[42] = 0;
   out_3871028545822381301[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3871028545822381301[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3871028545822381301[45] = 0;
   out_3871028545822381301[46] = 0;
   out_3871028545822381301[47] = 0;
   out_3871028545822381301[48] = 0;
   out_3871028545822381301[49] = 0;
   out_3871028545822381301[50] = 0;
   out_3871028545822381301[51] = 0;
   out_3871028545822381301[52] = 0;
   out_3871028545822381301[53] = 0;
   out_3871028545822381301[54] = 0;
   out_3871028545822381301[55] = 0;
   out_3871028545822381301[56] = 0;
   out_3871028545822381301[57] = 1;
   out_3871028545822381301[58] = 0;
   out_3871028545822381301[59] = 0;
   out_3871028545822381301[60] = 0;
   out_3871028545822381301[61] = 0;
   out_3871028545822381301[62] = 0;
   out_3871028545822381301[63] = 0;
   out_3871028545822381301[64] = 0;
   out_3871028545822381301[65] = 0;
   out_3871028545822381301[66] = dt;
   out_3871028545822381301[67] = 0;
   out_3871028545822381301[68] = 0;
   out_3871028545822381301[69] = 0;
   out_3871028545822381301[70] = 0;
   out_3871028545822381301[71] = 0;
   out_3871028545822381301[72] = 0;
   out_3871028545822381301[73] = 0;
   out_3871028545822381301[74] = 0;
   out_3871028545822381301[75] = 0;
   out_3871028545822381301[76] = 1;
   out_3871028545822381301[77] = 0;
   out_3871028545822381301[78] = 0;
   out_3871028545822381301[79] = 0;
   out_3871028545822381301[80] = 0;
   out_3871028545822381301[81] = 0;
   out_3871028545822381301[82] = 0;
   out_3871028545822381301[83] = 0;
   out_3871028545822381301[84] = 0;
   out_3871028545822381301[85] = dt;
   out_3871028545822381301[86] = 0;
   out_3871028545822381301[87] = 0;
   out_3871028545822381301[88] = 0;
   out_3871028545822381301[89] = 0;
   out_3871028545822381301[90] = 0;
   out_3871028545822381301[91] = 0;
   out_3871028545822381301[92] = 0;
   out_3871028545822381301[93] = 0;
   out_3871028545822381301[94] = 0;
   out_3871028545822381301[95] = 1;
   out_3871028545822381301[96] = 0;
   out_3871028545822381301[97] = 0;
   out_3871028545822381301[98] = 0;
   out_3871028545822381301[99] = 0;
   out_3871028545822381301[100] = 0;
   out_3871028545822381301[101] = 0;
   out_3871028545822381301[102] = 0;
   out_3871028545822381301[103] = 0;
   out_3871028545822381301[104] = dt;
   out_3871028545822381301[105] = 0;
   out_3871028545822381301[106] = 0;
   out_3871028545822381301[107] = 0;
   out_3871028545822381301[108] = 0;
   out_3871028545822381301[109] = 0;
   out_3871028545822381301[110] = 0;
   out_3871028545822381301[111] = 0;
   out_3871028545822381301[112] = 0;
   out_3871028545822381301[113] = 0;
   out_3871028545822381301[114] = 1;
   out_3871028545822381301[115] = 0;
   out_3871028545822381301[116] = 0;
   out_3871028545822381301[117] = 0;
   out_3871028545822381301[118] = 0;
   out_3871028545822381301[119] = 0;
   out_3871028545822381301[120] = 0;
   out_3871028545822381301[121] = 0;
   out_3871028545822381301[122] = 0;
   out_3871028545822381301[123] = 0;
   out_3871028545822381301[124] = 0;
   out_3871028545822381301[125] = 0;
   out_3871028545822381301[126] = 0;
   out_3871028545822381301[127] = 0;
   out_3871028545822381301[128] = 0;
   out_3871028545822381301[129] = 0;
   out_3871028545822381301[130] = 0;
   out_3871028545822381301[131] = 0;
   out_3871028545822381301[132] = 0;
   out_3871028545822381301[133] = 1;
   out_3871028545822381301[134] = 0;
   out_3871028545822381301[135] = 0;
   out_3871028545822381301[136] = 0;
   out_3871028545822381301[137] = 0;
   out_3871028545822381301[138] = 0;
   out_3871028545822381301[139] = 0;
   out_3871028545822381301[140] = 0;
   out_3871028545822381301[141] = 0;
   out_3871028545822381301[142] = 0;
   out_3871028545822381301[143] = 0;
   out_3871028545822381301[144] = 0;
   out_3871028545822381301[145] = 0;
   out_3871028545822381301[146] = 0;
   out_3871028545822381301[147] = 0;
   out_3871028545822381301[148] = 0;
   out_3871028545822381301[149] = 0;
   out_3871028545822381301[150] = 0;
   out_3871028545822381301[151] = 0;
   out_3871028545822381301[152] = 1;
   out_3871028545822381301[153] = 0;
   out_3871028545822381301[154] = 0;
   out_3871028545822381301[155] = 0;
   out_3871028545822381301[156] = 0;
   out_3871028545822381301[157] = 0;
   out_3871028545822381301[158] = 0;
   out_3871028545822381301[159] = 0;
   out_3871028545822381301[160] = 0;
   out_3871028545822381301[161] = 0;
   out_3871028545822381301[162] = 0;
   out_3871028545822381301[163] = 0;
   out_3871028545822381301[164] = 0;
   out_3871028545822381301[165] = 0;
   out_3871028545822381301[166] = 0;
   out_3871028545822381301[167] = 0;
   out_3871028545822381301[168] = 0;
   out_3871028545822381301[169] = 0;
   out_3871028545822381301[170] = 0;
   out_3871028545822381301[171] = 1;
   out_3871028545822381301[172] = 0;
   out_3871028545822381301[173] = 0;
   out_3871028545822381301[174] = 0;
   out_3871028545822381301[175] = 0;
   out_3871028545822381301[176] = 0;
   out_3871028545822381301[177] = 0;
   out_3871028545822381301[178] = 0;
   out_3871028545822381301[179] = 0;
   out_3871028545822381301[180] = 0;
   out_3871028545822381301[181] = 0;
   out_3871028545822381301[182] = 0;
   out_3871028545822381301[183] = 0;
   out_3871028545822381301[184] = 0;
   out_3871028545822381301[185] = 0;
   out_3871028545822381301[186] = 0;
   out_3871028545822381301[187] = 0;
   out_3871028545822381301[188] = 0;
   out_3871028545822381301[189] = 0;
   out_3871028545822381301[190] = 1;
   out_3871028545822381301[191] = 0;
   out_3871028545822381301[192] = 0;
   out_3871028545822381301[193] = 0;
   out_3871028545822381301[194] = 0;
   out_3871028545822381301[195] = 0;
   out_3871028545822381301[196] = 0;
   out_3871028545822381301[197] = 0;
   out_3871028545822381301[198] = 0;
   out_3871028545822381301[199] = 0;
   out_3871028545822381301[200] = 0;
   out_3871028545822381301[201] = 0;
   out_3871028545822381301[202] = 0;
   out_3871028545822381301[203] = 0;
   out_3871028545822381301[204] = 0;
   out_3871028545822381301[205] = 0;
   out_3871028545822381301[206] = 0;
   out_3871028545822381301[207] = 0;
   out_3871028545822381301[208] = 0;
   out_3871028545822381301[209] = 1;
   out_3871028545822381301[210] = 0;
   out_3871028545822381301[211] = 0;
   out_3871028545822381301[212] = 0;
   out_3871028545822381301[213] = 0;
   out_3871028545822381301[214] = 0;
   out_3871028545822381301[215] = 0;
   out_3871028545822381301[216] = 0;
   out_3871028545822381301[217] = 0;
   out_3871028545822381301[218] = 0;
   out_3871028545822381301[219] = 0;
   out_3871028545822381301[220] = 0;
   out_3871028545822381301[221] = 0;
   out_3871028545822381301[222] = 0;
   out_3871028545822381301[223] = 0;
   out_3871028545822381301[224] = 0;
   out_3871028545822381301[225] = 0;
   out_3871028545822381301[226] = 0;
   out_3871028545822381301[227] = 0;
   out_3871028545822381301[228] = 1;
   out_3871028545822381301[229] = 0;
   out_3871028545822381301[230] = 0;
   out_3871028545822381301[231] = 0;
   out_3871028545822381301[232] = 0;
   out_3871028545822381301[233] = 0;
   out_3871028545822381301[234] = 0;
   out_3871028545822381301[235] = 0;
   out_3871028545822381301[236] = 0;
   out_3871028545822381301[237] = 0;
   out_3871028545822381301[238] = 0;
   out_3871028545822381301[239] = 0;
   out_3871028545822381301[240] = 0;
   out_3871028545822381301[241] = 0;
   out_3871028545822381301[242] = 0;
   out_3871028545822381301[243] = 0;
   out_3871028545822381301[244] = 0;
   out_3871028545822381301[245] = 0;
   out_3871028545822381301[246] = 0;
   out_3871028545822381301[247] = 1;
   out_3871028545822381301[248] = 0;
   out_3871028545822381301[249] = 0;
   out_3871028545822381301[250] = 0;
   out_3871028545822381301[251] = 0;
   out_3871028545822381301[252] = 0;
   out_3871028545822381301[253] = 0;
   out_3871028545822381301[254] = 0;
   out_3871028545822381301[255] = 0;
   out_3871028545822381301[256] = 0;
   out_3871028545822381301[257] = 0;
   out_3871028545822381301[258] = 0;
   out_3871028545822381301[259] = 0;
   out_3871028545822381301[260] = 0;
   out_3871028545822381301[261] = 0;
   out_3871028545822381301[262] = 0;
   out_3871028545822381301[263] = 0;
   out_3871028545822381301[264] = 0;
   out_3871028545822381301[265] = 0;
   out_3871028545822381301[266] = 1;
   out_3871028545822381301[267] = 0;
   out_3871028545822381301[268] = 0;
   out_3871028545822381301[269] = 0;
   out_3871028545822381301[270] = 0;
   out_3871028545822381301[271] = 0;
   out_3871028545822381301[272] = 0;
   out_3871028545822381301[273] = 0;
   out_3871028545822381301[274] = 0;
   out_3871028545822381301[275] = 0;
   out_3871028545822381301[276] = 0;
   out_3871028545822381301[277] = 0;
   out_3871028545822381301[278] = 0;
   out_3871028545822381301[279] = 0;
   out_3871028545822381301[280] = 0;
   out_3871028545822381301[281] = 0;
   out_3871028545822381301[282] = 0;
   out_3871028545822381301[283] = 0;
   out_3871028545822381301[284] = 0;
   out_3871028545822381301[285] = 1;
   out_3871028545822381301[286] = 0;
   out_3871028545822381301[287] = 0;
   out_3871028545822381301[288] = 0;
   out_3871028545822381301[289] = 0;
   out_3871028545822381301[290] = 0;
   out_3871028545822381301[291] = 0;
   out_3871028545822381301[292] = 0;
   out_3871028545822381301[293] = 0;
   out_3871028545822381301[294] = 0;
   out_3871028545822381301[295] = 0;
   out_3871028545822381301[296] = 0;
   out_3871028545822381301[297] = 0;
   out_3871028545822381301[298] = 0;
   out_3871028545822381301[299] = 0;
   out_3871028545822381301[300] = 0;
   out_3871028545822381301[301] = 0;
   out_3871028545822381301[302] = 0;
   out_3871028545822381301[303] = 0;
   out_3871028545822381301[304] = 1;
   out_3871028545822381301[305] = 0;
   out_3871028545822381301[306] = 0;
   out_3871028545822381301[307] = 0;
   out_3871028545822381301[308] = 0;
   out_3871028545822381301[309] = 0;
   out_3871028545822381301[310] = 0;
   out_3871028545822381301[311] = 0;
   out_3871028545822381301[312] = 0;
   out_3871028545822381301[313] = 0;
   out_3871028545822381301[314] = 0;
   out_3871028545822381301[315] = 0;
   out_3871028545822381301[316] = 0;
   out_3871028545822381301[317] = 0;
   out_3871028545822381301[318] = 0;
   out_3871028545822381301[319] = 0;
   out_3871028545822381301[320] = 0;
   out_3871028545822381301[321] = 0;
   out_3871028545822381301[322] = 0;
   out_3871028545822381301[323] = 1;
}
void h_4(double *state, double *unused, double *out_2936144003194801573) {
   out_2936144003194801573[0] = state[6] + state[9];
   out_2936144003194801573[1] = state[7] + state[10];
   out_2936144003194801573[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_591656984978388915) {
   out_591656984978388915[0] = 0;
   out_591656984978388915[1] = 0;
   out_591656984978388915[2] = 0;
   out_591656984978388915[3] = 0;
   out_591656984978388915[4] = 0;
   out_591656984978388915[5] = 0;
   out_591656984978388915[6] = 1;
   out_591656984978388915[7] = 0;
   out_591656984978388915[8] = 0;
   out_591656984978388915[9] = 1;
   out_591656984978388915[10] = 0;
   out_591656984978388915[11] = 0;
   out_591656984978388915[12] = 0;
   out_591656984978388915[13] = 0;
   out_591656984978388915[14] = 0;
   out_591656984978388915[15] = 0;
   out_591656984978388915[16] = 0;
   out_591656984978388915[17] = 0;
   out_591656984978388915[18] = 0;
   out_591656984978388915[19] = 0;
   out_591656984978388915[20] = 0;
   out_591656984978388915[21] = 0;
   out_591656984978388915[22] = 0;
   out_591656984978388915[23] = 0;
   out_591656984978388915[24] = 0;
   out_591656984978388915[25] = 1;
   out_591656984978388915[26] = 0;
   out_591656984978388915[27] = 0;
   out_591656984978388915[28] = 1;
   out_591656984978388915[29] = 0;
   out_591656984978388915[30] = 0;
   out_591656984978388915[31] = 0;
   out_591656984978388915[32] = 0;
   out_591656984978388915[33] = 0;
   out_591656984978388915[34] = 0;
   out_591656984978388915[35] = 0;
   out_591656984978388915[36] = 0;
   out_591656984978388915[37] = 0;
   out_591656984978388915[38] = 0;
   out_591656984978388915[39] = 0;
   out_591656984978388915[40] = 0;
   out_591656984978388915[41] = 0;
   out_591656984978388915[42] = 0;
   out_591656984978388915[43] = 0;
   out_591656984978388915[44] = 1;
   out_591656984978388915[45] = 0;
   out_591656984978388915[46] = 0;
   out_591656984978388915[47] = 1;
   out_591656984978388915[48] = 0;
   out_591656984978388915[49] = 0;
   out_591656984978388915[50] = 0;
   out_591656984978388915[51] = 0;
   out_591656984978388915[52] = 0;
   out_591656984978388915[53] = 0;
}
void h_10(double *state, double *unused, double *out_1737615237719831993) {
   out_1737615237719831993[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1737615237719831993[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1737615237719831993[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4052938281048870893) {
   out_4052938281048870893[0] = 0;
   out_4052938281048870893[1] = 9.8100000000000005*cos(state[1]);
   out_4052938281048870893[2] = 0;
   out_4052938281048870893[3] = 0;
   out_4052938281048870893[4] = -state[8];
   out_4052938281048870893[5] = state[7];
   out_4052938281048870893[6] = 0;
   out_4052938281048870893[7] = state[5];
   out_4052938281048870893[8] = -state[4];
   out_4052938281048870893[9] = 0;
   out_4052938281048870893[10] = 0;
   out_4052938281048870893[11] = 0;
   out_4052938281048870893[12] = 1;
   out_4052938281048870893[13] = 0;
   out_4052938281048870893[14] = 0;
   out_4052938281048870893[15] = 1;
   out_4052938281048870893[16] = 0;
   out_4052938281048870893[17] = 0;
   out_4052938281048870893[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4052938281048870893[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4052938281048870893[20] = 0;
   out_4052938281048870893[21] = state[8];
   out_4052938281048870893[22] = 0;
   out_4052938281048870893[23] = -state[6];
   out_4052938281048870893[24] = -state[5];
   out_4052938281048870893[25] = 0;
   out_4052938281048870893[26] = state[3];
   out_4052938281048870893[27] = 0;
   out_4052938281048870893[28] = 0;
   out_4052938281048870893[29] = 0;
   out_4052938281048870893[30] = 0;
   out_4052938281048870893[31] = 1;
   out_4052938281048870893[32] = 0;
   out_4052938281048870893[33] = 0;
   out_4052938281048870893[34] = 1;
   out_4052938281048870893[35] = 0;
   out_4052938281048870893[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4052938281048870893[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4052938281048870893[38] = 0;
   out_4052938281048870893[39] = -state[7];
   out_4052938281048870893[40] = state[6];
   out_4052938281048870893[41] = 0;
   out_4052938281048870893[42] = state[4];
   out_4052938281048870893[43] = -state[3];
   out_4052938281048870893[44] = 0;
   out_4052938281048870893[45] = 0;
   out_4052938281048870893[46] = 0;
   out_4052938281048870893[47] = 0;
   out_4052938281048870893[48] = 0;
   out_4052938281048870893[49] = 0;
   out_4052938281048870893[50] = 1;
   out_4052938281048870893[51] = 0;
   out_4052938281048870893[52] = 0;
   out_4052938281048870893[53] = 1;
}
void h_13(double *state, double *unused, double *out_4819018816793413092) {
   out_4819018816793413092[0] = state[3];
   out_4819018816793413092[1] = state[4];
   out_4819018816793413092[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8202288193295089844) {
   out_8202288193295089844[0] = 0;
   out_8202288193295089844[1] = 0;
   out_8202288193295089844[2] = 0;
   out_8202288193295089844[3] = 1;
   out_8202288193295089844[4] = 0;
   out_8202288193295089844[5] = 0;
   out_8202288193295089844[6] = 0;
   out_8202288193295089844[7] = 0;
   out_8202288193295089844[8] = 0;
   out_8202288193295089844[9] = 0;
   out_8202288193295089844[10] = 0;
   out_8202288193295089844[11] = 0;
   out_8202288193295089844[12] = 0;
   out_8202288193295089844[13] = 0;
   out_8202288193295089844[14] = 0;
   out_8202288193295089844[15] = 0;
   out_8202288193295089844[16] = 0;
   out_8202288193295089844[17] = 0;
   out_8202288193295089844[18] = 0;
   out_8202288193295089844[19] = 0;
   out_8202288193295089844[20] = 0;
   out_8202288193295089844[21] = 0;
   out_8202288193295089844[22] = 1;
   out_8202288193295089844[23] = 0;
   out_8202288193295089844[24] = 0;
   out_8202288193295089844[25] = 0;
   out_8202288193295089844[26] = 0;
   out_8202288193295089844[27] = 0;
   out_8202288193295089844[28] = 0;
   out_8202288193295089844[29] = 0;
   out_8202288193295089844[30] = 0;
   out_8202288193295089844[31] = 0;
   out_8202288193295089844[32] = 0;
   out_8202288193295089844[33] = 0;
   out_8202288193295089844[34] = 0;
   out_8202288193295089844[35] = 0;
   out_8202288193295089844[36] = 0;
   out_8202288193295089844[37] = 0;
   out_8202288193295089844[38] = 0;
   out_8202288193295089844[39] = 0;
   out_8202288193295089844[40] = 0;
   out_8202288193295089844[41] = 1;
   out_8202288193295089844[42] = 0;
   out_8202288193295089844[43] = 0;
   out_8202288193295089844[44] = 0;
   out_8202288193295089844[45] = 0;
   out_8202288193295089844[46] = 0;
   out_8202288193295089844[47] = 0;
   out_8202288193295089844[48] = 0;
   out_8202288193295089844[49] = 0;
   out_8202288193295089844[50] = 0;
   out_8202288193295089844[51] = 0;
   out_8202288193295089844[52] = 0;
   out_8202288193295089844[53] = 0;
}
void h_14(double *state, double *unused, double *out_5456552129190884631) {
   out_5456552129190884631[0] = state[6];
   out_5456552129190884631[1] = state[7];
   out_5456552129190884631[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2491131447316983381) {
   out_2491131447316983381[0] = 0;
   out_2491131447316983381[1] = 0;
   out_2491131447316983381[2] = 0;
   out_2491131447316983381[3] = 0;
   out_2491131447316983381[4] = 0;
   out_2491131447316983381[5] = 0;
   out_2491131447316983381[6] = 1;
   out_2491131447316983381[7] = 0;
   out_2491131447316983381[8] = 0;
   out_2491131447316983381[9] = 0;
   out_2491131447316983381[10] = 0;
   out_2491131447316983381[11] = 0;
   out_2491131447316983381[12] = 0;
   out_2491131447316983381[13] = 0;
   out_2491131447316983381[14] = 0;
   out_2491131447316983381[15] = 0;
   out_2491131447316983381[16] = 0;
   out_2491131447316983381[17] = 0;
   out_2491131447316983381[18] = 0;
   out_2491131447316983381[19] = 0;
   out_2491131447316983381[20] = 0;
   out_2491131447316983381[21] = 0;
   out_2491131447316983381[22] = 0;
   out_2491131447316983381[23] = 0;
   out_2491131447316983381[24] = 0;
   out_2491131447316983381[25] = 1;
   out_2491131447316983381[26] = 0;
   out_2491131447316983381[27] = 0;
   out_2491131447316983381[28] = 0;
   out_2491131447316983381[29] = 0;
   out_2491131447316983381[30] = 0;
   out_2491131447316983381[31] = 0;
   out_2491131447316983381[32] = 0;
   out_2491131447316983381[33] = 0;
   out_2491131447316983381[34] = 0;
   out_2491131447316983381[35] = 0;
   out_2491131447316983381[36] = 0;
   out_2491131447316983381[37] = 0;
   out_2491131447316983381[38] = 0;
   out_2491131447316983381[39] = 0;
   out_2491131447316983381[40] = 0;
   out_2491131447316983381[41] = 0;
   out_2491131447316983381[42] = 0;
   out_2491131447316983381[43] = 0;
   out_2491131447316983381[44] = 1;
   out_2491131447316983381[45] = 0;
   out_2491131447316983381[46] = 0;
   out_2491131447316983381[47] = 0;
   out_2491131447316983381[48] = 0;
   out_2491131447316983381[49] = 0;
   out_2491131447316983381[50] = 0;
   out_2491131447316983381[51] = 0;
   out_2491131447316983381[52] = 0;
   out_2491131447316983381[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1813739608873815140) {
  err_fun(nom_x, delta_x, out_1813739608873815140);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8036368585793301884) {
  inv_err_fun(nom_x, true_x, out_8036368585793301884);
}
void pose_H_mod_fun(double *state, double *out_3792066886079858939) {
  H_mod_fun(state, out_3792066886079858939);
}
void pose_f_fun(double *state, double dt, double *out_8697136999633362847) {
  f_fun(state,  dt, out_8697136999633362847);
}
void pose_F_fun(double *state, double dt, double *out_3871028545822381301) {
  F_fun(state,  dt, out_3871028545822381301);
}
void pose_h_4(double *state, double *unused, double *out_2936144003194801573) {
  h_4(state, unused, out_2936144003194801573);
}
void pose_H_4(double *state, double *unused, double *out_591656984978388915) {
  H_4(state, unused, out_591656984978388915);
}
void pose_h_10(double *state, double *unused, double *out_1737615237719831993) {
  h_10(state, unused, out_1737615237719831993);
}
void pose_H_10(double *state, double *unused, double *out_4052938281048870893) {
  H_10(state, unused, out_4052938281048870893);
}
void pose_h_13(double *state, double *unused, double *out_4819018816793413092) {
  h_13(state, unused, out_4819018816793413092);
}
void pose_H_13(double *state, double *unused, double *out_8202288193295089844) {
  H_13(state, unused, out_8202288193295089844);
}
void pose_h_14(double *state, double *unused, double *out_5456552129190884631) {
  h_14(state, unused, out_5456552129190884631);
}
void pose_H_14(double *state, double *unused, double *out_2491131447316983381) {
  H_14(state, unused, out_2491131447316983381);
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
