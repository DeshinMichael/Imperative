#include <stdio.h>
#include <string.h>

typedef struct Note_t {
    int key;
    char value[8];
} Note;

void insert_sorted(Note *notes, int *len, Note new_note) {
    int i = *len - 1;
    while (i >= 0 && notes[i].key > new_note.key) {
        notes[i+1] = notes[i];
        i--;
    }
    notes[i+1] = new_note;
    (*len)++;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    Note notes[n];
    int len = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %s", &notes[i].key, notes[i].value);

        insert_sorted(notes, &len, notes[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("%d %s\n", notes[i].key, notes[i].value);
    }

    return 0;
}