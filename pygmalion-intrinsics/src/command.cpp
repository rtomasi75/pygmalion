#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command::onProcess(const std::string& cmd) noexcept
	{
		return false;
	}

	bool command::process(const std::string& cmd) noexcept
	{
		return onProcess(cmd);
	}

	engine& command::intrinsicsEngine() noexcept
	{
		return *m_pEngine;
	}

	const engine& command::intrinsicsEngine() const noexcept
	{
		return *m_pEngine;
	}

	command::command() noexcept :
		m_pEngine(nullptr)
	{

	}

	std::ostream& command::output() noexcept
	{
		return m_pEngine->outputStream();
	}

	std::istream& command::input() noexcept
	{
		return m_pEngine->inputStream();
	}

	std::string command::help() noexcept
	{
		return "<TODO: implement help>";
	}

	void command::getXBoardFeatures(std::deque<std::string>& optionList) const noexcept
	{

	}

}