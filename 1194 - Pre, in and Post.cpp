#include<iostream>
#include<string>
using namespace std;

int index;

void find_post_order(int left,int right, string pre_order, string in_order)
{
	if (left <= right)
	{
		int j;
		for (j = left; j <= right; ++j) // find root in in order tree
			if (in_order[j] == pre_order[index]) break;

		if (j != right + 1)
		{
			index++;
			find_post_order(left, j - 1, pre_order, in_order); //for left subtree
			find_post_order(j + 1, right, pre_order, in_order); // for right subtree
			cout << in_order[j];
		}
	}
	else return;
}

int main()
{

	int test_cases, length,left,right;
	string pre_order, in_order;
	cin >> test_cases;
	while (test_cases--)
	{
		cin >> length >> pre_order >> in_order;
		index = 0;
		find_post_order(0, length-1, pre_order, in_order);

		cout << endl;
	}

	return 0;
}