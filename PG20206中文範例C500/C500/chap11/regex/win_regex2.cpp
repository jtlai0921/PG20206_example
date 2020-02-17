/*
 * win_regex2.cpp
 *
 * ¡u¨Ï¥ÎManaged C++¨Ó¨Ï¥Î¥¿³Wªí²{ªº½d¨Ò¡v
 */
#using <mscorlib.dll>
#using <System.dll>

using namespace System;
using namespace System::Text;
using namespace System::Text::RegularExpressions;

int main()
{
	// ¥¿³Wªí²{
	String *pattern = "=\\?ISO-2022-JP\\?B\\?(.+?)\\?=";

	// ·j´M¹ï¶H¦r¦ê
	String *src = "=?ISO-2022-JP?B?GyRCNEE7ekZ+JGolWCVDJUAkchsoQg==?= MIME =?ISO-2022-JP?B?hogehogefugafuga?=";

	MatchCollection *result;
	Regex *regex;

	try {
		regex = new Regex(pattern);
	} catch (ArgumentException *e) {
		Console::WriteLine("¥¿³Wªí²{{0}¬°¿ù»~ªº¼gªk", pattern);
		Console::WriteLine(e);
		return 1;
	}

	/* ·j´M¹ï¶H¦r¦ê */
	Console::WriteLine(String::Concat("·j´M¹ï¶H¦r¦ê:", src));

	/* °õ¦æ¨Ï¥Î¥¿³Wªí²{ªº·j´M¤u§@ */
	result = regex->Matches(src);

	Console::WriteLine("²Å¦X¼Æ {0}", __box(result->Count));

	for (int i = 0 ; i < result->Count ; i++) {
		Match *match = result->get_Item(i);
		GroupCollection *gc = match->Groups;

		Console::WriteLine("item[{0}]={1} ¨ {2}", 
				__box(i), result->get_Item(i), gc->get_Item(1));
	}

	return 0;
}


