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
void Compressor::compress(const std::string& inputFilename, const std::string& outputFilename, const std::string& outputTree) {

    // �Զ����Ʒ�ʽ�����������ļ�
    std::ifstream inputFile(inputFilename, std::ios::binary);

    std::ofstream outputFile(outputFilename, std::ios::binary);

    std::ofstream outputtree(outputTree, std::ios::binary);
    // ����޷������������ļ����׳��쳣
    if (!inputFile.is_open() || !outputFile.is_open() || !outputtree.is_open()) {
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
    
    currentByte = 0;
    bitCount = 0;
    outputtree.put(0); // ��ռλһ���ֽڣ��Ժ��������һ���ֽ��е���Чλ��

    // ��������������ƹ�������
    huffmanTree.Hierachicalorder();// Tree��������

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
    // �������һ�����������ֽ�
    if (bitCount > 0) {
        outputtree.put(currentByte);
    }

    // �����ļ���ͷ��д�����һ���ֽڵ���Чλ��
    outputtree.seekp(0, std::ios::beg);
    outputtree.put(bitCount == 0 ? 8 : bitCount);
    

    inputFile.close();
    outputFile.close();
    outputtree.close();
    
}


// ��ȡ�ļ�������ѹ���������ָ���ļ�
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
        // ���Խ�ѹ�ļ�
        decompress(inputTree,inputFilename, outputFilename);
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
void Compressor::decompress(const std::string& inputTree,const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inputFile(inputFilename, std::ios::binary); // �Զ����Ʒ�ʽ��ѹ���ļ���ȡ����������
    std::ifstream inputtree(inputTree, std::ios::binary);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot open input file for decompression");
    }

    std::ofstream outputFile(outputFilename, std::ios::binary); // �Զ����Ʒ�ʽ������ļ�д���ѹ���������
    
    // �����������������
    char paddingtree;// ���������ļ���ͷ��
    inputtree.get(paddingtree);
    int paddingt = static_cast<int>(paddingtree);
    std::vector<bool> compressedtree;
    char b;
    // ��ȡ�������ļ�
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

    // �ö���Ķ�����������
    HuffmanTree H;
    //HuffmanTree::Node* current=H.buildingHuffmanTree(huffmanTree.Tree);
    HuffmanTree::Node* current = H.buildingHuffmanTree(compressedtree);

    // ��ȡ�����Ϣ�����������ļ��ĵ�һ���ֽڣ�s
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
        compressedData.erase(compressedData.end() - (8 - padding), compressedData.end());
    }

    // ʹ�ù����������н���
    std::string decodedText;
    //HuffmanTree::Node* current = huffmanTree.getRoot();
    for (bool bit : compressedData) {
        if (!bit && current->left != nullptr) {
            current = current->left;
        }
        else if (bit && current->right != nullptr) {
            current = current->right;
        }

        // ������Ҷ�ӽڵ�ʱ���ҵ�һ���ַ�
        if (current->left == nullptr && current->right == nullptr) {
            decodedText.append(current->character); // ���ַ���ӵ������ı�
            current = H.getRoot(); // ���õ����ڵ㿪ʼ��һ���ַ��Ľ���
        }
    }

    outputFile.write(decodedText.c_str(), decodedText.size()); // ���������ı�д������ļ�
    outputFile.close(); // �ر�����ļ�
}
