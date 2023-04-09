#include<iostream>
#include <algorithm>
using namespace std;
const int num = 4;
const int stamps = 300; // 邮票种类数

bool tie, none;    // 由题意不言而喻
int total;         // 当前组合的邮票张数
int types;         // 每组测试（第一行）的邮票种类数
int end_comb_num;  // 每位顾客最终输出的组合的邮票张数
int customer;      // 每位顾客所需的面值
int now[num];      // 存储当前符合条件的组合
int end_comb[num]; // 存储最终结果组合
int stamp[stamps]; // 存储每种邮票的面值

int get_type(int a[], int n)
{ // 获取组合的种类
    if (n == 0)
        return 0;
    int type = 1;
    sort(a, a + n);
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] != a[i + 1])
            type++;
    }
    return type;
}

int get_max(int a[], int n)
{ // 获取组合中最大的那个数的值
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (max < stamp[a[i]])
            max = stamp[a[i]];
    }
    return max;
}

void compare()
{ // 比较两个组合，选取最优组合存储
    int now_types = get_type(now, total);
    int end_comb_types = get_type(end_comb, end_comb_num);
    int now_max = get_max(now, total);
    int end_comb_max = get_max(end_comb, end_comb_num);
    if (end_comb_num == 0 || (now_types > end_comb_types) || (now_types == end_comb_types && total < end_comb_num) ||
        (now_types == end_comb_types && total == end_comb_num && now_max > end_comb_max))
    { // 判断条件
        tie = false;
        end_comb_num = total;
        for (int i = 0; i < total; i++)
            end_comb[i] = now[i];
    }
    if (now_types == end_comb_types && total == end_comb_num && now_max == end_comb_max)
    {
        tie = true;
    }
}

void dfs(int n, int value)
{ // 遍历所有合法组合
    if (value > customer)
        return;
    if (value == customer)
    {
        none = true;
        compare();
    }
    if (total == 4)
        return;
    for (int i = n; i < types; i++)
    {
        now[total] = i;
        total++;
        dfs(i, value + stamp[i]);
        total--;
    }
}

void print()
{ // 输出函数
    cout << customer << ' ';
    if (none == false)
    {
        cout << "---- none" << endl;
    }
    else
    {
        cout << '(' << get_type(end_comb, end_comb_num) << "): ";
        if (tie == true)
            cout << "tie" << endl;
        else
        {
            sort(end_comb, end_comb + end_comb_num);
            for (int i = 0; i < end_comb_num; i++)
                cout << stamp[end_comb[i]] << ' ';
            cout << endl;
        }
    }
}
int main()
{
    int n;
    while (cin >> n)
    {
        types = 0;
        while (n != 0)
        {
            stamp[types++] = n;
            cin >> n;
        }
        sort(stamp, stamp + types);
        cin >> customer;
        while (customer != 0)
        {
            total = 0;
            end_comb_num = 0;
            none = false;
            tie = true;
            dfs(0, 0);
            if (none == true)
            {
                sort(end_comb, end_comb + end_comb_num);
            }
            print();
            cin >> customer;
        }
    }
    return 0;
}