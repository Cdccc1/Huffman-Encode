#include "frequency_counter.h"
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>
using namespace std;

// ���Ҫ���иò����ļ�������������ȡ��ע�ͣ��������������ļ�(��_test��β)���ⲿ�����ݼ���ע��
 // #define RUN_TEST

// �������������ڴ� std::string ת��Ϊ std::wstring
std::wstring string_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}


#ifdef RUN_TEST
int main() {
    cout << "������ԭʼ�ļ�·����" << endl;
    string inputPath;
    getline(cin, inputPath);  // ��ȡԭʼ�ļ�·��

    cout << "����������ļ�·����" << endl;
    string outputPath;
    getline(cin, outputPath);  // ��ȡ����ļ�·��

    try {
        FrequencyCounter counter(inputPath);  // ���� FrequencyCounter ʵ��
        counter.writeFrequency(outputPath);  // ��Ƶ�ʽ��д������ļ�

        cout << "�ַ�Ƶ����д���ļ�: " << outputPath << endl;
    }
    catch (const std::runtime_error& e) {
        cerr << "����: " << e.what() << endl;
    }

    return 0;
}
#endif
