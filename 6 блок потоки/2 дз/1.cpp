#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

atomic<int> cnt_cl(0);
const int max_cl = 5;

// версия с упорядочением memory_order_relaxed
void cl_thread_relaxed() {
    while (cnt_cl.load(memory_order_relaxed) < max_cl) {
        int current = cnt_cl.load(memory_order_relaxed);
        cnt_cl.store(current + 1, memory_order_relaxed);
        cout << "Клиент ПРИШЕЛ (relaxed). Всего: " << cnt_cl.load(memory_order_relaxed) << endl;
        this_thread::sleep_for(1000ms);
    }
}

// версия с упорядочением memory_order_acquire/release
void cl_thread_acquire_release() {
    while (cnt_cl.load(memory_order_acquire) < max_cl) {
        int current = cnt_cl.load(memory_order_acquire);
        cnt_cl.store(current + 1, memory_order_release);
        cout << "Клиент ПРИШЕЛ (acquire/release). Всего: " << cnt_cl.load(memory_order_acquire) << endl;
        this_thread::sleep_for(1000ms);
    }
}

// версия с упорядочением memory_order_seq_cst
void cl_thread_seq_cst() {
    while (cnt_cl.load(memory_order_seq_cst) < max_cl) {
        int current = cnt_cl.load(memory_order_seq_cst);
        cnt_cl.store(current + 1, memory_order_seq_cst);
        cout << "Клиент ПРИШЕЛ (seq_cst). Всего: " << cnt_cl.load(memory_order_seq_cst) << endl;
        this_thread::sleep_for(1000ms);
    }
}

void oper_thread_relaxed() {
    while (true) {
        int current = cnt_cl.load(memory_order_relaxed);
        if (current > 0) {
            cnt_cl.store(current - 1, memory_order_relaxed);
            cout << "Клиент ОБСЛУЖЕН (relaxed). Всего: " << cnt_cl.load(memory_order_relaxed) << endl;
        }
        else {
            break;
        }
        this_thread::sleep_for(2000ms);
    }
}

void oper_thread_acquire_release() {
    while (true) {
        int current = cnt_cl.load(memory_order_acquire);
        if (current > 0) {
            cnt_cl.store(current - 1, memory_order_release);
            cout << "Клиент ОБСЛУЖЕН (acquire/release). Всего: " << cnt_cl.load(memory_order_acquire) << endl;
        }
        else {
            break;
        }
        this_thread::sleep_for(2000ms);
    }
}

void oper_thread_seq_cst() {
    while (true) {
        int current = cnt_cl.load(memory_order_seq_cst);
        if (current > 0) {
            cnt_cl.store(current - 1, memory_order_seq_cst);
            cout << "Клиент ОБСЛУЖЕН (seq_cst). Всего: " << cnt_cl.load(memory_order_seq_cst) << endl;
        }
        else {
            break;
        }
        this_thread::sleep_for(2000ms);
    }
}

// функция для тестирования с использованием fetch_add/fetch_sub
void cl_thread_fetch() {
    while (cnt_cl.load() < max_cl) {
        int new_val = cnt_cl.fetch_add(1) + 1;
        cout << "Клиент ПРИШЕЛ (fetch_add). Всего: " << new_val << endl;
        this_thread::sleep_for(1000ms);
    }
}

void oper_thread_fetch() {
    while (true) {
        int current = cnt_cl.load();
        if (current > 0) {
            int new_val = cnt_cl.fetch_sub(1) - 1;
            cout << "Клиент ОБСЛУЖЕН (fetch_sub). Всего: " << new_val << endl;
        }
        else {
            break;
        }
        this_thread::sleep_for(2000ms);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "=== Тест 1: memory_order_relaxed ===" << endl;
    cnt_cl = 0;
    thread client1(cl_thread_relaxed);
    thread oper1(oper_thread_relaxed);
    client1.join();
    oper1.join();

    cout << "\n=== Тест 2: memory_order_acquire/release ===" << endl;
    cnt_cl = 0;
    thread client2(cl_thread_acquire_release);
    thread oper2(oper_thread_acquire_release);
    client2.join();
    oper2.join();

    cout << "\n=== Тест 3: memory_order_seq_cst ===" << endl;
    cnt_cl = 0;
    thread client3(cl_thread_seq_cst);
    thread oper3(oper_thread_seq_cst);
    client3.join();
    oper3.join();

    cout << "\n=== Тест 4: fetch_add/fetch_sub ===" << endl;
    cnt_cl = 0;
    thread client4(cl_thread_fetch);
    thread oper4(oper_thread_fetch);
    client4.join();
    oper4.join();

    return 0;
}