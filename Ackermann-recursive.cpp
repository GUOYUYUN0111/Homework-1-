#include <iostream>
using namespace std;

int Ackermann(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return Ackermann(m - 1, 1);
    else
        return Ackermann(m - 1 , Ackermann(m , n - 1));
}

int main() {
    int m = 1;
    int n = 1;

    cout << "Ackermann(" << m << ", " << n << ") = " << Ackermann(m, n) << endl;
    return 0;
}
