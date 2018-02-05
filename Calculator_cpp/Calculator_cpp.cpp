// Calculator_cpp.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Calculator_cpp.h"



// 这是导出变量的一个示例
//CALCULATOR_CPP_API string nCalculator_cpp;

// 这是导出函数的一个示例。
/*
CALCULATOR_CPP_API string fnCalculator_cpp(string firNumber, string sceNumber, char op, int prec)
{
string sCalculator_cpp;
calculator answer(firNumber, sceNumber, op, prec);
return sCalculator_cpp = answer.ans;
}
*/

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 Calculator_cpp.h
string CCalculator_cpp::fnCalculator_cpp(string firNumber, string sceNumber, char op, int prec)
{
	string sCalculator_cpp;
	calculator answer(firNumber, sceNumber, op, prec);
	return sCalculator_cpp = answer.ans;
}

bool NumInfo::operator < (NumInfo numRight) const {
	NumInfo numLeft;
	numLeft.head = head, numLeft.len = len, numLeft.tail = tail;
	while (numLeft.tail->num == 0 && numLeft.tail->last != NULL) {
		numLeft.tail = numLeft.tail->last;
		--numLeft.len;
	}
	while (numRight.tail->num == 0 && numRight.tail->last != NULL) {
		numRight.tail = numRight.tail->last;
		--numRight.len;
	}
	numLeft.head = head, numLeft.len = len, numLeft.tail = tail;
	if (numLeft.len == numRight.len) {
		for (int i = 0; i < numLeft.len; ++i) {
			if (numLeft.tail->num != numRight.tail->num)
				return numLeft.tail->num < numRight.tail->num;
			numLeft.tail = numLeft.tail->last;
			numRight.tail = numRight.tail->last;
		}
		return 0;
	}
	return numLeft.len < numRight.len;
}

//重载==运算符
bool NumInfo::operator == (NumInfo numRight) const {
	NumInfo numLeft;
	numLeft.head = head, numLeft.len = len, numLeft.tail = tail;
	if (numLeft.len == numRight.len) {
		for (int i = 0; i < numLeft.len; ++i) {
			if (numLeft.head->num != numRight.head->num)
				return 0;
			numLeft.head = numLeft.head->next;
			numRight.head = numRight.head->next;
		}
		return 1;
	}
	return 0;
}

//重载++运算符，每次++相当于乘以10
void NumInfo::operator ++() {
	len++;
	Node *p = new Node;
	p->num = 0;
	p->last = NULL;
	head->last = p, p->next = head;
	head = p;
}

//重载--运算符，每次--相当于除以10
void NumInfo::operator --() {
	len--;
	Node *p;
	p = head;
	head = head->next;
	if (head != NULL) head->last = NULL;//当len为1时无需再进行
	delete p;
}

//前处理：
//获取计算式
bool calculator::GetNum(string num1, string num2) {
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	//cout << "请输入计算式：\nFirst  Number:";
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//if ((num1[0] >= 'A' &&num1[0] <= 'Z') || (num1[0] <= 'z' &&num1[0] >= 'a')) return 0;
	//int sum = 0;
	//for (int i = 0; i < int(num1.length()); ++i) if (num1[i] == '.') ++sum;
	//if (sum > 1) {
	//	cout << "错误数据！请重新输入：\nFirst  Number:";
	//	goto loop1;
	//}
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	//cout << "运算符：";
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//if ((op >= 'A' && op <= 'Z') || (op <= 'z' && op >= 'a')) return 0;
	//if (op != '+' && op != '-' && op != '*' && op != '/') {
	//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	//	cout << "错误符号！请重新输入：\n运算符：";
	//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//	goto loop2;
	//}
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	//cout << "Second Number:";
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//cin >> num2;
	//  if ((num2[0] >= 'A' && num2[0] <= 'Z') || (num2[0] <= 'z' && num2[0] >= 'a')) return 0;
	//  sum = 0;
	//  for (int i = 0; i < int(num1.length()); ++i) if (num1[i] == '.') ++sum;
	//  if (sum > 1) {
	//	  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	//	  cout << "错误数据！请重新输入：\nSecond Number:";
	//	  goto loop3;
	// }
	// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	RadixPoint(num1, num2);
	BuildList(num1, FirNum);
	BuildList(num2, SecNum);
	return 1;
}

//对字符串进行小数点移位（两个字符串小数补零对齐），并将移位保存，将字符串小数点,逗号和前缀0全部删除
void calculator::RadixPoint(string & str1, string & str2) {
	str1.erase(remove(str1.begin(), str1.end(), ','), str1.end());
	str2.erase(remove(str2.begin(), str2.end(), ','), str2.end());

	//加减法
	if (op == '+' || op == '-') {
		int point1, point2;
		if (string::npos == str1.find('.')) point1 = 0;
		else {
			point1 = str1.length() - str1.find('.') - 1;
			str1 = str1.replace(str1.find('.'), 1, "");
		}

		if (string::npos == str2.find('.')) point2 = 0;
		else {
			point2 = str2.length() - str2.find('.') - 1;
			str2 = str2.replace(str2.find('.'), 1, "");
		}

		if (point1 > point2) {
			str2.append(point1 - point2, '0');
			pointMove = point1;
		}
		if (point1 < point2) {
			str1.append(point2 - point1, '0');
			pointMove = point2;
		}
		if (point1 == point2) {
			pointMove = point1;
		}
	}

	//乘法
	if (op == '*') {
		int point1 = 0, point2 = 0;
		if (string::npos == str1.find('.')) point1 = 0;
		else {
			point1 = str1.length() - str1.find('.') - 1;
			str1 = str1.replace(str1.find('.'), 1, "");
		}

		if (string::npos == str2.find('.')) point2 = 0;
		else {
			point2 = str2.length() - str2.find('.') - 1;
			str2 = str2.replace(str2.find('.'), 1, "");
		}
		pointMove = point1 + point2;
	}

	//除法
	if (op == '/') {
		int point1, point2;
		if (string::npos == str1.find('.')) point1 = 0;
		else {
			point1 = str1.length() - str1.find('.') - 1;
			str1 = str1.replace(str1.find('.'), 1, "");
		}

		if (string::npos == str2.find('.')) point2 = 0;
		else {
			point2 = str2.length() - str2.find('.') - 1;
			str2 = str2.replace(str2.find('.'), 1, "");
		}

		if (point1 > point2)
			str2.append(point1 - point2, '0');
		if (point1 < point2)
			str1.append(point2 - point1, '0');

		str1.append(Precision, '0');
		pointMove = Precision;
	}

	//去掉数据前缀0
	while (str1[0] == '0' && str1.length() != 1) {
		str1.replace(0, 1, "");
	}
	while (str2[0] == '0' && str2.length() != 1) {
		str2.replace(0, 1, "");
	}

}

//建立双向动态链表保存待计算数据
void calculator::BuildList(string & num, NumInfo & numinfo) {
	if (num[0] == '-')
		numinfo.len = num.length() - 1, numinfo.sign = 1;
	else
		numinfo.len = num.length(), numinfo.sign = 0;

	Node *p = NULL;
	for (int i = num.length() - 1; i >= int(num.length() - numinfo.len); --i) {//int()强行转化成有符号类型才能与i比较
		Node *q = new Node;
		q->num = num[i] - '0';
		if (i == num.length() - 1) numinfo.head = q;//首次循环先把链表头存入numinfo.head中
		else p->next = q, q->last = p;
		p = q;
	}
	p->next = NULL;
	numinfo.tail = p;
}

//对数据正负进行预处理,并选择调用的计算函数（包括对所有数字取绝对值等等）
NumInfo calculator::Operator() {
	NumInfo sum;
	if (op == '+') {
		if (FirNum.sign == 0 && SecNum.sign == 0) {
			FirNum.sign = SecNum.sign = 0;//把计算数据绝对值化，以下同理
			sum = OpPlus(FirNum, SecNum);
		}
		if (FirNum.sign == 0 && SecNum.sign == 1) {
			FirNum.sign = SecNum.sign = 0;
			sum = OpReduce(FirNum, SecNum);
		}
		if (FirNum.sign == 1 && SecNum.sign == 0) {
			FirNum.sign = SecNum.sign = 0;
			sum = OpReduce(SecNum, FirNum);
		}
		if (FirNum.sign == 1 && SecNum.sign == 1) {
			FirNum.sign = SecNum.sign = 0;
			sum = OpPlus(FirNum, SecNum);
			sum.sign = 1;
		}
	}

	if (op == '-') {
		if (FirNum.sign == 0 && SecNum.sign == 0) {
			FirNum.sign = SecNum.sign = 0;
			sum = OpReduce(FirNum, SecNum);
		}
		if (FirNum.sign == 0 && SecNum.sign == 1) {
			FirNum.sign = SecNum.sign = 0;
			sum = OpPlus(FirNum, SecNum);
		}
		if (FirNum.sign == 1 && SecNum.sign == 0) {
			FirNum.sign = SecNum.sign = 0;
			sum = OpPlus(FirNum, SecNum);
			sum.sign = 1;
		}
		if (FirNum.sign == 1 && SecNum.sign == 1) {
			FirNum.sign = SecNum.sign = 0;
			sum = OpReduce(SecNum, FirNum);
		}
	}

	if (op == '*') {
		int sign = FirNum.sign ^ SecNum.sign;
		FirNum.sign = SecNum.sign = 0;
		sum = OpMulti(FirNum, SecNum);
		sum.sign = sign;
	}

	if (op == '/') {
		if (FirNum.len == 1 && FirNum.head->num == 0) {
			Node *p = new Node;
			p->num = 0;
			p->next = p->last = NULL;
			sum.len = 1;
			sum.head = sum.tail = p;
			return sum;
		}

		int sign = FirNum.sign ^ SecNum.sign;
		FirNum.sign = SecNum.sign = 0;
		sum = OpDivision(FirNum, SecNum);
		sum.sign = sign;
	}

	return sum;
}

//加法运算
NumInfo calculator::OpPlus(NumInfo fir, NumInfo sec, int NoDelete) {
	int lenMin = min(fir.len, sec.len);
	int lenMax = max(fir.len, sec.len);
	Node *p1, *p2;
	NumInfo sum;
	p1 = fir.head;
	p2 = sec.head;
	int carry = 0;//用于保存进位

	Node *p = NULL;//用于保存链表中上一个数据

	for (int i = 0; i < lenMin; ++i) {
		Node *q = new Node;
		q->num = (p1->num + p2->num + carry) % 10;
		carry = (p1->num + p2->num + carry) / 10;
		if (i == 0) sum.head = q, sum.head->last = NULL;//首次循环先把链表头存入sum.head中
		else p->next = q, q->last = p;//建立双向链表指针
		p = q;
		p1 = p1->next, p2 = p2->next;
	}

	//当两个数据长度不一致时进行处理
	if (fir.len > sec.len) {
		while (p1) {
			Node *q = new Node;
			q->num = (p1->num + carry) % 10;
			carry = (p1->num + carry) / 10;
			p->next = q, q->last = p;
			p = q;
			p1 = p1->next;
		}
	}
	if (fir.len < sec.len) {
		while (p2) {
			Node *q = new Node;
			q->num = (p2->num + carry) % 10;
			carry = (p2->num + carry) / 10;
			p->next = q, q->last = p;
			p = q;
			p2 = p2->next;
		}
	}

	if (carry) {
		Node *q = new Node;
		q->num = carry;
		p->next = q, q->last = p;
		q->next = NULL;
		sum.len = lenMax + 1;
		sum.tail = q;
	}
	else {
		p->next = NULL;
		sum.len = lenMax;
		sum.tail = p;
	}
	//sum.sign = 0;//符号为正

	Delete(fir);//释放fir动态链表空间
	if (NoDelete) Delete(sec);//如果不是除法中的调用，则释放sec动态链表空间
	return sum;
}

//减法运算
NumInfo calculator::OpReduce(NumInfo fir, NumInfo sec, int NoDelete) {
	NumInfo sum;
	//sum.sign = 0;//结果符号默认为正

	if (fir == sec) {//对于被减数和减数相等的情况，直接输出
		Node *p = new Node;
		p->num = 0;
		p->next = p->last = NULL;
		sum.len = 1;
		sum.head = sum.tail = p;
		return sum;
	}
	if (fir < sec) {//对于被减数小于减数的情况，交换以保证被减数大于减数
		NumInfo tmp;
		tmp = fir;
		fir = sec;
		sec = tmp;
		sum.sign = 1;//结果为负
	}

	int lenMin = min(fir.len, sec.len);
	int lenMax = max(fir.len, sec.len);
	Node *p1, *p2;
	p1 = fir.head;
	p2 = sec.head;
	int carry = 0;//用于保存借位

	Node *p = NULL;//用于保存链表中上一个数据

	for (int i = 0; i < lenMin; ++i) {
		Node *q = new Node;
		q->num = (p1->num + 10 - p2->num + carry) % 10;
		carry = (p1->num + 10 - p2->num + carry) / 10 - 1;
		if (i == 0) sum.head = q, sum.head->last = NULL;//首次循环先把链表头存入sum.head中
		else p->next = q, q->last = p;//建立双向链表指针
		p = q;
		p1 = p1->next, p2 = p2->next;
	}

	//当两个数据长度不一致时进行处理
	if (fir.len > sec.len) {
		while (p1) {
			Node *q = new Node;
			q->num = (p1->num + 10 + carry) % 10;
			carry = (p1->num + 10 + carry) / 10 - 1;
			p->next = q, q->last = p;
			p = q;
			p1 = p1->next;
		}
	}

	if (p->num == 0) {
		Node *temp = p;
		p = p->last;
		p->next = NULL;
		sum.len = lenMax - 1;
		sum.tail = p;
		delete temp;//首位为0时，释放首位数据的空间
	}
	else {
		p->next = NULL;
		sum.len = lenMax;
		sum.tail = p;
	}

	Delete(fir);//释放fir动态链表空间
	if (NoDelete) Delete(sec);//如果不是除法中的调用，则释放sec动态链表空间
	return sum;
}

//乘法运算
NumInfo calculator::OpMulti(NumInfo fir, NumInfo sec) {
	NumInfo sum;
	Node *p = sec.head;//用于保存链表中上一个数据

	for (int i = 0; i < sec.len; ++i) {
		int n = p->num;
		NumInfo sumTemp = OpMulti_singel(fir, n);

		Node *tmp = NULL;
		sumTemp.len += i;
		for (int j = 0; j < i; ++j) {
			tmp = new Node;
			tmp->num = 0;
			sumTemp.head->last = tmp, tmp->next = sumTemp.head, tmp->last = NULL;
			sumTemp.head = tmp;
		}

		if (i == 0) sum = sumTemp;
		else sum = OpPlus(sum, sumTemp);
		p = p->next;
	}

	Delete(fir);
	Delete(sec);
	return sum;
}

//除法运算
NumInfo calculator::OpDivision(NumInfo fir, NumInfo sec) {
	NumInfo sum;
	if (fir < sec) {//按照所取的精度，此情况计算结果为0
		Node *p = new Node;
		p->num = 0;
		p->next = p->last = NULL;
		sum.len = 1;
		sum.head = sum.tail = p;
		return sum;
	}
	int Dvalue = fir.len - sec.len;//两个数据位数差值
	sum.len = Dvalue + 1;//商的长度
	for (int i = 0; i < Dvalue; ++i) ++sec;

	Node *p = NULL;
	for (int i = 0; i < sum.len; ++i) {//从右数第sum.len位除起
		int num = 0;

		while (sec < fir || sec == fir) {//试商
			++num;
			fir = OpReduce(fir, sec, 0);
		}

		Node *q = new Node;
		q->num = num;
		if (i == 0) sum.tail = q, sum.tail->next = NULL;//从链尾开始建起
		else p->last = q, q->next = p;//建立双向链表指针
		p = q;
		--sec;
	}

	p->last = NULL;
	sum.head = p;

	Delete(fir);//释放链表空间
	Delete(sec);
	return sum;
}

//乘数为个位数的算法
NumInfo calculator::OpMulti_singel(NumInfo fir, int n) {
	NumInfo sum;
	int carry = 0;//用于保存进位
	Node *p = NULL;//用于保存链表中上一个数据
	if (n == 0) {//遇到乘数为零时直接返回0
		Node *q = new Node;
		sum.len = 1;
		q->num = 0;
		q->last = q->next = NULL;
		sum.head = sum.tail = q;
		//sum.sign = 0;
		return sum;
	}

	for (int i = 0; i < fir.len; ++i) {
		Node *q = new Node;
		q->num = (fir.head->num * n + carry) % 10;
		carry = (fir.head->num * n + carry) / 10;
		if (i == 0) sum.head = q;//首次循环先把链表头存入sum.head中
		else p->next = q, q->last = p;//建立双向链表指针
		p = q;
		fir.head = fir.head->next;
	}

	if (carry) {
		Node *q = new Node;
		q->num = carry;
		p->next = q, q->last = p;
		q->next = NULL;
		sum.len = fir.len + 1;
		sum.tail = q;
	}
	else {
		p->next = NULL;
		sum.len = fir.len;
		sum.tail = p;
	}
	//sum.sign = 0;//符号为正

	return sum;
}


//后处理：

//输出结果
void calculator::PrintSum(NumInfo & num) {
	//cout << "计算结果：";
	if (num.sign == 1) ans += "-";//先输出符号


	int x = pointMove - num.len;
	for (int i = 0; i <= x; ++i) {//先处理掉-1到1之间的数据，比如0.001等等
		++num.len;
		Node *q = new Node;
		q->num = 0;
		q->last = num.tail, num.tail->next = q;
		num.tail = q;
	}

	Node *p;
	bool front = true;//用于判断是否输出了非零的首位数，以防出现前缀0
	for (int i = 0; i < num.len; ++i) {
		if (num.tail->num == 0 && front == true && i < num.len - pointMove - 1) {
			p = num.tail;
			num.tail = num.tail->last;
			delete p;//释放sum中前缀0的链表空间
			continue;
		}
		front = false;
		if (i == num.len - pointMove) ans += ".";
		if (pointMove == 0 && i % 3 == num.len % 3 && i) ans += ",";
		char c = num.tail->num + '0';
		ans += c;
		p = num.tail;
		num.tail = num.tail->last;
		delete p;//释放sum中的链表空间
	}
	//cout << "ans = " << ans << endl;
	//cout << "\n\n";
}

//释放链表空间
void calculator::Delete(NumInfo & num) {
	Node *p;
	while (num.head) {
		p = num.head;
		num.head = num.head->next;
		delete p;
	}
	num.head = num.tail = NULL;//删除悬挂指针
	num.len = 0;
}