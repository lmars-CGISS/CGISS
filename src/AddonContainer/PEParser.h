#pragma once
#include "windows.h"
#include <string>
#include <vector>
class PEParser
{
	HMODULE m_hMod;
public:
	PEParser(const char* file);
	virtual ~PEParser(void);
	bool EnumExport(std::vector<std::string>& vec);
};
 