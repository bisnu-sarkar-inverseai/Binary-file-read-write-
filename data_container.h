#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

class tensor
{
public:
    vector<vector<long long>> data;
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
    void setData(ifstream & in);
    void readInt(ifstream & in, int &x);
    void readLong(ifstream & in, long long &x);
    void readDouble(ifstream & in, double &x);
};