#include "compressor.h"
#include <locale>
#include <codecvt>


// ���캯��
Compressor::Compressor() {}

// ��������
Compressor::~Compressor() {}

// ��ȡ�ļ�,ͳ���ַ�Ƶ��,�ַ�Ƶ��д��
void Compressor::countFrequency(const std::string& inputFilename) {
    try {
        // FrequencyCounter fc(inputFilename);
        fc = inputFilename;
        frequencyTable = fc.countFrequency(inputFilename);
        // ֱ�ӵ���FrequencyCounter��д��ͳ�ƺ���
        fc.writeFrequency(inputFilename + "_freq.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "Error counting frequency: " << e.what() << std::endl;
        throw;
    }
}

// �����������������ɱ���
void Compressor::buildCodes() {
    huffmanTree.buildTree(frequencyTable);
    codes = huffmanTree.encode();
}
/*
// �������������ֽ����ж�ȡ��һ��UTF-8������ַ�
std::string readUTF8CharHelper(std::ifstream& stream) {
    std::string utf8char;
    char ch;
    if (stream.get(ch)) {
        utf8char += ch;
        // ȷ��UTF-8�ַ��е��ֽ���
        int bytesInChar = 1;
        if ((ch & 0x80) != 0) { // ����һ���ֽ�
            if ((ch & 0xE0) == 0xC0) bytesInChar = 2;
            else if ((ch & 0xF0) == 0xE0) bytesInChar = 3;
            else if ((ch & 0xF8) == 0xF0) bytesInChar = 4;
            // ��ȡUTF-8�ַ���ʣ���ֽ�
            while (--bytesInChar > 0 && stream.get(ch)) {
                utf8char += ch;
            }
        }
    }
    return utf8char;
}
*/
void Compressor::compress(const std::string& inputFilename, const std::string& outputFilename) {

    // �Զ����Ʒ�ʽ�����������ļ�
    std::ifstream inputFile(inputFilename, std::ios::binary);

    std::ofstream outputFile(outputFilename, std::ios::binary);

    // ����޷������������ļ����׳��쳣
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        throw std::runtime_error("Cannot open input/output files.");
    }

    char currentByte = 0;
    int bitCount = 0;
    outputFile.put(0); // ��ռλһ���ֽڣ��Ժ��������һ���ֽ��е���Чλ��

    // ʹ�ø���������ȡUTF-8�ַ�
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

        // ������ȡ��һ���ַ�
        utf8char = fc.readUTF8Char(inputFile);
    }

    // �������һ�����������ֽ�
    if (bitCount > 0) {
        outputFile.put(currentByte);
    }

    // �����ļ���ͷ��д�����һ���ֽڵ���Чλ��
    outputFile.seekp(0, std::ios::beg);
    outputFile.put(bitCount == 0 ? 8 : bitCount);

    inputFile.close();
    outputFile.close();
    /*
    // ��ȡ�����ļ����ݵ��ַ�����
    std::string text((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    std::cout << text << std::endl;

    // ��ʼ��һ���յĶ������ַ������ڴ�ű���

    char currentByte = 0; // ��ǰ���ڹ������ֽ�
    int bitCount = 0; // ��ǰ�ֽ����Ѿ��ۼӵı�����

    // ��ռλһ���ֽڣ��Ժ��������һ���ֽ��е���Чλ��
    outputFile.put(0);

    for (auto& ch : text) {  // ����ÿ���ַ�
        // ��ȡ�ַ��Ĺ���������
        std::vector<bool> bits = codes[std::string(1,ch)];  
        
        for (bool bit : bits) {
            // �������ۼӵ���ǰ�ֽ�
            if (bit) {
                currentByte |= (1 << (7 - bitCount));
            }
            bitCount++;

            // ����Ƿ��ѹ�����һ���������ֽ�
            if (bitCount == 8) {
                outputFile.put(currentByte); // ���������ֽ���ӵ�����ļ���
                currentByte = 0; // ���õ�ǰ�ֽ�
                bitCount = 0; // ���ñ��ؼ�����
            }
        }
    }

    // �������һ�����������ֽ�
    if (bitCount > 0) {
        outputFile.put(currentByte); // �������ֽ�д���ļ�
    }

    // �����ļ���ͷ��д�����һ���ֽڵ���Чλ��
    outputFile.seekp(0, std::ios::beg);
    outputFile.put(bitCount == 0 ? 8 : bitCount);

    // �ر��ļ�
    inputFile.close();
    outputFile.close();*/
}


// ��ȡ�ļ�������ѹ���������ָ���ļ�
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
        // ���Խ�ѹ�ļ�
        decompress(inputFilename, outputFilename);
    }
    catch (const std::runtime_error& e) {
        // ��������ʱ���󣬲����ʵ�����
        std::cerr << "Runtime error occurred: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // �������б�׼�쳣
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
    catch (...) {
        // ��������δ֪���͵��쳣
        std::cerr << "An unknown error occurred." << std::endl;
    }
}


// ʵ�ʽ�ѹ��
void Compressor::decompress(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inputFile(inputFilename, std::ios::binary); // �Զ����Ʒ�ʽ��ѹ���ļ���ȡ����������
    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot open input file for decompression");
    }

    std::ofstream outputFile(outputFilename, std::ios::binary); // �Զ����Ʒ�ʽ������ļ�д���ѹ���������

    // ��ȡ�����Ϣ�����������ļ��ĵ�һ���ֽڣ�
    char paddingInfo;
    inputFile.get(paddingInfo);
    int padding = static_cast<int>(paddingInfo);

    // ��ȡʣ���ѹ������
    std::vector<bool> compressedData;
    char byte;
    while (inputFile.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            compressedData.push_back((byte >> i) & 1);
        }
    }
    inputFile.close(); // �ر������ļ�

    // ���ǵ���䣬��ѹ���������Ƴ���󼸸����λ
    if (padding > 0 && padding < 8) {
        compressedData.erase(compressedData.end() - padding, compressedData.end());
    }

    // ʹ�ù����������н���
    std::string decodedText;
    HuffmanTree::Node* current = huffmanTree.getRoot();
    for (bool bit : compressedData) {
        if (!bit && current->left != nullptr) {
            current = current->left;
        }
        else if (bit && current->right != nullptr) {
            current = current->right;
        }

        // ������Ҷ�ӽڵ�ʱ���ҵ�һ���ַ�
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->character; // ���ַ���ӵ������ı�
            current = huffmanTree.getRoot(); // ���õ����ڵ㿪ʼ��һ���ַ��Ľ���
        }
    }

    outputFile.write(decodedText.c_str(), decodedText.size()); // ���������ı�д������ļ�
    outputFile.close(); // �ر�����ļ�
    
    /*
    // 1. ��ѹ���ļ��Զ�ȡ����������
    std::ifstream inputFile(inputFilename, std::ios::binary); // 1. ��ѹ���ļ��Զ�ȡ����������
    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    // ��ȡ�����Ϣ���ļ��ĵ�һ���ֽڣ�
    char paddingByte;
    inputFile.get(paddingByte);
    int padding = paddingByte;

    // 2. �ؽ������Ʊ����ַ���
    std::string binaryString;
    char byte;
    while (inputFile.get(byte)) {
        std::bitset<8> bits(byte); // ��ÿ���ֽ�ת��Ϊ�������ַ���
        binaryString.append(bits.to_string());
    }
    inputFile.close(); // �ر��ļ�

    // 3. ʹ�ù�������ʵ�����н��� 
    std::string decodedText;
    HuffmanTree::Node* current = huffmanTree.getRoot();

    for (char bit : binaryString) {
        if (bit == '0' && current->left != nullptr) {
            current = current->left;
        }
        else if (bit == '1' && current->right != nullptr) {
            current = current->right;
        }

        // ������Ҷ�ӽڵ�ʱ���ҵ�һ���ַ�
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->character; // ���ַ���ӵ������ı�
            current = huffmanTree.getRoot(); // ���õ����ڵ㿪ʼ��һ���ַ��Ľ���
        }
    }

    // 4. ���������ı�д������ļ�
    std::wofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Cannot open output file");
    }
    outputFile << decodedText;
    outputFile.close();*/
}