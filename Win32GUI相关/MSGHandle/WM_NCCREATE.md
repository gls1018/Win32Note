## 1. 消息来源

在调用`CreateWindow`或者`CreateWindowEx`时会产生该消息. 产生的顺序如下

```cpp
CreateWindowEx()
    |
    +-- WM_GETMINMAXINFO
    |
    +-- WM_NCCREATE
    |      |
    |      +-- 初始化窗口数据
    |      +-- 返回 TRUE 表示允许继续创建
    |
    +-- WM_NCCALCSIZE
    |
    +-- WM_CREATE
    |      |
    |      +-- 创建窗口相关资源
    |      +-- 返回 0 表示成功
    |
    +-- 其他创建过程中的消息
    |
    +-- CreateWindowEx() 返回 HWND
```





## 2. 自定义处理

消息附带信息

- wParam : 0
- lParam : 指向`CREATESTRUCT`结构体的指针.



方式一: 完全自定义处理

```cpp
case WM_NCCREATE: {
    CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

    // 获取窗口创建参数
    int nWidth = pCreate->cx;
    int nHeight = pCreate->cy;

    // 获取窗口实例句柄
    HINSTANCE hInstance = pCreate->hInstance;
	
    // Other Code ...
    
    return TRUE;
}
```

方式二: 执行自己的初始化后再调用默认窗口过程

```cpp
case WM_NCCREATE: {
    // 自定义处理
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
```

返回值:

- TRUE : 允许继续创建窗口

- FALSE : 终止窗口创建, CreateWindowEx 返回 NULL.

  

注意: CreateWindowEx函数返回的是窗口句柄, 但是在 WM_NCCREATE 消息中, 窗口句柄已经有效.