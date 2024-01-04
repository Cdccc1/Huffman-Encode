#include "compressor.h"
#include <locale>
#include <codecvt>


// 构造函数
Compressor::Compressor() {}

// 析构函数
Compressor::~Compressor() {}

// 读取文件,统计字符频率,字符频率写入
void Compressor::countFrequency(const std::string& inputFilename) {
    try {
        // FrequencyCounter fc(inputFilename);
        fc = inputFilename;
        frequencyTable = fc.countFrequency(inputFilename);
        // 直接调用FrequencyCounter的写入统计函数
        fc.writeFrequency(inputFilename + "_freq.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "Error counting frequency: " << e.what() << std::endl;
        throw;
    }
}

// 构建哈夫曼树并生成编码
void Compressor::buildCodes() {
    huffmanTree.buildTree(frequencyTable);
    codes = huffmanTree.encode();
}
/*
// 辅助函数，从字节流中读取下一个UTF-8编码的字符
std::string readUTF8CharHelper(std::ifstream& stream) {
    std::string utf8char;
    char ch;
    if (stream.get(ch)) {
        utf8char += ch;
        // 确定UTF-8字符中的字节数
        int bytesInChar = 1;
        if ((ch & 0x80) != 0) { // 超过一个字节
            if ((ch & 0xE0) == 0xC0) bytesInChar = 2;
            else if ((ch & 0xF0) == 0xE0) bytesInChar = 3;
            else if ((ch & 0xF8) == 0xF0) bytesInChar = 4;
            // 读取UTF-8字符的剩余字节
            while (--bytesInChar > 0 && stream.get(ch)) {
                utf8char += ch;
            }
        }
    }
    return utf8char;
}
*/
void Compressor::compress(const std::string& inputFilename, const std::string& outputFilename) {

    // 以二进制方式打开输入和输出文件
    std::ifstream inputFile(inputFilename, std::ios::binary);

    std::ofstream outputFile(outputFilename, std::ios::binary);

    // 如果无法打开输入或输出文件，抛出异常
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        throw std::runtime_error("Cannot open input/output files.");
    }

    char currentByte = 0;
    int bitCount = 0;
    outputFile.put(0); // 先占位一个字节，稍后填入最后一个字节中的有效位数

    // 使用辅助函数读取UTF-8字符
    std::string& utf8char = fc.readUTF8Char(inputFile);
    while (!utf8char.empty()) {
        std::vector<bool> bits = codes[utf8char];

        for (bool bit : bits) {
            if (bit) {
                currentByte |= (1 << (7 - bitCount));
            }
            bitCount++;

            if (bitCount == 8) {
                outputFile.put(currentByte);
                currentByte = 0;
                bitCount = 0;
            }
        }

        // 继续读取下一个字符
        utf8char = fc.readUTF8Char(inputFile);
    }

    // 处理最后一个不完整的字节
    if (bitCount > 0) {
        outputFile.put(currentByte);
    }

    // 返回文件开头，写入最后一个字节的有效位数
    outputFile.seekp(0, std::ios::beg);
    outputFile.put(bitCount == 0 ? 8 : bitCount);

    inputFile.close();
    outputFile.close();
    /*
    // 读取整个文件内容到字符串中
    std::string text((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    std::cout << text << std::endl;

    // 初始化一个空的二进制字符串用于存放编码

    char currentByte = 0; // 当前正在构建的字节
    int bitCount = 0; // 当前字节中已经累加的比特数

    // 先占位一个字节，稍后填入最后一个字节中的有效位数
    outputFile.put(0);

    for (auto& ch : text) {  // 遍历每个字符
        // 获取字符的哈夫曼编码
        std::vector<bool> bits = codes[std::string(1,ch)];  
        
        for (bool bit : bits) {
            // 将比特累加到当前字节
            if (bit) {
                currentByte |= (1 << (7 - bitCount));
            }
            bitCount++;

            // 检查是否已构建了一个完整的字节
            if (bitCount == 8) {
                outputFile.put(currentByte); // 将完整的字节添加到输出文件中
                currentByte = 0; // 重置当前字节
                bitCount = 0; // 重置比特计数器
            }
        }
    }

    // 处理最后一个不完整的字节
    if (bitCount > 0) {
        outputFile.put(currentByte); // 将最后的字节写入文件
    }

    // 返回文件开头，写入最后一个字节的有效位数
    outputFile.seekp(0, std::ios::beg);
    outputFile.put(bitCount == 0 ? 8 : bitCount);

    // 关闭文件
    inputFile.close();
    outputFile.close();*/
}


// 读取文件，进行压缩，输出到指定文件
void Compressor::compressFile(const std::string& inputFilename, const std::string& outputFilename) {
    try {
        countFrequency(inputFilename);
        buildCodes();
        compress(inputFilename, outputFilename);
    }
    catch (const std::exception& e) {
        std::cerr << "Compression failed: " << e.what() << std::endl;
    }
}

HuffmanTree& Compressor::getHuffmanTree() {
    return huffmanTree;
}


void Compressor::decompressFile(const std::string& inputFilename, const std::string& outputFilename) {
    try {
        // 尝试解压文件
        decompress(inputFilename, outputFilename);
    }
    catch (const std::runtime_error& e) {
        // 捕获运行时错误，并做适当处理
        std::cerr << "Runtime error occurred: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // 捕获所有标准异常
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
    catch (...) {
        // 捕获所有未知类型的异常
        std::cerr << "An unknown error occurred." << std::endl;
    }
}


// 实际解压缩
void Compressor::decompress(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inputFile(inputFilename, std::ios::binary); // 以二进制方式打开压缩文件读取二进制数据
    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot open input file for decompression");
    }

    std::ofstream outputFile(outputFilename, std::ios::binary); // 以二进制方式打开输出文件写入解压缩后的数据

    // 读取填充信息（假设它是文件的第一个字节）
    char paddingInfo;
    inputFile.get(paddingInfo);
    int padding = static_cast<int>(paddingInfo);

    // 读取剩余的压缩数据
    std::vector<bool> compressedData;
    char byte;
    while (inputFile.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            compressedData.push_back((byte >> i) & 1);
        }
    }
    inputFile.close(); // 关闭输入文件

    // 考虑到填充，从压缩数据中移除最后几个填充位
    if (padding > 0 && padding < 8) {
        compressedData.erase(compressedData.end() - padding, compressedData.end());
    }

    // 使用哈夫曼树进行解码
    std::string decodedText;
    HuffmanTree::Node* current = huffmanTree.getRoot();
    for (bool bit : compressedData) {
        if (!bit && current->left != nullptr) {
            current = current->left;
        }
        else if (bit && current->right != nullptr) {
            current = current->right;
        }

        // 当到达叶子节点时，找到一个字符
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->character; // 将字符添加到解码文本
            current = huffmanTree.getRoot(); // 重置到根节点开始下一个字符的解码
        }
    }

    outputFile.write(decodedText.c_str(), decodedText.size()); // 将解码后的文本写入输出文件
    outputFile.close(); // 关闭输出文件
    
    /*
    // 1. 打开压缩文件以读取二进制数据
    std::ifstream inputFile(inputFilename, std::ios::binary); // 1. 打开压缩文件以读取二进制数据
    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    // 读取填充信息（文件的第一个字节）
    char paddingByte;
    inputFile.get(paddingByte);
    int padding = paddingByte;

    // 2. 重建二进制编码字符串
    std::string binaryString;
    char byte;
    while (inputFile.get(byte)) {
        std::bitset<8> bits(byte); // 将每个字节转换为二进制字符串
        binaryString.append(bits.to_string());
    }
    inputFile.close(); // 关闭文件

    // 3. 使用哈夫曼树实例进行解码 
    std::string decodedText;
    HuffmanTree::Node* current = huffmanTree.getRoot();

    for (char bit : binaryString) {
        if (bit == '0' && current->left != nullptr) {
            current = current->left;
        }
        else if (bit == '1' && current->right != nullptr) {
            current = current->right;
        }

        // 当到达叶子节点时，找到一个字符
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->character; // 将字符添加到解码文本
            current = huffmanTree.getRoot(); // 重置到根节点开始下一个字符的解码
        }
    }

    // 4. 将解码后的文本写入输出文件
    std::wofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Cannot open output file");
    }
    outputFile << decodedText;
    outputFile.close();*/
}