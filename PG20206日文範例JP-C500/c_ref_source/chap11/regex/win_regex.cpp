/*
 * win_regex.cpp
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
	String *pattern = "C(#|\\+\\+|--)";
//	String *pattern = "C(#|++|--)";    // 不正な正規表現

	// 検索対象文字列
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
		Console::WriteLine("正規表現 {0} が不正です", pattern);
		Console::WriteLine(e);
		return 1;
	}

	for (int i = 0 ; i < src->Length ; i++) {
		Console::Write("{0}", src[i]);

		if (regex->IsMatch(src[i])) {
			Console::WriteLine(" マッチしました");
		} else {
			Console::WriteLine("");
		}
	}

	return 0;
}

