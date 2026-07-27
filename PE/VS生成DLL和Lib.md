## 1. Dll

### 1.1 DllMain函数

将[项目属性]-->[配置属性]-->[配置类型]设置为动态链接库Dll.

Dll也有main函数叫做DllMain; 

```cpp
BOOL DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{

		} break;
		case DLL_PROCESS_DETACH:
		{

		} break;

		case DLL_THREAD_ATTACH:
		{

		} break;

		case DLL_THREAD_DETACH:
		{

		}break;
	}
	return TRUE;
}
```



- hModule: 当前Dll在进程中的模块句柄. 实际上它就是被映射到内存后的基地址(ImageBase).

- ul_reason_for_call
  - DLL_PROCESS_ATTACH: 一个进程第一次加载该Dll.
  - DLL_PROCESS_DETACH: Dll从当前进程卸载, 引用计数器变为0. 通常在调用FreeLibrary后
  - DLL_THREAD_ATTACH: 进程中新创建了一个线程. 
  - DLL_THREAD_DETACH: 线程退出.



### 1.2 __declspec(dllexport) 关键字



假设我们导出两个函数, 可以这样写

```cpp
extern "C"
{
    __declspec(dllexport) int add(int a, int b)
    {
        return a + b;
	}
    
    __declspec(dllexport) int sub(int a, int b)
    {
        return a - b;
	}
}
```



这里需要注意以下， 导出的函数需要用`extern "C" `来修饰.

因为C++会采用名字修饰.`Add`函数可能会被导出成`?Add@@YAHHH@Z`. 采用C风格导出就可以避免这个问题.

### 1.3 生成的三个文件

dll项目会生成下面3个文件

- MyDll.dll: 实际二进制代码存放的地方, 是一个标准的PE文件.
- MyDll.exp
- MyDll.lib

MyDll.dll不是静态链接库那种lib文件, 它实际上是**Import Library 导入库**.

这个导入库里面包含了**地址跳转表**和**重定位信息**.

### 1.4 显式使用Dll

显式使用Dll中函数不要lib文件, 只要dll文件配合Windows中的一些API函数就可以了.

- GetProcAddress
- LoadLibrary

```cpp
int main()
{
	HMODULE hMod = LoadLibrary(L"./MyDll.dll");
	if (hMod == NULL)
	{
		return -1;
	}
	using FuncPtrType = int(*)(int, int);
	FuncPtrType add = (FuncPtrType)GetProcAddress(hMod, "add");

	if (add == NULL)
	{
		return -2;
	}
	std::cout << "add(1, 4) = " << add(1, 5) << std::endl;
	return 0;
}
```

### 1.5 隐式使用Dll

- 将dll文件放到exe目录下.
- 将lib文件放到源文件目录下, 使用 `#pragma comment`进行链接.

实际使用过程中:

- 需要函数声明
- 函数声明前面加不加 `__declspec(dllimport)`好像不影响函数调用.

```cpp
#pragma comment(lib, "./MyDll.lib")
extern "C"
{
__declspec(dllimport)
int add(int, int);

int sub(int, int);
}
int main()
{
	std::cout << "add(1, 4) = " << add(1, 5) << std::endl;
	std::cout << "sub(4, 1) = " << sub(4, 1) << std::endl;
	return 0;
}
```

## 2. Lib

将[项目属性]-->[配置属性]-->[配置类型]设置为静态链接库Dll.

和Dll不一样的是, lib不需要DllMain函数, Dll是一个PE文件, 但lib不是一个PE文件,

如果编写DllMain函数, 会被当成一个普通函数来处理.

关于lib文件的链接, 可以使用`#pragma comment`来进行

```cpp
#pragma comment(lib, "./MyDll.lib")
```

