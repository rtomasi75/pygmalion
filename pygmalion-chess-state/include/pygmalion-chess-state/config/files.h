namespace pygmalion::config::chess
{
	class fileA_Info :
		public fileInfo
	{
	public:
		constexpr fileA_Info() noexcept :
			fileInfo("a", "file_A")
		{

		}
	};

	class fileB_Info :
		public fileInfo
	{
	public:
		constexpr fileB_Info() noexcept :
			fileInfo("b", "file_B")
		{

		}
	};

	class fileC_Info :
		public fileInfo
	{
	public:
		constexpr fileC_Info() noexcept :
			fileInfo("c", "file_C")
		{

		}
	};

	class fileD_Info :
		public fileInfo
	{
	public:
		constexpr fileD_Info() noexcept :
			fileInfo("d", "file_D")
		{

		}
	};

	class fileE_Info :
		public fileInfo
	{
	public:
		constexpr fileE_Info() noexcept :
			fileInfo("e", "file_E")
		{

		}
	};

	class fileF_Info :
		public fileInfo
	{
	public:
		constexpr fileF_Info() noexcept :
			fileInfo("f", "file_F")
		{

		}
	};

	class fileG_Info :
		public fileInfo
	{
	public:
		constexpr fileG_Info() noexcept :
			fileInfo("g", "file_G")
		{

		}
	};

	class fileH_Info :
		public fileInfo
	{
	public:
		constexpr fileH_Info() noexcept :
			fileInfo("h", "file_H")
		{

		}
	};

	class standardfilesInfo :
		public filesInfo<fileA_Info, fileB_Info, fileC_Info, fileD_Info, fileE_Info, fileF_Info, fileG_Info, fileH_Info>
	{
	public:
		constexpr standardfilesInfo() noexcept :
			filesInfo<fileA_Info, fileB_Info, fileC_Info, fileD_Info, fileE_Info, fileF_Info, fileG_Info, fileH_Info>(
				fileA_Info(),
				fileB_Info(),
				fileC_Info(),
				fileD_Info(),
				fileE_Info(),
				fileF_Info(),
				fileG_Info(),
				fileH_Info())
		{

		}
	};
}