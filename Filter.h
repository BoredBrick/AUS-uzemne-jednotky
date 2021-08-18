#pragma once
#include "heap_monitor.h"
#include "Kriterium.h"
#include "UniverzalnyFilter.h"
template <typename T, typename V> // T je hodnota, ktora sa vracia(int) V je co - UJ
class Filter : public UniverzalnyFilter<V> {
protected:
	Kriterium<T, V>* kriterium_; //vysledok hodnotenia (int), co do neho davam - UJ
	Filter(Kriterium<T, V>& kriterium) : kriterium_(&kriterium) {}
public:
	~Filter() {
		delete kriterium_;
	}
	Kriterium<T, V>* getKriterium() { return kriterium_; }
};

template <typename T, typename V>
class FilterPodlaHodnoty : public Filter<T, V> {
protected:
	T value_;
	FilterPodlaHodnoty(Kriterium<T, V>& kriterium, T value) : Filter(kriterium), value_(value) {}
public:
	bool splnaFilter(V& o)  override {
		return Filter<T, V>::kriterium_->evaluate(o) == value_;
	}
};

template < typename T, typename V>
class FilterPodlaIntervalu : public Filter<T, V> {
protected:
	T min_;
	T max_;
	FilterPodlaIntervalu(Kriterium<T, V>& kriterium, T min, T max) : Filter(kriterium), min_(min), max_(max) {}
public:
	bool splnaFilter(V& o)  override {
		T value = Filter<T, V>::kriterium_->evaluate(o);
		return value >= min_ && value <= max_;
	}
};
