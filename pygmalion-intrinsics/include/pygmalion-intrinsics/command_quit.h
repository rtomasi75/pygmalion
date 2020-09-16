namespace pygmalion::intrinsics
{
	class command_quit : public command
	{
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
	};

}