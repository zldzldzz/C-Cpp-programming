#include <iostream>
using namespace std;

class Printer {
public:
    // int 타입의 변수를 출력하는 함수
    void print(int i) {
        cout << "Integer: " << i << endl;
    }

    // double 타입의 변수를 출력하는 함수
    void print(double d) {
        cout << "Double: " << d << endl;
    }

    // string 타입의 변수를 출력하는 함수
    void print(string s) {
        cout << "String: " << s << endl;
    }
};

int main() {
    Printer p;  // Printer 클래스의 객체 생성

    p.print(10);       // int 타입 출력
    p.print(3.14);     // double 타입 출력
    p.print("Hello");  // string 타입 출력

    return 0;
}