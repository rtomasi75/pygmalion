namespace pygmalion::intrinsics
{
	class command_debugIntrinsics : public command
	{
	protected:
		virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override;
	};

}