// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 CALCULATOR_CPP_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// CALCULATOR_CPP_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef CALCULATOR_CPP_EXPORTS
#define CALCULATOR_CPP_API __declspec(dllexport)
#else
#define CALCULATOR_CPP_API __declspec(dllimport)
#endif
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// 此类是从 Calculator_cpp.dll 导出的

class CALCULATOR_CPP_API CCalculator_cpp {
public:
	string fnCalculator_cpp(string firNumber, string sceNumber, char op, int prec);
	// TODO:  在此添加您的方法。
};


//extern CALCULATOR_CPP_API int nCalculator_cpp;

//CALCULATOR_CPP_API string fnCalculator_cpp(string firNumber, string sceNumber, char op, int prec);

//双向链表
struct Node {
	short num;
	Node *last;
	Node *next;
};

//链表信息，以便进行数据传递
struct NumInfo {
	int len, sign;
	Node *head, *tail;
	bool operator < (NumInfo e) const;//重载<
	bool operator == (NumInfo e) const;//重载==
	void operator ++();//重载++，相当于乘以10
	void operator --();//重载--，相当于除以10
	NumInfo() {
		sign = 0;//默认为正数
	}
};


struct calculator {
public:	char op;//运算符
		int pointMove;//小数点移位数
		int Precision;//除法精确度
		NumInfo FirNum, SecNum, sum;
		string ans;
		//前处理：
		calculator(string a, string b, char oper, int prec) {
			Precision = prec;
			op = oper;
			ans = "";
			GetNum(a, b);
			sum = Operator();
			PrintSum(sum);
		}
		bool GetNum(string, string);//获取计算式
									//对字符串进行小数点移位（两个字符串小数补零对齐），并将移位保存，将字符串小数点,逗号和前缀0全部删除
		void RadixPoint(string &, string &);
		//建立双向动态链表保存待计算数据
		void BuildList(string &, NumInfo &);
		NumInfo OpPlus(NumInfo, NumInfo, int = 1);
		NumInfo OpReduce(NumInfo, NumInfo, int = 1);
		NumInfo Operator();
		NumInfo OpMulti(NumInfo, NumInfo);
		NumInfo OpMulti_singel(NumInfo, int);
		NumInfo OpDivision(NumInfo, NumInfo);
		//后处理：
		void PrintSum(NumInfo &);//输出结果
		void Delete(NumInfo &);//删除动态链表空间
};
