
## WM_SYSCOMMAND 消息是如何产生的?

- 用户点击标题栏上的最大化、最小化和关闭按钮
- 用户鼠标点击标题栏.
- Alt + Space 呼出系统菜单栏.
- 点击菜单栏中的选项
- 从任务栏还原窗口 



## WM_SYSCOMMAND 消息的附带信息是什么?

- lPara 
  - 鼠标触发: 鼠标坐标
  - 键盘触发: 0
  
- wPara & 0xFFF0 
  - SC_CLOSE        //关闭
  - SC_MAXIMIZE     //最大化
  - SC_MINIMIZE     //最小化
  - SC_MOVE         //移动窗口
  - SC_SIZE         //调整大小
  - SC_RESTORE      //还原
  


验证代码:
```cpp
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	switch (msg)
	{
		case WM_SYSCOMMAND:
		{
			switch (wPara & 0xFFF0)
			{
				case SC_CLOSE:
				{
					std::cout << "SC_CLOSE\n";
				}break;

				case SC_MAXIMIZE:
				{
					std::cout << "SC_MAXIMIZE\n";
				}break;

				case SC_MINIMIZE:
				{
					std::cout << "SC_MINIMIZE\n";
				}break;

				case SC_RESTORE:
				{
					std::cout << "SC_RESTORE\n";
				}break;

				case SC_SIZE:
				{
					std::cout << "SC_SIZE\n";
				}break;

				case SC_MOVE:
				{
					std::cout << "SC_MOVE\n";
				}break;

				default:
					return DefWindowProcW(hWnd, msg, wPara, lPara);
			}
		}break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;

		default:
			return DefWindowProcW(hWnd, msg, wPara, lPara);
	}
	return DefWindowProcW(hWnd, msg, wPara, lPara);
}
```


## DefWindowProc 对消息是如何默认处理的?


### 关于 SC_CLOSE

`WM_SYSCOMMAND(SC_CLOSE)` 通过点击`x`产生.
DefWindowProc处理过程如下:


```cpp
用户点击 X / Alt+F4
    ↓
WM_SYSCOMMAND (SC_CLOSE)
    ↓
DefWindowProc
    ↓
SendMessage(WM_CLOSE)
    ↓
WindowProc            //如果用户不处理WM_CLOSE消息, 就还是由 DefWindowProc 处理        
    ↓（默认）
DefWindowProc
    ↓
DestroyWindow
    ↓
WM_DESTROY
    ↓
WM_NCDESTROY

```


```cpp
LRESULT CALLBACK DefWindowProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
    switch(msg)
    {
        case WM_SYSCOMMAND:
        {
            switch(wPara & 0xFFF0)
            {
                case SC_CLOSE:
                {
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    return 0;
                }break;

                case SC_MOVE:
                {
                    
                }break;
            }
        }break;

        case WM_PAINT:
        {

        }break;
        
        case WM_CLOSE:
        {
            DestroyWindow(hWnd);
            return 0;
        }break;

        case WM_DESTROY:
        {
            // 什么也不做, 需要用户自己接住这个消息, 自定义处理
            return 0;
        }break;

        case WM_PAINT:
        {

        }break;
    }

}
```

## 对 WM_SYSCOMMAND 消息如何自定义处理?


## 几个问题和注意点


1.  WM_SYSCOMMAND(SC_CLOSE) && WM_CLOSE 为什么要设计成两层? 

- WM_SYSCOMMAND(SC_CLOSE)是关闭意图
- WM_CLOSE 表达的是关闭请求.

  




## 总结

- `WM_SYSCOMMAND`是系统菜单和窗口控制行为的统一入口.
- 