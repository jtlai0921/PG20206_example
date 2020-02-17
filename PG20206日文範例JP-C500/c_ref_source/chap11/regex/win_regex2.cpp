/*
 * win_regex2.cpp
 *
 * 「Managed C++による正規表現の利用例」
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

	// 検索対象文字列
	String *src = "=?ISO-2022-JP?B?GyRCNEE7ekZ+JGolWCVDJUAkchsoQg==?= MIME =?ISO-2022-JP?B?hogehogefugafuga?=";

	MatchCollection *result;
	Regex *regex;

	try {
		regex = new Regex(pattern);
	} catch (ArgumentException *e) {
		Console::WriteLine("正規表現 {0} が不正です", pattern);
		Console::WriteLine(e);
		return 1;
	}

	/* 検索対象文字列 */
	Console::WriteLine(String::Concat("検索対象文字列：", src));

	/* 正規表現による検索を実行 */
	result = regex->Matches(src);

	Console::WriteLine("マッチ数 {0}", __box(result->Count));

	for (int i = 0 ; i < result->Count ; i++) {
		Match *match = result->get_Item(i);
		GroupCollection *gc = match->Groups;

		Console::WriteLine("item[{0}]={1} → {2}", 
				__box(i), result->get_Item(i), gc->get_Item(1));
	}

	return 0;
}


