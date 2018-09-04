#include "ExecException.hpp"

ExecException::ExecException( std::string line, std::string error ) : _error("\033[1;31mExec error:\033[0m Line " + line + ": `" + error) { return; }

ExecException::~ExecException( void ) throw() { return; }

const char *	ExecException::what() const throw() {
	
	return ( _error.c_str() );
}