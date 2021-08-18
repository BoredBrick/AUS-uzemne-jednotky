#include "UserInteraction.h"
#include <iostream>
#include "TvorenieFiltrov.h"
#include "structures/table/unsorted_sequence_table.h"
#include "ZlozenyFilter.h"
#include <iomanip>
#include "Triedenie.h"
using std::wcout;
using std::cout;
using std::endl;
using std::cin;

void UserInteraction::vypisPodcelky(UzemnaJednotka* jednotka) {
	for (auto item : jednotka->getPodcelky()) {
		wcout << item->getKey() << endl;
	}
}

bool UserInteraction::vzostupne() {
	cout << "\n1. Zoradenie vzostupne" << endl;
	cout << "2. Zoradenie zostupne" << endl;
	int choice;
	cin >> choice;
	return (choice == 1) ? true : false;
}

void UserInteraction::selectFunctionality(Stat& stat) {
	int choice;
	cout << "Zvolte pozadovanu funkcionalitu:" << endl;
	cout << "1. Vypisanie informacii o uzemnych jednotkach" << endl;
	cout << "2. Zoradenie uzemnych jednotiek splnajucich dany filter" << endl;
	cin >> choice;
	if (choice == 1) { infoOJednotkach(stat); }
	else { zoradenieJednotiek(stat); }
}

void UserInteraction::zoradenieJednotiek(Stat& stat) {
	TvorenieZlozenychFiltrov tvoric{};
	auto zlozenyFilter = tvoric.vytvorFiltreZoradenieJednotiek(stat);

	auto filtered = new structures::UnsortedSequenceTable<std::wstring, UzemnaJednotka*>;
	filtrovanieVsetkychJednotiekDoTabulky(stat, *zlozenyFilter, *filtered);

	cout << "Vyberte kriterium na zoradenie: " << endl;
	cout << "1. Nazov " << endl;
	cout << "2. Pocet obyvatelov" << endl;
	cout << "3. Zastavanost " << endl;
	int choice;
	cin >> choice;
	switch (choice) {
	case 1:
	{
		KriteriumUJNazov krit;
		Triedenie<std::wstring>::sort(*filtered, krit, vzostupne());
		for (auto item : *filtered) {
			wcout << item->getKey() << endl;
		}
		break;
	}
	case 2:
	{
		KriteriumUJPocetObyvatelov kritObyv;
		Triedenie<int>::sort(*filtered, kritObyv, vzostupne());
		for (auto item : *filtered) {
			wcout << item->getKey() << " " << kritObyv.evaluate(*item->accessData()) << endl;
		}
		break;
	}
	case 3:
	{
		KriteriumUJZastavanost kritZastavanost;
		Triedenie<double>::sort(*filtered, kritZastavanost, vzostupne());
		for (auto item : *filtered) {
			wcout << item->getKey() << " " << kritZastavanost.evaluate(*item->accessData()) << endl;
		}
		break;
	}
	}

	delete zlozenyFilter;
	delete filtered;
}
void UserInteraction::filtrovanieVsetkychJednotiekDoTabulky(Stat& stat, ZlozenyFilter<UzemnaJednotka>& filter, structures::UnsortedSequenceTable<std::wstring, UzemnaJednotka*>& cistaTab) {
	int choice;
	cout << "\n1. Kazdy filter musi byt splneny" << endl;
	cout << "2. Aspon jeden filter musi byt splneny" << endl;
	cin >> choice;

	std::function<void(structures::SortedSequenceTable<std::wstring, UzemnaJednotka*>&,
		structures::UnsortedSequenceTable<std::wstring, UzemnaJednotka*>&)> f;
	std::function<bool(UzemnaJednotka&)> fStat;

	if (choice == 1) {
		f = [&filter](auto& tabulka, auto& cistaTab) {return filter.vyfiltrujTabulkuAND(tabulka, cistaTab); };
		fStat = [&filter](auto& jednotka) {return filter.splnaFilterAND(jednotka); };
	}
	else {
		f = [&filter](auto& tabulka, auto& cistaTab) {return filter.vyfiltrujTabulkuOR(tabulka, cistaTab); };
		fStat = [&filter](auto& jednotka) {return filter.splnaFilterOR(jednotka); };
	}
	if (fStat(stat)) { cistaTab.insert(stat.getNazov(), &stat); }
	f(stat.getPodcelky(), cistaTab);
	for (auto kraj : stat.getPodcelky()) {
		f(kraj->accessData()->getPodcelky(), cistaTab);
		for (auto okres : kraj->accessData()->getPodcelky()) {
			f(okres->accessData()->getPodcelky(), cistaTab);
		}
	}
}

void UserInteraction::infoOJednotkach(Stat& stat) {
	TvorenieZlozenychFiltrov tvoric{};
	auto zlozenyFilter = tvoric.vytvorFiltreInfoOJednotkach(stat);
	filtrovanieVsetkychJednotiek(stat, *zlozenyFilter);
	delete zlozenyFilter;
}

void UserInteraction::filtrovanieVsetkychJednotiek(Stat& stat, ZlozenyFilter<UzemnaJednotka>& filter) {
	int choice;
	cout << "\n1. Kazdy filter musi byt splneny" << endl;
	cout << "2. Aspon jeden filter musi byt splneny" << endl;

	cin >> choice;
	std::function<bool(UzemnaJednotka&)> f;
	if (choice == 1) {
		f = [&filter](auto& jednotka) {return filter.splnaFilterAND(jednotka); };
	}
	else {
		f = [&filter](auto& jednotka) {return filter.splnaFilterOR(jednotka); };
	}
	if (f(stat)) { printUdajeOJednotke(stat, stat); }
	for (auto kraj : stat.getPodcelky()) {
		if (f(*kraj->accessData())) { printUdajeOJednotke(*kraj->accessData(), stat); }
		for (auto okres : kraj->accessData()->getPodcelky()) {
			if (f(*okres->accessData())) { printUdajeOJednotke(*okres->accessData(), stat); }
			for (auto obec : okres->accessData()->getPodcelky()) {
				if (f(*obec->accessData())) {
					printUdajeOJednotke(*obec->accessData(), stat);
				}
			}
		}
	}
}

void UserInteraction::printUdajeOJednotke(UzemnaJednotka& jednotka, Stat& stat) {
	std::cout.precision(2);
	cout << std::fixed;
	wcout << jednotka.getNazov();
	if (jednotka.getOkres()) { wcout << " - okres " << jednotka.getOkres()->getNazov(); }
	if (jednotka.getKraj()) { wcout << " - " << jednotka.getKraj()->getNazov() << " kraj "; }
	wcout << " - " << stat.getNazov() << endl;
	cout << "Pocet obyvatelov: " << jednotka.getPocetObyvatelov() << endl;
	cout << "Pocet preproduktivnych obyvatelov: " << jednotka.getPredProdObyv() << endl;
	cout << "Pocet produktivnych obyvatelov: " << jednotka.getProdObyv() << endl;
	cout << "Pocet poproduktivnych obyvatelov: " << jednotka.getPoProdObyv() << endl;
	cout << "Celkova vymera: " << jednotka.getVymera() << " km2" << endl;
	cout << "Zastavana plocha: " << jednotka.getZastavanaPlocha() << " km2" << endl;
	cout << "Zastavanost: " << jednotka.getZastavanost() << "%" << "\n" << endl;
}

UzemnaJednotka* UserInteraction::vyberJednotky(Stat& stat) {
	UzemnaJednotka* zvolena = &stat;
	std::wstring odpoved = L" ";
	while (odpoved != L"x" && zvolena->getType() != LocationType::Okres) {
		wcout << "\nZvolena jednotka: " << zvolena->getNazov() << "\n" << endl;
		vypisPodcelky(zvolena);
		std::wcin >> odpoved;
		if (odpoved != L"x") {
			try {
				zvolena = (*zvolena).getPodcelky()[odpoved];
			}
			catch (std::exception& e) {
				cout << "\n--Neplatna volba--\n" << endl;
			}
		}
	}
	return zvolena;
}

UserInteraction::UserInteraction(Stat& stat) {
	selectFunctionality(stat);
}