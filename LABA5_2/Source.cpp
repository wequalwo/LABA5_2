#include <iostream>
#include <conio.h>

using std::cin;
using std::cout;
using std::endl;

struct Tree
{
	int a;
	Tree* right;
	Tree* left;
};

void deleting(Tree* my)
{
	if (my->left)
		deleting(my->left);
	if (my->right)
		deleting(my->right);
	delete my;
}

//TODO1: обработка ctrl+v;
//TODO2: полноценная обработка backspace;
int read(bool& inv)
{
	char stop;
	int value = 0;
	stop = _getch();
	bool sign = 0;
	if (stop == '-')
	{
		cout << "-";
		sign = 1;
	}
	else if ((int)stop >= 48 && (int)stop <= 57)
	{
		cout << stop;
		value = value * 10 + (stop - '0');
	}
	while (1)
	{
		stop = _getch();
		if ((int)stop >= 48 && (int)stop <= 57)
		{
			cout << stop;
			value = value * 10 + (stop - '0');
		}
		else if((int)stop == 13)
		{
			inv = 1;
			break;
		}
		else if ((int)stop == 8)
		{
			cout << "\b \b";
			value = (value - value % 10) / 10;
		}
		else if ((int)stop == 32)
		{
			cout << " ";
			break;
		}
	}
	if (sign)
		return -value;
	else
		return value;
}

void prefix(Tree*& my)
{
	if (my)
	{
		cout << my->a << " ";

		prefix(my->left);

		prefix(my->right);
	}
}
void infix(Tree*& my)
{
	if (my)
	{
		infix(my->left);
		cout << my->a << " ";

		infix(my->right);
	}
}
void postfix(Tree*& my)
{
	if (my)
	{
		postfix(my->left);
		postfix(my->right);
		cout << my->a << " ";
	}
}
int find(Tree*& my, int& fin)
{
	if (my)
	{
		if (fin > my->a)
		{
			cout << "Right\n";
			find(my->right, fin);
		}
		else if (fin < my->a)
		{
			cout << "Left\n";
			find(my->left, fin);
		}
		else
			return 1;
	}
	else
		return 0;
}

int menu()
{
	int n = 4;
	int choice = 'p';
	while (choice != 13)//пока не нажали enter
	{
		if (choice != 13)//не enter?
		{
			if (n == 4)
			{
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mSearch \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Prefix " << "  " << std::endl;
				std::cout << "  " << "Postfix" << "  " << std::endl;
				std::cout << "  " << "Infix  " << "  " << std::endl;
				std::cout << "  " << "Exit   " << "  " << std::endl;
				n = 0;
			}
			else if (n == 0)
			{
				std::cout << "  " << "Search " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mPrefix \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Postfix" << "  " << std::endl;
				std::cout << "  " << "Infix  " << "  " << std::endl;
				std::cout << "  " << "Exit   " << "  " << std::endl;
				n = 1;
			}
			else if (n == 1)
			{
				std::cout << "  " << "Search " << "  " << std::endl;
				std::cout << "  " << "Prefix " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mPostfix\x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Infix  " << "  " << std::endl;
				std::cout << "  " << "Exit   " << "  " << std::endl;
				n = 2;
			}
			else if (n == 2)
			{
				std::cout << "  " << "Search " << "  " << std::endl;
				std::cout << "  " << "Prefix " << "  " << std::endl;
				std::cout << "  " << "Postfix" << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mInfix  \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Exit   " << "  " << std::endl;
				n = 3;
			}
			else if (n == 3)
			{
				std::cout << "  " << "Search " << "  " << std::endl;
				std::cout << "  " << "Prefix " << "  " << std::endl;
				std::cout << "  " << "Postfix" << "  " << std::endl;
				std::cout << "  " << "Infix  " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mExit   \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				n = 4;
			}
		}
		std::cout << "\x1b[5A";
		choice = _getch();//считываем
		if (choice == 224)
		{
			choice = _getch();
			if (choice == 72)
			{
				n -= 2;
			}
			if (n < 0)
				n = 4;
		}
	}
	return n;
}

int main()
{
	Tree* root = new Tree;
	Tree* enter = root;
	bool inv = 0;
	root->a = read(inv);
	root->left = 0;
	root->right = 0;
	int val;

	while (!inv)
	{
		val = read(inv);
		while (1)
		{
			if (val > enter->a)
			{
				if (enter->right == 0)
				{
					enter->right = new Tree;
					enter->right->a = val;
					enter->right->right = 0;
					enter->right->left = 0;
					enter = root;
					break;
				}
				enter = enter->right;
			}
			else
			{
				if (enter->left == 0)
				{
					enter->left = new Tree;
					enter->left->a = val;
					enter->left->left = 0;
					enter->left->right = 0;
					enter = root;
					break;
				}
				enter = enter->left;
			}
		}

	}

	int switzch;
	cout << endl;
	while (true)
	{
		int switzch = menu();
		if (switzch == 0)
		{
			system("cls");
			int g = 0;
			cin >> g;
			if (find(root, g) > 0)
			{
				cout << "Found ";
			}
			else
			{
				cout << "Doesn't exist";
			}
		}
		else if (switzch == 1)
		{
			system("cls");
			prefix(root);
		}
		else if (switzch == 2)
		{
			system("cls");
			postfix(root);
		}
		else if (switzch == 3)
		{
			system("cls");
			infix(root);
		}
		else
		{
			system("cls");
			break;
		}
		cout << endl;
	}

	deleting(root);
	return 0;
}
//7 5 9 12 8 6 3