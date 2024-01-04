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
// 如果要运行该测试文件，将下面那行取消注释，并将其他测试文件(以_test结尾)的这部分内容加上注释
#define RUN_TEST

#ifdef RUN_TEST
int main() {
    // 设置控制台的输出编码为UTF-8
    //SetConsoleOutputCP(CP_UTF8);

    cout << "file compress test" << endl;
    // 请求用户输入待压缩文件名和输出文件名
    string inputFilename1, outputFilename1,outputTree,inputTree,inputFilename2, outputFilename2;
    
    cout << "请输入要压缩的文件名: " << endl;
    getline(cin, inputFilename1);
    // inputFilename = "E:\\DataStucture\\Huffman-Encode\\src\\斗破苍穹.txt";
    cout << "请输入压缩后的输出文件名: " << endl;
    getline(cin, outputFilename1);
    cout << "请输入压缩后的树的输出文件名: " << endl;
    getline(cin, outputTree);
    
    // 创建Compressor实例
    Compressor compressor;
    
    // 尝试进行文件压缩
    try {
        compressor.compressFile(inputFilename1, outputFilename1,outputTree);
        cout << "文件压缩成功。输出文件: " << outputFilename1 <<"和"<<outputTree<< endl;
    }
    catch (const std::exception& e) {
        cerr << "文件压缩失败: " << e.what() << endl;
    }
    cout << "请输入要解压缩的树名: " << endl;
    getline(cin, inputTree);
    cout << "请输入要解压缩的文件名: " << endl;
    getline(cin, inputFilename2);
    cout << "请输入解压缩后的输出文件名: " << endl;
    getline(cin, outputFilename2);
    compressor.decompressFile(inputTree,inputFilename2, outputFilename2);
    cout << "文件解压缩成功。输出文件: " << outputFilename2 << endl;
    FileHasher in1, in2;
    in1.computeHash(inputFilename1);
    in2.computeHash(outputFilename2);
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