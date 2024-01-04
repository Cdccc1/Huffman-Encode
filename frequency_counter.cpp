#include "frequency_counter.h"


FrequencyCounter::FrequencyCounter() {}


FrequencyCounter::FrequencyCounter(const std::string& filename) {
    // �ڹ��캯���м����ַ�Ƶ��
    this->frequencyTable = countFrequency(filename);
}


FrequencyCounter::~FrequencyCounter() {}

// �������������ֽ����ж�ȡ��һ��UTF-8������ַ�
std::string readUTF8Char(std::ifstream& stream) {
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

// �����ַ�Ƶ��
std::map<std::string, int> FrequencyCounter::countFrequency(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary); // �Զ����Ʒ�ʽ���Է�ֹ�ַ�ת��

    if (!file.is_open()) {
        throw std::runtime_error("FrequencyCounter �޷����ļ�");
    }
    

    std::map<std::string, int> frequencyTable;

    while (!file.eof()) {
        std::string utf8char = readUTF8Char(file);
        if (!utf8char.empty()) {
            frequencyTable[utf8char]++;
        }
    }
    file.close();
    return frequencyTable;
}


void FrequencyCounter::writeFrequency(const std::string& outputFilename) {
    std::ofstream outFile(outputFilename, std::ios::binary); // �Զ����Ʒ�ʽ�򿪣���ֹ�ַ�ת��

    if (!outFile.is_open()) {
        throw std::runtime_error("FrequencyCounter �޷������ļ�");
    }

    for (const auto& pair : frequencyTable) {
        // ��ÿ���ַ�����Ƶ��д���ļ�
        outFile << pair.first << ": " << pair.second << "\n";
    }

    outFile.close();
}



