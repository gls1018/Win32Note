### 1. ID2D1Factory

ID2D1Factory是D2D的入口点接口, 用于创建渲染目标, 几何图形, 绘图状态块等核心绘图资源.



1. 渲染目标(Render target)

- CreateHwndTarget
- CreateDCRenderTarget
- CreateWicBitmapRenderTarget





2. 几何图形(Geometry)

- CreateEllipseGeometry
- 





### 2. ComPtr



画刷:

- ID2D1SolidColorBrush
- ID2D1LinearGradientBrush
- ID2D1RadicalGradientBrush
- ID2D1BitmapBrush







#### ID2D1SolidColorBrush

#### ID2D1LinearGradientBrush



使用渐变ID2D1LinearGradientBrush 时, 先定义渐变颜色, 再定义渐变方向.





#### ID2D1RadicalGradientBrush





