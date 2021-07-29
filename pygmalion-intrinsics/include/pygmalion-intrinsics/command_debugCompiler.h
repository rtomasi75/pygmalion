namespace pygmalion::intrinsics
{
	class command_debugCompiler : public command
	{
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
		virtual std::string help() noexcept override;
	};

}