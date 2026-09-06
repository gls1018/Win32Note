## 1. WM_CHAR消息如何产生?

先看一下消息循环

```cpp
MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
```

当按下A键时, 产生WM_KEYDOWN消息.

- hwnd
- msg = WM_KEYDOWN
- wParam = 'A'
- lParam = ...



通过GetMessage抓到这个消息,然后交给 TranslateMessage函数处理.

TranslateMessage根据下面状态, 判断是否要生成A和a

- Shift
- Caps Lock
- 键盘布局
- AltGr
- Dead Key
- IME

## 2. 附带信息

- wPara: 实际的字符数据
- lPara
- lPara: 位掩码 Key Data Mask, 一个32位整数, 包含该按键事件的附加信息. 和WM_KEYDOWN消息一样.
  - 0~15: 重复次数, 长按时触发的连发次数.
  - 16~23: OEM扫描码, 硬件相关的按键原始位置编码.
    - `UINT scanCode = (lParam >> 16) & 0xFF;`来获得
  - 24:扩展键标志, 如果是右Alt, 右Ctrl, 方向键, 或者是小键盘键,值为1.
  - 25~28:保留不用
  - 30: 表示该按键是否是第一次按下.
    - 通过`lPara & (1<<30)`来获得
    - 0表示第一次按下
    - 1表示重复按键



## 3. 示例代码

```cpp
LRESULT OnWmChar(HWND hWnd, WPARAM wPara, LPARAM lPara)
{
	if (wPara == 'A')
		std::print("A is Pressed\n");
	if (wPara == 'a')
		std::print("a is Pressed\n");
	return DefWindowProc(hWnd, WM_CHAR, wPara, lPara);
}
```

