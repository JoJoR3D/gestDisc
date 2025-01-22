/*Questo programma ha il compito di gestire un archivio di dischi composto da 'n' categorie
  ogniuna delle quali contiene 'm' dischi identificati da autore, titolo e prezzo.
  Questo programma permette di inserire nuovi dischi, eliminarli,
  e data una categoria, restituisce il disco con prezzo minore*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>




typedef enum{Pop,Rap,Rock,Punk,Indie}Genere;


struct brani{
    int cod_num;
    Genere generi_musicali;
    char autore[30];
    char titolo[30];
    float prezzo;
};

typedef struct brani Brani;



void aggiorna_archivio(Brani*, int);
void copia_stringa(char[], char[]);
int appartiene(int[], int, int);
void new_dischi(Brani*, int);
int confronto_stringhe(char[], char[]);
int lunghezza_stringa(char*);
void elim_catalogo(Brani*,int);
Genere successivo(Genere);

Brani min(Brani, Brani);
Brani minimo(Brani[],int);
void Prezzo_Min(Brani*, int, Brani, Brani*, int*);
int ricerca_prezzo(Brani[], Brani, int);




int main()
{
    Brani Musica[15]= {{000,Pop,"Tiziano Ferro","il mistero della vita",9.90},
                       {000,Pop,"Marco Mengoni","atlantico",7.99},
                       {000,Pop,"Henry Styles","fine line",17.56},
                       {001,Rap,"Travis Scott","astroworld",14.49},
                       {001,Rap,"Marracash","persona",14.26},
                       {001,Rap,"Fabri Fibra","tradimento",7.08},
                       {002,Rock,"Pink Floyd","the dark side of the moon",13.75},
                       {002,Rock,"The Who","Who's next",8.49},
                       {002,Rock,"Luciano Ligabue","buon compleanno Elvis",4.99},
                       {003,Punk,"Green Day","dookie",22.93},
                       {003,Punk,"Pink Flag","wire",30.79},
                       {003,Punk,"Descendents","all",136.01},
                       {004,Indie,"Calcutta","mainstream",15.75},
                       {004,Indie,"Gazelle","plastica",95.00},
                       {004,Indie,"Brunori Sas","a casa tutto bene",17.99}
    };

    int i,j,pos,disc_categoria=3,cont=3;        /*disc_categoria= Numero di dischi presenti*/
    Brani Mini,Categoria;                       /*per ogni categoria.*/
    char Euro[]= "euro";

    for(j=0;j<disc_categoria;j++){
        fflush(stdin);                          /*Istruzione per pulire il buffer.*/
        printf("\n%d ESECUZIONE\n",j+1);

        new_dischi(Musica,disc_categoria);

        printf("\n\nCATALOGO\n");
        for(i=0;i<15;i++)
            printf("\n%d elemento: %d,%d,%s,%s,%.2f\n",i,Musica[i].cod_num, Musica[i].generi_musicali, Musica[i].autore, Musica[i].titolo, Musica[i].prezzo);
        printf("\n");

        elim_catalogo(Musica,15);

        printf("\n\nCATALOGO\n");
        for(i=0;i<15;i++)
            printf("\n%d elemento: %d,%d,%s,%s,%.2f\n",i,Musica[i].cod_num, Musica[i].generi_musicali, Musica[i].autore, Musica[i].titolo, Musica[i].prezzo);
        printf("\n");

        new_dischi(Musica,disc_categoria);

        printf("\n\nCATALOGO\n");
        for(i=0;i<15;i++)
            printf("\n%d elemento: %d,%d,%s,%s,%.2f\n",i,Musica[i].cod_num, Musica[i].generi_musicali, Musica[i].autore, Musica[i].titolo, Musica[i].prezzo);
        printf("\n");


        /*Se il codice categoria inserito è corretto verrà chiamata la function Prezzo_Min che
          ritornerà il prezzo minore del disco e la sua posizione nel catalogo.
          Se il prezzo minore che verrà ritornato è 0.00, vuol dire che nella categoria selezionata
          al momento non sono presenti dischi.*/

        do{
            cont--;

            printf("\nInserire codice della categoria per individuare il titolo con prezzo minore: Pop=0, Rap=1, Rock=2, Punk=3, Indie=4\n");
            scanf("%d",&Categoria.cod_num);

            if((Categoria.cod_num > 4 || Categoria.cod_num < 0) && cont !=0)                        /*Controlli per verificare che non venga inserito un codice categoria non corretto.*/
                printf("\nCodice errato, ripetere grazie (Numero tentativi rimasti %d)\n",cont);
            }
            while((Categoria.cod_num > 4 || Categoria.cod_num < 0)  && cont != 0);

            if((Categoria.cod_num >= 0 && Categoria.cod_num <= 4)){
                Prezzo_Min(Musica,disc_categoria,Categoria,&Mini,&pos);
                if(Mini.prezzo != 0.00)
                    printf("\nIl titolo del disco '%s' della categoria selezionata (%d) con posizione %d e' quello con prezzo minore (%.2f %s)\n",Musica[pos].titolo,Categoria.cod_num,pos,Mini.prezzo,Euro);

                else
                    printf("\nCi dispiace, ma nella categoria selezionata (%d) non sono attualmente presenti dischi\n",Categoria.cod_num);}
            else if(cont==0)
                printf("\nFine tentativi, grazie.\n");
        printf("\n");
        }

    return 0;
}




/*La procedura aggiorna_archivio permette di inserire nuovi dischi (Artista, Titolo e Prezzo).
  Ha come parametro di input la posizione che serve per indicare, appunto, in quale posizione
  del catalogo inserire il nuovo disco, e il catalogo dei dischi di tipo Brani.
  Ha come parametro di output lo stesso catalogo, però aggiornato con i nuovi dichi*/


void aggiorna_archivio(Brani*agg_arch, int posizione)
{
    float nuovo_prezzo;
    char nuovoArtista[30];
    char nuovoTitolo[30];
    fflush(stdin);                                              /*Istruzione per pulire il buffer, senza non mi fa inserire l'artista*/
    printf("\nInserire nuovo disco\n");
    printf("\nInserire Artista: ");
    gets(nuovoArtista);
    copia_stringa(agg_arch[posizione].autore,nuovoArtista);
    printf("\nInserire Titolo: ");
    gets(nuovoTitolo);
    copia_stringa(agg_arch[posizione].titolo,nuovoTitolo);
    printf("\nInserire Prezzo: ");
    scanf("%f",&nuovo_prezzo);
    agg_arch[posizione].prezzo= nuovo_prezzo;
    printf("\n\nNuovo disco:\nAutore: %s\nTitolo: %s\nPrezzo: %.2f\n\n",agg_arch[posizione].autore,agg_arch[posizione].titolo,agg_arch[posizione].prezzo);
}




/*La procedura copia_stringa permette di copiare la stringa 't' in 's'.
  Ha come parametro di input le due stringhe e come output mi restituisce la stringa 's'.
  Nel programma viene chiamata dalla function elim_catalogo per eliminare un disco dal catalogo
  (copia la stringa t="(vuoto)" in 's' */


void copia_stringa(char s[], char t[])
{
    int i;
    for(i=0; t[i] != '\0'; i++)
        s[i] = t[i];

    s[i]= '\0';
}




/*La function appartiene permette di verificare se la chiave appartiene ad un elemento dell'array.
  Ha come parametri di input un array 'a', una chiave di tipo intero e 'n' (tipo intero)
  che rappresenta la dimensione dell'array
  La function restituisce come output 0 o 1 a seconda del fatto se
  la chiave appartiene o meno all'array.
  Nel programma viene chiamata dalla function new_dischi per evitare
  che venga generato lo stesso numero casuale.*/


int appartiene(int a[], int chiave, int n)
{
    int i;
    for(i=0;i<n;i++)
        if(a[i]==chiave)
            return 0;
    return 1;
}




/*La function confronto_stringhe permette di comparare tra loro due stringhe.
  Nella function viene prima verificata la lunghezza delle due stringhe
  chiamando la function lunghezza_stringa, se le due stringhe hanno la stessa lunghezza si prosegue
  altrimenti se la lunghezza è diversa, significa che non possono essere uguali,
  quindi viene ritornato 0.
  Se la lunghezza è uguale si prosegue verificando carattere per carattere le due stringhe.
  Se sono uguali la function ritorna 1, altrimenti ritorna 0.
  Nel programma viene chiamata dalle function new_dichi e elim_catalogo per comparare due stringhe
  (es.: se la risposta data ad una domanda è SI o NO)*/


int confronto_stringhe(char s[], char t[])
{
    int i;
    if(lunghezza_stringa(s) != lunghezza_stringa(t))
        return 0;

    for(i=0; s[i] != '\0'; i++)
        if(s[i] != t[i])
            return 0;
    return 1;
}




/*La function lunghezza_stringa verifica la lunghezza di una stringa data in input ('s')
  e restituisce in output la sua lunghezza (i).
  Nel programma viene utilizzata dalla function confronto_stringhe.*/


int lunghezza_stringa(char*s)
{
    int i;
    for(i=0; *s != '\0'; i++)
        s++;
    return i;
}




/*La procedura new_dischi permette di inserire nel catalogo, indicata una categoria,
  nuovi dischi se nella categoria selezionata risultano dischi venduti.
  Ha come parametri di input la variabile di tipo intero disc_categoria che indica il numero di dischi
  (dimensione) presenti in ogni categoria, e il catalogo Musica di tipo Brani.
  Restituisce come output il catalogo Musica aggiornato che contiene i nuovi dischi inseriti.*/


void new_dischi(Brani*Musica, int disc_categoria)
{
    int venduto,i,j,k,pos,s=0,cont=3,el_vuoto;
    char risp_affermativa[10]="SI";
    char risp_negativa[10]="NO";
    char risposta[10];
    char eliminato[]="(vuoto)";
    int prova[]={0,0,0,0,0,0,0,0,0,0};          /*E' stato inizializato con tutti zero per evitare che*/
    Brani gene;                                 /*a quelle locazioni ci fossero altri valori che avrebbero alterato
                                                  il funzionamento del programma.*/

    srand(time(NULL));

    venduto= rand()%4;                          /*Genera numeri pseudocasuali da 0 a 3.
                                                 Es.: se viene generato il valore 4, il modulo è 0; se viene generato il valore 3, il modulo è 3.*/

    do{
        printf("\nSi desidera inserire un nuovo disco? SI/NO\n");
        gets(risposta);

        if(confronto_stringhe(risposta,risp_affermativa)==0)        /* ==0 perché se si scrive la risposta in minuscolo, la function confronto mi ritornerà*/
             strupr(risposta);                                      /*sempre ==0 e quindi verrà eseguita la function strupr che*/
                                                                    /*converte la risposta che inserisco se è in minuscolo in MAIUSCOLO.
                                                                      In questo modo anche se do come risposta "si" in minuscolo lo converte in maiuscolo e non da errore.*/

        if(confronto_stringhe(risposta,risp_affermativa)==1){
            printf("\nInserire codice della categoria: Pop=0, Rap=1, Rock=2, Punk=3, Indie=4\n");
            scanf("%d",&gene.cod_num);
            printf("\nSono stati venduti %d disco/dischi nella categoria selezionata (codice %d)\n",venduto,gene.cod_num);
            }

        else if(confronto_stringhe(risposta,risp_negativa)==1)
            printf("\nGrazie\n");
        else if(confronto_stringhe(risposta,risp_affermativa)!=1 && confronto_stringhe(risposta,risp_negativa)!=1){   /*Eseguo un controllo per verificare che vengano inserite come risposte "SI" o "NO" */
            cont--;
            if(cont!=0)                                                     /*Ogni volta che viene inserito una risposta diversa, il sistema richiede di rispondere*/
                printf("\nERRORE sono rimasti %d tentativi\n",cont);        /*alla domanda "SI" o "NO" per un massimo di tre volte, dopo si interrompe.*/
            else
                printf("\nERRORE sono terminati i tentativi\n");
            }
    }
    while(confronto_stringhe(risposta,risp_affermativa)==0 && confronto_stringhe(risposta,risp_negativa)==0 && cont!=0);



    if(venduto==0 && confronto_stringhe(risposta,risp_affermativa)==1)
        printf("\nSiamo spiacenti ma non e' possibile inserire ulteriori disco/dischi\n");

    else if(venduto!=0 && confronto_stringhe(risposta,risp_affermativa)==1){

        if(gene.cod_num==0)
            j=0;
        else if(gene.cod_num==1)
            j=disc_categoria*gene.cod_num;          /*Serve per indicare da quale posizione (quindi categoria) del array di struct partire.*/
        else if(gene.cod_num==2)                    /*Ad esempio se viene selezionata la categoria Rap=1 :  j=3*1= 3.*/
            j=disc_categoria*gene.cod_num;          /*Dalla posizione 3 del catalogo inizia la categoria Rap.*/
        else if(gene.cod_num==3)
            j=disc_categoria*gene.cod_num;
        else
            j=disc_categoria*gene.cod_num;


        for(i=0+j;i<j+disc_categoria;i++){
            el_vuoto= confronto_stringhe(Musica[i].titolo,eliminato);       /*Serve per individuare i brani eliminati dal catalogo*/
            venduto=venduto+el_vuoto;                                       /*in modo da poter utilizzare questo spazio vuoto
                                                                            per inserire un nuovo disco*/
            }

        if(venduto>disc_categoria)                                      /*E' un controllo per evitare che i dischi venduti siano superiori*/
            venduto=disc_categoria;                                     /*rispetto al numero di dischi che sono presenti in ciascuna categoria*/
                                                                        /*Esempio: venduto==4 è un errore perché il numero massimo di*/
                                                                        /*dischi presenti in ciascuna categoria è 3.*/

        printf("\nE' possibile inserire nella categoria selezionata con codice %d, considerando anche eventuali dischi venduti, solo %d disco/dischi\n", gene.cod_num, venduto);

        for(k=0;k<venduto;k++){
            for(i=0;i<=s;i++){
                pos= j+rand()%disc_categoria;           /*Genera numeri pseudocasuali da 0 a 2 (disc_categoria==3), al numero generato*/
                printf("\nPosizione= %d\n",pos);        /*poi viene sommato il valore di 'j' (j indica la posizione della categoria).*/
                if(appartiene(prova,pos,k)){            /*In questo modo si evita che venga generato lo stesso numero casuale per 'pos'.*/
                    aggiorna_archivio(Musica,pos);      /*Salvo il valore di 'pos' in un array (parte[]) e tramite la function appartiene controllo*/
                    prova[k]=pos;}                      /*se il valore pseudocasuale di pos è già presente nell'array. Se NON appartiene entro nell'if altrimenti salto all'else.*/
                else{                                   /*In base a quanti dischi sono stati venduti, posso andare ad inserire nuovi dischi a sostituzione di quelli venduti*/

                    printf("\nQuesto valore e' stato gia' generato\n");
                    k--;}
                                                        /*Se pos è presente nell'array prova, vuol dire che quel valore*/
                }                                       /*è stato già generato e per non perdere un ciclo decremento k.*/
            }                                           /*altrimenti verrà inserito un disco in meno. Se sono stati venduti 3 dischi,*/
        }                                               /*e ad un ciclo risulta prova==pos, dei 3 dischi me ne farà inserire solo 2.*/
}




/*La procedura elim_catalogo permette di aggiornare il catalogo eliminando,
  indicando il titolo del disco, un prodotto dal catalogo.
  Ha come parametri di input la variabile di tipo intero 'n' che indica il numero di dischi
  (dimensione) presenti nel catalogo, e il catalogo Music di tipo Brani.
  Restituisce come output il catalogo Music aggiornato.*/


void elim_catalogo(Brani*Music, int n)
{
    char ric_titolo[30];
    int Stato,Posizione,i,cont=3;
    char risp_affermativa[10]="SI";
    char risp_negativa[10]="NO";
    char risposta[10];
    char new_contenuto[]="(vuoto)";
    float new_prezzo=0.0;
    int v[n];
    fflush(stdin);                      /*Istruzione per pulire il buffer.*/

    do{
        do{
        printf("\nSi desidera aggiornare il catalogo? SI/NO\n");
        gets(risposta);

        if(confronto_stringhe(risposta,risp_affermativa)==0)
            strupr(risposta);

        if(confronto_stringhe(risposta,risp_affermativa)!=1 && confronto_stringhe(risposta,risp_negativa)!=1){   /*Eseguo un controllo per verificare che vengano inserite come risposte "SI" o "NO" */

            cont--;
            if(cont!=0)                                                 /*Ogni volta che viene inserito una risposta diversa,*/
                printf("\nERRORE sono rimasti %d tentativi\n",cont);    /*il sistema richiede di rispondere alla domanda "SI" o "NO" */
            else                                                        /*per un massimo di tre volte, dopo si interrompe.*/
                printf("\nERRORE sono terminati i tentativi\n");
            }
        }
        while(confronto_stringhe(risposta,risp_affermativa)==0 && confronto_stringhe(risposta,risp_negativa)==0 && cont!=0);

        if(confronto_stringhe(risposta,risp_affermativa)==1){
            printf("\nIndicare il titolo del brano: ");
            gets(ric_titolo);

            for(i=0;i<n;i++)
                if(confronto_stringhe(ric_titolo,Music[i].titolo)==0)       /*Ho messo ==0 perché se scrivo la risposta in Maiuscolo, la function confronto*/
                    strlwr(ric_titolo);                                     /*mi ritornerà sempre ==0 e quindi verrà eseguita la function strlwr che*/
                                                                            /*converte la risposta che inserisco se è in MAIUSCOLO in minuscolo. In questo modo anche se do come risposta,*/
                                                                            /*ad es.: "PLAstiCA" (tutto in maiuscolo o in parte) lo converte in minuscolo e non da errore.*/
            for(i=0;i<n;i++){
                Stato=confronto_stringhe(Music[i].titolo,ric_titolo);       /*Verifica se il titolo inserito è presente nel catalogo*/
                 v[i]=Stato;                                                /*Se è stato trovato nel catalogo la function confronto_stringhe ritorna Stato==1, altrimenti Stato==0.*/
                                                                            /*I valori di Stato sono memorizzati nell'array 'v'*/
                if(Stato==1){                                               /*Se il titolo inserito è stato trovato nel catalogo, copia a quella posizione la stringa new_contenuto.*/
                    Posizione= i;
                    printf("\nIl titolo inserito '%s' e' stato trovato alla Posizione: %d\n",ric_titolo,Posizione);
                    copia_stringa(Music[Posizione].titolo,new_contenuto);
                    copia_stringa(Music[Posizione].autore,new_contenuto);
                    Music[Posizione].prezzo=new_prezzo;}
                }

                if(appartiene(v,1,n))                                       /*Stato==0, vuol dire che il titolo inserito non è stato trovato nel catalogo.*/
                    printf("\nIl titolo inserito '%s' NON e' stato trovato\n",ric_titolo);
        }
        else if(confronto_stringhe(risposta,risp_negativa)==1)
            printf("\nGrazie\n");
    }
    while(confronto_stringhe(risposta,risp_negativa)==0 && cont != 0);
}




/*La function ricorsiva minimo con approccio divide-et-impera, dato in input il catalogo
 (di tipo Brani) e 'n' che rappresenta il numero di dischi (dimensione)
  presenti in ciascuna categoria, ritorna, chiamando la function 'min',
  il prezzo minore del prodotto presente nella categoria selezionata.
  Viene chiamata dalla procedura Prezzo_Min.*/


Brani minimo(Brani a[],int n)
{
    int mediano;

    if(n==1)
        return a[0];
    else{
        mediano=(n-1)/2;
        return min(minimo(a,mediano+1), minimo(a+mediano+1,n-mediano-1));
    }

}




/*La function min, dati in input due valori ('a' e 'b') di tipo Brani,
  ritorna 'b' se il valore di 'a' è uguale a 0.00,
  viceversa ritorna 'a' se il valore di 'b' è uguale a 0.00.
  Oppure se né 'a' e né 'b' sono uguali a 0.00 verifica quali dei due è minore.
  Viene chiamata dalla procedura Prezzo_Min.*/


Brani min(Brani a, Brani b)
{
    if(a.prezzo == 0.00)
        return b;
        else if(b.prezzo == 0.00)
            return a;

    if(a.prezzo < b.prezzo)
		return a;
   return b;
}




/*La function ricerca_prezzo riceve in input il catalogo di dischi, una variabile chiave
 (entrambi di tipo Brani) e 'n' che rappresenta il numero di dischi (dimensione)
  presenti in ciascuna categoria. Mentre in output ritorna la posizione.
  Viene chiamata dalla procedura Prezzo_Min con lo scopo di trovare il valore minore
  (ritornato dalla function minimo) presente nella categoria selezionata
  e di ritornare la sua posizione nel catalogo.*/


int ricerca_prezzo(Brani a[], Brani chiave, int n)
{
    int i,posizione=0;

    for(i=0;i<n;i++)
        if(a[i].prezzo == chiave.prezzo)
            return posizione=posizione+1;
    return posizione;
}




/*La procedura Prezzo_Min riceve come input il catalogo Music,
 'n' che rappresenta il numero di dischi (dimensione) presenti in ciascuna categoria e
  categoria (del tipo Brani).
  Selezionando una categoria e chiamando le function minimo e ricerca_prezzo,
  la procedura Prezzo_Min ritorna il prezzo minore del disco e la sua posizione nel catalogo.*/


void Prezzo_Min(Brani*Music, int n, Brani categoria, Brani*Min, int*pos)
{
    int i,j;

    if(categoria.cod_num==0)
        j=0;
    else if(categoria.cod_num==1)           /*Serve per indicare da quale posizione (quindi categoria) del array di struct partire*/
        j=n*categoria.cod_num;              /*Ad esempio se viene selezionata la categoria Punk=3 :  j=3*3= 9.*/
    else if(categoria.cod_num==2)           /*Dalla posizione 9 del catalogo inizia la categoria Punk*/
        j=n*categoria.cod_num;
    else if(categoria.cod_num==3)
        j=n*categoria.cod_num;
    else
        j=n*categoria.cod_num;

    *Min= minimo(&Music[j],n);              /* *Min contiene il valore minimo (prezzo più basso) trovato nella categoria selezionata.*/

    for(i=0+j;i<j+n;i++){
        if(ricerca_prezzo(&Music[i],*Min,n))    /*Eseguo una ricerca del prezzo ritornato dalla function minimo nella categoria selezionata per conoscere*/
            *pos=i;                             /*a quele posizione del catalogo si trova tale importo.*/
    }                                           /*La posizione servirà per individuare a quale disco (titolo) corrisponde il prezzo minore.*/
}
