## 1. WM_COMMAND

### 1.1 消息来源

当用户选择菜单项, 控件向父窗口发送通知消息, 或者加速键被触发时, 系统会发送WM_COMMAND消息.

WM_COMMAND消息一共有三个来源

- 菜单 MENU
- 控件 Control
- 加速键 Accelerator



### 1.2 附带参数

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



### 1.3 自定义处理WM_COMMAND

关于WM_COMMAND的处理过程如下:

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

## 2. WM_SYSCOMMAND

### 2.1 消息来源

每一个普通窗口都有一个系统菜单.`Alt + Space`或者点击左上角图标都会出现系统菜单

每一个菜单项都有一个命令ID.例如Close. 对应SC_CLOSE

Windows系统最终发送

```cpp
WM_SYSCOMMAND
wParam = SC_CLOSE
```

关于WM_SYSCOMMAND的附带参数. lPara不必关系, 只需要注意wPara就可以了

```tex
┌────────────────────────────┐
│  高12位      │ 低4位       │
├────────────────────────────┤
│ Command ID   │ Reserved    │
└────────────────────────────┘
```

比如判断是否是SC_CLOSE. `wPara & 0xFFF0 == SC_CLOSE`



### 2.2 自定义处理

对于WM_SYSCOMMAND的自定义处理如下:

```cpp
LRESULT OnSysCommand(HWND hWnd, WPARAM wPara, LPARAM lPara)
{
	switch (wPara & 0xFFF0)
	{
		case SC_CLOSE:
		{
			int nRes = MessageBox(hWnd, L"确定关闭窗口?", L"提示", MB_OKCANCEL);
			if (nRes == IDOK)
				break;
			if (nRes == IDCANCEL)
				return 0;
		}
	}
	return DefWindowProc(hWnd, WM_SYSCOMMAND, wPara, lPara);
}
```





