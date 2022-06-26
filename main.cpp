#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "restore_quantize.h"

using namespace std;
// run command: g++ main.cpp data_container.cpp restore_quantize.cpp  -o main
// .\main

int main()
{
    ifstream in{"weight_data_for_cpp.bin", ios::binary  | ios::in};
   
    restore_quantize_state state;
    DataContainer dc;
    if(!in){
        printf("Error: Couldn't open");
        return 0;
    }
    else{
        vector<layer> Layers = dc.setData(in);

        state.restore_state(Layers);    

        //dc.display(Layers[0]);
    }
 
}
