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
const std::string s_fileName1(s_fileName + "1");
const std::string s_subFolder("Subfolder");

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

const std::string s_srcFilePath(ConcatPath(s_srcFolder, s_fileName));
const std::string s_dstFilePath(ConcatPath(s_dstFolder, s_fileName));
const std::string s_srcFilePath1(ConcatPath(s_srcFolder, s_fileName1));
const std::string s_dstFilePath1(ConcatPath(s_dstFolder, s_fileName1));
const std::string s_srcFolderPath(ConcatPath(s_srcFolder, s_subFolder));
const std::string s_dstFolderPath(ConcatPath(s_dstFolder, s_subFolder));
const std::string s_srcFolderFilePath(ConcatPath(s_srcFolderPath, s_fileName));
const std::string s_dstFolderFilePath(ConcatPath(s_dstFolderPath, s_fileName));

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
            const std::string relativePath(m_fileSystem->GetRelativePath(srcFilePath, src));
            const std::string dstPath(ConcatPath(dst, relativePath));
            if (m_fileSystem->IsDirectory(srcFilePath))
            {
                Copy(srcFilePath, dstPath);
            }
            else
            {
                m_fileSystem->CopyFile(srcFilePath, dstPath);
            }
        }
    }

private:
    IFileSystem* m_fileSystem;
};

void CopyFileTest(const std::string& srcFolder,
                  const std::string& srcFilePath,
                  const std::string& fileName,
                  const std::string& dstFilePath,
                  MockFileSystem& fileSystem)
{
    EXPECT_CALL(fileSystem, GetRelativePath(srcFilePath, srcFolder))
            .WillOnce(testing::Return(fileName));
    EXPECT_CALL(fileSystem, IsDirectory(srcFilePath))
            .WillOnce(testing::Return(false));
    EXPECT_CALL(fileSystem, CopyFile(srcFilePath, dstFilePath))
            .WillOnce(testing::Return(true));
}

void CopyFolderTest(const std::string& srcFolder,
                    const std::string& srcFilePath,
                    const std::string& fileName,
                    MockFileSystem& fileSystem)
{
    EXPECT_CALL(fileSystem, GetRelativePath(srcFilePath, srcFolder))
            .WillOnce(testing::Return(fileName));
    EXPECT_CALL(fileSystem, IsDirectory(srcFilePath))
            .WillOnce(testing::Return(true));
}

void BeforeCopyFileTest(const std::string& srcFolder,
                        const std::string& dstFolder,
                        const FilesList& filesList,
                        MockFileSystem& fileSystem)
{
    EXPECT_CALL(fileSystem, IsFileExist(srcFolder))
            .WillOnce(testing::Return(true));
    EXPECT_CALL(fileSystem, GetFilesList(srcFolder))
            .WillOnce(testing::Return(filesList));
    EXPECT_CALL(fileSystem, CreateDirectory(dstFolder))
            .WillOnce(testing::Return(true));
}

void EmptyFolderTest(const std::string& srcFolder, MockFileSystem& fileSystem)
{
    EXPECT_CALL(fileSystem, IsFileExist(srcFolder))
            .WillOnce(testing::Return(true));
    EXPECT_CALL(fileSystem, GetFilesList(srcFolder))
            .WillOnce(testing::Return(FilesList()));
    EXPECT_CALL(fileSystem, CreateDirectory(srcFolder)).Times(0);
    EXPECT_CALL(fileSystem, CopyFile(testing::_, testing::_)).Times(0);
}
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

    EmptyFolderTest(s_srcFolder, fileSystem);

    FileCopier fileCopier(&fileSystem);
    EXPECT_NO_THROW(fileCopier.Copy(s_srcFolder, s_dstFolder));
}

TEST(FileCopierTests, Copy_OneFile)
{
    MockFileSystem fileSystem;
    testing::InSequence copySequence;

    BeforeCopyFileTest(s_srcFolder,
                       s_dstFolder,
                       FilesList({s_srcFilePath}),
                       fileSystem);

    CopyFileTest(s_srcFolder, s_srcFilePath, s_fileName, s_dstFilePath, fileSystem);

    FileCopier fileCopier(&fileSystem);
    EXPECT_NO_THROW(fileCopier.Copy(s_srcFolder, s_dstFolder));
}

TEST(FileCopierTests, Copy_TwoFiles)
{
    MockFileSystem fileSystem;
    testing::InSequence copySequence;

    BeforeCopyFileTest(s_srcFolder,
                       s_dstFolder,
                       FilesList({s_srcFilePath, s_srcFilePath1}),
                       fileSystem);

    CopyFileTest(s_srcFolder, s_srcFilePath, s_fileName, s_dstFilePath, fileSystem);
    CopyFileTest(s_srcFolder, s_srcFilePath1, s_fileName1, s_dstFilePath1, fileSystem);

    FileCopier fileCopier(&fileSystem);
    EXPECT_NO_THROW(fileCopier.Copy(s_srcFolder, s_dstFolder));
}

TEST(FileCopierTests, Copy_FolderWithFile)
{
    MockFileSystem fileSystem;
    testing::InSequence copySequence;

    BeforeCopyFileTest(s_srcFolder,
                       s_dstFolder,
                       FilesList({s_srcFolderPath}),
                       fileSystem);

    CopyFolderTest(s_srcFolder, s_srcFolderPath, s_subFolder, fileSystem);

    BeforeCopyFileTest(s_srcFolderPath,
                       s_dstFolderPath,
                       FilesList({s_srcFolderFilePath}),
                       fileSystem);

    CopyFileTest(s_srcFolderPath, s_srcFolderFilePath, s_fileName, s_dstFolderFilePath, fileSystem);

    FileCopier fileCopier(&fileSystem);
    EXPECT_NO_THROW(fileCopier.Copy(s_srcFolder, s_dstFolder));
}

TEST(FileCopierTests, Copy_FolderWithoutFiles)
{
    MockFileSystem fileSystem;
    testing::InSequence copySequence;

    BeforeCopyFileTest(s_srcFolder,
                       s_dstFolder,
                       FilesList({s_srcFolderPath}),
                       fileSystem);

    CopyFolderTest(s_srcFolder, s_srcFolderPath, s_subFolder, fileSystem);

    EmptyFolderTest(s_srcFolderPath, fileSystem);

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
