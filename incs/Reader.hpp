#ifndef READER_HPP
# define READER_HPP

# include <iostream>
# include <vector>

class Reader {

public:

	Reader( void );
	// Reader( std::string file );
	~Reader( void );

	void			read( void );
	int				getContent( void ) const;
	// std::string		getContent( void ) const;

private:
	std::vector<std::string>	_content;

	Reader( Reader const & src );
	Reader & operator=( Reader const & rhs );
};

#endif