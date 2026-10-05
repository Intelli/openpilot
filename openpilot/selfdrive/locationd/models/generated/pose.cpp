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
void err_fun(double *nom_x, double *delta_x, double *out_2561165156665466750) {
   out_2561165156665466750[0] = delta_x[0] + nom_x[0];
   out_2561165156665466750[1] = delta_x[1] + nom_x[1];
   out_2561165156665466750[2] = delta_x[2] + nom_x[2];
   out_2561165156665466750[3] = delta_x[3] + nom_x[3];
   out_2561165156665466750[4] = delta_x[4] + nom_x[4];
   out_2561165156665466750[5] = delta_x[5] + nom_x[5];
   out_2561165156665466750[6] = delta_x[6] + nom_x[6];
   out_2561165156665466750[7] = delta_x[7] + nom_x[7];
   out_2561165156665466750[8] = delta_x[8] + nom_x[8];
   out_2561165156665466750[9] = delta_x[9] + nom_x[9];
   out_2561165156665466750[10] = delta_x[10] + nom_x[10];
   out_2561165156665466750[11] = delta_x[11] + nom_x[11];
   out_2561165156665466750[12] = delta_x[12] + nom_x[12];
   out_2561165156665466750[13] = delta_x[13] + nom_x[13];
   out_2561165156665466750[14] = delta_x[14] + nom_x[14];
   out_2561165156665466750[15] = delta_x[15] + nom_x[15];
   out_2561165156665466750[16] = delta_x[16] + nom_x[16];
   out_2561165156665466750[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1962872074544000331) {
   out_1962872074544000331[0] = -nom_x[0] + true_x[0];
   out_1962872074544000331[1] = -nom_x[1] + true_x[1];
   out_1962872074544000331[2] = -nom_x[2] + true_x[2];
   out_1962872074544000331[3] = -nom_x[3] + true_x[3];
   out_1962872074544000331[4] = -nom_x[4] + true_x[4];
   out_1962872074544000331[5] = -nom_x[5] + true_x[5];
   out_1962872074544000331[6] = -nom_x[6] + true_x[6];
   out_1962872074544000331[7] = -nom_x[7] + true_x[7];
   out_1962872074544000331[8] = -nom_x[8] + true_x[8];
   out_1962872074544000331[9] = -nom_x[9] + true_x[9];
   out_1962872074544000331[10] = -nom_x[10] + true_x[10];
   out_1962872074544000331[11] = -nom_x[11] + true_x[11];
   out_1962872074544000331[12] = -nom_x[12] + true_x[12];
   out_1962872074544000331[13] = -nom_x[13] + true_x[13];
   out_1962872074544000331[14] = -nom_x[14] + true_x[14];
   out_1962872074544000331[15] = -nom_x[15] + true_x[15];
   out_1962872074544000331[16] = -nom_x[16] + true_x[16];
   out_1962872074544000331[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_279889982478867027) {
   out_279889982478867027[0] = 1.0;
   out_279889982478867027[1] = 0.0;
   out_279889982478867027[2] = 0.0;
   out_279889982478867027[3] = 0.0;
   out_279889982478867027[4] = 0.0;
   out_279889982478867027[5] = 0.0;
   out_279889982478867027[6] = 0.0;
   out_279889982478867027[7] = 0.0;
   out_279889982478867027[8] = 0.0;
   out_279889982478867027[9] = 0.0;
   out_279889982478867027[10] = 0.0;
   out_279889982478867027[11] = 0.0;
   out_279889982478867027[12] = 0.0;
   out_279889982478867027[13] = 0.0;
   out_279889982478867027[14] = 0.0;
   out_279889982478867027[15] = 0.0;
   out_279889982478867027[16] = 0.0;
   out_279889982478867027[17] = 0.0;
   out_279889982478867027[18] = 0.0;
   out_279889982478867027[19] = 1.0;
   out_279889982478867027[20] = 0.0;
   out_279889982478867027[21] = 0.0;
   out_279889982478867027[22] = 0.0;
   out_279889982478867027[23] = 0.0;
   out_279889982478867027[24] = 0.0;
   out_279889982478867027[25] = 0.0;
   out_279889982478867027[26] = 0.0;
   out_279889982478867027[27] = 0.0;
   out_279889982478867027[28] = 0.0;
   out_279889982478867027[29] = 0.0;
   out_279889982478867027[30] = 0.0;
   out_279889982478867027[31] = 0.0;
   out_279889982478867027[32] = 0.0;
   out_279889982478867027[33] = 0.0;
   out_279889982478867027[34] = 0.0;
   out_279889982478867027[35] = 0.0;
   out_279889982478867027[36] = 0.0;
   out_279889982478867027[37] = 0.0;
   out_279889982478867027[38] = 1.0;
   out_279889982478867027[39] = 0.0;
   out_279889982478867027[40] = 0.0;
   out_279889982478867027[41] = 0.0;
   out_279889982478867027[42] = 0.0;
   out_279889982478867027[43] = 0.0;
   out_279889982478867027[44] = 0.0;
   out_279889982478867027[45] = 0.0;
   out_279889982478867027[46] = 0.0;
   out_279889982478867027[47] = 0.0;
   out_279889982478867027[48] = 0.0;
   out_279889982478867027[49] = 0.0;
   out_279889982478867027[50] = 0.0;
   out_279889982478867027[51] = 0.0;
   out_279889982478867027[52] = 0.0;
   out_279889982478867027[53] = 0.0;
   out_279889982478867027[54] = 0.0;
   out_279889982478867027[55] = 0.0;
   out_279889982478867027[56] = 0.0;
   out_279889982478867027[57] = 1.0;
   out_279889982478867027[58] = 0.0;
   out_279889982478867027[59] = 0.0;
   out_279889982478867027[60] = 0.0;
   out_279889982478867027[61] = 0.0;
   out_279889982478867027[62] = 0.0;
   out_279889982478867027[63] = 0.0;
   out_279889982478867027[64] = 0.0;
   out_279889982478867027[65] = 0.0;
   out_279889982478867027[66] = 0.0;
   out_279889982478867027[67] = 0.0;
   out_279889982478867027[68] = 0.0;
   out_279889982478867027[69] = 0.0;
   out_279889982478867027[70] = 0.0;
   out_279889982478867027[71] = 0.0;
   out_279889982478867027[72] = 0.0;
   out_279889982478867027[73] = 0.0;
   out_279889982478867027[74] = 0.0;
   out_279889982478867027[75] = 0.0;
   out_279889982478867027[76] = 1.0;
   out_279889982478867027[77] = 0.0;
   out_279889982478867027[78] = 0.0;
   out_279889982478867027[79] = 0.0;
   out_279889982478867027[80] = 0.0;
   out_279889982478867027[81] = 0.0;
   out_279889982478867027[82] = 0.0;
   out_279889982478867027[83] = 0.0;
   out_279889982478867027[84] = 0.0;
   out_279889982478867027[85] = 0.0;
   out_279889982478867027[86] = 0.0;
   out_279889982478867027[87] = 0.0;
   out_279889982478867027[88] = 0.0;
   out_279889982478867027[89] = 0.0;
   out_279889982478867027[90] = 0.0;
   out_279889982478867027[91] = 0.0;
   out_279889982478867027[92] = 0.0;
   out_279889982478867027[93] = 0.0;
   out_279889982478867027[94] = 0.0;
   out_279889982478867027[95] = 1.0;
   out_279889982478867027[96] = 0.0;
   out_279889982478867027[97] = 0.0;
   out_279889982478867027[98] = 0.0;
   out_279889982478867027[99] = 0.0;
   out_279889982478867027[100] = 0.0;
   out_279889982478867027[101] = 0.0;
   out_279889982478867027[102] = 0.0;
   out_279889982478867027[103] = 0.0;
   out_279889982478867027[104] = 0.0;
   out_279889982478867027[105] = 0.0;
   out_279889982478867027[106] = 0.0;
   out_279889982478867027[107] = 0.0;
   out_279889982478867027[108] = 0.0;
   out_279889982478867027[109] = 0.0;
   out_279889982478867027[110] = 0.0;
   out_279889982478867027[111] = 0.0;
   out_279889982478867027[112] = 0.0;
   out_279889982478867027[113] = 0.0;
   out_279889982478867027[114] = 1.0;
   out_279889982478867027[115] = 0.0;
   out_279889982478867027[116] = 0.0;
   out_279889982478867027[117] = 0.0;
   out_279889982478867027[118] = 0.0;
   out_279889982478867027[119] = 0.0;
   out_279889982478867027[120] = 0.0;
   out_279889982478867027[121] = 0.0;
   out_279889982478867027[122] = 0.0;
   out_279889982478867027[123] = 0.0;
   out_279889982478867027[124] = 0.0;
   out_279889982478867027[125] = 0.0;
   out_279889982478867027[126] = 0.0;
   out_279889982478867027[127] = 0.0;
   out_279889982478867027[128] = 0.0;
   out_279889982478867027[129] = 0.0;
   out_279889982478867027[130] = 0.0;
   out_279889982478867027[131] = 0.0;
   out_279889982478867027[132] = 0.0;
   out_279889982478867027[133] = 1.0;
   out_279889982478867027[134] = 0.0;
   out_279889982478867027[135] = 0.0;
   out_279889982478867027[136] = 0.0;
   out_279889982478867027[137] = 0.0;
   out_279889982478867027[138] = 0.0;
   out_279889982478867027[139] = 0.0;
   out_279889982478867027[140] = 0.0;
   out_279889982478867027[141] = 0.0;
   out_279889982478867027[142] = 0.0;
   out_279889982478867027[143] = 0.0;
   out_279889982478867027[144] = 0.0;
   out_279889982478867027[145] = 0.0;
   out_279889982478867027[146] = 0.0;
   out_279889982478867027[147] = 0.0;
   out_279889982478867027[148] = 0.0;
   out_279889982478867027[149] = 0.0;
   out_279889982478867027[150] = 0.0;
   out_279889982478867027[151] = 0.0;
   out_279889982478867027[152] = 1.0;
   out_279889982478867027[153] = 0.0;
   out_279889982478867027[154] = 0.0;
   out_279889982478867027[155] = 0.0;
   out_279889982478867027[156] = 0.0;
   out_279889982478867027[157] = 0.0;
   out_279889982478867027[158] = 0.0;
   out_279889982478867027[159] = 0.0;
   out_279889982478867027[160] = 0.0;
   out_279889982478867027[161] = 0.0;
   out_279889982478867027[162] = 0.0;
   out_279889982478867027[163] = 0.0;
   out_279889982478867027[164] = 0.0;
   out_279889982478867027[165] = 0.0;
   out_279889982478867027[166] = 0.0;
   out_279889982478867027[167] = 0.0;
   out_279889982478867027[168] = 0.0;
   out_279889982478867027[169] = 0.0;
   out_279889982478867027[170] = 0.0;
   out_279889982478867027[171] = 1.0;
   out_279889982478867027[172] = 0.0;
   out_279889982478867027[173] = 0.0;
   out_279889982478867027[174] = 0.0;
   out_279889982478867027[175] = 0.0;
   out_279889982478867027[176] = 0.0;
   out_279889982478867027[177] = 0.0;
   out_279889982478867027[178] = 0.0;
   out_279889982478867027[179] = 0.0;
   out_279889982478867027[180] = 0.0;
   out_279889982478867027[181] = 0.0;
   out_279889982478867027[182] = 0.0;
   out_279889982478867027[183] = 0.0;
   out_279889982478867027[184] = 0.0;
   out_279889982478867027[185] = 0.0;
   out_279889982478867027[186] = 0.0;
   out_279889982478867027[187] = 0.0;
   out_279889982478867027[188] = 0.0;
   out_279889982478867027[189] = 0.0;
   out_279889982478867027[190] = 1.0;
   out_279889982478867027[191] = 0.0;
   out_279889982478867027[192] = 0.0;
   out_279889982478867027[193] = 0.0;
   out_279889982478867027[194] = 0.0;
   out_279889982478867027[195] = 0.0;
   out_279889982478867027[196] = 0.0;
   out_279889982478867027[197] = 0.0;
   out_279889982478867027[198] = 0.0;
   out_279889982478867027[199] = 0.0;
   out_279889982478867027[200] = 0.0;
   out_279889982478867027[201] = 0.0;
   out_279889982478867027[202] = 0.0;
   out_279889982478867027[203] = 0.0;
   out_279889982478867027[204] = 0.0;
   out_279889982478867027[205] = 0.0;
   out_279889982478867027[206] = 0.0;
   out_279889982478867027[207] = 0.0;
   out_279889982478867027[208] = 0.0;
   out_279889982478867027[209] = 1.0;
   out_279889982478867027[210] = 0.0;
   out_279889982478867027[211] = 0.0;
   out_279889982478867027[212] = 0.0;
   out_279889982478867027[213] = 0.0;
   out_279889982478867027[214] = 0.0;
   out_279889982478867027[215] = 0.0;
   out_279889982478867027[216] = 0.0;
   out_279889982478867027[217] = 0.0;
   out_279889982478867027[218] = 0.0;
   out_279889982478867027[219] = 0.0;
   out_279889982478867027[220] = 0.0;
   out_279889982478867027[221] = 0.0;
   out_279889982478867027[222] = 0.0;
   out_279889982478867027[223] = 0.0;
   out_279889982478867027[224] = 0.0;
   out_279889982478867027[225] = 0.0;
   out_279889982478867027[226] = 0.0;
   out_279889982478867027[227] = 0.0;
   out_279889982478867027[228] = 1.0;
   out_279889982478867027[229] = 0.0;
   out_279889982478867027[230] = 0.0;
   out_279889982478867027[231] = 0.0;
   out_279889982478867027[232] = 0.0;
   out_279889982478867027[233] = 0.0;
   out_279889982478867027[234] = 0.0;
   out_279889982478867027[235] = 0.0;
   out_279889982478867027[236] = 0.0;
   out_279889982478867027[237] = 0.0;
   out_279889982478867027[238] = 0.0;
   out_279889982478867027[239] = 0.0;
   out_279889982478867027[240] = 0.0;
   out_279889982478867027[241] = 0.0;
   out_279889982478867027[242] = 0.0;
   out_279889982478867027[243] = 0.0;
   out_279889982478867027[244] = 0.0;
   out_279889982478867027[245] = 0.0;
   out_279889982478867027[246] = 0.0;
   out_279889982478867027[247] = 1.0;
   out_279889982478867027[248] = 0.0;
   out_279889982478867027[249] = 0.0;
   out_279889982478867027[250] = 0.0;
   out_279889982478867027[251] = 0.0;
   out_279889982478867027[252] = 0.0;
   out_279889982478867027[253] = 0.0;
   out_279889982478867027[254] = 0.0;
   out_279889982478867027[255] = 0.0;
   out_279889982478867027[256] = 0.0;
   out_279889982478867027[257] = 0.0;
   out_279889982478867027[258] = 0.0;
   out_279889982478867027[259] = 0.0;
   out_279889982478867027[260] = 0.0;
   out_279889982478867027[261] = 0.0;
   out_279889982478867027[262] = 0.0;
   out_279889982478867027[263] = 0.0;
   out_279889982478867027[264] = 0.0;
   out_279889982478867027[265] = 0.0;
   out_279889982478867027[266] = 1.0;
   out_279889982478867027[267] = 0.0;
   out_279889982478867027[268] = 0.0;
   out_279889982478867027[269] = 0.0;
   out_279889982478867027[270] = 0.0;
   out_279889982478867027[271] = 0.0;
   out_279889982478867027[272] = 0.0;
   out_279889982478867027[273] = 0.0;
   out_279889982478867027[274] = 0.0;
   out_279889982478867027[275] = 0.0;
   out_279889982478867027[276] = 0.0;
   out_279889982478867027[277] = 0.0;
   out_279889982478867027[278] = 0.0;
   out_279889982478867027[279] = 0.0;
   out_279889982478867027[280] = 0.0;
   out_279889982478867027[281] = 0.0;
   out_279889982478867027[282] = 0.0;
   out_279889982478867027[283] = 0.0;
   out_279889982478867027[284] = 0.0;
   out_279889982478867027[285] = 1.0;
   out_279889982478867027[286] = 0.0;
   out_279889982478867027[287] = 0.0;
   out_279889982478867027[288] = 0.0;
   out_279889982478867027[289] = 0.0;
   out_279889982478867027[290] = 0.0;
   out_279889982478867027[291] = 0.0;
   out_279889982478867027[292] = 0.0;
   out_279889982478867027[293] = 0.0;
   out_279889982478867027[294] = 0.0;
   out_279889982478867027[295] = 0.0;
   out_279889982478867027[296] = 0.0;
   out_279889982478867027[297] = 0.0;
   out_279889982478867027[298] = 0.0;
   out_279889982478867027[299] = 0.0;
   out_279889982478867027[300] = 0.0;
   out_279889982478867027[301] = 0.0;
   out_279889982478867027[302] = 0.0;
   out_279889982478867027[303] = 0.0;
   out_279889982478867027[304] = 1.0;
   out_279889982478867027[305] = 0.0;
   out_279889982478867027[306] = 0.0;
   out_279889982478867027[307] = 0.0;
   out_279889982478867027[308] = 0.0;
   out_279889982478867027[309] = 0.0;
   out_279889982478867027[310] = 0.0;
   out_279889982478867027[311] = 0.0;
   out_279889982478867027[312] = 0.0;
   out_279889982478867027[313] = 0.0;
   out_279889982478867027[314] = 0.0;
   out_279889982478867027[315] = 0.0;
   out_279889982478867027[316] = 0.0;
   out_279889982478867027[317] = 0.0;
   out_279889982478867027[318] = 0.0;
   out_279889982478867027[319] = 0.0;
   out_279889982478867027[320] = 0.0;
   out_279889982478867027[321] = 0.0;
   out_279889982478867027[322] = 0.0;
   out_279889982478867027[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3993756686932435860) {
   out_3993756686932435860[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3993756686932435860[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3993756686932435860[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3993756686932435860[3] = dt*state[12] + state[3];
   out_3993756686932435860[4] = dt*state[13] + state[4];
   out_3993756686932435860[5] = dt*state[14] + state[5];
   out_3993756686932435860[6] = state[6];
   out_3993756686932435860[7] = state[7];
   out_3993756686932435860[8] = state[8];
   out_3993756686932435860[9] = state[9];
   out_3993756686932435860[10] = state[10];
   out_3993756686932435860[11] = state[11];
   out_3993756686932435860[12] = state[12];
   out_3993756686932435860[13] = state[13];
   out_3993756686932435860[14] = state[14];
   out_3993756686932435860[15] = state[15];
   out_3993756686932435860[16] = state[16];
   out_3993756686932435860[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8805999151920846348) {
   out_8805999151920846348[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8805999151920846348[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8805999151920846348[2] = 0;
   out_8805999151920846348[3] = 0;
   out_8805999151920846348[4] = 0;
   out_8805999151920846348[5] = 0;
   out_8805999151920846348[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8805999151920846348[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8805999151920846348[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8805999151920846348[9] = 0;
   out_8805999151920846348[10] = 0;
   out_8805999151920846348[11] = 0;
   out_8805999151920846348[12] = 0;
   out_8805999151920846348[13] = 0;
   out_8805999151920846348[14] = 0;
   out_8805999151920846348[15] = 0;
   out_8805999151920846348[16] = 0;
   out_8805999151920846348[17] = 0;
   out_8805999151920846348[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8805999151920846348[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8805999151920846348[20] = 0;
   out_8805999151920846348[21] = 0;
   out_8805999151920846348[22] = 0;
   out_8805999151920846348[23] = 0;
   out_8805999151920846348[24] = 0;
   out_8805999151920846348[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8805999151920846348[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8805999151920846348[27] = 0;
   out_8805999151920846348[28] = 0;
   out_8805999151920846348[29] = 0;
   out_8805999151920846348[30] = 0;
   out_8805999151920846348[31] = 0;
   out_8805999151920846348[32] = 0;
   out_8805999151920846348[33] = 0;
   out_8805999151920846348[34] = 0;
   out_8805999151920846348[35] = 0;
   out_8805999151920846348[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8805999151920846348[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8805999151920846348[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8805999151920846348[39] = 0;
   out_8805999151920846348[40] = 0;
   out_8805999151920846348[41] = 0;
   out_8805999151920846348[42] = 0;
   out_8805999151920846348[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8805999151920846348[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8805999151920846348[45] = 0;
   out_8805999151920846348[46] = 0;
   out_8805999151920846348[47] = 0;
   out_8805999151920846348[48] = 0;
   out_8805999151920846348[49] = 0;
   out_8805999151920846348[50] = 0;
   out_8805999151920846348[51] = 0;
   out_8805999151920846348[52] = 0;
   out_8805999151920846348[53] = 0;
   out_8805999151920846348[54] = 0;
   out_8805999151920846348[55] = 0;
   out_8805999151920846348[56] = 0;
   out_8805999151920846348[57] = 1;
   out_8805999151920846348[58] = 0;
   out_8805999151920846348[59] = 0;
   out_8805999151920846348[60] = 0;
   out_8805999151920846348[61] = 0;
   out_8805999151920846348[62] = 0;
   out_8805999151920846348[63] = 0;
   out_8805999151920846348[64] = 0;
   out_8805999151920846348[65] = 0;
   out_8805999151920846348[66] = dt;
   out_8805999151920846348[67] = 0;
   out_8805999151920846348[68] = 0;
   out_8805999151920846348[69] = 0;
   out_8805999151920846348[70] = 0;
   out_8805999151920846348[71] = 0;
   out_8805999151920846348[72] = 0;
   out_8805999151920846348[73] = 0;
   out_8805999151920846348[74] = 0;
   out_8805999151920846348[75] = 0;
   out_8805999151920846348[76] = 1;
   out_8805999151920846348[77] = 0;
   out_8805999151920846348[78] = 0;
   out_8805999151920846348[79] = 0;
   out_8805999151920846348[80] = 0;
   out_8805999151920846348[81] = 0;
   out_8805999151920846348[82] = 0;
   out_8805999151920846348[83] = 0;
   out_8805999151920846348[84] = 0;
   out_8805999151920846348[85] = dt;
   out_8805999151920846348[86] = 0;
   out_8805999151920846348[87] = 0;
   out_8805999151920846348[88] = 0;
   out_8805999151920846348[89] = 0;
   out_8805999151920846348[90] = 0;
   out_8805999151920846348[91] = 0;
   out_8805999151920846348[92] = 0;
   out_8805999151920846348[93] = 0;
   out_8805999151920846348[94] = 0;
   out_8805999151920846348[95] = 1;
   out_8805999151920846348[96] = 0;
   out_8805999151920846348[97] = 0;
   out_8805999151920846348[98] = 0;
   out_8805999151920846348[99] = 0;
   out_8805999151920846348[100] = 0;
   out_8805999151920846348[101] = 0;
   out_8805999151920846348[102] = 0;
   out_8805999151920846348[103] = 0;
   out_8805999151920846348[104] = dt;
   out_8805999151920846348[105] = 0;
   out_8805999151920846348[106] = 0;
   out_8805999151920846348[107] = 0;
   out_8805999151920846348[108] = 0;
   out_8805999151920846348[109] = 0;
   out_8805999151920846348[110] = 0;
   out_8805999151920846348[111] = 0;
   out_8805999151920846348[112] = 0;
   out_8805999151920846348[113] = 0;
   out_8805999151920846348[114] = 1;
   out_8805999151920846348[115] = 0;
   out_8805999151920846348[116] = 0;
   out_8805999151920846348[117] = 0;
   out_8805999151920846348[118] = 0;
   out_8805999151920846348[119] = 0;
   out_8805999151920846348[120] = 0;
   out_8805999151920846348[121] = 0;
   out_8805999151920846348[122] = 0;
   out_8805999151920846348[123] = 0;
   out_8805999151920846348[124] = 0;
   out_8805999151920846348[125] = 0;
   out_8805999151920846348[126] = 0;
   out_8805999151920846348[127] = 0;
   out_8805999151920846348[128] = 0;
   out_8805999151920846348[129] = 0;
   out_8805999151920846348[130] = 0;
   out_8805999151920846348[131] = 0;
   out_8805999151920846348[132] = 0;
   out_8805999151920846348[133] = 1;
   out_8805999151920846348[134] = 0;
   out_8805999151920846348[135] = 0;
   out_8805999151920846348[136] = 0;
   out_8805999151920846348[137] = 0;
   out_8805999151920846348[138] = 0;
   out_8805999151920846348[139] = 0;
   out_8805999151920846348[140] = 0;
   out_8805999151920846348[141] = 0;
   out_8805999151920846348[142] = 0;
   out_8805999151920846348[143] = 0;
   out_8805999151920846348[144] = 0;
   out_8805999151920846348[145] = 0;
   out_8805999151920846348[146] = 0;
   out_8805999151920846348[147] = 0;
   out_8805999151920846348[148] = 0;
   out_8805999151920846348[149] = 0;
   out_8805999151920846348[150] = 0;
   out_8805999151920846348[151] = 0;
   out_8805999151920846348[152] = 1;
   out_8805999151920846348[153] = 0;
   out_8805999151920846348[154] = 0;
   out_8805999151920846348[155] = 0;
   out_8805999151920846348[156] = 0;
   out_8805999151920846348[157] = 0;
   out_8805999151920846348[158] = 0;
   out_8805999151920846348[159] = 0;
   out_8805999151920846348[160] = 0;
   out_8805999151920846348[161] = 0;
   out_8805999151920846348[162] = 0;
   out_8805999151920846348[163] = 0;
   out_8805999151920846348[164] = 0;
   out_8805999151920846348[165] = 0;
   out_8805999151920846348[166] = 0;
   out_8805999151920846348[167] = 0;
   out_8805999151920846348[168] = 0;
   out_8805999151920846348[169] = 0;
   out_8805999151920846348[170] = 0;
   out_8805999151920846348[171] = 1;
   out_8805999151920846348[172] = 0;
   out_8805999151920846348[173] = 0;
   out_8805999151920846348[174] = 0;
   out_8805999151920846348[175] = 0;
   out_8805999151920846348[176] = 0;
   out_8805999151920846348[177] = 0;
   out_8805999151920846348[178] = 0;
   out_8805999151920846348[179] = 0;
   out_8805999151920846348[180] = 0;
   out_8805999151920846348[181] = 0;
   out_8805999151920846348[182] = 0;
   out_8805999151920846348[183] = 0;
   out_8805999151920846348[184] = 0;
   out_8805999151920846348[185] = 0;
   out_8805999151920846348[186] = 0;
   out_8805999151920846348[187] = 0;
   out_8805999151920846348[188] = 0;
   out_8805999151920846348[189] = 0;
   out_8805999151920846348[190] = 1;
   out_8805999151920846348[191] = 0;
   out_8805999151920846348[192] = 0;
   out_8805999151920846348[193] = 0;
   out_8805999151920846348[194] = 0;
   out_8805999151920846348[195] = 0;
   out_8805999151920846348[196] = 0;
   out_8805999151920846348[197] = 0;
   out_8805999151920846348[198] = 0;
   out_8805999151920846348[199] = 0;
   out_8805999151920846348[200] = 0;
   out_8805999151920846348[201] = 0;
   out_8805999151920846348[202] = 0;
   out_8805999151920846348[203] = 0;
   out_8805999151920846348[204] = 0;
   out_8805999151920846348[205] = 0;
   out_8805999151920846348[206] = 0;
   out_8805999151920846348[207] = 0;
   out_8805999151920846348[208] = 0;
   out_8805999151920846348[209] = 1;
   out_8805999151920846348[210] = 0;
   out_8805999151920846348[211] = 0;
   out_8805999151920846348[212] = 0;
   out_8805999151920846348[213] = 0;
   out_8805999151920846348[214] = 0;
   out_8805999151920846348[215] = 0;
   out_8805999151920846348[216] = 0;
   out_8805999151920846348[217] = 0;
   out_8805999151920846348[218] = 0;
   out_8805999151920846348[219] = 0;
   out_8805999151920846348[220] = 0;
   out_8805999151920846348[221] = 0;
   out_8805999151920846348[222] = 0;
   out_8805999151920846348[223] = 0;
   out_8805999151920846348[224] = 0;
   out_8805999151920846348[225] = 0;
   out_8805999151920846348[226] = 0;
   out_8805999151920846348[227] = 0;
   out_8805999151920846348[228] = 1;
   out_8805999151920846348[229] = 0;
   out_8805999151920846348[230] = 0;
   out_8805999151920846348[231] = 0;
   out_8805999151920846348[232] = 0;
   out_8805999151920846348[233] = 0;
   out_8805999151920846348[234] = 0;
   out_8805999151920846348[235] = 0;
   out_8805999151920846348[236] = 0;
   out_8805999151920846348[237] = 0;
   out_8805999151920846348[238] = 0;
   out_8805999151920846348[239] = 0;
   out_8805999151920846348[240] = 0;
   out_8805999151920846348[241] = 0;
   out_8805999151920846348[242] = 0;
   out_8805999151920846348[243] = 0;
   out_8805999151920846348[244] = 0;
   out_8805999151920846348[245] = 0;
   out_8805999151920846348[246] = 0;
   out_8805999151920846348[247] = 1;
   out_8805999151920846348[248] = 0;
   out_8805999151920846348[249] = 0;
   out_8805999151920846348[250] = 0;
   out_8805999151920846348[251] = 0;
   out_8805999151920846348[252] = 0;
   out_8805999151920846348[253] = 0;
   out_8805999151920846348[254] = 0;
   out_8805999151920846348[255] = 0;
   out_8805999151920846348[256] = 0;
   out_8805999151920846348[257] = 0;
   out_8805999151920846348[258] = 0;
   out_8805999151920846348[259] = 0;
   out_8805999151920846348[260] = 0;
   out_8805999151920846348[261] = 0;
   out_8805999151920846348[262] = 0;
   out_8805999151920846348[263] = 0;
   out_8805999151920846348[264] = 0;
   out_8805999151920846348[265] = 0;
   out_8805999151920846348[266] = 1;
   out_8805999151920846348[267] = 0;
   out_8805999151920846348[268] = 0;
   out_8805999151920846348[269] = 0;
   out_8805999151920846348[270] = 0;
   out_8805999151920846348[271] = 0;
   out_8805999151920846348[272] = 0;
   out_8805999151920846348[273] = 0;
   out_8805999151920846348[274] = 0;
   out_8805999151920846348[275] = 0;
   out_8805999151920846348[276] = 0;
   out_8805999151920846348[277] = 0;
   out_8805999151920846348[278] = 0;
   out_8805999151920846348[279] = 0;
   out_8805999151920846348[280] = 0;
   out_8805999151920846348[281] = 0;
   out_8805999151920846348[282] = 0;
   out_8805999151920846348[283] = 0;
   out_8805999151920846348[284] = 0;
   out_8805999151920846348[285] = 1;
   out_8805999151920846348[286] = 0;
   out_8805999151920846348[287] = 0;
   out_8805999151920846348[288] = 0;
   out_8805999151920846348[289] = 0;
   out_8805999151920846348[290] = 0;
   out_8805999151920846348[291] = 0;
   out_8805999151920846348[292] = 0;
   out_8805999151920846348[293] = 0;
   out_8805999151920846348[294] = 0;
   out_8805999151920846348[295] = 0;
   out_8805999151920846348[296] = 0;
   out_8805999151920846348[297] = 0;
   out_8805999151920846348[298] = 0;
   out_8805999151920846348[299] = 0;
   out_8805999151920846348[300] = 0;
   out_8805999151920846348[301] = 0;
   out_8805999151920846348[302] = 0;
   out_8805999151920846348[303] = 0;
   out_8805999151920846348[304] = 1;
   out_8805999151920846348[305] = 0;
   out_8805999151920846348[306] = 0;
   out_8805999151920846348[307] = 0;
   out_8805999151920846348[308] = 0;
   out_8805999151920846348[309] = 0;
   out_8805999151920846348[310] = 0;
   out_8805999151920846348[311] = 0;
   out_8805999151920846348[312] = 0;
   out_8805999151920846348[313] = 0;
   out_8805999151920846348[314] = 0;
   out_8805999151920846348[315] = 0;
   out_8805999151920846348[316] = 0;
   out_8805999151920846348[317] = 0;
   out_8805999151920846348[318] = 0;
   out_8805999151920846348[319] = 0;
   out_8805999151920846348[320] = 0;
   out_8805999151920846348[321] = 0;
   out_8805999151920846348[322] = 0;
   out_8805999151920846348[323] = 1;
}
void h_4(double *state, double *unused, double *out_704160499582318412) {
   out_704160499582318412[0] = state[6] + state[9];
   out_704160499582318412[1] = state[7] + state[10];
   out_704160499582318412[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6011978304101277191) {
   out_6011978304101277191[0] = 0;
   out_6011978304101277191[1] = 0;
   out_6011978304101277191[2] = 0;
   out_6011978304101277191[3] = 0;
   out_6011978304101277191[4] = 0;
   out_6011978304101277191[5] = 0;
   out_6011978304101277191[6] = 1;
   out_6011978304101277191[7] = 0;
   out_6011978304101277191[8] = 0;
   out_6011978304101277191[9] = 1;
   out_6011978304101277191[10] = 0;
   out_6011978304101277191[11] = 0;
   out_6011978304101277191[12] = 0;
   out_6011978304101277191[13] = 0;
   out_6011978304101277191[14] = 0;
   out_6011978304101277191[15] = 0;
   out_6011978304101277191[16] = 0;
   out_6011978304101277191[17] = 0;
   out_6011978304101277191[18] = 0;
   out_6011978304101277191[19] = 0;
   out_6011978304101277191[20] = 0;
   out_6011978304101277191[21] = 0;
   out_6011978304101277191[22] = 0;
   out_6011978304101277191[23] = 0;
   out_6011978304101277191[24] = 0;
   out_6011978304101277191[25] = 1;
   out_6011978304101277191[26] = 0;
   out_6011978304101277191[27] = 0;
   out_6011978304101277191[28] = 1;
   out_6011978304101277191[29] = 0;
   out_6011978304101277191[30] = 0;
   out_6011978304101277191[31] = 0;
   out_6011978304101277191[32] = 0;
   out_6011978304101277191[33] = 0;
   out_6011978304101277191[34] = 0;
   out_6011978304101277191[35] = 0;
   out_6011978304101277191[36] = 0;
   out_6011978304101277191[37] = 0;
   out_6011978304101277191[38] = 0;
   out_6011978304101277191[39] = 0;
   out_6011978304101277191[40] = 0;
   out_6011978304101277191[41] = 0;
   out_6011978304101277191[42] = 0;
   out_6011978304101277191[43] = 0;
   out_6011978304101277191[44] = 1;
   out_6011978304101277191[45] = 0;
   out_6011978304101277191[46] = 0;
   out_6011978304101277191[47] = 1;
   out_6011978304101277191[48] = 0;
   out_6011978304101277191[49] = 0;
   out_6011978304101277191[50] = 0;
   out_6011978304101277191[51] = 0;
   out_6011978304101277191[52] = 0;
   out_6011978304101277191[53] = 0;
}
void h_10(double *state, double *unused, double *out_3225747117198463437) {
   out_3225747117198463437[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3225747117198463437[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3225747117198463437[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_134585223641373339) {
   out_134585223641373339[0] = 0;
   out_134585223641373339[1] = 9.8100000000000005*cos(state[1]);
   out_134585223641373339[2] = 0;
   out_134585223641373339[3] = 0;
   out_134585223641373339[4] = -state[8];
   out_134585223641373339[5] = state[7];
   out_134585223641373339[6] = 0;
   out_134585223641373339[7] = state[5];
   out_134585223641373339[8] = -state[4];
   out_134585223641373339[9] = 0;
   out_134585223641373339[10] = 0;
   out_134585223641373339[11] = 0;
   out_134585223641373339[12] = 1;
   out_134585223641373339[13] = 0;
   out_134585223641373339[14] = 0;
   out_134585223641373339[15] = 1;
   out_134585223641373339[16] = 0;
   out_134585223641373339[17] = 0;
   out_134585223641373339[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_134585223641373339[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_134585223641373339[20] = 0;
   out_134585223641373339[21] = state[8];
   out_134585223641373339[22] = 0;
   out_134585223641373339[23] = -state[6];
   out_134585223641373339[24] = -state[5];
   out_134585223641373339[25] = 0;
   out_134585223641373339[26] = state[3];
   out_134585223641373339[27] = 0;
   out_134585223641373339[28] = 0;
   out_134585223641373339[29] = 0;
   out_134585223641373339[30] = 0;
   out_134585223641373339[31] = 1;
   out_134585223641373339[32] = 0;
   out_134585223641373339[33] = 0;
   out_134585223641373339[34] = 1;
   out_134585223641373339[35] = 0;
   out_134585223641373339[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_134585223641373339[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_134585223641373339[38] = 0;
   out_134585223641373339[39] = -state[7];
   out_134585223641373339[40] = state[6];
   out_134585223641373339[41] = 0;
   out_134585223641373339[42] = state[4];
   out_134585223641373339[43] = -state[3];
   out_134585223641373339[44] = 0;
   out_134585223641373339[45] = 0;
   out_134585223641373339[46] = 0;
   out_134585223641373339[47] = 0;
   out_134585223641373339[48] = 0;
   out_134585223641373339[49] = 0;
   out_134585223641373339[50] = 1;
   out_134585223641373339[51] = 0;
   out_134585223641373339[52] = 0;
   out_134585223641373339[53] = 1;
}
void h_13(double *state, double *unused, double *out_638625316845772836) {
   out_638625316845772836[0] = state[3];
   out_638625316845772836[1] = state[4];
   out_638625316845772836[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1598652904215423738) {
   out_1598652904215423738[0] = 0;
   out_1598652904215423738[1] = 0;
   out_1598652904215423738[2] = 0;
   out_1598652904215423738[3] = 1;
   out_1598652904215423738[4] = 0;
   out_1598652904215423738[5] = 0;
   out_1598652904215423738[6] = 0;
   out_1598652904215423738[7] = 0;
   out_1598652904215423738[8] = 0;
   out_1598652904215423738[9] = 0;
   out_1598652904215423738[10] = 0;
   out_1598652904215423738[11] = 0;
   out_1598652904215423738[12] = 0;
   out_1598652904215423738[13] = 0;
   out_1598652904215423738[14] = 0;
   out_1598652904215423738[15] = 0;
   out_1598652904215423738[16] = 0;
   out_1598652904215423738[17] = 0;
   out_1598652904215423738[18] = 0;
   out_1598652904215423738[19] = 0;
   out_1598652904215423738[20] = 0;
   out_1598652904215423738[21] = 0;
   out_1598652904215423738[22] = 1;
   out_1598652904215423738[23] = 0;
   out_1598652904215423738[24] = 0;
   out_1598652904215423738[25] = 0;
   out_1598652904215423738[26] = 0;
   out_1598652904215423738[27] = 0;
   out_1598652904215423738[28] = 0;
   out_1598652904215423738[29] = 0;
   out_1598652904215423738[30] = 0;
   out_1598652904215423738[31] = 0;
   out_1598652904215423738[32] = 0;
   out_1598652904215423738[33] = 0;
   out_1598652904215423738[34] = 0;
   out_1598652904215423738[35] = 0;
   out_1598652904215423738[36] = 0;
   out_1598652904215423738[37] = 0;
   out_1598652904215423738[38] = 0;
   out_1598652904215423738[39] = 0;
   out_1598652904215423738[40] = 0;
   out_1598652904215423738[41] = 1;
   out_1598652904215423738[42] = 0;
   out_1598652904215423738[43] = 0;
   out_1598652904215423738[44] = 0;
   out_1598652904215423738[45] = 0;
   out_1598652904215423738[46] = 0;
   out_1598652904215423738[47] = 0;
   out_1598652904215423738[48] = 0;
   out_1598652904215423738[49] = 0;
   out_1598652904215423738[50] = 0;
   out_1598652904215423738[51] = 0;
   out_1598652904215423738[52] = 0;
   out_1598652904215423738[53] = 0;
}
void h_14(double *state, double *unused, double *out_3735192849560274451) {
   out_3735192849560274451[0] = state[6];
   out_3735192849560274451[1] = state[7];
   out_3735192849560274451[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2048737447761792662) {
   out_2048737447761792662[0] = 0;
   out_2048737447761792662[1] = 0;
   out_2048737447761792662[2] = 0;
   out_2048737447761792662[3] = 0;
   out_2048737447761792662[4] = 0;
   out_2048737447761792662[5] = 0;
   out_2048737447761792662[6] = 1;
   out_2048737447761792662[7] = 0;
   out_2048737447761792662[8] = 0;
   out_2048737447761792662[9] = 0;
   out_2048737447761792662[10] = 0;
   out_2048737447761792662[11] = 0;
   out_2048737447761792662[12] = 0;
   out_2048737447761792662[13] = 0;
   out_2048737447761792662[14] = 0;
   out_2048737447761792662[15] = 0;
   out_2048737447761792662[16] = 0;
   out_2048737447761792662[17] = 0;
   out_2048737447761792662[18] = 0;
   out_2048737447761792662[19] = 0;
   out_2048737447761792662[20] = 0;
   out_2048737447761792662[21] = 0;
   out_2048737447761792662[22] = 0;
   out_2048737447761792662[23] = 0;
   out_2048737447761792662[24] = 0;
   out_2048737447761792662[25] = 1;
   out_2048737447761792662[26] = 0;
   out_2048737447761792662[27] = 0;
   out_2048737447761792662[28] = 0;
   out_2048737447761792662[29] = 0;
   out_2048737447761792662[30] = 0;
   out_2048737447761792662[31] = 0;
   out_2048737447761792662[32] = 0;
   out_2048737447761792662[33] = 0;
   out_2048737447761792662[34] = 0;
   out_2048737447761792662[35] = 0;
   out_2048737447761792662[36] = 0;
   out_2048737447761792662[37] = 0;
   out_2048737447761792662[38] = 0;
   out_2048737447761792662[39] = 0;
   out_2048737447761792662[40] = 0;
   out_2048737447761792662[41] = 0;
   out_2048737447761792662[42] = 0;
   out_2048737447761792662[43] = 0;
   out_2048737447761792662[44] = 1;
   out_2048737447761792662[45] = 0;
   out_2048737447761792662[46] = 0;
   out_2048737447761792662[47] = 0;
   out_2048737447761792662[48] = 0;
   out_2048737447761792662[49] = 0;
   out_2048737447761792662[50] = 0;
   out_2048737447761792662[51] = 0;
   out_2048737447761792662[52] = 0;
   out_2048737447761792662[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2561165156665466750) {
  err_fun(nom_x, delta_x, out_2561165156665466750);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1962872074544000331) {
  inv_err_fun(nom_x, true_x, out_1962872074544000331);
}
void pose_H_mod_fun(double *state, double *out_279889982478867027) {
  H_mod_fun(state, out_279889982478867027);
}
void pose_f_fun(double *state, double dt, double *out_3993756686932435860) {
  f_fun(state,  dt, out_3993756686932435860);
}
void pose_F_fun(double *state, double dt, double *out_8805999151920846348) {
  F_fun(state,  dt, out_8805999151920846348);
}
void pose_h_4(double *state, double *unused, double *out_704160499582318412) {
  h_4(state, unused, out_704160499582318412);
}
void pose_H_4(double *state, double *unused, double *out_6011978304101277191) {
  H_4(state, unused, out_6011978304101277191);
}
void pose_h_10(double *state, double *unused, double *out_3225747117198463437) {
  h_10(state, unused, out_3225747117198463437);
}
void pose_H_10(double *state, double *unused, double *out_134585223641373339) {
  H_10(state, unused, out_134585223641373339);
}
void pose_h_13(double *state, double *unused, double *out_638625316845772836) {
  h_13(state, unused, out_638625316845772836);
}
void pose_H_13(double *state, double *unused, double *out_1598652904215423738) {
  H_13(state, unused, out_1598652904215423738);
}
void pose_h_14(double *state, double *unused, double *out_3735192849560274451) {
  h_14(state, unused, out_3735192849560274451);
}
void pose_H_14(double *state, double *unused, double *out_2048737447761792662) {
  H_14(state, unused, out_2048737447761792662);
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
