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

using namespace testing;

std::string DirSeparator()
{
    return "/";
}

std::string BuildPath(const std::string& parentDir, const std::string& fileName)
{
    return parentDir + DirSeparator() + fileName;
}

class IFileSystem
{
public:
    virtual ~IFileSystem() {}
    virtual std::vector<std::string> GetChild(const std::string& path) = 0;
    virtual bool IsDir(const std::string& path) = 0;
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
};

class MocFileSystem : public IFileSystem
{
public:
    MOCK_METHOD1(GetChild, std::vector<std::string>(const std::string&));
    MOCK_METHOD1(IsDir, bool(const std::string&));
    MOCK_METHOD2(Copy, void(const std::string&, const std::string&));
};

class IFileCopier
{
public:
    virtual ~IFileCopier() {}
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
};

class FileCopier : public IFileCopier
{
public:
    FileCopier(IFileSystem& fileSystem);

    virtual void Copy(const std::string& src, const std::string& dst) override;

private:
    IFileSystem& m_fileSystem;
};

FileCopier::FileCopier(IFileSystem &fileSystem)
    : m_fileSystem(fileSystem)
{

}

void FileCopier::Copy(const std::string &src, const std::string &dst)
{
    std::vector<std::string> child = m_fileSystem.GetChild(src);
    for (const auto& children : child)
    {
        m_fileSystem.Copy(BuildPath(src, children), BuildPath(dst, children));
    }
}


TEST(FileCopierTest, CopySingleFile)
{
    MocFileSystem moc;
    FileCopier copier(moc);
    std::vector<std::string> files{"singleFileName"};

    std::string srcPath;
    std::string dstPath;
    EXPECT_CALL(moc, GetChild(_)).WillOnce(Return(files));
    ON_CALL(moc, IsDir(files[0])).WillByDefault(Return(false));
    EXPECT_CALL(moc, Copy(BuildPath(srcPath, files[0]), BuildPath(dstPath, files[0]))).Times(1);

    copier.Copy(srcPath, dstPath);
}

TEST(FileCopierTest, CopyEmptyFolder)
{
    MocFileSystem moc;
    FileCopier copier(moc);
    std::vector<std::string> files{};

    EXPECT_CALL(moc, GetChild(_)).WillOnce(Return(files));
    EXPECT_CALL(moc, Copy(_, _)).Times(0);

    std::string srcPath;
    std::string dstPath;
    copier.Copy(srcPath, dstPath);
}

TEST(FileCopierTest, CopyFolderWithFolders)
{
    MocFileSystem moc;
    FileCopier copier(moc);
    std::vector<std::string> filesInParentFolder{"sub_folder_1", "sub_folder_1"};
    std::vector<std::string> filesInSubfolder_1{"file_1", "file_2"};
    std::vector<std::string> filesInSubfolder_2{"file_3", "file_4"};

    std::string srcPath;
    std::string dstPath;
    EXPECT_CALL(moc, GetChild(dstPath)).WillOnce(Return(filesInParentFolder));
    EXPECT_CALL(moc, GetChild(filesInParentFolder[0])).WillOnce(Return(filesInSubfolder_1));
    EXPECT_CALL(moc, GetChild(filesInParentFolder[1])).WillOnce(Return(filesInSubfolder_2));

    EXPECT_CALL(moc, IsDir(filesInParentFolder[0])).WillOnce(Return(true));
    EXPECT_CALL(moc, IsDir(filesInParentFolder[1])).WillOnce(Return(true));
    ON_CALL(moc, IsDir(_)).WillByDefault(Return(false));

    EXPECT_CALL(moc, Copy(BuildPath(BuildPath(srcPath, filesInParentFolder[0]), filesInSubfolder_1[0])
                , BuildPath(BuildPath(dstPath,  filesInParentFolder[0]), filesInSubfolder_1[0]))).Times(1);

    EXPECT_CALL(moc, Copy(BuildPath(BuildPath(srcPath, filesInParentFolder[0]), filesInSubfolder_1[1])
                , BuildPath(BuildPath(dstPath,  filesInParentFolder[0]), filesInSubfolder_1[1]))).Times(1);

    EXPECT_CALL(moc, Copy(BuildPath(BuildPath(srcPath, filesInParentFolder[1]), filesInSubfolder_1[0])
                , BuildPath(BuildPath(dstPath,  filesInParentFolder[1]), filesInSubfolder_1[0]))).Times(1);

    EXPECT_CALL(moc, Copy(BuildPath(BuildPath(srcPath, filesInParentFolder[1]), filesInSubfolder_1[1])
                , BuildPath(BuildPath(dstPath,  filesInParentFolder[1]), filesInSubfolder_1[1]))).Times(1);

    copier.Copy(srcPath, dstPath);
}
