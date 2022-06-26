#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<tuple>

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