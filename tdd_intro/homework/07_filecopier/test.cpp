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
#include <sstream>
//Checklist:
//1. Check file on exist.
//2. Check if filetype is directory.
//3. Copy single file.
//4. Copy empty directory.
//5. Copy directory with another embeded directory.

namespace
{
    const char pathSeparator =
            #ifdef _WIN32
            '\\';
    #else
            '/';
    #endif
    std::string buildPath(std::initializer_list<std::string> list)
    {
        std::stringstream ss;
        for (auto el : list)
        {
            ss << el;
            if (el.back() != pathSeparator)
            {
                ss << pathSeparator;
            }
        }
        std::cout << ss.str();
        return ss.str();
    }
}
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

    StringVector children = filesystem.getChildList(src);
    for (const auto& child : children)
    {
        if  (!filesystem.isDirectory(child))
        {
            filesystem.copy(buildPath({src, child}), buildPath({dst, child}));
        }
        else
        {
            copy(buildPath({src, child}), buildPath({dst, child}));
        }

    }
}

TEST(FileCopierTests, CopyNonExistSingleFile)
{
    MockFileSystem filesystem;
    FileCopier fileCopier(filesystem);

    const std::string file_path = "some_path/to/folder";

    EXPECT_CALL(filesystem, isExist(file_path)).WillOnce(testing::Return(false));
    EXPECT_THROW(fileCopier.copy(file_path, "G:"), std::runtime_error);
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

    EXPECT_CALL(filesystem, copy(buildPath({src_path, files[0]}), buildPath({dst_path, files[0]}))).Times(1);

    fileCopier.copy(src_path, dst_path);
}

TEST(FileCopierTests, CopyFileRecursively)
{
    MockFileSystem filesystem;
    FileCopier fileCopier(filesystem);
    const std::string src_path = "G:\\1";
    const std::string dst_path = "G:\\2";

    StringVector foldersInParentDirectory{"folder1", "folder2"};
    StringVector filesInFolder1{"file1", "file2"};
    StringVector filesInFolder2{"file3", "file4"};


    const std::string folder1_path = buildPath({src_path, foldersInParentDirectory[0]});
    const std::string folder2_path = buildPath({src_path, foldersInParentDirectory[1]});

    EXPECT_CALL(filesystem, getChildList(src_path)).WillOnce(testing::Return(foldersInParentDirectory));
    EXPECT_CALL(filesystem, getChildList(folder1_path)).WillOnce(testing::Return(filesInFolder1));
    EXPECT_CALL(filesystem, getChildList(folder2_path)).WillOnce(testing::Return(filesInFolder2));

    EXPECT_CALL(filesystem, isDirectory(foldersInParentDirectory[0])).WillOnce(testing::Return(true));
    EXPECT_CALL(filesystem, isDirectory(foldersInParentDirectory[1])).WillOnce(testing::Return(true));


    EXPECT_CALL(filesystem, isDirectory(filesInFolder1[0])).WillOnce(testing::Return(false));
    EXPECT_CALL(filesystem, isDirectory(filesInFolder1[1])).WillOnce(testing::Return(false));
    EXPECT_CALL(filesystem, isDirectory(filesInFolder2[0])).WillOnce(testing::Return(false));
    EXPECT_CALL(filesystem, isDirectory(filesInFolder2[1])).WillOnce(testing::Return(false));

    EXPECT_CALL(filesystem, copy(buildPath({folder1_path, filesInFolder1[0]}),
                                 buildPath({dst_path, foldersInParentDirectory[0], filesInFolder1[0]}))).Times(1);

    EXPECT_CALL(filesystem, copy(buildPath({folder1_path, filesInFolder1[1]}),
                                 buildPath({dst_path, foldersInParentDirectory[0], filesInFolder1[1]}))).Times(1);

    EXPECT_CALL(filesystem, copy(buildPath({folder2_path, filesInFolder2[0]}),
                                 buildPath({dst_path, foldersInParentDirectory[1], filesInFolder2[0]}))).Times(1);

    EXPECT_CALL(filesystem, copy(buildPath({folder2_path, filesInFolder2[1]}),
                                 buildPath({dst_path, foldersInParentDirectory[1], filesInFolder2[1]}))).Times(1);

    ON_CALL(filesystem, isExist(testing::_)).WillByDefault(testing::Return(true));

    fileCopier.copy(src_path, dst_path);
}
