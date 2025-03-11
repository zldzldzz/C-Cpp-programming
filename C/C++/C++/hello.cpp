#include <iostream>
using namespace std;



int main() {
	char ch;
	while(true) {
		cin.get(ch); // 입력된 키를 ch에 저장하여 리턴
		if(cin.eof()) break; // EOF를 만나면 읽기 종료
		cout.put(ch); // ch의 문자 출력
		if(ch == '\n')  
			break; // <Enter> 키가 입력되면 읽기 중단
	}

}
