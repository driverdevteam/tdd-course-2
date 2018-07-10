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

/*  1. Copy single file
    2. Attempt to copy unexistant file
    3. Copy folder with single file
    4. Copy empty folder
    5. Attempt to copy unexistant folder
    6. Copy folder with several files
    7. Copy folder with several files and other folders */

const std::string s_singleFileSrcPath("C://singleFile");
const std::string s_singleFileDstPath("D://singleFile");

class IFileCopier
{
public:
    ~IFileCopier();
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
    virtual void CopyFile(const std::string& src, const std::string& dst) = 0;
};

class FileCopierMock : public IFileCopier
{
public:
    MOCK_METHOD2(Copy, void(const std::string&, const std::string&));
    MOCK_METHOD2(CopyFile, void(const std::string&, const std::string&));
};

TEST(FileCopier, CopySingleFile)
{
    FileCopierMock mock;

    EXPECT_CALL(mock, CopyFile(s_singleFileSrcPath, testing::_)).Times(1);
    mock.Copy(s_singleFileSrcPath, s_singleFileDstPath);
}
