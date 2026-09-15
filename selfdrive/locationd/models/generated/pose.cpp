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
void err_fun(double *nom_x, double *delta_x, double *out_4724133448419912693) {
   out_4724133448419912693[0] = delta_x[0] + nom_x[0];
   out_4724133448419912693[1] = delta_x[1] + nom_x[1];
   out_4724133448419912693[2] = delta_x[2] + nom_x[2];
   out_4724133448419912693[3] = delta_x[3] + nom_x[3];
   out_4724133448419912693[4] = delta_x[4] + nom_x[4];
   out_4724133448419912693[5] = delta_x[5] + nom_x[5];
   out_4724133448419912693[6] = delta_x[6] + nom_x[6];
   out_4724133448419912693[7] = delta_x[7] + nom_x[7];
   out_4724133448419912693[8] = delta_x[8] + nom_x[8];
   out_4724133448419912693[9] = delta_x[9] + nom_x[9];
   out_4724133448419912693[10] = delta_x[10] + nom_x[10];
   out_4724133448419912693[11] = delta_x[11] + nom_x[11];
   out_4724133448419912693[12] = delta_x[12] + nom_x[12];
   out_4724133448419912693[13] = delta_x[13] + nom_x[13];
   out_4724133448419912693[14] = delta_x[14] + nom_x[14];
   out_4724133448419912693[15] = delta_x[15] + nom_x[15];
   out_4724133448419912693[16] = delta_x[16] + nom_x[16];
   out_4724133448419912693[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6531814374965429464) {
   out_6531814374965429464[0] = -nom_x[0] + true_x[0];
   out_6531814374965429464[1] = -nom_x[1] + true_x[1];
   out_6531814374965429464[2] = -nom_x[2] + true_x[2];
   out_6531814374965429464[3] = -nom_x[3] + true_x[3];
   out_6531814374965429464[4] = -nom_x[4] + true_x[4];
   out_6531814374965429464[5] = -nom_x[5] + true_x[5];
   out_6531814374965429464[6] = -nom_x[6] + true_x[6];
   out_6531814374965429464[7] = -nom_x[7] + true_x[7];
   out_6531814374965429464[8] = -nom_x[8] + true_x[8];
   out_6531814374965429464[9] = -nom_x[9] + true_x[9];
   out_6531814374965429464[10] = -nom_x[10] + true_x[10];
   out_6531814374965429464[11] = -nom_x[11] + true_x[11];
   out_6531814374965429464[12] = -nom_x[12] + true_x[12];
   out_6531814374965429464[13] = -nom_x[13] + true_x[13];
   out_6531814374965429464[14] = -nom_x[14] + true_x[14];
   out_6531814374965429464[15] = -nom_x[15] + true_x[15];
   out_6531814374965429464[16] = -nom_x[16] + true_x[16];
   out_6531814374965429464[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4336476144052946499) {
   out_4336476144052946499[0] = 1.0;
   out_4336476144052946499[1] = 0.0;
   out_4336476144052946499[2] = 0.0;
   out_4336476144052946499[3] = 0.0;
   out_4336476144052946499[4] = 0.0;
   out_4336476144052946499[5] = 0.0;
   out_4336476144052946499[6] = 0.0;
   out_4336476144052946499[7] = 0.0;
   out_4336476144052946499[8] = 0.0;
   out_4336476144052946499[9] = 0.0;
   out_4336476144052946499[10] = 0.0;
   out_4336476144052946499[11] = 0.0;
   out_4336476144052946499[12] = 0.0;
   out_4336476144052946499[13] = 0.0;
   out_4336476144052946499[14] = 0.0;
   out_4336476144052946499[15] = 0.0;
   out_4336476144052946499[16] = 0.0;
   out_4336476144052946499[17] = 0.0;
   out_4336476144052946499[18] = 0.0;
   out_4336476144052946499[19] = 1.0;
   out_4336476144052946499[20] = 0.0;
   out_4336476144052946499[21] = 0.0;
   out_4336476144052946499[22] = 0.0;
   out_4336476144052946499[23] = 0.0;
   out_4336476144052946499[24] = 0.0;
   out_4336476144052946499[25] = 0.0;
   out_4336476144052946499[26] = 0.0;
   out_4336476144052946499[27] = 0.0;
   out_4336476144052946499[28] = 0.0;
   out_4336476144052946499[29] = 0.0;
   out_4336476144052946499[30] = 0.0;
   out_4336476144052946499[31] = 0.0;
   out_4336476144052946499[32] = 0.0;
   out_4336476144052946499[33] = 0.0;
   out_4336476144052946499[34] = 0.0;
   out_4336476144052946499[35] = 0.0;
   out_4336476144052946499[36] = 0.0;
   out_4336476144052946499[37] = 0.0;
   out_4336476144052946499[38] = 1.0;
   out_4336476144052946499[39] = 0.0;
   out_4336476144052946499[40] = 0.0;
   out_4336476144052946499[41] = 0.0;
   out_4336476144052946499[42] = 0.0;
   out_4336476144052946499[43] = 0.0;
   out_4336476144052946499[44] = 0.0;
   out_4336476144052946499[45] = 0.0;
   out_4336476144052946499[46] = 0.0;
   out_4336476144052946499[47] = 0.0;
   out_4336476144052946499[48] = 0.0;
   out_4336476144052946499[49] = 0.0;
   out_4336476144052946499[50] = 0.0;
   out_4336476144052946499[51] = 0.0;
   out_4336476144052946499[52] = 0.0;
   out_4336476144052946499[53] = 0.0;
   out_4336476144052946499[54] = 0.0;
   out_4336476144052946499[55] = 0.0;
   out_4336476144052946499[56] = 0.0;
   out_4336476144052946499[57] = 1.0;
   out_4336476144052946499[58] = 0.0;
   out_4336476144052946499[59] = 0.0;
   out_4336476144052946499[60] = 0.0;
   out_4336476144052946499[61] = 0.0;
   out_4336476144052946499[62] = 0.0;
   out_4336476144052946499[63] = 0.0;
   out_4336476144052946499[64] = 0.0;
   out_4336476144052946499[65] = 0.0;
   out_4336476144052946499[66] = 0.0;
   out_4336476144052946499[67] = 0.0;
   out_4336476144052946499[68] = 0.0;
   out_4336476144052946499[69] = 0.0;
   out_4336476144052946499[70] = 0.0;
   out_4336476144052946499[71] = 0.0;
   out_4336476144052946499[72] = 0.0;
   out_4336476144052946499[73] = 0.0;
   out_4336476144052946499[74] = 0.0;
   out_4336476144052946499[75] = 0.0;
   out_4336476144052946499[76] = 1.0;
   out_4336476144052946499[77] = 0.0;
   out_4336476144052946499[78] = 0.0;
   out_4336476144052946499[79] = 0.0;
   out_4336476144052946499[80] = 0.0;
   out_4336476144052946499[81] = 0.0;
   out_4336476144052946499[82] = 0.0;
   out_4336476144052946499[83] = 0.0;
   out_4336476144052946499[84] = 0.0;
   out_4336476144052946499[85] = 0.0;
   out_4336476144052946499[86] = 0.0;
   out_4336476144052946499[87] = 0.0;
   out_4336476144052946499[88] = 0.0;
   out_4336476144052946499[89] = 0.0;
   out_4336476144052946499[90] = 0.0;
   out_4336476144052946499[91] = 0.0;
   out_4336476144052946499[92] = 0.0;
   out_4336476144052946499[93] = 0.0;
   out_4336476144052946499[94] = 0.0;
   out_4336476144052946499[95] = 1.0;
   out_4336476144052946499[96] = 0.0;
   out_4336476144052946499[97] = 0.0;
   out_4336476144052946499[98] = 0.0;
   out_4336476144052946499[99] = 0.0;
   out_4336476144052946499[100] = 0.0;
   out_4336476144052946499[101] = 0.0;
   out_4336476144052946499[102] = 0.0;
   out_4336476144052946499[103] = 0.0;
   out_4336476144052946499[104] = 0.0;
   out_4336476144052946499[105] = 0.0;
   out_4336476144052946499[106] = 0.0;
   out_4336476144052946499[107] = 0.0;
   out_4336476144052946499[108] = 0.0;
   out_4336476144052946499[109] = 0.0;
   out_4336476144052946499[110] = 0.0;
   out_4336476144052946499[111] = 0.0;
   out_4336476144052946499[112] = 0.0;
   out_4336476144052946499[113] = 0.0;
   out_4336476144052946499[114] = 1.0;
   out_4336476144052946499[115] = 0.0;
   out_4336476144052946499[116] = 0.0;
   out_4336476144052946499[117] = 0.0;
   out_4336476144052946499[118] = 0.0;
   out_4336476144052946499[119] = 0.0;
   out_4336476144052946499[120] = 0.0;
   out_4336476144052946499[121] = 0.0;
   out_4336476144052946499[122] = 0.0;
   out_4336476144052946499[123] = 0.0;
   out_4336476144052946499[124] = 0.0;
   out_4336476144052946499[125] = 0.0;
   out_4336476144052946499[126] = 0.0;
   out_4336476144052946499[127] = 0.0;
   out_4336476144052946499[128] = 0.0;
   out_4336476144052946499[129] = 0.0;
   out_4336476144052946499[130] = 0.0;
   out_4336476144052946499[131] = 0.0;
   out_4336476144052946499[132] = 0.0;
   out_4336476144052946499[133] = 1.0;
   out_4336476144052946499[134] = 0.0;
   out_4336476144052946499[135] = 0.0;
   out_4336476144052946499[136] = 0.0;
   out_4336476144052946499[137] = 0.0;
   out_4336476144052946499[138] = 0.0;
   out_4336476144052946499[139] = 0.0;
   out_4336476144052946499[140] = 0.0;
   out_4336476144052946499[141] = 0.0;
   out_4336476144052946499[142] = 0.0;
   out_4336476144052946499[143] = 0.0;
   out_4336476144052946499[144] = 0.0;
   out_4336476144052946499[145] = 0.0;
   out_4336476144052946499[146] = 0.0;
   out_4336476144052946499[147] = 0.0;
   out_4336476144052946499[148] = 0.0;
   out_4336476144052946499[149] = 0.0;
   out_4336476144052946499[150] = 0.0;
   out_4336476144052946499[151] = 0.0;
   out_4336476144052946499[152] = 1.0;
   out_4336476144052946499[153] = 0.0;
   out_4336476144052946499[154] = 0.0;
   out_4336476144052946499[155] = 0.0;
   out_4336476144052946499[156] = 0.0;
   out_4336476144052946499[157] = 0.0;
   out_4336476144052946499[158] = 0.0;
   out_4336476144052946499[159] = 0.0;
   out_4336476144052946499[160] = 0.0;
   out_4336476144052946499[161] = 0.0;
   out_4336476144052946499[162] = 0.0;
   out_4336476144052946499[163] = 0.0;
   out_4336476144052946499[164] = 0.0;
   out_4336476144052946499[165] = 0.0;
   out_4336476144052946499[166] = 0.0;
   out_4336476144052946499[167] = 0.0;
   out_4336476144052946499[168] = 0.0;
   out_4336476144052946499[169] = 0.0;
   out_4336476144052946499[170] = 0.0;
   out_4336476144052946499[171] = 1.0;
   out_4336476144052946499[172] = 0.0;
   out_4336476144052946499[173] = 0.0;
   out_4336476144052946499[174] = 0.0;
   out_4336476144052946499[175] = 0.0;
   out_4336476144052946499[176] = 0.0;
   out_4336476144052946499[177] = 0.0;
   out_4336476144052946499[178] = 0.0;
   out_4336476144052946499[179] = 0.0;
   out_4336476144052946499[180] = 0.0;
   out_4336476144052946499[181] = 0.0;
   out_4336476144052946499[182] = 0.0;
   out_4336476144052946499[183] = 0.0;
   out_4336476144052946499[184] = 0.0;
   out_4336476144052946499[185] = 0.0;
   out_4336476144052946499[186] = 0.0;
   out_4336476144052946499[187] = 0.0;
   out_4336476144052946499[188] = 0.0;
   out_4336476144052946499[189] = 0.0;
   out_4336476144052946499[190] = 1.0;
   out_4336476144052946499[191] = 0.0;
   out_4336476144052946499[192] = 0.0;
   out_4336476144052946499[193] = 0.0;
   out_4336476144052946499[194] = 0.0;
   out_4336476144052946499[195] = 0.0;
   out_4336476144052946499[196] = 0.0;
   out_4336476144052946499[197] = 0.0;
   out_4336476144052946499[198] = 0.0;
   out_4336476144052946499[199] = 0.0;
   out_4336476144052946499[200] = 0.0;
   out_4336476144052946499[201] = 0.0;
   out_4336476144052946499[202] = 0.0;
   out_4336476144052946499[203] = 0.0;
   out_4336476144052946499[204] = 0.0;
   out_4336476144052946499[205] = 0.0;
   out_4336476144052946499[206] = 0.0;
   out_4336476144052946499[207] = 0.0;
   out_4336476144052946499[208] = 0.0;
   out_4336476144052946499[209] = 1.0;
   out_4336476144052946499[210] = 0.0;
   out_4336476144052946499[211] = 0.0;
   out_4336476144052946499[212] = 0.0;
   out_4336476144052946499[213] = 0.0;
   out_4336476144052946499[214] = 0.0;
   out_4336476144052946499[215] = 0.0;
   out_4336476144052946499[216] = 0.0;
   out_4336476144052946499[217] = 0.0;
   out_4336476144052946499[218] = 0.0;
   out_4336476144052946499[219] = 0.0;
   out_4336476144052946499[220] = 0.0;
   out_4336476144052946499[221] = 0.0;
   out_4336476144052946499[222] = 0.0;
   out_4336476144052946499[223] = 0.0;
   out_4336476144052946499[224] = 0.0;
   out_4336476144052946499[225] = 0.0;
   out_4336476144052946499[226] = 0.0;
   out_4336476144052946499[227] = 0.0;
   out_4336476144052946499[228] = 1.0;
   out_4336476144052946499[229] = 0.0;
   out_4336476144052946499[230] = 0.0;
   out_4336476144052946499[231] = 0.0;
   out_4336476144052946499[232] = 0.0;
   out_4336476144052946499[233] = 0.0;
   out_4336476144052946499[234] = 0.0;
   out_4336476144052946499[235] = 0.0;
   out_4336476144052946499[236] = 0.0;
   out_4336476144052946499[237] = 0.0;
   out_4336476144052946499[238] = 0.0;
   out_4336476144052946499[239] = 0.0;
   out_4336476144052946499[240] = 0.0;
   out_4336476144052946499[241] = 0.0;
   out_4336476144052946499[242] = 0.0;
   out_4336476144052946499[243] = 0.0;
   out_4336476144052946499[244] = 0.0;
   out_4336476144052946499[245] = 0.0;
   out_4336476144052946499[246] = 0.0;
   out_4336476144052946499[247] = 1.0;
   out_4336476144052946499[248] = 0.0;
   out_4336476144052946499[249] = 0.0;
   out_4336476144052946499[250] = 0.0;
   out_4336476144052946499[251] = 0.0;
   out_4336476144052946499[252] = 0.0;
   out_4336476144052946499[253] = 0.0;
   out_4336476144052946499[254] = 0.0;
   out_4336476144052946499[255] = 0.0;
   out_4336476144052946499[256] = 0.0;
   out_4336476144052946499[257] = 0.0;
   out_4336476144052946499[258] = 0.0;
   out_4336476144052946499[259] = 0.0;
   out_4336476144052946499[260] = 0.0;
   out_4336476144052946499[261] = 0.0;
   out_4336476144052946499[262] = 0.0;
   out_4336476144052946499[263] = 0.0;
   out_4336476144052946499[264] = 0.0;
   out_4336476144052946499[265] = 0.0;
   out_4336476144052946499[266] = 1.0;
   out_4336476144052946499[267] = 0.0;
   out_4336476144052946499[268] = 0.0;
   out_4336476144052946499[269] = 0.0;
   out_4336476144052946499[270] = 0.0;
   out_4336476144052946499[271] = 0.0;
   out_4336476144052946499[272] = 0.0;
   out_4336476144052946499[273] = 0.0;
   out_4336476144052946499[274] = 0.0;
   out_4336476144052946499[275] = 0.0;
   out_4336476144052946499[276] = 0.0;
   out_4336476144052946499[277] = 0.0;
   out_4336476144052946499[278] = 0.0;
   out_4336476144052946499[279] = 0.0;
   out_4336476144052946499[280] = 0.0;
   out_4336476144052946499[281] = 0.0;
   out_4336476144052946499[282] = 0.0;
   out_4336476144052946499[283] = 0.0;
   out_4336476144052946499[284] = 0.0;
   out_4336476144052946499[285] = 1.0;
   out_4336476144052946499[286] = 0.0;
   out_4336476144052946499[287] = 0.0;
   out_4336476144052946499[288] = 0.0;
   out_4336476144052946499[289] = 0.0;
   out_4336476144052946499[290] = 0.0;
   out_4336476144052946499[291] = 0.0;
   out_4336476144052946499[292] = 0.0;
   out_4336476144052946499[293] = 0.0;
   out_4336476144052946499[294] = 0.0;
   out_4336476144052946499[295] = 0.0;
   out_4336476144052946499[296] = 0.0;
   out_4336476144052946499[297] = 0.0;
   out_4336476144052946499[298] = 0.0;
   out_4336476144052946499[299] = 0.0;
   out_4336476144052946499[300] = 0.0;
   out_4336476144052946499[301] = 0.0;
   out_4336476144052946499[302] = 0.0;
   out_4336476144052946499[303] = 0.0;
   out_4336476144052946499[304] = 1.0;
   out_4336476144052946499[305] = 0.0;
   out_4336476144052946499[306] = 0.0;
   out_4336476144052946499[307] = 0.0;
   out_4336476144052946499[308] = 0.0;
   out_4336476144052946499[309] = 0.0;
   out_4336476144052946499[310] = 0.0;
   out_4336476144052946499[311] = 0.0;
   out_4336476144052946499[312] = 0.0;
   out_4336476144052946499[313] = 0.0;
   out_4336476144052946499[314] = 0.0;
   out_4336476144052946499[315] = 0.0;
   out_4336476144052946499[316] = 0.0;
   out_4336476144052946499[317] = 0.0;
   out_4336476144052946499[318] = 0.0;
   out_4336476144052946499[319] = 0.0;
   out_4336476144052946499[320] = 0.0;
   out_4336476144052946499[321] = 0.0;
   out_4336476144052946499[322] = 0.0;
   out_4336476144052946499[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5802866657257443587) {
   out_5802866657257443587[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5802866657257443587[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5802866657257443587[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5802866657257443587[3] = dt*state[12] + state[3];
   out_5802866657257443587[4] = dt*state[13] + state[4];
   out_5802866657257443587[5] = dt*state[14] + state[5];
   out_5802866657257443587[6] = state[6];
   out_5802866657257443587[7] = state[7];
   out_5802866657257443587[8] = state[8];
   out_5802866657257443587[9] = state[9];
   out_5802866657257443587[10] = state[10];
   out_5802866657257443587[11] = state[11];
   out_5802866657257443587[12] = state[12];
   out_5802866657257443587[13] = state[13];
   out_5802866657257443587[14] = state[14];
   out_5802866657257443587[15] = state[15];
   out_5802866657257443587[16] = state[16];
   out_5802866657257443587[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4553776162496472303) {
   out_4553776162496472303[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4553776162496472303[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4553776162496472303[2] = 0;
   out_4553776162496472303[3] = 0;
   out_4553776162496472303[4] = 0;
   out_4553776162496472303[5] = 0;
   out_4553776162496472303[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4553776162496472303[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4553776162496472303[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4553776162496472303[9] = 0;
   out_4553776162496472303[10] = 0;
   out_4553776162496472303[11] = 0;
   out_4553776162496472303[12] = 0;
   out_4553776162496472303[13] = 0;
   out_4553776162496472303[14] = 0;
   out_4553776162496472303[15] = 0;
   out_4553776162496472303[16] = 0;
   out_4553776162496472303[17] = 0;
   out_4553776162496472303[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4553776162496472303[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4553776162496472303[20] = 0;
   out_4553776162496472303[21] = 0;
   out_4553776162496472303[22] = 0;
   out_4553776162496472303[23] = 0;
   out_4553776162496472303[24] = 0;
   out_4553776162496472303[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4553776162496472303[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4553776162496472303[27] = 0;
   out_4553776162496472303[28] = 0;
   out_4553776162496472303[29] = 0;
   out_4553776162496472303[30] = 0;
   out_4553776162496472303[31] = 0;
   out_4553776162496472303[32] = 0;
   out_4553776162496472303[33] = 0;
   out_4553776162496472303[34] = 0;
   out_4553776162496472303[35] = 0;
   out_4553776162496472303[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4553776162496472303[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4553776162496472303[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4553776162496472303[39] = 0;
   out_4553776162496472303[40] = 0;
   out_4553776162496472303[41] = 0;
   out_4553776162496472303[42] = 0;
   out_4553776162496472303[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4553776162496472303[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4553776162496472303[45] = 0;
   out_4553776162496472303[46] = 0;
   out_4553776162496472303[47] = 0;
   out_4553776162496472303[48] = 0;
   out_4553776162496472303[49] = 0;
   out_4553776162496472303[50] = 0;
   out_4553776162496472303[51] = 0;
   out_4553776162496472303[52] = 0;
   out_4553776162496472303[53] = 0;
   out_4553776162496472303[54] = 0;
   out_4553776162496472303[55] = 0;
   out_4553776162496472303[56] = 0;
   out_4553776162496472303[57] = 1;
   out_4553776162496472303[58] = 0;
   out_4553776162496472303[59] = 0;
   out_4553776162496472303[60] = 0;
   out_4553776162496472303[61] = 0;
   out_4553776162496472303[62] = 0;
   out_4553776162496472303[63] = 0;
   out_4553776162496472303[64] = 0;
   out_4553776162496472303[65] = 0;
   out_4553776162496472303[66] = dt;
   out_4553776162496472303[67] = 0;
   out_4553776162496472303[68] = 0;
   out_4553776162496472303[69] = 0;
   out_4553776162496472303[70] = 0;
   out_4553776162496472303[71] = 0;
   out_4553776162496472303[72] = 0;
   out_4553776162496472303[73] = 0;
   out_4553776162496472303[74] = 0;
   out_4553776162496472303[75] = 0;
   out_4553776162496472303[76] = 1;
   out_4553776162496472303[77] = 0;
   out_4553776162496472303[78] = 0;
   out_4553776162496472303[79] = 0;
   out_4553776162496472303[80] = 0;
   out_4553776162496472303[81] = 0;
   out_4553776162496472303[82] = 0;
   out_4553776162496472303[83] = 0;
   out_4553776162496472303[84] = 0;
   out_4553776162496472303[85] = dt;
   out_4553776162496472303[86] = 0;
   out_4553776162496472303[87] = 0;
   out_4553776162496472303[88] = 0;
   out_4553776162496472303[89] = 0;
   out_4553776162496472303[90] = 0;
   out_4553776162496472303[91] = 0;
   out_4553776162496472303[92] = 0;
   out_4553776162496472303[93] = 0;
   out_4553776162496472303[94] = 0;
   out_4553776162496472303[95] = 1;
   out_4553776162496472303[96] = 0;
   out_4553776162496472303[97] = 0;
   out_4553776162496472303[98] = 0;
   out_4553776162496472303[99] = 0;
   out_4553776162496472303[100] = 0;
   out_4553776162496472303[101] = 0;
   out_4553776162496472303[102] = 0;
   out_4553776162496472303[103] = 0;
   out_4553776162496472303[104] = dt;
   out_4553776162496472303[105] = 0;
   out_4553776162496472303[106] = 0;
   out_4553776162496472303[107] = 0;
   out_4553776162496472303[108] = 0;
   out_4553776162496472303[109] = 0;
   out_4553776162496472303[110] = 0;
   out_4553776162496472303[111] = 0;
   out_4553776162496472303[112] = 0;
   out_4553776162496472303[113] = 0;
   out_4553776162496472303[114] = 1;
   out_4553776162496472303[115] = 0;
   out_4553776162496472303[116] = 0;
   out_4553776162496472303[117] = 0;
   out_4553776162496472303[118] = 0;
   out_4553776162496472303[119] = 0;
   out_4553776162496472303[120] = 0;
   out_4553776162496472303[121] = 0;
   out_4553776162496472303[122] = 0;
   out_4553776162496472303[123] = 0;
   out_4553776162496472303[124] = 0;
   out_4553776162496472303[125] = 0;
   out_4553776162496472303[126] = 0;
   out_4553776162496472303[127] = 0;
   out_4553776162496472303[128] = 0;
   out_4553776162496472303[129] = 0;
   out_4553776162496472303[130] = 0;
   out_4553776162496472303[131] = 0;
   out_4553776162496472303[132] = 0;
   out_4553776162496472303[133] = 1;
   out_4553776162496472303[134] = 0;
   out_4553776162496472303[135] = 0;
   out_4553776162496472303[136] = 0;
   out_4553776162496472303[137] = 0;
   out_4553776162496472303[138] = 0;
   out_4553776162496472303[139] = 0;
   out_4553776162496472303[140] = 0;
   out_4553776162496472303[141] = 0;
   out_4553776162496472303[142] = 0;
   out_4553776162496472303[143] = 0;
   out_4553776162496472303[144] = 0;
   out_4553776162496472303[145] = 0;
   out_4553776162496472303[146] = 0;
   out_4553776162496472303[147] = 0;
   out_4553776162496472303[148] = 0;
   out_4553776162496472303[149] = 0;
   out_4553776162496472303[150] = 0;
   out_4553776162496472303[151] = 0;
   out_4553776162496472303[152] = 1;
   out_4553776162496472303[153] = 0;
   out_4553776162496472303[154] = 0;
   out_4553776162496472303[155] = 0;
   out_4553776162496472303[156] = 0;
   out_4553776162496472303[157] = 0;
   out_4553776162496472303[158] = 0;
   out_4553776162496472303[159] = 0;
   out_4553776162496472303[160] = 0;
   out_4553776162496472303[161] = 0;
   out_4553776162496472303[162] = 0;
   out_4553776162496472303[163] = 0;
   out_4553776162496472303[164] = 0;
   out_4553776162496472303[165] = 0;
   out_4553776162496472303[166] = 0;
   out_4553776162496472303[167] = 0;
   out_4553776162496472303[168] = 0;
   out_4553776162496472303[169] = 0;
   out_4553776162496472303[170] = 0;
   out_4553776162496472303[171] = 1;
   out_4553776162496472303[172] = 0;
   out_4553776162496472303[173] = 0;
   out_4553776162496472303[174] = 0;
   out_4553776162496472303[175] = 0;
   out_4553776162496472303[176] = 0;
   out_4553776162496472303[177] = 0;
   out_4553776162496472303[178] = 0;
   out_4553776162496472303[179] = 0;
   out_4553776162496472303[180] = 0;
   out_4553776162496472303[181] = 0;
   out_4553776162496472303[182] = 0;
   out_4553776162496472303[183] = 0;
   out_4553776162496472303[184] = 0;
   out_4553776162496472303[185] = 0;
   out_4553776162496472303[186] = 0;
   out_4553776162496472303[187] = 0;
   out_4553776162496472303[188] = 0;
   out_4553776162496472303[189] = 0;
   out_4553776162496472303[190] = 1;
   out_4553776162496472303[191] = 0;
   out_4553776162496472303[192] = 0;
   out_4553776162496472303[193] = 0;
   out_4553776162496472303[194] = 0;
   out_4553776162496472303[195] = 0;
   out_4553776162496472303[196] = 0;
   out_4553776162496472303[197] = 0;
   out_4553776162496472303[198] = 0;
   out_4553776162496472303[199] = 0;
   out_4553776162496472303[200] = 0;
   out_4553776162496472303[201] = 0;
   out_4553776162496472303[202] = 0;
   out_4553776162496472303[203] = 0;
   out_4553776162496472303[204] = 0;
   out_4553776162496472303[205] = 0;
   out_4553776162496472303[206] = 0;
   out_4553776162496472303[207] = 0;
   out_4553776162496472303[208] = 0;
   out_4553776162496472303[209] = 1;
   out_4553776162496472303[210] = 0;
   out_4553776162496472303[211] = 0;
   out_4553776162496472303[212] = 0;
   out_4553776162496472303[213] = 0;
   out_4553776162496472303[214] = 0;
   out_4553776162496472303[215] = 0;
   out_4553776162496472303[216] = 0;
   out_4553776162496472303[217] = 0;
   out_4553776162496472303[218] = 0;
   out_4553776162496472303[219] = 0;
   out_4553776162496472303[220] = 0;
   out_4553776162496472303[221] = 0;
   out_4553776162496472303[222] = 0;
   out_4553776162496472303[223] = 0;
   out_4553776162496472303[224] = 0;
   out_4553776162496472303[225] = 0;
   out_4553776162496472303[226] = 0;
   out_4553776162496472303[227] = 0;
   out_4553776162496472303[228] = 1;
   out_4553776162496472303[229] = 0;
   out_4553776162496472303[230] = 0;
   out_4553776162496472303[231] = 0;
   out_4553776162496472303[232] = 0;
   out_4553776162496472303[233] = 0;
   out_4553776162496472303[234] = 0;
   out_4553776162496472303[235] = 0;
   out_4553776162496472303[236] = 0;
   out_4553776162496472303[237] = 0;
   out_4553776162496472303[238] = 0;
   out_4553776162496472303[239] = 0;
   out_4553776162496472303[240] = 0;
   out_4553776162496472303[241] = 0;
   out_4553776162496472303[242] = 0;
   out_4553776162496472303[243] = 0;
   out_4553776162496472303[244] = 0;
   out_4553776162496472303[245] = 0;
   out_4553776162496472303[246] = 0;
   out_4553776162496472303[247] = 1;
   out_4553776162496472303[248] = 0;
   out_4553776162496472303[249] = 0;
   out_4553776162496472303[250] = 0;
   out_4553776162496472303[251] = 0;
   out_4553776162496472303[252] = 0;
   out_4553776162496472303[253] = 0;
   out_4553776162496472303[254] = 0;
   out_4553776162496472303[255] = 0;
   out_4553776162496472303[256] = 0;
   out_4553776162496472303[257] = 0;
   out_4553776162496472303[258] = 0;
   out_4553776162496472303[259] = 0;
   out_4553776162496472303[260] = 0;
   out_4553776162496472303[261] = 0;
   out_4553776162496472303[262] = 0;
   out_4553776162496472303[263] = 0;
   out_4553776162496472303[264] = 0;
   out_4553776162496472303[265] = 0;
   out_4553776162496472303[266] = 1;
   out_4553776162496472303[267] = 0;
   out_4553776162496472303[268] = 0;
   out_4553776162496472303[269] = 0;
   out_4553776162496472303[270] = 0;
   out_4553776162496472303[271] = 0;
   out_4553776162496472303[272] = 0;
   out_4553776162496472303[273] = 0;
   out_4553776162496472303[274] = 0;
   out_4553776162496472303[275] = 0;
   out_4553776162496472303[276] = 0;
   out_4553776162496472303[277] = 0;
   out_4553776162496472303[278] = 0;
   out_4553776162496472303[279] = 0;
   out_4553776162496472303[280] = 0;
   out_4553776162496472303[281] = 0;
   out_4553776162496472303[282] = 0;
   out_4553776162496472303[283] = 0;
   out_4553776162496472303[284] = 0;
   out_4553776162496472303[285] = 1;
   out_4553776162496472303[286] = 0;
   out_4553776162496472303[287] = 0;
   out_4553776162496472303[288] = 0;
   out_4553776162496472303[289] = 0;
   out_4553776162496472303[290] = 0;
   out_4553776162496472303[291] = 0;
   out_4553776162496472303[292] = 0;
   out_4553776162496472303[293] = 0;
   out_4553776162496472303[294] = 0;
   out_4553776162496472303[295] = 0;
   out_4553776162496472303[296] = 0;
   out_4553776162496472303[297] = 0;
   out_4553776162496472303[298] = 0;
   out_4553776162496472303[299] = 0;
   out_4553776162496472303[300] = 0;
   out_4553776162496472303[301] = 0;
   out_4553776162496472303[302] = 0;
   out_4553776162496472303[303] = 0;
   out_4553776162496472303[304] = 1;
   out_4553776162496472303[305] = 0;
   out_4553776162496472303[306] = 0;
   out_4553776162496472303[307] = 0;
   out_4553776162496472303[308] = 0;
   out_4553776162496472303[309] = 0;
   out_4553776162496472303[310] = 0;
   out_4553776162496472303[311] = 0;
   out_4553776162496472303[312] = 0;
   out_4553776162496472303[313] = 0;
   out_4553776162496472303[314] = 0;
   out_4553776162496472303[315] = 0;
   out_4553776162496472303[316] = 0;
   out_4553776162496472303[317] = 0;
   out_4553776162496472303[318] = 0;
   out_4553776162496472303[319] = 0;
   out_4553776162496472303[320] = 0;
   out_4553776162496472303[321] = 0;
   out_4553776162496472303[322] = 0;
   out_4553776162496472303[323] = 1;
}
void h_4(double *state, double *unused, double *out_3898746135561568286) {
   out_3898746135561568286[0] = state[6] + state[9];
   out_3898746135561568286[1] = state[7] + state[10];
   out_3898746135561568286[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6156174869959243360) {
   out_6156174869959243360[0] = 0;
   out_6156174869959243360[1] = 0;
   out_6156174869959243360[2] = 0;
   out_6156174869959243360[3] = 0;
   out_6156174869959243360[4] = 0;
   out_6156174869959243360[5] = 0;
   out_6156174869959243360[6] = 1;
   out_6156174869959243360[7] = 0;
   out_6156174869959243360[8] = 0;
   out_6156174869959243360[9] = 1;
   out_6156174869959243360[10] = 0;
   out_6156174869959243360[11] = 0;
   out_6156174869959243360[12] = 0;
   out_6156174869959243360[13] = 0;
   out_6156174869959243360[14] = 0;
   out_6156174869959243360[15] = 0;
   out_6156174869959243360[16] = 0;
   out_6156174869959243360[17] = 0;
   out_6156174869959243360[18] = 0;
   out_6156174869959243360[19] = 0;
   out_6156174869959243360[20] = 0;
   out_6156174869959243360[21] = 0;
   out_6156174869959243360[22] = 0;
   out_6156174869959243360[23] = 0;
   out_6156174869959243360[24] = 0;
   out_6156174869959243360[25] = 1;
   out_6156174869959243360[26] = 0;
   out_6156174869959243360[27] = 0;
   out_6156174869959243360[28] = 1;
   out_6156174869959243360[29] = 0;
   out_6156174869959243360[30] = 0;
   out_6156174869959243360[31] = 0;
   out_6156174869959243360[32] = 0;
   out_6156174869959243360[33] = 0;
   out_6156174869959243360[34] = 0;
   out_6156174869959243360[35] = 0;
   out_6156174869959243360[36] = 0;
   out_6156174869959243360[37] = 0;
   out_6156174869959243360[38] = 0;
   out_6156174869959243360[39] = 0;
   out_6156174869959243360[40] = 0;
   out_6156174869959243360[41] = 0;
   out_6156174869959243360[42] = 0;
   out_6156174869959243360[43] = 0;
   out_6156174869959243360[44] = 1;
   out_6156174869959243360[45] = 0;
   out_6156174869959243360[46] = 0;
   out_6156174869959243360[47] = 1;
   out_6156174869959243360[48] = 0;
   out_6156174869959243360[49] = 0;
   out_6156174869959243360[50] = 0;
   out_6156174869959243360[51] = 0;
   out_6156174869959243360[52] = 0;
   out_6156174869959243360[53] = 0;
}
void h_10(double *state, double *unused, double *out_5696118002194808494) {
   out_5696118002194808494[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5696118002194808494[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5696118002194808494[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2562922199780515749) {
   out_2562922199780515749[0] = 0;
   out_2562922199780515749[1] = 9.8100000000000005*cos(state[1]);
   out_2562922199780515749[2] = 0;
   out_2562922199780515749[3] = 0;
   out_2562922199780515749[4] = -state[8];
   out_2562922199780515749[5] = state[7];
   out_2562922199780515749[6] = 0;
   out_2562922199780515749[7] = state[5];
   out_2562922199780515749[8] = -state[4];
   out_2562922199780515749[9] = 0;
   out_2562922199780515749[10] = 0;
   out_2562922199780515749[11] = 0;
   out_2562922199780515749[12] = 1;
   out_2562922199780515749[13] = 0;
   out_2562922199780515749[14] = 0;
   out_2562922199780515749[15] = 1;
   out_2562922199780515749[16] = 0;
   out_2562922199780515749[17] = 0;
   out_2562922199780515749[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2562922199780515749[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2562922199780515749[20] = 0;
   out_2562922199780515749[21] = state[8];
   out_2562922199780515749[22] = 0;
   out_2562922199780515749[23] = -state[6];
   out_2562922199780515749[24] = -state[5];
   out_2562922199780515749[25] = 0;
   out_2562922199780515749[26] = state[3];
   out_2562922199780515749[27] = 0;
   out_2562922199780515749[28] = 0;
   out_2562922199780515749[29] = 0;
   out_2562922199780515749[30] = 0;
   out_2562922199780515749[31] = 1;
   out_2562922199780515749[32] = 0;
   out_2562922199780515749[33] = 0;
   out_2562922199780515749[34] = 1;
   out_2562922199780515749[35] = 0;
   out_2562922199780515749[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2562922199780515749[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2562922199780515749[38] = 0;
   out_2562922199780515749[39] = -state[7];
   out_2562922199780515749[40] = state[6];
   out_2562922199780515749[41] = 0;
   out_2562922199780515749[42] = state[4];
   out_2562922199780515749[43] = -state[3];
   out_2562922199780515749[44] = 0;
   out_2562922199780515749[45] = 0;
   out_2562922199780515749[46] = 0;
   out_2562922199780515749[47] = 0;
   out_2562922199780515749[48] = 0;
   out_2562922199780515749[49] = 0;
   out_2562922199780515749[50] = 1;
   out_2562922199780515749[51] = 0;
   out_2562922199780515749[52] = 0;
   out_2562922199780515749[53] = 1;
}
void h_13(double *state, double *unused, double *out_5143493122680971933) {
   out_5143493122680971933[0] = state[3];
   out_5143493122680971933[1] = state[4];
   out_5143493122680971933[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1454456338357457569) {
   out_1454456338357457569[0] = 0;
   out_1454456338357457569[1] = 0;
   out_1454456338357457569[2] = 0;
   out_1454456338357457569[3] = 1;
   out_1454456338357457569[4] = 0;
   out_1454456338357457569[5] = 0;
   out_1454456338357457569[6] = 0;
   out_1454456338357457569[7] = 0;
   out_1454456338357457569[8] = 0;
   out_1454456338357457569[9] = 0;
   out_1454456338357457569[10] = 0;
   out_1454456338357457569[11] = 0;
   out_1454456338357457569[12] = 0;
   out_1454456338357457569[13] = 0;
   out_1454456338357457569[14] = 0;
   out_1454456338357457569[15] = 0;
   out_1454456338357457569[16] = 0;
   out_1454456338357457569[17] = 0;
   out_1454456338357457569[18] = 0;
   out_1454456338357457569[19] = 0;
   out_1454456338357457569[20] = 0;
   out_1454456338357457569[21] = 0;
   out_1454456338357457569[22] = 1;
   out_1454456338357457569[23] = 0;
   out_1454456338357457569[24] = 0;
   out_1454456338357457569[25] = 0;
   out_1454456338357457569[26] = 0;
   out_1454456338357457569[27] = 0;
   out_1454456338357457569[28] = 0;
   out_1454456338357457569[29] = 0;
   out_1454456338357457569[30] = 0;
   out_1454456338357457569[31] = 0;
   out_1454456338357457569[32] = 0;
   out_1454456338357457569[33] = 0;
   out_1454456338357457569[34] = 0;
   out_1454456338357457569[35] = 0;
   out_1454456338357457569[36] = 0;
   out_1454456338357457569[37] = 0;
   out_1454456338357457569[38] = 0;
   out_1454456338357457569[39] = 0;
   out_1454456338357457569[40] = 0;
   out_1454456338357457569[41] = 1;
   out_1454456338357457569[42] = 0;
   out_1454456338357457569[43] = 0;
   out_1454456338357457569[44] = 0;
   out_1454456338357457569[45] = 0;
   out_1454456338357457569[46] = 0;
   out_1454456338357457569[47] = 0;
   out_1454456338357457569[48] = 0;
   out_1454456338357457569[49] = 0;
   out_1454456338357457569[50] = 0;
   out_1454456338357457569[51] = 0;
   out_1454456338357457569[52] = 0;
   out_1454456338357457569[53] = 0;
}
void h_14(double *state, double *unused, double *out_1192181091089126491) {
   out_1192181091089126491[0] = state[6];
   out_1192181091089126491[1] = state[7];
   out_1192181091089126491[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2192934013619758831) {
   out_2192934013619758831[0] = 0;
   out_2192934013619758831[1] = 0;
   out_2192934013619758831[2] = 0;
   out_2192934013619758831[3] = 0;
   out_2192934013619758831[4] = 0;
   out_2192934013619758831[5] = 0;
   out_2192934013619758831[6] = 1;
   out_2192934013619758831[7] = 0;
   out_2192934013619758831[8] = 0;
   out_2192934013619758831[9] = 0;
   out_2192934013619758831[10] = 0;
   out_2192934013619758831[11] = 0;
   out_2192934013619758831[12] = 0;
   out_2192934013619758831[13] = 0;
   out_2192934013619758831[14] = 0;
   out_2192934013619758831[15] = 0;
   out_2192934013619758831[16] = 0;
   out_2192934013619758831[17] = 0;
   out_2192934013619758831[18] = 0;
   out_2192934013619758831[19] = 0;
   out_2192934013619758831[20] = 0;
   out_2192934013619758831[21] = 0;
   out_2192934013619758831[22] = 0;
   out_2192934013619758831[23] = 0;
   out_2192934013619758831[24] = 0;
   out_2192934013619758831[25] = 1;
   out_2192934013619758831[26] = 0;
   out_2192934013619758831[27] = 0;
   out_2192934013619758831[28] = 0;
   out_2192934013619758831[29] = 0;
   out_2192934013619758831[30] = 0;
   out_2192934013619758831[31] = 0;
   out_2192934013619758831[32] = 0;
   out_2192934013619758831[33] = 0;
   out_2192934013619758831[34] = 0;
   out_2192934013619758831[35] = 0;
   out_2192934013619758831[36] = 0;
   out_2192934013619758831[37] = 0;
   out_2192934013619758831[38] = 0;
   out_2192934013619758831[39] = 0;
   out_2192934013619758831[40] = 0;
   out_2192934013619758831[41] = 0;
   out_2192934013619758831[42] = 0;
   out_2192934013619758831[43] = 0;
   out_2192934013619758831[44] = 1;
   out_2192934013619758831[45] = 0;
   out_2192934013619758831[46] = 0;
   out_2192934013619758831[47] = 0;
   out_2192934013619758831[48] = 0;
   out_2192934013619758831[49] = 0;
   out_2192934013619758831[50] = 0;
   out_2192934013619758831[51] = 0;
   out_2192934013619758831[52] = 0;
   out_2192934013619758831[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4724133448419912693) {
  err_fun(nom_x, delta_x, out_4724133448419912693);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6531814374965429464) {
  inv_err_fun(nom_x, true_x, out_6531814374965429464);
}
void pose_H_mod_fun(double *state, double *out_4336476144052946499) {
  H_mod_fun(state, out_4336476144052946499);
}
void pose_f_fun(double *state, double dt, double *out_5802866657257443587) {
  f_fun(state,  dt, out_5802866657257443587);
}
void pose_F_fun(double *state, double dt, double *out_4553776162496472303) {
  F_fun(state,  dt, out_4553776162496472303);
}
void pose_h_4(double *state, double *unused, double *out_3898746135561568286) {
  h_4(state, unused, out_3898746135561568286);
}
void pose_H_4(double *state, double *unused, double *out_6156174869959243360) {
  H_4(state, unused, out_6156174869959243360);
}
void pose_h_10(double *state, double *unused, double *out_5696118002194808494) {
  h_10(state, unused, out_5696118002194808494);
}
void pose_H_10(double *state, double *unused, double *out_2562922199780515749) {
  H_10(state, unused, out_2562922199780515749);
}
void pose_h_13(double *state, double *unused, double *out_5143493122680971933) {
  h_13(state, unused, out_5143493122680971933);
}
void pose_H_13(double *state, double *unused, double *out_1454456338357457569) {
  H_13(state, unused, out_1454456338357457569);
}
void pose_h_14(double *state, double *unused, double *out_1192181091089126491) {
  h_14(state, unused, out_1192181091089126491);
}
void pose_H_14(double *state, double *unused, double *out_2192934013619758831) {
  H_14(state, unused, out_2192934013619758831);
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
