#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid, pid1, pid2, status;
    printf("INIZIO: L'officina meccanica apre in modo da ricevere clienti\n\n");
    // Cliente 1
    pid1 = fork();
    if(pid1 == 0) {
        printf("CLIENTE 1: Il cliente 1 arriva nell'officina meccanica con il suo veicolo da diagnosticare e successivamente riparare; percio', gli viene assegnato un meccanico\n");
        sleep(1);
        printf("CLIENTE 1: Il veicolo del cliente 1 verra' trasportato nella stazione di diagnosi affinche' il meccanico assegnato potra' diagnosticare il suo veicolo\n");
        sleep(2);
        printf("CLIENTE 1: Il veicolo del cliente 1 verra' trasportato nella stazione di riparazione affinche' il meccanico assegnato potra' riparare il suo veicolo\n");
        sleep(2);
        printf("CLIENTE 1: Riparazione completata e andata a buon fine, il cliente 1 percio' puo' uscire dall'officina con il suo veicolo riparato\n");
        exit(0);
    }
    else {
        // Cliente 2
        pid2 = fork();
        if(pid2 == 0) {
            printf("CLIENTE 2: Il cliente 2 arriva nell'officina meccanica con il suo veicolo da diagnosticare e successivamente riparare; percio', gli viene assegnato un meccanico\n");
            sleep(1);
            printf("CLIENTE 2: Il veicolo del cliente 2 verra' trasportato nella stazione di diagnosi affinche' il meccanico assegnato potra' diagnosticare il suo veicolo\n");
            sleep(2);
            printf("CLIENTE 2: Il veicolo del cliente 2 verra' trasportato nella stazione di riparazione affinche' il meccanico assegnato potra' riparare il suo veicolo\n");
            sleep(2);
            printf("CLIENTE 2: Riparazione completata e andata a buon fine, il cliente 2 percio' puo' uscire dall'officina con il suo veicolo riparato\n");
            exit(0);
        }
        else {
            // Cliente 3
            sleep(1);
            printf("CLIENTE 3: Il cliente 3 arriva nell'officina meccanica con il suo veicolo da diagnosticare e successivamente riparare, ma deve attendere che un meccanico sia disponibile\n");
            // Attende che il cliente 1 finisca (simula attesa meccanico)
            pid = waitpid(pid1, &status, 0);
            printf("CLIENTE 3: Al cliente 3 gli viene assegnato un meccanico disponibile attualmente; percio', adesso il suo veicolo potra' essere diagnosticato da un meccanico nella stazione di diagnosi\n");
            sleep(1);
            printf("CLIENTE 3: Il veicolo del cliente 3 verrà trasportato nella stazione di riparazione affinche' il meccanico assegnato potra' riparare il suo veicolo\n");
            // Attende che il cliente 2 finisca
            pid = waitpid(pid2, &status, 0);
            printf("CLIENTE 3: Riparazione completata e andata a buon fine, il cliente 3 percio' esce dall'officina con il suo veicolo riparato\n");
        }
    }
    printf("\nFINE: Tutti i veicoli dei clienti sono stati diagnosticati e riparati\n");
    return 0;
}