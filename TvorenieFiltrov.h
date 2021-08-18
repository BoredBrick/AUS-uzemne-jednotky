#pragma once
#include <string>

#include "heap_monitor.h"
#include "Stat.h"
#include "FilterUJ.h"
#include "ZlozenyFilter.h"

class  TvorenieFiltrov {
	bool pouzitieFiltra(std::string nazovFilter);
public:
	FilterUJTyp* makeFilterTyp();
	FilterUJPrislusnost* makeFilterPrislusnost(Stat& stat);
	FilterUJNazov* makeFilterNazov();
	FilterUJPocetObyvatelov* makeFilterPocetObyvatelov();
	FilterUJZastavanost* makeFilterZastavanost();
};

class TvorenieZlozenychFiltrov {
	FilterUJTyp* filterUJTyp;
	FilterUJPrislusnost* filterUJprislusnost;
	FilterUJNazov* filterUJNazov;
	FilterUJPocetObyvatelov* filterUJPocetObyvatelov;
	FilterUJZastavanost* filterUJZastavanost;
public:
	ZlozenyFilter<UzemnaJednotka>*  vytvorFiltreInfoOJednotkach(Stat& stat);
	ZlozenyFilter<UzemnaJednotka>* vytvorFiltreZoradenieJednotiek(Stat& stat);
	~TvorenieZlozenychFiltrov() {
		delete filterUJNazov;
		delete filterUJPocetObyvatelov;
		delete filterUJTyp;
		delete filterUJZastavanost;
		delete filterUJprislusnost;
	}
};
