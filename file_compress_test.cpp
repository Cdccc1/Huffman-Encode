#include <iostream>
#include <string>
#include "compressor.h"
#include "h_priority_queue.h"
#include <locale>
#include <codecvt>

using namespace std;
// 如果要运行该测试文件，将下面那行取消注释，并将其他测试文件(以_test结尾)的这部分内容加上注释
#define RUN_TEST

#ifdef RUN_TEST
int main() {
    // 设置locale为中文环境，只有这样才能测试时输出中文
    std::locale::global(std::locale("zh_CN.UTF-8"));
    std::wcout.imbue(std::locale());


    wcout << "file compress test" << endl;
    // 请求用户输入待压缩文件名和输出文件名
    wstring inputFilename, outputFilename;
    wcout << L"请输入要压缩的文件名: " << endl;
    getline(std::wcin, inputFilename);
    wcout << L"请输入压缩后的输出文件名: " << endl;
    getline(std::wcin, outputFilename);

    // 创建Compressor实例
    Compressor compressor;

    // 尝试进行文件压缩
    try {
        compressor.compressFile(inputFilename, outputFilename);
        wcout << L"文件压缩成功。输出文件: " << outputFilename << endl;
    }
    catch (const std::exception& e) {
        wcerr << L"文件压缩失败: " << e.what() << endl;
    }

    return 0;
}
#endif