#pragma once
#include "heap_monitor.h"
#include "UzemnaJednotka.h"

class Stat : public UzemnaJednotka {
public:
	Stat() : UzemnaJednotka(L"Slovensko", LocationType::Stat, nullptr, nullptr) {
	}
};