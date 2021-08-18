#pragma once
#include "heap_monitor.h"
#include <string>
#include "UzemnaJednotka.h"

class Kraj : public UzemnaJednotka {
public:

	Kraj(std::wstring nazov) : UzemnaJednotka(nazov, LocationType::Kraj, nullptr, nullptr) {
	}
};
