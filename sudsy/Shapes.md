This is the documentation for the features that the shapes header has, including the classes and their methods.

Shapes are generally intended to be used to add decoration, color, and shape (duh) to other objects, such as buttons or windows.
They can act on their own, obviously.

Shape struct (virtual)
	Type GetType()
	void Draw()
	void SetColor(const Color &color)
	void SetThickness(float thickness)
	void SetFilled(bool filled)
	float Area()

```c
Type GetType() //
```
	
	A function that will return the shapes Type, an enum. This enum is defined in Sudject.h, and can be one of four things:
		S_TEXT,
		S_SHAPE,
		S_WINDOW,
		S_BUTTON
	There is a chance this will be removed.



```c
void Draw() //
```
	
	The main shapes drawing function. Its unlikely this will ever be something you need to manually call.
	


```c
void SetColor(const Color &color) //
```
	
	This will set the color of the shape.



```c
void SetThickness(float thickness) //
```

	Likely to be removed, but will likely set thickness of shapes _outline_.



```c
void SetFilled(bool filled) // 
```
	
	Will determine if a shape is drawn filled or outline.



```c
float Area() //
```
	
	This will return a shapes area.