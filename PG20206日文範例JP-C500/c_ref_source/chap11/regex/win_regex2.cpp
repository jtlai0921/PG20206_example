/*
 * win_regex2.cpp
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
	String *pattern = "=\\?ISO-2022-JP\\?B\\?(.+?)\\?=";

	// �����Ώە�����
	String *src = "=?ISO-2022-JP?B?GyRCNEE7ekZ+JGolWCVDJUAkchsoQg==?= MIME =?ISO-2022-JP?B?hogehogefugafuga?=";

	MatchCollection *result;
	Regex *regex;

	try {
		regex = new Regex(pattern);
	} catch (ArgumentException *e) {
		Console::WriteLine("���K�\�� {0} ���s���ł�", pattern);
		Console::WriteLine(e);
		return 1;
	}

	/* �����Ώە����� */
	Console::WriteLine(String::Concat("�����Ώە�����F", src));

	/* ���K�\���ɂ�錟�������s */
	result = regex->Matches(src);

	Console::WriteLine("�}�b�`�� {0}", __box(result->Count));

	for (int i = 0 ; i < result->Count ; i++) {
		Match *match = result->get_Item(i);
		GroupCollection *gc = match->Groups;

		Console::WriteLine("item[{0}]={1} �� {2}", 
				__box(i), result->get_Item(i), gc->get_Item(1));
	}

	return 0;
}


