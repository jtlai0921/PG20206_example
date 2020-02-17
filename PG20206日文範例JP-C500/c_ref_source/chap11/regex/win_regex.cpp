/*
 * win_regex.cpp
 *
 * �uManaged C++�ɂ�鐳�K�\���̗��p��v
 */
#using <mscorlib.dll>
#using <System.dll>

using namespace System;
using namespace System::Text;
using namespace System::Text::RegularExpressions;

int main()
{
	// ���K�\��
	String *pattern = "C(#|\\+\\+|--)";
//	String *pattern = "C(#|++|--)";    // �s���Ȑ��K�\��

	// �����Ώە�����
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
		Console::WriteLine("���K�\�� {0} ���s���ł�", pattern);
		Console::WriteLine(e);
		return 1;
	}

	for (int i = 0 ; i < src->Length ; i++) {
		Console::Write("{0}", src[i]);

		if (regex->IsMatch(src[i])) {
			Console::WriteLine(" �}�b�`���܂���");
		} else {
			Console::WriteLine("");
		}
	}

	return 0;
}

