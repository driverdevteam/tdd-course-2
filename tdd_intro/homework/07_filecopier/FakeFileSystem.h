#include <vector>
#include <filesystem>
namespace std
{
    using namespace experimental; // for filesystem support
}

using path = std::filesystem::path;

class IFileSystem
{
public:
    virtual ~IFileSystem() { }
    virtual std::vector<std::string> GetChildren(const path& dir) = 0;
    virtual bool IsDir(const path& obj) = 0;

    virtual void MakeDir(const path& dir) = 0;
    virtual void CopyFile(const path& src, const path& dst) = 0;

    virtual bool FileExists(const path& file) = 0;
    virtual bool DirExists(const path& dir) = 0;
};

class FakeFileSystem: public IFileSystem
{
public:
    FakeFileSystem();

    virtual std::vector<std::string> GetChildren(const path& dir);
    virtual bool IsDir(const path& obj);

    virtual void MakeDir(const path& dir);
    virtual void CopyFile(const path& src, const path& dst);

    virtual bool FileExists(const path& file);
    virtual bool DirExists(const path& dir);

private:
    void CreateFile(const path& file);
    void CreateDir(const path& dir);

    struct FileSystemObject
    {
        std::string name;
        std::vector<FileSystemObject> children;
        bool isDir = true;
    };

    FileSystemObject& GoTo(const path& path);

private:
    FileSystemObject m_root;
};
