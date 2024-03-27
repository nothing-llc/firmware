#ifndef ARDUINO_PRINT_H
#define ARDUINO_PRINT_H

class Print {
public:
	virtual void write() {}
	virtual void print(const char*) {}
	virtual void println() {}
};

#endif
