

#ifdef EX_EXPORTS
#define EX_API __declspec(dllexport)
#else
#define EX_API __declspec(dllimport)
#endif