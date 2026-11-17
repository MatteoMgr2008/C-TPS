🇮🇹 [Italiano](#-italiano) | 🇬🇧 [English](#-english)

# C - TPS

## 🇮🇹 Italiano

### 📌 Descrizione

Raccolta di programmi in **linguaggio C** realizzati per la materia **TPS** (Tecnologie e Progettazione di Sistemi informatici e di telecomunicazioni). I progetti di gruppo simulano un'**officina meccanica** con clienti, un meccanico e una stazione di riparazione e analisi, per mettere in pratica i concetti della programmazione concorrente: **processi (`fork`)**, **thread (`pthread`)**, **semafori**, **mutex**, **deadlock** e il problema del **produttore-consumatore**.

### 📂 Contenuto

**Esercizi in classe**

| File | Descrizione |
|------|-------------|
| `File 0` | File segnaposto (vuoto) per la cartella degli esercizi in classe |

**Progetti di gruppo / Modulo 1** – processi e thread

| File | Descrizione |
|------|-------------|
| `Rappresentazione di una officina meccanica mediante l'uso di fork in C.c` | Tre clienti gestiti come processi figli creati con `fork()`; il cliente 3 attende con `waitpid()` che un meccanico si liberi |
| `Rappresentazione di una officina meccanica mediante l'uso di thread in C.c` | Lo stesso scenario realizzato con tre thread (`pthread_create` / `pthread_join`) |
| `...fork in C` (senza estensione) | Eseguibile Linux già compilato del programma con `fork` |
| `...thread in C.exe` | Eseguibile Windows già compilato del programma con i thread |

**Progetti di gruppo / Modulo 2** – sincronizzazione

| File | Descrizione |
|------|-------------|
| `Codice in C sul deadlock (senza soluzione).c` | Due tipi di clienti acquisiscono le risorse "meccanico" e "stazione di riparazione e analisi" in ordine opposto, causando un deadlock |
| `Codice in C sul deadlock (con soluzione senza i ticket).c` | Evita il deadlock forzando il rilascio della stazione quando risulta occupata (tramite flag e semafori) |
| `Codice in C sul deadlock (con soluzione dei ticket).c` | Evita il deadlock servendo i clienti in ordine di ticket, con un contatore protetto da mutex |
| `Codice in C sul produttore-consumatore.c` | Un thread produttore (arrivo dei clienti) e un thread consumatore (riparazione) sincronizzati con semafori su una coda di 5 posizioni |
| File omonimi senza estensione | Eseguibili Linux già compilati dei programmi sopra |
| `Comandi WSL per aprire i codici in C.txt` | Comandi per avviare gli eseguibili da terminale WSL |

Nei programmi sul deadlock l'utente inserisce da tastiera il numero massimo di clienti; i tipi di cliente vengono scelti a caso.

### 🛠️ Tecnologie utilizzate

- **Linguaggio C**
- **POSIX**: `fork`, `waitpid`, `pthread`, semafori (`semaphore.h`) e mutex
- **Linux / WSL** per compilare ed eseguire i programmi

### ▶️ Come compilare ed eseguire

I programmi usano librerie POSIX, quindi vanno compilati su **Linux** o su **WSL** (Windows Subsystem for Linux) con `gcc`. Dalla cartella del programma:

```bash
gcc "Codice in C sul produttore-consumatore.c" -o "Codice in C sul produttore-consumatore" -pthread
./"Codice in C sul produttore-consumatore"
```

Lo stesso vale per gli altri file `.c` (sostituendo il nome del file). In alternativa si possono avviare direttamente gli eseguibili già presenti nella repository, come indicato in `Comandi WSL per aprire i codici in C.txt` (nota: in quel file il comando per la soluzione senza ticket riporta `(con soluzione senza ticket)`, mentre l'eseguibile si chiama `Codice in C sul deadlock (con soluzione senza i ticket)`).

### 📋 Requisiti

- Un compilatore C (`gcc`) con supporto ai `pthread`
- Un ambiente Linux o WSL

### 👤 Autore

[MatteoMgr2008](https://github.com/MatteoMgr2008)

---

## 🇬🇧 English

### 📌 Description

A collection of **C programs** written for the **TPS** school subject (Information and Telecommunication Systems Technologies and Design). The group projects simulate a **car repair shop** with customers, a mechanic and a repair/diagnosis station, to practise concurrent programming concepts: **processes (`fork`)**, **threads (`pthread`)**, **semaphores**, **mutexes**, **deadlock** and the **producer-consumer** problem.

### 📂 Contents

**Esercizi in classe** (class exercises)

| File | Description |
|------|-------------|
| `File 0` | Empty placeholder file for the class exercises folder |

**Progetti di gruppo / Modulo 1** (group projects, module 1) – processes and threads

| File | Description |
|------|-------------|
| `Rappresentazione di una officina meccanica mediante l'uso di fork in C.c` | Three customers handled as child processes created with `fork()`; customer 3 waits with `waitpid()` for a mechanic to become free |
| `Rappresentazione di una officina meccanica mediante l'uso di thread in C.c` | The same scenario implemented with three threads (`pthread_create` / `pthread_join`) |
| `...fork in C` (no extension) | Precompiled Linux executable of the `fork` program |
| `...thread in C.exe` | Precompiled Windows executable of the thread program |

**Progetti di gruppo / Modulo 2** (group projects, module 2) – synchronization

| File | Description |
|------|-------------|
| `Codice in C sul deadlock (senza soluzione).c` | Two customer types acquire the "mechanic" and "repair/diagnosis station" resources in opposite order, causing a deadlock |
| `Codice in C sul deadlock (con soluzione senza i ticket).c` | Avoids the deadlock by forcing the release of the station when it is occupied (using flags and semaphores) |
| `Codice in C sul deadlock (con soluzione dei ticket).c` | Avoids the deadlock by serving customers in ticket order, with a mutex-protected counter |
| `Codice in C sul produttore-consumatore.c` | A producer thread (customer arrivals) and a consumer thread (repairs) synchronized with semaphores over a 5-slot queue |
| Files with the same names and no extension | Precompiled Linux executables of the programs above |
| `Comandi WSL per aprire i codici in C.txt` | Commands to launch the executables from a WSL terminal |

In the deadlock programs the user types the maximum number of customers; customer types are chosen at random.

### 🛠️ Technologies

- **C language**
- **POSIX**: `fork`, `waitpid`, `pthread`, semaphores (`semaphore.h`) and mutexes
- **Linux / WSL** to compile and run the programs

### ▶️ How to compile and run

The programs use POSIX libraries, so they should be compiled on **Linux** or **WSL** (Windows Subsystem for Linux) with `gcc`. From the program's folder:

```bash
gcc "Codice in C sul produttore-consumatore.c" -o "Codice in C sul produttore-consumatore" -pthread
./"Codice in C sul produttore-consumatore"
```

The same applies to the other `.c` files (just change the file name). Alternatively, you can run the precompiled executables already in the repository, as listed in `Comandi WSL per aprire i codici in C.txt` (note: in that file the command for the no-ticket solution says `(con soluzione senza ticket)`, while the executable is actually named `Codice in C sul deadlock (con soluzione senza i ticket)`).

### 📋 Requirements

- A C compiler (`gcc`) with `pthread` support
- A Linux or WSL environment

### 👤 Author

[MatteoMgr2008](https://github.com/MatteoMgr2008)
