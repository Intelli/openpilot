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
void err_fun(double *nom_x, double *delta_x, double *out_7076630439446261590) {
   out_7076630439446261590[0] = delta_x[0] + nom_x[0];
   out_7076630439446261590[1] = delta_x[1] + nom_x[1];
   out_7076630439446261590[2] = delta_x[2] + nom_x[2];
   out_7076630439446261590[3] = delta_x[3] + nom_x[3];
   out_7076630439446261590[4] = delta_x[4] + nom_x[4];
   out_7076630439446261590[5] = delta_x[5] + nom_x[5];
   out_7076630439446261590[6] = delta_x[6] + nom_x[6];
   out_7076630439446261590[7] = delta_x[7] + nom_x[7];
   out_7076630439446261590[8] = delta_x[8] + nom_x[8];
   out_7076630439446261590[9] = delta_x[9] + nom_x[9];
   out_7076630439446261590[10] = delta_x[10] + nom_x[10];
   out_7076630439446261590[11] = delta_x[11] + nom_x[11];
   out_7076630439446261590[12] = delta_x[12] + nom_x[12];
   out_7076630439446261590[13] = delta_x[13] + nom_x[13];
   out_7076630439446261590[14] = delta_x[14] + nom_x[14];
   out_7076630439446261590[15] = delta_x[15] + nom_x[15];
   out_7076630439446261590[16] = delta_x[16] + nom_x[16];
   out_7076630439446261590[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2828328233536285037) {
   out_2828328233536285037[0] = -nom_x[0] + true_x[0];
   out_2828328233536285037[1] = -nom_x[1] + true_x[1];
   out_2828328233536285037[2] = -nom_x[2] + true_x[2];
   out_2828328233536285037[3] = -nom_x[3] + true_x[3];
   out_2828328233536285037[4] = -nom_x[4] + true_x[4];
   out_2828328233536285037[5] = -nom_x[5] + true_x[5];
   out_2828328233536285037[6] = -nom_x[6] + true_x[6];
   out_2828328233536285037[7] = -nom_x[7] + true_x[7];
   out_2828328233536285037[8] = -nom_x[8] + true_x[8];
   out_2828328233536285037[9] = -nom_x[9] + true_x[9];
   out_2828328233536285037[10] = -nom_x[10] + true_x[10];
   out_2828328233536285037[11] = -nom_x[11] + true_x[11];
   out_2828328233536285037[12] = -nom_x[12] + true_x[12];
   out_2828328233536285037[13] = -nom_x[13] + true_x[13];
   out_2828328233536285037[14] = -nom_x[14] + true_x[14];
   out_2828328233536285037[15] = -nom_x[15] + true_x[15];
   out_2828328233536285037[16] = -nom_x[16] + true_x[16];
   out_2828328233536285037[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_180736316877999173) {
   out_180736316877999173[0] = 1.0;
   out_180736316877999173[1] = 0.0;
   out_180736316877999173[2] = 0.0;
   out_180736316877999173[3] = 0.0;
   out_180736316877999173[4] = 0.0;
   out_180736316877999173[5] = 0.0;
   out_180736316877999173[6] = 0.0;
   out_180736316877999173[7] = 0.0;
   out_180736316877999173[8] = 0.0;
   out_180736316877999173[9] = 0.0;
   out_180736316877999173[10] = 0.0;
   out_180736316877999173[11] = 0.0;
   out_180736316877999173[12] = 0.0;
   out_180736316877999173[13] = 0.0;
   out_180736316877999173[14] = 0.0;
   out_180736316877999173[15] = 0.0;
   out_180736316877999173[16] = 0.0;
   out_180736316877999173[17] = 0.0;
   out_180736316877999173[18] = 0.0;
   out_180736316877999173[19] = 1.0;
   out_180736316877999173[20] = 0.0;
   out_180736316877999173[21] = 0.0;
   out_180736316877999173[22] = 0.0;
   out_180736316877999173[23] = 0.0;
   out_180736316877999173[24] = 0.0;
   out_180736316877999173[25] = 0.0;
   out_180736316877999173[26] = 0.0;
   out_180736316877999173[27] = 0.0;
   out_180736316877999173[28] = 0.0;
   out_180736316877999173[29] = 0.0;
   out_180736316877999173[30] = 0.0;
   out_180736316877999173[31] = 0.0;
   out_180736316877999173[32] = 0.0;
   out_180736316877999173[33] = 0.0;
   out_180736316877999173[34] = 0.0;
   out_180736316877999173[35] = 0.0;
   out_180736316877999173[36] = 0.0;
   out_180736316877999173[37] = 0.0;
   out_180736316877999173[38] = 1.0;
   out_180736316877999173[39] = 0.0;
   out_180736316877999173[40] = 0.0;
   out_180736316877999173[41] = 0.0;
   out_180736316877999173[42] = 0.0;
   out_180736316877999173[43] = 0.0;
   out_180736316877999173[44] = 0.0;
   out_180736316877999173[45] = 0.0;
   out_180736316877999173[46] = 0.0;
   out_180736316877999173[47] = 0.0;
   out_180736316877999173[48] = 0.0;
   out_180736316877999173[49] = 0.0;
   out_180736316877999173[50] = 0.0;
   out_180736316877999173[51] = 0.0;
   out_180736316877999173[52] = 0.0;
   out_180736316877999173[53] = 0.0;
   out_180736316877999173[54] = 0.0;
   out_180736316877999173[55] = 0.0;
   out_180736316877999173[56] = 0.0;
   out_180736316877999173[57] = 1.0;
   out_180736316877999173[58] = 0.0;
   out_180736316877999173[59] = 0.0;
   out_180736316877999173[60] = 0.0;
   out_180736316877999173[61] = 0.0;
   out_180736316877999173[62] = 0.0;
   out_180736316877999173[63] = 0.0;
   out_180736316877999173[64] = 0.0;
   out_180736316877999173[65] = 0.0;
   out_180736316877999173[66] = 0.0;
   out_180736316877999173[67] = 0.0;
   out_180736316877999173[68] = 0.0;
   out_180736316877999173[69] = 0.0;
   out_180736316877999173[70] = 0.0;
   out_180736316877999173[71] = 0.0;
   out_180736316877999173[72] = 0.0;
   out_180736316877999173[73] = 0.0;
   out_180736316877999173[74] = 0.0;
   out_180736316877999173[75] = 0.0;
   out_180736316877999173[76] = 1.0;
   out_180736316877999173[77] = 0.0;
   out_180736316877999173[78] = 0.0;
   out_180736316877999173[79] = 0.0;
   out_180736316877999173[80] = 0.0;
   out_180736316877999173[81] = 0.0;
   out_180736316877999173[82] = 0.0;
   out_180736316877999173[83] = 0.0;
   out_180736316877999173[84] = 0.0;
   out_180736316877999173[85] = 0.0;
   out_180736316877999173[86] = 0.0;
   out_180736316877999173[87] = 0.0;
   out_180736316877999173[88] = 0.0;
   out_180736316877999173[89] = 0.0;
   out_180736316877999173[90] = 0.0;
   out_180736316877999173[91] = 0.0;
   out_180736316877999173[92] = 0.0;
   out_180736316877999173[93] = 0.0;
   out_180736316877999173[94] = 0.0;
   out_180736316877999173[95] = 1.0;
   out_180736316877999173[96] = 0.0;
   out_180736316877999173[97] = 0.0;
   out_180736316877999173[98] = 0.0;
   out_180736316877999173[99] = 0.0;
   out_180736316877999173[100] = 0.0;
   out_180736316877999173[101] = 0.0;
   out_180736316877999173[102] = 0.0;
   out_180736316877999173[103] = 0.0;
   out_180736316877999173[104] = 0.0;
   out_180736316877999173[105] = 0.0;
   out_180736316877999173[106] = 0.0;
   out_180736316877999173[107] = 0.0;
   out_180736316877999173[108] = 0.0;
   out_180736316877999173[109] = 0.0;
   out_180736316877999173[110] = 0.0;
   out_180736316877999173[111] = 0.0;
   out_180736316877999173[112] = 0.0;
   out_180736316877999173[113] = 0.0;
   out_180736316877999173[114] = 1.0;
   out_180736316877999173[115] = 0.0;
   out_180736316877999173[116] = 0.0;
   out_180736316877999173[117] = 0.0;
   out_180736316877999173[118] = 0.0;
   out_180736316877999173[119] = 0.0;
   out_180736316877999173[120] = 0.0;
   out_180736316877999173[121] = 0.0;
   out_180736316877999173[122] = 0.0;
   out_180736316877999173[123] = 0.0;
   out_180736316877999173[124] = 0.0;
   out_180736316877999173[125] = 0.0;
   out_180736316877999173[126] = 0.0;
   out_180736316877999173[127] = 0.0;
   out_180736316877999173[128] = 0.0;
   out_180736316877999173[129] = 0.0;
   out_180736316877999173[130] = 0.0;
   out_180736316877999173[131] = 0.0;
   out_180736316877999173[132] = 0.0;
   out_180736316877999173[133] = 1.0;
   out_180736316877999173[134] = 0.0;
   out_180736316877999173[135] = 0.0;
   out_180736316877999173[136] = 0.0;
   out_180736316877999173[137] = 0.0;
   out_180736316877999173[138] = 0.0;
   out_180736316877999173[139] = 0.0;
   out_180736316877999173[140] = 0.0;
   out_180736316877999173[141] = 0.0;
   out_180736316877999173[142] = 0.0;
   out_180736316877999173[143] = 0.0;
   out_180736316877999173[144] = 0.0;
   out_180736316877999173[145] = 0.0;
   out_180736316877999173[146] = 0.0;
   out_180736316877999173[147] = 0.0;
   out_180736316877999173[148] = 0.0;
   out_180736316877999173[149] = 0.0;
   out_180736316877999173[150] = 0.0;
   out_180736316877999173[151] = 0.0;
   out_180736316877999173[152] = 1.0;
   out_180736316877999173[153] = 0.0;
   out_180736316877999173[154] = 0.0;
   out_180736316877999173[155] = 0.0;
   out_180736316877999173[156] = 0.0;
   out_180736316877999173[157] = 0.0;
   out_180736316877999173[158] = 0.0;
   out_180736316877999173[159] = 0.0;
   out_180736316877999173[160] = 0.0;
   out_180736316877999173[161] = 0.0;
   out_180736316877999173[162] = 0.0;
   out_180736316877999173[163] = 0.0;
   out_180736316877999173[164] = 0.0;
   out_180736316877999173[165] = 0.0;
   out_180736316877999173[166] = 0.0;
   out_180736316877999173[167] = 0.0;
   out_180736316877999173[168] = 0.0;
   out_180736316877999173[169] = 0.0;
   out_180736316877999173[170] = 0.0;
   out_180736316877999173[171] = 1.0;
   out_180736316877999173[172] = 0.0;
   out_180736316877999173[173] = 0.0;
   out_180736316877999173[174] = 0.0;
   out_180736316877999173[175] = 0.0;
   out_180736316877999173[176] = 0.0;
   out_180736316877999173[177] = 0.0;
   out_180736316877999173[178] = 0.0;
   out_180736316877999173[179] = 0.0;
   out_180736316877999173[180] = 0.0;
   out_180736316877999173[181] = 0.0;
   out_180736316877999173[182] = 0.0;
   out_180736316877999173[183] = 0.0;
   out_180736316877999173[184] = 0.0;
   out_180736316877999173[185] = 0.0;
   out_180736316877999173[186] = 0.0;
   out_180736316877999173[187] = 0.0;
   out_180736316877999173[188] = 0.0;
   out_180736316877999173[189] = 0.0;
   out_180736316877999173[190] = 1.0;
   out_180736316877999173[191] = 0.0;
   out_180736316877999173[192] = 0.0;
   out_180736316877999173[193] = 0.0;
   out_180736316877999173[194] = 0.0;
   out_180736316877999173[195] = 0.0;
   out_180736316877999173[196] = 0.0;
   out_180736316877999173[197] = 0.0;
   out_180736316877999173[198] = 0.0;
   out_180736316877999173[199] = 0.0;
   out_180736316877999173[200] = 0.0;
   out_180736316877999173[201] = 0.0;
   out_180736316877999173[202] = 0.0;
   out_180736316877999173[203] = 0.0;
   out_180736316877999173[204] = 0.0;
   out_180736316877999173[205] = 0.0;
   out_180736316877999173[206] = 0.0;
   out_180736316877999173[207] = 0.0;
   out_180736316877999173[208] = 0.0;
   out_180736316877999173[209] = 1.0;
   out_180736316877999173[210] = 0.0;
   out_180736316877999173[211] = 0.0;
   out_180736316877999173[212] = 0.0;
   out_180736316877999173[213] = 0.0;
   out_180736316877999173[214] = 0.0;
   out_180736316877999173[215] = 0.0;
   out_180736316877999173[216] = 0.0;
   out_180736316877999173[217] = 0.0;
   out_180736316877999173[218] = 0.0;
   out_180736316877999173[219] = 0.0;
   out_180736316877999173[220] = 0.0;
   out_180736316877999173[221] = 0.0;
   out_180736316877999173[222] = 0.0;
   out_180736316877999173[223] = 0.0;
   out_180736316877999173[224] = 0.0;
   out_180736316877999173[225] = 0.0;
   out_180736316877999173[226] = 0.0;
   out_180736316877999173[227] = 0.0;
   out_180736316877999173[228] = 1.0;
   out_180736316877999173[229] = 0.0;
   out_180736316877999173[230] = 0.0;
   out_180736316877999173[231] = 0.0;
   out_180736316877999173[232] = 0.0;
   out_180736316877999173[233] = 0.0;
   out_180736316877999173[234] = 0.0;
   out_180736316877999173[235] = 0.0;
   out_180736316877999173[236] = 0.0;
   out_180736316877999173[237] = 0.0;
   out_180736316877999173[238] = 0.0;
   out_180736316877999173[239] = 0.0;
   out_180736316877999173[240] = 0.0;
   out_180736316877999173[241] = 0.0;
   out_180736316877999173[242] = 0.0;
   out_180736316877999173[243] = 0.0;
   out_180736316877999173[244] = 0.0;
   out_180736316877999173[245] = 0.0;
   out_180736316877999173[246] = 0.0;
   out_180736316877999173[247] = 1.0;
   out_180736316877999173[248] = 0.0;
   out_180736316877999173[249] = 0.0;
   out_180736316877999173[250] = 0.0;
   out_180736316877999173[251] = 0.0;
   out_180736316877999173[252] = 0.0;
   out_180736316877999173[253] = 0.0;
   out_180736316877999173[254] = 0.0;
   out_180736316877999173[255] = 0.0;
   out_180736316877999173[256] = 0.0;
   out_180736316877999173[257] = 0.0;
   out_180736316877999173[258] = 0.0;
   out_180736316877999173[259] = 0.0;
   out_180736316877999173[260] = 0.0;
   out_180736316877999173[261] = 0.0;
   out_180736316877999173[262] = 0.0;
   out_180736316877999173[263] = 0.0;
   out_180736316877999173[264] = 0.0;
   out_180736316877999173[265] = 0.0;
   out_180736316877999173[266] = 1.0;
   out_180736316877999173[267] = 0.0;
   out_180736316877999173[268] = 0.0;
   out_180736316877999173[269] = 0.0;
   out_180736316877999173[270] = 0.0;
   out_180736316877999173[271] = 0.0;
   out_180736316877999173[272] = 0.0;
   out_180736316877999173[273] = 0.0;
   out_180736316877999173[274] = 0.0;
   out_180736316877999173[275] = 0.0;
   out_180736316877999173[276] = 0.0;
   out_180736316877999173[277] = 0.0;
   out_180736316877999173[278] = 0.0;
   out_180736316877999173[279] = 0.0;
   out_180736316877999173[280] = 0.0;
   out_180736316877999173[281] = 0.0;
   out_180736316877999173[282] = 0.0;
   out_180736316877999173[283] = 0.0;
   out_180736316877999173[284] = 0.0;
   out_180736316877999173[285] = 1.0;
   out_180736316877999173[286] = 0.0;
   out_180736316877999173[287] = 0.0;
   out_180736316877999173[288] = 0.0;
   out_180736316877999173[289] = 0.0;
   out_180736316877999173[290] = 0.0;
   out_180736316877999173[291] = 0.0;
   out_180736316877999173[292] = 0.0;
   out_180736316877999173[293] = 0.0;
   out_180736316877999173[294] = 0.0;
   out_180736316877999173[295] = 0.0;
   out_180736316877999173[296] = 0.0;
   out_180736316877999173[297] = 0.0;
   out_180736316877999173[298] = 0.0;
   out_180736316877999173[299] = 0.0;
   out_180736316877999173[300] = 0.0;
   out_180736316877999173[301] = 0.0;
   out_180736316877999173[302] = 0.0;
   out_180736316877999173[303] = 0.0;
   out_180736316877999173[304] = 1.0;
   out_180736316877999173[305] = 0.0;
   out_180736316877999173[306] = 0.0;
   out_180736316877999173[307] = 0.0;
   out_180736316877999173[308] = 0.0;
   out_180736316877999173[309] = 0.0;
   out_180736316877999173[310] = 0.0;
   out_180736316877999173[311] = 0.0;
   out_180736316877999173[312] = 0.0;
   out_180736316877999173[313] = 0.0;
   out_180736316877999173[314] = 0.0;
   out_180736316877999173[315] = 0.0;
   out_180736316877999173[316] = 0.0;
   out_180736316877999173[317] = 0.0;
   out_180736316877999173[318] = 0.0;
   out_180736316877999173[319] = 0.0;
   out_180736316877999173[320] = 0.0;
   out_180736316877999173[321] = 0.0;
   out_180736316877999173[322] = 0.0;
   out_180736316877999173[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3533683092462162875) {
   out_3533683092462162875[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3533683092462162875[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3533683092462162875[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3533683092462162875[3] = dt*state[12] + state[3];
   out_3533683092462162875[4] = dt*state[13] + state[4];
   out_3533683092462162875[5] = dt*state[14] + state[5];
   out_3533683092462162875[6] = state[6];
   out_3533683092462162875[7] = state[7];
   out_3533683092462162875[8] = state[8];
   out_3533683092462162875[9] = state[9];
   out_3533683092462162875[10] = state[10];
   out_3533683092462162875[11] = state[11];
   out_3533683092462162875[12] = state[12];
   out_3533683092462162875[13] = state[13];
   out_3533683092462162875[14] = state[14];
   out_3533683092462162875[15] = state[15];
   out_3533683092462162875[16] = state[16];
   out_3533683092462162875[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5100092372859724848) {
   out_5100092372859724848[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5100092372859724848[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5100092372859724848[2] = 0;
   out_5100092372859724848[3] = 0;
   out_5100092372859724848[4] = 0;
   out_5100092372859724848[5] = 0;
   out_5100092372859724848[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5100092372859724848[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5100092372859724848[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5100092372859724848[9] = 0;
   out_5100092372859724848[10] = 0;
   out_5100092372859724848[11] = 0;
   out_5100092372859724848[12] = 0;
   out_5100092372859724848[13] = 0;
   out_5100092372859724848[14] = 0;
   out_5100092372859724848[15] = 0;
   out_5100092372859724848[16] = 0;
   out_5100092372859724848[17] = 0;
   out_5100092372859724848[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5100092372859724848[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5100092372859724848[20] = 0;
   out_5100092372859724848[21] = 0;
   out_5100092372859724848[22] = 0;
   out_5100092372859724848[23] = 0;
   out_5100092372859724848[24] = 0;
   out_5100092372859724848[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5100092372859724848[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5100092372859724848[27] = 0;
   out_5100092372859724848[28] = 0;
   out_5100092372859724848[29] = 0;
   out_5100092372859724848[30] = 0;
   out_5100092372859724848[31] = 0;
   out_5100092372859724848[32] = 0;
   out_5100092372859724848[33] = 0;
   out_5100092372859724848[34] = 0;
   out_5100092372859724848[35] = 0;
   out_5100092372859724848[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5100092372859724848[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5100092372859724848[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5100092372859724848[39] = 0;
   out_5100092372859724848[40] = 0;
   out_5100092372859724848[41] = 0;
   out_5100092372859724848[42] = 0;
   out_5100092372859724848[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5100092372859724848[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5100092372859724848[45] = 0;
   out_5100092372859724848[46] = 0;
   out_5100092372859724848[47] = 0;
   out_5100092372859724848[48] = 0;
   out_5100092372859724848[49] = 0;
   out_5100092372859724848[50] = 0;
   out_5100092372859724848[51] = 0;
   out_5100092372859724848[52] = 0;
   out_5100092372859724848[53] = 0;
   out_5100092372859724848[54] = 0;
   out_5100092372859724848[55] = 0;
   out_5100092372859724848[56] = 0;
   out_5100092372859724848[57] = 1;
   out_5100092372859724848[58] = 0;
   out_5100092372859724848[59] = 0;
   out_5100092372859724848[60] = 0;
   out_5100092372859724848[61] = 0;
   out_5100092372859724848[62] = 0;
   out_5100092372859724848[63] = 0;
   out_5100092372859724848[64] = 0;
   out_5100092372859724848[65] = 0;
   out_5100092372859724848[66] = dt;
   out_5100092372859724848[67] = 0;
   out_5100092372859724848[68] = 0;
   out_5100092372859724848[69] = 0;
   out_5100092372859724848[70] = 0;
   out_5100092372859724848[71] = 0;
   out_5100092372859724848[72] = 0;
   out_5100092372859724848[73] = 0;
   out_5100092372859724848[74] = 0;
   out_5100092372859724848[75] = 0;
   out_5100092372859724848[76] = 1;
   out_5100092372859724848[77] = 0;
   out_5100092372859724848[78] = 0;
   out_5100092372859724848[79] = 0;
   out_5100092372859724848[80] = 0;
   out_5100092372859724848[81] = 0;
   out_5100092372859724848[82] = 0;
   out_5100092372859724848[83] = 0;
   out_5100092372859724848[84] = 0;
   out_5100092372859724848[85] = dt;
   out_5100092372859724848[86] = 0;
   out_5100092372859724848[87] = 0;
   out_5100092372859724848[88] = 0;
   out_5100092372859724848[89] = 0;
   out_5100092372859724848[90] = 0;
   out_5100092372859724848[91] = 0;
   out_5100092372859724848[92] = 0;
   out_5100092372859724848[93] = 0;
   out_5100092372859724848[94] = 0;
   out_5100092372859724848[95] = 1;
   out_5100092372859724848[96] = 0;
   out_5100092372859724848[97] = 0;
   out_5100092372859724848[98] = 0;
   out_5100092372859724848[99] = 0;
   out_5100092372859724848[100] = 0;
   out_5100092372859724848[101] = 0;
   out_5100092372859724848[102] = 0;
   out_5100092372859724848[103] = 0;
   out_5100092372859724848[104] = dt;
   out_5100092372859724848[105] = 0;
   out_5100092372859724848[106] = 0;
   out_5100092372859724848[107] = 0;
   out_5100092372859724848[108] = 0;
   out_5100092372859724848[109] = 0;
   out_5100092372859724848[110] = 0;
   out_5100092372859724848[111] = 0;
   out_5100092372859724848[112] = 0;
   out_5100092372859724848[113] = 0;
   out_5100092372859724848[114] = 1;
   out_5100092372859724848[115] = 0;
   out_5100092372859724848[116] = 0;
   out_5100092372859724848[117] = 0;
   out_5100092372859724848[118] = 0;
   out_5100092372859724848[119] = 0;
   out_5100092372859724848[120] = 0;
   out_5100092372859724848[121] = 0;
   out_5100092372859724848[122] = 0;
   out_5100092372859724848[123] = 0;
   out_5100092372859724848[124] = 0;
   out_5100092372859724848[125] = 0;
   out_5100092372859724848[126] = 0;
   out_5100092372859724848[127] = 0;
   out_5100092372859724848[128] = 0;
   out_5100092372859724848[129] = 0;
   out_5100092372859724848[130] = 0;
   out_5100092372859724848[131] = 0;
   out_5100092372859724848[132] = 0;
   out_5100092372859724848[133] = 1;
   out_5100092372859724848[134] = 0;
   out_5100092372859724848[135] = 0;
   out_5100092372859724848[136] = 0;
   out_5100092372859724848[137] = 0;
   out_5100092372859724848[138] = 0;
   out_5100092372859724848[139] = 0;
   out_5100092372859724848[140] = 0;
   out_5100092372859724848[141] = 0;
   out_5100092372859724848[142] = 0;
   out_5100092372859724848[143] = 0;
   out_5100092372859724848[144] = 0;
   out_5100092372859724848[145] = 0;
   out_5100092372859724848[146] = 0;
   out_5100092372859724848[147] = 0;
   out_5100092372859724848[148] = 0;
   out_5100092372859724848[149] = 0;
   out_5100092372859724848[150] = 0;
   out_5100092372859724848[151] = 0;
   out_5100092372859724848[152] = 1;
   out_5100092372859724848[153] = 0;
   out_5100092372859724848[154] = 0;
   out_5100092372859724848[155] = 0;
   out_5100092372859724848[156] = 0;
   out_5100092372859724848[157] = 0;
   out_5100092372859724848[158] = 0;
   out_5100092372859724848[159] = 0;
   out_5100092372859724848[160] = 0;
   out_5100092372859724848[161] = 0;
   out_5100092372859724848[162] = 0;
   out_5100092372859724848[163] = 0;
   out_5100092372859724848[164] = 0;
   out_5100092372859724848[165] = 0;
   out_5100092372859724848[166] = 0;
   out_5100092372859724848[167] = 0;
   out_5100092372859724848[168] = 0;
   out_5100092372859724848[169] = 0;
   out_5100092372859724848[170] = 0;
   out_5100092372859724848[171] = 1;
   out_5100092372859724848[172] = 0;
   out_5100092372859724848[173] = 0;
   out_5100092372859724848[174] = 0;
   out_5100092372859724848[175] = 0;
   out_5100092372859724848[176] = 0;
   out_5100092372859724848[177] = 0;
   out_5100092372859724848[178] = 0;
   out_5100092372859724848[179] = 0;
   out_5100092372859724848[180] = 0;
   out_5100092372859724848[181] = 0;
   out_5100092372859724848[182] = 0;
   out_5100092372859724848[183] = 0;
   out_5100092372859724848[184] = 0;
   out_5100092372859724848[185] = 0;
   out_5100092372859724848[186] = 0;
   out_5100092372859724848[187] = 0;
   out_5100092372859724848[188] = 0;
   out_5100092372859724848[189] = 0;
   out_5100092372859724848[190] = 1;
   out_5100092372859724848[191] = 0;
   out_5100092372859724848[192] = 0;
   out_5100092372859724848[193] = 0;
   out_5100092372859724848[194] = 0;
   out_5100092372859724848[195] = 0;
   out_5100092372859724848[196] = 0;
   out_5100092372859724848[197] = 0;
   out_5100092372859724848[198] = 0;
   out_5100092372859724848[199] = 0;
   out_5100092372859724848[200] = 0;
   out_5100092372859724848[201] = 0;
   out_5100092372859724848[202] = 0;
   out_5100092372859724848[203] = 0;
   out_5100092372859724848[204] = 0;
   out_5100092372859724848[205] = 0;
   out_5100092372859724848[206] = 0;
   out_5100092372859724848[207] = 0;
   out_5100092372859724848[208] = 0;
   out_5100092372859724848[209] = 1;
   out_5100092372859724848[210] = 0;
   out_5100092372859724848[211] = 0;
   out_5100092372859724848[212] = 0;
   out_5100092372859724848[213] = 0;
   out_5100092372859724848[214] = 0;
   out_5100092372859724848[215] = 0;
   out_5100092372859724848[216] = 0;
   out_5100092372859724848[217] = 0;
   out_5100092372859724848[218] = 0;
   out_5100092372859724848[219] = 0;
   out_5100092372859724848[220] = 0;
   out_5100092372859724848[221] = 0;
   out_5100092372859724848[222] = 0;
   out_5100092372859724848[223] = 0;
   out_5100092372859724848[224] = 0;
   out_5100092372859724848[225] = 0;
   out_5100092372859724848[226] = 0;
   out_5100092372859724848[227] = 0;
   out_5100092372859724848[228] = 1;
   out_5100092372859724848[229] = 0;
   out_5100092372859724848[230] = 0;
   out_5100092372859724848[231] = 0;
   out_5100092372859724848[232] = 0;
   out_5100092372859724848[233] = 0;
   out_5100092372859724848[234] = 0;
   out_5100092372859724848[235] = 0;
   out_5100092372859724848[236] = 0;
   out_5100092372859724848[237] = 0;
   out_5100092372859724848[238] = 0;
   out_5100092372859724848[239] = 0;
   out_5100092372859724848[240] = 0;
   out_5100092372859724848[241] = 0;
   out_5100092372859724848[242] = 0;
   out_5100092372859724848[243] = 0;
   out_5100092372859724848[244] = 0;
   out_5100092372859724848[245] = 0;
   out_5100092372859724848[246] = 0;
   out_5100092372859724848[247] = 1;
   out_5100092372859724848[248] = 0;
   out_5100092372859724848[249] = 0;
   out_5100092372859724848[250] = 0;
   out_5100092372859724848[251] = 0;
   out_5100092372859724848[252] = 0;
   out_5100092372859724848[253] = 0;
   out_5100092372859724848[254] = 0;
   out_5100092372859724848[255] = 0;
   out_5100092372859724848[256] = 0;
   out_5100092372859724848[257] = 0;
   out_5100092372859724848[258] = 0;
   out_5100092372859724848[259] = 0;
   out_5100092372859724848[260] = 0;
   out_5100092372859724848[261] = 0;
   out_5100092372859724848[262] = 0;
   out_5100092372859724848[263] = 0;
   out_5100092372859724848[264] = 0;
   out_5100092372859724848[265] = 0;
   out_5100092372859724848[266] = 1;
   out_5100092372859724848[267] = 0;
   out_5100092372859724848[268] = 0;
   out_5100092372859724848[269] = 0;
   out_5100092372859724848[270] = 0;
   out_5100092372859724848[271] = 0;
   out_5100092372859724848[272] = 0;
   out_5100092372859724848[273] = 0;
   out_5100092372859724848[274] = 0;
   out_5100092372859724848[275] = 0;
   out_5100092372859724848[276] = 0;
   out_5100092372859724848[277] = 0;
   out_5100092372859724848[278] = 0;
   out_5100092372859724848[279] = 0;
   out_5100092372859724848[280] = 0;
   out_5100092372859724848[281] = 0;
   out_5100092372859724848[282] = 0;
   out_5100092372859724848[283] = 0;
   out_5100092372859724848[284] = 0;
   out_5100092372859724848[285] = 1;
   out_5100092372859724848[286] = 0;
   out_5100092372859724848[287] = 0;
   out_5100092372859724848[288] = 0;
   out_5100092372859724848[289] = 0;
   out_5100092372859724848[290] = 0;
   out_5100092372859724848[291] = 0;
   out_5100092372859724848[292] = 0;
   out_5100092372859724848[293] = 0;
   out_5100092372859724848[294] = 0;
   out_5100092372859724848[295] = 0;
   out_5100092372859724848[296] = 0;
   out_5100092372859724848[297] = 0;
   out_5100092372859724848[298] = 0;
   out_5100092372859724848[299] = 0;
   out_5100092372859724848[300] = 0;
   out_5100092372859724848[301] = 0;
   out_5100092372859724848[302] = 0;
   out_5100092372859724848[303] = 0;
   out_5100092372859724848[304] = 1;
   out_5100092372859724848[305] = 0;
   out_5100092372859724848[306] = 0;
   out_5100092372859724848[307] = 0;
   out_5100092372859724848[308] = 0;
   out_5100092372859724848[309] = 0;
   out_5100092372859724848[310] = 0;
   out_5100092372859724848[311] = 0;
   out_5100092372859724848[312] = 0;
   out_5100092372859724848[313] = 0;
   out_5100092372859724848[314] = 0;
   out_5100092372859724848[315] = 0;
   out_5100092372859724848[316] = 0;
   out_5100092372859724848[317] = 0;
   out_5100092372859724848[318] = 0;
   out_5100092372859724848[319] = 0;
   out_5100092372859724848[320] = 0;
   out_5100092372859724848[321] = 0;
   out_5100092372859724848[322] = 0;
   out_5100092372859724848[323] = 1;
}
void h_4(double *state, double *unused, double *out_7074427651173269504) {
   out_7074427651173269504[0] = state[6] + state[9];
   out_7074427651173269504[1] = state[7] + state[10];
   out_7074427651173269504[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1236248867215554898) {
   out_1236248867215554898[0] = 0;
   out_1236248867215554898[1] = 0;
   out_1236248867215554898[2] = 0;
   out_1236248867215554898[3] = 0;
   out_1236248867215554898[4] = 0;
   out_1236248867215554898[5] = 0;
   out_1236248867215554898[6] = 1;
   out_1236248867215554898[7] = 0;
   out_1236248867215554898[8] = 0;
   out_1236248867215554898[9] = 1;
   out_1236248867215554898[10] = 0;
   out_1236248867215554898[11] = 0;
   out_1236248867215554898[12] = 0;
   out_1236248867215554898[13] = 0;
   out_1236248867215554898[14] = 0;
   out_1236248867215554898[15] = 0;
   out_1236248867215554898[16] = 0;
   out_1236248867215554898[17] = 0;
   out_1236248867215554898[18] = 0;
   out_1236248867215554898[19] = 0;
   out_1236248867215554898[20] = 0;
   out_1236248867215554898[21] = 0;
   out_1236248867215554898[22] = 0;
   out_1236248867215554898[23] = 0;
   out_1236248867215554898[24] = 0;
   out_1236248867215554898[25] = 1;
   out_1236248867215554898[26] = 0;
   out_1236248867215554898[27] = 0;
   out_1236248867215554898[28] = 1;
   out_1236248867215554898[29] = 0;
   out_1236248867215554898[30] = 0;
   out_1236248867215554898[31] = 0;
   out_1236248867215554898[32] = 0;
   out_1236248867215554898[33] = 0;
   out_1236248867215554898[34] = 0;
   out_1236248867215554898[35] = 0;
   out_1236248867215554898[36] = 0;
   out_1236248867215554898[37] = 0;
   out_1236248867215554898[38] = 0;
   out_1236248867215554898[39] = 0;
   out_1236248867215554898[40] = 0;
   out_1236248867215554898[41] = 0;
   out_1236248867215554898[42] = 0;
   out_1236248867215554898[43] = 0;
   out_1236248867215554898[44] = 1;
   out_1236248867215554898[45] = 0;
   out_1236248867215554898[46] = 0;
   out_1236248867215554898[47] = 1;
   out_1236248867215554898[48] = 0;
   out_1236248867215554898[49] = 0;
   out_1236248867215554898[50] = 0;
   out_1236248867215554898[51] = 0;
   out_1236248867215554898[52] = 0;
   out_1236248867215554898[53] = 0;
}
void h_10(double *state, double *unused, double *out_1452877130807937946) {
   out_1452877130807937946[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1452877130807937946[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1452877130807937946[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4992083827767139638) {
   out_4992083827767139638[0] = 0;
   out_4992083827767139638[1] = 9.8100000000000005*cos(state[1]);
   out_4992083827767139638[2] = 0;
   out_4992083827767139638[3] = 0;
   out_4992083827767139638[4] = -state[8];
   out_4992083827767139638[5] = state[7];
   out_4992083827767139638[6] = 0;
   out_4992083827767139638[7] = state[5];
   out_4992083827767139638[8] = -state[4];
   out_4992083827767139638[9] = 0;
   out_4992083827767139638[10] = 0;
   out_4992083827767139638[11] = 0;
   out_4992083827767139638[12] = 1;
   out_4992083827767139638[13] = 0;
   out_4992083827767139638[14] = 0;
   out_4992083827767139638[15] = 1;
   out_4992083827767139638[16] = 0;
   out_4992083827767139638[17] = 0;
   out_4992083827767139638[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4992083827767139638[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4992083827767139638[20] = 0;
   out_4992083827767139638[21] = state[8];
   out_4992083827767139638[22] = 0;
   out_4992083827767139638[23] = -state[6];
   out_4992083827767139638[24] = -state[5];
   out_4992083827767139638[25] = 0;
   out_4992083827767139638[26] = state[3];
   out_4992083827767139638[27] = 0;
   out_4992083827767139638[28] = 0;
   out_4992083827767139638[29] = 0;
   out_4992083827767139638[30] = 0;
   out_4992083827767139638[31] = 1;
   out_4992083827767139638[32] = 0;
   out_4992083827767139638[33] = 0;
   out_4992083827767139638[34] = 1;
   out_4992083827767139638[35] = 0;
   out_4992083827767139638[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4992083827767139638[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4992083827767139638[38] = 0;
   out_4992083827767139638[39] = -state[7];
   out_4992083827767139638[40] = state[6];
   out_4992083827767139638[41] = 0;
   out_4992083827767139638[42] = state[4];
   out_4992083827767139638[43] = -state[3];
   out_4992083827767139638[44] = 0;
   out_4992083827767139638[45] = 0;
   out_4992083827767139638[46] = 0;
   out_4992083827767139638[47] = 0;
   out_4992083827767139638[48] = 0;
   out_4992083827767139638[49] = 0;
   out_4992083827767139638[50] = 1;
   out_4992083827767139638[51] = 0;
   out_4992083827767139638[52] = 0;
   out_4992083827767139638[53] = 1;
}
void h_13(double *state, double *unused, double *out_7690389037451804524) {
   out_7690389037451804524[0] = state[3];
   out_7690389037451804524[1] = state[4];
   out_7690389037451804524[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1976024958116777903) {
   out_1976024958116777903[0] = 0;
   out_1976024958116777903[1] = 0;
   out_1976024958116777903[2] = 0;
   out_1976024958116777903[3] = 1;
   out_1976024958116777903[4] = 0;
   out_1976024958116777903[5] = 0;
   out_1976024958116777903[6] = 0;
   out_1976024958116777903[7] = 0;
   out_1976024958116777903[8] = 0;
   out_1976024958116777903[9] = 0;
   out_1976024958116777903[10] = 0;
   out_1976024958116777903[11] = 0;
   out_1976024958116777903[12] = 0;
   out_1976024958116777903[13] = 0;
   out_1976024958116777903[14] = 0;
   out_1976024958116777903[15] = 0;
   out_1976024958116777903[16] = 0;
   out_1976024958116777903[17] = 0;
   out_1976024958116777903[18] = 0;
   out_1976024958116777903[19] = 0;
   out_1976024958116777903[20] = 0;
   out_1976024958116777903[21] = 0;
   out_1976024958116777903[22] = 1;
   out_1976024958116777903[23] = 0;
   out_1976024958116777903[24] = 0;
   out_1976024958116777903[25] = 0;
   out_1976024958116777903[26] = 0;
   out_1976024958116777903[27] = 0;
   out_1976024958116777903[28] = 0;
   out_1976024958116777903[29] = 0;
   out_1976024958116777903[30] = 0;
   out_1976024958116777903[31] = 0;
   out_1976024958116777903[32] = 0;
   out_1976024958116777903[33] = 0;
   out_1976024958116777903[34] = 0;
   out_1976024958116777903[35] = 0;
   out_1976024958116777903[36] = 0;
   out_1976024958116777903[37] = 0;
   out_1976024958116777903[38] = 0;
   out_1976024958116777903[39] = 0;
   out_1976024958116777903[40] = 0;
   out_1976024958116777903[41] = 1;
   out_1976024958116777903[42] = 0;
   out_1976024958116777903[43] = 0;
   out_1976024958116777903[44] = 0;
   out_1976024958116777903[45] = 0;
   out_1976024958116777903[46] = 0;
   out_1976024958116777903[47] = 0;
   out_1976024958116777903[48] = 0;
   out_1976024958116777903[49] = 0;
   out_1976024958116777903[50] = 0;
   out_1976024958116777903[51] = 0;
   out_1976024958116777903[52] = 0;
   out_1976024958116777903[53] = 0;
}
void h_14(double *state, double *unused, double *out_9127280363092827270) {
   out_9127280363092827270[0] = state[6];
   out_9127280363092827270[1] = state[7];
   out_9127280363092827270[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4319037299510927194) {
   out_4319037299510927194[0] = 0;
   out_4319037299510927194[1] = 0;
   out_4319037299510927194[2] = 0;
   out_4319037299510927194[3] = 0;
   out_4319037299510927194[4] = 0;
   out_4319037299510927194[5] = 0;
   out_4319037299510927194[6] = 1;
   out_4319037299510927194[7] = 0;
   out_4319037299510927194[8] = 0;
   out_4319037299510927194[9] = 0;
   out_4319037299510927194[10] = 0;
   out_4319037299510927194[11] = 0;
   out_4319037299510927194[12] = 0;
   out_4319037299510927194[13] = 0;
   out_4319037299510927194[14] = 0;
   out_4319037299510927194[15] = 0;
   out_4319037299510927194[16] = 0;
   out_4319037299510927194[17] = 0;
   out_4319037299510927194[18] = 0;
   out_4319037299510927194[19] = 0;
   out_4319037299510927194[20] = 0;
   out_4319037299510927194[21] = 0;
   out_4319037299510927194[22] = 0;
   out_4319037299510927194[23] = 0;
   out_4319037299510927194[24] = 0;
   out_4319037299510927194[25] = 1;
   out_4319037299510927194[26] = 0;
   out_4319037299510927194[27] = 0;
   out_4319037299510927194[28] = 0;
   out_4319037299510927194[29] = 0;
   out_4319037299510927194[30] = 0;
   out_4319037299510927194[31] = 0;
   out_4319037299510927194[32] = 0;
   out_4319037299510927194[33] = 0;
   out_4319037299510927194[34] = 0;
   out_4319037299510927194[35] = 0;
   out_4319037299510927194[36] = 0;
   out_4319037299510927194[37] = 0;
   out_4319037299510927194[38] = 0;
   out_4319037299510927194[39] = 0;
   out_4319037299510927194[40] = 0;
   out_4319037299510927194[41] = 0;
   out_4319037299510927194[42] = 0;
   out_4319037299510927194[43] = 0;
   out_4319037299510927194[44] = 1;
   out_4319037299510927194[45] = 0;
   out_4319037299510927194[46] = 0;
   out_4319037299510927194[47] = 0;
   out_4319037299510927194[48] = 0;
   out_4319037299510927194[49] = 0;
   out_4319037299510927194[50] = 0;
   out_4319037299510927194[51] = 0;
   out_4319037299510927194[52] = 0;
   out_4319037299510927194[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7076630439446261590) {
  err_fun(nom_x, delta_x, out_7076630439446261590);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2828328233536285037) {
  inv_err_fun(nom_x, true_x, out_2828328233536285037);
}
void pose_H_mod_fun(double *state, double *out_180736316877999173) {
  H_mod_fun(state, out_180736316877999173);
}
void pose_f_fun(double *state, double dt, double *out_3533683092462162875) {
  f_fun(state,  dt, out_3533683092462162875);
}
void pose_F_fun(double *state, double dt, double *out_5100092372859724848) {
  F_fun(state,  dt, out_5100092372859724848);
}
void pose_h_4(double *state, double *unused, double *out_7074427651173269504) {
  h_4(state, unused, out_7074427651173269504);
}
void pose_H_4(double *state, double *unused, double *out_1236248867215554898) {
  H_4(state, unused, out_1236248867215554898);
}
void pose_h_10(double *state, double *unused, double *out_1452877130807937946) {
  h_10(state, unused, out_1452877130807937946);
}
void pose_H_10(double *state, double *unused, double *out_4992083827767139638) {
  H_10(state, unused, out_4992083827767139638);
}
void pose_h_13(double *state, double *unused, double *out_7690389037451804524) {
  h_13(state, unused, out_7690389037451804524);
}
void pose_H_13(double *state, double *unused, double *out_1976024958116777903) {
  H_13(state, unused, out_1976024958116777903);
}
void pose_h_14(double *state, double *unused, double *out_9127280363092827270) {
  h_14(state, unused, out_9127280363092827270);
}
void pose_H_14(double *state, double *unused, double *out_4319037299510927194) {
  H_14(state, unused, out_4319037299510927194);
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
