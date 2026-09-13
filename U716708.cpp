#include <iostream>
using namespace std;

int main() {
    int a,b;
    cin >> a >> b;
    int mx = a > b ? a : b;
    cout << mx << endl;
    return 0;
}