# Thompson VM Lexer #

## Specificatons ##
This lexical analysis engine:
1. Matches prefixes of the input.
2. Matches multiple patterns at once.
3. Picks the pattern that matches the longest prefix.
4. Breaks ties by picking the pattern that appears earliest in the user supplied list of patterns.