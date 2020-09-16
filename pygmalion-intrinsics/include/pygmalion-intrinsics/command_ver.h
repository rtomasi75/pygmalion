namespace pygmalion::intrinsics
{
	class command_ver : public command
	{
	protected:
		virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override;
	};

}