namespace pygmalion::intrinsics
{
	class gui : 
		public consumer<std::string>
	{
	private:
		std::deque<std::shared_ptr<command>> m_Commands;
	protected:
		void addCommand(std::shared_ptr<command> pCommand) noexcept;
		template<typename T>
		void addCommand() noexcept
		{
			auto delCmd = [](command* pCmd)
			{
				delete static_cast<T*>(pCmd);
			};
			std::shared_ptr<command> pCommand(static_cast<command*>(new T()), delCmd);
			this->addCommand(pCommand);
		}
		virtual void onConsume(const std::string& text) noexcept override
		{
			bool processed{ false };
			std::string input{ std::string(text) };
			while (!processed)
			{
				for (auto& cmd : m_Commands)
				{
					processed |= cmd->process(text);
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

		}
	public:
		gui(engine& engine_) noexcept
		{
			addCommand<command_help>();
			addCommand<command_quit>();
			addCommand<command_ver>();
			addCommand<command_debugCpu>();
			addCommand<command_debugCompiler>();
			addCommand<command_debugIntrinsics>();
		}
	};
}