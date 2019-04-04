#include <stdio.h>
#include <stdlib.h>
#define POS 3 // dimensione della matrice 
/* Gioco del tris 
	@AUTHOR Nicholas Cerrone
	@DATE 28-3-2019 - 3-04-2019
	@VERSION 1.0.0
	@LAST-UPDATE 3-04-2019
	@DESCRIPTION Gioco del tris, esercizio assegnato durante un corso di programmazione di C
				, collaborazione con Roberta Sansotta
*/

//prototipazione delle funzioni
void caricaTris(char matrice[][3], int dim);
void stampaMatrice(char matrice[][3], int dim);
int controllaPosizioni(char matrice[][3], int dim, char scelta, char tic);
void svuotaMatrice(char matrice[][3], int dim);
int controllaRiga(char matrice[][3], int dim);
int controllaColonna(char matrice[][3], int dim);
int controllaDiagonalePrincipale(char matrice[][3], int dim);
int controllaDiagonaleSecondaria(char matrice[][3], int dim);
void inizializzaMatriceTris(char matrice[][3], int dim);
void inserimentoInput(char matrice[][3], int dim, char tic);
void modificaMatrice(char matrice[][3], int dim, char scelta, char tic);
int checkVittoria(char matrice[][3], int dim);


int main(int argc, char *argv[]) {
	char matrice[POS][POS];
	int check, nMosse;
	char tic;
	check=0; // valore neutro / iniziale
	inizializzaMatriceTris(matrice, POS); // inizializzazione dei valori di base / di scelta per l'utente
	tic='X'; // inizializzazione del simbolo usato per identificare un player
	nMosse=0; // inizializzazione del contatore di mosse
	//printf("Gioco del Tris, benvenuto utente %c\n",tic);
	while(check!=1 && nMosse<9){
		system("cls");
		printf("Turno dell'utente %c",tic);
		stampaMatrice(matrice, POS); 
		printf("Utente %c , selezionare la scelta per la posizione ==> ",tic);
		
		inserimentoInput(matrice, POS, tic); // richiamo la funzione per l'inserimento dell'input
		
		
		/*gestione del cambio del player: alla fine dell'inserimento dell'input, cambio il valore
		della variabile tic, andando a considerare come input l'altro player*/
		if(tic=='X'){tic='O';}else{
			tic='X';
		}
		
		check = checkVittoria(matrice, POS); // restituisce 1/0 (vittoria/non vittoria)
		//printf("\n\n\n\n\n");
		nMosse++; // incremento il numero delle mosse effettuate
	}
	system("cls");
	stampaMatrice(matrice, POS);
	// stampa finale dello stato, vittoria di uno dei due player oppure pareggio
	if(check==1){ // Vittoria
		if(tic=='X'){tic='O';}else{
			tic='X';
		}
		printf("Il giocatore %c ha vinto, complimenti!",tic); 
	}else if(nMosse==9 && check!=1){ printf("Pareggio!! ");} // Pareggio
	return 0;
}



/**
	* funzione per caricare manualmente un matrice di dimensione dim
	* @PARAM matrice[][3] matrice nella quale andremo ad inserire i valori 
	* @PARAM dim dimensione della matrice (n x n)
	* @MODIFY valori della matrice passata alla funzione
*/
void caricaTris(char matrice[][3], int dim){
	int count,count2;
	for(count=0;count<dim;count++){
		for(count2=0;count2<dim;count2++){
			printf("matrice[%d][%d] = ",count,count2);	
			scanf("%c",&matrice[count][count2]);	
			printf("%c",matrice[count][count2]);
		}
	}	
}

/**
	* funzione per svuotare completamente una matrice di caratteri
	* @PARAM matrice[][3] matrice nella quale andremo ad inserire i valori 
	* @PARAM dim dimensione della matrice (n x n)
	* @MODIFY matrice[][] modifica di tutti i valori contenuti all'interno della matrice
*/
void svuotaMatrice(char matrice[][3], int dim){
	int rows, columns;
	for(rows=0;rows<dim;rows++){
		for(columns=0;columns<dim;columns++){
			matrice[rows][columns]=' ';
		}
	}
}

/**
	* funzione per stampare interamente i valori 
	* contenuti in una matrice quadratica
	* @PARAM matrice[][3] matrice nella quale andremo ad inserire i valori 
	* @PARAM dim dimensione della matrice (n x n)
*/
void stampaMatrice(char matrice[][3], int dim){
	int rows, columns;
	printf("\n");
	for(rows=0;rows<dim;rows++){
		for(columns=0;columns<dim;columns++){
			printf(" %c |",matrice[rows][columns]);
		}
		printf("\n");
	}
}

/**
	* funzione per inizializzare la matrice con i valori delle
	* scelte utente
	* @PARAM matrice[][3] matrice nella quale andremo ad inserire i valori 
	* @PARAM dim dimensione della matrice (n x n)
	* @MODIFY matrice[][] modifica di tutti i valori contenuti all'interno della matrice	
*/
void inizializzaMatriceTris(char matrice[][3], int dim){
	int rows, columns;
	int value;
	value=1;
	char number=49; // 49 = '1' <Codifica ASCII>
	svuotaMatrice(matrice, dim);
	for(rows=0;rows<dim;rows++){
		for(columns=0;columns<dim;columns++){
			matrice[rows][columns]=number;
			/*vado ad incrementare il valore (secondo la codifica Ascii)
			della variabile che andrà a costituire il valore di una porzione
			della matrice*/
			number++;	
		}
	}
}

/**
	* funzione per controllare se alla posizione selezionata è già presente
	* un valore oppure è realmente disponibile
	* @PARAM matrice[][3] matrice nella quale andremo ad inserire i valori 
	* @PARAM dim dimensione della matrice (n x n)	
	* @PARAM scelta scelta della posizione selezionata dall'utente e passata come carattere
	* @PARAM tic valore in un dato momento del player <identificatore del player>
	* @RETURN valore di check che serve a definire se la posizione è già occupata oppure no:
		- -1: valore già occupato 
		- 1: valore disponibile
*/
int controllaPosizioni(char matrice[][3], int dim, char scelta, char tic){
	int riga, colonna;
	int sceltaI = scelta-48; // sottraggo il carattere '0' al carattere prescelto dal player 
							 // esempio ==> scelta='4' diventerà (52-48)
	// tramite i due successivi calcoli sono in grado di determinare la posizione all'interno della matrice
	riga=(sceltaI-1)/3;
	colonna=(sceltaI-1)%3;
	if(matrice[riga][colonna]=='X' || matrice[riga][colonna]=='O') return -1; // già presente
	else return 1; // non è presente
}

/**
	* funzione per modificare, ad una determinata posizione,
	* la matrice con il tic del player in turno
	* @PARAM matrice[][3] matrice nella quale andremo ad inserire i valori 
	* @PARAM dim dimensione della matrice (n x n)
	* @PARAM scelta posizione prescelta dall'utente 
	* @PARAM tic simbolo del player in turno
	* @MODIFY matrice[][] alla posizione determinata dalla scelta dell'utente ==> con il tic del player	
*/
void modificaMatrice(char matrice[][3], int dim, char scelta, char tic){
	int riga, colonna;
	int sceltaI = scelta-48; // sottraggo il carattere '0' al carattere prescelto dal player 
	// tramite i due successivi calcoli sono in grado di determinare la posizione all'interno della matrice
	riga=(sceltaI-1)/3;
	colonna=(sceltaI-1)%3;
	matrice[riga][colonna]=tic; // vado a modificare il valore
}

/**
	* funzione per gestire l'inserimento dell'input di un utente
	* anche attraverso sotto-metodi definiti sopra
	* @PARAM matrice[][3] matrice nella quale andremo ad inserire i valori 
	* @PARAM dim dimensione della matrice (n x n)	
	* @PARAM tic simbolo del player in turno
*/
void inserimentoInput(char matrice[][3], int dim, char tic){
	char scelta;
	int checkPosizione;
	checkPosizione=0; // stato neutro / non ancora utilizzato
	//printf("\n\nBreakP#1\n\n");
	while(checkPosizione!=1){
		//printf("\n\nBreakP#2\n\n");
		while(scelta<'1' || scelta>'9'){
			scelta=getch();
			//printf("\n\nBreakP#3\n\n");
		}
		//printf("\n\nBreakP#4\n\n");
		checkPosizione = controllaPosizioni(matrice, dim, scelta, tic); // controllo se la posizione è libera o meno
		printf("%c", scelta);
		/*se il valore è già presente eseguo questa porzione di codice*/
		if(checkPosizione==-1) {
			scelta='0'; // fondamentale: serve per eseguire il macro-while correttamente (il problema sorgerebbe poi
							// nel while più interno)
			printf("\n#ERROR 57: valore inserito gia' presente nella matrice, inserire nuovo valore [valore inserito: %c]\n",scelta); // stampa di errore	
		}
	}
	//printf("\n\nBreakP#5\n\n");
	//printf("%c", scelta);
	modificaMatrice(matrice, dim, scelta, tic); // a questo punto abbiamo la certezza che i controlli sono andati a buon fine
													// e quindi possiamo modificare tranquillamente il valore alla posizione
													// determinata dall'utente
	
	/*
	SOLUZIONE ALTERNATIVA:
	considerare <da richiamare nel main> di richiamare singolarmente i metodi:
		- inserimentoInput
		- controllaPosizioni
		- modificaMatrice
	[in questa sequenza]
	senza utilizzare un unico macro-metodo
	.....
	*/
}

/**
	* funzione per controllare una determinata riga e restituisce un valore di 
	* controllo che determina se la vittoria si è verificata
	* @PARAM matrice[][3] matrice sulla quale vogliamo eseguire il controllo su una determinata riga
	* @PARAM row valore intero che determinata (passato come parametro) su quale riga vogliamo effettuare il controllo
	* @RETURN valore di controllo
		- 1 = condizione di vittoria verificata
		- -1 = condizione di vittoria non verificata
*/
int controllaRiga(char matrice[][3], int row){
	if((matrice[row][0] == matrice[row][1]) && matrice[row][0] == matrice[row][2]){
		return 1; // vittoria in atto
	}else return -1; // vittoria non verificata
}

/**
	* funzione per controllare una determinata colonna e restituire un valore
	* di controllo che determina se la vittoria si è verificata	
	* @PARAM matrice[][3] matrice sulla quale vogliamo eseguire il controllo su una determinata colonna
	* @PARAM col valore intero che determinata (passato come parametro) su quale colonna vogliamo effettuare il controllo
	* @RETURN valore di controllo
		- 1 = condizione di vittoria verificata
		- -1 = condizione di vittoria non verificata
*/
int controllaColonna(char matrice[][3], int col){
	if((matrice[0][col] == matrice[1][col]) && matrice[0][col] == matrice[2][col]){
		return 1; // vittoria in atto
	}else return -1; // vittoria non verificata
}

/**
	* funzione per controllare la diagonale sx-dx e restituire un valore
	* di controllo che determina se la vittoria si è verificata
	* @PARAM matrice[][3] matrice sulla quale vogliamo eseguire il controllo sulla diagonale principale sx-dx
	* @RETURN valore di controllo
		- 1 = condizione di vittoria verificata
		- -1 = condizione di vittoria non verificata
*/
int controllaDiagonalePrincipale(char matrice[][3], int dim){
	/*
	Metodo deprecato ... 
	if((matrice[0][0] == matrice[1][1]) && matrice[0][0] == matrice[2][2]){
		return 1; // vittoria in atto
	}else return -1; // vittoria non verificata
	*/
	int c, check;
	check=0;
	for(c=0;c<(dim-1);c++){
		if(matrice[c][c] == matrice[c+1][c+1]) check++;
		else check--;
	}
	//se all'uscita dal ciclo check vale 2 vuol dire che si sono riscontrati tre valori in diagonale uguali
	if(check==2) return 1; // vittoria in atto
	else return -1; // vittoria non verificata
}

/**
	* funzione per controllare la diagonale dx-sx e restituire un valore
	* di controllo che determina se la vittoria si è verificata
	* @PARAM matrice[][3] matrice sulla quale vogliamo eseguire il controllo sulla diagonale secondaria dx-sx
	* @PARAM dim dimensione della matrice (n x n)
	* @RETURN valore di controllo
		- 1 = condizione di vittoria verificata
		- -1 = condizione di vittoria non verificata
*/
int controllaDiagonaleSecondaria(char matrice[][3], int dim){
	/*int c,check,c2;
	check=0;*/
	
	/*for(c=0;c<(dim-1);c++){
		/*for(c2=(dim-1);c2>0;c2--){
			if(matrice[c][c2-1] == matrice[c+1][c2-1]) check++;
			else check--;
			system("cls");
			printf("%d-%d",c,c2);
			system("pause");
		}*/
		/*if(matrice[c][dimensione-c] == matrice[c+1][dimensione-(c*2)]) check++;
		else check--;
		
		printf("\n\n%d-%d",c,(dimensione-c));
		system("pause");*/
	/*}*/
	
	/*int r,c;
	int f=0;
	for(r=0;r<dim;r++){
		for(c=2;c>0;c--){
			if (r%c==0){
			f++;
			}
		}
	}
	if (f==dim){
	return 1;
	}
	else{
	return -1;
	}
	/*if(check==2) *//*return 1; // vittoria in atto
	/*else return -1; // vittoria non verificata*/
	int row, column;
	int check=0;
	for(row=0,column=(dim-1);row<(dim-1);row++,column--){
		if(matrice[row][column]==matrice[row+1][column-1]) check++;
		else check--;
	}
	//se all'uscita dal ciclo check vale 2 vuol dire che si sono riscontrati tre valori in diagonale uguali
	if(check==2) return 1;
	else return -1;
	/*
	if((matrice[0][2] == matrice[1][1]) && matrice[0][2] == matrice[2][0){
		return 1; // vittoria in atto
	}else return -1; // vittoria non verificata
	*/
}

/**
	* funzione generale per verificare se si è nel caso di vittoria
	* per un player
	* @PARAM matrice[][3] matrice sulla quale vogliamo eseguire i controlli
 	* @PARAM dim dimensione della matrice (n x n)
	* @RETURN valore di check con il seguente significato:
		- 1: vittoria verificata (attraverso i sotto-metodi)
		- 0: vittoria non verificata --> continuazione della partita
*/
int checkVittoria(char matrice[][3], int dim){
	/* quattro metodi per il controllo di 
	: - righe
	  - colonne
	  - diagonaleprincipale
	  - diagonalesecondaria
	*/
	int del; // delimitatore
	int check,checkF; // check usato per i sotto-metodi e checkF come valore di ritorno
	check=0; // stato iniziale / neutro
	for(del=0;del<dim || check==0;del++){
		// richiamo dei controlli e verifica del valore di controllo
		check = controllaRiga(matrice, del);
		if(check==1) checkF=1;		
		check = controllaColonna(matrice, del);
		if(check==1) checkF=1;
	}
	check = controllaDiagonalePrincipale(matrice, dim);
	if(check==1) checkF=1;
	check = controllaDiagonaleSecondaria(matrice, dim);
	if(check==1) checkF=1;
	
	/* adesso restituisco checkF, che mi darà 1 se si è verificata, almeno
	una volta, una condizione di vittoria */	  
	return checkF;
}
