#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;

	cout << "문자열 입력" << endl;
	getline(cin, s, '\n');
	int len = s.length();

	for(int i = 0; i < len; i++) {
		string first = s.substr(0, len-1);
		string last = s.substr(len-1,len);
		s = last + first;
		cout << s << endl;
	}
}