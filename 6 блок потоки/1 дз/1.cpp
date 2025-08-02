#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

int cnt_cl = 0;
const int max_cl = 5;

void cl_thread() {
    while (cnt_cl < max_cl) {
        cnt_cl++;
        cout << "Клиент ПРИШЕЛ. Всего: " << cnt_cl << endl;
        this_thread::sleep_for(1000ms);
    }
}

void oper_thread() {
    while (true) {
        if (cnt_cl > 0) {
            cnt_cl--;
            cout << "Клиент ОБСЛУЖЕН. Всего: " << cnt_cl << endl;
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

    thread client(cl_thread);
    thread oper(oper_thread);

    client.join();
    oper.join();

    return 0;
}