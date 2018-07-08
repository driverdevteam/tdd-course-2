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

//Checklist:
//1. Check file on exist.
//2. Check if filetype is directory.
//3. Copy single file.
//4. Copy empty directory.
//5. Copy directory with another embeded directory.

using StringVector = std::vector<std::string>;

class IFileSystem
{
public:
    virtual ~IFileSystem();
    virtual bool isExist(const std::string& path) = 0;
    virtual StringVector getChildList(const std::string& path) = 0;
    virtual bool isDirectory(const std::string& path) = 0;
    virtual void copy(const std::string& src, const std::string& dst) = 0;
};

class IFileCopier
{
public:
    virtual ~IFileCopier();
    virtual void copy(const std::string& src, const std::string& dst) = 0;
};



TEST(FileCopierTests, CopyNonExistSingleFile)
{
    MockFileSystem filesystem;
    FileCopier fileCopier(&fileSystem);

    const std::string file_path = "some_path/to/folder";

    EXPECT_CALL(filesystem, IsExist(file_path)).WillOnce(testing::Return(false));
    EXPECT_THROW(fileCopier.Copy(file_path, "G:\\"), std::runtime_error);
}

