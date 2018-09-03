#include "Parser.hpp"

Parser::ParsingException::ParsingException( std::string line, std::string error ) : _error("Line " + line + ": Parsing error: `" + error) { return; }

Parser::ParsingException::ParsingException( Parser::ParsingException const & src ) {

	*this = src;
	return;
}

Parser::ParsingException::~ParsingException( void ) throw() { return; }

Parser::ParsingException &	Parser::ParsingException::operator=( Parser::ParsingException const & rhs ) {

	if ( this != &rhs ) {
		_error = rhs._error;
	}
    return *this;
}


const char *	Parser::ParsingException::what() const throw() {
	
	// std::cout << "verif exeption " << _line;
	// std::cout << "verif exeption " << _error;
	// std::string message = "Line " + _line + ": Parsing error: `" + _error;
	// std::cout << "verif exeption " << message.c_str() << std::endl;
	// return ( message.c_str() );
	return ( _error.c_str() );
}