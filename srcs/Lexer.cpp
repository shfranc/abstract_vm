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

	while( _pos < _input.size() )
	{
		if ( isWhitespaces(_input[_pos]) ) {
			std::cout << "space" << std::endl;
			skipWhitespaces();
			continue ;
		}
		if ( isNewline(_input[_pos]) ) {
			std::cout << "newline" << std::endl;
			skipNewline();
		}
		else
			return ( createToken() );
	}
	return "";
}

bool			Lexer::isWhitespaces( char c ) {

	return ( c == ' ' || c == '\t' ? 1 : 0 );
}

bool			Lexer::isNewline( char c ) {

	return ( c == '\n' ? 1 : 0 );
}

void			Lexer::skipWhitespaces( void ) {

	while ( _input[_pos] == ' ' || _input[_pos] == '\t' )
		_pos++;
}

void			Lexer::skipNewline( void ) {

	_pos++;
	_line++;
}

std::string		Lexer::createToken( void ) {

	size_t		len = 0;
	size_t		start = _pos;

	std::cout << "create token :";
	while ( !isWhitespaces(_input[_pos + len]) && !isNewline(_input[_pos + len]) )
	{
		std::cout << _input[_pos + len];
		len++;
	}
	_pos += len;

	std::cout << std::endl;
	
	return ( _input.substr (start, len) );
}