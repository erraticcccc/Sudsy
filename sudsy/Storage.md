This is the documentation for the features that the storage header has, including the classes and their methods.

Storage will likely be the biggest header within Sudsy until I bother to split its classes into their own files. It currently contains 5 different structs,
with a largely uncomplete Vec3, a relatively detailed but still somewhat lacking Vec2, a Color class, ScreenPos (which is just 2 Vec2's), and a VTX class, which is used
as a vertice.


```c
HYPOTENUSE(a,b)
```
	
	This is a macro that expands to sqrtf((a*a)+(b*b)), which returns the square root of the float sum of a and b squared individually.



```c
int _clmp(int to, int max, int min)
```

	Deceivingly, both this function and the next function do not clamp, but instead overflow the number. What this means is that if 
	"to" is greater than "max", to will not become max, but instead become "min". As an example, say that I do this:
	```c
	_clmp(43,25,1)
	```
	This will return 43-25 (18). It works recursively, so if 43 was instead 63 (which is greater than 25 * 2), it would do 63 - 25 (38), 
	see that its still greater than 25, then do it again (38 - 25, 13.)



```c
float _fclmp(float to, float max, float min)
```
	
	This works exactly the same as the one above, just with floats.



```c
std::vector<byte> capbytes(byte* loc, int amt)
```
	
	This function returns a vector of bytes given a location and amount.



```c
bool psrch(std::vector <byte> pat, byte* pile, int dist, int leniency)
```
	
	This function searches an array of bytes for a pattern with a given leniency. Leniency describes how many bytes it can be off
	before failing. This will at some point have a mask, or an alternative function will do the same but instead of leniency will
	only have a mask. Not sure yet.



```c
static void checkfunc() {} // used within fver
bool fver(byte* loc)
```
	
	This verifies that something is a function. Not even sure if it works, but it will be used for buttons.