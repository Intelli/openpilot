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
void err_fun(double *nom_x, double *delta_x, double *out_6965396131273747251) {
   out_6965396131273747251[0] = delta_x[0] + nom_x[0];
   out_6965396131273747251[1] = delta_x[1] + nom_x[1];
   out_6965396131273747251[2] = delta_x[2] + nom_x[2];
   out_6965396131273747251[3] = delta_x[3] + nom_x[3];
   out_6965396131273747251[4] = delta_x[4] + nom_x[4];
   out_6965396131273747251[5] = delta_x[5] + nom_x[5];
   out_6965396131273747251[6] = delta_x[6] + nom_x[6];
   out_6965396131273747251[7] = delta_x[7] + nom_x[7];
   out_6965396131273747251[8] = delta_x[8] + nom_x[8];
   out_6965396131273747251[9] = delta_x[9] + nom_x[9];
   out_6965396131273747251[10] = delta_x[10] + nom_x[10];
   out_6965396131273747251[11] = delta_x[11] + nom_x[11];
   out_6965396131273747251[12] = delta_x[12] + nom_x[12];
   out_6965396131273747251[13] = delta_x[13] + nom_x[13];
   out_6965396131273747251[14] = delta_x[14] + nom_x[14];
   out_6965396131273747251[15] = delta_x[15] + nom_x[15];
   out_6965396131273747251[16] = delta_x[16] + nom_x[16];
   out_6965396131273747251[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7732022762673456989) {
   out_7732022762673456989[0] = -nom_x[0] + true_x[0];
   out_7732022762673456989[1] = -nom_x[1] + true_x[1];
   out_7732022762673456989[2] = -nom_x[2] + true_x[2];
   out_7732022762673456989[3] = -nom_x[3] + true_x[3];
   out_7732022762673456989[4] = -nom_x[4] + true_x[4];
   out_7732022762673456989[5] = -nom_x[5] + true_x[5];
   out_7732022762673456989[6] = -nom_x[6] + true_x[6];
   out_7732022762673456989[7] = -nom_x[7] + true_x[7];
   out_7732022762673456989[8] = -nom_x[8] + true_x[8];
   out_7732022762673456989[9] = -nom_x[9] + true_x[9];
   out_7732022762673456989[10] = -nom_x[10] + true_x[10];
   out_7732022762673456989[11] = -nom_x[11] + true_x[11];
   out_7732022762673456989[12] = -nom_x[12] + true_x[12];
   out_7732022762673456989[13] = -nom_x[13] + true_x[13];
   out_7732022762673456989[14] = -nom_x[14] + true_x[14];
   out_7732022762673456989[15] = -nom_x[15] + true_x[15];
   out_7732022762673456989[16] = -nom_x[16] + true_x[16];
   out_7732022762673456989[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_387031049435319729) {
   out_387031049435319729[0] = 1.0;
   out_387031049435319729[1] = 0.0;
   out_387031049435319729[2] = 0.0;
   out_387031049435319729[3] = 0.0;
   out_387031049435319729[4] = 0.0;
   out_387031049435319729[5] = 0.0;
   out_387031049435319729[6] = 0.0;
   out_387031049435319729[7] = 0.0;
   out_387031049435319729[8] = 0.0;
   out_387031049435319729[9] = 0.0;
   out_387031049435319729[10] = 0.0;
   out_387031049435319729[11] = 0.0;
   out_387031049435319729[12] = 0.0;
   out_387031049435319729[13] = 0.0;
   out_387031049435319729[14] = 0.0;
   out_387031049435319729[15] = 0.0;
   out_387031049435319729[16] = 0.0;
   out_387031049435319729[17] = 0.0;
   out_387031049435319729[18] = 0.0;
   out_387031049435319729[19] = 1.0;
   out_387031049435319729[20] = 0.0;
   out_387031049435319729[21] = 0.0;
   out_387031049435319729[22] = 0.0;
   out_387031049435319729[23] = 0.0;
   out_387031049435319729[24] = 0.0;
   out_387031049435319729[25] = 0.0;
   out_387031049435319729[26] = 0.0;
   out_387031049435319729[27] = 0.0;
   out_387031049435319729[28] = 0.0;
   out_387031049435319729[29] = 0.0;
   out_387031049435319729[30] = 0.0;
   out_387031049435319729[31] = 0.0;
   out_387031049435319729[32] = 0.0;
   out_387031049435319729[33] = 0.0;
   out_387031049435319729[34] = 0.0;
   out_387031049435319729[35] = 0.0;
   out_387031049435319729[36] = 0.0;
   out_387031049435319729[37] = 0.0;
   out_387031049435319729[38] = 1.0;
   out_387031049435319729[39] = 0.0;
   out_387031049435319729[40] = 0.0;
   out_387031049435319729[41] = 0.0;
   out_387031049435319729[42] = 0.0;
   out_387031049435319729[43] = 0.0;
   out_387031049435319729[44] = 0.0;
   out_387031049435319729[45] = 0.0;
   out_387031049435319729[46] = 0.0;
   out_387031049435319729[47] = 0.0;
   out_387031049435319729[48] = 0.0;
   out_387031049435319729[49] = 0.0;
   out_387031049435319729[50] = 0.0;
   out_387031049435319729[51] = 0.0;
   out_387031049435319729[52] = 0.0;
   out_387031049435319729[53] = 0.0;
   out_387031049435319729[54] = 0.0;
   out_387031049435319729[55] = 0.0;
   out_387031049435319729[56] = 0.0;
   out_387031049435319729[57] = 1.0;
   out_387031049435319729[58] = 0.0;
   out_387031049435319729[59] = 0.0;
   out_387031049435319729[60] = 0.0;
   out_387031049435319729[61] = 0.0;
   out_387031049435319729[62] = 0.0;
   out_387031049435319729[63] = 0.0;
   out_387031049435319729[64] = 0.0;
   out_387031049435319729[65] = 0.0;
   out_387031049435319729[66] = 0.0;
   out_387031049435319729[67] = 0.0;
   out_387031049435319729[68] = 0.0;
   out_387031049435319729[69] = 0.0;
   out_387031049435319729[70] = 0.0;
   out_387031049435319729[71] = 0.0;
   out_387031049435319729[72] = 0.0;
   out_387031049435319729[73] = 0.0;
   out_387031049435319729[74] = 0.0;
   out_387031049435319729[75] = 0.0;
   out_387031049435319729[76] = 1.0;
   out_387031049435319729[77] = 0.0;
   out_387031049435319729[78] = 0.0;
   out_387031049435319729[79] = 0.0;
   out_387031049435319729[80] = 0.0;
   out_387031049435319729[81] = 0.0;
   out_387031049435319729[82] = 0.0;
   out_387031049435319729[83] = 0.0;
   out_387031049435319729[84] = 0.0;
   out_387031049435319729[85] = 0.0;
   out_387031049435319729[86] = 0.0;
   out_387031049435319729[87] = 0.0;
   out_387031049435319729[88] = 0.0;
   out_387031049435319729[89] = 0.0;
   out_387031049435319729[90] = 0.0;
   out_387031049435319729[91] = 0.0;
   out_387031049435319729[92] = 0.0;
   out_387031049435319729[93] = 0.0;
   out_387031049435319729[94] = 0.0;
   out_387031049435319729[95] = 1.0;
   out_387031049435319729[96] = 0.0;
   out_387031049435319729[97] = 0.0;
   out_387031049435319729[98] = 0.0;
   out_387031049435319729[99] = 0.0;
   out_387031049435319729[100] = 0.0;
   out_387031049435319729[101] = 0.0;
   out_387031049435319729[102] = 0.0;
   out_387031049435319729[103] = 0.0;
   out_387031049435319729[104] = 0.0;
   out_387031049435319729[105] = 0.0;
   out_387031049435319729[106] = 0.0;
   out_387031049435319729[107] = 0.0;
   out_387031049435319729[108] = 0.0;
   out_387031049435319729[109] = 0.0;
   out_387031049435319729[110] = 0.0;
   out_387031049435319729[111] = 0.0;
   out_387031049435319729[112] = 0.0;
   out_387031049435319729[113] = 0.0;
   out_387031049435319729[114] = 1.0;
   out_387031049435319729[115] = 0.0;
   out_387031049435319729[116] = 0.0;
   out_387031049435319729[117] = 0.0;
   out_387031049435319729[118] = 0.0;
   out_387031049435319729[119] = 0.0;
   out_387031049435319729[120] = 0.0;
   out_387031049435319729[121] = 0.0;
   out_387031049435319729[122] = 0.0;
   out_387031049435319729[123] = 0.0;
   out_387031049435319729[124] = 0.0;
   out_387031049435319729[125] = 0.0;
   out_387031049435319729[126] = 0.0;
   out_387031049435319729[127] = 0.0;
   out_387031049435319729[128] = 0.0;
   out_387031049435319729[129] = 0.0;
   out_387031049435319729[130] = 0.0;
   out_387031049435319729[131] = 0.0;
   out_387031049435319729[132] = 0.0;
   out_387031049435319729[133] = 1.0;
   out_387031049435319729[134] = 0.0;
   out_387031049435319729[135] = 0.0;
   out_387031049435319729[136] = 0.0;
   out_387031049435319729[137] = 0.0;
   out_387031049435319729[138] = 0.0;
   out_387031049435319729[139] = 0.0;
   out_387031049435319729[140] = 0.0;
   out_387031049435319729[141] = 0.0;
   out_387031049435319729[142] = 0.0;
   out_387031049435319729[143] = 0.0;
   out_387031049435319729[144] = 0.0;
   out_387031049435319729[145] = 0.0;
   out_387031049435319729[146] = 0.0;
   out_387031049435319729[147] = 0.0;
   out_387031049435319729[148] = 0.0;
   out_387031049435319729[149] = 0.0;
   out_387031049435319729[150] = 0.0;
   out_387031049435319729[151] = 0.0;
   out_387031049435319729[152] = 1.0;
   out_387031049435319729[153] = 0.0;
   out_387031049435319729[154] = 0.0;
   out_387031049435319729[155] = 0.0;
   out_387031049435319729[156] = 0.0;
   out_387031049435319729[157] = 0.0;
   out_387031049435319729[158] = 0.0;
   out_387031049435319729[159] = 0.0;
   out_387031049435319729[160] = 0.0;
   out_387031049435319729[161] = 0.0;
   out_387031049435319729[162] = 0.0;
   out_387031049435319729[163] = 0.0;
   out_387031049435319729[164] = 0.0;
   out_387031049435319729[165] = 0.0;
   out_387031049435319729[166] = 0.0;
   out_387031049435319729[167] = 0.0;
   out_387031049435319729[168] = 0.0;
   out_387031049435319729[169] = 0.0;
   out_387031049435319729[170] = 0.0;
   out_387031049435319729[171] = 1.0;
   out_387031049435319729[172] = 0.0;
   out_387031049435319729[173] = 0.0;
   out_387031049435319729[174] = 0.0;
   out_387031049435319729[175] = 0.0;
   out_387031049435319729[176] = 0.0;
   out_387031049435319729[177] = 0.0;
   out_387031049435319729[178] = 0.0;
   out_387031049435319729[179] = 0.0;
   out_387031049435319729[180] = 0.0;
   out_387031049435319729[181] = 0.0;
   out_387031049435319729[182] = 0.0;
   out_387031049435319729[183] = 0.0;
   out_387031049435319729[184] = 0.0;
   out_387031049435319729[185] = 0.0;
   out_387031049435319729[186] = 0.0;
   out_387031049435319729[187] = 0.0;
   out_387031049435319729[188] = 0.0;
   out_387031049435319729[189] = 0.0;
   out_387031049435319729[190] = 1.0;
   out_387031049435319729[191] = 0.0;
   out_387031049435319729[192] = 0.0;
   out_387031049435319729[193] = 0.0;
   out_387031049435319729[194] = 0.0;
   out_387031049435319729[195] = 0.0;
   out_387031049435319729[196] = 0.0;
   out_387031049435319729[197] = 0.0;
   out_387031049435319729[198] = 0.0;
   out_387031049435319729[199] = 0.0;
   out_387031049435319729[200] = 0.0;
   out_387031049435319729[201] = 0.0;
   out_387031049435319729[202] = 0.0;
   out_387031049435319729[203] = 0.0;
   out_387031049435319729[204] = 0.0;
   out_387031049435319729[205] = 0.0;
   out_387031049435319729[206] = 0.0;
   out_387031049435319729[207] = 0.0;
   out_387031049435319729[208] = 0.0;
   out_387031049435319729[209] = 1.0;
   out_387031049435319729[210] = 0.0;
   out_387031049435319729[211] = 0.0;
   out_387031049435319729[212] = 0.0;
   out_387031049435319729[213] = 0.0;
   out_387031049435319729[214] = 0.0;
   out_387031049435319729[215] = 0.0;
   out_387031049435319729[216] = 0.0;
   out_387031049435319729[217] = 0.0;
   out_387031049435319729[218] = 0.0;
   out_387031049435319729[219] = 0.0;
   out_387031049435319729[220] = 0.0;
   out_387031049435319729[221] = 0.0;
   out_387031049435319729[222] = 0.0;
   out_387031049435319729[223] = 0.0;
   out_387031049435319729[224] = 0.0;
   out_387031049435319729[225] = 0.0;
   out_387031049435319729[226] = 0.0;
   out_387031049435319729[227] = 0.0;
   out_387031049435319729[228] = 1.0;
   out_387031049435319729[229] = 0.0;
   out_387031049435319729[230] = 0.0;
   out_387031049435319729[231] = 0.0;
   out_387031049435319729[232] = 0.0;
   out_387031049435319729[233] = 0.0;
   out_387031049435319729[234] = 0.0;
   out_387031049435319729[235] = 0.0;
   out_387031049435319729[236] = 0.0;
   out_387031049435319729[237] = 0.0;
   out_387031049435319729[238] = 0.0;
   out_387031049435319729[239] = 0.0;
   out_387031049435319729[240] = 0.0;
   out_387031049435319729[241] = 0.0;
   out_387031049435319729[242] = 0.0;
   out_387031049435319729[243] = 0.0;
   out_387031049435319729[244] = 0.0;
   out_387031049435319729[245] = 0.0;
   out_387031049435319729[246] = 0.0;
   out_387031049435319729[247] = 1.0;
   out_387031049435319729[248] = 0.0;
   out_387031049435319729[249] = 0.0;
   out_387031049435319729[250] = 0.0;
   out_387031049435319729[251] = 0.0;
   out_387031049435319729[252] = 0.0;
   out_387031049435319729[253] = 0.0;
   out_387031049435319729[254] = 0.0;
   out_387031049435319729[255] = 0.0;
   out_387031049435319729[256] = 0.0;
   out_387031049435319729[257] = 0.0;
   out_387031049435319729[258] = 0.0;
   out_387031049435319729[259] = 0.0;
   out_387031049435319729[260] = 0.0;
   out_387031049435319729[261] = 0.0;
   out_387031049435319729[262] = 0.0;
   out_387031049435319729[263] = 0.0;
   out_387031049435319729[264] = 0.0;
   out_387031049435319729[265] = 0.0;
   out_387031049435319729[266] = 1.0;
   out_387031049435319729[267] = 0.0;
   out_387031049435319729[268] = 0.0;
   out_387031049435319729[269] = 0.0;
   out_387031049435319729[270] = 0.0;
   out_387031049435319729[271] = 0.0;
   out_387031049435319729[272] = 0.0;
   out_387031049435319729[273] = 0.0;
   out_387031049435319729[274] = 0.0;
   out_387031049435319729[275] = 0.0;
   out_387031049435319729[276] = 0.0;
   out_387031049435319729[277] = 0.0;
   out_387031049435319729[278] = 0.0;
   out_387031049435319729[279] = 0.0;
   out_387031049435319729[280] = 0.0;
   out_387031049435319729[281] = 0.0;
   out_387031049435319729[282] = 0.0;
   out_387031049435319729[283] = 0.0;
   out_387031049435319729[284] = 0.0;
   out_387031049435319729[285] = 1.0;
   out_387031049435319729[286] = 0.0;
   out_387031049435319729[287] = 0.0;
   out_387031049435319729[288] = 0.0;
   out_387031049435319729[289] = 0.0;
   out_387031049435319729[290] = 0.0;
   out_387031049435319729[291] = 0.0;
   out_387031049435319729[292] = 0.0;
   out_387031049435319729[293] = 0.0;
   out_387031049435319729[294] = 0.0;
   out_387031049435319729[295] = 0.0;
   out_387031049435319729[296] = 0.0;
   out_387031049435319729[297] = 0.0;
   out_387031049435319729[298] = 0.0;
   out_387031049435319729[299] = 0.0;
   out_387031049435319729[300] = 0.0;
   out_387031049435319729[301] = 0.0;
   out_387031049435319729[302] = 0.0;
   out_387031049435319729[303] = 0.0;
   out_387031049435319729[304] = 1.0;
   out_387031049435319729[305] = 0.0;
   out_387031049435319729[306] = 0.0;
   out_387031049435319729[307] = 0.0;
   out_387031049435319729[308] = 0.0;
   out_387031049435319729[309] = 0.0;
   out_387031049435319729[310] = 0.0;
   out_387031049435319729[311] = 0.0;
   out_387031049435319729[312] = 0.0;
   out_387031049435319729[313] = 0.0;
   out_387031049435319729[314] = 0.0;
   out_387031049435319729[315] = 0.0;
   out_387031049435319729[316] = 0.0;
   out_387031049435319729[317] = 0.0;
   out_387031049435319729[318] = 0.0;
   out_387031049435319729[319] = 0.0;
   out_387031049435319729[320] = 0.0;
   out_387031049435319729[321] = 0.0;
   out_387031049435319729[322] = 0.0;
   out_387031049435319729[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4790244506834107583) {
   out_4790244506834107583[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4790244506834107583[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4790244506834107583[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4790244506834107583[3] = dt*state[12] + state[3];
   out_4790244506834107583[4] = dt*state[13] + state[4];
   out_4790244506834107583[5] = dt*state[14] + state[5];
   out_4790244506834107583[6] = state[6];
   out_4790244506834107583[7] = state[7];
   out_4790244506834107583[8] = state[8];
   out_4790244506834107583[9] = state[9];
   out_4790244506834107583[10] = state[10];
   out_4790244506834107583[11] = state[11];
   out_4790244506834107583[12] = state[12];
   out_4790244506834107583[13] = state[13];
   out_4790244506834107583[14] = state[14];
   out_4790244506834107583[15] = state[15];
   out_4790244506834107583[16] = state[16];
   out_4790244506834107583[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4347921339132117367) {
   out_4347921339132117367[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4347921339132117367[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4347921339132117367[2] = 0;
   out_4347921339132117367[3] = 0;
   out_4347921339132117367[4] = 0;
   out_4347921339132117367[5] = 0;
   out_4347921339132117367[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4347921339132117367[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4347921339132117367[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4347921339132117367[9] = 0;
   out_4347921339132117367[10] = 0;
   out_4347921339132117367[11] = 0;
   out_4347921339132117367[12] = 0;
   out_4347921339132117367[13] = 0;
   out_4347921339132117367[14] = 0;
   out_4347921339132117367[15] = 0;
   out_4347921339132117367[16] = 0;
   out_4347921339132117367[17] = 0;
   out_4347921339132117367[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4347921339132117367[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4347921339132117367[20] = 0;
   out_4347921339132117367[21] = 0;
   out_4347921339132117367[22] = 0;
   out_4347921339132117367[23] = 0;
   out_4347921339132117367[24] = 0;
   out_4347921339132117367[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4347921339132117367[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4347921339132117367[27] = 0;
   out_4347921339132117367[28] = 0;
   out_4347921339132117367[29] = 0;
   out_4347921339132117367[30] = 0;
   out_4347921339132117367[31] = 0;
   out_4347921339132117367[32] = 0;
   out_4347921339132117367[33] = 0;
   out_4347921339132117367[34] = 0;
   out_4347921339132117367[35] = 0;
   out_4347921339132117367[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4347921339132117367[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4347921339132117367[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4347921339132117367[39] = 0;
   out_4347921339132117367[40] = 0;
   out_4347921339132117367[41] = 0;
   out_4347921339132117367[42] = 0;
   out_4347921339132117367[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4347921339132117367[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4347921339132117367[45] = 0;
   out_4347921339132117367[46] = 0;
   out_4347921339132117367[47] = 0;
   out_4347921339132117367[48] = 0;
   out_4347921339132117367[49] = 0;
   out_4347921339132117367[50] = 0;
   out_4347921339132117367[51] = 0;
   out_4347921339132117367[52] = 0;
   out_4347921339132117367[53] = 0;
   out_4347921339132117367[54] = 0;
   out_4347921339132117367[55] = 0;
   out_4347921339132117367[56] = 0;
   out_4347921339132117367[57] = 1;
   out_4347921339132117367[58] = 0;
   out_4347921339132117367[59] = 0;
   out_4347921339132117367[60] = 0;
   out_4347921339132117367[61] = 0;
   out_4347921339132117367[62] = 0;
   out_4347921339132117367[63] = 0;
   out_4347921339132117367[64] = 0;
   out_4347921339132117367[65] = 0;
   out_4347921339132117367[66] = dt;
   out_4347921339132117367[67] = 0;
   out_4347921339132117367[68] = 0;
   out_4347921339132117367[69] = 0;
   out_4347921339132117367[70] = 0;
   out_4347921339132117367[71] = 0;
   out_4347921339132117367[72] = 0;
   out_4347921339132117367[73] = 0;
   out_4347921339132117367[74] = 0;
   out_4347921339132117367[75] = 0;
   out_4347921339132117367[76] = 1;
   out_4347921339132117367[77] = 0;
   out_4347921339132117367[78] = 0;
   out_4347921339132117367[79] = 0;
   out_4347921339132117367[80] = 0;
   out_4347921339132117367[81] = 0;
   out_4347921339132117367[82] = 0;
   out_4347921339132117367[83] = 0;
   out_4347921339132117367[84] = 0;
   out_4347921339132117367[85] = dt;
   out_4347921339132117367[86] = 0;
   out_4347921339132117367[87] = 0;
   out_4347921339132117367[88] = 0;
   out_4347921339132117367[89] = 0;
   out_4347921339132117367[90] = 0;
   out_4347921339132117367[91] = 0;
   out_4347921339132117367[92] = 0;
   out_4347921339132117367[93] = 0;
   out_4347921339132117367[94] = 0;
   out_4347921339132117367[95] = 1;
   out_4347921339132117367[96] = 0;
   out_4347921339132117367[97] = 0;
   out_4347921339132117367[98] = 0;
   out_4347921339132117367[99] = 0;
   out_4347921339132117367[100] = 0;
   out_4347921339132117367[101] = 0;
   out_4347921339132117367[102] = 0;
   out_4347921339132117367[103] = 0;
   out_4347921339132117367[104] = dt;
   out_4347921339132117367[105] = 0;
   out_4347921339132117367[106] = 0;
   out_4347921339132117367[107] = 0;
   out_4347921339132117367[108] = 0;
   out_4347921339132117367[109] = 0;
   out_4347921339132117367[110] = 0;
   out_4347921339132117367[111] = 0;
   out_4347921339132117367[112] = 0;
   out_4347921339132117367[113] = 0;
   out_4347921339132117367[114] = 1;
   out_4347921339132117367[115] = 0;
   out_4347921339132117367[116] = 0;
   out_4347921339132117367[117] = 0;
   out_4347921339132117367[118] = 0;
   out_4347921339132117367[119] = 0;
   out_4347921339132117367[120] = 0;
   out_4347921339132117367[121] = 0;
   out_4347921339132117367[122] = 0;
   out_4347921339132117367[123] = 0;
   out_4347921339132117367[124] = 0;
   out_4347921339132117367[125] = 0;
   out_4347921339132117367[126] = 0;
   out_4347921339132117367[127] = 0;
   out_4347921339132117367[128] = 0;
   out_4347921339132117367[129] = 0;
   out_4347921339132117367[130] = 0;
   out_4347921339132117367[131] = 0;
   out_4347921339132117367[132] = 0;
   out_4347921339132117367[133] = 1;
   out_4347921339132117367[134] = 0;
   out_4347921339132117367[135] = 0;
   out_4347921339132117367[136] = 0;
   out_4347921339132117367[137] = 0;
   out_4347921339132117367[138] = 0;
   out_4347921339132117367[139] = 0;
   out_4347921339132117367[140] = 0;
   out_4347921339132117367[141] = 0;
   out_4347921339132117367[142] = 0;
   out_4347921339132117367[143] = 0;
   out_4347921339132117367[144] = 0;
   out_4347921339132117367[145] = 0;
   out_4347921339132117367[146] = 0;
   out_4347921339132117367[147] = 0;
   out_4347921339132117367[148] = 0;
   out_4347921339132117367[149] = 0;
   out_4347921339132117367[150] = 0;
   out_4347921339132117367[151] = 0;
   out_4347921339132117367[152] = 1;
   out_4347921339132117367[153] = 0;
   out_4347921339132117367[154] = 0;
   out_4347921339132117367[155] = 0;
   out_4347921339132117367[156] = 0;
   out_4347921339132117367[157] = 0;
   out_4347921339132117367[158] = 0;
   out_4347921339132117367[159] = 0;
   out_4347921339132117367[160] = 0;
   out_4347921339132117367[161] = 0;
   out_4347921339132117367[162] = 0;
   out_4347921339132117367[163] = 0;
   out_4347921339132117367[164] = 0;
   out_4347921339132117367[165] = 0;
   out_4347921339132117367[166] = 0;
   out_4347921339132117367[167] = 0;
   out_4347921339132117367[168] = 0;
   out_4347921339132117367[169] = 0;
   out_4347921339132117367[170] = 0;
   out_4347921339132117367[171] = 1;
   out_4347921339132117367[172] = 0;
   out_4347921339132117367[173] = 0;
   out_4347921339132117367[174] = 0;
   out_4347921339132117367[175] = 0;
   out_4347921339132117367[176] = 0;
   out_4347921339132117367[177] = 0;
   out_4347921339132117367[178] = 0;
   out_4347921339132117367[179] = 0;
   out_4347921339132117367[180] = 0;
   out_4347921339132117367[181] = 0;
   out_4347921339132117367[182] = 0;
   out_4347921339132117367[183] = 0;
   out_4347921339132117367[184] = 0;
   out_4347921339132117367[185] = 0;
   out_4347921339132117367[186] = 0;
   out_4347921339132117367[187] = 0;
   out_4347921339132117367[188] = 0;
   out_4347921339132117367[189] = 0;
   out_4347921339132117367[190] = 1;
   out_4347921339132117367[191] = 0;
   out_4347921339132117367[192] = 0;
   out_4347921339132117367[193] = 0;
   out_4347921339132117367[194] = 0;
   out_4347921339132117367[195] = 0;
   out_4347921339132117367[196] = 0;
   out_4347921339132117367[197] = 0;
   out_4347921339132117367[198] = 0;
   out_4347921339132117367[199] = 0;
   out_4347921339132117367[200] = 0;
   out_4347921339132117367[201] = 0;
   out_4347921339132117367[202] = 0;
   out_4347921339132117367[203] = 0;
   out_4347921339132117367[204] = 0;
   out_4347921339132117367[205] = 0;
   out_4347921339132117367[206] = 0;
   out_4347921339132117367[207] = 0;
   out_4347921339132117367[208] = 0;
   out_4347921339132117367[209] = 1;
   out_4347921339132117367[210] = 0;
   out_4347921339132117367[211] = 0;
   out_4347921339132117367[212] = 0;
   out_4347921339132117367[213] = 0;
   out_4347921339132117367[214] = 0;
   out_4347921339132117367[215] = 0;
   out_4347921339132117367[216] = 0;
   out_4347921339132117367[217] = 0;
   out_4347921339132117367[218] = 0;
   out_4347921339132117367[219] = 0;
   out_4347921339132117367[220] = 0;
   out_4347921339132117367[221] = 0;
   out_4347921339132117367[222] = 0;
   out_4347921339132117367[223] = 0;
   out_4347921339132117367[224] = 0;
   out_4347921339132117367[225] = 0;
   out_4347921339132117367[226] = 0;
   out_4347921339132117367[227] = 0;
   out_4347921339132117367[228] = 1;
   out_4347921339132117367[229] = 0;
   out_4347921339132117367[230] = 0;
   out_4347921339132117367[231] = 0;
   out_4347921339132117367[232] = 0;
   out_4347921339132117367[233] = 0;
   out_4347921339132117367[234] = 0;
   out_4347921339132117367[235] = 0;
   out_4347921339132117367[236] = 0;
   out_4347921339132117367[237] = 0;
   out_4347921339132117367[238] = 0;
   out_4347921339132117367[239] = 0;
   out_4347921339132117367[240] = 0;
   out_4347921339132117367[241] = 0;
   out_4347921339132117367[242] = 0;
   out_4347921339132117367[243] = 0;
   out_4347921339132117367[244] = 0;
   out_4347921339132117367[245] = 0;
   out_4347921339132117367[246] = 0;
   out_4347921339132117367[247] = 1;
   out_4347921339132117367[248] = 0;
   out_4347921339132117367[249] = 0;
   out_4347921339132117367[250] = 0;
   out_4347921339132117367[251] = 0;
   out_4347921339132117367[252] = 0;
   out_4347921339132117367[253] = 0;
   out_4347921339132117367[254] = 0;
   out_4347921339132117367[255] = 0;
   out_4347921339132117367[256] = 0;
   out_4347921339132117367[257] = 0;
   out_4347921339132117367[258] = 0;
   out_4347921339132117367[259] = 0;
   out_4347921339132117367[260] = 0;
   out_4347921339132117367[261] = 0;
   out_4347921339132117367[262] = 0;
   out_4347921339132117367[263] = 0;
   out_4347921339132117367[264] = 0;
   out_4347921339132117367[265] = 0;
   out_4347921339132117367[266] = 1;
   out_4347921339132117367[267] = 0;
   out_4347921339132117367[268] = 0;
   out_4347921339132117367[269] = 0;
   out_4347921339132117367[270] = 0;
   out_4347921339132117367[271] = 0;
   out_4347921339132117367[272] = 0;
   out_4347921339132117367[273] = 0;
   out_4347921339132117367[274] = 0;
   out_4347921339132117367[275] = 0;
   out_4347921339132117367[276] = 0;
   out_4347921339132117367[277] = 0;
   out_4347921339132117367[278] = 0;
   out_4347921339132117367[279] = 0;
   out_4347921339132117367[280] = 0;
   out_4347921339132117367[281] = 0;
   out_4347921339132117367[282] = 0;
   out_4347921339132117367[283] = 0;
   out_4347921339132117367[284] = 0;
   out_4347921339132117367[285] = 1;
   out_4347921339132117367[286] = 0;
   out_4347921339132117367[287] = 0;
   out_4347921339132117367[288] = 0;
   out_4347921339132117367[289] = 0;
   out_4347921339132117367[290] = 0;
   out_4347921339132117367[291] = 0;
   out_4347921339132117367[292] = 0;
   out_4347921339132117367[293] = 0;
   out_4347921339132117367[294] = 0;
   out_4347921339132117367[295] = 0;
   out_4347921339132117367[296] = 0;
   out_4347921339132117367[297] = 0;
   out_4347921339132117367[298] = 0;
   out_4347921339132117367[299] = 0;
   out_4347921339132117367[300] = 0;
   out_4347921339132117367[301] = 0;
   out_4347921339132117367[302] = 0;
   out_4347921339132117367[303] = 0;
   out_4347921339132117367[304] = 1;
   out_4347921339132117367[305] = 0;
   out_4347921339132117367[306] = 0;
   out_4347921339132117367[307] = 0;
   out_4347921339132117367[308] = 0;
   out_4347921339132117367[309] = 0;
   out_4347921339132117367[310] = 0;
   out_4347921339132117367[311] = 0;
   out_4347921339132117367[312] = 0;
   out_4347921339132117367[313] = 0;
   out_4347921339132117367[314] = 0;
   out_4347921339132117367[315] = 0;
   out_4347921339132117367[316] = 0;
   out_4347921339132117367[317] = 0;
   out_4347921339132117367[318] = 0;
   out_4347921339132117367[319] = 0;
   out_4347921339132117367[320] = 0;
   out_4347921339132117367[321] = 0;
   out_4347921339132117367[322] = 0;
   out_4347921339132117367[323] = 1;
}
void h_4(double *state, double *unused, double *out_8125039053526857015) {
   out_8125039053526857015[0] = state[6] + state[9];
   out_8125039053526857015[1] = state[7] + state[10];
   out_8125039053526857015[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1141192051490032336) {
   out_1141192051490032336[0] = 0;
   out_1141192051490032336[1] = 0;
   out_1141192051490032336[2] = 0;
   out_1141192051490032336[3] = 0;
   out_1141192051490032336[4] = 0;
   out_1141192051490032336[5] = 0;
   out_1141192051490032336[6] = 1;
   out_1141192051490032336[7] = 0;
   out_1141192051490032336[8] = 0;
   out_1141192051490032336[9] = 1;
   out_1141192051490032336[10] = 0;
   out_1141192051490032336[11] = 0;
   out_1141192051490032336[12] = 0;
   out_1141192051490032336[13] = 0;
   out_1141192051490032336[14] = 0;
   out_1141192051490032336[15] = 0;
   out_1141192051490032336[16] = 0;
   out_1141192051490032336[17] = 0;
   out_1141192051490032336[18] = 0;
   out_1141192051490032336[19] = 0;
   out_1141192051490032336[20] = 0;
   out_1141192051490032336[21] = 0;
   out_1141192051490032336[22] = 0;
   out_1141192051490032336[23] = 0;
   out_1141192051490032336[24] = 0;
   out_1141192051490032336[25] = 1;
   out_1141192051490032336[26] = 0;
   out_1141192051490032336[27] = 0;
   out_1141192051490032336[28] = 1;
   out_1141192051490032336[29] = 0;
   out_1141192051490032336[30] = 0;
   out_1141192051490032336[31] = 0;
   out_1141192051490032336[32] = 0;
   out_1141192051490032336[33] = 0;
   out_1141192051490032336[34] = 0;
   out_1141192051490032336[35] = 0;
   out_1141192051490032336[36] = 0;
   out_1141192051490032336[37] = 0;
   out_1141192051490032336[38] = 0;
   out_1141192051490032336[39] = 0;
   out_1141192051490032336[40] = 0;
   out_1141192051490032336[41] = 0;
   out_1141192051490032336[42] = 0;
   out_1141192051490032336[43] = 0;
   out_1141192051490032336[44] = 1;
   out_1141192051490032336[45] = 0;
   out_1141192051490032336[46] = 0;
   out_1141192051490032336[47] = 1;
   out_1141192051490032336[48] = 0;
   out_1141192051490032336[49] = 0;
   out_1141192051490032336[50] = 0;
   out_1141192051490032336[51] = 0;
   out_1141192051490032336[52] = 0;
   out_1141192051490032336[53] = 0;
}
void h_10(double *state, double *unused, double *out_1313374945329114385) {
   out_1313374945329114385[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1313374945329114385[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1313374945329114385[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3646778444555579065) {
   out_3646778444555579065[0] = 0;
   out_3646778444555579065[1] = 9.8100000000000005*cos(state[1]);
   out_3646778444555579065[2] = 0;
   out_3646778444555579065[3] = 0;
   out_3646778444555579065[4] = -state[8];
   out_3646778444555579065[5] = state[7];
   out_3646778444555579065[6] = 0;
   out_3646778444555579065[7] = state[5];
   out_3646778444555579065[8] = -state[4];
   out_3646778444555579065[9] = 0;
   out_3646778444555579065[10] = 0;
   out_3646778444555579065[11] = 0;
   out_3646778444555579065[12] = 1;
   out_3646778444555579065[13] = 0;
   out_3646778444555579065[14] = 0;
   out_3646778444555579065[15] = 1;
   out_3646778444555579065[16] = 0;
   out_3646778444555579065[17] = 0;
   out_3646778444555579065[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3646778444555579065[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3646778444555579065[20] = 0;
   out_3646778444555579065[21] = state[8];
   out_3646778444555579065[22] = 0;
   out_3646778444555579065[23] = -state[6];
   out_3646778444555579065[24] = -state[5];
   out_3646778444555579065[25] = 0;
   out_3646778444555579065[26] = state[3];
   out_3646778444555579065[27] = 0;
   out_3646778444555579065[28] = 0;
   out_3646778444555579065[29] = 0;
   out_3646778444555579065[30] = 0;
   out_3646778444555579065[31] = 1;
   out_3646778444555579065[32] = 0;
   out_3646778444555579065[33] = 0;
   out_3646778444555579065[34] = 1;
   out_3646778444555579065[35] = 0;
   out_3646778444555579065[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3646778444555579065[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3646778444555579065[38] = 0;
   out_3646778444555579065[39] = -state[7];
   out_3646778444555579065[40] = state[6];
   out_3646778444555579065[41] = 0;
   out_3646778444555579065[42] = state[4];
   out_3646778444555579065[43] = -state[3];
   out_3646778444555579065[44] = 0;
   out_3646778444555579065[45] = 0;
   out_3646778444555579065[46] = 0;
   out_3646778444555579065[47] = 0;
   out_3646778444555579065[48] = 0;
   out_3646778444555579065[49] = 0;
   out_3646778444555579065[50] = 1;
   out_3646778444555579065[51] = 0;
   out_3646778444555579065[52] = 0;
   out_3646778444555579065[53] = 1;
}
void h_13(double *state, double *unused, double *out_488303792701597214) {
   out_488303792701597214[0] = state[3];
   out_488303792701597214[1] = state[4];
   out_488303792701597214[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4353465876822365137) {
   out_4353465876822365137[0] = 0;
   out_4353465876822365137[1] = 0;
   out_4353465876822365137[2] = 0;
   out_4353465876822365137[3] = 1;
   out_4353465876822365137[4] = 0;
   out_4353465876822365137[5] = 0;
   out_4353465876822365137[6] = 0;
   out_4353465876822365137[7] = 0;
   out_4353465876822365137[8] = 0;
   out_4353465876822365137[9] = 0;
   out_4353465876822365137[10] = 0;
   out_4353465876822365137[11] = 0;
   out_4353465876822365137[12] = 0;
   out_4353465876822365137[13] = 0;
   out_4353465876822365137[14] = 0;
   out_4353465876822365137[15] = 0;
   out_4353465876822365137[16] = 0;
   out_4353465876822365137[17] = 0;
   out_4353465876822365137[18] = 0;
   out_4353465876822365137[19] = 0;
   out_4353465876822365137[20] = 0;
   out_4353465876822365137[21] = 0;
   out_4353465876822365137[22] = 1;
   out_4353465876822365137[23] = 0;
   out_4353465876822365137[24] = 0;
   out_4353465876822365137[25] = 0;
   out_4353465876822365137[26] = 0;
   out_4353465876822365137[27] = 0;
   out_4353465876822365137[28] = 0;
   out_4353465876822365137[29] = 0;
   out_4353465876822365137[30] = 0;
   out_4353465876822365137[31] = 0;
   out_4353465876822365137[32] = 0;
   out_4353465876822365137[33] = 0;
   out_4353465876822365137[34] = 0;
   out_4353465876822365137[35] = 0;
   out_4353465876822365137[36] = 0;
   out_4353465876822365137[37] = 0;
   out_4353465876822365137[38] = 0;
   out_4353465876822365137[39] = 0;
   out_4353465876822365137[40] = 0;
   out_4353465876822365137[41] = 1;
   out_4353465876822365137[42] = 0;
   out_4353465876822365137[43] = 0;
   out_4353465876822365137[44] = 0;
   out_4353465876822365137[45] = 0;
   out_4353465876822365137[46] = 0;
   out_4353465876822365137[47] = 0;
   out_4353465876822365137[48] = 0;
   out_4353465876822365137[49] = 0;
   out_4353465876822365137[50] = 0;
   out_4353465876822365137[51] = 0;
   out_4353465876822365137[52] = 0;
   out_4353465876822365137[53] = 0;
}
void h_14(double *state, double *unused, double *out_8265272713495484247) {
   out_8265272713495484247[0] = state[6];
   out_8265272713495484247[1] = state[7];
   out_8265272713495484247[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1941596380805339960) {
   out_1941596380805339960[0] = 0;
   out_1941596380805339960[1] = 0;
   out_1941596380805339960[2] = 0;
   out_1941596380805339960[3] = 0;
   out_1941596380805339960[4] = 0;
   out_1941596380805339960[5] = 0;
   out_1941596380805339960[6] = 1;
   out_1941596380805339960[7] = 0;
   out_1941596380805339960[8] = 0;
   out_1941596380805339960[9] = 0;
   out_1941596380805339960[10] = 0;
   out_1941596380805339960[11] = 0;
   out_1941596380805339960[12] = 0;
   out_1941596380805339960[13] = 0;
   out_1941596380805339960[14] = 0;
   out_1941596380805339960[15] = 0;
   out_1941596380805339960[16] = 0;
   out_1941596380805339960[17] = 0;
   out_1941596380805339960[18] = 0;
   out_1941596380805339960[19] = 0;
   out_1941596380805339960[20] = 0;
   out_1941596380805339960[21] = 0;
   out_1941596380805339960[22] = 0;
   out_1941596380805339960[23] = 0;
   out_1941596380805339960[24] = 0;
   out_1941596380805339960[25] = 1;
   out_1941596380805339960[26] = 0;
   out_1941596380805339960[27] = 0;
   out_1941596380805339960[28] = 0;
   out_1941596380805339960[29] = 0;
   out_1941596380805339960[30] = 0;
   out_1941596380805339960[31] = 0;
   out_1941596380805339960[32] = 0;
   out_1941596380805339960[33] = 0;
   out_1941596380805339960[34] = 0;
   out_1941596380805339960[35] = 0;
   out_1941596380805339960[36] = 0;
   out_1941596380805339960[37] = 0;
   out_1941596380805339960[38] = 0;
   out_1941596380805339960[39] = 0;
   out_1941596380805339960[40] = 0;
   out_1941596380805339960[41] = 0;
   out_1941596380805339960[42] = 0;
   out_1941596380805339960[43] = 0;
   out_1941596380805339960[44] = 1;
   out_1941596380805339960[45] = 0;
   out_1941596380805339960[46] = 0;
   out_1941596380805339960[47] = 0;
   out_1941596380805339960[48] = 0;
   out_1941596380805339960[49] = 0;
   out_1941596380805339960[50] = 0;
   out_1941596380805339960[51] = 0;
   out_1941596380805339960[52] = 0;
   out_1941596380805339960[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6965396131273747251) {
  err_fun(nom_x, delta_x, out_6965396131273747251);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7732022762673456989) {
  inv_err_fun(nom_x, true_x, out_7732022762673456989);
}
void pose_H_mod_fun(double *state, double *out_387031049435319729) {
  H_mod_fun(state, out_387031049435319729);
}
void pose_f_fun(double *state, double dt, double *out_4790244506834107583) {
  f_fun(state,  dt, out_4790244506834107583);
}
void pose_F_fun(double *state, double dt, double *out_4347921339132117367) {
  F_fun(state,  dt, out_4347921339132117367);
}
void pose_h_4(double *state, double *unused, double *out_8125039053526857015) {
  h_4(state, unused, out_8125039053526857015);
}
void pose_H_4(double *state, double *unused, double *out_1141192051490032336) {
  H_4(state, unused, out_1141192051490032336);
}
void pose_h_10(double *state, double *unused, double *out_1313374945329114385) {
  h_10(state, unused, out_1313374945329114385);
}
void pose_H_10(double *state, double *unused, double *out_3646778444555579065) {
  H_10(state, unused, out_3646778444555579065);
}
void pose_h_13(double *state, double *unused, double *out_488303792701597214) {
  h_13(state, unused, out_488303792701597214);
}
void pose_H_13(double *state, double *unused, double *out_4353465876822365137) {
  H_13(state, unused, out_4353465876822365137);
}
void pose_h_14(double *state, double *unused, double *out_8265272713495484247) {
  h_14(state, unused, out_8265272713495484247);
}
void pose_H_14(double *state, double *unused, double *out_1941596380805339960) {
  H_14(state, unused, out_1941596380805339960);
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
