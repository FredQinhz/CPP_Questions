#include <iostream>
#include <vector>

using namespace std;

void init(vector<int>& father){ // 初始化，每个元素的父亲是自己
    for(int i = 0; i < father.size(); i++)
        father[i] = i; 
}
int find(int u, vector<int>& father){ // 寻根过程
    if(u == father[u])
        return u;
    else
        return father[u] = find(father[u], father);
}
void join(int u, int v, vector<int>& father){ // 将v，u 这条边加入并查集
    int u_f = find(u, father);
    int v_f = find(v, father);
    if(u_f == v_f)
        return;
    father[v_f] = u_f;
}
bool check(int u, int v, vector<int>& father){ // 判断 u 和 v是否为同一个根
    int u_f = find(u, father);
    int v_f = find(v, father);
    return u_f == v_f;
}

int count_sets(vector<int>& father){ //计算集合的个数
	int cnt = 0;
	for (int i = 0; i < father.size(); i++)
		if (find(i, father) == i)
			cnt++;
	return cnt;
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> matrix[i][j];
           

    vector<int> father(n, 0); // 并查集
    init(father); // 初始化并查集
    for(int i = 0; i < n; i++){ //由于朋友关系无向性，遍历一半即可。
        for(int j = i + 1; j < n; j++){
            if(matrix[i][j])
                join(i, j, father); // 加入边
        }
    }

    cout << count_sets(father);
    return count_sets(father);
}
