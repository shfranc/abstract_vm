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
		input.read();
		std::cout << input.getContent() << std::endl;
	}
	else if (argc == 2)
		std::cout << "mode file: " << argv[1] << std::endl;
	else
		ft_usage();
	return 0;
}
