#include <iostream>
#include <pygmalion-core.h>

int main(int argc, char* argv[])
{
	std::cout << "sizeof(score)=" << sizeof(pygmalion::score<16, 7, 4>) << std::endl;
	pygmalion::score<16, 7, 4> sc{ pygmalion::score<16, 7, 4>::atom() };
	std::cout << "score::maximum()=" << static_cast<std::string>(pygmalion::score<16, 7, 4>::maximum()) << std::endl;
	std::cout << "score::minimum()=" << static_cast<std::string>(pygmalion::score<16, 7, 4>::minimum()) << std::endl;
	std::cout << "score::win()=" << static_cast<std::string>(pygmalion::score<16, 7, 4>::win()) << std::endl;
	std::cout << "score::loss()=" << static_cast<std::string>(pygmalion::score<16, 7, 4>::loss()) << std::endl;
	std::cout << "score::winning()=" << static_cast<std::string>(pygmalion::score<16, 7, 4>::winning()) << std::endl;
	std::cout << "score::losing()=" << static_cast<std::string>(pygmalion::score<16, 7, 4>::losing()) << std::endl;
	std::cout << "score::atom()=" << static_cast<std::string>(pygmalion::score<16, 7, 4>::atom()) << std::endl;
	return 0;
}