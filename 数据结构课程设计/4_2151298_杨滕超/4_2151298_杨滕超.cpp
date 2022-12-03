#include "4_2151298_杨滕超.h"

using namespace std;


/***************************************************************************
  函数名称：to_String
  功    能：将int数组转换为相应的String字符串
  输入参数：int num
  返 回 值：String
  说    明：
***************************************************************************/
String to_String(int num)
{
	String ans;
	while (num)
	{
		ans += num % 10 + '0';
		num /= 10;
	}
	ans.reverse();
	return ans;
}
//操作符优先级
/***************************************************************************
  函数名称：grage
  功    能：返回操作符的优先级
  输入参数：String& ch，String类型的操作符的引用
  返 回 值：int 操作符的优先级具体化为数字的大小
  说    明：
***************************************************************************/
inline int grade(String& ch) {
	if (ch == "(")
		return 5;
	else if (ch == "*" || ch == "/" || ch == "%")
		return 4;
	else if (ch == "+" || ch == "-")
		return 3;
	else
		return 2;
}

/***************************************************************************
  函数名称：isDigit
  功    能：判断一个字符是否是数字
  输入参数：const char& ch，字符
  返 回 值：bool，true表示为是数字，false表示不是数字
  说    明：
***************************************************************************/
inline bool isDigit(const char& ch) {
	return ch >= '0' && ch <= '9';
}
/***************************************************************************
  函数名称：isOp
  功    能：判断是否是合法操作符
  输入参数：const char& ch，字符
  返 回 值：bool，true表示为是合法操作符，false表示不是合法操作符
  说    明：
***************************************************************************/
inline bool isOp(const char& ch) {
	return ch == '(' || ch == '*' || ch == '/'
		|| ch == '%' || ch == '+' || ch == '-'
		|| ch == ')';
}


/***************************************************************************
  函数名称：valid
  功    能：判断表达式是否合法
  输入参数：const String& str，算术表达式
  返 回 值：bool，true表示为是合法表达式，false表示不是合法表达式
  说    明：0表示没有问题
*			1括号不匹配
*			2缺少操作符
*			3存在非法字符
*			4操作符冗余
***************************************************************************/
int valid(String& str)
{
	int len = str.length(), i = 0;
	int cnt = 0;//记录入栈的左括号的个数
	while (i < len)
	{
		if (str[i] == '(')//如果是左括号
			++cnt;//模拟入栈
		else if (str[i] == ')')//右括号与之前的左括号配对
		{
			if (cnt == 0)//没有左括号与之匹配
				return 1;
			--cnt;//模拟出栈
		}
		++i;
	}
	//找空格两边都是数字，就是少了
	i = 0;
	bool isNum = false;
	while (i < len)
	{
		//是数字或者是有符号的数字
		if (isDigit(str[i]) || ((str[i] == '+' || str[i] == '-') && i + 1 < len && isDigit(str[i + 1])))
		{
			if (str[i] == '+' || str[i] == '-')
				++i;//跳到数字取
			isNum = true;
			++i;
		}
		else if (isOp(str[i]))//是操作符标记为不是数字
		{
			isNum = false;
			++i;
		}
		else if (str[i] == ' ')
		{
			if (isNum)//之前是数字
			{
				int next = i + 1;
				for (; next < len; ++next)
				{
					if (isDigit(str[next]))//是数字，两个数字之间没有符号
						return 2;
					else if (isOp(str[next]))//是操作符跳出循环
						break;
					else//忽略空格，以及其他非+-*/的符号
						continue;
				}
				i = next;//跳到上述过程最后找的地方
			}
			else//空格前面不是数字跳过
				++i;
		}
		else//其他跳过
			++i;
	}
	//检查是否两个操作符连在一起
	bool isOperator = false;
	for (i = 0; i < len; ++i)
	{
		if (str[i] == '+' || str[i] == '-'
			|| str[i] == '/' || str[i] == '*' || str[i] == '%')
		{
			if (isOperator)
				return 4;
			isOperator = true;
		}
		else if (str[i] != ' ')
			isOperator = false;
	}
	//检查是否有非法符号
	for (i = 0; i < len; ++i)
	{
		if (str[i] == ' ')//空格ok
			++i;
		else if (isDigit(str[i]))//数字ok
			++i;
		else if (isOp(str[i]))//操作符也ok
			++i;
		else if (str[i] == '.' && i - 1 >= 0
			&& isDigit(str[i - 1])
			&& i + 1 < len && isDigit(str[i + 1]))//是小数点并且前后都有数字
			++i;
		else//不允许上述之外的东西存在了
			return 3;
	}

	if (cnt == 0)//栈空匹配完成
		return 0;
	else//左右括号不匹配
		return 1;
}
/***************************************************************************
  函数名称：cal
  功    能：通过后缀表达式计算表达式的值
  输入参数：String& str，后缀表达式
  返 回 值：Pair<double, bool>，第一个double表示计算结果
			第二个bool表示计算结果是否正确
  说    明：
***************************************************************************/
Pair<double, bool> cal(String& str)
{
	Stack<double> stk;
	double temp1 = 0, temp2 = 0;
	int i = 0, len = str.length() + 1;
	while (i < len)
	{
		//有操作数才看符号，对负号还需要判断后面不是数字
		if (!stk.empty() && (str[i] == '*' || str[i] == '/'
			|| str[i] == '+' || (str[i] == '-' && i + 1 < len && !isDigit(str[i + 1]))))
		{
			temp1 = stk.top();
			stk.pop();
			if (stk.empty())//只剩下一个操作数
			{
				if (str[i] == '-' || str[i] == '+')//如果是单目
					stk.emplace(-temp1);
				else
					return Pair<double, bool>(0, false);
			}
			else//有两个操作数
			{
				temp2 = stk.top();
				stk.pop();
				switch (str[i])
				{
					case '+':
						stk.emplace(temp2 + temp1);
						break;
					case '-':
						stk.emplace(temp2 - temp1);
						break;
					case '*':
						stk.emplace(temp2 * temp1);
						break;
					case '/':
						stk.emplace(temp2 / temp1);
						break;
					default:
						break;
				}
			}
			++i;
		}
		//是数字
		else if (isDigit(str[i]) || (str[i] == '-' && i + 1 < len && isDigit(str[i + 1])))
		{
			bool minus = false;
			if (str[i] == '-')//负数
			{
				minus = true;
				++i;
			}
			double sum = 0, help = 0.1;
			int cnt = 0;//记录位数
			const int MAX_N = 6;//有效数字取六位小数
			while (isDigit(str[i]))
			{
				sum = sum * 10 + str[i] - '0';
				++i;
				++cnt;
			}
			//如果有小数点
			if (str[i] == '.')
			{
				++i;//跳过这个小数点取后面的数字
				while (isDigit(str[i]) && i < len && cnt <= MAX_N)
				{
					sum += help * ((double)str[i] - '0');
					++i;
					++cnt;
					help /= 10;
				}
			}
			if (minus)//有负号了就取反
				sum = 0 - sum;
			stk.emplace(sum);
		}
		//是空格
		else
			++i;
	}
	return Pair<double, bool>(stk.top(), true);
}
//表达式转换函数
String ans;
/***************************************************************************
  函数名称：covert
  功    能：将中缀表达式转换为后转表达式，并记录于String类型的ans变量中
  输入参数：String& str，中缀表达式
  返 回 值：
  说    明：1.数字直接入栈
			2.符号优先级高的入栈，（ * / % + =
			3.遇到），符号依次弹出op，并且压入num，直到遇到左括号删除
			4.遍历完成，op中元素都压入num
***************************************************************************/
void convert(String& str)
{
	/*
	* 1.数字直接入栈
	* 2.符号优先级高的入栈，（ * / % + =
	* 3.遇到），符号依次弹出op，并且压入num，直到遇到左括号删除
	* 4.遍历完成，op中元素都压入num
	*/
	String s;
	Stack<String> op, num;
	//处理之前前去除所有空格
	str.erase(' ');
	int len = str.length() + 1, i = 0;

	while (i < len)
	{
		s = "";
		/*
		* 判断是负号还是减号
		* -前面是）or 数字 作为减号
		* -在第一个后面是（ 作为单目取反
		* 否则都是负号
		*/
		//如果是操作符
		if ((isOp(str[i]) && str[i] != '-' && str[i] != '+')
			|| ((str[i] == '-' || str[i] == '+') && i - 1 >= 0 && str[i - 1] == ')')
			|| ((str[i] == '-' || str[i] == '+') && i - 1 >= 0 && isDigit(str[i - 1]))
			|| ((str[i] == '-' || str[i] == '+') && i + 1 < len && str[i + 1] == '('))//取反
		{
			//栈中没有操作符直接放入
			if (op.empty())
			{
				s = str[i];
				op.emplace(s);
			}
			else//栈中有操作符，进行比较
			{
				String Op1 = "", Op2 = "";
				Op1 += str[i];
				int grade1 = grade(Op1);
				Op2 += op.top();
				int grade2 = grade(Op2);
				//栈中的左括号优先级最小
				if (Op2 == "(")
					grade2 = 0;

				//左括号的直接入栈
				if (Op1 == "(")
				{
					op.emplace(Op1);
				}
				//把括号中的符号放入num直到（
				else if (Op1 == ")")
				{
					while (!op.empty() && !(op.top() == "("))
					{
						ans += op.top();
						ans += ' ';
						op.pop();
					}
					//弹出与之匹配的左括号
					op.pop();
				}
				else//加减乘除
				{
					while (!op.empty() && grade1 <= grade2)
					{
						ans += op.top();
						ans += ' ';
						op.pop();

						if (op.empty())
							break;

						Op2 = "";
						Op2 += op.top();
						grade2 = grade(Op2);
						if (Op2 == "(")
							grade2 = 0;

					}
					op.emplace(Op1);
				}
			}
			++i;
		}
		//如果是数字
		else if (isDigit(str[i]) || str[i] == '-' || str[i] == '+')
		{
			//如果是作为负号
			if (str[i] == '-')
				s += str[i++];
			else if (str[i] == '+')//正号直接跳过
				++i;

			//把数字连起来
			while (isDigit(str[i]) && i < len)
			{
				s += str[i];
				++i;
			}
			//如果有小数点
			if (str[i] == '.')
			{
				s += str[i];
				++i;
				while (isDigit(str[i]) && i < len)
				{
					s += str[i];
					++i;
				}
			}
			ans += s;
			ans += ' ';
		}

		else//其他跳过
			++i;
	}
	//剩下操作符都加入
	while (!op.empty())
	{
		ans += op.top();
		ans += ' ';
		op.pop();
	}
	//删掉结尾空格
	while (ans.back() == ' ')
		ans.pop_back();
}
/***************************************************************************
  函数名称：show
  功    能：展示后缀表达式转换与计算函数是否正确
  输入参数：String str, double correctAns，中缀表达式和正确答案
  返 回 值：
  说    明：
***************************************************************************/
void show(String str, double correctAns)
{
	static int num = 1;
	ans.clear();
	convert(str);
	auto res = cal(ans);
	printf("%-8d%-28s%-28s", num, str.c_str(), ans.c_str());
	cout.width(16);
	cout << res.first;
	cout.width(16);
	cout << correctAns << endl;
	//cout << num << "\t" << str << "\t\t\t" << ans << "\t\t\t" << res.first << "\t" << correctAns << endl;
	++num;
}
int main() {
	cout << "序号\t表达式\t\t\t    后缀表达式\t\t\t\t    答案\t正确答案\n";
	//加减乘除小数负数
	show("22+3", 25);
	show("-1.7+2.4", 0.7);
	show("6-45/2", -16.5);
	show("8+2.8*23/23", 10.8);
	show("(-8+4.8)+3.2", 0);
	show("(2*100)/20", 10);
	show("-3*3.8", -11.4);
	show("0.7*2+23", 24.4);
	show("-(+23-3)*10/3+(-11/2)", -72.1667);


	//自己表达式测试
	cout << endl << "请输入表达式: " << endl;
	char buffer[defaultSizeString] = { '\0' };
	String temp;
	//可用于空格输入，标准输入
	fgets(buffer, defaultSizeString, stdin);
	temp = buffer;
	temp.pop_back();//去掉最后的\n
	if (temp == "\0")
		cout << "输入为空!" << endl;
	else
	{
		ans.clear();//清空之前
		//得到返回值
		int isValidRes = valid(temp);
		if (isValidRes == 0)
		{
			convert(temp);//求后缀表达式
			Pair<double, bool> res = cal(ans);
			if (res.second == false)//计算不成功
				cout << "表达式不规范，请重新输入" << endl;
			else
			{
				cout << "后缀表达式为：" << ans << endl;
				cout << "计算结果为：" << res.first << endl;
			}
		}
		else if (isValidRes == 1)
			cout << "表达式不规范，左右括号不匹配，请重新输入!" << endl;
		else if (isValidRes == 2)
			cout << "表达式不规范，缺少操作符，请重新输入!" << endl;
		else if (isValidRes == 3)
			cout << "表达式不规范，存在非法字符，请重新输入!" << endl;
		else if (isValidRes == 4)
			cout << "表达式不规范，操作符冗余，请重新输入" << endl;
	}


	//前面输入的回车已经读入无需跳过
	cout << endl << "回车键继续操作" << endl;
	cin.clear();
	cin.get();
	return 0;
} 
