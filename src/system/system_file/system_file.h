#ifndef SYSTEM_FILE_H_
#define SYSTEM_FILE_H_

void* openFile(const char* filename, const char* mode);
int writeFile(void* file, const char* fileEntry);
int closeFile(void* file);

#endif /* SYSTEM_FILE_H_ */
