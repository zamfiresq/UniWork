# Zamfirescu Alexandra, grupa 241
# SCHEME CLASICE DE PROBABILITATI



# Schema cu bila revenita -> generalizare 
# Vom folosi formula lui Bernoulli

probabilitate_bernoulli <- function(n, k, p){
  q <-  1 - p # q - prob de esec; p - prob de succes dintr-o singura miscare
  prob_calculare <- choose(n, k) * (p ^ k) * (q ^ (n - k)) # aplicam formula
  return(prob_calculare)
}

# folosire functie
# exemplu enunt: 
# Se arunca un zar de 5 ori. Se cere probabilitatea ca fata cu un punct sa apara
# exact de doua ori
P1 <- probabilitate_bernoulli(5, 2, 1/6)
cat(P1)




# Schema cu bila fara intoarcere -> generalizare
# Schema hipergeometrica

probabilitate_hipergeometrica <- function(N, K, n, k){
  # calculam raportul dintre nr de combinatii de a extrage 
  #n-k din N-K elemente si nr total de combinatii de a extrage n elem din N
  prob <- choose(K, k) * choose(N - K, n - k) /choose (N, n) 
  return(prob)
}

# folosire functie
# enunt: Intr-un playlist de Spotify exista 60 de melodii din care 30 sunt dintre preferatele lui Gigel,
# 20 sunt din playlist-uri anterioaresi 10 sunt melodii noi. 
# Lui Gigel ii place sa fie surprins si asculta playlist-ul in mod shuffle. 
# Calculati probabilitatea ca primele sigma melodii ascultate sa fie din cele preferate.


N <- 60  # nr total de melodii din playlist
K <- 30  # nr de melodii preferate ale lui Gigel
n <- 5   # Numărul de piese extrase
k <- 5   # Numărul de piese bune extrase din cele 5

  
# calculam probabilitatea pentru primele sigma melodii
P2 <- probabilitate_hipergeometrica(N, K, n, k)
cat(P2)




# Schema lui Pascal (la a cata intoarcere avem primul sucees?)
# Schema geometrica

probabilitate_pascal <- function(p, k) {
  q <- 1 - p
  prob <- p * (q^(k-1))
  return(prob)
}

# problema:
# Se arunca un zar pana la aparitia unei fete cu 6 puncte. Determinati pt ca fata sa apara in primele 3 aruncari.

p <- 1/6  # probabilitatea de a obtine fata cu 6 puncte intr-o singura aruncare
k <- 3    # nr de aruncari pana la primul succes

P3 <- probabilitate_pascal(p, k)
cat(P3)




# Schema lui Poisson (generalizare schema bila revenita)
# nu prea am idee aici sincer :,)