#include <iostream>
using namespace std;



int main() {
	char ch;
	while(true) {
		cin.get(ch); // �Էµ� Ű�� ch�� �����Ͽ� ����
		if(cin.eof()) break; // EOF�� ������ �б� ����
		cout.put(ch); // ch�� ���� ���
		if(ch == '\n')  
			break; // <Enter> Ű�� �ԷµǸ� �б� �ߴ�
	}

}
