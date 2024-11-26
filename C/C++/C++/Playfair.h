#include <iostream>
#include <string>
#include <vector>
using namespace std;

string alphabet1="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
class Playfair {
	string mTable[25];
	string mPair;
	string mKey;
public:
	Playfair(string mKey, string mPair);
	void makeTable();
	void showTable();
    void findindex(char let,int& row,int& col);
	string makeEncryption(string mEncryption);
};

//"assasinator", "q/z"
Playfair::Playfair(string mKey, string mPair) {
	this->mKey = mKey;
    if (mPair[0]>mPair[2]){
        string tmp="";
        tmp[0]=mPair[0];//z a
        mPair[0]=mPair[2];
        mPair[2]=tmp[0];
    }
    for(int i=0;i<mPair.size();i++){
        mPair[i]=toupper(mPair[i]);
    }
	this->mPair = mPair;

}


void Playfair::makeTable() {
	// mKey와 mPair를 이용하여 mTable을 만드세요. (5 X 5 로 표현하시오)
    string str=this->mKey;
    string afterStr="";
    string afterPair="";
    string alphabet="";

    int check=0;

    for (int i=0;i<str.size();i++){
        str[i]=toupper(str[i]);
    }

    for (int i = 0; i <str.length(); i++) {
        check = 0; // 초기화: 중복 여부를 확인
        // 이미 afterStr에 존재하는지 확인
        for (int j = 0; j < afterStr.length(); j++) {
            if (afterStr[j] ==str[i]) {
                check = 1;
                break; // 중복 발견 시 중단
            }
        }
        // 중복되지 않고 조건에 부합하면 추가
        if (check == 0 && 
            alphabet1.find(str[i]) != string::npos && // alphabet1에 있는 문자인지 확인
            mPair.find(str[i]) == string::npos) {    // mPair에 없는 문자인지 확인
            afterStr.push_back(str[i]);
        }
    }
    // cout<<"afterstr:"+afterStr+"\n";

   for (int i = 0; i < alphabet1.size(); i++) {
    check = 0; // 초기화: 중복 여부를 확인

    // 이미 alphabet에 존재하는지 확인
    for (int j = 0; j < alphabet.size(); j++) {
        if (alphabet[j] == alphabet1[i]) {
            check = 1; // 중복 발견
            break; // 중복 발견 시 더 이상 확인하지 안함
        }
    }

    // 중복되지 않고 두 조건에 부합하면 추가
    if (check == 0 && 
        afterStr.find(alphabet1[i]) == string::npos)  // afterStr에 없는 문자인지 확인) 
        { 
        alphabet.push_back(alphabet1[i]); // 두 문자열 모두에 없으면 추가
    }
}
   
   
    this->mKey=afterStr;
    // cout<<"알파벳"+alphabet;

//테이블 구현부
int index=0;
    for (char ch : afterStr) {
        if (index < 25) {
            mTable[index++] = string(1, ch); // 한 글자씩 저장
        }
    }

    for (char ch : alphabet) {
    // 현재 문자를 문자열로 변환
    string currentChar(1, ch);

    // mPair의 첫 번째 단어와 같으면 mPair를 저장
    if (currentChar == mPair.substr(0, 1)) {
        mTable[index++] = mPair;
        continue; // 다음 문자로 넘어감
    }

    // mPair의 세 번째 자리와 같으면 해당 문자는 추가하지 안함
    if (mPair.length() >= 3 && currentChar == mPair.substr(2, 1)) {
        continue; // 아무 작업도 하지 않고 다음 문자로 넘어감
    }

    // 기본 동작: 한 글자씩 저장
    if (index < 25) {
        mTable[index++] = currentChar;
    } else {
        break; // 공간이 다 차면 종료
    }
}

}
void Playfair::findindex(char let, int& row, int& col) {
    // mTable 배열에서 문자의 위치를 찾아 행(row)과 열(col)을 계산
    if(mPair[2]==let){
        let=mPair[0];
    }
    for (int i = 0; i < 25; i++) { // mTable의 모든 요소를 순회
        if (mTable[i][0] == let) { // mTable[i]의 첫 문자가 찾는 문자와 같다면
            row = i / 5; // 5로 나눈 몫은 행 번호
            col = i % 5; // 5로 나눈 나머지는 열 번호
            return;      // 위치를 찾으면 함수 종료
        }
    }
    // 문자를 찾지 못하면 row와 col을 -1로 설정 (예외 처리)
    row = -1;
    col = -1;
}
void Playfair::showTable() {
	// mTable에 있는 값들을 5 X 5 로 화면에 출력하시오.
    cout << "mTable:" << endl;
    for(int j=0;j<5;j++){
        cout<<"\n";
        for (int i = 0; i < 5; i++) {
        cout  << mTable[5*j+i] +"\t";
    }
    }
    cout << endl;

}

string Playfair::makeEncryption(string mEncryption) {
    // 입력 문자열을 대문자로 변환
    for (size_t i = 0; i < mEncryption.size(); i++) {
        mEncryption[i] = toupper(mEncryption[i]);
    }

 bool completion = true;
    while (completion) {
        completion = false; // 기본적으로 반복 종료를 설정
        for (size_t i = 0; i + 1 < mEncryption.size(); i += 2) { // i+1이 범위를 초과하지 않도록 확인
            if (mEncryption[i] == mEncryption[i + 1]) {
                if (mEncryption[i] == 'X') { 
                    mEncryption.insert(i + 1, "Q"); // "X" 사이에 "Q" 삽입
                } else {
                    mEncryption.insert(i + 1, "X"); // 다른 경우 "X" 삽입
                }
                completion = true; // 삽입이 일어나면 루프를 다시 실행            // 삽입이 일어나면 루프를 다시 실행
                break;                         // 한 번 삽입 후 종료
            }
        }
    }

    // 문자열을 2글자씩 나누기 위해 필요한 배열 크기 계산

    size_t pairCount = (mEncryption.size() + 1) / 2; // 2글자씩 나눴을 때 필요한 쌍의 개수
    string str[pairCount]; // 배열 선언
    string strl[pairCount]; // 배열 선언


    // 문자열을 2글자씩 나누어 배열에 저장
    for (size_t i = 0, j = 0; i < mEncryption.size(); i += 2, j++) {
        if (i + 1 < mEncryption.size()) {
            // 2글자가 있는 경우 그대로 저장
            str[j] = mEncryption.substr(i, 2);
        } else {
            // 마지막 글자가 한 글자인 경우 뒤에 'X' 추가
            str[j] = mEncryption.substr(i, 1) + "X";
        }
    }

    // 2개의 단어씩 끊어서 확인하기
    // for (size_t i = 0; i < pairCount; i++) {
    //     cout << "str[" << i << "]: " << str[i] << endl;
    // }
    int col1,row1,col2,row2=0;
    mEncryption="";
    for(int i=0;i<pairCount;i++){
        findindex(str[i][0],row1,col1);
        findindex(str[i][1],row2,col2);
        // cout<<row1<<col1<<str[i][0]<<" 2번 ";
        // cout<<row2<<col2<<str[i][1]<<endl;

        if(row1==row2){
        if(mTable[((row2+1)%5)*5+col1]==mPair){
                mEncryption.append(1,mPair[0]);
        }
        else{
        mEncryption.append(mTable[((row2+1)%5)*5+col1]);
        }
        if(mTable[((row2+1)%5)*5+col2]==mPair){
                mEncryption.append(1,mPair[0]);
        }
        else{
        mEncryption.append(mTable[((row2+1)%5)*5+col2]);

        }
        }
        else if(col1==col2){
            if(mTable[row2*5+((col2+1)%5)]==mPair){
                mEncryption.append(1,mPair[0]);
            }
            else{
                mEncryption.append(mTable[row2*5+((col2+1)%5)]);
            }
            if(mTable[row1*5+((col2+1)%5)]==mPair){
                    mEncryption.append(1,mPair[0]);
            }
            else{
            mEncryption.append(mTable[row1*5+((col2+1)%5)]);
            }
        }
        else
        {
            if(mTable[row2*5+col1]==mPair){
                mEncryption.append(1,mPair[0]);
            }
            else{
                mEncryption.append(mTable[row2*5+col1]);

            }
            if(mTable[row1*5+col2]==mPair){
                mEncryption.append(1,mPair[0]);
                }
            else{
                mEncryption.append(mTable[row1*5+col2]);
            }
        }
        


        cout<<i<<": "<<mEncryption<<endl;


    }


    return "\n";
}
