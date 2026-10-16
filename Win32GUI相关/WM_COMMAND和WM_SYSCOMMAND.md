

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





