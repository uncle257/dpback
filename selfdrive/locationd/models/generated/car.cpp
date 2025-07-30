#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with sympy 1.9                        *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6920520309618378367) {
   out_6920520309618378367[0] = delta_x[0] + nom_x[0];
   out_6920520309618378367[1] = delta_x[1] + nom_x[1];
   out_6920520309618378367[2] = delta_x[2] + nom_x[2];
   out_6920520309618378367[3] = delta_x[3] + nom_x[3];
   out_6920520309618378367[4] = delta_x[4] + nom_x[4];
   out_6920520309618378367[5] = delta_x[5] + nom_x[5];
   out_6920520309618378367[6] = delta_x[6] + nom_x[6];
   out_6920520309618378367[7] = delta_x[7] + nom_x[7];
   out_6920520309618378367[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5302696854806540781) {
   out_5302696854806540781[0] = -nom_x[0] + true_x[0];
   out_5302696854806540781[1] = -nom_x[1] + true_x[1];
   out_5302696854806540781[2] = -nom_x[2] + true_x[2];
   out_5302696854806540781[3] = -nom_x[3] + true_x[3];
   out_5302696854806540781[4] = -nom_x[4] + true_x[4];
   out_5302696854806540781[5] = -nom_x[5] + true_x[5];
   out_5302696854806540781[6] = -nom_x[6] + true_x[6];
   out_5302696854806540781[7] = -nom_x[7] + true_x[7];
   out_5302696854806540781[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4449921069090285960) {
   out_4449921069090285960[0] = 1.0;
   out_4449921069090285960[1] = 0;
   out_4449921069090285960[2] = 0;
   out_4449921069090285960[3] = 0;
   out_4449921069090285960[4] = 0;
   out_4449921069090285960[5] = 0;
   out_4449921069090285960[6] = 0;
   out_4449921069090285960[7] = 0;
   out_4449921069090285960[8] = 0;
   out_4449921069090285960[9] = 0;
   out_4449921069090285960[10] = 1.0;
   out_4449921069090285960[11] = 0;
   out_4449921069090285960[12] = 0;
   out_4449921069090285960[13] = 0;
   out_4449921069090285960[14] = 0;
   out_4449921069090285960[15] = 0;
   out_4449921069090285960[16] = 0;
   out_4449921069090285960[17] = 0;
   out_4449921069090285960[18] = 0;
   out_4449921069090285960[19] = 0;
   out_4449921069090285960[20] = 1.0;
   out_4449921069090285960[21] = 0;
   out_4449921069090285960[22] = 0;
   out_4449921069090285960[23] = 0;
   out_4449921069090285960[24] = 0;
   out_4449921069090285960[25] = 0;
   out_4449921069090285960[26] = 0;
   out_4449921069090285960[27] = 0;
   out_4449921069090285960[28] = 0;
   out_4449921069090285960[29] = 0;
   out_4449921069090285960[30] = 1.0;
   out_4449921069090285960[31] = 0;
   out_4449921069090285960[32] = 0;
   out_4449921069090285960[33] = 0;
   out_4449921069090285960[34] = 0;
   out_4449921069090285960[35] = 0;
   out_4449921069090285960[36] = 0;
   out_4449921069090285960[37] = 0;
   out_4449921069090285960[38] = 0;
   out_4449921069090285960[39] = 0;
   out_4449921069090285960[40] = 1.0;
   out_4449921069090285960[41] = 0;
   out_4449921069090285960[42] = 0;
   out_4449921069090285960[43] = 0;
   out_4449921069090285960[44] = 0;
   out_4449921069090285960[45] = 0;
   out_4449921069090285960[46] = 0;
   out_4449921069090285960[47] = 0;
   out_4449921069090285960[48] = 0;
   out_4449921069090285960[49] = 0;
   out_4449921069090285960[50] = 1.0;
   out_4449921069090285960[51] = 0;
   out_4449921069090285960[52] = 0;
   out_4449921069090285960[53] = 0;
   out_4449921069090285960[54] = 0;
   out_4449921069090285960[55] = 0;
   out_4449921069090285960[56] = 0;
   out_4449921069090285960[57] = 0;
   out_4449921069090285960[58] = 0;
   out_4449921069090285960[59] = 0;
   out_4449921069090285960[60] = 1.0;
   out_4449921069090285960[61] = 0;
   out_4449921069090285960[62] = 0;
   out_4449921069090285960[63] = 0;
   out_4449921069090285960[64] = 0;
   out_4449921069090285960[65] = 0;
   out_4449921069090285960[66] = 0;
   out_4449921069090285960[67] = 0;
   out_4449921069090285960[68] = 0;
   out_4449921069090285960[69] = 0;
   out_4449921069090285960[70] = 1.0;
   out_4449921069090285960[71] = 0;
   out_4449921069090285960[72] = 0;
   out_4449921069090285960[73] = 0;
   out_4449921069090285960[74] = 0;
   out_4449921069090285960[75] = 0;
   out_4449921069090285960[76] = 0;
   out_4449921069090285960[77] = 0;
   out_4449921069090285960[78] = 0;
   out_4449921069090285960[79] = 0;
   out_4449921069090285960[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7814524287760230042) {
   out_7814524287760230042[0] = state[0];
   out_7814524287760230042[1] = state[1];
   out_7814524287760230042[2] = state[2];
   out_7814524287760230042[3] = state[3];
   out_7814524287760230042[4] = state[4];
   out_7814524287760230042[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7814524287760230042[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7814524287760230042[7] = state[7];
   out_7814524287760230042[8] = state[8];
}
void F_fun(double *state, double dt, double *out_411706590768419199) {
   out_411706590768419199[0] = 1;
   out_411706590768419199[1] = 0;
   out_411706590768419199[2] = 0;
   out_411706590768419199[3] = 0;
   out_411706590768419199[4] = 0;
   out_411706590768419199[5] = 0;
   out_411706590768419199[6] = 0;
   out_411706590768419199[7] = 0;
   out_411706590768419199[8] = 0;
   out_411706590768419199[9] = 0;
   out_411706590768419199[10] = 1;
   out_411706590768419199[11] = 0;
   out_411706590768419199[12] = 0;
   out_411706590768419199[13] = 0;
   out_411706590768419199[14] = 0;
   out_411706590768419199[15] = 0;
   out_411706590768419199[16] = 0;
   out_411706590768419199[17] = 0;
   out_411706590768419199[18] = 0;
   out_411706590768419199[19] = 0;
   out_411706590768419199[20] = 1;
   out_411706590768419199[21] = 0;
   out_411706590768419199[22] = 0;
   out_411706590768419199[23] = 0;
   out_411706590768419199[24] = 0;
   out_411706590768419199[25] = 0;
   out_411706590768419199[26] = 0;
   out_411706590768419199[27] = 0;
   out_411706590768419199[28] = 0;
   out_411706590768419199[29] = 0;
   out_411706590768419199[30] = 1;
   out_411706590768419199[31] = 0;
   out_411706590768419199[32] = 0;
   out_411706590768419199[33] = 0;
   out_411706590768419199[34] = 0;
   out_411706590768419199[35] = 0;
   out_411706590768419199[36] = 0;
   out_411706590768419199[37] = 0;
   out_411706590768419199[38] = 0;
   out_411706590768419199[39] = 0;
   out_411706590768419199[40] = 1;
   out_411706590768419199[41] = 0;
   out_411706590768419199[42] = 0;
   out_411706590768419199[43] = 0;
   out_411706590768419199[44] = 0;
   out_411706590768419199[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_411706590768419199[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_411706590768419199[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_411706590768419199[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_411706590768419199[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_411706590768419199[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_411706590768419199[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_411706590768419199[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_411706590768419199[53] = -9.8000000000000007*dt;
   out_411706590768419199[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_411706590768419199[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_411706590768419199[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_411706590768419199[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_411706590768419199[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_411706590768419199[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_411706590768419199[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_411706590768419199[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_411706590768419199[62] = 0;
   out_411706590768419199[63] = 0;
   out_411706590768419199[64] = 0;
   out_411706590768419199[65] = 0;
   out_411706590768419199[66] = 0;
   out_411706590768419199[67] = 0;
   out_411706590768419199[68] = 0;
   out_411706590768419199[69] = 0;
   out_411706590768419199[70] = 1;
   out_411706590768419199[71] = 0;
   out_411706590768419199[72] = 0;
   out_411706590768419199[73] = 0;
   out_411706590768419199[74] = 0;
   out_411706590768419199[75] = 0;
   out_411706590768419199[76] = 0;
   out_411706590768419199[77] = 0;
   out_411706590768419199[78] = 0;
   out_411706590768419199[79] = 0;
   out_411706590768419199[80] = 1;
}
void h_25(double *state, double *unused, double *out_624214668376866341) {
   out_624214668376866341[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4996036056466787679) {
   out_4996036056466787679[0] = 0;
   out_4996036056466787679[1] = 0;
   out_4996036056466787679[2] = 0;
   out_4996036056466787679[3] = 0;
   out_4996036056466787679[4] = 0;
   out_4996036056466787679[5] = 0;
   out_4996036056466787679[6] = 1;
   out_4996036056466787679[7] = 0;
   out_4996036056466787679[8] = 0;
}
void h_24(double *state, double *unused, double *out_7726624714175041949) {
   out_7726624714175041949[0] = state[4];
   out_7726624714175041949[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8630386512586775674) {
   out_8630386512586775674[0] = 0;
   out_8630386512586775674[1] = 0;
   out_8630386512586775674[2] = 0;
   out_8630386512586775674[3] = 0;
   out_8630386512586775674[4] = 1;
   out_8630386512586775674[5] = 0;
   out_8630386512586775674[6] = 0;
   out_8630386512586775674[7] = 0;
   out_8630386512586775674[8] = 0;
   out_8630386512586775674[9] = 0;
   out_8630386512586775674[10] = 0;
   out_8630386512586775674[11] = 0;
   out_8630386512586775674[12] = 0;
   out_8630386512586775674[13] = 0;
   out_8630386512586775674[14] = 1;
   out_8630386512586775674[15] = 0;
   out_8630386512586775674[16] = 0;
   out_8630386512586775674[17] = 0;
}
void h_30(double *state, double *unused, double *out_2951458280903618951) {
   out_2951458280903618951[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5125375003610027749) {
   out_5125375003610027749[0] = 0;
   out_5125375003610027749[1] = 0;
   out_5125375003610027749[2] = 0;
   out_5125375003610027749[3] = 0;
   out_5125375003610027749[4] = 1;
   out_5125375003610027749[5] = 0;
   out_5125375003610027749[6] = 0;
   out_5125375003610027749[7] = 0;
   out_5125375003610027749[8] = 0;
}
void h_26(double *state, double *unused, double *out_464815008745451065) {
   out_464815008745451065[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8737539375340843903) {
   out_8737539375340843903[0] = 0;
   out_8737539375340843903[1] = 0;
   out_8737539375340843903[2] = 0;
   out_8737539375340843903[3] = 0;
   out_8737539375340843903[4] = 0;
   out_8737539375340843903[5] = 0;
   out_8737539375340843903[6] = 0;
   out_8737539375340843903[7] = 1;
   out_8737539375340843903[8] = 0;
}
void h_27(double *state, double *unused, double *out_2651633144370590248) {
   out_2651633144370590248[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7300138315410452660) {
   out_7300138315410452660[0] = 0;
   out_7300138315410452660[1] = 0;
   out_7300138315410452660[2] = 0;
   out_7300138315410452660[3] = 1;
   out_7300138315410452660[4] = 0;
   out_7300138315410452660[5] = 0;
   out_7300138315410452660[6] = 0;
   out_7300138315410452660[7] = 0;
   out_7300138315410452660[8] = 0;
}
void h_29(double *state, double *unused, double *out_2926827206655096137) {
   out_2926827206655096137[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4615143659295635565) {
   out_4615143659295635565[0] = 0;
   out_4615143659295635565[1] = 1;
   out_4615143659295635565[2] = 0;
   out_4615143659295635565[3] = 0;
   out_4615143659295635565[4] = 0;
   out_4615143659295635565[5] = 0;
   out_4615143659295635565[6] = 0;
   out_4615143659295635565[7] = 0;
   out_4615143659295635565[8] = 0;
}
void h_28(double *state, double *unused, double *out_2833450886970242207) {
   out_2833450886970242207[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8749201397344385477) {
   out_8749201397344385477[0] = 1;
   out_8749201397344385477[1] = 0;
   out_8749201397344385477[2] = 0;
   out_8749201397344385477[3] = 0;
   out_8749201397344385477[4] = 0;
   out_8749201397344385477[5] = 0;
   out_8749201397344385477[6] = 0;
   out_8749201397344385477[7] = 0;
   out_8749201397344385477[8] = 0;
}
void h_31(double *state, double *unused, double *out_899408730661372230) {
   out_899408730661372230[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4965390094589827251) {
   out_4965390094589827251[0] = 0;
   out_4965390094589827251[1] = 0;
   out_4965390094589827251[2] = 0;
   out_4965390094589827251[3] = 0;
   out_4965390094589827251[4] = 0;
   out_4965390094589827251[5] = 0;
   out_4965390094589827251[6] = 0;
   out_4965390094589827251[7] = 0;
   out_4965390094589827251[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_6920520309618378367) {
  err_fun(nom_x, delta_x, out_6920520309618378367);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5302696854806540781) {
  inv_err_fun(nom_x, true_x, out_5302696854806540781);
}
void car_H_mod_fun(double *state, double *out_4449921069090285960) {
  H_mod_fun(state, out_4449921069090285960);
}
void car_f_fun(double *state, double dt, double *out_7814524287760230042) {
  f_fun(state,  dt, out_7814524287760230042);
}
void car_F_fun(double *state, double dt, double *out_411706590768419199) {
  F_fun(state,  dt, out_411706590768419199);
}
void car_h_25(double *state, double *unused, double *out_624214668376866341) {
  h_25(state, unused, out_624214668376866341);
}
void car_H_25(double *state, double *unused, double *out_4996036056466787679) {
  H_25(state, unused, out_4996036056466787679);
}
void car_h_24(double *state, double *unused, double *out_7726624714175041949) {
  h_24(state, unused, out_7726624714175041949);
}
void car_H_24(double *state, double *unused, double *out_8630386512586775674) {
  H_24(state, unused, out_8630386512586775674);
}
void car_h_30(double *state, double *unused, double *out_2951458280903618951) {
  h_30(state, unused, out_2951458280903618951);
}
void car_H_30(double *state, double *unused, double *out_5125375003610027749) {
  H_30(state, unused, out_5125375003610027749);
}
void car_h_26(double *state, double *unused, double *out_464815008745451065) {
  h_26(state, unused, out_464815008745451065);
}
void car_H_26(double *state, double *unused, double *out_8737539375340843903) {
  H_26(state, unused, out_8737539375340843903);
}
void car_h_27(double *state, double *unused, double *out_2651633144370590248) {
  h_27(state, unused, out_2651633144370590248);
}
void car_H_27(double *state, double *unused, double *out_7300138315410452660) {
  H_27(state, unused, out_7300138315410452660);
}
void car_h_29(double *state, double *unused, double *out_2926827206655096137) {
  h_29(state, unused, out_2926827206655096137);
}
void car_H_29(double *state, double *unused, double *out_4615143659295635565) {
  H_29(state, unused, out_4615143659295635565);
}
void car_h_28(double *state, double *unused, double *out_2833450886970242207) {
  h_28(state, unused, out_2833450886970242207);
}
void car_H_28(double *state, double *unused, double *out_8749201397344385477) {
  H_28(state, unused, out_8749201397344385477);
}
void car_h_31(double *state, double *unused, double *out_899408730661372230) {
  h_31(state, unused, out_899408730661372230);
}
void car_H_31(double *state, double *unused, double *out_4965390094589827251) {
  H_31(state, unused, out_4965390094589827251);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
