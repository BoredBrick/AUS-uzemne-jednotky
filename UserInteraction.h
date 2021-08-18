#pragma once
#include "Stat.h"
#include <functional>
#include "ZlozenyFilter.h"
class UserInteraction {
	static void vypisPodcelky(UzemnaJednotka* jednotka);
	bool vzostupne();
	void selectFunctionality(Stat& stat);
	void infoOJednotkach(Stat& stat);
	void zoradenieJednotiek(Stat& stat);
	void filtrovanieVsetkychJednotiek(Stat& stat, ZlozenyFilter<UzemnaJednotka>& filter);
	void filtrovanieVsetkychJednotiekDoTabulky(Stat& stat, ZlozenyFilter<UzemnaJednotka>& filter, structures::UnsortedSequenceTable<std::wstring, UzemnaJednotka*>& cistaTab);

	static void printUdajeOJednotke(UzemnaJednotka& jednotka, Stat& stat);

public:
	static UzemnaJednotka* vyberJednotky(Stat& stat);
	UserInteraction(Stat& stat);
};