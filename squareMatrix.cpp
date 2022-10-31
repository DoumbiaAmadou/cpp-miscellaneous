#include <iostream>
using namespace std;
#include <vector>
#include <initializer_list>
#include <algorithm>

/**
 * Eg:
 * @brief
 *

	{1,1,1,1},
	{1,1,1,1},
	{1,1,1,0}
	} ;
 */
/*eg:
{   {0,0,0,0,0},
		{0,1,1,1,1},
		{0,1,1,1,1},
		{0,1,1,1,1},
		{0,1,1,1,1}
} ;
*/
class Solution
{

	int checkUp(int posI, int posJ, vector<vector<int>> &matrix)
	{
		int n = 0;
		bool end = false;
		while (!end)
		{
			n++;
			if (posI - n < 0 || posJ - n < 0)
				return n - 1;
			for (int i = 0; i <= n; i++)
			{
				end = matrix[posI - n][posJ - i] != 1 || matrix[posI - i][posJ - n] != 1;
				if (end)
					break;
			}
		}
		return n - 1;
	}

public:
	/**
	 * @brief Func countSquares :
	 * Count number  submatrix full to 1.
	 *
	 * @param matrix
	 * @return int  result
	 */
	int countSquares(vector<vector<int>> &matrix)
	{
		vector<vector<int>> a = matrix;
		int n = a.size(), m = a[0].size();

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (i * j != 0)
				{
					if (a[i][j] == 1)
					{
						a[i][j] = min({a[i - 1][j - 1], a[i - 1][j], a[i][j - 1]}) + 1;
					}
				}
			}
		}
		int ans = 0;
		for (auto x : a)
		{
			for (auto y : x)
			{
				if (y > ans)
					ans = y;
			}
		}

		return ans;
	}

	/**
	 * @brief Func maxSubSquare :
	 * Count number  submatrix full to 1.
	 * an another algorythm.
	 *
	 * @param matrix
	 * @return int  result
	 *
	 */
	int maxSubSquare(vector<vector<int>> &matrix)
	{
		int maxS = 0;

		{
			for (int i = 0; i < matrix.size(); i++)
				for (int j = 0; j < matrix[0].size(); j++)
				{

					if (matrix[i][j] == 1)
					{
						int res = 1 + checkUp(i, j, matrix);
						maxS = max(res, maxS);
					}
				}
		}
		return maxS;
	}
};

int main()
{
	vector<vector<int>> val = {{1, 1, 1, 1},
														 {1, 1, 1, 1},
														 {1, 1, 1, 0},
														 {1, 1, 1, 0}};

	Solution s;
	cout << "|solution1 => " << s.countSquares(val) << endl;
	cout << "|solution2 => " << s.maxSubSquare(val) << endl;
}
