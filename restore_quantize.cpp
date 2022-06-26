#include "restore_quantize.h"

#define  vec_un_short vector<unsigned short>
#define vec_un_long_long vector<unsigned long long>

restore_quantize_state state;



vector<unsigned short> restore_quantize_state:: unpacked_bits(vector<vector<vec_un_long_long > > packed_bits)
{
    int lines = packed_bits.size();
    int nbits = packed_bits[0].size();
    int block_size = packed_bits[0][0].size();

   // cout<<lines<<" "<<nbits<<" "<<block_size<<endl;
    int storage =64;

    vec_un_short out(lines*block_size*storage,0);

    unsigned short x;
    unsigned long long tem;
    int c=0;
    for(int line=0;line<lines;++line){
        for(int bit_in=0;bit_in<storage;++bit_in){
            for(int bit_out=0;bit_out<nbits;++bit_out){
               for(int index=0;index<block_size;++index){           
                    tem = packed_bits[line][bit_out][index];
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


void restore_quantize_state:: unpack_param(vector<tensors> packed_all_level,double scale0,double scale1, tensor packed_bits)
{
    vector<vector<vec_un_long_long> > packed_bit_3d;
   
    packed_bit_3d.push_back(packed_bits.data);
    //cout<<packed_bit_3d.size()<<endl;
    //vec_un_short packed_bits_up =
    state.unpacked_bits(packed_bit_3d);


}

void restore_quantize_state:: restore_state(vector<layer> layers){
    int num_layers = layers.size();

    printf("Num layers: %d\n", num_layers);
    for(int i=0; i<num_layers; i++){
        vector<tensors> packed_all_level = layers[i].packed_all_levels;
        double scale0 = layers[i].scale[0];
        double scale1 = layers[i].scale[1];
        tensor packed_bits = layers[i].packed_bits;
        
      
        //tuple<vector<tensors>,double, double, tensor > quantize = 
        state.unpack_param(packed_all_level,scale0,scale1,packed_bits);  


    }
}


void DataContainer::readInt(ifstream &in, int &x)
{
    in.read(reinterpret_cast<char *>(&x), sizeof(int));
}
void DataContainer::readLong(ifstream &in, unsigned long long &x)
{
    in.read(reinterpret_cast<char *>(&x), sizeof(unsigned long long));
}

void DataContainer::readDouble(ifstream &in, double &x)
{
    in.read(reinterpret_cast<char *>(&x), sizeof(double));
}

vector<layer> DataContainer::setData(ifstream &in)
{
    int num_of_layer;
    readInt(in, num_of_layer);

    vector<layer> layers(num_of_layer);
    for (unsigned int i = 0; i < num_of_layer; i++)
    {
        int quantize_len;
        readInt(in, quantize_len);

        tensors multiple_tensors;

        int all_quantize_len;
        readInt(in, all_quantize_len);

        for (unsigned int j = 0; j < all_quantize_len; ++j)
        {
            int tensor_len;
            readInt(in, tensor_len);

            tensor tensor_data;
            if (tensor_len == 0)
            {
                multiple_tensors.zero_tensor = true;
            }
            else
            {
                multiple_tensors.zero_tensor = false;
                for (unsigned int k = 0; k < tensor_len; ++k)
                {
                    int first_dimension;
                    readInt(in, first_dimension);
                    vector<vector<unsigned long long>> matrix;

                    for (unsigned int l = 0; l < first_dimension; ++l)
                    {
                        int second_dimension;
                        readInt(in, second_dimension);

                        vector<unsigned long long> v;
                        for (unsigned int m = 0; m < second_dimension; ++m)
                        {
                            unsigned long long val;
                            readLong(in, val);
                            v.push_back(val);
                        }
                        matrix.push_back(v);
                    }
                    tensor_data.data = matrix;
                }
                multiple_tensors.multi_tensor.push_back(tensor_data);
            }
            layers[i].packed_all_levels.push_back(multiple_tensors);
        }

        double scale0;
        readDouble(in, scale0);
        layers[i].scale[0] = scale0;

        double scale1;
        readDouble(in, scale1);
        layers[i].scale[1] = scale1;

        int packed_bits_first_dimension;
        readInt(in, packed_bits_first_dimension);

        vector<vector<unsigned long long>> matrix;
        for (unsigned int j = 0; j < packed_bits_first_dimension; ++j)
        {
            int packed_bits_second_dimension;
            readInt(in, packed_bits_second_dimension);

            vector<unsigned long long> v;
            for (unsigned int k = 0; k < packed_bits_second_dimension; ++k)
            {
                unsigned long long val;
                readLong(in, val);
                v.push_back(val);
            }
            matrix.push_back(v);
        }
        tensor tensor_data;
        tensor_data.data = matrix;

        layers[i].packed_bits = tensor_data;
    }

    // print(layers,num_of_layer);

    int float_len;
    readInt(in, float_len);

    for (unsigned int j = 0; j < float_len; ++j)
    {
        int float_first_dimension;
        readInt(in, float_first_dimension);

        vector<double> v;
        for (unsigned int k = 0; k < float_first_dimension; ++k)
        {
            double val;
            readDouble(in, val);
            v.push_back(val);
        }
        layers[j].bias = v;
    }
    return layers;
}

void DataContainer::display(layer Layer)
{
    //     tensors multiple_tensors;
    vector<tensors> all_quantize = Layer.packed_all_levels;
    int all_quantize_len = all_quantize.size();
    cout<<"Length of all_quantize :"<<all_quantize.size()<<endl;
    for (unsigned int j = 0; j < all_quantize_len; ++j)
    {
        if(all_quantize[j].zero_tensor){
            cout<<"None"<<endl;
            continue;
        }
        else
        {
            vector<tensor> Tensors = all_quantize[j].multi_tensor;
            int tensor_len = Tensors.size();
            for (unsigned int k = 0; k < tensor_len; ++k)
            {
                vector<vector<unsigned long long>> Tensor = Tensors[k].data;
                int tensor_len = Tensor.size();
                cout<<"packed_all_levels "<<j<<" "<<"Tensors "<<k<<" "<<endl; 
                for (unsigned int l = 0; l < tensor_len; ++l)
                {
                    vector<unsigned long long> first_dimension = Tensor[l];
                    int first_dimension_len = first_dimension.size();
                    for (unsigned int m = 0; m <first_dimension_len; ++m)
                    {
                        unsigned long long val =first_dimension[m];
                        cout << val << " ";
                    }
                    cout<<endl;
                }
                cout<<endl;  
            }   
        }
    }
    double scale0 =  Layer.scale[0];
    double scale1 =  Layer.scale[1];
    cout<<"Scale "<<endl;
    cout<<scale0<<" "<<scale1<<endl;

    vector<vector<unsigned long long> > packed_bits = Layer.packed_bits.data; 
    int packed_bits_len = packed_bits.size();

    cout<<"packed_bits val :"<<endl;
    cout<<packed_bits_len<<endl;
    for (unsigned int j = 0; j < packed_bits_len; ++j)
    {
        vector<unsigned long long> packed_bits_first_dimension =packed_bits[j];
        int first_dimension_len = packed_bits_first_dimension.size();
        cout<<first_dimension_len<<endl;
        for (unsigned int k = 0; k < first_dimension_len; ++k)
        {
            unsigned long long val = packed_bits_first_dimension[k];
            cout<<val<<" ";
        }
    }
    cout<<endl;


    vector<double> bias = Layer.bias;
    int bias_len = bias.size();

    for (unsigned int k = 0; k < bias_len; ++k)
    {
        double val= bias[k];
        cout<<val<<" ";
    } 
    cout<<endl;
}