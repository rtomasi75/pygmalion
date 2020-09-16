namespace pygmalion::intrinsics
{
	class command_debugCpu : public command
	{
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
	};

}