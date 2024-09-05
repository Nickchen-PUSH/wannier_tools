source /mnt/lvm/intel/oneapi/setvars.sh

export LIBRARY_PATH=/mnt/lvm/group1/software/spack/opt/spack/linux-debian12-zen3/gcc-12.2.0/arpack-ng-3.9.0-3m56xyf5xnyxs3iqry2g7cbpgjawhs7l/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=/mnt/lvm/group1/software/spack/opt/spack/linux-debian12-zen3/gcc-12.2.0/arpack-ng-3.9.0-3m56xyf5xnyxs3iqry2g7cbpgjawhs7l/lib:$LD_LIBRARY_PATH
export CPATH=/mnt/lvm/group1/software/spack/opt/spack/linux-debian12-zen3/gcc-12.2.0/arpack-ng-3.9.0-3m56xyf5xnyxs3iqry2g7cbpgjawhs7l/include:$CPATH

export PATH=/usr/local/cuda/bin/:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib64/:$LD_LIBRARY_PATH
export CPATH=/usr/local/cuda/include/:$CPATH

# mpicc -o mpi_cublas_matrix_mul test.c -lcublas -lcudart -L/usr/local/cuda/lib64 -I/usr/local/cuda/include
