#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Using putenv
    char env1[] = "MYVAR1=HelloWorld1";
    putenv(env1);
    printf("MYVAR1 (after putenv): %s\n", getenv("MYVAR1"));

    // Modify env1 and see the effect
    strcpy(env1, "MYVAR1=Changed");
    printf("MYVAR1 (after modifying env1): %s\n", getenv("MYVAR1"));

    // Using setenv
    setenv("MYVAR2", "HelloWorld2", 1);
    printf("MYVAR2 (after setenv): %s\n", getenv("MYVAR2"));

    // Modify environment variable with setenv
    setenv("MYVAR2", "ChangedAgain", 1);
    printf("MYVAR2 (after setenv with overwrite): %s\n", getenv("MYVAR2"));

    return 0;
}

