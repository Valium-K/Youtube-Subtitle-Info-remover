#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class OnlyText {
public:
	OnlyText() {
		isSuccessfullyFinished = false;
	}

	void deInfomation() {
		//파일열기
		getFile();

		//사용자가 그냥 종료할 경우
		if (!input.is_open()) return;

		//쓰기위한 파일 열기
		output.open("new-" + inputFileName);

		//information offset
		input.getline(buffer, sizeof(buffer));
		input.getline(buffer, sizeof(buffer));
		while (input.getline(buffer, sizeof(buffer))) {

			//공백일경우 2둘 건너뛰기
			if (buffer[0] == 0 && buffer[10] == 0 && buffer[50] == 0 && buffer[100] == 0) {
				input.getline(buffer, sizeof(buffer));
				input.getline(buffer, sizeof(buffer));
				input.getline(buffer, sizeof(buffer));
			}

			//문자 하나하나 검사
			for (int i = 0; buffer[i] != NULL; i++) {
				// < > 안에있는 내용 0으로 전처리
				if (buffer[i] == '<') {
					buffer[i] = '0';

					while (buffer[++i] != '>') buffer[i] = '-';

					buffer[i] = '-';
				}
				// [ ] 안에있는 내용 0으로 전처리
				if (buffer[i] == '[') {
					buffer[i] = '0';

					while (buffer[++i] != ']') buffer[i] = '0';

					buffer[i] = '0';
				}
			}

			//전처리된 buffer 내용 result에 담기
			for (int i = 0, j = 0; buffer[i] != NULL; i++) {
				if (buffer[i] != '0') {
					result[j] = buffer[i];
					j++;
				}
				else
					if (buffer[i + 1] == NULL) result[j + 1] = NULL;
			}
			//쓰기
			output << result << endl;

			//버퍼 비우기
			for (int i = 0; i < 150; i++) {
				buffer[i] = NULL;
				result[i] = NULL;
			}
		}
		//파일 닫기
		closeFile();

		//결과출력
		if (isSuccessfullyFinished) cout << "완료되었습니다!" << endl;
		else cout << "사용자에 의해 종료되었습니다!" << endl;
	}

	void closeFile() {
		if (input.is_open()) input.close();
		if (output.is_open()) output.close();
	}

	void getFile() {
		cout << "파일 이름.확장자 입력: ";
		getline(cin, inputFileName);

		input.open(inputFileName);

		//열리면 실행, 안열리면 재입력 혹은 종료
		if (!input.is_open()) {
			cout << inputFileName + "을 찾을 수 없습니다. 재입력 하시겠습니까? (Y/N): ";

			//실패한 string 재활용
			getline(cin, inputFileName);

			if (inputFileName == "Y" || inputFileName == "y") {
				system("cls");
				getFile();
			}
			return;
		}
		isSuccessfullyFinished = true;
	}
private:
	ifstream input;
	ofstream output;
	string inputFileName;
	char buffer[200];
	char result[200];
	bool isSuccessfullyFinished;
};
int main()
{
	OnlyText ot;
	ot.deInfomation();
}