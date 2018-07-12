#include <Reader.hpp>

void	ft_usage( void )
{
	std::cerr << "./avm [input_file]" << std::endl;
}

int main( int argc, char const *argv[] )
{
	Reader	input;

	if (argc == 1)
	{	
		std::cout << "mode std::cin" << std::endl;
		input.read_stdin();
		std::cout << input << std::endl;
	}
	else if (argc == 2)
	{
		std::cout << "mode file: " << argv[1] << std::endl;
		try {
			input.read_file(argv[1]);
			std::cout << input << std::endl;
		}
		catch ( std::invalid_argument e)
		{
			std::cout << e.what() << std::endl;		
		}
	}
	else
		ft_usage();
	return 0;
}
