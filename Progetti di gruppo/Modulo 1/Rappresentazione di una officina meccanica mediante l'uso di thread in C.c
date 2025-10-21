#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
 
void* cliente1(void *arg) {
    printf("CLIENTE 1: Il cliente 1 arriva nell'officina meccanica con il suo veicolo da diagnosticare e successivamente riparare; percio', gli viene assegnato un meccanico\n");
    sleep(1);
    printf("CLIENTE 1: Il veicolo del cliente 1 verra' trasportato nella stazione di diagnosi affinche' il meccanico assegnato potra' diagnosticare il suo veicolo\n");
    sleep(2);
    printf("CLIENTE 1: Il veicolo del cliente 1 verra' trasportato nella stazione di riparazione affinche' il meccanico assegnato potra' riparare il suo veicolo\n");
    sleep(2);
    printf("CLIENTE 1: Riparazione completata e andata a buon fine, il cliente 1 percio' puo' uscire dall'officina con il suo veicolo riparato\n");
    return NULL;
}
 
void* cliente2(void *arg) {
    printf("CLIENTE 2: Il cliente 2 arriva nell'officina meccanica con il suo veicolo da diagnosticare e successivamente riparare; percio', gli viene assegnato un meccanico\n");
    sleep(1);
    printf("CLIENTE 2: Il veicolo del cliente 2 verra' trasportato nella stazione di diagnosi affinche' il meccanico assegnato potra' diagnosticare il suo veicolo\n");
    sleep(2);
    printf("CLIENTE 2: Il veicolo del cliente 2 verra' trasportato nella stazione di riparazione affinche' il meccanico assegnato potra' riparare il suo veicolo\n");
    sleep(2);
    printf("CLIENTE 2: Riparazione completata e andata a buon fine, il cliente 2 percio' puo' uscire dall'officina con il suo veicolo riparato\n");
    return NULL;
}
 
void* cliente3(void *arg) {
    printf("CLIENTE 3: Il cliente 3 arriva nell'officina meccanica con il suo veicolo da diagnosticare e successivamente riparare, ma deve attendere che un meccanico sia disponibile\n");
    sleep(3); // Attende che un meccanico si liberi
    printf("CLIENTE 3: Al cliente 3 gli viene assegnato un meccanico disponibile attualmente; percio', adesso il suo veicolo potra' essere diagnosticato da un meccanico nella stazione di diagnosi\n");
    sleep(1);
    printf("CLIENTE 3: Il veicolo del cliente 3 verra' trasportato nella stazione di riparazione affinche' il meccanico assegnato potra' riparare il suo veicolo\n");
    sleep(2);
    printf("CLIENTE 3: Riparazione completata e andata a buon fine, il cliente 3 percio' puo' uscire dall'officina con il suo veicolo riparato\n");
    return NULL;
}
 
int main() {
    pthread_t tid1, tid2, tid3;
    printf("INIZIO SCENARIO: L'officina meccanica apre, in questo modo puo' ricevere diversi clienti\n\n");
    // Creazione dei thread per i clienti 1 e 2 (arrivano subito all'inizio dello scenario)
    pthread_create(&tid1, NULL, &cliente1, NULL);
    pthread_create(&tid2, NULL, &cliente2, NULL);
    // Cliente 3 arriva dopo un breve ritardo rispetto ai clienti 1 e 2
    sleep(1);
    pthread_create(&tid3, NULL, &cliente3, NULL);
    // Attesa del completamento di tutti i clienti
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    printf("\nFINE SCENARIO: Tutti i veicoli dei clienti sono stati diagnosticati e riparati\n");
    return 0;
}