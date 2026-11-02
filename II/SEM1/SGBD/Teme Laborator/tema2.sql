-- E2
-- Definirea tipului de colectie
CREATE OR REPLACE TYPE TIP_ORASE_AZ AS VARRAY(10) OF VARCHAR2(20);
/

-- Tabel pentru excursie
CREATE TABLE EXCURSIE_AZ (
    cod_excursie NUMBER(4) PRIMARY KEY,
    denumire VARCHAR2(20),
    orase TIP_ORASE_AZ,
    status VARCHAR2(15) CHECK (status IN ('Disponibila', 'Anulata'))
);
/

-- a) Inserati 5 inregistrari in tabel

INSERT INTO EXCURSIE_AZ (cod_excursie, denumire, orase, status)
VALUES (1, 'Tur Muntenia', TIP_ORASE_AZ('Bucuresti', 'Prahova', 'Arges'), 'Disponibila');

INSERT INTO EXCURSIE_AZ (cod_excursie, denumire, orase, status)
VALUES (2, 'Tur Transilvania', TIP_ORASE_AZ('Cluj-Napoca', 'Sibiu', 'Alba Iulia'), 'Disponibila');

INSERT INTO EXCURSIE_AZ (cod_excursie, denumire, orase, status)
VALUES (3, 'Tur Oltenia', TIP_ORASE_AZ('Craiova', 'Targu Jiu', 'Drob. Turnu Severin'), 'Anulata');

INSERT INTO EXCURSIE_AZ (cod_excursie, denumire, orase, status)
VALUES (4, 'Tur Banat-Crisana', TIP_ORASE_AZ('Resita', 'Timisoara', 'Arad'), 'Anulata');

INSERT INTO EXCURSIE_AZ (cod_excursie, denumire, orase, status)
VALUES (5, 'Tur Moldova', TIP_ORASE_AZ('Iasi', 'Botosani', 'Suceava'), 'Disponibila');


-- b) Actualizați coloana orase pentru o excursie specificată:
-- adăugați un oraș nou în listă, ce va fi ultimul vizitat în excursia respectivă;

UPDATE EXCURSIE_AZ
SET orase = TIP_ORASE_AZ('Bucuresti', 'Prahova', 'Arges', 'Calarasi')
WHERE cod_excursie = 1; -- actualizam pentru excursia "Tur Muntenia"
COMMIT;
ROLLBACK;

select * from excursie_az;

-- adăugați un oraș nou în listă, ce va fi al doilea oraș vizitat în excursia respectivă; 
-- adaug pe a doua pozitie orasul "Sighisoara" in cel de-al doilea vector de orase

UPDATE EXCURSIE_AZ
SET orase = TIP_ORASE_AZ('Cluj-Napoca','Sighisoara', 'Sibiu', 'Alba Iulia') 
WHERE cod_excursie = 2; -- actualizam pentru excursia "Tur Transilvania"
COMMIT;


-- inversați ordinea de vizitare a două dintre orașe al căror nume este specificat;
-- inversez "Iasi" si "Suceava" in vectorul cu codul 5 

UPDATE EXCURSIE_AZ
SET orase = TIP_ORASE_AZ('Suceava','Botosani', 'Iasi') 
WHERE cod_excursie = 5; -- actualizam pentru excursia "Tur Moldova"
COMMIT;


-- eliminați din listă un oraș al cărui nume este specificat.
-- eliminam "Resita" din vectorul cu codul 4
    
    UPDATE EXCURSIE_AZ
    SET orase = TIP_ORASE_AZ('Timisoara', 'Arad')
    WHERE cod_excursie = 4; -- actualizam pentru excursia "Tur Banat-Crisana"
    COMMIT;


-- c) Pentru o excursie al cărui cod este dat, afișați numărul de orașe vizitate, respectiv numele orașelor

DECLARE
   v_cod_excursie NUMBER := 5; 
   v_numar_orase NUMBER;
BEGIN
   
   SELECT COUNT(oras.column_value) AS numar_orase
   INTO v_numar_orase
   FROM TABLE((SELECT orase FROM EXCURSIE_AZ WHERE cod_excursie = v_cod_excursie)) oras;

   
   DBMS_OUTPUT.PUT_LINE('In excursia cu codul ' || v_cod_excursie || ' vom vizita ' || v_numar_orase || ' orase.');
   DBMS_OUTPUT.NEW_LINE;
   
   FOR city IN (SELECT oras.column_value AS nume_oras
                FROM TABLE((SELECT orase FROM EXCURSIE_AZ WHERE cod_excursie = v_cod_excursie)) oras) 
   LOOP
      
      DBMS_OUTPUT.PUT_LINE('Oras: ' || city.nume_oras);
   END LOOP;
   DBMS_OUTPUT.NEW_LINE;
END;
/