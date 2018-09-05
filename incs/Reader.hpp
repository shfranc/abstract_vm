#ifndef READER_HPP
# define READER_HPP

# include <iostream>
# include <fstream>
# include <sys/types.h>
# include <sys/stat.h>

# define READ_ERROR "Read error: file doesn't exist or permission is denied."
# define NOT_FILE_ERROR "Read error: is not a REGULAR file."

class Reader {

public:

	Reader( void );
	Reader( std::string filename );
	~Reader( void );

	void			read( void );
	std::string		getContent( void ) const;

private:
	std::string		_filename;
	std::string		_content;

	void			read_stdin( void );
	void			read_file( void );

	Reader( Reader const & src );
	Reader & operator=( Reader const & rhs );
};

std::ostream &		operator<<( std::ostream & o, Reader & src );

#endif