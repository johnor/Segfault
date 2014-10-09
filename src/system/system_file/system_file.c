#include "system_file.h"
#include <stdio.h>

void* openFile(const char* filename, const char* mode)
{
  return (void*)fopen(filename, mode);
}

int writeFile(void* file, const char* fileEntry)
{
  int writtenCharacters;
  writtenCharacters = fprintf((FILE*)file, "%s", fileEntry);
  return writtenCharacters;
}

int closeFile(void* file)
{
  return fclose((FILE*)file);
}
