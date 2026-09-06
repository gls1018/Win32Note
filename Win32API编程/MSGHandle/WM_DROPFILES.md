## 1. 消息来源

以下几种情况当用户拖拽文件到窗口上时会触发WM_DROPFILES消息.

- 在调用CreateWindowEx函数时设置了窗口扩展属性`WS_ACCEPTFILES`
- 调用了DragAcceptFiles函数.



## 2. 附带信息

- wParam:HDROP类型的指针
- lParam: 0





## 3. 自定义处理



处理`WM_DROPFILES`消息时,主要通过`DragQueryFile`函数来实现, 该函数既可以得到拖拽文件的数量,也可以得到每个文件的路径



```cpp
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wPara, LPARAM lPara)
{
    switch(uMsg)
    {
        case WM_DROPFILES:
		{
                HDROP hDrop = reinterpret_cast<HDROP>(wPara);
                //先查询一下文件的数量
                UINT uFileCount = DragQueryFile(hDrop, 0xFFFFFFFF, szFilePath, 0);
                for(UINT i=0; i<uFileCount; i++)
                {
                    DragQueryFile(hDrop, i, szFilePath, MAX_PATH);
                    //这里打印一下文件名
                    OutputDebugString((szFilePath));
                    memset(szFilePath, 0, MAX_PATH);
				}
                DragFinish(hDrop);
		}
	}
    return DefWindowProc(hWnd, uMsg, wPara, lPara);
}
```

补充:
`DragAcceptFiles`函数作用于`EDIT`控件,可以让用户拖拽文件到文本框.