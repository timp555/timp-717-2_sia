#include <stdio.h>

int main(){
    int n, num, sum = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &num);
        if ((i+1) % 2 == 1)
        sum += num * num * num;
    }
    printf("%d\n", sum);
    return 0;
}

