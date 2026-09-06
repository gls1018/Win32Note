调用`CreateWindowEx`函数时，系统会发送此消息到`WindowProc`.
附带信息:

- wParam: 0
- lParam: 指向CREATESTRUCT结构体的指针

自定义处理:

- 自定义处理该消息时,**一般是创建子控件或者加载资源**.
- 返回值为0,表示成功.
- 如果返回-1，`CreateWindow`函数将返回`NULL`表示窗口创建失败





**示例代码:**

```cpp
LRESULT OnWMCreate(HWND hWnd, WPARAM wPara, LPARAM lPara)
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
}
```

