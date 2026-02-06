# 笔记
## leecode题目记录：
### 135. 分发糖果【***】
```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> candy(n, 0);

        // 两次遍历，左->右，保证右边的一定不小于左边的（即使分数比左边低）。
        candy[0] = 1;
        for(int i = 1; i < n; i++){
            if(ratings[i] > ratings[i - 1])
                candy[i] = candy[i - 1] + 1;
            else
                candy[i] = 1;
        }

        // 右->左，如果左边比右边分高，则(candy[i + 1] + 1, candy[i])取较大值
        for(int i = n - 2; i >= 0; i--){
            if(ratings[i] > ratings[i + 1]){
                candy[i] = max(candy[i + 1] + 1, candy[i]);
            }
        }

        int sum = 0;
        for(int i : candy)
            sum += i;
        return sum;
    }
};
```
### 42. 接雨水【***】
```cpp
class Solution{
public:
    int trap(vector<int> &height){
        int res = 0;
        int n = height.size();
        int waterFlag = false; // 当前状态是否可以装水【即是否在桶内】
        int maxHigh = 0;   // 当前左边最高柱子
        int waterHigh = 0; // 当前最高水位

        vector<int> rightMax(n, 0);
        for (int i = n - 2; i >= 0; i--) // 记录右边最高的柱子，限制最高水位 waterHigh
            rightMax[i] = max(rightMax[i + 1], height[i + 1]);
        
        for (int i = 0; i < n; i++){
            if (height[i] > maxHigh) // 更新左边最高柱子
                maxHigh = height[i];
            
            waterHigh = min(maxHigh, rightMax[i]); // 根据左边高度和右边高度来限制水位

            if (waterHigh > height[i])
                res += waterHigh - height[i]; 
        }
        return res;
    }
};
```
### 14. 最长公共前缀【*】
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 0)
            return "";

        //公共前缀比所有字符串都短，随便选一个先
        string prefix = strs[0];
        for (string s : strs) {
            while(!startsWith(prefix, s)){
                if(prefix.size() == 0)
                    return "";
                //公共前缀不匹配就让它变短！
                prefix = prefix.substr(0, prefix.size()-1);
            }
        }
        return prefix;
    }
    bool startsWith(string & str1, string & str2){ // str1 是否为 str2 的前缀
        int n1 = str1.size();
        int n2 = str2.size();
        if(n1 <= n2){
            string tmp = str2.substr(0, n1);
            if(str1 == tmp)
                return true;
            else 
                return false;
        }else{
            return false;
        }
    }
};
```
### 68. 文本左右对齐【***】
```cpp
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int n = words.size();
        string line;
        int line_l = 0;
        int idx_s = 0;
        for(int i = 0; i < n; i++){
            string tmp_s = words[i];
            int tmp_l = tmp_s.size();
            if((line_l + tmp_l) > maxWidth){
                line = processLine(idx_s, i, words, maxWidth);
                res.emplace_back(line);
                
                idx_s = i;
                line = tmp_s; // 删除并替换
                if(i != n - 1)
                    line += " ";
                line_l = line.size();
            }else if((line_l + tmp_l) == maxWidth){
                line += tmp_s;
                res.emplace_back(line);

                idx_s = i + 1;
                line = "";
                line_l = 0;
            }
            else{
                if(i != n - 1){
                    line += tmp_s + " ";
                    line_l = line.size();
                }else{
                    line += tmp_s;
                    line_l = line.size();
                }
            }
        }
        if(line_l != 0)
           res.emplace_back(line.append(maxWidth - line_l, ' '));
        return res;
    }

    string processLine(int idx_s, int idx_e, vector<string>& words, int maxWidth){
        int wordsCnt = idx_e - idx_s;
        int len = 0;
        for(int i = idx_s; i < idx_e; i++)
            len += words[i].size();

        int spaceCnt = maxWidth - len;
            if(wordsCnt == 1)
                return words[idx_s].append(spaceCnt, ' ');

        
        int spaceAvg = spaceCnt / (wordsCnt - 1);
        int spaceLeft = spaceCnt % (wordsCnt - 1);

        string res;
        for(int i = idx_s; i < idx_e; i++){
            if(i != idx_e - 1){
                res += words[i];
                res.append(spaceAvg, ' ');
                if(spaceLeft-- > 0){
                    res.append(" ");
                }
            }else{
                res += words[i];
            }
        }

        return res;
    }
};
```
### 11. 盛最多水的容器【**】
```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int max = 0;
        int left = 0;
        int right = height.size() - 1;
        while(left < right){
            int area = calArea(left, right, height);
            max = std::max(max, area);
            if(height[left] <= height[right]){ // 移动低的一边，这样面积才可能变大；移动高的一边的面积一定会变小。
                left++;
            }else{
                right--;
            }
        }
        return max;
    }
    int calArea(int idx1, int idx2, vector<int>& height){
        return (idx2 - idx1) * std::min(height[idx1], height[idx2]);
    }
};
```
### 15. 三数之和【**】
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end(), less<int>());
        int n = nums.size();

        // 枚举第一个数
        for(int first = 0; first < n; first++){
            if(nums[first] > 0) 
                return res;
            // 需要和上一个不同【相当于保证第一层不会重复】
            if(first > 0 && nums[first] == nums[first - 1])
                continue;
            
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;

            // 枚举第二个数
            for(int second = first + 1; second < n; second++){
                // 需要和上一个不同【相当于保证第二层不会重复】
                if(second > first + 1 && nums[second] == nums[second - 1])
                    continue;
                
                while(second < third && (nums[first] + nums[second] + nums[third] > 0)){
                    third--;
                }
                // 如果指针重合，那么这种情况不存在，结束这个循环
                if(second == third){
                    break;
                }
                if(nums[first] + nums[second] + nums[third] == 0){
                    res.emplace_back(vector<int>{nums[first], nums[second], nums[third]});
                }
            }
        }
        return res;
    }
};
```
### 209. 长度最小的子数组【**】
```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        int res = n + 1; // 结果最大只能是 n, 设为n + 1
        int sum = 0;
        int left = 0, right = 0;
        while(right < n){
            sum += nums[right];
            while(sum >= s){ // 说明目前right右边界最优，这时候优化左边。
                res = min(right - left + 1, res); 
                sum -= nums[left];
                left++; // 之所以左边能++，以left为边界的最优情况都考虑过了
            }
            right++;
        }
        return res == (n + 1) ? 0 : res;
    }
};
```
### 3. 无重复字符的字串【**】
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int res = 0;
        string subStr;
        int left = 0, right = 0;
        int pos = 0;
        while(right < n){
            pos = subStr.find(s[right]);  // 在原本不重复的字串里面寻找
            if(pos != string::npos){ // 如果新增的重复了
                subStr.erase(0, pos + 1); // 将重复的左边全部删除，裁掉 pos + 1 个元素
                left += pos + 1;  // 左指针相应移动 pos + 1
            }
            subStr += s[right];
            res = max(res, right - left + 1);
            right++;
        }
        return res;
    }
    /** 腾讯面试题，如若需要返回的是子串
    *   唯一性：如果有唯一性，则将left和right维护好就行
    *   不唯一：如果答案不唯一，可以使用栈的思想，满足一个就扔进去；出现更好的把之前的全部弹出来，再把最好的扔进去。
    */
};
```
### 30. 串联所有单词的子串【***】
```cpp
class Solution {
public:
    vector<int> findSubstring(string &s, vector<string> &words) {
        vector<int> res;         // 存储结果的数组
        int m = words.size();    // 单词数量
        int n = words[0].size(); // 单词长度
        int ls = s.size();       // 字符串 s 的长度
        for (int i = 0; i < n && i + m * n <= ls; i++) {  // 外层循环，从每个可能的起始位置 i 开始【i 属于 [0, ls % mn]】
            unordered_map<string, int> differ;  // 用于统计当前窗口内单词的出现次数
            // 初始化窗口（能容纳 m 个单词），分为两步
            // 1. 统计 s 中从当前起始位置 i 开始的 m 个单词
            for (int j = 0; j < m; j++) {
                ++differ[s.substr(i + j * n, n)];  // 将子串加入到 differ 中并计数
            }
            // 2. 遍历 words 中的每个单词，检查其在 differ 中的出现次数
            for (string &word: words) {
                if (--differ[word] == 0) {  // 如果单词的计数减为 0，则从 differ 中删除
                    differ.erase(word);
                }
            }

            // 内层循环，从起始位置 i 开始滑动窗口
            for (int start = i; start < ls - m * n + 1; start += n) { // 滑动到最后所剩不到一个窗口时停止
                if (start != i) {
                    // 添加新进入窗口的单词到 differ 中
                    string word = s.substr(start + (m - 1) * n, n);//窗口右边加的单词
                    if (++differ[word] == 0) {
                        differ.erase(word);
                    }
                    // 移除窗口左侧移出的单词
                    word = s.substr(start - n, n);
                    if (--differ[word] == 0) {
                        differ.erase(word);
                    }
                }
                // 如果 differ 为空，表示当前窗口符合要求，将起始位置加入结果数组 res
                if (differ.empty()) {
                    res.emplace_back(start);
                }
            }
        }
        return res;  // 返回所有符合要求的起始位置数组
    }
};
```
### 76. 最小覆盖子串【***】
```cpp
class Solution {
public:
    unordered_map<char, int> s_map, t_map;

    bool check(){
        for(auto p : t_map){
            if(s_map[p.first] < p.second)
                return false;
        }
        return true;
    }

    string minWindow(string s, string t) {
        int sl = s.size(), tl = t.size();
        string res;
        if(sl < tl)
            return res;
        // 初始化 t_map 哈希表
        for(char c : t)
            t_map[c]++;

        int left = 0, right = - 1; // 滑动窗口边界
        int resL = -1;      // 最终结果左边界
        int len = INT_MAX;  // 最终结果长度
        while(right < sl){
            if(t.find(s[++right]) != string::npos){ // s[right] 当前元素在 t 当中
                s_map[s[right]]++;
            }

            while(check() && left <= right){
                if(int tmp; (tmp = right - left + 1) < len){
                    len = tmp;
                    resL = left; 
                }

                if(t.find(s[left]) != string::npos){ // s[left] 当前元素在 t 当中
                    s_map[s[left]]--;
                }
                left++;
            }
        }
        
        if(resL != -1){
            res = s.substr(resL, len);
        }
        return res;
    }
};
```
### 909. 蛇梯棋(BFS)【**】
```cpp
class Solution {
public:
    pair<int, int> id2rc(int id, int n){
        int r = (id - 1) / n;
        int c = (id - 1) % n;
        if(r % 2 == 1) // 逆序的r
            c = n - 1 - c;
        return{n - 1 - r, c};
    }   
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        vector<int> vis(n * n + 1, 0); // 1 -> n 范围
        queue<pair<int,int>> q; // pair<id, steps>
        q.emplace(1, 0); 
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            // 枚举所有情况
            for(int i = 1; i <= 6; i++){
                // 得到下一步的格子
                int next_id = p.first + i;
                if(next_id > n * n){ // 超出边界
                    break;
                }
                auto next_rc = id2rc(next_id, n);

                if(int tmp = board[next_rc.first][next_rc.second]; tmp != -1){ // 遇到蛇 梯
                    next_id = tmp;
                    next_rc = id2rc(next_id, n);
                }
                
                // 处理
                if(next_id == n * n){ // 到达终点
                    return p.second + 1;
                }
                
                if(!vis[next_id]){ // 没走过
                    vis[next_id] = p.second + 1;
                    q.emplace(next_id, p.second + 1); 
                }else{ // 走过，比较步数
                    if(vis[next_id] > p.second + 1){
                        vis[next_id] = p.second + 1;
                        q.emplace(next_id, p.second + 1); 
                    }
                } 
            }
        }
        return -1;
    }
};
```
### 433. 最小基因变化 && 127. 单词接龙 (BFS)【***】
```cpp
class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        if(find(bank.begin(), bank.end(), endGene) == bank.end()) // 目标基因不在变异基因库里
            return -1;

        unordered_map<string, int> mutTimes; // map<变异基因, 变异次数>
        for(string str: bank){
            mutTimes.emplace(str, INT_MAX);
        }
        
        // 建立一个邻接表，用于优化枚举时间
        unordered_map<string, vector<string>> edges;
        for(int n = bank.size(), i = 0; i <= n; i++){
            string str;
            if(i != n)
                str = bank[i];
            else 
                str = startGene; // 不要忘记初始边

            vector<string> list;
            for(string edge: bank){
                if(edge != str){
                    int diff = 0;
                    for(int i = 0; i < str.size(); i++)
                        if(str[i] != edge[i])
                            diff++;
               
                    if(diff == 1)
                        list.emplace_back(edge);
                }
            } 
            edges.emplace(str, list);
        }
        
        
        queue<string> q;
        q.emplace(startGene);
        
        while(!q.empty()){
            string gene = q.front();
            q.pop();
            int steps = 0; // 当前基因的变异次数

            if(gene == startGene){ // 起始基因
                if(mutTimes.find(gene) != mutTimes.end()) // bank中找得到，原始基因无需经过变异就是一个变异基因，直接将置为0
                    mutTimes[gene] = 0;
            }else{ // 变异基因， 获取上一次变异次数
                steps = mutTimes[gene];
            }

            // 枚举所有可能变异情况
            for(string edge: edges[gene]){
                if(mutTimes[edge] >= (steps + 1)){ // 只有一处不同，并且变异次数比原来更少，允许变异
                    mutTimes[edge] = steps + 1; // 更新变异次数
                    q.emplace(edge);
                }
            }
        }
        return mutTimes[endGene] == INT_MAX ? -1 : mutTimes[endGene];
    }
};
```


## 代码随想录
> [代码随想录网站链接](programmercarl.com)

## C++ 结构体
### 创建结构步骤
- 定义struct结构
  ```c++
  /*关键字：struct*/
  struct Point{
      int x;
      int y;
      int cost;
  };
  ```
- 定义后创建变量，其中struct在c++中可以省略关键字struct，不会报错
  ```cpp
  Point p1;  // C++中，struct可省略
  struct Point p2; // c语言中
  ```
- **初始化**：使用由逗号分隔值列表，并将值用花括号括起来；
  ```cpp
  Point p1;
  p1 = {1, 2, 10};
  
  Point p2 = {3, 4, 11};
  Point p3 {5, 6, 12}; // 或者省略 =
  Point p4 {};  //大括号内不包含任何内容，各个成员都将设置为0，字符串string类型设置为空字符串 ""
  
  // 也能这样
  vector<Point> points;
  for(int i = 0; i < 3; i++)
     points.push_back({1, 1, 10});
  ```
- 使用成员运算符 `.` 来访问各个成员变量同时给变量进行赋值；

### 结构体声明的位置
- **外部声明**
  - 将结构体的声明放在main()的前面，外部声明可以被后面任何函数使用
- **内部声明**
  - 将结构体的声明放在main()函数中，紧跟在开始括号的后面，内部声明只能被该声明所属的函数使用，通常应使用外部声明，便于所有函数都可以使用这种类型的结构；
### 其他属性
- 可以将结构体**作为函数的参数传给函数**，同时**也可以将函数返回一个结构体**；
- 同时**可以使用赋值运算符** `=` 将结构体赋给另一个**同类型**的结构体（结构体中的每个成员都设置为另一个结构体中相应成员的值，称为成员赋值）
### 汇总
```cpp
#include<iostream>
using namespace std;
#include<string>//使用字符串要添加的头文件，不然报错
//定义结构体：结构体属于用户自定义的数据类型，允许用户存储不同的数据类型
//三种方式：
//1、struct 结构体名 变量名
//2、struct 结构体名 变量名 = {member1,member2,...}
//3、定义结构体时顺便创建变量
 
struct Student
{
    //将string类作为成员
	string name;
	int age;
	int score;
 
}s3; //创建结构体时创建了一个默认的s3结构变量
 
int main()
{
	//1、struct Student s1
	//给变量赋值，使用结构体变量名加.进行赋值
	struct Student s1;
	s1.name = "张三";
	s1.age = 19;
	s1.score = 90;
	cout << "姓名：" << s1.name << " 年龄：" << s1.age << " 分数：" << s1.score << endl;
 
	//2、 struct Student s2 = {....}
	struct Student s2 = { "李四",20,80 };
	cout << "姓名：" << s2.name << " 年龄：" << s2.age << " 分数：" << s2.score << endl;
 
	//3、在创建结构体的时候就创建了一个s3结构体变量
	s3.name = "王五";
	s3.age = 23;
	s3.score = 100;
	cout << "姓名：" << s3.name << " 年龄：" << s3.age << " 分数：" << s3.score << endl;
 
	system("pause");
	return 0;
}
```

## C++ 类
### C++中struct和class的区别是什么
- C++需要兼容C语言，所以C++中struct可以当成结构体使用。
- C++中struct还可以用来定义类。和class定义类是一样的，
- **struct**定义的类默认访问权限是**public**，**class**定义的类默认访问权限是**private**。

### 定义
声明和定义全部放在类体中，需注意：成员函数如果在类中定义，编译器可能会将其当成内联函数处理
```cpp
//声明和定义全部放在类体中
class Person{
public:
    Person(){ // 无参构造函数
    // todo
    } 
    Person(char* name, char* sex, int age){ // 带参构造函数
    // todo
    }
    void showinfo(){
        cout << "_name" << "_sex" << "_age" << endl;
    }
    ~Person(){
      // todo
    }
private:
    char *_name;
    char *_sex;
    int _age;
}
```
类声明放在.h文件中，成员函数定义放在.cpp文件中，注意：成员函数名前需要加类名 `::`
```cpp
//声明放在类的头文件person.h中
class Person{
public:
    void showinfo();
private:
    char *_name;
    char *_sex;
    int _age;
}

//定义放在类的实现文件person.cpp中
void Person::showinfo(){
    cout << "name:" << _name << endl;
}
```
### 类的实例化
#### 实例化
**用类类型创建对象的过程，称为类的实例化**
- 类是对对象进行描述的，是一个模型一样的东西，限定了类有哪些成员，定义出一个类并没有分配实际的内存空间来存储它
- 一个类可以实例化出多个对象，**实例化出的对象 占用实际的物理空间**
- `Person p;` 和 `Person p = Person();`都会调用**无参构造函数**
  - 前者直接声明并定义一个 Person 类的对象 person。根据情况，编译器会调用 Person 类的默认构造函数来初始化 person 对象。
  - 后者使用了复制初始化的方式来创建对象 person。右侧的 Person() 是一个临时对象，通过调用 Person 类的默认构造函数来创建。然后，使用复制初始化的语法将这个临时对象复制到 person 对象中。
- `Person p(name, sex, age);` 和 `Person p = Person(name, sex, age);` 都会调用**有参构造函数**
  
### `this`指针
- C++编译器给每个“**非静态的成员函数**“增加了一个**隐藏的指针参数**，让该指针指向当前对象(函数运行时调用该函数的对象)，在函数体中所有“成员变量”的操作，都是通过该指针去访问。只不过所有的操作对用户是透明的，即用户不需要来传递，**编译器自动完成**
- `this`指针特性：**this指针是形参，存在于栈桢中**
  - this指针的类型：类类型* const，即成员函数中，不能给this指针赋值，不能修改this指针。
  - 只能在“成员函数”的内部使用
  - this指针本质上是“成员函数”的形参，当对象调用成员函数时，将对象地址作为实参传递给this形参。所以对象中不存储this指针。
  - this指针是“成员函数”第一个隐含的指针形参，一般情况由编译器通过ecx寄存器自动传递，不需要用户传递
> 不能显示写this相关的实参和形参，但是可以在类中显式使用
#### 经典例子
```cpp
class A{
public:
    void Print()
    {
      cout << "Print()" << endl;
    }
private:
    int _a;
};
int main(){
    A* p = nullptr;
    p->Print();
    return 0;
}
```
如上例子，我们发现是可以**正常运行**的。
有人可能会说，这是空指针解引用，运行时报错。
p虽然是空指针，但是**Print函数地址不存在对象中**，这就**不是空指针的解引用**。
<br>

再看看这个例子
```cpp
class A{
public:
    void PrintA()
    {
      cout << _a << endl;
    }
private:
	  int _a;
};
int main()
{
    A* p = nullptr;
    p->PrintA();
    return 0;
}
```
能通过编译，但是会在**运行时报错**。
`cout << this->_a << endl;` 这句代码就变成了**空指针的解引用操作**了。`_a`是存在于对象中的。

## C++ 字符串string
### 初始化
- `string s1;` 默认初始化，是一个空串`""`。 
- `string s1(s2)` `string s1 = s2` s1 是 s2 的副本。
- `string s3("value")` `string s3 = "value"` s3 是字面值 "value" 的副本
- `string s4(n, 'c')` 把 s4 初始化为 n 个 字符 c 组成的串。
  
### 比较大小
```cpp
// 尽管两者的前面对应的字符都一样，但是phrase长度长（多一个空格），所以phrase>str。
string str = "Hello";
string phrase = "Hello ";
// thrase > str;

//这种情况比较的是第一个相异字符，根据ascii码比较，，因为 e < i，所以 str2 < phrase2。
string str2 = "Hello";
string phrase2 = "Hi ";
// str2 < phrase2
```

### 获取和处理string中的每个字符
- 使用下标运算符 `[]`
- 使用迭代器
  ```cpp
  string s = "Hello world!";
  for (auto it = s.begin(); it != s.end(); it++){ // std::string::iterator it;
	  cout << *it << ",";
  }
  cout << endl;
  ```
- 基于范围的 for
  ```cpp
  string str("some string");
  for (auto c : str)
	  cout << c << ",";
  cout << endl;
  ```
#### `substr` 成员函数
- std::string 类型的对象调用 substr 方法并**不会修改其自身内容**。相反，substr 方法会**返回一个新的 std::string 对象**，该对象包含了从原始字符串中指定位置开始的指定长度的子串。
```cpp
string s ("value");

string s2 = s.substr();//s2为”value”,大小为5

string s3 = s.substr(2);//s3为”lue”,大小为3
string s4 = s.substr(5);//s3为””,大小为0
string s5 = s.substr(6);//错误，s5的大小为pos = 5，小于s.size()

string s6 = s.substr(1,2);// s6为”al”,大小为2
string s7 = s.substr(1,7);// s7为”alue”,大小为4
string s8 = s.substr(5,7);// s8为””,大小为0
string s9 = s.substr(6,7);// 错误，s9的大小为pos = 5，小于s.size()
```

#### append() 追加方法
- 在字符串的末尾**添加字符串str**
  - `string& append (const string& str);`
  - `string& append (const char* s);`
  - 这种情况实际上就相当于 `+=`
- 在字符串的末尾添加字符串str的子串，子串以subpos索引开始，长度为sublen
  - `string& append (const string& str, size_t subpos, size_t sublen);`
    ```cpp
    string s1 = "hello";
    string s2 = "the world";
    s1.append(s2,4,5);  //把字符串从s2中从4开始的5个字符连接到当前字符串的结尾
    // 运行结果为：s1 = "helloworld";
    ```
  - 若是添加的子串中只有索引开始的位置，没有长度，则表示字符串从**第n个字符到末尾的字符连接到当前字符串末尾**【注意和char* 类型的区别！】，如下：
    ```cpp
    string s1 = "hello";
    string s2 = "the world";
    s1.append(s2, 3);
    // 运行结果为：s1 ="hello world"
    
    ```
- 在字符串的末尾添加字符串s中的前n个字符。
  - `string& append (const char* s, size_t n)`
  - 在string的后面添加C-string的一部分。把c类型字符串c的前n个字符连接到当前字符串结尾，如下：
    ```cpp
    string s = "hello";
    const char*c = "the world";
    s.append(c,3);
    // 运行结果为：s = "hellothe";
    ```
- 在字符串的末尾**添加n个字符c**;
  - string& append (size_t n, char c);
    ```cpp
    string s1 = "hello";
    s1.append(3, '!'); //在当前字符串结尾添加3个字符!
    // 运行结果为 s1 = "hello!!!";
    ```
- 在字符串的末尾添加以迭代器first和last表示的字符序列。
  - `string& append (InputIterator first, InputIterator last););
  `

#### insert() 插入方法
- `iterator insert(iterator pos, CharT ch)` 迭代器insert
  - 顺序容器通用的迭代器版本
    ```cpp
    string s1("value");
    s1.insert(s1.begin()++, 's'); //执行后，s1为"svalue"
    s1.insert(s1.begin(), 's');   //执行后，s1为"vsalue"
    ```
- `basic_string& insert(size_type index, size_type count, CharT ch)` 下标insert
  - 在下标index前插入count个字符ch
    ```cpp
    string s1("value");
    s1.insert(3, 2, 's'); //执行后，s1为"valssue"
    s1.insert(5, 2, 's'); //执行后，s1为"valuess"
    ```
- `basic_string& insert( size_type index, const CharT* s );`
- `basic_string& insert( size_type index, const basic_string& str );`
  - 在下标index前插入一个常量字符串或者string对象。
    ```cpp
    string s1("value");
    string s3 = "value";
    const char* cp = "value";
    
    s1.insert(0,s3); //执行完后，s1为"valuevalue"
    s1.insert(0,cp); //执行完后，s1为"valuevalue"
    ```

#### erase() 删除方法
三种形式
- `basic_string & erase(size_type pos=0, size_type n=npos)`
  - 如果string对象s调用，它**删除s从pos下标开始的n个字符**，并返回删除后的s。当`pos > s.size()`时，报错
- `iterator erase(const_iterator position)`
  - 如果string对象s调用，它删除s**迭代器position位置**的字符，并返回下一个字符的迭代器。
- `iterator erase(const_iterator position)`
  - 如果string对象s调用，它删除s**迭代器[first,last)区间**的字符，并返回last字符的迭代器。
  ```cpp
  string s1("value");
  string s2("value");
  string s3("value");
  string s4("value");
  
  s1.erase();            //执行后，s1为空
  s2.erase(0,2);         //执行后，s2为"lue"
  s3.erase(s3.begin());  //执行后，s3为"alue"
  s4.erase(s4.begin(),++s4.begin());//执行后，s4为"alue"
  ```
#### replace() 替换方法
- replace可看作是erase和insert的结合体，它删除指定的字符，删除后再插入指定的字符。
- 和insert一样，可以通过下标或者是迭代器指定位置。
```cpp
string s("i very love China!");
string str1 = "really";

// 将s从下标2开始删除5个字符，删除后在下标2插入str1
s.replace(2, 5, str1); // s="i really love China!"
// 将s从下标2开始删除6个字符，删除后在下标2插入str2从下标0开始的6个字符
s.replace(2, 6, str2, 0, 6); // s=""i really love China!"
// 将s从下标2开始删除6个字符，删除后在下标2插入4个’*’字符
s.replace(2, 6, 4, '*'); // s="i **** love China!"
```
#### 搜索操作

**函数形式**

| string搜索函数            | 描述                                              |
| ------------------------- | ------------------------------------------------- |
| s.find(args)              | 在s中查找第一次出现args的下标                     |
| s.rfind(args)             | 在s中查找最后一次出现args的下标                   |
| s.find_first_of(args)     | 在s中查找第一个在args中出现的字符，返回其下标     |
| s.find_first_not_of(args) | 在s中查找第一个不在args中出现的字符，返回其下标   |
| s.find_last_of(args)      | 在s中查找最后一个在args中出现的字符，返回其下标   |
| s.find_last_not_of(args)  | 在s中查找最后一个不在args中出现的字符，返回其下标 |

**args参数格式**

| args参数格式 | 描述                                                         |
| ------------ | ------------------------------------------------------------ |
| c,pos        | 搜索单个字符。从s中位置pos开始查找字符c。pos可省略，默认值为0 |
| s2,pos       | 搜索字符串。从s中位置pos开始查找字符串string对象s2。pos可省略，默认值为0 |
| cp,pos       | 搜索字符串。从s中位置pos开始查找指针cp指向的以空字符结尾的C风格字符串。pos可省略，默认值为0 |
| cp,pos,n     | 从s中位置pos开始查找指针cp指向的数组的前n个字符。            |


- 注意：`std::string::npos`是string类中定义的一个`std::size_t`类型变量，值为`std::size_t`类型的**最大值**。
```cpp
std::string str("There are two needles in this haystack with needles.");
std::string str2("needle");
// 对应参数 args为 (s2, po)
std::size_t found = str.find(str2); //返回第一个"needles" n的下标
if (found != std::string::npos)
	std::cout << "first 'needle' found at: " << found << '\n'; // 14


// 把str中的所有元音字母aeiou换成*。
std::string str("Please, replace the vowels in this sentence by asterisks.");
std::size_t found = str.find_first_of("aeiou");
while (found != std::string::npos)
{
	str[found] = '*';
	found = str.find_first_of("aeiou", found + 1);
}

std::cout << str << '\n';
```

#### compare操作
- 若 s = 指定的字符串，s.compare()返回 0
- 若 s > 指定的字符串，s.compare()返回正数
- 若 s < 指定的字符串，s.compare()返回负数
```cpp
string str1("green apple");
string str2("red apple");

// str1和str2比较：参数形式1
int res = str1.compare(str2); // str1 < str2，res < 0;
```

## C++ 查找方法
### `std::find()` 查找方法
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 查找值为 3 的元素
    auto it = std::find(vec.begin(), vec.end(), 3);

    if (it != vec.end()) {
        std::cout << "Element found at index: " << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    return 0;
}
```
### `std::find_if()` 自定义查找条件
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

bool isEven(int num) {
    return num % 2 == 0;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 查找偶数元素
    auto it = std::find_if(vec.begin(), vec.end(), isEven);

    if (it != vec.end()) {
        std::cout << "First even element found at index: " << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << "No even element found" << std::endl;
    }

    return 0;
}
```
### `std::count()` 统计元素个数
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 2, 2};

    // 统计值为 2 的元素个数
    int count = std::count(vec.begin(), vec.end(), 2);

    std::cout << "Number of 2s in vector: " << count << std::endl;

    return 0;
}
```


## C++ 手搓split()方法
- 以字符进行分割：
  ```cpp
  vector<string> Split(const string &s, const char &separator) {
      vector<string> ans;
      string tmp = "";
      for (int i = 0; i < s.size(); i++) {
          if (s[i] != separator) {
              tmp += s[i];
          }else {
              if(tmp != ""){
                  ans.push_back(tmp);
                  tmp = "";
              }  
          }
      }
      if(tmp != "")
          ans.push_back(tmp);
      return ans;
  }
  ```
- 以字符串进行分割：
  ```cpp
  vector<string> Split(const string &s, const string &separator) {
	  vector<string> ans;
	  string token, str = s;
	  size_t pos = 0;
	  while((pos = str.find(separator)) != string::npos) {
		  token = str.substr(0, pos);
          if(token != "")
		      ans.push_back(token);
		  str.erase(0, pos + separator.length());
	  }
      if(str != "")
	      ans.push_back(str);
	  return ans;
  }
  ```


## advance() 方法的使用
- advance() 函数用于**将迭代器**前进（或者后退）**指定长度的距离**。
- `void advance (InputIterator& it, Distance n);`
- **注意**：
  - advance() 函数本身不会检测 it 迭代器移动 n 个位置的可行性，如果 it 迭代器的移动位置超出了合理范围，it 迭代器的指向将无法保证，此时使用 *it 将会导致程序崩溃。
### 其成员函数
| 迭代器辅助函数        | 功能                                                                                           |
| --------------------- | ---------------------------------------------------------------------------------------------- |
| advance(it, n)        | it 表示某个迭代器，n 为整数。该函数的功能是将 it 迭代器前进或后退 n 个位置。                   |
| distance(first, last) | first 和 last 都是迭代器，该函数的功能是计算 first 和 last 之间的距离。                        |
| begin(cont)           | cont 表示某个容器，该函数可以返回一个指向 cont 容器中第一个元素的迭代器。                      |
| end(cont)             | cont 表示某个容器，该函数可以返回一个指向 cont 容器中最后一个元素之后位置的迭代器。            |
| prev(it)              | it 为指定的迭代器，该函数默认可以返回一个指向上一个位置处的迭代器。注意，it 至少为双向迭代器。 |
| next(it)              | it 为指定的迭代器，该函数默认可以返回一个指向下一个位置处的迭代器。注意，it 最少为前向迭代器。 |
### 示例
```cpp
#include <iostream>     // std::cout
#include <iterator>     // std::advance
#include <vector>
using namespace std;
 
vector<int> vec{ 1,2,3,4 };

vector<int>::iterator it = vec.begin();
advance(it, 2); // 输出 1、*it = 3
cout << "1、*it = " << *it << endl;

it = vec.end();
advance(it, -3);
cout << "2、*it = " << *it; // 输出 2、*it = 2
```

## BFS 广度优先搜索
### 一般过程
- 可以分为四个步骤：
  - 初始化（初始化队列和所求的值） -> 
  - 判空取队头（判断是否为空并取出队头） -> 
  - 拓展（利用队头去扩展） -> 
  - 判断入队（如果符合，将该点入队）。
    ```cpp
    void bfs(){
        queue<int>q;
        q.push(初始位置);
        //初始化
        
        while(q.size()){
            int t = q.front();
            q.pop();//取出队头的点，用该点向周围扩散。
            if(check(j)){       //如果该点可行就将它加入队列中
            q.psuh(j);		
            //实施相应的操作 
            }
        } 
    } 
    ```
- 如果是对图进行广度搜索，则可以建立一个邻接表，以优化枚举时间。 

## 并查集
并查集常用来解决**连通性**问题。当我们需要**判断两个元素是否在同一个集合里**的时候，我们就要想到用并查集。
- 主要有两个功能：
  - 将两个元素添加到一个集合中。
  - 判断两个元素在不在同一个集合
- 复杂度
  - 空间复杂度：O(n)，申请一个 father 数组
  - 时间复杂度：O(logn)~O(1)，随着查询或者合并操作的增加，时间复杂度会越来越趋于O(1)。
### 原理讲解
- 只需要用一个**一维数组**来表示。即：`father[A] = B, father[B] = C` 这样就表述 A 与 B 与 C连通了（有向连通图）。
- 寻根：**在同一个根下就是同一个集合**
- 初始化：father数组初始化的时候要 `father[i] = i`，默认自己指向自己。
- 注意！`join`方法一定是**先寻根，再关联**。不能简单调用`isSame`方法。
  ```cpp
    int n = 1005; // n根据题目中节点数量而定，一般比节点数量大一点就好
    vector<int> father = vector<int> (n, 0); // 数组结构
  
    // 并查集里寻根的过程
    int find(int u) {
        if (u == father[u]) return u; // 如果根就是自己，直接返回
        else return find(father[u]); // 如果根不是自己，就根据数组下标一层一层向下找
    }
  
    // 将v，u 这条边加入并查集
    void join(int u, int v) {
        u = find(u); // 寻找u的根
        v = find(v); // 寻找v的根
        if (u == v) return; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
        father[v] = u;
    }
  
    // 并查集初始化
    void init() {
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }
  
    // 判断 u 和 v是否找到同一个根
    bool isSame(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
  ```

### 路径压缩
在实现 find 函数的过程中，我们知道，通过**递归**的方式，不断获取father数组下标对应的数值，最终找到这个集合的根。
搜索过程像是一个多叉树中从叶子到根节点的过程。
如果这棵多叉树**高度很深**的话，每次 find 函数去寻找根的过程就要**递归很多次**。
- 我们的目的只需要知道这些节点在同一个根下就可以。
- 除了根节点其他所有节点**都挂载根节点下**，这样我们在寻根的时候就很快，只需要一步。
- **路径压缩**，将非根节点的所有节点直接指向根节点。
- 只需要在递归的过程中，让 `father[u]` 接住 递归函数 `find(father[u])` 的返回结果。

**代码实现**：
```cpp
// 并查集里寻根的过程
int find(int u) {
    if (u == father[u]) return u;
    else return father[u] = find(father[u]); // 路径压缩
}
```
