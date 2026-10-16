## 1. 消息来源

- 用户点击标题栏上的最大化、最小化和关闭按钮
- 用户鼠标点击标题栏.
- Alt + Space 呼出系统菜单栏.
- 点击菜单栏中的选项
- 从任务栏还原窗口 

## 2. 附带信息

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

## 3. 自定义处理

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



## 4. 默认处理

