#include"../include/mass.h"

//reference webpage of MASS OF NUCLEI
// http://amdc.impcas.ac.cn/index.html
Mass he6 = {6018885.889 * 1.0e-6 * 931.494013, 6.0, 2.0};
Mass h3 = {3016049.28132 * 1.0e-6 * 931.494013, 3.0, 1.0};
Mass p = {1007825.031898 * 1.0e-6 * 931.494013, 1.0, 1.0};
Mass c12 = {12.0 * 1.0e-6 * 931.494013, 12.0, 6.0};
Mass d = {2014101.777844 * 1.0e-6 * 931.494013, 2.0, 1.0};
Mass n = {1008664.91590 * 1.0e-6 * 931.494013, 1.0, 0.0};
Mass li7 = {7016003.43426 * 1.0e-6 * 931.494013, 7.0, 3.0};


Mass *main_beam = &he6;
Mass *main_target = &d;
Mass *sub_beam = &h3;
Mass *sub_target = &c12;
Mass *out_beam = &n;
Mass *out_target = &li7;

