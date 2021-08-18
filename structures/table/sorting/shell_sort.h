#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include <cmath>
namespace structures {
	/// <summary> Triedenie Shell sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class ShellSort : public Sort<K, T> {
		void shell(UnsortedSequenceTable<K, T>& table, int step);
	public:
		/// <summary> Utriedi tabulku triedenim Shell sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void ShellSort<K, T>::sort(UnsortedSequenceTable<K, T>& table) {
		auto step = log10(table.size());
		shell(table, step);
	}

	template<typename K, typename T>
	void ShellSort<K, T>::shell(UnsortedSequenceTable<K, T>& table, int step) {
		for (int delta = 0; delta <= step - 1; delta++) {
			for (int i = delta; i <= table.size() - 1; i += step) {
				auto j = i;
				while ((j - step >= delta) && (table.getItemAtIndex(j).getKey() < table.getItemAtIndex(j - step).getKey())) {
					table.swap(j, j - step);
					j -= step;

				}
				notify();

			}
		}
		if (step > 1) {
			shell(table, step - 1);
		}
	}
}