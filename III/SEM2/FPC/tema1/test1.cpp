#include <iostream>
#include <cmath>
#include "my_header.h"

#define PI 3.14159
using namespace std;

/*nnm
jjk
*/

class Shape {
protected:
    double area;
public:
    Shape() : area(0) {}
    virtual void computeArea() = 0; // Funcție pur virtuală
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    void computeArea() override {
        area = PI * radius * radius;
    }
    void display() {
        cout << "Circle area: " << area << endl;
    }
};

int main() {
    Circle c1(5.0);
    c1.computeArea();
    c1.display();

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

    // ---------- ERORI LEXICALE ----------
    int 123abc = 10; // Invalid: începe cu cifră
    @specialChar = 50; // Invalid: @ nu este permis în identificatori
    string broken = "String fără închidere;
    float num = 3.14.15; // Invalid: două puncte zecimale
    
    return 0;
}

