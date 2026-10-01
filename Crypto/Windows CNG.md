## 1. CNG

Cryptography Next Generation(CNG)



主要提供下面功能；

- Hash
- Symmetric Encryption
- Asymmetric Cryptography
- Digital Signature
- Random Number
- Key Management







## 2. Random Number

下面代码生成 32位和64位随机数.

使用到的API:

- BCryptGenRandom

```cpp
int main()
{
	uint32_t value32{};
	uint64_t value64{};
	NTSTATUS status32 = BCryptGenRandom(NULL, (UCHAR*)&value32, sizeof(value32), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
	NTSTATUS status64 = BCryptGenRandom(NULL, (UCHAR*)&value64, sizeof(value64), BCRYPT_USE_SYSTEM_PREFERRED_RNG);

	if (!BCRYPT_SUCCESS(status32) && !BCRYPT_SUCCESS(status64))
		return -1;
	std::print("0x{:0>8X}\n", value32);
	std::print("0x{:0>16X}\n", value64);
	return 0;
}
```

其实就是往pBuffer中随机填充字节.



