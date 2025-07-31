#include <iostream>
using namespace std;

int AckermannIterative(int m, int n) {
    const int MAX = 1000; // 根據需求可調整
    int mStack[MAX];
    int top = -1;

    mStack[++top] = m;

    while (top >= 0) {
        m = mStack[top--];

        if (m == 0)
            n = n + 1;
        else if (n == 0) {
            n = 1;
            mStack[++top] = m - 1;
        } else {
            mStack[++top] = m - 1;
            mStack[++top] = m;
            n = n - 1;
        }
    }
    return n;
}

int main() {
    int m = 1;
    int n = 1;

    cout << "Ackermann (non-recursive)(" << m << ", " << n << ") = " << AckermannIterative(m, n) << endl;
    return 0;
}
