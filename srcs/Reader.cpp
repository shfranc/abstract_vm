#include "Reader.hpp"

Reader::Reader( void ) : _filename(""), _content("") {

	return;
}

Reader::Reader( std::string filename ) : _filename(filename), _content("") {

	return;
}

Reader::~Reader( void ) {

	return;
}

void		Reader::read( void ) {

	if ( _filename != "" )
		read_file();
	else
		read_stdin();
}

void		Reader::read_stdin( void ) {

	std::string		buff;

	std::cout << "> ";
	while ( std::getline( std::cin, buff ) )
	{
		_content += buff + '\n';
		if ( buff.find(";;") != std::string::npos )
			break ;
		std::cout << "> ";
	}
}

void		Reader::read_file( void ) {

	std::ifstream	file( _filename );
	std::string 	buff;
	struct stat s;

	if ( !file.is_open() )
		throw std::invalid_argument( READ_ERROR );
	if( stat( _filename.c_str(), &s ) == 0 ) {
		if ( !(s.st_mode & S_IFREG) )
			throw std::invalid_argument( NOT_FILE_ERROR );
	} else {
		throw std::invalid_argument( READ_ERROR );
	}
	while ( std::getline( file, buff ) )
	{
		_content += buff + '\n';
	}
	file.close();
}

// ACCESSOR
std::string			Reader::getContent( void ) const { return _content; };

// OPERATOR <<

std::ostream &		operator<<( std::ostream & o, Reader & src ) {

	o << src.getContent();
	return o;
}