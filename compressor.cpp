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
void Compressor::compress(const std::string& inputFilename, const std::string& outputFilename, const std::string& outputTree) {

    // 以二进制方式打开输入和输出文件
    std::ifstream inputFile(inputFilename, std::ios::binary);

    std::ofstream outputFile(outputFilename, std::ios::binary);

    std::ofstream outputtree(outputTree, std::ios::binary);
    // 如果无法打开输入或输出文件，抛出异常
    if (!inputFile.is_open() || !outputFile.is_open() || !outputtree.is_open()) {
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
    
    currentByte = 0;
    bitCount = 0;
    outputtree.put(0); // 先占位一个字节，稍后填入最后一个字节中的有效位数

    // 层序遍历建二进制哈夫曼树
    huffmanTree.Hierachicalorder();// Tree被建好了

     for (bool bit : huffmanTree.Tree) {
        if (bit) {
            currentByte |= (1 << (7 - bitCount));
        }
        bitCount++;
        if (bitCount == 8) {
            outputtree.put(currentByte);
            currentByte = 0;
            bitCount = 0;
        }
    }
    // 处理最后一个不完整的字节
    if (bitCount > 0) {
        outputtree.put(currentByte);
    }

    // 返回文件开头，写入最后一个字节的有效位数
    outputtree.seekp(0, std::ios::beg);
    outputtree.put(bitCount == 0 ? 8 : bitCount);
    

    inputFile.close();
    outputFile.close();
    outputtree.close();
    
}


// 读取文件，进行压缩，输出到指定文件
void Compressor::compressFile(const std::string& inputFilename, const std::string& outputFilename,const std::string& outputTree) {
    try {
        countFrequency(inputFilename);
        buildCodes();
        compress(inputFilename, outputFilename,outputTree);
    }
    catch (const std::exception& e) {
        std::cerr << "Compression failed: " << e.what() << std::endl;
    }
}

HuffmanTree& Compressor::getHuffmanTree() {
    return huffmanTree;
}


void Compressor::decompressFile(const std::string& inputTree,const std::string& inputFilename, const std::string& outputFilename) {
    try {
        // 尝试解压文件
        decompress(inputTree,inputFilename, outputFilename);
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
void Compressor::decompress(const std::string& inputTree,const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inputFile(inputFilename, std::ios::binary); // 以二进制方式打开压缩文件读取二进制数据
    std::ifstream inputtree(inputTree, std::ios::binary);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot open input file for decompression");
    }

    std::ofstream outputFile(outputFilename, std::ios::binary); // 以二进制方式打开输出文件写入解压缩后的数据
    
    // 读入二进制树，建树
    char paddingtree;// 二进制树文件的头部
    inputtree.get(paddingtree);
    int paddingt = static_cast<int>(paddingtree);
    std::vector<bool> compressedtree;
    char b;
    // 读取二进制文件
    while(inputtree.get(b))
    {
        for (int i = 7; i >= 0; --i)
        {
            compressedtree.push_back((b >> i) & 1);
        }
    }
    inputtree.close();
    if (paddingt > 0 && paddingt < 8) {
        compressedtree.erase(compressedtree.end() - (8 - paddingt), compressedtree.end());
    }

    // 用读入的二进制树建树
    HuffmanTree H;
    //HuffmanTree::Node* current=H.buildingHuffmanTree(huffmanTree.Tree);
    HuffmanTree::Node* current = H.buildingHuffmanTree(compressedtree);

    // 读取填充信息（假设它是文件的第一个字节）s
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
        compressedData.erase(compressedData.end() - (8 - padding), compressedData.end());
    }

    // 使用哈夫曼树进行解码
    std::string decodedText;
    //HuffmanTree::Node* current = huffmanTree.getRoot();
    for (bool bit : compressedData) {
        if (!bit && current->left != nullptr) {
            current = current->left;
        }
        else if (bit && current->right != nullptr) {
            current = current->right;
        }

        // 当到达叶子节点时，找到一个字符
        if (current->left == nullptr && current->right == nullptr) {
            decodedText.append(current->character); // 将字符添加到解码文本
            current = H.getRoot(); // 重置到根节点开始下一个字符的解码
        }
    }

    outputFile.write(decodedText.c_str(), decodedText.size()); // 将解码后的文本写入输出文件
    outputFile.close(); // 关闭输出文件
}
