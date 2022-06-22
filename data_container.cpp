#include "data_container.h"

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
            layers[i].all_quantizes.push_back(multiple_tensors);
        }

        double scale0;
        readDouble(in, scale0);
        layers[i].scale[0] = scale0;

        double scale1;
        readDouble(in, scale1);
        layers[i].scale[1] = scale1;

        int packed_first_dimension;
        readInt(in, packed_first_dimension);

        vector<vector<unsigned long long>> matrix;
        for (unsigned int j = 0; j < packed_first_dimension; ++j)
        {
            int packed_second_dimension;
            readInt(in, packed_second_dimension);

            vector<unsigned long long> v;
            for (unsigned int k = 0; k < packed_second_dimension; ++k)
            {
                unsigned long long val;
                readLong(in, val);
                v.push_back(val);
            }
            matrix.push_back(v);
        }
        tensor tensor_data;
        tensor_data.data = matrix;

        layers[i].packed = tensor_data;
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
    vector<tensors> all_quantize = Layer.all_quantizes;
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
                cout<<"all_quantizes "<<j<<" "<<"Tensors "<<k<<" "<<endl; 
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

    vector<vector<unsigned long long> > Packed = Layer.packed.data; 
    int packed_len = Packed.size();

    cout<<"Packed val :"<<endl;
    cout<<packed_len<<endl;
    for (unsigned int j = 0; j < packed_len; ++j)
    {
        vector<unsigned long long> packed_first_dimension =Packed[j];
        int first_dimension_len = packed_first_dimension.size();
        cout<<first_dimension_len<<endl;
        for (unsigned int k = 0; k < first_dimension_len; ++k)
        {
            unsigned long long val = packed_first_dimension[k];
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