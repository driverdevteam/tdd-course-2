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

/*
 * Test plan:
 * 1. Copy single file
 * 2. Copy several files
 * 3. Copy folder with files
 * 4. Copy folder with folders and files
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FakeFileSystem.h"

class IFileCopier
{
public:
    virtual void CopyFolderRecursive(const path& src, const path& dst) = 0;
};


TEST(FakeFileSystem, RootTest)
{
    FakeFileSystem fs;
    EXPECT_TRUE(fs.DirExists(root));
    EXPECT_TRUE(fs.GetChildren(root).empty());
}

TEST(FakeFileSystem, SingleFileTest)
{
    File file("file");
    FileSystemObjects rootObjects = { file };
    FakeFileSystem fs(rootObjects);

    EXPECT_TRUE(fs.DirExists(root));
    EXPECT_TRUE(fs.FileExists(root / "file"));
    ASSERT_EQ(1, fs.GetChildren(root).size());
    EXPECT_EQ("file", *fs.GetChildren(root).begin());
}

TEST(FakeFileSystem, SingleFolderTest)
{
    Folder folder("folder");
    FileSystemObjects rootObjects = { folder };
    FakeFileSystem fs(rootObjects);

    EXPECT_TRUE(fs.DirExists(root));
    EXPECT_TRUE(fs.DirExists(root / "folder"));
    ASSERT_EQ(1, fs.GetChildren(root).size());
    EXPECT_EQ("folder", *fs.GetChildren(root).begin());
}

TEST(FakeFileSystem, FoldersWithNextedFolders)
{
    Folder folder1("folder1");
    Folder folder2("folder2", FileSystemObjects { folder1 });
    Folder folder3("folder3", FileSystemObjects { folder2 });
    FileSystemObjects rootObjects = { folder3 };
    FakeFileSystem fs(rootObjects);

    EXPECT_TRUE(fs.DirExists(root));
    ASSERT_EQ(1, fs.GetChildren(root).size());
    EXPECT_TRUE(fs.DirExists(root / "folder3"));
    ASSERT_EQ(1, fs.GetChildren(root / "folder3").size());
    EXPECT_TRUE(fs.DirExists(root / "folder3" / "folder2"));
    ASSERT_EQ(1, fs.GetChildren(root / "folder3" / "folder2").size());
    EXPECT_TRUE(fs.DirExists(root / "folder3" / "folder2" / "folder1"));
    ASSERT_EQ(0, fs.GetChildren(root / "folder3" / "folder2" / "folder1").size());
}

TEST(FakeFileSystem, FoldersWithNestedFoldersAndFiles)
{
    File file2("nested_file");
    Folder folder2("nested_folder", FileSystemObjects { file2 } );
    File file1("root_file");
    Folder folder1("root_folder", FileSystemObjects { folder2 });

    FileSystemObjects rootObjects = { file1, folder1 };
    FakeFileSystem fs(rootObjects);

    EXPECT_TRUE(fs.DirExists(root));
    ASSERT_EQ(2, fs.GetChildren(root).size());
    EXPECT_TRUE(fs.DirExists(root / "root_folder"));
    EXPECT_TRUE(fs.FileExists(root / "root_file"));
    ASSERT_EQ(1, fs.GetChildren(root / "root_folder").size());
    EXPECT_TRUE(fs.DirExists(root / "nested_folder"));
    EXPECT_TRUE(fs.FileExists(root / "nested_folder" / "nested_file"));
}
