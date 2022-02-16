#include <Windows.h>
#include <fstream>
#include <iostream>
#include <iomanip>

const int THREADS = 8;
const int N = 1024;
const int DATA_SIZE = N / THREADS;
const char* MATRIX_A_FILE = "M1024A.txt";
const char* MATRIX_B_FILE = "M1024B.txt";
const char* RESULT_FILE = "1927405160.txt";

/* global variables */
double matrix_a[N][N];
double matrix_b[N][N];
double result[N][N];

struct THR_FUNC_PARAM {
    int a_start; 
    int a_end; 
    int b_start; 
    int b_end;
};

/* thread function */
DWORD thr_func_calc(LPVOID IpParam) {
    //  args *arg = (args *) _arg;
    THR_FUNC_PARAM* pmd = (THR_FUNC_PARAM*) IpParam;
    int i, j, k;
    for (i = pmd->a_start; i < pmd->a_end; ++i) {
        for (j = pmd->b_start; j < pmd->b_end; ++j) {
            result[i][j] = 0;
            for (k = 0; k < N; ++k) {
                result[i][j] += matrix_a[i][k] * matrix_b[j][k];
            }
        }
    }
    return 0;
}

DWORD thr_read_matrix_A() {
    int i, j;
    double number;
    std::ifstream fin(MATRIX_A_FILE);
    if (!fin.is_open()) {
        std::cerr << "can't read file:" << MATRIX_A_FILE << '\n';
        return 1;
    }
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            fin >> number;
            matrix_a[i][j] = number;
        }
    }
    fin.close();
    return 0;
}

DWORD thr_read_matrix_B() {
    int i, j;
    double number;
    std::ifstream fin(MATRIX_B_FILE);
    if (!fin.is_open()) {
        std::cerr << "can't read file:" << MATRIX_B_FILE << '\n';
        return 1;
    }
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            fin >> number;
            matrix_b[j][i] = number;
        }
    }
    fin.close();
    return 0;
}

int write_matrix(const char* file_name, double matrix[N][N]) {
    int i, j;
    std::ofstream out(file_name, std::ios::out);
    if (!out.is_open()) {
        std::cerr << "can't write file:" << file_name << '\n';
        return 1;
    }
    out << std::setiosflags(std::ios::fixed);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            out << matrix[i][j] << ' ';
        }
        out << '\n';
    }
    out.close();
    return 0;
}

int read_matrix() {
    HANDLE hThread[2];
    hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr_read_matrix_A, NULL, 0, NULL);
    hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr_read_matrix_B, NULL, 0, NULL);;
    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
    return 0;
}

THR_FUNC_PARAM params[THREADS];

int main() {
    std::ios::sync_with_stdio(false);
    int i, start, end;
    /* read matrix a and b */
    read_matrix();

    /* create threads */
    HANDLE threads[THREADS];
    for (i = 0; i < THREADS / 2; ++i) {
        // 2 * i , 2 * i + 1
        start = i * DATA_SIZE * 2;
        end = (i + 1) * DATA_SIZE * 2;
        params[2 * i].a_start = start;
        params[2 * i].a_end = end;
        params[2 * i].b_start = 0;
        params[2 * i].b_end = N / 2;
        params[2 * i + 1].a_start = start;
        params[2 * i + 1].a_end = end;
        params[2 * i + 1].b_start = N / 2;
        params[2 * i + 1].b_end = N;
        threads[2 * i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr_func_calc, &params[2 * i], 0, NULL);
        threads[2 * i + 1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr_func_calc, &params[2 * i + 1], 0, NULL);
    }

    /* join threads */
    WaitForMultipleObjects(THREADS, threads, TRUE, INFINITE);

    /* write result */
    write_matrix(RESULT_FILE, result);
    return 0;
}

