#include <bits/stdc++.h>

using namespace std;


int main()
{
    ifstream in{"weight_data_for_cpp.bin", ios::binary  | ios::in};
    if (!in)
    {
        printf("error opening");
    }
    else
    {
        int num_of_layer;
        in.read(reinterpret_cast<char*>(& num_of_layer),sizeof(int));

        cout<<"Number of layers: "<<num_of_layer<<endl;

        for(unsigned int i=0;i<num_of_layer;i++){
         //   if(i>5)break;
            int quantize_len;
            in.read(reinterpret_cast<char*>(&quantize_len),sizeof(int));
            cout<<"Layer :"<<i<<endl;
            int all_quantize_len;
            in.read(reinterpret_cast<char*>(&all_quantize_len),sizeof(int));
            cout<<"All Quantize len: "<<all_quantize_len<<endl;

            for(unsigned int j=0;j<all_quantize_len;++j){
                 int tensor_len;
                 in.read(reinterpret_cast<char*>(&tensor_len),sizeof(int));
                 cout<<"Tensor len: "<<tensor_len<<endl;

                if(tensor_len ==0)continue;
                else{
                    for(unsigned int k=0;k<tensor_len;++k){
                         int first_dimension;
                         in.read(reinterpret_cast<char*>(&first_dimension),sizeof(int));
                         cout<<"First dimension: "<<first_dimension<<endl;

                         for(unsigned int l=0;l<first_dimension;++l){
                            int second_dimension;
                            in.read(reinterpret_cast<char*>(&second_dimension),sizeof(int));
                            cout<<"Second dimension: "<<second_dimension<<endl;

                            for(unsigned int m=0;m<second_dimension;++m){
                                  long long val;
                                  in.read(reinterpret_cast<char*>(&val),sizeof(long long));
                                  //cout<<"Val: "<<val<<endl;
                            }
                         }
                    }
                }

            }

            double scale0;
            in.read(reinterpret_cast<char*>(&scale0),sizeof(double));
            cout<<"Scale0: "<<scale0<<endl;

            double scale1;
            in.read(reinterpret_cast<char*>(&scale1),sizeof(double));
            cout<<"Scale1: "<<scale1<<endl;


            int packed_first_dimension;
            in.read(reinterpret_cast<char*>(&packed_first_dimension),sizeof(int));
            cout<<"First dimension: "<<packed_first_dimension<<endl;

            for(unsigned int j=0;j<packed_first_dimension;++j){
                int packed_second_dimension;
                in.read(reinterpret_cast<char*>(&packed_second_dimension),sizeof(int));
                cout<<"First dimension: "<<packed_second_dimension<<endl;

                for(unsigned int k=0;k<packed_second_dimension;++k){
                      long long val;
                      in.read(reinterpret_cast<char*>(&val),sizeof(long long));
                      //cout<<"Val: "<<val<<endl;
                }
            }

        }

        int float_len;
        in.read(reinterpret_cast<char*>(&float_len),sizeof(int));
        cout<<"Float len: "<<float_len<<endl;

        for(unsigned int j=0;j<float_len;++j){
                int float_first_dimension;
                in.read(reinterpret_cast<char*>(&float_first_dimension),sizeof(int));
                cout<<"First dimension: "<<float_first_dimension<<endl;

                for(unsigned int k=0;k<float_first_dimension;++k){
                      double val;
                      in.read(reinterpret_cast<char*>(&val),sizeof(double));
                      //cout<<"Val: "<<val<<endl;
                }
        }
        
    }
}