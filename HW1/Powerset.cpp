#include <iostream>
#include <string>
using namespace std;

void generatePowerSet(char set[], int n, int index, string current) {
    if (index == n) {
        if (current.empty())
            cout << "{}" << endl;
        else
            cout << "{ " << current << "}" << endl;
        return;
    }


    generatePowerSet(set, n, index + 1, current);

    generatePowerSet(set, n, index + 1, current + set[index] + " ");
}

int main() {
    char S[] = {'a', 'b', 'c'};
    int size = 3;

    cout << "Power Set of {a, b, c}:" << endl;
    generatePowerSet(S, size, 0, "");

    return 0;
}
