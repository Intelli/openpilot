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
void err_fun(double *nom_x, double *delta_x, double *out_3124141466551087525) {
   out_3124141466551087525[0] = delta_x[0] + nom_x[0];
   out_3124141466551087525[1] = delta_x[1] + nom_x[1];
   out_3124141466551087525[2] = delta_x[2] + nom_x[2];
   out_3124141466551087525[3] = delta_x[3] + nom_x[3];
   out_3124141466551087525[4] = delta_x[4] + nom_x[4];
   out_3124141466551087525[5] = delta_x[5] + nom_x[5];
   out_3124141466551087525[6] = delta_x[6] + nom_x[6];
   out_3124141466551087525[7] = delta_x[7] + nom_x[7];
   out_3124141466551087525[8] = delta_x[8] + nom_x[8];
   out_3124141466551087525[9] = delta_x[9] + nom_x[9];
   out_3124141466551087525[10] = delta_x[10] + nom_x[10];
   out_3124141466551087525[11] = delta_x[11] + nom_x[11];
   out_3124141466551087525[12] = delta_x[12] + nom_x[12];
   out_3124141466551087525[13] = delta_x[13] + nom_x[13];
   out_3124141466551087525[14] = delta_x[14] + nom_x[14];
   out_3124141466551087525[15] = delta_x[15] + nom_x[15];
   out_3124141466551087525[16] = delta_x[16] + nom_x[16];
   out_3124141466551087525[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2496827843304733878) {
   out_2496827843304733878[0] = -nom_x[0] + true_x[0];
   out_2496827843304733878[1] = -nom_x[1] + true_x[1];
   out_2496827843304733878[2] = -nom_x[2] + true_x[2];
   out_2496827843304733878[3] = -nom_x[3] + true_x[3];
   out_2496827843304733878[4] = -nom_x[4] + true_x[4];
   out_2496827843304733878[5] = -nom_x[5] + true_x[5];
   out_2496827843304733878[6] = -nom_x[6] + true_x[6];
   out_2496827843304733878[7] = -nom_x[7] + true_x[7];
   out_2496827843304733878[8] = -nom_x[8] + true_x[8];
   out_2496827843304733878[9] = -nom_x[9] + true_x[9];
   out_2496827843304733878[10] = -nom_x[10] + true_x[10];
   out_2496827843304733878[11] = -nom_x[11] + true_x[11];
   out_2496827843304733878[12] = -nom_x[12] + true_x[12];
   out_2496827843304733878[13] = -nom_x[13] + true_x[13];
   out_2496827843304733878[14] = -nom_x[14] + true_x[14];
   out_2496827843304733878[15] = -nom_x[15] + true_x[15];
   out_2496827843304733878[16] = -nom_x[16] + true_x[16];
   out_2496827843304733878[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8432171404531004476) {
   out_8432171404531004476[0] = 1.0;
   out_8432171404531004476[1] = 0.0;
   out_8432171404531004476[2] = 0.0;
   out_8432171404531004476[3] = 0.0;
   out_8432171404531004476[4] = 0.0;
   out_8432171404531004476[5] = 0.0;
   out_8432171404531004476[6] = 0.0;
   out_8432171404531004476[7] = 0.0;
   out_8432171404531004476[8] = 0.0;
   out_8432171404531004476[9] = 0.0;
   out_8432171404531004476[10] = 0.0;
   out_8432171404531004476[11] = 0.0;
   out_8432171404531004476[12] = 0.0;
   out_8432171404531004476[13] = 0.0;
   out_8432171404531004476[14] = 0.0;
   out_8432171404531004476[15] = 0.0;
   out_8432171404531004476[16] = 0.0;
   out_8432171404531004476[17] = 0.0;
   out_8432171404531004476[18] = 0.0;
   out_8432171404531004476[19] = 1.0;
   out_8432171404531004476[20] = 0.0;
   out_8432171404531004476[21] = 0.0;
   out_8432171404531004476[22] = 0.0;
   out_8432171404531004476[23] = 0.0;
   out_8432171404531004476[24] = 0.0;
   out_8432171404531004476[25] = 0.0;
   out_8432171404531004476[26] = 0.0;
   out_8432171404531004476[27] = 0.0;
   out_8432171404531004476[28] = 0.0;
   out_8432171404531004476[29] = 0.0;
   out_8432171404531004476[30] = 0.0;
   out_8432171404531004476[31] = 0.0;
   out_8432171404531004476[32] = 0.0;
   out_8432171404531004476[33] = 0.0;
   out_8432171404531004476[34] = 0.0;
   out_8432171404531004476[35] = 0.0;
   out_8432171404531004476[36] = 0.0;
   out_8432171404531004476[37] = 0.0;
   out_8432171404531004476[38] = 1.0;
   out_8432171404531004476[39] = 0.0;
   out_8432171404531004476[40] = 0.0;
   out_8432171404531004476[41] = 0.0;
   out_8432171404531004476[42] = 0.0;
   out_8432171404531004476[43] = 0.0;
   out_8432171404531004476[44] = 0.0;
   out_8432171404531004476[45] = 0.0;
   out_8432171404531004476[46] = 0.0;
   out_8432171404531004476[47] = 0.0;
   out_8432171404531004476[48] = 0.0;
   out_8432171404531004476[49] = 0.0;
   out_8432171404531004476[50] = 0.0;
   out_8432171404531004476[51] = 0.0;
   out_8432171404531004476[52] = 0.0;
   out_8432171404531004476[53] = 0.0;
   out_8432171404531004476[54] = 0.0;
   out_8432171404531004476[55] = 0.0;
   out_8432171404531004476[56] = 0.0;
   out_8432171404531004476[57] = 1.0;
   out_8432171404531004476[58] = 0.0;
   out_8432171404531004476[59] = 0.0;
   out_8432171404531004476[60] = 0.0;
   out_8432171404531004476[61] = 0.0;
   out_8432171404531004476[62] = 0.0;
   out_8432171404531004476[63] = 0.0;
   out_8432171404531004476[64] = 0.0;
   out_8432171404531004476[65] = 0.0;
   out_8432171404531004476[66] = 0.0;
   out_8432171404531004476[67] = 0.0;
   out_8432171404531004476[68] = 0.0;
   out_8432171404531004476[69] = 0.0;
   out_8432171404531004476[70] = 0.0;
   out_8432171404531004476[71] = 0.0;
   out_8432171404531004476[72] = 0.0;
   out_8432171404531004476[73] = 0.0;
   out_8432171404531004476[74] = 0.0;
   out_8432171404531004476[75] = 0.0;
   out_8432171404531004476[76] = 1.0;
   out_8432171404531004476[77] = 0.0;
   out_8432171404531004476[78] = 0.0;
   out_8432171404531004476[79] = 0.0;
   out_8432171404531004476[80] = 0.0;
   out_8432171404531004476[81] = 0.0;
   out_8432171404531004476[82] = 0.0;
   out_8432171404531004476[83] = 0.0;
   out_8432171404531004476[84] = 0.0;
   out_8432171404531004476[85] = 0.0;
   out_8432171404531004476[86] = 0.0;
   out_8432171404531004476[87] = 0.0;
   out_8432171404531004476[88] = 0.0;
   out_8432171404531004476[89] = 0.0;
   out_8432171404531004476[90] = 0.0;
   out_8432171404531004476[91] = 0.0;
   out_8432171404531004476[92] = 0.0;
   out_8432171404531004476[93] = 0.0;
   out_8432171404531004476[94] = 0.0;
   out_8432171404531004476[95] = 1.0;
   out_8432171404531004476[96] = 0.0;
   out_8432171404531004476[97] = 0.0;
   out_8432171404531004476[98] = 0.0;
   out_8432171404531004476[99] = 0.0;
   out_8432171404531004476[100] = 0.0;
   out_8432171404531004476[101] = 0.0;
   out_8432171404531004476[102] = 0.0;
   out_8432171404531004476[103] = 0.0;
   out_8432171404531004476[104] = 0.0;
   out_8432171404531004476[105] = 0.0;
   out_8432171404531004476[106] = 0.0;
   out_8432171404531004476[107] = 0.0;
   out_8432171404531004476[108] = 0.0;
   out_8432171404531004476[109] = 0.0;
   out_8432171404531004476[110] = 0.0;
   out_8432171404531004476[111] = 0.0;
   out_8432171404531004476[112] = 0.0;
   out_8432171404531004476[113] = 0.0;
   out_8432171404531004476[114] = 1.0;
   out_8432171404531004476[115] = 0.0;
   out_8432171404531004476[116] = 0.0;
   out_8432171404531004476[117] = 0.0;
   out_8432171404531004476[118] = 0.0;
   out_8432171404531004476[119] = 0.0;
   out_8432171404531004476[120] = 0.0;
   out_8432171404531004476[121] = 0.0;
   out_8432171404531004476[122] = 0.0;
   out_8432171404531004476[123] = 0.0;
   out_8432171404531004476[124] = 0.0;
   out_8432171404531004476[125] = 0.0;
   out_8432171404531004476[126] = 0.0;
   out_8432171404531004476[127] = 0.0;
   out_8432171404531004476[128] = 0.0;
   out_8432171404531004476[129] = 0.0;
   out_8432171404531004476[130] = 0.0;
   out_8432171404531004476[131] = 0.0;
   out_8432171404531004476[132] = 0.0;
   out_8432171404531004476[133] = 1.0;
   out_8432171404531004476[134] = 0.0;
   out_8432171404531004476[135] = 0.0;
   out_8432171404531004476[136] = 0.0;
   out_8432171404531004476[137] = 0.0;
   out_8432171404531004476[138] = 0.0;
   out_8432171404531004476[139] = 0.0;
   out_8432171404531004476[140] = 0.0;
   out_8432171404531004476[141] = 0.0;
   out_8432171404531004476[142] = 0.0;
   out_8432171404531004476[143] = 0.0;
   out_8432171404531004476[144] = 0.0;
   out_8432171404531004476[145] = 0.0;
   out_8432171404531004476[146] = 0.0;
   out_8432171404531004476[147] = 0.0;
   out_8432171404531004476[148] = 0.0;
   out_8432171404531004476[149] = 0.0;
   out_8432171404531004476[150] = 0.0;
   out_8432171404531004476[151] = 0.0;
   out_8432171404531004476[152] = 1.0;
   out_8432171404531004476[153] = 0.0;
   out_8432171404531004476[154] = 0.0;
   out_8432171404531004476[155] = 0.0;
   out_8432171404531004476[156] = 0.0;
   out_8432171404531004476[157] = 0.0;
   out_8432171404531004476[158] = 0.0;
   out_8432171404531004476[159] = 0.0;
   out_8432171404531004476[160] = 0.0;
   out_8432171404531004476[161] = 0.0;
   out_8432171404531004476[162] = 0.0;
   out_8432171404531004476[163] = 0.0;
   out_8432171404531004476[164] = 0.0;
   out_8432171404531004476[165] = 0.0;
   out_8432171404531004476[166] = 0.0;
   out_8432171404531004476[167] = 0.0;
   out_8432171404531004476[168] = 0.0;
   out_8432171404531004476[169] = 0.0;
   out_8432171404531004476[170] = 0.0;
   out_8432171404531004476[171] = 1.0;
   out_8432171404531004476[172] = 0.0;
   out_8432171404531004476[173] = 0.0;
   out_8432171404531004476[174] = 0.0;
   out_8432171404531004476[175] = 0.0;
   out_8432171404531004476[176] = 0.0;
   out_8432171404531004476[177] = 0.0;
   out_8432171404531004476[178] = 0.0;
   out_8432171404531004476[179] = 0.0;
   out_8432171404531004476[180] = 0.0;
   out_8432171404531004476[181] = 0.0;
   out_8432171404531004476[182] = 0.0;
   out_8432171404531004476[183] = 0.0;
   out_8432171404531004476[184] = 0.0;
   out_8432171404531004476[185] = 0.0;
   out_8432171404531004476[186] = 0.0;
   out_8432171404531004476[187] = 0.0;
   out_8432171404531004476[188] = 0.0;
   out_8432171404531004476[189] = 0.0;
   out_8432171404531004476[190] = 1.0;
   out_8432171404531004476[191] = 0.0;
   out_8432171404531004476[192] = 0.0;
   out_8432171404531004476[193] = 0.0;
   out_8432171404531004476[194] = 0.0;
   out_8432171404531004476[195] = 0.0;
   out_8432171404531004476[196] = 0.0;
   out_8432171404531004476[197] = 0.0;
   out_8432171404531004476[198] = 0.0;
   out_8432171404531004476[199] = 0.0;
   out_8432171404531004476[200] = 0.0;
   out_8432171404531004476[201] = 0.0;
   out_8432171404531004476[202] = 0.0;
   out_8432171404531004476[203] = 0.0;
   out_8432171404531004476[204] = 0.0;
   out_8432171404531004476[205] = 0.0;
   out_8432171404531004476[206] = 0.0;
   out_8432171404531004476[207] = 0.0;
   out_8432171404531004476[208] = 0.0;
   out_8432171404531004476[209] = 1.0;
   out_8432171404531004476[210] = 0.0;
   out_8432171404531004476[211] = 0.0;
   out_8432171404531004476[212] = 0.0;
   out_8432171404531004476[213] = 0.0;
   out_8432171404531004476[214] = 0.0;
   out_8432171404531004476[215] = 0.0;
   out_8432171404531004476[216] = 0.0;
   out_8432171404531004476[217] = 0.0;
   out_8432171404531004476[218] = 0.0;
   out_8432171404531004476[219] = 0.0;
   out_8432171404531004476[220] = 0.0;
   out_8432171404531004476[221] = 0.0;
   out_8432171404531004476[222] = 0.0;
   out_8432171404531004476[223] = 0.0;
   out_8432171404531004476[224] = 0.0;
   out_8432171404531004476[225] = 0.0;
   out_8432171404531004476[226] = 0.0;
   out_8432171404531004476[227] = 0.0;
   out_8432171404531004476[228] = 1.0;
   out_8432171404531004476[229] = 0.0;
   out_8432171404531004476[230] = 0.0;
   out_8432171404531004476[231] = 0.0;
   out_8432171404531004476[232] = 0.0;
   out_8432171404531004476[233] = 0.0;
   out_8432171404531004476[234] = 0.0;
   out_8432171404531004476[235] = 0.0;
   out_8432171404531004476[236] = 0.0;
   out_8432171404531004476[237] = 0.0;
   out_8432171404531004476[238] = 0.0;
   out_8432171404531004476[239] = 0.0;
   out_8432171404531004476[240] = 0.0;
   out_8432171404531004476[241] = 0.0;
   out_8432171404531004476[242] = 0.0;
   out_8432171404531004476[243] = 0.0;
   out_8432171404531004476[244] = 0.0;
   out_8432171404531004476[245] = 0.0;
   out_8432171404531004476[246] = 0.0;
   out_8432171404531004476[247] = 1.0;
   out_8432171404531004476[248] = 0.0;
   out_8432171404531004476[249] = 0.0;
   out_8432171404531004476[250] = 0.0;
   out_8432171404531004476[251] = 0.0;
   out_8432171404531004476[252] = 0.0;
   out_8432171404531004476[253] = 0.0;
   out_8432171404531004476[254] = 0.0;
   out_8432171404531004476[255] = 0.0;
   out_8432171404531004476[256] = 0.0;
   out_8432171404531004476[257] = 0.0;
   out_8432171404531004476[258] = 0.0;
   out_8432171404531004476[259] = 0.0;
   out_8432171404531004476[260] = 0.0;
   out_8432171404531004476[261] = 0.0;
   out_8432171404531004476[262] = 0.0;
   out_8432171404531004476[263] = 0.0;
   out_8432171404531004476[264] = 0.0;
   out_8432171404531004476[265] = 0.0;
   out_8432171404531004476[266] = 1.0;
   out_8432171404531004476[267] = 0.0;
   out_8432171404531004476[268] = 0.0;
   out_8432171404531004476[269] = 0.0;
   out_8432171404531004476[270] = 0.0;
   out_8432171404531004476[271] = 0.0;
   out_8432171404531004476[272] = 0.0;
   out_8432171404531004476[273] = 0.0;
   out_8432171404531004476[274] = 0.0;
   out_8432171404531004476[275] = 0.0;
   out_8432171404531004476[276] = 0.0;
   out_8432171404531004476[277] = 0.0;
   out_8432171404531004476[278] = 0.0;
   out_8432171404531004476[279] = 0.0;
   out_8432171404531004476[280] = 0.0;
   out_8432171404531004476[281] = 0.0;
   out_8432171404531004476[282] = 0.0;
   out_8432171404531004476[283] = 0.0;
   out_8432171404531004476[284] = 0.0;
   out_8432171404531004476[285] = 1.0;
   out_8432171404531004476[286] = 0.0;
   out_8432171404531004476[287] = 0.0;
   out_8432171404531004476[288] = 0.0;
   out_8432171404531004476[289] = 0.0;
   out_8432171404531004476[290] = 0.0;
   out_8432171404531004476[291] = 0.0;
   out_8432171404531004476[292] = 0.0;
   out_8432171404531004476[293] = 0.0;
   out_8432171404531004476[294] = 0.0;
   out_8432171404531004476[295] = 0.0;
   out_8432171404531004476[296] = 0.0;
   out_8432171404531004476[297] = 0.0;
   out_8432171404531004476[298] = 0.0;
   out_8432171404531004476[299] = 0.0;
   out_8432171404531004476[300] = 0.0;
   out_8432171404531004476[301] = 0.0;
   out_8432171404531004476[302] = 0.0;
   out_8432171404531004476[303] = 0.0;
   out_8432171404531004476[304] = 1.0;
   out_8432171404531004476[305] = 0.0;
   out_8432171404531004476[306] = 0.0;
   out_8432171404531004476[307] = 0.0;
   out_8432171404531004476[308] = 0.0;
   out_8432171404531004476[309] = 0.0;
   out_8432171404531004476[310] = 0.0;
   out_8432171404531004476[311] = 0.0;
   out_8432171404531004476[312] = 0.0;
   out_8432171404531004476[313] = 0.0;
   out_8432171404531004476[314] = 0.0;
   out_8432171404531004476[315] = 0.0;
   out_8432171404531004476[316] = 0.0;
   out_8432171404531004476[317] = 0.0;
   out_8432171404531004476[318] = 0.0;
   out_8432171404531004476[319] = 0.0;
   out_8432171404531004476[320] = 0.0;
   out_8432171404531004476[321] = 0.0;
   out_8432171404531004476[322] = 0.0;
   out_8432171404531004476[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5003705705076485198) {
   out_5003705705076485198[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5003705705076485198[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5003705705076485198[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5003705705076485198[3] = dt*state[12] + state[3];
   out_5003705705076485198[4] = dt*state[13] + state[4];
   out_5003705705076485198[5] = dt*state[14] + state[5];
   out_5003705705076485198[6] = state[6];
   out_5003705705076485198[7] = state[7];
   out_5003705705076485198[8] = state[8];
   out_5003705705076485198[9] = state[9];
   out_5003705705076485198[10] = state[10];
   out_5003705705076485198[11] = state[11];
   out_5003705705076485198[12] = state[12];
   out_5003705705076485198[13] = state[13];
   out_5003705705076485198[14] = state[14];
   out_5003705705076485198[15] = state[15];
   out_5003705705076485198[16] = state[16];
   out_5003705705076485198[17] = state[17];
}
void F_fun(double *state, double dt, double *out_228980895344950613) {
   out_228980895344950613[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_228980895344950613[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_228980895344950613[2] = 0;
   out_228980895344950613[3] = 0;
   out_228980895344950613[4] = 0;
   out_228980895344950613[5] = 0;
   out_228980895344950613[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_228980895344950613[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_228980895344950613[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_228980895344950613[9] = 0;
   out_228980895344950613[10] = 0;
   out_228980895344950613[11] = 0;
   out_228980895344950613[12] = 0;
   out_228980895344950613[13] = 0;
   out_228980895344950613[14] = 0;
   out_228980895344950613[15] = 0;
   out_228980895344950613[16] = 0;
   out_228980895344950613[17] = 0;
   out_228980895344950613[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_228980895344950613[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_228980895344950613[20] = 0;
   out_228980895344950613[21] = 0;
   out_228980895344950613[22] = 0;
   out_228980895344950613[23] = 0;
   out_228980895344950613[24] = 0;
   out_228980895344950613[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_228980895344950613[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_228980895344950613[27] = 0;
   out_228980895344950613[28] = 0;
   out_228980895344950613[29] = 0;
   out_228980895344950613[30] = 0;
   out_228980895344950613[31] = 0;
   out_228980895344950613[32] = 0;
   out_228980895344950613[33] = 0;
   out_228980895344950613[34] = 0;
   out_228980895344950613[35] = 0;
   out_228980895344950613[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_228980895344950613[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_228980895344950613[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_228980895344950613[39] = 0;
   out_228980895344950613[40] = 0;
   out_228980895344950613[41] = 0;
   out_228980895344950613[42] = 0;
   out_228980895344950613[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_228980895344950613[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_228980895344950613[45] = 0;
   out_228980895344950613[46] = 0;
   out_228980895344950613[47] = 0;
   out_228980895344950613[48] = 0;
   out_228980895344950613[49] = 0;
   out_228980895344950613[50] = 0;
   out_228980895344950613[51] = 0;
   out_228980895344950613[52] = 0;
   out_228980895344950613[53] = 0;
   out_228980895344950613[54] = 0;
   out_228980895344950613[55] = 0;
   out_228980895344950613[56] = 0;
   out_228980895344950613[57] = 1;
   out_228980895344950613[58] = 0;
   out_228980895344950613[59] = 0;
   out_228980895344950613[60] = 0;
   out_228980895344950613[61] = 0;
   out_228980895344950613[62] = 0;
   out_228980895344950613[63] = 0;
   out_228980895344950613[64] = 0;
   out_228980895344950613[65] = 0;
   out_228980895344950613[66] = dt;
   out_228980895344950613[67] = 0;
   out_228980895344950613[68] = 0;
   out_228980895344950613[69] = 0;
   out_228980895344950613[70] = 0;
   out_228980895344950613[71] = 0;
   out_228980895344950613[72] = 0;
   out_228980895344950613[73] = 0;
   out_228980895344950613[74] = 0;
   out_228980895344950613[75] = 0;
   out_228980895344950613[76] = 1;
   out_228980895344950613[77] = 0;
   out_228980895344950613[78] = 0;
   out_228980895344950613[79] = 0;
   out_228980895344950613[80] = 0;
   out_228980895344950613[81] = 0;
   out_228980895344950613[82] = 0;
   out_228980895344950613[83] = 0;
   out_228980895344950613[84] = 0;
   out_228980895344950613[85] = dt;
   out_228980895344950613[86] = 0;
   out_228980895344950613[87] = 0;
   out_228980895344950613[88] = 0;
   out_228980895344950613[89] = 0;
   out_228980895344950613[90] = 0;
   out_228980895344950613[91] = 0;
   out_228980895344950613[92] = 0;
   out_228980895344950613[93] = 0;
   out_228980895344950613[94] = 0;
   out_228980895344950613[95] = 1;
   out_228980895344950613[96] = 0;
   out_228980895344950613[97] = 0;
   out_228980895344950613[98] = 0;
   out_228980895344950613[99] = 0;
   out_228980895344950613[100] = 0;
   out_228980895344950613[101] = 0;
   out_228980895344950613[102] = 0;
   out_228980895344950613[103] = 0;
   out_228980895344950613[104] = dt;
   out_228980895344950613[105] = 0;
   out_228980895344950613[106] = 0;
   out_228980895344950613[107] = 0;
   out_228980895344950613[108] = 0;
   out_228980895344950613[109] = 0;
   out_228980895344950613[110] = 0;
   out_228980895344950613[111] = 0;
   out_228980895344950613[112] = 0;
   out_228980895344950613[113] = 0;
   out_228980895344950613[114] = 1;
   out_228980895344950613[115] = 0;
   out_228980895344950613[116] = 0;
   out_228980895344950613[117] = 0;
   out_228980895344950613[118] = 0;
   out_228980895344950613[119] = 0;
   out_228980895344950613[120] = 0;
   out_228980895344950613[121] = 0;
   out_228980895344950613[122] = 0;
   out_228980895344950613[123] = 0;
   out_228980895344950613[124] = 0;
   out_228980895344950613[125] = 0;
   out_228980895344950613[126] = 0;
   out_228980895344950613[127] = 0;
   out_228980895344950613[128] = 0;
   out_228980895344950613[129] = 0;
   out_228980895344950613[130] = 0;
   out_228980895344950613[131] = 0;
   out_228980895344950613[132] = 0;
   out_228980895344950613[133] = 1;
   out_228980895344950613[134] = 0;
   out_228980895344950613[135] = 0;
   out_228980895344950613[136] = 0;
   out_228980895344950613[137] = 0;
   out_228980895344950613[138] = 0;
   out_228980895344950613[139] = 0;
   out_228980895344950613[140] = 0;
   out_228980895344950613[141] = 0;
   out_228980895344950613[142] = 0;
   out_228980895344950613[143] = 0;
   out_228980895344950613[144] = 0;
   out_228980895344950613[145] = 0;
   out_228980895344950613[146] = 0;
   out_228980895344950613[147] = 0;
   out_228980895344950613[148] = 0;
   out_228980895344950613[149] = 0;
   out_228980895344950613[150] = 0;
   out_228980895344950613[151] = 0;
   out_228980895344950613[152] = 1;
   out_228980895344950613[153] = 0;
   out_228980895344950613[154] = 0;
   out_228980895344950613[155] = 0;
   out_228980895344950613[156] = 0;
   out_228980895344950613[157] = 0;
   out_228980895344950613[158] = 0;
   out_228980895344950613[159] = 0;
   out_228980895344950613[160] = 0;
   out_228980895344950613[161] = 0;
   out_228980895344950613[162] = 0;
   out_228980895344950613[163] = 0;
   out_228980895344950613[164] = 0;
   out_228980895344950613[165] = 0;
   out_228980895344950613[166] = 0;
   out_228980895344950613[167] = 0;
   out_228980895344950613[168] = 0;
   out_228980895344950613[169] = 0;
   out_228980895344950613[170] = 0;
   out_228980895344950613[171] = 1;
   out_228980895344950613[172] = 0;
   out_228980895344950613[173] = 0;
   out_228980895344950613[174] = 0;
   out_228980895344950613[175] = 0;
   out_228980895344950613[176] = 0;
   out_228980895344950613[177] = 0;
   out_228980895344950613[178] = 0;
   out_228980895344950613[179] = 0;
   out_228980895344950613[180] = 0;
   out_228980895344950613[181] = 0;
   out_228980895344950613[182] = 0;
   out_228980895344950613[183] = 0;
   out_228980895344950613[184] = 0;
   out_228980895344950613[185] = 0;
   out_228980895344950613[186] = 0;
   out_228980895344950613[187] = 0;
   out_228980895344950613[188] = 0;
   out_228980895344950613[189] = 0;
   out_228980895344950613[190] = 1;
   out_228980895344950613[191] = 0;
   out_228980895344950613[192] = 0;
   out_228980895344950613[193] = 0;
   out_228980895344950613[194] = 0;
   out_228980895344950613[195] = 0;
   out_228980895344950613[196] = 0;
   out_228980895344950613[197] = 0;
   out_228980895344950613[198] = 0;
   out_228980895344950613[199] = 0;
   out_228980895344950613[200] = 0;
   out_228980895344950613[201] = 0;
   out_228980895344950613[202] = 0;
   out_228980895344950613[203] = 0;
   out_228980895344950613[204] = 0;
   out_228980895344950613[205] = 0;
   out_228980895344950613[206] = 0;
   out_228980895344950613[207] = 0;
   out_228980895344950613[208] = 0;
   out_228980895344950613[209] = 1;
   out_228980895344950613[210] = 0;
   out_228980895344950613[211] = 0;
   out_228980895344950613[212] = 0;
   out_228980895344950613[213] = 0;
   out_228980895344950613[214] = 0;
   out_228980895344950613[215] = 0;
   out_228980895344950613[216] = 0;
   out_228980895344950613[217] = 0;
   out_228980895344950613[218] = 0;
   out_228980895344950613[219] = 0;
   out_228980895344950613[220] = 0;
   out_228980895344950613[221] = 0;
   out_228980895344950613[222] = 0;
   out_228980895344950613[223] = 0;
   out_228980895344950613[224] = 0;
   out_228980895344950613[225] = 0;
   out_228980895344950613[226] = 0;
   out_228980895344950613[227] = 0;
   out_228980895344950613[228] = 1;
   out_228980895344950613[229] = 0;
   out_228980895344950613[230] = 0;
   out_228980895344950613[231] = 0;
   out_228980895344950613[232] = 0;
   out_228980895344950613[233] = 0;
   out_228980895344950613[234] = 0;
   out_228980895344950613[235] = 0;
   out_228980895344950613[236] = 0;
   out_228980895344950613[237] = 0;
   out_228980895344950613[238] = 0;
   out_228980895344950613[239] = 0;
   out_228980895344950613[240] = 0;
   out_228980895344950613[241] = 0;
   out_228980895344950613[242] = 0;
   out_228980895344950613[243] = 0;
   out_228980895344950613[244] = 0;
   out_228980895344950613[245] = 0;
   out_228980895344950613[246] = 0;
   out_228980895344950613[247] = 1;
   out_228980895344950613[248] = 0;
   out_228980895344950613[249] = 0;
   out_228980895344950613[250] = 0;
   out_228980895344950613[251] = 0;
   out_228980895344950613[252] = 0;
   out_228980895344950613[253] = 0;
   out_228980895344950613[254] = 0;
   out_228980895344950613[255] = 0;
   out_228980895344950613[256] = 0;
   out_228980895344950613[257] = 0;
   out_228980895344950613[258] = 0;
   out_228980895344950613[259] = 0;
   out_228980895344950613[260] = 0;
   out_228980895344950613[261] = 0;
   out_228980895344950613[262] = 0;
   out_228980895344950613[263] = 0;
   out_228980895344950613[264] = 0;
   out_228980895344950613[265] = 0;
   out_228980895344950613[266] = 1;
   out_228980895344950613[267] = 0;
   out_228980895344950613[268] = 0;
   out_228980895344950613[269] = 0;
   out_228980895344950613[270] = 0;
   out_228980895344950613[271] = 0;
   out_228980895344950613[272] = 0;
   out_228980895344950613[273] = 0;
   out_228980895344950613[274] = 0;
   out_228980895344950613[275] = 0;
   out_228980895344950613[276] = 0;
   out_228980895344950613[277] = 0;
   out_228980895344950613[278] = 0;
   out_228980895344950613[279] = 0;
   out_228980895344950613[280] = 0;
   out_228980895344950613[281] = 0;
   out_228980895344950613[282] = 0;
   out_228980895344950613[283] = 0;
   out_228980895344950613[284] = 0;
   out_228980895344950613[285] = 1;
   out_228980895344950613[286] = 0;
   out_228980895344950613[287] = 0;
   out_228980895344950613[288] = 0;
   out_228980895344950613[289] = 0;
   out_228980895344950613[290] = 0;
   out_228980895344950613[291] = 0;
   out_228980895344950613[292] = 0;
   out_228980895344950613[293] = 0;
   out_228980895344950613[294] = 0;
   out_228980895344950613[295] = 0;
   out_228980895344950613[296] = 0;
   out_228980895344950613[297] = 0;
   out_228980895344950613[298] = 0;
   out_228980895344950613[299] = 0;
   out_228980895344950613[300] = 0;
   out_228980895344950613[301] = 0;
   out_228980895344950613[302] = 0;
   out_228980895344950613[303] = 0;
   out_228980895344950613[304] = 1;
   out_228980895344950613[305] = 0;
   out_228980895344950613[306] = 0;
   out_228980895344950613[307] = 0;
   out_228980895344950613[308] = 0;
   out_228980895344950613[309] = 0;
   out_228980895344950613[310] = 0;
   out_228980895344950613[311] = 0;
   out_228980895344950613[312] = 0;
   out_228980895344950613[313] = 0;
   out_228980895344950613[314] = 0;
   out_228980895344950613[315] = 0;
   out_228980895344950613[316] = 0;
   out_228980895344950613[317] = 0;
   out_228980895344950613[318] = 0;
   out_228980895344950613[319] = 0;
   out_228980895344950613[320] = 0;
   out_228980895344950613[321] = 0;
   out_228980895344950613[322] = 0;
   out_228980895344950613[323] = 1;
}
void h_4(double *state, double *unused, double *out_5085675732535578637) {
   out_5085675732535578637[0] = state[6] + state[9];
   out_5085675732535578637[1] = state[7] + state[10];
   out_5085675732535578637[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_306024827551984662) {
   out_306024827551984662[0] = 0;
   out_306024827551984662[1] = 0;
   out_306024827551984662[2] = 0;
   out_306024827551984662[3] = 0;
   out_306024827551984662[4] = 0;
   out_306024827551984662[5] = 0;
   out_306024827551984662[6] = 1;
   out_306024827551984662[7] = 0;
   out_306024827551984662[8] = 0;
   out_306024827551984662[9] = 1;
   out_306024827551984662[10] = 0;
   out_306024827551984662[11] = 0;
   out_306024827551984662[12] = 0;
   out_306024827551984662[13] = 0;
   out_306024827551984662[14] = 0;
   out_306024827551984662[15] = 0;
   out_306024827551984662[16] = 0;
   out_306024827551984662[17] = 0;
   out_306024827551984662[18] = 0;
   out_306024827551984662[19] = 0;
   out_306024827551984662[20] = 0;
   out_306024827551984662[21] = 0;
   out_306024827551984662[22] = 0;
   out_306024827551984662[23] = 0;
   out_306024827551984662[24] = 0;
   out_306024827551984662[25] = 1;
   out_306024827551984662[26] = 0;
   out_306024827551984662[27] = 0;
   out_306024827551984662[28] = 1;
   out_306024827551984662[29] = 0;
   out_306024827551984662[30] = 0;
   out_306024827551984662[31] = 0;
   out_306024827551984662[32] = 0;
   out_306024827551984662[33] = 0;
   out_306024827551984662[34] = 0;
   out_306024827551984662[35] = 0;
   out_306024827551984662[36] = 0;
   out_306024827551984662[37] = 0;
   out_306024827551984662[38] = 0;
   out_306024827551984662[39] = 0;
   out_306024827551984662[40] = 0;
   out_306024827551984662[41] = 0;
   out_306024827551984662[42] = 0;
   out_306024827551984662[43] = 0;
   out_306024827551984662[44] = 1;
   out_306024827551984662[45] = 0;
   out_306024827551984662[46] = 0;
   out_306024827551984662[47] = 1;
   out_306024827551984662[48] = 0;
   out_306024827551984662[49] = 0;
   out_306024827551984662[50] = 0;
   out_306024827551984662[51] = 0;
   out_306024827551984662[52] = 0;
   out_306024827551984662[53] = 0;
}
void h_10(double *state, double *unused, double *out_4336648869499679786) {
   out_4336648869499679786[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4336648869499679786[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4336648869499679786[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1911216833332166041) {
   out_1911216833332166041[0] = 0;
   out_1911216833332166041[1] = 9.8100000000000005*cos(state[1]);
   out_1911216833332166041[2] = 0;
   out_1911216833332166041[3] = 0;
   out_1911216833332166041[4] = -state[8];
   out_1911216833332166041[5] = state[7];
   out_1911216833332166041[6] = 0;
   out_1911216833332166041[7] = state[5];
   out_1911216833332166041[8] = -state[4];
   out_1911216833332166041[9] = 0;
   out_1911216833332166041[10] = 0;
   out_1911216833332166041[11] = 0;
   out_1911216833332166041[12] = 1;
   out_1911216833332166041[13] = 0;
   out_1911216833332166041[14] = 0;
   out_1911216833332166041[15] = 1;
   out_1911216833332166041[16] = 0;
   out_1911216833332166041[17] = 0;
   out_1911216833332166041[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1911216833332166041[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1911216833332166041[20] = 0;
   out_1911216833332166041[21] = state[8];
   out_1911216833332166041[22] = 0;
   out_1911216833332166041[23] = -state[6];
   out_1911216833332166041[24] = -state[5];
   out_1911216833332166041[25] = 0;
   out_1911216833332166041[26] = state[3];
   out_1911216833332166041[27] = 0;
   out_1911216833332166041[28] = 0;
   out_1911216833332166041[29] = 0;
   out_1911216833332166041[30] = 0;
   out_1911216833332166041[31] = 1;
   out_1911216833332166041[32] = 0;
   out_1911216833332166041[33] = 0;
   out_1911216833332166041[34] = 1;
   out_1911216833332166041[35] = 0;
   out_1911216833332166041[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1911216833332166041[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1911216833332166041[38] = 0;
   out_1911216833332166041[39] = -state[7];
   out_1911216833332166041[40] = state[6];
   out_1911216833332166041[41] = 0;
   out_1911216833332166041[42] = state[4];
   out_1911216833332166041[43] = -state[3];
   out_1911216833332166041[44] = 0;
   out_1911216833332166041[45] = 0;
   out_1911216833332166041[46] = 0;
   out_1911216833332166041[47] = 0;
   out_1911216833332166041[48] = 0;
   out_1911216833332166041[49] = 0;
   out_1911216833332166041[50] = 1;
   out_1911216833332166041[51] = 0;
   out_1911216833332166041[52] = 0;
   out_1911216833332166041[53] = 1;
}
void h_13(double *state, double *unused, double *out_6880935629319661407) {
   out_6880935629319661407[0] = state[3];
   out_6880935629319661407[1] = state[4];
   out_6880935629319661407[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3518298652884317463) {
   out_3518298652884317463[0] = 0;
   out_3518298652884317463[1] = 0;
   out_3518298652884317463[2] = 0;
   out_3518298652884317463[3] = 1;
   out_3518298652884317463[4] = 0;
   out_3518298652884317463[5] = 0;
   out_3518298652884317463[6] = 0;
   out_3518298652884317463[7] = 0;
   out_3518298652884317463[8] = 0;
   out_3518298652884317463[9] = 0;
   out_3518298652884317463[10] = 0;
   out_3518298652884317463[11] = 0;
   out_3518298652884317463[12] = 0;
   out_3518298652884317463[13] = 0;
   out_3518298652884317463[14] = 0;
   out_3518298652884317463[15] = 0;
   out_3518298652884317463[16] = 0;
   out_3518298652884317463[17] = 0;
   out_3518298652884317463[18] = 0;
   out_3518298652884317463[19] = 0;
   out_3518298652884317463[20] = 0;
   out_3518298652884317463[21] = 0;
   out_3518298652884317463[22] = 1;
   out_3518298652884317463[23] = 0;
   out_3518298652884317463[24] = 0;
   out_3518298652884317463[25] = 0;
   out_3518298652884317463[26] = 0;
   out_3518298652884317463[27] = 0;
   out_3518298652884317463[28] = 0;
   out_3518298652884317463[29] = 0;
   out_3518298652884317463[30] = 0;
   out_3518298652884317463[31] = 0;
   out_3518298652884317463[32] = 0;
   out_3518298652884317463[33] = 0;
   out_3518298652884317463[34] = 0;
   out_3518298652884317463[35] = 0;
   out_3518298652884317463[36] = 0;
   out_3518298652884317463[37] = 0;
   out_3518298652884317463[38] = 0;
   out_3518298652884317463[39] = 0;
   out_3518298652884317463[40] = 0;
   out_3518298652884317463[41] = 1;
   out_3518298652884317463[42] = 0;
   out_3518298652884317463[43] = 0;
   out_3518298652884317463[44] = 0;
   out_3518298652884317463[45] = 0;
   out_3518298652884317463[46] = 0;
   out_3518298652884317463[47] = 0;
   out_3518298652884317463[48] = 0;
   out_3518298652884317463[49] = 0;
   out_3518298652884317463[50] = 0;
   out_3518298652884317463[51] = 0;
   out_3518298652884317463[52] = 0;
   out_3518298652884317463[53] = 0;
}
void h_14(double *state, double *unused, double *out_2812231938192808748) {
   out_2812231938192808748[0] = state[6];
   out_2812231938192808748[1] = state[7];
   out_2812231938192808748[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4269265683891469191) {
   out_4269265683891469191[0] = 0;
   out_4269265683891469191[1] = 0;
   out_4269265683891469191[2] = 0;
   out_4269265683891469191[3] = 0;
   out_4269265683891469191[4] = 0;
   out_4269265683891469191[5] = 0;
   out_4269265683891469191[6] = 1;
   out_4269265683891469191[7] = 0;
   out_4269265683891469191[8] = 0;
   out_4269265683891469191[9] = 0;
   out_4269265683891469191[10] = 0;
   out_4269265683891469191[11] = 0;
   out_4269265683891469191[12] = 0;
   out_4269265683891469191[13] = 0;
   out_4269265683891469191[14] = 0;
   out_4269265683891469191[15] = 0;
   out_4269265683891469191[16] = 0;
   out_4269265683891469191[17] = 0;
   out_4269265683891469191[18] = 0;
   out_4269265683891469191[19] = 0;
   out_4269265683891469191[20] = 0;
   out_4269265683891469191[21] = 0;
   out_4269265683891469191[22] = 0;
   out_4269265683891469191[23] = 0;
   out_4269265683891469191[24] = 0;
   out_4269265683891469191[25] = 1;
   out_4269265683891469191[26] = 0;
   out_4269265683891469191[27] = 0;
   out_4269265683891469191[28] = 0;
   out_4269265683891469191[29] = 0;
   out_4269265683891469191[30] = 0;
   out_4269265683891469191[31] = 0;
   out_4269265683891469191[32] = 0;
   out_4269265683891469191[33] = 0;
   out_4269265683891469191[34] = 0;
   out_4269265683891469191[35] = 0;
   out_4269265683891469191[36] = 0;
   out_4269265683891469191[37] = 0;
   out_4269265683891469191[38] = 0;
   out_4269265683891469191[39] = 0;
   out_4269265683891469191[40] = 0;
   out_4269265683891469191[41] = 0;
   out_4269265683891469191[42] = 0;
   out_4269265683891469191[43] = 0;
   out_4269265683891469191[44] = 1;
   out_4269265683891469191[45] = 0;
   out_4269265683891469191[46] = 0;
   out_4269265683891469191[47] = 0;
   out_4269265683891469191[48] = 0;
   out_4269265683891469191[49] = 0;
   out_4269265683891469191[50] = 0;
   out_4269265683891469191[51] = 0;
   out_4269265683891469191[52] = 0;
   out_4269265683891469191[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3124141466551087525) {
  err_fun(nom_x, delta_x, out_3124141466551087525);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2496827843304733878) {
  inv_err_fun(nom_x, true_x, out_2496827843304733878);
}
void pose_H_mod_fun(double *state, double *out_8432171404531004476) {
  H_mod_fun(state, out_8432171404531004476);
}
void pose_f_fun(double *state, double dt, double *out_5003705705076485198) {
  f_fun(state,  dt, out_5003705705076485198);
}
void pose_F_fun(double *state, double dt, double *out_228980895344950613) {
  F_fun(state,  dt, out_228980895344950613);
}
void pose_h_4(double *state, double *unused, double *out_5085675732535578637) {
  h_4(state, unused, out_5085675732535578637);
}
void pose_H_4(double *state, double *unused, double *out_306024827551984662) {
  H_4(state, unused, out_306024827551984662);
}
void pose_h_10(double *state, double *unused, double *out_4336648869499679786) {
  h_10(state, unused, out_4336648869499679786);
}
void pose_H_10(double *state, double *unused, double *out_1911216833332166041) {
  H_10(state, unused, out_1911216833332166041);
}
void pose_h_13(double *state, double *unused, double *out_6880935629319661407) {
  h_13(state, unused, out_6880935629319661407);
}
void pose_H_13(double *state, double *unused, double *out_3518298652884317463) {
  H_13(state, unused, out_3518298652884317463);
}
void pose_h_14(double *state, double *unused, double *out_2812231938192808748) {
  h_14(state, unused, out_2812231938192808748);
}
void pose_H_14(double *state, double *unused, double *out_4269265683891469191) {
  H_14(state, unused, out_4269265683891469191);
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
