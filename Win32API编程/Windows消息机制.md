
## 消息机制介绍
Windows系统是基于消息机制的。 操作系统有一个系统消息队列, 应用程序每个`GUI线程`有一个线程消息队列(`没有所谓的进程消息队列`), 线程一开始创建的时候并没有消息队列,只有线程第一次调用GDI函数(`User32.dll或者gdi32.dll中的函数时`),系统才会为它创建消息队列，也就是非GUI线程是没有消息队列的，同时一个线程也只有一个消息队列，但可以有多个窗口, 这些窗口共用一个消息队列,正常UI线程会启动一个消息循环,不断从线程消息队列中取出消息交给窗口过程函数`WndProc`去处理.


## MSG结构体

```cpp
struct MSG
{
    HWND hWnd;         // 产生消息的窗口的句柄
    UINT UMsgId;       // 消息ID
    WPARAM wParam;     // 附带参数
    LPARAM lParam;     // 附带参数
    DWORD time;        // 消息产生的时间
    POINT pt;          // 消息产生时在屏幕上的坐标
}
```

## 常见消息处理

### WM_NCCREATE

在调用`CreateWindow`或者`CreateWindowEx`时会产生该消息. 产生的顺序如下
- WM_NCCREATE
- WM_NCCALCSIZE
- WM_CREATE

附带信息
- wParam: 0
- lParam: 指向`CREATESTRUCT`结构体的指针。

自定义处理：
- 返回值必须为`TRUE`

```cpp
typedef struct tagCREATESTRUCT {
    LPVOID lpCreateParams;  // CreateWindowEx 的 lParam 参数
    HINSTANCE hInstance;    // 当前应用程序实例句柄
    HMENU hMenu;            // 菜单句柄
    HWND hwndParent;        // 父窗口句柄
    int cy;                 // 窗口高度
    int cx;                 // 窗口宽度
    int y;                  // 窗口初始位置 (y 坐标)
    int x;                  // 窗口初始位置 (x 坐标)
    LONG style;             // 窗口样式
    LPCSTR lpszName;        // 窗口名称
    LPCSTR lpszClass;       // 窗口类名
    DWORD dwExStyle;        // 扩展窗口样式
} CREATESTRUCT;
```
lParam参数的附带信息,其实就是调用`CreateWindowEX`函数时的传递的参数信息.


### WM_CREATE

调用`CreateWindowEx`函数时，系统会发送此消息到`WindowProc`.
附带信息:
- wParam: 0
- lParam: 指向CREATESTRUCT结构体的指针

自定义处理:
- 自定义处理该消息时,一般是创建子控件或者加载资源.
- 返回值为0,表示成功，返回-1，`CreateWindow`函数将返回`NULL`

```cpp
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
        LPVOID lpParam = pcs->lpCreateParams;

        // 例如，创建一个按钮控件
        HWND hButton = CreateWindow(
            "BUTTON", "Click Me",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 20, 100, 30,
            hwnd, (HMENU)1, pcs->hInstance, NULL
        );

        if (!hButton)
        {
            return -1;  // 返回 -1 表示窗口创建失败
        }

        return 0;  // 成功处理 WM_CREATE
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
```

### WM_DROPFILES

以下几种情况当用户拖拽文件到窗口上时会触发WM_DROPFILES消息.

- 在调用CreateWindowEx函数时设置了窗口扩展属性`WS_ACCEPTFILES`
- 调用了DragAcceptFiles函数.

附带信息：
- wParam:HDROP类型的指针
- lParam: 0

自定义处理:
- 处理`WM_DROPFILES`消息时,主要通过`DragQueryFile`函数来实现, 该函数既可以得到拖拽文件的数量,也可以得到每个文件的路径

```cpp
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wPara, LPARAM lPara)
{
    switch(uMsg)
    {
        case WM_DROPFILES:
		{
                HDROP hDrop = reinterpret_cast<HDROP>(wPara);
                //先查询一下文件的数量
                UINT uFileCount = DragQueryFile(hDrop, 0xFFFFFFFF, szFilePath, 0);
                for(UINT i=0; i<uFileCount; i++)
                {
                    DragQueryFile(hDrop, i, szFilePath, MAX_PATH);
                    //这里打印一下文件名
                    OutputDebugString((szFilePath));
                    memset(szFilePath, 0, MAX_PATH);
				}
                DragFinish(hDrop);
		}
	}
    return DefWindowProc(hWnd, uMsg, wPara, lPara);
}
```

补充:
`DragAcceptFiles`函数作用于`EDIT`控件,可以让用户拖拽文件到文本框.

### WM_SETCURSOR

### WM_NCHITTEST
