//Bir txt dosya içerisindeki kodda var olan parantez hatalarını tespit edecek programı stack array implementation ile yazınız. 
//Metin dosyasında yazılı kodu açılacak, dosya göstericisi tek tek okuyacak ve bir stack'e aktaracaktır, yalnızca parantez kontrolü yapılacaktır.

/*

int main(){
while(1){
float a= [((4*8) +7)/5];
for(int i=0; i<=0; i++){
    printf("%d\n",i);
}
}
}
}
*/ 
#include <stdio.h>
#include <stdlib.h>

// Stack veri yapısı
struct Stack {
    char data;
    struct Stack* next;
};

// Stack'in başlangıç noktası
struct Stack* stack = NULL;

// Stack'e eleman ekleme işlemi
void push(char data) {
    struct Stack* newElement = (struct Stack*)malloc(sizeof(struct Stack));
    newElement->data = data;
    newElement->next = stack;
    stack = newElement;
}

// Stack'ten eleman çıkarma işlemi
char pop() {
    if (stack == NULL) {
        return '\0'; // Boş stack'ten eleman çıkarma işlemi
    }
    char data = stack->data;
    struct Stack* temp = stack;
    stack = stack->next;
    free(temp);
    return data;
}

// Parantez kontrol fonksiyonu
int checkParentheses(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Dosya bulunamadı!\n");
        return -1;
    }

    int line = 1;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            line++;
        } else if (c == '(' || c == '{' || c == '[') {
            push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            char top = pop();
            if (top == '\0' || (c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
                printf("Parantez hatası: Satır %d\n", line);
                fclose(file);
                return 1;
            }
        }
    }

    if (stack != NULL) {
        printf("Parantez hatası: Dosyanın sonunda kapanmamış parantezler bulunuyor.\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

int main() {
    const char* fileName = "ornek_kod.txt"; // Kontrol edilecek dosyanın adı belirtilir
    int result = checkParentheses(fileName);

    if (result == 0) {
        printf("Parantezler düzgün eşleşiyor.\n");
    } else {
        printf("Parantez hataları bulundu.\n");
    }

    return 0;
}