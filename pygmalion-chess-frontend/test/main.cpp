#include <pygmalion-chess-frontend.h>

using namespace pygmalion;
using namespace pygmalion::frontend;
using namespace pygmalion::chess;

int main(int argc, char* argv[])
{
	pygmalion::chess::frontend::engine<pygmalion::chess::front> eng(std::cin, std::cout);
	eng.run();
	return 0;
}