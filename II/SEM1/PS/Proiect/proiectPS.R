# instalarea pachetelor pe care le-am folosit

install.packages("gt")
install.packages("pracma")

# integrarea pachetelor necesare
library(gt)
library(pracma)


# 1
# a) ------------------------------------------ REPARTITIA COMUNA INCOMPLETA A LUI X SI Y ------------------------------------------
frepcomgen <- function(n, m) {
  # valorile lui X si Y
  xv <- 1:n
  yv <- 1:m
  
  # generam valori din repartitia comuna
  xycomp <- matrix(runif(n * m), nrow = n, ncol = m)
  
  # facem normalizarea fiecarei linii pentru a ne asigura ca suma fiecărei linii este 1
  xycomp <- t(apply(xycomp, 1, function(row) row / sum(row)))
  
  # facem normalizarea globala pentru a ne asigura ca suma totala a elementelor este 1
  xycomp <- xycomp / sum(xycomp)
  
  # rotunjim elementele la doua zecimale pentru usurinta calculelor
  xycomp <- round(xycomp, digits = 2)
  
  xycomp[1,1] <- xycomp[1,1] +(1-sum(xycomp))
  # calculam sumele pe linii si coloane
  pi <- rowSums(xycomp, na.rm = TRUE)
  qj <- colSums(xycomp, na.rm = TRUE)
  
  # generam 3 pozitii random ale unor elemente din matrice pe care sa le stergem din repartitia comuna
  random_col <- sample(c(1,m), 3, replace=TRUE)
  random_row <- sample(c(1,n), 3, replace=TRUE)
  xycomp[random_row[1], random_col[1]] <- NaN
  xycomp[random_row[2], random_col[2]] <- NaN
  xycomp[random_row[3], random_col[3]] <- NaN
  
  # adaugam probabilitatile lui X si Y (ultima coloana / linie)
  xycomp <- rbind(cbind(xycomp, pi), c(qj, 1))
  
  xycomp <- cbind(c(as.character(xv), "∑qj"), xycomp)
  rownames(xycomp) <- NULL
  colnames(xycomp) <- c("X\\Y", as.character(yv), "∑pi")
  
  # transformam matricea in data.frame
  xycomp <- as.data.frame(xycomp)
  
  # tabelul de repartitie comuna cu gt
  tbl <- gt(xycomp) %>%
    tab_header(title = "Repartitia Comuna a v.a. X si Y (incompleta)") %>%
    sub_missing(columns = everything(), missing_text = " ") %>%
    cols_align(align = "left")
  
  return(list(tbl = tbl, xycomp = xycomp))
}

# exemplu de utilizare
result <- frepcomgen(4,5)

# extragem tabelul si matricea din rezultatul functiei
table_result <- result$tbl
matrice_xycomp <- result$xycomp

# afisare
print(table_result)
print(matrice_xycomp)
View(matrice_xycomp)


# b) ------------------------------------------ COMPLETAREA REPARTITIEI COMUNE A LUI X SI Y ------------------------------------------

# FUNCTIE AUXILIAR CARE CALCULEAZA VALOAREA CE TREBUIE COMPLETATA PE O ANUMITA POZITIE
completare <- function(mtx, indice_linie, indice_coloana, tip_completare){
  n <- nrow(mtx) # linii
  m <- ncol(mtx) # coloane
  suma_pi <- as.numeric(mtx[indice_linie,m]) 
  suma_qi <- as.numeric(mtx[n,indice_coloana]) 

  # daca tip_completare este 1 înseamna ca vom face completarea la nivel de linie
  if(tip_completare==1){
    for(j in 2:(m-1)){
      if(indice_coloana!=j){
        # calculam valoarea lipsa prin scaderi repetate
        suma_pi <- suma_pi - as.numeric(mtx[indice_linie,j])
      }
    }
    mtx[indice_linie,indice_coloana] <- round(suma_pi,digits=2)
    # print(mtx)
  }
  
  # dacă tip_completare este 0 inseamna ca vom face completarea la nivel de coloana
  else{
    for(i in 1:(n-1)){
      if(indice_linie!=i){
        # calculam valoarea lipsa prin scaderi repetate
        suma_qi <- suma_qi - as.numeric(mtx[i,indice_coloana])
      }
    }
    mtx[indice_linie,indice_coloana] <- round(suma_qi,digits=2)
    #print(mtx)
  }
  return (mtx)
}
# matrice_xycomp <- completare(matrice_xycomp, 4, 2, 0)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# FUNCTIA PRINCIPALA CARE IDENTIFICA VALORILE LIPSA(NaN) PE CARE LE PUTEM COMPLETA
fcomplrepcom <- function(mtx) {
  n <- nrow(mtx) 
  m <- ncol(mtx) 
  
  # parcurgem liniile matricei
  for (i in 1:(n-1)) {
    contor_linie <- 0 
    
    for (j in 2:(m-1)) {
      if (is.nan(as.numeric(mtx[i, j]))) {
        # daca gasim o valoare NaN incrementam contorul si salvam coloana pe care am gasit elementul 
        contor_linie  <- contor_linie + 1
        indice_col <- j
      }
    }
    # daca am gasit un singur element lipsa pe linia i înseamna ca putem face completarea
    if(contor_linie == 1)
      mtx <- completare(mtx,i,indice_col,1)
  }
  
  # parcurgem coloanele matricei
  for(j in 2:(m-1)){
    # variabilă in care retinem nr de valori NaN de pe coloana j
    contor_coloana <- 0
    for(i in 1: (n-1)){
      if (is.nan(as.numeric(mtx[i, j]))) {
        # daca gasim o valoare NaN incrementam contorul si salvam linia pe care am gasit elementul 
        contor_coloana  <- contor_coloana + 1
        indice_lin <- i
      }
    }
    
    # daca am gasit un singur element lipsa pe coloana j înseamna ca putem face completarea
    if(contor_coloana==1){
      mtx <- completare(mtx,indice_lin,j,0)
    }
  }
  return (mtx)
}

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# ex
matrice_xycomp <- fcomplrepcom(matrice_xycomp)
print(matrice_xycomp)
View(matrice_xycomp)

df <- as.data.frame(matrice_xycomp)
gt(df)


# c) ------------------------------------------ COMPLETAREA REPARTIȚIEI COMUNE A LUI X SI Y ------------------------------------------

frepmarginal <- function(mtx) {
  n <- nrow(mtx)
  m <- ncol(mtx) 
  
  # construim repartitia marginala a lui X
  matrice_X <- rbind(format(as.numeric(mtx[, 1]),nsmall=0), as.numeric(mtx[, m]))
  matrice_X <- matrice_X[, -ncol(matrice_X)]
  
  # construim repartitia marginala a lui Y
  elementele_Y <- 0:(m - 1)
  matrice_Y <- rbind(format(as.numeric(elementele_Y),nsmall=0), as.numeric(mtx[n, -m]))
  
  # eliminam prima coloana (etichetele) si ultima coloana (suma) din matricea Y
  matrice_Y <- matrice_Y[, -c(1, ncol(matrice_Y))]
  
  # convertim matricile intr-un data frame pentru a putea lucra cu libraria gt
  tabel_X <- as.data.frame(matrice_X)
  tabel_Y <- as.data.frame(matrice_Y)
  
  
  # utilizam functia gt() pentru a crea tabelul
  tb1 <- gt(tabel_X) %>%
    tab_header(title = "Repartitia marginala a lui X") %>%
    cols_align(align = "left") 
  
  tb2 <- gt(tabel_Y) %>%
    tab_header(title = "Repartitia marginala a lui Y") %>%
    cols_align(align = "left")
  
  return(list(tb1 = tb1, tb2 = tb2, matrice_X = matrice_X, matrice_Y = matrice_Y))
}


# ex
rezultat <- frepmarginal(matrice_xycomp)
rep_X <- rezultat$matrice_X
rep_Y <- rezultat$matrice_Y
print(rep_X)
print(rep_Y)
print(rezultat$tb1)
print(rezultat$tb2)

# d) ------------------------------------------ CALCULUL COVARIANȚEI COMPUSA ------------------------------------------

# Z <– aX + bY
# T <– cX + dY

# avem de calculat:
# Cov (Z, T) = Cov(aX + bY, cX + dY) = acVar(X) + (ad+bc)Cov(X,Y) + bdVar(Y)


# FUNCTII AUXILIAR

# calculam E[X]
calculMedie<-function(mtx)
{
  medie <-0
  m <-ncol(mtx)
  for (i in 1:m)
  {
    medie <- medie + as.numeric(mtx[1,i])*as.numeric(mtx[2,i])
  }
  return(medie)
}

# calculam E[Y]
calcul_Medie_XY <- function(mtx){
  n <- nrow(mtx)
  m <- ncol(mtx)
  suma <- 0
  for(i in 1:(n-1)){
    for (j in 2:(m-1)){
      suma <- suma + i * (j-1) * as.numeric(mtx[i,j])
    }
  }
  return(suma)
}


# calculam cov(X,Y)
calcul_Covarianta <- function(m_X,m_Y,m_XY){
  covarianta <- m_XY - m_X*m_Y
  return(covarianta)
}

# calculam Var(X)
calcul_Varianta  <- function(mtx){
  # Var(X)=E[x^2]-E[x]^2
  mtx_patrat <- mtx
  mtx_patrat[1,] <- as.numeric(mtx[1,])^2
  var <- calculMedie(mtx_patrat)-calculMedie(mtx)^2
  return(var)
}

# FUNCTIA PRINCIPALA
fpropcov <- function(a, b, c, d, X, Y, mtx) {
  
  var_X <- calcul_Varianta(X)
  var_Y <- calcul_Varianta(Y)
  medie_XY <- calcul_Medie_XY(mtx)
  medie_X <- calculMedie(X)
  medie_Y <- calculMedie(Y)
  cov_X_Y <- calcul_Covarianta(medie_X, medie_Y, medie_XY)
  
  # aplicam proprietatea covariantei 
  cov_Z_T <- a*c*var_X + (a*d + b*c)*cov_X_Y + b*d*var_Y
  
  return(cov_Z_T)
}

# Exemple de utilizare
medie_X <- calculMedie(rep_X)
print(medie_X)

medie_Y <- calculMedie(rep_Y)
print(medie_Y)

medie_XY <- calcul_Medie_XY(matrice_xycomp)
print(medie_XY)

cov <- calcul_Covarianta(medie_X,medie_Y,medie_XY)
print(cov)

print(calcul_Varianta(rep_X))
print(calcul_Varianta(rep_Y))
print(fpropcov(1,3,2,4,rep_X, rep_Y,matrice_xycomp))



# e) ------------------------------------------ CALCULUL PROBABILITATII CONDITIONATE ------------------------------------------

# P(X=x|Y=y) = P(X=x,Y=y)/P(Y=y)
# functia pentru P(X | Y = y)
fPcond_X_de_Y <- function(mtx, x, y) {
  
  # probabilitatea comuna P(X = xi, Y = yj)
  p_xy <- as.numeric(mtx[x, y+1])
  
  # probabilitatea P(Y = y)
  p_y <- as.numeric(mtx[nrow(mtx), y+1])
  
  # calculam probabilitatea cond P(X | Y = y)
  p_cond <- p_xy / p_y
  
  return(p_cond)
}

# P(Y=y | X=x) = P(X=x,Y=y)/P(X=x)
# functia pentru P(Y | X = x)
fPcond_Y_de_X <- function(mtx, x, y) {
  
  p_xy <- as.numeric(mtx[x, y+1])
  print(p_xy)
  
  # probabilitatea P(X = x) 
  p_x <- as.numeric(mtx[x,ncol(mtx)])
  print(p_x)
  
  # calculam probabilitatea cond P(Y | X = x) = p_xy / p_x
  p_cond <- p_xy / p_x
  
  return(p_cond)
}

# functia principala fPcond
fPcond <- function(mtx, x, y, cond = "x|y") {
  if (cond == "x|y") {
    return(fPcond_X_de_Y(mtx, x, y))
  } else if (cond == "y|x") {
    return(fPcond_Y_de_X(mtx, x, y))
  } else {
    stop("Argumentul 'cond' trebuie sa fie 'x|y' sau 'y|x'")
  }
}

fPcond(matrice_xycomp, 1, 2, cond= "x|y")
fPcond(matrice_xycomp, 2, 1, cond= "y|x")


#f) ------------------------------------------ CALCULUL Probabilitatii(X,Y) ------------------------------------------
# P(a≤X≤b,c≤Y≤d)
fPcomun <- function(a,b,c,d,mtx){
  suma <- 0
  for(i in a:b){
    for(j in (c+1):(d+1)){
      suma <- suma+ as.numeric(mtx[i,j])
    }
  }
  return(suma)
}
fPcomun(1,2,3,5,matrice_xycomp)


# g) ------------------------------------------ CALCUL DE PROBABILITATI ------------------------------------------

# 1.Cov(5X+9,-3Y-2) = Cov(5X,-3Y) + Cov(5X, -2) + Cov(9,-2) + Cov(9,-3Y)
                # = Cov(5X,-3Y)
                # = Cov(5X+0Y , 0X-3Y)
                # = Cov(Z,T) - aplicam functia de la subpunctul d)
print(fpropcov(5,0,0,-3,rep_X,rep_Y,matrice_xycomp))

# 2. P(0<X<0.8|Y>0.3) = P(0<X<0.8 , Y>0.3)/P(Y>0.3)

calcul_g.2 <- function (mtx){
  suma <- 0
  suma_y <- 0
  for(i in 1:(nrow(mtx)-1)){
    for(j in 2:(ncol(mtx)-1)){
      if(mtx[i,1]>0 && mtx[i,1]<0.8 && (j-1) > 0.3 ){
        suma <- suma + as.numeric(mtx[i,j]) 
      }
      
      if((j-1)>0.3){
        suma_y <- suma_y + as.numeric(mtx[nrow(mtx),j])
      }
    }
  }
  if(suma_y!=0){
    rezultat <- suma/suma_y
  }
  else{
    rezultat <- 0
  }
  return(rezultat)
}
print(calcul_g.2(matrice_xycomp))

# 3. P(X>0.2,Y<1.7) 
calcul_g.3 <- function(mtx){
  suma <- 0
  for(i in 1:(nrow(mtx)-1)){
    for(j in 2:(ncol(mtx)-1)){
      if(mtx[i,1]>0.2 && (j-1) < 1.7 ){
        suma <- suma + as.numeric(mtx[i,j]) 
      }
      
      }
    }
  return(suma)
}
print(calcul_g.3(matrice_xycomp))


# h) ------------------------------------------ INDEPENDENTA ------------------------------------------

# X si Y independente => P(X=x, Y=y) = P(X=x)*p(Y=y)
# P(X=x, Y=y) = matrice_xycomp[x,y+1]
# P(X=x) = matrice_xycomp[x, m+2]
# P(Y=y) = matrice_xycomp[n+1, y+1]
# parcurgem fiecare element matrice_xycomp[x,y+1] si verificam 
# daca egalitatea are loc pt fiecare element 
# facem asta cu o variabila bool ok=1, cand inegalitatea nu mai e indeplinita => ok=0
# daca ok = 1, X si Y sunt independente, daca ok = 0, X si Y nu sunt independente


fverind <- function(mtx){
  n <- nrow(mtx)
  m <- ncol(mtx)
  
  ok <- 1
  for (i in 1:(n-1)) {
    for (j in 2:(m-1)) {
      produs <- as.numeric(mtx[i, m]) * as.numeric(mtx[n, j])
     
      if(isTRUE(all.equal(as.numeric(mtx[i,j]), produs))== FALSE)
      {
        ok <- 0
      }
    }
  }
  return(ok)
}


# verificam pentru o repartitie generata, care cel mai probabil NU are X si Y independente
verifindep <- fverind(matrice_xycomp)
if (verifindep == 0) {
  print("X și Y nu sunt independente")
} else {
  print("X și Y sunt independente")
}

# verificam si pentru o repartitie data de noi, special ca sa fie independenta

result <- frepcomgen(2,2)
matrice_xycomp <- result$xycomp
View(matrice_xycomp)
matrice_xycomp <- fcomplrepcom(matrice_xycomp)
View(matrice_xycomp)


# transformam repartitia generata random astfel incat sa fie independenta
matrice_xycomp[1,4] <- 0.6
matrice_xycomp[2,4] <- 0.4
matrice_xycomp[3,2] <- 0.7
matrice_xycomp[3,3] <- 0.3
matrice_xycomp[1,2] <- 0.42
matrice_xycomp[2,2] <- 0.28
matrice_xycomp[1,3] <- 0.18
matrice_xycomp[2,3] <- 0.12

verifindep <- fverind(matrice_xycomp)
if (verifindep == 0) {
  print("X și Y nu sunt independente")
} else {
  print("X și Y sunt independente")
}


# h) ------------------------------------------ NECORELATIA ------------------------------------------

fnercor <- function(mtx){
  
  rezultat <- frepmarginal(mtx)
  rep_X <- rezultat$matrice_X
  rep_Y <- rezultat$matrice_Y
  # print(rep_X)
  # print(rep_Y)
  medie_X <- calculMedie(rep_X)
  medie_Y <- calculMedie(rep_Y)
  medie_XY <- calcul_Medie_XY(matrice_xycomp)
  # print(medie_X)
  # print(medie_Y)
  # print(medie_XY)
  cov_XY <- 0
  cov_XY <- calcul_Covarianta(medie_X,medie_Y,medie_XY)
  # print(cov_XY)
  # print(round(as.numeric(cov_XY),digits=2))
  if(round(as.numeric(cov_XY),digits=2) == 0){
    print("X si Y sunt necorelate")
  } else{
    print("X si Y sunt corelate")
  }
}
fnercor(matrice_xycomp)


# verificam si pentru cazul in care ar trebui sa fie corelate
result <- frepcomgen(4,4)
matrice_xycomp <- result$xycomp
View(matrice_xycomp)
matrice_xycomp <- fcomplrepcom(matrice_xycomp)
View(matrice_xycomp)

fnercor(matrice_xycomp)
#i) ------------------------------------------ X,Y,Z ------------------------------------------

# reprezentare 3D a repartitiei comune a 3 variabile aleatoare discrete (X, Y, Z) 
# si obtine repartitiile lor marginale
# cu ajutorul librariei plotly vom construi reprezentarea vizuala
# cu ajutorul librariei dplyr vom construi repartitiile marginale

# pe axa x este valoarea variabilei aleatoare X
# pe axa y este valoarea variabilei aleatoare Y
# pe axa z este valoarea variabilei aleatoare Z

# probabilitatea din repartitia comuna a celor 3 variabile este, de fapt,
# un punct(bulina) din interiorul reprezentarii vizuale, si difera ca dimensiune in functie de valoarea ei (dimensiunea unui punct e direct proportionala cu valoarea probabilitatii).

install.packages('plotly')
install.packages('dplyr')

library(plotly)
library(dplyr)

# pentru exemplificare vom lua valori mici pentru a putea observa punctele rezultate
n <- 3  
m <- 2  
k <- 2  

# generarea celor 3 variabile aleatoare cu probabilitatea in fiecare punct
rep_comuna <- expand.grid(X = 1:n, Y = 1:m, Z = 1:k) %>%
  mutate(probabilitate = runif(n * m * k))

# normalizarea probabilitatilor astfel incat suma sa fie 1
rep_comuna$probabilitate <- rep_comuna$probabilitate / sum(rep_comuna$probabilitate)
View(rep_comuna)

# verificarea sumei probabilitatilor
# suma_probabilitatilor <- sum(rep_comuna$probabilitate)
plot_ly(rep_comuna, x = ~X, y = ~Y, z = ~Z, type = 'scatter3d', mode = 'markers',
        marker = list(size = ~probabilitate*200, color = ~probabilitate, colorscale = 'Reds')) %>%
  layout(title = 'Reprezentarea vizuala a repartitiei comune X, Y, Z',
         scene = list(xaxis = list(title = 'X'),
                      yaxis = list(title = 'Y'),
                      zaxis = list(title = 'Z')))

# construim repartitiile marginale ale celor 3 variabile aleatoare discrete
rep_X <- aggregate(probabilitate ~ X, data = rep_comuna, FUN = sum)
rep_Y <- aggregate(probabilitate ~ Y, data = rep_comuna, FUN = sum)
rep_Z <- aggregate(probabilitate ~ Z, data = rep_comuna, FUN = sum)


print(rep_X)
View(rep_X)

print(rep_Y)
View(rep_Y)

print(rep_Z)
View(rep_Z)



##############################################################################################################################
# 2
# a)

# testam aplicabilitatea teoremei lui Fubini
test_fubini <- function(f, a, b, c, d) {
  if (!is.na(integrate(function(x) f(x, a), lower = a, upper = b)$value) && 
      !is.na(integrate(function(y) f(a, y), lower = c, upper = d)$value)) { 
    return(TRUE)  # teorema lui Fubini e aplicabila
  } else {
    return(FALSE) # teorema lu Fubini nu e aplicabila
  }
}

# limitele de integrare pentru x si y
a <- 0
b <- 1
c <- 0
d <- 1

# o functie buna
f1 <- function(x, y) {
  return(x^2+y^2)
}

# o functie (ne)buna
f2 <- function(x, y) {
  return(1/(x*y))
}


if (test_fubini(f2, a, b, c, d)) {
  cat("Teorema lui Fubini este aplicabilă pentru funcția dată.\n")
  
  library(pracma)
  I <- integral2(f2, 0, 1, 0, 1)
  I$Q
  
} else {
  cat("Teorema lui Fubini nu este aplicabilă pentru funcția dată.\n")
}


# 2.b
library(plotly)

# functia f
f <- function(x, y) {
  return(x^22 + y^8 + 76*x^55*x^5)
}

# nr de esantioane pt fiecare axa
num_samples <- 100

# generarea eșantioanelor aleatoare pentru axa x și y între 0 și 1
x <- sort(runif(num_samples, 0, 1))
y <- sort(runif(num_samples, 0, 1))

# calculul valorilor funcției f(x, y) pe baza eșantioanelor generate
z <- outer(x, y, f)

# crearea plotului
plot_ly(x = x, y = y, z = z, type = "surface") %>%
  layout(scene = list(
    xaxis = list(title = "X"),
    yaxis = list(title = "Y"),
    zaxis = list(title = "Z")
  ))

# c. 
# functie care nu e pozitiva pe tot domeniul
f <- function(x, y) {
  return(-1)  
}

# functie care e pozitiva pe tot domeniul si are integrala dubla = 1
f <- function(x, y) {
  return(4 * x * y)
}

# functie care e pozitiva pe tot domeniul, dar nu are integrala dubla = 1
f <- function(x, y) {
  return(x^2 + y^2)
}

# verificam daca f este pozitiva pe [0,1]x[0,1]
if(all(sapply(seq(0,1,0.01), function(x) all(f(x, seq(0,1,0.01)) >= 0))) && 
   all(sapply(seq(0,1,0.01), function(y) all(f(seq(0,1,0.01), y) >= 0)))) {
  print("Functia este pozitiva pe intervalul dat.")
} else {
  print("Functia nu este pozitiva pe intervalul dat.")
}


# calculam integrala dubla a functiei peste domeniul [0,1]x[0,1]
integral <- integral2(f, 0, 1, 0, 1)$Q

print(integral)

if(integral==1) {
  print("Functia este o densitate de probabilitate.")
} else {
  print("Functia nu este o densitate de probabilitate.")
}

#d.

install.packages("mvtnorm")
library(mvtnorm)


creare_variabila_aleatoare <- function(densitate, dimensiune = 1) {
  # verific daca este vorba despre o v.a. unidim sau bidim
  if (is.function(densitate)) {
    if (dimensiune == 1) {
      # generam v.a. unidim folosind densitatea data
      valori_x <- seq(-10, 10, length.out = 1000)
      densitati <- densitate(valori_x)
      variabila_aleatoare <- sample(valori_x, size = 1000)
    } else if (dimensiune == 2) {
      # generam v.a. bidim folosind densitatea data
      variabila_aleatoare <- rmvnorm(n = 1000, mean = c(0, 0), sigma = matrix(c(1, 0.5, 0.5, 1), nrow = 2))
    } else {
      stop("Dimensiunea specificată nu este valida.")
    }
  } else {
    stop("Densitatea de probabilitate nu este functie.")
  }
  
  print(variabila_aleatoare)
  return(variabila_aleatoare)
}


# functia densitate de probabilitate pt o v.a. unidim
densitate_unidimensionala <- function(x) {
  return(1)
}

# crearea v.a. unidim folosind densitatea de probabilitate definita
variabila_aleatoare_unidimensionala <- creare_variabila_aleatoare(densitate_unidimensionala, dimensiune = 1)

# functia densitate de probabilitate pt o v.a. bidim
densitate_bidimensionala <- function(x, y) {
  return(4 * x * y)
}

# crearea v.a. bidim folosind densitatea de probabilitate definita
variabile_aleatoare_bidimensionale <- creare_variabila_aleatoare(densitate_bidimensionala, dimensiune = 2)