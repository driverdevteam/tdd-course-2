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

 - Pass not existent src
 - Copy one file
 - Copy two files
 - Copy folder with file
 - Check empty folder is not copying
 - Copy file and folder with file
 - Copy file hierarchy
*/

using FilesList = std::vector<std::string>;

class IFileSystem
{
public:
    virtual bool IsFileExist(const std::string& path) const = 0;
    virtual FilesList GetFilesList(const std::string& dirPath) const = 0;
    virtual bool IsDirectory(const std::string& path) const = 0;
    virtual std::string GetRelativePath(const std::string& fullPath, const std::string& relativeToPath) const = 0;
    virtual bool CreateDirectory(const std::string& dirPath) const = 0;
    virtual bool CopyFile(const std::string& srcFilePath, const std::string& dstFilePath) const = 0;
};

class MockFileSystem : public IFileSystem
{
public:
    MOCK_CONST_METHOD1(IsFileExist, bool(const std::string& path));
    MOCK_CONST_METHOD1(GetFilesList, FilesList(const std::string& dirPath));
    MOCK_CONST_METHOD1(IsDirectory, bool(const std::string& path));
    MOCK_CONST_METHOD2(GetRelativePath, std::string(const std::string& fullPath, const std::string& relativeToPath));
    MOCK_CONST_METHOD1(CreateDirectory, bool(const std::string& dirPath));
    MOCK_CONST_METHOD2(CopyFile, bool(const std::string& srcFilePath, const std::string& dstFilePath));
};

class IFileCopier
{
public:
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
};

class FileCopier : public IFileCopier
{
public:
    FileCopier(IFileSystem* fileSystem)
    {
    }

    virtual void Copy(const std::string& src, const std::string& dst) override
    {
    }
};

TEST(FileCopierTests, Copy_NotExistentSrc)
{
    MockFileSystem fileSystem;

    const std::string notExistentSrc("NotExistentSrc");
    EXPECT_CALL(fileSystem, IsFileExist(notExistentSrc)).WillOnce(testing::Return(false));

    FileCopier fileCopier(&fileSystem);
    EXPECT_THROW(fileCopier.Copy(notExistentSrc, "D:\\Folder"), std::runtime_error);
}
