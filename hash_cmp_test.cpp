#include <iostream>
#include "hash_cmp.h"
#include <string>

using namespace std;
int main()
{
    string input1, input2;
    cout << "�����һ���ļ�·����" << endl;
    getline(cin, input1);
    cout << "����ڶ����ļ�·����" << endl;
    getline(cin, input2);
    FileHasher in1, in2;
    in1.computeHash(input1);
    in2.computeHash(input2);
    if (in1.compareHash(in2))
    {
        cout << "�ļ���ͬ" << endl;
    }
    else
    {
        cout << "�ļ���ͬ" << endl;
    }
    return 0;
}