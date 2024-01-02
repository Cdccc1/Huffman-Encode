#pragma once
class hash_cmp
{
};

#pragma once
#include <string>
class FileHasher
{
public:
	FileHasher();
	unsigned long long computeHash(const std::string& filename);
	bool compareHash(FileHasher y);
private:
	unsigned long long Hash;
};