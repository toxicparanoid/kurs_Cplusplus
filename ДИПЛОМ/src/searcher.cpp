#include "config.h"

int main() {
	Config cfg;
	cfg.load("config.ini");
	cfg.print();

	std::cout << "\nSearcher started (stub)\n";
	std::cout << "Ready for search queries...\n";

	return 0;
}