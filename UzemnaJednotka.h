#pragma once
#include "heap_monitor.h"
#include <string>
#include "locationType.h"
#include "structures/table/sorted_sequence_table.h"

class UzemnaJednotka {
protected:
	structures::SortedSequenceTable<std::wstring, UzemnaJednotka*>* podCelky_;
	std::wstring nazov_;
	LocationType type_;
	int predProdObyv_ = 0;
	int prodObyv_ = 0;
	int poProdObyv_ = 0;
	double vymera_ = 0;
	double zastavanaPlocha_ = 0;
	UzemnaJednotka* okres_;
	UzemnaJednotka* kraj_;

	UzemnaJednotka(std::wstring nazov, LocationType type, UzemnaJednotka* okres,
		UzemnaJednotka* kraj) :
		podCelky_(new structures::SortedSequenceTable<std::wstring, UzemnaJednotka*>()),
		nazov_(nazov),
		type_(type),
		okres_(okres),
		kraj_(kraj) {
	}
public:

	void addObecData(double* data) {
		predProdObyv_ += static_cast<int>(data[0]);
		prodObyv_ += static_cast<int>(data[1]);
		poProdObyv_ += static_cast<int>(data[2]);
		vymera_ += data[3];
		zastavanaPlocha_ += data[4];
	}

	void setOkres(UzemnaJednotka* okres) {
		okres_ = okres;
	}

	void setKraj(UzemnaJednotka* kraj) {
		kraj_ = kraj;
	}

	UzemnaJednotka* getOkres() const {
		return okres_;
	}

	UzemnaJednotka* getKraj() const {
		return kraj_;
	}

	std::wstring getNazov() {
		return nazov_;
	}

	LocationType getType() {
		return type_;
	}

	int getPredProdObyv() const {
		return predProdObyv_;
	}

	int getProdObyv() const {
		return prodObyv_;
	}

	int getPoProdObyv() const {
		return poProdObyv_;
	}

	int getPocetObyvatelov() {
		return predProdObyv_ + prodObyv_ + poProdObyv_;
	}

	double getVymera() const {
		return vymera_;
	}

	double getZastavanaPlocha() const {
		return zastavanaPlocha_;
	}

	double getZastavanost() {
		return 100 * (zastavanaPlocha_ / vymera_);
	}

	bool patriDoVyssiehoCelku(UzemnaJednotka& vyssiCelok) {
		if (vyssiCelok.getType() == LocationType::Stat && this->getType() != LocationType::Stat) return true;
		if (&vyssiCelok == okres_ || &vyssiCelok == kraj_) return true;
		if (type_ == vyssiCelok.getType() || vyssiCelok.getType() == LocationType::Obec) return false;
		return false;
	}

	structures::SortedSequenceTable<std::wstring, UzemnaJednotka*>& getPodcelky() {
		return *podCelky_;
	}

	void insertPodcelok(std::wstring nazov, UzemnaJednotka& jednotka) {
		podCelky_->insert(nazov, &jednotka);
	}

	~UzemnaJednotka() {
		for (auto item : *podCelky_) {
			delete item->accessData();
			item = nullptr;
		}
		delete podCelky_;
		podCelky_ = nullptr;
	}
};
