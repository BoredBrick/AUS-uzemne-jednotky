#pragma once
#include "heap_monitor.h"

template <typename V>
class UniverzalnyFilter {
public:
	virtual bool splnaFilter(V& o) = 0;
};