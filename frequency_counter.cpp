#include "frequency_counter.h"
#include <cstring>


FrequencyCounter::FrequencyCounter() : utf8char(std::string(10, 0)) {}


FrequencyCounter::FrequencyCounter(const std::string& filename) : FrequencyCounter() {
    // 在构造函数中计算字符频率
    this->frequencyTable = countFrequency(filename);
}


FrequencyCounter::~FrequencyCounter() {}


std::string& FrequencyCounter::readUTF8Char(std::ifstream& stream) {
    utf8char.clear();
    char ch;
    if (stream.get(ch)) {
        utf8char.push_back(ch);
        // utf8char += ch;
        // 确定UTF-8字符中的字节数
        int bytesInChar = 1;
        if ((ch & 0x80) != 0) { // 超过一个字节
            if ((ch & 0xE0) == 0xC0) bytesInChar = 2;
            else if ((ch & 0xF0) == 0xE0) bytesInChar = 3;
            else if ((ch & 0xF8) == 0xF0) bytesInChar = 4;
            // 读取UTF-8字符的剩余字节
            while (--bytesInChar > 0 && stream.get(ch)) {
                // utf8char += ch;
                utf8char.push_back(ch);
            }
        }
    }
    return utf8char;
}
// 计算字符频率
std::map<std::string, int> FrequencyCounter::countFrequency(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary); // 以二进制方式打开以防止字符转换

    if (!file.is_open()) {
        throw std::runtime_error("FrequencyCounter 无法打开文件");
    }
    

    std::map<std::string, int> frequencyTable;

    while (!file.eof()) {
        // std::string utf8char = readUTF8Char(file);
        std::string& utf8char = readUTF8Char(file);
        if (!utf8char.empty()) {
            frequencyTable[utf8char]++;
        }
    }
    file.close();
    return frequencyTable;
}


void FrequencyCounter::writeFrequency(const std::string& outputFilename) {
    std::ofstream outFile(outputFilename, std::ios::binary); // 以二进制方式打开，防止字符转换

    if (!outFile.is_open()) {
        throw std::runtime_error("FrequencyCounter 无法创建文件");
    }

    for (const auto& pair : frequencyTable) {
        // 将每个字符及其频率写入文件
        outFile << pair.first << ": " << pair.second << "\n";
    }

    outFile.close();
}



