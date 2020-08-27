namespace pygmalion
{
	template<typename ENGINE>
	class command
	{
	public:
		using engineType = ENGINE;
	protected:
		virtual bool onProcess(engineType& eng, const std::string& cmd) const noexcept
		{
			return false;
		}
	public:
		bool process(engineType& eng, const std::string& cmd) const noexcept
		{
			return onProcess(eng, cmd);
		}
	};
}