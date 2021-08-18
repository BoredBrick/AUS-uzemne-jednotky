#pragma once
#include "heap_monitor.h"
#include <string>
#include "UzemnaJednotka.h"

class Obec : public UzemnaJednotka {
public:
	Obec(std::wstring nazov, int pred_prod_obyv, int prod_obyv, int po_pord_obyv, double vymera,
		double zastavana_plocha)
		: UzemnaJednotka(nazov, LocationType::Obec, nullptr, nullptr) {
		predProdObyv_ = pred_prod_obyv;
		prodObyv_ = prod_obyv;
		poProdObyv_ = po_pord_obyv;
		vymera_ = vymera;
		zastavanaPlocha_ = zastavana_plocha;
	}

	double* getObecData() {
		static double data[5];
		data[0] = predProdObyv_;
		data[1] = prodObyv_;
		data[2] = poProdObyv_;
		data[3] = vymera_;
		data[4] = zastavanaPlocha_;
		return data;
	}
};