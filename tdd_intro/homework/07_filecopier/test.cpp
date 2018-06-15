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

/*
 * Test plan:
 * 1. Copy single file
 * 2. Copy several files
 * 3. Copy folder with files
 * 4. Copy folder with folders and files
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FakeFileSystem.h"

class IFileCopier
{
public:
    virtual void CopyFolderRecursive(const path& src, const path& dst) = 0;
};
