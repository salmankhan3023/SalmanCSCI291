#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

template <typename T>
void update_scale(T &m1, T &m2, T m3 = 10) {//function to update the values of m1 and m2
    T old_m1 = m1;
    T old_m2 = m2;
    m1 = (old_m1 + old_m2) * m3;
    m2 = (old_m1 - old_m2) * m3;
}

void print_real(float number, int fieldspace, int precision) {
    printf("%*.*f\n", fieldspace, precision, number); //function to print the numbers entered
}

int main(void) {
    float a, b;
    cout << "input two real numbers: "; //printed in terminal
    cin >> a >> b;//values for a and b taken

    print_real(a, 7, 3);//call function with value of a
    print_real(b, 7, 3);//call function with value of b

    // Call the function with the actual parameters a and b
    update_scale(a, b);

    print_real(a, 7, 3);
    print_real(b, 7, 3);

    return 0;
}

