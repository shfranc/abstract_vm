#include "Parser.hpp"

Parser::Parser( void ) {
	
	return;
}

Parser::~Parser( void ) {

	return;
}

void	Parser::parse( std::string input ) {

	Lexer			lexer(input);
	Token			currentToken;
	Token			token;

	currentToken = "";
	while ( (token = lexer.getNextToken()) != "" ) {

		if (currentToken == "add" && token == "\n")
		{
			std::cout << "adding " << currentToken << std::endl;
			_instructions.push_back(currentToken;
		}
		else
			std::cerr << "more than one instruction on the same line" << std::endl;
		currentToken = token;

	}
	// verifier si c'est un token reconnu ?
	// if PUSH or ASSERT --> getNextToken pour chopper la Value.
}

// PRIVATE

// ACCESSOR
std::vector<std::string> const &	Parser::getInstructions( void ) const { return _instructions; }


// OPERATOR <<

std::ostream &		operator<<( std::ostream & o, Parser const & src ) {
	std::vector<Token> const &	v = src.getInstructions();
	size_t	len = v.size();

	for (size_t i = 0; i < len; i++)
	{
		o << v[i].getStr() << std::endl;
	}

	return o;
}