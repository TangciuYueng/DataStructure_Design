#include "4_2151298_������.h"

using namespace std;


/***************************************************************************
  �������ƣ�to_String
  ��    �ܣ���int����ת��Ϊ��Ӧ��String�ַ���
  ���������int num
  �� �� ֵ��String
  ˵    ����
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
//���������ȼ�
/***************************************************************************
  �������ƣ�grage
  ��    �ܣ����ز����������ȼ�
  ���������String& ch��String���͵Ĳ�����������
  �� �� ֵ��int �����������ȼ����廯Ϊ���ֵĴ�С
  ˵    ����
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
  �������ƣ�isDigit
  ��    �ܣ��ж�һ���ַ��Ƿ�������
  ���������const char& ch���ַ�
  �� �� ֵ��bool��true��ʾΪ�����֣�false��ʾ��������
  ˵    ����
***************************************************************************/
inline bool isDigit(const char& ch) {
	return ch >= '0' && ch <= '9';
}
/***************************************************************************
  �������ƣ�isOp
  ��    �ܣ��ж��Ƿ��ǺϷ�������
  ���������const char& ch���ַ�
  �� �� ֵ��bool��true��ʾΪ�ǺϷ���������false��ʾ���ǺϷ�������
  ˵    ����
***************************************************************************/
inline bool isOp(const char& ch) {
	return ch == '(' || ch == '*' || ch == '/'
		|| ch == '%' || ch == '+' || ch == '-'
		|| ch == ')';
}


/***************************************************************************
  �������ƣ�valid
  ��    �ܣ��жϱ��ʽ�Ƿ�Ϸ�
  ���������const String& str���������ʽ
  �� �� ֵ��bool��true��ʾΪ�ǺϷ����ʽ��false��ʾ���ǺϷ����ʽ
  ˵    ����0��ʾû������
*			1���Ų�ƥ��
*			2ȱ�ٲ�����
*			3���ڷǷ��ַ�
*			4����������
***************************************************************************/
int valid(String& str)
{
	int len = str.length(), i = 0;
	int cnt = 0;//��¼��ջ�������ŵĸ���
	while (i < len)
	{
		if (str[i] == '(')//�����������
			++cnt;//ģ����ջ
		else if (str[i] == ')')//��������֮ǰ�����������
		{
			if (cnt == 0)//û����������֮ƥ��
				return 1;
			--cnt;//ģ���ջ
		}
		++i;
	}
	//�ҿո����߶������֣���������
	i = 0;
	bool isNum = false;
	while (i < len)
	{
		//�����ֻ������з��ŵ�����
		if (isDigit(str[i]) || ((str[i] == '+' || str[i] == '-') && i + 1 < len && isDigit(str[i + 1])))
		{
			if (str[i] == '+' || str[i] == '-')
				++i;//��������ȡ
			isNum = true;
			++i;
		}
		else if (isOp(str[i]))//�ǲ��������Ϊ��������
		{
			isNum = false;
			++i;
		}
		else if (str[i] == ' ')
		{
			if (isNum)//֮ǰ������
			{
				int next = i + 1;
				for (; next < len; ++next)
				{
					if (isDigit(str[next]))//�����֣���������֮��û�з���
						return 2;
					else if (isOp(str[next]))//�ǲ���������ѭ��
						break;
					else//���Կո��Լ�������+-*/�ķ���
						continue;
				}
				i = next;//����������������ҵĵط�
			}
			else//�ո�ǰ�治����������
				++i;
		}
		else//��������
			++i;
	}
	//����Ƿ���������������һ��
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
	//����Ƿ��зǷ�����
	for (i = 0; i < len; ++i)
	{
		if (str[i] == ' ')//�ո�ok
			++i;
		else if (isDigit(str[i]))//����ok
			++i;
		else if (isOp(str[i]))//������Ҳok
			++i;
		else if (str[i] == '.' && i - 1 >= 0
			&& isDigit(str[i - 1])
			&& i + 1 < len && isDigit(str[i + 1]))//��С���㲢��ǰ��������
			++i;
		else//����������֮��Ķ���������
			return 3;
	}

	if (cnt == 0)//ջ��ƥ�����
		return 0;
	else//�������Ų�ƥ��
		return 1;
}
/***************************************************************************
  �������ƣ�cal
  ��    �ܣ�ͨ����׺���ʽ������ʽ��ֵ
  ���������String& str����׺���ʽ
  �� �� ֵ��Pair<double, bool>����һ��double��ʾ������
			�ڶ���bool��ʾ�������Ƿ���ȷ
  ˵    ����
***************************************************************************/
Pair<double, bool> cal(String& str)
{
	Stack<double> stk;
	double temp1 = 0, temp2 = 0;
	int i = 0, len = str.length() + 1;
	while (i < len)
	{
		//�в������ſ����ţ��Ը��Ż���Ҫ�жϺ��治������
		if (!stk.empty() && (str[i] == '*' || str[i] == '/'
			|| str[i] == '+' || (str[i] == '-' && i + 1 < len && !isDigit(str[i + 1]))))
		{
			temp1 = stk.top();
			stk.pop();
			if (stk.empty())//ֻʣ��һ��������
			{
				if (str[i] == '-' || str[i] == '+')//����ǵ�Ŀ
					stk.emplace(-temp1);
				else
					return Pair<double, bool>(0, false);
			}
			else//������������
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
		//������
		else if (isDigit(str[i]) || (str[i] == '-' && i + 1 < len && isDigit(str[i + 1])))
		{
			bool minus = false;
			if (str[i] == '-')//����
			{
				minus = true;
				++i;
			}
			double sum = 0, help = 0.1;
			int cnt = 0;//��¼λ��
			const int MAX_N = 6;//��Ч����ȡ��λС��
			while (isDigit(str[i]))
			{
				sum = sum * 10 + str[i] - '0';
				++i;
				++cnt;
			}
			//�����С����
			if (str[i] == '.')
			{
				++i;//�������С����ȡ���������
				while (isDigit(str[i]) && i < len && cnt <= MAX_N)
				{
					sum += help * ((double)str[i] - '0');
					++i;
					++cnt;
					help /= 10;
				}
			}
			if (minus)//�и����˾�ȡ��
				sum = 0 - sum;
			stk.emplace(sum);
		}
		//�ǿո�
		else
			++i;
	}
	return Pair<double, bool>(stk.top(), true);
}
//���ʽת������
String ans;
/***************************************************************************
  �������ƣ�covert
  ��    �ܣ�����׺���ʽת��Ϊ��ת���ʽ������¼��String���͵�ans������
  ���������String& str����׺���ʽ
  �� �� ֵ��
  ˵    ����1.����ֱ����ջ
			2.�������ȼ��ߵ���ջ���� * / % + =
			3.���������������ε���op������ѹ��num��ֱ������������ɾ��
			4.������ɣ�op��Ԫ�ض�ѹ��num
***************************************************************************/
void convert(String& str)
{
	/*
	* 1.����ֱ����ջ
	* 2.�������ȼ��ߵ���ջ���� * / % + =
	* 3.���������������ε���op������ѹ��num��ֱ������������ɾ��
	* 4.������ɣ�op��Ԫ�ض�ѹ��num
	*/
	String s;
	Stack<String> op, num;
	//����֮ǰǰȥ�����пո�
	str.erase(' ');
	int len = str.length() + 1, i = 0;

	while (i < len)
	{
		s = "";
		/*
		* �ж��Ǹ��Ż��Ǽ���
		* -ǰ���ǣ�or ���� ��Ϊ����
		* -�ڵ�һ�������ǣ� ��Ϊ��Ŀȡ��
		* �����Ǹ���
		*/
		//����ǲ�����
		if ((isOp(str[i]) && str[i] != '-' && str[i] != '+')
			|| ((str[i] == '-' || str[i] == '+') && i - 1 >= 0 && str[i - 1] == ')')
			|| ((str[i] == '-' || str[i] == '+') && i - 1 >= 0 && isDigit(str[i - 1]))
			|| ((str[i] == '-' || str[i] == '+') && i + 1 < len && str[i + 1] == '('))//ȡ��
		{
			//ջ��û�в�����ֱ�ӷ���
			if (op.empty())
			{
				s = str[i];
				op.emplace(s);
			}
			else//ջ���в����������бȽ�
			{
				String Op1 = "", Op2 = "";
				Op1 += str[i];
				int grade1 = grade(Op1);
				Op2 += op.top();
				int grade2 = grade(Op2);
				//ջ�е����������ȼ���С
				if (Op2 == "(")
					grade2 = 0;

				//�����ŵ�ֱ����ջ
				if (Op1 == "(")
				{
					op.emplace(Op1);
				}
				//�������еķ��ŷ���numֱ����
				else if (Op1 == ")")
				{
					while (!op.empty() && !(op.top() == "("))
					{
						ans += op.top();
						ans += ' ';
						op.pop();
					}
					//������֮ƥ���������
					op.pop();
				}
				else//�Ӽ��˳�
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
		//���������
		else if (isDigit(str[i]) || str[i] == '-' || str[i] == '+')
		{
			//�������Ϊ����
			if (str[i] == '-')
				s += str[i++];
			else if (str[i] == '+')//����ֱ������
				++i;

			//������������
			while (isDigit(str[i]) && i < len)
			{
				s += str[i];
				++i;
			}
			//�����С����
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

		else//��������
			++i;
	}
	//ʣ�²�����������
	while (!op.empty())
	{
		ans += op.top();
		ans += ' ';
		op.pop();
	}
	//ɾ����β�ո�
	while (ans.back() == ' ')
		ans.pop_back();
}
/***************************************************************************
  �������ƣ�show
  ��    �ܣ�չʾ��׺���ʽת������㺯���Ƿ���ȷ
  ���������String str, double correctAns����׺���ʽ����ȷ��
  �� �� ֵ��
  ˵    ����
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
	cout << "���\t���ʽ\t\t\t    ��׺���ʽ\t\t\t\t    ��\t��ȷ��\n";
	//�Ӽ��˳�С������
	show("22+3", 25);
	show("-1.7+2.4", 0.7);
	show("6-45/2", -16.5);
	show("8+2.8*23/23", 10.8);
	show("(-8+4.8)+3.2", 0);
	show("(2*100)/20", 10);
	show("-3*3.8", -11.4);
	show("0.7*2+23", 24.4);
	show("-(+23-3)*10/3+(-11/2)", -72.1667);


	//�Լ����ʽ����
	cout << endl << "��������ʽ: " << endl;
	char buffer[defaultSizeString] = { '\0' };
	String temp;
	//�����ڿո����룬��׼����
	fgets(buffer, defaultSizeString, stdin);
	temp = buffer;
	temp.pop_back();//ȥ������\n
	if (temp == "\0")
		cout << "����Ϊ��!" << endl;
	else
	{
		ans.clear();//���֮ǰ
		//�õ�����ֵ
		int isValidRes = valid(temp);
		if (isValidRes == 0)
		{
			convert(temp);//���׺���ʽ
			Pair<double, bool> res = cal(ans);
			if (res.second == false)//���㲻�ɹ�
				cout << "���ʽ���淶������������" << endl;
			else
			{
				cout << "��׺���ʽΪ��" << ans << endl;
				cout << "������Ϊ��" << res.first << endl;
			}
		}
		else if (isValidRes == 1)
			cout << "���ʽ���淶���������Ų�ƥ�䣬����������!" << endl;
		else if (isValidRes == 2)
			cout << "���ʽ���淶��ȱ�ٲ�����������������!" << endl;
		else if (isValidRes == 3)
			cout << "���ʽ���淶�����ڷǷ��ַ�������������!" << endl;
		else if (isValidRes == 4)
			cout << "���ʽ���淶�����������࣬����������" << endl;
	}


	//ǰ������Ļس��Ѿ�������������
	cout << endl << "�س�����������" << endl;
	cin.clear();
	cin.get();
	return 0;
}