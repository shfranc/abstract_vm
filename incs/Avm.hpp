#ifndef AVM_HPP
# define AVM_HPP

#include "Reader.hpp"
#include "Parser.hpp"

class Avm {

public:

	Avm( void );
	Avm( std::string filename );
	~Avm( void );

	void		readUserInput();	
	void		parseInstructions();	

private:
	Reader			*_reader;
	Parser			*_parser;

	Avm( Avm const & src );
	Avm & operator=( Avm const & rhs );
};

#endif