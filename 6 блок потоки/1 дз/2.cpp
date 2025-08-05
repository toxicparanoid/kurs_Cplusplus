#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <iomanip>

using namespace std;

void vectorAddPart(const vector<double>& a, const vector<double>& b, vector<double>& c, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        c[i] = a[i] + b[i];
    }
}

void vectorAdd(const vector<double>& a, const vector<double>& b, vector<double>& c, int threads) {
    vector<thread> thread_pool;
    size_t size = a.size();
    size_t chunk_size = size / threads;

    for (int i = 0; i < threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == threads - 1) ? size : start + chunk_size;
        thread_pool.emplace_back(vectorAddPart, ref(a), ref(b), ref(c), start, end);
    }

    for (auto& t : thread_pool) {
        t.join();
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    int sizes[] = { 1000, 10000, 100000, 1000000 };
    int threads[] = { 2, 4, 8, 16 };

    int cores = thread::hardware_concurrency();
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