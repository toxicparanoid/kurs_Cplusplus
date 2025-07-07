#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    int n;
    cout << "[IN]: ";
    cin >> n;
    
    set<int, greater<int>> numbers;
    
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        numbers.insert(num);
    }
    
    cout << "[OUT]: " << endl;
    for (int num : numbers) {
        cout << num << endl;
    }
    
    return 0;
}