#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures {
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T> {
		void quick(UnsortedSequenceTable<K, T>& table, int min, int max);
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table) {
		quick(table, 0, table.size() - 1);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::quick(UnsortedSequenceTable<K, T>& table, int min, int max) {
		K pivot = table.getItemAtIndex((min + max) / 2).getKey();
		auto lavy = min;
		auto pravy = max;
		do {
			while (table.getItemAtIndex(lavy).getKey() < pivot) { lavy++; }
			while (table.getItemAtIndex(pravy).getKey() > pivot) { pravy--; }
			if (lavy <= pravy) {
				table.swap(lavy, pravy);
				lavy++;
				pravy--;

			}
		} while (lavy <= pravy);
		if (min < pravy) { quick(table, min, pravy); }
		if (lavy < max) { quick(table, lavy, max); }
	}
}