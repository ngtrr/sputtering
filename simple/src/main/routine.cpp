


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