# ANALIZATOR LEXICAL PENTRU C++


import re

# dictionar de tokens unde vom defini setul de expresii regulate
TOKEN_TYPES = {
    "PREPROCESSOR": r"#\s*\b[a-zA-Z_][a-zA-Z0-9_]*\b",  # preprocesor #include, #define, etc
    "STRING": r'"(?:[^"\\]|\\.|\\\n)*"',
    "HEADER": r"<[a-zA-Z0-9_.]+>|\"[^\"]+\"",  
    "KEYWORD": r"\b(alignas|alignof|and|and_eq|asm|auto|bitand|bitor|bool|break|case|catch|char|char16_t|char32_t|class|compl|const|constexpr|const_cast|continue|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|final|float|for|friend|goto|if|inline|int|long|main|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|register|reinterpret_cast|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq)\b",
    "IDENTIFIER": r"\b[a-zA-Z_][a-zA-Z0-9_]*\b",
    "SEPARATOR": r"[\(\)\{\}\[\];,:]",  
    "OPERATOR": r"(->|\+{1,2}|-{1,2}|==|!=|<=|>=|&&|\|\||::|<<|>>|[-+*/%=<>!&|.])", 
    "NUMBER": r"\b\d+(\.\d+)?\b",
    "CHAR": r"'.'",
    "COMMENT": r"(//.*|/\*[\s\S]*?\*/)"
}

def lexical_analyzer(input_file):
    with open(input_file, 'r') as file:
        content = file.read()
    
    current_line = 1
    current_position = 0
    tokens = []                             # lista pentru tokenii detectati
    in_preprocessor = False                 # flag pentru preprocesor

    while current_position < len(content):
        while current_position < len(content) and content[current_position].isspace():
            if content[current_position] == '\n':
                current_line += 1
                in_preprocessor = False     # resetare flag preprocesor la inceput de linie
            current_position += 1
        
        # sfarsitul fisierului
        if current_position >= len(content):
            break

        # cel mai lung token valid
        longest_token = None
        longest_token_type = None
        longest_token_length = 0

        for token_type, regex in TOKEN_TYPES.items():
            match = re.match(regex, content[current_position:])
            if match:
                token_length = len(match.group(0))
                if token_length > longest_token_length:
                    longest_token = match.group(0)
                    longest_token_type = token_type
                    longest_token_length = token_length

        if longest_token:
            # flag pentru preprocesor
            if longest_token_type == "PREPROCESSOR":
                in_preprocessor = True

            if longest_token_type == "STRING" and in_preprocessor:
                longest_token_type = "HEADER"
                in_preprocessor = False

            # salvare token
            tokens.append((longest_token, longest_token_type, longest_token_length, current_line, current_position))
            print(f"Token: {longest_token}, Type: {longest_token_type}, Line: {current_line}, Position: {current_position}")
            # avansare pointer cu lungimea tokenului
            current_position += longest_token_length
        else:
            # erorile lexicale
            error_char = content[current_position]
            print(f"Lexical error at line {current_line}, position {current_position}: Unexpected character '{error_char}'")
            tokens.append((error_char, "LEXICAL_ERROR", 1, current_line, current_position))
            current_position += 1  # Avansam pointerul pentru a nu intra in bucla infinita

    print("Lexical analysis completed.")
    return tokens



# ex fisier
filename = "/Users/alexandrazamfirescu/FPC/tema1/test1.cpp"
tokens = lexical_analyzer(filename)



# salvare fisier de output
with open("/Users/alexandrazamfirescu/FPC/tema1/output.txt", "w") as f:
    for token in tokens:
        f.write(f"{token[0]:<15} | {token[1]:<15} | Len: {token[2]:<3} | Line: {token[3]} | Pos: {token[4]}\n")

print("Tokens saved to output.txt")