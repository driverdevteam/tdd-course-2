#include "FakeFileSystem.h"

FakeFileSystem::FakeFileSystem()
{
    m_root.name = path::preferred_separator;
}

std::vector<std::string> FakeFileSystem::GetChildren(const path &dir)
{
    return { };
}

bool FakeFileSystem::IsDir(const path &obj)
{
    return false;
}

void FakeFileSystem::MakeDir(const path &dir)
{

}

void FakeFileSystem::CopyFile(const path &src, const path &dst)
{

}

bool FakeFileSystem::FileExists(const path &file)
{
    return false;
}

bool FakeFileSystem::DirExists(const path &dir)
{
    return false;
}

void FakeFileSystem::CreateFile(const path &file)
{

}

void FakeFileSystem::CreateDir(const path &dir)
{

}

FakeFileSystem::FileSystemObject &FakeFileSystem::GoTo(const path &path)
{
    return m_root;
}
