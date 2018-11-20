# get_next_line_v2

  get_next_line is a function that returns a line read from a file descriptor. What we call a “line” is a succession of characters that end with ’\n’ (ascii code 0x0a) or with End Of File (EOF).

  It's prototype:
```int get_next_line(const int fd, char **line);```

• The first parameter is the file descriptor that will be used to read.

• The second parameter is the address of a pointer to a character that will be used

to save the line read from the file descriptor.

• The return value can be 1, 0 or -1 depending on whether a line has been read,
when the reading has been completed, or if an error has happened respectively.


  Function get_next_line returns its result without ’\n’. Calling get_next_line in a loop will then allow you to read the text
available on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.

  In header file get_next_line.h there is a prototype of the function get_next_line and a macro BUFF_SIZE that allows to choose the size of the reading buffer for the read function. It also contains a macro DELIM defining a delimiter character ('\n' by default).
  
  get_next_line is also able to manage multiple file descriptors. For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors.
