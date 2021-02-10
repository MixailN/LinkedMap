#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
#include<iostream>
#include <cstdio>

using namespace std;


struct genius
{
	string key;
	string val;
	genius* prev;
	genius* next;
};

genius *tmp = NULL;


int HashFunc(string s)
{
	int hash = 0;
	/*for (int i = 0; i < s.size(); i++)
	{
		hash = (hash * 31 + s[i]) % 51913;
	}*/
	return hash;
}

void insert(string s1, string s2, vector<genius*>  table[])
{
	int hash = HashFunc(s1);
	for (int i = 0; i < table[hash].size(); i++)
	{
		if (table[hash][i]->key == s1)
		{
			table[hash][i]->val = s2;
			return;
		}
	}
	genius *put;
	*put = { s1, s2, tmp, NULL };
	table[hash].push_back(put);
	if (tmp == NULL)
	{
		tmp = table[hash].back();
	}
	else
	{
		tmp->next = table[hash].back();
		tmp = table[hash].back();
	}
}

void delete_v(string s1, vector<genius*>  table[])
{
	int hash = HashFunc(s1);
	for (int i = 0; i < table[hash].size(); i++)
	{
		if (table[hash][i]->key == s1)
		{
			if (table[hash][i]->next != NULL)
			{
				table[hash][i]->next->prev = table[hash][i]->prev;
			}
			if (table[hash][i]->prev != NULL)
			{
				table[hash][i]->prev->next = table[hash][i]->next;
			}
			if (tmp->key != table[hash][i]->key && tmp->key != table[hash].back()->key)
			{	
				if (table[hash][i]->key != table[hash].back()->key)
				{
					swap(table[hash][i], table[hash].back());
					if (table[hash][i]->prev != NULL)
					{
						table[hash][i]->prev->next = table[hash][i];
					}
					if (table[hash][i]->next != NULL)
					{
						table[hash][i]->next->prev = table[hash][i];
					}
				}
				table[hash].pop_back();
			}
			else
			{
				if (table[hash][i]->key != table[hash].back()->key)
				{
					if (tmp->key == table[hash][i]->key)
					{
						tmp = table[hash][i]->prev;
					}
					else
					{
						tmp = table[hash][i];
					}
					swap(table[hash][i], table[hash].back());
					if (table[hash][i]->prev != NULL)
					{
						table[hash][i]->prev->next = table[hash][i];
					}
					if (table[hash][i]->next != NULL)
					{
						table[hash][i]->next->prev = table[hash][i];
					}
				}
				else
				{
						tmp = table[hash][i]->prev;
				}
				table[hash].pop_back();
			}
			return;
		}
	}
}

string get_v(string s1, vector<genius*>  table[])
{
	int hash = HashFunc(s1);
	for (int i = 0; i < table[hash].size(); i++)
	{
		if (table[hash][i]->key == s1)
		{
			return table[hash][i]->val;
		}
	}
	return "none";
}

string prev_v(string s1, vector<genius*>  table[])
{
	int hash = HashFunc(s1);
	for (int i = 0; i < table[hash].size(); i++)
	{
		if (table[hash][i]->key == s1)
		{ 
			if (table[hash][i]->prev == NULL)
			{
				return "none";
			}
			else
			{
				return table[hash][i]->prev->val;
			}
		}
	}
	return "none";
}

string next_v(string s1, vector<genius*>  table[])
{
	int hash = HashFunc(s1);
	for (int i = 0; i < table[hash].size(); i++)
	{
		if (table[hash][i]->key == s1)
		{
			if (table[hash][i]->next == NULL)
			{
				return "none";
			}
			else
			{
				return table[hash][i]->next->val;
			}
		}
	}
	return "none";
}

int main()
{
	ios_base::sync_with_stdio(false);
	freopen("linkedmap.in", "r", stdin);
	freopen("linkedmap.out", "w", stdout);
	const int n = 3413;
	vector<genius*> ex[n];
	//vector<vector<genius> > ex(n);
	//vector<vector<genius> > ex(n, vector<genius>(100));
	string command, keys, value;
	while (cin >> command)
	{
		switch (command[0])
		{
			case 'p':
			{
				if (command == "prev")
				{
					cin >> keys;
					value = prev_v(keys, ex);
					cout << value << endl;
					break;
				}
				else
				{
					cin >> keys >> value;
					insert(keys, value, ex);
					break;
				}
			}
			case 'n':
			{
				cin >> keys;
				value = next_v(keys, ex);
				cout << value << endl;
				break;
			}
			case 'g':
			{
				cin >> keys;
				value = get_v(keys, ex);
				cout << value << endl;
				break;
			}
			case 'd':
			{
				cin >> keys;
				delete_v(keys, ex);
				break;
			}
		}
	}
	return 0;
}