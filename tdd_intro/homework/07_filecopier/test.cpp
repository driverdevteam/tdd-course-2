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

const std::string s_emptyFolderSrcPath("C://emptyFolder");
const std::string s_emptyFolderDstPath("D://emptyFolder");

const std::string s_unexistantFolderSrcPath("C://unexistantFolder");
const std::string s_unexistantFolderDstPath("D://unexistantFolder");

const std::string s_singleFileFolderSrcPath("C://singleFileFolder");
const std::string s_singleFileFolderDstPath("D://singleFileFolder");
const std::string s_singleFileFolderFileName("file");
const std::string s_singleFileFolderFileSrc("C://singleFileFolder//file");
const std::string s_singleFileFolderFileDst("D://singleFileFolder//file");

class IFileCopier
{
public:
    ~IFileCopier(){}
    virtual void CopyFile(const std::string& src, const std::string& dst) = 0;
    virtual void CopyFolder(const std::string& src, const std::string& dst) = 0;

    virtual bool CheckIfExists(const std::string& file) = 0;
    virtual bool IsFolder(const std::string& path) = 0;
};

class FileCopierMock : public IFileCopier
{
public:
    MOCK_METHOD2(CopyFile, void(const std::string&, const std::string&));
    MOCK_METHOD2(CopyFolder, void(const std::string&, const std::string&));

    MOCK_METHOD1(CheckIfExists, bool(const std::string&));
    MOCK_METHOD1(IsFolder, bool(const std::string&));
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
    if (m_fileCopier.CheckIfExists(src))
    {
        if (m_fileCopier.IsFolder(src))
        {
            m_fileCopier.CopyFolder(src, dst);
        }
        else
        {
            m_fileCopier.CopyFile(src, dst);
        }
    }
}

TEST(FileCopier, CopySingleFile)
{
    FileCopierMock mock;
    FileCopier fileCopier(mock);

    EXPECT_CALL(mock, CheckIfExists(s_singleFileSrcPath)).WillOnce(testing::Return(true));
    EXPECT_CALL(mock, IsFolder(s_singleFileSrcPath)).WillOnce(testing::Return(false));
    EXPECT_CALL(mock, CopyFile(s_singleFileSrcPath, s_singleFileDstPath)).Times(1);
    EXPECT_CALL(mock, CopyFolder(testing::_, testing::_)).Times(0);

    fileCopier.Copy(s_singleFileSrcPath, s_singleFileDstPath);
}

TEST(FileCopier, CopyUnexistantFile)
{
    FileCopierMock mock;
    FileCopier fileCopier(mock);

    EXPECT_CALL(mock, CheckIfExists(s_unexistantFileSrcPath)).WillOnce(testing::Return(false));
    EXPECT_CALL(mock, IsFolder(testing::_)).Times(0);
    EXPECT_CALL(mock, CopyFile(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mock, CopyFolder(testing::_, testing::_)).Times(0);

    fileCopier.Copy(s_unexistantFileSrcPath, s_unexistantFileDstPath);
}

TEST(FileCopier, CopyEmptyFolder)
{
    FileCopierMock mock;
    FileCopier fileCopier(mock);

    EXPECT_CALL(mock, CheckIfExists(s_emptyFolderSrcPath)).WillOnce(testing::Return(true));
    EXPECT_CALL(mock, IsFolder(s_emptyFolderSrcPath)).WillOnce(testing::Return(true));
    EXPECT_CALL(mock, CopyFile(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mock, CopyFolder(s_emptyFolderSrcPath, s_emptyFolderDstPath)).Times(1);

    fileCopier.Copy(s_emptyFolderSrcPath, s_emptyFolderDstPath);
}

TEST(FileCopier, CopyUnexistantFolder)
{
    FileCopierMock mock;
    FileCopier fileCopier(mock);

    EXPECT_CALL(mock, CheckIfExists(s_unexistantFolderSrcPath)).WillOnce(testing::Return(false));
    EXPECT_CALL(mock, IsFolder(testing::_)).Times(0);
    EXPECT_CALL(mock, CopyFile(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mock, CopyFolder(testing::_, testing::_)).Times(0);

    fileCopier.Copy(s_unexistantFolderSrcPath, s_unexistantFolderDstPath);
}

TEST(FileCopier, CopyFolderWithSingleFile)
{
    FileCopierMock mock;
    FileCopier fileCopier(mock);

    EXPECT_CALL(mock, CheckIfExists(s_unexistantFolderSrcPath)).WillOnce(testing::Return(true));
    EXPECT_CALL(mock, IsFolder(s_emptyFolderSrcPath)).WillOnce(testing::Return(true));
    EXPECT_CALL(mock, CopyFolder(s_singleFileFolderSrcPath, s_singleFileFolderDstPath)).Times(1);
    EXPECT_CALL(mock, CopyFile(s_singleFileFolderFileSrc, s_singleFileFolderFileDst)).Times(1);

    fileCopier.Copy(s_singleFileFolderSrcPath, s_singleFileFolderDstPath);
}

