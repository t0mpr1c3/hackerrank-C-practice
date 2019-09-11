#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};
struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document doc, int k, int m, int n) {
    return doc.data[n - 1].data[m - 1].data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document doc, int k, int m) {
    return doc.data[m - 1].data[k - 1];
}

struct paragraph kth_paragraph(struct document doc, int k) {
    return doc.data[k - 1];
}

struct word parse_word(char** pp) {
    char* p = *pp;
    char* op = p;
    int length = 0;
    while (*p != ' ' && *p != '.' && *p != '\n') {
        length++;
        p++;
    }
    struct word w;
    w.data = (char*)calloc(length + 1, sizeof(char));
    for (int i = 0; i < length; i++) {
        w.data[i] = op[i];
    }
    *pp = p;
    return w;
}

struct document get_document(char* text) {
    char* p = text;
    struct document doc;
    struct paragraph* pdata = (struct paragraph*)malloc(5 * sizeof(struct paragraph*));
    int i = 0;
    while ((*p != '\0') && (i < 5)) {
        struct sentence* sdata = (struct sentence*)malloc(50 * sizeof(struct sentence*));
        int j = 0;
        while (*p >= 'A') {
            struct word* wdata = (struct word*)calloc(50, sizeof(struct word*));
            int k = 0;
            while (*p != '.') {
                wdata[k] = parse_word(&p);
                k++;
                if (*p == ' ')
                    p++;
            }
            sdata[j].word_count = k;
            sdata[j].data = wdata;
            //sdata[j].data = (struct word*)realloc(wdata, k * sizeof(struct word*));
            j++;
            if (*p == '.')
                p++;
        }
        pdata[i].sentence_count = j;
        pdata[i].data = sdata;
        //pdata[i].data = (struct sentence*)realloc(sdata, j * sizeof(struct sentence*));
        i++;
        if (*p == '\x0a') 
            p++;
    } 
    doc.paragraph_count = i;
    doc.data = pdata;
    //doc.data = (struct paragraph*)realloc(pdata, i * sizeof(struct paragraph*));
    return doc;
}




void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {    
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}