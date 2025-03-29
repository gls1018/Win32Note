## 第一个窗口程序

##### WNDCLASSEX数据结构

```cpp
typedef struct _WNDCLASSEX {
    UINT     cbSize;             // 结构体的大小
    UINT     style;              // 窗口样式
    WNDPROC  lpfnWndProc;        // 窗口处理程序
    int      cbClsExtra;         // 窗口类的附加数据大小
    int      cbWndExtra;         // 窗口的附加数据大小
    HANDLE   hInstance;          // 窗口类的应用程序实例句柄
    HICON    hIcon;              // 窗口的图标
    HCURSOR  hCursor;            // 窗口的光标
    HBRUSH   hbrBackground;      // 窗口的背景画刷
    LPCSTR   lpszMenuName;       // 窗口菜单名称
    LPCSTR   lpszClassName;      // 窗口类名称
    HICON    hIconSm;            // 窗口的缩略图标
} WNDCLASSEX;
```





## 内存相关API



## 文件操作相关API



## 线程操作相关API







