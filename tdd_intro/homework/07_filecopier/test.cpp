/*
Folder copying
Implement a class for recursively copying files from source directory to the destination directory.

A folder hierarchy and file names must be saved.

Empty folders should not be copied at all.

For example it can be something that looks like a

class IFileCopier
{
public:
	virtual void Copy(const std::string& src, const std::string& dst) = 0;
};
You don't need to test filesystem functions. To work with a filesystem you should declare an interface and to mock it.

You can start with GMock from https://goo.gl/j7EkQX, good luck!
*/
#include <gtest/gtest.h>
#include <gmock/gmock.h>

/*
 - Check if file/directory exist
 - Get list of files in direcroty
 - Check if file is directory
 - Get relative path
 - Create directory
 - Copy file

 - Copy one file
 - Copy two files
 - Copy folder with file
 - Check empty folder is not copying
 - Copy file and folder with file
 - Copy file hierarchy
*/
