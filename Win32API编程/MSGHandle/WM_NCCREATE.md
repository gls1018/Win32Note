在调用`CreateWindow`或者`CreateWindowEx`时会产生该消息. 产生的顺序如下

- WM_NCCREATE
- WM_NCCALCSIZE
- WM_CREATE

附带信息

- wParam: 0
- lParam: 指向`CREATESTRUCT`结构体的指针.

自定义处理：

- 返回值必须为`TRUE`