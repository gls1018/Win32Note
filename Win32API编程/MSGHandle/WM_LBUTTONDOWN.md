## 1. 附带参数

wPara携带当前鼠标和键盘的按键状态, Windows定义了一些标志位.

- MK_LBUTTON    左键按下(此时肯定为`true`)
- MK_RBUTTON    右键按下
- MK_MBUTTON    中键按下
- MK_SHIFT      SHIFT按下
- MK_CONTROL    Control键按下

检测是否按下了 `Control`按键.

```cpp
LRESULT OnLBtnDown(HWND hWnd, WPARAM wPara, LPARAM lPara)
{
    if(wPara & MK_CONTROL)
        // 执行 Ctrl 加点击逻辑
}
```



lPara 携带了**当前鼠标的坐标**.

- 低16位是X坐标
- 高16位是Y坐标
- 这里坐标是客户区坐标, 相对于客户区左上角(0,0).

Windows系统设置了宏来获取坐标.

```cpp
int x = GET_X_LPARAM(lPara);
int y = GET_Y_LPARAM(lPara);
```



## 2. 自定义处理

