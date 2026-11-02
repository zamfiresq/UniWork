# Zamfirescu Alexandra - grupa 241

# 1) Construiti doi vectori x si y cu 1000 de elemente fiecare, extrase in mod
# aleator din multimea cu numere intregi -24500:76000.

# SOLUTIE:

interval <- -24500:76000 # scriem intervalul ca lista de la -24500 la 76000
sizev <- 1000 # marimea unui vector
x <- sample(interval,sizev,replace = FALSE) # folosim functia sample() pentru a lua valori random, fara a se repeta
y <- sample(interval,sizev,replace = FALSE)


# a) Stabiliti care dintre cei doi vectori are mai multe elemente,
# luate in valoare absoluta, mai mari decat valoarea absoluta a elementului
# corespondent din celalalt vector.


# vom folosi functia sum() pentru determinarea numarului de elemente, atat pentru abs(x)>abs(y),
# cat si pentru abs(y)>abs(x)

nr_x_gr_y <- sum(abs(x)>abs(y)) 
nr_y_gr_x <- sum(abs(y)>abs(x))

cat("Nr de elemente din x mai mari decât elementele din y in valoare absolută:", nr_x_gr_y, "\n\n")
cat("Nr de elemente din y mai mari decât elementele din x in valoare absolută:", nr_y_gr_x, "\n\n")

# b) Stabiliti care dintre cei doi vectori are minimul pe o pozitie mai mare

element_minim_x <- min(x)
element_minim_y <- min(y)

# folosim which() pentru determinarea pozitiei unui element

poz_x <- which(x == element_minim_x) 
poz_y <- which(y == element_minim_y)

if (poz_x > poz_y) {
  cat("Poziția elementului", element_minim_x,"este mai mare decât poziția elementului", element_minim_y, "\n")
  cat("Poziția:",poz_x, "\n\n")
} else {
  cat("Poziția elementului", element_minim_y,"este mai mare decât poziția elementului", element_minim_x, "\n")
  cat("Poziția:", poz_y, "\n\n")
}

# c) Stabiliti care dintre cei doi vectori are cele mai multe valori care se repeta

# trebuie intai sa modificam vectorii x si y la replace = TRUE in cadrul functiei sample, pentru a
# permite repetarea valorilor

x <- sample(interval,sizev,replace = TRUE) 
y <- sample(interval,sizev,replace = TRUE)

# folosim functia table() pentru a afisa de cate ori se repeta o valoare

frecv_x <- table(x)
frecv_y <- table(y)

# determinam frecventa maxima din ambii vectori

max_frecv_x <-  max(frecv_x)
max_frecv_y <-  max(frecv_y)

# comparam valorile, determinand care vector are mai multe valori care se repeta


if(max_frecv_x > max_frecv_y){
  cat("Vectorul x are mai multe valori care se repetă.\n\n")
}else if(max_frecv_y > max_frecv_x){
  cat("Vectorul y are mai multe valori care se repetă.\n\n")
}else{
  cat("Ambii vectori x și y au acelasi numar de valori care se repetă.\n\n")
}


# d) Stabiliti care dintre cei doi vectori are o secventa de cel putin 2 valori consecutive

x <- sample(interval,sizev,replace = FALSE) 
y <- sample(interval,sizev,replace = FALSE)

# cat("Vectorul x: ", x)
# cat("Vectorul y: ", y)

# folosim any pentru a determina daca este adevarat daca gasim o pereche de numere consecutive 

secventa_consecutiva_x <-  any(diff(x) == 1) 
secventa_consecutiva_y <-  any(diff(y) == 1)

if(secventa_consecutiva_x){
  cat("Vectorul x are o secvență de cel puțin o pereche valori consecutive.\n\n")
} else {
  cat("Pentru vectorul x nu există nicio secvență de cel puțin 2 valori consecutive.\n\n")
}

if(secventa_consecutiva_y){
  cat("Vectorul y are o secvență de cel puțin o pereche de valori consecutive.\n\n")
} else {
  cat("Pentru vectorul y nu există nicio secvență de cel puțin 2 valori consecutive.\n\n")
}

# e) Stabiliti care dintre cei doi vectori are mai multe valori divizibile cu corespondentele lor din celalalt vector.

# initializam 2 variabile x divizibil cu y, y divizibil cu x, avand restul 0
x_div_y <- x %% y == 0
y_div_x <- y %% x == 0

# folosim sum() pentru a numara valorile adevarate din fiecare vector
nr_x_div_y <- sum(x_div_y)
nr_y_div_x <- sum(y_div_x)

# comparam nr de valori divizibile intre ele 
if (nr_x_div_y > nr_y_div_x) {
  cat("Vectorul x are mai multe valori divizibile cu corespondentele lor din vectorul y.\n\n")
} else if (nr_y_div_x > nr_x_div_y) {
  cat("Vectorul y are mai multe valori divizibile cu corespondentele lor din vectorul x.\n\n")
} else {
  cat("Vectorii au același număr de valori divizibile între ei.\n")
}
