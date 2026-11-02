## Context
Scripturile dnstunnel-server.py si dnstunnel-host.py functioneaza pentru un caz mai simplist: se creeaza tunelul DNS si se transmite un mesaj text.

## Probleme pe care le-am intampinat
Scripturile dnstnl-file-server.py si dnstnl-file-client.py nu functioneaza corect in intregime.
- Conexiunea se creeaza.
- Cererea DNS este primita de server, insa dintr-un motiv neidentificat, fisierul cu text salvat pe server nu se transfera.

## Cum am incercat sa rezolvam?
- Am realizat teste cu 'tcpdump' pentru a observa pachetele pe care le primim.
- Deducem ca din cauza buclei, transferul nu se finalizeaza.

## Aditional
In directorul de lucru se gaseste si fisierul 'captura_c_dns.pcap', generat de 'tcpdump'.




### Incercam sa rezolvam problema in timp util pentru prezentare!
