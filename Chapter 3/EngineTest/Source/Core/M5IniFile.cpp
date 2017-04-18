/******************************************************************************/
/*!
file    M5IniFile.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/16

Class to read from or write to an ini file
*/
/******************************************************************************/
#include "M5IniFile.h"
#include <fstream>
#include <ostream>

/******************************************************************************/
/*!
Default Constructor for M5IniFile
*/
/******************************************************************************/
M5IniFile::M5IniFile(void)
{
	m_sections.insert(std::make_pair("", KeyValMap()));
	SetToSection("");
}
/******************************************************************************/
/*!
Reads an .ini file and stores the data for later searching.

\param [in] fileName
The name of the .ini file to read.
*/
/******************************************************************************/
void M5IniFile::ReadFile(const std::string& fileName)
{
	//Clear old data
	m_currSection = 0;
	m_sections.clear();

	std::ifstream inFile(fileName, std::ios::in);

	//check if the file was opened properly
	M5DEBUG_ASSERT(inFile.is_open(), "File Could Not be opened!");

	StringMapPair currSection;//First section has no name, it's the global section
	std::string line;

	while (!inFile.eof())
	{
		//Read a line
		if (!std::getline(inFile, line))
			break;

		//Get end points
		size_t begin = 0, end = line.length();

		RemoveLeadingSpaces(line, begin, end);

		//Ignore empty lines and ; comments
		if (begin >= (end) || line[begin] == ';')
		{
			continue;
		}
		else if (line[begin] == '[')//New section
			ParseSectionName(currSection, line, begin, end);
		else //Key/value
			ParseKeyValue(currSection, line, begin, end);
	}//end while

	//Add the last section
	m_sections.insert(currSection);
	inFile.close();
	SetToSection("");
}
/******************************************************************************/
/*!
Sets the active search section to the specified sectionName of the ini file.

\param [in] sectionName
The name of the section to set active.
*/
/******************************************************************************/
void M5IniFile::SetToSection(const std::string& sectionName)
{
	SectionMapItor itor = m_sections.find(sectionName);
	M5DEBUG_ASSERT(itor != m_sections.end(), "Section name could not be found!")
	m_currSection = &(itor->second);
}
/******************************************************************************/
/*!
Takes a single string and separates the key and the value, then stores them
in sPair.

\param [out] sPair
The storage for the key and the value.

\param [in] line
The line containing the key and the value

\param [in, out] begin
The logical beginning of the line

\param [in, out] end
The logical ending of the line

*/
/******************************************************************************/
void M5IniFile::SeperateKeyValueFromLine(StringPair& sPair,
	const std::string& line, size_t& begin, size_t& end) const
{
	size_t firstEnd, secondBegin;
	//Find the equal sign
	firstEnd = secondBegin = line.find_first_of('=', begin);

	//if(begin >= firstEnd)
	M5DEBUG_ASSERT(firstEnd != std::string::npos, "There was no equal sign in key value");

	//Remove spaces between key and =
	RemoveTrailingSpaces(line, begin, --firstEnd);
	//Remove spaces in front of value
	RemoveLeadingSpaces(line, ++secondBegin, end);
	//check for ; comments after value
	size_t commentEnd = line.find_first_of(';', secondBegin);
	if (commentEnd != std::string::npos)
	{
		end = commentEnd;
	}
	//Remove spaces after value
	RemoveTrailingSpaces(line, secondBegin, --end);
	//create my key and value
	sPair.first = line.substr(begin, firstEnd - begin + 1);
	sPair.second = line.substr(secondBegin, end - secondBegin + 1);
}
/******************************************************************************/
/*!
Removes brackets and extra spaces around the section name

\param [in, out] line
The line to change

\param [in, out] begin
The logical beginning of the line.

\param [in, out] end
The logical ending of the line.

*/
/******************************************************************************/
void M5IniFile::GetSectionName(std::string& line, size_t& begin, size_t& end) const
{
	++begin;//We know the first character is [
	RemoveLeadingSpaces(line, begin, end); //find start of name
	end = line.find_first_of(']');//find the end of section bracket
								  
								  
	//There is no ending ] character so the section name is invalid
	M5DEBUG_ASSERT(begin != end && static_cast<size_t>(end) != std::string::npos,
		"Invalid Section Name");

	RemoveTrailingSpaces(line, begin, --end);//we know end is ]
	line = line.substr(begin, end - begin + 1);
}
/******************************************************************************/
/*!
Removes leading spaces and tabs from a line.

\param [in, out] line
The line change.

\param [in, out] begin
The logical beginning of the line.

\param [in, out] end
The logical ending of the line.

*/
/******************************************************************************/
void M5IniFile::RemoveLeadingSpaces(const std::string& line, size_t& begin,
	size_t& end) const
{
	//if line size is zero we are done
	if (begin >= end)
		return;
	//Start at the beginning and make sure there are no spaces or tabs;
	while (line[begin] == ' ' || line[begin] == '\t')
	{
		if (begin == std::string::npos)
			break;
		++begin;
	}
}
/******************************************************************************/
/*!
Removes trailing spaces and tabs from a line.

\param [in] line
The line change.

\param [in, out] begin
The logical beginning of the line.

\param [in, out] end
The logical ending of the line.

*/
/******************************************************************************/
void M5IniFile::RemoveTrailingSpaces(const std::string& line, size_t& begin,
	size_t& end) const
{
	if (begin >= end)
		return;
	while (line[end] == ' ' || line[end] == '\t')
		--end;
}
/******************************************************************************/
/*!
The function to extract a section name from a line.

\param [in, out] currSection
The previous section info that must be added and then cleared.

\param [in, out] line
The line change.

\param [in, out] begin
The logical beginning of the line.

\param [in, out] end
The logical ending of the line.

*/
/******************************************************************************/
void M5IniFile::ParseSectionName(StringMapPair& currSection, std::string& line,
	size_t& begin, size_t& end)
{
	m_sections.insert(currSection);//We are on a new section, so insert previous
	GetSectionName(line, begin, end);
	//Start the new section here
	currSection.first = line;
	currSection.second.clear();
}
/******************************************************************************/
/*!
The function to extract a key and value from a line.

\param [in, out] currSection
The section to add this key and value to.

\param [in, out] line
The line change.

\param [in, out] begin
The logical beginning of the line.

\param [in, out] end
The logical ending of the line.

*/
/******************************************************************************/
void M5IniFile::ParseKeyValue(StringMapPair& currSection, std::string& line,
	size_t& begin,
	size_t& end)
{
	StringPair sPair;
	SeperateKeyValueFromLine(sPair, line, begin, end);
	currSection.second.insert(sPair);
}
/******************************************************************************/
/*!
Adds a section to the to M5IniFile. 

\attention This won't be added to any files until you call WriteFile

\param [in] sectionName
The section name to add.

*/
/******************************************************************************/
void M5IniFile::AddSection(const std::string& sectionName)
{
	SectionMapCItor found = m_sections.find(sectionName);
	if (found == m_sections.end())
		m_sections.insert(std::make_pair(sectionName, KeyValMap()));
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
void M5IniFile::AddKeyValue(const std::string& key, const std::string& value)
{
	KeyValMapItor found = m_currSection->find(key);
	if (found == m_currSection->end())
		m_currSection->insert(std::make_pair(key, value));
	else
		found->second = value;
}
/******************************************************************************/
/*!
Writes the current contents of the M5IniFile class to a file.

\param [in] fileName
The file to create or overwrite
*/
/******************************************************************************/
void M5IniFile::WriteFile(const std::string& fileName) const
{
	//Create out file and check if it can be opened.
	std::ofstream outFile(fileName, std::ios::out);
	if (!outFile.is_open())
		return;

	//First see if empty section
	SectionMapCItor emptySection = m_sections.find("");
	if (emptySection == m_sections.end())
	{
		outFile << ";The IniFile object was empty when writing this file" << std::endl;
		outFile.close();
		return;
	}

	//Alwasy write global section first
	KeyValMapCItor mapBegin = emptySection->second.begin();
	KeyValMapCItor mapEnd = emptySection->second.end();

	for (; mapBegin != mapEnd; ++mapBegin)
		outFile << mapBegin->first << " = " << mapBegin->second << std::endl;
	outFile << std::endl;

	//Then loop through the rest of the sections
	SectionMapCItor sectionBegin = m_sections.begin();
	SectionMapCItor sectionEnd = m_sections.end();

	for (; sectionBegin != sectionEnd; ++sectionBegin)
	{
		//If we find the global/empty section, just skip
		if (sectionBegin->first == "")
			continue;

		mapBegin = sectionBegin->second.begin();
		mapEnd = sectionBegin->second.end();

		//print section name then key/value pairs
		outFile << "[" << sectionBegin->first << "]" << std::endl;
		for (; mapBegin != mapEnd; ++mapBegin)
			outFile << mapBegin->first << " = " << mapBegin->second << std::endl;
		outFile << std::endl;
	}

	outFile.close();

}




