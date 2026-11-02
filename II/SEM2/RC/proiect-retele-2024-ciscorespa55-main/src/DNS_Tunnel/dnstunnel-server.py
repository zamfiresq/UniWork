import socket
from dnslib import DNSRecord, DNSHeader, RR, QTYPE, TXT
import base64
# importam bibliotecile de care avem nevoie: socket pt conexiuni, dnslib pentru a crea si analiza pachete DNS
# si base64 pt a codifica si decodifica datele in baza 64

# domeniul care va fi gestionat de serverul dns
domain = "ciscorespa55.com"
# adresa ip a serverului dns
SERVER_IP = "141.147.63.189"

# functie pentru a gestiona cererile dns primite
def handle_request(data, client_address, sock):
    try:
        # parsam cererea dns primita
        request = DNSRecord.parse(data)
        # obtinem numele complet al domeniului din cerere
        qname = str(request.q.qname)
        # cream un raspuns dns cu acelasi id ca si cererea si setam cateva flaguri
        reply = DNSRecord(DNSHeader(id=request.header.id, qr=1, aa=1, ra=1), q=request.q)

        # verificam daca cererea este pentru domeniul nostru
        if domain in qname:
            # extragem subdomeniul din numele complet al domeniului
            subdomain = qname.split('.')[0]
            # decodificam datele din subdomeniu folosind base32
            decoded_data = base64.b32decode(subdomain.replace('-', '='))

            # codificam raspunsul in base64 si adaugam un prefix
            response_data = base64.b64encode(b"Received: " + decoded_data).decode('utf-8')
            # adaugam raspunsul de tip txt la raspunsul dns
            reply.add_answer(RR(qname, QTYPE.TXT, rdata=TXT(response_data), ttl=60))

        # trimitem raspunsul inapoi clientului
        sock.sendto(reply.pack(), client_address)
    except Exception as e:
        print(f"Error handling request: {e}")

# functie principala pentru a porni serverul dns
def main():
    # cream un socket udp
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # legam socket-ul la toate interfetele de retea pe portul 53
    sock.bind(('0.0.0.0', 53))
    print("DNS Server running...")

    try:
        while True:
            # asteptam sa primim date de la clienti (512 octeti maxim)
            data, client_address = sock.recvfrom(512)
            # gestionam cererea primita
            handle_request(data, client_address, sock)
    except KeyboardInterrupt:
        # cand primim un semnal de intrerupere (Ctrl+C), inchidem serverul
        print("\nServer shutting down.")
    finally:
        # inchidem socket-ul
        sock.close()

# verificam daca scriptul este rulat direct
if __name__ == "__main__":
    main()
