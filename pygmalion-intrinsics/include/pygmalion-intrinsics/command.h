namespace pygmalion::intrinsics
{
	class engine;

	class command
	{
		friend class engine;
	private:
		engine* m_pEngine;
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept;
		engine& intrinsicsEngine() noexcept;
		const engine& intrinsicsEngine() const noexcept;
	public:
		std::ostream& output() noexcept;
		std::istream& input() noexcept;
		command() noexcept;
		bool process(const std::string& cmd) noexcept;
		virtual std::string help() noexcept;
		virtual void getXBoardFeatures(std::deque<std::string>& optionList) const noexcept;
	};
}