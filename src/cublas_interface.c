#include <cublas_v2.h>
#include <cuda_runtime.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
void cublas_zgemm(const char transa, const char transb, 
                  const double complex  _alpha, const cuDoubleComplex *A, 
                  const cuDoubleComplex *B,  const double complex _beta,
                  cuDoubleComplex *C, const int lda) {
    cuDoubleComplex alpha = make_cuDoubleComplex(creal(_alpha), cimag(_alpha));
    cuDoubleComplex beta = make_cuDoubleComplex(creal(_beta), cimag(_beta));

    cublasHandle_t handle;
    cublasCreate(&handle);
    cuDoubleComplex *d_A, *d_B, *d_C;
    d_A = d_B = d_C = NULL;
    // 在 显存 中为将要计算的矩阵开辟空间
    cudaError_t cudaStatus;
    uint64_t size = lda*lda * sizeof(cuDoubleComplex);
    // uint64_t size = 1024;
    fprintf(stderr, "lda:%lld cuDoubleComplex:%lld all:%lld size:%lld \n",lda,sizeof(cuDoubleComplex),lda*lda * sizeof(cuDoubleComplex) ,size );
    cudaStatus = cudaMalloc (
        (void**)&d_A,    // 指向开辟的空间的指针
        size    //　需要开辟空间的字节数
    );

    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed for d_A. cudaStatus:%d\n",cudaStatus);
        return;
    }
    cudaStatus = cudaMalloc (
        (void**)&d_B,    
        size
    );
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed for d_B\n");
        cudaFree(d_A);
        return;
    }

    // 在 显存 中为将要存放运算结果的矩阵开辟空间
    cudaStatus = cudaMalloc (
        (void**)&d_C,
        size 
    );
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed for d_C\n");
        cudaFree(d_A);
        cudaFree(d_B);
        return;
    }

    fprintf(stderr, "memcpy \n");

    // cublasSetVector (
    //     lda*lda,    // 要存入显存的元素个数
    //     sizeof(float),    // 每个元素大小
    //     A,    // 主机端起始地址
    //     1,    // 连续元素之间的存储间隔
    //     d_A,    // GPU 端起始地址
    //     1    // 连续元素之间的存储间隔
    // );
    // cublasSetVector (
    //     ldb*ldb, 
    //     sizeof(float), 
    //     B, 
    //     1, 
    //     d_B, 
    //     1
    // );
    // Print matrix B
    // cuDoubleComplex* h_B = (cuDoubleComplex*)malloc(size);
    // cudaMemcpy(h_B, B, size, cudaMemcpyHostToDevice);
    // for (int i = 0; i < lda; i++) {
    //     for (int j = 0; j < lda; j++) {
    //         printf("(%f, %f) ", B[i * lda + j].x, B[i * lda + j].y);
    //     }
    //     printf("\n");
    // }
    // free(h_B);
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);
    
    // Print matrix d_A
    // cuDoubleComplex* h_B = (cuDoubleComplex*)malloc(size);
    // cudaMemcpy(h_B, d_B, size, cudaMemcpyDeviceToHost);
    // for (int i = 0; i < lda; i++) {
    //     for (int j = 0; j < lda; j++) {
    //         printf("(%f, %f) ", h_B[i * lda + j].x, h_B[i * lda + j].y);
    //     }
    //     printf("\n");
    // }
    // free(h_B);
    // 同步函数
    cudaThreadSynchronize();
    cublasOperation_t opA = (transa == 'N' || transa == 'n') ? CUBLAS_OP_N : CUBLAS_OP_T;
    cublasOperation_t opB = (transb == 'N' || transb == 'n') ? CUBLAS_OP_N : CUBLAS_OP_T;
    printf("cublasZgemm\n");
    cublasZgemm(handle, opA, opB, lda, lda, lda, &alpha, d_A, lda, d_B, lda, &beta, d_C, lda);
    printf("finished Zgemm\n");
    // cublasGetVector (
    //     ldc*ldc,    //  要取出元素的个数
    //     sizeof(float),    // 每个元素大小
    //     d_C,    // GPU 端起始地址
    //     1,    // 连续元素之间的存储间隔
    //     C,    // 主机端起始地址
    //     1    // 连续元素之间的存储间隔
    // );
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    cublasDestroy(handle);
}