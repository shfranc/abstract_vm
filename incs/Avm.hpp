#ifndef AVM_HPP
# define AVM_HPP

class Avm {

public:

	Avm( void );
	Avm( std::string filename );
	~Avm( void );

	void		

private:
	Reader			*_reader;
	Parser			*_parser;

	Avm( Avm const & src );
	Avm & operator=( Avm const & rhs );
};

#endif