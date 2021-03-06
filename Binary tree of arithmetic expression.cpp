#include"Tree.h"
#include"Parser.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");

	char expression[100];
	cout << "Введите выражение: ";
	cin.getline(expression, 100);

	Parser p(expression);
	string result = p.parse();

	cout << "Префиксная запись: " << result << endl;
	stringstream str(result);
	Tree* BTree = makeTree(str);
	show(BTree);
	cout << "\n\n\n";
	bool mode = _setmode(_fileno(stdout), _O_U16TEXT);
	printBT(BTree);

	try {
		wcout << L"\nОтвет: " << calculate(BTree) << endl;
	}
	catch (const wchar_t* e) {
		wcout << e;
	}
	system("pause");
}