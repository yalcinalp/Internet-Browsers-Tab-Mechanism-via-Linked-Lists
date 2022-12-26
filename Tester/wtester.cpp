#include <iostream>
using namespace std;

int main() {
    const int tc = 200;
    int passed = 0;
    char compile[50], compare[50], expected[50], failure[50];

    for (int i = 1; i <= tc; ++i) {

        snprintf(compile, 50, "g++ -std=c++17 window_in/case%d.cpp", i);

        system(compile);
        
        system("./a.out > g.txt");

        snprintf(compare, 50, "cmp -s window_out/output%d.txt g.txt", i);

        if (!system(compare)) {
            ++passed;
            cout << "Case " << i << " PASSED.\n" << flush;
        } else {
            cout << "----------------------------------\n" << flush;
            cout << "Case " << i << " FAILED.\n" << std::flush;
            cout << "Given Output:\n" << flush;
            system("cat g.txt");
            cout << "Expected Output:\n" << flush;
            snprintf(failure, 50, "cat window_out/output%d.txt", i);
            system(failure);
            cout << "----------------------------------\n" << flush;
        }
    }

    system("rm -rf g.txt");

    cout << "Your grade is " << (static_cast<double>(passed)/tc)*100 << "/100 onii-chan.\n";

    return 0;
}
