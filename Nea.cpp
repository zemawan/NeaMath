#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

typedef std::vector<string> Vec;

int main(int argc, char* argv[]) {
	std::ofstream out;
	out.open("res.asm");

	string data = "format PE CONSOLE\ninclude 'include/win32ax.inc'\nentry start\n ;entry scane\nsection '.data' data  readable writeable\nx      dd 0\n";
	string code = "section '.code' code readable executable\nstart:\n";
	string idata = "section '.idata' import data readable writeable\n      library kernel,'KERNEL32.DLL', msvcrt, 'msvcrt.dll'\n     import kernel, ExitProcess,'ExitProcess'\n  import msvcrt,\\\n           printf,'printf',\\\n               system, 'system', \\\n               getch, '_getch', \\\n                    scanf, 'scanf'\n";

	data += "\n%";
	data += "d     db \"%";
	data += "d\", 0\n";

	string math;
	string buffer;
	string local;
	char a;
	getline(cin, math);

	math += "+0";
	Vec maths;
	maths.clear();

	for(int this_sym = 0; this_sym < math.length(); this_sym++) {
		a = math[this_sym];
			
		if(a == '+' || a == '-' || a == '*' || a == '/') {
			// cout << buffer << endl;

			maths.push_back(buffer);

			local += a;
			maths.push_back(local);
			local = "";

			buffer = "";
		} else if(a != ' ') {
			buffer += a;
		}
	}

	maths.push_back("0");

	int beginMode = 0;
	string num1 = "";
	string num2 = "";
	string operatorS = "";

	for (int i = 0; i < maths.size(); i++) {
		if(i == 0) {
			code += "\tadd [x], " + maths[i] + "\n";
		}

		// cout << maths[i] << endl;

		if(beginMode == 0) {
			num1 = maths[i];
		}

		if(beginMode == 1) {
			if(maths[i] == "+" || maths[i] == "-" || maths[i] == "*" || maths[i] == "/") {
				operatorS = maths[i];
			}
		}

		if(beginMode == 2) {
			num2 = maths[i];
		}

		beginMode += 1;

		if(beginMode == 3) {
			beginMode = 1;

			// cout << "0*" << endl;
			// cout << num1 << endl;
			// cout << "1*" << endl;
			// cout << num2 << endl;
			// cout << "2*" << endl;

			if(operatorS == "+") {
				code += "\tadd [x], " + num2 + "\n";
			} else if(operatorS == "-") {
				code += "\tsub [x], " + num2 + "\n";
			}
			// cout << operatorS << endl;
		}

		// cout << "New" << endl;
	}

	code += "\n\tinvoke printf, \"%";
	code += "d\", [x]\n";

	if(out.is_open()) {
		out << data + code + idata << endl;
	}

	out.close();

	cout << "asm file create" << endl;
	system("pause");
	
	return 0;
} 