#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{

	engine::engine(std::istream& input, std::ostream& output) noexcept :
		m_IsRunning(false),
		m_Input(input),
		m_Output(output),
		m_Commands(),
		m_StartStopMutex()
	{
		addCommand<command_help>();
		addCommand<command_quit>();
		addCommand<command_ver>();
		addCommand<command_debugCpu>();
		addCommand<command_debugCompiler>();
		addCommand<command_debugIntrinsics>();
	}

	std::string engine::version() const noexcept
	{
		PYGMALION_ASSERT(false);
		return "(todo: add version)";
	}

	std::string engine::author() const noexcept
	{
		PYGMALION_ASSERT(false);
		return "(todo: add author)";
	}

	void engine::mainloop() noexcept
	{
		while (m_IsRunning)
		{
			std::string input;
			std::getline(m_Input, input);
			input = parser::trim_copy(input);
			bool processed{ false };
			while (!processed)
			{
				for (auto& cmd : m_Commands)
				{
					processed |= cmd->process(input);
					if (processed)
						break;
				}
				std::string token;
				std::string remainder;
				parser::parseToken(input, token, remainder);
				if (token == "")
					break;
				input = remainder;
			}
			if (!processed)
			{
				if (input.size() == 0)
				{
					m_Output << std::endl;
					m_Output << "Error (invalid command): " << input << std::endl;
					m_Output << std::endl;
				}
			}
			m_Output.flush();
		}
	}

	bool engine::isRunning() const noexcept
	{
		return m_IsRunning;
	}

	void engine::run() noexcept
	{
		std::lock_guard<std::recursive_mutex> lock(m_StartStopMutex);
		PYGMALION_ASSERT(!m_IsRunning);
		m_IsRunning = true;
		mainloop();
	}

	void engine::stop() noexcept
	{
		std::lock_guard<std::recursive_mutex> lock(m_StartStopMutex);
		PYGMALION_ASSERT(m_IsRunning);
		m_IsRunning = false;
	}

	std::istream& engine::inputStream() noexcept
	{
		return m_Input;
	}

	std::ostream& engine::outputStream() noexcept
	{
		return m_Output;
	}

	void engine::addCommand(std::shared_ptr<command> pCommand) noexcept
	{
		pCommand->m_pEngine = this;
		m_Commands.emplace_back(std::move(pCommand));
	}

	void engine::getXBoardFeatures(std::deque<std::string>& features) const noexcept
	{
		for (auto& cmd : m_Commands)
		{
			cmd->getXBoardFeatures(features);
		}
	}

	void engine::getXBoardVariants(std::deque<std::string>& variants) const noexcept
	{

	}

}