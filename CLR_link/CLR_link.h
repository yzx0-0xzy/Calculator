// CLR_link.h

#pragma once
#include <string>
#include "..\Calculator_cpp\Calculator_cpp.h"
using namespace System;
using namespace Runtime::InteropServices;
using namespace std;
namespace CLR_link {

	public ref class Class1
	{
	public:
		Class1() { ptr = new CCalculator_cpp; }
		~Class1() { this->!Class1(); }
		!Class1() { delete ptr; }
		//String ^ ss(Char op, int prec) { return "dsf"; }
		String^ link(String ^a, String ^b, Char op, Int32 prec)
		{
			string firNum, secNum;
			char *str1 = (char *)(Marshal::StringToHGlobalAnsi(a)).ToPointer();
			char *str2 = (char *)(Marshal::StringToHGlobalAnsi(b)).ToPointer();
			firNum = str1;
			secNum = str2;
			String ^ res = gcnew String(ptr->fnCalculator_cpp(firNum, secNum, op, prec).c_str());
			return res;
		}
		// TODO:  在此处添加此类的方法。
	private:
		CCalculator_cpp *ptr;
	};
}
