#include <iostream>
#include "hash_cmp.h"
#include <string>
using namespace std;


// 如果要运行该测试文件，将下面那行取消注释，并将其他测试文件(以_test结尾)的这部分内容加上注释
// #define RUN_TEST



#ifdef RUN_TEST
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
#endif