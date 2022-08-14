#include <time.h>
#include <stdlib.h>
#define N 10000
int **matrix;

int main(void) {
  srand(time(NULL));
  for (int i = 0; i < N; ++i) {
    // 申请内存空间
    matrix = (int **) malloc(sizeof(int *) * N);
    for (int j = 0; j < N; ++j) {
      matrix[j] = (int *) malloc(sizeof(int) * N);
    }
    // 尽量避免顺序访问数组，从而造成缺页
    for (int j = 0; j < N; ++j) {
      for (int k = N-1; k >= 0; --k) {
        matrix[k][j] = (i + j + k) * rand();  //随机产生数字写入
      }
    }
    for (int j = 0; j < N; ++j) {
      free(matrix[j]);
    }
    free(matrix);
  }
  return 0;
}