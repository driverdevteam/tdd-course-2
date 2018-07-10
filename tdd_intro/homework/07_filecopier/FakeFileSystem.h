#include <set>
#include <filesystem>
namespace std
{
    using namespace experimental; // for filesystem support
}

using path = std::filesystem::path;
static path::value_type separator = path::preferred_separator;
static path root = std::basic_string<path::value_type>(1, separator);

class IFileSystem
{
public:
    virtual ~IFileSystem() { }
    virtual std::set<std::string> GetChildren(const path& dir) = 0;
    virtual bool IsDir(const path& obj) = 0;

    virtual void MakeDir(const path& dir) = 0;
    virtual void CopyFile(const path& src, const path& dst) = 0;

    virtual bool FileExists(const path& file) = 0;
    virtual bool DirExists(const path& dir) = 0;
};

class FileSystemObject;
using FileSystemObjects = std::set<FileSystemObject>;
class FileSystemObject
{
public:
    FileSystemObject(const std::string& name, bool isDir);
    FileSystemObject(const std::string& name, const FileSystemObjects& children);

    bool const operator==(const FileSystemObject& other) const;
    bool const operator!=(const FileSystemObject& other) const;
    bool const operator<(const FileSystemObject& other) const;

    const std::string& GetName() const;
    const FileSystemObjects& GetChildren() const;
    bool IsDir() const;

protected:
    std::string name;
    FileSystemObjects children;

private:
    bool isDir = true;
};

class File : public FileSystemObject
{
public:
    explicit File(const std::string& name): FileSystemObject(name, false) { }
};

class Folder : public FileSystemObject
{
public:
    explicit Folder(const std::string& name) : FileSystemObject(name, true) { }
    Folder(const std::string& name, const FileSystemObjects& children) : FileSystemObject(name, children) { }
    void AddChild(const FileSystemObject& child, bool overwrite = false);
};

class FakeFileSystem: public IFileSystem
{
public:
    explicit FakeFileSystem(const FileSystemObjects& rootObjects = { });

    virtual std::set<std::string> GetChildren(const path& dir);
    virtual bool IsDir(const path& obj);

    virtual void MakeDir(const path& dir);
    virtual void CopyFile(const path& src, const path& dst);

    virtual bool FileExists(const path& file);
    virtual bool DirExists(const path& dir);

private:
    void CreateFile(const path& file);
    void CreateDir(const path& dir);

    FileSystemObject& GoTo(const path& path);
    Folder &GoToDir(const path& dir);
    FileSystemObject* GoToSafe(const path& path);

private:
    FileSystemObject m_root;
};
