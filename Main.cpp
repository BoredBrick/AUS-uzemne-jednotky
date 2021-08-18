#include "heap_monitor.h"
#include <iostream>
#include "Stat.h"
#include "LoadData.h"
#include <Windows.h>
#include "UserInteraction.h"
using namespace std;

int main() {
	initHeapMonitor();
	locale::global(locale("slovak"));
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
	LoadData loader("obce.csv", "clenenie.csv");
	auto Slovensko = loader.getStat();
	UserInteraction inter(*Slovensko);

	return 0;
}