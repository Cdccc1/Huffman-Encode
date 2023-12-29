#include "frequency_counter.h"
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>

using namespace std;

// 辅助函数，用于从 std::string 转换为 std::wstring
std::wstring string_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

int main() {
    cout << "请输入原始文件路径：" << endl;
    string inputPath;
    getline(cin, inputPath);  // 读取原始文件路径

    cout << "请输入输出文件路径：" << endl;
    string outputPath;
    getline(cin, outputPath);  // 读取输出文件路径

    // 将路径转换为 std::wstring
    wstring wInputPath = string_to_wstring(inputPath);
    wstring wOutputPath = string_to_wstring(outputPath);

    try {
        FrequencyCounter counter(wInputPath);  // 创建 FrequencyCounter 实例
        counter.writeFrequency(wOutputPath);  // 将频率结果写入输出文件

        cout << "字符频率已写入文件: " << outputPath << endl;
    }
    catch (const std::runtime_error& e) {
        cerr << "错误: " << e.what() << endl;
    }

    return 0;
}
