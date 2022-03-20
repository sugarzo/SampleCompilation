 #include <fstream>
#include <iostream>
#include <stdlib.h>
#include<map>
#include<list>
#include<stack>
#include<vector>
#include<cstdio>
using namespace std;

map<string, int> sampleDictionary;
map<string, int> Store_Identifier;
map<string, int> Store_String;
map<string, int> Store_Int;
int total_Count = 0;

string ToString(char* a, char* b)
{
	string ret = "";
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
string ToString(int a)
{
	string ret = "";
	while (a > 0)
	{
		char temp = (char)(a % 10 + '0');
		ret = temp + ret;
		a /= 10;
	}
	return ret;
}
int ToInt(string a)
{
	int ret = 0;
	for(int i=0;i<a.length();i++)
	{
		if (a[i] >= '0' && a[i] <= '9')
		{
			ret = ret * 10 + a[i] - '0';
		}
	}
	return ret;
}


//二元组
struct DoubleGroup {
	int a;
	int b;
	string Word;
	DoubleGroup(string w, int x = 0, int y = 0)
	{
		Word = w;
		a = x;
		b = y;
	}
};
//四元组
struct Quaternion {
	string v1, v2, v3, v4;
	int index;
	Quaternion(int _index, string _v1 = "-", string _v2 = "-", string _v3 = "-", string _v4 = "-")
	{
		index = _index;
		v1 = _v1;
		v2 = _v2;
		v3 = _v3;
		v4 = _v4;
	}
};
vector<Quaternion> Quaternions;
int _getFinalJump(int index)
{
	if (Quaternions[index].v1 != "j")
	{
		return index;
	}
	else
	{
		int retTemp = _getFinalJump(ToInt(Quaternions[index].v4));
		Quaternions[index].v4 = ToString(retTemp);
		return retTemp;
	}
}
struct EState
{
	int selfpos; //自己在四元组中对应的位置
	int _true; //真出口
	int _false; //假出口
	bool isCorrect; //锁定 真出口&假出口，给e1 or e2 或 e1 and e2情况下使用
	EState* _trueList; //回填真出口的链表
	EState* _falseList;//回填假出口的链表
	EState(int _index)
	{
		selfpos = _index;
		_true = -1;
		_false = -1;
		_trueList = NULL;
		_falseList = NULL;
		isCorrect = false;
	}
	EState*& GetTlist() //得到需要回填的真出口链表尾
	{
		if (_trueList == NULL)
			return _trueList;
		else
			return _trueList->GetTlist();
	}
	EState*& GetFlist() //得到需要回填的假出口链表尾
	{
		if (_falseList == NULL)
			return _falseList;
		else
			return _falseList->GetFlist();
	}
	void backpatch_T(int exit) //回填真出口
	{
		_true = exit;
		if (selfpos > 0 && !isCorrect)
		{
			Quaternions[selfpos].v4 = ToString(_true);
		}
		if (_trueList == NULL)
			return;
		else
			_trueList->backpatch_T(exit);
	}
	void backpatch_F(int exit)//回填假出口
	{
		_false = exit;
		if (selfpos > 0 && !isCorrect)
		{
			Quaternions[selfpos].v4 = ToString(_false);
		}
		if (_falseList == NULL)
			return;
		else
			_falseList->backpatch_F(exit);
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
		//cout << PrintList.front().Word<<"\t";
		printDoubleGroup(PrintList.front().a, PrintList.front().b);
		PrintList.pop_front();
		if (--tot == 0)
		{
			cout << endl;
			tot = 5;
		}
	}
	cout << endl;
}



class sampleAnalyze {
private:
	string text;
	ifstream fin;
	int lp; //左指针
	int rp; //右指针
	int currRow; //当前行数
	void (sampleAnalyze::* currState)(); //当前状态
	vector<DoubleGroup> words; //词法列表
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
	bool isDivided(string Input)
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
		//if (Store_Identifier[Input]) return true;
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
	bool IsCondition(string op) //是 bool 符
	{
		return (op == "<") || (op == "<=") || (op == "=") || (op == ">") || (op == ">=");
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
	void SerializationWord() //将Printlist序列化存储
	{
		words.clear();
		int len = PrintList.size();
		for (int i = 0; i < len; i++)
		{
			words.push_back(PrintList.front());
			PrintList.push_back(PrintList.front());
			PrintList.pop_front();
		}
	}
	sampleAnalyze(string fileName, bool print = false)
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
		//cout << ToString(&text[lp], &text[lp+10]);
	}


	//实验一后的补充，以下是语法分析，words为单词数组
	void Gramma_analysis();   //语法分析，负责逐字扫描单词，压语义栈，跳转到对应语义动作
	void Gramma_Expression();  //表达式的四元式翻译
	void Gramma_Expression(int);
	void Gramma_Assignment();  //赋值句的四元式翻译
	EState& Gramma_Condition(); //bool式的四元式翻译，返回整个bool式子的状态E
	void Gramma_FrontQuaternions(); //四元式生成前调用，在这里匹配语义栈执行对应语义动作
	void Gramma_Quaternions_MergeJump(); //在最终输出前先合并一次jump

	void Gramma_AfterQuaternions(); //use after the Quaternions produce
};
void sampleAnalyze::FSM()
{
	//cout << "进入词法分析\n\n";
	while (lp < text.length())
	{
		(this->*currState)();
	}
	SerializationWord();
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
		//TODO 切换状态，二元标识符的判断
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
		if (isString(currWord) == 1)
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

	while (curr[curr.length() - 1] != '\'')
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

//词法分析 END
//语法分析 代码部分

void PrintQuatrenions()
{
	for (int i = 0; i < Quaternions.size(); i++)
	{
		printf("(%d) (%s,%s,%s,%s)\n", Quaternions[i].index,
			Quaternions[i].v1.c_str(),
			Quaternions[i].v2.c_str(),
			Quaternions[i].v3.c_str(),
			Quaternions[i].v4.c_str());
	}
}
int _curr_lp = 0;
int _curr_index = 0;
int _curr_T= 0;
//if while repeat的属性
struct if_State
{
	EState* E;      //对应的bool表达式
	int pos_ElseQ;  //如果该if出现了对应的else，要记录该E.false的入口和E.true的出口
	if_State(EState& _temp)
	{
		E = &_temp;
		pos_ElseQ = -1;
	}
	void backpatch_T(int exit)
	{
		E->backpatch_T(exit);
	}
	void backpatch_F(int exit)
	{
		E->backpatch_F(exit);
	}

};
struct while_State
{
	int Enter; //while入口编号
	EState* E; //对应的bool表达式
	void backpatch_T(int exit)
	{
		E->backpatch_T(exit);
	}
	void backpatch_F(int exit)
	{
		E->backpatch_F(exit);
	}
	while_State(EState& _temp,int _enter = _curr_index)
	{
		E = &_temp;
		Enter = _enter;
	}
};
struct repeat_State
{
	int Enter; //repeat入口编号
	EState* E; //对应的bool表达式
	repeat_State(int _enter)
	{
		Enter = _enter;
		E = NULL;
	}
	void backpatch_T(int exit)
	{
		E->backpatch_T(exit);
	}
	void backpatch_F(int exit)
	{
		E->backpatch_F(exit);
	}
};
stack<string> StateStack; //语义栈  只会出现if\else\then\while\do的动作符
stack<if_State> ifStack;
stack<while_State> whileStack;
stack<repeat_State> repeatState;
list<EState> e_Storage;   //bool表达式、储存ei条件的状态
list<EState> E_stateList; //储存E条件的状态
void sampleAnalyze::Gramma_analysis()
{
	cout << "\n进入语法分析\n\n";
	while (_curr_lp < words.size())
	{
		//cout << "指针" << _curr_lp << "  " << words[_curr_lp].Word << endl;
		if (words[_curr_lp].Word == "program")
		{
			_curr_lp++;
			Gramma_FrontQuaternions();
			Quaternions.push_back(Quaternion(_curr_index++, "program", words[_curr_lp].Word));
			Gramma_AfterQuaternions();
			_curr_lp++;
			continue;
		}
		if (words[_curr_lp].a == 36 || words[_curr_lp].a == 37)
		{
			Gramma_Expression();
			continue;
		}
		if (words[_curr_lp].Word == ":=")
		{
			Gramma_Assignment();
			continue;
		}
		if (words[_curr_lp].Word == "if")
		{
			Gramma_FrontQuaternions();
			ifStack.push(Gramma_Condition());
			StateStack.push("if");
		}
		if (words[_curr_lp].Word == "while")
		{
			Gramma_FrontQuaternions();
			int _enter = _curr_index;
			whileStack.push( while_State(Gramma_Condition(),_enter) );
			StateStack.push("while");
		}
		if (words[_curr_lp].Word == "repeat")
		{
			repeatState.push( repeat_State(-1) ); //标记需要回填repeat的入口
		}
		if (words[_curr_lp].Word == "then")
		{
			StateStack.push("then");
		}
		if (words[_curr_lp].Word == "else")
		{
			StateStack.push("else");
		}
		if (words[_curr_lp].Word == "until")
		{
			repeatState.top().E = &Gramma_Condition();
			repeatState.top().backpatch_F(repeatState.top().Enter);  //假出口为repeat的入口
			repeatState.top().backpatch_T(_curr_index);				 //真出口为until下一行
			repeatState.pop();
		}
		if (words[_curr_lp].Word == "do")
		{
			StateStack.push("do");
		}
		_curr_lp++;
	}
	Gramma_FrontQuaternions();
	Quaternions.push_back(Quaternion(_curr_index++, "sys"));

	Gramma_Quaternions_MergeJump();
	PrintQuatrenions();
	return;
}
void sampleAnalyze::Gramma_Expression()
{
	int _temp_rp = _curr_lp + 1;
	list<int> multip_division; //乘除标志位
	list<int> add_sub; //加减标志位

	while (words[_temp_rp].a == 36 || words[_temp_rp].a == 37 || words[_temp_rp].a == 38 ||
		words[_temp_rp].Word == "*" || words[_temp_rp].Word == "/" ||
		words[_temp_rp].Word == "+" || words[_temp_rp].Word == "-")
	{
		if (words[_temp_rp].Word == "*" || words[_temp_rp].Word == "/")
		{
			multip_division.push_back(_temp_rp); //记录位置
		}
		_temp_rp++;
	}
	_temp_rp--;
	if (_temp_rp == _curr_lp) {
		_curr_lp++;
		return;
	}

	Gramma_FrontQuaternions();
	//处理乘除，再处理加减
	int additive = 0;
	while (!multip_division.empty())
	{
		int _temp_pos = multip_division.front();
		multip_division.pop_front();
		Quaternions.push_back(Quaternion(_curr_index++,
			words[_temp_pos - additive].Word, words[_temp_pos - 1 - additive].Word, words[_temp_pos + 1 - additive].Word, "T" + ToString(++_curr_T)));

		words.erase(words.begin() + _temp_pos - additive - 1, words.begin() + _temp_pos - additive + 2);
		words.insert(words.begin() + _temp_pos - additive - 1, DoubleGroup("T" + ToString(_curr_T), 36, -1));
		additive += 2;
	}

	_temp_rp = _curr_lp + 1;
	while (words[_temp_rp].a == 36 || words[_temp_rp].a == 37 || words[_temp_rp].a == 38 ||
		words[_temp_rp].Word == "*" || words[_temp_rp].Word == "/" ||
		words[_temp_rp].Word == "+" || words[_temp_rp].Word == "-")
	{
		if (words[_temp_rp].Word == "+" || words[_temp_rp].Word == "-")
		{
			add_sub.push_back(_temp_rp); //记录位置
		}
		_temp_rp++;
	}
	_temp_rp--;

	additive = 0;
	while (!add_sub.empty())
	{
		int _temp_pos = add_sub.front();
		add_sub.pop_front();
		Quaternions.push_back(Quaternion(_curr_index++,
			words[_temp_pos - additive].Word, words[_temp_pos - 1 - additive].Word, words[_temp_pos + 1 - additive].Word, "T" + ToString(++_curr_T)));

		words.erase(words.begin() + _temp_pos - additive - 1, words.begin() + _temp_pos - additive + 2);
		words.insert(words.begin() + _temp_pos - additive - 1, DoubleGroup("T" + ToString(_curr_T), 36, -1));
		additive += 2;
		_temp_rp -= 2;
	}

	Gramma_AfterQuaternions();
	_curr_lp = _temp_rp + 1;
}
void sampleAnalyze::Gramma_Expression(int lp)
{

	int _temp_rp = lp;
	list<int> multip_division; //乘除标志位
	list<int> add_sub; //加减标志位

	while (words[_temp_rp].a == 36 || words[_temp_rp].a == 37 || words[_temp_rp].a == 38 ||
		words[_temp_rp].Word == "*" || words[_temp_rp].Word == "/" ||
		words[_temp_rp].Word == "+" || words[_temp_rp].Word == "-")
	{
		if (words[_temp_rp].Word == "*" || words[_temp_rp].Word == "/")
		{
			multip_division.push_back(_temp_rp); //记录位置
		}
		_temp_rp++;
	}
	_temp_rp--;
	if (_temp_rp == lp) {
		return;
	}

	Gramma_FrontQuaternions();
	//处理乘除，再处理加减
	int additive = 0;
	while (!multip_division.empty())
	{
		int _temp_pos = multip_division.front();
		multip_division.pop_front();
		Quaternions.push_back(Quaternion(_curr_index++,
			words[_temp_pos - additive].Word, words[_temp_pos - 1 - additive].Word, words[_temp_pos + 1 - additive].Word, "T" + ToString(++_curr_T)));

		words.erase(words.begin() + _temp_pos - additive - 1, words.begin() + _temp_pos - additive + 2);
		words.insert(words.begin() + _temp_pos - additive - 1, DoubleGroup("T" + ToString(_curr_T), 36, -1));
		additive += 2;
	}

	_temp_rp = lp;
	while (words[_temp_rp].a == 36 || words[_temp_rp].a == 37 || words[_temp_rp].a == 38 ||
		words[_temp_rp].Word == "*" || words[_temp_rp].Word == "/" ||
		words[_temp_rp].Word == "+" || words[_temp_rp].Word == "-")
	{
		if (words[_temp_rp].Word == "+" || words[_temp_rp].Word == "-")
		{
			add_sub.push_back(_temp_rp); //记录位置
		}
		_temp_rp++;
	}
	_temp_rp--;

	additive = 0;
	while (!add_sub.empty())
	{
		int _temp_pos = add_sub.front();
		add_sub.pop_front();
		Quaternions.push_back(Quaternion(_curr_index++,
			words[_temp_pos - additive].Word, words[_temp_pos - 1 - additive].Word, words[_temp_pos + 1 - additive].Word, "T" + ToString(++_curr_T)));

		words.erase(words.begin() + _temp_pos - additive - 1, words.begin() + _temp_pos - additive + 2);
		words.insert(words.begin() + _temp_pos - additive - 1, DoubleGroup("T" + ToString(_curr_T), 36, -1));
		additive += 2;
		_temp_rp -= 2;
	}
	Gramma_AfterQuaternions();
}
EState& sampleAnalyze::Gramma_Condition()
{
	int _temp_lp, _temp_rp;
	_temp_lp = _curr_lp + 1;
	_temp_rp = _curr_lp + 1;

	int andPoint = 0;
	int orPoint = 0;
	int _Condition = 0;
	
	//记录属性
	E_stateList.push_back(EState(-1));
	EState *p = &E_stateList.back();
	EState *lastT = NULL, *lastF = NULL;

	while (words[_temp_rp].a == 36 || words[_temp_rp].a == 37 || words[_temp_rp].a == 38  || IsCondition(words[_temp_rp].Word) || words[_temp_rp].Word == "and" || words[_temp_rp].Word == "or")
	{
		if (words[_temp_rp].a == 36 || words[_temp_rp].a == 37 || words[_temp_rp].a == 38)
		{
			Gramma_Expression(_temp_rp);
		}
		if (IsCondition(words[_temp_rp].Word))
		{
			Gramma_Expression(_temp_rp + 1);
			if(orPoint + andPoint < 1)
			{ 
				//压入状态栈
				e_Storage.push_back(EState(_curr_index));
				Quaternions.push_back(Quaternion(_curr_index++, "j" + words[_temp_rp].Word, words[_temp_rp - 1].Word, words[_temp_rp + 1].Word, "-1"));
				lastT = p->GetTlist() = &e_Storage.back();

				e_Storage.push_back(EState(_curr_index));
				Quaternions.push_back(Quaternion(_curr_index++,"j", "-","-" ,"-1"));
				lastF = p->GetFlist() = &e_Storage.back();
			}
			else 
			{
				if (orPoint == 1)
				{
					e_Storage.push_back(EState(_curr_index));
					Quaternions.push_back(Quaternion(_curr_index++, "j" + words[_temp_rp].Word, words[_temp_rp - 1].Word, words[_temp_rp + 1].Word, "-1"));
					lastT = p->GetTlist() = &e_Storage.back();

					lastF->isCorrect = true;
					Quaternions[lastF->selfpos].v4 = ToString(_curr_index);
					e_Storage.push_back(EState(_curr_index));
					Quaternions.push_back(Quaternion(_curr_index++, "j", "-", "-", "-1"));
					lastF = p->GetFlist() = &e_Storage.back();

					orPoint--;
				}
				if (andPoint == 1)
				{
					lastT->isCorrect = true;
					Quaternions[lastT->selfpos].v4 = ToString(_curr_index);
					e_Storage.push_back(EState(_curr_index));
					Quaternions.push_back(Quaternion(_curr_index++, "j" + words[_temp_rp].Word, words[_temp_rp - 1].Word, words[_temp_rp + 1].Word, "-1"));
					lastT = p->GetTlist() = &e_Storage.back();

					e_Storage.push_back(EState(_curr_index));
					Quaternions.push_back(Quaternion(_curr_index++, "j", "-", "-", "-1"));
					lastF = p->GetFlist() = &e_Storage.back();

					andPoint--;
				}
			}
			_Condition++;
		}
		if (words[_temp_rp].Word == "and")
		{
			andPoint++;
			if(orPoint + andPoint > 1)
			{
				cout << "ERROR:" << "条件式语法分析错误：多余的and或or！";
				abort();
			}
		}
		if (words[_temp_rp].Word == "or")
		{
			orPoint++;
			if (orPoint + andPoint > 1)
			{
				cout << "ERROR:" << "条件式语法分析错误：多余的and或or！";
				abort();
			}
		}
		_temp_rp++;
	}
	if (_Condition == 0)
	{
		cout << "ERROR:" << "条件式语法分析错误！";
		abort();
	}
	_curr_lp = _temp_rp - 1;

	Gramma_AfterQuaternions();
	return *p;
}
void sampleAnalyze::Gramma_Assignment()
{
	int _temp_pos = _curr_lp;
	_curr_lp++;
	Gramma_Expression();
	Quaternions.push_back(Quaternion(_curr_index++, ":=", words[_temp_pos + 1].Word, "-", words[_temp_pos - 1].Word));
}
void sampleAnalyze::Gramma_FrontQuaternions()
{
	while (!StateStack.empty())
	{
		if (StateStack.top() == "if")
		{
			if (ifStack.top().E->_true != -1 && ifStack.top().E->_false == -1) //true出口已回填，false出口未回填(无else情况)
			{
				ifStack.top().backpatch_F(_curr_index); //回填false出口
			}
			else if (ifStack.top().E->_true == -1) //true出口未回填
			{
				cout << "语法分析错误：if缺少then";
				abort();
			}
			else if (ifStack.top().E->_true != -1 && ifStack.top().E->_false != -1) //true出口\false出口已回填(有else情况)
			{
				Quaternions[ifStack.top().pos_ElseQ].v4 = ToString(_curr_index); //回填if-exit的出口
			}
			ifStack.pop();
			StateStack.pop();
			continue;
		}
		if (StateStack.top() == "else")
		{
			if (ifStack.top().E->_true != -1 && ifStack.top().E->_false == -1) //true出口已回填，false出口未回填
			{
				ifStack.top().pos_ElseQ = _curr_index;	//标记if-exit的出口
				Quaternions.push_back(Quaternion(_curr_index++,"j"));
				ifStack.top().backpatch_F(_curr_index); //回填假出口
			}
			else if (ifStack.top().E->_true != -1 && ifStack.top().E->_false != -1) //true出口已回填，false出口未回填
			{
				cout << "语法分析错误：出现了多余的else";
				abort();
			}
			else if (ifStack.top().E->_true == -1) //true出口未回填
			{
				cout << "语法分析错误：if缺少then";
				abort();
			}
			StateStack.pop(); //弹出then
			break;
		}
		if (StateStack.top() == "then")
		{
			if (ifStack.top().E->_true != -1) //true出口已回填
			{
				cout << "语法分析错误：多余的then出现";
				abort();
			}
			if (ifStack.top().E->_true == -1) //true出口未回填
			{
				ifStack.top().backpatch_T(_curr_index); //回填if.true
			}
			StateStack.pop();
			break;
		}

		if (StateStack.top() == "while")
		{
			if (whileStack.top().E->_true == -1) //while.true出口未被回填
			{
				cout << "语法分析错误：while缺少do";
				abort();
			}
			//产生新四元式(循环回调）
			Quaternions.push_back(Quaternion(_curr_index++, "j", "-", "-", ToString(whileStack.top().Enter)));
			whileStack.top().backpatch_F(_curr_index);//回填while.false出口

			whileStack.pop();
			StateStack.pop();
			continue;
		}
		if (StateStack.top() == "do")
		{
			if (whileStack.top().E->_true != -1) //while.true出口已被回填
			{
				cout << "语法分析错误：多余的do出现";
				abort();
			}
			//回填while.true出口
			whileStack.top().backpatch_T(_curr_index);

			StateStack.pop();
			break;
		}
	}
	if (!repeatState.empty() && repeatState.top().Enter == -1) //有需要回填的repeat出口(写在这里的目的是为了先把else的四元式生成完)
	{
		repeatState.top().Enter = _curr_index;
	}
}
void sampleAnalyze::Gramma_AfterQuaternions()
{

}
void sampleAnalyze::Gramma_Quaternions_MergeJump()
{
	for (int i = 0; i < Quaternions.size(); i++)
	{
		_getFinalJump(i);
	}
}

int main()
{
	cout << "罗俊龙 2020计科二班 202030444506\n\n";
	cout << "请输入需要读取的文件名:(例如：program3.txt/program4.txt)\n" ;
	string FileName = "program3.txt";
	cin>>FileName;
	sampleDictionaryInit();  //初始化字典
	cout << "尝试读取" << FileName << "文件中\n\n";
	sampleAnalyze a(FileName, 1);
	//printAll(); //词法分析输出
	a.Gramma_analysis();

	cout << endl;
	system("pause");
}
