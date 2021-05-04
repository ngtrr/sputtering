#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Np 256*256
#define PERIOD 8.0f
#define dt 0.01f
#define Nt (int)((double)PERIOD/(double)dt + 1e‐3 )
#define THREAD 256
#define BLOCK  (Np/THREAD)

int main(void){
    int n;
    float *px,*py;
    float *host_px=(float *)malloc(Np*sizeof(float));
    float *host_py=(float *)malloc(Np*sizeof(float));
    cudaMalloc((void **)&px, Np*sizeof(float));
    cudaMalloc((void **)&py, Np*sizeof(float));
    init(host_px, host_py);
    cudaMemcpy(px, host_px, Np*sizeof(float),  cudaMemcpyHostToDevice);
    cudaMemcpy(py, host_py, Np*sizeof(float),  cudaMemcpyHostToDevice);

    for(n=1;n<=Nt;n++){
        printf("%d/%d¥n",n,Nt);
        integrate<<<BLOCK, THREAD>>> (px,py,(n‐1)*dt);
        cudaThreadSynchronize();
    }

    free(host_px);
    free(host_py);
    cudaFree(px);
    cudaFree(py);
    return 0;
}

    void init(float *px,float *py){
        int i;
        float x,y;
        srand(820);

        for(i=0;i<Np;i++){
            do{
                x = (float)rand()/RAND_MAX;
                y = (float)rand()/RAND_MAX;
            }while( (x‐0.5f)*(x‐0.5f)+(y‐0.25f)*(y‐0.25f) > 0.24*0.24 );
            px[i] = x;
            py[i] = y;
        }
    }
    
    __device__ float U (float x, float y, float t){
        return ‐2.0f*cosf(M_PI*t/PERIOD)*sinf(M_PI*x) *sinf(M_PI*x)*cosf(M_PI*y)*sinf(M_PI*y);
    }
    
    __device__ float V (float x, float y, float t){
        return  2.0f*cosf(M_PI*t/PERIOD)*sinf(M_PI*y) *sinf(M_PI*y)*cosf(M_PI*x)*sinf(M_PI*x);
    }
    
    __global__ void integrate (float *px,float *py, float t){
        int i = blockIdx.x*blockDim.x + threadIdx.x;
        float x,y,pu,pv;
        x = px[i];
        y = py[i];
        pu = U(x,y,t);
        pv = V(x,y,t);
        px[i] = px[i] + dt*pu;
        py[i] = py[i] + dt*pv;
    }