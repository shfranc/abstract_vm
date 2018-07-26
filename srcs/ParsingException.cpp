#include "Parser.hpp"

Parser::ParsingException::ParsingException( std::string line, std::string error ) : _line(line), _error(error) { return; }

Parser::ParsingException::ParsingException( Parser::ParsingException const & src ) {

	*this = src;
	return;
}

Parser::ParsingException::~ParsingException( void ) throw() { return; }

Parser::ParsingException &	Parser::ParsingException::operator=( Parser::ParsingException const & rhs ) {

	if ( this != &rhs ) {
		_line = rhs._line;
		_error = rhs._error;
	}
    return *this;
}


const char *	Parser::ParsingException::what() const throw() {
	
	std::string message = "Line " + _line + ": Parsing error: `" + _error;

	return (message.c_str());
}