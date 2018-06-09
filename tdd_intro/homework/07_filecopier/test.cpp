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
const std::string s_srcFolder("C:\\Folder");
const std::string s_dstFolder("D:\\Folder");
const std::string s_fileName("file.name");

std::string ConcatPath(const std::string& left, const std::string& right)
{
    if (left.empty())
    {
        return right;
    }
    if (right.empty())
    {
        return left;
    }

    return left + "\\" + right;
}

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
        : m_fileSystem(fileSystem)
    {
    }

    virtual void Copy(const std::string& src, const std::string& dst) override
    {
        if (!m_fileSystem->IsFileExist(src))
        {
            throw std::runtime_error("Source path not exist");
        }

        FilesList files(m_fileSystem->GetFilesList(src));
        if (files.empty())
        {
            return;
        }

        m_fileSystem->CreateDirectory(dst);

        for (const std::string& srcFilePath : files)
        {
            const std::string dstPath(m_fileSystem->GetRelativePath(srcFilePath, src));
            m_fileSystem->CopyFile(srcFilePath, ConcatPath(dst, dstPath));
        }
    }

private:
    IFileSystem* m_fileSystem;
};

TEST(FileCopierTests, Copy_NotExistentSrc)
{
    MockFileSystem fileSystem;

    const std::string notExistentSrc("NotExistentSrc");
    EXPECT_CALL(fileSystem, IsFileExist(notExistentSrc)).WillOnce(testing::Return(false));

    FileCopier fileCopier(&fileSystem);
    EXPECT_THROW(fileCopier.Copy(notExistentSrc, s_dstFolder), std::runtime_error);
}

TEST(FileCopierTests, Copy_GetFilesListEmpty)
{
    MockFileSystem fileSystem;
    testing::InSequence copySequence;

    EXPECT_CALL(fileSystem, IsFileExist(s_srcFolder))
            .WillOnce(testing::Return(true));
    EXPECT_CALL(fileSystem, GetFilesList(s_srcFolder))
            .WillOnce(testing::Return(FilesList()));
    EXPECT_CALL(fileSystem, CopyFile(testing::_, testing::_)).Times(0);

    FileCopier fileCopier(&fileSystem);
    EXPECT_NO_THROW(fileCopier.Copy(s_srcFolder, s_dstFolder));
}

TEST(FileCopierTests, Copy_OneFile)
{
    MockFileSystem fileSystem;
    testing::InSequence copySequence;

    const std::string srcFilePath(ConcatPath(s_srcFolder, s_fileName));
    const std::string dstFilePath(ConcatPath(s_dstFolder, s_fileName));

    EXPECT_CALL(fileSystem, IsFileExist(s_srcFolder))
            .WillOnce(testing::Return(true));
    EXPECT_CALL(fileSystem, GetFilesList(s_srcFolder))
            .WillOnce(testing::Return(FilesList({srcFilePath})));
    EXPECT_CALL(fileSystem, CreateDirectory(s_dstFolder))
            .WillOnce(testing::Return(true));
    EXPECT_CALL(fileSystem, GetRelativePath(srcFilePath, s_srcFolder))
            .WillOnce(testing::Return(s_fileName));
    EXPECT_CALL(fileSystem, CopyFile(srcFilePath, dstFilePath))
            .WillOnce(testing::Return(true));

    FileCopier fileCopier(&fileSystem);
    EXPECT_NO_THROW(fileCopier.Copy(s_srcFolder, s_dstFolder));
}

TEST(FileCopierTests, Copy_TwoFiles)
{
    MockFileSystem fileSystem;
    testing::InSequence copySequence;

    const std::string srcFilePath(ConcatPath(s_srcFolder, s_fileName));
    const std::string dstFilePath(ConcatPath(s_dstFolder, s_fileName));

    const std::string fileName1(s_fileName+"1");
    const std::string srcFilePath1(ConcatPath(s_srcFolder, fileName1));
    const std::string dstFilePath1(ConcatPath(s_dstFolder, fileName1));

    EXPECT_CALL(fileSystem, IsFileExist(s_srcFolder))
            .WillOnce(testing::Return(true));
    EXPECT_CALL(fileSystem, GetFilesList(s_srcFolder))
            .WillOnce(testing::Return(FilesList({srcFilePath, srcFilePath1})));
    EXPECT_CALL(fileSystem, CreateDirectory(s_dstFolder))
            .WillOnce(testing::Return(true));
    EXPECT_CALL(fileSystem, GetRelativePath(srcFilePath, s_srcFolder))
            .WillOnce(testing::Return(s_fileName));
    EXPECT_CALL(fileSystem, CopyFile(srcFilePath, dstFilePath))
            .WillOnce(testing::Return(true));
    EXPECT_CALL(fileSystem, GetRelativePath(srcFilePath1, s_srcFolder))
            .WillOnce(testing::Return(fileName1));
    EXPECT_CALL(fileSystem, CopyFile(srcFilePath1, dstFilePath1))
            .WillOnce(testing::Return(true));

    FileCopier fileCopier(&fileSystem);
    EXPECT_NO_THROW(fileCopier.Copy(s_srcFolder, s_dstFolder));
}

TEST(FileCopierTests, ConcatPath_ConcatLeftWithRight)
{
    EXPECT_EQ("C:\\Folder\\file.name", ConcatPath(s_srcFolder, s_fileName));
}

TEST(FileCopierTests, ConcatPath_ConcatLeftWithoutRight)
{
    EXPECT_EQ(s_srcFolder, ConcatPath(s_srcFolder, ""));
}

TEST(FileCopierTests, ConcatPath_ConcatRightWithoutLeft)
{
    EXPECT_EQ(s_fileName, ConcatPath("", s_fileName));
}

TEST(FileCopierTests, ConcatPath_ConcatEmpty)
{
    EXPECT_EQ("", ConcatPath("", ""));
}
