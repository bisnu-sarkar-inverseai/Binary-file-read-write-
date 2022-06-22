#include <iostream>
#include <vector>
using namespace std;

vector<unsigned int> unpacked(vector<vector<vector<unsigned long long> > > packed){
    int lines = packed.size();
    int nbits = packed[0].size();
    int block_size = packed[0][0].size();

    cout<<lines<<" "<<nbits<<" "<<block_size<<endl;
    int storage =64;

    vector<unsigned short> out(lines*block_size*storage,0);

    unsigned short x;
    unsigned long long tem;
    int c=0;
    for(int line=0;line<lines;++line){
        for(int bit_in=0;bit_in<storage;++bit_in){
            for(int bit_out=0;bit_out<nbits;++bit_out){
               for(int index=0;index<block_size;++index){           
                    tem = packed[line][bit_out][index];
                   // cout<<tem<<endl;
                    x = (tem >> bit_in) & 1;
                    out[line * block_size * storage + bit_in * block_size + index] |= x << bit_out;
               } 
            }
           // cout<<bit_in<<endl;
        }
       // cout<<line<<endl;
    }
   
    return out; 
}

int main()
{
    vector<unsigned long long> v;
    vector<vector<unsigned long long>> vv;
    vector<vector<vector<unsigned long long>>> vvv;

    v.insert(v.end(), { 1, 2, 3 });
    vv.push_back(v);
    v.clear();
    v.insert(v.end(), { 3, 4, 5});
    vv.push_back(v);
    v.clear();
    v.insert(v.end(), { 5, 6, 7 });
    vv.push_back(v);
    v.clear();
    v.insert(v.end(), { 8, 9, 10 });
    vv.push_back(v);
    v.clear();

    vvv.push_back(vv);

    unpacked(vvv);

    return 0;
}