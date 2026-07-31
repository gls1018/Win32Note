## 1. 前言

`WM_NCHITTEST`是Windows向程序询问鼠标命中了哪个区域的消息, 而应用程序通过返回不同的`HT*`值告诉操作系统如何处理后续的鼠标行为.



WM_NCHITTEST的应用场景:

- 无边框自定义拖动和缩放.
- 实现鼠标穿透







## 2. HTTRANSPARENT





