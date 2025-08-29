#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <random>
#include <iomanip>
#include <mutex>
#include <sstream>

using namespace std;
using namespace std::chrono;

mutex cout_mutex;

void set_cursor_position(int row, int col) {
    cout << "\033[" << row << ";" << col << "H" << flush;
}

void clear_line(int row) {
    set_cursor_position(row, 1);
    cout << "\033[2K" << flush;
}

void print_at_position(int row, int col, const string& message) {
    lock_guard<mutex> lock(cout_mutex);
    set_cursor_position(row, col);
    cout << message << flush;
}

void calculation_thread(int thread_num, int calculation_length, 
                       atomic<int>& completed_threads, int row_position) {
    auto start_time = high_resolution_clock::now();
    thread::id thread_id = this_thread::get_id();
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(50, 200);
    
    const int bar_width = 50;
    
    for (int i = 0; i <= calculation_length; i++) {
        stringstream progress_bar;
        progress_bar << "Поток " << setw(2) << thread_num << " | ID: " << thread_id << " | [";
        
        int pos = bar_width * i / calculation_length;
        for (int j = 0; j < bar_width; j++) {
            if (j < pos) progress_bar << "=";
            else if (j == pos) progress_bar << ">";
            else progress_bar << " ";
        }
        
        progress_bar << "] " << setw(3) << (100 * i / calculation_length) << "%";
        
        print_at_position(row_position, 1, progress_bar.str());
        
        this_thread::sleep_for(milliseconds(dis(gen)));
    }
    
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    
    stringstream result;
    result << "Поток " << setw(2) << thread_num << " | ID: " << thread_id 
           << " | [";
    for (int j = 0; j < bar_width; j++) result << "=";
    result << "] 100% | Завершён за: " << duration.count() << " мс";
    
    print_at_position(row_position, 1, result.str());
    
    completed_threads++;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    const int num_threads = 5;
    const int calculation_length = 100;
    
    atomic<int> completed_threads(0);
    vector<thread> threads;
    
    cout << "\033[2J" << "\033[H";
    cout << "Запуск многопоточного расчёта..." << endl;
    cout << "Количество потоков: " << num_threads << endl;
    cout << "Длина расчёта: " << calculation_length << " шагов" << endl << endl;
    
    const int start_row = 5;
    
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(calculation_thread, i + 1, calculation_length, 
                           ref(completed_threads), start_row + i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    print_at_position(start_row + num_threads + 1, 1, "Все потоки завершили работу!");
    cout << endl;
    
    return 0;
}