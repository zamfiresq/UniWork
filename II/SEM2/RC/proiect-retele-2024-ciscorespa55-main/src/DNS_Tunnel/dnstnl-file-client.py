import socket
import base64
from dnslib import DNSRecord, DNSQuestion, QTYPE
import hashlib

# adresa ip a serverului dns
server = "141.147.63.189"
# domeniul care va fi gestionat de serverul dns
domain = "ciscorespa55.com"

# functie pentru a trimite o cerere dns si a primi un raspuns
def send_query(query_name):
    # cream un obiect DNSQuestion cu numele query-ului si tipul TXT
    question = DNSQuestion(query_name, QTYPE.TXT)
    # cream un obiect DNSRecord care contine intrebarea
    request = DNSRecord(q=question)
    # trimitem cererea dns catre serverul specificat pe portul 53
    response = request.send(server, 53, tcp=False)
    # parsam raspunsul primit de la server
    reply = DNSRecord.parse(response)
    return reply

# functie pentru a cere un fisier si a-l salva local
def request_file(filename):
    # initializam un buffer pentru a stoca datele fisierului
    file_data = b""
    # obtinem numele subdomeniului din numele fisierului
    subdomain = filename.split('.')[0]
    # cream numele de query folosind subdomeniul si domeniul
    query_name = f"{subdomain}.{domain}"
    
    while True:
        # trimitem cererea dns si primim raspunsul
        reply = send_query(query_name)
        if reply.rr:
            for answer in reply.rr:
                # decodificam fiecare bucata din raspunsul de tip TXT
                chunk = base64.b64decode(str(answer.rdata))
                # adaugam bucata la bufferul de date al fisierului
                file_data += chunk
                # trimitem confirmarea pentru fiecare bucata primita
                ack_name = f"ack.{subdomain}.{domain}"
                send_query(ack_name)
        else:
            break
    
    # scriem datele primite intr-un fisier local
    with open(f"received_{filename}", 'wb') as file:
        file.write(file_data)
    
    return file_data

# functie pentru a calcula md5 checksum al fisierului primit
def calculate_md5(data):
    # cream un obiect hash md5
    md5 = hashlib.md5()
    # actualizam hash-ul cu datele fisierului
    md5.update(data)
    # returnam checksum-ul in format hexazecimal
    return md5.hexdigest()

# functie principala pentru a trimite cererea de fisier si a afisa checksum-ul
def main():
    # numele fisierului de cerut
    filename = "fisier"
    # cerem fisierul de la server
    file_data = request_file(filename)
    # calculam checksum-ul md5 al fisierului primit
    checksum = calculate_md5(file_data)
    # afisam checksum-ul
    print(f"MD5 Checksum: {checksum}")

# verificam daca scriptul este rulat direct
if __name__ == "__main__":
    main()
