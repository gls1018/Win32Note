### 1. 总览



文件打开和创建:

- CreateFile



文件读写:

- ReadFile
- ReadFileEx
- WriteFile
- WriteFileEx





其他辅助函数:

- GetFileSize
- GetFileSizeEx

- LockFile
- UnLockFile





### CreateFile

```
HANDLE CreateFile(
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwSharedMode,
	
	);
```

