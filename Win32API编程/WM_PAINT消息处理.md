## 1. 消息来源

- 窗口第一次显示, 调用UpdateWindow之后.
- 窗口大小发生变化. 
- 

## 2. 附带信息



## 3. 自定义处理



## 4. 几个API函数



### 4.1 InvalidateRect

该函数的作用是将窗口客户区的指定区域标记为无效, 触发系统在合适的时候发送WM_PAINT消息来重绘该区域.

```cpp
BOOL InvalidateRect(
    HWND      hWnd,      // 窗口句柄
    CONST RECT *lpRect,  // 指向RECT结构体的指针，指定无效区域
    BOOL      bErase     // 是否擦除背景
);
```

- hWnd:
- lpRect: 传入NULL, 表示整个客户区都无效. 如果传入的区域超过了客户区, 会自动裁剪到客户区大小. RECT的坐标是相对于客户区左上角(0,0).

- 返回值: 成功返回TRUE, 失败返回FALSE. 