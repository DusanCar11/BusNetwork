#pragma once
#include "Mreza.h"
class Format;
class Generator {
protected:
	Format* FormatIspisa;
public:
	Generator() {}
	void AddFormat(Format* f) { FormatIspisa = f; }
	~Generator() { FormatIspisa = nullptr; }
};
