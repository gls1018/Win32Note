## 1. 附带信息

wParam 里面是窗口产生WM_SIZE的原因， 包含以下几个宏

- SIZE_RESTORED
  - 从最小化恢复
  - 从最大化恢复
  - 拖动窗口边框调节大小
- SIZE_MINIMIZED
  - 最小化
- SIZE_MAXIMIZED
  - 最大化
- SIZE_MAXSHOW
- SIZE_MAXHIDE

SIZE_MAXSHOW和SIZE_MAXHIDE暂时还不知道怎么触发.





lParam 是窗口发生变化后的客户区大小. 低16位是客户区宽度, 高16位是客户区高度.

- LOWORD(lParam) 客户区宽度
- HIWORD(lParam) 客户区高度





## 2. 自定义处理

- 返回值: 自定义处理后,需要返回0.



WM_SIZE的核心作用是, 在主窗口大小发生变化时, 用来调整子控件大小和重新调整布局.

假设窗口有一个Edit控件.

```cpp
case WM_SIZE:
{
    int width  = LOWORD(lParam);
    int height = HIWORD(lParam);

    MoveWindow(
        hEdit,
        0,
        0,
        width,
        height,
        TRUE
    );
    break;
}
```

通过`MoveWindow`函数来重新调整Edit的大小和位置.