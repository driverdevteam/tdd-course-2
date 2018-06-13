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
