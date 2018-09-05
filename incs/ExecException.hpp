#ifndef EXECEXCEPTION_HPP
# define EXECEXCEPTION_HPP

# include <iostream>

# define EMPTY_STACK		"' on an empty stack."
# define ASSERT_EMPTY_STACK	"assert' on an empty stack."
# define ASSERT_ERROR		"' is not equal to `'"
# define WRONG_TYPE 		"' is not an 8-bit integer."

class ExecException : public std::exception {

public:

	ExecException( std::string line, std::string error );
	ExecException( ExecException const & src );
	virtual ~ExecException( void ) throw();
	ExecException & operator=( ExecException const & rhs );
	
	virtual const char *	what() const throw();

private:
	std::string			_error;

	ExecException( void );	

};

#endif