#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <omp.h>
#include <iomanip>
using namespace std;

void vectorAdd(vector<double> a, vector<double> b, vector<double> c, int threads) {
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for
        for (auto i = 0; i < a.size(); i++) {
            c[i] = a[i] + b[i];
        }

    }


}

int main()
{
    setlocale(LC_ALL, "rus");

    int sizes[] = { 1000, 10000, 100000, 1000000 };
    int threads[] = { 2, 4, 8, 16 };

    int cores = omp_get_num_procs();
    cout << "Количество аппаратных ядер - " << cores << endl;

    cout << "Количество потоков\t" << "1000" << "\t" << "10000" << "\t"
        << "100000" << "\t" << "1000000" << endl;

    for (int t : threads) {
        cout << t << " потоков\t";
        for (int size : sizes) {

            vector<double> a(size, 1.0);
            vector<double> b(size, 2.0);
            vector<double> c(size);

            auto start = chrono::high_resolution_clock::now();
            vectorAdd(a, b, c, t);
            auto end = chrono::high_resolution_clock::now();
            double time_taken = chrono::duration<double, chrono::seconds::period>(end - start).count();

            cout << fixed << setprecision(8) << setw(12) << time_taken << "\t";
        }
        cout << endl;
    }

    return 0;
}