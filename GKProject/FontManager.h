#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include<SFML\Graphics.hpp>
#include<map>
#include<string>
#include<iostream>


////////////////////////////////////////////////////////
/// An Exception class that is thrown when
/// an error occured during font loading.
///
///	version 1.0
////////////////////////////////////////////////////////
class LoadFontError : public std::runtime_error
{
public:
	LoadFontError(const char * msg) : runtime_error(msg) {}
};


////////////////////////////////////////////////////////
/// Simple font manager class, that loads and stores
/// fonts.
///
///	version 1.0
////////////////////////////////////////////////////////
class FontManager {

public:

	///Returns an instance of font manager class.
	static FontManager & getInstance();

	///Returns the specified font.
	///If the font is not loaded, function tries to load
	///it from currently set font directory.
	///filename		Name of the font file.
	///Throws LoadFontError if failed to load font from file.
	sf::Font * getFont(const std::string filename);

	///Returns path to the currently set fonts directory.
	std::string getDirectory() const {
		return directory;
	}

	///Sets path to the directory containing fonts.
	void setDirectory(const std::string dir) {
		this->directory = dir;
	}

	///Releases all resources used by the font manager.
	virtual ~FontManager();

protected:
	
	///Default constructor.
	///dir		Directory with fonts to load (optional).
	FontManager(std::string dir = "Fonts") : directory(dir){}

private:

	typedef std::map<std::string, sf::Font*> FontMap;

	///Contains loaded fonts
	FontMap fonts;
	
	///Contains path to the fonts directory
	std::string directory;
	
	FontManager(const FontManager &) = delete;
	FontManager & operator=(const FontManager &) = delete;

	
};

#endif //_FONT_MANAGER_H_