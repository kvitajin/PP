
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <omp.h>
#include <cmath>
#include <random>
#include <vector>

# define M_PI           3.14159265358979323846

void  generateMatrix(std::vector<std::vector<int>> &matrix,int size){
    matrix.resize(size);
    for (int i = 0; i < size; ++i) {
        matrix[i].resize(size);
    }
    std::random_device rd;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j]=rd()%90+10;
        }
    }
}
void printMatrix(std::vector<std::vector<int>> &matrix){
    for (auto & i : matrix) {
        for (int j : i) {
            std::cout<<j<< " ";
        }
        std::cout<<"|" <<std::endl;
    }
}

std::vector<std::vector<int>> multiplyMatrix(std::vector<std::vector<int>> &matrixA,
                                             std::vector<std::vector<int>> &matrixB){
    std::vector<std::vector<int>> tmp = {{0}};

#pragma omp parallel shared (matrixA, matrixB, tmp)
    {
        tmp.resize(matrixA[0].size());
        for (auto &i : tmp) {
            i.resize(matrixB.size());
        }
#pragma omp  for schedule(static)
        for (int i = 0; i < matrixA.size(); i=i+1) {
            for (int j = 0; j < matrixB[i].size(); j=j+1) {
                for (int k = 0; k < matrixA[i].size(); k=k+1) {
                    tmp[i][j] = (tmp[i][j])+ (matrixA[i][k] * matrixB[k][j]);
                }

            }
        }

    }
        return tmp;

}

/* [i,k][k,j]
double** multiply(double* a, double** b) {
    double** c;
    for (int i = 0; ;) {
        for (int j = 0; ;) {
            for (int k = 0; ;) {
                c[i, j] += a[i*vel_radku+ k] * b[k, j];
            }
        }
    }
    return c;
}*/


int main(){
    std::vector<std::vector<int>> matrixA;
    std::vector<std::vector<int>> matrixB;
    std::vector<std::vector<int>> matrixC;

    generateMatrix(matrixA,20);
    generateMatrix(matrixB,20);

    printMatrix(matrixA);
    std::cout<<std::endl;

    printMatrix(matrixB);
    std::cout<<std::endl;

    matrixC=multiplyMatrix(matrixA, matrixB);
    printMatrix(matrixC);
//
//    omp_set_num_threads(4);
//
//    int all = 1;
//    for (int k = 0; k < 8; k++) {
//        all = all * 10;
//        int inside = 0;
//
//#pragma omp parallel
//        {
//            std::srand(std::time(0)+omp_get_thread_num());
//            int inner_count = 0;
//            int count_i = 0;
//#pragma omp  for
//            for (int i = 0; i < all; i++) {
//                double x = ((double)std::rand()) / RAND_MAX;
//                double y = ((double)std::rand()) / RAND_MAX;
//
//                if (sqrt(x * x + y * y) <= 1) {
//                    inner_count++;
//                }
//                count_i = i;
//            }
//#pragma omp critical
//            {
//                inside += inner_count;
//                printf("%d -> %d %d %d\n", omp_get_thread_num() , inner_count , all, count_i);
//            }
//        }
//        printf("%d %f %f\n", all, (double)inside / all * 4, M_PI);
//    }
//
//
//





}

