#include <iostream>
#include <string>
#include "compressor.h"
#include "decompressor.h"
#include "h_priority_queue.h"
#include "hash_cmp.h"
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
    string inputFilename1, outputFilename1,outputTree,inputTree,inputFilename2, outputFilename2;
    
    cout << "������Ҫѹ�����ļ���: " << endl;
    getline(cin, inputFilename1);
    // inputFilename = "E:\\DataStucture\\Huffman-Encode\\src\\���Ʋ��.txt";
    cout << "������ѹ���������ļ���: " << endl;
    getline(cin, outputFilename1);
    cout << "������ѹ�������������ļ���: " << endl;
    getline(cin, outputTree);
    
    // ����Compressorʵ��
    Compressor compressor;
    
    // ���Խ����ļ�ѹ��
    try {
        compressor.compressFile(inputFilename1, outputFilename1,outputTree);
        cout << "�ļ�ѹ���ɹ�������ļ�: " << outputFilename1 <<"��"<<outputTree<< endl;
    }
    catch (const std::exception& e) {
        cerr << "�ļ�ѹ��ʧ��: " << e.what() << endl;
    }
    cout << "������Ҫ��ѹ��������: " << endl;
    getline(cin, inputTree);
    cout << "������Ҫ��ѹ�����ļ���: " << endl;
    getline(cin, inputFilename2);
    cout << "�������ѹ���������ļ���: " << endl;
    getline(cin, outputFilename2);
    compressor.decompressFile(inputTree,inputFilename2, outputFilename2);
    cout << "�ļ���ѹ���ɹ�������ļ�: " << outputFilename2 << endl;
    FileHasher in1, in2;
    in1.computeHash(inputFilename1);
    in2.computeHash(outputFilename2);
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
#endif