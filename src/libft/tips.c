## char *strcpy(char *dest, const char *src);

The strcpy() function copies the string pointed to by src, including the terminating null byte ('\0'), to the buffer pointed to by dest.  
	
	the strings may not overlap, and the destination string dest must be large enough to receive the copy.  Beware of buffer overruns! 

| __*src__   | A | B | \0 |   |    |
|------------|---|---|----|---|----|
|            | ↓ | ↓ | ↓  |   |    |
| __*dest__  | A | B | \0 |   |    |

__return *dest__

## char *strncpy(char *dest, const char *src, size_t n);

The strncpy() function is similar, except that at most n bytes of src are copied.  Warning: If there is no null byte among the first n  bytes of src, the string placed in dest will not be null-terminated.

	If the length of src is less than n, strncpy() writes additional null bytes to dest to ensure that a total of n bytes are written.


__size = 5__ 

| __*src__   | A | B | \0 |    |    |
|------------|---|---|----|----|----|
|            | ↓ | ↓ | ↓  | ↓  | ↓  |
| __*dest__  | A | B | \0 | \0 | \0 |

__return *dest__

---

__size = 3__ 

| __*src__   | A | B | C  | D  | \0 |
|------------|---|---|----|----|----|
|            | ↓ | ↓ | ↓  |    |    |
| __*dest__  | A | B | C  |    |    |

__return *dest__

	the string placed in dest is not be null-terminated


## void	*ft_memcpy(void *dest, const void *src, size_t n)

The  memcpy()  function copies  n bytes from memory area src to memory area dest. The memory areas must not overlap.  Use memmove(3) if the memory areas do overlap.

__n = 3__ 

| __*src__   | A | B | C | D |
|------------|---|---|---|---|
|            | ↓ | ↓ | ↓ |   |
| __*dest__  | A | B | C |   |

__return *dest__

## size_t	ft_strlcpy(char *dst, const char *src, size_t size)

The strlcpy() function copies up to size - 1 characters from the NUL-terminated string src to dst, NUL-terminating the result

__size = 3__ 

| __*src__   | A | B | C  | D  | \0 |
|------------|---|---|----|----|----|
|            | ↓ | ↓ | ↓  |    |    |
| __*dest__  | A | B | \0 |    |    |

__return = 4 (len of src)__

---

__size = 10__ 

| __*src__   | A | B | \0 |   |    |
|------------|---|---|----|---|----|
|            | ↓ | ↓ | ↓  |   |    |
| __*dest__  | A | B | \0 |   |    |

__return = 2 (len of src)__

