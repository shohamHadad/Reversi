#include "../include/Square.h"
using namespace std;
#include <iostream>

/**
 * function name: Square
 * input: 2 integers
 * output: a new Square object
 * operation: constructor
 */
Square::Square(int x, int y): x(x), y(y), type(' ') {
}

/**
 * function name: print
 * input: void
 * output: void
 * operation: print out the square values
 */
void Square::print() {
	cout << "(" << x << "," << y << ")";
}

/**
 * function name: getX
 * input: void
 * output: the square's x value
 * operation: return the square's x value
 */
int Square::getX() {
	return this->x;
}

/**
 * function name: getY
 * input: void
 * output: the square's y value
 * operation: return the square's y value
 */
int Square::getY() {
	return this->y;
}

/**
 * function name: equals
 * input: Square
 * output: boolean
 * operation: checks if the given square is equal to this square
 */
bool Square::operator ==(const Square &other) const {
	if (other.x == x && other.y == y && other.type == type) {
		return true;
	}
	return false;
}

/**
 * function name: setType
 * input: char
 * output: void
 * operation: set the square's type
 */
void Square::setType(char t) {
	type = t;
}

/**
 * function name: getType
 * input: void
 * output: char
 * operation: returns the square's type
 */
char Square::getType() {
	return type;
}
