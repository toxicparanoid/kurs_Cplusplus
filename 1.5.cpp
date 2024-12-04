#include<iostream>

int main(){
    setlocale(LC_ALL, "rus");
//-------------------------------------------------
    std::wcout << L"1 Задание: " << std::endl;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++){
        if (i == 9){
            std::cout << arr[i];
            break;
        }
        std::cout << arr[i] << ", ";
    }

    std::cout << std::endl << std::endl;;

//-------------------------------------------------
    std::wcout << L"2 Задание: " << std::endl;

    int ar[5] = {3, 8, 2, 15, 6};
    int min = 10000, max = 0;

    std::wcout << L"Массив: ";

    for (int i = 0; i < 5; i++) {
        std::cout << ar[i] << " ";
        if (ar[i] < min) {
            min = ar[i];
        }
        if (ar[i] > max) {
            max = ar[i];
        }

    }

    std::wcout << std::endl << L"Минимальный элемент: " << min << std::endl;
    std::wcout << L"Максимальный элемент: " << max << std::endl << std::endl;

//-------------------------------------------------
    std::wcout << L"3 Задание: " << std::endl;




    return 0;
}
