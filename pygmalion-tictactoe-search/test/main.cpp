#include <pygmalion-tictactoe-search.h>

using namespace pygmalion;
using namespace pygmalion::search;
using namespace pygmalion::tictactoe;

int main(int argc, char* argv[])
{
	engine<pygmalion::tictactoe::node> eng(std::cin, std::cout);
	eng.run();
	return 0;
}