#include<iostream>
#include<string>
#include<vector>
#include<fstream>

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
    vector<tensors> all_quantizes;
    double scale[2];
    tensor packed;
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