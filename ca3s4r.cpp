#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void usage(char* arg1){
	printf("\nUsage: %s file_name [mode]\n", arg1);
	printf("Examples:\n\n");
	printf("%s password.txt\n", arg1);
	printf("%s extra_secure_password.txt --all\n\n", arg1);
	exit(0);
}

string getFileContents(string filePath){
	ifstream file;
	file.open(filePath, ios::in);
	string line;
	string contents;
	while (getline(file, line)){
		contents.append(line+"\n");
	}
	file.close();
	return contents;
}

const char getAlphabetLetter(const char letter, int offset){
	const char alph[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	if ((letter+0 > 64 && letter+0 < 91) || (letter+0 > 96 && letter+0 < 123)){
		bool isCapital = false;
		int letterNumber = letter+0;
		int alphabetPosition = -1;
		if (letter+0 > 64 && letter+0 < 91){
			isCapital = true;
			letterNumber += 32;
		}

		for (int i = 0; i < sizeof(alph); i++){
			if (alph[i] == (char)letterNumber){
				alphabetPosition = i;
			}
		}
		if (alphabetPosition >= offset){
			if (isCapital){
				return (char)((alph[alphabetPosition-offset])-32);
			} else {
				return alph[alphabetPosition-offset];
			}
		} else {
			int revOffset = abs(alphabetPosition - offset);
			if (isCapital){
				return (char)(alph[sizeof(alph)-revOffset]-32);
			} else {
				return alph[sizeof(alph)-revOffset];
			}
		}
	} else {
		return letter;
	}
}

string decrypt(string s, int amount, bool letterOnlyMode){
	string r;
	for (int i = 0; i < s.length(); i++){
		if (letterOnlyMode){
			r += getAlphabetLetter(s[i], amount);
		} else {
			r += (char)(s[i]-amount);
		}
	}
	return r;
}

int main(int argc, char* argv[]) {
	if (argc < 2){
		usage(argv[0]);
	} else {
		string fileContents = getFileContents(argv[1]);
		if (argc < 3){
			for (int i = 1; i < 51; i++){
				cout << i << "\n\n" << decrypt(fileContents, i, true) << "\n\n";
			}
		} else if (strncmp(argv[2], "--all", sizeof("--all")) == 0) {
			for (int i = 1; i < 51; i++){
				cout << i << "\n\n" << decrypt(fileContents, i, false) << "\n\n";
			}
		} else {
			for (int i = 1; i < 51; i++){
				cout << i << "\n\n" << decrypt(fileContents, i, true) << "\n\n";
			}
		}
	}
	return 0;
}
