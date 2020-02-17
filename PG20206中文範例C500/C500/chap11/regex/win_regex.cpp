/*
 * win_regex.cpp
 *
 * �u�ϥ�Managed C++�ӨϥΥ��W��{���d�ҡv
 */
#using <mscorlib.dll>
#using <System.dll>

using namespace System;
using namespace System::Text;
using namespace System::Text::RegularExpressions;

int main()
{
	// ���W��{
	String *pattern = "C(#|\\+\\+|--)";
//	String *pattern = "C(#|++|--)";    // ���~�����W��{

	// �j�M��H�r��
	String *src[] = {
		"C# World",
		"Java World",
		"C++ World",
		"F# World",
	};
	Regex *regex;

	try {
		regex = new Regex(pattern);
	} catch (ArgumentException *e) {
		Console::WriteLine("���W��{{0}�����~���g�k", pattern);
		Console::WriteLine(e);
		return 1;
	}

	for (int i = 0 ; i < src->Length ; i++) {
		Console::Write("{0}", src[i]);

		if (regex->IsMatch(src[i])) {
			Console::WriteLine(" ���ŦX�r��");
		} else {
			Console::WriteLine("");
		}
	}

	return 0;
}

