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
		//���Ͽ���
		getFile();

		//����ڰ� �׳� ������ ���
		if (!input.is_open()) return;

		//�������� ���� ����
		output.open("new-" + inputFileName);

		//information offset
		input.getline(buffer, sizeof(buffer));
		input.getline(buffer, sizeof(buffer));
		while (input.getline(buffer, sizeof(buffer))) {

			//�����ϰ�� 2�� �ǳʶٱ�
			if (buffer[0] == 0 && buffer[10] == 0 && buffer[50] == 0 && buffer[100] == 0) {
				input.getline(buffer, sizeof(buffer));
				input.getline(buffer, sizeof(buffer));
				input.getline(buffer, sizeof(buffer));
			}

			//���� �ϳ��ϳ� �˻�
			for (int i = 0; buffer[i] != NULL; i++) {
				// < > �ȿ��ִ� ���� 0���� ��ó��
				if (buffer[i] == '<') {
					buffer[i] = '0';

					while (buffer[++i] != '>') buffer[i] = '-';

					buffer[i] = '-';
				}
				// [ ] �ȿ��ִ� ���� 0���� ��ó��
				if (buffer[i] == '[') {
					buffer[i] = '0';

					while (buffer[++i] != ']') buffer[i] = '0';

					buffer[i] = '0';
				}
			}

			//��ó���� buffer ���� result�� ���
			for (int i = 0, j = 0; buffer[i] != NULL; i++) {
				if (buffer[i] != '0') {
					result[j] = buffer[i];
					j++;
				}
				else
					if (buffer[i + 1] == NULL) result[j + 1] = NULL;
			}
			//����
			output << result << endl;

			//���� ����
			for (int i = 0; i < 150; i++) {
				buffer[i] = NULL;
				result[i] = NULL;
			}
		}
		//���� �ݱ�
		closeFile();

		//������
		if (isSuccessfullyFinished) cout << "�Ϸ�Ǿ����ϴ�!" << endl;
		else cout << "����ڿ� ���� ����Ǿ����ϴ�!" << endl;
	}

	void closeFile() {
		if (input.is_open()) input.close();
		if (output.is_open()) output.close();
	}

	void getFile() {
		cout << "���� �̸�.Ȯ���� �Է�: ";
		getline(cin, inputFileName);

		input.open(inputFileName);

		//������ ����, �ȿ����� ���Է� Ȥ�� ����
		if (!input.is_open()) {
			cout << inputFileName + "�� ã�� �� �����ϴ�. ���Է� �Ͻðڽ��ϱ�? (Y/N): ";

			//������ string ��Ȱ��
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