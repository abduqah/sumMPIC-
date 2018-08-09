/*
 * File:   test_3.cpp
 * Author: abdu
 *
 * Created on March 8, 2016, 1:06 PM
 */
#include <mpi.h>
#include <cstdlib>
/* Also include usual header files */
using namespace std;

int main(int argc, char **argv) {
    int myrank, size;
    int sum=0, vp, n,l;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    /* Initialise MPI */
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (myrank != 0) {
        MPI_Recv(&l, 1, MPI_INT, 0, 18, MPI_COMM_WORLD, &status);
        int arcopy1[l];
        int arcopy2[l];
        MPI_Recv(&arcopy1[0], l, MPI_INT, 0, 21, MPI_COMM_WORLD, &status);
        MPI_Recv(&arcopy2[0], l, MPI_INT, 0, 23, MPI_COMM_WORLD, &status);
        vp = 0;
        for (int i = 0; i < l; i++)
            vp += arcopy1[i]*arcopy2[i];
        MPI_Send(&vp, 1, MPI_INT, 0, 19, MPI_COMM_WORLD);
    } else {
        n = 100;
        l = (n/2)/size;
        for(int i =1; i < size; ++i)
        MPI_Send(&l, 1, MPI_INT, i, 18, MPI_COMM_WORLD);
        int ar[n];
        int v1[n / 2];
        int v2[n / 2];
        for (int i = 0; i < n; i++) {
        ar[i] = rand() % 100;
        }
        for(int i=0; i < n/2; i++){
            v1[i] = ar[i];
            v2[i] = ar[i+(n/2)];
        }
        for (int i = 0; i < l; i++)
            sum += v1[i]*v2[i];
        for (int i = 1; i < size; ++i) {
            MPI_Send(&v1[l * i], l, MPI_INT, i, 21, MPI_COMM_WORLD);
            MPI_Send(&v2[l * i], l, MPI_INT, i, 23, MPI_COMM_WORLD);
        }
        printf("%d\n", sum);
        for (int i = 1; i < size; ++i) {
            MPI_Recv(&vp, 1, MPI_INT, i, 19, MPI_COMM_WORLD, &status);
            printf("%d\n", vp);
            sum = sum + vp;
        }
        printf("%d\n", sum);
    }
    MPI_Finalize();
    /* Terminate MPI */
    return 0;
}