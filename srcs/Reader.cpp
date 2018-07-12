#include "Reader.hpp"

Reader::Reader( void ) {

    return;
}

Reader::~Reader( void ) {

    return;
}

void		Reader::read( void )
{
	std::string		tmp;

	while (1)
	{
		std::getline( std::cin, tmp );
		_content.push_back( tmp );
		if ( tmp.find(";;") != std::string::npos )
			break ;
	}
}

// ACCESSOR
int			Reader::getContent( void ) const { return _content.size(); };