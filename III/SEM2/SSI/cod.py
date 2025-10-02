import secrets
import string

# 1
def generate_secure_password(length):
    if length < 10:
        raise ValueError("Password length should be at least 10 characters.")
    
    characters = (
        string.ascii_letters +  # a-zA-Z
        string.digits +  # 0-9
        string.punctuation  # !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
    )

    while True:
        password = ''.join(secrets.choice(characters) for _ in range(length))
        if (any(c.islower() for c in password) and
            any(c.isupper() for c in password) and
            any(c.isdigit() for c in password) and
            any(c in string.punctuation for c in password)):
            return password
        
# Exemplu de utilizare
# Generarea unei parole sigure intr-o aplicatie de autentificare 



# 2
def generate_url_token(length):
    if length < 32:
        raise ValueError("Token length should be at least 32 characters.")
    return secrets.token_urlsafe(length)

# Exemplu de utilizare
# Token pentru resetarea unei parole, trimisa prin link in email




# 3
def generate_hex_token(length):
    if length < 32:
        raise ValueError("Token length should be at least 32 characters.")
    
    return secrets.token_hex(length)

# Exemplu de utilizare
# Token pentru autentificare API intre microservicii



# 4
def compare_tokens(token1, token2):
    return secrets.compare_digest(token1, token2)



# 5
def generate_binary_key(length=100):
    return secrets.token_bytes(length)



# 6
import bcrypt

def hash_password(password: str) -> bytes:
    salt = bcrypt.gensalt()
    hashed = bcrypt.hashpw(password.encode('utf-8'), salt)
    return hashed

# Alegere bcrypt:
# Ofera protectie impotriva brute-force si este standardizat dpdv industrial





# TESTARE
if __name__ == "__main__":
    # testare generare parola
    try:
        password = generate_secure_password(12)
        print(f"Parola generata: {password}")
    except ValueError as e:
        print(e)
    print('\n')

    # testare generare token URL
    try:
        url_token = generate_url_token(32)
        print(f"Token URL generat: {url_token}")
    except ValueError as e:
        print(e)
    print('\n')

    # testare generare token hex
    try:
        hex_token = generate_hex_token(32)
        print(f"Token hex generat: {hex_token}")
    except ValueError as e:
        print(e)
    print('\n')

    # testare comparare tokenuri
    token1 = generate_url_token(32)
    token2 = generate_url_token(32)
    are_equal = compare_tokens(token1, token2)
    print(f"Tokenurile sunt egale: {are_equal}")
    print('\n')

    # testare generare cheie binara
    binary_key = generate_binary_key(100)
    print(f"Cheie binara generata: {binary_key}")
    print('\n')

    # testare hash parola
    password = "parola_secreta"
    hashed_password = hash_password(password)
    print(f"Parola hashuita: {hashed_password}")
    print('\n')

