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
	private:
		std::deque<std::shared_ptr<command>> m_Commands;
	protected:
		template<typename T>
		void addCommand()
		{
			auto delCmd = [](command* pCmd)
			{
				delete static_cast<T*>(pCmd);
			};
			std::shared_ptr<command> pCommand(static_cast<command*>(new T()), delCmd);
			pCommand->m_pEngine = this;
			m_Commands.emplace_back(std::move(pCommand));
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