#include<iostream>
#include<string>
#include<vector>
#include<fstream>
//#include "data_container.h"

using namespace std;

class tensor
{
public:
    vector<vector<unsigned long long>> data;
};

class tensors
{
public:
    vector<tensor> multi_tensor;
    bool zero_tensor;
};


class layer
{
public:
    vector<tensors> packed_all_levels;
    double scale[2];
    tensor packed_bits;
    vector<double> bias;
};

class DataContainer
{
public:
    vector<layer> setData(ifstream & in);
    void readInt(ifstream & in, int &x);
    void readLong(ifstream & in, unsigned long long &x);
    void readDouble(ifstream & in, double &x);
    void display(layer l);
};


class restore_quantize_state
{
public:
    void restore_state(vector<layer> layers);
    vector<unsigned short> unpacked_bits(vector<vector<vector<unsigned long long> > > packed_bits);
    void unpack_param(vector<tensors> packed_all_level,double scale0,double scale1, tensor packed_bits);
    int num_of_params(vector<layer> layers);
};


