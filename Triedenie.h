#pragma once
#include "heap_monitor.h"
#include "Kriterium.h"
#include "structures/table/unsorted_sequence_table.h"
template <   typename V>
class Triedenie {
	static void quick(structures::UnsortedSequenceTable<std::wstring, UzemnaJednotka*>& table, Kriterium<V, UzemnaJednotka>& krit, bool vzostupne, int min, int max) {
		auto pivot = krit.evaluate(*(table.getItemAtIndex((min + max) / 2).accessData()));
		auto lavy = min;
		auto pravy = max;
		do {
			if (vzostupne) {
				while (krit.evaluate(*(table.getItemAtIndex(lavy).accessData())) < pivot) { lavy++; }
				while (krit.evaluate(*(table.getItemAtIndex(pravy).accessData())) > pivot) { pravy--; }
			}
			else {
				while (krit.evaluate(*(table.getItemAtIndex(lavy).accessData())) > pivot) { lavy++; }
				while (krit.evaluate(*(table.getItemAtIndex(pravy).accessData())) < pivot) { pravy--; }
			}
			if (lavy <= pravy) {
				table.swap(lavy, pravy);
				lavy++;
				pravy--;
			}
		} while (lavy <= pravy);
		if (min < pravy) { quick(table, krit, vzostupne, min, pravy); }
		if (lavy < max) { quick(table, krit, vzostupne, lavy, max); }
	}
public:
	static void sort(structures::UnsortedSequenceTable<std::wstring, UzemnaJednotka*>& table, Kriterium<V, UzemnaJednotka>& krit, bool vzostupne) {
		quick(table, krit, vzostupne, 0, table.size() - 1);
	}
};