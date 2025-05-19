#include <iostream>
#include <string>
using namespace std;

class Pyramid {
public:



    void print_pyramid(int* arr, int size) {
        for (int i = 0; i < size; i++) {
            if (i == 0){
                cout << i << " root " << arr[i] << endl;
            }
            else {
                int level = 0;
                int temp = i + 1;
                while (temp > 1) {
                    temp /= 2;
                    level++;
                }

                int parent_index = (i - 1) / 2;

                string type = (i % 2 == 1) ? " left  " : " right ";

                cout << level << type << "(" << arr[parent_index] << ") " << arr[i] << endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    int arr[] = { 1, 3, 6, 5, 9, 8 };
    int size = sizeof(arr) / sizeof(arr[0]);

    Pyramid a;

    a.print_pyramid(arr, size);

    return 0;
}

