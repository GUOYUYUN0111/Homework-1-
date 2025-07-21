```cpp
#include <iostream>
#include <stack>
using namespace std;

int AckermannIterative(int m, int n) {
    stack<int> stk;
    stk.push(m);

    while (!stk.empty()) {
        m = stk.top();
        stk.pop();

        if (m == 0)
            n = n + 1;
        else if (n == 0) {
            n = 1;
            stk.push(m - 1);
        } else {
            stk.push(m - 1);
            stk.push(m);
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
```