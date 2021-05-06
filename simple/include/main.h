#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<fstream>


#define Np 256*256                                  //サンプル数
#define PERIOD 8.0f                                 //最大時間
#define dt 0.01f                                    //ステップ時間
#define Nt (int)((double)PERIOD/(double)dt +1e-3)   //ステップ数