## 1. 附带信息

- wPara: 虚拟键码 Virtual-Key Code，表示哪个键被按下
  - 'A'
  - 'B'
  - VK_RETURN
  - VK_SHIFT
- lPara: 位掩码 Key Data Mask, 一个32位整数, 包含该按键事件的附加信息.
  - 0~15: 重复次数, 长按时触发的连发次数.
  - 16~23: OEM扫描码, 硬件相关的按键原始位置编码.
    - `UINT scanCode = (lParam >> 16) & 0xFF;`来获得
  - 24:扩展键标志, 如果是右Alt, 右Ctrl, 方向键, 或者是小键盘键,值为1.
  - 25~28:保留不用
  - 30: 表示该按键是否是第一次按下.
    - 通过`lPara & (1<<30)`来获得
    - 0表示第一次按下
    - 1表示重复按键

## 2. 几个问题

1. **WM_KEYDOWN是无法判断到底是`A`被按下还是`a`被按下的**.

```cpp
LRESULT OnKeyDown(HWND hWnd, WPARAM wPara, LPARAM lPara)
{
    if(wPara == 'A')
        ;
    if(wPara == 'a')
        ;
}
```

当按下A键时, 无论是A还是a, 永远进入 `wPara == A`, 不会进入`wPara == a`.



2. **按住A不放, 如何判断产生的WM_KEYDOWN消息, 是第一次按下产生的, 还是后续重复产生的? 还有如判断这是第几次产生的?**

```cpp
LRESULT OnKeyDown(HWND hWnd, WPARAM wPara, LPARAM lPara)
{
	if (wPara == 'A')
	{
		static size_t RepeatCount = 1;
		if (lPara & (1 << 30))
		{
			std::print("重复按下: {}\n", ++RepeatCount);
		}
		else
		{
			RepeatCount = 1;
			std::print("第一次按下\n");
		}
	}
	return DefWindowProc(hWnd, WM_KEYDOWN, wPara, lPara);
}

```

lPara的第30位, 表示该按键是否是第一次被按下, 使用 `lPara & (1<<30)`来判断

但是如果判断一个按键重复了多少次, 需要自己来维护, 不能通过`LOWORD(lPara)`来得到， 因为这个值恒为1.



## 3. OEM扫描码和虚拟键码

1. **为什么需要扫描码?**   

OEM扫描码(OEM Scan Code)可以简单理解成**键盘硬件用于表示哪个物理按键被按下的编码.**主要是为了区分物理位置不同，但虚拟键码相同的按键(其实有时候左CTRL和右CTRL的扫描码是相同的.).比如:

```cpp
左Ctrl   右Ctrl
左Shift  右Shift
左Alt    右Alt
```



2. **有了OEM扫描码, 为什么还需要虚拟键码VK_Code?**

因为OEM扫描码太过于硬件化, 不同键盘和布局可能会存在差异, 而且Windows并不关心这个物理按键的扫描码是什么, 它更关心的是,这是什么按键.

所以Windows在中间做了一层抽象，VK_Code的核心作用是屏蔽底层键盘硬件差异, 给应用程序统一硬件编号.

```cpp
LRESULT OnKeyDown(HWND hWnd, WPARAM wPara, LPARAM lPara)
{
	if (wPara == VK_CONTROL)
	{
		UINT scanCode = (lPara >> 16) & 0xFF;
		std::print("Scan Code: {}\n", scanCode);
	}
	return DefWindowProc(hWnd, WM_KEYDOWN, wPara, lPara);
}
```

