import socket
from dnslib import DNSRecord, DNSHeader, RR, QTYPE, TXT
import base64
import os

# domeniul care va fi gestionat de serverul dns
domain = "ciscorespa55.com"
# adresa ip a serverului dns
SERVER_IP = "141.147.63.189"
CHUNK_SIZE = 255  # dimensiune mica de bucata din fisier trimisa in fiecare pachet pentru a evita fragmentarea

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
            filename = subdomain + ".txt"  # nume fisier

            # verificam daca fisierul exista
            if os.path.exists(filename):
                with open(filename, 'rb') as file:
                    file_data = file.read()
                    # impartim fisierul in bucati de CHUNK_SIZE
                    chunks = [file_data[i:i+CHUNK_SIZE] for i in range(0, len(file_data), CHUNK_SIZE)]
                    
                    for i, chunk in enumerate(chunks):
                        # codificam fiecare bucata in base64
                        response_data = base64.b64encode(chunk).decode('utf-8')
                        # adaugam raspunsul de tip txt la raspunsul dns
                        reply.add_answer(RR(qname, QTYPE.TXT, rdata=TXT(response_data), ttl=60))
                        
                        # trimitem raspunsul inapoi clientului
                        sock.sendto(reply.pack(), client_address)
                        # asteptam confirmarea inainte de a trimite urmatoare bucata
                        ack_data, _ = sock.recvfrom(512)
                        ack = DNSRecord.parse(ack_data)
                        if str(ack.q.qname) != f"ack.{subdomain}.{domain}.":
                            break

        else:
            # raspundem cu un mesaj de cerere invalida
            response_data = base64.b64encode(b"Invalid request").decode('utf-8')
            reply.add_answer(RR(qname, QTYPE.TXT, rdata=TXT(response_data), ttl=60))
            sock.sendto(reply.pack(), client_address)
    except Exception as e:
        # in cazul unei erori, afisam mesajul de eroare
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
