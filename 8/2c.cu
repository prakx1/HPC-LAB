#include<iostream>
#include<cuda.h>
using namespace std;

__global__ void staticmultiply(int *x, int n)
{
  __shared__ int tmp[64];
  int index = threadIdx.x;
  tmp[index] = x[index]*100;
  __syncthreads();
  x[index] = tmp[index];
}

__global__ void dynamicmultiply(int *x, int n)
{
  extern __shared__ int tmp[];
  int index = threadIdx.x;
  tmp[index] = x[index]*100;
  __syncthreads();
  x[index] = tmp[index];
}

int main(void)
{
  const int n=10;
  cout<<"Elements in array:";
  
  int a[n],x[n];

  for (int i = 0; i < n; i++) {
    a[i]=i;
  }

  int *arr;
  cudaMalloc(&arr, n * sizeof(int)); 

 
  cudaMemcpy(arr, a, n*sizeof(int), cudaMemcpyHostToDevice);
  staticmultiply<<<1,n>>>(arr, n);
  cudaMemcpy(x, arr, n*sizeof(int), cudaMemcpyDeviceToHost);
  for (int i = 0; i < n; i++) 
    {
      cout<<x[i]<<" ";
    }
  cout<<"\n";
 
  cudaMemcpy(arr, a, n*sizeof(int), cudaMemcpyHostToDevice);
  dynamicmultiply<<<1,n,n*sizeof(int)>>>(arr, n);
  cudaMemcpy(x, arr, n * sizeof(int), cudaMemcpyDeviceToHost);
  for (int i = 0; i < n; i++) 
    {
      cout<<x[i]<<" ";
    }
  cout<<"\n";
  return 0;
}
