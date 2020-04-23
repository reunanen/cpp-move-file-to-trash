#ifndef MOVEFILETOTRASH_H
#define MOVEFILETOTRASH_H

#include <string>

// - may throw on error
// - may return false if user cancels the operation (which is not an error)
bool move_file_to_trash(const std::wstring& filename);

#endif // MOVEFILETOTRASH_H
