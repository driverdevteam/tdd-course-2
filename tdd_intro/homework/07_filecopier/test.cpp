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
    3. Copy empty folder
    4. Attempt to copy unexistant folder
    5. Copy folder with single file
    6. Copy folder with several files
    7. Copy folder with several files and other folders */

const std::string s_singleFileSrcPath("C://singleFile");
const std::string s_singleFileDstPath("D://singleFile");

const std::string s_unexistantFileSrcPath("C://unexistantFile");
const std::string s_unexistantFileDstPath("D://unexistantFile");

class IFileCopier
{
public:
    ~IFileCopier(){}
    virtual void CopyFile(const std::string& src, const std::string& dst) = 0;
    virtual bool CheckFileExists(const std::string& file) = 0;
};

class FileCopierMock : public IFileCopier
{
public:
    MOCK_METHOD2(CopyFile, void(const std::string&, const std::string&));
    MOCK_METHOD1(CheckFileExists, bool(const std::string&));
};

class FileCopier
{
public:
    FileCopier(IFileCopier& fileCopier);
    void Copy(const std::string& src, const std::string& dst);
private:
    IFileCopier& m_fileCopier;
};

FileCopier::FileCopier(IFileCopier &fileCopier)
    : m_fileCopier(fileCopier)
{
}

void FileCopier::Copy(const std::string &src, const std::string &dst)
{
    if (m_fileCopier.CheckFileExists(src))
    {
        m_fileCopier.CopyFile(src, dst);
    }
}

TEST(FileCopier, CopySingleFile)
{
    FileCopierMock mock;
    FileCopier fileCopier(mock);

    EXPECT_CALL(mock, CheckFileExists(s_singleFileSrcPath)).WillOnce(testing::Return(true));
    EXPECT_CALL(mock, CopyFile(s_singleFileSrcPath, s_singleFileDstPath)).Times(1);

    fileCopier.Copy(s_singleFileSrcPath, s_singleFileDstPath);
}

TEST(FileCopier, CopyUnexistantFile)
{
    FileCopierMock mock;
    FileCopier fileCopier(mock);

    EXPECT_CALL(mock, CheckFileExists(s_unexistantFileSrcPath)).WillOnce(testing::Return(false));
    EXPECT_CALL(mock, CopyFile(s_unexistantFileSrcPath, testing::_)).Times(0);

    fileCopier.Copy(s_unexistantFileSrcPath, s_unexistantFileDstPath);
}
