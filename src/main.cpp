#include <cstdio>
#include <string>
#include "App.h"

using namespace std;

int main(int argc, char *argv[]) {
	string dbUrl;

	if (argc == 1) {
		dbUrl = "/home/albert/flashcards/flashcards.db";
	} else {
		dbUrl = argv[1];
	}

	App app(dbUrl);

	return 0;
}
