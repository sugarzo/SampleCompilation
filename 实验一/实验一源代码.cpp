#include <fstream>
#include <iostream>
#include <stdlib.h>
#include<map>
#include<list>
using namespace std;

map<string, int> sampleDictionary;
map<string, int> Store_Identifier;
map<string, int> Store_String;
map<string, int> Store_Int;
int total_Count = 0;

//二元组
struct DoubleGroup {
	int a;
	int b;
	string Word;
	DoubleGroup(string w,int x = 0, int y = 0)
	{
		Word = w;
		a = x;
		b = y;
	}
};
list<DoubleGroup> PrintList;
void sampleDictionaryInit()
{
	sampleDictionary["and"] = 1;
	sampleDictionary["array"] = 2;
	sampleDictionary["begin"] = 3;
	sampleDictionary["bool"] = 4;
	sampleDictionary["call"] = 5;
	sampleDictionary["case"] = 6;
	sampleDictionary["char"] = 7;
	sampleDictionary["constant"] = 8;
	sampleDictionary["dim"] = 9;
	sampleDictionary["do"] = 10;
	sampleDictionary["else"] = 11;
	sampleDictionary["end"] = 12;
	sampleDictionary["false"] = 13;
	sampleDictionary["for"] = 14;
	sampleDictionary["if"] = 15;
	sampleDictionary["input"] = 16;
	sampleDictionary["integer"] = 17;
	sampleDictionary["not"] = 18;
	sampleDictionary["of"] = 19;
	sampleDictionary["or"] = 20;
	sampleDictionary["output"] = 21;
	sampleDictionary["procedure"] = 22;
	sampleDictionary["program"] = 23;
	sampleDictionary["read"] = 24;
	sampleDictionary["real"] = 25;
	sampleDictionary["repeat"] = 26;
	sampleDictionary["set"] = 27;
	sampleDictionary["stop"] = 28;
	sampleDictionary["then"] = 29;
	sampleDictionary["to"] = 30;
	sampleDictionary["true"] = 31;
	sampleDictionary["until"] = 32;
	sampleDictionary["var"] = 33;
	sampleDictionary["while"] = 34;
	sampleDictionary["write"] = 35;
	//sampleDictionary[""] = 36;
	//sampleDictionary[""] = 37;
	//sampleDictionary[""] = 38;
	sampleDictionary["("] = 39;
	sampleDictionary[")"] = 40;
	sampleDictionary["*"] = 41;
	sampleDictionary["*/"] = 42;
	sampleDictionary["+"] = 43;
	sampleDictionary[","] = 44;
	sampleDictionary["-"] = 45;
	sampleDictionary["."] = 46;
	sampleDictionary[".."] = 47;
	sampleDictionary["/"] = 48;
	sampleDictionary["/*"] = 49;
	sampleDictionary[":"] = 50;
	sampleDictionary[":="] = 51;
	sampleDictionary[";"] = 52;
	sampleDictionary["<"] = 53;
	sampleDictionary["<="] = 54;
	sampleDictionary["<>"] = 55;
	sampleDictionary["="] = 56;
	sampleDictionary[">"] = 57;
	sampleDictionary[">="] = 58;
	sampleDictionary["["] = 59;
	sampleDictionary["]"] = 60;
	return;
}
/// <summary>
/// 输出二元组
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
void printDoubleGroup(int a, int b = 0)
{
	if (b == 0)
		cout << "(" << a << ",-)\t";
	else
		cout << "(" << a << "," << b << ")\t";
	//cout << endl;
}
void printAll()
{
	int tot = 5;
	while (!PrintList.empty())
	{
		printDoubleGroup(PrintList.front().a, PrintList.front().b);
		PrintList.pop_front();
		if (--tot == 0)
		{
			cout << endl;
			tot = 5;
		}
	}
}

string ToString(char* a, char* b)
{
	string ret ="";
	//if (*a == '\0') return ret;
	int tot = 0;
	while (a != b)
	{
		ret += *a;
		a++;
		tot++;
		if (tot > 100)
		{
			cout << "Tostring函数未成功返回，可能错误引用了*a,*b\n";
			break;
		}
	}
	ret += *a;

	return ret;
}
string ToString(char a)
{
	string ret = "";
	ret += a;
	return ret;
}

class sampleAnalyze {
private:
	string text;
	ifstream fin;
	int lp; //左指针
	int rp; //右指针
	int currRow; //当前行数
	void (sampleAnalyze::*currState)(); //当前状态
public:
	string readWord();
	void FSM();
	void DefaultState();
	/// <summary>
	/// 注释状态
	/// </summary>
	void IState(); 
	/// <summary>
	/// 字符串判定状态
	/// </summary>
	void CState();

	bool isKeyWord(string input) //是 关键字
	{
		if (sampleDictionary[input])
		{
			if (sampleDictionary[input] >= 1 && sampleDictionary[input] <= 35)
				return true;
		}
		return false;
	}
	bool isNum(char Input) //是 数字
	{
		if (Input >= '0' && Input <= '9')
			return true;
		else
			return false;
	}
	bool isInt(string Input) //是 整数类型
	{
		for (int i = 0; i < Input.length(); i++)
		{
			if (!isNum(Input[i]))
				return false;
		}
		if (Store_Int.find(Input) == Store_Int.end())
			Store_Int[Input] = ++total_Count;
		return true;
	}
	bool isLetter(char Input)//是 字母
	{
		return (Input >= 'a' && Input <= 'z') || (Input >= 'A' && Input <= 'Z');
	}
	bool isDivided(string Input) //是 分隔符
	{
		if (sampleDictionary[Input])
		{
			if (sampleDictionary[Input] >= 39 && sampleDictionary[Input] <= 60)
				return true;
		}
		if (Input == " " || Input == "\n")
			return true;
		return false;
	}
	bool isIdentifier(string Input)//是 标识符
	{
		if (sampleDictionary[Input]) return false;
		if (Input.length() < 1) return false;
		if (!isLetter(Input[0])) return false;
		for (int i = 1; i < Input.length(); i++)
		{
			if (!(isLetter(Input[i]) || isNum(Input[i])))
				return false;
		}
		if (Store_Identifier.find(Input) == Store_Identifier.end())
			Store_Identifier[Input] = ++total_Count;
		return true;
	}
	/// <summary>
	/// 字符串匹配，0为非字符串，1为完整字符串，2为半匹配字符串
	/// </summary>
	/// <param name="Input"></param>
	/// <returns></returns>
	int isString(string Input)
	{
		if (Input[0] == '\'' && Input[Input.length() - 1] == '\'') //已经是完整的字符串了
		{
			if (Store_String.find(Input) == Store_String.end())
				Store_String[Input] = ++total_Count;
			return 1;
		}
		if (Input[0] == '\'') //如果只有一个头，切换状态
		{
			currState = &sampleAnalyze::CState;
			return 2;
		}
		return 0;
	}

	sampleAnalyze(string fileName,bool print = false)
	{
		lp = 0;
		rp = 0;
		currRow = 1;
		currState = &sampleAnalyze::DefaultState;
		fin.open(fileName, ios::in);
		if (!fin)
		{
			cout << "未成功打开文件：" << fileName << endl;
			return;
		}
		while (!fin.eof())
		{
			text += fin.get();
		}
		fin.close();
		if (print)
		{ 
			cout << "成功读取文件!\n\n";
			cout << text << endl;
		}
		FSM();
	}
	
};

void sampleAnalyze::FSM()
{
	cout << "进入词法分析\n\n";
	while (lp < text.length())
	{
		(this->*currState)();
	}
	printAll();
}
void sampleAnalyze::DefaultState()
{
	string currWord = readWord();
	bool isLegal = false;
	//忽略空格和换行
	while (currWord == " " || currWord == "\n")
	{
		if (currWord == "\n")
			currRow++;
		lp++;
		currWord = readWord();
	}
	if (!isLegal && isKeyWord(currWord))
	{
		PrintList.push_back(DoubleGroup(currWord, sampleDictionary[currWord], 0));
		isLegal = true;
		
	}
	if (!isLegal && isInt(currWord))
	{
		PrintList.push_back(DoubleGroup(currWord, 37, Store_Int[currWord]));
		isLegal = true;
	}
	if (!isLegal && isDivided(currWord))
	{
		if (!PrintList.empty())
		{
			string lastWord = PrintList.back().Word;
			if (isDivided(lastWord + currWord))
			{
				currWord = lastWord + currWord;
				PrintList.pop_back();
			}
		}
		if (sampleDictionary[currWord] == 49) //进入注释状态
			currState = &sampleAnalyze::IState;
		else
			PrintList.push_back(DoubleGroup(currWord, sampleDictionary[currWord]));
		isLegal = true;
	}
	if (!isLegal && isIdentifier(currWord))
	{
		PrintList.push_back(DoubleGroup(currWord, 36, Store_Identifier[currWord]));
		isLegal = true;
	}
	//字符常数判断，切换状态
	if (!isLegal && isString(currWord))
	{
		isLegal = true;
		if(isString(currWord) == 1)
			PrintList.push_back(DoubleGroup(currWord, 38, Store_String[currWord]));
	}
	//非法字符串报错
	if (!isLegal) {
		if ((int)currWord[0] != -1) //EOF判断
		cout << "ERROR: 非法字符 " << currWord << " 出现在第 " << currRow << " 行" << endl;
	}
	lp = ++rp;
}
string sampleAnalyze::readWord()
{
	rp = lp;
	while (rp < text.length() && !isDivided(ToString(text[rp])))
	{
		rp++;
	}
	if (rp != lp) rp--;
	return ToString(&text[lp], &text[rp]);
}
void sampleAnalyze::IState()
{
	string curr, last;
	curr = "";
	last = "";

	while (sampleDictionary[last + curr] != 42)	//右注释 */
	{
		last = curr;
		curr = readWord();
		lp = ++rp;
		if (curr == "\n")
		{
			cout << "ERROR：注释部分缺右边的界符*/ 在第" << currRow << "行\n";
			currRow++;
			break;
		}
	}
	currState = &sampleAnalyze::DefaultState;
}
void sampleAnalyze::CState()
{
	string curr;
	curr = readWord();
	lp = ++rp;

	while(curr[curr.length()-1]!='\'')
	{ 
		lp = ++rp;

		if (curr[curr.length() - 1] == '\n' || (int)curr[curr.length() - 1] == -1) //报错处理
		{
			cout << "ERROR：字符常数缺右边单引号 在第" << currRow << "行\n";
			currRow++;
			currState = &sampleAnalyze::DefaultState;
			return;
		}

		curr = curr + readWord();
	}

	int _temp_lp = lp - 1; //bug更改：向前回溯找到'
	while (text[_temp_lp] != '\'')
	{
		_temp_lp--;
	}
	curr = ToString(&text[_temp_lp], &text[lp]);

	if (Store_String.find(curr) == Store_String.end())
		Store_String[curr] = ++total_Count;

	currState = &sampleAnalyze::DefaultState;
	PrintList.push_back(DoubleGroup(curr, 38, Store_String[curr]));
}

int main()
{
	cout << "罗俊龙 2020计科二班 202030444506\n\n";
	cout << "请输入需要读取的文件名:(例如：program1.txt/program2.txt)\n" ;
	string FileName = "program2.txt";
	cin>>FileName;
	sampleDictionaryInit();
	cout << "尝试读取" << FileName << "文件中\n\n";
	sampleAnalyze a(FileName, 1);
	
	cout << endl;
	system("pause");
}
