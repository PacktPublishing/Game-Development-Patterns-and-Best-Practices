/******************************************************************************/
/*!
\file   M5IniFile.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/16

Class to read from or write to an ini file
*/
/******************************************************************************/
#ifndef M5INI_FILE_H
#define M5INI_FILE_H

#include "M5Debug.h"

#include <map>
#include <string>
#include <sstream>

//! Class to read from or write to an ini file
class M5IniFile
{
public:
	M5IniFile(void);
	void ReadFile(const std::string& fileName);
	//Function to get the data from a section
	template<typename T>
	void GetValue(const std::string& key, T& value) const;
	void SetToSection(const std::string& sectionName);
	void AddSection(const std::string& sectionName);
	template<typename T>
	void AddKeyValue(const std::string& key, const T& value);
	void WriteFile(const std::string& fileName) const;
private:
	///Template types 
	//! String pair used for reading key/values
	typedef std::pair<std::string, std::string>        StringPair;
	//! Map of keys to values
	typedef std::map<std::string, std::string>         KeyValMap;
	//! Iterator for key/value map
	typedef KeyValMap::iterator                        KeyValMapItor;
	//! Const interator for key/value map
	typedef KeyValMap::const_iterator                  KeyValMapCItor;
	//! Pair for sections
	typedef std::pair<std::string, KeyValMap>          StringMapPair;
	//! Map of names to sections
	typedef std::map<std::string, KeyValMap>           SectionMap;
	//! Iterator for name/section map
	typedef SectionMap::iterator                       SectionMapItor;
	//! Const Interator for name/section map
	typedef SectionMap::const_iterator                 SectionMapCItor;

	//Functions to parse file
	void SeperateKeyValueFromLine(StringPair& sPair, const std::string& line, size_t& begin, size_t& end) const;
	void GetSectionName(std::string& line, size_t& begin, size_t& end) const;
	void RemoveLeadingSpaces(const std::string& line, size_t& begin, size_t& end) const;
	void RemoveTrailingSpaces(const std::string& line, size_t& begin, size_t& end) const;
	void ParseSectionName(StringMapPair& currSection, std::string& line, size_t& begin, size_t& end);
	void ParseKeyValue(StringMapPair& currSection, std::string& line, size_t& begin, size_t& end);

	//! Map of all loaded sections in the ini file
	SectionMap m_sections;
	//! a pointer to the currectly selected section
	KeyValMap* m_currSection;
};
/******************************************************************************/
/*!
Takes a key and returns a value of templated type

\param [in] key
The key from the file
\param [in, out] value
The value that will be filled in if the key exists
*/
/******************************************************************************/
template<typename T>
void M5IniFile::GetValue(const std::string& key, T& value) const
{
	KeyValMapCItor itor = m_currSection->find(key);
	M5DEBUG_ASSERT(itor != m_currSection->end(), "Ini Key could not be found");

	std::stringstream ss(itor->second);
	ss >> value;
}
/******************************************************************************/
/*!
Takes a key and returns a value of type type string

\param [in] key
The key from the file
\param [in, out] value
The value that will be filled in if the key exists
*/
/******************************************************************************/
template<>
inline void M5IniFile::GetValue(const std::string& key, std::string& value) const
{
	KeyValMapCItor itor = m_currSection->find(key);
	M5DEBUG_ASSERT(itor != m_currSection->end(), "Ini Key could not be found");

	value = itor->second;
}
/******************************************************************************/
/*!
Adds a key/value pair to the current section of the M5IniFile.  If the key
already exists, it will be updated with the new value.

\attention This won't be added to any actual files until you call WriteFile

\param [in] key
The key name to add.

\param [in] value
The value to add

*/
/******************************************************************************/
template<typename T>
void M5IniFile::AddKeyValue(const std::string& key, const T& value)
{
	std::stringstream ss;
	ss << value;
	KeyValMapItor found = m_currSection->find(key);
	if (found == m_currSection->end())
		m_currSection->insert(std::make_pair(key, ss.str()));
	else
		found->second = ss.str();
}
#endif //M5INI_FILE_H
