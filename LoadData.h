#pragma once
#include "heap_monitor.h"
#include <fstream>
#include <sstream>
#include "Obec.h"
#include "Stat.h"

class LoadData {
	std::wifstream obceFile_;
	std::wifstream clenenieFile_;
	Obec* makeObecFromLine(std::wstring line);
	structures::ArrayList<std::wstring*> splitClenenie(std::wstring line);
	void createClenenie(Stat& stat, std::wstring lineClenenie, std::wstring obecLine);
	Stat* stat_;
public:
	LoadData(std::string obceFile, std::string clenenieFile);
	~LoadData();
	Stat* getStat();
};
