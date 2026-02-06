#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point
{
    int x, y, cost;
};

// 右、下、左、上
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool isValid(int x, int y, int m, int n, vector<vector<char>> &map)
{
    return x >= 0 && x < m && y >= 0 && y < n && map[x][y] != 'B';
}

int bfs(Point start, vector<vector<char>> &map, vector<vector<int>> &cost, Point target)
{
    int m = map.size(), n = map[0].size();
    queue<Point> q;
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

    q.push(start);
    dist[start.x][start.y] = start.cost;

    while (!q.empty())
    {
        Point p = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            if (isValid(nx, ny, m, n, map))
            {
                int newCost = p.cost + cost[nx][ny];
                if (newCost < dist[nx][ny])
                {
                    dist[nx][ny] = newCost;
                    q.push({nx, ny, newCost});
                }
            }
        }
    }

    return dist[target.x][target.y];
}

int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<char>> map(m, vector<char>(n));
    vector<vector<int>> cost(m, vector<int>(n, 0));
    Point start, end;
    vector<Point> checkpoints;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            string input;
            cin >> input;
            if (isdigit(input[0]))
            {
                cost[i][j] = stoi(input);
                map[i][j] = '0'; // Placeholder
            }
            else
            {
                map[i][j] = input[0];
                if (input[0] == 'S')
                {
                    start = {i, j, 0};
                }
                else if (input[0] == 'E')
                {
                    end = {i, j, 0};
                }
                else if (input[0] == 'C')
                {
                    checkpoints.push_back({i, j, 0});
                }
            }
        }
    }

    int minCost = INT_MAX;
    for (const auto &checkpoint : checkpoints)
    {
        int costToCheckpoint = bfs(start, map, cost, checkpoint);
        int costToEnd = bfs(checkpoint, map, cost, end);
        if (costToCheckpoint != INT_MAX && costToEnd != INT_MAX)
        {
            minCost = min(minCost, costToCheckpoint + costToEnd);
        }
    }

    cout << (minCost == INT_MAX ? -1 : minCost) << endl;

    return 0;
}