#include<stdio.h>
#include<cuda.h>
#define row1 500 
#define col1 500  
#define row2 500 
#define col2 500 

__global__ void matrix_multiply(int *l,int *m, int *n)
{
    int x=blockIdx.x;
    int y=blockIdx.y;
    int k;
  
n[col2*y+x]=0;
for(k=0;k<col1;k++)
   {
    n[col2*y+x]=n[col2*y+x]+l[col1*y+k]*m[col2*k+x];
   }
}

int main()
{
    int a[row1][col1];
    int b[row2][col2];
    int c[row1][col2];
    int *d,*e,*f;
    int i,j;

    for(i=0;i<row1;i++)
    {
        for(j=0;j<col1;j++)
            {
                a[i][j]=1;
            }
    }
    
        for(i=0;i<row2;i++)
        {
            for(j=0;j<col2;j++)
                {
                    b[i][j]=1;
                }
        }

    double time_spent = 0.0;
    clock_t begin = clock();
 
    cudaMalloc((void **)&d,row1*col1*sizeof(int));
    cudaMalloc((void **)&e,row2*col2*sizeof(int));
    cudaMalloc((void **)&f,row1*col2*sizeof(int));

 cudaMemcpy(d,a,row1*col1*sizeof(int),cudaMemcpyHostToDevice);
 cudaMemcpy(e,b,row2*col2*sizeof(int),cudaMemcpyHostToDevice);

dim3 grid(col2,row1);
    matrix_multiply<<<grid,1>>>(d,e,f);

 cudaMemcpy(c,f,row1*col2*sizeof(int),cudaMemcpyDeviceToHost);
 clock_t end = clock();

    cudaFree(d);
    cudaFree(e);
    cudaFree(f);
 
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds\n", time_spent);

    return 0;
}

