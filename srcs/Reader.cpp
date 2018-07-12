#include "Reader.hpp"

Reader::Reader( void ) {

    return;
}

Reader::~Reader( void ) {

    return;
}

void		Reader::read_stdin( void ) {

	std::string		buff;

	while ( std::getline( std::cin, buff ) )
	{
		_content.push_back( buff );
		std::cout << _content[_content.size() - 1] << std::endl;
		if ( buff.find(";;") != std::string::npos )
			break ;
	}
}

void		Reader::read_file( std::string filename ) {

	std::ifstream	file( filename );
	std::string 	buff;

	if (!file.is_open())
		throw std::invalid_argument("Error: file is not open or didn't exist"); // directory
	while ( std::getline( file, buff ) )
	{
		_content.push_back( buff );
		std::cout << _content[_content.size() - 1] << std::endl;
	}
	file.close();
}

// ACCESSOR
std::vector<std::string> *	Reader::getContent( void ) const { return _content; };

// OPERATOR <<

std::ostream &				operator<<( std::ostream & o, Reader & src ) {

	std::vector<std::string> *	v;
	unsigned int len;

	v = src.getContent();
	len = v->size();
	for (unsigned int i = 0; i < len; i++)
	{
		o << v[0] << std::endl;
	}

	return o;
}