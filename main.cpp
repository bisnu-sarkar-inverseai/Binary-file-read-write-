#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "data_container.h"

using namespace std;

int main()
{
    ifstream in{"weight_data_for_cpp.bin", ios::binary  | ios::in};
    DataContainer dc;
    if(!in){
        printf("Error: Couldn't open");
        return 0;
    }
    else{
       vector<layer> Layer = dc.setData(in);

       dc.display(Layer[0]);
    }
 
}
