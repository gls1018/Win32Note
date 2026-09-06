## 1. 消息何时产生

当用户选择菜单项, 控件向父窗口发送通知消息, 或者加速键被触发时, 系统会发送WM_COMMAND消息.

WM_COMMAND消息一共有三个来源

- 菜单 MENU
- 控件 Control
- 加速键 Accelerator

## 2. 消息附带信息

当WM_COMMAND来源于菜单时.

- wParam
  - High Word == 0
  - Low Word == Menu ID
- lParam == 0，不用管 

当WM_COMMAND来源于控件时

- wParam
  - High Word = Notify Code
  - Low Word = Control ID
- lParam = Control Hanle.



当WM_COMMAND来源于加速键时. 和菜单一样, 加速键就是菜单项的快捷键.

## 3. 自定义处理

- 如果自定义处理, **必须返回0， 以此告知操作系统该消息我已经处理**.

```cpp
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        int code = HIWORD(wParam);
        HWND hCtrl = (HWND)lParam;

        switch (id)
        {
        case ID_FILE_OPEN:      // 菜单或加速键
            OnFileOpen(hWnd);
            break;

        case ID_BUTTON_OK:      // 按钮 ID
            if (code == BN_CLICKED)
                OnButtonOK(hWnd);
            break;

        case ID_EDIT_NAME:      // 编辑框 ID
            if (code == EN_CHANGE)
                OnEditNameChanged(hWnd);
            break;

        case ID_COMBO_SELECT:
            if (code == CBN_SELCHANGE)
                OnComboSelect(hWnd);
            break;

        default:
            // 转发给 DefWindowProc 处理系统默认行为（如果有）
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }
        return 0; // 消息已处理
    }

    // ... 其他消息

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}
```

