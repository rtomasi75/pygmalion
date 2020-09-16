namespace pygmalion
{
	namespace intrinsics
	{
		class engine;
	}

	class command
	{
	protected:
		virtual bool onProcess(pygmalion::intrinsics::engine& eng, const std::string& cmd) const noexcept;
	public:
		bool process(pygmalion::intrinsics::engine& eng, const std::string& cmd) const noexcept;
	};
}