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
void err_fun(double *nom_x, double *delta_x, double *out_3009149682027724813) {
   out_3009149682027724813[0] = delta_x[0] + nom_x[0];
   out_3009149682027724813[1] = delta_x[1] + nom_x[1];
   out_3009149682027724813[2] = delta_x[2] + nom_x[2];
   out_3009149682027724813[3] = delta_x[3] + nom_x[3];
   out_3009149682027724813[4] = delta_x[4] + nom_x[4];
   out_3009149682027724813[5] = delta_x[5] + nom_x[5];
   out_3009149682027724813[6] = delta_x[6] + nom_x[6];
   out_3009149682027724813[7] = delta_x[7] + nom_x[7];
   out_3009149682027724813[8] = delta_x[8] + nom_x[8];
   out_3009149682027724813[9] = delta_x[9] + nom_x[9];
   out_3009149682027724813[10] = delta_x[10] + nom_x[10];
   out_3009149682027724813[11] = delta_x[11] + nom_x[11];
   out_3009149682027724813[12] = delta_x[12] + nom_x[12];
   out_3009149682027724813[13] = delta_x[13] + nom_x[13];
   out_3009149682027724813[14] = delta_x[14] + nom_x[14];
   out_3009149682027724813[15] = delta_x[15] + nom_x[15];
   out_3009149682027724813[16] = delta_x[16] + nom_x[16];
   out_3009149682027724813[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6241253285121461636) {
   out_6241253285121461636[0] = -nom_x[0] + true_x[0];
   out_6241253285121461636[1] = -nom_x[1] + true_x[1];
   out_6241253285121461636[2] = -nom_x[2] + true_x[2];
   out_6241253285121461636[3] = -nom_x[3] + true_x[3];
   out_6241253285121461636[4] = -nom_x[4] + true_x[4];
   out_6241253285121461636[5] = -nom_x[5] + true_x[5];
   out_6241253285121461636[6] = -nom_x[6] + true_x[6];
   out_6241253285121461636[7] = -nom_x[7] + true_x[7];
   out_6241253285121461636[8] = -nom_x[8] + true_x[8];
   out_6241253285121461636[9] = -nom_x[9] + true_x[9];
   out_6241253285121461636[10] = -nom_x[10] + true_x[10];
   out_6241253285121461636[11] = -nom_x[11] + true_x[11];
   out_6241253285121461636[12] = -nom_x[12] + true_x[12];
   out_6241253285121461636[13] = -nom_x[13] + true_x[13];
   out_6241253285121461636[14] = -nom_x[14] + true_x[14];
   out_6241253285121461636[15] = -nom_x[15] + true_x[15];
   out_6241253285121461636[16] = -nom_x[16] + true_x[16];
   out_6241253285121461636[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3247087395785811549) {
   out_3247087395785811549[0] = 1.0;
   out_3247087395785811549[1] = 0.0;
   out_3247087395785811549[2] = 0.0;
   out_3247087395785811549[3] = 0.0;
   out_3247087395785811549[4] = 0.0;
   out_3247087395785811549[5] = 0.0;
   out_3247087395785811549[6] = 0.0;
   out_3247087395785811549[7] = 0.0;
   out_3247087395785811549[8] = 0.0;
   out_3247087395785811549[9] = 0.0;
   out_3247087395785811549[10] = 0.0;
   out_3247087395785811549[11] = 0.0;
   out_3247087395785811549[12] = 0.0;
   out_3247087395785811549[13] = 0.0;
   out_3247087395785811549[14] = 0.0;
   out_3247087395785811549[15] = 0.0;
   out_3247087395785811549[16] = 0.0;
   out_3247087395785811549[17] = 0.0;
   out_3247087395785811549[18] = 0.0;
   out_3247087395785811549[19] = 1.0;
   out_3247087395785811549[20] = 0.0;
   out_3247087395785811549[21] = 0.0;
   out_3247087395785811549[22] = 0.0;
   out_3247087395785811549[23] = 0.0;
   out_3247087395785811549[24] = 0.0;
   out_3247087395785811549[25] = 0.0;
   out_3247087395785811549[26] = 0.0;
   out_3247087395785811549[27] = 0.0;
   out_3247087395785811549[28] = 0.0;
   out_3247087395785811549[29] = 0.0;
   out_3247087395785811549[30] = 0.0;
   out_3247087395785811549[31] = 0.0;
   out_3247087395785811549[32] = 0.0;
   out_3247087395785811549[33] = 0.0;
   out_3247087395785811549[34] = 0.0;
   out_3247087395785811549[35] = 0.0;
   out_3247087395785811549[36] = 0.0;
   out_3247087395785811549[37] = 0.0;
   out_3247087395785811549[38] = 1.0;
   out_3247087395785811549[39] = 0.0;
   out_3247087395785811549[40] = 0.0;
   out_3247087395785811549[41] = 0.0;
   out_3247087395785811549[42] = 0.0;
   out_3247087395785811549[43] = 0.0;
   out_3247087395785811549[44] = 0.0;
   out_3247087395785811549[45] = 0.0;
   out_3247087395785811549[46] = 0.0;
   out_3247087395785811549[47] = 0.0;
   out_3247087395785811549[48] = 0.0;
   out_3247087395785811549[49] = 0.0;
   out_3247087395785811549[50] = 0.0;
   out_3247087395785811549[51] = 0.0;
   out_3247087395785811549[52] = 0.0;
   out_3247087395785811549[53] = 0.0;
   out_3247087395785811549[54] = 0.0;
   out_3247087395785811549[55] = 0.0;
   out_3247087395785811549[56] = 0.0;
   out_3247087395785811549[57] = 1.0;
   out_3247087395785811549[58] = 0.0;
   out_3247087395785811549[59] = 0.0;
   out_3247087395785811549[60] = 0.0;
   out_3247087395785811549[61] = 0.0;
   out_3247087395785811549[62] = 0.0;
   out_3247087395785811549[63] = 0.0;
   out_3247087395785811549[64] = 0.0;
   out_3247087395785811549[65] = 0.0;
   out_3247087395785811549[66] = 0.0;
   out_3247087395785811549[67] = 0.0;
   out_3247087395785811549[68] = 0.0;
   out_3247087395785811549[69] = 0.0;
   out_3247087395785811549[70] = 0.0;
   out_3247087395785811549[71] = 0.0;
   out_3247087395785811549[72] = 0.0;
   out_3247087395785811549[73] = 0.0;
   out_3247087395785811549[74] = 0.0;
   out_3247087395785811549[75] = 0.0;
   out_3247087395785811549[76] = 1.0;
   out_3247087395785811549[77] = 0.0;
   out_3247087395785811549[78] = 0.0;
   out_3247087395785811549[79] = 0.0;
   out_3247087395785811549[80] = 0.0;
   out_3247087395785811549[81] = 0.0;
   out_3247087395785811549[82] = 0.0;
   out_3247087395785811549[83] = 0.0;
   out_3247087395785811549[84] = 0.0;
   out_3247087395785811549[85] = 0.0;
   out_3247087395785811549[86] = 0.0;
   out_3247087395785811549[87] = 0.0;
   out_3247087395785811549[88] = 0.0;
   out_3247087395785811549[89] = 0.0;
   out_3247087395785811549[90] = 0.0;
   out_3247087395785811549[91] = 0.0;
   out_3247087395785811549[92] = 0.0;
   out_3247087395785811549[93] = 0.0;
   out_3247087395785811549[94] = 0.0;
   out_3247087395785811549[95] = 1.0;
   out_3247087395785811549[96] = 0.0;
   out_3247087395785811549[97] = 0.0;
   out_3247087395785811549[98] = 0.0;
   out_3247087395785811549[99] = 0.0;
   out_3247087395785811549[100] = 0.0;
   out_3247087395785811549[101] = 0.0;
   out_3247087395785811549[102] = 0.0;
   out_3247087395785811549[103] = 0.0;
   out_3247087395785811549[104] = 0.0;
   out_3247087395785811549[105] = 0.0;
   out_3247087395785811549[106] = 0.0;
   out_3247087395785811549[107] = 0.0;
   out_3247087395785811549[108] = 0.0;
   out_3247087395785811549[109] = 0.0;
   out_3247087395785811549[110] = 0.0;
   out_3247087395785811549[111] = 0.0;
   out_3247087395785811549[112] = 0.0;
   out_3247087395785811549[113] = 0.0;
   out_3247087395785811549[114] = 1.0;
   out_3247087395785811549[115] = 0.0;
   out_3247087395785811549[116] = 0.0;
   out_3247087395785811549[117] = 0.0;
   out_3247087395785811549[118] = 0.0;
   out_3247087395785811549[119] = 0.0;
   out_3247087395785811549[120] = 0.0;
   out_3247087395785811549[121] = 0.0;
   out_3247087395785811549[122] = 0.0;
   out_3247087395785811549[123] = 0.0;
   out_3247087395785811549[124] = 0.0;
   out_3247087395785811549[125] = 0.0;
   out_3247087395785811549[126] = 0.0;
   out_3247087395785811549[127] = 0.0;
   out_3247087395785811549[128] = 0.0;
   out_3247087395785811549[129] = 0.0;
   out_3247087395785811549[130] = 0.0;
   out_3247087395785811549[131] = 0.0;
   out_3247087395785811549[132] = 0.0;
   out_3247087395785811549[133] = 1.0;
   out_3247087395785811549[134] = 0.0;
   out_3247087395785811549[135] = 0.0;
   out_3247087395785811549[136] = 0.0;
   out_3247087395785811549[137] = 0.0;
   out_3247087395785811549[138] = 0.0;
   out_3247087395785811549[139] = 0.0;
   out_3247087395785811549[140] = 0.0;
   out_3247087395785811549[141] = 0.0;
   out_3247087395785811549[142] = 0.0;
   out_3247087395785811549[143] = 0.0;
   out_3247087395785811549[144] = 0.0;
   out_3247087395785811549[145] = 0.0;
   out_3247087395785811549[146] = 0.0;
   out_3247087395785811549[147] = 0.0;
   out_3247087395785811549[148] = 0.0;
   out_3247087395785811549[149] = 0.0;
   out_3247087395785811549[150] = 0.0;
   out_3247087395785811549[151] = 0.0;
   out_3247087395785811549[152] = 1.0;
   out_3247087395785811549[153] = 0.0;
   out_3247087395785811549[154] = 0.0;
   out_3247087395785811549[155] = 0.0;
   out_3247087395785811549[156] = 0.0;
   out_3247087395785811549[157] = 0.0;
   out_3247087395785811549[158] = 0.0;
   out_3247087395785811549[159] = 0.0;
   out_3247087395785811549[160] = 0.0;
   out_3247087395785811549[161] = 0.0;
   out_3247087395785811549[162] = 0.0;
   out_3247087395785811549[163] = 0.0;
   out_3247087395785811549[164] = 0.0;
   out_3247087395785811549[165] = 0.0;
   out_3247087395785811549[166] = 0.0;
   out_3247087395785811549[167] = 0.0;
   out_3247087395785811549[168] = 0.0;
   out_3247087395785811549[169] = 0.0;
   out_3247087395785811549[170] = 0.0;
   out_3247087395785811549[171] = 1.0;
   out_3247087395785811549[172] = 0.0;
   out_3247087395785811549[173] = 0.0;
   out_3247087395785811549[174] = 0.0;
   out_3247087395785811549[175] = 0.0;
   out_3247087395785811549[176] = 0.0;
   out_3247087395785811549[177] = 0.0;
   out_3247087395785811549[178] = 0.0;
   out_3247087395785811549[179] = 0.0;
   out_3247087395785811549[180] = 0.0;
   out_3247087395785811549[181] = 0.0;
   out_3247087395785811549[182] = 0.0;
   out_3247087395785811549[183] = 0.0;
   out_3247087395785811549[184] = 0.0;
   out_3247087395785811549[185] = 0.0;
   out_3247087395785811549[186] = 0.0;
   out_3247087395785811549[187] = 0.0;
   out_3247087395785811549[188] = 0.0;
   out_3247087395785811549[189] = 0.0;
   out_3247087395785811549[190] = 1.0;
   out_3247087395785811549[191] = 0.0;
   out_3247087395785811549[192] = 0.0;
   out_3247087395785811549[193] = 0.0;
   out_3247087395785811549[194] = 0.0;
   out_3247087395785811549[195] = 0.0;
   out_3247087395785811549[196] = 0.0;
   out_3247087395785811549[197] = 0.0;
   out_3247087395785811549[198] = 0.0;
   out_3247087395785811549[199] = 0.0;
   out_3247087395785811549[200] = 0.0;
   out_3247087395785811549[201] = 0.0;
   out_3247087395785811549[202] = 0.0;
   out_3247087395785811549[203] = 0.0;
   out_3247087395785811549[204] = 0.0;
   out_3247087395785811549[205] = 0.0;
   out_3247087395785811549[206] = 0.0;
   out_3247087395785811549[207] = 0.0;
   out_3247087395785811549[208] = 0.0;
   out_3247087395785811549[209] = 1.0;
   out_3247087395785811549[210] = 0.0;
   out_3247087395785811549[211] = 0.0;
   out_3247087395785811549[212] = 0.0;
   out_3247087395785811549[213] = 0.0;
   out_3247087395785811549[214] = 0.0;
   out_3247087395785811549[215] = 0.0;
   out_3247087395785811549[216] = 0.0;
   out_3247087395785811549[217] = 0.0;
   out_3247087395785811549[218] = 0.0;
   out_3247087395785811549[219] = 0.0;
   out_3247087395785811549[220] = 0.0;
   out_3247087395785811549[221] = 0.0;
   out_3247087395785811549[222] = 0.0;
   out_3247087395785811549[223] = 0.0;
   out_3247087395785811549[224] = 0.0;
   out_3247087395785811549[225] = 0.0;
   out_3247087395785811549[226] = 0.0;
   out_3247087395785811549[227] = 0.0;
   out_3247087395785811549[228] = 1.0;
   out_3247087395785811549[229] = 0.0;
   out_3247087395785811549[230] = 0.0;
   out_3247087395785811549[231] = 0.0;
   out_3247087395785811549[232] = 0.0;
   out_3247087395785811549[233] = 0.0;
   out_3247087395785811549[234] = 0.0;
   out_3247087395785811549[235] = 0.0;
   out_3247087395785811549[236] = 0.0;
   out_3247087395785811549[237] = 0.0;
   out_3247087395785811549[238] = 0.0;
   out_3247087395785811549[239] = 0.0;
   out_3247087395785811549[240] = 0.0;
   out_3247087395785811549[241] = 0.0;
   out_3247087395785811549[242] = 0.0;
   out_3247087395785811549[243] = 0.0;
   out_3247087395785811549[244] = 0.0;
   out_3247087395785811549[245] = 0.0;
   out_3247087395785811549[246] = 0.0;
   out_3247087395785811549[247] = 1.0;
   out_3247087395785811549[248] = 0.0;
   out_3247087395785811549[249] = 0.0;
   out_3247087395785811549[250] = 0.0;
   out_3247087395785811549[251] = 0.0;
   out_3247087395785811549[252] = 0.0;
   out_3247087395785811549[253] = 0.0;
   out_3247087395785811549[254] = 0.0;
   out_3247087395785811549[255] = 0.0;
   out_3247087395785811549[256] = 0.0;
   out_3247087395785811549[257] = 0.0;
   out_3247087395785811549[258] = 0.0;
   out_3247087395785811549[259] = 0.0;
   out_3247087395785811549[260] = 0.0;
   out_3247087395785811549[261] = 0.0;
   out_3247087395785811549[262] = 0.0;
   out_3247087395785811549[263] = 0.0;
   out_3247087395785811549[264] = 0.0;
   out_3247087395785811549[265] = 0.0;
   out_3247087395785811549[266] = 1.0;
   out_3247087395785811549[267] = 0.0;
   out_3247087395785811549[268] = 0.0;
   out_3247087395785811549[269] = 0.0;
   out_3247087395785811549[270] = 0.0;
   out_3247087395785811549[271] = 0.0;
   out_3247087395785811549[272] = 0.0;
   out_3247087395785811549[273] = 0.0;
   out_3247087395785811549[274] = 0.0;
   out_3247087395785811549[275] = 0.0;
   out_3247087395785811549[276] = 0.0;
   out_3247087395785811549[277] = 0.0;
   out_3247087395785811549[278] = 0.0;
   out_3247087395785811549[279] = 0.0;
   out_3247087395785811549[280] = 0.0;
   out_3247087395785811549[281] = 0.0;
   out_3247087395785811549[282] = 0.0;
   out_3247087395785811549[283] = 0.0;
   out_3247087395785811549[284] = 0.0;
   out_3247087395785811549[285] = 1.0;
   out_3247087395785811549[286] = 0.0;
   out_3247087395785811549[287] = 0.0;
   out_3247087395785811549[288] = 0.0;
   out_3247087395785811549[289] = 0.0;
   out_3247087395785811549[290] = 0.0;
   out_3247087395785811549[291] = 0.0;
   out_3247087395785811549[292] = 0.0;
   out_3247087395785811549[293] = 0.0;
   out_3247087395785811549[294] = 0.0;
   out_3247087395785811549[295] = 0.0;
   out_3247087395785811549[296] = 0.0;
   out_3247087395785811549[297] = 0.0;
   out_3247087395785811549[298] = 0.0;
   out_3247087395785811549[299] = 0.0;
   out_3247087395785811549[300] = 0.0;
   out_3247087395785811549[301] = 0.0;
   out_3247087395785811549[302] = 0.0;
   out_3247087395785811549[303] = 0.0;
   out_3247087395785811549[304] = 1.0;
   out_3247087395785811549[305] = 0.0;
   out_3247087395785811549[306] = 0.0;
   out_3247087395785811549[307] = 0.0;
   out_3247087395785811549[308] = 0.0;
   out_3247087395785811549[309] = 0.0;
   out_3247087395785811549[310] = 0.0;
   out_3247087395785811549[311] = 0.0;
   out_3247087395785811549[312] = 0.0;
   out_3247087395785811549[313] = 0.0;
   out_3247087395785811549[314] = 0.0;
   out_3247087395785811549[315] = 0.0;
   out_3247087395785811549[316] = 0.0;
   out_3247087395785811549[317] = 0.0;
   out_3247087395785811549[318] = 0.0;
   out_3247087395785811549[319] = 0.0;
   out_3247087395785811549[320] = 0.0;
   out_3247087395785811549[321] = 0.0;
   out_3247087395785811549[322] = 0.0;
   out_3247087395785811549[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8180428593278352040) {
   out_8180428593278352040[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8180428593278352040[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8180428593278352040[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8180428593278352040[3] = dt*state[12] + state[3];
   out_8180428593278352040[4] = dt*state[13] + state[4];
   out_8180428593278352040[5] = dt*state[14] + state[5];
   out_8180428593278352040[6] = state[6];
   out_8180428593278352040[7] = state[7];
   out_8180428593278352040[8] = state[8];
   out_8180428593278352040[9] = state[9];
   out_8180428593278352040[10] = state[10];
   out_8180428593278352040[11] = state[11];
   out_8180428593278352040[12] = state[12];
   out_8180428593278352040[13] = state[13];
   out_8180428593278352040[14] = state[14];
   out_8180428593278352040[15] = state[15];
   out_8180428593278352040[16] = state[16];
   out_8180428593278352040[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7556302766395134047) {
   out_7556302766395134047[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7556302766395134047[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7556302766395134047[2] = 0;
   out_7556302766395134047[3] = 0;
   out_7556302766395134047[4] = 0;
   out_7556302766395134047[5] = 0;
   out_7556302766395134047[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7556302766395134047[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7556302766395134047[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7556302766395134047[9] = 0;
   out_7556302766395134047[10] = 0;
   out_7556302766395134047[11] = 0;
   out_7556302766395134047[12] = 0;
   out_7556302766395134047[13] = 0;
   out_7556302766395134047[14] = 0;
   out_7556302766395134047[15] = 0;
   out_7556302766395134047[16] = 0;
   out_7556302766395134047[17] = 0;
   out_7556302766395134047[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7556302766395134047[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7556302766395134047[20] = 0;
   out_7556302766395134047[21] = 0;
   out_7556302766395134047[22] = 0;
   out_7556302766395134047[23] = 0;
   out_7556302766395134047[24] = 0;
   out_7556302766395134047[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7556302766395134047[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7556302766395134047[27] = 0;
   out_7556302766395134047[28] = 0;
   out_7556302766395134047[29] = 0;
   out_7556302766395134047[30] = 0;
   out_7556302766395134047[31] = 0;
   out_7556302766395134047[32] = 0;
   out_7556302766395134047[33] = 0;
   out_7556302766395134047[34] = 0;
   out_7556302766395134047[35] = 0;
   out_7556302766395134047[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7556302766395134047[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7556302766395134047[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7556302766395134047[39] = 0;
   out_7556302766395134047[40] = 0;
   out_7556302766395134047[41] = 0;
   out_7556302766395134047[42] = 0;
   out_7556302766395134047[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7556302766395134047[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7556302766395134047[45] = 0;
   out_7556302766395134047[46] = 0;
   out_7556302766395134047[47] = 0;
   out_7556302766395134047[48] = 0;
   out_7556302766395134047[49] = 0;
   out_7556302766395134047[50] = 0;
   out_7556302766395134047[51] = 0;
   out_7556302766395134047[52] = 0;
   out_7556302766395134047[53] = 0;
   out_7556302766395134047[54] = 0;
   out_7556302766395134047[55] = 0;
   out_7556302766395134047[56] = 0;
   out_7556302766395134047[57] = 1;
   out_7556302766395134047[58] = 0;
   out_7556302766395134047[59] = 0;
   out_7556302766395134047[60] = 0;
   out_7556302766395134047[61] = 0;
   out_7556302766395134047[62] = 0;
   out_7556302766395134047[63] = 0;
   out_7556302766395134047[64] = 0;
   out_7556302766395134047[65] = 0;
   out_7556302766395134047[66] = dt;
   out_7556302766395134047[67] = 0;
   out_7556302766395134047[68] = 0;
   out_7556302766395134047[69] = 0;
   out_7556302766395134047[70] = 0;
   out_7556302766395134047[71] = 0;
   out_7556302766395134047[72] = 0;
   out_7556302766395134047[73] = 0;
   out_7556302766395134047[74] = 0;
   out_7556302766395134047[75] = 0;
   out_7556302766395134047[76] = 1;
   out_7556302766395134047[77] = 0;
   out_7556302766395134047[78] = 0;
   out_7556302766395134047[79] = 0;
   out_7556302766395134047[80] = 0;
   out_7556302766395134047[81] = 0;
   out_7556302766395134047[82] = 0;
   out_7556302766395134047[83] = 0;
   out_7556302766395134047[84] = 0;
   out_7556302766395134047[85] = dt;
   out_7556302766395134047[86] = 0;
   out_7556302766395134047[87] = 0;
   out_7556302766395134047[88] = 0;
   out_7556302766395134047[89] = 0;
   out_7556302766395134047[90] = 0;
   out_7556302766395134047[91] = 0;
   out_7556302766395134047[92] = 0;
   out_7556302766395134047[93] = 0;
   out_7556302766395134047[94] = 0;
   out_7556302766395134047[95] = 1;
   out_7556302766395134047[96] = 0;
   out_7556302766395134047[97] = 0;
   out_7556302766395134047[98] = 0;
   out_7556302766395134047[99] = 0;
   out_7556302766395134047[100] = 0;
   out_7556302766395134047[101] = 0;
   out_7556302766395134047[102] = 0;
   out_7556302766395134047[103] = 0;
   out_7556302766395134047[104] = dt;
   out_7556302766395134047[105] = 0;
   out_7556302766395134047[106] = 0;
   out_7556302766395134047[107] = 0;
   out_7556302766395134047[108] = 0;
   out_7556302766395134047[109] = 0;
   out_7556302766395134047[110] = 0;
   out_7556302766395134047[111] = 0;
   out_7556302766395134047[112] = 0;
   out_7556302766395134047[113] = 0;
   out_7556302766395134047[114] = 1;
   out_7556302766395134047[115] = 0;
   out_7556302766395134047[116] = 0;
   out_7556302766395134047[117] = 0;
   out_7556302766395134047[118] = 0;
   out_7556302766395134047[119] = 0;
   out_7556302766395134047[120] = 0;
   out_7556302766395134047[121] = 0;
   out_7556302766395134047[122] = 0;
   out_7556302766395134047[123] = 0;
   out_7556302766395134047[124] = 0;
   out_7556302766395134047[125] = 0;
   out_7556302766395134047[126] = 0;
   out_7556302766395134047[127] = 0;
   out_7556302766395134047[128] = 0;
   out_7556302766395134047[129] = 0;
   out_7556302766395134047[130] = 0;
   out_7556302766395134047[131] = 0;
   out_7556302766395134047[132] = 0;
   out_7556302766395134047[133] = 1;
   out_7556302766395134047[134] = 0;
   out_7556302766395134047[135] = 0;
   out_7556302766395134047[136] = 0;
   out_7556302766395134047[137] = 0;
   out_7556302766395134047[138] = 0;
   out_7556302766395134047[139] = 0;
   out_7556302766395134047[140] = 0;
   out_7556302766395134047[141] = 0;
   out_7556302766395134047[142] = 0;
   out_7556302766395134047[143] = 0;
   out_7556302766395134047[144] = 0;
   out_7556302766395134047[145] = 0;
   out_7556302766395134047[146] = 0;
   out_7556302766395134047[147] = 0;
   out_7556302766395134047[148] = 0;
   out_7556302766395134047[149] = 0;
   out_7556302766395134047[150] = 0;
   out_7556302766395134047[151] = 0;
   out_7556302766395134047[152] = 1;
   out_7556302766395134047[153] = 0;
   out_7556302766395134047[154] = 0;
   out_7556302766395134047[155] = 0;
   out_7556302766395134047[156] = 0;
   out_7556302766395134047[157] = 0;
   out_7556302766395134047[158] = 0;
   out_7556302766395134047[159] = 0;
   out_7556302766395134047[160] = 0;
   out_7556302766395134047[161] = 0;
   out_7556302766395134047[162] = 0;
   out_7556302766395134047[163] = 0;
   out_7556302766395134047[164] = 0;
   out_7556302766395134047[165] = 0;
   out_7556302766395134047[166] = 0;
   out_7556302766395134047[167] = 0;
   out_7556302766395134047[168] = 0;
   out_7556302766395134047[169] = 0;
   out_7556302766395134047[170] = 0;
   out_7556302766395134047[171] = 1;
   out_7556302766395134047[172] = 0;
   out_7556302766395134047[173] = 0;
   out_7556302766395134047[174] = 0;
   out_7556302766395134047[175] = 0;
   out_7556302766395134047[176] = 0;
   out_7556302766395134047[177] = 0;
   out_7556302766395134047[178] = 0;
   out_7556302766395134047[179] = 0;
   out_7556302766395134047[180] = 0;
   out_7556302766395134047[181] = 0;
   out_7556302766395134047[182] = 0;
   out_7556302766395134047[183] = 0;
   out_7556302766395134047[184] = 0;
   out_7556302766395134047[185] = 0;
   out_7556302766395134047[186] = 0;
   out_7556302766395134047[187] = 0;
   out_7556302766395134047[188] = 0;
   out_7556302766395134047[189] = 0;
   out_7556302766395134047[190] = 1;
   out_7556302766395134047[191] = 0;
   out_7556302766395134047[192] = 0;
   out_7556302766395134047[193] = 0;
   out_7556302766395134047[194] = 0;
   out_7556302766395134047[195] = 0;
   out_7556302766395134047[196] = 0;
   out_7556302766395134047[197] = 0;
   out_7556302766395134047[198] = 0;
   out_7556302766395134047[199] = 0;
   out_7556302766395134047[200] = 0;
   out_7556302766395134047[201] = 0;
   out_7556302766395134047[202] = 0;
   out_7556302766395134047[203] = 0;
   out_7556302766395134047[204] = 0;
   out_7556302766395134047[205] = 0;
   out_7556302766395134047[206] = 0;
   out_7556302766395134047[207] = 0;
   out_7556302766395134047[208] = 0;
   out_7556302766395134047[209] = 1;
   out_7556302766395134047[210] = 0;
   out_7556302766395134047[211] = 0;
   out_7556302766395134047[212] = 0;
   out_7556302766395134047[213] = 0;
   out_7556302766395134047[214] = 0;
   out_7556302766395134047[215] = 0;
   out_7556302766395134047[216] = 0;
   out_7556302766395134047[217] = 0;
   out_7556302766395134047[218] = 0;
   out_7556302766395134047[219] = 0;
   out_7556302766395134047[220] = 0;
   out_7556302766395134047[221] = 0;
   out_7556302766395134047[222] = 0;
   out_7556302766395134047[223] = 0;
   out_7556302766395134047[224] = 0;
   out_7556302766395134047[225] = 0;
   out_7556302766395134047[226] = 0;
   out_7556302766395134047[227] = 0;
   out_7556302766395134047[228] = 1;
   out_7556302766395134047[229] = 0;
   out_7556302766395134047[230] = 0;
   out_7556302766395134047[231] = 0;
   out_7556302766395134047[232] = 0;
   out_7556302766395134047[233] = 0;
   out_7556302766395134047[234] = 0;
   out_7556302766395134047[235] = 0;
   out_7556302766395134047[236] = 0;
   out_7556302766395134047[237] = 0;
   out_7556302766395134047[238] = 0;
   out_7556302766395134047[239] = 0;
   out_7556302766395134047[240] = 0;
   out_7556302766395134047[241] = 0;
   out_7556302766395134047[242] = 0;
   out_7556302766395134047[243] = 0;
   out_7556302766395134047[244] = 0;
   out_7556302766395134047[245] = 0;
   out_7556302766395134047[246] = 0;
   out_7556302766395134047[247] = 1;
   out_7556302766395134047[248] = 0;
   out_7556302766395134047[249] = 0;
   out_7556302766395134047[250] = 0;
   out_7556302766395134047[251] = 0;
   out_7556302766395134047[252] = 0;
   out_7556302766395134047[253] = 0;
   out_7556302766395134047[254] = 0;
   out_7556302766395134047[255] = 0;
   out_7556302766395134047[256] = 0;
   out_7556302766395134047[257] = 0;
   out_7556302766395134047[258] = 0;
   out_7556302766395134047[259] = 0;
   out_7556302766395134047[260] = 0;
   out_7556302766395134047[261] = 0;
   out_7556302766395134047[262] = 0;
   out_7556302766395134047[263] = 0;
   out_7556302766395134047[264] = 0;
   out_7556302766395134047[265] = 0;
   out_7556302766395134047[266] = 1;
   out_7556302766395134047[267] = 0;
   out_7556302766395134047[268] = 0;
   out_7556302766395134047[269] = 0;
   out_7556302766395134047[270] = 0;
   out_7556302766395134047[271] = 0;
   out_7556302766395134047[272] = 0;
   out_7556302766395134047[273] = 0;
   out_7556302766395134047[274] = 0;
   out_7556302766395134047[275] = 0;
   out_7556302766395134047[276] = 0;
   out_7556302766395134047[277] = 0;
   out_7556302766395134047[278] = 0;
   out_7556302766395134047[279] = 0;
   out_7556302766395134047[280] = 0;
   out_7556302766395134047[281] = 0;
   out_7556302766395134047[282] = 0;
   out_7556302766395134047[283] = 0;
   out_7556302766395134047[284] = 0;
   out_7556302766395134047[285] = 1;
   out_7556302766395134047[286] = 0;
   out_7556302766395134047[287] = 0;
   out_7556302766395134047[288] = 0;
   out_7556302766395134047[289] = 0;
   out_7556302766395134047[290] = 0;
   out_7556302766395134047[291] = 0;
   out_7556302766395134047[292] = 0;
   out_7556302766395134047[293] = 0;
   out_7556302766395134047[294] = 0;
   out_7556302766395134047[295] = 0;
   out_7556302766395134047[296] = 0;
   out_7556302766395134047[297] = 0;
   out_7556302766395134047[298] = 0;
   out_7556302766395134047[299] = 0;
   out_7556302766395134047[300] = 0;
   out_7556302766395134047[301] = 0;
   out_7556302766395134047[302] = 0;
   out_7556302766395134047[303] = 0;
   out_7556302766395134047[304] = 1;
   out_7556302766395134047[305] = 0;
   out_7556302766395134047[306] = 0;
   out_7556302766395134047[307] = 0;
   out_7556302766395134047[308] = 0;
   out_7556302766395134047[309] = 0;
   out_7556302766395134047[310] = 0;
   out_7556302766395134047[311] = 0;
   out_7556302766395134047[312] = 0;
   out_7556302766395134047[313] = 0;
   out_7556302766395134047[314] = 0;
   out_7556302766395134047[315] = 0;
   out_7556302766395134047[316] = 0;
   out_7556302766395134047[317] = 0;
   out_7556302766395134047[318] = 0;
   out_7556302766395134047[319] = 0;
   out_7556302766395134047[320] = 0;
   out_7556302766395134047[321] = 0;
   out_7556302766395134047[322] = 0;
   out_7556302766395134047[323] = 1;
}
void h_4(double *state, double *unused, double *out_8616831018009531357) {
   out_8616831018009531357[0] = state[6] + state[9];
   out_8616831018009531357[1] = state[7] + state[10];
   out_8616831018009531357[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_603353465574763679) {
   out_603353465574763679[0] = 0;
   out_603353465574763679[1] = 0;
   out_603353465574763679[2] = 0;
   out_603353465574763679[3] = 0;
   out_603353465574763679[4] = 0;
   out_603353465574763679[5] = 0;
   out_603353465574763679[6] = 1;
   out_603353465574763679[7] = 0;
   out_603353465574763679[8] = 0;
   out_603353465574763679[9] = 1;
   out_603353465574763679[10] = 0;
   out_603353465574763679[11] = 0;
   out_603353465574763679[12] = 0;
   out_603353465574763679[13] = 0;
   out_603353465574763679[14] = 0;
   out_603353465574763679[15] = 0;
   out_603353465574763679[16] = 0;
   out_603353465574763679[17] = 0;
   out_603353465574763679[18] = 0;
   out_603353465574763679[19] = 0;
   out_603353465574763679[20] = 0;
   out_603353465574763679[21] = 0;
   out_603353465574763679[22] = 0;
   out_603353465574763679[23] = 0;
   out_603353465574763679[24] = 0;
   out_603353465574763679[25] = 1;
   out_603353465574763679[26] = 0;
   out_603353465574763679[27] = 0;
   out_603353465574763679[28] = 1;
   out_603353465574763679[29] = 0;
   out_603353465574763679[30] = 0;
   out_603353465574763679[31] = 0;
   out_603353465574763679[32] = 0;
   out_603353465574763679[33] = 0;
   out_603353465574763679[34] = 0;
   out_603353465574763679[35] = 0;
   out_603353465574763679[36] = 0;
   out_603353465574763679[37] = 0;
   out_603353465574763679[38] = 0;
   out_603353465574763679[39] = 0;
   out_603353465574763679[40] = 0;
   out_603353465574763679[41] = 0;
   out_603353465574763679[42] = 0;
   out_603353465574763679[43] = 0;
   out_603353465574763679[44] = 1;
   out_603353465574763679[45] = 0;
   out_603353465574763679[46] = 0;
   out_603353465574763679[47] = 1;
   out_603353465574763679[48] = 0;
   out_603353465574763679[49] = 0;
   out_603353465574763679[50] = 0;
   out_603353465574763679[51] = 0;
   out_603353465574763679[52] = 0;
   out_603353465574763679[53] = 0;
}
void h_10(double *state, double *unused, double *out_4956865148383568303) {
   out_4956865148383568303[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4956865148383568303[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4956865148383568303[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6422333739801875195) {
   out_6422333739801875195[0] = 0;
   out_6422333739801875195[1] = 9.8100000000000005*cos(state[1]);
   out_6422333739801875195[2] = 0;
   out_6422333739801875195[3] = 0;
   out_6422333739801875195[4] = -state[8];
   out_6422333739801875195[5] = state[7];
   out_6422333739801875195[6] = 0;
   out_6422333739801875195[7] = state[5];
   out_6422333739801875195[8] = -state[4];
   out_6422333739801875195[9] = 0;
   out_6422333739801875195[10] = 0;
   out_6422333739801875195[11] = 0;
   out_6422333739801875195[12] = 1;
   out_6422333739801875195[13] = 0;
   out_6422333739801875195[14] = 0;
   out_6422333739801875195[15] = 1;
   out_6422333739801875195[16] = 0;
   out_6422333739801875195[17] = 0;
   out_6422333739801875195[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6422333739801875195[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6422333739801875195[20] = 0;
   out_6422333739801875195[21] = state[8];
   out_6422333739801875195[22] = 0;
   out_6422333739801875195[23] = -state[6];
   out_6422333739801875195[24] = -state[5];
   out_6422333739801875195[25] = 0;
   out_6422333739801875195[26] = state[3];
   out_6422333739801875195[27] = 0;
   out_6422333739801875195[28] = 0;
   out_6422333739801875195[29] = 0;
   out_6422333739801875195[30] = 0;
   out_6422333739801875195[31] = 1;
   out_6422333739801875195[32] = 0;
   out_6422333739801875195[33] = 0;
   out_6422333739801875195[34] = 1;
   out_6422333739801875195[35] = 0;
   out_6422333739801875195[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6422333739801875195[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6422333739801875195[38] = 0;
   out_6422333739801875195[39] = -state[7];
   out_6422333739801875195[40] = state[6];
   out_6422333739801875195[41] = 0;
   out_6422333739801875195[42] = state[4];
   out_6422333739801875195[43] = -state[3];
   out_6422333739801875195[44] = 0;
   out_6422333739801875195[45] = 0;
   out_6422333739801875195[46] = 0;
   out_6422333739801875195[47] = 0;
   out_6422333739801875195[48] = 0;
   out_6422333739801875195[49] = 0;
   out_6422333739801875195[50] = 1;
   out_6422333739801875195[51] = 0;
   out_6422333739801875195[52] = 0;
   out_6422333739801875195[53] = 1;
}
void h_13(double *state, double *unused, double *out_8713729594127404972) {
   out_8713729594127404972[0] = state[3];
   out_8713729594127404972[1] = state[4];
   out_8713729594127404972[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8213984673891464608) {
   out_8213984673891464608[0] = 0;
   out_8213984673891464608[1] = 0;
   out_8213984673891464608[2] = 0;
   out_8213984673891464608[3] = 1;
   out_8213984673891464608[4] = 0;
   out_8213984673891464608[5] = 0;
   out_8213984673891464608[6] = 0;
   out_8213984673891464608[7] = 0;
   out_8213984673891464608[8] = 0;
   out_8213984673891464608[9] = 0;
   out_8213984673891464608[10] = 0;
   out_8213984673891464608[11] = 0;
   out_8213984673891464608[12] = 0;
   out_8213984673891464608[13] = 0;
   out_8213984673891464608[14] = 0;
   out_8213984673891464608[15] = 0;
   out_8213984673891464608[16] = 0;
   out_8213984673891464608[17] = 0;
   out_8213984673891464608[18] = 0;
   out_8213984673891464608[19] = 0;
   out_8213984673891464608[20] = 0;
   out_8213984673891464608[21] = 0;
   out_8213984673891464608[22] = 1;
   out_8213984673891464608[23] = 0;
   out_8213984673891464608[24] = 0;
   out_8213984673891464608[25] = 0;
   out_8213984673891464608[26] = 0;
   out_8213984673891464608[27] = 0;
   out_8213984673891464608[28] = 0;
   out_8213984673891464608[29] = 0;
   out_8213984673891464608[30] = 0;
   out_8213984673891464608[31] = 0;
   out_8213984673891464608[32] = 0;
   out_8213984673891464608[33] = 0;
   out_8213984673891464608[34] = 0;
   out_8213984673891464608[35] = 0;
   out_8213984673891464608[36] = 0;
   out_8213984673891464608[37] = 0;
   out_8213984673891464608[38] = 0;
   out_8213984673891464608[39] = 0;
   out_8213984673891464608[40] = 0;
   out_8213984673891464608[41] = 1;
   out_8213984673891464608[42] = 0;
   out_8213984673891464608[43] = 0;
   out_8213984673891464608[44] = 0;
   out_8213984673891464608[45] = 0;
   out_8213984673891464608[46] = 0;
   out_8213984673891464608[47] = 0;
   out_8213984673891464608[48] = 0;
   out_8213984673891464608[49] = 0;
   out_8213984673891464608[50] = 0;
   out_8213984673891464608[51] = 0;
   out_8213984673891464608[52] = 0;
   out_8213984673891464608[53] = 0;
}
void h_14(double *state, double *unused, double *out_1912344082414302298) {
   out_1912344082414302298[0] = state[6];
   out_1912344082414302298[1] = state[7];
   out_1912344082414302298[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4566594321914248208) {
   out_4566594321914248208[0] = 0;
   out_4566594321914248208[1] = 0;
   out_4566594321914248208[2] = 0;
   out_4566594321914248208[3] = 0;
   out_4566594321914248208[4] = 0;
   out_4566594321914248208[5] = 0;
   out_4566594321914248208[6] = 1;
   out_4566594321914248208[7] = 0;
   out_4566594321914248208[8] = 0;
   out_4566594321914248208[9] = 0;
   out_4566594321914248208[10] = 0;
   out_4566594321914248208[11] = 0;
   out_4566594321914248208[12] = 0;
   out_4566594321914248208[13] = 0;
   out_4566594321914248208[14] = 0;
   out_4566594321914248208[15] = 0;
   out_4566594321914248208[16] = 0;
   out_4566594321914248208[17] = 0;
   out_4566594321914248208[18] = 0;
   out_4566594321914248208[19] = 0;
   out_4566594321914248208[20] = 0;
   out_4566594321914248208[21] = 0;
   out_4566594321914248208[22] = 0;
   out_4566594321914248208[23] = 0;
   out_4566594321914248208[24] = 0;
   out_4566594321914248208[25] = 1;
   out_4566594321914248208[26] = 0;
   out_4566594321914248208[27] = 0;
   out_4566594321914248208[28] = 0;
   out_4566594321914248208[29] = 0;
   out_4566594321914248208[30] = 0;
   out_4566594321914248208[31] = 0;
   out_4566594321914248208[32] = 0;
   out_4566594321914248208[33] = 0;
   out_4566594321914248208[34] = 0;
   out_4566594321914248208[35] = 0;
   out_4566594321914248208[36] = 0;
   out_4566594321914248208[37] = 0;
   out_4566594321914248208[38] = 0;
   out_4566594321914248208[39] = 0;
   out_4566594321914248208[40] = 0;
   out_4566594321914248208[41] = 0;
   out_4566594321914248208[42] = 0;
   out_4566594321914248208[43] = 0;
   out_4566594321914248208[44] = 1;
   out_4566594321914248208[45] = 0;
   out_4566594321914248208[46] = 0;
   out_4566594321914248208[47] = 0;
   out_4566594321914248208[48] = 0;
   out_4566594321914248208[49] = 0;
   out_4566594321914248208[50] = 0;
   out_4566594321914248208[51] = 0;
   out_4566594321914248208[52] = 0;
   out_4566594321914248208[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3009149682027724813) {
  err_fun(nom_x, delta_x, out_3009149682027724813);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6241253285121461636) {
  inv_err_fun(nom_x, true_x, out_6241253285121461636);
}
void pose_H_mod_fun(double *state, double *out_3247087395785811549) {
  H_mod_fun(state, out_3247087395785811549);
}
void pose_f_fun(double *state, double dt, double *out_8180428593278352040) {
  f_fun(state,  dt, out_8180428593278352040);
}
void pose_F_fun(double *state, double dt, double *out_7556302766395134047) {
  F_fun(state,  dt, out_7556302766395134047);
}
void pose_h_4(double *state, double *unused, double *out_8616831018009531357) {
  h_4(state, unused, out_8616831018009531357);
}
void pose_H_4(double *state, double *unused, double *out_603353465574763679) {
  H_4(state, unused, out_603353465574763679);
}
void pose_h_10(double *state, double *unused, double *out_4956865148383568303) {
  h_10(state, unused, out_4956865148383568303);
}
void pose_H_10(double *state, double *unused, double *out_6422333739801875195) {
  H_10(state, unused, out_6422333739801875195);
}
void pose_h_13(double *state, double *unused, double *out_8713729594127404972) {
  h_13(state, unused, out_8713729594127404972);
}
void pose_H_13(double *state, double *unused, double *out_8213984673891464608) {
  H_13(state, unused, out_8213984673891464608);
}
void pose_h_14(double *state, double *unused, double *out_1912344082414302298) {
  h_14(state, unused, out_1912344082414302298);
}
void pose_H_14(double *state, double *unused, double *out_4566594321914248208) {
  H_14(state, unused, out_4566594321914248208);
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
