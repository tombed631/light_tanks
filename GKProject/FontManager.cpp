
#include "FontManager.h"


///Returns an instance of font manager class.
FontManager & FontManager::getInstance(){
	static FontManager fontManager;
	return fontManager;
}

///Releases all resources used by the font manager.
FontManager::~FontManager() {
	for (FontMap::iterator iter = fonts.begin(); iter != fonts.end(); iter++) {
		if (iter->second != nullptr)
			delete iter->second;
	}
		
	fonts.clear();
}

///Returns the specified font.
///If the font is not loaded, function tries to load
///it from currently set font directory.
///filename		Name of the font file.
///Throws LoadFontError if failed to load font from file.
sf::Font * FontManager::getFont(const std::string filename){
	
	//Check if font has been already loaded
	FontMap::iterator result = fonts.find(filename);
	if (result != fonts.end()) {
		return result->second; //return font
	}

	//else load font from file
	sf::Font * font = new sf::Font();
	std::string filePath = this->directory + "/" + filename;
	if (!font->loadFromFile(filePath)) {
		delete font;
		std::string msg = "Cannot load font from file!\n *Path: " + filePath;
		throw LoadFontError(msg.c_str());
	}
	//add font to the container
	fonts[filename] = font;

	return font;
}