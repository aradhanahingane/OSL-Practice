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
 
    shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666); 
    if (shm_id < 0) { 
        perror("shmget failed"); 
        exit(1); 
    } 
    cout << "Server: Shared memory created with ID " << shm_id << "\n"; 
 
    shm_ptr = (char *)shmat(shm_id, NULL, 0); 
    if (shm_ptr == (char *)-1) { 
        perror("shmat failed"); 
        exit(1); 
    } 
 
    cout << "Server: Enter message to write: "; 
    string msg; 
    getline(cin, msg); 
 
    strncpy(shm_ptr, msg.c_str(), SHM_SIZE - 1); 
    shm_ptr[SHM_SIZE - 1] = '\0'; 
 
    cout << "Server: Message written.\n"; 
 
    shmdt(shm_ptr); 
    return 0; 
}
