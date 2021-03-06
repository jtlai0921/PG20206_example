/*
 * win_regex2.cpp
 *
 * 「使用Managed C++來使用正規表現的範例」
 */
#using <mscorlib.dll>
#using <System.dll>

using namespace System;
using namespace System::Text;
using namespace System::Text::RegularExpressions;

int main()
{
	// 正規表現
	String *pattern = "=\\?ISO-2022-JP\\?B\\?(.+?)\\?=";

	// 搜尋對象字串
	String *src = "=?ISO-2022-JP?B?GyRCNEE7ekZ+JGolWCVDJUAkchsoQg==?= MIME =?ISO-2022-JP?B?hogehogefugafuga?=";

	MatchCollection *result;
	Regex *regex;

	try {
		regex = new Regex(pattern);
	} catch (ArgumentException *e) {
		Console::WriteLine("正規表現{0}為錯誤的寫法", pattern);
		Console::WriteLine(e);
		return 1;
	}

	/* 搜尋對象字串 */
	Console::WriteLine(String::Concat("搜尋對象字串:", src));

	/* 執行使用正規表現的搜尋工作 */
	result = regex->Matches(src);

	Console::WriteLine("符合數 {0}", __box(result->Count));

	for (int i = 0 ; i < result->Count ; i++) {
		Match *match = result->get_Item(i);
		GroupCollection *gc = match->Groups;

		Console::WriteLine("item[{0}]={1} �� {2}", 
				__box(i), result->get_Item(i), gc->get_Item(1));
	}

	return 0;
}


