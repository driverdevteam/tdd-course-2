#include "FakeFileSystem.h"
#include <iterator>

FakeFileSystem::FakeFileSystem(const FileSystemObjects &rootObjects)
    : m_root(root.string(), rootObjects)
{ }

std::set<std::string> FakeFileSystem::GetChildren(const path &dir)
{
    const auto& fsos = GoTo(dir).GetChildren();
    std::set<std::string> children;
    std::transform(fsos.begin(), fsos.end(), std::inserter(children, children.begin()), [](const auto& fso) { return fso.GetName(); });
    return children;
}

bool FakeFileSystem::IsDir(const path &obj)
{
    return GoTo(obj).IsDir();
}

void FakeFileSystem::MakeDir(const path &dir)
{
    GoToDir(dir.parent_path()).AddChild(Folder(dir.filename().string()));
}

void FakeFileSystem::CopyFile(const path &src, const path &dst)
{
    src; // unused
    CreateFile(dst);
}

bool FakeFileSystem::FileExists(const path &file)
{
    auto fso = GoToSafe(file);
    return fso != nullptr && !fso->IsDir();
}

bool FakeFileSystem::DirExists(const path &dir)
{
    auto fso = GoToSafe(dir);
    return fso != nullptr && fso->IsDir();
}

void FakeFileSystem::CreateFile(const path &file)
{
    GoToDir(file.parent_path()).AddChild(File(file.filename().string()));
}

FileSystemObject &FakeFileSystem::GoTo(const path &obj)
{
    FileSystemObject* current = &m_root;
    path::iterator it = obj.begin();
    if (it == obj.end())
    {
        throw std::runtime_error("Path is empty");
    }

    for (++it; it != obj.end(); ++it)
    {
        auto child = std::find_if(current->GetChildren().begin(), current->GetChildren().end(), [&it](const auto& fso)
            { return fso.GetName() == it->string(); }
        );
        if (child == current->GetChildren().end())
        {
            throw std::runtime_error("Path does not exist");
        }
        current = (FileSystemObject*)&(*child);
    }
    return *current;
}

Folder &FakeFileSystem::GoToDir(const path &dir)
{
    auto& target = GoTo(dir);
    if (!target.IsDir())
    {
        throw std::runtime_error("Target path is not a directory");
    }
    return (Folder&)target;
}

FileSystemObject *FakeFileSystem::GoToSafe(const path &path)
{
    FileSystemObject* fso = nullptr;
    try
    {
        fso = &GoTo(path);
    }
    catch(const std::exception&) { }
    return fso;
}

FileSystemObject::FileSystemObject(const std::string& name, bool isDir)
    : name(name)
    , isDir(isDir)
{ }

FileSystemObject::FileSystemObject(const std::string &name, const FileSystemObjects &children)
    : name(name)
    , children(children)
    , isDir(true)
{ }

const bool FileSystemObject::operator==(const FileSystemObject &other) const
{
    return name == other.name;
}

const bool FileSystemObject::operator!=(const FileSystemObject &other) const
{
    return !operator==(other);
}

const bool FileSystemObject::operator<(const FileSystemObject &other) const
{
    return name < other.name;
}

const std::string &FileSystemObject::GetName() const
{
    return name;
}

const FileSystemObjects &FileSystemObject::GetChildren() const
{
    return children;
}

bool FileSystemObject::IsDir() const
{
    return isDir;
}

void Folder::AddChild(const FileSystemObject &child, bool overwrite /*= false*/)
{
    FileSystemObjects::iterator existant = std::find_if(children.begin(), children.end(), [&child](const auto& fso)
        { return fso.GetName() == child.GetName(); }
    );
    if (existant != children.end() && overwrite)
    {
        throw std::runtime_error("Child with specified name is already exist");
    }
    children.insert(child);
}
