#include <iostream>
#include "my_header.h"

#define PI 3.14159
using namespace std;

class Circle {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() {
        return PI * radius * radius;
    }
};

int main() {
    Circle c1(5.0);
    cout << "Area of the circle: " << c1.area() << endl;

    // Testăm operatorii logici și matematici
    int a = 10, b = 20;
    if (a < b && b != 0) {
        cout << "b is greater than a" << endl;
    }

    // Testăm pointeri și alocare dinamică
    int *ptr = new int(25);
    cout << "Pointer value: " << *ptr << endl;
    delete ptr;

    // Testăm un switch-case
    char grade = 'B';
    switch (grade) {
        case 'A':
            cout << "Excellent!" << endl;
            break;
        case 'B':
            cout << "Good job!" << endl;
            break;
        case 'C':
            cout << "You passed." << endl;
            break;
        default:
            cout << "Invalid grade" << endl;
    }

    // Testăm un șir de caractere multi-linie
    string message = "Aceasta este o propoziție \
                      pe mai multe linii.";
    cout << message << endl;

    return 0;
}
