
## 1. WM_SYSCOMMAND 消息何时产生

- 用户点击标题栏上的最大化、最小化和关闭按钮
- 用户鼠标点击标题栏.
- Alt + Space 呼出系统菜单栏.
- 点击菜单栏中的选项
- 从任务栏还原窗口 



## 2. WM_SYSCOMMAND 消息的附带信息

- 
  


验证代码:
```cpp

```


## 3. DefWindowProc 对该消息如何处理


### 3.1 关于 SC_CLOSE

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

## 4. WM_SYSCOMMAND 消息自定义处理


## 几个问题和注意点


1.  WM_SYSCOMMAND(SC_CLOSE) && WM_CLOSE 为什么要设计成两层? 

- WM_SYSCOMMAND(SC_CLOSE)是关闭意图
- WM_CLOSE 表达的是关闭请求.

  




## 总结

- `WM_SYSCOMMAND`是系统菜单和窗口控制行为的统一入口.
- 