## 1. 介绍

`WM_NCHITTEST`是Windows向程序询问鼠标命中了哪个区域的消息, 而应用程序通过返回不同的`HT*`值告诉操作系统如何处理后续的鼠标行为.



WM_NCHITTEST的应用场景:

- 无边框自定义拖动和缩放.
- 实现鼠标穿透



处理该消息时,需要返回命中测试码(Hit-Test-Codes).

- HTCLIENT       客户区
- HTCAPTION      标题栏
- HTSYSMENU      菜单栏
- HTMAXBUTTON    最大化
- HTMINBUTTON    最小化
- HTCLOSE        关闭
- HTTOP          上边框
- HTBOTTOM       下边框
- HTLEFT         左边框
- HTRIGHT        右边框
- HTTOPLEFT      左上角
- HTTOPRIGHT     右上角
- HTBOTTOMRIGHT  右下角
- HTBOTTOMLEFT   左下角

## 2. 触发时机

- 鼠标在窗口区域内移动
- 鼠标按下或者释放按键
- 鼠标进入或者离开窗口
- 窗口被最大化或者最小化, 还原或者移动时.



WM_NCHITTEST消息的触发频率非常高. 对该消息的处理逻辑必须快, 否则造成界面卡顿.



## 3. 附带消息

- wPara: 固定为0, 无实际用途.
- lPara: 鼠标的屏幕坐标, 低16位是X坐标, 高16位是Y坐标
  - X = GET_X_LPARAM
  - Y = GET_Y_LPARAM



## 4. 默认处理(DefWindowProc)

DefWindowProc会根据鼠标的屏幕坐标, 计算出鼠标在窗口上的坐标.

然后根据其相对于窗口边框、标题栏、菜单的距离, 返回相应的**HT***值



## 5. 自定义处理

