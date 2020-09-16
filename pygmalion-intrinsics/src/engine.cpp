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
		addCommand<command_quit>();
		addCommand<command_ver>();
		addCommand<command_debugCpu>();
		addCommand<command_debugCompiler>();
		addCommand<command_debugIntrinsics>();
	}
	
	std::string engine::version() const noexcept
	{
		return "no game (intrinsics only)";
	}

	void engine::mainloop() noexcept
	{
		while (m_IsRunning)
		{
			std::string input;
			std::getline(m_Input, input);
			bool processed{ false };
			for (auto& cmd : m_Commands)
			{
				processed |= cmd->process(input);
				if (processed)
					break;
			}
			if (!processed)
			{
				m_Output << std::endl;
				m_Output << "invalid command." << std::endl;
				m_Output << std::endl;
			}
		}
	}

	bool engine::isRunning() const noexcept
	{
		return m_IsRunning;
	}

	void engine::run() noexcept
	{
		std::lock_guard<std::recursive_mutex> lock(m_StartStopMutex);
		assert(!m_IsRunning);
		m_IsRunning = true;
		mainloop();
	}

	void engine::stop() noexcept
	{
		std::lock_guard<std::recursive_mutex> lock(m_StartStopMutex);
		assert(m_IsRunning);
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

}