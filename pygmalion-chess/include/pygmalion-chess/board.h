namespace pygmalion::chess
{

	class board : public pygmalion::board<8, 8, 6, 2, 12, 64, 254, pygmalion::chess::board>
	{
	public:
	private:
		constexpr static uint8_t DrawingDistance{ 100 };
		constexpr static std::array<std::array<std::array<hashValue, 64>, 6>, 2> m_PieceHash
		{
			hashValue(0x56436C9FE1A1AA8D),
			hashValue(0xEFAC4B70633B8F81),
			hashValue(0xBB215798D45DF7AF),
			hashValue(0x45F20042F24F1768),
			hashValue(0x930F80F4E8EB7462),
			hashValue(0xFF6712FFCFD75EA1),
			hashValue(0xAE623FD67468AA70),
			hashValue(0xDD2C5BC84BC8D8FC),
			hashValue(0x7EED120D54CF2DD9),
			hashValue(0x22FE545401165F1C),
			hashValue(0xC91800E98FB99929),
			hashValue(0x808BD68E6AC10365),
			hashValue(0xDEC468145B7605F6),
			hashValue(0x1BEDE3A3AEF53302),
			hashValue(0x43539603D6C55602),
			hashValue(0xAA969B5C691CCB7A),
			hashValue(0xA87832D392EFEE56),
			hashValue(0x65942C7B3C7E11AE),
			hashValue(0xDED2D633CAD004F6),
			hashValue(0x21F08570F420E565),
			hashValue(0xB415938D7DA94E3C),
			hashValue(0x91B859E59ECB6350),
			hashValue(0x10CFF333E0ED804A),
			hashValue(0x28AED140BE0BB7DD),
			hashValue(0xC5CC1D89724FA456),
			hashValue(0x5648F680F11A2741),
			hashValue(0x2D255069F0B7DAB3),
			hashValue(0x9BC5A38EF729ABD4),
			hashValue(0xEF2F054308F6A2BC),
			hashValue(0xAF2042F5CC5C2858),
			hashValue(0x480412BAB7F5BE2A),
			hashValue(0xAEF3AF4A563DFE43),
			hashValue(0x19AFE59AE451497F),
			hashValue(0x52593803DFF1E840),
			hashValue(0xF4F076E65F2CE6F0),
			hashValue(0x11379625747D5AF3),
			hashValue(0xBCE5D2248682C115),
			hashValue(0x9DA4243DE836994F),
			hashValue(0x066F70B33FE09017),
			hashValue(0x4DC4DE189B671A1C),
			hashValue(0x51039AB7712457C3),
			hashValue(0xC07A3F80C31FB4B4),
			hashValue(0xB46EE9C5E64A6E7C),
			hashValue(0xB3819A42ABE61C87),
			hashValue(0x21A007933A522A20),
			hashValue(0x2DF16F761598AA4F),
			hashValue(0x763C4A1371B368FD),
			hashValue(0xF793C46702E086A0),
			hashValue(0xD7288E012AEB8D31),
			hashValue(0xDE336A2A4BC1C44B),
			hashValue(0x0BF692B38D079F23),
			hashValue(0x2C604A7A177326B3),
			hashValue(0x4850E73E03EB6064),
			hashValue(0xCFC447F1E53C8E1B),
			hashValue(0xB05CA3F564268D99),
			hashValue(0x9AE182C8BC9474E8),
			hashValue(0xA4FC4BD4FC5558CA),
			hashValue(0xE755178D58FC4E76),
			hashValue(0x69B97DB1A4C03DFE),
			hashValue(0xF9B5B7C4ACC67C96),
			hashValue(0xFC6A82D64B8655FB),
			hashValue(0x9C684CB6C4D24417),
			hashValue(0x8EC97D2917456ED0),
			hashValue(0x6703DF9D2924E97E),
			hashValue(0x7F9B6AF1EBF78BAF),
			hashValue(0x58627E1A149BBA21),
			hashValue(0x2CD16E2ABD791E33),
			hashValue(0xD363EFF5F0977996),
			hashValue(0x0CE2A38C344A6EED),
			hashValue(0x1A804AADB9CFA741),
			hashValue(0x907F30421D78C5DE),
			hashValue(0x501F65EDB3034D07),
			hashValue(0x37624AE5A48FA6E9),
			hashValue(0x957BAF61700CFF4E),
			hashValue(0x3A6C27934E31188A),
			hashValue(0xD49503536ABCA345),
			hashValue(0x088E049589C432E0),
			hashValue(0xF943AEE7FEBF21B8),
			hashValue(0x6C3B8E3E336139D3),
			hashValue(0x364F6FFA464EE52E),
			hashValue(0xD60F6DCEDC314222),
			hashValue(0x56963B0DCA418FC0),
			hashValue(0x16F50EDF91E513AF),
			hashValue(0xEF1955914B609F93),
			hashValue(0x565601C0364E3228),
			hashValue(0xECB53939887E8175),
			hashValue(0xBAC7A9A18531294B),
			hashValue(0xB344C470397BBA52),
			hashValue(0x65D34954DAF3CEBD),
			hashValue(0xB4B81B3FA97511E2),
			hashValue(0xB422061193D6F6A7),
			hashValue(0x071582401C38434D),
			hashValue(0x7A13F18BBEDC4FF5),
			hashValue(0xBC4097B116C524D2),
			hashValue(0x59B97885E2F2EA28),
			hashValue(0x99170A5DC3115544),
			hashValue(0x6F423357E7C6A9F9),
			hashValue(0x325928EE6E6F8794),
			hashValue(0xD0E4366228B03343),
			hashValue(0x565C31F7DE89EA27),
			hashValue(0x30F5611484119414),
			hashValue(0xD873DB391292ED4F),
			hashValue(0x7BD94E1D8E17DEBC),
			hashValue(0xC7D9F16864A76E94),
			hashValue(0x947AE053EE56E63C),
			hashValue(0xC8C93882F9475F5F),
			hashValue(0x3A9BF55BA91F81CA),
			hashValue(0xD9A11FBB3D9808E4),
			hashValue(0x0FD22063EDC29FCA),
			hashValue(0xB3F256D8ACA0B0B9),
			hashValue(0xB03031A8B4516E84),
			hashValue(0x35DD37D5871448AF),
			hashValue(0xE9F6082B05542E4E),
			hashValue(0xEBFAFA33D7254B59),
			hashValue(0x9255ABB50D532280),
			hashValue(0xB9AB4CE57F2D34F3),
			hashValue(0x693501D628297551),
			hashValue(0xC62C58F97DD949BF),
			hashValue(0xCD454F8F19C5126A),
			hashValue(0xBBE83F4ECC2BDECB),
			hashValue(0xDC842B7E2819E230),
			hashValue(0xBA89142E007503B8),
			hashValue(0xA3BC941D0A5061CB),
			hashValue(0xE9F6760E32CD8021),
			hashValue(0x09C7E552BC76492F),
			hashValue(0x852F54934DA55CC9),
			hashValue(0x8107FCCF064FCF56),
			hashValue(0x098954D51FFF6580),
			hashValue(0xDA3A361B1C5157B1),
			hashValue(0xDCDD7D20903D0C25),
			hashValue(0x36833336D068F707),
			hashValue(0xCE68341F79893389),
			hashValue(0xAB9090168DD05F34),
			hashValue(0x43954B3252DC25E5),
			hashValue(0xB438C2B67F98E5E9),
			hashValue(0x10DCD78E3851A492),
			hashValue(0xDBC27AB5447822BF),
			hashValue(0x9B3CDB65F82CA382),
			hashValue(0xB67B7896167B4C84),
			hashValue(0xBFCED1B0048EAC50),
			hashValue(0xA9119B60369FFEBD),
			hashValue(0x1FFF7AC80904BF45),
			hashValue(0xAC12FB171817EEE7),
			hashValue(0xAF08DA9177DDA93D),
			hashValue(0x1B0CAB936E65C744),
			hashValue(0xB559EB1D04E5E932),
			hashValue(0xC37B45B3F8D6F2BA),
			hashValue(0xC3A9DC228CAAC9E9),
			hashValue(0xF3B8B6675A6507FF),
			hashValue(0x9FC477DE4ED681DA),
			hashValue(0x67378D8ECCEF96CB),
			hashValue(0x6DD856D94D259236),
			hashValue(0xA319CE15B0B4DB31),
			hashValue(0x073973751F12DD5E),
			hashValue(0x8A8E849EB32781A5),
			hashValue(0xE1925C71285279F5),
			hashValue(0x74C04BF1790C0EFE),
			hashValue(0x4DDA48153C94938A),
			hashValue(0x9D266D6A1CC0542C),
			hashValue(0x7440FB816508C4FE),
			hashValue(0x13328503DF48229F),
			hashValue(0xD6BF7BAEE43CAC40),
			hashValue(0x4838D65F6EF6748F),
			hashValue(0x1E152328F3318DEA),
			hashValue(0x8F8419A348F296BF),
			hashValue(0x72C8834A5957B511),
			hashValue(0xD7A023A73260B45C),
			hashValue(0x94EBC8ABCFB56DAE),
			hashValue(0x9FC10D0F989993E0),
			hashValue(0xDE68A2355B93CAE6),
			hashValue(0xA44CFE79AE538BBE),
			hashValue(0x9D1D84FCCE371425),
			hashValue(0x51D2B1AB2DDFB636),
			hashValue(0x2FD7E4B9E72CD38C),
			hashValue(0x65CA5B96B7552210),
			hashValue(0xDD69A0D8AB3B546D),
			hashValue(0x604D51B25FBF70E2),
			hashValue(0x73AA8A564FB7AC9E),
			hashValue(0x1A8C1E992B941148),
			hashValue(0xAAC40A2703D9BEA0),
			hashValue(0x764DBEAE7FA4F3A6),
			hashValue(0x1E99B96E70A9BE8B),
			hashValue(0x2C5E9DEB57EF4743),
			hashValue(0x3A938FEE32D29981),
			hashValue(0x26E6DB8FFDF5ADFE),
			hashValue(0x469356C504EC9F9D),
			hashValue(0xC8763C5B08D1908C),
			hashValue(0x3F6C6AF859D80055),
			hashValue(0x7F7CC39420A3A545),
			hashValue(0x9BFB227EBDF4C5CE),
			hashValue(0x89039D79D6FC5C5C),
			hashValue(0x8FE88B57305E2AB6),
			hashValue(0x001F837CC7350524),
			hashValue(0x1877B51E57A764D5),
			hashValue(0xA2853B80F17F58EE),
			hashValue(0x993E1DE72D36D310),
			hashValue(0xB3598080CE64A656),
			hashValue(0x252F59CF0D9F04BB),
			hashValue(0xD23C8E176D113600),
			hashValue(0x1BDA0492E7E4586E),
			hashValue(0x21E0BD5026C619BF),
			hashValue(0x3B097ADAF088F94E),
			hashValue(0x8D14DEDB30BE846E),
			hashValue(0xF95CFFA23AF5F6F4),
			hashValue(0x3871700761B3F743),
			hashValue(0xCA672B91E9E4FA16),
			hashValue(0x64C8E531BFF53B55),
			hashValue(0x241260ED4AD1E87D),
			hashValue(0x106C09B972D2E822),
			hashValue(0x7FBA195410E5CA30),
			hashValue(0x7884D9BC6CB569D8),
			hashValue(0x0647DFEDCD894A29),
			hashValue(0x63573FF03E224774),
			hashValue(0x4FC8E9560F91B123),
			hashValue(0x1DB956E450275779),
			hashValue(0xB8D91274B9E9D4FB),
			hashValue(0xA2EBEE47E2FBFCE1),
			hashValue(0xD9F1F30CCD97FB09),
			hashValue(0xEFED53D75FD64E6B),
			hashValue(0x2E6D02C36017F67F),
			hashValue(0xA9AA4D20DB084E9B),
			hashValue(0xB64BE8D8B25396C1),
			hashValue(0x70CB6AF7C2D5BCF0),
			hashValue(0x98F076A4F7A2322E),
			hashValue(0xBF84470805E69B5F),
			hashValue(0x94C3251F06F90CF3),
			hashValue(0x3E003E616A6591E9),
			hashValue(0xB925A6CD0421AFF3),
			hashValue(0x61BDD1307C66E300),
			hashValue(0xBF8D5108E27E0D48),
			hashValue(0x240AB57A8B888B20),
			hashValue(0xFC87614BAF287E07),
			hashValue(0xEF02CDD06FFDB432),
			hashValue(0xA1082C0466DF6C0A),
			hashValue(0x8215E577001332C8),
			hashValue(0xD39BB9C3A48DB6CF),
			hashValue(0x2738259634305C14),
			hashValue(0x61CF4F94C97DF93D),
			hashValue(0x1B6BACA2AE4E125B),
			hashValue(0x758F450C88572E0B),
			hashValue(0x959F587D507A8359),
			hashValue(0xB063E962E045F54D),
			hashValue(0x60E8ED72C0DFF5D1),
			hashValue(0x7B64978555326F9F),
			hashValue(0xFD080D236DA814BA),
			hashValue(0x8C90FD9B083F4558),
			hashValue(0x106F72FE81E2C590),
			hashValue(0x7976033A39F7D952),
			hashValue(0xA4EC0132764CA04B),
			hashValue(0x733EA705FAE4FA77),
			hashValue(0xB4D8F77BC3E56167),
			hashValue(0x9E21F4F903B33FD9),
			hashValue(0x9D765E419FB69F6D),
			hashValue(0xD30C088BA61EA5EF),
			hashValue(0x5D94337FBFAF7F5B),
			hashValue(0x1A4E4822EB4D7A59),
			hashValue(0x9D39247E33776D41),
			hashValue(0x2AF7398005AAA5C7),
			hashValue(0x44DB015024623547),
			hashValue(0x9C15F73E62A76AE2),
			hashValue(0x75834465489C0C89),
			hashValue(0x3290AC3A203001BF),
			hashValue(0x0FBBAD1F61042279),
			hashValue(0xE83A908FF2FB60CA),
			hashValue(0x0D7E765D58755C10),
			hashValue(0x1A083822CEAFE02D),
			hashValue(0x9605D5F0E25EC3B0),
			hashValue(0xD021FF5CD13A2ED5),
			hashValue(0x40BDF15D4A672E32),
			hashValue(0x011355146FD56395),
			hashValue(0x5DB4832046F3D9E5),
			hashValue(0x239F8B2D7FF719CC),
			hashValue(0x05D1A1AE85B49AA1),
			hashValue(0x679F848F6E8FC971),
			hashValue(0x7449BBFF801FED0B),
			hashValue(0x7D11CDB1C3B7ADF0),
			hashValue(0x82C7709E781EB7CC),
			hashValue(0xF3218F1C9510786C),
			hashValue(0x331478F3AF51BBE6),
			hashValue(0x4BB38DE5E7219443),
			hashValue(0xAA649C6EBCFD50FC),
			hashValue(0x8DBD98A352AFD40B),
			hashValue(0x87D2074B81D79217),
			hashValue(0x19F3C751D3E92AE1),
			hashValue(0xB4AB30F062B19ABF),
			hashValue(0x7B0500AC42047AC4),
			hashValue(0xC9452CA81A09D85D),
			hashValue(0x24AA6C514DA27500),
			hashValue(0x4C9F34427501B447),
			hashValue(0x14A68FD73C910841),
			hashValue(0xA71B9B83461CBD93),
			hashValue(0x03488B95B0F1850F),
			hashValue(0x637B2B34FF93C040),
			hashValue(0x09D1BC9A3DD90A94),
			hashValue(0x3575668334A1DD3B),
			hashValue(0x735E2B97A4C45A23),
			hashValue(0x18727070F1BD400B),
			hashValue(0x1FCBACD259BF02E7),
			hashValue(0xD310A7C2CE9B6555),
			hashValue(0xBF983FE0FE5D8244),
			hashValue(0x9F74D14F7454A824),
			hashValue(0x51EBDC4AB9BA3035),
			hashValue(0x5C82C505DB9AB0FA),
			hashValue(0xFCF7FE8A3430B241),
			hashValue(0x3253A729B9BA3DDE),
			hashValue(0x8C74C368081B3075),
			hashValue(0xB9BC6C87167C33E7),
			hashValue(0x7EF48F2B83024E20),
			hashValue(0x11D505D4C351BD7F),
			hashValue(0x6568FCA92C76A243),
			hashValue(0x4DE0B0F40F32A7B8),
			hashValue(0x96D693460CC37E5D),
			hashValue(0x42E240CB63689F2F),
			hashValue(0x6D2BDCDAE2919661),
			hashValue(0x42880B0236E4D951),
			hashValue(0x5F0F4A5898171BB6),
			hashValue(0x39F890F579F92F88),
			hashValue(0x93C5B5F47356388B),
			hashValue(0x63DC359D8D231B78),
			hashValue(0xEC16CA8AEA98AD76),
			hashValue(0x230E343DFBA08D33),
			hashValue(0x43ED7F5A0FAE657D),
			hashValue(0x3A88A0FBBCB05C63),
			hashValue(0x21874B8B4D2DBC4F),
			hashValue(0x1BDEA12E35F6A8C9),
			hashValue(0x53C065C6C8E63528),
			hashValue(0xE34A1D250E7A8D6B),
			hashValue(0xD6B04D3B7651DD7E),
			hashValue(0x5E90277E7CB39E2D),
			hashValue(0x2C046F22062DC67D),
			hashValue(0xB10BB459132D0A26),
			hashValue(0x3FA9DDFB67E2F199),
			hashValue(0x0E09B88E1914F7AF),
			hashValue(0x10E8B35AF3EEAB37),
			hashValue(0x9EEDECA8E272B933),
			hashValue(0xD4C718BC4AE8AE5F),
			hashValue(0x81536D601170FC20),
			hashValue(0x91B534F885818A06),
			hashValue(0xEC8177F83F900978),
			hashValue(0x190E714FADA5156E),
			hashValue(0xB592BF39B0364963),
			hashValue(0x89C350C893AE7DC1),
			hashValue(0xAC042E70F8B383F2),
			hashValue(0xB49B52E587A1EE60),
			hashValue(0xFB152FE3FF26DA89),
			hashValue(0x3E666E6F69AE2C15),
			hashValue(0x3B544EBE544C19F9),
			hashValue(0xE805A1E290CF2456),
			hashValue(0x24B33C9D7ED25117),
			hashValue(0xE74733427B72F0C1),
			hashValue(0x0A804D18B7097475),
			hashValue(0x57E3306D881EDB4F),
			hashValue(0x4AE7D6A36EB5DBCB),
			hashValue(0x2D8D5432157064C8),
			hashValue(0xD1E649DE1E7F268B),
			hashValue(0x8A328A1CEDFE552C),
			hashValue(0x07A3AEC79624C7DA),
			hashValue(0x84547DDC3E203C94),
			hashValue(0x990A98FD5071D263),
			hashValue(0x1A4FF12616EEFC89),
			hashValue(0xF6F7FD1431714200),
			hashValue(0x30C05B1BA332F41C),
			hashValue(0x8D2636B81555A786),
			hashValue(0x46C9FEB55D120902),
			hashValue(0xCCEC0A73B49C9921),
			hashValue(0x4E9D2827355FC492),
			hashValue(0x19EBB029435DCB0F),
			hashValue(0x4659D2B743848A2C),
			hashValue(0x963EF2C96B33BE31),
			hashValue(0x74F85198B05A2E7D),
			hashValue(0x5A0F544DD2B1FB18),
			hashValue(0x03727073C2E134B1),
			hashValue(0xC7F6AA2DE59AEA61),
			hashValue(0x352787BAA0D7C22F),
			hashValue(0x9853EAB63B5E0B35),
			hashValue(0xABBDCDD7ED5C0860),
			hashValue(0xCF05DAF5AC8D77B0),
			hashValue(0x49CAD48CEBF4A71E),
			hashValue(0x7A4C10EC2158C4A6),
			hashValue(0xD9E92AA246BF719E),
			hashValue(0x13AE978D09FE5557),
			hashValue(0x730499AF921549FF),
			hashValue(0x4E4B705B92903BA4),
			hashValue(0xFF577222C14F0A3A),
			hashValue(0xC547F57E42A7444E),
			hashValue(0x78E37644E7CAD29E),
			hashValue(0xFE9A44E9362F05FA),
			hashValue(0x08BD35CC38336615),
			hashValue(0x9315E5EB3A129ACE),
			hashValue(0x94061B871E04DF75),
			hashValue(0xDF1D9F9D784BA010),
			hashValue(0x3BBA57B68871B59D),
			hashValue(0xD2B7ADEEDED1F73F),
			hashValue(0xF7A255D83BC373F8),
			hashValue(0xD7F4F2448C0CEB81),
			hashValue(0xD95BE88CD210FFA7),
			hashValue(0x336F52F8FF4728E7),
			hashValue(0xA74049DAC312AC71),
			hashValue(0xA2F61BB6E437FDB5),
			hashValue(0x4F2A5CB07F6A35B3),
			hashValue(0x87D380BDA5BF7859),
			hashValue(0x16B9F7E06C453A21),
			hashValue(0x7BA2484C8A0FD54E),
			hashValue(0xF3A678CAD9A2E38C),
			hashValue(0x39B0BF7DDE437BA2),
			hashValue(0xFCAF55C1BF8A4424),
			hashValue(0x18FCF680573FA594),
			hashValue(0x4C0563B89F495AC3),
			hashValue(0x40E087931A00930D),
			hashValue(0x8CFFA9412EB642C1),
			hashValue(0x68CA39053261169F),
			hashValue(0x7A1EE967D27579E2),
			hashValue(0x9D1D60E5076F5B6F),
			hashValue(0x3810E399B6F65BA2),
			hashValue(0x32095B6D4AB5F9B1),
			hashValue(0x35CAB62109DD038A),
			hashValue(0xA90B24499FCFAFB1),
			hashValue(0x77A225A07CC2C6BD),
			hashValue(0x513E5E634C70E331),
			hashValue(0x4361C0CA3F692F12),
			hashValue(0xD941ACA44B20A45B),
			hashValue(0x528F7C8602C5807B),
			hashValue(0x52AB92BEB9613989),
			hashValue(0x9D1DFA2EFC557F73),
			hashValue(0x722FF175F572C348),
			hashValue(0x1D1260A51107FE97),
			hashValue(0x7A249A57EC0C9BA2),
			hashValue(0x04208FE9E8F7F2D6),
			hashValue(0x5A110C6058B920A0),
			hashValue(0x0CD9A497658A5698),
			hashValue(0x56FD23C8F9715A4C),
			hashValue(0x284C847B9D887AAE),
			hashValue(0x04FEABFBBDB619CB),
			hashValue(0x742E1E651C60BA83),
			hashValue(0x9A9632E65904AD3C),
			hashValue(0x881B82A13B51B9E2),
			hashValue(0x506E6744CD974924),
			hashValue(0xB0183DB56FFC6A79),
			hashValue(0x0ED9B915C66ED37E),
			hashValue(0x5E11E86D5873D484),
			hashValue(0xF678647E3519AC6E),
			hashValue(0x1B85D488D0F20CC5),
			hashValue(0xDAB9FE6525D89021),
			hashValue(0x0D151D86ADB73615),
			hashValue(0xA865A54EDCC0F019),
			hashValue(0x93C42566AEF98FFB),
			hashValue(0x99E7AFEABE000731),
			hashValue(0x48CBFF086DDF285A),
			hashValue(0x23B70EDB1955C4BF),
			hashValue(0xC330DE426430F69D),
			hashValue(0x4715ED43E8A45C0A),
			hashValue(0xA8D7E4DAB780A08D),
			hashValue(0x0572B974F03CE0BB),
			hashValue(0xB57D2E985E1419C7),
			hashValue(0xE8D9ECBE2CF3D73F),
			hashValue(0x2FE4B17170E59750),
			hashValue(0x11317BA87905E790),
			hashValue(0x7FBF21EC8A1F45EC),
			hashValue(0x1725CABFCB045B00),
			hashValue(0x964E915CD5E2B207),
			hashValue(0x3E2B8BCBF016D66D),
			hashValue(0xBE7444E39328A0AC),
			hashValue(0xF85B2B4FBCDE44B7),
			hashValue(0x49353FEA39BA63B1),
			hashValue(0x1DD01AAFCD53486A),
			hashValue(0x1FCA8A92FD719F85),
			hashValue(0xFC7C95D827357AFA),
			hashValue(0x18A6A990C8B35EBD),
			hashValue(0xCCCB7005C6B9C28D),
			hashValue(0x3BDBB92C43B17F26),
			hashValue(0xAA70B5B4F89695A2),
			hashValue(0xE94C39A54A98307F),
			hashValue(0xB7A0B174CFF6F36E),
			hashValue(0xD4DBA84729AF48AD),
			hashValue(0x2E18BC1AD9704A68),
			hashValue(0x2DE0966DAF2F8B1C),
			hashValue(0xB9C11D5B1E43A07E),
			hashValue(0x64972D68DEE33360),
			hashValue(0x94628D38D0C20584),
			hashValue(0xDBC0D2B6AB90A559),
			hashValue(0xD2733C4335C6A72F),
			hashValue(0x7E75D99D94A70F4D),
			hashValue(0x6CED1983376FA72B),
			hashValue(0x97FCAACBF030BC24),
			hashValue(0x7B77497B32503B12),
			hashValue(0x8547EDDFB81CCB94),
			hashValue(0x79999CDFF70902CB),
			hashValue(0xCFFE1939438E9B24),
			hashValue(0x829626E3892D95D7),
			hashValue(0x92FAE24291F2B3F1),
			hashValue(0x63E22C147B9C3403),
			hashValue(0xC678B6D860284A1C),
			hashValue(0x5873888850659AE7),
			hashValue(0x0981DCD296A8736D),
			hashValue(0x9F65789A6509A440),
			hashValue(0x9FF38FED72E9052F),
			hashValue(0xE479EE5B9930578C),
			hashValue(0xE7F28ECD2D49EECD),
			hashValue(0x56C074A581EA17FE),
			hashValue(0x5544F7D774B14AEF),
			hashValue(0x7B3F0195FC6F290F),
			hashValue(0x12153635B2C0CF57),
			hashValue(0x7F5126DBBA5E0CA7),
			hashValue(0x7A76956C3EAFB413),
			hashValue(0x3D5774A11D31AB39),
			hashValue(0x8A1B083821F40CB4),
			hashValue(0x7B4A38E32537DF62),
			hashValue(0x950113646D1D6E03),
			hashValue(0x4DA8979A0041E8A9),
			hashValue(0x3BC36E078F7515D7),
			hashValue(0x5D0A12F27AD310D1),
			hashValue(0x7F9D1A2E1EBE1327),
			hashValue(0xA09E8C8C35AB96DE),
			hashValue(0xFA7E393983325753),
			hashValue(0xD6B6D0ECC617C699),
			hashValue(0xDFEA21EA9E7557E3),
			hashValue(0xB67C1FA481680AF8),
			hashValue(0xCA1E3785A9E724E5),
			hashValue(0x1CFC8BED0D681639),
			hashValue(0xD18D8549D140CAEA),
			hashValue(0x4ED0FE7E9DC91335),
			hashValue(0xE4DBF0634473F5D2),
			hashValue(0x1761F93A44D5AEFE),
			hashValue(0x53898E4C3910DA55),
			hashValue(0x734DE8181F6EC39A),
			hashValue(0x2680B122BAA28D97),
			hashValue(0x298AF231C85BAFAB),
			hashValue(0x7983EED3740847D5),
			hashValue(0x66C1A2A1A60CD889),
			hashValue(0x9E17E49642A3E4C1),
			hashValue(0xEDB454E7BADC0805),
			hashValue(0x50B704CAB602C329),
			hashValue(0x4CC317FB9CDDD023),
			hashValue(0x66B4835D9EAFEA22),
			hashValue(0x219B97E26FFC81BD),
			hashValue(0x261E4E4C0A333A9D),
			hashValue(0x1FE2CCA76517DB90),
			hashValue(0xD7504DFA8816EDBB),
			hashValue(0xB9571FA04DC089C8),
			hashValue(0x1DDC0325259B27DE),
			hashValue(0xCF3F4688801EB9AA),
			hashValue(0xF4F5D05C10CAB243),
			hashValue(0x38B6525C21A42B0E),
			hashValue(0x36F60E2BA4FA6800),
			hashValue(0xEB3593803173E0CE),
			hashValue(0x9C4CD6257C5A3603),
			hashValue(0xAF0C317D32ADAA8A),
			hashValue(0x258E5A80C7204C4B),
			hashValue(0x8B889D624D44885D),
			hashValue(0xF4D14597E660F855),
			hashValue(0xD4347F66EC8941C3),
			hashValue(0xE699ED85B0DFB40D),
			hashValue(0x2472F6207C2D0484),
			hashValue(0xC2A1E7B5B459AEB5),
			hashValue(0xAB4F6451CC1D45EC),
			hashValue(0x63767572AE3D6174),
			hashValue(0xA59E0BD101731A28),
			hashValue(0x116D0016CB948F09),
			hashValue(0x2CF9C8CA052F6E9F),
			hashValue(0x0B090A7560A968E3),
			hashValue(0xABEEDDB2DDE06FF1),
			hashValue(0x58EFC10B06A2068D),
			hashValue(0xC6E57A78FBD986E0),
			hashValue(0x2EAB8CA63CE802D7),
			hashValue(0x14A195640116F336),
			hashValue(0x7C0828DD624EC390),
			hashValue(0xD74BBE77E6116AC7),
			hashValue(0x804456AF10F5FB53),
			hashValue(0xEBE9EA2ADF4321C7),
			hashValue(0x03219A39EE587A30),
			hashValue(0x49787FEF17AF9924),
			hashValue(0xA1E9300CD8520548),
			hashValue(0x5B45E522E4B1B4EF),
			hashValue(0xB49C3B3995091A36),
			hashValue(0xD4490AD526F14431),
			hashValue(0x12A8F216AF9418C2),
			hashValue(0x6FFE73E81B637FB3),
			hashValue(0xDDF957BC36D8B9CA),
			hashValue(0x64D0E29EEA8838B3),
			hashValue(0x08DD9BDFD96B9F63),
			hashValue(0x087E79E5A57D1D13),
			hashValue(0xE328E230E3E2B3FB),
			hashValue(0x1C2559E30F0946BE),
			hashValue(0x720BF5F26F4D2EAA),
			hashValue(0xB0774D261CC609DB),
			hashValue(0x443F64EC5A371195),
			hashValue(0x4112CF68649A260E),
			hashValue(0xD813F2FAB7F5C5CA),
			hashValue(0x660D3257380841EE),
			hashValue(0x59AC2C7873F910A3),
			hashValue(0xE846963877671A17),
			hashValue(0x93B633ABFA3469F8),
			hashValue(0xC0C0F5A60EF4CDCF),
			hashValue(0xCAF21ECD4377B28C),
			hashValue(0x57277707199B8175),
			hashValue(0x506C11B9D90E8B1D),
			hashValue(0xD83CC2687A19255F),
			hashValue(0x4A29C6465A314CD1),
			hashValue(0xED2DF21216235097),
			hashValue(0xB5635C95FF7296E2),
			hashValue(0x22AF003AB672E811),
			hashValue(0x52E762596BF68235),
			hashValue(0x9AEBA33AC6ECC6B0),
			hashValue(0x944F6DE09134DFB6),
			hashValue(0x6C47BEC883A7DE39),
			hashValue(0x6AD047C430A12104),
			hashValue(0xA5B1CFDBA0AB4067),
			hashValue(0x7C45D833AFF07862),
			hashValue(0x5092EF950A16DA0B),
			hashValue(0x9338E69C052B8E7B),
			hashValue(0x455A4B4CFE30E3F5),
			hashValue(0x6B02E63195AD0CF8),
			hashValue(0x6B17B224BAD6BF27),
			hashValue(0xD1E0CCD25BB9C169),
			hashValue(0xDE0C89A556B9AE70),
			hashValue(0x50065E535A213CF6),
			hashValue(0x9C1169FA2777B874),
			hashValue(0x78EDEFD694AF1EED),
			hashValue(0x6DC93D9526A50E68),
			hashValue(0xEE97F453F06791ED),
			hashValue(0x32AB0EDB696703D3),
			hashValue(0x3A6853C7E70757A7),
			hashValue(0x31865CED6120F37D),
			hashValue(0x67FEF95D92607890),
			hashValue(0x1F2B1D1F15F6DC9C),
			hashValue(0xB69E38A8965C6B65),
			hashValue(0xAA9119FF184CCCF4),
			hashValue(0xF43C732873F24C13),
			hashValue(0xFB4A3D794A9A80D2),
			hashValue(0x3550C2321FD6109C),
			hashValue(0x371F77E76BB8417E),
			hashValue(0x6BFA9AAE5EC05779),
			hashValue(0xCD04F3FF001A4778),
			hashValue(0xE3273522064480CA),
			hashValue(0x9F91508BFFCFC14A),
			hashValue(0x049A7F41061A9E60),
			hashValue(0xFCB6BE43A9F2FE9B),
			hashValue(0x08DE8A1C7797DA9B),
			hashValue(0x8F9887E6078735A1),
			hashValue(0xB5B4071DBFC73A66),
			hashValue(0x5355F900C2A82DC7),
			hashValue(0x07FB9F855A997142),
			hashValue(0x5093417AA8A7ED5E),
			hashValue(0x7BCBC38DA25A7F3C),
			hashValue(0x19FC8A768CF4B6D4),
			hashValue(0x637A7780DECFC0D9),
			hashValue(0x8249A47AEE0E41F7),
			hashValue(0x79AD695501E7D1E8),
			hashValue(0x14ACBAF4777D5776),
			hashValue(0xF145B6BECCDEA195),
			hashValue(0xDABF2AC8201752FC),
			hashValue(0x24C3C94DF9C8D3F6),
			hashValue(0xBB6E2924F03912EA),
			hashValue(0x0CE26C0B95C980D9),
			hashValue(0xA49CD132BFBF7CC4),
			hashValue(0xE99D662AF4243939),
			hashValue(0x27E6AD7891165C3F),
			hashValue(0x8535F040B9744FF1),
			hashValue(0x54B3F4FA5F40D873),
			hashValue(0x72B12C32127FED2B),
			hashValue(0xEE954D3C7B411F47),
			hashValue(0x9A85AC909A24EAA1),
			hashValue(0x70AC4CD9F04F21F5),
			hashValue(0xF9B89D3E99A075C2),
			hashValue(0x87B3E2B2B5C907B1),
			hashValue(0xA366E5B8C54F48B8),
			hashValue(0xAE4A9346CC3F7CF2),
			hashValue(0x1920C04D47267BBD),
			hashValue(0x87BF02C6B49E2AE9),
			hashValue(0x092237AC237F3859),
			hashValue(0xFF07F64EF8ED14D0),
			hashValue(0x8DE8DCA9F03CC54E),
			hashValue(0x9C1633264DB49C89),
			hashValue(0xB3F22C3D0B0B38ED),
			hashValue(0x390E5FB44D01144B),
			hashValue(0x5BFEA5B4712768E9),
			hashValue(0x1E1032911FA78984),
			hashValue(0x9A74ACB964E78CB3),
			hashValue(0x4F80F7A035DAFB04),
			hashValue(0x6304D09A0B3738C4),
			hashValue(0x2171E64683023A08),
			hashValue(0x5B9B63EB9CEFF80C),
			hashValue(0x506AACF489889342),
			hashValue(0x1881AFC9A3A701D6),
			hashValue(0x6503080440750644),
			hashValue(0xDFD395339CDBF4A7),
			hashValue(0xEF927DBCF00C20F2),
			hashValue(0x7B32F7D1E03680EC),
			hashValue(0xB9FD7620E7316243),
			hashValue(0x05A7E8A57DB91B77),
			hashValue(0xB5889C6E15630A75),
			hashValue(0x4A750A09CE9573F7),
			hashValue(0xCF464CEC899A2F8A),
			hashValue(0xF538639CE705B824),
			hashValue(0x3C79A0FF5580EF7F),
			hashValue(0xEDE6C87F8477609D),
			hashValue(0x799E81F05BC93F31),
			hashValue(0x86536B8CF3428A8C),
			hashValue(0x97D7374C60087B73),
			hashValue(0xA246637CFF328532),
			hashValue(0x043FCAE60CC0EBA0),
			hashValue(0x920E449535DD359E),
			hashValue(0x70EB093B15B290CC),
			hashValue(0x73A1921916591CBD),
			hashValue(0x55B6344CF97AAFAE),
			hashValue(0xB862225B055B6960),
			hashValue(0xCAC09AFBDDD2CDB4),
			hashValue(0xDAF8E9829FE96B5F),
			hashValue(0xB5FDFC5D3132C498),
			hashValue(0x310CB380DB6F7503),
			hashValue(0xE87FBB46217A360E),
			hashValue(0x2102AE466EBB1148),
			hashValue(0xF8549E1A3AA5E00D),
			hashValue(0x07A69AFDCC42261A),
			hashValue(0xC4C118BFE78FEAAE),
			hashValue(0xF9F4892ED96BD438),
			hashValue(0x1AF3DBE25D8F45DA),
			hashValue(0xF5B4B0B0D2DEEEB4),
			hashValue(0x962ACEEFA82E1C84),
			hashValue(0x046E3ECAAF453CE9),
			hashValue(0xF05D129681949A4C),
			hashValue(0x964781CE734B3C84),
			hashValue(0x9C2ED44081CE5FBD),
			hashValue(0x522E23F3925E319E),
			hashValue(0x177E00F9FC32F791),
			hashValue(0x2BC60A63A6F3B3F2),
			hashValue(0x222BBFAE61725606),
			hashValue(0x486289DDCC3D6780),
			hashValue(0x7DC7785B8EFDFC80),
			hashValue(0x8AF38731C02BA980),
			hashValue(0x1FAB64EA29A2DDF7),
			hashValue(0xE4D9429322CD065A),
			hashValue(0x9DA058C67844F20C),
			hashValue(0x24C0E332B70019B0),
			hashValue(0x233003B5A6CFE6AD),
			hashValue(0xD586BD01C5C217F6),
			hashValue(0x5E5637885F29BC2B),
			hashValue(0x7EBA726D8C94094B),
			hashValue(0x0A56A5F0BFE39272),
			hashValue(0xD79476A84EE20D06),
			hashValue(0x9E4C1269BAA4BF37),
			hashValue(0x17EFEE45B0DEE640),
			hashValue(0x1D95B0A5FCF90BC6),
			hashValue(0x93CBE0B699C2585D),
			hashValue(0x65FA4F227A2B6D79),
			hashValue(0xD5F9E858292504D5),
			hashValue(0xC2B5A03F71471A6F),
			hashValue(0x59300222B4561E00),
			hashValue(0xCE2F8642CA0712DC),
			hashValue(0x7CA9723FBB2E8988),
			hashValue(0x2785338347F2BA08),
			hashValue(0xC61BB3A141E50E8C),
			hashValue(0x150F361DAB9DEC26),
			hashValue(0x9F6A419D382595F4),
			hashValue(0x64A53DC924FE7AC9),
			hashValue(0x142DE49FFF7A7C3D),
			hashValue(0x0C335248857FA9E7),
			hashValue(0x0A9C32D5EAE45305),
			hashValue(0xE6C42178C4BBB92E),
			hashValue(0x71F1CE2490D20B07),
			hashValue(0xF1BCC3D275AFE51A),
			hashValue(0xE728E8C83C334074),
			hashValue(0x96FBF83A12884624),
			hashValue(0x81A1549FD6573DA5),
			hashValue(0x5FA7867CAF35E149),
			hashValue(0x56986E2EF3ED091B),
			hashValue(0x917F1DD5F8886C61),
			hashValue(0xD20D8C88C8FFE65F)
		};
		static constexpr std::array<hashValue, 32> m_FlagHash
		{
			hashValue(0x0000000000000000),
			hashValue(0xF8D626AAAF278509),
			hashValue(0x1EF6E6DBB1961EC9),
			hashValue(0xE620C0711EB19BC0),
			hashValue(0xA57E6339DD2CF3A0),
			hashValue(0x5DA84593720B76A9),
			hashValue(0xBB8885E26CBAED69),
			hashValue(0x435EA348C39D6860),
			hashValue(0xF165B587DF898190),
			hashValue(0x09B3932D70AE0499),
			hashValue(0xEF93535C6E1F9F59),
			hashValue(0x174575F6C1381A50),
			hashValue(0x541BD6BE02A57230),
			hashValue(0xACCDF014AD82F739),
			hashValue(0x4AED3065B3336CF9),
			hashValue(0xB23B16CF1C14E9F0),
			hashValue(0x31D71DCE64B2C310),
			hashValue(0xC9013B64CB954619),
			hashValue(0x2F21FB15D524DDD9),
			hashValue(0xD7F7DDBF7A0358D0),
			hashValue(0x94A97EF7B99E30B0),
			hashValue(0x6C7F585D16B9B5B9),
			hashValue(0x8A5F982C08082E79),
			hashValue(0x7289BE86A72FAB70),
			hashValue(0xC0B2A849BB3B4280),
			hashValue(0x38648EE3141CC789),
			hashValue(0xDE444E920AAD5C49),
			hashValue(0x26926838A58AD940),
			hashValue(0x65CCCB706617B120),
			hashValue(0x9D1AEDDAC9303429),
			hashValue(0x7B3A2DABD781AFE9),
			hashValue(0x83EC0B0178A62AE0)
		};
		static constexpr std::array<hashValue, 256> m_EpHash
		{
			hashValue(0x0000000000000000),
			hashValue(0x70CC73D90BC26E24),
			hashValue(0xE21A6B35DF0C3AD7),
			hashValue(0x92D618ECD4CE54F3),
			hashValue(0x003A93D8B2806962),
			hashValue(0x70F6E001B9420746),
			hashValue(0xE220F8ED6D8C53B5),
			hashValue(0x92EC8B34664E3D91),
			hashValue(0x1C99DED33CB890A1),
			hashValue(0x6C55AD0A377AFE85),
			hashValue(0xFE83B5E6E3B4AA76),
			hashValue(0x8E4FC63FE876C452),
			hashValue(0x1CA34D0B8E38F9C3),
			hashValue(0x6C6F3ED285FA97E7),
			hashValue(0xFEB9263E5134C314),
			hashValue(0x8E7555E75AF6AD30),
			hashValue(0xCF3145DE0ADD4289),
			hashValue(0xBFFD3607011F2CAD),
			hashValue(0x2D2B2EEBD5D1785E),
			hashValue(0x5DE75D32DE13167A),
			hashValue(0xCF0BD606B85D2BEB),
			hashValue(0xBFC7A5DFB39F45CF),
			hashValue(0x2D11BD336751113C),
			hashValue(0x5DDDCEEA6C937F18),
			hashValue(0xD3A89B0D3665D228),
			hashValue(0xA364E8D43DA7BC0C),
			hashValue(0x31B2F038E969E8FF),
			hashValue(0x417E83E1E2AB86DB),
			hashValue(0xD39208D584E5BB4A),
			hashValue(0xA35E7B0C8F27D56E),
			hashValue(0x318863E05BE9819D),
			hashValue(0x41441039502BEFB9),
			hashValue(0xD0E4427A5514FB72),
			hashValue(0xA02831A35ED69556),
			hashValue(0x32FE294F8A18C1A5),
			hashValue(0x42325A9681DAAF81),
			hashValue(0xD0DED1A2E7949210),
			hashValue(0xA012A27BEC56FC34),
			hashValue(0x32C4BA973898A8C7),
			hashValue(0x4208C94E335AC6E3),
			hashValue(0xCC7D9CA969AC6BD3),
			hashValue(0xBCB1EF70626E05F7),
			hashValue(0x2E67F79CB6A05104),
			hashValue(0x5EAB8445BD623F20),
			hashValue(0xCC470F71DB2C02B1),
			hashValue(0xBC8B7CA8D0EE6C95),
			hashValue(0x2E5D644404203866),
			hashValue(0x5E91179D0FE25642),
			hashValue(0x1FD507A45FC9B9FB),
			hashValue(0x6F19747D540BD7DF),
			hashValue(0xFDCF6C9180C5832C),
			hashValue(0x8D031F488B07ED08),
			hashValue(0x1FEF947CED49D099),
			hashValue(0x6F23E7A5E68BBEBD),
			hashValue(0xFDF5FF493245EA4E),
			hashValue(0x8D398C903987846A),
			hashValue(0x034CD9776371295A),
			hashValue(0x7380AAAE68B3477E),
			hashValue(0xE156B242BC7D138D),
			hashValue(0x919AC19BB7BF7DA9),
			hashValue(0x03764AAFD1F14038),
			hashValue(0x73BA3976DA332E1C),
			hashValue(0xE16C219A0EFD7AEF),
			hashValue(0x91A05243053F14CB),
			hashValue(0x77C621CC9FB3A483),
			hashValue(0x070A52159471CAA7),
			hashValue(0x95DC4AF940BF9E54),
			hashValue(0xE51039204B7DF070),
			hashValue(0x77FCB2142D33CDE1),
			hashValue(0x0730C1CD26F1A3C5),
			hashValue(0x95E6D921F23FF736),
			hashValue(0xE52AAAF8F9FD9912),
			hashValue(0x6B5FFF1FA30B3422),
			hashValue(0x1B938CC6A8C95A06),
			hashValue(0x8945942A7C070EF5),
			hashValue(0xF989E7F377C560D1),
			hashValue(0x6B656CC7118B5D40),
			hashValue(0x1BA91F1E1A493364),
			hashValue(0x897F07F2CE876797),
			hashValue(0xF9B3742BC54509B3),
			hashValue(0xB8F76412956EE60A),
			hashValue(0xC83B17CB9EAC882E),
			hashValue(0x5AED0F274A62DCDD),
			hashValue(0x2A217CFE41A0B2F9),
			hashValue(0xB8CDF7CA27EE8F68),
			hashValue(0xC80184132C2CE14C),
			hashValue(0x5AD79CFFF8E2B5BF),
			hashValue(0x2A1BEF26F320DB9B),
			hashValue(0xA46EBAC1A9D676AB),
			hashValue(0xD4A2C918A214188F),
			hashValue(0x4674D1F476DA4C7C),
			hashValue(0x36B8A22D7D182258),
			hashValue(0xA45429191B561FC9),
			hashValue(0xD4985AC0109471ED),
			hashValue(0x464E422CC45A251E),
			hashValue(0x368231F5CF984B3A),
			hashValue(0xA72263B6CAA75FF1),
			hashValue(0xD7EE106FC16531D5),
			hashValue(0x4538088315AB6526),
			hashValue(0x35F47B5A1E690B02),
			hashValue(0xA718F06E78273693),
			hashValue(0xD7D483B773E558B7),
			hashValue(0x45029B5BA72B0C44),
			hashValue(0x35CEE882ACE96260),
			hashValue(0xBBBBBD65F61FCF50),
			hashValue(0xCB77CEBCFDDDA174),
			hashValue(0x59A1D6502913F587),
			hashValue(0x296DA58922D19BA3),
			hashValue(0xBB812EBD449FA632),
			hashValue(0xCB4D5D644F5DC816),
			hashValue(0x599B45889B939CE5),
			hashValue(0x295736519051F2C1),
			hashValue(0x68132668C07A1D78),
			hashValue(0x18DF55B1CBB8735C),
			hashValue(0x8A094D5D1F7627AF),
			hashValue(0xFAC53E8414B4498B),
			hashValue(0x6829B5B072FA741A),
			hashValue(0x18E5C66979381A3E),
			hashValue(0x8A33DE85ADF64ECD),
			hashValue(0xFAFFAD5CA63420E9),
			hashValue(0x748AF8BBFCC28DD9),
			hashValue(0x04468B62F700E3FD),
			hashValue(0x9690938E23CEB70E),
			hashValue(0xE65CE057280CD92A),
			hashValue(0x74B06B634E42E4BB),
			hashValue(0x047C18BA45808A9F),
			hashValue(0x96AA0056914EDE6C),
			hashValue(0xE666738F9A8CB048),
			hashValue(0x67A34DAC4356550B),
			hashValue(0x176F3E7548943B2F),
			hashValue(0x85B926999C5A6FDC),
			hashValue(0xF5755540979801F8),
			hashValue(0x6799DE74F1D63C69),
			hashValue(0x1755ADADFA14524D),
			hashValue(0x8583B5412EDA06BE),
			hashValue(0xF54FC6982518689A),
			hashValue(0x7B3A937F7FEEC5AA),
			hashValue(0x0BF6E0A6742CAB8E),
			hashValue(0x9920F84AA0E2FF7D),
			hashValue(0xE9EC8B93AB209159),
			hashValue(0x7B0000A7CD6EACC8),
			hashValue(0x0BCC737EC6ACC2EC),
			hashValue(0x991A6B921262961F),
			hashValue(0xE9D6184B19A0F83B),
			hashValue(0xA8920872498B1782),
			hashValue(0xD85E7BAB424979A6),
			hashValue(0x4A88634796872D55),
			hashValue(0x3A44109E9D454371),
			hashValue(0xA8A89BAAFB0B7EE0),
			hashValue(0xD864E873F0C910C4),
			hashValue(0x4AB2F09F24074437),
			hashValue(0x3A7E83462FC52A13),
			hashValue(0xB40BD6A175338723),
			hashValue(0xC4C7A5787EF1E907),
			hashValue(0x5611BD94AA3FBDF4),
			hashValue(0x26DDCE4DA1FDD3D0),
			hashValue(0xB4314579C7B3EE41),
			hashValue(0xC4FD36A0CC718065),
			hashValue(0x562B2E4C18BFD496),
			hashValue(0x26E75D95137DBAB2),
			hashValue(0xB7470FD61642AE79),
			hashValue(0xC78B7C0F1D80C05D),
			hashValue(0x555D64E3C94E94AE),
			hashValue(0x2591173AC28CFA8A),
			hashValue(0xB77D9C0EA4C2C71B),
			hashValue(0xC7B1EFD7AF00A93F),
			hashValue(0x5567F73B7BCEFDCC),
			hashValue(0x25AB84E2700C93E8),
			hashValue(0xABDED1052AFA3ED8),
			hashValue(0xDB12A2DC213850FC),
			hashValue(0x49C4BA30F5F6040F),
			hashValue(0x3908C9E9FE346A2B),
			hashValue(0xABE442DD987A57BA),
			hashValue(0xDB28310493B8399E),
			hashValue(0x49FE29E847766D6D),
			hashValue(0x39325A314CB40349),
			hashValue(0x78764A081C9FECF0),
			hashValue(0x08BA39D1175D82D4),
			hashValue(0x9A6C213DC393D627),
			hashValue(0xEAA052E4C851B803),
			hashValue(0x784CD9D0AE1F8592),
			hashValue(0x0880AA09A5DDEBB6),
			hashValue(0x9A56B2E57113BF45),
			hashValue(0xEA9AC13C7AD1D161),
			hashValue(0x64EF94DB20277C51),
			hashValue(0x1423E7022BE51275),
			hashValue(0x86F5FFEEFF2B4686),
			hashValue(0xF6398C37F4E928A2),
			hashValue(0x64D5070392A71533),
			hashValue(0x141974DA99657B17),
			hashValue(0x86CF6C364DAB2FE4),
			hashValue(0xF6031FEF466941C0),
			hashValue(0x10656C60DCE5F188),
			hashValue(0x60A91FB9D7279FAC),
			hashValue(0xF27F075503E9CB5F),
			hashValue(0x82B3748C082BA57B),
			hashValue(0x105FFFB86E6598EA),
			hashValue(0x60938C6165A7F6CE),
			hashValue(0xF245948DB169A23D),
			hashValue(0x8289E754BAABCC19),
			hashValue(0x0CFCB2B3E05D6129),
			hashValue(0x7C30C16AEB9F0F0D),
			hashValue(0xEEE6D9863F515BFE),
			hashValue(0x9E2AAA5F349335DA),
			hashValue(0x0CC6216B52DD084B),
			hashValue(0x7C0A52B2591F666F),
			hashValue(0xEEDC4A5E8DD1329C),
			hashValue(0x9E10398786135CB8),
			hashValue(0xDF5429BED638B301),
			hashValue(0xAF985A67DDFADD25),
			hashValue(0x3D4E428B093489D6),
			hashValue(0x4D82315202F6E7F2),
			hashValue(0xDF6EBA6664B8DA63),
			hashValue(0xAFA2C9BF6F7AB447),
			hashValue(0x3D74D153BBB4E0B4),
			hashValue(0x4DB8A28AB0768E90),
			hashValue(0xC3CDF76DEA8023A0),
			hashValue(0xB30184B4E1424D84),
			hashValue(0x21D79C58358C1977),
			hashValue(0x511BEF813E4E7753),
			hashValue(0xC3F764B558004AC2),
			hashValue(0xB33B176C53C224E6),
			hashValue(0x21ED0F80870C7015),
			hashValue(0x51217C598CCE1E31),
			hashValue(0xC0812E1A89F10AFA),
			hashValue(0xB04D5DC3823364DE),
			hashValue(0x229B452F56FD302D),
			hashValue(0x525736F65D3F5E09),
			hashValue(0xC0BBBDC23B716398),
			hashValue(0xB077CE1B30B30DBC),
			hashValue(0x22A1D6F7E47D594F),
			hashValue(0x526DA52EEFBF376B),
			hashValue(0xDC18F0C9B5499A5B),
			hashValue(0xACD48310BE8BF47F),
			hashValue(0x3E029BFC6A45A08C),
			hashValue(0x4ECEE8256187CEA8),
			hashValue(0xDC22631107C9F339),
			hashValue(0xACEE10C80C0B9D1D),
			hashValue(0x3E380824D8C5C9EE),
			hashValue(0x4EF47BFDD307A7CA),
			hashValue(0x0FB06BC4832C4873),
			hashValue(0x7F7C181D88EE2657),
			hashValue(0xEDAA00F15C2072A4),
			hashValue(0x9D66732857E21C80),
			hashValue(0x0F8AF81C31AC2111),
			hashValue(0x7F468BC53A6E4F35),
			hashValue(0xED909329EEA01BC6),
			hashValue(0x9D5CE0F0E56275E2),
			hashValue(0x1329B517BF94D8D2),
			hashValue(0x63E5C6CEB456B6F6),
			hashValue(0xF133DE226098E205),
			hashValue(0x81FFADFB6B5A8C21),
			hashValue(0x131326CF0D14B1B0),
			hashValue(0x63DF551606D6DF94),
			hashValue(0xF1094DFAD2188B67),
			hashValue(0x81C53E23D9DAE543)
		};
		hashValue m_PawnstructureHash;
		score m_Material;
		square m_KingSquare[player::countValues];
		uint8_t m_DistanceToDraw;
	public:
		constexpr auto getDistanceToDraw() const noexcept
		{
			return m_DistanceToDraw;
		}
		constexpr void setDistanceToDraw(const uint8_t distance) noexcept
		{
			m_DistanceToDraw = distance;
		}
		constexpr auto getPawnstructureHash() const noexcept
		{
			return m_PawnstructureHash;
		}
		constexpr void setPawnstructureHash(const hashValue hash) noexcept
		{
			m_PawnstructureHash = hash;
		}
		constexpr score getMaterial() const noexcept
		{
			return m_Material;
		}
		constexpr void setMaterial(const score material) noexcept
		{
			m_Material = material;
		}
		constexpr static hashValue pieceHash_Implementation(const player p, const piece pc, const square sq)
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
			return m_PieceHash[p][pc][sq];
		}
		constexpr static hashValue flagsHash_Implementation(const flags f)
		{
			assert(f < (size_t(1) << countFlags));
			constexpr int shift{ countIntrinsicFlags + 4 };
			constexpr flags mask{ (size_t(1) << shift) - 1 };
			return m_FlagHash[f & mask] ^ m_EpHash[f >> shift];
		}
		constexpr static piece knight{ 0x0 };
		constexpr static piece bishop{ 0x1 };
		constexpr static piece rook{ 0x2 };
		constexpr static piece queen{ 0x3 };
		constexpr static piece pawn{ 0x4 };
		constexpr static piece king{ 0x5 };
		constexpr board(const board&) noexcept = default;
		constexpr board(board&&) noexcept = default;
		~board() = default;
		board& operator=(const board&) = default;
		board& operator=(board&&) = default;
		constexpr static player whitePlayer{ 0 };
		constexpr static player blackPlayer{ 1 };
		constexpr static flags castlerightQueensideWhite{ flagBit(countIntrinsicFlags) };
		constexpr static flags castlerightQueensideBlack{ flagBit(countIntrinsicFlags + 1) };
		constexpr static flags castlerightKingsideWhite{ flagBit(countIntrinsicFlags + 2) };
		constexpr static flags castlerightKingsideBlack{ flagBit(countIntrinsicFlags + 3) };
		constexpr static flags castlerightMask{ castlerightQueensideWhite | castlerightQueensideBlack | castlerightKingsideWhite | castlerightKingsideBlack };
		constexpr static flags castlerightQueenside(const player p) noexcept
		{
			assert(p.isValid());
			return (size_t(1) << countIntrinsicFlags) << (p * 2);
		}
		constexpr static flags castlerightKingside(const player p) noexcept
		{
			assert(p.isValid());
			return (size_t(1) << (countIntrinsicFlags + 1)) << (p * 2);
		}
		constexpr static flags enPassantFlagsMask{ ((flags(1) << 9) - 1) << (countIntrinsicFlags + 4) };
		constexpr static flags enPassantFlags(const file f) noexcept
		{
			assert(f.isValid());
			return flagBit(countIntrinsicFlags + 4 + f);
		}
		constexpr static rank rank1{ 0 };
		constexpr static rank rank2{ 1 };
		constexpr static rank rank3{ 2 };
		constexpr static rank rank4{ 3 };
		constexpr static rank rank5{ 4 };
		constexpr static rank rank6{ 5 };
		constexpr static rank rank7{ 6 };
		constexpr static rank rank8{ 7 };
		constexpr static file fileA{ 0 };
		constexpr static file fileB{ 1 };
		constexpr static file fileC{ 2 };
		constexpr static file fileD{ 3 };
		constexpr static file fileE{ 4 };
		constexpr static file fileF{ 5 };
		constexpr static file fileG{ 6 };
		constexpr static file fileH{ 7 };
		constexpr static square squareA1{ fromRankFile(rank1,fileA) };
		constexpr static square squareA2{ fromRankFile(rank2,fileA) };
		constexpr static square squareA3{ fromRankFile(rank3,fileA) };
		constexpr static square squareA4{ fromRankFile(rank4,fileA) };
		constexpr static square squareA5{ fromRankFile(rank5,fileA) };
		constexpr static square squareA6{ fromRankFile(rank6,fileA) };
		constexpr static square squareA7{ fromRankFile(rank7,fileA) };
		constexpr static square squareA8{ fromRankFile(rank8,fileA) };
		constexpr static square squareB1{ fromRankFile(rank1,fileB) };
		constexpr static square squareB2{ fromRankFile(rank2,fileB) };
		constexpr static square squareB3{ fromRankFile(rank3,fileB) };
		constexpr static square squareB4{ fromRankFile(rank4,fileB) };
		constexpr static square squareB5{ fromRankFile(rank5,fileB) };
		constexpr static square squareB6{ fromRankFile(rank6,fileB) };
		constexpr static square squareB7{ fromRankFile(rank7,fileB) };
		constexpr static square squareB8{ fromRankFile(rank8,fileB) };
		constexpr static square squareC1{ fromRankFile(rank1,fileC) };
		constexpr static square squareC2{ fromRankFile(rank2,fileC) };
		constexpr static square squareC3{ fromRankFile(rank3,fileC) };
		constexpr static square squareC4{ fromRankFile(rank4,fileC) };
		constexpr static square squareC5{ fromRankFile(rank5,fileC) };
		constexpr static square squareC6{ fromRankFile(rank6,fileC) };
		constexpr static square squareC7{ fromRankFile(rank7,fileC) };
		constexpr static square squareC8{ fromRankFile(rank8,fileC) };
		constexpr static square squareD1{ fromRankFile(rank1,fileD) };
		constexpr static square squareD2{ fromRankFile(rank2,fileD) };
		constexpr static square squareD3{ fromRankFile(rank3,fileD) };
		constexpr static square squareD4{ fromRankFile(rank4,fileD) };
		constexpr static square squareD5{ fromRankFile(rank5,fileD) };
		constexpr static square squareD6{ fromRankFile(rank6,fileD) };
		constexpr static square squareD7{ fromRankFile(rank7,fileD) };
		constexpr static square squareD8{ fromRankFile(rank8,fileD) };
		constexpr static square squareE1{ fromRankFile(rank1,fileE) };
		constexpr static square squareE2{ fromRankFile(rank2,fileE) };
		constexpr static square squareE3{ fromRankFile(rank3,fileE) };
		constexpr static square squareE4{ fromRankFile(rank4,fileE) };
		constexpr static square squareE5{ fromRankFile(rank5,fileE) };
		constexpr static square squareE6{ fromRankFile(rank6,fileE) };
		constexpr static square squareE7{ fromRankFile(rank7,fileE) };
		constexpr static square squareE8{ fromRankFile(rank8,fileE) };
		constexpr static square squareF1{ fromRankFile(rank1,fileF) };
		constexpr static square squareF2{ fromRankFile(rank2,fileF) };
		constexpr static square squareF3{ fromRankFile(rank3,fileF) };
		constexpr static square squareF4{ fromRankFile(rank4,fileF) };
		constexpr static square squareF5{ fromRankFile(rank5,fileF) };
		constexpr static square squareF6{ fromRankFile(rank6,fileF) };
		constexpr static square squareF7{ fromRankFile(rank7,fileF) };
		constexpr static square squareF8{ fromRankFile(rank8,fileF) };
		constexpr static square squareG1{ fromRankFile(rank1,fileG) };
		constexpr static square squareG2{ fromRankFile(rank2,fileG) };
		constexpr static square squareG3{ fromRankFile(rank3,fileG) };
		constexpr static square squareG4{ fromRankFile(rank4,fileG) };
		constexpr static square squareG5{ fromRankFile(rank5,fileG) };
		constexpr static square squareG6{ fromRankFile(rank6,fileG) };
		constexpr static square squareG7{ fromRankFile(rank7,fileG) };
		constexpr static square squareG8{ fromRankFile(rank8,fileG) };
		constexpr static square squareH1{ fromRankFile(rank1,fileH) };
		constexpr static square squareH2{ fromRankFile(rank2,fileH) };
		constexpr static square squareH3{ fromRankFile(rank3,fileH) };
		constexpr static square squareH4{ fromRankFile(rank4,fileH) };
		constexpr static square squareH5{ fromRankFile(rank5,fileH) };
		constexpr static square squareH6{ fromRankFile(rank6,fileH) };
		constexpr static square squareH7{ fromRankFile(rank7,fileH) };
		constexpr static square squareH8{ fromRankFile(rank8,fileH) };
		board() noexcept;
		constexpr static bitsType notFileH{ 0x7f7f7f7f7f7f7f7f };
		constexpr static bitsType notFileA{ 0xfefefefefefefefe };
		constexpr static bitsType notRank1{ 0xffffffffffffff00 };
		constexpr static bitsType notRank8{ 0x00ffffffffffffff };
		constexpr static bitsType right(const bitsType bits) noexcept
		{
			return (bits & notFileH) << 1;
		}
		constexpr static bitsType rightFast(const bitsType bits) noexcept
		{
			return bits << 1;
		}
		constexpr static bitsType left(const bitsType bits) noexcept
		{
			return (bits & notFileA) >> 1;
		}
		constexpr static bitsType left_lazy(const bitsType bits) noexcept
		{
			return bits >> 1;
		}
		constexpr static bitsType down(const bitsType bits) noexcept
		{
			return bits >> 8;
		}
		constexpr static bitsType up(const bitsType bits) noexcept
		{
			return bits << 8;
		}
		constexpr static bitsType downRight(const bitsType bits) noexcept
		{
			return (bits & notFileH) >> 7;
		}
		constexpr static bitsType downRight_lazy(const bitsType bits) noexcept
		{
			return bits >> 7;
		}
		constexpr static bitsType upRight(const bitsType bits) noexcept
		{
			return (bits & notFileH) << 9;
		}
		constexpr static bitsType upRight_lazy(const bitsType bits) noexcept
		{
			return bits << 9;
		}
		constexpr static bitsType downLeft(const bitsType bits) noexcept
		{
			return (bits & notFileA) >> 9;
		}
		constexpr static bitsType downLeft_lazy(const bitsType bits) noexcept
		{
			return bits >> 9;
		}
		constexpr static bitsType upLeft(const bitsType bits) noexcept
		{
			return (bits & notFileA) << 7;
		}
		constexpr static bitsType upLeft_lazy(const bitsType bits) noexcept
		{
			return bits << 7;
		}
		constexpr static bitsType upUpLeft(const bitsType bits) noexcept
		{
			return up(upLeft(bits));
		}
		constexpr static bitsType upUpRight(const bitsType bits) noexcept
		{
			return up(upRight(bits));
		}
		constexpr static bitsType downDownLeft(const bitsType bits) noexcept
		{
			return down(downLeft(bits));
		}
		constexpr static bitsType downDownRight(const bitsType bits) noexcept
		{
			return down(downRight(bits));
		}
		constexpr static bitsType upLeftLeft(const bitsType bits) noexcept
		{
			return upLeft(left(bits));
		}
		constexpr static bitsType downLeftLeft(const bitsType bits) noexcept
		{
			return downLeft(left(bits));
		}
		constexpr static bitsType upRightRight(const bitsType bits) noexcept
		{
			return upRight(right(bits));
		}
		constexpr static bitsType downRightRight(const bitsType bits) noexcept
		{
			return downRight(right(bits));
		}
		constexpr square kingSquare(const player side) const noexcept
		{
			return m_KingSquare[side];
		}
		constexpr static bitsType queensideCastleInterestWhite{ bitsType::setMask(squareD1) | bitsType::setMask(squareC1) | bitsType::setMask(squareB1) };
		constexpr static bitsType queensideCastleInterestBlack{ bitsType::setMask(squareD8) | bitsType::setMask(squareC8) | bitsType::setMask(squareB8) };
		constexpr static bitsType kingsideCastleInterestWhite{ bitsType::setMask(squareF1) | bitsType::setMask(squareG1) };
		constexpr static bitsType kingsideCastleInterestBlack{ bitsType::setMask(squareF8) | bitsType::setMask(squareG8) };
		constexpr static bitsType queensideCastleWalkWhite{ bitsType::setMask(squareE1) | bitsType::setMask(squareD1) | bitsType::setMask(squareC1) };
		constexpr static bitsType queensideCastleWalkBlack{ bitsType::setMask(squareE8) | bitsType::setMask(squareD8) | bitsType::setMask(squareC8) };
		constexpr static bitsType kingsideCastleWalkWhite{ bitsType::setMask(squareE1) | bitsType::setMask(squareF1) | bitsType::setMask(squareG1) };
		constexpr static bitsType kingsideCastleWalkBlack{ bitsType::setMask(squareE8) | bitsType::setMask(squareF8) | bitsType::setMask(squareG8) };
		class move : public moveBase<true, true, requiredUnsignedBits(countSquares), 4, 2>
		{
		private:
			constexpr move(const squareType from, const squareType to, const channelType channel, const dataType data) noexcept :
				moveBase<true, true, requiredUnsignedBits(countSquares), 4, 2>(from, to, channel, data)
			{

			}
		public:
			constexpr move() noexcept :
				moveBase<true, true, requiredUnsignedBits(countSquares), 4, 2>()
			{

			}
			constexpr static move quiet(const square from, const square to) noexcept
			{
				return move(from, to, 0b00, 0b00);
			}
			constexpr static move doublePush(const square from, const square to) noexcept
			{
				return move(from, to, 0b00, 0b01);
			}
			constexpr static move capture(const square from, const square to) noexcept
			{
				return move(from, to, 0b01, 0b00);
			}
			constexpr static move captureEnPassant(const square from, const square to) noexcept
			{
				return move(from, to, 0b01, 0b01);
			}
			constexpr static move castleKingside(const  player p) noexcept
			{
				return (p == whitePlayer) ? move(squareE1, squareG1, 0b00, 0b11) : move(squareE8, squareG8, 0b00, 0b11);
			}
			constexpr static move castleQueenside(const  player p) noexcept
			{
				return (p == whitePlayer) ? move(squareE1, squareC1, 0b00, 0b10) : move(squareE8, 0b00, squareC8, 0b10);
			}
			constexpr static move promotion(const square from, const square to, const piece promoted) noexcept
			{
				assert(promoted.isValid());
				return move(from, to, 0b10, promoted);
			}
			constexpr static move promotionCapture(const square from, const square to, const piece promoted) noexcept
			{
				assert(promoted.isValid());
				return move(from, to, 0b11, promoted);
			}
			constexpr square from() const noexcept
			{
				return square1();
			}
			constexpr square to() const noexcept
			{
				return square2();
			}
			constexpr move(const move&) noexcept = default;
			constexpr move(move&&) noexcept = default;
			constexpr move& operator=(const move&) noexcept = default;
			constexpr move& operator=(move&&) noexcept = default;
			~move() noexcept = default;
			constexpr bool isEnPassant() const noexcept
			{
				return (channel() == 0b01) && (data() == 0b01);
			}
			constexpr bool isCastleQueenside() const noexcept
			{
				return (channel() == 0b00) && (data() == 0b10);
			}
			constexpr bool isCastleKingside() const noexcept
			{
				return (channel() == 0b00) && (data() == 0b11);
			}
			constexpr bool isPromotion() const noexcept
			{
				return channel() == 0b10;
			}
			constexpr bool isCapture() const noexcept
			{
				return (channel() == 0b11) || (channel() == 0b01);
			}
			constexpr bool isPromotionCapture() const noexcept
			{
				return channel() == 0b11;
			}
			constexpr bool isCastle() const noexcept
			{
				return isCastleQueenside() || isCastleKingside();
			}
			constexpr bool isDoublePush() const noexcept
			{
				return (channel() == 0b00) && (data() == 0b01);
			}
			constexpr board::piece get_PromotionPiece() const noexcept
			{
				assert(isPromotion() || isPromotionCapture());
				return data();
			}
		};
		using moveType = move;
		class movedata : public movedataBase
		{
		private:
			hashValue m_OldHash;
			hashValue m_OldPawnstructureHash;
			score m_OldMaterial;
			flags m_OldFlags;
			uint8_t m_OldDistanceToDraw;
			bool m_IsCapture;
			bool m_IsPromotion;
			bool m_IsDoublePush;
			bool m_IsCastling;
			square m_FromSquare;
			square m_ToSquare;
			player m_OtherPlayer;
			piece m_MovingPiece;
			piece m_TargetPiece;
			square m_CaptureSquare;
			piece m_CapturedPiece;
			square m_RookFrom;
			square m_RookTo;
			square m_WhiteKing;
			square m_BlackKing;
		public:
			constexpr auto oldHash() const noexcept
			{
				return m_OldHash;
			}
			constexpr auto oldPawnstructureHash() const noexcept
			{
				return m_OldPawnstructureHash;
			}
			constexpr auto oldMaterial() const noexcept
			{
				return m_OldMaterial;
			}
			constexpr auto oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr auto oldDistanceToDraw() const noexcept
			{
				return m_OldDistanceToDraw;
			}
			constexpr auto isCapture() const noexcept
			{
				return m_IsCapture;
			}
			constexpr auto isPromotion() const noexcept
			{
				return m_IsPromotion;
			}
			constexpr auto isDoublePush() const noexcept
			{
				return m_IsDoublePush;
			}
			constexpr auto isCastling() const noexcept
			{
				return m_IsCastling;
			}
			constexpr auto fromSquare() const noexcept
			{
				return m_FromSquare;
			}
			constexpr auto toSquare() const noexcept
			{
				return m_ToSquare;
			}
			constexpr auto otherPlayer() const noexcept
			{
				return m_OtherPlayer;
			}
			constexpr auto movingPiece() const noexcept
			{
				return m_MovingPiece;
			}
			constexpr auto targetPiece() const noexcept
			{
				return m_TargetPiece;
			}
			constexpr auto captureSquare() const noexcept
			{
				return m_CaptureSquare;
			}
			constexpr auto capturedPiece() const noexcept
			{
				return m_CapturedPiece;
			}
			constexpr auto rookFrom() const noexcept
			{
				return m_RookFrom;
			}
			constexpr auto rookTo() const noexcept
			{
				return m_RookTo;
			}
			constexpr auto whiteKing() const noexcept
			{
				return m_WhiteKing;
			}
			constexpr auto blackKing() const noexcept
			{
				return m_BlackKing;
			}
			movedata(const board& position, const player oldPlayer) noexcept;
			movedata(const board& position, const move& mv) noexcept;
			~movedata() noexcept = default;
		};
		static void makeMove_Implementation(board& position, const movedata& md) noexcept;
		static void unmakeMove_Implementation(board& position, const movedata& md) noexcept;
		class boardStack : public stack<movedata, move, boardStack>
		{
		private:
			mutable bitsType m_AttackedSquares[player::countValues];
			player m_OtherPlayer;
			mutable bool m_AttackedSquaresValid[player::countValues];
			mutable bool m_IsCheck;
			mutable bool m_IsCheckValid;
			void computeAttackSquares(const player p) const noexcept;
			void computeIsCheck() const noexcept;
		public:
			bool isMoveLegal_Implementation(const moveType& move) const noexcept;
			bool generateMoves_Implementation(movelistType& moves, int& currentPass) const noexcept;
			bool generateTacticalMoves_Implementation(movelistType& moves, int& currentPass) const noexcept;
			boardStack(const boardStack& parent, const move mv) noexcept;
			boardStack(instanceType& position, const player oldPlayer) noexcept;
			~boardStack() noexcept = default;
			constexpr player otherPlayer() const noexcept
			{
				return m_OtherPlayer;
			}
			bool isCheck() const noexcept
			{
				if (!m_IsCheckValid)
					computeIsCheck();
				return m_IsCheck;
			}
			bitsType attackedSquares(const player p) const noexcept
			{
				if (!m_AttackedSquaresValid[p])
					computeAttackSquares(p);
				return m_AttackedSquares[p];
			}
		};
		using stackType = boardStack;
	};
}