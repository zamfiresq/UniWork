import socket
from dnslib import DNSRecord, DNSHeader, RR, QTYPE, A

# configurarea domeniilor și adresele IP asociate
DOMAIN = "ciscorespa55.com"
SUBDOMAIN = "sub.ciscorespa55.com"

# adresele IP care vor fi returnate pentru domenii
DOMAIN_IP = "141.147.63.189"
SUBDOMAIN_IP = "141.147.63.190"

def handle_request(data, client_address, sock):
    # parsam cererea DNS primita
    request = DNSRecord.parse(data)
    # obtinem numele domeniului din cerere
    qname = str(request.q.qname)

    # cream raspunsul DNS cu acelasi ID ca si cererea si setam cateva flaguri
    reply = DNSRecord(DNSHeader(id=request.header.id, qr=1, aa=1, ra=1), q=request.q)

    # verificam daca cererea este pentru DOMAIN
    if qname == DOMAIN + ".":
        # adaugam un raspuns cu adresa IP pentru DOMAIN
        reply.add_answer(RR(qname, QTYPE.A, rdata=A(DOMAIN_IP), ttl=60))
    # verificam daca cererea este pentru SUBDOMAIN
    elif qname == SUBDOMAIN + ".":
        # adaugam un raspuns cu adresa IP pentru SUBDOMAIN
        reply.add_answer(RR(qname, QTYPE.A, rdata=A(SUBDOMAIN_IP), ttl=60))

    # trimitem raspunsul inapoi clientului
    sock.sendto(reply.pack(), client_address)

def main():
    # cream un socket UDP
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

if __name__ == "__main__":
    main()

