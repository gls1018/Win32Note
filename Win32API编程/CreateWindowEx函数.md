## 1. CreateWindowEx 函数

```cpp
HWND CreateWindowEx(
  DWORD     dwExStyle,       // 扩展样式
  LPCSTR    lpClassName,     // 窗口类名
  LPCSTR    lpWindowName,    // 窗口名称（标题）
  DWORD     dwStyle,         // 窗口样式
  int       x,               // 窗口左上角的 x 坐标
  int       y,               // 窗口左上角的 y 坐标
  int       nWidth,          // 窗口宽度
  int       nHeight,         // 窗口高度
  HWND      hWndParent,      // 父窗口句柄
  HMENU     hMenu,           // 菜单句柄
  HINSTANCE hInstance,       // 应用程序实例句柄
  LPVOID    lpParam          // 附加的窗口创建数据（可以是 NULL）
);
```

- dwExStyle: 扩展样式;
  - WS_EX_TOPMOST：窗口始终置顶
  - WS_EX_TRANSPARENT：窗口透明，鼠标点击可以穿透
  - WS_EX_LAYERED：分层窗口，支持透明度和颜色键
  - WS_EX_CLIENTEDGE：窗口客户区有凹陷边缘
  - WS_EX_WINDOWEDGE：窗口边缘凸起
  - WS_EX_ACCEPTFILES:窗口可以接收文件, 拖拽文件到窗口上,系统会发送WM_DROPFILES消息
- lpClassName: WNDCLASS中lpszClassName的值.**使用之前一定要调用RegisterClassEx注册**.
- lpWindowName: 窗口标题
- dwStyle:  窗口样式，
  - WS_POPUP:弹出式窗口,没有标题栏和边框,只有客户区
  - WS_OVERLAPPED:重叠式窗口,自带标题栏





## 2. 创建不同样式的窗口

### 2.1 WS_EX_ACCEPTFILES





## 3. 创建其它控件





