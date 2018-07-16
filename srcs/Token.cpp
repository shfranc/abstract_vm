#include "Token.hpp"

Token::Token( void ) : _str(""), _type(NONE) {

	std::cout << "Token: default contruct " << _str << std::endl;
	return;
}

Token::Token( std::string str ) : _str(str), _type( tokenType() ) {

	std::cout << "Token: param contruct " << _str << std::endl;
	return;
}

Token::Token( Token const & src ) {

	std::cout << "Token: copy contruct " << src._str << std::endl;
	*this = src;
	return;
}

Token::~Token( void ) {

	std::cout << "Token: destruct " << _str << std::endl;
	return;
}

Token &	Token::operator=( Token const & rhs ) {
	
	if ( this != &rhs ) {
		_str = rhs._str;
		_type = rhs._type;
	}
	
    return *this;
}

int		Token::tokenType( void ) {

	if ( _str == "push" )
		return (PUSH);
	if ( _str == "pop" )
		return (POP);
	if ( _str == "dump" )
		return (DUMP);
	if ( _str == "assert" )
		return (ASSERT);							
	if ( _str == "add" )
		return (ADD);
	if ( _str == "sub" )
		return (SUB);
	if ( _str == "mul" )
		return (MUL);
	if ( _str == "div" )
		return (DIV);
	if ( _str == "mod" )
		return (MOD);
	if ( _str == "print" )
		return (PRINT);
	if ( _str == "exit" )
		return (EXIT);
	if ( _str == "<newline>" )
		return (SEP);
	if ( std::strncmp(_str.c_str(), "int", 3) == 0 || std::strncmp(_str.c_str(), "float", 5) == 0 || std::strncmp(_str.c_str(), "double", 6) == 0 ) // regex ?
		return (VALUE);
	return (NONE);
}

// ACCESSOR
std::string		Token::getStr( void ) const { return _str; }
int				Token::getType( void ) const { return _type; }
