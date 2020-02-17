/*
 * win_regex2.cpp
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
	String *pattern = "=\\?ISO-2022-JP\\?B\\?(.+?)\\?=";

	// �j�M��H�r��
	String *src = "=?ISO-2022-JP?B?GyRCNEE7ekZ+JGolWCVDJUAkchsoQg==?= MIME =?ISO-2022-JP?B?hogehogefugafuga?=";

	MatchCollection *result;
	Regex *regex;

	try {
		regex = new Regex(pattern);
	} catch (ArgumentException *e) {
		Console::WriteLine("���W��{{0}�����~���g�k", pattern);
		Console::WriteLine(e);
		return 1;
	}

	/* �j�M��H�r�� */
	Console::WriteLine(String::Concat("�j�M��H�r��:", src));

	/* ����ϥΥ��W��{���j�M�u�@ */
	result = regex->Matches(src);

	Console::WriteLine("�ŦX�� {0}", __box(result->Count));

	for (int i = 0 ; i < result->Count ; i++) {
		Match *match = result->get_Item(i);
		GroupCollection *gc = match->Groups;

		Console::WriteLine("item[{0}]={1} �� {2}", 
				__box(i), result->get_Item(i), gc->get_Item(1));
	}

	return 0;
}


