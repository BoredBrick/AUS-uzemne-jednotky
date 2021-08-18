#pragma once
#include "Kriterium.h"
#include "heap_monitor.h"

template <typename T>
class KriteriumUJ : public Kriterium<T, UzemnaJednotka> {
public:
	T evaluate(UzemnaJednotka& uzemnaJednotka)  override = 0;
};

class KriteriumUJNazov : public KriteriumUJ<std::wstring> {
public:
	std::wstring evaluate(UzemnaJednotka& uzemnaJednotka)  override { return uzemnaJednotka.getNazov(); }
};

class KriteriumUJTyp : public KriteriumUJ<LocationType> {
public:
	LocationType evaluate(UzemnaJednotka& uzemnaJednotka)  override { return uzemnaJednotka.getType(); }
};

class KriteriumUJPrislusnost : public KriteriumUJ<bool> {
	UzemnaJednotka& vyssiCelok_;
public:
	KriteriumUJPrislusnost(UzemnaJednotka& vyssiCelok_) : vyssiCelok_(vyssiCelok_) {}
	bool evaluate(UzemnaJednotka& uzemnaJednotka)  override {
		return uzemnaJednotka.patriDoVyssiehoCelku(vyssiCelok_);
	}
};

class KriteriumUJPocetPreproduktivnychObyvatelov : public KriteriumUJ<int> {
public:
	int evaluate(UzemnaJednotka& uzemnaJednotka)  override { return uzemnaJednotka.getPredProdObyv(); }
};

class KriteriumUJPocetProduktivnychObyvatelov : public KriteriumUJ<int> {
public:
	int evaluate(UzemnaJednotka& uzemnaJednotka)  override { return uzemnaJednotka.getProdObyv(); }
};

class KriteriumUJPocetPoproduktivnychObyvatelov : public KriteriumUJ<int> {
public:
	int evaluate(UzemnaJednotka& uzemnaJednotka)  override { return uzemnaJednotka.getPoProdObyv(); }
};

class KriteriumUJPocetObyvatelov : public KriteriumUJ<int> {
public:
	int evaluate(UzemnaJednotka& uzemnaJednotka)  override { return uzemnaJednotka.getPocetObyvatelov(); }
};

class KriteriumUJCelkovaVymera : public KriteriumUJ<double> {
public:
	double evaluate(UzemnaJednotka& uzemnaJednotka)  override { return uzemnaJednotka.getVymera(); }
};

class KriteriumUJZastavanaPlocha : public KriteriumUJ<double> {
public:
	double evaluate(UzemnaJednotka& uzemnaJednotka)  override { return uzemnaJednotka.getZastavanaPlocha(); }
};

class KriteriumUJZastavanost : public KriteriumUJ<double> {
public:
	double evaluate(UzemnaJednotka& uzemnaJednotka)  override { return uzemnaJednotka.getZastavanost(); }
};