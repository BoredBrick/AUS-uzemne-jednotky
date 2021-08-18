#pragma once
#include "heap_monitor.h"
#include "UzemnaJednotka.h"

class Okres : public UzemnaJednotka {
public:
	Okres(std::wstring nazov, UzemnaJednotka* kraj) : UzemnaJednotka(nazov, LocationType::Okres, nullptr, kraj) {
	}
};
