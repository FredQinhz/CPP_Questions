#include <iostream>
#include <vector>

using namespace std;

void backtracking(int n, int k, int index, vector<int> &temp, vector<vector<int>> &result)
{
    if (temp.size() == k)
    {
        result.push_back(temp);
        return;
    }

    for (int i = index; i <= n; i++)
    {
        temp.push_back(i);
        backtracking(n, k, i + 1, temp, result);

        // 回溯
        if (!temp.empty())
        {
            temp.pop_back(); // 剪枝
        }
    }
}

int main()
{
    cout << "Please enter n, k: " << endl;
    int n, k;
    cin >> n >> k;
    vector<vector<int>> result;
    vector<int> temp;
    backtracking(n, k, 1, temp, result);
    cout << "The result is: " << endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout << '{';
        for (int j = 0; j < result[i].size(); j++)
        {
            if (j != result[i].size() - 1)
                cout << result[i][j] << ", ";
            else
                cout << result[i][j];
        }
        cout << '}' << endl;
    }
}
