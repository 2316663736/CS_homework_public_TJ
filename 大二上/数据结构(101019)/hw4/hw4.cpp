#include<iostream>
#include<string>

using namespace std;
//����ת����ʽ��ÿ���ڵ�����ס�ұߵ�һ���ֵܽڵ����һ�����ӽڵ㣬��Ϊ�˷��㽨��ԭ���������ﻹ�Ѹ��ڵ���Ϊ��Ԫ�أ��ⲽҲ����ʹ��ջ����ɣ�d��ջ��u��ջ��
struct  tree {
	tree* first_child = NULL;
	tree* first_brother = NULL;

};


int cin_tree(tree* start_tree, string input)
{
	tree** stack =new(nothrow) tree* [input.size()];
	if (stack == NULL)
		return OVERFLOW;
	int top_stack = NULL;
	
	tree* now_tree=start_tree;

	int now_high = 0 , max_high = 0;
	for (int str = 0; input[str]; str++)
	{
		if (input[str] == 'd')
		{
			now_high++;
			//tree* father_tree;
			//now_tree = now_tree;
			if (now_tree->first_child == NULL) {
				now_tree->first_child = &start_tree[str+1];
			}
			else {
				tree* brother_tree = now_tree->first_child;

				while (brother_tree->first_brother)
					brother_tree = brother_tree->first_brother;

				brother_tree->first_brother = &start_tree[str+1];
			}
			stack[top_stack++] = now_tree;
			now_tree = &start_tree[str+1];
		}
		else if (input[str] == 'u')
		{
			now_high--;
			now_tree = stack[--top_stack];	
		}
		max_high = max(max_high, now_high);
	}
	delete[]stack;
	return max_high;
}

int er_cha_shu(tree* start_tree,string input)
{
	tree** queue = new(nothrow) tree * [input.size()];
	if (queue == NULL)
		return -1;
	int start = 0, end = 0;
	queue[end++] = start_tree;

	int high = -1;

	while (start != end)
	{
		high++;
		int tem_queue_num = end - start;

		for (int i_cycle = 0; i_cycle < tem_queue_num; i_cycle++)
		{
			tree* now_tree = queue[start++];

			if (now_tree->first_brother)
				queue[end++] = now_tree->first_brother;
			
			if (now_tree->first_child)
				queue[end++] = now_tree->first_child;
		}
	}
	delete[]queue;
	return high;
}

int main()
{
	int num = 1;
	string input;
	while (1)
	{
		cin >> input;
		if (input == "#")
			break;
		tree* the_tree = new tree[input.size()];
		if (the_tree == NULL)
			return OVERFLOW;
		int high_old, high_new;

		high_old = cin_tree(the_tree, input);
		high_new = er_cha_shu(the_tree, input);

		delete[]the_tree;
		cout << "Tree " << num++ << ": " << high_old << " => " << high_new << endl;
	}
}