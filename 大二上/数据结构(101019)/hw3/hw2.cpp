#include<iostream>
using namespace std;

int get_new_pri(char* operator_bool_stack, int top_operator_stack)
{
	for (int tem_top = top_operator_stack; tem_top > 0; --tem_top)
	{
		if (operator_bool_stack[tem_top - 1] != 'F' && operator_bool_stack[tem_top - 1] != 'V')
		{
			switch (operator_bool_stack[tem_top - 1])
			{
				case '!':
					return 4;
					break;
				case '&':
					return 3;
					break;
				case '|':
					return 2;
					break;
				case '(':
					return 1;
					break;
			}
		}
	}
	return 0;
}
/*����ֵΪ1����ɹ���ջ���ɼ������룬��֮����ջʧ�ܣ�����Ԫ����Ҫ��ջ��������*/
bool into_the_stack(char input, char* operator_bool_stack, int& top_operator_stack, bool &bool_or_not,int & pri_of_operate)
{
	if (input == 'F' || input == 'V')
	{
		operator_bool_stack[top_operator_stack++] = input;
		bool_or_not = true;
	}
	else
	{
		switch (input)
		{
			case '!'://���һ��������ջ�ģ���ʹǰ���ǣ����ߣ�
				operator_bool_stack[top_operator_stack++] = input;
				pri_of_operate = 4;
				bool_or_not = false;
				break;
			case '('://һ������ջ
				operator_bool_stack[top_operator_stack++] = input;
				pri_of_operate = 1;
				bool_or_not = false;
				break;
			case '&':
				if (pri_of_operate >= 3)
				  	return false;
				operator_bool_stack[top_operator_stack++] = input;
				pri_of_operate = 3;
				bool_or_not = false;
				break;
			case '|':
				if (pri_of_operate >= 2)
					return false;
				operator_bool_stack[top_operator_stack++] = input;
				pri_of_operate = 2;
				bool_or_not = false;
				break;
			case ')':
				if (operator_bool_stack[top_operator_stack - 1] == '(')
				{
					operator_bool_stack[--top_operator_stack] = '\0';
					bool_or_not = false;
					pri_of_operate = get_new_pri(operator_bool_stack, top_operator_stack);
				}
				else if ((operator_bool_stack[top_operator_stack - 1] == 'F' || operator_bool_stack[top_operator_stack - 1] == 'V')&&top_operator_stack >= 2 && operator_bool_stack[top_operator_stack - 2] == '(')
				{
					operator_bool_stack[top_operator_stack-2] = operator_bool_stack[top_operator_stack-1];
					top_operator_stack--;
					bool_or_not = true;
					pri_of_operate = get_new_pri(operator_bool_stack, top_operator_stack);
				}
				else 
					return false;
				//����������ţ����������Ž�ϣ���ȥ

				break;
		}

	}
	return true;
}

void out_the_stack(char* operator_bool_stack, int& top_operator_stack, bool& bool_or_not, int& pri_of_operate)
{
	char tem_operator, tem_bool_1, tem_bool_2;
	bool tem_1, tem_2,result=0;
	tem_bool_1 = operator_bool_stack[--top_operator_stack];
	if (tem_bool_1 == 'F')
		tem_1 = false;
	else
		tem_1 = true;
	tem_operator = operator_bool_stack[--top_operator_stack];
	if (tem_operator == '!')
	{
		result = !tem_1;
	}
	else if (tem_operator == '&')
	{
		tem_bool_2 = operator_bool_stack[--top_operator_stack];
		if (tem_bool_2 == 'F')
			tem_2 = false;
		else
			tem_2 = true;
		result = tem_1 && tem_2;
	}
	else if (tem_operator == '|')
	{
		tem_bool_2 = operator_bool_stack[--top_operator_stack];
		if (tem_bool_2 == 'F')
			tem_2 = false;
		else
			tem_2 = true;
		result = tem_1 || tem_2;
	}
	else {//��������˵�������������ģ������ų��ˣ�F/V/�������ܣ����Ϊ����ֵ�����������
		cout << "����";
		getchar();
	}
	char the_in;
	if (result)
		the_in = 'V';
	else
		the_in = 'F';
	operator_bool_stack[top_operator_stack++] = the_in;
	bool_or_not = true;
	pri_of_operate = get_new_pri(operator_bool_stack, top_operator_stack);

}

int main()
{
	int expression_no = 0;
	char operator_bool_stack[200] = { 0 };      //��Ϊ�������F/V�����100��
	bool bool_or_not = false;                 //��¼ǰһ���ǲ���F/V,������Ϊtrue���Һ���ΪF/V/(/!��������н������������expression
	int top_operator_stack = 0;           //ָ��ջ��ջ������һ��Ԫ��
	int pri_of_operator = 0;                //�����ջ��ջ��Ԫ�����ȼ���������м�
	//'('��ջǰ���ȼ�Ϊ5����ջ��Ϊ1,'('���ȼ�Ϊ0��һ��Ҫ�������Ž�ϲ��У��޷���ջ��'!'���ȼ�Ϊ4,'&'���ȼ�Ϊ3,'|'���ȼ�Ϊ2

	char tem_input;                   //��ʱ���������ַ�

	while (1)
	{
		if (cin >> tem_input)
		{
			if (bool_or_not && (tem_input == 'F' || tem_input == 'V'||tem_input=='!'||tem_input=='('))
			{
				//���н�����ȫ�����м���
				while(top_operator_stack>1)
					out_the_stack(operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator);
			}
			else
			{
				while (!into_the_stack(tem_input, operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator))
				{
					out_the_stack(operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator);
				}
				continue;

			}
		}
		else //����ΪEOF���˳�ѭ��
			break;

		cout << "Expression " << ++expression_no << ": " << operator_bool_stack[--top_operator_stack] << endl;
		into_the_stack(tem_input, operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator);
	}
	//�˳�ѭ���󣬽��м��㣬��������
	while (top_operator_stack > 1)
		out_the_stack(operator_bool_stack, top_operator_stack, bool_or_not, pri_of_operator);
	cout << "Expression " << ++expression_no << ": " << operator_bool_stack[--top_operator_stack] << endl;

	return 0;
}
