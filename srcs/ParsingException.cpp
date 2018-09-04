#include "Parser.hpp"

Parser::ParsingException::ParsingException( std::string line, std::string error ) : _error("\033[1;31mParsing error:\033[0m Line " + line + ": `" + error) { return; }

Parser::ParsingException::~ParsingException( void ) throw() { return; }

const char *	Parser::ParsingException::what() const throw() {
	
	return ( _error.c_str() );
}