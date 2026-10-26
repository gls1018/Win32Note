### 1. ComPtr

`ComPtr`是一个 COM 智能指针模板类.

它通过自动调用 COM 对象的 `AddRef()` 和 `Release()` 来管理对象的引用计数.

减少内存泄漏、重复释放等问题. 

```cpp
#include <wrl/client.h>

using namepace Microsoft::WRL::ComPtr
```



### 2. 内部实现

 `Microsoft::WRL::ComPtr`

```cpp
template <typename InterfaceType>
class ComPtr
{
    private:
    	InterfaceType * ptr_     // COM接口指针  
}
```



#### 2.1 构造函数

- ComPtr()                                            
- ComPtr(const ComPtr& other)

```cpp
ComPtr() : ptr_(nullptr)
{
}

ComPtr(const ComPtr& other) : ptr_(other.ptr_)
{   
    InternalAddRef();  // 增加引用计数
}
```



#### 2.2 引用计数

- InternalAddRef
- InternalRelease

```cpp
void InternalAddRef() const 
{
    if(ptr_ != nullptr)
        ptr_->AddRef();           // 调用 IUnknown.AddRef() 方法
}

unsigned long InternalRelease()
{
    unsigned long ref = 0;
    T *temp = ptr_;
    if(temp != nullptr) 
    {
        ptr_ = nullptr;
        ref = temp->Release();     // 调用 IUnknown.Release() 方法
    }
    return ref;
}
```



#### 2.3 析构函数



#### 2.4 暴露的接口

- Get()
- GetAddressOf()
- ReleaseAndGetAddressOf()

```cpp
InterfaceType* Get() const 
{
    return ptr_;
}

InterfaceType** GetAddressOf() const 
{
    return &ptr_;
}

InterfaceType** ReleaseAndGetAddressOf()
{
    InternalRelease();
    return &ptr_;
}
```

`Get()` 返回一级指针. 

`GetAddressOf()`返回二级指针.

`ReleaseAndGetAddressOf()`

### 3. 示例

```cpp
using Mircosoft::WRL::ComPtr;
ComPtr<ID2D1Factory> pFactory;
Comptr<ID2D1HwndRenderTarget> pHwndRenderTarget;
```

