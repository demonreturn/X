

#ifdef EX_EXPORTS
#define EX_API __declspec(dllexport)
#else
#define EX_API __declspec(dllimport)
#endif

#ifndef EX_BIT_ENABLED
	#define EX_BIT_ENABLED( dword, bit ) ( ((dword) & (bit)) != 0 )
#endif

/* 检查某bit的值是否与<mask>相等 */
#ifndef EX_BIT_CMP_MASK
	#define EX_BIT_CMP_MASK( dword, bit, mask ) ( ((dword) & (bit)) == mask )
#endif	// SC_BIT_CMP_MASK