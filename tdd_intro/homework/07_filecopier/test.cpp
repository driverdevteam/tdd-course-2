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
Tests list
-Copy one file
-Copy list of files from folder
-Copy folder
-Copy folders recurcive
-Check folder empty
-Check Folder hierarchy
*/


class IFileCopier
{
public:
    virtual ~IFileCopier(){}
    virtual std::vector<std::string> GetFilesFromFolder(const std::string& path)=0;
    virtual bool IsDir(const std::string& path)=0;
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
};

class MockFileCopier:public IFileCopier
{
public:
    MOCK_METHOD1(GetFilesFromFolder, std::vector<std::string>(const std::string&));
    MOCK_METHOD1(IsDir, bool(const std::string&));
    MOCK_METHOD2(Copy, void(const std::string& src, const std::string& dst));
};

class FileCopier
{
public:
    FileCopier(IFileCopier& fileSystem);
    void Copy(const std::string& src, const std::string& dst);

private:
    IFileCopier& m_copyCore;
};

FileCopier::FileCopier(IFileCopier &fileSystem):m_copyCore(fileSystem)
{
}

void FileCopier::Copy(const std::string &src, const std::string &dst)
{
    m_copyCore.Copy(src, dst);
    std::vector<std::string> fileList = m_copyCore.GetFilesFromFolder(src);

    for(int i=0;i< fileList.size(); ++i)
    {
       m_copyCore.Copy(src + "/"+ fileList[i], dst + "/" + fileList[i] );
    }
}

TEST(CopyFilesTests, CopyOnlyFolder)
{
    MockFileCopier mock;
    FileCopier copier(mock);

    EXPECT_CALL(mock, Copy("srcPath","dstPath")).Times(1);

    EXPECT_CALL(mock, GetFilesFromFolder("srcPath")).WillOnce(testing::Return(std::vector<std::string>{}));

    copier.Copy("srcPath","dstPath");
}

TEST(CopyFilesTests, CopyOneFile)
{
    MockFileCopier mock;
    FileCopier copier(mock);
    EXPECT_CALL(mock, Copy("srcPath","dstPath")).Times(1);
    EXPECT_CALL(mock, GetFilesFromFolder("srcPath")).WillOnce(testing::Return(std::vector<std::string>{"file", "file"}));
    EXPECT_CALL(mock, Copy("srcPath/file","dstPath/file")).Times(2);

    copier.Copy("srcPath","dstPath");
}






