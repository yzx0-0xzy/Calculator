// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CALCULATOR_CPP_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CALCULATOR_CPP_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CALCULATOR_CPP_EXPORTS
#define CALCULATOR_CPP_API __declspec(dllexport)
#else
#define CALCULATOR_CPP_API __declspec(dllimport)
#endif
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// �����Ǵ� Calculator_cpp.dll ������

class CALCULATOR_CPP_API CCalculator_cpp {
public:
	string fnCalculator_cpp(string firNumber, string sceNumber, char op, int prec);
	// TODO:  �ڴ�������ķ�����
};


//extern CALCULATOR_CPP_API int nCalculator_cpp;

//CALCULATOR_CPP_API string fnCalculator_cpp(string firNumber, string sceNumber, char op, int prec);

//˫������
struct Node {
	short num;
	Node *last;
	Node *next;
};

//������Ϣ���Ա�������ݴ���
struct NumInfo {
	int len, sign;
	Node *head, *tail;
	bool operator < (NumInfo e) const;//����<
	bool operator == (NumInfo e) const;//����==
	void operator ++();//����++���൱�ڳ���10
	void operator --();//����--���൱�ڳ���10
	NumInfo() {
		sign = 0;//Ĭ��Ϊ����
	}
};


struct calculator {
public:	char op;//�����
		int pointMove;//С������λ��
		int Precision;//������ȷ��
		NumInfo FirNum, SecNum, sum;
		string ans;
		//ǰ����
		calculator(string a, string b, char oper, int prec) {
			Precision = prec;
			op = oper;
			ans = "";
			GetNum(a, b);
			sum = Operator();
			PrintSum(sum);
		}
		bool GetNum(string, string);//��ȡ����ʽ
									//���ַ�������С������λ�������ַ���С��������룩��������λ���棬���ַ���С����,���ź�ǰ׺0ȫ��ɾ��
		void RadixPoint(string &, string &);
		//����˫��̬���������������
		void BuildList(string &, NumInfo &);
		NumInfo OpPlus(NumInfo, NumInfo, int = 1);
		NumInfo OpReduce(NumInfo, NumInfo, int = 1);
		NumInfo Operator();
		NumInfo OpMulti(NumInfo, NumInfo);
		NumInfo OpMulti_singel(NumInfo, int);
		NumInfo OpDivision(NumInfo, NumInfo);
		//����
		void PrintSum(NumInfo &);//������
		void Delete(NumInfo &);//ɾ����̬����ռ�
};
