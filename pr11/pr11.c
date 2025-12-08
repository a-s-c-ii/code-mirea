#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

typedef struct {
    char title[40];    
    char explanation[60]; 
} Course;

#define INPUT_FILE "courses_input.txt" 
#define DATA_FILE "courses.dat"        
#define NUM_RECORDS 10                 

int load_data_from_text(Course courses[]) {
    FILE *f_in = fopen(INPUT_FILE, "r");
    if (f_in == NULL) {
        perror("Error opening input text file (courses_input.txt)");
        return 0;
    }

    int i = 0;
    while (i < NUM_RECORDS && fscanf(f_in, "%s %s", courses[i].title, courses[i].explanation) == 2) {
        i++;
    }

    fclose(f_in);
    return i; 
}

void set_lock(int fd, short l_type, off_t start_record, off_t num_records_to_lock) {
    struct flock fl;

    fl.l_type = l_type;       
    fl.l_whence = SEEK_SET;   
    fl.l_start = start_record * sizeof(Course); 
    fl.l_len = num_records_to_lock * sizeof(Course); 
    fl.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("Error applying lock/unlock");
    }
}

void print_file_contents(int fd, const char* stage_name) {
    printf("\n %s \n", stage_name);
    
    lseek(fd, 0, SEEK_SET);

    Course c;
    int record_index = 0;
    
    while (record_index < NUM_RECORDS) {
        lseek(fd, record_index * sizeof(Course), SEEK_SET);
        
        if (read(fd, &c, sizeof(Course)) == sizeof(Course)) {
            printf("Record %02d: Title: %s, Explanation: %s\n", 
                   record_index + 1, c.title, c.explanation);
        } else {
            printf("Record %02d: Data read failed\n", record_index + 1);
        }
        record_index++;
    }
}

int count_available_records(int fd) {
    int available_count = 0;
    struct flock fl;
    
    printf("\nПодсчет доступных записей\n");

    for (int i = 0; i < NUM_RECORDS; i++) {
        fl.l_type = F_WRLCK;     
        fl.l_whence = SEEK_SET;
        fl.l_start = i * sizeof(Course);
        fl.l_len = sizeof(Course);
        
        if (fcntl(fd, F_GETLK, &fl) == -1) {
            perror("fcntl F_GETLK error");
            continue;
        }

        if (fl.l_type == F_UNLCK) {
            available_count++;
        } else {
            printf("Record %02d: НЕДОСТУПНА (Locked)\n", i + 1);
        }
    }
    return available_count;
}


int main() {
    Course courses[NUM_RECORDS];
    int actual_records;
    int fd;

    actual_records = load_data_from_text(courses);
    if (actual_records == 0) {
        return 1;
    }
    
    fd = open(DATA_FILE, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening data file");
        return 1;
    }
    
    if (write(fd, courses, sizeof(Course) * actual_records) == -1) {
        perror("Error writing records to data file");
        close(fd);
        return 1;
    }

    set_lock(fd, F_WRLCK, 0, 5); 

    print_file_contents(fd, "Содержимое после запрета чтения 1-5 записей");
    
    set_lock(fd, F_UNLCK, 1, 6);

    print_file_contents(fd, "Содержимое после разрешения чтения 2-7 записей");

    int count = count_available_records(fd);
    printf("Итоговое количество доступных записей: %d\n", count);

    close(fd);
    return 0;
}