#ifndef READER_HPP
# define READER_HPP

# include <iostream>
# include <fstream>
# include <vector>

class Reader {

public:

	Reader( void );
	~Reader( void );

	void							read_stdin( void );
	void							read_file( std::string filename );
	std::vector<std::string> &		getContent( void ) const;

private:
	std::vector<std::string>	_content;

	Reader( Reader const & src );
	Reader & operator=( Reader const & rhs );
};

std::ostream &		operator<<( std::ostream & o, Reader & src );

#endif