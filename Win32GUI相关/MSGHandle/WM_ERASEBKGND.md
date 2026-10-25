### 1. 消息来源



### 2. 附带参数

- wParam: 用于擦除背景的HDC
- lParam: 未使用.

### 3. 自定义处理

自定义处理返回值:

- TRUE: 表示背景已擦除
- FALSE: 表示背景未擦除



#### 3.1 不擦除背景, 直接返回TRUE

这是Direct2D中常见的处理方式

```cpp
case WM_ERASEBKGND:
	return TRUE;
```

虽然没有执行实际的背景擦除操作, 但返回TRUE是为了告诉Windows, 不需要再执行默认背景擦除.

这样可以避免Windows先用GDI擦除背景, 然后Direct2D再绘制整个客户区.



上面这样处理需有一个前提, Direct在WM_PAINT消息中必须要完整绘制需要更新的客户区.

代码如下:

```cpp
case WM_PAINT:
{
    PAINTSTRUCT ps;
    HDC hDc = BeginPaint(hWnd, &ps);
    
    if(g_pHwndRenderTarget != nullptr)
    {
        g_pHwndRenderTarget->BeginDraw();
        g_pHwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
        
        // 绘制其它内容
        
        HRESULT hr = g_pHwndRenderTarget->EndDraw();
    }
    
    EndPaint(hWnd, &ps);
    return 0;
}
```

#### 3.2 使用GDI自定义擦除背景

假设希望窗口背景始终为浅蓝色.

```cpp
case WM_ERASEBKGND:
{
    
}
```



#### 3.3 交给DefWindowProc处理

```cpp
case WM_ERASEBKGND:
	return DefWindowProc(hWnd, msg, wParam, lParam);
```

