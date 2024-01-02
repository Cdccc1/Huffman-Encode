#include <iostream>
#include <string>
#include "compressor.h"
#include "h_priority_queue.h"
#include <locale>
#include <codecvt>

using namespace std;
// ���Ҫ���иò����ļ�������������ȡ��ע�ͣ��������������ļ�(��_test��β)���ⲿ�����ݼ���ע��
#define RUN_TEST

#ifdef RUN_TEST
int main() {
    // ����localeΪ���Ļ�����ֻ���������ܲ���ʱ�������
    std::locale::global(std::locale("zh_CN.UTF-8"));
    std::wcout.imbue(std::locale());


    wcout << "file compress test" << endl;
    // �����û������ѹ���ļ���������ļ���
    wstring inputFilename, outputFilename;
    wcout << L"������Ҫѹ�����ļ���: " << endl;
    getline(std::wcin, inputFilename);
    wcout << L"������ѹ���������ļ���: " << endl;
    getline(std::wcin, outputFilename);

    // ����Compressorʵ��
    Compressor compressor;

    // ���Խ����ļ�ѹ��
    try {
        compressor.compressFile(inputFilename, outputFilename);
        wcout << L"�ļ�ѹ���ɹ�������ļ�: " << outputFilename << endl;
    }
    catch (const std::exception& e) {
        wcerr << L"�ļ�ѹ��ʧ��: " << e.what() << endl;
    }

    return 0;
}
#endif