#include "Lexer.hpp"

Lexer::Lexer( void ) { // n'a pas de sens
	
	return;
}

Lexer::Lexer( std::string input ) : _pos(0), _line(1), _input(input) {
	
	return;
}

Lexer::~Lexer( void ) {

	return;
}

std::string		Lexer::getNextToken( void ) {

	return "test";
}
