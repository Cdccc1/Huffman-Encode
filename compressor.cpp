#include "compressor.h"

// 构造函数
Compressor::Compressor() {}

// 析构函数
Compressor::~Compressor() {}

// 读取文件,统计字符频率,字符频率写入
void Compressor::countFrequency(const std::wstring& inputFilename) {
    try {
        FrequencyCounter fc(inputFilename);
        frequencyTable = fc.countFrequency(inputFilename);
        // 直接调用FrequencyCounter的写入统计函数
        fc.writeFrequency(inputFilename + L"_freq.txt");
    }
    catch (const std::exception& e) {
        std::wcerr << "Error counting frequency: " << e.what() << std::endl;
        throw;
    }
}

// 构建哈夫曼树并生成编码
void Compressor::buildCodes() {
    huffmanTree.buildTree(frequencyTable);
    codes = huffmanTree.encode();
}

// 实际进行压缩的函数
void Compressor::compress(const std::wstring& inputFilename, const std::wstring& outputFilename) {
    
    // 以二进制方式打开输入和输出文件
    std::wifstream inputFile(inputFilename, std::ios::binary);
    std::ofstream outputFile(outputFilename, std::ios::binary);

    // 如果无法打开输入或输出文件，抛出异常
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::wcerr << "Error opening files!" << std::endl;
        throw std::runtime_error("Cannot open input/output files.");
    }

    // 读取整个文件内容到宽字符串中
    std::wstring text((std::istreambuf_iterator<wchar_t>(inputFile)), std::istreambuf_iterator<wchar_t>());

    // 初始化一个空的二进制字符串用于存放编码
    std::string binaryStream;

    for (wchar_t ch : text) {
        std::wstring wcode = codes[ch]; // 获取宽字符串格式的哈夫曼编码
        // 将宽字符串编码转换为普通字符串并累加到二进制流中
        for (wchar_t wch : wcode) {
            binaryStream.push_back(static_cast<char>(wch));
        }
    }

    // 计算需要填充的位数以确保二进制流长度为8的倍数
    int padding = 8 - (binaryStream.length() % 8);
    if (padding != 8) { // 如果不是刚好填满，需要进行填充
        binaryStream.append(padding, '0');
    }

    // 将填充信息作为第一个字节写入，然后写入实际的二进制数据
    outputFile.put(padding);
    for (size_t i = 0; i < binaryStream.length(); i += 8) {
        // 每8位二进制字符串转换为一个字节并写入
        std::string byteString = binaryStream.substr(i, 8);
        char byte = static_cast<char>(std::bitset<8>(byteString).to_ulong());
        outputFile.write(&byte, sizeof(char));
    }

    // 关闭文件
    inputFile.close();
    outputFile.close();
}


// 读取文件，进行压缩，输出到指定文件
void Compressor::compressFile(const std::wstring& inputFilename, const std::wstring& outputFilename) {
    try {
        countFrequency(inputFilename);
        buildCodes();
        compress(inputFilename, outputFilename);
    }
    catch (const std::exception& e) {
        std::wcerr << "Compression failed: " << e.what() << std::endl;
    }
}

HuffmanTree& Compressor::getHuffmanTree() {
    return huffmanTree;
}