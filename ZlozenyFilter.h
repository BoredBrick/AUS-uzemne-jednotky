#pragma once
#include "heap_monitor.h"
#include "Filter.h"
#include "structures/list/array_list.h"
#include "structures/table/unsorted_sequence_table.h"


template <typename V>
class ZlozenyFilter {
public:
	structures::ArrayList<UniverzalnyFilter<V>*>* filtre_;
	ZlozenyFilter() {
		filtre_ = new structures::ArrayList<UniverzalnyFilter<V>*>();
	}
	void insertFilter(UniverzalnyFilter<V>* filter) {
		filtre_->add(filter);
	}
	bool splnaFilterAND(V& o) {
		for (auto filter : *filtre_) {
			if (!(*filter).splnaFilter(o)) { return false; }
		}
		return true;
	}

	bool splnaFilterOR(V& o) {
		for (auto filter : *filtre_) {
			if ((*filter).splnaFilter(o)) { return true; }
		}
		return false;
	}

	void vyfiltrujTabulkuAND(structures::SortedSequenceTable<std::wstring, V*>& filtrovana, structures::UnsortedSequenceTable<std::wstring, V*>& cistaTab) {

		for (auto item : filtrovana) {
			if (splnaFilterAND(*item->accessData())) {
				cistaTab.insert(item->getKey(), item->accessData());
			}
		}
	}

	void vyfiltrujTabulkuOR(structures::SortedSequenceTable<std::wstring, V*>& filtrovana, structures::UnsortedSequenceTable<std::wstring, V*>& cistaTab) {
		for (auto item : filtrovana) {
			if (splnaFilterOR(*item->accessData())) {
				cistaTab.insert(item->getKey(), item->accessData());
			}
		}
	}

	~ZlozenyFilter() {
		//for (auto element : *filtre_) {
		//	delete element;
		//}
		delete filtre_;
	}
};