// Calculator_cpp.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "Calculator_cpp.h"



// ���ǵ���������һ��ʾ��
//CALCULATOR_CPP_API string nCalculator_cpp;

// ���ǵ���������һ��ʾ����
/*
CALCULATOR_CPP_API string fnCalculator_cpp(string firNumber, string sceNumber, char op, int prec)
{
string sCalculator_cpp;
calculator answer(firNumber, sceNumber, op, prec);
return sCalculator_cpp = answer.ans;
}
*/

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� Calculator_cpp.h
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

//����==�����
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

//����++�������ÿ��++�൱�ڳ���10
void NumInfo::operator ++() {
	len++;
	Node *p = new Node;
	p->num = 0;
	p->last = NULL;
	head->last = p, p->next = head;
	head = p;
}

//����--�������ÿ��--�൱�ڳ���10
void NumInfo::operator --() {
	len--;
	Node *p;
	p = head;
	head = head->next;
	if (head != NULL) head->last = NULL;//��lenΪ1ʱ�����ٽ���
	delete p;
}

//ǰ����
//��ȡ����ʽ
bool calculator::GetNum(string num1, string num2) {
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	//cout << "���������ʽ��\nFirst  Number:";
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//if ((num1[0] >= 'A' &&num1[0] <= 'Z') || (num1[0] <= 'z' &&num1[0] >= 'a')) return 0;
	//int sum = 0;
	//for (int i = 0; i < int(num1.length()); ++i) if (num1[i] == '.') ++sum;
	//if (sum > 1) {
	//	cout << "�������ݣ����������룺\nFirst  Number:";
	//	goto loop1;
	//}
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	//cout << "�������";
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//if ((op >= 'A' && op <= 'Z') || (op <= 'z' && op >= 'a')) return 0;
	//if (op != '+' && op != '-' && op != '*' && op != '/') {
	//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	//	cout << "������ţ����������룺\n�������";
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
	//	  cout << "�������ݣ����������룺\nSecond Number:";
	//	  goto loop3;
	// }
	// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	RadixPoint(num1, num2);
	BuildList(num1, FirNum);
	BuildList(num2, SecNum);
	return 1;
}

//���ַ�������С������λ�������ַ���С��������룩��������λ���棬���ַ���С����,���ź�ǰ׺0ȫ��ɾ��
void calculator::RadixPoint(string & str1, string & str2) {
	str1.erase(remove(str1.begin(), str1.end(), ','), str1.end());
	str2.erase(remove(str2.begin(), str2.end(), ','), str2.end());

	//�Ӽ���
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

	//�˷�
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

	//����
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

	//ȥ������ǰ׺0
	while (str1[0] == '0' && str1.length() != 1) {
		str1.replace(0, 1, "");
	}
	while (str2[0] == '0' && str2.length() != 1) {
		str2.replace(0, 1, "");
	}

}

//����˫��̬���������������
void calculator::BuildList(string & num, NumInfo & numinfo) {
	if (num[0] == '-')
		numinfo.len = num.length() - 1, numinfo.sign = 1;
	else
		numinfo.len = num.length(), numinfo.sign = 0;

	Node *p = NULL;
	for (int i = num.length() - 1; i >= int(num.length() - numinfo.len); --i) {//int()ǿ��ת�����з������Ͳ�����i�Ƚ�
		Node *q = new Node;
		q->num = num[i] - '0';
		if (i == num.length() - 1) numinfo.head = q;//�״�ѭ���Ȱ�����ͷ����numinfo.head��
		else p->next = q, q->last = p;
		p = q;
	}
	p->next = NULL;
	numinfo.tail = p;
}

//��������������Ԥ����,��ѡ����õļ��㺯������������������ȡ����ֵ�ȵȣ�
NumInfo calculator::Operator() {
	NumInfo sum;
	if (op == '+') {
		if (FirNum.sign == 0 && SecNum.sign == 0) {
			FirNum.sign = SecNum.sign = 0;//�Ѽ������ݾ���ֵ��������ͬ��
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

//�ӷ�����
NumInfo calculator::OpPlus(NumInfo fir, NumInfo sec, int NoDelete) {
	int lenMin = min(fir.len, sec.len);
	int lenMax = max(fir.len, sec.len);
	Node *p1, *p2;
	NumInfo sum;
	p1 = fir.head;
	p2 = sec.head;
	int carry = 0;//���ڱ����λ

	Node *p = NULL;//���ڱ�����������һ������

	for (int i = 0; i < lenMin; ++i) {
		Node *q = new Node;
		q->num = (p1->num + p2->num + carry) % 10;
		carry = (p1->num + p2->num + carry) / 10;
		if (i == 0) sum.head = q, sum.head->last = NULL;//�״�ѭ���Ȱ�����ͷ����sum.head��
		else p->next = q, q->last = p;//����˫������ָ��
		p = q;
		p1 = p1->next, p2 = p2->next;
	}

	//���������ݳ��Ȳ�һ��ʱ���д���
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
	//sum.sign = 0;//����Ϊ��

	Delete(fir);//�ͷ�fir��̬����ռ�
	if (NoDelete) Delete(sec);//������ǳ����еĵ��ã����ͷ�sec��̬����ռ�
	return sum;
}

//��������
NumInfo calculator::OpReduce(NumInfo fir, NumInfo sec, int NoDelete) {
	NumInfo sum;
	//sum.sign = 0;//�������Ĭ��Ϊ��

	if (fir == sec) {//���ڱ������ͼ�����ȵ������ֱ�����
		Node *p = new Node;
		p->num = 0;
		p->next = p->last = NULL;
		sum.len = 1;
		sum.head = sum.tail = p;
		return sum;
	}
	if (fir < sec) {//���ڱ�����С�ڼ���������������Ա�֤���������ڼ���
		NumInfo tmp;
		tmp = fir;
		fir = sec;
		sec = tmp;
		sum.sign = 1;//���Ϊ��
	}

	int lenMin = min(fir.len, sec.len);
	int lenMax = max(fir.len, sec.len);
	Node *p1, *p2;
	p1 = fir.head;
	p2 = sec.head;
	int carry = 0;//���ڱ����λ

	Node *p = NULL;//���ڱ�����������һ������

	for (int i = 0; i < lenMin; ++i) {
		Node *q = new Node;
		q->num = (p1->num + 10 - p2->num + carry) % 10;
		carry = (p1->num + 10 - p2->num + carry) / 10 - 1;
		if (i == 0) sum.head = q, sum.head->last = NULL;//�״�ѭ���Ȱ�����ͷ����sum.head��
		else p->next = q, q->last = p;//����˫������ָ��
		p = q;
		p1 = p1->next, p2 = p2->next;
	}

	//���������ݳ��Ȳ�һ��ʱ���д���
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
		delete temp;//��λΪ0ʱ���ͷ���λ���ݵĿռ�
	}
	else {
		p->next = NULL;
		sum.len = lenMax;
		sum.tail = p;
	}

	Delete(fir);//�ͷ�fir��̬����ռ�
	if (NoDelete) Delete(sec);//������ǳ����еĵ��ã����ͷ�sec��̬����ռ�
	return sum;
}

//�˷�����
NumInfo calculator::OpMulti(NumInfo fir, NumInfo sec) {
	NumInfo sum;
	Node *p = sec.head;//���ڱ�����������һ������

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

//��������
NumInfo calculator::OpDivision(NumInfo fir, NumInfo sec) {
	NumInfo sum;
	if (fir < sec) {//������ȡ�ľ��ȣ������������Ϊ0
		Node *p = new Node;
		p->num = 0;
		p->next = p->last = NULL;
		sum.len = 1;
		sum.head = sum.tail = p;
		return sum;
	}
	int Dvalue = fir.len - sec.len;//��������λ����ֵ
	sum.len = Dvalue + 1;//�̵ĳ���
	for (int i = 0; i < Dvalue; ++i) ++sec;

	Node *p = NULL;
	for (int i = 0; i < sum.len; ++i) {//��������sum.lenλ����
		int num = 0;

		while (sec < fir || sec == fir) {//����
			++num;
			fir = OpReduce(fir, sec, 0);
		}

		Node *q = new Node;
		q->num = num;
		if (i == 0) sum.tail = q, sum.tail->next = NULL;//����β��ʼ����
		else p->last = q, q->next = p;//����˫������ָ��
		p = q;
		--sec;
	}

	p->last = NULL;
	sum.head = p;

	Delete(fir);//�ͷ�����ռ�
	Delete(sec);
	return sum;
}

//����Ϊ��λ�����㷨
NumInfo calculator::OpMulti_singel(NumInfo fir, int n) {
	NumInfo sum;
	int carry = 0;//���ڱ����λ
	Node *p = NULL;//���ڱ�����������һ������
	if (n == 0) {//��������Ϊ��ʱֱ�ӷ���0
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
		if (i == 0) sum.head = q;//�״�ѭ���Ȱ�����ͷ����sum.head��
		else p->next = q, q->last = p;//����˫������ָ��
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
	//sum.sign = 0;//����Ϊ��

	return sum;
}


//����

//������
void calculator::PrintSum(NumInfo & num) {
	//cout << "��������";
	if (num.sign == 1) ans += "-";//���������


	int x = pointMove - num.len;
	for (int i = 0; i <= x; ++i) {//�ȴ����-1��1֮������ݣ�����0.001�ȵ�
		++num.len;
		Node *q = new Node;
		q->num = 0;
		q->last = num.tail, num.tail->next = q;
		num.tail = q;
	}

	Node *p;
	bool front = true;//�����ж��Ƿ�����˷������λ�����Է�����ǰ׺0
	for (int i = 0; i < num.len; ++i) {
		if (num.tail->num == 0 && front == true && i < num.len - pointMove - 1) {
			p = num.tail;
			num.tail = num.tail->last;
			delete p;//�ͷ�sum��ǰ׺0������ռ�
			continue;
		}
		front = false;
		if (i == num.len - pointMove) ans += ".";
		if (pointMove == 0 && i % 3 == num.len % 3 && i) ans += ",";
		char c = num.tail->num + '0';
		ans += c;
		p = num.tail;
		num.tail = num.tail->last;
		delete p;//�ͷ�sum�е�����ռ�
	}
	//cout << "ans = " << ans << endl;
	//cout << "\n\n";
}

//�ͷ�����ռ�
void calculator::Delete(NumInfo & num) {
	Node *p;
	while (num.head) {
		p = num.head;
		num.head = num.head->next;
		delete p;
	}
	num.head = num.tail = NULL;//ɾ������ָ��
	num.len = 0;
}