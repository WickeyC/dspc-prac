#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/sort.h>
#include <thrust/copy.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <algorithm>
#include <cstdlib>

int main(void)
{
    // generate 100 random numbers serially
    thrust::host_vector<int> h_vec(100);
    std::generate(h_vec.begin(), h_vec.end(), rand);

    // to save down original 100 random numbers
    thrust::host_vector<int> h_vec_ori = h_vec;

    // transfer data to the device
    thrust::device_vector<int> d_vec = h_vec;

    // sort data on the device 
    thrust::sort(d_vec.begin(), d_vec.end());

    //@@ transfer data back to host
    thrust::copy(d_vec.begin(), d_vec.end(), h_vec.begin());

    // print h_vec
    for (int i = 0; i < h_vec.size(); i++)
    {
        std::cout << "H_ORI[" << i << "] = " << h_vec_ori[i] 
        << " H[" << i << "] = " << h_vec[i] <<  std::endl;
    }


    return 0;
}
