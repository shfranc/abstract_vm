#include "Reader.hpp"
#include "Parser.hpp"

void	ft_usage( void )
{
	std::cerr << "./avm [input_file]" << std::endl;
}

int main( int argc, char const *argv[] )
{
	Reader	*input;
	Parser	parser;

	if (argc == 1)
		input = new Reader();
	else if (argc == 2)
		input = new Reader(argv[1]);
	else {
		ft_usage();
		return 1;
	}

	try {
		input->read();
		std::cout << *input;
		parser.parse( input->getContent() );
		std::cout << parser;
	}
	catch ( std::invalid_argument e) {
		std::cout << e.what() << std::endl;		
	}
	
	delete input;
	return 0;
}
