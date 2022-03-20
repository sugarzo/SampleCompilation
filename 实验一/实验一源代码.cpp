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

//��Ԫ��
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
/// �����Ԫ��
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
			cout << "Tostring����δ�ɹ����أ����ܴ���������*a,*b\n";
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
	int lp; //��ָ��
	int rp; //��ָ��
	int currRow; //��ǰ����
	void (sampleAnalyze::*currState)(); //��ǰ״̬
public:
	string readWord();
	void FSM();
	void DefaultState();
	/// <summary>
	/// ע��״̬
	/// </summary>
	void IState(); 
	/// <summary>
	/// �ַ����ж�״̬
	/// </summary>
	void CState();

	bool isKeyWord(string input) //�� �ؼ���
	{
		if (sampleDictionary[input])
		{
			if (sampleDictionary[input] >= 1 && sampleDictionary[input] <= 35)
				return true;
		}
		return false;
	}
	bool isNum(char Input) //�� ����
	{
		if (Input >= '0' && Input <= '9')
			return true;
		else
			return false;
	}
	bool isInt(string Input) //�� ��������
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
	bool isLetter(char Input)//�� ��ĸ
	{
		return (Input >= 'a' && Input <= 'z') || (Input >= 'A' && Input <= 'Z');
	}
	bool isDivided(string Input) //�� �ָ���
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
	bool isIdentifier(string Input)//�� ��ʶ��
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
	/// �ַ���ƥ�䣬0Ϊ���ַ�����1Ϊ�����ַ�����2Ϊ��ƥ���ַ���
	/// </summary>
	/// <param name="Input"></param>
	/// <returns></returns>
	int isString(string Input)
	{
		if (Input[0] == '\'' && Input[Input.length() - 1] == '\'') //�Ѿ����������ַ�����
		{
			if (Store_String.find(Input) == Store_String.end())
				Store_String[Input] = ++total_Count;
			return 1;
		}
		if (Input[0] == '\'') //���ֻ��һ��ͷ���л�״̬
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
			cout << "δ�ɹ����ļ���" << fileName << endl;
			return;
		}
		while (!fin.eof())
		{
			text += fin.get();
		}
		fin.close();
		if (print)
		{ 
			cout << "�ɹ���ȡ�ļ�!\n\n";
			cout << text << endl;
		}
		FSM();
	}
	
};

void sampleAnalyze::FSM()
{
	cout << "����ʷ�����\n\n";
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
	//���Կո�ͻ���
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
		if (sampleDictionary[currWord] == 49) //����ע��״̬
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
	//�ַ������жϣ��л�״̬
	if (!isLegal && isString(currWord))
	{
		isLegal = true;
		if(isString(currWord) == 1)
			PrintList.push_back(DoubleGroup(currWord, 38, Store_String[currWord]));
	}
	//�Ƿ��ַ�������
	if (!isLegal) {
		if ((int)currWord[0] != -1) //EOF�ж�
		cout << "ERROR: �Ƿ��ַ� " << currWord << " �����ڵ� " << currRow << " ��" << endl;
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

	while (sampleDictionary[last + curr] != 42)	//��ע�� */
	{
		last = curr;
		curr = readWord();
		lp = ++rp;
		if (curr == "\n")
		{
			cout << "ERROR��ע�Ͳ���ȱ�ұߵĽ��*/ �ڵ�" << currRow << "��\n";
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

		if (curr[curr.length() - 1] == '\n' || (int)curr[curr.length() - 1] == -1) //������
		{
			cout << "ERROR���ַ�����ȱ�ұߵ����� �ڵ�" << currRow << "��\n";
			currRow++;
			currState = &sampleAnalyze::DefaultState;
			return;
		}

		curr = curr + readWord();
	}

	int _temp_lp = lp - 1; //bug���ģ���ǰ�����ҵ�'
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
	cout << "�޿��� 2020�ƿƶ��� 202030444506\n\n";
	cout << "��������Ҫ��ȡ���ļ���:(���磺program1.txt/program2.txt)\n" ;
	string FileName = "program2.txt";
	cin>>FileName;
	sampleDictionaryInit();
	cout << "���Զ�ȡ" << FileName << "�ļ���\n\n";
	sampleAnalyze a(FileName, 1);
	
	cout << endl;
	system("pause");
}
