#include "move-file-to-trash.h"

#ifdef WIN32
#include <Windows.h>
#include <vector>
#include <sstream>

void move_file_to_trash(const std::wstring& filename)
{
    // Need to double-terminate the string; see https://stackoverflow.com/a/42555504/19254
    const size_t length = filename.length();
    std::vector<wchar_t> buffer(length + 2);
    memcpy(buffer.data(), filename.c_str(), length * sizeof(wchar_t));
    buffer[length] = L'\0';
    buffer[length + 1] = L'\0';

    SHFILEOPSTRUCT operation;
    memset(&operation, 0, sizeof operation);
    operation.wFunc = FO_DELETE;
    operation.pFrom = buffer.data();
    operation.fFlags = FOF_ALLOWUNDO;
    const int ret = SHFileOperation(&operation);

    // "Returns zero if successful; otherwise nonzero. Applications normally should simply check for zero or nonzero."
    // (source: https://msdn.microsoft.com/en-us/library/windows/desktop/bb762164(v=vs.85).aspx)
    const bool success = ret == 0;

    if (!success) {
        std::ostringstream error;
        error << "Unable to move the file to the recycle bin; error code = " << ret << " (see Winerror.h to understand what the code means)";
        throw std::runtime_error(error.str());
    }
}

#endif // WIN32
