
## 1.前言
Windows系统是基于消息机制的。 操作系统有一个系统消息队列, 应用程序每个`GUI线程`有一个线程消息队列(`没有所谓的进程消息队列`), 线程一开始创建的时候并没有消息队列,只有线程第一次调用GDI函数(`User32.dll或者gdi32.dll中的函数时`),系统才会为它创建消息队列，也就是非GUI线程是没有消息队列的，同时一个线程也只有一个消息队列，但可以有多个窗口, 这些窗口共用一个消息队列,正常UI线程会启动一个消息循环,不断从线程消息队列中取出消息交给窗口过程函数`WndProc`去处理.


## 2. MSG结构体

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



## 3. 队列消息 & 非队列消息

队列消息和非队列消息的区别是消息是先进入消息队列，还是直接进入窗口过程函数`WndProc`.

队列消息: Windows把消息放到线程的消息队列中, 通过GetMessage抓到消息, 然后再由DispatchMessage派发到WndProc函数.

非队列消息: Window不把消息放到消息队列, 直接调用目标窗口的WndProc



典型的队列消息:

- 键盘消息

  - WM_KEYDOWN

  - WM_KEYUP

  - WM_CHAR

- 鼠标消息

  - WM_MOUSEMOVE

  - WM_LBUTTONDOWN

  - WM_LBUTTONUP

  - WM_RBUTTONDOWN

  - WM_RBUTTONUP





典型的非队列消息:

- WM_NCHITTEST: `优先级最高`的非队列消息

- WM_NCCREATE

- WM_CREATE

- WM_DESTROY

- WM_NC_DESTROY

- WM_ACTIVATE

- WM_SIZE

  



## 4. 常见消息流程



- WM_GETMINMAXINFO   `0x24`
- WM_NCCREATE        `0x81`
- WM_NCCALCSIZE     `0x83`
- `0x93`
- `0x94`
- `0x94`
- `0x94`
- `0x94`
- `0x83`
- `0x01` WM_CREATE
- `0x46` WM_WINDOWPOSCHANING
- `0x83`
- `0x93`
- `0x94`
- `0x94`
- `0x94`
- `0x94`
- `0x83`

- `0x47` WM_WINDOWPOSCHANGED
- `0x93`
- `0x7F` WM_GETICON
- `0x7F`
- `0x7F`
- `0x210` WM_PARENTNOTIFY 

- `0x46`
- `0x46`
- `0x1C` WM_ACTIVATEAPP 
- `0x86` WM_NCACTIVATE 
- `0x93`
- `0x93`
- `0x91`
- 

## 5. 相关API

- GetMessage

- PeekMessage

- TranslateMessage

- DispatchMessage

- SendMessage

- PostMessage

  
  
  

### 3.1 GetMessage

从线程消息队列中抓消息,  抓到 `WM_QUIT`消息时, 返回`FALSE`.

```cpp
BOOL GetMessage(
  [out]          LPMSG lpMsg,
  [in, optional] HWND  hWnd,
  [in]           UINT  wMsgFilterMin,
  [in]           UINT  wMsgFilterMax
);
```



### 3.2 PeekMessgae

### 3.3 TranslateMessage



### 3.4 DispatchMessage



该函数的作用是将一个已经获取到的消息(MSG结构体)，分派给该消息所指定的目标窗口的"WndProc"去执行.

```cpp
LRESULT DispatchMessage(
  [in] const MSG *lpMsg
);
```

