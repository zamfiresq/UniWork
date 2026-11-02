import socket
import time
import struct
import requests
import argparse
# folosim aceste librarii pentru interfata de retea si comunicare prin socket uri,
# latenta(time) si generarea de pachete pe care le vom transmite(struct)
# import requests pentru cererea http
# argparse pentru parsarea argumentului scriptului din terminal
# facem functie pentru a apela api-ul ip-api pentru geolocatia fiecarui ip

def geo(ip):
    url = f"http://ip-api.com/json/{ip}"
    response = requests.get(url)

    if response.status_code == 200:
        data = response.json()
        if data['status'] == 'success':
            return {
                'ip': data['query'],
                'country': data['country'],
                'city': data['city'],
            }
        else:
            return {'error': 'IP not found'}
    else:
        return {'error': 'Failed...'}


def main():

    parser = argparse.ArgumentParser(description="Traceroute script with geolocation")
    parser.add_argument('host', help="Host to traceroute")
    args = parser.parse_args()

    # host-ul este acum un argument din linia de comandă
    host = args.host

    timeout = 3 # timp de asteptare pentru fiecare pachet
    port = 33434 #port destinatie pentru pachetele UDP, (port arbitrar, folosit de regula in UDP)

    # in variabilele ICMP si UDP definim protocoalele pe care le vom folosi pe socket (obinem numerele protocoalelor)
    #UDP - user datagram protocol - prin acesta se vor trimite pachetele
    #ICMP - internet control message protocol - pachetele de raspuns trimise de noduri(routere)
    ICMP = socket.getprotobyname('icmp')
    UDP = socket.getprotobyname('udp')

    #creem 2 obiecte de tip socket raw si setam fiecaruia cate un protocol (icmp si udp)
    icmp_sock = socket.socket(socket.AF_INET, socket.SOCK_RAW, ICMP)
    udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, UDP)
    # AF_INET - adrese IPV4, SOCK_RAW si SOCK_DGRAM indica tipurile socket-urilor, iar ultimul parametru reprezinta protocolul
    # SOCK_RAW - socket pt pachetele brute folosite de ICMP 
    # SOCK_DGRAM - socket pt pachete de tip datagram folosite de UPD

    timeout_struct = struct.pack('ll', timeout, 0)
    icmp_sock.bind(("", port)) # binding the ICMP protocol to the port.
    icmp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVTIMEO, timeout_struct)

    #ttl = time to live = se initializeaza cu 1 si se va incrementa la fiecare nod(router)

    dest_addr = socket.gethostbyname(host)
    ttl = 1
    # salvam in geo_data 
    geo_data = geo(dest_addr)

    print(f"Tracerouting... {host}({dest_addr})")
    if 'error' in geo_data:
        print(geo_data['error'])
    else:
        print(f"IP: {geo_data['ip']}")
        print(f"Country: {geo_data['country']}")
        print(f"City: {geo_data['city']}")
    # bucla infinita pana la gasirea adresei destinatie
    while True:
        #seteaza ttl pentru pachetul udp (1,2,3,...)
        udp_sock.setsockopt(socket.SOL_IP, socket.IP_TTL, ttl)
        #trimite pachet UDP gol pe portul ales, la adresa destinatie
        udp_sock.sendto(b'', (dest_addr, port))
        #timpul de start
        start_time = time.time()
        #numarul de incercari de primit pachete ICMP
        no_tries = 3
        #flaguri sa verificam daca primim pachet inapoi si respectiv daca am ajuns la destinatie
        success = False
        done = False
        # incercam de 3 ori sa primim pachet
        while no_tries > 0:
            try:
                # daca primim inapoi pachet ICMP de 512bytes success devine true
                packet, addr = icmp_sock.recvfrom(512)
                success = True
            except socket.error:
                # altfel scade nr de incercari si continua bucla pana primeste/nu primeste raspuns
                no_tries -= 1
                continue
            if addr[0] == dest_addr:
                # daca ajungem la ip-ul destinatie 'done' devine true si iesim din bucla principala
                done = True
                break
        if success:
            # daca primeste:
            # se salveaza timpul de sfarsit
            end_time = time.time()
            try:
                # incearca sa primeasca numele hostname-ul in functie de IP
                name = socket.gethostbyaddr(addr[0])[0]
            except: pass # ignora erorile de la cererea hostname-ului
            geo_data1 = geo(addr[0])
            # timpul de raspuns e calculat in msec cu 4 zecimale
            t = round((end_time - start_time) * 1000, 4)
            # trateaza afisarile pentru fiecare ip in parte - posibil ca unele sa nu returneze datele geolocatiei
            if 'error' in geo_data1:
                print(f"TTL: {ttl} Addr: {name}({addr[0]}) Time: {t}ms Geo Error: {geo_data1['error']}")
            else:
                print(f"TTL: {ttl} Addr: {name}({addr[0]}) Time: {t}ms Country: {geo_data1['country']} City: {geo_data1['city']}")
        else:
            print(f"TTL: {ttl} *  *  *")

        if done: 
            # daca ajungem la ip-ul destinatie 'done' devine true si iesim din bucla principala
            break
        # incrementeaza ttl pentru urmatorul nod(router)
        ttl += 1
        
    print("Traceroute completed.")

if __name__ == "__main__":
    main()