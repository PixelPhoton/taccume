# silly esolang thingy, kinda like brainfuck!

## build instructions:
run `sh build.sh`, executable should be in `./build/silly_esolang`

## usage:
`silly_esolang <file_to_interpret>`

## how it works:
theres an array of 1024 bytes
### two pointers:
- byte pointer, points to one byte of that array
- code pointer, points to a character in the code

### instructions:
- `>` moves the byte pointer one to the right, if it goes above 1023 then it just loops back to 0
- `<` move the byte pointer one to the left, if it goes below 0 it loops back to 1023
- `+` adds one to the byte at the byte pointer
- `-` subtracts one from the byte at the byte pointer
- `[` moves the code pointer to the right by the amount in the byte at the byte pointer (skipped if thats 0), also it wraps to 0 if it reaches the end of the code
- `]` is the same but to the left, wrapping to the end of the code if it reaches 0
- `.` outputs the current byte as an ASCII char
- `,` gets a char from stdin and puts it into the current byte
- `;` ends the program
- any other characters are simply ignored.

you may see examples in the examples folder!
