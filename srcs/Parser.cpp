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

	while ( (token = lexer.getNextToken()) != ""  )
		_instructions.push_back(token);
	// verifier si c'est un token reconnu ?
	// if PUSH or ASSERT --> getNextToken pour chopper la Value.
}

// PRIVATE

// ACCESSOR
std::vector<std::string> const &	Parser::getInstructions( void ) const { return _instructions; }


// OPERATOR <<

std::ostream &		operator<<( std::ostream & o, Parser const & src ) {
	std::vector<std::string> const &	v = src.getInstructions();
	size_t	len = v.size();

	for (size_t i = 0; i < len; i++)
	{
		o << v[i] << std::endl;
	}

	return o;
}