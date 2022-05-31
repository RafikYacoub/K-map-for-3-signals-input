#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <set>
#include <map>

using namespace std;

struct min_term
{
	int decimal;
	int instances;
	string binary;
	bool taken;
};
struct min_term_prime
{
	int decimal, instances;
	bool prime;
};
struct min_term_2
{
	vector<int> decimal;
	string binary;
	bool taken;
};
struct min_term_4
{
	vector<int> decimal;
	string binary;
	bool taken;
};
int n_min;
vector <min_term> min_terms_vec;
vector <vector<int>> k_map(2, vector<int>(4, 0));
vector <vector<min_term>> NumberOfOnes(4);
vector <vector<min_term_2>> step1(3);
vector <vector<min_term_4>> step2(2);
vector <min_term> EPI;
vector <string> Essential;
map<string, vector<int>> EPIs;
vector <min_term_2> EPI2;
vector <min_term_4> EPI4;



void input_data()
{
	cout << "Enter the number of minterms: " << endl;

	cin >> n_min;
	while (n_min < -1 || n_min > 9)
	{
		cout << "invalid input!" << endl;
		cout << "Enter the number of minterms: " << endl;
		cin >> n_min;
	}

	if (n_min == 0)
	{
		cout << "f = 0" << endl;
		return;
	}
	else if (n_min == 8)
	{
		cout << "f = 1" << endl;
		return;
	}
	else
	{
		int counter_values = 0;
		int min_inpt;
		min_terms_vec.resize(n_min);
		cout << "Enter the minterms: " << endl;
		while (counter_values < n_min)
		{
			cin >> min_inpt;
			if (min_inpt > -1 && min_inpt < 8)
			{
				min_terms_vec[counter_values].decimal = min_inpt;
				min_terms_vec[counter_values].binary = bitset<3>(min_inpt).to_string();
				min_terms_vec[counter_values].taken = false;
				counter_values++;
			}
			else
			{
				cout << "Enter a valid input minterm from 0 to 7!" << endl;
			}
		}

	}
}
void k_initialize()
{
	if (n_min == 8)
	{
		k_map[0][0] = 1;
		k_map[1][0] = 1;
		k_map[0][1] = 1;
		k_map[1][1] = 1;
		k_map[0][3] = 1;
		k_map[1][3] = 1;
		k_map[0][2] = 1;
		k_map[1][2] = 1;
		return;
	}
	for (int i = 0; i < n_min; i++)
	{

		if (min_terms_vec[i].decimal == 0) { k_map[0][0] = 1; }
		if (min_terms_vec[i].decimal == 1) { k_map[1][0] = 1; }
		if (min_terms_vec[i].decimal == 2) { k_map[0][1] = 1; }
		if (min_terms_vec[i].decimal == 3) { k_map[1][1] = 1; }
		if (min_terms_vec[i].decimal == 4) { k_map[0][3] = 1; }
		if (min_terms_vec[i].decimal == 5) { k_map[1][3] = 1; }
		if (min_terms_vec[i].decimal == 6) { k_map[0][2] = 1; }
		if (min_terms_vec[i].decimal == 7) { k_map[1][2] = 1; }

	}



}
void print_kmap()
{
	cout << endl << "KMap: " << endl;
	cout << "AB" << '\t' << "00" << '\t' << "01" << '\t' << "11" << '\t' << "10" << endl;
	for (int i = 0; i < 2; i++)
	{
		cout << "C  " << i << '\t';
		for (int j = 0; j < 4; j++)
		{
			cout << k_map[i][j] << '\t';
		}
		cout << endl;
	}

}
void CountOnes()
{
	if (n_min == 0 || n_min == 8)
	{
		return;
	}
	int count = 0;
	for (int i = 0; i < n_min; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (min_terms_vec[i].binary[j] == '1')
				count++;
		}
		NumberOfOnes[count].push_back(min_terms_vec[i]);
		count = 0;
	}
}
void matching()
{
	if (n_min == 0 || n_min == 8)
	{
		return;
	}
	int count_diff = 0;
	int index, CountTrue = 0;
	for (int i = 0; i < NumberOfOnes.size() - 1; i++)
	{
		for (int j = 0; j < NumberOfOnes[i].size(); j++)
		{
			for (int k = 0; k < NumberOfOnes[i + 1].size(); k++)
			{
				for (int l = 0; l < 3; l++)
				{

					if (NumberOfOnes[i][j].binary[l] != NumberOfOnes[i + 1][k].binary[l])
					{
						count_diff++;
						index = l;
					}
				}
				if (count_diff == 1)
				{
					min_term_2 temp;
					temp.decimal.push_back(NumberOfOnes[i][j].decimal);
					temp.decimal.push_back(NumberOfOnes[i + 1][k].decimal);
					temp.binary = NumberOfOnes[i][j].binary;
					temp.binary[index] = '-';
					temp.taken = false;
					count_diff = 0;
					step1[i].push_back(temp);
					NumberOfOnes[i][j].taken = true;
					NumberOfOnes[i + 1][k].taken = true;
				}
				count_diff = 0;
			}

		}
	}

	for (int i = 0; i < NumberOfOnes.size(); i++)
	{
		for (int j = 0; j < NumberOfOnes[i].size(); j++)
		{

			if (NumberOfOnes[i][j].taken == false)
			{
				EPI.push_back(NumberOfOnes[i][j]);
				vector<int> temp;
				temp.push_back(NumberOfOnes[i][j].decimal);
				EPIs.insert(pair<string, vector<int>>(NumberOfOnes[i][j].binary, temp));
			}
			else
			{
				CountTrue++;
			}
		}
	}
	if (CountTrue == 0)
	{
		for (const auto k : step1)
			for (const auto l : k)
			{
				EPIs.insert(pair<string, vector<int>>(l.binary, l.decimal));
			}
		return;
	}
	count_diff = 0;
	CountTrue = 0;
	index = 0;

	// ==================================================== end of step 1


	for (int i = 0; i < step1.size() - 1; i++)
	{

		for (int j = 0; j < step1[i].size(); j++)
		{
			for (int k = 0; k < step1[i + 1].size(); k++)
			{

				for (int l = 0; l < 3; l++)
				{
					if (step1[i][j].binary[l] != step1[i + 1][k].binary[l])
					{
						count_diff++;
						index = l;
					}
				}
				if (count_diff == 1)
				{
					min_term_4 temp;
					temp.decimal.insert(temp.decimal.end(), step1[i][j].decimal.begin(), step1[i][j].decimal.end());
					temp.decimal.insert(temp.decimal.end(), step1[i + 1][k].decimal.begin(), step1[i + 1][k].decimal.end());
					temp.binary = step1[i][j].binary;
					temp.binary[index] = '-';
					temp.taken = false;
					count_diff = 0;
					step2[i].push_back(temp);
					step1[i][j].taken = true;
					step1[i + 1][k].taken = true;
				}
				count_diff = 0;
			}

		}
	}

	for (const auto i : step1)
	{
		for (const auto j : i)
		{
			if (j.taken == false)
			{
				EPI2.push_back(j);
				EPIs.insert(pair<string, vector<int>>(j.binary, j.decimal));
			}
			else
			{
				CountTrue++;
			}

		}

	}

	if (CountTrue == 0)
	{
		for (const auto k : step2)
			for (const auto l : k)
				EPIs.insert(pair<string, vector<int>>(l.binary, l.decimal));
		return;
	}
	count_diff = 0;
	CountTrue = 0;
	index = 0;
	for (const auto i : step2)
		for (const auto j : i)
			EPIs.insert(pair<string, vector<int>>(j.binary, j.decimal));
	// =================================== end of step 2
}
void result()
{
	if (n_min == 0 || n_min == 8)
		return;
	for (int i = 0; i < min_terms_vec.size(); i++)
	{
		for (auto j : EPIs)
			for (const auto k : j.second)
			{
				if (min_terms_vec[i].decimal == k)
				{
					min_terms_vec[i].instances++;
				}

			}
		if (min_terms_vec[i].instances == 1)
		{
			for (auto j : EPIs)
				for (auto k : j.second)
				{
					if (min_terms_vec[i].decimal == k)
					{
						if (find(Essential.begin(), Essential.end(), j.first) == Essential.end())
						{
							Essential.push_back(j.first);
						}
					}
				}
		}
	}
	int x = Essential.size();
	cout << endl << "simplified f= ";
	for (const auto i : Essential)
	{
		for (int j = 0; j < i.size(); j++)
		{
			if (j == 0)
			{
				if (i[j] == '0')
					cout << "A'";
				else if (i[j] == '1')
					cout << "A";
			}
			if (j == 1)
			{
				if (i[j] == '0')
					cout << "B'";
				else if (i[j] == '1')
					cout << "B";
			}
			if (j == 2)
			{
				if (i[j] == '0')
					cout << "C'";
				else if (i[j] == '1')
					cout << "C";
			}
		}
		if (x - 1 > 0)
		{
			cout << " + ";
			x--;
		}

	}
}



int main()
{
		input_data();
		k_initialize();
		print_kmap();
		CountOnes();
		matching();
		result();
}