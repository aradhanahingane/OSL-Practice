#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <cstring> 
#include <cstdlib> 
 
#define SHM_SIZE 1024 
#define SHM_KEY 1234 
 
using namespace std; 
 
int main() { 
    int shm_id; 
    char *shm_ptr; 
 
    shm_id = shmget(SHM_KEY, SHM_SIZE, 0666); 
    if (shm_id < 0) { 
        perror("shmget failed"); 
        exit(1); 
    } 
 
    shm_ptr = (char *)shmat(shm_id, NULL, 0); 
    if (shm_ptr == (char *)-1) { 
        perror("shmat failed"); 
        exit(1); 
    } 
 
    cout << "Client: Message from shared memory:\n" << shm_ptr << "\n"; 
 
    shmdt(shm_ptr); 
    // Optional cleanup 
    // shmctl(shm_id, IPC_RMID, NULL); 
 
    return 0; 
} 

/*
amarr@LAPTOP-OQ6BFHFC:~/Assignment7B$ g++ shared_memory_server.cpp -o server 
amarr@LAPTOP-OQ6BFHFC:~/Assignment7B$ ./server 
Server: Shared memory created with ID 0 
Server: Enter message to write: hii 
Server: Message written. 
amarr@LAPTOP-OQ6BFHFC:~/Assignment7B$ g++ shared_memory_client.cpp -o client  
./client 
Client: Message from shared memory: 
hii
*/