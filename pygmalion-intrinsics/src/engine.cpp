#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{

	engine::engine(std::istream& input, std::ostream& output) noexcept :
		m_IsRunning(false),
		m_Input(input),
		m_Output(output),
		m_Commands(),
		m_StartStopMutex(),
		m_pInputThread{ nullptr },
		m_pOutputThread{ nullptr }
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

	void engine::inputLoop() noexcept
	{
		while (m_IsRunning)
		{
			std::string input;
			if (m_Input.peek() != std::istream::traits_type::eof())
			{
				std::getline(m_Input, input);
				input = parser::trim_copy(input);
				bool processed{ false };
				while (!processed)
				{
					for (auto& cmd : m_Commands)
					{
						processed |= cmd->process(input);
						if (processed)
						{
							writeOutput(cmd->output().str());
							cmd->output() = std::stringstream();
							break;
						}
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
					handleInvalidCommand(input);
				}
			}
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	void engine::outputLoop() noexcept
	{
		std::unique_lock<std::mutex> lock(m_OutputMutex);
		while (m_IsRunning)
		{
			m_OutputReady.wait_for(lock, std::chrono::milliseconds(10));
			if (m_ScheduledOutput.size() > 0)
			{
				for (const auto& text : m_ScheduledOutput)
				{
					m_Output << text;
				}
				m_Output.flush();
				m_ScheduledOutput.clear();
			}
		}
	}

	void engine::handleInvalidCommand(const std::string& command) noexcept
	{

	}

	bool engine::isRunning() const noexcept
	{
		return m_IsRunning;
	}

	void engine::run() noexcept
	{
		std::unique_lock<std::mutex> lock(m_StartStopMutex);
		PYGMALION_ASSERT(!m_IsRunning);
		m_IsRunning = true;
		m_pInputThread = new std::thread([this]() { this->inputLoop(); });
		m_pOutputThread = new std::thread([this]() { this->outputLoop(); });
		m_pInputThread->join();
		m_pInputThread = nullptr;
		m_pOutputThread->join();
		m_pOutputThread = nullptr;
	}

	engine::~engine() noexcept
	{
		std::unique_lock<std::mutex> lock(m_StartStopMutex);
		if (m_IsRunning)
		{
			m_IsRunning = false;
			m_pInputThread->join();
			m_pInputThread = nullptr;
			m_pOutputThread->join();
			m_pOutputThread = nullptr;
		}
	}

	void engine::stop() noexcept
	{
		PYGMALION_ASSERT(m_IsRunning);
		m_IsRunning = false;
	}

	void engine::writeOutput(const std::string& text) noexcept
	{
		{
			std::unique_lock<std::mutex> lock(m_OutputMutex);
			m_ScheduledOutput.push_back(text);
		}
		m_OutputReady.notify_all();
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

	void engine::writeDebugString(const std::string& text) noexcept
	{
		writeOutput(text);
	}

}