
void output_data(float *pos_x,float *pos_y,float t){
    int i;
    std::ofstream outputfile("particle" + std::to_string(t).erase(4) + ".txt");
    for(i=0;i<Np;i++){
        outputfile << pos_x[i] <<" "<< pos_y[i] << std::endl;
    }
    outputfile.close();
}