## 1. API集合



- CreateMenu 创建菜单栏 Menu Bar
- CreatePopMenu  创建弹出菜单
- DestroyMeny 销毁菜单
- SetMenu 把菜单设置给窗口
- GetMenu 获取窗口菜单句柄
- DrawMenuBar 动态更新菜单后,重新绘制菜单栏
- AppendMenu 向菜单末尾添加菜单项
- InsertMenu 在指定位置插入菜单项
- InsertMenuItem 插入菜单项的增强版本, 功能更加现代
- ModifyMenu 修改已有菜单项
- SetMenuItemInfo 修改菜单项的增强版本, 功能更加现代
- GetMenuItemInfo 获取菜单项信息
- GetMenuItemCount 获取菜单项数量
- GetMenuItemID 根据菜单项位置获取ID
- GetMenuItemRect 获取菜单项在屏幕上的矩形区域
- RemoveMenu 删除菜单项
- DeleteMenu 删除菜单项，同时删除子菜单
- EnableMenuItem 启用菜单项
- CheckMenuItem 设置菜单项为选中状态
- CheckMenuRadioItem 用于实现单选菜单项





## 1. 创建菜单

### 1.1 CreateMenu

```cpp
HMENU CreateMenu(void);
```
创建一个标准菜单(Menu Bar Menu)，通常用于窗口顶部的菜单栏(Menu Bar)




### 1.2 CreatePopMenu

```cpp
HMENU CreatePopupMenu(void);
```

用途:
- DropDown Menu 下拉菜单
- SubMenu 子菜单
- Shortcut Menu / Context Menu / Right Click Menu  右键菜单  



### 1.3 TrackPopupMenu



### 1.4 TrackPopupMenuEx





## 2. 添加菜单项

### 2.1 AppendMenu

用于在指定的菜单末尾添加一个新的菜单项.

```cpp
BOOL AppendMenuA(
  [in]           HMENU    hMenu,
  [in]           UINT     uFlags,
  [in]           UINT_PTR uIDNewItem,
  [in, optional] LPCSTR   lpNewItem
)
```

- hMenu: 要操作的菜单句柄。可以是顶层菜单或子菜单的句柄。
- uFlags: 控制菜单项的外观和行为，常用组合见下文
  - MF_STRING:  最常用，表示菜单项显示文本（`lpNewItem` 为字符串）
  - MF_POPUP:  表示该项是一个子菜单（`uIDNewItem` 传入子菜单的 `HMENU`)
  - MF_SEPARATOR: 添加一条分割线（此时 `uIDNewItem` 和 `lpNewItem` 被忽略）
  - MF_CHECKED:  在项前面显示对勾 ✔
  - MF_UNCHECKED:  取消对勾（默认）
  - MF_GRAYED:  禁用并灰显该项，不可点击
  - MF_DISABLED: 禁用但不灰显（很少单独使用）
  - MF_ENABLED: 启用（默认）
  - MF_BYCOMMAND: 通过命令 ID 定位(默认，通常不显式写)
  - MF_BYPOSITION： 通过位置索引定位（不常用）
- uIdNewItem: 菜单项的标识符（ID）。当用户点击时，Windows 会通过 `WM_COMMAND` 消息返回此 ID。如果是子菜单，则此处为子菜单句柄。
- lpNewItem: 菜单项的显示文本（字符串）。如果设置了 `MF_BITMAP` 或 `MF_OWNERDRAW`，则含义不同

### 2.2 InsertMenu

```cpp

```


### 2.3 InsertMenuItem

```cpp
BOOL InsertMenuItemA(
  [in] HMENU            hmenu,
  [in] UINT             item,
  [in] BOOL             fByPosition,
  [in] LPCMENUITEMINFOA lpmi
);
```


- hmenu: 菜单句柄, CreateMenu或者CreatePopUpMenu的返回值
- item:  插入的位置. 当 fByPosition 为 TRUE时.
  - -1: 表示在尾部添加Item
  - 0: 表示在最前面插入.
- fByPosition: 
    - TRUEL: item的数字表示菜单项的插入位置.
- LPMENUITEMINFO: `MENUITEMINFO`结构体指针, 控制菜单项的所有属性.



### 2.4 MENUITEMINFO 结构体

**`MENUITEMINFO结构体` 是菜单项的完整描述对象.**

```cpp
typedef struct tagMENUITEMINFOA {
  UINT      cbSize;
  UINT      fMask;
  UINT      fType;
  UINT      fState;
  UINT      wID;
  HMENU     hSubMenu;
  HBITMAP   hbmpChecked;
  HBITMAP   hbmpUnchecked;
  ULONG_PTR dwItemData;
  LPSTR     dwTypeData;
  UINT      cch;
  HBITMAP   hbmpItem;
} MENUITEMINFOA, *LPMENUITEMINFOA;
```

- cbSize: 始终设置为 `sizeof(mii)`;
- fMask: 它的值决定了MENUITEMINFO结构体哪些成员有效. 



#### 2.4.1 关于 fMask 的解释

Win32插入菜单项函数`InsertMenuItem(hMenu, pos, TRUE, &mii)`; 
系统在拿到MENUITEMINFO后, 它怎么知道你设置了哪些字段? 哪些是垃圾值? 答案是完全依赖 `fMask`.

常用 fMask 标志:

**1. `MIIM_ID`**

启用 `wID` 字段. 表示菜单项有ID
```cpp
mii.fMask = MIIM_ID;
mii.wId = IDM_ID;
```

- 点击此菜单项, 发送 WM_COMMAND 消息.
- `LOWORD(wParam) == wId`, 触发对应逻辑代码.


**2. MIIM_STRING**

启用 `dwTypeData` 字段, 表示这个菜单项有文本. 
```cpp
mii.fMask = MIIM_STRING;
mii.dwTypeData = L"Open File"; 
```


**3. MIIM_STATE**

启用 `fState` 字段. 用于控制菜单项的状态.

```cpp
mii.fMask = MIIM_STATE;
mii.fState = MFS_DISABLED;
```

- MFS_ENABLED : 可用
- MFS_DISABLED : 灰色
- MFS_CHECKED: 勾选 √

**4. MIIM_SUBMENU**

启用 `hSubMenu`字段, 表示这是一个有子菜单的项.

```cpp
mii.fMask = MIIM_SUBMENU;
mii.hSubMenu = hSubMenu;
```

**4. MIIM_FTYPE**


#### MENUITEMINFO 的常用组合

**普通菜单项**

```cpp
mii.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE; 
```

**分隔符**
```cpp
mii.fMask = MIIM_FTYPE;
mii.fType = MFT_SEPRATOR;
```

**子菜单**

```cpp
mii.fMask = MIIM_SUBMENU | MIIM_STRING;
mii.hSubeMenu = hSubMenu;
```

**带数据菜单**

```cpp
mii.fMask = MIIM_ID | MIIM_STRING | MIIM_DATA;
```

### 3个菜单添加函数有什么不同?


- AppendMenu是InsertMenu的一种特例.
- AppendMenu能实现的效果, InsertMenu都能实现.
- InsertMenuItem是InsertMenu的增强版. 所有InsertMenu能实现的功能, InsertMenuItem都能实现.

## 









## 代码