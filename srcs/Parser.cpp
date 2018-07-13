#include "Parser.hpp"

Parser::Parser( void ) {
	
	return;
}

Parser::~Parser( void ) {

	return;
}

void	Parser::parse( std::string input ) {

	Lexer			lexer(input);
	std::string		token;

	token = lexer.getNextToken();
	// verifier si c'est un token reconnu ?
	// if PUSH or ASSERT --> getNextToken pour chopper la Value.
	_instructions.push_back(token);
}

// PRIVATE

// ACCESSOR
std::vector<std::string> const &	Parser::getInstructions( void ) const { return _instructions; }


// OPERATOR <<

std::ostream &		operator<<( std::ostream & o, Parser const & src ) {
	std::vector<std::string> const &	v = src.getInstructions();

	o << v[0];

	return o;
}