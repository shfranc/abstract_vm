#include "Parser.hpp"

Parser::Parser( void ) {
	
	return;
}

Parser::~Parser( void ) {

	return;
}

void	Parser::parse( std::string input ) {

	Lexer			lexer(input);
	Token			*token;

	while ( (token = lexer.getNextToken()) != nullptr ) {
		if ( token->getType() != SEP) {
			std::cout << "adding " << token->getStr() << std::endl;
			_instructions.push_back(*token);
		}
		std::cout << "je delete: ";
		delete token;
	}
	// verifier si c'est un token reconnu ?
	// if PUSH or ASSERT --> getNextToken pour chopper la Value.
}

// PRIVATE

// ACCESSOR
std::vector<Token> const &	Parser::getInstructions( void ) const { return _instructions; }


// OPERATOR <<

std::ostream &		operator<<( std::ostream & o, Parser const & src ) {
	std::vector<Token> const &	v = src.getInstructions();
	size_t	len = v.size();

	for (size_t i = 0; i < len; i++)
	{
		o << v[i].getStr() << "\t" << v[i].getType() << std::endl;
	}

	return o;
}