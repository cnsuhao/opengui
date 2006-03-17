#ifndef BE0F3698_B136_43b6_993F_F93035AB500C
#define BE0F3698_B136_43b6_993F_F93035AB500C

namespace OpenGUI{
	//! Provides complete loading of xml files containing data for all different subsystems.
	class XMLParser{
	public:
		static void LoadFromFile(const std::string& xmlFilename);
	private:
		//static void LoadFromFile(const std::string& xmlFilename);
	};
};

#endif

