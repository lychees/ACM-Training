// ��̬�滮���LCS����
#include <iostream>
#include <string>
#include <vector>
using namespace std;


/**
 * ����X[0...m-1]��Y[0...n-1]��LCS�ĳ���
 */
int lcs(string &X, string &Y, int m, int n)
{
	// ��̬�滮����С(m+1)*(n+1)
	vector<vector<int>> table(m+1,vector<int>(n+1));

	for(int i=0; i<m+1; ++i)
	{
		for(int j=0; j<n+1; ++j)
		{
			// ��һ�к͵�һ����0
			if (i == 0 || j == 0)
				table[i][j] = 0;
			else if(X[i-1] == Y[j-1])
				table[i][j] = table[i-1][j-1] + 1;
			else
				table[i][j] = max(table[i-1][j], table[i][j-1]);
		}
	}

	return table[m][n];
}

int main()
{
	string X = "ABCBDAB";
	string Y = "BDCABA";

	cout << "The length of LCS is " << lcs(X, Y, X.length(), Y.length());
	cout << endl;

	getchar();
	return 0;
}
