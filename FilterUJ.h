#pragma once
#include "heap_monitor.h"
#include "Filter.h"
#include "KriteriumUJ.h"
#include "locationType.h"
template < typename T>
class FilterPodlaHodnotyUJ : public FilterPodlaHodnoty<T, UzemnaJednotka> {
protected:
	FilterPodlaHodnotyUJ(Kriterium<T, UzemnaJednotka>& kriterium, T value) : FilterPodlaHodnoty< T, UzemnaJednotka>(kriterium, value) {}
};

template <typename T>
class FilterPodlaIntervaluUJ : public FilterPodlaIntervalu<T, UzemnaJednotka> {
protected:
	FilterPodlaIntervaluUJ(Kriterium<T, UzemnaJednotka>& kriterium, T min, T max) : FilterPodlaIntervalu< T, UzemnaJednotka>(kriterium, min, max) {}
};

class FilterUJNazov : public FilterPodlaHodnotyUJ< std::wstring> {
public:
	FilterUJNazov(KriteriumUJNazov& kriterium, std::wstring nazov) : FilterPodlaHodnotyUJ< std::wstring>(kriterium, nazov) {}
};

class FilterUJTyp : public FilterPodlaHodnotyUJ<LocationType> {
public:
	FilterUJTyp(KriteriumUJTyp& kriterium, LocationType type) : FilterPodlaHodnotyUJ< LocationType>(kriterium, type) {}
};

class FilterUJPrislusnost : public FilterPodlaHodnotyUJ<bool> {
public: // hodnotu davam na true, v podstate porovnam, ci vysledok najdenia prislusnosti sa rovna tej hodnote
	FilterUJPrislusnost(KriteriumUJPrislusnost& kriterium, bool val) : FilterPodlaHodnotyUJ< bool>(kriterium, val) {}
};

class FilterUJPocetObyvatelov : public FilterPodlaIntervaluUJ< int> {
public:
	FilterUJPocetObyvatelov(KriteriumUJPocetObyvatelov& kriterium, int min, int max) : FilterPodlaIntervaluUJ<int>(kriterium, min, max) {}
};

class FilterUJZastavanost : public FilterPodlaIntervaluUJ< double> {
public:
	FilterUJZastavanost(KriteriumUJZastavanost& kriterium, double min, double max) : FilterPodlaIntervaluUJ<double>(kriterium, min, max) {}
};