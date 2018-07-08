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
#include <vector>
#include <string>
#include <memory>
#include "ifilecopier.h"
#include "ifilesystem.h"

//Checklist:
//1. Check file on exist.
//2. Check if filetype is directory.
//3. Copy single file.
//4. Copy empty directory.
//5. Copy directory with another embeded directory.

class MockFileSystem: public IFileSystem
{
public:
    virtual ~MockFileSystem() {}
    MOCK_METHOD1(isExist, bool(const std::string&));
    MOCK_METHOD1(getChildList, StringVector(const std::string&));
    MOCK_METHOD1(isDirectory, bool(const std::string&));
    MOCK_METHOD2(copy, void(const std::string&, const std::string&));
};

class FileCopier: public IFileCopier
{
public:
    virtual ~FileCopier() {}
    FileCopier(IFileSystem& fs): filesystem(fs) {}
    virtual void copy(const std::string &src, const std::string &dst) override;
private:
    IFileSystem& filesystem;
};

void FileCopier::copy(const std::string &src, const std::string &dst)
{
    if (!filesystem.isExist(src))
    {
        throw std::runtime_error("Can't copy a not exist file");
    }

    std::vector<std::string> children = filesystem.getChildList(src);
    for (const auto& child : children)
    {
        if  (!filesystem.isDirectory(child))
        {
            filesystem.copy(src + "\\" + child, dst + "\\" + child);
        }

    }
}

TEST(FileCopierTests, CopyNonExistSingleFile)
{
    MockFileSystem filesystem;
    FileCopier fileCopier(filesystem);

    const std::string file_path = "some_path/to/folder";

    EXPECT_CALL(filesystem, isExist(file_path)).WillOnce(testing::Return(false));
    EXPECT_THROW(fileCopier.copy(file_path, "G:\\"), std::runtime_error);
}

TEST(FileCopierTests, CopySingleFile)
{
    MockFileSystem filesystem;
    FileCopier fileCopier(filesystem);

    const std::string src_path = "G:\\1";
    const std::string dst_path = "G:\\2";
    StringVector files = {"G:\\1.txt"};

    EXPECT_CALL(filesystem, isExist(src_path)).WillOnce(testing::Return(true));
    EXPECT_CALL(filesystem, getChildList(src_path)).WillOnce(testing::Return(files));
    EXPECT_CALL(filesystem, isDirectory(files[0])).WillOnce(testing::Return(false));

    EXPECT_CALL(filesystem, copy(src_path + "\\" + files[0], dst_path + "\\" + files[0])).Times(1);

    fileCopier.copy(src_path, dst_path);
}
