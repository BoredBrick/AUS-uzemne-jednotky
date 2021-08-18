#include "TvorenieFiltrov.h"
#include <iostream>
#include "locationType.h"
#include "UserInteraction.h"
using std::wcout;
using std::cout;
using std::endl;
using std::cin;

bool TvorenieFiltrov::pouzitieFiltra(std::string nazovFilter) {
	cout << "\nChcete pouzit filter " << nazovFilter << endl;
	cout << "1. Ano" << endl;
	cout << "2. Nie\n" << endl;
	int choice;
	cin >> choice;
	return choice == 1 ? true : false;
}

FilterUJTyp* TvorenieFiltrov::makeFilterTyp() {
	if (pouzitieFiltra("UJTyp")) {
		cout << "\nZvolte si pozadovany typ uzemnej jednotky" << endl;
		cout << "1. Obec" << endl;
		cout << "2. Okres" << endl;
		cout << "3. Kraj" << endl;
		cout << "4. Stat" << endl;
		LocationType choiceType;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			choiceType = LocationType::Obec;
			break;
		case 2:
			choiceType = LocationType::Okres;
			break;
		case 3:
			choiceType = LocationType::Kraj;
			break;
		case 4:
			choiceType = LocationType::Stat;
			break;
		}
		auto kritTyp = new KriteriumUJTyp();
		return new FilterUJTyp(*kritTyp, choiceType);
	}
	return nullptr;
}

FilterUJPrislusnost* TvorenieFiltrov::makeFilterPrislusnost(Stat& stat) {
	if (pouzitieFiltra("UJPrislusnost")) {
		cout << "\nZvolte si vyssi celok, potvrdite 'x'\n" << endl;
		auto vyssiCelok = UserInteraction::vyberJednotky(stat);
		auto kritPris = new KriteriumUJPrislusnost(*vyssiCelok);
		return new FilterUJPrislusnost(*kritPris, true);
	}
	return nullptr;
}

FilterUJNazov* TvorenieFiltrov::makeFilterNazov() {
	if (pouzitieFiltra("UJNazov")) {
		std::wstring nazov;
		cout << "Zvolte nazov: " << endl;
		std::wcin >> nazov;
		auto kritNazov = new KriteriumUJNazov();
		return new FilterUJNazov(*kritNazov, nazov);
	}
	return nullptr;
}

FilterUJPocetObyvatelov* TvorenieFiltrov::makeFilterPocetObyvatelov() {
	if (pouzitieFiltra("UJPocetObyvatelov")) {
		cout << "Zadajte minimalny pocet obyvatelov: " << endl;
		int min;
		cin >> min;
		cout << "Zadajte maximalny pocet obyvatelov: " << endl;
		int max;
		cin >> max;
		auto kritPocetObyv = new KriteriumUJPocetObyvatelov();
		return new FilterUJPocetObyvatelov(*kritPocetObyv, min, max);
	}

	return nullptr;
}

FilterUJZastavanost* TvorenieFiltrov::makeFilterZastavanost() {
	if (pouzitieFiltra("UJZastavanost")) {
		cout << "Zadajte minimalnu zastavanost: " << endl;
		double min;
		cin >> min;
		cout << "Zadajte maximalnu zastavanost: " << endl;
		double max;
		cin >> max;
		auto kritZastavanost = new KriteriumUJZastavanost();
		return new FilterUJZastavanost(*kritZastavanost, min, max);
	}
	return nullptr;
}

ZlozenyFilter<UzemnaJednotka>* TvorenieZlozenychFiltrov::vytvorFiltreInfoOJednotkach(Stat& stat) {
	TvorenieFiltrov tvoric{};
	filterUJTyp = tvoric.makeFilterTyp();
	filterUJprislusnost = tvoric.makeFilterPrislusnost(stat);
	filterUJNazov = tvoric.makeFilterNazov();
	filterUJPocetObyvatelov = tvoric.makeFilterPocetObyvatelov();
	filterUJZastavanost = tvoric.makeFilterZastavanost();

	auto zlozenyFilter = new ZlozenyFilter<UzemnaJednotka>();
	if (filterUJTyp) { zlozenyFilter->insertFilter(filterUJTyp); }
	if (filterUJprislusnost) { zlozenyFilter->insertFilter(filterUJprislusnost); }
	if (filterUJNazov) { zlozenyFilter->insertFilter(filterUJNazov); }
	if (filterUJPocetObyvatelov) { zlozenyFilter->insertFilter(filterUJPocetObyvatelov); }
	if (filterUJZastavanost) { zlozenyFilter->insertFilter(filterUJZastavanost); }

	return zlozenyFilter;
}

ZlozenyFilter<UzemnaJednotka>* TvorenieZlozenychFiltrov::vytvorFiltreZoradenieJednotiek(Stat& stat) {
	TvorenieFiltrov tvoric{};
	filterUJTyp = tvoric.makeFilterTyp();
	filterUJprislusnost = tvoric.makeFilterPrislusnost(stat);
	auto zlozenyFilter = new ZlozenyFilter<UzemnaJednotka>();

	if (filterUJTyp) { zlozenyFilter->insertFilter(filterUJTyp); }
	if (filterUJprislusnost) { zlozenyFilter->insertFilter(filterUJprislusnost); }
	return zlozenyFilter;
}