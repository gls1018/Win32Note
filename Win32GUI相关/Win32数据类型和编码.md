

## 数据类型

基本数据类型:

- BOOL: int 4字节
- DWORD: unsigned long 32bit
- WORD: unsigned short 16bit
- CHAR: char   8bit
- WCHAR:  wchar_t  16bit Unicode character


句柄类型
- HANDLE
- HMODULE
- HWND
- HDC
  

一些通用类型:

- WinMain / wWinMain  : _tWinMain
- LPSTR / LPWSTR : LPTSTR




## 字符集和编码

Windows系统采用Unicode-16编码. 大部分汉字以固定长度 16bit 存储, 少部分以 32bit 存储.
UTF16 有大端和小端之别. 