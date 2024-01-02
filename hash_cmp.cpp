#include "hash_cmp.h"
#include <fstream>
#include <iostream>
#include <sstream>
FileHasher::FileHasher() {}
unsigned long long FileHasher::computeHash(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return 0;
	}
	else
	{
		std::ostringstream content;
		content << file.rdbuf();
		std::string fileContent = content.str();
		unsigned long long hash = 0, count = 0;
		for (auto x : fileContent)
		{
			hash = x * count;
			count++;
		}
		Hash = hash;
		return hash;
	}
	
}
bool FileHasher::compareHash( FileHasher y)
{
	return this->Hash==y.Hash;
}