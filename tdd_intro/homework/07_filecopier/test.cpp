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

const std::string s_dstPath = "dstPath";
const std::string s_srcPath = "srcPath";
const std::string s_fileName = "SomeFile";

std::string JoinPath(const std::string& parent, const std::string& child)
{
    return parent + "/" + child;
}

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
       if(m_copyCore.IsDir(JoinPath(src, fileList[i])))
       {
            Copy(JoinPath(src, fileList[i]), JoinPath(dst,fileList[i] ));
       }
       m_copyCore.Copy(JoinPath(src, fileList[i]), JoinPath(dst, fileList[i]));
    }
}

TEST(CopyFilesTests, CopyOnlyFolder)
{
    MockFileCopier mock;
    FileCopier copier(mock);

    EXPECT_CALL(mock, Copy(s_srcPath, s_dstPath)).Times(1);

    EXPECT_CALL(mock, GetFilesFromFolder(s_srcPath)).WillOnce(testing::Return(std::vector<std::string>{}));

    copier.Copy(s_srcPath, s_dstPath);
}

TEST(CopyFilesTests, CopyOneFile)
{
    MockFileCopier mock;
    FileCopier copier(mock);
    EXPECT_CALL(mock, Copy(s_srcPath, s_dstPath)).Times(1);
    EXPECT_CALL(mock, GetFilesFromFolder(s_srcPath)).WillOnce(testing::Return(std::vector<std::string>{s_fileName, s_fileName}));
    EXPECT_CALL(mock, Copy(JoinPath(s_srcPath, s_fileName),JoinPath(s_dstPath, s_fileName))).Times(2);

    copier.Copy(s_srcPath, s_dstPath);
}

TEST(CopyFilesTests, CopyManyFile)
{
    MockFileCopier mock;
    FileCopier copier(mock);
    EXPECT_CALL(mock, Copy(s_srcPath, s_dstPath)).Times(1);
    EXPECT_CALL(mock, GetFilesFromFolder(s_srcPath)).WillOnce(testing::Return(std::vector<std::string>{s_fileName, s_fileName, s_fileName, s_fileName, s_fileName}));
    EXPECT_CALL(mock, Copy(JoinPath(s_srcPath, s_fileName),JoinPath(s_dstPath, s_fileName))).Times(5);
    copier.Copy(s_srcPath, s_dstPath);
}

TEST(CopyFilesTests, CopyFolder)
{
    MockFileCopier mock;
    FileCopier copier(mock);
    EXPECT_CALL(mock, Copy(s_srcPath, s_dstPath));
    EXPECT_CALL(mock, GetFilesFromFolder(testing::_)).WillRepeatedly(testing::Return(std::vector<std::string>{"someFolder"}));
    EXPECT_CALL(mock, Copy(JoinPath(s_srcPath,"someFolder"), JoinPath(s_dstPath,"someFolder"))).Times(1);
    copier.Copy(s_srcPath, s_dstPath);
}
//------------------------------------------------------------
TEST(CopyFilesTests, JoinPath)
{
    EXPECT_EQ("Parent/Child", JoinPath("Parent", "Child"));
}





