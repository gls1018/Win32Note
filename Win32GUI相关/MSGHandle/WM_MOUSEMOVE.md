## 0. 消息来源

当鼠标在窗口的**客户区**内移动, 就会触发这个消息. 

并不是一个像素就会产生一个WM_MOUSEMOVE消息, 假如鼠标移动很快, 多条WM_MOUSEMOVE消息可能会被合并一条消息.

## 1. 附带信息

`wparam`表示当前鼠标按键和键盘修饰键的状态. 常见的标志包括

- MK_LBUTTON
- MK_RBUTTON
- MK_MBUTTON
- MK_SHIFT
- MK_CONTROL
- MK_XBUTTON1
- MK_XBUTTON2

例如:

```cpp
case WM_MOUSEMOVE:
{
    if(wPara & MK_LBUTTON)
        ;// 鼠标移动过程中, 左键被按下
    if(wPara & MK_CONTROL)
        ;// 鼠标移动过程中, 右键被按下
}
```



`lParam`中保存了鼠标的位置, 位置坐标是相对于客户区左上角的.

- int x = GET_X_LPARAM(lPara);
- int y = GET_Y_LPARAM(lPara);

## 2. 应用场景

- **WM_MOUSEMOVE可以用来实现Hover效果**, 假设自己绘制一个按钮.
  - WM_MOUSEMOVE
  - 得到鼠标坐标(X, Y)
  - PtInRect()
  - 鼠标位于Button上
  - hover = true
  - InvaildateRect()
  - WM_PAINT
  - 绘制 Hover Button

- 使用WM_MOUSEMOVE实现拖动功能.

## 3. 练习

实现画线功能

使用WM_MOUSEMOVE && WM_LBUTTONDOWN && WM_LBUTTONUP 三个消息实现绘图中的画线功能

```cpp
LRESULT CALLBACK WindProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
    switch (msg)
	{
		case WM_LBUTTONDOWN:
			return OnLButtonnDown(hWnd, wPara, lPara);

		case WM_LBUTTONUP:
			return OnLButtonUp(hWnd, wPara, lPara);

		case WM_MOUSEMOVE:
			return OnMouseMove(hWnd, wPara, lPara);

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, msg, wPara, lPara);
	}
	return DefWindowProc(hWnd, msg, wPara, lPara);
}

bool g_drawing = false;   //用来保存当前是在画线
POINT g_lastPoint;    

LRESULT OnMouseMove(HWND hWnd, WPARAM wPara, LPARAM lPara)
{
	if (g_drawing && (wPara & MK_LBUTTON))
	{
		int x = GET_X_LPARAM(lPara);
		int y = GET_Y_LPARAM(lPara);

		HDC hdc = GetDC(hWnd);
		MoveToEx(hdc, g_lastPoint.x, g_lastPoint.y, NULL);
		LineTo(hdc, x, y);
		ReleaseDC(hWnd, hdc);
		g_lastPoint.x = x;
		g_lastPoint.y = y;
	}
	return DefWindowProc(hWnd, WM_MOUSEMOVE, wPara, lPara);
}

LRESULT OnLButtonUp(HWND hWnd, WPARAM wPara, LPARAM lPara)
{
	g_drawing = false;
	ReleaseCapture();

	return DefWindowProc(hWnd, WM_LBUTTONUP, wPara, lPara);
}

LRESULT OnLButtonDown(HWND hWnd, WPARAM wPara, LPARAM lPara)
{
	g_drawing = true;
	g_lastPoint = POINT{ GET_X_LPARAM(lPara), GET_Y_LPARAM(lPara) };
	SetCapture(hWnd);
	return DefWindowProc(hWnd, WM_LBUTTONDOWN, wPara, lPara);
}
```



介绍两个API函数 MoveToEx, 和 LineTo

```cpp
BOOL MoveToEx(
  HDC     hdc,       // 设备上下文句柄（画布）
  int     X,         // 目标位置的 X 坐标（逻辑单位）
  int     Y,         // 目标位置的 Y 坐标（逻辑单位）
  LPPOINT lpPoint    // 指向 POINT 结构的指针，用于接收上一个位置（可为 NULL）
);


BOOL LineTo(
  HDC hdc,    // 设备上下文句柄（画布）
  int nXEnd,  // 线段终点的 X 坐标（逻辑单位）
  int nYEnd   // 线段终点的 Y 坐标（逻辑单位）
);
```

`MoveToEx`和`LineTo`函数是专门用来配合画线的, 画线需要起点和终点, MoveToEx可以设置起点, LineTo中传入终点就可以画线了.缺陷是画出来的线条有锯齿状.