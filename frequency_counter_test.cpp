#include "frequency_counter.h"
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>

using namespace std;

// �������������ڴ� std::string ת��Ϊ std::wstring
std::wstring string_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

int main() {
    cout << "������ԭʼ�ļ�·����" << endl;
    string inputPath;
    getline(cin, inputPath);  // ��ȡԭʼ�ļ�·��

    cout << "����������ļ�·����" << endl;
    string outputPath;
    getline(cin, outputPath);  // ��ȡ����ļ�·��

    // ��·��ת��Ϊ std::wstring
    wstring wInputPath = string_to_wstring(inputPath);
    wstring wOutputPath = string_to_wstring(outputPath);

    try {
        FrequencyCounter counter(wInputPath);  // ���� FrequencyCounter ʵ��
        counter.writeFrequency(wOutputPath);  // ��Ƶ�ʽ��д������ļ�

        cout << "�ַ�Ƶ����д���ļ�: " << outputPath << endl;
    }
    catch (const std::runtime_error& e) {
        cerr << "����: " << e.what() << endl;
    }

    return 0;
}
