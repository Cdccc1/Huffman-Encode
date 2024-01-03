#include "compressor.h"

// ���캯��
Compressor::Compressor() {}

// ��������
Compressor::~Compressor() {}

// ��ȡ�ļ�,ͳ���ַ�Ƶ��,�ַ�Ƶ��д��
void Compressor::countFrequency(const std::wstring& inputFilename) {
    try {
        FrequencyCounter fc(inputFilename);
        frequencyTable = fc.countFrequency(inputFilename);
        // ֱ�ӵ���FrequencyCounter��д��ͳ�ƺ���
        fc.writeFrequency(inputFilename + L"_freq.txt");
    }
    catch (const std::exception& e) {
        std::wcerr << "Error counting frequency: " << e.what() << std::endl;
        throw;
    }
}

// �����������������ɱ���
void Compressor::buildCodes() {
    huffmanTree.buildTree(frequencyTable);
    codes = huffmanTree.encode();
}

// ʵ�ʽ���ѹ���ĺ���
void Compressor::compress(const std::wstring& inputFilename, const std::wstring& outputFilename) {
    
    // �Զ����Ʒ�ʽ�����������ļ�
    std::wifstream inputFile(inputFilename, std::ios::binary);
    std::ofstream outputFile(outputFilename, std::ios::binary);

    // ����޷������������ļ����׳��쳣
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::wcerr << "Error opening files!" << std::endl;
        throw std::runtime_error("Cannot open input/output files.");
    }

    // ��ȡ�����ļ����ݵ����ַ�����
    std::wstring text((std::istreambuf_iterator<wchar_t>(inputFile)), std::istreambuf_iterator<wchar_t>());

    // ��ʼ��һ���յĶ������ַ������ڴ�ű���
    std::string binaryStream;

    for (wchar_t ch : text) {
        std::wstring wcode = codes[ch]; // ��ȡ���ַ�����ʽ�Ĺ���������
        // �����ַ�������ת��Ϊ��ͨ�ַ������ۼӵ�����������
        for (wchar_t wch : wcode) {
            binaryStream.push_back(static_cast<char>(wch));
        }
    }

    // ������Ҫ����λ����ȷ��������������Ϊ8�ı���
    int padding = 8 - (binaryStream.length() % 8);
    if (padding != 8) { // ������Ǹպ���������Ҫ�������
        binaryStream.append(padding, '0');
    }

    // �������Ϣ��Ϊ��һ���ֽ�д�룬Ȼ��д��ʵ�ʵĶ���������
    outputFile.put(padding);
    for (size_t i = 0; i < binaryStream.length(); i += 8) {
        // ÿ8λ�������ַ���ת��Ϊһ���ֽڲ�д��
        std::string byteString = binaryStream.substr(i, 8);
        char byte = static_cast<char>(std::bitset<8>(byteString).to_ulong());
        outputFile.write(&byte, sizeof(char));
    }

    // �ر��ļ�
    inputFile.close();
    outputFile.close();
}


// ��ȡ�ļ�������ѹ���������ָ���ļ�
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