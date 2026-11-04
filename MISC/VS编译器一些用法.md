### 0x1 编译优化相关



可以使用 `#pragma optimize("optimization-list", {on | off})` 来控制优化



- Optimization-list: 由特定字母组成的字符串, 用于指定要开启或关闭的优化类型.
  - g: 启用全局优化, 已被弃用
  - s: 生成更小的机器序列
  - t: 生成执行速度更快的机器码序列
  - y: 在程序栈上省略栈指针
- {on|off} : 用于开启或关闭

特殊用法, 当传入空字符串时

```
#pragma optimize("", off)
```

表示关闭所有优化.