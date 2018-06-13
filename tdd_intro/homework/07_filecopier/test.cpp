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

//Copy single file
//Copy empty folder
//Copy folder with folders


#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IFileSystem
{
public:
    virtual ~IFileSystem();
    std::vector<std::String> GetChild(const std::string& path);
    bool IsDir(const std::string& path);
    void Copy(const std::string& src, const std::string& dst);
};

