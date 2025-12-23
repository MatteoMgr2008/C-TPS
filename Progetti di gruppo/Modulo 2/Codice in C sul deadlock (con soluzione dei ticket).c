#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

// Dichiarazione delle variabili globali
bool flag_meccanico=false, flag_stazione_riparazione_analisi=false; // Dichiarazione dei flag usati nel codice (true = risorsa occupata, false = risorsa libera)
int counter_clienti_officina=0; // Counter dei clienti totali (generico per entrambi i tipi di clienti)
int counter_ticket_clienti=1; // Counter per la gestione dei ticket dei clienti dell'officina meccanica
sem_t sem_meccanico, sem_stazione_riparazione_analisi, sem_clienti; // Dichiarazione dei semafori usati nel codice
pthread_mutex_t mutex_ticket=PTHREAD_MUTEX_INITIALIZER; // Mutex per la gestione del counter dei ticket

// Genera il thread denominato "cliente1"
void *cliente1(void *arg) {
    int counter_clienti1;
    int ticket_cliente_officina;
    
    // Un cliente di tipo "cliente1" entra nell'officina meccanica e prende il suo ticket
    sem_wait(&sem_clienti);
    counter_clienti_officina++; // Counter dei clienti totali (generico per entrambi i tipi di clienti)
    counter_clienti1=counter_clienti_officina; // Counter dei clienti di tipo "cliente1" (è un counter locale, cioè solo di questo thread)
    ticket_cliente_officina=counter_clienti1; // Assegna un ticket al cliente
    printf("Il cliente %d entra nell'officina meccanica e prende il ticket n°%d\n", counter_clienti1, ticket_cliente_officina); // Stampa il numero del ticket preso dal cliente quando entra nell'officina meccanica
    sem_post(&sem_clienti);

    // Il cliente deve aspettare in sala d'attesa finché il suo ticket non corrisponde al valore del counter dei ticket attuali
    pthread_mutex_lock(&mutex_ticket);
    while(counter_ticket_clienti != ticket_cliente_officina) {
        pthread_mutex_unlock(&mutex_ticket);
        usleep(50000); // Attende 50 millisecondi prima di ricontrollare il ticket
        pthread_mutex_lock(&mutex_ticket);
    }
    pthread_mutex_unlock(&mutex_ticket);

    // Il thread denominato "cliente1" alloca la risorsa "meccanico"
    sem_wait(&sem_meccanico);
    flag_meccanico=true; // La risorsa "meccanico" è attualmente occupata
    printf("Il cliente %d entra nell'officina meccanica e dialoga con il meccanico per spiegargli il problema riguardante il suo veicolo\n", counter_clienti1);   
    sleep(2);
    printf("Il meccanico, quindi, si dirige alla stazione di riparazione e analisi con il veicolo del cliente %d per poterlo analizzare e succesivamente riparare\n", counter_clienti1);
    sleep(2);
    if(flag_stazione_riparazione_analisi==true){
        sem_post(&sem_stazione_riparazione_analisi);
    printf("Il meccanico sta spostando il veicolo del cliente che occupava la stazione di riparazione e analisi; il veicolo è ora parcheggiato temporaneamente all'interno dell'officina.\n");
        flag_stazione_riparazione_analisi=false; // La risorsa "stazione di riparazione e analisi" è attualmente libera
    }
    sem_wait(&sem_stazione_riparazione_analisi); 
    flag_stazione_riparazione_analisi=true; // La risorsa "stazione di riparazione e analisi" è attualmente occupata
    printf("Il meccanico attualmente sta analizzando e riparando il veicolo del cliente %d nella stazione di riparazione e analisi\n", counter_clienti1);
    sleep(2);
    printf("È appena stata conclusa la riparazione del veicolo del cliente %d e quindi adesso il veicolo è perfettamente funzionante\n", counter_clienti1);
    flag_stazione_riparazione_analisi=false; // La risorsa "stazione di riparazione e analisi" è attualmente libera
    sem_post(&sem_stazione_riparazione_analisi);
    flag_meccanico=false; // La risorsa "meccanico" è attualmente libera
    sem_post(&sem_meccanico);
    
    // Il counter dei ticket viene incrementato per permettere al successivo cliente in attesa di essere servito
    pthread_mutex_lock(&mutex_ticket);
    counter_ticket_clienti++;
    pthread_mutex_unlock(&mutex_ticket);
    
    // Elimina il thread denominato "cliente1"
    pthread_exit(0);
}

void *cliente2(void *arg) {
    // Dichiarazione delle variabili locali
    int counter_clienti2;
    int ticket_cliente_officina;
    
    // Un cliente di tipo "cliente2" entra nell'officina meccanica e prende il suo ticket
    sem_wait(&sem_clienti);
    counter_clienti_officina++; // Counter dei clienti totali (generico per entrambi i tipi di clienti)
    counter_clienti2=counter_clienti_officina; // Counter dei clienti di tipo "cliente2" (è un counter locale, cioè solo di questo thread)
    ticket_cliente_officina=counter_clienti2; // Assegna un ticket al cliente
    printf("Il cliente %d si mette in coda con il suo veicolo all'ingresso dell'officina meccanica e prende il ticket n°%d\n", counter_clienti2, ticket_cliente_officina); // Stampa il numero del ticket preso dal cliente quando entra nell'officina meccanica
    sem_post(&sem_clienti);

    // Il cliente deve aspettare in sala d'attesa finché il suo ticket non corrisponde al valore del counter dei ticket attuali
    pthread_mutex_lock(&mutex_ticket);
    while(counter_ticket_clienti != ticket_cliente_officina) {
        pthread_mutex_unlock(&mutex_ticket);
        usleep(50000); // Attende 50 millisecondi prima di ricontrollare il ticket
        pthread_mutex_lock(&mutex_ticket);
    }
    pthread_mutex_unlock(&mutex_ticket);

    // Il thread denominato "cliente2" alloca la risorsa "stazione di riparazione e analisi"
    sem_wait(&sem_stazione_riparazione_analisi); 
    flag_stazione_riparazione_analisi=true; // La risorsa "stazione di riparazione e analisi" è attualmente occupata
    printf("Il cliente %d entra nell'officina meccanica e si dirige direttamente alla stazione di riparazione e analisi con il suo veicolo, aspettando l'arrivo del meccanico\n", counter_clienti2);   
    sleep(2);
    sem_wait(&sem_meccanico);
    printf("Il meccanico, quindi, si dirige dal cliente %d alla stazione di riparazione e analisi\n", counter_clienti2);
    sleep(2);
    flag_meccanico=true; // La risorsa "meccanico" è attualmente occupata
    printf("Appena il meccanico raggiunge il cliente %d, quest'ultimo dialoga con il meccanico per spiegargli il problema riguardante il suo veicolo\n", counter_clienti2);   
    sleep(2);
    printf("Il meccanico attualmente sta analizzando e riparando il veicolo del cliente %d nella stazione di riparazione e analisi\n", counter_clienti2);
    sleep(2);
    printf("È appena stata conclusa la riparazione del veicolo del cliente %d e quindi adesso il veicolo è perfettamente funzionante\n", counter_clienti2);
    flag_stazione_riparazione_analisi=false; // La risorsa "stazione di riparazione e analisi" è attualmente libera
    sem_post(&sem_stazione_riparazione_analisi);
    flag_meccanico=false; // La risorsa "meccanico" è attualmente libera
    sem_post(&sem_meccanico);
    
    // Il counter dei ticket viene incrementato per permettere al successivo cliente in attesa di essere servito
    pthread_mutex_lock(&mutex_ticket);
    counter_ticket_clienti++;
    pthread_mutex_unlock(&mutex_ticket);
    
    // Elimina il thread denominato "cliente2"
    pthread_exit(0);
}

int main() {
    // Dichiarazione delle variabili locali
    int numero_clienti_officina;
    int domanda_numero_clienti_officina;

    // Messaggio di benvenuto nell'officina meccanica
    printf("Benvenuto nell'officina meccanica più piccola di Milano!\n");

    // Input per permettere all'utente di inserire il numero dei clienti massimo che possono entrare nell'officina meccanica
    do{
        printf("Inserire il numero di clienti massimo che si desidera permettere di entrare nell'officina meccanica: ");
        domanda_numero_clienti_officina=scanf("%d", &numero_clienti_officina);
        int c; // Variabile usata per pulire il buffer di input
        while((c=getchar()) !='\n' && c!=EOF); // Pulisce il buffer di input per evitare possibili problemi con scanf in caso di input non valido
        if(domanda_numero_clienti_officina!=1 || numero_clienti_officina<0){ // Esegue un controllo per verificare se l'input inserito è valido (dev'essere necessariamente un numero intero positivo)
            printf("Non è possibile inserire un numero minore di 0 oppure una qualsiasi altra tipologia di carattere che non sia un numero intero positivo. È possibile inserire un nuovo valore!\n");
        }
    } while(domanda_numero_clienti_officina!=1 || numero_clienti_officina<0); // Continua a richiedere l'input finché non viene inserito un numero intero positivo valido

    // Dichiarazione dell'array di thread dei clienti dell'officina meccanica
    pthread_t t[numero_clienti_officina];
    
    // Inizializza i semafori usati nel codice (1 risorsa disponibile per ciascuno)
    sem_init(&sem_meccanico, 0, 1);
    sem_init(&sem_stazione_riparazione_analisi, 0, 1);
    sem_init(&sem_clienti, 0, 1);
    
    // Inizializza il generatore di numeri casuali per il ciclo for successivo
    srand(time(NULL));

    // Questo ciclo for è necessario per simulare l'entrata alternata dei due tipi di clienti (ovvero di "cliente1" e di "cliente2") nell'officina meccanica
    printf("\n");
    printf("--- L'officina meccanica è attualmente aperta ai clienti ---\n"); // Avviso (messaggio) di apertura dell'officina meccanica ai clienti
    printf("\n");
    for(int i=0; i<numero_clienti_officina; i++){
        if(rand()%2==0){
            pthread_create(&t[i], NULL,cliente1,NULL);
        }else{
            pthread_create(&t[i], NULL,cliente2,NULL);
        }
        usleep(3000000);
    }

    // Questo ciclo for è necessario per aspettare che tutti i thread dei clienti dell'officina meccanica terminino la loro esecuzione
    for(int i=0; i<numero_clienti_officina; i++){
        pthread_join(t[i], NULL);
    }

    // Avviso (messaggio) di chiusura dell'officina meccanica ai clienti
    printf("\n=== Tutti i clienti entrati nell'officina meccanica sono stati serviti e i loro veicoli sono stati perfettamente riparati e perciò sono funzionanti ===\n");
    printf("\n");
    printf("--- L'officina meccanica è attualmente chiusa ai clienti ---\n");

    // Distrugge (elimina) i semafori usati nel codice, ormai non più necessari
    sem_destroy(&sem_meccanico);
    sem_destroy(&sem_stazione_riparazione_analisi);
    sem_destroy(&sem_clienti);
    pthread_mutex_destroy(&mutex_ticket);
    
    // Termina il programma con successo
    return 0;
}