/*
 * win_regex.cpp
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
	String *pattern = "C(#|\\+\\+|--)";
//	String *pattern = "C(#|++|--)";    // 錯誤的正規表現

	// 搜尋對象字串
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
		Console::WriteLine("正規表現{0}為錯誤的寫法", pattern);
		Console::WriteLine(e);
		return 1;
	}

	for (int i = 0 ; i < src->Length ; i++) {
		Console::Write("{0}", src[i]);

		if (regex->IsMatch(src[i])) {
			Console::WriteLine(" 找到符合字串");
		} else {
			Console::WriteLine("");
		}
	}

	return 0;
}

