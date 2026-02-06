#include <iostream>

using namespace std;

struct inflatable
{
    string name;
    float volume;
    double price;
};

class A
{
public:
    void Print()
    {
        cout << _a << endl;
    }

private:
    int _a;
};
class Date
{
public:
    Date(int year, int month, int day)
    {
        _year = year;
        _month = month;
        _day = day;
        cout << "带参数构造函数被调用\n";
    }
    Date()
    {
        _year = 0;
        _month = 0;
        _day = 0;
        cout << "无参构造函数被调用\n";
    }
    void Init(int year, int month, int day)
    {
        _year = year;
        _month = month;
        _day = day;
    }
    void Print()
    {
        cout << _year << "-" << _month << "-" << _day << endl;
    }

private:
    int _year;
    int _month;
    int _day;
};
int main()
{
    // Date d1(2022, 1, 11);
    // // Date d1 = Date(2022, 1, 11)
    // Date d2;
    // // Date d2 = Date();
    // d2.Init(2022, 1, 12);
    // d1.Print();
    // d2.Print();

    // A *p = nullptr;
    // p->Print();
    // return 0;

    inflatable hat1{"jack", 20.6, 39.35};
    inflatable hat2{};
    cout << hat1.name
         << " "
         << hat1.price
         << " "
         << hat1.volume << endl;
    cout << hat2.name
         << " "
         << hat2.price
         << " "
         << hat2.volume << endl;

    if (hat2.name == "")
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }
}
