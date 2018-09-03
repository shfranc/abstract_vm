#include "Parser.hpp"

Parser::ParsingException::ParsingException( std::string line, std::string error ) : _error("Line " + line + ": Parsing error: `" + error) { return; }

Parser::ParsingException::~ParsingException( void ) throw() { return; }

const char *	Parser::ParsingException::what() const throw() {
	
	return ( _error.c_str() );
}