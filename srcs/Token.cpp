#include "Token.hpp"

Token::Token( void ) : {
	
	return;
}

Token::Token( std::string str ) : _str(str) {

	tokenType();
	return;
}

Token::~Token( void ) {

	return;
}

void		tokenType( void ) {

	switch (_str) {
		case std:strcmp(_str, "add"):
			_type = ADD;
			break;
		default:
			_type = NONE;
			break
	}
	return;
}

// ACCESSOR
std::string		getStr( void ) const { return _str; }
int				getType( void ) const { return _type; }
