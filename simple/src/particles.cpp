#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<fstream>


#define Np 256*256                                  //サンプル数
#define PERIOD 8.0f                                 //最大時間
#define dt 0.01f                                    //ステップ時間
#define Nt (int)((double)PERIOD/(double)dt +1e-3)   //ステップ数

void init(float *px,float *py){
    int i;
    float x,y;
    srand(820);//乱数のシードは適当に定める
    for(i=0;i<Np;i++){
        do{
            x = (float)rand()/RAND_MAX;
            y = (float)rand()/RAND_MAX;
        }
        while((x-0.5f)*(x-0.5f)+(y-0.25f)*(y-0.25f)>0.24*0.24);
        px[i] = x;
        py[i] = y;
    }
}

inline float U(float x,float y,float t){
    return -2.0f*cosf(M_PI*t/PERIOD)*sinf(M_PI*x)*sinf(M_PI*x)*cosf(M_PI*y)*sinf(M_PI*y);
}
    
inline float V(float x,float y,float t){
    return 2.0f*cosf(M_PI*t/PERIOD)*sinf(M_PI*y)*sinf(M_PI*y)*cosf(M_PI*x)*sinf(M_PI*x);
}

inline float W(float x,float y,float t){
    return 2.0f*cosf(M_PI*t/PERIOD)*sinf(M_PI*y)*sinf(M_PI*y)*cosf(M_PI*x)*sinf(M_PI*x);
}

void integrate (float *px,float *py, float t){
    int i;
    float x,y,pu,pv;
    for(i=0;i<Np;i++){
        x = px[i];
        y = py[i];
        pu = U(x,y,t);
        pv = V(x,y,t);
        px[i] = px[i] + dt*pu;
        py[i] = py[i] + dt*pv;
    }
}

void output_data(float *pos_x,float *pos_y,float t){
    int i;
    std::ofstream outputfile("particle" + std::to_string(t).erase(4) + ".txt");
    for(i=0;i<Np;i++){
        outputfile << pos_x[i] <<" "<< pos_y[i] << std::endl;
    }
    outputfile.close();
}

int main(void){ 
    float *px,*py;
    px = (float *)malloc(Np*sizeof(float)); 
    py = (float *)malloc(Np*sizeof(float)); 
    init(px, py); 
    for(int n=1;n<=Nt;n++){ 
            integrate(px,py,(n-1)*dt);
            output_data(px,py,(n-1)*dt);
        }
    //std::cout << Nt << std::endl;
    free(px);
    free(py);
}