#include <iostream>
#include "hash_cmp.h"
#include <string>

using namespace std;
int main()
{
    string input1, input2;
    cout << "输入第一个文件路径：" << endl;
    getline(cin, input1);
    cout << "输入第二个文件路径：" << endl;
    getline(cin, input2);
    FileHasher in1, in2;
    in1.computeHash(input1);
    in2.computeHash(input2);
    if (in1.compareHash(in2))
    {
        cout << "文件相同" << endl;
    }
    else
    {
        cout << "文件不同" << endl;
    }
    return 0;
}