# taccume, silly esolang thingy, almost kinda like brainfuck! (but extended and kinda funky)
pronounciation: up to u :3

## build instructions:
run `sh build.sh`, executable should be in `./build/taccume`

## design goal:
as you many know, esolangs aren't designed to be practical, but rather for some other reason.<br>
this esolang was semi-inspired by brainfuck, and initially, was made to not need to keep track of [] cus i was lazy :3<br>
but then I decided, I also wanted to make it easier to use and less tedious for certain things (like printing strings or comparing/manipulating values)

## usage:
`taccume <file_to_interpret>`

## how it works:
there's an array of values, the tape. *(in this implementation, each value is 32-bit signed, and there are 2048 values)*<br>
there's an accumulator, which can be accessed at any time but only holds one value, *(in this implementation, 32-bit signed)*<br>
and there's the code, which must be made up of only ASCII characters.<br>
<br>
also, two pointers: 
- tape pointer, points to a value on the tape
- code pointer, points to a character in the code

### commands:
- `>` moves the tape pointer one to the right, if it goes above 1023 then it just loops back to 0
- `<` move the tape pointer one to the left, if it goes below 0 it loops back to 1023
- `+` adds one to the value at the tape pointer
- `-` subtracts one from the value at the tape pointer
- `^` sends the value at the tape pointer to the accumulator
- `v` puts the value in the accumulator in the tape pointer's current location
- '!' if the accumulator != 0, sets the accumulator to 0, otherwise, sets the accumulator to 1
- '=' if the accumulator and the value at the tape pointer are the same, the accumulator is set to 1, otherwise, 0
- '#' puts the current location on the tape into the acuumulator
- `[` if the accumulator != 0, moves the code pointer to the right by the amount in the value at the tape pointer (skipped if thats 0), also it wraps to 0 if it reaches the end of the code
- `]` same as above but to the left, wrapping to the end of the code if it reaches 0
- `T` similar to above, except it moves to the left if accumulator == 0 and to the right otherwise
- `)` if the code pointer is moving to the right, flips its direction unless accumulator == 0
- `(` same as above, but only if moving to the left
- `|` same as above, but doesn't depend on direction
- `*` outputs the value at the tape pointer as an integer
- `.` outputs the value at the tape pointer as an ASCII char
- `,` gets a char from stdin and puts it where the tape pointer currently is
- `_` becomes the value in the accumulator (mod 256) as an ASCII character (which can be executed)
- `s` subtracts the value in the accumulator from the value at the tape pointer
- 'a' adds the value in the accumulator to the value at the tape pointer
- 'm' multiplies the value at the tape pointer by the value in the accumulator
- 'd' divides the value at the tape pointer by the value in the accumulator
-  '  puts the following character into the tape at the tape pointer, and skips running its associated command
-  "  until reaching another ", doesn't run any commands it encounters, and outputs every character it passes
- `;` ends the program
- ':' ends the program only if the accumulator != 0
- any other characters are simply ignored.
<br>
you may see examples in the examples folder!<br>
<br>
<br>
<br>
... i made this cus I was bored, I don't even know why i put so many commands in it
