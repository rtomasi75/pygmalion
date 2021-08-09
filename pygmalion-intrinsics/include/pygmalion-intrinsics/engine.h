namespace pygmalion::intrinsics
{
	class engine
	{
	private:
		std::ostream& m_Output;
		std::istream& m_Input;
		std::atomic_bool m_IsRunning;
		std::recursive_mutex m_StartStopMutex;
		void mainloop() noexcept;
		friend class command_help;
	private:
		std::deque<std::shared_ptr<command>> m_Commands;
	protected:
		void addCommand(std::shared_ptr<command> pCommand) noexcept
		{
			pCommand->m_pEngine = this;
			m_Commands.emplace_back(std::move(pCommand));
		}
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
	public:
		virtual std::string version() const noexcept;
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept;
		virtual ~engine() noexcept = default;
		std::istream& inputStream() noexcept;
		std::ostream& outputStream() noexcept;
		bool isRunning() const noexcept;
		void run() noexcept;
		void stop() noexcept;
	};
}