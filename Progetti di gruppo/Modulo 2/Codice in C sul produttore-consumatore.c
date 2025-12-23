#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

// Dichiarazione delle costanti
#define dim_coda 5 // Dimensione della coda di attesa dell'officina meccanica

// Dichiarazione delle variabili globali
bool coda_officina[dim_coda]; // Definizione di un array globale condiviso (coda di veicoli), ovvero il buffer
static sem_t s_meccanico, s_stazione;  // Semafori per le risorse "meccanico" e "stazione di riparazione e analisi"

// Genera il thread denominato "arrivo_clienti_officina"
void *arrivo_clienti_officina(void *arg) {
    for(int cliente_officina=0; cliente_officina<dim_coda; cliente_officina++) {
        sem_wait(&s_meccanico); // Il cliente deve aspettare che il meccanico sia disponibile per poter essere servito
        coda_officina[cliente_officina]=true; // Il primo cliente nella coda potrà parlare con il meccanico e quindi analizzare e succesivamente riparare il suo veicolo (true = è possibile analizzare e riparare il veicolo successivo, false = il veicolo del cliente è stato analizzato e riparato)
        printf("\nIl cliente %d entra in officina, dialoga con il meccanico e lascia il suo veicolo a quest'ultimo per poter essere analizzato e successivamente riparato \nVisualizzazione della coda per l'ingresso all'officina meccannica: ", cliente_officina+1);
        for(int elemento_coda=0; elemento_coda<dim_coda; elemento_coda++)
            printf("%d ", coda_officina[elemento_coda]);
        sleep(1);
        sem_post(&s_stazione); // Segnala che serve la risorsa "stazione di riparazione e analisi"
    }
    fflush(stdout);

    // Elimina il thread denominato "arrivo_clienti_officina"
    pthread_exit(0);
}

// Genera il thread denominato "servizio_riparazione_officina"
void *servizio_riparazione_officina(void *arg) {
    for(int cliente_officina=0; cliente_officina<dim_coda; cliente_officina++) {
        sem_wait(&s_stazione); // Aspetta che la risorsa "stazione di riparazione e analisi" diventi necessaria
        printf("\nIl meccanico attualmente sta analizzando e riparando il veicolo del cliente %d nella stazione di riparazione e analisi", cliente_officina+1);
        
        printf("\nÈ appena stata conclusa la riparazione del veicolo del cliente %d e quindi adesso il veicolo è perfettamente funzionante", cliente_officina+1);
        coda_officina[cliente_officina]=false; // Il veicolo è stato analizzato e successivamente riparato dal meccanico dell'officina meccanica
        
        printf("\nVisualizzazione della coda per l'ingresso all'officina meccanica: ");
        for(int elemento_coda=0; elemento_coda<dim_coda; elemento_coda++)
            printf("%d ", coda_officina[elemento_coda]);
        
        sleep(1);
        sem_post(&s_meccanico); // Rilascia il meccanico per il cliente successivo della coda
    }
    fflush(stdout);

    // Elimina il thread denominato "servizio_riparazione_officina"
    pthread_exit(0);
}

int main(void) {
    pthread_t tid_clienti, tid_riparazione;
    
    // Messaggio di benvenuto nell'officina meccanica
    printf("Benvenuto nell'officina meccanica più piccola di Milano!\n");

    // Avviso (messaggio) di apertura dell'officina meccanica ai clienti
    printf("\n");
    printf("--- L'officina meccanica è attualmente aperta ai clienti ---\n");
    printf("\n");

    printf("Coda di attesa: %d posizioni\n", dim_coda);
    printf("Risorse disponibili attualmente nell'officina meccanica: 1 meccanico + 1 stazione di riparazione e analisi\n");
    
    // Inizializza i semafori usati nel codice (1 risorsa disponibile per ogni semaforo)
    sem_init(&s_meccanico, 0, 1); // Meccanico disponibile (inizia a 1)
    sem_init(&s_stazione, 0, 0); // Stazione in attesa (inizia a 0)
    
    // Crea il thread produttore (ovvero il thread denominato "arrivo_clienti_officina")
    if(pthread_create(&tid_clienti, NULL, arrivo_clienti_officina, NULL)<0) {
        printf("Errore nella creazione del thread\n");
        exit(1);
    }
    
    // Crea il thread consumatore (ovvero il thread denominato "servizio_riparazione_officina")
    if(pthread_create(&tid_riparazione, NULL, servizio_riparazione_officina, NULL)<0) {
        printf("Errore nella creazione del thread\n");
        exit(1);
    }
    
    // Attende la terminazione dei thread
    pthread_join(tid_clienti, NULL);
    pthread_join(tid_riparazione, NULL);
    
    // Avviso (messaggio) di chiusura dell'officina meccanica ai clienti
    printf("\n");
    printf("\n=== Tutti i clienti entrati nell'officina meccanica sono stati serviti e i loro veicoli sono stati perfettamente riparati e perciò sono funzionanti ===\n");
    printf("\n");
    printf("--- L'officina meccanica è attualmente chiusa ai clienti ---\n");
    
    // Distrugge (elimina) i semafori usati nel codice, ormai non più necessari
    sem_destroy(&s_meccanico);
    sem_destroy(&s_stazione);
    
    // Termina il programma con successo
    exit(0);
}