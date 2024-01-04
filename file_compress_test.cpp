#include <iostream>
#include <string>
#include "compressor.h"
#include "decompressor.h"
#include "h_priority_queue.h"
#include <locale>
#include <codecvt>
#include <windows.h>

using namespace std;
// ���Ҫ���иò����ļ�������������ȡ��ע�ͣ��������������ļ�(��_test��β)���ⲿ�����ݼ���ע��
#define RUN_TEST

#ifdef RUN_TEST
int main() {
    // ���ÿ���̨���������ΪUTF-8
    //SetConsoleOutputCP(CP_UTF8);

    cout << "file compress test" << endl;
    // �����û������ѹ���ļ���������ļ���
    string inputFilename, outputFilename;
    cout << "������Ҫѹ�����ļ���: " << endl;
    getline(cin, inputFilename);
    // inputFilename = "E:\\DataStucture\\Huffman-Encode\\src\\���Ʋ��.txt";
    cout << "������ѹ���������ļ���: " << endl;
    getline(cin, outputFilename);

    // ����Compressorʵ��
    Compressor compressor;

    // ���Խ����ļ�ѹ��
    try {
        compressor.compressFile(inputFilename, outputFilename);
        cout << "�ļ�ѹ���ɹ�������ļ�: " << outputFilename << endl;
    }
    catch (const std::exception& e) {
        cerr << "�ļ�ѹ��ʧ��: " << e.what() << endl;
    }


    cout << "������Ҫ��ѹ�����ļ���: " << endl;
    getline(cin, inputFilename);
    cout << "�������ѹ���������ļ���: " << endl;
    getline(cin, outputFilename);
    compressor.decompressFile(inputFilename, outputFilename);
    cout << "�ļ���ѹ���ɹ�������ļ�: " << outputFilename << endl;
    return 0;
}
#endif