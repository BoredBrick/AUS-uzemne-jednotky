#include "LoadData.h"
#include <iostream>
#include <sstream>
#include "heap_monitor.h"
#include "Kraj.h"
#include "Obec.h"
#include "Okres.h"
#include "Stat.h"
#include "string"
#include "ZlozenyFilter.h"
#include "structures/table/unsorted_sequence_table.h"
using std::wstring;

structures::ArrayList<wstring*> LoadData::splitClenenie(wstring line) {
	std::wistringstream lineStream(line);
	structures::ArrayList<wstring*> splitted;
	wstring s;
	getline(lineStream, s, L';');
	splitted.add(new wstring(s));
	getline(lineStream, s, L' ');
	getline(lineStream, s, L';');
	splitted.add(new wstring(s));

	getline(lineStream, s, L';');
	if (s[s.length() - 1] == ',') { s.pop_back(); }
	splitted.add(new wstring(s));
	return splitted;
}

Obec* LoadData::makeObecFromLine(std::wstring line) {
	std::wistringstream lineStream(line);
	structures::ArrayList<wstring*> obecData;
	while (lineStream) {
		wstring s;
		if (!getline(lineStream, s, L';')) break;
		obecData.add(new wstring(s));
	}

	Obec* newObec = new Obec(*obecData[0], stoi(*obecData[1]), stoi(*obecData[2]), stoi(*obecData[3]),
		stoi(*obecData[4]) / static_cast<double>(1000000), stoi(*obecData[5]) / static_cast <double>(1000000));

	for (auto data : obecData) {
		delete data;
	}

	return newObec;
}

void LoadData::createClenenie(Stat& stat, wstring lineClenenie, std::wstring obecLine) {
	auto clenenieData = splitClenenie(lineClenenie);
	auto newObec = this->makeObecFromLine(obecLine);
	auto dataOObci = newObec->getObecData();
	stat.addObecData(dataOObci);
	UzemnaJednotka* okres = nullptr;
	UzemnaJednotka* kraj = nullptr;

	if (!stat.getPodcelky().tryFind(*clenenieData[2], kraj)) {
		kraj = new Kraj(*clenenieData[2]);
		stat.insertPodcelok(*clenenieData[2], *kraj);
	}
	kraj->addObecData(dataOObci);

	if (!kraj->getPodcelky().tryFind(*clenenieData[1], okres)) {
		okres = new Okres(*clenenieData[1], kraj);
		kraj->insertPodcelok(*clenenieData[1], *okres);
	}
	okres->addObecData(dataOObci);

	newObec->setKraj(kraj);
	newObec->setOkres(okres);
	okres->insertPodcelok(*clenenieData[0], *newObec);

	for (auto dataDel : clenenieData) {
		delete dataDel;
	}
}

LoadData::LoadData(std::string obceFile, std::string clenenieFile) :
	stat_(new Stat()) {
	obceFile_.open(obceFile);
	clenenieFile_.open(clenenieFile);
	wstring obecLine;
	std::getline(obceFile_, obecLine); //skip hlaviciek
	std::getline(clenenieFile_, obecLine);
	while (std::getline(obceFile_, obecLine)) {
		std::wstring clenenie;
		std::getline(clenenieFile_, clenenie);
		createClenenie(*stat_, clenenie, obecLine);
	}
}

LoadData::~LoadData() {
	delete stat_;
	stat_ = nullptr;
}

Stat* LoadData::getStat() {
	return stat_;
}