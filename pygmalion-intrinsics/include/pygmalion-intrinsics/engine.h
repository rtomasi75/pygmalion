namespace pygmalion::intrinsics
{
	class engine
	{
	private:
		std::ostream& m_Output;
		std::istream& m_Input;
		std::atomic_bool m_IsRunning;
		std::mutex m_StartStopMutex;
		void inputLoop() noexcept;
		std::thread* m_pInputThread;
		void outputLoop() noexcept;
		std::thread* m_pOutputThread;
		friend class command_help;
		std::mutex m_OutputMutex;
		std::deque<std::string> m_ScheduledOutput;
		std::condition_variable m_OutputReady;
	private:
		std::deque<std::shared_ptr<command>> m_Commands;
		std::mutex m_StreamsMutex;
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
		virtual void handleInvalidCommand(const std::string& command) noexcept;
	public:
		virtual void writeDebugString(const std::string& text) noexcept;
		void writeOutput(const std::string& text) noexcept;
		void getXBoardFeatures(std::deque<std::string>& features) const noexcept;
		virtual void getXBoardVariants(std::deque<std::string>& variants) const noexcept;
		virtual std::string version() const noexcept;
		virtual std::string author() const noexcept;
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept;
		virtual ~engine() noexcept;
		bool isRunning() const noexcept;
		void run() noexcept;
		void stop() noexcept;
	};
}